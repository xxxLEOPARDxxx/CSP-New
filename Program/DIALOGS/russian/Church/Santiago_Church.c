// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������, "+ GetSexPhrase("��� ���","���� ���") +"?", "���������, � ������ ����..."), "� ������ ����, ������, "+ GetSexPhrase("��� ���","���� ���") +"...", "� � ������ ��� ������ ����, "+ GetSexPhrase("��� ���","���� ���") +" ���: ������� ���� ������.",
                          "������� ������������ � �����������������, � ��� ��� � �� ���������, "+ GetSexPhrase("��� ���","���� ���") +" ���...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "�� ������, �����..."), "��, ���� ����� � ������ �������...",
                      "�����, �����... ������ �����...", "��������, ������ ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Inquisition_toDeSouza")
            {
                link.l1 = "����, �������, ��� � ���� ����� ������� ������� �� �����?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
            {
                link.l1 = "����, �������, ��� ����� � ��� ��������� ����������?";
                link.l1.go = "Step_F7_1";
            }
		break;
        case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("� �� ������, "+ GetSexPhrase("��� ���","���� ���") +", ��� ���?", ""+ GetSexPhrase("��� ���","���� ���") +", � ���� ��� ��� ������.", "�� ����� � ��� �� ��������? � �� ��� ������� ����...", "�����? �����, ���� � ���������� ��������� ����� ���������, ������� � �������...",  "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, �� ������������������ ����������.", "��������, �����, � �� ����� "+ GetSexPhrase("�����","������") +"... �� �����...", "��, �� � �� "+ GetSexPhrase("�����","������") +"... ��, ��������, �����...", "��, �������, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = "Step_S2_2";
		break;
        case "Step_S2_2":
			dialog.text = "�����... �� ��� ��, �� ��������� � ���� � ����������.";
			link.l1 = "��������, �����, � ��� ���, ���������� ����������?";
			link.l1.go = "Step_S2_3";
		break;
        case "Step_S2_3":
			dialog.text = "����� ��� ��������.";
			link.l1 = "��� ���?..";
			link.l1.go = "Step_S2_4";
		break;
        case "Step_S2_4":
			dialog.text = "��� ���... ���, "+ GetSexPhrase("��� ���","���� ���") +", ���. �� ������ ���� � ������ ���������� ���� ��� �����...";
			link.l1 = "�-�-�, �� �����...";
			link.l1.go = "exit";
		break;

        case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("����� ��� ��������, "+ GetSexPhrase("��� ���","���� ���") +".", "����� ��� ����� ��������, "+ GetSexPhrase("��� ���","���� ���") +". ���� ��������� ��� ���������.", "�� ������ "+ GetSexPhrase("����� �� ����, ��� ���","���� �� ����, ���� ���") +". ��, �������� ���� �������...",
                          "��������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, �����.", "������� ��� ���, �����.",
                      "�����������!", "���?", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

