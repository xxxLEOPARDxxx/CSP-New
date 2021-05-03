#include "Addons\Korsar_Maxim_func.c"		//Функции Korsar-а Maxim-а
#include "Addons\LORD_func.c"	        	//Функции LORD-а
#include "Addons\Academy.c"		// Академия и тренировки
#include "Addons\Arena.c"		// Поселение фехтовальщиков и множество фич с ними
#include "Addons\Colony.c"		// Постройка и жизнь колонии
#include "Addons\ColonyGuarding.c"	// Организация охраны колонии в море
#include "Addons\Plantation.c"		// Постройка и жизнь плантации
#include "Addons\Mines.c"		// Постройка и жизнь рудников
#include "Addons\Quests.c"		// Квесты
#include "Addons\GenerateQuests.c"	// Генерируемые квесты

void SetDamnedDestinyVariable()
{
	PChar.SelectMainCharacter = false;
	
	GenerateColonyVariable();
	ReloadProgressUpdate();
	InitPlantation();
	ReloadProgressUpdate();
	SetStartColonyGuarding();
	ReloadProgressUpdate();
	
	PChar.Dozor = "0";
	PChar.Dozor.Riddle.CurType = 1;
	PChar.Dozor.Riddle.CanInterface = 0;
	DozorPrepare();
	
	PChar.GenerateShipWreck.Block = false;
	PChar.GenerateShipWreck.ShipInMap = "";
	PChar.GenerateShipWreck.State = "none";
	PChar.GenerateShipWreck.MaxGoods = 500;
	PChar.GenerateShipWreck.MaxGoods.Planks = 0;
	PChar.GenerateShipWreck.MaxGoods.SailCloth = 0;
	PChar.GenerateShipWreck.GoodsChange = false;
	PChar.GenerateShipWreck.GoodsChange.Yes = false;
	PChar.GenerateShipWreck.AddBandaShip = false;
	PChar.GenerateShipWreck.ValodyaToMoney = false;
	
	PChar.GenerateQuestDuel.Block = false;
	
	PChar.TmpModel = "Hero1";
	PChar.ToMusketeer.Model = "hero1";
	PChar.ToMusketeer.Ani = "man";
	
	PChar.SuccessPrice.ReadNotice = false;
	PChar.SuccessPrice.CreateCharacter = false;
	PChar.SuccessPrice.CreateCharacter.Model = "Hero1";
	
	GenerateArena();
	AcademyLandInit();
	
	ReloadProgressUpdate();
}
/////////////////////////////////////////////////////////////////////////////////
// Начало игры и выбор главного героя
/////////////////////////////////////////////////////////////////////////////////
void SelectMainCharacterInCabine(string sQuest)
{
	ref PChar = GetMainCharacter();
	
	bDisableCharacterMenu = true;
	bDisableQuestInterface = true;

	StartQuestMovie(true, true, true);
	
	Locations[FindLocation(PChar.location)].items.randitem1 = "";
	
	ChangeCharacterAddressGroup(PChar, PChar.location, "goto", "SelectCharacter");
	
	PChar.model = "";
	SetNewModelToChar(PChar);
	
    	SetCharacterTask_None(GetMainCharacter());
	InterfaceStates.Buttons.Save.enable = false;
	
	LAi_SetActorTypeNoGroup(PChar);
	LAi_ActorTurnToLocator(PChar, "reload", "reload1");
	
	DoQuestFunctionDelay("SelectMainCharacterInCabineLocCamera", 0.1);
	DoQuestFunctionDelay("LaunchCreateCharacterInterface", 2.0);
}

void SelectMainCharacterInCabineLocCamera(string _tmp)
{
	float x, y, z;
	x = stf(loadedLocation.locators.camera.reload1.x) + 0.5;
	y = stf(loadedLocation.locators.camera.reload1.y) - 0.5;
	z = stf(loadedLocation.locators.camera.reload1.z) + 1.0;
	locCameraToPos(x, y, z, false);	
}

void LaunchCreateCharacterInterface(string _tmp)
{
	LaunchCreateCharacter();
}

void EndSelectMainCharacter(ref chr)
{
	bDisableCharacterMenu = false;
	bDisableQuestInterface = false;
	//Log_Info("Ожидайте прогрузки, игра не зависнет.");
	SetTimerFunction("StartGameOpenArena", 0, 0, 30);
	pchar.starttype = startHeroType;
	LaunchSelectCharacter();
}


void NoFreeze()
{
	SetLaunchFrameFormParam("Идёт симуляция ПГГ и генерация сторожей, пожалуйста подождите.", "", 0.1, 2.0);
	LaunchFrameForm();
}

void StartGameOpenArena(string qName)
{
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.label = "Arena";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = 1;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l4.label = "FencingTown";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l4.disable = 0;
	
	Locations[FindLocation("FencingTown_Arena")].id.label = "Arena";
	Locations[FindLocation("FencingTown_Fort")].id.label = "FencingTown";
}

void WayBeginning(string _tmp)
{
	DeleteAttribute(pchar,"cirassID");
	initNewMainCharacter();
	if (startHeroType == 1) //21/07/07 homo для Блада даем другое начало
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Estate";
    	pchar.quest.Tut_start.function                  = "Blood_StartGame";
		Pchar.questTemp.WhisperLine = false;
		InterfaceStates.startGameWeather = FindWeather("20 Hour");
		DoQuestReloadToLocation("Estate", "reload", "reload1", "");
		return;
    }
	InitPsHeros();
	ReloadProgressUpdate();
	for (int j = 0; j< MAX_COLONIES; j++)
	{
		GenerateIslandShips(colonies[j].island);
	}
	ReloadProgressUpdate();
    if (startHeroType == 2)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Bermudes_Dungeon";
    	pchar.quest.Tut_start.function                  = "Whisper_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		DoQuestReloadToLocation("Bermudes_Dungeon", "reload", "reload2_back", "");
		return;
    }
	if (startHeroType == 3 || startHeroType == 4)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Shore57";
    	pchar.quest.Tut_start.function                  = "Sharp_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
		DoQuestReloadToLocation("Shore57", "item", "item11", "");
		return;
    }
	if (startHeroType == 5 || startHeroType == 6)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Shore_ship2";
    	pchar.quest.Tut_start.function                  = "SharleMary_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
		DoQuestReloadToLocation("Shore_ship2", "goto", "goto4", "");
		return;
    }
	if (startHeroType == 7)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "My_Campus";
    	pchar.quest.Tut_start.function                  = "DarkHuman_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
		DoQuestReloadToLocation("My_Campus", "goto", "goto5", "");
		return;
    }
	if (startHeroType > 7 && startHeroType <= 11)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Temple_skulls";
    	pchar.quest.Tut_start.function                  = "Undead_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
		DoQuestReloadToLocation("Temple_skulls", "goto", "goto2", "");
		return;
    }
	if (startHeroType > 11)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Ship_deck_Low";
    	pchar.quest.Tut_start.function                  = "Tut_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
		DoQuestReloadToLocation("Ship_deck_low", "goto", "goto4", "");
    }
}

/* PROGRAM/LUGGER/UTILS.C */
/////////////////////////////////////////////////////////////////////////////////
// Раздача еды
/////////////////////////////////////////////////////////////////////////////////
void SetFoodToCharacter(ref chr, int iQuantity, int iFoodQuantity)
{
	int d = 1;
	int iSum = 0;
	string sFood = "";
	for(int f = 1; f <= iQuantity; f++)
	{
		sFood = "Food" + f;
		if(CheckAttribute(chr, "items." + sFood))
		{
			DeleteAttribute(chr, "items." + sFood);
		}
		
		switch(f)
		{
			case 1: d = 12; break;
			case 2: d = 14; break;
			case 3: d = 16; break;
			case 4: d = 18; break;
			case 5: d = 20; break;
		}
		
		iSum = makeint(iFoodQuantity / d)+1;
		TakeNItems(chr, sFood, iSum);
	}
}


void SetEnergyQty(ref chr, float fQty, float fQtyMax)
{
	chr.chr_ai.energy = fQty;
	chr.chr_ai.energyMax = fQtyMax;
}
/////////////////////////////////////////////////////////////////////////////////
// Переключение режима абордажа
/////////////////////////////////////////////////////////////////////////////////
void GetBoardModeToLocation(ref loc)
{
	if(!CheckAttribute(loc, "CheckBoardMode"))
	{
		return;	
	}
	
	string sFile = "DeckLowVSMedium_locators";
	
	switch(loc.id)
	{
		case "BOARDING_SMALL_DECK":
			if(bBoardMode)
			{
				sFile = "DeckLowVSMedium_locators_lugger";
			}
			else
			{
				sFile = "DeckLowVSMedium_locators";
			}
		break;
		
		case "BOARDING_MEDIUM_DECK":
			if(bBoardMode)
			{
				sFile = "deckLowVSBig_locators_lugger";
			}
			else
			{
				sFile = "deckLowVSBig_locators";
			}
		break;
		
		case "BOARDING_BIG_DECK":
			if(bBoardMode)
			{
				sFile = "deckMediumVSBig_locators_lugger";
			}
			else
			{
				sFile = "deckMediumVSBig_locators";
			}
		break;	

		case "BOARDING_LNSHP_FRGT_DECK":
			if(bBoardMode)
			{
				sFile = "deckLineshipVSFrigate_locators_lugger";
			}
			else
			{
				sFile = "deckLineshipVSFrigate_locators";
			}
		break;
	}
	
	loc.models.always.locators = sFile;
	
	Log_TestInfo("Считываем тип абордажа.");
	Log_TestInfo("Сменили локаторы для локации абордажа: " + loc.id);
	Log_TestInfo("Имя файла локаторов для локации абордажа: " + loc.models.always.locators);
}


void Log_InfoS(string sText)
{
	PlayStereoSound("new_round");
	Log_Info(sText);
}

int GetRank(ref chr, int step)
{
	int iRank = sti(chr.rank) + step;
	
	if(iRank < 1)
	{
		iRank = 1;
	}
	
	return iRank;
}

ref PCharLoc()
{
	int iLocation = FindLocation(PChar.location);
	return &Locations[iLocation];
}

void DeleteAllFantomCharactersFromLocation(ref loc)
{
	ref chr;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(chr,Characters[n]);
		
		if(CheckAttribute(chr, "id"))
		{
			if(GetCharacterIndex(chr.id) != nMainCharacterIndex && !CheckAttribute(chr, "NotRemoved") && !IsOfficer(chr))
			{
		    		if(chr.location == loc.id)
				{
					LAi_SetActorType(chr);
					LAi_ActorGoToLocation(chr,"reload","sea","none","","","",10.0);
				}
			}
		}
	}
}

void AddSimpleRumourToAllNations(string sText, int iTime, int iQty)
{
	for(int i=0; i<MAX_NATIONS; i++)
	{
		AddSimpleRumour(sText, ENGLAND, iTime, iQty);
	}
}

void SetGeraldDetails(ref chr, int iHull, int iColor, string sType, string sGerald)
{
	if(!CheckAttribute(chr, "Ship.Type")) { return; }
	if(sti(chr.Ship.Type) >= REAL_SHIPS_QUANTITY) { return; }

	ref rShip = GetRealShip(sti(chr.Ship.Type));
	
	if(iHull != -1 && !CheckAttribute(rShip, "DisableChangedHull"))
	{
		rShip.Ship.Upgrades.Hull = iHull;
	}
	
	if(sType != "")
	{
		rShip.EmblemedSails.normalTex = "ships\" + sType + ".tga";
	}
	
	if(iColor != -1)
	{
		rShip.ship.sailscolor = SailsColors[iColor].color;
	}
	
	if(sGerald != "")
	{
		rShip.GeraldName = sGerald;
		rShip.ShipSails.gerald_name = "Ships\Gerald\" + sGerald + ".tga";
	}
}

string GetNameLugger(ref chr, string sType)
{
	string sName = "";
	switch(sType)
	{
		case "n": sName = chr.name; break;
		case "l": sName = chr.lastname; break;
		case "f": sName = chr.name + " " + chr.lastname; break;
	}
	return sName;
}

void CreateCaimanShoreSlaves(ref loc)
{
	Log_TestInfo(PChar.location);
	if(PChar.ColonyBuilding.SlavesInShore.CurShore != loc.id) { return; }

    int iMassive;
	string model[23];
	
	int iQuantity = 10;
	if(PChar.ColonyBuilding.Stage != "0")
	{
		iQuantity += 5;	
	}

	model[0] = "prizon_1";
    model[1] = "prizon_2";
    model[2] = "prizon_3";
    model[3] = "prizon_4";
    model[4] = "prizon_5";
    model[5] = "prizon_6";
    model[6] = "prizon_7";
	model[7] = "prizon_8";
    model[8] = "pirate_1";
    model[9] = "prison_5";
    model[10] = "pirate_1";
    model[11] = "pirate_11";
    model[12] = "pirate_12";
    model[13] = "pirate_13";
    model[14] = "pirate_14";
    model[15] = "pirate_15";
    model[16] = "pirate_16";
    model[17] = "pirate_21";
    model[18] = "pirate_25";
    model[19] = "PKM_rab_1";
    model[20] = "PKM_rab_2";
    model[21] = "PKM_rab_3";
    model[22] = "PKM_rab_4";

	ref sld;
	for(int i=1; i <= iQuantity; i++)
	{
	    iMassive = rand(22);
	
    	string sAni = "man2";
    	if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man";
		
		sld = GetCharacter(NPC_GenerateCharacter("FantomSlaveInCaimanShore_" + i, model[iMassive], "man", sAni, 1, PIRATE, 0, false));
		sld.dialog.filename = "Common_Builder.c";
        sld.greeting = "Gr_slave";
		sld.dialog.currentnode = "ForSlave";
		sld.PoorSit = true;
		LAi_SetLoginTime(sld, 6.0, 22.99);
		LAi_SetCitizenTypeNoGroup(sld);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		PlaceCharacter(sld, "officers", "random_must_be_near");
	}
		
	/*string sModel = "GenresBag1";
	switch(rand(4))
	{
		case 0: sModel = "GenresBag" + (rand(1)+1); break;
		case 1: sModel = "GenresBarrel" + (rand(1)+1); break;
		case 2: sModel = "GenresBarrelTop" + (rand(1)+1); break;
		case 3: sModel = "GenresBottle" + (rand(1)+1); break;
		case 4: sModel = "GenresChest" + (rand(1)+1); break;
	}
	
	sld = GetCharacter(NPC_GenerateCharacter("Carrier", sModel, "man", "genres", 0, PIRATE, 0, false));
	sld.id = sld.id + "_" + sld.index;
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 7.0, 20.0);
	sld.firstLoc = "Gate";
	sld.firstLoc.timer = 1.0;
	LAi_SetCarrierType(sld);
	ChangeCharacterAddressGroup(sld, loc.id, "reload", "gate");*/
}

ref LocFromID(string sLocation)
{
	int iLocation = FindLocation(sLocation);
	return &Locations[iLocation];
}

void SetQuestBoxItems(string sLocation, string sItem, int Qty)
{
	string sBox = "box1";
	if(sItem == "SuccessPrice_Chest")
	{
		sBox = "box8";
	}
	
	PChar.GenQuestBox.(sLocation) = true;
	PChar.GenQuestBox.(sLocation).(sBox).items.(sItem) = Qty;
	PChar.GenQuestBox.(sLocation).stay = true;
}

void ClearQuestBoxStay(string sLocation)
{
	if(!CheckAttribute(PChar, "GenQuestBox." + sLocation))
	{
		return;
	}

	DeleteAttribute(PChar, "GenQuestBox." + sLocation);
}

void SetDialogCharacter2Character(ref chr, ref achr, float fTime, bool bActor)
{
	LAi_SetActorType(achr);
	
	if(bActor)
	{
		LAi_SetActorType(chr);
		LAi_ActorWaitDialog(chr, achr);
	}
	
	LAi_ActorDialog(achr, chr, "", fTime, 1.0);
}

void DeleteAllOfficersFromLocation()
{
	int iOfficer = 0;
	if(GetOfficersQuantity(PChar) > 0)
	{
		for(int off=0; off <= MAX_NUM_FIGHTERS; off++)
		{
			iOfficer = GetOfficersIndex(PChar, off);
			if(iOfficer != -1 && iOfficer != nMainCharacterIndex)
			{
				LogoffCharacter(&Characters[iOfficer]);
			}
		}
	}
}

int FindShipFromClass(int iClass, string sType)
{
	if(sType == "none" || sType == "")
	{
		return 0;
	}

	int iShip = 0;
	switch(sType)
	{
		case "Fast":
			switch(iClass)
			{
				case 7: return SHIP_WAR_TARTANE; break;
				case 6: return 3 + rand(11); break;
				case 5: return 15 + rand(12); break;
				case 4: return 28 + rand(23); break;
				case 3: return 52 + rand(31); break;
				case 2: return 84 + rand(20); break;
				case 1: return 84 + rand(40); break;
			}
		break;
		
		case "Trader":
			switch(iClass)
			{
				case 7: return SHIP_WAR_TARTANE; break;
				case 6: return 3 + rand(11); break;
				case 5: return 15 + rand(12); break;
				case 4: return 28 + rand(23); break;
				case 3: return 52 + rand(31); break;
				case 2: return 84 + rand(20); break;
				case 1: return 84 + rand(40); break;
			}
		break;
		
		case "All":
			switch(iClass)
			{
				case 7: return SHIP_WAR_TARTANE; break;
				case 6: return 3 + rand(11); break;
				case 5: return 15 + rand(12); break;
				case 4: return 28 + rand(23); break;
				case 3: return 52 + rand(31); break;
				case 2: return 84 + rand(20); break;
				case 1: return 84 + rand(40); break;
			}
		break;
	}
	return 0;
}

int GetMastQuantityFromShip(ref chr)
{
	if(!CheckAttribute(chr, "ship")) { return 0; }
	if(!CheckAttribute(chr, "ship.masts")) { return 0; }
	if(sti(chr.Ship.Type) >= REAL_SHIPS_QUANTITY) { return 0; }
	
	aref ar;
	makearef(ar, chr.ship.masts);
	
	return GetAttributesNum(ar);
}

void SetQuestFunction(string sQuest, string sFunction, string sType, string sName)
{
	switch(sType)
	{
		case "efl":
			PChar.quest.(sQuest).win_condition.l1 = "ExitFromLocation";
			PChar.quest.(sQuest).win_condition.l1.location = sName;
			PChar.quest.(sQuest).function = sFunction;	
		break;
		
		case "l":
			PChar.quest.(sQuest).win_condition.l1 = "location";
			PChar.quest.(sQuest).win_condition.l1.location = sName;
			PChar.quest.(sQuest).function = sFunction;	
		break;
		
		case "i":
			PChar.quest.(sQuest).win_condition.l1 = "item";
			PChar.quest.(sQuest).win_condition.l1.item = sName;
			PChar.quest.(sQuest).function = sFunction;	
		break;
	}
}