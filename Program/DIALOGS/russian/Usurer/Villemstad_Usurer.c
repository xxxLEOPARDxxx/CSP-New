// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
   	float locx, locy, locz;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "�-��, ��������� ������... ����� ������ �������������?",
                          "����������, � ��������� ��������, � �� �� ������� �������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� �������, ��������...", "� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> ����.������� ����� �4 ������������ � �������
			if (pchar.questTemp.State == "Intelligence_Curacao_toYozef")
            {
                link.l1 = "� "+ GetSexPhrase("�����","������") +" �� ��������� � ��� ������ � ����� ����. ��� ������ ����� ����� ��������.";
                link.l1.go = "Step_E4_1";
            }
			if (pchar.questTemp.State == "Intelligence_Curacao_NoMoney_Yozef")
            {
                link.l1 = "� "+ GetSexPhrase("�����","������") +" �� ���������� � ��� ���� �� 100000 �����.";
                link.l1.go = "no_money";
            }
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco" )// ����� �2 ����. �������.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
        			dialog.text = "��� ��� �����?";
        			link.l1 = "������ ���������� ������������� ��� �������� ���� ����� �� 50 �����. ��� �����? ������ � �� ���� ���� ������� �� ������?";
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JansenDeFonceicao"))
                    {
                        dialog.text = "��� ����� ��! ��� ������!";
            			link.l1 = "�� ��� ������! ������ ���� �����. ������� ������ ������ �, � �� ����������� ��������, ������������, � ��� ��������� �������� � ���, ��� ����� �� ���� ���� ������.";
            			link.l1.go = "Step_S2_5";
                    }
                    else
                    {
                        if (pchar.questTemp.State.Usurer != "Ok")
                        {
                            dialog.text = "���, �� ��� �� ��� ��� ������ "+ GetSexPhrase("���������","����������") +" ��� �������� ����?";
                			link.l1 = "�����, �����, ��������� ���...";
                			link.l1.go = "exit";
                        }
                        else
                        {
                            dialog.text = "��� ��� ���� �����, "+ GetSexPhrase("��������� ����������, ���������� �����������","��������� ����������, ���������� ����������") +" ...";
                			link.l1 = "����� ������, ����� �����! �����������...";
                			link.l1.go = "exit";
                        }
                    }
                }
            }
			//�������, ����� �5
			if (pchar.questTemp.piratesLine == "PL5Hunter_toVillemstad")
            {
				link.l1 = "������, ����� �������� � ����-������ �� ����?!";
				link.l1.go = "Step_P5_1";
			}
		break;
//********************** ���������� �������, ����� �4 "�������� � �������" ************************
		case "Step_E4_1":
			dialog.text = "������, ��� ���� �����?";
			link.l1 = "� "+ GetSexPhrase("�����","������") +" ������ ��������� �� ����������. ��� ����� ����� � ������ �������-����������� ������� � ��������� ��������.";
			link.l1.go = "Step_E4_2";
		break;
		case "Step_E4_2":
			dialog.text = "�������, �� ���������, � ��� �������.";
			link.l1 = "�������, � �� ���������, ��� � ���� ����� "+ GetSexPhrase("����","�����") +".";
			link.l1.go = "Step_E4_3";
		break;
		case "Step_E4_3":
			dialog.text = "100000 ����� � � �������� ��� ���, ��� ����.";
			link.l1 = "� "+ GetSexPhrase("�����","������") +" ������ ��������� �����.";
			link.l1.go = "agree_to_pay";
			link.l2 = "� ���� ��� � ����� ����� �����, �� � ����������� ������� �����.";
			link.l2.go = "no_money_now";
			link.l3 = "�� ������� �� �����, ������� ������?";
			link.l3.go = "fack_yozef";
		break;
		case "agree_to_pay":
            if (sti(pchar.money) >= 100000)
            {
        		dialog.text = "��� �, ���� ��� �������� ���������: ����� ���� ���� ����� � ���������� ������ ����������, �������-����������� ����� �������, ���������� ������� ����� �� ������ ��� ��� ������ ������� - ������� ����������� ������� � �������� ����� � �������. �� ����� ��������� � �� �������������, �� ����, ��� �� ����������� ����� �������� �������-����������� ������������ ����-�� �� �������� ���������. �� ����� ��������� ������� ����.\n"+
                         "�� �� ���� �����, � ��� �� �������� ����� ����� ����������� ����. ��� ��� ������������, ���� ��� �� ������� �� ����������. � ���... � ��� �� ����. ��������.";
        		link.l1 = "��� ���� ������. � � �� ���� ��� �����, �� � ����� �� ����. ��������.";
        		link.l1.go = "exit";
        		AddMoneyToCharacter(pchar, -100000);
        		AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "3");
        		pchar.questTemp.State = "Intelligence_Curacao_GaveMoneyYozef"; // �������� �� ��������� ����� ������� ������ � ����.
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
                Log_QuestInfo("���� ���������� � �����.");
            }
            else
            {
        		dialog.text = "���, ������ ����� ����� � ��� ���-���� ���. ������, ����� ���, �� �������� ��� ������. ��� ��� � ��������� ������.";
        		link.l1 = "������, � ��� "+ GetSexPhrase("�����","������") +".";
        		link.l1.go = "exit";
        		pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
        		//ChangeCharacterReputation(pchar, -1); TO_DO eddy
            }
		break;
		case "no_money_now":
			dialog.text = "�� ���, ������������ ��������� ������. � ���� ����� ���.";
			link.l1 = "�����, � ����� ���������.";
			link.l1.go = "exit";
            if (pchar.questTemp.State != "Intelligence_Curacao_NoMoney_Yozef")
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "4");
            }
            pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
		break;
		case "no_money":
			dialog.text = "�� ��������� ������? ��� ��� 100000?";
			link.l1 = "��, ������ � ���� � � "+ GetSexPhrase("�����","������") +" �� ��� �������. ��� ��� �� ��� ������� ������?";
			link.l1.go = "agree_to_pay";
			link.l2 = "��� ���, �� � ����������� ������� �� � ������� �����.";
			link.l2.go = "no_money_now";
			link.l3 = "�� ������� �� �����, ������� ������?";
			link.l3.go = "fack_yozef";
		break;
		case "fack_yozef":    // ����� ������ � �������� ��������
			dialog.text = "�� �� "+ GetSexPhrase("�����","�������") +"! ������� �������� �� ����� ���� ����������!";
			link.l1 = "���� ���� ������, ��������� ����������! ������ � ���� ������ �����!";
			link.l1.go = "Step_E4_4";
		break;
		case "Step_E4_4":
			dialog.text = "�� ��� �� ����, "+ GetSexPhrase("�������","�����") +". ������, �� ���!!!";
			link.l1 = "���������!";
			link.l1.go = "Step_E4_5"; 
		break;
		case "Step_E4_5":
            pchar.questTemp.State = "Intelligence_Curacao_FightGard";
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "5");
	    AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","�"));
	    AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("��","���"));	
            LAi_NoRebirthEnable(npchar);
            LAi_group_Register("EnemyFight");
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("HolSolder"+i, "sold_hol_"+i, "man", "man", 20, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_SetCheckMinHP(pchar, 10, true, "Intelligence_Curacao_KickYozef");
            LAi_SetPlayerType(pchar);
            LAi_SetFightMode(pchar, true);
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
			DialogExit();
		break;
//********************** ��������� �������, ����� �2 "����������" ************************
		case "Step_S2_1":
			dialog.text = "�� ���� � ���-�� ����������. �� ���� ��� ������� ����!";
			link.l1 = "��� �� ��� ��������, � ����� ������� ������. ��� ��� ������ ��� �������� ���������.";
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = "� ��� ������ ������� �� ����! � ���� �� ������ �� �� ��������� �� ����� ����, �� � ������ ����!";
			link.l1 = "�� ��� ������, ���� �� ���� �����...";
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = "�� ��� ��, �������� ��� "+ GetSexPhrase("�������","��������") +"?";
			link.l1 = "�� ���, ������ ��. ��� ���������, �����...";
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "5");
			pchar.questTemp.State.Usurer = 1;
		break;
		case "Step_S2_5":
			dialog.text = "� � ���� ��� � ������ ����������� ����, ������� �� ������?";
			link.l1 = "��� ������, ����� - ���� ��� � ���� �����. � ����������� ������? ��� ���� ���������� ��������������? ��, � �������, � ���� �������� ���������� �����, ��� ��� ������ ����. ������?";
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = "��... �� ����, � ����... ���� � ������ ����� ������, �� ��� ��������, ��� �� �� ������������ � ���?";
			link.l1 = "� ����� �������� ���. ������ ���� ������� � ����� ���, ���� �� ������� �� ��������. �����, ����� ���� ����. � ������ �������, ����� ������.";
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = "�������. �� � ����� �� ������.";
			link.l1 = "��� �������. �����. � ���, ��� ����� ������ �� �����, ���� �����...";
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
            AddQuestRecord("Spa_Line_2_Inquisition", "10");
			ReleasePrisoner(characterFromId("JansenDeFonceicao"));
            AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State.Usurer = "Ok"; //����� ��������
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
//********************** ��������� �������, ����� �5 ��� ************************
		case "Step_P5_1":
			dialog.text = "���. �� ����.\n��, ��, ��� ���������� ������������� ������, ��� �������� ���, "+ GetSexPhrase("���� ���� � ��� ����������","���� ���� � ��� ����������. ���� �� � �������") +". ��� � ������ ����� ��� �� �������������.";
			link.l1 = "���� ������?! ��� ��� ��� ��������. �� ��� � ������? ��� ��� ����� ��������?";
			link.l1.go = "Step_P5_2";
		break;	
		case "Step_P5_2":
			dialog.text = "������� �� ����. �� ������� �������, �����, ��� �����������������. � ������ ����, ��� �� ��� � �����������, ��� ���� ��, ����� ��� ���� ������ �� ��������. �� �� "+ GetSexPhrase("��������","������������") +" �����, ������ ��������, ��� ������ ��� ���� ���, ��� ��� ������ ����� - � ��������!";
			link.l1 = "��! �� �������, ��� �� ����������... �� �� ����� ������ ������ �� ����������, ���� �� ��� ��������? ����� ����-�� ������?..";
			link.l1.go = "Step_P5_3";
		break;
		case "Step_P5_3":
			pchar.questTemp.piratesLine.Q5.city_1 = GetQuestNationsCity(ENGLAND); 
			dialog.text = "������, ��� ������ � ���������� ����������. ����� � " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Dat") + " ��� ����, �� ����� �� �����.";
			link.l1 = "� �������, ��� ������� �� ������. �� ������� ����!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "2");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_1) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirst";
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

