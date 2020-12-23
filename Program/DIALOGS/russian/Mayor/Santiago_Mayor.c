// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("��� �� ������? �����������.", "� ������ ���, ��� �� ������?"), "������ ��� �� ���� �� ��������� ������ ������...", "� ������ ��� �� ���� �� ����� ��������� ������ ������...",
                          "�� ����� �� ��� ��������?! � ���� ��� ����� �� ���������� ������ ������, � �� ��� ������� ��������� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "�� ������, �� ����� � �� �����..."), "��, �����... �� �� ������, �����...",
                      "�����, �����... ������ �����...", "��������, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            //===> �������� ��������� �������� ������
            if (pchar.questTemp.State == "Sp5LaVegaAttack_toSantiago")
            {
    			dialog.text = "� ��� ������, ������"+ GetSexPhrase("","���") +".";
    			link.l1 = "� ������������"+ GetSexPhrase("","�") +" � ���� ������������ �������-������������ ������.";
    			link.l1.go = "Step_S5_1";
            }
            if (pchar.questTemp.State == "Sp5LaVegaAttack_WeWon")
            {
    			dialog.text = "��� �������, ������?";
    			link.l1 = "��� ������� � ������ ����. ��������� ���������� �� ���� ����������, �� �������, ��������, ���� ���� ���������������.";
    			link.l1.go = "Step_S5_6";
            }
            //<=== �������� ��������� �������� ������
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //********************** ������� ����� ����.�������: ��������� �� �������� ************************
        case "EL9_SantiagoAttack":
			dialog.text = "�� �������"+ GetSexPhrase("","�") +", ��������!";
			link.l1 = "������, � �� �����, ����� ���� ��� ��������. � �� �������"+ GetSexPhrase("��","��") +", ����� ���� �������� �������.";
			link.l1.go = "Step_E9_1";
			AfterTownBattle();
        break;
        case "Step_E9_1":
            dialog.text = "����������, ���������� ������.";
			link.l1 = "�����, ��� ���, ������. ���� � ���, ��� �� ������ �� ����. �� ��������� ��� �������� � ����������� � ������� ������. ��� ����� �������� ������ ������� � ����.";
			link.l1.go = "Step_E9_2";
        break;
        case "Step_E9_2":
            dialog.text = "���?!!! �� ������ �����?!!!";
			link.l1 = "�� ����� ����������, ������. � ������, ��� ��� ���, � ���� �������������, ��������� ����� �������� ��������, � ������"+ GetSexPhrase("","�") +" �� ��� �������� ���� ������ ��� - '�����', �� �� '������"+ GetSexPhrase("'","��'") +".";
			link.l1.go = "Step_E9_3";
        break;
        case "Step_E9_3":
            dialog.text = "������� ������ ������� ��� ������ �� ��� �� �������. ������ ���� �� ����...";
			link.l1 = "��� �� � ��������� ������� � �������� � ����. ������� ��� �������, ������� �������. �����������, ����������� ������. � ���������!";
			link.l1.go = "Step_E9_4";
        break;
        case "Step_E9_4":
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1); // ����������
			AddQuestRecord("Eng_Line_9_AttackSantiago", "2");
			chrDisableReloadToLocation = false;
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1 = "location";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1.location = "Cuba1";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition = "AttackSantiago_FightWithPardal";
            // ==> ������ ��� � ������ � ������,
            npchar.model = "usurer_3";
            npchar.name 	= "�������� �������";
        	npchar.lastname = "�� �������";
        	SendMessage(npchar, "lss", MSG_CHARACTER_SETMODEL, npchar.model, npchar.model.animation);
        	FaceMaker(npchar);
            // ==> � ������� ������ ����������.
            sld = GetCharacter(NPC_GenerateCharacter("Himenes", "huber_spa", "man", "man", 10, SPAIN, -1, false));
            LAi_SetStayTypeNoGroup(sld);
            sld.name 	= "���� �����";
        	sld.lastname = "�������";
            SetCharacterRemovable(sld, false);
            AddPassenger(pchar, sld, true);
			SetReturn_Gover_Dialog_Exit(NPChar);
            DoReloadCharacterToLocation("Santiago_town",  "reload", "reload3");
            NextDiag.CurrentNode = "Cupture_after";
            chrDisableReloadToLocation = false;
            DialogExit();
        break;
        //********************** ����� �5, ��������� �� �� ����. ************************
        case "Step_S5_1":
            dialog.text = "��, ����� ������, ��� �� �����. �� ������ � ������� ������ �������� �� ����?";
			link.l1 = "������ �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "Step_S5_2";
        break;
        case "Step_S5_2":
            dialog.text = "���������. � ����� ������, �������� ��������� ��, ��� ��� �������� ���������.";
			link.l1 = "� �"+ GetSexPhrase("���","��") +" ��������.";
			link.l1.go = "Step_S5_3";
        break;
        case "Step_S5_3":
            dialog.text = "�� ������ ��������� � ���������� ��������� ���������� �� ���������, ���������� �� ����. ���������� ��� ���� ����� ������ ��������, ������ ������. ������ ��������� �������� ���������� �����������, ���, ��������� ��� - ���� �������� ������. ��������� ������ ���� ��������� ���������, � ������ ����������� �� ���� � ����� - �� ����. � ������ ����� ������ ����������, �� ����� ������������ ��� �����.";
			link.l1 = "�������. � ���� ����������?";
			link.l1.go = "Step_S5_4";
        break;
        case "Step_S5_4":
            dialog.text = "�������, � ��� ������, ��� �����. � ��� ��� ����� �� ��������� ���� �������� �� ���, ��� ��������� ������ ���� ���������� ����������, ��� �� ������ �������� �� ������ ������ ��������. ��������� - ��� ������, �� ��� ��� ����� ����� ������.";
			link.l1 = "� ������� � ���������� ��������� � ���������� ������.";
			link.l1.go = "Step_S5_5";
        break;
        case "Step_S5_5":
            dialog.text = "�����������! ��� ��������� �������������� ��� ��� ������ ���������� � ��������������� ������� �������. � ��� ��� � �������� ���������.";
			link.l1 = "���� ��� �������, ��� �� ���� � ������ ������� ���������� ������������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_AttackLaVega";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "2");
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1 = "location";
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1.location = "LaVega_ExitTown";
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition = "Sp5LaVegaAttack_AttackGoOn";
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry3 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry4 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry5 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry7 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry8 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry10 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry14 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry17 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.cirass3 = 1;
			locations[FindLocation("LaVega_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			sld = characterFromId("Edward Mansfield");
			sld.Default.Crew.Quantity    = 1700;
			sld.Default.Crew.MinQuantity = 1100;
			sld.from_sea = ""; // ��� ������� � ����
			sld.Default  = "LaVega_townhall";  // ���� ���������� ������ ������� ���������
			sld.Default.BoardLocation = "LaVega_ExitTown";
        break;
        case "Step_S5_6":
            dialog.text = "���������, ������"+ GetSexPhrase("","���") +"! ������ �����������! ��� ��������� ������-�-������ ����� �� ����� �������� ���, ��� � ���� �� ������ ��������� ����� �������.";
			link.l1 = "��������� - ��������� ���������, � ���"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("","�") +" ��������� ������������ ������... ������, � ��������������?";
			link.l1.go = "Step_S5_7";
        break;
        case "Step_S5_7":
            dialog.text = "�� ��... ���������� ����� �������� ������� ����������� ������� �������� � 100000 ��������. �������� ��������.";
			link.l1 = "�����������. ������ �������, ��� ���� ������� ����� � ���� ����. ��������.";
			link.l1.go = "exit";
			locations[FindLocation("LaVega_townhall")].models.day.charactersPatch = "SmallResidence_patch";
            AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "Sp5LaVegaAttack_BackToHavana";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "4");
        break;
	}
    UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

