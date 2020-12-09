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
			//�������, ����� �7
			if (pchar.questTemp.piratesLine == "Soukins_toLaVega")
			{
				link.l1 = "������, � ��� ����� ������, �� ����������, ������� �� �� � ����?";
				link.l1.go = "PL_Q7_1";
			}
		break;
		case "PL_Q7_1":
			dialog.text = "���. ��� �� ����� ��������� ����� ��������� ������������. ��������� ��� ���, � ����� ��� �� �������... �������� ��� ������� �� ������� �� ����� �������, ���� ������������, �� ������� � ���� �����������. � ���� � ��������, ��� ������ ������.";
			link.l1 = "�������!";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toLaVegaSea";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			AddQuestRecord("Pir_Line_7_Soukins", "2");
			pchar.quest.PQ7_FriendLinney.win_condition.l1 = "location";
			pchar.quest.PQ7_FriendLinney.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PQ7_FriendLinney.function = "PQ7_FriendLinney";	
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

