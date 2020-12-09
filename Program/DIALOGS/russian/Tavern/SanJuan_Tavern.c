// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("��� ������� ������ "+ GetCityName(npchar.city) +" � ����� �������. ��� �� �� ������ ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��� �� "+ GetSexPhrase("�������","��������") +" ��� ������� ���� � �� ��...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "�� ��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> ��������� ���� ��������� �������. ����.
			switch(pchar.questTemp.State)
            {
                case "MorrisWillams_PinnaceNotFound":
                    link.l2 = "��������� � � ��� �� ���"+ GetSexPhrase("","�") +"... ��� ������ � ���-�����?";
                    link.l2.go = "Step_E6_1";
                break;
            }
		break;
        //---------------- ������ --------------------
        case "Step_E6_1":
			dialog.text = "� �����, ��� �� �������. ����� ����������.";
			link.l1 = "�������... ������, � ����� �� ������� ����� '����� ������'?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = "��, ������ �������� �� ������-������, � �� ����-�����!";
			link.l1 = "��� ��� ��! � ����������� ���?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = "�� �� �������, ����� ���, �� ��� � �� �����. � �������� ������ � ����������� ������������, ��� ��� � ������ ����� ��������� ������������.";
			link.l1 = "�� ��� ��, ��� � �������... � ����� ���� ��� ������?";
			link.l1.go = "Step_E6_4";
		break;
        case "Step_E6_4":
			dialog.text = "��������� ����� � ����. ������ ���-���� ������� ������ �� ��������. ���� �����...";
			link.l1 = "��� ���, ���� � ������ ���������?";
			link.l1.go = "Step_E6_5";
		break;
        case "Step_E6_5":
			dialog.text = "��� ��! � ����-�� ����� ���� ����� �����������?";
			link.l1 = "�� � "+ GetSexPhrase("�������������","��������������") +", ��� ���� ���� ��� �������, � ��� ������� ��� �����...";
			link.l1.go = "Step_E6_6";
		break;
        case "Step_E6_6":
			dialog.text = "�� ��� ��, � ��������� ��� ������������� � ���-������ ������.";
			link.l1 = "��� �����, ��������. ������� ����, ���� ������.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_2PinnaceNotFound";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

