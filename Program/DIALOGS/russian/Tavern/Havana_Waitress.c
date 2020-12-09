// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
    float locx, locy, locz, fTemp;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("�������, " + GetAddress_Form(NPChar) + "?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("��, �� �� ��������� �� �� �� ���, " + GetAddress_Form(NPChar) + "? ","����� �� ��������� ���������? �������, ������ �� �� ����, ��� ��...") +"", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������..."+ GetSexPhrase(" ��� ����� ��������?","") +"",
                          "����� ������� ������ ��������, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "�� ���, ��� ��, ���������...",
                      "����� ���, ��������, �������...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
            if (pchar.questTemp.State == "Sp4Detection_FoundLetter")
            {
    		    dialog.text = "� ��� ������, ������"+ GetSexPhrase("","���") +".";
    			link.l1 = "��������, "+ GetSexPhrase("���������","�������") +", �� �� �������� � ������� ������ ���������� � ��������� �����?";
    			link.l1.go = "Step_S4_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_toHavana")
            {
    		    dialog.text = "� ��� ������, ������"+ GetSexPhrase("","���") +".";
    			link.l1 = "����� �������, ���� ���� ���� ����� �� ����������, ��� � ���������, �� ��, �������, �� ���������� ��� ������.";
    			link.l1.go = "Step_F3_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_WaitOneDay")
            {
				if (GetQuestPastDayParam("questTemp") > 0)
				{
    				dialog.text = "��, ��� � �� ������"+ GetSexPhrase("","���") +"! ��� ��� �������.";
    				link.l1 = "���, ����, ��� �� �������� ������...";
    				link.l1.go = "Step_F3_4";
				}
				else
				{
    				dialog.text = "������"+ GetSexPhrase("","���") +", � ��� �� ��������� ������ ���������. ���������, ����� ���������, ����� ���...";
    				link.l1 = "������, ��������, ���...";
    				link.l1.go = "exit";
				}
			}
            // <== ��������� ���� ��������� �������.
		break;
//========================== ���. �������, ����� �4. ������������� �������� ==================================
 	 	case "Step_S4_1":
			dialog.text = "���, ������"+ GetSexPhrase("","���") +", ��� � �������.";
			link.l1 = "�������� ����� �� ��������, ������ ������ ����������?";
			link.l1.go = "Step_S4_2";
        break;
 	 	case "Step_S4_2":
			dialog.text = "�������� ����� � ��� � ������� �����, ���� � �� ��������...";
			link.l1 = "� ����������� � ��������� ����� �� ������ �����?";
			link.l1.go = "Step_S4_3";
        break;
 	 	case "Step_S4_3":
			dialog.text = "������ ������ ����... ����������, ������"+ GetSexPhrase("","���") +", ��� ����� ��������. �� ������� ���, ����������.";
			link.l1 = "��������"+ GetSexPhrase("","�") +" ��������. �� ������ �� �������� � ���� ���������� ������ ���� ���� �������� �� �����?";
			link.l1.go = "Step_S4_4";
        break;
 	 	case "Step_S4_4":
			dialog.text = "(��������, �����) ����...";
			link.l1 = "��� ���, � ��������� ��� ���� �� ��������� �������-����������� ������. � ����, ��� �� ���-�� ������. ������� ����������, ��� ������� �� ��������� � ������!";
			link.l1.go = "Step_S4_5";
        break;
 	 	case "Step_S4_5":
			dialog.text = "������, ������"+ GetSexPhrase("","���") +", � ��� �����! ������ ���������� ���, ��� ������ ������� ��� �� ��������.";
			link.l1 = "������, ��� ���� �� �� ������ - � ������ ���� �� ������.";
			link.l1.go = "Step_S4_6";
        break;
 	 	case "Step_S4_6":
			dialog.text = "� �� ������ ������"+ GetSexPhrase("","���") +", ������� �� ���...";
			link.l1 = "�� ��, �������� ������� ����������� ������� � ������ ������ �������� - �� ������������ ��� ����. � ������ ������ ���, ��� ������.";
			link.l1.go = "Step_S4_7";
        break;
 	 	case "Step_S4_7":
			dialog.text = "������"+ GetSexPhrase("","���") +", � ������� ���� ��������, ������� ���� ���� ���� � ���� ����� ����...";
			link.l1 = "��� ��?";
			link.l1.go = "Step_S4_8";
        break;
 	 	case "Step_S4_8":
			dialog.text = "�� �������� � ��� ����������, �� ��������, ����� ������ � ��� ������. ��� ���, ���� ����������, �� ��������� �������, �������� �������� ����� ���� ������. � � ��������, ��� � ���� �������? ����� �������� ������ � � ������ ������ �� ��������, ������ �������� ������������� �������� � �����. ����� ��������� ���������, ��� �� �������� ������� � ��������� �������� ����� ��������.\n"+
                          "����� � �������� �������, �� ����������� ��������. �� ��� ����� ������ �� ��������, ��� ��� �� ����� �����, ��� ��� �������� �������. ��� ������ ��������� �������� � �������� �����, ��� ������ ������ ����. � ������ � ���� �������, ��� ������ �����. ������ ����� ��� ���� �� ��� ��������, ������� �� �������� �������, � ���� ��� ���� �������� �������������.";
			link.l1 = "���� ������! ������, ��� �� ��������� ����� ����... ��� ���� ��� ��������?";
			link.l1.go = "Step_S4_9";
        break;
 	 	case "Step_S4_9":
			dialog.text = "������ ������, ������"+ GetSexPhrase("","���") +". ���� ������� ������ ������� � ����. � ����� �� ������ ���������� ����� � ���, ��� ��� ���� �����. ��� ���-�� � � ����������, ��� � ����. ������ ������ �� �������, �������, ��� ���� ��������� � ������������ ������������. ������"+ GetSexPhrase("","���") +", �� ������� �� ������ ��� ������ �������. ����� ���, �������� ���� �����!";
			link.l1 = "������, � ������� ���� �� �������. ���� �������, ��� ��� �� ������� ������ � ��� ���� ����. ������ �������, ��� ���� �� ����� ����, �� ���-������ ����� �� ��� ����� ������ �� � ����� ����. ��� ��� ���� ����...";
			link.l1.go = "Step_S4_10";
        break;
 	 	case "Step_S4_10":
			dialog.text = "�������, ������"+ GetSexPhrase("","���") +", �� ������ ��� �������! � ����� �������, ��� ��� ��� �����, �� � �� � ��� �� ��������!";
			link.l1 = "���� ������� ����� �������� ��� ��� - ���������� ������� ������. ����, ���� �� �� �������� ����� ��� ���.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toGovernor";
            AddQuestRecord("Spa_Line_4_MirderDetection", "3");
        break;
//========================== ��. �������, ����� �3. ������ ����� ���� ==================================
 	 	case "Step_F3_1":
			dialog.text = "�� ��� ��, �����... "+ GetSexPhrase("������ ������������ ��������� �������� �� � ��� ����������!","����� ������ ������� � ������, �������.") +"";
			link.l1 = "��� �����, ����� �� ������� ��� ������ ����� ���� ������� �� �����, ���� ����������. �� ������ ���, ����� �� ���� �� ����� �� ���� ����� ����!";
			link.l1.go = "Step_F3_2";
        break;
 	 	case "Step_F3_2":
			dialog.text = "��, � ����� ���� � ��� ����� �������� �����, ����� �� ��� ����? � � ������ ������� ��� ������...";
			link.l1 = "��������, � �����"+ GetSexPhrase("","�") +", �� ��� �� ���������! ��, ����� 500 �����, � ��� ������� �� ��������, ����� ��������� ����� �� ����� ����. �� ��� ������ �� ������ ���� ������� ������ ���������.";
			link.l1.go = "Step_F3_3";
			AddMoneyToCharacter(pchar, -500);
        break;
 	 	case "Step_F3_3":
			dialog.text = "�������, ������"+ GetSexPhrase("","���") +"! ��� �������� ��������� ����-������. � ������ ����� ����� � ����� ����� ��� ����, ����� ������� � ���� ������� �� �����. �� � ������ ����� ���������� - ��� ������ � ��� � ��� �� ���������...";
			link.l1 = "����� ������, �����. � ��� ����...";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			pchar.questTemp.State = "Fr3TakeAnna_WaitOneDay";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_3_TakeAnna", "2");
        break;
 	 	case "Step_F3_4":
			dialog.text = "��, ��������.";
			link.l1 = "������. � ������ �������� ���, ��� ��� ���� �������...";
			link.l1.go = "Step_F3_5";
        break;
 	 	case "Step_F3_5":
			dialog.text = "� ����� ������"+ GetSexPhrase("","���") +" �� ����� ��� ������ ������ �������?\n"+
				          "��, ������"+ GetSexPhrase("","���") +", ����� ���, �� �������� ��� ���� ��� ������! � ���� ����� ��������� ������ �� ����� �������!";
			link.l1 = "�����... ��������, � ����� ���� �������� ������ � �� ��������. �� ���� ���� �� �����, ����� - ����� ������...";
			link.l1.go = "Step_F3_6";
        break;
 	 	case "Step_F3_6":
			dialog.text = "������, ������"+ GetSexPhrase("","���") +"... � ������ �� ��� ��������. � ������ ���, ������"+ GetSexPhrase("","���") +"? ����� ��� ��� �������, �� ����������, ��� �������.";
			link.l1 = "� ���? ��� ��� �������?";
			link.l1.go = "Step_F3_7";
        break;
 	 	case "Step_F3_7":
			dialog.text = "������ ����������. ��������� ���������, ��� �� �������� ������� � �������� �� ���.";
			link.l1 = "����� ������� ����!";
			link.l1.go = "Step_F3_8";
        break;
 	 	case "Step_F3_8":
			dialog.text = "������, ������"+ GetSexPhrase("","���") +", ������ �� ������� ��� ����� ������... ��� ���, ��������.";
			link.l1 = "�������, ������� �������. �� �����, ������ ��� ��� �����, ���� ���� ���-������... � ����� ���� �� ������, ���������. ���� �������?";
			link.l1.go = "Step_F3_9";
        break;
 	 	case "Step_F3_9":
			dialog.text = "�������, ������"+ GetSexPhrase("","���") +", ��� �� ����� ���������.";
			link.l1 = "�� ��� � ������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -500);
			AddQuestRecord("Fra_Line_3_TakeAnna", "3");
			AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("��","��"));
            ChangeItemDescribe("letter_open", "itmdescr_letter_open_FraLineQ3");
            GiveItem2Character(pchar,"letter_open");
			pchar.questTemp.State = "Fr3TakeAnna_WaitMidnight";
        break;
//========================== ������� � ������� ������ ==================================
		case "Allarm": 
    		dialog.text = "� ������ �"+ GetSexPhrase("��","�") +"! ������! ���-������, �������� ������, "+ GetSexPhrase("����� �������","��� �����������") +" ����� ���������!";
    		link.l1 = "�-��, ��������!!";
    		link.l1.go = "Step_F_Allarm";
			NextDiag.TempNode = "First time";
        break;
		case "Step_F_Allarm":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true; // ������� ����� �� �������.
			GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaGuard"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, 0, true));
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 30);
				LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto",   LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //�� ������ ������	
			LAi_SetWaitressType(npchar);
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

