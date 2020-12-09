// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("�������, " + GetAddress_Form(NPChar) + "?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "��, �� �� ��������� �� �� �� ���, " + GetAddress_Form(NPChar) + "? ����� �� ��������� ���������...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������... ��� ����� ��������?",
                          "����� ������� ������ ��������, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������...", "������ ��� �� � ��� ��������"), "�� ���, ��� ��, ���������...",
                      "����� ���, ��������, �������...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "������, "+ GetSexPhrase("���������","�������") +", ��� ����� �����, ��� �������� �������. ����� ����...";
				link.l1.go = "PL_Q7_1";
			}
			if (pchar.questTemp.piratesLine == "Soukins_seekRings" && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
			{
				link.l1 = "� "+ GetSexPhrase("������","��������") +" ��, ��� �� ������. ��� ���� ������.";
				link.l1.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_1":
			dialog.text = "������� ��� ������� � ��������� � ������� � �������. � �����, ��������, � ����� ���� ������...";
			link.l1 = "� ���� �� ���...";
			link.l1.go = "PL_Q7_2";
			pchar.questTemp.piratesLine = "Soukins_seekRings";
			if (CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
            {
				link.l2 = "��� ���� ������, ��������...";
				link.l2.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_2":
			dialog.text = "����� ����, �� ��� ��� �������������� �������.";
			link.l1 = "�������...";
			link.l1.go = "exit";
		break;
		case "PL_Q7_3":
			dialog.text = "�-�-�, ��� �������!.. �������. ��� ��� �� �����"+ GetSexPhrase("","�") +" �����?";
			link.l1 = "��� ����� �����, ��� �������� ������ �������. �� � �����?";
			link.l1.go = "PL_Q7_4";
			TakeItemFromCharacter(pchar, "jewelry7");
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		case "PL_Q7_4":
			dialog.text = "���.";
			link.l1 = "��� ������ ����� �� �������� ��� ������?!!";
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = "� �� ������, ��� ����, ��� ������. ������, ������ �����������. ������ - ������� �����������, �� ��� ���������� � ���� ������� ������. ���� ����� �������� ���, ��� � ���.";
			link.l1 = "��! ����� �� ��� ����������, ��� ��� �������?";
			link.l1.go = "PL_Q7_6";
		break;
		case "PL_Q7_6":
			dialog.text = "��������. ������ ������ �� ��� ����������. ���� �� ��� ����� ��� ������, ��� ��� ����� �� ������ �� ������, ���� �������� ������� ������. �� ��� �����...";
			link.l1 = "��� ����� ��� �������!";
			link.l1.go = "PL_Q7_7";
		break;
		case "PL_Q7_7":
			dialog.text = "����� ����� ���� � ������ ������� ����. ������ ���� �������� ����� �����, ����� ��������� ������.";
			link.l1 = "� ��� �� �����?";
			link.l1.go = "PL_Q7_8";
		break;
		case "PL_Q7_8":
			dialog.text = "�� ����...";
			link.l1 = "��, �� ��� ��, ������� � �� ����.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toWindow";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

