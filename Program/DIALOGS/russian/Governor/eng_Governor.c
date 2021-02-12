// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // ������ �� ����� ������ - ������� �����
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "� ���������, � �� ���� ������������ ��� ������. �� �� ��� �������, ���� � ����� �� �������� ���� ����. �� ��������.";
                link.l1 = "��� ��� ��...";
                link.l1.go = "exit";
				break;
			}
            // ���� ���� ������ � ��������, �������� ����
            dialog.text = LinkRandPhrase("�� ���������� ����� � ������ ������� ������ ��� �����! ����� ���������� ���������� � ���������� ������������ �� ��� ���������!",
                                         "�� ��� ���, ���� �� �� ��������� ��� �������, ��� �� � ��� � ���� �������������.",
                                         "� ��� ������ ������� � ���������� �������������� ���������, � �� ������ ����������!");
            link.l1 = RandPhraseSimple("��������� ����������.", "� ��� � �������� ����������...");
            link.l1.go = "exit";
            
			switch (pchar.questTemp.State)   // ��� ������ � ������ ������
            {
                case "empty":   // ��� ������ �������
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("���� � ���� ��� ������ ��������� ��� ���. �������� �� ��� ����� �� �������.",
                                                     "�� ������, � ������� �����!",
                                                     "���� �������� � ������ ���� �� �������������, ����������� ����� ���������� ������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +".");
                        link.l1 = "������, ���.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // ������ ������� ������� �� �������
                        {
                            case "2":
                                dialog.text = "� ���� ���� ��� ��� �������.";
                                link.l1 = "� "+ GetSexPhrase("�����","������") +", ���.";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":   // ������ ������ �� ����, ������ ����� ��� ����, ����� �� ��� ����� ����� �4 ��� ������ �3.
                                dialog.text = "������� �� ��� ����� ��� ���, � ���� ��������� ���� ��� ���.";
                                link.l1 = "������, ���.";
                                link.l1.go = "exit";
                                pchar.questTemp.Waiting_time = "2";
                                SaveCurrentQuestDateParam("questTemp");
                                pchar.questTemp.CurQuestNumber = "4";
                            break;
                            case "4":
                                dialog.text = "� ���� ���� ��� ��� ���� - ���������������� ������. � ������ �����, ��� ���������� ����������� ��������� � ����� � �������� ������. ����������� �� ������� � ������������ ������� ��� ����� ������ ���������� � ������������ ���. ���� ���������� ���, ��� ���������� � ������, ������ �� �������.";
                                link.l1 = "� "+ GetSexPhrase("�����","������") +", ���.";
                                link.l1.go = "Step_4_0";
                            break;
                            case "5":
                                dialog.text = "�, ��� � ��. � ���� ���.";
                                link.l1 = "� � ����� �������.";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "������� ���������� ������� ������ ������� ������ � ���� ���������� ������ �� ����� � ���� �����.";
                                link.l1 = "��� ������ ������� �������.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "� �������� ���������� ������ ��� ��������, ��� ������������ ����������� ������������� ������� ����, ����������� �������� ��������� ���������� ���������, ������ � ������� ������������ ��� ������.";
                                link.l1 = "��... �� ����� �������, ���...";
                                link.l1.go = "Step_7_1";
                                // ==> ������� ������� ��������
                                sld = characterFromID("Morris_Willams");
                        	    sld.LifeDay = 1; // ������ ��� �� ����.����.
                        	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
                            break;
                            case "8":
                                dialog.text = "�� ����� ����� ���, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". ��� ���������� ��������� ��������� �������� � ����� ��������� ���������� �� ����, ��� �� ���������. �� �� �� ������ ������� ���������, �� ����� ��������� �� ��� ���� � ����. �������?";
                                link.l1 = "� �����, ���. � "+ GetSexPhrase("�������","��������") +" ��������� ��� ������������ ��������� �� �������.";
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = "������ �� �� ��������� ��������� ������ �� ������ ���������� ������?";
                                link.l1 = "��, � ���������� "+ GetSexPhrase("�����������","������������") +".";
                                link.l1.go = "Step_9_1";
                                link.l2 = "���, ���. � ���� ������������ �������� ��� ������ ���������� �����������. � ������������ ��� ������� � ������� �����.";
                                link.l2.go = "exit";
                            break;
                            case "10":
                                dialog.text = "������������� ������� ��������� ������ �������� �������� ������� �� ���� �������� �������� ��� ������������� ��������� �� ������� � ���� �����-�-��������. ��� ��� ������� � ������. ������ ������ ��� ������ �����, �� ���� ������, ��� �� ����� ���� �����, ����� ���, ��� ������ ��������, ��� � �������� � ��������� ����� �� ��������. �� ������ ������ ���������. � ���� ������������ ��������� ������� ���������, ��� ���, ��� � ���� ��� ������. ������, � �� ������� ��� �������!";
                                link.l1 = "������, ���. �������, ���������.";
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SpanishAttack_ShipsInShore";
                                SetQuestHeader("Eng_Line_10_SpanishAttack");
                                AddQuestRecord("Eng_Line_10_SpanishAttack", "1");
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1 = "location";
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1.location = "Jamaica";
                                Pchar.quest.SpanishAttack_Battle.win_condition = "SpanishAttack_Battle";
                                ChangeCharacterAddress(characterFromID("Henry Morgan"), "None", "");
                            break;
                            case "11":
                                dialog.text = "�� ��� ������ ������! � ���� ��� ��� ��������� ���������.";
                                link.l1 = "������ ���, ���.";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = ""+ GetSexPhrase("���� ���","" + pchar.name + "") +", � ���� ��� ��� ��������� ��������� ���������...";
                                link.l1 = "����������� ������.";
                                link.l1.go = "Step_12_1";
                            break;
                            case "13":
                                dialog.text = "����� ��� ������ ��� � ����. � �� ����� ������, ���.";
                                link.l1 = "���?";
                                link.l1.go = "Step_12_5";
                            break;
                        }
                    }
                break;

                case "":           // ����� �1 - ������������� ����������
                    dialog.text = "� ���� ���� ��� ��� ����� ������ ���������. �� ����� ������� �����, � �� ������, ����� �� ��� �������� ���, �� � ����, ������, ��� ������.";
                    link.l1 = "���� "+ GetSexPhrase("���","����") +" ��������� ���� ���������.";
                    link.l1.go = "Step_1_1";
                    link.l2 = "��������, �� � � ������ ������ ����� ������ ������.";
                    link.l2.go = "exit";
                break;
                case "Albermal_good_time":                  // ������ ����� ��������� ���������� �� ������.
                    dialog.text = "� ������������ ���� ������ ������ ���������� ���� ��� ������ ������� ������. ������ - ��� �����������, ������ ��� � ������ ����������� �� ��� ���������. ���� �� �� ��� �������� � ������������� �������� � ������, �� ��������, ��� �� ����������� ��� �������������� �� ���������...\n"+
                                  "�� �������� ��������� ������������ ������. ��������� ������� ���������� 50000. �� ��������� ��� ������ � ��� ���������������.\n"+
                                  "������������ ������� ���������� - ������ �������������� ��� ����. ���� �� ������ ���������� �������������� � �������, �� ����� �������� �� ��� ����� �� �������.";
                    link.l1 = "�������, ���. �� ������ ������������ �� ���� � ����������.";
                    link.l1.go = "exit";
    				AddMoneyToCharacter(pchar, 50000);
    				ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
    				AddCharacterExpToSkill(pchar, "Defence", 100);
    				AddTitleNextRate(sti(NPChar.nation), 1);
                    CloseQuestHeader("Eng_Line_1_Albermal");
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    TakeItemFromCharacter(pchar, "letter_Albermal");
					//�����
					AddSimpleRumour("�� �������, �������� " + GetMainCharacterNameGen() + " ��� �������-���������� ����� ������. "+ GetSexPhrase("���, �����, �����","��, �����, ������") +" ����� ����������� � ������� ��� ����������� ���� � ����������� - ���� �������, ������� ����������. �� �� ������, ��� ����� ����������?! ����� � ��� �� �������, ��� ������ ��������� ��� ��� ����� �������� ��������� ����������� ����������� ������, ����� ��� �� �� �������������...", ENGLAND, 5, 1);
                break;
                case "Albermal_late":  // ������ �� ����� �� ������ ��������� ����������.
                    dialog.text = "��� �, � ������������ ���� ������ ���������� �������� ���� � ����� ������������� �������� � ����-�����. �� ������ ��������� ���������� �����, �� �� �� ������ ��������� ������� �� ����� ���������� � ����. ���� ������� ���������� 20000. � �� �� ������, ��� ������� ���� � ������ ����.";
                    link.l1 = "���, ����� �������� �� ���������, �� ���� ��������� �������������� ������������� ����. �������, � ���� ������������ �� ��������� ������ ��������� � ����������?";
                    link.l1.go = "Step_1_4";
                break;
                case "after_talks_with_pirates":  // ����� ������ �������
                    dialog.text = "�� ���������� ���������� �������? ����� �������� ��������� �����?";
                    link.l1 = "���, � ���������, ��� �� ������� ������������ �� � ����� �� ��������� ���� �������. ����� ���� ������� ����� ��������� �������. �������, �� ������� ������� ���������� ���������� ���������, ��������.";
                    link.l1.go = "Step_2_3";
                break;
                case "Intelligence_Curacao_Sink":  // ����������� ����� � ����� �� ����� ��� ��������, ������ ������
                    dialog.text = "������������, ��� �� ������.";
                    link.l1 = "� ���������, ��� �� ������� ��������� �������, �� ������� � "+ GetSexPhrase("������ ���","������ ����") +" ����� ����������� ������. ��� �� ������� ������ ������ ���������.";
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_Boarding":  // ������ ���������, ����������� ����� ���� �� �������
                    dialog.text = "������������, ��� �� ������.";
                    link.l1 = "��� ��������, ������� ��� ������ �� ����������� ����������� �����. ��� ������ ���������� ����� ����� ������ �������� �����.";
                    link.l1.go = "Step_4_2";
                break;
                case "Intelligence_Curacao_BoardingNotFoundLetter":  // ������ ���������, ����������� ����� ���� �� �������, �� ������ �� �������
                    dialog.text = "������������, ��� �� ������.";
                    link.l1 = "� "+ GetSexPhrase("�������","��������") +" ���������� � ����������� �����-�������. ��� ������� ����� ���� ���� �� �������, �� ������� ���������� � ��� �� "+ GetSexPhrase("�����","�����") +".";
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_OutPrison":  // ������ ���������, �� ������� � ������
                    dialog.text = "������������, ��� �� ������.";
                    link.l1 = ""+ GetSexPhrase("� ���������, � ��� ������� � �������� � ������. ��� ������� ������, �� � ������ �� �����","� ���������, � ���� �������� � ��������� � ������. ��� ������� ������, �� � ������ �� ������") +".";
                    link.l1.go = "Step_4_4";
                break;
                case "Intelligence_Curacao_FightGard": // ������ ���������, �� ������ � ���� �� ������ �� � ���
                    dialog.text = "������������, ��� �� ������.";
                    link.l1 = "� ���������, � �������� ���������� ������� ���� �����������. ��� ���, � � ���� "+ GetSexPhrase("��������","���������") +" �� ������. ������ � ���� ��������� �� ������� �� ����� ���� � ����. ������ ����������� ��� ��� ��� ������ �� �������.";
                    link.l1.go = "Step_4_5";
                break;
                case "AttackFortOrange_WeWin":   // ���� ����� ����.
                    dialog.text = "�� "+ GetSexPhrase("����","���") +" � �����.";
                    link.l1 = "��� ����������� �����... �� ������� ���, ���� ����� ����������. ��� ������� ������� ����������. ������� ���������.";
                    link.l1.go = "Step_5_2";
                break;
                case "MorrisWillams_AfterFirstTalkingWithMorris": // �������� �������� ������� �������� ����� � ���� �����.
                    dialog.text = "���, ��� �������, " + GetFullName(pchar) + "?";
                    link.l1 = "���, ���� ��������� ���������, ������ ������c ������� � ����.";
                    link.l1.go = "Step_6_2";
                break;
                case "MorrisWillams_ToModifordForCoolTalking": // �� �������� ����� ��������� � ��������� � �������
                    dialog.text = "�-�-�, ��� � �� �����, " + GetFullName(pchar) + ". ������ ��� �����������.";
                    link.l1 = "���� ������! ��� ����������?";
                    link.l1.go = "Step_6_3";
                break;
                case "MorrisWillams_ArrestedToModiford": // �� �������� ����� ��������� � ����������� ������
                    dialog.text = "�-�-�, ��� � �� �����, " + GetFullName(pchar) + ". ��� ������� ��� �� ��� �� ���� ���?";
                    link.l1 = "���, ��� ����� ���������� � ����.";
                    link.l1.go = "Step_6_6";
                break;
                case "MorrisWillams_ModifordGood5000":
                    dialog.text = "�-�-�, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", �� ���, ��� ������ ��������� ���� ����� �������������� � ��� ��������� ������?";
                    link.l1 = "���, � "+ GetSexPhrase("�����","�����") +" ���������� �� ����������� ����.";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_ModifordPolitic":
                    dialog.text = "��� ������ ��� ����� �������. �������� ������ ������ ����������, ������ � ������ � ������� ��������� �������...";
                    link.l1 = "����� ����, ���.";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_SeekSpanishGoods":
                    dialog.text = "�� ���, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", �� ��� ����������� �� ������ ��������? ��� ��� ����� - �������� ��� ����, ������� �� �������. �� ������ �����, ���-�� ������ ���� �����������...";
                    link.l1 = "���, � � ������� ������� ���� ��� ������ �����. ���������� ��� ���������...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoard":
                    dialog.text = "������, �� ����� �� ������� ��������� ����� ����� ����� ���-����� ��� ����� �����?!! ���� �������, ����������� ��������...";
                    link.l1 = "��� ������, ��� ������ ���������, ���...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoardNotFoundMoney":
                    dialog.text = "������, �� ����� �� ������� ��������� ����� ����� ����� ���-�����?!! �������, � ���� ��� ��������?";
                    link.l1 = "���, ���. ������ ��������� � ������...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceSink":
                    dialog.text = "������, �� �������� ��������� ����� ����� ����� ���-�����. � ����� ����� ����� ��� ����� �����?";
                    link.l1 = "��� �����, ���...";
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_DieHard":
                    dialog.text = "��������� ����� ������� ���, ��� �� ��������� � ������ �� ��������� �������. �������, ���� ���, ������? (� ��������)";
                    link.l1 = "���, ���. "+ GetSexPhrase("��������","���������") +" ���...";
                    link.l1.go = "exit";
                break;
                case "SevenTreasures_GoOn":
                    dialog.text = "�� ����� ������?";
                    link.l1 = "��� ���, �� � ����������� ���� ������. ������ ��������...";
                    link.l1.go = "exit";
                    if (CheckCharacterItem(pchar, "jewelry5"))
                    {
                        link.l1 = "���-��� ����.";
                        link.l1.go = "Step_7_4";
                    }
                    link.l2 = "������, �������-����������, ��� ��� ������� �� ������. � ����� �� ����� �������� �� ������� � ������ ��� ��� ������.";
                    link.l2.go = "Step_7_10";
                break;
                case "ToMansfield_CatchToPardal":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, ��������� ���������� ����������� ��������� ��������. �������� ����, ������ ��������. ��������� ��������� �������, �� ���� ���������, ��� ������� ������ �������.";
                    link.l1.go = "Step_8_3";
                break;
                case "ToMansfield_NotFoundGaleon":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, �� ���� ����������� ���������� ��������. �������� ����, ������ ��������. ��������� ��������� ������� ��� ������� ������ �������. ���, � "+ GetSexPhrase("��������","���������") +" ��� ������ �� ��������, �� �� "+ GetSexPhrase("��������","���������") +" �������� ��������.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "�� ������ ���������� ��������?";
                        link.l1 = "���, ���. ��� ��� �� �������. � "+ GetSexPhrase("��������","���������") +" ��� ������ �� ��������, �� �� "+ GetSexPhrase("��������","���������") +" ��������.";
                    }
                    link.l1.go = "Step_8_5";
                break;
                case "ToMansfield_Boarding":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, �� ���� ����������� ��������� ��������. �������� ����, ������ ��������. ��������� ��������� ������� ��� ������� ������ �������. ��� ������� ���������� ���� �� ���� ���������� �������� � ����� ��� �� �������. ������ ��� �� ����, �� � ����� �������� � "+ GetSexPhrase("�����","�����") +" ������ ������� ����������� �������� ��������. ��� ���.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "�� ������ ���������� ��������?";
                        link.l1 = "����� � �������� � "+ GetSexPhrase("�����","������") +" ����� �� ������� ��������� ������, ���� �� ���, ��� ����������� � ��������� �� ����������. ������ ��� �� ����, �� � ����� �������� ���� ������� ������ �� ������� ����������� �������� ��������, ��� ���.";
                    }
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 1; // ������� ���������� ���������� ������, 1 == ���� ��������� ������
        			AddCharacterExpToSkill(pchar, "Cannons", 600);
        			AddCharacterExpToSkill(pchar, "Sailing", 750);
        			AddCharacterExpToSkill(pchar, "Defence", 550);
        			AddCharacterExpToSkill(pchar, "Accuracy", 700);
        			AddTitleNextRate(sti(NPChar.nation), 1);
                break;
                case "ToMansfield_BoardingNotFoundLetter":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, �� ���� ����������� ��������� ��������. �������� ����, ������ ��������. ��������� ��������� ������� ��� ������� ������ �������. ��� ������� ���������� ���� �� ���� ���������� �������� � ����� ��� �� �������. ������ ��� �� ����. ��-��������, ��� ���������� �� ������ �������. ���� ���� ��� ������ �������, ��� ����������.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "�� ������ ���������� ��������?";
                        link.l1 = "����� � �������� � "+ GetSexPhrase("�����","������") +" ����� �� ������� ��������� ������, ���� �� ���, ��� ����������� � ��������� �� ����������. ������ ��� �� ����. �� �������� ��� ���������� �� ������ �������. ���� ���� ��� ������ �������, ��� ����������.";
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 40);
        			AddCharacterExpToSkill(pchar, "Commerce", 50);
        			AddCharacterExpToSkill(pchar, "Defence", 20);
        			AddCharacterExpToSkill(pchar, "Leadership", 10);
        			AddTitleNextRate(sti(NPChar.nation), 0.5);
                break;
                case "ToMansfield_GaleonSink":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, �� ���� ����������� ���������� ��������. �������� ����, ������ ��������. ��������� ��������� ������� ��� ������� ������ �������. ��� ������� ���������� ���� �� ���� ���������� �������� � �������� ���. ���� ���� ��������� ��� ������� ��� ����������.";
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = "�� ������ ���������� ��������?";
                        link.l1 = "����� � �������� � "+ GetSexPhrase("�����","������") +" ����� �� ������� ��������� ������, ���� �� ���, ��� ������������ � ��������� �� ����������. ��� ������� ���������� ���� �� ���� ���������� �������� � �������� ���. ���� ���� ��� ������ �������, ��� ����������.";
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 5);
        			AddCharacterExpToSkill(pchar, "Commerce", 10);
        			AddCharacterExpToSkill(pchar, "Cannons", -50);
        			AddCharacterExpToSkill(pchar, "Accuracy", -70);
        			AddCharacterExpToSkill(pchar, "Fencing", -100);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "ToMansfield_DidNotFindBecaners":
                    dialog.text = "�� �������� ������ �� ���������?";
                    link.l1 = "���, ����� � "+ GetSexPhrase("������","�������") +" � �� ����, �� ��� ��������� �����! �� ������ ����� ����. � "+ GetSexPhrase("�������","��������") +" �����������, �� ������ �� "+ GetSexPhrase("�����","�����") +".";
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 2; // ������� ���������� ���������� ������, 2 == ������ �� � �����, ��� ���������
        			AddCharacterExpToSkill(pchar, "Cannons", 10);
        			AddCharacterExpToSkill(pchar, "Pistol", -200);
        			AddCharacterExpToSkill(pchar, "Defence", -100);
        			AddCharacterExpToSkill(pchar, "Accuracy", -210);
        			AddCharacterExpToSkill(pchar, "Fencing", -400);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "AttackSantiago_GoodWork":
                    dialog.text = "� ��� ���� � ����� ��������. ��� ��������� ������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +".";
                    link.l1 = "�������, ���. �����, ��� ����� ������� ������, ��� ���������� �������� �������� ���� ��������� � ��������� � ���� �� �����.";
                    link.l1.go = "Step_9_4";
                break;
                case "SpanishAttack_GoodWork":
                    dialog.text = "���� ������, �� ��������� ������ ���� ���! ����� ����-����� ������ ��� ������!";
                    link.l1 = "�� ��, ������� ������� ����, � ������� ������� � � ������������ �� "+ GetSexPhrase("���","�����") +"...";
                    link.l1.go = "Step_10_1";
                break;
                case "OccupyMein_GoOn":
                    dialog.text = "�� ��� �� ��������� �� ������, �� ��������. ��� ��������� ����� �� ��� ��� �� ������ ��������...";
                    link.l1 = "���, � ���� ���������. ������ �� ������ � ������� ��������� ����������. ��������� ����� ��������� �� ���� ����������.";
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas"))
                    {
                        dialog.text = "�� ��������� �������! ��� ���������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". �� ������ ��� �� ���������. ������������!";
                        link.l1 = "������, ���.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = "������ ����������� ������, � ��� ���� �������! �����������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +"! �� � ��� �� ��� ��� �� ������� ��������, ������� ����� ������ ���� ��������!";
                        link.l1 = "� ��� ������, ���.";
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas") && CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = "������ � ������� ���������! ������ ��� ��������� ����� ����������� ������!";
                        link.l1 = "��, ���. �� ������� ���.";
                        link.l1.go = "Step_11_2";
                    }
                break;
                case "ColonelLinch_ArrestModiford":
                    dialog.text = "�������������, ��� �� ��������? ��� ���������� � ����-������?";
                    link.l1 = "���, � ���������� ����������� ����-������ � "+ GetSexPhrase("��������","���������") +" ���������� ������ �����.";
                    link.l1.go = "Step_12_2";
                break;
                case "ColonelLinch_ModifordArrested":
                    dialog.text = "�� ��������� ������������ ������, �������� ��������� � ������� � ������. ������ ���������� ������������ ������������� ��� ������������ �� ����� �������-����������� ������. � ����� ����� �� ������ ��� � ���� �������� ����� �����.";
                    link.l1 = "������, ���.";
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "13";
                    pchar.questTemp.Waiting_time = "30";
                    CloseQuestHeader("Eng_Line_12_ColonelLinch");
                break;
                case "QuestLineBreake":
                    dialog.text = "� �� ���� ���� � ������, ����������� ���� �����. ��� ������ ������ ��� �������.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
                case "EndOfQuestLine":
                    dialog.text = "���, � ������� ������ ������� �������� � ��������� ����. ������� ��� ������������� ������ ������� �������� � ��������� ������.";
                    link.l1 = "� "+ GetSexPhrase("�����","������") +", ���. ��������� �� �������.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
             }
		break;

		case "Step_1_1":
			//LockQuestLine(characterFromId("Jackman")); // ����� ��������� �������
            dialog.text = "������ � ���� ������ ��� ������� �����������, ������ ����������. ��� ������ ����� ���������, � � ������ ������ ������������ ��� � ��������. �� ������� �������, � ����-������, ������� ���� ������ ����������� ������-������� ���. ��������� ������� � ����-�����, � ���������� � �����������.\n"+
                          "���������� ������������� � ������ ���������, � ���� ����� �������� ��� ����� ��������� ������� � � ��������� ������, ��� � ������ ��� �������� ������. � ������ �������� �� ����, ��� � ����������� ����� ����� ������������������ ���������� ������� ������� �����. ����� ����, ��� ����������� � �������� ���������� ��������� ������� ����� ������ ������.";
            link.l1 = "��, �������������, ����� ������������ �� ������.";
            link.l1.go = "Step_1_2";
        break;

        case "Step_1_2":
            dialog.text = "������ � ������ ������ ��� ����� ������� � �� ������������ �������� ������. ��� ������ ������� �� �����������. ��� ����� �� �����, ��� �������� ����� �� ��������. � ��� ������ ����� ����� ������������ ��������� ������� ���������� � �������.";
            link.l1 = "�������, �� �����, ���.";
            link.l1.go = "Step_1_3";
        break;

        case "Step_1_3":
            dialog.text = "�������� ��� � ������� ���� ������, � �� ������ ����� �������������. �� ������� ���������� ��������� �������. �� ������ ��������� � ���� � ���������� � ��������� ��������. �����������, ��� ������ ������ ������, � �� ������ � ����.";
            link.l1 = "� "+ GetSexPhrase("�����","������") +" ���, ���.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
			// ��������� ������� � ��� -->
			pchar.questTemp.NationQuest = ENGLAND;
			// ��������� ������� � ��� <--
            pchar.questTemp.State = "to_Albermal";               // ���������� ��������� ������ ��� ������
            sld = GetCharacter(NPC_GenerateCharacter("Albermal", "Albermal", "man", "man", 10, ENGLAND, -1, false));
        	sld.name 	= "������";
        	sld.lastname = "����������";
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_QuestMan";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Albermal")], "PortRoyal_RoomTownhall", "goto", "goto3");
            AddQuestRecord("Eng_Line_1_Albermal", "1");
        break;
            
        case "Step_1_4":
            dialog.text = "�����, ��. �� ������ ������ ����� ��������� � ���������� ���� �������. �� - ���������� �����. �������� ������ ������� �����!";
            link.l1 = "�� �����, ���. �� ������ ������ ������������ �� ��, ��� � ���� ����� "+ GetSexPhrase("������������","�������������") +".";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			pchar.questTemp.Waiting_time = 10;
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            CloseQuestHeader("Eng_Line_1_Albermal");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            TakeItemFromCharacter(pchar, "letter_Albermal");
			AddCharacterExpToSkill(pchar, "Leadership", -70);
			//�����			
			AddSimpleRumour("�� ������, ������� " + GetFullName(pchar) + " "+ GetSexPhrase("�����","������") +" ��������� ����� ������� ������� ���������. "+ GetSexPhrase("���","��") +" ����� ���� ��������� � ���������� ����� ��� ������� ����������... �� �� ������, ��� ����� ����������?! ����� � ��� �� �������, ��� ������ ��������� ��� ��� ����� �������� ��������� ����������� ����������� ������... ������ ������� �� ������� "+ GetSexPhrase("������","�������") +".", ENGLAND, 5, 1);
        break;

        case "Step_2_1":
            dialog.text = "� ������ ���� �������� ����� � ����������. �����-��������� ���� ������� � ������� ���������, ��, � ����������� ���������, ��� ����������. ������, �� ������� ������������� ������, � ������ ������������ ��������� �� ����������� ������� �������.\n"+
                          "������, � ���� ������������ ��� ������ ���, ��������� ���������� � ����� ���������, ��� ����������. � �������� ��� ��������� ���������� �������. �� ����, ��� ����� ������� ������� ����������������� ��������� ���� � ���� ����� - ������� ������ � ���������� ��������� ��� ������! ���...";
            link.l1 = "� ��� ����������� ��� �������?";
            link.l1.go = "Step_2_2";
        break;

        case "Step_2_2":
            dialog.text = "��� ����������, ����� �� ����� ������� ��������� � ��������� ���������� �� ����, ��� �� ���������, ����� �������, ������������ � ������ ������ � ����-������, �������� � ��������� ��������� �� ��������, � ����� ������� �� ������� ��������. �� ������ �������� �������� ���� ������� ���������� ��������� �� �������, ������� ��������� ��������. ���������� ��� ����� �������, � ����������� �� ���.";
            link.l1 = "��������� ����������, ���.";
            link.l1.go = "Step_2_21";
        break;
        
        case "Step_2_21":
            dialog.text = "� �������� � �� ����� ���������� � �������. ���� � ���, ��� ��� ��� �� ������� ������������ �� ���� ��������� ��������. ��� ������ ���� �� �������. ��� �������� ���������� � ��� ����� ����������, ����������� ��� ����-�������.";
            link.l1 = "� "+ GetSexPhrase("�����","������") +", ���. ������� �� ��������������. �������, ���������, ��� � ����.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "go_talks_with_pirates";          // ���������� ��������� ������ ��� ������
            AddQuestRecord("Eng_Line_2_Talking", "1");
            // ==>  �������� ������� �� ������� � ���� ���� ������� � �������
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "EngLine_quests");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  ������� � �������� ����� ������� � ��������� � ���� ���� ������� � �������
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name 	= "����";
        	sld.lastname = "������";
            sld.Dialog.Filename = "Quest\JohnMorris.c";
            FantomMakeCoolSailor(sld, SHIP_GALEON_H, "������", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol3", 150);
			sld.greeting = "Gr_HeadPirates";
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //�� ������ ������� ����� ������.  
           	LAi_SetHuberType(sld);
        	LAi_SetLoginTime(sld, 0.0, 24.0);
        	LAi_SetHP(sld, 180.0, 180.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  ���� ���� ������� � ������� ����� �������
            QuestSetCurrentNode("John Morris", "EngLine_quests");
            // ==>  ���� ���� ������� � ������� ��������
            QuestSetCurrentNode("Jackman", "EngLine_quests");
            // ==>  ���� ���� ������� � ������� ����������
            QuestSetCurrentNode("Edward Mansfield", "EngLine_quests");
            // ==>  ��������� ������� ��������� ��������, � ����� ������ == 4
            pchar.questTemp.Count = "0";
        break;

        case "Step_2_3":
            dialog.text = "��� �� ��������, ���-���� ����� �������� � ����������?";
            link.l1 = "������ �������, �� �� �����, ���. ���� �������� �� ��������� �����.";
            link.l1.go = "Step_2_4";
        break;

        case "Step_2_4":
            if (GetQuestPastDayParam("questTemp") < 35)
            {
                dialog.text = "��, �������. ��� �, �������� �� ������������� ��������� ������, � ������� ����� �������������� � �����������������. ��� ���������� 15 000 ��������������. �������, ������ � ���� ������������ ������ ��������?";
                link.l1 = "�������, ���. ���� "+ GetSexPhrase("���","����") +" ������ ���.";
                AddMoneyToCharacter(pchar, 15000);
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Repair", 150);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddTitleNextRate(sti(NPChar.nation), 2);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            }
            else
            {
                dialog.text = "� ������ �����������, ������ ����������� ������������� �� ����� ��������. ��� �����, � ���� �� �� ���� ������������ ���������� ��� ���������� ������� �������. �� ��������� " +
                                GetQuestPastDayParam("questTemp") + " ����! ������ ����� ���������������, �� ���� ������.";
                link.l1 = "��� �, ��� ������.";;
                AddMoneyToCharacter(pchar, 800);
				ChangeCharacterReputation(pchar, 1);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
            }
            link.l1.go = "exit";
			//�����
			AddSimpleRumour("�� ������, ������� " + GetFullName(pchar) + " "+ GetSexPhrase("���������","����������") +" �� ���������� � ��������� - "+ GetSexPhrase("�������","��������") +" �� ����� ���������� ���� �� ����� � �����, ���� � ������� "+ GetSexPhrase("�����������","������������") +"...", ENGLAND, 5, 1);
            DeleteAttribute(pchar, "questTemp.Count");
            pchar.questTemp.State = "empty";
            AddQuestRecord("Eng_Line_2_Talking", "6");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("","�"));
            CloseQuestHeader("Eng_Line_2_Talking");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "70";    // ����� �������� ��� ����� �4 ����� 70 ����, ���� ���� �� �� ����� � �������
            // ==> ������� - � ���������� �� ������
            LAi_SetHuberType(characterFromID("Henry Morgan"));
            QuestSetCurrentNode("Henry Morgan", "hot_business");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
        break;

        case "Step_4_0":
            dialog.text = "��� ����, ����� ��������� ���������� ���������, � ��� ��� �������� ����������� ����-������� �������� ������ �� 20 ����, ������� �������� ��� �������� ����� � �����. ����������� ����������.";
            link.l1 = "������, ���.";
            link.l1.go = "exit";
			GiveNationLicence(HOLLAND, 20);
			pchar.questTemp.State = "Intelligence_Curacao_tavern";
			SetQuestHeader("Eng_Line_4_Intelligence_Curacao");
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "1");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("�","��"));
			SaveCurrentQuestDateParam("questTemp");
		break; 

        case "Step_4_1":
            dialog.text = "��� ����� �����, � � ��� �����������. �� ������ ��������� ����� �����, ����� ��� ������� ���-���� �������� ������ ����������.";
            link.l1 = "�������, ���. ��������, ��� �� "+ GetSexPhrase("����","������") +" ������ ���.";
            link.l1.go = "exit";
			TakeNationLicence(HOLLAND);
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    //������ ����� ����� ��������� �����, �.�. �������� ����� �������� ���� ��� ������� ��
			AddCharacterExpToSkill(pchar, "Sailing", -140);
			AddCharacterExpToSkill(pchar, "Sneak", -180);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//�����
			AddSimpleRumour("�������, ��� �� �� ������ �������� �������� �� �������. ��, ���� ��...", ENGLAND, 5, 1);
        break;

        case "Step_4_2":
            dialog.text = "�� ������ ��������� ��� ��������?! ���������, � � ��� �� ������.\n"+
                          "������, ��������� ������ � ����� ������... � ����� ��� ��������� � ���� ��������� �����, � ������ ��������. �� ������� ����������� ������� ��� ���������� �������������� � ������� 100 000.";
            link.l1 = "���, ��� �������� ��������� ���������� � �����������. ����� ������� ���������� ��� ��� ��� �����. ���� ��������������� �� ����� ���� ������������� ��� �������.";
            link.l1.go = "Step_4_3";
        break;

        case "Step_4_3":
            dialog.text = "�� ��� �, ����� ��� ������� 110 000, � �����������. ������ �������� ���� �� �����. ����� ��� ��������� �� ��� ����� ���� ����.";
            link.l1 = "�������� ��� �������, ���. �� ������� ��������� �����.";
            link.l1.go = "exit";
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "10");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","�"));
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "2";
            AddMoneyToCharacter(pchar, 110000);
			AddCharacterExpToSkill(pchar, "Sailing", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 170);
			AddCharacterExpToSkill(pchar, "Grappling", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
			TakeNationLicence(HOLLAND);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�������, ��� �� �������� � ���������� � ������ ��������� ��� ����������� �������. �������, ��� ������ �� ����� ����� ������������ � ������������� �����...",ENGLAND, 5, 1);
        break;

        case "Step_4_4":
            dialog.text = "��, ��� �� �������� � ����������� ������, ���� ������� ����. ��� ����� ����������, � � ��� �� ���. � �����������. �� ������ ��������� ����� �����, ����� ��� ������� ���-���� �������� ������ ����������.";
            link.l1 = "�������, ���. ��������, ��� �� "+ GetSexPhrase("����","������") +" ������ ���.";
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    // ������ ����� ����� ��������� �����, �.�. �������� ����� �������� ���� ��� ������� ��
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Leadership", -150);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//�����
			AddSimpleRumour("�������, ��� �� ���������� �������� � ����������� ������. �� � ��� ���, ����� ����?", ENGLAND, 5, 1);
        break;

        case "Step_4_5":
            dialog.text = "�� �������� � ������� ������� ���� ��� ����, �� ��� ��� ��������� ��������, �� ���������� �� ������.\n"+
                          "��� ����� ����� �������� ������ ��� ���������� ����� ������ ����� � ����� � ������ ��, ��������, �� ������ ��� �����.";
            link.l1 = "�������, ���. ��������, ��� �� "+ GetSexPhrase("����","������") +" ������ ���.";
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
			TakeNationLicence(HOLLAND);
            pchar.questTemp.Waiting_time = "30";    // ������ ����� ����� ��������� �����, �.�. �������� ����� �������� ���� ��� ������� ��
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Fencing", -300);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//�����
			AddSimpleRumour("�������, �� �������� � ����������� ������� ���������...", ENGLAND, 5, 1);
        break;
        
        case "Step_5_1":
            dialog.text = "��� �, ������ �� ����� ���������� � ���, ��� ��������� ������ �������� �������� ���� ��������� �� ������ - ���� �����. � ��������, ��, ��� ��� ���������� �� ������ ����� ������� - ��� ���� �������� �� ����������, �� ������ ���� �� �������� �������� �����.\n"+
                          "������ ��� ���� �������� ����������� ��������� �� ���������� ����������. � ������� ��� ���.\n"+
                          "���� ����������� ���� � ����� ����� - ���. ����������.";
            link.l1 = "����� ������, ���.";
            link.l1.go = "exit";
         	pchar.GenQuestBox.Trinidad_Cave = true;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry3 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry4 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry5 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry7 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry8 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry10 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry14 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry17 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.cirass3 = 1;
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			pchar.questTemp.State = "AttackFortOrange_GoToFort";
            SetQuestHeader("Eng_Line_5_AttackFortOrange");
            AddQuestRecord("Eng_Line_5_AttackFortOrange", "1");
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], false);
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1.location = "FortOrange_ExitTown";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition = "AttackFortOrange_GoToFort";
        break;

        case "Step_5_2":
            dialog.text = "��-�-�, ����� �� � ������ ���� ����� ����� ����� ������... ���� ��� ��� ���� ����� - ������ ����� �� �����!\n"+
                          "� �������� ������ �������� �������, �� �������� ���� ������� �������� �����... ����� ������!\n"+
                          "������� ������ ��� � ���� ����, "+ GetSexPhrase("��� ����","" + pchar.name + "") +".";
            link.l1 = "���������, ���, �� ������ ������ ���� ������������... � - �����, � ������ ���� ������ ��������� �������� �����. � ������ ��������� ����������� - ����...";
            link.l1.go = "Step_5_3";
        break;

        case "Step_5_3":
            dialog.text = ""+ GetSexPhrase("��� �, �������... �� ����� ������, ���-�� ������ ������ � ������������ ������ ���������... ��-��","��� �, �������") +".\n"+
                          ""+ GetSexPhrase("���� ���, � �������� ����� ��� �������� ����� ������, � ����� �� �������� ���������, ��� �������... ����������� ������� ��������� �� ����","" + pchar.name + ", � �������� ����� ��� ������ �������� �����") +".\n"+
                          "��, �� ���� �����������. �� �������...";
            link.l1 = "�� ��������, ���.";
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            CloseQuestHeader("Eng_Line_5_AttackFortOrange");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "30"; // �� ���� ������ ������ ���������� ��������� ������� ����� ����� �������. ����� ����������� ������ ��� � �����.
            // ==> ������� �������������� ����� ����� ���������� �����.
            SetLocationCapturedState("FortOrange_town", false);
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], true);
			//--> ����� � ������� �������
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- ����� � �������
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_patch";
			AddCharacterExpToSkill(pchar, "Pistol", 250);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Repair", 350);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("��, ��� �� �������� � ����� ����� - ���, ������ ��, ����������... ���������� ���������...", ENGLAND, 5, 1);
        break;
        
        case "Step_6_1":
            dialog.text = "��� �, ��� ������. ��� ���, �� ���� ����� �������� ������ �� ��������, � ��� ����� ���� �������� ������, ������� � ������.\n"+
                          "��� ����� ������� ������, ����� ������� ��� ���� ����� � ���� �����. ��������� ��� ����� ��� ���������� �� ������� ����� � ���������� �������.\n"+
                          "��, � � ����, ����� �� ������� ��� �������� ��� ����������.";
            link.l1 = "��� ������ �����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_GoToMorrisBegin";
            SetQuestHeader("Eng_Line_6_MorrisWillams");
            AddQuestRecord("Eng_Line_6_MorrisWillams", "1");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = "Jamaica";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_ShipToPort";
        break;

        case "Step_6_2":
            dialog.text = "��� ��� ��������. ��� ��� 5000 �� �����.";
            link.l1 = "��� �� ��������� ��� �������� �����, �� �� ����� �� ��������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordGood5000";
            AddMoneyToCharacter(pchar, 5000);
            AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "3");
            group_DeleteGroup("Willams_Group");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = Pchar.location.from_sea;
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_MeetWithManFromWillams";
        break;

        case "Step_6_3":
            dialog.text = "��� �� ������? � ��� ����?";
            link.l1 = "�� ������������ ���� ������ ������� ��������! � ��� "+ GetSexPhrase("���������","����������") +" � ���� ����� �!";
            link.l1.go = "Step_6_4";
        break;

        case "Step_6_4":
            dialog.text = "�� ��, � � ��������� ��� � ���� �����. �� ��������� ���� ���������, �� �����. ��� �������� �����, �� �� ��������� ���������� ������������.";
            link.l1 = "� ����� ���� �� ����! �����?!!";
            link.l1.go = "Step_6_5";
        break;

        case "Step_6_5":
            dialog.text = "��������� ����� ������� � �������� ������������. ��� ���� ������ ����.\n"+
                          ""+ GetSexPhrase("���� ���","" + pchar.name + "") +", �� ������ � ��������, �� ������ �� ������� ��������. �� ��������.";
            link.l1 = "� ���� ������ ��� ����... ��� �, �� ��������, ���.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordPolitic";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "5");
            QuestSetCurrentNode("Morris_Willams", "First time");
			//�����
			AddSimpleRumour("�������, ������� ��� �� ��� ���������� ������� ��������?! ����� �� �����, ��� �� �������� �� �����...", ENGLAND, 5, 1);
        break;

        case "Step_6_6":
            dialog.text = "��� ���������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +"?";
            link.l1 = "������ ������� ������� � ������, ������ �� ���� ����. � ������ ������ ����������� ���������� ���.";
            link.l1.go = "Step_6_7";
        break;

        case "Step_6_7":
            dialog.text = "��� �, � ����, ��� �� ������� �����������. ��� ����� �� ���������� ������������ ������� �������� ������ ��� �������, �� � �������� ��� �������. ����� ���� �����.\n"+
                          "������� ��� ���������� � �������� ����������, ������ ���������� �������� ����� ��� ������ ��������� � ������.";
            link.l1 = "������� �� �����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedToUsurer";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "17");
        break;
        
        case "Step_7_1":
            dialog.text = "���� � ���, ��� ���������� ������� ��������� �������� � �������� �������, ����������� � ��������. ��� ������ ������� ������ �� ������ � ���������� ����������� ����������� �����.\n"+
                          "�������, ��� �� ����� ���������, ������� ������ ������ ������ ����� �� ��������� ���������������� ������� �� ������� ������������ �����, � ������� ������ �������� ����������!!!\n"+
                          "������� ������ ���� ������ ����� �� �������� ������ �� ��������, ���� �������� �������� � �������� � ��� ������������� �����, ���� ������� ����������� ����� ����� ����������� ����������� �� �������.\n"+
                          "�� ����, �������� ���� ��� ����: ������ �� �������� ������������, � �� �� �������� � ����� ������!\n"+
                          "����� ������ ������ ������� ����� ���������� � ������� ��������� �������� ��� ����� ��������. ���� �� ��������� ������ ��������� � ����������� � ���������: ��� ����� ��������, ��� ����� ���� ��������� �������� �������� ������ � ������� �� ����� �������.\n"+
                          "��� ����� �������� ��������� ����� �������� ������:\n"+
                          "1. ����� ������ - ���� ���������\n"+
                          "2. ������ ����� - �� ������� ��������\n"+
                          "3. ������� ��� - �� ������� �����\n"+
                          "4. ������� ����� - �� ������� ��������\n"+
                          "5. ������ ��������� - �� ������� ������\n"+
                          "6. ������� ����� - �� ����\n"+
                          "7. ������� ��������� - �� ���������\n"+
                          "������� ��� ��� ����� � ��������� �� ���. �����, ������ ����� ��������, ��� ������ ������ ��������, ��� � ����� ���������...";
            link.l1 = "�������. �������, � ����� ������ ������ ������, ���.";
            link.l1.go = "Step_7_3";
            link.l2 = "���, ��� �� ����� ������� ���� ���������. ����� �������� - ��� �� ������ ����. � ����� �� ��� ���...";
            link.l2.go = "Step_7_2";
        break;

        case "Step_7_2":
            dialog.text = "� ������ �������� ����� ����������...";
            link.l1 = "���, � �������, �� ����� �� ���� ������.";
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 3);
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "8";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "35";
            AddCharacterExpToSkill(pchar, "Leadership", -500);
            AddCharacterExpToSkill(pchar, "Cannons", -300);
            AddCharacterExpToSkill(pchar, "Sneak", -350);
			//�����
			AddSimpleRumour("�� ������, ������� " + GetFullName(pchar) + " "+ GetSexPhrase("���������","����������") +" ��������� ��������� ��������� �� ������ ��������� �������...", ENGLAND, 5, 1);
        break;

        case "Step_7_3":
            dialog.text = "�� ���� ������� ������ �� ���� ���� ������ 2100 �������! ��������� ��� ��� ���...";
            link.l1 = "������, ���. ��������� ����������.";
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, -4);
            pchar.questTemp.State = "SevenTreasures_GoOn";
            pchar.questTemp.GoldQtyGaveModiford = "0"; // ���-�� ������� ���������
            pchar.questTemp.GoldQtyForSeek = "2100"; // ���-��, ������� ��� ����� ���������
            SaveCurrentQuestDateParam("questTemp");
            SetQuestHeader("Eng_Line_7_SevenTresures");
            AddQuestRecord("Eng_Line_7_SevenTresures", "1");
            // ==> ���� ������ ������� � ������ ���� ���������.
         	pchar.GenQuestBox.Cartahena_Cave = true;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry5 = 300;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry1 = 110;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.statue1 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.pistol2 = 1;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.icollection = 1;
            // ==> ���� ������� ������ �� ���������.
         	pchar.GenQuestBox.Trinidad_Grot = true;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry5 = 450;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.blade5 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potion2 = 10;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potionwine = 3;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry2 = 90;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian6 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian11 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian15 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian12 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.chest = 1;
            // ==> ���� �������� ��� � ����� �� ������.
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry3 = 85;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade10 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
            // ==> ���� �������� ������ �� ���������.
         	pchar.GenQuestBox.Dominica_Grot = true;
            pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 150;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry4 = 75;
            pchar.GenQuestBox.Dominica_Grot.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potion1 = 5;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potionrum = 2;
			pchar.GenQuestBox.Dominica_Grot.box1.items.chest = 1;
            // ==> ���� ������ ���������� �� �������.
         	pchar.GenQuestBox.Caiman_Grot = true;
            pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry17 = 250;
            pchar.GenQuestBox.Caiman_Grot.box1.items.blade2 = 1;
            pchar.GenQuestBox.Caiman_Grot.box1.items.potion5 = 10;
            pchar.GenQuestBox.Caiman_Grot.box1.items.indian18 = 1;
            // ==> ���� �������� ����� �� ����.
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry17 = 150;
            pchar.GenQuestBox.Cuba_Grot.box1.items.topor2 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.chest = 3;
            // ==> ���� �������� ���������� � ���������� ����� ����� � �������.
         	pchar.GenQuestBox.Guadeloupe_Cave = true;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry17= 100;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.mineral8 = 1;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry2 = 50;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.mineral8 = 1;
        break;

        case "Step_7_4":
            dialog.text = "��-�-��, ������� ���������...";
            link.l1 = "����, ���, ������ � ���� ������ " + pchar.items.jewelry5 + " �������. � "+ GetSexPhrase("�����","������") +" ����� ��� ���.";
            link.l1.go = "Step_7_5";
            link.l2 = "���, � ���� � ����� " + pchar.items.jewelry5 + " ������� ������. �� ��� ������ � "+ GetSexPhrase("�����","������") +" �� � ���������� ������������ ���� ������. ��� ��� ��� ������ � �������� ����.";
            link.l2.go = "Step_7_7";
        break;

        case "Step_7_5":
            if ((sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5)) <= 2100)
            {
                pchar.questTemp.GoldQtyGaveModiford = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5);
                pchar.questTemp.GoldQtyForSeek = 2100 - sti(pchar.questTemp.GoldQtyGaveModiford);
                if (pchar.questTemp.GoldQtyForSeek != "0")
                {
                    dialog.text = "����� ������, " + pchar.items.jewelry5 + " ������� ������ � �������� � ���. ����� �� ����� " + pchar.questTemp.GoldQtyGaveModiford + " ������� ������. ��������������, ��� �������� ��������� � ��������� ��� ��� " + pchar.questTemp.GoldQtyForSeek + " �������.";
                    link.l1 = "� "+ GetSexPhrase("�����","������") +", ���. ������ ����� ����������.";
                    link.l1.go = "exit";
                    AddQuestRecord("Eng_Line_7_SevenTresures", "3");
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyGaveModiford", pchar.questTemp.GoldQtyGaveModiford);
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyForSeek", pchar.questTemp.GoldQtyForSeek);
                }
                else
                {
                    dialog.text = "�� ��������� ������������ ������. ���� ���������� � ����� ���, ��� � � �����������, 2100 ������� ������. ���� 10 ��������� ���������� 70 �����.";
                    link.l1 = "�������, ���.";
                    link.l1.go = "Step_7_6";
                }
                DeleteAttribute(pchar, "items.jewelry5");
            }
            else
            {
                pchar.questTemp.GoldQtyForSeek = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5) - 2100);
                dialog.text = "���, �� ����� ������ ������, ��� � �����������! � ��� ������ " + pchar.items.jewelry5 + " ������� ������. �� ����� �� ����� " + pchar.questTemp.GoldQtyGaveModiford + " ������� ������. �������������� �������������� ����� �� " + pchar.questTemp.GoldQtyForSeek + " �������.";
                link.l1 = "���, '�������������� �����' - ��� ��� ������ ������, � ������������ ������� ��� �� ����� �������� ���������.";
                link.l1.go = "Step_7_6";
                pchar.items.jewelry5 = pchar.questTemp.GoldQtyForSeek;
            }
        break;

        case "Step_7_6":
            dialog.text = "�� ��� ��, � ����� � ����� ������� ����. ���� �������������� ��� ���� ������� ������. ���� ������ ��� ������ ��� � ����.";
            link.l1 = "�������, ���. ���� �������� � ��� ������������.";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 70000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "2";
            AddQuestRecord("Eng_Line_7_SevenTresures", "2");
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
            DeleteAttribute(pchar, "questTemp.GoldQtyGaveModiford");
            DeleteAttribute(pchar, "questTemp.GoldQtyForSeek");
			AddCharacterExpToSkill(pchar, "Repair", 500);
			AddCharacterExpToSkill(pchar, "Commerce", 550);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("����� ������� �����, ��� ����� ������� ����� ��������� ��������� ����� ��������� �������. � ���� �������� ��� �������, ��� ������ ����� ������� ������������ �� ������� � ������...", ENGLAND, 5, 1);
        break;

        case "Step_7_7":
            dialog.text = RandPhraseSimple("� ������ ����� ����� �� ������� �� � ���� ����� �������?", "������ ����� ��� �������� ������ � ���� ������.");
            link.l1 = "���, �� ���� �������� - � ��� "+ GetSexPhrase("�������","��������") +" ��� ����. ����� ���� ��������.";
            link.l1.go = "exit";
        break;
 
        case "Step_7_10":
			dialog.text = "��, ����� ����� �������� ����� ���� ����� � ��� �� ����������. � ����������� ���� � ������� �� ��� �����!\n����� � ��� �� ����������, �� ������ ����.";
            link.l1 = "�������, ��� "+ GetSexPhrase("��������","���������") +" ��� ����������, ���.";
            link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuestBox.Cartahena_Cave");
			DeleteAttribute(pchar, "GenQuestBox.Trinidad_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Terks_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Dominica_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Caiman_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Cuba_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Guadeloupe_Cave");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            AddQuestRecord("Eng_Line_7_SevenTresures", "4");
			AddQuestUserData("Eng_Line_7_SevenTresures", "sSex", GetSexPhrase("��","���"));
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			ChangeCharacterReputation(pchar, -5);
			AddMoneyToCharacter(pchar, -150000);
        break;

        case "Step_8_1":
            dialog.text = "������! �� ��� �, ��� �����.\n"+
                          "� ��������� ������������ ��� ��� ������� ����� � ������� �������. ��� ����� ��������� ��� ������ � ���� �����. ��� ���� � ���� �������� ������ ���.";
            link.l1 = "������, ���. � ���-�� "+ GetSexPhrase("���������","����������") +" �� �������?";
            link.l1.go = "Step_8_2";
        break;

        case "Step_8_2":
            dialog.text = "���, ���������� ����� ������. �� � ������ �� �����.";
            link.l1 = "�������. ��� ������ � ���� "+ GetSexPhrase("�����","������") +", �� ����� ����� � ����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "ToMansfield_GoOn";
            SetQuestHeader("Eng_Line_8_ToMansfield");
            AddQuestRecord("Eng_Line_8_ToMansfield", "1");
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1 = "location";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1.location = "LaVega_town";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition = "ToMansfield_IntoTheTown";
            SetLocationCapturedState("LaVega_town", true);
			//--> ����� � �������
			locations[FindLocation("LaVega_town")].hidden_effects = true;
			locations[FindLocation("LaVega_ExitTown")].hidden_effects = true;	
			//<-- ����� � �������
            Log_QuestInfo("���� ���������� ���� � �����.");
        break;

        case "Step_8_3":
            dialog.text = "���� ������!!! ��� ���-������ ������� ��������� ��������?";
            link.l1 = "����� �� ������� ���� �� ��������. � ���������� �� �����������.";
            link.l1.go = "Step_8_4";
        break;

        case "Step_8_4":
            dialog.text = "����� ������. � ����� ��� ��������� ��� ���� ��� ������.";
            link.l1 = "�������, ���.";
            link.l1.go = "exit";
            npchar.TempQuest.KnowAboutModiford = 1;
        break;

        case "Step_8_5":
            dialog.text = "��� ����� ��������. ������� �� ��� ���� ����� ������.";
            link.l1 = "������, ���.";
            link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
            DeleteAttribute(npchar, "TempQuest.KnowAboutModiford");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Eng_Line_8_ToMansfield");
            SetLocationCapturedState("LaVega_town", false);
			//--> ����� � ������� �������
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "hidden_effects");	
			//<-- ����� � �������
            // ==> �������� ����, ������ �� ����� ��������� �����.
            sld = characterFromID("Edward Mansfield");
            LAi_SetStayTypeNoGroup(sld);
            sld.model = "bocman";
        	sld.name 	= "�������";
        	sld.lastname = "���";
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            QuestSetCurrentNode("Edward Mansfield", "No_Mansfield_first_time");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Edward Mansfield")], "LaVega_townhall", "sit", "sit1");
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			AddCharacterExpToSkill(pchar, "Sailing", 550);
			AddCharacterExpToSkill(pchar, "FencingLight", 450);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("����� �����, ��� ��������� ���������� �� ��������� �������� ���������...", ENGLAND, 5, 1);
		break;
        
        case "Step_9_1":
            pchar.questTemp.State = "AttackSantiago_GoOn";
            if (!CheckAttribute(npchar, "TempQuest.KindResult")) // ������ �� ��������, �� � ����� ��������� ��������
            {
                dialog.text = "� ���������� ������������ �������� � ��� ������� ���������� ����� ����������, ��� ����� �� ���������� �������� �� �� ����.";
                link.l1 = "� ��� �� ���?";
                link.l1.go = "Step_9_2";
            }
            else if (npchar.TempQuest.KindResult == 2) // ������� ���������� ���������� ������, 2 == ������ �� � �����, ��� ���������
            {
                dialog.text = "���� ������� �� ������ ��������, ��� ����� � �� ���� ������� ����������� ��������� ��������.";
                link.l1 = "����, ���.";
                link.l1.go = "Step_9_2";
            }
            else // ������� ���������� ���������� ������, 1 == ���� ��������� ������
            {
                dialog.text = "��������� ���������� ���� �� ��������� ������� ������, �� ������ ����� ����� ���� ������������, ��� ����� �� ���������� �������� �� �� ����.";
                link.l1 = "��, ���. ������ � "+ GetSexPhrase("������","������") +".";
                link.l1.go = "Step_9_2";
            }
            Log_QuestInfo("������� ��������.");
            DeleteAttribute(npchar, "TempQuest.KindResult");
			characters[GetCharacterIndex("Santiago_Mayor")].dialog.captureNode = "EL9_SantiagoAttack"; //�������������� ���� ����
        break;

        case "Step_9_2":
            dialog.text = "������ ��������� ���� ������������ ������������ �������� ���� ����� ���������. ��� ���������� ���� �������� �� ������� ������� ������ �������, ������������� �������-������ � ���� �����.";
            link.l1 = "��� ��� ����� �������?";
            link.l1.go = "Step_9_3";
        break;

        case "Step_9_3":
            dialog.text = "��� ����� ������� �� �������� � ��������� ��� ����������� ���� ����� ��������. ��� ����� �������, ����� - ���.";
            link.l1 = "� "+ GetSexPhrase("�����","������") +", ���.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_9_AttackSantiago");
            AddQuestRecord("Eng_Line_9_AttackSantiago", "1");
        break;

        case "Step_9_4":
            dialog.text = "���� ������, �� ������������� ����������� �������, " + pchar.name + ". �������� ������� �� �����!";
            link.l1 = "��� ��� ������ � ���������?";
            link.l1.go = "Step_9_5";
            QuestSetCurrentNode("Santiago_Mayor", "First time");
        break;

        case "Step_9_5":
            dialog.text = "������ ��� ����� ��������� �������. � ������ ������� ��, ������� ��� ����� � ���� ������� ������� ����������.\n"+
                          "���, � �������, ����� ��������� � �������� ���� � ������� ����� ����� ������������ ���������. �� ���� �����������, �������� �� ��� � ����� �����.\n"+
                          "��, � ���... ������� � �������, � �����, ��� ����� ����� ������� ������, ��� ����� �� ������� ��������� ���������� ��� ����� � ����������. �������� ��� ��� ������� ��� ����...";
            link.l1 = "������, ���. ����������� �����.";
            link.l1.go = "exit";
            QuestSetCurrentNode("Henry Morgan", "Give_blade");
            sld = characterFromID("Himenes");
            RemovePassenger(pchar, sld);
    	    sld.LifeDay = 1; // ������ ��� �� ����.����.
    	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Eng_Line_9_AttackSantiago");
			AddCharacterExpToSkill(pchar, "Repair", 550);
			AddCharacterExpToSkill(pchar, "Cannons", 760);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Pistol", 300);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�������, ��� ������ � ��� � �������, ��� �� �������� � ���� ����� �������� ���������� �����������! �� "+ GetSexPhrase("��������� �����","��������� �������") +", �������...", ENGLAND, 5, 1);
        break;
        
        case "Step_10_1":
            dialog.text = "������� ������ ������ ��������� � ����. ������� ����� ���������� �������� �������� ����� - ��� ������ ����������! �� �� ���������� � ����!";
            link.l1 = "��, ���. ���� ��� � ���� � ������� ������� ������, ��� �� �����, �������� ����� ��������� ��������. � �������, �������, ���� �� ��������� �� ������ �����...";
            link.l1.go = "Step_10_2";
        break;

        case "Step_10_2":
            dialog.text = "�������� � ����, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". �������, ��� ����� � 80000 ������, ����� �������� ���� ������� � ������� � ������� ����� �������. �� ����� ������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", � ������ ��� �� �������!\n"+
                          "��������, �� ������ ��� ����� �������� �� �������� �����... ����� ��� ��������� �� ��� ����� ������.";
            link.l1 = "������, � ���������� ���� � ��� � ����������� ����, ���.";
            link.l1.go = "exit";
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Eng_Line_10_SpanishAttack");
			AddCharacterExpToSkill(pchar, "Repair", 600);
			AddCharacterExpToSkill(pchar, "Leadership", 550);
			AddCharacterExpToSkill(pchar, "Commerce", 600);
			AddCharacterExpToSkill(pchar, "Accuracy", 400);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 80000);
			//�����
			AddSimpleRumour("�������, �� ������ ������ ��� ����. ������ ������ ��� ���� ������������ ��� �� ��� ������.", ENGLAND, 10, 6);
        break;
        
        case "Step_11_1":
            dialog.text = "������� �� ��������� �������� �� ���� ����� ����� ���� ��������� �� ��������� ������.\n"+
                          "����� � ���������� �� ���������� ��������� ��� ��������� ������: ������ � �������. ��������� ��� ������ � ��������� ��������� � ������� ��� ���������� ����� II �������.\n"+
                          "������������ ���������� ����� ������������� ��� ������������ ���������� ���������� � ���������� ����� ������� � ������.";
            link.l1 = "� "+ GetSexPhrase("�����","������") +", ���. ��������� �� ���� ����������.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_11_OccupyMein");
            AddQuestRecord("Eng_Line_11_OccupyMein", "1");
            pchar.questTemp.State = "OccupyMein_GoOn";
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //�������������� ���� ����
			characters[GetCharacterIndex("Caracas_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //�������������� ���� ����
        break;

        case "Step_11_2":
            dialog.text = "�����������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". ������ �����������! ����������� �� ������� ������ �� ����� ����������� ���!\n"+
                          "� ����� ��� ���� � ���� � ���������� ����� �����. � ���� ����� ����� ��� ��� ����.";
            link.l1 = "������, ���.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Q11_Cumana");
            DeleteAttribute(pchar, "questTemp.Q11_Caracas");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Eng_Line_11_OccupyMein");
			AddCharacterExpToSkill(pchar, "Repair", 1000);
			AddCharacterExpToSkill(pchar, "Commerce", 1600);
			AddCharacterExpToSkill(pchar, "Accuracy", 1000);
			AddCharacterExpToSkill(pchar, "Defence", 1100);
			AddCharacterExpToSkill(pchar, "Cannons", 1300);
			AddCharacterExpToSkill(pchar, "Sailing", 1200);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�������, ������, ��� ����� ��� ����� �������� " + pchar.name + ""+ GetSexPhrase("-�����������","-���������������") +"", ENGLAND, 5, 1);
        break;
        
        case "Step_12_1":
            dialog.text = "���-�� ��������� ���������� � ����-������. � �� ������� ���������� ����������� � ��������� ��� �� ����������� ������.\n"+
                          "�� ��������� ���� ���������� �����, ������� � ����� ��� ����������� � ���������� ����-������ � ��������� �������� � �����������.";
            link.l1 = "������, ���. �� �����, ��� ���������� �����-���� ��������, �� � ��� �����.";
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_12_ColonelLinch");
            AddQuestRecord("Eng_Line_12_ColonelLinch", "1");
            pchar.questTemp.State = "ColonelLinch_GoToKingstown";

            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1 = "location";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1.location = "SentJons_townhall";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition = "ColonelLinch_IntoTheResidence";
        break;

        case "Step_12_2":
            dialog.text = "��... � ���?";
            link.l1 = "�� ������� ����������� ������������� �� ����������, ���...";
            link.l1.go = "Step_12_3";
        break;

        case "Step_12_3":
            dialog.text = "�� ��� ������... ������, �� ���!!!";
            link.l1 = "���������!!!";
            link.l1.go = "Step_12_4";
        break;

        case "Step_12_4":
            pchar.nation = PIRATE;
            LAi_SetImmortal(npchar, true);
            LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), true);
            bDisableFastReload = true; // ������� ��������.
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            LAi_NoRebirthEnable(npchar);
            //LAi_SetActorType(npchar);
            //LAi_ActorAfraid(npchar, pchar, false);

            LAi_group_Register("EnemyFight");
           	float locx, locy, locz;
            GetCharacterPos(pchar, &locx, &locy, &locz);
			//�������� ���������� �� ���������� ������
			int num = FindNearCharacters(pchar, 20.0, -1.0, -1.0, 0.01, true, true);
			if(num > 0)
			{
				for(int i = 0; i < num; i++)
				{
					int idx = sti(chrFindNearCharacters[i].index);
					sld = &Characters[idx];
					if (sld.chr_ai.type == "guardian")
					{
						LAi_NoRebirthEnable(sld);
						LAi_CharacterReincarnation(sld, false, false);
						LAi_group_MoveCharacter(sld, "EnemyFight");						
					}
				}
			}
			//������� ������ ��� ���������
            string SModel;
            for (i=1; i<=3; i++)
            {
                SModel = "off_eng_"+i;
                if (i == 3) SModel = "sold_eng_3";
                sld = GetCharacter(NPC_GenerateCharacter("EngSolder"+i, SModel, "man", "man", 30, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 100, "topor1", "pistol3", 250);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ColonelLinch_AfterFight");
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
			//�����
			AddSimpleRumour("�� � ���� � ��� ����������!! ���������� �������� ��������� � ������� � ������ ����� �� ����� ������������ �������! ��, ����!..", ENGLAND, 5, 1);
        break;

        case "Step_12_5":
            dialog.text = "�� �����������! �� ������� ��� �� �������.\n"+
                          "� �������� ������������� ������ ��������, ��� ���� ������� ����� ���������� ������� � ������� ����.\n"+
                          "� ���� ����� �������� � ���������� ��� � ��������� ������. ������ ����� ����� ������ ������ ������ ����� ������������� ��������� ���.\n"+
                          "�����, � ���������� ������������ ������������� ������������ ���������, ������� ��� �������� ���������. ����� ���� ����� ����������� ���, ���. ��� ������ ����� �������. �������� ��������.";
            link.l1 = "��������� ���. �������, ��� � ����� � ����� ���� ��� �� "+ GetSexPhrase("�������","�������") +" ��� ����������.";
            link.l1.go = "Step_12_6";
        break;

        case "Step_12_6":
            dialog.text = "� ��� �� ����������� �� ���.\n"+
                          "�������, ��� � ����� ��������, ���, ��������� ���� ������ ����� ����������. � �� ���������, ��� ������� ��� �� ����. ����, �� ������ ������...";
            link.l1 = "� "+ GetSexPhrase("�����","������") +", ���. ������� ��� ������ ��� ����������� ���������� ������� � ��������� ����.";
            link.l1.go = "exit";
			pchar.name = "��� " + pchar.name;
            AddMoneyToCharacter(pchar, 300000);
            AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            SetNationRelationBoth(SPAIN, ENGLAND, RELATION_NEUTRAL);
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // ����� �������
        break;
        
        
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
