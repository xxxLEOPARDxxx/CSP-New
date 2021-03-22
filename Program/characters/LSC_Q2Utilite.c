// Warship -->
// ����������� ��������� �������
void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership = _min + rand(iDelta);
	_ch.skill.FencingLight = _min + rand(iDelta);
	_ch.skill.Fencing = _min + rand(iDelta);
	_ch.skill.FencingHeavy = _min + rand(iDelta);
	_ch.skill.Pistol = _min + rand(iDelta);
	_ch.skill.Fortune = _min + rand(iDelta);
	_ch.skill.Sneak = _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}

void SelAllPerksToNotPChar(ref _ch)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.Medic = "1";
	_ch.perks.list.HPPlus = "1";
	_ch.perks.list.EnergyPlus = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.ShipEscape = "1";
	
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";
	_ch.perks.list.ByWorker = "1";
	_ch.perks.list.ByWorker2 = "1";
}

// ���������� ����� ��� �����
void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.AgileMan = "1";
	_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.SharedExperience = "1";
	_ch.perks.list.Medic = "1";
	_ch.perks.list.HPPlusFixed = "1";
	_ch.perks.list.EnergyPlusFixed = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.UnlimitedContra = "1";
	_ch.perks.list.ShipEscape = "1";
	_ch.perks.list.Buldozer = "1";
	_ch.perks.list.AboardCollector = "1";
	
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SeaDogProfessional = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";
	
	if(_isOfficer) // � ���� ���� ���. �����
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// ���������� ����� �������� ������
void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.SharedExperience = "1";
	
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	
	if(_isOfficer) // � ���� ���� ���. �����
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// �������� ��� �������� (����� ���������) � ���������� ���������
void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	// ������ ����� ��� ����������
	if(_ch == GetMainCharacter())
	{
		StoreEquippedMaps(_ch);
		_ch.MapsAtlasCount = 0;
	}	
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, MAPS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BACKPACK_ITEM_TYPE);
	RemoveCharacterEquip(_ch, TALISMAN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BOOK_ITEM_TYPE);
	
	//������ ��� ��������, ����� ��������� -->
	aref arItems;
	string sName;
	ref rLoc;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (int a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}			
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{		
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}		
	DeleteAttribute(_ch, "questTemp.items");
	
	if(_removemoney)
	{
		_ch.money = 0;
	}
}

// ������ ���� ���������� � ����������� ��
void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;
	
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // ������ ������ � ������� �� ���������, ���� �� ����
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // ��������� �� �������
		{
		    ch.LifeDay = 1; // ���� �� ����� �������
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // �� ������� ��������� � ���
			{
			    ch.LifeDay = 1; // ���� �� ����� �������
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
}

void CleanAllCabinBoxes()
{
	ref loc;
	int n;
	string sTemp;
	
    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
}

// ����� ������ ��������� ��� �������, ������� ������� �� ������ ���� ���������
int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_WARSHIP + rand(2);
			break;
			
		case 2:
			iShipType = SHIP_FRIGATE + rand(1);
			break;
		
		case 3:
			iShipType = SHIP_CORVETTE + rand(2);
			break;
			
		case 4:
			iShipType = SHIP_FLEUT + rand(2);
			break;
			
		case 5:
			iShipType = SHIP_BARQUE + rand(1);
			break;
			
		case 6:
			iShipType = SHIP_SLOOP + rand(1);
			break;
			
		case 7:
			iShipType = SHIP_WAR_TARTANE + rand(1);
			break;
	}
	return iShipType;
}

// ��������, ���� �� � �� ��������
bool IsPCharHaveTreasurer()
{
	ref rOfficer;

	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		rOfficer = &characters[i];
		if(CheckAttribute(rOfficer, "treasurer") && sti(rOfficer.Treasurer) == 1)
		{
			return true; // �������� ����
		}
		
	}
	
	return false;
}

// ����� ������ ������ �� ��������
ref GetPCharTreasurerRef()
{
	if(!IsPCharHaveTreasurer()) return &NullCharacter;
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(CheckAttribute(&characters[i], "treasurer") && sti(characters[i].Treasurer) == 1)
		{
			return &characters[i];
		}
	}
	
	return &NullCharacter;
}

// ����� ������ �������� ��������
string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";
	
	sTemp = _rChar.(_sAttr);
	return sTemp;
}

// �������� ��������� ������� � ��������� ����� �� �������� �������
string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	for(i=1; i<MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		if(findsubstr(rLoc.id, _type, 0) != -1 && rLoc.islandId == _island)
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}
	
	if(iRandLoc == 0)
		return "none";
	
	i = iMaxLoc[rand(iRandLoc-1)];
	return locations[i].id;
}

// ������ ���������� -->
void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}
// ������ ���������� <--

// Warship <--

void LockQuestLine(ref refChar) // ����� ��������� �������
{
	refChar.notQuestLine = true;
}

string QuestGetGangLocation(string _areal)	// �������� ������� ��� ��������� ���� � �.�.
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if(GiveArealByLocation(&locations[n]) == island)
		{			
			//==> �� ������ ������
			if(CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if(findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string QuestGetColony(string _city) // �������� ��������� ������� �� ��������� NPChar.city, �� ������ _city
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != _city)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) // �������� ��� �������
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && GetRelation2BaseNation(sti(rColony.nation)) != RELATION_ENEMY && rColony.id != "Panama" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

void initStartState2Character(ref ch)
{// ����� ���������� � ������ ����� ����, ��������� �������� ����� ����������, ���� ������ ������ �������� � if
    NullCharacter.Siege = "";

	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; // boal 28.03.05 ����� ���  My_Cabin_Small

    ch.questTemp.Contraband.relation = 60;
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; // �������� � �����
	ch.questTemp.abordage = 0;   // ������� �������
	ch.questTemp.donate   = 0; // ������������� ������

	ch.questTemp.friend_in_tavern = ""; // ����������� boal
	ch.questTemp.RelationAgentMet = "0"; // ����������� boal

	ch.questTemp.NationQuest = ""; // ������ ������� �������

	ch.GenQuest.BrothelCount = "0"; // ������� ��������� �������
	//ch.GenQuest.Hunter2Pause   = false; // ������� ����� � ����� �� ���� - �� ������ �����
	ch.I_MAP_SHOW = false;  // boal ����� ������� �� ���������
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;// ����� ���������� ��� ������ 0 - ��
	ch.GenQuestFort.FarLocator = true; // ��� ������� ������� �������� � �����

	// ������ ���������
	ch.GenQuest.GhostShip.DeadByMe       = 0;
	ch.GenQuest.GhostShip.KillMe         = 0;
	ch.GenQuest.GhostShip.AskAbout       = 0; // � ������� ��� ���� �������� �� ���������
	ch.GenQuest.GhostShip.lastspeak_date = "";
    GhostShipInit();

    ch.GenQuest.Find_Merchant.lastspeak_date = "";
    ch.GenQuest.ConvoyPassenger = ""; //��������� ����������� �� ������ �������� ���������

	// ==> ��������� ������ ������� �������
	ch.questTemp.State = "";
	// ==> ���-�� ���� �������� ������ ���������� ������ �������, �������� - ��� ���
	ch.questTemp.Waiting_time = "2";
	// ==> ����� �������� ������, ����������� ����� ������, �.�. ������ ������� �� ������ ������� ��������� � ������.
	ch.questTemp.CurQuestNumber = "2";
	//��������� �������� � ���� ��� ����������� �����, ���, � ����� ��� ���� :)
	InitTravelMap();
	// ==> �������� �� ��������� �������� ����� �������
	pchar.RomanticQuest.HorseCheck = -1;
	// ==> ���������� ���� � ������������� ������
	ch.MapsAtlasCount = 0;
	// ==> ����� ���������� ����� (������� �� �������� ������������ ������ ��)
	ch.Flags.Pirate = 5;
	// ==> ����� ��������.
	ch.questTemp.Ascold = "canTakeQuest"; // ���������, ���� ����� "", �� ���� �� ���� �����.
	// ==> ������������
	ch.questTemp.Slavetrader = "canTakeQuest"; //���� �� ������ ����
	// ==> ����� ������ ����.
	ch.questTemp.Azzy = "1";
	// ==> ����� ������ �������� � �������� �������� �� ��������.
	SelectAscoldRendom();
	// ==> ����� ����������-������������
	SelectSlavetraderRendom(); //��� ��������������� �����
	// ==> ����� ��������
	IsabellaInit();
	//==>����� ������� ������ ������ Lipsar
	SilencePriceInit();
	// ==> ����� ��������� ���� Sinistra
	CursedIdolInit();
	// ==> ����� ����� ������ Sinistra
	NovayaRodinaInit();
	// ==>  ����� � ����� ��������� 
	BerglarsInit();
	// ==>  �����
	PoormansInit();
	// ==>  ���-�� ����, ��������� �������
	pchar.questTemp.HorseLoot = 0;
	// ==>  ���-�� ��������� �� �������
	pchar.questTemp.HorseQty = 0;
	// ==> ���������� �� ��� � ���������� ��������
	PearlGen_SetSantaCatalina("none");
	PearlGen_SetTeno("none");
	// ==> ��������������
	QuestionsInit();
	SeaQuestionsInit(); //02/02/08
	// ==> �������� ���� �� ������ ������
	ch.questTemp.jailCanMove = false;
	OfficerGirlInit();
	// ==> ���������
	OfficerMushketerInit();
	// ==> ������� ���
	ch.questTemp.LSC = false;
	ch.questTemp.LSC.checkBoxes = false; //���� �������� �������� � �������	
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1 = "location";
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.FirstLoginLostShipsCity.function = "FirstLoginLostShipsCity";
	// ==> ����� ��������� ����� �����
	ch.questTemp.BlueBird = "begin";
	ch.questTemp.BlueBird.City = "";
	ch.questTemp.BlueBird.count = 0;
	// ==> ��������� ����� �� �������
	ch.questTemp.Sharp = "begin";
	ch.questTemp.Sharp.City = "";
	ch.questTemp.Sharp.count = 0; //������� ���-�� �������
	ch.questTemp.Sharp.brothelChance = 1; //�������, ���� ��������� ����� ����� � �������
	ch.questTemp.Sharp.SeekSpy = "begin"; //��������� ����� �� ������ ����������� �����
	// ==> ��������� �������
	PiratesLineInit();
	// ==> ����� ������ �������, ������ �� ������ �� ��������
	ch.questTemp.different = "free";
	// ==> ������� ����� homo
	ch.questTemp.CapBloodLine = true;
	ch.questTemp.WhisperLine = true;
	ch.questTemp.CapBUnarmed = false; //�� ����� �� �������� - false
	// ==> ������� ������������
	ch.questTemp.Teno = "begin";
	pchar.quest.Teno_startInShore.win_condition.l1 = "location";
	pchar.quest.Teno_startInShore.win_condition.l1.location = "Shore53";
	pchar.quest.Teno_startInShore.function = "Teno_startInShore";
	//������������ �����
	LocatorReloadEnterDisable("Shore_ship3", "reload1", true);
	ch.questTemp.MC = "begin"; //���� ������	
	pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
	pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
	pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
	//�������� � ����
	ch.CanGenerateShipSituation = true;
}

//==> eddy. ��������� ��������� '���� �����'.
void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); // Warship. ��������������� �����������-����������������
	// �������� ������������ ��������
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}
	}
	//���� ���� ������� ���, �� ������� �������� �������. ���, ����� ����������.
	if (sti(pchar.questTemp.LSC.checkBoxes))
	{
		LSC_checkBoxes();
	}
	//************** ��.�������, ������ �����. ��������� ����� ���� ���������� ������ *******************
	if (pchar.questTemp.State == "Fr3TakeAnna_WaitMidnight")
	{
		LocatorReloadEnterDisable("Havana_town", "houseS1", false);
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1 = "location";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1.location = "Havana_houseS1";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition = "Fr3TakeAnna_FightInHouse";
		pchar.questTemp.State = "Fr3TakeAnna_DoorIsOpen";
	}
	//************** ��������, ����� ����� ����� �������� ������ �������� *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "DelivMigel")
	{
		pchar.RomanticQuest = "SeeTalkNearHouse"; //�������� �� ����� ������ ���������
        sld = CharacterFromID("MigelDeValdes");
		//������
		sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto24");
        LAi_SetActorType(sld);
		sld.rank = 1; //����� ���� �����
		sld.skill.Fencing = 1;
		sld.skill.Pistol = 1;
		LAi_SetHP(sld, 1, 1);
		DeleteAttribute(sld, "Items");
		GiveItem2Character(sld, "blade1");
		GiveItem2Character(sld, "pistol1");
		GiveItem2Character(sld, "order");
		TakeNItems(sld,"bullet", 1);
		TakeNItems(sld,"GunPowder", 1);
		//��������� � �����������
		LAi_group_Delete("EnemyFight");
        sld = CharacterFromID("Husband");
        sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto25");		
        for (i=8; i<=9; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 30, PIRATE, 1, true));
			FantomMakeCoolFighter(sld, 30, 80, 70, "blade33", "pistol3", 100);			
			LAi_SetStayType(sld);
			if (i==8) ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto7");
			else ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto26");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		SetTimerCondition("Romantic_DeadBrother_Cancel", 0, 0, 1, false);
	}
	//************** ��������, �������!!!! *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "WaitBeginWidding")
	{
		pchar.RomanticQuest = "BeginWidding";
		pchar.quest.Isabella_widding.win_condition.l1 = "locator";
		pchar.quest.Isabella_widding.win_condition.l1.location = "SanJuan_church";
		pchar.quest.Isabella_widding.win_condition.l1.locator_group = "quest";
		pchar.quest.Isabella_widding.win_condition.l1.locator = "detector1";
		pchar.quest.Isabella_widding.function = "Isabella_widding";
		sld = CharacterFromID("Isabella");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld , "SanJuan_church", "goto",  "goto11");
		sld.dialog.currentnode = "TalkWidding";
		//�����
		LAi_SetActorType(CharacterFromID("SanJuan_Priest"));
		SetTimerCondition("Romantic_Widding_Cancel", 0, 0, 1, false);
	}
	//************** ������ ������ � ������ *******************
	if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard"))
	{
		if (pchar.questTemp.different.Church_NightGuard == pchar.location)
		{
			if (!CheckAttribute(pchar, "pchar.quest.ChurchNightGuard_exitFromLoc") && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1 = "ExitFromLocation";
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1.location = pchar.location;
				pchar.quest.ChurchNightGuard_exitFromLoc.function = "ChurchNightGuard_exitFromLoc";
				DoQuestFunctionDelay("ChurchNightGuard_timerInChurch", 10.0 + frand(10.0));
			}
		}
		else
		{	//�� �� ��������� � ������ ������ � ������ �������
			string sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTitle, "Church_NightGuard", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));			
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterReputation(pchar, -20);
		}
	}
	//************** ������� ���, ������� � �������� ������� *******************
	if (pchar.questTemp.LSC == "toWineCellar")
	{
		if (GetHour() < 1)
		{
			pchar.questTemp.LSC = "toWineCellarGone";
			sld = characterFromId("LSCBarmen");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FleuronTavern", "rld", "stay1");
			PChar.quest.LSC_returnBarmen.win_condition.l1            = "Timer";
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.hour  = 1;
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			PChar.quest.LSC_returnBarmen.function = "LSC_returnBarmen";
		}
		else pchar.questTemp.LSC = "toWineCellarLate";
	}
	//************** ������� ���, ������� � �������� ��� ������������� *******************
	if (pchar.questTemp.LSC == "toInterception")
	{
		if (pchar.location == "FleuronTavern" && pchar.location.locator == "reload2")
		{
			DoQuestFunctionDelay("LSC_scriptInterception", 10.0 + frand(20));
		}
		else
		{
			pchar.questTemp.LSC = "InterceptionLate";
			AddQuestRecord("ISS_MainLine", "19");
		}
	}
	//************** ������� ���, ����� ������� ������� � ������ ���� *******************
	if (CheckAttribute (pchar, "questTemp.LSC.Armo"))
	{
		//������ ������ �����
		if (sti(pchar.questTemp.LSC.Armo) == 1 || sti(pchar.questTemp.LSC.Armo) == 3 || sti(pchar.questTemp.LSC.Armo) == 5)
		{
			if (pchar.location == "LostShipsCity_town" && GetHour() < 2)
			{
				LAi_group_Delete("EnemyFight");
				sld = characterFromId("Casper_" + pchar.questTemp.LSC.Armo);
				sld.BreakTmplAndFight = true; //��������� �� �����
				sld.reactionOnFightModeOn = true; //��������� �� ������������ ������
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
				LAi_ActorGoToLocator(sld, "reload", "reload65", "LSC_casperIsGone", -1.0);
				sld.talker = 11;
				LAi_Character_CanDialog(sld, pchar)
				pchar.questTemp.LSC.Armo.casperIdx = sld.index; //�������� ������, ���������� �� ������
				//������ �� ��������, ���� �� ������
				pchar.quest.LSC_checkCasperDead.win_condition.l1               = "Location_Type";
				pchar.quest.LSC_checkCasperDead.win_condition.l1.location_type = "LSC_inside";
				pchar.quest.LSC_checkCasperDead.win_condition.l2            = "Timer";
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.hour  = 2;
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.function = "LSC_checkCasperDead";
				pchar.quest.LSC_checkCasperDead.casperIdx = sld.index;
			}
			else
			{
				pchar.questTemp.LSC.Armo = 11; //�������� �������
			}
		}
	}
	//************** ��������� "��������� �������" *********************************
	if(CheckAttribute(pchar, "questTemp.ReasonToFast"))
	{
		if(pchar.questTemp.ReasonToFast == "SpeakHorse") // �� ������ � �����
		{
			AddQuestRecord("ReasonToFast", "2");	
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","�"));			
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(pchar.questTemp.ReasonToFast == "MeetPatrolFail") // � ����� ������ �� ���� ��� ����� �� �������
		{
			AddQuestRecord("ReasonToFast", "3");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("��","���"));		
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.PatrolLocation"))
		{
			if(CheckAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)],"DisableEncounters"))
			{
				DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			}
		}	
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.end"))
		{
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}	
	}
	//************** ��������� "�������� �� ��������� �������" **********************
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		ShipSituation_CheckConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}
	//************** ������� ���-����� 5 � 20 ����� ������� ������ *******************
	if (GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); //Id ����
				capIndex = GetCharacterIndex(sName);
    			//---------- ����� ------------
    			if (capIndex == -1)
    			{
					//���������. ���� ����� ��� ������ - ��������� ���
					/*if (CheckActiveQuest(arCapBase.Tilte1))
					{
						CitizCapIsDead_CloseQuest(arCapBase, sName);
					}*/
					DeleteAttribute(arBase, sName);
					Qty --; //��� ���������� ������ ����� ��� �������� ������ � ����
					a--;
				}
				//---------- ��� ------------
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						//if (characters[capIndex].location == "none" && characters[capIndex].quest == "InMap")
						//{
							Cap_SetMapAgain(&characters[capIndex], arCapBase);
						//}
					}
				}
    		}
		}
	}
}

//������ ������, ���� ��������� ���� ����� �� �����
void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	//������� ������������� ������
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	pchar.quest.(sTemp).over = "yes";
	//---------- ���-������������ -------------
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		//������� ���������� �� ������ ������������
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; //����������� ������ ���� ������ ��� ��������
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes";
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}

//����������������� �� ����� ������, �� ����������� ����
void Cap_SetMapAgain(ref sld, aref arCapBase)
{
	//� ������� ������ ����
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	switch (arCapBase.quest)
	{
	case "mushket":
		if (sld.cityShore == sld.quest.targetShore)
		{
			sld.quest.targetShore = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "citizen":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "robber":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "jornal":
		if (sld.quest.baseShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
		}
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "Danielle":
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	}
	//������ ����� �������� �� Id ���� � ���� ���-�����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//����� ������, ������ � �������
void BerglarsInit()
{
	//Korsar Maxim - ������� ����� ������������� ������ ��� ������ (��� ��-�� ����� ������ ����������.), ������� ������ ��� �������� � ��������������� ����� � ������� ���������.
	ref sld;
	pchar.questTemp.tugs.berglarState = 1; //�������
	//============> ��������� � ����-������
	pchar.questTemp.tugs.berglarSentJons = "SentJons_TownCave"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarSentJons.hp = 160; //������� HP
	pchar.questTemp.tugs.berglarSentJons.locator = "basement1"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSentJons", "citiz_12", "man", "man", 22, ENGLAND, -1, false));
	sld.name 	= "�������";
	sld.lastname = "����";
	sld.rank = 25;
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry1", 30+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 10460;
	sld.talker = 7; //������ ������
	SetSelfSkill(sld, 10, 100, 70, 100, 70);
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//=============> ��������� �� ���������
	pchar.questTemp.tugs.berglarFortFrance = "FortFrance_Dungeon"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarFortFrance.hp = 180; //������� HP
	pchar.questTemp.tugs.berglarFortFrance.locator = "basement1"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarFortFrance", "citiz_11", "man", "man", 23, FRANCE, -1, false));
	sld.name 	= "�������";
	sld.lastname = "�����";
	sld.rank = 25;
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	TakeNItems(sld, "jewelry2", 25+rand(10));
	sld.money = 12670;
	sld.talker = 7; //������ ������
	SetSelfSkill(sld, 10, 100, 70, 50, 60);
	SetCharacterPerk(sld, "BasicDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//============> ��������� � ������ 
	pchar.questTemp.tugs.berglarMarigo = "Marigo_Cave"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarMarigo.hp = 200; //������� HP
	pchar.questTemp.tugs.berglarMarigo.locator = "gate_back"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarMarigo", "citiz_1", "man", "man", 21, HOLLAND, -1, false));
	sld.name 	= "�������";
	sld.lastname = "����";
	sld.rank = 25;
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
/* 	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade16")); */
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15480;
	sld.talker = 7; //������ ������
	SetSelfSkill(sld, 60, 10, 100, 100, 40);
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//============> ��������� � ������
	pchar.questTemp.tugs.berglarPanama = "Panama_Cave"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarPanama.hp = 200; //������� HP
	pchar.questTemp.tugs.berglarPanama.locator = "gate_back"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarPanama", "citiz_4", "man", "man", 27, SPAIN, -1, false));
	sld.name 	= "����";
	sld.lastname = "������";
	sld.rank = 27;
	sld.city = "Panama";
	sld.location	= "Panama_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry2", 30+rand(5));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15180;
	sld.talker = 8; //������ ������
	SetSelfSkill(sld, 100, 10, 50, 50, 70);
	SetCharacterPerk(sld, "AdvancedDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> ��������� � ���������
	pchar.questTemp.tugs.berglarCartahena = "Cartahena_Cave"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarCartahena.hp = 170; //������� HP
	pchar.questTemp.tugs.berglarCartahena.locator = "gate_back"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarCartahena", "citiz_7", "man", "man", 22, SPAIN, -1, false));
	sld.name 	= "������";
	sld.lastname = "��������";
	sld.rank = 22;
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry1", 40+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15980;
	sld.talker = 7; //������ ������
	SetSelfSkill(sld, 100, 10, 70, 100, 50);
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> ��������� � ����� ��������
	pchar.questTemp.tugs.berglarSantaCatalina = "SantaCatalina_Cave"; //�������� ��� �������� ������
	pchar.questTemp.tugs.berglarSantaCatalina.hp = 230; //������� HP
	pchar.questTemp.tugs.berglarSantaCatalina.locator = "gate_back"; //�������� �������
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSantaCatalina", "citiz_9", "man", "man", 25, SPAIN, -1, false));
	sld.name 	= "�������";
	sld.lastname = "�������";
	sld.rank = 25;
	sld.city = "SantaCatalina";
	sld.location	= "SantaCatalina_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 16450;
	sld.talker = 7; //������ ������
	SetSelfSkill(sld, 10, 10, 100, 50, 80);
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void QuestionsInit()
{
	ref sld;
	//============> ���� ��������, ���������� ����� � ����, �� � ���. ��� �� ��������.
	NullCharacter.questions = 73; //���-�� �������� (��������� � ����, �����. ��������� ������ ��������� !!!)
	NullCharacter.questions.q0 = "��� ���������� ������ ������, ������������ � ������������� �������� ���� �������� �������� � ���������� ����� ����������� ���� �� �����? ���������: ����� ��� ����, ����� �������� ����������� �������� � ����� � ���������� �� �����.";
	NullCharacter.questions.a0 = "�������";
	NullCharacter.questions.q1 = "�������� ��������� ���������� ������� ��� ������� ������� ����?";
	NullCharacter.questions.a1 = "�������";
	NullCharacter.questions.q2 = "��� ���������� ���������� �������������� ������� �� ������, ���������� �� ������, �������� ��� ������� ������ ������ �� ���������� ������?";
	NullCharacter.questions.a2 = "������";
	NullCharacter.questions.q3 = "��� ���������� ��������� ��� �������� ������� ������� ����� ��� �����������?";
	NullCharacter.questions.a3 = "�������";
	NullCharacter.questions.q4 = "��� ���������� ����� �����, ������� �����, � ������� �������� ��� ��� ������ ������������ � ������ � ����� ��� �������?";
	NullCharacter.questions.a4 = "������";
	NullCharacter.questions.q5 = "��� ���������� ��������� ���� ������ ������ ������ ��� �����?";
	NullCharacter.questions.a5 = "�������";
	NullCharacter.questions.q6 = "��� ���������� ���������� ��������� � ������� ����� �������� �����.";
	NullCharacter.questions.a6 = "������";
	NullCharacter.questions.q7 = "��� ���������� ���������� ����� �����, �������� ��� ����������� �����, ����������� ��������������� �������� ����� ���������� � ��������� ����� ���������� ���������?";
	NullCharacter.questions.a7 = "�����";
	NullCharacter.questions.q8 = "��� ��������� �������� ������� ������� ������� � ����� ������ �����?";
	NullCharacter.questions.a8 = "������";
	NullCharacter.questions.q9 = "��� ���������� ���������� ����� �� ������ ������� ��� ��������� ������?";
	NullCharacter.questions.a9 = "������";
	NullCharacter.questions.q10 = "��� ���������� ��������� ����� �� ��������, ������� ��� � ������ �������?";
	NullCharacter.questions.a10 = "������-�������";
	NullCharacter.questions.q11 = "�������� �����, ������� ������ ��� ���������.";
	NullCharacter.questions.a11 = "�����";
	NullCharacter.questions.q12 = "��� ���������� �������������� ���������� �������, ������� ��������� ������ �� ����� �����? ���� ����������, ��� ��� ������ ��� ��������� ������ �� ����, ������� �������� � ������������ ������.";
	NullCharacter.questions.a12 = "�������";
	NullCharacter.questions.q13 = "�������� ���������� ������, �������� ������������ �������.";
	NullCharacter.questions.a13 = "����-�������";
	NullCharacter.questions.q14 = "��� ���������� ������ �������� ��������, �������� ��� �������� ��� � �������������� ���������?";
	NullCharacter.questions.a14 = "����";
	NullCharacter.questions.q15 = "�������� ���������� � �������������� ����� ��� ������� ������ � ������.";
	NullCharacter.questions.a15 = "��������";
	NullCharacter.questions.q16 = "��� ���������� ������ ����, �������� ��� ��������� ������������ ������ ��� ������?";
	NullCharacter.questions.a16 = "����";
	NullCharacter.questions.q17 = "�������� �������������� �����, ���������� ��������� ��������������� � ���������.";
	NullCharacter.questions.a17 = "�����";
	NullCharacter.questions.q18 = "��� ���������� ����, ������� ������ ��� ����������� � ���� ������� ��������� ������� ������ ��� ���� ����� � ���������?";
	NullCharacter.questions.a18 = "������";
	NullCharacter.questions.q19 = "�������� ������ ����� ������ ����� �� �����, ���������� ����� ����-���� � �����-����.";
	NullCharacter.questions.a19 = "��������";
	NullCharacter.questions.q20 = "��� ���������� ������ ����� �������� ��������, �������� ��� ��������� ���� � �����?";
	NullCharacter.questions.a20 = "�����";
	NullCharacter.questions.q21 = "�������� �������� ��������� �������� � ����������.";
	NullCharacter.questions.a21 = "�����-������";
	NullCharacter.questions.q22 = "�������� ��������������� ������� �����, �������� ��� ������ ����� � ����.";
	NullCharacter.questions.a22 = "����";
	NullCharacter.questions.q23 = "��� ���������� �������� ������ �� �������� ����� ������?";
	NullCharacter.questions.a23 = "�������";
	NullCharacter.questions.q24 = "��� ���������� ������ �����, ��������� ������� ���� � �������� ��������� ��� ������� �� ������ �� ����� � �������?";
	NullCharacter.questions.a24 = "��������";
	NullCharacter.questions.q25 = "�������� ������������� ����, ������������� � ����� �����, �������� ��� ������� ������, ����� � ������� �������.";
	NullCharacter.questions.a25 = "���";
	NullCharacter.questions.q26 = "��� ���������� ������� ����� �������� ����������� �����, �� ������� ��������������� �������� ������?";
	NullCharacter.questions.a26 = "��������";
	NullCharacter.questions.q27 = "�������� ������ �������� �������� ��� ����������� ��������� ���� ������ � ����.";
	NullCharacter.questions.a27 = "����";
	NullCharacter.questions.q28 = "�������� ��������� ���������� ������ ��� ��������� ������� ��������� �������.";
	NullCharacter.questions.a28 = "������";
	NullCharacter.questions.q29 = "�������� ���� �����, ������ ����� ������� ������� ����.";
	NullCharacter.questions.a29 = "���������";
	NullCharacter.questions.q30 = "��� ���������� ���������� ������� � ������� ������?";
	NullCharacter.questions.a30 = "������";
	NullCharacter.questions.q31 = "��� ���������� ����������� ����� ������� ������ � �������� ����� �����?";
	NullCharacter.questions.a31 = "����������";
	NullCharacter.questions.q32 = "�������� �������������� ����� �������� ������, ������������ � ����, ����� ��������� �� �����������.";
	NullCharacter.questions.a32 = "�������";
	NullCharacter.questions.q33 = "�������� ����� ����������� �����, ������������� � ������, ������ �� ����� � ��������.";
	NullCharacter.questions.a33 = "������";
	NullCharacter.questions.q34 = "��� ���������� ��������� � ����� ����� ��� �������� ������?";
	NullCharacter.questions.a34 = "����";
	NullCharacter.questions.q35 = "��� ���������� ������� ������-�����?";
	NullCharacter.questions.a35 = "��������";
	NullCharacter.questions.q36 = "��� ���������� �������������� ����� � ����� ��������, ������� ������ � ������� ������� ������� ������?";
	NullCharacter.questions.a36 = "������";
	NullCharacter.questions.q37 = "�������� ������ ����, ������� �������� ������ �������.";
	NullCharacter.questions.a37 = "�������";
	NullCharacter.questions.q38 = "��� ���������� ����, �������� ��� ��������� �������?";
	NullCharacter.questions.a38 = "���";
	NullCharacter.questions.q39 = "�������� ����, ���������� ����� �������, � ������ ������� �������� ���������.";
	NullCharacter.questions.a39 = "������";
	NullCharacter.questions.q40 = "��� ���������� �������, ���������� ��������� � ������?";
	NullCharacter.questions.a40 = "������";
	NullCharacter.questions.q41 = "�������� ������ ����� ������ ����� �� �����, ���������� ����� �����-���� � ������ ����.";
	NullCharacter.questions.a41 = "�������";
	NullCharacter.questions.q42 = "��� ���������� ���������� ������?";
	NullCharacter.questions.a42 = "������";
	NullCharacter.questions.q43 = "��� ���������� ���������� �������, ��� �������� ������, ����� � �������� ����?";
	NullCharacter.questions.a43 = "�������";
	NullCharacter.questions.q44 = "�������� �����, �� ������� ������ ������� �� ����� ������ �� ����.";
	NullCharacter.questions.a44 = "�����";
	NullCharacter.questions.q45 = "�������� ����� ������� ���� �� ���������� �������� �����.";
	NullCharacter.questions.a45 = "�������";
	NullCharacter.questions.q46 = "��� ���������� �������������� ��� �������, �������� ������ �����, ������� ��������� ��������� ��� �������?";
	NullCharacter.questions.a46 = "����";
	NullCharacter.questions.q47 = "�������� ������ �����, �� ������� �������� ������� �����.";
	NullCharacter.questions.a47 = "���";
	NullCharacter.questions.q48 = "��� ���������� ����, �������� ��� ���������� ��������� ������ �����?";
	NullCharacter.questions.a48 = "������";
	NullCharacter.questions.q49 = "�������� ������, � ������� ����������� ����� ����� ������.";
	NullCharacter.questions.a49 = "�����";
	NullCharacter.questions.q50 = "��� ���������� ���������� ������, �������� ������������ ������ �����?";
	NullCharacter.questions.a50 = "�������";
	NullCharacter.questions.q51 = "�������� ����� ����� ����������� ��� �������������� �����, ���������� �� �����.";
	NullCharacter.questions.a51 = "��������";
	NullCharacter.questions.q52 = "��� ���������� ����������� ���� ��� ������ ����� ����� �� �����������?";
	NullCharacter.questions.a52 = "���";
	NullCharacter.questions.q53 = "�������� ����� �������������� �����, ������� ���������� ����������� � ������, � ������ ��������������� �� ����.";
	NullCharacter.questions.a53 = "�������";
	NullCharacter.questions.q54 = "��� ��������� ������ ������� ������� � ������� ������ � ����� ������ �����, ������� ������� �������� ��� �����?";
	NullCharacter.questions.a54 = "������";
	NullCharacter.questions.q55 = "��� ��������� ������ ������� ������� � ������� ���� � ����� ������ �����?";
	NullCharacter.questions.a55 = "�������";
	NullCharacter.questions.q56 = "��� ���������� ���������� ������, �������� ������������ ��������?";
	NullCharacter.questions.a56 = "��������";
	NullCharacter.questions.q57 = "�������� ������, �������� ��� ������� ��������� ���, �������, ���������� ������ � ������� �������.";
	NullCharacter.questions.a57 = "���";
	NullCharacter.questions.q58 = "��� ���������� ����������� ����� ���� �������� ������� ������?";
	NullCharacter.questions.a58 = "���������";
	NullCharacter.questions.q59 = "��� ���������� �������������� �������, � ������� ������� ������ ����� ���������� ������ ������ �� ������?";
	NullCharacter.questions.a59 = "�����";
	NullCharacter.questions.q60 = "��� ���������� ������� ������ � �������� ����� ��������� �����, ��� ��������� ��������� ������� � ��������������� �������?";
	NullCharacter.questions.a60 = "������";
	NullCharacter.questions.q61 = "��� ���������� ������� �����, ��������� ������������� ����� ������ ��� ������� � ���� �� ������?";
	NullCharacter.questions.a61 = "������";
	NullCharacter.questions.q62 = "��� ���������� ������, ������������ ������ ���� ������ � ����������� ����� ����� � ������������ ����� � �������� ���������?";
	NullCharacter.questions.a62 = "����";
	NullCharacter.questions.q63 = "��� ���������� ���������� �����, ���������� ����� ������� �����?";
	NullCharacter.questions.a63 = "��������";
	NullCharacter.questions.q64 = "��� ���������� ����� �����, ������������ ��� ��������� ��� ������ ������-���� ��������?";
	NullCharacter.questions.a64 = "����";
	NullCharacter.questions.q65 = "��� ���������� ������� �������������� ����� ��� �������� ������, �� ���� ��� ������������ ���� � �������?";
	NullCharacter.questions.a65 = "�����";
	NullCharacter.questions.q66 = "��� ���������� ���������� �������������� ������ � ����� �����������, �������� ��� ���������� ��������� ������ �����?";
	NullCharacter.questions.a66 = "���������";
	NullCharacter.questions.q67 = "�������� ������� ���������� ���� ��� ����� � ����� ��������� ����������� ��� ��������� ������ � ����.";
	NullCharacter.questions.a67 = "�����";
	NullCharacter.questions.q68 = "�������� �������� ������� ��������� �������� � ��������� ���� � ������-�������� ����� ����.";
	NullCharacter.questions.a68 = "�����";
	NullCharacter.questions.q69 = "�������� �������� ������� ��������� ������� � ��������� ���� � ������-�������� ����� ����.";
	NullCharacter.questions.a69 = "����";
	NullCharacter.questions.q70 = "�������� ������ ��� ������� ������������ �������������, ������������ ������������ ��������?";
	NullCharacter.questions.a70 = "������ ��� ����";
	NullCharacter.questions.q71 = "��� ���������� ������ �������� ����������� ����-������� �������� � �������? ���� �������� � 1626.";
	NullCharacter.questions.a71 = "��� ���������";
	NullCharacter.questions.q72 = "����� ���������� ����, �����, ������� �������, ����������� ��������� � ��������� �������� ��������� I ��� �����(����� ��������� ������) � 1618 ����?";
	NullCharacter.questions.a72 = "��� ������ �����";
	NullCharacter.questions.q73 = "��� ������ �� ������� ���� ���������� �� ����� ����� ����� � �������?";
	NullCharacter.questions.a73 = "��������� ����";
	//============> ������������ � ���������
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortSpein", "citiz_"+(rand(11)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortSpein";
	sld.greeting = "cit_common";
	sld.talker = 4; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	SetSelfSkill(sld, 10, 10, 10, 10, 10);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> ���������������� � ����������
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad", "girl_"+(rand(7)+1), "woman", "towngirl", 5, HOLLAND, -1, false));
	sld.rank = 5;
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Villemstad";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//============> ���������������� � ����-�-������
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax", "girl_"+(rand(7)+1), "woman", "towngirl", 5, FRANCE, -1, false));
	sld.rank = 5;
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortPax";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 6; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//============> ������������ � ���-�����
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSanJuan", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "SanJuan";
	sld.location	= "SanJuan_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "SanJuan";
	sld.greeting = "cit_common";
	sld.talker = 6; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> ������������ � ������
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsCumana", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Cumana";
	sld.greeting = "cit_common";
	sld.talker = 6; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> ������������ � ���� �����
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortRoyal", "girl_"+(rand(7)+1), "woman", "towngirl", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortRoyal";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> ������������ � ��������
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSantiago", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Santiago";
	sld.greeting = "cit_common";
	sld.talker = 5; //������ ������
	sld.quest.numQuestion = SelectQuestions(); //����� �������
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");

}
// ==> ��������� ���� ��������, ��������� � ������ ����
int SelectQuestions()
{
	bool bOk = true;
	int iTemp;
	string sTemp;
	while (bOk)
	{
		iTemp = rand(sti(NullCharacter.questions));
		sTemp = "m" + iTemp;
		if (!CheckAttribute(NullCharacter, "questions" + sTemp))
		{
			NullCharacter.questions.(sTemp) = true;
			break;
		}
	}
	return iTemp;
}
// -- ����� --
void PoormansInit()
{
	ref sld;
	//����� � ����-������
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//����� � ����������
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//����� � ������
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ��������
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ���������
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ������
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � �������
	/*sld = GetCharacter(NPC_GenerateCharacter("Villemstad_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto24";
	sld.forStay.locator = "goto24"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto23";
	sld.forSit.locator1 = "goto7"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto8";
	LAi_SetLoginTime(sld, 9.0, 22.0);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");*/
	//����� � ���-����, ���������
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//����� � ������
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ���� �����
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//����� � ����-��-������, ���������
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//����� �� ������
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//����� � ����� �����
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ����-�-�����, ���������
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//����� � ��������
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//����� � ������, ��� ������
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//����� � �������
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//����� � ���� ������, ��������
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //��� ��������� � ������ �������
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; //��� ��������, ��� ��������� � ������ �������
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//�������� �����
	sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man", 30, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "�����";
	sld.talker = 8; //������ ������
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "Begin_PoorKill";
	sld.greeting = "Gr_OliverTrast";
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetHP(sld, 100.0, 100.0);
	sld.greeting = "Gr_OliverTrast";
	//���������� ��������
	sld = GetCharacter(NPC_GenerateCharacter("OffMushketer", "MusketeerEnglish_1", "man", "man", 25, ENGLAND, -1, false));
	sld.name = "������";
	sld.lastname = "������";
	sld.location	= "PortSpein_houseH3";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "OffMushketer";
	sld.HalfImmortal = true;  // ��������
	SetSelfSkill(sld, 80, 10, 2, 100, 80);
	SetShipSkill(sld, 5, 5, 2, 10, 5, 20, 10, 10, 70);
	SetSPECIAL(sld, 7, 4, 9, 3, 8, 7, 9);
	LAi_SetSitType(sld);
	sld.greeting = "cit_common";
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HPPlus");
	SetCharacterPerk(sld, "Medic");
	SetCharacterPerk(sld, "GunProfessional");
	DeleteAttribute(sld, "Items");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.HoldEquip = true; //���������� ������ ��� ������ ����������
}

//=============== ������� ���� ====================
string Sharp_choiceAction()
{
	string sBack;
	ref sld;
	//������ ����� � �����, ���� �� ������ ��� ���-��
	Map_ReleaseQuestEncounter("Sharp");
	group_DeleteGroup("Sharp_Group");
	if (rand(3) != 2 && sti(pchar.questTemp.Sharp.count) < 5)
	{	//��� �������, ���������� �� � ������ �����
		string sCity = pchar.questTemp.Sharp.City; //���������� ����, �������� ��� ��
		pchar.questTemp.Sharp.City.rumour = true; //���� ���� ���� � ������
		pchar.questTemp.Sharp.City = GetSharpCity(); //����� ����� 
		sBack = GetSharpRumour_toCityTarget();
		pchar.questTemp.Sharp.count = sti(pchar.questTemp.Sharp.count) + 1; //�������
		AddQuestRecord("SharpPearl", "2");
		AddQuestUserData("SharpPearl", "sOldTarget", XI_ConvertString("Colony" + sCity + "Dat"));
		AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
		if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
		{
			AddQuestUserData("SharpPearl", "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Dat"));
		}
		//��������� ����� ����� �� �����
		sld = characterFromId("Sharp");
		string sGroup = "Sharp_Group";
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "���� '����������'";
		string sColony= SelectAnyColony(sCity); //�������, ������ ������ ����
		int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City))+3; //���� ������� ���� � �������
		Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
	}
	else
	{
		if (rand(5) < 4)
		{
			sBack = GetSharpRumour_inIsland();
			pchar.questTemp.Sharp.Island = GiveArealByLocation(loadedLocation);
			pchar.questTemp.Sharp.count = 0; //������� ����� ��� ����. ����
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //���� �� �������
			pchar.questTemp.Sharp.price.evil = rand(1); //������ ��� ����, ��� ������
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1 = "location";
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1.location = pchar.questTemp.Sharp.Island;
			Pchar.quest.Sharp_loginNearIsland.function = "Sharp_loginNearIsland";
			AddQuestRecord("SharpPearl", "3");
			SaveCurrentQuestDateParam("questTemp.Sharp");
			Log_QuestInfo("��������� �� ������.");
		}
		else
		{
			sBack = GetSharpRumour_inCity();
			pchar.questTemp.Sharp.count = 0; //������� ����� ��� ����. ����
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //���� �� �������
			pchar.questTemp.Sharp.price.evil = rand(1); //������ ��� ����, ��� ������
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "CitySharp";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol", LAi_FindFarLocator("patrol", locx, locy, locz));
			AddQuestRecord("SharpPearl", "11");
			Log_QuestInfo("��������� �� �����.");
		}
	}
	return sBack;
}

//���� ����� ����� 
string GetSharpCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (GetBaseHeroNation() != PIRATE)
	{
	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //�� �� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //�� �� ���� ������
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[rand(howStore-1)];
	return colonies[iRes].id;
}
//����� �� ���������
string GetSharpRumour_default()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "������� ���� ��� �����, � ��� �����. �� ������ ��� � ������ ���, � ���� ���� - �� ����."; break;
        case 1: sRumour = "������� ���� ������� � ��� �����. ��� �� ������ � �� ����, � ��� ��� ����� ���."; break;
        case 2:	sRumour = "������� ���������� ���� ���� �� ������ ��������� �� ����..."; break;
    }
	return sRumour;
}
//����� � ������ �����
string GetSharpRumour_toCityTarget()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "������� ���������� ���� ��� � ��� � ������ �, ��� ������, ��������� '����������'... �� ������ ��� ����� ���. �� ������ �� ���� � " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 1: sRumour = "������, ������� ���� ��� � ������ �������. ������� �����, ���� ����������... ������, ������, ��� �� ������� ��� �����. ������� �� ���� � " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 2:	sRumour = "�� ������, ������� ��� ������ ����� ������������ ������� ����. ��, � ������ �������� �������������, ������ ���������� �������� '�� �����' �� ���������. ����... � ������ ��� ��� � ��� � ������. �������, �� ���� � " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ". ����� �� �������..."; break;
    }
	return sRumour;
}
//����� � ������
string GetSharpRumour_inIsland()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "�� ������, ������� ���� ������ ��� ����� �� ������ �� ����� �����. ���� �� �� ������� � ��� ���� �����, �� ������� �� ��� ����� � �����."; break;
        case 1: sRumour = "������� ����... �� ���, ��� ��� �������. ������, �� ������ ��� ������� ��� �����. ���� �� ������������, �� ������� ��� ������� � ��������� �����."; break;
        case 2:	sRumour = "���������� ���� ��������� � ��� ����� ����� �� ������ ����� � ����."; break;
    }
	return sRumour;
}
//����� � ������
string GetSharpRumour_inCity()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "���� ����� ����� ������� ���� ���������� �� ���� ����� � ����. ����� ����� �� ������, �������, ��� �� � �������..."; break;
        case 1: sRumour = "������ ��� �� ����� �������� ���������� � ��������� ������. ��������, ������ ��, ���..."; break;
        case 2:	sRumour = "������� ���� ������ ������ �� ������. � �� ��� ����, ���� �� �� ������� � ��������� ���..."; break;
    }
	return sRumour;
}

//=============== ������ ����� �����.  ====================
string BlueBurd_setTradeShip()
{
	pchar.questTemp.BlueBird.Island = GiveArealByLocation(loadedLocation);
	Pchar.quest.BlueBird_loginFleut.win_condition.l1 = "location";
	Pchar.quest.BlueBird_loginFleut.win_condition.l1.location = pchar.questTemp.BlueBird.Island;
	Pchar.quest.BlueBird_loginFleut.function = "BlueBird_loginFleut";
	pchar.questTemp.BlueBird.nation = colonies[FindColony(pchar.questTemp.BlueBird.City)].nation; //����� �������, ������ ��������
	aref aName;
	makearef(aName, pchar.questTemp.BlueBird);
	SetRandomNameToShip(aName);
	AddQuestRecord("Xebeca_BlueBird", "10");
	AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Dat"));
	AddQuestUserData("Xebeca_BlueBird", "sShipName", "'" + aName.Ship.Name + "'");
	AddQuestUserData("Xebeca_BlueBird", "sCity_2", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Gen"));
	AddQuestUserData("Xebeca_BlueBird", "sTradeName", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	SaveCurrentQuestDateParam("questTemp.BlueBird");
	return GetBlueBirdRumour_Ship(); //����� �����
}
//����� �� ������, ������� �� ������� ��������
string GetBlueBirdRumour_Ship()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "�� ������, ������� ��������, " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + ", ����� ���������� ����������� ����� '" + pchar.questTemp.BlueBird.Ship.Name + "' � ������ ���� �� �������. ������� ����� ����� �� �����."; break;
		case 1: sRumour = "��, � ���� � ������ ���������� ������������� ���� �������! " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + " ����� �������� ����������� ����� '" + pchar.questTemp.BlueBird.Ship.Name + "' �� �������, ��� ������ ��� ����� �� ������ �����."; break;
        case 2:	sRumour = "�-��, � " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + " ��� �������� � ��������. ������ ����� ��� �������� ����� ��� ���������� � �����, � ������� ���� ��� ���������� � ���. ����� '" + pchar.questTemp.BlueBird.Ship.Name + "' ���� ����� �� �������, ��� ��!"; break;
    }
	return sRumour;
}
//======================= ��������� ������� ===================================
void PiratesLineInit()
{
	ref sld;
	pchar.questTemp.piratesLine = "begin";
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirate1", "officer_9", "man", "man", 20, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "�����";
	sld.rank = 20;
	sld.city = "PuertoPrincipe";
	sld.location	= "PuertoPrincipe_town";
	sld.location.group = "goto";
	sld.location.locator = "goto7";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PiratesMan1";
	sld.greeting = "Gr_EvilPirate";
	sld.talker = 8; //������ ������
	sld.TiedItems.itm1.model = "HandsItems\meet";
	sld.TiedItems.itm1.locator = "Saber_hand";
	sld.TiedItems.itm2.model = "HandsItems\cup";
	sld.TiedItems.itm2.locator = "Saber_hand";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
}

//���� ����� ������������ �����, ��������� ������� ���������� � ����������
string GetQuestNationsCity(int _nation)
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) //�� �� ���� ������
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

//���� �� ��������� �������, ���� ����� �������
string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		/* if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].id != "Caiman" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� �� ���� ������ */
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].id != "Caiman" && colonies[n].nation != "none"  && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� �� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

//���� ����� ������������ �������, ���� ����� �������
string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City) != colonies[n].islandLable) //�� �� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City1) != colonies[n].islandLable && GetIslandByCityName(_City2) != colonies[n].islandLable) //�� �� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

ref CheckLSCCitizen()
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[3]);
	if (sSeeked == "�������" || sSeeked == "�������a")
	{
		return characterFromId("LSCMayor");
	}
	if (sSeeked == "����������" || sSeeked == "�����������" || sSeeked == "���������"|| sSeeked == "����������" || sSeeked == "������ �������" || sSeeked == "������� �������")
	{
		return characterFromId("LSCBarmen");
	}
	if (sSeeked == "����������" || sSeeked == "����������")
	{
		return characterFromId("LSCwaitress");
	}
	if (sSeeked == "��������" || sSeeked == "�������")
	{
		return characterFromId("Mechanic");
	}
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "city") && rCharacter.city == "LostShipsCity")
		{
			sTemp = GetStrSmallRegister(rCharacter.name + " " + rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			else
			{
				sTemp = GetStrSmallRegister(rCharacter.name);
				if (findsubstr(sSeeked, sTemp , 0) != -1)
				{
					return rCharacter;
				}
			}
		}
	}
	return &NullCharacter;
}

string WhereLSCCitizen(ref rCharacter)
{
	string sShip = "none";
	string sTemp;
	if (rCharacter.location	== "LostShipsCity_town")
	{
		sTemp = rCharacter.location.locator;
		sTemp = strcut(sTemp, 4, 5);
		switch (sTemp)
		{
			case "01": sShip = "�� ��������� '��������', ��� ������"; break;
			case "02": sShip = "�� ������� '��������'"; break;
			case "03": sShip = "�� ������ '����� �����'"; break;
			case "04": sShip = "�� ������� '����������', ��� �������"; break;
			case "05": sShip = "�� ��������� '������', ��� �������"; break;
			case "06": sShip = "�� ������ '�����', � ������� �����"; break;
			case "07": sShip = "�� ������ '�����', � �������� �����"; break;
			case "08": sShip = "�� ������� '������', ��� �������"; break;
			case "09": sShip = "�� ������ '�����'"; break;
			case "10": sShip = "�� ������� '���������'"; break;
			case "11": sShip = "�� ������� '��� ��������', ��� ���������� ��������"; break;
			case "12": sShip = "�� ����� '��� ��������', � ������� �����"; break;
			case "13": sShip = "�� ����� '��� ��������', � �������� �����"; break;
			case "14": sShip = "�� ����� '����� ����������'"; break;
			case "15": sShip = "�� ������� '���'"; break;
			case "16": sShip = "�� ������� '�������'"; break;
		}
	}
	else
	{
		switch (rCharacter.location)
		{
			case "AvaShipInside3": sShip = "� ������� '���'"; break;
			case "CarolineBank": sShip = "� ������� '��������'"; break;
			case "CeresSmithy": sShip = "�� ������ '����� �����'"; break;
			case "EsmeraldaStoreBig": sShip = "� ������� '����������', � ��������"; break;
			case "FenixPlatform": sShip = "� ��������� '������'"; break;
			case "FernandaDiffIndoor": sShip = "�� ������ '�������� ���������'"; break;
			case "FleuronTavern": sShip = "� ��������� '������', � �������"; break;
			case "FurieShipInside2": sShip = "� ������ '�����'"; break;
			case "GloriaChurch": sShip = "� ������� '������', � ������"; break;
			case "PlutoStoreSmall": sShip = "�� ����� '�����'"; break;
			case "ProtectorFisher": sShip = "� ������� '���������'"; break;
			case "SanAugustineResidence": sShip = "� ������� '��� ��������', � ���������� ��������"; break;
			case "SanGabrielMechanic": sShip = "� ����� '��� ��������'"; break;
			case "SantaFlorentinaShipInside4": sShip = "� ����� '����� ����������'"; break;
			case "TartarusPrison": sShip = "� ��������� '��������', � ������"; break;
			case "VelascoShipInside1": sShip = "� ������� '�������'"; break;
		}
	}
	return sShip;
}

//������ ������� ������� ������. �������� � ����� ����, ������� ������� � ����������� �������
void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //���� � ������
	sld.City = sld.quest.targetCity; //�������� �������� ������ ��������
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	/*int iColony = FindColony(sld.City);
	string sGroup = "PorpmansShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);*/

	//������ ����� ������� ����� ����� � ����
	int Qty = rand(4)+3;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; //� ���������� �������� Id ����
	//������� ���� � ���� ��� �������� ����� �� ����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//���� ����, ��� ��� � ������
	AddSimpleRumourCity(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ������ � ������. �������, ��� ����� " + GetFullName(sld) + ". �� ������ ������� ���� � ���������� �����.", 
		"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ������ ����� ������� � ���������� �����.", 
		"���� �� ������ ���������� � ��������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ����� �������� � ���������� �����. " + GetFullName(sld) + " ������ ���..."), sld.City, Qty, 1, "none");
}
//������ ������� ������� ������. ������� � �������� �� ������
void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//��������� ����-����. �������� � ����� ����, ������� ������� � ����������� �������
void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; //���� ���� ����� � �����
	sld.City = sld.quest.targetCity; //�������� �������� ������ ��������
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //����� �����, ��� � � ������

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	//������ ����� ������� ����� ����� �� �����
	int Qty = rand(5)+4;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //� ���������� �������� Id ����
	//������� ���� � ���� ��� �������� ����� �� ����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//���� ����, ��� ��� �� �����
	AddSimpleRumourCity(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ����� � ����� �� �����. �������, ��� ����� " + GetFullName(sld) + ". �������� ���, ����� � ���, �� ����� �� ������ ������.", 
		"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ������ ����� ���������, ������ ���� ����� �� ������ � ����. ������� ����� �� �����, �� ������� � ����� �� �������, ������������ ���������� �� �������. � � ������� ���?..", 
		"���� �� ������ ���������� � ��������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� �������� � ����. " + GetFullName(sld) + " ����� �� ��� �����... � �����, �� ������ ����� � �����, �� �� ����� �� ������. ��������� ������� ����, ���� � �������� ������ ������������ �� �����."), sld.City, Qty, 1, "none");
}
//��������� ����-����. ������ � �������� �� ������
void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "����", "����"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//������ ����� ����������
void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //���� ���� ����� �� ������
	sld.City = sld.quest.targetCity; //�������� �������� ������ ��������
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //����� �����, ��� � � ������
	if (rand(1))
	{	//����� � ������
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		//���� ����, ��� ��� �� �����
		AddSimpleRumourCity(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' � ������. �������, ��� ����� " + GetFullName(sld) + ".", 
			"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ������ ����� ������� � ������.", 
			"���� �� ������ ���������� � ��������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ������� ��� � �� ������. " + GetFullName(sld) + " ����� �� ��� �����..."), sld.City, Qty, 1, "none");
	}
	else
	{	//����� �� ����� � �����
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		//���� ����, ��� ��� �� �����
		AddSimpleRumourCity(LinkRandPhrase("������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ��������� � ����� �� �����. �������, ��� ����� " + GetFullName(sld) + ".", 
			"�� ������, �������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' ������ ����� ������� � ����� �����. ��� ������� ����� �� �����.", 
			"���� �� ������ ���������� � ��������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', �� ������� ��� ������� � ����� �����. " + GetFullName(sld) + " ����� �� ��� �����..."), sld.City, Qty, 1, "none");
	}
	//������ ����� ������� ����� ����� �� �����
	int Qty = rand(7)+5; //����� ������� ���� ������ �� �����
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //� ���������� �������� Id ����
	//������� ���� � ���� ��� �������� ����� �� ����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//������ ���� �� �������. ������ � �������� �� ������
void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//�������� ������������� ����
void SetMushketFromMapToSea()
{
	ref sld = characterFromId("MushketCap");
	sld.quest = "InShore"; //���� ���� ����� � �����
	sld.City = sld.quest.targetCity; //�������� �������� ������ ��������
	int iColony = FindColony(sld.City);

	string sGroup = "MushketCapShip";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+5));
	Group_SetTaskNone(sGroup);
	//������ ����� ������� ����� ����� �� �����
	int Qty = rand(2)+3;
	string name = "MushketTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetMushketFromSeaToMap";
	//������� ���� � ���� ��� �������� ����� �� ����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//�������� ������
void SetDanielleFromMapToSea()
{
	ref sld = characterFromId("Danielle");
	sld.quest = "InShore"; //���� ���� ����� � �����
	sld.City = sld.quest.targetCity; //�������� �������� ������ ��������
	int iColony = FindColony(sld.City);

	string sGroup = "DanielleGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//������ ����� ������� ����� ����� �� �����
	int Qty = rand(5)+7;
	string name = "DanielleTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetDanielleFromSeaToMap";
	//������� ���� � ���� ��� �������� ����� �� ����
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//������� ����� � ���������
//��������� ����� ������ � �����
void SetShipInBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	locations[n].models.always.ship = "Bridgetown_ship";
	locations[n].models.always.shipreflect = "Bridgetown_shipreflect";
	Locations[n].models.always.shipreflect.sea_reflection = 1;
	locations[n].models.always.locators = "Bridgetown_locatorsShip";
	locations[n].models.day.fonarShip = "Bridgetown_fdShip";
	locations[n].models.night.fonarShip = "Bridgetown_fnShip";
	locations[n].models.day.charactersPatch = "Bridgetown_patchship_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patchship_night";

	locations[n].reload.ship1.name = "reloadShip";
	locations[n].reload.ship1.go = "Cabin";
	locations[n].reload.ship1.emerge = "reload1";
	locations[n].reload.ship1.autoreload = "0";
	locations[n].reload.ship1.label = "cabine";

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "boarding");
	DeleteAttribute(&locations[n], "camshuttle");
	DeleteAttribute(&locations[n], "CabinType");

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bridgetown_town";
	locations[n].reload.l1.emerge = "reloadShip";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Ship";
}
//������ ����� ������ �� ������
void RemoveShipFromBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	DeleteAttribute(&locations[n], "models.always.ship");
	DeleteAttribute(&locations[n], "models.always.shipreflect");
	DeleteAttribute(&locations[n], "models.always.shipreflect.sea_reflection");
	locations[n].models.always.locators = "Bridgetown_locators";
	DeleteAttribute(&locations[n], "models.day.fonarShip");
	DeleteAttribute(&locations[n], "models.night.fonarShip");
	locations[n].models.day.charactersPatch = "Bridgetown_patch_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patch_night";
	DeleteAttribute(&locations[n], "reload.ship1");

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "reload");
	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc0";
    Locations[n].boarding.Loc.Capt = "aloc2";
}

//------------------- ������� ��� ----------------------
//����������� �� ��������
void LSC_checkBoxes()
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{
		loc = &locations[i];
		if (CheckAttribute(loc, "fastreload") && loc.fastreload == "LostShipsCity" && loc.id != "FernandaDiffIndoor")
		{
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName) && sName != "private11")
				{
					makearef(arBox, loc.(sName));
					if (CheckAttribute(arBox, "equip") && rand(1))
					{
						DeleteAttribute(arBox, "items");
						arBox.items = "";
					}
				}
				else break;
			}
		}
	}
}

//������� ���. ��������� ��������� �� ����� �� ����� �����
void LSC_CheckCasperDistance(ref sld)
{
	if (!CheckAttribute(pchar, "questTemp.LSC.Armo.Interrapt"))
	{
		sld.quest.checkCasper = true; //��� ��������� � �� warrior
		pchar.quest.LSC_KillOneCasper.win_condition.l1 = "NPC_Death";
		pchar.quest.LSC_KillOneCasper.win_condition.l1.character = sld.id;
		pchar.quest.LSC_KillOneCasper.function= "LSC_KillOneCasper";
		pchar.quest.LSC_KillOneCasper.casperIdx = sld.index;
		pchar.questTemp.LSC.Armo.Interrapt = true; //����� �� �������� ������ ����������
	}
	float dist;
	if (GetCharacterDistByLoc(sld, "goto", "goto12_4", &dist))
	{
		if (dist < 40.0)
		{
			LSC_CasperIsHelp();
		}
	}
}
//���� ������� �� �������
void LSC_CasperIsHelp()
{
	Log_SetStringToLog("����� ������ ���� �������� �� ����� '��� ��������'.");
	chrDisableReloadToLocation = true;
	pchar.questTemp.LSC = "toSeekMechanikCasperOff";
	//���� ����� �����, �� ������ ����� ����
	pchar.questTemp.LSC.Armo = 15; //���������� � ����� ������� �� ����
	pchar.quest.LSC_KillOneCasper.over = "yes"; 
	pchar.quest.LSC_checkCasperDead.over = "yes"; 
	//������ � �������
	int iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1) ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
	for (int i=1; i<=11; i++)
	{
		iTemp = GetCharacterIndex("Casper_"+i);
		if (iTemp != -1)
		{
			if (characters[iTemp].location != "LostShipsCity_town")
			{
				ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
			}
			else
			{
				if (!LAi_IsDead(&characters[iTemp]))
				{
					LAi_group_MoveCharacter(&characters[iTemp], "PearlGroup_2");
					DeleteAttribute(&characters[iTemp], "quest.checkCasper"); //������ ����� �� �������� ���������� �� ����
				}
			}
		}
	}
	//���������� ������
	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_1", "Mushketer_2", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");

	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_2", "Mushketer_4", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
	//�������������, �� ������ ������
	//LAi_group_SetRelation("PearlGroup_2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	//LAi_group_FightGroups("PearlGroup_2", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("PearlGroup_2", "OpenTheDoors");
}

//����� �� ���� ���� ������, ����� ��������� �����
void LSC_rumourElisHusband()
{
	if (!CheckActiveQuest("ISS_ElisHusband"))
	{
		pchar.questTemp.LSC.ElisHusband = "begin";
		AddQuestRecord("ISS_ElisHusband", "1");
	}
}
//������ �����, ����� ������� ������ � ���������
void LSC_beginElisHusband()
{
	// ��� ���� ������
	ref sld = GetCharacter(NPC_GenerateCharacter("MaximTailor", "shipowner_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = "������";
	sld.lastname = "������";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "quest";
	sld.location.locator = "prison4";
	sld.dialog.filename   = "Quest\LostShipsCity\MaximTailor.c";
	sld.dialog.currentnode   = "InPrison";
	sld.cityTape = "quest"; //��� ���
	sld.greeting = "pirat_common";
	sld.location.hours = 4; //������������ ����� .. �����
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
}

//����� �� �������� ������� ��������
void LSC_rumourLostDecster()
{
	if (!CheckActiveQuest("LSC_findDekster"))
		AddQuestRecord("LSC_findDekster", "1");
}
void LSC_enterAdmiralBox()
{
	if (!CheckAttribute(pchar, "questTemp.LSC.private10"))
	{
		if (CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
		{
			if (pchar.questTemp.LSC.lostDecster == "seekBox")
			{
				AddQuestRecord("LSC_findDekster", "6");
				AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("��","��"));
			}
			else
			{
				iTemp = GetCharacterIndex("LSC_Prisoner1");
				if (iTemp != 1 && CheckAttribute(&characters[iTemp], "quest.decster"))
				{
					AddQuestRecord("LSC_findDekster", "7");
				}
				else
				{
					AddQuestRecord("LSC_findDekster", "9");
					AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("��","��"));
				}
			}
		}
		else
		{
			AddQuestRecord("LSC_findDekster", "8");
			AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("��","��"));
		}
		pchar.questTemp.LSC.lostDecster = "foundAdmiralBox";
		AddSimpleRumourCityTip("�� �������, ��� ��� ������ ������� �����-�� ������ ��� ���� ����. ������ ������ �� ����� ������, ����...", "LostShipsCity", 10, 1, "LSC", "LSC_rumourAdmiralLostKey");
		pchar.questTemp.LSC.private10 = true; //����� ������ �� �����������
	}
}
void LSC_rumourAdmiralLostKey()
{
	//������ ������� ����
	ref sld = ItemsFromID("keyPanama");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item" + (rand(4)+2);
	ChangeItemName("keyPanama", "itmname_keyPanama_LSC");
	ChangeItemDescribe("keyPanama", "itmdescr_keyPanama_LSC");
	SetTimerFunction("LSC_admiralFoundOwnKey", 0, 0, 2); //������ �� ������ ����� �� ��������
	pchar.questTemp.LSC.lostDecster = "admiralLostKey";
	AddQuestRecord("LSC_findDekster", "10");
}

//������
void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}

//�������� ��������� ���� �� ������������ ��� ��� ����������� ������
void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "SkullAztec"))
	{
        //������ ������ ����
        DeleteAttribute(pchar, "AztecSkull");
		pchar.AztecSkull = "";
		//��������� �������� ���� 
		string sTemp;
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.AztecSkull);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "AztecSkull.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.AztecSkull);
    for (i=1; i<=MAX_NUM_FIGHTERS; i++)
    {
		sTemp = "id" + i;
		if (arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}

void SetAztecUsedTotem(ref _location, string _itemId, string _locator)
{
	//-----------------------------------------
	if (_itemId == "Totem_11")    //������� �����
	{
		DeleteAttribute(_location, "gotoFire");
		Log_SetStringToLog("�������� ���� �����");
		pchar.questTemp.Teno = "takeFire";
	}
	//-----------------------------------------
	if (_itemId == "Totem_12") //��������� �������� ������ � ������� ����� (� ��������)
	{
		DeleteAttribute(_location, "private1.closed");
		Log_SetStringToLog("������ �������� ������");
	}
	//-----------------------------------------
	if (_itemId == "Totem_13") //������� ����� 2�
	{
		_location.lockFire.button02.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog("�������� ���� �����");
			pchar.questTemp.Teno = "takeFire";
		}
	}
	if (_itemId == "Totem_14") //������� ����� 2�
	{
		_location.lockFire.button03.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog("�������� ���� �����");
			pchar.questTemp.Teno = "takeFire";
		}
	}
	//-----------------------------------------
	if (_itemId == "Totem_15") //��������� �������� ������ � ������� �����
	{
		DeleteAttribute(_location, "private2.closed");
		Log_SetStringToLog("������ �������� ������");
	}
	//-----------------------------------------
	if (_itemId == "Totem_1" || _itemId == "Totem_2" || _itemId == "Totem_3" || _itemId == "Totem_4" || _itemId == "Totem_5" ||
		_itemId == "Totem_6" || _itemId == "Totem_7" || _itemId == "Totem_8" || _itemId == "Totem_9" || _itemId == "Totem_10")
	{
		int n;
		int num = 0;
		int locIndex = sti(_location.idxTeno); //������ ������������
		string sTemp;
		_location.openGreatTemple = true;
		for (int i=1 ; i<=10; i++)
		{
			sTemp = "idx" + i;
			n = sti(locations[locIndex].temples.(sTemp));
			if (CheckAttribute(locations[n], "openGreatTemple")) num++;
		}
		if (num >= 10)
		{
			DeleteAttribute(&locations[locIndex], "reload.l32.disable");
			DeleteAttribute(&locations[locIndex], "reload.l33.disable");
			DeleteAttribute(&locations[locIndex], "reload.l34.disable");
			AddQuestRecord("Tenochtitlan", "7");
			pchar.questTemp.Teno = "takeSkull";
		}
	}
}

//��� ������� ���������
void LoginDeadmansGod()
{
	chrDisableReloadToLocation = true;
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//������ ���� �������
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "pistol5", 3000);
	sld.name = "��������������";
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "InGreateTemple";
	ChangeCharacterAddressGroup(sld, "Temple_great", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_CharacterPlaySound(sld, "DeadmansGod");
}

//�������� �� ������� ������� � �� � �� ������������� �����
bool CheckMainHeroTotem(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )
	{
		return true;
	}
	else
	{
		for (int i=Totems_start; i<Totems_end; i++)
		{
			if (Items[i].id == itemName)
			{
				if (CheckAttribute(&Items[i], "shown.used"))
				{
					return true;
				}
				break;
			}
		}
	}
	return false;
}

// --> ugeen 20.06.09 - �������� �� ������� ���� � ��
bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )	
	{
		return true;
	}
	return false;	
}
// <-- ugeen
void LoginShotgunGuards()
{
	ref sld;
	if (pchar.questTemp.Teno != "YouWinGod")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = true;
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("AztecWarrior_"+i, "AztecWarrior"+(rand(4)+1), "skeleton", "man", 30, PIRATE, 0, true));
			FantomMakeCoolFighter(sld, 30, 90, 90, "toporAZ", "", 100);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		}
	}
}

// ������������� ������ �������. Warship
void OtherQuestCharactersInit()
{
	ref sld;
	
	// ����� "������ ����� �����"
	/*sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
	FantomMakeCoolFighter(sld, 10, 30, 35, "blade14", "pistol2", 10);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "�����", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
	sld.name = "�����";
	sld.lastname = "�����";
	sld.SaveItemsForDead = true; // ��������� �� ����� ����
	sld.DontClearDead = true; // �� ������� ���� ����� 200�
	sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	// �� ���� ������ �����
	SetCharacterGoods(sld, GOOD_SILK, 700);
	SetCharacterGoods(sld, GOOD_TOBACCO, 500);
	ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");*/
}

// Warship 07.07.09 �������� - ���������� "���� ������"
void MaryCelesteInit()
{
	ref character, realShip;
	String capID = "MaryCelesteCapitan";
	String seaGroup = "MaryCelesteGroup";
	int good;
	
	// �����.. � ������� ���� ������ ��� generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, ... }; - ���� ������
	// ���� ������� �� �������, �� ��� ����
	/*int generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, GOOD_MAHOGANY, GOOD_MEDICAMENT, GOOD_SILK,
		GOOD_SANDAL, GOOD_COFFEE, GOOD_CLOTHES, GOOD_EBONY, GOOD_TOBACCO,
		GOOD_CHOCOLATE, GOOD_WINE, GOOD_RUM, GOOD_CINNAMON, GOOD_LEATHER };*/
	
	int generableGoods[15];
	
	generableGoods[0] = GOOD_FOOD;
	generableGoods[1] = GOOD_WEAPON;
	generableGoods[2] = GOOD_MAHOGANY;
	generableGoods[3] = GOOD_MEDICAMENT;
	generableGoods[4] = GOOD_SILK;
	generableGoods[5] = GOOD_SANDAL;
	generableGoods[6] = GOOD_COFFEE;
	generableGoods[7] = GOOD_CLOTHES;
	generableGoods[8] = GOOD_EBONY;
	generableGoods[9] = GOOD_TOBACCO;
	generableGoods[10] = GOOD_CHOCOLATE;
	generableGoods[11] = GOOD_WINE;
	generableGoods[12] = GOOD_RUM;
	generableGoods[13] = GOOD_CINNAMON;
	generableGoods[14] = GOOD_LEATHER;
	
	character = GetCharacter(NPC_GenerateCharacter(capID , "Pirate_5", "man", "man", 50, ENGLAND, -1, true));
//	FantomMakeCoolFighter(character, 50, 50, 45, "blade34", "pistol5", 50);
	FantomMakeCoolSailor(character, SHIP_BRIGANTINE, "���� ������", CANNON_TYPE_CANNON_LBS24, 50, 50, 50);
	character.name = "������� ����";
	character.lastname = "";
	character.mapEnc.type = "trade";
	character.mapEnc.Name = "���������� '���� ������'";
	LAi_SetImmortal(character, true);
	SetCharacterGoods(character, GOOD_RUM, 700);
	Character_SetAbordageEnable(character, false); // ���� ������������
	
	SetCrewQuantityOverMax(character, 0); // ������ ������
	
	realShip = GetRealShip(GetCharacterShipType(character));
	
	PChar.QuestTemp.MaryCeleste = "NotFind";
	PChar.QuestTemp.MaryCeleste.TurnRate = realShip.TurnRate; // ��������, ����� ����������� ��� ����������
	
	realShip.lowpolycrew = 0; // ���� ������ �� ������
	realShip.TurnRate = 1; // ���� �� ����� ������������ ���
	realShip.capacity = 2820;
	
	NullCharacterGoods(character); // ����� ������ � �����
	
	AddCharacterGoodsSimple(character, GOOD_BALLS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_GRAPES, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_KNIPPELS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_BOMBS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_POWDER, 500 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_FOOD, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_WEAPON, 20 + rand(30));
	AddCharacterGoodsSimple(character, GOOD_MEDICAMENT, 10 + rand(20));
	AddCharacterGoodsSimple(character, GOOD_SAILCLOTH, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_PLANKS, 20 + rand(30));
	
	good = generableGoods[rand(14)];
	// GetCharacterFreeSpace(ref _refCharacter,int _Goods) - ������ ������� ����� �������� ������� ������ � ���� ���������
	AddCharacterGoodsSimple(character, good, GetCharacterFreeSpace(character, good) - 1);
	
	character.AlwaysFriend = true; // ������ �����
	character.ShipEnemyDisable = true; // ���� �� ��������� �� ��������
	character.CanDropSails = false; // ���� �������� ������
	
	Group_FindOrCreateGroup(seaGroup);
	Group_SetTaskAttackInMap(seaGroup, PLAYER_GROUP);
	Group_LockTask(seaGroup);
	Group_AddCharacter(seaGroup, capID);
	Group_SetGroupCommander(seaGroup, capID);
	SetRandGeraldSail(character, ENGLAND);
	
	character.fromCity = SelectAnyColony(""); // �������, �� ����� ������� ������
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // �������, � ����� ������� ������
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	Map_CreateTrader(character.fromShore, character.toShore, capID, GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));
	
	trace("���������� ���� ������ ����� �� " + character.fromCity + " � ����������� � " + character.toShore);
}