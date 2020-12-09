// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������, " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = "�������, � ��� ���� ���� �� ����� �������� �������. �� � ����� �� ������?";
				link.l1.go = "MCLiz";
			}
		break;
		case "MCLiz":
			dialog.text = "���� ��� ������� - ���������� ������ ������. � ��� ��� ����� �� ���?";
			link.l1 = "���������, ��� ���-��� ������ � ������ ���������...";
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = "��, ��� � ��������� ����� ���-�� ����� ����� ��������������. � ������ �� � �� �������.";
			link.l1 = "� ������ ��� ���?";
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = "������ � ���� � ����.";
			link.l1 = "� ��� ����������� ���?";
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = "��, ��� �� ����.";
			link.l1 = "� ��� �� ����?";
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = "��, �� ���� ����� ���������������� �� �������, �� ��� � ��������.\n"+
				"������� �� � �������� ��������? ���? ��-��, ����� ������, ��� ������� �������, ���� �� ������ ������������, � ���� ���� ���. � ���� �����, ����� �� ��� ��� ���, ������� ����� ������ ��� �������� ������, ��� ��� ������ ������ ��� �������.";
			link.l1 = "�������� ����� ������� �������.";
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = "��� ������� ��� �����. ����� �� ��������� � ������ � ������, �� ���� ������ �������. ���, �� ������ ������...";
			link.l1 = "� ��� ������ ����� ����?";
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = "��, �� ���� ��������� �������� ������� � ���������� ����� ��, �� �������. � ������� �� ���������� ���� ��� ���� ���.";
			link.l1 = "�������?";
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = "������� ������ ���.";
			link.l1 = "�������. �� ��� ��, ������� ����, ��������.";
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = "�� �� ���. �������, �� �������� ��� ������� �������. ��� ������� �������, �������...";
			link.l1 = "�� ������ ������, ������ �������. ��� �� �����.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

