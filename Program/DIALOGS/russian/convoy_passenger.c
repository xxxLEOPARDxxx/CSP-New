//�������� �� ��������
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("�-�-�, ����!! � ����, ��� �� "+ GetSexPhrase("�����","�����") +"! ������ ������ ����� ����� ����� � ���� �� ���� ����������. ������!", "�-�, � ����, ��� �� ����! � ���� �� ���� ��� ���� �� ������. ��� ������...");
				link.l1 = RandPhraseSimple("���, ��������� �����...", "�������� ����� ����� �����!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! � "+ GetFullName(NPChar) + ". � ������, ��� �� ������ �� ���� ����������?";
				link.l1 = "�������� ��, ��� ������� �� ���� ������.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "��� �����, ����� ���� ��������� � ������� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") +
                          ", �� " + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", � �� ��� � ������� ��� " + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + ". ��� �������?";
			link.l1 = "� "+ GetSexPhrase("��������","��������") +".";
			link.l1.go = "convoy_agreeded";
			link.l2 = "�� �����, ��� ��� ��� ���������.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // �� ������ ������ ��� �������
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "������� ���. �� ��������� ���� �������������. ������ � �� �����. ��� ���� �������.";
			Link.l1 = "��������� ���.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//�����
		    chrDisableReloadToLocation = false; //#20180201-01
			AddSimpleRumour(LinkRandPhrase("����� ������� �� ����� " + GetFullName(npchar) + " �������, ��� ����� �������� �������� " + GetMainCharacterNameDat() + ", ��� ��� "+ GetSexPhrase("���","��") +" ��� ������ ������� "+ GetSexPhrase("��������","���������") +" ��� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"�������� �� ����� " + GetFullName(npchar) + " �������, ��� �������� " + GetMainCharacterNameDat() + " ����� ������. "+ GetSexPhrase("��� ��������","�� ���������") +" ��� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " � ������� � �����������.", 
				"� ������, �������, ��� �� ������� �����, ������ ����������. ����� �������� �� ����� " + GetFullName(npchar) + " ����� ������ � ��� ����������."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //��������� �� ��������� �����������
			//--> ������� Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- ������� Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterReputation(pchar, 1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "�������, ����� �����. ����� ��, � ����� ������, � ������ � " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", 
						  RandSwear() + "�������, ������� ����� �������� ���������� ���?! ����� �� ��������� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?" , 
						  RandSwear() + "����������, �������, ��� ���������� ���� ��������� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", � � ���� �������� ������ � ����� �����, ����� ��� ����������!"), 
				RandPhraseSimple("�������, ��� ������ ��� � �������� ���� ���������� ���� ����� ������������. ����� �� ��������� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", "�������, ������ ��� � �������� ��������� ������ � ���� ��������. �����, �������, �� ������ ������ " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?"), 
				RandPhraseSimple(RandSwear() + "�������, ������ ��� � ��������� ��� � ��� �� - ����� �� �������� � " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", "�������, �� �������� ���� ����� ������� �������! ����� �� ��������� ���� � " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"), 
                "����������, �������, ��� ��� �� � ����� ������ �� �����...", "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("����� ���� ��������, ����... "+ GetSexPhrase("���������","����������") +"... ����� 7 ���� �� ����� ������ �� �����.", "�������� " + GetAddress_FormToNPC(NPChar) + ", ������ �� ���� ����������� ��������� ������������� �� ��������� � ���. �� ������ �� ����������, ����� ������ ����� �� �����."),
					RandPhraseSimple("� "+ GetSexPhrase("��������","���������") +" �� ������ ��� ����������... ����� ������ �� ����� �� �����.", "� �������� ������� ���������. ����� ������ �� ����� �� �����."),
					RandPhraseSimple("� � ������ ��� � "+ GetSexPhrase("��������","���������") +" ������� �������� � ���... �� ����� �� ����� ����� ������.", "� ������� ��������� � ������ ���. ����� ������ �� ����� �� �����, ������..."),
					"� �������, " + GetAddress_FormToNPC(NPChar) + ", �� ����� ��� ������� ���������... ����� ���� ���� � �������� ��� �� ����� ����������!", npchar, Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("�-�... ��������... � � "+ GetSexPhrase("�����","������") +" ��� ���. �����, � ����� ��� ����� ���������, � ��������� ���� �� ����������.", "���, �� ���� ��! � ���� �� ������� - �����������!.. �������, ���� ����� ������������� � ���� ������."),
				"������ ���? ��, ���� ��... �������, � �������� ���� � ���� �� ���������.",
				"������ ���? ��� ��� ��������, ��-��... ��� ���, ��������, ���� ���� � ����, ������ ����������� �� ���� �������.",
				"������? �-�, �������, ��� ������ ������� �����������! ��, ������, ��������, � �������� ������... ����� ���������� � ����, " + GetAddress_FormToNPC(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //������ �������
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("������, �� � ������� ������ �� ����� ����������.", "�� ��� ��, ������... �� ������, ��� � ������� ������ ������� ���!", "��, �������� ��� ������ � �������, �� ������ � ����, ��� ������ ������ �������� ����������...");
			Link.l1 = LinkRandPhrase("������������.", "��, ������...", "�����, ����� ����� ���.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("� ���� ������, ��� � ���� ��� ������� ����� ��������.", "� �������, ��� ��� ��� ��������� �������� �� ����� ���������� ����...");
			Link.l1 = "����������.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //��������� �� ��������� �����������
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear() + "����� ��� ����? � �� ������� ���!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "��� ��� ��������? ������ �� ��� �������! ����� � ����!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "���� �... ���� ����� ���� ����� ����� � ������ ������.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear() + "�� ��� ��������� �� ���, "+ GetSexPhrase("��������","��������") +"!";
			Link.l1 = "��� ��� �������, �� ������� ��� ��� �������� - ������ ���!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("����� ��������, ��� ����� ������� " + GetFullName(pchar) + " ������ ��������� ��������� �� ����� " + GetFullName(npchar) + ", �� ����� ������ �� "+ GetSexPhrase("�������","��������") +". � ���� �� "+ GetSexPhrase("������","�������") +" �������. ��� ��� - �������� ������������ �����...", 
				"��, ���� ������� ���?! ������� " + GetFullName(pchar) + " "+ GetSexPhrase("��������","���������") +" ������� �� ����� " + GetFullName(npchar) + ", ���� ��� ��� ���������� �� ��� �������...", 
				"����� �����, �������, ��� �� "+ GetSexPhrase("���������� ��������","���������� ��������") +". ����������, ��� ������� " + GetFullName(npchar) + " ��� ������ �� ����� �������. � �� ���� ������� ��������� ��� �� " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". �� ��, ���������..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterReputation(pchar, -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 10+rand(10));// �������            
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //��������� �� ��������� �����������
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //���� �������� ����� �� ��������� �����
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //�� ������ ������� �������������
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 4.5;
		break;
	}
}