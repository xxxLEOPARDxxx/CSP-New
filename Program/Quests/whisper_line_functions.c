
void Whisper_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.WhisperTutorial = true;
    Pchar.questTemp.WhisperFuture = true;
    Pchar.BaseNation = PIRATE;
    //fix ������ ������
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
	DeleteAttribute(Pchar, "perks.list.FlagEng");
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	������� ������	������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    SetCharacterPerk(Pchar, "FlagPir");
    Flag_SPAIN();

    //������� �� �����
    RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
    RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
    RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
    DeleteAttribute(Pchar, "items");
	//DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
	//��������� ���������� �������
	GiveItem2Character(pchar, "blade_whisper");
	EquipCharacterByItem(pchar, "blade_whisper");
	GiveItem2Character(pchar, "pistol7shotgun");
	EquipCharacterByItem(pchar, "pistol7shotgun");
	GiveItem2Character(pchar, "cirass5");
	EquipCharacterbyItem(pchar, "cirass5");
    TakeNItems(Pchar, "12_gauge", 99);
    TakeNItems(Pchar, "grapeshot", 99);
	TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
	LAi_SetCharacterUseBullet(pchar,"grapeshot");
    SetCharacterPerk(Pchar, "GunProfessional");
	Pchar.model="PGG_Whisper_5_NoHat";
	SetNewModelToChar(Pchar);
	
	//������� ��� ����������� ��������� � ����� ������ ��, ��, ����� �� ����� �������
	//DoReloadCharacterToLocation(pchar.location,"reload","reload2_back");
	
	//��������� ����� �� �������
	chrDisableReloadToLocation = true;
	//������������� ���� ���������
	bDisableCharacterMenu = true;
	//� ����������
	InterfaceStates.DisFastTravel = true;
	//������ ���������� ��������� �������
	//LockQuestLine(characterFromId("spa_guber"));
	
	//������������� �������
	pchar.questTemp.Whisper.Entered_Dungeon = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);

	//worldMap.date.year = 2065;
    //Environment.date.month = 7;
    //Environment.date.day = 3;
	
	ref _location = &locations[reload_location_index];
	_location.box1.QuestClosed = true;
	_location.box2.QuestClosed = true;
	_location.box3.QuestClosed = true;
	_location.box4.QuestClosed = true;
	
	//������� �������
	for (int i = 0; i < 10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Robot"+sti(i), "Terminator", "Terminator_Sex", "Terminator", MOD_SKILL_ENEMY_RATE, PIRATE, 0, false));
		sld.name = "�-"+(800+rand(150));
		sld.lastname = "";
		sld.CantLoot = true;
		if (rand (1) == 0)
		{
			GiveItem2Character(sld, "katar");
			EquipCharacterByItem(sld, "katar");
		}
		else 
		{
			GiveItem2Character(sld, "blade14");
			EquipCharacterByItem(sld, "blade14");
		}
		LAi_SetHP(sld, 10.0 * MOD_SKILL_ENEMY_RATE, 10.0 *MOD_SKILL_ENEMY_RATE);
		if (MOD_SKILL_ENEMY_RATE == 10)
		{
			SetCharacterPerk(sld, "Sliding");
		}
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
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster24");
    
	PChar.quest.WhisperScientist.win_condition.l1 = "locator";
	PChar.quest.WhisperScientist.win_condition.l1.location = "Bermudes_Dungeon";
	PChar.quest.WhisperScientist.win_condition.l1.locator_group = "box";
	PChar.quest.WhisperScientist.win_condition.l1.locator = "box1";
	PChar.quest.WhisperScientist.function = "WhisperScientist";
}

void WhisperScientist(string qName)
{
	
	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);
		
		if(sld.FaceId == 487 || sld.FaceId == 535 || sld.FaceId == 211)
		{//��� �� ����� ������ �����, ��� ��� ������� �� ���
			sld.willDie = true;
			LAi_KillCharacter(sld);
		}
	}
	pchar.questTemp.Whisper.Near_Chest = true;	
	PlayVoice("interface\important_item.wav");
	StartActorSelfDialog("First time");
	sld = GetCharacter(NPC_GenerateCharacter("CrazyScientist", "CCS_Mechanic", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 1, 20, 20, "", "", 80);
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster25");
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.name = "�������";
	sld.lastname = "����";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	//�������� �����
	Group_FindOrCreateGroup("Scientist");
	Group_AddCharacter("Scientist", sld.id);
    LAi_SetActorType(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetHP(sld, 5.0, 5.0);
	LAi_SetImmortal(sld, true);
	sld.LifeDay = 0;
	
	sld = GetCharacter(NPC_GenerateCharacter("FinalBot", "Terminator", "Terminator_Sex", "Terminator", 55, PIRATE, 0, false));
	FantomMakeCoolFighter(sld, 1, 20, 20, "", "pistol7", 80);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.name = "�-911";
	sld.lastname = "";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "item", "duhi1");
	DoQuestFunctionDelay("TeleportBot", 0.5);
}

void TeleportBot(string qName)
{
	sld = CharacterFromID("FinalBot");
	switch (rand(2))
	{
		case 0:
		TeleportCharacterToPos(sld, -36.0, -0.11696, -18.0);
		break;
		case 1:
		TeleportCharacterToPos(sld, -3.8456, -0.11696, -15.0);
		break;
		case 2:
		TeleportCharacterToPos(sld, 16.0, -0.11696, 20.0);
		break;
	}
}
void WhisperTeleport(string qName)
{
	InterfaceStates.Buttons.Save.enable = false;
	pchar.questTemp.WhisperLine = false;
	sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_Cap", "PGG_Rozencraft", "man", "man", 1, PIRATE, -1, true));
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade15");
	EquipCharacterByItem(sld, "blade15");
	sld.dialog.currentnode = "First time";
	sld.name = "�����";
	sld.lastname = " �������";
	sld.greeting = "GR_ErnanEsteban";

	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto11");
	
	Group_FindOrCreateGroup("wl_Pirate");
	Group_AddCharacter("wl_Pirate", sld.id);
	string cnd, fnk;
		
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	
	for (i = 1; i < 13; i++)
	{
			sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 3+MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+sti(i));
			Group_AddCharacter("wl_Pirate", sld.id);
			LAi_SetWarriorType(sld);
			sld.chr_ai.disableDlg = true;
			sld.DontClearDead = true;
			sld.LifeDay = 0;
			cnd = "l" + i;
			fnk = "WhisperBonusChallengeRecheck"+i;
			//pchar.quest.WhisperBonusChallenge.win_condition.(cnd) = "NPC_Death";
			//pchar.quest.WhisperBonusChallenge.win_condition.(cnd).character = "wl_Pirate_"+sti(i);
			//pchar.quest.WhisperBonusChallenge.function = "WhisperBonusChallenge";
			pchar.quest.(fnk).win_condition.(cnd) = "NPC_Death";
			pchar.quest.(fnk).win_condition.(cnd).character = "wl_Pirate_"+sti(i);
			pchar.quest.(fnk).function = "WhisperBonusChallengeReCheck";
	}
}


void WhisperBonusChallengeReCheck(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.BonusEnergy"))
	{
		int n = 1;
		for (int i = 1; i < 13; i++)
		{
			if(LAi_IsDead(CharacterFromID("wl_Pirate_"+sti(i))))
			{
				n++;
			}
		}
		if(n >= 10)
		{
			DoQuestFunctionDelay("WhisperBonusChallenge", 0.5);
		}
	}
}

void WhisperBonusChallenge(string qName)
{
	AddBonusEnergyToCharacter(pchar, 10);
	pchar.Whisper.BonusEnergy = true;
	
	for (int i = 0; i < 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_mush"+i, GetPirateMushketerModel(), "man", "mushketer", 777, PIRATE, 0, false));
		//LAi_SetCharacterUseBullet(sld,"bullet");
		Group_AddCharacter("wl_Pirate", sld.id);
		LAi_SetWarriorType(sld);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetImmortal(sld, true);
		
		sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_sword"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 777, PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+sti(i));
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetImmortal(sld, true);
		Group_AddCharacter("wl_Pirate", sld.id);
		LAi_SetWarriorType(sld);
	}
}
	void WhisperHold(string qName)
{
    //chrDisableReloadToLocation = true;
    //InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;

	//LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	//InterfaceStates.Buttons.Save.enable = 0;
	
	//���������� ��� ����� �����
    LAi_SetCurHPMax(Pchar);
    LAi_SetPlayerType(Pchar);
    //�������
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
    //�������� ���� ���������� ������
	sld = CharacterFromID("wl_Pirate_Cap");
	DeleteAttribute(sld, "equip");
	ChangeCharacterAddressGroup(sld, "My_Deck", "reload", "reload1");
	GiveItem2Character(sld, "blade_whisper");
	EquipCharacterByItem(sld, "blade_whisper");
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
	
	//sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "priest", "man", "man", 10, SPAIN, -1, false));
	sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "PGG_Vincento_0", "man", "man", 10, SPAIN, -1, false));
   	sld.name 	= "�������";
    sld.lastname = "�� �����";
	//sld.model.animation = "man2";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	sld.greeting = "GR_DeSouza";
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
	switch (2)
	{
		case 0:
			LAi_ActorAnimation(sld, "attack_fast_"+sti(rand(2)+1), "", 0.6);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 0.5);
		break;
		case 1:
			LAi_ActorAnimation(sld, "attack_force_"+sti(rand(3)+1), "", 0.6);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 0.5);
		break;
		case 2:
			LAi_ActorAnimation(sld, "attack_break_1", "", 2.9);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 1.0);
		break;
	}	
	
}

void WhisperLine_WhisperHits(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	LAi_SetActorTypeNoGroup(PChar);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	TakeNItems(sld, "pistol3", -1);
	LAi_ActorAnimation(pchar, "Shot", "", 1.9);
    DoQuestFunctionDelay("WhisperLine_WhisperHits_1", 0.8);
}
void WhisperLine_WhisperHits_1(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	LAi_KillCharacter(sld);
    DoQuestFunctionDelay("WhisperLine_WhisperHits_2", 0.25);
}
void WhisperLine_WhisperHits_2(string qName)
{
	//LAi_LockFightMode(PChar, false);
	Lai_SetPlayerType(pchar);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	TakeNItems(pchar, "pistol3", -1);
	pchar.questTemp.Whisper.Inside_Incquisition = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.3);
}
void WhisperLine_WhisperHits_3(string qName)
{	
	for (i=1; i<=4; i++)
	{
		sld = characterFromId("IncqGuard_"+i);
		LAi_SetGuardianTypeNoGroup(sld);
	}
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

void WhisperLine_IncqGuard_bad_speaks(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	sld.dialog.currentnode = "IncqGuard_bad_wheel";
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}
void WhisperLine_IncqGuard(string qName)
{	
	for (i=1; i<=4; i++)
	{
		sld = characterFromId("IncqGuard_"+i);
		TakeNItems(sld, "spyglass3", -1);
		LAi_SetHP(sld, 10+2.0 * MOD_SKILL_ENEMY_RATE, 10+2.0 *MOD_SKILL_ENEMY_RATE);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		TakeNItems(sld, "blade16", -10);
		TakeNItems(sld, "blade4", 1);
		EquipCharacterByItem(sld, "blade4");
		if (sld.Dialog.Filename == "Incquistors.c")
		{
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);
			if (LAi_FindNearestLocator("soldiers", locx, locy, locz) == "soldier1")
			{
				float locx, locy, locz;
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
				if(!CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
				{
					sld.dialog.currentnode = "IncqGuard";
				}
				else
				{
					sld.dialog.currentnode = "IncqGuard_bad";
					pchar.Whisper.IncqGuard_bad = sld.id;
					LAi_SetActorTypeNoGroup(sld);
					AddMoneyToCharacter(sld, 1500);
					TakeNItems(sld, "map_cuba", 1);
				}
				LAi_SetActorTypeNoGroup(sld);
				LAi_type_actor_Reset(sld);
				//LAi_ActorDialog(sld, pchar, "", 20.0, 0);
				SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
				LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
				sld.LifeDay = 0;
			}
		}
		else
		{
			if(CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
			{
				int weaponskill = 6 * MOD_SKILL_ENEMY_RATE;
				SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
				//LAi_group_Attack(sld, Pchar);
				//if (MOD_SKILL_ENEMY_RATE != 10)
				//{
					DeleteAttribute(sld, "perks.list.Sliding");
				//}
				TakeNItems(sld,"potion1", -5);
				TakeNItems(sld,"potion2", -5);
				pchar.quest.WhisperOpenTunnel.win_condition.l1 = "NPC_Death";
				pchar.quest.WhisperOpenTunnel.win_condition.l1.character = sld.id;
				pchar.quest.WhisperOpenTunnel.function = "WhisperOpenTunnel";
				TakeNItems(sld, "pistol3", -1);
				RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			}
		}
	}
}

void WhisperOpenTunnel(string qName)
{
	PChar.quest.WhisperEscape.win_condition.l1 = "locator";
	PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
	PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
	PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
	PChar.quest.WhisperEscape.function = "WhisperEscape";
}
void WhisperIncqAlarm(string qName)
{	
	LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
}
void WhisperEscape(string qName)
{	
	Pchar.BaseNation = PIRATE;
	ChangeCharacterNationReputation(pchar, 2, -15);
	if (!CheckAttribute(pchar, "Whisper.Escaped"))
	{
		DoReloadCharacterToLocation("Santiago_ExitTown","reload","reload3");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", true);
		LocatorReloadEnterDisable("Cuba_Jungle_03", "reload1_back", true);
		LocatorReloadEnterDisable("Cuba_Jungle_01", "reload3_back", true);
		LocatorReloadEnterDisable("Havana_ExitTown", "reload4", true);
		pchar.Whisper.Escaped = true;
		PChar.quest.WhisperPirateTown.win_condition.l1 = "location";
		PChar.quest.WhisperPirateTown.win_condition.l1.location = "PuertoPrincipe_town";
		PChar.quest.WhisperPirateTown.function = "WhisperPirateTown";
		if(CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
		{
			pchar.questTemp.Whisper.Escaped_Incquisition = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		}
	}
}

void WhisperPirateTown(string qName)
{	
	sld = GetCharacter(NPC_GenerateCharacter("NineFingers", "PGG_Alex_blade_0", "man", "man", 10, PIRATE, -1, false));
   	sld.name 	= "����������� ����";
	chrDisableReloadToLocation = true;
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
	LocatorReloadEnterDisable("Cuba_Jungle_03", "reload1_back", false);
	LocatorReloadEnterDisable("Cuba_Jungle_01", "reload3_back", false);

	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", true);

	string cnd;
	int weaponskill = 2 * MOD_SKILL_ENEMY_RATE;
	for (int i = 0; i < 12; i++)
	{
		if (i < 10)
		{
			sld = GetCharacter(NPC_GenerateCharacter("IncqSoldier_"+sti(i), "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE, SPAIN, 0, true));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);	
			cnd = "l" + i;
			pchar.quest.WhisperAfterTownBattle.win_condition.(cnd) = "NPC_Death";
			pchar.quest.WhisperAfterTownBattle.win_condition.(cnd).character ="IncqSoldier_"+sti(i);
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, "blade4");
			EquipCharacterByItem(sld, "blade4");
			SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
			LAi_SetHP(sld, 12.0 * MOD_SKILL_ENEMY_RATE, 12.0 *MOD_SKILL_ENEMY_RATE);
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item8");
		}
			sld = GetCharacter(NPC_GenerateCharacter("PirateTownDefender_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
			sld.dialog.currentnode = "Pirateguard";
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, "blade1");
			EquipCharacterByItem(sld, "blade1");
			SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
			LAi_SetHP(sld, 12.0 * MOD_SKILL_ENEMY_RATE, 12.0 *MOD_SKILL_ENEMY_RATE);
		if (i < 10)
		{
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
		}
		if (i >= 10 && MOD_SKILL_ENEMY_RATE < 10)	
		{
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item1");
			LAi_SetImmortal(sld, false);
		}
		
		
	}
	/*
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
	
	if (MOD_SKILL_ENEMY_RATE != 10)
	{
		sld = characterFromID("PirateTownDefender_8");
		ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item9");
	}
	*/
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
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	DeleteAttribute(sld, "items");
    DeleteAttribute(sld, "equip");
	GiveItem2Character(sld, "Map_bad");
	GiveItem2Character(sld, "spyglass1");
	GiveItem2Character(sld, "pistol1");
	TakeNItems(sld, "GunPowder", 10);
    TakeNItems(sld, "bullet", 10);
    TakeNItems(sld, "potionrum", 5);
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
   	sld.name 	= "����";
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
	LAi_SetHP(sld, 30.0 * MOD_SKILL_ENEMY_RATE, 30.0 *MOD_SKILL_ENEMY_RATE);
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		SetCharacterPerk(sld, "Sliding");
		LAi_SetHP(sld, 35.0 * MOD_SKILL_ENEMY_RATE, 35.0 *MOD_SKILL_ENEMY_RATE);
	}
	sld.greeting = "GR_ToughPirate";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "officers", "reload1_1");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld,pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("Wh_Jim", "PGG_Doggerty", "man", "man", 5, PIRATE, -1, false));
   	sld.name 	= "����";
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
		LAi_SetImmortal(sld, true);
		sld.LifeDay = 0;
	}
	
}
void WhisperJimTalk(string qName)
{	
	//sld = CharacterFromID("Wh_Jack");
	//Dead_DelLoginedCharacter(sld);
	sld = characterFromID("Wh_Jim");
	LAi_SetActorTypeNoGroup(sld);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
	
	//LAi_SetActorType(pchar);
	//LAi_ActorTurnToCharacter(pchar, sld);
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
		Smuggler = GetCharacter(NPC_GenerateCharacter("W_Smug0" + i, Model, "man", "man", 5, PIRATE, -1, true)); // 4 ���, ����� ���� ��������
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
	LAi_group_SetRelation(player.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_NEITRAL); // ������� �� ������

	//SetTimerCondition("Rand_Smuggling", 0, 0, 4, false);  // ����� 4 ��� ���� ������
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
	sld = GetCharacter(NPC_GenerateCharacter("W_ChinamanGuard", "pirate_10", "man", "man", 5, PIRATE, 0, false));
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "����";
    sld.lastname = "";
	sld.greeting = "Gr_Officer";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", LAi_FindNearestFreeLocator2Pchar("rld"));	
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
	
	sld = GetCharacter(NPC_GenerateCharacter("W_Chinaman", "PGG_Longway", "man", "man", 5, PIRATE, -1, false));
	sld.CanTakeMushket = true;
	sld.greeting = "GR_longway";
	//PlayVoice("Voice\Russian\Longway-01.wav");
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "����";
    sld.lastname = "���";
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", LAi_FindNearestFreeLocator2Pchar("rld"));
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
	int iNation = 1;// ����� �������
	string Model;
	
	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		CoastGuard = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE), iNation, 3, true)); // 3 ���, ����� ���� ��������
		SetFantomParam(CoastGuard);
		SelectCoastalGuardShip(CoastGuard);
		CoastGuard.AlwaysEnemy = true;
		CoastGuard.DontRansackCaptain = true;
		CoastGuard.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Coastal_Guards", CoastGuard.id);
		SetCharacterRelationBoth(sti(CoastGuard.index), GetMainCharacterIndex(), RELATION_ENEMY);
		//if (makeint(pchar.rank) < 6 && i == 1 && GetCompanionQuantity(pchar) == 1) break;
		
		if (MOD_SKILL_ENEMY_RATE!= 10)
		{
			if (makeint(pchar.rank) < 9 && i == 2 && GetCompanionQuantity(pchar) < 3) break;
		}
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
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", 5+MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
		//SetFantomParamHunter(sld);
		LAi_SetHP(sld, 50+sti(pchar.rank)*10.0, 50+sti(pchar.rank)*10.0);
		if (MOD_SKILL_ENEMY_RATE == 10)
		{
			LAi_SetHP(sld, 50+sti(pchar.rank) * 20.0, 50+sti(pchar.rank) * 20.0);
		}
		
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
	sld.CanTakeMushket = true;
	sld.name = "������";
	sld.lastname = "������";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "enc01", "enc01_02");
	LAi_SetImmortal(sld, true);
	SetSelfSkill(sld, 45, 45, 75, 45, 35);
	SetShipSkill(sld, 50, 25, 20, 20, 20, 25, 70, 25, 15);
	SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 15;
	LAi_SetHP(sld, 250.0, 250.0);
	sld.greeting = "GR_Lejitos";
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
	SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
	
	
	PChar.quest.WhisperAfterHuntersCaveBattle.function = "WhisperAfterHuntersCaveBattle";
	
}

void WhisperAfterHuntersCaveBattle(string qName)
{
	chrDisableReloadToLocation = false;
	if(!LAi_IsDead(CharacterFromID("W_Lejitos")))
	{
		sld = characterFromID("W_Lejitos");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	WhisperDeSouzaSeaBattle();
}

void WhisperDeSouzaSeaBattle()
{
	sld = CharacterFromID("AntonioDeSouza");
	SetFantomParamHunter(sld);
	sld.Ship.Type = GenerateShipExt(SHIP_GALEON_H, true, sld);
	sld.Ship.name = "���� ��������";
	LAi_SetImmortal(sld, false);
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(sld);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	sld.SaveItemsForDead = true;
	TakeNItems(sld, "DeSouzaCross", 1);
	
	SetSelfSkill(sld, 50, 50, 50, 50, 50);
	SetShipSkill(sld, 50, 50, 50, 50, 50, 50, 50, 50, 50);
	//SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 25;
	LAi_SetHP(sld, 50.0 * MOD_SKILL_ENEMY_RATE, 50.0 * MOD_SKILL_ENEMY_RATE);
	GiveItem2Character(sld, "cirass3");
	EquipCharacterbyItem(sld, "cirass3");

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		SetCharacterPerk(sld, "Sliding");
		sld.rank = 40;
		SetSelfSkill(sld, 80, 80, 80, 80, 80);
		SetShipSkill(sld, 80, 80, 80, 80, 80, 80, 80, 80, 80);
		LAi_SetHP(sld, 500.0, 500.0);
	}
	
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
	SetCharacterGoods(sld,GOOD_MEDICAMENT,300);
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
	sld.Ship.name = "ϸ� �����";
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	
	ChangeCharacterAddressGroup(sld, "My_Deck", "reload", "reload1");
	//GiveItem2Character(sld, "blade_15");
	EquipCharacterByItem(sld, "blade_15");
	//GiveItem2Character(sld, "pistol7shotgun");
	EquipCharacterByItem(sld, "pistol7shotgun");
    TakeNItems(sld, "blade_whisper", -1);
    TakeNItems(sld, "blade_whisper", -1);
	
	SetCrewQuantityFull(sld);
	int hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew + 12 * MOD_SKILL_ENEMY_RATE);// �������� ���
	
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 50 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 50 + 5 * MOD_SKILL_ENEMY_RATE);
	
	TakeNItems(sld, "12_gauge", 99);
    TakeNItems(sld, "grapeshot", 99);
    //TakeNItems(sld, "bullet", 99);
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	LAi_SetCharacterUseBullet(sld,"grapeshot");
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld, "cirass5");
	EquipCharacterbyItem(sld, "cirass5")
	LAi_SetHP(sld, 200.0 + 20 * MOD_SKILL_ENEMY_RATE, 200.0 + 20 * MOD_SKILL_ENEMY_RATE);
	SetSelfSkill(sld, 80, 80, 80, 80, 80);
	SetShipSkill(sld, 75, 75, 75, 75, 75, 75, 75, 75, 75);
	sld.rank = 30;
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		SetHalfPerksToChar(sld, true);
	}
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		sld.rank = 60;
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
		//LAi_SetHP(sld, 1000.0, 1000.0);
	}
	SetFoodToCharacter(sld, 3, 20);	
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);

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
	SetCharacterGoods(sld,GOOD_MEDICAMENT,300);
	
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_FindOrCreateGroup("WarDog");
	Group_SetType("WarDog", "pirate");
	Group_AddCharacter("WarDog", "wl_Pirate_Cap");
	Group_SetGroupCommander("WarDog", "wl_Pirate_Cap");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	LAi_SetImmortal(sld, false);
	Group_SetPursuitGroup("WarDog", PLAYER_GROUP);
	Group_SetTaskAttack("WarDog", PLAYER_GROUP);
	Group_LockTask("WarDog");
	
	Group_SetAddress("WarDog", "Terks", "Quest_ships", "quest_ship_7");	
	SetFunctionNPCDeathCondition("WhisperWarDog_Is_Dead", "wl_Pirate_Cap", false);
}

void WhisperSpawn_Chard()
{
	SetQuestHeader("WhisperChardQuest");
	AddQuestRecord("WhisperChardQuest", "1");
	AddQuestUserData("WhisperChardQuest", "sCity", XI_ConvertString("Colony" + pchar.Whisper.EsFriendTown + "Gen")));
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], true);
	LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", false);
	sld = GetCharacter(NPC_GenerateCharacter("W_Chard", "PGG_Chard_0", "man", "man", 1, PIRATE, -1, true));
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, pchar.Whisper.EsFriendTown+"_tavern_upstairs", "goto", "goto1");
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	
	sld.CanTakeMushket = true;
	sld.HeroModel = "PGG_Chard_0,PGG_Chard_1,PGG_Chard_2,PGG_Chard_3,PGG_Chard_4,PGG_Chard_5";
	sld.name = "�����";
	sld.lastname = "����";
	//LAi_SetImmortal(sld, true);
	SetSelfSkill(sld, 50, 50, 50, 50, 100);
	SetShipSkill(sld, 60, 30, 80, 80, 40, 30, 40, 30, 60);
	SetSPECIAL(sld, 7, 10, 8, 6, 7, 8, 10);
	sld.rank = 20;
	LAi_SetHP(sld, 220.0, 220.0);
	//sld.greeting = "GR_Lejitos";
	GiveItem2Character(sld, "blade_whisper");
	EquipCharacterByItem(sld, "blade_whisper");
	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	TakeNItems(sld, "bullet", 10);
	TakeNItems(sld, "GunPowder", 10);
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "ImmediateReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Tireless");
	//SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
}

void WhisperSpawnPortman (ref npchar)
{
	//pchar.Whisper.PortmanAtSea = true;
	int difficulty = 5 * MOD_SKILL_ENEMY_RATE;
	sld = GetCharacter(NPC_GenerateCharacter("Whisper_Portman_Captain", "off_eng_2", "man", "man", 55, ENGLAND, -1, true));
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������� ������ ��������";
	sld.mapEnc.type = "trade";
	FantomMakeCoolFighter(sld, 70, 50 + difficulty, 50 + difficulty, "blade23", "pistol3", 60);
	FantomMakeCoolSailor(sld, SHIP_UNICORN, "��������", CANNON_TYPE_CANNON_LBS32, 50 + difficulty, 50 + difficulty, 50 + difficulty);
	sld.dialog.filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
	sld.DeckDialogNode = "Portman";
	sld.name 	= "�����";
	sld.lastname = "�������";
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
					
	sld.ship.Crew.Morale = 50 + difficulty;
	ChangeCrewExp(sld, "Sailors", 50 + difficulty);
	ChangeCrewExp(sld, "Cannoners", 50 + difficulty);
	ChangeCrewExp(sld, "Soldiers", 50 + difficulty);

	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	GiveItem2Character(sld, "jewelry9");
	SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	sld.money = 100000;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	LAi_group_MoveCharacter(sld, "W_portman");
	string  sGroup = "Sea_" + sld.id;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	string targetCity = PGG_FindRandomTownByNation(sti(npchar.nation));
	while (targetCity == npchar.city)
	{
		targetCity = PGG_FindRandomTownByNation(sti(npchar.nation));
	}
	AddQuestRecord("WhisperChardQuest", "3");
	AddQuestUserData("WhisperChardQuest", "sTargetCity", XI_ConvertString("Colony" + targetCity + "Gen")));
	Map_CreateTrader(npchar.city, targetCity, sld.id, 8);
	pchar.Whisper.PortmanTargetCity = targetCity;
	SetFunctionNPCDeathCondition("Whisper_Portman_Is_Dead", sld.id, false);
	for (int i = 0; i < 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Whisper_Portman_follower"+i, "off_eng_1", "man", "man", 30, ENGLAND, -1, true));
		FantomMakeCoolFighter(sld, 50, 30 + difficulty, 30 + difficulty, "blade36", "pistol3", 10);
		FantomMakeCoolSailor(sld, SHIP_SALAMANDER, "", CANNON_TYPE_CANNON_LBS24, 30 + difficulty, 30 + difficulty, 30 + difficulty);
		SetRandomNameToShip(sld);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		SetCharacterPerk(sld, "MusketsShoot");
						
		sld.ship.Crew.Morale = 30 + difficulty;
		ChangeCrewExp(sld, "Sailors",30 + difficulty);
		ChangeCrewExp(sld, "Cannoners", 30 + difficulty);
		ChangeCrewExp(sld, "Soldiers", 30 + difficulty);

		GiveItem2Character(sld, "cirass3");
		EquipCharacterbyItem(sld, "cirass3");
		GiveItem2Character(sld, "jewelry9");
		SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
		TakeNItems(sld, "Food5", 3);
		TakeNItems(sld, "potion2", 3);
		sld.money = 30000;
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		
		LAi_group_MoveCharacter(sld, "W_portman");
		Group_AddCharacter(sGroup, sld.id);
	}
}

void Whisper_Portman_Is_Dead(string qName)
{
	DeleteAttribute(pchar, "Whisper.ActiveChardQuest");
	if (!CheckAttribute(pchar, "Whisper.FoundPortmanJournal"))
	{
		AddQuestRecord("WhisperChardQuest", "6");
		CloseQuestHeader("WhisperChardQuest");
	}
}

void WhisperChardShore(string qName)
{
	if(CheckAttribute(pchar,"WhisperChardCompanion"))
	{
		LocatorReloadEnterDisable("shore26", "boat", true);
		LocatorReloadEnterDisable("shore27", "boat", true);
		sld = CharacterFromID("W_Chard");
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		chrDisableReloadToLocation = true;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	DeleteAttribute(pchar,"WhisperChardCompanion");
}

void WhisperChardCave(string qName)
{
	LocatorReloadEnterDisable("shore26", "boat", true);
	LocatorReloadEnterDisable("shore27", "boat", true);
	GiveItem2Character(sld, "blade13");
	EquipCharacterbyItem(sld, "blade13");
	sld = CharacterFromID("W_Chard");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

}

void WhisperEngRevengeWarning(string qName)
{
	pchar.questTemp.Whisper.EngRevenge = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
}

void WhisperEnglandRevengel()
{
	ref sld;
	int i;
	int difficulty = 5 * MOD_SKILL_ENEMY_RATE;
	for (i = 1; i <= 4; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("W_Captain0"+i, "off_eng_" + (rand(1) + 1), "man", "man", difficulty, ENGLAND, -1, true));
		FantomMakeCoolFighter(sld, 50, 30 + difficulty, 30 + difficulty, "blade36", "pistol3", 50);
		FantomMakeCoolSailor(sld, SHIP_OXFORD, "", CANNON_TYPE_CANNON_LBS24, 40 + difficulty, 40 + difficulty, 40 + difficulty);
		SetRandomNameToShip(sld);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		SetCharacterPerk(sld, "MusketsShoot");
						
		sld.ship.Crew.Morale = 40 + difficulty;
		ChangeCrewExp(sld, "Sailors",40 + difficulty);
		ChangeCrewExp(sld, "Cannoners", 40 + difficulty);
		ChangeCrewExp(sld, "Soldiers", 40 + difficulty);

		GiveItem2Character(sld, "cirass3");
		EquipCharacterbyItem(sld, "cirass3");
		SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
		TakeNItems(sld, "Food5", 2);
		TakeNItems(sld, "potion2", 2);
		sld.money = 40000;
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		
		sld.AlwaysEnemy = true;
		Group_AddCharacter("Coastal_Guards", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		Fantom_SetBalls(sld, "pirate");
		if (MOD_SKILL_ENEMY_RATE!= 10)
		{
			if (i == 3) break;
		}
    }
	Group_SetGroupCommander("Coastal_Guards", "W_Captain01");
	if(pchar.location.from_sea == "shore27")
	{
		Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "Quest_ships", "quest_ship_1");
	}
	else
	{
		Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
		Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	}
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
	Flag_PIRATE();
}

void WhisperSelectRandomUsurer() // ����� ���������� ���������� �� ������
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		string thisTown = FindStringBeforeChar(pchar.location, "_tavern");
		for(n=0; n<MAX_COLONIES; n++)
		{			
			if (colonies[n].nation != thisTown && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange" && colonies[n].id != "Havana" && colonies[n].id != "Santiago" && colonies[n].id != "Portroyal" && colonies[n].id != "Villemstad" && colonies[n].id != "Tortuga" && colonies[n].id != "Panama")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.Whisper.UsurerId = colonies[nation].id + "_usurer";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- ������� ������ --     �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	������� ������� ���������	������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void DarkHuman_StartGame(string qName)
{
	DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
	
	SetQuestHeader("DarkHumanQuestline");
	AddQuestRecord("DarkHumanQuestline", "1");
	
	//��������� ����� �� �������
	chrDisableReloadToLocation = true;
	//������������� ���� ���������
	bDisableCharacterMenu = true;
	//� ����������
	InterfaceStates.DisFastTravel = true;
	
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	
	//ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit3");
	//LAi_SetActorTypeNoGroup(pchar);
	//LAi_ActorSetSitMode(pchar);
	pchar.selectedHero = rand(PsHeroQty-2)+2;
	sld = CharacterFromID("PsHero_" + pchar.selectedHero);
	ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc12");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload_hold");
	
	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "PGG_transporter";
	LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
	//SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
	sld.PGGAi.location.town = PGG_FindRandomTownByNation(sti(sld.nation));
	
	GiveNationLicence(SPAIN, 45);
	GiveNationLicence(HOLLAND, 80);
	Flag_HOLLAND();
	pchar.money = 1000;
	GiveItem2Character(pchar, "DHGlove");
	EquipCharacterbyItem(pchar, "DHGlove");
}

void DarkHuman_Amatike(string qName)
{
	bDisableCharacterMenu = false;
	sld = CharacterFromID("PsHero_" + pchar.selectedHero);
	string futureLoc = sld.PGGAi.location.town + "_Tavern";
	ChangeCharacterAddressGroup(sld, futureLoc, "goto", "goto1");
	DeleteAttribute(pchar, "selectedHero");
	DoReloadCharacterToLocation("Shore9","smugglers", "smuggler02");
	
	sld = GetCharacter(NPC_GenerateCharacter("DH_mercenary", "officer_" + (rand(62)+2), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smuggler01");
	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "DH_mercenary_shore";
	LAi_SetActorType(sld);
	Group_AddCharacter(PLAYER_GROUP, sld.id);
    LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
	
	for (int i = 0; i < 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DH_merc_mush" + i, GetPirateMushketerModel(), "man", "mushketer", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
		ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
		LAi_SetWarriorType(sld);
		LAi_SetActorType(sld);
		Group_AddCharacter(PLAYER_GROUP, sld.id);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);

		sld = GetCharacter(NPC_GenerateCharacter("DH_merc_blade"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
			
		ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
		LAi_SetWarriorType(sld);
		LAi_SetActorType(sld);
		Group_AddCharacter(PLAYER_GROUP, sld.id);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);
	}
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_03", "reload3_back", true);
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload1_back", true);
}

void DarkHuman_Temple(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple";
	for (int i = 0; i < 4; i++)
	{
		sld = CharacterFromID("DH_merc_mush" + i);
		ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto2");
		LAi_SetStayType(sld);
		sld = CharacterFromID("DH_merc_blade" + i);
		ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto5");
		LAi_SetStayType(sld);
	}
	
	string cnd;
	pchar.maxIndians = 8;
	if (MOD_SKILL_ENEMY_RATE == 10)
	{//������� ��� ����������
		pchar.maxIndians+=2;
	}
	for (i = 0; i <= sti(pchar.maxIndians) * 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DHindian"+i, "Canib_"+(rand(5)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, 1, true));
		//SetFantomParamFromRank(sld, 1, true);
		sld.name = "��������";
		sld.lastname = "";
		DeleteAttribute(sld, "equip");
		DeleteAttribute(sld, "items");
		string _Blade = GiveRandomBladeByType("indian");
		LAi_SetHP(sld, 10*MOD_SKILL_ENEMY_RATE, 10*MOD_SKILL_ENEMY_RATE);
		weaponskill = 2* MOD_SKILL_ENEMY_RATE;
		SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
		GiveItem2Character(sld, _Blade);
		EquipCharacterbyItem(sld, _Blade);

		LAi_SetStayTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "Jungle_indians");
		
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
		cnd = "l" + i;
		pchar.quest.DarkHuman_Temple_Afterfight.win_condition.(cnd) = "NPC_Death";
		pchar.quest.DarkHuman_Temple_Afterfight.win_condition.(cnd).character ="DHindian"+i;
		
		if (i < sti(pchar.maxIndians))
		{
			LAi_KillCharacter(sld);
		}
	}
	PChar.quest.DarkHuman_Temple_Afterfight.function = "DarkHuman_Temple_Afterfight";
	LAi_group_SetCheck("Jungle_indians", "IndianInJungleClearGroup");
	
}

void DarkHuman_Temple_Afterfight(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	Lai_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple_afterfight";
	LocatorReloadEnterDisable("Temple", "reload1_back", true);
	LocatorReloadEnterDisable("Temple", "reload2", false);
	//CheckAttribute(Items[itemN], "shown")
	
	PChar.quest.DarkHuman_Temple_Inside.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Temple_Inside.win_condition.l1.location = "Temple_Inside";
	PChar.quest.DarkHuman_Temple_Inside.function = "DarkHuman_Temple_Inside";
	
	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor", "Dark_Incquisitor", "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, false));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto9");
	TakeNItems(sld, "suit_1", 1);
	GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	sld.SaveItemsForDead = true;
	LAi_SetActorType(sld);
	//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "Dark_Incquisitor";
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 5*MOD_SKILL_ENEMY_RATE, 5*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor1", "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto11");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 3*MOD_SKILL_ENEMY_RATE, 3*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor2", "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto13");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 3*MOD_SKILL_ENEMY_RATE, 3*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
}

void DarkHuman_Temple_Inside(string qName)
{
	pchar.CantTakeItems = true;
	
	sld = CharacterFromID("Dark_Incquisitor");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	chrDisableReloadToLocation = true;
}

void DarkHuman_Temple_Stash(string qName)
{
	//Log_Info("���")
	AddQuestRecord("DarkHumanQuestline", "3");
	SetQuestHeader("DarkHumanIncquisitorJournal");
	AddQuestRecord("DarkHumanIncquisitorJournal", "1");
	chrDisableReloadToLocation = false;
	
	PChar.quest.DarkHuman_Temple_Merc_After_Stash.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Temple_Merc_After_Stash.win_condition.l1.location = "Temple";
	PChar.quest.DarkHuman_Temple_Merc_After_Stash.function = "DarkHuman_Temple_Merc_After_Stash";
}
void DarkHuman_Temple_Merc_After_Stash(string qName)
{
	AddQuestRecord("DarkHumanQuestline", "4");
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto3");
	Lai_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple_afterstash";
	
	PChar.quest.DarkHuman_Amatike_return.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Amatike_return.win_condition.l1.location = "Shore9";
	PChar.quest.DarkHuman_Amatike_return.function = "DarkHuman_Amatike_return";
}
void DarkHuman_Amatike_return(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("DH_sailor", "officer_1", "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smuggler02");
	Lai_SetActorType(sld);
	//LAi_ActorFollow(sld, pchar, "", -1);
	
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
	Lai_SetActorType(sld);
	
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1 = "locator";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.location = "Shore9";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.locator_group = "encdetector";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.locator = "enc02";
	PChar.quest.DarkHuman_Amatike_return_dialog.function = "DarkHuman_Amatike_return_dialog";
}

void DarkHuman_Amatike_return_dialog(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_Amatike_return";
	chrDisableReloadToLocation = true;
}

void DarkHuman_SK(string qName)
{
	CloseQuestHeader("DarkHumanIncquisitorJournal");
	DoReloadCharacterToLocation("SantaCatalina_exittown","goto", "goto1");
	DoQuestFunctionDelay("DarkHuman_SK_gate", 2.5);
}
void DarkHuman_SK_gate(string qName)
{
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_03", "reload3_back", false);
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload1_back", false);
	// �� ������
	LocatorReloadEnterDisable("SantaCatalina_town", "reload5_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
	LocatorReloadEnterDisable("SantaCatalina_exittown", "reload1_back", true);
	LocatorReloadEnterDisable("SantaCatalina_exittown", "reload2_back", true);
	AddQuestRecord("DarkHumanQuestline", "5");
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_SK_gate";
	
	PChar.quest.DarkHuman_SK_tavern_dialog.win_condition.l1 = "location";
	PChar.quest.DarkHuman_SK_tavern_dialog.win_condition.l1.location = "SantaCatalina_tavern";
	PChar.quest.DarkHuman_SK_tavern_dialog.function = "DarkHuman_SK_tavern_dialog";
}
void DarkHuman_SK_tavern_dialog(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "goto", "goto2");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_SK_vavern";
	
	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID("DH_merc_mush" + i);
		if (CheckAttribute(sld, "model"))
		{
			Lai_SetWarriorType(sld);
			sld.LifeDay = 0;
			LAi_warrior_DialogEnable(sld, false);
		}
		sld = CharacterFromID("DH_merc_blade" + i);
		if (CheckAttribute(sld, "model"))
		{
			Lai_SetWarriorType(sld);
			sld.LifeDay = 0;
			LAi_warrior_DialogEnable(sld, false);
		}
	}
}
void DarkHuman_Villemstad(string qName)
{
	DoReloadCharacterToLocation("Villemstad_town","reload", "reload1_back");
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto23");
	DoQuestFunctionDelay("DarkHuman_Villemstad_merc", 1.5);
}
void DarkHuman_Villemstad_merc(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_Villemstad_merc";
	bDisableLandEncounters = false;
}
void SpeakAfterKill(string qName)
{
	sld = characterFromId(qName);
	Lai_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void DHmessages(string qName)
{
	Log_info("������ - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_2",3.0);
}
void DHmessages_2(string qName)
{
	Log_info("������ - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_3",3.0);
}void DHmessages_3(string qName)
{
	Log_info("������ - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_4",3.0);
}void DHmessages_4(string qName)
{
	Log_info("��������� - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_5",3.0);
}void DHmessages_5(string qName)
{
	Log_info("����� - "+(1500 + rand(750)));
}void DHmessages_wait(string qName)
{
	Log_info(" - �������� - ");
}
//���� ������ � ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- ������� ������� ��������� --     �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////