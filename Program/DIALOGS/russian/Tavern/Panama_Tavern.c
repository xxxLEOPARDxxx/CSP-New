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
            // ==> �������� �� ������
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = "��������, ���� ������ �� �������� � ����������� �������� �� ����� ���� ����� �� �������?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "��������, �������, � ��� � ������ ��� ����� - ������� �������. �� ������, ��� ��� ��� ����� �����?";
                link.l1.go = "Panama_rat_1";
            }
            // <== �������� �� ������
		break;
//*************************** ����� �2 �������, ������� ���������� ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("���, �� ����� ����� ������ � �� ������ � ���.", "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� �����.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� ��, ������� ����.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//-->������������
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("��, ��� � ��� � ������ ���� ���. ��� �� ������ ����� ��������... ����� � ���� �������� �����-�� ������ - �� ��� - ��������� ����������, � �� � ���� �� ������.", "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� ��������.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ���� ����, �� ������?", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "��, ������ ������ ������ ���� ������ - � ����� �����. � �� ������ � �����. ��� ��� ��� ��� ���.";
			link.l1 = "�������, �� ��� ������� �����!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--������������
		

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

