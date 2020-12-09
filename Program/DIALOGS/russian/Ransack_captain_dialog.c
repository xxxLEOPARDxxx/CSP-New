// BOAL ������ ��������� - � �����
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "� ��� �������, " + GetAddress_Form(NPChar) + ". �� ������ �������, ��� " + NationNameNominative(sti(NPChar.nation)) + " ������� �� �������� ����� -  ������ ��� �� ����.";
				link.l1 = "�-��... �� ���� �� ����������, ������ ���� ����� ���� ��� ����������� � �����-������ ����� �� �����.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "������, �� �������� ����, � ��� ��� ��� ����� ��������� ����������. �� ������� ��������� � ���� ��������?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear() + "� ��� �������, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + " �������� ������� ����� �� ��� �������.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "����������, � ������� ���� �� ����, � ��� ����� ������� ������. �� ������� ��������� ��� ���� �������?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "�� ������ ���� ������ " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". � "+ GetSexPhrase("���","�����") +" �� ��� ��� ��������.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "�������� � �������, ������� ����� ������� ������ �� ����. � ��������� ����� ������ �� �����.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "� �����, �� ��� ��������� �������� ��� - ������� � ���������.";
			link.l4.go = "Slave_1";
			link.l5 = "�� ��������������� ������ ���� � ����� � ������� �������������, �� ��� ������ �������. ������ ��� ������� ��������������� ������������.";
			link.l5.go = "PunishmentAction";
			link.l99 = "� ����.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "�������"
						dialog.text = RandPhraseSimple("�������, �� ������� �� ��������, �� ����� �� ��� ��������� ���������� �������� �������� ������� ����� ������������?",
							"� �������, ��� ����������� � ��� ��������� ���������, �� �� ����������� �� ��������� �������, ��� �������, �����������?");
						link.l1 = "��, �� ��������� ��� �����������.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "�������, ��������� �� �� ����. �� ��� � ��� ������? ��, ��������� ���� ������������� - ����� � �������� ������ ��������, ������ ��������� ��������� �������� �����������.";
						link.l1 = "���� ������, �� ������ ������ �� ���������...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "�� ��������������� ������ ���� � ����� � ������� �������������, �� ��� ������ �������. ������ ��� ������� ��������������� ������������.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "�� ��� ����������� �� ������������, ��� � ����� ����� ��� ���������. �� �������� - �������� �����.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("�� ��������� ��� ��������. ��� ��� ������� �������� � �����.",
							"� ���� ������ ��� ������ �����.","� �����, ��� �� ��� ��� �����������.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "�����"
						dialog.text = "�������, ����� ����� �������� ���������������. ��������� ������, ����� � ��� ������ ���� �����?";
						link.l1 = "������ ���������� �����������?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple(RandPhraseSimple("� ��� �� �����"+ GetSexPhrase("","�") +", ��� � ���� ������.","�������, ����� ����� �����."),
							RandPhraseSimple("� ����� �����? ���� �� ��� � ���... �� ���� �, ����.","�� ��� �������, � � ������ ��������� � ����, ��� ����� ������, �� �������� �� ������ ������, �� �������."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "�������, ��������� �� �� ���� ��-�����, ��-�������. ���� � ���� �����? � ���� �� �� ������ ����� � ������ ������� - ������ ������ � �� ������. �����, ������� �� �������� �������, � �����-�� ��� ���.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "������, �� �������� ����, � ��� ��� ��� ����� ��������� ����������. �� ������� ��������� � ���� ��������?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("������ �� �����. ����� ��� ����� �� ���� �����, ������ �� ������ ������ �����.",
						"��� ����������, '����� �����'? ����, ��� �������.",
						"����� �������� �� ������, � ����� �� ��������. ���� ���� �������, ���� ������ ��������� ����.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "�������, ����� ������� ���� - ��������� � �����. ���� �����, ���� �����, ������ �� ��� ���������? �� ����������, ��������...";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "����������, � ������� ���� �� ����, � ��� ����� ������� ������. �� ������� ��������� ��� ���� �������?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("� ���� ������ ��� ������ �����.","� �����, ��� �� ��� ��� �����������.","�� ��� �������, � � �������� � ���� ���, ��� ����� ������.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("�������, � ��� �������� �������� � ���� ������� � ������������. ��� ������������ ������� ��������� �� ����� ����������. �� ���� ��������� ��� �� �������� - ��������� �� ����� �����. ��� ���� ������� �� �������...",
							"�������, ������ � ������ �����������! ������� - ��� ������ ��������� ���������� �� ����, ��� � �������������, ������� ����� ����������. ��� ����� �������, ��� ������ ���� �������� ������� � ����.");
						link.l2 = LinkRandPhrase("�� ��������� ��� ��������. ��� ��� ������� �������� � �����.", 
							RandPhraseSimple("� ���� ������ ��� ������ �����.","� �����, ��� �� ��� ��� �����������."),
							RandPhraseSimple("�� ��� �������, � � ������ ��������� � ����, ��� ����� ������, �� �������� �� ������ ������, �� �������.",
							"��  ������� �������� ����� � ����� �� ��� ����. ������ ������ �� ���� ������� ������������."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "������, �� �������� ����, � ��� ��� ��� ����� ��������� ����������. �� ������� ��������� � ���� ��������?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "�� ������ ���� ������ " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". � "+ GetSexPhrase("���","�����") +" �� ��� ��� ��������.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "�������� � �������, ������� ����� ������� ������ �� ����. � ��������� ����� ������ �� �����.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "���� � ����! �������� � �������, �� ������� ��������������� ������������, ��� ������� � ��������� �����. � ������� - ��������� ���� ������� ����� ���������.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "�� ��������������� ������ ���� � ����� � ������� �������������, �� ��� ������ �������. ������ ��� ������� ��������������� ������������.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "�����������? ��, ��������, ������, " + GetAddress_Form(NPChar) + "!";
			link.l1 = "�� ����� ��� �����. ����� - �� � ���� �����.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "������� � ���? ��� ��, ����� ������� ����!";
				link.l1 = "���������� ����, � �� ���� ��� � ������.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "��������, " + GetAddress_Form(NPChar) + "? ������������ �� �����. ���� � ����, �� � ������� ����� ������ �� ����� ����� � ����� ������� � �����.";
				link.l1 = "��� � ������������! ���, �������� ����.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "�� ��������, � ���������"+ GetSexPhrase("","�") +". ����� �������� ������� ������ - ���� ������.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("��� ������� ������� �����������, �� � �������� ����������... �� �������, ��� �������, ������������.",
					"���, ����� ����, ��� �� ������� � ����� ����������, ��� ���� �� ��������...",
					"���, �������, ����� ����� ����� ����� � ������ �� �����. � ��� ����, ���, ���� ��������� ���� ������� ��� ������� � ������ �������, �� � ���� � ������ �� �����.");
				link.l1 = "��, ��� ������. ���������� �� �����.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "� ������ �� �� ���������? �������� �� ���� �� �����, ���� ��� �������, ��� ���� ��� �� ������, ����� �������� � �������� ��������?.. ������� - ��� �������.";
				link.l1 = "��� � ������������! ����� � ������� - ����� �������� ��� �� �����������. ����� �������� ��� ���������.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "�� ����������, � ���������"+ GetSexPhrase("","�") +". �� �� ����� �� ��������� ����.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // ���������� ��������
            DeleteAttribute(NPChar, "LifeDay") // ����������
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// ��� ���� ������������ ����� � ������� 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // ��� �������
            Npchar.Fellows.Passengers.id0 = Npchar.index; // ���� ��������

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "�� " + GetAddress_Form(NPChar) + ", �� �� ������ ��� ���������! � �� ������ � ��� �� ���� �������.";
            link.l1 = "��������� ���������! � ������� ���.";
			link.l1.go = "Slave_2";
			link.l99 = "�� �����, � ��� �������, �������� ����...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterReputation(pchar, -2);
            if (rand(5) == 1)
            {
    			dialog.text = "�� �� ���!.. � ����� ������� � �����, ��� ����� �����!";
                link.l1 = "����! � ����������!.. ������! �������� ����...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "�� �� �����! ������, ���� ������� �� ������, � ����� �� ��������!";
                        link.l1 = "� ��� ��� �� ��������. ������� ����� � �������� ��������������� � ��� ����������...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "���! �� ����� ������ � ���!";
						link.l1 = "��� ��� ����� ������...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "������, � ��������. � ���� ������ ��� ������� ������...";
                    link.l1 = "��� � ������. ����� ���� ����� �����, ��� ������ ������.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  �������� � ����
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "�, " + GetAddress_Form(NPChar) + ", �� ����� �����, ��� ���������� ���� ��� ������?";
            link.l1 = "��, ��������. �� ��������, " + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "��... ��, �� �����! ��� �������...";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "�������, "+GetFullName(PChar) + "! � ���� �� ��� ��������.";
            link.l1 = "�����, ��������, ���� � �� ���������"+ GetSexPhrase("","�") +".";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // ���������� ��������
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("���, �������, �������. ��� �� ������ ����� �������. ����� � ������ ���� �������� - ������� ������� ������. �� ���-�� � ����...",
						"������� ���, �������. � ������ ���� �� ������ �� ��� �������. ��� ��� ����� - ����� ��� ������������� �������, � ������ �������.");
					link.l1 = "�������� �� ������...";	
				break;
				case "trade":
					dialog.text = "���� �� ����, ��� ��� �����������, �������. �� �� ���� ����������. � ���� �������� � ����� �����������. � �������, �������� �� ��� ������ - ����� ������ �� ������ ���������!";
					link.l1 = "��������, � � ������� �� ��������� ��������� �������������. ������ �� ��� ������� - ��� �������� �������� � ���, � �������.";
				break;
				case "war":
					dialog.text = "������� ���, �������. � ���� �� ��� ��������.";
					link.l1 = "������ �� �������, ��� � ��������� ��� � ���� ���� ����� �����������"+ GetSexPhrase("��","��") +".";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // ���������� ��������        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> ������ ������� !!! ����� ������ ��������� ���-�� ���������� ����������� � ���� ������� ������ �� ����������
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ������ ������ ��������
        	            {
                        	ReleasePrisoner(offref); // ���������� ��������
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // ���������� ��������
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "�� " + GetAddress_Form(NPChar) + ", �� �� ������ ��� ���������! � �� ������ � ��� �� ���� �������.";
			link.l1 = "����� ����, ��� ������� ����, ������� �� ������ �������... ������! �����������.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "�� �����, � ��� �������, �������� ����...";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterReputation(pchar, -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "�� �� �����! ������, ���� ������� �� ������, � ����� �� ��������!";
                    link.l1 = "� ��� ��� �� ��������. ������� ����� � �������� ��������������� � ��� ����������...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "���! �� ����� ������ � ���!";
					link.l1 = "��� ��� ����� ������...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "��������� ���� ���������� ����� �������...";
                link.l1 = "��������...";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // ���������� ��������
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "� ���� ���� ��������� ��������, �������� �������� ����� ������������, ��� ����� ��������� ��� ���������. �� � ����� �� ����� ��������, ��� � ����� �� ���������� ������ �������.";
			link.l1 = "��� � ���� ��� ���-���� �������������, ���� �� ���� � ��� ����� ����? ��������� ���� �������� � ���������� ���� �� �����.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "����� �� �� ���� ��������, ����� ����� ����� �����?";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterReputation(pchar, -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "����� � �� ����� ������������, �� ������� ���������� � ������� - � ���������.";  
				break;
				case "war":
					sTmp = "��� ��������� ��� ����������� ������������ ��� � �������� �������� ������.";
				break;
				case "pirate":
					sTmp = "� ���-�� ��������� ��� �����������, �� �� ������������ �������� ������.";
				break;
			}
			dialog.text = "������. ����� ����������. ������ � ���� - � " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " ���� ������� ����� " + NPChar.Hold_GenQuest.Name + ". " + 
				"�� �������� ��� ������� ��������� ���, ��� �� ����� '" + NPChar.Hold_GenQuest.ShipName + "' ����� " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " ��������� " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " + 
				"����� ������ ������ ������� ������ ��� ��� �����, �� �������� ������. " + sTmp + " ������, ��� ��� �������� ����� ��� ��� ���� ������, ��� ������� ������ ��������.";
			link.l1 = "�� �����, ��� ��� ����� ���� ��� ���� �������. � �� ����� ��������� �� ������ ���������.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "�� ����, ���������� �� ��� ���� ��������, ��, �������� �������, �� ��������. ������ ��������� ��� � ��������, � � ��������� ����� ������� �� �����.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "������� ���, �������! � �� ������� �� ���������� � ����� ���������!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("�������� �� � � ��� ������ ��� ��","� ���������, �� ���� ������� ���� �� � ���."),
				RandPhraseSimple("������ �� �������, ��� � ��������� ��� � ���� ���� ����� �����������"+ GetSexPhrase("��","��") +".","�������� � �� ����������� ��� ������. � ������ ��� � �� ���� ����� ��������"+ GetSexPhrase("��","��") +"."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // ���������� ��������
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "�����, ����������� �������. � " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " ���� ��� ������� �������, " + NPChar.Hold_GenQuest.Name + " �����, �� ���� ������ ��������. " +
				"���� ����� � ��� ������ - �������� ���. � ������, �� �� ����������, ������� ����� ����. � � �� � ��� ����������� ��-�������... �� � ������ �� ���.";
			link.l1 = "�������, ��������? ��� �, ���������� � ������ ��������...";	
			link.l1.go = "free_buyout1";
			link.l2 = "���� �� � ����� ������ ������ ��������, ���� ������ �� ���������� ����� ���� �� ��� �����.";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "� �� �������... ���� � ������ ��������, ������� ����� �������� ���������, ������ �� ������ ��������� �� �������� �� ���������������.";
			link.l1 = "� ��� ��� ��?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "�������� ���� �������, ��� ������ ����� ����� � ���� ��������.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "� �������� ��� ��� �������, ������� ���� �������� � ��������� ����������... ������ ����� �����, ��� ��������� ���� � ������ �� �����.";
			link.l1 = "� ���" + GetSexPhrase("","�") + " ���� ������ ��� � ����� � ���� ������. �� ����� ������� ��� �������� �� �����.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "�� ������������� ���� �������. ��� �����...";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "���� ������������ ��������! ���"+ GetSexPhrase("��","��") +", ��� ��, �����, ���� �� ���" + GetSexPhrase("","�") + ", �� �-��-��... �����, ���� ����� ������ ������, � ��" +GetSexPhrase("","�")+ " ��� ����� ������� �����! �� ������ �� ������� " + GetFullName(pchar) + "?..";
			link.l1 = "��� �������������, ��� � ������ ��� ����� ������... ������ �� ����.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "��-��, ������� �����, ��-��... � ������� ���������. ���� � " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " ������� "+ 
				"�� ����� " + NPChar.Hold_GenQuest.Name + ", � ��������� ��� ��������� ������, ������� ����� ��������, ��� � ��������� �������... " + 
				"��� ���, ���-�� �� �������� ���� ��������� ��� ���� ��������, ���, ��������� � ����� " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + ", �������� ��� ���� ���������� ����, ��� ������ ���� ��������." +
				" ������� ����� ������� " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_NOM) + " ������ ����� ����� �������...\n����� �������� �����, ��� " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " ������� � � ��������� ��� ����������, � " + NPChar.Hold_GenQuest.Name + " � ��� ��� �� ��� ������, " +
				"�����������, ������ ��������. �� ����� ����� �� ������ ��������, ���� ����� ���������. ��� ��������� ������ � ��� �� ����������� ����. ������, �������, ������ - ���� ��� ������� ������ ������, � ������� �� ���������. �, ����������, ���� �� �������. "+ 
				"�� ����� ��� � ����� �������, �� �� ��� ��� ��� - � �� ���� �� ��� ���� �� ��������...\n ��� ����� ��� �������... �����, ����� ��� ��� ��� �������� ��������� � ����� ��� ����������� ��... �� � ������� ������.";
			link.l1 = "� �� ������������� ���������, ��� � ������ � ��� ������? ������ ������������ �� ������� ����������������� ����� �������.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "��... ���������� �������, ���� � ������� � ������. ��, ��� ����� ��� - �����, ������� �������, ����� ������� ��� ������ �� ����. � ������ �� ����� ������ �� �����.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "���, ������� ���, �������! ��� ��� ������ ����� "+ GetSexPhrase("�����������!","����!");
			link.l1 = "�������� � �� ����������� ��� ������. � ������ ��� � �� ���� ����� " + GetSexPhrase("����������.","����������.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // ���������� ��������
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "��, " + GetAddress_Form(NPChar) + ", �� �� � �������� ����! ��� ����������� ���� �����!!!";
			link.l1 = "�� �� �� ������ ����� ���������� - ��� ��� ��������. ������ ��������� �� ����������� ����� ������������.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "�� �����, � ��� �������...";
			link.l2.go = "exit";
		break;		
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
