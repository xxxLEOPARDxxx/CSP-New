
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
			dialog.text = "�� ���� �������������.";
			link.l1 = "��, �������...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������� � ����� � ������, ������� ����� �� ����
		case "Shore53":
			pchar.defaultanimation = pchar.model.animation;
			dialog.text = "������"+ GetSexPhrase("","���") +", ������� ������! ��������� ����������!";
			link.l1 = "� ��� ����?";
			link.l1.go = "Shore53_1";
		break;
		case "Shore53_1":
			dialog.text = "������� ���, �� ������� ������ �����!!!";
			link.l1 = "��� �����?";
			link.l1.go = "Shore53_2";
		break;
		case "Shore53_2":
			dialog.text = "�-�-�, ����� �� ������ ���� �����?..";
			link.l1 = "�������, ���������! �������� �������� � �� �������, ��� ���������.";
			link.l1.go = "Shore53_3";
		break;
		case "Shore53_3":
			dialog.text = "������, ������"+ GetSexPhrase("","���") +". ���� ����� ������� �����\n��� �������� � ����, ��� ��� ������� ����� ����, ������ � �������, ��� ������ ������ ���������. �� ���������� � ���� ����� � ����� � ���������� ������, ������� ��� ������ ��������� ������ ����� ��� �����. �������, �� ���?!!";
			link.l1 = "���, ����� ��������... ���������� ��������!!!";
			link.l1.go = "Shore53_4";
		break;
		case "Shore53_4":
			dialog.text = "������, ������"+ GetSexPhrase("","���") +"\n������ ����� � ��� ������� ����� ����� 50 �������. � ������ ����� ������ ���� �.";
			link.l1 = "� ��� ���������?";
			link.l1.go = "Shore53_5";
		break;
		case "Shore53_5":
			dialog.text = "��� ������, ������"+ GetSexPhrase("","���") +"! �� ������� ������ �����!";
			link.l1 = "���?!";
			link.l1.go = "Shore53_6";
		break;
		case "Shore53_6":
			dialog.text = "� ������ �������� ������, ������"+ GetSexPhrase("","���") +"! �����, ����������� ��������, �� ���� ����� ��� �� ��������� �������� ����, ��� ����� ������. ���� ������!\n������"+ GetSexPhrase("","���") +", ���� ����� �������� ��� ��� ������!";
			link.l1 = "�� ���, ������� ��� �����?";
			link.l1.go = "Shore53_7";
		break;
		case "Shore53_7":
			dialog.text = "�����, ��� � ��� ������!\n��� �� ������, � ������, ����� ������������ ������. ��� �������� ������� ������, ���, ��� ����� � ������ ����. �� ��������� ��� ���� �������, ����� ����� ����� ����� ������� ���������� � ����� �����������. ������ �� �������� � ���� ���� - ��� �� ������� ������� �� ������. � ������ �������, ��� ������ �����!\n� ����� ���� ������ ���� ������ �� ���� � ���� ����� ������� ���� ������. ���� ���� - � ������ ����������� �� �����. ������ � � ������...";
			link.l1 = "� ��� �� ��� ���������, ��� �������, �������?";
			link.l1.go = "Shore53_8";
		break;
		case "Shore53_8":
			dialog.text = "������ � ������ �������.";
			link.l1 = "�-��, ���������� �������...";
			link.l1.go = "Shore53_9";
		break;
		case "Shore53_9":
			dialog.text = "������"+ GetSexPhrase("","���") +", �� ������ ����. ��� ����� ��������!";
			link.l1 = "� ���-���� ������.";
			link.l1.go = "Shore53_10";
		break;
		case "Shore53_10":
			dialog.text = "��, ���� ����, � � ���� ������. ��������, ������"+ GetSexPhrase("","���") +"!";
			link.l1 = "������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_startInShore_2");
		break;
	}
}
