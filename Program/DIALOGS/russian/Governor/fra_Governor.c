// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� ���������...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";

            //******************** ����������� ������� ***************************
        	switch (pchar.questTemp.State)   // ��� ������ � ������ ������
            {
				case "DelivLettTortuga_toDOjeron": // ����� �7 ����. �������. ������ �� ����������
					link.l1 = "�����, � �����������"+ GetSexPhrase("","�") +" ��������� ��� ��������������� ������ �� �������-����������� ������� ������ ����������. �������� ��������.";
					link.l1.go = "Step_H7_1";
				break;
				case "DelivLettTortuga_WaitTwoHours":
					if (GetQuestPastTimeParam("questTemp") > 1)
					{
						link.l1 = "����� �������-����������, � ������"+ GetSexPhrase("","�") +".";
						link.l1.go = "Step_H7_3";
					}
					else
					{
						dialog.text = "�� ������ ������� ����, � �� ������ ��� - ����� ��� ����!";
						link.l1 = "��������, �����, � ���������"+ GetSexPhrase("��","���") +".";
						link.l1.go = "exit";
					}
				break;
				case "DelivLettTortuga_AfterRape": //����������� �������, ����� �7. ����� �������.
					link.l1 = "����� �������-����������, ��� ����� �!";
					link.l1.go = "Step_H7_5";
				break;
			}
		break;
		//******************** ����������� ������� ***************************
		case "work_1":  // ������ �� ����� ������ - ������� �����
            // ���� ���� ������ � ��������, �������� ����
            dialog.text = LinkRandPhrase("�� ���������� �� ������ �������! ����� ���������� ���������� � ���������� ������������ �� ��� ���������!",
                                         "� �� ���� ��������, ��� �� ����� �������� �������� ������ �������. ������� ����������� � ���������� ������ �� ���� ������������!",
                                         "� ��� ������ ������� � ���������� ����� �������������� ���������, �� �� ������ ����������.");
            link.l1 = RandPhraseSimple("��������� ����������, ����� �������-����������.", "� ��� � �������� ����������...");
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // ��� ������ � ������ ������
            {
                case "empty":   // ��� ������ �������
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("� ������ ������ � ���� ��� ��� ��� ������������� ���������. �� ������ ��������� � ���� � ���������� �����...",
                                                     "����� ���� ��������, � ����� ������ ����� � ������ ������!",
                                                     "����������� ������ ������ �� ����, ������ � ���� ��� ��� ��� �������.");
                        link.l1 = "������, ����� �������-����������.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // ������ ������� ������� �� �������
                        {
                            case "2":
                                dialog.text = "��� ����������, ����� �� ��������� ��� ������ ��� ����� ������ �� �������, �������-����������� ������ ����������. � ��� �������, ��� ���� ����� �������.";
								link.l1 = "������, ����� �������-����������, � ������ ���. ������� ���� ������.";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = "�����"+ GetSexPhrase("�","���") +", � ���� ��� ��� ��������� ������ ����������� ��������. �� ������, ������ ������� �����, ��� ��� �� ��� ����������... � ���� ������� � ���� ���� ����� �������� ��� ��������...";
								link.l1 = "�����, ������� ����� � ����...";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                dialog.text = "�����"+ GetSexPhrase("�","���") +", �� �������� ���� ����������� � �����, ������� � ������� ��� ��������� � ���������� ��������� ����.";
								link.l1 = "�������, ��� ��� �� ������� � �����?";
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = "�����"+ GetSexPhrase("�","���") +", ��� ��� ����� ��������� ����������� ��������. � ���� ���� ��������� �������� �� ����� ����� �� �����. ��������� ��, ����������, ��� ������ � ���� � ���������� � �������� �������. ������� �������� ��� � �����������.";
								link.l1 = "� ������ ��� ����������.";
                                link.l1.go = "exit";
								LAi_group_Delete("PeaceGroup");
    							pchar.questTemp.State = "Fr5AnnaHant_toAnna";
								AddQuestRecord("Fra_Line_5_KillAnnaHanters", "1");
								sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
								sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
								sld.name = "���� �������";
								sld.lastname = "�� �����";
								LAi_SetStayType(sld);
								LAi_group_MoveCharacter(sld, "PeaceGroup");
								ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "goto","goto2");
                            break;
                            case "6":
                                dialog.text = "�����"+ GetSexPhrase("�","���") +", ������ ��������� ���� ����� ��������� ���� ������, ������� ������ ��������� �� ���������. ������ �� ��������� �������� ��� ���� ������, ��-��, �� ����� �������� ��� ������� �����.";
								link.l1 = "��� ����� ���������� ����������?";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "������������, ��� �� ������, � ��� ��� ��������� �������� ��������� ���. � ���� � ��� ����, ������� �� ������ �������������.";
								link.l1 = "����� ������ ��������� � ����!";
                                link.l1.go = "Step_7_1";
                            break;
                            case "8":
                                dialog.text = "�����"+ GetSexPhrase("�","���") +", ��� ��������� ������������ ��������� ����������, ���������������, ������� � ���������� ������������� ����������� � ������������ �������� ���������� ������� ������� �������, ������� ������ ��������� �� ���������. ���� ����������� � ������ ���������.";
								link.l1 = "��������� �� �������. �� � ��� ����������� ��� �������?";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = "�����"+ GetSexPhrase("","����") +", ��� ��������� ��������� ��� ���������� ������������ ������������ �������� ������� � ������� � ���� ������������ ��� ��������� ��� �������� ������� '����� ������'. ���� ��������� ������ ����� �������� � ������� ��������� ������ ������� � ������ ������������� �����. ������ ������ - ������ ��������� ��������� ������� �� ����-�-�����.";
								link.l1 = "��, ������ ������� ����� ������� ���������� ����������...";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "���, �����"+ GetSexPhrase("","����") +", � ��� ��� ������. �� ��� ������ �������!";
								link.l1 = "� ������ ���, ������.";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "����, �����"+ GetSexPhrase("","����") +", ������� ���� �� ��� ����� ���������. �� ���� ��� ������� ��������, ������ ������� � ����������.";
								link.l1 = "������ ������, �����?";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = "�����"+ GetSexPhrase("","����") +", ������������� ����� ��������� ������������ ������� ������ �������� ������-������ �������� XIV!!!";
								link.l1 = "�����, ����� �������-����������!";
                                link.l1.go = "Step_12_1";
                            break;
						}
					}
				break;
                case "":           // ����� �1, ������ ������ �������.
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", ������ �� �� ����� �������? �� �� ����, ������ �����������, �� ������� �������� ��������� ������� ������ � ���������� �������. ������� � ���� ������, ����� �� �������� �������, ����� � ����������� ����� ��������. ������ ���� ������������ ��������� � ����� ��������� �� �������. ��� �, � ������ ��� �������.";
                    link.l1 = "� ��� ���������� ���� ����?";
                    link.l1.go = "Step_1_1";
                break;
                case "Fr1Legran_backGovernor":
                    dialog.text = "����� ������ ����� ��� ��������, ��� � ��� ��� � �������. ������, �� ����� ������ � ��� ���������. � ���, ��� �� ������ � ������ �������� � ��������� ��������.";
                    link.l1 = "������� �� �������, �����...";
                    link.l1.go = "Step_1_2";
                break;
                case "Fr1Legran_LegranKilled":
                    dialog.text = "�-�-�, ��� ��... �� ��� �������?";
                    link.l1 = "� ��������"+ GetSexPhrase("","�") +" ���� �������, ��� � �������. ����� ����, � �����"+ GetSexPhrase("","��") +" ������� ����������� � ���������, ������� �������� ��� ��������.";
                    link.l1.go = "Step_1_3";
                break;
                case "Fr1Legran_LegranIsDead":
                    dialog.text = "�-�-�, ��� ��... �� ��� �������?";
                    link.l1 = "�������� �������-����������, ��� ��������� ��� ��������, �� �� ��������� ��� ����� ������. �� � �������� �������� � �������. � ���������, ������ ����� � ���� ���...";
                    link.l1.go = "Step_1_5";
                break;
                case "Fr2Letter_SeekProblems":
                    dialog.text = "���, �������, �������������, ��� � ���?";
                    link.l1 = "���� ������ ���������� ��������, �����.";
                    link.l1.go = "Step_2_3";
                break;
                case "Fr2Letter_NiceResult":
                    dialog.text = "���, �������, �������������, ��� � ���?";
                    link.l1 = "����� � ���, ����� �'������, ��� �����"+ GetSexPhrase("","�") +" � � �������� ���������...";
                    link.l1.go = "Step_2_6";
                break;
                case "Fr3TakeAnna_BadResult":
                    dialog.text = "� ���� ���. ��� �������, "+ GetSexPhrase("�����","�����������") +"?";
                    link.l1 = "� �� ����"+ GetSexPhrase("","��") +" �������� ����� ����, � �������, ��� ��� �����...";
                    link.l1.go = "Step_3_5";
                break;
                case "Fr3TakeAnna_NiceResult":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", � ���� �� ����, ��� ��� ��� �����������!";
                    link.l1 = "��� ���� �� ������, �����...";
                    link.l1.go = "Step_3_7";
                break;
                case "Fr4SoleiRoyal_DieHard":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �������� � ���������� �������.";
                    link.l1 = "����� �������-����������, ���� �������� � �� ������"+ GetSexPhrase("","�") +" ����������� �������, ���� �� ���� ������ ��������� ������� ����� ������. � �� ����"+ GetSexPhrase("","��") +" ������������� ��, ��� �������� �������� ����� ��������...";
                    link.l1.go = "Step_4_7";
                break;
                case "Fr4SoleiRoyal_SoleiRoyalSunk":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �������� � ���������� �������.";
                    link.l1 = "����� �������-����������, ���� �������� � �� ������"+ GetSexPhrase("","�") +" ����������� �������, ���� �� ���� ������ ��������� ������� ����� ������. � �������"+ GetSexPhrase("","�") +" ���������, �� � ���������� ��� '����� ������' ��� ��������. ��� ����� ����...";
                    link.l1.go = "Step_4_9";
                break;
                case "Fr4SoleiRoyal_backTortuga":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �������� � ���������� �������.";
                    link.l1 = "��� � �������, �����, ���� � �� ��� �������. � �������"+ GetSexPhrase("","�") +" ��������� ��������� ������� ��� ������������� ���� ������ ����� ������, ����������� ������� ���� �������� � �� ���"+ GetSexPhrase("��","��") +", ������� �������� ��������� '����� ������' � ���-���.";
                    link.l1.go = "Step_4_11";
                break;
                case "Fr5AnnaHant_GoodWork":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", � ������� ������, ��� ��� ������ ���������, ������� �� �� ����� �� ���������. ��� ���� �������, � ����� �� ����� ����� ����� ������������� ���.";
                    link.l1 = "�������, ����� �������-����������...";
                    link.l1.go = "exit";
					DeleteAttribute(&locations[FindLocation("Mayak10")], "DisableEncounters"); //������� ����������
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "6";
					pchar.questTemp.Waiting_time = "7";
					CloseQuestHeader("Fra_Line_5_KillAnnaHanters");
					AddMoneyToCharacter(pchar, 5000);
                break;
                case "Fr6Olone_OloneIsDead":
                    dialog.text = "��� �������, �������? ��� ������ ������?";
                    link.l1 = "������ ����������, ������ ��� � ����� �������� �����...";
                    link.l1.go = "Step_6_3";
                break;
                case "Fr6Olone_OloneIsLive":
                    dialog.text = "��� �������, �������? ��� ������ ������?";
                    link.l1 = "��, ��� � �������, �����. �� ����� �������, �� ������ ��������� ������ � ����� �������� ����.";
                    link.l1.go = "Step_6_7";
                break;
                case "Fr6Olone_TakeMoney":
                    dialog.text = "��� �������, �������? ��� ������ ������?";
                    link.l1 = "��, �����, ������ ���������� �������� ����� � ����. ��� � �������.";
                    link.l1.go = "Step_6_9";
                break;
                case "Fr7RockBras_toSeekPlace":
                    dialog.text = "���, �������. ���������� ��� � ����������� ������ �� �������� ���� ���������.";
                    link.l1 = "���� � �� �����"+ GetSexPhrase("","�") +" ����� ���, �� � �������� ������...";
                    link.l1.go = "exit";
					link.l2 = "������, � �����"+ GetSexPhrase("","�") +" ��� �������, �� ����� ��� � �� �����"+ GetSexPhrase("","�") +". � ����"+ GetSexPhrase("��","��") +" ����������, ��� ��� ����������...";
                    link.l2.go = "Step_7_6";
                break;
                case "Fr7RockBras_RockIsDead":
                    dialog.text = "���, �������, � ���� ���. ���� �����-������ ������� � ���������?";
                    link.l1 = "������� ����, ����� �������-����������. ������, ��� �������������� - ��� �������� ����� ��� ������ �� ��������� ����������...";
                    link.l1.go = "Step_7_7";
                break;
                case "Fr7RockBras_RockIsSaved":
                    dialog.text = "����, �������, ��� � �������. ��� ��� ���������, ��� ��� �������� �������� � ���������� � ��� �� �������� ��� ������. � � ����������!";
                    link.l1 = "�����, ��� ���� ���������� ������� ����...";
                    link.l1.go = "Step_7_8";
                break;
                case "Fr7RockBras_RockIsAgony":
                    dialog.text = "���, �������, � ���� ���. ���� �����-������ ������� � ���������?";
                    link.l1 = "������� ����, ����� �������-����������. ������, ��� �������������� - ���������� �������� ���� ��������� �� ������. �� �������� ��� � ���� �� �����...";
                    link.l1.go = "Step_7_7";
                break;
                case "Fr8ThreeCorsairs_backGovernor":
                    dialog.text = "����, �����"+ GetSexPhrase("���","��") +" " + GetFullName(pchar) + ", � �������� ���������� ��� � ������� �����"+ GetSexPhrase("�","����") +"! ��������, ����� ��� ������������� ����� �����.";
                    link.l1 = "����������, ������, � �� ����� �������, ����� �� ���? ��� �����, ��� �������� �� ��� ��������...";
                    link.l1.go = "Step_8_2";
                break;
                case "Fr9GuardPP_GoodWork":
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						dialog.text = "�����"+ GetSexPhrase("�","���") +", �� �������� '����� ������'!";
						link.l1 = "� ����"+ GetSexPhrase("","��") +" ����-�-����� � ������"+ GetSexPhrase("","�") +" �� ��� ��������� ������� ��������!";
						link.l1.go = "Step_9_4";
					}
					else
					{
						dialog.text = "�����"+ GetSexPhrase("","����") +", ��� ��� �������� � ����� ������. ��� � ���� �������? ���������, "+ GetSexPhrase("���� ���","�����������") +", ������ �����������!";
						link.l1 = "������ ������� �������� ���������, ����� �������-����������...";
						link.l1.go = "Step_9_2";					
					}
                break;
                case "Fr9GuardPP_SoleiRoyalSunk":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �� �������� '����� ������'!";
                    link.l1 = "� ����"+ GetSexPhrase("","��") +" ����-�-����� � ������"+ GetSexPhrase("","�") +" �� ��� ��������� ������� ��������!";
                    link.l1.go = "Step_9_4";
                break;
                case "Fr9GuardPP_DieHard":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �� �� ������ �������� ����-�-�����! � ��� ����?!";
                    link.l1 = "����� ����������, ������� ������ ������� ������� ���������� ����! ��� �������� ���������...";
                    link.l1.go = "Step_9_6";
                break;
                case "Fr9GuardPP_Late":
                    dialog.text = "�����"+ GetSexPhrase("�","���") +", �� �� ������ �������� ����-�-�����! � ��� ����?!";
                    link.l1 = "� �� �����"+ GetSexPhrase("","�") +" �������, ����� �������-����������, ����� � �����"+ GetSexPhrase("��","��") +" � ������, �� ��� ��� ���������...";
                    link.l1.go = "Step_9_7";
                break;
                case "Fr10OccupySD_toWeWon":
					dialog.text = "��� �������, �����"+ GetSexPhrase("","����") +"? ��� ������ ��������?";
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = "� ��������"+ GetSexPhrase("","�") +" �����-�������, ������ ���� ����� ����������� �������! �� �� ��� ������ ������...";
						link.l1.go = "Step_10_4";
					}
					else
					{
						link.l1 = "� ��������"+ GetSexPhrase("","�") +" �����-�������, ������ ���� ����� ����������� �������!";
						link.l1.go = "Step_10_6";
					}
                break;
                case "Fr11OccupySC_toWeWon":
					dialog.text = "�����"+ GetSexPhrase("","����") +", � ��� ������ �������, ��������� ������� �������� �� ������� �����-��������?";
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = "�����-�������� ��������� � ��������� � ������� �������� XIV. ��� ������� �������, � ������ - � �������"+ GetSexPhrase("","�") +" '����� ������'...";
						link.l1.go = "Step_11_3";
					}
					else
					{
						link.l1 = "�����-�������� ��������� � ��������� � ������� �������� XIV.";
						link.l1.go = "Step_11_5";
					}
                break;
                case "QuestLineBreake":
                    dialog.text = "� �� ���� ���� � ������, ����������� ���� �����. ��� ������ ������ ��� �������.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;	
                case "EndOfQuestLine":
                    dialog.text = "���������� �������������� � ��������� �������, � ������������ ���� �� ���������. ����� �����������, ���� ���������� ���� �����, �����"+ GetSexPhrase("","����") +"...";
                    link.l1 = "������, ������.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
			}
		break;
        //********************** ����� �7 ���������, �������� ������ �'������� �� ���������� ************************
        case "Step_H7_1":
            dialog.text = "���������.";
            link.l1 = "�� ���, ��������� �����������...";
            link.l1.go = "Step_H7_2";
            TakeItemFromCharacter(pchar, "letter_2");
            BackItemDescribe("letter_2");
        break;
        case "Step_H7_2":
            dialog.text = "���������. ������� �� ��� ����� ��� ����, � ������ ������������ � ����������� ������� ���������. ��������, ����� �����.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ���� � ��� � ���������� ����� ��� ����, �����.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "2");
            pchar.questTemp.State = "DelivLettTortuga_WaitTwoHours";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_H7_3":
            dialog.text = "��, ������. ����, � ����������� � ����������� ������. � ���� ������������� ���� ����� ��� ����������, ����� ��������� ������ ����� � �������.";
            link.l1 = "������, �����. ������ � ���� ���������?";
            link.l1.go = "Step_H7_4";
        break;
        case "Step_H7_4":
            dialog.text = "��, �������. ����� ��� �� �������� ����. � ������� ������������� ����� ������� �������� ����������������. ��� ��� ������ ����� ���������. ���� ���-���� �� ����� ��������� ������� � ��������, �� ��� ������ �������� ���� ������������� �������� ������ �������. ������� ���������� ����������� ��������� � ���� ������ �� ������������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", �����. �������� � ����� ��� �����.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "3");
	    AddQuestUserData("Hol_Line_7_DelivLettTortuga", "sSex", GetSexPhrase("","�"));
            pchar.questTemp.State = "DelivLettTortuga_SnapMeeting";
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7");
            GiveItem2Character(pchar,"letter_1");
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", true);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition = "DelivLettTortuga_SnapMeeting";
        break;
        case "Step_H7_5":
            dialog.text = "� ����. � ������ �� ��� �����? ������, ��� � ������ �� ����������!";
            link.l1 = "�����, ���������� ���� ������ ��������. ���� ������� �� ������, � � ��������"+ GetSexPhrase("","�") +" ��� �������� ��� ��� �����!";
            link.l1.go = "Step_H7_6";
        break;
        case "Step_H7_6":
            dialog.text = "���������� ������������� � ���������� ����� � ���� ������������� ������� ���, ��� �� ����� �������� ������� � ������� ��������� ���� �����. ����� �������� ��, �������� ����� �� ������� � ������� �����!";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", �����, ������� �� ������!";
            link.l1.go = "exit";
            pchar.questTemp.State = "DelivLettTortuga_toPortMan";
        break;
        //********************** ����� �1 ����������� �������, ������ ������� ************************
        case "Step_1_1":
            dialog.text = "�� ����� �������. ����� ������� ����� ����� ������� �� ���������, ����� �� ������ ����������� ������ �������� �������� � �����. �� �� ������ �� ���� ������ � ��� ����� ���, ������� ���� ��������� �������� �� ������������� ����� ����������� � ������ ����.\n"+
				          "������������� � ������� - ��� �� ������� �������. ���� ������ � ��������� ��� � ����� �� �����, ��� �� ���������. ���� ������������ ���, �����"+ GetSexPhrase("�","���") +".";
            link.l1 = "������, �����, � ������ ��� ���, ��� �� �������.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		// ��������� ������� � ��� -->
    		pchar.questTemp.NationQuest = FRANCE;
    		// ��������� ������� � ��� <--
    		pchar.questTemp.State = "Fr1Legran_toTavern";
            AddQuestRecord("Fra_Line_1_LegranDis", "1");
            sld = GetCharacter(NPC_GenerateCharacter("Legran", "officer_9", "man", "man", 40, FRANCE, -1, false));
			FantomMakeCoolFighter(sld, 40, 90, 40, "blade28", "pistol4", 120);
			sld.name = "����";
			sld.lastname = "������";
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.SaveItemsForDead = true; // ��������� �� ����� ����
			sld.DontClearDead = true; // �� ������� ���� ����� 200�
			sld.money = 1000000;
			sld.items.jewelry5 = 30;
			sld.items.indian6 = 1;
			sld.items.jewelry14 = 12;
			sld.items.indian2 = 1;
			sld.items.indian8 = 1;
			sld.items.indian7 = 1;
			sld.items.indian12 = 1;
			sld.items.jewelry2 = 20;
			sld.greeting = "Gr_MiddPirate";
			GiveItem2Character(sld, "cirass3");
			FreeSitLocator("Tortuga_tavern", "sit3");
            LAi_SetSitType(sld);
            ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
        break;		
		case "Step_1_2":
            dialog.text = "�� ��� ��, � ������ ������ � ��� �� ����������, �� ����� �� ��������� ������� �� ���� ����� ������ - ��� ����������� � ���� ��������� ������ ������.";
            link.l1 = "������, ����� �������-����������, � ���� ������������ � ��� ����� �� �������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			AddCharacterExpToSkill(pchar, "Commerce", 90);
			AddCharacterExpToSkill(pchar, "Fencing", 80);
			AddCharacterExpToSkill(pchar, "Fortune",70);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        case "Step_1_3":
            dialog.text = "��, ��� ��� ���������, �� ��� �������� - ��� ������ ������. �� ������ ��� ����� �������� �� ���� �� ������ �������� ���, �� ������ ���, �� � ��� �� ��� � ���� �����. ��� �� ������� �� ����?";
            link.l1 = "� �� � �����, �����...";
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = "������� ��� ���... ��� ���, �����"+ GetSexPhrase("�","���") +", � �� ����� ������ ����� � ���� ����. ����� ����, ���� � �����-������ �����, ��� ��� �� ����� ������� - ��� ������ ������� �������, ��� � ���� �����.\n"+
				          "� ��� �� ����������!";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", �����...";
            link.l1.go = "exit";
            pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_1_LegranDis");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -3);
			bWorldAlivePause   = false; // ����� �������
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			//�����			
			AddSimpleRumour("�� �������, �������� " + GetMainCharacterNameGen() + " ��� �������-���������� �������� �� ���������� �� �����-�� ������ �������, ��������� � ��������... ������ � ��"+ GetSexPhrase("��","�") +" '������ �����.'", FRANCE, 5, 1);
        break;
        case "Step_1_5":
            dialog.text = "��, ��� ��� �������� �� ���� ��������� �������... ��� ����, ��� ������� ��� � �� ������� ��������� � ���������� �����, ��� ����...";
            link.l1 = "� ����"+ GetSexPhrase("","�") +" ��� ������ ����-����, �� ��� �� ��������� ������� �����.";
            link.l1.go = "Step_1_6";
        break;
		case "Step_1_6":
            dialog.text = "� ��� ������������� ���, "+ GetSexPhrase("�����","�����������") +" " + pchar.lastname + ". �� ��� ��, ��������, ��� ��� �����, ��, ��� �� �����, � ���������� ��� �� ����������. ������� ����� ��� ����������� �� ��� ����� �� ������� - ��������, ����������� ������ ��� �����������.";
            link.l1 = "������, ����� �'������, ���� ������������ � ���� ����������.";
            link.l1.go = "Step_1_7";
        break;
        case "Step_1_7":
            dialog.text = "���� ������, �����"+ GetSexPhrase("�","���") +"! ������� ������, ������� ���� � �������, ��� ��� �� �����������.";
            link.l1 = "��, �����...";
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = "� ������� �� ������ � ��, ��� �� �� �� �������. ������� ������� ��� 1200000 �����, � � �������� � ���� ��������������.";
            link.l1 = "� ������ ��� ����� - 1200000?";
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = "������ ��� � ����, ������� ����� ���� � �������."; 
			link.l1 = "� ��� �� ������ ��� ������?";
			link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = "���� �� �� ������� ��� ������ ������� ������� � ���������, � ���� � ���������� ��� ������ ������.";
			if (sti(pchar.money) >= 1200000)
			{
				link.l1 = "������, �����, ���������...";
				link.l1.go = "Step_1_11";
				AddMoneyToCharacter(pchar, -1200000);
				NextDiag.TempNode = "First time";
			}
			else
			{
				link.l1 = "���� � ���� ��� ����� �����. �� � ��������� � ������� �� ���.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_1_10";
			}
        break;

		case "Step_1_11":
            dialog.text = "�� ��� ��, �� � �������. �� ������ ������ ������ � ����, � ���� ������ ��� ������ ����� �� �������, �����"+ GetSexPhrase("�","���") +"."; 
			link.l1 = "����� ������, �������� �������-����������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�� ������, ������� " + GetFullName(pchar) + " "+ GetSexPhrase("��� �����","���� ������") +" �������-������������ ��� ������������� �������� ������� �������. � ��"+ GetSexPhrase("","�") +" � ������ ��������"+ GetSexPhrase("","�") +" ��� ���������!", FRANCE, 5, 1);
        break;
        //********************** ����� �2 �������� ������ �� ������� ************************
        case "Step_2_1":
            dialog.text = "����� ���������, �������-���������� �������, ��� ������ ���� � ���� ���������� ����������� ���������. ������� �� ��������� ������� ��� ���-������ ������, �����, �� �������� �� �������, � ����� � ��� �����.";
			link.l1 = "����� �������, � ����������, �� ����� �����"+ GetSexPhrase("","�") +" �� ��������������"+ GetSexPhrase("��� ����","�� ������") +"? ��� ����� ������� � ������ ����, ������ �� ������������.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "�� ��� ��, ����� ������. ��������, �����"+ GetSexPhrase("�","���") +".";
            link.l1 = "�� ��������, �����.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "Fr2Letter_toCuracao";
            AddQuestRecord("Fra_Line_2_DelivLetter", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ1");
            GiveItem2Character(pchar,"letter_1");
        break;	
        case "Step_2_3":
            dialog.text = "��� ������ ���������, ��� �������������?";
			link.l1 = "��, ��� ��� �������, �� ������. ���� ������� ���������� ��������� ������, ����� ���������...";
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = "� �� ��� ��� ����� ����������?";
			link.l1 = "������� �� ����. �������, �� ������� ���. �� � ����� ��� ��������� ������, �����. ��� ��� ������ ������ ��� ������������ ���.";
            link.l1.go = "Step_2_5";
        break;
        case "Step_2_5":
            dialog.text = "�-��, ������� ��� ���... �� �� �����. �� ������ ������ � ���� ��� ��� ��� ������, ��� ��� ������������ �� ��� � ���������� ����� �� �������, ��������, ���-������ �����������.";
			link.l1 = "������, ����� �������-����������.";
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Accuracy", 200);
			ChangeCharacterReputation(pchar, -1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//�����
			AddSimpleRumour("�� �������, ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" ����������� ������"+ GetSexPhrase("���","��") +" ������ �������-�����������. � ������, �������� ������� ������������ � �"+ GetSexPhrase("��","��") +" � �����������, ����� ��������...", FRANCE, 5, 1);
        break;
        case "Step_2_6":
            dialog.text = "��� ���������, �����"+ GetSexPhrase("�","���") +"?";
			link.l1 = "��, �����, ������� �� �������. ������� ���� ������� � ������ � ������ ��������, �� �� ���� ���������� ��� ����������.";
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            dialog.text = "��� ��������? �� �� ���� "+ GetSexPhrase("���� ��������","���� ��������") +"!";
			link.l1 = "������, ��� � �������"+ GetSexPhrase("�","��") +" ��������, ������������ �������� ����������� ����� ���� �������. � �����, � ����� � ���"+ GetSexPhrase("��","��") +" ��� ����� � ��������"+ GetSexPhrase("","�") +" � ����. ��� ��������� ��������� ������, ��� ��� ���?!";
            link.l1.go = "Step_2_8";
        break;
        case "Step_2_8":
            dialog.text = "��������� ������?! ��-��, ��� ������ �-�-����� �����������.\n"+
				          "��� ������, ��� �� ������ �������� ���� � �����������. � ���, ��� ������� ��� ������� "+ GetSexPhrase("������ ��������� �����������","����� ��������������� � �������� �������") +".\n"+
						  "������ � ��� ����� ����������� �� ���� - ���������. �� ����� ������-������ ����� ������� �� ��� � ����������, � ������� ��� ��� ��� ������.";
			link.l1 = "�������, ����� �������-����������. ���� ����������.";
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//�����
			AddSimpleRumour("�� �������, ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" ����������� �������"+ GetSexPhrase("��","�") +" ������ �������-�����������. � ������, �������� ������� ������������ � �"+ GetSexPhrase("��","��") +" � ����������� - �"+ GetSexPhrase("��","��") +" ����������. �� � ����� ���������, "+ GetSexPhrase("�� �����","��� ������") +" ���������� �� ��������. �'������, ������ ����, �������...", FRANCE, 5, 1);
		break;
        //********************** ����� �3 ��������� ����� ���� ************************
        case "Step_3_1":
            dialog.text = "� ��� ����� �����, ��� �� �������"+ GetSexPhrase("�� ���������","�� �����������") +", � � ����, ��� ��� ��� ����� '�����' �� ������ ����. ��������, ��� ������� ���������� ���, �� �������, ��� ������ �������... ��� ����� � ����� �����, � ��� ������, ���������� �� �� �� �� ������ ��� ��������, ��� �� "+ GetSexPhrase("������","����������� �������") +"!";
			link.l1 = "���� ������, ����� ������, ��� � ���� ������ ������, �� ����� �� ������� �������, ��� � "+ GetSexPhrase("������ � ���������","�������������") +"! � ������ ���.";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "��, ��������, � �����, ��� � �������� ��������� �� ������� ������ ��� ����� �������� ������������. ������ ������� - ��� ��� ������, ����� ������ �����, ������� ���� ������ ������... �� ���, �� ��� ������� ������� �����.";
			link.l1 = "���� ������ ������� �� ������ ����������?";
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = "���� �� �� ���. ���� ����, ������� ����� ��������� �������� ������� ������ ����� �������, �� ��������� ������ �������� ��� ������� ��������� �������... ��������� �� �� �������, � ������� ��� ��������� - ����"+ GetSexPhrase(", ��������� ��������"," ������������! ��, ��� �������, ������ ������ ����") +"!";
			link.l1 = "����� ���������, �� �������-�� ��������� �� ����. ���� � ����"+ GetSexPhrase("��","��") +" ������?";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "������, �� �������� �� ��� ����? �������! ����, � ������� � ������, - ������� ���� ���� �������� �� �����, ���������� ������. ��� �������� ���������� � ����� � ����� ������ ������� �� ������.\n"+
						  "��� ����, ����� �� ����� ������� ��� �������, � ��� ��� ��������� �������� �������� ��������� ������ �� 60 ����, � ��� ��� ����� ��������� �������� � ��������� ����� � �������� ��������� ������. � ������������ � ���, ����� �� ����� ������� ���������� ������������� ������� ����.\n"+
				          "���, �������� ��� ������, �� ���� ����� ���� ������� �� ����� ������, ��� �� - ��� ���������� �������. � �������, ����� ���� ��������� ������� - � ����� �����.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ���, �����. ���������, ����������� ����, ������ ���� ���� �������... ��� ����� ������� � ������ ���� - �� ������������.";
            link.l1.go = "exit";
            GiveNationLicence(SPAIN, 60);
			GiveItem2Character(pchar,"DOjeronRing");
    		pchar.questTemp.State = "Fr3TakeAnna_toHavana";
            AddQuestRecord("Fra_Line_3_TakeAnna", "1");
	    AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("","�"));
			LocatorReloadEnterDisable("Havana_town", "houseS1", true);
        break;
        case "Step_3_5":
            dialog.text = "������! � � ����������� �� ���� ����������������� � ��������. � ��� ���������?";
			link.l1 = "�� ������ ����������, �����. � ������ �� �����"+ GetSexPhrase("","�") +" � ��� ����������� - ���� ���������� �������, ���-�����...";
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = "�-��, ��������... �� ��� ��, ��� ���� ��� ������ ������� � ���, ������� ����� �������� �� �� � ��� �� ��������.\n"+
				          "� ����� ��� �������� �� ��� � ����������, ��������, � ���� ����� ��� ��� ����.";
			link.l1 = "������, ����� �������-����������...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//�����
			AddSimpleRumour("����� �����, ��� ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" �����-�� ����� ������ ������� �'�������, ��������� � �������� ������...", FRANCE, 5, 1);
		break;
        case "Step_3_7":
			dialog.text = "��� �� �����, ������� �� ���� �������� ��������������.\n"+
				          "� ���� ������, �� �� �������� ���� ������, ��� ������ �� �� ���������������� ��������. �������� ����� ��������� �����...";
			link.l1 = "������, ����� �������-����������. ����������� ���� �����...";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			AddMoneyToCharacter(pchar, 25000);
            sld = characterFromId("AnnaDeLeiva");
            RemovePassenger(pchar, sld);
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // ������ ���
			pchar.questTemp.AnnaIsLife = true; //�� ������� ���� �� ����� �����
			//==> ������ ���������� �� ��������� � �������.
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1 = "location";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1.location = "Havana_tavern";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition = "Fr3_AfterAnna_IKnowYou";			
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//�����
			AddSimpleRumour("����� �����, ��� ������ ������� " + GetFullName(pchar) + " �������"+ GetSexPhrase("","�") +" ������ ��������� � ������������, � �����"+ GetSexPhrase("","�") +" ��������� ���� ��������� ������ �'������� - ����� ����...", FRANCE, 5, 1);
		break;

        //********************** ����� �4  ����� ������ ************************		
		case "Step_4_1":
            dialog.text = "��, � ����, ��� �� ����"+ GetSexPhrase("�","���") +", � �� ��������"+ GetSexPhrase("","����") +" ��������� ����. �� � ��� �������: �������� ���� � ����� �����. ������� � ���������� ������ �� ���� ����� ������ � ���������� ������� ���� - '����� ������'. ��� ���������� ������������� � ������������ ����������� ������� � ����-�����, � ��� ��� ������� �����, ��� ���� ������� ��������� ������ � ���.";
			link.l1 = "����� �� �� ��������?";
            link.l1.go = "Step_4_2";
        break;
		case "Step_4_2":
            dialog.text = "�� ��� �����, �� �����. � ������ �� ������ ������ � ��������. ��� �������� ������������ ��� �� ����� �������.";
			link.l1 = "� ���� �������� - �������� ������ ������� �������? ��, ������� ���...";
            link.l1.go = "Step_4_3";
        break;
		case "Step_4_3":
            dialog.text = "������ ���������. ��� ������� ������ �����, ��� ����, � �� "+ GetSexPhrase("������� � ������ �������","������� � ������, �������") +". � ���� �� � ���� ���� ��������� ��������, ��� ������� ���������� �������� ����� �� '����� ������'. ���� ��� ������� �������� � ���������� �������� �� ����� ������ �� ����� ��������� ���� ����� ������ �������.\n"+
				          "����� ����, ��� ���������� ��������, ��� ��� ������� ��� ������������� ������� ����� ������ ��� ��������. �������� �����, ���� ��� ����� ����������, �� ������ ���������, ����� ��� ������� ����� � ���� ���������. ��� �� ��������� � �������� �� �������� ���������� ������, ��� ����� �� �������������...";
			link.l1 = "�������� �����... � ������ �� ����"+ GetSexPhrase("","���") +", �� ������ ��� �� ����� ���������!";
            link.l1.go = "Step_4_4";
        break;
		case "Step_4_4":
            dialog.text = "� ����� �����, �������. �������, ��������� ��������� �������� ������ ������� �� ��� ������?";
			link.l1 = "� ����� ����� ������� ������ � ��������? ��� �� ����������� ������...";
            link.l1.go = "Step_4_5";
        break;
		case "Step_4_5":
            dialog.text = "��� �� ������ ������ ����������� � �������� �� ���������. �� ������ ��������� � �������� �������-���������� ���-���� " + GetFullName(characterFromId("BasTer_Mayor")) + ".";
			link.l1 = "�������. �� ��� ��, � ������"+ GetSexPhrase("��","��") +" ��������� ������ ���������.";
            link.l1.go = "Step_4_6";
        break;
		case "Step_4_6":
            dialog.text = "�������. ����, '����� ������' ��������� ��� ���� ������. ����� ��� ���������� ������� � ���������� �����, �� ������� �������� '����� ������' � ��� � ����������.";
			link.l1 = "�� ������������, �����.";
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr4SoleiRoyal_toPortMan";
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "1");
        break;
		case "Step_4_7":
            dialog.text = "�������� �� ����... �� ������� '����� ������', ����� �������� ����"+ GetSexPhrase("��","�") +"?!";
			link.l1 = "��� �������� ��� ������� �����...";
            link.l1.go = "Step_4_8";
        break;
		case "Step_4_8":
            dialog.text = "��� ��� ���� - �� "+ GetSexPhrase("��������� ����","����� ���� ��������� ��������") +", �������. ����� ��� ��������� ����������, � ����� �� ����� ��� ������. ����� ����, �����-������ �� ������� ������������ �� ��� ���������������, �� �� � ��������� �����...";
			link.l1 = "������, �����, � �����"+ GetSexPhrase("","�") +".";
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // ����� �������
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ������� � ��� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_4_9":
            dialog.text = "���� ������, �� �� ������ �������� '����� ������'... ��� ����������...";
			link.l1 = "����� �������-����������, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +"...";
            link.l1.go = "Step_4_10";
        break;
		case "Step_4_10":
            dialog.text = "����� ����� ���������, ��� �� ������ ��������� ������������� ���������. �� ������ �������� ���������, � ��� �� ������ ��� �������! � ����������� � ��� � ������� ������� � ����� �� ����� ����� � ���� ����!\n"+
				          "� ������ �������� ����!";
			link.l1 = "������, �����...";
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // ����� �������
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ���������� ������� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_4_11":
            dialog.text = "��, �������������� ��������������... ��� ��, �� ������� ���������� �������, �����"+ GetSexPhrase("�","���") +". � ���������� ��� � ������� ����������� ���������� ���� � ����� ������� �������������� - 28000 �������.";
			link.l1 = "�������, ����� �������-����������...";
            link.l1.go = "Step_4_12";
        break;
		case "Step_4_12":
            dialog.text = "� ����� ��� ���� � ���� � ���������� ����� ������-������, ��������, � ���� �������� ��� ��� ����� ����.";
			link.l1 = "������, ������. ���� � ��� �������������.";
            link.l1.go = "Step_4_check";
			AddMoneyToCharacter(pchar, 28000);  
            pchar.questTemp.Waiting_time = "8";
        break;
		case "Step_4_check":
			if (CheckAttribute(pchar, "questTemp.AnnaIsLife"))
			{
				pchar.questTemp.CurQuestNumber = "5";
				DeleteAttribute(pchar, "questTemp.AnnaIsLife");
			}
			else pchar.questTemp.CurQuestNumber = "6";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//�����
			AddSimpleRumour("����� �����, ��� ��� ������������� '����� ������' �� ��� ������ �������! ��������� �������� ��� ���� ����������"+ GetSexPhrase(" - �� ���������� ����� � ��������� ����"," - �� ��������� ����� �'���") +"!", FRANCE, 5, 1);
			DialogExit();
        break;
        //********************** ����� �6. �������� ������ ����� ************************	
		case "Step_6_1":
            dialog.text = "������ ��. � ������, ��� ��� ������ �� ��� ����� ��������������� �� ������ ��������� � ����� �����. ���� �� �������� � ���������, �� ���� ��������� �� ������ ����� ������, ��� ���������� �����.";
			link.l1 = "�� ���������, �������� �������� ����������, ��� � ���� ������?";
            link.l1.go = "Step_6_2";
        break;
		case "Step_6_2":
            dialog.text = "� ���������� ���������� ������� �� ����. ������������� �������, ������� ��� ������ ��� ����� �����.";
			link.l1 = "������, ����� �������-����������. �������, ��� ����� ���������.";
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
    		pchar.questTemp.State = "Fr5Olone_toGuadeloupe";
            AddQuestRecord("Fra_Line_6_Olone", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ6");
            GiveItem2Character(pchar,"letter_1");
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1.location = "Guadeloupe";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition = "Fr6Olone_GuadeloupeBattle";
			//==> �����
            sld = GetCharacter(NPC_GenerateCharacter("Olone", "BigPirate", "man", "man", 45, FRANCE, -1, false));
            FantomMakeCoolSailor(sld, SHIP_FRIGATE, "�������� �����", CANNON_TYPE_CULVERINE_LBS32, 90, 80, 80);
			FantomMakeCoolFighter(sld, 45, 100, 90, "blade28", "pistol5", 200);
			sld.name = "�������";
			sld.lastname = "�����";
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.CompanionEnemyEnable = false; 
			sld.Abordage.Enable = false; // ������!
			sld.RebirthPhantom = true;
			sld.greeting = "Gr_EvilPirate";
			ChangeCharacterReputation(sld, -100);
            LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            ChangeCharacterAddressGroup(sld, "BasTer_houseF1", "goto", "goto5");
        break;
		case "Step_6_3":
            dialog.text = "��� ���������?";
			link.l1 = "����� �������-����������, �� � ����� ������������ ����� ������... �����, �� ����� ����� �����... � �����, ����� �����, ������...";
            link.l1.go = "Step_6_4";
        break;
		case "Step_6_4":
            dialog.text = "��� ��� ��... � ��� �� ���� �����, ��� ��������� ������� ����� ������ ������� �����?";
			link.l1 = "�����, "+ GetSexPhrase("��� ��� �������� �����","��.. ��� �") +"...";
            link.l1.go = "Step_6_5";
        break;
		case "Step_6_5":
            dialog.text = "�� ��, ��, "+ GetSexPhrase("������, ��������� ���������","��������, ��������� �����������") +"! ����� - ����� �� �����.\n"+
				          "�� ������ ��, ��� ��� ��� ������ �� ����, �� � ���������� ����� �� ����. ��� �����, ��� ������ ���� ������� �� �������� ����� ���������� ��������.";
			link.l1 = "��� �����, ����� �������-����������.";
            link.l1.go = "Step_6_6";
        break;
		case "Step_6_6":
            dialog.text = "�� ��� ��, � ��� �� ���������� �����. ���� � ���� ��� ��� ��� ����, �� �� ������ �������� �� ��� ����� �� �������...";
			link.l1 = "������, ������, ������ ��� � ��������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", 170);
			AddCharacterExpToSkill(pchar, "Sneak", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//�����
			AddSimpleRumour("����� �����, ��� �� ������������ � ����� ������� �����! �� ��, ����� � ���, ��������� �� ��������� "+ GetSexPhrase("�������","�������") +"...", FRANCE, 5, 1);
        break;
		case "Step_6_7":
            dialog.text = "�, ��� ���������. �� ���� �����, ������ ������ ������ � � ���������. �� ��� ��, ���������� ������, "+ GetSexPhrase("���� ���","�����������") +". � ������ ������� ����� ��������������.";
			link.l1 = "������� �� ������ ����� � ��� �����, ������. �� ��� ��������� ����������� - ����...";
            link.l1.go = "Step_6_8";
        break;
		case "Step_6_8":
            dialog.text = "��, �������, �� ���� ��� �����������, �������. �� �� ��������� ����������� � ��� ���������� ����� �� �������.";
			link.l1 = "������, ����� �������-����������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 6);
			AddCharacterExpToSkill(pchar, "Grappling", 220);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Defence", 280);
			AddCharacterExpToSkill(pchar, "Accuracy", 190);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//�����
			AddSimpleRumour("�� ������ ����� �����, ��� �� ���������� ������ � ������� �����. ��������� ����, ������, ������� ����������! ", FRANCE, 5, 1);
        break;
		case "Step_6_9":
            dialog.text = "��� ���������� ����� � ����� � �������?";
			link.l1 = "�� ��������� ��� ����� �� ������. � ���������, � "+ GetSexPhrase("�������� ���","��������� ����") +" ����������. ������, �������, ��� �� � ��� ���� ���������, ���� � ������� ����� ������� ��� �������.";
            link.l1.go = "Step_6_10";
        break;
		case "Step_6_10":
            dialog.text = "�� ��� ��, ����� ���������, ��� ��� ���� ���������... ��� � ������ �� ���� �����������, �����"+ GetSexPhrase("�","���") +". �� ��������� ������ � ���� ����� �� �������, �� ������ ������������.";
			link.l1 = "������, ����� �������-����������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 2);	
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Sneak", 190);
			AddCharacterExpToSkill(pchar, "Defence", 150);
			AddCharacterExpToSkill(pchar, "Accuracy", 220);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        //********************** ����� �7. ���������� �� ������ ���� ����������� ************************	
		case "Step_7_1":
            dialog.text = "� �������� � ���� ����� ��������� ���������� ��� ��������. ������� ��� ����� �� ����������, ��������� �� ���������� ������� ��������. ����������, ������ ��� ����������� ���� � ���������� ��������, ��� ������� ��������, ��� �� ��������� ���������� � ��� ������. �� ��� ���� �� ����� �������.";
			link.l1 = "������ - �� �������?! � ��� �� �����?";
            link.l1.go = "Step_7_2";
        break;
		case "Step_7_2":
            dialog.text = "������ ���� ���������� ����� ����������� �����, � � ��������, ��� �������� ��������� �� ������ ��� ������...";
			link.l1 = "... �� � ��� ������, �������, ��� � �������, ������������ �� ������ ��������� �� ������ ���� ������...";
            link.l1.go = "Step_7_3";
        break;
		case "Step_7_3":
            dialog.text = "���������� �����. ��� ��� �� ���������: ����������� ����� ��� �����������. ��� �������, ��� ���� ��������� � ��������� ������. �� ������ ���������� ���� ��� ����� ������� � �������� ��� �� ����� ����� �����. � ����, ����� �������� ��� �����, � �� ����������� ����� � ��������.";
			link.l1 = "�� ���� �� ��������...";
            link.l1.go = "Step_7_4";
        break;
		case "Step_7_4":
            dialog.text = "����� ������� ������ �� ������, �� �� ������ � ��. � � ���� ���� ��������� ��������, ��� ��� � ������������� �� �������� ����������� �� �������� ������������� ��������� ����� ����� ��������...";
			link.l1 = "������� ���������, �� ��� ��� �� ���! � ����������� ����������.";
            link.l1.go = "Step_7_5";
        break;
		case "Step_7_5":
            dialog.text = "����� ������. � ��� - � ������ ��� ���������� ����������� �������, �� ����������� �� �������� �������. ��� ����� � ����� ��� ��� ����������� ������� ��������� �������� ��������.";
			link.l1 = "�������� �������, ����� �������-����������.";
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
			GiveNationLicence(SPAIN, 20);
			SetNationRelation2MainCharacter(SPAIN, RELATION_NEUTRAL);
    		pchar.questTemp.State = "Fr7RockBras_toSeekPlace";
            AddQuestRecord("Fra_Line_7_RockBras", "1");
			SaveCurrentQuestDateParam("questTemp");
			//==> ��������� - � ����������. 
            sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "bocman", "man", "man", 30, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 90, 90, "", "", 80);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
			sld.RebirthPhantom = true;
        	sld.name 	= "���";
        	sld.lastname 	= "��������";
			LAi_LoginInCaptureTown(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetGroundSitType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison9");
        break;
		case "Step_7_6":
            dialog.text = "��, ���������� � ����� ����������, "+ GetSexPhrase("�����","�����������") +". �� �������� �� ���� ����� ����.\n"+
				          "����� ����, �����"+ GetSexPhrase("�","���") +", ��� �� �� ������ ��������� �������, ����� ����... �������, �� ��� ������ �� �����. �� ������ ����������� �� ��� � ���������� ������������, ��������, � ��� ��� �������� ������...";
			link.l1 = "������, ����� �������-����������.";
            link.l1.go = "Step_7_exit";	
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �� �����"+ GetSexPhrase("","�") +" �������� ���� ��������� �� ��������� ���������. �����, �� ��� ������� ���������...", FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "35";
        break;
		case "Step_7_7":
            dialog.text = "�-��, ��������... �� ��� ������� ������� � ��������� ���������. ����� ����.\n"+
				          "�� ��� ��, � �������, �� ������� ��� ��������� ��� ��� ��������. ������� � ��������� ��� ���� � ���� � ���������� ����� ���� ������ - � ����� ��� ��� ����� ����.";
			link.l1 = "������, ������, ���� ����������.";
            link.l1.go = "Step_7_exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 100);
			AddCharacterExpToSkill(pchar, "Defence", 100);
			AddCharacterExpToSkill(pchar, "Cannons", 100);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �� �����"+ GetSexPhrase("","�") +" �������� ���� ��������� �� ��������� ���������. �����, �� ��� ������� ���������...", FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "15";
        break;
		case "Step_7_exit":
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
			TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
            sld = characterFromId("RockBrasilian");
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // ������ ���
			DialogExit();
        break;
		case "Step_7_8":
            dialog.text = "�� ������������, �������. �������� �� ����������� ������ �������� 30 ����� �����. �������� ��������.";
			link.l1 = "�������, ����� �������-����������...";
            link.l1.go = "Step_7_9";
        break;
		case "Step_7_9":
            dialog.text = "�, ��� ������, ����� ��� ����������� � ��� ���������� ����� �� �������, �������, ��� � ��������� ����� �� ������ ��� �����.";
			link.l1 = "������, ������, ����������� ���� �������� ���.";
            link.l1.go = "Step_7_Rock";
			AddMoneyToCharacter(pchar, 30000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
            TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);	
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �������"+ GetSexPhrase("","�") +" ���� ��������� �� ��������� ���������. ��������� �����, ����� � ���, ���� ����� �������.", FRANCE, 5, 1);
        break;
		case "Step_7_Rock":
			sld = characterFromId("RockBrasilian");
			RemovePassenger(PChar, sld);
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			DialogExit();
        break;
        //********************** ����� �8. ������� � ����� ��������� ************************	
		case "Step_8_1":
            dialog.text = "���� ������ � ���, ����� ��� ����� ������ ������� � �������. ����������� ��� ����������, ���� �� �����, ���� ����� ������ ���������.";
			link.l1 = "��� �, ��� �� � ������. ������� �������, � �����������...";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr8ThreeCorsairs_toBonrepo";
            AddQuestRecord("Fra_Line_8_ThreeCorsairs", "1");
			//==> ������ �������.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= "������";
        	sld.lastname 	= "�������";
			sld.greeting = "Gr_QuestMan";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
		case "Step_8_2":
            dialog.text = "�������, �� ��� � ���� ����� ���������� ��������. ����� ��������� � �������� ���������� �� ������ �� �� ����� ������.";
			link.l1 = "��� �����, �����...";
            link.l1.go = "Step_8_3";
        break;
		case "Step_8_3":
            dialog.text = "�� ��� ��, ���� ����� ������ � ��� � ���� ���, �� � ���� ��������, ���� �� ������ ����� �� ������� �������� ���� - ��������, ��� ��� ��������� ���������� ����!";
			link.l1 = "������, ������. �, ��� "+ GetSexPhrase("����������� ��������, �����","����������� ��������, ���������") +", ���� � ������ � ��� � ���������� ����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "12";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", -100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//�����
			AddSimpleRumour("�������, ��� �������� " + GetMainCharacterNameDat() + " ��������� ���������� ����� �����"+ GetSexPhrase("�","����") +"! ��, ����...", FRANCE, 5, 1);
        break;
        //********************** ����� �9. ������ ��������� �� ����-�-����� ************************	
		case "Step_9_1":
            dialog.text = "��� ���, �����"+ GetSexPhrase("","����") +". ��� ��� ������ �� ��������� ���������� ��-����, ������, �� ���� ���������, ������� �� ����-�-�������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. � ���� ���������� � ���������� ������?";
            link.l1.go = "Step_9_11";
        break;
		case "Step_9_11":
            dialog.text = "� ��������, ��. ������, ��� ����� ������� �� ��� ��������� - '����� ������' ��������� ��� � �������� �������� �������.\n"+
				          "�� �� � ���� ������ �� ������ �������� ���� �������, ��� ����� �������� ������ ������. � �� �� ������� ������ �������� �� ����������� �������������.";
			link.l1 = "��, �� ��� ��, � ����� ��� ���� � ����, ����� ������������ '����� ������' �������� �� ���������.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr9GuardPP_toPortPax";
            AddQuestRecord("Fra_Line_9_GuardPortPax", "1");
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			sld.Ship.Name = "����� ������";
			SetBaseShipData(sld);
			ResetShipCannonsDamages(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");	
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);	
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // ������!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
			pchar.TempPerks.QuestTroopers = true; //���� ���������� �������
			SetTimerCondition("Fr9GuardPP_Late", 0, 0, 5, false);
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1.location = "Hispaniola2";
            Pchar.quest.Fr9GuardPP_Fight.win_condition = "Fr9GuardPP_Fight";
        break;
		case "Step_9_2":
            dialog.text = "�����, �����"+ GetSexPhrase("","����") +", � ��������� ��������. ����������� ������������� ������������� ������������ ����� �� ������ �������� � ���������� ������� ������� - 5 ����� �������... �������� ��������.";
			link.l1 = "����� 5 �����?! ��������, ��� ������, ��� ������!";
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = "�����"+ GetSexPhrase("","����") +", ��� ����� ������� �� ���� ��� ����������� ���������� ���. � ����� ��� ������ �������� - ����� ��������������� �� �������. ������� ����� ��� ������� ����������� �������� ��� ��������.\n"+
				          "������ � ��� ����������� �� ���� - ������������� � ��������� ������ ���������. � ������� - �� ����� �������!";
			link.l1 = "��, �� ��� ��, ���� � ��� ���"+ GetSexPhrase("��","��") +" ������� - ��� ���� �������. ���� � ��� � ���������� ����� ����, ��� ������� � ������� ���� ����, ������. �� ��������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "18";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
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
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("","��") +" ������� ����-�-����� �� ��������!", FRANCE, 5, 1);
        break;
		case "Step_9_4":
            dialog.text = "�� �� �������� '����� ������', �������, � ����� ��� ����������!";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���, ��� ���� � ���� �����...";
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = "�� ������� ������������! � �����, ������ ������ ������� ������� � ����, ��� ������� ������������ �� ����� �����, �����"+ GetSexPhrase("�","���") +". ��������.";
			link.l1 = "� ��� ����� �����, ��� � ������"+ GetSexPhrase("","�") +" ��� �������?! ��������, ������, ��� � ����"+ GetSexPhrase("��","�") +" ��� ��� ��� ������� �������...";
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // ����� �������
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ���������� ������� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_9_6":
            dialog.text = "���� ������, �� �� ������ "+ GetSexPhrase("��������� ����","��������� ��������") +"! � �� ����� ����� � ���� ������ ������. ��������, �����"+ GetSexPhrase("","����") +"...";
			link.l1 = "��������, ������, ��� ��������� ������ ������� �������...";
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // ����� �������
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ������� � ��� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_9_7":
            dialog.text = "������, ��� �� ���?! ����� ��� ��� ����!! � ����� ���, � �� ����� ����� � ���� ������ ������. ��������, �����"+ GetSexPhrase("","����") +"...";
			link.l1 = "��������, ������, ��� ��������� ������ ������� �������...";
            link.l1.go = "exit";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // ����� �������
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� �� ������ ������� ������� � ����-�-������ � ����� ��� ������� ���������. ������� ���!", FRANCE, 5, 1);
        break;
        //********************** ����� �10. ������ �����-������� ************************	
		case "Step_10_1":
            dialog.text = "������� ����� ���� ���������� ����� �� ������� ������� ����-�-������. �, ��� ��� �������, ������ ������� ����� ���������� ���������� ����� ������� ���������, ������ � ���������� �����������...";
			link.l1 = "����� �������-����������, ����� ��� �������� ����� ���������.";
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = "������, �����"+ GetSexPhrase("","����") +". ����, � ������� ��� ��������� �����-�������! ����� �������, ��� ��������� ����� ������������ ������� ����� �������, �� �� �������, � �������. ������ �������?";
			link.l1 = "�������, ������. �������, ��� ������ ������ ������ ������� ��������? � �� ���� ��������� '����� ������' � ����� ����� �� ���� ����!";
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = "��, � �������. ������ �� ���� ����� ����� - ����� ������� �����-������� �� �������� ����� ������� ��������������.";
			link.l1 = "�� ��� ��, ������, � ���� ���. ����, � ��������� � ��������, ����� ���� � �������� ���������.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr10OccupySD_toSantoDomingo";
            AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "1");
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			characters[GetCharacterIndex("SantoDomingo_Mayor")].dialog.captureNode = "FraLine10Quest_OccupySD"; //�������������� ���� ����
        break;
		case "Step_10_4":
            dialog.text = "�� �������� '����� ������'!!";
			link.l1 = "����� ���� ������, ����� �������-����������, �������-�������� ������������� ����� �� ���. ��� ����� ����...";
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = "���� ��������� ��� �� �����. ������ ������� ������� - ������� �������� ��� �������. ������� � ������ �� ���� ����� � ���� ����, ����������� ������������� ����� �� ������� ��� ������. ��������.";
			link.l1 = "��, ��� ������, ������...";
            link.l1.go = "exit";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // ����� �������
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "FencingLight", -130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -130);
			AddCharacterExpToSkill(pchar, "Fencing", -130);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ���������� ������� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_10_6":
            dialog.text = "���������, "+ GetSexPhrase("���� ���","�����������") +", ������ �����������!\n"+
				          "������ � ����, ����� ������ ��� ��� - � ��������������. � ����� ������ �� ������� �� �������������� ����� ���������� ����������� ����� - 40 ����� �������... ��� ����, �����"+ GetSexPhrase("","����") +"!";
			link.l1 = "�������, ����� �������-����������. ��� ������� �����!";
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = "� ����� ���, ��� �� ��������... �� ��� ��, ����������� ��� � �� ���� �����, ����� ��� �������� ����������� � ������� ����. ��������� � ������� ���� ������� � ������ � ���� �������� ����� �����, �����"+ GetSexPhrase("","����") +".";
			link.l1 = "������, ����� �������-����������, ���� � ���������� �����.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 40000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 330);
			AddCharacterExpToSkill(pchar, "Fortune", 360);
			AddCharacterExpToSkill(pchar, "Accuracy", 320);
			AddCharacterExpToSkill(pchar, "Grappling", 350);
			AddCharacterExpToSkill(pchar, "Defence", 350);
			//�����
			AddSimpleRumour("�������, ��� �� ��������� �����-�������! ���������� ������, �������, ������ ������������!", FRANCE, 5, 1);
        break;
        //********************** ����� �11. ������ �����-�������� ************************
		case "Step_11_1":
            dialog.text = "�����, �����"+ GetSexPhrase("�","���") +".";
			link.l1 = "�������... � ����� ����� ������ ����������� ����� ��������� �����?";
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = "�����-��������, ��� �� �����. ���� ����� ������������ ��������� �������� �� �������� ������ ������ �����. ����������� ������������� ��������, ��� ������ ������� ����� ��� ������ ����� ������...";
			link.l1 = "���������� ������"+ GetSexPhrase("��","��") +" � ����������� ��������������. � �����"+ GetSexPhrase("","�") +" � ���������� ������ ��������. ��������� ����������.";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr11OccupySC_toSantaCatalina";
            AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "1");
			characters[GetCharacterIndex("SantaCatalina_Mayor")].dialog.captureNode = "FraLine11Quest_OccupySC"; //�������������� ���� ����
        break;
		case "Step_11_3":
            dialog.text = "������, ��� ����� � ����� �����. ������ ����� ������� ������ ����������� ���� �������������� � ����������.";
			link.l1 = "������� �� ��� ��� �����?";
            link.l1.go = "Step_11_4";
        break;
		case "Step_11_4":
            dialog.text = "���� �� �� ��� ����, '����� ������' - �������� ������������ ����� �������. ���� ������ ��������������� �������� ���, ��������� �� ���� ����������� ����������. �� �� ��������� �������� �������, ������� � �������� �������� ��� � ���������� ��������������.";
			link.l1 = "�� ��� ��, ���� ������. ���� ��� �� ������� ������� ������, ���������� �� ������������ ���������. ��������, ������.";
            link.l1.go = "Step_11_2";
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // ����� �������
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //������ ����� ���������� �������
			AddCharacterExpToSkill(pchar, "Repair", -550);
			AddCharacterExpToSkill(pchar, "Pistol", -530);
			AddCharacterExpToSkill(pchar, "Fortune", -560);
			AddCharacterExpToSkill(pchar, "Accuracy", -520);
			AddCharacterExpToSkill(pchar, "Grappling", -550);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��, ��� �� ���������� ������� '����� ������'. ���, �������...", FRANCE, 5, 1);
        break;
		case "Step_11_5":
            dialog.text = "�����������! �� ��������� ��� ��������, ��� ��������� ��� ������� ���������� ���������.";
			link.l1 = "����� �������-����������, ��� ������ �������������� ��������?";
            link.l1.go = "Step_11_6";
        break;
		case "Step_11_6":
            dialog.text = "��� ������, ����������� � ����� ��������, �� ����� ����������� ���.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" �� �������� ������ � ���� ������� � ���������� ���������� ��������, �����...";
            link.l1.go = "Step_11_7";
        break;
		case "Step_11_7":
            dialog.text = "��� ����������, �����"+ GetSexPhrase("�","���") +". ������ ������ �� �������� � ����-������� ��������, �������-�������� �������! �����"+ GetSexPhrase("","����") +", ������ ������ ������ � �� �����, ����� ������� ��������� ����������� � ���� �����.";
			link.l1 = "��, �������, �� �����, ������...";
            link.l1.go = "Step_11_8";
        break;
		case "Step_11_8":
            dialog.text = "�� ��� ��, � �������� ���, ��� �� ������ �������� ���� �����. �����"+ GetSexPhrase("","����") +", � �� ���� ��� ����������� ������, ����� ��� �������� � ������� ���� ������� � ���� �����"+ GetSexPhrase("��","��") +" � ����� �������� �� ����� ������� � ������ �������� ������-������!";
			link.l1 = "����� �������-����������, � ������� ���� �������. �� �������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "10";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //������ ����� ���������� �������
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//�����
			AddSimpleRumour("����� �����, ��� �� ��������� ����� ��������. � ����� �������� �������� ���� �� ��������� ���������� � �'�������. ���, ��������� ����, ����������...", FRANCE, 5, 1);
        break;
        //********************** ����� �12. ���������� ������� ************************
		case "Step_12_1":
            dialog.text = "�� ����� ������ ����� � ��� ������. �� ���� ����, ������ �� ���������� ����������� ������� ��� �������� � ��������� ����.\n"+
				          "���-������ ������� ������� ���� ������� �������� �� ������� � �����, ���� ��� ������ �������� ������ �������� XIV!";
			link.l1 = "� ����� � ����� ���"+ GetSexPhrase("","�") +". �������, �����, � �������� ��������� �� ������ ����� �� �������������?";
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = "�� ���� ��� ������ �� ��������. �������, �� ������ ������ ���� ������ ������� �������. ���� ��������� ������ - ��������� �� ���-����, ��� �� ���������, � ����������� ��� � ��������. �� ������� ���.";
			link.l1 = "�������, �����! ����� ����� � �� �����... � �������� ����������.";
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = "� ��������� � ������� '����� ������', �� ������ ���� � ������ ������ ���������.";
			link.l1 = "������, ������.";
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr12EndWar_toBorepo";
			AddQuestRecord("Fra_Line_12_EndOfWar", "1");
			//==> ������ �������.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= "������";
        	sld.lastname 	= "�������";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
