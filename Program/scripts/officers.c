// BOAL ��������� ���������� ��� ����� ���

// -> ugeen 27.01.09 - ����� ���������� ��������� ���-�� (������ ������������)
void OfficersReaction(string alignment)
{
	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // ����� �������� � ���� ���� ����������� ����� ������� ���� ���� ���� ��� �� �� ����
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = makeint(sld.loyality) + 1;
				}
				else
				{
					sld.loyality = makeint(sld.loyality) - 1;
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = makeint(sld.loyality) + 1;
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
				}
				else
				{
					sld.loyality = makeint(sld.loyality) - 1;
					// ���������� �� ����� ���������� � 0 � ���. ������ ���� ��� ����� ������� ��� ��������
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
				}
			}									
		}
	}
}
//-> ugeen

void ChangeOfficersLoyality(string alignment, int iLoyality)
{ // aliggnment types : "bad" , "good" , "bad_all" , "good_all"

	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // ����� �������� � ���� ���� ����������� ����� ������� ���� ���� ���� ��� �� �� ����	
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;				
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;				
					break;
					case "good":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;				
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;									
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
					break;
				}
			}
		}	
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;				
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
						}	
						else 
						{
							sld.loyality = makeint(sld.loyality) - iLoyality;				
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
						}	
					break;
					case "good":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy		
						}	
						else 
						{							
							sld.loyality = makeint(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
						}	
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
					break;
				}	
			}									
		}
	}	
}

// ��������� ������� - �������� ��� - ������
void OfficersReactionResult()
{
	int iPassenger;
	int i;
	ref sld;
	
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // ���� ����� ������ ����� � �������� ������
	if (CheckAttribute(Pchar,"questTemp.MunityOfficerIDX") && Pchar.questTemp.MunityOfficerIDX.begin == "1") return;
	
	for (i = 0; i<GetPassengersQuantity(pchar); i++)
	{   // ����� �������� � ���� ���� ����������� ����� ������� ���� ���� ���� ��� �� �� ����
		iPassenger = GetPassenger(pchar, i);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld,"prisoned") && GetRemovable(sld) && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sti(sld.loyality) < 1)
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "Enc_Officer_dialog.c";
						sld.dialog.currentnode = "WantToRemove";
				      	if (sld.sex != "woman")
						{
					    	sld.greeting = "Gr_Officer_Fired";
					    }
						DeleteAttribute(sld, "quest.officertype");
	
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", 2.0, 0);
						//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
			    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			    		chrDisableReloadToLocation = true;
			    		DoQuestCheckDelay("OpenTheDoors", 5.0);
						break; 
					}
				}
			}
		}
	}
	if (chrDisableReloadToLocation) return; // ��� �����������
	
	if (CheckNPCQuestDate(pchar, "OfficerWantToGo") && rand(1) == 1) // ������ ��� � ����
	{
		SetNPCQuestDate(pchar, "OfficerWantToGo");
		for (i = 0; i<GetPassengersQuantity(pchar); i++)
		{   // ����� �������� � ���� ���� ����������� ����� ������� ���� ���� ���� ��� �� �� ����
			iPassenger = GetPassenger(pchar, i);
			if (iPassenger != -1)
			{
				sld = GetCharacter(iPassenger);
				if (!CheckAttribute(sld,"prisoned") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && GetRemovable(sld) && rand(10) == 5 && GetNpcQuestPastDayParam(sld, "HiredDate") > 60)
				{
					if (sld.dialog.filename == "Enc_Officer_dialog.c") // ��������� �� �������
					{
						if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
						{
							sld.dialog.currentnode = "WantToGo";
		                    sld.greeting           = "Gr_Officer_Salary";
		
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", 2.0, 0);
							//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
				    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
				    		chrDisableReloadToLocation = true;
				    		DoQuestCheckDelay("OpenTheDoors", 5.0);
							break; 
						}
					}
				}
			}
		}
	}
}

bool isOfficerInShip(ref _chr, bool _withBoard)
{
	if(sti(pchar.Fellows.Passengers.navigator) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == sti(_chr.index))
	{
		return true;
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.doctor) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == sti(_chr.index))
	{
  		return true;
	}
    if(sti(pchar.Fellows.Passengers.treasurer) == sti(_chr.index))
	{
  		return true;
	}
	if(_withBoard && IsOfficer(_chr))
	{
		return true;
	}
	return false;
}
// ����� ��������� ������� - �������� �����, �������� �3
void CheckForReleaseOfficer(int iCharIndex)
{
	if(sti(pchar.Fellows.Passengers.navigator) == iCharIndex)
	{
		pchar.Fellows.Passengers.navigator = -1;
		DeleteAttribute(&characters[iCharIndex], "navigator"); // ������������ ��������
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == iCharIndex)
	{
		pchar.Fellows.Passengers.boatswain = -1;
		DeleteAttribute(&characters[iCharIndex], "boatswain"); // ������������ ��������
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == iCharIndex)
	{
		pchar.Fellows.Passengers.cannoner = -1;
		DeleteAttribute(&characters[iCharIndex], "cannoner"); // ������������ ��������
	}

	if(sti(pchar.Fellows.Passengers.doctor) == iCharIndex)
	{
		pchar.Fellows.Passengers.doctor = -1;
		DeleteAttribute(&characters[iCharIndex], "doctor"); // ������������ ��������
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == iCharIndex)
	{
		pchar.Fellows.Passengers.carpenter = -1;
		DeleteAttribute(&characters[iCharIndex], "carpenter"); // ������������ ��������
	}

    if(sti(pchar.Fellows.Passengers.treasurer) == iCharIndex)
	{
		pchar.Fellows.Passengers.treasurer = -1;
		DeleteAttribute(&characters[iCharIndex], "treasurer"); // ������������ ��������
	}

	//if (IsOfficer(&characters[iCharIndex]) == true)
	//{
		// ��� �������� ������,  ����� �� �������� �� �����
		RemoveOfficersIndex(pchar, iCharIndex);
		DeleteAttribute(&characters[iCharIndex], "fighter"); // ������������ ��������
	//}
	DeleteAttribute(&characters[iCharIndex], "isfree"); // ��� ����� �2, �������� �������� - �������� �����, ���� ����, �� �����
}

//////////////// OFFICER ////////////////
void SetOfficerParam(ref Npchar, int _type)
{
	float upSkill = 0.7;

	ClearCharacterExpRate(Npchar); // ���� ��� ������ ����� �� ���� ������

    Npchar.quest.LeadershipModify  = 0;
	Npchar.quest.FencingModify     = 0;
	Npchar.quest.SailingModify     = 0;
	Npchar.quest.AccuracyModify    = 0;
	Npchar.quest.CannonsModify     = 0;
	Npchar.quest.GrapplingModify   = 0;
	Npchar.quest.RepairModify      = 0;
	Npchar.quest.DefenseModify     = 0;
	Npchar.quest.CommerceModify    = 0;
	Npchar.quest.SneakModify       = 0;
	Npchar.quest.PistolModify      = 0;

	// SetRandSPECIAL(Npchar);   //  ��� ��� �����
	Npchar.quest.officertype_2 = ""; //mercen_";
    switch(_type)
	{
		case 0:
		    SetRandSPECIAL_K(Npchar);  // ��� ���� ������  ��� ������� ���� �����
			Npchar.quest.officertype = "boatswain";
			Npchar.quest.officertype_2 = RandPhraseSimple("���� � �������� ������, ���� �������. ", "��� ���� �������� ������, ����� �� ���������, ����� ��������. ");
			Npchar.quest.LeadershipModify     = frandSmall(2.0);
			Npchar.quest.FencingModify     = Rand(1);
			Npchar.quest.GrapplingModify   = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify     = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify       = Rand(1);

			//Npchar.skill.Grappling_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Defence_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 1:
		    SetRandSPECIAL_K(Npchar);
			Npchar.quest.officertype = "cannoner";
			Npchar.quest.AccuracyModify      = frandSmall(2.0) + 2;
			Npchar.quest.CannonsModify       = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = Rand(1);

			//Npchar.skill.Cannons_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Accuracy_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 2:
		    SetRandSPECIAL_K(Npchar); 
			Npchar.quest.officertype_2 = RandPhraseSimple("���� � ������� �������� ������. ", "��� ���� � ����� � �������� ����������. ");
			Npchar.quest.officertype = "treasurer";
			Npchar.quest.RepairModify        = frandSmall(2.0) + 3;
			Npchar.quest.CommerceModify      = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = frandSmall(2.0) + 2;

			//Npchar.skill.Repair_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Commerce_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 3:
		    SetRandSPECIAL_K(Npchar);
			Npchar.quest.officertype_2 = RandPhraseSimple("��� ������������ �������� ����. ", "������, �������, �� ��������, �� �������� � � ����. ");
			Npchar.quest.officertype = "navigator";
			Npchar.quest.SailingModify        = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify        = frandSmall(2.0) + 1.3;
			Npchar.quest.SneakModify          = frandSmall(2.0);

			//Npchar.skill.Sailing_rate = makeint(MOD_EXP_RATE * upSkill);
		break;

        case 4:
		    SetRandSPECIAL_F(Npchar);
			Npchar.quest.officertype = "fighter";
			Npchar.quest.FencingModify         = frandSmall(2.0) + 2;
			Npchar.quest.PistolModify          = frandSmall(2.0) + 2;

			//Npchar.skill.Fencing_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Pistol_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;
        // �� ��� ����� -->
        case 5:
		    SetRandSPECIAL(Npchar);
			//Npchar.quest.officertype = OFFIC_TYPE_FIRSTMATE;
			Npchar.quest.LeadershipModify     = frandSmall(3.0) + 2;
			Npchar.quest.SailingModify        = frandSmall(1.0) + 1;
			Npchar.quest.SneakModify          = Rand(3) + 1;

			//Npchar.skill.Leadership_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Sneak_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 6:
		    SetRandSPECIAL(Npchar);
			//Npchar.quest.officertype = OFFIC_TYPE_DOCTOR;
			Npchar.quest.DefenseModify       = Rand(3) + 3;
			Npchar.quest.SneakModify         = Rand(3);
		break;
		// �� ��� �����
		case 7:
		      SetRandSPECIAL(Npchar);
			//Npchar.quest.officertype = OFFIC_TYPE_CARPENTER;
			Npchar.quest.RepairModify         = Rand(3) + 3;
			Npchar.quest.SneakModify          = Rand(3);
		break;
	}

	// Npchar.rank = makeint(Pchar.rank) - 2 + Rand(4);
	Npchar.experience = 0;// CalculateExperienceFromRank(sti(Npchar.rank));
    // fix 16.12.2003 -->
	//CalculateAppropriateSkills(NPchar);
	float MiddleK = GetMiddleMainSkill();

    Npchar.skill.Leadership    = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Fencing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sailing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Accuracy      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Cannons       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Grappling     = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Repair        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Defence       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Commerce      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sneak         = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Pistol        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingLight  = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingHeavy  = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Fortune       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;

    CorrectSkillParam(Npchar); // �������� � 0-1
    // boal fix 16.12.2003 <--

	Npchar.skill.Leadership   = makeint(stf(Npchar.skill.Leadership)   + 10*stf(Npchar.quest.LeadershipModify));
	Npchar.skill.Fencing      = makeint(stf(Npchar.skill.Fencing)      + 10*stf(Npchar.quest.FencingModify));
	Npchar.skill.Sailing      = makeint(stf(Npchar.skill.Sailing)      + 10*stf(Npchar.quest.SailingModify));
	Npchar.skill.Accuracy     = makeint(stf(Npchar.skill.Accuracy)     + 10*stf(Npchar.quest.AccuracyModify));
	Npchar.skill.Cannons      = makeint(stf(Npchar.skill.Cannons)      + 10*stf(Npchar.quest.CannonsModify));
	Npchar.skill.Grappling    = makeint(stf(Npchar.skill.Grappling)    + 10*stf(Npchar.quest.GrapplingModify));
	Npchar.skill.Repair       = makeint(stf(Npchar.skill.Repair)       + 10*stf(Npchar.quest.RepairModify));
	Npchar.skill.Defence      = makeint(stf(Npchar.skill.Defence)      + 10*stf(Npchar.quest.DefenseModify));
	Npchar.skill.Commerce     = makeint(stf(Npchar.skill.Commerce)     + 10*stf(Npchar.quest.CommerceModify));
	Npchar.skill.Sneak        = makeint(stf(Npchar.skill.Sneak)        + 10*stf(Npchar.quest.SneakModify));
    Npchar.skill.Pistol       = makeint(stf(Npchar.skill.Pistol)       + 10*stf(Npchar.quest.PistolModify));
    Npchar.skill.FencingLight = makeint(stf(Npchar.skill.FencingLight) + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.FencingHeavy = makeint(stf(Npchar.skill.FencingHeavy) + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.Fortune      = makeint(stf(Npchar.skill.Fortune)      + 10*stf(Npchar.quest.SneakModify));

    CorrectSkillParam(Npchar); // �������� � 0-10

    Npchar.reputation = rand(84) + 5;
    // ����������� ������� -->
    Npchar.loyality = 5 + rand(10);
    if (sti(Npchar.reputation) > 41)
    {
        Npchar.alignment = "good";
    }
    else
    {
        Npchar.alignment = "bad";
    }
    SetRankFromSkill(Npchar);

    LAi_NPC_Equip(Npchar, sti(Npchar.rank), true, true); // fix 101104 ������� ��� ������!!!!

    SetFantomHP(Npchar);

    Npchar.quest.OfficerPrice    = (11 + 2*sti(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
    Npchar.quest.OfficerLowPrice = makeint(sti(Npchar.quest.OfficerPrice)/1.5 + 0.5);
}

int FindFreeRandomOfficer()
{
	int Counter, OfficerIdx;
	string OfficerId;
	// special -->
	if (GetCharacterMaxOfficersQty(Pchar) <= (GetOfficerPassengerQuantity(Pchar) + GetCompanionQuantity(Pchar) - 1)) return -1;
	return 1;
}
void LandEnc_OfficerHired()
{
	ref sld = &Characters[sti(Pchar.questTemp.HiringOfficerIDX)];
    sld.Money = 0; // ������

	AddPassenger(pchar, sld, false);

	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
	/*if (sld.sex == "man") sld.greeting = "Gr_officer";
	else sld.greeting = "Gr_Danielle";*/
	// boal ����� ���� �� -->
	sld.Payment = true;  // ������� ������� ��� +1 ���������  
	sld.DontClearDead = true;  // �� ������� ����
	// boal ����� ���� �� <--
	DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
	DeleteAttribute(sld, "LifeDay") // ����������
	SaveCurrentNpcQuestDateParam(sld, "HiredDate"); // ���� �����
}

void LandEnc_OfficerStay()
{
    SetCharacterTask_Stay(Characters[makeint(Pchar.questTemp.HiringOfficerIDX)]);
    Characters[makeint(Pchar.questTemp.HiringOfficerIDX)].chr_ai.tmpl = LAI_TMPL_STAY;
    DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
}

void LandEnc_OfficerFired()
{
	ref sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
	sld.location = "none";
	if (sld.sex != "woman")
	{
    	sld.greeting = "Gr_Officer_Fired";
    }
    sld.LifeDay = 0; // ������� ��� ������
    DeleteAttribute(sld, "Payment"); // ������� ������� ��� +1 ���������  
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");
}

bool SetOfficerToMushketer(ref rCharacter, string sMushket, bool _ToMushketer) 
{
	int iItem;
	string sLastGun = "";
	
	if(_ToMushketer && sMushket != "") // ������ ����������
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;
		sLastGun = GetCharacterEquipByGroup(rCharacter, GUN_ITEM_TYPE);
		rCharacter.DefaultAnimation = rCharacter.model.Animation;
		rCharacter.IsMushketer = true; // ������ ���� "��������"
		rCharacter.IsMushketer.MushketID = sMushket; // ��������, ����� ������ ������
		rCharacter.IsMushketer.LastGunID = sLastGun; // �������� ID ����������� �������
		rCharacter.model = rCharacter.model + "_mush";
		rCharacter.model.animation = "mushketer"; // ������ ��������
		Characters_RefreshModel(rCharacter); // ������� ������. �����: ��������� ������ ����� �� ���������� ��������
		EquipCharacterByItem(rCharacter, sMushket); // ��������� ������
		rCharacter.Equip.TempGunID = sLastGun; // ������� ��������� �������������, �� � ������ ������
		if (!CheckAttribute(rCharacter, "MusketerDistance")) rCharacter.MusketerDistance = 10.0;
		rCharacter.isMusketer = true;
		rCharacter.isMusketer.weapon = true;
		LAi_SetOfficerType(rCharacter);
	}
	else // ������ ������� ��������������
	{
		rCharacter.model = FindStringBeforeChar(rCharacter.model, "_mush"); // ������ ������ � ��������
		rCharacter.model.Animation = rCharacter.DefaultAnimation;
		Characters_RefreshModel(rCharacter);
		RemoveCharacterEquip(rCharacter, GUN_ITEM_TYPE); // c����� ������
		if(rCharacter.IsMushketer.LastGunID != "" && GetCharacterItem(rCharacter, rCharacter.IsMushketer.LastGunID) > 0)
		{
			EquipCharacterByItem(rCharacter, rCharacter.IsMushketer.LastGunID); // ������ ������� �������
		}
		DeleteAttribute(rCharacter, "IsMushketer");
		DeleteAttribute(rCharacter, "Equip.TempGunID");
		DeleteAttribute(rCharacter, "MusketerDistance");
		DeleteAttribute(rCharacter, "isMusketer");
		LAi_SetOfficerType(rCharacter);
	}
	return true;
}
