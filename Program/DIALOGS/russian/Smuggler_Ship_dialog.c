void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

    string ret;
    
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "start":
			dialog.text = "����������, " + Pchar.name + "! �� ������� ��������� �� "+ Pchar.HeroParam.Land +" ����� ���� ���� �������!"+
                          " ��� ����������� ������? �������-�� � ���� ������ ���.";
			link.l1 = "�� � ������ ���! ����� - ������������ �����.";
			link.l1.go = "start1";
			link.l2 = "������ ��� ���������� ������, �������?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "�������, ���� ������� ������ ��� � '���������'. ������.";
			link.l1 = "�� ����������. ������, �������!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", � �������������, � �� ��� ������. ����� � ���� ��� ���� ������?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret + " ������� � ������� � ����. ��� ����� ���� �� ���� �������."+
                              " ����� � �������, �� ����� � ������� ������ �����������. �� ������� �������� � �������� ��������.";
            }
            else
            {
                dialog.text = ret + " ����� ���-������ �����, ������ ���-������. �� ��� ���� �����.";
            }
            link.l1 = "�����, ������� �� �����. ������.";
			link.l1.go = "game_begin";
			link.l2 = "������, �������, �, �������, ���������� ���� �������. ��� �� ����� ����������!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "�� ����� ������, ��������.";
			link.l1 = "�� ���� � ������, ������. ������!";
			link.l1.go = "game_begin";
			link.l2 = "� ��� ������, ��� � ����? �� ������� �������, ��� ������ ��� ���� ��������. � � ������� ���� �����. ������������?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "��������, ��� �� ���� ������ ������� ���������� ������� ��-�� �������� �����. �� �����, � ���. ������� �� ������ ������� ���. � ���� ��� �� �����, ��������.";
			link.l1 = "�������?!";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "���...";
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	���������� �����
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // ���� �� ������ �� ��������
			//���� �� �� ��� �������� �� �������.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = "�� ��� ��������, ���, �����, ����� ������� ���� �� �������. ��... ������ ������� �� ������.";
				link.l1 = "��� �� ��������?";
				//��������, ���� ��� ��������.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //���������� ���� ����� ������ ������������, �� ��������������.
			}
			else
			{
				dialog.text = "�� ������� �� �����, ������.";
				link.l1 = "������.";
				link.l1.go = "Travel_end";
				link.l2 = "� ��� �������, �������� ��� ���� �������. ���� �������� ��� ����.";
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//������� �����
   			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//����� ���
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//������ �� ���� �����.... 
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//���� ���������
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
