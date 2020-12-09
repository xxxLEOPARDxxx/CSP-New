// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "��������� ����� ���� �����, �������� � ���� � ��������, �� �������� ������ �����-�� ������...", "�� ������� ������ ������. ��� ��������� ����, � �� ������ ��������� �����...",
                          "����� �������? ����� ����� ��������� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, �����, �����"+ GetSexPhrase("��","���") +"... �������� � ��������...",
                      "�� ��, ������������� � ������ ���...", "��, ����� � ���������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeStore": //����������� �������, ����� �2, �������� �������������� �� ����� �����.
                    link.l2 = "� ���� ������������ ���������� ����� ��� ���.";
                    link.l2.go = "Step_H2_1";
                break;

            }
             // <== ��������� ���� ��������� �������.
		break;

        case "Step_H2_1":
			dialog.text = NPCStringReactionRepeat("�����, ������ ������������ ���� ��������. ������� ������������ �� ��� �����, � ������� � ��� ���� ����, "+ GetSexPhrase("������","�������") +".",
                         "����� ��, ����� ������. ������� ��������� ���� ��������� ������.",
                         "����� ���"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("�� �������","�� �������") +"! ���������. ������� ��������...",
                         "�������, ��� ��� ������ �� ���� �� ������. ��, ������� ��������� �������� �� ���� ����������� ������ ������.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������� ��������� � ��������.", "������� ���������...",
                      "�������...", "��, �� ���� �������������, ����� ���. "+ GetSexPhrase("������","�����") +" ������� ��� ��� ��� �� ������..." , npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
         case "DefenceOrange": //����������� �������, ����� �4, ������ ����� �����.
            dialog.text = "���-���, ��� ��� ������ � ������ �������, �������. �� ��� ����� ����� �����!";
            link.l2 = "��, �� ��, ��������� ���� ��� ����...";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = "� ���� � ���� ����, �������, � ������ ����, ��� �� �� ������ ��������� �������. � ��� ��������� ����� ������ � ��� �� �������... �������, "+ GetSexPhrase("������","�������") +", �� ���� ���� �������.";
			link.l1 = "�� �� �� ���, ������ ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);
}

