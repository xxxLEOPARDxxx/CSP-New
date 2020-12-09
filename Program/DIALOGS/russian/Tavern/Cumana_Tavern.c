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
            if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
    			link.l1 = "�� �� ������, ��� � ���� ����� �������� ����� '���� ��� ���������'?";
    			Link.l1.go = "RomanticQuest_1";
			}
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn"))
			{
    			link.l1 = "��� � ���� ����� �������� ����� '���� ��� ���������'? ��� ������� �� ���.";
    			Link.l1.go = "RomanticQuest_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				link.l1 = "�� ������� �� � ��� ����� ������� �����, �� ����� ������ ���?";
				link.l1.go = "PL_Q3_1";
			}
		break;

		case "RomanticQuest_1":
			dialog.text = "��, ���������� ��� ���� �������, ��� ����� ���� ����� ���� �������. �� ������ ��� ���. � ������ �������.";
			link.l1 = "�������!";
			link.l1.go = "exit";
		break;		
		case "RomanticQuest_2":
			dialog.text = "��� �� ������� �������� �����, ����� ���� ��������.";
			link.l1 = "�������!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn");
		break;

		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("���. ������ ��� ��� ��� �����.", 
				"� ��� ������� ��� �� ���� ������.", 
				"�������� �� ��� �� ���� ���...",
                "��������� ��� ������, ��� ������ �� ������� ��� �� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, ��������.", 
				"��-��, � �����...",
                "��, �������...", 
				""+ GetSexPhrase("�����","������") +".", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

