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
            // ==> ����� ����
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveMoney"))
            {
                link.l5 = "� ����"+ GetSexPhrase("��","��") +" �� ��������� ����. � ��� ��� ���� ������ ���� ���-��� ������������.";
                link.l5.go = "Step_Az_1";
            }
			if (!CheckAttribute(pchar, "questTemp.Azzy.GiveMoney") && pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
                link.l5 = "����������, ��� ����� ������ ����� ����.";
                link.l5.go = "Step_Az_4";
            }
		break;
        // ==> ����� ����. ���� ���� ������� �� �� ��������� ����.
		case "Step_Az_1":
			dialog.text = "��� �����. ��� �������� ��������� �������� ���, " + GetAddress_Form(NPChar) + ". �������� �������� ����� ������?";
			Link.l1 = "��, � ��� ����� �������.";
			Link.l1.go = "Step_Az_2";
		break;
		case "Step_Az_2":
			dialog.text = "����� ���, " + GetAddress_Form(NPChar) + ". ���-������ ���?";
			Link.l1 = "���, ������ �� �����... ��������, � ��� � ���� �� ���� � ���� ����? ���, ��� �������� ���������...";
			Link.l1.go = "Step_Az_3";
            DeleteAttribute(pchar, "questTemp.Azzy.GiveMoney");
            AddMoneyToCharacter(pchar, 3000000);
		break;
		case "Step_Az_3":
			dialog.text = ""+ GetSexPhrase("���","����") +", ������� ��� �� ��������� ��������� �����������. � ���� ��� - ������ ��� �����. ���� � ��� ���, �� ��������� ��� �������� ������ ������...";
			Link.l1 = "��, �������! ������� �� ������.";
			Link.l1.go = "exit";
		break;
		case "Step_Az_4":
            dialog.text = NPCStringReactionRepeat("��� ����� ����? �� ������� ��� ������ ���. � ��� ������� ���, ��� ��� ������ ��� �����.", "� �� ���� ����� �������� �� ����.", "���, ������ � ����...", "�� ���� ��������.", "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat("���� ��� ��� � ���� � ���� �����. ��� �� �����, ���� �� ������, ��� ��� �����, �� �������, ����� ���.", "�������...", "����� ����...", "�� ��� �, ������ ��� ������������� ������ �������.", npchar, Dialog.CurrentNode);
			Link.l1.go = DialogGoNodeRepeat("Step_Az_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_Az_5":
			dialog.text = "� ���������, � �� ����. ���� ������� �� ����.\n"+
                     "������, � ���� ��� ���� ���������, ����� �� ����������� ��� �������������. ��-��, ������ ����, ��� ��� ��� �� ��� ��������������� ��� � �������� ������ �� ������.\n"+
                     "��� ��� ��� ��� ��������, �������� �����, ��������� �������� ����. � �� ���� ��������� � �������� ���������� ���������, �� �������� ��� - ����� ���� �� �����.\n"+
                     "� ������ ������ ���� ����� ��������������. �� ��� � ��� �� ���������� ����� - ��� �� �������.";
			Link.l1 = "��� ����... �������.";
			Link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

