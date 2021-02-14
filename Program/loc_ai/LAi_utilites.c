//#20171008-01 Brothel adjust changeover period
#define BROTHEL_CHANGEDAYS 200

string arrayNPCModel[64];
int    arrayNPCModelHow; // ��� ������������ ������� � ����� �������

// ������� ������� � ������� + �������, �������-����������� (����� 48�) ����������� boal 13.05.06
void CreateCitizens(aref loc)
{
	if(CheckAttribute(pchar, "Arrive.EnemyPort")) //Korsar Maxim - ���� ���� ���� ��������, �� ����� ������� ��������� ������ ��� ���� ������ �� ������.
	{
		DoQuestFunctionDelay("SetPortAlarm", 1.0);
		DeleteAttribute(pchar, "Arrive.EnemyPort");
	}
	
	if (loc.type != "town" && loc.type != "church" && loc.type != "residence") return; //��������� ��������� �� ������ ������������ �����
	if(LAi_IsCapturedLocation) // fix ����� �������, ����� ����� ������ ��� ������
	{
		return;
	}
	int iColony = -1;
	int iNation = -1;

	if (isLocationHasCitizens(loc.id)) return; // boal  ���� ���� ��� � ���� ����, �� �� �����
	
	if(CheckAttribute(loc, "fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	if(iColony == -1)
	{
		return;
	}
	
	iNation = GetCityNation(loc.fastreload);
	
	if(iNation == -1)
	{
		return;
	}

	int iCitizensQuantity, iModel, iSailorQty;
	ref chr;
	int iChar, i, iSex;
	bool bOk;
	string slai_group, locatorName, sType;
    slai_group = GetNationNameByType(iNation)  + "_citizens"; 

	// Lugger -->
	QuestDuelCheckPossibility(loc);
	// Lugger <--

	// ����� -->
	if (loc.type == "town")
	{
		int iPoorIdx = GetCharacterIndex(colonies[iColony].id + "_Poorman");
		if (iPoorIdx != -1)
		{
			if (rand(1)) 
			{
				characters[iPoorIdx].PoorSit = true;
				sType = "locator" + rand(2);
				locatorName = characters[iPoorIdx].forSit.(sType);
			}
			else 
			{ 
				DeleteAttribute(&characters[iPoorIdx], "PoorSit");
				locatorName = characters[iPoorIdx].forStay.locator;
			}
			LAi_SetPoorTypeNoGroup(&characters[iPoorIdx]);
			if (LAi_CheckLocatorFree("goto", locatorName))
				ChangeCharacterAddressGroup(&characters[iPoorIdx], loc.id, "goto", locatorName);
			else
				PlaceCharacter(&characters[iPoorIdx], "patrol", "random_free");

		}
	}
	// ����� <--

    // �������� -->	
    arrayNPCModelHow = 0;
    
	if (checkAttribute(loc, "citizens") || loc.type == "church")
	{
		iCitizensQuantity = rand(8) + 6;
		
       if(loc.type == "town")   iSailorQty = rand(2)+2;		
	   else iSailorQty = 0;
		
		if (loc.type == "church")  iCitizensQuantity = rand(6) + 2;

        if(iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true)//�������
		{
			for(i=0; i<iSailorQty; i++)//�������
			{
    	   	    iSex = MAN;
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade3","blade5"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade3","blade5"));
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Sailor.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "pirat_common";
				if (rand(40) <= 10+GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP)) //WW ���������� � ������� � 20-40 ��������� ������� �� ���������� 
				{
					chr.quest.crew = "true";
					chr.quest.crew.qty = 10+rand(14)+(GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP) * 6); //WW   10-24 + 6-60 = 16-84    �� ����������   
					chr.quest.crew.type = rand(2);
					chr.quest.crew.money = 60+rand(2)*20+rand(80);   // WW  60-180
					chr.talker = rand(9);
				}
			}
		}

		for(i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true)
			{
			    // ����� ���������� �������� ����� ����, ���� ��� �������? ������� == ������ - ��� ��
                if (loc.type == "church") iSex = MAN;
				else iSex = rand(WOMAN);
                sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
			}
			else
			{
                iSex = MAN;
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, iSex, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, iSex);
			
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			LAi_SetLoginTime(chr, 6.0, 21.99);
			
			if (sti(chr.nation) == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				LAi_SetWarriorType(chr);
				LAi_warrior_DialogEnable(chr, true);
				chr.watchBoxes = true;
			}
			else
			{
				if (loc.type == "church" && chr.sex == "man")
				{
				    LAi_SetSitType(chr);
				}
				else
				{
					LAi_SetCitizenType(chr);
				}
			}

			if (LAi_IsCapturedLocation)  // to_do ����� �� �����, ���� �� �������, �� ���� �� �������
			{
				chr.location.loadcapture = 1;
				LAi_SetActorType(chr);
				LAi_ActorSetLayMode(chr);
				LAi_SetImmortal(chr, 1);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
            if (loc.type == "church" && chr.sex == "man")
            {
                PlaceCharacter(chr, "sit", "random_free");
            }
            else
			{
				PlaceCharacter(chr, "goto", "random_free");
			}
			if (loc.type == "church")
			{
				chr.dialog.filename    = "Enc_Walker.c";
				chr.nonTable = true;
			}
			else
			{
				chr.dialog.filename    = "Common_citizen.c";
			}
			chr.dialog.currentnode = "first time";

			if(sti(chr.nation) == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				chr.greeting = "pirat_common";
			}
			else
			{
				if(chr.sex == "man")
				{
					chr.greeting = "cit_common";
				}
				else
				{
					chr.greeting = "Gr_Woman_Citizen";
				}
			}
			SetFoodToCharacter(chr, 3, 20);
		}
	}
	// �������� <--

    // �������� -->
	aref st;
	if (checkAttribute(loc, "locators.merchant"))
	{
		makearef(st, loc.locators.merchant);
		iCitizensQuantity = GetAttributesNum(st) / 2;
		for (i=0; i<iCitizensQuantity; i++)
		{
			//eddy. ����� �� ������ ������ �������
			iSex = rand(1);
			iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);

			chr = &characters[iChar];
			SetNPCModelUniq(chr, "citizen", iSex);
			
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			chr.Merchant = true; // ���� "��������"
			LAi_SetLoginTime(chr, 7.0, 20.0);

			//PlaceCharacter(chr, "merchant", "random");
			ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
			LAi_SetMerchantType(chr);
			chr.dialog.filename = "Common_ItemTrader.c";
			chr.dialog.currentnode = "first time";
			if (chr.sex == "man") chr.greeting = "tra_common";
			else chr.greeting = "tra_woman_common";			
   			if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	} 
	// �������� <--	
	// ������� -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref solderLoc;
		makearef(st, loc.locators.soldiers);
		iCitizensQuantity = GetAttributesNum(st);		
		for (i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			LAi_SetLoginTime(chr, 6.0, 23.0); //� ����� ����� ������� �� ������� :)

			//locatorName = PlaceCharacter(chr, "soldiers", "random_free"); // ���� ��������� ���� ��-�� ������ �������
			solderLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(solderLoc);
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
			// eddy. ���������, ������ �� ������ ���� ����������� -->
			if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
			{
				chr.protector = true;
				chr.greeting = "soldier_arest";
			}
			else chr.greeting = "soldier_common";
			// <-- eddy. ���������, ������ �� ������ ���� �����������

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";   
			LAi_SetGuardianType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			SetFoodToCharacter(chr, 3, 20);
		}
	}
	// ������� <--
	// ������� -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
			if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
			LAi_SetLoginTime(chr, 0.0, 24.0);
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				chr.greeting = "soldier_common";
			}
			PlaceCharacter(chr, "patrol", "random_free");
		}
		//���������
		for (i=1; i<=3; i++)
		{
			if(iNation == PIRATE)
			{
                sType = GetPirateMushketerModel();
			}
			else
			{
                sType = NationShortName(iNation) + "_mush_" + i;
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// ���� ���� ���������
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.greeting = "soldier_common";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
			LAi_SetLoginTime(chr, 0.0, 24.0); //� ����� ����� ������� �� ������� :)

			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			SetFoodToCharacter(chr, 3, 20);
		}
	}
	// ������� <--
	// �������� -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[7];
		locReload[0] = "reload4_back";
		locReload[1] = "reload5_back";
		locReload[2] = "reload6_back";
		locReload[3] = "reload7_back";
		locReload[4] = "reload8_back";
		locReload[5] = "reload10_back";
		locReload[6] = "reload9_back";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";
		for (i=iQtyCarrier; i>0; i--)
		{
			//������� ���������� ��� ���� ������� ��������
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = ""; //��� �������� ������ �� ������
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(6);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = frand(7) + 4.0;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// �������� <--
	//--> ��������� ��������� ������������ �� ������ ���������
	if (CheckAttribute(loc, "questSeekCap") && GetCharacterIndex("QuestCitiz_" + loc.fastreload) == -1)
	{		
		string sModel, sSex, sAnimation, sGr;	
		if (rand(1))
		{
			sModel = "citiz_"+(rand(11)+1);
			sSex = "man";
			sAnimation = "man";
			sGr = "cit_common";
		}
		else
		{
			sModel = "girl_"+(rand(8)+1);
			sSex = "woman";
			sAnimation = "towngirl";
			sGr = "Gr_Woman_Citizen";
		}
		chr = GetCharacter(NPC_GenerateCharacter("QuestCitiz_"+loc.fastreload, sModel, sSex, sAnimation, 10, iNation, -1, false));
		chr.city = loc.fastreload;
		chr.dialog.filename   = "Quest\ForAll_dialog.c";
		chr.dialog.currentnode = "SCQ_" + sSex;
		chr.greeting = sGr; 
		chr.talker = sti(loc.questSeekCap); //������ ������
		chr.quest.SeekCap.numQuest = rand(2); //����� ����� ����� ������
		LAi_SetLoginTime(chr, 6.0, 21.99);
		LAi_SetCitizenType(chr);
		//#20200315-01
        chr.chr_ai.type.checkFight = 999999.0;
		LAi_group_MoveCharacter(chr, slai_group);
		PlaceCharacter(chr, "goto", "random_free");
	}
}

// ������ ������������ � �������, ���� �������-������������ (24�) ����������� boal 13.05.06
void CreateHabitues(aref loc)
{
	int iColony = -1;
	int iNation = -1;
	
	if (!checkAttribute(loc, "habitues")) return;
	if(LAi_IsCapturedLocation) return;
	
	OfficersReactionResult(); // ���� ���� � ������, ��� ���� ����� � �� ��� - ���� ��� �������

	if (!isLocationHasCitizens(loc.id))  // boal  ���� ���� ��� � ���� ����, �� �� �����
	{
		if (CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);

			if(iColony == -1)
			{
				return;
			}

			iNation = GetCityNation(loc.fastreload);

			if (iNation == -1)
			{
				return;
			}

			string sColony = loc.fastreload;
			int iCitizensQuantity, iModel;
			ref chr;
		    string slai_group;
			int iChar;
			int i, n, k;
			string sTemp;
/// ---> Navarra			
			string locatorName;
			string sType;
/// <--- Navarra
			slai_group = GetNationNameByType(iNation)  + "_citizens";

            arrayNPCModelHow = 0;
			// ������ �����, �� �������� ����� ��� ��
/// ---> Navarra
			// for (i = 1; i <=4; i++)
			for (i = 1; i <=10; i++)
/// <--- Navarra		
			{
                if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					if (Colonies[iColony].nation == PIRATE) sType = RandPhraseSimple("pirate","sailor");
					else sType = RandPhraseSimple("citizen","sailor");
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);

					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					//PlaceCharacter(chr, "sit", "random");
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Tavern_Mate";
				}
			}
			iChar = GetCharacterIndex(Colonies[iColony].id + "_Smuggler");
			if (iChar != -1) // � ������� ��� ������ - ��� �������
			{
		        chr = &characters[iChar];
				if (sti(Colonies[iColony].HeroOwn) != true)
				{ // ������ ���������� ������, �� ������, �� ������� � ������� ������ ���
		            chr.City = Colonies[iColony].id;  // ��� ����� ��������� � �������, �� ��� ������ �� 20 ������� ������.
		            chr.nation = iNation; // ����� ��� �����, �� ��� ����� ������ ������� �� ������, �� �� �����
					CreateModel(iChar, "pirate", MAN);
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					LAi_group_MoveCharacter(chr, slai_group);
/// ---> Navarra
				///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
					{	LAi_SetGroundSitType(chr);	}
				///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
					{	LAi_SetBarmanType(chr);		}
/// <--- Navarra
				}
				else
				{
				    ChangeCharacterAddressGroup(chr, "none", "none", "none");
				}
				// ��� ������
			}
			// ������ ����� � ���������, ������ � �������� �������� -->
			if (iNation == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "citizen", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
/// ---> Navarra
				///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
					{	LAi_SetGroundSitType(chr);	}
				///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
					{	LAi_SetBarmanType(chr);		}
/// <--- Navarra		
				LAi_group_MoveCharacter(chr, slai_group);
				chr.Name = "��������";
				chr.LastName = "";
				chr.dialog.filename = "RelationAgent_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_RelationAgent";
				LAi_group_MoveCharacter(chr, slai_group);
			}
			// ������ ����� � ���������, ������ � �������� �������� <--
			// ������� -->
			iCitizensQuantity = rand(6) - 3;
			for (i = 0; i <iCitizensQuantity; i++)
			{
			    iChar = NPC_GeneratePhantomCharacter("pofficer", iNation, MAN, 1);
				chr = &characters[iChar];
				chr.model = "Officer_"+(rand(63)+1);
				FaceMaker(chr);
				SetOfficerParam(chr, rand(4));
				sTemp = PlaceCharacter(chr, "sit", "random_free");
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
/// ---> Navarra
				///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
					{	LAi_SetGroundSitType(chr);	}
				///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
					{	LAi_SetBarmanType(chr);		}
/// <--- Navarra
				// ��� ������
				chr.dialog.filename = "Enc_Officer_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_Officer";
    			if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// ������� <--
			if (!IsCharacterPerkOn(pchar, "Adventurer"))
			{
				if (rand(16 - makeint(GetCharacterSPECIALSimple(pchar, SPECIAL_L)/3)) == 3 || TestRansackCaptain) // ugeen --> �������� ����������� ��������� �������� �������� � ������ �� 1/20
				{ // ����� ������
					Log_TestInfo("������������� ������ ���� � �������");
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "pirate", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
					ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetSitType(chr);
	/// ---> Navarra
					///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
						if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
						{	LAi_SetGroundSitType(chr);	}
					///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
						if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
						{	LAi_SetBarmanType(chr);		}
	/// <--- Navarra
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "Enc_Treasure_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Smuggler Agent";
					
					if (GetCharacterItem(pchar, "map_full") == 0) // ��� ����� - �������, ���� �����
					{
						aref item;
						Items_FindItem("map_full", &item);
						FillMapForTreasure(item);
						pchar.GenQuest.TreasureMoney = 5000 + rand(60)*500;
					}
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			if (IsCharacterPerkOn(pchar, "Adventurer"))
			{
				if (rand(10 - makeint(GetCharacterSPECIALSimple(pchar, SPECIAL_L)/3)) == 0 || TestRansackCaptain) // ugeen --> �������� ����������� ��������� �������� �������� � ������ �� 1/20
				{ // ����� ������
					Log_TestInfo("������������� ������ ���� � �������");
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "pirate", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
					ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetSitType(chr);
	/// ---> Navarra
					///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
						if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
						{	LAi_SetGroundSitType(chr);	}
					///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
						if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
						{	LAi_SetBarmanType(chr);		}
	/// <--- Navarra
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "Enc_Treasure_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Smuggler Agent";
					
					if (GetCharacterItem(pchar, "map_full") == 0) // ��� ����� - �������, ���� �����
					{
						aref item1;
						Items_FindItem("map_full", &item1);
						FillMapForTreasure(item1);
						pchar.GenQuest.TreasureMoney = 5000 + rand(60)*500;
					}
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			
			else
			{
				iCitizensQuantity = rand(3) - 1 ; // ������� ����� ��� ��������
				for (i = 0; i <iCitizensQuantity; i++)
				{
				    iChar = NPC_GeneratePhantomCharacter("citizen", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "citizen", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // ����� �� ���� �����, ���� ��� ����� ������
                    ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
/// ---> Navarra				
				///	if (findsubstr(sTemp, "sit_ground" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_ground" , 0) != -1)
					{	LAi_SetGroundSitType(chr);	}
				///	if (findsubstr(sTemp, "sit_bar" , 0) != -1)
					if (findsubstr(chr.location.locator, "sit_bar" , 0) != -1)
					{	LAi_SetBarmanType(chr);		}
/// <--- Navarra		
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Tavern_Mate";
				}
			}
		}
	}
	//navy -- ��� � �������.
	//��� ����� ���������� ��� ������ ������ � �������...
	PGG_TavernCheckIsPGGHere();
}

// ���������� ����������. eddy
void CreateIncquisitio(aref loc)
{	
	if (GetCityNation("Santiago") != SPAIN) return; 
	
	if (CheckAttribute(loc, "Incquisitio"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i, nSit;
		//====> �������� �����������
		if (CheckNPCQuestDate(loc, "Incquisitor_date"))
		{
			SetNPCQuestDate(loc, "Incquisitor_date");
			LocatorGroup = "goto";
			nSit = rand(2)+1;
			for (i=1; i<=3; i++)
			{
				LocatorGroup = "goto";
				LocatorName = LAi_FindRandomLocator("goto");				 
				if (i==nSit) 
				{
					LocatorGroup = "sit";
					LocatorName = "sit"+(rand(3)+1);			
				}
				sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+i, "priest_sp"+i, "man", "man2", 20, SPAIN, 1, false));
				sld.Dialog.Filename = "Incquistors.c";									
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (i==nSit) LAi_SetSitType(sld);
				else LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", LocatorGroup, LocatorName);
				SetFoodToCharacter(sld, 3, 20);
			}
		}
		//====> �������� ������.
		if (CheckNPCQuestDate(loc, "Guard_date"))
		{
			SetNPCQuestDate(loc, "Guard_date");
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("IncqGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 35, SPAIN, 1, true));
				sld.City = "Santiago";
				sld.CityType = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 90, BLADE_LONG, "pistol3", 100);//�������
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
				locatorName = PlaceCharacter(sld, "soldiers", "random");
				// eddy. ���������, ������ �� ������ ���� ����������� -->				
				if (locatorName == "soldier1" || locatorName == "soldier2")
				{
					sld.protector.CheckAlways = true; //��������� ������
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "soldier_arest";
				}
				else
				{
					if (findsubstr(locatorName, "protector" , 0) != -1) sld.protector = true;
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.greeting = "soldier_common";
				}
				// <-- eddy. ���������, ������ �� ������ ���� �����������
				SetFoodToCharacter(sld, 3, 20);
			}
		}
		//====> �������� �����������, ��� � �����.
		if (!CheckAttribute(loc, "Prison_date") || GetNpcQuestPastDayParam(loc, "Prison_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "Prison_date");
			for (i=1; i<=8; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, SPAIN, 30, false));							
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "Gr_prison";
					LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					if (rand(10)>5) LAi_ActorSetLayMode(sld);
					else 
					{
						LAi_SetGroundSitType(sld);
					}				
					//ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison"+i);
					PlaceCharacter(sld, "prison", "random_free");
					SetFoodToCharacter(sld, 3, 20);
				}
			}
		}
	}
}
//eddy. ���������� �����
void CreateMayak(aref loc)
{
	if (loc.type == "mayak")
	{
		if (!CheckAttribute(loc, "Mayak_date") || GetNpcQuestPastDayParam(loc, "Mayak_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Mayak_date");

			if(CheckAttribute(loc, "from_colony")) 
			{
				int iColony = FindColony(loc.from_colony);
			}
			else 
			{
				iColony = FindColony(GetCityNameByIsland(GiveArealByLocation(loc)));
			}
			if(iColony == -1) return;

			int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loc)));
			if(iNation == -1) return;

			int iCitizensQuantity, iModel;
			ref chr;
			aref st, solderLoc;
			int iChar, i;
			string slai_group, locatorName;
			slai_group = GetNationNameByType(iNation)  + "_mayak"; 
			// ������� -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
			{
				makearef(st, loc.locators.soldiers);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);					
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{		
						iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
						chr = &characters[iChar];
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "eng_mush_1", "man", "mushketer", sti(pchar.rank), iNation, 2, false));
						chr.id = "GenChar_" + chr.index;
						chr.MusketerDistance = 0;
					}					
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					chr.greeting = "soldier_common";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+6, true); // ������ ����
					LAi_SetLoginTime(chr, 0.0, 24.0);
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);
					ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
					// eddy. ���������, ������ �� ������ ���� ����������� -->
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{
						chr.protector = true;
						chr.greeting = "soldier_arest";
						if (locatorName != "protector1" && locatorName != "protector2") 
						{
							chr.protector.CheckAlways = 1; //��������� ������
							if (locatorName == "protector11") chr.dialog.currentnode = "PortRoyal_Mayak";
							else chr.dialog.currentnode = "PortRoyal_Gans";
						}
					}
					else chr.greeting = "soldier_common";
					// <-- eddy. ���������, ������ �� ������ ���� �����������
					chr.dialog.filename = "Common_Soldier.c";
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					SetFoodToCharacter(chr, 3, 20);
				}
			}
			// ������� <--
			// ������� -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
			{
				makearef(st, loc.locators.patrol);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
					chr = &characters[iChar];
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetPatrolType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
					PlaceCharacter(chr, "patrol", "random_free");
					chr.dialog.filename = "Common_Soldier.c";
					chr.dialog.currentnode = "first time";
					SetFoodToCharacter(chr, 3, 20);
				}
			}
			// ������� <--
			LAi_group_SetLookRadius(slai_group, 80);
			LAi_group_SetHearRadius(slai_group, 80);
		}
	}
}

void CreateBrothels(aref loc)
{
	if (CheckAttribute(loc, "brothel"))
	{
		ref location;
		if (findsubstr(loc.id, "SecBrRoom", 0) != -1)
		{
			location = &locations[FindLocation(loc.fastreload + "_Brothel")];
		}
		else
		{
			makeref(location, loc);
		}
		if (!CheckAttribute(location, "Brothel_date") || GetNpcQuestPastDayParam(location, "Brothel_date") > 100)
		{
			ref sld;
			int iColony, iNation, qty, num, qtyAll;
			// ==>  ������ ������� ����, ���� �� �������� � ��������
			string horse[8];
			horse[0] = "horse01";
			horse[1] = "horse02";
			horse[2] = "horse03";
			horse[3] = "horse04";
			horse[4] = "horse05";
			horse[5] = "horse06";
			horse[6] = "horse07";
			horse[7] = "horse08";
			SaveCurrentNpcQuestDateParam(location, "Brothel_date");
			if(CheckAttribute(location, "fastreload"))
			{
				iColony = FindColony(location.fastreload);
			}
			else return;
			iNation = GetCityNation(location.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			//Boyer change
			//qty = 1;
			qtyAll = rand(2) + 4;
			//while (qty < qtyAll)
			for(qty=1; qty < qtyAll; qty++)
			{
				num = rand(7);
				//if (horse[num] != "")
				//{
					//#20171008-01 Brothel adjust changeover period
					sld = GetCharacter(NPC_GenerateCharacter("HorseGen_"+location.index +"_"+ qty, horse[num], "woman", "towngirl", 3, iNation, 100, false));
					sld.City = location.fastreload;
					sld.CityType = "horse";
					sld.dialog.filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Horse_talk";
					sld.greeting = "whore";
					switch (location.fastreload)
					{
						case "Tortuga":		 sld.quest.price = 1000*(rand(4)+5); break;
						case "PortRoyal":	 sld.quest.price = 1100*(rand(4)+5); break;
						case "Panama":		 sld.quest.price = 900*(rand(4)+5); break;
						case "Marigo":	     sld.quest.price = 700*(rand(4)+5); break;
						case "Bridgetown":	 sld.quest.price = 400*(rand(4)+5); break;
						case "FortFrance":	 sld.quest.price = 500*(rand(4)+5); break;
						case "Charles":		 sld.quest.price = 300*(rand(4)+5); break;
						case "SantoDomingo": sld.quest.price = 200*(rand(4)+5); break;
					}
					LAi_SetCitizenType(sld);
					LAi_group_MoveCharacter(sld, slai_group);
					ChangeCharacterAddressGroup(sld, location.id, "goto", "goto"+qty);
				//	horse[num] = "";
				//	qty++;
				//}
				SetFoodToCharacter(sld, 3, 20);
			}
		}
	}
}

//eddy. ���������� ��������� ���������
void CreatePearlVillage(aref loc)
{
	if (CheckAttribute(loc, "pearlVillage") && sti(loc.pearlVillage) == true)
	{	
		string iPrefix, sTemp;
		sTemp = loc.id;
		iPrefix = GetSymbol(sTemp, strlen(sTemp)-1); //�������� ������� ���� ������� ���
		int iPearNation = sti(colonies[FindColony("SantaCatalina")].nation);
		int iTemp = GetCharacterIndex("PearlGuardMan_"+iPrefix);
		if (iTemp != -1 && !CheckAttribute(&characters[iTemp], "quest.TalkOk")) 
		{//���� �� ������� ��������
			if (characters[iTemp].location == "none")
			{
				loc.pearlVillage = false;
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box1");
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box2");
				Log_SetStringToLog("������� �� ������� � ��������� ����� ������� �������, � ���� ��������� �������� ������� � ��������.");
				return; 
			}
			else
			{//���� ����� ������ ��������
				DoQuestCheckDelay("Pearl_GuardManIsLife", 3.5);
				pchar.quest.Pearl_GuardManIsLife.idx = iTemp;//������ �������� ��������
				chrDisableReloadToLocation = true;			
			}
		}
		else 
		{//������� ����
			//LAi_group_SetRelation("PearlGroup_"+iPrefix, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		}
		ref chr;
		int num, i, iMassive, iRank;
		string sAnime;
		string model[25];
		loc.pearlVillage = false; //���� �� �������� ������
		// ==> ����� �������������
		iRank = 20+rand(15);
		chr = GetCharacter(NPC_GenerateCharacter("HeadMan_"+iPrefix, "SpaOfficer"+(rand(2)+1), "man", "man", iRank, iPearNation, 30, true));
		SetCharacterPerk(chr, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������  
		SetCharacterPerk(chr, "SwordplayProfessional");
		chr.dialog.Filename = "Pearl_dialog.c";
	    chr.dialog.currentnode = "HeadMan";		
		chr.city = "SantaCatalina"; //��� �����-��������
		SetFantomParamFromRank(chr, iRank, true);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
        sTemp = "PearlTown"+iPrefix+"_Townhall"; //ID ����������
		ChangeCharacterAddressGroup(chr, sTemp, "goto", "goto5");
		// ==> ������ �����
		DeleteAttribute(&locations[FindLocation(sTemp)], "box1");
		DeleteAttribute(&locations[FindLocation(sTemp)], "box2");
		pchar.GenQuestBox.(sTemp) = true;
        pchar.GenQuestBox.(sTemp).box1.items.jewelry11 = rand(150) + rand(150);
        pchar.GenQuestBox.(sTemp).box2.items.jewelry12 = rand(250) + rand(250);
		// ==> ���������, ��������� ���� ��������
		model[0] = "pirate_1";
		model[1] = "pirate_2";
		model[2] = "pirate_3";
		model[3] = "pirate_4";
		model[4] = "pirate_5";
		model[5] = "pirate_6";
		model[6] = "pirate_7";
		model[7] = "pirate_8";
		model[8] = "pirate_9";
		model[9] = "pirate_10";
		model[10] = "pirate_11";
		model[11] = "pirate_12";
		model[12] = "pirate_13";
		model[13] = "pirate_14";
		model[14] = "pirate_15";
		model[15] = "pirate_16";
		model[16] = "pirate_17";
		model[17] = "pirate_18";
		model[18] = "pirate_19";
		model[19] = "pirate_20";
		model[20] = "pirate_21";
		model[21] = "pirate_22";
		model[22] = "pirate_23";
		model[23] = "pirate_24";
		model[24] = "pirate_25";
		//i = 0;
		num = rand(3) + 2;
		//while(i < num)
		for(i=0; i < num; i++)
		{
			iMassive = rand(25);
			//if (model[iMassive] != "")
			//{
				chr = GetCharacter(NPC_GenerateCharacter("FightMan"+iPrefix+"_"+i, model[iMassive], "man", "man", 15, iPearNation, 30, true));
				SetFantomParamFromRank(chr, 15, true);
				chr.dialog.Filename = "Pearl_dialog.c";
				chr.dialog.currentnode = "PearlMan";
				chr.greeting = "cit_common";
				chr.city = "SantaCatalina"; //��� �����-��������
				PlaceCharacter(chr, "goto", "random");
				LAi_SetWarriorType(chr);
				LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
			//	i++;
			//	model[iMassive] = "";
			//}
				SetFoodToCharacter(chr, 3, 20);
		}
		// ==> ������ ���������
		model[0] = "indsair2";
		model[1] = "indsar1";
		model[2] = "barmen_1";
		model[3] = "barmen_9";
		model[4] = "citiz_11";
		model[5] = "officer_10";
		model[6] = "shipowner_10";
		model[7] = "trader_13";
		model[8] = "trader_4";
		model[9] = "barmen_9";
		//Boyer change
		//i = 0;
		num = rand(3) + 2;
		//while(i < num)
		for(i=0; i < num; i++)
		{
			iMassive = rand(9);
			//if (model[iMassive] != "")
			//{
				sAnime = "man"
				if (model[iMassive] == "indsair2" || model[iMassive] == "indsar1") sAnime = "man";
				chr = GetCharacter(NPC_GenerateCharacter("WorkMan"+iPrefix+"_"+i, model[iMassive], "man", sAnime, 7, iPearNation, 30, false));
				chr.dialog.Filename = "Pearl_dialog.c";
				chr.dialog.currentnode = "PearlMan";
				if (model[iMassive] == "indsair2" || model[iMassive] == "indsar1")
				{
					chr.name = LinkRandPhrase("������", "��������� ����", "����� �����");
					chr.lastname = "";
					chr.dialog.currentnode = "IndPearlMan";
					chr.greeting = "Gr_PearlIndian";
				}
				else
				{
				    chr.greeting = "cit_common";
				}
				chr.CityType = "citizen";
				chr.city = "SantaCatalina"; //��� �����-��������

				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
			//	i++;
			//	model[iMassive] = "";
			//}
				SetFoodToCharacter(chr, 3, 20);
		}
		//=========================== ������ � ���������� ================================
		//--> ���� ������
		if (loc.id == "Pearl_town_1" && !CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle"))
		{
			chr = GetCharacter(NPC_GenerateCharacter("JohnDavy", "QuestMan1", "man", "man", 10, iPearNation, -1, false)); // ���������� �����, ���� ������ �������, ������ ��� �� �� ���������, � ������ ������
			chr.dialog.Filename = "Quest\GhostShip_dialog.c";
			chr.name = "�����";
			chr.lastname = "�������";
			chr.CityType = "citizen";
			chr.city = "SantaCatalina"; //��������� ���
			chr.RebirthPhantom = true;  // �� ������ �������-����������� (� -1), ���� ����
			chr.greeting = "Gr_JohnDavy";
			PlaceCharacter(chr, "goto", "random");
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
			SetFoodToCharacter(chr, 3, 20);
		}
		//<-- ���� ������
		//--> ������� ����������
		if (loc.id == "Pearl_town_2" && sti(pchar.questTemp.tugs.berglarState) > 6)
		{
			pchar.quest.Berglars_Ostin.win_condition.l1 = "location";
			pchar.quest.Berglars_Ostin.win_condition.l1.location = "PearlTown2_House6";
			pchar.quest.Berglars_Ostin.win_condition = "Berglars_Ostin";
			//==> ���� ���� �� ������
			DeleteAttribute(pchar, "questTemp.tugs");
			//==> ������ �������, ����� �� ������� �� ����
			pchar.questTemp.tugs.berglarState = 0; 
		}
		//<-- ������� ����������
		//=========================== ������ � ���������� ================================
		LAi_group_SetLookRadius("PearlGroup_"+iPrefix, 16);
		LAi_group_SetHearRadius("PearlGroup_"+iPrefix, 10);
	}
}

void CreateInsideHouseEncounters(aref loc)
{	
	if (CheckAttribute(loc, "MustSetReloadBack") && loc.id.label == "house" && !IsLocationCaptured(loc.fastreload+"_town"))
	{
		// ��������� ���������� ������ �� ������������ �����������
		int iBaseCity = FindLocation(loc.fastreload+"_town");
		if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
		//==> ��������� ����� ����
		if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location") && pchar.GenQuest.SeekSpy.Location == loc.id) return;
		//==> ��������� ����� �������� ������
		if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") && pchar.questTemp.jailCanMove.Deliver.locationId == loc.id) return;
		//--> ����� �� ���������
		bool bDN = IsDay();
    	aref arRld, arDis;
		makearef(arRld, loc.reload);
		int i;
    	int	Qty = GetAttributesNum(arRld);
		for (i=0; i<Qty; i++)
    	{
    		arDis = GetAttributeN(arRld, i);
    		if (arDis.name != "reload1")
    		{
				if (bDN && !isBadReputation(pchar, 40)) DeleteAttribute(arDis, "disable");
				else arDis.disable = true; //��������� ���� � ������� 2 ������
    		}
    	}
		//<-- ����� �� ���������
		//==> ��������� ������� ������� ������		
		if (locations[reload_cur_location_index].type == "town")
		{
			ref chr, npchar;
			aref rCity;
			makearef(rCity, locations[iBaseCity].houseEnc);		
			bool bMW = rand(1);
			int iNation = GetCityNation(loc.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			string Model, Name, LastName, sName;
			string sTemp = reload_locator_ref.name + loc.index;
			int iManIdx = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+loc.index);
			int iWomanIdx = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+loc.index);
			if (iWomanIdx != -1 || iManIdx != -1) 
			{				
				if (!CheckAttribute(rCity, sTemp)) //��� ���� ������, �� ��� �� ��� ��, �����!!! ������� �� ������� ������� ������
				{
					if (iWomanIdx != -1) 
					{
						npchar = &characters[iWomanIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "girl_"+(rand(9)+1);
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						rCity.(sTemp) = "woman"; //��������� �����������
						rCity.(sTemp).woman.model = npchar.model;
						rCity.(sTemp).woman.name = npchar.name;
						rCity.(sTemp).woman.lastname = npchar.lastname;
						//<-- �������� ��������� ��� � ��������� �������
					}
					else 
					{
						npchar = &characters[iManIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "citiz_"+(rand(9)+1);
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						//--> �������� ��������� ��� � ��������� �������
						rCity.(sTemp) = "man"; //��������� �����������
						rCity.(sTemp).man.model = npchar.model;
						rCity.(sTemp).man.name = npchar.name;
						rCity.(sTemp).man.lastname = npchar.lastname;
						//<-- �������� ��������� ��� � ��������� �������
					}
				}
				else //��� ���� ��������� �� ��� � ������� �������
				{
					if (iWomanIdx != -1) npchar = &characters[iWomanIdx];
					else npchar =  &characters[iManIdx];
					string sSex = sTemp + "." + rCity.(sTemp);
					if (rCity.(sSex).model != npchar.model) 
					{	//������ �� ������� ������, ���������� ��������	
						npchar.model = rCity.(sSex).model;
						if (rCity.(sTemp) == "man") 
						{
							npchar.sex = "man";
							npchar.model.animation = "man";
							npchar.dialog.currentnode = "HouseMan";
							npchar.greeting = "cit_common";
							LAi_NPC_Equip(npchar, sti(npchar.rank), true, true);
						}
						else 
						{
							npchar.sex = "woman";
							npchar.model.animation = "towngirl";
							npchar.dialog.currentnode = "HouseWoman";
							npchar.greeting = "Gr_Woman_Citizen";
							DeleteAttribute(npchar, "equip");
						}
						npchar.name = rCity.(sSex).name;
						npchar.lastname = rCity.(sSex).lastname;
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // ���������� ������ �� ����					
					}
				}
				return;
			}
			Model = "";
			Name = "";
			LastName = "";
			//-->> ��������� �� ����� ������		
			if (CheckAttribute(rCity, sTemp))
			{
				if (GetNpcQuestPastDayParam(rCity, sTemp) < 30)
				{
					if (rCity.(sTemp) == "man") 
					{//���� ��� �����, �� ����. - ����
						bMW = true;
						if (CheckAttribute(rCity, sTemp + ".woman.model"))
						{
							Model = rCity.(sTemp).woman.model;
							Name = rCity.(sTemp).woman.name;
							LastName = rCity.(sTemp).woman.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".man.lastname"))
							{
								LastName = rCity.(sTemp).man.lastname;
							}
						}
					}
					else 
					{//���� ���� ����, �� ����. - �����
						bMW = false;
						if (CheckAttribute(rCity, sTemp + ".man.model"))
						{
							Model = rCity.(sTemp).man.model;
							Name = rCity.(sTemp).man.name;
							LastName = rCity.(sTemp).man.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".woman.lastname"))
							{
								LastName = rCity.(sTemp).woman.lastname;
							}
						}
					}
				}
				else //����� ������ � ����
				{
					if (rand(10) > 8) //���� �� ������ ���.
					{
						for (i=0; i<Qty; i++) 
    					{//������� ��������� ���� �������� ������� ������ (���� ���� � �� ��������) 
    						arDis = GetAttributeN(arRld, i);
    						if (arDis.name != "reload1")
    						{
								DeleteAttribute(arDis, "disable");
    						}
    					}
						return; 
					}
					SaveCurrentNpcQuestDateParam(rCity, sTemp); //����� ���� ��������� ������� ��� � ���� �������
				}
			}
			else 
			{
				if (rand(10) > 8) //���� �� ������ ���.
				{
					for (i=0; i<Qty; i++) 
    				{//������� ��������� ���� �������� ������� ������ (���� ���� � �� ��������) 
    					arDis = GetAttributeN(arRld, i);
    					if (arDis.name != "reload1")
    					{
							DeleteAttribute(arDis, "disable");
    					}
    				}
					return; 
				}
				SaveCurrentNpcQuestDateParam(rCity, sTemp); //����� ���� ��������� ������� ��� � ���� �������
			}
			//<<-- ��������� �� ����� ������
			if (bMW)
			{//============= ������� ���� ====================
				if (Model == "") Model = "girl_"+(rand(9)+1);
				sName = "HouseWoman_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "woman", "towngirl", rand(2)+4, iNation, 3, false));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseWoman";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //���
				chr.greeting = "Gr_Woman_Citizen";			
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> �������� ��������� ��� � ��������� �������
				rCity.(sTemp) = "woman"; //��������� �����������
				rCity.(sTemp).woman.model = chr.model;
				rCity.(sTemp).woman.name = chr.name;
				rCity.(sTemp).woman.lastname = chr.lastname;
				//<-- �������� ��������� ��� � ��������� �������
				SetFoodToCharacter(chr, 3, 20);
			}
			else
			{//============ ������� ������ ==================
				if (Model == "") Model = "citiz_"+(rand(9)+1);
				sName = "HouseMan_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "man", "man", rand(10)+4, iNation, 3, true));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseMan";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //���
				chr.greeting = "cit_common";
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> �������� ��������� ��� � ��������� �������
				rCity.(sTemp) = "man"; //��������� �����������
				rCity.(sTemp).man.model = chr.model;
				rCity.(sTemp).man.name = chr.name;
				rCity.(sTemp).man.lastname = chr.lastname;
				//<-- �������� ��������� ��� � ��������� �������
				SetFoodToCharacter(chr, 3, 20);
			}
		}
		//==> ���������� ������� �� �� � ������ ������� ����
		else
		{
			//���� � ������� ��� ���� ���-��, �� �� ������� �� �� �� ������ ����
			for(int n=0; n<MAX_CHARACTERS; n++)
			{
				if (characters[n].location == pchar.location && characters[n].id != "Blaze")
				{
					return;
				}
			}
			//��������� ������� �� ������ ����				
			int iLocIndexEnc;
			if (pchar.location.locator == "reload1") iLocIndexEnc = reload_cur_location_index;
			else iLocIndexEnc = reload_location_index;
			int iEnc = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+iLocIndexEnc);
			if (iEnc != -1)
			{
				ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
			}
			else
			{
				iEnc = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+iLocIndexEnc);
				if (iEnc != -1)
				{
					ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
				}
			}
			
		}
	}
}

//���������� � �����������
void CreateInsideResidenceEncounters(aref loc)
{	
	bool bOk;
	if (CheckAttribute(loc, "MustSetReloadBack"))
	{ //���� ��������
		if (CheckAttribute(loc, "id.label"))
		{
			if (loc.id.label == "TownhallRoom" || loc.id.label == "Townhall")
			{
				bOk = CreateQuestResidenceNPC(loc);
				if(!bOk) 
				{
					CreateResidenceNpc(loc);
				}
			}
		}
	}
	else
	{ //���� ��������� �������
		if (CheckAttribute(loc, "id.label"))
		{
			if (loc.id.label == "TownhallRoom")
			{
				bOk = CreateQuestResidenceNPC(loc);
				if(!bOk)
				{
					CreateResidenceNpc(loc);
				}	
			}	
		}
	}
}
//��������� � ������ ����
void CreateResidenceNpc(aref loc)
{
	ref chr;
	int Rank;
	string sModel, sSex, sAni, sNode, sGreeting;
	bool bWeapon;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
	if (rand(10) > 8) return; //���� �� ������ �������
	//==> �������� ���
	int iEncType = rand(2); //0 - ��������, 1 - ��������, 2 - ������.
	if (loc.id.label  == "TownhallRoom") iEncType = 2;
	if (CheckAttribute(loc, "Bedroom"))  iEncType = 0;	
	if (CheckAttribute(loc, "PlayHall")) iEncType = 1;	
	int iNation = GetCityNation(loc.fastreload);
	if (iNation == PIRATE) return; //��������� ���������� ��� �� �����
	switch (iEncType)
	{
	case 0:
		Rank = 3;
		sModel = "girl_"+(rand(9)+1);
		sSex = "woman";
		sAni = "towngirl"
		bWeapon = false;
		sNode = "ResWoman";
		sGreeting = "Gr_Woman_Citizen";
		break;
	case 1:
		Rank = 5;
		sModel = "barmen_"+(rand(15)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResMan";
		sGreeting = "worker";
		break;
	case 2:
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		sModel = "sold_"+NationShortName(iNation)+"_"+(rand(7)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResGuard";
		sGreeting = "guardHouse";
		break;
	}
	//==> ������� ������
	string slai_group = GetNationNameByType(iNation) + "_citizens";		
	string sName = "EncResidence_" + iBaseCity + "_" + loc.index;
	if (GetCharacterIndex(sName) > 0) return; //���� ����
	chr = GetCharacter(NPC_GenerateCharacter(sName, sModel, sSex, sAni, Rank, iNation, 1, bWeapon));
	chr.dialog.Filename = "ResidenceEnc_dialog.c"; 
	chr.dialog.currentnode = sNode;
	chr.CityType = "citizen";
	chr.city = loc.fastreload; //���
	chr.greeting = sGreeting;
	SetFoodToCharacter(chr, 3, 20);
	ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
	LAi_SetOwnerType(chr);
	LAi_group_MoveCharacter(chr, slai_group);
}

bool CreateQuestResidenceNPC(aref loc)
{
	bool bOk;
	if(CheckAttribute(pchar,"questTemp.ReasonToFast"))
	{
		if(!CheckAttribute(pchar,"questTemp.ReasonToFast.GenerateLakey") && (pchar.questTemp.ReasonToFast.chain == "A1"))
		{
			// ������� �����
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther")) return false;
			bOk = ReasonToFast_CreateResidenceNPC(loc);
			if(bOk) 
			{
				pchar.questTemp.ReasonToFast.GenerateLakey = true;
				return true;	
			}
			else return false;	
		}
	}
	return false;
}

//���������� �� ����� ����� � ��������
void CreateSkladInsideEncounters(aref loc)
{
	if (CheckAttribute(loc, "packhouse") && !IsLocationCaptured(loc.id))
	{
		ref chr;
		int iNation = GetCityNation(loc.fastreload);
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
		string sName = "SkladMan_"+reload_cur_location_index;
		if (GetCharacterIndex(sName) > 0) return; //���� ����
		int Rank = sti(pchar.rank) + rand(6);
		if (Rank < 10) Rank += 10;
		if (Rank > 30) Rank -= 10;
		chr = GetCharacter(NPC_GenerateCharacter(sName, "citiz_"+(rand(9)+1), "man", "man", Rank, iNation, 2, true));
		chr.dialog.Filename = "HouseEnc_dialog.c"; 
		chr.dialog.currentnode = "SkladMan";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //���
		chr.greeting = "cit_common";
		LAi_LoginInCaptureTown(chr, false);
		ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
		SetFoodToCharacter(chr, 3, 20);
	}
}

//������
void CreateJail(aref loc)
{
	if (loc.type == "jail")
	{
		ref sld;
		string LocatorGroup, LocatorName, slai_group, nShortName;
		int i, nSit, iNation, iRank;			
		if(!CheckAttribute(pchar, "isload") && reload_location_index != reload_cur_location_index)
		{
			pchar.questTemp.jailCanMove = false;
		}
		if (CheckNPCQuestDate(loc, "Jail_date"))
		{
			SetNPCQuestDate(loc, "Jail_date");
			LAi_group_Delete("Prisoner_Group"); 
			iNation = GetCityNation(loc.parent_colony);
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			nShortName = NationShortName(iNation);
			iRank = sti(pchar.rank) + rand(4);
			if (iRank < 10) iRank = 10;
			if (iRank > 20) iRank = 20;
			//====> ��������� ������
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailOff", "off_"+nShortName+"_"+(rand(1)+1), "man", "man", iRank+5, iNation, 2, true));
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //�������� � �������� �� �����
 			sld.Dialog.Filename = "Common_prison.c";
			sld.dialog.currentnode = "First_officer";
			sld.greeting = "soldier_common";
			FantomMakeCoolFighter(sld, iRank+5, 70, 50, BLADE_LONG, "pistol3", 30);//�������
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			SetFoodToCharacter(sld, 3, 20);
			//====> �������
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailSold_"+i, "sold_"+nShortName+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true));
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_prison.c";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				locatorName = PlaceCharacter(sld, "soldiers", "random_free");
				SetFoodToCharacter(sld, 3, 20);
				// eddy. ���������, ������ �� ������ ���� ����������� -->				
				if (locatorName == "protector1")
				{
					sld.protector = true;
					sld.protector.CheckAlways = 1; //��������� ������
					sld.dialog.currentnode = "First_protector";
					sld.greeting = "soldier_arest";
				}
				else
				{
					sld.dialog.currentnode = "First_soldier";
					sld.greeting = "soldier_common";
				}
				// <-- eddy. ���������, ������ �� ������ ���� �����������
			}
			//====> �������� �����������
			for (i=1; i<=10; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, iNation, 2, false));							
					sld.Dialog.Filename = "Common_prison.c";
					sld.dialog.currentnode = "First_prisoner";
					sld.City = loc.parent_colony;
					sld.greeting = "Gr_prison";
					//LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					locatorName = "prison"+i;
					if (rand(10)>5) 
					{
						LAi_ActorSetLayMode(sld);
						locatorName += "lay";
					}
					else LAi_SetGroundSitType(sld);
					LAi_group_MoveCharacter(sld, "Prisoner_Group");
					ChangeCharacterAddressGroup(sld, loc.id, "prison", locatorName);
				}
			}
		}
	}
}

//�����
void CreateFortsNPC(aref loc)
{	
	if (loc.type == "fort")
	{
		int iNation = GetCityNation(loc.parent_colony);	
		if(iNation == -1) return;
		string slai_group = GetNationNameByType(iNation)  + "_citizens";
		if (locations[reload_cur_location_index].type == "jail" && GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && !CheckAttribute(loc, "loginNpc"))
		{
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			return;
		}
		DeleteAttribute(loc, "loginNpc"); //������� ��������� ���� �� ��������� ��� ��� ������ �� ������
		if (GetNpcQuestPastDayWOInit(loc, "Fort_date") < 2) return;
		ref chr;
		int iCitizensQuantity, iChar, i;
		string locatorName, sType;
		int iColony = -1;
		SaveCurrentNpcQuestDateParam(loc, "Fort_date");
		if(CheckAttribute(loc, "parent_colony")) iColony = FindColony(loc.parent_colony);
		if(iColony == -1) return;		
		arrayNPCModelHow = 0;
		// ������� -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
			aref solderLoc, st;
			makearef(st, loc.locators.soldiers);
			iCitizensQuantity = GetAttributesNum(st);		
			for (i=0; i<iCitizensQuantity; i++)
			{	
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
				solderLoc = GetAttributeN(st, i);
				locatorName = GetAttributeName(solderLoc);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
				// eddy. ���������, ������ �� ������ ���� ����������� -->
				if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
				{
					chr.protector = true;
					chr.greeting = "soldier_arest";
				}
				else chr.greeting = "soldier_common";
				// <-- eddy. ���������, ������ �� ������ ���� �����������
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetGuardianType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
				SetFoodToCharacter(chr, 3, 20);
			}
		}
		// ������� <--
		// ������� -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{			
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			for (i=0; i<iCitizensQuantity; i++)
			{
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "fortPatrol";
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //������ ��� �� ���������� ����� �������� �� ������������
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "pirat_guard";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
				}
				PlaceCharacter(chr, "patrol", "random_free");
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
				SetFoodToCharacter(chr, 3, 20);
			}
		}
		// ������� <--
	}
}

int GetCityNation(string _sColony) // boal ����� ������ ����� �� �� ������
{
    int iColony = FindColony(_sColony)
	if (colonies[iColony].nation == "none")
	{
		return PIRATE;
	}
	return sti(Colonies[iColony].nation);
}

/// boal
// ������� ������� �� ������������ � ��� ������� �����������, ���� ����, �� ����� �� ������
bool isLocationHasCitizens(string _locId)
{
    ref rCharacter; //����
	int n, Qty;
	bool bOk = false;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "CityType")) // ������� �������-�����������
		{
            if (rCharacter.location == _locId)
			{
				bOk = true;
				if (rCharacter.chr_ai.type == "patrol")
					PlaceCharacter(rCharacter, "patrol", "random_free"); //������� ��������� � ������ ���������
			}
		}
    }
	return bOk;
}

void ReSitCharacterOnFree(ref chr, string _locId, string sTemp)
{
	int n, k;
	
	n = 0;
	while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && n < 10)
	{
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    n++;
	}
	
	n = 0;
	while (findsubstr(sTemp, "sit_front" , 0) != -1 && n < 20)
	{    // ���� �� �������� ����� ��������
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    k = 0;
	    while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && k < 10)
		{
		    sTemp = PlaceCharacter(chr, "sit", "random_free");
		    k++;
		}
	    n++;
	}
}

bool CheckNPCModelUniq(ref chr)
{
	int   i, n;
	bool  bOk;
	string sModel = chr.model;
	
    bOk = true;
	for (i=0; i<arrayNPCModelHow; i++)
	{
	    if (arrayNPCModel[i] == sModel)
	    {
	        bOk = false;
	        break;
	    }
	}
	return bOk;
}

void SetNPCModelUniq(ref chr, string sType, int iSex)
{
	int i;
	
	i = 0;
	while (!CheckNPCModelUniq(chr) && i < 10)
	{
	    i++;
	    CreateModel(sti(chr.index), sType, iSex);
	}
	arrayNPCModel[arrayNPCModelHow] = chr.model;
	arrayNPCModelHow++;
}

