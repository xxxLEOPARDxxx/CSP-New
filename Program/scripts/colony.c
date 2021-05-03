int CheckColonyMoney(string sColony)
{
	int iMoney;
	iMoney = sti(Colonies[FindColony(sColony)].money);
	return iMoney;
}

void RemoveColonyMoney(string sColony)
{
	int iMoney;
	int iColony = FindColony(sColony);
	iMoney = sti(Colonies[iColony].money);
	AddMoneyToCharacter(pchar, iMoney);
	Colonies[iColony].money = 0;
}

// ������� �������� ����������
void CreateColonyCommanders()
{
	int iChar;
	
	string sColony;

	int i;
	float x, y, z;  // boal
	
	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // ����������
		// ������� ������� ����� �������
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // ��� ����
        	SetTownMayor(&characters[iChar], sti(colonies[i].nation));
        	characters[iChar].from_sea = colonies[i].from_sea; // ��� ������� � ����
        	characters[iChar].Default  = characters[iChar].location;  // ���� ���������� ������ ������� ���������
        	characters[iChar].Default.BoardLocation = colonies[i].Default.BoardLocation;
        	characters[iChar].Mayor = true; // ������� ����
        }

		// �������� �������� �� �������, � ��� ��� ������, ����� �� ���������?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
            if (iChar != -1)
            {   // ����� �������� ���-�� ������
				characters[iChar].Default.Crew.Quantity    = 1900;
				characters[iChar].Default.Crew.MinQuantity = 1200;
				characters[iChar].Default.nation = characters[iChar].nation; // ���������� �����, ��� ��� �� ���������� (��� �������� ���������)
			}
			continue;
		}
		// boal <--
		colonies[i].commander = colonies[i].id + " Fort Commander";

		iChar = GenerateCharacter(sti(colonies[i].nation), WITH_SHIP, "officer", MAN, 1, FORT_COMMANDER);
		Nations[sti(colonies[i].nation)].fort = sti(Nations[sti(colonies[i].nation)].fort) + 1; // ����� ������ �����
		characters[iChar].id = colonies[i].id + " Fort Commander";
		characters[iChar].location = colonies[i].island;
		characters[iChar].location.group = "reload";
		characters[iChar].location.locator = "reload_fort" + Colonies[i].num;
		colonies[i].commanderIdx = iChar; // ����������� ������ ��������� ��� ������ (����� � �������)
		// boal -->
		characters[iChar].City = colonies[i].id;  // ������� ����������
		characters[iChar].from_sea = colonies[i].from_sea; // ��� ������� � ����
		characters[iChar].CheckLicence    = true; // ��������� ������� �������� �������� ��� �����������,����� ������ � ������������
		if (FindIslandLocatorXYZ(characters[iChar].location, characters[iChar].location.locator, &x, &y, &z))
		{
		    characters[iChar].Ship.Pos.x = x;
		    characters[iChar].Ship.Pos.z = y;
		    characters[iChar].Ship.Pos.z = z;
		}
		SetCaptanModelByEncType(&characters[iChar], "war"); // ������ ������� �����
		SetSeaFantomParam(&characters[iChar], "war"); // ���������!!
		// boal <--
		SetCharacterRelationBoth(iChar,nMainCharacterIndex,RELATION_FRIEND);
		UpdateRelations();

  		characters[iChar].Fort.Cannons.Charge.Type = GOOD_BOMBS;

        SetCrewQuantityFull(&characters[iChar]);
        
		characters[iChar].Fort.Cannons.Type.1 = CANNON_TYPE_CANNON_LBS42;
		characters[iChar].Fort.Cannons.Type.2 = -1;
		characters[iChar].Fort.Cannons.Type.3 = -1;

		if(sti(colonies[i].fort) > 1)
		{
			characters[iChar].Fort.Cannons.Type.2 = CANNON_TYPE_CULVERINE_LBS32;
		}
		if(sti(colonies[i].fort) > 2)
		{
			characters[iChar].Fort.Cannons.Type.3 = CANNON_TYPE_CANNON_LBS48;
		}
		// boal -->
		characters[iChar].Default.Crew.Quantity    = ShipsTypes[SHIP_FORT].MaxCrew;  // ��� ���� ���������, ��� ���������� ���������� ������
		characters[iChar].Default.Crew.MinQuantity = ShipsTypes[SHIP_FORT].MinCrew;
		characters[iChar].Default.nation        = characters[iChar].nation; // ���������� �����, ��� ��� �� ���������� (��� �������� ���������)
		characters[iChar].Default               = colonies[i].from_sea;
        characters[iChar].Default.BoardLocation = colonies[i].Default.BoardLocation;
        characters[iChar].Default.Island        = colonies[i].island; // ������ ��� ����
        characters[iChar].from_sea              = colonies[i].from_sea; // ��� ������� � ����
		// boal <--
	}
}

// ����� ������� �� ����� ������� ������
void RepairAllShips()
{
    int cn;
	ref chr;
	for (int i = 0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			chr = &characters[cn];
			ProcessHullRepair(chr, 100.0);
			ProcessSailRepair(chr, 100.0);
			DeleteAttribute(chr, "ship.blots");
			DeleteAttribute(chr, "ship.sails");
			DeleteAttribute(chr, "ship.masts");
		}
	}
}
//// boal -->
int GetFortCommanderIdx(string _city)
{
     int ind = -1;
     ind = GetCharacterIndex(_city + " Fort Commander");
	 if (ind != -1) return ind;
	 // ���� ��� ���������, ������ ��� �������
	 ind = GetCharacterIndex(_city + "_Mayor");
	 return ind;
}

ref GetFortCommander(string _city)
{
     int ind = GetFortCommanderIdx(_city);

	 return GetCharacter(ind);
}

#define MAX_TOWN_CREW 9 // ��� ����� �������� ������ � ������� (� ����� 32 ���)
#define MAX_ESCADRA_CREW 5 // ������ ������� - ���� �������
#define MAX_TOWN_MUSHKETER 3 //��������� � ������

void SetCrewBackAfterBattle()
{
    float  fTemp, fTemp2;
    int    i, iTemp;
	// ������ ����� �� ������� -->
	fTemp = stf(Pchar.GenQuestFort.PlayerCrew) * stf(Pchar.GenQuestFort.PlayerCrew_per_char); // �����
	fTemp2 = 0.9 + MakeFloat(GetSummonSkillFromName(Pchar, SKILL_DEFENCE)) / SKILL_MAX;
	i     = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp) /fTemp2 + 0.3); // �����
	iTemp = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp)); // �����  ��� ������
	// ������ �������� -->
	iTemp = makeint((iTemp - i)*0.6);
	if (iTemp > 0)
	{
	    if (GetCargoGoods(Pchar, GOOD_MEDICAMENT) < iTemp)
	    {
            iTemp = iTemp - GetCargoGoods(Pchar, GOOD_MEDICAMENT); // ������ �� ���
			RemoveCharacterGoodsSelf(Pchar, GOOD_MEDICAMENT, GetCargoGoods(Pchar, GOOD_MEDICAMENT)); // ��� �����
			i += iTemp; // ������ ������
			Log_Info("��-�� �������� ������������ �� ��� ������ " + iTemp + " ��������");
	    }
	    else
	    {
	        RemoveCharacterGoodsSelf(Pchar, GOOD_MEDICAMENT, iTemp);
	        if (GetCargoGoods(Pchar, GOOD_MEDICAMENT) < 16)
		    {
		        Log_Info("�� ������� " + Pchar.Ship.Name + " �������� ���� ������������");
		    }
	    }
	}
	// ������ �������� <--
	Statistic_AddValue(Pchar, "DeadCrewTown", i);
	AddCharacterExpToSkill(Pchar, "Defence", makeint(i / 3 + 0.5)); //������ ������
	RemoveCharacterGoodsSelf(Pchar, GOOD_WEAPON, i*0.7);// �� ����� ��� �����
	i = sti(Pchar.GenQuestFort.PlayerCrew_Start) - i; // �������� � �������
	SetCrewQuantityOverMax(Pchar, i);
	AddTroopersCrewToOther(Pchar); // 09.07.05
}

bool PrepareTownBattle()
{
    ref    fortChr;
    int    mcrew, ecrew, maxcrew;
    float  rel;
    string sTemp, sCity, sNext;
    int    i, how;
    ref    nulChr;

    nulChr  = &NullCharacter;
    fortChr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));

    mcrew = GetCrewQuantity(Pchar) + GetTroopersCrewQuantity(Pchar);
    if (CheckAttribute(fortChr, "Fort.Mode") && sti(fortChr.Fort.Mode) != FORT_DEAD)
    { // ��� �������� ����� � ���� �����
        ecrew = sti(fortChr.Default.Crew.Quantity) + makeint(sti(fortChr.Default.Crew.Quantity) * (MOD_SKILL_ENEMY_RATE / 10.0));
    }
    else
    { // ���� ����
        ecrew = sti(fortChr.Default.Crew.MinQuantity) + makeint(sti(fortChr.Default.Crew.MinQuantity) * (MOD_SKILL_ENEMY_RATE / 10.0));
    }

    Pchar.GenQuestFort.PlayerCrew_Start = mcrew; // ����� ����
	// ���� ������ -->
    rel = (stf(Pchar.ship.crew.morale) - MORALE_NORMAL) / MORALE_NORMAL;
	if (rel < -0.99) rel = -0.99;
	if (rel > 0.5)  rel = 0.5 + rel / 5.0;
	mcrew = makeint(mcrew * (rel * 0.3 + 1.0));
    // ���� ������ <--
    
    // ���� ������
    ///  to_do 29.07.06 ���� �� ���� ��� �������� ���� � ���������� ���� �� ���� ��������, ����� ��� �������� ����� �����. rel = (GetCrewQuantity(Pchar) * GetCrewExp(Pchar, "Soldiers") / GetCrewExpRate()) / stf(Pchar.GenQuestFort.PlayerCrew_Start);
    // ����������, ��� ���� ������ ������ ��� ����, �� ���� ��� ��-�������.
    sCity   = fortChr.City;
    if (!CheckAttribute(nulChr, "GenQuestFort." + sCity))
    {
        Log_Info("ERROR: �� ����� ����� ������ ��� �������!!!");
        return false;
    }

    how     = sti(nulChr.GenQuestFort.(sCity).howSolder);
    maxcrew = (how - 1) * MAX_TOWN_CREW;

    if(mcrew > ecrew)
	{
        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
        if(ecrew > maxcrew)
		{
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;

    Pchar.GenQuestFort.TownCrew   = ecrew;
    Pchar.GenQuestFort.PlayerCrew = mcrew; // ������� �������

    Pchar.GenQuestFort.PlayerCrew_per_char = makefloat(stf(Pchar.GenQuestFort.PlayerCrew_Start) / stf(Pchar.GenQuestFort.PlayerCrew));

    if (CheckAttribute(pchar, "quest.Enemy_" + sCity))// ��� � ����� ����� ���� � ����������, �� ����� ��������� ��� �����
    {
        Pchar.quest.FightInTown_Next0.win_condition.l1          = "location";
	    Pchar.quest.FightInTown_Next0.win_condition.l1.location = Pchar.location;
	    Pchar.quest.FightInTown_Next0.win_condition             = "FightInTown";
        return;
    }

    // ����������
    how     = sti(nulChr.GenQuestFort.(sCity).how);
    for (i=0; i < how; i++)
    {
        sTemp = "FightInTown_Next" + i;
        sNext = "next" + i;

		Pchar.quest.(sTemp).win_condition.l1          = "location";
	    Pchar.quest.(sTemp).win_condition.l1.location = nulChr.GenQuestFort.(sCity).(sNext);
	    Pchar.quest.(sTemp).win_condition             = "FightInTown";
    }
    //#20190713-05
    Pchar.FightInTown.howMany = how - 1;
    // ���������� �� ����� ������� (���� ������� ������)
    Pchar.quest.FreeCaptureForts.win_condition.l1 = "MapEnter";
    Pchar.quest.FreeCaptureForts.win_condition    = "FreeCaptureForts";
    return true;
}

void AfterTownBattle()
{
    ref    fortChr;
    string sTemp, sCity;
    int    i, how;
    ref    nulChr;

    nulChr  = &NullCharacter;
	if (CheckAttribute(Pchar, "GenQuestFort.StartAttack" )) DeleteAttribute(Pchar, "GenQuestFort.StartAttack");	
    if (!CheckAttribute(Pchar, "GenQuestFort.fortCharacterIdx")) return; // ��� �� ����

	fortChr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    bDisableFastReload = false;
    chrDisableReloadToLocation = false;

    sCity   = fortChr.City;
    how     = sti(nulChr.GenQuestFort.(sCity).how);

    // ����������
    for (i=0; i < how; i++)
    {
        sTemp = "FightInTown_Next" + i;

		Pchar.quest.(sTemp).over          = "yes";
    }
}

void SoundInResidenceBattle()
{
	switch (rand(1))
    {
        case 0:
            PlayVoice("VOICE\" + LanguageGetLanguage() + "\soldier_arest_4.WAV");
        break;
        case 1:
            PlayVoice("VOICE\" + LanguageGetLanguage() + "\soldier_common_4.WAV");
        break;
    }
}

// ���������� ����
ref SetFantomSlaves(string group, string locator, string enemygroup)
{
    string emodel;
    ref    Cr;

    switch(rand(1))
    {
        case 0: emodel = "Pirate_1";   break;
        case 1: emodel = "Pirate_6";   break;
    /*    case 2: emodel = "man4";   break;
        case 3: emodel = "rabblack";   break;
        case 4: emodel = "rabblack_1";   break;
        case 5: emodel = "rabWhite";   break;
        case 6: emodel = "rabwhite1";   break;
        case 7: emodel = "rabblack";   break;
        case 8: emodel = "rabblack_1";   break;*/
    }

    Cr = LAi_CreateFantomCharacter(emodel, group, locator);

    if (Cr.location.locator != "")
    {
		SetFantomParam(Cr);
		string blade;
		switch (rand(3))
        {
            case 0: blade = "rabble";   break;
            case 1: blade = GetGeneratedItem("blade1"); 		break;
            case 2: blade = GetGeneratedItem("blade5");       	break;
            case 3: blade = GetGeneratedItem("topor3");   		break;
        }
		GiveItem2Character(Cr, blade);
		EquipCharacterByItem(Cr, blade);

	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //�� ���������� ������ ��� ����� � �������
	    LAi_LoginInCaptureTown(Cr, true); // ��� ������ ����
    }
    return Cr;
}

ref SetFantomDefenceForts(string group, string locator, int nation, string enemygroup)
{
    string emodel,natmod;
    ref Cr;

    natmod = NationShortName(nation);
    if(nation == PIRATE)
    {
       emodel = "Pirate_" + (rand(9) + 1);
    }
    else
    {
       emodel = "sold_" + natmod + "_" + (rand(7) + 1);
    }

    Cr = LAi_CreateFantomCharacter(emodel, group, locator);
    FaceMaker(Cr);

    if (Cr.location.locator != "")
    {
		SetFantomParam(Cr);
		Cr.nation = nation;
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //�� ���������� ������ ��� ����� � �������
	    LAi_LoginInCaptureTown(Cr, true); // ��� ������ ����
    }
    return Cr;
}

ref SetFantomOfficer(string group, string locator, int nation, string enemygroup)
{
    string emodel,natmod;
    ref Cr;

    natmod = NationShortName(nation);
    if(nation == PIRATE)
    {
       emodel = "officer_" + (rand(63) + 1);
    }
    else
    {
       emodel = "off_" + natmod + "_" + (rand(1) + 1);
    }

    Cr = LAi_CreateFantomCharacter(emodel, group, locator);
    FaceMaker(Cr);

    if (Cr.location.locator != "")
    {
		SetFantomParam(Cr);
		Cr.nation = nation;
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //�� ���������� ������ ��� ����� � �������
	    LAi_LoginInCaptureTown(Cr, true); // ��� ������ ����
    }
    return Cr;
}
//�������� �������� �� ����� �������
ref SetFantomOurAttackForts(string group, string locator)
{
    string  smodel;
    ref     CrOur;
    string  ani;
	// boal 08.01.05 ������ ������
    smodel = LAi_GetBoardingModel(GetMainCharacter(), &ani);

    CrOur = LAi_CreateFantomCharacterEx(smodel, ani, group, locator);

    if (CrOur.location.locator != "")
    {
	    SetFantomParam(CrOur);
	    LAi_group_MoveCharacter(CrOur, LAI_GROUP_PLAYER);
	    LAi_LoginInCaptureTown(CrOur, true); // ��� ������ ����
    }
    return CrOur;
}

void TWN_FreeCaptureForts() // ������ ������, ������� ����� (�� ���� ������) ��� ������ �� �����
{
	ref sld, Builder;
	
	AfterTownBattle();
    // ������ ����� ��������
    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    if (CheckAttribute(Builder, "Default"))
    {
        SetLocationCapturedState(Builder.Default, false); // �� ����� ���� ���� ��� � ����� - ����� ��� ���������� ������
		Builder.greeting = "spa_gov_common";
    }
}

void TWN_Capture_Forts()
{
    ref    sld, Builder;
    aref   aData;
    string sCap, sGroup;
    
    sGroup = "NoGroupFind"; // ���� �� ����� � Group_FindGroup
    makearef(aData, NullCharacter.Siege);
    if (CheckAttribute(aData, "nation"))
    {
        sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
        sGroup = "Sea_"+sCap+"1";
    }
    
	if (PrepareTownBattle())
    {
        sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));

		if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))  // ����� ��� ������ � ���� � ������� �������
		{
        	PlayVoice("INTERFACE\_GTBoard_0.wav");
        	if (isCityHasFort(sld.City))// ������� ����� �����
            {
            	AddCharacterExpToSkillSquadron(Pchar, "Leadership", 230);
			    AddCharacterExpToSkillSquadron(Pchar, "Sailing", 200);
			    AddCharacterExpToSkillSquadron(Pchar, "Sneak", 200);
		    }
        }
        else
        {
            DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
        }

        Builder = characterFromID(sld.City + "_Mayor");

        if (!CheckQuestAttribute("Union_with_Escadra", "Yes") || 
			!CheckAttribute(aData, "Colony") || 
			!CheckAttribute(aData, "island") || 
			Builder.City != aData.Colony) 
	    { // ����� �� ����� ���� ����� ��� ����� �������
            LAi_LoginInCaptureTown(Builder, true);
			//homo
			if (Group_FindGroup(sGroup)!= -1)
			{
                Builder = Group_GetGroupCommander(sGroup);
                LAi_LoginInCaptureTown(Builder, false); // ������ � ���� ����
            }
            return;	 // �� ����������� ���� ���� ������-�� ������ ���
		}
		else
		{   // to_do
            LAi_LoginInCaptureTown(Builder, false); // ������ ���� � ���� ����
            //homo
			Builder = Group_GetGroupCommander(sGroup);
            LAi_SetSitTypeNoGroup(Builder);
            ChangeCharacterAddressGroup(Builder, aData.Colony+"_townhall", "sit", "sit1" );
		    LAi_LoginInCaptureTown(Builder, true);
		    LAi_SetCurHPMax(Builder); // ���� �� ����
		    LAi_SetImmortal(Builder, true);
		    Builder.dialog.currentnode = "Talk_Capture_City";
		    
        	string sQuest = "LeaveTown";
            pchar.quest.(sQuest).win_condition.l1 = "location";
            pchar.quest.(sQuest).win_condition.l1.location = aData.island;
            pchar.quest.(sQuest).win_condition = "LeaveTown";
            pchar.quest.(sQuest).function = "LeaveTown";

		}
	}
}

void TWN_FightInTown()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp, snCity, sModel;
    aref aData;  //  homo
    makearef(aData, NullCharacter.Siege);   // homo
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Log_TestInfo("Cur boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    Log_TestInfo("Cur TownCrew: " + Pchar.GenQuestFort.TownCrew);
    snCity = sld.City;
    if (loadedLocation.type == "residence")
    {
		csmDA(pchar, "CSM.LootCollector.CanBeRun");
		// ������ ����� �� ������� -->
		SetCrewBackAfterBattle();
        
		if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony) //fix homo
        {
            chrDisableReloadToLocation = true;
			// �� ��� DoQuestCheckDelay("Union_with_Escadra_End", 0.5);
            return; // ������ ������ ������� - ����� ��
		}
        sTemp = sld.City;
		if (sti(sld.nation) == PIRATE) // ����� ��������    // to_do
        {
			if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp))
			{ // ��������� ������ �������
				if (sti(PChar.GenQuestFort.ResidenceQuest.(sTemp).MayorOff) == true)
				{   // �������, ��� ��� ����
                    Builder = characterFromID(sld.City + "_Mayor");
					LAi_LoginInCaptureTown(Builder, false);
                    if (!isCityHasFort(Builder.City))
		            {
		                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
		            }
					LogoffCharacter(Builder);
				}
				if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp + ".method"))
				{
                    sGlobalTemp = PChar.GenQuestFort.ResidenceQuest.(sTemp).method;
					call sGlobalTemp();
				}
				DeleteAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp);
				return;
			}
			AfterTownBattle();  // ���, ��� ��������
			//AddQuestRecord("tales_" + sld.City, "6");
			//sTemp = "Enable_Gover_" + sld.City;
            //pchar.GenQuestFort.(sTemp) = "1";

            //Pchar.GenQuestFort.MunityCharacterIdx = sld.index;
            //DoQuestCheckDelay("LaunchMunityCapture", 1.0);


            SetCaptureTownByHero(sld.City);
            Statistic_AddValue(Pchar, NationShortName(sti(sld.nation)) + "_TakeTown", 1);
        }
        else
        {  // ����� �����
			// �������� �� �������
			Builder = characterFromID(sld.City + "_Mayor");
			if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp))
			{
				if (sti(PChar.GenQuestFort.ResidenceQuest.(sTemp).MayorOff) == false)
				{
					// ������ ������ ��� ������, ���� ������ ������ - ��� �� �����
					//Builder.Dialog.Filename    = "Capture_Gover_dialog.c";
					// � �3 �� ����� ������ �����
                    Builder.dialog.CurrentNode = "CAPTURE_Main";
					LAi_SetImmortal(Builder, true);
					chrDisableReloadToLocation = true;
				}
				else
				{
                    LAi_LoginInCaptureTown(Builder, false);
                    if (!isCityHasFort(Builder.City))
		            {
		                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
		            }
					LogoffCharacter(Builder);
				}
				if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp + ".method"))
				{
                    sGlobalTemp = PChar.GenQuestFort.ResidenceQuest.(sTemp).method;
					call sGlobalTemp();
				}
				DeleteAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp);
				return;
			}
			else
			{
				//Builder.Dialog.Filename    = "Capture_Gover_dialog.c";
                if (CheckAttribute(Builder, "dialog.captureNode")) //eddy. � �� ������� ������ ��� ����.
                {
                    Builder.dialog.CurrentNode = Builder.dialog.captureNode;
					DeleteAttribute(Builder, "dialog.captureNode");
                }
				else Builder.dialog.CurrentNode = "CAPTURE_Main";
				LAi_SetImmortal(Builder, true);
				Builder.greeting = "mayor_capture";
				chrDisableReloadToLocation = true;
				if (!isCityHasFort(Builder.City))   // ������� �������
	            {
	                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
	        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
	        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
	            }
			}

            // ���������
			j = makeint(sti(Pchar.GenQuestFort.TownCrew) - sti(Pchar.GenQuestFort.PlayerCrew) / 1.6 + 0.6);
			if (j > 5) j = 5;
			if (j < 0) j = 0;
            if (j > 0)
			{
				// �������
				PChar.GenQuest.CallFunctionParam = "SoundInResidenceBattle";
				DoQuestCheckDelay("CallFunctionParam", 1.5);

				natEsc = sti(sld.nation);
				for (i = 0; i < j; i++)
	            {
					if (sti(Pchar.GenQuestFort.TownCrew) < 1) break;
					sld = SetFantomDefenceForts("goto", "", natEsc, "TOWN_BATTLE_SOLDIERS");
					SetFantomParamHunter(sld); //������ �����

	            	Pchar.GenQuestFort.TownCrew = sti(Pchar.GenQuestFort.TownCrew) - 1;
	            }
	            // ��������
	            LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
	            LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	            LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

	            LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "FightInTown_Finish");
                LAi_LocationFightDisable(&Locations[FindLocation(Pchar.location)], false);
	            LAi_SetFightMode(Pchar, true);
            }
        }
    }
    else
    {   // �� ���������� - ������ ��� ����
		if (sti(Pchar.GenQuestFort.TownCrew) > 0)
		{   // ���� ���� �����
			bDisableFastReload = true;
			// �����
			if (CheckAttribute(pchar, "quest.Enemy_" + sld.City))
            {  // ���������� �����
               natEsc = sti(sld.Default.nation);
            }
            else
            {
               natEsc = sti(sld.nation);
            }
            Pchar.GenQuestFort.FarLocator = true;
            sTemp = LAi_FindNPCLocator("rld");
            for (i = 0; i < MAX_TOWN_CREW; i++)
            {
				if (sti(Pchar.GenQuestFort.TownCrew) < 1) break;
				sld = SetFantomDefenceForts("rld", sTemp, natEsc, "TOWN_BATTLE_SOLDIERS");
				if (sld.location.locator == "") break;
            	Pchar.GenQuestFort.TownCrew = sti(Pchar.GenQuestFort.TownCrew) - 1;
            	chrDisableReloadToLocation = true; // �� ����� ���� ��������
            }
			//��������� ���������
			if (pchar.questTemp.Ascold != "Ascold_ImMummy")
			{
				for (i = 0; i < MAX_TOWN_MUSHKETER; i++)
				{				
					if (sti(Pchar.GenQuestFort.TownCrew) < 1) break;
					if(natEsc == PIRATE)
					{
						sModel = GetPirateMushketerModel();
					}
					else
					{
					   
						sModel = NationShortName(natEsc) + "_mush_" + i;
					}				
					sld = GetCharacter(NPC_GenerateCharacter("GenChar_", sModel, "man", "mushketer", 5, natEsc, 0, false));
					sld.id = "GenChar_" + sld.index;
					LAi_NoRebirthEnable(sld); //�� ���������� ������ ��� ����� � �������
					LAi_LoginInCaptureTown(sld, true); // ��� ������ ����
					SetMushketerParamFortEnemy(sld);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "TOWN_BATTLE_SOLDIERS");			    
					ChangeCharacterAddressGroup(sld, loadedLocation.id, "rld", sTemp);
					Pchar.GenQuestFort.TownCrew = sti(Pchar.GenQuestFort.TownCrew) - 1;
				}
			}

            if (chrDisableReloadToLocation)
            {
	            // ����
	            Pchar.GenQuestFort.FarLocator = false;
	            sTemp = LAi_FindNPCLocator("rld");
	            for (i = 0; i < MAX_TOWN_CREW; i++)
	            {
                    if (sti(Pchar.GenQuestFort.PlayerCrew) < 1) break;
					SetFantomOurAttackForts("rld", sTemp);
	            	Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) - 1;
	            }
				if (pchar.questTemp.Ascold != "Ascold_ImMummy")
				{
					//���� ���������
					for (i = 0; i < MAX_TOWN_MUSHKETER; i++)
					{				
						if (sti(Pchar.GenQuestFort.PlayerCrew) < 1) break;
						if(sti(pchar.nation) == PIRATE)
						{
							sModel = GetPirateMushketerModel();
						}
						else
						{
							//#20180930-02
                            sModel = NationShortName(natEsc) + "_mush_" + (i + 1);
						}
						sld = GetCharacter(NPC_GenerateCharacter("GenChar_", sModel, "man", "mushketer", 5, sti(pchar.nation), 0, false));
						sld.id = "GenChar_" + sld.index;
						LAi_NoRebirthEnable(sld); //�� ���������� ������ ��� ����� � �������
						LAi_LoginInCaptureTown(sld, true); // ��� ������ ����
						SetMushketerParamFortOur(sld);
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
						ChangeCharacterAddressGroup(sld, loadedLocation.id, "rld", sTemp);
						//Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) - 1;
					}
				}
				// ������ �������
		        if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony) //fix homo
	            {

                    natEsc = sti(aData.nation); // homo
                    //sti(Characters[GetCharacterIndex("NatCapitan_1")].nation);

	                for (i = 0; i < MAX_ESCADRA_CREW; i++) //������ 5 ����
		            {
		            	SetFantomDefenceForts("rld", sTemp, natEsc, LAI_GROUP_PLAYER);
		            }
	            }
	            Pchar.GenQuestFort.FarLocator = true;
          		// ��������
	            LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
	            LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	            LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

	            LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "FightInTown_OpenNext");

	            LAi_SetFightMode(Pchar, true);
            }
        }
    }
}

void TWN_FightInTown_OpenNext()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp, snCity;
    float fTemp;
    aref aData;  //  homo
    makearef(aData, NullCharacter.Siege);   // homo
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
	snCity = sld.City;
    if (CheckAttribute(pchar, "quest.Enemy_" + sld.City))
    {// ����� ���������� ������
        TWN_End_Siege_Any(sld.City);
        AfterTownBattle();  // ���, ��� ��������
        SetLocationCapturedState(sld.Default, false);
    }
    //#20190713-05
    Pchar.FightInTown.howMany = sti(Pchar.FightInTown.howMany) - 1;
    if(sti(Pchar.FightInTown.howMany) <= 0) {
        LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
        DeleteAttribute(Pchar, "FightInTown");
    }
    chrDisableReloadToLocation = false;
    LAi_SetFightMode(Pchar, false);
    Log_Info("���� ���������� ���������! ���� ��������.");
    PlaySound("interface\door_locked.wav");
    // ������� ����� ��������
    Log_TestInfo("Old boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    for(i = 0; i < LAi_numloginedcharacters; i++)
	{
		j = LAi_loginedcharacters[i];
		if(j >= 0)
		{
			if(j != GetMainCharacterIndex())
			{
				sld = &Characters[j];
				if(LAi_IsDead(sld) == false && !IsOfficer(sld) && sld.model.animation != "mushketer") // �� ����� ������� ��� ��������
				{
					if (sld.chr_ai.group == LAI_GROUP_PLAYER)
					{
						Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) + 1;
					}
				}
			}
		}
	}
	if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony ) //fix homo
    {
        Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) - MAX_ESCADRA_CREW; //������ 5 ����
    }
    Log_TestInfo("New boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    Log_TestInfo("New TownCrew: " + Pchar.GenQuestFort.TownCrew);
    // ������ ����� �� ������� -->
	fTemp = stf(Pchar.GenQuestFort.PlayerCrew) * stf(Pchar.GenQuestFort.PlayerCrew_per_char); // �����
	i     = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp) /1.5 + 0.5); // �����
	// ��� ����� ���������� RemoveCharacterGoodsSelf(Pchar, GOOD_WEAPON, i);
	i = sti(Pchar.GenQuestFort.PlayerCrew_Start) - i; // �������� � �������
	SetCrewQuantityOverMax(Pchar, i);
	// ������ ����� �� ������� <--
	if (csmCA(pchar, "CSM.LootCollector.Enable") && loadedLocation.type != "residence")
	{
		pchar.CSM.LootCollector.CanBeRun = true;
		csmLootCollector();
	}
}

void TWN_Residence_Captured_Any()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	Lai_SetPlayerType(pchar);
    DoQuestCheckDelay("CapturedToOurCity", 1.5);

    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    if (Builder.location.group == "sit")
    {// ����� ���!
        LAi_SetHuberStayTypeNoGroup(Builder);
		PlaceCharacter(Builder, "goto", pchar.location);
    }
    sld = GetOurSailor("OurSailorForArest");
    sld.location = "none"; //fix
    LAi_LoginInCaptureTown(sld, true);

    if (PlaceCharacter(sld, "reload", pchar.location) != "")
    {
        chrDisableReloadToLocation = true; // ���� �� �� ������ �� �����
    }
    else
    {
        Builder.location = "none";
    }

    LAi_SetActorType(sld);
    LAi_ActorFollow(sld, Builder, "Residence_Captured_Any_02", 7.0);
}

void TWN_Residence_Captured_Any_02()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	sTemp = "reload1"; //LAi_FindRandomLocator("reload");
	LAi_ActorRunToLocation(characterFromID("OurSailorForArest"), "reload", sTemp, "none", "", "", "", 7.0);

    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    LAi_SetActorType(Builder);
    if (CheckAttribute(sld, "Default.Prison"))
    {  // ���� �����
    	LAi_ActorRunToLocation(Builder, "reload", sTemp, sld.Default.Prison, "goto", "goto9", "Back_Mayor_Type", 7.0);  // to_do
    }
    else
    {
        LAi_ActorRunToLocation(Builder, "reload", sTemp, "none", "", "", "Back_Mayor_Type", 7.0);
    }
}

void TWN_Back_Mayor_Type()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    chrDisableReloadToLocation = false;
	LAi_SetHuberStayTypeNoGroup(Builder);
    LAi_SetImmortal(Builder, false);
    if (!CheckAttribute(sld, "Default.Prison"))
    { // ��� �������� �����
    }
}

void TWN_ExitForPay() // ��� ���� ����� - �������� �������
{
    ref sld, Builder;
    
    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    LAi_SetImmortal(Builder, false);
    LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
    FadeOutMusic(3);
    PlayStereoOGG("music_ship_victory");

    int iTest;
    iTest = FindColony(sld.City); // �����
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	chrDisableReloadToLocation = false;
	ClearIslandShips(sld.City); // ������ ������� � �����, ������
	int iStat = (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "hol_GrabbingTown", 0));
	if(iStat >= 5) UnlockAchievement("AchCityRobbery", 1);
	if(iStat >= 10) UnlockAchievement("AchCityRobbery", 2);
	if(iStat >= 15) UnlockAchievement("AchCityRobbery", 3);
	int nBooty;
	if (CheckAttribute(Pchar, "HalfOfPaymentByCity"))
	{
        nBooty = 700;
		DeleteAttribute(Pchar, "HalfOfPaymentByCity");
		SetNull2StoreManPart(rColony, 6.0);
	}
	else
	{
        nBooty = 2000;
		SetNull2StoreManPart(rColony, 3.0);
	}
	if (CheckAttribute(rColony, "FortValue"))
	{
		AddMoneyToCharacter(pchar, (sti(rColony.FortValue) + rand(10)) * nBooty);
	}
	else
	{
	    AddMoneyToCharacter(pchar, (20 + rand(10)) * nBooty);
	}
	LaunchColonyCapture(rColony);
	DeleteAttribute(rColony, "AlreadyGen");
}

//��� ����� ������ ������ �����
// SetAllTownNation ������
void SetCaptureTownByNation(string sColony, int iNation)
{
	ref  rChar;
	int  j;
	int iColony = FindColony(sColony);

    // ��������
    pchar.GenQuest.CapturedCity  = sColony;
	pchar.GenQuest.CaptureNation = iNation;
	
    string sGroup;
	sGroup = GetNationNameByType(iNation) + "_CITIZENS";
	
    for (j=0; j< MAX_CHARACTERS; j++)
    {
        rChar = GetCharacter(j);

        if(CheckAttribute(rChar, "city") && rChar.City == sColony)
        {
            if (CheckAttribute(rChar, "CityType")) // ������
        	{
        	    rChar.LifeDay = 0; // ����
        	}
        	rChar.nation = iNation;
        	LAi_group_MoveCharacter(rChar, sGroup);
			if (rChar.id == (sColony + "_Mayor"))
			{
			    // ��� ����
	          	if (iNation != PIRATE)
			    {
			        rChar.Default.nation = iNation; // ��� ����� ����� ����� ������� � ������� ���������
			    }
	        	SetTownMayor(rChar, iNation); // ����� ���
	        }
	        if (rChar.id == (sColony + " Fort Commander"))
			{
			    // �������� ���������
	          	if (iNation != PIRATE)
			    {
			        rChar.Default.nation = iNation; // ��� ����� ����� ����� ������� � ������� ���������
			    }
			    SetTownOfficForts(rChar, iNation);
	        }
        }
    }
    if (!CheckAttribute(Pchar, "questTemp.DontNullDeposit"))
    {
	    SetNull2Deposit(sColony); // �����, ���� �����  �� ��
	    SetNull2StoreMan(&Colonies[iColony]); // ����� ������� ��� ������� ������ ��������
    }
    else
    {
        DeleteAttribute(PChar, "questTemp.DontNullDeposit");
    }
    ClearIslandShips(sColony); // ������ ������� � �����, ������
	// ���� �� �����
	sColony = sColony + "_town";
	worldMap.labels.(sColony).icon = iNation;
	AddFortNation(sti(Colonies[iColony].nation), -1);
	j = sti(Colonies[iColony].nation);
 	AddFortNation(iNation, 1);
    Colonies[iColony].nation = iNation;
    Move_Govenour_Nation(j); // ���������� ������ �����, ������� ���� ���� ����� ���� ���
    // ������� ����������, ���� ���
	if (CheckAttribute(&Colonies[iColony], "OfficerIdx"))
	{
	    rChar = GetCharacter(sti(Colonies[iColony].OfficerIdx));
	    rChar.location = "none";
	    rChar.LifeDay = 0;
	    DeleteAttribute(&Colonies[iColony], "OfficerIdx");
	}
	if (sti(Colonies[iColony].HeroOwn) == true)
	{
    	Colonies[iColony].HeroOwn = false; // ���, ��� �� ��� �����
    	//  �� -->
    	sGroup =  GetNationNameByType(iNation);
		ReOpenQuestHeader("Gen_CityCapture");
        AddQuestRecord("Gen_CityCapture", "t4");
		AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + Colonies[iColony].id));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sGroup + "Gen"));
		//  �� <--
    }
 	if (iNation != PIRATE)
 	{
    	Colonies[iColony].isBought = false; // ���� �����, �� �� ���������
    }
    SaveCurrentNpcQuestDateParam(&Colonies[iColony], "CaptureDate");
}


//���� �� �����������
//void SetAllTownOurCity(ref FortCrefM) - ������ � ���
void SetCaptureTownByHero(string sColony)
{
    ref  rChar;
	int  j;
	int iColony = FindColony(sColony);
    int iNation = PIRATE;

    // ��������
    pchar.GenQuest.CapturedCity  = sColony;
	pchar.GenQuest.CaptureNation = iNation;
	
    string sGroup;
	sGroup = LAI_GROUP_PLAYER_OWN;

    for (j=0; j< MAX_CHARACTERS; j++)
    {
        rChar = GetCharacter(j);

        if(CheckAttribute(rChar, "city") && rChar.City == sColony)
        {
            if (rChar.id != (sColony + "_Mayor"))  // ��� � ������, ��� �� �������
			{
			    if (CheckAttribute(rChar, "CityType")) // ������
	        	{
	        	    rChar.LifeDay = 0; // ����
	        	}
	        	rChar.nation = iNation;
	        	LAi_group_MoveCharacter(rChar, sGroup);

		        if (rChar.id == (sColony + " Fort Commander"))
				{
				    SetTownOurOfficForts(rChar); // ������ � ���������
		        }
	        }
			else
			{
			    LAi_group_MoveCharacter(rChar, sGroup);
			}
        }
    }
    ClearIslandShips(sColony); // ������ ������� � �����, ������
	// ���� �� �����
	sColony = sColony + "_town";
	worldMap.labels.(sColony).icon = iNation;
	AddFortNation(sti(Colonies[iColony].nation), -1);
	j = sti(Colonies[iColony].nation);
 	AddFortNation(iNation, 1);
    Colonies[iColony].nation = iNation;
    Move_Govenour_Nation(j); // ���������� ������ �����, ������� ���� ���� ����� ���� ���
    Colonies[iColony].HeroOwn = true;
    // ������������� ������ �� ������, �� ����� �� ������ ���� ��
    SaveCurrentNpcQuestDateParam(&Colonies[iColony], "CaptureDate");
}


//������ ������ ����
void SetTownMayor(ref Ch, int natGover)
{
    string rmodel;

	if (natGover == PIRATE)
	{
	    // ����� ����� ������ - � ��� ������ �����, ���� ������ �� �����
        rmodel = Ch.model;
	}
	else
	{
	    switch(rand(11))
        {
            case 0: rmodel = "usurer_8";   break;
            case 1: rmodel = "usurer_7";   break;
            case 2: rmodel = "usurer_6";   break;
            case 3: rmodel = "usurer_4";   break;
            case 4: rmodel = "usurer_3";   break;
            case 5: rmodel = "usurer_2";   break;
            case 6: rmodel = "trader_8";   break;
            case 7: rmodel = "trader_3";   break;
            case 8: rmodel = "trader_16";   break;
            case 9: rmodel = "trader_11";   break;
            case 10: rmodel = "trader_10";   break;
            case 11: rmodel = "shipowner_13";   break;
        }
	}

    if (natGover != PIRATE) // ��� ����� ��� � ����� ��� � ����� ������... ������ ������ + ��������.
    {
 		// eddy, �� ������� ����� ������ �����
		if (!CheckAttribute(Ch, "name"))
		{       
			SetRandomNameToCharacter(Ch);
		}
        Ch.model = rmodel;
        FaceMaker(Ch);
        Ch.quest.meeting = 0; // ���� ������ ��� ����������
        if (!CheckAttribute(pchar, "questTemp.DontSetNewDialogToMayor"))
        {
            Ch.dialog.currentnode = "First time"; // ������ �� ����
        }
		// �� ��� � ����� - �� �����
		LAi_SetCurHPMax(Ch); // �����������, ���� ����������
		ReturnMayorPosition(Ch);
		LAi_LoginInCaptureTown(Ch, false);
    }
}
// ���� �� �����, ���� ��� � ������ ��� �����
void ReturnMayorPosition(ref Ch)
{
	Ch.location = Ch.City + "_townhall";
	Ch.location.group   = "sit";
	Ch.location.locator = "sit1";
	LAi_SetHuberTypeNoGroup(Ch);
}

//�������� ���� � �����  (�� ��������, � ������ ������ �� �����)
int AddFortNation(int nation,int fort)
{
	int newfort = sti(Nations[nation].fort) + fort;
	if(newfort<0) newfort=0;
	Nations[nation].fort = newfort;
	return newfort;
}

// boal ����������� ����������� -->
void Move_Govenour()
{
    int iNation = rand(4);

    if (bWorldAlivePause) return;

    while (iNation == PIRATE)
    {
        iNation = rand(4);
    }
    // ����� �����  <--
    Move_Govenour_Nation(iNation);
}
void Move_Govenour_Nation(int iNation)
{
    ref rChar;
    if (bWorldAlivePause) return;

    if (iNation != PIRATE)
    {
    	rChar = CharacterFromID(NationShortName(iNation)+"_guber");  // �����

		if (CheckAttribute(rChar, "notMoveAble")) return; //��������� ������ ���� ����������� �� �������

        ref ch;
    	int i, iChar;
        int storeGover[40];
        int howGover = 0;

        for (i=0; i<MAX_COLONIES; i++)
		{
			if (colonies[i].nation == "none") continue; // ����������

			// �������� �������� �� �������, � ��� ��� ������, ����� �� ���������?
			if (CheckAttribute(&colonies[i], "HasNoFort"))  continue;
			
			// �������� ������� ����� �������
			iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
			if (iChar != -1)
			{   // ��� ����, ������ ���� ����������
			    if (sti(colonies[i].nation) == iNation) // ���� ����� �����, �� ��� �� � �����
			    {
			        storeGover[howGover] = i; // ������ ������
                	howGover++;
			    }
	        }
		}

        if (howGover > 0) // ����� ������ ������ - ���� ����� �������
        {
			i = storeGover[rand(howGover-1)];
            SetGovenourToCity(iNation, colonies[i].id);
        }
        else
        {// ����� ���� - ������� � ������� ������ ���, ������ ������
            if (CheckAttribute(rChar, "CityToStay")) // ��� ���
			{
		        i = GetCharacterIndex(rChar.CityToStay + "_Mayor");  // ������� ���� �� �����
		        if (characters[i].location == rChar.location)
		        {   //���� �� ��� � ����������, � �� � ������
		            characters[i].location.group = "sit";
					characters[i].location.locator = "sit1";
					LAi_SetHuberTypeNoGroup(&characters[i]);
				}
			}
			rChar.location = "none";
			DeleteAttribute(rChar, "CityToStay");
        }
    }
}
// ����� ��� �������� � ��������� ������ ������� � � ������ ����
void SetGovenourToCity(int iNation, string sCity)
{
    ref     rChar;
    int     iChar, i2;
    
    rChar = CharacterFromID(NationShortName(iNation) + "_guber");  // �����
    
    iChar = GetCharacterIndex(sCity + "_Mayor");  // ����
	
	if (CheckAttribute(rChar, "CityToStay")) // ��� ���
	{
        i2 = GetCharacterIndex(rChar.CityToStay + "_Mayor");  // ������� ���� �� �����
        if (characters[i2].location == rChar.location)
        {   //���� �� ��� � ����������, � �� � ������
            characters[i2].location.group = "sit";
			characters[i2].location.locator = "sit1";
			LAi_SetHuberTypeNoGroup(&characters[i2]);
		}
	}
 	rChar.location = characters[iChar].location;
	rChar.CityToStay = characters[iChar].City;
	rChar.location.group = "sit";
	rChar.location.locator = "sit1";
	LAi_SetHuberTypeNoGroup(rChar);
	
	characters[iChar].location.group = "goto";
	characters[iChar].location.locator = "governor1";
	LAi_SetHuberStayTypeNoGroup(&characters[iChar]);
}
// boal ����������� ����������� <--

//������ ������ ���������� ����� � ��������� � ���
void SetTownOurOfficForts(ref ChOff)
{
    // ���������� ������
	if (CheckAttribute(ChOff, "Mayor")) return; // ��� ���� �������� (����������� ����)

    SetCaptanModelByEncType(ChOff, "pirate");
    SetCharacterRelationAsOtherCharacter(sti(ChOff.index), GetMainCharacterIndex());
    SetCharacterRelation(sti(ChOff.index),GetMainCharacterIndex(),RELATION_FRIEND);
    UpdateRelations();
}

//������ ������ ���������� �����
void SetTownOfficForts(ref ChOf, int fnat)
{
	// ���������� ������
	if (CheckAttribute(ChOf, "Mayor")) return; // ��� ���� �������� (����������� ����)

    SetCaptanModelByEncType(ChOf, "war");
    // ��������� ��� � ������ �����
	if (fnat != PIRATE)
	{
	    ref govenour = CharacterFromID(NationShortName(fnat)+"_guber"); // ������ �� ����������� ������ ����.
	    SetCharacterRelationAsOtherCharacter(sti(ChOf.index), sti(govenour.index));
    }
    else
    {
        SetCharacterRelationAsOtherCharacter(sti(ChOf.index), -1);
    }
    /*   to_do ��� ����� ������������
    */
}
///////////////////////////////////////////////////////////   ����� ������ //////////////////////////////////
//  ����������
// "Attack_Fort_" + city - ������ �����, ������, ���������� TWN_Siege_Any
// "End_Siege_" + city; - ���������� �� �������� �������, ����������  TWN_End_Siege_Any, ��� ���������� ���, ����� �����
// "LandBattleStart_For_" + city - �� �������, ������ ���������� ������ � �����
//  "Enemy_" + city - ����� �� ������ �����, ����� � �� �������, �����  TWN_Enemy_Any
// ����� ����� �������
void TWN_Siege_Any(string city)
{
    ref    sld, rCap;
    int    i, iDay;
    string sTemp, sGroup, sCapId, sAttr;

    city = PChar.Quest.(city).CityId; // �������� �����
    
    if (!isCityHasFort(city)) // ���������� �����
    {
        TWN_SiegeLand_Any(city);
    }
    else
    {
	    sld = GetFortCommander(city);

	    Log_Info("��� ����� " + GetCityName(city) + " � �����!");

	    sTemp = "Enemy_" + city;
	    iDay = 9 + rand(15);
	    SetTimerCondition(sTemp, 0, 0, iDay, false);
	    PChar.Quest.(sTemp).CityId   = city;
		PChar.Quest.(sTemp).function = "TWN_Enemy_Any";

		//  �� -->
		sTemp =  GetNationNameByType(sti(sld.Default.nation));
		ReOpenQuestHeader("Gen_CityCapture");
	    AddQuestRecord("Gen_CityCapture", "t5");
		AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
		AddQuestUserData("Gen_CityCapture", "sDay", FindRussianDaysString(iDay));
		//  �� <--

        sGroup = city + "Squadron";
	    Group_FindOrCreateGroup(sGroup);
	    sCapId = city + "CapSquadron_";
	    sTemp = "End_Siege_" + city;
        for (i = 1; i <= 6; i++)
	    {
	        rCap = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, sti(sld.Default.nation), iDay + 2, true));

	        SetShipSquadron(rCap);
	        SetFantomParamHunter(rCap); //������ �����
	        SetCaptanModelByEncType(rCap, "war");
	        Group_AddCharacter(sGroup, sCapId + i);
	        rCap.AlwaysEnemy        = true; //������ ����
	        SetCharacterRelationBoth(sti(rCap.index), GetMainCharacterIndex(), RELATION_ENEMY);
	        // ����������
	        sAttr = "l" + i;
			Pchar.quest.(sTemp).win_condition.(sAttr) = "NPC_Death";
	        Pchar.quest.(sTemp).win_condition.(sAttr).character = sCapId + i;
	        
	        SetRandGeraldSail(rCap, sti(rCap.Nation));
	    }
        Pchar.quest.(sTemp).win_condition = sTemp;
	    PChar.Quest.(sTemp).CityId   = city;
		PChar.Quest.(sTemp).function = "TWN_End_Siege_Any";
		
	    Group_SetGroupCommander(sGroup, sCapId + "1");
	    Group_SetAddress(sGroup, sld.Default.Island, "Quest_ships", "reload_fort1_siege");
	    Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	    
	    ClearIslandShips(city); // ������ ������� � �����
	    makeref(rCap, Colonies[FindColony(city)]);
    	rCap.DontSetShipInPort = true;
    	
    	if (!bQuestCheckProcessFreeze) // ����� ��������
		{
	        Pchar.GenQuestFort.ColonySiegeId   = city;
	        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
	        Pchar.GenQuestFort.ColonySiegeTime = iDay;
			PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
			DoQuestCheckDelay("CallFunctionParam", 1.5);
		}
	}
}
void SetShipSquadron(ref rChar)
{
    int SiegeShips, hcrew;

    SiegeShips = SHIP_FRIGATE + rand(makeint(SHIP_MANOWAR - SHIP_FRIGATE));

    SetRandomNameToCharacter(rChar);
    SetRandomNameToShip(rChar);
    rChar.Ship.Type = GenerateShipExt(SiegeShips, 1, rChar);
    SetBaseShipData(rChar);
    hcrew = GetMaxCrewQuantity(rChar);
    SetCrewQuantity(rChar, hcrew);

    DeleteAttribute(rChar,"ship.sails");
    DeleteAttribute(rChar,"ship.masts");
    DeleteAttribute(rChar,"ship.blots");

    Fantom_SetCannons(rChar, "war");
    Fantom_SetBalls(rChar, "war");
    Fantom_SetGoods(rChar, "war");
}
// ��������
void TWN_End_Siege_Any(string city)
{
    ref    sld, rColony;
    int    i;
    string sTemp, sAttr;

	if (CheckAttribute(PChar, "Quest." + city +".CityId")) // ��� ����������
	{
    	city = PChar.Quest.(city).CityId; // �������� �����
    } // ����� ����������, � ��� ����� ����� �� �����

	sld = GetFortCommander(city);

 	//  �� -->
	sTemp =  GetNationNameByType(sti(sld.Default.nation));
	ReOpenQuestHeader("Gen_CityCapture");
	if (isCityHasFort(city)) // �������� �����
    {
    	// ����� ��������� - ���� �������
        AddQuestRecord("Gen_CityCapture", "t6");
        makeref(rColony, Colonies[FindColony(city)]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //���������� �����
		DeleteAttribute(rColony, "AlreadyGen");
	}
	else
	{
    	AddQuestRecord("Gen_CityCapture", "t6_1");
    }
	AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
	AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
	//  �� <--
	
	sTemp   = "Enemy_" + city;
    Pchar.quest.(sTemp).over = "yes";

    sTemp = "Attack_Fort_" + city;
    SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_Siege_Any";
			
    Log_Info("����� �����!");
}
///////////////////////////////
// ���������� �����
void TWN_SiegeLand_Any(string city)
{
    ref    sld;
    int    i;
    string sTemp, sAttr;

    sld = GetFortCommander(city);

    Log_Info("��� ����� " + GetCityName(city) + " � �����!");

    sTemp = "Enemy_" + city;
    i = 9 + rand(15);
    SetTimerCondition(sTemp, 0, 0, i, false);
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_Enemy_Any";
	
	//  �� -->
	sTemp =  GetNationNameByType(sti(sld.Default.nation));
	ReOpenQuestHeader("Gen_CityCapture");
    AddQuestRecord("Gen_CityCapture", "t5_1");
	AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
	AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
	AddQuestUserData("Gen_CityCapture", "sDay", FindRussianDaysString(i));
	//  �� <--
	
	if (!bQuestCheckProcessFreeze) // ����� ��������
	{
        Pchar.GenQuestFort.ColonySiegeId   = city;
        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
        Pchar.GenQuestFort.ColonySiegeTime = i;
        
        PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
		DoQuestCheckDelay("CallFunctionParam", 1.5);
	}
			
    sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).win_condition.l1          = "location";
    Pchar.quest.(sTemp).win_condition.l1.location = sld.Default.BoardLocation;
    Pchar.quest.(sTemp).win_condition             = sTemp;
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_LandBattleStart_For_Any";
}

// ������ ����� ������ �� ���� ����� ������
void  TWN_LandBattleStart_For_Any(string city)
{
    ref    sld;
    string sTemp;

    city = PChar.Quest.(city).CityId; // �������� �����
    
    sld = GetFortCommander(city);

	Pchar.GenQuestFort.fortCharacterIdx = sld.index;

    DeleteQuestAttribute("Union_with_Escadra"); // to_do

    SetLocationCapturedState(sld.Default, true);

    if (CheckAttribute(pchar, "quest.Enemy_" + city))// ��� � �����
    {
        DoQuestCheckDelay("Capture_Town_Siege", 0.1); // ������ � ����� ��� ����!
    }
    else
    {
        DoQuestCheckDelay("Capture_Forts", 0.1); // �����
    }
}
// ��� ��������� �����
void TWN_Enemy_Any(string city)
{
    ref    sld, rColony;
    int    i;
    string sTemp, sAttr;

    city = PChar.Quest.(city).CityId; // �������� �����
    sld = GetFortCommander(city);

    sTemp = "End_Siege_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "Attack_Fort_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).over               = "yes";

	// �������������� �� �����
	// ��� � CreateHabitues �����

    SetCaptureTownByNation(city, sti(sld.Default.nation));
    // �������� �������� ���� �� �������, �����-�� ����� ����� ������ � �����

    if (!bQuestCheckProcessFreeze) // ����� ��������
	{
        Pchar.GenQuestFort.ColonySiegeId     = city;
        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
        Pchar.GenQuestFort.ColonySiegeEnd    = true;
		PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
		DoQuestCheckDelay("CallFunctionParam", 2.0);
	}
	Log_Info("��� ����� " + GetCityName(city) + " ��������.");
	makeref(rColony, Colonies[FindColony(city)]);
    DeleteAttribute(rColony, "DontSetShipInPort"); //���������� �����
	DeleteAttribute(rColony, "AlreadyGen");
}

void TWN_RealeseForMoney(string city, bool _agent)
{
    string  sTemp;
    ref     sld, rColony;
    
	sTemp = "Attack_Fort_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "End_Siege_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).over               = "yes";
    sTemp   = "Enemy_" + city;
    Pchar.quest.(sTemp).over = "yes";
    // ���� ������� ����, �� ��� �������� ��� �� ����� ����� � �������
    
	makeref(rColony, Colonies[FindColony(city)]);
	rColony.isBought = true;
	DeleteAttribute(rColony, "DontSetShipInPort"); //���������� �����
	DeleteAttribute(rColony, "AlreadyGen");
	
	if (_agent)
	{
		sld = GetFortCommander(city);
		//  �� -->
		sTemp =  GetNationNameByType(sti(sld.Default.nation));
		ReOpenQuestHeader("Gen_CityCapture");
	    AddQuestRecord("Gen_CityCapture", "t7");
		AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
		//  �� <--

		AddMoneyToCharacter(pchar, -TWN_CityCost(city));
	}
}

bool isHeroOwnCity(bool _isBoughtCare) // _isBoughtCare - true, �� ��������� �����������, ���� ���, �� �����, ������ ����� �� (��� ��������)
{
	int i;

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (sti(colonies[i].HeroOwn) == true)
		{
			if (!_isBoughtCare || sti(colonies[i].isBought) == false) return true;
		}
	}
	return false;
}

int TWN_CityCost(string city)
{
    ref     rColony;
    
	makeref(rColony, Colonies[FindColony(city)]);
	int money =  1000;
	if (CheckAttribute(rColony, "FortValue"))
	{
		money = (sti(rColony.FortValue) * 50000);
	}
	else
	{
	    money = (25 * 50000);
	}
	return money;
}
