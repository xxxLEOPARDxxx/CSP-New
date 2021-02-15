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
		if(!bDisableMapEnter && !CheckAttribute(pchar,"GenQuest.CannotWait") && CheckSaveGameEnabled() == true) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
	    {
			Link.l4 = "��������� 2 ����.";
	    		Link.l4.go = "TalkSelf_WasteTime";
				if(PChar.Dozor != "0" && PChar.Dozor != "END")
				{
					if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
					{
							link.l4 = "������� ������� ���������.";
							link.l4.go = "Dozor_MekaKhrom";
					}
				}
		}
		//End Boyer add
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
	        	// ��� ������ ������ ���� ��������� ���������
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
			
			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l18 = "��... ���������� ��� ����� ������ ��������� ������������ ������� ''" + PChar.ColonyBuilding.ColonyName + "''. ���� �����, � � ���"+GetSexPhrase("","�")+" ���������?";
						Link.l18.go = "ColonyBuilding_Hovernor_1";
					}
				}	
			}
					
			if(PChar.ColonyBuilding.Hovernor == PChar.id)
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l19 = "������� � ����� �������.";
						Link.l19.go = "ColonyBuilding_Hovernor";
					}
				}	
			}
			
			if(PChar.Dozor != "0" && PChar.Dozor != "END")
			{
				if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
				{
		    			link.l10 = "������� ������� ���������.";
		    			link.l10.go = "Dozor_MekaKhrom";
				}
			}
			
			if (!CheckAttribute(pchar,"questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay();
	        if (pchar.location != Get_My_Cabin() && Pchar.questTemp.CapBloodLine == false && !CheckAttribute(pchar, "DisableChangeFlagMode") && sti(pchar.questTemp.stels.sea) != GetDataDay() && CheckSaveGameEnabled() == true)
			{
				Link.l7 = "������ ������ �� ����� �����.";
				Link.l7.go = "TalkSelf_ChangeFlag";
			}
	        if(!bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
	        {
	        	Link.l8 = "��� �� ������ �� ���������...";
	    		Link.l8.go = "TalkSelf_StartWait";
	    	}
			if(!CheckAttribute(pchar,"bookreadtoday") && CheckAttribute(pchar,"booktime") && !bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
	        {
	        	Link.l9 = "�������� �����.";
	    		Link.l9.go = "ReadBook";
	    	}
			Link.l10 = "���������� ��������� ������������� ���.";
	    	Link.l10.go = "food_priority";
			Link.l11 = "������������ ��� �������������.";
	    	Link.l11.go = "autofood";
			if(CheckAttribute(pchar,"autofood"))
	        {
	        	Link.l11 = "���������� �������������� ������������� ���.";
	    		Link.l11.go = "autofood_stop";
	    	}
			
			Link.l12 = RandPhraseSimple("�� ������. ��� �������.", "�������. ���� ����.");
			Link.l12.go = "exit";
		break;
		
		case "autofood":
			Dialog.Text = "������� �������, �� �������� ������ ���������� �������, ������ ��� ������ ������������ ��� (10-90).";
			//PChar.autofood_use
			link.l1 = "";
			Link.l1.edit = 3;
			Link.l1.go = "autofood_percentage";
		break
		
		case "autofood_stop":
			DeleteAttribute(pchar, "autofood");
			DeleteAttribute(pchar, "autofood_use");
			dialog.text = "�������������� ������������� ��� ���������.";
			Link.l1 = "��, ������ �� �������.";
			Link.l1.go = "exit";
		break
		
		case "autofood_percentage":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 10 || iTemp > 90)
			{
				dialog.text = "���-�� � ������� �� � ���� �������... � ������ ���, �������.";
				link.l1 = "������!";
				link.l1.go = "exit";
				break;
			}
			PChar.autofood_use = iTemp;
			dialog.text = "�������������� ������������� ��� ��������.";
			pchar.autofood = true;
			link.l1 = "������!";
			link.l1.go = "exit";
		break;

		case "food_priority":
			dialog.text = "����� ��� ����� ������������ � ������ �������?.";
			link.l1 = "����� ����������� (������, ����)";
			link.l1.go = "autofood_finished";
			link.l2 = "����� ����������� ����������� (����, ����)";
			link.l2.go = "autofood_finished_betterfood";
		break;
		
		case "autofood_finished":
			dialog.text = "��������� ��� ��� ����������.";
			DeleteAttribute(pchar, "autofood_betterfood");
			link.l1 = "������!";
			link.l1.go = "exit";
		break;
		
		case "autofood_finished_betterfood":
			dialog.text = "��������� ��� ��� ����������.";
			PChar.autofood_betterfood = true;
			link.l1 = "������!";
			link.l1.go = "exit";
		break;
		
		case "ReadBook":
			Dialog.Text = "�� ���-�, ������� ���� �����...";
			WasteTime(4);
			pchar.booktime = sti(pchar.booktime) - 1;
			pchar.bookreadtoday = true;
			if (sti(pchar.booktime) <= 0)
			{
				AddCharacterExpToSkill(pchar, pchar.booktype, sti(pchar.bookbonus));
				int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
				Log_Info(GetFullName(pchar) + " ������ ����� ''"+LanguageConvertString(idLngFile, pchar.bookname)+"'' � �������� ����� ''"+XI_ConvertString(pchar.booktype)+"''");
				LanguageCloseFile(idLngFile);
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktime.full");
				DeleteAttribute(pchar,"bookbonus");
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktype");
				DeleteAttribute(pchar,"bookreadtoday");
				string sEquipItem = GetCharacterEquipByGroup(pchar, BOOK_ITEM_TYPE);
				RemoveCharacterEquip(pchar, BOOK_ITEM_TYPE);
				RemoveItems(pchar, sEquipItem, 1);
			}
			Link.l6 = "��, ������ �� �������.";
			Link.l6.go = "exit";
		break
		
		case "TalkSelf_ChangeFlag":
			Dialog.Text = "����� ���� ��� ��������� �� ������ ������? ��� ����� ����� 1 ���.";
			if (IsCharacterPerkOn(pchar,"FlagPir") && sti(pchar.nation) != 4) {Link.l1 = "������� ��������� ����."; Link.l1.go = "TalkSelf_ChangeFlagPir";}
			if (IsCharacterPerkOn(pchar,"FlagEng") && sti(pchar.nation) != 0) {Link.l2 = "������� ���������� ����."; Link.l2.go = "TalkSelf_ChangeFlagEng";}
			if (IsCharacterPerkOn(pchar,"FlagFra") && sti(pchar.nation) != 1) {Link.l3 = "������� ����������� ����."; Link.l3.go = "TalkSelf_ChangeFlagFra";}
			if (IsCharacterPerkOn(pchar,"FlagSpa") && sti(pchar.nation) != 2) {Link.l4 = "������� ��������� ����."; Link.l4.go = "TalkSelf_ChangeFlagSpa";}
			if (IsCharacterPerkOn(pchar,"FlagHol") && sti(pchar.nation) != 3) {Link.l5 = "������� ����������� ����."; Link.l5.go = "TalkSelf_ChangeFlagHol";}
			Link.l6 = RandPhraseSimple("�� ������. ��� �������.", "�������. ���� ����.");
			Link.l6.go = "exit";
		break;
		
		case "TalkSelf_ChangeFlagPir":
			Log_Info("������ ��������� ����");
			FlagsProcess1(4);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagEng":
			Log_Info("������ ���������� ����");
			FlagsProcess1(0);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagFra":
			Log_Info("������ ����������� ����");
			FlagsProcess1(1);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagSpa":
			Log_Info("������ ��������� ����");
			FlagsProcess1(2);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagHol":
			Log_Info("������ ����������� ����");
			FlagsProcess1(3);
			DialogExit_Self();
		break;
		
		// �������� �������
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
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
		
		// ���� ����� �������� ���������.
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "��� �� ����� ���������?";
			Link.l1 = "�������, � � ���"+GetSexPhrase("","�")+" ���������.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "� ���������.";
			Link.l2.go = "Exit";
		break;
	        case "ColonyBuilding_Hovernor_2":
		        bQuestDisableMapEnter = true;
		        Log_SetStringToLog("��� ��� �� ����� ������������, ������ �� �� ������ �������� ������� �������.");
		        
			PChar.ColonyBuilding.Hovernor = PChar.id;
			DialogExit_Self();
	        break;
	
		case "ColonyBuilding_Hovernor":
			dialog.Text = "����������� ������� ��������� ��� ������� " + PChar.ColonyBuilding.ColonyName + ".";
			Link.l1 = "����� �������� ������� ������� ��������� ���.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "���-�� ��� �� �� ���� ��� ���������� �����.";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "������ �� �������������.";
			Link.l3.go = "Exit";
		break;
	
		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "��... � ����� ������ ����� � ���� ������������?";
			Link.l1 = "��������� ������� � � ���������� �����������.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "������ ���������� ��������� � �������� �������.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "�������� ������� � ������� ��� ������.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "������ �� �������������.";
			Link.l4.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			DialogExit_Self();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			DialogExit_Self();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			DialogExit_Self();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "������"+GetSexPhrase("","�")+" �� �, ��� �� ���� ��������� ����� ��������?";
			Link.l1 = "��.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "���, � ���������"+GetSexPhrase("","�")+". �� ��������� - ����������!";
			Link.l2.go = "Exit";
		break;
		
		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
		        bQuestDisableMapEnter = false;
		        Log_SetStringToLog("�������� ���� ������������ �� ����� ������ ���� ��������� ���������!");
			dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
			Link.l1 = "...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
		break;
		
		// �������� �������
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;
		
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}


void FlagsProcess1(int nation)
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;
	

	Sea_ClearCheckFlag(); // �������� ���� � ���� �������� ��������� �� ����.
	DoQuestFunctionDelay("FreeChangeFlagMode", 15.0); // ����� + �����
	
	switch (nation)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void PirateProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";
	
    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void EnglandProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void FranceProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";
	
    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void SpainProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void HollandProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

