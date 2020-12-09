// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("��� �� ������? �����������.", "� ������ ���, ��� �� ������?"), "������ ��� �� ���� �� ��������� ������ ������...", "� ������ ��� �� ���� �� ����� ��������� ������ ������...",
                          "�� ����� �� ��� ��������?! � ���� ��� ����� �� ���������� ������ ������, � �� ��� ������� ��������� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "�� ������, �� ����� � �� �����..."), "��, �����... �� �� ������, �����...",
                      "�����, �����... ������ �����...", "��������, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //********************** ��.�������. ����� �11. ������ ����� �������� ************************
		case "FraLine11Quest_OccupySC":
            dialog.text = "��� ��������� - ������ �� ��������� �����! �������� ������ ������� �������� �� ���� ���� ��������� � ������ ����.";
			link.l1 = "���, �� ���� ��! �� ����� ��������� ��������-����, � ��� �����, ���� ���.";
            link.l1.go = "Step_F11_1";
			AfterTownBattle();
        break;
		case "Step_F11_1":
            dialog.text = "� ��� �� �������� ������ ������?";
			link.l1 = "������ � �������"+ GetSexPhrase("","�") +" �������� ���, �������� ������� � ������� �������� XIV � �������� ���������� ������� � ���� ����������� �������������. �� �� ������ ������?";
			link.l1.go = "Step_F11_2";
        break;
		case "Step_F11_2":
            dialog.text = "��, ��������������, ������"+ GetSexPhrase("","���") +", �� ����� ���������� �� ������ ���� ��� ���������. �� ��� �������� �����, � ��������� ����...";
			link.l1 = "������� ��� ������, ����� ��� �������� ���� �� ������ �������, ������. �� ���, ���� �������...";
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr11OccupySC_toWeWon";
            AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "2");
            NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // ����� ����� ������� ������ � ��������
            PChar.questTemp.DontNullDeposit = true;    // ���� �� ������ ����������
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            UpdateRelations();
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // �������� 
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

