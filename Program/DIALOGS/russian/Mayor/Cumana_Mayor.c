// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("��� �� ������? �����������.", "� ������ ���, ��� �� ������?"), "������ ��� �� ���� �� ��������� ������ ������...", "� ������ ��� �� ���� �� ����� ��������� ������ ������...",
                          "�� ����� �� ��� ��������?! � ���� ��� ����� �� ���������� ������ ������, � �� ��� ������� ��������� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "�� ������, �� ����� � �� �����..."), "��, �����... �� �� ������, �����...",
                      "�����, �����... ������ �����...", "��������, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp8SaveCumana_GoodWork")//����� �8 �������.
			{
				dialog.text = RandPhraseSimple("������"+ GetSexPhrase("","���") +", ���� ����� ���������� ��� �� ���� �����. ���� �� �� ��, ���� ������� ���� �����������, ��� ����� ���������...", "���� ����� �������� �� ��������� - ��� ���� ������� �����. �� ��� ����� ���������� �� �������� �� ������� �������.");
				link.l1 = RandPhraseSimple("�� ��, �� �������� ������ ����� �� ����������...", "���� �������� ����� ���������� �����������...");
				link.l1.go = "exit";			
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** ��������� ������ ************************	
        //==> ������������ ����� ����.�������: ������ �������� � ������.
        case "EngLine11Quest_OccupyMein":
			dialog.text = "���, �� ���������� �������������. ����� ���. ��� ������ �����?";
			link.l1 = "������ ��� �������-������������ ������ ������� �������� ������ ����� ��������� ����� II �������.";
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
        break;
        case "Step_E10_1":
			dialog.text = "�-�-��...";
			link.l1 = "������ ����� ������ ��������� ��� ������������� ������. ��� ��������� �����, �������� ������� � ������ ��������� �������� ������� ����� ���������� �������������.";
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_11_OccupyMein", "3");
            pchar.questTemp.Q11_Cumana = 1;
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
        //==> ������ ����� ��.�������: ������ ������ � �����.
 		case "FraLine6Quest_Attack":
			dialog.text = "��� ����� ���... � ����� ��������� ���� ����������.";
			link.l1 = "��� ����� ��������, ��� � ������ ��������� 200 ����� ������... �� ������ ���� �� ����� ��������.";
			link.l1.go = "Step_F6_1";
			group_DeleteGroup("Spa_Attack");
			AfterTownBattle();
		break;		
		case "Step_F6_1":
            dialog.text = "��, �������... � ���� � �����, ��� ����� ���?";
			link.l1 = "����������, ������, �� ������ ��� ����� ������� �����?";
            link.l1.go = "Step_F6_2";
        break;
		case "Step_F6_2":
            dialog.text = "��� ���������� ������� ��� ����� ������������ �������...";
			link.l1 = "��� ���, ����� - ��� ���������, �� ���� ����� ������ �� ����. � �������� ��� - ���� �� ������ ������������, �� �������� ������� ������ ������ ������� ������. � ������� ������ ����� ��������������� �� ������ ��������� �����. ��� ��� ����� �����������?";
            link.l1.go = "Step_F6_3";
        break;
		case "Step_F6_3":
			if (GetQuestPastDayParam("questTemp") < 14)
			{
				dialog.text = "� ������, ��� ����� �� ��� ����������... �� ��� ��, � �� ���� ������� �� ���� �����, ��� �����, ��� ���������� ���������� �������� ����... ��� ����� � �������� ������� � ���������. ��������� � ����� ��������!";
				link.l1 = "���������� � ����������, ������. � ���� � �� �����, �� � ������������� ������ ���� ������� ����...";
				link.l1.go = "Step_F6_exit";
         		pchar.GenQuestBox.Cumana_TownhallRoom = true;
				pchar.GenQuestBox.Cumana_TownhallRoom.box1.money = 200000;
				LocatorReloadEnterDisable("Cumana_townhall", "reload2", false);
				pchar.questTemp.State = "Fr5Olone_FoundMoney";
			}
			else
			{
				dialog.text = "� ������, ��� ����� �� ��� ���������� � ��������� �� ����������, ��� ������ ��������� ���. �� ����� ���, ��� ������. ���� ���� ���� ����� �� ���� ������ �������. ������ �� ���� � ����� ����.";
				link.l1 = "����� �� ����� ������ ��������� ������...";
				link.l1.go = "Step_F6_4";
			}
        break;
		case "Step_F6_4":
            dialog.text = "������"+ GetSexPhrase("","���") +", ���������� ����, ��� �� � ����� ������. �, ��� ���������� ����� ������, ���������� ����� �������, � ����� �������� �� ���������. ��������� ���, ��� �������, �� �����, �� �������� �� ���� ������, ����� ��� ���. �� ��������...";
			link.l1 = "��������!! � ����"+ GetSexPhrase("��","��") +" �������� ������ ������ �� ������ ������������!";
            link.l1.go = "Step_F6_exit";
			pchar.questTemp.State = "Fr5Olone_WeLate";
        break;
		case "Step_F6_exit":
			for (i=0; i<3; i++)
			{				
				if (i==0)	sld = characterFromID("Olone");
				else	sld = characterFromID("Captain_"+i); 
				RemoveCharacterCompanion(pchar, sld);
				sld.dialog.currentnode = "First time";
				LAi_SetStayType(sld);
				LAi_SetCurHPMax(sld);
				LAi_LoginInCaptureTown(sld, true);
			}
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1.location = "Cumana_town";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition = "Fr6Olone_TalkWithOlone";
			LAi_LocationDisableOfficersGen("Cumana_town", true); //�������� �� �������
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = "Cupture_after";
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
        break;

	}
    UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

