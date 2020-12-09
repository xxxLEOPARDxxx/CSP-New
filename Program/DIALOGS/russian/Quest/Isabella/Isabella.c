// boal 27.03.2004 ������� ������ (������������� �����)
void ProcessDialogEvent()
{
	ref NPChar, d, sld, rColony;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i, iMoney, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
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
					//����� ������ ���������� ����� ����
                    if (npchar.angry.name == "NewLife_Budget_Add") Dialog.CurrentNode = "AngryRepeat_Budget_Add";
					//����� ��������� ������, � ��� �� �����
					if (npchar.angry.name == "NewLife_Present") Dialog.CurrentNode = "AngryRepeat_Present";
                break;
				case "quest":
					//����� ����� ������� ��������
					if (npchar.angry.name == "NewLife_Budget_Pay") Dialog.CurrentNode = "AngryRepeat_Budget_Pay";
					//����� ������� �������� �������� ��
					if (npchar.angry.name == "NewLife_KnowPirates") Dialog.CurrentNode = "AngryRepeat_KnowPirates";
				break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= ���� angry ===================================
// ============================================================================	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			//��� � �������
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			// ���������� �� �����, � �� ��� ������� � ����� �������
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
            dialog.text = "��� �� ���� ������? ���� �� ���������� �� �������� ��� �������, � ������ ����.";
			link.l1 = "� " + GetFullName(pchar) + ". ���� � ������ ��� ����� ���������� ���������?";
			link.l1.go = "Next_1";
			link.l2 = "����� ���� ��������. � ��� �����...";
			link.l2.go = "exit";
		break;
		
		case "Next_1":
			NextDiag.TempNode = "Next_2";
			
            dialog.text = "�������, � �� ���������. � - ������� ����� ����, "+ NPChar.Name + " " + NPChar.LastName +
                          ". ����� �� ��������� � ��� �����?";
            link.l1 = "�����������, �������, � - ��������� ������ ����. �� ��������� ��� ��������� ��� ����� ���, � ����� ��� ����� ������, ��� ����������� ������ ��������.";
			link.l1.go = "Next_4";
			link.l2 = "������� �����������. � ��� �����.";
			link.l2.go = "exit";
		break;
		
		case "Next_2":
			NextDiag.TempNode = "Next_2";			
            dialog.text = "�� ��� �����? �������� ���� � �����!";
            link.l1 = "���� � ������ ���-���?";
			link.l1.go = "Next_3";
            link.l2 = "��������...";
			link.l2.go = "exit";
		break;
		
		case "Next_3":
			NextDiag.TempNode = "Next_2";			
            dialog.text = "��� ��� �� ���� �����? ���������� � ���� �����. � �� ���� ������������� � ���� ������.";
            link.l1 = "������, � ��� � ��������.";
			link.l1.go = "exit";
		break;
		
		case "Next_4":
            dialog.text = "��, �� ������� ������ ���� ���. � ����� ����� ���� � ��� � ���� �����?";
            link.l1 = "���� �������� ������������ � ������������ ����� ������� ��������� ������.";
			link.l1.go = "Next_5";
            link.l2 = "�� � ��� ������ ������.";
			link.l2.go = "Next_6";
			link.l3 = "������ �����������. ��������.";
			link.l3.go = "Next_7";
		break;
		
		case "Next_5":
            dialog.text = "��������... ������������... ������������... - � �� ����� ������� ������. ��, �� �����. ��� ��� �������� ��� ���? ����� ��������� � ����.";
            link.l1 = "������ ����������! � ��� ����� ���������� ����!";
			link.l1.go = "Next_8";
            link.l2 = "������ ������, �� ����������. ����� ������� � ����� � ���������� �������.";
			link.l2.go = "Next_9";
			Pchar.RomanticQuest.TalkInShop = true;
		break;
		
		case "Next_6":
            dialog.text = "������? �� �����, ��� � ����� ���� ����� ���� ����� ������. "+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = "���������! � ��� �������...";
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;
		
		case "Next_7":
			dialog.text = "�� ��� �� ���������. �����, ����� �����, ���� � ������ ����. "+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = "���������! � ��� �������...";
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;
		
		case "Next_8":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "� ��������. �� ������ ����������� � ���� ����, ������.";
            link.l1 = "� ������ ������ ������. � ������ ��������� �����������, �� ���� ��� ������...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
		break;
		
		case "Next_9":
		    NextDiag.TempNode = "Next_2";
            dialog.text = "��-�����, �� ������ ����������� ������!";
            link.l1 = "��... ��������� ������ �����...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -4);
		break;
		
		case "Good_1":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "���� ����� �������. ������ ��������?";
            link.l1 = "������ ����� ���������������� ���, ���������� "+Npchar.Name+".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		
		case "Romantic_Battle_in_Bedroom":
		    NextDiag.CurrentNode = "Next_2";
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_1");
		break;
		
		case "Murder":
		    NextDiag.TempNode = "Murder";
            dialog.text = "�������� ����, ������� ������!";
            link.l1 = "...";
			link.l1.go = "exit";
			PChar.quest.Romantic_TalkInShop.over = "yes";
		break;
		
		case "TalkInShop":
		    NextDiag.TempNode = "TalkInShop_2";
            dialog.text = "������� "+GetFullName(PChar)+"!";
            link.l1 = "�������! ����� �������� �������!";
			link.l1.go = "exit";
			//AddDialogExitQuest("Romantic_TalkInShop_3");
		break;
		
		case "TalkInShop_2":
            dialog.text = "���� ����, �������, �������� ���!";
            link.l1 = "�� ������, ��� ���� ������� �������� ��������!";
			link.l1.go = "TalkInShop_3";
		break;
		
		case "TalkInShop_3":
            dialog.text = "�� ���� ��� ������ ��������� �������������.";
            link.l1 = "����� ���������� ���, ��� ���������?";
			link.l1.go = "TalkInShop_4";
		break;
		
		case "TalkInShop_4":
            dialog.text = "� ������ ������, ������ ������� ��� �� �������� ��������, ��� ���� ���������. � ���� �������, ��� ��� ������ �������� ������� "+
                          GetCharacterFullName("SanJuan_trader")+". ��, ������, �� �������. ���������, ��� � ��� ���� �� ����� �����. � ���� �� ��������� � ����� 1200 �������. � �������, ��� ������� �� �����, � ������ " +
                          GetCharacterFullName("SanJuan_trader")+" �����, ��� � � ����� ����������� �������.";
            link.l1 = "(��������) ������ ���� ������, ��������� ������.";
			link.l1.go = "TalkInShop_5";
			link.l2 = "(��������) ��, ������-�� �� ��� �������, �� ��� ��?";
			link.l2.go = "TalkInShop_6";
		break;
		
		case "TalkInShop_5":
            AddMoneyToCharacter(pchar, -1200);
		    NextDiag.TempNode = "Good_1";
            dialog.text = "���, �����, �������, �������. � ������ �� ����� ��� ������. � ������ ��� ����.";
            link.l1 = "������, ������� ��������. � ������ ������������ ���, ��� ���� ������� ��������� � ����.";
			link.l1.go = "TalkInShop_Go";
		break;
		
		case "TalkInShop_6":
            NextDiag.CurrentNode = "TalkInShop_7";
			DialogExit();
			characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_2";
			AddDialogExitQuest("Romantic_TalkInShop_3");
		break;
		
		case "TalkInShop_7":
		    NextDiag.TempNode = "Good_1";
            dialog.text = "��������� ���. �� ��� ����. �� ��������.";
            link.l1 = "������, ������� ��������. � ������ ������������ ���, ��� ���� ������� ��������� � ����.";
			link.l1.go = "TalkInShop_Go";
		break;
		
		case "TalkInShop_Go":
            NextDiag.CurrentNode = "Good_1";
			DialogExit();
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "SanJuan_church", "goto", "goto1", "Romantic_TalkInShop_end", 4.0);
			chrDisableReloadToLocation = true;
		break;
		
		case "TalkInChurch":
		    //NextDiag.TempNode = "TalkInChurch_1";
            dialog.text = "������ �������, � ���� ��� ������. �������, �� �� �� ������� ����� '���� ��� ���������'?";
            link.l1 = "'���� ��� ���������'? ������ ��������, ��� �, ������� �� ������ �� � ������ ������� ���� �������� ����� ������������� ������. �������, ���� ���������� ������� � ����� ������� �� ������ ��� �������, �� � ���� �����������.";
			link.l1.go = "TalkInChurch_1";
			DeleteAttribute(npchar, "talker"); //������� ���������
		break;
		
		case "TalkInChurch_1":
            dialog.text = "��������, �������, � ��������.";
            link.l1 = "��������, c������! ������ �� ��� ��������? ��� ���� ����������-�������, ������ �������� ��� ��� ��������? ���� �����, � ���-�� ������ � ��� � ����� ��� ������?";
			link.l1.go = "TalkInChurch_2";
		break;
		
		case "TalkInChurch_2":
            dialog.text = "� �����, �� ���� �������, ������? ���� '���� ��� ���������' ������ ��� ��� ����� ������� ����� � ������ ���-�����. ����� ����, �������� ����� ������ ��� �� ���� �� ������?";
            link.l1 = "���, c������, � ������ �� ���� � ������ ����� �����, �� ����� ���������� ����������� �� ������ ������ �������� ��������, ���� �� �������� ��� ����-������������ ������.";
			link.l1.go = "TalkInChurch_3";
		break;
		
		case "TalkInChurch_3":
            dialog.text = "��, ������, � ��� ����� �� ����� ��������, �� ������ ��� �������. �� ����� ������ ���� �������� - ��� ���� ��� ������ �� �������. � ������ ��� ������ �� ������ ����� �� ���� �������.";
            link.l1 = "� ������� �������� � ������, ���������� �������!";
			link.l1.go = "TalkInChurch_4";
		break;
		
		case "TalkInChurch_4":
            dialog.text = "� � ����������� ���� ����� �� ��� ������ � �����. �� �������, ��� ��������� ��� ���?";
            link.l1 = "��, �������. ����� �������.";
			link.l1.go = "TalkInChurch_Go";
		break;
		
		case "TalkInChurch_Go":
			chrDisableReloadToLocation = true;
            NextDiag.CurrentNode = "WaitShip";
            Pchar.RomanticQuest.ShipToCumana = true;
			DialogExit();
			AddQuestRecord("Romantic_Line", "5");
			LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 20.0);
            // ������� ������� �����
            TraderHunterOnMap();
		break;
		
		case "WaitShip":
		    NextDiag.TempNode = "WaitShip";
            dialog.text = "���� �����-������ �������?";
            link.l1 = "� ������, ����� ����� ������ ������� '���� ��� ���������'. �� �������, "+Npchar.Name+ ".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// �������� � ������
		case "Brother_1":
            dialog.text = "������! ��� � ���� ���� ������! � ����������� �� ����! �� ���� ��� ����� �� ���� ������! ��� ����?";
            link.l1 = "��������! ���� �� �� ���� ������� �������, �� � ����� ��� �� ���� �� ��������� �� ���-�����. ������� ������ �������� ������ ������ ������� �������. � ������ ������� ����� - ��� ���� ����, ��������! �� ��� �������� ������� ������� ��������, ����� �������� ���� �������. ��� ���� ��� ���� ��������� ��������, � ��� ������ �� ������� �����!";
			link.l1.go = "Brother_2";
		break;		
		case "Brother_2":
            dialog.text = "��, ������! �� � �� �������� ������� ��������! ��� �����-�� ����������� �������������!";
            link.l1 = "������, �� ��� �� ������������� ������ �������������� �������� �� ����� ������� ��������� ��� ������. �������, �� ������ �������� ���� �������� ������� �����.";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_Brother_House_3");
			NextDiag.TempNode = "Brother_3";
		break;		
		case "Brother_3":
            dialog.text = "��, ������� "+GetFullName(pchar)+"! � ���������� ��� �� ����� ������! �������� ����! � ��� ��������� ������� ����, ��� ������ � ���! � ���� ���� ������ ��� ������� ������� � ����� ����!";
            link.l1 = "������� ��������! � ������ � ����� �������. � ������ ����� ���� ��������, � �������� ��� ��������.";
			link.l1.go = "Brother_4";
		break;
		case "Brother_4":
			AddQuestRecord("Romantic_Line", "8");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 5.0);
			NextDiag.CurrentNode = "Temp_Thanks";
			DialogExit();
		break;		
		case "Temp_Thanks":
            NextDiag.TempNode = "Temp_Thanks";
            dialog.text = "�, ������� �������! � ��� ��� ������� � �����!";
            link.l1 = "������������� ����, ������� ��������.";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";			
		break;
		// �������� � �� �� ������ �����
		case "BrigAbordage":
            dialog.text = "��� ��!!! ������������ � ���������� ������! ��� � �����!";
            link.l1 = "�������, � �� ���������, �� ��� ����� �� ��������� �������� ���� ���!";
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
            dialog.text = "�� ������������� ��������! ��������� ��������� ���, ��� �� ����� ����� ����� ����� ������! ��! ������!";
            link.l1 = "� �� ��������? �������! � ������� ����� ������� ���� ���, � �� ���������, ��� � ���� ������ �����? �������...";
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
            dialog.text = "��� ���� �����, � �� �������! � �� ����� ������� ����� ����������!";
			if (CheckCharacterItem(pchar, "Order"))
			{			
				link.l1 = "��� �� � ���� �������������, ��� � ��� �����, ��� ��������� ������� ������ �����. ������ �������, ��� ������ ��������� �������� �������, ������� ������ ����. �� ��������� �������� �� ���� �������, � ����� ��������� ���� ���. � ����� ��������� ������� �� ���� ������ �����. ��� ������ ������ ���� ������, �� ������ �������. ��� ���, ���������...";
				link.l1.go = "BrigAbordage_8";
			}
			else
			{
				link.l1 = "��� �� � ���� �������������, ��� � ��� �����, ��� ��������� ������� ������ �����. ��� ���� �������, ��� ������ ��������� �������� �������, ������� ������ ����. ��� ������ ��������� �������� �� ���� ����������� � ����� ��������� ���� ���. �� ������� ����� � ����, ����� ������� ���� ������������. �� ��� ����� �� ��� �� ��������, � � ����� �������� ����� �� �����.";
				link.l1.go = "BrigAbordage_3";
			}
		break;
		// --> ���� ���������� �������� � �������
		case "BrigAbordage_3":
            dialog.text = "��, �������, �� ������ �������� ������, �� ��� � ������� ����! ��� �� ������ ����������� ������� ����� ����?";
            link.l1 = "�������, � ������������ ����� ������, ��� ��� ���� ����� ������ � ���� ���������� ��������� � �������� ��������. � ����� ������������ ������� �����, ��� ��������� � ���� ����� �������� ������� ������! � ���������, � �� ����� ������ �� ������...";
			link.l1.go = "BrigAbordage_4";
		break;
		case "BrigAbordage_4":
            dialog.text = "�� ������, ����� � �������� ����� ������? � ��� ��� '���������� �������', ��-�� ������� ����� ��� ����?! �������� ��� ��!";
            link.l1 = "� ���� �� ���, �������...";
			link.l1.go = "BrigAbordage_5";
		break;	
		case "BrigAbordage_5":
            dialog.text = "��������, ��� �������� ������������ �������. ��������, �������! � �������� � ������� �������� ���...";
            link.l1 = "������� ��������, � ��� ��� ������� �� ���������, ������� ����� ������ �� ���. � ��������� ���������� ��� ������ � ���� �� �����.";
			link.l1.go = "BrigAbordage_6";
		break;	
		case "BrigAbordage_6":
            dialog.text = "��������, ��, ������� �����! ������� ���� � ���� �� �������� ���� ����� � ����. ���� ��� ������� ���������, �� ����� ��� ����� ����� � ������. � ���, �������, � ��������� �� ��� ����, ������� �� �������� ����� �����!";
            link.l1 = "���� ������, ��������!!";
			link.l1.go = "BrigAbordage_7";
		break;	
		case "BrigAbordage_7":
            dialog.text = "��������, ����� � �� ����� �� �����...";
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.location = "none";
			npchar.location.group = "";
			npchar.location.locator = "";
			AddQuestRecord("Romantic_Line", "17");
			QuestSetCurrentNode("Atilla", "Isabella_Sink");
		break;	
		// --> ���������� ������� - � ��.
		case "BrigAbordage_8":
            dialog.text = "���?!! ���������?!! ��� ������ ����!! �������! ��������� ����� ����... ��������! �� ��� ������... � ���� �������... � ������ ����������... ��� � ����, ����� ��� ��� ������ ���, ������� " + GetFullName(pchar) + ".";
            link.l1 = "������? �������? � ��� �� ��������?";
			link.l1.go = "BrigAbordage_9";
			TakeItemFromCharacter(pchar, "Order");
		break;	
		case "BrigAbordage_9":
            dialog.text = "������� ����� ����� ������ � ��� ��� � �������, ���������� ����� ����������. ��� ����� � �����-�� ���������, ������� ��� ������. �� ������ ���� �������� ���-���� �� ������� ��������, ������������ ������. �� ��� ������ ������� ������� ������ ���-�����, ���� ������� � �����. ������ ������ � ������, ��� ������ � �������!";
            link.l1 = "� ��� ������ ���������? �����, ������ ����� ���������� � ���.";
			link.l1.go = "BrigAbordage_10";
		break;	
		case "BrigAbordage_10":
            dialog.text = "� �� ����, ��� ��� ���... �������, ��� ������ ����������! �������� ���� � �����, � ������, �����������, ��� ��� ��� ��������� - �������� ���� ���� ���!\n"+
				          "���� � ������� ��� �� ������, �������?";
            link.l1 = "���� ��� ������� ���, ������� ��������.";
			link.l1.go = "BrigAbordage_11";
		break;	
		case "BrigAbordage_11":
            dialog.text = "�� ����� �� �� ������� ���� � ���� ������ ������ ��������� � �����?";
            link.l1 = "�������, �������. �� ��������� ���, ��� �� ����� � ����� �����, �������� ���� �����. ��������� ��������� ��� ����������, ���� �� ���� ������ ��������.";
			link.l1.go = "BrigAbordage_12";
		break;	
		case "BrigAbordage_12":
            dialog.text = "������, �������. �� � �����, �� ������ �����, ��������� ���� � ������...";
            link.l1 = "��� ����� ���������, �������.";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			pchar.RomanticQuest = "SeekInPortoBello";
			AddQuestRecord("Romantic_Line", "18");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);			
			//������, ����������� ����������� � ����� �����
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1.location = "PortoBello_houseF2";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition = "Romantic_AmbushInPortoBello";
			//������ ������ � ��� ������
			sld = GetCharacter(NPC_GenerateCharacter("Rosita", "girl_11", "woman", "towngirl", 5, SPAIN, -1, false));
            sld.name 	= "������";
	        sld.lastname = "���������";
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
	        sld.dialog.currentnode = "Rosita";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_houseS4", "goto", "goto2");
		break;	
		//�������� � ���� � ������� � ����� �����
		case "AmbushPortoBello":
            dialog.text = "������ " + pchar.name + ", � ����� � ������� �� ����� ������, ��� � ��� ����.";
            link.l1 = "������� ��������, ��� ������ ������������ ��������...";
			link.l1.go = "AmbushPortoBello_1";
		break;	
		case "AmbushPortoBello_1":
            dialog.text = "���� ���, ��� ����� ���������?!!";
            link.l1 = "��, ��������, ��� ����� �� ������� � ������. ��� - ��� �������, ������� ��������� ������� ���� ��������.";
			link.l1.go = "AmbushPortoBello_2";
		break;	
		case "AmbushPortoBello_2":
            dialog.text = "��� ��������?!";
			link.l1 = "������ ���. ��� ������ ���� �� ���� �������: '��������� ��-������'. ��� �������� ��� ��� - ���������� � ��������� �����, ������� ����� ��� �� ���-�����. �������, ��� ������ �������, ��� � ������� �� ���� ����� � ����� ����������� ���...";
			link.l1.go = "AmbushPortoBello_3";
		break;	
		case "AmbushPortoBello_3":
            dialog.text = "����� �����, �������, ��� ������������� ���. ��� ������� ��������, � ��� ������� ������...";
            link.l1 = "������, ��������. ����� � ���� ��� ����� ���������� � �����������, � ���� ���� ����������� ��������� ������ �������...";
			link.l1.go = "AmbushPortoBello_4";
		break;	
		case "AmbushPortoBello_4":
            dialog.text = "��, ������ " + pchar.name + ", ������ �� ����� �, ��� �����, �� ����� ��� ������ ���� ������. �������� ����, �������.\n"+
				          "������� ������� ��� ������� �����!";
            link.l1 = "��� �� ���� ��������, ������� ��������, � ������������� ������ ��������� �����... �� ������.";
			link.l1.go = "AmbushPortoBello_5";
		break;	
		case "AmbushPortoBello_5":
			AddQuestRecord("Romantic_Line", "24");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			DialogExit();
		break;
		//�������� �� ������ �� ���� ������ � ������
		case "BelizTalk":
            dialog.text = "�� ���, �� � �������. ��� �������, ������ " + pchar.name + "?";
            link.l1 = "�������, � �������� ���� �������. ������ � ��� �������� � ����� ��������, ��� ���� ���. � ���� �� � �������� ��� � ����� � ����� ������, ��� ��������� �� ��������� � ������.";
			link.l1.go = "BelizTalk_1";
		break;
		case "BelizTalk_1":
            dialog.text = "�������, �� ��� �����-���������...";
            link.l1 = "��������, �������, ���� � ������ �������� � ���� ��������?";
			link.l1.go = "BelizTalk_2";
		break;
		case "BelizTalk_2":
            dialog.text = "��������, ������...";
            link.l1 = "��������, ��� ��������, ��� � - �����. �������, ����������� �������� ����� ����, ��� ��. �� � ����� ���, ��������, � ����, ����� �� ����� ���!";
			link.l1.go = "BelizTalk_3";
		break;
		case "BelizTalk_3":
            dialog.text = "������� " + pchar.name + ", �� ����������� �������, ��������� ������. � ������� ��� ������, �� ���� ������� �����, ��� ��� ������� � ��� �� �������������� ����� �������������� �� ��������...";
            link.l1 = "�������, ���� � ��������� ��� ����� - � ���� ��������� �� ��, ��� ������� �� ������� ��� '��'?";
			link.l1.go = "BelizTalk_4";
		break;
		case "BelizTalk_4":
            dialog.text = "�� ��� ��������� ������, ��� �����-���������.";
            link.l1 = "� ������ ��������, ���� ������, � ����� ������� �� �������, ��� ���������! ��, �������� ����, �������, �� ������� ������ - ���������...";
			link.l1.go = "BelizTalk_5";
		break;
		case "BelizTalk_5":
            dialog.text = "������, �������. � ���������� �������� ��� ����, ���� ��� ����� ������������� ����� �����������.";
            link.l1 = "��������, � ��� �� ����� ������. �� ������ � ��� �������� ���� ��������� ������ - ���������.";
			link.l1.go = "BelizTalk_6";
		break;
		case "BelizTalk_6":
            dialog.text = "� ��� �� ������ �����������?";
            link.l1 = "�� ����, ������ ������� ���, ��������� ��������� � ��������. �� � ���� ���� ���� ��� ����� �������� - ����� �� ����� ������. ��������� ������� ��� ��������...";
			link.l1.go = "BelizTalk_7";
		break;
		case "BelizTalk_7":
            dialog.text = "����, �������. �� ��� ��, ��� ���� ����� ��������� �� ����������, � ����� ����� ��� � �������� ��������� �����, � ���� ������.";
            link.l1 = "�� ��������, ��������.";
			link.l1.go = "BelizTalk_8";
		break;
		case "BelizTalk_8":
			QuestSetCurrentNode("Atilla", "SalvatorNews");
			NextDiag.CurrentNode = "BelizTalk_after";
			AddQuestRecord("Romantic_Line", "19");
			chrDisableReloadToLocation = false;
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseS4", "Beliz_houseS4", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			DialogExit();
		break;
		case "BelizTalk_after":
            dialog.text = "�������, ����� � ��� �������?";
            link.l1 = "���� �������, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BelizTalk_after";
		break;
		//�������� � ������
		case "IsabellaInCave":
            dialog.text = "��, ��� � ��, " + pchar.name + "! �������-�� � ��� ���������!";
            link.l1 = "��������, �� ����! ����� �������! � �������� � ����� ������� �������, �� ���� ���������, ��� ��������, � ������� ����� �� �������� ��� ������.";
			link.l1.go = "IsabellaInCave_1";
		break;
		case "IsabellaInCave_1":
            dialog.text = "������ �������, ��������� ���� ��!";
            link.l1 = "��������! ���������� ��� ������, ��������, ��� ���������?";
			link.l1.go = "IsabellaInCave_2";
		break;
		case "IsabellaInCave_2":
            dialog.text = pchar.name + ", ��� ��� - ������� ���! ������ ���������, ��� � ��������� ����� ����������� - ��������� �������� �� �������� �� �����. ����� ��������� � ��� ����� �������� ������ �� ���, � ���� ������, �� ����� �� �������, ������ ������� �����. ���� ���!..";
            link.l1 = "�����������, ��������... ��� ���� ������?";
			link.l1.go = "IsabellaInCave_3";
		break;
		case "IsabellaInCave_3":
            dialog.text = "������ ��� ���������� ���� ����. ��������� ������� ��������� ���� ��������� ������������ �� ������������ ���������� ������� ������, ���� ����� ��� ������ ��� ��������� ��� �� ���������.";
            link.l1 = "��� ��� ������ �� �� ���� ��� ����������! ��������, ��� ������ ���������� �����, ��� ��������� ����� � ��������� ������.";
			link.l1.go = "IsabellaInCave_4";
		break;
		case "IsabellaInCave_4":
            dialog.text = "� ������, ��� ��� ������ � ������� ��� ������, �� � �� �� ������ ���� ������. � ������� ��� ���� ���� � ���������� �����������, �������� �� �� ����� ������. ��������� � ���� �� ��, ��� ������ ������� ��� � ���� ������� � �� ������� �������� ����...";
            link.l1 = "��, ��������, � ���� �����! ������� ��� � ������ ���� � ��� ������! � ���� ��� �� ����������, �� ��� ��� ����� ��������...";
			link.l1.go = "IsabellaInCave_5";
		break;
		case "IsabellaInCave_5":
            dialog.text = "�� ������ ����, " + pchar.name + ", ���� �� ����� ������ ����.";
            link.l1 = "��������, � ������ ����������� � ����������, � ��� ��� ���������?";
			link.l1.go = "IsabellaInCave_6";
		break;
		case "IsabellaInCave_6":
            dialog.text = "�� ���� � �����, �� ����� ������ ��������� � ��������.";
            link.l1 = "����� ��������?";
			link.l1.go = "IsabellaInCave_7";
		break;
		case "IsabellaInCave_7":
            dialog.text = "� �������� � ������� - ����� ��������� ��� �����.";
            link.l1 = "���� ������! � ������������� �������� ����� �������...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			pchar.RomanticQuest = "FoundIsabella";
			AddDialogExitQuest("Romantic_SalvatorInCave");
		break;
		//����� ������� � ����������� � ������
		case "SalvatorIsDead":
            dialog.text = "��� �������!";
            link.l1 = "�������-��, ��������...";
			link.l1.go = "SalvatorIsDead_1";
		break;
		case "SalvatorIsDead_1":
            dialog.text = "������ " + pchar.name + ", ����� ���, ��������� ���� � ��� ������.";
            link.l1 = "������� ��������, ��� ��� ��� ����� � �� ������ �����, �� ��������� ��� ��������� ��� ���� ���� � ������!";
			link.l1.go = "SalvatorIsDead_2";
		break;
		case "SalvatorIsDead_2":
            dialog.text = pchar.name + ", � �������� ���� �����������.";
            link.l1 = "�������! � � ���� ��������� ����� ��, ��� ����� � ��� ���������.";
			link.l1.go = "SalvatorIsDead_3";
		break;
		case "SalvatorIsDead_3":
            dialog.text = "������, �������, ��� ������, � �� ���� �������� ������ ��� ����, ��� ���������.\n"+
				          "������� ������� ����� �������: ��������� ���� � ������� � ������, � ����� �������������� �������� �� ���-�����, ���� ��� ������ ������ �� ��������.";
            link.l1 = "��, ��������, �������, ��� ��������� ��� ��� ����� ���.";
			link.l1.go = "SalvatorIsDead_4";
		break;
		case "SalvatorIsDead_4":
            dialog.text = "� ���-����� � ������� � ������� ���� ����, ����� ���� ������� ������� - �� �������, � ���-�� ����� ����� �� ����������� � ������ ������.";
            link.l1 = "����� �������, ��������...";
			link.l1.go = "SalvatorIsDead_5";
		break;
		case "SalvatorIsDead_5":
            dialog.text = "�� �� ������ ������� ���, ��� ������� ��� �������� ��� ������� - ���������.";
            link.l1 = "�������, ��� ��������� ��� ��� ����. � ����������� ���� �� �����. �� ���� ��� � ����� �� ���... � ��������, ��������!";
			link.l1.go = "SalvatorIsDead_6";
		break;
		case "SalvatorIsDead_6":
            dialog.text = "����� ������, " + pchar.name + ". � ������ � ����� ��� - �������� ���� � ���� ������, � ������ �� ���� ����� ����������...";
            link.l1 = "������, ��������.";
			link.l1.go = "SalvatorIsDead_7";
		break;
		case "SalvatorIsDead_7":
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1 = "location";
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1.location = "Beliz_houseS4";
			Pchar.quest.Romantic_DelivToRosita.win_condition = "Romantic_DelivToRosita";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//����� �������� � ���� � ������
		case "RositaHouse":
            dialog.text = "������� " + GetFullName(pchar) + ", � ��� ��� � ���-����� ����� �����...";
            link.l1 = "������, ��������. �� �� �������, ��� ���������� ���� ��� �������?";
			link.l1.go = "RositaHouse_1";
			AddQuestRecord("Romantic_Line", "22");
		break;
		case "RositaHouse_1":
            dialog.text = "� ���� � ���-����� ����� �����, ������ �������...";
            link.l1 = "������, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RositaHouse_1";
		break;
		//�������� ����� � ���-�����
		case "InSanJuanAgain":
            dialog.text = "������ " + pchar.name + ", �� �������...";
            link.l1 = "��, ������� ��������. ��� � �������?";
			link.l1.go = "InSanJuanAgain_1";
		break;
		case "InSanJuanAgain_1":
            dialog.text = "��, ��� ������. ����, ��� �����-���������, �� ������ � ����� �������� �����?";
            link.l1 = "��, ��������, ������ � ���� �����.";
			link.l1.go = "InSanJuanAgain_2";
		break;
		case "InSanJuanAgain_2":
            dialog.text = "� �� ��� ��� ������ ����?..";
            link.l1 = "��������, �������, ��� �� ������ ���������� �����?! � ��� ��� �� ���!";
			link.l1.go = "InSanJuanAgain_3";
		break;
		case "InSanJuanAgain_3":
            dialog.text = "������, " + pchar.name + ". ����� � ����� ���, ��� ��� ��� ������������ � ��������. ������ ����� � ��� ��� � ������ � ������...";
            link.l1 = "��������... ����� ���� ������ �����������!";
			link.l1.go = "InSanJuanAgain_4";
		break;
		case "InSanJuanAgain_4":
            dialog.text = "��, ��� ������. � ������ � ����� ��� �������� ��� ���, �� ������� ��� ��� ������ ������...";
            link.l1 = "������, ��������, �� ������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "InSanJuanAgain_after";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //��������� ����� ����.
			pchar.RomanticQuest = "WaitBeginWidding";
			AddQuestRecord("Romantic_Line", "23");
		break;
		case "InSanJuanAgain_after":
			dialog.text = NPCStringReactionRepeat("�� ������� ��� ��� ������ ������...", "������, ������ ������������! �� ������� - ������!", "���, ��� � ��� ��� ���!",
                          "������ '��� ������������', � ����� ��� ��������� ����������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��, ��������, ��� �� ��� ��������� ��� ���?! � ���� ������ ��� ������...", "��������, ��� ��������� �����-��. � � ��� ����� �� ������!",
                      "��������! �� ��� ������?.. ���� � ���, ��� ������ ����� ��� ���� ������� - �� ������ ����...", "��, ��������, � �������� �����������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "InSanJuanAgain_out", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "InSanJuanAgain_after";
		break;
		case "InSanJuanAgain_out":
			AddDialogExitQuest("Romantic_OutFromHouse");
			DialogExit();
		break;

		case "Cancel_Widding":
            dialog.text = "��� �� ������� �� ������� � ������� �� ��������?! � ������ ��� ���� ������, � �� ��� ������� � �������� �� ����������!";
            link.l1 = "��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //��������� ���
			CloseQuestHeader("Romantic_Line");
		break;
		case "Cancel_Widding_1":
            dialog.text = "���, � ���� ������. ���������� ���!";
            link.l1 = "��, ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
		break;
		//�������
		case "TalkWidding":
            dialog.text = "������������, " + pchar.name + ".";
            link.l1 = "������������, ��������... �� ������� ���������, ��� �������!";
			link.l1.go = "TalkWidding_1";
		break;
		case "TalkWidding_1":
            dialog.text = "�������, " + pchar.name + ". �� ������, ����� ��������?";
            link.l1 = "�������!";
			link.l1.go = "TalkWidding_2";
		break;
		case "TalkWidding_2":
            dialog.text = "�����, �� ������ ��������...";
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "barmen", "stay");
			AddDialogExitQuest("Romantic_Padre");
		break;
		//����� � ������
		case "AmbushInChurch":
            dialog.text = "��� ����������? " + pchar.name + ", � �����!";
            link.l1 = "��������, � �������!!";
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_2");
		break;
		case "IsabellaIsMyWife":
			dialog.text = "��� ���� ���� ����������? �� ��� �� ����� ����� ���� - �� �� ���� ��� � ���� �� ������?!";
			link.l1 = "�� ����� �� �� ����, ��� � ��� ���������.";
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "�, �������, ������� � ��� � ���� ���� � ������?";
			link.l1 = "��������, ��� ���! ���������� ������ ���, �� � �����, ������� �� �����, ����.";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "����� �� ��� �������... " + pchar.name + ", � ���� ����� ��� ����� �������!";
			link.l1 = "���, �������, � ������� ���������, �� ������ ���� ����.";
			link.l1.go = "IsabellaIsMyWife_3";
		break;
		case "IsabellaIsMyWife_3":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = "�������, ���� ����� ����� � ����������� � ����� ���������� ��� ��� �� ���� ������������. ����� ������ ��� ����� �������� ��������� ������� �� ���������� � ������.";
			if (sti(rColony.HeroOwn))
			{	
				link.l1 = "��������, ���� ����� ����������� ��� �� ����� ���������. ��� ��� �� ���������...";	
				LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			}
			else
			{
				link.l1 = "������, ��������, � ��� ������...";				
				pchar.RomanticQuest.MayorOk = 1; //���� �� ����� � ����� ���-�����
			}
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 15.0);
			NextDiag.TempNode = "NewLife_firstTime";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������ ������ ����� �������
		case "NewLife_firstTime":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = "��, �������, ��� ������, ��� �� �������-�� ������ �����! ������ ��� ������� � ������������� � ������?";
			if (sti(rColony.HeroOwn))
			{
				dialog.text = "��, �������, ��� ������, ��� �� �������-�� ������ �����! ��� � �������?";
				link.l1 = "��, �������, ��� ���������...";
			}
			else
			{
				dialog.text = "��, �������, ��� ������, ��� �� �������-�� ������ �����! ������ ��� ������� � ������������� � ������?";
				link.l1 = "��, �������, � ��� �� ������ � �����������. ��� � ������� - �� ��� �����������.";
			}
			link.l1.go = "NewLife_firstTime_1";
		break;
		case "NewLife_firstTime_1":
			dialog.text = "�� ��� ��, ��� ����� ������. ������, ���� �� ����������, ����� ������� �������� ����������� ����������.";
			link.l1 = "����� ����� ���� ��������, ��������? � ����� ���� - ��� �������� �������!";
			link.l1.go = "NewLife_firstTime_2";
		break;
		case "NewLife_firstTime_2":
			dialog.text = "� � ���� ����, �������. �� ����� - ��� �� ������ ������, ��� ��� � ���������� ���. ����� �������, ������ �������� �����, � ��� ���� ��� ��� ������� ��� ��������, �� ������� ������ ���� ���� �����.";
			link.l1 = "��������, � �������� ����� �������������! ��, ����� ����, �� ���� ����������� �� ������ �������� � ��������� ��� � ����� ����������?";
			link.l1.go = "NewLife_firstTime_3";
		break;
		case "NewLife_firstTime_3":
			dialog.text = "�������, ����� ���� �����, �� ���� ������� ���������! ����� ������� ������� ���������� ���, �� �� ������?..";
			link.l1 = "�������, ��� ���� - ��� ��� ������... ����� ������� ��� ��� ��������.";
			link.l1.go = "NewLife_firstTime_4";
		break;
		case "NewLife_firstTime_4":
			dialog.text = "�����, � ���� ������... ����, ������� ����� ��� - �������. �� ������ ���������� �������� ������. ����� ����� ��� �������, �� ������ ���� ��� �����, � �� ������ ��������, ��� ��������� ������������� - ��� ������������ ���������� �����, �� ���� ��������� ������.\n"+
				          "����� ����, ����������� ����� ��������� ������������ ����� ������� ������...";
			link.l1 = "��������, � ����� ������ ���, ��� ����!";
			link.l1.go = "NewLife_firstTime_5";
		break;
		case "NewLife_firstTime_5":
			dialog.text = "������, �� ������ � ������... ��� ��, �������� ����: ���������� ���� ����� ����� ��������� � ��� " + FindRussianMoneyString(MOD_SKILL_ENEMY_RATE*10000) + ".";
			link.l1 = "��� �������, ��������. ��� - ��� ����! ���, � ��� � ��� ������� ���������?";
			link.l1.go = "NewLife_firstTime_6";
		break;
		case "NewLife_firstTime_6":
			dialog.text = "������ ������� - ��� ���� �������� ������� ���������. ����������� ����� ������ ��������, �� ���� ������ ������� � ����������� ������ - ������� ��� ����� �� �������...";
			link.l1 = "�� ��� ��, ���� �������� � ����� ���������. � �������� � ����� ���������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NewLife";
			AddDialogExitQuest("Romantic_afterFirstTime");
		break;
//************************************ ����� ����� ������� ������� ********************************
		case "NewLife_hello":
			iDay = GetQuestPastDayParam("RomanticQuest");
			dialog.text = LinkRandPhrase("����������, �������!", "����������� ������ ����.", "���� ������ ������ �������.");
			link.l1 = RandPhraseSimple("����������, ��������!", "�����������, ��� �������...");
			link.l1.go = "NewLife";
			if (iDay > 40)
			{				
				dialog.text = RandPhraseSimple("���������� �������! � ����� �� ������� ���, ����������, ��� ���� ������ " + FindRussianDaysString(iDay) + "?", "����������� ������ ����, �������� ������ ���������� ��� " + FindRussianDaysString(iDay) + ". �����, ����������, �������?");
				link.l1 = RandPhraseSimple("��������, �������, � ���������� ��� ��� ����� �� �����.", "�������, ���������� ��� ����� ���-��...");
				link.l1.go = "NewLife_hello_1";
			}
			if (GetQuestPastDayParam("RomanticQuest") > 3 && pchar.RomanticQuest == "OpenTheDoosOfHouse")
			{
				dialog.text = "����������, ��� ��������. � ������� ���� ����� ������ ������, ��� ���� ��������� �� ���� ������ ������.";
				link.l1 = "��������, � ��� �������, �� � �� ����� ���� - � �����!";
				link.l1.go = "NewLife_hello_2";					
			}
		break;	
		case "NewLife_hello_1":
			dialog.text = "��������, �, �������, �������, ��� �� ������� � ������ � ���� ����� - �������� �� ����. �� � �� ���� ����� - � �� ��������� ������ ���� ���� �� ��������� ������� � ����! � ����, ��� ���� ���� �� ����� ���� ��� �����, �� � ���� � ��������� ��� ������ ����� �� ������!";
			link.l1 = RandPhraseSimple("��������, � �������... �� �� ������, ��� �������� �������� ���� ���� �������.", "������ ����, ��� ���� �������� �������� ����� �������, � ��� �������...");
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //������� ����, �� ������� ������� ����������
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		case "NewLife_hello_2":
			dialog.text = "� ���� �������� ������ ���� - �������� ����� �����. ���� �� �������, ��� ������ �������� ���� ����� �� �������, �� ������� ����������. � ��� ������ ���� �����, � �� �������.";
			link.l1 = "������, ��������, � ���� ��������� �� �������� ���� �������...";
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //������� ����, �� ������� ������� ����������
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		//======================== ������� ���� ==========================
		case "NewLife":
			//���������, ��� ��� � ��������� � ���
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > 0)
			{
				dialog.text = NPCStringReactionRepeat("�������, � ��� �������� - �� � ������, ��� � ������. ���������� ������ " + FindRussianMoneyString(iMoney) + " � ������������� ��� ����� ��������� ��������.", 
					"�� ����������� ���� � ������ ��� ������ ��� � ����������� � ���������� ���������. �� ��������� " + FindRussianMoneyString(iMoney) + ".", 
					"� ������ ��� �� ������� � ��������� � ����� ������, ������������ " + FindRussianMoneyString(iMoney) + ".", 
					"������� ��� ��� ��������� �� �������� �������� - ������ � ������� " + FindRussianMoneyString(iMoney) + ".", "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("��������!! ��� �� � �������� ��� ����?!", "���� ��, ��� ��� �������� � �������� �����..."), 
					"������ ���? ��� ��������...", 
					"��� � ������?! �� ��...", 
					"� �����, ��������...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay";
				break;
			}
			//--> ��������� ���������� �� ���������
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.GrabbingTown)*150) >= GetCharacterSkill(pchar, "Sneak"))//���� ���� ����� �� �����
				{
					dialog.text = RandPhraseSimple("��������, ������ ������ � �������, ��� �� ��������� �����-�� �����. ��� ������?", "������, ��� ����� �����, ��� �� ����� ������ �� ������ � ��������� �����-�� �����. ������ �� ���?");
					link.l1 = LinkRandPhrase("�� ��� ��, �������, ��� �������!", "�������, ������ ������ � �� �����.", "���, �����, ��� ��������, � �� ������!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("GrabbingTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.TakeTown") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.TakeTown)*140) >= GetCharacterSkill(pchar, "Sneak"))//���� ���� ����� �� �����
				{
					dialog.text = RandPhraseSimple("������, ����� �����, ��� �� �������� �����-�� �����. ��� ������?", "������, ��� ����� �����, ��� �� ����� ������ �� ������ � �������� �����-�� �����. ������ �� ���?");
					link.l1 = LinkRandPhrase("�� ��� ��, �������, ��� �������!", "�������, ��� ������ ������ � �� �����.", "���, �����, ��� ��������, � �� ������!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("TakeTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillFort") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillFort)*130) >= GetCharacterSkill(pchar, "Sneak"))//���� ���� ����� �� �����
				{
					dialog.text = RandPhraseSimple("��������, �� ���� ��� ����� �����, ��� �� �������� �����-�� ����. ��� ������?", "������, ��� ����� �����, ��� �� ����� ������ �� ������ � �������� �����-�� ����. ������ �� ���?");
					link.l1 = LinkRandPhrase("�� ��� ��, �������, ��� �������!", "�������, ��� ������ ������ � �� �����.", "���, �����, ��� ��������, � �� ������!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillFort");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.AbordShip") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.AbordShip)*70) >= GetCharacterSkill(pchar, "Sneak"))//���� ���� ����� �� �����
				{
					dialog.text = RandPhraseSimple("�� ���� ����� ������� �����, ��� �� ������ �� ������� �������. ��� ������?", "������, ��� ����� �����, ��� �� ����� ������ �� ������ - ������ �� ������� � ������� �������. ������ �� ���?");
					link.l1 = LinkRandPhrase("�� ��� ��, �������, ��� �������!", "�������, ��� ������ ������ � �� �����.", "���, �����, ��� ��������, � �� ������!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("AbordShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillShip") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillShip)*50) >= GetCharacterSkill(pchar, "Sneak"))//���� ���� ����� �� �����
				{
					dialog.text = RandPhraseSimple("��������, ���� ������������, ��� �� ������ �������. ��� ������?", "������, ��� ����� �����, ��� �� ����� ������ �� ������ - ������ �������. ������ �� ���?");
					link.l1 = LinkRandPhrase("�� ��� ��, �������, ��� �������!", "�������, ��� ������ ������ � �� �����.", "���, �����, ��� ��������, � �� ������!");
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			//<-- ��������� ���������� �� ���������
			//        -------  �������� ����  ----------
			dialog.text = LinkRandPhrase("�������, � ������ ����...", "��� ����� ��� ������� ���?", "������ " + pchar.lastname + ", ���� ���� ������� ��� ��������������� �������...");
			link.l1 = "�� ���, ������ ����������... ����������, ������ ��...";
			link.l1.go = "NewLife_JustTalk";
			link.l2 = "����� ���������, � ����� ��������� ��� �������� ������...";
			link.l2.go = "NewLife_Budget";
			link.l3 = "�������, � ������ ���� �������.";
			link.l3.go = "NewLife_Present";
			link.l4 = "��������, �����, �� ������ ������������ �����...";
			link.l4.go = "NewLife_Sex";
			link.l5 = "����� ����, ������ ��� ���...";
			link.l5.go = "NewLife_Sleep";
		break;
		//=========================== ������ =================================
		case "NewLife_Budget":	
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > -(MOD_SKILL_ENEMY_RATE*10000)) //������ �� ������
			{
				if (iMoney == 0)
				{
					dialog.text = RandPhraseSimple("������ ���� ���, �� ������ �����������, �������...", "����� ��� ������ ��� � �������� ����������� � ����� �� �������... � ��� ������ ��������� ������.");
				}
				else
				{
					dialog.text = "������ ���� ���, �� ������ ���������. � ���� �������� " + FindRussianMoneyString(-iMoney) + ".";
					link.l1 = RandPhraseSimple("��, ������ ����� - ����� ������...", "��� ������ �� �� �����, �������� ��, ��� ����...");
					link.l1.go = "NewLife";
				}
				link.l2 = RandPhraseSimple("�� ��� ��, ����� �������� ���� ��������, ��������!", "����� ������ ��������� ������, ����� ���� � ��������!");
				link.l2.go = "NewLife_Budget_Add";
				LAi_CharacterPlaySound(npchar, "Gr_Isabella_4");
			}
			else //��������
			{
				dialog.text = RandPhraseSimple("������� �������, �������, ����� ���� ������� - " + FindRussianMoneyString(-iMoney) + " ��� � ���� ����.", "��� ���������, �����, ����� � ����� ������� ���������� - " + FindRussianMoneyString(-iMoney) + ".");
				link.l1 = RandPhraseSimple("�� ��� ��, ��� ������.", "���������, �������, ����� ������!");
				link.l1.go = "NewLife";			
				link.l2 = "���� ��� �������� ���� �����, ����� �� �� � ��� �� ���������.";
				link.l2.go = "NewLife_Budget_Add";
			}
		break;
		case "NewLife_Budget_Add":			
            dialog.text = NPCStringReactionRepeat("������, �������. ������� ����� �� ������ ��� ��������?", "����� �� ������ ��� ���-�� �������� ��� ������ ��� �� ��� - �� �����... ��� ������� �� ������ ��������?", "�� ���, ����������� ���� ����? ������ ��� �� ��� �� ������ ���� ��� �����! ����� ��� ������ ������?", "�� ���, �� ��� ������ - ������ �����������! �� ���� ������ � ����� �������������!", "repeat", 10, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= 50000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l1 = HeroStringReactionRepeat("50 �����.", "��, 50 �����, ���� ��������...", "���... 50 ����� ���� �������� ����.", "...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_50";
			}
			if (sti(pchar.money) >= 100000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l2 = HeroStringReactionRepeat("100 �����.", "100 �����...", "100 �����...", "...", npchar, Dialog.CurrentNode);
				link.l2.go = "NewLife_Budget_100";
			}
			if (sti(pchar.money) >= 200000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l3 = HeroStringReactionRepeat("200 �����.", "200 �����...", "200 �����...", "...", npchar, Dialog.CurrentNode);
				link.l3.go = "NewLife_Budget_200";
			}
			if (sti(pchar.money) >= 500000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l4 = HeroStringReactionRepeat("500 �����.", "500 �����...", "500 �����...", "...", npchar, Dialog.CurrentNode);
				link.l4.go = "NewLife_Budget_500";
			}
			link.l5 = HeroStringReactionRepeat("���... ���� ������, ��������... � �������� ��������...", "��� �����, �������... ������, �� ����� ���.", "����� ���-�� �� ����������, ��������... � ����� ���.", "��������, �� ��� �� ���?..", npchar, Dialog.CurrentNode);
			link.l5.go = "NewLife_Budget_No";
		break;
		case "NewLife_Budget_50":
			dialog.text = "������, " + pchar.name + " ������� ����.";
			link.l1 = "��� ��� �����������, ��������...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(50000);
		break;
		case "NewLife_Budget_100":
			dialog.text = "������, �����. 100 ����� - ��� ������, ������� ����.";
			link.l1 = "�� �� ���, �����...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(100000);
		break;
		case "NewLife_Budget_200":
			dialog.text = "����� ������, �������. 200 ����� - ������� ��������� ��������� �������.";
			link.l1 = "� ���, ��� �� ��������, ��������...";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(200000);
		break;
		case "NewLife_Budget_500":
			dialog.text = "��� �����! ��� �� ���� ������� �����?";
			link.l1 = "���������, ��� �� ���?";
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(500000);
		break;
		case "NewLife_Budget_No":
            dialog.text = LinkRandPhrase("��, � ����� ���� ����� ����������?", "����� ����� �� �� ���� ��������?" , "� ����� ����� �� ���� ��������?");
			link.l1 = LinkRandPhrase("� ������, �������, ������...", "������, �������, ���-�� � ������� ���� �����...", "� ������� ���-�� �� ����� ������ � ����...");
			link.l1.go = "NewLife";
		break;
		//��������� ����� � �������� ������� �������
		case "NewLife_Budget_Pay":
			iMoney = IsabellaCheckBudgetMoney();
			dialog.text = NPCStringReactionRepeat("�����, ������� " + pchar.lastname + ", �� ������� ��������� ��� ����! ��� ��� �������� �������� �������������!", 
				"�� ������ ���� ����� ������ �� ��������� �������������!", 
				"�������, � ������� ��� ����� ��� ����� �������� ���� ������������� �� �������!", 
				"�������, � ������ ��������� ���� � �� ��. � ��� ������, ������, � ��� ���������� ������� � ���� ���. ��� ��� � ��� �����, �������: � � ���� � ��������� ��������� � ����������! ��, � ��� � ������ �� �����!", "quest", 30, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= iMoney)
			{
				link.l1 = HeroStringReactionRepeat("������, �������, � ����� �������� �������������.", "� � �� �����, ��������! � ����� ������������ � �������!", "��������, �������, � ��� ��������� �����. � ����� ������ � ����� ������� �����.", "��������, ��� ��� ������...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_2";
				link.l2 = "���������, ��������, ����� ������ � ���� ��� �����...";
				link.l2.go = "NewLife_Budget_Pay_1";	
			}
			else
			{
				link.l1 = HeroStringReactionRepeat("��������, ��������, � ���� ��� ������ " + FindRussianMoneyString(iMoney) + "...", "������ ���, �� �� �����...", "��������, ��� � ���� ������ �����!", "���, ������ ���?..", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_1";
			}
		break;
		case "NewLife_Budget_Pay_1":
			dialog.text = RandPhraseSimple("��� ����� � �������! � �� ��������� ��-�� ��� �������� � �������� ���!", "���������� ����, �������! � �� �����, ����� �� ��� � ��� ����� ���� ������� �������� ����������� � �������� ������ ��������������! �������� ������, ��� ���� ������ �����������!");
			link.l1 = RandPhraseSimple("������, ��������, ��� �������...", "� �����, ��������, ���� ���������...");
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_Budget_Pay_2":
            dialog.text = RandPhraseSimple("��, ��� ��, �����������! � ����� ����, ��� ��� ��� - ������������� �������.", "���������, �������! �� - ��������� �������...");
			link.l1 = RandPhraseSimple("�� ��...", "���, ��� ��!");
			link.l1.go = "NewLife";
			iMoney = IsabellaCheckBudgetMoney();
			AddMoneyToCharacter(pchar, -iMoney);
			IsabellaNullBudget();
		break;
		//=========================== �������� ������, ��� �� ����� ����������� =================================
		case "NewLife_KnowPirates":
			pchar.RomanticQuest.Cheking = "Ok"; //���� "�� ��������� ������ �� ���������" � ���� ���
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma")) //��������, ���� :)
			{
				dialog.text = LinkRandPhrase("��, � ���� ����, " + pchar.name + "...", "��� ��, ����� � ������ ����, ��� �����-�� ������!", "�������� �� ������, " + pchar.name + ", ����, � �� ��������...");
				link.l1 = RandPhraseSimple("�� ��� � ����������, �������.", "��� �������! ���������� �������� - � ����� �������������...");
				link.l1.go = "NewLife";
			}
			else //�� ��������, � ��������� �������
			{
				dialog.text = NPCStringReactionRepeat("������, �����, � � ������� �������� ���� ������ � ��������. ������, ����� � �������� ������ �� ����, ��� ��� ����� ��� ����� ���� ������ ���������������.", 
					"�������, � ���� �� ������ - ������� ����� �� ���� �������... ������ ��� ������ ���������������.", 
					"��, ��������, � ��� �� �����, �� ���� �� ���� ����������? ��� ������ �� ���� � �������, � �� ������������! ������, ��� �� �� ������� ������ �����. � �����, ��� ���� ��������� ��������������, " + pchar.name + ".", 
					"���, ������� " + pchar.lastname + ", ������� ������ � ���� ������ ���. �� ����� ���� �� ���! �� ����� � ����� �������������!", "quest", 80, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("������, �������. � ������, ��� ���� ��� � ������������.", 
					"������, �������, ����� ��� ����� ��������������� ����� ���.", 
					"�-�-�, ������, ��������, ����� ��� ����� ��������� ���������������.", 
					"��, ��������...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife";	
			}
		break;
		//=========================== ���� =================================
		case "NewLife_Sex":			
			if (GetQuestPastMonthParam("RomanticQuest") > 2 && GetNpcQuestPastDayParam(npchar, "sex") != 0)
			{
				dialog.text = "��� �����, �� ������� ����� ������?";
				link.l1 = "��-�-�, ���� �����...";
				link.l1.go = "NewLife_Sex_1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("� ��� ��� ��?", 
					"�-�-�, � �����������, � ��� ��...", 
					"�����? � ��� � ���� ������?", 
					"��, �� �������...", "cycle", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("�� ��� � ��� ��, ��������, � �����...", 
					"������ �� ����, ������� - � �����...", 
					"� ������ � ����� �����, �������...", 
					"��������, � ������ � �����, �������...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Sex_5";
			}			
		break;
		case "NewLife_Sex_1":
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //���������� ����
			dialog.text = "� �� �� ����� �����, �������, �� ���������� ��� ������� �� ����...";
			link.l1 = "��� ������?";
			link.l1.go = "NewLife_Sex_2";
		break;
		case "NewLife_Sex_2":
			dialog.text = "������, ��� ���� � ���� - �������� �������, ���� �� ����� ������ �� �������. � � ���-����� �� ���� ������� �����, ���� ��� ����� ���������� ���������...";
			link.l1 = "���, ������!! ��������, �� ���� ��� ����� ��������?!";
			link.l1.go = "NewLife_Sex_3";
		break;
		case "NewLife_Sex_3":
			dialog.text = "�� � ������, ����� �� ���� ����� ������, �������!";
			link.l1 = "�����, ��������, � ���� �����... ����� �� ����� ���������, �����...";
			link.l1.go = "NewLife_Sex_4";
		break;
		case "NewLife_Sex_4":
			if (rand(6) < 5)
			{
				dialog.text = "�� ������... � ��� � �������...";
				link.l1 = "� - �� �����!";
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = "������, ��������� �� �����, �����. �� � ���� ������� �������, ��� ��� ������ �� ������. ������...";
				link.l1 = "��, ��� �� �������!..";
				link.l1.go = "NewLife_exit";
			}
		break;

		case "NewLife_Sex_Late":
			dialog.text = "������, ��� �������, � �� ��������� ����� ���� ��� ����� � ������ ������ ����������... �� ������� ���� ����!";
			link.l1 = "��������, �� ��� �� ���?..";
			link.l1.go = "NewLife_Sex_Late_1";			
		break;
		case "NewLife_Sex_Late_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NewLife_Sex_5":
			if (GetNpcQuestPastDayParam(npchar, "sex") > 3)
			{
				dialog.text = NPCStringReactionRepeat("�-�-�... ����� ��������� ��� �� ����...", 
					"� �����? �� ��� ��, ���������, �����...", 
					"������, ��� ���������... ��� ��� ��?..", 
					"��, ��� ������... � ����� ����� ����� ��������!..", "block", 60, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("��������, � ������ �� �������!!", 
					"��������, � �������� ����� ��������� � ����� ����!", 
					"��������, ������� �������� ����� ����������� ����...", 
					"�� ����� ��� ��������, ��������?! ����� ���������� ������ � �������, �������?..", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("NewLife_Sex_10", "NewLife_Sex_11", "NewLife_Sex_12", "NewLife_Sex_13", npchar, Dialog.CurrentNode);
			}
			else //������� �����, �� ��������
			{
				dialog.text = LinkRandPhrase("������� ����� � ����� �������� ������, �������. ��� ��� ������, �� ������ �� ������...", "���, �������, ������ ��������� � ����� ������ ��� ���� � ����, ��� ������� �����...", "��, �����, � �� ���� �������� �� ��� ���� ������� �����, �� ������� ����, ����������. ����� ��������� ����, �������...");
				link.l1 = RandPhraseSimple("��... ���... ����...", "�-��, � �����������...");
				link.l1.go = "NewLife_exit";
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //���������� ����
		break;
		case "NewLife_Sex_10":
			dialog.text = "����� � ��� ���� � �������, �������!";
			link.l1 = "��������, � ��� ������...";
			link.l1.go = "NewLife_GoSex";
		break;
		case "NewLife_Sex_11":
			if (rand(10) < 8)
			{
				dialog.text = "��������� ����?.. ��, ������. � ��� � �������...";
				link.l1 = "��, ��������...";
				link.l1.go = "NewLife_GoSex";
			}
			else //�� ������
			{
				dialog.text = LinkRandPhrase("� ���� ����� ������, �������, �� �������...", "� ���� ������� ����� ��������, �������. �� ������...", "�����, ����� �������... � �� ���� - ������ ������������.");
				link.l1 = RandPhraseSimple("��, ��� �� �������!..", "����!.. ������, ��������, ���������...");
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_12":
			if (rand(10) < 5)
			{
				dialog.text = "�������... �-�-�, �� ������. � ��� ���� � �������, �������...";
				link.l1 = "��������, � �����!..";
				link.l1.go = "NewLife_GoSex";
			}
			else //�� ������
			{
				dialog.text = LinkRandPhrase("� ���� ����� ������, �������, �� �������...", "� ���� ������� ����� ��������, �������. �� ������...", "�����, ����� �������... � �� ���� - ������ ������������.");
				link.l1 = RandPhraseSimple("��, ��� �� �������!..", "����!.. ������, ��������, ���������...");
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_13":
			if (rand(10) < 2)
			{
				dialog.text = "�������, �� �����!.. �� �����, ��������...";
				link.l1 = "��������...";
				link.l1.go = "NewLife_GoSex";
			}
			else //�� ������
			{
				dialog.text = "������ �� �� �������! � ������ �� �������� ���� ���������� ����!";
				link.l1 = "������, ��������, ������...";
				link.l1.go = "NewLife_exit";
			}
		break;
		//���� � �������
		case "NewLife_GoSex":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //��������� ����
			Pchar.quest.Romantic_Sex.win_condition.l1 = "location";
			Pchar.quest.Romantic_Sex.win_condition.l1.location = "SanJuan_houseS1Bedroom";
			Pchar.quest.Romantic_Sex.win_condition = "Romantic_Sex";
			SetTimerCondition("Romantic_IsabellaBackToHall", 0, 0, 1, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto6", "Romantic_TalkInChurch_end", 20.0);
			DialogExit();
		break;
		//����� �����
		case "NewLife_afterSex":			
			dialog.text = NPCStringReactionRepeat("�-�-�... �����, ��� ����... �����������!", 
				"��, ��� � ���� ����, �������? ��� ������?", 
				"���-�� �� ������� �� � �����...", 
				"��, ������... ��� ���������...", "block", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, �������...", 
				"���������, �����, �� ���� ������ �����������!", 
				"��... ������, �������, ��� �����...", 
				"��������� � ����� ��������, �������.", npchar, Dialog.CurrentNode);
			link.l1.go = "NewLife_afterSex_1";
		break;
		case "NewLife_afterSex_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto2", "Romantic_TalkInChurch_end", 20.0);
			Pchar.quest.Romantic_IsabellaBackToHall.over = "yes";
			DialogExit();
		break;
		//=========================== ��� =================================
		case "NewLife_Sleep":
			dialog.text = "����� ���� ���������, �������?";
			if(!isDay())
			{
				link.l1 = "�����, ���� �����...";
				link.l1.go = "NewLife_Sleep_day";
			}
			else
			{
				link.l1 = "��� ����� ������ �����, ��������.";
				link.l1.go = "NewLife_Sleep_night";
				link.l2 = "���� ����������. ������� ��������� �����.";
				link.l2.go = "NewLife_Sleep_day";
			}
		break;
		case "NewLife_Sleep_day":
			dialog.text = "������, ������� ���� �����.";
			link.l1 = "��, �������. ����� � ����� � �������...";
			link.l1.go = "room_day_wait";
			link.l2 = "�� ������, ���������. �� ���� ���� �����.";
			link.l2.go = "NewLife_exit";
		break;
		case "NewLife_Sleep_night":
			dialog.text = "������, ������� ���� ����� ��������.";
			link.l1 = "�������, �������. ����� � ����� � �������...";
			link.l1.go = "room_night_wait";
			link.l2 = "�� ������, ���������. ����� ������� ��� ����� �� �����.";
			link.l2.go = "NewLife_exit";
		break;
		case "room_day_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_day");
			AddDialogExitQuest("sleep_in_home");
		break;
		case "room_night_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			TavernWaitDate("wait_night");
			AddDialogExitQuest("sleep_in_home");
		break;
		//=========================== ������ �������� =================================
		case "NewLife_JustTalk":
			if (CheckAttribute(pchar, "RomanticQuest.Atilla"))
			{
				switch (pchar.RomanticQuest.Atilla)
				{
					case "YouAreBaster": 
						dialog.text = "��������, � �������, ��� �� �������� �������� �� ����� ������ - �������. �������, ��� �� ��� ��� ����� ���� �����, � � ���� ����, ������� �� ������ ��� ���... � ������ � ����!";
						link.l1 = "�������, ��� ��� ��� �������, ������ ��� ����������...";
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreNormal": 
						dialog.text = "�������, � �������, ��� �� ������������ ������ ����� ������. ��� ��������� ��������, � ����, ��� ��� ��� - ��������� �������, ������� �����!";
						link.l1 = "��������, ����� �� ���� �����?..";
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreGood": 
						dialog.text = "�������, �� ��� ������ �� �������, �� ��� �������� ������, ��� �� ����� ������ ����� ������ ����� ������� �����. �������, ��� ������������� �� ��� ��, ��� �� ������ ��� ���. �������, �� ����� ������ ������� �� �����! � � ���� ��������� ��������� ���.";
						link.l1 = "��������, �� ��� ��... �� ����� �����, � ����� ���� ������ ����...";
						link.l1.go = "NewLife_exit";
					break;
				}
				DeleteAttribute(pchar, "RomanticQuest.Atilla");
				break;
			}
			switch (rand(1))
			{
				case 0: 
					dialog.text = LinkRandPhrase("��, �������, ��� ��� ������� ���� ��������...", pchar.name + ", �� ��������� ������...", "��, �������, ����� �������, ��� �� ������ ��� � ����� " + GetMainCharacterNameGen() + "...");
					link.l1 = RandPhraseSimple("��� ���� ������� � �����, �������...", "������, ��������, � ����� �����: ��� ������, ��� �� ������ ������� ���� ������...");
					link.l1.go = "NewLife_exit";
				break;
				case 1: 
					dialog.text = LinkRandPhrase("�������, � �� ������, ���������� ������ �������������, ��� � ��� ����.", "���������� ��������� ���� �� ����, ��� � ���� ����, �������.", "����� � ��������� ����������� �� ����� � �� ����������. �� �������������, ��� � ���� ����.");
					link.l1 = RandPhraseSimple("�� ��� � �������, ��� ��� � ����� � ��������� ���.", "�� ������ ��, ��� ��� ������ �������� ����������� � ����...");
					link.l1.go = "NewLife_exit";
				break;
			}
		break;
		//=========================== ������� =================================
		case "NewLife_Present":
			dialog.text = RandPhraseSimple("� ��� �� ������ �������� ���, �������?", "����� ������� ������, ��� �� ��� ������� ��������?");
			iTemp = 1;
			for (i=18; i>=1; i--)
			{
				if (i==8 || i==9) continue;
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = XI_ConvertString("jewelry"+i+"Gen") + ".";
					link.(sTemp).go = "NewLife_jewelry_"+i;
					iTemp++;				
				}
			}
			if (iTemp == 1)
			{
				dialog.text = NPCStringReactionRepeat("� ��� �� ������ �������� ���, �������?", 
					"����� ���-�� ������ ��������? ��, �� � ��� ���?", 
					pchar.name + ", �� ���, ����������� � ����� ���������? ��� �� ���� ���?", 
					"�� ���, �� ���� ������, ������! � ������� �� ���� � �� ����� � ����� �������������!", "repeat", 20, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("�� ������ ������...", 
					"������, ���������� ���� � ���� ���, ������...", 
					"��������, � ����� ������ �� ����� ��� ����, ������...", 
					"��������, ������!..", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_jewelry_1":
			dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ������� ��� ����� ��������.", "��, ��� �� ������ �� ������! �������, �����..." , "������������ ������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";			
			TakeItemFromCharacter(pchar, "jewelry1");
		break;
		case "NewLife_jewelry_2":
			if (rand(4)==1)
			{
				dialog.text = "��, �����... � ������ � ��� �����! �����, ����� ���������� ������!";
				link.l1 = "� �������������, �����.";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ������ ��� ����� ��������.", "��, ��� �� ������ �� ������! �������, �����..." , "������������ ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry2");
		break;
		case "NewLife_jewelry_3":
			if (rand(10)==1)
			{
				dialog.text = "��, ��� �� �����! � ��� ����� ��� �������-������� �����! �������, �� ���� ����� ���������, � ������ � ���� ��������� � ����� ������...";
				link.l1 = "� � ���� ����� ����, �����...";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ������ ��� ����� ��������.", "��, ��� �� ������ �� ������! �������, �����..." , "������������ ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry3");
		break;
		case "NewLife_jewelry_4":
			if (rand(3)==1)
			{
				dialog.text = "��, ��� �� ��� ������� ������ - �������! �� ���� �������, �����... �������, � ���� ��������� � ����� ������...";
				link.l1 = "� � ���� ����� ����, �����...";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. �������� ��� ����� ��������.", "��, ��� �� ������ �� ������! �������, �����..." , "������������ ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry4");
		break;
		case "NewLife_jewelry_5":
			dialog.text = LinkRandPhrase("�-�-�, ������! ����� ������� �������, �������, �������.", "��, � ����� �� �����, ���� ���������! �������, �������." , "������������ ���������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� ������� �������� �� �������!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";	
			TakeItemFromCharacter(pchar, "jewelry5");
		break;
		case "NewLife_jewelry_6":
			dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ��������� � ��������� ��� ����� ����.", "��, ��� ������ ������ ��������� � ���������� ������! �������, �����..." , "������������ ������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";			
			TakeItemFromCharacter(pchar, "jewelry6");
		break;
		case "NewLife_jewelry_7":
			if (rand(2)==1)
			{
				dialog.text = "��, ������ � ���� ������� ���������! �� ���� �������, �����... �������, � ���� ��������� � ����� ������...";
				link.l1 = "� � ���� ����� ����, �����...";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ������ � ���������� ��� ����� � ����...", "��, ��� �� ������ �� ������ � ������� ������! �������, �����..." , "������������ ������ � ��������� ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry7");
		break;
		case "NewLife_jewelry_10":
			dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ��������� � ��������� ��� ����� ����.", "��, ��� ������ ������ ��������� � ������� ������! �������, �����..." , "������������ ������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry10");
		break;
		case "NewLife_jewelry_11":
			dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ����� ������� ��������� ������������� ���������!", "������... �������� �� ��������� ������ �������� ��������. �������, �������." , "������������ ���������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry11");
		break;
		case "NewLife_jewelry_12":
			dialog.text = LinkRandPhrase("�������, �������, �� ����� �������...", "������... �������� �� ��������� ������ �������� ��������..." , "������������ ���������! �������, �������...");
			link.l1 = RandPhraseSimple("���...", "��...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry12");
		break;
		case "NewLife_jewelry_13":
			dialog.text = LinkRandPhrase("�-�-�, ����� ���������� ����������, ��� �����... �������, �������.", "���������� ���������, �����. ������� ����..." , "������� ���������! �������, �������...");
			link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry13");
		break;
		case "NewLife_jewelry_14":
			if (rand(1)==1)
			{
				dialog.text = "��, �����, ��� ����� �������� ��������... � ���� ���������� ��������� � ����� ������...";
				link.l1 = "� � ���� ����� ����...";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ��� ������� ����� ����� �������...", "��, ��� ��� ������ ��������� �� ����� �����! �������, �����..." , "������������ ����� � ��������� ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry14");
		break;
		case "NewLife_jewelry_15":
			if (rand(1)==1)
			{
				dialog.text = "��, �����, ��� ��������... � ������ ��� ��� �� ���� � ���� ���������� ��������� � ����� ������...";
				link.l1 = "� �� ������, �������.";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������. ��� ���������� �������� ����� ��� ����...", "��, ��� �������� ������ ��������� �� ����� �����! �������, �����..." , "������������ ����� � ��������� ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry15");
		break;
		case "NewLife_jewelry_16":
			dialog.text = LinkRandPhrase("�������, ������ ��� �������� ����, � �� �������...", "��, � �� �������, � ���� ����� ������?" , "�� � ���� � ����, �������. �� �� ������ ������, ���� ����������� ��� ����� ������!");
			link.l1 = RandPhraseSimple("��? �-�-�, �� �����...", "���-�� � ������...");
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_jewelry_17":
			dialog.text = LinkRandPhrase("�-�-�, �������! �� ��� ��, ������, � ��������� ����������...", "�������?.. �� �����, �����..." , "���������� ���������? ��, ������� ������� � ������� �����������. �� �����, ����� ������...");
			link.l1 = RandPhraseSimple("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� ������� �������� �� �������!");
			link.l1.go = "NewLife_exit";	
			TakeItemFromCharacter(pchar, "jewelry17");
		break;
		case "NewLife_jewelry_18":
			if (rand(8)==1)
			{
				dialog.text = "�������� � ������ - ��� ������� �����. ��� ������� ������ �����������, �� ���� �������, �����... �������, � ���� ��������� � ����� ������...";
				link.l1 = "� � ���� ����� ����...";
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase("�������, �������, �� ����� �������, ��� ������ � ������� ����� �������...", "����� ������ ��������� ����� � ������! �������, �����..." , "������������ ������ � ��������� ������! �������, �������...");
				link.l1 = LinkRandPhrase("�� �� �� ���, �������...", "� ����, ����� �� ���� ����� �������� �������� �� �����!", "��� - ��� ����, �����...");
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		//�����
		case "NewLife_exit":
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto"+(rand(3)+1), "Romantic_TalkInChurch_end", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		//==> ������� ���� �����
		case "AngryRepeat_Budget_Add":
            dialog.text = RandPhraseSimple("� �� ����� �������� � ����� �������! ����� ��� ���������� � ������� ������� � ��������� �������� ��� ������...", "�� ���� �������������, � ��������� �� ����, ������ � ������! ������, � ���� ���������� � ������� ������ � ���������...");
			link.l1 = "��, ��������...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "��, ������, �������, � �������� � ����� ��������. �� �� ���� ����� �������! � ��� �����, �� ������ ������, ����� ����� ���!";
        			link.l1 = "������, ��������, � ���� ���������...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //���������� ����� ������ � ��������
				{
					if (CheckCharacterItem(pchar, "jewelry6") && CheckCharacterItem(pchar, "jewelry10"))
					{
         				dialog.text = "��, �� ������ ��� ��, ��� � ������ - ������� � ���������� ������ � ��������! ��, �� ������, ��� ��� �������... �� ������, � ������ � ����� ��������...";
        				link.l1 = "��-�-�, �������!";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry6");
						TakeItemFromCharacter(pchar, "jewelry10");
					}
				}
            }	
    	break;
		//==> ������� �� ����������� � �������
		case "AngryRepeat_Budget_Pay":
            dialog.text = RandPhraseSimple("����������, �������, �� �� �������� ���������� ������������� ����, ��� �������� ����� ������ ���� ���������� ��������. ��� ������ �� �������!", "�������� ������, � ���� ������ ������ ��� ������� � �����! ���� ������������� ���������� ����� ���� ��������!");
			link.l1 = "������� ��������, ��� ����������...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� 30 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "�� ������, � �������� �� ����������, �� ��� �������������� ������������� ���� ����� ��������!";
        			link.l1 = "������, ��������, � ������ ���, ��� �� �������.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //���������� ����� ��������
				{
					if (CheckCharacterItem(pchar, "jewelry4") && CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "jewelry15"))
					{
         				dialog.text = "�� �� ��������! �� ������ ��� ��������� � ����������... ������ ��� �����, ��� ��� ��� ��������!.. �� ������, � �������� �� ����������, �� ��� �������������� ������������� ���� ����� ��������!";
        				link.l1 = "������, ��������, ������...";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry4");
						TakeItemFromCharacter(pchar, "jewelry7");
						TakeItemFromCharacter(pchar, "jewelry15");
					}
				}
            }
    	break;
		//==> ���� ������� �� ���������
		case "AngryRepeat_KnowPirates":
            dialog.text = RandPhraseSimple("�� �������� ���� �����, ������ ��� ����� ��������! � �� ����� ��� ������!", "�� �� ������, ��� � ���������� ���������, � ��� � �� ����� ���������� ��������� ����� ��������!");
			link.l1 = "��������, � �� �����, ����� ��� �����...";
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� 80 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "��� ���, ������! � ������ � ����������, �� �� ������ ������ ������� ���� �����!";
        			link.l1 = "������, ��������, � ������ ���, ��� �� �������. ��������� ������ �� �����, �������...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar); 
					IsabellaSetCurrentState("All");
                }
				else //���������� ����� �����, ������ � ������� ���������
				{
					if (CheckCharacterItem(pchar, "jewelry1") && CheckCharacterItem(pchar, "jewelry2") && CheckCharacterItem(pchar, "jewelry3") && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry11"))
					{
         				dialog.text = "��, " + pchar.name + ", �� ������, ��� �������, ����� � �� ���������... �� �� ������ ������� ���� ����� � ��������� � ����������!";
        				link.l1 = "��, ��������, � ����� ����� ���. � �� �� ���� ��� ����...";
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry1");
						TakeItemFromCharacter(pchar, "jewelry2");
						TakeItemFromCharacter(pchar, "jewelry3");
						TakeItemFromCharacter(pchar, "jewelry18");
						TakeItemFromCharacter(pchar, "jewelry11");
						IsabellaSetCurrentState("All");
					}
				}
			}
    	break;
		//==> ���� ������ ���������
		case "AngryRepeat_Present":
            dialog.text = RandPhraseSimple("���, �� ������ ���������� ���� � ����� ���������! � ����� ����� ���� ���������� ���� �������������� ���������?! ���� ������ ���!!", "�� ���� ������������� � ����� ������������ ������� � �������! ��� �� ���� - ������ ���� �������������� �������! ��, �������, �������!..");
			link.l1 = RandPhraseSimple("��������, �� �� ��� �������������...", "���-�� ����� �� ����, ��������. � �� �������...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� 20 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "�� ������, � ������ � ����� ����������. �� �� �� ���� ����� �������� � �� ��������� ��������, ���� � ���� �� ���!";
        			link.l1 = "������, �������, ��� ������ ������ � �� ����...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //���������� ����� �����-�������
				{
					if (CheckCharacterItem(pchar, "jewelry5") && CheckCharacterItem(pchar, "jewelry17"))
					{
						if (sti(pchar.items.jewelry5) >= 3 && sti(pchar.items.jewelry17) >=5)
						{
         					dialog.text = "�� ���� ��!.. �� ������ ������������, ��� � ������ ������������� ���� - ������� � ���������� ������... �� ������, � ������ ����������� �������. �� ������ ����� �� ���� ���������� ����� �������������� � ���������!!";
        					link.l1 = "������, ��������, ��� �������...";
        					link.l1.go = NextDiag.TempNode;
        					CharacterDelAngry(npchar);
							TakeNItems(pchar, "jewelry5", -3);
							TakeNItems(pchar, "jewelry17", -5);
						}
					}
				}
			}
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;

// <<<<<<<<<<<<============= ���� ��� angry =============================
	}
}
