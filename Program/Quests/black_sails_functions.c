/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BS_ReplaceHostessWithMaks()
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Maks";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = "Макс";
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = "";
	sld.beforeGatriGreeting = sld.greeting;
	//sld.greeting = "";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreMaksHostess(string q)
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BS_ReplaceTraderWithGatri()
{
	sld = CharacterFromID("Pirates_trader");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Gatry";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = "Элеонора";
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = "Гатри";
	sld.beforeGatriGreeting = sld.greeting;
	sld.greeting = "Gr_officiant";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreGatriTrader(string q)
{
	sld = CharacterFromID("Pirates_trader");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BSRestoreWorldAlivePause()
{
	//bWorldAlivePause = true;
	pchar.BSFinish = true;
	Log_TestInfo("Линейка ЧП завершена.")
}

void GatriSpeech(string qName)
{
	sld = CharacterFromID("Gatri_temp");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void GatriStoreSpeech(string qName)
{
	sld = CharacterFromID("Pirates_trader");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void FlintSpeech(string qName)
{
	sld = CharacterFromID("Flint");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void SilverSpeech(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void MaksSpeech(string qName)
{
	sld = CharacterFromID("BS_Maks");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void VeinSpeech(string qName)
{
	sld = CharacterFromID("BS_Vein");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void BonySpeech(string qName)
{
	sld = CharacterFromID("BS_Bony");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void RakhamSpeech(string qName)
{
	sld = CharacterFromID("BS_Rakham");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void Gatri_upstairs(string qName)
{
	DoQuestFunctionDelay("GatriSpeech", 0);
}

void Flint_upstairs(string qName)
{
	DoQuestFunctionDelay("FlintSpeech", 0);
}

void Silver_Downstairs(string qName)
{
	DoQuestFunctionDelay("SilverSpeech", 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Черные паруса на горизонте
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BSOnTheHorizon_start(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.dialog.currentnode = "BS_CPNG_3";
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.name = "Элеонора";
	sld.lastname = "Гатри";
	
	for (i = 1; i < 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp"+i, "head_pir", "man", "man", 1, PIRATE, -1, true));
		if (i == 1) sld.model = "huber_fra";
		if (i == 2) sld.model = "mansfield";
		ChangeCharacterAddressGroup(sld, PChar.location, "officers", "reload3_"+i);
		LAi_SetImmortal(sld, true);
	}
}

void BSOnTheHorizon_Flint();
{
	sld = GetCharacter(NPC_GenerateCharacter("Flint", "BS_Flint_0", "man", "man", 999, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_NL_PinnaceofWar47, "Морж", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	sld.name = "Джеймс";
	sld.lastname = "Флинт";
	string sGroup = "Flint_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "капитан Флинт";
	string sColony = "LaVega";
	pchar.questTemp.Flint.City = "PuertoPrincipe";
	int daysQty = 3;
	SetTimerCondition("Flint_SetCity", 0, 0, daysQty, true);
	Map_CreateTrader(sColony, pchar.questTemp.Flint.City, sld.id, daysQty);
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.DeckDialogNode = "BS_CPNG_15";
	LAi_SetImmortal(sld, true);
	sld.Abordage.Enable = false;
	Log_TestInfo("Флинт выходит из " + sColony + "  в " + pchar.questTemp.Flint.City+", дней до прибытия: "+daysQty);
}

void MeetFlintCrew(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest1");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_CPNG_18";
	
	sld = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	sld.name = "Джон";
	sld.lastname = "Сильвер";
	LAi_SetImmortal(sld, true);
	sld = GetCharacter(NPC_GenerateCharacter("BS_Billy", "BS_Billy", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto6");
	sld.name = "Билли";
	sld.lastname = "Бонс";
	LAi_SetImmortal(sld, true);
}

void BSOnTheHorizon_End(string qName)
{
	AddQuestRecord("BSOnTheHorizon", "5");
	CloseQuestHeader("BSOnTheHorizon");
	
	SetFunctionExitFromLocationCondition("BSCourtlyPassions_begin_again", pchar.location, true);
	
	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
	pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1 = "NPC_Death";
	pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1.character ="Flint";
	PChar.quest.BSCourtlyPassions_DontStart.function = "BSCourtlyPassions_DontStart";
	
	pchar.BSCPFlint_talk = true;
}
void BSOnTheHorizon_SeaBattle()
{
	pchar.ContraInterruptWaiting = true;
	
	Group_FindOrCreateGroup("BSOnTheHorizon_SeaBattle");
	Group_SetType("BSOnTheHorizon_SeaBattle", "pirate");
	for (i = 1; i < 7; i++)
	{
		
		sld = GetCharacter(NPC_GenerateCharacter("BSOnTheHorizon_enemyfleet"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, 3, true));
		if (i == 1) 
		{
			sld.Ship.Type = GenerateShipExt(SHIP_FASTFRIGATE, true, sld);
			sld.Ship.Name = "Денуво";
			sld.Name = "Денуво";
			sld.Lastname = "Антитампер";
		}
		if (i == 2) sld.Ship.Type = GenerateShipExt(SHIP_FR_ESSEX, true, sld);
		if (i == 3) sld.Ship.Type = GenerateShipExt(SHIP_FEARLESS, true, sld);
		if (i == 4) sld.Ship.Type = GenerateShipExt(SHIP_ALEXIS, true, sld);
		if (i == 5) sld.Ship.Type = GenerateShipExt(SHIP_NL_FWZP, true, sld);
		if (i == 6) sld.Ship.Type = GenerateShipExt(SHIP_OXFORD, true, sld);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");
		
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSOnTheHorizon_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("BSOnTheHorizon_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		
		//Group_SetPursuitGroup("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSOnTheHorizon_SeaBattle");
		
		Group_SetAddress("BSOnTheHorizon_SeaBattle", "Bermudes", "Quest_ships", "quest_ship_0");	
	}
	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Черные паруса на горизонте --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Куртуазные страсти
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSCourtlyPassions_DontStart(string qName)
{
	DeleteAttribute(pchar, "BSCPFlint_talk");
	BSRestoreWorldAlivePause();
}

void BSCourtlyPassions_begin(string qName)
{
	ref sld, chr;
	
	if(pchar.location == pchar.location.from_sea || HasSubStr(pchar.location,"_town" || HasSubStr(pchar.location,"shore")))
	{
		if (CheckAttribute(pchar, "BSCPFlint_talk") && !bSeaActive)
		{
			sld = CharacterFromID("Flint");
			if (!CheckAttribute(sld, "curtown") || sld.curtown != pchar.location)
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
				sld.dialog.currentnode = "BS_KS_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.curtown = pchar.location;
				LAi_SetImmortal(sld, true);
				
				chr = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
				ChangeCharacterAddressGroup(chr, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
				chr.name = "Джон";
				chr.lastname = "Сильвер";
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", -1);
				LAi_SetImmortal(chr, true);
			}
		}
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_begin_again", pchar.location, true);
	}	
}

void BSCourtlyPassions_begin_again(string _quest)
{
	if(CheckAttribute(pchar, "BSCPFlint_talk"))
	{
		pchar.quest.BSCourtlyPassions_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_begin.function = "BSCourtlyPassions_begin";		
	}	
}

void BSCourtlyPassions_sailor_begin(string qName)
{
	if(pchar.location == "LeFransua_port" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
	{
		BSCourtlyPassions_sailor();
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
	}
}

void BSCourtlyPassions_sailor()
{
	ref sld, chr;
	
	if (CheckAttribute(pchar, "BSCPSailor_talk") && !bSeaActive)
	{
		chr = CharacterFromID("Flint");
		if (!CheckAttribute(chr, "curtown") || chr.curtown != pchar.location)
		{
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Pirate_9", "man", "man", 1, PIRATE, 0, false));
			sld.name 	= "Сандро";
			sld.lastname 	= "Торн";
			sld.greeting = "Teacher_pirat";
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chr.curtown = pchar.location;
			LAi_SetImmortal(sld, true);
		}
	}
	else
	{
		if (CheckAttribute(pchar, "BSCPSilver_talk") && pchar.location == "FortFrance_town")
		{
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("BS_Silver");
			LAi_type_actor_Reset(sld);
			sld.dialog.currentnode = "BS_KS_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chr.curtown = pchar.location;
		}
	}
}

void BSCourtlyPassions_sailor_begin_again(string _quest)
{
	if(CheckAttribute(pchar, "BSCPSailor_talk") || CheckAttribute(pchar, "BSCPSilver_talk"))
	{
		pchar.quest.BSCourtlyPassions_sailor_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_sailor_begin.function = "BSCourtlyPassions_sailor_begin";		
	}	
}

void BSCourtlyPassions_wait(string _quest)
{
	pchar.ContraInterruptWaiting = true;//Заблочить сон и отдых
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1.location = "FortFrance_dungeon";
	PChar.quest.BSCourtlyPassions_dungeon.function = "BSCourtlyPassions_dungeon";
}

void BSCourtlyPassions_dungeon_lockWeapons(string _quest)
{
	ref _location = &locations[reload_location_index];
	LAi_LocationFightDisable(_location, true);
}
	void BSCourtlyPassions_dungeon(string _quest)
{
	LAi_LocationDisableMonGenTimer("FortFrance_dungeon", 3);//Лок спавна скелетов
	DoQuestFunctionDelay("BSCourtlyPassions_dungeon_lockWeapons", 0);
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	sld.name 	= "Чарльз";
	sld.lastname 	= "Вейн";
	ChangeCharacterAddressGroup(sld, "FortFrance_dungeon", "monsters", "monster35");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_27";
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	BSCourtlyPassions_spawn_podsos();
}

void BSCourtlyPassions_spawn_podsos()
{
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.monsters);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (i = 1; i < maxPodsos; i++)
	{
		
		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd) = "NPC_Death";
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd).character = sld.id;
	}
	//PChar.quest.BSCourtlyPassions_kill_podsos.function = "BSCourtlyPassions_kill_podsos";
	
}

void BSCourtlyPassions_kill_podsos(string _quest)
{
	chrDisableReloadToLocation = false;
	Log_testinfo ("killed all");
	LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", true);
	LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
	BSCourtlyPassions_SeaBattle();
}

void BSCourtlyPassions_fleeng(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto34");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "gate_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1.location = "FortFrance_exittown";
	PChar.quest.BSCourtlyPassions_fleeng_1.function = "BSCourtlyPassions_fleeng_1";
}

void BSCourtlyPassions_fleeng_1(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_exittown", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1.location = "Martinique_jungle_01";
	PChar.quest.BSCourtlyPassions_fleeng_2.function = "BSCourtlyPassions_fleeng_2";
}

void BSCourtlyPassions_fleeng_2(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1.location = "Martinique_jungle_02";
	PChar.quest.BSCourtlyPassions_fleeng_3.function = "BSCourtlyPassions_fleeng_3";
}

void BSCourtlyPassions_fleeng_3(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_02", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1.location = "Martinique_jungle_03";
	PChar.quest.BSCourtlyPassions_fleeng_4.function = "BSCourtlyPassions_fleeng_4";
}

void BSCourtlyPassions_fleeng_4(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_03", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1.location = "Shore39";
	PChar.quest.BSCourtlyPassions_fleeng_5.function = "BSCourtlyPassions_fleeng_5";
}

void BSCourtlyPassions_fleeng_5(string _quest)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Vein");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	LAi_ActorGoToLocation(sld, "reload", "sea", "", "", "", "", -1);
	
	string cnd;
	for (i = 2; i < 6; i++)
	{
		
		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd).character = sld.id;
	}
	PChar.quest.BSCourtlyPassions_kill_podsos.function = "BSCourtlyPassions_kill_podsos";
}

void BSCourtlyPassions_SeaBattle()
{
	Group_FindOrCreateGroup("BSCourtlyPassions_SeaBattle");
	Group_SetType("BSCourtlyPassions_SeaBattle", "pirate");
	sld = CharacterFromID("BS_Vein");
	//LAi_SetHP(sld, 20, 20);
	sld.Ship.Type = GenerateShipExt(SHIP_PDN, true, sld);
	FantomMakeCoolestSailor(sld, SHIP_PDN, "Рейнджер", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	Fantom_SetBalls(sld, "war");
	
	LAi_SetImmortal(sld, false);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSCourtlyPassions_SeaBattle", sld.id);
	Group_SetGroupCommander("BSCourtlyPassions_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	Group_SetPursuitGroup("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_SetTaskAttack("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSCourtlyPassions_SeaBattle");
	
	Group_SetAddress("BSCourtlyPassions_SeaBattle", "Martinique", "Quest_ships", "quest_ship_0");	
	
	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1 = "NPC_Death";
	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1.character = sld.id;
	PChar.quest.BSCourtlyPassions_fail_to_board.function = "BSCourtlyPassions_fail_to_board";
	pchar.BSCourtlyPassionsFail = true;
}

void BSCourtlyPassions_final(string _quest)
{
	ref chr;
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Shore39", "goto", "goto3");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_KS_33";
}

void BSCourtlyPassions_finalRoyal(string _quest)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, 0, false));
	sld.name = "Макс";
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_36";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
}

void BSCourtlyPassions_fail_to_board(string _quest)
{
	if (CheckAttribute(pchar, "BSCourtlyPassionsFail"))
	{
		CloseQuestHeader("BSCourtlyPassions");
		AddQuestRecord("BSCourtlyPassions", "9");
		BSRestoreWorldAlivePause();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Куртуазные страсти --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Погоня начинается
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSChaseBegun()
{
	Group_DeleteGroup("BSCourtlyPassions_SeaBattle");
	Group_DeleteGroup("Flint_Group");
	Group_DeleteGroup("BSOnTheHorizon_SeaBattle");
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	sld = CharacterFromID("Flint");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipF";
	Group_AddCharacter("Flint_Group", sld.id);
	Group_SetGroupCommander("Flint_Group", sld.id);
	Fantom_SetBalls(sld, "war");
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	
	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	sld.name 	= "Чарльз";
	sld.lastname 	= "Вейн";
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipV";
	FantomMakeCoolestSailor(sld, SHIP_PDN, "Рейнджер", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	Group_AddCharacter("Flint_Group", sld.id);
	Fantom_SetBalls(sld, "war");
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetTaskAttack("Flint_Group", PLAYER_GROUP);
	Group_LockTask("Flint_Group");
	
	Group_SetAddress("Flint_Group", "Bermudes", "Quest_ships", "quest_ship_8");	
	
	PChar.quest.BSChaseBegun_shore.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_shore.win_condition.l1.location = "Shore_ship1";
	PChar.quest.BSChaseBegun_shore.function = "BSChaseBegun_shore";
}

void BSChaseBegun_shore(string q)
{
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(pchar.location.from_sea, "boat", true);
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto3");
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_PN_1";
	LAi_SetImmortal(sld, true);
	
	chr = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto1");
	chr.name = "Джон";
	chr.lastname = "Сильвер";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
	
	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto2");
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);	
	
	chr = GetCharacter(NPC_GenerateCharacter("BS_Rakham", "BS_Rakham", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto5");
	chr.name = "Джек";
	chr.lastname = "Рэкхэм";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);	
	
	chr = GetCharacter(NPC_GenerateCharacter("BS_Bony", "BS_Bony", "woman", "YokoDias", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto6");
	chr.name = "Энн";
	chr.lastname = "Бони";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BSChaseBegun_shore_fight()
{
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	//makearef(grp, _location.locators.monsters);
	//int maxPodsos = GetAttributesNum(grp);
	string cnd, fnk;
	Group_DeleteGroup("BSChaseBegun_shore_fight");
	Group_FindOrCreateGroup("BSChaseBegun_shore_fight");//создать группу
	Group_SetType("BSChaseBegun_shore_fight", "war");//тип группы
	for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSChaseBegun_shore_fight"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, "Shore_ship1", "reload", "reload1_back"));
		LAi_group_MoveCharacter(sld, "BSChaseBegun_shore_fight");
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		LAi_SetWarriorTypeNoGroup(sld);
		//LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.(cnd) = "NPC_Death";
		//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.(cnd).character = sld.id;
		fnk = "BSChaseBegun_shore_fightRecheck"+i;
		pchar.quest.(fnk).win_condition.(cnd) = "NPC_Death";
		pchar.quest.(fnk).win_condition.(cnd).character = "BSChaseBegun_shore_fight"+sti(i);
		pchar.quest.(fnk).function = "BSChaseBegun_shore_fightReCheck";
		Group_AddCharacter("BSChaseBegun_shore_fight", sld.id);//добавление в группу
	}
	Group_SetGroupCommander("BSChaseBegun_shore_fight", "BSChaseBegun_shore_fight1");
	Group_SetTaskAttack("BSChaseBegun_shore_fight", PLAYER_GROUP);
	Group_SetPursuitGroup("BSChaseBegun_shore_fight", PLAYER_GROUP);
	Group_SetAddress("BSChaseBegun_shore_fight", "Bermudes", "", "");
	Group_LockTask("BSChaseBegun_shore_fight");	
}


void BSChaseBegun_shore_fightReCheck(string qName)
{
	if (!CheckAttribute(pchar, "BSChaseBegun_shore_fightEnd"))
	{
		int n = 1;
		for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
		{
			sld = CharacterFromID("BSChaseBegun_shore_fight"+sti(i));
			if(LAi_IsDead(sld))
			{
				n++;
			}
		}
		if(n >= 8 + MOD_SKILL_ENEMY_RATE * 2)
		{
			for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
			{
				sld = CharacterFromID("BSChaseBegun_shore_fight"+sti(i));
				if(!LAi_IsDead(sld))
				{
					LAi_KillCharacter(sld);
				}
			}
			Group_DeleteGroup("BSChaseBegun_shore_fight");
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_9";
			//DoQuestFunctionDelay("BSChaseBegun_shore_fight_end", 1.5);
			pchar.BSChaseBegun_shore_fightEnd = true;
			PChar.quest.BSChaseBegun_lock_shore.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_shore.win_condition.l1.location = "Bermudes_Cavern";
			PChar.quest.BSChaseBegun_lock_shore.function = "BSChaseBegun_lock_shore";
		}
	}
}

void BSChaseBegun_shore_fight_end(string q)
{
	pchar.BSChaseBegun_shore_fightEnd = true;
	sld = CharacterFromID("BS_Vein");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_9";
	
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
}

void BSChaseBegun_lock_shore(string q)
{
	DeleteAttribute(pchar, "BSChaseBegun_shore_fightEnd")
	LocatorReloadEnterDisable("Bermudes_Cavern", "reload2_back", true);
	InterfaceStates.Buttons.Save.enable = true;
	PChar.quest.BSChaseBegun_dungeon.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_dungeon.win_condition.l1.location = "Bermudes_Dungeon";
	PChar.quest.BSChaseBegun_dungeon.function = "BSChaseBegun_dungeon";
}

void BSChaseBegun_dungeon(string q)
{
	BSCourtlyPassions_spawn_podsos();
	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	
	sld = CharacterFromID("Pirates_Shipyarder");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_13";
	
	LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
}

void BSChaseBegun_town(string q)
{
	chrDisableReloadToLocation = true;
	BS_spawn_dead_podsos();
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "officers", "reload3_1");
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	
	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "officers", "reload3_2");
	LAi_SetStayTypeNoGroup(chr);
	chr.talker = 10;
	chr.dialog.currentnode = "BS_PN_15";
	LAi_SetImmortal(chr, true);	
	
	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "officers", "reload3_3");
	chr.name = "Энн";
	chr.lastname = "Бони";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BS_spawn_dead_podsos()
{
	InterfaceStates.Buttons.Save.enable = false;
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.patrol);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (i = 1; i < maxPodsos; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "patrol", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_KillCharacter(sld);	
		cnd = "l" + i;
	}
	sld = CharacterFromID("Atilla");
	sld.AtillaNode = sld.dialog.currentnode;
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_13_1";
}

void BSChaseBegun_townhall(string q)
{
	chrDisableReloadToLocation = true;
	ref chr;
	sld = CharacterFromID("Jackman");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "Jackman_Defeated";
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "", "");
	
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto2");
	LAi_SetActorType(sld);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto3");
	LAi_SetActorType(chr);
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.dialog.currentnode = "BS_PN_21";
	if (!CheckAttribute(pchar, "BSChaseBegun_townhall_Flint"))	chr.talker = 10;
	
	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);
	
	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);
	
	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto1");
	LAi_SetActorType(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto6");
	LAi_SetActorType(chr);
}

void BSChaseBegun_lock_townhall(string q)
{
	InterfaceStates.Buttons.Save.enable = true;
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
	LocatorReloadEnterDisable("Pirates_townhall", "reload2", true);
	LocatorReloadEnterDisable("Pirates_portoffice", "reload1", true);
	
	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1.location = "Hispaniola1";
	PChar.quest.BSChaseBegun_Hispaniola.function = "BSChaseBegun_Hispaniola";
}

void BSChaseBegun_unlock_townhall()
{
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	LocatorReloadEnterDisable("Pirates_townhall", "reload2", false);
	LocatorReloadEnterDisable("Pirates_portoffice", "reload1", false);
}

void BSChaseBegun_FewDeaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam("Несколько дней спустя...", "", 0.1, 2.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSChaseBegun_FewDeaysLater_Reload", 2.0);
}

void BSChaseBegun_FewDeaysLater_Reload(string q)
{
	ClearIslandShips("SantoDomingo");
    Colonies[FindColony("SantoDomingo")].DontSetShipInPort = true; // не заыть потереть
    Colonies[FindColony("SantoDomingo")].BSChaseBegun = true; // не заыть потереть
	BSChaseBegun_SeaBattle();
	DoReloadCharacterToLocation("Pirates_townhall","goto","goto4");
}

void BSChaseBegun_Hispaniola(string q)
{
	AddQuestRecord("BSChaseBegun", "5");
}

void BSChaseBegun_Fail(string q)
{
	CloseQuestHeader("BSChaseBegun");
	DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
	if (CheckAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun"))
	{
		AddQuestRecord("BSChaseBegun", "7");
		BSChaseBegun_unlock_townhall();
		EraseBSCharacters();
		DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
		BSRestoreWorldAlivePause();
	}
}

void EraseBSCharacters()
{
	sld = CharacterFromID("Flint");	sld.LifeDay = 0;
	RemoveCharacterCompanion(PChar, sld);
	sld = CharacterFromID("gatri_temp");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Vein");	sld.LifeDay = 0;
	RemoveCharacterCompanion(PChar, sld);
	sld = CharacterFromID("BS_Rakham");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Bony");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Silver");	sld.LifeDay = 0;
	sld = CharacterFromID("BSUrka_enemyfleet");	sld.LifeDay = 0;
	sld = CharacterFromID("BSUrka");	sld.LifeDay = 0;
	
	for (i = 1; i < 7; i++)
	{
		sld = CharacterFromID("BSUrka_Curacao_enemyfleet"+i);	sld.LifeDay = 0;
	}
		
}
void BSChaseBegun_EndQuest(string q)
{
	sld = CharacterFromID("Flint");
	RemoveCharacterCompanion(PChar, sld);
	ProcessHullRepair(sld, 100.0);
	ProcessSailRepair(sld, 100.0);
	DeleteAttribute(sld, "ship.blots");
	DeleteAttribute(sld, "ship.sails");
	DeleteAttribute(sld, "ship.masts");
	
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "quest", "quest1");
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "BS_PN_30";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
void BSChaseBegun_SeaBattle()
{
	Group_FindOrCreateGroup("BSChaseBegun_SeaBattle");
	Group_SetType("BSChaseBegun_SeaBattle", "pirate");
	
	Group_DeleteGroup("Flint_Group");
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	ref chr = CharacterFromID("Flint");
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.DeckDialogNode = "BS_PN_30_seabattle";
	Group_AddCharacter("Flint_Group", chr.id);
	Group_SetGroupCommander("Flint_Group", chr.id);
	Fantom_SetBalls(chr, "war");
	LAi_SetImmortal(chr, false);
	chr.AlwaysFriend = true;
	chr.DontRansackCaptain = true;
	chr.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetTaskAttack("Flint_Group", PLAYER_GROUP);
	Group_LockTask("Flint_Group");
	
	//Group_SetAddress("Flint_Group", "Hispaniola1", "Quest_ships", "reload_fort1");	
	Group_SetAddress("Flint_Group", "Hispaniola1", "Quest_ships", "quest_ship_5");	
	
	pchar.quest.BSChaseBegun_Fail.win_condition.c1 = "NPC_Death";
	pchar.quest.BSChaseBegun_Fail.win_condition.c1.character ="Flint";
	PChar.quest.BSChaseBegun_Fail.function = "BSChaseBegun_Fail";
	
	for (i = 1; i < 9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSChaseBegun_SeaBattle"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
		CreatePGG_War(sld, 2, chr);
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");
		
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSChaseBegun_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("BSChaseBegun_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		
		//Group_SetPursuitGroup("BSChaseBegun_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSChaseBegun_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSChaseBegun_SeaBattle");
		
		Group_SetAddress("BSChaseBegun_SeaBattle", "Hispaniola1", "Quest_ships", "quest_ship_1");	
	}
	//sld = CharacterFromID("Flint");
	//LAi_SetImmortal(sld, false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Погоня начинается --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Неуловимая «Урка»
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSUrka_Negril(string q)
{
	AddQuestRecord("BSUrka", "2");
	BS_RestoreMaksHostess("q");
	pchar.BSUrka_Negril = true;
}
	
void BSBons_SeaBattle(bool bonsAdmiral)
{
	string sGroup = "Sea_BSBons0";
	string sScarboro = "";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	for (int i = 0; i < 5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSBons"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, 8, true));
		FantomMakeCoolSailor(sld, SHIP_NL_PinnaceofWar47, "Морж", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
		sld.AlwaysEnemy = true;
		sld.Ship.Type = GenerateShipExt(SHIP_FEARLESS, true, sld);
		
		Group_AddCharacter(sGroup, sld.id);
		if (i == 0) 
		{
			
				Group_SetGroupCommander(sGroup, sld.id);
				if (bonsAdmiral)
				{
					if (!CheckAttribute(pchar, "BSBonsSpawned"))
					{
						FantomMakeCoolestSailor(sld, SHIP_FASTFRIGATE, "Фортуна", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
						sld.Name = "Билли";
						sld.Lastname = "Бонс";
						sld.Model = "BS_Billy";
						sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
						sld.DeckDialogNode = "BS_CPNG_15";
						FaceMaker(sld);
					}
					else
					{
						FantomMakeCoolestSailor(sld, SHIP_BATTLEMANOWAR, "Скарборо", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
						FaceMaker(sld);
						sScarboro = " со 'Скарборо' во главе";
						
						pchar.quest.BSUrka_Scarboro.win_condition.l1 = "NPC_Death";
						pchar.quest.BSUrka_Scarboro.win_condition.l1.character ="BSBons0";
						PChar.quest.BSUrka_Scarboro.function = "BSUrka_Scarboro";
					}
				}
		}
		Group_LockTask(sGroup);
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "охотники на пиратов" + sScarboro;
	}
	Map_CreateFastWarrior("", "BSBons0", 8);
}

void BSUrka_Pirates_town(string q)
{
	chrDisableReloadToLocation = true;
	ref chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "reload", "reload3_back");
	LAi_SetImmortal(chr, true);
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "goto", "goto7");
	LAi_SetImmortal(sld, true);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorTypeNoGroup(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, -1, false));
	sld.name = "Макс";
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_SetImmortal(sld, true);
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1 = "locator";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.location = "Pirates_town";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator_group = "reload";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator = "reload3_back";
	PChar.quest.BSUrka_Pirates_town_residence.function = "BSUrka_Pirates_town_residence";
}

void BSUrka_Pirates_town_residence(string q)
{
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "Pirates_Townhall", "goto", "goto3");
	
	DoReloadCharacterToLocation("Pirates_townhall","goto","goto4");
	pchar.BSChaseBegun_townhall_Flint = true;
	BSChaseBegun_townhall("q");
	DeleteAttribute(pchar, "BSChaseBegun_townhall_Flint");
	
	sld = CharacterFromID("Flint");
	LAi_SetStayTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "BS_NU_18";
	sld.talker = 10;
}

void BSUrka_Pirates_town_Vein(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "quest", "quest1");
	sld.dialog.currentnode = "BS_NU_33_Ya_Ne_Krisa";
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	chrDisableReloadToLocation = true;
}

void BSUrka_Curacao_SeaBattle()
{
	Group_FindOrCreateGroup("BSUrka_Curacao_SeaBattle");
	Group_SetType("BSUrka_Curacao_SeaBattle", "pirate");
	LAi_group_Delete("BSUrka_Curacao_Battle");
	string cnd;
	for (i = 1; i < 7; i++)
	{
		
		sld = GetCharacter(NPC_GenerateCharacter("BSUrka_Curacao_enemyfleet"+i, "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
		if (i == 1) 
		{
			sld.Ship.Type = GenerateShipExt(SHIP_GALEON50, true, sld);
			//sld.Ship.Name = "Денуво";
			//sld.Name = "Денуво";
			//sld.Lastname = "Антитампер";
		}
		if (i == 2) sld.Ship.Type = GenerateShipExt(SHIP_FRIGATE_SAT, true, sld);
		if (i == 3) sld.Ship.Type = GenerateShipExt(SHIP_WARSHIP, true, sld);
		if (i == 4) sld.Ship.Type = GenerateShipExt(SHIP_ALEXIS, true, sld);
		if (i == 5) sld.Ship.Type = GenerateShipExt(SHIP_SUPERBE, true, sld);
		if (i == 6) sld.Ship.Type = GenerateShipExt(SHIP_LINK2, true, sld);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");
		
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSUrka_Curacao_SeaBattle", sld.id);
		LAi_group_MoveCharacter(sld, "BSUrka_Curacao_Battle");
		if (i == 1) Group_SetGroupCommander("BSUrka_Curacao_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		
		//Group_SetPursuitGroup("BSUrka_Curacao_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSUrka_Curacao_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSUrka_Curacao_SeaBattle");
		
		Group_SetAddress("BSUrka_Curacao_SeaBattle", "Curacao", "Quest_ships", "quest_ship_4");	
		
		cnd = "l" + i;
		pchar.quest.BSUrka_Curacao_EndSeaBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSUrka_Curacao_EndSeaBattle.win_condition.(cnd).character ="BSUrka_Curacao_enemyfleet"+sti(i);
	}
	PChar.quest.BSUrka_Curacao_EndSeaBattle.function = "BSUrka_Curacao_EndSeaBattle";
	
	SetFunctionNPCDeathCondition("BSUrka_Curacao_SeaBattleStarted", "BSUrka_Curacao_enemyfleet1", false);
}

void BSUrka_Curacao_SeaBattleStarted(string q)
{
	if (!CheckAttribute(pchar, "BSFinish"))	pchar.LockSeaReload = "На это нет времени. Сперва нужно добить испанскую эскадру.";
}

void BSUrka_Curacao_EndSeaBattle(string q)
{
	LAi_group_Delete("BSUrka_Curacao_Battle");
	Sea_CabinStartNow();
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1          = "location";
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1.location = Get_My_Cabin();
	pchar.quest.BSUrka_Curacao_Cabin.function             = "BSUrka_Curacao_CabinTalk";	
}

void BSUrka_Curacao_CabinTalk(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);	
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_35";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void BSUrka_Curacao_Shore(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);	
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_37";
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smugglerload");
	LAi_SetStayType(sld);
	sld.talker = 10;
	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_Prisoner", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, 3, true));
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler01");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler02");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
	
}

void BSUrka_BonyHits(string qName)
{
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorTurnToCharacter(chr, sld);
	LAi_ActorAnimation(chr, "Shot", "", 1.9);
    DoQuestFunctionDelay("BSUrka_BonyHits_1", 0.8);
}
void BSUrka_BonyHits_1(string qName)
{
	DialogExit();
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_KillCharacter(sld);
    DoQuestFunctionDelay("BSUrka_BonyHits_2", 0.25);
}
void BSUrka_BonyHits_2(string qName)
{
	ref chr = CharacterFromId("BS_Bony");
	Lai_SetStayType(chr);
	
	sld = CharacterFromID("BS_Vein");
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode   = "BS_NU_41";
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialog", 1.3);
	
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, false);
}
void BSUrka_Found(string qName)
{
	AddQuestRecord("BSUrka", "8");
}

void BSUrka_PlaceUrka()
{
	//Урка
	Group_FindOrCreateGroup("BSUrka");
	Group_SetType("BSUrka", "pirate");
	string cnd;
		
	sld = GetCharacter(NPC_GenerateCharacter("BSUrka", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));

	sld.Ship.Type = GenerateShipExt(SHIP_GALEON50, true, sld);
	sld.Ship.Name = "Урка де Лима";
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

	sld.LockBoat = true;
	sld.ShipEnemyDisable = true;
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka", sld.id);
	LAi_group_MoveCharacter(sld, "BSUrka");
	Group_SetGroupCommander("BSUrka", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	
	int iMast = 0;
	int iMastQty = 4;
	string sMast = "";
	for(int m=1; m <= iMastQty; m++)
	{
		sMast = "mast" + m;
		sld.ship.masts.(sMast) = true;
	}
	sld.ship.HP = sti(sld.ship.HP) / 4;
	SetCrewQuantity(sld, 0);
	LAi_SetImmortal(sld, true);
	
	Group_SetAddress("BSUrka", "Cumana", "quest_ships", "quest_ship_9");	
	
	//Самовар
	Group_FindOrCreateGroup("BSUrka_SeaBattle");
	Group_SetType("BSUrka_SeaBattle", "pirate");
		
	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_enemyfleet", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
	sld.Ship.Type = GenerateShipExt(SHIP_SP_SANFELIPE, true, sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	Fantom_SetBalls(sld, "war");
	
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka_SeaBattle", sld.id);
	Group_SetGroupCommander("BSUrka_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	Group_SetTaskAttack("BSUrka_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSUrka_SeaBattle");
	
	Group_SetAddress("BSUrka_SeaBattle", "Cumana", "Quest_ships", "quest_ship_9");	
	
	SetFunctionNPCDeathCondition("BSUrka_SeaBattleEnded", "BSUrka_enemyfleet", false);
}

void BSUrka_SeaBattleEnded(string q)
{
	AddQuestRecord("BSUrka", "8_1");
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1          = "location";
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1.location = "Shore20";
	pchar.quest.BSUrka_ShoreBattle.function             = "BSUrka_ShoreBattle";	
	
	AddGeometryToLocation("Shore20", "smg");
}

void BSUrka_ShoreBattle(string q)
{
	ref chr;
	string attrName, sLoc, sLoc_2, relation;
	int i, iRnd, iNation;
 
	relation = LAI_GROUP_PLAYER;
	sLoc = "Shore20";
	iNation = SPAIN;
	
	chrDisableReloadToLocation = true;
	//our
	chr = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);
	
	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation); 
	
	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);
	
	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation); 
	
	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation); 
	
	iRnd = 15 - GetOfficersQuantity(pchar);
	PChar.GenQuestFort.FarLocator = false;
	sLoc = LAi_FindNPCLocator("officers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 3 != 0)
		{
		chr = SetFantomDefenceForts("officers", sLoc, PIRATE, relation);
		}
		else
		{
		chr = SetFantomDefenceForts("enc02", "",PIRATE, relation);
		}
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	Pchar.GenQuestFort.FarLocator = true;	

	//enemy
	iRnd = 80;
	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("goto");
	sLoc_2 = LAi_FindNPCLocator("smugglers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 2 == 0)
		{
		chr = SetFantomDefenceForts("goto", sLoc, iNation, "BSUrkaShore");
		}
		else
		{
			chr = SetFantomDefenceForts("smugglers", sLoc_2, iNation, "BSUrkaShore");
		}
		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	//натравим.
	LAi_group_SetHearRadius("BSUrkaShore", 100.0);
	LAi_group_FightGroupsEx("BSUrkaShore", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);	
	LAi_group_FightGroupsEx("BSUrkaShore", relation, true, Pchar, -1, false, false);	

	LAi_group_SetCheckFunction("BSUrkaShore", "BSUrka_AfterShoreBattle");
	
	LAi_SetFightMode(pchar, true);
}

void BSUrka_AfterShoreBattle()
{
	//chrDisableReloadToLocation = false;
	RemoveGeometryFromLocation("Shore20", "smg");
	
	ref chr, rGroup;
	string sGroup;
	
	chr = CharacterFromID("BSUrka");
	chr.LifeDay = 0;
	chr = CharacterFromID("Flint");
	chr.dialog.currentnode   = "BS_NU_45";
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
}

void BSUrka_Scarboro(string q)
{
	AddQuestRecord("BSUrka", "11");
}

void BSUrka_Fail(string q)
{
	AddQuestRecord("BSUrka", "12");
	CloseQuestHeader("BSUrka");
	BSChaseBegun_unlock_townhall();
	PChar.quest.BSChaseBegun_Fail.over = "yes";
	PChar.quest.BSUrka_Fail1.over = "yes";
	PChar.quest.BSUrka_Fail2.over = "yes";
	PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
	PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
	EraseBSCharacters();
	BSRestoreWorldAlivePause();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Неуловимая «Урка» --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////