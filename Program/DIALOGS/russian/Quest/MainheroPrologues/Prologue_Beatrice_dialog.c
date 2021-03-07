void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			pchar.quest.SharpAfterTreasure.win_condition.l1          = "location";
			pchar.quest.SharpAfterTreasure.win_condition.l1.location = "Shore57";
			pchar.quest.SharpAfterTreasure.function                  = "SharpAfterTreasure";		
			dialog.text = "��� ��� �� ��� ���, ��� ���� � ���� �����.";
			link.l1 = "������..!? � ��� ��? � ���� � ������ ��� ����, ��� � ��� ���-�� � ���� �������?";
			link.l1.go = "2";

			NextDiag.TempNode = "First time";
		break;

		case "2":
			dialog.text = "�� �������. ��� ������ �������� �� ������, � �� �� ��������. � ������ �������� ����, ���� �� ����, ��� �� ���� ��������. ��� � � ��������.";
			link.l1 = "������, � ������� �� ����, � ���� �� �����, ��� � ����� ���� �����, �� �� ����������. ������, � ��� �� ���� ���� ������?";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "� ������ ������� �� ����� � ���� ������� ��� ������, ��� ��� �� ���� �������.";
			link.l1 = "� ��� �� ������, ��� ��� � ����� �����? ������ �����������.";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "��������! � ���������� ��������� ���� �����, � �� ���������, � ������ � ��� ������!";
			link.l1 = "����...";
			link.l1.go = "Exit_fight";
		break;

//grotto - dialog 2

		case "5":
			LAi_SetCurHPMax(npchar);
			LAi_SetPlayerType(PChar);
			dialog.text = "� �� ������� ����. ������ �� �����������? �����, �������� � ����!";
			link.l1 = "���� �� � ����� ���� �����, � �� ��� ��� ������. ���� ��� ������������� �������, ��� ��� ������, ������ �� ������, ��� � ����� ���� �����. � � ���� �� �����, ��� ��� ������ ����.";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "������, � ������. �� ��� ����� � ��������� ��������� ��������, ������� ��� ��� �������� ���� �������� �����, ��������, ��� ������ ����� ���� ��� �������. ������� ����� ������ ����� ����� ���-�� ������ � ���� �����, ���� � �������� � ��������� � �����-�� �������� �������. � ������ ���������� ������������� �������, � ������� ����� ��������, ������� ���������, ��� �����, ��� �� ������������ � ������������ � ���������� ���-�� ������ ������������ ������� �����. � ��������, ��� ��� �� ����� ��� �����, � ��� ������ �� ����� ������ ��������. ��� ��� � ������ ��������� ���� �� ����� � ����������, ���� ��� ���� ��������.";
			link.l1 = "�����. �� �� �������� � ����� - ���� � ������������� ����� ������ �������� �����, ��� ����, ��������� � �������, ���� ��������. ��� � � ���� ������� ��� �������, ������ ����� �� �������, ��� � �� - ����. ���� �������� � �� ����� ���� ����� � ���� �����������, �� ���������� ����������� ������, ������. ������� ��� �� ���� ������������� ��� �� ������� ��������� ������ ��� ������.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "�� ���� ��� ������, �� ����������, ��� �� - ���...";
			link.l1 = "�� �����. � ����� �������, ��������� ��������. ����, ��� ��� ��������� ����������� ��������� ������ ��������� ����������, �� � ��� ����� ��� ���� ������.";
			link.l1.go = "8";
			link.l2 = "���� ����. �����, ������ ��� �������� ���� ����� - � �� ���� �������� ������� �������� ����� ����������� � ���-���� ����� ����, �, ����� ��, ����. ���� ����������� ���� �������� �������.";
			link.l2.go = "Exit kill";
		break;

		case "8":
			dialog.text = "��... ������-��, ���� ��������, ��� ��� �� ������ �� ����������. � �����, ��� ��� ���� ������ ��� � ���������� - ����� ��� �������� ����� ���� �����, ����� ��������� ����. ��������, ��������� � ����� �� �� ����������, �� � ��������� ��� ��������. �������� ��, ��� �� ������� ������� �� ��� �������� ����� � ������ �������.";
			link.l1 = "��, ������ �� �����. ���������, ����� �� ��, ����� �� ������� ���-�� ��������� �� ���� ���� �������. ���� �� �� ������ ������� ��� ��� �� ��������, ���� ����� ���� ��������...";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "�� ����, ����� � �� � �����... �� � ����, ����� �� ��� ������� ��� ���������. ���������, ��� �������, ��� ������� ��� ��� �������� �����, ��� ��� ��� � ��������� �������. ������, � ���� ���� ����� - ������� �� ������� ����� �����������, ��������� �� �������� ���� � ������ ������������ ������� �����, ��������� ��������� ������ ������� ��� ����� �������. �� ������� ��� �����������. ��� ������ ��������������� ��� ��� ��������.";
			link.l1 = "����������, ��������... ������� �����, ��� �� �����. ���������, ����������� �� �� � �� ����������? ����� ����, ��� ������ ����������� ���� �����, �������.";
			link.l1.go = "10";
			link.l2 = "��� ������, ��� � ��� ��������� � ���� ����, ������������� ����� ��������. ���, ��� ������� ����� ��� ��������� � ���� ������, ��� �������. ��������� �� ���� �� ��������� � ������, �������� ���� �����.";
			link.l2.go = "Exit kill";
		break;

		case "10":
			dialog.text = "�� ������ �����������, � ����� ��� ��������, �� ��� ����� ������� ���, ����� ���� �� ���� ������. 20 ��� ����� �� ������ ������ ����, ����� ��������� �������, �� ���� �� ��� ����� ������ ��� ��� ����� ������. ���� ���� ��� ���������� ������������� ������ ������, ������� � ���������, � ��������� � ������� ���. ��� ���� ����� � ��� ���, � ������������ ������� ��������� ������� ������ � ����, ����� �������� ��� ������� �������, �������� �������� ������������ ���������. �� ��, ������, ������������ ���, � ������� ���, ����� �� � ����� ����� � ������������, ����� ���� �� �����, � ������������ ��� ��������� � �����, ����� �� ��������, � ��� ���� ����� ������������ ������.";
			link.l1 = "��, ��� ������� ������� �����������. ��� ���� ����� � ��� ������, ��� ��� ���� - ����� ���� ��������� �����... �������, �� ������� '������������ ��� �����' - �������, �� �����, ����� ��...";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "�������! �� �������� ������� ������ ��� ����, ����� �� ����������� ����� � ����� ��� ��������� � ������� - �� ��������� �����, ����� �� ��������� ��, ��� �� �����, ��������� � ����� ��� �����. � ��� ����� ���� �����! � �� ����, ����� �� � ��� �������, � ���� �� ����, �������� �� ��� ������, �� �, ���� ������, ��������! � ��?";
			link.l1 = "����������... ������� ������, ����� ��� � ����������� ���������. � � �����, ��������!";
			link.l1.go = "Exit grotto continue";
			link.l2 = "�� �� �� ��������� ������� ��� ������ ��� ����� � �������� ������������ ������ � ����������, �� ����� �� ��������, ��������� � ��������? ���, � ���� ������������ � �� ����� ��������� �������� �������. �������� ���� �������� �������� ��� ���� ����������, � � ������ ����.";
			link.l2.go = "Exit half";
			link.l3 = "���� ���� ����� ���� �����, ����� ��� �� �������� �� ������� ���� ����. ���� ��������� ��� ������!";
			link.l3.go = "Exit kill";
		break;

//grotto - dialog 3

		case "12":
			dialog.text = "������, ��� ������� - ����� ��������, ��� � ���� ���� �����...";
			link.l1 = "��... ������, � ��� ������ ������� ����� ������?";
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = "������ ������, ������� �� ����... �� � ���� ���� �� ������� ���-��� �������� � ���� ����. � ����� �������� ���� ����� ��������� ������� ������� ������������ - ��, ������, ��� ������� ���������� ���� � ���, ��� �������� ��������������� ���. � ������ � ��� ������� - �����������, �� �� ��� ��� � ������ �������, � ����� �� ���� ����. � �� ����, ������� �� �� ���, �� ��� ��� ������ ����. � �����, ��� ����� � ��� �����������.";
			link.l1 = "��������. ���� �� ������� ����, ��������, ������� � ���.";
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = "����� � ���������� ������ � ���������� � �������. �� ����� ����� ���� � ������� ���� ����.";
			link.l1 = "������������.";
			link.l1.go = "Exit grotto end";
		break;

//after advisor quest done

		case "16":
			dialog.text = "�� ����, �� ���������� � ���������� ����� ����. � ��������� ���������� � ���������� � ������������, � ����� ����� � ���� ����.";
			link.l1 = "��������, � ������� ������ �����.";
			link.l1.go = "17";
		break;

		case "17":
			dialog.text = "����� � ����� ���������� � �������� ����� ������. ��� ��� ������ ����� �������. � ������� ������ ����� ���, �� �������� ��������.";
			link.l1 = "������ ����. ��� �� ����� �� �������� ���� ��������.";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "��� ���� � ����� �������, �����. �� ������, ��� ���� ��� �������� �������...";
			link.l1 = "�������, � ������, ��� �� �������. �����.";
			link.l1.go = "Exit";
		break;

//boss killed rant

		case "19":
			dialog.text = "������ � ����� �������. ���� ����������?";
			link.l1 = "...";
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = "...���? � ��� � ������. ������ ��������, � ��������� ���������. � ������� ����� ��������� ���������, �����, � ���� ����� ����������, ����� ��� ������. ������� ����� � ���� ������� ��� ����, �� ��������, ��� �� ���������� �����.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "21":
			dialog.text = "�� ���������, ���������. � �� ������� ������, � �� ��������� ������ ��� ������� ������. ��� ��, ��������, ������, ��� ����, ������� ����, 20 ��� ����� ��������� ������� �� ���� �������� ���������� - �����, ��������� �����������. ��������� �� ������ �������������� ������� �����, ��������� �� �� �������� ����, ���� ����� ������� �������� � ����, ����� ��� ��� ���� ������ ������� ������� ����� � ������. ��� �� ����� ��, ��������, ������, ���� �������� ��������� - ���� �� ���������� ������ ���, � � ���������� ��� ���� ��� ���������. �� ��� ���� �� ��������� �� ������, ��� ��� ����, ��� ��������� ������ ���� ��� � ������. ������ � ��� �� ������ � ������������� ��� �����, � ����������� ��� ���� � ����, ����� �� ��������� ��� ������, �� � �������� ��� �� ����������. ��� ����� �� - ��������� ���� � ������ ���������, ����� ������� ������ ���, ��� ����� �������� ����, ���������� ��� ���� ������ � �����. � �� ����� ��� ������� ��� ����� �� ������ - ���, ��, ��� ��� �� ��� �����, ������ �� ��� ������, �� �� ����� ����� ��� ������. ��� �����, ����� �� ��������� �� �������� �����, ������ ������, �������� �� �� �������. ��� �����, ����� �� ����� �������� �������. � ����� �������, �� �� �������, �� �������, ������� �� ������ ��������, �������� ��������. ������� � ����� ��� - ������� �� ���� � ��� ���������� ����� ���, ������� �� ��������!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting

		case "22":
			dialog.text = "�� ������������ � ������, � ���, ��� ��� ����� �������. � ����� ��� - ���� � ���� ������� � ���� ���-��, ��� �������� ��������� �����, �� ��� ��. �� �����������. � ���� ��� ������ - ����� ������� ������� ������. �� ��������� ��� � ���: ���� �������� ��� - ��������� ������ �����. ����� �������� ������ �����-���� �������� ����� ����, � �����, ������� �� �������� ��� ������. ��� ���, ����� � ������ - ��� ��� ����. ��� � ��� ������ - ������ ��� � ������ ���. �� � ���� ���� - � �� ����� ���� ���� ���� �� ��� ������ ����! � ������� ���� �����, ������ ��� �����!";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//at pirate meeting - autodialog 2

		case "23":
			dialog.text = "�������, �� �� ��������� � ����� �������. ������ ��������, ��� ����� ������ ��������...";
			link.l1 = "...";
			link.l1.go = "23_exit";
		break;

		case "23_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("captains_long_speak");
		break;

		case "24":
			dialog.text = "(������ ��������� �����) ...������ �� ������, ��� ������, �������. �������� ���, � ������ ����� �����. ������ ����.";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

//after pirate meeting

		case "25":
			dialog.text = "�� � ��, �����. �� ������������� ��� ������! ����������!";
			link.l1 = "�� �������, �������, ��. ���� �� �� ���� ������������ ����, ��� �� �� ����� �� ����.";
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = "��, ���� �� �����������. ����... ��� �� ����������� ������ ������, ������� ������� ������?..";
			link.l1 = "������-�� � ���� ���� ���� ���������� ����, ���� �� �� ������� ������...";
			link.l1.go = "27";
		break;

		case "27":
			dialog.text = "� ���� ��������� �������� ��� ����. �������...";
			link.l1 = "��, ��� �����, ���! � ���� ����� ��� �����?";
			link.l1.go = "28";
		break;

		case "28":
			dialog.text = "���-�� ��� ������������, ��� � ���� ����������, �������, ������, ������ ����, ������ ���� ���� �� ���� �������.";
			link.l1 = "� �����! ��������� ���������� �� ����� � ������������ �� ����������!";
			link.l1.go = "Exit";
		break;
//exits

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit_fight":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetCheckMinHP(NPChar, 1, true, "Sharp_Prologue_CheckHP");
			LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit grotto continue":
			NextDiag.CurrentNode = "hired";
			DialogExit();
			//pchar.questTemp.HiringOfficerIDX = NPChar.index;
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			if (NPChar.model.animation == "man") Npchar.CanTakeMushket = true;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // ��������
			LAi_SetImmortal(NPChar, false);
			sld.greeting = "Gr_Danielle";
			sld.rank = 5;
			SetSelfSkill(sld, 20, 20, 20, 20, 20);
			SetShipSkill(sld, 20, 20, 20, 25, 20, 20, 20, 20, 20);
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			
			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 50000;
			//_location.box1.items.icollection = 1;
			//_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			//_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
		break;

		case "Exit kill":
			LAi_SetWarriorType(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetPlayerType(PChar);
			LAi_SetImmortal(NPChar, false);
			DialogExit();
			
			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 150000;
			_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 20+rand(5);
			_location.box1.items.jewelry2 = 20+rand(5);
			_location.box1.items.jewelry3 = 20+rand(5);
			_location.box1.items.jewelry4 = 11+rand(5);
			_location.box1.items.jewelry6 = rand(50);
			_location.box1.items.jewelry7 = rand(100);
			_location.box1.items.jewelry10 = rand(50);
			_location.box1.items.jewelry14 = rand(50);
			_location.box1.items.jewelry15 = rand(10);
			_location.box1.items.jewelry18 = rand(100);
			
			pchar.quest.SharpExitFromCave.win_condition.l1 = "NPC_Death";
			pchar.quest.SharpExitFromCave.win_condition.l1.character ="Sharp_Sibling";
			pchar.quest.SharpExitFromCave.function = "SharpExitFromCave";

		break;

		case "Exit half":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			_location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 70000;
			//_location.box1.items.icollection = 1;
			_location.box1.items.indian1 = 1;
			_location.box1.items.indian7 = 1;
			_location.box1.items.chest = 1;
			_location.box1.items.jewelry1 = 10+rand(5);
			_location.box1.items.jewelry2 = 10+rand(5);
			_location.box1.items.jewelry3 = 10+rand(5);
			_location.box1.items.jewelry4 = 5+rand(5);
			_location.box1.items.jewelry6 = rand(25);
			_location.box1.items.jewelry7 = rand(50);
			_location.box1.items.jewelry10 = rand(25);
			_location.box1.items.jewelry14 = rand(25);
			_location.box1.items.jewelry15 = rand(5);
			_location.box1.items.jewelry18 = rand(50);
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			chrDisableReloadToLocation = false;
		break;

		case "Exit grotto end":
			AddDialogExitQuest("Grotto end");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}