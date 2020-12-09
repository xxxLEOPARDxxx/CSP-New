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
		break;

		case "Romantic_1":
            dialog.Text = "(��������):  ��� �� ������ ������� ��� ��� ������� ������?";
			Link.l1 = "�� ��� �� ������, ��������!  ���������� �������� ����� ��������, ��� � ������� ���� ������� �����!";
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;
		
		case "Romantic_2":
            dialog.Text = "�������, �������, ������ �������.";
			Link.l1 = "���, ������ ��������.";
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}

