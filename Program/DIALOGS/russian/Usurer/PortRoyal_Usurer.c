// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "�-��, ��������� ������... ����� ������ �������������?",
                          "����������, � ��������� ��������, � �� �� ������� �������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� �������, ��������...", "� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedToUsurer")
            {
                link.l1 = "��� ����� ���������� � ���� � ������� ��������.";
                link.l1.go = "Step_E6_1";
            }
			if (pchar.questTemp.State == "MorrisWillams_AfterFightGoRedmond")
            {
                link.l1 = "����� ��������� �� ������ �� �������.";
                link.l1.go = "Step_E6_5";
            }
		break;

		case "Step_E6_1":
			dialog.text = "��� ��������� � �������� ���������?";
			link.l1 = "�� ���, �� ������, ��� �� � ������?!";
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = "����, �������. � ��� ���������-��, �� ����?";
			link.l1 = "���, �� ����, �� �� ����� ��������. ��, ��������, ������, ��� ��� ������ ����� �� �������, ����� ���� ��� �� ��� ��������.";
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = "�� �� �� �� ��������!";
			link.l1 = "� ���, ��� �� �������, ��� ����� ����� ������ � ������?!";
			link.l1.go = "Step_E6_4";
		break;
		case "Step_E6_4":
			dialog.text = "���� ��������� ������ ����������� ��������, � �� ��������� ��� ���������, "+ GetSexPhrase("���","����") +". � ������ �� ����� �������� �� ����.";
			link.l1 = "� ��� ���� ��� �� �������. �� ���������� ���...";
			link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfo";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "18");
		break;
		case "Step_E6_5":
			dialog.text = "� ��� ��� ��?";
			link.l1 = "� � ���������������, � �������� �� ������ ����. � "+ GetSexPhrase("������","�������") +" �� �����.";
			link.l1.go = "Step_E6_6";
		break;
		case "Step_E6_6":
			dialog.text = "��... � ��� �� ��� �����?";
			link.l1 = "�������� �������� ������� �������� ��� ������. � �������� � ����� ����� ���������, ������� ����� �������������� ����� � ��� ������ � ���� ��� �����.";
			link.l1.go = "Step_E6_7";
		break;
		case "Step_E6_7":
			dialog.text = "� ��� ������� �����?!! �� ������, ������� ���������� ����� ����������.";
			link.l1 = "��� ��� �� ���. �� ��� �������� � ����� �������� � ������������ �� ������ ����������� ���... 10000 ����������.";
			link.l1.go = "Step_E6_8";
		break;
		case "Step_E6_8":
			dialog.text = "��-��! ���, �� ����.\n"+
                     "��� ����� � ������������ �� �������� ��� �� �������, ������ ���� ����� ������ �����.\n"+
                     "�� ��� �� ����� �������, ������� � ��� ��� �� ������� �� ��������. �������� ��� �� ������. ��������.";
			link.l1 = "��������. � �� �������� � ���, ��� �� ��� �������.";
			link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "5";
            //ChangeCharacterReputation(pchar, -2); // �� ������� ������� TO_DO eddy
            AddCharacterExpToSkill(pchar, "Accuracy", 80);
            AddCharacterExpToSkill(pchar, "Commerce", 50);
            AddCharacterExpToSkill(pchar, "Sneak ", 70);
            AddCharacterExpToSkill(pchar, "Fencing  ", 100);
            AddCharacterExpToSkill(pchar, "Defence  ", 50);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "22");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Morris_Willams")], "PortRoyal_tavern", "sit", "sit1");
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "Willams_NiceTalking";
            LAi_SetSitTypeNoGroup(characterFromID("Morris_Willams"));
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

