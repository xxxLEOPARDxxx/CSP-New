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
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHolWaitress"))
			{
				DeleteAttribute(pchar, "Whisper.FindDesouzaHolWaitress")
				link.l1 = "���� ���������, "+GetCharacterFullName("Marigo_tavernkeeper")+", ������ ���, ��� � ���� ��������� �������������� ���� � ������� � ����� �������� �� ����. � �� ���. ������ ��������� ���������� � ��� ��� ����������?";
				link.l1.go = "FindDesouzaHolWaitress";
				break;
			}
		break;
	
		case "FindDesouzaHolWaitress":
			dialog.text = "���� �����. ���, ������, ���� ��� ������. �� ������� ����, �� ��������� ��� ��������, ��� ��� ��� ����.";
			link.l1 = "� ��� ���� ��� ������ ����-��, �������� �� ����?";
			link.l1.go = "FindDesouzaHolWaitress_1";
		break;
		case "FindDesouzaHolWaitress_1":
			dialog.text = "����� ���, ���, �� �������. �� ��� �� ������ ��� ������, � ��� ��� ������ �� ���������� �������� ������� � ���������� ����������, ������� ����� �� ������� - �������. ��� �������, ��� ��� ��� ���� - ����������� � �� �����������. ������, ��� ���������, ������� ������ � ������, ��� ��� ��� ���������� ����������� �� ���. ��� ���� ��������� ���� ����� �����.";
			link.l1 = "� � ����� ����������� ��� ���� ������ ����� ����?";
			link.l1.go = "FindDesouzaHolWaitress_2";
		break;
		case "FindDesouzaHolWaitress_2":
			dialog.text = "�������, ��� ������� �� �� ���� �� ���� ���� �������. �������, ��� ���� ��� ��� �����������?";
			link.l1 = "� ���� � ���� ������ �����. �� ����� - ������ � �������. �� ������ ����� ���� ������. ��� ���� ������ � �� ����� ����������.";
			link.l1.go = "FindDesouzaHolWaitress_3";
		break;
		case "FindDesouzaHolWaitress_3":
			dialog.text = "��� ��� ��� ������ �� ����, �� ������-�� ������� ��� ������. ������ ���� �� ��� ����� �� �������� �����������, ������� ��� ��������� ��� ����.";
			link.l1 = "������? ��� ��� ���� �����������?";
			link.l1.go = "FindDesouzaHolWaitress_4";
		break;
		case "FindDesouzaHolWaitress_4":
			dialog.text = "��� ��� ���� �����������? ��� �� �� ����� �� �������, �������? ���� ������������ �������� ����� ����� ������� ������ �� ����� �������������� �������! �����������! ������ ������...";
			link.l1 = "�����, ���� ��� ����. ���� �����, � ��� ����� ��� ������.";
			link.l1.go = "FindDesouzaHolWaitress_5";
		break;
		case "FindDesouzaHolWaitress_5":
			dialog.text = "���� �� ����������� �������, ��� ������ ���� � ������, ��������� ����� � �����-�� �����.";
			link.l1 = "������� �� ����������, � ��������.";
			link.l1.go = "exit";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1 = "location";
			PChar.quest.WhisperHuntersCaveEntrance.win_condition.l1.location = "Marigo_CaveEntrance";
			PChar.quest.WhisperHuntersCaveEntrance.function = "WhisperHuntersCaveEntrance";
			AddQuestRecord("WhisperQuestline", "5");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

