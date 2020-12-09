// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			link.l1 = "� "+ GetSexPhrase("������","��������") +". ��������.";
			link.l1.go = "Exit";
            if (pchar.questTemp.State == "MorrisWillams_ArrestedToPrison")   // �������� �� ������� ������ ����.�������
            {
    			link.l2 = "���������, �� ���� ������ ������ �� �����. � ����, ����� ����������� ������ ������� ��� ��������.";
    			link.l2.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "SaveFromMorgan_toPrison")   // �������, ����� �1
            {
    			link.l2 = "������, � ����, ��� � ��� ���������� ��� �������, ����� �� ������ �� ��������.";
    			link.l2.go = "Step_S1_1";
            }
		break;

        case "Step_E6_1":
            dialog.text = "��... ��� �, ���� ���� �������������. ���������, ��� ��� ���� �� �� ����� ����� � ���������� ����������� ��� �������.\n"+
                          "�� � ������� ������� � ������ �������� �� ����� �� ��� ����� ���������������. ��������� ��� ���������� � �������-����������� � ����� �����.";
			link.l1 = "������ ������ � �������-�����������?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
            dialog.text = "������, ��� ������ ������� ��������� �� ��� ����������� ������������.";
			link.l1 = "�������... �������, ���������, � � ���� ���������� � ���������?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
            dialog.text = "�����, ��. ������ ������ ������, �� �����. � ����� �������������.";
			link.l1 = "�������, ���������.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			pchar.questTemp.State = "MorrisWillams_ArrestedToModiford";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "16");
		break;

        case "Step_S1_1":
            dialog.text = "� ���?";
			link.l1 = "�� ������ ����������. ������ � ���� ���� �� �������.";
			link.l1.go = "Step_S1_2";
		break;
        case "Step_S1_2":
            dialog.text = "���� ������ ��������� ��� ���� ���� �����������.";
			link.l1 = "� � �������, ��� �� ������ ���� ������ �������������� � ����. ����� � ���� ���.";
			link.l1.go = "Step_S1_3";
		break;
        case "Step_S1_3":
            dialog.text = "����� �������� ���� ��� �� �����. ����� "+ GetSexPhrase("���","��") +"!!";
			link.l1 = "�� ��� ��, �� ���� �����������...";
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

