// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber") && pchar.questTemp.PDM_Novaya_Rodina.Guber == "HugoLesopilka")	//����� "����� ������". ���������� ��� ���������.
			{
				link.l2 = "���� �� ������� ����� ��������� � ��� �� ������. �� ����� ��������� 10000 ������� �� ��������� �������������, ������� �������� ��� ������� � ���.");
				link.l2.go = "HugoLesopilka_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber") && pchar.questTemp.PDM_Novaya_Rodina.Guber == "Lubopitno")	//����� "����� ������". ���������� ��� ���������.
			{
				link.l2 = "��� ��� ���� ����� ���������?");
				link.l2.go = "HugoLesopilka_Lubopitno_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena") && pchar.questTemp.PDM_ONV_VedmaKaznena == "PDM_ONV_VedmaKaznena")	//����� "����� �� ������". ������ �������
			{
				link.l2 = "� ���������, ��� �� ������� �������� � ���� ���������� �������, ������� ������� � ��������� ������ ���������, ���������� ��������.");
				link.l2.go = "PDM_ONV_VedmaKaznena";
			}
		break;

		case "work_1":  // ������ �� ����� ������ - ������� �����
            // ���� ���� ������ � ��������, �������� ����
			//if (CheckAttribute(npchar, "notQuestLine"))
			//{
            //    dialog.text = "� ���������, � �� ���� ������������ ��� ������. �� �� ��� �������, ���� � ����� �� �������� ���� ����. �� ��������.";
            //    link.l1 = "��� ��� ��...";
            //    link.l1.go = "exit";
			//	break;
			//}
            dialog.text = LinkRandPhrase("�� ���������� �� ������ �������! ����� ���������� ���������� � ���������� ������������ �� ��� ���������!",
                                         "���������� ����������� � ���������� ������ �� ���� ������������!",
                                         "� ��� ������ ������� � ���������� ����� �������������� ���������, �� �� ����������.");
            link.l1 = RandPhraseSimple("��������� ����������, ������ �������-����������", "� ��� � �������� ����������...");
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // ��� ������ � ������ ������
            {
                case "empty":   // ��� ������ �������
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("� ������ ������ � ���� ��� ��� ��� ������������� ���������. �� ������ ��������� � ���� � ���������� �����...",
                                                     "����� ���� ��������, � ����� ������ ����� � ������ ������!",
                                                     "����������� ������ ������ �� ����, ������ � ���� ��� ��� ��� �������.");
                        link.l1 = "������, ������ �������-����������.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // ������ ������� ������� �� �������
                        {
                            case "2":
                                dialog.text = "�-�-�, ��� � ��, " + pchar.name + "! ������������, ��� �� �������� ������ �������� � ������������! ��� ��������, ��� ��������� ���� ���� ��� ��������� �� ���� � ��������. �� ������������� ��������� �� ����� ������. ���� ������ � ����-����� �������� �����-���� �������������� ����, �������, ����� �� �������� ���������� ���������� � �����!";
                                link.l1 = "� ������ ����� ������, ��� ���������...";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = "��� ������ ��� �����, "+ GetSexPhrase("���� ���","���������") +". ���� ���������� ��� ���� ����, � �������, ��� ��� ����� ��� �� �����.";
                                link.l1 = "� "+ GetSexPhrase("����","���") +" ��������.";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                dialog.text = "����������, � ���� ������ ��������� ������� �� ���� ���.";
                                link.l1 = "����������� ������, ��� ���������.";
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = "� ���������� ��� � ������������ ����������� �������� ���� ����� ��������.";
                                link.l1 = "��� � ����"+ GetSexPhrase("��","��") +" ���� ������?";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "� ���� ���� ��� ��� �������. ������� ������� �����������...";
                                link.l1 = "������ �����������, ��� ���������.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "��� ������� ������ ������� ������ ������� ������ ����� � ������� ������� � ������� ���������� �������� �����. �� ���� ����� ����������, ��� �� ��� �������� ����������� ����������� ����������� ��� ������������� ������ ��������. ��������� � ������� � ������� ����������� ������ �������. �� - ������ ������ ��������!";
                                link.l1 = "� �����"+ GetSexPhrase("","�") +", ��� ���������. ��������� ����������.";
                                link.l1.go = "exit";
								pchar.questTemp.State = "Sp7SavePardal_toAntigua";
								AddQuestRecord("Spa_Line_7_SavePardal", "1");
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1 = "location";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1.location = "Antigua";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition = "Sp7SavePardal_FightNearAntigua";
							break;
                            case "8":
                                dialog.text = "����� ������, ��� �� ��������� ��� �������. � ���� ���� ����� ������ ������� ��� ���. ���� � ���, ��� ��������� ���������� ������� ������ ����� ���������� ���������� � ����������� ������� � ����� ��������� �� ������.";
                                link.l1 = "��� ���������, � �� ������������ ����������� � ����������� � ��������� ������ �������?";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = "��� �������� ���������� ����������� � ����� �����. ��� ��� ������� ���������� ������, �� �������� ��� ������.";
                                link.l1 = "������, �� ����� �� �� � ����� ������ �������, ��� ��� ��������� �������?";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "� ����� ��� ���������� ����������� � ����������� ������ ��������� ��� ���������� �������������� ���������.";
                                link.l1 = "�����, ��� ���������?";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "�� ������ � ��������� �������� �� ������ ����������� �������?";
                                link.l1 = "������ �����"+ GetSexPhrase("","�") +", ������ �������-����������";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = "�-�-�, ��� � ��, �������! � ���� ���...";
                                link.l1 = "������ � ����� �������, ��� ���������.";
                                link.l1.go = "Step_12_1";
                            break;
						}
                    }
                break;
                
                case "":           // ����� �1, ������ ������� �� �������.
                    dialog.text = "���-���, �������, � ��� ��������������� � ����� ��������.";
                    link.l1 = "��� ���� ��� ������� �����, ��� ���������. ����� �� ������"+ GetSexPhrase("","�") +", ��� ��� �������� ������� ���������� �������� ����� ������������������� �������.";
                    link.l1.go = "Step_1_1";
                break;
                case "SaveFromMorgan_OutOfPrison":
                    dialog.text = "������������, ��� � ��� � ����������� �������.";
                    link.l1 = "���� ���������� ���������, ������ �������-����������.";
                    link.l1.go = "Step_1_7";
                break;
                case "Inquisition_backBad":
                    dialog.text = "�-�-�, ��� �� � ���������, ����� ������. ��� ������ ����, ������� ��� �������� ������ ����������?";
                    link.l1 = "�� ������ ������, ��� ����. �� ������ ��������� �� ���������, ���, ����������, � ������.";
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backPartGood":
                    dialog.text = "�-�-�, ��� �� � ���������, ����� ������. ��� ������ ����, ������� ��� �������� ������ ����������?";
                    link.l1 = "����� ��� ����� ���������, ��� ����. ������ ��������� ��������, ��� ����, ����������, �������.";
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backAllGood":
                    dialog.text = "�-�-�, ��� �� � ���������, ����� ������. ��� ������ ����, ������� ��� �������� ������ ����������?";
                    link.l1 = "������� � ������� �������, ��� ���������. ��� ������� � ��������� ����, ������ ���������� ���� ��������.";
                    link.l1.go = "Step_2_3";
                break;
                case "TakeRockBras_RockSink":
                    dialog.text = "���, �� ��� �� ��� ������� �� ������ ���� ���������?";
                    link.l1 = "� ��������"+ GetSexPhrase("","�") +" ��� ������ � ���������� ����� ���������, ��� �� �������� �� ���� �������. �������, ��� ���������, �� ����� ��� ����� ��� �� �������, �� ������ ������ �� ����� ��������...";
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_DieHardRock":
                    dialog.text = "���, �� ��� �� ��� ������� �� ������ ���� ���������?";
                    link.l1 = "� ��������"+ GetSexPhrase("���","����") +" ��������� ��� ������ � ���������� ����� ���������, ��� �� �������� �� ���� �������. � ���������, �� ��������, �� ���� �� ���������, ��� �������� �������� ����, ��� ��������� ��� ��������. �� ���� �� ����...";
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_RockTaken":
                    dialog.text = "���, �� ��� �� ��� ������� �� ������ ���� ���������?";
                    link.l1 = "�� � ���� � �����, ��� ���������.";
                    link.l1.go = "Step_3_7";
                break;
                case "TakeRockBras_RockGiven":
                    dialog.text = "��-��, ���� ��� ��������� �� �������� �������� ��������� � ��������. ���� ����������.";
                    link.l1 = "�������, ��� ���������. ��� � ��� ���� ���� ��� �����"+ GetSexPhrase("��","��") +"?";
                    link.l1.go = "Step_3_8";
                break;
                case "TakeRockBras_WaitTwoDays":
                if (GetQuestPastDayParam("questTemp") > 2)
                    {
                        dialog.text = "����, ��� � � �����������, �������� ������ �� ���� ����� �������� ������ ������� � ������������, �������� � ������ ����������.";
                        link.l1 = "��� ��� ��������� ������?";
                        link.l1.go = "Step_3_9";
                    }
                    else
                    {
                        dialog.text = "� ������ ��� ����� ����� ��� ���, �� ������.";
                        link.l1 = "��������, ������ �������-����������.";
                        link.l1.go = "exit";
                    }
                break;
                case "TakeRockBras_SeekRocksMoney":
                    dialog.text = "�� ���, ������������, ��� ��� ������� ��������� �� ������ ���������?";
                    link.l1 = "���� ������ ������, ������ �������-����������. �� � � ������...";
                    link.l1.go = "exit";
                    if (sti(pchar.money) > 500000)
                    {
                        link.l2 = "��� ���������, � �����"+ GetSexPhrase("","�") +" ����������, ������ ���������.";
                        link.l2.go = "Step_3_10";
                    }
                break;
                case "Sp4Detection_toMirderPlace":
                    dialog.text = "�� ���-������ ������ ��������� �� ���� ����?";
                    link.l1 = "� �������, ��� ���������, �� ���� ������ ������ �� �������...";
                    link.l1.go = "exit";
                break;
                case "Sp4Detection_toGovernor":
                    dialog.text = "������������, ��� �� ������ �� ���� ��������.";
                    link.l1 = "��� ������� ������, ��� �������������� ������ �� �������� ����� �� �������. �������, ��� ����� ������������ ����� �� �������.";
                    link.l1.go = "Step_4_6";
                break;
                case "Sp4Detection_toDEstre":
                    dialog.text = "��� � ����������� ������ ������� � ������������� �� �������";
                    link.l1 = "��� ���������, �� ������� � �����"+ GetSexPhrase("","�") +" � ���, ��� ����� ����� ���� ��������� � �������� �'������� �� ����������. ����� ������������, ��� ��� � ���� ����� ���� ������� �� �����, �� �������� ��� � ������������ � �� ����.";
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_1":
                    dialog.text = "��� � ����������� ������ ������� � ������������� �� �������";
                    link.l1 = "��� ���������, �� ������� � �����"+ GetSexPhrase("","�") +" � ���, ��� ����� ����� ���� ��������� � �������� �'������� �� ����������. ����� ������������, ��� ��� � ���� ����� ���� ������� �� �����, �� �������� ��� � ������������ � �� ����.";
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_2":
                    dialog.text = "��� � ����������� ������ ������� � ������������� �� �������";
                    link.l1 = "��� ���������, �� ������� � ����� � ���, ��� ����� ����� ���� ��������� � �������� �'������� �� ����������. � ���� ��, ��� ������� ���������� ���������� ���� �������-����������� - ������� ���� �'�����.";
                    link.l1.go = "Step_4_10";
                break;
                case "Sp4Detection_DEstreIsDead":
                    dialog.text = "������������, ��� ������������ ���� �������������?";
                    link.l1 = "� ��� �����"+ GetSexPhrase("","�") +". ���� � ���, ��� ���� ���� ���� �������� �� ����� �� ������������ ������� ������� � �������-����������� ������� �'�������.";
                    link.l1.go = "Step_4_14";
                break;
                case "Sp5LaVegaAttack_BackToHavana":
                    dialog.text = "��-��, � ��� ���� � ����� ����� �������� �����������. ��� ��, � �� ����������, ��� ����� �� ��������� ��� ���������� ����� ���������� �� ������� ����� ����� ������� ������� �������.";
                    link.l1 = "� ����������� ���������, ��� ���������. � ������ �������� ��� ���� ����� ����!";
                    link.l1.go = "Step_5_3";
                break;
                case "Sp6TakeMess_waitMessanger":
                    dialog.text = "��-�-��, ��� ������ "+ GetSexPhrase("����������� ��������","���, ���������") +".";
                    link.l1 = "� � ��� ����� ���"+ GetSexPhrase("","�") +" ������, ��� ���������.";
                    link.l1.go = "Step_6_4";
                break;
                case "Sp6TakeMess_Action":
                    dialog.text = "��-�-��, ��� ������ "+ GetSexPhrase("����������� ��������","���, ���������") +".";
                    link.l1 = "� � ��� ����� ���"+ GetSexPhrase("","�") +" ������, ��� ���������.";
                    link.l1.go = "Step_6_4";
                break;
                case "Sp7SavePardal_PardalIsSink":
                    dialog.text = "������������ � ����������� ������.";
                    link.l1 = "������, � �� ����"+ GetSexPhrase("","��") +" ������ �������, ��� ������� ��������� ����������� �������������� ������. ��� ������� �����...";
                    link.l1.go = "Step_7_1";
                break;
                case "Sp7SavePardal_GoodWork":
                    dialog.text = "������������ � ����������� ������.";
                    link.l1 = "������, ����������, ���������� ����, ��������� �����������. � "+ GetSexPhrase("���","���") +" � ������� �� ���� ������� � ��������"+ GetSexPhrase("","�") +" � ������� ��� ������ ������� - �� � ��� ������� ��� ������� ��� ���� ��� � �������������� ������ ����������� �������. ����������� �������� ��� ������� ������� �������� �����, ������� ������������ ����� �� ���!";
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_2GoodWork":
                    dialog.text = "������������ � ����������� ������.";
                    link.l1 = "������, ����������, ���������� ����, ��������� �����������. � "+ GetSexPhrase("���","���") +" � ������� �� ���� ������� � ��������"+ GetSexPhrase("","�") +" � ������� ��� ������ ������� - ��� ��� ������� ��� ���� ��� � �������������� ������ ����������� �������. ����������� �������� ��� ������� ������� �������� �����, ������� ������������ ����� �� ���!";
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_DieHard":
                    dialog.text = "������������ � ����������� ������.";
                    link.l1 = "������ �������-����������, � ���������, ��� ������ ��������� ��� �� �� �����. � �� ����"+ GetSexPhrase("","��") +" ������ �������.";
                    link.l1.go = "Step_7_6";
                break;
                case "Sp8SaveCumana_YouLate":
                    dialog.text = "����� �������� �� ������ ��� ������� ����. �� �� ������ ������ ����� � ��� �������.";
                    link.l1 = "� ����"+ GetSexPhrase("��","���") +" � ������ �� ���� �������, ����� �� ������������ ���� �� ������. �� ��� ����� �� �����"+ GetSexPhrase("","�") +" �������, ������� ��� ���� ������ ����������.";
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "20";
                break;
                case "Sp8SaveCumana_DieHard":
                    dialog.text = "����� �������� �� ������ ��� ������� ����. �� �� ������ ������ ����� � ��� �������.";
                    link.l1 = "��������� ������� �������� ���� ������ ���������, ��� ���������� � ��� �� �� ������. � ���� ������, �������� � ����������"+ GetSexPhrase("","�") +", ������� ��� ���� ������ ����������.";
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "40";
                break;
                case "Sp8SaveCumana_GoodWork":
                    dialog.text = "��� ��� ��������, ��� ������ �������. �����������!";
                    link.l1 = "�� ������ �������� ���� ��������. ����� �� ���� �����...";
                    link.l1.go = "Step_8_6";
                break;
                case "Sp9SaveCumana_BackHavana":
                    dialog.text = "������������, ��� � ��� ���������?";
                    link.l1 = "��� ���������, � �������"+ GetSexPhrase("","�") +" �� �������-����������� ����� ����� ������� ����������� ������ ������� ������� �� ������������ ������� ������...";
                    link.l1.go = "Step_9_2";
                break;
                case "Sp10Maracaibo_DieHard":
                    dialog.text = "��� �������, ��� ��������� �������� � ��� ���������� ����������� ������!";
                    link.l1 = "��, ��������, ������.";
                    link.l1.go = "Step_10_6";
                break;
                case "Sp10Maracaibo_GoodWork":
                    dialog.text = "� ��� ����, �� �������� ���������� � ������������ �������!";
                    link.l1 = "�� ���� ��� �������� ������� �� ��� ������� ���������� �������.";
                    link.l1.go = "Step_10_11";
                break;
                case "Sp10Maracaibo_2GoodWork":
                    dialog.text = "� ��� ����, �� �������� ���������� � ������������ �������!";
                    link.l1 = "�� ���� ��� �������� ������� �� ��� ������� ���������� �������.";
                    link.l1.go = "Step_10_9";
                break;
                case "DestrHolland_GoOn":
                    dialog.text = "�� ���� �� ������ ��������� �� �����������, �� ������...";
                    link.l1 = "������ �������-����������, � ���� ���������. ������ ��������, ������� ��������� ����������.";
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad"))
                    {
                        dialog.text = "�� �������� ����������, �������! ������ ������� �� ������!";
                        link.l1 = "����� ���, ��� ���������...";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = "�����������, ������ �������! �� � ��� �� ��� ��� �� ������� � ��������� �����������.";
                        link.l1 = "� ��� ������, ������ ����������.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad") && CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = "������ � ���������� ����� ������� � ��������! ���������� ������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +"!";
                        link.l1 = "���� �������, ��� ���������...";
                        link.l1.go = "Step_11_3";
                    }
                break;
                case "OccupyPortPax_WeWin":
                    dialog.text = "�� ��� ��, �������� ����� ���������� � ��������� �������������. ������ ��������� - ���!";
                    link.l1 = "����� ���, ������ �������-����������. ��� ������� ��������� ����-�-�����.";
                    link.l1.go = "Step_12_4";
                break;
                case "QuestLineBreake":
                    dialog.text = "� �� ���� ���� � ������, ����������� ���� �����. ��� ������ ������ ��� �������.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
                case "EndOfQuestLine":
                    dialog.text = ""+ GetSexPhrase("���","�����") +" " + pchar.name + ", �������� ������������� ��� ������ ������� �������� � ��������� �������. ���������� ��������������.";
                    link.l1 = "������, ��� ���������.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
			}
        break;
        //********************** ����� �1, ������ ������� �� �������. ************************
        case "Step_1_1":
            dialog.text = "��� �������� ����� ��������� ������ �� ����� ������� ��������, ���� � ���, �������, ���� ���.\n"+
                          "�� � ��� ���� ������� � ��������� ������, ��� ����������� ��� ���� ������. �������� ������, ����� ����� ������� ������� ������ � �������� ����� ������ �� ��� ���� ������� ���������.";
            link.l1 = "������� ��������� ������� ��������� ��������?";
            link.l1.go = "Step_1_2";
        break;
        case "Step_1_2":
            dialog.text = "��, ���� �� ������ ������ ��� � �������. ��������� � ���������� ������� ������ ������� ������� ����������� ���������. ������ ��, ����� ���� ����� �� ��������� ���������� �������� ���� ������, ��������� ����� ��������� �������.\n"+
                          "���������� ��������� �� ���� ������� � �������� ��������, ��������� ������� � ������� ������� � ����� ��������� ������ ����� ������� ��������. ������ ��������� ���������� ��� �������� ����, ��� ������� �������� � ���� ����� ����� �������.\n"+
                          "�������� � ���������, �� ���������� ��������-���� ������� ���������������� � ����������� �������� �� ���������� ���������� ������������ �������� ���� ������. ��� ���������� ��� ���� ������� ������� �������� � ������ ��� �� ��������, �� ���� �������� ������� �� ������ ������.";
            link.l1 = "������, ��� � �������...";
            link.l1.go = "Step_1_3";
        break;
        case "Step_1_3":
            dialog.text = "������, ��� ��� ��� � ����. ��� ����� "+ GetSexPhrase("����� �������","����� �����") +", ��� ��, ���"+ GetSexPhrase("","��") +" ������������ ������ �� ������ ������ ���������� ��� ��������� �������. �� ������� ����������. �������� ���� ����������� ������� ������ � ��������, � ������ ����� ��� - ���������, �����, ������� � �������.";
            link.l1 = "������ �������. � �����"+ GetSexPhrase("","�") +" ���������� ��������������� � ���������� ������.";
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = "��, ����� ��������� � ����.\n"+
                          "����������� �������� ��������� ��� ����� ��������� ����������. � �����, ������� ����������� ��������� ����� ���������� ����� ������, ��������� ��� �������� � �������� �������. ���� ������ ������� 500 ����� �������! ��� ����� ����� ���������� � ����-�����, ��������� �� ������ ����� ������� � � ������� ��������� �� �� ���.\n"+
                          "�� ������ ������� ���������� � ������ � ���������� ������� �� ������. ������� �������� ����� ���������, ��� ��� � ������ ������ �������� ���������������. � ����� � ���� ������� ���������������� ���������� � �������� �����, ����� �� �����. �� ��� ����� ��������������� �� ����������� ��������� ����� ��������� ��� �����, ��� �������������� ����������.\n"+
                          "��� ��� �������?";
            link.l1 = "��, ������ �������-����������.";
            link.l1.go = "Step_1_5";
        break;
        case "Step_1_5":
            dialog.text = "� ��� ���� ����� �� ������������ �������, �� ������. ���������� � ������������� � ����.";
            link.l1 = "���������� ���������.";
            link.l1.go = "Step_1_6";
        break;
        case "Step_1_6":
            SaveCurrentQuestDateParam("questTemp");
    		// ��������� ������� � ��� -->
    		pchar.questTemp.NationQuest = SPAIN;
    		// ��������� ������� � ��� <--
    		pchar.questTemp.State = "SaveFromMorgan_toPrison";
            AddQuestRecord("Spa_Line_1_SaveCitizens", "1");
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaPrisoner"+i, "usurer_"+i, "man", "man", 10, SPAIN, -1, false));
                sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
                LAi_SetCitizenType(sld);
            	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto9");
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_1_7":
            dialog.text = "�� ��� ��, ���� ������ ������ �������� ��� �� ��������� ���� ������� ��� �� ���������� ��������-������ �����-���� �����������. �������� ������ ������������ 50 �����. ���, ��� �� ������ � ���.";
            link.l1 = "���������, �������� �������-����������. ������, �� ���������� ���������.";
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = "� ��� ��?";
            link.l1 = "�� ��� ��, ���� � ���� ���������� 50-�� ������� �������� ���� '0', �� ������ �����, ������� �� �� �������� �������� ����� �������.";
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = "�-�-�, �� ��� ���. ��, �������, ����� ���� ��������� ������ ����� ������������ �����, ��������� ��� �����, ��� ��� ������ ���� ��������, �� ����� 50 ����� �� ���������� �� ��� ����� ��� ������, �� ��� ��?";
            link.l1 = "� ��, ������. �� ������� � ������� ������� ������������ ������!";
            link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = "� ����� ������, �� ���� ��� ������ �����������... ������������� �� ��� � ���������� ����� �� �������.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
			if (startherotype == 2)
			{
				pchar.questTemp.CurQuestNumber = "4";
			}
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_1_SaveCitizens");
            AddMoneyToCharacter(pchar, 50000);
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                RemovePassenger(pchar, sld);
         	    sld.LifeDay = 0; // ������ ���
            }
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�� ������, ��� ������� �������-���������� ������-�-������ ����� �������� " + GetMainCharacterNameGen() + " ��� ������������ ����� �������, ����������� ���� �������� ��������. � �� ������, ��������� ���� ������� ���������.", SPAIN, 5, 1);
		break;
        //********************** ����� �2, ������� ����������. ************************
        case "Step_2_1":
            dialog.text = "���� ���������� ������ ��� �����... �� ��� ��, ������ ����� ��� ����� ������. � ��� ������ ������������������ ������ ������� �� �����, �� �������� ������������ � ��� ������������ ��������������, ������������� � �������� �������.\n"+
                          "� �������������� ���. ������������� � ��������, ��� ��������� ���������� ���������� �� ���������� ����, � ������� �� �����. ������� ���, ��� �� ��������, �� ����������� �� � ���. � ��� ���� �������?";
            link.l1 = "���, ������ �������-����������.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "����� ��������.";
            link.l1 = "...";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toDeSouza";
            AddQuestRecord("Spa_Line_2_Inquisition", "1");
            SaveCurrentQuestDateParam("questTemp");
            sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "priest", "man", "man", 10, SPAIN, -1, false));
        	sld.name 	= "�������";
        	sld.lastname = "�� �����";
			sld.model.animation = "man";
            sld.Dialog.Filename = "Quest\AntonioDeSouza.c";
			sld.greeting = "Gr_padre";
            LAi_SetHuberType(sld);
        	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
        break;
        case "Step_2_3":
            dialog.text = "�� ��� � ������. �� ��������� ���� ������ �� ������ ��������� �� ����� ������, � ����� ����� �� ��� �� �����. �������, ��� ����� ��� ����� ����.";
            link.l1 = "������ � ����� �������, ������!";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "15";
            CloseQuestHeader("Spa_Line_2_Inquisition");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			
			//******����� "����� �� ������" Sinistra******												
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));	//���������� �������
			sld.name = "����������";
			sld.lastname = "�������";
			LAi_SetCitizenType(sld);
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_time";
			sld.sex = "man";
			sld.City = "Havana";
			sld.location	= "Havana_town";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			sld.talker = 7;
			sld.nation = SPAIN;
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Havana_town","goto","goto6");
					
			//�����
			AddSimpleRumour("����� �����, ��� ������� " + GetFullName(pchar) + " ���������� ��������� ��������� ������ �� �����! ����������... ��� ����� ���� ����� - ����� �� ����.", SPAIN, 5, 1);
        break;
        //********************** ����� �3, ��������� ���� �������. ************************
        case "Step_3_1":
            dialog.text = "����, �� ���-������ ������ � ������� ���� ���������?";
            link.l1 = "��, ��������� ��������, ����� ������� �����. ��������� �� �������.";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "��, ��� ���. ��������� �������� ���� ��� ���.\n"+
                          "��� ���, � ������� ��������� �� ���� ������� ��� � �������� �� ��� ����� ����������. � ����, ����� �� ��������� ����� ������������ ���� ���������. � ��� ����� ����� - ��������� ��� �����.";
            link.l1 = "� ��� �����������? ����� ����� �������, � ���� ����� ���� ���������.";
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = "� ���? � �� ����� ������� ���, "+ GetSexPhrase("������","���������") +" " + pchar.name + ". �� ����������?!";
            link.l1 = "��� ���������, � �� ����� �� �����, �� �������. �������, ��� �� ����� ����������� � ���� ���������! �� � ���� � ���� ��, ��� �� ���� �������������� ������� ���������. � ����� ����� ����� ��������� ��� ������.";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "� ��� �������. �� ��� �� ������� - ��� �������� ����� ��� �����. ������, �� ���, � ������ ���������� ��� ���������� ������� �� �����. ��� ���������� ������ ����������, �� ���������, ��������� ��� ����� ��� ���?";
            link.l1 = "��, ������, �������. �� ��� ��, � ���� ������� ���, ��� ��������� ��� ��������� ��� �������� ���������� ������� ��������� � ������ ������.";
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = "�����������! ���, ����� ��� ������� � ����� ���������� � ����� ������ �� ���� � ����� ��������.";
            link.l1 = "�� ��������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toTortuga";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "1");
        break;
        case "Step_3_6":
            dialog.text = "��, ��� �����. � ����������� � ���.\n"+
                          "������ ����� �������� ���� ������... ������, �� ������ ������ � ���� �� ������ ����� �� �������, ��������, � ��� ��� �������� ����...";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������ �������-����������. �������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//�����
			AddSimpleRumour("�� �������, ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" ������� �������-����������� - �� ����"+ GetSexPhrase("","��") +" ��������� ����� ������� ������� ���� ���������. ��������"+ GetSexPhrase("�","��") +", ����� ������...", SPAIN, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = "�������! ������ ������������� � �������� � ������ ��� ���������� ������� �� �����.";
            link.l1 = "������, ������, ����� ���������.";
            link.l1.go = "exit";
        break;
        case "Step_3_8":
            dialog.text = "������� �� ��� ����� ���� ����, ��������� ������� ������ ���������� ��� ���� ����������, ������ ���� �������.";
            link.l1 = "������, ���� � ��� ����� ��� ���, ������.";
            link.l1.go = "exit";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "9");
            pchar.questTemp.State = "TakeRockBras_WaitTwoDays";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_3_9":
            dialog.text = "�������, �� ������ �� ��� ��������� �� ����� �����! ��� �������� ������� ����� ��, ���� ����������.\n"+
                          "�� �� ��� ����� ��������� ������� ���� ���������� ��� �����, �� � ������ ��� ������� ������ ���������� ��� ����� ��������������� ������������ �����. �� �������� � ������� ��� � ���������� ����� �� ����, ��������� � � ������������ ������.\n"+
                          "�� ������ ����� � ��������� ��� ������ ���������. �� ��������������� ������� � ���, � ����� ���������, ����� 500000 ��������!";
            link.l1 = "�������, �������! ������, � ������� ��������������� ����� ������� ��������?";
            link.l1.go = "Step_3_13";
        break;
        case "Step_3_13":
            dialog.text = "���, � ���������...";
            link.l1 = "�����, ����� ������� ��������� � ��������� ������� ���� ����������� ��������?";
            link.l1.go = "Step_3_14";
        break;
        case "Step_3_14":
            dialog.text = "��� ��� ���������� - ��� �������� ����� ���� ������� ������. �����...";
            link.l1 = "�����... ������, � ���� ������������ �� ����� ��������� ��������?";
            link.l1.go = "Step_3_15";
        break;
        case "Step_3_15":
            dialog.text = "���������. ����� ����� ��������� �������� ��������� - ����. � �� ������ ��� ��� ��� � �����������, ��������� �����, ����� �������� ��������� ����� - 500 �����.";
            link.l1 = "������, ������ �������-����������, � ���������� ��������� � �������.";
            link.l1.go = "exit";
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.gold = 150000;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian18 = 1;
         	pchar.GenQuestBox.Hispaniola_Cave = true;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry5 = 250;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry14= 10;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.potion3 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.mineral8 = 1;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry7 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry2 = 20;
         	pchar.GenQuestBox.Beliz_Cave = true;
            pchar.GenQuestBox.Beliz_Cave.box1.items.gold = 50000;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian6 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian11 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian15 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian12 = 1;
            pchar.GenQuestBox.Beliz_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion5 = 10;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potionrum = 2;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion4 = 10;
            pchar.questTemp.State = "TakeRockBras_SeekRocksMoney";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "8");
        break;
        case "Step_3_10":
            dialog.text = "�����������! ������ ������� �������� ����... �� ������� � ����� ��������� 500 �����, �������������, ���� ���� ���������� 100 ����� ��������.";
            link.l1 = "���������, ������ �������-����������.";
            link.l1.go = "Step_3_11";
        break;
        case "Step_3_11":
            dialog.text = "������... ������ � �� ���� ��� �����������, �� ����� ������ ����� ���� � ���� �� ������.";
            link.l1 = "������, ��� ���������, ���� � ��� � ��������� �����. � ������ ��������� �����������...";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, -400000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//�����
			AddSimpleRumour("�� �� ������� ���������� �������? ���"+ GetSexPhrase("��","��") +" ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" ����� �������� ������� ���� ���������. ����� ������� �����������!", SPAIN, 5, 1);
        break;
        //********************** ����� �4, ������������� ��������. ************************
        case "Step_4_1":
            dialog.text = "������ ������������ �������� �������������. ����� �������� ��, ��� ���������� ���������, ��� ��� ���������.\n"+
                          "��������� ������, ��� ���� ������� �� �����, ��� ���� � ����������� ���� ������ � �������� �������. ��� ���� � ������ ������ ��������, ��� ����� ��������� �� �����.";
            link.l1 = "��� ��� ��! � ����� ������ �� ������? �������, ��������?";
            link.l1.go = "Step_4_2";
        break;
        case "Step_4_2":
            dialog.text = "���, � ���� ����� ��� ���� ������ ������ �� ����. �������� ��� ���� ������ ������ ������� � ����� � �������� ���� ���� �������� ���� ��������.";
            link.l1 = "� ��� �� ������� ��� ����?";
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = "��� �������...";
            link.l1 = "��� �������, ������?";
            link.l1.go = "Step_4_4";
        break;
        case "Step_4_4":
            dialog.text = "���, ��������... ������� � ���, ��� ��������!";
            link.l1 = "����� ��������, ��� ���������. ������� ��� ���... �� ������, ��� �� ��� �������, � �� �����. ����� ���� ���������� �����������.";
            link.l1.go = "Step_4_5";
        break;
        case "Step_4_5":
            dialog.text = "��� ���� � ��� ����������� ������. ����������, � �� ���� ��� ��������� ���������� �������������� ������������, �� ������ ������ � ����� ������� ���.\n"+
                          "����� ����������, ���� ���������. �� ��� ��� ������������... �� �������� ��� ������ - ��������������. ��� ����� ����������� ���� � ������������� ����������, � �� - ��������� ����������� �� ������ ������.";
            link.l1 = "������, ������ �������-����������. � ������ ���, ��� �����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toMirderPlace";
            AddQuestRecord("Spa_Line_4_MirderDetection", "1");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","�"));
         	pchar.GenQuestBox.Havana_houseS1Bedroom = true;
            pchar.GenQuestBox.Havana_houseS1Bedroom.box2.items.letter_notes = 1;
        break;
        case "Step_4_6":
            dialog.text = "������� - ��������� �������� ���� ������... � ��� ����� ����?";
            link.l1 = "������ ������������... �� ��� ��� � ���"+ GetSexPhrase("��","��") +" �� ����� ������������ - ������������ ������...";
            link.l1.go = "Step_4_7";
        break;
        case "Step_4_7":
            dialog.text = "(������) ��, ���� �� ����, ��� �������... ��� ����� ���������� �� ������� � �����������, ��� � ����.";
            link.l1 = "������, ��� ���������, � ��� ������.";
            link.l1.go = "Step_4_8";
            TakeItemFromCharacter(pchar, "letter_notes");
        break;
        case "Step_4_8":
            dialog.text = "������ ��� �������� ����������� ����-������� ��������, ������ �������� �� 50 ����. ������ �������� �������� ��� ���������������� ������������� �� �������. � �������, �� ����������� ������� ����������� ���� �� �����...";
            link.l1 = "�������, ��� ���������, ��� ����� ������. �������, � ��������� � ���������� ������.";
            link.l1.go = "exit";
            GiveNationLicence(FRANCE, 50);
            pchar.questTemp.State = "Sp4Detection_toTortuga";
            AddQuestRecord("Spa_Line_4_MirderDetection", "4");
            sld = GetCharacter(NPC_GenerateCharacter("ServantDEstre", "Barmen_13", "man", "man", 10, FRANCE, -1, false));
        	sld.name 	= "�����";
        	sld.lastname = "";
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            LAi_SetStayType(sld);
        	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "goto", "goto2");
        break;
        case "Step_4_9":
            dialog.text = "���� �������������... ��, ����� ����, ����� ������� ������� ������.\n"+
                          "� ��������� ����. ������� ��� �������� ���� ������, � ���� ��� ��� ��� ���.\n"+
                          "�������, �� ������ �������� �� ��� �� ����� ������������, ��������, ���-������ �������������� � �����������...";
            link.l1 = "������, ������ �������-����������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            TakeNationLicence(FRANCE);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("�� ������, ��� �������-���������� ������� �������� " + GetMainCharacterNameDat() + " ������������� �������� ���������� �� �����. ������, ������� ������� ������"+ GetSexPhrase("��","���") +" ����������...", SPAIN, 5, 1);
        break;
        case "Step_4_10":
            dialog.text = "�����������...";
            link.l1 = "� ������"+ GetSexPhrase("","��") +" ����� �����������, �� ����� ��� ��� �� ������� - �� ����� �����, ��� �������� ������������.";
            link.l1.go = "Step_4_11";
        break;
        case "Step_4_11":
            dialog.text = "��� � �������. ����� ������� ����������� �� ����� �������, ������� � ������� � ��� - ��� ��� �� � ������ �� ����� ������ ��������...";
            link.l1 = "��� ���, �� ��������� � ��� ��� ������� ������, ��� ������ �'������� - ������ ����� ���� ������� �� �����. ���, ����������, � ���...";
            link.l1.go = "Step_4_12";
        break;
        case "Step_4_12":
            dialog.text = "�� ��� ��, ���� �� ��� ���� ��������� � ����� ���� ������� �������, ��, �������, ������ �� ����� �� ���������. ����� ��������, ��� ����� ���� ������� �������� �� ������ ������ ������� � ��������, ������� �� ��������� � ����� ����. ��� �� �����, �� ���� �� ��� �����...";
            link.l1 = "������ �������-����������, � ���� ������� ������������� �����������?";
            link.l1.go = "Step_4_13";
        break;
        case "Step_4_13":
            dialog.text = "��, �������. ���� ������� ���������� 3 ������ ��������. ���� �� �� ������ ����� ��� '���������� ����', �� ������� ���� �� ����.\n"+
                          "� ������ ����� ��� �������� ����, ��� ����� �������� ������������� �� ����� � �������� � ��������� ��� ������.";
            link.l1 = "������, ��� ���������, �� ��������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 3000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Grappling", 100);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 120);
			ChangeCharacterReputation(pchar, 2);
			//�����
			AddSimpleRumour("�� ������, ��� �������-���������� ������� �������� " + GetMainCharacterNameDat() + " ������������� �������� ���������� �� �����. ������� ���"+ GetSexPhrase("��","��") +" ������, �� �������� �����-�� �������. �� ��������� �� �����"+ GetSexPhrase("","�") +".", SPAIN, 5, 1);
        break;
        case "Step_4_14":
            dialog.text = "��� ������ � ��� ��������...";
            link.l1 = "��� �� �����, ��� ������. ������ ��� ��������� �� ������� � ������ ���������, ������.";
            link.l1.go = "Step_4_15";
        break;
        case "Step_4_15":
            dialog.text = "�� ��� ��, ���� �� ��� ���� ��������� � ����� ���� ���������� �������, ��, �������, ������ �� ����� �� ���������. ����� ��������, ��� ����� ���� ������� �������� �� ������ ������ ������� � ��������, ������� �� ��������� � ����� ����. ��� �� �����, �� ���� �� ��� �����... ��� ��� �� ���� ���� ����?";
            link.l1 = "����������� ���������� ���� �'�����, ���������� ���� �������-����������� �'�������.";
            link.l1.go = "Step_4_16";
        break;
        case "Step_4_16":
            dialog.text = "���������! �� �����, ��� ��� �� ����� �������� ��� ����, ������ ������� ����� � ���� ��� ����� ������ �����������! ������ ���������� ���������!";
            link.l1 = "��� ��� ���������� - ������ ���� ���� �����. � ��������"+ GetSexPhrase("","�") +" ��� �� ������� � ����"+ GetSexPhrase("","�") +".";
            link.l1.go = "Step_4_17";
        break;
        case "Step_4_17":
            dialog.text = "���� ������! �� ������������� �������� ������ � ������� �����, � ���� ��. � ���������� ��� �� ����������� ��������.";
            link.l1 = "�������, ��� ���������.";
            link.l1.go = "Step_4_18";
        break;
        case "Step_4_18":
            dialog.text = "�� ��������. �� � ��� ����� �������� ���, ����� ����� ���� �� ���� ��� ���������. �������, ���� �� �������� �������...";
            link.l1 = "�� �������� ��������� � ��� ������?";
            link.l1.go = "Step_4_19";
        break;
        case "Step_4_19":
            dialog.text = "�? �� � ���� ����, � ���� ���� ���� � ��������. � ��� �������� �������� ������������� ���� ���� � ����������� ������ ������������� � ������ ���� ������������. �������� �������� ����������� ������� �����, ���� ����� ���� �������� �� ���� �������...";
            link.l1 = "�������. �� ��� ��, ���, ����������, ��� �� ��� ����. ������ �������-����������, � ���� ������� ������������� �����������?";
            link.l1.go = "Step_4_20";
        break;
        case "Step_4_20":
            dialog.text = "��, �������. �� �������� ���������� � ������������ �������, ���� ������� ���������� 120 ����� ��������.\n"+
                          "� ������ ����� ��� �������� ����. � �� ��������� ����������� �� ��� � ���������� ����� �� �������...";
            link.l1 = "������, ��� ���������, �� ��������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "4";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 120000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//�����
			AddSimpleRumour("�� ������, ��� �������-���������� ������� �������� " + GetMainCharacterNameDat() + " ������������� �������� ���������� �� �����. ������� ���"+ GetSexPhrase("��","��") +" ������, �� �������� �����-�� �������, � ��������"+ GetSexPhrase("","�") +" ��� �� ��� ����.", SPAIN, 5, 1);
        break;
        //********************** ����� �5, ��������� �� �� ����. ************************
        case "Step_5_1":
            dialog.text = "��� ������� � ��������. �� ��������� ����� �� ���������� ��������� � ��� ������������. ������������, ��� � ���� ��� ������� - ������ �� �����, ��������� ��������� ������ ��������.";
            link.l1 = "�����������...";
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = "��� � ��������. ������������ � �������� ����������.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_toSantiago";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "1");
 		AddQuestUserData("Spa_Line_5_LaVegaAttack", "sSex", GetSexPhrase("","�"));
        break;
        case "Step_5_3":
            dialog.text = "��, �������. �������� ��� ������������ ��������, ��� ����������� ����� ���������� ������. � ���������� ��� � ���� �������!\n"+
                          "�������, ���������� ���� ��������� �������� ���� � ����������� ���� �������� ������������ ��������?";
            link.l1 = "��, ������ �������-����������, � ����������� ����. ��� � �������";
            link.l1.go = "Step_5_4";
        break;
        case "Step_5_4":
            dialog.text = "�� ��� ��, �����������! ��� ��� � ���� ����� ��������� �����, �������� � ���� ����� ��� ��� ��� ������.";
            link.l1 = "���� �������� ��� ����� �� �������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_5_LaVegaAttack");
			//--> ����� � ������� �������
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "hidden_effects");	
			//<-- ����� � �������
            //===> ������ ���� :( ������ �� ����� ����� ������� �����.
            sld = characterFromID("Edward Mansfield");
            sld.name 	= "�������";
        	sld.lastname = "�����";
        	sld.model.animation = "man"
            sld.model = "officer_8";
            sld.Sp5LaVegaAttackDone = true; // fix 1.2.3
            sld.quest.meeting = "0";  // fix 1.2.3 ���� ����� ���
            // ������ ��� ��� 1.2.3 SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			SetLocationCapturedState("LaVega_town", false); // fix 1.2.3 ������� �����
			//�����
			AddSimpleRumour("�������, ��� ��� �� ��������� �� ��� ���� ����� ���������� ���������. ����� ����, ����� � ���...", SPAIN, 5, 1);
        break;
        //********************** ����� �6, �������� �� �������. ************************
        case "Step_6_1":
            dialog.text = "���� � ���, ��� �������� � ���������, ���� �� �����, ������ ��������������� ����� �����. ��� � �������, ������� XIV ����� � ���� ������������� ����� �� ����������� ������� � ������. ���� ���������� �� ������������ ������� ������������� ���, ������ �� ���������� ������ ��������� ������ ����� ������, ���� �� �������� ���� � ����� - ���� ��������, ��� � �������� �������� � ��������.\n"+
                          "���� ������ ����������� � ���������: ��� ���������� ����� ����� ���������� �� ������� � ���������� ����������� ���-���� �� ��������������� ��������� ����� �������-������������ ������� ������� ����������� � �������-������������ ������� ��������� �'��������.\n"+
                          "�������� � ��������������� ������ ���������� ��� ���������, ��� ��� ��� ����� ����� ����������� ����-������ �� ���. ��� ����� ��������, ������� ���� ��������������� ��������� ������ ������������ � �������� �������������� ������������ �������� ���������� � ���������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. � �����-�� ������� ���������"+ GetSexPhrase("","�") +" � ������ ����������?";
            link.l1.go = "Step_6_2";
        break;
        case "Step_6_2":
            dialog.text = "�� � ���� ����. ������������, � ��� � ���� ��� ��������� - �� ����������� �������� ����� �� �������, ��� ������ ������� � �������������� �������.";
            link.l1 = "��� ���������, � ���������� ������ ��� ����� ���������������.";
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = "� ��� ���� ������. � ������ ��� �������� ����������� ����-������� �������� ������ �� 60 ����. �� ������ ���������� ��� ������ ���������� ����� � ��� ����� �� � ��� �� ����������.\n"+
                          "�� ��� ��, ��� ���������� ���� ��������. �� ������ ���������� � ���������� �������.";
            link.l1 = "���������, ������ �������-����������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp6TakeMess_toTotuga";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "1");
			GiveNationLicence(FRANCE, 60);
        break;
        case "Step_6_4":
            dialog.text = "��, ������������ �� ���������� �������.";
			if (CheckCharacterItem(pchar, "letter_1"))
			{
				link.l1 = "��� ������� ������ ��������������� ��������� ����� �������-������������� ������� � �������.";
				link.l1.go = "Step_6_6";
			}
			else
			{
				link.l1 = "� �� ����"+ GetSexPhrase("","��") +" ������ ������ �� ��� ���. ��� �������, ��� ��� ���������� � ��� ������� ��� ��� �� ���������...";
				link.l1.go = "Step_6_5";			
			}
        break;
        case "Step_6_5":
            dialog.text = "� ����������� � ���, ����� �����... �� ��� ��, �� ��� �� ����� �����. ������ ��������� � ���� �������, �������� � ����� ��������� ��������� ��� ������ ������������ �������...";
            link.l1 = "������, ������ �������-����������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
            BackItemDescribe("letter_1");
  			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//�����
			AddSimpleRumour("��� �������-���������� �������� �������� " + GetMainCharacterNameGen() + " �� ������� � �����-�� ����� ������ ����������. ������� ������"+ GetSexPhrase("��","���") +" �� � ���, ���� ����� - ��������"+ GetSexPhrase("�","��") +"...", SPAIN, 5, 1);
         break;
        case "Step_6_6":
            dialog.text = "�����������, " + pchar.name + ", ������ �����������!";
            link.l1 = "�������, ��� ���������...";
            link.l1.go = "Step_6_7";
        break;
        case "Step_6_7":
            dialog.text = "������ � ��� � ����� ��������� �������� � ��������������� �����... �� ��������� �������� ������.";
            link.l1 = "�������������, �������� �����������, ��� ��� �������...";
            link.l1.go = "Step_6_8";
        break;
        case "Step_6_8":
            dialog.text = "50 ����� ����� - ��� ���� �������! �������� ��������... ����� ��� �� ��������� ������� �� ������, �� � ������ ������� ������ ��� �����.";
            link.l1 = "������, ������ �������-����������.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "9";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + ", ������ ���������"+ GetSexPhrase("","�") +" ������������ ���� �� �������. �-��, ��������� "+ GetSexPhrase("����� ��������","���� �������") +" ����� ������ �����������...", SPAIN, 5, 1);
		break; 
        //********************** ����� �7, ������ �������. ************************
        case "Step_7_1":
            dialog.text = "������, ��� ����� � ����� �����. ������ ��� ���������� �������� ������ � ���� ���������...";
            link.l1 = "��� ����� ����, ������, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +".";
            link.l1.go = "Step_7_2";
        break;
        case "Step_7_2":
            dialog.text = "�� ��� ��, ����������, ������, �� ���������� ��� �� ��������. ������������� � ������. ����� ��������� ����� ������ ��������� ����, ��������, � ���� ����� ���� ��� ���.";
            link.l1 = "������, ��� ���������. �� ��������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Spa_Line_7_SavePardal"); 
		break;
        case "Step_7_3":
            dialog.text = "�����������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", ������ ���������!";
            link.l1 = "������, ��� ��� ������� ���, �������, �������, ��������� ��� ����������� �������...";
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = "��� ��������... �� � ���� ����������� ������ �������� ��������� ������� � ������� �������. 25000 ������ - ��� ���� �������!";
            link.l1 = "��, �����... �����... ��, ����������, �� � ������� ����!";
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = "����� ���������� �������! � � ��� �� ��������.\n"+ 
				          "������ � ��� �� ����������, ������ ������� ����� ������ ���� � ���� � ���������� - ���������� ���� ��� ��������� ��������. �������, � ����, ��� ���� �������...";
            link.l1 = "������, ��� ���������, ���� � ��� �������� � ��� �����.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 25000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_7_SavePardal");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sneak", 250);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			//�����
			AddSimpleRumour("�������, ��� �� ������ ������ ����� �������! ��������� �������� ��� ���� ����������, �� �������"+ GetSexPhrase("�� ����","�� �����������") +"!", SPAIN, 5, 1);
        break;
        case "Step_7_6":
            dialog.text = "�-��, � �����������, ����� �����... �� ��� ��, � ��� ������ �� ����������. ����� ��������� ����� ������ ������� �� ��� �� �����, ��������, � � ����� ���� ��� ������ ������������ ��������...";
            link.l1 = "������, ��� ���������, ��������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_7_SavePardal"); 
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("����� �����, ��� ������� ����� �� ������ �� ����� ����. �������� ���, "+ GetSexPhrase("������ ����","��������� �������") +"...", SPAIN, 5, 1);
        break;
//********************** ����� �8, ������ ��������� �� ������. ************************
        case "Step_8_1":
            dialog.text = "� ���������, ������ � ����� ������. ��� �������, ��� � ������� �� ������� ���� ���� �������� ������� ������� ������, ��� ���������� ������������ ��� �������. ����������� �� �����������, ��� ������ ��������� ���������� ������ �������...";
            link.l1 = "� �� �� ����� �����-�� ������� �� ��������?";
            link.l1.go = "Step_8_2";
        break;
        case "Step_8_2":
            dialog.text = "��, "+ GetSexPhrase("���� ���","������� ���������") +", ��� �������� ���� � ���� � ����� ������� �����... �������, ���� ������, ������ ����� �� ���� ������. � ������ ����� �� ������ �������� ��������� � ������������� ����� � ���������, ����� ����������� �������� �� ��� �� ������� ������������� ������...\n"+
				          "��� � ��������, ������, ��� ������ ���� � ������ ������� �������� ������������ � ����...";
            link.l1 = "�������� ���, ������...";
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = "������, ��� � ���� �� �������� ������� � ������. �� ��������� �� ������ ������, ��������� ����� ������ �� ��� ������� � ������� �����������! � ��� ��� ����� ������� �����, �� ������ �� ���� �������� ��������.\n"+
				          "��� �� ��� ���������� � ����������� ���� ������, ����� �������� ��� �������, ����������� ���� ������, ������ � ������� ����� ����������...\n"+
						  "�� ���� ��� �� ������ ���������� �������� ������ ������, ��� � �������� ����� �������. ���������� ������������� � ������ � �������� ��������� �������� ��� ������������� �������� ������.";
            link.l1 = "� ��� �����"+ GetSexPhrase("","�") +", ��� ���������. ����� ���������.";
            link.l1.go = "Step_8_4";
        break;
		case "Step_8_4":
            dialog.text = "�������! � �������, ��� � ����� �����, � ����� ����� ������ � ��������, ��������� ������ ������ ������! �� ��������� ����.";
            link.l1 = "������� ����� ����������, ������ �� �����������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp8SaveCumana_toCumana";
            AddQuestRecord("Spa_Line_8_SaveCumana", "1");
			SetTimerCondition("Sp8SaveCumana_RescueTimeOver", 0, 0, 20, false);
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1.location = "Cumana";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition = "Sp8SaveCumana_Battle";
        break;
		case "Step_8_5":
            dialog.text = "��� ����, � ����� ��������� ����. �� ������ ��������� � ���� � ���������� ��������� �����, � ���� � ���� ��� ��� ��� ���. �������, ������������� ��������, ��� ��������� �� �����...";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ��� ���������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			SetLocationCapturedState("Cumana_town", false);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �� �����"+ GetSexPhrase("","�") +" ������ ������� ������! ��������� ������...", SPAIN, 5, 1);
        break;
		case "Step_8_6":
            dialog.text = "�������! ������� ���� �� ������ ������� � ��������� ����. � ������� �� ����������� �������� ����� ������� �� ��������� ������ 100000 �������!";
            link.l1 = "� ��������������, ������. � ������ ��������� �����������, ��� ����� �������� � ������� ������� ����� ���...";
            link.l1.go = "Step_8_7";
        break;
		case "Step_8_7":
            dialog.text = "������, "+ GetSexPhrase("���� ���","���������") +". ����� ��� �� ��������� ������� �� ������, ����� ����� ����, ��� �� ����� ������������ ���.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ��� ���������.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "7";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//�����
			AddSimpleRumour("�������, �������, ��� ��� �� ������ ������! ��������� ��� �������� ���� ����������, ������"+ GetSexPhrase("","���") +"...", SPAIN, 5, 1);
        break;
//********************** ����� �9, ������ ������� �������. ************************
		case "Step_9_1":
            dialog.text = "������� ����� ����������� � ������������� ��������. ����� � ������ ������� �� ����, ��� ���������� � � ����������� ����� �����. �������� �������� ����������� ������ �� ���� ��� � ����������� ����� �����.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ��������� ����������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp9SaveCumana_toPortoBello";
            AddQuestRecord("Spa_Line_9_FourGolgGaleons", "1");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","�"));
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_SpaLineQ10");
            GiveItem2Character(pchar,"letter_1");
        break;
		case "Step_9_2":
            dialog.text = "�� ������ ���� ����������� ������� �� ������, ��� ��� ����� ������?!";
            link.l1 = "������, � ������� �� ����, ��� ��� ����� ������, �� ��� ���� �������, ��� � ������� ���� �������� ��������� ������� �������.";
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = "� ���, ���������?";
            link.l1 = "��������� ������� ������� - ���, ���� ������ ������� ��� ����������� ���� �������� ��������. ��� ���� ��������� ������ ��� �������.";
            link.l1.go = "Step_9_4";
        break;
		case "Step_9_4":
            dialog.text = "������ �� ��� ������?";
            link.l1 = "������, �� ��� ������ ����� ������� ������� � ������������ ������� ������� ��������� ����� ���������� ����? �����, �������, ������������, ��� ��� ��������� � ����� ������������, �� ��� ������������.";
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = "���� ������, ������, ��� �� ����� ���� ���� � ���������� �������, ���� � ��������������. � ���� � ���������, � ���� ������� ���, ��� �� ������� ����?";
			iTemp = 0;
			iMoney = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_GALEON_L) 
					{
						iTemp++;
						iMoney = iMoney + sti(sld.Ship.Cargo.Goods.Gold);
					}
                }
            } 
			npchar.quest.money = iMoney;
			if (iTemp < 4 && iTemp > 0)
            {
                if (iTemp == 1)
                {
					link.l1 = "������, ��������� ���� ���������. ��� ������� ��������� ������ ���� ������.";
					link.l1.go = "Step_9_6";
                }
                else
                {
					link.l1 = "������, ��������� ���� ���������. ��� ������� ��������� " + iTemp + " �������...";
					link.l1.go = "Step_9_6";
                }
            }
            else
            {
				if (iTemp == 0)
				{
					link.l1 = "������, ��������� �������� ���� ��������� � ���������� ������� �������. � �������"+ GetSexPhrase("","�") +" ��� �������...";
					link.l1.go = "Step_9_8";				
				}
				else
				{
					link.l1 = "������, ���� ��������� �������� � ���������� ������������, ��� ������� ��������� ��� ��������� ��� �������.";
					link.l1.go = "Step_9_11";
				}
            }
        break;
		case "Step_9_6":
            dialog.text = "��� ����� �����. � �������, ��� �� ��������� � ���������� ��������, �� �� ����� �� ���� ����� ���������"+ GetSexPhrase("��","��") +". � ������ ��� ����� ������������ � ������� �� ��������� ��������� � ��������� ������... � ��� �����, ����� ������� ����� ������������� ������ � ������!\n"+
				          "�-��, ����� � ����� �����. � ����������� �� ���, � �� �� ������ ��������� ����� �������.";
            link.l1 = "��� ���������, �������� ���, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +". � ���� ����� ����... ������ ���� ���� ������� �������, � � ���� ��� ����� ���� ������� ��� ������ ������� ��������! ������, �� ��������� ����������� ����� �����. ����� ����, �������� �� ���� ��������� ������ � ����?";
            link.l1.go = "Step_9_7";
        break;
		case "Step_9_7":
            dialog.text = "����� ����, �� ��� �� ���� ����. � ������� ���, �� ���������� ���� �������������� ������� ��������� �� ������� ����� ����.";
            link.l1 = "� �������...";
            link.l1.go = "Step_9_71";
		break;
		case "Step_9_71":
			if (sti(npchar.quest.money) < (iTemp*1200))
			{
				dialog.text = "������� � ����� ��� �������� ���� ������. � ���������� �� ������ �������� �� ��� � ����������, �������� � ��� ��� �������� ���������� �������...";
				link.l1 = "�������, ��� ���������.";
				link.l1.go = "Step_9_exit";
				pchar.questTemp.Waiting_time = "20";
				pchar.questTemp.State = "empty";
				SaveCurrentQuestDateParam("questTemp");
				pchar.questTemp.CurQuestNumber = "10";
			}
			else
			{
				dialog.text = "�-�-�, �� ��, ������"+ GetSexPhrase("","���") +", ����� ���������� ��������?! �� �������� �� ������� ������! � �� ����� ����� ����� � ���� ���� �� ��� ����� ������. ��������!";
				link.l1 = "��, �� ��� ��...";
				link.l1.go = "Step_9_exit";
				pchar.questTemp.State = "QuestLineBreake";	
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				AddCharacterExpToSkill(pchar, "Sailing", -300);
				AddCharacterExpToSkill(pchar, "Leadership", -300);
				AddCharacterExpToSkill(pchar, "Commerce", -300);
				AddCharacterExpToSkill(pchar, "Pistol", -300);
				//�����
				AddSimpleRumour("�������, �������, ��� ������� �� ������������. � ��� �������-���������� �������� ��� �� ����������. �-��, ������ ���� ��� ����� �������...", SPAIN, 5, 1);
			}
        break;
		case "Step_9_8":
            dialog.text = "���� ������!!! ��� �� ����� ����� ���������?! � �������, ��� �� ��������� � ���������� ��������, �� �� ����� �� ���� ����� ���������"+ GetSexPhrase("��","��") +". � ������ ��� ����� ������������ � ������� �� ��������� ��������� � ��������� ������... � ��� �����, ����� ������� ����� ������������� ������ � ������!";
            link.l1 = "��� ���������, �������� ���, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +". � ���� �� � �����"+ GetSexPhrase("","�") +" � ������� ��-�� ����������� ����� �����!";
            link.l1.go = "Step_9_10";
        break;
		case "Step_9_10":
            dialog.text = "� ���� ������� ����� ���������� �� �����. ����� ���!\n"+
				          "�������, �� ������ �������� �� ���, ��������, ����� ���-����� ��������� ��� "+ GetSexPhrase("������ �������","����� �������") +"...";
            link.l1 = "������, ��� ���������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "60";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons"); 
        break;
		case "Step_9_11":
            dialog.text = "����������� �� ��� ������ ���� � �����������?";
			if (sti(npchar.quest.money) >= 5000)
			{
				link.l1 = "��, ��� ���������, ��� � �������.";
				link.l1.go = "Step_9_12";			
			}
			else
			{
				if(sti(npchar.quest.money) > 4800)
				{
					link.l1 = "�� ������, ��� ���������. � ���� �� �� �������� " + FindRussianQtyString(sti(npchar.quest.money)) + " ������.";
					link.l1.go = "Step_9_14";	
				}
				else
				{
					link.l1 = "��, �� ������, ��� ���������... � ���� �� �� �������� " + FindRussianQtyString(sti(npchar.quest.money)) + " ������.";
					link.l1.go = "Step_9_16";				
				}
			}
        break;
		case "Step_9_12":
            dialog.text = "��� ����� ������. �� � ������ ������ ���������� �� ���������� ��������. ������� 220000 �������� ����� ��� ��������� ��������.";
            link.l1 = "� ��������"+ GetSexPhrase("��","��") +" ���, ������, �� ������ ���� ������. ���� � ��� ����� �� ���"+ GetSexPhrase("��","��") +", �� ��������� ��� �������� ��� �� ��������� �����.";
            link.l1.go = "Step_9_13";
        break;
		case "Step_9_13":
            dialog.text = "������, ����������� ������ ������. �� ���������, ������, �������� ���� ����� �� �������.";
            link.l1 = "������, ��� ���������.";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "7";
			pchar.questTemp.State = "empty";
			AddMoneyToCharacter(pchar, 220000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//�����
			AddSimpleRumour("�������, ������� �������, ���, ����������� ������� � �������, �� ������ � ������! ��� ��� ������� ���������� �� ���� �������� � ������ - ��� �� �������...", SPAIN, 5, 1);
        break;
		case "Step_9_14":
            dialog.text = "�� ��� ��, ��� ������ ���������� � ����� ��������. ������ �������������� ����� ��������� ��� �� ������� ������������ ������. ����� ���� ������� ���������� 200000 �������.\n"+
				          "�������, �� ����� ����� ����������, ��� �� � ������ ������ ���������� �� ���������� ��������.";
            link.l1 = "� ��������"+ GetSexPhrase("��","��") +" ���, ������, �� ������ ���� ������. ���� � ��� ����� �� ���"+ GetSexPhrase("��","��") +", �� ��������� ��� �������� ��� �� ��������� �����.";
            link.l1.go = "Step_9_15";
        break;
		case "Step_9_15":
            dialog.text = "������, ����������� ������ ������. �� ���������, ������, �������� ���� ����� �� �������.";
            link.l1 = "������, ��� ���������.";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "12";
			pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");            
			AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 190);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			//�����
			AddSimpleRumour("�������, ������� �������, ���, ����������� ������� � �������, �� ������ � ������! �� �������� ����� ��������, �� ��� ������! �������, ��� ������ ��� ��������!", SPAIN, 5, 1);
		break;
		case "Step_9_16":
			dialog.text = "���� �� ����� ���� " + FindRussianQtyString(5000-sti(npchar.quest.money)) + " ������?! ��� ������ ������������� � ����������� �� � ���� ����.";
            link.l1 = "������ �������-����������, �� �� ������, � ����� ��������� � �����"+ GetSexPhrase("","�") +" � ��� ��� �������� ��������. ������ �� ��������, ��������� ���� ����� ���...";
            link.l1.go = "Step_9_17";
        break;
		case "Step_9_17":
            dialog.text = "��� �� ����������! �������, ���� �� ����� ������... � �� ����� ����� ����� � ���� ���� �� ��� ����� ������. ��������!";
            link.l1 = "��, �� ��� ��...";
            link.l1.go = "Step_9_exit";
			pchar.questTemp.State = "QuestLineBreake";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			AddCharacterExpToSkill(pchar, "Pistol", -300);
			//�����
			AddSimpleRumour("�������, �������, ��� �������-���������� �������� ��� �� ����������. �-��, ������ ���� ��� ����� �������...", SPAIN, 5, 1);
		break;
		case "Step_9_exit":
			pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
            for (i=1; i<=4; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            DialogExit();
        break;
//********************** ����� �10, ������ ��������� ************************
		case "Step_10_1":
            dialog.text = "��, �����!";
            link.l1 = "������, ��������� ��� ��������, �������� ��������� ����������� ����� �����, � �����"+ GetSexPhrase("","�") +" � ��������� ���������...";
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = "������ �������� ������� ����������� ��������������� ��������. ���� �������, ������ ����� �� �����������.";
            link.l1 = "� ����� ������ ��� ��������� ��������� � ���������?";
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = "� ������� ��� ���� ��� �������� ������, ������� � ��������� ������. ����� ������� ����� �������� ������ ��������� �� ���������� ��������.";
            link.l1 = "��������� � ���������� ����������� ������?";
            link.l1.go = "Step_10_4";
        break;
		case "Step_10_4":
            dialog.text = "� ������ ���������� ���������� ������ �� ������ ������ �� ������������ ����������� ���������. � ���� ������ �� ������ ��������, �� ��������� ��������������� � ����.";
            link.l1 = "�������! �� ��� ��, � �����"+ GetSexPhrase("","�") +" ���������� � ���������� ������.";
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = "�����������! ������������� � ��������� ��� ����� �������.";
            link.l1 = "������, ��� ���������, ��� ������� � ��������� �� �������� ���� �����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp10Maracaibo_toMaracaibo";
            AddQuestRecord("Spa_Line_10_Maracaibo", "1");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("","�"));
        break;
		case "Step_10_6":
            dialog.text = "�� � �� ���������� ������������ ��� ��� ������ ������!";
            link.l1 = "��� ���������, ���� ������� ���� ������������ ������ ����. � �� ����"+ GetSexPhrase("","��") +" ������� �� ���������� �������������, ��� �������� �������� ���� ���, ���� �������� � �����...";
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = "���� ����� �� ����! ";
            link.l1 = "���, �� ��� ���...";
            link.l1.go = "Step_10_8";
        break;
		case "Step_10_8":
            dialog.text = "� ����� �� ����� ����� � ���� �������� ����. ����� ������ � ����������� �� ���� ��� �� ������ �������! ����� �����... ���, �������� � ���� ������� ��� � ��������, ��������.";
            link.l1 = "...";
            link.l1.go = "exit";
			CloseQuestHeader("Spa_Line_10_Maracaibo"); 
            DeleteAttribute(pchar, "questTemp.CurQuestNumber");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
            bWorldAlivePause   = false; // ����� �������
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Pistol", -430);
			AddCharacterExpToSkill(pchar, "Fortune", -460);
			AddCharacterExpToSkill(pchar, "Accuracy", -420);
			AddCharacterExpToSkill(pchar, "Grappling", -450);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			//�����
			AddSimpleRumour("�������, �������, ��� �������-���������� �������� ��� �� ���������� �� ��������. �-��, ������ ���� ��� ����� �������...", SPAIN, 5, 1);
        break;
		case "Step_10_9":
            dialog.text = "�����������! � � ��� �� ����������.";
            link.l1 = "���������� ���������, ������ " + Characters[GetCharacterIndex("Maracaibo_Mayor")].name + ", ����� ��������, ��� ���������� ��� �� ��� ������� ��������� ������.";
            link.l1.go = "Step_10_10";
        break;
		case "Step_10_10":
            dialog.text = "������... ��� �� ������������?";
            link.l1 = "��, ������, ��� ���������...";
            link.l1.go = "Step_10_11";
        break;
		case "Step_10_11":
            dialog.text = "�� ��� ��, �����������! ������ � ������� ��� �������� � ���������� ��� ��� ����������� ��������. � �� ���������� ������� �� ������, ��������, ��� �� ������ ��� ����� � ��������� �����.";
            link.l1 = "������, ��� ���������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "15";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            CloseQuestHeader("Spa_Line_10_Maracaibo"); 
			ChangeCharacterReputation(pchar, 5);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//�����
			AddSimpleRumour("�������, �������, ��� �� ������ �������� ���������! ��� �������������, ��� - ��������� ������, ������"+ GetSexPhrase("","���") +"!", SPAIN, 5, 1);
        break;
//********************** ����� �11, ��������� �� ������� � ��� ������ ************************
		case "Step_11_1":
            dialog.text = "����� ������! ����, �������� ������.\n"+
				          "� ������ �������������� ������������� ����� � �������� �� ��������� �������� � ���������, ������ � ������������ ������� ��� ��� �������� ��������� ������� � ���-�������. �� ������������� ������ ����� ��������, ��� ��������� �������� �������� ����� �� ������� ����� �������.\n"+
						  "�� �� ����� ��� �������� �����, ��� ��� ��� ��������� ����������� ������ �������, ����� ������ ���������� ����. �� ��� �� ����� �� ������ ��������� � ����, ��������� ���������� ����������� ������ ���� ������� �����!\n"+
						  "��� ���������� ����� ������� � ����������� ��������� ����������� ��������� ����������, ��� �� ������� �������, � ������, ��� �� ������� ��� ������. ��� ������, ����������� � ���������� ��������, �������� �� ����.\n"+
						  "�� ������ � ������������� ����� ������?";
            link.l1 = "��, ��� ���������. � �����-�� ������� ���������"+ GetSexPhrase("","�") +" � ������?";
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = "�� � ���� ����.";
            link.l1 = "�� ��� ��, ����� ������. � ���������.";
            link.l1.go = "exit";
            SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY); //������ �� � ����������. 
            SetNationRelationBoth(HOLLAND, SPAIN, RELATION_ENEMY);
            SetQuestHeader("Spa_Line_11_DestrHolland");
            AddQuestRecord("Spa_Line_11_DestrHolland", "1");
			AddQuestUserData("Spa_Line_11_DestrHolland", "sSex", GetSexPhrase("","�"));
            pchar.questTemp.State = "DestrHolland_GoOn";
			characters[GetCharacterIndex("Villemstad_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //�������������� ���� ����
			characters[GetCharacterIndex("Marigo_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //�������������� ���� ����       
		break;
		case "Step_11_3":
            dialog.text = "� ������� �������! ��������� �������� �� �����, �������, ��� �� �������� ���� ����� ������������ � ������, ��-��.\n"+
				          "����������� �� ������� ������ �� ����� ����������� ���! � ����� ��� ������� �� ��� �� ����� ����� �����. � ���� ����� ��������� ��� ��� ����.";
            link.l1 = "������, ��� ���������. ����������� ���� � ��� �������� � ��� �����.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 2);
            DeleteAttribute(pchar, "questTemp.Q11_Villemstad");
            DeleteAttribute(pchar, "questTemp.Q11_Marigo");
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            CloseQuestHeader("Spa_Line_11_DestrHolland"); 
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//�����
			AddSimpleRumour("�������� ������, �������! ������� �� ������� ���� ����������� ��������!", SPAIN, 5, 5);
        break;
//********************** ����� �12, ������ ����-�-������ ************************
		case "Step_12_1":
            dialog.text = "�� ����� ��� ��� ������� ��� ������ ������. ������ �� ���� ��� �� � ����� ���������, � � ����� ����������� ������ �������.";
            link.l1 = "�����������, ������ �������-����������. ��� �� �����?";
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = "���� ����� - ���� ����������� ����-�-�����. �� ��� ������ ������ �������� ���������� �� ����, ������ ������� �� ���� ��������. ��������� ������ ����� ��������� ���������!";
            link.l1 = "�������... � ���-�� ���������"+ GetSexPhrase("","�") +" � ������?";
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = "����� �� - ���. ������ ������� - ������ ���������, ������ ���� �� ����������� � ���� ������� ��������� ����� �� �� �� ���� ������. ������������� ��� ������� � ������ � �����������. ��� ������, ��� ������, ���� �������������.";
            link.l1 = "�������, ������ �������-����������. � ���������.";
            link.l1.go = "exit";
            SetQuestHeader("Spa_Line_12_OccupyPortPax");
            AddQuestRecord("Spa_Line_12_OccupyPortPax", "1");
			AddQuestUserData("Spa_Line_12_OccupyPortPax", "sSex", GetSexPhrase("","�"));
            pchar.questTemp.State = "OccupyPortPax_GoOn";
			characters[GetCharacterIndex("PortPax_Mayor")].dialog.captureNode = "SpaLine12Quest_PortPax"; //�������������� ���� ���� 
        break;
		case "Step_12_4":
            dialog.text = "���������! � ���������� ������ ���� ���������������� ��� �� ���� ����������� �������. ������������ ������, �������, ������ ��������� �����!";
            link.l1 = "������� ���������� � ������ ���������� - ������ �������������������, ������...";
            link.l1.go = "Step_12_5";
        break;
		case "Step_12_5":
            dialog.text = "���������, ���������� �������� �����. �� ��� ��, � ���������� ��� �� ���, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", �� ����� ����� �������� ��������� � ��������� ����. ��� ������������!";
            link.l1 = "�������, ��� ���������...";
            link.l1.go = "Step_12_6";
        break;
		case "Step_12_6":
            dialog.text = "����, �������� ������, ������������ ������ ���� ��������, ���������. ������ � ��� ��� ������� �������� � ��������� �����������. � ����� ������� �� ��, ��� ���� ����������� ������ ������ ������� ���������� ������� � ���� �����.";
            link.l1 = "������ � ���� �� �����������, ������ �������-����������. �� ��� ��������� �����������.";
            link.l1.go = "exit";
            AddTitleNextRate(sti(NPChar.nation), 4);
            DeleteAttribute(pchar, "questTemp.CurQuestNumber");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine"; 
			bWorldAlivePause   = false; // ����� �������
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			CloseQuestHeader("Spa_Line_12_OccupyPortPax"); 
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//�����
			AddSimpleRumour("�������, �������, ��� �� ������ ��������� ����-�-�����! ������� ������ ���� ������� ���?! �����������!!", SPAIN, 5, 1);
		break;
		
//********************** //����� "����� ������". ���������� ��� ��������� ************************
		case "HugoLesopilka_1":	
            dialog.text = "��� ���� �������?";
            link.l1 = "��� ����� ����� ���������. ��...";
            link.l1.go = "HugoLesopilka_2";
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber");
        break;
		
		case "HugoLesopilka_2":
            dialog.text = "�� ���������, ��� ���� ������� - �������������� ����� � �������� ������? � ������� �� ������, ����� ���� ������� ������ � ����� �����.";
            link.l1 = "�� ����������� ��������� ��� �� ������. ���������� ������ ����� ��� ������, � �����... ����������� ������� ��������, ���� ���?";
            link.l1.go = "Nakazat_1";
			link.l2 = "�� �� �� ������... � �����"+ GetSexPhrase("","�") +" ���, �� ������ ������� ������, � ��� ����� ������� ������� - ������� � ������� �������. �� ����� ���� �� ������ � ���� ��� ����� ���������� ������, ��� ��� �������� ���� ��������.";
            link.l2.go = "Na_Slujbu_1";
        break;
		
		case "Nakazat_1":
            dialog.text = "��� ������! �� ����������� ��� ������ �� �����������? ��� ������������� � �����������, "+ GetSexPhrase("������","���������") +"! ������ ������� �� �������� �� ���� �� ����!";
            link.l1 = "�������. � ��������"+ GetSexPhrase("","�") +" ������. ������ ������ �� ����������. ���� �����!";
            link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -12);
        break;
		
		case "Na_Slujbu_1":
            dialog.text = "�����... ���� �� ��� �������� - ����� ����, �� � �����. � �������� ��� � ���� ����, "+pchar.name+". � ���������� ��������� ������������� ��� ����� �������� � ��� ��� ���. �� ������ ����� ���������� ������� �� ��� ����� ��� ���������. � ������ ��������� ��� ��������� � ���� �����.";
            link.l1 = "�������, ���� ������������������. ���� �����!";
            link.l1.go = "Na_Slujbu_2";
			Log_info("�� �������� ��������� ������ ��� �����");
			GiveItem2Character(PChar, "Patent_Espa_Lesopilka");
			PlaySound("Interface\important_item.wav");
			ChangeCharacterReputation(pchar, 1);
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
			pchar.questTemp.PDM_Novaya_Rodina.IshemHugo = "IshemHugo";
        break;
		
		case "Na_Slujbu_2":
			AddQuestRecord("PDM_Novaya_Rodina", "2");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.PDM_Novaya_Rodina.Patent = "Patent";
			DialogExit();
        break;
		
		case "HugoLesopilka_Lubopitno_1":
			dialog.text = "�, �������� �������, "+ GetSexPhrase("������","���������") +" "+pchar.name+". �� ����� ������� � ������� ������. ���� ����� �������� ��� ��������� ��������. � ����� �� ������������ ����������. ��� ������� � ����� �������� �������� ����� ���������� � �������! � ������, ���� �� ���� ��������, � ������� ��� �������� ����.";
            link.l1 = "��, ���� ������������������. ���� �����!";
            link.l1.go = "HugoLesopilka_Lubopitno_2";
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			LAi_SetCitizenType(sld);
        break;
		
		case "HugoLesopilka_Lubopitno_2":
			AddQuestRecord("PDM_Novaya_Rodina", "5");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			sld = CharacterFromID("Hugo_Lesopilka")
			sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
			sld.dialog.currentnode   = "Novoe_Zadanie_1";
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Guber");
			DialogExit();
        break;
//********************** //����� "����� �� ������". ������ ������� ************************		
		case "PDM_ONV_VedmaKaznena":
            dialog.text = "�, ��, � ������� ������ �� ������� ���� ������� �� ����� �� ���� ����������� ��������, � � � ������. �� ������ ����������, "+ GetSexPhrase("������","���������") +" �������. � �� ����� ������ ��������� ��� �� ������ � ���� ����. �������, �� ��� ����� ���� ����� �. � ��������� �������� ����� - 200000 ������ � ���� ����� �������������.";
            link.l1 = "�������, ���� ������������������. ���� �����!";
            link.l1.go = "PDM_ONV_Nagrada";
			AddMoneyToCharacter(pchar, 200000);
        break;
		
		case "PDM_ONV_Nagrada":
			AddQuestRecord("PDM_Ohota_na_vedmu", "15");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena");
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddSimpleRumour("�������, �������, ��� �� ������ ������� ������ �����! ������� ��� ������?! ����������!!", SPAIN, 7, 1);
			
            DialogExit();
        break;

		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
