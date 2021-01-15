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
				RandPhraseSimple("�� ������ ��� �����, " + GetAddress_Form(NPChar) + "! �� ��� �������� ���������.", "��� �� ������? ���������� �������� ���� ����� �����!"));

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
				RandPhraseSimple("� �������, �� ���������� ��������� ���� ���������, ��� � �� ���� �� �������!", "�� ���������, ��� ��� ��������?"));

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
				Dialog.Text = "�� ��� � ����� ������������ ��� ����.";
			}
			link.l1 = RandSwear() + "��� ��� � �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
			break
		}
		//����� ����������.
		if (rand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))         //WW  
		{
			Dialog.Text = RandPhraseSimple("�����?!!! ����������, �� �� ������ ������������ �������.", "�����? ������� ����� �����! �����!");
			link.l1 = RandPhraseSimple("��-��...", "� ���� � ���������...");
			link.l1.go = "exit";
/**/
			//����� ���� ����������� ������� �������� :)			
			if (rand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))    //WW
			{
				link.l1 = RandPhraseSimple("��, ��� �� ������ ���������!!!", "�� ��� �� ��������?! ������ � ����� ���� ����� �����!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//��������.
		Dialog.Text = RandPhraseSimple("�����, ��������? �������, � �� �����. ����� ������ �� ������ � ����������.", 
			"�� ��, ��������, � �����-�� ������� �� ������?");
		link.l1 = RandPhraseSimple("�� ������ �� ������� ������� � ������.", "� �������� ���� ��� ����� ������, ��������!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " ��� �� ����� ����� � ���� � ����������, ��� �� ��� ��������!", 
				"�����?!! ��, �� � �������� ���� ��� �����! �������, ��� �� ������!");
			link.l2 = RandPhraseSimple("� ���� ��� ��� ������.", "��� ������� ������ �� ��� ���� ������ ������!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "� ���������"+ GetSexPhrase("","�") +"...";
		link.l3.go = "change_mind";
		break;

	//����� �� ��������� ������ :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("���-�� �� ���� ������ ������� � �����...", "����������, ���� �� ������� ���� ���� �����-������ ������!!!");
		link.l1 = RandPhraseSimple("��� ������...", "...����� � ��� �������.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "��� �, ��� ���� �� ������ �� �����...";
			link.l1 = "����� �� �������� �����.";

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
		link.l3 = "� ���������...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("� �����, ��� ����� ����� �� ��������� ������. ��� ���� ��� ����� " + pchar.questTemp.Duel.WaitTime + " ����. �� ������������!", 
				"��� �� ������ ����� ��� ��������������. ����� ������ �� ������. ����� " + pchar.questTemp.Duel.WaitTime + " ���� � ���� ���.");
			link.l1 = RandPhraseSimple("������� ����� �����! ���������!", "��� �������! �������� ���� ������!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("��� �, ����� �����������.", "�������, �� ����. ���������� �� ��������.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//����������� "������ ������" ���������������
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("������� ����� �����! ���������!", "��� �������! ����� � ������!");
		link.l1 = RandPhraseSimple("��, ���� �� ��� ���������� �������...", "���������! � ������ ���� ����������� � ��!!!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("��� �, ����� �����������.", "�������, �� ����. ���������� �� ��������.");
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
		link.l2 = "���, � �����"+ GetSexPhrase("","�") +" �������� ���� ���������. ���"+ GetSexPhrase("","�") +" ������, �������"+ GetSexPhrase("","�") +".";
		link.l2.go = "change_mind";
		if (rand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))  //WW 
		{
			Dialog.Text = RandPhraseSimple("������, � ��� ������� � �����, ��� ��� ������. ������� ���� ���������", 
				"����! ��� ��� ���!!! ������, "+ GetSexPhrase("����","������") +"!");
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("�� �� ���, ������ ������ ���� ����� ����� �������� ��� ��������������!", "�������� ���� �����, � ������ ��� ����� ����������!"), 
				RandPhraseSimple("���! � ������ �����������!", "�� - ����� ����� �����! ���������� ���� �����!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("��� �, ������"+ GetSexPhrase("��","��") +". ������������.", "����� ����� ����� ������!!"), 
				RandPhraseSimple("�������, �� �����. �� ����� ��������� ����� �� ��������.", "��� ����������� �� ����� ������! �� �������!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//����� ����!
	case "fight_right_now":
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
				RandPhraseSimple("� ����� ������, �� ���� ��� ������ �����������!", "����� ��� ����� ����, ���� � �� ���������."));
		link.l1 = "��� �����...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("���������� ������!", "�������. � �� � ���� ����������."),
				RandPhraseSimple("��� ���� ���� �������?", "�� ���-�� ������?"));
		link.l1 = "� �����.";
		link.l1.go = "peace";
		break;

	//��� � ��� �����.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
