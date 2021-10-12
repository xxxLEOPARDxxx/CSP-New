// 03.02.08 ������� �� ���

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;
	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		case "First time":
			
            NextDiag.TempNode = "First time";
			dialog.text = RandPhraseSimple("�����������, �������! �������-������ �� ����� �� ����� ������?",
                          "�����, ����� ����������� ������ �����?");
			link.l1 = ""+ GetSexPhrase("�������? ������? ����� �������... � �� ��� �� ��������?","��� ���� ������� �� �������, � ����� �� ���� ������?") +"";
			link.l1.go = "Node_2";
            link.l2 = ""+ GetSexPhrase("���, �������, � ���� ������ ��������.","� ����� ����������, ��� � �������... ��������...") +"";
			link.l2.go = "exit";
		break;
		
		case "CitizenNotBlade":
			dialog.text = "�������, ��� �� ��������! ������� ������, ���� ��� �� ��������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break;

		case "Node_2":
            if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
            {
                dialog.text = "� ������ �� ������, �� � ���� �� �� �����������. ���� ��������� ������������ ������. �������, � �� ����� � ��� � �������.";
    			link.l1 = "� ������ ��������� �� ����� ������ ��� ������!";
    			link.l1.go = "exit";
    			break;
            }
            
            if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
            {
                dialog.text = "� ������ �� ������, �� �� ��� ����� ������ ��� ��, "+ GetSexPhrase("���������","���������") +". �������, � �� ����� � ���� � �������.";
    			link.l1 = "� ������ ��������� �� ����� ������ ��� ������!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "�������� ���� � �������� ������������� � ���� ����� ������ ����� �������� ���� ������. �������� � �������� - ��� ��� ������";
			link.l1 = "������ ����������������� ���... "+ GetSexPhrase("","� ���� �� �������...") +" ������� �� �� ������ �� ��� ������?";
			link.l1.go = "price";
            link.l2 = "�������, ��������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
            if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
            {
                dialog.text = "� ������ �� ������, �� � ���� �� �� �����������. ���� ��������� ������������ ������. �������, � �� ����� � ��� � �������.";
    			link.l1 = "� ������ ��������� �� ����� ������ ��� ������!";
    			link.l1.go = "exit";
    			break;
            }

            if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
            {
                dialog.text = "� ������ �� ������, �� �� ��� ����� ������ ��� ��, "+ GetSexPhrase("���������","���������") +". �������, � �� ����� � ���� � �������.";
    			link.l1 = "� ������ ��������� �� ����� ������ ��� ������!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "������� �� ����������, �������? ������, ��� ����� �������������, �� ��� �������, ��� �� ��������?";
			link.l1 = "�������, ���. ������� �� ������?";
			link.l1.go = "price";
            link.l2 = "����������. ��������� ����������.";
			link.l2.go = "exit";
		break;

		case "price":
            if (FindFreeRandomOfficer() == -1)
            {
                dialog.text = "��. � ��� ������ ��������. � ���� ���������, ����� �� ������� ���� ��� ������.";
    			link.l1 = "������.";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "�����, �� � ���� �������� �� 50000 ��������.";
			link.l1 = "� "+ GetSexPhrase("��������","��������") +", ��������. ������ ���� ����������� � �������.";//"+ GetSexPhrase("","�") +"
			link.l1.go = "hire";
            link.l2 = "�� �� ������ ���� �����. ������.";
			link.l2.go = "exit";
		break;
		
        case "hire":
			if(makeint(Pchar.money) >= 50000)
			{
				AddMoneyToCharacter(Pchar, -50000);
                dialog.text = "�� ����� ����������� ���, �������. �� ���� ��������� ������, ��� ������ ������� ���� ������.";
			    link.l1 = "������� � ��� ������.";
			    link.l1.go = "Exit_hire";
			}
			else
			{
				NextDiag.TempNode = "OnceAgain";
                dialog.text = "��, ������, � ��� �������� � �����������! ��������, �������, �� � �� ������� � ������.";
				link.l1 = "�� ��, ����!";
				link.l1.go = "Exit";								
			}
		break;
                
        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = ""+ GetSexPhrase("��� ������ ��� ����������� �������?","����� ����� ������������?") +"";
			link.l2 = "�� �������. � �������� ��� ����� �����!";
			link.l2.go = "AsYouWish";
            
			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "0";
				}
				if (sti(pchar.Option_ImmortalOfficers) < makeint(GetCharacterSPECIAL(pchar,"Charisma")*2) && !CheckAttribute(npchar,"ImmortalOfficer"))
				{
					Link.l6 = "� ���� � ���� �����������."; 
					Link.l6.go = "contract"; 
				}
			}
			
			// ������� -->
            if (PChar.location == Get_My_Cabin())
            {
    			if (PChar.sex != "woman")
    			{
					Link.l3 = RandPhraseSimple("��� �� �� � ����� ����� �����...�? �������� ��� � ������� ����... ����� ���������...",
	                                           "�������� ����� � ���� ����� ������� �������. �� ������ ��������� �� �� ����?");
	                if (sti(pchar.GenQuest.BrothelCount) > 4+rand(3))
	                {
	                    Link.l3.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Love_Sex";
	                }
                }
                if (CheckAttribute(pchar , "questTemp.FUNY_SHIP_FIND") && PChar.questTemp.FUNY_SHIP_FIND == true && GetCharacterItem(PChar, "mineral4") >= 25)
                {
                    Link.l4 = "������ ����� � ���� ��������� ��������� ����������!";
            		Link.l4.go = "FUNY_SHIP_1";
                }
            }
            else
            {
                if (PChar.sex != "woman")
                {
					Link.l3 = RandPhraseSimple("�������-������������� - ���, �������, ������, �� ����� �� ���������� ����� �����?",
	                                           "��� ������ ���������� �����?");
	                Link.l3.go = "Love_Sex";
                }
            }
            Link.l5 = "������ ��� ������!";
            Link.l5.go = "stay_follow";
			
			// �� ��� ������� ��������� ����� �� ��� ���������  -->
			if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
							{
								NPChar.ColonyIdx = iTemp;
								Link.l7 = "� �������� ���� ����������� ����� ������!";
								Link.l7.go = "Gover_Hire";
							}
                        }
                    }
                }
            }
			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
					{
						Link.l8 = "� ���� ��������� ���� ����������� ������� ''" + PChar.ColonyBuilding.ColonyName + "'', ������� �� ��������� �� ������� ������.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}	
			}
			
            link.l9 = ""+ GetSexPhrase("����������, ��������, �������","������. ������") +".";
			link.l9.go = "exit";
        break;
        
        case "FUNY_SHIP_1":
		    dialog.text = "� ����! �������, ������� �� ���� ���, ����� ����������� ����... �� ��� ������ �� ��� ��� ���� ������ ������� ��� ��������� ������������ �����?";
   			Link.l1 = "���, �������, ������. ����� ������ ��� ��� �������� ����� �� ����.";
            Link.l1.go = "exit";
            Link.l2 = "��, ����! ���� ����, �������. ��-��, ������� �����!";
            Link.l2.go = "FUNY_SHIP_2";
        break;
        
        case "FUNY_SHIP_2":
		    dialog.text = "�� � ����! ��... ���� ��������, � �������� ���� ������� � ����, ��, ��������.";
   			Link.l1 = "���! � �� �������, ���� ���� �� ��������. ���� ������ ������ ����.";
            Link.l1.go = "FUNY_SHIP_3";
        break;
        
        case "FUNY_SHIP_3":
            PChar.questTemp.FUNY_SHIP_FIND = false;
            DialogExit();
			NextDiag.CurrentNode = "Hired";
			
			TakeNItems(pchar, "mineral4", -25);
			AddSPECIALValue(Npchar, SPECIAL_S, 1);
			AddSPECIALValue(Npchar, SPECIAL_P, 1);
			AddSPECIALValue(Npchar, SPECIAL_E, 1);
			AddSPECIALValue(Npchar, SPECIAL_C, 1);
			AddSPECIALValue(Npchar, SPECIAL_I, 1);
			AddSPECIALValue(Npchar, SPECIAL_A, 1);
			AddSPECIALValue(Npchar, SPECIAL_L, 1);
        break;
        
		case "contract": 
			dialog.text = "������ ��� �����������, �������."; 
			Link.l1 = "�� ������� ������ � ��������� ��� ���������. ���� ���������� ���� ����� �� ��� �� ������ �� ���������."; 
			Link.l1.go = "contract2"; 
		break; 

		case "contract2": 
			dialog.text = "������� �� ������ �����, �������. � ����� ������� �� ���������?"; 
			Link.l1 = "������� ������������ ������. ���������� �������, "+ NPCharSexPhrase(NPChar,"���","����") +" ���������. ���� ��������� 10 ���. ��������� ������ �� ��������� �����, � ���� �� ����� ���������� ��� �����, ���������� ������."; 
			Link.l1.go = "contract3"; 
		break; 

		case "contract3":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*1000);
			dialog.text = "���������� �����������, ������ �� �������. �� ��������� �������� ���������� �������. � ��� ������ ��������� ��������� ��� ����������� �������?"; 
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{ 
				Link.l1 = "������ ������ �� ����, " + sti(NPChar.contractMoney) + " ������� ����� ������ �� ���� ���� �������?";
				Link.l1.go = "contract4";
			} 
			Link.l2 = "������ ������ �� ����, �� ����� ������� � ����� ��������� �����."; 
			Link.l2.go = "Exit"; 
		break;
 
		case "contract4": 
			dialog.text = "������, �������. � ��������."; 
			AddMoneyToCharacter(Pchar, -sti(NPChar.contractMoney));
			SetCharacterPerk(NPChar, "EnergyPlus"); 
			SetCharacterPerk(NPChar, "HPPlus"); 
			NPChar.OfficerWantToGo.DontGo = true; 
			NPChar.loyality = MAX_LOYALITY; 
			NPChar.Reputation = 50; 
			DeleteAttribute(NPChar, "alignment");
			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "1";
				}
				else
				{
					pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) + 1);
				}
				//pchar.PGG_hired = true;
				NPChar.ImmortalOfficer = true;
				NPChar.HalfImmortal = true;  // ��������
				//string immortal_officer = npchar.id;
				//pchar.quest.(immortal_officer).win_condition.l1 = "NPC_Death";
				//pchar.quest.(immortal_officer).win_condition.l1.character = npchar.id;
				//pchar.quest.(immortal_officer).function = "Remove_Contract_Officer";
			}
			// DeleteAttribute(NPChar, "contractMoney");//Mett: ��� ����� ������������� �� �������, �� ����� ������������ ��� ����������� ����� ���������
			Link.l1 = "��� � �������! ������������"; 
			Link.l1.go = "Exit"; 
		break; 
		
        case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("�������, ������ �������� ����� � ��������.",
                                           "������, ��� �����, ��� ���������� ������ �� ������� �����.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "�������, �� ���� �� ��� � �������, ����� ��� ����� ���� ����� ���� ��� ��!");
			link.l1.go = "Love_Sex_Yes_2";
        break;
        
        case "Love_Sex_Yes_2":
            pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// ��������
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);

   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;
        
        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("��.. �������, � ������ �� �������� �� �������...",
                                           "�������, ������ �� ����� ������ ���������� �������, � ��... ? �������� � ����� �����.");
            link.l1 = RandPhraseSimple("��-��! ��� �� �������������� �� ������� �� ������!", "� ���� ������, ���� �������� � �������.");
			link.l1.go = "exit";
        break;
        
        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("���!!!?? �������, �� ����� �� ������ �� ����� � �� ��� � �������?", "�� �������, � ��� ��� ��?");
            link.l1 = RandPhraseSimple("�� ���� �������.. �� ����� ���������, �� ��� � � ���� ����������", "�� �� ���� �� ��� � �������, ����� ��� ����� ���� ��!");
			link.l1.go = "Love_Sex_2";							
			link.l2 = RandPhraseSimple("������ ����, ������, ����� ������ ���� ����������, ���� �� ����������..", "��.. �����, ��������...");
			link.l2.go = "exit";	
        break;
        
        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("�������! ������� ���� � �����, ���� �� ������ � �����, �������� ��������", "��, ��� � ������ � ���������� ���������� ���, �������, ��� ������ �� ������!");
            link.l1 = RandPhraseSimple("�����, �� ��������. � ��� �� ���� ���� ����������. ������..", "� - ���� �������! � � ���������� ����!");
			link.l1.go = "Love_Sex_3";							
			link.l2 = RandPhraseSimple("������ ����, ������, ����� ������ ���� ����������, ���� �� ����������..", "��.. �����, ��������...");
			link.l2.go = "exit";	
        break;
        
        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("�� ���! �� �������� �� ���! � ����� ������!", "������������� � �����? ���� ������ ��������, ��� �� ��� ��������..");
            link.l1 = "�.. �� � ���?";
			link.l1.go = "Love_Sex_4";							
        break;
        
        case "Love_Sex_4":
            ChangeCharacterReputation(pchar, -15);
            CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
            LAi_SetWarriorType(Npchar);
            LAi_group_MoveCharacter(Npchar, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
            LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			DeleteAttribute(Npchar,"HalfImmortal");
			Npchar.LifeDay = 0;
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
                LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        // ������� <--

        case "AsYouWish":
			dialog.text = "��� �������, �������, ������ ���.";
			link.l1 = "�������, � ���������"+ GetSexPhrase("","�") +". �� ��� ��� �����.";
			link.l1.go = "exit";								
			link.l2 = "�������. ������ �����������, ���� ��������.";
			link.l2.go = "Exit_Fire";		
		break;

        case "Exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			Npchar.CanTakeMushket = true;
			npchar.HalfImmortal = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "� �� ������������� ���, �������, ��� �� ������� �� ��� �������. � ���� ���� ���� ��������.";
		      Link.l1 = "�� �� ��� � �� �����!";
		      Link.l1.go = "Exit";
	    break;
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "stay_follow":
            dialog.Text = "����� ����� ����������?";
            Link.l1 = "���� �����!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "������ �� ���� � �� ��������!";
            Link.l2.go = "Boal_Follow";
			if (!CheckAttribute(npchar,"AboardRestriction"))
			{
				Link.l4 = "����� ���� �� ����������� � ���������. �������� ����.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "� ���������, ������ ����������� � ���������.";
				Link.l4.go = "AboardAllowed";
			}
        break;
		
		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "��� ����� �������. �� ���� ����������� � ���������, ���� �� ����� �� ���������.";
            Link.l1 = "�� � ������.";
            Link.l1.go = "exit";
		break;
		
		case "AboardAllowed":
			DeleteAttribute(npchar,"AboardRestriction");
			dialog.text = "��� ����� �������. ���� ����������� � ��������� � �������� �������.";
            Link.l1 = "�� � ������.";
            Link.l1.go = "exit";
		break;
        
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "���� �������� ����������!";
            Link.l1 = "������.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar); // it works!!!
            dialog.Text = "���� �������� ����������!";
            Link.l1 = "������.";
            Link.l1.go = "Exit";
        break;
		
		//////////////////////////////    ������-��������� -->
		case "Gover_Hire":
            dialog.Text = "����� �� �����!";
            Link.l1 = "����� �� �������� � ������������ ������, � ���� ������ ���������� �� ��������� ��������.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // ������ ��������� -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// ������ ��������� <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  �� <--
			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "����� ����� ����������? ��������� ��� ����� ��� " + FindRussianDaysString(iTemp) + " �����.";
			}
			else
			{
			    dialog.Text = "����� ����� ����������?";
			}

            Link.l1 = "����� ����� ������� �� " + NPCharSexPhrase(NPChar, "������", "�������") + " �� ������ ������?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "�� " + NPCharSexPhrase(NPChar, "�����", "�����") + " ��� �� �������, � ������ ���� � ��������� ������.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "����� ��������.";
            Link.l9.go = "Exit";
            NextDiag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "��� ������ ��������� ��� �������� " + FindRussianMoneyString(iFortValue*iTax) + " � ����. �� " + FindRussianDaysString(iTemp) + " � " + NPCharSexPhrase(NPChar, "������", "�������") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "� ���� ������� ��� ����� �������.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "��������� �� ������!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
            Link.l8 = "��� � ������.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  �� <--
        break;
        //////////////////////////////    ������-��������� <--

		//�������� ��� ���������� 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "����������� ������.";
			Link.l1 = "��� �������� ��������.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "��� �������� ������ �������.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // ������ ��� ����-�����
			{
			    Link.l3 = "� ����, ����� �� �� ����� ����� �� ������� ���� ������� � ������� ����� ��������������.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "���� ������.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "��� �� �� �������?";
			Link.l1 = "� ���� ����� �� �� ���� ������� �� �������. �������� ���� � ���� �������.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "��� ����� ����� �� ���� ��������� ������� �� �������.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "��� �� �� �������?";
			Link.l1 = "� ���� ����� �� �� ����� ���� ������� ����� ��������. �� ������� �����.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "����� ������ ����� ������ �� �������, ��������, ����� �������� ��������� �����, ����� ���� ����.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "��� �����.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "����� ���������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "��� �����.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "����� ���������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
		case "exit_spec":
			DialogExit();
		break;
		//����
		case "Yoko_meet":
			if (sti(pchar.reputation) >= 70)
			{
				dialog.Text = "����������� ���, �������. � - ���� ����, ������� ������.";
				Link.l1 = "��������� ���-�� ���������. ����� ������?";
				Link.l1.go = "Yoko";
			}
			else
			{	
				dialog.Text = "�� �����, ��� ��� ���� � ��� ��������, �������.";
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Yoko_meet";
			}
		break;
		
		case "Yoko":
			dialog.Text = "���, �� ������ ����� �� ���� ���� �� �����.";
			Link.l1 = "������ ���?";
			Link.l1.go = "Yoko_1";
		break;
		
		case "Yoko_1":
			ref locLoad = &locations[FindLocation("Shore_ship1")];
			string blade = GetGeneratedItem("Blade15");
			locLoad.box1.items.(blade) = 1;
			npchar.stortaid = blade;
			locLoad.box1.money = 7461;
			locLoad.box1.notouch = true;
		
			dialog.Text = "�������� � ����� ����� � ������� �������, � ����� ���������, ��� ������� ��� ������ � ��� ������. ���� ������� �� ������� - � ����� � ���� �������.";
			Link.l1 = "����� �� ������� ������� ���������� ���... �� ��� �������, �� � ���� �����������.";
			Link.l1.go = "Yoko_2";
		break;
		
		case "Yoko_2":
			dialog.Text = "� ���� �����, �������.";
			Link.l1 = "�� �������, ����!";
			Link.l1.go = "exit_spec";
			NextDiag.currentnode = "Yoko_wait";
			NextDiag.TempNode = "Yoko_wait";
		break;
		
		case "Yoko_wait":
			dialog.Text = "��� ������, �������?.";
			if (GetCharacterFreeItem(pchar,npchar.stortaid))
			{
				Link.l1 = "��� ������� ��������� ���� ������. �����.";
				Link.l1.go = "Yoko_nowait";
			}
			Link.l2 = "������, ���� ������.";
			Link.l2.go = "Yoko_2";
		break;
		
		case "Yoko_nowait":
			TakeNItems(pchar,npchar.stortaid,-1);
			GiveItem2Character(NPChar, npchar.stortaid);
			EquipCharacterbyItem(NPChar, npchar.stortaid);
			dialog.Text = "��������� ���!";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
		//����
		case "Helen_meet":
			if (startherotype == 5 || startherotype == 6)
			{
				if(npchar.id == "Beatrice")
				{
					dialog.text = "� ���� ������� �������� ���������� ����, ����� ����, ��� ����? ����� � ���� ����, ���� � ���� �� ��������!";
					link.l1 = "������, ����...";
					link.l1.go = "exit";
					break;
				}
			}
			if (sti(pchar.reputation) >= 70)
			{
				dialog.Text = "����������� ���, �������. � - ���� ��� �����, ����� ������ ��������� �� ������ � ������ ��� ������ ��������.";
				Link.l1 = "�� ������ ���� ���������? ������ ��������� ������ ����������� ���� ��������� �� ���, ���?";
				Link.l1.go = "Helen";
			}
			else
			{	
				dialog.Text = "�� �����, ��� ��� ���� � ��� ��������, �������.";
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Helen_meet";
			}
		break;
		case "Helen":
			dialog.Text = "��� �����. ���������� � � ���������, � � ��������.";
			Link.l1 = "���� �� ��� ������, ������ �� ���� ��� �� �����?";
			Link.l1.go = "Helen_1";
		break;
		case "Helen_1":
			dialog.Text = "���� ����� ���� �������� � ������-��������, ���� �� ���� ������ ��� ��� ��� ������. ��� ��� �� ���������� ��� ������ ��� ������� �����, ��-�� ���� ����� �� ������ ����� ���� � ����.";
			Link.l1 = "� �� ��������� �������� ��� ��� ������?";
			Link.l1.go = "Helen_2";
		break;
		case "Helen_2":
			dialog.Text = "������, ��� �� �������, � �� ��� �����? ��� ��������, ��� �� �������� ���� ��� ���� � ������� �� ������ ���.";
			Link.l1 = "� �� ������, ����� � ���� ����� � ����? � ����� ��������������?";
			Link.l1.go = "Helen_3";
		break;
		case "Helen_3":
			dialog.Text = "����������. ��, ��� �� ��������� ����������.";
			Link.l1 = "� ���������� ���� ������, ����.";
			Link.l1.go = "Helen_wait";
			
			sld = GetCharacter(NPC_GenerateCharacter("HelenBastard", "pirate_1", "man", "man", 30, PIRATE, -1, false));
			sld.name 	= "�������";
			sld.lastname = "����";
			SetSPECIAL(sld, 9,8,7,6,7,8,9);
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade42", "pistol4", 350);
			SelAllPerksToNotPchar(sld);
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto7";
			sld.dialog.filename   = "Enc_OfficerGirl.c";
			sld.dialog.currentnode = "Helen_Bastard";
			sld.perks.list.BasicDefense = true;
			sld.perks.list.AdvancedDefense = true;
			sld.perks.list.SwordplayProfessional = true;
			sld.perks.list.CriticalHit = true;
			sld.perks.list.Gunman = true;
			sld.perks.list.GunProfessional = true;
			sld.perks.list.Energaiser = true;
			sld.perks.list.ByWorker = true;
			sld.perks.list.ShipEscape = true;
			sld.perks.list.Ciras = true;
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_SetImmortal(sld,true);
			DeleteAttribute(sld,"lifeDay");
			LAi_group_MoveCharacter(sld, "player");	
		break;
		case "Helen_wait":
			if (!CheckAttribute(pchar,"HelenMet"))
			{
				dialog.Text = "� ���� �����, �������. �����!";
				pchar.HelenMet = true;
			}
			else
			{
				dialog.Text = "��� ������, �������?";
			}
			Link.l1 = "������. ����, ����.";
			Link.l1.go = "exit_spec";
			if (CheckAttribute(pchar,"HelenQuest"))
			{
				Link.l1 = "� ��� ���������, � ���� ������ ����� �� ����� ���������� �����.";
				Link.l1.go = "Helen_nowait";
			}
			NextDiag.currentnode = "Helen_wait";
			NextDiag.TempNode = "Helen_wait";
		break;
		case "Helen_Bastard":
			dialog.Text = "� �� ��� ���? �������"+ GetSexPhrase("�� ��������","�� ����") +", �����"+ GetSexPhrase("��","��") +" ����� ������ ���� � �������? � ���� ������ � ��� ��������, ��� � ���� ������ ����� �������.";
			Link.l1 = "�� ����������. ��������� ������. �� �� ��� ���������� �� ������-�������� ��� ������ ���� ����� ����� � ������. ��� �������?";
			Link.l1.go = "Helen_Bastard_2";
		break;
		
		case "Helen_Bastard_2":
			dialog.Text = "������ ��� ��������? ���-�, ���� ��������. ���������, �������!";
			Link.l1 = "� �� �����"+ GetSexPhrase("","�") +", ��� �� � �� ���������...";
			Link.l1.go = "Helen_Bastard_exit";
		break;
		case "Helen_Bastard_exit":
			pchar.HelenQuest = 1;
			DialogExit();
			LAi_SetImmortal(NPChar,false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			chrDisableReloadToLocation = true;
			pchar.quest.HelenBastard.win_condition.l1 = "NPC_Death";
			pchar.quest.HelenBastard.win_condition.l1.character = "HelenBastard";
			pchar.quest.HelenBastard.win_condition = "OpenTheDoors";
		break;
		case "Helen_nowait":
			dialog.Text = "��������� ���, �������! ������ � ���� ���������...";
			Link.l1 = "�� �� ���! �� ��� �������?";
			Link.l1.go = "price";
			DeleteAttribute(pchar,"HelenMet");
			DeleteAttribute(pchar,"HelenQuest");
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
		//���������
		case "Angellica_meet":
			if (NPChar.alignment == "bad" && sti(pchar.reputation) <= 30)
			{
				dialog.Text = "��, �������! ���� ������ ����� ������ ��������� - ���� ������ �������� �����! ���� �� �����"+ GetSexPhrase("��","���") +", �������!";
				Link.l1 = "����� ����������! � �� �������, ��� � ��������� ��������� ���� ���-�� ������?";
				Link.l1.go = "Angellica";
			}
			else
			{
				dialog.Text = "�� �����, ��� ��� ���� � ��� ��������, �������.";
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Angellica_meet";
			}
		break;
		case "Angellica":
			dialog.Text = "�� ������, �������� ��������. ����� ������ �����������?";
			Link.l1 = "� ��� �� �� �������� ��������� �����������?";
			Link.l1.go = "Angellica_2";
		break;
		
		case "Angellica_2":
			if (!CheckAttribute(pchar,"AngellicaDuelInfo")) {dialog.Text = "������ ���� �� ����� � �� �������� �������������� � ������������ � ����."; pchar.AngellicaDuelInfo = true;}
			else dialog.Text = "�� ���, �����"+ GetSexPhrase("��","���") +"?";
			Link.l1 = "� �����"+ GetSexPhrase("","�") +"!";
			Link.l1.go = "Angellica_duel_exit";
			Link.l2 = "�������, �������.";
			Link.l2.go = "exit_spec";
			NextDiag.currentnode = "Angellica_2";
			NextDiag.TempNode = "Angellica_2";
		break;
		
		case "Angellica_duel_exit":
			DialogExit();
			NextDiag.currentnode = "Angellica_duel_won";
			NextDiag.TempNode = "Angellica_duel_won";
			ChangeCharacterAddressGroup(NPChar, "LeFransua_ExitTown", "enc01", "enc01_04");
			LAi_SetCheckMinHP(NPChar, 5, true, "AngellicaDialog");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DoQuestReloadToLocation("LeFransua_ExitTown","reload","reload3", "");
			chrDisableReloadToLocation = true;
		break;
		case "Angellica_duel_won":
			dialog.Text = "����������! �� ������� ������ ��� �� ��������� ������� ����...";
			Link.l1 = "�� ���� ��������� ���� ��������.";
			Link.l1.go = "Angellica_duel_won_exit";
			LAi_SetHP(npchar, 150, 150);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"AngellicaDuelInfo");
			LAi_SetImmortal(NPChar,false);
		break;
		case "Angellica_duel_won_exit":
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_warrior_DialogEnable(NPChar, true);
			NextDiag.currentnode = "Angellica_duel_won_2";
			NextDiag.TempNode = "Angellica_duel_won_2";
		break;
		case "Angellica_duel_won_2":
			dialog.Text = "������ � ������ � ��� ��������������, �������.";
			Link.l1 = "� �� �������?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
	}
}

void FireImmortalOfficer(ref chr)
{
	if (CheckAttribute(chr,"ImmortalOfficer"))
	{
		DeleteAttribute(chr,"ImmortalOfficer")
		pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) - 1);
	}
}