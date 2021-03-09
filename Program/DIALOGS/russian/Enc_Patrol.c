void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("�-�-�, �������, "+ GetSexPhrase("���� �������� ������","��� �������� �������") +" ������� � " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! �������� �"+ GetSexPhrase("��","�") +"!!", "���, �� ������ �����������! ��������� " + NationNamePeople(sti(pchar.nation))+ " ���������� ���� �� ������ � " + NationNameAblative(sti(npchar.nation)) + "! �������� ������"+ GetSexPhrase("�","���") +"!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("��������� ����� ���� " + XI_ConvertString("Colony" + npchar.city + "Gen") + "! ����� �"+ GetSexPhrase("��","�") +"!!", "��������-��, " + NationNamePeople(sti(pchar.nation))+ " ����������� ���� �� �� � " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! ���������� ��������!!!");
				}
				link.l2 = RandPhraseSimple("����������, ����� �� � �����������...", "���, ����� ��� ������ ����� ��������.");
				link.l2.go = "exit_fight"; 		
				if (IsCharacterPerkOn(pchar, "Adventurer") || IsCharacterPerkOn(pchar, "Agent"))
				{
					link.l1 = RandPhraseSimple("�� ����������, ���! � ������������"+ GetSexPhrase("���","���") +" �������"+ GetSexPhrase("��","��") +".", "� ���� ����� ��������? ����� � ������ ����������� ���"+ GetSexPhrase("��","��") +"?");
					link.l1.go = "CheckPeg";
				}					
			}
			else
			{				
				dialog.text = LinkRandPhrase("���� ����� �������������! � ��������� ������� �� " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", �� ����������� ������� ����������.",
					"������������, � ��������� ����� �������. �� ����������� ���������� �� " + XI_ConvertString("Colony" + npchar.city + "Gen") + " ����.",
					"����������� ���, " + GetAddress_Form(NPChar) + ". ��� ������������� ������������ �������������� ���������� ���� " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				Link.l1 = LinkRandPhrase("���������. ��� � ���� ��� ������?",
				"����� ������. ���� �� � ���� ��� ���-������ �����"+ GetSexPhrase("��","��") +", " + GetAddress_FormToNPC(NPChar) + "?",
				"�����������. ��� ����� � ���� ��� ��� �������?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "CheckPeg":
		switch (rand(1))
		{
			case 0: 
				dialog.text = RandPhraseSimple("�-�-�, ����... ��� � �������, �� ������ ����, " + GetAddress_Form(pchar) + ".", "���-�� � ������� �������� � �������... ��� � �������, " + GetAddress_Form(pchar) + ", ����� ��������.");
				link.l1 = "���-��!";
				link.l1.go = "exit_noFight";
				if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
				{
					AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
					pchar.questTemp.stels.landSolder = GetDataDay();
				}
				break;
			case 1: 
				dialog.text = RandPhraseSimple("��� �� ��������� ��� ������! �������� ������!", "�� ����� �����... ���������� ����������!");
				link.l1 = RandPhraseSimple("��� �� �� ���!", "����� ��������, � �������...");
				link.l1.go = "exit_fight";
				if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
				{
					AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
					pchar.questTemp.stels.landSolder = GetDataDay();
				}
				break;
		}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("�� �� ������ ������ ��������������� � ������?", "���������� �� ��� ���-������, ��������� ����������, " + GetAddress_Form(NPChar) + "?");
			link.l1 = RandPhraseSimple("���, ������ ������.", "���, ������, ��� ��������.");
			link.l1.go = "Node_3";
			
			/* Nathaniel (09.03.2021): ����������� �������������� ����� � ������� ------------- */
			link.l2 = "��, ������, � ���� � ��� ����� ������ ����... � ��, �����������, ���������!";
			link.l2.go = "exit_fight";
			/* --------------------------------------------------------------------------------- */
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("�� ��� ��, �� ���� ��� �����������. ��������, " + GetAddress_Form(NPChar) + ".",
				"�������. � ����� ������, ��������.");
			Link.l1 = "����� ���.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("�� ���������� ��� �� ������� ������.",
				"� ����� ��� �� ������ ���!",
				"�, ��� ����� ��... ����� ����� �������, �� ������� ���.");
			Link.l1 = "������.";
			Link.l1.go = "Exit";			
		break;
		
		// ��������� "����� ��� ������"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "��... � ���� ������ �� �����. �� ��� �����"+ GetSexPhrase("","�") +"?";
					link.l1 = "� �"+ GetSexPhrase("��","�") +", ���� �� �����...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "� ������� " + GetFullName(pchar) + ". ���� ����������������, ����� �� ���� ��� ���������, ���� ������ � ������� �� �������...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "� ������� " + GetFullName(pchar) + ". ����� �����, ������� ������ ����...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "����"+ GetSexPhrase("��","��") +", �������. � �� �����, �� �������... � ���� ��� � ����� ���-��?";
					link.l1 = "����� ���?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "�� �����-�� �� �����"+ GetSexPhrase("","�") +" �� ����, ���� �� ��������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "������, � ��� ��� � �������.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "� ��� ����� ���� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "�����������, ������� �� �����, �� ������ ������� ����������� �����...";
			link.l1 = "��-��!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "����� ������. �� �� �������� �����, ����� ���� ����������� �� ����� ��������� ��������.";
			link.l1 = "������, � ������ ������.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "��������";
				break;
				case 2:
					sItemName = "�������";
				break;
				case 3:
					sItemName = "�������";
				break;
				case 4:
					sItemName = "���������";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "�����, �����. ��������� 30 " + sItemName + " � �����?";
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ������, ��� ������� ���� ����, ����� ������� �������� �������. ����� ������ ����������.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "������.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "���! �� ��� ����� �������!";
			link.l1 = "����� ���������������...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "�������, ����� � ���� " + sti(pchar.questTemp.ReasonToFast.p5) + " �������, ��� � �������������.";
			link.l1 = "�� ����� �� �� �������?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "������.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "�� � ���� ��� ��� ���� ����� �����!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "��� �������� �������. ���, �����. ��� ����� ������ � ���� ����������� ������, � ������� ��������� "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "���� �������!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//����� �������� � ������� 
			AddDialogExitQuest("pchar_back_to_player");				
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "�� � ����� � " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + " ������� ������������... ���-�� �� �������� ��� ���... ���� �"+ GetSexPhrase("��","�") +", ������!";
			link.l1 = "��� �, ��������!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // ����� ��������� ������
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // ������� � �������
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "�������! ������ � ����. �� ����������� ��� " + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) +" '" + sTemp1 + "' � ������ " + GetGoodsNameAlt(iShipGoods) + ", ���� ������ ��� � ���������, � '�����' ���� �� �����. ������������ ������� ������� �� �������� ��������, � �� ������ � ���� ������ ���� ��. �������� � ����, ��� ������ ������.";
					link.l1 = "������. ��� ��� � ������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//����� �������� � �������
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // ��������� �����������
					switch(rand(3))
					{
						case 0:
							sTemp1 = "�������� ����� �������";
						break;
						case 1:
							sTemp1 = "������� ��� ����-������";
						break;
						case 2:
							sTemp1 = "������� � ������ ������";
						break;
						case 3:
							sTemp1 = "���� '����������'";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "��������";
						break;
						case 1:
							sTemp2 = "�������";
						break;
						case 2:
							sTemp2 = "����������";
						break;
						case 3:
							sTemp2 = "��������";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "�������! " + sTemp1 + " ���������� ������ � ���� � �������. ���������� ����� ��� ��������������� ����� �� ��� �� ����, �� �� �������. ����� '���' �������. ������: '"+ pchar.questTemp.ReasonToFast.password +"', �����: '"+ sTemp2 +"'.";
					link.l1 = "������. ��� ��� � ������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//����� �������� � �������
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "�� �� ��������� ���� ��������?! ������!";
				link.l1 = "������ ���!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "�� ������"+ GetSexPhrase("","�") +"! ���! ������!... ����.";
				link.l1 = "��� ����!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "�� �� �������� �����, ��� ������ �������...";
			link.l1 = "��-��, ��� �����.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //��� �� �����������
			pchar.GenQuest.ReputationNotChange = 1; //��������� �� ������
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "�� �� ��������������, ��� ��������� ������ ���� ����!";
			link.l1 = "���������� �����. ������, ��������� ��������? ���� �� ������� ��������.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "� � � ����"+ GetSexPhrase("�� ����","�� ����") +", ������ �� �� ���, � ��� �� �������.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "������, ��-���� ��������"+ GetSexPhrase("","�") +"... ��, ����� �� ��������.";
			link.l1 = "����...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "��, ������"+ GetSexPhrase("��","��") +"! � � ���� �� �������!.. ������! ����� �"+ GetSexPhrase("��","�") +"...";
			link.l1 = "����...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// ��������� "����� ��� ������"
	}
}
