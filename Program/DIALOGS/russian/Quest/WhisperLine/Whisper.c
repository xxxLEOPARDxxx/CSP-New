void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	string sTemp;
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "������";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";
		
			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "� ��, ����!";
				link.l1.go = "CS";
			}
			if (npchar.id == "FinalBot")
			{
				dialog.text = "(�� ������� ������ ��������� ����. ��� ����� ����, ��� �������� ���� ��������.)";
				LAi_LocationFightDisable(locLoad, false);
				DeleteAttribute(locLoad, "box1");
				DeleteAttribute(locLoad, "box2");
				DeleteAttribute(locLoad, "box3");
				DeleteAttribute(locLoad, "box4");
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "׸��!";
				link.l1.go = "FB";
			}
			if (npchar.id == "wl_Pirate_Cap")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
				dialog.text = "��� ��� ��� �� ���������� �� ���� ������?! ��������!";
				link.l1 = "��� �? ��� � ���� ������?";
				link.l1.go = "PC";
				npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "���������� � ���� �������, � �����, ��� ���� ������� �� ��� ��� ����\n���� �� �� ������� ���������. ������� ����, ������ - ����� ������� �����, � ���� �� �������� ��������. ��� �����?";
					link.l1 = "�� ��� ����. ����� �� ���� ����������� ����� �������?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}
			
			if (npchar.id == "AntonioDeSouza")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "���� ��, ����� ���������� '���������' ����� ��� "+GetFullName(characterFromId("wl_Pirate_Cap"))+". �������� ���, �����, �� ������ ����� ��� �� �����?";
					link.l1 = "� �� �����.";
					link.l1.go = "ADS";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "�� ���, ������� ���-�� ���������?";
					link.l1 = "��� �� ��� �������, ����. � ���� � ��������� ����, ����� ��������.";
					link.l1.go = "ADS_2";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					dialog.text = "�� ����� ��������� �� ��, ��� � ���� �������, ��� ��� ����� ������� ��������. ��� �������. ��� ���������� ��������? �������!";
					link.l1 = "�����. � �� �����.";
					link.l1.go = "ADS_1_truth";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "��?";
					link.l1 = "��� ������ ������ ��� �������.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "����� �� ������� ��������� ���� ����� ������, �� ������ � ���� �� ������� �������� ������� � ������������. ������ �� �����, � �� ������ ��� ��� ����, ��-��. ������ ���������.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					if(rand(100) < 90)
					{
						pchar.Whisper.IncqGuard_bad = true;
					}
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "���, � ��� � ������ ������� ��������� ��������! ������ ��������?";
					chrDisableReloadToLocation = false;
					link.l1 = "�� ���, ��������� �� ������ ����������.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "�� ��� ������? �� ������ ����� ����������� ����� �� ��������. �� �� ���� �� ���� ��� ������?";
					link.l1 = "׸��! �� ����, �������� ������� ����� �� ��� ����. ��� �� ��� ������ ������?";
					AddMoneyToCharacter(npchar, 777);
					npchar.SaveItemsForDead = true;
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
			{
				dialog.text = "��� ��� �������? ������ ����� � ���� ��� ����� � ������?";
				chrDisableReloadToLocation = true;
				link.l1 = "�� ������ �������� ������ �������, ��� ������� ����� � ���.";
				link.l1.go = "Jack";
				break;
			}
			if (npchar.id == "Wh_Jim")
			{
				dialog.text = "������! �� ����� �����! ������ �� �� ����� ��� �������.";
				link.l1 = "������ ��� ��? ��� ��� ������?";
				link.l1.go = "Jim";
				break;
			}
			if (npchar.id == "W_Lejitos")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);				
					npchar.DontChangeBlade = true; // ������ ����� ��� �������� ������
					
					dialog.text = "������. ��� ��������� �� �����, ��� �����, ��������� � ���� - ������. � � �� ������ �����-�� �����, � - �����. �������, �� ������ ���������� ������ ������� ����, ������ ��� ������ � ��� � ���� ��������!";
					link.l1.go = "exit_cave_entrance_fight";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "� �� � ��� ���������, �� ��-�����, ��������� �� ������������� �������������. � ����, ��� � ����, ���� ���� ����� � ���������?";
					link.l1 = "��, � ������ ������ ���� ������� ������. � ��� �� ��� ������� ����� ����, ��� ������� ����?";
					link.l1.go = "Lejitos";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "W_Chard")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "�� ��� ��� �����? ������� � ���������� ����� � ���� � ����� �� ���������.";
					link.l1 = "�� ���� �� ������ ���� ���� ������ ���� ����, ���� �����������? ��� ���� ����� ������� � '���������� �����' ������� ���� �����.";
					link.l1.go = "meet_chard";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					chrDisableReloadToLocation = false;
					if (CheckAttribute(pchar, "WhisperWonSword"))
					{
						dialog.text = "���������� � �������. � �� ������� �������, ������� ����� ������� ��������. ������� ���� ���. �������� ������, ��� ���� �� ���� �� ����������� ��� ����������. � �������� �� � ����� ������ �������, ������ �� ����� ���������...";
						link.l1 = "(������� ���)";
						link.l1.go = "chard_get_sword";
					}
					else
					{
						dialog.text = "�� ������� ����. �� �� �� �������������, ����� � ������ ����� ���������\n����, ���� ������ ���� ����� �����, � ���� �����, ��� ��� �������. ��� ���, ���� �� �������� ��� � ����� ������, � ���� ��� ������. �� ����� � ��� ���������� ���� ����� � ������� �����.";
						link.l1 = "������ ���� ������ �����?";
						link.l1.go = "chard_discuss_quest";
					}
					npchar.quest.meting = 2;
					break;
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Chinaman_plead":
			npchar.ChinamanAskedSword = true;
			WhisperSelectRandomUsurer();
			LAi_SetOfficerType(NPChar);
			dialog.Text = "�������, � ������ �� ������� ��� �� ������. ������ ���� ���������?";
			Link.l1 = "������� � ���� ��������! �� ������� ������, �� ���� ��� �� �������� ����.";
			Link.l1.go = "Chinaman_plead_1";
		break;
		case "Chinaman_plead_1":
			dialog.Text = "������� �� ������� �����, �������. ����� ��������\n����� ���, ��� � ������� � �������, �  ���� ��� ���. �� �������� ��� �� ����� ����, � ��� - �� ��� ����, � ��� �� ���������� ����� ������ ���. �� ��������, ��������� ���� ��� ����� ��� ����?";
			Link.l1 = "�������, ��������� ��������.";
			Link.l1.go = "Chinaman_plead_2";
		break;
		case "Chinaman_plead_2":
			dialog.Text = "�� ��� ����� � �������, ��� ��� �������� ������. �� ����� �� ����� � ����, � �������� �������� ���� �����. ��� �������� ��� ����������-������������� ������ ���������� �� ������ ������ �����. � ��������� ��� ��� ��� ���� ��� '��� � ����� ��������'. � ��������� ��� ������ � ���� ���� ���� ������ �����, �� � �� ����� ������, ��� ���� ��� ��� ���. ������ ���� ��� ������� ��� ���������. ����� ���, �������, �������� ������� ���!";
			Link.l1 = "���������, ��������? ��� ��� ������?";
			Link.l1.go = "Chinaman_plead_3";
		break;
		case "Chinaman_plead_3":
			sld = characterFromId(pchar.Whisper.UsurerId);
			//Lai_SetStayType(npchar);
			dialog.Text = XI_ConvertString("Colony" + sld.city) +". ��� ����� �������� �� ����.";
			NextDiag.TempNode = "Hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			SetQuestHeader("WhisperChinamanRelic");
			AddQuestRecord("WhisperChinamanRelic", "1");
			AddQuestUserData("WhisperChinamanRelic", "sCity", XI_ConvertString("Colony" + sld.city+ "Gen"));
			Link.l1 = "������, ���� ����� � ���� ������, ������� ����������.";
			Link.l1.go = "exit";
		break;
		case "Chinaman_plead_4":
			dialog.Text = "������� ���, �������. � �����, ��� � ��� ��� ������ ��� ������. �� ���� �������� - �������, ���� ����� ��� �� ������ �����.";
			Link.l1 = "������, ���� ����� � ��� ������, ������� ����������.";
			Link.l1.go = "exit";
		break;
		
		case "chard_waiting_quest_result":
			dialog.Text = "��, ��� ������ �� ������ ����?";
			if (!CheckAttribute(npchar,"DiscussedEsteban"))
			{
				Link.l2 = "� ��� ���� ��������� � ���������? �� ���� ���� �� �������.";
				Link.l2.go = "chard_discuss_esteban"
			}
			if (!CheckAttribute(pchar,"Whisper.FoundPortmanJournal") && !CheckAttribute(pchar,"Whisper.ActiveChardQuest"))
			{
				Link.l1 = "������, �� � ���� �� ����� ��� ���������. � ��������� �������� ����. ������� �������� ����� �� ���...";
				Link.l1.go = "chard_failed"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.FoundPortmanJournal"))
			{
				Link.l1 = "� ����� � �������� ���� ������. �����, ��� ���� ����� �� ������������ ���� ������.";
				Link.l1.go = "chard_check_journal"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.BetrayChard"))
			{
				Link.l1 = "��� �� �����-�� ����������� ���� �����. ������ �������, �� � ���������� � ��� ��������. �� ��������� ������� �� ����������� ����� ������.";
				Link.l1.go = "chard_betrayed"
				break;
			}
			Link.l1 = "���� ��� �����.";
			Link.l1.go = "exit";
			
		break;
		case "chard_check_journal":
			Log_Info("�� ������ ������");
			PlaySound("interface\important_item.wav");
			dialog.Text = "���������... ����� ���� ��� �����������. ��� ����������� �����. ��������� �����. ������ ���� ��������.";
			Link.l1 = "� ������� �����.";
			Link.l1.go = "chard_check_journal_1";
		break;
		case "chard_check_journal_1":
			dialog.Text = "�� ��������� ���? �����, ������ ������� ���� �� �������.";
			Link.l1 = "...";
			Link.l1.go = "chard_check_journal_2";
		break;
		case "chard_check_journal_2":
			chrDisableReloadToLocation = true;
			LAi_Fade("", "");
			WaitDate("",0,0,0,12,3);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			NextDiag.TempNode = "chard_check_journal_after";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "chard_check_journal_after":
			AddQuestRecord("WhisperChardQuest", "8");
			chrDisableReloadToLocation = false;
			dialog.Text = "���� � ��������� �����, ���� ��������� �� ��������. ����� ������ ����� ����� ��� �������� ����.";
			Link.l1 = "����� �� ����� �������. ������ ���� ����.";
			npchar.Ship.Type = GenerateShipExt(SHIP_PDN, true, npchar);
			npchar.Ship.name = "������� �����";
			SetBaseShipData(npchar);
			npchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCharacterGoods(npchar,GOOD_FOOD,500);
			SetCharacterGoods(npchar,GOOD_BALLS,500);
			SetCharacterGoods(npchar,GOOD_GRAPES,500);
			SetCharacterGoods(npchar,GOOD_KNIPPELS,500);
			SetCharacterGoods(npchar,GOOD_BOMBS,500);
			SetCharacterGoods(npchar,GOOD_POWDER,1000);
			SetCharacterGoods(npchar,GOOD_PLANKS,150);
			SetCharacterGoods(npchar,GOOD_SAILCLOTH,150);
			SetCharacterGoods(npchar,GOOD_RUM,200);
			SetCharacterGoods(npchar,GOOD_WEAPON,250);
			SetCharacterGoods(npchar,GOOD_MEDICAMENT,300);
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			Link.l1.go = "exit_chard_setsail";
		break;
		case "exit_chard_setsail":
			NextDiag.TempNode = "chard_on_dominica";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.WhisperChardCompanion = true;
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", pchar.Whisper.EsFriendTown+"_tavern", "", "", "", 7);
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
			
			pchar.quest.WhisperChardShore26.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore26.win_condition.l1.location = "shore26";
			pchar.quest.WhisperChardShore26.function             = "WhisperChardShore";	
			pchar.quest.WhisperChardShore27.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore27.win_condition.l1.location = "shore27";
			pchar.quest.WhisperChardShore27.function             = "WhisperChardShore";	
		break;
		case "chard_on_dominica":
			dialog.Text = "��� �� � �� �����. ���� ������ �����, �������� ����� ����.";
			Link.l1 = "�� �����.";
			Link.l1.go = "chard_follow";
		break;
		case "chard_follow":
			NextDiag.TempNode = "chard_in_cave";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_grot";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;
		case "chard_in_cave":
			if (!CheckAttribute(pchar, "cursed.waitingSkull"))
			{
				pchar.cursed.waitingSkull = true;
				pchar.cursed.lockspawn = true;
			}
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				dialog.Text = "��-��-��! � ���� ������ �� ���! ����� ����� �������. � � ����� ������ �������� ��������. ������� � ������, ����� � ��� ���� ���-�� ���������� ������.";
			}
			else
			{
				Log_Info("�� ������� ���� ���");
				GiveItem2Character(pchar, "blade_whisper");
				EquipCharacterByItem(pchar, "blade_whisper");
				PlaySound("interface\important_item.wav");
				dialog.Text = "��-��-��! � ���� ������ �� ���! ����� ����� �������. � � ����� ������ �������� ��������. � ������, � �� ������, ����� ���� ���� ���-������. �� ������ ��������� � ������, ����� � ��� ���� ���-�� ���������� ������.";
				
			}
			Link.l1 = "�� �� �������! ������, ��� ����� ������ ��� ������ �������. �����, �����...";
			Link.l1.go = "chard_exit_to_cave_entrance";
			
			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 300000;
			_location.box1.items.icollection = 1;
			_location.box1.items.Map_Best = 1;
			_location.box1.items.suit_2 = 1;
			//_location.box1.items.indian11 = 1;
			_location.box1.items.chest = 5;
			_location.box1.items.chest_quest = 2;
			_location.box1.items.jewelry1 = 30+rand(5);
			_location.box1.items.jewelry2 = 30+rand(5);
			_location.box1.items.jewelry3 = 30+rand(5);
			_location.box1.items.jewelry4 = 15+rand(5);
			_location.box1.items.jewelry6 = rand(55);
			_location.box1.items.jewelry7 = rand(70);
			_location.box1.items.jewelry10 = rand(55);
			_location.box1.items.jewelry14 = rand(55);
			_location.box1.items.jewelry15 = rand(8);
			_location.box1.items.jewelry18 = rand(90);
			
		break;
		case "chard_exit_to_cave_entrance":
			chrDisableReloadToLocation = false;
			NextDiag.TempNode = "chard_cave_entrance";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Dominica_caveentrance", "", "", "", 7);
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_caveentrance";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;
		
		case "chard_cave_entrance":
			if (CheckAttribute(pchar, "cursed.lockspawn"))
			{
				DeleteAttribute(pchar, "cursed.waitingSkull");
				DeleteAttribute(pchar, "cursed.lockspawn");

			}
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.WhisperChardCave.function             = "WhisperEngRevengeWarning";
			LocatorReloadEnterDisable("shore26", "boat", false);
			LocatorReloadEnterDisable("shore27", "boat", false);
			WhisperEnglandRevengel();
			pchar.ContraInterruptWaiting = true;
			dialog.Text = "���������, ������� ���� ��� �� ������. ��� ������ ���� �������, ��� ��� ���� �� ����� ���������� � �����. � ����� ��������� ��� ��������� ���. �� �����, ����� �����������?";
			Link.l2 = "��, ��� ���� ���� ����������� �� ����� �����. ����� ����.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				Link.l1 = "������, ��������. �� ������ � ������ ������� �� ����? �������, ������ �� ����� ��� ������ ������.";
				Link.l1.go = "chard_discuss_recruitment";
			}
		break;
		case "chard_discuss_recruitment":
			dialog.Text = "��... � ���� ������ � ����, � ����� ���� � ��������� ������. �� �������� ���� � �����, �� � � ��� �� ��� �����, ��� � ������. ����� ��������. ���� ����� �� ����� ���� ���� �����, �� �� ���������, � � ����� �� ����� ���� �� ���� �����. ������� �� ��, �� ���� �����.";
			Link.l1 = "������. ������.";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = false;
			Link.l1.go = "meet_chard_dice_begin_go";
			Link.l2 = "��, �� ���� � ������� ������, ����� ����� ����������. ����� ����.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
		break;
		case "meet_chard_dice_begin_go":
			chrDisableReloadToLocation = true;
			NextDiag.TempNode = "chard_after_dice_game";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchDiceGame();
			Lai_SetStayType(npchar);
		break;
		case "chard_after_dice_game":
			chrDisableReloadToLocation = false;
			
			if(CheckAttribute(pchar, "WhisperWonChard"))
			{
				LAi_SetImmortal(NPChar, false);
				SetCharacterRemovable(npchar, true);
				dialog.Text = "��, ����� ���� �� ��������. ��� � ����, � ������� ���� ���� �����.";
				Link.l1 = "��� � �������. ������ � �������. �����... �����.";
				Link.l1.go = "chard_hired";
			}
			else
			{
				dialog.Text = "������, ���� ������ ���������. ��� �� ����������, ������ � ��� �� ������.";
				Link.l1 = "�� �����. ����� ����� ����.";
				Link.l1.go = "chard_exit_to_cave_entrance_1";
			}
		break;
		case "chard_exit_to_cave_entrance_1":
			dialog.Text = "� ����. ����� ������ ��� � ������! ��� ���� ������� �� �����, �� ���� ����.";
			npchar.LifeDay = 0;
			TakeNItems(pchar, "indian11", 1);
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			Link.l1 = "�������! ������.";
			Link.l1.go = "chard_exit_to_cave_entrance_2";
		break;
		case "chard_hired":
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
			SetCharacterPerk(npchar, "Adventurer");
			NPChar.Payment = true;
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.HalfImmortal = true;  // ��������
			npchar.loyality = MAX_LOYALITY;
			//AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			npchar.Dialog.CurrentNode = "hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
		break;
		case "chard_exit_to_cave_entrance_2":
			chrDisableReloadToLocation = false;
			//NextDiag.TempNode = "chard_cave_entrance";
			//NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
		break;
		
		case "chard_failed":
			dialog.Text = "��, ��� ���������� ��� ������ ������, ������ �� ������ ���� ��������. ���� � ���� ����...";
			LAi_SetImmortal(NPChar, true);
			npchar.LifeDay = 0;
			Link.l1 = "�� �� ����� �� ���, ����� ���.";
			Link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_betrayed":
			NPChar.rank = 77;
			LAi_SetHP(NPChar, 777.0, 777.0);
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				NPChar.money = 77777;
			}
			else
			{
				NPChar.money = 277777;
			}
			chrDisableReloadToLocation = true;
			pchar.Whisper.BetrayChardKill = true;
			TakeNItems(npchar, "bible", 1);
			npchar.SaveItemsForDead = true;
			dialog.Text = "��, ��� ���������� ��� ������ ������, ������ �� ������ ���� ��������\n���������, ���� ������� ��������� �����. �������� ������!";
			Link.l1 = "� ����, ��� ���� ��� ����� �� ����, ��� � �����. ���� �� ����.";
			Link.l1.go = "chard_fight";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_fight":
			Group_FindOrCreateGroup("EnemyFight");
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "chard_discuss_esteban":
			npchar.DiscussedEsteban = true;
			dialog.Text = "�� � ��� ���� ������� ���������, ���� ������ ��� ��� ����� ������� ����� ���� �������� ���������. ��� ������� ������� � ������� ����, �� ������ �� ��������������. �� ��� ���� ����� ��� �����. � ����� ������ ����� ����� ������� � ���� �� ������, � � ����������� �� ���� �������\n�� ������ ����� � ��� ��� �� ��������, �� ������� ����� ����������� � ������ ��������� ��������� ������� � �����. ������, ��� �� ���� ������ �� �������� ��� ���� ����� �����, ��� ��� � ������� ��� �������� ������. � ����� �� ������� ��� ������ ������� ����� �����. �� ������ ������, � �� ���� ������ �������� ��� � �������. �� ��� �� ��������� ���� �����, ��� �� ����-�� ������, ��� ����� ���, ��� ��� ����� �����, ��� ����� ������� ���� ��� �������, ���� �� ������� �����, ��� ������ �� ����������� ��� ������������. � � ����� �� ������ ��� ����� �� ���������� ������, ����� �������� ������ � ������ ������� ��������� ����. � ������������� ����� ����� � ����������, � ������ �� ���.\n� �� ����� ��� ���������, �� ����� ��������� �� ����. � ����� �� ������������, ��� �� ����� ��������� ����������� �� ���� ���� �� ��������. � ������ ���� ��� � ��� ���� ������, �� ������ �������� ������� ���� �������� � ���� ���������� �����.";
			Link.l1 = "�� �������� �����-�� ������. ��� ���?";
			Link.l1.go = "chard_discuss_esteban_1";
			//Link.l1 = "�� �� ����������� ������ ��� �� ������ ������ �����?";
			//Link.l1.go = "chard_discuss_esteban_1";
		break;
		case "chard_discuss_esteban_1":
			dialog.Text = "��� �� ����, ��� ���������� ������ �������� �����������. � �� ������ �� ��������� �� ���� ������-�� ���� � ��������, ��� ����� �� ��� ��������.";
			Link.l1 = "��� ��������� ��� ����������?";
			Link.l1.go = "chard_discuss_esteban_2";
		break;
		case "chard_discuss_esteban_2":
			dialog.Text = "������������� ��������, �� ������� ���������� ���� ���������� ������ � ��������. � ��� ��� ���� ������� ��������� ��������� � ������ �������.";
			Link.l1 = "���������, ��� �� ��� ������ �������!";
			Link.l1.go = "chard_discuss_esteban_3";
		break;
		case "chard_discuss_esteban_3":
			dialog.Text = "����?";
			Link.l1 = "������. ���� ���� ���� ���� ����������?";
			Link.l1.go = "chard_discuss_esteban_4";
		break;
		case "chard_discuss_esteban_4":
			dialog.Text = "������� �� ����, ����� ����� ������ � ��� ����� ��� �������� � �������� ��� ������� ��������� �� �������, �� �� ����. �� ������ ���������. �� ����������, �� �������� ��������� ��� �� ������. � ����� ���� �������, ��� ��� ��� ������� �� �����, ���� �� �� ������� � ���� ��������. ��������, �� �������� ���� ����� ����������� ����� �� ��������.";
			Link.l1 = "����, ����� �����, ��, �� ������� ����, � ���� ��������� �������. ������� �� ����������.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_esteban_old":
			dialog.Text = "� ���� � ��� ���� ���� �����, � �� ���� �� ��� ��������. �� � �� ������� ���� ������� ���� ����� ������ ����, ��� ����� ��� ����� �����������. � ��� �������� �������� �������� - ������ ������. �� ���������� � ���� �� ���� � �� ����.";
			Link.l1 = "����.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_quest":
			dialog.Text = "������� � ������� �� ��������. ���, � ����������, � ����� ���-�� ����, ������ ������ ��������������, � ����� ������. �� � �������� ������� � �� ������� ��������, �� ����� ������ ���� ���� �����, ����� �� ����������� ���������. ������ ����, ��� ��� ��� ���� �������� �� ������ ��� �����-�� ������ �������� �����, � ��� �� ���� ������ ���������������. �� ����������� ���������� ������������ ����, ������������ �� ���� �����. ��� � ����� �����, ��� ��� ����. ��� � �������� ������������ ��������� ����, ���� ��� ���������\n� ���� ������� �������� ���������� � ����� ���� ������� ��������, �������� �������� ������ ��������, ���� ����������� ���������� ��� ���������������. ��� ������ �� ������, ����� ������� �����������. ��� ��������� ������� ����� ��� �� ������� ������ �����. ����� � ����� ���������� � ������ ������ ��������, �� �� ��� ������� ����, ��� ������� ������, �� �� ��� ��������. �������� ��� ������ �������, �� � ����� � ����� ������ �� ������� ����� ���� �����, �� � ��� �� ������ ������ � �����, ��� ���� ����� ����� �� ������ � ��������. ";
			Link.l1 = "�� ����� ����� ��� ���������, �� ��� � �� ������� � ����. � ���� �����?";
			Link.l1.go = "chard_discuss_quest_1";
		break;
		case "chard_discuss_quest_1":
			//NextDiag.TempNode = "chard_discuss_quest_1";
			dialog.Text = "��� �����, ����� �� �������� ����� �������� � ������ ����������� ����������, ���� ����� � ���� �������.";
			Link.l1 = "������ �� �� ��� ����� �� ��������?";
			Link.l1.go = "chard_discuss_quest_2";
		break;
		case "chard_discuss_quest_2":
			dialog.Text = "������ ��, � ���� �������� ��������� ���� �������� ����, � � �������� - ��������� ��������. �����, ���� ���� ����� �� ���, �� ���� ������� ������ ������ ����� ���������. �� ���� 'ϸ�' ��� ������� �� �������.";
			Link.l1 = "������ ������ ������ ��������? ���-�� � ����������.";
			Link.l1.go = "chard_discuss_quest_3";
		break;
		case "chard_discuss_quest_3":
			dialog.Text = "�� �������� ������ ������� �������� �� '���'. ���� ������ ����� �� �������� ��������, �� ������ ���� ����������� ��. �� ���� ��� �� ������������ � ����� �����, ������ ��������� ��������.";
			Link.l1 = "�������? ��� ���?";
			Link.l1.go = "chard_discuss_quest_4";
			Link.l2 = "�����, � �������. ��� ������ ������ ����� �����������?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_4":
			dialog.Text = "�� ��� ��, ������-�������, ������ �� ���� ����������. � ���� �� �������� ���� ����� ����. ������ �������� ��� ���� �������. ���� 'ϸ�' � �����, � ������, ������� ������ �������, ��� ��� ����� ��������. ����� �� ��� ������� ������������ � ����� ��������.";
			Link.l2 = "�����, � �������. ��� ������ ������ ����� �����������?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_5":
			NextDiag.TempNode = "chard_waiting_quest_result";
			//SaveCurrentNpcQuestDateParam(pchar,"Whisper.LastSeenPortman");
			pchar.Whisper.ActiveChardQuest = true;
			AddQuestRecord("WhisperChardQuest", "2");
			dialog.Text = "� ��������� ��� � ��� ����� � ������� �����, �� ����� �� ������� �����������, � �� �����. � �����, �� ��� ������� ������� ��� �����. ����������� � �������� �����������, ��������� ���-�� ��� ������\n��� ���������� - ����������� ����. � ������� ���������� � ������ ������ ����� �����.";
			Link.l2 = "������, ������.";
			Link.l2.go = "exit";
		break;
		case "chard_get_sword":
			Log_Info("�� ������� ���� ���");
			GiveItem2Character(pchar, "blade_whisper");
			EquipCharacterByItem(pchar, "blade_whisper");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			DeleteAttribute(npchar, "items");
			DeleteAttribute(npchar, "equip");
			GiveItem2Character(npchar, "pistol4");
			EquipCharacterbyItem(npchar, "pistol4");
			GiveItem2Character(npchar, "blade39");
			EquipCharacterByItem(npchar, "blade39");
			dialog.Text = "��� �� �� �����, � ������� �������� ������, �� ���������� �� ������ ��� � ����� ������?";
			Link.l1 = "������ ���� ������ �����?";
			Link.l1.go = "chard_discuss_quest";
		break;
		case "chard_not_played":
			dialog.Text = "����� ��? ���, �������� ������� �� ����?";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "�����, �������� �����.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "���.";
			Link.l2.go = "exit";
		break;
		case "meet_chard":
			NextDiag.TempNode = "chard_not_played";
			dialog.Text = "� ���� ����? ������, �� ��������. �������� � ��� ������� ����... �� ��� ���������� �����?";
			Link.l1 = "������. ������� ������� 'ϸ� �����'.";
			Link.l1.go = "meet_chard_1";
		break;
		case "meet_chard_1":
			dialog.Text = "�������? ������, � ���� ��������� �������?";
			Link.l1 = "���������� ����� � ������. ��� �� ���� �������� ������.";
			Link.l1.go = "meet_chard_2";
			Link.l2 = "� ���������� ����� �������.";
			Link.l2.go = "meet_chard_3";
		break;
		case "meet_chard_2":
			dialog.Text = "� ���� � ������� ���, ��� � ���� ������ ���-�� ��������. ��� ���� �������. ";
			Link.l1 = "(��� ������ ���������� �������� ������� ������, ��� ����� �� ����� � ����������.) ������-��... ��� �� ��� ���! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_3":
			dialog.Text = "� ���, ��� �� �������, �� ���������\n�� ��� �� ������ �������, �� ������ ������� ��� ����?";
			Link.l1 = "(��� ������ ���������� �������� ������� ������, ��� ����� �� ����� � ����������.) ������-��... ��� �� ��� ���! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_4":
			dialog.Text = "������ �� ����. ���� ������ ���, � ������ ������� ��� � ����� � ��������\n�... �������, � �����, ��� ��, ������. ������� ���� ������� ��� �����, � ������� ������� ������� � ���. ����� ������� ������� �������������, � ����� ����. ������ �� ������ ���, ��� ��������� ����.";
			Link.l1 = "��� ������, � ����� ���� �����, � ������� �� ����� ����������. � ������ ������� ���� ���! ";
			Link.l1.go = "meet_chard_5";
		break;
		case "meet_chard_5":
			dialog.Text = "���, ���� �������! ������ ��� � ������ ���� �� ���\n�� ��� ��, ���� ��� ��� �� ����� �� �����, ������� �� �����, � � ����� ����� ��������� ������. ������ ���? ����� ������� � �����. ��������� - �� ����. ������� � - ���������. ������... ������ �����.";
			Link.l1 = "�������? �� ���, ������� ��������?";
			Link.l1.go = "meet_chard_6";
			if (sti(pchar.money) >= 200000)
			{
				Link.l2 = "����, �������� �����.";
				Link.l2.go = "meet_chard_7_cardGame";
			}
			Link.l3 = "����� ���-������ � ������ ���.";
			Link.l3.go = "exit";
		break;
		case "meet_chard_6":
			dialog.Text = "�� ������� ����� � ������ �� ���������. ���� ������, ���� ���� ������.";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "�����, �������� �����.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "����� ���-������ � ������ ���.";
			Link.l2.go = "meet_chard_8";
		break;
		case "meet_chard_8":
			dialog.Text = "�����������, ���� �����������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
		break;
		case "meet_chard_7_cardGame":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.Text = "��� ��� �� ������! ������ �� ���� �����.";
			Link.l1 = "����.";
			Link.l1.go = "meet_chard_Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			int iLa_Puesta = 0;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		break;
		case "meet_chard_Cards_begin_go":
				chrDisableReloadToLocation = true;
                //Diag.CurrentNode = Diag.TempNode;
                DialogExit();
                LaunchCardsGame();
		break;
		
		case "LejitosOff":
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.HalfImmortal = true;  // ��������
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			//LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "LejitosNoOff":
			DialogExit();
			NPChar.lifeday = 0;
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10);
		break;
		case "Lejitos":
			dialog.Text = "� �� ����������. ��� �������� ��� ���� �����-��, �� ��� �� ������� ���������� �����, ���� �������� ��� ��� ����. ���� �����, ��������� � ��������� � ������� �������� �������. ��� ������� ��� ����� �� �������� ���� � ���������� ��� ���� ��� ������������� ����.";
			Link.l1 = "�� ������ ��� ����� ����� ��������?";
			Link.l1.go = "Lejitos_1";
		break;
		case "Lejitos_1":
			dialog.Text = "� ���������, ������� �� ���� ��� ����� �������. ������� � ���������� �� �����, � ����� �������� ����� � ������� - ������ ���� ������� � ������. �� ����� ���� ����������. � ������� �� ��������, �� ����� ���� �� ������\n����� ����� � ������� ���� � ��������, � ��� ���������� �������������� ��������. ��������� ��� � ��� � �����������, ���������� �� ����� �����, ���� ������� ���-�� �� ��������� �������� ���������� � ���������� ��������� ��������, ��� � �������� ����� ��������� ���. ��� � ���� ������� ���� ��� �� ����������, � ��� ���� ������ ����� �� � ���� ������ ������\n� ��� ��� � ��������� �� �������� � ����������� ��������, �� ���� ����� ��� �� ���� �����. ��� ������ �� ������ � �� ��������� ������ ���������, ��� �������� �� ���� �������.";
			Link.l1 = "����� ��� ��-�����, �� ��� �� ������. �� ��� ���� � ����, ��� �� - ��������� �����. �� ������ ����� �� ��� �� ������? ������, ������ � ���� � ������� �� ��������� ������ ��������. ����� ������ � ����������� ������� ��� �������, ��� ������� ������� ���� �� ���� ��������.";
			Link.l1.go = "Lejitos_2";
			Link.l2 = "�� �����, ��� ��� � ����� �� ����, ��������. ������.";
			Link.l2.go = "LejitosNoOff";
		break;
		case "Lejitos_2":
			dialog.Text = "�� ������ ��������. ������� ��, � �� �������� �������� ��� ������� ��������� �������� ���� � ���������.";
			Link.l1 = "��� � ������������. ������, ��� ��������, ��� �� ���������� � ��� ������ �� ������. ������� ����� ���-������?";
			Link.l1.go = "Lejitos_3";
		break;
		case "Lejitos_3":
			dialog.Text = "��� �� ����, � ��������� ��������. � ���� ������ � ���� �� ��������, ������ �����, �� ��������. Ÿ ��������� ���������� � ������, ����� ���� � ��������� �������� ����� �������� �������.";
			Link.l1 = "�� �����, ������.";
			Link.l1.go = "LejitosOff";
		break;
		
		case "DeSouzaHunter":
			dialog.Text = "���� ��, ��� ������! ������, �� ����� ����� ��������� ����� ���� ������! ����� ���������� ������ ��� ���� �� ����������, ����� ���������� ������� �� �����, �� ����� �� ������� ��� ��� � ����, ��� ��������� ������� ������!";
			Link.l1 = "�� �����, ��������? � ��� �� �� ���?";
			Link.l1.go = "DeSouzaHunter_1";
		break;
		case "DeSouzaHunter_1":
			AddQuestRecord("WhisperQuestline", "6");
			dialog.Text = "���, �� �������� �������� �� ���� ������ ������ �����? ������, ����� �������� �������, ���� �� �����, ��������, �� �������. �� ��������� � ����� � ��������� ��� ���� ��������� - ����� ��������\n�� ������� ��� ����������� ��� ������������. �� �� ������, �����? � ����� ��� �������� ����, ����������� ����� ������\n�� ��� ���, ���� ������? ��� ������� ������ ��������� ������ � �� ���? ���, ������ ������, � ��� �� ������ �����.";
			Link.l1 = "������ ���������, ��� �� ���� �������!";
			Link.l1.go = "exit_lejitos_speak";
		break;
		case "exit_lejitos_speak":
			DialogExit();
			sld = characterFromID("W_Lejitos");
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;
		case "exit_cave_entrance_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			for (int i = 1; i <= 7; i++)
			{
				sld = characterFromID("DeSouzaHunter"+sti(i));
				LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "Smuggler":
			NextDiag.TempNode = "Smuggler";
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				dialog.Text = "�� ��� ��� �����? ���� ���� ����� ����?";
				Link.l1 = "� ��� � ���� ���� ���� ����� �������� �� ����� "+GetCharacterFullName("Tortuga_trader")+". � �������� �����, ��� ��������������.";
				Link.l1.go = "Whisper_contraband";
				Link.l2 = "������.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "������ ����������, � ������ ���� ������, ������ ����� ��������!";
				Link.l1 = "�����, ������ ������� ��� �� ����.";
				Link.l1.go = "exit";
			}
			
		break;	
		case "Whisper_contraband":
			if(Pchar.Location != Pchar.location.from_sea)
			{
				dialog.Text = "��� �� ����� ���������, �� ������� ���� ���? ��� �� ���� ����� �� ����� ��������?";
				Link.l1 = "������� �����, � ������ ������� ����� ��������� ������.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) >= 100)
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				dialog.Text = "����. ������, �� � �������. ��� ����... �� ���� ���������, ����� �� ��������. ��� ���� ������.";
				AddMoneyToCharacter(PChar, 50000);
				RemoveCharacterGoods(Pchar, GOOD_EBONY, 100);
				Link.l1 = "�������� �����, �������.";
				Link.l1.go = "Whisper_contraband_1";
				
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) < 100 && GetSquadronGoods(Pchar, GOOD_EBONY) > 0)
			{
				dialog.Text = "� ���� �� ������� ������. �����������, ����� �������.";
				Link.l1 = "� ������. ���, ������ ������� � �������.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) == 0)
			{
				dialog.Text = "�����������? � ���� � ����� ������ ��� ������� ������!";
				Link.l1 = "�������, � ��� ����-�� ����������. ������ �� �����, � ������.";
				Link.l1.go = "Whisper_contraband_2";
			}
		break;
		case "Whisper_contraband_1":
			dialog.Text = "������, ���� ��� ��� ���������� ������, ����� ��� ����, � �� "+GetCharacterFullName("Tortuga_trader")+" ���������� ���������� � ��������� ��������. ������ ������ ������������� �� ������ ������� ����� � �������.";
			WhisperRemoveSmugglersFromShore();
			AddQuestRecord("WhisperContraband", "3");
			CloseQuestHeader("WhisperContraband");
			Link.l1 = "������, � ��� ����.";
			Link.l1.go = "exit";
			//pchar.quest.WhisperChinaman.win_condition.l1 = "ExitFromLocation";
			pchar.quest.WhisperChinaman.win_condition.l1 = "EnterToSea";
			pchar.quest.WhisperChinaman.function    = "WhisperChinaman";
			WhisperSmugglingPatrol();
			pchar.ContraInterruptWaiting = true;
			//CaptainComission_GenerateCoastalPatrol();
			
		break;
		case "Whisper_contraband_2":
			dialog.Text = "� ��������� �����, � ��� ����� � ���� ����� ������� �� ���������.";
			Link.l1.go = "exit";
		break;
		
		case "Jim":
			dialog.text = "����� ����, ��� �� ����������� � ������, ����� �� ������� ���� �������� �� ��������. �� ������ � ������ ����. � ���� ��, � ��� �� ������� �������� ����� - ����� ������ ������� ��������, ����� ��������� ������ ���������� ������, ������� �������� ��������� ������������ �� �����. ����� ������� �� �������� �������� ��� � ����� ������� ������. ";
			link.l1 = "������, ��� �������� ���� ��������. � ����� �� ��� ��������� ���������?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "��������.  �� ��� �� ������� '׸���� ������' ������. �� ���� ����� ������ �������� ���� ���� ������, ��������� � �����. � ������� ��� ���������� ��� ��������� ��������� �������, � ������ ���� �� �����-�� ������� ����������� ��������, ���� ������� �������. ���� ��� ����� ��������� - ��� ���� �����������. ";
			link.l1 = "������� ������� �� ��� ������. �������, ����� ��� ���� '�����' - ��������. �� �� ���� ��� ������ �� ����������. � �������� ����� ���������, ������ �� ������� ��, ��� ���������� � ���������� �������.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);
			dialog.text = "������, ���������. ���� �������� ���� �� ����, �� ��� �� ����� ���� ����� �������� ��������� '�����'. ��, ���� ���, �������, �� ������ �����. ������, � ����� ��� ���� ��� ���� ����� ����������, ���� �� � ����� - ���������, ����� ����� ���� ��������������� �� ����\n� ���� �� ������ � ���� ������ - ������� � ��� ������� ������. ��� �������, ��� ��������� ����. �� ����� ���������� ������� ����� ����-�� �� �������, �� ���� ������������ � �� ����, ��� ��� ����� ���� ��������.";
			link.l1 = "������, ������� �� ������. � ��� ��� ��������?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "�� ����� �����, � �����. ������� � ������ � ������� � ������\n� ���. ����, ������� ������� ���� ��������� �� ������ ��������. ������� ����������� �� ���-������ �����������, ������ ��� �� ���� �������. � ��� �� ������� ����� ������� ������, ������ ��������� ���� ���-������.";
			TakeNItems(pchar, "suit_1", 1);
			Log_Info("�� �������� �������");
			PlaySound("interface\important_item.wav");
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			//DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);
			
			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			//AddQuestRecord("WhisperQuestline", "3");
	
			SetQuestsCharacters();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 25);
			for(i=1; i < 5; i++)
			{
				sld = CharacterFromID("Wh_Crew"+sti(i));
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 20);
			}
		break;
		case "Jack":
			dialog.text = "������ ��� ��? ��-��! �� ����, �... ����� ����, �������. �����, ����� ���� ��� ������� � ����������.";
			link.l1 = "��� ���� ��. ��� ��� ��� �����������.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "�� �������� �� ������. ��� ����� � �������, ��� ������ �� ��������� - ������� ������ �� '׸���� �����'. ����, ���� ��� ����������� � ���� ���������. � ����� ������, � �������� ����� �������. �� ������ �������� �� ��� ����� ��� ��������. ���������, �� �� ����.";
			link.l1 = "���� ������ �� ���������� - �� ��� ��� �������, � �������� ���� ������ - �������.";
			link.l1.go = "Jack_2";
		break;
		case "Jack_2":
			dialog.text = "�� ��, �������! �� � ����...";
			link.l1 = "��������.";
			link.l1.go = "Jack_fight";
		break;
		case "Jack_fight":
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			PChar.quest.WhisperJimTalk.win_condition.l1 = "NPC_Death";
			PChar.quest.WhisperJimTalk.win_condition.l1.character = npchar.id;
			pchar.quest.WhisperJimTalk.function = "WhisperJimTalk";
			DialogExit();
		break;
		case "NF":
			dialog.text = "���� � ������������, ���� ���������� ������� �� ���� ��������. ��, �����! �� ��-�����, � ��� ����� ��������� �� � ������.";
			link.l1 = "��� � ��� ������.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "����� �����������. � ����������� ����.";
			link.l1 = "������.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "׸��, � ���� ��� ���� ������, ��� � ��������� ��������! ��� ��� � ���� ���������, ������. ��� �� �� ��������� �� ��������, ���� ������� ���� �� ������� ����� ���������, ���� �� ����� �������� � �������� ������ ������.";
			link.l1 = "� ��� � ����� �� ���������?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "�� ����� � ����� �������, � �������. ��� ������� ������ � ���� �� ������. ����� �� ����� �� �������� ���������. �� ���� �� ������� � ������ ����.";
			link.l1 = "������� �� �����, ���������� �� ������������.";
			link.l1.go = "NF_exit";
		break;
		case "NF_exit":
			Lai_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.Whisper.BuyDocuments = true;
		break;
		case "NF_2_1":
			dialog.text = "�� ���� ��� ��, � � ���������� � ������ ������� � ��������� ������.";
			link.l1 = "...";
			link.l1.go = "NF_2_exit";
		break;
		case "NF_2_exit":
			//Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_CharacterPlaySound(pchar, "People Fight\Player_Man_Shoot_01.wav");
			DoQuestFunctionDelay("WhisperKillNineFingers", 0.7);
			DialogExit();
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.5);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
			link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard_bad":
			dialog.text = "��� �� � �������� ����\n�������� �� ��������, ��� �� ���� ��� �����������? ���� ���, �� �������� ���� ��������. ������ ��, ���� �� ����� �������� ��� ���������� ������� ������, � ��� ����� ��������. ������� � ���� �������� �� ����, ���� ���������� ����������. � ���� ������ ���� ����� ����������� � ��� �������, ����� ��� ������ �� �������� ���������� �� ���� ������\n�����, ���������� ���� � ������ '���������'. ��� ������� �������� '������', ���� ������� ����� ������ �������� ��� � ��������. �����, �� ���������. � �� ������� �������� �������, ����� ����� ����������.";
			link.l1 = "(����� ��������� �� ���)";
			link.l1.go = "IncqGuard_bad_go_to_wheel";
		break;
		case "IncqGuard_bad_go_to_wheel":
			DialogExit();
			LAi_ActorGoToLocator(NPChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", -1);
			LAi_ActorGoToLocator(PChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", 10);
			Npchar.dialog.currentnode = "IncqGuard_bad_wheel";
			//DoQuestFunctionDelay("WhisperLine_IncqGuard_bad_speaks", 5);
		break;
		case "IncqGuard_bad_wheel":
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("IncqGuard_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			dialog.text = "��� � ���� ���������\n���� � ��������� ����� ����������, ���� ������� ������� ��������� � ������, ����� ����, ���������� ���������� ������� �����. ���� ����� ���������� ��������� � ��������� ���� ����. ���� �� ����� ������ �� ������ ������� ������ ��� ����� ������\n���... �� � ���� �� ���������� ������?";
			link.l1 = "������, �� � ��������� ���������� �� ������ �����������. ����������� ������ ��� ��� �����������, ����� � ���� ������ ������ �����. (���� �� ����������, �� ������ ��������� ������������ ��� �������� �� ������)";
			link.l1.go = "IncqGuard_bad_wheel_kill";
		break;
		case "IncqGuard_bad_wheel_kill":
			DialogExit();
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			npchar.SaveItemsForDead = true;
			GiveItem2Character(pchar, "pistol3");
			EquipCharacterByItem(pchar, "pistol3");
			Lai_SetPlayerType(pchar);
			//AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("WhisperLine_WhisperHits", 0.2);
		break;
		case "IncqGuard":
			dialog.text = "׸��, ������ �� �� ���� �������. ���� �� � ����� �������� ���� �� ����� - �� �� ��� �� ����� �� ���� �� ������.";
			link.l1 = "������, ��� � ������ �����������.";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "��� ��-����� ������ �� ��� ��������. ����� �� ������ ������� � ��� ���� �������, �� ������\n� ��� �������, ����� ���� ��� �� �������. ���� �����, �� ������ �� �������? � � ��� �� ����������� � ������ �������.";
			link.l1 = "��� �����-�� �������������� ������? �� ���� ���������, � ����� ����������, ���� �����?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "��� ������� ������. ������� ������������ �����������. � ���� ������� ����� ���� ���, ���� �� �� ������� �����, ��� ����������.";
			link.l1 = "׸��, �� � ������ �������� ��� �������. ����� ����?";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "���� ����� �� �������� � ������. ��������� ������ �������� �� ������, �� ��� ��� ������ ��������� ����� �����, ��� ��� ����� �������������. ���� ������������, ��� ���� � ������� ������� �� ������\n��� ������ ������� �� ����������, �� ������� ��������� � ������ � ������, ��� ��� ������ ���� ���� ����������. �� ��-�����, �� ������������ � ��������, ��� ��� ���� ��������� ����� �����������\n����������� � ��������� ����������, ������-��������. ����� ������� �� ������, ������ ������ �� ������ �����, ����� �������, ��������� ����� � �����. ��� �� ��� ������ �� ������� ������� ������������, ���� �� �� ������� �� ����� � ���� ������ ������ ��������. ����� ��� �� ����� ����������, �� �� �� ��� ���� �� ��� ���������� ������, ��� � ���� ������.";
			link.l1 = "���� �� ����, ����� �� � �����-�� ���� �������������. �� ��������� ������! ���, ������ � ����� ����� ���� ��� �������.";
			link.l1.go = "IncqGuard_4";
			Pchar.BaseNation = SPAIN;
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "�����, � ������.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "�� ��� �������. �� �����, �� �� ������? ������ ��������, ����� ������ ������. �� ����� �� �����.";
			npchar.quest.answer_1 = true;
			link.l1 = "��, ������ ������ �������� � �������.";
			link.l1.go = "IncqGuard_exit";
			link.l2 = "������� ��� ��� ����������, ��� ��� ����� ������.";
			link.l2.go = "IncqGuard_3";
		break;
		case "IncqGuard_exit":
			Lai_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 1500);
			InterfaceStates.Buttons.Save.enable = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
			PChar.quest.WhisperEscape.win_condition.l1 = "locator";
			PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
			PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
			PChar.quest.WhisperEscape.function = "WhisperEscape";
		break;
		case "ADS":
			dialog.text = "������? ������ �����, ��� ��? ����� ���� ���� � ����� �� ������ ���� �������, ������ ��. � ��� �� ������� � ���� ����� "+GetFullName(characterFromId("wl_Pirate_Cap"))+"?";
			link.l1 = "�... ����������� ��������.";
			link.l1.go = "ADS_1_lie";
			
		break;
		case "ADS_1":
			dialog.text = "�� ��������, ��������? � ��� �� ���� � ����� ������ ������������ � ����� �������?";
			link.l1 = "������, ����������� ���� ���� ������������. ����������, �� ������ ���������� � ������� ��������� � ��������� � ���� ����������, ��� ���� ��� ���. � ������ ���, ��� ��� �������� � ������ ���� �����.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_lie":
			dialog.text = "� �������� ����������� �� ���� ������?";
			pchar.Whisper.DeSouzaHits = 0;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_truth":
			dialog.text = "������. ";
			link.l2 = "��������, ��� ����� ������ � ��� ��������, �� � ������ �� ��������. ��������� ����� ������ ����� ������ ����� ����� ��������������, ��� ������ �����. � ��� ��������� �� ����� �������� ����� ���������.";
			link.l2.go = "ADS_1";
		break;
		case "ADS_1_1":
			dialog.text = "���, ������. �� ������� ���� �� ������? � ������� �� ������ � ����������� �� �������. �� �� ��� ��� ����� � '������� ���������' ����������\n�������� � ����. ���� ������� �� ��������, �� ���, ����������?";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_2":
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
			DialogExit();
		break;
		case "ADS_2":
			dialog.text = "�� ��� ��� �������� ������?! �� ��, ��������!";
			pchar.Whisper.DeSouzaHits = 1;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_3":
			dialog.text = "���� ���� ��������������.";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_4_exit":
			LAi_SetActorTypeNoGroup(npchar);
			//LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 8.0);
		break;
		
		
		case "PC":
			dialog.text = "��� � � ���� ������ ����������! ��� ����?";
			link.l1 = "������.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			dialog.text = "��, �� ��������� �� ���. ��� � ���� �� ������� ��������������. ��-��, �������, �������� ����� ����� ��������� ������ � ����, � ���������� ��� �������. ����� � ��� ���������.";
			link.l1 = "��������� � �� ���������!";
			link.l1.go = "PC_fight";
			link.l2 = "������, ��-����� � ��� ���� �� ������.";
			link.l2.go = "PC_nofight";
		break;
		case "PC_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetActorType(NPChar);
			LAi_SetCheckMinHP(Pchar, 1, true, "Whisper_PC_CheckHP");
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		case "PC_nofight":
			Pchar.model="PGG_Whisper_0_NoHat";
			DeleteAttribute(pchar,"cirassID");
			DoQuestFunctionDelay("WhisperHold", 0.5);
			DialogExit();
		break;
		case "PC_2":
			dialog.text = "������� �����������. �� ��� ��� ������ ������ �����, ��������� � ���� ������� ��������. ��������� ������� � ��� � ����������� �����. ��� ������ � ������ ������ - �� ��������. ����, � ����� ������� �� ������ �� �����?";
			link.l1 = "� �� �� ���� ����. � ���� ����� ��� ������.";
			link.l1.go = "PC_2_1";
		break;
		case "PC_2_1":
			dialog.text = "�� ��������, ��� ��� ������� �� ��� �������? ���, ���� �����, �� ������ �������? ����� �� ������� �������������\n������, � ���� ���� ���� ��������, ������� ������ ���� ����������� - ������� �� �����. ��� ����� ���������� � ��������\n�� ����� ������ ��� �������� ������� � ��� ����������. ��� ��� � ���� �����, ��� ������ ����������, �� ������ ���������� �����\n� ����� � ���� ������ ���������������� ������, � �� ��������� ���� �� ��� ����� � ��������������� ������ ������� �� ������. ��� �������� ��� ���� ����, ����� ���������\n����� ���� �����������, ��� �� ����� ������� � �����, ����� ������. � ����� ������ �����, ������ ����� - ����� �� �����.";
			link.l1 = "����� ������� ������, � � ���������� ������� ����!";
			link.l1.go = "PC_2_2";
			link.l2 = "������� �� �� ������ ������������?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "� ���� ������ ��� ����\n�����, �������. ���� �� �������, � ���� ���� ��������� ���� ����� ������������� � ������ �� ����� �������� ������� � ����� �����. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
		break;
		case "PC_2_3":
			dialog.text = "�����, ��� ���. � ��������� ���� �������, �� �� ������ ��������� �� ������. ������ ��� �� ����� ������, ����� �� � ���� �������� �����, ��� ��� ������� ����� �������\n�����, �������. ���� �� ��������, � ���� ���� ��������� ���� ����� ������������� � ������ �� ����� �������� ������� � ����� �����. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "������...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.Whisper.HoldMonologue = true;
			DoQuestCheckDelay("TalkSelf_Quest", 3.0);
			
		break;
		
		case "FB":
			//CharacterPlayAction(npchar, "Shot");
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(�� ���� �� ����������, ������ ����� ������ ������� �� ���������� � ����� �����. ���� �������� � ��������� ����������� ������, ����� ���� ���������� ���������� � �������� �������� ������������ �������, ������� ����� ������� � �������)";
			PlayVoice("interface\beeping.wav");
			link.l1 = "������!";
			link.l1.go = "FB_exit";
		break;
		case "FB_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(�� ���� �� ����������, ������ ����� ������ ������� �� ���������� � ����� �����.���� �������� � ��������� ����������� ������, ����� ���� ���������� ���������� � �������� �������� ������������ �������, ������� ����� ������� � �������)";
			link.l1 = "������!";
			link.l1.go = "exit";
			DoReloadCharacterToLocation("Ship_Deck_Big","goto","goto5");
			PChar.quest.WhisperTeleport.win_condition.l1 = "location";
			PChar.quest.WhisperTeleport.win_condition.l1.location = "Ship_Deck_Big";
			PChar.quest.WhisperTeleport.function = "WhisperTeleport";
		break;
		case "CS":
			dialog.text = "��� ���� �� �������, �������. �� � ����������� ���� �� ������, �� ��� �������� ���� �������. ������ ��� �� �����, �������� � ���������.";
			link.l1 = "�� ��� ��������� ����������� ������?";
			link.l1.go = "CS_1";
		break;
		case "CS_1":
			dialog.text = "�� ���� ���� ���������, ��� ������ ��� �������?";
			link.l1 = "�� �����...";
			link.l1.go = "CS_1_1";
			link.l2 = "�������! � �� �����.";
			link.l2.go = "CS_1_2";
		break;
		case "CS_1_1":
			dialog.text = "���� �� ������ �������� ����� ���� �� ����, �� ��� ���������� ��������� ������������ � ������������ � �������. ������, ����� ���������� ����� �������� � ����, ��� ��� ��������� ������������������ ��������� �����������. �� �, �� ��, ����� ������� �� ��������. ��� ��� ����� ������ ������� �� �����, �� ����� ��������.";
			link.l1 = "��������, �����, ��� ������� �������� � ����� ���������. �������� ���.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "�� ����� �� ������ ��������, ������ ��� �� ����� �������.";
			link.l1 = "��������, �����, ��� ������� �������� � ����� ���������. �������� ���.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "��������? � ���� ������ ������ ���������� ���������, �������� �������� �� ���� ����������\n������ �� - ������������ ���������? ������� ��, ��� ���� ��������?! � �� ���� ������, �� ������ ���� � ������� �����, ��� ������ ���� ������...";
			link.l1 = "������� ��� �����������. � - ��������� �������. ������ ������ �� �� ������, ������� ���� �������.";
			link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "��� �� ��� ��������. �� ����� ���� ��, �� � ��� �� - ��� ����� � ��� �� ������. ������ �������� �����������, � ��� ���������� �� �������? ������ �� ��������. � ��� ������� �� Omnitech � ����� ��� �� ������ ������� �������.";
			link.l1 = "��. � ������ �� �������, ��� '�������� ������' - �� ������ ���������.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "�� � ��������! �� ��� ����� �����, ��� � ����! ��� ���������, ��� ��������� ���� ����������� ����� � ����� ����� - �������! ������� � � ����� �������� � �� ���.";
			link.l1 = "�� ���� �� ����� ��� ���������� � Omnitech?";
			link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "�����, ����� '�����' - ����������� � ������ ��������. �� ��� ��� ���������, ��� - ��� ����������. �� ��, �� �� �������� ������ ����� ���������������� ������������� ������������� ����������� ���������� �� ���������� ���������� - ����������� ����������. �� ����� ���� �� �� ������� �����. ����� � ������ ������ �������, ������ ������������������ ��� ���� ������� ������������ �����, ������� �� ����� ��������� �� ���� ����.";
			link.l1 = "��� ���� ���������� ����� ������������ ������ �������?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "� ��� ��� �� ��� ���������� ������� ��������� ��������. ���� ��������� � ������� � ���������� �� ������������ ��� �������! ���� � ������ ����� ������, ��� �� ����� ����, ��� ��� ������� ������ ������������� �� ��� �������� � ����������, � ��� ��� ������� ���� ����� ��������� ��� ��, ��� ���������� � ���� ������.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "� ������ ���� �������. �� ����� ��� ��-�����, ��� �������� � ��������� �������������. � � ������ ����� �� ���� �����, �� ������ �� ��, ������� ��� ����������� ����� ���� ����, ��� ���!";
			link.l1.go = "CS_bad";
			link.l2 = "���� ��� ��������� � ������ ������ ��, ��� �� ��������, �� ������� �������� � ���������� �� �����. � ����� �� ������� ������ ���������� � ����� �����. ";
			link.l2.go = "CS_neutral";
			link.l3 = "׸��, � ���� �� ����... ��� � ����, ������� � ����� ������. � ����� ���������, ��� �� ������.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "����� �� �� ��-���� �������.";
			ChangeCharacterReputation(pchar, -100);
			LAi_tmpl_afraid_SetAfraidCharacter(npchar,pchar,false);
			link.l1 = "� ��, ���������!";
			Link.l1.go = "ExitSC";
		break;
		case "CS_neutral":
			dialog.text = "��������... ������� ��� �������. ��� ��, � ��������� � �� � ����� ���� ����������.";
			link.l1 = "� ���� �� ��������� ����. ������.";
			link.l1.go = "ExitSC";
		break;
		case "CS_good":
			dialog.text = "� ���� �� �� ����� ���� ����� �� ��������� �����, ��� ��� �������� ��������. �� ���������� ����� ������ � ����. ���� ���� ������ ��������� ���� � ���� ����� ������� ����, �� ������ ����� �� ���� �����-�� ������� �������� ���������� ��������. ������ ��� ������� ������ �������� ��� ������, ��� ��� � ���� �� ����� ��������. � ����, � ������ �������, ��� ���� ����. ";
			ChangeCharacterReputation(pchar, +100);
			link.l1 = "��� �������, ��� ��, �� ��� � ���� ������ �����������. �� �������� �� ����, ������� ������ �� ����. ������, ��������� �� ������� ��� ����������.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "������ ���� �������� �� ������ ������. ��� ������� ����������, ��� �� ���������� �� ���� �����. � �� ����� ��������� �� �������, ��� ��� ���� ������� ����������� � ���� ��������������.";
			link.l1 = "���, ������.";
			link.l1.go = "ExitSC";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "ExitSC":
			LAi_LocationFightDisable(locLoad, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
		break;
		
		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			//LAi_SetImmortal(npchar, false);
			//LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
		
		case "OrderHunter":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			if(!CheckAttribute(pchar,"OrderHunter"))
			{
				SetQuestHeader("TheLastMass");
				if (startherotype == 2)	
				{
					sTemp = "�� �� �� ������, ��� ������� ����� ����� ����������, � ���� ��� ��� ������ ����� � ���? ";
					AddQuestRecord("TheLastMass", "1");
				}
				else	
				{
					sTemp = "�� ���������� ����� �������� � ����� ����������! ";
					AddQuestRecord("TheLastMass", "1_1");
				}
				pchar.OrderHunter = "1";
				Link.l1 = "����������? ������� ���� ��������� ������� � ���� ���� ��� �������� ��������. �� ��, ����, ���� � ����"+GetSexPhrase("��","��")+"!";
				Link.l1.go = "OrderHunterMeeting"; 
				if (WhisperIsHere())
				{
					Link.l1 = "...";
					Link.l1.go = "OrderHunterMeetingWhisperIsHere"; 
				}
			}
			else	
			{
				sTemp = " ";
				
				Link.l1 = "�����? �����, ����������� � ���������� �� ������.";
				Link.l1.go = "OrderHunterBattle";
				
				if(sti(PChar.OrderHunter) == 2) {AddQuestRecord("TheLastMass", "2");}
				
				if(sti(PChar.OrderHunter) == 3)
				{
					Link.l1 = "������, � ���� �� ��� �� ������ ����������, ��� �������� �� ����. �����, �� �������������, ��� ��������� � ����������. �����, ��� ��������� ���� ����, � � ������� ���� ���� �����.";
					Link.l1.go = "OrderHunterNegotiate";
				}
				if(sti(PChar.OrderHunter) > 3)
				{
					Link.l2 = "����� ��, �***� �� ���������! ����� ����-�� ������� ����������?";
					Link.l2.go = "OrderHunterCheck";
				}
			}
			dialog.text = GetFullName(PChar) + "! "+ sTemp + "� ���������� ���� ������ �����, � ���, �������, �� �������� ����������� ���������.";
			if (WhisperIsHere())
			{
				dialog.text = dialog.text + "\n� ����� ��� ������ ������? ��� ������ ����� ����, ����� ������, ��� � ������� ������� ����� �� ���� ������!"
			}
		break;
		
		case "OrderHunterNegotiateWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterNegotiateWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;
		
		case "OrderHunterNegotiateWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			RestoreOldDialog(npchar);
			dialog.text = "� ��� ������ ��� ����� ���������. ��� ����� ����������� ������� �� ���� ��� �������.";
            Link.l1 = "��� �, � ��� ����� �����, ������ ����.";
			Link.l1.go = "OrderHunterPeace";
			Link.l2 = "��������� �� ����������. �� �������� ������ � ������, �� � �� ���� ��������� ���� ���� ����� � ������������ � ��� ������.";
			Link.l2.go = "OrderHunterBattle";
		break;
		
		case "OrderHunterNegotiate":
			dialog.text = "��... ��� � ����. � ����� ����� � �� ������, �� ��� ����� �������� ��������� ������� ����. ��� ������� ���������� �� ���� �������, � ����� ���������. ��� � ���� ���� ���� �� ������ �� �������.";

            Link.l1 = "�� ������� �� ��� ����������� ����� ��� '�������������' ���������� ������?";
			Link.l1.go = "OrderHunterNegotiate_1";
		break;
		
		case "OrderHunterNegotiate_1":
			dialog.text = "������ ����� ����� ���� ������������ ������ ������� ����� ���� � ������. ��� ������� ��� ��������.";
			if (WhisperIsHere())
			{
				Link.l1.go = "OrderHunterNegotiateWhisperIsHere"; 
			}
			else
			{
				Link.l1 = "��� �, � ��� ����� �����, ������ ����.";
				Link.l1.go = "OrderHunterPeace";
				Link.l2 = "��������� �� ����������. �� �������� ������ � ������, �� � �� ���� ��������� ���� ���� ����� � ������������ � ��� ������.";
				Link.l2.go = "OrderHunterBattle";
			}
			
			AddQuestRecord("TheLastMass", "3");
			CaptureCapitol_SeaBattle();
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1.location = "Reefs";
			pchar.quest.CaptureCapitol_SeaBattleStarted.function             = "CaptureCapitol_SeaBattleStarted";	
		break;
		
		case "OrderHunterMeetingWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterMeetingWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;
		
		case "OrderHunterMeetingWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			RestoreOldDialog(npchar);
			dialog.text = "����� ����������? ���� ��� ������ �� ���\n���� ���� �� ���������, "+pchar.name+", ������ ��� ���� ��������� � ���� ���.";
            Link.l1 = "�����, ����� ��� ���� ���������? ����������, ������� ���� ��������� ������� � ���� ���� ��� �������� ��������. �� ��, ����, ���� � ����"+GetSexPhrase("��","��")+"!";
			Link.l1.go = "OrderHunterMeetingWhisperIsHere_2"; 
		break;
		
		case "OrderHunterMeetingWhisperIsHere_2":
			StartInstantDialog(pchar.PrevNpc, "OrderHunterMeeting", "Quest\WhisperLine\Whisper.c");
		break;
		
		case "OrderHunterMeeting":
			dialog.text = "�������� ������ �� �������� ����� ������� ����������� �� �������. ���� �� ������ ������ ��� ����� �������� � ����� ������������� ������ ��������. � � ����� � ���������� ���������, ��� ����� ������� � ������������ ����������� �������������� �������������� � ����������� ������� �������.";
            Link.l1 = "���� ��! ��� ���������... � ��� ��������� ���� ����� �������?";
			Link.l1.go = "OrderHunterMeeting_1";
		break;
		
		case "OrderHunterMeeting_1":
			dialog.text = "� ������ ����� � ��� ������� �������.";
            Link.l1 = "��������� �����. ��� �� �� �� ��� �����, ����� ���� �� �������� ����������� �� ������.";
			Link.l1.go = "OrderHunterBattle";
		break;
		
		case "OrderHunterCheck":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > rand(150))
            {
                dialog.text = "������� � �� ����� ��������� � ����� �������. ������� ������� ���� ����� ��������� � ����� ������.";
                Link.l1 = "�� � ����������.";
                Link.l1.go = "OrderHunterPeace";
				Link.l2 = "�������, �� ��� �������� � �����, ���� � ���� ������� �� ��������.";
				Link.l2.go = "OrderHunterBattle";
                AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            }
            else
            {
                dialog.text = "���� �� �������� ���� ����� ��������� ������������!";
			    Link.l1 = "����� � ������ ���� ����� �������.";
			    Link.l1.go = "OrderHunterBattle";
			    AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            }
		break;
		
		case "OrderHunterPeace":
            PChar.OrderHunter = sti(PChar.OrderHunter)+1;
			AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
		
		case "OrderHunterBattle":
			PChar.OrderHunter = sti(PChar.OrderHunter)+1;
            AddDialogExitQuest("Battle_Hunters_Land");
            DialogExit();
        break;
		
		case "OrderLeader":
			LAi_SetActorType(npchar);
			dialog.text = "���� ���� ������� �������� ����� ������ ���� �������. �� ��� ������ �������: ̸����� ������, ���� �� ����� ��������� � �����, ��������� ��� � ��������������\n� ��, ����������� �� �����, - ����������� � �������!";

            Link.l1 = "��� ��� �� ����������?";
			Link.l1.go = "OrderLeader_exit";
		break;
		
		case "OrderLeader_exit":
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			DoQuestFunctionDelay("CaptureCapitol_ShoreBattleRaiseUndead", 3.5);
			DialogExit();
		break;
		
		case "OrderLeader_1":
			dialog.text = "���� ������� � ����, ������� ������ �����. �� � �� ����� ������������ ��� � ������� � �����! ���! � �� ����������, ���� ��� ������� ����������� ������� � �������� �������� - ��� ���� � ����. �� � �� �� �������, ��� ������� ������� ���� �����, ����� � ��� ������� ����� ���.";

			if (WhisperIsHere())
			{
				Link.l1.go = "OrderLeaderWhisperIsHere"; 
			}
			else
			{
				Link.l1 = "��� ��� ���� ���, �������? ����������, ��� ����� ������ � �������� ��� ������ �� ���� ����, � �� �, � ������ ���� �������� � ��.";
				Link.l1.go = "OrderLeader_2";
			}
		break;
		
		case "OrderLeaderWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderLeaderWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;
		
		case "OrderLeaderWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			RestoreOldDialog(npchar);
			dialog.text = "��� �� ���� ���� �����... �������� �������? ��������� ������ - � ������� ������������.";
			Link.l1.go = "OrderLeaderWhisperIsHere_2";
		break;
		
		case "OrderLeaderWhisperIsHere_2":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.PrevNpc, "OrderLeaderWhisperIsHere_3", "Quest\WhisperLine\Whisper.c");
		break;
		
		case "OrderLeaderWhisperIsHere_3":
			dialog.text = "��� ���� ��, ������? � ������ ������ � ������������, ��� �� �������� ����� �����, ������� �� �����. �����, �� ��� �� ��� ������, ��� � ������� �������� ���� � ��, ������!";
			Link.l1 = "��� ��� ���� ���, �������? ����������, ��� ����� ������ � �������� ��� ������ �� ���� ����, � �� ��, � ������ ���� �������� � ��.";
			Link.l1.go = "OrderLeader_2";
		break;
		
		case "OrderLeader_2":
			dialog.text = "�������� �� ����� � ���� �� ������. ������� ������������ ��������� �� �����. ��� ���������, �� ������ ��? � ����� ������� �� �� � �����, � ��� ���� �� ������� ����, � ��������� ���? ������� ����, ��� ������� ��������� �����, � ������ ������. � ���, ������� � ����� ������\n�����-�� ��� ���� ���� ������� ����, �� � ����� �������� ���� ����� ���������� ������� � ��������� �� �� �����. � ������ �� �������� � ����� �������!";
            Link.l1 = "�� ����� ����� ����������� �������? �� ����������� ��� �� ����� ������� � ����� �� ����. � ���� ������� ����� ���� ���� �����! ������ ����, ����� ���������� ��, �� ������� �� �������� � ����������� ����� ��������. ���� �� ���� ����� ����������. �� ������ �� �������, ��� ������ �����.";
			Link.l1.go = "OrderLeader_3";
		break;
		
		case "OrderLeader_3":
			dialog.text = "���� �� ������, ��� �� ���������� ��� ������� �����. ����� ��� �������� ����� �����, ������� ������� ����. � ��, ��� ������ ����� ������, �� ����, �� �� ������ ������ ������ �� �����!";

            Link.l1 = "��� ���� ��.";
			Link.l1.go = "OrderLeader_fight";
			if (startherotype == 2)
			{
				Link.l1 = "��� �������� �� ��� ������ � ���� �� �����?";
				Link.l1.go = "OrderLeader_4";
			}
		break;
		
		case "OrderLeader_4":
			dialog.text = "�, �� ��������. � ����� ��� ������ ����� ���������� � �������� �� �����, ����� ����� ��� ����. ��������, ��� ���� ����? ������ ����������, � � ���������� �� ����� ���������, �������� ������� ������ �� ������� ��������. �����, �� � ���� ��� ������. � ����� ���� ��������� �� ����.";

            Link.l1 = "��� ���� ����� ������ ���� �����!";
			Link.l1.go = "OrderLeader_fight";
		break;
		
		case "OrderLeader_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			CaptureCapitol_OnLeaderDeath();
			LAi_LocationFightDisable(locLoad, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "CaptureCapitol");	
			for (int j=1; j<=6; j++)
			{
				sld = CharacterFromID("MaltGuard_"+j);
				LAi_group_MoveCharacter(sld, "CaptureCapitol");	
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
			}
			
			LAi_group_SetHearRadius("CaptureCapitol", 100.0);
			LAi_group_FightGroupsEx("CaptureCapitol", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);	
		break;
		
		case "CapitolCaptured":
			chrDisableReloadToLocation = false;
			pchar.quest.CaptureCapitol_Decision.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_Decision.win_condition.l1.location = "DeckWithReefs";
			pchar.quest.CaptureCapitol_Decision.function             = "CaptureCapitol_Decision";
			
			dialog.text = "��� ��� �������, � ����� �� ����� ������� ������! ������� �� �� �������, �, �������?";
            Link.l1 = "��? ���-�� �� ��������, ����� �����"+GetSexPhrase("","�")+" ���� ����� �����������.";
			Link.l1.go = "CapitolCaptured_1";
		break;
		case "CapitolCaptured_1":
			dialog.text = "�� ��� ��, � �������� ����, �� ������, ���� ��� ���������� ��������. �� ���������, �������\n��� ���, � ����, ��� ��� ����������! ���� �, ���... �������� ������ ���������, � ����� ������� �� ���������. ����� ����� ����� ���������� ������ �����, ����� ��������, � ����� ���������� - � ����� ����������, ����������� ������� �� ������� ��������. ������, ���������� ���������� ������� ����� ����������� �����.";

            Link.l1 = "���������, � ��� �� ���� ���� ����� �������? ������� ����-��?";
			Link.l1.go = "CapitolCaptured_2";
		break;
		case "CapitolCaptured_2":
			dialog.text = "����� �������, � �����... ���� ����� ��� ��������, �� � �����, ��� �� ����� �� ��������������� ���� ������ ��� ���������� � ���������� ����������� �����? ��, ����� �� ����� �����, �� �� ����� �� ��������� ����� ����� ��������, ����� ��� ���������� �����.";

            Link.l1 = "�� ����, ��� ��������. �������� �� � ���� � ������.";
			Link.l1.go = "CapitolCaptured_3";
			Link.l2 = "����� �����������. ����� � ��� ����� ����������� ����, �� ������ ������.";
			Link.l2.go = "CapitolCaptured_4";
		break;
		case "CapitolCaptured_3":
			dialog.text = "�����. ����� � ������ ������ ������ �����, ��� ����� ����, � �� ������� ����������.";

            Link.l1 = "�����, ���������� ����� ������ ���� �������� ���� ����� �����.";
			Link.l1.go = "CapitolCaptured_sell";
			Link.l2 = "����... ����� �� �� ������� ��� ����� ����.";
			Link.l2.go = "CapitolCaptured_4";
		break
		case "CapitolCaptured_4":
			dialog.text = "�������� �����, �������!";

            Link.l1 = "���� ��� � ��������� �� ��������. ��������� ������� � ����� ������. ������ ������� ������, �� ����� � ��� �� ���� ����� ��������.";
			Link.l1.go = "CapitolCaptured_keep";
		break;
		
		case "CapitolCaptured_keep":
			dialog.text = "�������, �������! � ��� �� �������.";
            Link.l1 = "������.";
			Link.l1.go = "exit";
		break;
		
		case "CapitolCaptured_sell":
			pchar.SellCapitol = true;
			DialogExit();
			if (CheckAttribute(pchar, "WhisperChSpokeToUsurer"))
			{
				AddQuestRecord("WhisperChinamanRelic", "4");
			}
		break;
		
		case "Beatrice":
			dialog.text = "������� ������� ��� �������. �� ���� ����������� ���������� �������� �� �����-������ �����? � �� �� ���������� ������ ����� �����, ������� ������� �� ��� ����� ������ ����, � ��� ����� �� ������ �������� ����.";
            Link.l1 = "���� ����� � ����.";
			Link.l1.go = "exit";
			npchar.MetWhisper = true;
		break;
		
		case "Hugo_Lesopilka":
			dialog.text = "�����-�� ��� ���, �������.";
            Link.l1 = "� ���� �� ����������!";
			Link.l1.go = "exit";
		break;
		
		//�������
		case "WhisperIsHere_exit":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
		break;
		
		case "BS_WhisperIsHere":
			dialog.text = "����� ������� ������� � ��������? ��� �, ��� �� ���������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_1_WhisperIsHere":
			dialog.text = "������? �� � ������?";
			Link.l1 = "��. �������, ��� ��� � ���� �����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_2_WhisperIsHere":
			dialog.text = "������, �� '���������' ���� ��� ��������...";
			Link.l1 = "����� � ���� �����. ���� �����, ������� �������� ������, ��� ����� ���������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_3_WhisperIsHere":
			dialog.text = "'����� ������ ������, � ������ - ��� �����.' ��� �������� ��� �����!";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_4_WhisperIsHere":
			dialog.text = "�� ���, ��� ��� ��������� ���������. ��������� � ����� ���� �� � ����.";
			Link.l1 = "�������, �� �����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_5_WhisperIsHere":
			dialog.text = "� ���� ������ ������������. ���� ������.";
			Link.l1 = "�� � ���? ���� �������, �� ������� ����� ������������.";
			Link.l1.go = "BS_5_WhisperIsHere_1";
		break;
		
		case "BS_5_WhisperIsHere_1":
			dialog.text = "������������, ����� �� ���� ��� ��������� ���������? � ����� ������� ���� ����� ���� �������� ��� ������� ������!";
			Link.l1 = "�� ��������� �� ���. ������ �� ��������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_6_WhisperIsHere_1":
			dialog.text = "��, ��� �� ��� �����\n�� ���� ���� ���������, �� ���� � �� �������� ���� ����������. ׸��, � ������ �� ������, ��� �������, � ���� ������ ��� ������.";
			Link.l1 = "������, ��� ���� ������� ����������, ���� ��� ����. ����� ������� ���? ��� ���������?";
			Link.l1.go = "BS_6_WhisperIsHere_2";
		break;
		
		case "BS_6_WhisperIsHere_2":
			dialog.text = "� ���� �� ������ ������, ���� �������� ������� �����.";
			Link.l1 = "�����, ����� ���������� ����. ����� � ������� ���-�� ��� ������.";
			Link.l1.go = "BS_6_WhisperIsHere_3";
		break;
		
		case "BS_6_WhisperIsHere_3":
			dialog.text = "������ �� �����, � ���� ������ �� ��� ��������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_7_WhisperIsHere":
			dialog.text = "�� ��, ������ ��� ����� ���� �����.";
			Link.l1 = "�� ����� ���� ���. ����, ��� ����� �������, � ��� �����.";
			Link.l1.go = "BS_7_WhisperIsHere_1";
		break;
		
		case "BS_7_WhisperIsHere_1":
			dialog.text = "�� ����"+ GetSexPhrase("","�") +", � ��� �� �������� ��������� ��� ����.";
			Link.l1 = "��� ����, �� ������ ����� ����, ��� �� ������� ����� �� ��� ������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_8_WhisperIsHere":
			dialog.text = "�� �������������? � �� �������, ��� ��� ��� ��������, ���� ���� ����� ������������?";
			Link.l1 = "�� � ����� �������� ��������. ������� �� ���������� �����-�� ������ ������?";
			Link.l1.go = "BS_8_WhisperIsHere_1";
		break;
		
		case "BS_8_WhisperIsHere_1":
			dialog.text = "���� ������, ����� ����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_9_WhisperIsHere":
			dialog.text = "����� ����� �� ����� � �����. �� ������� ��� ������ ��� ������ �����...";
			Link.l1.go = "BS_9_WhisperIsHere_1";
		break;
		
		case "BS_9_WhisperIsHere_1":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_6_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;
		
		case "BS_10_WhisperIsHere":
			dialog.text = "����... �������� ��� ����� ���� �� � �����.";
			Link.l1.go = "BS_10_WhisperIsHere_1";
		break;
		
		case "BS_10_WhisperIsHere_1":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_7_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;
		
		case "BS_11_WhisperIsHere":
			dialog.text = "��� ���������� ������� ���� ������� �������.";
			Link.l1 = "���� ����. �� � ��������, ��� ������� ���-�� �����. ����� ��� �������� ������.";
			Link.l1.go = "BS_9_WhisperIsHere_1";
		break;
		
		case "BS_12_WhisperIsHere":
			dialog.text = "��� ��� �����! � ���� ������� ��������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_13_WhisperIsHere":
			dialog.text = "��� ������ ������ �� ����� �����?";
			Link.l1 = "�� ����. ����� �������� � ����������. ����� ������� �������, ��� ���. � ��?";
			Link.l1.go = "BS_13_WhisperIsHere_1";
		break;
		
		case "BS_13_WhisperIsHere_1":
			dialog.text = "� ���� ��������� � ���� �� ������. ���� �����, ������ ������� � ����.";
			Link.l1 = "����� ��� ��� �� ������? ������ ���������� �� ����� �������� �������, � ������!";
			Link.l1.go = "BS_13_WhisperIsHere_2";
		break;
		
		case "BS_13_WhisperIsHere_2":
			dialog.text = "��� ������ ��������� ����� ������. �����, ������� ���� �� �����.";
			Link.l1 = "����� �� �������� ���������. �����, ����� ���. �����, ������� ��������.";
			Link.l1.go = "BS_13_WhisperIsHere_3";
		break;
		
		case "BS_13_WhisperIsHere_3":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_SetPlayerType(pchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "goto", "goto2");
			BSHangover_Cutscene_2("");
		break;
	
		case "BS_14_WhisperIsHere_1":
			dialog.text = "��... ������, ����� � ����� ������ �� ������� ����� �������.";
			Link.l1 = "������ �� ��. �� �� ������� ����, �� ���� �� ������� ���� ���� ����� ������. � � ���� ��� ��������"+ GetSexPhrase("��","���") +", ������ ��.";
			Link.l1.go = "BS_14_WhisperIsHere_2";
		break;
		
		case "BS_14_WhisperIsHere_2":
			dialog.text = "��, �� ��������� ���� ��������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
	
		case "BS_15_WhisperIsHere":
			dialog.text = "����� �� ��� ���������� ������?";
			Link.l1 = "���� �� ������� ��� � ������ �������, ��������.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
	
		case "BS_16_WhisperIsHere":
			dialog.text = "� ��� � �������. ������, ��� �� ���"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("","�") +".";
			Link.l1 = "� ������ ����"+ GetSexPhrase("","�") +".";
			Link.l1.go = "BS_16_WhisperIsHere_1";
		break;
	
		case "BS_16_WhisperIsHere_1":
			dialog.text = "� ���� � �� ���������, �� �����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
	
		case "BS_17_WhisperIsHere":
			dialog.text = "��������, � ��� �����!";
			Link.l1.go = "BS_17_WhisperIsHere_1";
		break;
		
		case "BS_17_WhisperIsHere_1":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Flint", "BS_PN_8_1", "Quest\BlackSails\Pogonya_Nachalas.c");
		break;
		
		case "BS_18_WhisperIsHere":
			dialog.text = "������, ��� ��� ��������� ����� '�������' ������.";
			Link.l1 = "�� ����� ����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_19_WhisperIsHere":
			dialog.text = "����� ��� ������ �� ������ ������. ������ � ���� ���������� �� �������.";
			Link.l1 = "��, �����.";
			Link.l1.go = "WhisperIsHere_exit";
		break;
		
		case "BS_20_WhisperIsHere":
			dialog.text = "���-�� ��� ��������...";
			Link.l1.go = "BS_20_WhisperIsHere_1";
		break;
		
		case "BS_20_WhisperIsHere_1":
			DialogExit();
			RestoreOldDialog(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			SetCharacterTask_Dead(npchar);
			DoQuestFunctionDelay("BSUrka_PoisonOfficers", 1);
			DoQuestFunctionDelay("BSUrka_PoisonSelf", 3.0);
			DoQuestFunctionDelay("BSUrka_Poison_Flint", 6.0);
		break;

		// <- �������
	}
}