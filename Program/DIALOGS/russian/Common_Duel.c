//navy 26.07.06
//��������� ������...
//� ������� ��� ������ ���� � ��������� ����� �����������... �� ���� ������� �� "outraged"
//���� ��� ������ ���-�� �� (������� ���������) ��� �� ������ �� ���, ������ �� ���� ����.
//��� ���������, �������� ���, ����� ������ ������� ����� �� �����: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//���� �������
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("��� �� ������ ���� ����������, ������"+ GetSexPhrase("��","��") +"?!", "�� ������ ��������� �� ���� �����!"), 
				RandPhraseSimple("�� ������ ��� �����, " + GetAddress_Form(NPChar) + "! �� ��� ������� ���������.", "��� �� ������? ���������� �������� ���� ����� �����!"));

		//��� ����� ������.. ����� ������ ����� :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("��??!! �� � �� ���� � ����� ������ �� ����!", "��??!! �� � �� ���� � ����� ������ �� ����!"), 
				RandPhraseSimple("� ������ � ����� �������!", "� �� �������"+ GetSexPhrase("","�") +" �������� ���������, ������������ � ��������!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("� �� ��� ����"+ GetSexPhrase("","�") +" � ����...", "� ���������"+ GetSexPhrase("��","���") +"..."), 
				RandPhraseSimple("��� ���� ������. ����� ��������.", "� �������"+ GetSexPhrase("��","���") +", " + GetAddress_FormToNPC(NPChar) + ". ����� ���� ��������.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,  
				RandPhraseSimple("� ���� ��� ������!", "� ������ ���� ������!"), 
				RandPhraseSimple("� �������, �� ���������� �������� ���� ���������, ��� � �� ���� �� �������!", "�� ���������, ��� ��� ��������?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("�������, ���� ����� ��� �� ������, ��� ���� ����!", "�� ���� ����� �������� ��� ������."), 
				RandPhraseSimple("� ������� ��� �� �����!", "��� ���� �����!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("�������, � ��� �� �����"+ GetSexPhrase("","�") +" � ������� � ��������!", "�����, �� ����� ��� ����������! ��� ������ �����!"), 
				RandPhraseSimple("� ��� ��������"+ GetSexPhrase("","�") +", ���� ����. ���� ����...", "��! �������, ��� ������� ��� ���������.")), "change_mind");
		break;

	case "let_s_duel":
		//�������� �� ������� �����.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "���� ����� ������� ����������� � �������, � ����� �� ���������.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "�� ��� � ����� ������������ ��� ���.";
			}
			link.l1 = RandSwear() + "��� ��� � �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
			break;
		}
		//����� ����������.
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))         //WW  
		{
			Dialog.Text = RandPhraseSimple("�����?!!! ����������, �� �� ������ ������������ �������.", "�����? ������� ����� �����! �����!");
			link.l1 = RandPhraseSimple("��-��...", "� ���� � ���������...");
			link.l1.go = "exit";
/**/
			//����� ���� ����������� ������� �������� :)			
			if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))    //WW
			{
				link.l1 = RandPhraseSimple("��, ��� �� ������ ���������!!!", "�� ��� �� ��������?! ������ � ����� ���� ����� �����!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//��������.
		Dialog.Text = RandPhraseSimple("�����, ��������? �������, � �� ������ ���������.", 
			"�� ���� �� ������ ����� �������� ����� �������?");
		link.l1 = RandPhraseSimple("�� ������ �� ������� ������� � ������.", "� �������� ���� ��� ����� ������, �����"+ GetSexPhrase("���","���") +"!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " ��� �� ����� ����� � ���� � ����������, ��� �� ��� ��������!", 
				"�����?!! ��, �� � �������� ���� ��� �����! �������, ��� �� ������!");
			link.l2 = RandPhraseSimple("� ���� ��� ��� ������.", "��� ������� ������ �� ��� ��� ������ ������!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "� ���������"+ GetSexPhrase("","�") +"...";
		link.l3.go = "change_mind";
		break;

	//����� �� ��������� ������ :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("���-�� �� ���� ������ ������� � �����...", "����������, ���� �� ������ ���� ���� �����-������ ������!!!");
		link.l1 = RandPhraseSimple("��� ������...", "...����� � ��� �������.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "��� �, ��� ���� �� ������ �� �����...";
			link.l1 = "����� �� ������� �����.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//�� ����
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //���������������� ��� ������ ������ �� �����
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("�������� ���� ������, � �� ���������, ������ ����� ���� �����!", "��, ���� �� ��� ������ �������...");
		link.l1 = RandPhraseSimple("����� ��� ����� ����, ��� ���������� ��������. � ���� ���� �������� �� ���������� ��������. ���������� ��� ����� " + iHour + " ����.",
			"��... �� ��� ������. ����� ���� ����� ������ ��� ����������. ������� ����� " + iHour + " ���� � ����� � �����.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("��, ���� �� ��� ���������� �������...", "���������! � ������ ���� ����������� � ��!!!");
		link.l2.go = "fight_right_now";
		link.l3 = "� ���������"+ GetSexPhrase("","�") +"...";
		link.l3.go = "change_mind";

		if (drand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("� �����, ��� ����� ����� �� ��������� ������. ��� ���� ��� ����� " + pchar.questTemp.Duel.WaitTime + " ����. �� ������������!", 
				"��� �� ������ ����� ��� ��������������. ����� ������ �� ������. ����� " + pchar.questTemp.Duel.WaitTime + " ���� � ���� ���.");
			link.l1 = RandPhraseSimple("������� ����� �����! ���������!", "��� �������! �������� ���� ������!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("��� �, ����� �����������.", "�������, �� ����"+ NPCharSexPhrase(NPChar,"","�") +". ���������� �� ��������.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//����������� "������ ������" ���������������
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("������� ����� �����! ���������!", "��� �������! ����� � ������!");
		link.l1 = RandPhraseSimple("��, ���� �� ��� ���������� �������...", "���������! � ������ ���� ����������� � ��!!!");
		link.l1.go = "fight_right_now";
		if (drand(1))
		{
			Dialog.Text = RandPhraseSimple("��� �, ����� �����������.", "�������, �� ����"+ NPCharSexPhrase(NPChar,"","�") +". ���������� �� ��������.");
			link.l1 = RandPhraseSimple("��� ���� ���.", "�� ���������.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//��� �, ������ ������
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//���?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//�������� �� �������.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//�� ������, ���� �� ��������, ���� ������ ����������
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // ���� �� ���� ������ � ������
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // ���� �� ����� �� �����
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//��������� ����� ����� ����
	case "talk_off_town":
		Dialog.Text = "�� ���, �� �����"+ GetSexPhrase("","�") +" ����������� � ��?";
		link.l1 = "��. ������ ���������, ��� ����!";
		link.l1.go = "fight_right_now";
		link.l2 = "���, � �����"+ GetSexPhrase("","�") +" �������� ���� ���������. ���"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("","�") +", �������"+ GetSexPhrase("","�") +".";
		link.l2.go = "change_mind";
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))  //WW 
		{
			Dialog.Text = RandPhraseSimple("������, � ��� �������"+ NPCharSexPhrase(NPChar,"","�") +" � �����"+ NPCharSexPhrase(NPChar,"","�") +", ��� ���"+ NPCharSexPhrase(NPChar,"","�") +" ������"+ NPCharSexPhrase(NPChar,"","�") +". ������� ���� ���������", 
				"׸��! ��� �� ���!!! ������, "+ GetSexPhrase("����","������") +"!");
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("�� �� ���, ������ ������ ���� ����� ����� �������� ��� ��������������!", "�������� ���� �����, � ������ ��� ����� ����������!"), 
				RandPhraseSimple("���! � ������ �����������!", "�� - ����� ����� �����! ���������� ���� �����!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("��� �, ������"+ GetSexPhrase("��","��") +". ������������.", "����� ����� ����� ������!!"), 
				RandPhraseSimple("�������, �� �����. �� ����� ��������� ����� �� ��������.", "�� ����������� �� ����� ������! �� �������!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//����� ����!
	case "fight_right_now":
		if(findsubstr(npchar.id, "PsHero_" , 0) != -1)
		{
			LAi_SetCheckMinHP(npchar, 1, true, "PGG_CheckHPDuel");
			SaveCurrentQuestDateParam("pchar.questTemp.DuelCooldown");
			chrDisableReloadToLocation = true;
		}
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	                  //WW  ?????
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//���������, �... �� ������ ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("����� ���������� ������!", "������� �����. � �� � ���� ����������."), 
				RandPhraseSimple("� ����� ������, �� ���� ��� ������ �����������!", "����� ��� ����� ����, ���� � �� ���������"+ NPCharSexPhrase(NPChar,"","�") +"."));
		link.l1 = "��� �����...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("���������� ������!", "�������. � �� � ���� ����������."),
				RandPhraseSimple("��� ���� ���� �����"+ NPCharSexPhrase(NPChar,"��","��") +"?", "�� ���-�� ������?"));
		link.l1 = "� �����.";
		link.l1.go = "peace";
		break;

	//��� � ��� �����.
	case "peace":
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
		
	case "Duel_Won":
		LAi_SetCurHPMax(npchar);
		Dialog.text = "���������! � ������.";
		link.l1 = "� ������� "+GetSexPhrase("������","������")+". ���� ������.";
		link.l1.go = "duel_nomoney";
		link.l2 = "�������. � ������ ����������� �������!";
		link.l2.go = "duel_money";
		NextDiag.TempNode = "Second time";
		break;
	case "duel_nomoney":
		ChangeCharacterReputation(pchar, 10);
		PGG_ChangeRelation2MainCharacter(npchar, 20);
		Dialog.text = "���������, �� ��� ��������? �� �����, ��� ��������"+NPCharSexPhrase(npchar, "","�")+ " �� �����, ���� � �� ���� �����. � ����� �� ������.";
		link.l1 = "��� �����, ���� � �� ���������"+GetSexPhrase("","�")+".";
		link.l1.go = "duel_exit";
		break;
	case "duel_money":
		ChangeCharacterReputation(pchar, -25);
		PGG_ChangeRelation2MainCharacter(npchar, -30);
		AddMoneyToCharacter(pchar, sti(npchar.money)/3);
		AddMoneyToCharacter(npchar, -sti(npchar.money)/3);
		Dialog.text = "�� ��, "+GetSexPhrase("��������","��������")+"! �� ������, � ��� � ����� ����������.";
		link.l1 = "���� ����� � �����������.";
		link.l1.go = "duel_exit";
		if (!CheckAttribute(npchar, "PGGAi.Boosted"))
		{
			Train_PPG(npchar, true, true);
		}
		break;
	case "duel_exit":
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), npchar.PGGAi.location.town+"_Tavern", "", "", "", 10.0);
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetImmortal(npchar, false);
		DialogExit();
		break;
		
	case "TreasureHunterPGG":
		NextDiag.CurrentNode = "Second time";
		//dialog.text = "������-��, "+ GetSexPhrase("��������","�������") +"... �������, � ���� ���� ���-��� ����������. ����� �������� � �������� ��������� �����������.";
		dialog.text = RandPhraseSimple("� ��� � ����������" + npcharSexPhrase(npchar,"","�") + ", ��� ���� ����� ������ ������ ����� �����. �� ��� � ��� ����" + npcharSexPhrase(npchar,"","�")+".","������-��, "+ GetSexPhrase("��������","�������") +". ��� ����� - ���. �� ����, ��� ������ ��� � ���� ���������, �� � ���� � ������ �� ����� ���� �����. ��� ��� ��� ��������� ���� �� �����������. ");
	    //if (PGG_ChangeRelation2MainCharacter(npchar, 0) < 41)
		if (sti(npchar.reputation) < 41)
		{
			dialog.text = "�� ���"+GetSexPhrase("","�")+" ��������� ����"+GetSexPhrase("","�")+", ��� �� �������"+GetSexPhrase("","�")+" ������ ������ �� ������ ���������";
			Link.l1 = "�� ��� ��, ������ ����� ���������� ����� ������ �� ����.";
			Link.l1.go = "battleTreasure";
			break;
		}
		Link.l1 = "�� ��, �������� ��������. ���" + npcharSexPhrase(npchar,"","�") + " ���������, ������ ��� � ���� ���� �� �����, ���� ��� ��� ����� �� ����� ���������, �� � ���� ���� ��� �� �������. �� ��������� � ����� � �� �����. ��������� ��������� ������.";
		Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
        Link.l2 = "�� ��� ��, ������ � ����� ������, �� ������� ����. � ������ ����� � ������!";
		Link.l2.go = "NoMoney_1";
		break;
	case "battleTreasure":
        AddDialogExitQuest("Battle_PGGHunters_Land");
		PChar.quest.PGGbattleTreasure.win_condition.l1 = "NPC_Death";
		PChar.quest.PGGbattleTreasure.win_condition.l1.character = npchar.id;
		PChar.quest.PGGbattleTreasure.function = "T102_DoorUnlock";
        DialogExit();
        break;
	case "Cost_Head":
			PChar.HunterCost = MOD_SKILL_ENEMY_RATE/4 * sti(npchar.rank) * 1000 + rand(1000);
			dialog.text = "���� ���? � ��� ���"+ NPCharSexPhrase(NPChar,"","�") +" �����"+ NPCharSexPhrase(NPChar,"","�") +" �� ������ �������\n�� ��� ��, � �� ������. �����, ��� " + sti(PChar.HunterCost) + " �������� ���� �������.";
			if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "� ���� ��� ����� �����.";
                Link.l1.go = "NoMoney";
            }
			else
			{
                Link.l1 = "��� � ����, �������.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "����� ����� ��������, ��������� ����... �� ����� � ���� ������ ������!!!";
                Link.l2.go = "NoMoney";
            }
	break;	
	case "NoMoney":
			dialog.text = "� ����� ������ �������� �������!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "������ �� ��.";
			Link.l1.go = "battleTreasure"; 
		break;
	case "NoMoney_1":
			dialog.text = "�� �� ���! ������ �� � ���� ������ �� �����!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "� ����� ������, ������ ����� ���������� ����� ������ �� ����.";
			Link.l1.go = "battleTreasure"; 
	break;
	case "Cost_Head2":
        AddMoneyToCharacter(pchar, -(sti(PChar.HunterCost)));
		PGG_AddMoneyToCharacter(npchar, (sti(PChar.HunterCost)));
		ChangeCharacterReputation(pchar, 15);
		PGG_ChangeRelation2MainCharacter(npchar, 40);
		chrDisableReloadToLocation = false;
        dialog.text = "� �� "+GetSexPhrase("�������� �����","������� ��������")+"! ��������� �� ���������. �������, �� ��� ����������, � �� � ����� ���������"+ NPCharSexPhrase(NPChar,"","�") +" ������-������.";
		Link.l1 = "���������� �����������. ���� ���������� ������ - ����������� ������!";
		Link.l1.go = "Cost_Head3";	
        break;
	case "Cost_Head3":
        AddDialogExitQuest("GoAway_PGGHunters_Land"); 
        DialogExit();
        break;
		
	case "Play_Game":
		bool allow = false;
		if (!CheckAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index)) allow = true;
		if (GetQuestPastDayParam("questTemp.pgggamesplayed"+npchar.index) > 0) allow = true;
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 40 && allow)
		{
			DeleteAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index);
			dialog.text = "��� �����������?";
			link.l1 = "����������� � �����?";
			link.l1.go = "Card_Game";
			link.l2 = "�������� �������?";
			link.l2.go = "Dice_Game";
			link.l10 = "����� ��������, �� ���� ���� ����.";
			link.l10.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase ("����� � ����, �� �� � �����", "������, �� �� ���� ������!", "������ ���? " + LinkRandPhrase("� ��� �� ��������"+ NPCharSexPhrase(NPChar,"","�") +".", "�� ��� ���� ��������"+GetSexPhrase("","�")+".", "� ������ �� � ��� ����������, ������."));
			link.l10 = "��� ������, ���� ����.";
			link.l10.go = "exit";
		}
	break;
	// ����� -->
	case "Card_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			dialog.text = "��� ������, � �� � ����������.";
			link.l1 = "��� ������.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "�� �����, �������...";
			link.l1 = "������������.";
			link.l1.go = "Cards_begin";
			link.l2 = "�� ����� �������� ������?";
			link.l2.go = "Cards_Rule";
		}
	break;

	case "Cards_Rule":
		dialog.text = CARDS_RULE;
		link.l1 = "��� �, ������!";
		link.l1.go = "Cards_begin";
		link.l3 = "���, ��� �� ��� ����...";
		link.l3.go = "exit";
	break;

	case "Cards_begin":
		Dialog.text = "����� ����������� �� �������.";
		link.l1 = "������ �� 500 �����.";
		link.l1.go = "Cards_Node_100";
		link.l2 = "����� �� 2000 �������.";
		link.l2.go = "Cards_Node_500";
		link.l3 = "�������, ��� ����.";
		link.l3.go = "exit";
	break;

	case "Cards_Node_100":
		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "������ ��������? � ���� ��� �����!";
			link.l1 = "������.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "������ � ����, � �� �� ���������� ������� �� ���������...";
			link.l1 = "����.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "������, ������ �� 500 �����.";
		link.l1 = "������!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 500;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_Node_500":
		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "������ ��������? � ���� ��� ����� �� ����� ������!";
			link.l1 = "�����!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "���, ����� ������ �� ������� �� �����.";
			link.l1 = "��� ������.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "������, ������ �� 2000 �����.";
		link.l1 = "������!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 2000;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchCardsGame();
	break;
	// ����� <--
	//  Dice -->
	case "Dice_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			dialog.text = "����� ������, � �� � ����������.";
			link.l1 = "��� ��� ����� ������.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "�����! ����� ������� �� ������ ��������... ������ ��������...";
			link.l1 = "������������.";
			link.l1.go = "Dice_begin";
			link.l2 = "�� ����� �������� ����?";
			link.l2.go = "Dice_Rule";
		}
	break;

	case "Dice_Rule":
		dialog.text = DICE_RULE;
		link.l1 = "��� �, ������!";
		link.l1.go = "Dice_begin";
		link.l3 = "���, ��� �� ��� ����...";
		link.l3.go = "exit";
	break;

	case "Dice_begin":
		Dialog.text = "����� ����������� �� �������.";
		link.l1 = "������ �� 200 ����� �� �����.";
		link.l1.go = "Dice_Node_100";
		link.l2 = "����� �� 1000 ������� �� �����.";
		link.l2.go = "Dice_Node_500";
		link.l3 = "�������, ��� ����.";
		link.l3.go = "exit";
	break;

	case "Dice_Node_100":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "� ���� ����� ����� �������������"+ GetSexPhrase("��� ������","�� ������") +". � �� ���� � ����� ������ � ����� ������.";
			link.l1 = "��� ����! �� � �� �����.";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "������ ��������? � ���� ��� �����!";
			link.l1 = "������.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "���! ����� ���������� � ������, � �� ������� � ����������� � ������ �� �����...";
			link.l1 = "����.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "������, ������ �� 200 �����.";
		link.l1 = "������!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 200;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_Node_500":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "� ���� ����� ����� �������������"+ GetSexPhrase("��� ������","�� ������") +". � �� ���� � ����� ������ � ����� ������.";
			link.l1 = "��� ����! �� � �� �����.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckDiceGameBigRate())
		{
			dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
			link.l1 = "����� �� ����� ������ �������?";
			link.l1.go = "Dice_Node_100";
			link.l2 = "������, ��� ����.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "������ ��������? � ���� ��� ������� �����!";
			link.l1 = "�����!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "���, ����� ������ �� ������� �� �����.";
			link.l1 = "��� ������.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "������, ������ �� 1000 ����� �� �����.";
		link.l1 = "������!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 1000;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchDiceGame();
	break;
	
// ����� ��� ������
	case "Quest_Whisper":
		npchar.QuestWhisper = true;
		chrDisableReloadToLocation = true;

		Dialog.Text = "���� ���������, � �� ����� ��������� ��� ��� ����. ��������� � ���� � �������?";
		link.l1 = "�� �����.";
		link.l1.go = "Quest_Whisper_Room";
	break;
	
	case "Quest_Whisper_Room":
		DoReloadCharacterToLocation(npchar.PGGAi.location.town + "_tavern_upstairs","goto","goto1");
		ChangeCharacterAddressGroup(npchar, npchar.PGGAi.location.town + "_tavern_upstairs", "goto", "goto1");
		pchar.InstantDialog = npchar.id;
		
		npchar.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		npchar.dialog.currentnode   = "Quest_Whisper_1";
		DoQuestFunctionDelay("InstantDialog", 1.1);
		DialogExit();
	break;
	
	case "Quest_Whisper_1":
		dialog.text = "����, ������ ���������, �� ���, ������� �� ������ ������, ����� �����.";
		link.l1 = "� ������.";
		link.l1.go = "Quest_Whisper_2";
	break;
	
	case "Quest_Whisper_2":
		dialog.text = "�� ���, �� �����"+ GetSexPhrase("","��")+" �� ����� �����?";
		link.l1 = "...";
		link.l1.go = "Quest_Whisper_2_exit";
		for (int i = 1; i < 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, false));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
		}
	break;

	case "Quest_Whisper_2_exit":
		DialogExit();
		sld = CharacterFromId("PGG_Whisper_Incquisitor3");
		sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		sld.dialog.currentnode   = "Quest_Whisper_3";
		pchar.InstantDialog = sld.id;
		DoQuestFunctionDelay("InstantDialog", 0);
	break;
// <-- ����� ��� ������
	}
}
