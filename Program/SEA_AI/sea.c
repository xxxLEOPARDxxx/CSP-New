#include "sea_ai\Script_defines.h"
#include "sea_ai\SeaPeople.h"

#include "sea_ai\AIGroup.c"
#include "sea_ai\AIShip.c"
#include "sea_ai\AIFort.c"
#include "sea_ai\AISea.c"
#include "sea_ai\AICameras.c"
#include "sea_ai\AIAbordage.c"
#include "sea_ai\Cabin.c" //boal
#include "sea_ai\AIFantom.c"
#include "sea_ai\AICannon.c"
#include "sea_ai\AIBalls.c"
#include "sea_ai\AIIsland.c"
#include "sea_ai\AISeaGoods.c"
#include "sea_ai\AITasks\AITasks.c"

#include "sea_ai\ShipBortFire.c"
#include "sea_ai\ShipDead.c"
#include "sea_ai\ShipWalk.c"

#include "sea_ai\CoastFoam.c"

#include "sea_ai\Telescope.c"

#include "battle_interface\BattleInterface.c"


#event_handler("Sea_FirstInit", "Sea_FirstInit");
#event_handler("SeaLoad_GetPointer", "SeaLoad_GetPointer");

#define PLAYER_GROUP	"OurGroup"

string	sCurrentSeaExecute = "execute"; 
string	sCurrentSeaRealize = "realize";

int		iAITemplatesNum;
bool	bSeaActive;
bool	bSeaLoaded = false;
bool 	bSkipSeaLogin = false;
bool	bIslandLoaded = false;
bool	bSeaReloadStarted = false;
bool	bNotEnoughBalls;
bool	bStorm, bTornado;
bool	bSeaQuestGroupHere = false;
bool 	bSeaCanGenerateShipSituation = true; 

int		iStormLockSeconds = 0;

object	Island, IslandReflModel, sLightModel, lighthouseLightModel;
object	Touch, AISea;
object	SeaFader;
object	Seafoam, BallSplash, SinkEffect, PeopleOnShip, Telescope, SeaOperator, Artifact;
object	Sharks;
object	SeaLighter;
object  ShipTracks;

object	SeaLocatorShow;
object	LoginGroupsNow;
bool	bSeaShowLocators = true;
bool	bQuestDisableMapEnter = false;
bool	bFromCoast = false;
bool    bFortCheckFlagYet = false; //eddy. ���� �� ������������� ����� ������

float	SeaMapLoadX = -1570.99;
float	SeaMapLoadZ = 950.812;
float	SeaMapLoadAY = 10.54;

float	fSeaExp = 0.0;
float	fSeaExpTimer = 0.0;

int	iSeaSectionLang = -1;

void DeleteSeaEnvironment()
{
    PauseParticles(true); //fix
	Ship_Walk_Delete();

	StopMusic();
	bSeaActive = false;
	bSeaLoaded = false;

	sCurrentSeaExecute = "execute";
	sCurrentSeaRealize = "realize";

	pchar.Ship.Stopped = true;
	DeleteBattleInterface();

	DelEventHandler(SHIP_BORT_FIRE, "Ship_BortFire");
	DelEventHandler(BALL_FLY_UPDATE, "Ball_OnFlyUpdate");

	SendMessage(&AISea, "l", AI_MESSAGE_UNLOAD);

	DeleteSea();

	DeleteClass(&ShipTracks);

	DeleteClass(&Island);
	DeleteGrass(); // ����� �� ������
	DeleteClass(&IslandReflModel);
	DeleteClass(&Touch);
	DeleteClass(&Seafoam);
	DeleteClass(&BallSplash);
	DeleteClass(&SinkEffect);
	//DeleteClass(&PeopleOnShip);
	DeleteClass(&SeaLocatorShow);
	DeleteClass(&SeaOperator);
	DeleteClass(&Telescope);
	DeleteClass(&Sharks);
	DeleteClass(&sLightModel);

	DeleteClass(&SeaLighter);

	if (IsEntity(&Artifact))
		DeleteClass(&Artifact);

	DeleteBallsEnvironment();
	DeleteCannonsEnvironment();
	DeleteSeaCamerasEnvironment();
	DeleteShipEnvironment();
	DeleteFortEnvironment();
	DeleteAbordageEnvironment();
	DeleteSeaGoodsEnvironment();

	DeleteWeatherEnvironment();

	DeleteCoastFoamEnvironment();

	DeleteAttribute(&AISea,"");

	LayerFreeze(SEA_EXECUTE, true);
	LayerFreeze(SEA_REALIZE, true);

	LayerFreeze("realize", false);
	LayerFreeze("execute", false);

	DeleteClass(&AISea);

	DeleteAnimals();
	
	// delete masts fall modules
		DeleteEntitiesByType("mast");

 	// delete particle system
	//	DeleteParticles();

	// delete our group
		Group_DeleteGroup(PLAYER_GROUP);

	// delete fantom and dead groups
		Group_DeleteUnusedGroup();

	// 
		LanguageCloseFile(iSeaSectionLang); iSeaSectionLang = -1;

	//
		Encounter_DeleteDeadQuestMapEncounters();

}

void CreateSeaEnvironment()
{
	if (IsEntity(&Sea)) { Trace("ERROR: CreateSeaEnvironment Sea Already Loaded!!!"); return; } //fix
	
	sCurrentSeaExecute = SEA_EXECUTE;
	sCurrentSeaRealize = SEA_REALIZE;

	iSeaSectionLang = LanguageOpenFile("SeaSection.txt");

	CreateParticleEntity();

	Ship_Walk_Init();

	LayerFreeze("realize", true);
	LayerFreeze("execute", true);
	LayerCreate("sea_reflection", 1);
	LayerFreeze("sea_reflection", false);
	LayerCreate("sea_reflection2", 1);			// this layer enabled for sea and disabled for abordage
	LayerFreeze("sea_reflection2", false);

	InterfaceStates.Buttons.Resume.enable = true;
	
	bSeaActive = true;

	LayerCreate(SEA_REALIZE, 1);
	LayerSetRealize(SEA_REALIZE, 1);
	LayerCreate(SEA_EXECUTE, 1);
	LayerSetExecute(SEA_EXECUTE, 1);

	LayerFreeze(SEA_EXECUTE, false);
	LayerFreeze(SEA_REALIZE, false);

	CreateSea(SEA_EXECUTE, SEA_REALIZE);			ReloadProgressUpdate();
	CreateWeather(SEA_EXECUTE, SEA_REALIZE);		ReloadProgressUpdate();
	
	CreateEntity(&AISea, "sea_ai");					ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &AISea, 1);
	LayerAddObject(SEA_REALIZE, &AISea, -1);

	CreateEntity(&Touch, "touch");					ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Touch, 1);
	Touch.CollisionDepth = -10.0;
	//LayerAddObject(SEA_REALIZE, &Touch, -1);		// for collision debug

	CreateEntity(&BallSplash, "BallSplash");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &BallSplash, -1);
	LayerAddObject(SEA_REALIZE, &BallSplash, 65535);

	CreateEntity(&SinkEffect, "SINKEFFECT");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &SinkEffect, 65532);
	LayerAddObject(SEA_REALIZE, &SinkEffect, 65532);

	CreateEntity(&ShipTracks, "ShipTracks");		ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &ShipTracks, 100);
	LayerAddObject(SEA_REALIZE, &ShipTracks, 65531);

/*
	CreateEntity(&PeopleOnShip, "PEOPLE_ON_SHIP");	ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &PeopleOnShip, 100);
	LayerAddObject(SEA_REALIZE, &PeopleOnShip, 100);
*/
	CreateEntity(&SeaLocatorShow, "SeaLocatorShow"); ReloadProgressUpdate();
	LayerAddObject(SEA_REALIZE, &SeaLocatorShow, -1);

	/*CreateEntity(&Telescope, "TELESCOPE");			ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Telescope, -1);
	LayerAddObject(SEA_REALIZE, &Telescope, -3);*/
	//TelescopeInitParameters(&Telescope);

	CreateSeaAnimals();								ReloadProgressUpdate();

	// create all other environment
	CreateBallsEnvironment();						ReloadProgressUpdate();
	CreateCannonsEnvironment();						ReloadProgressUpdate();
	CreateSeaCamerasEnvironment();					ReloadProgressUpdate();
	CreateShipEnvironment();						ReloadProgressUpdate();
	CreateFortEnvironment();						ReloadProgressUpdate();
	CreateAbordageEnvironment();					ReloadProgressUpdate();
	CreateSeaGoodsEnvironment();					ReloadProgressUpdate();

	//SetEventHandler(SHIP_CREATE, "Ship_Walk_Create", 0);
	SetEventHandler("MSG_TELESCOPE_REQUEST", "Telescope_Request", 0);
	SetEventHandler(SHIP_BORT_FIRE, "Ship_BortFire", 0);

	bNotEnoughBalls = false;

	Sharks.execute = SEA_EXECUTE;
	Sharks.realize = SEA_REALIZE;
	Sharks.executeModels = 75;
	Sharks.realizeModels = 75;
	Sharks.executeParticles = 78;
	Sharks.realizeParticles = 100001;

	CreateEntity(&Sharks, "Sharks");				ReloadProgressUpdate();

	//PeopleOnShip.isNight = Whr_IsNight();

	// ��� ������ QuestsCheck();
}
// boal -->
string Sea_FindNearColony()
{
	aref aLocators;
	int iNum =  GetAttributesNum(arIslandReload);
	string sColony = "none";

	for(int i = 0; i < iNum; i++)
	{
		aLocators = GetAttributeN(arIslandReload, i);
		if(aLocators.name == sIslandLocator)
		{
			sColony = aLocators.go;
            if(CheckAttribute(&locations[FindLocation(sColony)], "fastreload"))
            {
                sColony = locations[FindLocation(sColony)].fastreload;
                break;
            }
		}
	}
	return sColony;
}
// boal <--
void Sea_LandLoad()
{	
	string sColony = Sea_FindNearColony(); // boal
	int iColony = FindColony(sColony);
	if(bPortPermission && FindColony(Sea_FindNearColony()) != -1 && sti(Colonies[FindColony(Sea_FindNearColony())].nation) != PIRATE && colonies[FindColony(Sea_FindNearColony())].nation != "none" && colonies[FindColony(Sea_FindNearColony())].id != "FortOrange" && colonies[FindColony(Sea_FindNearColony())].id != "LostShipsCity" && pchar.questTemp.sbormoney != Sea_FindNearColony() && sti(pchar.money) < ((sti(GetCharacterShipHP(pchar)) + (sti(GetCrewQuantity(pchar)) * 10) + sti(GetCargoMaxSpace(pchar)))/5))
	{
		Log_Info("������������ ����� �� ������ ��������� �����. ���� ����������.")
		Log_Info("��� ���������� ��� "+ (sti((sti(GetCharacterShipHP(pchar)) + (sti(GetCrewQuantity(pchar)) * 10) + sti(GetCargoMaxSpace(pchar)))/5) - sti(pchar.money)) +" ��������.")
	}
	else
	{
		if(iColony != -1)
		{
			if (CheckAttribute(pchar, "ship.crew.disease"))  // to_do
			{
				if (pchar.ship.crew.disease == "1")
				{
					if (Colonies[iColony].disease != "1" && sti(Colonies[iColony].nation) != PIRATE)
					{
						LaunchDiseaseAlert(DISEASE_ON_SHIP);
						return;
					}
				}
			}
			if(CheckAttribute(&Colonies[iColony], "disease.time"))
			{
				if(sti(Colonies[iColony].disease.time > 0))
				{
					LaunchDiseaseAlert(DISEASE_ON_COLONY);  // to_do
					return;
				}
			}
		}
		pchar.CheckEnemyCompanionType = "Sea_LandLoad"; // ������ ����
   	    if (!CheckEnemyCompanionDistance2GoAway(true)) return; // && !bBettaTestMode  �������� ������ �� ���
    
		bSeaReloadStarted = true;
		PauseAllSounds();
		//ResetSoundScheme();
		ResetSound(); // new

		if (bSeaActive == false) return;
		if (bCanEnterToLand == true)
		{
		    //#20190717-01
        	resetGroupRel();
			LayerFreeze("realize", false);
			LayerFreeze("execute", false);
			Reload(arIslandReload, sIslandLocator, sIslandID);
			ReleaseMapEncounters();
			EmptyAllFantomShips(); // boal
			DeleteAttribute(pchar, "CheckStateOk"); // �������� �����������
			Group_FreeAllDead();
		}
	
		// �������� ���� �� ����� ������������ � ����� (Rasteador)
		// ������ ---->
		if (bPortPermission)
		{
			int sbormoney
			if(iColony != -1 && sti(Colonies[iColony].nation) != PIRATE && colonies[iColony].nation != "none" && colonies[iColony].id != "FortOrange" && colonies[iColony].id != "LostShipsCity") // �� ����� ���� �� �����������, � ��������� ��������, � ��� � � ���� ������
			{
				if(pchar.questTemp.sbormoney != Sea_FindNearColony())
				{
					if(GetNationRelation(sti(Colonies[iColony].nation), sti(pchar.nation)) == RELATION_ENEMY) //Korsar Maxim -  ��������� ��������� �����.
					{
						if(!CheckAttribute(pchar, "Arrive.EnemyPort")) pchar.Arrive.EnemyPort = true; //��� ������������ �� ���������� ����� ������ �������� �� ������.
	/* 					LAi_group_FightGroups(GetNationNameByType(sti(Colonies[iColony].nation)) + "_citizens", LAI_GROUP_PLAYER, true);
						SetNationRelation2MainCharacter(sti(Colonies[iColony].nation), RELATION_ENEMY);
						Log_Info("�������!! ���� � �����!!"); */
						return;
					}
					
					sbormoney = (sti(GetCharacterShipHP(pchar)) + (sti(GetCrewQuantity(pchar)) * 10) + sti(GetCargoMaxSpace(pchar)))/5; // ���� ������� �� ��������� �������, ���������� �������� � ������� �����
					Log_Info("������� �������� ���� � ������� "+ sbormoney +" ��������");
					pchar.money = sti(pchar.money) - sbormoney;
					
					if(GetNationRelation(sti(Colonies[iColony].nation), sti(pchar.nation)) != RELATION_ENEMY)
					{
						if(GetDaysContinueNationLicence(sti(Colonies[iColony].nation)) < 2) //Korsar Maxim -  ��������� ��������� �����. ���� �������� �������, �� �������� �������� ���� ������� �� ��� ���.
						{
							TakeNationLicence(sti(Colonies[iColony].nation));
							GiveNationLicence(sti(Colonies[iColony].nation), 2);
							Log_Info("������� ������� � ����� �� ��� ���.");
						}
					}
				
					pchar.questTemp.taxescount = sti(pchar.questTemp.taxescount) + 1;
				
					// �� ����� ����� ���� ��������� ��� ������
					// �� ��� ���, ���� �� �������� � ������ ����� ��� �� ������ �� ��������
					pchar.questTemp.sbormoney = Sea_FindNearColony();
				}
			}
			// ����� <----
		}
	}
}

void Sea_MapStartFade()
{
	DelEventHandler("FaderEvent_StartFade", "Sea_MapStartFade");
	DeleteSeaEnvironment();
	EmptyAllFantomCharacter(); // ���� ���
	EmptyAllFantomShips();    // ���� �������
	wdmEmptyAllDeadQuestEncounter(); // ���� ��������
	pchar.location = "";
	PGG_DailyUpdate();
	Siege_DailyUpdate();//homo ����� 05/11/06
	wdmUpdateAllEncounterLivetime(); // homo ����� 25/03/07
	Flag_Rerise(); // ����������� ���� ��� ������ �� �����, �������� ��������� ����� � ������� ��
}

void Land_MapStartFade()
{
	DelEventHandler("FaderEvent_StartFade", "Land_MapStartFade");
	//DeleteSeaEnvironment();
	string deckID = pchar.location; /// fix GetShipLocationID(pchar);

	ref loc = &locations[FindLocation(deckID)];

	UnloadLocation(loc);
	EmptyAllFantomShips();
	wdmEmptyAllDeadQuestEncounter(); // ���� ��������
}

void Sea_MapEndFade()
{
	DelEventHandler("FaderEvent_EndFade", "Sea_MapEndFade");
	Partition_SetValue("after");// ����� ������ ���� �� �����
	wdmCreateMap(SeaMapLoadX, SeaMapLoadZ, SeaMapLoadAY);
}

void Sea_MapLoadXZ_AY(float x, float z, float ay)
{
	Sea_MapLoad();

	SeaMapLoadX = x;
	SeaMapLoadZ = z;
	SeaMapLoadAY = ay;
}

void Sea_MapLoad()
{
	// boal 201004 �������� �� �������� � ��� ������� -->
	ref  rPlayer = GetMainCharacter();
    int  i, cn;
    ref  chref;
    bool ok = true;
    //float minShipSpeed = 40; // ��������� ���
    for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(rPlayer,i);
		if( cn>=0 )
		{
			chref = GetCharacter(cn);
            // ������� ������� �� ����� �� �������� �������� -->
            /*r1 = GetSailPercent(chref) / 100.0 * GetCharacterShipSpeedRate(chref);
            if (minShipSpeed > r1)
            {
                minShipSpeed = r1;
            }       */
            // ������� ������� �� ����� �� �������� �������� <--
			if (!GetRemovable(chref)) continue;
			
            if (GetCargoLoad(chref) > GetCargoMaxSpace(chref))
            {
                ok = false;
                Log_SetStringToLog("������� '" +  chref.Ship.Name + "' ����������.");
            }
            if (MOD_SKILL_ENEMY_RATE > 2) // ������ � ���� - �����������
    		{
	            if (i > 0 && GetMinCrewQuantity(chref) > GetCrewQuantity(chref))
	            {
	                ok = false;
	                Log_SetStringToLog("�� ������� '" +  chref.Ship.Name + "' ��� ������������ �������.");
	            }
			}
			
            if (GetMaxCrewQuantity(chref) < GetCrewQuantity(chref))
            {
                ok = false;
                Log_SetStringToLog("�� ������� '" +  chref.Ship.Name + "' �������� ������� ������ �����������.");
            }  
        }
    }
    if (!ok)
    {
        Log_Info("����� �� ����� ����������.");
        PlaySound("knock");
        return;
    }
    // boal 201004 �������� �� �������� � ��� ������� <--
    // ������� ������� �� ����� �� �������� �������� -->
    /*if (minShipSpeed < 1)
	{
		minShipSpeed = 1;
	}
    worldMap.date.hourPerSec = makefloat(12.5 / minShipSpeed * 4.0);  */
    // ������� ������� �� ����� �� �������� �������� <--
    pchar.CheckEnemyCompanionType = "Sea_MapLoad"; // ������ ����
    if (!CheckEnemyCompanionDistance2GoAway(true)) return; // && !bBettaTestMode  �������� ������ �� ���
	LAi_SetAlcoholNormal(pchar);
	LAi_grp_alarmactive = false;
    LAi_grp_playeralarm = 0.0;
    alarmed = 0;
    //#20170530-01
    seaAlarmed = false;
    //#20190717-01
    resetGroupRel();
	bSeaReloadStarted = true;
	PauseAllSounds();

 	//ResetSoundScheme();
	ResetSound(); // new
		
	SetEventHandler("FaderEvent_StartFade", "Sea_MapStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "Sea_MapEndFade", 0);

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "lfl", FADER_OUT, 0.7, true);
	SendMessage(&SeaFader, "l", FADER_STARTFRAME);
	SendMessage(&SeaFader, "ls", FADER_PICTURE, "loading\sea_" + rand(31) + ".tga");

	bSkipSeaLogin = true;

	SeaMapLoadX = stf(pchar.Ship.Pos.x);
	SeaMapLoadZ = stf(pchar.Ship.Pos.z);
	SeaMapLoadAY = stf(pchar.Ship.Ang.y);
}

// ����� �� ���������, ����� ������� ��� ��������
void Land_MapLoad()
{
	bSeaReloadStarted = true;
	PauseAllSounds();

 	//ResetSoundScheme();
	ResetSound(); // new

	SetEventHandler("FaderEvent_StartFade", "Land_MapStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "Sea_MapEndFade", 0);

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "lfl", FADER_OUT, 0.7, true);
	SendMessage(&SeaFader, "l", FADER_STARTFRAME);
	SendMessage(&SeaFader, "ls", FADER_PICTURE, "loading\sea_" + rand(31) + ".tga");

	bSkipSeaLogin = true;

	SeaMapLoadX = stf(pchar.Ship.Pos.x);
	SeaMapLoadZ = stf(pchar.Ship.Pos.z);
	SeaMapLoadAY = stf(pchar.Ship.Ang.y);
}

string	sTaskList[2];

void Sea_FreeTaskList()
{
	ref rMassive; 
	makeref(rMassive, sTaskList);
	SetArraySize(rMassive, 2);
}

void Sea_AddGroup2TaskList(string sGroupID)
{
	ref rMassive; 
	makeref(rMassive, sTaskList);
	int iSize = GetArraySize(rMassive);
	SetArraySize(rMassive, iSize + 1);
	sTaskList[iSize-2] = sGroupID;
}

void Sea_LoginGroupNow(string sGroupID)
{
	LoginGroupsNow.QuestGroups = "";
	aref arGroups; makearef(arGroups, LoginGroupsNow.QuestGroups);
	string sID = "n" + GetAttributesNum(arGroups);
	arGroups.(sID) = sGroupID;
}


void SeaLogin(ref Login)
{
	int		i, j, k, iShipType;
	float	x, y, z, ay;
	ref		rCharacter, rGroup, rEncounter;
	aref	rRawGroup;
	aref	arQCGroups; 
	string	sGName;
	int		iNumQCGroups;
	ref 	rFantom;
	bSeaLoaded = false;
    //#20200408-01
    bAbordageStarted = false;
	Sea.AbordageMode = false;

	int iRDTSC = RDTSC_B();

	// clear load groups now object
	DeleteAttribute(&LoginGroupsNow, "");

	iStormLockSeconds = 0;
	iNumFantoms = 0;
	bSkipSeaLogin = false;
	bSeaReloadStarted = false;
	bSeaQuestGroupHere = false;
	bIslandLoaded = false;

	fSeaExp = 0.0;
	fSeaExpTimer = 0.0;

	Sea_FreeTaskList();	
	
	Encounter_DeleteDeadQuestMapEncounters();

	// weather parameters
	WeatherParams.Tornado = false; 
	WeatherParams.Storm = false; 
	if (CheckAttribute(&Login,"Storm")) { WeatherParams.Storm = Login.Storm; } 
	if (CheckAttribute(&Login,"Tornado")) { WeatherParams.Tornado = Login.Tornado; } 
	bStorm = sti(WeatherParams.Storm);
	bTornado = sti(WeatherParams.Tornado); 
	if (bStorm)
	{
		iStormLockSeconds = 60;
	}

	// Island
	int iIslandIndex = FindIsland(Login.Island);
	//Trace("Island id = " + Login.Island + ", Island index = " + iIslandIndex);
	string sIslandID = "";
	if (iIslandIndex != -1) { sIslandID = Islands[iIslandIndex].id; }
	
	// main character
	pchar.Ship.Stopped = false;
	pchar.Ship.POS.Mode = SHIP_SAIL;
	pchar.location = sIslandID;

	// clear old fantom relations in our character
		if (CheckAttribute(pchar, "Relation"))
		{
			aref	arRelations; makearef(arRelations, pchar.Relation);
			int		iNumRelations = GetAttributesNum(arRelations);
			for (i=0; i<iNumRelations; i++)
			{
				aref arRelation = GetAttributeN(arRelations, i);
				string sRName = GetAttributeName(arRelation);
				if (sti(sRName) >= FANTOM_CHARACTERS)
				{
					DeleteAttribute(arRelations, sRName);
					iNumRelations--;
					i--;
				}
			}
		}

	// Quest check
	Event(EVENT_SEA_LOGIN, "");
	if (bSkipSeaLogin) return;

	// Sea Fader start
	//Boyer add #20170401-02
	pchar.loadscreen = "loading\sea.tga.tx";
	if (!CheckAttribute(&Login,"ImageName")) { Login.ImageName = "loading\sea_" + rand(31) + ".tga"; }

	CreateEntity(&SeaFader, "fader");
	SendMessage(&SeaFader, "lfl", FADER_IN, 0.5, true);
	SendMessage(&SeaFader, "ls", FADER_PICTURE0, Login.ImageName);

	// create all sea modules
	CreateSeaEnvironment();

	// delete our group
	Group_DeleteGroup(PLAYER_GROUP);

	// set commander to group
	Group_SetGroupCommander(PLAYER_GROUP, Characters[nMainCharacterIndex].id);

	// set our group position
	/*if (checkAttribute(pchar, "sneak"))   // to_do del
	{
		Login.PlayerGroup.x = pchar.sneak.x;
		Login.PlayerGroup.z = pchar.sneak.z;
		pchar.sneak.success = 1;
	}*/
	Group_SetXZ_AY(PLAYER_GROUP, stf(Login.PlayerGroup.x), stf(Login.PlayerGroup.z), stf(Login.PlayerGroup.ay) );
	//Trace("Set group : " + PLAYER_GROUP + ", x = " + Login.PlayerGroup.x + ", z = " + Login.PlayerGroup.z + ", ay = " + Login.PlayerGroup.ay);
	// boal -->
	NullCharacter.Login.PlayerGroup.x  = Login.PlayerGroup.x;  // 1.2.3 ������� �������� ����� �� ��� ���������� Group_SetPursuitGroup � ������������ �����
	NullCharacter.Login.PlayerGroup.z  = Login.PlayerGroup.z;
	NullCharacter.Login.PlayerGroup.ay = Login.PlayerGroup.ay;
    pchar.Ship.Pos.x = stf(Login.PlayerGroup.x);
    pchar.Ship.Pos.z = stf(Login.PlayerGroup.z);
    //Log_Info(" x " + pchar.Ship.Pos.x + " z " + pchar.Ship.Pos.z);
    // boal <--
	Sea.MaxSeaHeight = 200;

	ReloadProgressUpdate();

	// login island if exist
	Sea_LoadIsland(sIslandID);
	
	AISea.Island = sIslandID;

	// clear some of group attributes
	for (i=0; i<MAX_SHIP_GROUPS; i++) 
	{
		rGroup = Group_GetGroupByIndex(i);
		if (CheckAttribute(rGroup, "AlreadyLoaded")) 
		{ 
			DeleteAttribute(rGroup, "AlreadyLoaded"); 
		}
	}

	ReloadProgressUpdate();

	// from coast check (move / stop)
	bFromCoast = false;
	if (CheckAttribute(&Login, "FromCoast")) { bFromCoast = sti(Login.FromCoast); }

	// login main player and his friends
	int iCompanionIndex;

	pchar.SeaAI.Group.Name = PLAYER_GROUP;
	pchar.Ship.Type = Characters[nMainCharacterIndex].Ship.Type;
	pchar.Ship.Stopped = false;
	Partition_SetValue("before");// ����� ������
	Ship_Add2Sea(nMainCharacterIndex, bFromCoast, "");
	Group_AddCharacter(PLAYER_GROUP, Characters[nMainCharacterIndex].id);
	//Sea.Sea2.BumpScale = stf(Sea.Sea2.BumpScale) * stf(RealShips[sti(pchar.Ship.Type)].sea_enchantment);
	int iPlayerCompanionsQ = GetCompanionQuantity(pchar);
	if(iPlayerCompanionsQ > 1)
	{
		for (i=1; i<COMPANION_MAX; i++)
		{
			iCompanionIndex = GetCompanionIndex(&Characters[nMainCharacterIndex],i);
			if (iCompanionIndex == -1) 
			{ 
				continue; 
			}
			DeleteAttribute(&Characters[iCompanionIndex], "SeaAI"); // ����� ��� ����� ���� �� �������
			Characters[iCompanionIndex].SeaAI.Group.Name = PLAYER_GROUP;
			Ship_SetTaskNone(PRIMARY_TASK, iCompanionIndex); // ����� ��� ����� ���� �� �������
			Ship_Add2Sea(iCompanionIndex, bFromCoast, "");

			// add companion to player group
			Group_AddCharacter(PLAYER_GROUP, Characters[iCompanionIndex].id);
			//Ship_SetTaskDefendGroup(PRIMARY_TASK, iCompanionIndex, PLAYER_GROUP);
			// to_do ����� ��� �����, � ��� �� ���� � �� ������
			Ship_SetTaskDefend(PRIMARY_TASK, iCompanionIndex, nMainCharacterIndex);
		}
	}
    //SetMaxSeaHeight(sIslandID); // boal ����� � �������
	// set ship for sea camera
	SeaCameras_SetShipForSeaCamera(&pchar);

	// login encounters
	object oResult;
	int iFantomIndex;

	if (sIslandID != "")
	{
		GenerateIslandShips(sIslandID);
	}

	ReloadProgressUpdate();

	// login quest group if island exist
	ReloadProgressUpdate();
	if (sIslandID != "")
	{
		for (i=0; i<MAX_SHIP_GROUPS; i++) 
		{
			rGroup = Group_GetGroupByIndex(i);
			if (!CheckAttribute(rGroup,"AlreadyLoaded")) 
			{ 
				DeleteAttribute(rGroup,"AlreadyLoaded");	
			}

			if (!CheckAttribute(rGroup, "id")) { continue; }
			if (!CheckAttribute(rGroup, "location")) { continue; }
			if (rGroup.location != sIslandID) { continue; }

			Sea_LoginGroup(rGroup.id);
		}
	}

	// login quest groups to sea 
	if (CheckAttribute(&Login, "QuestGroups"))
	{
		arQCGroups; makearef(arQCGroups, Login.QuestGroups);
		iNumQCGroups = GetAttributesNum(arQCGroups);
		for (i=0; i<iNumQCGroups; i++)
		{
			Sea_LoginGroup(GetAttributeValue(GetAttributeN(arQCGroups, i)));
		}
	}

	ReloadProgressUpdate();

	// login quest groups to sea from LoginGroupsNow object
	if (CheckAttribute(&LoginGroupsNow, "QuestGroups"))
	{
		makearef(arQCGroups, LoginGroupsNow.QuestGroups);
		iNumQCGroups = GetAttributesNum(arQCGroups);
		for (i=0; i<iNumQCGroups; i++)
		{
			Sea_LoginGroup(GetAttributeValue(GetAttributeN(arQCGroups, i)));
		}
	}
	
	ReloadProgressUpdate();
		

	//if (!bStorm) //������� �� ���������� ����������
			   
	//{
	// login fantom groups		
	aref arEncounters;
	makearef(arEncounters,Login.Encounters);
	int iNumGroups = GetAttributesNum(arEncounters);

	for (i=0; i<iNumGroups; i++)
	{
		int iAloneCharIndex = -1;

		rRawGroup = GetAttributeN(arEncounters, i);
		rEncounter = GetMapEncounterRef(sti(rRawGroup.type));
		
		if (!CheckAttribute(rEncounter, "RealEncounterType")) // boal �������� �� ����
		{
			//trace("��� �������� �� ������ RealEncounterType, ���������� �");
			continue;
		}		
		int iEncounterType = sti(rEncounter.RealEncounterType);
		//trace ("RealEncounterType is " + iEncounterType);

		x = stf(rRawGroup.x);
		z = stf(rRawGroup.z);
		ay = stf(rRawGroup.ay);

		ReloadProgressUpdate();

		int iCompanionsQ;
		int cn;

		if (iEncounterType == ENCOUNTER_TYPE_ALONE)
		{
			iAloneCharIndex = GetCharacterIndex(rEncounter.CharacterID);
			if (iAloneCharIndex < 0) 
			{ 
				continue; 
			}
			sGName = "Sea_" + rEncounter.CharacterID; //boal ��� �������� ��������������� � �� ������� "EncTypeAlone_" + iAloneCharIndex;
			// ����� ������ ������ �� 10 �������� ��� ����� 4 ���������� - �������� � ���, � ���. � ���� ������ � ��, � ��. ����� ������.

			Group_AddCharacter(sGName, rEncounter.CharacterID);
			
			iCompanionsQ = GetCompanionQuantity(&Characters[iAloneCharIndex]);
			if(iCompanionsQ > 1)
			{
				for(k = 1; k < COMPANION_MAX; k++)
				{
					cn = GetCompanionIndex(&characters[iAloneCharIndex], k);
					if (cn != -1)
					{
						Group_AddCharacter(sGName, characters[cn].id);
					}
				}
			}
			Group_SetGroupCommander(sGName, characters[iAloneCharIndex].id);
			if(GetNationRelation2MainCharacter(sti(characters[iAloneCharIndex].nation)) == RELATION_ENEMY)
			{
				Group_SetTaskAttack(sGName, PLAYER_GROUP);
				Group_LockTask(sGName);
			}
			rEncounter.qID = sGName; // ������� ��� � ������ boal 23/06/06
		}
		else
		{
			sGName = rEncounter.GroupName;
		}
		// check for Quest fantom
		if (CheckAttribute(rEncounter, "qID"))
		{
			Trace("SEA: Login quest encounter " + rEncounter.qID);
			Group_SetAddressNone(rEncounter.qID);
			Group_SetXZ_AY(rEncounter.qID, x, z, ay);
			Sea_LoginGroup(rEncounter.qID);
			
			continue;
		}

		//if (bSeaQuestGroupHere) { continue; }

		Sea_AddGroup2TaskList(sGName);

		//rGroup = Group_GetGroupByIndex(Group_CreateGroup(sGName));
		//rGroup = Group_GetGroupByIndex(Group_FindOrCreateGroup(sGName)); // <--- ��� ��� ��� �������!!!??? :)
		rGroup = Group_FindOrCreateGroup(sGName); // ���� ���
		Group_SetXZ_AY(sGName, x, z, ay);
		Group_SetType(sGName, rEncounter.Type);
		Group_DeleteAtEnd(sGName);

		// copy task attributes from map encounter to fantom group
		if (CheckAttribute(rEncounter, "Task"))							
		{ 
			rGroup.Task = rEncounter.Task; 
		}
		if (CheckAttribute(rEncounter, "Task.Target"))					
		{ 
			rGroup.Task.Target = rEncounter.Task.Target; 
		}
		if (CheckAttribute(rEncounter, "Task.Pos")) 
		{
			rGroup.Task.Target.Pos.x = rEncounter.Task.Pos.x;
			rGroup.Task.Target.Pos.z = rEncounter.Task.Pos.z;
		}
		if (CheckAttribute(rEncounter, "Lock") && sti(rEncounter.Lock)) { Group_LockTask(sGName); }
        // ������� ��� � ������ boal 23/06/06 -->
		/*if (iEncounterType == ENCOUNTER_TYPE_ALONE)
		{
			//Group_SetGroupCommander(sGName, Characters[iAloneCharIndex].id);
			Characters[iAloneCharIndex].SeaAI.Group.Name = sGName;
			Ship_Add2Sea(iAloneCharIndex, 0, rEncounter.Type);

			iCompanionsQ = GetCompanionQuantity(&Characters[iAloneCharIndex]);
			if(iCompanionsQ > 1)
			{
				for(int l = 1; l < COMPANION_MAX; l++)
				{
					cn = GetCompanionIndex(&characters[iAloneCharIndex], l);
					if (cn != -1)
					{
						Characters[cn].SeaAI.Group.Name = sGName;
						Ship_Add2Sea(cn, 0, rEncounter.Type);
					}
				}
			}
			continue;
		} */
		// ������� ��� � ������ boal 23/06/06   <--

		int iNumWarShips = 0;
		int iNumMerchantShips = 0;
		int iNation = PIRATE;
		if(CheckAttribute(rEncounter, "NumWarShips"))
		{
			iNumWarShips = sti(rEncounter.NumWarShips);
		}

		if(CheckAttribute(rEncounter, "NumMerchantShips"))
		{
			iNumMerchantShips = sti(rEncounter.NumMerchantShips);
		}
		if(CheckAttribute(rEncounter, "Nation")) 
		{ 
		iNation = sti(rEncounter.Nation); 
		}

		int iNumFantomShips = Fantom_GenerateEncounterExt(sGName, &oResult, iEncounterType, iNumWarShips, iNumMerchantShips, iNation);
		// Ugeen --> ��������� ����������	��� ���������������
		if (iEncounterType == ENCOUNTER_TYPE_BARREL || iEncounterType == ENCOUNTER_TYPE_BOAT)
		{	
			iFantomIndex = FANTOM_CHARACTERS + iNumFantoms;
			rFantom = &Characters[iFantomIndex];
			rFantom.id = iFantomIndex;
			rFantom.index = iFantomIndex;
			rFantom.Nation = PIRATE;			
			rFantom.EncType  = "pirate";
            rFantom.RealEncounterType = iEncounterType;//boal
			rFantom.reputation = 5 + rand(84);
			rFantom.EncGroupName = sGName;
			rFantom.MainCaptanId = Characters[iFantomIndex].id;
			rFantom.location = sIslandID;
			rGroup.EmptyFantom = true;
			rFantom.sex = "man";
			rFantom.model.animation = "man";			
			SetCaptanModelByEncType(rFantom, rFantom.EncType);
			SetRandomNameToCharacter(rFantom);
			SetSeaFantomParam(rFantom, rEncounter.Type);
			int iRank = sti(pchar.rank) - rand(5) + rand(5);
			if (iRank < 1) iRank = 1;
			SetFantomParamFromRank(rFantom, iRank, false); 
			rFantom.SeaAI.Group.Name = sGName;
			Group_AddCharacter(sGName, rFantom.id);
			Log_TestInfo("Generate Special Encounter");
			EmptyFantom_DropGoodsToSea(rFantom, iEncounterType);			
			continue;
		}
		// <-- Ugeen

        //navy --> 28.12.2009 ��������� ��������� �������� �������� ������� � ����, ����� �� ������ � ����� �������� �� ��������.
        float b, x_mc, z_mc, ay_mc, ay_res, ay_e, z1;
        bool isMChrAttack = false;

        //���������� ��
        x_mc = 	stf(Login.PlayerGroup.x);
        z_mc = 	stf(Login.PlayerGroup.z);
        ay_mc = stf(Login.PlayerGroup.ay);
		
		if(ay_mc < 0) ay_mc = ay_mc + PIm2;
		ay_e = ay;
		if(ay < 0) ay_e = ay_e + PIm2;
		
        //���� ��������������� ������� ����� ��������� � �� �� �����
        ay_res = atan(-((z_mc-z)/(x-x_mc)));

		Trace("ay_res = " + ay_res);		
		
        //�.�. ���������� ���� ������ ������ ����, �� ������� �����
        if (ay_res < 0 && z > z_mc)
        {
            ay_res += PI;
        }

        if (ay_res > 0 && z < z_mc)
        {
            ay_res += PI;
        }
		//Trace("Set group : " + sGName + ", x = " + x + ", z = " + z);
        //���� ���� ����� �������� �� � �������������� �������� ������,
        //�� �������, ��� ������� ��
        if (cos(ay_res - ay_mc) > 0) 
		{
			isMChrAttack = true;
//			Log_TestInfo("�� ������� !");
		}

        if (isMChrAttack)
        {
            //���������� ���� ���������� ���������� �
            if (abs(ay) < PI) k = 1;
            else k = -1;
				
            //��������� ������ ��� �������� z = k * x + b
            b = z - ay_e * x;

            //������� ������� ��������, ����������� �������� ��������� ���������������� ��� ������ �������.
//			z1 = (k * iNumFantomShips * 200 + x) * ay - b;
			//z1 = k * x * ay + b;
			
//            Group_SetXZ_AY(sGName, x, z, ay);
			Trace("Set group new coords : " + sGName + ", x = " + x + ", z = " + z + ", ay_e = " + ay_e + ", b = " + b + ", k = " + k);		
			
        }
		
        //navy <--
		// load ship to sea
		if (iNumFantomShips) 
		{
			for (j=0; j<iNumFantomShips; j++)
			{
				iFantomIndex = FANTOM_CHARACTERS + iNumFantoms - iNumFantomShips + j;
				rFantom = &Characters[iFantomIndex];
                DeleteAttribute(rFantom, "items"); // boal 28.07.04 ���� ���� ������, ����� ���� � ����
				rFantom.id = "fenc_" + iFantomIndex;
                // boal 26.02.2004 -->
				rFantom.location = sIslandID;
				// boal 26.02.2004 <--
				// set commander to group
				if (j==0) { Group_SetGroupCommander(sGName, Characters[iFantomIndex].id); }
				
				// set random character and ship names, face id
				rFantom.sex = "man";
				rFantom.model.animation = "man";
				rFantom.Nation = iNation; //Mett test sti(rEncounter.Nation); 
				// boal �������� � ���� -->
                rFantom.reputation = 5+rand(84);
                rFantom.EncType      = rEncounter.Type; // ���  war, trade pirate
                rFantom.RealEncounterType = iEncounterType;//boal
                rFantom.EncGroupName = sGName;
                rFantom.MainCaptanId = Characters[iFantomIndex - j].id;
				rFantom.WatchFort = true; //������� �� ������
				rFantom.AnalizeShips = true; //��������� ���������� ������� ����� �� � �������� � �����
				if(rand(10) == 1) rFantom.DontRansackCaptain = true;
                if (CheckAttribute(rFantom, "Ship.Mode"))
                {
                	SetCaptanModelByEncType(rFantom, rFantom.Ship.Mode);
                }
                else
                {
                    SetCaptanModelByEncType(rFantom, rEncounter.Type);
                }
                // boal �������� � ���� <--
				
				SetRandomNameToCharacter(rFantom);
				SetRandomNameToShip(rFantom);
				
				SetSeaFantomParam(rFantom, rEncounter.Type); // ��� ���

				if(j == 0 && rFantom.EncType == "pirate")
				{
					rFantom.Flags.Pirate = rand(4);
				}
				
//				trace("rFantom.id = " + rFantom.id + " Ship.pos.x = " + rFantom.Ship.pos.x + " Ship.pos.z = " + rFantom.Ship.pos.z);
//				trace("pchar.Ship.pos.x = " + pchar.Ship.pos.x + " pchar.Ship.pos.z = " + pchar.Ship.pos.z);
				
				trace("bSeaCanGenerateShipSituation = " + bSeaCanGenerateShipSituation);
				
				//ugeen --> ��������� ��������� �������� � ����� ���� ��� �������� - ����� ��� ��������
				if(j != 0 && bSeaCanGenerateShipSituation && iEncounterType != ENCOUNTER_TYPE_ALONE && pchar.CanGenerateShipSituation)  // �������� � �������� ���������
				{
					if (CheckAttribute(rFantom, "hunter")) // ��� ��� ��
					{
						if(rFantom.hunter == "hunter") Fantom_SetQuestSitiation(rFantom, "hunter");
						else Fantom_SetQuestSitiation(rFantom, "pirate");	
					}
					else
					{	
						if(sti(rFantom.Nation) == PIRATE) Fantom_SetQuestSitiation(rFantom, "pirate");	
						else
						{
							if(rFantom.EncType == "trade") // �������� � ������� �������� ���������
							{
								if (CheckAttribute(rFantom, "Ship.Mode") && rFantom.Ship.Mode != "trade")
								{
									Fantom_SetQuestSitiation(rFantom, rFantom.Ship.Mode); // ������� ��������
								}	
							}
							else Fantom_SetQuestSitiation(rFantom, rFantom.EncType); // ������� ������� - ������� � ��.
						}
					}
				}				
				if(bSeaCanGenerateShipSituation && pchar.CanGenerateShipSituation)
				{
					if (iEncounterType == ENCOUNTER_TYPE_MERCHANT_SMALL || iEncounterType == ENCOUNTER_TYPE_MERCHANT_MEDIUM) // � ��� ��� ������� - ������������� ��� �������� �� ������-���� ��������
					{
						Fantom_SetQuestSitiation(rFantom, rFantom.EncType);
					}				
				}	
				// <-- ugeen
				Fantom_SetCannons(rFantom, rEncounter.Type);
				Fantom_SetSails(rFantom, rEncounter.Type);
                // boal <--
				rFantom.SeaAI.Group.Name = sGName;
				rFantom.Experience = 0;
				rFantom.Skill.FreeSkill = 0;

				//rFantom.Features.GeraldSails = false;  // ��� �� �3, ������ �������, �� ��� �������� � Ship_Add2Sea ���� ���� ����������� ���� :)
				//if (CheckAttribute(rEncounter, "GeraldSails")) { rFantom.Features.GeraldSails = sti(rEncounter.GeraldSails); }

				// boal ���� �� ������� -->
				DeleteAttribute(rFantom, "ShipSails.gerald_name");   // ��� ���� � ���� ����
				if (j == 0 || GetCharacterShipClass(rFantom) == 1)
				{
					SetRandGeraldSail(rFantom, sti(rFantom.Nation));
				}
                // boal ���� �� ������� <--
                
				// add fantom
				Group_AddCharacter(sGName, rFantom.id);
				
				// add to sea
				Ship_Add2Sea(iFantomIndex, 0, rEncounter.Type);
			}
		}
	}
	//}
	
	ReloadProgressUpdate();

	// set tasks 2 all groups
	for (i=0; i<GetArraySize(&sTaskList)-2; i++)
	{
		string sGroupID = sTaskList[i];

		rGroup = Group_GetGroupByID(sGroupID);
		
		// set task 
		switch (sti(rGroup.Task))
		{
			case AITASK_RUNAWAY:
				Group_SetTaskRunAway(sGroupID, rGroup.Task.Target);
			break;
			case AITASK_ATTACK:
				Group_SetTaskAttack(sGroupID, rGroup.Task.Target);
			break;
			case AITASK_MOVE:
				if (CheckAttribute(rGroup, "Task.Target.Pos"))
				{
					Group_SetTaskMove(sGroupID, stf(rGroup.Task.Target.Pos.x), stf(rGroup.Task.Target.Pos.z));
				}
				else
				{
					x = 10000.0 * sin(stf(rGroup.Pos.ay));
					z = 10000.0 * cos(stf(rGroup.Pos.ay));
					Group_SetTaskMove(sGName, x, z);
				}
			break;
		}
		if(!CheckAttribute(rGroup,"EmptyFantom"))
		{
			rCharacter = Group_GetGroupCommanderR(rGroup);
			int iRelation = GetRelation(nMainCharacterIndex, sti(rCharacter.index));

		// set relations to all characters in this group
			int qq = 0;
			while (true)
			{
				int iCharacterIndex = Group_GetCharacterIndexR(rGroup, qq); qq++;
				if (iCharacterIndex < 0) { break; }
				SetCharacterRelationBoth(iCharacterIndex, nMainCharacterIndex, iRelation);
			}
		}
	}

	// update AISea 
	AISea.DistanceBetweenGroupShips = 250.0;
	AISea.isDone = "";
	
	InitBattleInterface();							ReloadProgressUpdate();
	StartBattleInterface();							ReloadProgressUpdate();
	RefreshBattleInterface();						ReloadProgressUpdate();
	//Boyer change
	TelescopeInitParameters();

	/*CreateEntity(&SeaOperator, "SEA_OPERATOR");
	LayerAddObject(SEA_EXECUTE, &SeaOperator, -1);
	LayerAddObject(SEA_REALIZE, &SeaOperator, 3);*/

	SendMessage(&Telescope, "leee", MSG_TELESCOPE_INIT_ARRAYS, &Nations, &RealShips, &Goods);

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1);
	
	SetSchemeForSea();								ReloadProgressUpdate();
	sSeaStartMusicName = oldMusicName;

	iRDTSC = RDTSC_E(iRDTSC);
	//Trace("SeaLogin RDTSC = " + iRDTSC);
	//Trace("iNumFantomShips = " + iNumFantomShips);

	pchar.space_press = "0";
	DeleteAttribute(pchar, "SkipEshipIndex");// boal
	
	/*if (checkattribute(pchar, "sneak"))
	{
		string sgroup = pchar.sneak.group;
		LAi_group_NotFightPlayerVSGroup(sgroup);
		deleteAttribute(pchar, "sneak");
	}*/
	
	PostEvent("Sea_FirstInit", 1);
}

void Sea_LoginGroup(string sGroupID)
{
	if (!isEntity(&Sea)) { Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but Sea is not active!"); return; }

	if (Group_FindGroup(sGroupID) < 0)
	{
		Trace("Not find group '" + sGroupID + "' in groups massive, but login try spotted");
		return;
	}

	ref rGroup = Group_GetGroupByID(sGroupID); 
	if (!CheckAttribute(rGroup, "Quest"))			{ Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", but group doesn't contain any quest ships!"); return; }
	if (CheckAttribute(rGroup, "AlreadyLoaded"))	{ Trace("Error: Group sGroupID = " + sGroupID + ", already loaded... check for duplicate group login"); return; }
	if (Group_GetGroupCommanderIndexR(rGroup) < 0)
	{
		Group_DeleteAtEnd(sGroupID);
		return;
	}

	aref arQuestShips; makearef(arQuestShips, rGroup.Quest);

	int iNumQuestShips = GetAttributesNum(arQuestShips);
	if (iNumQuestShips == 0) { return; }

	float x, z, ay; x = 0.0; z = 0.0; ay = 0.0;

	// find group position
	if (CheckAttribute(rGroup, "location") && CheckAttribute(rGroup, "location.group") && rGroup.location != "none")
	{
		string sLocationGroup = rGroup.location.group;
		string sLocationLocator = rGroup.location.locator;

		ref rIsland = GetIslandByID(rGroup.location);

		string sTst = sLocationGroup + "." + sLocationLocator + ".x";
		if (CheckAttribute(rIsland, sTst))
		{
			x = stf(rIsland.(sLocationGroup).(sLocationLocator).x);
			z = stf(rIsland.(sLocationGroup).(sLocationLocator).z);
			ay = stf(rIsland.(sLocationGroup).(sLocationLocator).ay);
		}
		else
		{
			x = 0.0; z = 0.0; ay = 0.0;
			Trace("ERR: Group " + sGroupID + ", Island " + rGroup.location);
			Trace("ERR: Find locators Group " + sLocationGroup + ", Locator " + sLocationLocator);
		}
	}
	else
	{
		if (CheckAttribute(rGroup, "Pos"))
		{
			x = stf(rGroup.Pos.x);
			z = stf(rGroup.Pos.z);
			ay = stf(rGroup.Pos.ay);
		}
		else
		{
			Trace("Error: Sea_LoginGroup sGroupID = " + sGroupID + ", I can't find any locators or position for this group, maybe you can check this???");
		}
	}
    // 1.2.3 - ������������ �����, ������ ���� �  Group_SetPursuitGroup -->
    if (CheckAttribute(rGroup, "location.neargroup"))
	{
  		float fAngle = frnd() * PIm2;
  		ay = 500.0 + rand(300);
  		//Log_testInfo("Group_SetPursuitGroup " + NullCharacter.Login.PlayerGroup.x + " " + NullCharacter.Login.PlayerGroup.z + " " + NullCharacter.Login.PlayerGroup.ay + " fAngle " + fAngle);
  		x  = stf(NullCharacter.Login.PlayerGroup.x) + ay*cos(fAngle); // ���������� ������� 500
  		z  = stf(NullCharacter.Login.PlayerGroup.z) + ay*sin(fAngle);
  		ay = stf(NullCharacter.Login.PlayerGroup.ay) + fAngle;
  		//NullCharacter.Login.PlayerGroup.ay = stf(NullCharacter.Login.PlayerGroup.ay) + frnd() * PI;
	}
	// 1.2.3 - ������������ �����, ������ ���� �  Group_SetPursuitGroup   <--
	// set group position
	Group_SetXZ_AY(sGroupID, x, z, ay);

	// set group commander
	ref rGroupCommander = Group_GetGroupCommander(sGroupID);
	// update commander for SEA AI
	if(sti(rGroupCommander.index) <= 0)
	{
		return;
	}
	Group_SetGroupCommander(sGroupID, rGroupCommander.id);  // �������� �������� � ����������, �� ���� � ����� �����

	// set location near 
	if (CheckAttribute(rGroup, "location.neargroup"))			
	{
		Group_SetPursuitGroup(sGroupID, rGroup.location.neargroup);
	}
	
	// load group ships
	int iNumDeadCharacters = 0;
	for (int i=0; i<iNumQuestShips; i++) //? homo;
	{
		aref arShip;
		
		arShip = GetAttributeN(arQuestShips, i);
		int itmp = GetCharacterIndex(GetAttributeValue(arShip));  // homo fix 29/09/06
		if (itmp != -1)
		{
    		ref rCharacter = GetCharacter(itmp);// bad homo
    		if (!CheckAttribute(rCharacter, "index") || rCharacter.index == "none") // boal for slib
    		{
    			continue;
    		}
    		int iCharacterIndex = sti(rCharacter.index);

    		if(iCharacterIndex <= 0)
    		{
    			continue;
    		}

    		if (LAi_IsDead(rCharacter))
    		{
    			iNumDeadCharacters++; continue;
    		}
    		if (iCharacterIndex == nMainCharacterIndex)
    		{
    			Trace("Error: You assigned main character to quest group... This is a error!");
    			continue;
    		}

    		rCharacter.SeaAI.Group.Name = sGroupID;
    		if (CheckAttribute(rGroup, "location"))
    		{
            	rCharacter.location = rGroup.location;  // ��������� ��� �������
            }
    		Ship_Add2Sea(sti(rCharacter.index), bFromCoast, "");

    		ReloadProgressUpdate();

            // ������� ��� � ������ boal 23/06/06 -->
    		/*int iCompanionsNum = GetCompanionQuantity(rCharacter);
    		//int iGroupIndex = Group_FindGroup(sGroupID);
    		if (iCompanionsNum > 1)
    		{
    			int cn = -1;
    			for(int k = 1; k < COMPANION_MAX; k++)
    			{
    				cn = GetCompanionIndex(rCharacter, k);
    				if(cn != -1)
    				{
    					rCharacter = &characters[cn];

    					rCharacter.SeaAI.Group.Name = sGroupID;

    					Ship_Add2Sea(sti(rCharacter.index), bFromCoast, "");

    					ReloadProgressUpdate();
    				}
    			}
    		} */
    		// <--
        }//<- homo fix
	}

	rGroup.AlreadyLoaded = "";

	if (iNumDeadCharacters == iNumQuestShips)
	{
		Trace("Warn: I am automatic delete group '" + sGroupID +"', because it's empty");
		Group_DeleteAtEnd(sGroupID);
		//Group_DeleteGroup(sGroupID);
		return;
	}

	bSeaQuestGroupHere = true;

	Sea_AddGroup2TaskList(sGroupID);
}

void Sea_FirstInit()
{ 
	bSeaLoaded = true;
	RefreshBattleInterface();
	if( SeaCameras.Camera == "SeaDeckCamera" ) {
		Sailors.IsOnDeck = "1";
	}

	CreateEntity(&Seafoam,"Seafoam");//				ReloadProgressUpdate();
	LayerAddObject(SEA_EXECUTE, &Seafoam, -1);
	LayerAddObject(SEA_REALIZE, &Seafoam, -1);
	if (Whr_IsStorm()) { Seafoam.storm = "true"; }
	
	QuestsCheck(); // boal 26/05/06 ��� ��� �����
}

void Sea_Reload()
{
	DelEventHandler("Sea_Reload", "Sea_Reload");

	object Login;

	Login.PlayerGroup.ay = 0.0;
	Login.PlayerGroup.x = 0.0;
	Login.PlayerGroup.y = 0.0;
	Login.PlayerGroup.z = 0.0;
	Login.Island = pchar.location;

	SeaLogin(&Login);	
}

void Sea_ReloadStart()
{
	if (!bSeaActive) { return; }
	ShipsInit();	
	//characters[1].ship.type = GenerateShip(SHIP_barque, 1);
	DeleteSeaEnvironment();
	SetEventHandler("Sea_Reload", "Sea_Reload", 0);
	PostEvent("Sea_Reload", 1);
}

ref		rSeaLoadResult;
object	oSeaSave;

void Sea_Save()
{
	DeleteAttribute(&oSeaSave, "");

	SendMessage(&AISea, "l", AI_MESSAGE_SEASAVE);
}

// boal -->
float SetMaxSeaHeight(int islandIdx)
{
	if (!bSeaActive) return   6.0; // ������� ����� ��� ����, ��� ��������� pchar.Ship.Pos.x
	if (bStorm) return 200.0;
	string sIslandID = Islands[islandIdx].id;

	float  fMaxViewDist;
    int    i, iQty;
	
	if (CheckAttribute(Islands[islandIdx], "MaxSeaHeight")) return stf(Islands[islandIdx].MaxSeaHeight);

	// ����� ��� ���������� �� ������� �� ������ -->
    //fMaxViewDist = 2000; // �������� �������� ����������
	
	aref arReloadLoc, arLocator;	
	makearef(arReloadLoc, Islands[islandIdx].reload);
	string  sLabel;
	iQty = GetAttributesNum(arReloadLoc); 
    //Log_TestInfo("Sea.MaxSeaHeight " + Sea.MaxSeaHeight);
	for (i=0; i<iQty; i++)
	{
		arLocator = GetAttributeN(arReloadLoc, i);
		sLabel = arLocator.label;

		//���������� �� ���� � ������
		if (findsubstr(sLabel, "Shore" , 0) != -1 || findsubstr(sLabel, "Mayak" , 0) != -1)
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix ������ ��������� � �������, ������ ������ ���� � ������ to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 1500)
					return 6.0;
			}
			else
			{
				trace("Error: �������� ����������� SetMaxSeaHeight ��� " + sLabel);
			}
		}
		//���������� �� �����
		if (findsubstr(sLabel, "Fort" , 0) != -1)  
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix ������ ��������� � �������, ������ ������ ���� � ������ to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 1700)
					return 6.0;
			}
			else
			{
				trace("Error: �������� ����������� SetMaxSeaHeight ��� " + sLabel);
			}				
		}
		//���������� �� �����
		if (findsubstr(sLabel, "Port" , 0) != -1)
		{
			if (CheckAttribute(pchar, "Ship.Pos.x") && CheckAttribute(arLocator, "x"))  // fix ������ ��������� � �������, ������ ������ ���� � ������ to_do
			{
				if (GetDistance2D(stf(pchar.Ship.Pos.x), stf(pchar.Ship.Pos.z), stf(arLocator.x), stf(arLocator.z)) < 2000)
					return 6.0;
			}
			else
			{
				trace("Error: �������� ����������� SetMaxSeaHeight ��� " + sLabel);
			}
		}
	}
    //Log_TestInfo("Sea.MaxSeaHeight Max 200");
	return 200.0;
}
// boal <--
void Sea_LoadIsland(string sIslandID)
{
	bIsFortAtIsland = false;
	if (sIslandID == "") { return; }

	int iIslandIndex = FindIsland(sIslandID);
	if (iIslandIndex != -1 && Islands[iIslandIndex].visible == true)
	{
		// boal -->
		float  fMaxViewDist;
        Sea.MaxSeaHeight = SetMaxSeaHeight(iIslandIndex); // ��� ����� ��� �������� ���� �� �����, ��� ����������� �������� �� ��������, �� �� ��� �� � ����, ��� �����
        Log_TestInfo("Sea_LoadIsland Sea.MaxSeaHeight " + Sea.MaxSeaHeight);
		// boal <--
		CreateEntity(&Island, "Island");
		Island.LightingPath = GetLightingPath();
		Island.ImmersionDistance = Islands[iIslandIndex].ImmersionDistance;			// distance = fRadius * ImmersionDistance, from island begin immersion
		Island.ImmersionDepth = Islands[iIslandIndex].ImmersionDepth;			// immersion depth = (Distance2Camera / (fRadius * ImmersionDistance) - 1.0) * ImmersionDepth
		string sTexturePath = "islands\" + Islands[iIslandIndex].TexturePath + "\";
		SetTexturePath(0, sTexturePath);
		Island.FogDensity = Weather.Fog.IslandDensity;
		// ����� �� ������
		if( CheckAttribute(&Islands[iIslandIndex],"jungle") )
		{
			float fJungleScale = 10.0;
			if( CheckAttribute(&Islands[iIslandIndex],"jungle.scale") )
			{
				fJungleScale = stf(Islands[iIslandIndex].jungle.scale);
			}
			CreateGrass(GetResourceDirectory() + "models\islands\"+ Islands[iIslandIndex].id +"\"+ Islands[iIslandIndex].jungle.patch + ".grs", "Grass\"+Islands[iIslandIndex].jungle.texture+".tga.tx", fJungleScale, 20.0, 200.0, 100.0, 1000.0, 0.6);
		}
		/*if (MOD_BETTATESTMODE == "On")
		{
			CreateEntity(&SeaLighter, "lighter");  //eddy. �� ���� ��� ���� ���������, ��� � ���� Lighter. ������ ����, ���� � ���������� ������� == 0, �.�. � ���� ������ ����� �� �������� � ������.
		}*/
		SendMessage(&SeaLighter, "ss", "ModelsPath", Islands[iIslandIndex].filespath.models);
		SendMessage(&SeaLighter, "ss", "LightPath", GetLightingPath());

		SendMessage(&Island, "lsss", MSG_ISLAND_LOAD_GEO, "islands", Islands[iIslandIndex].filespath.models, Islands[iIslandIndex].model);
		LayerAddObject(SEA_REALIZE, &Island, 4);
		LayerAddObject("mast_island_trace", &Island, 1);
		LayerAddObject("sun_trace", &Island, 1);
		fMaxViewDist = 6000.0;
		if(CheckAttribute(&Islands[iIslandIndex], "maxviewdist"))
		{
			fMaxViewDist = stf(Islands[iIslandIndex].maxviewdist);
		}
		SendMessage(&Island, "lf", MSG_MODEL_SET_MAX_VIEW_DIST, fMaxViewDist);

		CreateEntity(&IslandReflModel, "MODELR");
		string sReflModel = Islands[iIslandIndex].filespath.models + "\" + Islands[iIslandIndex].refl_model;
		SendMessage(&IslandReflModel, "ls", MSG_MODEL_SET_LIGHT_PATH, GetLightingPath());
		SendMessage(&IslandReflModel, "ls", MSG_MODEL_LOAD_GEO, sReflModel);
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
		LayerAddObject("sea_reflection2", &IslandReflModel, -1);
		SendMessage(&SeaLighter, "ssi", "AddModel", Islands[iIslandIndex].refl_model, &IslandReflModel);
		//--> eddy. �� ����� ���� �� �����
		//if(CheckAttribute(Islands[iIslandIndex], "mayak"))
		//{
		//	CreateEntity(&sLightModel, "MODELR");
		//	string sMayakLightModel;
		//	if (isDay()) sMayakLightModel = Islands[iIslandIndex].filespath.models + "\" + Islands[iIslandIndex].mayak.model_day;
		//	else sMayakLightModel = Islands[iIslandIndex].filespath.models + "\" + Islands[iIslandIndex].mayak.model_night;
		//	//SendMessage(&sLightModel, "ls", MSG_MODEL_SET_TECHNIQUE, "LocVisRays");
		//	SendMessage(&sLightModel, "ls", MSG_MODEL_LOAD_GEO, sMayakLightModel);
		//	SendMessage(&Island, "li", MSG_ISLAND_ADD_FORT,  &sLightModel);
		//	SendMessage(SeaLighter, "ssi", "AddModel", Islands[iIslandIndex].mayak.model_night, &sLightModel);
		//}
		//<-- eddy. �� ����� ���� �� �����
		// Warship ����� � ����� - �������� ��������� �����
		Sea_CreateLighthouse(sIslandID);
		bIslandLoaded = true;
		SendMessage(&SeaLocatorShow, "a", &Islands[iIslandIndex]);
		Fort_Login(iIslandIndex);	
		SetTexturePath(0, "");

		CreateCoastFoamEnvironment(sIslandID, SEA_EXECUTE, SEA_REALIZE);
		//eddy. ������� � ���������� ���������� �����
		aref arReloadFort;	
		makearef(arReloadFort, Islands[iIslandIndex].reload.l2);
		if (!CheckAttribute(arReloadFort, "colonyname")) return;
		string sTest = arReloadFort.colonyname + " Fort";
		if (arReloadFort.label == sTest && CheckAttribute(arReloadFort, "x") && CheckAttribute(arReloadFort, "z"))
		{
			fFort_x = stf(arReloadFort.x);
			fFort_z = stf(arReloadFort.z);
			int iColony = FindColony(arReloadFort.colonyname);
			iFortNation = sti(colonies[iColony].nation);
			iFortCommander = sti(colonies[iColony].commanderIdx);
			//������� �� ������ ������, ���� �� ���
			if (!CheckAttribute(&characters[iFortCommander], "Fort.Mode") || sti(characters[iFortCommander].Fort.Mode) != FORT_DEAD)
			{
				bIsFortAtIsland = true; 
			}
		}
	}
}

// Warship ����� �� �������� ��������� ������ � ����
void Sea_CreateLighthouse(String _islandID)
{
	ref islandRef;
	int islandIndex = FindIsland(_islandID);
	
	String lighthouseLightModelName;
	
	if(islandIndex == -1) return;
	
	islandRef = &Islands[islandIndex];

	//--> eddy. �� ����� ���� �� �����
	if(CheckAttribute(&islandRef, "mayak"))
	{
		CreateEntity(&sLightModel, "MODELR");
		
		if(isDay())
		{
			lighthouseLightModelName = islandRef.filespath.models + "\" + islandRef.mayak.model_day;
		}
		else
		{
			lighthouseLightModelName = islandRef.filespath.models + "\" + islandRef.mayak.model_night;
		}
		
		//SendMessage(&sLightModel, "ls", MSG_MODEL_SET_TECHNIQUE, "LocVisRays");
		SendMessage(&sLightModel, "ls", MSG_MODEL_LOAD_GEO, lighthouseLightModelName);
		SendMessage(&island, "li", MSG_ISLAND_ADD_FORT,  &sLightModel); // &island - ������-������ (��������), � �� ������� ������� Islands[]
		SendMessage(SeaLighter, "ssi", "AddModel", islandRef.mayak.model_night, &sLightModel);
	}
	//<-- eddy. �� ����� ���� �� �����
	
	// Warship ����� - �������� ����� ����� -->
	// ������� ����� � ������� ��� �� ����������� - �� ���� ������ � ����� ������
	if(_islandID == "Jamaica" || _islandID == "Cuba1" || _islandID == "Cuba2")
	{
		if(IsEntity(lighthouseLightModel))
		{
			DeleteClass(&lighthouseLightModel);
		}
		
		if(!IsDay())
		{
			CreateEntity(&lighthouseLightModel, "MODELR");
			// ������� - �������� ��� �������� ����� ������� �� "RESOURCE\TEXTURES\" + DIRPATH � ����� ��� �� ��������� :(
			// � �����, �������� ������ ������ � ��� �� �����, ��� � ������, ������ � �������� "TEXTURES"
			//SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_SET_DIRPATH, "");
			SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_LOAD_GEO, "lighthouse_volumeLight");
			SendMessage(&lighthouseLightModel, "ls", MSG_MODEL_SET_TECHNIQUE, "LighthouseLight");
			LayerAddObject(SEA_EXECUTE, &lighthouseLightModel, ITEMS_LAYER);
			LayerAddObject(SEA_REALIZE, &lighthouseLightModel, ITEMS_LAYER);
			
			if(_islandID == "Jamaica")
			{
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, 3000.0, 24.5, -1679.1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
			
			if(_islandID == "Cuba1")
			{
				// TO_DO ��������� ��� - ����� ������
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, 627.0, 24.0, -2170.5, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
			
			if(_islandID == "Cuba2")
			{
				SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION, -413.0, 65.5, 815.1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
			}
		}
	}
	// <-- �������� ����� �����
}
bool bSeaLoad = false;

void Sea_Load()
{
	bSeaLoad = true;

	CreateSeaEnvironment();

	// login island if exist
	Sea_LoadIsland(AISea.Island);

	SendMessage(&AISea, "l", AI_MESSAGE_SEALOAD);
	SendMessage(&Telescope, "leee", MSG_TELESCOPE_INIT_ARRAYS, &Nations, &RealShips, &Goods);

	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1);
	
	SetSchemeForSea();

	PostEvent("Sea_FirstInit", 1);
	
	// clear save attribute
	DeleteAttribute(&oSeaSave, "");
	bSeaLoad = false;

	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();
	//#20190205-01
    SeaCameras_SetShipForSeaCamera(&pchar);
}

ref SeaLoad_GetPointer()
{
	string sType = GetEventData();
	int iIndex = GetEventData();

	switch (sType)
	{
		case "character":
			makeref(rSeaLoadResult, Characters[iIndex]);
		break;
		case "ship":
			makeref(rSeaLoadResult, RealShips[iIndex]);
		break;
		case "seacameras":
			makeref(rSeaLoadResult, SeaCameras);
		break;
		case "seasave":
			makeref(rSeaLoadResult, oSeaSave);
		break;
	}
	return rSeaLoadResult;
}
//#20190424-02
void ReconnectShips()
{
    if (bSeaActive && !IsEntity(&Characters[nMainCharacterIndex])) {
        aref refObj;
        int tmp;
        if(GetEntity("SEA_REALIZE", &refObj))
        {
            while(true)
            {
                if(GetEntityName(&refObj)=="SHIP")
                {
                    tmp = -1;
                    SendMessage(&refObj, "le", MSG_SHIP_GET_CHARACTER_INDEX, &tmp);
                    if(tmp > -1 && !IsEntity(&Characters[tmp])) {
                        ReconnectEntity(&Characters[tmp], refObj);
                    }
                }
                if(!GetEntityNext(&refObj)) break;
            }
        }
	}
}
