// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "�-��, ��������� ������... ����� ������ �������������?",
                          "����������, � ��������� ��������, � �� �� ������� �������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� �������, ��������...", "� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //����������� �������, ����� �3. ������ � ������ ����������.
                    link.l2 = "��������, "+ GetSexPhrase("�����","������") +" �� ���������� ���� ���� ���������� ��������...";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== ��������� ���� ��������� �������.
		break;
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("����� ���� �������, ��� ������ � ���� �� ����. ������ - ��� ����������.", "����� �� �� ���������� ��������?...", "����� ������ ����� ����������?", "������� ����� ��������, � �� � ����� ��������� �����.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ������?", "��, ����� �� ��...", "�����...", "�������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "���� ��������� ��������� ���� �������� ������, ��� �� ��� ������ �������. �� ��� ���, ������?";
			link.l1 = "���, � ��� ��� "+ GetSexPhrase("�����","������") +" ���� ���� ������.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Usurer = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "10");
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

