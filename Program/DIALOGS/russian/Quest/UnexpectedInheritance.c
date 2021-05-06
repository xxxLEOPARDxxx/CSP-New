void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
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
			NextDiag.TempNode = "First time";
		break;
		
		case "GrottoSkeleton":
			scareOfficers(70);
			InterfaceStates.Buttons.Save.enable = false;
			dialog.Text = "�� ����"+GetSexPhrase("��","��")+" ������� ���� �����  � ������?";
			Link.l1 = "��� ��?";
			Link.l1.go = "GrottoSkeleton_1";
		break;
		case "GrottoSkeleton_1":
			dialog.Text = "��������� ���������! ��� ��� �! ������ ������� ��� � ������ ���� ���������, �� ������ ���� ���� �������� � ������, �����, ��� �� ��� ���� � ��� ����� � ������� �����, ������� ���. ��� �, ���������� �� ���, ��� ����� ������!";
			Link.l1 = "� ����"+GetSexPhrase("��","��")+" �� ���� ��� ����������, ��� ���������, �����. ��� �� ��������� ����?";
			Link.l1.go = "GrottoSkeleton_2";
		break;
		case "GrottoSkeleton_2":
			dialog.Text = "������ ��� ����� � ����������� �����, �� ���������� � ������� ���� � ����������� ������ ��� ������. � ����� ������ ����, �� ����� ���������� ����. �� � � � ������������ �������� �������� ���� � ���������� �� ���";
			Link.l1 = "�� ��� �� ����� �� ���?";
			Link.l1.go = "GrottoSkeleton_3";
		break;
		case "GrottoSkeleton_3":
			dialog.Text = "�� ����� �� ���. � ������ ��� �� ��������� ������� � ��������� ��� � ������. ������ ��������, ������� ���� ������, � ���� ��������� � ����� ����� �������� ������. ��� � � ����� �� ����, ����� � ������, ���������� �� ��� ������. ����� � ����. ����� ����"+GetSexPhrase("��","��")+" ��";
			Link.l1 = "�������� ������, �� �������� ����������� �� �����������! ���� ��� ���!";
			Link.l1.go = "exit_fight";
		break;
		
		case "GrottoPirate":
			dialog.Text = "��� - �� ����������� � ���, ���� �� ���? ���� ��� ���! ������ ����!";
			Link.l1 = "...";
			Link.l1.go = "exit_fight_grotto";
		break;
		
		case "Girl":
			dialog.Text = GetSexPhrase("�����","�������") + ", �������� ����������, �� �������?";
			Link.l1 = "�������, �� ������ �� ������� � ��������� ����� ������ � ������, �� ������������.";
			Link.l1.go = "Girl_1";
		break;
		case "Girl_1":
			dialog.Text = "���, "+GetSexPhrase("�����","�������")+", � �� �������, ����� ���, ���������� ����! ��� �����, ���� �������, ������, �� ������ � �������, ��...";
			Link.l1 = "������� ����, ���� ���� ������ ������, ������ ��� ������ �����������. � �������� ���.";
			Link.l1.go = "Girl_2";
			Link.l2 = "��, ����� ����� ��� ������, �� ��������� � ������������. ����� ��������, �� � ���� ������� ����!";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_2":
			dialog.Text = "������� �������. ��� ����� ����� ���� ���� �������� ���, ������� ��� � ����� � ����� ���������� ������ ��� �������. ��� ����, �������� ������� ���������� � ��� ������� �� �����.";
			Link.l1 = "����������, � � �������� �����"+GetSexPhrase("","��")+" �� ���, �� � ���� ����...";
			Link.l1.go = "Girl_3";
		break;
		case "Girl_3":
			dialog.Text = "��������, ����� ���. ����� �������, ����� ������ ���� ���� �������, ������ ���-�� ��� ���������� � �������� ���. � �������� ��������� �����, ������� �������� �������, �� ��� ����� �� ���������� ����. ��������, ��� ������� �����, ��� �� ������� ���������! �� ���� ��� ��������!";
			Link.l1 = "� ��������, ��� ������� �������� ���������� �����...";
			Link.l1.go = "Girl_4";
		break;
		case "Girl_4":
			dialog.Text = "�������, ����� ���!";
			if (sti(pchar.money) >= 7000)
			{
				Link.l1 = "������, � ����� ���� �������. ���� ����� ������? �����, �������� ����, �������, ��� ������� ����� ����� ������ �����. ��������...";
				Link.l1.go = "Girl_5";
			}
			Link.l2 = "�� ����������. ��������.";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_5":
			dialog.Text = "������� ��� �������, �������! ��� �������.";
			AddMoneyToCharacter(PChar, -7000);
			SetQuestHeader("UnexpectedInheritance");
			AddQuestRecord("UnexpectedInheritance", "1");
			AddQuestUserData("UnexpectedInheritance", "sSex", GetSexPhrase("��","��"));
			pchar.UnexpectedInheritance = "part1";
			Link.l1 = "��� ��, �������� �� ������.";
			Link.l1.go = "Exit_cancel";
		break;
		case "Girl_annoyed":
			dialog.Text = "�� ��������, �������.";
			Link.l1 = "���, �� ��������.";
			Link.l1.go = "Exit_cancel";
		break;

		case "Exit_cancel":
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Girl_annoyed";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		
		case "exit_fight":
			locLoad = &locations[reload_location_index];
			locLoad.box1.items.indian11 = 1;
			locLoad.box1.items.jewelry1 = 5;
			locLoad.box1.items.jewelry2 = 10;
			locLoad.box1.items.jewelry3 = 15;
			locLoad.box1.items.jewelry4 = 20;
			locLoad.box1.items.jewelry5 = 25;
			locLoad.box1.items.jewelry6 = 30;
			locLoad.box1.items.jewelry7 = 35;
			SetSkeletonsToLocation(&locations[reload_location_index]);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
		
		case "exit_fight_grotto":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);;
			for (i = 1; i <= MOD_SKILL_ENEMY_RATE; i++)
			{
				sld = CharacterFromID("UI_pirate"+i)
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

