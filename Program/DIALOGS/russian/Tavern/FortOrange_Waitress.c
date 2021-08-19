// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("�������, " + GetAddress_Form(NPChar) + "?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("��, �� �� ��������� �� �� �� ���, " + GetAddress_Form(NPChar) + "? ","����� �� ��������� ���������? �������, ������ �� �� ����, ��� ��...") +"", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������..."+ GetSexPhrase(" ��� ����� ��������?","") +"",
                          "����� ������� ������ ��������, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "�� ���, ��� ��, ���������...",
                      "����� ���, ��������, �������...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "��������, ��������, �������, �� ������ �������� � ���� ��������� ������� ���������. ����� ������ ��������...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry15"))
				{
					link.l1 = "� ����"+ GetSexPhrase("��","����") +" ���� ���� ��������. �����.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "�� ���� ������. ��� ���� ��������.";
					link.l1.go = "exit";
				}
            }
			
		break;

        case "DefenceOrange": //����������� �������, ����� �4, ������ ����� �����.
            dialog.text = "��, "+ GetSexPhrase("������","�������") +", � ������ ���������, ��� �������� ����! � ��� � ��������...";
            link.l2 = "� ��� �� ����?";
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = ""+ GetSexPhrase("� ��� � ���������, ��� ���� ������ �������� �������� � �������! ���� ���� ��� ����������, �� ������ ������ ���!","� ��� � ���������, ��� �� ����� ���� ����� �������� �������! ���� ���� ��� ����������, �� ������ ������ ���!") +"";
			link.l1 = "�� �� ��� ��, "+ GetSexPhrase("���������","�������") +", � ��������"+ GetSexPhrase("","�") +" ���� ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "��, ��������, � ��� � ����? � ������� ����������, � ��� ���� - � ��� � �������. ������� ����� ������ �����, �� ��, ��� ���� ������� ������ �� �������. ���� �����... ��! � ����� ������� �� ��� �����!";
            link.l1 = "����-����, ������! � ���� � ������������ ����� ��������, ������ ��� �� �� �����������. ��� ��� �����, ��� ��� ����� ���� ���� - ���� ��������. ��� ����� ������ ��� �����, ���������? �� ������, ���� �� ����������?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "��-��... �� ��� "+ GetSexPhrase("��������","������������, ��-��") +", � �� ������, ���� �� ����������. ��� �������!";
            link.l1 = "������ ��������, �������. �� ������������ � ��� ����������� �� ������, � ������ ��� ���� ���������� ����... ���� �� ���������, � ��� �. ��� � �������� �� ����������, � �� ���� � ������ ���������� ����!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "�������. ��, ��� ��� ���� ����� ���������� ����, � �� � ������� ������... � ����� ���, ���� �� ����������, �� �� ������ ���.";
            link.l1 = "��... ������� �� ������?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "��, "+ GetSexPhrase("��� �����","����� �� ������, �������") +". ����� ��� �� ����. ������� ������ �������� ���������� ��������, � ��� � ����� ���������� �������������, � �� ���� � ������... ��������� ��� ��������, � � �����, ���� �� ����������.";
            link.l1 = "�� �� ��������! ������, ��� ��������� - ����� ��������� � ��������� �� �������. ������, ����� ���� ��������.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "��, ����� �������! ������ ��� ��� ������� ������ �� �������!";
            link.l1 = "������� �� ��� ��������������. ������ � ��� ������, ���� ���������� �������.";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry15", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "��, �������, "+ GetSexPhrase("������","�������") +". ������� ���� ���� �� ����, � ������.";
            link.l1 = "�������, ��������. ��� ���, ��� � �����"+ GetSexPhrase("","�") +" �����.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

