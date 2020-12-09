// ����� ������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	float locx, locy, locz;
	string sTemp;
	int iTemp;
// ============================================================================
// ============================= ���� angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //������� ������� ������������
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //���� ����������� ������� �����. � npchar.angry.name ������� �������!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= ���� angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            dialog.text = NPCStringReactionRepeat("� ��� �� ��� ����? ���? ����� �������� ��� ���������� ����������!",
                         "�, �������, ���� ���������.", "���� � ��������� ����, �� �� ����������� ��������� ����!",
                         "��-�-��, ��� ��� ������ �� ��������, ���� ��� �������.", "repeat", 20, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� �����.",
                                               "��, ������, ���������� ����.",
                                               "������, ������...",
                                               "��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "������, ��������, �� ������ �� ������ ��� ��������� �������� � ����? �������, ��� � ��� ����������.";
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ��� ���� ������! ����� ���������"+ GetSexPhrase("","�") +" �� ���� ���?",
                         "�� ��� ���� ���?", "����� ��� ����� ������������? ���� ���� ������ ������, �� �������� ������!",
                         "�� "+ GetSexPhrase("������� �����","������� �������") +", ������� ���� ����. �� �������� � ������������� � ����� � ������ �� �����.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��, ����������, ������ ��� ��������"+ GetSexPhrase("","�") +", ���������. ������ �� ���� ���.",
                                               "������, ������ ���...",
                                               "������, ������, ������...",
                                               "��� ���� ������, �������"+ GetSexPhrase("��","���") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "������, ��������, �� ������ �� ������ ��� ��������� �������� � ����? �������, ��� � ��� ����������.";
				link.l1.go = "SharpPearl_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q4" && GetQuestPastDayParam("questTemp.piratesLine") > 5 && pchar.questTemp.Sharp != "toPearl")
			{
				link.l1 = "������, �����, ���� ��� ���� ���������� ������?";
				link.l1.go = "PL_Q4_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q8" && GetQuestPastDayParam("questTemp.piratesLine") > 30)
			{
				link.l1 = "�����, � ����"+ GetSexPhrase("��","��") +", ��� �� � ��������������.";
				link.l1.go = "PL_Q8_1";
			}
		break;

		//********************* ������� ���� *********************
		case "SharpPearl_1":
			dialog.text = "���, ����������, ��� �����. ������ ������� � ��� - �����... ����� �����, �� � ��� ���������� �� �������, ��-��...";
			link.l1 = "� �� �� ������, ��� ��� ����� �����?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "������� �� ����. � ������ ���� ������ ������ ���� ������ ����� ��������� � ��������. ��� � ���...";
			link.l1 = "�������... �������, ������.";
			link.l1.go = "exit";
		break;
		//********************* ���������� ������� *********************
 		case "EngLine_quests":
			dialog.text = "� ��� �� ��� ����?";
			link.l1 = "���, �������-���������� ������, ��� ����� �������� ��������� � ����� ������.";
			link.l1.go = "Step_1_1";
  		break;

 		case "Step_1_1":
			dialog.text = "� ��� ��?";
			link.l1 = "� ��� ��������"+ GetSexPhrase("�","��") +".";
			link.l1.go = "Step_1_2";
  		break;
  		
 		case "Step_1_2":
			dialog.text = "��, ������. � ��� �� � ���� ������ ���� ������ ���������?";
			link.l1 = "�� ������ ������� �� ����������� ����� �������.";
			link.l1.go = "Step_1_3";
  		break;
  		
 		case "Step_1_3":
			dialog.text = "�� �����, ��� ��� �������� � ������ ������. � �� ���� ������ ���������� ��� ��� ����� ��������. ��������� ��� ���������.";
			link.l1 = "��� ����� �������� ������������ �� ��� � ���� ����.";
			link.l1.go = "Step_1_4";
  		break;
  		
 		case "Step_1_4":
			dialog.text = "��� �������, � ���� ���������, ��� �� ���� �������� ������ ������ ��������. ������ ���� �� ������� ���� ��������� ����� � ���� ���� �� ������, ��, ��������, � ����� ���������� ����� ��� ������� ����. ���� ��� ���������� �������. � ���� ����� ��������.";
			link.l1 = "� ������� ���� �����. �����, ��� ����� � ��� ����������, ��� ������ � ����������. ����� ����������.";
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_2_Talking", "2");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("","�"));	
			AddQuestRecord("Eng_Line_3_Morgan", "1");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("","�"));

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "hot_business":            // ������ ������� �� �������� ������ ����.�������
			dialog.text = "���, ���"+ GetSexPhrase("��","��") +"-���� ����� ���������?";
			link.l1 = "������ ����, �����. � ����"+ GetSexPhrase("��","��") +" ������ � '������� ���� ��� ���������� �������'. ����� ������?";
			link.l1.go = "Step_3_1";
  		break;

	 	case "Step_3_1":
            if (GetQuestPastDayParam("questTemp") < 27 && pchar.questTemp.CurQuestNumber == "3")
            {
    			dialog.text = "��-��, ����� ������ ��� ������! ����� �� ���"+ GetSexPhrase("","�") +" � ���� � ����������"+ GetSexPhrase("","�") +" ������� �� �������, � ��� ���������� ���������� � ����� ���������� � ���. �� �� �� �������.";
    			link.l1 = "������ �� �� ������ ����� �� ����?";
    			link.l1.go = "Step_3_2";
            }
            else
            {
    			dialog.text = "����� ��� ����. �� ��� �����"+ GetSexPhrase("","�") +", � ���� ����� ���� �����? ���... � ����� ���������� ���� ����� �� ������, �� �� �����"+ GetSexPhrase("��","���") +" ���-�� ��� ��� �����. �� ���������� ��� ����.";
    			link.l1 = "��, ��� ����...";
    			link.l1.go = "exit";
                AddQuestRecord("Eng_Line_3_Morgan", "8");
				AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("��","��"));
				AddQuestUserData("Eng_Line_3_Morgan", "sSex1", GetSexPhrase("","�"));
                CloseQuestHeader("Eng_Line_3_Morgan");
                NextDiag.TempNode = "First time";
                if (pchar.questTemp.CurQuestNumber == "3")
                {
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.Waiting_time = "2";
                    pchar.questTemp.CurQuestNumber = "4";
                }
            }
  		break;

	 	case "Step_3_2":
			dialog.text = "������, ��� �� �����"+ GetSexPhrase("��","���") +" �� ����� ���������� ��� ������"+ GetSexPhrase("��","��") +", ��������� ������� ��������� ��������� ���������. � � ��������� � ������� � ���� ������ ��� �����, ��� ����� ����� �� ������� � ��� �������. ��� ������ ���� �� � ����. � ���� �� �� ������ ��������� ��������� �������� ������.";
			link.l1 = "������, ��� �� �����?";
			link.l1.go = "Step_3_3";
  		break;
  		
	 	case "Step_3_3":
			dialog.text = "���� � ���, ��� �������� ��������� �����, ��� ��, ��� �������, �� �������� �� ���������� ���� � ����, �� ������ ��� � ������� ���������. ��������� - ����� �������� ��������, �� ��� �������� �������� ������� � ����������. ���� �� ������� �� �� ��������, �� ������� ������ �����, ������� ������ ��������� �����.\n"+
                          "� ���� ��, ����� �������� �������� ����� ����������, ��� ���� ������. ��� ��� �������� ��� ���� ����������� ������������ �������.";
			link.l1 = "������ ����. ���� �� ����������, ����� �������� � ����� �����. ��� �� ������� ����?";
			link.l1.go = "Step_3_4";
  		break;

	 	case "Step_3_4":
			dialog.text = "� ���� ������� �� ��������� �����. �� �����"+ GetSexPhrase("","�") +" ����������� � ������������� ��������?";
			link.l1 = "�����������! � � �����, �� ������ ���� � ������ �� ������� ���������� ��������.";
			link.l1.go = "I_want_attack";
			link.l2 = "����! ��� ��������� ��� �� ������, �� � ��������"+ GetSexPhrase("","�") +" ����������. ��������� ����� ������� ��������� ������ �������, �� � ������� �� ������� ����� ���������� �������� �� �������. �� � ���� ���.";
			link.l2.go = "Step_3_6";
  		break;

	 	case "I_want_attack":    // ���� �� ��������, � ����� � �� ����
            if (GetCompanionQuantity(pchar) == 1)   // ���������� ������� ���������� �� ������ �������.
            {
           		dialog.text = "�� ��� �, ��������� ����� - �����. ��� �������, ��� ������ ��� ������� ����� ������ � ��������� ������� ���� �� ������������ ����������. ������ ��������� � �������� � ������, ��� ������ �������.\n"+
                              "�������� ��������� ��������� ������������� � ����������. ������ ��� ����� ����������� � �������� �� ������� � � ����� ������� � ����-��-�����, ��� �� ������� ��������. ��� ������ � ���� ���. �� ��, ����� ����� �����, � ��� ���� ��������� ����.\n"+
                              "� ��� ���� ������ ������ - ���� �� ������ ���������� ���� � ���� ��������� �����, �� ����, ��� ������� ����� �������� ��������� ���� ��� ������.\n"+
                              "� ������ �� ������ ������������.";
    			link.l1 = "������!";
                link.l1.go = "Step_3_7";
            }
            else
            {
                NextDiag.TempNode = "Step_3_4";
               	dialog.text = "�� ����� ����� ����� �������! �� ���� �� ��������� ����, ��� ����� �� ������ �������� �� � ����."+
                              "��� ��� ���������� � ����� ���������� � ��������, �������� �� ������ �����������. � �� ���� � ����, ����� �� ������� ����������� � ����.";
    			link.l1 = "������ ���, ��� �����.";
    			link.l1.go = "exit";
    			link.l2 = "� ���� ��� ����������� ��� ����� �������� ���� �����. ��������"+ GetSexPhrase("","�") +" ���������� �� ������������� ����� ����.";
    			link.l2.go = "Step_3_6";
             }
  		break;

	 	case "Have_hot_bussines":    // ���� ������� ����� ��������� ��� ����������, �� ����, ������ ��. �� �� ������ ������.
			dialog.text = "���� �� ����? ����� ������, ����� ���������.";
			link.l1 = "�������, ��������� ����������.";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Step_3_6":                   // ����� �� ����������� ������� ��������� ��������� �����.
			dialog.text = "��� �, ����� ���� ������ �� �����... ��-��!\n"+
                          "������ ����������� �� ���� ������ �� ���������. ����� ��������.";
			link.l1 = "�����, ������. ������...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10); 
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
            
            AddQuestRecord("Eng_Line_3_Morgan", "2");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("��","���"));	
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";       // 2 ���, ��� ��������, ���� ���������� ��������
            pchar.questTemp.CurQuestNumber = "4";     // ���� �� ��������� �����
            NextDiag.TempNode = "First time";
  		break;

	 	case "Step_3_7":                  // �������� �� ������� � ��������� �� �����
			AddQuestRecord("Eng_Line_3_Morgan", "3");
            pchar.nation = PIRATE;
            pchar.questTemp.State = "AttackBeliz_GoOn";
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
            // ==>  ���-�� �����������. ����� ��� ������� ������ ���������� �� ����, ��� ������� ���, �.�. � ������ �����������(�� ������ ���������� ��������).
            pchar.questTemp.CompanionQuantity = "2";
            // ==>  ���� �����. ���� ��������
            characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Lets_go_bussines";
            // ==>  �������� ����� ������� � ��������� � ���� �����. ����
            characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Lets_go_bussines";
            // ==>  ������� ������ �� ����������, ���� 31 ����.
            SetTimerCondition("time_over_Beliz_attack", 0, 0, 51, false);
            SaveCurrentQuestDateParam("questTemp");
            NextDiag.TempNode = "Have_hot_bussines";
            pchar.TempPerks.QuestTroopers = true; //���� ���������� �������
            // ==> �������������� ���� ����������� ������
			characters[GetCharacterIndex("Beliz_Mayor")].dialog.captureNode = "EngLine3Quest_BelizAttack"; //�������������� ���� ����
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
  		break;

	 	case "time_over_Beliz":    // ������ �� ����� ����� ���������
			dialog.text = "���� �� ��� ��������� ���������� ���, ������ �� ������ ���� � �������, � ��� ����� ������ ����� ��� �� ���������. �� ������"+ GetSexPhrase("","�") +" ���� �����, �� ������.";
			link.l1 = "��� �, ��� ���� �����.";
			link.l1.go = "Step_3_8";
			// ����� � ������
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
        break;

        case "Step_3_8":
			LAi_SetPlayerType(pchar);
            if(IsCompanion(npchar))  {RemoveCharacterCompanion(pchar, npchar);}
            if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}

            QuestToSeaLogin_Prepare(worldMap.playerShipX, worldMap.playerShipZ, worldMap.island);
            if(worldMap.island !=	WDM_NONE_ISLAND)      // ���� ����� �������
            {
                questToSeaLoginer.FromCoast = true;
            }
            else
            {
                questToSeaLoginer.FromCoast = false;
            }
            QuestToSeaLogin_Launch();
            
            Log_SetStringToLog("������� ��������� �������� ����� �� ������� �������.");
            // ==> ���������� �� ����� �������
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(npchar);
            // ==> ���������� �� ����� ��������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                LAi_SetHuberType(characterfromID("Jackman"));
				LAi_group_MoveCharacter(characterfromID("Jackman"), "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> ���������� �� ����� ����� �������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                LAi_SetHuberType(characterfromID("John Morris"));
				LAi_group_MoveCharacter(characterfromID("John Morris"), "ENGLAND_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            AddMoneyToCharacter(pchar, -50000);
            ChangeCharacterReputation(pchar, -20); 
            // ����� ���� � ���������� � �����
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
            AddCharacterSkill(pchar, SKILL_SNEAK, 0);
            
            AddQuestRecord("Eng_Line_3_Morgan", "6");
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // ���� �� ��������� �����
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers");  //������ ����� ���������� �������
			// ����� �������� ��� ���� ������ � ������...
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
  		break;

	 	case "Gold_found_in_fort":    // ���� ��������� � ����� ������
			dialog.text = "������ �������, ��� �� � �������"+ GetSexPhrase("","�") +", � �����. �� ����������� ��� �������� � �����. �� �����"+ GetSexPhrase("��","�� �������") +" � ������ ����.";
			link.l1 = "�������.";
			link.l1.go = "Step_3_9";
        break;
        
	 	case "Step_3_9":
            if (!IsCompanion(characterFromID("Henry Morgan")))
            {
                dialog.text = "��� �, ������ ����� �������� ���� �����. � ���� � ������� ����� ���� ������������ ������, ������ ���� ���� �������. �� ������ ������ �� ��� ������ ����� ������. �� �������� � ���� ������"+ GetSexPhrase("","�") +".";
            }
            else
            {
            	dialog.text = "��� �, ������ ����� �������� ���� �����. �� ���������, ��� ������ � ������ � ������� ������. �� ������ ������ �� ��� ������ ����� ������. �� �������� � ���� ������"+ GetSexPhrase("","�") +".";
            }
			link.l1 = "����� ��������, ������.";
			link.l1.go = "Step_3_10";
        break;

	 	case "Step_3_10":
            if (GetCargoMaxSpace(pchar) >= RecalculateCargoLoad(pchar))
            {
                dialog.text = "������� ��� ������. � ��� �������: ����� ����, ������ ������, ��� �� �� ������ ���������� ���� ������-��������? ���� ���, �� � ����� ��������� � ���� ���� ���� ������.\n"+
                              "���� ���� ������ - " + pchar.Ship.Cargo.Goods.gold + " ��������. �����, ������� ����� ��� ���� ���? ������ �� 200 ����� �� ������� ����.";
            }
            else
            {
                dialog.text = "������� �������. ������, ���� ������� ������ ���� ����������. � ���� ��������, �� �� ������� ������ ���� �� �����.\n"+
                              "������������ ���������������� ������ ������� " + GetCargoMaxSpace(pchar) + " ��������, � � ������ � ���� ������ " + RecalculateCargoLoad(pchar) + " ��������\n"+
                              "������ � ���� " + pchar.Ship.Cargo.Goods.gold + " ��������. �����, ������� �����? ������ �� 200 ����� �� ������� ����.";
            }
			link.l1 = "���, ������. �� ����� ������� � ��������� ���"+ GetSexPhrase("","�") +". ������.";
			link.l1.go = "out_fort";
			link.l2 = "��� ������������� ����� ������� �������.";
			link.l2.go = "Agree_sale_gold";
			link.l3 = "��� ��������, � ���� �� �����"+ GetSexPhrase("","�") +" ��������.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Think_sale_gold":    // �� ������ � ������� ������
			dialog.text = "�� ���, �������"+ GetSexPhrase("","�") +" ������� ��� ������?";
			link.l1 = "��, ������...";
			link.l1.go = "Agree_sale_gold";
			link.l2 = "���, ������. ������ � ������ �����. ������.";
			link.l2.go = "out_fort";
			link.l3 = "������� ��� �������...";
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Agree_sale_gold":    // �� �������� ������� ������
			dialog.text = "������. ������� �� ������ ������� ������?";
			link.l1 = "�����"+ GetSexPhrase("","�") +" ������� 25 ��������� ������������� ��� ���� ������.";
			link.l1.go = "sale_gold_25_persent";
			link.l2 = "�����"+ GetSexPhrase("","�") +" ������� 50 ��������� ������������� ��� ���� ������.";
			link.l2.go = "sale_gold_50_persent";
			link.l3 = "����� �������"+ GetSexPhrase("","�") +" 75 ��������� ������������� ��� ���� ������.";
			link.l3.go = "sale_gold_75_persent";
			link.l4 = "�����"+ GetSexPhrase("","�") +" ������� ���.";
			link.l4.go = "sale_gold_all";
			link.l5 = "������ ������, � ���������"+ GetSexPhrase("","�") +"... ������.";
			link.l5.go = "out_fort";
        break;
        
	 	case "sale_gold_25_persent":
			dialog.text = "������, �� ������"+ GetSexPhrase("","�") +" �������� ����� ����. ��� �, �������� ������ ��� ��� �����. ������.";
			link.l1 = "�����, ������. ��� ��������.";
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25*200));
        break;

	 	case "sale_gold_50_persent":
			dialog.text = "����� ������, �� ������"+ GetSexPhrase("","�") +" �������� ����� ����. ��� �, �������� ������ ��� ��� �����. ������.";
			link.l1 = "�����, ������. ��� ��������.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.5));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.50*200));
        break;

	 	case "sale_gold_75_persent":
			dialog.text = "����� ������, �� ������"+ GetSexPhrase("","�") +" ��� �������� ����� ����. ��� �, �������� ������ ��� ��� �����. ������.";
			link.l1 = "�����, ������. ��� ��������.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75*200));
        break;

	 	case "sale_gold_all":
			dialog.text = "�� �������� ��� ���? �����������! �������� ������ ��� ��� �����. ������.";
			link.l1 = "�����, ������. ��� ��������.";
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*200));
        break;

	 	case "out_fort":
			pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // �����, ���� ��� �����������
	        pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";
	        pchar.quest.time_over_Beliz_attack.over = "yes";
	        		
			if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}
            AddQuestRecord("Eng_Line_3_Morgan", "7");
            RemoveCharacterCompanion(pchar, npchar);
            // ==> ���������� �� ����� �������
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberTypeNoGroup(npchar);
            // ==> ���������� �� ����� ��������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                LAi_SetHuberType(characterfromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> ���������� �� ����� ����� �������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                LAi_SetHuberType(characterfromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
               characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            ChangeCharacterReputation(pchar, 1); 
            AddCharacterExpToSkill(pchar, "Leadership", 20);
            AddCharacterExpToSkill(pchar, "Fencing", 500);
            AddCharacterExpToSkill(pchar, "Pistol", 550);
            AddCharacterExpToSkill(pchar, "Sailing", 550);
            AddCharacterExpToSkill(pchar, "Accuracy", 330);
            AddCharacterExpToSkill(pchar, "Cannons", 150);

            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // ���� �� ��������� �����
            pchar.questTemp.State = "empty";
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "questTemp.BelizGoldQty");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //������������ ������ ����� ���������� �������
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], false); //������ ������
            chrDisableReloadToLocation = false;
            pchar.nation = ENGLAND; // ������ �����
            InterfaceStates.Buttons.Save.enable = true;   // ������ ������
			DoReloadCharacterToLocation("Beliz_town",  "reload", "gate_back"); //�� � �����
            NextDiag.CurrentNode = "I_know_you_good";
			DialogExit();
        break;

	 	case "Give_blade":
			dialog.text = GetFullName(pchar) + ", � ���������� ���� �� ������� ����. ������ �������� ��� ����� ������� ��������� � ���������� ��������, ������ ���� ���������� ��������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ��������� ������ ��������� ��� � ������ � ��� �� �����"+ GetSexPhrase("��","���") +". �� ��� �� ��������� ������� � ����������� ���������.";
			link.l1.go = "Step_9_1";
        break;
        
	 	case "Step_9_1":
			dialog.text = "� ��� ������������� ���.\n"+
                          "� ������� �� ����� ���� ����� ������� �� ���� ������� - ��� ������. ����� ������ ��� ������ �� �������.";
			link.l1 = "�������, ������. ���� ������� ������ ��� �����. ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
            GiveItem2Character(pchar, "blade27");
            RemoveCharacterEquip(NPChar, BLADE_ITEM_TYPE);
            TakeItemFromCharacter(NPChar, "blade27");
            GiveItem2Character(NPChar, "blade22");
            EquipCharacterByItem(NPChar, "blade22");
        break;
		//********************* ����������� ������� *********************
        case "HolLine3_fromMansfield":
            dialog.text = "���� ������ �� ������������ ������ ��� �����?";
            link.l1 = "� ������"+ GetSexPhrase("","�") +" � ��� �� ��������� ������� ���������.";
            link.l1.go = "Step_H3_1";
        break;
 	 	case "Step_H3_1":
			dialog.text = "������ ��� ��������������� �������.";
			link.l1 = "������ ������ ��� ������� ��� ������. ��� ����� ���������� � ������ �������-����������� ���� ����� ������ ���������. ���� ����������, ���� �� � ���� ������ �� �������� ������ �������� ������ ����������� ������� � ��� ��������� �� ���������� �����������.";
			link.l1.go = "Step_H3_2";
        break;
 	 	case "Step_H3_2":
			dialog.text = "��, �� �����, �� ���� - � ������ ��� ��� � ����������?!";
			link.l1 = "��, ������ ���, ���.";
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = "�� ��� ��, ����� ������� ����� � ����. �������� ��� - ��� ���� ������, ���� ���� � ����� �� ������. �� ��� ���� ��������� � �� ������ �� �����. ������� ���� ������, ����� � ��� �����, �������� ��� ���������� ����� �� ����.";
			link.l1 = "� �������� ��������� ������ �������-����������� �������.";
			link.l1.go = "Step_H3_NoWork";
			link.l2 = "� �����"+ GetSexPhrase("","�") +" ��������� ����� ���� ���������.";
			link.l2.go = "Step_H3_4";
        break;
 	 	case "Step_H3_NoWork":
			dialog.text = "� ����� ������ ��������. ��� �� � ��� ����� ��������.";
			link.l1 = "����� ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_SurrenderWorkMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "4");
		AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("��","���"));
        break;
 	 	case "Step_H3_4":
			dialog.text = "������. ��������� ���������: �� ������� � ������ ������ ��������� ���������� �� ����� ���� ���������. �� ������ ����������� � ����� ����, � � ����������, ��� ��������� �������� ����� ������.\n"+
                          "��� ����� ��� ���������. ������������� �� ������� - ��� ��� ����� ������ �� �����, - � ����������� ������ ��� �������� ���������� � ����������.";
			link.l1 = "�����, � ����� ���� � ��� � ������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HolLine3_aboutWorm";
    		pchar.questTemp.State = "WormEnglPlans_WormPicarder";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "6");
		AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("��","���"));
        break;
 	 	case "HolLine3_aboutWorm":
			dialog.text = "��� �� ������? ��� ��� �������� ��� ������� ���� � �������� ���� ���������?";
            if (CheckAttribute(pchar, "questTemp.Talks"))
            {
    			link.l1 = "�� �������, ����� �������� ������� � ������.";
    			link.l1.go = "Step_H3_5";
            }
            else
            {
    			link.l1 = "���� ������ ������������� ��� ������ �� �������...";
    			link.l1.go = "exit";
            }
        break;
 	 	case "Step_H3_5":
            sTemp = "��� ������� ��������� ��������� �����.";
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern")) sTemp = sTemp + " ���� ��������� ���� ������� � ������� ������� �� ��� ������.";
            if (CheckAttribute(pchar, "questTemp.Talks.Store")) sTemp = sTemp + " ������� ������������� � �������� ������� ���� �� �� �����.";
            if (CheckAttribute(pchar, "questTemp.Talks.Shipyard")) sTemp = sTemp + " �������� �� ���� ������ �������� ��������� ���������.";
            if (CheckAttribute(pchar, "questTemp.Talks.Usurer")) sTemp = sTemp + " ���������� ��� � ���� ����� �����, ��� ��� ������ �� � ���� �� ��������� ������.";
            if (CheckAttribute(pchar, "questTemp.Talks.Brothel")) sTemp = sTemp + " � ������� �� ����������� � �������� �����.";
            dialog.text = "� ����� ������� � ����, ����� �� �������� ����������� ��������. �� ��� �� ��������� ������ ������?";
			link.l1 = sTemp;
			link.l1.go = "Step_H3_6";
        break;
 	 	case "Step_H3_6":
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern") && CheckAttribute(pchar, "questTemp.Talks.Store") && CheckAttribute(pchar, "questTemp.Talks.Shipyard") && CheckAttribute(pchar, "questTemp.Talks.Usurer") && CheckAttribute(pchar, "questTemp.Talks.Brothel"))
 	 	    {
    			dialog.text = "�� ��� ��, � �������, ��� ����. ����� ������ ��������� �� ���������� ����� � �� ������� � ���������� ����������� ��������� ��������. �������� ��� ����������, ��� �������� �������� ��������, ���� ���������� ����� �����... � ��������� ���.";
    			link.l1 = "��, ���"+ GetSexPhrase("","�") +", ��� ����"+ GetSexPhrase("","��") +" ������. �� � ������, ���� �� �� ����������, ������� ��������� � ���� ����, �� �������� � ���� � ������"+ GetSexPhrase("","�") +", ����������.";
    			link.l1.go = "Step_H3_10";
 	 	    }
            else
            {
                dialog.text = "�������. �� ��� ��� ������ �� ���������� �����. � ����, ��� ����� ����� � ���� ���� � �������. ��� ��� ��� �������� ��������� �� ������� � ���������� ���� ����������.";
    			link.l1 = "� �����"+ GetSexPhrase("","�") +" ���������� �����, ����� ������� ��������������� ������.";
    			link.l1.go = "Step_H3_7";
    			link.l2 = "������, ��� ��� ������� �� ������� � �������� ���������.";
    			link.l2.go = "exit";
    		}
        break;
 	 	case "Step_H3_7":
			dialog.text = "� ��� �� �����.";
			link.l1 = "������ � ����� ���������� ����.";
			link.l1.go = "Step_H3_8";
        break;
 	 	case "Step_H3_8":
			dialog.text = "�������, ����, �� �� ������� ���� ����. ������ � ���, �������.";
			link.l1 = "����� � ������ �� �����.";
			link.l1.go = "Step_H3_9";
        break;
 	 	case "Step_H3_9":
			dialog.text = "� ����� ������ ��������, ��� �� �� ������������. ���� ��������� � �� ���� ������ ������������� � ����� �������� ������� ��� ����� �����. ��������, �� ������ �������� ��������� ��������.";
			link.l1 = "��, �� ��� ��, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "12");
            DeleteAttribute(pchar, "questTemp.Talks");
        break;
 	 	case "Step_H3_10":
			dialog.text = "���� � ���, ��� � �� ����, ����� ����� � ��������� � ����� ���������� �� ������� �� ������ ������� � �����. ������ ��� ��������, ��� �������� ������� ��������� �������� ������ ��������� ���� �����.";
			link.l1 = "����� ��� ����, ��� ����� ����� �����, ��� �� ��������.";
			link.l1.go = "Step_H3_11";
        break;
 	 	case "Step_H3_11":
			dialog.text = "���� ������ ��� ������. ������ � ������ ����� ���������� ������, ��������� �� ����� ���� �������, �������� ������ ������ �������� ��������� �������. ����� �� �������� � �������� ������ ������� �� ��������� � ������ �����. ������ ��� �� ������, � �� ��������� ����, ��� ����������. � �����, ��� ������ ��� �������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +". ������� �� �����, �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "13");
            DeleteAttribute(pchar, "questTemp.Talks");
            pchar.questTemp.State = "WormEnglPlans_SaveOfficer";
            sld = GetCharacter(NPC_GenerateCharacter("Alan_MacLine", "off_eng_2", "man", "man", 10, ENGLAND, 1, false));
        	sld.name 	= "����";
        	sld.lastname = "�������";
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Alan_MacLine")], "SentJons_prison", "goto", "goto9");
        break;
        // ==> ����� �6 ���������.
 	 	case "HolLine6_fromStuvesant":
			dialog.text = "��� ������� ��� �� ��� �� ���� ���?";
			link.l1 = "� �����������"+ GetSexPhrase("","�") +" �������, ��� ���������� ����� ��������� �� ������ ������� ���c�����.";
			link.l1.go = "Step_H6_1";
        break;
 	 	case "Step_H6_1":
			dialog.text = "��� ��, ������ ��� ����������, � �������... ��� �� ���������� �����������?";
			link.l1 = "��� ���������� ����������� � ���� ������� ���� ��������.";
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = "��, �������. �� ��� ��, ������� � ������ ��� ��, ��� ���� ���. ������� ��������� ��������� �� ��������� ����������. ���������� � ���������������� ������������� ����� �������� �������-���������� �������� ���� ����� �������, ������ �� ������� � ������������ ��� ��������.";
			link.l1 = "�� ������� �� ��������?";
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = "��������. ������ ��� �� ����� ���������� - ��� ����������� ������� �� ������� �������-����������� ��������. ��������� ���� ����� ��� �����, � �� � ������� � ����� � ���������� �������� ����������. ������ ��� ������ ������ ���� ����� ��������� �� �����.";
			link.l1 = "��-�-�, � �������� ������� ��������.";
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = "���, ��� �����. ����, ���� �� ������ ����������� � ���� ����, ��� �������� �������� ���������������� ������.";
			link.l1 = "��� ��������� � ����"+ GetSexPhrase("��","��") +" �������?";
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = "�� ������ ���������� � �������� � ������, �� ����� �� �������-���������� ����� ������, �������������� ���� ����� �������. ��������� ������ ���� ��������� ������ �����, ����� �������-���������� ����� � ������. ������� ���������� ����� ��� ���������� �� ��������� �����.";
			link.l1 = "��� ����. ����� � ���� � ��� � ����������� �����������.";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "2");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("��","��"));
            pchar.questTemp.State = "RevengeMansfield_toTavern";
            NextDiag.TempNode = "I_know_you_good";
            LAi_group_MoveCharacter(characterFromID("Santiago_tavernkeeper"), "QuestGroup");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "QuestGroup");
        break;
 	 	case "HolLine6_fromSantiago":
			dialog.text = "��, ������ �������, ��� ������� ������.";
			link.l1 = "������� � ������ � ������ �� ���������� � ��������� �����. � ��� � �������� ���������� �������� ������ � ��� �������-����������� �����.";
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = "�������! �� ��� ��, �� ������"+ GetSexPhrase("","�") +" ���� ����, �������. ��� ������� ����� � ��� ������ ���� ����� �� ����������� ������ ��������� ���������.";
			link.l1 = "� ����� ���"+ GetSexPhrase("","�") +", ��� �� ������ ������ ���. ��, � ��� �� ����� ������?";
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = "��� ��� �� ���� ������, �� ���� ���� �������. �������� ����� �������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +". ������, ������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "RevengeMansfield_FromMorganWithResult";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "4");
            NextDiag.TempNode = "I_know_you_good";
        break;
		//********************* ����������� ������� *********************
        case "FraLine8_talk":
            dialog.text = "���, �� ��� ���"+ GetSexPhrase("","�") +" ������� " + GetFullName(pchar) + "! � ����� �� ����� ������������. �� ��� ��� �� �� ���"+ GetSexPhrase("","��") +" � ��� ����, � ������� ��� ���"+ GetSexPhrase("","�") +" � ������"+ GetSexPhrase("","�") +". ������, ����� ���������"+ GetSexPhrase("","�") +". �������, �� ��� �������� ����������.";
            link.l1 = "��������, ������, �� �� ������, ��� ������ ��� � �� ����"+ GetSexPhrase("","�") +" �� ���� ����������. � �� ����.";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "����������...";
            link.l1 = "��� �� ������� � ����������� �����-����������� ���������?";
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = "�� ���� � �����... �� ��� ��, ���� �������, ��� ��������� � ���� ����� ��� �� ������, ����� ����, ��� ��� ������� - �� ��� �������� ��� �������� � ���� �����. ��� ��� ���� ����� � ������ ��� �� ��������, �� � ���������� ������� �� ������ ������ �������� ����������, ������ ����������� ����� ������� �� ������� ��������.\n"+
				          "������ �������, ��� ������ ��� �������� ���������� �������� ������� �� ���� ������ ������.";
            link.l1 = "��� �����, �� �����. ���� ������, ��� �� ���������� ������������ � ����� ��������� ��������.";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "����� ������ ����� ����...";
            link.l1 = "�����, �� ���� ������ ������ �� �����. ��� �����, ����� �� �� �������� ������� � ��������� �� ����������. ���� �������, ���� ������ ��� ����, ��� ����� ��� ���� �� ���������...";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = "��, ����� ���� �������� - ��� ����� ��� ���������, �� � �� �� ������, ��� ��� ��� �� ���������. ���� � ���, ��� ��� ������ ������� ��� �������� � �������� ��������� �������, � ������� ��� � ��� ����� �� ����. �������, ���, ��� ������� ���� � ���������� ���������� ����, ��������� ������������ ����� �������?";
            link.l1 = "���, �� ��� ��� ���� �� �����. �� ��� ��� ������. ������� ����������� ����� �����������, ����� ���������� �� ������ � �� ����������� � ������� ��������?";
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = "�� �������� �� ���� ������ ���, � 250 �����, � �����, �� ����-������ ������ ������.";
            link.l1 = "� �������"+ GetSexPhrase("","�") +" ���������� ���� ������ �� ����������� �� ����������.";
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = "250 ����� �� ����� - � � ��� � ����������� ����� ���������.";
			if (sti(pchar.money) >= 250000)
			{
				link.l1 = "��, ������� �� ���� ������ ��� ��������! ���� ������ � �����: ��� ������ �����.";
				link.l1.go = "Step_F8_7";
				AddMoneyToCharacter(pchar, -250000);
			}
			else
			{
				link.l1 = "������ � ���� ��� ����� �����, �� � ����������� �� ����� � ����� ����. ��� ��� ������� ����-����.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_F8_6";
			}
        break;
        case "Step_F8_7":
            dialog.text = "� ����� ��� ��� ��� ���������� � �����? �� ������, �� �� �������������...";
            link.l1 = "������, �����, �� �����"+ GetSexPhrase("","�") +" ���� �������. ��, ������ � ���� ������.";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "4");
        break;
		//********************* ��������� ������� *********************
		//����� �1, ������ � ������
		case "PL_Q1_1":
			dialog.text = "��-�-�, "+ GetSexPhrase("������","������") +", �����"+ GetSexPhrase("","�") +" �� � ��������. ������� - �������������� �� ����"+ GetSexPhrase("","�") +".\n������, ��� � ���� ����� � ���� ����� ������, � ��������� ��� ����� � ���� �������. ��� ��� ������ � ����� ������������ ��� �����.";
			link.l1 = "� ��� �� ���� ������? � �� � ���� ��� ���"+ GetSexPhrase("","��") +".";
			link.l1.go = "PL_Q1_2";
		break;
		case "PL_Q1_2":
			dialog.text = "��� � ���� ��������... �����. ���-�� ������� ���� ����������, � � ����� ��� ���.\n������ � ����. � ���� ����� ���� ���������, ����� ������������ - ������ �� �����, ��� ����� ����� ���������� "+ GetSexPhrase("������","�������") +". ������� ���� ���� � ������� � ������� �� ���.";
			link.l1 = "������, ������ ���� � ���� ��� ���������� �������. �, ������, ����� ������, ��� �� �� ���� ������������.";
			link.l1.go = "PL_Q1_3";
		break;
		case "PL_Q1_3":
			dialog.text = "�� ����, ���� �� �����. �����... "+ GetSexPhrase("� ����, � ���� ����� �������� �������. ��� ��� �� ����� ������� �����.","") +"";;
			link.l1 = ""+ GetSexPhrase("������, ���� ����� � ����","C������") +"."
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_1";
			AddMoneyToCharacter(PChar, 10000);
			AddDialogExitQuestFunction("PiratesLine_q1_MorganEnd");
		break;
		//����� �2, ������ � ���������� ���� �����.
		case "PL_Q2_1":
			CloseQuestHeader("Pir_Line_1_JohnBolton");
			dialog.text = "�-�-�, ����"+ GetSexPhrase("��","��") +". ��� ������. ���-��� � ��� ������� �� �������.\n������ ���� ����� ����������� �� ���������. ��� ����� ���� ����������, ����� ��� ������ ���. ��� ��� ��������, ����� �� ���� ������ �����.";
			link.l1 = "�� ������ ���-������ ��������?";
			link.l1.go = "PL_Q2_2";
		break;
		case "PL_Q2_2":
			dialog.text = "���, �� ����� ����� ���� �����, ����� �� ����� ������ �����?! ������ ����� ��� ����������.\n�� ������� ��� �� �����, ����� ������������. ��� ���� ���� ��� ������, ����� ����� �����. ��, ����� ��-����, ����� ��� ������ �� ���, ���� ���� �����. ���, ���, �� ����������� ���� ����� ����� �������.";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ��� � ������.";
			link.l1.go = "exit";
			sld = GetCharacter(NPC_GenerateCharacter("EdwardLoy", "officer_10", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade25", "pistol3", 100);
			FantomMakeCoolSailor(sld, SHIP_BRIGSW, "������� ����", CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			sld.name = "������";
			sld.lastname = "���";
			sld.rank = 30;
			sld.city = "LeFransua";
			sld.location	= "LeFransua_House4";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "EdwardLoy";
			sld.greeting = "Gr_EvilPirate";
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
			LAi_SetWarriorType(sld);
			GiveItem2Character(pchar, "BlackLabel");
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			pchar.questTemp.piratesLine = "BlackLabel_toLaVega";
            SetQuestHeader("Pir_Line_2_BlackLabel");
            AddQuestRecord("Pir_Line_2_BlackLabel", "1");
			NextDiag.TempNode = "PL_Q2_wait";
		break;
		case "PL_Q2_wait":
			dialog.text = "������"+ GetSexPhrase("","�") +" �����?";
			link.l1 = "��� ���, ������, ��������� ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_wait";
		break;

		case "PL_Q2_away_1":
			dialog.text = "�-�, " + GetFullName(PChar) + ", ����������� ����. ��, �����������, ���"+ GetSexPhrase("","�") +" �� ���������? ��� ���"+ GetSexPhrase("��","��") +"?";
			link.l1 = "���"+ GetSexPhrase("","�") +", ����� �������"+ GetSexPhrase("","�") +".";
			link.l1.go = "PL_Q2_away_2";
			CloseQuestHeader("Pir_Line_2_BlackLabel");
		break;
		case "PL_Q2_away_2":
			dialog.text = "� ��� ��?";
			link.l1 = "��, � �� �� ������"+ GetSexPhrase("","�") +", ��� �� ����� �����������.";
			link.l1.go = "PL_Q2_away_3";
		break;
		case "PL_Q2_away_3":
			dialog.text = "�� ��, �� ����������. ������ ��� ����� �����, � �� �� ��� �� ������.\n��� �, ������ ���� �������� �������� �� ��� �����. �� ������ �������������?";
			link.l1 = "��, ������ �� ���? � �������, ������� ����� ���������?";
			link.l1.go = "PL_Q2_away_4";
		break;
		case "PL_Q2_away_4":
			dialog.text = "��, ������ �������. ��� ����� ������������� �� �������� �����.";
			link.l1 = "�������... ��� ��� ������ ������ �������?";
			link.l1.go = "PL_Q2_away_5";
			//AddMoneyToCharacter(PChar, 15000);
			TakeNItems(pchar, "chest", 1);
			Log_Info("�� �������� ��������� ������");
			PlaySound("interface\important_item.wav");
		break;
		case "PL_Q2_away_5":
			dialog.text = "� ��� ����� ��� ����������� ���������� ����� �������, ��������� � ���� � ����. ����, ��� �������� ��� ������ ���, ��� ������� � ��������� ����� �������.";
			link.l1 = "��, � ������ �����������? ��-�� � ��� ����� �� ����� �������������, � �� ������, �����, � �������...";
			link.l1.go = "PL_Q2_away_6";
		break;
		case "PL_Q2_away_6":
			dialog.text = "�� ���, �������. ��� � ���, ������� ���������.";
			link.l1 = "�� ��� �, ������ �������.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_3_KillLoy");
            AddQuestRecord("Pir_Line_3_KillLoy", "1");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","�"));
			NextDiag.TempNode = "PL_Q2_awaywait";
			pchar.questTemp.piratesLine = "KillLoy_toHouse";
			ChangeCharacterAddress(characterFromId("EdwardLoy"), "none", "");
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1.location = "LeFransua_House4";
			pchar.quest.PiratesLine_q3_LoyHouse.function = "PiratesLine_q3_LoyHouse";
		break;
		case "PL_Q2_awaywait":
			dialog.text = "������ ��� �����?";
			link.l1 = "��� ���, ������, �� ����� �����.";
			link.l1.go = "exit";
			link.l2 = "������, ������, ������� ��� ��� ���. �� ���"+ GetSexPhrase("��","��") +" � ���, � ������ ��� ��� ������� ���...";
			link.l2.go = "PL_Q3_notFound";
			NextDiag.TempNode = "PL_Q2_awaywait";
		break;

		case "PL_Q3_notFound":
			dialog.text = "���-�� � ���� ��� ���������, ����� �������"+ GetSexPhrase("","�") +" ����� ���?";
			link.l1 = "�������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "PL_Q3_notFound_1";
		break;
		case "PL_Q3_notFound_1":
			dialog.text = "��� �, ������-�� � ��� � �������. �����, � �� ������ ���� ����� ��������� ������, �����, ���� ������ - ������, ��������, �������?\n����� �������. ������, ��������, �����-������, � ��� ���� ��� ���� ����.";
			link.l1 = "������� � �� ����, ������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
		break;

		case "PL_Q3_GoodWork":
			dialog.text = "�� "+ GetSexPhrase("����� ������� ����������","������ �������� ����") +" ����� ������, ��� ��� ������ �������.";
			link.l1 = "��! ������ ��� �����!";
			link.l1.go = "PL_Q3_GoodWork_1";
		break;
		case "PL_Q3_GoodWork_1":
			dialog.text = "���������� �������. �������� ��������? ������� �� ��� �������� ������ � ������ ���������.";
			link.l1 = "��������  ��������, ���� �������� ��� �� ������. �� � ������ � ������� ������, ���� ������ ���� � ������ �� ���������. � ���. ��� ������, ��� ����� ������� ���������� �����.";
			link.l1.go = "PL_Q3_GoodWork_2";
		break;
		case "PL_Q3_GoodWork_2":
			dialog.text = "��������� ��, " + GetFullName(pchar) + ", ��� ��������� ����������� ������...\n" +
				"��������� ��������� �� �������. ���� ���� � ���� ����� ������ ��� ����������, ������� ��������� ���� � �� �� ������ � �������� ���������� ������, �� ��� ��� ������ ����� ���� ����� ������������. ������ ���! ����, ��� ��� ����� �����, ����� �������, ��� �� �������� ������� ������, ��� ��� �����������. ������� �� ����� �������, ��� �� ���������� ������ �� ������ �������� ������ ���������, �.�. ������ �� �� ������ ���.\n" +
				"������, ���� �� �������, � ���������� � ����� �� �����. � �� ������ ��������"+ GetSexPhrase("","�") +" ���� �������. ����� ��� ��������� ��������������. � ���������� �� ��� ������������, ��������, ����� ��� ���� �������� �������.";
			link.l1 = "������, ������, �������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
			//AddMoneyToCharacter(PChar, 50000);
			TakeNItems(pchar, "icollection", 1);
			Log_Info("�� �������� ���������");
			PlaySound("interface\important_item.wav");
		break;
		//����� �4, ��������� �������
		case "PL_Q4_1":
			dialog.text = "����. ��� ��� ��� ����� ���-�� ����� ����. ����� ������������, ������ ��� �������, ���� ����� ��������. �������� ����������� ������� ������ ���� ������ - ������� ���������� �����? ������, � ���� ��������� ����������, ��� ����� ���������� ������� ������ ������� ��������� �����.";
			link.l1 = "������ �� ������ �� ��������. � ��� �� ���?";
			link.l1.go = "PL_Q4_3";
		break;
		// Warship 13.07.09 � ����� �������� ����
		/*case "PL_Q4_2":
			dialog.text = "��, � ������ ������ ��� ���������� ������. �������� ����������� ������� ������ ���� ������ - ������� ���������� �����? ������, � ���� ��������� ����������, ��� ����� ���������� ������� ������ ������� ��������� �����.";
			link.l1 = "�������. � ��� ���?";
			link.l1.go = "PL_Q4_3";
		break;*/
		case "PL_Q4_3":
			dialog.text = "� ������, � ������ ��������. ��� ��� ����������� ���� � ������ ����� �� ��������. ��� ���� � ����� �������.";
			link.l1 = "�������!";
			link.l1.go = "PL_Q4_4";
		break;
		case "PL_Q4_4":
			dialog.text = "�� ���� ��������, � ��� � ���� ������� ������ ���� �� ����� ������ ����� � ������� ������� ��������. ��� ��� ����������. ������ � �������.";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ��� �������� �����.";
			link.l1.go = "PL_Q4_5";
		break;
		
		case "PL_Q4_5":
			dialog.text = "�������. �� ������ ������ ���� ���� ������������. �� ������� ������ ���� ���� ������� ���������! ���� �� �� ����"+ GetSexPhrase("","�") +", �������� ����� �������� ������ ��������...";
			link.l1 = "�������. ���� ��� ����� ���� � �� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
			pchar.questTemp.piratesLine = "PearlQ4_toTerks"; //���� ������
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			pchar.questTemp.Sharp.PearlAreal.terms = 30; //�����
			pchar.questTemp.Sharp.PearlAreal.qtyShips = 9; //���-�� ������ ������
			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //��� ��������� ��������
			pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
			SetQuestHeader("Pir_Line_4_Pearl");
			AddQuestRecord("Pir_Line_4_Pearl", "1");
			AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("��","��"));
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1.location = "Terks";
			pchar.quest.PQ4_SeaPearl_login.function = "PQ4_SeaPearl_login";
			SetTimerFunction("PQ4_SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
		break;

		case "PL_Q4_wait":
			dialog.text = "�������"+ GetSexPhrase("","�") +" ������ �������?";
			link.l1 = "��� ���, ������, � ��������� ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
		break;
		//�������
		case "PL_Q4_late":
			dialog.text = "��, ��� �������?";
			link.l1 = "�����, ��������� ���, ��� � �������"+ GetSexPhrase("","�") +" � ������.";
			link.l1.go = "PL_Q4_late_1";
		break;
		case "PL_Q4_late_1":
			dialog.text = ""+ GetSexPhrase("��������","�������") +", �� �� ������ �� �������� �����"+ GetSexPhrase("��","��") +" � ����� ���������!.. ���� � ��� �������. � ���� � ������������ ������� �����, � � ����� ��� ���� ����. � ��������� ��� ���� ��������������.";
			link.l1 = "�����, � ���� ������������� ��� ��������� ��������������...";
			link.l1.go = "PearlQ4_late_2";
		break;
		case "PearlQ4_late_2":
			dialog.text = "�����������. ������ ���-������ � ������ ���. � ���� ��� ����-������ ��������, ��� �� �� ����...";
			link.l1 = "������, �������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//���� ������ ������
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		//��������� �����
		case "PL_Q4_badWork":
			dialog.text = "��, ��� ���� � ��������?";
			link.l1 = "�����. ��� ������� ������� ����������� �� ���� ��� ����. �� ���� �� ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "PL_Q4_badWork_1";
		break;
		case "PL_Q4_badWork_1":
			dialog.text = ""+ GetSexPhrase("��������","�������") +", �� �� ������ �� �������� �����"+ GetSexPhrase("��","��") +" � ����� ���������! ���� �� ���� �������������! ���� � ��� �������. � ���� � ������������ ������� �����, � � ����� ��� ���� ����. � ��������� ��� ���� ��������������.";
			link.l1 = "�����, ��� ��� ������. �� � ���� �����, �� ����� ��������� �������! � �������� ���������.";
			link.l1.go = "PearlQ4_late_2";
		break;
		//������� �����
		case "PL_Q4_goodWork":
			dialog.text = "��, ��� ��� ������, "+ GetSexPhrase("��������","" + pchar.name + "") +"?";
			if (!CheckAttribute(pchar, "items.jewelry12") || !CheckAttribute(pchar, "items.jewelry11"))
			{
				link.l1 = "������, �����, ���-�� ��� �������� �����. � ��������, � �����, ��������... ��� ���.";
				link.l1.go = "PL_Q4_goodWork_lair";
			}
			else
			{
				link.l1 = "� ����. � �����"+ GetSexPhrase("","�") +" " + pchar.items.jewelry12 + " ����� � " + pchar.items.jewelry11 + " ������� ��������!";
				link.l1.go = "PL_Q4_goodWork_1";
			}
		break;

		case "PL_Q4_goodWork_lair":
			dialog.text = "�� ��, �����������, �����! �� ���, �����"+ GetSexPhrase("","��") +", ������� � �� � �����, ��� �� �������� ������"+ GetSexPhrase("","�") +"?!";
			link.l1 = "�����, �� ��������...";
			link.l1.go = "PL_Q4_goodWork_lair_1";
		break;
		case "PL_Q4_goodWork_lair_1":
			dialog.text = "�� ��������?!! �� ��, �������� ���� �� ��������. ��� ���, �����, ���� �����. ������������ ������ ��������... ������� �����!";
			link.l1 = "�����, �����!..";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true; 
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_1":
			if (sti(pchar.items.jewelry12) < sti(pchar.questTemp.piratesLine.Qty.SmallPearl) || sti(pchar.items.jewelry11) < sti(pchar.questTemp.piratesLine.Qty.BigPearl))
			{
				dialog.text = "��, ������, � ���� ������ ��������. �� �������"+ GetSexPhrase("","�") +" �� ������� " + pchar.questTemp.piratesLine.Qty.SmallPearl + " ����� � " + pchar.questTemp.piratesLine.Qty.BigPearl + " ������� ��������. ��� �������?";
				link.l1 = "�� �� ��� ��, �����! � ���� ������ ������.";
				link.l1.go = "PL_Q4_goodWork_2";
			}
			else
			{
				if (sti(pchar.items.jewelry12) >= 1000 && sti(pchar.items.jewelry11) >= 500)
				{
					dialog.text = "�������, �� ������ ���������"+ GetSexPhrase("","�") +". � ���� ��, ��������"+ GetSexPhrase("","�") +" '���� �� ������', � ������� �� ������ ����������� ����������. �������, ��� ��� � ���� �������!";
					link.l1 = "� ����� ����� ���� �����?..";
					link.l1.go = "PL_Q4_goodWork_3";
				}
				else
				{
					dialog.text = "��, �� ���� �������, ��� � �������. �� �� ������"+ GetSexPhrase("��","���") +" � ���������� ���� - 1000 ������ � 500 ������� ��������. ��� ��� ������, �� � ������� ��� ����...";
					link.l1 = "���� ������! �� � �� ��������"+ GetSexPhrase("","�") +" ������!";
					link.l1.go = "PL_Q4_goodWork_5";
				}
			}
		break;
		case "PL_Q4_goodWork_2":
			dialog.text = "� ��� � ��� �� �����. �������� ��� ������������� �����. �� �����������"+ GetSexPhrase("","�") +" ������. ��������� �� ��� ���� - ������. � ��, �������� �����, ������ ����� ������ ����...";
			link.l1 = "�����, �� ���� ���?!..";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true; 
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_3":
			dialog.text = "�������� ������ - ����, ��� � ��������������. ��������� - ���.";
			link.l1 = "�������! �� ���, �������, �, �������, �����.";
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -makeint(sti(pchar.items.jewelry12)/2));
			TakeNItems(pchar, "jewelry11", -makeint(sti(pchar.items.jewelry11)/2));
		break;
		case "PL_Q4_goodWork_4":
			dialog.text = "�� ������� ����������� �� ���. ����� ��� ���-������ �����������.";
			link.l1 = "������. ����������� �����, ����� ������ ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//���� ������ ������
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		case "PL_Q4_goodWork_5":
			dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ���� �����, "+ GetSexPhrase("��������","�������") +"! � ����������� �� ������ ������ �����. � ���� �� ���������"+ GetSexPhrase("","�") +" ������� - ��� �� ���� ����� ����. � �����, ������� ����������, ������ � �������...";
			link.l1 = "��, ��� ��, ��� �������� ������, �������... ������ � ���� ����?";
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -sti(pchar.items.jewelry12));
			TakeNItems(pchar, "jewelry11", -sti(pchar.items.jewelry11));
		break;
		//����� �5, ��-���. ����� ����� ����
		case "PL_Q5_begin":
			dialog.text = "���, ����"+ GetSexPhrase("��","��") +" �������. � ���� � ����, " + PChar.Name + ", ���� �������� ���������� ��������.";
			link.l1 = "��� ���������?";
			link.l1.go = "PL_Q5_begin_1";
		break;
		case "PL_Q5_begin_1":
			dialog.text = "��� ��������, ��� �� ����"+ GetSexPhrase("","�") +" ����� ������, ����� ����, ��� ����� �� ��� ������"+ GetSexPhrase("��","���") +". ��� ������?!";
			link.l1 = "��, ��� ������. � ���� ��� ����� �� ����. � � ���, ���������� ����?";
			link.l1.go = "PL_Q5_begin_2";
		break;
		case "PL_Q5_begin_2":
			dialog.text = "��� ��� �����?";
			link.l1 = "�����, �� �� ������, ����� ���� �� ���������.";
			link.l1.go = "PL_Q5_begin_3";
		break;
		case "PL_Q5_begin_3":
			dialog.text = "��� ��������?! � ���� ���������!!!";
			link.l1 = "������� �����.";
			link.l1.go = "PL_Q5_begin_4";
		break;
		case "PL_Q5_begin_4":
			dialog.text = "��� ���?! � ����� �� �� ��� ����"+ GetSexPhrase("","�") +" �������� �� �������� �����? � �����, �� ��� �������! �����, �� �� � �����, �������, �� ���� ������ ���� ��� ���� ���������! �����, ���� �� �� ���������� �� �����, ����� ������. �� ����� ����� ���������� �������� �� ������!\n�� ��� ������ � ������� ������.";
			link.l1 = "������!!! �� � �� ����"+ GetSexPhrase("","�") +", ��� ������ ���� �������!";
			link.l1.go = "PL_Q5_begin_5";
		break;
		case "PL_Q5_begin_5":
			dialog.text = "��������, �� ����"+ GetSexPhrase("","�") +". �� ������ ����� �� �������"+ GetSexPhrase("��","���") +" ����� �����?!\n� ���-��� ��������, ����� ��� �������� � ������ ������. �� ��� �� ����, ��� ��������� �������� ���� ���� �����, ��� �������� ������� ������ �� ���� �����?!! �� ���������, - ������ ������. ����� ����� ����� ��� ������ - ���� � ������. ��� ��� ������, ���� ������!\n��� ����� ������� ������ ���������� ���������?";
			link.l1 = "������. � ���������"+ GetSexPhrase("","�") +", �� �� �� ���������.";
			link.l1.go = "PL_Q5_begin_6";
		break;
		case "PL_Q5_begin_6":
			dialog.text = "�����. ������, ������� ���������� ��������� ���� �����! ���������� �� �����, ��� �������... � �� ���� ������ � ��������.";
			link.l1 = "������ ����, ������ ���� ����� ��������� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_talking";
			AddDialogExitQuestFunction("PQ5_Morgan_1");
		break;

		case "PL_Q5_talking":
			sld = characterFromId("Blaze");	
			dialog.text = "�-�-�, ����� ����! �������, ��� �����. �����-��, ���� ��� �����, ����� ��� ����� �� ������� " + GetMainCharacterNameDat() + "?";
			link.l1 = "�?!! ������ ������ �� ����, �������. � ������ "+ NPCharSexPhrase(sld, "���","��") +" �� �������.";
			link.l1.go = "PL_Q5_talking_1";
		break;
		case "PL_Q5_talking_1":
			sld = characterFromId("Blaze");
			dialog.text = "� ��� ��"+ NPCharSexPhrase(sld, "","�") +" ����������, ��� �� ��� "+ NPCharSexPhrase(sld, "���","��") +" ����� �� ������ ������ ����� ������. �� ������ �� ������������?";
			link.l1 = "�� � ���, ������ �������? ���, �������! ���-�� ��"+ NPCharSexPhrase(sld, "","�") +" ������, � ���� �������� ����������!";
			link.l1.go = "PL_Q5_talking_2";
		break;
		
		case "PL_Q5_talking_2":
			sld = characterFromId("Blaze");
			dialog.text = "�����, �����, �� ���. ��� ��� ��������. � �������� ����� �� ������ ���������� ���������. ��� �����������, ��� ��� �� ����������� ���������� �� " + GetMainCharacterNameGen() + " � ������. �� ����, ��� �� ���� �� ��� ���� �� �� �����, ������� � �������� ������ ������ ������ �������! �� ����� ����, ��� � �� ����� �� ������ ������ �� ���, ������� � ������� ���� �� ����.\n"+"��, � ����, � �����, �� ����. �� ��� ����� �����, ��� ���� �������� �� ��� �������. ���� ������������ ������������ ���� ����� ���� �� �����?! � ������� ������� �� �� ���� ���������� ���?!";
			link.l1 = "�������, ��� �������������! ���� ����������! �� �� ���� ������� ��� ������, ������� �� �������� "+ NPCharSexPhrase(sld, "����� ����������","���� �����") +"?! �� � "+ NPCharSexPhrase(sld, "���","��") +" ������������ ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end";
			AddDialogExitQuestFunction("PQ5_Morgan_4");
		break;

		case "PL_Q5_end":
			dialog.text = "" + GetFullName(pchar) + ", ������� �� ���� �������� �� ������ ������?";
			link.l1 = "���������� �����.";
			link.l1.go = "PL_Q5_end_1";
		break;
		case "PL_Q5_end_1":
			dialog.text = "��, ��� �������� ��������, ��� � ������� ����� ��������� ���� ������, ��� �� ����� ����� �� ��������"+ GetSexPhrase("��","���") +" ���������� � ����� �� ������ ������ ����������.";
			link.l1 = "�� �� ������������ � ����������.";
			link.l1.go = "PL_Q5_end_2";
		break;
		case "PL_Q5_end_2":
			dialog.text = "���, ��� � ���������! ��������� ���� �� ���� � ����� ������ ��� �� �����, �� �� �������� ���� ����� ������� � ������� ���� ����� ������� � ����� �������� �����. ������ ���������� ����� �����, � �� ����������.";
			link.l1 = "��, � �� ��� ������"+ GetSexPhrase("","�") +" � ��� ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
			AddDialogExitQuestFunction("PQ5_Morgan_5");
		break;

		case "PL_Q5_end_3":
			dialog.text = "������� ����� ��������� ����...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
		break;

		case "PL_Q5_afterFight":
			dialog.text = "������ �������� ���� ������. ������! ������� 35000 ������� ��� �������� " + GetMainCharacterNameGen() + ". ��, ��� �, ����� ������� ���� �� ����� �������, ����� ��������� ����� ������.";
			link.l1 = "��, ��� ���. �� � �������"+ GetSexPhrase("","�") +", � ��� ���� ��, ���� �� �� �� ����� �������������?";
			link.l1.go = "PL_Q5_afterFight_1";
			AddMoneyToCharacter(PChar, 35000);
		break;
		case "PL_Q5_afterFight_1":
			dialog.text = "���� ����������: � �� ����, ��� ���� ��, �� ������� � �������������. �����, �� �������������. �� �� ����� ����� �� ������. ��� ���� ������ �������.\n ��, ��� ��� �� ���, ����������� � ��������. � ���� ��� ��������� �����-�� ������������, � ������� ����� ���������� ���� ���. ������ ���������� � ����������� �������. ������, ��� ��� ������ ����� ����.";
			link.l1 = "������, �������. ���������� ����������.";
			link.l1.go = "PL_Q5_afterFight_2";
		break;
		case "PL_Q5_afterFight_2":
			dialog.text = "���� �������"+ GetSexPhrase("��","��") +". ������ ���, ��� ��� ���� ���-�� ������� ������� ������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", �������, ����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q6";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_5_Hunter");
			//����� ���� ����� �6
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "1");
			QuestSetCurrentNode("Jackman", "PL_Q6"); //���� ���� ��������
		break;
		//����� �7, ����� �� ��������
		case "PL_Q7_begin":
			dialog.text = "�-�-�, ��� � " + pchar.name + " ���������"+ GetSexPhrase("","�") +"! ������, ����� �������� ��������.";
			link.l1 = "�����, ����� �������, �� ��� ��� ���������� �� �� �����.";
			link.l1.go = "PL_Q7_begin_1";
			CloseQuestHeader("Pir_Line_6_Jackman");
		break;
		case "PL_Q7_begin_1":
			dialog.text = "���� �� ������ ���������� ������� ��� "+ GetSexPhrase("������ ��������","���� ���������") +", �� ��� ��� ��� ��������.";
			link.l1 = "� ��� �� ������� �� ����� ������?";
			link.l1.go = "PL_Q7_begin_2";
		break;
		case "PL_Q7_begin_2":
			dialog.text = "���� ��� ������ ������. ������� ���, ��� ��������� ����� ������ ��������������.";
			link.l1 = "� ��� ��� ��������� ������? ����� ���� � �����?";
			link.l1.go = "PL_Q7_begin_3";
		break;
		case "PL_Q7_begin_3":
			dialog.text = "�������� ������, ��� ����� �� ����� ����� ���������������. �� ��� �������� ��������� ��������������� �������.\n� ��� ���������� ���-����� ���� � ����, ����� ��������� ��������. �������� �������� �� ��������, ��� �������. �� ������ ����� ��� � ������, ��� �� �����. �� ���� �� � ���� ������.";
			link.l1 = "� ��� �� �������? ���... ��������?";
			link.l1.go = "PL_Q7_begin_4";
		break;
		case "PL_Q7_begin_4":
			dialog.text = "��-��-��! ���� �������. ����� ���� ������, ���������� � ��-����, ����� ������ ��� �������� ������ ��������� ���������. � ��� ������� ��� ���, ��� �������� �� ���"+ GetSexPhrase("","�") +".";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ���"+ GetSexPhrase("��","��") +" ����������.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_7_Soukins");
            AddQuestRecord("Pir_Line_7_Soukins", "1");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toLaVega";
			SetLocationCapturedState("LaVega_town", false);
		break;

		case "PL_Q7_LaVegaLate":
			dialog.text = "�-�, ����� "+ GetSexPhrase("��� �����","���� �������") +" ����"+ GetSexPhrase("��","���") +". ��, ��� �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "�� ������, � �� ���"+ GetSexPhrase("��","��") +" ����� ������ � ��-����.";
			link.l1.go = "PL_Q7_LaVegaLate_1";
		break;
		case "PL_Q7_LaVegaLate_1":
			dialog.text = "� ���� �� ����, ��� ���� � �������. ���-�� �� ����������"+ GetSexPhrase("��","��") +", ��� ������� ��������. ���� ������ ������, � ����� �����, ��� ��� ����� '��������' ����������� �� ����� �����-�������.";
			link.l1 = "������!!";
			link.l1.go = "PL_Q7_LaVegaLate_2";
		break;
		case "PL_Q7_LaVegaLate_2":
			dialog.text = "��� ������. ����������� � �����-�������, �������� ��� �� ����� ��� ������������ '��������'. � ���� ���������, ��� ��...";
			link.l1 = "������, ������ ��� � ������ ����.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "4");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
		break;

		case "PL_Q7_LeonNotFound":
			dialog.text = "�-�, ����� "+ GetSexPhrase("��� �����","���� �������") +" ����"+ GetSexPhrase("��","���") +". ��, ��� �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "�����, ���� ������ ������ ��� �����.";
			link.l1.go = "PL_Q7_LeonNotFound_1";
		break;
		case "PL_Q7_LeonNotFound_1":
			dialog.text = "��� ���?";
			link.l1 = "��� ����-�� ������� ���� ����������� � ��-����, � ��� ��� ��� ����� �� �����, � ������� ��� ��� ������ �� ����� �����-�������.";
			link.l1.go = "PL_Q7_LeonNotFound_2";
		break;
		case "PL_Q7_LeonNotFound_2":
			dialog.text = "�-��, ������, ����� �� ��� �� ������... �� ��� ��, ������ �� ��� ���-������. �����, ����������� ��� ���� ����� ������.";
			link.l1 = "������, �����, �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -3);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_afterLeon":
			dialog.text = "�-�, ��� ���� ������. ��� ������ ����������?";
			link.l1 = "� ���������, ���� ������ �����. ��� ����� ������ � ������� '����'. �� � ���� � ��� ���������"+ GetSexPhrase("��","���") +".";
			link.l1.go = "PL_Q7_afterLeon_1";
		break;
		case "PL_Q7_afterLeon_1":
			dialog.text = "�������! ���� �����...";
			link.l1 = "��� ��� �� ���. ��� ����� ������� ���������� ���� �������� �� �������� ���������� ��������.";
			link.l1.go = "PL_Q7_afterLeon_2";
		break;
		case "PL_Q7_afterLeon_2":
			dialog.text = "��� ���?! ���������, ��� �� �� ������� ��� �������� ���� ��������� ���������� ��������? �� �� ������ �� ��������? ��� ��������, ��� �� �� �������� ����� ��� ��� ������������.";
			link.l1 = "���, �����. ��� ������ �������, ����� ������-��������.";
			link.l1.go = "PL_Q7_afterLeon_3";
		break;
		case "PL_Q7_afterLeon_3":
			dialog.text = "��! ���� ���� ����������? �������, �������� � ��������� � ��� ��� ����, �� ������� �������� ���. ������� ��������� ����� - � ��� ������ ������ ������� �������� ������ ����� �� ����� �������, ����� ���� ������ �� ��� ������� ��������� ���� ����� ���������. � �� ������� ���������� ��������...";
			link.l1 = "��, ������� ������� �������� � ��� ��.";
			link.l1.go = "PL_Q7_afterLeon_4";
		break;
		case "PL_Q7_afterLeon_4":
			dialog.text = "��, ������� - ��������� �������, ������� � ���� ������� ��� �� ����� � ��������.\n�� �� �����. ���� �� ����� ��� ������������� �������: ������ � �������� �� ������� ������� �� ������ ����������; � ������ � �� ����� ��� �� ����� ��������� �����! ������ ����� ��������, ��� ����� ������, ��� ������� ��� ����� ��������� ���� ����������.";
			link.l1 = "����� ��������.";
			link.l1.go = "PL_Q7_afterLeon_5";
		break;
		case "PL_Q7_afterLeon_5":
			dialog.text = "������ ���. ����� �����, ��� ������� ��������� �����. ������ ���������, ����� ��� ����� �������, ����� �� ���������� �������������� ���. �� �������, � ��� ����� ���������.";
			link.l1 = "�� ���-������ ������ �� ���� �����?";
			link.l1.go = "PL_Q7_afterLeon_6";
		break;
		case "PL_Q7_afterLeon_6":
			dialog.text = "�� ��� ������, ����� �������� ��������. � ��� ���� ����� �������.";
			link.l1 = "� ���� � ���� � ���� ����������� ����� ��������?";
			link.l1.go = "PL_Q7_afterLeon_7";
		break;
		case "PL_Q7_afterLeon_7":
			dialog.text = "���. ��� �� �������� ���"+ GetSexPhrase("","�") +" � ����������� ��� ���� ������. ��, ��� ������ ���. � ����� �������� �� ��������. ��� ���� ������� - ������������� ���������.";
			link.l1 = "�������. �� ��� �, ���������.";
			link.l1.go = "PL_Q7_afterLeon_8";
		break;
		case "PL_Q7_afterLeon_8":
			dialog.text = "�������! ��� ���� � �������� ���������.";
			link.l1 = "������ ��, ��� ����.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "8");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toPuertoPrincipe";
			sld = ItemsFromID("OpenBook");
			sld.shown = true;
			sld = ItemsFromID("Ladder");
			sld.shown = true;
			sld.startLocation = "PuertoPrincipe_town";
			sld.startLocator = "item1";
			sld.useLocation = "PuertoPrincipe_town";
			sld.useLocator = "button01";
			//���������� �� ���� � ����������, �� ���� ����������� �������
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1 = "location";
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1.location = "PuertoPrincipe_townhall";
            Pchar.quest.PQ7_inSoukinsResidence.function = "PQ7_inSoukinsResidence";
		break;

		case "PL_Q7_BadWork":
			dialog.text = "��, ��� ����? �����"+ GetSexPhrase("","�") +" �������� ��������?";
			link.l1 = "� ���������, ���, �����...";
			link.l1.go = "PL_Q7_BadWork_1";
		break;
		case "PL_Q7_BadWork_1":
			dialog.text = "�����. ������ ������� ���� �������...";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_GoodWork":
			dialog.text = "��, ��� ����? �����"+ GetSexPhrase("","�") +" �������� ��������?";
			link.l1 = "��, ��� ������"+ GetSexPhrase("","�") +", ��� � �����������.";
			link.l1.go = "PL_Q7_GoodWork_1";
		break;
		case "PL_Q7_GoodWork_1":
			dialog.text = "�������! � ��� �� �������?";
			link.l1 = "�� ���������� ����������� �������� �������, ������� ������� ���������� � ������.";
			link.l1.go = "PL_Q7_GoodWork_2";
		break;
		case "PL_Q7_GoodWork_2":
			dialog.text = "� ���?";
			link.l1 = "� �� ����������"; 
			link.l1.go = "PL_Q7_GoodWork_3";
		break;
		case "PL_Q7_GoodWork_3":
			dialog.text = "��� " + GetFullName(PChar) + ", ����� ���������. �� ���"+ GetSexPhrase("","�") +" ��� ����������"+ GetSexPhrase("","�") +"?";
			link.l1 = "������"+ GetSexPhrase("","�") +" � ���. ��� �������� �������� ������, ����� ���� ��� ������� ��������. ��� ��� �������� ������, ���� ������� ��� �� ������.";
			link.l1.go = "PL_Q7_GoodWork_4";
		break;
		case "PL_Q7_GoodWork_4":
			dialog.text = "����! � ���� �� �����"+ GetSexPhrase("","�") +" ������ �� ��� ��� ����� ��� ��������?";
			link.l1 = "�����"+ GetSexPhrase("��","���") +". ���� ������"+ GetSexPhrase("","�") +" ��� ������� ������. �� �� ���� ������� �������� ������ ������� � ����� ��������. ������ ��� ����������.";
			link.l1.go = "PL_Q7_GoodWork_5";
		break;
		case "PL_Q7_GoodWork_5":
			dialog.text = "�������������. ��� ������� ������ ��������, ������ ����� �� ����� ������ ����������. ��� �����, ��� ����� ������ ��� ���� �������� �������.";
			link.l1 = "�� ���� � � �������"+ GetSexPhrase("","�") +", ����� ��������"+ GetSexPhrase("","�") +" �������� �������."; 
			link.l1.go = "PL_Q7_GoodWork_6";
			RemoveItems(PChar, "OpenBook", 1);
		break;
		case "PL_Q7_GoodWork_6":
			dialog.text = "�� �����, ������ ���� ����� �������� ������ ������, ���� �� ������ ���������� �� �����-������ ������� - � �� ���� ������. ��� ��������� - ������� �� ���, ��������� ���� ��������������. ������ � ���������� �� �����, ��������� ������� ������ �������� � ����� �����������. �� � ���, � ��������� ����, ������.";
			link.l1 = "� ���� � �� ���� ����������� � ��������?";
			link.l1.go = "PL_Q7_GoodWork_7";
		break;
		case "PL_Q7_GoodWork_7":
			dialog.text = "����� ������� ���-�� ����� �����.";
			link.l1 = "�������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, 10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;
		//����� �8, ����� ������
		case "PL_Q8_1":
			if (pchar.questTemp.State == "" || pchar.questTemp.State == "EndOfQuestLine")
			{
				dialog.text = "�� ��� ������ �������! � ��� ����� ���������� �� ���� ������ ��������.";
				link.l1 = "��, �������-��! ��� �� ����?";
				link.l1.go = "PL_Q8_2";
				pchar.questTemp.State = "EndOfQuestLine"; //���� ������ ��� �� ���� ���.�������, �� � �� ���� �� ����� ������ ������
				bWorldAlivePause = false; // ����� �������
			}
			else
			{
				dialog.text = "��, ����� �� ���� �����, ��� ��, "+ GetSexPhrase("��������","�������") +", ������"+ GetSexPhrase("��","���") +" � " + NationNamePeopleAcc(sti(pchar.questTemp.NationQuest)) + ". � ����, �������, ���� �������, ����� �� ��������"+ GetSexPhrase("","�") +" ������ �� ������, � ����� ��� ���� ������"+ GetSexPhrase("","�") +". ��� ���� ���������?!";
				link.l1 = "��� ����, �����, ������...";
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_2":
			dialog.text = "����? ��, ���� ���������. � ������� ���� ������� ��� ������������ �����������, ������� ������� ���� � �������!";
			link.l1 = "��������� ���������.";
			link.l1.go = "PL_Q8_3";
		break;
		case "PL_Q8_3":
			dialog.text = "����� ���! � � ���� ����, "+ GetSexPhrase("���� ���","��� �������") +", � ���� ����� ������ ������. ������ ���� ������ ����� � ����� ������ ���������.";
			link.l1 = "����� ����.";
			link.l1.go = "PL_Q8_4";
		break;
		case "PL_Q8_4":
			dialog.text = "����� �������� '����' - ��� ������ ���, � ���� ������ - �������������� ��������� ��, � ��� � ���� �����.";
			link.l1 = "�����, ���� � ��� � ���� ������������� �������������, �� � ������ ����������"+ GetSexPhrase("","�") +" �� �������� �������� �������� ���������� ��������.";
			link.l1.go = "PL_Q8_5";
		break;
		case "PL_Q8_5":
			dialog.text = "�� ��������� "+ GetSexPhrase("��������, ��������","���������, " + pchar.name + "") +", � ��� ����. ��, � ������ ����� � ����� ���� � ���� ����!";
			link.l1 = "����������� ���� ������, �����.";
			link.l1.go = "PL_Q8_6";
		break;
		case "PL_Q8_6":
			dialog.text = "� �������. � ������� ����� ������!!";
			link.l1 = "���! � �� ������, ��� ��� �������� � ��������?";
			link.l1.go = "PL_Q8_7";
		break;
		case "PL_Q8_7":
			dialog.text = "� ������ ����������?";
			link.l1 = "��� ������ ��������� ����� �������������� � ��������� �������� ������. �� �����, ��� ������� ������ ��� �����-�� ������� ��������.";
			link.l1.go = "PL_Q8_8";
		break;
		case "PL_Q8_8":
			dialog.text = "� ���� �� ��������� � ������, ��� ����� ������� �������� �������� ����� ������, ��� ���� � ��������� � ����� �����?";
			link.l1 = "��, � ��� ��������, ��� �� �������� ��������... ������, �� � ������"+ GetSexPhrase("","�") +", ��� ��� ���� �������� ��� � ��������� ���������! � ���� �� ����� ������� � �������?";
			link.l1.go = "PL_Q8_9";
		break;
		case "PL_Q8_9":
			dialog.text = "�� ��������� ������"+ GetSexPhrase("","�") +" - '������"+ GetSexPhrase("","�") +"'! � � ������, ��� ������ ������ ����� �������� ������� �������� � ���������  �� ����� �������� ����������. ������, ��� ����������� ��������.";
			link.l1 = "��, ��, ���� ������. � �� ������, ��� ����� ������� ������� �� ������ ����� ��� ���� ��� ������?";
			link.l1.go = "PL_Q8_10";
		break;
		case "PL_Q8_10":
			dialog.text = "�� ������, ������� �� ������ �� ����� ��� ����, � ����� ��������.";
			link.l1 = "������! ��� �� ��� ������� �������!!";
			link.l1.go = "PL_Q8_11";
		break;
		case "PL_Q8_11":
			dialog.text = "�����. ������� ������� � �� ���� �� ��� �����, � ���� �� �� ������� �������� ����� � ����. �� ������� ��� ����� - �� ��� �������.";
			link.l1 = "�, ����! ���������, ���� � ������! ����� ����������?";
			link.l1.go = "PL_Q8_12";
		break;
		case "PL_Q8_12":
			dialog.text = "� ��� ���� 20 ����, ����� �� ����"+ GetSexPhrase("","��") +" ������������� ��� �������. ������� ������� ��������, � �������� ������� �������� ������. �� ������� ����������� � ���� ���� ������ � ����� �������, ���� ��� � ����.";
			link.l1 = "�������. ��� ��� ��� ����� �����?";
			link.l1.go = "PL_Q8_13";
		break;
		case "PL_Q8_13":
			dialog.text = "������� �� ������� ����� �����, ����� �� ��������� �������� �������� � ����. ����� �������� �� ������ ����� �������. ������, ����� ����� ��������� ������ ������� ����������, ������� ������ ���� � �� ��������.";
			link.l1 = "�� � � �� �������"+ GetSexPhrase("��","���") +"!";
			link.l1.go = "PL_Q8_14";
		break;
		case "PL_Q8_14":
			dialog.text = "��-��, ���� � "+ GetSexPhrase("����� ������� �����, ��� �����.","����, ������� ��������!") +" �������: �� ����, ����� �������� �������� � ���, ����������� ��� ������ ���-����� �������. ��������, ����� ����� �����.";
			link.l1 = "� ��� �� �������?";
			link.l1.go = "PL_Q8_15";
		break;
		case "PL_Q8_15":
			dialog.text = "� �� ������, �������, ����� ����� �����.";
			link.l1 = "��, ������ � �� ����� ���������� ���������.";
			link.l1.go = "PL_Q8_16";
		break;
		case "PL_Q8_16":
			dialog.text = "������ ����, ��� ������� ��� ���� ������ �������� ��������. � �����, ����� 20 ���� ��� ����, � ������ ��������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", �����.";
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_8_Panama", "1");
			NextDiag.TempNode = "PL_Q8_ready";
			pchar.questTemp.piratesLine = "Panama_toReady";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			SetTimerFunction("PQ8_timeOver", 0, 0, 35);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //�������� ������� � ������
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		break;

		case "PL_Q8_ready":
			if (GetQuestPastDayParam("questTemp.piratesLine") > 20)
			{
				dialog.text = "���, ��� � �� ����"+ GetSexPhrase("��","��") +"! ��� ������, ��� ��� ����� ������. � ��� �������, ��� �� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = "��, �������. � ������ ������ ����������.";
				link.l1.go = "PL_Q8_ready_1";
			}
			else
			{
				dialog.text = "����� ����"+ GetSexPhrase("��","���") +"? ����� 20 ����, � �� ������ ����!";
				link.l1 = "��, � �����. ������ �����"+ GetSexPhrase("","�") +" �������...";
				link.l1.go = "PL_Q8_NotReady1";
			}
		break;
		case "PL_Q8_NotReady1":
			dialog.text = "��������, " + PChar.name + ", � �� ���� ���������� ������ ������, ����� �� ��������"+ GetSexPhrase("","�") +" � ����� ��������. ���� ����� ������ ���� ��, ��� � ������. ��� ��� �����������?!";
			link.l1 = "��� ����, �������, ������ ��������.";
			link.l1.go = "exit";
		break;
		case "PL_Q8_ready_1":
            if (GetCompanionQuantity(pchar) == 1)
            {
				dialog.text = "�������! ����, �� ���������. � �������� ��������� � ���� ��� ��������� �������, ���� ������ � ��� ������� ���� ������ �������. �� ���� � �������� ������������ �������� � ����� ����� �����.";
				link.l1 = "������� �� �������, �������. � �� �������, ���� ������!";
				link.l1.go = "PL_Q8_ready_2";
			}
			else
			{
				dialog.text = "��������, " + pchar.name + ", � �� ���� ���������� ������ ������, ����� �� ��������"+ GetSexPhrase("","�") +" � ����� ��������. ���� ����� ������ ���� ��, ��� � ������. ��� ��� �����������?!";
				link.l1 = "��� ����, �������, ��� ������.";
				link.l1.go = "exit";
				NextDiag.TempNode = "PL_Q8_ready";
			}
		break;
		case "PL_Q8_ready_2":
			dialog.text = "����� �� ��� �����������, "+ GetSexPhrase("��������","" + pchar.name + "") +". � ��������� ������, �������� ���� �� �����.";
			link.l1 = "�� �� ������� ��� ����� �����, �� ��������.";
			link.l1.go = "PL_Q8_ready_3";
		break;
		case "PL_Q8_ready_3":
			dialog.text = "������. ����� �������� ����������.";
			link.l1 = "����, � �����"+ GetSexPhrase("","�") +" ���������� � ������������.";
			link.l1.go = "PL_Q8_ready_4";
		break;
		case "PL_Q8_ready_4":
			pchar.quest.PQ8_timeOver.over = "yes"; //������� ������ 
			SetTimerFunction("PQ8_PanamaTimerOver", 0, 0, 20); //������ ����� ������
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1 = "location";
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1.location = "PortoBello";
			pchar.Quest.PQ8_EnterPortoBello.function = "PQ8_EnterPortoBello";
            pchar.questTemp.piratesLine = "Panama_toPortoBello";
			AddQuestRecord("Pir_Line_8_Panama", "4");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("��","��"));
			pchar.TempPerks.QuestTroopers = true; //���� ���������� �������
			characters[GetCharacterIndex("PortoBello_Mayor")].dialog.captureNode = "PQ8_MayorPortoBello"; //�������������� ���� ����
			//������
			FantomMakeCoolSailor(npchar, SHIP_BATTLESHIP, "���������", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            pchar.nation = PIRATE;
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			//LAi_SetImmortal(NPChar, false);
			NPChar.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(NPChar);
			LAi_RebirthOldName(NPChar); 
			npchar.DeckDialogNode = "PL_Q8_deck"; //���� �� ������
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            npchar.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
			SetCharacterRemovable(npchar, false);
			//�������
			sld = characterFromId("Jackman");
			FantomMakeCoolSailor(sld, SHIP_WARSHIP, "���������", CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
			LAi_SetImmortal(sld, false);
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//���� ������
			if (GetCharacterIndex("John Morris") == -1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        		sld.name 	= "����";
        		sld.lastname = "������";
				sld.Dialog.Filename = "Quest\JohnMorris.c";
				sld.greeting = "Gr_HeadPirates";
				FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol4", 150);
           		LAi_SetStayType(sld);
        		LAi_SetLoginTime(sld, 0.0, 24.0);
        		LAi_SetHP(sld, 180.0, 180.0);
			}
			else
			{
				sld = characterFromId("John Morris");
			}
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, "������", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);	
			sld.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //�� ������ ������� ����� ������.  
			sld.DeckDialogNode = "PL_Q8_deck"; //���� �� ������
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//������ �������
			sld = characterFromId("Richard_Soukins");
			FantomMakeCoolSailor(sld, SHIP_MANOWAR, "�����������", CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 2500;
			LAi_SetImmortal(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_RemoveLoginTime(sld);
			sld.DeckDialogNode = "PL_Q8_deck"; //���� �� ������
			SetCompanionIndex(pchar, -1, sti(sld.index));
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q8_timeOver":
			dialog.text = "� ������� ���� ���������� ��������, � �� ��������� ��� �����������. �� ��� ���� �������� ����� �� �������, ����� �� ����-����� �� ����� ����� �� ���� ������ ���� ����!";
			link.l1 = "��� ����������, �����...";
			link.l1.go = "PL_Q8_timeOver_1";
			// ����� � ������
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
		break;
		case "PL_Q8_timeOver_1":
			dialog.text = "����� � ���� '��� ����������' ���-������ � ������ �����. �������, ���� ������ ������ ������ ������� � ����� �������� � ������. � �����, �� ������, ���-������ ��������� ��� ���� � ����� ����. ������.";
			link.l1 = "�� � ���� � ����!";
			link.l1.go = "PL_Q8_timeOver_2";
		break;
		case "PL_Q8_timeOver_2":
			dialog.text = "�� ��������, "+ GetSexPhrase("��������","�������") +". �� ������ ���� �� ����.";
			link.l1 = "�� �� ��� ��� ��� ������� ���� ������? ������ �������� � �������� �������.";
			link.l1.go = "PL_Q8_timeOver_3";
		break;
		case "PL_Q8_timeOver_3":
			SetTimerFunction("PQ8_openPanama", 0, 0, 40);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //�������� ������� � ������
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
			pchar.questTemp.piratesLine = "over";
			AddQuestRecord("Pir_Line_8_Panama", "3");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("Pir_Line_8_Panama");
			//���������� �������
            if(IsCompanion(npchar))  RemoveCharacterCompanion(pchar, npchar);
            //���������� �� ����� ��������
			iTemp = GetCharacterIndex("Jackman");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}               
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
			//���� ������
			iTemp = GetCharacterIndex("John Morris");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}   				
				sld = &characters[iTemp];
				sld.lifeDay = 0;
			}
            //���������� �� ����� ��������
			iTemp = GetCharacterIndex("Richard_Soukins");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}                   
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
            NextDiag.TempNode = "PL_Q8_timeOver_exit";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_timeOver_exit":
			dialog.text = "�� � ��� ������ ��������.";
			link.l1 = "...";
			link.l1.go = "PL_Q8_timeOver_exit";
		break;
		//� ���������� ������� ����� �����
		case "PL_Q8_PBResidence":
			dialog.text = "�� ������ ������"+ GetSexPhrase("","�") +" �����, �����.";
			link.l1 = "����� ����� ���, �������. �� � ��� ���� ��������� ��������.";
			link.l1.go = "PL_Q8_PBResidence_1";
		break;
		case "PL_Q8_PBResidence_1":
			dialog.text = "� ��� ����?";
			link.l1 = "�������� �������� � ����� ���������� ���� �� ������. ��� ��������� ��� ������� ����������.";
			link.l1.go = "PL_Q8_PBResidence_2";
		break;
		case "PL_Q8_PBResidence_2":
			dialog.text = "������!! � ��� ��� ������ �� ����?";
			link.l1 = "�� ��� ������, ��������� �������-����������.";
			link.l1.go = "PL_Q8_PBResidence_3";
		break;
		case "PL_Q8_PBResidence_3":
			dialog.text = "�-��, �������� ����. ������� ���, ��� ��� ����� ������� ��������. ������ ������� ��������� ������ � ������ ������� � ������ ������� ������.";
			link.l1 = "�� ��, ���� ����� � ������ ������� ������������ �����������, �� � ������ ��� ������ ������������.";
			link.l1.go = "PL_Q8_PBResidence_4";
		break;
		case "PL_Q8_PBResidence_4":
			dialog.text = "��-��, ����� ����. ��� ���, " + pchar.name + ", ��� ���� ����������� �� ��������.";
			link.l1 = "������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "PL_Q8_PBResidence_5";
		break;
		case "PL_Q8_PBResidence_5":
			dialog.text = "�� ��� ���� ���� �������� - ��� ����. ��� ��� �����. ���� � ��� ���-�� �������� ������, �� ��� ������ ����� ��� ��������. � ��� ������ ���������� ��� ������ ������!";
			link.l1 = "�����, ��� �� �� ����������� ������������ �� ���� �����?!";
			link.l1.go = "PL_Q8_PBResidence_6";
		break;
		case "PL_Q8_PBResidence_6":
			dialog.text = "�������, ���!! ����� ��� � ������� ����� ������������ ������? �� �� ��������, ������� - ����� ��, ��� � ���� ������. � ��� ����� ������.";
			link.l1 = "�� �����������, �����! �� ������-�� � ���� � �����! ��� ����� ������?";
			link.l1.go = "PL_Q8_PBResidence_7";
		break;
		case "PL_Q8_PBResidence_7":
			if (pchar.location.from_sea == "Shore48")
			{
				dialog.text = "�� �������"+ GetSexPhrase("��","���") +" � ���������� ������, � ��� ���������. ������ ����, ������ ����� ����� � ������ � ������. � ���� ���� � ���� �� ������ ������� ������, �� ����� �����. � ����� ������ ���������� � ����� ������ ����� � ���� �����������.";
				link.l1 = "� �����"+ GetSexPhrase("","�") +", �������!";
				link.l1.go = "PL_Q8_PBResidence_8";
			}
			else
			{
				dialog.text = "����������� � ���������� �����. ������ ����� ����� � ������ � ������. � ���� ���� � ���� �� ������ ������� ������, �� ����� �����. � ����� ������ ���������� � ����� ������ ����� � ���� �����������.";
				link.l1 = "� �����"+ GetSexPhrase("","�") +", �������!";
				link.l1.go = "PL_Q8_PBResidence_8";
			}
		break;
		case "PL_Q8_PBResidence_8":
			dialog.text = "��� ��� �� ���. ������� � ������ ������ �� ����. �� ������� � ���������. ������� ����� � ����� ������, � ��������� ���������� ������������ ������ � ��������. � ������ �����, � �� ����.";
			link.l1 = "�����, ��� ��� ���, �������. �� ����� ������.";
			link.l1.go = "PL_Q8_PBResidence_9";
		break;
		case "PL_Q8_PBResidence_9":
			dialog.text = "���� ����� �� ������ �������� �� ����������. �� ����� ������� ���� � �������� ��������, � �� ���� ������ ��� � ���� ������. �� ��������� ����� � ����� ��� ��������� �� ������ ������, ��� ��� ���� �������� ������ ��������� �� �����. � ����� ��� ������ �� �������, ������������ - ������� ���� � � ��������� ��������.";
			link.l1 = "��� �� ����������� ���������?"
			link.l1.go = "PL_Q8_PBResidence_10";
		break;
		case "PL_Q8_PBResidence_10":
			dialog.text = "����� ������. ��-������ �������� �������� � ���, �� ���, ����� ����� �� �����. ������� � ����� - ����� ������ ��������.";
			link.l1 = "��, �������, �� �����"+ GetSexPhrase("","�") +", ��� �� �������� ���������� ����� ��������.";
			link.l1.go = "PL_Q8_PBResidence_11";
		break;
		case "PL_Q8_PBResidence_11":
			dialog.text = "������, " + PChar.name + ", ����� ��� �������������.";
			link.l1 = "�� �������...";
			link.l1.go = "PL_Q8_PBResidence_12";
		break;
		case "PL_Q8_PBResidence_12":
			dialog.text = "������, ������ ����� ����� ������ ���������� ��� ���� ������. �� �����, ��� ������� �� ������ ������ ��������� �� ������.";
			link.l1 = "������, ���-������ ��������.";
			link.l1.go = "PL_Q8_PBResidence_13";
		break;
		case "PL_Q8_PBResidence_13":
			dialog.text = "��, ��� � �������! � �����, ���� ����� ����� � ������ � ���������� �����. �� �����, ��� ����� ��� ��� �� ����"+ GetSexPhrase("��","��") +" ���� ���. � �� ������� ������ ����� � ��������, ��� ���� �������� ����.";
			link.l1 = "������, �����, ���� ����� ���� � ������.";
			link.l1.go = "PL_Q8_PBResidence_14";		
		break;
		case "PL_Q8_PBResidence_14":
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false; 
			//bQuestDisableMapEnter = false;
			LocatorReloadEnterDisable("Shore48", "reload1_back", false); //��������� ������ � ������� ����� �����
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1.location = pchar.location;
            Pchar.quest.PQ8_PBExitResidence.function = "PQ8_PBExitResidence";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_PBResidence_over":
			dialog.text = "�� ������������, ������ � ������!";
			link.l1 = "��, � �����"+ GetSexPhrase("","�") +", �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
		break;
		//� ����� ������
		case "PL_Q8_ExTPanama":
			iTemp = GetCharacterIndex("Richard_Soukins");
			
			if(PChar.QuestTemp.piratesLine == "Panama_RichardBadWork")
			{
				if(LAi_IsDead(&Characters[iTemp]))
				{
					dialog.text = "� ����� �������� ����� ����������� � ��������� ���. ������, ��� �� �������"+ GetSexPhrase("","�") +" � ��������...";
					link.l1 = "��, �� ���� ������ �� �����! � ������, ���� ������� - ������� ����� �������� ���������� ������.";
					link.l1.go = "PL_Q8_ExTPanama_1";
				}
				else
				{
					dialog.text = "����, �� �� ����"+ GetSexPhrase("","��") +" ��������� �������! ��� ���� ����������� ����� ��� �� � ��� �� ������.";
					link.l1 = "�����, � �� ����"+ GetSexPhrase("","��") +" ������ �������, ��� ���� ����� ������!";
					link.l1.go = "PL_Q8_ExTPanama_7_Soukins";
				}
			}
			else
			{
				dialog.text = "��-��, ��� ���� ������, " + PChar.name + ", "+ GetSexPhrase("����� � ��������","����� � ��������") +"! � ���-�� �� ����� �������� � ���� ���.";
				link.l1 = "�����, � ����������� ����"+ GetSexPhrase("��","��") +" ���� ��������, ��� ������ ������� ������� ���� ������� ���. �� ��� ��� �����!";
				link.l1.go = "PL_Q8_ExTPanama_1";
			}
		break;
		case "PL_Q8_ExTPanama_1":
			dialog.text = "������� ������ � ����, ������ ���! �� ����� ������� ���, ��� �����.\n��, �����������, ��� ���� � ��������?";
			link.l1 = "�� ����� ��� � ��������� ���� ������ ��� �������� ��������� ��� ��� �����. ���� ������� ��� ���������!";
			link.l1.go = "PL_Q8_ExTPanama_2";
		break;
		case "PL_Q8_ExTPanama_2":
			dialog.text = "�� �� ����� ���� � � ���. �� ��� �� �����, "+ GetSexPhrase("�������","�������") +"!";
			link.l1 = "��� �� ������ � ����? �� ������� ��������� ������!";
			link.l1.go = "PL_Q8_ExTPanama_3";
		break;
		case "PL_Q8_ExTPanama_3":
			dialog.text = "�� � ��� ��� ������? ��� �����. �� ���� � ���, ��� ������� �������� �������� ����������. �������� ��� �������� ���� ����, ����� �������, ��� ������� ���������� �� �� ������! ���� �� ��� ������� ��� ���� � �����, ��, ����������, ������� �� ���. ��, � ������ ��� ����� ��� �� ��� ����. � ������ - ������ ����!";
			link.l1 = "�� �������, ��� � ������ ��� ������?";
			link.l1.go = "PL_Q8_ExTPanama_4";
		break;
		case "PL_Q8_ExTPanama_4":
			dialog.text = "������ � ����! ������ ������, ������ �� �������� � ���������� ����������� � ������� ������. � ���� ������ ������������.";
			link.l1 = "��� �� ������ � ����?";
			link.l1.go = "PL_Q8_ExTPanama_5";
		break;
		case "PL_Q8_ExTPanama_5":
			dialog.text = "��� ��������, ��� ��� ����� ����� ������ ������ - ��� �����. � ������, ��������� ������ ���� �� ���� ������ �� ���� ������ �������. � ���� ������ ������� �� ������ ����������� ����� �������� ����. �� � ��� ���� ���� ����� ������ ���������, � ��� ����� ��� ����� ����������. �� ��������� ����� ���� �������� ������ � �������� ������.";
			link.l1 = "�� ������������� ����.";
			link.l1.go = "PL_Q8_ExTPanama_6";
		break;
		case "PL_Q8_ExTPanama_6":
			dialog.text = "���������� � ���������� ������, � �� ������������! � � ������� ������� ������ � ������.";
			link.l1 = "�������. ��������.";
			link.l1.go = "PL_Q8_ExTPanama_7";
		break;
		case "PL_Q8_ExTPanama_7":
			AddQuestRecord("Pir_Line_8_Panama", "9");
			//characters[GetCharacterIndex("Panama_Mayor")].dialog.captureNode = "PQ8_afterAttack"; //�������������� ���� ����
			pchar.quest.PQ8_piratesInPanama.win_condition.l1 = "location";
			pchar.quest.PQ8_piratesInPanama.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_piratesInPanama.function = "PQ8_piratesInPanama";
			NextDiag.TempNode = "PL_Q8_ExTPanama_over";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_ExTPanama_over":
			dialog.text = "������ � ����������, �� ����� �������!";
			link.l1 = "��, �����, � �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
		break;
		case "PL_Q8_ExTPanama_7_Soukins":
			dialog.text = "�� ��� ��!";
			link.l1 = "��� ����� �����, ���� �� � ��� ��� ���������.";
			link.l1.go = "PL_Q8_ExTPanama_8_Soukins";
		break;
		case "PL_Q8_ExTPanama_8_Soukins":
			dialog.text = "��� � �����! ����, �� ���� � �����������. �� ������ ������������ � ������ �������, � ������ ���� ���� ���. �� ��, ��� �� ������"+ GetSexPhrase("","�") +" ����, �������� ���� �� ���������� ��������. ���"+ GetSexPhrase("��","��") +" ���!";
			link.l1 = "�� �����-�� � ��������!";
			link.l1.go = "PL_Q8_ExTPanama_9_Soukins";
		break;
		case "PL_Q8_ExTPanama_9_Soukins":
			QuestSetCurrentNode("Richard_Soukins", "PQ8_exitTown");
			AddQuestRecord("Pir_Line_8_Panama", "10");
			CloseQuestHeader("Pir_Line_8_Panama");
			LocatorReloadEnterDisable("Panama_ExitTown", "reload4", true); //������� ���� � �����
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30); //������ �� ������� ��� �����.
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//� ������ ����� ������ �� �� ����������
		case "PL_Q8_Panama1":
			dialog.text = "�� ���"+ GetSexPhrase("��","��") +" �����������?";
			link.l1 = "��. ���"+ GetSexPhrase("��","��") +" � ��������"+ GetSexPhrase("","�") +".";
			link.l1.go = "PL_Q8_Panama1_1";
		break;
		case "PL_Q8_Panama1_1":
			dialog.text = "� ��� �� ������?";
			link.l1 = "������ ���������, ��������, ��������� � �������� ����������� � ����������. ������ ��� ����� � ������� ���, �� ������.";
			link.l1.go = "PL_Q8_Panama1_2";
		break;
		case "PL_Q8_Panama1_2":
			dialog.text = "� ��� ���� ����?";
			link.l1 = "� ����������. ��� ����� ��� ������� ��������� ���� ���������� ���, �����, ����� ��� ����������. ���� ���, �� �������� ������ � �����.";
			link.l1.go = "PL_Q8_Panama1_3";
		break;
		case "PL_Q8_Panama1_3":
			dialog.text = "��, �� ��� ��, �����������. � � ���� ������� ������������, ���-�� ��� ������� ������������. ������ ��������� � �����������, � ���� - � ����������! ���, �������...";
			link.l1 = "�� ���� ��� ���������? ��������� ��� ���� ������������, ���� ��������� �������������� ����� ������� ������ ������. ������, ��� ������ � ������� �� ��������. ��� ��� �����.";
			link.l1.go = "PL_Q8_Panama1_4";
		break;
		case "PL_Q8_Panama1_4":
			sld = characterFromId("FantomMayor");
			sld.lifeDay = 0;
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
			pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload3", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//� ���������� ������ � ������
		case "PL_Q8_Panama2":
			npchar.quest.locInd = FindLocation(pchar.location);
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.money")) sld.private1.money = 0;
			if (CheckAttribute(sld, "private2.money")) sld.private2.money = 0;	
			dialog.text = "� ����, �� �������"+ GetSexPhrase("��","���") +" � �������. ���"+ GetSexPhrase("��","��") +" ���-���� ����!";
			link.l1 = "���"+ GetSexPhrase("��","��") +"! � ��� ����������?";
			link.l1.go = "PL_Q8_Panama2_1";
		break;
		case "PL_Q8_Panama2_1":
			dialog.text = "���������� �� ��� ����. ��� ����������, ��� �� ���� �� ��� ������, � � �������� ��� � ������������. �� �������� ��� �������...";
			link.l1 = "��, ������� ������ ���-�� ������?";
			link.l1.go = "PL_Q8_Panama2_2";
		break;
		case "PL_Q8_Panama2_2":
			dialog.text = "�� ����, ������� ������ � �������� �������. ��� 50 ��������� ��������, "+ GetSexPhrase("��������","" + pchar.name + "") +"! �� �� � ��� ���� ��� ��� ������, �����, ���������� ������!";
			link.l1 = "��� ��� ������, ������. ������, � ��� �� ���������� ������������ ������ ����?";
			link.l1.go = "PL_Q8_Panama2_3";
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.items.gold")) DeleteAttribute(sld, "private1.items.gold");
			else AddMoneyToCharacter(pchar, -50000000);
		break;
		case "PL_Q8_Panama2_3":
			dialog.text = "���� ������ ������ ����� ���� ���������� � ���� � ��������. ������� � �������� ����� ��� � ����� �����, � ����� ������� ��� ������ �� ������� ���������� ��������.";
			link.l1 = "��, ��� ���� �� �����������!";
			link.l1.go = "PL_Q8_Panama2_4";
		break;
		case "PL_Q8_Panama2_4":
			dialog.text = "�� ���� ������ ��� ����"+ GetSexPhrase("","�") +", ��� ��� � ��������� � ���� �� ���� - ������ ���� ������"+ GetSexPhrase("��","��") +" �� ������������ ���� �����������. �� ��� ���� �� ��� ����� ���� ������\n"+
				"����������� ����� � ���� ������. ��� �� ������, � ������� ������� ����� ���� ������. � ��� ������ ���� ��� ������ ���������! ��� ��������� �������� ���������� ������.";
			link.l1 = "����, �� ����� ����! � ������� �������?!";
			link.l1.go = "PL_Q8_Panama2_5";
		break;
		case "PL_Q8_Panama2_5":
			dialog.text = "������ ���, ������ ��������� ����� �� �������� �����. � ��� ���� � ���� �������, ��� ��� �� ������.";
			link.l1 = "������, ������ �������.";
			link.l1.go = "PL_Q8_Panama2_6";
		break;
		case "PL_Q8_Panama2_6":
			AddQuestRecord("Pir_Line_8_Panama", "12");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("Pir_Line_8_Panama", "sSex1", GetSexPhrase("","�"));
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1.location = "Panama_Fort";
			Pchar.quest.PL_Q8_inPanamaFort2.function = "PL_Q8_inPanamaFort2";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������ � ���� �����
		case "PL_Q8_afterPanama":
			dialog.text = "���, ��� ��� �������! " + pchar.name + ", �� �� ���?!";
			link.l1 = "�, ����������� ��������. ���, ����"+ GetSexPhrase("��","��") +" ��������� ���� � �����.";
			link.l1.go = "PL_Q8_afterPanama_1";
		break;
		case "PL_Q8_afterPanama_1":
			dialog.text = "��, ��������, ������"+ GetSexPhrase("","�") +" �� ����. ��, ������, ��� �������� �������� ���� � ������ - ����� ���������, ������ ��.";
			link.l1 = "������"+ GetSexPhrase("","�") +"?!! ��� � �� ���� �� ������"+ GetSexPhrase("","�") +". � ���� ��������, ��� �����, ������� ������ � ���������� �������� ��� ����!";
			link.l1.go = "PL_Q8_afterPanama_2";
		break;
		case "PL_Q8_afterPanama_2":
			dialog.text = "�� �����, ��� ��������!!! ������, ������� ���� ��������!";
			link.l1 = "�����, � �����, �������?!!";
			link.l1.go = "PL_Q8_afterPanama_3";
		break;
		case "PL_Q8_afterPanama_3":
			dialog.text = "������������, "+ GetSexPhrase("��������","" + pchar.name + "") +". �� ���, ��������� �� ����� ����� ������� ������� � ���� ��� ���������� ������? ��������� ������ � ������ ��� ���������, ��� ��� ����� ����� �������� ���������. ��� ������ ����������� ������� ���, �� ����� ������ �������!\n� ��� ����� ��� ���������! �� ��� ������!";
			link.l1 = "�� �� ������� � �� ���� ������ �����, �����, ��� �����������, ���������� �������� �� ��� ����! ��� ������ ������������ � ����� ��������� ����� �����, ��� ��! � ����� ���������, ����������� �������� � ������ � ����������!";
			link.l1.go = "PL_Q8_afterPanama_4";
		break;
		case "PL_Q8_afterPanama_4":
			dialog.text = "����� ��� ������ �� ������. ��� ������� � ���� ����������� �� ������ ������, �� ������, ������ ��� ���������?";
			link.l1 = "�� ����� �� ���� �������! �� ������, ������� �� ���� � ������ ������� ������ ����, � ��� ��� ������������, ��� � ����� ������������! �������, ������, �����������, ����� �� �������, �������� ������ ������ �������� ����������, � ����� �������� ������ ��� �� ��������! � ����� �������� ��� ���� ������, ����� �������� �����.";
			link.l1.go = "PL_Q8_afterPanama_5";
		break;
		case "PL_Q8_afterPanama_5":
			dialog.text = "��. � ������ �������� ������ ���������� ������ - ������� �������� ���������� ������� � ��������� ����, �� ��� � ������ � ���������� ����� ����� ������!";
			link.l1 = "���� ������, ������!!! ����! ������ ��� �����, ������� ������ � ����, ��� � �����, ������� �� ������ � ��������� ����� � ��������� ������� � �������, � ����� ������ � ������������� � �������� ������. ������ ���, ��� ����� ����� ��� � �������!";
			link.l1.go = "PL_Q8_afterPanama_6";
		break;
		case "PL_Q8_afterPanama_6":
			dialog.text = "��, "+ GetSexPhrase("��������","" + pchar.name + "") +". � ��� ��� ������������ ���� ������������ �����. � ������, � ������ ���������, � �� ������� ���������� ��������.";
			link.l1 = "��� ��� ���� ��� ����! �� �� ��� �������� ������������ ��� ���, ��� �������� ������. �, ���� ���� �� ���� ����� �������������, �� � ��� ��� ���� �����: ����� �����-������ ���� ��� �� ������������ � ������� ���������� ������, �������� �� ���� ��������� ���� ����� �� ������ ����. � ����� �� ��������� �� ���� � ���� ������������ ������, � ������ ����� ��������� � ����� ������, ����� ������� �� ���������� ������ ������ ����������� ���������!";
			link.l1.go = "PL_Q8_afterPanama_7";
		break;
		case "PL_Q8_afterPanama_7":
			dialog.text = "�� ������ �� �����"+ GetSexPhrase("","�") +"! � �������� � �� ����, � �� ����, � �� ���� �������, ��� ����� ���� ������� ������! ���������� �������� ������ ���, ������, ��� � ��� ��������. � ������ �������� ����������� �������� ���� �������! � ���, ��� �� ������� ����������� - ���� ������.";
			link.l1 = "�� ��� �� ������ �������? ��� ��� �� ���� ����� �� �������, ��� � ����� ������ ����������. ��� ��������� ������� �� ����������� � �������� ���������, ������������ ������� ��� �� ��� �����������.";
			link.l1.go = "PL_Q8_afterPanama_8";
		break;
		case "PL_Q8_afterPanama_8":
			dialog.text = "����, " + PChar.name + ", �� ������� � ����. � ���� ������ �� ������, �� ���� ������!";
			link.l1 = "��� ������� � � ������ ���� �����! � ���� ��������� ��� ��������� ���� �� ������, ���� �� ������� �� ��������� �� ������ ����������� ������, � ����� ���� ������� � ������ � ��������� ����! � �� ���� ��� �� ������ ����������� �� ����� �� ����� ��������� ������� � ��� ���� � ��������� �� �������, ����� ��� " + GetFullName(PChar) + " ��� ����"+ GetSexPhrase("��","��") +" �� ���� ������� �������!";
			link.l1.go = "PL_Q8_afterPanama_9";
		break;
		case "PL_Q8_afterPanama_9":
			dialog.text = "��, ��� ������... �� ���"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("","�") +" ���� ������.";
			link.l1 = "������, �����, �� �����. � �������� �� ���� ����� ������ �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "over";
            AddQuestRecord("Pir_Line_8_Panama", "14");
	    AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("��","���"));	
            CloseQuestHeader("Pir_Line_8_Panama");
		break;
		
		//*************************** ����� "������������� ������ "�����"" **********************
	
		case "Andre_Abel_Quest_Morgan_Dialog_1":
			dialog.text = "� ���� �� ��� ����?";
			link.l1 = "��, �������. ������ �������� �������� ����� ����� ���� ������.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_2";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_2":
			dialog.text = "������� ���� �������, � ���� ���� �������.";
			link.l1 = "�� ������� � �������� �� ����� ����� �����?";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_3";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_3":
			dialog.text = "����� �����, ����� �����... ���-�� � � �� ������... �� ��������, ���� �� ��������.";
			link.l1 = "���������� �����. ������� ��� ���������� ����� ����, ��� ����� ��������� ������� ��� 50 ��������� �� ����� �������.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_4";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_4":
			dialog.text = "��! ��������!.. �� �� �����! ��-��-��!.. ������ �� ������� ���� ������ ���� ������?";
			link.l1 = "����� ���������� ��������� ������� �� ���������� �� ����, � ������ ����������������� �� ���� ����� ���������, �� ��� � ������� ������ �� �����.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_5";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_5":
			dialog.text = "��� ������, ������� " + GetFullName(pchar) + ", �� ���� ������� �������� �������� � ��������� ��������?..\n"+
                          "��� �, � ����� �������� � �� ��������, �� ��� �������, ��� �� ��������� ���� ��� ���������... ������ �� ������, ��� �������.";

			link.l1 = "� � ����� ������ ��� ����?";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_6";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_6":
			dialog.text = "��� �����, ����� �� ��������"+ GetSexPhrase("","�") +" ����������� ������ �������-����������� ������� - ������ ����������.";
			link.l1 = "���, �������� �������!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_9";
			link.l2 = "��������, �������, �� � ���� ���� ���������� ������ �����...";
			link.l2.go = "Andre_Abel_Quest_Morgan_Dialog_7";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_7":
			dialog.text = "��, ������ ����� �����? ������, �� �������� ��������� �������� �� ����� ������� �� ���� '������� ��������' �����, � ����� ����, ��� �, ������������ ������ ����������, ����� ��� ������, �� ��� ���� ����� � ����� ������� �� �������?..\n"+
                          "�� ��� �� �����������. ������.";
			link.l1 = "����� ���, �� � ���� ���� ���� ���� ��������. � �� "+ GetSexPhrase("�������","�������") +" �� ����������...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_8";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "12");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("��","���"));
			ChangeCharacterAddressGroup(CharacterFromID("Andre_Abel"), "none", "", "");
			PChar.QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek = true; // ���� ��� ��������� � ����������� � ����-�-������
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_9":
			dialog.text = "�� ��� � �������. ������� �� ���������� � ���� 10 ����. ����� ����� ������, ��� ��� ����������.";
			link.l1 = "������, ����������� ����������.";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_10";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_10":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			Log_TestInfo("�������� ������ �� ����� �������.");
			GiveItem2Character(PChar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_Andre_Abel_Quest_Letter_1");
			AddQuestRecord("Andre_Abel_Quest", "14");
			QuestSetCurrentNode("hol_guber", "Andre_Abel_Quest_Hol_Gov_Node_1");
			SetFunctionTimerCondition("Andre_Abel_Quest_Curasao_10Days_Left", 0, 0, 10, false);
			SetFunctionLocationCondition("Andre_Abel_Quest_In_Curacao_Townhall", "Villemstad_townhall", false);
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_11":	// ������ � ������
			dialog.text = "��� ������ ���� ���"+ GetSexPhrase("��","��") +" � ��������"+ GetSexPhrase("��","��") +"... �� ���, ������ ��������"+ GetSexPhrase("","�") +"?";
			link.l1 = "��, ��������"+ GetSexPhrase("","�") +". ������ �� ��� ���� �������� � ������ � ������ ��������!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_12";
		break;
		
		case "Andre_Abel_Quest_Morgan_Dialog_12":
			dialog.text = "��, � ����, ��� �������-���������� ������� ����� ����������� ��������. ��, ���� ���� ����� �� ������, ����� �� ������...\n"+
                          "�� � ���, ��� ���� ������� ���������.";
			link.l1 = "� �� ��� � ���"+ GetSexPhrase("","�") +"! �� ���� � ����������� �� ������...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_13";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_13":
			dialog.text = "�����, �����... ���� �� ��� ���� ��� ������, � ������ �� ������ �� ����� ���������, ������, � ������ �������, ��� �� �������� �� ���������. � �� - ����, ��� �������, ������������������.";
			link.l1 = "���, ������, � ��� ����������� ��� ������...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_14";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_14":
			dialog.text = "�� �����, ������!.. � ���������� �� ���������� � ���, ��� ���� ������� ��������� ���"+ GetSexPhrase("��","��") +". � ����� �������� ���������������� ������ ������ �������� ����. ��������� ����� �������, ��� ����� ��������� ����������...\n"+
                          "��� ������ ��������. ��� � �������������� - ������ �� ������.";
			link.l1 = "������� � �� ����...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_15";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_15":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			Log_TestInfo("�������� ������ �� ����� �������.");
			GiveItem2Character(PChar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_Andre_Abel_Quest_Letter_2");
            AddQuestRecord("Andre_Abel_Quest", "21");
	    AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("��","���"));
	    AddQuestUserData("Andre_Abel_Quest", "sSex1", GetSexPhrase("","�"));
            QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_7");
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_16":	// ���������� �� ������ � ����������
			dialog.text = "��� ������ ���� ���"+ GetSexPhrase("��","��") +" � ��������"+ GetSexPhrase("��","��") +"... �� ���, ������ ��������"+ GetSexPhrase("","�") +"?";
			link.l1 = "��������"+ GetSexPhrase("","�") +"... ������ ���� � ������ �� ������"+ GetSexPhrase("","�") +"!";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_12";
		break;
			
		case "Andre_Abel_Quest_Morgan_Dialog_17":
			dialog.text = "� ������?! ��������� �����������, ��� � ����� - �������� ���������� � ������... �� �����... ������� - �� ��������"+ GetSexPhrase("","�") +" ������, � ��� ������, ��� �� ��������"+ GetSexPhrase("","�") +" ��� ���������.";
			link.l1 = "�?...";
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_14";
		break;

		
// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("���"+ GetSexPhrase("��","��") +" ��� ������!", "��� �� ����� ��������!");
			link.l1 = "��...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //����������� � �������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "��� �� ����� ��������� ���� �� ���� ������� �����������. ������ ��������� ����� ���� ����� ���������...";
        			link.l1 = "� �����"+ GetSexPhrase("","�") +", ������.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("�� ���� ������� ������"+ GetSexPhrase("","�") +", �������� �������.", "� �� ���� � ����� ��������, ��� ��� ���� ����� ���� �� ����������.");
			link.l1 = RandPhraseSimple("�� ��� ������...", "��, �� ��� ��...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� � �������� ����� 20 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "�������, ������ �� �� ������ �������� ���� ������� �����������, ����� ��� �������� ���� �����. ���������, ��� ��� ����� ����� ���������.";
        			link.l1 = "�� ����, ������.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
			if (Pchar.location == "SentJons_HouseF3")
			{
				DoReloadCharacterToLocation("SentJons_town","reload","houseF3");	
			}
			else
			{
				DoReloadCharacterToLocation("PortRoyal_town","reload","houseS1");	
			}
		break;
// <<<<<<<<<<<<============= ���� ��� angry =============================
	}
}

