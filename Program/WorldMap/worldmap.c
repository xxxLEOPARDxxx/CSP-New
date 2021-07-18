/*
	Programm interface:

	Init world map in start
		void wdmInitWorldMap();
	Create world map object
		void wdmCreateMap();
	Release world map object
		void wdmReleaseMap();


	SPI (Script program interface):
	��������� ������ �� �����
	(const) ���� ������ ��� ���������
	(var) ���� ������ ��� ������ � ���������, ������ � ��� �������� � ���������� ��������� �����,
	      ������������� ���� ������

	������
	worldMap.storm.num - ������� ���������� ������� � ����� (const)
	worldMap.storm.cur - ������ �������� ������ 0..num-1, ���� �������������� ��� ���������� ����� (var)
	worldMap.storm.x - ������� ������ �� x (const)
	worldMap.storm.z - ������� ������ �� z (const)
	worldMap.storm.time - ���������� ����� ����� � �������� (const)

	��������� �������
	worldMap.encounter.num - ������� ���������� ���������� � ����� (const)
	worldMap.encounter.cur - ������ �������� ��������� � ����� (var)
	worldMap.encounter.x - ������� ��������� �� x (const)
	worldMap.encounter.z - ������� ��������� �� z (const)
	worldMap.encounter.time - ���������� ����� ����� � �������� (const)
	worldMap.encounter.type - ��� �������, ������������ ���� ���������� (define � ������� ����� �����������)
	worldMap.encounter.attack - ������ ���������, ������� ������� (���� �� �����)
	worldMap.encounter.id - �������� �������� ����������: worldMap.encounters.(worldMap.encounter.id)...

	������ ����������
	worldMap.info.playerInStorm - ���� 1 �� ����� ���������� � ������
	worldMap.info.updateinfo - ������ ����������


	//��������� ���������� - !!!���������, �� ����� ��������!!!
	worldMap.enemyshipViewDistMin;		//��������� �� ������� ������� �������� ��������
	worldMap.enemyshipViewDistMax;		//��������� �� ������� ������� �������� ���������
	worldMap.enemyshipDistKill;			//���������� �� ������� ������� �������
	worldMap.enemyshipBrnDistMin;		//����������� ��������� �� ������� �������� �������
	worldMap.enemyshipBrnDistMax;		//������������ ��������� �� ������� �������� �������

	worldMap.stormViewDistMin;			//��������� �� ������� ����� �������� ��������
	worldMap.stormViewDistMax;			//��������� �� ������� ����� �������� ���������
	worldMap.stormDistKill;				//���������� �� ������� ������� �����
	worldMap.stormBrnDistMin;			//����������� ��������� �� ������� �������� �����
	worldMap.stormBrnDistMax;			//������������ ��������� �� ������� �������� �����

*/

#include "worldmap\worldmap_globals.c"
#include "worldmap\worldmap_events.c"
#include "worldmap\worldmap_reload.c"
#include "worldmap\worldmap_encgen.c"
#include "worldmap\worldmap_coords.c"


//=========================================================================================


#event_handler("WorldMap_EncounterCreate", "wdmEvent_EncounterCreate");
#event_handler("WorldMap_PlayerInStorm", "wdmEvent_PlayerInStorm");
#event_handler("WorldMap_ShipEncounter", "wdmEvent_ShipEncounter");
#event_handler("WorldMap_UpdateDate", "wdmEvent_UpdateDate");
#event_handler("ExitFromWorldMap", "wdmReloadToSea");
//#event_handler("NextDay", "wdmNextDayUpdate");

#event_handler("EventTimeUpdate", "wdmTimeUpdate");


//=========================================================================================
// Programm interface
//=========================================================================================


void wdmCreateMap(float x, float z, float ay)
{
	//���������� ������� � �������� ������
	float zeroX = MakeFloat(worldMap.zeroX);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float ShipX, ShipZ;
	//������� ������ ���������� �� �����
	int scale = WDM_MAP_TO_SEA_SCALE;
	if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina" 
		|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
		|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
	{
		scale = 25;
	}
	shipX = (x/scale) + zeroX;
	shipZ = (z/scale) + zeroZ;
	worldMap.playerShipX = (x/scale) + zeroX;
	worldMap.playerShipZ = (z/scale) + zeroZ;
	worldMap.playerShipAY = ay;
//	trace(" X :" + x + " Z :" + z + " scale :" + scale + " ZeroX :" + zeroX + " ZeroZ:" + zeroZ + " WDMShipX:"+worldMap.playerShipX + " WDMShipZ:" + worldMap.playerShipZ + " ShipX:" + ShipX + " ShipZ:" + ShipZ);
	//��������� �����
	wdmCreateWorldMap();
}

void wdmTimeUpdate()
{
	//QuestsTimeCheck();
	// boal -->
	QuestsCheck();
	PostEvent("EventTimeUpdate", 5000);
	// boal <--
}

void wdmCreateWorldMap()
{
    float fHtRatio = stf(Render.screen_y) / screenscaling;
	wdmLockReload = false;
	//����� ��� ��������� ��� ������
	ClearAllLogStrings();
	//
	ReloadProgressStart();
	//����������� ����� �������
	worldMap.date.monthnames.m01 = XI_ConvertString("target_month_1");
	worldMap.date.monthnames.m02 = XI_ConvertString("target_month_2");
	worldMap.date.monthnames.m03 = XI_ConvertString("target_month_3");
	worldMap.date.monthnames.m04 = XI_ConvertString("target_month_4");
	worldMap.date.monthnames.m05 = XI_ConvertString("target_month_5");
	worldMap.date.monthnames.m06 = XI_ConvertString("target_month_6");
	worldMap.date.monthnames.m07 = XI_ConvertString("target_month_7");
	worldMap.date.monthnames.m08 = XI_ConvertString("target_month_8");
	worldMap.date.monthnames.m09 = XI_ConvertString("target_month_9");
	worldMap.date.monthnames.m10 = XI_ConvertString("target_month_10");
	worldMap.date.monthnames.m11 = XI_ConvertString("target_month_11");
	worldMap.date.monthnames.m12 = XI_ConvertString("target_month_12");
	worldMap.date.font = "normal";
	worldMap.showFlag.count = 10;
	worldMap.showFlag.texture = "flagallWDM" + iFlagAllWdm + ".tga";  //path to texture if not in root: "WorldMap\Interfaces\texturename.tga.tx"
	//#20200226-03
	worldMap.outputRum = true;			   
	worldMap.resizeRatio = fHtRatio;
	//������ ��� ���������� ����������
	wdmRemoveOldEncounters();
//	Trace("Save check ---------------================--------------")
//	DumpAttributes(&worldMap);
//	Trace("Save check ###########----================--------------")
	worldMap.playerInStorm = "0";
	//������� �������� ��������� �����������
	wdmReset();
	//������ �����
	CreateEntity(&worldMap,"worldmap");
	worldMap.isLoaded = "true";
	//��������� ���������
	worldMap.update = "";
	//������
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeInTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_IN, fadeInTime, true);
	SendMessage(&wdm_fader, "ls",FADER_PICTURE0,"loading\sea_" + rand(31) + ".tga");
	//��������� �������� �����
	SetSchemeForMap();
	//�������, ��� �����������
	PostEvent("EventWorldMapInit", 830); //fix boal
	ReloadProgressEnd();
	PostEvent("EventTimeUpdate", 1000);	
	//������ ������������ ��������� ����������
	worldMap.addQuestEncounters = "updateQuest";
	InitWmInterface();
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation)); //Zero based array
}

void wdmLoadSavedMap()
{
	//��������� �����
	wdmCreateWorldMap();
}

void wdmRemoveOldEncounters()
{
	//������� ��������� ����������
	wdmMarkDeleteEncounters();
	//�������� ���� ��������
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	object forDelete;
	string attr, encID;
	int count = 0;
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "needDelete") != 0)
		{
			attr = "del" + count;
			forDelete.(attr) = GetAttributeName(enc);
			count = count + 1;
		}
	}
	for(i = 0; i < count; i++)
	{
		attr = "del" + i;
		encID = "encounters." + forDelete.(attr);
		DeleteAttribute(&worldMap, encID);
	}
}

float wdmGetDays(int year, int month, int day, int hour)
{
	//������� ��� �� �����
	if(year < 0) year = 0;
	if(year > 3000) year = 3000;
	year = year*365;
	//������� ����� ���
	for(int i = 1; i < month; i++)
	{
		day = day + GetMonthDays(i, year);
	}
	//������� ������ ���
	float days = year + day + (hour/24.0);
	return days;
}

void wdmMarkDeleteEncounters()
{
	//�������� ����
	int year = sti(worldMap.date.year);
	int month = sti(worldMap.date.month);
	int day = sti(worldMap.date.day);
	int hour = sti(worldMap.date.hour);
	float days = wdmGetDays(year, month, day, hour);
	int encYear, encMonth, encDay, encHour;
	//���������� ��� ����������, ������� �� ��������
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "Quest") != 0)
		{
			continue;
		}
		bool deleteMe = false;
		if(CheckAttribute(enc, "year") != 0)
		{
			encYear = sti(enc.year);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "month") != 0)
		{
			encMonth = sti(enc.month);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "day") != 0)
		{
			encDay = sti(enc.day);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "hour") != 0)
		{
			encHour = sti(enc.hour);
		}else{
			deleteMe = true;
		}
		if(deleteMe != true)
		{
			float deltaDays = wdmGetDays(encYear, encMonth, encDay, encHour) - days;
			if(deltaDays < 0)
			{
				deltaDays = -deltaDays;
			}
			if(deltaDays > 1.0)
			{
				deleteMe = true;
			}
		}
		if(deleteMe != false)
		{
			enc.needDelete = "Time delete";
		}
	}
}
