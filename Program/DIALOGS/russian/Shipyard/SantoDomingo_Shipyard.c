// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "� ���� �� �����, � � ������ � ������, � ����� ����������� �������������� �� �����.",
                          "�� ��� �� �������? ��� ���� - ������� �������, ������� ���� � ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "��, ������...", "�������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toSantoDomingo")
			{
				link.l1 = "��� �������, ��� � ���� ��������� ����� '��������', ��� ���?";
				link.l1.go = "PL_Q7_1";
			}
		break;
		//�������, ����� �7
		case "PL_Q7_1":
			dialog.text = "���, �� ���. �� ���������, � ��� �������. ������ ���������� � ��� �� ��� ����������, ��� ����� � ��� ��� ����� ��������� �� �����...";
			link.l1 = "���� ���������� �� ����������, � ��������. ��� ������ ���� �����?";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = "������? ������... ������� �����-�� ������...";
			link.l1 = "�� � �������, ��� �� ������. ��� ���� �������, ��� ��� �����?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "��� ����� - �� ����, � ������ �� ������� �������...";
			link.l1 = "�� �����, ��������, ��� ���� ��� ����� ����� ���������.";
			link.l1.go = "PL_Q7_4";
		break;
		case "PL_Q7_4":
			dialog.text = "����! � ��� � ����, ��� ��� ������� ����� ����� ��� �����. �� �� ����� ������� ���� ���� ����������... � ����� ����������, ��� ����� ���-�� �������, �� ����������, ��� ��������.";
			link.l1 = "������ �����, �� ����������. ��� ��� ����� ��������?";
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = "� ����. ����� �� ����� � ���� �� ������� '����', ��������� ��� ��������. ���-�� � ������� �� �����. ���� ��� ��� ����� ��������, �� ��� ����� ���� �� ���� ������� � ��������� ���.\n��� ��� ���-�� � ������� ���������. �� �����, ��� �� ����� ������ ����.";
			link.l1 = "�������. ����� ������.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_seekLeon";
			AddQuestRecord("Pir_Line_7_Soukins", "6");
			AddDialogExitQuestFunction("PQ7_LoginLeon");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //����, ������ �� �����
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

