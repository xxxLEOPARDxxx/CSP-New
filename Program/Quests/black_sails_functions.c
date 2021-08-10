
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Черные паруса на горизонте
/////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	sld = GetCharacter(NPC_GenerateCharacter("Flint", "BS_Flint", "man", "man", 999, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_NL_PinnaceofWar47, "Морж", CANNON_TYPE_CANNON_LBS24, 70, 70, 70);
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
	
	sld = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man2_ab", 999, PIRATE, -1, true));
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
}
void BSOnTheHorizon_SeaBattle()
{
	Group_FindOrCreateGroup("BSOnTheHorizon_SeaBattle");
	Group_SetType("BSOnTheHorizon_SeaBattle", "pirate");
	for (i = 1; i < 7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSOnTheHorizon_enemyfleet"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, -1, true));
		if (i == 1) sld.Ship.Type = GenerateShipExt(SHIP_FASTFRIGATE, true, sld);
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
		
		Group_SetPursuitGroup("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSOnTheHorizon_SeaBattle");
		
		Group_SetAddress("BSOnTheHorizon_SeaBattle", "Martinique", "Quest_ships", "quest_ship_7");	
	}
	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Черные паруса на горизонте --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////