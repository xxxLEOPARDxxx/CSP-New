void ProcessDialogEvent()
{
	ref NPChar, mc;
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
	
// ����� ���������� by xxxZohanxxx -->	
  	if (findsubstr(sAttr, "CabinPassengerTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
		PChar.GenQuest.CabinPassengerNum = strcut(sAttr, i+1, strlen(sAttr)-1); // ������ � �����
 	    Dialog.CurrentNode = "Cabin_Passenger_Talk";
 	}
// <-- ����� ���������� by xxxZohanxxx	
 	// ��������� ��� �� ����� <--
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "WhisperTownbattle_1":
				dialog.Text = "���������� � ���� �����\n(���������: ����� ������� ��������� ���� ������� ������� 1 ��� ������)";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				Pchar.model="PGG_Whisper_0";
				pchar.Whisper.HatEnabled = true;
				TakeNItems(PChar, "hatWhisper", 1);
				EquipCharacterByItem(pchar, "hatWhisper");
				ChangeWhisperHeroModel();
				Link.l1 = "��� ���� ��� ��� ��� �����, ��������. �������, �� �� � �����.";
				Link.l1.go = "exit_WhisperTownbattle";
		break;
		
		case "exit_WhisperTownbattle":
			NextDiag.CurrentNode = NextDiag.TempNode;
			WhisperPirateTownBattleMortality();
			//AddDialogExitQuest("MainHeroFightModeOn");	
			DialogExit_Self();
		break;
		case "exit_WhisperIncq":
			NextDiag.CurrentNode = NextDiag.TempNode;	
			DialogExit_Self();
			DoQuestFunctionDelay("WhisperLine_WhisperHits_3", 3.00);
		break;
		case "exit_WhisperAddWidow":
			NextDiag.CurrentNode = NextDiag.TempNode;	
			DialogExit_Self();
			
			mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
			mc.Ship.name="������ �����";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(mc);
			
            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
		break;
		case "Exit_incq":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperLine_Inquisition", 2.0);
			WaitDate("", 0, 0, 3, 2, 30);
			DialogExit_Self();
		break;
		case "Exit_Special":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
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
			//����� ������ �� ������������
			if (CheckAttribute(pchar, "questTemp.HellSpawn.Rebirth"))
			{
				dialog.Text = "(� ������ �� ����������� ����������� �� �������� ������ ������ � �����-�� �������, � ����� ������� �� �������� ����������)\n�������, ����� ������������, � ������ ������ ����� � �������� ����� ���� �����.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.HellSpawn.Rebirth");
				Link.l1 = "(��������� ������)";
				Link.l1.go = "HellSpawn_Ritual";
				Link.l2 = "���, ���� ������ ���������� ��� ������� �����.";
				Link.l2.go = "exit";
			}
			//����� �� ������
			if (CheckAttribute(pchar, "questTemp.Sharp.Entered_Shore"))
			{
				dialog.Text = "���� ������ ���������� �� �����, ��������� ������ ���� ���-�� ����������.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Sharp.Entered_Shore");
				Link.l1 = "����� �������� ����.";
				Link.l1.go = "Exit_Special";
			}
			//����� �� ���� � �����
			if (CheckAttribute(pchar, "questTemp.SharleMary.Entered_Shore"))
			{
				dialog.Text = "������ ��������, ��� ��� ����� ���... �����... � ���� ������ �������... ���� ������, �� ��� � ������. "+GetSexPhrase("����! ��� ����?!","�����! ��� �����?!")+" �� ����� �� �����, �� ������. '�������' ������� ��� �������� ��� �� � ����. � ������� �� ����!";
				DeleteAttribute(pchar, "questTemp.SharleMary.Entered_Shore");
				Link.l1 = "��� ����� ����� "+GetSexPhrase("����.","�����.");
				Link.l1.go = "Exit_Special";
			}
			if (CheckAttribute(pchar, "questTemp.SharleMary.Death"))
			{
				dialog.Text = "��... "+GetSexPhrase("������ ����...","������ �����...")+" � ���� �� ����� ������ ����.";
				chrDisableReloadToLocation = false;
				DeleteAttribute(pchar, "questTemp.SharleMary.Death");
				Link.l1 = "�� ����, ����� �� ���� ������ ����� ������. ����� �� ����, ��������, ��� ���� ���-�� �����.";
				Link.l1.go = "Exit";
			}
			//����� �� ������
			if (CheckAttribute(pchar, "questTemp.Undead.Leave_Crypt"))
			{
				dialog.Text = "�����... �������... �... ��� �� ����? � ��������, ��� "+GetSexPhrase("������","������")+" �������� ��� �����. ��� ����� �������. � ����� ���. ������. ��� ���� ��������. ��� ��� �����������. � ���, ��� ������. � ���.";
				DeleteAttribute(pchar, "questTemp.Undead.Leave_Crypt");
				Link.l1 = "����� ����������� � ��� ����������� ������, ������ ��� �������� ��� �����.";
				Link.l1.go = "Exit_Special";
			}
			//������� ������
			if (CheckAttribute(pchar, "questTemp.Whisper.Entered_Dungeon"))
			{
				dialog.Text = "���������� ���������. �������, � �� �����. ������ �� ������� ���������. �� ��� 300, � �� � ������. �������, ������ �� ��������� ��� �� ������.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
				if (bBettaTestMode)
                {
			        link.l1 = "BetaTest - ���������� � ������ ����.";
			        link.l1.go = "Whisper_Finish";
					Link.l2 = "(���������� ��������� �� ���������)";
					Link.l2.go = "Whisper_mission_1";

                }
				else
				{
					Link.l1 = "(���������� ��������� �� ���������)";
					Link.l1.go = "Whisper_mission_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Inside_Incquisition"))
			{
				dialog.Text = "���������, ��� �� ������! ��� � ��� '������' ����������� �� ����� ����� ��������. ��, � �� ������ �� ������ �� ���� ������ ������...";
				DeleteAttribute(pchar, "questTemp.Whisper.Inside_Incquisition");
				Link.l1 = "����� ������� � ����� �����, ���� ��������� ��������� �� ���������. ������, �������� ����������� � ����.";
				Link.l1.go = "exit_WhisperIncq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition"))
			{
				dialog.Text = "�������, ����������. �������� ������ �� ������\n����� ������� �������, � ��������� ���� ����� ����� �������. �� ��� �������� ��������� ������-��������, ��� ��������� �������� ������.";
				DeleteAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition");
				Link.l1 = "����� �������� ���� ����� ���.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Near_Chest"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Near_Chest");
				
				dialog.Text = "�������, ���������� � ����. ������ ���� ��������� ������.";
				Log_Info("�� ����� ��������� ����������� ������.");
				Link.l1 = "...";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.HoldMonologue"))
			{
				string sTemp = ""
				DeleteAttribute(pchar, "questTemp.Whisper.HoldMonologue");
				if (CheckAttribute(pchar, "Whisper.BonusEnergy"))
				{
					//DeleteAttribute(pchar, "Whisper.BonusEnergy");
					sTemp = "\n(�� � �������� �������� �������� ������� �� �������, ��� �������� �������� ���� ������ ������. ������������ ������� ��������� �� "+MOD_SKILL_ENEMY_RATE+".)"
				}
				dialog.Text = "���������! �� ������� ����, ��� ���� �������� � �������, � ������ ������� ���������� � ��������� ������ �� ����� ����� ������ � ����� ���� ������� �����������. � ������� � ������ � ����, � � ��������� ��� ���� ��������� ������� �����."+sTemp;
				pchar.Whisper.BonusEnergy = true;
				Link.l1 = "����� ���������. � �������� �� �������, ���� ��� ������.";
				Link.l1.go = "exit_incq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.GetHat"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.GetHat");
				dialog.Text = "��� ����! ���� ������� ������!\n������ ��������, �� � ����������� ���� �������, � ������ ������ ��� ��� ������� ������.";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				//Pchar.model="PGG_Whisper_0";
				//pchar.Whisper.HatEnabled = true;
				//TakeNItems(PChar, "hatWhisper", 1);
				//EquipCharacterByItem(pchar, "hatWhisper");
				
				Link.l1 = "";
				Link.l1.go = "WhisperTownbattle_1";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.AfterTownBattle"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.AfterTownBattle");
				dialog.Text = "������, �� ��������. ����, ��� ������� ����� �������\n����������� �������, ��� ��� ��� �������� ���� �������. ����� ���������� ������� �� ����, ���� ������� ��������� ����� ��������� ���� � ����� ������ � �������������.";
				Link.l1 = "����� ����� �����.";
				Link.l1.go = "exit_WhisperAddWidow";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_Port";
				PChar.quest.WhisperPirateTownBattle.function = "WhisperMeetCrew";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.SmugPatrol"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.SmugPatrol");
				dialog.Text = "��� � �����! ������� �� ���� ������� �������, ���� ������ ��� ����� �� ��� �������.";
				Link.l1 = "����� ��������� �� ������, ���� ��� ������� �� ��������.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Portman_Deck"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Portman_Deck");
				dialog.Text = "�� �����, ��� � ����� ���-�� �������� ������� �� ������, � � ����� ���� �� ������.";
				Link.l1 = "�������� ������ ���� ����� - ����� �� �������.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.KilledPortman"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.KilledPortman");
				AddQuestRecord("WhisperChardQuest", "7");
				pchar.Whisper.FoundPortmanJournal = true;
				dialog.Text = "��... � ������� ���� �����-�� ����. �� �����, ��� ���� ��������� � ��.";
				Link.l1 = "����� ������� ��� �����.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.EngRevenge"))
			{
				AddQuestRecord("WhisperChardQuest", "9");
				CloseQuestHeader("WhisperChardQuest");
				DeleteAttribute(pchar, "questTemp.Whisper.EngRevenge");
				dialog.Text = "������, ������ �������� ��������� ��������. � ��� ���� �� ��������� �������.";
				Link.l1 = "����� ��������� � ������.";
				Link.l1.go = "exit";
			}
			//������� ������
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
		if(!bDisableMapEnter && !CheckAttribute(pchar,"GenQuest.CannotWait") && CheckSaveGameEnabled() == true) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
	    {
				if(PChar.Dozor != "0" && PChar.Dozor != "END")
				{
					if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
					{
							link.l4 = "������� ������� ���������.";
							link.l4.go = "Dozor_MekaKhrom";
					}
				}
		}
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
				if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
				{
// ����� ���������� by xxxZohanxxx -->					
					link.l3 = "������� �� ���...";
					link.l3.go = "Cabin_PersonSelect";
// <-- ����� ���������� by xxxZohanxxx	
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
	        if(!bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait") && !CheckAttribute(pchar,"ContraInterruptWaiting")) // 21.03.09 Warship fix �� ����� ������� ����� �������� ������
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
			if (pchar.location == Get_My_Cabin())
				{
				Link.l11 = "������������ ��� �������������.";
				Link.l11.go = "autofood";
				if(CheckAttribute(pchar,"autofood"))
				{
					Link.l11 = "���������� �������������� ������������� ���.";
					Link.l11.go = "autofood_stop";
				}
			}
			if(startHeroType == 2)
			{
				if(CheckCharacterItem(pchar,"hatWhisper"))
				{
					if (!CheckAttribute(pchar,"Whisper.Equipped"))
					{
						Link.lWhisperHat = "���������� ������ �����.";
						Link.lWhisperHat.go = "WhisperHatUnequip";
					}
					else
					{
						Link.lWhisperHat = "������ �����.";
						Link.lWhisperHat.go = "WhisperHatEquip";
					}
				}
				if(CheckCharacterItem(pchar,"glasses"))
				{
					if (IsEquipCharacterByItem(pchar, "glasses"))
					{
						Link.lWhisperGlasses = "���������� ������ ����.";
						Link.lWhisperGlasses.go = "WhisperGlassesUnequip";
					}
					else
					{
						Link.lWhisperGlasses = "������ ����.";
						Link.lWhisperGlasses.go = "WhisperGlassesEquip";
					}
				}
				Link.lWhisperPortrait = "������� �������.";
				Link.lWhisperPortrait.go = "WhisperPortrait";
			}
			if (bBettaTestMode)
			{
				Link.l12 = "���������� ����� �� ���������� ����� (������ ���� �������� float)";
				Link.l12.go = "WorldmapTime";
			}
			
			Link.lSmugglingFlag = "�� ����� ������������� ������, ������������� ������ ���� �� ���������, � ������ ��������� �������.";
			Link.lSmugglingFlag.go = "SmugglingFlag";
			if (CheckAttribute(pchar, "SmugglingFlag"))
			{
				Link.lSmugglingFlag = "��������� �������������� ����� ����� �� ����� ������������� ������.";
				Link.lSmugglingFlag.go = "SmugglingFlag";
			}
			
			Link.l14 = RandPhraseSimple("�� ������. ��� �������.", "�������. ���� ����.");
			Link.l14.go = "exit";
		break;
		
		case "SmugglingFlag":
			if (CheckAttribute(pchar, "SmugglingFlag")) DeleteAttribute(pchar, "SmugglingFlag");
			else pchar.SmugglingFlag = true;
			Dialog.Text = "������.";
			Link.l12 = "� ���� ���������.";
			Link.l12.go = "exit";
		break;
// ����� ���������� by xxxZohanxxx -->
		case "Cabin_PersonSelect":
				Dialog.Text = "���� ������?";
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l1 = "����������.";
    				link.l1.go = "Cabin_CompanionSelect";
				}	
				if (!bDisableMapEnter)
				{
					if (sti(pchar.Fellows.Passengers.navigator) != -1 || sti(pchar.Fellows.Passengers.boatswain) != -1 || sti(pchar.Fellows.Passengers.cannoner) != -1 || sti(pchar.Fellows.Passengers.doctor) != -1 || sti(pchar.Fellows.Passengers.treasurer) != -1 || sti(pchar.Fellows.Passengers.carpenter) != -1)
					{
					link.l2 = "�������.";
    				link.l2.go = "Cabin_OfficerSelect";	
					}					
				}
				if (!bDisableMapEnter)
				{				
					link.l3 = "���������.";
    				link.l3.go = "Cabin_PassengerSelect";	
				}	
			link.l4 = "� ������ ���.";
			link.l4.go = "exit";				
		break;
// <-- ����� ���������� by xxxZohanxxx			
		
		case "WorldmapTime":
			Dialog.Text = "�������� float ����� ������� x.x, ���������� �� ����� 12.0, ����� �������� ���� ���� ��� ��������� ��������� �������.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "WorldmapTime_Change";	
		break;
		
		case "WorldmapTime_Change":
			if (stf(GetStrSmallRegister(dialogEditStrings[1])) > 0.0 && stf(GetStrSmallRegister(dialogEditStrings[1])) < 12.1) pchar.wmtimechange = stf(GetStrSmallRegister(dialogEditStrings[1]));
			else pchar.wmtimechange = 0.5;
			if (stf(pchar.wmtimechange) != 0.5) Dialog.Text = "����������� �������� ���������� ����� "+pchar.wmtimechange+".";
			else Dialog.Text = "����������� ����������� �������� � 0.5.";
			worldMap.date.hourPerSec = stf(pchar.wmtimechange);
			Link.l1 = "�������.";
			Link.l1.go = "exit";	
		break;
		case "HellSpawn_Ritual"://������������
			Dialog.Text = "(�� ���������� ���� ������� ������).";
			pchar.Ritual.ModelChanged = false;
			if (pchar.HeroModel == "PGG_Skeletcap_0,PGG_Skeletcap_1,PGG_Skeletcap_2,PGG_Skeletcap_3,PGG_Skeletcap_4,PGG_Skeletcap_5")
			{//������� ������
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_Tich_0";
				pchar.HeroModel  = "PGG_Tich_0,PGG_Tich_1,PGG_Tich_2,PGG_Tich_3,PGG_Tich_4,PGG_Tich_5";
				pchar.Ritual.ModelChanged = true;
			}
			if (pchar.HeroModel == "PGG_Ghost_0,PGG_Ghost_1,PGG_Ghost_2,PGG_Ghost_3,PGG_Ghost_4,PGG_Ghost_5")
			{//������� ��������
				pchar.sex = "woman";
				pchar.animation = "Jessika";
				pchar.model = "PGG_MaryBred_0";
				pchar.HeroModel  = "PGG_MaryBred_0,PGG_MaryBred_1,PGG_MaryBred_2,PGG_MaryBred_3,PGG_MaryBred_4,PGG_MaryBred_5";
				pchar.Ritual.ModelChanged = true;
			}
			if (pchar.HeroModel == "PGG_Meriman_2")
			{//�������
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_WillTerner_5";
				pchar.HeroModel  = "PGG_WillTerner_5";
				pchar.Ritual.ModelChanged = true;
			}
			if (pchar.HeroModel == "PGG_Giant_0,PGG_Giant_1,PGG_Giant_2,PGG_Giant_3,PGG_Giant_4,PGG_Giant_5" )
			{//������
				pchar.Ritual.ModelChanged = true;
			}
			if (pchar.Ritual.ModelChanged == false)
			{//����� �� �������������
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_Pat_0";
				pchar.HeroModel  = "PGG_Pat_0,PGG_Pat_1,PGG_Pat_2,PGG_Pat_3,PGG_Pat_4,PGG_Pat_5,PGG_Pat_6,PGG_Pat_7,PGG_Pat_8";
			}
			SetNewModelToChar(pchar);
			link.l1 = "���-�� ��� ��������. ����� �� ������.";
			Link.l1.go = "exit";
		break
		
		case "autofood":
			Dialog.Text = "������� �������, �� �������� ������ ���������� �������, ������ ��� ������ ������������ ��� (10-90).";
			//PChar.autofood_use
			link.l1 = "";
			Link.l1.edit = 3;
			Link.l1.go = "autofood_percentage";
		break
		
		case "autofood_stop":
			//DoQuestReloadToLocation(pchar.location, "reload", "LAi_FindNearestFreeLocator("reload", locx, locy, locz)", "");
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
						Dialog.Text = "��-�-��, � �� ���������"+ GetSexPhrase("��","��")+". ��� �� ������! ����� �� ����������!!! ���� ������ ������, � �� ����� ������� ������ �����...";
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

// ����� ���������� by xxxZohanxxx -->			
		case "Cabin_OfficerSelect":
			Dialog.Text = "���� �� �������� �������?";
			if (sti(pchar.Fellows.Passengers.navigator) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
				if (chr.location != Get_My_Cabin())
				{	
				link.l1 = "������� " + GetFullName(chr) + ".";
				link.l1.go = "Cabin_navigator_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.boatswain) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
				if (chr.location != Get_My_Cabin())
				{
				link.l2 = "������ " + GetFullName(chr) + ".";
				link.l2.go = "Cabin_boatswain_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.cannoner) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
				if (chr.location != Get_My_Cabin())
				{				
				link.l3 = "������� " + GetFullName(chr) + ".";
				link.l3.go = "Cabin_cannoner_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.doctor) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
				if (chr.location != Get_My_Cabin())
				{				
				link.l4 = "���� " + GetFullName(chr) + ".";
				link.l4.go = "Cabin_doctor_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.treasurer) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
				if (chr.location != Get_My_Cabin())
				{				
				link.l5 = "�������� " + GetFullName(chr) + ".";
				link.l5.go = "Cabin_treasurer_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.carpenter) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
				if (chr.location != Get_My_Cabin())
				{				
				link.l6 = "������� " + GetFullName(chr) + ".";
				link.l6.go = "Cabin_carpenter_Talk";
				}
			}			
			link.l7 = "� ������ ���.";
			link.l7.go = "exit";
			break;				
			
		case "Cabin_PassengerSelect":
			Dialog.Text = "���� �� ���������� �������?";
			for (i = 0; i < GetPassengersQuantity(PChar); i++)
			{
				chr = GetCharacter(GetPassenger(PChar,i));
					if (HasSubStr(chr.id,"ShipWreckSailor"))
					{
						LAi_SetCitizenType(chr);
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
						continue;
					}
					if (!CheckAttribute(chr,"prisoned") && !IsOfficer(chr) && GetRemovable(chr) && chr.location != Get_My_Cabin() && !CheckAttribute(chr, "isfree")) // ����� � ������ �� �������� ���������, ������� � ��������
					{
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
					}
			}
			link.l99 = "� ������ ���.";
			link.l99.go = "exit";
			break;	

		case "Cabin_navigator_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_boatswain_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;			
		case "Cabin_cannoner_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;				
		case "Cabin_doctor_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;			
		case "Cabin_treasurer_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;		
		case "Cabin_carpenter_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;	
		
		case "Cabin_Passenger_Talk":
			i = sti(PChar.GenQuest.CabinPassengerNum);
			chr = GetCharacter(GetPassenger(PChar,i));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
// <-- ����� ���������� by xxxZohanxxx				
			
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
			Link.l2 = "� ���������"+ GetSexPhrase("","�")+".";
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
		
		// ������� ������
		case "Whisper_mission":
			dialog.Text = "���������� ���������. �������, � �� �����. ������ �� ������� ��������� - �� ��� 300, �� ������. �������, ������ �� ���������, ���� � �����.";
			Link.l1 = "(���������� ��������� �� ���������)";
			Link.l1.go = "Whisper_mission_1";
		break;		
		case "Whisper_mission_1":
			dialog.Text = "'������� ������, ���� ������������ ���������� Omnitech! �� �������, ��� �� ������ � ����� ����, � ����� ���������� ���� ���� ������. ���� � ���, ��� ���������� ����� ������� - ��������� ����������� ������. ��� ������� ����������, � ������ ����� ��� ����� �������� ���� ����� ������������. � ������ ������ ��� � ��������� � ����� �����.'";
			Link.l1.go = "Whisper_mission_2";
		break;
		case "Whisper_mission_2":
			dialog.Text = "'�� ������� ���� ���������� ����������� ��������� �������, ��� ���������� ������ ����������. �� ������� ���� ������� ������ �����, �� ��� ���� ��� �� ������ ����� ������� �������. ������ ����� ���������, �� �� ����� �� �������. � ��� ���� ����������, ��� �� ���� ��� ������� ��������� ������. ������, ��� �� ��� �������, ���� ���������� �� ��� ����. � ��������������, ���������� ����� �������������� � ����� ������!'";
			Link.l1 = "��� �, ���������...";
			DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
			//AddDialogExitQuest("MainHeroFightModeOn");	
			Link.l1.go = "Exit_Special";
		break;
		case "Whisper_Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			Pchar.BaseNation = FRANCE;
			Flag_FRANCE();
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.DisFastTravel = false;
			pchar.Whisper.NanoCostume = true;
			pchar.questTemp.WhisperLine = false;
			pchar.Whisper.HatEnabled = false;
			
			TakeNItems(PChar, "hatWhisper", 1);
			TakeNItems(PChar, "glasses", 1);
			
			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);
			
			//initMainCharacterItem();
            mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
			mc.Ship.name="������ �����";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(mc);
			
            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		case "WhisperPortrait":
			dialog.Text = "� ��� �� � ���� ��������� �������?";
			Link.l1 = "������� 1.";	
			Link.l1.go = "portrait1";
			Link.l2 = "������� 2.";	
			Link.l2.go = "portrait2";
			Link.l3 = "������� 3.";	
			Link.l3.go = "portrait3";
			Link.l4 = "������� 4.";	
			Link.l4.go = "portrait4";
			Link.l5 = "������� 5.";	
			Link.l5.go = "portrait5";
			Link.l6 = "������� 6.";	
			Link.l6.go = "portrait6";
			Link.l7 = "������� 7.";	
			Link.l7.go = "portrait7";
			Link.l99 = "�������, ������� �� ��� ����.";	
			Link.l99.go = "Exit";
		break;
		case "portrait1":
			pchar.faceID = "543";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait2":
			pchar.faceID = "543_2";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait3":
			pchar.faceID = "543_3";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait4":
			pchar.faceID = "543_4";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait5":
			pchar.faceID = "543_5";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait6":
			pchar.faceID = "543_6";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "portrait7":
			pchar.faceID = "543_7";
			dialog.Text = "������� �����.";
			Link.l1 = "���, ������ �� �������.";	
			Link.l1.go = "Exit";
		break;
		case "WhisperHatUnequip":
			dialog.Text = "������� �� � �����, � �� ������ ������.";
			ref hatRef = ItemsFromID("hatWhisper");
			string itmGroup = hatRef.groupID;
			RemoveCharacterEquip(pchar, itmGroup);
			ChangeWhisperHeroModel();
			Link.l1 = "� ���� �����������.";	
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperHatEquip":
			dialog.Text = "���, ��� ������� �����.";
			EquipCharacterByItem(pchar, "hatWhisper");
			ChangeWhisperHeroModel();
			Link.l1 = "� ���� �����������.";	
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesUnequip":
			dialog.Text = "���-�� � ���� ��� ����� ����������, �������, ����� ����.";
			ref glassesRef = ItemsFromID("glasses");
			string gItmGroup = glassesRef.groupID;
			RemoveCharacterEquip(pchar, gItmGroup);
			Link.l1 = "� ���� �����������.";	
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesEquip":
			dialog.Text = "���, ��� ������� �����.";
			EquipCharacterByItem(pchar, "glasses");
			Link.l1 = "� ���� �����������.";	
			Link.l1.go = "TalkSelf_Main";
		break;
		case "PriestSurprise":
			dialog.Text = "���� ������ ������... ������ � �� ���� �� ��������� �������. ������� CSP, ������� �������� � ���������, ��� ���� �� ���� ���������, ���-���������� � ������� ��������� ���������. �� ��� ��� ��� ����� ������.";
			Link.l1 = "��, ��� ������ �� ��������� ���, ����� ���� ������.";	
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
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

