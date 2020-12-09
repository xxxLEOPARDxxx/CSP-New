// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;     
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������, "+ GetSexPhrase("������� �������","���� ����") +"?", "���� �� ������, "+ GetSexPhrase("���������","��������") +"? �� ���� ����� ���."), "����� �������?", "��-��, ������ ��� �� ��� ���� � �� �� - �������...",
                          ""+ GetSexPhrase("��, ����� �� �������� �����-������ �������� ����? � �� � ���� ��� ������������ � ��������� ���� ������ ������������ ������...","��, ����� �� �������� �����-������ �������� ����? ��������� �� ������, ��-��...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������...", "��, �� ������..."), "�� ����... ��� ��������...",
                      "�� ��, ������������� � ������ ���... ������.", "�� ������... � ������ ���...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> ����. �3, ������ � ������ ����������.
            if (pchar.questTemp.State == "WormEnglPlans_WormPicarder")
            {
                link.l1 = "��������, ����� ���������� ��� � ���� � ���������?";
                link.l1.go = "Step_H3_1";
			}
            // ==> ����� ����.
            if (CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = "��� ��� ������, "+ GetSexPhrase("���","����") +"?";
    			Link.l1 = "���� ������� � ��� ����. �� ������ ���...";
    			Link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy" && !CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = NPCStringReactionRepeat("��� ��� ������, "+ GetSexPhrase("���","����") +"?", "����� ��?", "����� �� ����� �� �������?", "�� ��� ���?", "block", 0, npchar, Dialog.CurrentNode);
    			Link.l1 = HeroStringReactionRepeat("��������, ��� ������ ����� ����� ����!", "��, ����� �! ��� ����� ����.", "����� �� ����� �� �������.", "�� �� �����. ��� ����� ����.", npchar, Dialog.CurrentNode);
    			Link.l1.go = DialogGoNodeRepeat("Step_15", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
            if (pchar.questTemp.Azzy == "DestrContract")
            {
                dialog.text = "�-�-�, ���� � ����?!";
    			Link.l1 = "����, ���������. �� �� ���� ��� � ������ � ���������� ������������.";
    			Link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Azzy == "2DestrContract")
            {
                dialog.text = "����� ��?";
    			Link.l1 = "����� �. ��� ������ ������ ����?";
    			Link.l1.go = "Step_20";
            }
			//��������� ��������� �����
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = "��������, " + npchar.name + ", � ��� �����. �� �� ������, ��� ��?";
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
            // <== ��������� ���� ��������� �������.
		break;
		//==>����������� �������, ����� �3.
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("������ ���, �� ����� ������� �����.", ""+ GetSexPhrase("���������","��������") +", �� "+ GetSexPhrase("���������","����������") +" ��� ���� � �����", "����� � �����?", "��������, "+ GetSexPhrase("����� ���","����� ���") +", ������ ��� ���������� � �����. ���������, ����������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ������ �� ������?", "��, �����...", "��, �����...", "��� �����������, ��, � ���������, �� ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = ""+ GetSexPhrase("����� ���","����� ���") +", ��� �� �� �����?! �� ���� ��� ��� � ������� ��� �����������, ����� �� �� ��������� � ����. � ������ ���� ����� ����� �����, ���� �� ����� ������������� � � ���������� ������ �����. ��� ���, ���� ������ ��� �������, �� ������ �������.";
			link.l1 = "�������, �� �, �������, ������.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Brothel = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "11");
        break;
		//==> ����� ����
        case "Step_1":
			dialog.text = "��������, ��� ���������... �������� ���� ���.";
			Link.l1 = "���� ����� " + GetFullName(pchar) + ".";
			Link.l1.go = "Step_2";
		break;
        case "Step_2":
			dialog.text = "� ����� ����, "+ GetSexPhrase("���������","��������") +". ���� ���� �������� � ���, ��� � ������ ���-��� ������� ��� ����.";
			Link.l1 = "��, �����. ���� �� ����, ��� ��������� ��� '���-���'...";
			Link.l1.go = "Step_3";
		break;
        case "Step_3":
			dialog.text = "� ������ ����� ��������������? �� �� ������, ��� �. ������, � ��� ����� ����.";
			Link.l1 = "���� ������, ��� �� ������!";
			Link.l1.go = "Step_4";
		break;
        case "Step_4":
			dialog.text = "� �������� ��������, ���� ����������... � �� ��� ���� �����������, ��� �� ��� ������� � ����?";
			Link.l1 = ""+ GetSexPhrase("��������","��������") +" ������...";
			Link.l1.go = "Step_5";
		break;
        case "Step_5":
			dialog.text = "�-�-�, �������... � �� ������, ��� �� ��������� ������� � ����� ��������. � �� ���, ��������� "+ GetSexPhrase("�����������","������������") +".\n"+
                     "����� ��������� � ����, "+ GetSexPhrase("���������","��������") +". ���� ������, ��� � ������ ��������� ���� ���� ��� ������������ �����. ���� �� ������?";
			Link.l1 = ""+ GetSexPhrase("��, ������, ��� ������ � �� ���� � ������� ��������� �� ��������... �� ������� ������� ��������?","��, � ���� �������... �����, � ��� ����� ������!") +"";
			Link.l1.go = "Step_6";
		break;
        case "Step_6":
			dialog.text = ""+ GetSexPhrase("���� � �� ������, �� ��� �� ���������. ���� � ����� ������� �� �������� ����, ����� ���� ��� ����","������� - ��� �� ��������") +".\n"+
                     "� ����� ���, ����� ������ � �� ����. � ���� ������� ���� �������, ������, �������� ���� ����������, �������, ������������ ��� ���������.\n"+
                     "��� ��� ������ � �������� ���� ����?";
			Link.l1 = "����� � "+ GetSexPhrase("���","����") +" �������, ������, �������������, �������������, ����� - � �����, ���� ����� ����.";
			Link.l1.go = "Step_7";
		break;
        case "Step_7":
			dialog.text = "���� ����� �� ���������.";
			Link.l1 = "��� ��� �� ���������?! "+ GetSexPhrase("���� ����, ��� ������� ������� ������ �� ��������, ����� �� �������, ��� ��� � ����������! ���� ������...","���� ������...") +"";
			Link.l1.go = "Step_8";
		break;
        case "Step_8":
			dialog.text = "������ ���� �����������, "+ GetSexPhrase("������ �������","��������") +"! ��� ����, ����� ������� ���� �������, ��� ����� ��������� � ������ ���� ����� ������� �����.\n"+
                     "��� ����, ����� ������� ���� ������, ��� ����� ������� ���� ��������� �� ����� ����������.\n"+
                     "��� ����, ����� ������� ���� ����������, ��� ����� �������� ���� ������ �� ������, ����� �������.\n"+
                     "� ��� ����� �� ������� ������. ���� ��� ������� �����, �� �������� ������ ������ ������ �� �����. ����������� �������� ����� - ��� ��� ��� �������� ��������� ��������� ������������� ����, ����������� �������� �� ��������� ������� �������� � ������. �� ����, ���� ���������.\n"+
                     "������� �� ����, ������� ���-������ ����. ���� � ������...";
			Link.l1 = "�������, ������ � "+ GetSexPhrase("������","������") +" �������?";
			Link.l1.go = "Step_9";
		break;
        case "Step_9":
			dialog.text = "�����. ������, ����� �������������� ������ ���� ��������?";
            Link.l1 = "����";
			Link.l1.go = "Strength";
            Link.l2 = "����������";
			Link.l2.go = "Perception";
            Link.l3 = "�������";
			Link.l3.go = "Agility";
            Link.l4 = "���������";
			Link.l4.go = "Charisma";
            Link.l5 = "�����������";
			Link.l5.go = "Intellect";
			Link.l6 = "������������";
			Link.l6.go = "Endurance";
            Link.l7 = "�����";
			Link.l7.go = "Luck";
		break;
        case "Strength":
			dialog.text =  "����, ������� �����. �� ��� �, ������� ����� - � ����� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
		break;
        case "Perception":
			dialog.text =  "����������, ����� ������. �� ��� �, ������� ����� ������ ������ - � ����� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_P, 1);
			}
		break;
        case "Endurance":
			dialog.text =  "�������������, ������. �� ��� �, ������� ������������ ������ - � ����� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
		break;
        case "Charisma":
			dialog.text =  "�������? ��, ������� �����, "+ GetSexPhrase("���������","��������") +"! �� ��� �, ������� ����������� �������� � "+ GetSexPhrase("�������������","������������") +" ������� ���� - � ����� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_C, 1);
			}
		break;
        case "Intellect":
			dialog.text =  "���������, ������� �����. �� ��� �, ������� ����� ������� ����� - � ����� ������. �� �����, ���� ������ ��������� ��� ����. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_I, 1);
			}
		break;
        case "Agility":
			dialog.text =  "��������, ������. �� ��� �, ������� ����� ��������������� ������ - � ����� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
		break;
        case "Luck":
			dialog.text =  "������ ���� "+ GetSexPhrase("���������, �����","���������, �������") +"? � ���������. �� ��� �, ������� ��� ����� - �����, ������, ���������, �����, ��� - � ����� ���. ������ �� � ���������� ����������������, �� ����� ���� ������. �������, ����������� ��� ������, ���������� ����� ������.";
			Link.l1 = "���������� � ����?";
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_L, 1);
			}
		break;
        case "Step_10":
			dialog.text =  "��� � ����? � ��������, "+ GetSexPhrase("���������","��������") +". ������ ���� �����! ��-��-��!!";
			Link.l1 = "���-�� ��� ��� ��� �� ��������...";
			Link.l1.go = "Step_11";
		break;
        case "Step_11":
			dialog.text =  "�� �� �� �����, ���� �� �����. ��� ���, ���������� ���� ������ ������, ��������� ���������...";
			Link.l1 = "� ���, � �� ���� ��� � ��������� "+ GetSexPhrase("������","������") +"?!";
			Link.l1.go = "Step_12";
		break;
        case "Step_12":
			dialog.text =  ""+ GetSexPhrase("���� �� ������ ����������","���� �� ������� ����������") +". �������� ����� �� ��� ���� "+ GetSexPhrase("��������","���������") +", � ����� ����� �������.";
			Link.l1 = "������, ������, � ������ � ������ �� �����! ��� ��� �� ���������� � ����������. � �������� � �� ���� ��������, ���� ��������� ����� - �� ����� ���� ��������!";
			Link.l1.go = "Step_13";
		break;
        case "Step_13":
			dialog.text =  "�� �����, ������� ��� ��� ��������, ��-��-��! ���, ����� ������. �������� ����� ����� ��� ��� - ����� ���� ����� ��������. � ���� � ����, ��� ������ � ����� ���� �� ����.";
			Link.l1 = "��, ��� ���� �� ���������! ����� ���� ������. � ���������� ��� �� ����...";
			Link.l1.go = "exit";
			AddDialogExitQuest("Azzy_PlusSkill");
		break;
        case "NotPosblAdd":
			dialog.text =  "����� ���������, ��� �� ������... ���, "+ GetSexPhrase("���������","��������") +", ��������� ������ � ���� ���. ������, ��������� ������ ����������, �� � ���� ���� ���������� �� ��, ��� ����... ������� ���-������ ������.";
			Link.l1 = "��, � "+ GetSexPhrase("�������","��������") +"... ��� ���, ���� ����� �������� ��� �������?";
			Link.l1.go = "Step_9";
		break;
        case "Step_15":
			dialog.text =  "� �� ����, � ��� �� ��������.";
			Link.l1 = "������ ���������� ���� ����! ��� ����� ����. ��� � ���� ����� ���?";
			Link.l1.go = "Step_16";
		break;
        case "Step_16":
			dialog.text =  "�� ������� �� ���� �����, "+ GetSexPhrase("������","��������") +"! ���� ������ �����, ����� � ����� ��� ������� ������ � ������������ ����. � ����� �� ���� ��� ������.";
			Link.l1 = "������� ������!";
			Link.l1.go = "exit";
		break;
        case "Step_17":
			dialog.text =  "��������� ���������.";
			Link.l1 = "� ��������� ���� ������� ���� � ������� ���� ����������� ������� ���������.";
			Link.l1.go = "Step_18";
		break;
        case "Step_18":
			dialog.text =  "��, � ������� �� ���� �������. ������������ ���������� ��� ����������� ��������. �� ��� ������ ������ ����� ��� ���� ������� - �������� ����.";
			Link.l1 = "�� ���� � ����. ��� �� ������ �������� ������?";
			Link.l1.go = "Step_19";
		break;
        case "Step_19":
			dialog.text =  "� ���� ������� ���, ���� � ���� ���� ��� ��������. �� ������ �������� ��� � ����� ������� ���� � �������� ����� �� ������.  � ���, ������ �� �����, ����� �� ������� �� �� ����. ��� ����� � ��������� ��������...";
			Link.l1 = "�� ������ ���� �� ����������, � ���� ���� ��� �������� �� ������� ���� � ������ ��� ������. � �������� � �������� ����.";
			Link.l1.go = "Step_20";
		break;
        case "Step_20":
			dialog.text =  "� ������ �������� ������. �������� � ����?";
            if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
            {
    			Link.l1 = "��, ��� � ����. ��������� ����� ������!";
    			Link.l1.go = "Step_22";
            }
            else
            {
    			Link.l1 = "���, � ���.";
    			Link.l1.go = "Step_21";
            }
		break;
        case "Step_21":
			dialog.text =  "������� - �������, ��� �������.";
			Link.l1 = ""+ GetSexPhrase("�����","������") +", ���� ������.";
			Link.l1.go = "exit";
			pchar.questTemp.Azzy = "2DestrContract";
		break;
        case "Step_22":
			dialog.text =  "����, ������! ��-��-�� (������ ����������)";
			Link.l1 = "��, �� � ������� �� ����...";
			Link.l1.go = "Step_23";
		break;
        case "Step_23":
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            pchar.questTemp.Azzy = "3DestrContract";
            DeleteAttribute(pchar, "questTemp.Azzy.Oliver")
            ChangeCharacterAddressGroup(characterFromId("Azzy"), pchar.location, "goto", "goto2");
            DoQuestCheckDelay("Azzy_IsFree", 2.0);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
		// ������� ����, ������ ��������� ���������
		case "SharpPearl_1":
			if (drand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//�������� ������� � �����
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //���� ���� �����
					dialog.text = "��������� ��� ��������, ������� ���� ���������� � " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = "���! ��������� ����, " + npchar.name + ". �� ��� ������� �������!";
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //� ������� ������ �� ��������
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Dat"));
					}
					//��������� ��������� ����� �� �����
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = "���� '����������'";
					string sColony= SelectAnyColony(npchar.city); //�������, ������ ������ ����
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City))+3; //���� ������� ���� � �������
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo("���������� ���������� �� " + sColony + "  � " + pchar.questTemp.Sharp.City);
				}
				else
				{	//����, ���� �����, � �������!
					dialog.text = "����. �� � ���� � ��������� ��������. ���� �������, ���� �� ���� ������ �����.";
					link.l1 = "������, ���������, " + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = "�� ����, � ���� ��� ����� ��� �� ����.";
				link.l1 = "�������... �� ��� ��, ������� ����, " + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = "����������-�-��! ����� �� ���, �������, ���� ��� ����������!";
			link.l1 = "���, � ���� � ��� � ������, ��� � �������...";
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //������� ����� ��� ����. ����
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //���� �� �������
			pchar.questTemp.Sharp.price.evil = rand(1); //������ ��� ����, ��� ������
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

