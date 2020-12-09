// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������ " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
			switch(pchar.questTemp.State)
            {
                case "RevengeMansfield_toTavern": //����������� �������, ����� �6. ������ ���� � ������.
                    link.l2 = "��� �� ������ ���������? ��� �����, ����������?";
                    link.l2.go = "Step_H6_1";
                break;
                case "Fr7RockBras_toSeekPlace": //��. �������, ����� �7. ������ ���� � ���� ���������.
					link.l1 = "� "+ GetSexPhrase("������","�������") +", ��� ��������� �����, ��� ��������, ����� � ���� � ����������...";
					link.l1.go = "Step_F7_1";
                break;
            }
            // <== ��������� ���� ��������� �������.
		break;
//**************************** ����. �������, ����� �6. ������ ��� ������� ���� � ������ �������� ************************
 	 	case "Step_H6_1":
			dialog.text = "����� ����������� ������� - � ��� ��� ������. ����� ����������.";
			link.l1 = "� ��������� ������ �������� ������ ����������. ��� ��� ��� �������?";
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = "��� ���������� - ���� ����� �������, ����� ������ ��������. ������� �� ��������� �� ��������� ���������� �� ���������. ����������� ���� ����, ����� � ���!";
			link.l1 = "��� ��� ��! � ���, ��������� ��� ������ ������?";
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = "�� ���, �� ���, ��� � ���� ���� �������. � ������ ���� ������� ������ ���� ��� ����� �����. � �������, � ���� ��. � ������ � ���� ����� �������, ��� ��������.";
			link.l1 = "��, ����� �� ����� ��� ���������� ��� ��������?";
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = "� ���� ��� �����. �������� ������, ��� ��� ��� ���� ������ - ������� ��������. ��������� ������ ���� ���������!";
			link.l1 = "�� ��� ��, ����� �����... ��������, � ���� �������� � ������ ����������� �� ������. ��� ��������������? �� ������ � ������?";
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = "��, ������ �� �����. � �������� ������ �����, ���� ���������� � ���� �����.";
			link.l1 = "�������... � ������ ������� �� ���������� � ��������� �����, �� �� � �����?";
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = "�� ���, ������. � ��� ����� �������� ������, ������� ����� ����� �����... ��, � ��� ���� �����?";
			link.l1 = "�� ���, ������...";
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = "������, �� �� ������. ���� �������� ������ �� ������, �� ��� � ���������. � ����� ���� �����, ��� ����� ���������� � ��������� �����?";
			link.l1 = "�� ��� �� ��� �������������, �� �������?! ���� ����, ���� ����, ������ �����...";
			link.l1.go = "Step_H6_8";
        break;
 	 	case "Step_H6_8":
			dialog.text = "���-�� �� "+ GetSexPhrase("������������ ����, ��� �������","������������� ����, ������� ���������") +".\n"+
                          "��, ������� �������, �� ����� �������! ��������� "+ GetSexPhrase("����� ��������","��� �������") +" �� ���������, ������, ��� ��� �����"+ GetSexPhrase("","��") +"!!!";
			link.l1 = "�-�-��, ������!..";
			link.l1.go = "Step_H6_9";
        break;
 	 	case "Step_H6_9":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "3");
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromSantiago");
            //==> ����� �������
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            //<== ����� �������
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "SPAIN_CITIZENS");
            LAi_group_Delete("QuestGroup");
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //���� ���� ������.
            ref sld;
            for (int i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, "off_spa_"+i, "man", "man", 30, SPAIN, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 80, "blade33", "pistol3", 120);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
        break;
//**************************** ��. �������, ����� �7. ������ ���� � ���� ��������� ************************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("�����, �� ������ � ������ �����.", "�� ��� ���������� ���� � ���������.", 
				          "����� � ���������?", "�� ������� ����� �� ���� �������, ������� � ������ ���������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���, � ����� �� ��� ������� ������?", ""+ GetSexPhrase("���������","����������") +"? �� ��, ��������...", "��, �����, "+ GetSexPhrase("���������","����������") +", ������...", "����� � � ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "��� ������ ������ ������� ��� ������� �� �����! ������ ������ ���������� ����� ������ �� ����������.";
			link.l1 = "�� � ����-�� ���������� ��� ���������?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "�� ��� �� �� ����������? �����, � ������, "+ GetSexPhrase("������","���������") +".\n"+
				          "� ������, "+ GetSexPhrase("������","���������") +", ����� �� ��� ���������� ��� ���������. �� � ����� ���, �������� ������ ����� ����...";
			link.l1 = "�����, ���� ������, ����������.";
			link.l1.go = "exit";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

