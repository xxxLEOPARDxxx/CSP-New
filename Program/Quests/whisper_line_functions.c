
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
	Pchar.model="PGG_Whisper_5";
	
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
	//sld.name = "";
	//sld.lastname = "";
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
	sld = characterFromID("NineFingers");
	
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto6");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
}

void WhisperPirateTownBattle(string qName)
{	

	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", true);

	string cnd;
	for (int i = 0; i < 10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("IncqSoldier_"+sti(i), "sold_spa_"+(rand(7)+1), "man", "man", 1, SPAIN, 1, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);	
		sld.LifeDay = 0;
		cnd = "l" + i;
		pchar.quest.WhisperAfterTownBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.WhisperAfterTownBattle.win_condition.(cnd).character ="IncqSoldier_"+sti(i);
		
		sld = GetCharacter(NPC_GenerateCharacter("PirateTownDefender_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 1, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
		sld.dialog.currentnode = "Pirateguard";
		sld.LifeDay = 0;
		
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

/*
Заблокировать испанскую
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка Виспер --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
