#include "Weather\WhrInit.c"

extern InitWeather();
string s4()
{
    return "3";
}

void locs()
{
	ref loc = loadedlocation;
	if(IsEntity(loc) != true) return;
	string locatorGroupName = "locators.reload";
	if(CheckAttribute(loadedLocation, locatorGroupName) == 0) return;
	aref locatorGroup;
	makearef(locatorGroup, loc.(locatorGroupName));
	int locatorCount = GetAttributesNum(locatorGroup);
	if(locatorCount <= 0) return;
	string locatorName, locatorType;
	int locatorNameLength;

	for(int i = 0; i < locatorCount; i++)
	{
		aref locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		locatorNameLength = strlen(locatorName);
		locatorType = strcut(locatorName, 0, locatorNameLength-3);
trace(locatorName);
		trace("Loc x " + locator.x);
trace("Loc y " + locator.y);
trace("Loc z " + locator.z);
	}
}

void ExecuteConsole()
{
    Log_SetStringToLog("screen_x " + Render.screen_x);
    Log_SetStringToLog("screen_y " + Render.screen_y);
    return;
    // ref rRealShip2 = GetRealShip(sti(characters[457].Ship.Type));
    // Log_SetStringToLog("Success1 " + rRealShip2.name);

    // return;
    pchar.Ship.Type = GenerateShip(SHIP_DUTCHLINESHIP, 0);
    //ref rRealShip2 = GetRealShip(sti(pchar.Ship.Type));
    //rRealShip2.ship.upgrades.hull = 1; //through 7
    SetCharacterPerk(pchar, "FlagPers");
    return;

    ref mychr = characterFromID("GenChar_452");


    Log_SetStringToLog("Success1 " + mychr.name);
    Log_SetStringToLog("Success1 " + mychr.nation);
    return;
    Duel_Prepare_Fight();
    return;
    SendMessage(loadedLocation, "lsl", MSG_LOCATION_EX_MSG, "AddCrabs", -1);
    return;
    LocatorReloadEnterDisable("BridgeTown_town", "houseS3", false);
    return;
    aref tref;
    int ltst, ltst2;
    float fDelaytime = 5.0;
    //string endPic = rndGameOverScreens("land", &fDelayTime);

    Log_SetStringToLog("Success1 " + characters[1].Ship.Type);
    //Log_SetStringToLog("Success2 " + fDelayTime);

    return;

    ltst = CheckAttributeN(pchar, "blah");
    Log_SetStringToLog("Successa " + ltst);
    pchar.blah = 44;
    pchar.blah.two = 22;
    ltst = CheckAttributeN(pchar, "blah");
    Log_SetStringToLog("Successb " + ltst);
     ltst2 = CheckAttributeN(pchar, "blah.two");
    Log_SetStringToLog("Successbb " + ltst2);
    tref = GetAttributeN(pchar,ltst-1);

    Log_SetStringToLog("Successc " + GetAttributeValue(tref));
    ltst2 = DeleteAttributeN(pchar, ltst);
    Log_SetStringToLog("Successd " + ltst2);

    ltst = CheckAttributeN(pchar, "blah");
    Log_SetStringToLog("Successe " + ltst);


    ltst = CheckAttributeN(pchar, "ship.type");
    Log_SetStringToLog("Successa " + pchar.ship.type);
    Log_SetStringToLog("Successb " + ltst);
    makearef(tref, pchar.ship);
    tref = GetAttributeN(tref,ltst-1);

    Log_SetStringToLog("Successc " + GetAttributeValue(tref));
    return;

    bool mytestdel;
    mytestdel = DeleteAttribute(pchar, "blahh");
    Log_SetStringToLog("Success " + mytestdel);
    pchar.blahh = 22;
    Log_SetStringToLog("Again");
     mytestdel = DeleteAttribute(pchar, "blahh2");
     Log_SetStringToLog("Success " + mytestdel);

      mytestdel = DeleteAttribute(pchar, "blahh");
    Log_SetStringToLog("Success " + mytestdel);
    return;

    Group_SetGroupCommander(PLAYER_GROUP, Characters[nMainCharacterIndex].id);
    Log_SetStringToLog("Success " + characters[350].id);
    Log_SetStringToLog("Success " + characters[350].name);
    return;

    for(n=0; n<ITEMS_QUANTITY; n++)
	{
		//makeref(itm,Items[n]);
		if(Items[n].id == "item"+(n+1)){
            Log_SetStringToLog("Success " + n);
            break;
		}
	}

	return;
    for(int kk = 0; kk < 15; kk++)
        trace("rnd " + rand(3));
    return;
    pchar.Ship.Type = GenerateShip(SHIP_RESOLUTION, 0);
    ref rRealShip = GetRealShip(sti(pchar.Ship.Type));
    rRealShip.ship.upgrades.hull = 2;


        return;
    pchar.Ship.Type = GenerateShip(SHIP_RESOLUTION, 0);

    return;

    ref chr;
    string sLocator = Island_FindRandomLocator("Tortuga", "Quest_Ships");
    Log_SetStringToLog("Success " + sLocator);
    return;
    GiveItem2Character(pchar, "bookcrunch_3");
    GiveItem2Character(pchar, "bookstealth_2");
    //chr = characterFromID("Carrier_481");

	//Log_SetStringToLog("Success " + chr.firstLoc);

		return;
    pchar.perks.list.FlagPor = "1";
    return;
    object modlist;
    ref modlistref;
    int iOptCount = 0;
    makeref(modlistref, modlist);

    string sTest = GetSaveDirectory() + PlayerProfile.name+"\options\mod_list";
    if(false) {
        modlist.realistic_spyglasses = true;
        modlist.test2 = 5;
        SaveVariable(sTest, &modlist);
    }
    else {
        LoadVariable(sTest, &modlist);
        iOptCount = GetAttributesNum(modlistref);
    }
    Log_SetStringToLog("Success " + iOptCount + ", " + modlist.test2);
    return;

	int nn;
	//SetTipsEnabled(true);
	//return;
    MOD_SKILL_ENEMY_RATE = 1;
	//RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	Log_SetStringToLog("Success " + IsEntity(&objISpyGlass));
	return;
	//InitBio();

	chr = characterFromID("spaSiegeCap_7");
		trace("Dead process " + chr.id);
    trace("Dead process2 " + chr.chr_ai.hp);
    trace("Dead process3 " + chr.location);
    trace("Dead process4 " + chr.location.group);
    trace("Dead process5 " + chr.location.locator);


	return;
    //ref sChk = characterFromId("Narval_head");
    //int nNarv = GetCharacterIndex("Narval_head");
    Log_SetStringToLog("Success " + pchar.questTemp.LSC.Armo);
    return;
    SendMessage(&characters[1], "lsf", MSG_CHARACTER_MULTANISPEED, "swim", 4.0);
    return;
     DeleteAttribute(PChar, "GenQuest.PGG_Quest");
     return;
    //TakeNItems(pchar,"pistol59",30);
    //int ntestbl = sti("");
    string s1 = "is";
    string s2 = "a";
    string s3 = "b";
    s1 += GetCharacterIndex("PSHero_115") + XI_ConvertString("You are overloaded");
    //SendMessage(&characters[1], "lsf", MSG_CHARACTER_SETANISPEED, "run", 9.0);
    Log_SetStringToLog("Success " + pchar.GenQuest.PGG_Quest.Stage);
    return;
    pchar.nation = FRANCE;
    pchar.basenation = FRANCE;
    GiveNationLicence(2, 30);
    return;
    pchar.perks.FreePoints_self = 35;
     Log_SetStringToLog("Success ");
     return;
    ref mytestchar = characterFromID("fenc_941");
    bool bme = CheckAttribute(&RealShips[171], "EmblemedSails");//CheckAttribute(&ShipsTypes[SHIP_GREYHOUND], "EmblemedSails");
    string sem = RealShips[171].EmblemedSails;
    //CreateBrothels(loadedLocation);
    Log_SetStringToLog("Success " + bme + ", " + sem + ", " + RealShips[171].basetype);
    Log_SetStringToLog("Success " + ShipsTypes[109].name + ", " + ShipsTypes[SHIP_CRIMSONBLOOD].EmblemedSails.normalTex);
    return;
    pchar.basenation = FRANCE;
    pchar.nation = FRANCE;
    doMargarita();
    return;
    pchar.Ship.Type = GenerateShip(SHIP_SOLEILROYAL, 0);
    AddCharacterGoodsSimple(pchar, GOOD_WINE, 20);
    Log_SetStringToLog("Success ");
    return;
    //Test swap with my officer, PSHero_115
    int testChar = GetCharacterIndex("PSHero_115"); //Get my officer by id
    int oldMain = nMainCharacterIndex;
    characters[testChar].isHiding = false;
    int ldLoc = FindLoadedLocation();
    SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
    object aChr, bChr;
    aChr.x = characters[testChar].saveposition.x;
    aChr.y = characters[testChar].saveposition.y;
    aChr.z = characters[testChar].saveposition.z;
    aChr.ay = characters[testChar].saveposition.ay;
    bChr.x = characters[oldMain].saveposition.x;
    bChr.y = characters[oldMain].saveposition.y;
    bChr.z = characters[oldMain].saveposition.z;
    bChr.ay = characters[oldMain].saveposition.ay;
    LogoffCharacter(&characters[testChar]);
    LogoffCharacter(&characters[oldMain]);
    SetMainCharacterIndex(testChar);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
    LAi_SetOfficerType(&characters[oldMain]); //This is hero index, switching with my officer
    LoginCharacter(&characters[testChar], loadedLocation.id);
    LoginCharacter(&characters[oldMain], loadedLocation.id);
    TeleportCharacterToPosAy(&characters[testChar], stf(aChr.x), stf(aChr.y), stf(aChr.z), stf(aChr.ay));
    TeleportCharacterToPosAy(&characters[oldMain], stf(bChr.x), stf(bChr.y), stf(bChr.z), stf(bChr.ay));
    locCameraTarget(&characters[testChar]);
    locCameraFollow();
     Log_SetStringToLog("Success ");
    return;

    int ifind = findSubStr("Hello", ",", 0);
    Log_SetStringToLog("Success " + ifind);
    return;
    DeleteAttribute(pchar, "fix20180707"));
    modTaverns();
    Log_SetStringToLog("Success ");
    return;

    fixMyCabin();
    return;

    //int ldLoc = FindLoadedLocation();
    Log_SetStringToLog("Success " + loadedlocation.id);
                       return;
    string myrel = "test";
    int isf = SendMessage(&LAi_grp_relations, "sii", "IsFriend", pchar, characterFromID("GenChar_492"));
    LAi_group_GetRelation(LAI_GROUP_PLAYER, LAI_GROUP_MONSTERS, &myrel);
	Log_SetStringToLog("Success " + isf + ", " + LAi_group_IsFriend(pchar, characterFromID("Blaze")) + ", " + myrel);
return;
DeleteAttribute(pchar, "fix20180530"));
    modTaverns();

    aref	locator_ships,locator_otherships;
	aref	locator;

	makearef(locator_ships, Island.locators.ships);

    int myNumShips = GetAttributesNum(locator_ships);
	Log_SetStringToLog("Success " + myNumShips);
	return;

    worldMap.islands.Bermudes.position.x = 907.0; //920.738;
	worldMap.islands.Bermudes.position.z = 872.0; //920.767;
	Log_SetStringToLog("Success ");
	return;
    MunityOnShip("ShipMunity");
    return;
    Weather.Wind.Speed = 4.5;
    fWeatherSpeed = stf(Weather.Wind.Speed);
    return;
    aref arScrShoter;
    SetEventHandler("dothis","setmysavestuff",0);
    if( !FindClass(&arScrShoter,"scrshoter") ) {
		CreateScreenShoter();

	}

    string mysave = GetSaveDirectory() + "Martien\Martien AutoReloadSave";
	string sSaveD = "Test Recover";
    ISetSaveData(mysave,sSaveD);

    Log_SetStringToLog("Success " + mysave);


	return;
    DeleteBattleInterface();
    return;
    pchar.Ship.Type = GenerateShip(SHIP_GALEON_SANTIAGO, 0);

    return;


    string sHello = "Hi there,two,three,four,five,six";
    int numF = GetStringListCount(sHello);
    string sRet = GetRandSubString(sHello);
   //pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = "Alice_town";
    //chrDisableReloadToLocation = false;
    ref mychar =
     Log_SetStringToLog("Success " + GetFullName(&characters[347]));

    return;
    BackgroundProcessExec("mybacktest");
    return;
    // pchar.Ship.Type = GenerateShip(SHIP_Dunkirker, 0);

pchar.nation = SPAIN;
return;
    aref refShip;
    makearef(refShip,pchar.Ship);
    refShip.Cannons.Borts = "";
Log_SetStringToLog("Hulls " + pchar.ship.upgrades.hull);
    if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
    if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); }
    chrDisableReloadToLocation = false;
    Log_SetStringToLog("Success");
return;

 SetTimerFunction("fackHealthDecline", 0, 0, 1);
 return;
    ref gcap = characterFromID("GhostCapt");

    ref  gShip;

   gShip = GetRealShip(sti(gcap.Ship.Type));
   string sGood = Goods[GOOD_GRAPES].name;
   Log_SetStringToLog("Balls " + gcap.Ship.Cargo.Goods.(sGood));
    return;

    Sea.Sea2.LodScale = 1;
    Sea.Sea2.GridStep = 0.0375;
    return;
//pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 2;
GiveItem2Character(pchar, "pistol59");
            return;
    pchar.Ship.Type = GenerateShip(SHIP_SANFELIPE, 0);
    return;
    Sea.Sea2.LodScale = 0.22;
    Sea.Sea2.GridStep = 0.03;

    sea.Sea2.MoveSpeed2 = sea.Sea2.MoveSpeed1;
    Sea.Sea2.Scale2 = stf(Sea.Sea2.Scale1);
    Sea.Sea2.Amp2 = stf(Sea.Sea2.Amp1);
    return;
    Sea.Sea2.BumpSpeed = 0.0;
     Sea.Sea2.Amp2 = 0.0;
    Sea.Sea2.LodScale = 0.22;
    Sea.Sea2.Scale2 = 0.0;
    sea.Sea2.MoveSpeed2 = "0.0, 0.0, 0.0";
    Sea.Sea2.GridStep = 0.03;
    Sea.Sea2.PosShift = 0.0;
    //Sea.isDone = "";
    return;
//Sea.Sea2.PosShift = 0.001;
//Log_SetStringToLog("Pos! " + Sea.Sea2.PosShift);
//return;
    Log_SetStringToLog("Ani1! " + sea.Sea2.AnimSpeed1);
    Log_SetStringToLog("Ani2! " + sea.Sea2.AnimSpeed2);
    Log_SetStringToLog("Move1! " + sea.Sea2.MoveSpeed1);
    Log_SetStringToLog("Move2! " + sea.Sea2.MoveSpeed2);

    Sea.MaxSeaHeight = 2.03;
    //Sea.Sea2.Amp1 = 1.0;
    Sea.Sea2.GridStep = 0.13;
    Sea.Sea2.PosShift = 0.001;

    Sea.Sea2.Amp1 = 5.0;
    Sea.Sea2.Amp2 = 0.02;
    Sea.Sea2.Scale1 = 2.0;
    Sea.Sea2.Scale2 = 15.0;

    //sea.Sea2.AnimSpeed1 = 1.0;
    sea.Sea2.AnimSpeed1 = 0.003;
    sea.Sea2.MoveSpeed2 = "1.0, 0.0, 0.003";
    sea.Sea2.AnimSpeed2 = 0.003;
    sea.Sea2.MoveSpeed1 = "1.0, 0.0, 0.003";
   // sea.Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";

Sea.isDone = "";
    return;
    Sea.Sea2.LodScale = 0.22;
    Sea.Sea2.PosShift = 0.0;
    Sea.Sea2.GridStep = 0.07;
    Sea.Sea2.Scale2 = 0.0;
    Sea.Sea2.Amp2 = -0.001;
    Sea.Sea2.Scale1 = 0.1;
    sea.Sea2.AnimSpeed2 = 1.0;
    sea.Sea2.MoveSpeed1 = "1.0, 0.0, 1.0";
    sea.Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";
//Sea.Sea2.AnimSpeed1 = 1.0;
return;

Log_SetStringToLog(pchar.location);
return;


    //MOD_SKILL_ENEMY_RATE = 5;
    pchar.basenation = HOLLAND;
    pchar.reputation = 100;
    return;

	return;
    Sea.Sea2.PosShift = 0.001;
    Sea.Sea2.Scale2 = 0.001;
    Sea.Sea2.Amp2 = 0.001;
    //Sea.Sea2.Amp1 = 0.0001;

    //return;

    //Sea.Sea2.LodScale = 0.25;
    Sea.Sea2.LodScale = 0.22;
    Sea.Sea2.GridStep = 0.13; //0.27;

    Sea.Sea2.Amp1 = 6.0;
	Sea.Sea2.AnimSpeed1 = 10.0;
	Sea.Sea2.Scale1 = 0.8;
	Sea.Sea2.MoveSpeed1 = "0.0, 0.0, 3.0";

	//Sea.Sea2.Amp2 = 1.0;
	Sea.Sea2.AnimSpeed2 = 19.0;
	//Sea.Sea2.Scale2 = 2.0;
	Sea.Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

    return;
    /*
    Weathers[n].Sea2.Amp1 = 19.0;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.25;
	Weathers[n].Sea2.MoveSpeed1 = "1.0, 0.0, 7.5";

	Weathers[n].Sea2.Amp2 = 1.5;
	Weathers[n].Sea2.AnimSpeed2 = 9.0;
	Weathers[n].Sea2.Scale2 = 3.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";
	*/
	Sea.Sea2.Frenel = 0.4;
	Sea.Sea2.Scale1 = 0.25;
Sea.Sea2.Amp1 = 15.0;

Sea.Sea2.Scale2 = 0.001;
Sea.Sea2.Amp2 = 0.25;
Sea.MoveSpeed2 = "0.0, 0.0, 0.001";
return;
    Sea.Sea2.FoamEnable = true;
	Sea.Sea2.FoamK = 0.1;
	Sea.Sea2.FoamV = 3.0;
	Sea.Sea2.FoamUV = 0.5;
	Sea.Sea2.FoamTexDisturb = 0.7;
    return;
    pchar.reputation = 100;
    pchar.basenation = HOLLAND;
    return;
    AddCharacterRank(pchar, 20, false, false, false, false, false);
    Log_SetStringToLog("Testing")
    return;
    pchar.reputation = 100;
    AddMoneyToCharacter(pchar, -49000);
    return;
    Log_SetStringToLog("Testing")
    Log_SetStringToLog("Testing2")
    return;

    pchar.nation = SPAIN;
    pchar.basenation = SPAIN;
    //CiriWitcher headgear
SendMessage(pchar,"lsfff",MSG_CHARACTER_SETHEAD,"hat4", -0.00, 0.14, -0.00);
return;
    pchar.model = "maska";
pchar.model.animation = "man_KVL_ab";
    return;
pchar.model = "ciriwitcher";
pchar.model.animation = "woman_sit2";
return;
BeginChangeCharacterActions(pchar);
SetDefaultStayIdle(pchar);

    SetDefaultNormWalk(pchar);
    SetDefaultFight(pchar);

SetDefaultDead(pchar);
SetDefaultFightDead(pchar);
EndChangeCharacterActions(pchar);


    return;
    //int an = findSubStr("ShipStockMan_1", "ShipStockMan_", 0);
    //string sss;
    //if(an==0) { //Begins
    //    sss = strcut("ShipStockMan_1", 13, strlen("ShipStockMan_1")-1);
    //}

    //Log_SetStringToLog("Operation successful! " + n + ", " + sss);
    //return;
    //pchar.nation = PIRATE;
    //LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
    //SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);

    //SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
    //return;
//SHIP_Fiftygunner
    //upgradeMyShip();
    //pchar.Ship.Type = GenerateShip(SHIP_FRIGATE_MB, 0);
    //worldMap.debug = "true";

    //LoadSegmentE("extensions\Quests\quests_reaction_ext.e");
    //QuestComplete_ext("1", "2");
    return;
    int n = findSubStr("ShipStockMan_1", "ShipStockMan_", 0);
    string sss;
    if(n==0) { //Begins
        sss = strcut("ShipStockMan_1", 13, strlen("ShipStockMan_1")-1);
    }

    Log_SetStringToLog("Operation successful! " + n + ", " + sss);
    return;
    pchar.nation = PIRATE;
    LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
    SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);

    //SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
    return;

    //upgradeMyShip();
    //pchar.Ship.Type = GenerateShip(SHIP_FRIGATE_MB, 0);
    //worldMap.debug = "true";

    //LoadSegmentE("extensions\Quests\quests_reaction_ext.e");
    //QuestComplete_ext("1", "2");

    //trace("Screen X = " + Render.screen_x);
    //trace("Screen y = " + Render.screen_y);
    //string ss = GetAddress_Form(&characters[35]);;
    //Log_SetStringToLog("Directory " + GetProgramDirectory());
//pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 4;
//pchar.basenation = SPAIN;
//YokoDias headgear
SendMessage(pchar,"lsfff",MSG_CHARACTER_SETHEAD,"helmet2", -0.02, 0.22, -0.05);
//pchar.actions.shot
//pchar.actions.shot = "MatchShot";
BeginChangeCharacterActions(pchar);
SetDefaultStayIdle(pchar);
if(GetItemsWeight(pchar) > GetMaxItemsWeight(pchar))
{
    pchar.actions.walk = "walk";
    pchar.actions.backwalk = "back walk";
    pchar.actions.run = "walk";
    pchar.actions.backrun = "back run";
    pchar.actions.stsUp = "stairs up";
    pchar.actions.stsUpRun = "stairs up";
    pchar.actions.stsDown = "stairs down";
    pchar.actions.stsDownRun = "stairs down";
    pchar.actions.fightwalk = "fight walk";
    pchar.actions.fightbackwalk = "fight back walk";
    pchar.actions.fightrun = "fight walk";
    pchar.actions.fightbackrun = "fight back walk";
}
else
{
    SetDefaultNormWalk(pchar);
    SetDefaultFight(pchar);
}
SetDefaultDead(pchar);
SetDefaultFightDead(pchar);
pchar.actions.shot = "MatchShot";
EndChangeCharacterActions(pchar);

 //mytestvar[2] = 5;
    Log_SetStringToLog("Operation successful! " + pchar.actions.shot);
return;
    Sea.MaxSeaHeight = 1.8;
    Sea.Scale1 = 10.0;
    Sea.Scale2 = -5.0;
    Sea.Amp1 = 0.075;
    Sea.Amp2 = 0.001;

    //Sea.GridStep = 0.05;
    /*
    Sea.MaxSeaHeight = 2.0;
Sea.Amp1 = 0.1;
Sea.AnimSpeed1 = 4.0;
Sea.Scale1 = 0.12;
Sea.MoveSpeed1 = "1.0, 0.0, 10.0";

Sea.Amp2 = 0.01;
Sea.AnimSpeed2 = 9.0;
Sea.Scale2 = 1.3;
Sea.MoveSpeed2 = "2.0, 0.0, 9.0"; */
    Log_SetStringToLog("Operation successful! " + Sea.Scale1);
}



void upgradeMyShip()
{
    int   cannonQ       = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity);
    int   cannonMax     = sti(RealShips[sti(Pchar.Ship.Type)].MaxCaliber);
    int   shipClass     = sti(RealShips[sti(Pchar.Ship.Type)].Class);
    //int   shipPrice     = sti(RealShips[sti(Pchar.Ship.Type)].Price);
    int   shipCapacity  = sti(RealShips[sti(Pchar.Ship.Type)].Capacity);
    float shipSpeedRate = stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);
    int   shipMaxCrew   = sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew);
    int   shipHP        = sti(RealShips[sti(Pchar.Ship.Type)].HP);
    int   shipSP        = sti(RealShips[sti(Pchar.Ship.Type)].SP);
    float shipTurnRate  = stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);
    ref shTo;

    shTo = &RealShips[sti(Pchar.Ship.Type)];

//speed, maneuverability, point of sail, crew, and cargo upgrades

    shTo.WindAgainstSpeed   = (stf(shTo.WindAgainstSpeed) + 2.8);
    shTo.Tuning.WindAgainstSpeed = true;

    shTo.SpeedRate        = (stf(shTo.SpeedRate) + 4);
    shTo.Tuning.SpeedRate = true;

    //increase sail texture level
    if(CheckAttribute(shTo, "ship.upgrades.sails") && shTo.ship.upgrades.sails == "pat")
    {
        shTo.ship.upgrades.sails = "silk";
    }
    else {
        shTo.ship.upgrades.sails = "pat";
    }

    shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/2);
    shTo.Tuning.Capacity = true;
    //increase sail texture level
    if(CheckAttribute(shTo, "ship.upgrades.sails") && shTo.ship.upgrades.sails == "pat")
    {
        shTo.ship.upgrades.sails = "silk";
    }
    else {
        shTo.ship.upgrades.sails = "pat";
    }

    shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/1.7);
    shTo.Tuning.TurnRate = true;


    shTo.MaxCrew        = sti(shTo.MaxCrew)*1.35;
    shTo.OptCrew        = sti(shTo.OptCrew)*1.1;
    shTo.Tuning.MaxCrew = true;
}

void doMargarita()
{

    locations[nLocationsNum].fastreload = "BasTer";
    locations[nLocationsNum].id = "Margarita_town";
	locations[nLocationsNum].id.label = "Street";
	locations[nLocationsNum].worldmap = "Margarita";
	locations[nLocationsNum].filespath.models = "locations\Town_Margarita\Town\";
	locations[nLocationsNum].image.1 = "loading\FrenchTownS.tga.tx";
	locations[nLocationsNum].image.2 = "loading\SpanishTown1.tga.tx";
	locations[nLocationsNum].image.3 = "loading\Town2.tga.tx";
	locations[nLocationsNum].image.4 = "loading\Town8.tga.tx";

	locations[nLocationsNum].citizens = true;
	locations[nLocationsNum].soldiers = true;
	locations[nLocationsNum].carrier = true;
	locations[nLocationsNum].questSeekCap = 6;
	//Town sack
	locations[nLocationsNum].townsack = "Margarita";
	//Sound
	locations[nLocationsNum].type = "town";
	//locations[nLocationsNum].fastreload = "Margarita";
	locations[nLocationsNum].islandId = "Guadeloupe";
	LAi_LocationFantomsGen(&locations[nLocationsNum], true);
	locations[nLocationsNum].houseEnc = true;
	//Models
	//Always
	locations[nLocationsNum].models.always.town = "Margarita";
	locations[nLocationsNum].models.always.town.sea_reflection = 1;
	//locations[nLocationsNum].models.always.L1 = "Margarita_signsA";
	locations[nLocationsNum].models.always.seabed = "Margarita_sb";
	locations[nLocationsNum].models.always.locators = "Margarita_locators";
	locations[nLocationsNum].models.always.grassPatch = "Margarita_grass";

	//locations[nLocationsNum].models.always.plan = "plan1";
	//locations[nLocationsNum].models.always.plan.level = 9;

	//Fontain
	locations[nLocationsNum].models.always.Waterfall1 = "fontain1";
	locations[nLocationsNum].models.always.Waterfall1.uvslide.v0 = 0.5;
    locations[nLocationsNum].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[nLocationsNum].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[nLocationsNum].models.always.Waterfall1.level = 50;

	locations[nLocationsNum].models.always.Waterfall2 = "fontain2";
	locations[nLocationsNum].models.always.Waterfall2.uvslide.v0 = 0.2;
    locations[nLocationsNum].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[nLocationsNum].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[nLocationsNum].models.always.Waterfall2.level = 49;

	//WindMill Fan
	/*
	locations[nLocationsNum].models.always.MillFan = "mill_movie";
	locations[nLocationsNum].models.always.MillFan.locator.group = "WindMill";
	locations[nLocationsNum].models.always.MillFan.locator.name ="Fan";
	locations[nLocationsNum].models.always.MillFan.rotate.x = 0.0;
	locations[nLocationsNum].models.always.MillFan.rotate.y = 0.0;
	locations[nLocationsNum].models.always.MillFan.rotate.z = 0.2;
    */
	//Day
	locations[nLocationsNum].models.day.fonar = "Margarita_fd";
	//locations[nLocationsNum].models.day.cPatch = "Margarita_patch_day";
	locations[nLocationsNum].models.day.charactersPatch = "Margarita_patch_day";
	locations[nLocationsNum].models.day.jumpPatch = "Margarita_jump_patch";
	locations[nLocationsNum].models.day.rinok = "Margarita_rinok";
	//Night
	locations[nLocationsNum].models.night.fonar = "Martinique_fn";
	//locations[nLocationsNum].models.night.cPatch = "Margarita_patch_night";
	locations[nLocationsNum].models.night.charactersPatch = "Margarita_patch_night";
	locations[nLocationsNum].models.might.jumpPatch = "Margarita_jump_patch";
	//Environment
	locations[nLocationsNum].environment.weather = "true";
	locations[nLocationsNum].environment.sea = "true";
	//Reload map

    locations[nLocationsNum].reload.l1.name = "reload1_back";
	locations[nLocationsNum].reload.l1.go = "Margarita";
	locations[nLocationsNum].reload.l1.emerge = "reload_1";
	locations[nLocationsNum].reload.l1.autoreload = "0";
	locations[nLocationsNum].reload.l1.label = "Sea";
	locations[nLocationsNum].locators_radius.reload.reload2_back = 1.8;

	locations[nLocationsNum].reload.l2.name = "reload2_back";
	locations[nLocationsNum].reload.l2.go = "Margarita";
	locations[nLocationsNum].reload.l2.emerge = "reload_1";
	locations[nLocationsNum].reload.l2.autoreload = "0";
	locations[nLocationsNum].reload.l2.label = "Sea";
	locations[nLocationsNum].locators_radius.reload.reload2_back = 1.8;

	locations[nLocationsNum].reload.l3.name = "reload3_back";
	locations[nLocationsNum].reload.l3.go = "Margarita_townhall";
	locations[nLocationsNum].reload.l3.emerge = "reload1";
	locations[nLocationsNum].reload.l3.autoreload = "0";
	locations[nLocationsNum].reload.l3.label = "Residence";
	locations[nLocationsNum].reload.l3.close_for_night = 1;

	locations[nLocationsNum].reload.l4.name = "reload4_back";
	locations[nLocationsNum].reload.l4.go = "Margarita_tavern";
	locations[nLocationsNum].reload.l4.emerge = "reload1";
	locations[nLocationsNum].reload.l4.autoreload = "0";
	locations[nLocationsNum].reload.l4.label = "Tavern";

	locations[nLocationsNum].reload.l5.name = "reload5_back";
	locations[nLocationsNum].reload.l5.go = "Margarita_shipyard";
	locations[nLocationsNum].reload.l5.emerge = "reload1";
	locations[nLocationsNum].reload.l5.autoreload = "0";
	locations[nLocationsNum].reload.l5.label = "Shipyard";
	locations[nLocationsNum].reload.l5.close_for_night = 1;

	locations[nLocationsNum].reload.l6.name = "reload6_back";
	locations[nLocationsNum].reload.l6.go = "Margarita_store";
	locations[nLocationsNum].reload.l6.emerge = "reload1";
	locations[nLocationsNum].reload.l6.autoreload = "0";
	locations[nLocationsNum].reload.l6.label = "Store";
	locations[nLocationsNum].reload.l6.close_for_night = 1;

	locations[nLocationsNum].reload.l7.name = "reload7_back";
	locations[nLocationsNum].reload.l7.go = "Margarita_church";
	locations[nLocationsNum].reload.l7.emerge = "reload1";
	locations[nLocationsNum].reload.l7.autoreload = "0";
	locations[nLocationsNum].reload.l7.label = "Church";
	//locations[nLocationsNum].reload.l7.close_for_night = 1;

	locations[nLocationsNum].reload.l8.name = "reload8_back";
	locations[nLocationsNum].reload.l8.go = "Margarita_bank";
	locations[nLocationsNum].reload.l8.emerge = "reload1";
	locations[nLocationsNum].reload.l8.autoreload = "0";
	locations[nLocationsNum].reload.l8.label = "Usurer House";
	locations[nLocationsNum].reload.l8.close_for_night = 1;

	locations[nLocationsNum].reload.l9.name = "reload9_back";
	locations[nLocationsNum].reload.l9.go = "Margarita_brothel";
	locations[nLocationsNum].reload.l9.emerge = "reload1";
	locations[nLocationsNum].reload.l9.autoreload = "0";
	locations[nLocationsNum].reload.l9.label = "Brothel";

 	locations[nLocationsNum].reload.l91.name = "reload91";
	locations[nLocationsNum].reload.l91.go = "Margarita_SecBrRoom";
	locations[nLocationsNum].reload.l91.emerge = "reload2";
	locations[nLocationsNum].reload.l91.autoreload = "0";
	locations[nLocationsNum].reload.l91.label = "Brothel";

	locations[nLocationsNum].reload.l10.name = "reload10_back";
	locations[nLocationsNum].reload.l10.go = "Margarita_PortOffice";
	locations[nLocationsNum].reload.l10.emerge = "reload1";
	locations[nLocationsNum].reload.l10.autoreload = "0";
	locations[nLocationsNum].reload.l10.label = "PortOffice";
	locations[nLocationsNum].reload.l10.close_for_night = 1;

	locations[nLocationsNum].reload.gate.name = "gate_back";
	locations[nLocationsNum].reload.gate.go = "FortFrance_ExitTown";
	locations[nLocationsNum].reload.gate.emerge = "reload3";
	locations[nLocationsNum].reload.gate.autoreload = "0";
	locations[nLocationsNum].reload.gate.label = "ExitTown";

    locations[nLocationsNum].reload.l11.name = "houseH1";
	locations[nLocationsNum].reload.l11.go = "Margarita_HouseHut";
	locations[nLocationsNum].reload.l11.emerge = "reload1";
	locations[nLocationsNum].reload.l11.autoreload = "0";
	locations[nLocationsNum].reload.l11.label = "House";

	locations[nLocationsNum].reload.l12.name = "houseH11";
	locations[nLocationsNum].reload.l12.go = "Margarita_HouseHut";
	locations[nLocationsNum].reload.l12.emerge = "reload2";
	locations[nLocationsNum].reload.l12.autoreload = "0";
	locations[nLocationsNum].reload.l12.label = "House";

	locations[nLocationsNum].reload.l13.name = "basement1";
	locations[nLocationsNum].reload.l13.go = "Margarita_Dungeon";
	locations[nLocationsNum].reload.l13.emerge = "reload1";
	locations[nLocationsNum].reload.l13.autoreload = "0";
	locations[nLocationsNum].reload.l13.label = "Dungeon";

    locations[nLocationsNum].reload.l20.name = "houseF4";
	locations[nLocationsNum].reload.l20.go = "CommonRoom_MH";
	locations[nLocationsNum].reload.l20.emerge = "reload1";
	locations[nLocationsNum].reload.l20.autoreload = "0";
	locations[nLocationsNum].reload.l20.label = "House";

	locations[nLocationsNum].reload.l21.name = "houseF3";
	locations[nLocationsNum].reload.l21.go = "CommonRoom_MH2";
	locations[nLocationsNum].reload.l21.emerge = "reload1";
	locations[nLocationsNum].reload.l21.autoreload = "0";
	locations[nLocationsNum].reload.l21.label = "House";

	locations[nLocationsNum].reload.l22.name = "houseS1";
	locations[nLocationsNum].reload.l22.go = "CommonCobHouse";
	locations[nLocationsNum].reload.l22.emerge = "reload1";
	locations[nLocationsNum].reload.l22.autoreload = "0";
	locations[nLocationsNum].reload.l22.label = "House";

	locations[nLocationsNum].reload.l23.name = "houseF1";
	locations[nLocationsNum].reload.l23.go = "CommonRoom_MH5";
	locations[nLocationsNum].reload.l23.emerge = "reload1";
	locations[nLocationsNum].reload.l23.autoreload = "0";
	locations[nLocationsNum].reload.l23.label = "House";

	locations[nLocationsNum].reload.l24.name = "houseS2";
	locations[nLocationsNum].reload.l24.go = "CommonFlamHouse";
	locations[nLocationsNum].reload.l24.emerge = "reload1";
	locations[nLocationsNum].reload.l24.autoreload = "0";
	locations[nLocationsNum].reload.l24.label = "House";

	locations[nLocationsNum].reload.l25.name = "houseH2";
	locations[nLocationsNum].reload.l25.go = "CommonRoom_MH7";
	locations[nLocationsNum].reload.l25.emerge = "reload1";
	locations[nLocationsNum].reload.l25.autoreload = "0";
	locations[nLocationsNum].reload.l25.label = "House";

	locations[nLocationsNum].reload.l26.name = "houseSp1";
	locations[nLocationsNum].reload.l26.go = "CommonResidence_BackHall";
	locations[nLocationsNum].reload.l26.emerge = "reload1";
	locations[nLocationsNum].reload.l26.autoreload = "0";
	locations[nLocationsNum].reload.l26.label = "House";

	locations[nLocationsNum].reload.l27.name = "houseF2";
	locations[nLocationsNum].reload.l27.go = "CommonRoom_MH9";
	locations[nLocationsNum].reload.l27.emerge = "reload1";
	locations[nLocationsNum].reload.l27.autoreload = "0";
	locations[nLocationsNum].reload.l27.label = "House";

	Colonies[14].id = "Margarita";
}
