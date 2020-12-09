#ifndef SEA_AI_SCRIPT_DEFINES
#define SEA_AI_SCRIPT_DEFINES

#define SEA_EXECUTE					"sea_execute"
#define SEA_REALIZE					"sea_realize"

//
#define SEA_GET_LAYERS				"SeaGetLayers"

//
#define EVENT_SEA_LOGIN				"EventSeaLogin"

// Abordage Section
#define	ABORDAGE_CAN_BE				"AbordageCanBe"

// Weather Section
#define WEATHER_LIGHTNING			"WhrLightning"
#define WEATHER_CALC_FOG_COLOR		"WhrCalcFogColor"

// Bort Section
#define SHIP_BORT_FIRE				"Ship_Bort_Fire"

// Balls Section
#define BALL_FORT_HIT				"Ball_FortHit"
#define BALL_WATER_HIT				"Ball_WaterHit"
#define BALL_ISLAND_HIT				"Ball_IslandHit"
#define BALL_FLY_UPDATE				"Ball_FlyUpdate"
#define BALL_FLY_NEAR_CAMERA		"Bll_FlyNCam"

// Group section
#define GROUP_CHECKTASKEVENT		"GrpChkTsk"
//#20181103-02
#define GROUP_REMOVEEVENT			"GrpRemovedEvt"
#define GROUP_CMDCHGEVENT			"GrpCmdChgEvt"

// Ship section
#define SHIP_DEAD						"ShpDead"
#define SHIP_CREATE						"ShpCreate"
#define SHIP_DELETE						"ShpDelete"
#define SHIP_FIRE_DAMAGE				"ShpFDamage"
#define SHIP_TO_STRAND					"Shp2Strand"
#define SHIP_TO_STRAND_NEXT				"Shp2StrandNext"
#define SHIP_MAST_DAMAGE				"ShpMastDamage"
#define SHIP_SAIL_DAMAGE				"ShpSailDamage"
#define SHIP_HULL_HIT					"Shp_HullHit"
#define SHIP_SHIP2ISLAND_COLLISION		"Shp_ShipIslColl"
#define SHIP_SHIP2SHIP_COLLISION		"Shp_Ship2ShipColl"
#define SHIP_GET_CURRENT_BALLS_NUM		"Shp_GetCurBallsNum"
#define SHIP_NOT_ENOUGH_BALLS			"Shp_NotEnoughBalls"
#define SHIP_CHECK_SITUATION			"Shp_ChkSituation"
#define SHIP_UPDATE_PARAMETERS			"Shp_UpdParams"
#define SHIP_CHANGE_CHARGE				"ShpChCharge"
#define SHIP_CHECK_RELOAD_ENABLE		"ShpChkReloadEnable"
#define SHIP_FIRE_ACTION				"ShpFireAction"
#define SHIP_EAT_SWIM_GOOD				"ShpEatSwimGood"
#define SHIP_GET_BORT_FIRE_DELTA		"ShpGetBortFireDelta"
#define SHIP_BRANDER_DETONATE			"ShpBrndrBoom"
#define SHIP_ACTIVATE_FIRE_PLACE		"ShpActFirePlace"
#define SHIP_CREATELOADSHIP				"Shp_LoadShp"
#define SHIP_LOAD_SHIPACTIVATEFIREPLACE	"Shp_LoadActFirePlace"
#define SHIP_DROP_GOOD					"Shp_DropGoodsToSea"
#define SHIP_GET_RUNAWAY_POINT			"Shp_GetRunawayPnt"
#define SHIP_BORT_RELOADED				"Shp_BortReloaded"
#define SHIP_TASK_COMPLETE				"Shp_TaskComplete"

#define SHIP_MAST_TOUCH_ISLAND		0
#define SHIP_MAST_TOUCH_SHIP		1
#define SHIP_MAST_TOUCH_BALL		2

// Fort Section
#define FORT_NORMAL					0
#define FORT_ABORDAGE				1
#define FORT_DEAD					2

#define SHIP_ABORDAGE				3

#define FORT_CREATE					"FortCreate"
#define FORT_DELETE					"FortDelete"
#define FORT_CANNON_DAMAGE			"FortCDamage"
#define FORT_LOADDMGCANNON		"FortLdDmgCann"

// Cannon Section
#define CANNON_RECALCULATE_PARAMETERS	"CannReCaclParam"
#define CANNON_GET_RECHARGE_TIME		"CannGRTime"
#define CANNON_GET_FIRE_TIME			"CannGFTime"
#define CANNON_FIRE						"CannFire"
#define CANNON_GET_FIRE_HEIGHT			"CannGFHeight"
#define CANNON_UNLOAD					"CannUnload"
#define CANNON_LOAD						"CannLoad"
#define CANNON_DAMAGE					"CannDamage"

// AI Section

// Nation section
//Boyer fix #20170318-46
#define RELATION_UNKNOWN		-1
#define RELATION_FRIEND			0
#define RELATION_NEUTRAL		1
#define RELATION_ENEMY			2
#define RELATION_ALLIANCE		3

#define AI_ALL					10000
#define AI_SELECT				10010
#define AI_ANY					10020
#define AI_WEAKEST_WAR			10030
#define AI_STRONGEST_WAR		10040
#define AI_WEAKEST_TRADE		10050
#define AI_STRONGEST_TRADE		10060

#define AI_RUNAWAY				20000
#define AI_RUNAWAY_ALL			20010
#define AI_ATTACK_HULL			20020
#define AI_ATTACK_RIG			20030
#define AI_ATTACK_DECK			20040
#define AI_ABORDAGE				20050
#define AI_DEFEND_TRADE			20060
#define AI_DEFEND_WAR			20070

#define AI_ABORDAGE_SUCCESS		30000
#define AI_KILL_SUCCESS			30010
#define AI_SAIL_STATE			30020
#define AI_PEOPLE_STATE			30030
#define AI_HULL_STATE			30040

// define AI tasks
#define AITASK_NONE				-1
#define AITASK_DRIFT			0
#define AITASK_ATTACK			1
#define AITASK_FOLLOW			2
#define AITASK_DEFEND			3
#define AITASK_DEFEND_GROUP		4
#define AITASK_ABORDAGE			5
#define AITASK_RUNAWAY			6
#define	AITASK_MOVE				7
#define	AITASK_BRANDER			8
//#20190313-01
#define AITASK_ABORDAGE_MULTI	9

// define AI tasks priority
#define PRIMARY_TASK			0
#define SECONDARY_TASK			1

// define AI messages
#define AI_MESSAGE_SET_CANNON_ATTRIBUTE				51000
#define AI_MESSAGE_ADD_SHIP							51001
#define AI_MESSAGE_CANNON_FIRE						51002
#define AI_MESSAGE_CANNON_RELOAD					51003
#define AI_MESSAGE_SET_CAMERAS_ATTRIBUTE			51004
#define AI_MESSAGE_ADD_FORT							51005
#define AI_MESSAGE_ADD_AI_TEMPLATE					51007
#define AI_MESSAGE_FORT_HIT							51008
#define AI_MESSAGE_GROUP_SET_TASK					51009	// "lss" AI_MESSAGE_GROUP_SET_ATTACK, TASK_COMMAND, GroupName, AttakinGroupName
#define AI_MESSAGE_GROUP_SET_XYZ_AY					51010	// "lsffff" AI_MESSAGE_GROUP_SET_XYZ_AY, GroupName, x, y, z, ay
#define AI_MESSAGE_SHIP_SET_TASK					51011
#define AI_MESSAGE_SHIP_CHANGE_GROUP				51012
#define AI_MESSAGE_SET_OFFICER_2_SHIP				51013
#define AI_MESSAGE_SWAP_SHIPS						51014
#define AI_MESSAGE_SET_LAYERS						51015
#define AI_MESSAGE_UPDATE_RELATIONS					51016
#define AI_MESSAGE_SAIL_2_CHARACTER					51017
#define AI_MESSAGE_SAIL_2_LOCATOR					51018
#define AI_MESSAGE_GROUP_SET_LOCATION_OTHER_GROUP	51019
#define AI_MESSAGE_GROUP_SET_TYPE					51020
#define AI_MESSAGE_SHIP_SET_SAIL_STATE				51021
#define AI_MESSAGE_GROUP_SET_COMMANDER				51022
#define AI_MESSAGE_SHIP_GET_ATTACK_HP				51023
#define AI_MESSAGE_GROUP_GET_ATTACK_HP				51024
#define AI_MESSAGE_UNLOAD							51025
#define AI_MESSAGE_CHARACTER_DEAD					51026
#define AI_MESSAGE_GET_RELATION						51027
#define AI_MESSAGE_SET_COMPANION_ENEMY				51028
#define AI_MESSAGE_CANNONS_BOOM_CHECK				51040
#define AI_MESSAGE_CANNONS_PARAMS					51041
#define AI_MESSAGE_SEASAVE							51042
#define AI_MESSAGE_SEALOAD							51043
#define AI_MESSAGE_FORT_SET_LIGHTS					51044
#define AI_MESSAGE_FORT_UNSET_LIGHTS				51045
#define AI_MESSAGE_RESEARCH_CANNONS					51050  // boal 08.08.06 метод пересчета орудий на корабле SendMessage(&AISea, "la", AI_MESSAGE_RESEARCH_CANNONS, aCharacter)
//#20181027-02
#define AI_MESSAGE_FORT_RESETISLAND					51055
//#20181102-02
#define AI_MESSAGE_CHARACTER_REMOVE					51060
#define AI_MESSAGE_GROUP_GET_COMMANDER				51065
//#20190701-01
#define AI_MESSAGE_GROUP_GET_POWERABS				51066
#define AI_MESSAGE_GROUP_GET_POWERREL				51067
#define AI_MESSAGE_GROUP_GET_POWERGRP				51068
#define AI_MESSAGE_GROUP_FIND_CLOSE					51069
//#20190210-01
#define AI_MESSAGE_RESET_CAMERAS_ATTRIBUTE			51070

//#20180112-01 Group mod for multiple squadron lines
#define AI_MESSAGE_GROUP_SET_LINES					51080
//#20181027-02
#define AI_MESSAGE_GROUP_ADJ_XYZ_AY					51081

// cameras
#define AI_CAMERAS_ADD_CAMERA					55000
#define AI_CAMERAS_SET_CAMERA					55001
//#20181027-02
#define AI_CAMERAS_RESETISLAND					55010

#endif
