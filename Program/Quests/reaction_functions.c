
ref		sld, rCharacter;
int     iTemp, i; // ����� ��� ���������� ����� ����� (�����)
float   locx, locy, locz;
string  sTemp; // ����� ������ ��� ����������
bool    bOk;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������ � �����������   ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//��� ����
void OpenPGGInformation()
{
	LaunchPsHeroScreen();
}
//==> ���������
void Birglars_fight(string qName)
{
	if (GetCharacterIndex("Berglar" + pchar.quest.(qName).city) != -1)
	{
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);		
		sTemp = "berglar" + pchar.quest.(qName).city;
		pchar.questTemp.tugs.(sTemp) = "over";
		sld = characterFromId("Berglar" + pchar.quest.(qName).city);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	}
}
//���������� ���� �� ���� �����������
void SmallQuests_free(string qName)
{
	pchar.questTemp.different = "free";
}
//������� ��� ������������ ������� � sit ����� ������
void MayorSitBack(string qName) 
{
	iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
	if (iTemp > 0)
	{
		sld = &characters[iTemp];
		sld.location = Pchar.quest.MayorSitBack.locationName;
		sld.location.group = "sit";
		sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
		LAi_SetHuberTypeNoGroup(sld);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	}
}

void Ascold_fightInsideTemple(string qName)
{
	if (MOD_SKILL_ENEMY_RATE > 5) chrDisableReloadToLocation = true;
	characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Ascold_KilledTemple";
	AddQuestRecord("Ascold", "11");
	AddQuestUserData("Ascold", "sSex", GetSexPhrase("","�"));
    //--------------------------- ������� ------------------------------
	LAi_group_Delete("EnemyFight");
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
 	sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_off", "SpaOfficer3", "man", "man", Rank, SPAIN, -1, true));
    FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);	
	LAi_SetActorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto9");
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==12) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol3", 50);
		DeleteAttribute(sld, "SuperShooter");
		sld.BreakTmplAndFightGroup = true;
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
    }
    for (i=10; i<=13; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	DoQuestFunctionDelay("Ascold_actorSetWarrior", 3.5);
}

void Ascold_actorSetWarrior(string qName)
{
	iTemp = GetCharacterIndex("SpaEnemy_off");
	if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	for (i=1; i<=8; i++)
    {
		iTemp = GetCharacterIndex("SpaEnemy_"+i);	
		if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	}
}

void Ascold_LeifIsDead(string qName)
{
	LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", false);
}

 void Ascold_OpenTheGrave(string qName)
{
	DoReloadCharacterToLocation("Guadeloupe_Cave", "reload", "reload5");
}

void DelivLettTortuga_Digress(string qName)
{
	LAi_ActorAnimation(characterFromId("AntonioDeBarras"), "attack_fast_1", "DelivLettTortuga_2KickPhar", 0.8);
}

void SeekIsabella_exitTown(string qName)
{
    DeleteAttribute(&locations[FindLocation("Beliz_ExitTown")], "DisableEncounters"); //��������� ������
	DoQuestCheckDelay("TalkSelf_Quest", 0.1); //������ ���-��-���
}

void Fr2Letter_shore22(string qName)
{
	if (characters[GetCharacterIndex("Bandit_1")].location == "Shore22")
	{
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("Bandit_"+i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		}
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
	}
}

void Isabella_widding(string qName)
{
	pchar.quest.Romantic_Widding_Cancel.over = "yes"; //������� ������ �� ������� �� �������
	pchar.RomanticQuest = "Widding";
	sld = characterFromID("Isabella");
	LAi_SetActorType(pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);	
}

void FrLine_HoverGoOnPrison()
{	
	pchar.questTemp.jailCanMove = true; //���� ����������� ����� �� ������
	LAi_SetPlayerType(pchar);
	pchar.questTemp.State = "Fr2Letter_SeekProblems";	
	AddQuestRecord("Fra_Line_2_DelivLetter", "3");

	RestoreTempRemoveParam(pchar, "items");
	pchar.money = pchar.questTemp.money;
	//RestoreEquippedMaps(pchar);
	DeleteAttribute(pchar, "questTemp.money");
	RefreshEquippedMaps(pchar);
	//==> �������� ����� �������� � �������
    LAi_group_Delete("PeaceGroup");
	for (i=1; i<=2; i++)
    {
		sTemp = "sit6";
		if (i==2) sTemp = "sit7";
		sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 20, FRANCE, 5, true));
		FantomMakeCoolFighter(sld, 20, 70, 40, BLADE_NORMAL, "pistol3", 70);
		sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
		LAi_SetSitType(sld);
		LAi_group_MoveCharacter(sld, "PeaceGroup");
		LAi_SetCheckMinHP(sld, sti(sld.chr_ai.hp)-1, false, "Fr2Letter_FightAfterShot");
		ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "sit", sTemp);
	}
	sld = characterFromID("GoverFantom");
	LAi_SetActorType(sld);
    LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 2.0);
	DoQuestFunctionDelay("FrLine_HoverGoOnPrison_2", 2.5);
}

void FrLine_HoverGoOnPrison_2(string qName)
{
	DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto12");
}

void HL5_portManGiveFleuts()
{
    pchar.questTemp.State = "ThreeFleutes_toLaVega";
    for (int j=1; j<=3; j++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("Captain_"+j, "trader_"+(rand(15)+1), "man", "man", 15, HOLLAND, -1, true));
        FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
        FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
        sld.Ship.Cargo.Goods.Balls = 18;
        sld.Ship.Cargo.Goods.Grapes = 18;
        sld.Ship.Cargo.Goods.Knippels = 18;
        sld.Ship.Cargo.Goods.Bombs = 18;
        sld.Ship.Cargo.Goods.Weapon = 0;
        sld.Ship.Cargo.Goods.Powder = 50;
		sld.CompanionEnemyEnable = false; 
		sld.Abordage.Enable = false; // ������!
		SetShipRemovable(sld, false);
		AddCharacterGoods(sld, GOOD_CLOTHES, 5000);
        AddCharacterGoods(sld, GOOD_FRUITS, 200);
        AddCharacterGoods(sld, GOOD_RUM, 900);
        SetCompanionIndex(pchar, -1, sti(sld.index));
        pchar.GenQuest.StoreGoods.StoreIdx = LaVega_STORE;
        pchar.GenQuest.StoreGoods.HL5_ThreeFleutes = true;
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1 = "location";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1.location = "LaVega_town";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition = "ThreeFleutes_TalkIntoLaVega";
    }
}

void SeekShip_Stay(string qName)
{
	sld = &characters[sti(pchar.quest.(qName).Idx)];
	LAi_SetStayType(sld);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������ � �����������   �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������ ����� �����   ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BlueBird_inCavern(string qName)
{
	pchar.questTemp.BlueBird = "seenCarriers";
	DoQuestCheckDelay("TalkSelf_Quest", 0.2); //������ ���-��-���
}

void BlueBird_endCaveDialog()
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnByLocator(pchar, "goto", "goto1");
	string sQuest = "";
	string CarrierName[10];
	CarrierName[0] = "GenresBag1";
	CarrierName[1] = "GenresBag2";
	CarrierName[2] = "GenresBarrel1";
	CarrierName[3] = "GenresBarrel2";
	CarrierName[4] = "GenresBarrelTop1";
	CarrierName[5] = "GenresBarrelTop2";
	CarrierName[6] = "GenresBottle1";
	CarrierName[7] = "GenresBottle2";
	CarrierName[8] = "GenresChest1";
	CarrierName[9] = "GenresChest2";
	for (i=0; i<10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Carrier_" + i, CarrierName[i], "man", "genres", 35, PIRATE, 0, true));
		sld.gotoGroup = "reload";
		sld.gotoLocator = "reload1_back";
		LAi_SetCarrierType(sld);
		ChangeCharacterAddressGroup(sld, "Bermudes_Cavern", "reload", "reload2");
	}
	DoQuestFunctionDelay("BlueBird_endCaveScript", 33.0);
}

void BlueBird_endCaveScript(string qName)
{
	LAi_LocationDisableMonstersGen("Bermudes_Cavern", false); //�������� ��������
	LAi_LocationDisableOfficersGen("Bermudes_Cavern", false); //�������� �������
	for (i=0; i<10; i++)
	{
		sld = characterFromId("Carrier_" + i);
		ChangeCharacterAddress(sld, "none", "");
	}
	AddQuestRecord("Xebeca_BlueBird", "6");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("��","��"));
	LAi_SetPlayerType(pchar);
	pchar.questTemp.BlueBird = "toSeaBattle";
	pchar.quest.BlueBird_seaBattle.win_condition.l1 = "location";
	pchar.quest.BlueBird_seaBattle.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_seaBattle.function = "BlueBird_seaBattle";	
}

void BlueBird_seaBattle(string qName)
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	sld = GetCharacter(NPC_GenerateCharacter("BlueBirdCapitain", "QuestCaptain", "man", "man", 20, PIRATE, 30, true));
	sld.name 	= "���";
    sld.lastname = "�������";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "BlueBirdCapitain";
	sld.greeting = "CapSinkShip";
	//Korsar Maxim - �������� ���� ������� ��� �����. -->
	sld.HeroModel = "QuestCaptain,QuestCaptain_1,QuestCaptain_2,QuestCaptain_3,QuestCaptain_4,QuestCaptain_5";
	//Korsar Maxim - �������� ���� ������� ��� �����. <--
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);
	FantomMakeCoolSailor(sld, SHIP_XebekVML, "����� �����", CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	SetCharacterPerk(sld, "MusketsShoot");
	GiveItem2Character(sld, "indian5");
	GiveItem2Character(sld, "jewelry15");
	GiveItem2Character(sld, "icollection");
	RemoveItems(sld, "spyglass3", 1);
	GiveItem2Character(sld, "spyglass4");
	EquipCharacterbyItem(sld, "spyglass4");
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 70);
	
	Group_AddCharacter("BlueBird_Group", "BlueBirdCapitain");			
	Group_SetType("BlueBird_Group", "pirate");
	Group_SetGroupCommander("BlueBird_Group", "BlueBirdCapitain");
	sTemp = "quest_ship_10";
	if (pchar.location.from_sea == "Shore_ship1") sTemp = "quest_ship_8";
	Group_SetAddress("BlueBird_Group", "Bermudes", "quest_ships", sTemp);
	Group_SetTaskAttack("BlueBird_Group", PLAYER_GROUP);

	pchar.quest.BlueBird_over.win_condition.l1 = "NPC_Death";
	pchar.quest.BlueBird_over.win_condition.l1.character = "BlueBirdCapitain";
	pchar.quest.BlueBird_over.function = "BlueBird_over";

	pchar.quest.BlueBird_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.BlueBird_DieHard1.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_DieHard1.function = "BlueBird_DieHard";
	Pchar.quest.BlueBird_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.BlueBird_DieHard2.function = "BlueBird_DieHard";
	pchar.quest.BlueBird_DieHard1.win_condition.l1 = "MapEnter";
	pchar.quest.BlueBird_DieHard1.function = "BlueBird_DieHard";
}

void BlueBird_over(string qName)
{
	pchar.quest.BlueBird_DieHard1.over = "yes";
	pchar.quest.BlueBird_DieHard2.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "7");
	pchar.questTemp.BlueBird = "weWon";
	// ������ ������, ������ ������� �������  <-- ugeen
	sld = characterFromId("Pirates_trader");
	sld.name = "���������";
	sld.lastname = "��������";
	sld.model = "trader_2";
	LAi_SetOwnerType(sld);
	// ����� ����
	AddSimpleRumourCity("�, �����"+ GetSexPhrase("�","���") +"! �� �� ��� �� ������ ������� �������! ������ �������� �������� �������� - ������� ������ ������! �����������, �� ������ ��� ������, ��� ������� ������ �������� � �������� �����. ��� ����� ���� � ���� ����� ������� ������ ���. � ����� ������� �������� � ������ ��������� �� ��� ������� - ������ �� ������ � ������� � ����, ��-��-��. ��� �����-�� ����! ������� ������ ��� ���� ������, ���� ���� �������� ��������� �������� ���� � ����� ����� �� �������.\n"+
		"�� ��� ����� - ������ � ���� ���������� - �� ����� �� ����� ����������, ������� �� ���������� ����� �������� ������� ����������... � �������� �� ��� - ��� ����� ����� ����� �����, ��-��...","Pirates", 30, 3, "");
	// --> ugeen
}

void BlueBird_DieHard(string qName)
{
	sld = characterFromId("BlueBirdCapitain");
	sld.lifeDay = 0;
	group_DeleteGroup("BlueBird_Group");
	pchar.quest.BlueBird_over.over = "yes";
	pchar.quest.BlueBird_DieHard1.over = "yes";
	//pchar.quest.BlueBird_DieHard2.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "8");
	pchar.questTemp.BlueBird = "DieHard";
}

//��������� ��������. ��������� �� ������ ����� ��������
void BlueBird_loginFleut(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.BlueBird") < 10) 
	{
		LAi_group_Delete("EnemyFight");
		group_DeleteGroup("BlueBird_Group");
		sld = GetCharacter(NPC_GenerateCharacter("BlueBirdTrader", "", "man", "man", 20, sti(pchar.questTemp.BlueBird.nation), 30, true));							
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "BlueBirdTrader";
		sld.greeting = "CapSinkShip";
		sld.AlwaysEnemy = true;
		SetCaptanModelByEncType(sld, "trade");
		FantomMakeCoolSailor(sld, SHIP_FLEUT, pchar.questTemp.BlueBird.Ship.Name, CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
		sld.Ship.Mode = "trade"; //��������
		sld.DontRansackCaptain = true;
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("BlueBird_Group", "BlueBirdTrader");			
		Group_SetGroupCommander("BlueBird_Group", "BlueBirdTrader");
		Group_SetAddress("BlueBird_Group", pchar.questTemp.BlueBird.Island, "quest_ships", "quest_ship_"+(rand(5)+1));
		Group_SetTaskRunaway("BlueBird_Group", PLAYER_GROUP);
		pchar.questTemp.BlueBird = "attackFleut"; //���� ������
		//���������� �� ���� �� �������
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1.location_type = "town";
		pchar.Quest.BlueBirdFleut_over1.function = "BlueBirdFleut_over";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1.location_type = "seashore";
		pchar.Quest.BlueBirdFleut_over2.function = "BlueBirdFleut_over";
		Pchar.quest.BlueBirdFleut_over3.win_condition.l1 = "MapEnter";
		pchar.Quest.BlueBirdFleut_over3.function = "BlueBirdFleut_over";
		//���������� �� �������
    	pchar.quest.BlueBirdFleut_board.win_condition.l1 = "NPC_death";
    	pchar.quest.BlueBirdFleut_board.win_condition.l1.character = "BlueBirdTrader";
    	pchar.quest.BlueBirdFleut_board.function = "BlueBirdFleut_board";
	}
	else
	{
		AddQuestRecord("Xebeca_BlueBird", "11");
		AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("��","��"));
		AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	}
}

void BlueBirdFleut_over(string qName)
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	pchar.Quest.BlueBirdFleut_board.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "12");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	pchar.questTemp.BlueBird = "returnMoney"; //����� ����� �� ����� �� ���������
}
//����� �����������, ������� ���������
void BlueBirdFleut_board(string qName)
{
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	pchar.questTemp.BlueBird.count = sti(pchar.questTemp.BlueBird.count) + 1; //������� ����������� �������
	AddQuestRecord("Xebeca_BlueBird", "13");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	pchar.questTemp.BlueBird = "returnMoney"; //����� ����� �� ����� �� ���������
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������ ����� �����    �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� ���������� �������� Sharp    ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sharp_loginNearIsland(string qName)
{	
	if (GetQuestPastMinutesParam("questTemp.Sharp") < 10) 
	{
		sld = &characters[GetCharacterIndex("Sharp")];
		LAi_SetCurHPMax(sld);
		sld.nation = pchar.nation; //����� ����� ������ ��� � ��
		SetCrewQuantityFull(sld);
		DeleteAttribute(sld, "ship.sails");// ������ ���� �� �������
		DeleteAttribute(sld, "ship.blots");
		DeleteAttribute(sld, "ship.masts");// ������� ������ �����
		SetBaseShipData(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		Group_AddCharacter("Sharp_Group", "Sharp");			
		Group_SetGroupCommander("Sharp_Group", "Sharp");
		Group_SetAddress("Sharp_Group", pchar.questTemp.Sharp.Island, "quest_ships", "quest_ship_"+(rand(1)+1));
		Group_SetTaskRunaway("Sharp_Group", PLAYER_GROUP);
		pchar.Quest.Sharp_landOver1.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver1.win_condition.l1.location_type = "town";
		pchar.Quest.Sharp_landOver1.function = "Sharp_Over";
		pchar.Quest.Sharp_landOver2.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver2.win_condition.l1.location_type = "seashore";
		pchar.quest.Sharp_landOver2.function = "Sharp_Over";
	    Pchar.quest.Sharp_mapOver.win_condition.l1 = "MapEnter";
		pchar.quest.Sharp_mapOver.function = "Sharp_Over";
	}
	else
	{
		AddQuestRecord("SharpPearl", "12");
		AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","�"));
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
		pchar.questTemp.Sharp.brothelChance = rand(10);
	}
}

void Sharp_Over(string qName)
{
	group_DeleteGroup("Sharp_Group");
	pchar.quest.Sharp_landOver1.over = "yes";
	pchar.quest.Sharp_landOver2.over = "yes";
	pchar.quest.Sharp_mapOver.over = "yes";
	//���� ������ � ��, ���� �� ����� �����
	if (pchar.questTemp.Sharp == "toSharp_going")
	{
		AddQuestRecord("SharpPearl", "4");
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
		pchar.questTemp.Sharp.brothelChance = rand(10);
	}
}

//�������� ������������� ������������
void Remove_Contract_Officer(string qName)
{
	ref chr = CharacterFromID(qName);
	if (CheckAttribute(chr,"ImmortalOfficer"))
	{
		if (!IsCompanion(chr) && !isOfficerInShip(chr, true))
		{
			pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) - 1);
		}
	}
}

//------------ ��������� �������� ----------------
void SeaPearl_login(string qName)
{
	characters[GetCharacterIndex("Sharp")].DeckDialogNode = "NewDeckSharp"; //����� ���� �� ������ �����
	pchar.quest.SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	Group_FindOrCreateGroup("PearlGroup");
	Group_SetType("PearlGroup", "trade");
	for (int j = 1; j <= iTemp; j++)
	{                
		sTemp = "PearlCapitain_" + j;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "trader_"+(rand(15)+1), "man", "man", 10, PIRATE, 30, true));	
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetBalls(sld, "pirate");
		sld.ShipTaskLock = true;
		sld.Abordage.Enable = false;
		sld.SinkTenPercent = true; //�������� � �� �����
		sld.PearlTartane = true; //������� ������ �������, ����� �������
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> ������������
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_LockTask("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.SeaPearl_DieHard1.function = "SeaPearl_DieHard";
	Pchar.quest.SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.SeaPearl_DieHard2.function = "SeaPearl_DieHard";
}

void SeaPearl_Late(string qName)
{	
	pchar.quest.SeaPearl_login.over = "yes";
	AddQuestRecord("SharpPearl", "9");
	AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("SharpPearl", "iDay", FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
	AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt"));
	pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
}

void SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.over = "yes";
	pchar.quest.SeaPearl_DieHard2.over = "yes";
	if (pchar.questTemp.Sharp == "SeaPearl_success")
	{	//�������� ���������
		AddQuestRecord("SharpPearl", "7");
		AddQuestUserData("SharpPearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
		AddQuestUserData("SharpPearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
	}
	else
	{	//��������� ���������
		AddQuestRecord("SharpPearl", "8");
		AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("��","��"));
		AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase("","�"));
	}
	pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	CloseQuestHeader("SharpPearl");
}

void SharpSeekSpy_loginSpy(string qName)
{
	if (rand(1) && !IsDay())
	{
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("SharpPearl_SeekSpy", "3");
		sld = GetCharacter(NPC_GenerateCharacter("Emillio", "pirate_5", "man", "man", 20, SPAIN, 0, true));
		sld.name = "������";
		sld.lastname = "������";
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
		rCharacter = GetCharacter(NPC_GenerateCharacter("QuestMan_5", "pirate_6", "man", "man", 20, SPAIN, 0, true));
		rCharacter.Dialog.Filename = "Quest\ForAll_dialog.c";
		rCharacter.dialog.currentnode = "SharpSeekSpy_fri";
		LAi_SetActorType(rCharacter);
		LAi_group_MoveCharacter(rCharacter, "EnemyFight");
		ChangeCharacterAddressGroup(rCharacter, pchar.location, "goto", "goto6");
		DoQuestCheckDelay("CannotFightCurLocation", 1.0);
		pchar.questTemp.Sharp.SeekSpy = "inDelNorte";
		pchar.quest.SharpSeekSpy_script.win_condition.l1 = "locator";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.location = "Shore55";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator_group = "quest";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator = "SharpSeekSpy";
		pchar.quest.SharpSeekSpy_script.function = "SharpSeekSpy_script";
		Group_DeleteGroup("Sharp_Group");
		string sGroup = "Sharp_Group";
		Group_FindOrCreateGroup(sGroup);
		sld = characterFromId("Sharp");
		LAi_SetHP(sld, 350.0, 350.0);
		SetHalfPerksToChar(sld, true);
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);

		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "���� '����������'";
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.mapEnc.type = "war";
		sld.hunter = "pirate";
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Map_CreateWarrior("", sld.id, 8);
	}
	else
	{
		SetTimerFunction("SharpSeekSpy_again", 0, 0, 3);
	}
}

void SharpSeekSpy_script(string qName)
{
	if (GetCharacterIndex("Emillio") != -1)
	{
		LAi_ActorTurnToCharacter(characterFromId("QuestMan_5"), pchar);
		sld = characterFromId("Emillio");
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else
	{
		pchar.questTemp.Sharp.SeekSpy = "over";
	}
}

void SharpSeekSpy_again(string qName)
{
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
	pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";	
}

void SharpSeekSpy_caveDialog()
{
	sld = characterFromId("QuestMan_5");
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SharpSeekSpy_fri";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_2()
{
	sld = characterFromId("Emillio");
	sld.dialog.currentnode = "SharpSeekSpy_Emi_1";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_3()
{
	DoQuestCheckDelay("CanFightCurLocation", 0.0);
	sld = characterFromId("Emillio");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	sld = characterFromId("QuestMan_5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    pchar.quest.SharpSeekSpy_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l1.character = "Emillio";
    pchar.quest.SharpSeekSpy_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l2.character = "QuestMan_5";
	pchar.quest.SharpSeekSpy_afterFight.function = "SharpSeekSpy_afterFight";
}

void SharpSeekSpy_afterFight(string qName)
{
	AddQuestRecord("SharpPearl_SeekSpy", "4");
	pchar.questTemp.Sharp.SeekSpy = "alwaysKnow";
	pchar.questTemp.Sharp = "seekSharp"; //����� ����� �������� �����
	CloseQuestHeader("SharpPearl");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� ���������� �������� Sharp   �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� �������     ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void PiratesLine_q1_tavernEnd()
{
	chrDisableReloadToLocation = false; 
	bDisableFastReload = false; 
	LAI_SetPlayerType(pchar);           
    DoReloadCharacterToLocation("PuertoPrincipe_tavern", "tables", "stay3");
    sld = CharacterFromID("QuestPirate1");
    LAI_SetSitType(sld);
}

void PiratesLine_q1_arrest(string qName)
{
	chrDisableReloadToLocation = true; 
	bDisableFastReload = true; 
	//LocatorReloadEnterDisable("Portroyal_town", "houseS1", true); //������� ��� �������
	GetCharacterPos(pchar, &locx, &locy, &locz);
    for (i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("QuestSold_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, 0, true));
		sld.City = "PortRoyal";
		//sld.CityType = "soldier";
		sld.BreakTmplAndFightGroup = true; //����������� �� �����
		sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "ArrestInPR";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, pchar.location, "patrol", "patrol16");
		if (i == 1) LAi_ActorDialog(sld, pchar, "", -1, 0);
		else LAi_ActorFollow(sld, characterFromId("QuestSold_1"), "", -1);
	}	
	sld = characterFromId("QuestPirate2");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));	
	LAi_SetActorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void PiratesLine_q1_toPrison()
{
	sld = characterFromId("QuestPirate2");
	sld.lifeDay = 0;
	ChangeCharacterAddress(sld, "none", "");
	RemovePassenger(pchar, sld);
	DoReloadCharacterToLocation("PortRoyal_prison",  "goto", "goto9");
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], true);
    DoQuestFunctionDelay("PiratesLine_q1_MorganInPrison", 10.0);
    sld = characterFromId("Henry Morgan");
    LAi_SetStayTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto13");
	locations[FindLocation("PortRoyal_fort")].loginNpc = true;
}

void PiratesLine_q1_MorganInPrison(string qName)
{
    sld = characterFromID("Henry Morgan");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "PiratesLine_q1_MorganGoTo", -1);
}

void PiratesLine_q1_MorganEnd()
{
	chrDisableReloadToLocation = false; 
	bDisableFastReload = false; 
	LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //������� ��� �������
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], false);
	pchar.questTemp.jailCanMove = true; //����� �������� ����� �� ������
	AddQuestRecord("Pir_Line_1_JohnBolton", "4");
	DoQuestReloadToLocation("PortRoyal_prison", "goto", "goto12", "");
    sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
}
//�������, ����� �3, ������ ���
void PiratesLine_q3_LoyHouse(string qName)
{
	AddQuestRecord("Pir_Line_3_KillLoy", "2");
	AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("��","���"));
	AddQuestUserData("Pir_Line_3_KillLoy", "sSex1", GetSexPhrase("","�"));
	pchar.questTemp.piratesLine = "KillLoy_toSeek";
}

void PiratesLine_q3_loginSeaWolf(string qName)
{
	if (GetCompanionQuantity(pchar) <= 1 && 6-sti(RealShips[sti(pchar.ship.type)].Class) <= 0)
	{
		sld = characterFromId("EdwardLoy");
		sld.dialog.currentnode   = "SeaWolf";
		sld.greeting = "CapSinkShip";
		pchar.questTemp.piratesLine = "KillLoy_SeaWolfBattle";
		AddQuestRecord("Pir_Line_3_KillLoy", "15");
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("��","��"));
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex1", GetSexPhrase("","�"));
		Group_AddCharacter("SW_Group", "EdwardLoy");			
		Group_SetType("SW_Group", "pirate");
		Group_SetGroupCommander("SW_Group", "EdwardLoy");
		sTemp = "quest_ship_" + (rand(4)+5);
		Group_SetAddress("SW_Group", "Cumana", "quest_ships", sTemp);
		Group_SetTaskAttack("SW_Group", PLAYER_GROUP);
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1.location_type = "town";
		pchar.Quest.PiratesLine_q3_over1.function = "PiratesLine_q3_over";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1.location_type = "seashore";
		pchar.quest.PiratesLine_q3_over2.function = "PiratesLine_q3_over";
	}
	else
	{
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1 = "ExitFromLocation";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1.location = "Cumana";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.function = "PiratesLine_q3_SeaWolfAgain";	
	}
}

void PiratesLine_q3_SeaWolfAgain(string qName)
{
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
	pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";	
}

void PiratesLine_q3_over(string qName)
{
	pchar.quest.PiratesLine_q3_over1.over = "yes";
	pchar.quest.PiratesLine_q3_over2.over = "yes";
	if (GetCharacterIndex("EdwardLoy") == -1)
	{
		QuestSetCurrentNode("Henry Morgan", "PL_Q3_GoodWork");
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_BRIGSW)
		{
			AddQuestRecord("Pir_Line_3_KillLoy", "17");
			pchar.questTemp.piratesLine.T1 = "KillLoy_GoodWork"; //��������� ���, ���� ��������			
		}
		else
		{
		    //#20171229-02 Check companion ships
		    bool bShipOK = false;
		    for(int i = 0; i < COMPANION_MAX; i++)
            {
                int cn = GetCompanionIndex(PChar, i);
                if(cn != -1)
                {
                    int iShipType = sti(characters[cn].ship.type);
                    if(iShipType != SHIP_NOTUSED)
                    {
                        if(sti(RealShips[iShipType].basetype) == SHIP_BRIGSW)
                        {
                            bShipOK = true;
                            break;
                        }
                    }
                }
            }
            //#20171231-01 Fix Low Quest
            if(bShipOK == true)
            {
                AddQuestRecord("Pir_Line_3_KillLoy", "17");
                pchar.questTemp.piratesLine = "KillLoy_GoodWork"; //��� ����, ���� �� ��������
                pchar.questTemp.KillLoy_GoodWork = true;
            }
            else //#20171229-02 Check companion ships
            {
                AddQuestRecord("Pir_Line_3_KillLoy", "18");
				pchar.questTemp.piratesLine.T1 = "KillLoy_LoyIsDied"; //��� ����, ���� �� ��������
                pchar.questTemp.KillLoy_LoyIsDied = true;
            }
		}
	}
	else
	{
		AddQuestRecord("Pir_Line_3_KillLoy", "16");
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","��"));
		pchar.questTemp.piratesLine = "KillLoy_loose"; //��� ������� ���, ������ ������
		sld = characterFromId("EdwardLoy");
		sld.lifeDay = 0;
		QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
	}
	group_DeleteGroup("SW_Group");
}
//�������, ����� �4, ������� ��������� ������
void PQ4_SeaPearl_login(string qName)
{
	pchar.quest.PQ4_SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	Group_FindOrCreateGroup("PearlGroup");
	Group_SetType("PearlGroup", "trade");
	for (int j = 1; j <= iTemp; j++)
	{        
		sTemp = "PearlCapitain_" + j;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "trader_"+(rand(15)+1), "man", "man", 10, PIRATE, 30, true));	
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetBalls(sld, "pirate");
		sld.ShipTaskLock = true;
		sld.Abordage.Enable = false;
		sld.SinkTenPercent = true; //�������� � �� �����
		sld.PearlTartane = true; //������� ������ �������, ����� �������
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> ������������
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_LockTask("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.PQ4_SeaPearl_DieHard1.function = "PQ4_SeaPearl_DieHard";
	Pchar.quest.PQ4_SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.PQ4_SeaPearl_DieHard2.function = "PQ4_SeaPearl_DieHard";
}

void PQ4_SeaPearl_Late(string qName)
{	
	pchar.quest.PQ4_SeaPearl_login.over = "yes";
	AddQuestRecord("Pir_Line_4_Pearl", "2");
	AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("","�"));
	pchar.questTemp.piratesLine = "PearlQ4_late";
	sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	QuestSetCurrentNode("Henry Morgan", "PL_Q4_late");
}

void PQ4_SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.over = "yes";
	pchar.quest.PQ4_SeaPearl_DieHard2.over = "yes";
	if (pchar.questTemp.Sharp == "SeaPearl_success")
	{	//�������� ���������
		AddQuestRecord("Pir_Line_4_Pearl", "3");
		AddQuestUserData("Pir_Line_4_Pearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
		AddQuestUserData("Pir_Line_4_Pearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
		pchar.questTemp.piratesLine = "PearlQ4_goodWork";
		QuestSetCurrentNode("Henry Morgan", "PL_Q4_goodWork");
		pchar.questTemp.piratesLine.Qty.SmallPearl = pchar.questTemp.Sharp.PearlAreal.SmallPearlQty;
		pchar.questTemp.piratesLine.Qty.BigPearl = pchar.questTemp.Sharp.PearlAreal.BigPearlQty;
	}
	else
	{	//��������� ���������
		AddQuestRecord("Pir_Line_4_Pearl", "4");
		AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("","��"));
		pchar.questTemp.piratesLine = "PearlQ4_badWork";
		QuestSetCurrentNode("Henry Morgan", "PL_Q4_badWork");
	}
	pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	CloseQuestHeader("SharpPearl");
}
//�������, ����� �5, ������ ����
void PQ5_meetInPortRoyal(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "officer_9", "man", "man", 20, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "�����";
	sld.rank = 20;
	sld.city = "PortRoyal";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5CapGoodly";
	sld.greeting = "Gr_EvilPirate";
    ChangeCharacterAddressGroup(sld, "PortRoyal_town", "patrol", "patrol16");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ5_inOrryHouse(string qName)
{
	pchar.questTemp.piratesLine = "PL5Hunter_exitReload";
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], true); //������� ������
	chrDisableReloadToLocation = true; 
	LAi_group_Delete("EnemyFight");

	sld = GetCharacter(NPC_GenerateCharacter("Aivory", "officer_7", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 100, 100, "blade28", "pistol3", 80);
	sld.name = "����";
	sld.lastname = "������";
	sld.city = "Pirates";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Hero";
	sld.greeting = "Gr_MiddPirate";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto1");

	sld = GetCharacter(NPC_GenerateCharacter("Orry", "officer_15", "man", "man", 27, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 100, 100, "topor2", "pistol3", 50);
	sld.name = "����";
	sld.lastname = "����";
	sld.city = "Pirates";
	sld.money = 51600;
	sld.SaveItemsForDead   = true; // ��������� �� ����� ����
	sld.DontClearDead = true;  // �� ������� ���� ����� 200�
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Orry";
	sld.greeting = "pirat_quest";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto2");

	pchar.quest.PQ5_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l1.character = "Aivory";
	pchar.quest.PQ5_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l2.character = "Orry";
	pchar.quest.PQ5_afterFight.function = "PQ5_afterFight";
}

void PQ5_afterChangeMainHero()
{
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], false);
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();	
	rCharacter = characterFromID("Orry");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	sld = characterFromID("Aivory");
	sld.dialog.currentnode = "PQ5Aivory";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	EndQuestMovie();
}

void PQ5_afterChangeMainHero2()
{	
	rCharacter = characterFromID("Orry");
	LAi_group_MoveCharacter(rCharacter, "EnemyFight");
	sld = characterFromID("Aivory");			
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(pchar, true);
}

void PQ5_afterFight(string qName)
{
	AddQuestRecord("Pir_Line_5_Hunter", "11");
	AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
	pchar.questTemp.piratesLine = "PL5Hunter_toMorgan";
	chrDisableReloadToLocation = false; 
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1 = "location";
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1.location = "PortRoyal_tavern";
	Pchar.quest.PQ5_inPortPoyalTavern.function = "PQ5_inPortPoyalTavern";
}

void PQ5_inPortPoyalTavern(string qName)
{
	FreeSitLocator("PortRoyal_tavern", "sit3");
	sld = characterFromID("CapGoodly");
	sld.dialog.currentnode = "PQ5CapGoodlyEnd";
	LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit3");
}

void PQ5_Morgan_1()
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto2", "PQ5_Morgan_2", -1.0);
}

void PQ5_Morgan_4()
{
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();	
	rCharacter = characterFromID("CapGoodly");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	sld = characterFromID("Henry Morgan");
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ5_Morgan_5()
{
	LAi_group_Delete("EnemyFight");
	LAi_SetPlayerType(pchar);
	sld = characterFromID("CapGoodly");
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1.character = "CapGoodly";
	pchar.quest.PQ5_Morgan_afterFight.function = "PQ5_Morgan_afterFight";
	LAi_SetFightMode(pchar, true);
}

void PQ5_Morgan_afterFight(string qName)
{
	QuestSetCurrentNode("Henry Morgan", "PL_Q5_afterFight");
	AddQuestRecord("Pir_Line_5_Hunter", "13");
	AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("","�"));
}
//�������, ����� �6, �������
void PQ6_ShoreBattle(string qName)
{
    LAi_group_Delete("EnemyFight"); 
	LocatorReloadEnterDisable("Shore7", "boat", true); //������� ����� � ����
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//����
	string sTemp = NationShortName(sti(pchar.nation));
    for (i=1; i<=5; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate_"+i, "pirate_"+(rand(24)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		//sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		//if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto8");
    }
	//�����
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 3); i++)
    {
        iTemp = 15 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate_"+i, "officer_"+(rand(63)+1), "man", "man", iTemp, PIRATE, -1, true));
        FantomMakeCoolFighter(sld, iTemp, 80, 80, BLADE_LONG, "pistol3", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        PlaceCharacter(sld, "goto", PChar.location);
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    Pchar.quest.PQ6_JungleDialog.win_condition.l1 = "location";
    Pchar.quest.PQ6_JungleDialog.win_condition.l1.location = "Common_jungle_01";
    Pchar.quest.PQ6_JungleDialog.function = "PQ6_JungleDialog";
}

void PQ6_JungleDialog(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation("Common_jungle_01")], true);
	chrDisableReloadToLocation = true;
	string sModel = pchar.model;
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirateHead", sModel, "man", pchar.model.animation, 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 90, 90, "blade27", "pistol6", 100);
	sld.name = pchar.name;
	sld.lastname = pchar.lastname;
    sld.dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "QuestPirateHead";
	sld.SaveItemsForDead = true;
	ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto1");
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ6_JungleBattle()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	//����
	string sTemp = NationShortName(sti(pchar.nation));
    for (i=1; i<=5; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate2_"+i, "pirate_"+(rand(24)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
	//�����
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 3); i++)
    {
        iTemp = 17 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2_"+i, "officer_"+(rand(63)+1), "man", "man", iTemp, PIRATE, -1, true));
        FantomMakeCoolFighter(sld, iTemp, 90, 90, "topor2", "pistol6", 100);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto2");
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "PQ6_afterBattle");
}
//�������, ����� �7, ����� ��������
void PQ7_FriendLinney(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.piratesLine") < 20)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FriendLinney", "", "man", "man", 20, sti(pchar.nation), 5, true));							
		SetCaptanModelByEncType(sld, "pirate");
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.DeckDialogNode = "FriendLinney";
		FantomMakeCoolFighter(sld, 20, 80, 70, "blade32", "pistol3", 20);
		FantomMakeCoolSailor(sld, SHIP_LUGGER, "", CANNON_TYPE_CULVERINE_LBS16, 70, 70, 70);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.Ship.Mode = "Pirate";
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "DontRansackCaptain");		
		sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
		Group_AddCharacter("FriendLinney_Group", "FriendLinney");			
		Group_SetType("FriendLinney_Group", "pirate");
		Group_SetGroupCommander("FriendLinney_Group", "FriendLinney");
		Group_SetAddress("FriendLinney_Group", "Hispaniola1", "quest_ships", "quest_ship_4");
		Group_SetTaskNone("FriendLinney_Group");
	}
	else
	{
		AddQuestRecord("Pir_Line_7_Soukins", "3");
		AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","�"));																
		pchar.questTemp.piratesLine = "Soukins_LaVegaLate";
		QuestSetCurrentNode("Henry Morgan", "PL_Q7_LaVegaLate");
	}
}

void PQ7_LoginLeon()
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("FriendLinney_Group"); //������ ����� ����� ������
	sld = GetCharacter(NPC_GenerateCharacter("LeonCapitain", "", "man", "man", 25, PIRATE, 30, true));							
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "LeonCapitain";
	sld.greeting = "CapSinkShip";
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade32", "pistol6", 50);
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "����", CANNON_TYPE_CULVERINE_LBS24, 80, 80, 80);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.Ship.Mode = "Pirate";
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");

	string sGroup = "Leon_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 

	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	sld.mapEnc.type = "warrior";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������ '����'";
	Map_CreateWarrior("shore33", "LeonCapitain", 30);
	Log_TestInfo("������ ���� ����������.");
}

void PQ7_inSoukinsResidence(string qName)
{
	QuestSetCurrentNode("Henry Morgan", "PL_Q7_BadWork"); //����, ���� ������ �� ������
	if (IsLoginTime())
	{
		DoQuestFunctionDelay("PQ7_inSoukinsResidence_2", 1.5);
	}
}

void PQ7_inSoukinsResidence_2(string qName)
{
	LAi_SetActorType(pchar);
	sld = characterFromId("Richard_Soukins");
	QuestSetCurrentNode("Richard_Soukins", "PL_Q7_5");
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ7_loadToRecidence(string qName)
{
	DoQuestReloadToLocation("PuertoPrincipe_townhall", "reload", "reload2", "");
}

void PQ7_setBattleShip(string qName)
{	
	sld = &locations[FindLocation("PuertoPrincipe_townhall")];
	DeleteAttribute(sld, "reload.l2"); //������ ����������� ���������� � ��������
	//#20180903-01 Change from 100 minutes to 24 hours
	if (GetQuestPastMinutesParam("questTemp.piratesLine") > 100)
	{
		Log_TestInfo("������� �������� �� ����� ����������. �� ����� ������� ����� � ����.");
		pchar.questTemp.piratesLine = "Soukins_battlshipLate";
		AddQuestRecord("Pir_Line_7_Soukins", "10");
		AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","�"));
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("QuestCap_PL7", "SpaOfficer1", "man", "man", 40, SPAIN, -1, true));							
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "QuestCap_PL7";
		sld.DeckDialogNode = "QuestCap_PL7_inDeck";
		sld.greeting = "CapSinkShip";
		FantomMakeCoolFighter(sld, 40, 90, 90, "blade32", "pistol4", 200);
		FantomMakeCoolSailor(sld, SHIP_BATTLESHIP, "����������", CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "DontRansackCaptain");
		sld.AlwaysSandbankManeuver = true;
		sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
		sld.DontRansackCaptain = true;
		SetCharacterPerk(sld, "FastReload");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");

		string sGroup = "Quest_Ship";
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 

		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "��������";
		Map_CreateTraderXZ(1009.22, -992.708, 988.514, 515.407, "QuestCap_PL7", 15);
		Log_TestInfo("������� �������� ����� ��������.");	
	}
}

void PQ7_winBattleShip(string qName)
{
	pchar.questTemp.piratesLine = "Soukins_battlshipWin";
	QuestSetCurrentNode("Henry Morgan", "PL_Q7_GoodWork");
	AddQuestRecord("Pir_Line_7_Soukins", "13");
	pchar.quest.PQ7_BattleShip_dieHard.over = "yes";
}

void PQ8_timeOver(string qName) //������� �������
{
	pchar.questTemp.piratesLine = "over";
	sld = characterFromId("Henry Morgan");
	ChangeCharacterAddress(sld, "none", "");
	AddQuestRecord("Pir_Line_8_Panama", "2");
	AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Pir_Line_8_Panama");
	SetTimerFunction("PQ8_openPanama", 0, 0, 40);
	QuestSetCurrentNode("Oliver_Green", "PL_Q8_over"); //���� ���������
}

void PQ8_openPanama(string qName) //������� ������
{
	LocatorReloadEnterDisable("Shore48", "reload1_back", false); 
	LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false);
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "First time";
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
    LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void PQ8_openPanama_2(string qName) //������� ������
{
	sld = characterFromId("Henry Morgan");
	if (pchar.questTemp.piratesLine == "Panama_backToShip") 
	{
		SetTimerFunction("PQ8_openPanama_3", 0, 0, 360); // Warship 18.07.09 fix - ���� 180 ������-��
	}
	else 
	{
		sld.dialog.currentnode = "I_know_you_good";
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		LAi_SetImmortal(sld, true);
		LAi_LoginInCaptureTown(sld, false);
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	//���������� ��������
	iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}               
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "I_know_you_good";
    }
    //���������� �� ����� ��������
	iTemp = GetCharacterIndex("Richard_Soukins");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}                   
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "First time";
    }
	LocatorReloadEnterDisable("Panama_ExitTown", "reload4", false); 
	SetLocationCapturedState("Panama_town", false);
	bDisableLandEncounters = false;
	pchar.quest.PL_Q8_backFight_1.over = "yes"; //�� ������ ������
}

void PQ8_openPanama_3(string qName) //������ ����� ������� � ������
{
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "PL_Q8_afterPanama";
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	LAi_SetImmortal(sld, true);
	LAi_LoginInCaptureTown(sld, false);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void PQ8_PanamaTimerOver(string qName)
{
    if (IsEntity(worldMap))
    {
        if (!bQuestCheckProcessFreeze) // ����� ��������
		{
	        pchar.quest.PQ8_PanamaTimerOver_01.over = "yes"; // �����, ���� ��� �����������
	        pchar.quest.PQ8_PanamaTimerOver_02.over = "yes";
			pchar.quest.PQ8_EnterPortoBello.over = "yes"; //������� ���������� �� ����
            
            aref arOldMapPos;
			makearef(arOldMapPos, worldMap.old);
            WdmPrepareMapForAbordage(arOldMapPos);
            MakeCloneShipDeck(pchar, true); // ������� ������
            DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
	        ReloadFromWMtoL_complete();
	        
            sld = characterFromID("Henry Morgan");
            ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
            LAi_SetWarriorType(sld);
	        LAi_warrior_DialogEnable(sld, true);
	        sld.dialog.currentnode = "PL_Q8_timeOver";
   	        // ==> �������
            for (i=1; i<5; i++)
        	{
                sTemp = "pirate_" + i;
                sld = GetCharacter(NPC_GenerateCharacter(sTemp, sTemp, "man", "man", 15, PIRATE, 1, true));
                sld.dialog.Filename = "Quest\sailors_dialog.c";
	            sld.dialog.currentnode = "Morgan_wait_you";
                LAi_SetWarriorType(sld);
                LAi_warrior_DialogEnable(sld, true);
                LAi_SetLoginTime(sld, 0.0, 24.0);
                LAi_SetHP(sld, 100.0, 100.0);
                ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto"+i);
            }
            pchar.quest.Munity = "";  // ������� ������ � ������ (�������, � �� ����� �� ��������)
            LAi_LockFightMode(pchar, true);
		}
		else
		{   // ������� �� ���������� (������ ��������)
      		Pchar.quest.PQ8_PanamaTimerOver_01.win_condition.l1 = "MapEnter";
            Pchar.quest.PQ8_PanamaTimerOver_01.function = "PQ8_PanamaTimerOver";
		}
	}
	else
	{   // �������� ������ �� �����, ��� ����� ������, �� �� �� �� ���
		Pchar.quest.PQ8_PanamaTimerOver_02.win_condition.l1 = "MapEnter";
        Pchar.quest.PQ8_PanamaTimerOver_02.function = "PQ8_PanamaTimerOver";
	}
}

void PQ8_EnterPortoBello()
{
	sld = characterFromId("Henry Morgan");
	LAi_SetImmortal(sld, false);
	pchar.quest.PQ8_PanamaTimerOver.over = "yes"; //������� ������ 
	//bQuestDisableMapEnter = true;
}

void PQ8_MorganInPortoBello()
{
	chrDisableReloadToLocation = true; 
	DoQuestFunctionDelay("PQ8_MorganInPortoBello_2", 3.0);	
}

void PQ8_MorganInPortoBello_2(string qName)
{	
	sld = characterFromId("Henry Morgan");
	LAi_LoginInCaptureTown(sld, true); 
	LAi_SetCurHPMax(sld);
	sld.dialog.currentNode = "PL_Q8_PBResidence";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PQ8_PBExitResidence(string qName)
{
	iTemp = GetCharacterIndex("Henry Morgan");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("John Morris");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	sld = characterFromId("Richard_Soukins");
	sld.DeckDialogNode = "PL_Q8_deck_2";
	AddQuestRecord("Pir_Line_8_Panama", "5");
	pchar.Quest.PQ8_fromPBport.win_condition.l1 = "EnterToSea";
	pchar.Quest.PQ8_fromPBport.function = "PQ8_fromPBport";
	SetTimerFunction("PQ8_controlShore48", 0, 0, 2);
}

void PQ8_fromPBport(string qName)
{
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1.location_type = "town";
	pchar.Quest.PQ8_controlShore48_1.function = "PQ8_controlShore48";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1.location_type = "seashore";
	pchar.Quest.PQ8_controlShore48_2.function = "PQ8_controlShore48";
}

void PQ8_controlShore48(string qName)
{
	pchar.Quest.PQ8_controlShore48.over = "yes";
	pchar.Quest.PQ8_controlShore48_1.over = "yes";
	pchar.Quest.PQ8_controlShore48_2.over = "yes";
	if (pchar.location == "Shore48")
	{	//�� ������� � �� ����� -->
		LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], true); //��������� ������� ��� ������
		LocatorReloadEnterDisable("Shore48", "boat", true); //�� ���� �������� � ����
		chrDisableReloadToLocation = true; 
		bDisableLandEncounters = true; //���������� �� �������
		pchar.questTemp.piratesLine = "Panama_inShore";
		pchar.questTemp.piratesLine.crewHero = makeint(GetCrewQuantity(pchar) / 100 / 2);	//�������� ���-�� ������� �� ��
		if (sti(pchar.questTemp.piratesLine.crewHero) > 5) pchar.questTemp.piratesLine.crewHero = 5;
		pchar.questTemp.piratesLine.crewRichard = 3;   //�������� ���-�� ������� �� ��������
		//����� ��. ���������������� �� ���� 3 �����������.
		SetCrewQuantity(pchar, GetMinCrewQuantity(pchar)); //����������� ������� �� ���
		iTemp = sti(pchar.questTemp.piratesLine.crewHero) ; //����� ������� ������ ��
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHpirate_"+i, "pirate_"+(rand(24)+1), "man", "man", sti(pchar.rank), PIRATE, -1, true));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }	
        for (i=1; i<=iTemp; i++) //��������� ��
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHmush_"+i, GetPirateMushketerModel(), "man", "mushketer", sti(pchar.rank), PIRATE, -1, false));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }
		//����� ��������
		iTemp = sti(pchar.questTemp.piratesLine.crewRichard); //����� ������� ������ ��������
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSpirate_"+i, "pirate_"+(rand(24)+1), "man", "man", 25, PIRATE, -1, true));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
        for (i=1; i<=iTemp; i++) //��������� ��������
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSmush_"+i, GetPirateMushketerModel(), "man", "mushketer", 25, PIRATE, -1, false));
            LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			TakeNItems(sld,"potion1", rand(2)+1);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
		//������� ��������
        for (i=1; i<=3; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSofficer_"+i, "officer_"+(rand(63)+1), "man", "man", 30, PIRATE, -1, true));
            FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol4", 100);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto4");
		}
		//��� �������
		sld = characterFromId("Richard_Soukins");
		sld.dialog.currentNode = "Shore48";
		LAi_SetImmortal(sld, false);
		LAi_NoRebirthEnable(sld);
		GiveItem2Character(sld, "blade23");
		EquipCharacterbyItem(sld, "blade23");
		GiveItem2Character(sld, "pistol4");
		EquipCharacterbyItem(sld, "pistol4");
		TakeNItems(sld,"potion1", 5);
		RemoveCharacterCompanion(pchar, sld); //������� �������� �� �����������
		ChangeCharacterAddressGroup(sld, "Shore48", "goto", "goto11");	
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
		//���������� �� ���� � �������
		pchar.Quest.PQ8_jungle_05.win_condition.l1 = "location";
		pchar.Quest.PQ8_jungle_05.win_condition.l1.location = "Panama_jungle_05";
		pchar.Quest.PQ8_jungle_05.function = "PQ8_jungle_05";
	}
	else
	{	//�� �� ����� ��� �� ���� ����� -->
		iTemp = GetCharacterIndex("Richard_Soukins");
		if (iTemp != -1)
		{
			if(IsCompanion(&characters[iTemp]))  
			{
				RemoveCharacterCompanion(pchar, &characters[iTemp]);
			}                   
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
        //���������� �� ����� ��������
		iTemp = GetCharacterIndex("Jackman");
		if (iTemp != -1)
		{              
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
		AddQuestRecord("Pir_Line_8_Panama", "6");
		AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("��","���"));
		AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","�"));
		CloseQuestHeader("Pir_Line_8_Panama");
		SetTimerFunction("PQ8_openPanama", 0, 0, 40);
		LocatorReloadEnterDisable("Shore48", "reload1_back", true); //�������� ������� � ������
		LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		pchar.questTemp.piratesLine = "over";
	}
}

void PQ8_jungle_05(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- ���� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//��� �������
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- ������� ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=12; i<=18; i++) //max - 21
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==16) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));       
		FantomMakeCoolFighter(sld, sti(pchar.rank), 80, 80, "blade34", "pistol6", 80);
		sld.BreakTmplAndFightGroup = true; 
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 8;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 6;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 3;
	for (i=1; i<=iTemp; i++) //max - 11
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_04.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_04.win_condition.l1.location = "Panama_jungle_04";
	pchar.Quest.PQ8_jungle_04.function = "PQ8_jungle_04";
}


void PQ8_jungle_04(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- ���� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//��� �������
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- ������� ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=13; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==14) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));      
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 100);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	for (i=14; i<=17; i++) //�������
    {
        if (i==14 || i==16) sTemp = "indsair2";
		else sTemp = "indsar1";
		sld = GetCharacter(NPC_GenerateCharacter("IndEnemy_"+i, "indsair2", "man", "man", Rank, SPAIN, -1, true)); //to_do ��������
		FantomMakeCoolFighter(sld, Rank, 90, 90, "topor2", "", 5);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_03.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_03.win_condition.l1.location = "Panama_jungle_03";
	pchar.Quest.PQ8_jungle_03.function = "PQ8_jungle_03";
}

void PQ8_jungle_03(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- ���� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//��� �������
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- ������� ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=16; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==13) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		sld.BreakTmplAndFightGroup = true; 
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_ExitTown.win_condition.l1 = "location";
	pchar.Quest.PQ8_ExitTown.win_condition.l1.location = "Panama_ExitTown";
	pchar.Quest.PQ8_ExitTown.function = "PQ8_ExitTown";
}

void PQ8_ExitTown(string qName)
{ 
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(LAi_IsDead(&characters[iTemp]))
	{	//������� �����, ������� ���������
		AddQuestRecord("Pir_Line_8_Panama", "7");	
		pchar.questTemp.piratesLine = "Panama_RichardGoodWork";
	}
	else
	{	//������� ���, ������� ���������
		AddQuestRecord("Pir_Line_8_Panama", "8");	
		pchar.questTemp.piratesLine = "Panama_RichardBadWork";
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
	}
	chrDisableReloadToLocation = true;
//	pchar.questTemp.piratesLine = "Panama_inExitTown"; // Warship FIX 19.07.09 - �������� ���� �� ��������
	//--------------------------- ���� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc15");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc16");
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc17");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc18");
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+(i+10));
		}
	}
    //--------------------------- ���� ������� ------------------------------
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMpirate_"+i, "pirate_"+(rand(24)+1), "man", "man", 25, PIRATE, 10, true));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc20");
	}
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMmush_"+i, "mushketer_"+(rand(4)+1), "man", "mushketer", 25, PIRATE, 10, false));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc19");
	}
    //--------------------------- ������� ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=15; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==12) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
    for (i=1; i<=10; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_ExitTown_afterFight");
}

void PQ8_piratesInPanama(string qName)
{
	DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured"); //����� ����� ����� ����
	//������� ���� ������ - ����������
	rCharacter = characterFromId("Panama_Mayor");
	sld = GetCharacter(NPC_GenerateCharacter("FantomMayor", rCharacter.model, "man", "man", sti(rCharacter.rank), sti(rCharacter.nation), -1, false));
	sld.quest.type = "hovernor";
	sld.City = "Panama";
	sld.location = "Panama_TownhallRoom";
	sld.greeting = "spa_gov_common";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
    sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.Dialog.CurrentNode = "PQ8_Mayor";
	LAi_SetStayType(sld);
	LAi_LoginInCaptureTown(sld, true);
	//--------------------------- ���� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    //--------------------------- ���� ������� ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
}	

void PQ8_MorganInPanama_1(string qName)
{
	chrDisableReloadToLocation = true;
	//������ ������� ����
	sld = ItemsFromID("keyPanama");
	sld.shown = true; 
	sld.startLocation = "Panama_prison";
	sld.startLocator = "item1";
	BackItemDescribe("keyPanama");
	BackItemName("keyPanama");
	//������� � ����� � �� ������
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentNode = "PL_Q8_Panama1";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_ResEnterBox(string qName)
{
	if (CheckCharacterItem(pchar, "keyPanama"))
    {
		TakeItemFromCharacter(pchar, "keyPanama");
		chrDisableReloadToLocation = true;
		sld = characterFromId("Henry Morgan");
		sld.dialog.currentNode = "PL_Q8_Panama2";		
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1 = "ExitFromLocation";
        Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1.location = pchar.location;
        Pchar.quest.PL_Q8_ResEnterBox_2.function = "PL_Q8_ResEnterBox_2";
	}
}

void PL_Q8_ResEnterBox_2(string qName)
{
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
	pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
}

void PL_Q8_inPanamaFort2(string qName)
{
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1 = "location";
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1.location = "Panama_town";
	Pchar.quest.PL_Q8_inPanamaPirates_1.function = "PL_Q8_inPanamaPirates_1";
}

void PL_Q8_inPanamaPirates_1(string qName)
{
	chrDisableReloadToLocation = true;	
	//--------------------------- ������ ���� � ���������� ������� ------------------------------
	//����������� ������ ��
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //����������� ������ ��������
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //������� ��������
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    //--------------------------- ���� ������� ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}	
	//����������� �����
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirate", "pirate_"+(rand(24)+1), "man", "man", 25, PIRATE, 0, true));
	sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentNode = "PL_Q8_QFackMorgan";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_backFight_1(string qName) 
{
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==2) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, 12, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc1");
    }
    for (i=1; i<=4; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, 12, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc3");
	}
	//�����������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� �������     �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   ����������        ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------- ��������� � ����������� ---------------------
void WaitressFack_null(string qName) //����� ����� ����������
{
	LocatorReloadEnterDisable(pchar.questTemp.different.FackWaitress.City + "_tavern", "reload2_back", true);
	pchar.questTemp.different = "free";
	pchar.quest.WaitressFack_inRoom.over = "yes"; 
	DeleteAttribute(pchar, "questTemp.different.FackWaitress");
}

void WaitressFack_inRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("WaitressFack_Enter", 10.0 + frand(10.0));
}

void WaitressFack_Enter(string qName)
{	
	LAi_group_Delete("EnemyFight"); 
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	if (pchar.questTemp.different.FackWaitress.Kick == "0")
	{	//��������
		iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter("BerglarWairessQuest", "officer_"+(rand(63)+1), "man", "man", iTemp, PIRATE, -1, true));
		FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
		sld.dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "WaitressBerglar";	
		sld.greeting = "Enc_Raiders"; 
 		//������ ������� ����������
		rCharacter = characterFromId(locations[reload_location_index].fastreload + "_waitress");
		rCharacter.model = "girl_" + (rand(7)+1);
		SetRandomNameToCharacter(rCharacter);
		FaceMaker(rCharacter);  
	}
	else
	{
        sld = characterFromId("WairessQuest");
	}
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void WaitressFack_outRoom()
{
	// ==> �������� ������, ������� � ������.
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    }
    pchar.money = 0;
    // <== �������� ������, ������� � ������.
	AddCharacterExpToSkill(pchar, "Pistol", 100);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	DoQuestCheckDelay("OpenTheDoors", 10.0);
	pchar.questTemp.different = "FackWaitress_noMoney"; //���� ��������
}

void WaitressFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingLight", 30);
	AddCharacterExpToSkill(pchar, "Fencing", 30);
	AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
	LAi_SetFightMode(pchar, true);
	pchar.questTemp.different = "FackWaitress_fighted"; //���� �������� ���������
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.WaitressFack_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.WaitressFack_afterFight.win_condition.l1.character = "BerglarWairessQuest";
	pchar.quest.WaitressFack_afterFight.win_condition = "OpenTheDoors";
}

void WaitressFack_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
													
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "FackWaitress_facking"; 
}

// ----------------- ������������� ������� ������� ---------------------
void HostessChurch_null(string qName) //����� ����� 
{
	//���� ����� ��� ����, �� ������ ������ ������������
	if (characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch == "taken") 
	{
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "baster";
		if (CheckAttribute(pchar,"HellSpawnLocation")) LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);
	}
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.HostessChurch");
}

// ----------------- ������� ������� �� ����� ---------------------
void ShipyardsMap_returnCFN(string qName) 
{
	string  sName;
	aref	arDis, arRld;
	int location_index = FindLocation(pchar.questTemp.different.ShipyardsMap.city + "_town");
    makearef(arRld, Locations[location_index].reload);
    int		Qty = GetAttributesNum(arRld);
    for (int a=0; a<Qty; a++)
    {
    	arDis = GetAttributeN(arRld, a);
		sName = arDis.go;
    	if (findsubstr(sName, "_shipyard" , 0) != -1)
    	{
			arDis.close_for_night = true;
			break;
    	}
    }
	LocatorReloadEnterDisable(pchar.questTemp.different.ShipyardsMap.city + "_shipyard", "reload2", false);
}

// ----------------- ����� ������ ���� � ������� ---------------------
void TakeMayorsRing_null(string qName) //����� ����� 
{
	pchar.questTemp.different = "free";
	if (CheckCharacterItem(pchar, "MayorsRing"))
    {
		TakeItemFromCharacter(pchar, "MayorsRing");
		AddQuestRecord("SeekMayorsRing", "4");
		AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase("","�"));
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		ChangeCharacterReputation(pchar, -3);
	}
	else
	{
		if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
		{
			AddQuestRecord("SeekMayorsRing", "5");
			AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			ChangeCharacterReputation(pchar, -5);
		}
	}
	DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
}

// ----------------- �������� ������� ������ ---------------------
void GiveShipLetters_null(string qName) //����� ����� 
{
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
}

void CheckShipLetters(string qName)
{	
	if (!CheckCharacterItem(pchar, "CaptainBook"))
	{
		Log_QuestInfo("������ �� �����!!");
		sld = ItemsFromID("CaptainBook");
		sld.shown = false;
		pchar.questTemp.different = "free";
		pchar.questTemp.different.GiveShipLetters.over = "yes"; //������� ������ 
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
	}
}
// ----------------- �������� ������� ������ ---------------------

// ----------------- ������ �� ���� ������� ������� ---------------------
void SexWithHostess_null(string qName) //����� ����� 
{
	if (pchar.questTemp.different.HostessSex == "toRoom")
	{
		sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
		LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
	}
	LAi_SetOwnerTypeNoGroup(sld);
	sld.dialog.currentnode = "First time";
	sld.quest.NotGoneToSex = true; //�� ������. ����� ������ �� �����
	DeleteAttribute(pchar, "questTemp.different.HostessSex");
	pchar.questTemp.different = "free";
}

void SexWithHostess_goToRoom()  
{
	chrDisableReloadToLocation = true;
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", pchar.questTemp.different.HostessSex.city + "_Brothel_room", "goto", "goto3", "OpenTheDoors", -1);
	pchar.quest.SexWithHostess_inRoom.win_condition.l1 = "location";
	pchar.quest.SexWithHostess_inRoom.win_condition.l1.location = pchar.questTemp.different.HostessSex.city + "_Brothel_room";
	pchar.quest.SexWithHostess_inRoom.function = "SexWithHostess_inRoom";
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", false);
}

void SexWithHostess_inRoom(string qName)
{
	DoQuestFunctionDelay("SexWithHostess_inRoom_2", 1.5);
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
}

void SexWithHostess_inRoom_2(string qName)
{
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	sld.dialog.currentnode = "Hostess_inSexRoom";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SexWithHostess_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "HostessSex";
}

// ----------------- ���������� ��������  ---------------------
void SetCapitainFromCityToSea(string qName) //�������� � ���� ����, ������� ������ ��������� � ������
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.location	= "none";
		sld.location.group = "";
		sld.location.locator = "";
		//� ������� ������ ����
		string sGroup = "PorpmansShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//���������� ������ � ��������� ����
		sld.quest = "InMap"; //������ ���� ����������� ����
		sld.quest.targetCity = SelectNotEnemyColony(sld); //��������� �������, ���� ���������� ���
		sld.quest.stepsQty = sti(sld.quest.stepsQty) + 1; //���������� ������� � ����
		Log_TestInfo("���������� ��� " + sld.id + " ����� �� " + sld.city + " � ���������� �: " + sld.quest.targetCity);
		//��������� �����, ���� ������� ���������. ����� ����� �� ��������� ����� �� � ������
		sTemp = GetArealByCityName(sld.city);
		sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
		//�� �����
		iTemp = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //���� ������� ���� � �������
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, iTemp);
		//���� ����� ����, ��� ��� ���� � ������ �����
		AddSimpleRumourEx(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �������� ����� " + GetFullName(sld) + ", ����� ���� � ����. �� ������, �� �������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'? ��� ���, �� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"���� ��� ����� ������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ��� �������� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + " ���� ������ ����."), 
			sld.city, iTemp, 1, "PortmansBook_DeliveryToCap", sld.id);
		//--> ������ ���� �� ���� � ���� �������� ��������
		sTemp = sld.id; //Id ����, ������� ������� �������
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //���� ����������
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //������� ����, ����� ����������
		//��������. � �������� ������ ��������� ������� ������ �� �������   PortmansBook_Delivery    #TEXT   5
		//� ������ �������� ������� �����, ��������� � ����� ������ �� quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 5;
		//����������� ����� � ���� �����
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SetRobberFromSeaToMap(string qName) //�������� � ���� ����-����, ������� ���� ����� �� ����� � �����
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		//� ������� ������ ����
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//���������� ������ � ��������� ����
		sld.quest = "InMap"; //������ ���� ����������� ����
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //��������� �������, ���� ���������� ���
		Log_TestInfo("���-��� " + sld.id + " ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetCity);
		//�� �����
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//���� ����� ����, ��� ��� ���� � ������ �����
		AddSimpleRumourEx(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �������� ����� " + GetFullName(sld) + ", ����� ���� � ����. �� ������, �� �������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'? ��� ���, �� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"���� ��� ����� ������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ��� �������� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + " ���� ������ ����."), 
			sld.city, iTemp, 1, "Portmans_SeekShip_rum", sld.id);
		//--> ������ ���� �� ���� � ���� �������� ��������
		sTemp = sld.id; //Id ����, ������� ������� �������
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //���� ����������
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //������� ����, ����� ����������
		//��������. � �������� ������ ��������� ������� ������ �� �������   PortmansBook_Delivery    #TEXT   5
		//� ������ �������� ������� �����, ��������� � ����� ������ �� quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")].id + "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//����������� ����� � ���� �����
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SeekShip_checkAbordage(string qName) //���-��� ������� �����������
{	
	//�������, ���� ������� ���� ��� ��������
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	bOk = false;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(pchar, i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			if (sld.ship.name == rCharacter.quest.PortmansSeekShip.shipName && 
				RealShips[sti(sld.ship.type)].BaseName == rCharacter.quest.PortmansSeekShip.shipTapeName &&
				RealShips[sti(sld.Ship.Type)].basetype == rCharacter.quest.PortmansSeekShip.shipTape)
			{
				bOk = true;
			}
		}
	}	
	//������� �� ����������� ��������
	sld = characterFromId(pchar.quest.(qName).CapId);
	sTemp = "SeekShip_checkSink" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //������� ���������� �� ������
	if (bOk)
	{		
		rCharacter.quest = "SeekShip_success"; //���� ��������� ������ �� �������
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "5");
	}
	else
	{
		rCharacter.quest = "SeekShip_sink"; //���� ��������� �����, ������ ������
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "9");
	}
}

void SeekShip_checkSink(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	rCharacter.quest = "SeekShip_sink"; //���� ��������� �����, ������ ������
	sTemp = rCharacter.id + "Portmans_SeekShip";
	AddQuestRecordEx(sTemp, "Portmans_SeekShip", "8");
	sTemp = "SeekShip_checkAbordage" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //������� ���������� �� �������
}

// ----------------- ������ ������ � ������ ---------------------
void ChurchNightGuard_exitFromLoc(string qName)
{
	DeleteAttribute(pchar, "PostEventQuest.questDelay.ChurchNightGuard_timerInChurch"); //������� ������ �� ��������� ��������
	if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0) pchar.questTemp.different.Church_NightGuard.NightQty = 1;
	else pchar.questTemp.different.Church_NightGuard.NightQty = sti(pchar.questTemp.different.Church_NightGuard.NightQty) + GetQuestPastDayParam("questTemp.different.Church_NightGuard");
	Log_TestInfo("���-�� ����� � ������: " + pchar.questTemp.different.Church_NightGuard.NightQty);
	if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
	{
		sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "4");
		AddQuestUserData(sTemp, "sSex", GetSexPhrase("","�"));
		else
		{
			if (GetTime() > 6.0 && GetTime() < 23.99)
			{
				SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //����������� ����
			}
			else
			{
				sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
				AddQuestRecordEx(sTemp, "Church_NightGuard", "3");
				AddQuestUserData(sTemp, "sSex", GetSexPhrase("","�"));
				AddQuestUserData(sTemp, "sSex1", GetSexPhrase("��","��"));
				CloseQuestHeader(sTemp);
				DeleteAttribute(pchar, "questTemp.different.Church_NightGuard"); //������� ����
				ChangeCharacterReputation(pchar, -20);
			}
		}
	}
}

void ChurchNightGuard_timerInChurch(string qName)
{
	int iRank, num;
	if (pchar.questTemp.different.Church_NightGuard.chance == pchar.questTemp.different.Church_NightGuard.NightQty)
	{	//��������� �����
		pchar.quest.ChurchNightGuard_exitFromLoc.over = "yes"; //������� ���������� �� ����� �� �������
		pchar.questTemp.different.Church_NightGuard.NightQty = 3; //�������� �������� ���� ���������
		pchar.questTemp.different.Church_NightGuard.fight = true; //���� ������
        chrDisableReloadToLocation = true; // ������� ����� �� �������.
		sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "5");		
        LAi_group_Delete("EnemyFight");
		//--> ������� ���� 
		num = rand(1)+2;
		if (sti(pchar.rank) > 6) 
		{
			if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
			else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
		}
		else  
		{	//�������� ������� ���� �� ������ ����
			if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
			else 
			{
				iRank = 1;
				num = 1;
			}
		}	
		//<-- ������� ���� 		
		for (i=1; i<=num; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+10), "man", "man", iRank, PIRATE, 0, true));
			SetFantomParamFromRank(sld, iRank, true);         
			LAi_SetWarriorType(sld); 
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, "EnemyFight");
            ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
        }
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "ChurchBerglar";
		GiveItem2Character(sld, "Chest");
		sld.SaveItemsForDead  = true;
		sld.DontClearDead = true;
        LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	}
	else
	{	//���� ������
        SetLaunchFrameFormParam("������� ����...", "ChurchNightGuard_timerInChurch_2", 0, 3);
        LaunchFrameForm();
        RecalculateJumpTable();
	}
}
// ----------------- ����� �����, ���� ������ ����������� ---------------------
void SCQ_seekCapIsDeath(string qName)
{	
	string sTitle;
	sld = characterFromId(pchar.quest.(qName).CapId); //�������
	rCharacter = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)]; //���������-������������
	//������ ���� ���-�����  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- ������ ���� ���-�����
	if (rCharacter.quest.SeekCap == "manSlave")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
	}
	if (sld.quest.SeekCap == "womanRevengeFight") //�������� ���� ��� �� �����, ��� ����� ������
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //������� �������� ������������� ������
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ������������
	}
	if (sld.quest.SeekCap == "womanHasband" || rCharacter.quest.SeekCap == "manRapeWife" || sld.quest.SeekCap == "manFriend" || sld.quest.SeekCap == "womanRevenge" || rCharacter.quest.SeekCap == "womanPirates")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "4");
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //������� �������� ������������� ������
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ������������
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		CloseQuestHeader(sTitle);
		//������� ���������-��������
		if (sld.quest.SeekCap == "womanRevenge")
		{
			rCharacter.lifeDay = 0;
		}
	}
}
//������ ������������ ��������� � ������ �����
void SCQ_CitizenIsDeath(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId); //�������	
	sld.lifeDay = 0;
	rCharacter = characterFromId(pchar.quest.(qName).CitizenId); //���������-������������
	//������ ���� ���-�����  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- ������ ���� ���-�����
	Map_ReleaseQuestEncounter(sld.id);
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	sTemp = "SecondTimer_" + sld.id;
	pchar.quest.(sTemp).over = "yes"; //������� �������� ������������� ������
	sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����
	string sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
	CloseQuestHeader(sTitle);
}

void CitizCapFromSeaToMap(string qName) //�������� �� ����� ����, �������������� ����������
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.nation = sld.quest.nation;
		//� ������� ������ ����
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//���������� ������ � ��������� ����
		sld.quest = "InMap"; //������ ���� �������� ����
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //��������� �������, ���� ���������� ���
		Log_TestInfo("������� ��� " + sld.id + " ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetCity);
		//�� �����
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//���� ����� ����, ��� ��� ���� � ������ �����
		AddSimpleRumourEx(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �������� ����� " + GetFullName(sld) + ", ����� ���� � ����. �� ������, �� �������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'? ��� ���, �� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			"���� ��� ����� ������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ��� �������� ���������� � " + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + " ���� ������ ����."), 
			sld.city, iTemp, 1, "Citiz_SeekCap_rum", sld.id);
		//--> ������ ���� �� ���� � ���� �������� ��������
		sTemp = sld.id; //Id ����, ������� ������� �������
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //���� ����������
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //������� ����, ����� ����������
		//��������. � �������� ������ ��������� ������� ������ �� �������   PortmansBook_Delivery    #TEXT   5
		//� ������ �������� ������� �����, ��������� � ����� ������ �� quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = sld.quest.cribCity + "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//������ ����� �������� �� Id ���� � ���� ���-�����
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

//����� ������ � �����. ��� ���� ������� �� ������� ����� ����������
void CitizSeekCap_afterCabinFight(string qName)
{	
    //#20191003-01
    LAi_group_SetAlarm(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, 0.0);
	sld = GetCharacter(NPC_GenerateCharacter(pchar.quest.(qName).label + "_" + pchar.quest.(qName).WifeCity, pchar.quest.(qName).model, "woman", "towngirl", 5, pchar.quest.(qName).nation, -1, false));
	sld.name = pchar.quest.(qName).WifeName;
	sld.lastname = pchar.quest.(qName).WifeLastname;
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = pchar.quest.(qName).label + "_Board";
	sld.quest.SeekCap = pchar.quest.(qName).label;
	sld.quest.cribCity = pchar.quest.(qName).WifeCity;
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

//�������� � ���������, ������� ����� ������ ����������� ���������
void SetMushketFromSeaToMap(string qName)
{
	sld = characterFromId("MushketCap");
	//� ������� ������ ����
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("��� � �������� ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "���� '������'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//������ ����� �������� �� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//����� ������ �������
void SetDanielleFromSeaToMap(string qName)
{
	sld = characterFromId("Danielle");
	//� ������� ������ ����
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("��� ������� Queen ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������ '��������'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//������ ����� �������� �� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//׸���� ������
void SetBlackBeardFromSeaToMap(string qName)
{
	sld = characterFromId("BlackBeardNPC");
	//� ������� ������ ����
	string sGroup = "BlackBeardGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = GetRandomPirateCity(); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("��� ������� ����� �������� ���� ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������ '����� �������� ����'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//������ ����� �������� �� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 3;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   ����������        �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������� ���           ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void ISS_MurderSignExecute(string qName)
{
	pchar.questTemp.LSC.killCost = sti(pchar.questTemp.LSC.killCost)-1;
	pchar.questTemp.LSC = "PoorMurderBegin";
	if (sti(pchar.questTemp.LSC.killCost) <= 0)
	{
		pchar.questTemp.LSC = "PoorMurderExecute";
		DeleteAttribute(pchar, "questTemp.LSC.killCost");
		SetQuestHeader("ISS_PoorsMurder");
		AddQuestRecord("ISS_PoorsMurder", "2");
	}
}

void LSC_enterStuvesantBox(string qName)
{
	AddQuestRecord("ISS_PoorsMurder", "5");
	AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("��","��"));
	pchar.questTemp.LSC = "toVillemstadTavern";
	//������� ������� � �������
	FreeSitLocator("Villemstad_tavern", "sit1");
	sld = GetCharacter(NPC_GenerateCharacter("GiveKeyMan", "shipowner_10", "man", "man", 10, HOLLAND, -1, false));
	sld.name = "����";
	sld.lastname = "������";
	sld.city = "Villemstad";
	sld.location	= "Villemstad_tavern";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode   = "GiveKeyMan";
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

void LSC_openMasterHouse(string qName)
{	
	LocatorReloadEnterDisable("Villemstad_town", "houseSp5", false);
	//������ ������� ����
	sld = ItemsFromID("keyQuestLSC");
	sld.shown = true; 
	//Boyer change #20170418-01
	pchar.restoreLSCKeymasterKey = "keyQuestLSC";
	pchar.quest.LSC_enterMasterHouse.win_condition.l1 = "location";
	pchar.quest.LSC_enterMasterHouse.win_condition.l1.location = "Villemstad_houseSp5";
	pchar.quest.LSC_enterMasterHouse.function = "LSC_enterMasterHouse";	
}

void LSC_enterMasterHouse(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], true);
	//������ ������� ������
	sld = characterFromId("GiveKeyMan");
	sld.dialog.currentnode = "GiveKeyManInside";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp5", "barmen", "bar1");
    LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar("GiveKeyMan", "", 0.0, 1.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void LSC_enterSoldiers()
{	
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight"); 
	pchar.questTemp.LSC = "CanFoundStuvesantKey";
	sld = characterFromId("GiveKeyMan"); 
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
	//int iNum = sti((2+MOD_SKILL_ENEMY_RATE)/2);
	//Boyer mod #20170318-33
	int iNum = makeint(MOD_SKILL_ENEMY_RATE/4) + 2;
	for (i=1; i<=iNum; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("MKSold"+i, "sold_hol_"+(rand(7)+1), "man", "man", iTemp, HOLLAND, 0, true));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld); 
		//LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("MKOfficer", "off_hol_2", "man", "man", iTemp, HOLLAND, 0, true));
	SetFantomParamFromRank(sld, iTemp, true);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "MK_HollOfficer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void FirstLoginLostShipsCity(string qName) //�������������� ��������� ��� � ���
{
	//��������� ���������
	pchar.questTemp.LSC = "AdmiralIsWaiting";
	bDisableFastReload = true; //������� �����������
	//�� ������ ������ �������� ������ ���� -->
	TakeItemFromCharacter(pchar, "letter_LSC");
	ChangeItemName("letter_LSC", "itmname_letter_LSC_2");
	ChangeItemDescribe("letter_LSC", "itmdescr_letter_LSC_2");
	i = FindLocation("LostShipsCity_town");
	locations[i].private11.items.letter_LSC = 1;
	//��������������� ����� � ��. � ���� ��� ���
	CloseQuestHeader("ISS_PoorsMurder");
	sld = characterFromId("hol_guber"); //����� ��� ����������
	DeleteAttribute(sld, "notMoveAble");
	DeleteAttribute(&colonies[FindColony("Villemstad")], "notCaptured"); //���������� ����� ����
	LAi_group_Delete("TmpEnemy"); //������ ������� ���
	LAi_group_Delete(LAI_GROUP_TmpEnemy); //������ ������� ������� ����� ������ ������������
	//������ ������ -->
	LAi_group_Delete("PearlGroup_1"); //��� ������ ������� ���� ������ �����������
	LAi_group_Register("PearlGroup_1");
	LAi_group_SetRelation("PearlGroup_1", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius("PearlGroup_1", 50);
	LAi_group_SetHearRadius("PearlGroup_1", 20);
	LAi_group_SetSayRadius("PearlGroup_1", 20);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	LAi_group_Delete("PearlGroup_2");
	LAi_group_Register("PearlGroup_2");
	LAi_group_SetRelation("PearlGroup_2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius("PearlGroup_2", 50);
	LAi_group_SetHearRadius("PearlGroup_2", 20);
	LAi_group_SetSayRadius("PearlGroup_2", 20);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	//<-- ������ ������
	//����� ����� � ������� ���
	reload_cur_island_index = FindIsland("LostShipsCity"); //to_do, � ����� ������
	DeleteAttribute(&Islands[reload_cur_island_index], "alwaysStorm");
	DeleteAttribute(&Islands[reload_cur_island_index], "storm");
	DeleteAttribute(&Islands[reload_cur_island_index], "tornado");
	DeleteAttribute(&Islands[reload_cur_island_index], "QuestlockWeather");
	DeleteAttribute(&Islands[reload_cur_island_index], "MaxSeaHeight");
	//������ ��� ������� � �����������
	int cn;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (i == 0)
			{	//������� ������� ��
				DeleteAttribute(pchar, "ship");
				pchar.ship.name = "";
				pchar.ship.type = SHIP_NOTUSED;
				SetCharacterShipLocation(pchar, "");
			}
			else
			{
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeDay = 0;
				LAi_KillCharacter(sld);
				i--;
			}
		}
	}
	//������ ���� ���������� � ��������
	for (i=0; i<=PASSENGERS_MAX; i++)
	{
		cn = GetPassenger(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			LAi_KillCharacter(sld);
			i--;
		}
	}
	//�������� �� �����, ����� �� ����� �� �����
	//#20170629-01 Dialog/follow bug in Passenger quest
    DeleteAttribute(pchar, "tempDlgInterruptPass"));
	PChar.quest.LSC_stormTimer_1.win_condition.l1            = "Timer";
	PChar.quest.LSC_stormTimer_1.win_condition.l1.date.hour  = 23;
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.function = "LSC_stormTimer_1";
	//��������� �����
	AddSimpleRumourCityTip("����� ����� �������� � ������� �������. ������ ������������...", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("� ��� ���������� ��������� �������� �� ������� ������. ��� - �������� �������...", "LostShipsCity", 10, 1, "LSC", "");

	//���-�������
	sld = GetCharacter(NPC_GenerateCharacter("LSCMayor", "capitan_2", "man", "man", 50, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 50, 90, 90, "blade33", "pistol4", 200);
	sld.name = "���";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location = "SanAugustineResidence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_0";
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mayor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mayor"; //��� ���
	sld.greeting = "Gr_Kapper";
	sld.standUp = true; //�������� � �������� �� ����� 
	sld.watchBoxes = true;
	sld.standUp.exitDisable = true;   //�������� ����� � ������ �����
	sld.watchBoxes.exitDisable = true; //�������� ����� � ������ �����
	sld.HeroModel = "capitan_2,capitan_2_1,capitan_2_2,capitan_2_3,capitan_2_4,capitan_2_5";
	TakeNItems(sld, "key_mechanic", 1);
	//sld.talker = true; //������ ������
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �1
	sld = GetCharacter(NPC_GenerateCharacter("Ment_1", "officer_25", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol4", 100);
	sld.name = "���";
	sld.lastname = "�����";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto9"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_1"; 
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.greeting = "pirat_common";
	sld.talker = true; //������ ������
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �2
	sld = GetCharacter(NPC_GenerateCharacter("Ment_2", "off_fra_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade25", "pistol4", 100);
	sld.name = "�����";
	sld.lastname = "�������";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_2"; 
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������	
	sld.location.hours = 2; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �3
	sld = GetCharacter(NPC_GenerateCharacter("Ment_3", "sold_hol_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade22", "pistol4", 100);
	sld.name = "����";
	sld.lastname = "�������";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto11"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_3"; 
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������
	sld.location.hours = 6; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.greeting = "pirat_common";
	sld.talker = true; //������ ������
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �4
	sld = GetCharacter(NPC_GenerateCharacter("Ment_4", "off_spa_2", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade24", "pistol4", 100);
	sld.name = "�����";
	sld.lastname = "����";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_4";  
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������
	sld.location.hours = 3; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �5
	sld = GetCharacter(NPC_GenerateCharacter("Ment_5", "officer_8", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade33", "pistol4", 100);
	sld.name = "�����";
	sld.lastname = "����";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_5"; 
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ����������� �6
	sld = GetCharacter(NPC_GenerateCharacter("Ment_6", "Dragoon_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "topor2", "pistol4", 100);
	sld.name = "����";
	sld.lastname = "�������";
	sld.rank = 30;
	//Korsar Maxim - �������� ���� ������� ��� �����. (���, �� ������� �� ������ ������� ����� ������ 1.3.2 ������) -->
	sld.HeroModel = "Dragoon_1,Dragoon_2,Dragoon_3,Dragoon_4,Dragoon_5,Dragoon_6,Dragoon_1,Dragoon_1,Dragoon_1";
	//Korsar Maxim - �������� ���� ������� ��� �����. (���, �� ������� �� ������ ������� ����� ������ 1.3.2 ������) <--
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.location.baseShip = "11"; //������� ������� � ���
	sld.location.baseLocator = "goto11_6"; 
	sld.location.baseShip.going = false; //������������ ����� ��������� � ������	
	sld.location.hours = 7; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //��� ���
	sld.talker = true; //������ ������
	sld.watchBoxes = true;
	sld.greeting = "pirat_common";
	SetSPECIAL(sld, 10, 4, 9, 6, 8, 9, 7);
	SetSelfSkill(sld, 100, 100, 100, 30, 90);
	SetShipSkill(sld, 10, 10, 5, 20, 20, 30, 10, 10, 60);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Ciras");
	//SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Rush");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ ������� ------------------------ 
	//���������
	sld = GetCharacter(NPC_GenerateCharacter("LSCBarmen", "barmen_8", "man", "man", 20, PIRATE, -1, false));
	sld.name = "����";
	sld.lastname = "�������";
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Barmen.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //��� ���
	sld.greeting = "Gr_Barmen";
	LAi_SetBarmanType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	//����������
	sld = GetCharacter(NPC_GenerateCharacter("LSCwaitress", "CitizenWom_1", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "����";
	sld.lastname = "�����";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	sld.dialog.filename   = "Quest\LostShipsCity\Waitress.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //��� ���
	sld.greeting = "Armo_Dulin";
	LAi_SetWaitressType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ ������� �������� ------------------------	
	// ������� ��������� ����� �������
	sld = GetCharacter(NPC_GenerateCharacter("PedroHurtado", "usurer_2", "man", "man", 10, PIRATE, -1, true));
	sld.name = "�����";
	sld.lastname = "�������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto06_1"; 
	sld.location.baseShip = "06"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 2; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\PedroHurtado.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ������� ��������� ���� ����
	sld = GetCharacter(NPC_GenerateCharacter("ZhilBaru", "trader_16", "man", "man", 10, PIRATE, -1, true));
	sld.name = "����";
	sld.lastname = "����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto07_1"; 
	sld.location.baseShip = "07"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 1; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\ZhilBaru.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ������� ��������� ������� ������
	sld = GetCharacter(NPC_GenerateCharacter("TristanBorcher", "soldier_free_1", "man", "man", 10, PIRATE, -1, false));
	sld.name = "�������";
	sld.lastname = "������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto09_1"; 
	sld.location.baseShip = "09"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 3; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\TristanBorcher.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ������� ��������� ����� ����
	sld = GetCharacter(NPC_GenerateCharacter("RoyelHaag", "trader_11", "man", "man", 10, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14_1"; 
	sld.location.baseShip = "14"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\RoyelHaag.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ������� ��������� ������� �����
	sld = GetCharacter(NPC_GenerateCharacter("DominicLegro", "trader_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = "�������";
	sld.lastname = "�����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15_1"; 
	sld.location.baseShip = "15"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\DiminicLegro.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ������� ��������� ����� ������
	sld = GetCharacter(NPC_GenerateCharacter("JorgeStouks", "barmen_5", "man", "man", 10, PIRATE, -1, true));
	sld.name = "�����";
	sld.lastname = "������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto08_1"; 
	sld.location.baseShip = "08"; //������� ������� � ���
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\JorgeStouks.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "Gr_JorgeStouks";
	sld.talker = true; //������ ������
	LAi_RemoveLoginTime(sld);	
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");
	ChangeCharacterAddress(sld, "LostShipsCity_town", "goto16_3");

	// ------------------------ ������� �������� � ������� ------------------------
	// � ������� ����� ������
	sld = GetCharacter(NPC_GenerateCharacter("HenryFolder", "barmen_14", "man", "man", 10, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit2"; 
	sld.location.baseShip = "03"; //������� ������� � ���
	sld.location.baseLocator = "goto03_2"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 6; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\HenryFolder.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ������ �������
	sld = GetCharacter(NPC_GenerateCharacter("FelixMendoza", "shipowner_1", "man", "man", 10, PIRATE, -1, true));
	sld.name = "������";
	sld.lastname = "�������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit3"; 
	sld.location.baseShip = "10"; //������� ������� � ���
	sld.location.baseLocator = "goto10_2"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\FelixMendoza.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ������ ������
	sld = GetCharacter(NPC_GenerateCharacter("RodgerWoyler", "usurer_5", "man", "man", 10, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit5"; 
	sld.location.baseShip = "12"; //������� ������� � ���
	sld.location.baseLocator = "goto12_2"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 7; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\RodgerWoyler.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ����� �����
	sld = GetCharacter(NPC_GenerateCharacter("AndreLabor", "shipowner_15", "man", "man", 15, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 15, 60, 60, "blade20", "pistol2", 10);
	sld.name = "�����";
	sld.lastname = "�����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit9"; 
	sld.location.baseShip = "15"; //������� ������� � ���
	sld.location.baseLocator = "goto15_2"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\AndreLabor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ������ �����
	sld = GetCharacter(NPC_GenerateCharacter("StefanKleyn", "shipowner_6", "man", "man", 10, PIRATE, -1, true));
	sld.name = "������";
	sld.lastname = "�����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit8"; 
	sld.location.baseShip = "14"; //������� ������� � ���
	sld.location.baseLocator = "goto14_2";  
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 3; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\StefanKleyn.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ����� �����
	sld = GetCharacter(NPC_GenerateCharacter("ThomasFlann", "citiz_1", "man", "man", 10, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "�����";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit6"; 
	sld.location.baseShip = "02"; //������� ������� � ���
	sld.location.baseLocator = "goto02_2";  
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 3; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\ThomasFlann.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	sld.talker = true; //������ ������
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������� ����� �������
	sld = GetCharacter(NPC_GenerateCharacter("PabloBarades", "officer_20", "man", "man", 10, PIRATE, -1, true));
	sld.name = "�����";
	sld.lastname = "�������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit14"; 
	sld.location.baseShip = "09"; //������� ������� � ���
	sld.location.baseLocator = "goto09_2";  
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\PabloBarades.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ ������� �������� � ������ ------------------------
	// �����
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Priest", "priest_3", "man", "man", 5, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "������";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Priest.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "priest"; //��� ���
	sld.greeting = "Gr_padre";
	LAi_SetPriestType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");		
	
	// � ������ ������ �����
	sld = GetCharacter(NPC_GenerateCharacter("SandraGomes", "girl_4", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "�����";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.location.baseShip = "04"; //������� ������� � ���
	sld.location.baseLocator = "goto04_3"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\SandraGomes.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// � ������ ������ ����
	sld = GetCharacter(NPC_GenerateCharacter("MonikaRight", "girl_5", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "����";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; 
	sld.location.baseShip = "08"; //������� ������� � ���
	sld.location.baseLocator = "goto08_3"; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\MonikaRight.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ ������� ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Trader", "trader_5", "man", "man", 20, PIRATE, -1, true));
	sld.name = "����";
	sld.lastname = "����";
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "EsmeraldaStoreBig";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Trader.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "trader"; //��� ���
	sld.greeting = "tra_common";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	

	// ------------------------ ������ ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_PrisonerHead", "Hobart", "man", "man", 40, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 40, 87, 87, "blade32", "pistol4", 100);
	sld.name = "��������";
	sld.lastname = "�'������";
	sld.rank = 40;
	sld.city = "LostShipsCity";
	sld.location = "TartarusPrison";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "prisonerHead";
	sld.cityTape = "prisonerHead"; //��� ���
	sld.greeting = "pirat_common";
	sld.standUp = true; //�������� � �������� �� ����� 
	sld.watchBoxes = true;
	sld.location.days = 2; //������������ ����� .. ����
	//sld.talker = true; //������ ������
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	SaveCurrentNpcQuestDateParam(sld, "location");

	// �������� �1
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Prisoner1", "SoldierEnglish_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol3", 100);
	sld.name = "�����";
	sld.lastname = "����";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "Prisoner";
	sld.cityTape = "prisoner"; //��� ���
	sld.greeting = "pirat_common";
	sld.standUp = true; //�������� � �������� �� ����� 
	sld.HeroModel = "SoldierEnglish_1,SoldierEnglish_1_1,SoldierEnglish_1_2,SoldierEnglish_1_3,SoldierEnglish_1_4,SoldierEnglish_1_5";
	sld.watchBoxes = true;
	sld.location.hours = 4; //������������ ����� .. �����
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ ������ ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Usurer", "trader_9", "man", "man", 30, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "�����";
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "CarolineBank";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Usurer.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "usurer"; //��� ���
	sld.greeting = "cit_common";
	LAi_SetImmortal(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	

	// ------------------------ ������� ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("Mechanic", "CCS_Mechanic", "man", "man", 5, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "�������";
	sld.rank = 5;
	//Korsar Maxim - �������� ���� ������� ��� �����. -->
	sld.HeroModel = "CCS_Mechanic,CCS_Mechanic_1,CCS_Mechanic_2,CCS_Mechanic_3,CCS_Mechanic_4,CCS_Mechanic_5";
	//Korsar Maxim - �������� ���� ������� ��� �����. <--
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Mechanic.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mechanic"; //��� ���
	sld.greeting = "Gr_Master";
	TakeNItems(sld, "talisman7", 1);
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");

	// ------------------------ ���������� �������� ------------------------
	// ��������� ��������� ���� ������
	sld = GetCharacter(NPC_GenerateCharacter("ElisTaylor", "girl_3", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "����";
	sld.lastname = "������";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "CeresSmithy";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "03"; //������� ������� � ���
	sld.location.baseLocator = "goto03_0"; 
	sld.location.baseLocation = "CeresSmithy"; //������� ��������� �������
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\ElisTaylor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ��������� ��������� ����� ������
	sld = GetCharacter(NPC_GenerateCharacter("OreliBertin", "girl_6", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "������";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FurieShipInside2";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "06"; //������� ������� � ���
	sld.location.baseLocator = "goto06_0"; 
	sld.location.baseLocation = "FurieShipInside2"; //������� ��������� �������
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 6; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\OreliBertin.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ��������� ��������� ��� �����
	sld = GetCharacter(NPC_GenerateCharacter("LeaToors", "girl_7", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "���";
	sld.lastname = "�����";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "PlutoStoreSmall";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "09"; //������� ������� � ���
	sld.location.baseLocator = "goto09_0"; 
	sld.location.baseLocation = "PlutoStoreSmall"; //������� ��������� �������
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\LeaToors.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ��������� ��������� ����� ������
	sld = GetCharacter(NPC_GenerateCharacter("ElizaCalvo", "girl_8", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "�����";
	sld.lastname = "������";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "SantaFlorentinaShipInside4";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "14"; //������� ������� � ���
	sld.location.baseLocator = "goto14_0"; 
	sld.location.baseLocation = "SantaFlorentinaShipInside4"; //������� ��������� �������
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 7; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\ElizaCalvo.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //��� ���
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ��������� ��������� ������ ������
	sld = GetCharacter(NPC_GenerateCharacter("SesilGalard", "BaynesWife", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "������";
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "AvaShipInside3";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "15"; //������� ������� � ���
	sld.location.baseLocator = "goto15_0"; 
	sld.location.baseLocation = "AvaShipInside3"; //������� ��������� �������
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 5; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\SesilGalard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //��� ���
	sld.greeting = "Gr_SesilGalard";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	//------------------- ���� ������ -------------------
	// ������ �������
	sld = GetCharacter(NPC_GenerateCharacter("Narval_head", "capitan_3", "man", "man", 35, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol4", 200);
	sld.name = "�����";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	sld.HeroModel = "capitan_3,capitan_3_1,capitan_3_2,capitan_3_3,capitan_3_4,capitan_3_5";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	SaveCurrentNpcQuestDateParam(sld, "location"); //����� ����� ������� �����������
	// ������ �1
	sld = GetCharacter(NPC_GenerateCharacter("Narval_1", "officer_24", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade21", "pistol6", 10);
	sld.name = "����";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �2
	sld = GetCharacter(NPC_GenerateCharacter("Narval_2", "officer_26", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 26, 80, 80, "blade34", "pistol3", 150);
	sld.name = "������";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �3
	sld = GetCharacter(NPC_GenerateCharacter("Narval_3", "trader_2", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 24, 70, 70, "blade25", "pistol5", 50);
	sld.name = "���";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �4
	sld = GetCharacter(NPC_GenerateCharacter("Narval_4", "pirate_17", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 85, 85, "blade33", "pistol6", 150);
	sld.name = "����";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto5"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �5
	sld = GetCharacter(NPC_GenerateCharacter("Narval_5", "pirate_13", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 100);
	sld.name = "�����";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto6"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �6
	sld = GetCharacter(NPC_GenerateCharacter("Narval_6", "pirate_14", "man", "man", 22, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 22, 65, 65, "blade22", "pistol6", 10);
	sld.name = "�����";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto7"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// ������ �7
	sld = GetCharacter(NPC_GenerateCharacter("Narval_7", "officer_44", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 85, 85, "blade23", "pistol4", 150);
	sld.name = "�����";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");

	//------------------- ���� ������ -------------------
	// ������ �������
	sld = GetCharacter(NPC_GenerateCharacter("Casper_head", "shipowner_24", "man", "man", 35, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol5", 200);
	sld.name = "������";
	sld.lastname = "�������";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//SaveCurrentNpcQuestDateParam(sld, "location"); //����� ����� ������� �����������
	//������ �1
	sld = GetCharacter(NPC_GenerateCharacter("Casper_1", "pirate_19", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "topor2", "pistol3", 100);
	sld.name = "�����";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �2
	sld = GetCharacter(NPC_GenerateCharacter("Casper_2", "pirate_18", "man", "man", 21, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 21, 80, 80, "blade26", "pistol6", 120);
	sld.name = "�����";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto6"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �3
	sld = GetCharacter(NPC_GenerateCharacter("Casper_3", "pirate_20", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade34", "pistol4", 150);
	sld.name = "����";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto5"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �4
	sld = GetCharacter(NPC_GenerateCharacter("Casper_4", "pirate_12", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade23", "pistol3", 100);
	sld.name = "������";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto7"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �5
	sld = GetCharacter(NPC_GenerateCharacter("Casper_5", "officer_20", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 130);
	sld.name = "������";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto13"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �6
	sld = GetCharacter(NPC_GenerateCharacter("Casper_6", "officer_2", "man", "man", 29, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 29, 80, 80, "blade25", "pistol4", 100);
	sld.name = "����";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto1" //; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �7
	sld = GetCharacter(NPC_GenerateCharacter("Casper_7", "officer_4", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade34", "pistol6", 150);
	sld.name = "������";
	sld.lastname = "���";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �8
	sld = GetCharacter(NPC_GenerateCharacter("Casper_8", "officer_34", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade26", "pistol4", 150);
	sld.name = "�����";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; // 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �9
	sld = GetCharacter(NPC_GenerateCharacter("Casper_9", "officer_10", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade28", "pistol6", 150);
	sld.name = "������";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto10"; //
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �10
	sld = GetCharacter(NPC_GenerateCharacter("Casper_10", "officer_6", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade28", "pistol3", 150);
	sld.name = "������";
	sld.lastname = "����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto11"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//������ �11
	sld = GetCharacter(NPC_GenerateCharacter("Casper_11", "officer_20", "man", "man", 27, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade28", "pistol4", 250);
	sld.name = "����";
	sld.lastname = "�����";
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto12"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //��� ���
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	
	// ������

	sld = GetCharacter(NPC_GenerateCharacter("pet_crab", "crabSmall", "crab", "crabSmall", 25, PIRATE, -1, false));
	sld.name = "����";
	sld.lastname = "";
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");;
	sld.location	= "none";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Crab.c";
	sld.dialog.currentnode   = "First time";
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "pet_crab");
    //��������� �������� �� ���
	
	// ������� ��������� ������ ������ - ������������� (����� "����� �����-�����")
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Rishard", "Shambone", "man", "man", 17, PIRATE, -1, false));
	SetFantomParamFromRank(sld, 17, true);
	sld.name = "������";
	sld.lastname = "������";
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto08_1"; 
	sld.location.baseShip = "08"; //������� ������� � ��� - ������
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //������������ ����� ��������� � ������	
	sld.location.hours = 4; //������������ ����� .. �����
	sld.dialog.filename   = "Quest\LostShipsCity\Rishard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //��� ���
	sld.greeting = "pirat_quest";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");
}

//����� �����
void LSC_stormTimer_1(string qName)
{
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			DeleteAttribute(&locations[i], "alwaysStorm");
			DeleteAttribute(&locations[i], "storm");
			DeleteAttribute(&locations[i], "tornado");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");
		}
	}
	//������� ����� ��, ���� ��� ��� �� ������ � ����
	if (pchar.questTemp.LSC == "AdmiralIsWaiting")
	{
		pchar.quest.LSC_admiralOwnFind.win_condition.l1 = "location";
		pchar.quest.LSC_admiralOwnFind.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_admiralOwnFind.function = "LSC_admiralOwnFind";
	}
}

void LSC_admiralOwnFind(string qName)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("LSC_admiralOwnFind_1", 1+rand(2));
}

void LSC_admiralOwnFind_1(string qName)
{
	sld = characterFromId("LSCMayor");
	sld.dialog.currentnode = "FoundHero";
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void LSC_admiralTakeAll()
{
	chrDisableReloadToLocation = false;
	//��������� ������� ����� -->
	sld = ItemsFromID("key1");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key2");
	sld.shown = true;
	sld.startLocation = "VelascoShipInside1";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key3");
	sld.shown = true;
	sld.startLocation = "EsmeraldaStoreBig";
	sld.startLocator = "item1";
	//������� �����
	ref rLoc = &locations[FindLocation("LostShipsCity_town")];
	DeleteAttribute(rLoc, "reload.l61.disable");
	DeleteAttribute(rLoc, "reload.l70.disable");
	DeleteAttribute(rLoc, "reload.l72.disable");
	pchar.questTemp.LSC = "AfterAdmiral";
	StoreEquippedMaps(pchar); // ugeen --> �������� ����� �� ������ ���� ��� �� �������
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
	pchar.MapsAtlasCount = 0; 	
	//������ ��� ��������, ����� ��������� -->
    aref arItems;
	string sName;
    makearef(arItems, pchar.items);
    int	Qty = GetAttributesNum(arItems);
    for (int a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			pchar.questTemp.items.(sName) = pchar.items.(sName);
		}
    }
	DeleteAttribute(pchar, "items");
	pchar.items = "";
	makearef(arItems, pchar.questTemp.items);
    Qty = GetAttributesNum(arItems);
    for (a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(pchar, sName, sti(arItems.(sName)));
    }
	DeleteAttribute(pchar, "questTemp.items");
	if(CheckCharacterItem(pchar, "MapsAtlas")) 
	{
		EquipCharacterByAtlas(pchar);	// ��������� �������, ���� �� ����
		RestoreEquippedMaps(pchar); 	// ������ ����� � ����� � 1 ����������, ��� ��������� ������� ��� � ������ ������
		RefreshEquippedMaps(pchar);
	}	
	//<-- ������ ��� ��������, ����� ���������	
	//��������, �� ������� � �� � �������� ������ -->
	int iLoc = FindLocation("LostShipsCity_town");
	if (CheckAttribute(&locations[iLoc], "private11.equip"))
	{
		DeleteAttribute(&locations[iLoc], "private11.money"); //���� �������, �� ������� �������, ��-��...
	}
	//<-- ��������, �� ������� � �� � �������� ������
	AddQuestRecord("ISS_MainLine", "3");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("� ���, ��� �����","� ���� ������ ���"));
	AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("��","�"));
	//------->>> ��� ������ ������ ��� ������� �� ������		AddSimpleRumourCityTip("", "LostShipsCity", 10, 1, "LSC", "");
	//������������ ���� ���� ������
	LSC_beginElisHusband();	
	AddSimpleRumourCityTip("�� ������, ��� ���� ������ ����� � ������, ������� ������� ��� �� ����� � ���� � ����������. � ������ ������� ���� ������ ������ �� ��������� �������.", "LostShipsCity", 10, 1, "LSC", "LSC_rumourElisHusband");
	//����� �� �������� ������� ��������
	AddSimpleRumourCityTip("��� ����� ������� ���������� ������� ��������. ������ ������� ��������� � ������...", "LostShipsCity", 10, 1, "LSC", "LSC_rumourLostDecster");
	//������� �� �������� ����� � �����
	AddSimpleRumourCityTip("�� ������, ������� ����� ���� ������� ����. � �� �������, ��� ����� ������ � ������ ���-������.", "LostShipsCity", 10, 1, "LSC", "");
}

void LSC_returnBarmen(string qName)
{
	pchar.questTemp.LSC = "toWineCellarLate";
	sld = characterFromId("LSCBarmen");
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");
}

void LSC_returnBarmen_2(string qName)
{
	sld = characterFromId("LSCBarmen");
	LAi_CharacterEnableDialog(sld);
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");
}

void LSC_enterToProtector(string qName)
{
    chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true); 
    DoQuestFunctionDelay("LSC_enterToProtector_1", 7.0);
}

void LSC_enterToProtector_1(string qName)
{
	LAi_group_Delete("EnemyFight"); 
    sld = GetCharacter(NPC_GenerateCharacter("LSCQuestMent", "off_hol_2", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade28", "pistol3", 50);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestMent";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_KillOneNarval(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true); 
    DoQuestFunctionDelay("LSC_KillOneNarval_1", 3.0 + frand(4.0));
}

void LSC_KillOneNarval_1(string qName)
{
	LAi_group_Delete("EnemyFight"); 
    sld = GetCharacter(NPC_GenerateCharacter("LSCQuestNarval", "officer_16", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade28", "pistol4", 150);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestNarval";
	ChangeItemName("DOjeronRing", "itmname_DOjeronRingNarval");
	ChangeItemDescribe("DOjeronRing", "itmdescr_DOjeronRingNarval");
	ref itm;
	itm = ItemsFromID("DOjeronRing");
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_4";
	GiveItem2Character(sld, "DOjeronRing");
	sld.SaveItemsForDead   = true; // ��������� �� ����� ����
	sld.DontClearDead = true;  // �� ������� ���� ����� 200�
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void NavalEnterOfficers(string qName)
{
	int idxMent;
	string sOffName;
	chrDisableReloadToLocation = true;
	for (i=1 ; i<=3; i++)
	{
		idxMent = GetCharacterIndex("Ment_" + i);
		if (idxMent != -1)
		{
			ChangeCharacterAddressGroup(&characters[idxMent], "VelascoShipInside1", "officers", "officer_"+i);
			characters[idxMent].Dialog.CurrentNode = "AffterFightN";
			LAi_SetWarriorType(&characters[idxMent]);
			LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER);
		}
	}
	LAi_group_SetCheck("PearlGroup_1", "NarvalDestroyed");
	//#20181015-01
	idxMent = GetCharacterIndex("Narval_head");
	if (idxMent != -1) {
        sld = &characters[idxMent];
        LAi_SetImmortal(sld, false);
        LAi_group_CheckGroupQuest(sld);
	}
}

void NavalExitVelasco(string qName)
{
	int idxMent;
	string sOffName;
	for (i=1 ; i<=3; i++)
	{
		idxMent = GetCharacterIndex("Ment_" + i);
		if (idxMent != -1)
		{
			sld = &characters[idxMent];
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
			sld.Dialog.CurrentNode = "First time";
			sld.cityTape = "ment"; //��� ���
			LAi_SetLSCoutTypeNoGroup(sld);
		}
	}
	//������������� �����
	AddSimpleRumourCityTip("�������, ��� �� ����� ���� '��������'! ��� ��� ��!..", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("�-��, ��������� ��� ����� '������' ����� �� ����������. �� ��� ��, �������� ���������� ���.", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("��, ��, �������, ����� � ��� �����, ��, ����� ����, �� ������ ��� ���������� � '���������' �����������?..", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("����� ���������� �� ��������, ������� ���� ���� ��� � �������� ������! '�������' ������� ���� �������, ����� � ���.", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("��������� ��� '�������' ������ ��������.", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("������ ������, � ������ ����������, ��� ������ ���� '������' ��� ��������� � �������� ������������ � ������. ����� ����������...", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("����� ����������� '��������' ������ ������������, ��� ������� ���� '�������'...", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("� �� �����, ����� � ���. �� ������ ��������� � ������, � ��� ����� ���� �������. ���������� ����� ���� '��������'!...", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("'�������' ���� �������� � ����� ������. � ��������� ������� ������� �������� ���������� ��. ��� ���, �� �������.", "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip("��� �� ������ ���������� � '���������' - ��� �� �������. ��� ���� ����� ������� �����, �����...", "LostShipsCity", 10, 1, "LSC", "");
}

void LSC_scriptInterception(string qName)
{
	if (pchar.location == "FleuronTavern")
	{
		LAi_SetActorType(pchar);
		sld = characterFromId("LSCMayor");
		sld.Dialog.CurrentNode = "Interception";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
		LAi_ActorGoToLocator(sld, "quest", "stay1", "LSC_EnterComplite_1", -1);
		sld = characterFromId("Casper_head");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_ActorGoToLocator(sld, "quest", "stay2", "LSC_EnterComplite_2", -1);		
	}
	else
	{
		pchar.questTemp.LSC = "InterceptionLate";
		AddQuestRecord("ISS_MainLine", "19");
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","��"));
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
	}
}

void LCS_EndScriptInterception()
{
    //�� ����� ������ � ��.
	SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();
    EndQuestMovie(); 
	//�������� �������� � �������
	sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1.0);
	sld = characterFromId("Casper_head");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1.0);	
	//���������� �� ������� �������� � ������� �� �����
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_EndScriptInterception_2.function = "LCS_EndScriptInterception_2";
	if (pchar.questTemp.LSC == "InterceptionOk")
	{
		AddQuestRecord("ISS_MainLine", "22");
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��� ������ ������","��� ������ ����"));
		AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","�"));
	}
	else
	{
		AddQuestRecord("ISS_MainLine", "20");
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","���"));
		AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","�"));
	}
}

void LCS_EndScriptInterception_2(string qName)
{
	sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	sld.location.going = "toTavern"; //������� � �������, ���� �� ���� �����
	SaveCurrentNpcQuestDateParam(sld, "location");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");

	sld = characterFromId("Casper_head");
	sld.Dialog.CurrentNode = "First time";
	//LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto1");
}

void LSC_changeBarmen(string qName)
{
	if (pchar.location != "FleuronTavern") 
	{
		pchar.questTemp.LSC = "barmenIsDead";
		sld = characterFromId("LSCBarmen");
        sld.name = "�������";
        sld.lastname = "����";
		sld.model = "barmen_2";
        SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
		AddSimpleRumourCityTip("�� �������, ���� ������� ����!!!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("�� ������� ��������� ������� ��������? ���? ���� ������� ����!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("���� �������, ������ ����� �������, ��� ������ � ����� ������� �������. ��� ���!..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("���-�� ���� ������� ������� ����� ��������! ������� ����� �����, ������ ��� ���� �������. �-��, ������� �������!..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("� �� ������, ��� ����� �������� �����? �������� � ��� �� ������ �������!!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("���� ������� �����! ����� � ����� ���� ����� ��������. � ��� ������ � ��� ���� ����� ������ �������, ���� �� ��� ��������� �������!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip("�� ������, ���� ������� �����! ��� ������ ����� � ��������?..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	}
	else
	{
		pchar.quest.LSC_changeBarmen_2.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_changeBarmen_2.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_changeBarmen_2.function = "LSC_changeBarmen_2";
	}
}

void LSC_changeBarmen_2(string qName)
{
	pchar.questTemp.LSC = "barmenIsDead";
	sld = characterFromId("LSCBarmen");
    sld.name = "�������";
    sld.lastname = "����";
	sld.model = "barmen_2";
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
	AddSimpleRumourCityTip("�� �������, ���� ������� ����!!!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("�� ������� ��������� ������� ��������? ���? ���� ������� ����!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("���� �������, ������ ����� �������, ��� ������ � ����� ������� �������. ��� ���!..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("���-�� ���� ������� ������� ����� ��������! ������� ����� �����, ������ ��� ���� �������. �-��, ������� �������!..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("� �� ������, ��� ����� �������� �����? �������� � ��� �� ������ �������!!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("���� ������� �����! ����� � ����� ���� ����� ��������. � ��� ������ � ��� ���� ����� ������ �������, ���� �� ��� ��������� �������!", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip("�� ������, ���� ������� �����! ��� ������ ����� � ��������?..", "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
}

void LSC_SaveSesilGalard(string qName)
{
	if (pchar.location.locator == "reload1") sTemp = "goto5";
	else sTemp = "goto4";
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = characterFromId("SesilGalard");
	sld.dialog.currentnode = "HelpMe";
	sld.greeting = "Enc_RapersGirl_1";
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  sTemp);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_SaveSesilGalard_2()
{	
	LAi_SetFightMode(pchar, true);
	LAi_LocationFightDisable(loadedLocation, false);
	//�������
	sld = characterFromID("SesilGalard");
	LAi_SetActorTypeNoGroup(sld);
	if (pchar.location.locator == "reload1") 
	{		
		LAi_ActorRunToLocator(sld, "barmen", "bar2", "LSC_SesilAfraid", -1);	
	}
	else 
	{
		LAi_ActorRunToLocator(sld, "barmen", "stay", "LSC_SesilAfraid", -1);	
	}
	//��������
	LAi_group_Delete("EnemyFight");
	if (sti(pchar.rank)<12) iTemp = sti(pchar.rank);
	else iTemp = 10+MOD_SKILL_ENEMY_RATE*2;
    for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("LSCBandit"+i, "officer_"+(i+3), "man", "man", iTemp, PIRATE, 0, true));
        if (sti(pchar.rank)<12) FantomMakeCoolFighter(sld, iTemp, 50, 50, "topor3", "pistol2", 50);
		else FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        LAi_SetWarriorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
        if (i == 2)
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
		else
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "start"+i);
    }
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetCheck("EnemyFight", "LSC_SesilAfterFight");
}
//���� � �������� �� ��� ��������
void LSC_enterCasper(string qName)
{	
	//���� �������� ����� ���� � ����
	iTemp = GetCharacterIndex("LSC_Prisoner1");
	if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic") 
	{
		characters[iTemp].reactionOnFightModeOn = true; //������������ �� ��������� ������
		characters[iTemp].lifeDay = 0;
		LAi_warrior_DialogEnable(&characters[iTemp], true);
		LAi_group_SetCheck("PearlGroup_2", "LSC_PrisonerAfterFight");
	}
	//�������
	iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic") 
	{
		chrDisableReloadToLocation = true;
		LAi_group_SetCheck("PearlGroup_2", "OpenTheDoors");
		AddSimpleRumourCityTip("�������, ��� �� ����� ���� '��������'! ������...", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("�� �����, ��� ��� ���� ���� ���������� '��������'. ���� �� � ������...", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("������, �� ����� �����! ������� '�������', ����� '�������'! ����...", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("��, ������� �� ���������� ������. ���� '������' ����� � ����... ��� ��, �������!", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("������, '�������' ����� ��� �� ���������. ������� �� �������� ������ ��� �� ��� �� � �������....", "LostShipsCity", 10, 1, "LSC", "");
	}
	//������� ����������� ������� � ��������.
	LocatorReloadEnterDisable("SanGabrielMechanic", "reload2", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload55", false);
	pchar.questTemp.LSC = "toSeekMechanikCanMove";
	DeleteAttribute(pchar, "questTemp.LSC.Armo");
}
//���������� �� ����� ������� �� ����
void LSC_KillOneCasper(string qName)
{
	pchar.quest.LSC_checkCasperDead.over = "yes"; 
	if (sti(pchar.questTemp.LSC.Armo) < 5)
	{		
		iTemp = sti(pchar.quest.(qName).casperIdx);
		pchar.questTemp.LSC.Armo = sti(pchar.questTemp.LSC.Armo) + 1; //�� ����������...
		pchar.questTemp.LSC.Armo.waiting = true;
		AddQuestRecord("ISS_MainLine", "36");
		AddQuestUserData("ISS_MainLine", "sName", GetFullName(&characters[iTemp]));
		AddSimpleRumourCityTip("�������, ��� ����� ����� ���-�� ������ �� ������ '����� �����'.", "LostShipsCity", 2, 1, "LSC", "");
		AddSimpleRumourCityTip("���� ������, ������� ������ '����� �����', ������� ����� ����� ����� �� ������. ��� ��� ����� ���������� ��������� �����...", "LostShipsCity", 2, 1, "LSC", "");
	}
	else
	{	//������ ����� �������� �������
		DoQuestFunctionDelay("LSC_KillOneCasper_3", 4.0);
		chrDisableReloadToLocation = true;
	}
}

void LSC_KillOneCasper_3(string qName)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Casper_6");
	sld.dialog.currentnode = "FackYou";
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator("reload", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}
//������ ������� �� ������ �� ����
void LSC_checkCasperDead(string qName)
{
	pchar.quest.LSC_KillOneCasper.over = "yes"; 
	iTemp = sti(pchar.quest.(qName).casperIdx);
	if (!LAi_IsDead(&characters[iTemp]))
	{
		pchar.questTemp.LSC.Armo = 11; //�������� �������
		sld = &characters[iTemp];
		sld.dialog.currentnode   = "First time";
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PearlGroup_2");
		ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto9");
	}
}

void LSC_3CarperAttackArmo()
{
	LAi_SetFightMode(pchar, true);
	chrDisableReloadToLocation = false;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//������ ������ ����
	sld = characterFromId("LSCwaitress");
    sld.dialog.currentnode = "ArmoIsDead";
	sld.name = "�����";
    sld.lastname = "��������";
	sld.model = "Girl_2";
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
    AddSimpleRumourCityTip("�� �������, ����� ������ ���� �����! ��, ����� ������� ������� ����...", "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip("���� ���, ������, ���, � ���� ������. �������, ���� ������ �������� �������...", "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip("���� ������� �������?! ����� ��� ��������� �������, � ������ ��� � �������� ����...", "LostShipsCity", 10, 1, "LSC", "");
	//������ ������
	sld = characterFromId("Casper_6");
	sld.quest.checkCasper = true; //��� ��������� � �� warrior
	LAi_SetWarriorTypeNoGroup(sld);
	//������
	sld = characterFromId("Casper_7");
	sld.quest.checkCasper = true; //��� ��������� � �� warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	//������
	sld = characterFromId("Casper_8");
	sld.quest.checkCasper = true; //��� ��������� � �� warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	AddQuestRecord("ISS_MainLine", "39");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","���"));
}

void LSC_underwaterDeathTimer(string qName)
{
	GameOver("sea");
}

//������ ����� �����
void LSC_SmallStormIsBegin()
{
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			locations[i].alwaysStorm = true; //����� � �������
			if (locations[i].id == "LostShipsCity_town")
			{
				locations[i].alwaysStorm.WaveHeigh = true; //������� ������� ���� �� 2.5 ��� ������� ��������
			}
			locations[i].storm = true;
			locations[i].tornado = true;			
		}
	}
	//������ ���� � ������
	AddSimpleRumourCityTip("������ ���������. ������ ����� ����� �����.", "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip("�-��, ������� ����� ����� �����������.", "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip("��, ��� �� ������� ��� ������! ���, ������� ����� ����������...", "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip("������ �����������. ������, ����� �����.", "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip("���������� �����. ����� ��������� ���� ����� ������ �� �����.", "LostShipsCity", 5, 1, "LSC", "");
	//��������� ��� �� ���� �����, ���������. ������������ �������� �� ������
	LAi_group_Delete("EnemyFight");
	for(i=0; i<MAX_CHARACTERS; i++)
	{	
		makeref(sld, characters[i]);
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
		{	
			if (sld.cityTape == "mayor")
			{
				//LAi_SetImmortal(sld, false);
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMove";  //�� ������������ �����
				LAi_SetHuberType(sld); //����� �� ����
				LAi_group_MoveCharacter(sld, "EnemyFight");	
				ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
			}
			if (sld.cityTape == "ment")
			{
				if (sld.id == "Ment_6")
				{
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //�� ������������ �����
					LAi_SetLSCoutTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
				}
				else
				{
					sTemp = sld.id;
					sTemp = "goto" + strcut(sTemp, 5, 5);
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //�� ������������ �����
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", sTemp);
				}				
			}
			if (sld.cityTape == "citizenHome")
			{
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMove";  //�� ������������ �����
				LAi_SetOwnerTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
			}
			if (sld.cityTape == "prisonerHead" || sld.cityTape == "prisoner")
			{
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
		}
	}
}

void LSC_afterArestMachanic(string qName)
{
	sld = &characters[sti(pchar.questTemp.LSC.lastManId)];
	LAi_SetStayTypeNoGroup(sld);			
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "barmen",  "stay");
	sld = characterFromId("Mechanic");
	ChangeCharacterAddress(sld, "none", "");
	DeleteAttribute(pchar, "questTemp.LSC.lastManId");
}

void LSC_fightEnterResidence(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	//��������� ������
	string sLocator;
	iTemp = GetCharacterIndex("Ment_1")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//------------------------
	iTemp = GetCharacterIndex("Ment_2")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//------------------------
	iTemp = GetCharacterIndex("Ment_3")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//� ����������
	iTemp = GetCharacterIndex("Ment_4")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_SetWarriorTypeNoGroup(sld); 
		LAi_warrior_DialogEnable(sld, false);
		LAi_warrior_SetStay(sld, true);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto2");
	}
	iTemp = GetCharacterIndex("Ment_5")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_SetWarriorTypeNoGroup(sld); 
		LAi_warrior_DialogEnable(sld, false);
		LAi_warrior_SetStay(sld, true);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto3");
	}	
	sld = characterFromId("LSCMayor");
	sld.dialog.currentnode = "fightTalking";
	LAi_SetImmortal(sld, false);
	LAi_SetActorTypeNoGroup(sld); 
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void LSC_figtInResidence()
{
	sld = characterFromId("pet_crab");
	if (!CharacterIsDead(sld) && CheckAttribute(sld, "quest.answer_1"))
	{
		sld.dialog.currentnode = "crab_hire";
		sld.model	= "pet_crab";
		sld.animation = "crabBig";
		LAi_SetHP(sld, 1000, 1000);
		SetSPECIAL(sld, 7,7,7,7,7,7,7)
		sld.rank = 25;
		LAi_SetActorTypeNoGroup(sld); 
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto11_1");
	}
	
	sld = characterFromId("Ment_6");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetWarriorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
    pchar.quest.LSC_figtInResidence_1.win_condition.l1 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l1.character = "LSCMayor";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2.character = "Ment_4";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3.character = "Ment_5";
    pchar.quest.LSC_figtInResidence_1.function= "LSC_figtInResidence_1";
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void LSC_figtInResidence_1(string qName)
{
	sld = characterFromId("Ment_6");
	if (!CharacterIsDead(sld))
	{
		sld.dialog.currentnode = "MentOffIsLife";
		LAi_SetActorTypeNoGroup(sld); 
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	}
	else
	{
		AddQuestRecord("ISS_MainLine", "65");
		chrDisableReloadToLocation = false;
	}
	pchar.quest.LSC_enterToPrison.win_condition.l1 = "location";
	pchar.quest.LSC_enterToPrison.win_condition.l1.location = "TartarusPrison";
	pchar.quest.LSC_enterToPrison.function = "LSC_enterToPrison";

}

void LSC_enterToPrison(string qName)
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mechanic");
	sld.dialog.currentnode = "inPrison";
	LAi_SetImmortal(sld, true);
	LAi_SetGroundSitType(sld);
	ChangeCharacterAddressGroup(sld, "TartarusPrison", "quest", "prison3");
}

//������ ������� �����
void LSC_BigStormIsBegin()
{
	bDisableFastReload = true; 
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (locations[i].id == "LostShipsCity_town")
		{	//��������� �������
			locations[i].notCrateFoam = true; //�� �������� ����
			DeleteAttribute(&locations[i], "reload.l2.disable"); //��������� ����� � ���
			locations[i].reload.l231.disable = true;
			for(int n=3; n<=73; n++)
			{	
				sTemp = "l" + n;
				locations[i].reload.(sTemp).disable = true; 
			}
			DeleteAttribute(&locations[i], "reload.l2.disable"); //������� ����� �� ���
			locations[i].locators_radius.reload.reload2_back = 20.0;
			pchar.location.from_sea = "LostShipsCity_town";
			//������ ���� ���
			locations[i].models.day.charactersPatch = "LostShipsCity_patch_end";
			locations[i].models.night.charactersPatch = "LostShipsCity_patch_end";	
			//������
			DeleteAttribute(&locations[i], "alwaysStorm");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");		
			locations[i].alwaysStorm_2 = true; //����� � �������
			locations[i].alwaysStorm_2.WaveHeigh = true; //������� ������� ���� �� 2.5 ��� ������� ��������
			locations[i].storm = true;
			locations[i].tornado = true;
			//#20181023-02
			if(MOD_SKILL_ENEMY_RATE==1)
                //locations[i].showLocatorGrp = "reload";
			break;
		}
	}
	//����� ����� � ������� ���
	i = FindIsland("LostShipsCity");
	Islands[i].reload.l2.emerge = "reload2_back";
	Islands[i].reload_enable = false;
	Islands[i].visible = true;
	Islands[i].reload_enable = false;
	Islands[i].alwaysStorm = true; //����� � �������
	Islands[i].storm = true;
	Islands[i].tornado = true;
	//���������� �� �������� ������� ��� � ������ ������ � ������
	pchar.quest.LSC_closeLine.win_condition.l1 = "location";
	pchar.quest.LSC_closeLine.win_condition.l1.location = "LostShipsCity";
	pchar.quest.LSC_closeLine.function = "LSC_closeLine";
	SetTimerFunction("LSC_takeStormIsland", 0, 0, 10);
}

void LSC_closeLine(string qName)
{
	AddQuestRecord("ISS_MainLine", "69");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("ISS_MainLine");
	CloseQuestHeader("TakeVineToPrisoner");
	CloseQuestHeader("LSC_findDekster");
	CloseQuestHeader("ISS_ElisHusband");
	CloseQuestHeader("ISS_takeStoreMoney");
	CloseQuestHeader("ISS_takeCandles");
	bQuestDisableMapEnter = false;
	bDisableFastReload = false; 
	TakeItemFromCharacter(pchar, "keyPanama");
	//�������� ������� ����� � ������� ���
	sld = characterFromId("LSC_Usurer");
	if (CheckAttribute(sld, "quest.loan.qtyMoney") && sti(sld.quest.loan.qtyMoney) > 0)
	{	
		SetTimerFunction("LSC_climeUsurer", 0, 3 + rand(3), 0);
		pchar.questTemp.LSC_climeUsurer.qtyMoney = sti(sld.quest.loan.qtyMoney) * 5; //������� ����� � ��������
	}
	sld = ItemsFromID("key1");
	sld.price = 10;
	sld = ItemsFromID("key2");
	sld.price = 10;
	sld = ItemsFromID("key3");
	sld.price = 10;
	// Return to LSC - Gregg
	//������� ������� ��� �� ���� 
	/*for(i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			sld.lifeDay = 0;	
	}*/
}

void LSC_takeStormIsland(string qName)
{	
	i = FindIsland("LostShipsCity");
	//Islands[i].reload_enable = false;
	//Islands[i].visible = false;
	DeleteAttribute(&Islands[i], "alwaysStorm");
	DeleteAttribute(&Islands[i], "storm");
	DeleteAttribute(&Islands[i], "tornado");
	DeleteAttribute(&Islands[i], "QuestlockWeather");
	DeleteAttribute(&Islands[i], "MaxSeaHeight");
	
	// Return to LSC - Gregg
	Islands[i].reload.l2.emerge = "reload1_back";
	Islands[i].reload_enable = true;
	Islands[i].visible = true;
	sld = characterFromId("LSC_Usurer");
	sld.lifeDay = 0;
	for(i=0; i<MAX_LOCATIONS; i++)
	{		
		if (locations[i].id == "LostShipsCity_town")
		{
			locations[i].reload.l1.disable = false;
			locations[i].reload.l231.disable = false;
			for(int n=3; n<=73; n++)
			{	
				sTemp = "l" + n;
				locations[i].reload.(sTemp).disable = false; 
			}
			DeleteAttribute(&locations[i], "reload.l2.disable"); //������� ����� �� ���
			locations[i].locators_radius.reload.reload2_back = 10.0;
			//������ ���� ���
			locations[i].models.day.charactersPatch = "LostShipsCity_patch_day";
			locations[i].models.night.charactersPatch = "LostShipsCity_patch_day";	
			//������
			DeleteAttribute(&locations[i], "alwaysStorm");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");
			DeleteAttribute(&locations[i], "alwaysStorm_2");	
			DeleteAttribute(&locations[i], "alwaysStorm_2.WaveHeigh");	
			DeleteAttribute(&locations[i], "storm");	
			DeleteAttribute(&locations[i], "tornado");	
			break;
		}
	}
	for(i=0; i<MAX_LOCATIONS; i++)
	{
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			DeleteAttribute(&locations[i], "alwaysStorm");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");
			DeleteAttribute(&locations[i], "alwaysStorm_2");	
			DeleteAttribute(&locations[i], "alwaysStorm_2.WaveHeigh");	
			DeleteAttribute(&locations[i], "storm");	
			DeleteAttribute(&locations[i], "tornado");			
		}
	}
}

//------------ �������� ����� ��������� �������� ----------->>>>>>
void LCS_SetPedroHurtado(string qName)
{
	sld = characterFromId("PedroHurtado");
	sld.cityTape = "quest"; //��� ���
	DeleteAttribute(sld, "location.going");
	LAi_SetLoginTime(sld, 10.0, 19.00);
	LAi_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto04_6");
}

void LSC_PedroRunOpenDoor()
{
	sld = characterFromId("PedroHurtado");
	sld.BreakTmplAndFight = true;
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "reload", "reload48", "LSC_PedroOpenedDoor", -1.0);
}

void LSC_Click(string qName)
{	
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);
	chrDisableReloadToLocation = true;
}

void LSC_PedroGoWaiting()
{
	sld = characterFromId("PedroHurtado");
	LAi_RemoveLoginTime(sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto04_6");
	chrDisableReloadToLocation = false;
	pchar.quest.LSC_EnterStoreBig.win_condition.l1 = "locator";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.location = "EsmeraldaStoreBig";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator = "reload2";
	pchar.quest.LSC_EnterStoreBig.function = "LSC_EnterStoreBig";
}

void LSC_EnterStoreBig(string qName)
{	
	//������
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	iTemp = 8+MOD_SKILL_ENEMY_RATE*2;
    for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("LSCStBandit"+i, "officer_"+(i+10), "man", "man", iTemp, PIRATE, 0, true));
        FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        LAi_SetWarriorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
		ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest"+i);
    }
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_HeroOutFromStory.function = "LCS_HeroOutFromStory";
}

void LCS_HeroOutFromStory(string qName)
{
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true);
	sld = characterFromId("PedroHurtado");	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	AddSimpleRumourCityTip("�������, ��� ���-�� ������� ������� �������� ����� �����...", "LostShipsCity", 10, 1, "LSC", "");
}
//<<<<<<-------- �������� ����� ��������� �������� ----------------

//------------ ������ ���������� ��� ----------->>>>>>
void LSC_climeUsurer(string qName)
{
	pchar.quest.LSC_climeUsurer_2.win_condition.l1 = "Location_Type";
	pchar.quest.LSC_climeUsurer_2.win_condition.l1.location_type = "shop";
	pchar.quest.LSC_climeUsurer_2.function = "LSC_climeUsurer_2";	
}

void LSC_climeUsurer_2(string qName)
{
	chrDisableReloadToLocation = true;
	sld = characterFromId(loadedLocation.fastreload + "_trader");
	LAi_CharacterDisableDialog(sld);
	//������� ������ ��� �������� � �������
	pchar.questTemp.LSC_climeUsurer.idx = sld.id;
	pchar.questTemp.LSC_climeUsurer.location = pchar.location;
	pchar.questTemp.LSC_climeUsurer.group = pchar.location.group;
	pchar.questTemp.LSC_climeUsurer.locator = pchar.location.locator;
	DoQuestFunctionDelay("LSC_climeUsurer_3", 3.5);
}

void LSC_climeUsurer_3(string qName)
{
 	//���������� ��
	DoQuestReloadToLocation("Temple_Skulls", "goto", "goto1", "");	
	DoQuestFunctionDelay("LSC_climeUsurer_4", 10.0);
	//������ ������� �������� ����������� �������
	sld = characterFromId(pchar.questTemp.LSC_climeUsurer.idx);
	LAi_CharacterEnableDialog(sld);
}

void LSC_climeUsurer_4(string qName)
{
	//������ ���� �������	
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 50, 100, 100, "toporAZ", "pistol4", 3000); //����� ����������������
	sld.name = "��������������";
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "ClimeUsurer";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Temple_Skulls", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);	
}

void ClimeUsurer_haveMoney()
{
	DoQuestFunctionDelay("ClimeUsurer_haveMoney_1", 1.0);	
}

void ClimeUsurer_haveMoney_1(string qName)
{
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&locations[FindLocation("Temple_Skulls")], false);
	DoQuestReloadToLocation(pchar.questTemp.LSC_climeUsurer.location, pchar.questTemp.LSC_climeUsurer.group, pchar.questTemp.LSC_climeUsurer.locator, "");	
	DeleteAttribute(pchar, "questTemp.LSC_climeUsurer");
}

void ClimeUsurer_noMoney()
{
	LAi_LocationFightDisable(loadedLocation, false);
	sld = characterFromId("DeadmansGod");
	ChangeCharacterAddress(sld, "none", "");
	//���� ���� � ���������, �� �������� ��
	if (pchar.questTemp.Azzy == "over")
	{
		DoQuestFunctionDelay("LSC_climeUsurer_Azzy", 30.0);
	}
}

void LSC_climeUsurer_Azzy(string qName)
{
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, 0, false));
	sld.name = "�����";
	sld.lastname = "����";
	sld.Dialog.Filename = "Quest\Azzy_dialog.c";
	sld.dialog.currentnode = "ClimeUsurer";
	GiveItem2Character(sld, "blade28");// ����� �������
	sld.equip.blade = "blade28";
	sld.rank 	= 100;
	sld.reputation = "0";
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetHP(sld, 10000.0, 10000.0);
	sld.greeting = "Gr_Azzy";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}
//<<<<<<-------- ������ ���������� ��� ----------------

//------------ ���������� ���� ���� ������ ----------->>>>>>
void LSC_ElisHusbandSet(string qName)
{
	sld = characterFromId("MaximTailor");
	sld.dialog.currentnode = "First time";
	sld.watchBoxes = true;
	GiveItem2Character(sld, "blade15");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "blade15");
 	EquipCharacterbyItem(sld, "pistol2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto1");
}
//<<<<<<-------- ���������� ���� ���� ������ ----------------

//------------ ����� ������� ������� �������� ----------->>>>>>
void LSC_admiralFoundOwnKey(string qName)
{
	sld = ItemsFromID("keyPanama");
	sld.shown = false;
	AddQuestRecord("LSC_findDekster", "11");
	AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("LSC_findDekster");
	pchar.questTemp.LSC.lostDecster = "over";
}
//<<<<<<-------- ����� ������� ������� �������� ----------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������� ���           �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������� ������������          ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����, ��� ��������� �� ����
void Teno_startInShore(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("QuestMan_Shore", "shipowner_1", "man", "man", 100, PIRATE, 0, false));
	sld.name = "�������";
	sld.lastname = "�����";
	sld.dialog.filename   = "Quest\Tenochtitlan\ForAll_Teno.c";
	sld.dialog.currentnode   = "Shore53";
	ChangeCharacterAddressGroup(sld, "Shore53", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

void Teno_startInShore_2()
{
	pchar.questTemp.Teno = "toMontesuma"; //���� ������
	sld = characterFromId("QuestMan_Shore");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "CanFightCurLocation", 10.0);
	//������ �����
	sld = GetCharacter(NPC_GenerateCharacter("Montesuma", "Aztec", "man", "man", 50, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 50, 100, 100, "toporAZ", "", 500);
	sld.name = "���������";
	sld.lastname = "";
	sld.location = "Tenochtitlan";
	sld.location.group = "quest";
	sld.location.locator = "quest2";
	sld.dialog.filename   = "Quest\Tenochtitlan\Montesuma.c";
	sld.dialog.currentnode   = "First time";
	sld.greeting = "Gr_Montesuma";
	sld.reactionOnFightModeOn = true; 
	sld.BreakTmplAndFight = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	//GiveItem2Character(sld, "Totem_15");
	LAi_group_MoveCharacter(sld, "MontesumaGroup");
	//������ ���������� �� ���� � �����������
	pchar.quest.Teno_createAztecTwin.win_condition.l1 = "location";
	pchar.quest.Teno_createAztecTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_createAztecTwin.function = "Teno_createAztecTwin";

	pchar.quest.Teno_talkWithTwin.win_condition.l1 = "locator";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator_group = "teleport";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator = "fire20";
	pchar.quest.Teno_talkWithTwin.function = "Teno_talkWithTwin";
	//��������� ����� � ��
	SetQuestHeader("Tenochtitlan");
	AddQuestRecord("Tenochtitlan", "1");
	AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("","�"));
}

//������ ������� �������
void Teno_createAztecTwin(string qName)
{
	//������� ���������
	sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_1", "AztecCitizen1", "man", "man", 15, PIRATE, -1, false));
	sld.name = "�������";
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT";
	sld.greeting = "cit_common";
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");  
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto23");
	
	sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_2", "AztecCitizen2", "man", "man", 15, PIRATE, -1, false));
	sld.name = "��������";
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT2";
	sld.greeting = "cit_common";
	LAi_SetLoginTime(sld, 7.0, 20.0);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto14");
	//��������� �� ��
	sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

void Teno_talkWithTwin(string qName)
{
	sld = characterFromId("AztecCitizen_1");
	LAi_ActorDialog(sld, pchar, "", 2.5, 0);
}

void Teno_MontesumaGoQuest1()
{
	AddQuestRecord("Tenochtitlan", "2");
	AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("","�"));
	sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest1", "Teno_MontesumaArrived", -1);
}

void Teno_fightInTemple()
{
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	sld = characterFromId("DeadmansGod");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "teno_monsters_group");
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("teno_monsters_group", LAI_GROUP_PLAYER, true);
	LAi_SetCheckMinHP(sld, 5.0, true, "Teno_youWinFight");
}

void Teno_exitFromTeno(string qName)
{
	sld = characterFromId("Montesuma");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
}

void Teno_clearGroups(string qName)
{
	LAi_group_Delete("AztecCitizenGroup");
	LAi_group_Delete("MontesumaGroup");
	LAi_group_Delete("teno_monsters_group");
	//ChangeItemDescribe("SkullAztec", "itmdescr_SkullAztecAdd");
	AddQuestRecord("Tenochtitlan", "6");
	CloseQuestHeader("Tenochtitlan");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������� ������������         �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������������ �����        ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void MC_startInCaracas(string qName)
{
	if (GetHour() > 9.0 && GetHour() < 20.0 && !LAi_IsCapturedLocation)
	{
		pchar.questTemp.MC = "toCaracas"; //���� ������	
		bDisableFastReload = true;
		iTemp = FindLocation("Caracas_town");
		DeleteAttribute(&locations[iTemp], "citizens"); //������ �������
		DeleteAttribute(&locations[iTemp], "carrier");	//������ ��������� 
		DeleteAttribute(&locations[iTemp], "questSeekCap");	//������ ������������
		//������� ������ �� ������
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l2.disable = true;
		locations[iTemp].reload.l3.disable = true;
		locations[iTemp].reload.l4.disable = true;
		locations[iTemp].reload.l41.disable = true;
		locations[iTemp].reload.l5.disable = true;
		locations[iTemp].reload.l6.disable = true;
		locations[iTemp].reload.l7.disable = true;
		locations[iTemp].reload.l8.disable = true;
		locations[iTemp].reload.l10.disable = true;
		locations[iTemp].reload.gate.disable = true;
		//������� �������
		iTemp = FindLocation("Caracas_tavern");
		DeleteAttribute(&locations[iTemp], "habitues"); //������ � ������� ���������� ���
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l4.disable = true;
		sld = characterFromId("Caracas_waitress"); //���������� ����
		ChangeCharacterAddress(sld, "none", "");	
		//������ �������
		for (i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CaracasCit_"+i, "citiz_"+i, "man", "man", 10, SPAIN, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasMan"; 
			sld.greeting = "cit_common";
			sld.BreakTmplAndFightGroup = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Caracas_town", "quest", "MCquest"+i);
		}
	}
	else
	{
		pchar.quest.MC_startAgain.win_condition.l1 = "MapEnter";
		pchar.quest.MC_startAgain.function = "MC_startAgain";
	}
}

void MC_startAgain(string qName)
{
	pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
	pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
	pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
}

void MC_endCaracas()
{
	bDisableFastReload = false;
	pchar.questTemp.MC = "toMaracaibo"; //���� ������	
	//������ �����
	iTemp = FindLocation("Caracas_town");
	locations[iTemp].citizens = true; 
	locations[iTemp].carrier = true; 
	locations[iTemp].questSeekCap = 8; 
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");	
	DeleteAttribute(&locations[iTemp], "reload.l2.disable");
	DeleteAttribute(&locations[iTemp], "reload.l3.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	DeleteAttribute(&locations[iTemp], "reload.l41.disable");
	DeleteAttribute(&locations[iTemp], "reload.l5.disable");
	DeleteAttribute(&locations[iTemp], "reload.l6.disable");
	DeleteAttribute(&locations[iTemp], "reload.l7.disable");
	DeleteAttribute(&locations[iTemp], "reload.l8.disable");
	DeleteAttribute(&locations[iTemp], "reload.l10.disable");
	DeleteAttribute(&locations[iTemp], "reload.gate.disable");
	DeleteAttribute(&locations[iTemp], "hidden_effects");
	//������ �������
	iTemp = FindLocation("Caracas_tavern");
	locations[iTemp].habitues = true;
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	sld = characterFromId("Caracas_waitress"); //���������� ����
	sld.location = "Caracas_tavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	SetQuestHeader("MagicCity");
	AddQuestRecord("MagicCity", "1");
	pchar.quest.MC_DesMoinesInShore.win_condition.l1 = "location";
	pchar.quest.MC_DesMoinesInShore.win_condition.l1.location = "Shore_ship3";
	pchar.quest.MC_DesMoinesInShore.function = "MC_DesMoinesInShore";
}

void MC_DesMoinesInShore(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_group_Delete("EnemyFight");
    //Boyer mod...halve number of enemies.  Their rank/skills will already outrank Hero and fight is VERY difficult...you will likely die.
    //#20181002-02
    int nNumE = round((MOD_SKILL_ENEMY_RATE + 0.2) / 2);
    int nNumF = GetOfficersQuantity(pchar);
    if(nNumF > nNumE)
        nNumE = nNumF + rand(2);
    for (i=1; i<=nNumE; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("ShoreGuard"+i, "officer_"+(i+10), "man", "man", 20, PIRATE, 0, true));
        FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);
		sld.dialog.filename = "Quest\MagicCity.c";
		sld.dialog.currentnode = "ShoreGuard";
		sld.BreakTmplAndFightGroup = true; 
		sld.reactionOnFightModeOn = true; 
        LAi_SetActorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
		PlaceCharacter(sld, "goto", "random_free");
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ������������ �����     eddy     �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- ������� �������� ����� --     ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Blood_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.CapBloodLine.stat = "Begining";
    Pchar.BaseNation = ENGLAND;
    //fix ������ ������
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
    SetCharacterPerk(Pchar, "FlagEng");
    Flag_ENGLAND();
    //���������� ���������
    int n = FindLocation("Bridgetown_town");
    DeleteAttribute(&locations[n], "questSeekCap");
    DeleteAttribute(&locations[n], "houseEnc");
    locations[n].notCloseCommonHouse = true;
    n = FindLocation("Bridgetown_tavern"); //homo fix
    DeleteAttribute(&locations[n], "habitues");
	colonies[FindColony("Bridgetown")].DontSetShipInPort = true;
    //������� �� �����
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
    //GiveItem2Character(Pchar, "unarmed");
    //EquipCharacterByItem(Pchar, "unarmed");
    TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
    SetCharacterPerk(Pchar, "Doctor1");
	
	//����� �����
    sld = GetCharacter(NPC_GenerateCharacter("Beyns", "trader_8", "man", "man", 7, ENGLAND, 1, false));
    sld.name = "�����";
    sld.lastname = "�����";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "cit_common";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto12");
	
    //==============//������� ����//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Pitt", "PBLine_Pitt_0", "man", "man", 1, ENGLAND, -1, false)); //TO_DO �������� ������� �� ���������� ��������
    sld.name 	= "�������";
    sld.lastname 	= "����";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_YoungMan";
//                  P I R  A T E  S
    SetSPECIAL(sld, 5,9,7,5,10,7,4);
    sld.rank = 12;
    sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.HalfImmortal = true;  // ��������
	sld.HeroModel = "PBLine_Pitt_0,PBLine_Pitt_1,PBLine_Pitt_2,PBLine_Pitt_3,PBLine_Pitt_4,PBLine_Pitt_5";
	sld.loyality = MAX_LOYALITY;
    InitStartParam(sld);
    //SetRandSPECIAL(sld);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 40, 25);
    //int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn
    SetShipSkill(sld, 40, 30, 25, 25, 50, 25, 25, 25, 30);
	
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");

    SetFantomHP(sld);
    SetEnergyToCharacter(sld);
   	LAi_SetImmortal(sld, true);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto1");
	
	pchar.quest.CureLordMovie.win_condition.l1 = "locator";
	pchar.quest.CureLordMovie.win_condition.l1.location = "EstateBadroom1";
	pchar.quest.CureLordMovie.win_condition.l1.locator_group = "quest";
	pchar.quest.CureLordMovie.win_condition.l1.locator = "quest1";
	pchar.quest.CureLordMovie.function = "CureLord";

}

void CureLord(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "EstateBadroom1", "reload", "reload1");
    sld.dialog.currentnode = "EBStep_1";
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);

}

void CureLordMovie()
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	ChangeShowIntarface();
    LAi_SetActorTypeNoGroup(Pchar);
    LAi_ActorGoToLocator(Pchar, "goto", "goto6", "CureLordMovie_Con1", 10.0);
}

void CureLordMovie_Con1()
{
    LAi_ActorTurnToLocator(Pchar, "goto", "goto7");
    LAi_ActorAnimation(Pchar, "Barman_idle", "CureLordMovie_Con2", 5);
}

void CureLordMovie_Con2()
{
    LAi_Fade("CureLordMovie_Con3", "");
}

void CureLordMovie_Con3()
{

    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    sld.dialog.currentnode = "EBStep_2";
//   	sld.talker = 10;
//    LAi_SetActorTypeNoGroup(sld);
//	LAi_ActorDialog(sld, pchar, "",  2, 0);
    ChangeCharacterAddressGroup(sld, "EstateOffice", "goto", "goto6");
    LAi_SetStayTypeNoGroup(sld);
    DoReloadCharacterToLocation("EstateOffice", "goto", "goto3");
    EndQuestMovie();
   	ChangeShowIntarface();
    LAi_SetPlayerType(Pchar);
    InterfaceStates.Buttons.Save.enable = true;

}

void BloodGetBlade(string qName)
{
    LAi_SetCheckMinHP(Pchar, 1, true, "CapBlood_CheckMinHP");
   	LAi_SetImmortal(pchar, false);
}

void DragunInvansion()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Pitt")];
    sld.dialog.currentnode = "PStep_5";
    ChangeCharacterAddressGroup(sld, "EstateOffice", "reload", "reload1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "",  -1, 0);
}

void DragunInvansion2()
{
    pchar.quest.BloodGetBlade.win_condition.l1 = "item";
    pchar.quest.BloodGetBlade.win_condition.l1.item= "blade2";
    pchar.quest.BloodGetBlade.function = "BloodGetBlade";
    pchar.quest.DragunInvansion.win_condition.l1          = "location";
    pchar.quest.DragunInvansion.win_condition.l1.location = "Estate";
    pchar.quest.DragunInvansion.function                  = "_DragunInvansion3";

}

void _DragunInvansion3(string qName)
{
    chrDisableReloadToLocation = true; // ������� ����� �� �������
    DoQuestFunctionDelay("DragunInvansion3", 60.0);
}

void DragunInvansion3(string qName)
{
    ref ch, sld;
    LAi_LocationFightDisable(loadedLocation, true);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix

	ch = GetCharacter(NPC_GenerateCharacter("CapGobart", "Hobart", "man", "man", 10, ENGLAND, 0, false));
    ch.name 	= "�������";
    ch.lastname 	= "������";
    ch.Dialog.CurrentNode = "First time";
    ch.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    ch.greeting = "soldier_arest";
    ch.location = "none";
    FantomMakeCoolFighter(ch, 25, 70, 70, "blade22", "pistol2", 20);
    LAi_SetImmortal(ch, true);
    ch.BreakTmplAndFightGroup = true; //fix
    LAi_group_MoveCharacter(ch, "TmpEnemy");
    //LAi_group_MoveCharacter(ch, "EnemyFight");
    ChangeCharacterAddressGroup(ch, "Estate", "goto", "goto1");
    LAi_SetActorTypeNoGroup(ch);
	LAi_ActorDialog(ch, pchar, "", 7, 0);

    for (int i=0 ; i<=4; i++)
    {
    	// ������� c �������������
		sTemp = "SoldierEnglish_1";
		if (i == 1) sTemp = "Dragoon_1"; 
        sld = GetCharacter(NPC_GenerateCharacter(("Dragun_"+i), sTemp, "man", "man", 2, ENGLAND, 0, false));
        sld.location = "none";
        sld.BreakTmplAndFightGroup = true;
        SetSPECIAL(sld, 8,10,9,3,6,10,4);
        InitStartParam(sld);
        SetEnergyToCharacter(sld);
        LAi_SetImmortal(sld, true); // ����� �������
        //LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
        GiveItem2Character(sld, "blade4");
    	EquipCharacterByItem(sld, "blade4");
	    sld.Dialog.CurrentNode = "Draguns_0";
        sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
        LAi_group_MoveCharacter(sld, "TmpEnemy");
        //LAi_group_MoveCharacter(sld, "EnemyFight");
    	ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload1");
        LAi_SetActorTypeNoGroup(sld);
    	if(i < 3)
    	{
        	if( i > 1 )
        	{
            	GiveItem2Character(sld, "pistol2");
            	EquipCharacterByItem(sld, "pistol2");
            	TakeNItems(sld, "bullet", 30);
				AddItems(sld, "GunPowder", 30);
            }
            LAi_ActorFollow(sld, ch, "", -1);
        }
        if(i == 3)LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 20);
        if(i == 4)LAi_ActorRunToLocation(sld, "reload", "reload5", "none", "", "", "", 20);
     }

}

void DragunInvansion4()
{
 	StartQuestMovie(true, true, true);
	locCameraToPos(18.241, 13, 0.35, false); 
	ref ch, sld;
    LAi_LockFightMode(pchar, false);
    LAi_LocationFightDisable(loadedLocation, false);
    ch = &characters[GetCharacterIndex("Pitt")];
    ChangeCharacterAddressGroup(ch, "Estate", "reload", "reload5");
    LAi_SetActorType(ch);
    LAi_ActorGoToLocator(ch, "goto", "goto5", "", -1);
    
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
    LAi_SetActorType(sld);
    LAi_ActorFollow(sld, ch, "", -1);

    for (i=1; i<5; i++)
    {
        sld = &characters[GetCharacterIndex("Dragun_"+i)];
        //LAi_group_MoveCharacter(sld, "TmpEnemy");
        if(i == 3 || i == 4)
        {
            ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorFollow(sld, ch, "", -1);
        }
        else
        {
            //LAi_SetStayTypeNoGroup(sld);
            //LAi_SetWarriorType(sld);
            //LAi_SetGuardianType(sld);
        }
    }

}

void CapGobartAttack(string qName)
{
    ref sld;
    int numdead = 0;
    for (i=1; i<=2; i++)
    {
        sld = characterFromID("Dragun_"+i);
        if (CharacterIsDead(sld))
        {
            numdead++;
        }
    }
    if(numdead == 2)
    {
        sld = characterFromID("CapGobart");
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
}
/////////////////////////////////////////////////////////////////////////
void Blood_StartGame_End(string qName)
{
    ref sld;
    chrDisableReloadToLocation = true;
    InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;
    sld = characterFromID("Dragun_0");
    LAi_RemoveCheckMinHP(sld);
    pchar.quest.CapGobartAttack_1.over = "yes";
    pchar.quest.CapGobartAttack_2.over = "yes";

	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;

    Pchar.model="PGG_Blad_6";
	DoQuestFunctionDelay("CapBloodLineInit", 0.1);
}


void CapBloodLineInit(string qName)
{
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
    // C���
    sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = "����������";
    sld.lastname = "C���";
    // ������ �����
	Environment.date.month = 4;
    SetCurrentTime(23, 1);
    pchar.quest.onPlantation.win_condition.l1          = "location";
    pchar.quest.onPlantation.win_condition.l1.location = "BridgeTown_Plantation";
    pchar.quest.onPlantation.function                  = "CapBloodLine_q1";
    //DoReloadCharacterToLocation("BridgeTown_Plantation", "patrol", "patrol12");

    //����� ������, ������� ��� ���               //to_do
    int n= FindLocation("Bridgetown_town");  // �� ������ �������
    locations[n].reload.l3.close_for_night = false;
    //��� ����������� � ��������
    bDisableLandEncounters = true;

	PostVideoAndQuest("slave", 100, "move_slave_2");
}

void CapBloodLine_firstEnterHome(string qName)
{	
	sld = characterFromID("Pitt");
	sld.Dialog.CurrentNode = "PStep_7";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "Plantation_S1", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
	Pchar.questTemp.CapBloodLine.statcrew = "";	
}


void CapBloodLine_q1(string qName)
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, true);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    chrDisableReloadToLocation = true; // ������� ����� �� �������
    bDisableFastReload = true; // ������� ��������.
    Pchar.questTemp.CapBUnarmed = true; //�� ����� �� ��������

    //����� �� ����������
   	sld = GetCharacter(NPC_GenerateCharacter("Bishop", "PBLine_Bishop", "man", "man", 1, ENGLAND, 3, false));
    sld.name 	= "���������";
    sld.lastname 	= "�����";
    sld.Dialog.CurrentNode = "First Bishop";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Bishop";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	LAi_SetImmortal(sld, true);

    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "reload", "houseSp1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

    //������� ����
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS1_3");
	
    //���������
	sld = GetCharacter(NPC_GenerateCharacter("Griffin", "shipowner_11", "man", "man", 10, ENGLAND, 3, false));
	sld.name = "��";
	sld.lastname = "�������";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Master";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto","goto1");
	
	LAi_SetImmortal(sld, true);
    //�����
	sld = GetCharacter(NPC_GenerateCharacter("Hells", "shipowner_9", "man", "man", 10, PIRATE, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.name = "������";
	sld.lastname = "������";
    sld.SaveItemsForDead = true; // ��������� �� ����� ����
    sld.DontClearDead = true;
	sld.greeting = "Gr_Fisher";
	AddMoneyToCharacter(sld, 2000);
	FantomMakeCoolFighter(sld, 7, 25, 50, "topor1", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    LAi_SetOwnerTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto","goto4");
	
	//������
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Smuggler", "Pirate_4", "man", "man", 10, ENGLAND, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Smuggler Agent";
	LAi_SetSitTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit2");

    //������ � �������
    int i=rand(2)
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Habitue", "citiz_"+(rand(11)+1), "man", "man", 10, ENGLAND, 3, false));
	sld.greeting = "Gr_Tavern_Mate";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front" + (i+1);
    LAi_SetCitizenType(sld);
    LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base"+(1+i));
	
    //==============//����������//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Volverston", "PBLine_Volverston_0", "man", "man", 12, ENGLAND, -1, false)); 
    sld.name 	= "����������";
    sld.lastname 	= "";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_questOfficer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.HalfImmortal = true;  // ��������
	sld.loyality = MAX_LOYALITY;
	sld.HeroModel = "PBLine_Volverston_0,PBLine_Volverston_1,PBLine_Volverston_2,PBLine_Volverston_3,PBLine_Volverston_4,PBLine_Volverston_5";
//                     P  I  E  A  T  R  S
	SetSPECIAL(sld, 10, 7, 9, 8, 8, 4, 8);
//    SetSPECIAL(sld, 5,9,7,5,10,7,4);
    //int           _fl,  f,  fh, p,  fr
    SetSelfSkill(sld, 20, 30, 45, 30, 40);//
    //int            ld,  cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 45, 30, 15, 15, 10, 40, 45, 30, 20);
   	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	//SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Rush");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseF2_1");
	
    //==============//���������   �������//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Hugtorp", "PBLine_Hagtorp_0", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= "���������";
    sld.lastname 	= "�������";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.HalfImmortal = true;  // ��������
	sld.HeroModel = "PBLine_Hagtorp_0,PBLine_Hagtorp_1,PBLine_Hagtorp_2,PBLine_Hagtorp_3,PBLine_Hagtorp_4,PBLine_Hagtorp_5";
	sld.loyality = MAX_LOYALITY;
//                    P  I  E  A  T  R  S
	SetSPECIAL(sld, 8, 9, 8, 8, 9, 8, 7);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 20, 40, 35, 30, 30);
    //int _ld, int _cr,  ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 45, 30, 25, 25, 20, 25, 35, 30, 20);
   	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "Brander");
	SetCharacterPerk(sld, "Troopers");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
   	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS2_2");
   	
    //==============//������� ����//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Dieke", "PBLine_Daik_0", "man", "man", 10, PIRATE, -1, false));
    sld.name 	= "�������";
    sld.lastname 	= "����";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.HalfImmortal = true;  // ��������
	sld.HeroModel = "PBLine_Daik_0,PBLine_Daik_1,PBLine_Daik_2,PBLine_Daik_3,PBLine_Daik_4,PBLine_Daik_5";
	sld.loyality = MAX_LOYALITY;
//                    P  I  E  A  T  R  S
	SetSPECIAL(sld, 6, 8, 7, 5, 9, 9, 7);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 30, 30);
    //                ld, cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 30, 35, 20, 20, 20, 45, 25, 35, 20);
   	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "LightRepair");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "EnergyPlus");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseF1_1");
	
    //==============//��� ���//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Ogl", "PBLine_NedOgl_0", "man", "man", 10, ENGLAND, -1, false)); 
    sld.name 	= "���";
    sld.lastname 	= "���";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Ogl";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    LAi_SetStayTypeNoGroup(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
    sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.HalfImmortal = true;  // ��������
	sld.loyality = MAX_LOYALITY;
	sld.HeroModel = "PBLine_NedOgl_0,PBLine_NedOgl_1,PBLine_NedOgl_2,PBLine_NedOgl_3,PBLine_NedOgl_4,PBLine_NedOgl_5";
	SetSPECIAL(sld, 8, 9, 5, 5, 9, 5, 7);
    //int           _fl,  f,  fh, p,  fr
    SetSelfSkill(sld, 20, 30, 20, 35, 30);
    //int            ld,  cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 20, 10, 50, 40, 15, 20, 20, 20, 20);
   	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "SharedExperience");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Plantation_S2", "barmen", "stay");
	
    //==============//������ ��� �����//==============
    sld = GetCharacter(NPC_GenerateCharacter("Slave_Quest", "shipowner_6", "man", "man", 7, ENGLAND, 2, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Dialog.CurrentNode = "SLQStep_0";
    sld.greeting = "Gr_slave";
    sld.talker = 10;
    sld.CityType = "citizen";
	sld.city = "BridgeTown";
	LAi_SetLoginTime(sld, 6.0, 22.99);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto12");
	LAi_SetCitizenType(sld);
    LAi_group_MoveCharacter(sld, sTemp);

    //��������� ��������� ��� �� ��������
	SetQuestsCharacters();

    // ������ ����� � �����
    pchar.quest.CapBloodLine_q1_1.win_condition.l1          = "location";
    pchar.quest.CapBloodLine_q1_1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodLine_q1_1.function                  = "_PrepareBridgeTown";
}

void ChangePIRATES()
{
	pchar.SystemInfo.ChangePIRATES = true;
	LaunchCharacter(pchar);
}

void _PrepareBridgeTown(string qName)
{
    DoQuestFunctionDelay("PrepareBridgeTown", 1.0);
}
void PrepareBridgeTown(string qName)
{
    trace("PrepareBridgeTown");
    //������ ����� ��� �������
    ChangeBridgeTownDialogs(false);
    //������ �� ������ � ����������
    ref sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.Dialog.CurrentNode = "First Guard";
    sld.protector = true;
    sld.protector.CheckAlways = 1 ;
    LAi_RemoveLoginTime(sld);
    LoginCharacter(sld, "BridgeTown_town");
    //�������
    LoginNettl("");
    //������� ���������� �� ����
    LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true); //fix
    LocatorReloadEnterDisable("BridgeTown_fort", "reload2", true); //fix
    //������ ����� �� �������
    //int n = FindLocation("Bridgetown_tavern");
    //locations[n].habitues = 0;
    //������� �����
    sld = &characters[GetCharacterIndex("Bridgetown_Smuggler")]
    LoginCharacter(sld, "Bridgetown_tavern");

}

void DetectBlades()
{
    if (Pchar.questTemp.CapBloodLine == true && Pchar.questTemp.CapBUnarmed == true)
    {
        string sweapon = FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE);
        //Log_Info("������:"+sweapon);
        bool bblades = ( sweapon != "unarmed") && !HasSubStr(sweapon, "blade5") && (sweapon!= "");
        bool bguns = (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "");
        if(bblades || bguns)
        {
            pchar.quest.CapBloodDetectBlades1.win_condition.l1          = "location";
            pchar.quest.CapBloodDetectBlades1.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.CapBloodDetectBlades1.function                  = "TakeBlades";
            
            pchar.quest.CapBloodDetectBlades2.win_condition.l1          = "location";
            pchar.quest.CapBloodDetectBlades2.win_condition.l1.location = "BridgeTown_Plantation";
            pchar.quest.CapBloodDetectBlades2.function                  = "TakeBlades";
        }
        if(sweapon == "")
        {
            /*sweapon = "unarmed";
            GiveItem2Character(Pchar, "unarmed");
            EquipCharacterByItem(Pchar, sweapon);*/
        }
        else
        {
            EquipCharacterByItem(Pchar,GetCharacterEquipByGroup(Pchar, BLADE_ITEM_TYPE));
        }
    }
}

void TakeBlades(string qName)
{
    sld = GetCharacter(NPC_GenerateCharacter("SolderTakeBlades", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "soldier_arest";
    sld.location = "none";
    sld.BreakTmplAndFight = true;
    //SetFantomParamHunter(sld); //������ �����
    SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
    pchar.quest.SolderTakeBladesDie.win_condition.l1 = "NPC_death";
    pchar.quest.SolderTakeBladesDie.win_condition.l1.character = "SolderTakeBlades";
   	pchar.quest.SolderTakeBladesDie.function = "SolderTakeBladesDie";
	//Log_Info("������ � �� ������� �����!");

}

void SolderTakeBladesDie(string qName)
{
    chrDisableReloadToLocation = false;
}


//������ ���� ������
void ChangeBridgeTownDialogs(bool restore)
{
    ref sld;
    int num, cur;
    num = 0;
    cur = rand(3)+1;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        //�������
        if (CheckAttribute(sld, "city") && sld.city == "Bridgetown")
        {
            if(CheckAttribute(sld, "CityType") && sld.CityType == "soldier")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_Soldier.c";
                }
                sld.lifeDay = 3;
            }
            //��������
            if(CheckAttribute(sld, "CityType") && sld.CityType == "citizen")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    if(sld.location.group == "merchant")
                    {   //��������
                        num++;
                        if(num == cur) // ��� ������ �� ������ ������ ����� ������ ��������
                        {
                            sld.quest.bGoodMerch = true;
                        }

                    }
                }
                else
                {
                    if(sld.location.group == "merchant")
                    {   //��������
                        sld.dialog.filename = "Common_ItemTrader.c";
                    }
                    else
                    {   //�������
                        sld.dialog.filename = "Common_citizen.c";
                    }
                }
                sld.lifeDay = 3;
            }
            //�����
            if(sld.id == "Bridgetown_Poorman")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_poorman.c";
                }
            }

            //���������
            if(sld.id == "QuestCitiz_Bridgetown")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    sld.Dialog.CurrentNode = "First time";
                }
                else
                {
                    sld.dialog.filename = "Quest\ForAll_dialog.c";
                }
            }
        }

	}
}

void LoginNettl(string qName)
{

        Pchar.questTemp.CapBloodLine.TalkWithNettl = false;          //10//3
		sld = GetCharacter(NPC_GenerateCharacter("Nettl", "shipowner_2", "man", "man", 7, ENGLAND, 3, false));
        sld.name = "������";
        sld.lastname = "�������";
		sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
		sld.dialog.currentnode = "First time";
		sld.city = "Bridgetown_town";
		sld.greeting = "Gr_Tavern_Mate";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
		//SetFantomParamFromRank(sld, Rank, true);
		LAi_SetCitizenType(sld);
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
		LAi_group_MoveCharacter(sld, sTemp);
		sld.talker = 10;
		PlaceCharacter(sld, "goto", "random");
}

void CapBloodLine_q1_Late(string qName)
{
    InterfaceStates.Buttons.Save.enable = false;
  //  SetLaunchFrameFormParam("���������� ���� �� ������� ������ �����"+ NewStr() +
  //  " ��� ������������� � �� ����."+ NewStr() +
  //  "��������� ���������� �������������� �������, "+ NewStr() +
  //  "����� ��� ����� ������� �� ������ � �������� ��� ����� �� ��������� ������."+ NewStr() +
  //  "������ ��� ���� ��������� ����� � ����� ��������� ������ �����."+ NewStr() +
  //  "������� �����������, �� ���������...", "", 0.1, 7.0);
//	LaunchFrameForm();
 //   PostEvent("LAi_event_GameOver", 15000, "s", "land");
    //PostEvent(GAME_OVER_EVENT, 15000);
    GameOver("blood");
}

void CapBloodLine_q1_End(string qName)
{
   AddQuestRecord("CapBloodLine_q1", "6");
   Pchar.questTemp.CapBloodLine.stat = "CureMisStid_Complite";
}

void CapBloodLine_q1_Complited(string qName)
{
    ref sld
    trace("CapBloodLine_q1_Complited!!!");
    pchar.quest.CapBloodLineTimer_1.over = "yes";
    sld = &characters[GetCharacterIndex("MisStid")];
//    sld.lifeDay = 0;
    sld.location = "none";
    sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.Dialog.CurrentNode = "First time";
    
    int n= FindLocation("Bridgetown_town");
    locations[n].reload.l3.close_for_night = true;//��������� ����������
    AddQuestRecord("CapBloodLine_q1", "7");
    CloseQuestHeader("CapBloodLine_q1");
    //LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 12, 0); // ������ �����
    SetCurrentTime(7, 0); // ������ ���� 2-� ����� 7 �����
    bQuestCheckProcessFreeze = false;
    SetLaunchFrameFormParam("�� ��������� ����...", "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Bridgetown_tavern", "reload","reload2", "");
	LaunchFrameForm();
	CapBloodLine_q2();
}

void CapBloodLine_q2()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.dialog.currentnode = "First time";
    Pchar.questTemp.CapBloodLine.stat = "WakerOffer";
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern_upstairs", "goto","goto1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "", 2.0, 0);
    AddQuestRecord("CapBloodLine_q2", "2");
    AddQuestRecord("CapBloodLine_q2", "3");
    
    //����� 10 �����
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 17;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

}

void Spain_spyDie(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Spain_spy")];
    LAi_KillCharacter(sld);
}

void LoginSpain_spy(string qName)
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "shipowner_13", "man", "man", 7, SPAIN, 2, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = "������";
    sld.lastname = "������";
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
    //SetFantomParamHunter(sld); //������ �����
    FantomMakeCoolFighter(sld, 7, 30, 50, "blade6", "", 20);
    TakeItemFromCharacter(sld, "spyglass3");
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void SpainSpyAttack(string qName)
{
    LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 0, 10); // ������ �����
    bQuestCheckProcessFreeze = false;
    AddQuestRecord("WeaponsForEscape", "8");
    LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);
}

void _DeadSolder(string qName)
{
    PlaySound("People Fight\Death_NPC_04.WAV");
    DoQuestFunctionDelay("DeadSolder", 1.0);
}

void DeadSolder(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("CPBQuest_Solder")];
    TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
    GiveItem2Character(sld, "blade6");
    LAi_KillCharacter(sld);
}

void FindMsStid_ring(string qName)
{
    AddQuestRecord("WeaponsForEscape", "14");
}



void LoginWinterwood()
{
    ref sld, ch, itm;
	sld = GetCharacter(NPC_GenerateCharacter("Winterwood", "officer_20", "man", "man", 10, PIRATE, 3, false));
	sld.name = "������";
	sld.lastname = "���������";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.greeting = "pirat_common";
    FantomMakeCoolFighter(sld, 7, 25, 20, "blade10", "pistol3", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    GiveItem2Character(sld, "DOjeronRing"); //����� to_do
    itm = ItemsFromID("DOjeronRing");
	itm.picIndex = 15;
    itm.picTexture = "ITEMS_13";
    ChangeItemDescribe("DOjeronRing", "itmdescr_HugtorpRing");
    ChangeItemName("DOjeronRing", "itmname_HugtorpRing");
    AddMoneyToCharacter(sld, 1000);
    sld.SaveItemsForDead = true; // ��������� �� ����� ����
    sld.DontClearDead = true;
    LAi_SetCitizenType(sld);
    
    string sQuest = "WinterwoodDuel";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "WinterwoodDie";

    if(!rand(1))
    {
   	    LAi_SetSitTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit4");
    }
    else
    {
   	    LAi_SetStayTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_Brothel_room", "goto","goto3");
        
		ch = GetCharacter(NPC_GenerateCharacter("Qhorse", "horse07", "woman", "towngirl", 10, ENGLAND, 1, false));
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(ch, sTemp);
        LAi_SetActorTypeNoGroup(ch);
		LAi_ActorAfraid(ch, Pchar, false);
		ChangeCharacterAddressGroup(ch, "Bridgetown_Brothel_room", "goto","goto1");
		
        int n= FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = false;
        
    }
}

void WinterwoodDuel(string qName)
{
	pchar.quest.Winterwood2Place.win_condition.l1 = "Location";
	pchar.quest.Winterwood2Place.win_condition.l1.location = "Bridgetown_ExitTown";
	pchar.quest.Winterwood2Place.function = "Winterwood2Place";
}

void Winterwood2Place(string qName)
{
    ref sld;
    sld = characterFromID("Winterwood");
   	sld.Dialog.CurrentNode = "talk_off_town";
    if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); // ���� �� ���� ������ � ������
		DeleteAttribute(sld, "CityType");
	}
   	ChangeCharacterAddressGroup(sld, "Bridgetown_ExitTown", "goto","goto1");
   	LAi_SetStayTypeNoGroup(sld);
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void Winterwood_Prepare_Fight()
{
	int i, idx;
	ref npchar, rLoc;

	npchar = characterFromID("Winterwood");
	makeref(rLoc, Locations[FindLoadedLocation()]);

	if (CheckAttribute(rLoc, "type") && rLoc.type == "tavern")
	{
		if (PChar.chr_ai.type == LAI_TYPE_SIT)
		{
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
		}
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
		PChar.Quest.Duel_Fight_Right_Now.function = "Winterwood_Fight_Right_Now";

		LocationMakeClone(pchar.location);
		Locations[FindLocation("Clone_location")].image = "loading\TavernFight_"+rand(1)".tga";
		DoReloadCharacterToLocation("Clone_location", pchar.location.group, pchar.location.locator);
		PlaceCharacter(npchar, "goto", "Clone_location")
	}
	else
	{
		DoQuestFunctionDelay("Winterwood_Fight_Right_Now", 0.5);
	}
	LAi_SetWarriorType(npchar);
	LAi_group_MoveCharacter(npchar, "DUEL_FIGHTER");
}

void Winterwood_Fight_Right_Now(string qName)
{
	bool bOk = false;
	ref sld = &Locations[FindLocation(pchar.location)];

	//���������� ������ �� ������ � �������
	if (CheckAttribute(sld, "noFight"))
	{
		bOk = sti(sld.noFight);
	}
	if (bOk)
	{
		LAi_LocationFightDisable(sld, !bOk);
		pchar.questTemp.LocFightEnable = bOk;
	}
	//������� �����
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DUEL_FIGHTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DUEL_FIGHTER", LAI_GROUP_PLAYER, true);
	chrDisableReloadToLocation = true;
}

void WinterwoodDie(string qName)
{
    if (CheckAttribute(PChar, "quest.Winterwood2Place")) Pchar.quest.Winterwood2Place.over = "yes";
    if (CheckAttribute(PChar, "quest.CapBloodLineTimer_3")) Pchar.quest.CapBloodLineTimer_3.over = "yes";

	//��������������� ������ �� ������, ���� ���
	if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
	{
		sld = &Locations[FindLocation(pchar.location)];
		LAi_LocationFightDisable(sld, true);
		DeleteAttribute(pchar, "questTemp.LocFightEnable");
	}

	//���� � ������� �����, �� ��������� ���� ��� ������
	if (CheckAttribute(pchar, "questTemp.LocationClone") && sti(pchar.questTemp.LocationClone))
	{
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	}

	//������ ������
	DoQuestCheckDelay("hide_weapon", 2.0);
	chrDisableReloadToLocation = false;
    AddQuestRecord("HugtorpTrouble", "3");
}

void MoneyForDieke(string qName)
{
    sld = characterFromID("Dieke");
    sld.Dialog.CurrentNode = "DKStep_3";
    AddQuestRecord("DiekeQuest", "4")
}

void CapBloodLine_q2_Late(string qName)
{
    InterfaceStates.Buttons.Save.enable = false;
    GameOver("blood");
}

void CapBloodLine_q2_Complited()
{
    ref sld;
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    AddQuestRecord("CapBloodLine_q2", "6");
    int n= FindLocation("Bridgetown_tavern");
    locations[n].reload.l2.disable = false;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.Dialog.CurrentNode = "WStep_11";
    LAi_SetStayTypeNoGroup(sld);
    
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 12, 0); // ������ �����
    Environment.date.day = 3;
    SetCurrentTime(7, 0); // ������ ���� 3-� ����� 7 �����
    bQuestCheckProcessFreeze = false;
    
    //�����
    sld = GetCharacter(NPC_GenerateCharacter("MoneySpy", "shipowner_5", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade9", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    sld.quest.meeting = 0;
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    sld.talker = 10; //fix
   	ChangeCharacterAddressGroup(sld, "CommonDoubleFlourHouse_1", "barmen", "stay");
    //#20190120-02
    LocatorReloadEnterDisable("BridgeTown_town", "houseS1", false);
    //��������� ���
    sld = GetCharacter(NPC_GenerateCharacter("Fisherman", "shipowner_8", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.name = "�������";
    sld.lastname = "����������";
	sld.greeting = "Gr_Fisher";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front4";//fix
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetSitType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base4"); //fix
    
    //��� �������
    sld = GetCharacter(NPC_GenerateCharacter("Jack", "DSolovey", "man", "man_kvl2", 10, ENGLAND, 1, false));
    sld.name = "�������";
    sld.lastname = "�������";
    sld.greeting = "Gr_Solovey";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade7", "", 10);
    sld.dialog.currentnode = "JSTStep_0";
    sld.talker = 10;
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetStayType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    //LAi_SetOwnerTypeNoGroup(sld);
   	ChangeCharacterAddressGroup(sld, "Bridgetown_Store", "goto", "goto1");
   	sld = characterFromID("Bridgetown_trader");
   	LAi_SetLoginTime(sld, 0.0, 1.0);
   	
    //�����
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 15;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

    SetLaunchFrameFormParam("�� ��������� ����...", "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Plantation_S1", "goto", "goto1", "");
   	LaunchFrameForm();
}

void QUsurerLate(string qName)
{
    ChangeCharacterHunterScore(PChar, "enghunter", 30);//fix ���� -30;
}

void LoginMainer()
{

        Pchar.questTemp.CapBloodLine.ShipForJack = false;
		sld = GetCharacter(NPC_GenerateCharacter("Mainer", "officer_1", "man", "man", 7, ENGLAND, 3, false));
        sld.name = "����";
        sld.lastname = "������";
		sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		sld.dialog.currentnode = "MNStep_0";
		sld.city = "Bridgetown_town";
		//sld.greeting = "Gr_Tavern_Mate";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
		//SetFantomParamFromRank(sld, Rank, true);
		LAi_SetCitizenType(sld);
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
		LAi_group_MoveCharacter(sld, sTemp);
	//	sld.talker = 10;
        ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "reload1");
}

void CapBloodLine_q3_Complited()
{
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    pchar.quest.CapBloodEscape1.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape1.function                  = "ReturnToPlantation1";

    //pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
    //pchar.quest.CapBloodEscape2.win_condition.l1.location = "BridgeTown_Plantation";
    //pchar.quest.CapBloodEscape.function                  = "ReturnToPlantation2";

}

void ReturnToPlantation1(string qName)
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("SolderTakeBlades", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "STBStep_2";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
    sld.BreakTmplAndFightGroup = true;
    SetFantomParamHunter(sld); //������ �����
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;

}

void ReturnToPlantation2(string qName)
{
    ref sld;
    sld = characterFromID("Hugtorp");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	
    sld = characterFromID("Pitt");
    ChangeCharacterAddressGroup(sld, "None", "", "");
	chrDisableReloadToLocation = true;
}

void ReturnToPlantation3()
{
    ref sld;
    SetLocationCapturedState("BridgeTown_Plantation", true);
    string sTemp = "TmpEnemy";
   	LAi_group_SetHearRadius(sTemp, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(sTemp, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(sTemp, LAI_GROUP_GRD_LOOK - 1);
    LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0);

    SetShipInBridgetown(); // ������� ���������
    Pchar.questTemp.CapBUnarmed = false;

    sld = characterFromID("Hugtorp");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.talker = 10;
    sld.Dialog.CurrentNode = "HTStep_18"; //to_do
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest3");

    sld = characterFromID("Volverston");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.Dialog.CurrentNode = "HTStep_18";  //to_do
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
	LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest4");
	
    sld = characterFromID("Ogl");
    LAi_LoginInCaptureTown(sld, true);
    sld.Dialog.CurrentNode = "HTStep_18";  //to_do
    LAi_SetStayTypeNoGroup(sld);
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest5");

    sld = characterFromID("Dieke");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.Dialog.CurrentNode = "HTStep_18";  //to_do
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest6");
    
    sld = characterFromID("Pitt");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetActorType(sld);
    LAi_ActorSetLayMode(sld);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit2");

    worldMap.date.day = 4;
    Environment.date.day = 4;
    SetCurrentTime(0, 0);

    int n = FindLocation("BridgeTown_Plantation");
    DeleteAttribute(&locations[n], "citizens");
    DeleteAttribute(&locations[n], "carrier");
    
    DoReloadCharacterToLocation("BridgeTown_Plantation", "reload", "reload1_back");
    SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
    
    for (int i=0; i < 7; i++)
	{
        if(i < 2)
        {
            sld = GetCharacter(NPC_GenerateCharacter("PittGuard_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
            SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
            LAi_LoginInCaptureTown(sld, true);
            LAi_SetActorType(sld);
            LAi_SetStayType(sld); // �����������
            LAi_group_MoveCharacter(sld, sTemp);
    		//LAi_SetGuardianTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit"+(2*i+1));
        }
        else
        {
            int iChar = NPC_GeneratePhantomCharacter("soldier", ENGLAND, MAN, 2);
            sld = &characters[iChar];
    		SetNPCModelUniq(sld, "soldier", MAN);
    		sld.City = "Bridgetown";
            sld.CityType = "soldier";
            SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
            LAi_LoginInCaptureTown(sld, true);
           	LAi_SetWarriorType(sld);
    		LAi_SetPatrolType(sld);
            LAi_group_MoveCharacter(sld, sTemp);
    		PlaceCharacter(sld, "patrol", "random_free");
        }
        LAi_SetLoginTime(sld, 0.0, 24.0);
        sld.greeting = "soldier_common";
        sld.dialog.filename = "Common_Soldier.c";
        sld.dialog.currentnode = "first time";
	}

    //pchar.GenQuestBox.BridgeTown_Plantation.stay = true; fix
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.blade6 = 1;
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.potion1 = 3;
    
   	pchar.quest.CapBloodEscape3.win_condition.l1 = "locator";
	pchar.quest.CapBloodEscape3.win_condition.l1.location = "BridgeTown_Plantation";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator = "detector1";
	pchar.quest.CapBloodEscape3.function = "ReturnToPlantation4";
    
    chrDisableReloadToLocation = true;

    //int n = FindLocation("BridgeTown_Plantation");
    //DeleteAttribute(&locations[n], "citizens");

}

void ReturnToPlantation4(string qName)
{
    ref sld;
    string sTemp = "TmpEnemy";
   	LAi_group_SetHearRadius(sTemp, 3); // �����������
   	LAi_group_SetSayRadius(sTemp, 4);
   	LAi_group_SetLookRadius(sTemp, 5);
    for (i = 0 ; i < 2; i++)
    {
        sld = characterFromID("PittGuard_"+i);
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "PStep_11";
    LAi_SetGroundSitTypeNoGroup(sld);
    SetLocationCapturedState("Bridgetown_town", true);
    pchar.quest.CapBloodEscape4.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape4.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape4.function                  = "StillShip";
}

void StillShip(string qName)
{
    //SetCurrentTime(2, 0);

    ref chr,sld ;
    aref st;
    int iNation = SPAIN;
	string slai_group, locatorName, sType, slocator;

    slai_group = "TmpEnemy";
   	LAi_group_SetHearRadius(slai_group, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(slai_group, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(slai_group, LAI_GROUP_GRD_LOOK - 1);
   	//LAi_group_SetRelation(slai_group, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0);
    
	for (i=0; i < 11; i++)
	{
        chr = GetCharacter(NPC_GenerateCharacter("SpaSolder_"+i, "sold_spa_"+(rand(7)+1), "man", "man", sti(pchar.rank)+rand(2)+1, SPAIN, 1, false));
		chr.City = "Bridgetown";
        chr.CityType = "soldier";
        SetFantomParamFromRank(chr, sti(pchar.rank)+rand(2)+1, true); // ������ ����
		LAi_LoginInCaptureTown(chr, true);
        LAi_SetLoginTime(chr, 0.0, 24.0);
       	LAi_SetWarriorType(chr);
		LAi_SetPatrolType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
		chr.greeting = "soldier_common";
		slocator = PlaceCharacter(chr, "patrol", "random_free");
		while( slocator == "patrol13")  // ������� ������ � �������
		{
            slocator = PlaceCharacter(chr, "patrol", "random_free");
		}
        chr.dialog.filename = "Common_Soldier.c";
        chr.dialog.currentnode = "first time";
	}
	sld = GetCharacter(NPC_GenerateCharacter("SpaRaider", "off_spa_2", "man", "man", 10, SPAIN, 1, false));
    FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 25, 20, RandPhraseSimple("blade19","blade22"), "pistol2", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    sld.SaveItemsForDead = true; // ��������� �� ����� ����
    sld.DontClearDead = true;
    sld.BreakTmplAndFight = true;
	LAi_LoginInCaptureTown(sld, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, slai_group);
	sld.greeting = "soldier_common";
    sld.dialog.filename = "Common_Soldier.c";
    sld.dialog.currentnode = "first time";
	sld.City = "Bridgetown";
    sld.CityType = "soldier";
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "houseF2");
    
    string sQuest = "SaveArabelaService";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "SaveArabelaService";
    
	chr = GetCharacter(NPC_GenerateCharacter("ArabelaService", "Girl_8", "woman", "towngirl", 10, ENGLAND, 1, false));
	chr.greeting = "Enc_RapersGirl_1";
    chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    chr.dialog.currentnode = "ASStep_0";
//    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
    LAi_SetActorType(chr);
   	LAi_LoginInCaptureTown(chr, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    ChangeCharacterAddressGroup(chr, "Bridgetown_town", "officers", "houseH1_2");

    
	LAi_ActorRunToLocator(chr, "officers", "gate1_3", "SaveArabelaServiceAfraid", 5);
    LAi_ActorFollow(sld, chr, "", -1);
    
   	pchar.quest.CapBloodEscape5.win_condition.l1 = "locator";
	pchar.quest.CapBloodEscape5.win_condition.l1.location = "Bridgetown_town";
	pchar.quest.CapBloodEscape5.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodEscape5.win_condition.l1.locator = "quest11";
	pchar.quest.CapBloodEscape5.function = "ShipGuardsAlarm";
	
	ShipGuards();
	
	Pchar.questTemp.CapBloodLine.SpainInBridgetown = false;
	Pchar.questTemp.CapBloodLine.withCrew = false;
	
	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", true);
	LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", true);
	
    Colonies[FindColony("Bridgetown")].DontSetShipInPort = true;
    sld = characterFromID("Bridgetown Fort Commander");
    sld.Fort.Mode = FORT_DEAD;
	// data of frot die
	sld.Fort.DieTime.Year = GetDataYear();
	sld.Fort.DieTime.Month = GetDataMonth();
	sld.Fort.DieTime.Day = GetDataDay();
	sld.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(sld.index));

}

void ShipGuards()
{
    ref chr,sld;
    string slai_group = "EnemyFight";
    int iChar;
	ref location;
	string boxId = "box1";
	aref boxItems;	
   	string model[6];

    	// ==> ���� ��������
		model[0] = "shipowner_1";
		model[1] = "shipowner_6";
		model[2] = "shipowner_9";
		model[3] = "shipowner_10";
		model[4] = "pirate_1";
		model[5] = "pirate_8";


    LAi_group_Delete(slai_group); // fix
	for (int i=0; i <= 9; i++)
	{

        if(i <= 6)
        {

            chr = GetCharacter(NPC_GenerateCharacter("ShipGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 10, SPAIN, 1, false));
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // ������ ����
            LAi_SetImmortal(chr, true); //homo � �������� �� �� ��������� ;-)
    		LAi_LoginInCaptureTown(chr, true);
            LAi_SetLoginTime(chr, 0.0, 24.0);
    		LAi_SetActorTypeNoGroup(chr);
    		LAi_ActorStay(chr);
    		LAi_group_MoveCharacter(chr, slai_group);
    		ChangeCharacterAddressGroup(chr, "Bridgetown_town", "rld", "aloc"+i);
		}
		else
		{
            sld = GetCharacter(NPC_GenerateCharacter("FreeSlave_"+(i-6), model[rand(5)], "man", "man", 10, SPAIN, 1, false));
            SetFantomParamFromRank(sld, sti(pchar.rank)+makeint(2*MOD_SKILL_ENEMY_RATE/3), true); // ������ ����
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            LAi_LoginInCaptureTown(sld, true);
            LAi_SetActorType(sld);
    		LAi_ActorStay(sld);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest"+i);
        }
    }
    sld = GetCharacter(NPC_GenerateCharacter("SpaFirstMate", "off_spa_1", "man", "man", 12, SPAIN, 1, false));
    FantomMakeCoolFighter(sld, 12, 30, 30, "blade30", "pistol3", 10);
	LAi_LoginInCaptureTown(sld, true);
	//LAi_group_MoveCharacter(sld, slai_group); fix
    LAi_SetWarriorType(sld);
    ChangeCharacterAddressGroup(sld, "Cabin", "rld", "aloc0");
    pchar.quest.SpaFirstMateDie.win_condition.l1 = "NPC_death";
    pchar.quest.SpaFirstMateDie.win_condition.l1.character = "SpaFirstMate";
   	pchar.quest.SpaFirstMateDie.function = "SpaFirstMateDie";

	location = &Locations[FindLocation("Cabin")];
	makearef(boxItems, location.(boxId).items);
	boxItems.money = 4000 * MOD_SKILL_ENEMY_RATE + rand(2000) + 250;
	boxItems.chest = 4;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
}

void SaveArabelaService(string qName)
{
    ref sld;
    sld = characterFromID("ArabelaService");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	sld = characterFromID("Hugtorp");
	sld.talker = 10;
}

void CapBloodOfficers()
{
    string offName;
    ref sld;
    Pchar.questTemp.CapBloodLine.withCrew = true;
       for (int i=1 ; i <= 7; i++)
    {

        if(i > 4) offName ="FreeSlave_"+(i-4);
        switch(i)
        {
            case 1:
                offName ="Volverston";
            break;

            case 2:
                offName ="Hugtorp";
            break;
            
            case 3:

                offName ="Dieke";
            break;
            
            case 4:

                offName ="Ogl";
            break;
        }
        sld = characterFromID(offName);
        LAi_SetImmortal(sld, false);
        sld.DontClearDead = true;  // �� ������� ����
        sld.BreakTmplAndFight = true;
        LAi_SetActorType(sld);
        LAi_ActorFollow(sld, pchar, "", -1);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        sld.Dialog.CurrentNode = "HTStep_22b";  //

        
    }
}
void ShipGuardsDie()
{
    ref sld;
    chrDisableReloadToLocation = false;
    LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", false);
    sld = characterFromID("SpaFirstMate");
    LAi_group_MoveCharacter(sld, "EnemyFight");
}

void ShipGuardsAlarm(string qName)
{
    chrDisableReloadToLocation = true; // ������� ����� �� �������
    LAi_group_SetCheck("EnemyFight", "ShipGuardsDie");
    DoQuestFunctionDelay("AttakShip", 2.0);
}

void AttakShip(string qName)
{
    string offName;
    ref sld;
    int iChar;
    for (int i=0 ; i <= 9; i++)
    {
        offName = "ShipGuard_"+i;
        switch(i)
        {
            case 7:
                offName ="Volverston";
            break;

            case 8:
                offName ="Hugtorp";
            break;

            case 9:

                offName ="Dieke";
            break;

            case 10:
                offName ="Ogl";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar]
       	    LAi_SetWarriorTypeNoGroup(sld);
       	    if(Pchar.questTemp.CapBloodLine.withCrew) LAi_SetImmortal(sld, false);
        }
    }
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); // ����� �� �������� ����� � �����
    
}

void SpaFirstMateDie(string qName)
{
    string offName;
    ref sld;
    int iChar;
    for (int i=0; i < 13; i++)
	{

       offName = "SpaSolder_"+i;
        switch(i)
        {
            case 11:
                offName ="SpaRaider";
            break;

            case 12:
                offName ="ArabelaService";
            break;

        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.lifeDay = 0;
        }
    }
    pchar.quest.CapBloodEscape6.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape6.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape6.function                  = "QOfficersRecruit";
    AddQuestRecord("EscapeFormBarbados", "5");
    CloseQuestHeader("EscapeFormBarbados");
    ShipGuardsDie();
}

void QOfficersRecruit(string qName)
{
    string offName, sNode;
    ref sld;
    int iChar;
    for (int i=0 ; i <= 4; i++)
    {
        offName = "ShipGuard_"+i;
        switch(i)
        {
            case 0:
                offName ="Pitt";
                sNode = "PStep_16";
            break;
            
            case 1:
                offName ="Hugtorp";
                sNode = "HTStep_24";
            break;

            case 2:
                offName ="Dieke";
                sNode = "DKStep_5";
            break;

            case 3:
                offName ="Ogl";
                sNode = "OGLStep_11";
            break;
			
			case 4:
                offName ="Volverston";
                sNode = "VLStep_11";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.loyality = MAX_LOYALITY; //fix ���������� ���������
            LAi_SetImmortal(sld, false);//fix ������������ �����
       	    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "rld", "aloc"+(i+1));
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "quest", "quest11");
            sld.dialog.currentnode = sNode;
            if (offName =="Pitt") LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
            else LAi_SetStayTypeNoGroup(sld);

        }
    }
    //chrDisableReloadToLocation = true;

}

void CapBloodLaspEpisode(string qName)
{
    RestoreBridgetown();
}

void SpaCrewAtack()
{
    int hcrew,iChar,i;
    ref chref;
    
    chref = characterFromID("Pitt");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";

    string sGroup = "SpaCrew";
    Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"war");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);

	//Ship_SetTaskAbordage(SECONDARY_TASK, sti(chref.index), sti(Pchar.index)); // fix PRIMARY_TASK
	//chref.Ship_SetTaskAbordage = true; // ��������, ���� �� �������
	//chref.ShipTaskLock = true;

    for (i=0; i<2; i++)
    {
        iChar = NPC_GenerateCharacter("SpaBoat_"+i, "off_spa_2", "man", "man", 7, SPAIN, 1, true));
        makeref(chref, Characters[iChar]);
        chref.Ship.Mode = "war";
        chref.Ship.Type = GenerateShipExt(SHIP_LUGGER, 1, chref);
        SetRandomNameToCharacter(chref);
        SetRandomNameToShip(chref);
        

        SetBaseShipData(chref);
        hcrew = GetMaxCrewQuantity(chref);
        SetCrewQuantityOverMax(chref, 150);

        DeleteAttribute(chref,"ship.sails");
        DeleteAttribute(chref,"ship.masts");
        DeleteAttribute(chref,"ship.blots");

        Fantom_SetCannons(chref, "war");
        Fantom_SetBalls(chref, "war");
        SetFantomParamHunter(chref); //������ �����
        SetCaptanModelByEncType(sld, "war");//
        Group_AddCharacter(sGroup, chref.id);
        if (i == 0) Group_SetGroupCommander(sGroup, chref.id);
    }
    Group_SetAddress(sGroup, "Barbados", "IslandShips1", "ship_3");
}


void VolverstonAdd()
{
    ref chref;
    chref = characterFromID("Volverston");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";
}

void HugtorpAdd()
{
    ref chref;
    chref = characterFromID("Hugtorp");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";
}

void DiekeAdd()
{
    ref chref;
    chref = characterFromID("Dieke");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";
}

void OglAdd()
{
    ref chref;
    chref = characterFromID("Ogl");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";
}

////////////////////
//BlackThorn - ���������� ���
////////////////////
void HellSpawn(string qName)
{
	if (GetQuestPastDayParam("pchar.questTemp.HellSpawn") < 1  && GetCharacterEquipSuitID(pchar)!= "suit_1")
	{
		chrDisableReloadToLocation = true;
		for (int i = 1; i<15; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("HellSpawn"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 1, PIRATE, 1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
			
			ChangeCharacterAddressGroup(sld, pchar.HellSpawnLocation, "patrol", "patrol"+i);
			sld.LifeDay = 0;
			
			if (i == 1)
			{
				LAi_SetActorType(sld);
				LAi_type_actor_Reset(sld);
				LAi_ActorDialog(sld, pchar, "", 20.0, 0);
				sld.dialog.filename = "Quest\HellSpawn.c";
			}
			else
			{
				LAi_SetWarriorType(sld);
			}
		}
	}
	else
	{
		ref locationHS = &locations[reload_location_index];
		LocatorReloadEnterDisable(locationHS.id, "reload7_back", false);
	}
}
void HellSpawnFinish(string qName)
{
	chrDisableReloadToLocation = false;
	pchar.HellSpawnFinished = true;
}

void HellSpawnRitualFinish(string qName)
{
	chrDisableReloadToLocation = false;
	pchar.questTemp.HellSpawn.Rebirth = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
}

void HellSpawnRitual(string qName)
{
	if (GetQuestPastDayParam("pchar.questTemp.HellSpawn.Rit") < 10)
	{
		ref locationHSRitual = &locations[reload_location_index];
		chrDisableReloadToLocation = true;
		
		aref grp;
		makearef(grp, locationHSRitual.locators.monsters);
		pchar.Hellspawn.num = GetAttributesNum(grp)/4;
		for(int i = 1; i < sti(pchar.Hellspawn.num); i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("HellSpawnR"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 1, PIRATE, 1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
			ChangeCharacterAddressGroup(sld, locationHSRitual.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
			sld.LifeDay = 0;
			
			if (i == 1)
			{
				LAi_SetActorType(sld);
				LAi_type_actor_Reset(sld);
				LAi_ActorDialog(sld, pchar, "", 20.0, 0);
				sld.dialog.filename = "Quest\HellSpawn.c";
				sld.dialog.currentnode = "Ritual";
			}
			else
			{
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////
void RestoreBridgetown()
{
        ref rColony;
        Pchar.questTemp.CapBloodLine = false;
        Pchar.model="PGG_Blad_0"; // 21.03.09 Warship fix ���������� ������ ������
        //����������
        ref sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
        sld.Dialog.Filename = "Common_Mayor.c";
        sld.Dialog.CurrentNode = "First time";
        //�����
        int n = FindLocation("Bridgetown_town");  // �� ������ �������
        locations[n].reload.l3.close_for_night = true;
        locations[n].questSeekCap = 6;
        locations[n].houseEnc = true;
        //������� �����
        n = FindLocation("Bridgetown_tavern");
        locations[n].habitues = 1;
        DeleteAttribute(&locations[n], "notCloseCommonHouse");
        //������� �������
        ChangeBridgeTownDialogs(true);
        bDisableLandEncounters = false;
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        Pchar.questTemp.CapBUnarmed = false;
        //������� ��������
        //if (CheckAttribute(PChar, "GenQuestBox.CommonStoneHouse")) DeleteAttribute(PChar, "GenQuestBox.CommonStoneHouse");
        n = FindLocation("CommonStoneHouse");
        locations[n].models.day.locators = "StoneHouse_locators";
        locations[n].models.night.locators = "StoneHouse_Nlocators";
        //���������
        n = FindLocation("BridgeTown_Plantation");
       	locations[n].citizens = true;
    	locations[n].carrier = true;
    	//
    	SetLocationCapturedState("Bridgetown_town", false);
    	SetLocationCapturedState("BridgeTown_Plantation", false);
    	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", false);
    	LocatorReloadEnterDisable("BridgeTown_town", "reload1_back", false);
	    LocatorReloadEnterDisable("BridgeTown_fort", "reload2", false); //fix
	    
        LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//fix ��������� ��������� ����������
        LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
        LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
	    
    	//�������� �������
    	sld = characterFromID("Bridgetown_trader");
   	    LAi_RemoveLoginTime(sld);
    	for (int j = 0; j< MAX_COLONIES; j++)
		{
			ClearIslandShips(colonies[j].id);
			DeleteAttribute(&colonies[j],"AlreadyGen");
			GenerateIslandShips(colonies[j].island);
		}
		InitPsHeros();
        makeref(rColony, Colonies[FindColony("Bridgetown")]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //���������� �����
        RemoveShipFromBridgetown();
        //������ ��������
        LAi_group_Delete("EnemyFight");
        LAi_group_Delete("TmpEnemy");

        //���������� �����
        if (CheckAttribute(PChar, "quest.CureLordMovie")) Pchar.quest.CureLordMovie.over = "yes";
        if (CheckAttribute(PChar, "quest.DragunInvansion")) Pchar.quest.DragunInvansion.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLine_q1_1")) Pchar.quest.CapBloodLine_q1_1.over = "yes";
        if (CheckAttribute(PChar, "quest.onPlantation")) Pchar.quest.onPlantation.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodDetectBlades1")) Pchar.quest.CapBloodDetectBlades1.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodDetectBlades2")) Pchar.quest.CapBloodDetectBlades2.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLineTimer_1")) Pchar.quest.CapBloodLineTimer_1.over = "yes";
        if (CheckAttribute(PChar, "quest.CureMisStid")) Pchar.quest.CureMisStid.over = "yes";
        if (CheckAttribute(PChar, "quest.PrepareToEscape2")) Pchar.quest.PrepareToEscape2.over = "yes";
        if (CheckAttribute(PChar, "quest.PrepareToEscape3")) Pchar.quest.PrepareToEscape3.over = "yes";
        if (CheckAttribute(PChar, "quest.WinterwoodDuel")) Pchar.quest.WinterwoodDuel.over = "yes";
        if (CheckAttribute(PChar, "quest.MoneyForDieke")) Pchar.quest.MoneyForDieke.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLineTimer_2")) Pchar.quest.CapBloodLineTimer_2.over = "yes";
        if (CheckAttribute(PChar, "quest.QUsurer")) Pchar.quest.QUsurer.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape1")) Pchar.quest.CapBloodEscape1.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape2")) Pchar.quest.CapBloodEscape2.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape3")) Pchar.quest.CapBloodEscape3.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape4")) Pchar.quest.CapBloodEscape4.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape5")) Pchar.quest.CapBloodEscape5.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape6")) Pchar.quest.CapBloodEscape6.over = "yes";
        if (CheckAttribute(PChar, "quest.SolderTakeBladesDie")) Pchar.quest.SolderTakeBladesDie.over = "yes";
        LAi_group_RemoveCheck("EnemyFight");
        //������ �������
        CloseQuestHeader("FishermanQuest");
        CloseQuestHeader("UsurerQuest");
        CloseQuestHeader("PirateQuest");
		
		UnlockAchievement("CapBladLine", 3);

}

void Slavetrader_GetRandomShore()//����� �����
{	
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.Slavetrader.Island = "Terks";
			break;
		case 1:
			pchar.questTemp.Slavetrader.Island = "Caiman";
			break;
		case 2:
			pchar.questTemp.Slavetrader.Island = "Dominica";
			break;
		case 3:
			pchar.questTemp.Slavetrader.Island = "Bermudes";
			break;
	}
	pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
	while(pchar.questTemp.Slavetrader.Island.Shore == "")
	{
		pchar.questTemp.Slavetrader.Island = GetRandomIslandId();
		pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.Slavetrader.Island)) pchar.questTemp.Slavetrader.Island.Shore = "";//�� ����� ��� ����, ��� ����� � ���������
	} 
}

void Slavetrader_SlaveShipsOver(string qName)//������������ ������
{
	pchar.quest.Slavetrader_ShipsAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_ShoreShipsOver(string qName)//������������ ������ ������
{
	pchar.quest.Slavetrader_ShoreAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway_pinas";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_CreateSlaveShips(string qName)//�������� �������� � �����
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	ref sld;
	string Blade, sTemp;
			
	sTemp = pchar.questTemp.Slavetrader.ShipName;//��� �������
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Slave_Attack");//������� ������
	Group_SetType("Slave_Attack", "war");//��� ������
	// ==> �������������
	for (i=1; i<=2; i++)//��������� ����� ���������
	{
		Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
		if(makeint(pchar.rank) >= 20) { iShipRank = 4; }
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20) { iShipRank = rand(1)+2; }	
		if(makeint(pchar.rank) >= 7 && makeint(pchar.rank) < 13) { iShipRank = rand(1); }	
		if(makeint(pchar.rank) < 7) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_BRIG;     					
				Rank = 12 + rand(5);
                Blade = "blade15";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 		
			case 1:  
				ShipType = SHIP_BRIGANTINE;			
				Rank = 15 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 
			case 2: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 20 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 
			case 3: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 25 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 
			case 4: 
				ShipType = SHIP_LINESHIP; 						
				Rank = 30 + rand(5);
                Blade = "blade33";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;  				
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainSlaveAttack_"+i, "officer_"+(rand(63)+1), "man", "man", Rank, PIRATE, 3, true));//�������� ����
		if (i == 1)
		{
		FantomMakeCoolSailor(sld, ShipType, "", iCannonType, 70, 50, 50);//�������� ��������
		FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol2", 30);//�������� ������� ����
		}
		if (i == 2)
		{
		FantomMakeCoolSailor(sld, SHIP_GALEON_L, sTemp, CANNON_TYPE_CANNON_LBS24, 70, 50, 50); //�������� ��������
		FantomMakeCoolFighter(sld, Rank, 40, 40, "blade16", "pistol2", 30);//�������� ������� ����
		}
		
		Group_AddCharacter("Slave_Attack", "CaptainSlaveAttack_"+i);//���������� � ������
		sld.SuperShooter  = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterGoods(sld, GOOD_SLAVES, 700 + rand(100));//�������� � ���� �����
		
		sld.ship.Crew.Morale = 50;
		ChangeCrewExp(sld, "Sailors", 70);
		ChangeCrewExp(sld, "Cannoners", 70);
		ChangeCrewExp(sld, "Soldiers", 50);
    }
    // ==> ������������
	Group_SetGroupCommander("Slave_Attack", "CaptainSlaveAttack_1");
	Group_SetTaskAttack("Slave_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Slave_Attack", PLAYER_GROUP);
	Group_SetAddress("Slave_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Slave_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Slave_Attack";//����� ������ ����������
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_SlaveAttack_AfterBattle";//��� ������
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_SlaveAttack_DieHard";//��� ������
	
	AddQuestRecord("Slavetrader", "3_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
}

void Slavetrader_SlaveAttack_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Slave_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "4");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "died";//���� �� ������
}

void Slavetrader_SlaveAttack_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Slave_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "5");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";//���� �� ������
	ChangeOfficersLoyality("bad_all",1);
}


void Slavetrader_CreateShoreShips(string qName)//�������� ������ � �����
{
	int hcrew;
	ref sld;
	string sTemp, sNation;
	
	sNation = pchar.questTemp.Slavetrader.Nation;//�����
	sTemp = pchar.questTemp.Slavetrader.ShipName;//��� �������
	pchar.questTemp.Slavetrader = "TakeShoreCap";//����������� � ���������� ����	
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Shore_Attack");//������� ������
	Group_SetType("Shore_Attack", "war");//��� ������
	sld = GetCharacter(NPC_GenerateCharacter("Slaveshorecap", "trader_"+(rand(15)+1), "man", "man", 25, sNation, 3, true));//�������� ����
		sld.DontRansackCaptain = true; 
		FantomMakeCoolSailor(sld, SHIP_PINNACE, sTemp, CANNON_TYPE_CANNON_LBS24, 100, 80, 80);//�������� ��������
		sld.Ship.Mode = "trade";
		sld.Nation = sti(sNation);
		FantomMakeCoolFighter(sld, 30, 50, 50, "blade21", "pistol3", 50);//�������� ������� ����
		Group_AddCharacter("Shore_Attack", "Slaveshorecap");//���������� � ������
		sld.SuperShooter  = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "MusketsShoot");
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantityOverMax(sld, 1.5*hcrew);
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 70);
		ChangeCrewExp(sld, "Cannoners", 70);
		ChangeCrewExp(sld, "Soldiers", 100);
    // ==> ������������
	Group_SetGroupCommander("Shore_Attack", "Slaveshorecap");
	Group_SetTaskAttack("Shore_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Shore_Attack", PLAYER_GROUP);
	Group_SetAddress("Shore_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Shore_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Shore_Attack";//����� ������ ����������
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_ShoreAttack_AfterBattle";//��� ������
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_ShoreAttack_DieHard";//��� ������
	pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
}

void Slavetrader_ShoreAttack_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Shore_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","��"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "End_quest";
	CloseQuestHeader("Slavetrader");
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_ShoreAttack_AfterBattle(string qName)//������� �� ������
{
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
	Group_DeleteGroup("Shore_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	AddQuestRecord("Slavetrader", "12");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
	}
	else
	{
		characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "Slaveshorecap"; //������ ������, ���� ��������, ����� � �����, �������� �� ����
	}
}

void Slavetrader_BrigOver(string qName)//������� �� ������������ ������
{
	pchar.questTemp.Slavetrader_BrigAttack.over = "yes";//���������� ����������
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","��"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_CreateBrig(string qName)//�������� ����������
{
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	ref sld;
	string sTemp, sNation;
			
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, false);
    Group_FindOrCreateGroup("Brig_Attack");//������� ������
	Group_SetType("Brig_Attack", "war");//��� ������
	
		sTemp = pchar.questTemp.Slavetraderbrig.ShipName;//��� �������
		sNation = pchar.questTemp.Slavetrader.Nation;//����� �������
		sld = GetCharacter(NPC_GenerateCharacter("CapBrigAttack", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", 35, sNation, 3, true));//�������� ����
		FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, sTemp, CANNON_TYPE_CANNON_LBS24, 100, 100, 100);//�������� ��������
		FantomMakeCoolFighter(sld, 35, 90, 90, "blade26", "pistol3", 90);//�������� ������� ����
		Group_AddCharacter("Brig_Attack", "CapBrigAttack");//���������� � ������
		sld.SuperShooter  = true;
		sld.AlwaysEnemy = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		
		sld.ship.Crew.Morale = 80;
		ChangeCrewExp(sld, "Sailors", 80);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
 
    // ==> ������������
	Group_SetGroupCommander("Brig_Attack", "CapBrigAttack");
	Group_SetTaskAttack("Brig_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Brig_Attack", PLAYER_GROUP);
	Group_SetAddress("Brig_Attack", pchar.questTemp.Slavetraderbrig.Island, "", "");
	Group_LockTask("Brig_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Brig_Attack";//����� ������ ����������
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_BrigAttack_AfterBattle";//��� ������
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_BrigAttack_DieHard";//��� ������
}

void Slavetrader_BrigAttack_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Brig_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_BrigOver.over = "yes";
	if (CheckCharacterItem(pchar, "letter_1"))
	{
		AddQuestRecord("Slavetrader", "16");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "winbrig";//���� �� ������
	}
	else
	{
		AddQuestRecord("Slavetrader", "17");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","��"));
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "goodbye_1";//���� �� ������
	}
}

void Slavetrader_BrigAttack_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Brig_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_BrigShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","��"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";//���� �� ������
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_enterSoldiers() //�������������� �������
{	
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight"); 
	pchar.questTemp.Slavetrader = "After_enterSoldiers"; //��� ��������� ������, �������� ��� ��������� ����
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2; //��� ���� �� ���������
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SLSold"+i, "sold_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld); 
		//LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("SLOfficer", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true));
	FantomMakeCoolFighter(sld, 25, 100, 100, "topor2", "pistol3", 80);
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; //���������� ����, �� �������� �������� �����
	sld.dialog.currentnode = "Slave_arest"; // ���������� ����
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}
void Slavetrader_Bonanza(string qName)//c������� �������� 
{
	chrDisableReloadToLocation = true;
    for (i=1; i<=8; i++)
    {
		if (i == 2 || i == 4 || i == 6 || i == 8)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Indian"+i, "indsar1", "man", "man", 25, PIRATE, 0, true));                    
            FantomMakeCoolFighter(sld, 25, 80, 100, "topor2", "pistol3", 100);
		}	
		else
        {
			sld = GetCharacter(NPC_GenerateCharacter("Indian"+i, "indsair2", "man", "man", 35, PIRATE, 0, true));
		}
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
               	ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
    }
	sld = GetCharacter(NPC_GenerateCharacter("Nabuki", "mummy", "man", "man", 25, PIRATE, 0, true));
    sld.name 	= "������";
    sld.lastname = "��������";
		FantomMakeCoolFighter(sld, 60, 100, 100, "toporAZ", "pistol4", 100);
                TakeNItems(sld, "jewelry2", 120+rand(80));
				TakeNItems(sld, "jewelry3", 120+rand(60));
				TakeNItems(sld, "jewelry4", 140+rand(50));
				TakeNItems(sld, "jewelry15", rand(50));
	TakeNItems(sld, "indian11", 1);
	sld.SaveItemsForDead = true; // ��������� �� ����� ����
	sld.DontClearDead = true;
					sld.cirassId = Items_FindItemIdx("cirass5"); 
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
               	ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
					
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
}

void Slavetrader_GetHispanShore()//����������� �����, �� ������� ������ ������
{
	pchar.questTemp.Slavetrader.Island = "Caracas";
	pchar.questTemp.Slavetrader.Island.Shore = "Shore21";
	pchar.questTemp.SlavetraderAreal.add = "�� ��������";
	while(pchar.questTemp.Slavetrader.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.questTemp.Slavetrader.Island = "Cumana";
		pchar.questTemp.Slavetrader.Island.Shore = "Shore19";
		pchar.questTemp.SlavetraderAreal.add = "�� ������";
	}
}

void Slavetrader_SlaveHalleon_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("SlaveGalleon");
	pchar.quest.Slavetrader_SlaveGalleonOver.over = "yes";
	AddQuestRecord("Slavetrader", "19");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	ChangeCharacterReputation(pchar, -5);
	pchar.questTemp.Slavetrader = "wingalleon";//���� �� ������
}

void Slavetrader_SlaveGalleonOver(string qName)//������������ ������
{
	pchar.quest.Slavetrader_SlaveGalleon.over = "yes";
	AddQuestRecord("Slavetrader", "7_2");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "lostgalleon";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_RatCorvette(string qName)//�������� ������� �����
{
	ref sld;
	string sTemp;
			
    Island_SetReloadEnableGlobal("Tortuga", false);
    Group_FindOrCreateGroup("Rat_Attack");//������� ������
	Group_SetType("Rat_Attack", "war");//��� ������
	
		sTemp = pchar.questTemp.Slavetrader.ShipName;//��� �������
		sld = GetCharacter(NPC_GenerateCharacter("RatCap", "officer_16", "man", "man", 35, FRANCE, 3, true));//�������� ����
		sld.name = "�������";
		sld.lastname = "�������";
		FantomMakeCoolSailor(sld, SHIP_CORVETTE, sTemp, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);//�������� ��������
		FantomMakeCoolFighter(sld, 35, 80, 80, "blade26", "pistol5", 90);//�������� ������� ����
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Ship.Mode = "pirate";
		Group_AddCharacter("Rat_Attack", "RatCap");//���������� � ������
		sld.SuperShooter  = true;
		sld.AlwaysEnemy = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
 
    // ==> ������������
	Group_SetGroupCommander("Rat_Attack", "RatCap");
	Group_SetTaskAttack("Rat_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Rat_Attack", PLAYER_GROUP);
	Group_SetAddress("Rat_Attack", "Tortuga", "", "");
	Group_LockTask("Rat_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Rat_Attack";//����� ������ ����������
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_RatAttack_AfterBattle";//��� ������
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_RatAttack_DieHard";//��� ������
	pchar.quest.Slavetrader_RatCorvetteOver.over = "yes";
}

void Slavetrader_RatAttack_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Rat_Attack");
	Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	AddQuestRecord("Slavetrader", "21_12");
	pchar.questTemp.Slavetrader = "wincorvette";//���� �� ������
}

void Slavetrader_RatAttack_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Rat_Attack");
    Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "21_11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("����","�����"));
	pchar.questTemp.Slavetrader = "lostcorvette";//���� �� ������
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_RatCorvetteOver(string qName)//������������ ������ �������
{
	pchar.quest.Slavetrader_RatAttack.over = "yes";
	AddQuestRecord("Slavetrader", "21_10");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	pchar.questTemp.Slavetrader = "lostcorvette";
	ChangeOfficersLoyality("bad_all", 1);
}


void Slavetrader_GetEscapeShore()//�������� ����, ���� ������ ����� �������
{
	switch (rand(9))
	{
		case 0:
			pchar.questTemp.Slavetrader.EsIsland = "Barbados";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak2";
			pchar.questTemp.SlavetraderAreal.add = "� ������� ���������";
			break;
		case 1:
			pchar.questTemp.Slavetrader.EsIsland = "Guadeloupe";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak4";
			pchar.questTemp.SlavetraderAreal.add = "� ������� ���������";
			break;
		case 2:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak9";
			pchar.questTemp.SlavetraderAreal.add = "�������� �� ��������";
			break;
		case 3:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak10";
			pchar.questTemp.SlavetraderAreal.add = "�������� �� ������";
			break;
		case 4:
			pchar.questTemp.Slavetrader.EsIsland = "Tortuga";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak6";
			pchar.questTemp.SlavetraderAreal.add = "� ������� �������";
			break;
		case 5:
			pchar.questTemp.Slavetrader.EsIsland = "Trinidad";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak1";
			pchar.questTemp.SlavetraderAreal.add = "� ������� ���������";
			break;
		case 6:
			pchar.questTemp.Slavetrader.EsIsland = "Nevis";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak5";
			pchar.questTemp.SlavetraderAreal.add = "� ������� ������";
			break;
		case 7:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak8";
			pchar.questTemp.SlavetraderAreal.add = "�������� �� �����-�������";
			break;
		case 8:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak7";
			pchar.questTemp.SlavetraderAreal.add = "�������� �� ����-�-������";
			break;
		case 9:
			pchar.questTemp.Slavetrader.EsIsland = "Cartahena";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak11";
			pchar.questTemp.SlavetraderAreal.add = "�������� �� ���������";
			break;
	}
}

void Slavetrader_EscapeSlaveInShore(string qName)
{
	string sShore;
	sShore = pchar.questTemp.Slavetrader.Island.Shore
    LAi_group_Delete("EnemyFight"); 
	chrDisableReloadToLocation = true; //������� �������
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//����
    for (i=1; i<=3; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnCrew_"+i, "pirate_"+(rand(23)+2), "man", "man", iTemp, sti(pchar.nation), 0, true));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, sShore, "goto", sTemp);
    }
	//�����
	for (i=21; i<=27; i++)
    {
		iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
		sld = GetCharacter(NPC_GenerateCharacter("EscapeSlave_"+i, "Pirate_1", "man", "man", iTemp, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, sShore, "goto", "goto"+i);
    }
			sld = GetCharacter(NPC_GenerateCharacter("Jimmy", "capitan_3", "man", "man", 35, PIRATE, 0, true));
			sld.name 	= "�������";
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 35, 100, 100, "topor2", "pistol3", 80);
			sld.SaveItemsForDead = true; // ��������� �� ����� ����
			sld.cirassId = Items_FindItemIdx("cirass3");
			sld.DontClearDead = true;
			sld.HeroModel = "capitan_3,capitan_3_1,capitan_3_2,capitan_3_3,capitan_3_4,capitan_3_5";
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");
    GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, sShore, "goto", "goto30");
		
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Slavetrader_EscapeSlaves_Win");
}

void Slavetrader_Slavewoman()
{
		  sld = characterFromId("Slavewoman");	
	      LAi_SetPlayerType(pchar);
          SetCharacterRemovable(sld, false);
          LAi_SetActorType(sld);
		  LAi_ActorRunToLocation(sld, "goto", "goto2", "none", "", "", "", 15.0);
		  sld.lifeday = 0;
		  for (i=10; i<=25; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SlaveShor_"+i, "Pirate_1", "man", "man", 10, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 25, 100, 100, "", "", 80);
				ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto"+i);
				sld = characterFromID("SlaveShor_"+i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				LAi_SetCitizenTypeNoGroup(sld);
				sld.lifeday = 0;//�� ������ ������
				LAi_CharacterDisableDialog(sld);
			}
		  SetCharacterGoods(pchar, GOOD_SLAVES, 1000 + rand(100));
		  sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
		  AddQuestRecord("Slavetrader", "22");
		  AddQuestUserData("Slavetrader", "sQty", sTemp);
		  pchar.questTemp.Slavetrader = "escapeslave_win";
		  ChangeCharacterReputation(pchar, -1);
		  OfficersReaction("bad");
}

void Slavetrader_CreateLineShips(string qName)//�������� �������� ��������
{
	int i;
	ref sld;
	string sTemp;

	Island_SetReloadEnableGlobal("Cuba2", false);
    Group_FindOrCreateGroup("Havana_Attack");//������� ������
	Group_SetType("Havana_Attack", "war");//��� ������
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);//������ �� � ��������
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("HavanaAttack_"+i, "off_spa_1", "man", "man", 35, SPAIN, 3, true));//�������� ����
		FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);//�������� ��������
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//�������� ������� ����
		Group_AddCharacter("Havana_Attack", "HavanaAttack_"+i);//���������� � ������
		sld.SuperShooter  = true;
		sld.AlwaysEnemy = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
    }
    // ==> ������������
	Group_SetGroupCommander("Havana_Attack", "HavanaAttack_1");
	Group_SetTaskAttack("Havana_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Havana_Attack", PLAYER_GROUP);
	Group_SetAddress("Havana_Attack", "Cuba2", "", "");
	Group_LockTask("Havana_Attack");
	bQuestDisableMapEnter = true; //��������� ����� �� �����, ���� �� ����� ���� �� ����������	
    // ==> ���������� �� ������� �������
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Havana_Attack";//����� ������ ����������
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_HavanaAttack_AfterBattle";//��� ������
	pchar.quest.Slavetrader_DieHardHavana.win_condition.l1 = "MapEnter";//�� ���� �� �����
    pchar.quest.Slavetrader_DieHardHavana.function = "Slavetrader_HavanaAttack_DieHard";//������ ����� �� ����
	AddQuestRecord("Slavetrader", "25");
}

void Slavetrader_HavanaAttack_AfterBattle(string qName)//������� �� ������
{
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("Havana_Attack");
	Island_SetReloadEnableGlobal("Cuba2", true);
	AddQuestRecord("Slavetrader", "26");
}

void Slavetrader_HavanaAttack_DieHard(string qName)//���� ������� ����������
{
	pchar.quest.Slavetrader_HavanaOver.over = "yes";//������ ������
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";//������ ���� ������
	AddQuestRecord("Slavetrader", "26_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_HavanaOver(string qName)//������������ ������
{
	pchar.quest.Slavetrader_HavanaAttack.over = "yes";
	AddQuestRecord("Slavetrader", "28");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","��"));
	ChangeOfficersLoyality("bad_all", 1);
	CloseQuestHeader("Slavetrader");
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_FiveTSlavesOver(string qName)//������������ ������
{
	ChangeCharacterHunterScore(pchar, "spahunter", 100);
	ChangeCharacterHunterScore(pchar, "holhunter", 100);
	ChangeCharacterHunterScore(pchar, "frahunter", 100);
	ChangeCharacterHunterScore(pchar, "enghunter", 100);
	pchar.questTemp.Slavetrader = "End_quest_bad";
	AddQuestRecord("Slavetrader", "30");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Slavetrader");
}

void Slavetrader_HavanaSeekOver(string qName)//������������ ������
{
	ChangeCharacterHunterScore(pchar, "spahunter", 100);
	ChangeCharacterHunterScore(pchar, "holhunter", 100);
	ChangeCharacterHunterScore(pchar, "frahunter", 100);
	ChangeCharacterHunterScore(pchar, "enghunter", 100);
	pchar.questTemp.Slavetrader = "End_quest_bad";
	AddQuestRecord("Slavetrader", "31");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Slavetrader");
}

void Slavetrader_UsurerEscape(string qName)//������ ������ ����������
{
	sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
	sld.name = "����";
	sld.lastname = "�������";
	sld.model = "trader_8";
	LocatorReloadEnterDisable(pchar.questTemp.Slavetrader.Cityname, "reload8_back", false);
}

//-->������, ������ ��������
void Deliver_CreateTraderShips(string qName)//�������� �������� ��������
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iGoods, iSpace;
	ref sld;
	string sTemp1, sTemp2, sNation;
			
	sTemp1 = pchar.questTemp.jailCanMove.Deliver.ShipName1;//��� �������
	sTemp2 = pchar.questTemp.jailCanMove.Deliver.ShipName2;//��� �������
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Trade_Attack");//������� ������
	Group_SetType("Trade_Attack", "trade");//��� ������
	for (i=1; i<=2; i++)
	{
		if(makeint(pchar.rank) >= 20) { iShipRank = 3; }
		if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 20) { iShipRank = rand(1)+2; }	
		if(makeint(pchar.rank) >= 10 && makeint(pchar.rank) < 15) { iShipRank = rand(1)+1; }	
		if(makeint(pchar.rank) >= 4 && makeint(pchar.rank) < 10) { iShipRank = rand(1); }	
		if(makeint(pchar.rank) < 4) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_BARQUE;     					
				Rank = 12 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 1:  
				ShipType = SHIP_FLEUT;			
				Rank = 18 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 
			case 2: 
				ShipType = SHIP_PINNACE; 				
				Rank = 25 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 
			case 3: 
				ShipType = SHIP_GALEON_H;         			
				Rank = 30 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 			
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, sNation, 3, true));//�������� ����
		if (i == 1)
		{
		FantomMakeCoolSailor(sld, ShipType, sTemp1, iCannonType, 48, 35, 35);//�������� ��������
		}
		if (i == 2)
		{
		FantomMakeCoolSailor(sld, ShipType, sTemp2, iCannonType, 44, 30, 30);//�������� ��������
		}
		sld.Ship.Mode = "trade";
		iGoods = sti(pchar.questTemp.jailCanMove.Deliver.Goods);
		iSpace = GetCharacterFreeSpace(sld, iGoods);
		iSpace = makeint(iSpace/2 + rand(iSpace/2));
		SetCharacterGoods(sld, iGoods, iSpace);
		Group_AddCharacter("Trade_Attack", "CaptainAttack_"+i);//���������� � ������
		sld.AlwaysEnemy = true;
		sld.ship.Crew.Morale = 60;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 100);
    }
    // ==> ������������
	Group_SetGroupCommander("Trade_Attack", "CaptainAttack_1");
	Group_SetTaskAttack("Trade_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Trade_Attack", PLAYER_GROUP);
	Group_SetAddress("Trade_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Trade_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1.group = "Trade_Attack";//����� ������ ����������
	pchar.quest.jailCanMoveDeliver_AfterBattle.function = "Deliver_AfterBattle";//��� ������
	pchar.quest.jailCanMoveDeliver_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.jailCanMoveDeliver_DieHard.function = "Deliver_DieHard";//��� ������
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "13_1");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
}

void Deliver_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHard.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void Deliver_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Trade_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattle.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void Deliver_TraderShipsOver(string qName)//������������ ������ �������� �������� � �������� - 2 � 1
{
	pchar.quest.jailCanMoveDeliver_ShipsAttack.over = "yes";
	AddQuestRecord("GivePrisonFree", "13_2");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--������, ������ ��������

//-->������, �������� �������
void Deliver_CreateCureerShips(string qName)//�������� ����������� �������
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iNation = sti(pchar.questTemp.jailCanMove.Deliver.Nation);
	ref sld;
	string Blade, sTemp, sNation;
	
	sTemp = pchar.questTemp.jailCanMove.Deliver.ShipName;//��� �������
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Cureer_Attack");//������� ������
	Group_SetType("Cureer_Attack", "war");//��� ������
		if(makeint(pchar.rank) >= 20) { iShipRank = 3; }
		if(makeint(pchar.rank) >= 12 && makeint(pchar.rank) < 20) { iShipRank = 2; }	
		if(makeint(pchar.rank) >= 5 && makeint(pchar.rank) < 12) { iShipRank = 1; }	
		if(makeint(pchar.rank) < 5) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_SCHOONER;     					
				Rank = 12 + rand(5);
                Blade = "blade15";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 		
			case 1:  
				ShipType = SHIP_BRIGANTINE;			
				Rank = 17 + rand(5);
                Blade = "blade34";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 
			case 2: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 22 + rand(5);
                Blade = "blade26";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 
			case 3: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 30 + rand(5);
                Blade = "blade28";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 			
		}
		sld = GetCharacter(NPC_GenerateCharacter("CureerAttack", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", Rank, sNation, 3, true));//�������� ����
		FantomMakeCoolSailor(sld, ShipType, sTemp, iCannonType, 75, 50, 50);//�������� ��������
		FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol3", 40);//�������� ������� ����
		Group_AddCharacter("Cureer_Attack", "CureerAttack");//���������� � ������
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "MusketsShoot");
		sld.AlwaysEnemy = true;
  
    // ==> ������������
	Group_SetGroupCommander("Cureer_Attack", "CureerAttack");
	Group_SetTaskAttack("Cureer_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Cureer_Attack", PLAYER_GROUP);
	Group_SetAddress("Cureer_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Cureer_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1.group = "Cureer_Attack";//����� ������ ����������
	pchar.quest.jailCanMoveDeliver_AfterBattleC.function = "DeliverC_AfterBattle";//��� ������
	pchar.quest.jailCanMoveDeliver_DieHardC.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.jailCanMoveDeliver_DieHardC.function = "DeliverC_DieHard";//��� ������
	pchar.quest.Deliver_CureerShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "14_1");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
}

void DeliverC_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Cureer_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHardC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void DeliverC_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Cureer_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattleC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void Deliver_CureerShipsOver(string qName)//������������ ������ ����������� �������
{
	pchar.quest.jailCanMoveDeliver_ShipsCAttack.over = "yes";
	AddQuestRecord("GivePrisonFree", "14_2");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","�"));
	AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--������, �������� �������

//-->������, ��������
void Deliver_lay(string qName)//������ - � ���� ������
{
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "15");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("","�"));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--������, ��������

/* Nathaniel (12.03.21): ������������ ����� "������ �������" ------------------------------------ */
void Findship_Over(string qName)//���������� ����� ������� �� �����
{
	AddQuestRecord("Findship", "2");
	CloseQuestHeader("Findship");
	DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
}
/* ---------------------------------------------------------------------------------------------- */
//zagolski - ����� �������
void mOfficer_fc(string qName)
{
	if (IsEntity(worldMap))
    	{
		ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog("������ " + GetFullName(sld) + " ������ � �������� " + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
		Log_SetStringToLog("������ " + GetFullName(sld) + " ������ � ������� " + pchar.ship.name + "");

		if (GetCrewQuantity(pchar) > 0)
		{
			AddCharacterExpToSkill(PChar, "Leadership", 200);
			MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
		
        }
	else
        {
            	pchar.quest.mOfficer_fc2.win_condition.l1 = "MapEnter";
		pchar.quest.mOfficer_fc2.function    = "mOfficer_fc2";
        }
}

void mOfficer_fc2(string qName)
{
	ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog("������ " + GetFullName(sld) + " ������ � �������� " + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
	Log_SetStringToLog("������ " + GetFullName(sld) + " ������ � ������� " + pchar.ship.name + "");

        if (GetCrewQuantity(pchar) > 0)
	{
		AddCharacterExpToSkill(PChar, "Leadership", 200);
		MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
}

//zagolski. ����� � ����� �� ������ �����
void sharp_pre(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");


    	for (i=1; i<=5; i++)
    	{
		sld = GetCharacter(NPC_GenerateCharacter("sh_pre_"+i, "pirate_"+i, "man", "man", 15, PIRATE, 0, true));
		FantomMakeCoolFighter(sld, 15, 70, 70, RandPhraseSimple("blade21","blade31"), RandPhraseSimple("pistol3", "pistol6"), 20);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "Shore9", "goto", "goto4");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	}
}

// zagolski - ������� ����
void zpq_sld1_fc(string qName)
{
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(loadedLocation, true);

    	for (i=1; i<=3; i++)
    	{
		sld = GetCharacter(NPC_GenerateCharacter("qp2_"+i, "pirate_"+i, "man", "man", 20, PIRATE, 0, true));
		sld.Dialog.Filename = "Quest\zpq_dialog.c";
		sld.dialog.currentnode = "zpq_sld2";
		sld.greeting = "Enc_Waiker";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "Cumana_ExitTown", "goto", "goto5");
		if (i == 1)
		{
			FantomMakeCoolFighter(sld, 20, 90, 90, "blade31", "pistol6", 50);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			sld.cirassId = Items_FindItemIdx("cirass2");
			GiveItem2Character(sld, "jewelry4");
			AddMoneyToCharacter(sld, 1000+rand(1000));
			sld.SaveItemsForDead  = true;
			sld.DontClearDead = true;
			if (GetCharacterItem(pchar, "map_full") == 0)
			{
				if (GetCharacterItem(pchar, "map_part1") == 0) GiveItem2Character(sld, "map_part1");
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0) GiveItem2Character(sld, "map_part2");
				}
			}
			else GiveItem2Character(sld, "map_normal");
		}
		else
		{
			FantomMakeCoolFighter(sld, 15, 55, 55, "blade7", "pistol3", 20);
			LAi_ActorFollow(sld, characterFromId("qp2_1"), "", -1);
		}
	}		
}

void zpq_seaBattle(string qName)
{
	LAi_group_Delete("EnemyFight");
	sld = GetCharacter(NPC_GenerateCharacter("zpqCaptain", "Lil_Jim_0", "man", "man", 40, PIRATE, 1, true));
	FantomMakeCoolFighter(sld, 40, 105, 105, "blade23", "pistol3", 200);
	FantomMakeCoolSailor(sld, SHIP_LUGGERQUEST, "���������", CANNON_TYPE_CANNON_LBS24, 105, 105, 105);
    sld.name 	= "���������";
    sld.lastname = "������";
	sld.id		= "zpqCaptain";
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.HeroModel = "Lil_Jim_0,Lil_Jim_1,Lil_Jim_2,Lil_Jim_3,Lil_Jim_4,Lil_Jim_5";
	SetCharacterPerk(sld, "MusketsShoot");

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	AddItems(sld, "talisman3", 1);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_group_MoveCharacter(sld, "EnemyFight");
	Group_AddCharacter("zpq_Group", "zpqCaptain");			
	Group_SetType("zpq_Group", "Pirate");
	Group_SetGroupCommander("zpq_Group", "zpqCaptain");
	Group_SetAddress("zpq_Group", "Cumana", "quest_ships", "quest_ship_4");
	Group_SetTaskAttack("zpq_Group", PLAYER_GROUP);
	Group_LockTask("zpq_Group");
}

//zagolski. ��������� ����� ������
void pirateStartQuest_Smuggler_fc(string qName)
{
	if (sti(pchar.rank)<5 && sti(pchar.Nation) == PIRATE)
	{
	AddQuestRecord("pSQ", "4");
	chrDisableReloadToLocation = true;
	int iRank = makeint(sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2);

    	for (i=1; i<=3; i++)
    	{
		sld = GetCharacter(NPC_GenerateCharacter("psq1_"+i, "sold_"+NationShortName(sti(pchar.questTemp.pirateStartQuest.City2Nation))+"_"+(rand(4)+1), "man", "man", iRank, sti(pchar.questTemp.pirateStartQuest.City2Nation), 0, true));
		SetFantomParamFromRank(sld, iRank, true);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "pirateStartQuest_Smuggler_group");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.pirateStartQuest.City2 +"_ExitTown", "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	}
	LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("pirateStartQuest_Smuggler_group", "OpenTheDoors");
	}
}

void pirateStartQuest_Smuggler_fc2(string qName)
{
    	LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	int iRank = makeint(sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2);

    	for (i=1; i<=3; i++)
    	{
		sld = GetCharacter(NPC_GenerateCharacter("psq2_"+i, "pirate_"+i, "man", "man", iRank, PIRATE, -1, true));
		SetFantomParamFromRank(sld, iRank, true);
		sld.Dialog.Filename = "Quest\pSQ_Smuggler_dialog.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "Gr_Smuggler_OnShore";
		LAi_SetImmortal(sld, true);
		LAi_SetGuardianType(sld);
		LAi_group_MoveCharacter(sld, "pirateStartQuest_Smuggler_group");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.pirateStartQuest.Shore, "Smugglers", "Smuggler0" + i);
	}
}

void pirateStartQuest_Lether_fc(string qName)
{
	if (GetCharacterItem(pchar, "letter_open") == 0)
	{
		GiveItem2Character(pchar, "letter_open");
		ChangeItemDescribe("letter_open", "itmdescr_letter_open_pirateStartQuest");
	}
	AddQuestRecord("pSQ", "6");
	AddQuestUserData("pSQ", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
	SetTimerFunction("pirateStartQuest_Bahus_fc", 0, 0, 1);
}

void pirateStartQuest_Bahus_fc(string qName)
{
	pchar.quest.pirateStartQuest_Bahus_seaBattle.win_condition.l1 = "location";
	pchar.quest.pirateStartQuest_Bahus_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
	pchar.quest.pirateStartQuest_Bahus_seaBattle.function = "pirateStartQuest_Bahus_seaBattle";
}

void pirateStartQuest_Bahus_seaBattle(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("pSQB_Captain", "pirate_3", "man", "man", 6, PIRATE, 1, true));
	FantomMakeCoolFighter(sld, 6, 30, 30, "blade6", "pistol1", 30);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "�����", CANNON_TYPE_CANNON_LBS12, 50, 30, 30);
        sld.name 	= "��������";
        sld.lastname = "��������";
	SetCharacterGoods(sld, GOOD_SLAVES, 300);
	SetCrewQuantity(sld, 129);
	sld.ship.Crew.Morale = 20;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 30);
	ChangeCrewExp(sld, "Soldiers", 20);

	Group_AddCharacter("pSQB_Group", "pSQB_Captain");			
	Group_SetType("pSQB_Group", "Pirate");
	Group_SetGroupCommander("pSQB_Group", "pSQB_Captain");
	Group_SetAddress("pSQB_Group", pchar.questTemp.pirateStartQuest.Areal, "quest_ships", "quest_ship_"+(1+rand(2)));
	Group_LockTask("pSQB_Group");
}

void pirateStartQuest_seaBattle(string qName)
{
	LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

	sld = GetCharacter(NPC_GenerateCharacter("pSQ_Captain", "pirate_6", "man", "man", 8, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 8, 40, 40, "blade9", "pistol3", 40);
	FantomMakeCoolSailor(sld, SHIP_LUGGER, "�������", CANNON_TYPE_CANNON_LBS16, 40, 40, 40);
        sld.name 	= "������";
        sld.lastname = "����";
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	//SetCharacterPerk(sld, "MusketsShoot");

	sld.ship.Crew.Morale = 50;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	GiveItem2Character(sld, "cirass1");
	GiveItem2Character(sld, "jewelry9");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	LAi_group_MoveCharacter(sld, "pirateStartQuest_Smuggler_group");
	Group_AddCharacter("pSQ_Group", "pSQ_Captain");			
	Group_SetType("pSQ_Group", "Pirate");
	Group_SetGroupCommander("pSQ_Group", "pSQ_Captain");
	Group_SetAddress("pSQ_Group", pchar.questTemp.pirateStartQuest.Areal, "quest_ships", "quest_ship_4");
	Group_SetTaskAttack("pSQ_Group", PLAYER_GROUP);
	Group_LockTask("pSQ_Group");

	pchar.quest.pirateStartQuest_seaBattle_over.win_condition.l1 = "NPC_Death";
	pchar.quest.pirateStartQuest_seaBattle_over.win_condition.l1.character = "pSQ_Captain";
	pchar.quest.pirateStartQuest_seaBattle_over.function = "pirateStartQuest_seaBattle_over";
}

void pirateStartQuest_seaBattle_over(string qName)
{
	pchar.questTemp.pirateStartQuest = "5";
	AddQuestRecord("pSQ", "8");
	AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
}

//--> ���, ������ ������
void SelectCarlosCity() //�������� �����
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.Headhunter.City = "Bridgetown";
			pchar.questTemp.Headhunter.Cityname = "����������";
			break;
		case 1:
			pchar.questTemp.Headhunter.City = "Charles";
			pchar.questTemp.Headhunter.Cityname = "�����������";
			break;
		case 2:
			pchar.questTemp.Headhunter.City = "Tortuga";
			pchar.questTemp.Headhunter.Cityname = "�������";
			break;
		case 3:
			pchar.questTemp.Headhunter.City = "Santodomingo";
			pchar.questTemp.Headhunter.Cityname = "�����-�������";
			break;
		case 4:
			pchar.questTemp.Headhunter.City = "Panama";
			pchar.questTemp.Headhunter.Cityname = "������";
			break;
		case 5:
			pchar.questTemp.Headhunter.City = "Portroyal";
			pchar.questTemp.Headhunter.Cityname = "����-�����";
			break;
		case 6:
			pchar.questTemp.Headhunter.City = "Marigo";
			pchar.questTemp.Headhunter.Cityname = "������";
			break;
	}
}

void CreateCarlos()//������� �������
{
    ref sld, ch;
	sld = GetCharacter(NPC_GenerateCharacter("Carlos", "ozg_carlos", "man", "man", 20, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "������";
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Carlos";
    sld.greeting = "pirat_common";
	sld.HeroModel = "ozg_carlos,ozg_carlos_1,ozg_carlos_2,ozg_carlos_3,ozg_carlos_4,ozg_carlos_5";
    FantomMakeCoolFighter(sld, 20, 70, 70, "blade21", "pistol3", 50);
    sld.DontClearDead = true;
    LAi_SetCitizenType(sld);
    
    if(pchar.questTemp.Headhunter.Chance == 1)
    {
   	    LAi_SetSitTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_tavern", "sit","sit2");
    }
    else
    {
   	    LAi_SetStayTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_Brothel_room", "goto","goto3");
        
		ch = GetCharacter(NPC_GenerateCharacter("Qhorse", "horse05", "woman", "towngirl", 10, ENGLAND, 1, false));
        LAi_SetActorTypeNoGroup(ch);
		ChangeCharacterAddressGroup(ch, pchar.questTemp.Headhunter.City + "_Brothel_room", "goto","goto1");
        int n = FindLocation(pchar.questTemp.Headhunter.City + "_Brothel");
        locations[n].reload.l2.disable = false;
    }
}

void CarlosDuel(string qName)
{
	pchar.quest.CarlosPlace.win_condition.l1 = "Location";
	pchar.quest.CarlosPlace.win_condition.l1.location = pchar.questTemp.Headhunter.City + "_ExitTown";
	pchar.quest.CarlosPlace.function = "CarlosPlace";
}

void CarlosDuelOver(string qName)//�� ������ �� �������
{
	pchar.quest.CarlosPlace.over = "yes";
	LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", false);//�������� �������
	locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = false; //��������� �������
	sld = characterFromId("Carlos");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "2_2");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","��"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void CarlosPlace(string qName)
{
	pchar.quest.CarlosDuelOver.over = "yes";
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight"); 
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5; //��� ���� �� ���������
	for (i=2; i<=4; i++)
    {
		if (i == 4)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Carloshelper_"+i, "mushketer_1", "man", "mushketer", iTemp, PIRATE, -1, true));                    
            FantomMakeCoolFighter(sld, iTemp, 20, 20, "", "mushket", 50);
		}	
		else
        {
			sld = GetCharacter(NPC_GenerateCharacter("Carloshelper_"+i, "Pirate_"+i, "man", "man", iTemp, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, iTemp, 40, 40, "blade16", "pistol2", 50);  
		}
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_ExitTown", "goto", "goto6");
    }
    sld = characterFromID("Carlos");
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; //���������� ����, �� �������� �������� �����
	sld.dialog.currentnode = "talk_off_town_Carlos"; // ���������� ����
	if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); // ���� �� ���� ������ � ������
		DeleteAttribute(sld, "CityType");
	}
	ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_ExitTown", "goto", "goto1");
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    LAi_ActorTurnToCharacter(sld, pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}
//<-- ���, ������ ������

void SelectHoumCity()//������� ������� ��� �����
{
	switch (sti(pchar.questTemp.Headhunter.Chance))
	{
		case 0:
			pchar.questTemp.Headhunter.City = "Bridgetown";
			pchar.questTemp.Headhunter.Cityname = "����������";
			pchar.questTemp.Headhunter.Island = "Barbados";
		break;
		case 1:
			pchar.questTemp.Headhunter.City = "Charles";
			pchar.questTemp.Headhunter.Cityname = "�����������";
			pchar.questTemp.Headhunter.Island = "Nevis";
		break;
		case 2:
			pchar.questTemp.Headhunter.City = "Sentjons";
			pchar.questTemp.Headhunter.Cityname = "����-������";
			pchar.questTemp.Headhunter.Island = "Antigua";
		break;
		case 3:
			pchar.questTemp.Headhunter.City = "Portspein";
			pchar.questTemp.Headhunter.Cityname = "����-��-������";
			pchar.questTemp.Headhunter.Island = "Trinidad";
		break;
		case 4:
			pchar.questTemp.Headhunter.City = "Portroyal";
			pchar.questTemp.Headhunter.Cityname = "����-�����";
			pchar.questTemp.Headhunter.Island = "Jamaica";
		break;
	}
}

void CreateHoum()//�������� �����
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Houm", "ozg_horn", "man", "man", 25, ENGLAND, -1, false));
	FantomMakeCoolFighter(sld, 25, 50, 50, "blade19", "pistol6", 70);
	FantomMakeCoolSailor(sld, SHIP_GALEON_H, "������� ������", CANNON_TYPE_CANNON_LBS32, 70, 70, 70);
	sld.name = "��������";
	sld.lastname = "����";
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Houm";
    sld.greeting = "Gr_HeadPirates";
	sld.Ship.Mode = "pirate";
    DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
    sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.AlwaysEnemy = true;
	sld.HeroModel = "ozg_horn,ozg_horn_1,ozg_horn_2,ozg_horn_3,ozg_horn_4,ozg_horn_5";
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterGoods(sld, GOOD_SILVER, 556);//�������� � ���� �������
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	sld.ship.Crew.Morale = 70;
	ChangeCrewExp(sld, "Sailors", 70);
	ChangeCrewExp(sld, "Cannoners", 70);
	ChangeCrewExp(sld, "Soldiers", 70);
    
    if(pchar.questTemp.Headhunter.Chance1 == 0)
    {
   	    LAi_SetSitTypeNoGroup(sld);
		FreeSitLocator(pchar.questTemp.Headhunter.City + "_tavern", "sit1");
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_tavern", "sit", "sit1");
    }
    else
    {
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_town", "quest", "quest1");
    }
}

void Headhunter_CreateHoumShips(string qName)//c������� �������� �����
{
	ref sld;
    Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, false);
    Group_FindOrCreateGroup("Houm_Attack");//������� ������
	Group_SetType("Houm_Attack", "war");//��� ������
	
		sld = CharacterFromID("Houm");
		LAi_SetImmortal(sld, false);
		Group_AddCharacter("Houm_Attack", "Houm");//������� ����� � ������
		
		sld = GetCharacter(NPC_GenerateCharacter("Houm_helper", "pirate_1", "man", "man", 35, ENGLAND, -1, true));//�������� ����-���������
		sld.name = "�����";
		sld.lastname = "������";
		FantomMakeCoolSailor(sld, SHIP_BRIG, "", CANNON_TYPE_CANNON_LBS24, 70, 70, 70);//�������� �����
		FantomMakeCoolFighter(sld, 35, 60, 60, "blade15", "pistol5", 90);//�������� ������� ����
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Ship.Mode = "pirate";
		sld.AlwaysEnemy = true;
		sld.Abordage.Enable = true;
		Group_AddCharacter("Houm_Attack", "Houm_helper");//���������� � ������
 
    // ==> ������������
	Group_SetGroupCommander("Houm_Attack", "Houm");
	Group_SetTaskAttack("Houm_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Houm_Attack", PLAYER_GROUP);
	Group_SetAddress("Houm_Attack", pchar.questTemp.Headhunter.Island, "quest_ships", "quest_ship_6");
	Group_LockTask("Houm_Attack");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "Houm_Attack";//����� ������ ����������
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_HoumAttack_AfterBattle";//��� ������
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Headhunter_DieHard.function = "Headhunter_HoumAttack_DieHard";//��� ������
}

void Headhunter_HoumAttack_AfterBattle(string qName)//������� �� ������
{
	Group_DeleteGroup("Houm_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, true);
    pchar.quest.Headhunter_DieHard.over = "yes";
	AddQuestRecord("Headhunt", "7");
	pchar.questTemp.Headhunter = "hunt_houm_yes";
}

void Headhunter_HoumAttack_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("Houm_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, true);
    pchar.quest.Headhunter_AfterBattle.over = "yes";
	AddQuestRecord("Headhunt", "8");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	ChangeOfficersLoyality("bad_all", 1);
}

void Headhunter_PinasseOver(string qName)//�� ����������, ���� ���� �� 30 ����
{
	pchar.quest.Headhunter_Rattortuga.over = "yes";
	sld = characterFromId("RatOfficer");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "10");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_CreateRatpinasse(string qName)//�������� ������ �������� � ��������
{
	pchar.quest.Headhunter_PinasseOver.over = "yes";
	ref sld;
	Group_FindOrCreateGroup("PinasseC");//������� ������
	Group_SetType("PinasseC", "war");//��� ������
	
	sld = GetCharacter(NPC_GenerateCharacter("RatSeaOfficer", "officer_15", "man", "man", 35, FRANCE, -1, true));//�������� ����
	sld.name = "������ ��������";
	sld.lastname = "�����";
	FantomMakeCoolSailor(sld, SHIP_PINNACE, "��������", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);//�������� ��������
	FantomMakeCoolFighter(sld, 35, 80, 80, "blade15", "pistol2", 90);//�������� ������� ����
	sld.DontRansackCaptain = true; 
	DeleteAttribute(sld, "AlwaysFriend");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("PinasseC", "RatSeaOfficer");//���������� � ������
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
		
	Group_SetGroupCommander("PinasseC", "RatSeaOfficer");
	Group_SetTaskAttack("PinasseC", PLAYER_GROUP);
	Group_SetAddress("PinasseC", "Tortuga", "quest_ships", "quest_ship_1");
	Group_LockTask("PinasseC");
	AddQuestRecord("Headhunt", "15");
			
    // ==> ���������� �� ������� �������
    pchar.quest.HeadhunterC_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.HeadhunterC_AfterBattle.win_condition.l1.group = "PinasseC";
	pchar.quest.HeadhunterC_AfterBattle.function = "PinasseC_AfterBattle";
}

void PinasseC_AfterBattle(string qName)//������� �� ��������� ����������� ������
{
	sld = characterFromId("RatOfficer");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "16");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","�"));
	ChangeCharacterHunterScore(PChar, "frahunter", 30); //��������� ���
	pchar.questTemp.Headhunter = "end_quest";
	CloseQuestHeader("Headhunt");
	Group_DeleteGroup("PinasseC");
}

void CreateRatOfficer()//������� � ������� ������ ����� - �� ����� ������ �������
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("RatOfficer", "ozg_piRat", "man", "man", 10, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "����";
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "RatOfficer";
    sld.greeting = "pirat_common";
	sld.HeroModel = "ozg_piRat,ozg_piRat_1,ozg_piRat_2,ozg_piRat_3,ozg_piRat_4,ozg_piRat_5";
    GiveItem2Character(sld, "blade15");
	EquipCharacterbyItem(sld, "blade15");
    DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
    LAi_SetCitizenType(sld);
   	LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit","sit3");
}

void Headhunter_Ratgulf(string qName)//���������� � ������
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	Group_DeleteGroup("PinasseC");
	pchar.quest.Headhunter_RatgulfOver.over = "yes";
	if (GetCompanionQuantity(pchar) > 1 || 3-sti(RealShips[sti(pchar.ship.type)].Class) > 0)
	{
		AddQuestRecord("Headhunt", "19_1");
		AddQuestUserData("Headhunt", "sSex", GetSexPhrase("��","���"));
		CloseQuestHeader("Headhunt");
		pchar.questTemp.Headhunter = "end_quest";
	}
	else
	{
		AddQuestRecord("Headhunt", "19");
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1 = "Timer";
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.hour  = sti(GetTime() + 24);
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.function = "Headhunter_CreateRatTruepinasse_prepare";
		SetFunctionTimerCondition("Headhunter_Ratgulf2Over", 0, 0, 5, false);
	}
}

void Headhunter_CreateRatTruepinasse_prepare(string qName)
{
	pchar.quest.Headhunter_RatgulfPinasse.win_condition.l1 = "location";
    pchar.quest.Headhunter_RatgulfPinasse.win_condition.l1.location = "Beliz";//���������� � �������
    pchar.quest.Headhunter_RatgulfPinasse.function = "Headhunter_CreateRatTruepinasse";
}

void Headhunter_RatOfficerOver(string qName)//���������� ���������� � ������
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	Group_DeleteGroup("PinasseC");
	sld = characterFromId("RatOfficer");
	sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "RatOfficer_5";
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "17_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("��","���"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_RatgulfOver(string qName)//���������� ����� �� ������
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	pchar.quest.Headhunter_Ratgulf.over = "yes";
	Group_DeleteGroup("PinasseC");
	AddQuestRecord("Headhunt", "20");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("��","����"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_Ratgulf2Over(string qName)//�������� ������ ������ ������� ����� ������� � ������
{
	pchar.quest.Headhunter_RatgulfPinasse.over = "yes";
	AddQuestRecord("Headhunt", "20_1");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_CreateRatTruepinasse(string qName)//�������� ������ �������� � ������
{
	pchar.quest.Headhunter_Ratgulf2Over.over = "yes";
	ref sld;
	int hcrew;
	Group_FindOrCreateGroup("PinasseT");//������� ������
	Group_SetType("PinasseT", "war");//��� ������
	Island_SetReloadEnableGlobal("Beliz", false);
	
		sld = GetCharacter(NPC_GenerateCharacter("RatCaptain", "ozg_piRat", "man", "man", 25, PIRATE, -1, true));//�������� ����
	sld.name = "������";
	sld.lastname = "����";
	sld.DontRansackCaptain = true;
	sld.HeroModel = "ozg_piRat,ozg_piRat_1,ozg_piRat_2,ozg_piRat_3,ozg_piRat_4,ozg_piRat_5";
	FantomMakeCoolSailor(sld, SHIP_PINNACE, "��������", CANNON_TYPE_CANNON_LBS32, 80, 80, 80);//�������� ��������
		FantomMakeCoolFighter(sld, 25, 70, 70, "blade15", "pistol6", 100);//�������� ������� ����
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("PinasseT", "RatCaptain");//���������� � ������
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, 250+hcrew);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
		
	// ==> ������������
	Group_SetGroupCommander("PinasseT", "RatCaptain");
	Group_SetTaskAttack("PinasseT", PLAYER_GROUP);
	Group_SetAddress("PinasseT", "Beliz", "quest_ships", "Quest_ship_8");
	Group_LockTask("PinasseT");
	AddQuestRecord("Headhunt", "21");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "PinasseT";
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_Pinassetrue_AfterBattle";
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Headhunter_DieHard.function = "Headhunter_Pinassetrue_DieHard";//��� ������
}

void Headhunter_Pinassetrue_DieHard(string qName)//������� �� ���������
{
	Group_DeleteGroup("PinasseT");
    Island_SetReloadEnableGlobal("Beliz", true);
    pchar.quest.Headhunter_AfterBattle.over = "yes";
	AddQuestRecord("Headhunt", "22");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	ChangeOfficersLoyality("bad_all", 1);
}

void Headhunter_Pinassetrue_AfterBattle(string qName)//������� �� ������
{
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
		Group_DeleteGroup("PinasseT");
		Island_SetReloadEnableGlobal("Beliz", true);
		pchar.quest.Headhunter_DieHard.over = "yes";
		AddQuestRecord("Headhunt", "24");
		pchar.questTemp.Headhunter = "hunt_rat_yes2";
	}
	else
	{
		characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "RatCaptain"; //����� � �����, �������� �� ����
	}
}

void Headhunter_HalenOver(string qName)//�������� �� 10 ���� �� �������
{
	AddQuestRecord("Headhunt", "26_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";	
}

void RatHunters_inRoom(string qName)//���� � �������
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestCheckDelay("TalkSelf_Quest", 5.0);
}

void RatHunters_Sleep()//���� � �������
{
	SetLaunchFrameFormParam("������ ������ �����...", "", 0, 6);
    LaunchFrameForm();
    WaitDate("", 0, 0, 0, 8, 10); //������ �����
    RecalculateJumpTable();
	DoQuestFunctionDelay("RatHunters_Enter", 0.5);
}

void RatHunters_Enter(string qName)//������ �������
{	
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	int iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	for (i=1; i<=2; i++)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("RatHunters"+i, "officer_7", "man", "man", iTemp, PIRATE, -1, true));
		FantomMakeCoolFighter(sld, iTemp, 50, 50, "topor2", "pistol5", 50);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			LAi_CharacterDisableDialog(sld);
         	ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "goto", "goto2");
		}
		else
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "RatHunters";	
			sld.greeting = "Gr_HUNTER"; 
         	ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "goto", "goto3");
			LAi_ActorDialog(sld, pchar, "", 2.0, 0); 
		}
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_group_MoveCharacter(sld, "EnemyFight");
}

void CreateHalen()//������� ������ � ��������� ���������
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Halen", "ozg_martin", "man", "man", 30, HOLLAND, -1, false));
	sld.name = "������";
	sld.lastname = "��� �����";
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Halen";
    sld.greeting = "pirat_common";
    FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);
    ChangeCharacterAddressGroup(sld, "Villemstad_town", "reload", "reload3");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.HeroModel = "ozg_martin,ozg_martin_1,ozg_martin_2,ozg_martin_3,ozg_martin_4,ozg_martin_5";
	GiveItem2Character(sld, "cirass5");
	EquipCharacterbyItem(sld, "cirass5");
	LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Headhunter_FightInPort");//��������� �� ����� ������
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "Headhunter_HalenOut", -1);//���������, ���� ����� �����
	LAi_Actor2WaitDialog(sld, pchar);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
	for (i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("AddSolder"+i, "Sold_hol_"+(rand(7)+1), "man", "man", 20, HOLLAND, 1, true));
		sld.Dialog.Filename = "Common_Soldier.c";
		sld.city = "Villemstad";
		sld.citytype = "soldier";
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade16", "pistol3", 50);
        LAi_SetPatrolType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto"+i);    
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	}
	LAi_group_SetLookRadius("HOLLAND_CITIZENS", 100);
	LAi_group_SetHearRadius("HOLLAND_CITIZENS", 100);
	pchar.quest.Headhunter_FightInPort.win_condition.l1 = "location";
	pchar.quest.Headhunter_FightInPort.win_condition.l1.location = "Curacao";
	pchar.quest.Headhunter_FightInPort.function = "Headhunter_SeabattleInPort";
}

void Headhunter_SeabattleInPort(string qName)//�������� ������� ������
{
	ref sld;
	Group_FindOrCreateGroup("Halen_frigate");//������� ������
	Group_SetType("Halen_frigate", "war");//��� ������
		
	if (GetCharacterIndex("Halen") == -1)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Halen1", "officer_17", "man", "man", 25, HOLLAND, -1, true));
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Halen1", "ozg_martin", "man", "man", 25, HOLLAND, -1, true));//�������� ����
		sld.name = "������";
		sld.lastname = "��� �����";
		sld.HeroModel = "ozg_martin,ozg_martin_1,ozg_martin_2,ozg_martin_3,ozg_martin_4,ozg_martin_5";
	}
	sld.DontRansackCaptain = true; 
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, "�������� �����", CANNON_TYPE_CANNON_LBS32, 70, 70, 70);//�������� ��������
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);//�������� ������� ����
	sld.Ship.Mode = "war";
	Group_AddCharacter("Halen_frigate", "Halen1");//���������� � ������
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	if (GetCharacterIndex("Halen") != -1)
	{
		GiveItem2Character(sld, "cirass5");
	}
	sld.ship.Crew.Morale = 80;
	ChangeCrewExp(sld, "Sailors", 80);
	ChangeCrewExp(sld, "Cannoners", 80);
	ChangeCrewExp(sld, "Soldiers", 80);

	sld = GetCharacter(NPC_GenerateCharacter("Halen_helper", "off_hol_2", "man", "man", 25, HOLLAND, -1, true));//�������� ����
	sld.DontRansackCaptain = true; 
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);//�������� �� ������ ������
	FantomMakeCoolFighter(sld, 35, 60, 60, "blade15", "pistol2", 90);//�������� ������� ����
	sld.Ship.Mode = "war";
	Group_AddCharacter("Halen_frigate", "Halen_helper");//���������� � ������
		
	// ==> ������������
	Group_SetGroupCommander("Halen_frigate", "Halen1");
	Group_SetTaskAttack("Halen_frigate", PLAYER_GROUP);
	Group_SetAddress("Halen_frigate", "Curacao", "quest_ships", "Quest_ship_2");
	Group_LockTask("Halen_frigate");
			
    // ==> ���������� �� ������� �������
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "Halen_frigate";
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_Halen_frigate_AfterBattle";
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//������� �� �������
    pchar.quest.Headhunter_DieHard.function = "Headhunter_Halen_frigate_DieHard";//��� ������
}


void Headhunter_Halen_frigate_DieHard(string qName)//���� �� �����
{
	Group_DeleteGroup("Halen_frigate");
    Island_SetReloadEnableGlobal("Curacao", true);
    pchar.quest.Headhunter_AfterBattle.over = "yes";
	if (GetCharacterIndex("Halen") == -1 || GetCharacterIndex("Halen1") == -1)
	{
		AddQuestRecord("Headhunt", "31");
		pchar.questTemp.Headhunter = "hunt_halen_yes";
		ChangeCharacterHunterScore(PChar, "holhunter", 30);
	}
	else
	{
		AddQuestRecord("Headhunt", "30");
		CloseQuestHeader("Headhunt");
		pchar.questTemp.Headhunter = "end_quest";
		ChangeOfficersLoyality("bad_all",1);
	}
	characters[GetCharacterIndex("Halen")].lifeDay = 0;
}

void Headhunter_Halen_frigate_AfterBattle(string qName)//�������� ������
{
	Group_DeleteGroup("Halen_frigate");
	Island_SetReloadEnableGlobal("Curacao", true);
    pchar.quest.Headhunter_DieHard.over = "yes";
	AddQuestRecord("Headhunt", "31");
	pchar.questTemp.Headhunter = "hunt_halen_yes";
	ChangeCharacterHunterScore(PChar, "holhunter", 30);
	characters[GetCharacterIndex("Halen")].lifeDay = 0;
}

void CreateMiko()//�������� ���� ����������
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Miko", "ozg_miko", "man", "man", 40, SPAIN, -1, false));
	FantomMakeCoolFighter(sld, 40, 50, 100, "blade22", "pistol4", 150);
	sld.name = "����";
	sld.lastname = "����������";
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Miko";
    sld.greeting = "pirat_common";
	sld.HeroModel = "ozg_miko,ozg_miko_1,ozg_miko_2,ozg_miko_3,ozg_miko_4,ozg_miko_5";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "GunProfessional");
	GiveItem2Character(sld, "indian10");
	GiveItem2Character(sld, "Totem_5");
	GiveItem2Character(sld, "sculMa2");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "Pearlgroup_2");
	ChangeCharacterAddressGroup(sld, "Pearl_Town_2", "goto", "goto1");
	for (i=2; i<=5; i++)//������� ������ � ���������
	{
		sld = GetCharacter(NPC_GenerateCharacter("AddPearlguard"+i, "Pirate_"+(rand(24)+1), "man", "man", 25, SPAIN, -1, true));
		sld.Dialog.Filename = "Pearl_dialog.c";
		sld.dialog.currentnode = "PearlMan";
		sld.city = "Pearl_Town_2";
		sld.citytype = "soldier";
		sld.greeting = "pirat_common";
		FantomMakeCoolFighter(sld, 25, 50, 50, "blade16", "pistol3", 100);
        LAi_SetPatrolType(sld);
		ChangeCharacterAddressGroup(sld, "Pearl_Town_2", "goto", "goto"+i);    
		LAi_group_MoveCharacter(sld, "Pearlgroup_2");
	}
	LAi_group_SetLookRadius("Pearl_Town_2", 50);
	LAi_group_SetHearRadius("Pearl_Town_2", 50);
}

void Miko_die(string qName)
{
	chrDisableReloadToLocation = false;
	pchar.quest.Headhunter_Jahunters.win_condition.l1 = "location";
	pchar.quest.Headhunter_Jahunters.win_condition.l1.location = "shore55";
	pchar.quest.Headhunter_Jahunters.function = "Headhunter_Jahunters";	
}
		
void Headhunter_Jahunters(string qName)//������� ��� � �����
{
	chrDisableReloadToLocation = true;
	for (i=1; i<=6; i++)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("JaHunters"+i, "officer_17", "man", "man", 25, PIRATE, -1, true));
		FantomMakeCoolFighter(sld, 25, 60, 60, "topor2", "pistol6", 70);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "JaHunters";	
			sld.greeting = "Gr_HUNTER"; 
			ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto4");
			LAi_ActorDialog(sld, pchar, "", 10.0, 0); 
			LAi_SetImmortal(sld, true);
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto1");
		}
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("JaMush", "mushketer_1", "man", "mushketer", 35, PIRATE, -1, true));                    
    FantomMakeCoolFighter(sld, iTemp, 80, 80, "", "mushket", 100);
	ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto2");
	LAi_group_MoveCharacter(sld, "EnemyFight");	
}		
		
void Create_Ja(string qName)//c������ ����� � ���
{
	int hcrew;
	Group_FindOrCreateGroup("BlueBird_Group2");
	bQuestDisableMapEnter = true;
	sld = GetCharacter(NPC_GenerateCharacter("Jafar", "QuestCaptain", "man", "man", 28, PIRATE, -1, true));
	sld.name 	= "���";
    sld.lastname = "�������";
	sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Ja_talk";
	sld.greeting = "CapSinkShip";
	//Korsar Maxim - �������� ���� ������� ��� �����. -->
	sld.HeroModel = "QuestCaptain,QuestCaptain_1,QuestCaptain_2,QuestCaptain_3,QuestCaptain_4,QuestCaptain_5,QuestCaptain,QuestCaptain,QuestCaptain";
	//Korsar Maxim - �������� ���� ������� ��� �����. <--
	FantomMakeCoolFighter(sld, 35, 75, 75, "blade14", "pistol6", 100);
	FantomMakeCoolSailor(sld, SHIP_XebekVML, "����� �����", CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "MusketsShoot");
	GiveItem2Character(sld, "indian5");
	GiveItem2Character(sld, "jewelry15");
	GiveItem2Character(sld, "icollection");
	RemoveItems(sld, "spyglass3", 1);
	GiveItem2Character(sld, "spyglass4");
	EquipCharacterbyItem(sld, "spyglass4");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew+100);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	Group_AddCharacter("BlueBird_Group2", "Jafar");
	
	Group_SetGroupCommander("BlueBird_Group2", "Jafar");
	Group_SetAddress("BlueBird_Group2", "SantaCatalina", "quest_ships", "Quest_ship_9");
	Group_SetTaskAttack("BlueBird_Group2", PLAYER_GROUP);
	Group_LockTask("BlueBird_Group2");
	AddQuestRecord("Headhunt", "36");
	
	pchar.quest.Headhunter_AfterBattleJa.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattleJa.win_condition.l1.group = "BlueBird_Group2";
	pchar.quest.Headhunter_AfterBattleJa.function = "Ja_over";
}

void Ja_over(string qName)//���������� ���
{
	Group_DeleteGroup("BlueBird_Group2");
	bQuestDisableMapEnter = false;
	AddQuestRecord("Headhunt", "37");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","�"));
	pchar.questTemp.Headhunter = "hunt_ja_yes";
	sld = characterFromId("Pirates_trader");
	sld.name = "���������";
	sld.lastname = "��������";
	sld.model = "trader_2";
	LAi_SetOwnerType(sld);
	AddSimpleRumourCity("�, �����"+ GetSexPhrase("�","���") +"! �� �� ��� �� ������ ������� �������! ������ �������� �������� �������� - ������� ������ ������! �����������, �� ������ ��� ������, ��� ������� ������ �������� � �������� �����. ��� ����� ���� � ���� ����� ������� ������ ���. � ����� ������� �������� � ������ ��������� �� ��� ������� - ������ �� ������ � ������� � ����, ��-��-��. ��� �����-�� ����! ������� ������ ��� ���� ������, ���� ���� �������� ��������� �������� ���� � ����� ����� �� �������.\n"+
		"�� ��� ����� - ������ � ���� ���������� - �� ����� �� ����� ����������, ������� �� ���������� ����� �������� ������� ����������... � �������� �� ��� - ��� ����� ����� ����� �����, ��-��...","Pirates", 30, 3, "");
}
	
void Pascal_Escape()
{
	sld = characterFromId("Pirates_trader");
	sld.name = "���������";
	sld.lastname = "��������";
	sld.model = "trader_2";
	LAi_SetOwnerType(sld);
	AddSimpleRumourCity("�, �����"+ GetSexPhrase("�","���") +"! �� �� ��� �� ������ ������� �������! ������ �������� �������� �������� - ������� ������ ������! �����������, �� ������ ��� ������, ��� ������� ������ �������� � �������� �����. ��� ����� ���� � ���� ����� ������� ������ ���. � ����� ������� �������� � ������ ��������� �� ��� ������� - ������ �� ������ � ������� � ����, ��-��-��. ��� �����-�� ����! ������� ������ ��� ���� ������, ���� ���� �������� ��������� �������� ���� � ����� ����� �� �������.\n"+
		"�� ��� ����� - ������ � ���� ���������� - �� ����� �� ����� ����������, ������� �� ���������� ����� �������� ������� ����������... � �������� �� ��� - ��� ����� ����� ����� �����, ��-��...","Pirates", 30, 3, "");
}

//���

// --> ����� �����-�����
void LSC_RingOver(string qName) // ������ ������
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit", "sit2");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	if (!CheckAttribute(sld, "quest.ring_final")) AddQuestRecord("LSC_Ring", "2");
	
	sld = characterFromId("pet_crab");
	ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto5");
	LAi_SetActorTypeNoGroup(sld);
	LAi_type_actor_Reset(sld);
	LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	
	CloseQuestHeader("LSC_Ring");
	CloseQuestHeader("RingCapBook");
	
	
}

void LSC_RingStart(string qName) // ������
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = "ring_10";
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "ring");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
}

void LSC_RingEnter(string qName) // ������
{
	pchar.quest.LSC_Ring_Over.over = "yes"; //����� ����������
	SetLaunchFrameFormParam("������ ���..."+ NewStr() +"�� ��������� �� ��������� �������", "", 0, 6);//��������
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //������ �����
	RecalculateJumpTable();
	DoQuestFunctionDelay("LSC_RingReload", 5.5);
}

void LSC_RingReload(string qName) // ��������
{
	DoQuestReloadToLocation("ExternalRingInside", "reload", "reload1", "LSC_RingEnterInside");
}

void LSC_RingRishardTalk(string node) // ��������� �������
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = node;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_RingDeleteItemsBoxes(string qName)
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{				
		loc = &locations[i];
		if (loc.id == "ExternalRingDeck" || loc.id == "ExternalRingInside" || loc.id == "ExternalRingCabin1")
		{	
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName))
				{					
					makearef(arBox, loc.(sName));
					DeleteAttribute(arBox, "items");
					arBox.items = "";
				}
				else break;
			}
		}
	}
	pchar.GenQuestBox.ExternalRingInside = true;
	pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 1;
}
// <-- ����� �����-�����

// ������� ������ ������ Lipsar
string RandomCityAllien()
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		string City;
		int n, nation;
		int storeArray[27];
		int howStore = 0;
		string NATION1=pchar.BaseNation;
		switch (NATION1)
		{
			case "0":
				NATION1="ENGLAND";
			break;
			case "1":
				NATION1="FRANCE";
			break;
			case "2":
				NATION1="SPAIN";
			break;
			case "3":
				NATION1="HOLLAND";
			break;
			case "4":
				NATION1="PIRATE";
			break;
		}
		for (int i = 0; i < 27; i++)
		{
			if (colonies[i].nation != "none" && colonies[i].id != "Havana" && colonies[i].id != "Panama" &&  colonies[i].nation == NATION1 && colonies[i].id != "PortRoyal")
			{
				storeArray[howStore] = i;
				howStore++;
			}
		}
	n = rand(howStore - 1);
	nation = storeArray[n];
	City = colonies[nation].id;
	}
	Log_Info(City);
	return City;
}
string RandomCityEnemy()
{
	string City;
	int n, n1, n2, n3 = 0;
	int nation = 0;
	int storeArray[27];
	int howStore = 0;
	string Patent = pchar.PatentNation;
	switch (Patent)
	{
	case "eng":
		n = 0;
		n1 = 1;
		n2 = 0;
		n3 = 0;
	break;
	case "fra":
		n = 1;
		n1 = 0;
		n2 = 3;
		n3 = 1;
	break;
	case "spa":
		n = 2;
		n1 = 3;
		n2 = 2;
		n3 = 2;
	break;
	case "hol":
		n = 3;
		n1 = 1;
		n2 = 2;
		n3 = 3;
	break;
	}
	for (int i = 0; i < 27; i++)
	{
		if (colonies[i].nation != "none" && sti(colonies[i].nation) != PIRATE && colonies[i].id != "Havana" && colonies[i].id != "Panama" && colonies[i].nation != n && colonies[i].nation != n1 && colonies[i].nation != n2 && colonies[i].nation != n3)
		{
			storeArray[howStore] = i;
			howStore++;
		}
	}
	n = rand(howStore - 1);
	nation = storeArray[n];
	City = colonies[nation].id;
	return City;
}
void SpawnMaks(string spawn_max)
{
	sld = GetCharacter(NPC_GenerateCharacter("Maks", "pirate_15", "man", "man", 30, PIRATE, -1, false));
	sld.name = "�����������";
	sld.lastname = "�����";
	sld.City = spawn_max - "_tavern";
	FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol5", 300);
	FreeSitLocator(spawn_max, "sit1");
	SetSelfSkill(sld, 100, 80, 80, 100, 80);
	SetShipSkill(sld, 70, 70, 70, 70, 70, 70, 70, 70, 70);
	ChangeCharacterAddressGroup(sld, spawn_max, "sit", "sit1");
	sld.Dialog.filename = "Quest\SilencePrice\Maks.c";
	LAi_SetImmortal(sld, true);
	LAi_SetSitType(sld);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	sld.NextDiag.TempNode = "First_Time";
}
string RandomHouse(ref npchar)
{
	aref arCommon, arRld, arRld2, arDis;
	int i, n, Qty, Qty2;
	string LocId;
	string storeArray[50];
	int howStore = 0;
	makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
	for (i = 0; i < Qty; i++)
	{
		arCommon = GetAttributeN(arRld, i);
		LocId = arCommon.go;
		if (findsubstr(LocId, "Common", 0) != -1)
		{
			storeArray[howStore] = LocId;
			howStore++;
		}

		if (arCommon.label != "Sea")
		{
			makearef(arRld2, Locations[FindLocation(LocId)].reload);
			Qty2 = GetAttributesNum(arRld2);
			for (n = 0; n < Qty2; n++)
			{
				arCommon = GetAttributeN(arRld2, n);
				LocId = arCommon.go;
				if (findsubstr(LocId, "Common", 0) != -1)
				{
					storeArray[howStore] = LocId;
					howStore++;
				}
			}
		}
	}
	LocId = storeArray[rand(howStore - 1)];
	Log_info(LocId);
	Pchar.Luke.City.Loc = LocID;
	SetOpenDoorCommonLoc(Pchar.Luke.City, LocID);
	return LocId;
}
void GetSpawnPirate(string qName)
{
	chrDisableReloadToLocation = true; 
	sld = GetCharacter(NPC_GenerateCharacter("Anri", "officer_58", "man", "man", 30, PIRATE, -1, false));
	sld.name = "����";
	sld.lastname = "�����������";
	SelAllPerksToNotPchar(sld);
	FantomMakeCoolFighter(sld, 30, 90, 90, "blade32", "pistol5", 300);
	sld.Dialog.filename = "Quest\SilencePrice\Anri.c";
	sld.SaveItemsForDead = true;
	LAi_SetImmortal(sld,true);
	SetSelfSkill(sld, 100, 80, 80, 100, 80);
	SetShipSkill(sld, 70, 70, 70, 70, 70, 70, 70, 70, 70);
	SelAllPerksToNotPchar(sld);
	sld.NextDiag.TempNode = "First_Time";
	ChangeCharacterAddressGroup(sld, "LaVega_town", "officers", LAi_FindNearestFreeLocator2Pchar("officers"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, Pchar, "", 20.0, 5.0);
	bDisableFastReload = false;
}
void PirateComeToIsabella(string qName)
{
	sld = CharacterFromID("Anri");
	sld.NextDiag.CurrentNode = "Isabella_1";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Shore32", "smugglers", "smugglerload"));
	Locations[FindLocation("Shore32")].DisableEncounters = true;
	LAi_SetActorType(sld);
	LAi_LocationDisableOfficersGen("Shore32", true);
	LAi_ActorDialog(sld, Pchar, "", 20.0, 20.0);
}
void PirateComeToIsabellaLoose(string qName)
{
	sld = CharacterFromID("Anri");
	ChangeCharacterAddressGroup(sld, "none", "none", "none");
	AddQuestRecord("Silence_Price", "5_1");
	CloseQuestHeader("Silence_Price");
}
void MaksCome(string qName)
{
	sld = CharacterFromID("Maks");
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld, Pchar.Luke.City.Loc, "reload", "reload1");
	SelAllPerksToNotPchar(sld);
	LAi_group_MoveCharacter(sld, "Maks");
	LAi_SetPlayerType(pchar);
	LAi_group_FightGroups("Maks", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("Maks","AddGuardians");
	EndLookAfterCharacter();
	LAi_SetFightMode(pchar, true);
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld,"book3_5");
	GiveItem2Character(sld,"book3_12");
	GiveItem2Character(sld,"cirass5");
	EquipCharacterByItem(sld, "cirass5");
	RemoveItems(sld, "cirass5", 1);
	sld.DontClearDead = true;
}
void LukesEscape(string qName)
{
	AddQuestRecord("Silence_Price", "6");
	Flag_PIRATE();
	AddCharacterHealth(pchar, -30);
	Pchar.Luke.BadPoison = "1";
}
void spawn_2()
{
}
void enemies()
{
}

//Korsar Maxim --> ��� ���
void SetPortAlarm(string qName) //������� � ������, ���� �������� ��� ��������� ������
{
	Log_Info("�������!! ���� � ������!!");
	
	string sCity = FindStringBeforeChar(PChar.location, "_town");
	
	int iNation = GetCityNation(sCity);
	
	string sNation = GetNationNameByType(iNation);
	
	LAi_group_FightGroups(GetNationNameByType(iNation)+"_citizens", LAI_GROUP_PLAYER, false);
	if (rand(3) != 1) SetNationRelation2MainCharacter(iNation, RELATION_ENEMY);
}
//Korsar Maxim <-- ��� ���

//Korsar Maxim - LEO � Gregg, ��� ����� ��� ������ ���������� (� �� ������) ����!
// || || || || || ||
// \/ \/ \/ \/ \/ \/
 
//LEO -->

//LEO <--

//Gregg -->

//Gregg <--

//Sinistra ��������� ���� -->
void PDM_Callow_RodjerProdolg(string qName)
{ 
	chrDisableReloadToLocation = true;   //������ �������	
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true); //��������� ������
	Pchar.GenQuest.Hunter2Pause = true;
    //--------------------------- �������� ------------------------------
	
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	sld = GetCharacter(NPC_GenerateCharacter("FraEnemy_off", "off_fra_1", "man", "man", Rank, FRANCE, -1, true));
    FantomMakeCoolFighter(sld, sti(pchar.rank), 20, 20, "blade18", "", 20);	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
	LAi_SetActorType(sld);
	sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";		//�������� ����� �������
	sld.dialog.currentnode   = "FraOff_1";				//� ����� ����� �������� ������
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
	for (i=1; i<=3; i++)
    {
        sTemp = "sold_fra_"+(rand(7)+1);  //����������
		if (i==12) sTemp = "off_fra_1";
 		sld = GetCharacter(NPC_GenerateCharacter("FraEnemy_"+i, sTemp, "man", "man", Rank, FRANCE, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 10, 10, "blade2", "", 10);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
    }
}
void PDM_Callow_Voina(string qName)
{
	sld = CharacterFromID("James_Callow");
	FantomMakeCoolFighter(sld, 6, 25, 25, "blade34", "", 120);
	FantomMakeCoolSailor(sld, SHIP_SCHOONERLIGHT, "������ �����", CANNON_TYPE_CULVERINE_LBS12, 60, 30, 50);
	sld.name	= "������";
	sld.lastname	= "������";
	LAi_SetImmortal(sld, false);
	sld.AlwaysSandbankManeuver = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true;
	sld.AlwaysEnemy = true;
	GiveItem2Character(sld, "lockpick");
	AddItems(sld, "jewelry1", rand(5)+2);
	AddItems(sld, "jewelry2", rand(2)+2);
	AddItems(sld, "jewelry3", rand(5)+2);	
	AddItems(sld, "jewelry4", rand(5)+2);
	AddItems(sld, "jewelry12", rand(20)+2);
	AddMoneyToCharacter(sld, 15000);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	sld.ship.Crew.Morale = 80;
	ChangeCrewExp(sld, "Sailors", 60);
	ChangeCrewExp(sld, "Cannoners", 30);
	ChangeCrewExp(sld, "Soldiers", 50);
	
	Group_FindOrCreateGroup("Nui");					//�������� ������
	Group_SetType("Nui", "war");						//��� ���������
	Group_AddCharacter("Nui", "James_Callow");	//�������� ��������
	Group_SetGroupCommander("Nui", "James_Callow");
	Group_SetTaskAttack("Nui", PLAYER_GROUP);
	Group_SetPursuitGroup("Nui", PLAYER_GROUP);
	Group_SetAddress("Nui", "Hispaniola1", "", "");
	Group_LockTask("Nui");

	pchar.quest.PDM_Pobeda_nad_Callow.win_condition.l1 = "NPC_Death";
	pchar.quest.PDM_Pobeda_nad_Callow.win_condition.l1.character = "James_Callow";
	pchar.quest.PDM_Pobeda_nad_Callow.win_condition = "PDM_Pobeda_nad_Callow";
	PChar.quest.PDM_NEPobeda_nad_Callow.win_condition.l1 = "MapEnter";
	PChar.quest.PDM_NEPobeda_nad_Callow.function = "PDM_NEPobeda_nad_Callow";
}
void PDM_NEPobeda_nad_Callow(string qName)
{
	sld = CharacterFromID("James_Callow");
	Group_FindOrCreateGroup("Nui");					//�������� ������
	Group_SetType("Nui", "war");						//��� ���������
	Group_AddCharacter("Nui", "James_Callow");	//�������� ��������
	Group_SetGroupCommander("Nui", "James_Callow");
	Group_SetTaskAttack("Nui", PLAYER_GROUP);
	Group_SetPursuitGroup("Nui", PLAYER_GROUP);
	Group_SetAddress("Nui", "none", "", "");
	Group_LockTask("Nui");								
	AddCharacterExpToSkill(PChar, "Leadership", -40);
    AddCharacterExpToSkill(PChar, "Sailing", -40);
    AddCharacterExpToSkill(PChar, "Accuracy", -20);
    AddCharacterExpToSkill(PChar, "Cannons", -20);
	AddCharacterExpToSkill(PChar, "Repair", -20);
    AddCharacterExpToSkill(PChar, "Defence", -20);
    AddCharacterExpToSkill(PChar, "Sneak", -20);
	AddQuestRecord("PDM_Cursed_Idol", "7");
	AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","�"));
	CloseQuestHeader("PDM_Cursed_Idol"); 
}
//Sinistra ��������� ���� <--

//Sinistra ������ �� ����� -->
void PDM_Zoloto_ne_tonet_BITVA_na_sushe(string qName)
{
	chrDisableReloadToLocation = true;
	Pchar.GenQuest.Hunter2Pause = true;
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	PlaySound("Kopcapkz\Voices\PDM\Witch\piple.wav");
	PlaySound("Kopcapkz\Voices\PDM\Ispantsi.wav");
	
	int Rank = sti(pchar.rank) - 3 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
//------------------------�������-------------------
	for (i=1; i<=9; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);  //����������
		if (i==6) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SraFriend_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 40, 40, BLADE_NORMAL, "", 10);
		sld.greeting = "GR_Spainguard";
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
		sld.dialog.currentnode   = "Novoe_Zadanie_ZaIspaniu";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto13");
	}
	for (i=10; i<=18; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);  //����������
		if (i==15) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SraFriend_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 40, 40, BLADE_NORMAL, "", 10);
		sld.greeting = "GR_Spainguard";
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
		sld.dialog.currentnode   = "Novoe_Zadanie_ZaIspaniu";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "item",  "item10");
	}
	for (i=19; i<=22; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));		
		sld.MusketerDistance = 0;
		sld.greeting = "GR_Spainguard";
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
		sld.dialog.currentnode   = "Novoe_Zadanie_ZaIspaniu";
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto10");
	}
//----------------------���������-------------------------	
	for (i=23; i<=43; i++)
    {
        sTemp = "sold_eng_"+(rand(7)+1);  //����������
		if (i==40) sTemp = "off_eng_1";
 		sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_"+i, sTemp, "man", "man", Rank, ENGLAND, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, BLADE_NORMAL, "", 20);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_ENGenemy");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto16");
	}
	for (i=44; i<=47; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("EngMush_"+i, "eng_mush_"+(rand(2)+1), "man", "mushketer", Rank, ENGLAND, -1, false));		
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "PDM_ENGenemy");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto26");
	}
	LAi_group_SetRelation("PDM_ENGenemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//�����������
	LAi_group_FightGroups("PDM_ENGenemy", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("PDM_ENGenemy", "PDM_ZolNeTon_PobNaSush");
}
//Sinistra ������ �� ����� <--

//Sinistra ����� �� ������ -->
void PDM_ONV_Kazn(string qName)
{
	sld = CharacterFromID("PDM_ONV_Podjigatel")
	LAi_ActorGoToLocator(sld, "merchant", "mrcActive2", "PDM_ONV_PodjIschezni", -1);
}
void PDM_ONV_Kazn_2(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("PDM_ONV_Podjigatel")
	sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "Inqizitor_Kazn_3";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}
void PDM_ONV_Kazn_3(string qName)
{
	sld = CharacterFromID("PDM_ONV_Carla")
	LAi_KillCharacter(sld);
}
void PDM_ONV_Kazn_4(string qName)
{
	AddQuestRecord("PDM_Ohota_na_vedmu", "14");
	AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
	LAi_SetPlayerType(pchar);
	pchar.questTemp.PDM_ONV_VedmaKaznena = "PDM_ONV_VedmaKaznena";
	
	sld = CharacterFromID("PDM_ONV_Inkvizitor")
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	LAi_ActorGoToLocator(sld, "reload", "basement1", "PDM_ONV_InqIschzni", -1);
			
	sld = CharacterFromID("PDM_ONV_Jitel_1")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_2")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_3")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
	
	sld = CharacterFromID("PDM_ONV_Podjigatel")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_4")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_5")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_6")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_7")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_8")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_9")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_10")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
			
	sld = CharacterFromID("PDM_ONV_Jitel_11")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
	
	sld = CharacterFromID("PDM_ONV_Jitel_12")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
	
	sld = CharacterFromID("PDM_ONV_Jitel_13")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
	
	sld = CharacterFromID("PDM_ONV_Jitel_14")
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	sld.lifeday = 0;
}
//Sinistra ����� �� ������ <--

//Sinistra ���� �������� -->
void PDM_CL_Ubrat_Lodku(string qName)
{
	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE * 12;
	
	sld = CharacterFromID("PDM_CL_Antonio")
	ChangeCharacterAddressGroup(sld, "Maracaibo_town", "none", "");
	sld = CharacterFromID("PDM_CL_Anto2")
	ChangeCharacterAddressGroup(sld, "Maracaibo_town", "none", "");
	Group_SetAddress("PDM_el_tib", "none", "", "");
	
	sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio3", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
	sld.name = "�������";
	sld.lastname = "�� �������";
	sld.greeting = "GR_Spainguard";
	FantomMakeCoolFighter(sld, Rank, Sila, Sila, "", "pistol2", DopHP);
	sld.equip.blade = "blade39";
	sld.nonTable = true;
	LAi_SetSitType(sld);
	sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
	sld.dialog.currentnode   = "Antonio_2_1";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	sld.city = "Maracaibo";
	ChangeCharacterAddressGroup(sld, "Maracaibo_church", "sit", "sit16");
	LAi_SetLoginTime(sld, 9.0, 13.00);
}
void PDM_CL_Sadis_Pokupatel(string qName)
{
	sld = CharacterFromID(pchar.LambriniPGG)
	ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
	LAi_SetSitType(sld);
}
void PDM_CL_Sadis_Octavio(string qName)
{
	sld = CharacterFromID("PDM_Octavio_Lambrini")
	ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_front2");
	LAi_SetSitType(sld);
}
void PDM_CL_PlayerType(string qName)
{
	LAi_SetPlayerType(pchar);
}
void PDM_CL_Octavio_Speech(string qName)
{
	sld = CharacterFromID("PDM_Octavio_Lambrini");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void PDM_CL_Pokupatel_Speech(string qName)
{
	sld = CharacterFromID(pchar.LambriniPGG);
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void PDM_CL_Pokupatel_Uhodit(string qName)
{
	sld = characterFromID(pchar.LambriniPGG);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "tables", "stay3");
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
}

void LambriniPGG_RemoveFromShore(string qName)
{
	sld = characterFromID(pchar.LambriniPGG);
	ChangeCharacterAddressGroup(sld, "none", "none", "none");
}

void LambriniPGG_Tavern(string qName)
{
	sld = CharacterFromID(pchar.LambriniPGG);
	sld.dialog.currentnode   = "LambriniPGG_2_3";
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialog", 0);
}
//Sinistra ���� �������� <--

void InstantDialog(string qName)
{
	sld = CharacterFromID(pchar.InstantDialog);
	LAi_SetStayTypeNoGroup(sld);
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void SaveOldDialog(ref chr)
{
	chr.Dialog.FilenameBackup = chr.Dialog.Filename;
	chr.dialog.currentnodeBackup   = chr.dialog.currentnode;
}

void RestoreOldDialog(ref chr)
{
	chr.Dialog.Filename = chr.Dialog.FilenameBackup;
	chr.dialog.currentnode   = chr.dialog.currentnodeBackup;
}

//Blackthorn ������
void PirateVikingQuest_Captain_Is_Dead(string qName)
{
	AddQuestRecord("pirateVikingQuest", "7");
	pchar.questTemp.pirateVikingQuest = "7";
}
//Blackthorn ������

//���������
void FreeTichingituOver(string qName)//������� ���������
{
	DeleteAttribute(pchar, "questTemp.Tichingitu");
	if (CheckCharacterItem(pchar, "letter_1")) RemoveItems(pchar, "letter_A", 1); // 170712
}

void SetTichingituJail()//������ ���������
{
	sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "Tichingitu_0", "man", "man", 10, FRANCE, -1, false));
	sld.name = "���������"; // 270912
	sld.lastname = "";
	sld.greeting = "GR_Tynichgitu";
    sld.Dialog.Filename = "Quest\Tichingitu.c";
	sld.dialog.currentnode = "Tichingitu";
	sld.rank = 12;
	sld.HeroModel = "Tichingitu_0,Tichingitu_1,Tichingitu_2,Tichingitu_3,Tichingitu_4,Tichingitu_5";
	LAi_SetHP(sld, 140.0, 140.0);
	SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
	SetSelfSkill(sld, 30, 30, 30, 50, 20);
    SetShipSkill(sld, 5, 5, 2, 5, 1, 2, 1, 1, 10);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	ChangeCharacterAddressGroup(sld, "BasTer_prison", "goto", "goto9");
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true); // 170712
}
//
void ReloadMyGun(string qName)
{
	if(!CheckAttribute(pchar, "MushketSwap"))
	{
		pchar.MushketSwap = true;
		string sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
		ref rItm = ItemsFromID(sGun); 
		int iCharge = iGetPistolChargeNum(pchar, LAi_GunSetChargeQuant(pchar,sti(rItm.chargeQ)));
		//pchar.chr_ai.charge = iCharge;
	}
}
// ��������� ����������
void UnexpectedInheritance()
{
	sld = GetCharacter(NPC_GenerateCharacter("UI_girl", "girl_1", "woman", "woman", 1, FRANCE, -1, false));
	LAI_SetStayType(sld);
	sld.talker = 10;
	LAi_group_MoveCharacter(sld, "France_citizens");
	sld.Dialog.Filename = "Quest\UnexpectedInheritance.c";
	sld.dialog.currentnode = "Girl";
	ChangeCharacterAddressGroup(sld, "BasTer_town", "patrol", "patrol12");
}

void UnexpectedInheritanceGetPartTwo(string qName)
{
	Log_Info("�� ����� ��������� � ������� �� ������");
	PlaySound("interface\important_item.wav");
	AddQuestRecord("UnexpectedInheritance", "3");
	AddQuestUserData("UnexpectedInheritance", "sSex", GetSexPhrase("��","��"));
	ref locLoad = &locations[reload_location_index];
	locLoad.box1.items.indian22 = 1;
	
	pchar.UnexpectedInheritance = "part2";
}
void UnexpectedInheritanceGetPartThree(string qName)
{
	Log_Info("�� ����� ��������� � ������� �� ������ � ��������� �����");
	PlaySound("interface\important_item.wav");
	AddQuestRecord("UnexpectedInheritance", "5");
	ref locLoad = &locations[reload_location_index];
	locLoad.private1.items.indian20 = 1;
	
	pchar.UnexpectedInheritance = "part3";
}
void UnexpectedInheritanceGetPartFour(string qName)
{
	chrDisableReloadToLocation = false;
	Log_Info("�� ����� ��� ����� ����������");
	PlaySound("interface\important_item.wav");
	AddQuestRecord("UnexpectedInheritance", "7");
	
	pchar.UnexpectedInheritance = "part4";
}
void UnexpectedInheritanceGetPartFive(string qName)
{
	Log_Info("� ������� �����");
	//PlaySound("interface\important_item.wav");
	AddQuestRecord("UnexpectedInheritance", "9");
	
	pchar.UnexpectedInheritanceFort = true;
}
void UnexpectedInheritanceEnd(string qName)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	AddQuestRecord("UnexpectedInheritance", "11");
	CloseQuestHeader("UnexpectedInheritance");
}
void UnexpectedInheritanceSeaBattle()
{
	sld = GetCharacter(NPC_GenerateCharacter("UICap", "officer_17", "man", "man", 55, PIRATE, -1, true));
	sld.Ship.Type = GenerateShipExt(SHIP_MORDAUNT, true, sld);
	SetRandomNameToShip(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	
	SetCrewQuantityFull(sld);
	int hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew + 12 * MOD_SKILL_ENEMY_RATE);// �������� ���
	
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 5 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 5 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 5 + 5 * MOD_SKILL_ENEMY_RATE);

	sld.money = 100000;
	sld.SaveItemsForDead = true;
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	sld.SaveItemsForDead = true;
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
	Group_FindOrCreateGroup("UI_seabattle");
	Group_SetType("UI_seabattle", "pirate");
	Group_AddCharacter("UI_seabattle", sld.id);
	Group_SetGroupCommander("UI_seabattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	LAi_SetImmortal(sld, false);
	Group_SetPursuitGroup("UI_seabattle", PLAYER_GROUP);
	Group_SetTaskAttack("UI_seabattle", PLAYER_GROUP);
	Group_LockTask("UI_seabattle");
	Group_SetAddress("UI_seabattle", "Dominica", "Quest_ships", "quest_ship_7");
}
void UnexpectedInheritanceGrottoPirates(string qName)
{
	chrDisableReloadToLocation = true;
	Group_FindOrCreateGroup("UIPirates");
	for (int i = 1; i <= MOD_SKILL_ENEMY_RATE; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("UI_pirate"+i, "pirate_"+(rand(20)+1), "man", "man", 55, PIRATE, -1, true));
		if (i == 1)
		{
			sld.model = "officer_25";
			LAI_SetStayType(sld);
			sld.talker = 10;
			sld.Dialog.Filename = "Quest\UnexpectedInheritance.c";
			sld.dialog.currentnode = "GrottoPirate";
			ChangeCharacterAddressGroup(sld, "Dominica_Grot", "goto", "goto1");
			TakeNItems(sld, "chest", 5);
			sld.SaveItemsForDead = true;
			pchar.quest.UnexpectedInheritanceGetPartFour.win_condition.l1 = "NPC_Death";
			pchar.quest.UnexpectedInheritanceGetPartFour.win_condition.l1.character ="UI_pirate1";
			PChar.quest.UnexpectedInheritanceGetPartFour.function = "UnexpectedInheritanceGetPartFour";
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "Dominica_Grot", "monsters", "monster1");
			LAI_SetWarriorType(sld);
		}
		LAi_group_MoveCharacter(sld, "UIPirates");
	}
}
void UnexpectedInheritanceTerks(string part)
{
	chrDisableReloadToLocation = true;
	Group_FindOrCreateGroup("UISkeletons");
	for (int i = 1; i <= MOD_SKILL_ENEMY_RATE; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("UI_skel"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 50, PIRATE, -1, true));
		if (i == 1)
		{
			LAi_SetImmortal(sld, true);
			sld.model = "BSUnd5";
			FantomMakeCoolFighter(sld, 50, 100, 100, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), "pistol8", MOD_SKILL_ENEMY_RATE*4);
			LAi_SetHP(sld, 500*MOD_SKILL_ENEMY_RATE, 500*MOD_SKILL_ENEMY_RATE);
			sld.SaveItemsForDead = true;
			sld.cirassId = Items_FindItemIdx("cirass5");  // �������� ���, �� �������� ����
			LAI_SetStayType(sld);
			sld.talker = 10;
			sld.Dialog.Filename = "Quest\UnexpectedInheritance.c";
			sld.dialog.currentnode = "GrottoSkeleton";
			sld.HeroModel = "BSUnd5,BSUnd5_1,BSUnd5_2,BSUnd5_3,BSUnd5_4,BSUnd5_5";
			ChangeCharacterAddressGroup(sld, "Terks_Grot", "monsters", "monster3");
			//TakeNItems(sld, "chest", 5);
			sld.SaveItemsForDead = true;
			pchar.quest.UnexpectedInheritanceEnd.win_condition.l1 = "NPC_Death";
			pchar.quest.UnexpectedInheritanceEnd.win_condition.l1.character ="UI_skel1";
			PChar.quest.UnexpectedInheritanceEnd.function = "UnexpectedInheritanceEnd";
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "Terks_Grot", "monsters", "monster1");
			LAi_KillCharacter(sld);
		}
		LAi_group_MoveCharacter(sld, "UIPirates");
	}
}
void UnexpectedInheritanceTranslatePart(string part)
{
	if (part == "part1")
	{
		AddQuestRecord("UnexpectedInheritance", "2");
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1 = "locator";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.location = "Mayak9";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator_group = "box";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator = "box1";
		pchar.quest.UnexpectedInheritanceGetPartTwo.function = "UnexpectedInheritanceGetPartTwo";
	}
	if (part == "part2")
	{
		AddQuestRecord("UnexpectedInheritance", "4");
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1 = "locator";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.location = "FortOrange_town";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator_group = "box";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator = "private1";
		pchar.quest.UnexpectedInheritanceGetPartTwo.function = "UnexpectedInheritanceGetPartThree";
	}
	if (part == "part3")
	{
		AddQuestRecord("UnexpectedInheritance", "6");
		UnexpectedInheritanceSeaBattle();
		
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1 = "location";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.location = "Dominica_Grot";
		pchar.quest.UnexpectedInheritanceGetPartTwo.function = "UnexpectedInheritanceGrottoPirates";
	}
	if (part == "part4")
	{
		AddQuestRecord("UnexpectedInheritance", "8");
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1 = "locator";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.location = "FortFrance_fort";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator_group = "box";
		pchar.quest.UnexpectedInheritanceGetPartTwo.win_condition.l1.locator = "box1";
		pchar.quest.UnexpectedInheritanceGetPartTwo.function = "UnexpectedInheritanceGetPartFive";
	}
}

void scareOfficers(int minSkill)
{
	int i, idx;
	for(i = 1; i <= MAX_NUM_FIGHTERS; i++ )
	{
		if (CheckOfficersPerk(pchar, "IronWill"))
	    {
			minSkill = minSkill * 0.7;
		}
		idx = GetOfficersIndex(pchar,i);
		if( idx == -1 ) continue;
		sld = GetCharacter(idx);
		if (sld.location == pchar.location )
		{
			if(minSkill + drand(30+i) > sti(GetSummonSkillFromName(sld, SKILL_LEADERSHIP)))
			{
				ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "goto",  "goto1");
				Log_Info("������ "+GetFullName(sld)+" �������"+NPCharSexPhrase(sld,"","�")+ " � �������!");
			}
			else
			{
				Log_Info("������ "+GetFullName(sld)+" ���������"+NPCharSexPhrase(sld,"","�")+ " ���� �����!");
			}
		}
	}
}