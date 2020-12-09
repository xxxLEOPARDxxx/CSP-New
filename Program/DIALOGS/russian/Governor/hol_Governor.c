// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr2Letter_toCuracao")
			{
                dialog.text = "� ������ ���.";
                link.l1 = "�������� �������-����������, ��� �������� ��������� ��� ������.";
                link.l1.go = "Step_F2_1";			
			}
			if (pchar.questTemp.State == "Fr2Letter_NiceResult")
			{
                dialog.text = "����� ��? ����� ����� �� �������?";
                link.l1 = "�� ���� ��� ���, ����� �������-����������. � ���� ���� ������� ������� ��� ���.";
                link.l1.go = "Step_F2_4";			
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				link.l1 = "� ���� �������� �� ����� ��������. �� �������� � ���������� �������� ���.";
				link.l1.go = "TizerFind";
			}
		break;

		case "work_1":  // ������ �� ����� ������ - ������� �����
            // ���� ���� ������ � ��������, �������� ����
            dialog.text = LinkRandPhrase("�� ���������� �� ������ ���������� ����������� ���������! ����� ���������� ���������� � ���������� ������������ �� ��� ���������!",
                                         "� �� ���� ��������, ��� �� ����� �������� �������� ������ �������. ������� ����������� � ���������� ������ �� ���� ������������!",
                                         "� ��� ������ ������� � ���������� ����� �������������� ���������, �� �� ����������� ����������.");
            link.l1 = RandPhraseSimple("��������� ����������, ������", "� ��� � �������� ����������...");
            link.l1.go = "exit";
            
        	switch (pchar.questTemp.State)   // ��� ������ � ������ ������
            {
                case "empty":   // ��� ������ �������
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase("� ������ ������ � ���� ��� ��� ��� ������������� ���������. �� ������ ��������� � ���� � ���������� �����...",
                                                     "����� ���� ��������, � ����� ������ ����� � ������ ������!",
                                                     "����������� ������ ���������� ������ �� ����, ������ � ���� ��� ��� ��� �������.");
                        link.l1 = "������, ������.";
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // ������ ������� ������� �� �������
                        {
                            case "2":
                                dialog.text = "� ���� ���� ��� ��� ����� ���������. ���������� �������� � ����� ����� �������������� ��� ������� ������ ����, �������, �������� � ����������� ������. ������������� ����������, ��� ����������� ��� ����� ������, ������� �� ���������� ����� �����.";
                                link.l1 = "�� ������� - ��������?";
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = "������ �������� ���, ��� �� ��������� � ��������� ����� � �������, �������� ��������� �������� �����.";
                                link.l1 = "��� ���...";
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
                                {
                                    dialog.text = "�� ������ ��������� ����������. ��������� ������ �� ������� ���, ����� ��������� ��� ��������� ������������ � �������, ������ ����� ����������� ���� �����, ����������� � ��� ��� ����� �� ������, ��� ����� ����������.";
                                    link.l1 = "��, ������, ��� ��� ��������.";
                                    link.l1.go = "Step_4_1";
                                }
                                else
                                {
                                    dialog.text = "�� �� ������ ������� ������� ��������� ���������� �������. ������ ��� ������ ������� � ������� ���� ��������� ������� ����������. ������ � ������������ ��� ����������� �����������������. � ���������� ���������� ���������� � ������ �����, ��� ��������� ������ �� ������� ���, ����� ��������� ��� ��������� ������������ � �������, ������ ����� ����������� ���� �����, ����������� � ��� ��� ����� �� ������, ��� ����� ����������.";
                                    link.l1 = "�������...";
                                    link.l1.go = "Step_4_1";
                                }
                            break;
                            case "5":
                                dialog.text = "����, ��� ���� ��������� �������. ����������� ��� � ���, ��� ��� ����� ����������� ��� ��������� ������ � ��������� ���������� �� ���� � ������� ��������.";
                                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������.";
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = "��� � ��, � ���� ���.";
                                link.l1 = "� ����� �������, ������.";
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = "� ���� ��� ��� ���� ��������� ������. ��� ���������� ��������� ������ �������-����������� ������� �������� �'�������. ������� ��� � ������ ���������� � ������������� ����� ������� ������ �������. ������ ��������� ������ ��������, ������� ����� ��� ��������, ��������� � ������ ���. ������ ������ �� ������ ������� ������, ����� �������-����������� �������, ��� �������������� ����������!";
                                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ��� ����� ��������� � ���������� ����, ������ ����� �'������ ������� ������ ������.";
                                link.l1.go = "Step_7_1";
                            break;
                            case "8":
                                dialog.text = "� ���� � ��� ������ �������. ��� ����, ����� ������ ���������� �������, �������� �� �������� �� ������, ������ ������������� � ���� ���������� �������. ����� ����� ����������� � ���� ������ ���. ������� ��� ����������� � ������ ����-��, ����� ��� �������. � �����, ����� ��������� ��� ��� ���, �� ������ � ����� ����, ��������� ���.";
                                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ���������� ���������� � ����.";
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SeekBible_toAaron";
                                AddQuestRecord("Hol_Line_8_SeekBible", "1");
								AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","�"));
                                SaveCurrentQuestDateParam("questTemp");
								sld = characterFromId("Chumakeiro");
								LAi_SetStayTypeNoGroup(sld);
                                ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "goto", "goto1");
                            break;
                            case "9":
                                dialog.text = "�� ���������� ��������� ��������� � ���������� �� ����� ����������� ������ �������� �������� � ������� �������������� - ����������� ������, ������ ��... � ����� ��������� ��� ���� ��������� ������, � ��� ��� ������ � ������ ���������� �����!";
                                link.l1 = "����� ��, ������?";
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = "���� ������, " + pchar.name + ", �� ���� �����, ����� ���������� ��� �������� ������� ���� ������� �����, � ��������� ����...";
                                link.l1 = "��� ���������, ������?";
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = "��� � ��! � ���� ������ ��������� � ����������.";
                                link.l1 = "��� ���������, ������?";
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = "����� ��������� ���, ��� ��������� ��������� �����, ������� ������������ ���������. ��� ���������. ������ ������ ������ ����� ���������� �� �������� ���������� ����������� ���������!";
                                link.l1 = "������� �����, ������.";
                                link.l1.go = "Step_12_1";
                            break;
                        }
                    }
                break;

                case "":           // ����� �1, �������� ����� ���������� ������� ������.
                    dialog.text = "�� ��� ��, � ���� ���� ��� ��� ������ ������ ��� ������ �������. �������, ��� ����� ��� �� �����.\n"+
                                  "���� ��� � ���: � ��� �� ������� � ��������� ����� ����� ��������� �������� ����� ������������ �� ������, � �������� �� �������� � ���������, ��� ������������ ����������. ������� � ��� ������� ��� �� ���������� ������ �������. ���� ���������� ������ ����������, ����������� �������� �������� �� ��������� �� ���-������ ������ ����������� �������� ����� ������ ���������.\n"+
                                  "��� ������� ���������, ��� ������ �������� � ������� ����. ������������� � ������ � ��������� ��� �� ���, ������� ������ ���������� ����� ��������� � ���.";
                    link.l1 = "��������� ��� ��������, � ��� ����� ���������?";
                    link.l1.go = "Step_1_1";
                break;
                case "SeekChumakeiro_GoToVillemstad":
                    dialog.text = "�� ��� ��, ����� ��� ��� ��� ���������. ������� ������, "+ GetSexPhrase("������","�������") +". �������� �� ��� ����� ��������� �����, ��� �������, ��� � ���� ������������ ������ �������� � ������.";
                    link.l1 = "������, ������.";
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "2";
                    pchar.questTemp.Waiting_time = "7";
                    CloseQuestHeader("Hol_Line_1_Chumakeiro");
					AddTitleNextRate(sti(NPChar.nation), 1);
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(pchar, "Pistol", 150);
					AddCharacterExpToSkill(pchar, "Grappling", 120);
					ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
					//�����
					AddSimpleRumour("�� ������, ��� �������-���������� ��������� ����� �������� " + GetMainCharacterNameGen() + " ��� �������� ��� ����� �� ������ ����, � ����������. � �� ������, ��������� ���� ������� ���������.", HOLLAND, 5, 1);
                break;
                case "TakeFoodCuracao_toOrangeStore":
                    dialog.text = "����, �������, � ��� ���������� � �������?";
                    link.l1 = "�������� ���� ��������� �� �������� ����� �� ����� �����, ������.";
                    if (GetQuestPastDayParam("questTemp") > 60)
                    {
                        dialog.text = "� ������ ��� ��������� ��� ��� ������ � ������� 60 ����. �� �� ����������....";
                        link.l1 = "�����, � �� ������"+ GetSexPhrase("��","���") +" �� ������� - ���� ��������� �������� � ������...";
                    }
                    link.l1.go = "Step_2_5";
                break;
                case "WormEnglPlans_SurrenderWorkMorgan":
                    dialog.text = "��� � ��, �������-��! ������������� ����������, ��� �� ������.";
                    link.l1 = "�������� ������ �� ����� � ������ ���������. �� � �����, ��� �������� ������� �������� �������� � ��������� �� �������. ����� �������, ����� ������������, ��� ������ �� �������� ������ �������� ������ ����������� � ��������� ���� ���������� �������.";
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_SaveOfficer":
                    dialog.text = "��� � ��, �������-��! ������������� ����������, ��� ��� ������� ��������.";
                    link.l1 = "�������� ������ �� ����� � ������ ���������. ������� �������� ����� ������ ������������, ��� ������ ��������� ����������� ��������� ����.";
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_GoodRusultWorm":
                    dialog.text = "��� ��� ������� ��������?";
                    link.l1 = "�������� ������� ��������� �� ���� �����. ���� ���������� � ������ ������ ��������� ���� �����. �������� ������� ��������� �������� ������� �� �������, �� � ���� ������ � ���� �� �����. ��� ��� ��� ��� ����� ������� ��������, ������ ����� ����� �����, � ��������� ���.";
                    link.l1.go = "Step_3_7";
                break;
                case "DefenceOrange_LateRiseOrange":
                    dialog.text = "������������, ��� � ������ �����?";
                    link.l1 = "������, � �� ����"+ GetSexPhrase("","��") +" ������ �� ������ ����� �����. ���������� ������ ����������, ����� ����� ��� ������������ ��������� ����� �� ����������...";
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_DieHard":
                    dialog.text = "������������, ��� � ������ �����?";
                    link.l1 = "������, � �� ����"+ GetSexPhrase("","��") +" ������ �� ������ ����� �����. �� ���� ���, �� ��������� ��������� �������. ��� �������� ��������� ��������... � ���������, ����� ����� ��� ������������ ��������� ����� �� ����������...";
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_LandingDestroyed":
                    dialog.text = "������������, ��� � ������ �����?";
                    link.l1 = "������, ������� ���������. ��� ������� � ��������� ����� �������� ���������� ��� ������� ���������� � �����. ��� ����� ������ �� ��������.";
                    link.l1.go = "Step_4_4";
                break;
                case "DefenceOrange_SquadronDestroyed":
                    dialog.text = "������������, ��� � ������ �����?";
                    link.l1 = "������, ��� ������� ���������� ������� �������� �� ����. ��, � ���������, � �� ����"+ GetSexPhrase("","��") +" ������������� ��������� ����� ���������. ���� ����� ��������...";
                    link.l1.go = "Step_4_5";
                break;
                case "ThreeFleutes_DieHard":
                    dialog.text = "��� ��� ��������, ��� �� �� ������ ������� ��������� ��� ������. ����� ����, �� ������� � ���� ���!";
                    link.l1 = "������, � ������� ��������� �� ���� ������ ����� ������� ��������! ���� ���� ������� �������...";
                    link.l1.go = "Step_5_3";
                break;
                case "ThreeFleutes_AllFleuts":
                    dialog.text = "������������, ��� � ��� ���������?";
                    link.l1 = "������, � ������� ��������� �� ���� ������ ����� ������� ��������! �� � �����"+ GetSexPhrase("","�") +" ��������� ��������� ��� �������.";
                    link.l1.go = "Step_5_4";
                break;
                case "ThreeFleutes_LostFleuts":
                    dialog.text = "��� ��� ��������, ��� �� �� ������ ������� ��������� ��� ������. ��� ����� �����.";
                    link.l1 = "������, � ������� ��������� �� ���� ������ ����� ������� ��������!";
                    link.l1.go = "Step_5_9";
                break;
                case "RevengeMansfield_FromMorganWithResult":
                    dialog.text = "���, ��� ��� ������. ����� �������, ��� �� ��� ����������?";
                    link.l1 = "��, ��� � ���� �������? �� ����������� ������ �������� � ��� �����������!";
                    link.l1.go = "Step_6_2";
                break;
                case "DelivLettTortuga_NotFoundLetter":
                    dialog.text = "�������� � ����������� ����� ������.";
                    link.l1 = "� ������� ��������"+ GetSexPhrase("","�") +" ���� ������ �'�������.";
                    link.l1.go = "Step_7_2";
                break;
                case "DelivLettTortuga_LetterFound":
                    dialog.text = "�������� � ����������� ����� ������.";
                    link.l1 = "� ������� ��������"+ GetSexPhrase("","�") +" ���� ������ �'�������.";
                    link.l1.go = "Step_7_8";
                break;
                case "DelivLettTortuga_WaitingNews":
                    if (GetQuestPastDayParam("questTemp") > 30)
                    {
                        dialog.text = "�� ��� ��, ��� ���� ������ �������. �'������, ������ ���, ��������� ����������� ������ ��������� ��� ��������. ������� ����� �������� ������� ������ �� ������.";
                        link.l1 = "����� �������!";
                        link.l1.go = "Step_7_20";
                    }
                    else
                    {
                        dialog.text = "� ��� �� ������� �������� �� �'�������. ������� �����.";
                        link.l1 = "������, ������.";
                        link.l1.go = "exit";
                    }
                break;
                case "SeekBible_BadResult":
                    dialog.text = "��������� ����� �� ���� ����������, ��� �� �� ������ ��������� ��� ���������.";
                    link.l1 = "� �����-��, ��. � ������"+ GetSexPhrase("","�") +" ���, ��� ���.";
                    link.l1.go = "Step_8_1";
                break;
                case "SeekBible_GoodResult":
                    dialog.text = ""+ GetSexPhrase("���� ���","�������") +", ����� � ��� ������ ��������� � ����������� �������. �� ��� ������, ��� �� ������ ������� ����� ����� ������ ��� ����. ������� ���, ��� ���?";
                    link.l1 = "� ������ ��������"+ GetSexPhrase("","�") +" ��� ���� ���� ��������� �������. �����, ������� ������������ �������.";
                    link.l1.go = "Step_8_2";
                break;
                case "TakeThreeShips_toAbordage":
                    dialog.text = "��-�-��, ��� �� ������� ��� �� ������ ������ �������? ��� ���� ������ ��������?";
                    tempQty = 0;
                    for (i=1; i<=COMPANION_MAX; i++)
                	{
                        chComp = GetCompanionIndex(pchar,i);
                        if(chComp != -1)
                		{
                			sld = GetCharacter(chComp);
                    		iShip = sti(sld.ship.type);
                    		iBaseType = sti(RealShips[iShip].basetype);
                            if (iBaseType == SHIP_MANOWAR || iBaseType == SHIP_INTREPIDE || iBaseType == SHIP_FR_TRINITY || iBaseType == SHIP_MANOWAR_FAST || iBaseType == SHIP_BATTLEMANOWAR || iBaseType == SHIP_MANOWAR_GUB || iBaseType == SHIP_PRINCE || iBaseType == SHIP_HMS_VICTORY || iBaseType == SHIP_SP_SANFELIPE)
                            {
                                tempQty++;
                                RemoveCharacterCompanion(pchar, sld);
                                AddPassenger(pchar, sld, false);
                                AddMoneyToCharacter(pchar, 75000);
                            }
                        }
                    }
                    if (tempQty == 0)
                    {
                        link.l1 = "���� ������ ���������� ������ �������� ��� ��������� �� �������. �� � ������� ��� ����, �����, ������...";
                        link.l1.go = "exit";
                    }
                    else
                    {
                        if (sti(pchar.questTemp.QtyShips) > tempQty)
                        {
                            if (tempQty > 1)
                            {
                                link.l1 = "�������, ������. � �����"+ GetSexPhrase("","�") +" ����� " + tempQty +  " �������.";
                            }
                            else
                            {
                                link.l1 = "�������, ������. � �����"+ GetSexPhrase("","�") +" ����� ���� �������.";
                            }
                            link.l1.go = "Step_9_5";
                            pchar.questTemp.QtyShips = sti(pchar.questTemp.QtyShips) - tempQty;
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "2");
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyTook", tempQty);
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyElse", pchar.questTemp.QtyShips);
                        }
                        else
                        {
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "3");
                            link.l1 = "�����������, ������. ������� ��������� ���������.";
                            link.l1.go = "Step_9_6";
                            DeleteAttribute(pchar, "questTemp.QtyShips");
                        }
                     }
                break;
                case "SpaAttackCuracao_GoodWork":
                    dialog.text = "� ��� �����! ��� ���� ������ �����������!";
                    link.l1 = "�������, ��� ������� � ����� ���� ���������� ��������...";
                    link.l1.go = "Step_10_3";
                break;
                case "SpaAttackSentMartin_Late":
                    dialog.text = "������������, �� ������ �������� ��� ������?";
                    link.l1 = "������, � ������"+ GetSexPhrase("","�") +" ���, ����� ������, ���� ������� ������... ������ ������ ��������� �����.";
                    link.l1.go = "Step_11_5";
                break;
                case "SpaAttackSentMartin_GoodWork":
                    dialog.text = "������������, �� ������ �������� ��� ������?";
                    link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ����� ��������� ������� � ������ ���-������ �����. ������� �����������.";
                    link.l1.go = "Step_11_8";
                break;
                case "OccupyMaracaibo_toWeWon":
                    dialog.text = "��� ����, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", ��� �������� � ����� ������������� ������!";
                    link.l1 = "������, ��� ������� ��������� ���������. ������ ��� ����������� �������.";
                    link.l1.go = "Step_12_3";
                break;
                case "QuestLineBreake":
                    dialog.text = "� �� ���� ���� � ������, ����������� ���� �����. ��� ������ ������ ��� �������.";
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
                case "EndOfQuestLine":
                    dialog.text = "���������� �������������� � ��������� �����������, � ����������� �� ��� ������� �����.";
                    link.l1 = "������, ������.";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // ����� �������
                break;
            }
        break;
        //********************** ����� �1, �������� ����� ���������� ������� ������. ************************
        case "Step_1_1":
            dialog.text = "������������ ����������� �������, ���� ��� ��� ���������.\n"+
                          "�������� ��� � ��������� �������� � 1640 ���� �������������� �������� �� ���������. ������� ������������ �������� ������������ �������� � ��������������� ������� � ���������� �������������� ����� ������������ �������. ������� XIV ����� ������� ���������� ��� ������.\n"+
                          "���������� ������ �����, ��� ���� ������, �������� ������ ������ ����� ��� �������� ����������� ������� �� �������. ���� � ���, ��� ����������� �� ��� - ��� �������, �������, ������ � ������� ����������. ����� ���� ��� ������� �� ����� ����� �������.\n"+
                          "�� ��� ��, ���� �� ������, �� ����� ���������� ���������� � ���������� ������������ ������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ��������, � ����� �������.";
            link.l1.go = "Step_1_2";
            link.l2 = "��������, �� � ������ ������ � ����� �����"+ GetSexPhrase("","�") +". ����� � �����"+ GetSexPhrase("","�") +" ���� ��������� ��� ���� ���������.";
            link.l2.go = "exit";
        break;
        case "Step_1_2":
            SaveCurrentQuestDateParam("questTemp");
    		// ��������� ������� � ��� -->
    		pchar.questTemp.NationQuest = HOLLAND;
    		// ��������� ������� � ��� <--
    		pchar.questTemp.State = "SeekChumakeiro_ToAaronHouse";
            sld = GetCharacter(NPC_GenerateCharacter("Chumakeiro", "usurer_4", "man", "man", 10, HOLLAND, -1, false));
        	sld.name 	= "����� ������";
        	sld.lastname = "���������";
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.greeting = "Gr_padre";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "goto", "goto1");
            AddQuestRecord("Hol_Line_1_Chumakeiro", "1");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("","�"));
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1.location = "Marigo_houseF1";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition = "SeekChumakeiro_intoMarigoHouse";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        //********************** ����� �2, ������� � �������� ������ �� ����� �����. ************************
        case "Step_2_1":
            dialog.text = "������ ��������. ��� ������� ���� ������ ������ ����� ���� ��� ����� ������� ����. ��� ������ �� ������� ��� ����������� ������� ����������� ����� - �� �������� �������� ����.\n"+
                          "�������������� ��� ��� ������ ���������� �� 400 ������ ������� ������������. ���� ��� ��� ����� �������� � ������ ��� ������� �� �������������.\n"+
                          "� ������������ � ����� ��������� � ������� ��� �� ������� 17700 �������. �������� ��������.";
            link.l1 = "���� �� ������������ ������ ��������, �� �� ���������� ���, ������� ��� ������ ���������� � ���������? ��� ����� ����������� ���������.";
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = "�������, ��������. � ����� ��������� ��� ���� ������ ���������� 5600 ���������.";
            link.l1 = "��, ������... ������, � "+ GetSexPhrase("��������� �������","�� �������� �������") +", � ��� ��� �������� � ����������� ������ �� ����� �� ����...";
            link.l1.go = "Step_2_3";
        break;
        case "Step_2_3":
            dialog.text = "��� ������, ��� ��, ��� �������, "+ GetSexPhrase("��������� �������","� �� �������� �������") +", � ������ ��� � ��������� � ���������� ������� ���������. ��� ���� ���� ����� ����� � ������� � �����������, � ��� �������, ��� ������ "+ GetSexPhrase("��������� �������","�����") +" ������ ���������� ��� ����������� � �����������.\n"+
                          "������ ������� �������, ��������� � ��� �� ��������� ��������� ������, ������� ������ �����... ��� ��� ����� ��� ������ ���� �����...\n"+
                          "������ �� ���������� ������� ��������� � �� ��� �� �����. �����������! � �������, ��� ��� ������, ��� 5600 ���������, ����� ��� �����, � �����������, �� �����, ��� ����� ��� ������.";
            link.l1 = "��, �-��... �� ������, ������, � ��� ������. �� �� ���������� ��� ������.";
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = "����� ���, ��� �� �����������. �� ��� ��, � ��� ��� � ������.";
            link.l1 = "�� �������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeFoodCuracao_toOrangeMayor";
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "1");
            ChangeItemDescribe("Trust", "itmdescr_Trust_HolLineQ2");
            GiveItem2Character(pchar,"Trust");
            AddMoneyToCharacter(pchar, 17700);
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.EbonyQtyElseNeed = 400;
            pchar.questTemp.CoffeeQtyElseNeed = 400;
            pchar.questTemp.MahoganyQtyElseNeed = 400;
            pchar.questTemp.SandalQtyElseNeed = 400;
        break;
        case "Step_2_5":
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = pchar.Ship.Cargo.Goods.Ebony;
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = pchar.Ship.Cargo.Goods.Coffee;
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = pchar.Ship.Cargo.Goods.Mahogany;
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = pchar.Ship.Cargo.Goods.Sandal;
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
                    if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = sti(pchar.questTemp.EbonyQty) + sti(sld.Ship.Cargo.Goods.Ebony);
                    if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = sti(pchar.questTemp.CoffeeQty) + sti(sld.Ship.Cargo.Goods.Coffee);
                    if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = sti(pchar.questTemp.MahoganyQty) + sti(sld.Ship.Cargo.Goods.Mahogany);
                    if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = sti(pchar.questTemp.SandalQty) + sti(sld.Ship.Cargo.Goods.Sandal);
                }
            }
            tempStr = "������, � ������"+ GetSexPhrase("","��") +" ��������� ������.";
            if (CheckAttribute(pchar, "questTemp.EbonyQty"))
            {
                if (sti(pchar.questTemp.EbonyQty > 0)) tempStr = tempStr + " ������� ������ - " + pchar.questTemp.EbonyQty + " ����.";
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQty"))
            {
                if (sti(pchar.questTemp.CoffeeQty > 0)) tempStr = tempStr + " ���� - " + pchar.questTemp.CoffeeQty + " ����.";
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty > 0)) tempStr = tempStr + " �������� ������ - " + pchar.questTemp.MahoganyQty + " ����.";
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty > 0)) tempStr = tempStr + " ����������� ������ - " + pchar.questTemp.SandalQty + " ����.";
            }
            dialog.text = "��������, ������� � ���� �� �������� �� ����� �����.";
            link.l1 = tempStr;
            link.l1.go = "Step_2_6";
            if (tempStr == "������, � ������"+ GetSexPhrase("","��") +" ��������� ������.")
            {
                link.l1 = "������, � � �������� ����������. ���� ������ ������ ��������� �� �����"+ GetSexPhrase("","�") +", ����� ���� ��������...";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.EbonyQty");
                DeleteAttribute(pchar, "questTemp.CoffeeQty");
                DeleteAttribute(pchar, "questTemp.MahoganyQty");
                DeleteAttribute(pchar, "questTemp.SandalQty");
            }
        break;
        case "Step_2_6":
            tempStr = "����, ������� �������� ����.";
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed"))
            {
                HolLine2_NullGoods();
                if (sti(pchar.questTemp.EbonyQty) >= sti(pchar.questTemp.EbonyQtyElseNeed))
                {
                    tempStr = tempStr + " �� ��������� ����������� �������� ������� ������.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_EBONY, sti(pchar.questTemp.EbonyQty)-sti(pchar.questTemp.EbonyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.EbonyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.EbonyQty > 0))
                    {
                        tempStr = tempStr + " � �������� � ��� " + pchar.questTemp.EbonyQty + " ������ ������� ������.";
                        pchar.questTemp.EbonyQtyElseNeed = sti(pchar.questTemp.EbonyQtyElseNeed) - sti(pchar.questTemp.EbonyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed"))
            {
                if (sti(pchar.questTemp.CoffeeQty) >= sti(pchar.questTemp.CoffeeQtyElseNeed))
                {
                    tempStr = tempStr + " �� ��������� ��� ������ ����.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_COFFEE, sti(pchar.questTemp.CoffeeQty)-sti(pchar.questTemp.CoffeeQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.CoffeeQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.CoffeeQty > 0))
                    {
                        tempStr = tempStr + " � �������� � ��� " + pchar.questTemp.CoffeeQty + " ������ ����.";
                        pchar.questTemp.CoffeeQtyElseNeed = sti(pchar.questTemp.CoffeeQtyElseNeed) - sti(pchar.questTemp.CoffeeQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty) >= sti(pchar.questTemp.MahoganyQtyElseNeed))
                {
                    tempStr = tempStr + " �� ��������� ��� ������ �������� ������.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_MAHOGANY, sti(pchar.questTemp.MahoganyQty)-sti(pchar.questTemp.MahoganyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.MahoganyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.MahoganyQty > 0))
                    {
                        tempStr = tempStr + " � �������� � ��� " + pchar.questTemp.MahoganyQty + " ������ �������� ������.";
                        pchar.questTemp.MahoganyQtyElseNeed = sti(pchar.questTemp.MahoganyQtyElseNeed) - sti(pchar.questTemp.MahoganyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty) >= sti(pchar.questTemp.SandalQtyElseNeed))
                {
                    tempStr = tempStr + " �� ������ �������� ��� ������ �������.";
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_SANDAL, sti(pchar.questTemp.SandalQty)-sti(pchar.questTemp.SandalQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.SandalQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.SandalQty > 0))
                    {
                        tempStr = tempStr + " � �������� � ��� " + pchar.questTemp.SandalQty + " ������ �������.";
                        pchar.questTemp.SandalQtyElseNeed = sti(pchar.questTemp.SandalQtyElseNeed) - sti(pchar.questTemp.SandalQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            DeleteAttribute(pchar, "questTemp.EbonyQty");
            DeleteAttribute(pchar, "questTemp.CoffeeQty");
            DeleteAttribute(pchar, "questTemp.MahoganyQty");
            DeleteAttribute(pchar, "questTemp.SandalQty");
            dialog.text = tempStr;
            link.l1 = "����� ������, ������.";
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            tempStr = "";
            if (!CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed") && !CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (GetQuestPastDayParam("questTemp") > 60)
                {
                    dialog.text = "�� ��������� ����������� ��������, ��� ������. ������ ��� ������� � ��� ��������� � ���� �������� ������ � ������� ���� �������. ��� �� ��������� �� ������.";
                    link.l1 = "������, ������ ��������� ��������, � ���� �� ��� ���������� ������������� �������� ��� ��������� ���������...";
                    link.l1.go = "Step_2_8";
                }
                else
                {
                    dialog.text = "�� ��������� ����������� ��������. ����� ����, �� ����������� �� � ����! ���� ������� �� ������ ��������, ��� ��������� ������� ����� � ���� ����� ��� ������� �������� ������������.";
                    link.l1 = "� ���"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("","�") +" ��������� ������ � ������ ����.";
                    link.l1.go = "Step_2_11";
                }
            }
            else
            {
                dialog.text = "� ����� ��� ��������� ������� ����. ��� ����� ��� ������ �� ����� �����, �� ���������� ��������.";
                link.l1 = "������, ������, ��� ����� ���������� � ����������.";
                link.l1.go = "exit";
                AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "3");
                if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", pchar.questTemp.EbonyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", "���������");
                if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", pchar.questTemp.CoffeeQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", "���������");
                if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", pchar.questTemp.MahoganyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", "���������");
                if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", pchar.questTemp.SandalQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", "���������");
            }
        break;
        case "Step_2_8":
            dialog.text = "� �������, ������ � �� ������ ��������, ��� � �������������� ����������� ������ � ��� ������ ���������� ������ ���������� ���� ����������./n"+
                          "� ����� � ������������� ��������, ������� �������������� �� ���������� ������ �������� �������� ������ �����������.\n"+
                          "� ��� ��� �������� �� ����� 15000 �������.";
            link.l1 = "��, ���, �-�-�... �� ��� ��, ������� � �� ����...";
            link.l1.go = "Step_2_9";
        break;
        case "Step_2_9":
            dialog.text = "������ � ����� �������, �������. �������� �� ��� ����� �� �������, �������� � ���� �������� ��� ��� ��� ������.";
            link.l1 = "������, ������.";
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 15000);
            pchar.questTemp.Waiting_time = "30";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("�� �������, ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("��","���") +" �� �������� �������� - �������� �������������� �� ����� �����. ������ "+ GetSexPhrase("�� ��������","��� ���������") +", �� � ������������� ����� �� ������"+ GetSexPhrase("��","���") +".", HOLLAND, 5, 1);
        break;
        case "Step_2_10":
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "4");
            CloseQuestHeader("Hol_Line_2_TakeFoodCuracao");
			DeleteAttribute(pchar, "GenQuest.HL2_AgainDiscount");  //������ ���������� ����
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //��������������� ������ ���� � ���-��
        	pchar.GenQuest.StoreGoods.HL2_QtyPriceIsBack = true;
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_2_11":
            dialog.text = "����, ����� �������������� �� �������� ���������� ������� ��������� ���������� 75000 �������. �����������, ��� ��� - ��������� ��������������.";
            link.l1 = "���������, ������...";
            link.l1.go = "Step_2_12";
        break;
        case "Step_2_12":
            dialog.text = "��� � ���������! � ������ ����� ��� �������� ���� - ����... ��������� ���� ����� ����, ����, ���������.";
            link.l1 = "������, ������, � ����������.";
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 75000);
            pchar.questTemp.Waiting_time = "2";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//�����
			AddSimpleRumour("�� �������, ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("��","���") +" �� �������� �������� - �������� �������������� �� ����� �����. ������ "+ GetSexPhrase("�� ��������","��� ���������") +", �� ��� � ������"+ GetSexPhrase("","�") +" ��� ������!", HOLLAND, 5, 1);
        break;
        //********************** ����� �3, ������ � ������ �������� � ����� � �������� ������ ************************
        case "Step_3_1":
            dialog.text = "�������� ����� ��������� � ���������� ����� ������ � � ��������� ������, ������ � �����, � ��������� ����, ��� ����� ������ ���� �������.\n"+
                          "��� ���������� ���������� � ������ ��������, ������ � ��������� �����������. �� ������� ��������� ���� ��������� ����������, ��������� ��� � �������� ��������, �� ���������� ����� ������. ��� ���, ����� ���������� - ������ ��������.\n"+
                          "��� ��� ���������� �� ���������� ���, ��� ��������� ������� ������ ���������, �� ���������. ������ - ���������� ���� ����������� �������-����������� ���� ������ ��������� � ����� ������� ��������.";
            link.l1 = "��, ���������...";
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = "���� ������� ����������� � ���������: ��������� ��� ������ ���������, � ������ ������� � ������. ��������� ��� ����������, ��� �� ����� � ������ ��������. ����������� � ���, ��� ��� ������� ���, �� ����������. �� ������ �����, ��� ��� ���������� �����������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ��������� � ����������.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "WormEnglPlans_toMansfield";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ3");
            GiveItem2Character(pchar,"letter_1");
            QuestSetCurrentNode("Edward Mansfield", "HolLine3_WormEngPlans");
        break;
        case "Step_3_3":
            dialog.text = "������������ ������.";
            link.l1 = "����������, ����������� ������ ������. ��� ���.";
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = "����������, ��� � ��� ���� ���� ������������� � ������� ����������. �� ������ ���-���� � ���������� ������ ��������?";
            link.l1 = "���, ������. ������ ����������� ��� ������ �� �������.";
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = "�� �� ���������� � ��������. ��� �������� ���������� ������, ����� ����������� ����� � ���������� ������ ������. � ������ � ���� ������ ���������� �����. � ����� ����������� � ���.";
            link.l1 = "������, ����� ��� ���� ��� ����������� �����������������.";
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = "������ �� � ���� ���� - ������� ����� �������� �������. �� � ���, �������� �� ��� ����� �� �������, ��������, � ����� ����� ��� ��� ���������� ����.";
            link.l1 = "�������, ������.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "5");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex1", GetSexPhrase("���������","��������"));
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//�����
			AddSimpleRumour("����� �����, ��� ������� " + GetFullName(pchar) + " ��������"+ GetSexPhrase("","�") +" ����� ��������� ������� ����������, ��������� � ������� ���������...", HOLLAND, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = "�����������! ������ ��� �������� ���, ��� �����. ������� �� ��� ����� ���� ����, � ����� ������� �� ������ �������� ��� �� ������ ������ �� ������� ��������... �� ������ ����������, ���� �������������� ���������� 50000.";
            link.l1 = "�������, ������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "3";
            pchar.questTemp.GoodWormRusult = true;
            AddMoneyToCharacter(pchar, 50000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//�����
			AddSimpleRumour("����� �����, ��� ������ ������� " + GetFullName(pchar) + " �����"+ GetSexPhrase("","�") +" ������ � ������ �������� � ����� �����.", HOLLAND, 5, 1);
        break;
        //********************** ����� �4, �������� ���� ����� ************************
        case "Step_4_1":
            dialog.text = "���������� ������������� � ����� �����, �� ������ ������ ����������� ���������� ����������, ����� ������ ��������� �����, ��� ��������� ���� � �������� � ���� ����. ������������� ��� �� ������, �� ������ ��������, ��� �� ����� ������������� ������ ������ �������.";
            if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
            {
                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ��������� ����������.";
            }
            else
            {
                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������, ������� �� �������. ����� ������� - �� ���� ��� � ��� �� �������! ��������� ����������.";
            }
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.GoodWormRusult");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "1");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","�"));
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DefenceOrange_toFortOrange";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1.location = "Jamaica";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition = "DefenceOrange_FightNearJamaica";
			locations[FindLocation("Shore35")].DisableEncounters = true;
        break;
        case "Step_4_2":
            dialog.text = "���� ������! �� �� ������ �������� ������� ���������� ����������� ��������� �� ����������� ��������. ��� ����� �����, ���� � ��� ���� �������� ����������� � ��������� ������� ������ ���������� ���������.";
            link.l1 = "��� ����� ����, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +"...";
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = "�� ��� ��, ��� �� �����, � ����� ��� ����������� �� ��� ����� �� �������. ��������, ��� � ���� �������� ��� ��� �����-������ ����.";
            link.l1 = "������, ������. ����������� ���� �������� ���.";
            link.l1.go = "exit";
			//--> ����� � ������� �������
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- ����� � �������
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //��������� ������
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("�������, ��� ��� �� ������ �������� ���������� ������� ����� ����� �� ��������. �-��, ����� ����...", HOLLAND, 5, 1);
        break;
        case "Step_4_4":
            dialog.text = "�����������! � �������� ���, ��� ������ �� ������ �������� ���� � ����� ������� ��������. ���� �������������� �� ����������� ������ ���������� 100000 �����. � ���� ��, � ����� ��� ����� ��������� �����, � ���� ����� ��� ��� ������ ���������.";
            link.l1 = "������, ������. ����������� �������� � ����� ���������� �� �����, ��� ����� �����.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 100000);
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "5";
            //==> �� ������ ������ ��������� ������ ���������.
            QuestSetCurrentNode("FortOrange_Mayor", "First time");
            QuestSetCurrentNode("FortOrange_waitress", "First time");
            QuestSetCurrentNode("FortOrange_tavernkeeper", "First time");
            QuestSetCurrentNode("FortOrange_trader", "First time");
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //��������� ������
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//�����
			AddSimpleRumour("�������, ��� ��� ������ �� �������� ������� ����� ����� �� ��������. ��������� �������� ��� ���� ����������!", HOLLAND, 5, 1);
        break;
        case "Step_4_5":
            dialog.text = "���� ������! �� ������� �������� ����, � ��� �� ������� ������ ������� �� �������� ���������� ������� �����!";
            link.l1 = "��� ���, ������. ��� ���������� ����� � ���� �� �������� ���. �������...";
            link.l1.go = "Step_4_6";
        break;
        case "Step_4_6":
            dialog.text = "�-��, ��������. ���������� ������ ����� �����\n�� ��� ��, �������� �� ������ ������, � ������ ���� ��������. �� ������ ������������ �� ��, ��� ������ � ����� �������� � ���� �������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. �������.";
            link.l1.go = "exit";
			//--> ����� � ������� �������
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- ����� � �������
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //��������� ������
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "15";
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			Pchar.quest.DefenceOrange_FightInShore.over = "yes";
			Pchar.quest.DefenceOrange_FightInExitTown.over = "yes";
			//�����
			AddSimpleRumour("�������, ��� �� ���������� ���������� ������ � ����� �����, �� � �������� ��� ��������� ���� �������. �����, ����� ����...", HOLLAND, 5, 1);
        break;		
		
		//********************** ����� �5, ����������� ��� ������ � ��������� ************************
        case "Step_5_1":
            dialog.text = "��� ��� �� ���. �� ������������ ���������� �������. � ���� ����������� ������ ������� ����� � �������� � ������������ � ������� � ��� �� ��������������. ����, ��� ��� �������� �������, ����� ��������� ��������. �����������, ��� ����, ����� ������ ���� �������, �� ������ ������������ � ���, ����� ��� ������ �������� ������� ��������� � ������� � �����������.";
            link.l1 = "��� ��� �������.";
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = "����� ����������, �� ��� �������� ������. ������ �������������. � �������, ��� �� ������ ��������� ��� �� ������� 7000 ��������� ���������. ������ �������� � ���� ������������ ��������� �����.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_5_ThreeFleutes", "1");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "ThreeFleutes_toPortMan";
        break;
        case "Step_5_3":
            dialog.text = "��� ������ �������� � ���������, ����������� ����������"+ GetSexPhrase("�� ������","�� ��������") +"! ����� ��� �������� ���� ����������, � ����������� � ������� �������.";
            link.l1 = "������, ������. ���� �������, ��� � ����� �������...";
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "100";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//�����
			AddSimpleRumour("����� �����, ��� ��� �������-���������� �������� ��� �� ���������� �� ��������!", HOLLAND, 5, 1);
        break;

        case "Step_5_4":
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);     
			for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
					sld = GetCharacter(chComp);
					iShip = sti(sld.ship.type);
                    iBaseType = sti(RealShips[iShip].basetype); 
                    if (iBaseType == SHIP_FLEUT) tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food); //������� ������ � �������
                }
            }
            tempQty = tempQty / 10; //��� �� ���-��
            dialog.text = "�����������! ����� � � �� ������. ������ ������� ���, �� �������� �������������� � ����������� ��� ���������� 7000 ���������?";
            if (tempQty >= 7000)
            {
                link.l1 = "��, ������, ��� � �������.";
                link.l1.go = "Step_5_5";
            }
            else
            {
                link.l1 = "������, ����� � ������� �� �����"+ GetSexPhrase("","�") +". ����� ���� ���������� �������������� " + tempQty + " ���������";
                link.l1.go = "Step_5_8";
            }
        break;
        case "Step_5_5":
            dialog.text = "�� ��� ��, �� �� ������ ������� ����, �� � "+ GetSexPhrase("����������� ������","����������� �������") +". � ���������� ��� �� �������� ���������� ���� ����� ������� ��������. ���� ������� ���������� 60000 �����, �������� ��������. ������������ �������������� ����� �����.";
            link.l1 = "�������, ������.";
            link.l1.go = "Step_5_6";
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
        			tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food);
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = tempQty - 70000; //� ����� - 10 ��.
            AddMoneyToCharacter(pchar, 60000);
            pchar.questTemp.Waiting_time = "2";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
        break;
        case "Step_5_6":
            dialog.text = "�� ��� ��, ����� ��������� ���� � ��� ��� � ����.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ������ ��� � ����, � ����"+ GetSexPhrase("��","��") +" �������� ����� ������ ������� - ������ �������� ���� ��� ��������� �������� �� ��������� ����������.";
            link.l1.go = "Step_5_7";
        break;
        case "Step_5_7":
            dialog.text = "���� ������, ����� ������� �������! ��� ��, ������� �� ����������, "+ GetSexPhrase("���� ���","�������") +". ��������� ����...";
            link.l1 = "��, ������. �� ��� ������� ���������... �� ��� ��������� �����������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
        break;
        case "Step_5_8":
            if (tempQty > 4000)
            {
                dialog.text = "�� ��� ��, �� ������� ����, �� �� �� "+ GetSexPhrase("����������� ������","����������� �������") +". ��� �� �����, � ���������� ��� �� �������� � ����� ��������. ���� ������� ���������� 20000 �����, �������� ��������. ��� �������������� � ������.";
                link.l1 = "������, ������.";
                AddMoneyToCharacter(pchar, 20000);
				AddTitleNextRate(sti(NPChar.nation), 3);
            }
            else
            {
                dialog.text = "������ ��������, "+ GetSexPhrase("��� �������","��� �������") +"? � ��� ��������� ��������������? �� ��, � ����, �������"+ GetSexPhrase("","��") +"! ������� ��� �� ������.";
                link.l1 = "���, ������, � ������ �����"+ GetSexPhrase("��","���") +" ��������� ���� �����������! ��� ���, ��� � ���� ��������...";
            }
            link.l1.go = "Step_5_6";
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = 0;
            pchar.questTemp.Waiting_time = "7";
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
        break;
        case "Step_5_9":
            dialog.text = "��� �� ����� �������� �����������! � ������� ��� ����������� ������� � ������������ ��������. �� �� ������ ��� ���������. � �� ����� ��� ������!";
            link.l1 = "������, ������. � ��������, ���� ���� �� ����� �� ��������.";
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
        			tempStr = sld.id;
                    if (findsubstr(tempStr, "Captain_", 0) != -1)
                    {
                        RemoveCharacterCompanion(pchar, sld);
                        sld.LifeDay = 0;
                    }
                }
            }
        break;
        case "Step_5_10":
            dialog.text = "��������, �� ������� ���, ��� ������. ����� ���� � � ����� ��������� ��� �����-������ ������ ��� ���, �� �� ������...";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ������ ��� � ����, � ����"+ GetSexPhrase("��","��") +" �������� ����� ������ ������� - ������ �������� ���� ��� ��������� �������� �� ��������� ����������.";
            link.l1.go = "Step_5_11";
        break;
        case "Step_5_11":
            dialog.text = "���� ������, ���� ��� �� ������� ���������� ��������! ��� �� �����, ������� �� ����������. ��������� ����...";
            link.l1 = "��, ������. �� ��� ������� ���������. �� ��� ��������� �����������.";
            link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
			//�����
			AddSimpleRumour("�������, �� �� �������� ������� � ������ ������� ���������. ���� �������...", HOLLAND, 5, 1);
		break;
        //********************** ����� �6, ������ � ������ ������ �� ��������� ************************
        case "Step_6_1":
            dialog.text = "��������� �������� �� ��������� ���������� � ������ ��������� ������������ ������� �������� �� ������ ��� � ��������� �������. � �� ������, ������ �� �� ���-���� ������������� � ����� � ����.\n"+
                          "������ ��������, ��� ��������� �������� ������������ ����, ��� ��� ���� �� ���, ��������� �� ������ ������ ���������� �����������. �������, ��� ���������� ����������� ���� ��������.\n"+
                          "������������� � ����� ������� � ������� � ����, ��� ��� ���������� �����������. ���� ������ ����� ������������� ��� � �������� ���������, �� �������� ��� ���������� �� ���� ������� ����������.";
            link.l1 = "������, ������. � � ������������� ���������� � ����� ����������� ����.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "1");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("��","��"));
            pchar.questTemp.State = "RevengeMansfield_toMorgan";
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromStuvesant");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_6_2":
            dialog.text = "��-�-��, �����������.";
            link.l1 = "������ ������� ��� ��������� ���������������� ������. � �������"+ GetSexPhrase("","�") +", ��� ���������� ������� � ��������� ����� ����� ���������� � ������. ������ �������� ����������.";
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = "��� ������... ������ �� �������� ������ ������������� ��� � ������ ������?";
            link.l1 = "���, ��������������� � ������ ����� ����������� ���������, �� ��������� �������� �� �� ����� ���������� �������.";
            link.l1.go = "Step_6_4";
        break;
        case "Step_6_4":
            dialog.text = "��� �����. �� ��� ��, ��� ���������� - � �������! �������, ��� ��������� ����� �������, �� ��� ������� ��������� � ��������� ����� ������ ���������.";
            link.l1 = "��������� ������"+ GetSexPhrase("��","��") +" � ����, ������.";
            link.l1.go = "Step_6_5";
        break;
        case "Step_6_5":
            dialog.text = "�� ������� ����������� ������� �� ������ �������� �������������� � ������� 20000 �����. ����� ��� ����� �� ��� � ���������� ����� ��������� �����. � ���� ����� ����� ��� ��� �������.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 20000);
            CloseQuestHeader("Hol_Line_6_RevengeMansfield");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "4";
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//�����
			AddSimpleRumour("����� �����, ��� ��� ������� �������� �������� ���������������� ������ � ��������... ��� ������������.", HOLLAND, 5, 1);
        break;
        //********************** ����� �7, �������� ������ �'������� ************************
        case "Step_7_1":
            dialog.text = "� ������, ���� �� ������������� ���������, ������ ����� ������ ���� ���������� ��������� ��� ����������� �� ��������������� ������ ���.";
            link.l1 = "������, ������. � ��������� � ����������.";
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "1");
            pchar.questTemp.State = "DelivLettTortuga_toDOjeron";
            SaveCurrentQuestDateParam("questTemp");
            ChangeItemDescribe("letter_2", "itmdescr_letter_2_HolLineQ7");
            GiveItem2Character(pchar,"letter_2");
        break;
        case "Step_7_2":
            dialog.text = "�����������! � �������, ��� ��� ��� ������ �����������.";
            link.l1 = "��, �� ������ ������, ������. ���� � ���, ��� ����� �'������ ������� �������� ������ ��� ���.";
            link.l1.go = "Step_7_3";
        break;
        case "Step_7_3":
            dialog.text = "� ������ ��������? ��� � �������, ������� �� ����.";
            tempStr = "���-���... ���� � ���, ��� ��� ���� �������� � ���� ����� �� �������.";
            switch (pchar.questTemp.State.KingResult)
            {
                case "BrigNotFound":
                    tempStr = tempStr + " � ������"+ GetSexPhrase("��","����") +" �������� �� ������ �����������, �� �� ����"+ GetSexPhrase("","��") +" ������� ������.";
                break;
                case "BrigSunk":
                    tempStr = tempStr + " � ������"+ GetSexPhrase("��","���") +" �������� �� ������ ����������� � �������"+ GetSexPhrase("","�") +" ���, �� ������ ����� �� ����"+ GetSexPhrase("","��") +". ��� ��� - ��� ����������.";
                break;
                case "BrigAborded":
                    tempStr = tempStr + " � ������"+ GetSexPhrase("��","���") +" �������� �� ������ � ����"+ GetSexPhrase("","�") +" ��� �� �������. �� �������� ������������ ����� � �����"+ GetSexPhrase("","�") +", ��� ��������� �� ���� ������������ �������. �� ����� ������ �� ����� ��� �� ����, ��� ������ � ��������.";
                break;
                case "WarshipSunk":
                    tempStr = tempStr + " � ������"+ GetSexPhrase("��","���") +" �������� �� ������ � ����"+ GetSexPhrase("","�") +" ��� �� �������. �� �������� ������������ ����� � �����"+ GetSexPhrase("","�") +", ��� ��������� �� ���� ������������ �������. � ������"+ GetSexPhrase("","��") +" ������, �� ������� ��� ������� � ������� �����-��������, �� � ��� ������ ��� ��������, ������ �� �������. ��� ��� � ��������� ������ - ��� �� ��������.";
                break;
            }
            link.l1 = tempStr;
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = "���?!!!";
            link.l1 = "� ����� �������, ������...";
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = "�� ���� ���������, ��� ���������?!";
            link.l1 = "��������, ������...";
            link.l1.go = "Step_7_6";
        break;
        case "Step_7_6":
            dialog.text = "� �����, ���. � �� ����� ��� ������ � ���� �� ��� ���, ���� �� ������ � �'������� ���������� ������. � ��������, ����� ��� ������ '������' �� ����!";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. � ��� ��� ����� ��������...";
            link.l1.go = "Step_7_7";
        break;
        case "Step_7_7":
            dialog.text = "����� ���!!!";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DelivLettTortuga_WaitingNews";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            BackItemDescribe("letter_1");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " ���"+ GetSexPhrase("","�") +" ��������� ���������"+ GetSexPhrase("","�") +" �� ���������� �������-�����������...", HOLLAND, 5, 1);
        break;
        
        case "Step_7_20":
            dialog.text = "� ��� ����� ��� �����! ������ � ����� ��� �������� ����, � ���� ��� ��� ��� ������� ���. ��������, � ������� ���-���� �����������, �� ������ �� ������.";
            link.l1 = "������, ������. �������, ������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
        break;

        case "Step_7_8":
            dialog.text = "�����������! � �������, ��� ��� ��� ������ �����������.";
            link.l1 = "��, ����� ���. �� ���� ���� ����������� �� ������ - ������� ������ �� ���� ����� �� �������.";
            link.l1.go = "Step_7_9";
        break;
        case "Step_7_9":
            dialog.text = "��� ��� ��! � ���?";
            link.l1 = "��� ������ �������� � ���� �������� ������ �'�������.";
            link.l1.go = "Step_7_10";
        break;
        case "Step_7_10":
            dialog.text = "��� � ���?";
            link.l1 = "�������, ������. ��� � �������, ��� ���!";
            link.l1.go = "Step_7_11";
        break;
        case "Step_7_11":
            dialog.text = "� ����� ��� ���������� ��� �� ���� ������������� � ��������. ��������, �� ������������� ������������ ������ � ������.";
            link.l1 = "����� �'������ ��������� ��� ��������, � �������, � ��� ���� ����.";
            link.l1.go = "Step_7_12";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_7_12":
            dialog.text = "�� ��� ��, � ������������� �������� ���, ��� ������� �� ���������� ������ ���������� 150000.";
            link.l1 = "�����������, ������! � �������.";
            link.l1.go = "Step_7_13";
        break;
        case "Step_7_13":
            dialog.text = "��� ��� � ���� ����� ��������� �����. �������, ��� � ���� ����� ��� ������� ��� ������ �������!";
            link.l1 = "���������� ���� ���������� � ��� ������������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "10";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            AddMoneyToCharacter(pchar, 150000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + ", �������� ������� ��������� ����������, �����"+ GetSexPhrase("","�") +" � ������������ ��������� - �� ��"+ GetSexPhrase("��","�") +" ���������� ������ ������� ����� � �������. �� "+ GetSexPhrase("�� �����","��� �����") +" �� ������� �����������.", HOLLAND, 5, 1);
        break;
        //********************** ����� �8, ������ ��������� ��� ������ ************************
        case "Step_8_1":
            dialog.text = "�� ����� ��������� ������������. � ������� ����� ��������, �� �� ������ ��������� ����������� �������. �� ��� ��, ������������ �� ��� ����� �� �������, ��������, � ����� ��������� ��� ��� ��, ��� ����� ��� �� �����.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("��","���") +" �� ���������� ���������� ������� - ������ ������-�� ����������� ����������� ��������. ����"+ GetSexPhrase("��","���") +", �� �� ������"+ GetSexPhrase("","�") +"...", HOLLAND, 5, 1);
		break;
        case "Step_8_2":
            dialog.text = "�-�-�, ��� �� ���... �� ��� ��, ���������. �������, �� ������������ ��� ������� �������?";
            link.l1 = "����� ���, ������.";
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = "�����������. �������, � ���� ���. �� ���� ��� �� �����, ������ ���������� ������ ������. � ��� ����� ���� ������ ����� ��������� �� ���, ��������� � ���� ����� ��� ��� ����� �������.";
            link.l1 = "������ � ����� �������, ������.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "2";
			TakeItemFromCharacter(pchar, "LegransMap");
			ChangeCharacterReputation(pchar, 2);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//�����
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " ������ �� ���������� ���������� ������� - ������ ������-�� ����������� ����������� ��������. � �������, ��� �����.", HOLLAND, 5, 1);
        break;
        //********************** ����� �9, ������ �������� ��������. ************************
        case "Step_9_1":
            dialog.text = "���� �� �� ����� ������� ������� ����, �� ������ �� �����������!";
            link.l1 = "����������! ������, ��� ��� ����������...";
            link.l1.go = "Step_9_2";
        break;
        case "Step_9_2":
            dialog.text = "��, �����... ����, � ����� ��� ������������ � ������������ ������������ ����� �� ����� ������� �������� ������� ������, �� ���� ���������.";
            link.l1 = "��... �������, �������...";
            link.l1.go = "Step_9_3";
        break;
        case "Step_9_3":
            dialog.text = "� ���� ��� �����. ��������� ��� ������� ������ �������, ��������� �� �� �������, � ���� �����������, � ������ ����� ���. ������ �� ������� �������� ��� ����� ��������� 50000 �����. ��� �� �������, ��� ������ ��� �� �����?";
            link.l1 = "�������, ��.";
            link.l1.go = "Step_9_4";
        break;
        case "Step_9_4":
            dialog.text = "����� �� ����� ������ ������� - ����������� ����������.";
            link.l1 = "������, ������, ��������� ����������.";
            link.l1.go = "exit";
            pchar.questTemp.QtyShips = 4;
            pchar.questTemp.State = "TakeThreeShips_toAbordage";
            AddQuestRecord("Hol_Line_9_TakeThreeShips", "1");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_9_5":
            if (sti(pchar.questTemp.QtyShips)>1)
            {
                dialog.text = "�����������, �� ������ ��� �� ��������� ���������, ��� ����� ���������� ��� ���� ��� " + pchar.questTemp.QtyShips + " ���������. �� ������� �����, � ��� �� ��� ������� ������.";
            }
            else
            {
                dialog.text = "�����������, �� ������ ��� �� ��������� ���������, ��� ���������� ��� ���� ��� ����� ��������. �� ������� �����, � ��� �� ��� ������� ������.";
            }
            link.l1 = "������, ������, � ������ ���, ��� �����.";
            link.l1.go = "exit";
        break;
        case "Step_9_6":
            dialog.text = "�������! � ���������� ����������� ��������� ����������� ������� � ��������� �����.";
            link.l1 = "������ ����, ��������� ��������, ������?";
            link.l1.go = "Step_9_7";
        break;
        case "Step_9_7":
            dialog.text = "������ ��� ��� ���� �������� �������������� � �����������. � ������ ������ � ��������� ������������ ��������� ������������ �����. �������, ��� ������ ������� ����������� �������.";
            link.l1 = "�� ��� ��, �������� ����. �� � �� �� ��������"+ GetSexPhrase("","�") +" � ����� �������� ���������� ������������ �������� �����, � ��������� ����.";
            link.l1.go = "Step_9_8";
        break;
        case "Step_9_8":
            dialog.text = "��� �� ������ � ����?";
            link.l1 = "� �� �� �������������, ��� ��� ������� ����� ����������� �����? ��� �������������� ������ ����������� ���������, � �������.";
            link.l1.go = "Step_9_9";
        break;
        case "Step_9_9":
            dialog.text = "�� ��� ��, ���, �������. ������ ��� �� ��������, ������ �������� �� ������ ����������� ���������.";
            link.l1 = "������, ������. ������ ����������� ��� ������� ����������. � ���� ��, ���������, ���-�����, ��������� � ��������� ����� � �������.";
            link.l1.go = "Step_9_10";
        break;
        case "Step_9_10":
            dialog.text = "�������� ���� ������ �������� ������. ���������� �� �� ���, � ��� �������� � ���������. ����������, ������ ������������ �������� - �� ���� ��������.";
            link.l1 = "� ������ ��������"+ GetSexPhrase("","�") +" ���� ������...";
            link.l1.go = "Step_9_11";
        break;
        case "Step_9_11":
            dialog.text = "���� ������ ������. � ������ � ������� ��� �������� ���� ������. �� ����� ��������� ����� � ����� �� ������ ��� � ����.";
            link.l1 = "������, ������.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            CloseQuestHeader("Hol_Line_9_TakeThreeShips");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//�����
			AddSimpleRumour("�������, �� ��������� ����� ���������� �������� ��������, ��� ������ ��� �����������!", HOLLAND, 5, 1);
        break;
        //********************** ����� �10, ������� �������. ************************
        case "Step_10_1":
            dialog.text = "��� ��������, ��� � ������� �������� ������� ��������� �������. �� ����, ������ �� �� ��������� ���������... � ��� �� �������, ����� ������� ������� ������ ������� ����� ���� � ��������� �����, �� ��� � ����� �������� ����.\n"+
                          "������, �������� �����, ���� ��� ������� ������. ������ � ����� ��������� ��� ���� ������ � ������ � ����, ����� ������ ����� � ������� ��������� �������� ���������. ��� ����� ������, � ���������� ������, ��� ������.";
            link.l1 = "� ���������� ������� ���, ��� � ���� �����. �������, ���������.";
            link.l1.go = "Step_10_2";
        break;
        case "Step_10_2":
            dialog.text = "�� ��� ��, � ����������� �� ���!";
            link.l1 = "�������� ����� �����.";
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackCuracao_toBattle";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "1");
 		 AddQuestUserData("Hol_Line_10_SpaAttackCuracao", "sSex", GetSexPhrase("��","��"));
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1.location = "Curacao";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition = "SpaAttackCuracao_Battle";
        break;
        case "Step_10_3":
            dialog.text = "� ���� ������ ������ �� ����� ������ - ���� ������� � �������� ���� ��������! � �� �����, ��� ������ ��� ��� - ������� � �����, ������ ����� ��� ������� � ������� �� �������� ������ 200000 �����.";
            link.l1 = "����� ��, ������, �, ��������, � �� ���������� ������...";
            link.l1.go = "Step_10_4";
        break;
        case "Step_10_4":
            dialog.text = "������ �� ���� �������, ����� ����� ���������� ������ �������� �������� � ����������. � ��� �� ����! � ������ ��� ����� ������� ������������ �������� � ���, ����� ������� ������ �� �������. ����� ��� ����� �� ��� �� ����, �� ���� ���������, ��� ��� �� ���...";
            link.l1 = "������, ������, ���� � ��� � ��� �����.";
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 200000);
            CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "3";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//�����
			AddSimpleRumour("�� ��� ������, �������! �������� ����� ������ ��������� - ��� ������ �����������!", HOLLAND, 5, 5);
        break;
        //********************** ����� �11, �������� ������ �� ��������. ************************
        case "Step_11_1":
            dialog.text = "������������� ���������. ������, ��� �� ���������� � '������ ���������'...";
            link.l1 = "��� ��� ��������, ������?";
            link.l1.go = "Step_11_2";
        break;
        case "Step_11_2":
            dialog.text = "�� ������, ��� ������� XIV ����� ������������� ����� � �������� �� ��� ���������� ��������� ���������� - �������� � ���������. ��� ����������, ���� � �� ������ � ���������� ����������� ���������, ��� �� ����� ��������� � ��������� ������� � ����������. ������� �� �������� �������� ��������� � ���� ����� - ���������, �����������.\n"+
                          "������, ��� ������� ������� ������ ��������� ���� �������� �����, ������� ������� ����� ���������� ���������� �����. ���, ���� �������, ����������, ��� ��� ������� ��������� � ����� ������� ���������� ��������� � ��� ����� ����� �������� ������ ����� ����� ������� �� ������� �����.\n"+
                          "������� � �����, ��� ������� - �� ������������ ����������� �������, ������� ����������� ���������. � ����� ����� ��� ������.";
            link.l1 = "���� ������...";
            link.l1.go = "Step_11_3";
        break;
        case "Step_11_3":
            dialog.text = "� ����� ��� ������� ��� ���� � ���������� ��������� � ��� ������� �� ������ ����������. �� ������ ����������� ������ ������ ����� �� �����������.";
            link.l1 = "� ������� � ����� ��� ���� ����, ������. ���������� �� ����.";
            link.l1.go = "Step_11_4";
        break;
        case "Step_11_4":
            dialog.text = " ��, ������, ��� ������� ��� ������ �� ��������.";
            link.l1 = "�������� ����������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackSentMartin_toBattle";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "1");
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1.location = "SentMartin";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition = "SpaAttackSentMartin_Battle";
            SetTimerCondition("SpaAttackSentMartin_YouLate", 0, 0, 10, false);
        break;
        case "Step_11_5":
            dialog.text = "��� �����. �� ������ �� ���������, ������ �����.";
            link.l1 = "��� ����� ����...";
            link.l1.go = "Step_11_6";
        break;
        case "Step_11_6":
            dialog.text = "�� ������� ���, ��� ������, � ������� ������ �������� ���. ��, ������ �� ����! � ����� ��� ������� �� ��� � ���������� �������� ����� �����. �� ������� ������� �����, ��������� � ������� ���� �������, �������� �������, ��������� ��������. � �����, ������������� ��� ������� � �������� ���������. ��� �������, ��� �������� ������, ����� ���������� ������ ��������� ����� ����� ������������ �������� � ��������� ����.";
            link.l1 = "� ����� ����� ������ ����� ����� �����������?";
            link.l1.go = "Step_11_7";
        break;
        case "Step_11_7":
            dialog.text = "���� ��� �� ����. ��� ������� �� ����������, ������� � ������ � ��������� �����.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +", ������. ����� ����� ���� � ���.";
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
        break;
        case "Step_11_8":
            dialog.text = "�����������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", ������ �����������. � � ��� ������� �� ����������.";
            link.l1 = "���"+ GetSexPhrase("","�") +" �������, ������.";
            link.l1.go = "Step_11_9";
        break;
        case "Step_11_9":
            dialog.text = "���� ������� �� �������� ��� ������� ���������� 200000 �����. �������� ��������.";
            link.l1 = "�������, ������.";
            link.l1.go = "Step_11_10";
            AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//�����
			AddSimpleRumour("�������, �� ������ ��� ������ �� �����������! ���������� ������, �������!", HOLLAND, 5, 1);
        break;
        case "Step_11_10":
            dialog.text = "����� � ����� ��� ������� �� ��� � ���������� �������� ����� �����. �� ������� ������� �����, ��������� � ������� ���� �������, �������� �������, ��������� ��������. � �����, ������������� ��� ������� � �������� ���������. ������� ����������, � ������ ������ �������� ������, ����� ���������� ������ ��������� ����� ����� ������������ �������� � ��������� ����.";
            link.l1 = "� ����� ����� ������ ����� ����� �����������?";
            link.l1.go = "Step_11_7";
        break;
        //********************** ����� �12, ������ ����������. ************************
        case "Step_12_1":
            dialog.text = "� ���� ��� �����. ����������, �����������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +" � ��������, ����� ��������� ����� �����������!";
            link.l1.go = "Step_12_2";
        break;
        case "Step_12_2":
            dialog.text = "�� ����� ���!";
            link.l1 = "�������� ����������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "OccupyMaracaibo_toFight";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "1");
            SaveCurrentQuestDateParam("questTemp");
			characters[GetCharacterIndex("Maracaibo_Mayor")].dialog.captureNode = "HolLine12Quest_Occupy"; //�������������� ���� ����
        break;
        case "Step_12_3":
            dialog.text = "� ��� �������� ������ �� ���� ������������ � ����������. ���� �����������, ���� ������� ����� ������ �����! � �� ������ ��� ��� ����������� ���������� ����������� ���������.\n"+
                          "����, �� ������ �����������. � ���� ������ ��� ��� ��� �������. �� � �������� �������, ��� ���� ���������� �������� � ��������� ������� ����� ������ �� ������������ � ������ �� ����������.";
            link.l1 = "�������, �� ������ �� ���� ������������, ������. ����� ����������� ������� �����!";
            link.l1.go = "Step_12_4";
        break;
        case "Step_12_4":
            dialog.text = "��� ����� "+ GetSexPhrase("�������� ����� � ���������� ��������","������� ����������� � ��������� ���������") +"! � ������ � ����� ������� �� ���� 300000 ����� � �������� ����� �� ���� ��������� ������.";
            link.l1 = "�������, ������.";
            link.l1.go = "Step_12_5";
            AddMoneyToCharacter(pchar, 300000);
        break;
        case "Step_12_5":
            dialog.text = "��, ������ ������� ���, ����� � ��� �����?";
            link.l1 = "����������, ������. � ������ ���������.";
            link.l1.go = "Step_12_6";
        break;
        case "Step_12_6":
            dialog.text = "�� ��� ��, �� ���� ��� ������.";
            link.l1 = "�� ��������, ������.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			CloseQuestHeader("Hol_Line_12_OccupyMaracaibo");
			bWorldAlivePause   = false; // ����� �������
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
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
			AddSimpleRumour("�������, �������, ��� �� ������ ��������� ���������! ��� ��� ��...", HOLLAND, 5, 1);
        break;

        //********************** ����������� �������. ����� �2, �������� ������ �'�������. ************************
        case "Step_F2_1":
            dialog.text = "��-��, ��������� ���... � �� �����������, ��� ��� ������ ������ ��� ��� �������-���������� �`������?";
            link.l1 = "����������! � ���� ����� �������� �� ������ ������ ������� � ������"+ GetSexPhrase("�","��") +" �������� �������-�����������.";
            link.l1.go = "Step_F2_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_F2_2":
            dialog.text = "�� �� �� ������. ����� � �`������� ������ ��� ������? � ��� ��� �������, ��� �� �������� �� ������ ���������� �������� � ����������� ��� ������, � ���� ������ ��������! ������, ���������� "+ GetSexPhrase("���","��") +"!!!";
            link.l1 = "���������� ��, �����...";
            link.l1.go = "Step_F2_3";
        break;
        case "Step_F2_3":
			pchar.questTemp.State = "Fr2Letter_Arrest";
			for (i=1; i<=3; i++)
			{
				tempStr = "sold_hol_"+i;
				if (i==3) tempStr = "off_hol_1";
				sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, tempStr, "man", "man", 30, HOLLAND, 0, true));
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 30, 70, 60, "blade34", "pistol2", 70);
         		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorType(sld);
			}
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
			DialogExit();
        break;
 		case "Step_F2_4":
    		dialog.text =  NPCStringReactionRepeat("����������� ��� ������.",
            "�� ��� ���� �� ��� ��������...", "����� �������� ����?", "����������!", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("����� �������-����������, ��������� ��� ����� ��������, ���� ������� ��������� ������, ������� �������� ��� ������� ��������.", "��, �����...", "���, ��������...", "������...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_F2_5", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
        case "Step_F2_5":
            dialog.text = "��� ���. �� �, ����������, ���?";
            link.l1 = "��� ������� ��������� �������� � ������ � �� �� ������ ����� �� ������, ������� � �������� �� ����������� ����. ����� ��������� ��������� ��������� ������.";
            link.l1.go = "Step_F2_6";
        break;
        case "Step_F2_6":
            dialog.text = "� ��� ���� ������?";
            link.l1 = "�� ��� ���� ���������� ������. � ����"+ GetSexPhrase("","�") +" ��� �� ������� � �������"+ GetSexPhrase("","�") +" �������. ������� ����� ������� ��� ���� ��������, ��� ��� �������� ���� �� ����� - ���� ��� ����� ������, �� �������� ��� �����.";
            link.l1.go = "Step_F2_7";
        break;
        case "Step_F2_7":
            dialog.text = "�� ��� � ���� ������� - ��� ������ �����������! �� ������� ������ �������� ������. ����������, � �����, ��� ��� ���� ��� ���������� ��������...";
            link.l1 = "� ��� �����"+ GetSexPhrase("","�") +", �����, ������� � ����������"+ GetSexPhrase("","�") +" ������. ����������� �� �������� �� ����������� ����.";
            link.l1.go = "Step_F2_8";
        break;
        case "Step_F2_8":
            dialog.text = "������, ��� � ��� �� �������... �� ��� ��, �������, �� ��������� �������. � ����� ��������� ��� 20000 ������� �� ����������� ��������� ������. ��� ��� �������?";
            link.l1 = "��� ��������, ������, ����� ����������. ������ ��������� ����������� - ��� ���� � �������� ����. ��������.";
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("Fra_Line_2_DelivLetter", "6");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("","�"));
        break;
		// --------------------- ������� ���, ������ � ������ ---------------------
		case "TizerFind":
			dialog.text = "���� � ���� ����� ��������, ��, ��� ��������, ������ ���, �������.";
			link.l1 = "���� ���������� ����� ���, ������.";
			link.l1.go = "TizerFind_1";
		break;
		case "TizerFind_1":
			dialog.text = "����� �������, ��� ��� ���������� ����� �������, ��������� � ������ ���!";
			link.l1 = "���������?";
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = "������ ���! �� ������� � ����� �� ��� ����� ���� ����������� ����������� � ������ �� �������. ������, �������, �� ������� ��� ����������, ��� �������� ��������, � ��� ���� ����� ��� ������ ��� � �������...";
			link.l1 = "���� ������, ����� ���������� ������!";
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = "�� ���� ������ �����������! � ������ ��� �� ������������� �������������?";
			link.l1 = "������, ���� ��� � ���, ���... � �����, � ��� ��������"+ GetSexPhrase("��","���") +" ��������������� �������� ��������� ����������. ����, ������ ��, �� ����������� � ������ ���� �������� ����� � ����� ������������ � �����. ��� ���-�... � ����� - ����� ���������� ������!";
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = "�� ���, �������� �� ���� ��������?";
			link.l1 = "���������. ��� �������� ������ �� ������� ������ ������ � ��� ������, ������� ����� ����������� ��������. ����� ���������, ������ ��... �, �������, �������, ��� ��� ��� �����, �� ����� �������������! ��������� �������� ��� �����.";
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = "��, � ������� ��������������. ��� ����� �����, ����� �����, ����� ��������� ����������� �������� ������... �-��, ����� ���������. �� �� ���, �������, � ����� �� ������ ����� ������������!";
			link.l1 = "������, �� ��� ������� ��� ��� �� ������.";
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = "�������. �� ��� �, � ��� �� ��� ��� ������ ������������ ������ ����, �� � �� ���� ��� ��. � �� ���� �� ��������� �������������. ���� � ���, ��� ���� ������� �� ��� ������� ������������ �������, � � �������� ��� ��������� � ���� ������������ ����. �������, ��� �� ���� � �������.";
			link.l1 = "��������... � � ��� �����"+ GetSexPhrase("","�") +", ��� �� �� ������ ����.";
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = "� ��� ������, ��� �� ���� �� ��������� �������. � ��������� ��� ������� ������� ��� ����, ��� ��������� ������� ������� ����. �������� ���, �� ����� ���� ��������� ������ ��������.";
			link.l1 = "�� ��� ��, � ����� �������� �� ����� �������. ������� ���!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toLicencer";
			AddQuestRecord("ISS_PoorsMurder", "9");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("","�"));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
