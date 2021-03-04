
//////////////////////////////////////////////////////////////////////
//	Линейка Виспер	начало
//////////////////////////////////////////////////////////////////////
void Whisper_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.WhisperTutorial = true;
    Pchar.questTemp.WhisperFuture = true;
    Pchar.BaseNation = SPAIN;
    //fix перков флагов
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
	DeleteAttribute(Pchar, "perks.list.FlagEng");
    SetCharacterPerk(Pchar, "FlagPir");
    Flag_SPAIN();

    //Обираем до нитки
    RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
    RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
    RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
    DeleteAttribute(Pchar, "items");
//    DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
	//Одеваемся подходящим образом
	GiveItem2Character(pchar, "blade14");
	EquipCharacterByItem(pchar, "blade14");
	GiveItem2Character(pchar, "pistol7shotgun");
	EquipCharacterByItem(pchar, "pistol7shotgun");
    TakeNItems(Pchar, "GunPowder", 99);
    TakeNItems(Pchar, "bullet", 99);
	TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
    SetCharacterPerk(Pchar, "GunProfessional");
	Pchar.model="PGG_Whisper_5_NoHat";
	
	//Костыль для перезарядки пистолета и смены модели ГГ, хз, можно ли проще сделать
	DoReloadCharacterToLocation(pchar.location,"reload","reload2_back");
	
	//Запретить выход из локации
	chrDisableReloadToLocation = true;
	//Заблокировать меню персонажа
	bDisableCharacterMenu = true;
	//и фасттревел
	InterfaceStates.DisFastTravel = true;
	//Виспер недоступна испанская линейка
	LockQuestLine(characterFromId("spa_guber"));
	
	//Вступительный монолог
	pchar.questTemp.Whisper.Entered_Dungeon = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);

	//worldMap.date.year = 2065;
    //Environment.date.month = 7;
    //Environment.date.day = 3;
	
	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);
		if(sld.FaceId == 487)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			LAi_KillCharacter(sld);
		}
		if(sld.FaceId == 535)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			LAi_KillCharacter(sld);
		}
	}
	
	//Спавним роботов
	for (int i = 0; i < 10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Robot"+sti(i), "Terminator", "Terminator_Sex", "Terminator", 55, PIRATE, 0, false));
		if (rand (1)==0) FantomMakeCoolFighter(sld, 1, 20, 20, "katar", "", 80);
		else FantomMakeCoolFighter(sld, 1, 20, 20, "blade14", "", 80);
		LAi_SetHP(sld, 30.0, 30.0);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;
	}
	sld = characterFromID("Robot0");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster32");
	sld = characterFromId("Robot1");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster31");
	sld = characterFromId("Robot2");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster5");
	sld = characterFromId("Robot3");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster8");
	sld = characterFromId("Robot4");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster6");	
	sld = characterFromId("Robot5");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster11");
	sld = characterFromId("Robot6");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster17");
	sld = characterFromId("Robot7");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster18");
	sld = characterFromId("Robot8");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster19");
	sld = characterFromId("Robot9");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster9");
    
	PChar.quest.WhisperScientist.win_condition.l1 = "locator";
	PChar.quest.WhisperScientist.win_condition.l1.location = "Bermudes_Dungeon";
	PChar.quest.WhisperScientist.win_condition.l1.locator_group = "box";
	PChar.quest.WhisperScientist.win_condition.l1.locator = "box1";
	PChar.quest.WhisperScientist.function = "WhisperScientist";
}

void WhisperScientist(string qName)
{
	pchar.questTemp.Whisper.Near_Chest = true;	
	PlayVoice("interface\important_item.wav");
	StartActorSelfDialog("First time");
	sld = GetCharacter(NPC_GenerateCharacter("CrazyScientist", "CCS_Mechanic", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 1, 20, 20, "", "", 80);
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster25");
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	//Добавить звуки
	Group_FindOrCreateGroup("Scientist");
	Group_AddCharacter("Scientist", sld.id);
    LAi_SetActorType(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	LAi_SetHP(sld, 5.0, 5.0);
	LAi_SetImmortal(sld, true);
	sld.LifeDay = 0;
	
	sld = GetCharacter(NPC_GenerateCharacter("FinalBot", "Terminator", "Terminator_Sex", "Terminator", 55, PIRATE, 0, false));
	FantomMakeCoolFighter(sld, 1, 20, 20, "katar", "pistol7", 80);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "item", "duhi1");
	
}

void WhisperTeleport(string qName)
{
	pchar.questTemp.WhisperLine = false;
	sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_Cap", "PGG_Rozencraft", "man", "man", 1, PIRATE, -1, true));
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.dialog.currentnode = "First time";
	sld.name = "Эрнан";
	sld.lastname = " Эстебан";
	//sld.greeting = "cit_common";
	//Добавить звуки
    LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	
	Group_FindOrCreateGroup("wl_Pirate");
	Group_AddCharacter("wl_Pirate", sld.id);
	
	for (i = 0; i < 11; i++)
	{
		if (i !=4 && i !=5)
		{
			sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+sti(i));
			Group_AddCharacter("wl_Pirate", sld.id);
			LAi_SetWarriorType(sld);
			sld.LifeDay = 0;
		}
	}
	
}


void WhisperHold(string qName)
{
    //chrDisableReloadToLocation = true;
    //InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;

	//LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	//InterfaceStates.Buttons.Save.enable = 0;
	
	//Возвращаем все после плена
    LAi_SetCurHPMax(Pchar);
    LAi_SetPlayerType(Pchar);
    //Рабство
    LAi_SetImmortal(Pchar, false);
    DeleteAttribute(Pchar, "items");
    DeleteAttribute(Pchar, "equip");
	
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    Pchar.money = 0;

	bDisableCharacterMenu = false;

    DoReloadCharacterToLocation("My_Deck", "rld", "aloc1");
	DoQuestFunctionDelay("WhisperHoldInit", 1.5);
	
}


void WhisperHoldInit(string qName)
{
    //Передаем нашу экипировку пирату
	sld = CharacterFromID("wl_Pirate_Cap");
	ChangeCharacterAddressGroup(sld, "My_Deck", "reload", "reload1");
	GiveItem2Character(sld, "blade14");
	EquipCharacterByItem(sld, "blade14");
	GiveItem2Character(sld, "pistol7shotgun");
	EquipCharacterByItem(sld, "pistol7shotgun");
    TakeNItems(sld, "GunPowder", 99);
    TakeNItems(sld, "bullet", 99);
	
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	LAi_SetImmortal(sld, true);
	
	
}

void WhisperLine_Inquisition(string qName)
{	
	DoReloadCharacterToLocation("Santiago_Incquisitio","reload","reload1");
	DoQuestFunctionDelay("WhisperLine_Cage", 1.2);
}
void WhisperLine_Cage(string qName)
{	
	TeleportCharacterToPos(pchar, -5.36, -1.96, -0.97);
	
	bDisableLandEncounters = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "priest", "man", "man", 10, SPAIN, -1, false));
   	sld.name 	= "Антониу";
    sld.lastname = "де Соуза";
	sld.model.animation = "man2";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	sld.greeting = "Gr_padre";
    LAi_SetHuberType(sld);
    LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
    ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", "goto5");
	
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    //LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
	
}

void WhisperLine_DeSouzaHits(string qName)
{	
	sld = characterFromId("AntonioDeSouza");
	LAi_SetActorTypeNoGroup(PChar);
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorTurnToCharacter(pchar, sld);
	switch (rand(2))
	{
		case 0:
			LAi_ActorAnimation(sld, "attack_fast_"+sti(rand(2)+1), "", 0.6);
		break;
		case 1:
			LAi_ActorAnimation(sld, "attack_force_"+sti(rand(3)+1), "", 0.6);
		break;
		case 2:
			LAi_ActorAnimation(sld, "attack_break_1", "", 0.6);
		break;
	}	
	DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 0.5);
}

void WhisperLine_DeSouzaHits_1(string qName)
{	
	LAi_ActorAnimation(pchar, "hit_attack_"+sti(rand(2)+1), "WhisperLine_DeSouzaHits_2", 0.1);
    DoQuestFunctionDelay("WhisperLine_DeSouzaHits_2", 0.5);
}

void WhisperLine_DeSouzaHits_2(string qName)
{	
	sld = characterFromId("AntonioDeSouza");
	LAi_SetStayType(sld);
	
	if (pchar.Whisper.DeSouzaHits == 0)
	{
		LAi_SetActorTypeNoGroup(PChar);
		DoQuestFunctionDelay("WhisperLine_DeSouzaSpeaks", 0.5);
	}
	else
	{
		pchar.Whisper.DeSouzaHits = sti(pchar.Whisper.DeSouzaHits)-1;
		DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
	}
}
void WhisperLine_DeSouzaSpeaks(string qName)
{	
	sld = characterFromId("AntonioDeSouza");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    //LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
}

void WhisperLine_IncqGuard(string qName)
{	
	for (i=1; i<=4; i++)
	{
		sld = characterFromId("IncqGuard_"+i);
		if (sld.Dialog.Filename == "Incquistors.c")
		{
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);
			if (LAi_FindNearestLocator("soldiers", locx, locy, locz) == "soldier1")
			{
				float locx, locy, locz;
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
				sld.dialog.currentnode = "IncqGuard";
				LAi_SetActorTypeNoGroup(sld);
				LAi_type_actor_Reset(sld);
				//LAi_ActorDialog(sld, pchar, "", 20.0, 0);
				SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
				LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
				sld.LifeDay = 0;
			}
		}
	}
}

void WhisperIncqAlarm(string qName)
{	
	LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
}
void WhisperEscape(string qName)
{	
	ChangeCharacterNationReputation(pchar, 2, -15);
	if (!CheckAttribute(pchar, "Whisper.Escaped"))
	{
		DoReloadCharacterToLocation("Santiago_ExitTown","reload","reload3");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", true);
		LocatorReloadEnterDisable("Havana_ExitTown", "reload4", true);
		
		pchar.Whisper.Escaped = true;

		PChar.quest.WhisperPirateTown.win_condition.l1 = "location";
		PChar.quest.WhisperPirateTown.win_condition.l1.location = "PuertoPrincipe_town";
		PChar.quest.WhisperPirateTown.function = "WhisperPirateTown";
	}
}

void WhisperPirateTown(string qName)
{	
	sld = GetCharacter(NPC_GenerateCharacter("NineFingers", "PGG_Alex_blade_0", "man", "man", 10, PIRATE, -1, false));
   	sld.name 	= "Девятипалый Билл";
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade19");
	EquipCharacterByItem(sld, "blade19");
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto5");
	
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
}

void WhisperPirateTownGetHat(string qName)
{	
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload2", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload4", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload5", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload6", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload7", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload8", true);
	PlayVoice("VOICE\Russian\EvilPirates02.wav");
	SetLocationCapturedState("PuertoPrincipe_town", false); 	
}
void WhisperPirateTownGetHat_part_1(string qName)
{	
	//PlayVoice("VOICE\Russian\EvilPirates02.wav");
	sld = characterFromID("NineFingers");
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);

	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload2", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload3", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload4", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload5", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload6", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload7", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload8", false);

	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", true);

	string cnd;
	for (int i = 0; i < 10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("IncqSoldier_"+sti(i), "sold_spa_"+(rand(7)+1), "man", "man", 5, SPAIN, 0, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);	
		cnd = "l" + i;
		pchar.quest.WhisperAfterTownBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.WhisperAfterTownBattle.win_condition.(cnd).character ="IncqSoldier_"+sti(i);
		LAi_SetImmortal(sld, true);
		
		sld = GetCharacter(NPC_GenerateCharacter("PirateTownDefender_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 5, PIRATE, 0, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
		sld.dialog.currentnode = "Pirateguard";
		LAi_SetImmortal(sld, true);
		
	}
	sld = characterFromID("IncqSoldier_0");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item7");
	sld = characterFromID("IncqSoldier_1");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item10");
	sld = characterFromID("IncqSoldier_2");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item8");
	sld = characterFromID("IncqSoldier_3");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item11");
	sld = characterFromID("IncqSoldier_4");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item13");
	sld = characterFromID("IncqSoldier_5");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item14");
	sld = characterFromID("IncqSoldier_6");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item15");
	sld = characterFromID("IncqSoldier_7");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item16");
	sld = characterFromID("IncqSoldier_8");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item6");
	sld = characterFromID("IncqSoldier_9");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item5");
	sld = characterFromID("PirateTownDefender_0");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_2");
	sld = characterFromID("PirateTownDefender_1");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_1");
	sld = characterFromID("PirateTownDefender_2");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_3");
	sld = characterFromID("PirateTownDefender_3");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "rld", "aloc0");
	sld = characterFromID("PirateTownDefender_4");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item2");
	sld = characterFromID("PirateTownDefender_5");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item1");
	sld = characterFromID("PirateTownDefender_6");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
	sld = characterFromID("PirateTownDefender_7");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item9");
	
	pchar.quest.WhisperAfterTownBattle.function = "WhisperAfterTownBattle";
}

void WhisperPirateTownBattle(string qName)
{	
	SetLocationCapturedState("PuertoPrincipe_town", false);
	DoQuestFunctionDelay("WhisperPirateTownGetHat_part_1", 0.1);
}
void WhisperKillNineFingers(string qName)
{	
	sld = characterFromID("NineFingers");
	DeleteAttribute(sld, "items");
    DeleteAttribute(sld, "equip");
	GiveItem2Character(sld, "Map_bad");
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	LAi_KillCharacter(sld);
}
void WhisperPirateTownBattleMortality()
{	
	for (int i = 0; i < 10; i++)
	{
		sld = characterFromID("IncqSoldier_"+sti(i));
		LAi_SetImmortal(sld, false);
		sld = characterFromID("PirateTownDefender_"+sti(i));
		LAi_SetImmortal(sld, false);
	}
}

void WhisperAfterTownBattle(string qName)
{	
	pchar.questTemp.Whisper.AfterTownBattle = true;
	LAi_SetFightMode(PChar, false);
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", true);
	LAi_group_Delete("wl_TownDefenders");

}

void WhisperMeetCrew(string qName)
{	
	LAi_group_Delete("wl_TownDefenders");
	
	sld = GetCharacter(NPC_GenerateCharacter("Wh_Jack", "PGG_HuanTubercul", "man", "man", 5, PIRATE, -1, false));
   	sld.name 	= "Джек";
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
	LAi_SetHP(sld, 200.0, 200.0);
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "officers", "reload1_1");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld,pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
	
	
	sld = GetCharacter(NPC_GenerateCharacter("Wh_Jim", "PGG_Doggerty", "man", "man", 5, PIRATE, -1, false));
   	sld.name 	= "Джим";
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	LAi_SetHP(sld, 250.0, 250.0);
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "goto", "goto7");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	sld.LifeDay = 0;
	
	for(i=1; i < 5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Wh_Crew"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 5, PIRATE, -1, false));
		LAi_SetHP(sld, 250.0, 250.0);
		//sld.greeting = "Gr_padre";
		ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "enc03", "enc03_0"+sti(i));
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		sld.LifeDay = 0;
	}
	
}
void WhisperJimTalk(string qName)
{	
	sld = CharacterFromID("Wh_Jack");
	Dead_DelLoginedCharacter(sld);
	sld = characterFromID("Wh_Jim");
	//sld.greeting = "Gr_padre";
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
}

void WhisperPlaceSmugglersOnShore(string LocationId)
{
	ref Smuggler, player;
	int RandCounter;
	int i;
	
	player = GetMainCharacter();

	string Model;
	
	player.GenQuest.Smugglers_Group = "Smugglers_1";
    LAi_group_Register(player.GenQuest.Smugglers_Group);
    
	for (i = 1; i <= 6; i++)
    {
        Model = "pirate_" + (rand(9)+1);
		Smuggler = GetCharacter(NPC_GenerateCharacter("W_Smug0" + i, Model, "man", "man", 5, PIRATE, -1, true)); // 4 дн¤, потом сами пропадут
		SetFantomParam(Smuggler);
		LAi_SetWarriorTypeNoGroup(Smuggler);
		LAi_warrior_DialogEnable(Smuggler, true);
		LAi_warrior_SetStay(Smuggler, true);
		Smuggler.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
		Smuggler.Dialog.CurrentNode = "Smuggler";
		Smuggler.greeting = "Gr_Smuggler_OnShore";
		LAi_SetImmortal(Smuggler, true);
		LAi_group_MoveCharacter(Smuggler, player.GenQuest.Smugglers_Group);
		if (i < 3) ChangeCharacterAddressGroup(Smuggler, LocationID, "Smugglers", "Smuggler0" + i);
		else
		{
			int rando = rand(3);
			switch (rando)
			{
				case 0: rando = 1; break;
				case 1: rando = 1; break;
				case 2: rando = 2; break;
				case 3: rando = 3; break;
			}
			ChangeCharacterAddressGroup(Smuggler, LocationID, "Smugglers", "Smuggler0"+rando);
		}		
    }
	
	AddGeometryToLocation(LocationID, "smg");
	
	LAi_group_SetRelation(LAI_GROUP_PLAYER, player.GenQuest.Smugglers_Group, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(player.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_NEITRAL); // патруль на берегу

	//SetTimerCondition("Rand_Smuggling", 0, 0, 4, false);  // через 4 дн¤ всех убрать
}

void WhisperRemoveSmugglersFromShore()
{
	ref Smuggler;
	int RandCounter, i, cn;
	string sLoc = "Shore58";

	RemoveGeometryFromLocation(sLoc, "smg");

	for (i = 1; i <= 6; i++) //eddy
	{
		cn = GetCharacterIndex("W_Smug0"+i);
		if (cn != -1)
		{
			characters[cn].lifeDay = 0;
		}
	}
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "CoastalGuards", LAI_GROUP_NEITRAL);
}

void WhisperChinaman(string qName)
{
	Sea_CabinStartNow();
	
	pchar.quest.WhisperChinamanCapSpeaks.win_condition.l1          = "location";
	pchar.quest.WhisperChinamanCapSpeaks.win_condition.l1.location = Get_My_Cabin();
	pchar.quest.WhisperChinamanCapSpeaks.function             = "WhisperChinamanCapSpeaks";	
}

void WhisperChinamanCapSpeaks(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("W_Chinaman", "PGG_Longway", "man", "man", 5, PIRATE, -1, false));
	sld.greeting = "GR_longway";
	//PlayVoice("Voice\Russian\Longway-01.wav");
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "Лонг";
    sld.lastname = "Вэй";
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "aloc1");
	
	sld = GetCharacter(NPC_GenerateCharacter("W_ChinamanGuard", "pirate_10", "man", "man", 5, PIRATE, 0, false));
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "Хуан";
    sld.lastname = "";
	sld.greeting = "Gr_Officer";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");	
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}
void WhisperChinamanSpeaks(string qName)
{
	sld = characterFromID("W_Chinaman");
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}
void WhisperChinamanCapSpeaksAgain(string qName)
{
	sld = characterFromID("W_ChinamanGuard");
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}

void WhisperSmugglingPatrol()
{
	ref CoastGuard;
	int i;
	int iNation = 1;// Нация патруля
	string Model;
	
	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		CoastGuard = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE), iNation, 3, true)); // 3 дня, потом сами пропадут
		SetFantomParam(CoastGuard);
		SelectCoastalGuardShip(CoastGuard);
		CoastGuard.AlwaysEnemy = true;
		CoastGuard.DontRansackCaptain = true;
		CoastGuard.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Coastal_Guards", CoastGuard.id);
		SetCharacterRelationBoth(sti(CoastGuard.index), GetMainCharacterIndex(), RELATION_ENEMY);
		//if (makeint(pchar.rank) < 6 && i == 1 && GetCompanionQuantity(pchar) == 1) break;
		if (makeint(pchar.rank) < 9 && i == 2 && GetCompanionQuantity(pchar) < 3) break;
    }
	Group_SetGroupCommander("Coastal_Guards", "Coastal_Captain01");
	Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
	Flag_PIRATE();
}

void WhisperHuntersCaveEntrance(string qName)
{
	Group_FindOrCreateGroup("DeSouzaHunter");
	
	chrDisableReloadToLocation = true;
	string cnd;
	for (int i = 1; i <= 7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", 8, PIRATE, 0, true));
		//SetFantomParamHunter(sld);
		LAi_SetHP(sld, 50+sti(pchar.rank)*10.0, 50+sti(pchar.rank)*10.0);
		LAi_SetActorType(sld);
		//LAi_warrior_SetStay(sld, true);
		Group_AddCharacter("DeSouzaHunter", sld.id);
		sld.LifeDay = 0;
		
		cnd = "l" + i;
		pchar.quest.WhisperAfterHuntersCaveBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.WhisperAfterHuntersCaveBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);
		if (i < 5)
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster3");
		}
		else
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster1");
		}
		if (i == 1)
		{
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
			ChangeCharacterAddressGroup(sld, PChar.location, "enc01", "enc01_03");
			sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
			sld.dialog.currentnode = "DeSouzaHunter";
	        sld.greeting = "Gr_HUNTER";
		}
		LAi_SetImmortal(sld, true);
	}
	
	sld = GetCharacter(NPC_GenerateCharacter("W_Lejitos", "PGG_Lejitos_GPK", "man", "man", 1, PIRATE, -1, true));
	sld.name = "Элихио";
	sld.lastname = "Лехито";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "enc01", "enc01_02");
	LAi_SetImmortal(sld, true);
	SetSelfSkill(sld, 45, 45, 75, 45, 35);
	SetShipSkill(sld, 50, 25, 20, 20, 20, 25, 70, 25, 15);
	SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 15;
	LAi_SetHP(sld, 300.0, 300.0);
	
	GiveItem2Character(sld, "topor_01");
	EquipCharacterByItem(sld, "topor_01");
	GiveItem2Character(sld, "cirass2");
	EquipCharacterbyItem(sld, "cirass2");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "pistol2")
	TakeNItems(sld, "indian18", 1);
	
	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	
	
	PChar.quest.WhisperAfterHuntersCaveBattle.function = "WhisperAfterHuntersCaveBattle";
	
}

void WhisperAfterHuntersCaveBattle(string qName)
{
	chrDisableReloadToLocation = false;
	if(!LAi_IsDead(CharacterFromID("W_Lejitos")))
	{
		sld = characterFromID("W_Lejitos");
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	}
	WhisperDeSouzaSeaBattle();
}

void WhisperDeSouzaSeaBattle()
{
	sld = CharacterFromID("AntonioDeSouza")
	SetFantomParamHunter(sld);
	sld.Ship.Type = GenerateShipExt(SHIP_GALEON_H, true, sld);
	sld.Ship.name = "Кара Господня";
	LAi_SetImmortal(sld, false);
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(sld);
	
	sld.SaveItemsForDead = true;
	TakeNItems(sld, "DeSouzaCross", 1);
	
	SetSelfSkill(sld, 50, 50, 50, 50, 50);
	SetShipSkill(sld, 40, 40, 40, 40, 40, 40, 40, 40, 40);
	//SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 15;
	LAi_SetHP(sld, 400.0, 400.0);

    SetCharacterGoods(sld,GOOD_FOOD,500);
    SetCharacterGoods(sld,GOOD_BALLS,1000);
    SetCharacterGoods(sld,GOOD_GRAPES,1000);
    SetCharacterGoods(sld,GOOD_KNIPPELS,1000);
    SetCharacterGoods(sld,GOOD_BOMBS,1000);
    SetCharacterGoods(sld,GOOD_POWDER,3000);
    SetCharacterGoods(sld,GOOD_PLANKS,150);
    SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
    SetCharacterGoods(sld,GOOD_RUM,200);
    SetCharacterGoods(sld,GOOD_WEAPON,600);
			
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_FindOrCreateGroup("DeSouza");
	Group_AddCharacter("DeSouza", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetGroupCommander("DeSouza", "AntonioDeSouza");

	//Group_SetPursuitGroup("DeSouza", PLAYER_GROUP);
	Group_SetTaskAttack("DeSouza", PLAYER_GROUP);
	Group_LockTask("DeSouza");
	
	Group_SetAddress("DeSouza", "SentMartin", "Quest_ships", "quest_ship_7");
	SetFunctionNPCDeathCondition("WhisperDeSouza_Is_Dead", "AntonioDeSouza", false);
}

void WhisperDeSouza_Is_Dead(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.DeSouzaTalked"))
	{
		AddQuestRecord("WhisperQuestline", "3");
		CloseQuestHeader("WhisperQuestline");
	}
}

void WhisperWarDog_Is_Dead(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.NanoCostume"))
	{
		AddQuestRecord("WhisperQuestline", "3");
		CloseQuestHeader("WhisperQuestline");
	}
}

void WhisperWarDogSeaBattle()
{
	sld = CharacterFromID("wl_Pirate_Cap")
	sld.Ship.Type = GenerateShipExt(SHIP_WH_CORVETTE_QUEST, true, sld);
	sld.Ship.name = "Пёс Войны";
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantityFull(sld);
	
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld, "cirass5");
	EquipCharacterbyItem(sld, "cirass5")
	
	SetSelfSkill(sld, 60, 60, 60, 60, 60);
	SetShipSkill(sld, 50, 50, 50, 50, 50, 50, 50, 50, 50);
	//SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 25;
	LAi_SetHP(sld, 500.0, 500.0);

    SetCharacterGoods(sld,GOOD_FOOD,500);
    SetCharacterGoods(sld,GOOD_BALLS,1000);
    SetCharacterGoods(sld,GOOD_GRAPES,1000);
    SetCharacterGoods(sld,GOOD_KNIPPELS,1000);
    SetCharacterGoods(sld,GOOD_BOMBS,1000);
    SetCharacterGoods(sld,GOOD_POWDER,3000);
    SetCharacterGoods(sld,GOOD_PLANKS,150);
    SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
    SetCharacterGoods(sld,GOOD_RUM,200);
    SetCharacterGoods(sld,GOOD_WEAPON,600);
			
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_FindOrCreateGroup("WarDog");
	Group_AddCharacter("WarDog", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetGroupCommander("WarDog", "wl_Pirate_Cap");
	LAi_SetImmortal(sld, false);
	//Group_SetPursuitGroup("DeSouza", PLAYER_GROUP);
	Group_SetTaskAttack("WarDog", PLAYER_GROUP);
	Group_LockTask("WarDog");
	
	Group_SetAddress("WarDog", "Terks", "Quest_ships", "quest_ship_7");	
	SetFunctionNPCDeathCondition("WhisperWarDog_Is_Dead", "wl_Pirate_Cap", false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка Виспер --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
