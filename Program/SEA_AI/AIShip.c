object	Sail, Rope, Flag, Vant, Pennant, sFlag;
object PirateFlag, PirateCFlag, CommanderFlag, FortFlag, MerchantFlag, PersonalFlag, QuestFlag;

#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER				1000.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT		1400.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION		1150.0
//#20190612-02
#define RA_CANNON_RATIO 0.55
#define RA_AMMO_DET 3.0
#define RA_POWDER_DET 3.0

bool	bAbordageShipCanBe = false;
bool 	LetCharge = false;
int		iAbordageShipEnemyCharacter;

//bool	bNoDamage2Us = false;
bool	bCanEnterToLand = false;
aref	arIslandReload;
string	sIslandLocator;
string	sIslandID;
string	sSeaSoundPostfix;
int		iShipPriorityExecute = 2;
int		iShipPriorityRealize = 31;
bool	bUpdatePosMode = false;
int		iVicSoundTime = 0;
string	sSeaStartMusicName;
bool	isEnemyAround = false;

int		iNumShips = 0;
int		Ships[MAX_SHIPS_ON_SEA];

int 	ShipModelrList[MAX_SHIPS_ON_SEA];
int 	ShipOnLoadModelrList;
#define SHIP_DETONATE_SMALL		"ShipDetonateSmall"

#event_handler("Ship_StartLoad", "Ship_StartLoad");
#event_handler("Ship_EndLoad", "Ship_EndLoad");

void CreateRiggingEnvironment()
{
	CreateEntity(&Sail, "Sail");
	LayerAddObject(sCurrentSeaExecute, &Sail, iShipPriorityExecute + 1);
	LayerAddObject(sCurrentSeaRealize, &Sail, iShipPriorityRealize + 1);
	LayerAddObject("sails_trace", &Sail, 10);
	LayerAddObject("sea_reflection2", &Sail, 3);
	Sail.MinSpeed = 0.05;

	CreateEntity(&Rope, "Rope");
	LayerAddObject(sCurrentSeaExecute, &Rope, iShipPriorityExecute + 2);
	LayerAddObject(sCurrentSeaRealize, &Rope, iShipPriorityRealize + 2);
	
	Flag.ratioLimit = 1;
	Flag.sizeRatio = 3.5;
	Flag.isDefault = 1;				
	CreateEntity(&Flag, "Flag");
	LayerAddObject(sCurrentSeaExecute, &Flag, iShipPriorityExecute + 3);
	LayerAddObject(sCurrentSeaRealize, &Flag, iShipPriorityRealize + 3);
	LayerAddObject("sea_reflection2", &Flag, 3);

	CreateEntity(&Vant, "Vant");
	LayerAddObject(sCurrentSeaExecute, &Vant, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &Vant, iShipPriorityRealize + 4);

	iNumShips = 0;
	//Boyer mod for new version #20170201
	Pennant.ratioExceeds = 1;
	Pennant.sizeRatio = 3.5;
	Pennant.iniSection = "PENNANT";
	CreateEntity(&Pennant, "Flag");
	LayerAddObject(sCurrentSeaExecute, &Pennant, iShipPriorityExecute + 5);
	LayerAddObject(sCurrentSeaRealize, &Pennant, iShipPriorityRealize + 5);
	LayerAddObject("sea_reflection2", &Pennant, 3);

	sFlag.lblGroup = "sflag";
	sFlag.iniSection = "PENNANT";
	CreateEntity(&sFlag, "Flag");
	LayerAddObject(sCurrentSeaExecute, &sFlag, iShipPriorityExecute + 6);
	LayerAddObject(sCurrentSeaRealize, &sFlag, iShipPriorityRealize + 6);
	LayerAddObject("sea_reflection2", &sFlag, 3);	  
}

void DeleteRiggingEnvironment()
{
	DeleteClass(&Sail);
	DeleteClass(&Rope);
	DeleteClass(&Flag);
	//Boyer mod for new version #20170201
	DeleteClass(&sFlag);
	DeleteClass(&Pennant);
	DeleteClass(&PirateFlag);
	DeleteClass(&CommanderFlag);
	DeleteClass(&FortFlag);
	DeleteClass(&PirateCFlag);
	DeleteClass(&MerchantFlag);
	DeleteClass(&PersonalFlag);
	DeleteClass(&QuestFlag);
	DeleteClass(&Vant);
}

void DeleteShipEnvironment()
{
	DeleteRiggingEnvironment();

	DelEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent");  // ����� �� ������������???
	DelEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea");
	DelEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent");
	DelEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter");
	DelEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall");
	DelEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate");
	DelEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage");
	DelEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext");
	DelEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded");
	DelEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace");
	DelEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters");
	DelEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation");
	DelEventHandler(WHR_LIGHTNING, "Ship_Lightning");
	DelEventHandler("eSwitchPerks", "Ship_UpdatePerks");
	DelEventHandler("TornadoDamage", "Ship_TornadoDamage");
	DelEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint");
	DelEventHandler("frame", "Ship_VicSoundTime");
	DelEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound");
	DelEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent");

	for (int i=0; i<iNumShips; i++) 
	{ 
		// delete particles from ship/etc
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE); 
	}

	// scan characters for delete snd id's
	DeleteEntitiesByType("ship");
}

void ClearAllFire() // boal new
{
    for (int i=0; i<iNumShips; i++)
	{
		// delete particles from ship/etc
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE);
	}
}
// boal new �������� ���� � ���� �������� ��������� �� ����.
void Sea_ClearCheckFlag() 
{
    if (bSeaActive)
    {
		for (int i=0; i<iNumShips; i++)
		{
			//Boyer fix
			if(sti(Ships[i]) >= 0 && sti(Ships[i]) < TOTAL_CHARACTERS) 												   
			{
				if (!CheckAttribute(&Characters[Ships[i]], "DontCheckFlag"))
				{
					DeleteAttribute(&Characters[Ships[i]], "CheckFlagYet"); // ���� ������������� �����
					DeleteAttribute(&Characters[Ships[i]], "CheckFlagDate");
				}
			}
			// ������ ����
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (CheckAttribute(&colonies[i], "commanderIdx"))
				{
					if (!CheckAttribute(&Characters[sti(colonies[i].commanderIdx)], "DontCheckFlag"))
					{
						DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagYet"); // ���� ������������� �����
						DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagDate");
					}
				}
			}
		}
	}
}

void CreateShipEnvironment()
{
	isEnemyAround = false;
	bUpdatePosMode = false;
	iVicSoundTime = 0;

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	sIslandLocator = "";
	sIslandID = "";
	
	for (int x = 0; x < MAX_SHIPS_ON_SEA; x++)
	{
		ShipModelrList[x] = -1;
		Ships[x] = -1;
	}
	ShipOnLoadModelrList = -1;
	aref arCurWeather = GetCurrentWeather();
	sSeaSoundPostfix = arCurWeather.Sounds.Sea.Postfix;

	CreateRiggingEnvironment();

	SetEventHandler(SEA_GET_LAYERS, "SeaAI_GetLayers", 0);

	SetEventHandler(SHIP_NOT_ENOUGH_BALLS, "Ship_NotEnoughBalls", 0);
	SetEventHandler(SHIP_GET_CURRENT_BALLS_NUM, "Ship_GetCurrentBallsNum", 0);
	SetEventHandler(SHIP_SHIP2ISLAND_COLLISION, "Ship_Ship2IslandCollision", 0);
	SetEventHandler(SHIP_SHIP2SHIP_COLLISION, "Ship_Ship2ShipCollision", 0);
	SetEventHandler(SHIP_SAIL_DAMAGE, "Ship_SailDamage", 0);
	SetEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage", 0);
	SetEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation", 0);
	SetEventHandler(SHIP_TO_STRAND, "Ship_OnStrand", 0);
	SetEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext", 0);
	SetEventHandler(SHIP_DEAD, "Ship_OnDead", 0);
	SetEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters", 0);
	SetEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea", 0);
	SetEventHandler(SHIP_CREATE, "Ship_OnCreate", 0);
	SetEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded", 0);
	SetEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent", 0);
	SetEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent", 0);
	SetEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter", 0);
	SetEventHandler(SHIP_FIRE_ACTION, "Ship_FireAction", 0);
	SetEventHandler(SHIP_GET_BORT_FIRE_DELTA, "Ship_GetBortFireDelta", 0);
	SetEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall", 0);
	SetEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace", 0);
	SetEventHandler(WHR_LIGHTNING, "Ship_Lightning", 0);
	SetEventHandler(SHIP_CREATELOADSHIP, "Ship_LoadShip", 0);
	SetEventHandler(SHIP_LOAD_SHIPACTIVATEFIREPLACE, "Ship_LoadShipActivateFirePlace", 0);
	// Boal ����� ������ ���? SetEventHandler(SHIP_LOAD_SHIPACTIVATEFIREPLACE, "Ship_LoadShipActivateFirePlace", 0);
	SetEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint", 0);
	SetEventHandler("TornadoDamage", "Ship_TornadoDamage", 0);

	SetEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate", 0);

	SetEventHandler(SHIP_MAST_DAMAGE, "Ship_MastDamage", 0);

	SetEventHandler("eSwitchPerks", "Ship_UpdatePerks", 0);

	SetEventHandler("frame", "Ship_VicSoundTime", 0);

	SetEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound", 0);
	SetEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent", 0);
}	

float Ship_GetBortFireDelta()
{
	aref aCharacter = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDistance = GetDistance2D(x, z, stf(aCharacter.Ship.Pos.x), stf(aCharacter.Ship.Pos.z));
	
	float fAccuracy = 1.3 - stf(aCharacter.TmpSkill.Accuracy);
	
	// to_do
	if (iArcadeSails == 1)// && aCharacter.id == characters[nMainCharacterIndex].id)
	{
		fAccuracy  = fAccuracy - 0.2;
		if (fAccuracy < 0.1)
		{
			fAccuracy = 0.1;
		}
	}
	/*
	if (aCharacter.id != characters[nMainCharacterIndex].id)
	{
		fAccuracy  = fAccuracy - 0.2;
		if (fAccuracy < 0.1)
		{
			fAccuracy = 0.1;
		}
	} */
	

	float fRadius = fAccuracy * Bring2Range(0.0, 120.0, 0.0, 1000.0, fDistance);
	return fRadius;
}

string Ship_GetGroupID(ref rCharacter)
{
 	if (CheckAttribute(rCharacter, "SeaAI.Group"))// boal fix bug
    {
        return rCharacter.SeaAI.Group.Name;
    }
    else
    {
        return "";
    }
}
// boal 030804 -->
void Ship_NationAgressivePatent(ref rCharacter)
{
	// ������ �������� ������, ����� ����� �� ����� �������
    ref rMainCharacter = GetMainCharacter();

    if (isMainCharacterPatented())
    {
        if (sti(rCharacter.nation) != PIRATE && GetNationRelation(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation), sti(rCharacter.nation)) != RELATION_ENEMY)
        {
        	TakeItemFromCharacter(rMainCharacter, "patent_" + NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)));
        	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)) + "hunter", 40);
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCur = 1; // ����� ������ �������
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCurNext = 0; // ������� ������ �������
        	RemoveCharacterEquip(rMainCharacter, "patent");// ������� ������ �� ����������
        	rCharacter.CheckNationBounty = true;
        }
    }
    else
    {// ��� �������
    	if (sti(rCharacter.nation) != PIRATE && !CheckAttribute(rCharacter, "CheckNationBounty"))   // ��� �� ���������
    	{
    		if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) != RELATION_ENEMY)
    		{
				rCharacter.CheckNationBounty = true;
				ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rCharacter.nation)) + "hunter", 1 + rand(2));
			}
    	}
    }
}

void SetCompanionsEnemy(ref rCharacter) // ��� ������ � � ���� ������
{
    if(!CheckAttribute(rCharacter, "index")) return;

    int i, iCompanionIndex;
    int nIndex =  sti(rCharacter.index);
    for (i=1; i<COMPANION_MAX; i++)
    {
        iCompanionIndex = GetCompanionIndex(&Characters[nMainCharacterIndex],i);
        if (iCompanionIndex != -1)
        {
            SetCharacterRelationBoth(iCompanionIndex, nIndex, RELATION_ENEMY);
        }
    }
}

void Ship_NationAgressive(ref rMainGroupCharacter, ref rCharacter)// ��� ������ � � ���� ������
{
    ref rMainCharacter = GetMainCharacter();
	
																																										  

    if (CheckAttribute(rCharacter, "Coastal_Captain")) return;  // ���� ���� ����, �� ��� ������, ��� ���������� � ���������

	//--> eddy. ����� ���� �� ������
	if (rCharacter.id == "MQPirate" && sti(rCharacter.nation) != PIRATE)
	{
		rCharacter.nation = PIRATE;
		Ship_FlagRefresh(characterFromId("MQPirate")); //���� �� ����
		//Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex); //���������
      	Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
		Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
	}
	//<-- eddy. ����� ���� �� ������
	else
	{
		if (CheckAttribute(rCharacter, "ShipEnemyDisable") || CheckAttribute(rCharacter, "AlwaysFriend"))  return; // ���� �� ��������� �� ��������
	    if( sti(rMainCharacter.nation) == sti(rCharacter.nation) && sti(rMainCharacter.nation) != PIRATE)
	    {
            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
            rMainCharacter.nation = PIRATE;
			DoQuestCheckDelay(NationShortName(PIRATE) + "_flag_rise", 0.1); // ���������� ��� ��������� �����
	        // Ship_FlagRefresh(PChar); //���� �� ����
	        //SetNationToOfficers(PIRATE);
	        ChangeCharacterReputation(rMainCharacter, -10);
	    }
	    Ship_NationAgressivePatent(rCharacter); // ������ �������� ������, ����� ����� �� ����� �������
	    // clear group temporary task status
		for (int i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; } // ����� ����� �3

	    SetNationRelation2MainCharacter(sti(rMainGroupCharacter.nation), RELATION_ENEMY);
	    SetCharacterRelationBoth(sti(rMainGroupCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	    //#20200307-02
        SetCompanionsEnemy(rMainGroupCharacter);
	    // boal 04.04.04 -->
	    if (sti(rMainGroupCharacter.nation) != PIRATE)
	    {
	    	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rMainGroupCharacter.nation)) + "hunter", 5);
	    }
    }
    //#20200307-02
    SetCompanionsEnemy(rCharacter);
}
// boal 030804 <--
void Ship_FireAction()
{
	aref rCharacter = GetEventData();				// we attack this character
	aref rMainGroupCharacter = GetEventData();		// commander character for rCharacter
	int iRelation = GetEventData();
	
	if (LAi_IsDead(rCharacter)) return; // fix - ����� ������ � ����!
	
	// if companion - decrease reputation
	if (IsCompanion(rCharacter))
	{
		if (CheckAttribute(rCharacter, "CompanionEnemyEnable") && sti(rCharacter.CompanionEnemyEnable))
		{
			if(HasSubStr(rCharacter,"PsHero_")) PChar.PGG_EnemyPP = "1";
			SeaAI_SetCompanionEnemy(rCharacter);
			// disconnect companion from our group and set it enemy to us
		}
		return;
	}
	else
	{
	    if (CheckAttribute(rCharacter, "ShipEnemyDisable") )  return; // ���� �� ��������� �� ��������
	    // ����� || CheckAttribute(rCharacter, "AlwaysFriend") �� ���� �� ����������� �������� ������, �� ������ ���������
	    DeleteAttribute(rCharacter, "AlwaysFriend");
	}
			
	if (iRelation != RELATION_ENEMY)
	{
		Ship_NationAgressive(rMainGroupCharacter, rCharacter);// boal 030804 � ���� �����

		// making whole group as enemy to us
		if (CheckAttribute(rMainGroupCharacter, "SeaAI.Group.Name"))
		{
			Group_SetEnemyToCharacter(rMainGroupCharacter.SeaAI.Group.Name, nMainCharacterIndex);
		}
		NationUpdate();
	}
	else
	{
	    // ������ ����� ������ ���� ���� ����
	    Ship_NationAgressivePatent(rCharacter);// ������ �������� ������, ����� ����� �� ����� �������
	}
	DoQuestCheckDelay("NationUpdate", 0.3);
	RefreshBattleInterface();
 
	//eddy. ������� � ���������� ������ �� ������
	if (CheckAttribute(rCharacter, "ShipTaskLock")) return;
	//eddy
	int i;
	string sGroupID, sGroupType;
	ref rGroup;

	// clear group temporary task status
	for (i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; }

	// if fort - return
	int iShipType = sti(rCharacter.Ship.Type);
	iShipType = sti(RealShips[iShipType].basetype);
	
	if (ShipsTypes[iShipType].name == "Fort")
	{
		return;
	}
	sGroupID = Ship_GetGroupID(rMainGroupCharacter);

	Group_SetTaskAttack(PLAYER_GROUP, sGroupID);
}

//#20171230-01 Mast damage mod
#define MAX_CAL_MAST_DMG 50
float Ship_MastDamage()
{
	int iDamageType = GetEventData();
	int iMastNum = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDamage = GetEventData();
	aref rCharacter = GetEventData();
	
	int iShipType = sti(rCharacter.ship.type);
	ref rBaseShip = GetRealShip(iShipType);
	int nClass = sti(rBaseShip.Class);
	float MastMulti = stf(rBaseShip.MastMultiplier);

	switch (iDamageType)
	{
		case SHIP_MAST_TOUCH_ISLAND:
			fDamage = fDamage + 0.1;
		break;
		case SHIP_MAST_TOUCH_SHIP:
			//aref rCollideCharacter = GetEventData();

			fDamage = fDamage + 0.1;
		break;
		case SHIP_MAST_TOUCH_BALL:
		    //#20171230-01 Mast damage mod
            //int iBallCharacterIndex = GetEventData();  //Passed in message, but not needed as AIBalls has needed info
            //ref rBallCharacter = GetCharacter(iBallCharacterIndex);
           	ref rCannon = GetCannonByType(sti(AIBalls.CurrentBallCannonType));
			int	iBallType = sti(AIBalls.CurrentBallType);
			int nCaliber = sti(rCannon.caliber);
            float nDirect = 0.35; //Glancing
            int nKni = nCaliber;
            if(iBallType == GOOD_KNIPPELS)
                nKni += 5;
            if(rand(65) < nKni)
                nDirect = 1.1; //Direct
            float fCbrMDamage = 0.5 * retMin(makefloat(nCaliber) / MAX_CAL_MAST_DMG, 1.0);
            float fClsMDamage = 0.005 * (nClass / 6);
            float tempDamage = 0.0;
            float baseDamage = 0.0;
			switch (iBallType)
			{
				case GOOD_BALLS:
					baseDamage = pow(nClass, 2.0) * 0.005; //0.025;
				break;
				case GOOD_GRAPES:
					baseDamage = 0.0;
					fCbrMDamage = 0.0;
					fClsMDamage = 0.0;
				break;
				case GOOD_KNIPPELS:
					baseDamage = pow(nClass, 2.0) * 0.0035; //0.015;
				break;
				case GOOD_BOMBS:
					baseDamage = pow(nClass, 2.0) * 0.0015; //0.005;
				break;
			}
			tempDamage = baseDamage * fCbrMDamage + fClsMDamage;
			tempDamage = tempDamage * nDirect;
			fDamage = fDamage + tempDamage;
        //#20190113-06
        int iBallCharacterIndex = GetEventData();
        ref rBallCharacter = GetCharacter(iBallCharacterIndex);
        if(GetNationRelation(sti(rBallCharacter.Nation), sti(rCharacter.nation)) != RELATION_FRIEND) 
			{
				if(CheckAttribute(rCharacter, "SeaAI.fortSanctuary")) 
				{
					DeleteAttribute(rCharacter, "SeaAI.fortSanctuary")
					rCharacter.SeaAI.hitInSanctuary = true;
				}
			}
		break;
	}

	fDamage = Clampf(fDamage);

	// if mast fall - play sound
	if (fDamage >= 1.0)
	{
		Play3DSound("mast_fall", x, y, z);
		rCharacter.ship.sp = CalculateShipSP(rCharacter);  // �������� ������ �� ������
		rCharacter.Tmp.SpeedRecall = 0; // ���� ������������ ������
		RefreshBattleInterface();
	}
	
	// LEO: ����� ����� �� ������ �������� �� ������
	string sShip = rBaseShip.BaseName;
	fDamage = fDamage * MastMulti;
	return fDamage;
	//procMastFall
}

float Ship_GetSailState(ref rCharacter)
{
	float fSailState = 1.0;
	SendMessage(rCharacter, "le", MSG_SHIP_GET_SAIL_STATE, &fSailState);
	return fSailState;
}
// boal 27.09.05 --> LEO - �������� ��������� �������� - ����� ������
void Ship_SetExplosion(ref rCharacter, ref	rShipObject)
{
    int i = 0;
	
	PostEvent(SHIP_BRANDER_DETONATE, 800, "l", sti(rCharacter.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(rCharacter.index));
}
// boal <--
void Ship_SetSailState(int iCharacterIndex, float fSailState)
{
	SendMessage(&AISea, "laf", AI_MESSAGE_SHIP_SET_SAIL_STATE, &Characters[iCharacterIndex], fSailState);
}

void Ship_SetTaskNone(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_NONE;
}

void Ship_SetTaskAbordage(int iTaskPriority, int iCharacterIndex, int iCharacterIndexAbordageTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ABORDAGE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexAbordageTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ABORDAGE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexAbordageTo]);
}

void Ship_SetTaskBrander(int iTaskPriority, int iCharacterIndex, int iCharacterIndexBranderTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_BRANDER;
	rCharacter.SeaAI.Task.Target = iCharacterIndexBranderTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_BRANDER, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexBranderTo]);
}

void Ship_SetTaskMove(int iTaskPriority, int iCharacterIndex, float x, float z)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	//rCharacter.SeaAI.Task.Target = "";
	rCharacter.SeaAI.Task.Pos.x = x;
	rCharacter.SeaAI.Task.Pos.z = z;
	SendMessage(&AISea, "lllaff", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], x, z);
}

void Ship_SetTaskRunaway(int iTaskPriority, int iCharacterIndex, int iFromIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_RUNAWAY;
	rCharacter.SeaAI.Task.Target = iFromIndex;
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_RUNAWAY, iTaskPriority, &Characters[iCharacterIndex]);
	Ship_SetSailState(iCharacterIndex, 1);
}

void Ship_SetTaskAttack(int iTaskPriority, int iCharacterIndex, int iCharacterIndexVictim)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ATTACK;
	rCharacter.SeaAI.Task.Target = iCharacterIndexVictim;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ATTACK, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexVictim]);
}

void Ship_SetTaskSailTo(int iTaskPriority, int iCharacterIndex, int iCharacterIndexSailTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexSailTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexSailTo]);
}

void Ship_SetTaskDrift(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DRIFT;
	//rCharacter.SeaAI.Task.Target = "";
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_DRIFT, iTaskPriority, &Characters[iCharacterIndex]);
}

void Ship_SetTaskDefendGroup(int iTaskPriority, int iCharacterIndex, string sDefendGroup)
{
	SendMessage(&AISea, "lllas", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND_GROUP, iTaskPriority, &Characters[iCharacterIndex], sDefendGroup);
}

void Ship_SetTaskDefend(int iTaskPriority, int iCharacterIndex, int iCharacterIndex2Defend)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DEFEND;
	rCharacter.SeaAI.Task.Target = iCharacterIndex2Defend;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndex2Defend]);
}

void Ship_DoFire()
{
	int bCameraOutside = SeaCameras_isCameraOutside();
	SendMessage(&AISea, "lal", AI_MESSAGE_CANNON_FIRE, &Characters[nMainCharacterIndex], bCameraOutside);
}

void Ship_StartLoad()
{
	aref rCharacter = GetEventData();
	if(rCharacter.id != "0" && sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		ref refBaseShip;
		int nShipType = GetCharacterShipType(rCharacter);
		refBaseShip = GetRealShip(nShipType);
		SetTextureForShip(refBaseShip, rCharacter);
	}
}

void Ship_EndLoad()
{
	SetTexturePath(0, "");
}

void Ship_SetTrackSettings(ref rCharacter)
{
	ref rShip = GetRealShip(GetCharacterShipType(rCharacter));

	rCharacter.Ship.Track.Enable = rShip.Track.Enable;
	if (!sti(rShip.Track.Enable)) return;

	rCharacter.Ship.Track.TrackDistance = 1.0;
	rCharacter.Ship.Track.WaveHeight2 = 0.9;
	rCharacter.Ship.Track.WaveHeight1 = 0.2;

	rCharacter.Ship.Track1.Texture = "ships\trailShip.tga";
	rCharacter.Ship.Track1.TrackWidthSteps = 12.0;

	rCharacter.Ship.Track2.Texture = "ships\trailKeel.tga";
	rCharacter.Ship.Track2.TrackWidthSteps = 4.0;

	rCharacter.Ship.Track1.ZStart = rShip.Track1.ZStart;
	rCharacter.Ship.Track1.LifeTime = rShip.Track1.LifeTime;
	rCharacter.Ship.Track1.Width = rShip.Track1.Width;
	rCharacter.Ship.Track1.Speed = rShip.Track1.Speed;

	rCharacter.Ship.Track2.ZStart = rShip.Track2.ZStart;
	rCharacter.Ship.Track2.LifeTime = rShip.Track2.LifeTime;
	rCharacter.Ship.Track2.Width = rShip.Track2.Width;
	rCharacter.Ship.Track2.Speed = rShip.Track2.Speed;
}

void Ship_SetLightsOff(ref rCharacter, float fTime, bool bLights, bool bFlares, bool bNow)
{
	SendMessage(rCharacter, "lflll", MSG_SHIP_SETLIGHTSOFF, fTime, bLights, bFlares, bNow);
	rCharacter.Ship.Lights = 0; //fix
}

void Ship_SetLightsAndFlares(ref rCharacter)
{
	if(sti(sea.lights) == 1)
	{
		rCharacter.Ship.Flares = 1;
		rCharacter.Ship.Lights = 1;
	}
	else
	{
		rCharacter.Ship.Flares = 0;
		rCharacter.Ship.Lights = 0;
	}
}

void Ship_Add2Sea(int iCharacterIndex, bool bFromCoast, string sFantomType)
{
	ref		rCharacter = GetCharacter(iCharacterIndex);

	DeleteAttribute(rCharacter, "ship.cannons.chance_for_explode"); //to_do � ��� �� �������

	aref	arCharacter; makearef(arCharacter, Characters[sti(rCharacter.index)]);
	
	int iShipType = sti(rCharacter.Ship.Type);

	if(iShipType == SHIP_NOTUSED)
	{
		return;
	}

	int iRealShip = sti(RealShips[iShipType].basetype);

	if(!CheckAttribute(&RealShips[iShipType], "name"))
	{
		Trace("Ship_Add2Sea() : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("Ship_Add2Sea ERROR : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		return;
	}
	if (iRealShip >= SHIP_TYPES_QUANTITY)
	{
		Trace("Character.id = " + rCharacter.id + ", have invalid ship type = " + iShipType + ", and try load to sea");
		return;
	}
	// boal -->
	// 22.04.05 ����� ���� ���������
    if (!CheckAttribute(rCharacter, "AlwaysEnemy") && !CheckAttribute(rCharacter, "AlwaysFriend")) // � ������ �� ����
    {
    	DelCharacterRelation(iCharacterIndex);
    }
    else
    {
		if (CheckAttribute(rCharacter, "AlwaysFriend"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_FRIEND);
		}
		if (CheckAttribute(rCharacter, "AlwaysEnemy"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_ENEMY);
		}
    }
    DeleteAttribute(rCharacter, "Ship_SetTaskAbordage"); // boal
    DeleteAttribute(rCharacter, "Killer.status"); // boal 09.06.05 SUPER FIX
    DeleteAttribute(rCharacter, "CheckFlagYet"); // ���� ������������� �����
    DeleteAttribute(rCharacter, "CheckNationBounty"); // �������� ��� �� ����� ����� ����
    DeleteAttribute(rCharacter, "ShipCannonChargeType"); // ���� ����, ��� ������ ���������, �������� ������� ���������, �� ���� ������� ����� ��� ����� ��������
    
	if (CheckAttribute(rCharacter, "DontCheckFlag"))
	{
	    rCharacter.CheckFlagYet = true;
	}
    rCharacter.TmpSkillRecall = "0"; //boal 25.05.04 ����������� �������, ����� == 0 ������� �����
    rCharacter.Tmp.SpeedRecall = 0; // ����������� �������� � �������
    rCharacter.Tmp.fShipSpeed  = 1; // ��������� ���������
	rCharacter.Tmp.fWatchFort  = rand(15); // ����������� ������� �� ����
	rCharacter.Tmp.fWatchFort.Qty = 15;
    // boal <--

	if (iCharacterIndex == GetMainCharacterIndex()) { // NK 04-09-16 clears timer attribute, -21 for updatetime
		rCharacter.seatime = 0;
		rCharacter.lastupdateseatime = 0;
	}
	if (iCharacterIndex >= FANTOM_CHARACTERS)
	{
		SetBaseShipData(rCharacter);
		Ship_SetFantomData(rCharacter);
		
        Fantom_SetCannons(rCharacter, sFantomType);
		Fantom_SetBalls(rCharacter, sFantomType);
		Fantom_SetGoods(rCharacter, sFantomType);
		Fantom_SetUpgrade(rCharacter, sFantomType);
		SaveCurrentNpcQuestDateParam(rCharacter, "Add2SeaTime"); //������� ������ ����� ����� � ����
	}
    AcceptWindCatcherPerk(rCharacter); // ���������� ����� ����� �����, ��� ��������, � �� ��� ��� � �3 boal 02/08/06
	//rCharacter.TmpPerks.Turn = false;

	CharacterUpdateShipFromBaseShip(iCharacterIndex);

	rCharacter.Ship.Ang.y = 0.0;

	Ship_ClearImpulseStrength(rCharacter);
	Ship_SetLightsAndFlares(rCharacter);
	Ship_SetTrackSettings(rCharacter);

	aref baseship;
	ref refBaseShip;
	
	makearef(baseship,rCharacter.ship);
	int nShipType = GetCharacterShipType(rCharacter);
	refBaseShip = GetRealShip(nShipType);
	
	rCharacter.Tmp.BortsReloaded.Event = false;
	rCharacter.Tmp.BortsReloaded.cannonl = false;
	rCharacter.Tmp.BortsReloaded.cannonr = false;
    
	rCharacter.Features.GeraldSails = true;
	rCharacter.Ship.LastBallCharacter = -1;
	rCharacter.Ship.WindDotShip = 1.0;
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
	
	//  ������ ���, ����� ����� � ���� ��������
	rCharacter.Ship.BoxSize.x = 1.0;  // ������ ��������� � ���� :( �� ��������
	rCharacter.Ship.BoxSize.y = 1.0;
	rCharacter.Ship.BoxSize.z = 2.0;
	
	rCharacter.Ship.Strand = false;
	rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
	rCharacter.Ship.Stopped = false;
	rCharacter.Ship.POS.Mode = SHIP_SAIL;
	rCharacter.Ship.SeaAI.Init.AbordageDistance = 30.0;
	// boal -->
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = 50;
	if (CheckAttribute(rCannon, "FireRange")) range = stf(rCannon.FireRange);
	rCharacter.Ship.SeaAI.Init.AttackDistance = range  / (1.4 + frandSmall(2.0));  // ��� ����� ������ ��������, �� ���������� ��������� ��, �� ������� ����� ��������� ��������� �������
	rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon = 0; //������� ������� ����� ����������� ��� ������ ���������, ��� ����� ���������
	// boal <--
	rCharacter.Ship.SeaAI.Init.FollowDistance = makefloat(180 + rand(120)); // ���� 300, ����� ������ ��� ������������ ��������� ����������� � ���������� � ������
	DeleteAttribute(rCharacter, "Ship.SeaAI.Init.AttackRangeSet");
	//#20180208-01 Add flexibility to AI ship
    rCharacter.Ship.SeaAI.Init.WindC = 2.0;
    rCharacter.Ship.SeaAI.Init.FortC = 2.75;
    rCharacter.Ship.SeaAI.Init.DefEnemyC = 5.0;
    rCharacter.Ship.SeaAI.Init.MinEnemyC = 3.0;
    rCharacter.Ship.SeaAI.Init.MaxEnemyC = 10.0;
    rCharacter.Ship.SeaAI.Init.IslandDist = 90.0;
    rCharacter.Ship.SeaAI.Init.IslandC = 2.5;
    rCharacter.Ship.SeaAI.Init.POSRatio = 0.3;
    rCharacter.Ship.SeaAI.Init.LowPredTime = 20.0;
    rCharacter.Ship.SeaAI.Init.HighPredTime = 50.0;
    rCharacter.Ship.SeaAI.Init.LowSpeed = 0.1;
    rCharacter.Ship.SeaAI.Init.HighSpeed = 50.0;
    rCharacter.Ship.SeaAI.Init.MinBrakeDist = 15.0;
    rCharacter.Ship.SeaAI.Init.FortEnemyDist = 750.0;
    //#20190313-01
    rCharacter.Ship.SeaAI.Init.MultiBoardDist = 100.0;

    rCharacter.Ship.SeaAI.Init.MaxTackAccumDistance = 200.0;
    rCharacter.Ship.SeaAI.Init.TackOffDistance = 50.0;
    rCharacter.Ship.SeaAI.Init.TackCheckAngle = (PIm2 / 13.0);
    rCharacter.Ship.SeaAI.Init.TackTurnAngle = (PIm2 / 12.0);

    rCharacter.Ship.SeaAI.Init.AttackRotate = 1.65; //1.2;
    rCharacter.Ship.SeaAI.Init.AttackRand = 50.0;

	rCharacter.Ship.Sounds = "";

	if(sti(rCharacter.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON)
	{
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	}

	if (bFromCoast == false) { rCharacter.Ship.Speed.z = 1.0; }

	// create ship
	Event("eSwitchPerks", "l", iCharacterIndex);											// Perks
	Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters
	ShipModelrList[iNumShips] = GetCurrentModelrNumber();
	
	//ugeen --> ����� !! � ����������� �� ���� ������� Ship.Sink <-- 3 ���� �������� ��-�� ���� ������ :(  <-- ��-�� ��� ����������� ������� ��� ������
	if(CheckAttribute(rCharacter,"Ship.Sink")) {trace("ShipSink rCharacter.id = " + rCharacter.id); DeleteAttribute(rCharacter,"Ship.Sink");}
	
	CreateEntity(&Characters[iCharacterIndex], "Ship");
    Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      ����� �������� �������
	aref arChar, arShip;
	makearef(arChar, characters[iCharacterIndex]);
	makearef(arShip, RealShips[iShipType]);

	Ship_CreateStaticSounds(rCharacter);

	//SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], &Characters[iCharacterIndex], &RealShips[iShipType]);
	SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], arChar, arShip);

	// ������ ��� ������� - ���������� ��� ������ ������ ������� �� ������� ���������
	//SendMessage(&Sail,"li", MSG_SAIL_FREE_GROUP, &Characters[iCharacterIndex]);
	
    /* if (!CheckAttribute(rCharacter, "Ship.BoxSize.x"))
	{
		trace("No Ship.BoxSize id=" + rCharacter.id);
		rCharacter.Ship.BoxSize.x = 1.0;  // ������ ��������� � ����
		rCharacter.Ship.BoxSize.y = 1.0;
		rCharacter.Ship.BoxSize.z = 2.0;
	} */
	ReloadProgressUpdate();
	
	if(CheckAttribute(rCharacter, "ShipWreck"))
	{
		MakeSailDmg(GetCharacterIndex(rCharacter.id), 90);
	}
	
	Ships[iNumShips] = iCharacterIndex;
	rCharacter.curshipnum = iNumShips;
	trace("AIShip  iNumShips : " + iNumShips + " ShipModelrList : " + ShipModelrList[iNumShips] + " ShipName : " + rCharacter.Ship.Name + " Ships = " + Ships[iNumShips]);
	iNumShips++;
}

void Ship_RecreateStaticSounds()
{
	for (int i=0; i<iNumShips; i++) {
		//Boyer fix for log error:
		//RUNTIME ERROR - file: sea_ai\AIShip.c; line: 851
		//invalid index -1 [size:1000]
		//RUNTIME ERROR - file: sea_ai\AIShip.c; line: 851
		//function 'Ship_RecreateStaticSounds' stack error
		if (makeint(Ships[i]) > -1)
			Ship_CreateStaticSounds(&Characters[Ships[i]]);
	}
	//#20190117-03
	if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
        Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));
}

void Ship_CreateStaticSounds(ref rCharacter)
{
    if (!CheckAttribute(rCharacter, "Ship.Pos.x")) return; // fix
	if (GetCharacterShipType(rCharacter) == SHIP_NOTUSED) return; // ����� ��� �� ����
	
    ref refBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
	// create water sound
	float fX = stf(rCharacter.Ship.Pos.x);
	float fY = stf(rCharacter.Ship.Pos.y);
	float fZ = stf(rCharacter.Ship.Pos.z);
	rCharacter.Ship.Sounds.WaterID.x = 0.0;
	rCharacter.Ship.Sounds.WaterID.y = 0.0;
	rCharacter.Ship.Sounds.WaterID.z = 0.12;
	rCharacter.Ship.Sounds.WaterID = Play3DSoundComplex("ship_water_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.WaterID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.WaterID), 0.0); }
	rCharacter.Ship.Sounds.WaterSpeed = 30.0;

	// create sails sound
	rCharacter.Ship.Sounds.SailsID.x = 0.0;
	rCharacter.Ship.Sounds.SailsID.y = 0.5;
	rCharacter.Ship.Sounds.SailsID.z = 0.0;
	rCharacter.Ship.Sounds.SailsID = Play3DSoundComplex("sails_up_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.SailsID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.SailsID), 0.0); }
	rCharacter.Ship.Sounds.SailsMove = 0.0;

	// create turn sound
	rCharacter.Ship.Sounds.TurnID.x = 0.0;
	rCharacter.Ship.Sounds.TurnID.y = 0.0;
	rCharacter.Ship.Sounds.TurnID.z = 0.0;
	rCharacter.Ship.Sounds.TurnID = Play3DSoundComplex("ship_turn_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	if (sti(rCharacter.Ship.Sounds.TurnID) > 0) { Sound_SetVolume(sti(rCharacter.Ship.Sounds.TurnID), 0.0); }
	rCharacter.Ship.Sounds.TurnSpeed = 0.05;
}

void Ship_PlaySound3DComplex(ref rCharacter, string sSoundID, float fVolume, float fX, float fY, float fZ)
{
	if (!CheckAttribute(rCharacter, "Ship.Pos.x")) return; // fix
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	float aY = stf(rCharacter.Ship.Ang.y);

    if (!CheckAttribute(rCharacter, "Ship.BoxSize.x")) return; // fix ���������
     
	float x1 = fX * stf(rCharacter.Ship.BoxSize.x) / 2.0;
	float z1 = fZ * stf(rCharacter.Ship.BoxSize.z) / 2.0;
	RotateAroundY(&x1, &z1, cos(aY), sin(aY));

	int iSoundID = Play3DSoundRet(sSoundID, x + x1, y + fY * stf(rCharacter.Ship.BoxSize.y) / 2.0, z + z1);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_PlaySound3D(ref rCharacter, string sSoundID, float fVolume)
{
	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	int iSoundID = Play3DSoundRet(sSoundID, x, y, z);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_OnBortReloaded()
{
	aref aCharacter = GetEventData();
	string sBort = GetEventData();

	if (!bSeaLoaded || bAbordageStarted) { return; }  // fix
	// ����� �� ���� ���� ��������, �� ���������� ��� �� ���� ���, ������ ����� �� ���� ����� � ��������, �� ���� ���� � ����. "����� boal"
	if (sti(aCharacter.index) != nMainCharacterIndex) { return; } // fix
	/*{
		if (sBort == "cannonl" || sBort == "cannonr") { Ship_PlaySound3D(aCharacter, "bortreloaded_" + sBort, 1.0);	}
		//"bortreloaded_all"
	}*/

	if (!sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		aCharacter.Tmp.BortsReloaded.Event = true;
		PostEvent("Ship_BortReloadEvent", 300, "a", aCharacter);
	}
	if (sBort == "cannonl") { aCharacter.Tmp.BortsReloaded.cannonl = true; }
	if (sBort == "cannonr") { aCharacter.Tmp.BortsReloaded.cannonr = true; }
	if (sBort == "cannonf") { aCharacter.Tmp.BortsReloaded.cannonf = true; }
	if (sBort == "cannonb") { aCharacter.Tmp.BortsReloaded.cannonb = true; }
}

void Ship_BortReloadEvent()
{
    aref aCharacter = GetEventData();
    
    if (sti(aCharacter.Tmp.BortsReloaded.Event))
    {
		LetCharge = LetRecharge();
        bool bLeft = false;
        bool bRight = false;
        bool bFront = false;
        bool bBack = false;
        if (CheckAttribute(aCharacter,"Tmp.BortsReloaded.cannonl")) bLeft = sti(aCharacter.Tmp.BortsReloaded.cannonl) == true;
        if (CheckAttribute(aCharacter,"Tmp.BortsReloaded.cannonr")) bRight = sti(aCharacter.Tmp.BortsReloaded.cannonr) == true;
        if (CheckAttribute(aCharacter,"Tmp.BortsReloaded.cannonf")) bFront = sti(aCharacter.Tmp.BortsReloaded.cannonf) == true;
        if (CheckAttribute(aCharacter,"Tmp.BortsReloaded.cannonb")) bBack = sti(aCharacter.Tmp.BortsReloaded.cannonb) == true;

        if (bLeft && bRight && bFront && bBack)
        {
            //Ship_PlaySound3D(aCharacter, "bortreloaded_all", 1.0);
            // ���� ����������� ���� ������ PlaySound("interface\_GunReady.wav");
            PlayVoice("interface\_GunReady.wav");
        }
        else
        {
            //Boyer change #20170327-01  Sound to use aliases changes
            //if (bLeft)  { PlaySound("interface\_GunReadyL.wav"); }
            //if (bRight) { PlaySound("interface\_GunReadyR.wav"); }
            if (bLeft)  { PlayVoice("interface\_GunReadyL.wav"); }
            if (bRight) { PlayVoice("interface\_GunReadyR.wav"); }
            if (bFront) { PlayVoice("interface\_Gun_FB_Ready.wav"); }
            if (bBack) { PlayVoice("interface\_Gun_FB_Ready.wav"); }
        }
    
    Ship_ClearBortsReloadedEvent(aCharacter);
	}
}
void Ship_ClearBortsReloadedEvent(aref aCharacter)
{
	aCharacter.Tmp.BortsReloaded.Event = false;
	aCharacter.Tmp.BortsReloaded.cannonl = false; 
	aCharacter.Tmp.BortsReloaded.cannonr = false; 
	aCharacter.Tmp.BortsReloaded.cannonf = false; 
	aCharacter.Tmp.BortsReloaded.cannonb = false;
}

void Ship_ChangeChargeEvent() // ����� �� ������������???
{
	string	sBallName;
	
	ref rCharacter = GetCharacter(GetEventData());

	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter);
	sBallName = GetEventData();
	rCharacter.Ship.Cannons.Charge = sBallName;
	Cannon_RecalculateParameters(sti(rCharacter.index));

	//fix if (bSeaLoaded) { Ship_PlaySound3D(rCharacter, "reloadstart_" + sBallName, 1.0); }

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_ChangeCharge(ref rCharacter, int iNewChargeType)
{
	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter);
	
	ref rGood = GetGoodByType(iNewChargeType);
	if (rGood) {
		rCharacter.Ship.Cannons.Charge = rGood.name;
		rCharacter.Ship.Cannons.Charge.Type = iNewChargeType;
	}

	Cannon_RecalculateParameters(sti(rCharacter.index));
	LetCharge = LetRecharge();
 // ���� ���� �� ��������� �� ����������� (����� ��� ������� ����������)
	//fix Ship_PlaySound3D(rCharacter, "reloadstart_" + rGood.name, 1.0);

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_OnCreate()
{
	ref rCharacter = GetCharacter(GetEventData());
	
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
}

void Ship_CheckSituation()
{
    //#20181101-01
    int oldRel, newRel;
	ref		rShip;
	aref	rSituation;
	
	aref	rCharacter = GetEventData();
	aref	rShipObject = GetEventData();
	
	if (sti(rCharacter.index) == nMainCharacterIndex)  return; 
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) { return; }  // super fix boal
	
	// Log_Testinfo("Ship_CheckSituation " + rCharacter.id);
	
	int iCharIdx = sti(rCharacter.index);
	int aiTask = AITASK_NONE;						  
	if (CheckAttribute(rCharacter, "SeaAI.Task"))
    {
         aiTask = sti(rCharacter.SeaAI.Task);
    }
	else
    {
		trace("Character " + rCharacter.id  + " without task");
		rCharacter.SeaAI.Task = AITASK_NONE;
	}

	rShip = GetRealShip(sti(rCharacter.Ship.Type));
	makearef(rSituation, rCharacter.SeaAI.Update.Situation);

	float	fMinEnemyDistance = stf(rSituation.MinEnemyDistance);
	float	fDistance;
	int nLastBallChar = sti(rCharacter.Ship.LastBallCharacter);
	// boal fix AI fMinEnemyDistance - �� ������������ :( 23.05.05
	if (nLastBallChar != -1 && LAi_IsDead(GetCharacter(nLastBallChar)))
	{
		rCharacter.Ship.LastBallCharacter = -1;
	}
    int nTaskTarg = 0;
	if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if (rCharacter.SeaAI.Task.Target != "" && LAi_IsDead(GetCharacter(sti(rCharacter.SeaAI.Task.Target))))
	    {
	        rCharacter.SeaAI.Task.Target = "";
	    }
		nTaskTarg = sti(rCharacter.SeaAI.Task.Target);
	    /*if (rCharacter.SeaAI.Task == AITASK_ABORDAGE && rCharacter.SeaAI.Task.Target == "")
	    {
	        Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex);  // ��� ���� ��������� ��������
	    } */
    }
	// <--
	// boal �������� �� ������� �� �������� ����� 27.01.2004 -->
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // check ships for abordage
    if (Ship_AutoAbordage(rCharacter, fMinEnemyDistance)) { return; }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	// ugeen ->  �������� �� ����������� ��������� ����� ���� // �������� ����� ��� ������ �� �������� - 27.11.17
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if(!CheckAttribute(rCharacter,"surrendered") && Ship_CheckSurrendered(rCharacter)) Ship_SetSurrendered(rCharacter);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Warship 08.07.09 ������ ������ �������
	if(CheckAttribute(rCharacter, "CanDropSails") && !sti(rCharacter.CanDropSails)) //  && Ship_GetSailState(rCharacter) < 1.0 // ��� �������� ����� ���
	{
		Ship_SetSailState(sti(rCharacter.index), 1.0);
	}
		
	// check for enought quantity of balls 
	int iShipCannonsNum  = GetCannonsNum(rCharacter);//sti(rShip.CannonsQuantity);
	int iCurrentBallType = sti(rCharacter.Ship.Cannons.Charge.Type);
	bool bBalls, bKnippels, bBombs, bGrapes;
	bBalls = true; bKnippels = true; bBombs = true; bGrapes = true;
	// boal -->
	if (CheckAttribute(rCharacter, "ShipCannonChargeType")) // ���� ������, ��� ������ ��� �����
	{
	    if (GetCargoGoods(rCharacter, sti(rCharacter.ShipCannonChargeType))    < iShipCannonsNum)
	    {
	        DeleteAttribute(rCharacter, "ShipCannonChargeType"); // ��������� ������ ����� �� ��� ������ �����
	    }
	}
	else
	{
        if (GetCargoGoods(rCharacter,GOOD_BALLS)    < iShipCannonsNum) { bBalls    = false; }
		if (GetCargoGoods(rCharacter,GOOD_BOMBS)    < iShipCannonsNum) { bBombs    = false; }
		if (GetCargoGoods(rCharacter,GOOD_KNIPPELS) < iShipCannonsNum) { bKnippels = false; }
		if (GetCargoGoods(rCharacter,GOOD_GRAPES)   < iShipCannonsNum) { bGrapes   = false; }

		int iNewBallType = iCurrentBallType;
	    if (LetCharge)
	    {
	        iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, bBalls, bBombs, bGrapes, bKnippels);
	    	if (iNewBallType >= 0 && iNewBallType != iCurrentBallType)
		    {
		   	   Ship_ChangeCharge(rCharacter, iNewBallType);
		    }
	    }
	    else
	    {
				ref rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
				float range = stf(rCannon.FireRange);
				if ((fMinEnemyDistance > (range*0.9)) &&  bBalls) // �� ���� ����
				{
					iNewBallType = GOOD_BALLS;
					if (iNewBallType != iCurrentBallType)
					{
						Ship_ChangeCharge(rCharacter, iNewBallType);
					}
				}
	    }
    }
	bool bIsCompanion = IsCompanion(rCharacter);
	
	// check some tasks
	if (CheckAttribute(rCharacter, "SeaAI.Task") && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		switch (sti(rCharacter.SeaAI.Task))
		{
			// boal potc -->
			case AITASK_BRANDER:
				ref rCharacter2Brander = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
				ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
				float fBranderDistance = 45.0 + (7.0 - stf(rBaseShip.Class)) * 15.0; // ������� ����
				fDistance = Ship_GetDistance2D(rCharacter, rCharacter2Brander); // boal 21.01.2004
				if (fBranderDistance > fDistance)
				{
					// fire ship
					Ship_SetExplosion(rCharacter, rShipObject); //boal 27.09.05
					Log_Info("" + XI_ConvertString(rBaseShip.BaseName) + " '" + rCharacter.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "�������", "��������") + " ����� ������.");
					return;
				}
				//Trace("test1 rCharacter2Brander = " + rCharacter2Brander.index);
			break;
			case AITASK_ATTACK:
				//to_del log
				//Log_SetStringToLog("���������: " + Ship_GetDistance2D(rCharacter, &characters[sti(rCharacter.SeaAI.Task.Target)]) + "   �����: " + rCharacter.Ship.SeaAI.Init.AttackDistance);
				//-->> ���� ���� ���� ��� �����, �� ������������ ����������� ���������� ��� ��������	
				//������ ��� ������ ������������ �� ������ ����� ��������
				if (CheckAttribute(rCharacter, "Sea_AI.cannon.charge.lasttime") && sti(rCharacter.Sea_AI.cannon.charge.lasttime) == 1) 
				{
					if (sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 2 || sti(rCharacter.Ship.SeaAI.Init.AttackDistance.qtyTryChangeCannon) == 5)
					{
						rCharacter.Ship.SeaAI.Init.AttackDistance = 50; //�������� ���������
						Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
					}
					else
					{
						float fAttackDist = Ship_GetDistance2D(rCharacter, &characters[sti(rCharacter.SeaAI.Task.Target)]);
						if (fAttackDist < 500)
						{
							rCharacter.Ship.SeaAI.Init.AttackDistance = fAttackDist;
							Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
						}	
					}
				}
			break;
            // ������� ��� ����������
		}
	}
	// boal AI ����� -->
    if (!bIsCompanion) //fix 171204 boal �� ����� ����� � ����� �������
    {
        string sGroupID = Ship_GetGroupID(rCharacter);
		//Lipsar --->�� ��������
		if(CheckAttribute(rCharacter, "fortDefender") && sti(rCharacter.fortDefender) == 1 && bSeaActive && rCharacter.SeaAI.Task == "3")
		{
			string defGroupID = rCharacter.SeaAI.Task.Target;
			Log_Info(defGroupID);
			if (pchar.Ship.LastBallCharacter == defGroupID) 
			{
				Group_SetEnemyToCharacter(sGroupID, Pchar);
				Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				Group_LockTask(sGroupID);
				DoQuestCheckDelay("NationUpdate", 0.7);
				return;
			}
			ref attckChar;
			ref fortChar = &characters[sti(rCharacter.SeaAI.Task.Target)];
			if (sti(rCharacter.Ship.LastBallCharacter) != -1 || CheckAttribute(fortChar,"Ship.LastBallCharacter")) 
			{
				if (sti(rCharacter.Ship.LastBallCharacter) != -1) attckChar = &characters[sti(rCharacter.Ship.LastBallCharacter)];
				else attckChar = CharacterFromId(fortChar.Ship.LastBallCharacter);
				if (GetNationRelation2Character(sti(rCharacter.nation), GetCharacterIndex(attckChar.id)) == RELATION_ENEMY && sti(rCharacter.SeaAI.Task.Target) != GetCharacterIndex(attckChar.id))
				{
					Group_SetEnemyToCharacter(sGroupID, attckChar);
					Group_SetTaskAttack(sGroupID, Ship_GetGroupID(attckChar));
					Group_LockTask(sGroupID);
					rCharacter.SeaAI.Task = AITASK_ATTACK;
					rCharacter.SeaAI.Task.Target = GetCharacterIndex(attckChar.id);
				}
			}
			return;
		}//<---Lipsar �� ��������
		if (CheckAttribute(rCharacter, "SeaAI.Task.Target"))
		{
	        if (iNewBallType < 0 || iShipCannonsNum < (sti(rShip.CannonsQuantity) / 2))
			{
				// maybe we can abordage???
				Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));
				return;
			}
		}
		if (GetNationRelation2MainCharacter(sti(rCharacter.nation)) == RELATION_ENEMY) // ���� �� �����
	    {
            if (CheckAttribute(rCharacter, "AlwaysFriend"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	        }
	        else
	        {
				//--> eddy. �������� ����. ��������� ������� �����, ������������ � ���������� ����
				if (CheckAttribute(rCharacter, "WatchFort") && bIsFortAtIsland && GetRelation(sti(rCharacter.index), iFortCommander) == RELATION_ENEMY && !CheckAttribute(rCharacter, "ShipTaskLock"))
				{
					if (sti(rCharacter.Tmp.fWatchFort) >= sti(rCharacter.Tmp.fWatchFort.Qty))
					{					
						rCharacter.Tmp.fWatchFort = 0; //����� �������� �����������
						//��������� ���������� �� ����� � ������� ����� '������� �� ������'
						if (GetDistance2D(stf(rCharacter.Ship.Pos.x), stf(rCharacter.Ship.Pos.z), fFort_x, fFort_z) < 2000)
						{
							Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), iFortCommander);
							rCharacter.Tmp.fWatchFort.Qty = 200; //�� ����� ����, �� ����������� ����� ������������
							//Log_SetStringToLog("� ("+rCharacter.id+") ����� �� �����."); 
						}
					}
					else
					{
						rCharacter.Tmp.fWatchFort = sti(rCharacter.Tmp.fWatchFort) + 1;
					}
				}
				//<-- �������� ����
				if (!CheckAttribute(rCharacter, "SinkTenPercent")) // ��� �� �� � �� ������ �� ������� ������
	            {
					int   SailsPercent    = sti(rCharacter.Ship.SP);
			        float HPPercent       = GetHullPercent(rCharacter);
			        int   CrewQuantity    = sti(rCharacter.Ship.Crew.Quantity);
			        int   MinCrewQuantity = GetMinCrewQuantity(rCharacter);
					int   iCharactersNum1, iCharactersNum2;

					if (GetRelation(sti(rCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
					{
						SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
				        Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				        UpdateRelations();
				        DoQuestCheckDelay("NationUpdate", 0.9);
			        }
                    if (sti(rCharacter.Ship.LastBallCharacter) != -1 && !CheckAttribute(rCharacter, "Ship_SetTaskAbordage") && !CheckAttribute(rCharacter, "ShipTaskLock")) // ��� ������� �� �������
                    {
						if (!CheckAttribute(rCharacter, "SeaAI.Task") || sti(rCharacter.SeaAI.Task) == AITASK_NONE)
				        {
							//��� ��� �����, ����� ������������. �� ��� �� �����...
							if (CheckAttribute(rCharacter, "AnalizeShips"))
							{									
								//��������, ����� �� ���������
								if (stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 4))
								{
									Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
								else
								{
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}							
							}
							else
							{	//��� ��� �������� �������� �������� - ������ � �����
								Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							}									        
						}
				        else
				        {
							if ((SailsPercent > 50) && (HPPercent > 30) && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY) // �� ������� ���
					        {
								//������� � ������� ���������, ���� �� �������. ����� ���� �������� ��� ������� �������� ������� ��������
								if (CheckAttribute(rCharacter, "AnalizeShips"))
								{									
									// Warship fix ������ ���� �����
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
									
									if(stf(rCharacter.ship.hp) < (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
									{
										if ((iCharactersNum1 / iCharactersNum2) >= 1.0 && iCharactersNum2 > 0) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
									else
									{	//���� ���� ���� ��������, �� ��������� ��� � �������������� ����������� �����. �� ����� �� ������� �������
										if((iCharactersNum2 / iCharactersNum1) >= 3.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
										else
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
										}
									}
								}
								else
								{	//��� ��� �������� �������� �������� - ������ � �����
									Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
								}
					        }  
					        else
					        {
						        // ���������!!!
						        if (HPPercent < 15)
						        {
						            if (rand(20) == 1)// ����� ����� ����� - ������� ��� ������
						            {
						                Ship_SetTaskBrander(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
						            }
						        }
						        else
						        {
						        	if ((HPPercent < 25) || (CrewQuantity <= (4*MinCrewQuantity)))// ������, �� ������ ���� || SailsPercent < 35)
							        {
							            Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
							        }
									else
									{	//eddy. ����� ������� Runaway. ��������� ������� ������� ����� � ��������, ����� �� ���������
										if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) > (stf(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.hp) / 2))
										{
											//����� ������ ��� ���� �� �����? 
											if (sti(rCharacter.Tmp.fWatchFort.Qty) == 200)
											{
												//����� Runaway ������ �� ���� ���� �� �������� �����
												if (sti(rCharacter.Tmp.fWatchFort) >= 199)
												{
													if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
													{	//������ �� �� ��������������, ��������� �� ������
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}
											else
											{	//���� ��� �� ��� ���
												if (sti(rCharacter.Ship.LastBallCharacter) == iFortCommander)
												{	//������ �� �� ��������������, ��������� �� ������
													Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
												}
												else
												{
													iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
													iCharactersNum2 =  Group_GetLiveCharactersNum(characters[sti(rCharacter.Ship.LastBallCharacter)].SeaAI.Group.Name);	
													if ((iCharactersNum2 / iCharactersNum1) >=3.0 && sti(RealShips[sti(rCharacter.ship.type)].Class) > sti(RealShips[sti(characters[sti(rCharacter.Ship.LastBallCharacter)].ship.type)].Class))
													{
														Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
													else
													{
														Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rCharacter.Ship.LastBallCharacter));
													}
												}
											}		
										}
									}
						        }
					        }
				        }
			        }
			        else
			        {   
						// ���� ������ ���� � ��� rCharacter.Ship.LastBallCharacter (����� �� ���� �� �������)
                        if (!CheckAttribute(rCharacter, "ShipTaskLock"))
						{
				            if (!CheckAttribute(rCharacter, "SeaAI.Task.Target") || sti(rCharacter.SeaAI.Task.Target) == -1)
					        {
								if (CheckAttribute(rCharacter, "SeaAI.Task") && sti(rCharacter.SeaAI.Task) != AITASK_RUNAWAY)
								{
									//����������������� ���, ��������� ������� ������� �����. ���� ������� ���� � ��������� ���� - �����.
									if (CheckAttribute(rCharacter, "AnalizeShips") && stf(rCharacter.ship.hp) < (stf(pchar.ship.hp) / 2))
							        {									
										iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
										iCharactersNum2 =  Group_GetLiveCharactersNum(characters[GetMainCharacterIndex()].SeaAI.Group.Name);	
										if ((iCharactersNum1 / iCharactersNum2) >= 3.0) 
										{
											Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex()));
										}
										else
										{
											Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
										}		
									}
									else
									{	//���� ���� ���� �������� - �������
										Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
									}
								}
								else
								{	//eddy. � �� ������� � ��� ��� ���������� ����
						        	if (CheckAttribute(rCharacter, "AnalizeShips") && (HPPercent > 33) && (SailsPercent > 50) && stf(rCharacter.ship.hp) > (stf(pchar.ship.hp) / 4))
							        {
							            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
							        }
								}
					        }
				        }
			        }
		        }
		        else
		        {	// --> � ����� �������� �������� �� ����� ����������� ���� ���� �� ���������
					if (CheckAttribute(rCharacter, "PearlTartane") && sti(rCharacter.PearlTartane))
					{
						//#20180524-01 Remove unneeded sqrt
						if (Ship_GetDistance2DRel(GetMainCharacter(), rCharacter) < 256) // 16^ Rel, instead of 16)
						{
							PlaySound("interface\important_item.wav");
							int SmallPearlQty = rand(250) + 100;
							int BigPearlQty = rand(150) + 50;
							TakeNItems(pchar, "jewelry12", SmallPearlQty);
							TakeNItems(pchar, "jewelry11", BigPearlQty);
							Log_SetStringToLog("����� ������� �� ������� " + rCharacter.ship.name + " ������ ��� " + SmallPearlQty + " ����� � " + BigPearlQty + " ������� ��������.");
							rCharacter.PearlTartane = false; //��� ��������
							pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = sti(pchar.questTemp.Sharp.PearlAreal.SmallPearlQty) + SmallPearlQty;
							pchar.questTemp.Sharp.PearlAreal.BigPearlQty = sti(pchar.questTemp.Sharp.PearlAreal.BigPearlQty) + BigPearlQty;
							pchar.questTemp.Sharp = "SeaPearl_success"; //���� �������� ���������
						}
					}
					// <-- � ����� �������� �������� �� ����� ����������� ���� ���� �� ���������
					else
					{
						if (!CheckAttribute(rCharacter, "PearlTartane"))
						{
							Ship_SetTaskAttack(SECONDARY_TASK, iCharIdx, GetMainCharacterIndex());
						}
					}
		        }
	        }
	    }
	    else
	    {
	        // ����� �������������� ������������ ������������ ��� ������������ ���
	        // boal 030804 ����� �� ����, ��� ����� ��� ��� ������ ��� ��� � ��� ������!!!  �� ����� ����� �� ���������, �� ����������� ����
	        if (CheckAttribute(rCharacter, "AlwaysEnemy"))
	        {
	            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
	            Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	        }
	        else
	        {
                if (CheckAttribute(rCharacter, "AlwaysFriend"))
		        {
		            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
		        }
		        else
		        {
					// ���� ���������
			        if (sti(rCharacter.nation) != PIRATE || bBettaTestMode)//boal 030804 ����� ���� ��� ����� ���� � �������� �����
			        {
	                    SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), GetNationRelation2MainCharacter(sti(rCharacter.nation)));
						// �������� �� ������ ���� -->
						if (!CheckAttribute(rCharacter, "CheckFlagYet"))
						{
	                        if (!CheckAttribute(rCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rCharacter, "CheckFlagDate") > 1)
	                        {
								if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
							    {
							        rCharacter.CheckFlagYet = true; // ���, ��������
							        Ship_CheckFlagEnemy(rCharacter);
							        SaveCurrentNpcQuestDateParam(rCharacter, "CheckFlagDate");
							    }
						    }
						}
						// �������� �� ������ ���� <--
						// --> eddy. ����� ����. �� �������������� ������
						if (rCharacter.id == "MQPirate")
						{
							//������� �������� �� ���������, ���� �� ����
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 150 && !CheckAttribute(pchar, "GenQuest.DestroyPirate.WasFirstDeside"))
							{
								pchar.GenQuest.DestroyPirate.WasFirstDeside = true; //��� ������ ������� �� ����� �����
								bool fight, shipHealth, shipClass, shipCrew, bFort;
								fight = false;
								bFort = false;
								shipHealth = false;
								shipClass = false;
								shipCrew = false;
								aref arReloadLoc, arFort;
								makearef(arReloadLoc, Islands[FindIsland(pchar.location)].reload);
								string  sLabel;
								int iQty = GetAttributesNum(arReloadLoc);
								Log_TestInfo("Sea.MaxSeaHeight " + Sea.MaxSeaHeight);
								if (bIsFortAtIsland) //�.�. �����, �� ���� ��������� ������, �� ���������
								{
									if (GetDistance2D(stf(rCharacter.Ship.Pos.x), stf(rCharacter.Ship.Pos.z), fFort_x, fFort_z) < 1000)
									{
										bFort = true; //���� �����!!
									}
								}
								//������� ��������� ������� � ������� (0..1)
								if ((GetCurrentShipHP(pchar) / GetCharacterShipHP(pchar)) < 0.5 || (sti(pchar.ship.sp) / GetCharacterShipSP(pchar) < 0.4))
								{
									shipHealth = true;
								}
								//������� ����� �������
								if ((sti(RealShips[sti(rCharacter.ship.type)].Class) - sti(RealShips[sti(pchar.ship.type)].Class)) <= 1)
								{
									shipClass = true;
								}
								//������� ���-�� ������� �� �����, ������ � ���� ������
								if ((GetCrewQuantity(pchar) / GetMaxCrewQuantity(pchar)) < 0.4 || GetCrewExp(pchar, "Soldiers") < 20 || GetCharacterCrewMorale(pchar) < 20)
								{
									if ((GetCrewQuantity(pchar) / GetCrewQuantity(rCharacter)) < 1.34) shipCrew = true;
								}
								//�������� ���� ����� � ������ ����������� ��
								iQty = GetCompanionQuantity(pchar);
								if (iQty == 1)
								{
									if (shipHealth || shipClass || shipCrew) fight = true;
								}
								if (iQty == 2)
								{
									if (shipClass && shipCrew || shipHealth) fight = true;
								}
								if (iQty == 3)
								{
									if (shipClass && shipCrew && shipHealth) fight = true;
								}
								if (fight && !bFort) //���� ������� �������, �� �� ����� � ������
								{
	                                if (sti(rCharacter.nation) != PIRATE)
									{
										rCharacter.nation = PIRATE;
										Ship_NationAgressivePatent(rCharacter);
										Ship_FlagRefresh(characterFromId("MQPirate")); //���� �� ����
									}
									Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex);
								}
								pchar.GenQuest.DestroyPirate.shipState = shipCrew + shipClass + shipHealth; //� ������� ����� ����� �� ������� ������
								pchar.GenQuest.DestroyPirate.fortPlace = bFort; //� ���� �� �����, ��� ������� �� ������
								Log_QuestInfo("������ ������� (���-��/0-1): " + shipCrew);
								Log_QuestInfo("������ ������� (���-��/0-1): " + shipClass);
								Log_QuestInfo("������ ��������� ������� (���-��/0-1): " + shipHealth);
								Log_QuestInfo("� ���� ��������� ����� (���-��/0-1): " + bFort);
							}
							//������� ��������, ���� �� ������� �� ������� ����������. ��� ��� ������ �������� :)
							if (Ship_GetDistance2D(GetMainCharacter(), rCharacter) < 30 && CheckAttribute(pchar, "GenQuest.DestroyPirate.WasFirstDeside") && !CheckAttribute(pchar, "GenQuest.DestroyPirate.FastAbordage"))
							{
								pchar.GenQuest.DestroyPirate.FastAbordage = true; //��������� �������
								if ((GetCrewQuantity(pchar) / GetCrewQuantity(rCharacter)) < 1.0) //���� ��������, ��������� �� �����
								{
	                                if (sti(rCharacter.nation) != PIRATE)
									{
										rCharacter.nation = PIRATE;
										Ship_NationAgressivePatent(rCharacter);
										Ship_FlagRefresh(characterFromId("MQPirate")); //���� �� ����
									}
									Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex);
								}
								else
								{
									Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), nMainCharacterIndex); //���������
								}
							}
						}

			        }
			        else
			        {
			            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);//�� ���� ������ �������� ������
			        }
		        }
	        }
	        // fix �� ��������� ��� �������, ��� ����� ���������, � � ��� �� ��� ����� �������� <--

	        if (GetRelation(GetMainCharacterIndex(), sti(rCharacter.index)) == RELATION_ENEMY)
	        {
	            Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
	            UpdateRelations(); // ������� �� ����, �� ������� �� ����, ��� ���������� ��� ������ ��� �����
	        }
	        //UpdateRelations();  // to_do ��� ������ �����, ��� ������, �� ��������� �����
	    }
	    // AI ����� <--
    }
}

// �������� ����� ��� � ��, ��� �� �����?
void Ship_CheckFlagEnemy(ref rCharacter)
{
	ref     mChar = GetMainCharacter();
	int     iCompan, iClass;
	float   fSneak;
	int     i, cn;
	ref     chref;
	bool    bViewFlag = false;
	int     iNationToChange = sti(mChar.nation);  // ����

    if (sti(rCharacter.nation) == PIRATE) return;
    iCompan = GetCompanionQuantity(mChar);
    iClass  = 7;
	// ����� ���.  �� �������� ������
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(), i);
		if (cn>=0)
		{
			chref = GetCharacter(cn);
            if (GetCharacterShipClass(chref) < iClass) iClass = GetCharacterShipClass(chref);
		}
	}
    if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) == RELATION_ENEMY && GetDaysContinueNationLicence(sti(rCharacter.nation)) == -1) // �������� ������
    {
        // to_do ch.CheckLicence    = true; // ��������� ������� �������� �������� ��� �����������,����� ������ � ������������
		iNationToChange = GetBaseHeroNation();
        bViewFlag       = true;
    }
    if (!bViewFlag)
    {
        if (ChangeCharacterHunterScore(mChar, NationShortName(sti(rCharacter.nation)) + "hunter", 0) > (8 + rand( (iClass-1)*(9-iCompan) ) ))
        {
            bViewFlag       = true;
            iNationToChange = PIRATE;
        }
    }
    if (bViewFlag)
    {  // ������� ���� � �� � ������ � ���...

		fSneak  = stf(mChar.TmpSkill.Sneak); // 0.01..1.0
		int rep = sti(abs(REPUTATION_NEUTRAL - sti(mChar.reputation)) * 0.75);
		int losechance = rand(100) + rand(20) + rand(rep) - GetCharacterSPECIALSimple(pchar, SPECIAL_L)*2;
		int winchance = makeint(fSneak * 10 * iClass * (9-iCompan));
		Log_TestInfo("���������: "+losechance+"/������� ��������: "+winchance);
		if (losechance > winchance)
		{
			Log_Info("����� �� ����� �� ������� - "+ NationNamePeople(sti(rCharacter.nation)) + " ���������� � ��� �����.");
			SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
			DoQuestCheckDelay(NationShortName(iNationToChange) + "_flag_rise", 0.1); // ���������� ��� ��������� �����
			if (!CheckAttribute(pchar,"questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay()-1;
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, 50);
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
		else
		{ // �� �����
			if (!CheckAttribute(pchar,"questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay()-1;
			if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			{
				AddCharacterExpToSkill(mChar, SKILL_SNEAK, (iCompan * 200 / iClass));
				ChangeCrewExp(mChar, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(mChar, "SeaWolf"), 0.5, 1.0));
				pchar.questTemp.stels.sea = GetDataDay();
			}
		}
	}
}

void Ship_ActivateFirePlace()
{
	aref	arShipObject = GetEventData();
	aref	arCharacter = GetEventData();
	int		iFirePlaceIndex = GetEventData();
	string	sSoundName = GetEventData();
	float	fFireTime = GetEventData();
	int		iBallCharacterIndex = GetEventData();

	if (!bAbordageStarted) // fix
	{
		SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "ship_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
	}
}

void Ship_BranderDetonate()
{
	ref		rCharacter = GetCharacter(GetEventData());

	ref		rBranderBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
 	float	fBranderDistance = 1.9 * (45.0 + (7.0 - stf(rBranderBaseShip.Class)) * 15.0); //fix
 	fBranderDistance *= fBranderDistance;
	//float	fMaxDamage = 1000.0 + (7.0 - stf(rBranderBaseShip.Class)) * 700.0;  //fix
	float   fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 4;

	aref	arShipObjects[64];
	int		iBranderNumShips = 1;
	
	if(CheckAttribute(rCharacter,"Situation") && rCharacter.situation == "Explosion" ) // �������� �� �������
	{
		fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 3;
		if(GetCargoGoods(rCharacter, GOOD_POWDER) < 300) { fMaxDamage += 400.0; }	
		ref mc = GetMainCharacter();
		int iDiffClass = sti(RealShips[sti(mc.Ship.Type)].Class) - sti(RealShips[sti(rCharacter.Ship.Type)].Class);
		if(iDiffClass > 0) fMaxDamage += iDiffClass * 500.0;
	}	
	if (!FindClass(&arShipObjects[0], "ship")) { return; }// can't be
	while (iBranderNumShips < 64 && FindClassNext(&arShipObjects[iBranderNumShips])) { iBranderNumShips++; }
	// enumerate ship and do damage
	iBranderNumShips = i_min(63, iBranderNumShips);
	for (int i=0; i<iBranderNumShips; i++)
	{
		int iCharacterIndex = -1;
		SendMessage(arShipObjects[i], "le", MSG_SHIP_GET_CHARACTER_INDEX, &iCharacterIndex);
		if (iCharacterIndex == sti(rCharacter.index)) { continue; }
		ref rOtherCharacter = GetCharacter(iCharacterIndex);
		ref	rOtherBaseShip = GetRealShip(sti(rOtherCharacter.Ship.Type));
		float fDistance = Ship_GetDistance2DRel(rCharacter, rOtherCharacter);
		if (fDistance > fBranderDistance) { continue; }
		float fDamageMultiply = Bring2Range(1.0, 0.0, 10.0, sqrt(fBranderDistance), sqrt(fDistance));
		Ship_ApplyHullHitpoints(rOtherCharacter, fMaxDamage * fDamageMultiply, KILL_BY_SPY, sti(rCharacter.index));
		// fire random fire places
		//int iNumFirePlaces = 0;
		//SendMessage(&arShipObjects[i], "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);

		// add move impulse to ship
		float x = stf(rOtherCharacter.Ship.Pos.x) - stf(rCharacter.Ship.Pos.x);
		float z = stf(rOtherCharacter.Ship.Pos.z) - stf(rCharacter.Ship.Pos.z);
		float fLen = stf(rOtherBaseShip.Class) * fDamageMultiply * (1.0 / sqrt(x * x + z * z));
		SendMessage(&arShipObjects[i], "llffffff", MSG_SHIP_ADD_MOVE_IMPULSE, false, x * fLen, 0.0, z * fLen, 0.0, 0.0, 0.0);
	}

	Ship_Detonate(rCharacter, true, true);
}

float Ship_GetDistance2D(ref rCharacter1, ref rCharacter2)
{
	if (CheckAttribute(rCharacter1, "Ship.Pos.x") && CheckAttribute(rCharacter2, "Ship.Pos.x")) // fix boal
	{
		return GetDistance2D(stf(rCharacter1.Ship.Pos.x), stf(rCharacter1.Ship.Pos.z), stf(rCharacter2.Ship.Pos.x), stf(rCharacter2.Ship.Pos.z));
	}   
	else
	{
		return 1000.0;
	}
}

//#20180524-01 Remove unneeded sqrt
float Ship_GetDistance2DRel(ref rCharacter1, ref rCharacter2)
{
	if (CheckAttribute(rCharacter1, "Ship.Pos.x") && CheckAttribute(rCharacter2, "Ship.Pos.x")) // fix
	{
		return GetDistance2DRel(stf(rCharacter1.Ship.Pos.x), stf(rCharacter1.Ship.Pos.z), stf(rCharacter2.Ship.Pos.x), stf(rCharacter2.Ship.Pos.z));
	}
	else
	{
		return 1000000.0;
	}
}

int Ship_FindOtherBallType(ref rCharacter, float fMinEnemyDistance, bool bBalls, bool bBombs, bool bGrapes, bool bKnippels)
{
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float range = stf(rCannon.FireRange);
	if (checkAttribute(rCharacter, "SeaAI.task.target") && rCharacter.SeaAI.task.target != "") //fix
	{
		int enemy = sti(rCharacter.SeaAI.task.target);
		ref rBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
		
		rCannon = GetCannonByType(sti(characters[enemy].Ship.Cannons.Type));
		float TargetRange = stf(rCannon.FireRange);

		int iType = -1;
		float fRangeModifier = 1.0;
		// ����������� float fDistance = Ship_GetDistance2D(rCharacter, &characters[enemy]);

		if (bBalls) //(fMinEnemyDistance <= range) && //���� ��������� ������, �� ��� ����� �� ����
		{
			iType = GOOD_BALLS;
		}

		if ((fMinEnemyDistance <= (range * 0.8)) && bKnippels) 
		{
			if (sti(characters[enemy].ship.sp) > 30 && ShipSailState(enemy) >= 0.5)  // ����� ��� ����������  ShipSailState - 0 ��� ������ 1 ������ 2 - ������
			{
				iType = GOOD_KNIPPELS;
			}
			fRangeModifier = 0.8;
		}

		if ((fMinEnemyDistance <= (range * 0.5)) && bBombs)
		{
			iType = GOOD_BOMBS;
			fRangeModifier = 0.6;
		}

		if ((fMinEnemyDistance <= (range * 0.2)) && bGrapes)
		{
			if (sti(characters[enemy].ship.crew.quantity) > sti(rBaseShip.MinCrew))
			{
				iType = GOOD_GRAPES;  
			}
			fRangeModifier = 0.3;
		}

		rCharacter.Ship.SeaAI.Init.AttackDistance = range * fRangeModifier / (1.4 + frandSmall(3.0));
		return iType;
	}
	
	if (bBalls) return GOOD_BALLS;
	if (bBombs) return GOOD_BOMBS;
	if (bKnippels) return GOOD_KNIPPELS;
	if (bGrapes) return GOOD_GRAPES;
	
	return -1;
}

// event: indicate that ball is not enough for fire for main character
void Ship_NotEnoughBalls()
{
	bNotEnoughBalls = GetEventData();
	// boal -->
	if (!bNotEnoughBalls)
	{
	    if (GetCargoGoods(pchar, GOOD_POWDER) < 1)
	    {
	        bNotEnoughBalls = true;
	    }
	}
	// boal <--

}

int Ship_GetCurrentBallsNum()
{
	aref aCharacter = GetEventData();
	return GetCargoGoods(aCharacter,sti(aCharacter.Ship.Cannons.Charge.Type));
}

void Ship_SailDamage()
{
	float x, y, z;
	int iCharacterIndex = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	string sSound;
	int	iBallType = sti(AIBalls.CurrentBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:	sSound = "ball2sail";	break;
		case GOOD_GRAPES:	sSound = "grapes2sail";	break;
		case GOOD_KNIPPELS:	sSound = "knippel2sail";	break;
		case GOOD_BOMBS:	sSound = "ball2sail"; break;
	}

	Play3DSound(sSound, x, y, z);
	if (rand(100) < 15) { Play3DSound("fly_ball_misc", x, y, z); }
}

void Ship_Ship2IslandCollision()
{
	float	fPower, fSlide, x, y, z;
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint, prevTask;
	
	iOurCharacterIndex = GetEventData();
	iEnemyCharacterIndex = GetEventData();
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

	if (iOurCharacterIndex != GetMainCharacterIndex())
		{
			Ship_SetTaskDrift(SECONDARY_TASK, iOurCharacterIndex);
			rOurCharacter.TmpPerks.Turn = true;
			rOurCharacter.TmpPerks.Turn.Angle = PI/1.3;//������� ����� �������� ������������ �� �������
			rOurCharacter.Tmp.SpeedRecall = 0;
		}

    if (!sti(rOurCharacter.TmpPerks.SandbankManeuver) && !CheckAttribute(rOurCharacter, "AlwaysSandbankManeuver"))  //boal
    {
		float fHP = (1.0 - fSlide) * fPower * 3.0;
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_ISLAND, -1);

		if (fPower > 1.0)  Play3DSound("coll_ship2rock", x, y, z); 
	}
	if (iOurCharacterIndex != GetMainCharacterIndex() && sti(rOurCharacter.SeaAI.Task)==AITASK_DRIFT)
		{
			Ship_SetTaskAttack(PRIMARY_TASK, sti(iOurCharacterIndex), GetMainCharacterIndex());//� ��������� � �����; ��������� Lipsar
			rOurCharacter.Tmp.SpeedRecall = 0;
		}
}

float Ship_GetAttackHP(int iCharacterIndex, float fDistance)
{
	float fAttackHP = 0.0;
	if (bSeaActive)
	{
		SendMessage(&AISea, "lafe", AI_MESSAGE_SHIP_GET_ATTACK_HP, &Characters[iCharacterIndex], fDistance, &fAttackHP);
	}
	return fAttackHP;
}

float Ship_GetHP(ref rCharacter) 
{ 
	return stf(rCharacter.Ship.HP); 
}

void Ship_Ship2ShipCollision()
{
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;
	float	fPower, fSlide, x, y, z;
	
	iOurCharacterIndex = GetEventData();   // ����
	iEnemyCharacterIndex = GetEventData();  // ���
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	
	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

	float fHP = (1.0 - fSlide) * fPower * 10.0;
	//Trace("Ship->Ship touch: idx = " + iOurCharacterIndex + ", fpower = " + fPower + ", fHP = " + fHP + ", fSlide = " + fSlide);
	Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_TOUCH, iEnemyCharacterIndex);
	// ������ �� ���������� ������� -->
	if (iEnemyCharacterIndex == GetMainCharacterIndex() && GetHullPercent(rOurCharacter) <= 14  && !LAi_IsDead(rOurCharacter))
	{
		if (!IsCompanion(rOurCharacter) && GetRelation(sti(rOurCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
		{
			Ship_NationAgressive(rOurCharacter, rOurCharacter);
			NationUpdate();
	    	DoQuestCheckDelay("NationUpdate", 0.9);
    	}
	}
	// ������ �� ���������� ������� <--

	if (fPower>1.0) { Play3DSound("coll_ship2ship", x, y, z); }
}

void Ship_ApplyCrewHitpoints(ref rOurCharacter, float fCrewHP)
{         // ��-�� ������ ����� "���������" - ��������� 29.07.06 boal
	if (LAi_IsImmortal(rOurCharacter)) 
	{ 
		return; 
	}
    if (MOD_SKILL_ENEMY_RATE == 1 && sti(rOurCharacter.index) == GetMainCharacterIndex())
	{
		fCrewHP = fCrewHP / MOD_Complexity_1_DMG;
	}
	ref rBaseShip = GetRealShip(GetCharacterShipType(rOurCharacter));
	float fMultiply = 1.0 - (0.75 * stf(rOurCharacter.TmpSkill.Defence)); // ���� 0.05 - ��� ������ �����, �� ���� 0..1

	if(CheckOfficersPerk(rOurCharacter, "Doctor2"))
	{
		fMultiply = fMultiply * 0.8;
	}
	else
	{
		if(CheckOfficersPerk(rOurCharacter, "Doctor1"))
		{
			fMultiply = fMultiply * 0.9;
		}
	}
	float fDamage = fCrewHP * fMultiply; 

	float fNewCrewQuantity = stf(rOurCharacter.Ship.Crew.Quantity) - fDamage;
	float f5Percent = stf(rBaseShip.MinCrew) * 1.0; //WW boal fix ����������� 25 ��������� �������- ���� 0.05;
	// boal  check skill -->
	if (fNewCrewQuantity >= f5Percent && IsCompanion(rOurCharacter))
	{
       AddCharacterExpToSkill(rOurCharacter, "Defence", makefloat(fCrewHP / 2 + 0.5));
       ChangeCrewExp(rOurCharacter, "Soldiers",  (fCrewHP / stf(rBaseShip.OptCrew))); // to_do ����� ���� �����
    }
    // boal <--
	
	if (fNewCrewQuantity < f5Percent) { fNewCrewQuantity = f5Percent; }
	if (fNewCrewQuantity < 0.0) { fNewCrewQuantity = 0.0; }
	
	if (sti(rOurCharacter.index) == GetMainCharacterIndex() && stf(rBaseShip.MinCrew) > fNewCrewQuantity && stf(rBaseShip.MinCrew) <= stf(rOurCharacter.Ship.Crew.Quantity))
    {  // ������� �� ��� �������
        PlaySound("OBJECTS\SHIPCHARGE\_Damage1.wav");
    }
	// boal fix ������������   -->
	if (stf(rOurCharacter.Ship.Crew.Quantity) > fNewCrewQuantity)
	{   // �� ������ ������� �� ������ fCrewHP
		if (sti(rOurCharacter.index) == GetMainCharacterIndex() || IsCompanion(rOurCharacter))
		{
			Statistic_AddValue(GetMainCharacter(), "Sailors_dead", stf(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity);
		}
		rOurCharacter.Ship.Crew.Quantity = fNewCrewQuantity;
	}
	if (stf(rOurCharacter.Ship.Crew.Quantity) < 0.0) { rOurCharacter.Ship.Crew.Quantity = 0.0; }
	// boal fix ������������   <--
}

void Ship_ApplyHullHitpoints(ref rOurCharacter, float fHP, int iKillStatus, int iKillerCharacterIndex)
{
   	if (LAi_IsImmortal(rOurCharacter)) { return; }

	float fCurHP;
	float fMinus = 0.0;
	float fPlus = 0.0;
	//float fAccuracy = 0.0;
	
    if (bSeaReloadStarted) { return; }
    if (MOD_SKILL_ENEMY_RATE == 1 && sti(rOurCharacter.index) == GetMainCharacterIndex())
	{
		fHP = fHP / MOD_Complexity_1_DMG;
	}
	if (fHP <= 0.0) { return; }
	if (LAi_IsDead(rOurCharacter) || !CheckAttribute(rOurCharacter, "Ship.HP")) { return; }   // fix

    if (iKillerCharacterIndex >= 0)
	{
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.HullDamageUp)) fPlus = 0.15;
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.CannonProfessional)) fPlus = 0.3;
		//fAccuracy = stf(characters[iKillerCharacterIndex].TmpSkill.Accuracy);
	}

	if (sti(rOurCharacter.TmpPerks.BasicBattleState))			fMinus = 0.15;
	if (sti(rOurCharacter.TmpPerks.AdvancedBattleState))		fMinus = 0.25;
	if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional))	fMinus = 0.35;

	fCurHP = stf(rOurCharacter.Ship.HP) - fHP * (1.0 + fPlus - fMinus);
	if (fCurHP <= 0.0)
	{
		fCurHP = 0.0;
		ShipDead(sti(rOurCharacter.index), iKillStatus, iKillerCharacterIndex);
	}
	
    if(fCurHP > sti(RealShips[sti(rOurCharacter.ship.type)].HP))
	{
		fCurHP = RealShips[sti(rOurCharacter.ship.type)].HP;
	}
	rOurCharacter.Ship.HP = fCurHP;
}


void Ship_AddCharacterExp(ref rCharacter, int iExpQuantity)
{
	if(IsCompanion(rCharacter) == true || rCharacter.id == pchar.id)
	{
		AddPartyExp(pchar, iExpQuantity);
	}
	
	if (sti(rCharacter.index) == nMainCharacterIndex)
	{
		fSeaExp = fSeaExp + iExpQuantity;
	}
}


void ShipDead(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rBaseShip, rKillerBaseShip;
	
	rDead = GetCharacter(iDeadCharacterIndex);
	
	if (!CheckAttribute(rDead, "Ship.Type")) // fix
    {
        if (MOD_BETTATESTMODE == "On") Log_Info("Error: ShipDead ��� ������� � iDeadCharacterIndex = "+iDeadCharacterIndex);
        return;
    }
    bool bDeadCompanion = IsCompanion(rDead);
	
	bool isPgg = HasSubStr(rDead.id,"PsHero_");	
	bool isntPgg1 = HasSubStr(rDead.id,"_Trader") && CheckAttribute(rDead,"PGG_companion");
	bool isntPgg2 = HasSubStr(rDead.id,"_Hunter") && CheckAttribute(rDead,"PGG_companion");

	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
    //#20180925-01
    float fBaseClass = stf(rBaseShip.Class);
	if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		// boal  check skill -->
		if (!bDeadCompanion && iKillStatus != KILL_BY_SPY)
        {
			switch (iKillStatus)
		    {
			    case KILL_BY_TOUCH:
	                AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / fBaseClass * 90);
	                ChangeCrewExp(rKillerCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 1.0, 2.0));
	                // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
	                // boal statistic info 17.12.2003 <--
					if (isPgg && !isntPgg1 && !isntPgg2)
					{ 
						DeleteAttribute(PChar,"PGG_EnemyPP");
						if(rKillerCharacter == pchar)
						{
							
							PChar.PGG_Enemy = "1";
						}
					}
			    break;
			    case KILL_BY_BALL:
			        AddCharacterExpToSkill(rKillerCharacter, "Accuracy", stf(rKillerBaseShip.Class) / fBaseClass * 35);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / fBaseClass * 65);
			        AddCharacterExpToSkill(rKillerCharacter, "Cannons", stf(rKillerBaseShip.Class) / fBaseClass * 40);
			        ChangeCrewExp(rKillerCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 1.0, 2.0));
			        ChangeCrewExp(rKillerCharacter, "Cannoners", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 2.0, 4.0));
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
	                // boal statistic info 17.12.2003 <--
	                //homo 25/06/07 ������ ���� � 1/4
        			if (rand(4) == 2 && GetRelation(sti(rDead.Index), sti(Pchar.Index))== RELATION_ENEMY)
                    {
                        //�������
                        if(!CheckAttribute(rDead, "DontRansackCaptain") || rDead.DontRansackCaptain == false) AISeaGoods_AddGood(rDead, "enemy_boat", "lo_boat", 1000.0, 1); //homo 25/06/07 ��������� �� ������
                    }
                    //homo
					if (isPgg && !isntPgg1 && !isntPgg2)
					{ 
						DeleteAttribute(PChar,"PGG_EnemyPP");
						if(rKillerCharacter == pchar)
						{
							PChar.PGG_Enemy = "1";
						}
					}
			    break;
			    case KILL_BY_ABORDAGE:
			        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / fBaseClass * 110);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / fBaseClass * 70);
			        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / fBaseClass * 10);
			        AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / fBaseClass * 60);
			        ChangeCrewExp(rKillerCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 0.5, 1.0));
					// � ���_������� ChangeCrewExp(rKillerCharacter, "Soldiers", 4);
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillAbordShip_" + rBaseShip.Class, 1);
	                // boal statistic info 17.12.2003 <--
					if (rKillerCharacter == pchar) FlagPerkForCapturedShip(rDead);
					if (isPgg && !isntPgg1 && !isntPgg2)
					{ 
						DeleteAttribute(PChar,"PGG_EnemyPP");
						if(rKillerCharacter == pchar)
						{
							
							PChar.PGG_Enemy = "1";
						}
					}
			    break;
		    }
			if (iKillStatus != KILL_BY_SELF)
			{
		        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / fBaseClass * 20);
		        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / fBaseClass * 25);

	            // ��������� �� �����
		    	Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_KillShip", 1);
		    	if (rand(8) < 3 && sti(rDead.nation) != PIRATE)  // 30 ��������� �������� �������
		    	{
					ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
				}
			}
        }
        // boal 04.04.04 <--
	}
	
	float fX = stf(rDead.Ship.Pos.x);
	float fY = stf(rDead.Ship.Pos.y);
	float fZ = stf(rDead.Ship.Pos.z);

	rDead.Ship.HP = 0;
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
	
	LAi_SetCurHP(rDead, 0.0);
  
	if (CheckAttribute(rDead, "curshipnum")) 
	{
		DeleteAttribute(rDead, "curshipnum");
	}
	int iExp = 0;
	if (iKillerCharacterIndex != -1) 
	{ 
		iExp = 2 * MakeInt(stf(rBaseShip.HP) * stf(rKillerBaseShip.Class) / fBaseClass);
	}

	bool bCompanion = false;
	if (iKillerCharacterIndex != -1) 
	{ 
		bCompanion = IsCompanion(rKillerCharacter); 
	}

 	if (bCompanion && bDeadCompanion)
	{
		iExp = 0;
		// boal -->
		if (iKillerCharacterIndex == GetMainCharacterIndex())
		{
			ChangeCharacterReputation(pchar, -15);
		}
		// boal <--
	}      
    
	bool bRealKill = false;
	switch (iKillStatus)
	{
		case KILL_BY_TOUCH:
			if (iKillerCharacterIndex != -1) { bRealKill = true; }
		break;
		case KILL_BY_BALL:
			bRealKill = true;
		break;
		case KILL_BY_ABORDAGE:
			bRealKill = true;
		break;
	}

	// Ship sunk log
	if (iDeadCharacterIndex != nMainCharacterIndex)
	{
		string sSunkString;
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = "";
		string sKillShipName = "";
		if (iKillerCharacterIndex != -1)
		{
		    sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);
		    sKillShipName = "" + rKillerCharacter.Ship.Name;
		}
		if (bCompanion && !bDeadCompanion && bRealKill)
		{
            sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "��� �������� ", "���� ��������� ") + GetFullName(rKillerCharacter);
        }
        else
        {
            if (sKillShipName == "")
            {
            	sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, "��� ��������.", "���� ���������.");
            }
            else
            {
				sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, "��� �������� ", "���� ��������� ") + sKillShipType + " '" + sKillShipName + "'";
			}
        }
		Log_SetStringToLog(sSunkString);
	}

 	if (rand(10) >= 6) // ������ �������... ��� ��� ������ :)  && sti(rBaseShip.Class) <= 6)
	{ 
		bool bDetonate = false;
		switch (iKillStatus)
		{
			case KILL_BY_BALL:	
				bDetonate = true; 
			break;
			/*case KILL_BY_SPY:	
				bDetonate = true; 
			break;  */ // ���� �����, ���� ������ ��� �������� Ship_Detonate ������
		}
		if (bDetonate) 
		{ 
			Ship_Detonate(rDead, true, false); 
		}
	}

	// set attributes for sinking effect
	rDead.Ship.Sink = "";
	aref aSink; makearef(aSink, rDead.Ship.Sink);
/*	
	aSink.Speed.y = 0.35;	// speed of sink y
	aSink.Speed.x = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z
*/
	// ������� �����  - ������� ������� ����������� :-)
	aSink.Speed.y = 0.25 + (frnd() * 0.05);	// speed of sink y
	aSink.Speed.x = 0.021 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.04 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z

	if(rDead.id == "GhostCapt" && iKillerCharacterIndex == nMainCharacterIndex && !CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") && !CheckAttribute(pchar, "GenQuest.GhostShip.Prize"))
	{
		pchar.GenQuest.GhostShip.Prize = true;
		InterfaceStates.Buttons.Save.enable = false;
		DoQuestCheckDelay("GhostCapt_OfferPrize", 1.5); // ���-���-������ � ������ !!!
	}
	if (iDeadCharacterIndex == nMainCharacterIndex)
	{ 
		SeaCameras_SetDieCamera();
		FadeOutMusic(2);
		//PlayStereoOGG("music_ship_dead");
		// ���� ��
		if (iKillerCharacterIndex != -1 && rKillerCharacter.id == "GhostCapt")
		{
		    DoQuestCheckDelay("Survive_In_Sea", 9.0);
		}
		else
		{
			InterfaceStates.Buttons.Save.enable = false;
			PostEvent(GAME_OVER_EVENT, 15000);
		}
	}
    // ������ �������� boal 07/02/05
	else
	{
        if (bDeadCompanion && CheckOfficersPerk(rDead, "ShipEscape") && GetRemovable(rDead)) // ��������
        {
            //homo 22/06/07
            AISeaGoods_AddGood(rDead, "boat", "lo_boat", 1000.0, 1);
            RemoveCharacterCompanion(pchar, rDead);
            Log_Info(GetFullName(rDead) + " ������ �� ������.");
        }
	}
	// ������ �������� boal 07/02/05
	Play3DSound("ship_sink", fX, fY, fZ);

	// Message to AI
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rDead);

	// Event
	Event(SHIP_DEAD, "l", iDeadCharacterIndex);
}

// boal -->
void ShipTaken(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();
    //#20180925-01
    float fBaseClass = stf(rBaseShip.Class);
	bool bCompanion = false;
	bool bDeadCompanion = IsCompanion(rDead);

    LAi_SetCurHP(rDead, 0.0); // ����
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1 && !bDeadCompanion)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		bCompanion = IsCompanion(rKillerCharacter);
		// boal  check skill -->
        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / fBaseClass * 20);
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / fBaseClass * 25);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / fBaseClass * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / fBaseClass * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Commerce", stf(rKillerBaseShip.Class) / fBaseClass * 30);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / fBaseClass * 60);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / fBaseClass * 60);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_AddValue(rKillerCharacter, "AbordShip_" + rBaseShip.Class, 1);
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShip", 1);
        // boal statistic info 17.12.2003 <--
        
        ChangeCrewExp(rKillerCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 0.5, 1.0));
		// � ���_������� ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do ��������� �� ����� �������
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex())
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

		if(bCompanion && !bDeadCompanion)
		{
            Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "��� ��������!");
        }
	}
    if (rand(8) < 3 && !bDeadCompanion && sti(rDead.nation) != PIRATE)  // 30 ��������� �������� �������
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// ����������� �������, �������
void ShipTakenFree(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();
    //#20180925-01
    float fBaseClass = stf(rBaseShip.Class);
    LAi_SetCurHP(rDead, 0.0); // ����
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / fBaseClass * 50);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / fBaseClass * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / fBaseClass * 80);
		AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / fBaseClass * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / fBaseClass * 10);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / fBaseClass * 10);
        
		Statistic_AddValue(rKillerCharacter, "AbordShipFree_" + rBaseShip.Class, 1);  // ��� ���������� ���� ����� �� ����� to_do
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShipFree", 1);
        Statistic_AddValue(rKillerCharacter, "AbordShipFree", 1); // ��������
        
        ChangeCrewExp(rKillerCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rKillerCharacter, "SeaWolf"), 0.5, 1.0));
		// � ���_������� ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do ��������� �� ����� �������
		if(!CheckAttribute(rDead,"Situation"))
		{
			ChangeCharacterReputation(rKillerCharacter, 2); // ������� ����
			OfficersReaction("good");
		}	
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex() && !CheckAttribute(rDead,"Situation"))
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

        Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + "��� ��������, �� ������� ����� �������.");
	}
    if (rand(20) < 3 && sti(rDead.nation) != PIRATE)  // 14 ��������� �������� �������
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// boal <--

void Ship_PlayVictory(string sSound, int iSoundTime)
{
	FadeOutMusic(3); // boal 3000
	PlayStereoOgg(sSound);

	iVicSoundTime = iSoundTime;
}
  /// �������� ������ ??? �� ���� �� � ��� � ��� ���� ���
void Ship_VicSoundTime()
{
	if (bAbordageStarted || sti(InterfaceStates.Launched)) { return; }

	if (iVicSoundTime > 0)
	{
		iVicSoundTime = iVicSoundTime - iRealDeltaTime;
		if (iVicSoundTime <= 0)
		{
			bUpdatePosMode = true;
		}
	}
}

void Ship_SailHitEvent()
{
}

void Ship_HullHitEvent()
{
	float	fHP;

	int		iBallType = sti(AIBalls.CurrentBallType);

	aref	rShipObject = GetEventData();

	int		iBallCharacterIndex = GetEventData();
	int		iOurCharacterIndex = GetEventData();

	ref		rBallCharacter = GetCharacter(iBallCharacterIndex);	// ��� ������
	ref		rOurCharacter = GetCharacter(iOurCharacterIndex);   // �� ����
	
	//--->Lipsar ��� �� ��������
	if(CheckAttribute(rBallCharacter, "fortDefender") && sti(rBallCharacter.fortDefender) == 1 && bSeaActive && sti(rBallCharacter.SeaAI.Task.Target) != GetCharacterIndex(rOurCharacter.id))
	{
		string sGroupID = Ship_GetGroupID(rBallCharacter);
		if (GetNationRelation2Character(sti(rBallCharacter.nation), GetCharacterIndex(rOurCharacter.id)) == RELATION_ENEMY)
		{
			Group_SetEnemyToCharacter(sGroupID, rOurCharacter);
			Group_SetTaskAttack(sGroupID, Ship_GetGroupID(rOurCharacter));
			Group_LockTask(sGroupID);
			rBallCharacter.SeaAI.Task = AITASK_ATTACK;
			rBallCharacter.SeaAI.Task.Target = GetCharacterIndex(rOurCharacter.id);
		}
	}
	//<---Lipsar ��� �� ��������
	
	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;

	float	x = GetEventData();
	float	y = GetEventData();
	float	z = GetEventData();

	int		iFirePlaceIndex = GetEventData();   
	float	fFirePlaceDistance = GetEventData();

	bool	bDead = LAi_IsDead(rOurCharacter) && CheckAttribute(rBallCharacter, "Ship.Cannons.Type");  // boal fix

	bool	bSeriousBoom = false;
	bool	bInflame = false;
    bool    isOurCompanion   = IsCompanion(rOurCharacter);
    float   fTmpCannonDamage = 0;
    
    if (bDead) return; // ����, �� ����� ����������� ����
	// Cannon damage multiply
	ref rCannon = GetCannonByType(sti(rBallCharacter.Ship.Cannons.Type));
	float fCannonDamageMultiply = stf(rCannon.DamageMultiply);

	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));

    if (sti(rBallCharacter.TmpPerks.CriticalShoot) && rand(19)==10) { bSeriousBoom = true; }		// +5 ���������
	if (sti(rBallCharacter.TmpPerks.CannonProfessional) && rand(9)==4) { bSeriousBoom = true; }		// +10 ���������
	
	ref rBall = GetGoodByType(iBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:
			if (rand(85) == 17) { bSeriousBoom = true; }  // boal 35
			if (rand(30) == 15) { bInflame = true; }
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_GRAPES:
			bSeriousBoom = false;
			Play3DSound("grapes2bort", x, y, z);
            if (rand(100) < 30) {Play3DSound("episode_boom", x, y, z);}
		break;
		case GOOD_KNIPPELS:
			bSeriousBoom = false;
			Play3DSound("ball2bort", x, y, z);
		break;
		case GOOD_BOMBS:
			if (rand(50) == 10) { bSeriousBoom = true; }  // boal 20
			if (rand(5) == 1) { bInflame = true; }
			Play3DSound("bomb2bort", x, y, z);
		break;
	}
	fTmpCannonDamage = fCannonDamageMultiply * stf(rBall.DamageHull);
	if (rand(2) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0);// boal fix

    if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional) && rand(1000) < 700) { bSeriousBoom = false; }				// no seriouse boom

    float fCrewDamage = stf(rBall.DamageCrew) * fCannonDamageMultiply * AIShip_isPerksUse(rBallCharacter.TmpPerks.CrewDamageUp, 1.0, 1.15);

	if (bSeriousBoom)
	{
		fCrewDamage = fCrewDamage * 7.0;
		// fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull) * (8.0 + frnd() * 4.0); // LEO: ���������
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull) * 4; // 4.0
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex);

		if (iBallCharacterIndex == nMainCharacterIndex)
		{
			Log_SetStringToLog(LanguageConvertString(iSeaSectionLang, "Ship_critical"));
		}

		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 15);
            AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, 15);
            AddCharacterExpToSkill(rBallCharacter, "Leadership", 2);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 15);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 15);
            ChangeCrewExp(rBallCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rBallCharacter, "SeaWolf"), 0.05, 0.1));
			ChangeCrewExp(rBallCharacter, "Cannoners", AIShip_isPerksUse(CheckCharacterPerk(rBallCharacter, "SeaWolf"), 0.5, 1.0));
        }
        // boal <--
	}
	else
	{ 
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull);
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 2.5);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 1);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 1);
            ChangeCrewExp(rBallCharacter, "Cannoners", AIShip_isPerksUse(CheckCharacterPerk(rBallCharacter, "SeaWolf"), 0.01, 0.02));
        }
        // boal <--
	}
	Ship_ApplyCrewHitpoints(rOurCharacter, fCrewDamage);

	if (bInflame == true && fFirePlaceDistance < 4.0 && iFirePlaceIndex >= 0)
	{
		int iRandStartTime = rand(1000);
		float fTotalFireTime = Ship_GetTotalFireTime(rOurCharacter); 

		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rShipObject, rOurCharacter, iFirePlaceIndex, "ship_onfire", fTotalFireTime, iBallCharacterIndex);
		PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}

	if (bSeriousBoom == true) 
	{ 
		if (rOurCharacter.id == pchar.id || rand(2) == 1)
		{
			Ship_Serious_Boom(x, y, z); 
		}
		fTmpCannonDamage = fTmpCannonDamage * 6.0;
		//boal 27.09.05 -->
		if ((GetCargoGoods(rOurCharacter, GOOD_POWDER) / 20.0) > (GetCargoMaxSpace(rOurCharacter) * 0.25) && rand(1) == 1)
		{
			Ship_SetExplosion(rOurCharacter, rShipObject);
			Log_Info("�� ������� " + rOurCharacter.Ship.Name + " ������������ ���� ��������� �����.");
		}
		//boal 27.09.05 <--
	}
    SendMessage(&AISea, "laffff", AI_MESSAGE_CANNONS_BOOM_CHECK, rOurCharacter, fTmpCannonDamage, x, y, z);  // fix ������� � ��������� �� ����
	// boal 290704 ��� � ������ ��������� ����� �� �� �����, ���� ������ ����� ������ ������ -->
	//Log_Info(rOurCharacter.id);
	//Log_Info(" LastBallCharacter = "+rOurCharacter.Ship.LastBallCharacter);
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {
        if (!isOurCompanion && !CheckAttribute(rOurCharacter, "Coastal_Captain")) // �� ����� ����� ������ ������� �����
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);// boal 030804 � ���� �����
            NationUpdate();
            DoQuestCheckDelay("NationUpdate", 0.7);
        }
    }
    // boal 290704 ��� � ������ ��������� ����� �� �� �����, ���� ������ ����� ������ ������ <--
    //#20190113-06
    if(GetNationRelation(sti(rBallCharacter.Nation), sti(rOurCharacter.nation)) != RELATION_FRIEND) 
	{
        if(CheckAttribute(rOurCharacter, "SeaAI.fortSanctuary")) 
		{
            DeleteAttribute(rOurCharacter, "SeaAI.fortSanctuary");
            rOurCharacter.SeaAI.hitInSanctuary = true;
        }
    }
}

float Ship_GetTotalFireTime(ref rCharacter)
{
	int iRepairSkill = MakeInt(stf(rCharacter.TmpSkill.Repair) * 10.0); 
	return MakeFloat(5 + 3 * (10 - iRepairSkill));
}

void Ship_FireDamage()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();

	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	//ref rBallCharacter = GetCharacter(iBallCharacterIndex);
	
	int iSClass = GetCharacterShipClass(rOurCharacter);

	float fHP = (8 - iSClass) * (0.5 + frnd() * 0.5);

	int iTime = 1000 + rand(500);

	// if abordage or interface launched
	if (!bAbordageStarted && !sti(InterfaceStates.Launched)) 
	{ 
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 

		fTotalFireTime = fTotalFireTime - MakeFloat(iTime) / 250.0;
	}

	if (fTotalFireTime > 0.0)
	{
		PostEvent(SHIP_FIRE_DAMAGE, iTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}
}

void Ship_Serious_Boom(float x, float y, float z)
{
	CreateBlast(x,y,z);
	CreateParticleSystem("ShipExplode", x, y, z, 0.0, 0.0, 0.0, 0);
	Play3DSound("ship_explosion", x, y, z);
}

void Ship_SetFantomData(ref rFantom)
{
	ref		rBaseShip;

	rBaseShip = GetRealShip(sti(rFantom.Ship.Type));

	int iOptCrew = sti(rBaseShip.OptCrew);

	int iBaseHP = sti(rBaseShip.HP);
	int iCapacity = sti(rBaseShip.Capacity);
	
	rFantom.ship.Crew.Quantity = iOptCrew - rand(makeint(iOptCrew / 3)) + makeint(iOptCrew / 5); //��� ������� +-20 ���������
	
	rFantom.Ship.HP = iBaseHP;
	if (rand(3) == 2) 
	{ 
		rFantom.Ship.HP = iBaseHP - rand(makeint(iBaseHP / 8));
	}
	if (CheckAttribute(rFantom, "Ship.Masts")) { DeleteAttribute(rFantom, "Ship.Masts"); }
	if (CheckAttribute(rFantom, "Ship.Blots")) { DeleteAttribute(rFantom, "Ship.Blots"); }
	if (CheckAttribute(rFantom, "Ship.Sails")) { DeleteAttribute(rFantom, "Ship.Sails"); }

}

void CharacterUpdateShipFromBaseShip(int iCharacterIndex)
{
	ref rCharacter, rBaseShip;
	
	rCharacter = GetCharacter(iCharacterIndex);
	rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));

	if (!CheckAttribute(rCharacter,"Ship.Crew.Quantity")) 
	{ 
		rCharacter.ship.Crew.Quantity = rBaseShip.MaxCrew; 
	}

	if (!CheckAttribute(rCharacter,"Ship.HP")) 
	{ 
		rCharacter.Ship.HP = rBaseShip.HP; 
	}
	if (!CheckAttribute(rCharacter,"Ship.SP")) 
	{ 
		rCharacter.Ship.SP = rBaseShip.SP; 
	}

	if (!CheckAttribute(rCharacter,"Ship.Cannons.Charge.Type")) 
	{ 
		rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS; 
	}
	
	//Trace("Init cindex = " + iCharacterIndex + ", ship HP = " + rCharacter.Ship.HP + ", id = " + rCharacter.id + ", idx = " + rCharacter.index);
	if (!CheckAttribute(rCharacter,"Ship.Cannons.Type")) 
	{ 
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS12; 
	}

	rCharacter.Ship.Cannons.Borts = "";
}

float Ship_CalcGrapplingPerk(ref rCharacter)
{
	aref	arTmpPerks; 
	makearef(arTmpPerks, rCharacter.TmpPerks);

	float fGrapplingPerk = AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeGrappling, 1.0, 1.15); 
	return AIShip_isPerksUse(rCharacter.TmpPerks.GrapplingProfessional, fGrapplingPerk, 1.25);

	return fGrapplingPerk;
}

float Ship_CalcMaxAbordageDistance(float fGrappling, float fGrapplingPerk)
{
	return fGrapplingPerk * Bring2Range(15.0, 40.0, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageAngle(float fGrappling)
{
	return Bring2Range(0.70, 0.45, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageSpeed(float fGrappling)
{
	return Bring2Range(3.0, 5.0, 0.0, 1.0, fGrappling);
}

void Ship_CheckEnemiesAroundMainCharacter()
{
}

void Ship_CheckMainCharacter()
{
	aref	arUpdate;
	ref		rIsland;
	int		i, iRelation;
	float	x, z, fBestDistance, fDistance;
	float	fMinEnemyDistance = 1000000.0;
	float	fMinFortAbordDistance = 1000000.0; // ��� ������ ������� �� ��� �������� �����
	float	fortDistance = 1000000.0; //��� ���������� ��������� ������ �� ����� �������� � ������
	bool	bAbordageStartNow = false;
	int		iAbordageStartNowCharacter = -1;

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1000);

	ref rCharacter = pchar;

	// if abordage launched, return
	if (bAbordageStarted) { return; }

	// if interface launched, return
	if (sti(InterfaceStates.Launched)) { return; }

	// if main character is dead - skip
	if (LAi_IsDead(rCharacter)) { return; }

	iStormLockSeconds = iStormLockSeconds - 1;
	if (iStormLockSeconds < 0) { iStormLockSeconds = 0; }

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	bDisableSailTo = false;
	sIslandLocator = "";
	sIslandID = "";

	makearef(arUpdate, rCharacter.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return; }
	if (!CheckAttribute(arUpdate, "Forts")) { return; }
    // boal ����� � ���� ����!!! -->
    locTmpTime = locTmpTime + 0.5;  // ����� �������� �������� locDisableUpdateTime, ���� ����� ���������
    if (locTmpTime > 9)
	{
		    CalcLocalTime(2);
      		BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();
	}
	// boal ����� � ���� ����!!! <--
	
	x = stf(rCharacter.Ship.Pos.x);
	z = stf(rCharacter.Ship.Pos.z);

	float fOurHP = Ship_GetHP(rCharacter);
	float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
	float fOurGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fOurCrewFencing = (0.1 + fOurFencing * stf(rCharacter.Ship.Crew.Quantity));

	float fOurBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;

	bool bGrapplingProfessional = sti(rCharacter.TmpPerks.GrapplingProfessional);

	// max abordage parameters for our player
	float fOurGrapplingPerk = Ship_CalcGrapplingPerk(rCharacter);

	float fOurMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fOurGrappling, fOurGrapplingPerk);
	float fOurMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fOurGrappling); 
	float fOurMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fOurGrappling);

	string sPlayerLocation = rCharacter.location;
	string sPlayerLocator = rCharacter.location.locator;

	// find island
	int iIslandIndex = FindIsland(sPlayerLocation);
	if (iIslandIndex >= 0)
	{
		rIsland = GetIslandByIndex(iIslandIndex);
	}

	aref aShips, aForts;
	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	// check forts for abordage
	int iFortsNum = GetAttributesNum(aForts);
	fBestDistance = 10000000.0;
	for (i=0; i<iFortsNum; i++)
	{
		aref aFort = GetAttributeN(aForts, i);
		iRelation = sti(aFort.relation);

		ref rFortCharacter = GetCharacter(sti(aFort.idx)); 
		if (LAi_IsDead(rFortCharacter)) { continue; }
		int iFortMode = sti(rFortCharacter.Fort.Mode);
		aref aRLoc = FindIslandReloadLocator(sPlayerLocation, rFortCharacter.location.locator);
		if (!CheckAttribute(aRLoc, "Radius")) { continue; }  // fix
		float fRadius = stf(aRLoc.Radius);
		fDistance = stf(aFort.Distance);
		switch (iFortMode)
		{
			case FORT_NORMAL:
				if (iRelation == RELATION_ENEMY)
				{
					if (fMinEnemyDistance > fDistance) { fortDistance = fDistance; }
				}
				else
				{
					// ������������ ��������� �����
					// �������� �� ������ ���� -->
					if (!CheckAttribute(rFortCharacter, "CheckFlagYet"))
					{
                        if (!CheckAttribute(rFortCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rFortCharacter, "CheckFlagDate") > 1)
                        { // ������ ��� ������ ��� �� �������, �� ����� �� �����
							if (fDistance < (MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT * 1.5))
						    {
						        rFortCharacter.CheckFlagYet = true; // ���, ��������
						        Ship_CheckFlagEnemy(rFortCharacter);
						        SaveCurrentNpcQuestDateParam(rFortCharacter, "CheckFlagDate");
						    }
					    }
					}
					// �������� �� ������ ���� <--
				}
			break;
			case FORT_DEAD:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (fDistance > fRadius) { continue; }
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bCanEnterToLand = true;

					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = aRLoc.GoAfterBoard.location;
				}
			break;
			case FORT_ABORDAGE:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (iRelation == RELATION_ENEMY)
				{
					//if (fMinEnemyDistance > fDistance) { fMinEnemyDistance = fDistance; }
					if (fMinFortAbordDistance > fDistance) { fMinFortAbordDistance = fDistance; } //fix ����� � ����
				}
				if (fDistance > fRadius) { continue; }
				if (!Character_IsAbordageEnable(rFortCharacter) || bDisableMapEnter)  { continue; } // bDisableMapEnter - ������ ����� �����, ����� ����� ���� ��� ������� �������� boal
				
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bAbordageFortCanBe = true;
					sAbordageLocator = rFortCharacter.location.locator;
					iAbordageFortEnemyCharacter = sti(rFortCharacter.index);
				}
			break;
		}
	}

	// check ships for abordage
	int iShipsNum = GetAttributesNum(aShips);
	fBestDistance = 10000000.0;
	for (i=0; i<iShipsNum; i++)
	{
		aref aShip = GetAttributeN(aShips, i);

		ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
		fDistance = stf(aShip.Distance);		// distance between player ship and this ship
		iRelation = sti(aShip.relation);
		
		if (LAi_IsDead(rShipCharacter)) 
		{ 
			continue; 
		}
		if (iRelation != RELATION_ENEMY) 
		{ 
			continue; 
		}
		if (fMinEnemyDistance > fDistance) 
		{ 
			fMinEnemyDistance = fDistance; 
		}

		if (!Character_IsAbordageEnable(rShipCharacter)) 
		{ 
			continue; 
		}

		float fAng = stf(aShip.d_ay);						// it's dot.ay between ships
		float fRelativeSpeed = stf(aShip.RelativeSpeed);	// it's relative speed about player ship
		float fEnemyBoxSizeX = stf(rShipCharacter.Ship.BoxSize.x) / 2.0;

		bool bOurAngleTest = abs(fAng) > fOurMaxAbordageAngle && fRelativeSpeed < fOurMaxAbordageSpeed;
		float fAbordageDistance = fDistance - fEnemyBoxSizeX - fOurBoxSizeX;

		// test our ship with enemy
		if (bGrapplingProfessional || bOurAngleTest)
		{
			if (fAbordageDistance < fOurMaxAbordageDistance && fBestDistance > fDistance)
			{
				// abordage enable
				fBestDistance = fDistance;
				bAbordageShipCanBe = true;
				iAbordageShipEnemyCharacter = sti(rShipCharacter.index);
			}
		}

		// test enemy ship with our
		float fEnemyGrappling = stf(rShipCharacter.TmpSkill.Grappling);

		// max abordage parameters for our player
		float fEnemyGrapplingPerk = Ship_CalcGrapplingPerk(rShipCharacter);

		float fEnemyMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fEnemyGrappling, fEnemyGrapplingPerk);
		float fEnemyMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fEnemyGrappling); 
		float fEnemyMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fEnemyGrappling);

		bool bEnemyAngleTest = abs(fAng) > fEnemyMaxAbordageAngle && fRelativeSpeed < fEnemyMaxAbordageSpeed;
		if (bEnemyAngleTest)
		{
			if (fAbordageDistance < fEnemyMaxAbordageDistance)
			{
				// maybe other character want abordage us?
				float fEnemyFencing = stf(rCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyFencing * stf(rShipCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rShipCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (fRatio > 1.2)
				{
					iAbordageStartNowCharacter = sti(rShipCharacter.index);
					bAbordageStartNow = true;
					break;
				}
			}
		}
	}

	// check reload to locations possibility
	if (iIslandIndex >= 0 && fMinEnemyDistance > MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
	{
		if (Island_isReloadEnableGlobal(sPlayerLocation))
		{
			aref arReload;
			makearef(arReload, rIsland.Reload);

			int iNumLocators = GetAttributesNum(arReload);
			for (int j=0; j<iNumLocators; j++)
			{
				aref arLocator;
				arLocator = GetAttributeN(arReload, j);
				string sLocatorName = GetAttributeName(arLocator);
				if (Island_isReloadFort(sPlayerLocation, arLocator.name)) { continue; }
				if (!Island_isReloadEnableLocal(sPlayerLocation, arLocator.name)) { continue; }
				if(!CheckAttribute(rIsland, "reload." + sLocatorName + ".x") || !CheckAttribute(rIsland, "reload." + sLocatorName + ".z"))
				{
					continue;
				}

				float x1 = stf(rIsland.reload.(sLocatorName).x);
				float z1 = stf(rIsland.reload.(sLocatorName).z);
				/*if (checkAttribute(rIsland, "reload."+sLocatorName+".wdmisland"))
				{
					wdmCurrentIsland = rIsland.reload.(sLocatorName).wdmisland;
				}*/
				float r = stf(rIsland.reload.(sLocatorName).radius);
				//#20180524-01 Remove unneeded sqrt
				r *= r;
				//if (sqrt(sqr(x1 - x) + sqr(z1 - z)) < r)
				if ((sqr(x1 - x) + sqr(z1 - z)) < r)
				{
					bCanEnterToLand = true;
					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = rIsland.reload.(sLocatorName).name;
					
					// LDH 24Jan17 - display mooring location name -->
                    int nFile = LanguageOpenFile("LocLables.txt");
					string MoorName = LanguageConvertString(nFile, rIsland.reload.(sLocatorName).label);
                    LanguageCloseFile(nFile);
					if (!CheckAttribute(pchar, "MoorName")) pchar.MoorName = " ";
					if (MoorName != pchar.MoorName)
                    {
						// LDH 14Feb17 rewrite
						// LDH 26Jan17 - play anchor sound if moor location changes due to overlapping locations
						if (pchar.MoorName != " " && MoorName != " ")
						{
							boal_soundOn = false;		// make sure it's only played once
							PlaySound("interface\_Yakordrop.wav");
						}
						pchar.MoorName = MoorName;
                    }
					// LDH 24Jan17 <--
					
					break;
				}
			}
			// LDH 12Feb17 display moor name in battle interface -->
			// If we don't do this, location does not update
			BattleInterface.textinfo.Location.text = GetBILocationName();
			// RefreshBattleInterface();
			// LDH 12Feb17 <--
		}
	}
	else
	{
		// LDH 13Feb17 display region name in battle interface -->
		pchar.Moorname = " ";
		// If we don't do this, location does not update
		BattleInterface.textinfo.Location.text = GetBILocationName();
		// RefreshBattleInterface();
		// LDH 13Feb17 <--
	}

	// disable any abordage if storm
	if (Whr_IsStorm())
	{
		bAbordageStartNow = false;
		bAbordageFortCanBe = false;
		bAbordageShipCanBe = false;
	}

	// Enter 2 map enable/disable
	// Peoples on ship mode update
	int iPrevShipPOSMode = sti(rCharacter.Ship.POS.Mode);
	rCharacter.Ship.POS.Mode = SHIP_SAIL;

	bDisableMapEnter = false;
	if (fMinEnemyDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;

		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
	if (fortDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;
		//#20190205-02
		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
    // boal fix ����� � ���� -->
    if (fMinFortAbordDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
    {
        bCanEnterToLand = false;
    }
    // boal <--
	if (iStormLockSeconds)
	{
		bDisableMapEnter = true;
		bCanEnterToLand = false;
		bDisableSailTo = true;

		rCharacter.Ship.POS.Mode = SHIP_STORM;
	}

	// new music
	bool bMakeCurrentUpdate = bUpdatePosMode;
	if( iVicSoundTime<=0 && sti(rCharacter.Ship.POS.Mode) != iPrevShipPOSMode ) {
		bMakeCurrentUpdate = true;
	}
	if( bMakeCurrentUpdate )
	{
		switch (sti(rCharacter.Ship.POS.Mode))
		{
			case SHIP_SAIL:
				if (!Whr_IsStorm()) 
				{ 
					seaAlarmed = false;
					if (iPrevShipPOSMode == SHIP_WAR)
					{
                   		Ship_PlayVictory("music_ship_victory", 12000);
					} // fix boal
					else
					{
						FadeOutMusic(3); //fix
						if(Whr_IsDay()) SetMusic("music_sea_day");
						else SetMusic("music_sea_night");
					}
				}
				else
				{ 
					FadeOutMusic(3); //fix
					PlayStereoOGG("music_End_storm"); 
				}
			break;
			case SHIP_WAR:
				FadeOutMusic(3); // fix
				seaAlarmed = true;
				SetMusic("music_sea_battle");
			break;
		}

		bUpdatePosMode = false;
	}

	// if quest disable enter 2 map
	if (bQuestDisableMapEnter) { bDisableMapEnter = true; }

	// Start abordage automatically
	if (bAbordageStartNow) 
	{ 
		ref rTargetCharacter = GetCharacter(iAbordageStartNowCharacter);
		if(GetRelation(sti(rCharacter.index), iAbordageStartNowCharacter) == RELATION_ENEMY)
		{
			if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
			{
				iAbordageShipEnemyCharacter = iAbordageStartNowCharacter;
				Sea_AbordageLoad(SHIP_ABORDAGE, false); 
			}
		}
	}
}

void Ship_OnStrandNext()
{
	ref	rCharacter = GetCharacter(GetEventData());
	if (LAi_IsDead(rCharacter)) { return; }

	bool bOnStrand = sti(rCharacter.Ship.Strand);
	if (!bOnStrand) 
	{ 
		int iSoundID = sti(rCharacter.Ship.Strand.SndID);
		if (iSoundID != 0) { StopSound(sti(rCharacter.Ship.Strand.SndID), 3000); }
		rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
		return; 
	}
	if (!CheckAttribute(rCharacter, "AlwaysSandbankManeuver"))  //boal
	{
		float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
		float fHP = 4.0 * fCurrentSpeedZ / 7.0;
		Ship_ApplyHullHitpoints(rCharacter, fHP, KILL_BY_ISLAND, -1);
	}
	PostEvent(SHIP_TO_STRAND_NEXT, 100 + rand(100), "l", sti(rCharacter.index));
}

void Ship_OnStrand()
{
	ref rCharacter = GetCharacter(GetEventData());
	bool bNewStrand = GetEventData();
	
	bool bPrevStrand = sti(rCharacter.Ship.Strand);

	rCharacter.Ship.Strand = bNewStrand;

	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	if (bPrevStrand == 0 && bNewStrand == 1)
	{
		PostEvent(SHIP_TO_STRAND_NEXT, 100, "l", sti(rCharacter.index));
		rCharacter.Ship.Strand.SndID = Play3DSoundComplex("ship_aground", x, y, z, true, false);
	}
}

// Small boom
void Ship_DetonateSmall()
{
	ref		rCharacter = GetCharacter(GetEventData());
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);

    if (bAbordageStarted) { return; }
	if (sti(InterfaceStates.Launched)) { return; }
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);
	
	if (y > -3.0)
	{
		int iSClass = GetCharacterShipClass(rCharacter);
		PostEvent(SHIP_DETONATE_SMALL, 200 + iSClass * 300 + rand(900), "l", sti(rCharacter.index));
	}

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	//for (int i=0; i < 1 + rand(1); i++)
	//{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);

		y1 = 1.0 + y + frnd() * 3.0;
		Ship_Serious_Boom(x1 + x, y1, z1 + z);
		CreateParticleSystem("blast", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	//}
}

void Ship_Turn180(ref rCharacter)
{
	//rCharacter.TmpPerks.Turn = true;
	//rCharacter.TmpPerks.Turn.Angle = PI;
	rCharacter.Tmp.SpeedRecall = 0; // ���� ������������ ������
}

// Big Boom on ship
void Ship_Detonate(ref rCharacter, bool bMakeSmallBoom, bool bMakeDead)
{
	if (!CheckAttribute(rCharacter, "Ship.Pos.x")) 
	{
		Trace("Ship_Detonate: Can't find Ship.Pos in character with id: " + rCharacter.id);
		return;
	}
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);

	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);

	int iMinBoom = MakeInt(Bring2Range(6.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	bool isBoomAlready = false;
	int iMax = iMinBoom + rand(2); //fix
	for (int i=0; i<iMax; i++)
	{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);
		
		y1 = 1.0 + y + frnd() * 3.0;
		if(isBoomAlready == false)
		{
			Ship_Serious_Boom(x1 + x, y1, z1 + z);
		}
		isBoomAlready = true;
		CreateParticleSystem("blast_inv", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	}
	if (bMakeDead) { ShipDead(sti(rCharacter.Index), KILL_BY_SPY, -1); }

	if (bMakeSmallBoom) { PostEvent(SHIP_DETONATE_SMALL, 600 + rand(1000), "l", sti(rCharacter.index)); } 
}

float AIShip_isPerksUse(string sPerk, float fOff, float fOn)
{
	if (sti(sPerk)) { return fOn; }
	return fOff;
}

// EVENT, calculate dynamic parameters for ship, one per second
void Ship_UpdateParameters()
{
	int		iCharacterIndex = GetEventData();
	ref		rCharacter = GetCharacter(iCharacterIndex);
	float	fSailState = GetEventData();
	
	bool	bDead = LAi_IsDead(rCharacter);
	//Log_Testinfo("Ship_UpdateParameters " + rCharacter.id);
	
	if(sti(rCharacter.ship.type) == SHIP_NOTUSED || bDead)   // super fix boal
	{
		return;
	}
    // �������� bool	bStrand = sti(rCharacter.Ship.Strand);
	aref	arTmpPerks; 
	makearef(arTmpPerks, rCharacter.TmpPerks);

	// update temporary skill storage
	Ship_UpdateTmpSkills(rCharacter);

	Cannon_RecalculateParameters(sti(rCharacter.index));

	// some of ship parameters
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	ref		rShip = GetRealShip(sti(arCharShip.Type));

    float fShipSpeed, fShipTurnRate;
    
	// boal ��� ����������� -->
	if (!CheckAttribute(rCharacter, "Tmp.SpeedRecall") || sti(rCharacter.Tmp.SpeedRecall) <= 0)
	{
		fShipSpeed    = FindShipSpeed(rCharacter);
		fShipTurnRate = FindShipTurnRate(rCharacter);
		
		rCharacter.Tmp.SpeedRecall   = 8 + rand(5);
		rCharacter.Tmp.fShipSpeed    = fShipSpeed;
		rCharacter.Tmp.fShipTurnRate = fShipTurnRate;
	}
	else
	{
		fShipSpeed    = stf(rCharacter.Tmp.fShipSpeed);
		fShipTurnRate = stf(rCharacter.Tmp.fShipTurnRate);
		
		rCharacter.Tmp.SpeedRecall   = sti(rCharacter.Tmp.SpeedRecall) - 1;
	}
    // boal ��� ����������� <--
    
	// wind power
	float	fWindPower = Whr_GetWindSpeed() / WIND_NORMAL_POWER;	
	float	fWindDotShip = GetDotProduct(Whr_GetWindAngle(), stf(arCharShip.Ang.y));		// Wind.ay | Ship.ay
    // boal -->
	fShipSpeed = (fShipSpeed * fWindPower);  // boal ����������� �������� �� ���������� ��� ������ �����.
	arCharShip.MaxSpeedZ = fShipSpeed; 
	//Log_info("1 = " + arCharShip.MaxSpeedZ);
	arCharShip.MaxSpeedZ = Sea_ApplyMaxSpeedZ(arCharShip, fWindDotShip); // ���� ������� � �� �����
	//Log_info("2 = " + arCharShip.MaxSpeedZ);
	// boal <--
	//  �������� ���� � ���������� float fShipTurnRate = FindShipTurnRate(rCharacter);
	
	float fMaxSpeedY = stf(rShip.TurnRate) / Sea_TurnRateMagicNumber(); //boal

	float fTRFromSailState = 1.0;
	switch (MakeInt(fSailState * 2.0))
	{
		case 0: fTRFromSailState = 0.05; break;
		case 1: fTRFromSailState = 1.0; break;
		case 2: fTRFromSailState = 0.68; break;
	}
	// boal ����������� �� �������� �� ������ -->
    float	fTRFromSpeed = 1.0;
    float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
	if (iCharacterIndex == GetMainCharacterIndex())
	{
        if (MOD_SKILL_ENEMY_RATE > 2) // ������ � ���� - �����������)
        {
            if (iArcadeSails == 1)
        	{
               fTRFromSpeed = 1.0 - 0.5 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
    		else
    		{
    		    fTRFromSpeed = 1.0 - 0.86 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
    		}
        }
	}
	else
	{
		if (iArcadeSails == 1)
    	{
           fTRFromSpeed = 1.0 - (0.51 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
		else
		{
		    fTRFromSpeed = 1.0 - (0.87 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
		}
	}
	// boal ����������� �� �������� �� ������ <--
	float fTRResult = fMaxSpeedY * fShipTurnRate * fTRFromSailState * fTRFromSpeed;
	// ===============
	// boal ����� � ��� ����������, �� ������ �������� ���� �� ��������, �� � ������ ����������� ��� ��� �������.
	// VANO :: update fTRResult using rotate with wind direction
	//float fRotateSide = stf(arCharShip.speed.y);
	/*float fPrevWindDotShip = stf(arCharShip.WindDotShip);
	bool bShipTurnToWind = fWindDotShip >= fPrevWindDotShip;
	float fWindTurnMultiply = 1.0;
	if (bShipTurnToWind) 
		{ fWindTurnMultiply = Bring2Range(1.5, 1.0, 0.0, 1.0, abs(fWindDotShip)); }
	else 
		{ fWindTurnMultiply = Bring2Range(0.5, 1.0, 0.0, 1.0, abs(fWindDotShip)); }

	arCharShip.WindDotShip = fWindDotShip;
	//Trace("fWindTurnMultiply = " + fWindTurnMultiply);
	// ===============

	fTRResult = fWindTurnMultiply * Bring2Range(0.01, 1.0, 0.00001, 1.0, fTRResult);
	*/
	fTRResult = Bring2Range(0.07, 0.95, 0.00001, 1.0, fTRResult);
	arCharShip.MaxSpeedY =	fTRResult;

    // Apply arcade mode
	if (iArcadeSails == 1)
	{
		//arCharShip.MaxSpeedZ = 6.0 * stf(arCharShip.MaxSpeedZ);
		arCharShip.MaxSpeedZ = (2.5 * stf(arCharShip.MaxSpeedZ));
		arCharShip.MaxSpeedY = (2.0 * stf(arCharShip.MaxSpeedY));
	}
	else
	{
		//arCharShip.MaxSpeedY = 0.75 * stf(arCharShip.MaxSpeedY);
		arCharShip.MaxSpeedZ = (1.0 * stf(arCharShip.MaxSpeedZ));
	}
	//Log_Info("MaxSpeedY = "  + arCharShip.MaxSpeedY);
	// calculate immersion
	float fLoad = Clampf(GetCargoLoad(rCharacter) / stf(rShip.Capacity));
	arCharShip.Immersion = (stf(rShip.SubSeaDependWeight) * fLoad); // ��� ������� ���������� �� ����

	// do damage if ship hull < 10 ���������, sinking
	float fBaseSailHP = stf(rShip.SP);
	float fBaseShipHP = stf(rShip.HP);
	float fCurHP = stf(arCharShip.HP);
	if(fBaseShipHP < fCurHP)
	{
		fBaseShipHP = fCurHP;
	}
	if (bSeaActive && (fCurHP / fBaseShipHP < 0.09999))
	{
        float fLightRepair = AIShip_isPerksUse(arTmpPerks.LightRepair, 1.0, 0.0);
        // ��� ���� ������� �� �������� ���� �������
        if (CheckAttribute(rCharacter, "SinkTenPercent") && !sti(rCharacter.SinkTenPercent)) { fLightRepair = 0.0; }
		float fSinkDamage = fLightRepair * (fBaseShipHP / 100.0) * 0.08;
		if (CheckAttribute(rCharacter, "Ship.LastBallCharacter")) 
		{ 
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_BALL, sti(rCharacter.Ship.LastBallCharacter));
		}
		else
		{
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_TOUCH, -1);
		}
		/*if(!CheckAttribute(rCharacter, "ship.flow")) // to_do
		{
			rCharacter.ship.flow = 0;
		}
		rCharacter.ship.flow = sti(rCharacter.ship.flow) + 1;
		*/
		if (iCharacterIndex == nMainCharacterIndex) 
		{ 
            // boal -->
			if(!IsPerkIntoList("sink"))
� � � � 	{
				if (rand(1) == 0)
				{
					PlayVoice("Interface\_Abandon1.wav");
				}
				else
				{
					PlayVoice("interface\_Abandon"+(2+rand(1))+".wav");
				}
			}
			// boal <--
			AddPerkToActiveList("sink"); 
		}
	}
	else
	{
		if (iCharacterIndex == nMainCharacterIndex) { DelPerkFromActiveList("sink"); }
	}

	float fStormProfessional = AIShip_isPerksUse(arTmpPerks.StormProfessional, 1.0, 0.7);

    // boal fix defence ship in storm 11.05.05 -->
    if (CheckAttribute(rCharacter, "DontHitInStorm"))
    {
		fStormProfessional = 0;
	}
	// boal fix defence ship in storm 11.05.05 <--
	// do damage if storm or tornado
	if (bStorm && bSeaActive)
	{
		float fWindAttack = 1.0 - abs(fWindDotShip);
		
		float fDamageMultiply = fStormProfessional * Bring2Range(0.25, 1.0, 0.0, 1.0, fWindAttack) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);

		// hull damage
		float fDamageHP = (fBaseShipHP / 100.0) * 1.1;
		Ship_ApplyHullHitpoints(rCharacter, fDamageMultiply * fDamageHP, KILL_BY_TOUCH, -1);

		// sails damage
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.15); break;
			case 1: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 0.55); break;
			case 2: MakeSailDmg(iCharacterIndex, fDamageMultiply * (fBaseSailHP / 100.0) * 1.1); break;
		}

		// experience
		float fExp = (1.0 - fWindAttack) * fDamageHP / (8 - GetCharacterShipClass(rCharacter)); // fDamageHP - ��� ������� �������, ��� �������� ������� �����
		fExp = fExp / 10;
  		if (!bDead)
        {
            Ship_AddCharacterExp(rCharacter, MakeInt(fExp));
			// boal -->
            if (IsCompanion(rCharacter))
            {
               AddCharacterExpToSkill(rCharacter, "Sailing", fExp);
               ChangeCrewExp(rCharacter, "Sailors", AIShip_isPerksUse(CheckCharacterPerk(rCharacter, "SeaWolf"), 0.5, 1.0));
            }
            // boal <--
        }

		// rotate impulse
  		float fRotate = stf(rCharacter.Ship.Tornado.Rotate.y) + (frnd() * 0.08 - 0.04);  //fix boal
		if (fRotate > 0.01)
		{
			fRotate = 0.01;
		}
		if (fRotate < -0.01)
		{
			fRotate = -0.01;
		}

		rCharacter.Ship.Tornado.Rotate.y = fRotate;  //fix boal
		arCharShip.Impulse.Rotate.y = fRotate;
	}

	if (bTornado && bSeaActive)
	{
		float fTornadoDistance = GetDistance2D(stf(Tornado.x), stf(Tornado.z), stf(arCharShip.Pos.x), stf(arCharShip.Pos.z));
		float fTornadoDamageMultiply = fStormProfessional * Bring2Range(1.0, 0.0, 0.0, 100.0, fTornadoDistance);

		// hull damage
		Ship_ApplyHullHitpoints(rCharacter, fTornadoDamageMultiply * (fBaseShipHP / 100.0) * 8.5, KILL_BY_TOUCH, -1);

		// sails damage
		switch (MakeInt(fSailState * 2.0))
		{
			case 0: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 1.5);
			break;
			case 1: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 4.5); 
			break;
			case 2: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 8.5); 
			break;
		}
	}
	
	// Expirience log section
	if (iCharacterIndex == nMainCharacterIndex && bSeaActive)
	{
		fSeaExpTimer = fSeaExpTimer + 1.0;
		if (fSeaExpTimer >= 15.0 && bStorm)
		{
			if (!bDead)
			{ 
				//Ship_PrintExp(MakeInt(fSeaExp));
			}

			fSeaExpTimer = 0.0;
			fSeaExp = 0.0;
		}
	}

	// Recalculate Cargo Load if need
	if (CheckAttribute(rCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(rCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		if (rand(5) == 1)  // �����������, ������� �������
		{
			RecalculateCargoLoad(rCharacter);
			rCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
	}
    //  to_do �� ���� � ��� -->
	if (bSeaLoaded && CheckAttribute(rCharacter, "SeaAI.Task.Target"))
	{
		if(sti(rCharacter.SeaAI.Task.Target) > 0)
		{
			ref rTargetCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
			bool bSkipTarget = false;
			if(!CheckAttribute(rTargetCharacter, "location"))
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location == "none")
			{
				bSkipTarget = true;
			}
			if(rTargetCharacter.location != rCharacter.location)
			{
				bSkipTarget = true;
			}
			if (!bSkipTarget)
			{
				float fDistance = Ship_GetDistance2D(rCharacter, rTargetCharacter);
				float fEnemyLeadership = stf(rTargetCharacter.TmpSkill.Leadership); 
				float fEnemyFencing = stf(rTargetCharacter.TmpSkill.Fencing); 
				float fEnemyCrewFencing = (0.1 + fEnemyLeadership + fEnemyFencing * stf(rCharacter.Ship.Crew.Quantity));
				float fOurLeadership = stf(rCharacter.TmpSkill.Leadership); 
				float fOurFencing = stf(rCharacter.TmpSkill.Fencing);
				float fOurCrewFencing = (0.1 + fOurLeadership + fOurFencing * stf(rTargetCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				if (sti(rCharacter.rank) > sti(rTargetCharacter.rank)) 
				{ 
					fRatio = fRatio * 1.2; 
				}
				
				if (fRatio > 1.2 && CheckAttribute(rCharacter, "Tmp.fShipSpeed") && CheckAttribute(rTargetCharacter, "Tmp.fShipSpeed") && stf(rCharacter.Tmp.fShipSpeed) > (stf(rTargetCharacter.Tmp.fShipSpeed) / 1.5))
				{
					//ref rTargetCharacter = GetCharacter(sti(rCharacter.SeaAI.Task.Target));
					if(GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
					{
						Ship_SetTaskAbordage(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index)); // fix PRIMARY_TASK
						rCharacter.Ship_SetTaskAbordage = true; // ��������, ���� �� �������
					}
				}
				else
				{
					DeleteAttribute(rCharacter, "Ship_SetTaskAbordage");
				}

				if (sti(rCharacter.SeaAI.Task) == AITASK_RUNAWAY)
				{
					/*Ship_SetSailState(sti(rCharacter.index), 1);

					//��������� ��������� � ��������� �������� ������ ����������
					//��������� ���� �������� � �������� ����������
					//������ ��� �� ��������
					//��������� ������ �������
					//���� �������� 2 ��� ������ ����� - ���������� ���� �� ����.
					//��������� ������.
					Ship_SetLightsOff(rCharacter, 15.0, true, true, false);

					ref rCannon = GetCannonByType(sti(rTargetCharacter.Ship.Cannons.Type));
					float TargetRange = stf(rCannon.FireRange);
					int isDropGoods = 0;

					if(fDistance <= TargetRange)
					{
						isDropGoods = isDropGoods + 1;
					}
					
					float fOurSpeed = FindShipSpeed(rCharacter);
					float fEnemySpeed = FindShipSpeed(rTargetCharacter);

					if(fOurSpeed <= fEnemySpeed)
					{
						isDropGoods = isDropGoods + 1;
					}

					if(fOurLeadership < rand(12))
					{
						isDropGoods = isDropGoods + 1;
					}

					float fOurMorale = GetCharacterCrewMorale(rCharacter);
					if(fOurMorale < rand(99))
					{
						isDropGoods = isDropGoods + 1;
					}

					if(isDropGoods > 2)
					*/
					// �������� �����������, ���� ���-�� ������� -->
					Ship_SetSailState(sti(rCharacter.index), 1);  // to_do ����� ���������, ����� �������� ������ ���� ��� � ���� ����� ������
					if (sti(rCharacter.Ship.Lights) == 1)
					{
						Ship_SetLightsOff(rCharacter, 15.0, true, true, false);
					}
					if (sti(rCharacter.Ship.SP) > 50 && rand(100) > 80)  // �� ����������, ���� �� �������, � �� ��� ������ ����� ����
					{
						PostEvent(SHIP_DROP_GOOD, 1000, "a", rCharacter);
					}
					// ����� ���� 09.07.07 boal -->
					if (sti(rCharacter.Ship.SP) < 60 && GetCargoGoods(rCharacter, GOOD_POWDER) >= MINE_POWDER*2 && rand(39) == 5)
					{
						SetMineFree(rCharacter, 1); 
					}
					// ����� ���� <--
					// �������� �����������, ���� ���-�� ������� <--
				}
		        else
		        {
					if (sti(rCharacter.SeaAI.Task) == AITASK_ABORDAGE)
					{
						if (GetRelation(sti(rCharacter.index), sti(rTargetCharacter.index)) == RELATION_ENEMY)
						{
							if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
							{
								if (sti(rTargetCharacter.index) == nMainCharacterIndex)
								{
									float fCharacterGrappling = stf(rCharacter.TmpSkill.Grappling);
									float fCharacterGrapplingPerk  = Ship_CalcGrapplingPerk(rCharacter);
									float fCharacterDistance = Ship_CalcMaxAbordageDistance(fCharacterGrappling, fCharacterGrapplingPerk);
									float fCharacterAngle = Ship_CalcMaxAbordageAngle(fCharacterGrappling);
									float fCharacterSpeed = Ship_CalcMaxAbordageSpeed(fCharacterGrappling);
		
									float fAng = 0.0;
									float fRelativeSpeed = stf(arCharShip.Speed.z);
		
									aref	arUpdate;
									makearef(arUpdate, rCharacter.SeaAI.Update);
									aref aShips;
									makearef(aShips, arUpdate.Ships);
									int iShipsNum = GetAttributesNum(aShips);
									for (int i=0; i<iShipsNum; i++)
									{
										aref aShip = GetAttributeN(aShips, i);
										ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
										if(rShipCharacter.id == rTargetCharacter.id)
										{
											fRelativeSpeed = stf(aShip.RelativeSpeed);
											fAng = stf(aShip.d_ay);
											break;
										}
									}
									float fEnemyBoxSizeX = stf(rTargetCharacter.Ship.BoxSize.x) / 2.0;
									float fCharacterBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;
									float fAbordageDistance = fDistance - fEnemyBoxSizeX - fCharacterBoxSizeX;
							
									if (fAbordageDistance < fCharacterDistance && fAng < fCharacterAngle && fRelativeSpeed < fCharacterSpeed)
									{
										/*if (sti(rTargetCharacter.index) != nMainCharacterIndex)
										{
											CalculateAbordage(rCharacter);
										}
										else  */ // ��� �3 ����� �����, �� ����� ������ ������� ����� �����
										//if (sti(rTargetCharacter.index) == nMainCharacterIndex)
										//{
										if (fRatio > 1.2)
										{
											iAbordageShipEnemyCharacter = sti(rCharacter.index);
											Sea_AbordageLoad(SHIP_ABORDAGE, false);
										}
										else
										{
											if (stf(rCharacter.ship.hp) > (stf(rTargetCharacter.ship.hp) / 4) || GetCrewQuantity(rCharacter) > GetCrewQuantity(rTargetCharacter)) //boal fix
											{
												Ship_SetTaskAttack(SECONDARY_TASK, sti(rCharacter.index), sti(rTargetCharacter.index));   //fix
											}
											else
											{
												Ship_SetTaskRunaway(SECONDARY_TASK,sti(rCharacter.index), sti(rCharacter.SeaAI.Task.Target));  //fix
											}
										}
										//}
									}
								} // if ��
							}
						}
					}
				} // else
			}
		}
	}
	//  to_do <--
	// start random sounds :: SAILS
	if (rand(40) <= fSailState * 5.0) { Ship_PlaySound3DComplex(rCharacter, "sails_ambient", fSailState * 0.5, 0.0, 0.0, 0.5 + frnd() * 0.0); }

	// start random sounds :: SHIPS
	if (rand(2) == 1) { Ship_PlaySound3DComplex(rCharacter, "squeak_sea"+sSeaSoundPostfix, 0.9, frnd() * 1.2 - 0.6, 0.0, frnd() * 1.6 - 0.8); }
}

void Ship_SailsMoveSound()
{
	aref arCharacter = GetEventData();
	bool bMove = GetEventData();

	//#20171230-02 Misc fixes
    if(!CheckAttribute(arCharacter, "Ship.Sounds.SailsID"))
        return;
	// update sounds :: SAILS - moving
	if (CheckAttribute(arCharacter, "Ship.Sounds") && sti(arCharacter.Ship.Sounds.SailsID) > 0) 
		{ Sound_SetVolume(sti(arCharacter.Ship.Sounds.SailsID), 0.75 * bMove); }
}

void Ship_PrintExp(int iExp)
{
	if (iExp <= 0) { return; }

	object oRes;
	string sExpQuantity = iExp;
	string sExpString = LanguageConvertString(iSeaSectionLang, "sea_exp_add");

	Event(PARSE_STRING, "asls", &oRes, sExpString, 1, sExpQuantity);

	Log_SetStringToLog(oRes.Str);
}

void Ship_TornadoDamage()
{
	float fTime = GetEventData();
	
	Tornado.x = GetEventData();
	Tornado.z = GetEventData();
}

void Ship_UpdateTmpSkills(ref rCharacter)
{
	///// � ������������
	if (!CheckAttribute(rCharacter, "TmpSkillRecall") || sti(rCharacter.TmpSkillRecall) <= 0)
    {
        rCharacter.TmpSkill = "";

    	aref aTmpSkill; makearef(aTmpSkill, rCharacter.TmpSkill);

    	// calc skills for speed optimization
    	//aTmpSkill.Commerce = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_COMMERCE)) / SKILL_MAX;
    	aTmpSkill.Leadership = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_LEADERSHIP)) / SKILL_MAX;
    	aTmpSkill.Sneak     = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SNEAK)) / SKILL_MAX;
    	aTmpSkill.Defence   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_DEFENCE)) / SKILL_MAX;
    	aTmpSkill.Grappling = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_GRAPPLING)) / SKILL_MAX;
    	aTmpSkill.Sailing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SAILING)) / SKILL_MAX;
    	aTmpSkill.Repair    = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_REPAIR)) / SKILL_MAX;
    	aTmpSkill.Fencing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_FENCING)) / SKILL_MAX;
    	aTmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
    	aTmpSkill.Cannons   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_CANNONS)) / SKILL_MAX;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
        {
            if (SeaCameras.Camera == "SeaDeckCamera")
        	{
        		aTmpSkill.Accuracy = Clampf(stf(aTmpSkill.Accuracy) + 0.15); // ���� 0.4
        	}
        	//rCharacter.SystemInfo.GlobalMinEnemyDistance = stf(rCharacter.SystemInfo.LastMainMinEnemyDistance); // fix ������ �� �����
        	if (rand(10) == 3)//boal fix ���������, ����� ����������� ��� ������������
        	{
        	    DoQuestCheckDelay("NationUpdate", 1.0);
        	}
    	}
    	rCharacter.TmpSkillRecall = 25 + rand(49); // ������ ����� - ����������� ��������, � �� ��� ������ ��� ����� //"60"; // ������� ��� � ������
    	// ������ ������
		if (GetNpcQuestPastTimeParam(rCharacter, "Add2SeaTime") > 55) // 2 ��� ������ � �������� ���� �������, ��������� 0
		{
		    if (CheckAttribute(rCharacter, "SeaAI.Task") && rCharacter.SeaAI.Task != AITASK_RUNAWAY) // �� � �� ����, ��� ����� ����� ����� �� ��
	        {
	        	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(pchar.index));
	        }
		}
	}
	else
	{
        rCharacter.TmpSkillRecall = sti(rCharacter.TmpSkillRecall) - 1;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
    	{
            rCharacter.TmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
            if (SeaCameras.Camera == "SeaDeckCamera")
            {
                rCharacter.TmpSkill.Accuracy = Clampf(stf(rCharacter.TmpSkill.Accuracy) + 0.15);
            }
    	}
	}
}

void Ship_UpdatePerks()
{
	int iCharacterIndex = GetEventData();
	ref rCharacter = GetCharacter(iCharacterIndex);

	//Trace("Ship_UpdatePerks: rCharacter.id = " + rCharacter.id);
	if (sti(rCharacter.ship.type) == SHIP_NOTUSED) return; // fix ��� ����� �������
	rCharacter.TmpPerks = "";
	aref aTmpPerks; makearef(aTmpPerks, rCharacter.TmpPerks);

	// calc perks for speed optimization
	//if (!CheckAttribute(rCharacter, "TmpPerks.Turn")) {	rCharacter.TmpPerks.Turn = 0; }
      // to_do
	aTmpPerks.StormProfessional	  	    = CheckOfficersPerk(rCharacter, "StormProfessional");
    aTmpPerks.FastReload				= CheckOfficersPerk(rCharacter, "FastReload");
	aTmpPerks.ImmediateReload			= CheckOfficersPerk(rCharacter, "ImmediateReload");
	aTmpPerks.HullDamageUp			 	= CheckOfficersPerk(rCharacter, "HullDamageUp");
	aTmpPerks.CrewDamageUp				= CheckOfficersPerk(rCharacter, "CrewDamageUp");
	aTmpPerks.CriticalShoot				= CheckOfficersPerk(rCharacter, "CriticalShoot");
	aTmpPerks.LongRangeShoot			= CheckOfficersPerk(rCharacter, "LongRangeShoot");
	aTmpPerks.CannonProfessional		= CheckOfficersPerk(rCharacter, "CannonProfessional");
	aTmpPerks.LongRangeGrappling		= CheckOfficersPerk(rCharacter, "LongRangeGrappling");
	aTmpPerks.GrapplingProfessional		= CheckOfficersPerk(rCharacter, "GrapplingProfessional");
	aTmpPerks.BasicBattleState			= CheckOfficersPerk(rCharacter, "BasicBattleState");
	aTmpPerks.AdvancedBattleState		= CheckOfficersPerk(rCharacter, "AdvancedBattleState");
	aTmpPerks.ShipDefenseProfessional	= CheckOfficersPerk(rCharacter, "ShipDefenseProfessional");
	aTmpPerks.ShipSpeedUp				= CheckOfficersPerk(rCharacter, "ShipSpeedUp");
	aTmpPerks.ShipTurnRateUp			= CheckOfficersPerk(rCharacter, "ShipTurnRateUp");
	aTmpPerks.SandbankManeuver			= CheckOfficersPerk(rCharacter, "SandbankManeuver");
	aTmpPerks.SailingProfessional		= CheckOfficersPerk(rCharacter, "SailingProfessional");
	aTmpPerks.LightRepair				= CheckOfficersPerk(rCharacter, "LightRepair");
	// update main character if rCharacter is companion   - ��� ����, �� �����?? (boal)
	if (iCharacterIndex != nMainCharacterIndex && IsCompanion(rCharacter))
	{
		Event("eSwitchPerks", "l", nMainCharacterIndex);
	}
}

void Ship_Lightning()
{
	if (!bSeaActive) { return; }

	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	for (int i=0; i<iNumShips; i++)
	{
	    if(Ships[i] < 0) continue;
		ref rCharacter = GetCharacter(Ships[i]);
		aref arShipChar; makearef(arShipChar, rCharacter.Ship);

		float sx = stf(arShipChar.Pos.x);
		float sy = stf(arShipChar.Pos.y);
		float sz = stf(arShipChar.Pos.z);
		float bx = stf(arShipChar.BoxSize.x);
		float by = stf(arShipChar.BoxSize.y);
		float bz = stf(arShipChar.BoxSize.z);
		float fDist = GetDistance2D(x, z, sx, sz);
		float fMinLightningDist = 20.0 + bz / 1.5;
		if (fDist < fMinLightningDist)
		{
			int iMinBoom = MakeInt(Bring2Range(5.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));
			float fCos = cos(stf(arShipChar.Ang.y));
			float fSin = sin(stf(arShipChar.Ang.y));
			int iMax = iMinBoom + rand(2);
			for (int k=0; k<iMax; k++)
			{
				float dx = 0.6 * bx * (frnd() - 0.5);
				float dz = 0.7 * bz * (frnd() - 0.5);
				RotateAroundY(&dx, &dz, fCos, fSin);
				Ship_Serious_Boom(sx + dx, sy + 0.1 * by * frnd(), sz + dz);
			}

			Ship_ApplyHullHitpoints(rCharacter, iMinBoom * 40.0, KILL_BY_TOUCH, -1);
			Ship_ApplyCrewHitpoints(rCharacter, MakeFloat(rand(3)));

			int iNumFirePlaces = 0;
			SendMessage(rCharacter, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
			
			float fFirePlaces = Bring2Range(1.0, 0.1, 0.0, fMinLightningDist, fDist);

			float fCurr = 0.0;
			float fTest = (1.0 - fFirePlaces) * iNumFirePlaces;
			for (int j=0; j<iNumFirePlaces; j++)
			{
				fCurr = fCurr + 1.0;
				if (fCurr < fTest) { continue; }
	
				fCurr = 0.0;
				int iRandStartTime = rand(10000);
				float fTotalFireTime = Ship_GetTotalFireTime(rCharacter);

				PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rCharacter, rCharacter, j, "ship_onfire", fTotalFireTime, -1);
				PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", Ships[i], -1, j, fTotalFireTime);
			}
		}
	}
}

// Create a new ship for character  to_do del ����� �� �������
void Ship_CreateForCharacter(ref rCharacter, int iShipType, string sShipName)
{
	DeleteAttribute(rCharacter, "Ship");

	rCharacter.Ship.Type = iShipType;
	rCharacter.Ship.Name = sShipName;

	rCharacter.Ship.Cannons.Borts = "";
	rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS;
	rCharacter.Ship.Ang.y = 0.0;
	rCharacter.Ship.Pos.x = 0.0;
	rCharacter.Ship.Pos.y = 0.0;
	rCharacter.Ship.Pos.z = 0.0;
	rCharacter.Ship.Speed.z = 0.0;

	SetBaseShipData(rCharacter);
}

void Ship_ClearImpulseStrength(ref rCharacter)
{
	aref arImpulse; makearef(arImpulse, rCharacter.Ship.Impulse);
	arImpulse.Rotate.x = 0.0;
	arImpulse.Rotate.y = 0.0;
	arImpulse.Rotate.z = 0.0;
	arImpulse.Speed.x = 0.0;
	arImpulse.Speed.y = 0.0;
	arImpulse.Speed.z = 0.0;

	rCharacter.Ship.Tornado.Rotate.y = 0.0;  // fix boal
}

void Ship_PrepareShipForLocation(ref rCharacter)
{
	Ship_ClearImpulseStrength(rCharacter);
}
//  ����� ����� ������, �� ���� � ���
void Ship_LoadShip()
{
	int iCharacterIndex = GetEventData();
	
	ref rCharacter = GetCharacter(iCharacterIndex);
	
	//Dev_Trace("Ship_LoadShip = " + iCharacterIndex + " id = " + rCharacter.id + " ship.type = " + rCharacter.ship.type + " IsDead = " + LAi_IsDead(rCharacter));

			   
	//if (sti(rCharacter.ship.type) != SHIP_NOTUSED && !LAi_IsDead(rCharacter))
	if (sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		Event("eSwitchPerks", "l", iCharacterIndex);
		ShipModelrList[iNumShips] = GetCurrentModelrNumber();

		Ships[iNumShips] = iCharacterIndex;
		rCharacter.curshipnum = iNumShips;
		Dev_Trace("Ship_LoadShip = " + iCharacterIndex + " id = " + rCharacter.id + " iNumShips = " + iNumShips + " curshipnum = " + rCharacter.curshipnum + " ShipModelrList[iNumShips] = " + ShipModelrList[iNumShips]);
		Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      ����� �������� �������
		iNumShips++;
	}
}

void Ship_LoadShipActivateFirePlace()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();
	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	Dev_Trace("iBallCharacterIndex = " + iBallCharacterIndex);
	int iStartTime = 500;

	PostEvent(SHIP_FIRE_DAMAGE, iStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
}

void SetTextureForShip(aref refBaseShip, aref rCharacter)
{
	if(!CheckAttribute(refBaseShip, "name"))
	{
		trace("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		return;
	}

	string sPath = "ships\" + refBaseShip.name + "\";
	
	if(CheckAttribute(refBaseShip, "ship.Upgrades.hull"))  // boal 16/07/06 ������ ������ �������, ��� ���
	{
		sPath = sPath + "hull" + refBaseShip.ship.upgrades.hull + "\";
	}

	//Boyer add #20170423-01
    rCharacter.Ship.setTexturePath = sPath;
	//SetTexturePath(0, sPath);
}

void DropGoodsToSea()
{
	aref rCharacter = GetEventData();

	ref rGood;
	string sGood;

	for (int i=GOOD_MEDICAMENT; i<GOOD_CULVERINE_32; i++)
	{
		sGood = Goods[i].name;

		if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood))
		{
			int	iQuantity = sti(rCharacter.Ship.Cargo.Goods.(sGood));
			
			if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood+".Lock")) continue; // ���������� ������ �� ���������� !!!!! <-- ugeen fix
			
			if (iQuantity < 1 && rand(1) == 1) continue; 
			iQuantity = makeint(iQuantity/2 + rand(makeint(iQuantity/3)));   // ���������� �� ��� � �� ������, � �� ��� ����
			
			if (iQuantity < 1) continue; 
			
			RemoveCharacterGoods(rCharacter, i, iQuantity);

			iQuantity = iQuantity / sti(Goods[i].Units);

			if (iQuantity <= 1) 
			{ 
				continue; 
			}

			rCharacter.Ship.Cargo.Goods.(sGood) = 0;
            rCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal fix �����������
			//RecalculateCargoLoad(rCharacter);
            rCharacter.Tmp.SpeedRecall = 0; // ���� ������������� �������� � ������
            
			if (CheckAttribute(&Goods[i], "Swim")) 
			{ 
				int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

				if(iSwimQuantity < 1)
				{
					iSwimQuantity = 1;
				}
				float fTime = stf(Goods[i].Swim.Time);
				string sModel = Goods[i].Swim.Model;

				//trace ("sModel is " + sModel);

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(rCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			return;
		}
	}
}

int Ship_GetRunAwayPoint()
{
	aref arChar = GetEventData();
	float fX = GetEventData();
	float fZ = GetEventData();

	float fRadius = 10000.0;
	float fWindAngle = Whr_GetWindAngle();

	arChar.SeaAI.WindAngle = fWindAngle;
	arChar.SeaAI.RunAwayPnt.x = stf(arChar.Ship.Pos.x) + fRadius * sin(fWindAngle);
	arChar.SeaAI.RunAwayPnt.z = stf(arChar.Ship.Pos.z) + fRadius * cos(fWindAngle);

	return 0;
}

// boal -->
string GetShipSexWord(string _type, string _man, string _woman)
{
    if (_type == "Tartane" || _type == "Schooner" || _type == "Caravel" )
    {
        return _woman;
    }
    else
    {
        return _man;
    }
}
// boal 08.08.06 ����� ��������� ������ �� �������  - ��������� ����
void Ship_ResearchCannons(ref aCharacter)
{
	if (bSeaLoaded)
	{
		// Log_Info("test5");
		aCharacter.BOAL_ReadyCharge = "1";
		SendMessage(&AISea, "la", AI_MESSAGE_RESEARCH_CANNONS, aCharacter);
		RefreshBattleInterface();
		Ship_ChangeCharge(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type));
	}
}
// boal 20.08.06 ����������� ����� -->
void Ship_FlagRefresh(ref rCharacter)
{
    if (bSeaLoaded)
	{
		SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
	}
}

void EmptyFantom_DropGoodsToSea(ref rChar, int iFantomType)
{
	float fTime;
	string sGood, sModel;
	int iQty;
	if(iFantomType == ENCOUNTER_TYPE_BARREL)
	{	
		int irand = drand(100);
		if(irand > 92) // ������ ���
		{
			AISeaGoods_AddGood_Special(rChar, "powder1", "barrel_treasure", 1500.0, 1); // ��������� �� ������������ ����
		}
		else
		{
			if(irand < 40) 
			{
				for (int i=GOOD_MEDICAMENT; i<GOOD_GOLD; i++)
				{
					sGood = Goods[i].name;
					if (rand(3) > 1) continue; 
					if (CheckAttribute(&Goods[i], "Swim")) 
					{
						iQty = rand(15) + 5; 
						fTime = stf(Goods[i].Swim.Time);
						sModel = Goods[i].Swim.Model;
						fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

						AISeaGoods_AddGood_Special(rChar, sGood, sModel, fTime * 60.0, iQty);
					}	
				}
			}		
			AISeaGoods_AddGood_Special(rChar, "barrel_treasure", "barrel_treasure", 1500.0, 1);			
		}	
	}
	if(iFantomType == ENCOUNTER_TYPE_BOAT)
	{
		AISeaGoods_AddGood_Special(rChar, "unknown_boat", "lo_boat", 1500.0, 1);
	}
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rChar);
}

bool Ship_CheckMorale(int chridx, bool checkNow)
{
	return true;
	ref rCharacter = GetCharacter(chridx);
	if(CheckAttribute(rCharacter,"surrendered")) return false; // NK surrender 05-04-20
	//if(IsCompanion(&rCharacter)) return false;  //Skip companions (and mainchar??)

	if (!CheckAttribute(rCharacter,"ship.type")) {
		trace("missing ship type for character: " + rCharacter.id + ", index: " + chridx);
		return false; //
	}
	if(rCharacter.ship.type == SHIP_FORT) return false;

	if (!checkNow) {
		//check occasionally
		int timecheck = CHANGE_MORALE_EVERY
		if(chridx == GetMainCharacterIndex()) {
			timecheck *= 50 //seem to get ~50 mainchar ticks per NPC tick
		}
		int timesincelast = 0;
		if(CheckAttribute(rCharacter,"seatime.timesincelast"))
		{	timesincelast = sti(rCharacter.seatime.timesincelast); }
		if(timesincelast < timecheck)
		{ //increment one and skip; this is to do this once every CHANGE_MORALE_EVERY seconds
			rCharacter.seatime.timesincelast = timesincelast+1;
			return false;
		}
		rCharacter.seatime.timesincelast = 0; //reset counter
	}
	//if (AISHIPDEBUG)	trace("************************************** CHECK MORALE FOR " + rCharacter.ship.name);

	//#20191022-02
	rCharacter.seatime.surmargin = SURR_MARGIN;
	if(!CheckAttribute(rCharacter,"Ship.Crew.Morale")) { rCharacter.Ship.Crew.Morale = 45; }
	if(!CheckAttribute(rCharacter,"seatime.basecrewmorale")) { rCharacter.seatime.basecrewmorale = rCharacter.Ship.Crew.Morale; }

	int CrewQuantity = GetCrewQuantity(rCharacter);
	if(!CheckAttribute(rCharacter,"seatime.basecrewquantity")) { rCharacter.seatime.basecrewquantity = CrewQuantity; }

	int basemorale = sti(rCharacter.seatime.basecrewmorale);

	float fMaxTempMorale = (MORALE_MAX + basemorale)/2.0;  //how much can morale increase if things are going well

	float tempmorale = stf(rCharacter.ship.crew.morale); if(CheckAttribute(rCharacter,"seatime.tempmorale")) tempmorale = stf(rCharacter.seatime.tempmorale); //i.e. a float morale
	rCharacter.seatime.tempmorale = tempmorale;

	float enemydistance = DIST_NOSHIP;
	//#20190703-01
	aref rSituation;
    makearef(rSituation, rCharacter.SeaAI.Update.Situation);

    int targetidx = sti(rSituation.MinEnemyIndex);
    enemydistance = stf(rSituation.MinEnemyDistance); // finds nearest hostile ship
    float fdist;
    int frndidx = sti(rSituation.MinFriendIndex);
    fdist = stf(rSituation.MinFriendDistance);

	int currenttime = GetSeaTime();
	int lasthit = -1; if(CheckAttribute(rCharacter,"seatime.lasthit")) lasthit = sti(rCharacter.seatime.lasthit); //last time we were hit
	int lastfired = -1; if(CheckAttribute(rCharacter,"seatime.lastfired")) lastfired = sti(rCharacter.seatime.lastfired); // last time we fired or reloaded

	//if (AISHIPDEBUG)	trace("Checking morale for the " + rCharacter.ship.name + ", time is " + currenttime + ", current morale is " + tempmorale + ", lht " + lasthit + ", lft " + lastfired);

	//Adjust Morale for dead crew
	if(CheckAttribute(rCharacter,"seatime.lastcrew"))
	{
		//Boyer fix for game crash after captain mission #20170318-44
		if (sti(rCharacter.seatime.basecrewquantity)  != 0) //Skip if basecrew zero
			tempmorale = tempmorale - (stf(rCharacter.seatime.lastcrew) - makefloat(CrewQuantity)) / stf(rCharacter.seatime.basecrewquantity) / CREW_PCT_FOR_MORALE;
		DeleteAttribute(rCharacter,"seatime.lastcrew");
		//if (AISHIPDEBUG)		trace("subtract morale for crew dmg, morale is: " + tempmorale);
	}
	//Adjust Morale for damaged ship
	if(CheckAttribute(rCharacter,"seatime.lastHP"))
	{
		//Boyer fix #20170318-44 for game crash after captain mission divide by zero error
		if (makefloat(GetCharacterShipHP(rCharacter)) != 0.0) //Skip if ShipHP is zero...would be dead anyway
			tempmorale = tempmorale - (stf(rCharacter.seatime.lastHP) - makefloat(rCharacter.Ship.HP)) / makefloat(GetCharacterShipHP(rCharacter)) / CREW_PCT_FOR_HPDAM;
		DeleteAttribute(rCharacter,"seatime.lastHP");
		//if (AISHIPDEBUG)		trace("subtract morale for ship dmg, morale is: " + tempmorale);
	}
	//Adjust Morale for being in combat
	float combatlevel = COMBATLEVEL_NONE;
	if(enemydistance <= RANGE_TO_ENEMY) combatlevel = COMBATLEVEL_ENEMYHERE;
	if(lastfired != -1) { if((currenttime - lastfired) < TIME_SINCE_GUNS) combatlevel = COMBATLEVEL_GUNS; }
	if(lasthit != -1) { if((currenttime - lasthit) < TIME_SINCE_HIT) combatlevel = COMBATLEVEL_HIT; }

	//if (AISHIPDEBUG)	trace("Current combatlevel is " + combatlevel);

	if(combatlevel == COMBATLEVEL_NONE)
	{
		// return to baseline when not in combat
		if(makeint(tempmorale) != basemorale)
		{
			//if (AISHIPDEBUG)			trace("Out of combat, return morale to base");
			if(tempmorale > basemorale) tempmorale -= MORALE_AMT_COMEBACK;
			else tempmorale += MORALE_AMT_COMEBACK;
		}
	}
	else
	{
		//morale auto decreases to: ~80 (with ENEMYHERE), ~62 (with COMBATLEVEL_GUNS), ~16 when COMBATLEVEL_HIT.  More than that requires crew loss
		if(tempmorale > 5.0 / combatlevel)
		{
			//if (AISHIPDEBUG)			trace("In combat, subtract morale:" + retmin(COMBATLEVEL_HIT*CHANGE_MORALE_EVERY, combatlevel*2.5));
			tempmorale -= retmin(COMBATLEVEL_HIT*CHANGE_MORALE_EVERY, combatlevel*2.5);
		}
	}
	if(CheckAttribute(rCharacter,"seatime.enemydead"))
	{
		//if (AISHIPDEBUG)		trace("Adding Morale enemydead= " + rCharacter.seatime.enemydead);
		tempmorale += stf(rCharacter.seatime.enemydead);
		DeleteAttribute(rCharacter,"seatime.enemydead"); // 04-09-22 fix
	}
	//if a more powerful fleet gain morale (up to base)
	float strengthrat = FindPowerRatio(chridx);

	if (strengthrat < 0.6 && fdist < enemydistance && combatlevel != COMBATLEVEL_NONE)
	{ //stronger and with friends, so recover morale (probably winning)
		//if (AISHIPDEBUG)		trace("Adding Morale for " + rCharacter.ship.name + " being in a position of power");
		if(tempmorale < fMaxTempMorale) tempmorale += COMBATLEVEL_ENEMYHERE*2.5;
	}
	if(tempmorale > MORALE_MAX) tempmorale = MORALE_MAX;
	if(tempmorale < MORALE_MIN) tempmorale = MORALE_MIN;

	//if (AISHIPDEBUG)	trace("Morale for " + rCharacter.ship.name + " is " + tempmorale + ", change " + (tempmorale - makefloat(sti(rCharacter.seatime.tempmorale))));

	//rCharacter.ship.crew.morale = makeint(tempmorale);
	rCharacter.seatime.tempmorale = tempmorale;

	//Calculate Morale at which we consider surrender
	float surmorale;
	rCharacter.seatime.surmorale = 0.0;  //default, no surrender chance

	if(IsCompanion(rCharacter) || targetidx == -1 || lasthit == -1 || CheckAttribute(rCharacter, "cannotsurrender")) {
		//No surrender
		//if (AISHIPDEBUG)		Trace("****** Surrender Disabled ******");
		return false;
	}
	float ftmult = 1.0;
	//#20191022-02
	float surrMarg = SURR_MARGIN;
	//#20200309-01
	/*
	if(CheckAttribute(rCharacter,"EncType"))
	{
		switch(rCharacter.EncType)
		{
			case "trade": ftmult = 1.5; surrMarg += 2.0; break; //ftmult was 2.0 and surrMarg was 2.5 //#20200307-03
			//#20191021-01
			case "pirate": ftmult = 0.85; surrMarg += 1.0; break; // ftmult was 0.75
		}
	}
	*/
	//Encounter type mod
	if(CheckAttribute(rCharacter,"EncType") && rCharacter.EncType == "trade") {
        ftmult *= 1.5; surrMarg += 2.0; //ftmult was 2.0 and surrMarg was 2.5 //#20200307-03
	}
	//Nation mod
	int nCharNat = sti(rCharacter.Nation);
	switch(nCharNat) {
        case PIRATE:
            int nOtherNation = sti(pchar.nation);
            int nLastBallChar = -1;
            if(CheckAttribute(rCharacter, "ship.LastBallCharacter"))
                nLastBallChar = sti(rCharacter.ship.LastBallCharacter);
            if(nLastBallChar > -1)
                nOtherNation = sti(Characters[nLastBallChar].nation);
            if(nOtherNation == PIRATE)
                ftmult *= 0.85; surrMarg *= 1.0; break;
            else
                ftmult *= 0.35; surrMarg *= 1.5; break;
        break;
        case SPAIN:
            ftmult *= 0.15;
        break;
        case HOLLAND:
            ftmult *= 0.85;
        break;
	}
	//Ship class mod
	int nShip = GetCharacterShipType(rCharacter);
	if (nShip != SHIP_NOTUSED) {
        int nClass = 7;
        if(CheckAttribute(RealShips[nShip], "class"))
            nClass = sti(RealShips[nShip].Class);
        switch(nClass) {
            case 5:
                ftmult *= 0.85; surrMarg *= 0.75; break;
            break;
            case 4:
                ftmult *= 0.65; surrMarg *= 0.55; break;
            break;
            case 3:
                ftmult *= 0.45; surrMarg *= 0.35; break;
            break;
            case 2:
                ftmult *= 0.25; surrMarg *= 0.15; break;
            break;
            case 1:
                ftmult = 0.0; surrMarg = 0.0; break;
            break;
        }
	}
	//NPC Rank mod
	int nRank = sti(pchar.rank);
	if (nRank > 10) {
        float fRnk = Bring2Range(1.0, 0.5, 10.0, 50.0, stf(pchar.rank));
        ftmult *= fRnk;
	}
	rCharacter.seatime.surmargin = surrMarg; //This only affects likely to flee
	float mrlmod = Bring2Range(SURR_MRL_SCL_MAX, SURR_MRL_SCL_MIN, 0.1, 1.4, stf(rCharacter.TmpSkill.Leadership)+ AIShip_isPerksUse(rCharacter.TmpPerks.IronWill, 0.0, 0.4));
	ref pch = GetMainCharacter();

	surmorale = SURR_MAX_MORALE * mrlmod * ftmult;

	//if (AISHIPDEBUG) Trace("SURR MORALE: base SurenderMorale = " + surmorale);

	if (enemydistance > 1600.0) {
        //#20200307-03
        DeleteAttribute(rCharacter, "seatime.thinkSurr");
        return false;				// LDH don't surrender if enemy not on radar
	}
	float HPp = GetHullPercent(rCharacter);

	//if(HPp > 40.0 && fdist <= enemydistance) return false; // if friend closer than enemy, no surrender.
	//#20191021-01
	//if (AISHIPDEBUG)	Trace("SURR MORALE: Check: HPp = " + HPp + ", fdist " + fdist + ", enemydist " + enemydistance + ", stren " + strengthrat);
    if (HPp > 40.0 && fdist <= enemydistance && strengthrat < 0.8) return false;

	if(HPp < 40.0)
	{
		//if (AISHIPDEBUG)		Trace("SURR: hull damage: HPp: " + HPp + ", Bring2Range(6.0, 1.0, 0.1, sqrt(40.0), sqrt(HPp)): " + Bring2Range(6.0, 1.0, 0.1, 6.325, sqrt(HPp)));
        //#20180921-01 remove sqrt(40.0) = 6.325
		surmorale *= Bring2Range(6.0, 1.0, 0.1, 6.325, sqrt(HPp)); //how broken are we? x6 change at really broken, x0.5 at 40 percents
		if (fdist < enemydistance - 200.0) {
			//if (AISHIPDEBUG)			Trace("SURR: friend close to help");
			surmorale *= 0.5; //is a friend close to help?
		}
	}
	//if (AISHIPDEBUG)	Trace("SURR MORALE: After Damage Mod: SurenderMorale = " + surmorale);

	//Whose got strong (local) power?
	if(strengthrat > 1.0) // they're stronger
	{
	    //if (AISHIPDEBUG)        Trace("SURR MORALE: Enemy Stronger strengthrat = " + strengthrat);
		float SP = GetSailPercent(rCharacter);
		//#20180921-01 remove sqrt(50.0) = 7.071
		if(SP < 40.0) surmorale *= Bring2Range(5.0, 1.0, 0.1, 7.071, sqrt(SP)); //panic if can't get away
	}
	else
	{ // we're stronger
		surmorale *= 0.3;
	}
	//if (AISHIPDEBUG)	Trace("SURR MORALE: After local Strength Mod: SurenderMorale = " + surmorale);

	//if (AISHIPDEBUG)	Trace("SURR: GetDistDeltaToNearestEnemy(chridx) " + GetDistDeltaToNearestEnemy(chridx));

	if (GetDistDeltaToNearestEnemy(chridx) > 1.0) {
		//seem to be escaping, so unlikely to surrender
		surmorale *= 0.1;
	}
	//if (AISHIPDEBUG)	Trace("SURR: surmorale after escaping modifier surmorale, tempmorale" + surmorale + ", " + tempmorale);

	rCharacter.seatime.surmorale = surmorale;

	if(tempmorale > surmorale)
	{
		// put ship back in group and do group's task.
		//ref rGroup = Group_FindOrCreateGroup(Ship_GetGroupID(rCharacter));
		//if(CheckAttribute(rGroup,"task") && rGroup.task != AITASK_RUNAWAY && CheckAttribute(rCharacter,"SeaAI.task") && rCharacter.SeaAI.task != rGroup.task) { Ship_SetTaskGroupTask(SECONDARY_TASK, chridx); }

		//if (AISHIPDEBUG)		trace("*** Ship_Checkmorale surmorale:" + surmorale + " is less than " + tempmorale + " so keep fighting");
        //#20200307-03
        if(CheckAttribute(rCharacter, "seatime.thinkSurr")) {
            int nSur = sti(rCharacter.seatime.thinkSurr);
            if(nSur <= 1)
                DeleteAttribute(rCharacter, "seatime.thinkSurr");
            else
                rCharacter.seatime.thinkSurr = nSur - 1;
        }
		return false;
	} //#20200307-03
	else {
        if(CheckAttribute(rCharacter, "seatime.thinkSurr"))
            rCharacter.seatime.thinkSurr = sti(rCharacter.seatime.thinkSurr) + 1;
        else
            rCharacter.seatime.thinkSurr = 1;
	}
	return true;  //chance to surrender
}

float GetDistDeltaToNearestEnemy(int idx)
{
	float fDistDelta = 0.0;
	ref chr = GetCharacter(idx);
	float fEnemyDistance = 0.0;
	//#20190703-01
	aref rSituation;
    makearef(rSituation, chr.SeaAI.Update.Situation);
	int iClosestIdx = sti(rSituation.MinEnemyIndex);
	fEnemyDistance = stf(rSituation.MinEnemyDistance);
	if (iClosestIdx == -1) { return 0; }
	float fNow = GetSeaTime();

	if (CheckAttribute(chr, "seatime.nearestenemy.id") && iClosestIdx == sti(chr.seatime.nearestenemy.id))
	{
		//same enemy is closest, return distance change.
		float fTimeDelta = fNow - stf(chr.seatime.nearestenemy.lastcheck)
//trace("fTimeDelta:" + fTimeDelta);
		if (fTimeDelta > 1)
		{
			//calc distance
			fDistDelta = (fEnemyDistance - stf(chr.seatime.nearestenemy.dist))/fTimeDelta;
		}
		else
		{
			//timespan too short
			return stf(chr.seatime.nearestenemy.LastDelta);
		}
	}
	chr.seatime.nearestenemy.id = iClosestIdx;
	chr.seatime.nearestenemy.dist = fEnemyDistance;
	chr.seatime.nearestenemy.lastcheck = GetSeaTime();
	chr.seatime.nearestenemy.LastDelta = fDistDelta;
	return fDistDelta;
}


bool Ship_CheckMoraleFail(int chridx, float fSurrMult)
{
	// start surrender checking, also used for ransome checking
	ref rCharacter = GetCharacter(chridx);
	//if (AISHIPDEBUG)	trace("*** Ship_CheckMoraleFail chridx:" + rCharacter.ship.id + ", fSurrMult " + fSurrMult);

	if(!CheckAttribute(rCharacter,"seatime.tempmorale")) {
		//do a morale calc
		Ship_CheckMorale(chridx, true);
	}
	float tempmorale = rCharacter.seatime.tempmorale;

	if (!CheckAttribute(rCharacter, "seatime.surmorale")) {
		//if (AISHIPDEBUG)  trace("*** Ship_CheckMoraleFail missing rCharacter.seatime.surmorale");
		return false;
	}
	float surmorale = stf(rCharacter.seatime.surmorale) * fSurrMult;

	if(tempmorale < surmorale)
	{
		//if (AISHIPDEBUG)		trace("*** Ship_CheckMoraleFail tempmorale:" + tempmorale + " is less than adjusted surmorale:" + surmorale + " so failed morale check");
		return true;
	}
	//if (AISHIPDEBUG)	trace("*** Ship_CheckMoraleFail tempmorale:" + tempmorale + " is greater than adjusted surmorale:" + surmorale + " so morale ok");
	return false;
}

bool CheckCanSurrender(ref chr)
{
	if(CheckAttribute(chr, "cannotsurrender"))
	{
		//if (AISHIPDEBUG)  trace("CheckCanSurrender: No Surrender! chr.cannotsurrender exists");
		return false;
	}
	if(CheckAttribute(chr, "DontRansackCaptain"))
	{
		//if (AISHIPDEBUG)  trace("CheckCanSurrender: No Surrender! chr.DontRansackCaptain exists");
		return false;
	}
	if (!CheckAttribute(chr,"Ship.Type") || sti(chr.Ship.Type) < 0 || sti(chr.Ship.Type) ==SHIP_NOTUSED)
	{
		//if (AISHIPDEBUG)  trace("CheckCanSurrender: No Surrender! invalid ship type");
		return false;
	}
	//conditions when ship will never surrender
	if (GetPrisonerQty() > PRISONER_MAX)
	{
		//if (AISHIPDEBUG) trace("CheckCanSurrender: No Surrender!GetPrisonerQty() > PRISONER_MAX");
		return false;
	}
	if (sti(pchar.rank) < (sti(chr.rank) - MOD_SKILL_ENEMY_RATE / 2))
	{
		//if (AISHIPDEBUG) trace("CheckCanSurrender: No Surrender!sti(pchar.rank) < (sti(chr.rank) - MOD_SKILL_ENEMY_RATE / 2)");
		return false;
	}
	if (GetCharacterShipClass(chr) == 1)
	{
		//if (AISHIPDEBUG) trace("CheckCanSurrender: No Surrender! Enemy ship is class 1, they don't surrender");
		return false;
	}
	return true;
}

void AddKillMorale(ref rKillerCharacter, ref rDead) {
	ref schr;
	int iDeadCharacterIndex = GetCharacterIndex(rDead.id);
	float tmped = 0;
	//if (AISHIPDEBUG) trace("AddKillMorale: rKillerCharacter.id" + rKillerCharacter.id + ", rDead.id" + rDead.id);
	if(rKillerCharacter.id != rDead.id) {
		if(CheckAttribute(rKillerCharacter,"seatime.enemydead")) tmped = stf(rKillerCharacter.seatime.enemydead);
		float origed = makefloat(GetCharacterShipClass(rKillerCharacter)) / makefloat(GetCharacterShipClass(rDead)) * CLASS_SCALAR_FOR_MORALE;
		tmped += origed;
		rKillerCharacter.seatime.enemydead = tmped;
	}
	int iDeadChNation = sti(rDead.nation);
	for(int s = 0; s < iNumShips; s++)
	{
		if(Ships[s] < 0 || Ships[s] == iDeadCharacterIndex) continue; // KK
		//if (AISHIPDEBUG) trace("AddKillMorale: Ships[s]" + Ships[s]);
		schr = GetCharacter(Ships[s]);
		bool bOldEnemy = CheckAttribute(rDead, "surrendered") && GetNationRelation2Character(iDeadChNation,Ships[s]) == RELATION_ENEMY;
		if(SeaAI_GetRelation(iDeadCharacterIndex, Ships[s]) == RELATION_ENEMY || bOldEnemy)
		{
			tmped = 0;
			if(CheckAttribute(schr,"seatime.enemydead")) tmped = stf(schr.seatime.enemydead);
			tmped += origed * CLASS_SCALAR_FOR_MORALE_ORIG_TO_OTHER + makefloat(GetCharacterShipClass(schr)) / makefloat(GetCharacterShipClass(rDead)) * CLASS_SCALAR_FOR_MORALE_OTHER;
			schr.seatime.enemydead = tmped;
		}
	}
}

int GetSeaTime()
{
	ref pchar = GetMainCharacter();
	if(!CheckAttribute(pchar,"seatime")) return 0;
	return sti(pchar.seatime);
}

float FindPowerRatio(int idx)
{
    //if (AISHIPDEBUG) trace("FindPowerRatio(idx=" + idx + ")");
	ref chr = GetCharacter(idx);

	//to reduce load do this every three ticks, otherwise return last value.
	if (CheckAttribute(chr,"seatime.lastPowercheck.val"))
	{
		//we can return last val if needed
		int iPowercheckdelay = sti(chr.seatime.lastPowercheck);

		if(iPowercheckdelay < 3)
		{
			chr.seatime.lastPowercheck = iPowercheckdelay + 1;
			return stf(chr.seatime.lastPowercheck.val);
		}
	}
	//haven't got previous value, or time to recalc:
	chr.seatime.lastPowercheck = 0; //reset counter

	//#20190703-01
	//int sidx = sti(chr.curshipnum); // change to array 05-06-27

	float epower;
	float fpower;

    SendMessage(&AISea, "lale", AI_MESSAGE_GROUP_GET_POWERREL, chr, RELATION_ENEMY, &epower);
    SendMessage(&AISea, "lale", AI_MESSAGE_GROUP_GET_POWERREL, chr, RELATION_FRIEND, &fpower);

	if(epower < 0.5) epower = 1.0;
	if(fpower < 0.5) fpower = 1.0;

	float fResult = epower / fpower;
    //if (AISHIPDEBUG)    trace("FindPowerRatio " + chr.ship.name + ": " + fResult);

	chr.seatime.lastPowercheck.val = fResult; //Fix missing .val
	return fResult;
}

bool Ship_Check_Surrender(int chridx, float fSurrMult)
{
	// start surrender checking, also used for ransom checking
	//#20200307-03
	int nSurr = surrenderenabled;
	if(fSurrMult > 0.0) {
	    switch(nSurr) {
	        case 1: //occasional surrender
                fSurrMult -= frand(0.15);
                fSurrMult += frand(0.1);
            break;
            case 2: //rare surrender
                fSurrMult -= frand(0.25);
                fSurrMult += frand(0.15);
            break;
            case 3://very rare surrender
                fSurrMult -= frand(0.25);
                fSurrMult -= frand(0.25);
            break;
        }
	}
	//if (AISHIPDEBUG)	trace("*** Ship_Check_Surrender chridx:" + Characters[chridx].ship.name + ", fSurrMult " + fSurrMult);

	ref rCharacter = GetCharacter(chridx);

	if(!CheckAttribute(rCharacter,"seatime.tempmorale")) {
		//do a morale calc
		if (!Ship_CheckMorale(chridx, true)) return false;  //Boyer fix for when Ship_CheckMorale does not set .seatime.tempmorale #20170318-45
	}
	float tempmorale = rCharacter.seatime.tempmorale;
	//#20200307-03
	if(tempmorale < 0.05) {
	    switch(nSurr) {
	        case 1: //occasional surrender
                tempmorale += frand(0.15);
            break;
            case 2: //rare surrender
                tempmorale += frand(0.25);
                tempmorale += frand(0.25);
            break;
            case 3://very rare surrender
                tempmorale += frand(0.5);
                tempmorale += frand(0.5);
            break;
        }
	}
	if (!CheckAttribute(rCharacter, "seatime.surmorale") || stf(rCharacter.seatime.surmorale) < 0.01) {
		return false;
	}
	float surmorale = stf(rCharacter.seatime.surmorale) * fSurrMult;
    //#20200307-03
	if(surmorale < tempmorale) return false;

	int nThink = 25;
	if(CheckAttribute(rCharacter, "seatime.thinkSurr"))
        nThink = sti(rCharacter.seatime.thinkSurr);
    nThink = nThink % 50;
    switch(nSurr) {
        case 1: //occasional surrender
            if(rand(nThink) > 20) return false;
        break;
        case 2: //rare surrender
            if(rand(nThink) > 10) return false;
        break;
        case 3://very rare surrender
            if(rand(nThink) > 5) return false;
        break;
    }
	//if (AISHIPDEBUG)	trace("*** Ship_Checkmorale surmorale:" + surmorale + " is greater than " + tempmorale + " so maybe surrender");

	float surch;
	surch = Bring2Range(0.75, 0.01, 0.01, surmorale, tempmorale);

	//if (AISHIPDEBUG) Trace("SURR: Initial surch = " + surch);

	//ref echr = GetCharacter(targetidx);

	surch *= SURR_GLOBAL_SCL; // LDH

	//if (AISHIPDEBUG)	Trace("SURR: surch after global modifier = " + surch);

	if (surch < 0.1) return false;  //just don't surrender if less then 10 percent chance

	//use random surrender chance
	float fRoll = frnd();
	//if (AISHIPDEBUG)	Trace("SURR: surrender roll: fRoll=" + fRoll + ", surch=" + surch);
	if(fRoll < surch)
	{
		//if (AISHIPDEBUG)		Trace("Morale fail");
		return true;
	}
	return false;
}

void Ship_Surrender(int chridx)
{
	//if (AISHIPDEBUG)	trace("SURR: Ship_Surrender begin idx: " + chridx);
	ref chr = GetCharacter(chridx);
	int pchridx = GetMainCharacterIndex();
	string chid = chr.id;

	if (CheckAttribute(chr, "surrendered") || CheckAttribute(chr, "cannotsurrender")) {
		//if (AISHIPDEBUG)		trace("trying to surrender again.  But will only surrender once");
		return;
	}
	//if (AISHIPDEBUG)	trace("SURR: " + chid + " is surrendering.  Ship nation: " + sti(chr.nation) );

	int nRel = SeaAI_GetRelation(chridx, pchridx);
	//set surrendered
	chr.surrendered = true;
	chr.surrendered.seatime = GetSeaTime();

	// Set ship to take no actions
	Ship_SetTaskDrift(PRIMARY_TASK, chridx);
	Ship_SetTaskDrift(SECONDARY_TASK, chridx);

	//Raise White Flag
	Ship_FlagRefresh(chr);

	//set flag to increase morale for enemies of surrendered ships
	AddKillMorale(chr, chr);

	//forget that you were shot
	chr.Ship.LastBallCharacter = -1;

	// Alert that ship has surrendered
	if (nRel == RELATION_ENEMY) {
		Log_SetStringToLog(xiStr("MSG_sea_10") + chr.ship.name + xiStr("MSG_sea_11"));
		PlaySound("interface\notebook.wav");
		PlayVoice("interface\abordage_wining.wav");
	} else {
		Log_SetStringToLog(xiStr("MSG_sea_10") + chr.ship.name + xiStr("MSG_sea_12"));
	}
	Ship_Neutral(chridx, "SURR_GROUP");
	//if (AISHIPDEBUG)	Trace("SURR: Ship_Surrender complete");
}

void Ship_Neutral(int chridx, string sGroup)
{
	//if (AISHIPDEBUG) Trace("Ship_Neutral: Ship_Neutral begin idx: " + chridx);
	ref chr = GetCharacter(chridx);
	string chid = chr.id;

	//remember old relations
	if(CheckAttribute(chr,"relation")) {
		chr.oldrelation = "";
		aref arRel; makearef(arRel, chr.relation);
		aref arOldRel; makearef(arOldRel, chr.oldrelation);
		CopyAttributes(arOldRel, arRel);
	}
	//string sTemp1 = "" + iCharacterIndex2;
	//Characters[iCharacterIndex1].relation.(sTemp1) = iRelationType;

	//forget that you were shot
	chr.Ship.LastBallCharacter = -1;

	//*** Fix group membership as neutral ship changes group.
	int i;
	ref rGroup = Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "trade");

	ref pchar = GetMainCharacter();
	int pchridx = GetMainCharacterIndex();
	ref schr;
	string ogroup = Ship_GetGroupID(&chr);

	int cmdridx = Group_GetGroupCommanderIndex(ogroup);
	if (cmdridx < 0) return;
	ref cmdr = GetCharacter(cmdridx);

	bool cmdrchange = cmdridx == chridx;

	ref rOGroup = Group_GetGroupByID(ogroup);
	bool firstchar = Group_GetCharacterIndexR(rOGroup, 0) == chridx;  // was this char the commander?
	//#20180914-03
	int og_ships = Group_GetLiveCharactersNum(ogroup); //Group_GetCharactersNumR(rOGroup);

	if (cmdrchange) {
		//set new commander if group commander surrenders
		if (og_ships > 1) {
			cmdridx = Group_GetCharacterIndexR(rOGroup, firstchar);  //if was the commander, get the second ship in group
			cmdr = GetCharacter(cmdridx);
			DeleteAttribute(cmdr,"relation.UseOtherCharacter");
			Group_SetGroupCommander(ogroup, cmdr.id); //set new commander
			Group_Refresh_Engine_relations(ogroup);
		} else {
		    Group_SetAddress(ogroup, "None", "", "");
			Group_DeleteGroup(ogroup); // KK
		}
	}
	//#20180914-03
    if(og_ships < 2 && ogroup == "PGGQuestE") {
        DeleteAttribute(PChar, "Quest.PGGQuest1_GroupDead.win_condition.l1.Group");
        PChar.Quest.PGGQuest1_GroupDead.win_condition.l1 = "Ship_capture";
        PChar.Quest.PGGQuest1_GroupDead.win_condition.l1.character = chridx;
    }
	//Remove ship from old group
	//if (AISHIPDEBUG) trace("Ship_Neutral: setting up character group: ogroup="+ ogroup);

	Group_DelCharacter(ogroup, chid);

	Event(SHIP_UPDATE_PARAMETERS, "lf", chridx, 1.0);		// Parameters

	DeleteAttribute(chr,"relation.UseOtherCharacter");
	Group_ChangeCharacter(sGroup, chid);
	Group_SetGroupCommander(sGroup, chid);
	ChangeCharacterShipGroup(chr, sGroup); //forces a engine group boss refresh for this char
	Group_DeleteAtEnd(sGroup);

	//if (AISHIPDEBUG) Trace("Ship_Neutral: group change done");
	//#20190728-01
    bool bHasOld = false;
    if(CheckAttribute(chr, "surrendered")) {
        bHasOld = true;
        int bOlSurr = sti(chr.surrendered);
        int nOldTime = sti(chr.surrendered.seatime);
        DeleteAttribute(chr, "surrendered");
    }
	//Set ship neutral to their enemies
	for (i = 0; i < iNumShips; i++) {
		//if (ships[i] == -1 || ships[i] == chridx) continue;
		if (ships[i] == -1) continue;
		schr = GetCharacter(ships[i]);
		//if (AISHIPDEBUG) trace("Ship_Neutral: chr.id: " + chr.id + ", schr.id " + schr.id);
		if (chr.id == schr.id) continue;

		if(GetRelation(chridx, ships[i]) == RELATION_ENEMY || GetNationRelation2Character(sti(schr.nation),chridx) == RELATION_ENEMY)
		{
			//if (AISHIPDEBUG) trace("Ship_Neutral: Set relation between: chr.id: " + chr.id + " and schr.id " + schr.id + " to neutral");
			SetCharacterRelationBoth(chridx, ships[i], RELATION_NEUTRAL);
		}
	}
	//set ships neutral to forts
	if (CheckAttribute(pchar, "seaAI.update.forts")) {
		aref fortattr; makearef(fortattr, PChar.seaAI.update.forts);
		int iFortidx;
		int num = GetAttributesNum(fortattr);
		for (i = 0; i < num; i++)
		{
		    string fortstr = "l" + i;
			iFortidx = sti(fortattr.(fortstr).idx);
			//#20181116-03
			if(GetRelation(nMainCharacterIndex, iFortidx) == RELATION_ENEMY) continue;
			if(GetRelation(chridx, iFortidx)  == RELATION_ENEMY)
			{
			    //if (AISHIPDEBUG) trace("Ship_Neutral: Set relation between: " + chridx + " and fort:" + iFortidx + " to neutral");
				SetCharacterRelationBoth(chridx, iFortidx, RELATION_NEUTRAL);
			}
		}
	}
	//#20190728-01
	if(bHasOld) {
        chr.surrendered = bOlSurr;
        chr.surrendered.seatime = nOldTime;
    }
	NationUpdate();
    DoQuestCheckDelay("NationUpdate", 0.9);

	//if (AISHIPDEBUG) Trace("Ship_Neutral: Ship_Neutral complete");
}


void FlagPerkForCapturedShip(ref refChar) 
{
	//Trace("FlagPerkForCapturedShip.nation = " + refChar.nation);
	string sMessage = "";
	string sPerk = "";

	if(!CheckAttribute(refChar, "nation")) return;
	switch(sti(refChar.nation))
	{
		case PIRATE:
			sMessage = xiStr("NewFlagPirate");
			sPerk = "FlagPir";
		break;
		case ENGLAND:
			sMessage = xiStr("NewFlagEngland");
			sPerk = "FlagEng";
		break;
		case SPAIN:
			sMessage = xiStr("NewFlagSpain");
			sPerk = "FlagSpa";
		break;
		case FRANCE:
			sMessage = xiStr("NewFlagFrance");
			sPerk = "FlagFra";
		break;
		case HOLLAND:
			sMessage = xiStr("NewFlagHolland");
			sPerk = "FlagHol";
		break;
	}
	if(!CheckCharacterPerk(pchar, sPerk)) {
		SetCharacterPerk(pchar, sPerk);
		Log_SetStringToLog(sMessage);
	}
}