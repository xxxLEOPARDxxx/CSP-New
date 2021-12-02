void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_Chinaman_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanSpeaks", 0.5);
			DialogExit();
		break;
		case "Exit_ChiGuard_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanCapSpeaksAgain", 0.5);
			DialogExit();
		break;
		case "Exit_portman":
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.questTemp.Whisper.Portman_Deck = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "exit";
			
			if (npchar.id == "W_ChinamanGuard")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "�������, �������� ����� '�����' �� ������� � �����.";
					Link.l1 = "���������, ������ �� �� ��� ���� �������������� �� �������. �� ��� ���� ���� ��������?";
					Link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "�� �� ����� �� ������ ������ �����. ����� �������� ��������� �����, ����� ��� ������� � ��� ���������. �-�-�... ������� �� � �� ��� ��������� ���� � ����, �������.";
					link.l1 = "�� ����� ��� ��������� ������.";
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "�� �������\n��, �����.";
					RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 3;
					break;
				}
			}
			if (npchar.id == "W_Chinaman")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "�������.";
					Link.l1 = "� ��� �� ���� �����?";
					Link.l1.go = "ChinamanSpeak_1";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "�����-�� ����� ��� ���� ���, ��� ��� � �������. �� ����� ����� �� �����, ����� ��������� ����� � �������, ����������� � ����� ������.  ���� ��� ������� ��� �������� ���� ������������, ������� ����������� ���. �� ����� �� ������ ������ ���� ����, ������� ������ �������� ������� �������, � ����� ���� ������. ������, ��������� �� ��� ������ ������, ������ ����, ���� �������, ���� ����������� �� ���� �������\n����� �� ������� ���������, ��������� ������� ��� �� ���, ��� �� ���� �������. ���� ������� ���������� �� ������ � ���������� �����. � ���������� �������� � �������� ������� ������������� � ���. �� ��� ���� ������ ��� ������� �� �����. ��������� �������� ��� �����, ��� ��� ���� ������� �� ������ ������� �������� �������������. ��������� �������� �������, � ���� � ������� ������� �����."; 
					Link.l1 = "������� �������. ���� �������� ����� ����� �������.";
					Link.l1.go = "ChinamanSpeak_1_1";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "������� �������, � �� ������ �����.";
					GiveItem2Character(npchar, "blade9");
					EquipCharacterByItem(npchar, "blade9");
					LAi_SetImmortal(NPChar, false);
					Link.l1 = "����� �� ��� �������.";
					Link.l1.go = "ChinamanOff";
					npchar.quest.meting = 3;
					break;
				}
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "Portman_Cabin":
			dialog.Text = "��, �������, ������ ����� ��������? ������ ����� �� �� ���� ������?";
			Link.l1 = "�� ������ ���-���, ��� ���� ����������. ���������� �������, ��� ����� ����.";
			Link.l1.go = "Portman_Cabin_1";
		break;
		case "Portman_Cabin_1":
			dialog.Text = "�... � �� ���� ����, ��� �������� ��� ����� �� ��������. � ���� ��� ������� �������� ���������� ����� �� ���? ������ �� �� ���� �� �������!";
			Link.l1 = "����� � ���� �� �����, ��� � ����� �������!";
			Link.l1.go = "Portman_Cabin_fight";
		break;
		case "Portman_Cabin_fight":
			//AddQuestRecord("WhisperQuestline", "8");
			//CloseQuestHeader("WhisperQuestline");
			//SetFunctionNPCDeathCondition("Whisper_Portman_Cabin_Is_Dead", npchar.id, false);
			pchar.questTemp.Whisper.KilledPortman = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			//AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Portman":
			dialog.Text = "�����������, ���������� ����������.";
			Link.l1 = "������������, �������.";
			Link.l1.go = "Portman_1";
			
			if (CheckAttribute(pchar, "Whisper.BetrayChard"))
			{
				dialog.Text = "�� ���, ���� ������ ����� ������� ����������� ���������?";
				Link.l1 = "��� ���.";
				Link.l1.go = "exit";
				if (CheckCharacterItem(pchar, "Bible"))
				{
					Link.l1 = "� ��� ��. ��� ���� ������.";
					Link.l1.go = "Portman_betray_chard_1";
					pchar.Whisper.GotPortmanAx = true;
				}
			}
		break;
		case "Portman_1":
			NextDiag.TempNode = "Portman_3";
			dialog.Text = "������ �������� ��� ������� �� ���� ����� �����?";
			//Link.l1 = "���� ��������, ����� �� �������� ���� �����? ���� � ���, ��� ��� ���� ������ � ��� � ������� �������� �� �����, �� ����� ���-����� ���������.";
			//Link.l1.go = "Portman_enemy";
			Link.l1 = "���� ������������, ��� ��� ������ �� �������� ������ � �������� ����� �������. ���� ������� �������� � �� ������� ������ �������, ���� ����� � ��� ����.";
			Link.l1.go = "Portman_ally";
			Link.l2 = "������ ������������. ��������� ���������� ������� �������.";
			Link.l2.go = "Portman_2";
		break;
		case "Portman_2":
			dialog.Text = "� ����� ������, �� ���� ��� ������. ������ ����� ���, �� ��������������, ��� ����� ���� ���������.";
			Link.l1 = "�����.";
			Link.l1.go = "exit_portman";
		break;
		case "Portman_3":
			dialog.Text = "����� �� �������������, �� ����� ���������!";
			Link.l1 = "�����...";
			Link.l1.go = "exit";
		break;
		case "Portman_ally":
			dialog.Text = "� � ����� �����. �� ����� ��������� �� ����, ��� ���?";
			Link.l1 = "����������� ����� ����� ����. ���� ������ ������ ���� ������ ���������� � ����� ��������.";
			Link.l1.go = "Portman_ally_1";
		break;
		case "Portman_ally_1":
			dialog.Text = "������� �� ������ ������ �����. �� � �������. ���� ��� ������ ��, ��������� � ���� ��� ������. ���� ����� ����� � ������� ��.";
			Link.l1 = "� ������� �� ������ ����� �����?";
			Link.l1.go = "Portman_ally_2";
		break;
		case "Portman_ally_2":
			AddQuestRecord("WhisperChardQuest", "4");
			pchar.Whisper.BetrayChard = true;
			NextDiag.TempNode = "Portman_betray_chard";
			dialog.Text = "� ���� �� �����, ������ ���. �� ���, ������. ����� �������� ����, ����� ������� ��� ������� ���� �����, ��� ��� ������� ��� �������.";
			Link.l1 = "������������.";
			Link.l1.go = "exit";
		break;
		case "Portman_betray_chard":
			dialog.Text = "�� ���, ���� ������ ����� ������� ����������� ���������?";
			Link.l1 = "��� ���.";
			Link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				Link.l1 = "��. ��� ���� ������.";
				Link.l1.go = "Portman_betray_chard_1";
				pchar.Whisper.GotPortmanAx = true;
			}
		break;
		case "Portman_betray_chard_1":
			AddQuestRecord("WhisperChardQuest", "5");
			CloseQuestHeader("WhisperChardQuest");
			TakeItemFromCharacter(pchar, "Bible");
			Log_Info("�� �������� ������������� �����");
			GiveItem2Character(pchar, "topor_emperor");
			PlaySound("interface\important_item.wav");
			dialog.Text = "�������! ������ � ���� ����� ��������, �� ����� ��� ��� ������ ����� ���� �������\n� �� �������, ��� � �������� �� �����. ���, ������ ���� �����. �� ���������, ������ � ��� ����, ��� ����� ������ ���. ���� �� ���� �� ��������, ������ �������. ������, ����� ��� ����� ����� �������.";
			Link.l1 = "��� ��� ��! �������.";
			Link.l1.go = "exit";
		break;
		
		case "WarDogCap":
			dialog.Text = "����� ��? � ����� �� ����� ��� ������� � ������ ����������.";
			Link.l1 = "�� ���� ��� ������ �� ����������.";
			Link.l1.go = "WarDogCap_1";
		break;
		case "WarDogCap_1":
			dialog.Text = "��� �� ���� ������ �����?";
			Link.l1 = "���� ������-����������, ������� �� �����, ��� ������� ��� �������. ���� �������� �������� ����� ��������� ��������� ������, �� ����� ����� ����� ���� ����� �������, �� � ������� ��������� ������� ��� ����� ���.";
			Link.l1.go = "WarDogCap_2";
		break;
		case "WarDogCap_2":
			dialog.Text = "������ ����� ���� �� ���� �����?";
			Link.l1 = "� ���� ���� ���-��� ��.";
			Link.l1.go = "WarDogCap_2_1";
		break;
		case "WarDogCap_2_1":
			dialog.Text = "�� ��� ���� ������? ���� ������, ���� ��������� ��� ����.";
			Link.l1 = "�� ������ ������, �� �� ����������, ������� ����������, � ������� �������� � ����������������� ����.";
			Link.l1.go = "WarDogCap_3";
		break;
		case "WarDogCap_3":
			dialog.Text = "����? �, �� ��� �� ����������� �������? ��� � �� �� ��� ���������, ������ � ��������� ��������. ������ ������ �������.";
			Link.l1 = "��� �� ������, ������?! � ����� ������ ���������?";
			Link.l1.go = "WarDogCap_4";
		break;
		case "WarDogCap_4":
			dialog.Text = "� ���, ��� ������ �� ��� �� �������. � � �� ������� ���� ��� � ����� �������������!";
			Link.l1 = "�� � ���� �������, �������!";
			Link.l1.go = "WarDogCap_fight";
		break;
		case "WarDogCap_fight":
			AddQuestRecord("WhisperQuestline", "8");
			CloseQuestHeader("WhisperQuestline");
			
			UnlockAchievement("WhisperLine", 3);
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
			pchar.Whisper.NanoCostume = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "DeSouza":
			dialog.Text = "���� ��, ����� �������. � � ����� ���� �����, ������.";
			Link.l1 = "��� ������� �����, ����� �� �� ���� ������, ��� ��� � ���� � ���� ������.";
			Link.l1.go = "DeSouza_1";
		break;
		case "DeSouza_1":
			dialog.Text = "������, �� �����. �� ���� �������������, ��� � ������ � ����� ������?";
			Link.l1 = "����������, ��� ���� ������ �� ��� ���, �� ��� �� ����� ������. ���� ���������� ���� ���������. ����� ������� ���������.";
			Link.l1.go = "DeSouza_2";
		break;
		case "DeSouza_2":
			dialog.Text = "� � ��� �� �� ������ ��������?";
			Link.l1 = "� ������� ���� � ������� �������. ��� ����������� ���� ����������, �� �� ����� ��� ���������. �� ��������� �� ��� ����� ������� ���-�� ��������?";
			Link.l1.go = "DeSouza_2_1";
		break;
		case "DeSouza_2_1":
			dialog.Text = "��, �� ���-�� ����� ��������� ��� � ����, ����� ���� �����. � �������� ��� �������� ������ � ���� ���� ����������� �������, � ����� ���������� �� ��� �������. �� ���� ������, �������� �� ���� ��� ���.";
			Link.l1 = "����� �������, ��� ���. � �� ������ ��� ����� ����� ��������?";
			Link.l1.go = "DeSouza_3";
		break;
		case "DeSouza_3":
			dialog.Text = "���� ��! � ���� ���� ��� �����. �� �������� ��� �� ��� ���������� �������, ������ � ��������� ����� ����� ������ ���������������� ��� ����� ������� ��������. �� �����������, ��� �� ���� ��� �������\n�� �������� ���������� � �������-�����������, � ��� �������, �� ������, ��� ������� �� ��������� ������ �������� �������. ����� �����������, ��� ��� �������-���������� �������� ���� ����� ��� ����� � ��������. ���� � � ��������� ������, � ������ ���������� ������ ������ ������, ����� ����.";
			Link.l1 = "� ���, ��� ������ ������� �������, ��� �� ����� ����?";
			Link.l1.go = "DeSouza_4";
		break;
		case "DeSouza_4":
			dialog.Text = "���� ����, �� ������ ��� � � ������, ������� � ��� ������ ������. ������ �� �� �� ��������?";
			Link.l1 = "��.";
			Link.l1.go = "DeSouza_5";
		break;
		case "DeSouza_5":
			dialog.Text = "����, ������ � ���� - �� �� ����. ������ �� ���, ������ �� ���-�� � ������� ��� ��� � ��� ������?";
			Link.l1 = "� ������� ���� ��������� ������ � ����� �������� ������. ���� � ����������, �� ������ � ���������� �����, ��� � ���������� ���������� � ����������. ��, ���� �� �������� - ��������� ������� � ����������� ������.";
			Link.l1.go = "DeSouza_6";
		break;
		case "DeSouza_6":
			dialog.Text = "�� ����� �����, � ����\n� �� ��, ���� ������ � ���� ����. �������� ��������� ���� ������� � ������ ��������. ������ � �� ������, ��� �������� �����������, ������ ���� - ��� ����������� ����, ����� ����� �����\n� ����� �����! ������ ������� ���� ���� ������!";
			Link.l1 = "� ������������� ���� �����������. ���� ����.";
			Link.l1.go = "DeSouza_7";
		break;
		case "DeSouza_7":
			AddQuestRecord("WhisperQuestline", "7");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			SetTimerCondition("Whisper_WarDog", 0, 0, 7, false);
			dialog.Text = "� �������� ����� ���������� ������, ������� ����� �������� "+GetFullName(characterFromId("wl_Pirate_Cap"))+", ����� ��� ������� ��� � ��� ���� ����, ����� � ����� �� ������ ������� ����. �� ������ �������, ��������� ������ �������. �� ���� ��������� ���������, ���� �� ���������, �� ������ ���������� ��� ����� ������.";
			Link.l1 = "�������� � �������� ����, ��� ��� � ����� ����������.";
			Link.l1.go = "DeSouza_8";
		break;
		case "DeSouza_8":
			dialog.Text = "������ �� ������� �����, ���� �� ��� ����� ������� ��� �����������, � ���� ����������� ������� �� ��� �����.";
			Link.l1 = "�����.";
			Link.l1.go = "DeSouza_fight";
		break;
		case "DeSouza_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.DeSouzaTalked = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "ChinamanSpeak_1":
			dialog.Text = "���� ���.";
			Link.l1 = "����, ���������� ���� ��������� �� ����. �� ���� �� ������? ������, � ���� �����-�� ��� �������� ���...";
			Link.l1.go = "ChinamanSpeak_2";
		break;
		case "ChinamanSpeak_2":
			dialog.Text = "� ������� ���� �� �����, ��������� �������.";
			Link.l1 = "����. � �� ����� �������, ������ ����, ����� ���������� � ���� �����, �� �������� � ���� �� �������?";
			Link.l1.go = "ChinamanSpeak_3";
		break;
		case "ChinamanSpeak_3":
			dialog.Text = "��� ������ �������\n�� ������ ������� ��� ���� �����. ��������� ��������� ���������� ������ � �����. ������ ������� �������, ��� � �� ������ �������\n� ������� ��� ������� �������� ���� ���, ������� ��������� ��� ��� �������� �� ������� ������� �������� ���� ��, ��� ��������� ���� ������� ������� ����������� ��� ��� �������� �����. ��� ��������� ���� ��������� ������\n������� ������� ������� ���������� �������� � ���������, ������� ����, � ���������� ���� �� ������. ���� �� � ������, � � ���������, ����� ���������, ����� ��� ��, ����� ��� ���� ��. ������� �������, ��� ��� ������ ������� �������. ������ ����������� �����, ����������� ������. ����� �����, �� ����������� ����, �� ������, � ������� ������ �����.";
			Link.l1 = "...";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSpeak_1_1":
			dialog.Text = "���� ������������� ����� ���, ���� ������� �� ��������� ������� � ���� ���� �����, ��� �� ��������� �� ������. ��� ���� ���� � ���������� ������ �������. � ���������� �� ��� � ����� ����� �������.";
			Link.l1 = "���, ������ ��� �� ����. ������ �� - ������ ���.";
			Link.l1.go = "ChinamanSpeak_1_2";
		break;
		case "ChinamanSpeak_1_2":
			dialog.Text = "����������, ��� ���.";
			Link.l1 = "���� �������� ���� �������. ���� ���������� ����� � �������. ��������, ��� ���������? ��� �� �� ������� ���-�� � ����� ������, ��� ��� � ���� � ���� ������� �������.";
			Link.l1.go = "ChinamanSpeak_1_3";
			Link.l2 = "����� ��� ����� - ����� ������ �����. ����, ������ ��� � ����.";
			Link.l2.go = "ChinamanSlave";
		break;
		case "ChinamanSpeak_1_3":
			dialog.Text = "���� ������ ��������� �������, � �����, � ������� �����, ���� ���� ��������������. ";
			Link.l1 = "� ����� ������, ����, ����� ��� ���� ������. ����� ������ ���� ������.";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSlave":
			DialogExit();
			ChangeCharacterReputation(pchar, -30);
			AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			npchar.lifeday = 0;
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			
			PlayVoice("interface\_EvEnemy1.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;	
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
		case "ChinamanOff":
			DialogExit();
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "GR_longway";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.HalfImmortal = true;  // ��������
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			LAi_SetWarriorType(NPChar);
			SetSelfSkill(NPChar, 25, 25, 25, 25, 25);
			SetShipSkill(NPChar, 15, 15, 20, 20, 40, 15, 15, 15, 15);
			SetSPECIAL(sld, 5, 5, 9, 4, 9, 9, 9);
			NPChar.rank = 6;
			LAi_SetHP(npchar, 120.0, 120.0);
			SetCharacterPerk(NPChar, "ByWorker");
			SetCharacterPerk(NPChar, "ShipSpeedUp");
			SetCharacterPerk(NPChar, "ShipTurnRateUp");
			SetCharacterPerk(NPChar, "Energaiser"); // ������� ���� ��� 1.5 � �������� �������, ����� �� � ������ �������
			
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			PlayVoice("interface\_EvShip3.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;	
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
	}
}