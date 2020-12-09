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
			//==> �������� �� ����� �������
			if (pchar.questTemp.State == "Sp10Maracaibo_toMaracaibo")
			{
				dialog.text = "� ������ ���...";
				link.l1 = "������, � ������"+ GetSexPhrase("","�") +" � ��� ��� ���������� �������������� ��������� �� ������ ��������� �� ������� ������. � ������������"+ GetSexPhrase("","�") +" � ���� ������������ ������������ ������ ��������� ������-�-��������.";
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toGovernor")
			{
				dialog.text = "�� ��� ��, �� ��� ������ �������. ��� �� ������ ���������� � ���������� ������� � ������ - � ��������� � ��������!";
				link.l1 = "����� ���������!";
				link.l1.go = "Step_S10_4";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toBattle")
			{
				dialog.text = "�� ��� �����? � �������, ��� ���� � ��������.";
				link.l1 = "�����, ������. � �� �������� �������� �����...";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_GoodWork")
			{
				dialog.text = "�������� ������, "+ GetSexPhrase("���� ���","���������") +". ��� ��������� ������� ��� ����� �������� � ��������� ��������!";
				link.l1 = "�������, ������...";
				link.l1.go = "Step_S10_5";
			}
			//<== �������� �� ����� �������
		break;
		//************************** ��������� ������ ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //==> ����������� ����� ����. �������. ������ ���������.
        case "HolLine12Quest_Occupy":
			dialog.text = "���, �� ���������� �������������. ����� ���. ��� ������ �����?";
			link.l1 = "���� ����� ������ ����������� ���������� ����������� ���������. ����� ��������������� ����������� ���������� � �������� � �������� ����������� ������.";
			link.l1.go = "Step_H12_1";
			AfterTownBattle();
        break;
        case "Step_H12_1":
			dialog.text = "� ������ ������ �� ��������� �������. �� ���������, ��� ����� ����� ��������� �����. �� ���� ��������� ��� �� ����� ������ ����� ��������� ���������� � ��������� ������, ��� �� �������� �� ����� ������� ���.";
			link.l1 = "���� ��� �������� �������� ������� �� ��������� ��������� ������.";
			link.l1.go = "Step_H12_2";
        break;
        case "Step_H12_2":
			dialog.text = "���� �� �� �� �������� ������� ��������, ������ �� ����� �� ����!";
			link.l1 = "�������, ������ ������ � ���-�� �������. ���� ����� ���� �����������, � ������ ����� �����.";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "2");
            pchar.questTemp.State = "OccupyMaracaibo_toWeWon";
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
        //==> ������� ����� �������. ������ ���������.
        case "Step_S10_1":
			dialog.text = "�������, ��� ������ �� �������� ������� � ��������� ������������!";
			link.l1 = "��, ��� ���. �� ����� �� �� ���������� ���, ���� �� ����������?";
			link.l1.go = "Step_S10_2";
        break;
        case "Step_S10_2":
			dialog.text = "�������, �������. ����, � ���������� ���������� ����������, ��� ��������� ������� ���������� �������� � ����-����� ���������� ��������� ���������. �������� ��� �� ����������� �������������� �������, �� ��� �� ����� � �������� ������ � ������� ��������� ������-�-�������.";
			link.l1 = "�������. ��� � ����"+ GetSexPhrase("��","��") +" ������ ������?";
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = "����������, ������. ������ ���������� � ��������� ������ ����������.";
			link.l1 = "� � ��� ������� ������ ��������� � ����� ���������... �� ��� ��, ���� � ��� �� ���"+ GetSexPhrase("��","��") +", �� �, �������, �������� �� ������ �� ����� �����.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_TalkWithOfficer";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1.location = "Maracaibo_town";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition = "Sp10Maracaibo_TalkWithOfficer";
		break;
        case "Step_S10_4":
			dialog.text = "� ����� ��� ���������� � ���������� ����� ������. ���������� ���������� ���������� ��������� �������!";
			link.l1 = "������, ������.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			pchar.questTemp.State = "Sp10Maracaibo_toBattle";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1.location = "Maracaibo";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition = "Sp10Maracaibo_Battle";
        break;
        case "Step_S10_5":
			dialog.text = "�� �������� ��������� ���������� ����� ����� ����� ��������� ��� 70000 �������. �������� ��������, �������.";
			link.l1 = "����� ������.";
			link.l1.go = "Step_S10_6";
        break;
        case "Step_S10_6":
			dialog.text = "����, ���� ������ ����� ���������, ����� �� ���� ��� �����������. ����������� ��� ��������� ������������� �������-����������� ������-�-�������.";
			link.l1 = "�������������, ������. ��������.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_2GoodWork";
			AddMoneyToCharacter(pchar, 70000);
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

