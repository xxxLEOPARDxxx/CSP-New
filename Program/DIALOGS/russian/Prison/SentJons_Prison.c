// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			link.l1 = "� "+ GetSexPhrase("������","��������") +". ��������.";
			link.l1.go = "Exit";
			// ==> ��������� ���� ��������� �������.
            if (pchar.questTemp.State == "WormEnglPlans_SaveOfficer")   // �������� �� ����� �3 ����������� �������.
            {
    			link.l2 = "� ���� ������ ���������� ����� ��������.";
    			link.l2.go = "Step_H3_1";
            }
             // <== ��������� ���� ��������� �������.
		break;

        case "Step_H3_1":
            dialog.text = "��� ����������.";
			link.l1 = "��� ��������, ������ ��� ����� �������� ���� ��� �����. � ���!";
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

