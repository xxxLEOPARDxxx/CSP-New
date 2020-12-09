// ��� ������ ������ �� ��������: ��� �����, ����, ������ ��� ������ � ��.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
			dialog.text = "������ ����, ������! �� �� �� ������� ���� �������, ��� ����� �� �����?";
			link.l1 = "� �� - ������� '���� ��� ���������'?";
			link.l1.go = "ShipToDomingoTavenr_2";
			link.l2 = "���, ��� �� �.";
			link.l2.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipToDomingoTavenr_2":
			dialog.text = "�� �����, ������.  ��������� �����!  ��� ���� ��� ����� �� ������ � ����.  ��������!  � �, ��� �� ����, ���� ���������.  �� ��� �� ��������, ������ �����!\n"+
				          "������� ����� � ���� ��������, �� ���� � ����� ����� ��� ���� ���� ����� � ����� �� ������.  ������� ��� ���� � ���-����, � �� ���� ����� ���� �� ����. ������ �����������, �������, ��� �� ��� ��������, �� �� ����!";
			link.l1 = "�������� ���, ��������, �� ��� ������ �� �������? � ��� �� ��������� ��� �� ���-����.";
			link.l1.go = "ShipToDomingoTavenr_3";
		break;
		
		case "ShipToDomingoTavenr_3":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
			dialog.text = "��, ������! ������! ��� ������ �� �������!  �, ������, �� ����������� ��� �������!";
			link.l1 = "��, ��� ������ ������� ��� � ������� ��� �� ��� �������. ���� ����� ��� � �����.";
			link.l1.go = "exit";
			Pchar.quest.Romantic_Brother.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother.win_condition.l1.location  = "Cumana_town";
        	Pchar.quest.Romantic_Brother.win_condition              = "Romantic_Brother";
        	Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
        	AddQuestRecord("Romantic_Line", "6");
			npchar.LifeDay = 2;
            SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ShipToDomingoTavenr_Temp":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
            dialog.text = "�, ������, �� ����������� ��� �������!";
			link.l1 = "����� ������. ��������.";
			link.l1.go = "exit";
		break;
		// ������ ��������
		case "Romantic_Brother_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "������ ����! �� ������� "+GetFullName(Pchar)+"? � ��� ������ �� �������. � ����������� � ���-����";
			link.l1 = "����� ���������� �� ����, ��� ������. ��, � ������� "+GetFullName(Pchar)+". � �������, ����������� ����� ��� ��� ��������.";
			link.l1.go = "Step_1";
		break;
		case "Step_1":
			AddQuestRecord("Romantic_Line", "7");
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 40);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddPassenger(pchar, NPChar, false);
			SetCharacterRemovable(NPChar, false);
            Pchar.quest.Romantic_Brother_port.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_port.win_condition.l1.location  = "SanJuan_town";
        	Pchar.quest.Romantic_Brother_port.win_condition              = "Romantic_Brother_port";
            // ������� ������� �����
            TraderHunterOnMap();
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_2":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "������� �� ������!";
			link.l1 = "��������, ��� ��� ������ �� � �������.";
			link.l1.go = "exit";
		break;
		
		case "Romantic_Brother_port_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = "�������. � ������ ������ �������� ��� ������.";
			link.l1 = "����������. �������.";
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			RemovePassenger(pchar, NPChar);
            Pchar.quest.Romantic_Brother_House.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_House.win_condition.l1.location  = "SanJuan_houseSp6";
        	Pchar.quest.Romantic_Brother_House.win_condition              = "Romantic_Brother_House";
            chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "", "goto", "goto4", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_Thanks":
            NextDiag.TempNode = "Romantic_Brother_Thanks";
            dialog.text = "�������, �������� ��� ������� �� ��������� ������. ��� �������, ��� �� ��������� � ������. �� ���������� ������ ����� �� ����������...";
			link.l1 = "�� ������ � ������, ������. ��� � �������. �������, ����� ���� ������ ���� ���������...";
			link.l1.go = "Step_3";
		break;
		case "Step_3":
            dialog.text = "�� ����� ���� ������� ��� ������� �������, �������.";
			link.l1 = "����������� ����, ������.";
			link.l1.go = "exit";
		break;
		//�������� ���������� � ������
		case "TalkNearHouse_1":
            dialog.text = "��������! ��� �� ����� ������ ���� ������ �� ��������� ��������! ��� � ������!";
			link.l1 = "��, ��� �! ��� ��������� ���� ����� ������! � �� �������� ����, �����, � �� �� � ���� ������ ��� �������! � ����� �������� ����...";
			link.l1.go = "TalkNearHouse_2";
		break;
		case "TalkNearHouse_2":
            dialog.text = "���� ���� �� ����� �� ��������, �������! � ������, ��� ��, ����� ������������ �� �����! �� ������ �� ������ �� ��������!";
			link.l1 = "�� ��� ������ ���� ������, �����!";
			link.l1.go = "TalkNearHouse_3";
		break;
		case "TalkNearHouse_3":		
			DialogExit();
			AddDialogExitQuest("Romantic_DeadBrother_1");
		break;
		//������ � ���� ���������� ��� ������
		case "ArrestInHome_2":
			ref rColony = GetColonyByIndex(FindColony("SanJuan"));
			if (sti(rColony.HeroOwn))
			{
				dialog.text = "������� ?!.. ��������, ��� �������, ��� ����� ��������� ������!";
				link.l1 = "������������. ������ ��� ��� ������ ��� ����������. ���� �� �� �� �������� ���� ���������...";
				link.l1.go = "ArrestInHome_5";
			}
			else
			{
				dialog.text = "������� " + GetFullName(pchar) + ", ������ ������ �� ����������!";
				link.l1 = "������, ���� ������� ��������� �������� � ���� ��������� ������. �� ��������� �������� �� ������� ���� ����!";
				link.l1.go = "ArrestInHome_3";
			}
		break;
		case "ArrestInHome_3":
			dialog.text = "� ��� ���� ��������������? ��� ��� �������?";
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = "��� � ����, ������!";
				link.l1.go = "ArrestInHome_Have";				
			}
			else
			{
				link.l1 = "� ��� ������� ������, � ��� ������...";
				link.l1.go = "ArrestInHome_NotHave";
			}
		break;
		case "ArrestInHome_Have":
			dialog.text = "������, ����������. �������, ��� ����� ������� � ������������. � ���� ������ ���� ������ � �������� �� ����!";
			link.l1 = "��������� �� �������?! ��� ��, ���� � ���� ��������� �������� � ���, ��� ��� ����� ����������� �����.";
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = "� ����� ������, �������, � ���� �������� ��������� ����.";
			link.l1 = "� �, � ����� ������, ���� �������� ������� ������������� ����������� ������.";
			link.l1.go = "FightInHouse";
		break;

		case "ArrestInHome_NotHave":
			dialog.text = "�������, ���� ��������� ����� ��������� �����������. � ������ ������ ������ � �������� �� ����!";
			link.l1 = "��������, �������, ���� ��� ����� - ����� ����� ����� � ���� ������ ���!";
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = "��� ����� ���... ������ ������ ����������!";
			link.l1 = "��... �� ���, ������, � ��������� ���������. � �� ������� �������� ���� ����������...";
			link.l1.go = "FightInHouse";
		break;

		case "FightInHouse":
			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], false);
			AddQuestRecord("Romantic_Line", "10");
		break;

		case "ArrestInHome_5":
			dialog.text = "��������, �� � �� ��� �����, ��� ��� ��. ��� ��� �������...";
			link.l1 = "�� �����, ��������� ������� ����� �������. ��, � �� ��������!";
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "31");
		break;
		//������ � ���� ����������, ������ � ������� �������
		case "AmbushBandit":
			dialog.text = "���-���... �������, �� ���������...";
			link.l1 = "���� �� ���������? � � ��� ���� ����� �������������?";
			link.l1.go = "AmbushBandit_1";
		break;
		case "AmbushBandit_1":
			dialog.text = "���� ���������, �������, ����...";
			link.l1 = "��� �������, ����� ���� ���-�� ����...";
			link.l1.go = "AmbushBandit_fight";
		break;
		case "AmbushBandit_fight":
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Romantic_Line", "12");
		break;
		//������� �����, ��� �������� ���� ������
		case "BrigAbordage":
			dialog.text = "���������! ������ ����� �� ����� �� ��� �������?!!";
			link.l1 = "� ����, �������, ��� ��������: �� � ��� �������� � �� �� ���� �� ����.";
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
			dialog.text = "��������� �����...";
			link.l1 = "� ������� �������� �������� � �� ������������� ���, ��� ���������. � ���� ������ �� ��������� ���.";
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
			dialog.text = "� �����?";
			link.l1 = "����� � ������ �� �������� ����, �������!";
			link.l1.go = "BrigAbordage_3";
		break;
		case "BrigAbordage_3":
			dialog.text = "��, ��� �� ��� ���������, ��� ���� ���������...";
			link.l1 = "��, ���������� ������� ���� ��������� ����? ��, ����� ���������...";
			link.l1.go = "BrigAbordage_4";
		break;
  		case "BrigAbordage_4":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("Romantic_TaklInCabinBrig");            
            pchar.quest.Romantic_BrigDieHard.over = "yes";
			pchar.quest.Romantic_AfterBrigSunk.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//������ � ����� �����
		case "AmbushPotroBello":
			dialog.text = "�������-��, �� ��� ���������! ����������� ���� ����� '������������'. � ��� �������?";
			link.l1 = "��������?";
			link.l1.go = "AmbushPotroBello_1";
		break;
		case "AmbushPotroBello_1":
			dialog.text = "���, ��������.";
			link.l1 = "� ���� �� �������.";
			link.l1.go = "AmbushPotroBello_2";
		break;
		case "AmbushPotroBello_2":
			dialog.text = "��� ���� �� ����... ��� �������, �� ���� - ����� ���� ������ � ���� �� ������� � ��-������ �� ��������. ������ �� �� ������ �����������.";
			link.l1 = "����� ���� �� ���� ������ �� ���-�����?";
			link.l1.go = "AmbushPotroBello_3";
		break;
		case "AmbushPotroBello_3":
			dialog.text = "�� ���� ������ ���, ��������...";
			link.l1 = "��, �����, ��� ���������� ����. � ��� ��������� ���? ����������� � ����� �� ������?";
			link.l1.go = "AmbushPotroBello_4";
		break;
		case "AmbushPotroBello_4":
			dialog.text = "��� ��� �����, �� ����� �����. ��� ��� �� ���� ���� ������ - � ��������.";
			link.l1 = "�������... � ��� ���� � ����������? ��� ����� ��� ���?";
			link.l1.go = "AmbushPotroBello_5";
		break;
		case "AmbushPotroBello_5":
			dialog.text = "��������� ��� ������� ���, ��� ��� �����, � ��� ������ ��������� - ����� ������ ��� ���������... ��, ���-�� �� �� �� ���� ���������!";
			link.l1 = "�����, � ���� �� ������� ����� '������������', � �������, ������� ������ ���� '������������' �� ���...";
			link.l1.go = "AmbushPotroBello_6";
		break;
		case "AmbushPotroBello_6":
			dialog.text = "��� � ���� ���� ��� �����������! �� ���, ��������, ���� ���� �� ��� ����...";
			link.l1 = "�������, �� �, �������, ��������� �� ����...";
			link.l1.go = "AmbushPotroBello_7";
		break;
		case "AmbushPotroBello_7":
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Romantic_TalkPortoBello");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//�������� �������� ������ � �����
		case "Rosita":
			dialog.text = "����������� ��� � ���� ����, ������. ��� ��?";
			link.l1 = "������������, �������. ���� ����� ������� " + GetFullName(pchar) + ", �������, ��� ��� ��� ������ �� ������.";
			link.l1.go = "Rosita_1";
		break;
		case "Rosita_1":
			dialog.text = "��, ��� ��� �� ��������. ��� ���� � ������� ����� ������ ��� � ���� ����?";
			link.l1 = "�������, � �������� �� ��������� ����� ������ - �������� ��������.";
			link.l1.go = "Rosita_2";
		break;
		case "Rosita_2":
			dialog.text = "�����������, ������.";
			link.l1 = "������� �������� �������� ������� ������� � ���, � � � ������������� �������� ��� �� �������.";
			link.l1.go = "Rosita_3";
		break;
		case "Rosita_3":
			dialog.text = "�������, �������, ������� �� �������� ���� �������� ����� � ����������?!";
			link.l1 = "������ ���, �������. ��� �� ���� ������� � ������ ��������� ����� �� �����.";
			link.l1.go = "Rosita_4";
		break;
		case "Rosita_4":
			dialog.text = "��, ������, � ���� �� ����, ��� ��� �����������! ���� ����������� ��������� ���������� �� ��������, ��� �������� ���� � �����, � ��� �����! �� ���� ����������� �� ������...";
			link.l1 = "������, �������, ��� ��� ��� ��������. �������, � ��������� �������� �� ��������� � ���?";
			link.l1.go = "Rosita_5";
		break;
		case "Rosita_5":
			dialog.text = "���, ��� ����� �� ����, �� ��������� �����. � ������ �� ����������� � ���, �������?";
			link.l1 = "�������, ����� �����, ���� ���� �������� ��� ��� ���������. � ��������, ��� ��� ��� ��� �������� ��������� � ������ �������� �� � ���. �������� ��, �������, �� ������� ��������� �� ��������� �����...";
			link.l1.go = "Rosita_6";
		break;
		case "Rosita_6":
			dialog.text = "������� ��� �� ���, ��� �� ������� ��� ��������, ������ " + pchar.name + ". � ���� �������� �� ���...";
			link.l1 = "������, ������� ������, � �� ���� ������ - ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1 = "location";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1.location = "Beliz_town";
            Pchar.quest.Romantic_BelizCityTalk.win_condition = "Romantic_BelizCityTalk";
			//������ ���������� �� ������ �� ������ ������
			pchar.quest.Romantic_AmbushInHouse.over = "yes";
			pchar.quest.Romantic_AmbushInPortoBello.over = "yes";
		break;
		case "Rosita_after":
			dialog.text = "������� " + GetFullName(pchar) + ", � ���� ��� ������.";
			link.l1 = "�������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
		break;
		//������ ����������, ��� �������� �������
		case "BackRosita":
			dialog.text = "��, ��� ��, ������� " + pchar.name + ". ��� �������! ����� �������, ��� �� ������ ���!";
			link.l1 = "��� ���������, ������? ��������� ��� �����?";
			link.l1.go = "BackRosita_1";
		break;
		case "BackRosita_1":
			dialog.text = "���, ���������� �� ����. �� � ��������� ���-�� ���������! ��� �������!";
			link.l1 = "��� �������? �����?";
			link.l1.go = "BackRosita_2";
		break;
		case "BackRosita_2":
			dialog.text = "����� ����� ��� ����������� �� ����� �� ���������, � � ��� ��� �� ����� �� �����!";
			link.l1 = "������� ������, � ������ �� ����������� �� ������!";
			link.l1.go = "BackRosita_3";
		break;
		case "BackRosita_3":
			dialog.text = "�� ������� ��� ������ ��������!";
			link.l1 = "������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "BackRosita_after";
			pchar.RomanticQuest = "SeekIsabella";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1 = "locator";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator_group = "quest";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator = "detector1";
			pchar.quest.SeekIsabella_exitTown.function = "SeekIsabella_exitTown";		
			AddQuestRecord("Romantic_Line", "21");
			//�������� ��������
			sld = GetCharacter(NPC_GenerateCharacter("ServantGirl", "girl_6", "woman", "towngirl", 5, SPAIN, 30, false));
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_ExitTown", "goto", "goto17");
			locations[FindLocation("Beliz_ExitTown")].DisableEncounters = true; //��������� ��������
			//�������� �������� � �����
            sld = GetCharacter(NPC_GenerateCharacter("Bandit", "officer_6", "man", "man", 35, PIRATE, -1, true));
            FantomMakeCoolFighter(sld, 35, 85, 75, "topor2", "pistol3", 60);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto4");
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", true); //�������� �� �������
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", true); //�������� �� ��������
			pchar.quest.Romantic_BanditIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Romantic_BanditIsDead.win_condition.l1.character = "Bandit";
			pchar.quest.Romantic_BanditIsDead.win_condition = "Romantic_BanditIsDead";
		break;
		case "BackRosita_after":
			dialog.text = "�� ����� ��������?!";
			link.l1 = "���� ���, �������, � ���...";
			link.l1.go = "exit";
		break;
		//���� �������� ������� ���-���� ��� ���������
		case "IsabellaIsDead_Beliz":
			dialog.text = "�������, �� ����� ��������?";
			link.l1 = "��, ������, �����. �� �� ������ � ����� �� ��� ������ � �������� �������...";
			link.l1.go = "IsabellaIsDead_Beliz_1";
			NextDiag.TempNode = "IsabellaIsDead_Beliz_after";
		break;
		case "IsabellaIsDead_Beliz_1":
			dialog.text = "�������� �� ����... ��� ��� �� ��� ���������! ������ ������� �� ����...";
			link.l1 = "������, � ������ �� ����!!";
			link.l1.go = "exit";
		break;
		case "IsabellaIsDead_Beliz_after":
			dialog.text = "�������, � �� ���� ��� ������, ��������.";
			link.l1 = "��������, ������...";
			link.l1.go = "exit";
		break;
		//����� �������� �������� � ������
		case "SavedIsabella":
			dialog.text = "��������!!";
			link.l1 = "������!";
			link.l1.go = "SavedIsabella_1";
		break;
		case "SavedIsabella_1":
			dialog.text = "�� � �������! ����� �������!";
			link.l1 = "����, � ������, � ������ �����...";
			link.l1.go = "SavedIsabella_2";
		break;
		case "SavedIsabella_2":
			dialog.text = "��� �� ���������? ��� �� ���������? � ��� �������?";
			link.l1 = "������, ���� ������� ���������. � ������� ������ - �� ���� ��� ���...";
			link.l1.go = "SavedIsabella_3";
		break;
		case "SavedIsabella_3":
			dialog.text = "��������! ����� ��� ���� �������� �����������, ����� �� ���������� ��������� ����������!";
			link.l1 = "��������� ���� �����. ���� ����� � �������� �� ����� ��� �����-���������... ��������� ����� � �� ����, �� ��� ���� � ���� �� ������.";
			link.l1.go = "SavedIsabella_4";
		break;
		case "SavedIsabella_4":
			dialog.text = "��������, ������� ���� ������ �������-�� ����������?";
			link.l1 = "��, ������, ��� �������...";
			link.l1.go = "SavedIsabella_5";
		break;
		case "SavedIsabella_5":
			dialog.text = "� ����� ��� �������� ����� ���� ������ ������... ��������, ���� ������ �������, ��� � ���� ���� ����� ����������!";
			link.l1 = "��, ������, ��� ������������� ���! ������, ���� ����� � ���� �������� � � ������ ��������, � ������ ����� �� ����� ����������� ����� ���������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";			
			AddDialogExitQuest("Romantic_DelivToRosita_2");
		break;
		case "SavedIsabella_after":
			dialog.text = "�������, �� ������������� ��������� �������!";
			link.l1 = "��, ������, ������� �� ����������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
		break;
		//��������� �� �� � �������� � ������
		case "AmbushInChurch":
			dialog.text = "�������, ���� ������ �� ����������!";
			link.l1 = "��������� �����, �����������...";
			link.l1.go = "AmbushInChurch_1";
		break;
		case "AmbushInChurch_1":
			dialog.text = "� ���������, ������� ��������, ���, � �������� ��� ����� ������ ��������...";
			link.l1 = "��� ��� ��������: ��������� �����! ��� ��� ���, ��� ������ �������? ��� �� �������� � ����� ������!";
			link.l1.go = "AmbushInChurch_2";
		break;
		case "AmbushInChurch_2":
			dialog.text = "���, ����� �� ��������� �����...";
			link.l1 = "����!..";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_1");
		break;
		//����� � ������� ����� �������� ��������
		case "IsabellaIsDead":
			dialog.text = "������� " + GetFullName(pchar) + ", ���� ������ ���. ����� �������? �� ��� ����������� � ���������?";
			link.l1 = "������� ���� ������, ������. �������� ������, �� ����� � ������ ����� �� ������. ���������� ���� ������� �����...";
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = "�, �������, ������ ��������!! ��� ��� ��������, �� ��� �� ������� � �����.\n"+
				          "����� ��������� �� � � ��������, ��� �� ������ �������-�� ���������� � �������. �� �� ������, ������, �� ������...";
			link.l1 = "��, ������, ��� ��� ������!..";
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = "� ������� ���, �������... ��������, � ������ ��������� ���� ������ - ��� ����� ����� �����...";
			link.l1 = "��, ������, �������...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		case "IsabellaIsDead_after":
			dialog.text = "�������, ��� �� ������?";
			link.l1 = "������, ������, ������ ����� ��������� ������ ���� ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		//����� � �������, ���� �� ������� � ������
		case "IsabellaIsMyWife":
			dialog.text = "������ " + pchar.name + ", ���� ��� ������! �� ������ ������������!";
			link.l1 = "��, ������� ������. �� ����������� � ���������...";
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "��� ���������, �������. �������� �������� ��������, ������ ���� ������� ���������!";
			link.l1 = "���������� � ���� ��������. � � ���������� ���� � ���������� �� �����, � �������� ��� � �������� � ����� ���� �������...";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "������ " + pchar.name + ", �� ��������� ������! �������� ��������... ������, ���� � ��� ����� � ��� ��������, �����������, � �������, �� ������ ���������� �� ��� - ���� ���� ������.";
			link.l1 = "������, ������ ������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = "���� ��� ������, ����� " + pchar.name + "!";
			link.l1 = "�������, ������� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		//�������� ����� ��
		case "IsabellaIsWife":
			dialog.text = NPCStringReactionRepeat("������������, �����. � ��� ���� ��� ������! ��� �������� ��������?", 
				"�� ����� �� ���, �����? �� �� ������ ��� ����������.", 
				"�����, ��� �����?! ������ ������ �� �� ���� �� ��������!", 
				"����������, �������, ���� �� � ���� ����� ������, �� ��� ���� ������ ��� ������ ��������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������������, ������ ������. �������� � �������.", 
				"��, �����, ������ ���... �������� ����, ������, �� ���� ��� ���������...", 
				"��? �� ����� �����...", 
				"���, ������, ���� � - ����� �� �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("IsabellaIsWife_1", "none", "none", "none", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "IsabellaIsWife";
		break;
		case "IsabellaIsWife_1":
			dialog.text = "�� ���-�� ������ � ���� ������, �������?";
			link.l1 = "�� ���, ������, ������ ����� ���������.";
			link.l1.go = "exit";				
			if (pchar.RomanticQuest == "over")
			{
				link.l2 = "������, ���� �� ���� ��� �������... �������� ������� ����� � ���� � �� ������� ����!";
				link.l2.go = "HorseCheck";	
				break;
			}			
			if (pchar.RomanticQuest == "TheDoosIsClosed")
			{
				link.l2 = "������, ���� �� ���� ��� �������... �������� ������� ����� � ���� � �� ������� ����!";
				link.l2.go = "TheDoosIsClosed";			
			}
			sld = characterFromID("Isabella");
			if (CheckAttribute(sld, "angry")) //���� �������� ����� �� �����
			{
				if (sld.angry.name == "NewLife_Budget_Pay")
				{
					link.l3 = "�� ������, ������, � ���� ��� � �������� �������� ���� � �������� ������� �� ���� ���������...";
					link.l3.go = "Budget";			
				}
				if (sld.angry.name == "NewLife_KnowPirates")
				{
					link.l4 = "�� �������������, ������, �������� �����-�� ������� ������ � ���, ��� � �� ������ ������ ���������, ��� ������ ����� ��������...";
					link.l4.go = "KnowPirates";			
				}
				if (sld.angry.name == "NewLife_Present")
				{
					link.l5 = "������, ��� ����� ����... � �����, �������� ������� �������� �� ����, �� ����� �������� � �����. ��� ���!";
					link.l5.go = "Present";			
				}
			}
		break;
		case "TheDoosIsClosed":
			dialog.text = "�������... ��, ������, �������� �����������, �������. �� ���, ����� �� ���� ����?";
			link.l1 = "��, �� ��� �������... � �����-��, ��. �� � �� �����, ������, � ��� ������ - ��� ���������� ������ � ����.";
			link.l1.go = "TheDoosIsClosed_1";	
		break;
		case "TheDoosIsClosed_1":
			dialog.text = "� �������, �������... �� ��� ��, � ����� ������� ��� ����. ������������� �����, ��� ����� ���������...";
			link.l1 = "������, �� ������ ����!";
			link.l1.go = "TheDoosIsClosed_2";	
		break;
		case "TheDoosIsClosed_2":
			dialog.text = "�� ����������� ����, " + pchar.name + ". � �� ��� ������������ ������� �� �� � ���� ������ ����.";
			link.l1 = "������, � ����������� �������� ������ ���. �� ��������...";
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "30");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			pchar.RomanticQuest = "OpenTheDoosOfHouse";
		break;

		case "Budget":
			dialog.text = "���, ����� �����?";
			link.l1 = "��, ������. �������� ������� ���� ��������� ��� �������� �������������, �� � ����, ��� �����, �� ���� ����� �����.";
			link.l1.go = "Budget_1";	
		break;
		case "Budget_1":
			dialog.text = "��, �����... �� �����, �������� ����, ��� ����� �������. ������� �� � ������� ��������: ������, �������� � ������ ������. ��� ����� ����� ��� ����� �, �������, �������...";
			link.l1 = "�������, ��� � ������! ������� ����, ������. �� ��������.";
			link.l1.go = "exit";	
		break;

		case "KnowPirates":
			dialog.text = "��, �����, �� ���� �������� �� ������, �� '�� ������' - ��� ���?";
			link.l1 = "��, ���������, �������� �� ���� ����, � ��� ��� �������� ������? ���������, �������!";
			link.l1.go = "KnowPirates_1";	
		break;
		case "KnowPirates_1":
			dialog.text = "��, �������... ������ ��, �������, ���������� �� ��� ���?";
			link.l1 = "������ ���, ������, ���������� ������ ����������� ���� ������������ � ���������!";
			link.l1.go = "KnowPirates_2";	
		break;
		case "KnowPirates_2":
			dialog.text = "����... �� ��� ��, ����������� ���� ������������ ��������� ������ ��������.";
			link.l1 = "�� ��� ����������, �� ���?";
			link.l1.go = "KnowPirates_3";	
		break;
		case "KnowPirates_3":
			dialog.text = "������ ������ � ��������. � ��, ��������, �������� ������, �����, �����, ������� ���������, �� � ������� ������ � ������� � �������...";
			link.l1 = "��, � ��� �����!.. ������� ����, ������, � ��� � ������, ������! ������...";
			link.l1.go = "exit";	
		break;

		case "Present":
			dialog.text = "� ��� ���������?";
			link.l1 = "�� ���, ������ ����������... � ��� ����� ������� �� �������, �� ����������� ������ �� �������.";
			link.l1.go = "Present_1";	
		break;
		case "Present_1":
			dialog.text = "��, ������ ���������... �����, �� ���-�� �� �������������.";
			link.l1 = "�� � ���-�� ��������� � �����, ��� ��� ��������� �� �������... � �����, ����� ���������. � ��� ������ ����...";
			link.l1.go = "Present_2";	
		break;
		case "Present_2":
			dialog.text = "��� �� ������� �����, �������! ��� �� ��� ������� �����?!";
			link.l1 = "�������, ��� ����������, �� ��� ������ �� ������?";
			link.l1.go = "Present_3";	
		break;
		case "Present_3":
			dialog.text = "������ ��� ���: �������� ��, �������, �������. �������� ��� ������� ��������� � ���� ���������� �������. � �����, �������� �������...";
			link.l1 = "��, ������ ������, ��� �� � ��� ��� �����! ������ ������ �����-�������. ��������...";
			link.l1.go = "exit";	
		break;

		case "HorseCheck":
			dialog.text = "��, ��� ��� ��������. � ��� � ���� ������� ���������, ������� - ��� ���� ���������� � ������������� �������.";
			link.l1 = "��� ��� �� ���� �����? �� �� ��� �� ���� ������� ����������?";
			link.l1.go = "HorseCheck_1";	
		break;
		case "HorseCheck_1":
			dialog.text = "���� ���������� ��-�����, �� ������ ������� �� ������� ��������.";
			link.l1 = "������ �� �������, �� ��� �� ��� ��������?";
			link.l1.go = "HorseCheck_2";	
		break;
		case "HorseCheck_2":
			dialog.text = "� �� �� ������? �� ����� � ��� �����, � ��� ����.";
			link.l1 = "��, ������ ��� �����.";
			link.l1.go = "HorseCheck_3";	
		break;
		case "HorseCheck_3":
			dialog.text = "��� ����� ���� ������ ������ �� ��������, ������� ���! �������� ����� ����� ��������, �� ������ - �������!";
			link.l1 = "����!! � ��� �� ������? ���� ���������!";
			link.l1.go = "HorseCheck_4";	
		break;
		case "HorseCheck_4":
			dialog.text = "�� ����� ����������, ���������� ��������� �������� ����� ��� ����������. ��������, �������...";
			link.l1 = "��... ��������, ������...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "HorseCheck_Bue";
			CloseQuestHeader("Romantic_Line");
		break;
		case "HorseCheck_Bue":
			dialog.text = "� �� ����� ����� � ���� ��������.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "HorseCheck_Bue";
		break;
	}
}
