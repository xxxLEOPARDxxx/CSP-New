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
		//************************** ��������� ������ ************************
       //==> ������ ����� ����.�������: ��������� �� �����.
        case "EngLine3Quest_BelizAttack":
			dialog.text = "���������!!! ��� ���� �����"+ GetSexPhrase(", ������ ������","") +"?!!";
			link.l1 = "��������� � ���� ���.";
			link.l1.go = "Step_E3_1";
			AfterTownBattle();
        break;

        case "Step_E3_1":
            dialog.text = "������...";
			link.l1 = "��� ������, �� ��� ��� ������. �� �������� ������ � ������, � �� ��������� � �����... ��� ����� �������.";
			link.l1.go = "Step_E3_2";
        break;

        case "Step_E3_2":
            dialog.text = "����� �������?";
			link.l1 = "�� �������, ��� �������� ������, �������������� � �������� � �������.";
			link.l1.go = "Step_E3_3";
        break;

        case "Step_E3_3":
            dialog.text = "� ���� �� �����?";
			link.l1 = "��, ������� ���� ����� ����� �������, ����� ����� ������. � ����� �� ��� ����������, ������ ���� ����� ����� ����� �� ������� - ����� �� ��������� ����� ������������ �� ����� ����...";
			link.l1.go = "Step_E3_4";
        break;

        case "Step_E3_4":
            dialog.text = "�� ������� �� ����������, ��� ��� ��� ����� �����������. ��������...\n"+
                          "������ � �����. ������� ��� ��� ������� � ������� ��� �����.";
			link.l1 = "�� ������ ��� ��������� ���� ����� � ��������. ���������� � ����� ������������� ����� ������, ������.";
			link.l1.go = "Step_E3_5";
        break;

        case "Step_E3_5":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Henry Morgan")], true); 
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Jackman")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("John Morris")], true);
            DoReloadCharacterToLocation("Beliz_fort",  "goto", "goto61");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "Beliz_fort", "goto", "goto13");
			LAi_SetStayType(characterFromID("Henry Morgan"));
			characters[GetCharacterIndex("Henry Morgan")].dialog.currentnode = "Gold_found_in_fort";
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))   // ��� ����� ����� ��� �����������, ���� �� �� ���� ������ �� ����. ���� ���, �� � �� � ����� �� �����.
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Beliz_fort", "goto", "goto72");
                LAi_SetStayType(characterFromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Gold_found_in_fort";
            }
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "Beliz_fort", "goto", "goto01");
                LAi_SetStayType(characterFromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Gold_found_in_fort";
            }     
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], true);
            // ==> ����� ������. ����� �� ����� �������� � ����� ������� ������ � �������.
            // === ����� ����� ��������, � ������ �������� ��������������.
            pchar.questTemp.BelizGoldQty = 3300 / sti(pchar.questTemp.CompanionQuantity);   // ����� ��� �������� ������ ������ �������, ���� �� ��������� �������� ��� ������������ � �� ������.
			// ������ �� � ��� ������� (�� ���������)
            SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.BelizGoldQty));// ��������
            if (IsCompanion(characterFromID("Henry Morgan")))   {AddCharacterGoodsSimple(characterFromID("Henry Morgan"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("Jackman")))        {AddCharacterGoodsSimple(characterFromID("Jackman"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("John Morris")))    {AddCharacterGoodsSimple(characterFromID("John Morris"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            Log_SetStringToLog("��������� ������ ����������� � ����� ��������.");
            InterfaceStates.Buttons.Save.enable = false;
            chrDisableReloadToLocation = true;
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

