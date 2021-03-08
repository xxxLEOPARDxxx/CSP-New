// BOAL ����� ������ ������� � ���������� 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	makearef(NextDiag, NPChar.Dialog);
	
	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;
	
	bool bGoldMine = false;
	bool bSilverMine = false;
	bool bIronMine = false;
	
	if(CheckAttribute(PChar, "ColonyBuilding.GoldMine.BuildingTime"))
	{
		bGoldMine = PChar.ColonyBuilding.GoldMine == true && PChar.ColonyBuilding.GoldMine.BuildingTime == false;
	}	
	if(CheckAttribute(PChar, "ColonyBuilding.SilverMine.BuildingTime"))
	{
		bSilverMine = PChar.ColonyBuilding.SilverMine == true && PChar.ColonyBuilding.SilverMine.BuildingTime == false;
	}	
	if(CheckAttribute(PChar, "ColonyBuilding.IronMine.BuildingTime"))
	{
		bIronMine = PChar.ColonyBuilding.IronMine == true && PChar.ColonyBuilding.IronMine.BuildingTime == false;
	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("���, �������, �� ����� ��� �������� ��������� ��������. ������ ���� �� ����� ���� � ���� � �������!", "����������� � ���� ����������� �� �������? ��� ��, � ������ ���, ���...");
				link.l1 = RandPhraseSimple("�� ��� ������...", "�� � � �� "+ GetSexPhrase("���������","����������") +" ���� ��������."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "������ �� �����, �������?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "������? � �� ��� �� �����?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "���, � ���� ������ ��������.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "�������, ��� �� ��������! ������� ������, ���� ��� �� ��������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// ������ ������ -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "������� �� ����� ������ � ����!";
				link.l2 = "��... � ���� ���"+ GetSexPhrase("","�") +".";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "������ � �����, �������, � ���������� �� ����. �� �������� ������������ - � ����� �� ��������.";
				Link.l1 = "������. ��������� - �������� ������ ������!";
				Link.l1.go = "Exit";
				break;
			}
			// ������ ������ <--
   			dialog.text = "��� �� ������, �������?";
			// ������ ���������� �� �������.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "� ���� ���� ��� ���� ��������� ��������.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			if (isOfficer(Npchar)) // �������� ��� �������, ��� �������� ���
			{
	            Link.l2 = "������ ��� ������!";
	            Link.l2.go = "stay_follow";
            }

			//aw013 --> ���� �� ��������� 
			if (!CheckAttribute(NPChar, "OfficerWantToGo.DontGo")) 
			{ 
				Link.l3 = "� ���� � ���� �����������."; 
				Link.l3.go = "contract"; 
			} 
			//aw013 <-- ���� �� ���������
           		// boal ����� � �������
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "��� ��� ������ ����� � �������, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. ����������� ������
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "� ����, ����� �� ����� ������� � �������, �� ������� ������.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "������, �������� ������ � �������� �� �����.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (npchar.id != "Sharp_Sibling" && npchar.id != "SharleMary")
			{
				Link.l4 = "������, � ����� �� �������� � ����� �������.";
				Link.l4.go = "AsYouWish";
			}
			
			for(iTemp=1; iTemp<=3; iTemp++) // �����, ���� ���� ��������� ������
			{
				attr = "Companion" + iTemp;
				if (CheckAttribute(PChar,"CompanionTravel."+(attr)+".ID")) 
				{
					if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
					{
						Link.l4 = "����������� � �������, ������.";
						Link.l4.go = "CompanionTravel_ToSquadron";
					}
				}
			}
			
			// ������� -->
			if (PChar.sex == "woman" && !CheckAttribute(pchar, "questTemp.MainHeroWoman"))
			{//��������� ������� ��� ������
				pchar.questTemp.MainHeroWoman = true;
				SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
			}
			
            if (PChar.location == Get_My_Cabin() && npchar.id != "Sharp_Sibling")
            {
    			if (PChar.sex == "woman" && NPChar.sex == "man")
    			{
					Link.l5 = RandPhraseSimple("��� �� �� � ����� ����� �����...�? �������� ��� � ������� ����... ����� ���������...",
	                                           "�������� ����� � ���� ����� ������� �������. �� ������ ��������� �� �� ����?");
	                if (drand(40) + 30 < sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) && GetQuestPastDayParam("pchar.questTemp.MainHeroWomanSex") >= 5)
	                {
	                    Link.l5.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l5.go = "Love_Sex";
	                }
                }
            }
			
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
            
			if(PChar.ColonyBuilding.Stage == "3" && PChar.Colony.Guardians.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l9 = "� ���� ��������� ���� ����������� �������� ����, ������� �� ��������� ��� ���������� ������� ����� ������� ''" + PChar.ColonyBuilding.ColonyName + "''.";
						Link.l9.go = "ColonyGuarding_Hovernor_1";
					}
				}	
			}
            
			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.Mines.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
						{
							Link.l10 = "� ���� ��������� ���� ����������� ��������, ������� ��������� �� ���� �������.";
							Link.l10.go = "MinesCommander_Hire";
						}
					}	
				}
			}
            	
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Plantation.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
						{
							Link.l11 = "� ���� ��������� ���� ����������� ���������, ������� ��������� �������� �� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' � �� �����������.";
							Link.l11.go = "PlantationCommander_Hire";
						}
					}	
				}
			}
            	
            Link.l12 = "������. ������.";
            Link.l12.go = "Exit";
        break;

		case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("�������, ����� �������� ���� ����������.",
                                           "� ����� ����� �� ��� ���� ���, �������.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "�������! ���� ������������, ���� ����� �������� � ���� ������ ������.");
			link.l1.go = "Love_Sex_Yes_2";
        break;
        
        case "Love_Sex_Yes_2":
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// ��������
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);
			SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;
        
        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("�� ��� ������ �� ������, �������.",
                                           "�������, �������, ��� ��� �����������, � ��������.");
            link.l1 = RandPhraseSimple("��, �� ������� ������� �����.", "���. ������ �������� � ����� �����.");
			link.l1.go = "exit";
        break;
        
        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("���!!!?? �������, �� ����� �� ������� �� ����� � �� ���� � �������?", "�� �������, � ��� ��� ��?");
            link.l1 = RandPhraseSimple("�� ��� �������.. �� ����� ����������, �� ��� � � ���� ����������", "�� �� ���� �� ��� � �������, ����� ��� ����� ���� ��!");
			link.l1.go = "Love_Sex_2";							
			link.l2 = RandPhraseSimple("������ ����, ���������, ����� ������ ���� ����������, ���� �� ����������..", "��.. �����, ��������...");
			link.l2.go = "exit";	
        break;
        
        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("�������! ������� ���� � �����, ���� �� ������ � �����, �������� ��������!", "��, ��� � ������ � ���������� ���������� ���, �������, ��� ������ �� ������!");
            link.l1 = RandPhraseSimple("�����, �� ��������. � ��� �� ���� ���� ����������. ������..", "� - ���� �������! � � ���������� ����!");
			link.l1.go = "Love_Sex_3";							
			link.l2 = RandPhraseSimple("������ ����, �����, ����� ������ ���� ����������, ���� �� ����������..", "��.. �����, ��������...");
			link.l2.go = "exit";	
        break;
        
        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("�� ���! �� �������� �� ���! � ����� ������!", "������������� � ����? ���� ������ ��������, ��� �� ��� ��������..");
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
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "�������, ����� ������?! ����� ������� ������� ���-������ ���������!";
				Link.l1 = "��, �� ����.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "����� ���������, "+GetAddress_Form(pchar)+" �������!";
			Link.l1 = "������.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // ��������� ����������� �������
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "����� ���������, "+GetAddress_Form(pchar)+" �������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;

        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.CanTakeMushket = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		//aw013 --> ���� �� ��������� 
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
			// DeleteAttribute(NPChar, "contractMoney");//Mett: ��� ����� ������������� �� �������, �� ����� ������������ ��� ����������� ����� ���������
			Link.l1 = "��� � �������! ������������"; 
			Link.l1.go = "Exit"; 
		break; 
		//aw013 <-- ���� �� ���������
		// boal 29.05.04 ������ ����� ������� -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("�������, ��� ����� ����... � �����, ����� ��������. ��� �� ����� �������� ����, ����� ������� � ����� ������ �� ������� �������, � � �� ����� ���� �� ������. ��� �� �������� ��� � ���� ������ ����� ������.","�������, ����� ��� ��������, � �� � ������� ��� �� ����� ���� �������, � ������ ������ � �� �����. ���� ������� ������ �����, ����� �������, �� �� ��� ������� ������� ����������.","�������, ������� ������ ���, �������, ������� - ��������� � ����������� ������, �� ���� � � ���� ��������. ������� ����� � ����� ������, ������� ������ �� ����� �������. �� �� ��������� ����."), LinkRandPhrase("�������, � ������� ���������, �� ��� ������ � ������� �� ������������ ��� ��������, ��� ������ �����. ���� ��������� ����� �������� ������� ������. �������, ��� ����� �� ������, ������� ����� ��������.","�������, ��� ��� �������� �� ������ ������������. �����-�� ���� ����� � ����� ����� ������������. ��������� �� ������� ����� - ����� ��������.","�������, ��� ��� ����� � ����� ����������. � ���� ����� ������ ����� ������� �� ������ �����������. ����� �������� - ����� ��� ����� ������ ����������."), LinkRandPhrase("�������, ���� �� ���� ��� � ���� �������. ������� ������� - �������������. ���������, ���� ������, ����� �����-������ �� ������� - �� ���� ������.","�������, ������ ������ ��� ���� ������������ �� ����������� ����� �����. ������� ���� ������ �����, ����� ������ ��������� ���� ���������, ����� ����� ��������... � ��������������� �� ����� ��� � ��������� - �� ������ ������... ����� ��������, ������ ���������.","�������, ������ ���� ���� - ��� ���, �� � �������� �������� ����� �� ���. ��� ������� � �� ���� ���� ��������, ��� ����� �� ������ ������? ����� �������� - ��������� �� ���� ������ ����� �����������."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("��, ���� ��� ����������... �� �������� �� ����� - ���, ���� �����.","�� ��� �, ������� �������. ���� ��� ������ �� �������������. ���... �� �� ��������, ���� ������"+ GetSexPhrase("","�") +" �����.","�� ��� �� �����! ��� � ������� �������� � ����� ������������ ������!.. ���, ����� �� ���� ������ �����..."), LinkRandPhrase("� ������ �������. ����-�� �� �� �������������... �� �� �����, ������ �� ������ � � ���� �� ��������"+ GetSexPhrase("","�") +", ��� ��� ����� � ������ ��������.","��� �� �� ����"+ GetSexPhrase("","�") +" �� ���� ��� ��������! ������� ������� ��� � ���... ������ ���"+ GetSexPhrase("","��") +" �����������, ������ �� ����. ����� �� ����� ���������������� � �����... ������� ���� � �� ��������� ��� ������ �� �����.","��� ���� ��������� - ���������� �� �����... ���� ��� ���� ����� ����� �� �������."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("��-�, ��� ������, ��� �� ����������... � � ���� �� ���� �����������... ��, ��� ������� ������� - ����� ������������. ��� ���� "+sti(NPChar.rank)*250+" ������� �� ������ ������. � �� ����� ���, ���� ����� ������.", "�� ��� �, � ��� �� ����� � ������ �� �����. ��� ����� - ���. �� ����� "+sti(NPChar.rank)*250+" ������� �� �������. ��� ������ ����������.", "����... ���� ��� ������ ��� ������ ���� ���������. ��������� ���� "+sti(NPChar.rank)*250+" ������� �� ������������ ������ �����. �� �������� �������, ������� ������ ��� �� ����� - �� ��� ����� ���� ���������..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("���, ������, ���. � �� ���� ���������, ��� ������ ���� ���� ��� ����, ��� ��� � �����? �� ���� ������ � ���� ��������� - ���� �� ����� � �� �����.", "��� ��� �������! � ����� ����� ������� ������������� �������. ��� ��� � ������ ����� ���� ������. ����� ����� �����, � ���"+ GetSexPhrase("","�") +" �������� ���� ��������.", "������� ��������. � ���� ������ ������� �� �����. �� ���� �, �� ������ ������� �������, �������� ��������������. �����, ���� � ���"+ GetSexPhrase("","�") +" �� ����� �������.");																																
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "������� ���, �������! ����� ����������� ��������. � ���� ��� �������� ���-��� �� ����� �����, ����� ������� �� �������?";
			Link.l1 = "�� �������... ������ ����� ������� ������ �� ��� ��������...";
			Link.l1.go = "Get_out_�2_chang";
			Link.l2 = "�� �����. ������ ���� � ������ � ������ ��� ���� �������...";
			Link.l2.go = "WantToGo_free";
		break;
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("�� ��� �� ���? �����������, � ��� �� ����� ���������. � � �� �� �� ��� � ������ ������ ���� ������!", "�������, ������� � �� �� ��� ������� �� �������� ����� �������������� ������ ���� ������?");
			Link.l1 = LinkRandPhrase("����, ��� ������ ���� �� ��������. ��� ������ ���������� ���������? ����� ���� ������ ���������� - � �������� � ����� ������ ������������, � �������� ���������...", "�����, ������ �������� ��-�������. �� ����� ����� �� �� ����� ��������?", "��� �� ����. � ��� ������ ������������� ��������� �������?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple("�-� ���, ��� �� ����������... ���� �� �������� ����� � �������, ����� ���� ������ ���� ������ ���������... �� ��� ������ ������ �� ���� ����� ����� - ��... ������ � ������ ���� �...", "��, ��� ��������� ���������. ������, ��� �� �������, ��� � ���� ���"+ GetSexPhrase("��","��") +" - � ������� ������� ��� ����� � �������. �� ���� ���� �������� ������ ������ ���������� - ��� ����� � ��� ������������, � ���� �� - '������ ���� ������'."),
				LinkRandPhrase("���� �� � ���� �� ������, ������� ���� ��������� �. ������ ��������� � ����� ������������, ���� �� ������ ������������ ��������� �� ���� ���������!", "��. ��� ��������� ���������. �� �� ��� �� ��������� ���� ���������� ���� �����. ������� ���� ������ � ������ �����������, ��� ������� �������.", "�������...� �����-�� �������� ������� �����. ����� ������ ������: '���� ��� �������� ������... �� ����� ������� �� ��������� ������ � ������ ������, ������ ����, ����� ������ � ������.' �� ��� ���� ����� �������?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("��, ��� ������ ����. "+sti(NPChar.rank)*500+" ������� �� ���� � � �������.", "��, ������� �� "+sti(NPChar.rank)*500+" ������� � �� �������.", "��, ��� ����� ����� ��������, �� �� "+sti(NPChar.rank)*500+" ������� ����� � ��������� ���.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("��� � ������������.", "������. ���� ��� �� ���� ����������...", "���� � ���� ��������! ��, ��� ������ - �����.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("��, ��� �� ���������. �� ����� ������ ����� ���� �������� ������. �������, ����� ���� ���������.", "������ �� �� ���� ������. �������, ������ �� ������� �����. �� ������� - ��� ���� �� ���� ��������.", "� �� �����"+ GetSexPhrase("","�") +" ������� ����� ������. ������ ����, �� ����� �� ������� - � ����� �� ������.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "�� �����, ��� ����� ���� - �������... �� ������, ��� � �������� ������ ����� ����...";
		Link.l1 = LinkRandPhrase("��� � ������. ����������� � ����� ������������, � ���� �������� �� ��������� �����.", "������ ����������� �� ����. � � ��������� ��� ���������� �������, ������, ��� ������� �� ��������.", "���-���. ������ - ���� ������, � ������ �������� ����� ���������.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
            Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;
		
		case "WantToGo_free":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();			
				break;
			}
			//navy <--
            Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		
		case "WantToGo_free_Yet":
            Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("�� �� ��������, ������� - ����� ���� � ���� ���������.", "�������, �������, ��� �� ����� ����������. ������� ��� ����-�� � ����� �����������.", "��, ���� ��������� � �������. ������ ������ �������, ��� ���������� �������� ������.");	
		Link.l1 = RandPhraseSimple("��, ��������� ���� �������...", "�����. ����������� ���� ������.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 ������ ����� ������� <--
		
	// �������� �������� ������� � ��������� -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("�������, � �� ���� ���� ������ ���������� ���� ������� � ���������� �������.","�������, � ����� �� ����� ��������� ������� � ����� �����������. � �� ������, � ������.","�������, ���� ���������� ������� ������ ����������� �� ���������� ���������� � �������."), LinkRandPhrase("�������, ����� ��������, ��� ��� ��� � ��� �� ������ ��� �������� �������. � ���������� �� ����� ���� ����� ���������� ����� ������� ������.","�������, �� ����� ����� ��������� ���������� �� ����� ������ �����, ���������� �������� � ����-�������� ����� ��������. � ������ �� ����� ������� � ����� �������.","�������, �� ������� � ������� ����� ����������� - �� � ��� ������ ������ �����������. ���� ���������� �� ����� � ����� ������.")) + " ��������.";
			Link.l1 = "���?!! � ���� ������ �����, � �� ����������� �������! ������ ��������� �� ���� ������!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "� ����� ����"+ GetSexPhrase("","�") +", ��� �� �����... ����� ������ �� ��� ����. �� ��������� ��� ���� �� � ���. ��� "+sti(NPChar.rank)*500+" ������� - ����������, ���� ������ ������ �� ����.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("���. ���, ������, ��� �� ������. � ����, ������� ���� ������������� � ������� �������, ���� �� ���? ��� �� �������� ������ � ��������� �������� - ����� ����������? ����� �� � �� ��� �������� �������! ��-��-��-��...", "��, ��� ��������� ���������. � ���� �� �������� ���� ����������� �������, ����� �� ������ ������� ������? ��� � �������� �����������? ������ �������� ����� ��������, ���� �� �������� ��������� � ������ ��������...", "�� ��� �����!.. ������, ��� �� �������, ��� � ���� ���"+ GetSexPhrase("��","��") +" - � ������� ������� ��� ����� � �������. �� ����, ��� ������� - ���� ����, � ���� �� - �� ������� �����.");
			Link.l3.go = "WantToGo_stop";
			}
			else
			{
            dialog.text = RandPhraseSimple(LinkRandPhrase("�������, ���� ���� � ������������ ��� ������ �� �� ����. � �� ����� ���� ������ ��������� ����������� ������ ���� ��������. ��������.","�������, � �� ���� ����� ���������� � ��� �� ������. ������� ������� ��������� ��� ����� - ��� ������� ���������� ����� ���� ��������� ����� ���������. � �����.","�������, ���� � ���� ������� �� ����� �����������. � ����-�������� ���� �� ������ - ��� �� ������ ���� ���������� �����, ���� ������ �� � ���. � �����."), LinkRandPhrase("�������, � ������ ������, � ��� ������� ����� ����� �� �������� �����. ����� ������ �� �� ���, � �����. ��������.","�������, �� ������� � ������� ����� ���������� - �� � ��� ���� ������ �� ������ �����������. ���� ���������� �� ����� � ����� ������, ������� ��������.","�������, ��� ��������, ��� � ����� ���������� �������. � �� ��� ����������? �������� �������������������! � �� ���� ������ ����� � �����."));
			Link.l1 = RandPhraseSimple("�-��. � ����� ���������� � ������ ���� ��� ������ ��� ������ ���� ���������. ��� �, ���������� �� �����.", "����� ��������� �� ����� ��� ���� ��������������. ��� ��������� � ������ ���� ����� �� ����������.") + " ����� �������.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "� ����"+ GetSexPhrase("","�") +", ��� �� �����... ����� ������ �� ��� ����. �� ��������� ��� ���� �� � ���. ��� "+sti(NPChar.rank)*500+" ������� - ����������, ���� ������ ������ ����� �����.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("��. ��� ��������� ���������. �� �� ��� �� ��������� ���� ���������� ���� �����. ������� ���� ������ � ������ �����������, ��� �������.", "�������...� �����-�� �������� ������� �����. ����� ������ ������: '���� ��� �������� ������... �� ����� ������� �� ��������� ������ � ������ ������, ������ ����, ����� ������ � ������.' �� ��� ���� ����� �������?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("�� ��������� ���� ���������! �, ��� � ���, ����� �� ������, �� ������ �������� ������ �� ����.", "� ��������� �������! � ������ ������� ������, ����� �������� ������.", "� �� ���, ����� ������� ���� �� ���, ������� ��� ������� �����! �� � �� ��������� � ����� ����������� � ���� ������!");
				Link.l1 = "�-� ���, ��� ��� �� ����������... ���� �� �������� ������ � ������� - ��, ����� ���� �������� ����� ������... �� ����� ����, ��� ������ �� ���� ����� ����� - ��... ������� ����� - ������ � ����� �� ���, ��-��... �� ������ ��� ���������, ���� �� ��� ����� �������� �� ��������, ���� �� �������...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "��, �����. ���... �� �� ������� ���� ������� ��������� ���� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("�� ��������� ���� ��������! �, ��� � ���, ����� �� ������, � ������ �������� ������ �� ����.", "� ��������� �������! � ������ ������� ������, ����� �������� ������.", "� ��� �� ���! � � �� ������� � ����� ��������� �� ����� ������!");
				Link.l1 = "�-� ���, ��� ��� �� ����������... ���� �� �������� ������ � ������� - ��, ����� ���� �������� ����� ������... �� ����� ����, ��� ������ �� ���� ����� ����� - ��... ������� ����� - ������ � ����� �� ���, ��-��... �� ������ ��� ���������, ���� �� ��� ����� �������� �� ��������, ���� �� �������...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "��, �����. ���... �� �� ������� ���� ������� ��������� ���� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("���� ���� ��������� ����� ������, �� � �������� - � ���� ������ ��� ������� ������. �� ������, ��� � ��� ����� �� �� ����������� ����...", "�� �����, ��� ����� ���� - �������... �� ������, ��� � �������� ������ ����� ����...");
			Link.l1 = RandPhraseSimple("��� � �����... �������, ���� � ���"+ GetSexPhrase("","�") +" �� ����, ����� ���� ����������.", "��� � ������ - ������� ����... � � ���"+ GetSexPhrase("","�") +" ����, ����� ���� ���������.");
			Link.l1.go = "WantToGo_Munity"; //���� ���� ����� � �������
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "��� ������� �� ��������� ���� �������� �������! �� �� ���� ������!", "�� �������� �������, ��� ������� �������� ������� �������?! ��� �� ������� ����������� ������ � �����. � ���� �� �� �����, ����� ������� � ������� ���, ��� �� ����� ������� �������!");
			Link.l1 = NPCharRepPhrase(NPChar, "�� ��� �... ������ ��� �������� ���� ������. �������, �� ��������� ����� ������� �� ���.", "���� �� � ����"+ GetSexPhrase("","�") +", �� ���� �����"+ GetSexPhrase("","�") +", ����� ��������"+ GetSexPhrase("","�") +" ���� � ������� ��� ����� � ��� ����� � ������� - �������, ��������"+ GetSexPhrase("","�") +" �� ���� ����� �� �����. � ������ ��� �� ������ ��� ��������...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "��, ��� �, ������, ��� ���� ��� ����� �������. �� ���� - ������������ �� ���� �� �� ��������.", "��, �����. ���... �� �� ������� ���� ������� ��������� ��� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			dialog.text = NPCharRepPhrase(NPChar, "������ �� ����� ���� ������! ��� �� ����� ����������� �������� ������� ������ ���� �����?! �� ���� � ��������� - ��� �� ����������� ���! � �� �������... ����������������, � ������ �������, ���� ������� �� ��� ������� �� �������������?!", "������� ���� �������, ��� ���� �� ��������! ��������.");
			Link.l1 = NPCharRepPhrase(NPChar, "���, ��������, �� ������� ���� �� ������. ����� ������� �� ��� ����...", "�� ��� ������, ��������, � ���� ��� �� ���"+ GetSexPhrase("","�") +" �������...");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. ������� ������� �������
			Diag.TempNode = "Hired";
			if (sti(Pchar.questTemp.MunityOfficerIDX) != GetCharacterIndex(Npchar.id))
			{
				Pchar.questTemp.MunityOfficerIDX = GetCharacterIndex(Npchar.id);
				Pchar.questTemp.MunityOfficerIDX.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// �������� �������� ������� � ��������� <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "�� � ������ "+ XI_ConvertString(Npchar.quest.officertype) + " � ���� �����. " + Npchar.quest.officertype_2 + "����� ������� ��� ������, ����� �� ������.",
                                    "��, �������, ��� � �������� " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "�������� ���� �� ���� �����, ������� - ��������� � ���� ����.");
			Link.l1 = "������� �� ������?";
			Link.l1.go = "price";
			Link.l2 = "� ��� �� �� ���� ������������� ��� ����������?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "���, � ���� ��� ���� " + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("���, �������, �� ����� ��� �������� ��������� ��������. ������ ���� �� ����� ���� � ���� � �������!", "����������� � ���� ����������� �� �������? ��� ��, � ������ ���, ���...");
				link.l1 = RandPhraseSimple("�� ��� ������...", "�� � � �� "+ GetSexPhrase("���������","����������") +" ���� ��������."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "������� ����������, �������? ������, ��� ����� " + XI_ConvertString(Npchar.quest.officertype) + " ��� �� ��������?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "�������, ���. ������� �� ������?";
                Link.l1.go = "price";
			}
			Link.l2 = "����� �� ������ � ����?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "� ���� ������ ��������. ��������� ����������.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "�����, �� � ���� �������� �� " + Npchar.quest.OfficerPrice + " ��������.";
			Link.l1 = "�� ������� �� �� ����� ������?";
			Link.l1.go = "trade";
			Link.l2 = "� "+ GetSexPhrase("��������","��������") +". ������ ���� ����������� � �������.";
			Link.l2.go = "hire";
			Link.l3 = "�� �� ������ ���� �����. ������.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // ����� ����� ��������� ����� �����
				dialog.text = "������... �������, � ����� ����������� ���� �� " + Npchar.quest.OfficerPrice + " ��������. �� ���?";
				Link.l1 = "��� ��� ��� �����. �� ������.";
				Link.l1.go = "hire";				
				Link.l2 = "� ��-�������� ������, ��� ��� ��������. ������.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "���, �������, � ���� ������ �������, ������� ��������. ���� ��� ������� ������ ��� ��� - ������� ����-������ �������.";
				Link.l1 = "�� �����, � "+ GetSexPhrase("��������","��������") +". � ���� ����.";
				Link.l1.go = "hire";				
				Link.l2 = "��� � � ��������. ����� ��������.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "��������� ���, �������. �� �� ���������, ��� ������ ��� ��� ������.";
				Link.l1 = "������� � ��� ������.";
				Link.l1.go = "Exit_hire";								
			}
			else
			{
				dialog.text = "��, ������, � ��� �������� � �����������! ��������, �������, �� � �� ������� � ������.";
				Link.l1 = "�� ��, ����!";
				Link.l1.go = "Exit";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "������ � �����, �������, � ���������� �� ����. �� �������� ������������ - � ����� �� ��������.";
			Link.l1 = "������. ��������� - �������� ������ ������!";
			Link.l1.go = "Exit";											
		break;
        
        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "�������, �� � ��� ���� ���� �������!";
				Link.l1 = "�������, ��������...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "������������ ���������� ���� � ����� " +
                     FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
                     "% �� ���������� �����. �� "+GetCrewQuantity(PChar) + " �������� ����� " + makeint((GetCrewQuantity(PChar)+6) / 10) + " ��������� � ����. ��� ��� ����� ����������� �����.";
            Link.l1 = "�������.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "����� ����� ����������?";
            Link.l1 = "���� �����!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "������ �� ���� � �� ��������!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "� ����, ����� �� �������� �� ������������ ���������� �� ����.";
				Link.l3.go = "TargetDistance";
			}
		break;

		case "TargetDistance":
			dialog.text = "�� ����� ������, �������? ������� � ������, �� �� ����� 20-��.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "�������, ��� �� ������ ���!";
				link.l1 = "������, �������� �����...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "� ���� ������ �� �����, ������ �� ��������. ��� ��� ����������, �������?";
				link.l1 = "��, ������ ��� �� ���� � ���������.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "� ������� �������, ��� ����� 20 ������ �� ���� ��� ��������� ������.";
				link.l1 = "������, ������� �� ���������� � 20 ������.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "������ �����, �������� � ��������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// �������� �� ���� -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "�������, ���� ��� � ��������� ������� ������ ��������� - ������� ������� � ����� ������� �� ������. ��� �� ������ ������ ��������� ���� �� ����?";
					Link.l1 = "��... ���, � �� ��� ����"+ GetSexPhrase("","�") +" � ����. ���������, ���� �� ����� � ����.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// �������� �� ���� <--
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) < 41) //����� ������ ������
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("��� ��� �������!","� ����� ��� �������?!","� ���� ��� �����?!"), RandPhraseSimple("�������, �� � ���� ���? �������� ����� ������� �� � ����, �� � ����!","���! � ��� ��� � ��� �� ������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("� �����"+ GetSexPhrase("","�") +" ������� ������� � �������. �, ��������� ��� �� �������� ���� ��������������� � ���������,","���� ����������� ��������� �� ��� ������, ��� ������������� ��� �����, �������","����������� � ����������� � ���� ������� �� �����! �������"), LinkRandPhrase("��� ����� ��������, ��� �� ������ �������� ��� � ��������� �������, ��� ����� �������� � ������ ���. �������","��� ��������� ������� ���� ����������� �������, � �� �������"+ GetSexPhrase("","�") +" ������� �� ����������. ��� ���,","�� ��������� ��������� ����� � ����-�������� �� ����� � ����� ��� �����, �������� ������ �������� �� ������� ������. ��� �� ����� ������������ ����������, �������")) + " ��������� � ������ �����.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) >= 41) // ����� ������ �����
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("���� � ������ ������� ������ �������?","��������� ����� ������� ����� ������ �������?"), RandPhraseSimple("����� �����������, �������","������ ����������. �� �������� �� ����� ���������."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("���� ������������� �� ���������� ��� ��������� � ����� ������������.","� ���������, �� ���� �� ����� ��������� �������, � �������� ��� �� ������...","�� ������� ������, � �������� �� ������, �� ����� ���� ���� ����������. � �� ��������� ���� ������."), LinkRandPhrase("� ������������"+ GetSexPhrase("","�") +", ��� ������� � ���� ���� �������. ��� � ���� ���������� � ��� ��������, ������� ������ � ����� ������� �� �����?","������ �� ����, ������ �����, �� �����... �����, �� ������ �� ��������� ��������.","���� ����� �� ���������� ���� ������������, �� ������ � �������-�� ���"+ GetSexPhrase("��","��") +" ��������� ������."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) >= 41) // ������ ������ ����� 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("��. ���� � ������ �������?","��� ��������� ���������. ���� � ������, ��� ��������� ��� �� ����������?"), RandPhraseSimple("����� �����������, �������.","�������, � ������ ��������� ������� ������ ���������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("���� ���������� �� ���������� ���� ������������, �������","� ���������, �� ���� �� ����� ��������� �������. ��� ���,","��� ��������� ������� ���� ����������� ������. � �� �������"+ GetSexPhrase("","�") +" ������� �� ����������, ��� ���,"), LinkRandPhrase("�� ���� ����� �����, ��� ������ �� ���������� ������� � �������������. ����������� �� ��� ����� �� �����! � �� ����� �����������, ��� � ������ �� ���������"+ GetSexPhrase("","�") +" ���� �� ����... ��� ���,","���� ����������� �������� ������ ���� �����, �� ��� ���� ������� � ��������� ������ �������� ������. ��� ���,","���� ������������� �� ���������� ��� ��������� � ����� ������������. �������")) + " ��������� � ������ �����.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) < 41) // ������ ������ ������
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("�������, � ����� �� ������ ������ ��������! ����� ���������, ��� ���������?","�������, ��� �� ���� ��� �������?!","��� ��������� ��� ��������, �������?!"), RandPhraseSimple("��� �� ���, �������?! ��� ����� �� ���� ���������, � ��� - �� ����...","���! �����, �� ������ ���� ���� ��� ����������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("�� ���������� ������� � ������� - ���� �� ����� � ���������� ��������. � � ��� ������� ����� ������"+ GetSexPhrase("","�") +". ��� ���,","�� ����� ���� �� �����������, �� ������ � �������-�� ���"+ GetSexPhrase("��","��") +" ��������� ������. ��� ���,","��� ����� ��������, ��� �� ������ �������� ��� � ��������� �������, ��� ����� �������� � ������ ���. �������"), LinkRandPhrase("��� ����� �� ����������, ��� ������� ������� �� ����� �� ��� �����, � �� ������� �������� ������������ ����������, ��� ���","� ������������"+ GetSexPhrase("","�") +", ��� ��� �������� ����� ��������. ������ � ����"+ GetSexPhrase("��","��") +" �� �� ���� ������ ���"+ GetSexPhrase("","�") +"? ��� ���,","������ ������� ������, �� ��������� ������� � ����-�������� �� ����� � ����� ��� �����. �������, �� �� �����, ��� ��� ����� ������������ ����������? ��� ���,")) + " ��������� � ����������.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("��� ������ ���! �� �����, ���� ����. �� ������: � ��� � ������ �� �������. ��� ������� ������...","����������, ���� ���� � ������������ ��� ���� ���-�� �� �� ����. ��� ��� - ��������...", "�� � ���� � ����! ����������� �� ������ �����������. ���� ��� - '�����'!"), LinkRandPhrase("�� ��� � ��� ������� � �� ���������, �� �����, � �������� �����. ������� ����������� �������...","�� ���� ������ � ���� ������� �� ����� �����������. � ����-�������� ���� �� ������, ��� �� ������ - ���� ���������� �����...","������, �������, ���� ��-������. ��, ����� ���, � ���� �� ������ �����..."));
			Link.l1 = "����. ������ � �� ���� �������� ����� ��� �������. �� ������� �� ��� �������� � ����� ���������.";
			Link.l1.go = "exit_bad";
			Link.l2 = "��� � ������ � �����.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�� ��������. � ����������"+ GetSexPhrase("","�") +" ���� �������� ������� "+sti(NPChar.rank)*500+" �������. �������, ��� ������ ��� �������.";
				Link.l3.go = "Get_out_�1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("���������! ��� ������ '������ �����'?! �� ��� ���� � ���� ������ ��� ������� ����������, ���� �� ����� ���� ����������, ����� ����������!", "��! '������ �����'! �� �������, � ������� ���������� ����, ��� ������?!", "�������, �������, � ��������� �������� ��� ���� �� ��������. � �� ������� ���������� � �����, ��� � �������.");
			Link.l1 = "������, ���������. �� ���� ���� � �� ����� ��������� ������." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "� �������� - ���� ������ ���������. ������ �������� ����.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�� ��������. � ����������"+ GetSexPhrase("","�") +" ���� �������� ������� "+sti(NPChar.rank)*500+" �������. �������, ��� ������ ��� �������.";
				Link.l3.go = "Get_out_�1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("�� � � �� ���� �������� � ��� �������������. ������ ��� ����������� �������� ����� �� ���������!", "�� � ������ � ��� �� �������� �� ����� ������. ������ �������� ������� ��������� �����������!") + " "+sti(NPChar.rank)*1000+" �������, � �� ������� ���� � �����.";
			Link.l1 = "� ���������"+ GetSexPhrase("��","���") +"... ����� ��� ���������, � ����������� �� ����.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "� ����� ������� ����� ���� ����, ���� �� ��������� ������� ���� ����? �� ��� ������� ��������� �� ��������������!";
			Link.l2.go = "Get_out_�1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "�����. ���� ���������� � �������� ��, � ��� �������.";
				Link.l3.go = "Get_out_�1_chang";
			}
		break;

		case "Get_out_�1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "��, ��� ������ ������ ����. ��������!";
			Link.l1 = "�������, ���� ������ ������ �� �����������.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_�1_strife_battle":
			dialog.text = LinkRandPhrase("�������� ��� ������������ ��������� ��������. � ������ �� ������� ��� � ����� ����������! � ��� �������, ��� ����� �������� �� ����!", "��� �� ��������������, � ����������� �������� ������������ �������! � � � ������, ���� �� ��� ��� �� ������!", "� �������� ������� ����� ������� �� ������ � ���"+ GetSexPhrase("��� ���������","�� �����������") +" ��� ��. �� ��� ����� ����� ���� ����������� �������� ���������. ������ ���� �������������� ��������� ������.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "�����. ��� ���� ������... � ������ �������� ������!";
				Link.l1.go = "Get_out_�1_ForMoney_angry";
			}
			Link.l2 = "�� �����������! � �� ������� ������ ��������� �������� �� ���� �����!";
			Link.l2.go = "Get_out_�1_strife_death";
		break;

		case "Get_out_�1_strife_death":
			ChangeCharacterReputation(pchar, 1);
			OfficersReaction("good");
			dialog.text = "�����-�����, �������! ������, �����"+ GetSexPhrase("","�") +" �� ������ ���������� ���������!";
			Link.l1 = "����� ���, � ����� �� �����"+ GetSexPhrase("","�") +"!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_�1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "��, ��� ������ ������ ����. ��������!";
			Link.l1 = "�������, ���� ������ ������ �� �����������.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("�� ��� �, ������ �� ������. ��������, �������, �� ��������� �����...","����� ����, �������. ��, ����� ���, � ��������. ��������.","��, �������, ��� �� �������!.. ��������� ����������."), LinkRandPhrase("����, �������. ��� ����� ��������� ������� � ���.","��� ���� ��� ������... �� � ��� �� �����, ��������.","�� ������������� �� ���, �������. �� � ������ ���� �������. ��������."));
			Link.l1 = "����, � ���������"+ GetSexPhrase("","�") +". ����� ����� � ����� ��������� �����.";
			Link.l1.go = "exit_good";
			Link.l2 = "�� ���������. ����� ����...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "������... � ���� ������� ����������"+ GetSexPhrase("","�") +". ����� �� ������� ������� - ��� ��� ����� ����� ��������� �����...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "������... �� ���� ��������� ���� � ������� ������. ��� ����� "+sti(NPChar.rank)*500+" �������, ����������, ���� ������ ������ ����� ������.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "�� � ��� ����, ������� ���������...";
			Link.l1 = "� ����"+ GetSexPhrase("","�") +", ��� �� ���� ��������� ������...";
			Link.l1.go = "Get_out_�2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "������� ���, �������! ����� ����������� ��������. � ���� ��� �������� ���-��� �� ����� �����, ����� ������� �� �������?";
			Link.l1 = "�� �������... ������ ����� ������� ������ �� ��� ��������...";
			Link.l1.go = "Get_out_�2_chang";
			Link.l2 = "�� �����. ������ ���� � ������ � ������ ��� ���� �������...";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("�� ��� �, ���� ����. �� ������: � ��� � ������ �� �������, ���� ���� ������� �������� � ������.","����������, ���� ���������� ������� ��� ���� �� �� ����. ��� ���, ��� ���� ��� ������ ������ ���� ���������... � �� ����� ���������� ������� ������.","�� � ����������� �� ������ ������������. �� ����� ����� ���������� �������� � ����-�������� ����� ������. ������� �������, ������ ���� �������!"), LinkRandPhrase("����������, � ���� ���� ���� �� ����� � ����� ������. ������� � ������� ����� ����������� - �� � ��� ������ ������ �����������.","��, ���� �� ������ ��� ���������� � ������� ������� - �� ��� ��� ���� ����������. ������� ������ ���������� �� �������.","���� ������� ��, ��� ���� ��������� �������. ��������� ����������."));
			Link.l1 = "����. ������ �� ����� ������� ������ ���� ���������. �� ��� ��������� �������� � ����.";
			Link.l1.go = "exit_bad";
			Link.l2 = "���-���. �������� ��� ����� �����������.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�������. ��� ���� �� ������ "+sti(NPChar.rank)*500+" �������. � �� ������ ��� �������, � ��� ����� ����� ����� ��������.";
				Link.l3.go = "Get_out_�3_ForMoney";
			}
		break;

		case "Get_out_�3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("� �� ��� �������. ��������...", "��������� �� ���������. ��������� ����������.", "��� ������ �� � �������. ����� ��������...");
			Link.l1 = "� ����"+ GetSexPhrase("","�") +", ��� �� ���� ��������� ������...";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("��, �������, ��� ����� �������� � ������� ������ �� ����. �� �� �� ������ ��������� ���� � ������� ����� �� �������?", "�� ������������� �� ���, �������. �� � ����� ������ �����, ���� ������ ��������� �����������.", "� ��� ���� ������������� �� ��� ��� ������ �������? �����, ��� �������� ����������� ��� �� ��������.");
			Link.l1 = "�����, � ���������"+ GetSexPhrase("","�") +". ���� ���������, �� �� ��� ������� � ����� ���������.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "��, �� ���� ������ �� ����������. ����� "+sti(NPChar.rank)*500+" �������. �����, �� ������ ����� ������.";
				Link.l2.go = "Get_out_�3_ForMoney";
				Link.l3 = "� ��� ���� �����. ��, ��������� ���, �� ������� ���������� - ������� ����� �� �������.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "���! � ��� �� ��������� ���������� ����� ����?! � ��� � ����"+ GetSexPhrase("","�") +", ��� �� ���������� ������ � ������������� �������.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "� ����, ��� �� ��� �������, �� ���������� ������� ������� ������, ����� � ������ "+sti(NPChar.rank)*1000+" �������. ��� ��� ������� ������� � � �����.";
			Link.l1 = "������, ����� ���� ������.";
			Link.l1.go = "Get_out_�3_chang";
			Link.l2 = "�� � ���� �� �� ���?! ��������� ����� ����� �� ��, ��� � ��� ���� ���������! ������, ����� ������ ��������, ��� ��������, ��-���� �������� ���� ��� ����� ��������� ������������.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "�� �� ������ ���� ����������! �, ����� � �� ����� ������ �� �����, �� �� �� ������ ������. � �������� ������� ����, ���� ���"+ GetSexPhrase("���","��") +" ������ ��� ��!";
			Link.l1 = "���� ���� ��� �� ����, �� ������� - ������ �� ��������, �� ����� ������ �� ��������.";
			Link.l1.go = "Get_out_�3_strife_death";
		break;

		case "Get_out_�3_strife_death":
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "��, �� ��������������-�� � ������ � ����� ������!!";
			Link.l1 = "�� ��� �����! ��, ��� �, ��� ���������...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("��� ��� ������! ��� ���� �� ������ ������, � ���� - ���, � ��� ��������� �������!","�� ��� � ��� �� ������� �����?! �� ������� ��������, ��� ���� ��� �� �������� ��� ���. �� � �� ����, ���� ������ �������...","��� �� ��! ��� ������ ���������� �� ��� - � �� �� �������������. ���� ��������� ���� �� ����� � �������� �� �����������!"), LinkRandPhrase("�� �����, ����� ���. ������ �� ������� ������� ��� ������ �����������.","�� ��� �, ���� ����. �� ������: ������� ������� ��� �� ����� �� �����.","������, �������, ���� ��-������. ��, ����� ��� - � ���� �� ������ �����..."));
			Link.l1 = "����. ������ �� ����� ������� ������ ���� ���������. �� ��� ��������� �������� � ����.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("�����-�����. � ��������� ����, ��� � ������� � ������� ����������.", "�����-�����. �� ����� �� ���� ������, ��� �� ������ ����.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�������. ��� ���� �� ������ "+sti(NPChar.rank)*500+" �������. � �� ������ ��� �������, � ��� ����� ����� ����� ��������.";
				Link.l3.go = "Get_out_�4_ForMoney";
			}
			Link.l4 = "������... � ���� ������� ����������"+ GetSexPhrase("","�") +" - ������� ����� �� �������.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_�4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("��� �������, �������! ��� ��� �������...", "��������� �� ���������. ��������� ����������.", "��� ������ �� � �������. ����� ��������...");
			Link.l1 = "���������. ������ �� ������ �� ��� � ��������� �������.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("��� ������ ��� � ���������� ���������! �� ������� ��� �� ��������! ��-���� � ������ �������...", "����, �� ���� ������� ������� ������. ��� �, ���������. ���� ������ ������ - �� �������...", "��������� �������! ������ ��� � ��������� ������. ��, ��������!.. ���������, ���� ��� �� �������...");
				Link.l1 = "�����-�����. �� ����� �� ���� ������, ��� �� ������ ����.";
				Link.l1.go = "Get_out_�4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("���� ��-������, �������, ������ ������� ������� ��� "+sti(NPChar.rank)*1000+" �������. ����� ������� ��� ������������ ��������� ��������.", "������. ������ �� ��� � ���� �������� "+sti(NPChar.rank)*1000+" ������� � �������� ����������� �� ������� ������.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "��� ��������! �����, ����� ���� ������.";
					Link.l1.go = "Get_out_�4_chang";
				}
				Link.l2 = "�� �� ����� ��������?! ������ ������� ������� ����� �� ��, ��� � ���"+ GetSexPhrase("","�") +" �� ���� ���"+ GetSexPhrase("","�") +"!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "��-��! �� � �������"+ GetSexPhrase("","�") +"! ����� � ���� ���������� ������� �����, ��� ������� ������!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterReputation(pchar, -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "��, ����� ������ � �� ��������! � � ����� �� �������, ���� �� ������, ��� ������ �� ������!";
			Link.l1 = RandPhraseSimple("������ �� ��������, ��� ������ ��� ������!", "������, ���� ������ ����� ������!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_�1_chang": // ��������� ������
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�2_chang": // ��������� ������
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�3_chang": // ��������� ������
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�4_chang_1": // ��������� ������
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�4_chang": // ��������� ������
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "�� ���� ���? ��, �������, ��� �� ������! ���� ���� ������ �� ����� ����� �� �����.";
			Link.l1 = RandPhraseSimple("������-������. �������� ������.", "���-���. ���������� �� �����.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "���-�� ���, �������? ��� ��������, ��� �� ��� �� ������...";
			Link.l1 = "���, ������. ������ ����������� �����"+ GetSexPhrase("","�") +"...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "�������, ��� ������� ������, ��������� ���������. �� ������ �� �� ����� ����� ����� �������, ��� ����������.";
			Link.l1 = "���-���. �������� ������.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "�������, �� ����� ��� ����� ���� �������? �, ������� �� �������, ����� �� ��� ������, � �������� ������� ������������ �� ����...";
			Link.l1 = "���-���. ����� �� ��� ������, ������ ������ ������.";	 
			Link.l1.go = "Exit";
		break;
        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "Hired";
		      dialog.text = "���� �������� ����������!";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = "���� �������� ����������!";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    ������-��������� -->
		case "Gover_Hire":
            dialog.Text = "����� �� �����!";
            Link.l1 = "����� �� �������� � ������������ ������, � ���� ������ ���������� �� ��������� ��������.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
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
			Diag.CurrentNode = "Gover_Main";
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
            Diag.TempNode = "Gover_Main";
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

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
            Link.l8 = "��� � ������.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
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
			// if(bBettaTestMode) // ������ ��� ����-�����
			// {
			    Link.l3 = "� ����, ����� �� �� ����� ����� �� ������� ���� ������� � ������� ����� ��������������.";
			    Link.l3.go = "CompanionTravel";
			// }
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
	
		// ��������������� �������� ���������� -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // ���� ��� ����� ��������
			{
				dialog.Text = "�������, � �� ����� �� ������� ����� �������, ��� ��� �� � ��� ��� ��������� ��� �������.";
					Link.l1 = "��, ������� �� ����.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "��� �������, ���. � ����� ������ �� ����������?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				NPChar.Temp.(attr) = attr;
				Link.(attrLoc) = "� " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "� ���������"+ GetSexPhrase("","�") +". ������ �� �����.";
				Link.l99.go = "exit";
		break;
		
		int nFind = findSubStr(Dialog.CurrentNode, "CompanionTravelToColony_", 0);
		string idxVal;
		string nodName;
		if(nFind == 0) 
		{
            idxVal = strcut(Dialog.CurrentNode, 24, strlen(Dialog.CurrentNode)-1);
            nodName = "CompanionTravelToColony_" + idxVal;
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn;									// Companion index
				cn = GetCompanionIndex(PChar, i);
				if (cn == -1) continue;
				if (NPChar.name == characters[cn].name) NPChar.realcompanionidx = &characters[cn].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = NPChar.Temp.(idxVal);
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D(NPChar.Temp.(idxVal))/300+1.0);
			dialog.Text = "�� ������� ������� "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", �������?";
			Link.l1 = "��, ������ �.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "���, � ���������, �� ���� � ������.";
            Link.l2.go = "exit";
            break;
        }
		
		case "CompanionTravel_EnemyColony":
			dialog.Text = "�������, �� � �� �� c���� ����� ��� � �������, ������� � ��� ���������!";
				Link.l1 = "������, ������ ��� ��� ��� �����������...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "���, �� ������� �� ����� ���� ��������! ����� ��������?!";
				Link.l1 = "��, �����. ������� ����� ����...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "���, ��� ������ ����������� � ���� �� ����� �������� ���������.";
				Link.l1 = "��, �� ����. ����������� �������, ����-���...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "���, �� ��� ������� � ������ ���������. ��� �� ������� �������� � ���� ������ ��� ����� ���������������!";
				Link.l1 = "��, �� ����. ���� ������� ��������� � �������.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			int iShip = sti(characters[sti(NPChar.realcompanionidx)].ship.type);
			ref refBaseShip = GetRealShip(iShip);
			if (sti(refBaseShip.hp)/4>sti(characters[sti(NPChar.realcompanionidx)].ship.hp))
			{
				dialog.Text = "� ���� ��������, ���...";
				Link.l1 = "�����?";
				Link.l1.go = "CompanionTravel_NoHP";
				break;
			}
			if (sti(refBaseShip.MinCrew)>GetCrewQuantity(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "� ���� ��������, ���...";
				Link.l1 = "�����?";
				Link.l1.go = "CompanionTravel_NoCrew";
				break;
			}
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+30>CalculateShipFood(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "� ���� ��������, ���...";
				Link.l1 = "�����?";
				Link.l1.go = "CompanionTravel_NoFood";
				break;
			}
			dialog.Text = "�� �������. �� " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " ��� ���� " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " ����, ��� ��� ������ �� ��������?";
				Link.l1 = "��� ���� �� ����� ������� �����.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "������, � ���������"+ GetSexPhrase("","�") +". ��������� �� ����, ����-���...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "�� �������, �������. ����������� ����������.";
				Link.l1 = "��, �����������.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("������� � ����� ����� � ����...",
			"�� �������� ��� ���� � ���� ������� � " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "� ���� ����� �����. ������ ��� ������� ����� ��� ����� ����������������, ���.";
					Link.l1 = "������.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // ������ ������
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // ����� ���������� ����� ������� � �������
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "���, � ��� �� � ��� ������� �� ���� �������, ����-�� ������ ���? � �����, � ���� ����� ��� ���, �� ����� ������� - ��� ��� ���� ����� ���������� �� ������� - �� ����� ����� ����� ������ �� ��� � �� �� ���� ���������.";
					Link.l1 = "��, ����� �� ������. ���� �� ���������, � ��������� ����� ����!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ������ ����� ��� ����
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "�-�, �������. ��� �� � ���������, ��� � � �������. �� ���, ����� � ������� ������������?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "��, " + NPChar.name + ", ������������. ����� ���������� � ������ �������.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // ����� ���������� ����� ������� � �������
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "��� ���, � ���������.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		
		//////////////////////////////    ������-��������� <--
        
        
	        // COLONY BUILDING
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "����� �� ����� ���� ����������� ����� �������!";
			Link.l1 = "����� �� �������� � ������������ ������. ���� ��������� ����� ������ ��������������. � ���� ����� �� ������� ������������ ����.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;
	
	        case "ColonyBuilding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.ColonyBuilding.Hovernor = NPChar.id;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			Diag.TempNode = "ColonyBuilding_Hovernor";
			
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_townhall", "sit", "sit1");
			LAi_SetHuberType(NPChar);
			
			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1.location = PChar.location;
			//PChar.quest.SetHovernorToColonyResidence.win_condition = "SetHovernorToColonyResidence";
			
			DialogExit();
	        break;
	
		case "ColonyBuilding_Hovernor":
			if(PChar.ColonyBuilding.AutoPurchaseFirst == true && PChar.ColonyBuilding.Store.BuildingTime == false && PChar.ColonyBuilding.AutoPurchaseFirst.Disable != true)
			{
				dialog.Text = "������������, �������. ������� � ����� ������� �������� ������� � � ���� ��� ���������� � ��������� ������������� ����� ������� ������.";
				Link.l1 = "���������.";
				Link.l1.go = "ColonyBuilding_AutoStore_1";
				break;
			}
			
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". ��� ���� �������?";
			Link.l1 = "� ���� ����� ������� ���� �������.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "� ���� ����� ���� � ���������� ���������, " + NPChar.name + ".";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "�����"+ GetSexPhrase("","�") +" ��������� ����, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "ColonyBuilding_Hovernor";
		break;
	
		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "��... � ����� ������ ����� �� ������ ������������?";
			Link.l1 = "���� ���������� ������ � ��������� ������� � � ���������� ������������.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "���� ���������� ������ � ������ ���������� ��������� � �������� �������.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "� ���� ������������� ������� � ������������ ������� ��� ������.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "������, " + NPChar.name + ", ��� ���������� �����������.";
			Link.l4.go = "Exit";
			
		break;

		case "ColonyBuilding_AutoStore_1":
			PChar.ColonyBuilding.AutoPurchaseFirst.Disable = true;
			dialog.Text = "��� ����������� �������� �� ������ ���������� �������������� ������� ������� ������ �������������, ����� ������� � ������� �������� � ���������� ������� �������� ����� ������������ �������� ����������� � �������� \n ���������� � ������ ��������, ���� ��� ��� ��������������.";
			Link.l1 = "���������. ����� ��������� � ������.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
		break;
		
		case "ColonyBuilding_Hovernor_3_1":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "�� �������?";
			Link.l1 = "��.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
		break;
		
		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
			dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
			Link.l1 = "��� � ������.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyBuilding_Expidition_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". � ���� ��� ��� �������. ������� ����������� ���������� ���� ����������. �� ������� ���� ������� ����� ������������ �����, � ������� - ������ ����.";
			Link.l1 = "��, ��� �, ������. �� �������.";
			Link.l1.go = "exit";
		break;
	
		case "ColonyBuilding_Mines_End":
			PChar.ColonyBuilding.MineMessage = true;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". � ���� ��� ��� �������. ����������� ������������� ��������. ������ ��� ���������� ��������� ���������� ��������. � ��� �� ������ ������ ��� ����, ��������� � ���� ��������.";
			Link.l1 = "��, ��� �, ������. �� �������.";
			Link.l1.go = "exit";
		break;
	
		case "ColonyBuilding_Plantation_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". � ���� ��� ��� �������. ����������� ������������� ���������. ������ ��� ���������� ��������� ���������� ���������. � ��� �� ������ ������ ��� ����, ��������� � ���� ��������.";
			Link.l1 = "��, ��� �, ������. �� �������.";
			Link.l1.go = "exit";
		break;
        
        	// ��������� ��������
		case "MinesCommander_1":
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". ��� ���� �������?";
			Link.l1 = "� ���� ����� ������� ���� ��������.";
			Link.l1.go = "MinesCommander_2";
			Link.l2 = "� ���� ����� ���� � ���������� ���������, " + NPChar.name + ".";
			Link.l2.go = "MinesCommander_Remove";
			Link.l3 = "�����"+ GetSexPhrase("","�") +" ��������� ����, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;
		
		case "MinesCommander_2":
			Diag.TempNode = "MinesCommander_1";
			DialogExit();
			LaunchMines();
		break;
		
		case "MinesCommander_Remove":
			dialog.Text = "�� �������?";
			Link.l1 = "��.";
			Link.l1.go = "MinesCommander_Removed";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;
		
		case "MinesCommander_Removed":
			PChar.Mines.Commander = "";
			dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
			Link.l1 = "��� � ������.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;
		
		case "MinesCommander_Hire":
			dialog.Text = "��� �. ���������� ��������� ���� ��������.";
			Link.l1 = "��� � ������. ��������� � ����� ������������.";
			Link.l1.go = "MinesCommander_Hired";
			Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;
		
		case "MinesCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_Mines_Comendant_House", "barmen", "stay");
			
			LAi_SetStayType(NPChar);
			PChar.Mines.Commander = NPChar.id;
			Diag.CurrentNode = "MinesCommander_1";
			Diag.TempNode = "MinesCommander_1";
			 
			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToMinesOffice.win_condition = "SetCommanderToMinesOffice";
			
			DialogExit();
		break;
		
        	// ��������� ���������
		case "PlantationCommander_1":
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". ��� ���� �������?";
			Link.l1 = "� ���� ����� ������� ���� ���������.";
			Link.l1.go = "PlantationCommander_2";
			Link.l2 = "� ���� ����� ���� � ���������� ���������, " + NPChar.name + ".";
			Link.l2.go = "PlantationCommander_Remove";
			Link.l3 = "����� ��������� ����, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;
		
		case "PlantationCommander_2":
			DialogExit();
			LaunchPlantation();
			Diag.TempNode = "PlantationCommander_1";
		break;
		
		case "PlantationCommander_Remove":
			dialog.Text = "�� �������?";
			Link.l1 = "��.";
			Link.l1.go = "PlantationCommander_Removed";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;
		
		case "PlantationCommander_Removed":
			PChar.Plantation.Commander = "";
			dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
			Link.l1 = "��� � ������.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;
		
		case "PlantationCommander_Hire":
			dialog.Text = "��� �. ���������� ��������� ���� ��������.";
			Link.l1 = "��� � ������. ��������� � ����� ������������.";
			Link.l1.go = "PlantationCommander_Hired";
			Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;
		
		case "PlantationCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Plantation.Commander = NPChar.id;
			Diag.CurrentNode = "PlantationCommander_1";
			Diag.TempNode = "PlantationCommander_1";
			 
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "CaimanPlantationOffice", "goto", "goto1");
			LAi_SetStayType(NPChar);
			
			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToPlantationOffice.win_condition = "SetCommanderToPlantationOffice";
			
			DialogExit();
		break;
		
	        // �������� �� ������ - ��������� ���������
		case "ColonyGuarding_Hovernor_1":
			dialog.Text = "��... �������, � ����� ���������� � ������������ �������.";
			Link.l1 = "������� ����������, �����... �-�-�... ������ ����������!";
			Link.l1.go = "ColonyGuarding_Hovernor_2";
			Link.l2 = "� "+ GetSexPhrase("���������","����������") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;
	
	        case "ColonyGuarding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Colony.Guardians.Hovernor = NPChar.id;
			
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "LandGuardingHeadHouse", "goto", "goto3");
			LAi_SetStayType(NPChar);
			
			Diag.CurrentNode = "ColonyGuarding_Hovernor";
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
	        break;
	
		case "ColonyGuarding_Hovernor":
			dialog.Text = "������������, ������� " + PChar.name + " " + PChar.lastname + ". ��� ���� �������?";
			Link.l1 = "� ���� ����� ������� ��������� ������.";
			Link.l1.go = "ColonyGuarding_Hovernor_3";
			Link.l2 = "� ���� ����� ���� � ���������� ���������, " + NPChar.name + ".";
			Link.l2.go = "ColonyGuarding_Hovernor_4";
			Link.l3 = "� ���� ���������� � ����� ������� ��� ���������, ����������� ���� �������.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_1";
			Link.l4 = "����� ��������� ����, " + NPChar.name + ".";
			Link.l4.go = "Exit";
			Diag.TempNode = "ColonyGuarding_Hovernor";
		break;
	
		case "ColonyGuarding_Hovernor_3":
			dialog.Text = "��... � ����� ������ ����� �� ������ ������������?";
			Link.l1 = "���� ���������� ������ � ��������� �����.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_1";
			Link.l2 = "���� ���������� ������ � ������ ���������� ��������� � �������� �������.";
			Link.l2.go = "ColonyGuarding_Hovernor_3_2";
			Link.l3 = "���� ���������� ������ � ���������� ������ ��������� �����.";
			Link.l3.go = "ColonyGuarding_Hovernor_3_3";
			Link.l4 = "������, " + NPChar.name + ", ��� ���������� �����������.";
			Link.l4.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_1":
		    	CheckDeadColonyGuard();
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyGuardiang();
		break;

		case "ColonyGuarding_Hovernor_3_2":
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyGuarding_Hovernor_3_3":
			CheckDeadColonyGuard();
			
			if(GetColonyGuardsShipsQuantity() < 1)
			{
				dialog.Text = "�������, �� ������ ������ � ������� ��� �� ������ �������...";
				Link.l1 = "�� ��, � � �����...";
				Link.l1.go = "exit";
				PChar.Colony.Guardians.BaseComplete = false;
				break;
			}
		
			string sBaseComplete = "";
			
			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				sBaseComplete = "������� ����������� �������� ������ ������������ � ������ ������ � ���. �� ������ ������ �����, ������� ���������� ��� �����, ���������� " + GetCostForBaseCompletationAllGuards() + " ��������.";
			}
			else
			{
				sBaseComplete = "������������ �������� ��������� ����� �� ������������. ��, ������� ����������� ������ ������ ��������� ������ �������� � ��������� �� ������ ������������, ����� � ����� ������ ���� ����� ���������.";
			}
			
			dialog.Text = "��... � ������ ������ " + sBaseComplete;
			
			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				Link.l1 = "�����, ���� ����� ������������� ������������ ������������. ����� �� ���������...";
				Link.l1.go = "ColonyGuarding_Hovernor_3_3_3";
			}
			else
			{
				if(PChar.Colony.Guardians.BaseComplete.First == true)
				{
					Link.l1 = "���������� ��������� �� ����.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_1";
				}
				else
				{
					Link.l1 = "�����, ����� ����������� ������������ ����������� ������ ��������� �����.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
				}
			}
			
			Link.l2 = "��������, ���� ���� ����.";
			Link.l2.go = "Exit";
			Diag.CurrentNode = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_3_3_1":
			PChar.Colony.Guardians.BaseComplete.First = false;
			dialog.Text = "������ ������ ����� ����������� ������ �������� ������ ��������� �����, � �� �������, ������� � ������ ������ ����� �������� �, ����� ��������� ������������ ������������ � �������� ������ �������������, ����� ���� ����� ���������� � ������� \n �� ����� �� ��� ��������, ���������� ����� ���� �� ��������� �����, ������� ������� �� ������������� ��������. ��������, �� ������ ������ ����� ���������� ����������� �� ����� ������� �� " + GetCostForBaseCompletationAllGuards() + " �������� � ������. ���� �� ������ ����� ����� �������������, ��, � ���������, ������������� ����� �� �� ���. ��� �������?";
			Link.l1 = "�������� ����. � ��� ���������� �� ������������� ������ ������� �� ����� �������.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
			Link.l2 = "�������, ���� �������� ��� �����.";
			Link.l2.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_3_2":
			PChar.Colony.Guardians.BaseComplete = true;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_3_3_3":
			PChar.Colony.Guardians.BaseComplete = false;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_4":
			dialog.Text = "�� �������?";
			Link.l1 = "��.";
			Link.l1.go = "ColonyGuarding_Hovernor_5";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "Exit";
		break;
		
		case "ColonyGuarding_Hovernor_5":
			PChar.Colony.Guardians.Hovernor = "";
			dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
			Link.l1 = "��� � ������.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_1":
			dialog.Text = "������, �������. ��� ���� ���� ������� � ���� �������?";
			Link.l1 = "�������� �� ��������� ������ � ����� �����������.";
			Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Info";
			Link.l2 = "� ���� ������ ����, ������� ��������� ��� ������������� �����.";
			Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Costs";
			Link.l3 = "���������� ������������ �������, �� ������� �������������� ���� ���������.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Set";
			Link.l4 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Info":
			dialog.Text = "� ���� �������������� �������� ������� ��� ���������, ����� ���� ������� � ���������, �� �������������, ������ ������ �� ���� ����� ����� � �������� ��������������� ������� � �����. \n ��, ��� �� ���������, ��� ����� ������ ������� ������� ��������, ��� ������� ���� � �������� ����������. ������ ��� �������� ����� �������������������� � ������ ������� ������������ ����������. \n ���� ��������� ����� ����������� �� ��� ������� - � ��� ���� �������, ��������� � �������. \n ������ ��� � ����� ������� ������ ���� �����, ����������� �������� ���� ��������� �� ����������� ������. ���� ����� ����� � ����� �� ��������, �� �����, ��������������, �� ���������.";
			Link.l1 = "������� �� ����������, " + NPChar.name + ".";
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Costs":
			dialog.Text = "���� ����������� ����� ����� �������� ��� ����������?";
			
			if(PChar.ColonyBuilding.Stage != "0")
			{
				Link.l1 = "�������.";
				Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony";
			}
			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				Link.l2 = "�������.";
				Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines";
			}
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l3 = "���������.";
				Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation";
			}
			
			Link.l4 = "������, ��� ���� ����.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony":
			dialog.Text = "�� ������ ������ ���� ����������� ����� ��������� ������� - � ������ ������������������ ���������: " + ColonyGuardingGetCostForObject("Colony", false) + " �������; ��� ������� ���������� ��� ����� ������������������: " + ColonyGuardingGetCostForObject("Colony", true) + " �������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines":
			dialog.Text = "�� ������ ������ ���� ����������� ����� ��������� �������� - � ������ ������������������ ���������: " + ColonyGuardingGetCostForObject("Mines", false) + " �������; ��� ������� ���������� ��� ����� ������������������: " + ColonyGuardingGetCostForObject("Mines", true) + " �������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation":
			dialog.Text = "�� ������ ������ ���� ����������� ����� ��������� ��������� - � ������ ������������������ ���������: " + ColonyGuardingGetCostForObject("Plantation", false) + " �������; ��� ������� ���������� ��� ����� ������������������: " + ColonyGuardingGetCostForObject("Plantation", true) + " �������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Set":
			dialog.Text = ColonyGuardingAutoCrewHireGetWork();
			
			if(PChar.ColonyBuilding.Stage != "0")
			{
				if(PChar.Colony.Guardians.Colony.AutoCrewHire == false)
				{
					Link.l1 = "� ���� ��������������� ������������ ����� ��������� ��� ������ �������.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1";
				}
				else
				{
					Link.l1 = "� ���� ������������� ���� ��������� ��� ������ �������.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1";
				}
			}
			
			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.Colony.Guardians.Mines.AutoCrewHire == false)
				{
					Link.l2 = "� ���� ��������������� ������������ ����� ��������� ��� ������ ��������.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1";
				}
				else
				{
					Link.l2 = "� ���� ������������� ���� ��������� ��� ������ ��������.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1";
				}
			}
			
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Colony.Guardians.Plantation.AutoCrewHire == false)
				{
					Link.l3 = "� ���� ��������������� ������������ ����� ��������� ��� ������ ���������.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1";
				}
				else
				{
					Link.l3 = "� ���� ������������� ���� ��������� ��� ������ ���������.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1";
				}
			}
			
			Link.l4 = "������, ��� ���� ����.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1":
			dialog.text = "�� �������, �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2";
			link.l2 = LinkRandPhrase("��... �������, �� ���� - ����� �������� ���.", "� ���������"+ GetSexPhrase("","�") +".", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = true;
			dialog.text = "������, �������! � ������������ ��� ������� ���� ��������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1":
			dialog.text = "�� �������, �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2";
			link.l2 = LinkRandPhrase("��... �������, �� ���� - ����� �������� ���.", "� ���������"+ GetSexPhrase("","�") +".", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = true;
			dialog.text = "������, �������! � ������������ ��� ������� ���� ��������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1":
			dialog.text = "�� �������, �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2";
			link.l2 = LinkRandPhrase("��... �������, �� ���� - ����� �������� ���.", "� ���������"+ GetSexPhrase("","�") +".", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = true;
			dialog.text = "������, �������! � ������������ ��� ������� ���� ��������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1":
			dialog.text = "�� ������������� ������ ������������� ���� ������� ��� ��������� �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2";
			link.l2 = LinkRandPhrase("���������!", "�, �������, ���������"+ GetSexPhrase("","�") +"..", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = false;
			dialog.text = "��� ���������, �������.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1":
			dialog.text = "�� ������������� ������ ������������� ���� ������� ��� ��������� ��������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2";
			link.l2 = LinkRandPhrase("���������!", "�, �������, ���������"+ GetSexPhrase("","�") +"..", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = false;
			dialog.text = "��� ���������, �������.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1":
			dialog.text = "�� ������������� ������ ������������� ���� ������� ��� ��������� ���������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������"+ GetSexPhrase("","�") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2";
			link.l2 = LinkRandPhrase("���������!", "�, �������, ���������"+ GetSexPhrase("","�") +"..", "���... ���, �� ������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
		break;
		
		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = false;
			dialog.text = "��� ���������, �������.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
		// <-- ��������������� �������� ����������
	}
}