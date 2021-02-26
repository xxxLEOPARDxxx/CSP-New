void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

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
				LAi_LocationFightDisable(locLoad, true);
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "����!";
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
					dialog.text = "� ����� ��� ���� ������ ���� ������ � ��������. ��������� ��� �� �������, �� ����� � ����������, ���� ���������� �����-���������.\n���� �� �� ������� ���������. ������� ����, ������ - ����� ������� �����, � ���� �� �������� ��������. ��� �����?";
					link.l1 = "�� ���� ����. ����� �� ���� ����������� ����� �������?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}
			
			if (npchar.id == "AntonioDeSouza")
            {
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "���� ��, ����� ���������� '���������' ������ ��� "+GetFullName(characterFromId("wl_Pirate_Cap"))+". �������� ���, �����, �� ������ ����� ��� �� �����?";
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
					dialog.text = "�� ����� ��������� �� ��, ��� � ���� �������, ��� ��� ����� ������� ��������. ���� ������� �� ��������, �� ���, ����������?";
					link.l1 = "�� � ����������� ���� �� ������, ��� ������ �������������.";
					link.l1.go = "ADS_3";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "��?";
					link.l1 = "��� ������ ��� �������.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "��, ���-�� �������� � �������. �����, �������, ������ ���������. ������ �� �����, ��-��.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
            {
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "���, � ��� � ������� ������� ��������� ��������! ������ ��������?";
					link.l1 = "�� ���, ��������� �� ����������.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					PlayVoice("VOICE\Russian\EvilPirates02.wav");
					dialog.text = "�������? �� ������� ����� ����������� ����� �� ��������. �� ������� ��� ����� ����������� �����. �� �� ���� �� ���� ��� ������?";
					link.l1 = "����! �� ����, �������� ����� ��������� �� ������ ��������� ������������� ��� �������. ��� �� ������ ������?";
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
            {
				dialog.text = "��� ��� �������? ������ ����� � ���� ��� ����� � ������?";
				link.l1 = "�� ������� �������� ������ �������, ��� ������� ����� � ���.";
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
			NextDiag.TempNode = "First time";
		break;

		case "Jim":
			dialog.text = "����� ����, ��� �� ����������� � ������, ����� �� ������� ���� �������� �� ��������. �� ������ � ������ ����. � ���� ��, � ��� �� ������� �������� ����� - ����� ������ ������� ��������, ����� ��������� ������ ���������� ������, ������� �������� ��������� ������������ �� �����. ����� ������� �� �������� �������� ��� � ����� ������� ������. ";
			link.l1 = "������, ��� �������� ���� ��������. � ����� �� ��� ��������� ���������?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "��������.  �� ��� �� ������� '������ ������' ������. �� ���� ����� ������ �������� ���� ���� ������, ��������� � �����. � ������� ��� ���������� ���� ��������� ��������� �������, � ������ ���� �� �����-�� ������� ����������� ��������, ���� ������� �������. ���� ��� ����� ��������� - ��� ���� �����������. ";
			link.l1 = "������� ������� �� ��� ������. �������, ����� ��� ���� '�����' - ��������. �� �� ���� ��� ������ �� ����������. � �������� ����� ���������, ������ �� ������� ��, ��� ���������� � ���������� ��������.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			dialog.text = "������, ���������. ���� �������� ���� �� ����, �� ��� �� ����� ���� ����� �������� ���������. ��, ���� ���, �������, �� ������ �����. ";
			link.l1 = "������. �� � ��� ��� ��������?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "�� ����� �����, � �����. ������� � ������ � ������� � ������. ";
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			
            ref mc = GetMainCharacter();
            mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
            mc.Ship.name="������ �����";
            SetBaseShipData(mc);
            mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
            SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,10);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,100);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);
			
			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			AddQuestRecord("WhisperQuestline", "3");

		break;
		case "Jack":
			dialog.text = "������ ��� ��? ��-��! �� ����, �... ����� ����, �������. �����, ����� ���� ��� ������� � ����������.";
			link.l1 = "��� ���� ��. ��� ��� ��� �����������.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "�� �������� �� ������. ��� ����� � �������, ��� ������ �� ��������� - ������� ������ �� '������ �����'. ����, ���� ��� ����������� � ���� ���������. � ����� ������, � �������� ����� �������. �� ������ �������� �� ��� ����� ��� ��������. ���������, �� �� ����.";
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
			dialog.text = "���� � ������������, ���� ���������� ������� �� ���� ��������. ��, �����! �� ��� �����, � ��� ����� ��������� �� � ������.";
			link.l1 = "��� � ��� ������.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "����� �����������. � ����������� ����.";
			link.l1 = "������.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "����, � ���� ��� ���� ������, ��� � ��������� ��������! ��� ��� � ���� ���������, ������. ��� �� �� ��������� �� ��������, ���� ������� ���� �� ������� ����� ���������, ���� �� ����� �������� � �������� ������ ������.";
			link.l1 = "� ��� � ����� �� ���������?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "�� ����� � ����� �������, � �������. ��� ������� ������ � ���� �� ������. ����� �� ����� �� �������� ���������. �� ���� ��� ������� � ������ ����.";
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
			Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlayVoice("People Fight\rifle_fire1.wav");
			LAi_KillCharacter(npchar);
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
			link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard":
			dialog.text = "����, ������ �� �� ���� �������. ���� �� � ����� �������� ���� �� ����� - �� �� ��� �� ����� �� ���� �� ������.";
			link.l1 = "������, ��� � ������ �����������.";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "��� ��� ����� ������ �� ��� ��������. ����� �� ������ ������� � ��� ���� �������, �� ������\n� ��� �������, ����� ���� ��� �� �������. ���� �����, �� ������ �� �������? � � ��� �� ����������� � ������ �������.";
			link.l1 = "��� �����-�� �������������� ������? �� ���� ���������, � ����� ����������, ���� �����?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "��� ������� ������. ������� ������������ �����������. � ���� ������� ����� ���� ���, ���� �� �� ������� �����, ��� ����������.";
			link.l1 = "����, �� � ������ �������� ��� �������. ����� ����?";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "���� ����� �� �������� � ������. ��������� ������ �������� �� ������, �� ��� ��� ������ ��������� ����� �����, ��� ��� ����� �������������. ���� ������������, ��� ���� � ������� ������� �� ������\n��� ������ ������� �� ����������, �� ������� ��������� � ������ � ������, ��� ��� ������ ���� ���� ����������. �� ��� �����, �� ������������ � ��������, ��� ��� ���� ��������� ����� �����������\n����������� � ��������� ����������, ������-��������. ����� ������� �� ������, ������ ������ �� ������ �����, ����� �������, ��������� ����� � �����. ��� �� ��� ������ �� ������� ������� ������������, ���� �� �� ������� �� ����� � ���� ������ ������ ��������. ����� ��� �� ����� ����������, �� ��� �� ��� ���� �� ���� ���������� ������, ��� � ���� ������.";
			link.l1 = "���� �� ����, ����� �� � �����-�� ���� �������������. �� ��������� ������! ���, ������ � ����� ����� ���� ��� �������.";
			link.l1.go = "IncqGuard_4";
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "�����, � ������.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "�� ��� �������. �� �����, �� ��� ������? ������ ��������, ����� ������ ������. �� ����� �� �����.";
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
			link.l1 = "� ������ �� ��������. ��������� ����� ������ ����� ������ ����� ����� ��������������, ��� ������ �����. �  ��������� ����� �� ����� �������� ����� ���������.";
			link.l1.go = "ADS_1";
		break;
		case "ADS_1":
			dialog.text = "�� ��������, ��������? � ��� �� ���� � ����� ������ ������������ � ����� �������?";
			link.l1 = "������, ����������� ���� ���� ������������. ����������, �� ������ ���������� � "+GetFullName(characterFromId("wl_Pirate_Cap"))+" � ��������� � ���� ����������, ��� ���� ��� ���. � ������ ���, ��� ��� �������� � ������ ���� �����, � ����� ������� ������.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_1":
			dialog.text = "���, ������. �� ������� ���� �� ������? � ������� �� ������ � ����������� �� �������. �� �� ��� ��� ����� � '������� ���������' ����������\n��� �������. ��� ���������� ��������? �������!";
			pchar.Whisper.DeSouzaHits = 0;
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
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 15.0);
		break;
		
		
		case "PC":
			dialog.text = "��� � � ���� ������ ����������! ��� ����?";
			link.l1 = "������.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			dialog.text = "��, �� ��������� �� ���. ��� � ���� �� ������� ��������������. ��-��, �������, �������� ����� ����� ��������� ������ � ����, � ���������� ��� �������. ����� � ��� ����������.";
			link.l1 = "��� ������ � �� ������!";
			link.l1.go = "PC_fight";
			link.l2 = "������, ��� ����� � ��� ���� �� ������.";
			link.l2.go = "PC_nofight";
		break;
		case "PC_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetCheckMinHP(Pchar, 1, true, "Whisper_PC_CheckHP");
            DialogExit();
		break;
		case "PC_nofight":
			Pchar.model="PGG_Whisper_0_NoHat";
			DoQuestFunctionDelay("WhisperHold", 0.5);
            DialogExit();
		break;
		case "PC_2":
			dialog.text = "������� �����������. �� ��� ��� ������ ������ �����, ��������� � ���� ������� ��������. ��������� ������� � ��� � ����������� �����. ��� ������ � ������ ������ - �� ��������. ����, � ����� ������� �� ������ �� �����?";
			link.l1 = "� �� �� ���� ����. � ���� ����� ��� ������.";
			link.l1.go = "PC_2_1";
		break;
		case "PC_2_1":
			dialog.text = "�� ��������, ��� ��� ������� �� ��� �������? ���, ���� �����, �� ������ �������? ����� �� ������� �������������\n������, � ���� ���� ���� ��������, ������� ������ ���� ����������� - ������� �� �����. ��� ����� ���������� � ��������\n�� ����� ������ ��� �������� ������� � ��� ����������. ��� ��� � ���� �����, ��� ������ ����������, �� ������ ���������� �����\n� ������ � ���� ������ ���������������� ������, � �� ��������� ���� �� ��� ����� � ��������������� ������� ������� �� ������. ��� �������� ��� ���� ����, ����� ���������\n����� ���� �����������, ��� �� ����� ������� � �����, ����� ������. � ����� ������ �����, ������ ����� - ����� �� ������.";
			link.l1 = "����� ������� ������, � � ���������� ������� ����!";
			link.l1.go = "PC_2_2";
			link.l2 = "������� �� �� ������ ������������?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "� ���� ������ ��� ����\n�����, �������. ���� �� ��������, � ���� ���� ��������� ���� ����� ������������� � ������ �� ����� �������� ������� � ����� �����. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "������...";
			link.l2.go = "PC_2_exit";
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
			DoReloadCharacterToLocation("Ship_Deck_Low","goto","goto5");
			PChar.quest.WhisperTeleport.win_condition.l1 = "location";
			PChar.quest.WhisperTeleport.win_condition.l1.location = "Ship_Deck_Low";
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
            link.l1 = "��������, �����, ��� ������� �������� � ����� ���������. �������� ����.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "�� ����� �� ������ ��������, ������ ��� �� ����� �������.";
            link.l1 = "��������, �����, ��� ������� �������� � ����� ���������. �������� ����.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "��������? � ���� ������ ������ ���������� ���������, �������� �������� �� ���� ����������\n������ �� - ������������ ���������? ������� ���, ��� ���� ��������?! � �� ���� ������, �� ������ ���� � ������� �����, ��� ������ ���� ������...";
            link.l1 = "������� ��� �����������. � - ��������� ��������. ������ ������ �� �� ������, ������� ���� �������.";
            link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "��� �� ��� ��������. �� ����� ���� ��, �� � ��� �� - ��� ����� � ��� �� ������. ������ �������� �����������, � ��� ���������� �� �������? ������ �� ��������. � ��� ������� �� Omnitech � ����� ��� �� ������ ������� �������.";
            link.l1 = "��. � ������ �� �������, ��� '�������� ������' - �� ������ ���������.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "�� � ��������! �� ��� ����� �����, ��� � ����! ��� ���������, ��� ��������� ���� ����������� ����� � ����� ����� - �������! ������� � � ����� �������� �� �� ���.";
			link.l1 = "�� ���� �� ����� ��� ���������� � Omnitech?";
            link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "�����, ����� '�����' - ����������� � ������ ��������. �� ��� ��� ���������, ��� - ��� ����������. �� ��, �� �� �������� ������ ����� ���������������� ������������� ������������� ����������� ���������� �� ���������� ���������� - ����������� ����������. �� ����� ���� ��� �� ������� �����. ����� � ������ ������ �������, ������ ������������������ ��� ���� ������� ������������ �����, ������� �� ����� ��������� �� ���� ����.";
			link.l1 = "��� ���� ���������� ����� ������������ ������ �������?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "� ��� ��� �� ��� ���������� ������� ��������� ��������. ���� ��������� � ������� � ���������� ��� ������������ ��� �������! ���� � ������ ����� ������, ��� ��� ����� ����, ��� ��� ������� ������ ������������� �� ���� �������� � ����������, � ��� ���� ������� ���� ����� ��������� ��� ��, ��� ���������� � ���� ������.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "� ������ ���� �������. �� ����� ��� ��� �����, ��� �������� � ��������� �������������. � � ������ ����� �� ���� �����, �� ������ �� ��, �������� ��� ����������� ����� ���� ����, ��� ���!";
			link.l1.go = "CS_bad";
			link.l2 = "���� ��� ��������� � ������ ������ ��, ��� �� ��������, �� ������� �������� �� ���������� �� �����. � ����� �� ������� ������ ���������� � ����� �����. ";
			link.l2.go = "CS_neutral";
			link.l3 = "����, � ���� �� ����... ��� � ����, ������� � ����� ������. � ����� ���������, ��� �� ������.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "����� �� �� ��� ���� �������.";
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
			dialog.text = "� ���� �� �� ����� ���� ����� �� ��������� �����, ��� ��� �������� ��������. �� ���������� ����� ������ � ����. ���� ���� ������ ��������� ���� � ���� ����� ������� ����, �� ������ ����� � ���� ����� ��� ��� ����� �� �� ������ ������� �����. � �� ����� ��������. � ����, � ������ �������, ��� ���� ����. ";
			ChangeCharacterReputation(pchar, +100);
			link.l1 = "��� �������, ��� ��, �� ��� � ���� ������ �����������. �� �������� �� ����, ������� ������ �� ����. ������, ��������� �� ������� ��� ����������.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "������ ���� �������� �� ������ ������. ��� ������� ����������, ��� �� ���������� �� ���� �����. � �� ����� ��������� �� ��������, ��� ��� ���� �������� ����������� � ���� ��������������.";
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
	}
}
