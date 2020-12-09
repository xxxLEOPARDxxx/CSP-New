void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, rShip;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr;
    
	// ��������� ��� �� ����� -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // ����� � �����
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
 	// ��������� ��� �� ����� <--
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "���� �� ������� ��� ������, ������, ���-�� ����� ��� � ����";
			Link.l1 = "�����";
			Link.l1.go = "exit";
			//���
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "halen_room")
        		{
        		    dialog.text = "��, ���� ����� � ���������. ���� ���������� ���������...";
        			link.l1 = "...";
        			link.l1.go = "exit";
		    		AddDialogExitQuestFunction("RatHunters_Sleep");
        		}
			}
 			//===> ������ ����, ����� ����� ������ �� ������
			if (CheckAttribute(pchar, "quest.DestroyPirate_PirateIsOut") || CheckAttribute(pchar,"quest.CaptainComission_CapIsOut"))
			{
				dialog.text = "���� ��������� ������, ���� ��� �� �������� � ��������� ��������...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				pchar.quest.Munity = "Deads";
			}
			// ==> ���������� �������, ����� �8: � ��������� ����������
   	    	if (pchar.questTemp.State == "ToMansfield_GoOn")
    		{
    		    dialog.text = "������!!! ��� ����� ���������? ����� ���������� ����� ���� ����-������ ������...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1 = "location";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1.location = "LaVega_port";
				Pchar.quest.ToMansfield_OutFromFort.win_condition = "ToMansfield_OutFromFort";
    		}
            // ==> ���. �������, ����� �4: � ������� ����� ����
            if (pchar.questTemp.State == "Sp4Detection_toMirderPlace")
    		{
    		    dialog.text = "��, �������� ������. ��� �������� �������� � �������� ��������... � ��� ��� �� ���������? ���, ��� ����� ������� �� ��������� �������� ����! ��� ����� ���� ������ ������� ������. ��� ����� ����� � ��������� �������� ������, ������� �������� ����� ����.";
    			link.l1 = "...";
    			link.l1.go = "exit";
                pchar.questTemp.State = "Sp4Detection_FoundLetter";
                AddQuestRecord("Spa_Line_4_MirderDetection", "2");
				AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","�"));
    		}
            // ==> ����������� �������, ����� �2: � ������� �������
   	    	if (pchar.questTemp.State == "Fr2Letter_SeekProblems")
    		{
    		    dialog.text = "�������� �������, ������... �������, ����� ����������, ���� ��� ��� �����������...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.questTemp.Out = 1;
				SaveCurrentQuestDateParam("questTemp");
    		}
			// ==> ��������, ����� ������� ��������
   	    	if (pchar.RomanticQuest == "SeekIsabella" && pchar.location == "Beliz_ExitTown")
    		{
    		    dialog.text = "������, ��� � ���� �������� ������... ���� ���������� ������� ����� - ������� ����� ��������. ������, � �� ������ ����.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.RomanticQuest = "FoundServantGirl";
				characters[GetCharacterIndex("ServantGirl")].LifeDay = 0;
    		}
			// ==> ����� ��������, ����������� ����� � ������ � ��������
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = "���, ����� ���� ���� ����-��. �� �� ������ ������. ����� �� �������.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			//===> ����� ��������, ������� ������� �����.
			if (pchar.questTemp.Azzy == "Azzy_IHaveLamp" && locations[reload_location_index].type == "shipyard")
			{
				dialog.text = "���, ��� � ��, ��� ��� �����: �������� �����, ���������, ������� ��� �����... ����� ���������� � ��������...";
				Link.l1 = "��������� �����������.";
    			Link.l1.go = "FreedomAzzy";
			}
			//===> ������ ����� �����
			if (pchar.questTemp.BlueBird == "seenCarriers")
			{
				dialog.text = "��-�-��, ����� �����-�� ���. ������ �����, ��������, ��� ����� ������...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				AddDialogExitQuestFunction("BlueBird_endCaveDialog");
			}
		break;
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("������ ���� �������... ������ ����� ������� ������������� ������.", "��! ��� ���� ������. � ��� ���������� ����� �����������!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("��... ��� �� ��� ������ �������� �������?", "��� �� ��������?");
		//Boyer add
		if (!bDisableMapEnter) {
			Link.l4 = "��������� 2 ����.";
	    		Link.l4.go = "TalkSelf_WasteTime";
		}
		//End Boyer add
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
	        	// ��� ������ ������ ���� ��������� ���������
	            /*if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    		{
	    			link.l1 = "�������� �� ����.";
	    			link.l1.go = "TalkSelf_room_day";
	    		}
	    		else
	    		{
	    			link.l1 = "�������� �� ����.";
	    			link.l1.go = "TalkSelf_room_night";
	    			link.l2 = "�������� �� ���������� ����.";
					link.l2.go = "TalkSelf_room_day";
	    		}*/
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "������� ����������.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //���.�������, ����� �6, ����������� ������������ � ���������� �������
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "�������� �� ����.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "�������� �� ����.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "�������� �� ���������� ����.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        /*if (CheckAttribute(pchar, "Quest.Loans") || CheckAttribute(pchar, "Quest.Deposits"))
	        {
	    		Link.l4 = "�������� �����.";
	    		Link.l4.go = "TalkSelf_CashBook";
			}*/
	        if (!bDisableMapEnter)//��� � ���� ���
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "��������� ����� � �������";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // ������ ������
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
	        {
	            Link.l6 = "������ ������ ���������� ������.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
	        if(!bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
	        {
	        	Link.l7 = "��� �� ������ �� ���������...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
	        
			Link.l10 = RandPhraseSimple("�� ������. ��� �������.", "�������. ���� ����.");
			Link.l10.go = "exit";
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // ����� � ���������, ����� - �� �������� ���������
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//Boyer add
		case "TalkSelf_WasteTime":
			NextDiag.CurrentNode = NextDiag.TempNode;
			WasteTime(2);
			DialogExit_Self();
		break;
		//End Boyer add
		//  ������ ������
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "������ ������, �������, �����, �� ��� ������ ������� ��� ������� ����� ����� �� �����������. � ������ �������� �� ������.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Panama_ExitTown")
					{
						Dialog.Text = "��-�-��, � �� �����������. ��� �� ������! ����� �� ����������!!! ���� ������ ������, � �� ����� ������� ������ �����...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "������� �� ����� " + GetCityName(chr.City) + ".";
		    			Link.l1 = "� ������!";
		    			Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "���������!";
		    			Link.l2.go = "exit";
					}
	    		}
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "��! ������� ��������, ����� ���� �� 500 �������.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "�� ������������! ���������� �����!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // ��� ����������
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // ��������� ����� � �������  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "����� �� ����� �� ����� ���� � �������.";
	            Link.l1 = "�� � �� �����!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "�� ������� ��� ����� ��� ����� ��������.";
	                Link.l1 = "��! ����� ����������� ����� ������� �� ������ �������.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "� ������� ������ ����� " + pchar.GenQuest.SlavesToCrew+ " �����. ����� ��?";
	                Link.l1 = "��";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "���";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        if (CheckOfficersPerk(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
	        // ������� ����� -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// ������� ����� <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// ��������� ����� � �������  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "������ ���� �������� ������� ���, � � ����� �������! ����, �������� �������� ��� �������.";
			Link.l1 = "���� �� �����...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//������ �� ���� �����...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//���� ���������
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "���� �� ����������� �������?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "� ������ ���.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		// ����� ��������, ������������ ����.
		case "FreedomAzzy":
			chr = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, -1, false));
			chr.name = "�����";
			chr.lastname = "����";
			chr.Dialog.Filename = "Quest\Azzy_dialog.c";
			GiveItem2Character(chr, "blade28");// ����� �������
			chr.equip.blade = "blade28";
			chr.rank 	= 100;
			chr.reputation = "0";
			SetSelfSkill(chr, 100, 100, 100, 100, 100);
			SetShipSkill(chr, 100, 100, 100, 100, 100, 100, 100, 100, 100);
			LAi_SetImmortal(chr, true);
			LAi_SetActorType(chr);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetHP(chr, 10000.0, 10000.0);
			chr.greeting = "Gr_Azzy";
			ChangeCharacterAddressGroup(chr, pchar.location, "officers", "reload1_1");
			DoQuestCheckDelay("Ascold_AzzyIsFree", 4.0);
			pchar.questTemp.Azzy = "Azzy_Freedom";
			DialogExit();
		break;	
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}
