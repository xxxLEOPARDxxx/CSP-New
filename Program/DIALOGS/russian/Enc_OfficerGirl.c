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
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman")
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
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
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
			Npchar.CanTakeMushket = true;
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