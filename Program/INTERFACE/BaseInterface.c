extern void initFastReloadTable();

void InitBaseInterfaces()
{
	InterfaceStates.BackEnvironmentIsCreated = false;
	SetEventHandler("GetQuestTextFileName","GetQuestTextFileName",0);
	GameInterface.GameTime.sec = InterfaceStates.GameTime.sec;
	GameInterface.GameTime.min = InterfaceStates.GameTime.min;
	GameInterface.GameTime.hour = InterfaceStates.GameTime.hour;
	CreateEntity(&GameInterface,"xinterface");
	DelEventHandler("GetQuestTextFileName","GetQuestTextFileName");
	LayerAddObject("iExecute",&GameInterface,-100);
	LayerAddObject("iRealize",&GameInterface,-100);
	if(!IsEntity(&LanguageObject))
	{	CreateEntity(&LanguageObject,"obj_strservice");
	}
	InitLogInterface();
	InitBattleLandInterface();
	InterfaceStates.Launched = false;
	if( storeDayUpdateCnt>=0 ) // обновление магазина можно включить
	{
		Event("EvStoreDayUpdate");
	}
	LanguageCloseFile("LocLables.txt");
	g_LocLngFileID = LanguageOpenFile("LocLables.txt");
	InitTimerInterface();
}

string questTextFileName[3];
ref GetQuestTextFileName()
{
	questTextFileName[0] = "texts\russian\questbook\QuestBook_Part1.txt";
	questTextFileName[1] = "texts\russian\questbook\QuestBook_Part2.txt";
	questTextFileName[2] = "texts\russian\questbook\QuestBook_New.txt"; // Warship. Ёто наш квестбук
	return &questTextFileName;
}

void InitBaseInterfaces_main()
{
	GameInterface.Scroll.current = 0;
	GameInterface.FourImage.current = 0;

	InterfaceStates.GameTime.sec = 0;
	InterfaceStates.GameTime.min = 0;
	InterfaceStates.GameTime.hour = 0;

	InterfaceStates.Buttons.New.enable = true;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Load.enable = false;
	InterfaceStates.Buttons.Save.enable = false;
	InterfaceStates.Buttons.Options.enable = true;
	InterfaceStates.Buttons.Credits.enable = true;
	InterfaceStates.Buttons.Quit.enable = true;
	InterfaceStates.Buttons.Controls.enable = true;


	InterfaceStates.BattleShow.FastCommand	= true;
	InterfaceStates.BattleShow.LogString	= true;
	InterfaceStates.BattleShow.Navigator	= true;
	InterfaceStates.BattleShow.Command		= true;
	InterfaceStates.BattleShow.Alarm		= true;


	InterfaceStates.doUnFreeze = true;
	InterfaceStates.Launched = false;

	InitInterfaceTables();

	if( LoadSegment("battle_interface\fast_reload_table.c") )
	{
		initFastReloadTable();
		UnloadSegment("battle_interface\fast_reload_table.c");
	}
}

void InitInterfaceTables()
{
	SetArraySize(&Interfaces,INTERFACE_QUANTITY+3);

	// Lugger -->
	// Быстрая продажа
	Interfaces[INTERFACE_QUICKLY_TRADER].SectionName = "interface\QuicklyTrade.c";
	Interfaces[INTERFACE_QUICKLY_TRADER].IniFile = "INTERFACES\QuicklyTrade.ini";
	// Create Character
	Interfaces[INTERFACE_CREATE_CHARACTER].SectionName = "interface\CreateCharacter.c";
	Interfaces[INTERFACE_CREATE_CHARACTER].IniFile = "INTERFACES\CreateCharacter.ini";
	// Colony Land Guard
	Interfaces[INTERFACE_COLONY_LAND_GUARD].SectionName = "interface\ColonyLandGuard.c";
	Interfaces[INTERFACE_COLONY_LAND_GUARD].IniFile = "INTERFACES\ColonyLandGuard.ini";
	// Colony Guardiang
	Interfaces[INTERFACE_COLONYGUARDING].SectionName = "interface\ColonyGuardiang.c";
	Interfaces[INTERFACE_COLONYGUARDING].IniFile = "INTERFACES\ColonyGuardiang.ini";
	// Њекахром
	Interfaces[INTERFACE_MEKAKHROM].SectionName = "interface\Mekakhrom.c";
	Interfaces[INTERFACE_MEKAKHROM].IniFile = "INTERFACES\Mekakhrom.ini";
	// Store House
	Interfaces[INTERFACE_STOREHOUSE].SectionName = "interface\StoreHouse.c";
	Interfaces[INTERFACE_STOREHOUSE].IniFile = "INTERFACES\StoreHouse.ini";
	// Plantation Interface
	Interfaces[INTERFACE_PLANTATION].SectionName = "interface\Plantation.c";
	Interfaces[INTERFACE_PLANTATION].IniFile = "INTERFACES\Plantation.ini";
	// Colony Interface
	Interfaces[INTERFACE_COLONY].SectionName = "interface\Colony.c";
	Interfaces[INTERFACE_COLONY].IniFile = "INTERFACES\Colony.ini";
	// Attack Colony And Mine Message
	Interfaces[INTERFACE_ATTACK_MESSAGE].SectionName = "interface\AttackMessage.c";
	Interfaces[INTERFACE_ATTACK_MESSAGE].IniFile = "INTERFACES\AttackMessage.ini";
	// Gold, Silver and Iron Mines
	Interfaces[INTERFACE_MINES].SectionName = "interface\Mines.c";
	Interfaces[INTERFACE_MINES].IniFile = "INTERFACES\Mines.ini";
	// Goods Transfer For Colony Building
	Interfaces[INTERFACE_COLONYBUILDING].SectionName = "interface\ColonyBuilding.c";
	Interfaces[INTERFACE_COLONYBUILDING].IniFile = "INTERFACES\ColonyBuilding.ini";
	// Lugger <--
	
	Interfaces[INTERFACE_CANNONS].SectionName = "interface\cannons.c";
	Interfaces[INTERFACE_CANNONS].IniFile = "INTERFACES\cannons.ini";
	Interfaces[INTERFACE_STORE].SectionName = "interface\store.c";
	Interfaces[INTERFACE_STORE].IniFile = "INTERFACES\store.ini";
	Interfaces[INTERFACE_SHIP_CHOOSE].SectionName = "interface\ship.c";
	Interfaces[INTERFACE_SHIP_CHOOSE].IniFile = "INTERFACES\ship.ini";
	Interfaces[INTERFACE_SHIPYARD].SectionName = "interface\shipyard.c";
	Interfaces[INTERFACE_SHIPYARD].IniFile = "INTERFACES\shipyard.ini";
	Interfaces[INTERFACE_CHARACTER].SectionName = "interface\character.c";
	Interfaces[INTERFACE_CHARACTER].IniFile = "INTERFACES\character.ini";
	Interfaces[INTERFACE_CHARACTER_ALL].SectionName = "interface\character_all.c";
	Interfaces[INTERFACE_CHARACTER_ALL].IniFile = "INTERFACES\character_all.ini";
	Interfaces[INTERFACE_MAINMENU].SectionName = "interface\mainmenu.c";
	Interfaces[INTERFACE_MAINMENU].IniFile = "INTERFACES\mainmenu.ini";
	Interfaces[INTERFACE_SAILSGERALD].SectionName = "interface\SailsGerald.c";
	Interfaces[INTERFACE_SAILSGERALD].IniFile = "INTERFACES\SailsGerald.ini";
	Interfaces[INTERFACE_HIRECREW].SectionName = "interface\hirecrew.c";
	Interfaces[INTERFACE_HIRECREW].IniFile = "INTERFACES\hirecrew.ini";
	//Interfaces[INTERFACE_PASSENGERS].SectionName = "interface\passengers.c";
	//Interfaces[INTERFACE_PASSENGERS].IniFile = "INTERFACES\passengers.ini";
	Interfaces[INTERFACE_CHARACTER_SELECT].SectionName = "interface\selectCharacter.c";
	Interfaces[INTERFACE_CHARACTER_SELECT].IniFile = "INTERFACES\selectCharacter.ini";
	Interfaces[INTERFACE_CREATENOTICE].SectionName = "interface\CreateNotice.c";
	Interfaces[INTERFACE_CREATENOTICE].IniFile = "INTERFACES\CreateNotice.ini";
	//Interfaces[INTERFACE_NATION_SELECT].SectionName = "interface\selectNation.c";
	//Interfaces[INTERFACE_NATION_SELECT].IniFile = "INTERFACES\selectNation.ini";
	Interfaces[INTERFACE_QUESTBOOK].SectionName = "interface\questbook.c";
	Interfaces[INTERFACE_QUESTBOOK].IniFile = "INTERFACES\questbook.ini";
	Interfaces[INTERFACE_TRADEBOOK].SectionName = "interface\tradebook.c";
	Interfaces[INTERFACE_TRADEBOOK].IniFile = "INTERFACES\tradebook.ini";
	Interfaces[INTERFACE_NATIONRELATION].SectionName = "interface\NationRelation.c";
	Interfaces[INTERFACE_NATIONRELATION].IniFile = "INTERFACES\NationRelation.ini";
	Interfaces[INTERFACE_SAVELOAD].SectionName = "interface\save_load.c";
	Interfaces[INTERFACE_SAVELOAD].IniFile = "INTERFACES\save_load.ini";
	Interfaces[INTERFACE_ITEMS].SectionName = "interface\items.c";
	Interfaces[INTERFACE_ITEMS].IniFile = "INTERFACES\items.ini";
	Interfaces[INTERFACE_FORTCAPTURE].SectionName = "interface\fortcapture.c";
	Interfaces[INTERFACE_FORTCAPTURE].IniFile = "INTERFACES\fortcapture.ini";
	Interfaces[INTERFACE_ITEMSBOX].SectionName = "interface\itemsbox.c";
	Interfaces[INTERFACE_ITEMSBOX].IniFile = "INTERFACES\itemsbox.ini";

	Interfaces[INTERFACE_OPTIONSCREEN].SectionName = "interface\option_screen.c";
	Interfaces[INTERFACE_OPTIONSCREEN].IniFile = "INTERFACES\option_screen.ini";

	Interfaces[INTERFACE_ITEMSTRADE].SectionName = "interface\itemstrade.c";
	Interfaces[INTERFACE_ITEMSTRADE].IniFile = "INTERFACES\itemstrade.ini";
	// boal -->
	Interfaces[INTERFACE_FOR_TEST].SectionName = "interface\for_test.c";
	Interfaces[INTERFACE_FOR_TEST].IniFile     = "INTERFACES\for_test.ini";

	Interfaces[INTERFACE_NATION_LEGEND].SectionName = "interface\NationLegend.c";
    Interfaces[INTERFACE_NATION_LEGEND].IniFile = "INTERFACES\NationLegend.ini";

    Interfaces[INTERFACE_COLONY_CAPTURE].SectionName = "interface\ColonyCapture.c";
    Interfaces[INTERFACE_COLONY_CAPTURE].IniFile = "INTERFACES\ColonyCapture.ini";
	// boal <--
	Interfaces[INTERFACE_SALARY].SectionName = "interface\salary.c";
	Interfaces[INTERFACE_SALARY].IniFile = "INTERFACES\salary.ini";

	Interfaces[INTERFACE_NET_FINDGAME].SectionName = "net\interfaces\FindGame.c";
	Interfaces[INTERFACE_NET_FINDGAME].IniFile = "INTERFACES\Net\FindGame.ini";

	Interfaces[INTERFACE_NET_CREATEGAME].SectionName = "net\interfaces\CreateGame.c";
	Interfaces[INTERFACE_NET_CREATEGAME].IniFile = "INTERFACES\Net\CreateGame.ini";

	Interfaces[INTERFACE_NET_BUY].SectionName = "net\interfaces\Buy.c";
	Interfaces[INTERFACE_NET_BUY].IniFile = "INTERFACES\Net\Buy.ini";

	Interfaces[INTERFACE_NET_CHAT].SectionName = "net\interfaces\Chat.c";
	Interfaces[INTERFACE_NET_CHAT].IniFile = "INTERFACES\Net\Chat.ini";

	Interfaces[INTERFACE_NET_GAMESTATE].SectionName = "net\interfaces\GameState.c";
	Interfaces[INTERFACE_NET_GAMESTATE].IniFile = "INTERFACES\Net\GameState.ini";

	Interfaces[INTERFACE_NET_TOPLIST].SectionName = "net\interfaces\TopList.c";
	Interfaces[INTERFACE_NET_TOPLIST].IniFile = "INTERFACES\Net\TopList.ini";

	Interfaces[INTERFACE_NET_CHATSTRING].SectionName = "net\interfaces\ChatString.c";
	Interfaces[INTERFACE_NET_CHATSTRING].IniFile = "INTERFACES\Net\ChatString.ini";

	Interfaces[INTERFACE_NET_PLAYERSETTINGS].SectionName = "net\interfaces\PlayerSettings.c";
	Interfaces[INTERFACE_NET_PLAYERSETTINGS].IniFile = "INTERFACES\Net\PlayerSettings.ini";

	Interfaces[INTERFACE_NET_ENDGAME].SectionName = "net\interfaces\EndGame.c";
	Interfaces[INTERFACE_NET_ENDGAME].IniFile = "INTERFACES\Net\EndGame.ini";

	Interfaces[INTERFACE_NET_NETMENU].SectionName = "net\interfaces\NetMenu.c";
	Interfaces[INTERFACE_NET_NETMENU].IniFile = "INTERFACES\Net\NetMenu.ini";

	Interfaces[INTERFACE_PAPER_MAP].SectionName = "interface\PaperMap.c";
	Interfaces[INTERFACE_PAPER_MAP].IniFile = "INTERFACES\PaperMap.ini";

	//Interfaces[INTERFACE_RANSACK_MAIN].SectionName = "interface\ransack_main.c";
	//Interfaces[INTERFACE_RANSACK_MAIN].IniFile = "INTERFACES\ransack_main.ini";
	Interfaces[INTERFACE_RANSACK_MAIN].SectionName = "interface\transfer_main.c";
	Interfaces[INTERFACE_RANSACK_MAIN].IniFile = "INTERFACES\transfer_main.ini"; // теперь это одна форма, но разные вызовы, тк проверка на море и абордаж нужна

	Interfaces[INTERFACE_TRANSFER_MAIN].SectionName = "interface\transfer_main.c";
	Interfaces[INTERFACE_TRANSFER_MAIN].IniFile = "INTERFACES\transfer_main.ini";

	Interfaces[INTERFACE_MAP].SectionName = "interface\map.c";
	Interfaces[INTERFACE_MAP].IniFile = "INTERFACES\map.ini";
	Interfaces[INTERFACE_COLONY_INFO].SectionName = "interface\ColonyInfo.c";
	Interfaces[INTERFACE_COLONY_INFO].IniFile = "INTERFACES\ColonyInfo.ini";

	Interfaces[INTERFACE_GAMEMENU].SectionName = "interface\game_menu.c";
	Interfaces[INTERFACE_GAMEMENU].IniFile = "INTERFACES\game_menu.ini";
	Interfaces[INTERFACE_GAMEMENU].ENG_IniFile = "INTERFACES\game_menu_eng.ini";

	Interfaces[INTERFACE_DISEASE_ALERT].SectionName = "interface\disease_alert.c";
	Interfaces[INTERFACE_DISEASE_ALERT].IniFile = "INTERFACES\disease_alert.ini";

	Interfaces[INTERFACE_QUICK_SAVE].SectionName = "interface\quick_save.c";
	Interfaces[INTERFACE_QUICK_SAVE].IniFile = "INTERFACES\quick_save.ini";
	// boal -->
	Interfaces[INTERFACE_DEBUGER].SectionName = "interface\debuger.c";
	Interfaces[INTERFACE_DEBUGER].IniFile     = "INTERFACES\debuger.ini";

	Interfaces[INTERFACE_BOAL_BETA].SectionName = "interface\boal_beta.c";
	Interfaces[INTERFACE_BOAL_BETA].IniFile = "INTERFACES\boal_beta.ini";

	Interfaces[INTERFACE_CARDSGAME].SectionName = "interface\boal_cards.c";
	Interfaces[INTERFACE_CARDSGAME].IniFile = "INTERFACES\boal_cards.ini";

	Interfaces[INTERFACE_DICE_GAME].SectionName = "interface\boal_dice.c";
	Interfaces[INTERFACE_DICE_GAME].IniFile = "INTERFACES\boal_dice.ini";

	Interfaces[INTERFACE_FRAMEFORM].SectionName = "interface\boal_frame.c";
	Interfaces[INTERFACE_FRAMEFORM].IniFile     = "INTERFACES\boal_frame.ini";

	Interfaces[INTERFACE_PS_HERO].SectionName = "interface\PsHero.c";
	Interfaces[INTERFACE_PS_HERO].IniFile = "INTERFACES\PsHero.ini";

	Interfaces[INTERFACE_LEAVE_BATTLE].SectionName = "interface\LeaveBattle.c";
	Interfaces[INTERFACE_LEAVE_BATTLE].IniFile = "INTERFACES\LeaveBattle.ini";
	
	Interfaces[INTERFACE_SPEAK].SectionName = "interface\Speak.c";  // Philippe
	Interfaces[INTERFACE_SPEAK].IniFile = "INTERFACES\Speak.ini";
	
	Interfaces[INTERFACE_CONTRATRADE].SectionName = "interface\contraband.c";
	Interfaces[INTERFACE_CONTRATRADE].IniFile = "INTERFACES\contraband.ini";

	Interfaces[INTERFACE_ABOUT].SectionName = "interface\about.c";
	Interfaces[INTERFACE_ABOUT].IniFile = "INTERFACES\about.ini";
	// boal <--
	
	// Warship -->
	// »нтерфейс отличной карты
	Interfaces[INTERFACE_BEST_MAP].SectionName = "interface\MapBest.c";
	Interfaces[INTERFACE_BEST_MAP].IniFile = "INTERFACES\MapBest.ini";
	
	// »нтерфейс отдыха в таверне
	Interfaces[INTERFACE_TAVERN_WAIT].SectionName = "interface\TavernWait.c";
	Interfaces[INTERFACE_TAVERN_WAIT].IniFile = "INTERFACES\TavernWait.ini";
	
	// »нтерфейс закупки товара казначеем
	Interfaces[INTERFACE_GOODS_TRANSFER].SectionName = "interface\GoodsTransfer.c";
	Interfaces[INTERFACE_GOODS_TRANSFER].IniFile = "INTERFACES\GoodsTransfer.ini";
	// Warship <--
	
	// ugeen --> 
	// »нтерфейс атласа карт
	Interfaces[INTERFACE_MAPVIEW].SectionName = "interface\mapview.c";
	Interfaces[INTERFACE_MAPVIEW].IniFile = "INTERFACES\mapview.ini";	
	
	Interfaces[INTERFACE_STORAGE].SectionName = "interface\storage.c";
	Interfaces[INTERFACE_STORAGE].IniFile = "INTERFACES\storage.ini";
	// ugeen <--
	
	//New abilities -->  
	
	//Взлом замков
	Interfaces[INTERFACE_LOCKPICK].SectionName = "interface\lockpicking.c";
    Interfaces[INTERFACE_LOCKPICK].IniFile = "INTERFACES\lockpicking.ini";
	
}