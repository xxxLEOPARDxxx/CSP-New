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
			if (pchar.questTemp.State == "Sp9SaveCumana_toPortoBello")//����� �9 �������.
			{
				dialog.text = "��� �� � ��� ��� �����?";
				link.l1 = "���� ����� " + GetFullName(pchar) + ", ����� ������������ � ������ ����������. ��� ����������� ������ �� ��� ��� �� �������� �������-����������� ��������� ������-�-�������.";
				link.l1.go = "Step_S10_1";			
			}
			if (pchar.questTemp.State == "Sp9SaveCumana_toCompOut")//����� �9 �������, ����� ����, ��� 0 �����������.
			{
				dialog.text = "��-�-��, �������, ��� ��� ������. ��� �������?";
				link.l1 = "� �� ������ �������. �� ������ �������� � ��� ������������ ��������� �������?";
				link.l1.go = "Step_S10_5";			
			}
			if (pchar.questTemp.piratesLine == "Panama_toPortoBello")//�������, ����� ������
			{
				dialog.text = "";
				link.l1 = "";
				link.l1.go = "Step_S10_5";
			}
		break;
        //==> ������� ����� ���.�������: ����������� ������ ������� �������.
        case "Step_S10_1":
			dialog.text = "��-�-��, ����. ����� ������, � ����� ��� ���. �� � ����� ����, ������ ���� ������ ������ ����?";
			link.l1 = "� ����� ������, � ����� �� ����"+ GetSexPhrase("��","��") +" ����������� ����-�� ����� �������...";
			link.l1.go = "Step_S10_2";
  			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_S10_2":
			dialog.text = "��, ���������. � ��� ��� � ������������ ������ �������, �������� �������. ��� ���������� ��������� �� � ������� � ����������� �� ������������ ������� ������. ��� ��� ����?";
			link.l1 = "�� ������... ���� ���������, � ������� ���� ������ �� ������� ������.";
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = "��, �������.";
			link.l1 = "� �������, ����� ���� ���� � �������� ������� �������� � ����������� �����, ��� ������ ������� �����. �� ����� �� � ������������ �������...";
			link.l1.go = "Step_S10_4";
        break;
        case "Step_S10_4":
			dialog.text = "��� ����� ����� ������� �������, ������� ������������ � ������ ����. ��� ��� ����� ������� ������ ��������� ����, ����������� �� ������. ��� ��� ��� ������� ������ ��� ������������, ��� ���� ����� ����������� ������ ��� ������ � ���������: ������ ��� ��������� �������� � ������, � � ���� ��� ������ ������ ������ ��������� ������� �������, ������� ������� �� �� �����.\n"+
				          "������ ��� ��� ����?";
			link.l1 = "�����. � ��� ��� �������, ��� �� ��������?";
			link.l1.go = "Step_S10_5";
        break;
        case "Step_S10_5":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "�������� ����� �������� � ���� ������������ ��� ������ �� ���������� �� ������ �������� � ������� ����� �������. �� ������ ����� ������ ���� ��� �������.";
				link.l1 = "� �����"+ GetSexPhrase("","�") +". ���� � ��� �����, ��� ������ ������ �� ����� ��������...";
				link.l1.go = "exit";
				pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			}
			else
			{
				dialog.text = "������� ��������� �� ����� ����� �����, � �������� ��� �� ������ ���������� � ���� ������������. ����������, �� ������ ���������� � ���������� ������� ����������.";
				link.l1 = "����� ������. � �����-�� ������� ���������"+ GetSexPhrase("","�") +" � ������?";
				link.l1.go = "Step_S10_6";
			}
        break;
        case "Step_S10_6":
			dialog.text = "���, ������� - ����� ��� ������� ��������� �� ������� � ������� � � ��� �� ���������� �����, ��� � ������. � ���� � ���� ������. ������ ��� � ������ �������� 5000 ����, ��� � ����� ���� ���������� 10000 ���������.";
			link.l1 = "� �������. �� ��� ��, � ��������� � ����������.";
			link.l1.go = "Step_S10_7";
        break;
        case "Step_S10_7":
            pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "2");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("��","��"));
            ref sld;
            for (int i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "trader_"+(rand(15)+1), "man", "man", 15, SPAIN, -1, true));
                FantomMakeCoolSailor(sld, SHIP_GALEON_L, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
                FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
                sld.Ship.Cargo.Goods.Balls = 48;
                sld.Ship.Cargo.Goods.Grapes = 10;
                sld.Ship.Cargo.Goods.Knippels = 48;
                sld.Ship.Cargo.Goods.Bombs = 48;
                sld.Ship.Cargo.Goods.Weapon = 0;
                sld.Ship.Cargo.Goods.Powder = 80;
				sld.Ship.Cargo.Goods.Food = 300;
				sld.Ship.Cargo.Goods.Gold= 1250;
				SetCharacterRemovable(sld, false);
				sld.CompanionEnemyEnable = false; 
				sld.Abordage.Enable = false; // ������!
                SetCompanionIndex(pchar, -1, sti(sld.index));
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1 = "location";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1.location = "Caiman";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition = "Sp9SaveCumana_toCaimanBattle";
            }
			DialogExit();
        break;
		//************************** ��������� ������ ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
        //==> �������, ����� ������
        case "PQ8_MayorPortoBello":
			dialog.text = "������!!! ��� ������ �� ������ ����� �����!";
			link.l1 = "��! ������� ���� ���������. �� ��� ������ ������...";
			link.l1.go = "Step_P1_1";
			AfterTownBattle();
        break;
        case "Step_P1_1":
			dialog.text = "��� ���� ��������, ��� ��������� ��������� �� ������. ��� ����� �� �����, �� ������ ��� �� ����� �������... ������� ��������� ��� ���� ����.";
			link.l1 = "��� ��� �� ���� ������. ������, � ������ ��� ����� �������� � ������?";
			link.l1.go = "Step_P1_2";
        break;
        case "Step_P1_2":
			dialog.text = "���? �� �������-�����������. � ������ �� ����� - ������� �� ����.";
			link.l1 = "����. �� ��� ��, ��� ��� ���������...";
			link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("PQ8_MorganInPortoBello");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

