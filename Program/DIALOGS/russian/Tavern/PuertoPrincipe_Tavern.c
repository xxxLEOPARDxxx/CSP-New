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
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "����� �����, ��� ������� �������� ����� ��� ������-�� ����. �� �� � �����?";
				link.l1.go = "PL_Q7_1";
			}
		break;
		//�������, ����� �7, ������� ������ � ������ ��������
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat("��, ���-�� ���������. ��������, ����� ������ �������� �������� ��������.",
				"�� ��� �������� �� ��� ����.", 
				"����� �� �� ������ �������?",
                "�������� ������ ������ � ���� �� ���.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������... � ����� � ��� �� ������?",
				"��, �����.",
                "���, �����...", 
				"��, ������� � �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = "��, �� �� �����! ������ ����� ����� ������� �� ���������, �� ������ ���������� �������, ���� ��� ����� ���������. � �� ���� �����������...";
			link.l1 = "�� ���� ��. ���������, ������ ��� ����������, ����� �� ��� ����������� �� ��� ����. ��� �������?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "�� ����, "+ GetSexPhrase("���","����") +" �����. � �������� ��������� ���������� ����. �� ����� � �� ����� � ���, �� ������ ������ ��������� � ����� ��������� - ������ ����� ����� � ���������� � ������� � ����� ������� ����-��...";
			link.l1 = "��, �������... �� ��� ��, ������� ���� �� �����.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

