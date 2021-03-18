void ProcessDialogEvent()
{
	ref NPChar, TempChar;
	aref Link, Diag;
	
	int iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar) + "! "+"�� ����������� ���� ������ �����, � ���, �������, �� � ��� � �����.";
			Link.l1 = "��� �� ����� � ��� ��� �� ���� �����?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + " ��������� �� ���� ������ ������� ����, �������, "+ GetSexPhrase("����� �� ���� �������� ��� �������","����� �� ���� �������� ��� �������") +".";
			Link.l1 = "� �����"+ GetSexPhrase("","�") +" ��������� ��� ���, ���� �� �� �������� ���� � �����.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("���������, ��, ������, �� ����������. � "+ GetFullName(TempChar) + " - ��������� � ���� ����� ��������","���������, ��, ������, �� ����������. � ������� �������, ��� ���� - "+ GetFullName(TempChar) + " - ��������� � ���� ����� ��������") +".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "�� ��� ��, ��������� ���� �����.";
			Link.l3.go = "battle";
			// to_do
            /*PChar.GenQuest.ToPrisonCmdIdx = GetCharIDXByParam("PrisonCommander", "nation", NPChar.nation);
            if (sti(PChar.GenQuest.ToPrisonCmdIdx) > 0)
            {
                Link.l4 = "������, � ��������� � ����. � ���"+ GetSexPhrase("","�") +" ��� "+ GetSexPhrase("���������","����������") +" ��� �������.";
    			Link.l4.go = "ToPrison";
            }*/
		break;
		
		/*case "ToPrison":
            AddDialogExitQuest("Hunters_GoToPrison");
            
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // ������ ����, � �� ������������
            {   // ������ � ��
	            AddQuestRecord("HeadHunter", "HeadHunter_GiveUp");
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;  */
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "�! ������� �� ��������, �������� ���, "+ GetAddress_Form(NPChar) + ".";
                Link.l1 = "�������, ������...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "������, �� �����!";
                Link.l1 = "� �����"+ GetSexPhrase("","�") +" ��������� ��� ���, ���� �� �� �������� ���� � �����.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "�� ��� ��, ��������� ���� �����.";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // ������ ����, � �� ������������
            {   // ������ � ��
	            AddQuestRecord("HeadHunter", "HeadHunter_free");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("��","���"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart");
				CloseQuestHeader("HeadHunter");				
            }
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL ���� ��� � ������� ���� �� ���� ������, ������ �� ������������
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // ������ ����, � �� ������������
            {   // ������ � ��
	            AddQuestRecord("HeadHunter", "HeadHunter_battle");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("��","���"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
				CloseQuestHeader("HeadHunter");
            }
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // ������ ����, � �� ������������
            {   // ������ � ��
	            AddQuestRecord("HeadHunter", "HeadHunter_Buy");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("��","���"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
				CloseQuestHeader("HeadHunter");
            }
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "� �����, ��� " + PChar.HunterCost + " �������� ��� �������.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "� ���� ��� ����� �����.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "��� ���� ������, ��������� � ������������.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "����� ����� ���, ��������... �� ����� � ��� ���� ����� ��������!!!";
                Link.l2.go = "battle";
            }
		break;


        case "NoMoney":
			dialog.text = "� ����� ������ �������� �������!";
			Link.l1 = "����� ��� ���� �� �����.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "������-��, "+ GetSexPhrase("��������","�������") +"... �������, � ���� ���� ���-��� ����������. ����� �������� � �������� ��������� �����������.";
            Link.l1 = "������, � �����"+ GetSexPhrase("","�") +" ��������� ���, ���� �� �� �������� ���� � �����.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("���������, ��, ������, �� ����������. � "+ GetFullName(TempChar) + " - ��������� � ���� ����� ��������, � �� �������� ��������","���������, ��, ������, �� ����������. � ������� �������, � �� ������������ ��������! ��� ���� - "+ GetFullName(TempChar) + " - ��������� � ���� ����� ��������") +"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "�� ��� ��, ������ ����� ���������� ����� ������� �� ����.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "�! ������� �� ��������, �������� ���, "+ GetAddress_Form(NPChar)+".";
                Link.l1 = "�������, ������...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "������, �� �����!";
			    Link.l1 = "����� ����������, ��� ���� ��� �����.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		// ��������� "����� ��� ������"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "� ��� � ���� ��������� ���������. �� ��� �� ���� ���������.";
			link.l1 = RandPhraseSimple("� ��� ��� ��, �����������? � "+ GetSexPhrase("�������������","�����������������") +" ����������� ����-������� �������� � ����� ������ ��������! "+ GetSexPhrase("�����������","������������") +" ������������ ����������!","��� �������, ��� �� ���� � ���-�� �������. � "+ GetSexPhrase("���������� ��� ������� ��������","������������ �����-������") +" � ������� ������� ������� �����. �� ������ ��������� �� ��� ��������� ������� ����? ����� ����������� ������������� �������!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "���� ��� ����?! ���������� � ������!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "� ���, " + GetSexPhrase("�������� �������","�������") + ". ��� ���� �� �����... �� ����� �����, ��� ����� " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) +" ��������� ����. � �� ��� �������� �������, � ��� ������� �������� �� ��������. ������� � ������� ������ �� �� ����.";
			link.l1 = "�� �����. ������� ���� �����. ������ ��� ��� �� ����������. ������ ������� � ������, ��� ��� �������� ���� ������� ����.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "�� �����, ��������� ���� ���������. �� ������� ��� ��� �� ��������, - �� ��� ������� ����� �����...";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+ GetSexPhrase("��, �������. ����� �������, ���� �� ��� ���� � ����","��, ��������. ����� �������, ���� �� ��� ���� � ����") +"...";
			link.l1 = "� � � �� ��������� �������!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "��� ��� �������� ����� ��������������� ��������!";
			link.l1 = "������ �� �������� ������ � ����� �����������...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "��, "+ GetSexPhrase("��������","�������") +"! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ������, ��� � ���� ���� ���-��� ��� ���.";
			link.l1 = "��� �� ������ � ����?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "����� " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
				link.l1 = "��������� � ��������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " ������. �������, ��� ����� ����������...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ����� ���������, ���� ������, ��� � ���� ������� ��� ���� ������� �� ����.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "�����, ��� �� ������" + GetSexPhrase("","�") + " � �����������.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "��������� � ��������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " ������. �������, ��� ����� ����������...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ����� ���������, ���� ������, ��� � ���� ������� ��� ���� ������� �� ����.";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "�����");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "��������");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "��, "+ GetSexPhrase("��������","�������") +"! � " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " ���� � ���� ���� ��������.";
			link.l1 = "� ���� �� �� ��� �� �� ������?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "�� �� ����... �� ������"+ GetSexPhrase("","�") +" ��������, ��-�� ���� �� �������� " + sti(pchar.questTemp.ReasonToFast.p10) + " ��������. ��� ��� � ���� ������.";
			link.l1 = "��������� � ��������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " ������. �������, ��� ����� ����������...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ����� ���������, ���� ������, ��� � ���� ������� ��� ���� ������� �� ����.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "������");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "� ���� ��� ����� �����! �� ��� �, �� ���� ����� ������"+ GetSexPhrase("","�") +"... ";
				link.l1 = "�����...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "�� ��� �, �� ���� ����� ������"+ GetSexPhrase("","�") +"...";
			link.l1 = "�����...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// ��������� "����� ��� ������"
	}
}
string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";
	
	if(nFile >= 0) 
	{
		if (CheckAttribute(&locations[nLoc],"islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = "������� " + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = "��������";
			}
		}
		//
        if (CheckAttribute(&locations[nLoc],"fastreload"))
		{
			ret += " (" +LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		//ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile( nFile );
	}
	return ret;	
}
