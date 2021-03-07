
//////////////////////////////////////////////////////////////////////
//	Блейз и Беатрис
//////////////////////////////////////////////////////////////////////
void Sharp_StartGame(string qName)
{
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	LocatorReloadEnterDisable("Shore57", "boat", true);
	pchar.cursed.waitingSkull = true;
	
	//Вступительный монолог
	pchar.questTemp.Sharp.Entered_Shore = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	
	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);
		if(sld.FaceId == 1)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			sld.PGGAi.IsPGG = false;
			sld.PGGAi.location.town = "none";
		}
	}
	pchar.quest.Sharp_MeetSiblings.win_condition.l1          = "location";
    pchar.quest.Sharp_MeetSiblings.win_condition.l1.location = "Terks_Grot";
    pchar.quest.Sharp_MeetSiblings.function                  = "Sharp_MeetSiblings";
}

void SharpAfterTreasure(string qName)
{
	DeleteAttribute(pchar, "cursed.waitingSkull");
	bDisableLandEncounters = false;
	LocatorReloadEnterDisable("Shore57", "boat", false);
}
	
void SharpExitFromCave(string qName)
{
	chrDisableReloadToLocation = false;
}
void Sharp_MeetSiblings(string qName)
{
	chrDisableReloadToLocation = true;
	if (startherotype == 3)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sharp_Sibling", "PGG_Devlin_0", "man", "man", 1, PIRATE, -1, true));
		sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Blaze_dialog.c";
		sld.name = "Блэйз";
		sld.lastname = "Шарп";
		sld.HeroModel = "PGG_Devlin_0,PGG_Devlin_1,PGG_Devlin_2,PGG_Devlin_3,PGG_Devlin_4,PGG_Devlin_5,PGG_Devlin_6,PGG_Devlin_7,PGG_Devlin_8";
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sharp_Sibling", "PGG_Beatric_0", "woman", "YokoDias", 1, PIRATE, -1, true));
		sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Beatrice_dialog.c";
		sld.name = "Беатрис";
		sld.lastname = "Шарп";
		sld.HeroModel = "PGG_Beatric_0,PGG_Beatric_1,PGG_Beatric_2,PGG_Beatric_3,PGG_Beatric_4,PGG_Beatric_5,PGG_Beatric_6,PGG_Beatric_7,PGG_Beatric_8";
	}
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster1");
	//sld.greeting = "cit_common";
	//Добавить звуки
	LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	LAi_SetHP(sld, 100.0, 100.0);
	sld.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, sld);
	sld.Ship.name = "Любимец удачи";
	SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	Group_FindOrCreateGroup("SharpSibling");
	Group_AddCharacter("SharpSibling", sld.id);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Блейз и Беатрис --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
