
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fightQuest":
			pchar.questTemp.LSC.Armo.checkCasper = npchar.index; //��� ��������� � ��
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������ ������ �� ������� ����
		case "Casper_1":
			dialog.text = "��, "+ GetSexPhrase("��������","�������") +", ��-��, ���� ������! ������ ��������.";
			link.l1 = "� ��� ����?";
			link.l1.go = "Casper_1_1";
			NextDiag.TempNode = "Casper_12";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_1_1":
			dialog.text = "� ��� ���-���� ���, ������ ������ �����. �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "����, ��� ��, ��������? ��� � �� ���.";
			link.l1.go = "Casper_1_2";
			link.l2 = "�-�, �������. �� �����...";
			link.l2.go = "exit";
		break;
		case "Casper_1_2":
			dialog.text = "����?!";
			link.l1 = "��� � �� �����? �� �����, ������ �������...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_12":
			dialog.text = "������, �, �������, ���� ���������. �������� ������, "+ GetSexPhrase("��������","�������") +"...";
			link.l1 = "� �� �� ���� �����, �������? ��� �� �� �����, � �� ���.";
			link.l1.go = "Casper_12_1";
			link.l2 = "�����, �����...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_13";
		break;
		case "Casper_12_1":
			dialog.text = "����?!";
			link.l1 = "��� � �� �����? �� �����, ������ �������...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_13":
			dialog.text = "�� ���, �� ���� ������"+ GetSexPhrase("","�") +". ��-�������� �� ����������...";
			link.l1 = "�� ��, � ���������"+ GetSexPhrase("","�") +"!";
			link.l1.go = "fightQuest";
		break;
		//������ ������ �� ������� ����
		case "Casper_3":
			dialog.text = ""+ GetSexPhrase("�������","��������") +", �� �� �"+ GetSexPhrase("��","��") +" ������...";
			link.l1 = "� ��� �����?";
			link.l1.go = "Casper_3_1";
			NextDiag.TempNode = "Casper_32";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_3_1":
			dialog.text = "��, ���������, � ���� ��� ��������. ��� ��� ���� ����������� ����� ������������, ����� ������.";
			link.l1 = "�� ����, ��������, �����?";
			link.l1.go = "Casper_3_2";
			link.l2 = "������, �������.";
			link.l2.go = "exit";
		break;
		case "Casper_3_2":
			dialog.text = "� ������ �� ������?";
			link.l1 = "���� �� �����, � ������ ���.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_32":
			dialog.text = ""+ GetSexPhrase("�������","��������") +", � ����� ����, �� ��������� ��������.";
			link.l1 = "��������? ��-��, �����, ������. ���� �� ������, � �� ���.";
			link.l1.go = "Casper_32_1";
			link.l2 = "������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_33";
		break;
		case "Casper_32_1":
			dialog.text = "��� ������?";
			link.l1 = "��� ������, ��� � �������...";
			link.l1.go = "fightQuest";
		break;

		case "Casper_33":
			dialog.text = "� ���� ������������, "+ GetSexPhrase("��������","��������") +". ������ ����� �� ����!";
			link.l1 = "�� ���� ������? �������, � �� ���������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "fightQuest";
		break;
		//������ ������ �� ������� ����
		case "Casper_5":
			dialog.text = "��, � �� ���� ������, ���� ���"+ GetSexPhrase("","�") +"!";
			link.l1 = "��, ��� ������?";
			link.l1.go = "Casper_5_1";
			NextDiag.TempNode = "Casper_52";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_5_1":
			dialog.text = "������ ��� � ����� ����! � ���� ��� ��������. �����"+ GetSexPhrase("?","�? � �� � �����.") +"";
			link.l1 = "�������� � ����? ��, ��� ���...";
			link.l1.go = "Casper_5_2";
			link.l2 = "�����"+ GetSexPhrase("","�") +"...";
			link.l2.go = "exit";
		break;
		case "Casper_5_2":
			dialog.text = "��, � ����.";
			link.l1 = "���� �� �����, � ���� �������� �� ����.";
			link.l1.go = "fightQuest";
		break;

		case "Casper_52":
			dialog.text = "������, � ���� ��� �������, ����� �� �����"+ GetSexPhrase("","�") +" ������!";
			link.l1 = "���� �� ���� ��������, �� �� �� �����. ������ ��, � ���� �������� �� ����.";
			link.l1.go = "Casper_52_1";
			link.l2 = "��-��, ��� �����...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_53";
		break;
		case "Casper_52_1":
			dialog.text = "����?!";
			link.l1 = "����, �����!..";
			link.l1.go = "fightQuest";
		break;

		case "Casper_53":
			dialog.text = "�� ���, ������ � ���� ��������...";
			link.l1 = "��, �����, ������.";
			link.l1.go = "fightQuest";
		break;
		//�� ��������� �� ������
		case "FackYou":
			dialog.text = "�� ��� � ���������� ��������� ����. ������� ����� ������� �����...";
			link.l1 = ""+ GetSexPhrase("��... � �� ��� � ���?","������ �����... �� ��� � ���?") +"";
			link.l1.go = "FackYou_1";
		break;
		case "FackYou_1":
			dialog.text = "�� ���� ����� ����. �� � � ����, �������, "+ GetSexPhrase("��������","�������") +". ��� �� �� �������, "+ GetSexPhrase("�������","��������") +"?";
			link.l1 = ""+ GetSexPhrase("���� � �� ����, ��� �������... ��-�, � �����, ���� '��������' �� ������.","��������, ���... �� ���, ���� ���, ��������, ����������.") +"";
			link.l1.go = "FackYou_2";
		break;
		case "FackYou_2":
			dialog.text = "�������... �� ��� ��, �� ��� � ������ ����� ����.";
			link.l1 = "���?!";
			link.l1.go = "FackYou_3";
		break;
		case "FackYou_3":
			dialog.text = "��-��, "+ GetSexPhrase("��������","�������") +". ���� � �������� ����� �� �� �����, ������ ���������. � ��� ����������� - �� ��� ���� ������ ������...";
			link.l1 = ""+ GetSexPhrase("�� �� ��� ���������!","�� ��... �� ���, ���� �����, �������.") +"";
			link.l1.go = "FackYou_4";
		break;
		case "FackYou_4":
			dialog.text = "���, �������, � ������ ������? ��� ����� ��� ��� ����� ����, ���� ��� ���� ������ ����������. � ������ � �� ����.";
			link.l1 = ""+ GetSexPhrase("��� ���� �� �������...","��� ���� �� �������! ������, �������!!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_3CarperAttackArmo");
		break;

	}
}
