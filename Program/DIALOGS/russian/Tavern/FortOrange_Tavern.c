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
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "� ��� � ������ �� ��������� ����� ������� �������? ��� �� ����� �����.";
                link.l1.go = "Jamaica_ratF_1";
            }
			//������
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHol") && !CheckAttribute(npchar, "Whisper.FindDesouzaHol"))
			{
				npchar.Whisper.FindDesouzaHol = true;
				link.l1 = "��������, � ���� ��� ������� �� ��������� ������ �������������� ����������? � ��� ��� ������ ���� ������ � ����� �������� �� ����.";
				link.l1.go = "FindDesouzaHol";
				break;
			}
			//������
		break;

        case "DefenceOrange": //����������� �������, ����� �4, ������ ����� �����.
            dialog.text = "��, ����� � ���, ����� ����� ����� � �� ����� �� ����� ����...";
            link.l2 = "����� �������� ���������� ����, �?";
            link.l2.go = "Step_H4_1";
        break;
        
        case "Step_H4_1":
			dialog.text = "�� ���� �� ��� �������, "+ GetSexPhrase("������","�������") +". ������ �� ������. �������� ��� �������!";
			link.l1 = "�� �� �� ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratF_1":
			dialog.text = "���������. ������ � ���� ������� ��������� ����. ���������������� ���, � ��� �����. � ����� ����, � ������ ������������� - ����� �������� � ����� ��������, ��� ��������. �� ���� �� �� ��� ������?";
			link.l1 = "���, �� ����. � ������ � ������� ������ �����, ��� ������. ��� ��� ��� �����? �� � ��� ������������ ������ �� ���� �����, � �� ��� ������ ����� ����������!";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "���� � ���� �� ����� �������. � ���� - �� ����. �� ��� �� ����������.";
			link.l1 = "��, ����! ��� � � ������ ��� ������ ����?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "�� ����, "+ GetSexPhrase("�������","���") +". ���� - ��������� ��.";
			link.l1 = "�����, ��� �������. �����, � ���� ��� �����������...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		case "FindDesouzaHol":
    		dialog.text = "���, ����� ����� ����� �� �����.";
    		link.l1 = "����, �������.";
			pchar.Whisper.FindDesouzaHolWaitress = true;
    		link.l1.go = "exit";
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
