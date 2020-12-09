// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
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
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "������� �������! ������� ������� �� ������ - ��� ����������� ��������! ��� ��� �����?!";
			link.l1 = "������� ���������� - �������.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "������, �������! ��� ���, ���������, ����� ������ ��� ����� ���� �����? �� ������ ��� � ��� ���... ����� ��� �� ������ ��������� ���, ��� ����� �� ������ ��������?";
			link.l1 = "��-��... ���, �� �� �� �������. �� ������ �� �������� ������... ������ �������� ������. �� �����, � ��� � ������?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//��� ����� ������ - ����� ����� � ����
			{
				dialog.text = "��-��! � ����������, ��� ������ ���� - ���� ����. �� ������ ��� ��������� � �����. ������ �������� ������������, � �� ����� ����� �� ��������� ���� ������� ���������.";
				link.l1 = "��� ������! �����, ���� ���� � �� ��������... ������! ���������...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "���... ��� �� ������ �� ����?";
				link.l1 = "��! ������� ���� ����� ����� � ����� ����� � ���������, ��� �� ���� ������ �� ������ ��������, ����� ���� ������ �����. �� �� ��� ���� ����� �� ����� �������... ��� �� ���������, �� �� ��������.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "�� ��� ��, �� ��������, � �� ��������� ����������� �������. �� �� �������, ��� ���� ������ � ���������� ���� ������� �������� ������� ������ ��� � ���! �� ������ ��������� �� ���� ��������!";
			link.l1 = "�� ������ ��� ������, ���� ������. ���� ���� � �� ��������...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterReputation(pchar, -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//������ ����� �� �����
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c ���������� ������
            Log_SetStringToLog("���� ��������� �� �������");
			Log_SetStringToLog("� ��� 30 ���� �� �������� ����� � ������������");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//������
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterReputation(pchar, -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//����� �� �����
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//���� �� �������� �� ���� ������ - ������ �������
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

