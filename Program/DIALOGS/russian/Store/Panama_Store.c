// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("���������, ���� �� ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��������, ��� �������, ����� ���� �������� ���-��. �� �������� ����!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> �������� �� ������
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = "��������, � ��� �������� �� ����� ���� ����� �� �������. �� ���������� ���� �� �����, �� ����� ��� �� ��������.";
                link.l1.go = "Step_S2_1";
            }
            // <== �������� �� ������

		break;
//*************************** ����� �2 �������, ������� ���������� ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("����� � ��� � ����� �����. ������ �������, �������� ������� �����. ����� �� ����� �������� �����, �������������, � �� ������, ��� ������ � ����� �� �����. �� � ��� ��� ��� ��� � �� ���� � ����.",
                                                  "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� �����.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� �� ������ �� ������ ���������: ��� �����������, ���� ����������?", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = "���, ������.";
			link.l1 = "�������... ������� ����.";
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "11");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

