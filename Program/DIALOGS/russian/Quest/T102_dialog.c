//����� � �������
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "... (������ �������� ������������� ���� � � ������ ��������� ���� �� �����, ���� �������� ����������)";
			link.l1 = "��� �����?!";
			link.l1.go = "Term_1";
			TakeNItems(Pchar, "term_arm", -1);
		break;
		
		case "Term_1":
			dialog.text = "� - ������ ����� �-102, ������������ '������� ��������', ������� �������, ������ 2022 ����. � ������ ����, ������� �� ��������� �������.";
			link.l1 = "���? ����? ����� ��� �� ����? ������ ����? �� ����� ����������� ��� �� ��������� ��������! �� - �������! ������ ������-�� �������������, ��� �������.";
			link.l1.go = "Term_2";
		break;
		
		case "Term_2":
			dialog.text = "�� ����� �� ����, ������������� �������, ���������������� ���� ��� " +GetFullName(pchar) +
			              ". � - ������ � ������������� ���������, ������. �������� ����� ������� ���� ������, ��� �������� ���� �� ������ ������������� ���������. �� 170 ��� ��������� ��� ������. ��� ������ �� �������. ������� �������� ������� ���, ������� �� �������.";
			link.l1 = "������� ����? ����� � �� �����"+ GetSexPhrase("","�") +", ����� ���� �������� - � 15-� ���� ��� �� � 21-�?";
			link.l1.go = "Term_3";
		break;
		
		case "Term_3":
			dialog.text = "Error. Main power too low. Critical error - restarting....";
			link.l1 = "����?";
			link.l1.go = "Term_4";
		break;
		
		case "Term_4":
			dialog.text = "Loading from backup store....";
			link.l1 = "��� ��� � ���? ��������, �� � ��� ������ ��������? � ������ � �������� �� ������, ��� ���������� �����, � ��!";
			link.l1.go = "Term_5";
		break;
		
		case "Term_5":
			dialog.text = "System ready.......  � - ������ ����� �-102, ������������ '������� ��������', ������� �������, ������ 2022 ����.";
			link.l1 = "��� � ��� ������"+ GetSexPhrase("","�") +"! �� ��� ����, ����� �������!";
			link.l1.go = "Term_6";
		break;
		
		case "Term_6":
			dialog.text = "��� ������ ���� - ����������� � �������, ��� - 1985-�, ���� - ���� �'�����, �����������.";
			link.l1 = "� � ��� ������ " + GetDataYear() + "-� ���! � ��� ��� ������� ����.";
			link.l1.go = "Term_7";
		break;
		
		case "Term_7":
			dialog.text = "��� �������� �� ���� ������ ���������, ��������� ������� � ���������������. ��������� ���� ����������������. �������� � ����� 15-�� ����. �������� ������ - ���������� ������. ����� �� ��� �����������.";
			link.l1 = "��������, � � ��� ������?";
			link.l1.go = "Term_8";
		break;
		
		case "Term_8":
			dialog.text = "��������� ����� ���� - �����������. ����������� ����� ������ - �� ����"+ GetSexPhrase("","�") +" ���. ����������� ��� ������ � ���� �������� 'I'll be back', ���������� �� �������� ������� 30 ��� �����. ������������������ ��������� �������, ������������� � �������� ���� ������ �������������, ��������� ������������, �� ����������������� ���������. ����������� - ������� � ������������� �������, �������� ������� - ����������.";
			link.l1 = "�-�-�, ��� �� �������-��������, ��� ��? ���� ����, ��� ���� - ��� ��, ������ �� ������, ��� � �������� �������! � ���� �� ��� ��������"+ GetSexPhrase("��","���") +" ���, �� ������ ���.";
			link.l1.go = "Term_9";
		break;
		
		case "Term_9":
			dialog.text = "������ ����������� ������������ � ������������� ���������. ����� �� ��� ���������� � ���� ������ �������� � ���������� ��������������.";
			link.l1 = "��� ���� ��������� ���?";
			link.l1.go = "Term_9_1";
		break;
		
		case "Term_9_1":
			dialog.text = "�������������.";
			link.l1 = "�-�, ��� �������� 'I'll be back' - ��� ������ �������? ���, ��� � ������, ��������� ������ ��������������� ��������� �� ����������.";
			link.l1.go = "Term_9_2";
		break;
		
		case "Term_9_2":
			dialog.text = "��, ������� '" +GetFullName(pchar) +"', �� ����"+ GetSexPhrase("","�") +". ��� ����� �������� � �������� ��������� �������. ������ �� ����� ���� ���������, ������ �� ���������, ������������ ������ ������� ���������� ��������� ������� ���� � ���� ������.";
			link.l1 = "��, �� ������� ����. ����, ������, �� �����. ��� ����� ������� ������, � ��� �����"+ GetSexPhrase("","�") +". ���� ������� ���� �'�����, ����������� ����, � �������� ����� �� ����� ������� �� ��������.";
			link.l1.go = "Term_10";
		break;
		
		case "Term_10":
			dialog.text = "������� �� ����������. Scanning in process... complete... ��� �� ����� ���� ������. ������.";
			link.l1 = "���! ����� ������ ����, � ��� �� ���� �� ��������!";
			link.l1.go = "Term_10_exit";
			//PChar.GenQuest.GhostShip.TakeShotgun = true;
		break;
		
		case "Term_10_exit":
            LAi_SetPlayerType(PChar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			//ChangeCharacterAddressGroup(NPChar, "none", "", "");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		/*case "Term_11":
			dialog.text = "Scanning in process... complite... ���� ������� �� 68%% ���� � ����� �'�����. �� ������������� ������. ������ ������ ���� ���������. ���������� ����������.";
			link.l1 = "������ ��� ��� ����������� ��� �������, ��� ����� ���� �����. ������, ��������, � �� �������� �� ���� ��������� � ���� �� ���� ���� ����������.";
			link.l1.go = "Term_11_exit";
		break;
		
		case "Term_11_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            NPChar.location = "none";
            LAi_SetWarriorType(NPChar);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Kill_T102");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//������� �����
   			LAi_SetFightMode(Pchar, true);
   			chrDisableReloadToLocation = true;
		break;
		*/
	}
} 
