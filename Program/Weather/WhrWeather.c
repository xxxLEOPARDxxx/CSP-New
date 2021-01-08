#include "weather\WhrUtils.c"
#include "weather\WhrLightning.c"
#include "weather\WhrRain.c"
#include "weather\WhrSea.c"
#include "weather\WhrSky.c"
#include "weather\WhrSun.c"
#include "weather\WhrTornado.c"
#include "weather\WhrAstronomy.c"
#include "weather\WhrSeaPresets.c"

#define WIND_NORMAL_POWER		20.0

#define MAX_WEATHERS   34

object	Weather, WeatherParams, WhrCommonParams;
int		iNextWeatherNum = -1;
int		iCurWeatherNum = -1;
int		iBlendWeatherNum = -1;
int		iCurWeatherHour = -1;
bool	bCurWeatherStorm = false;
int		iTotalNumWeathers = 0;
string	sLightingPath = "day";
string	sLmLightingPath = "day";
string	sInsideBack = "";
string	sNewExecuteLayer, sNewRealizeLayer;
string	sCurrentFog;
float	fWeatherDelta = 0.0;
float	fWeatherAngle, fWeatherSpeed;
float	fFogDensity;
int		iShadowDensity[2];
int		iPrevWeather = -1;
int		sunIsShine = true;
bool	bWeatherLoaded = false;
bool	bWeatherIsNight = false;
bool	bWeatherIsLight = false;
bool	bWeatherIsRain = false;
bool	bWeatherIsStorm = false;

object Weathers[MAX_WEATHERS];

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

void SetNextWeather(string sWeatherID)
{
	// find weather
	iNextWeatherNum = -1; 
	for (int i=0; i<MAX_WEATHERS; i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) { continue; }
		if (Weathers[i].id == sWeatherID)
		{
			iNextWeatherNum = i;
			if (bBettaTestMode)
			{
				Trace("iNextWeatherNum = " + iNextWeatherNum);
				Log_SetStringToLog("������: " + Weathers[i].Lighting);
			}
			return;
		}
	}
}

void WeatherInit()
{
	//DeleteAttribute(&WeatherParams,"");

	if (LoadSegment("weather\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("weather\WhrInit.c");
	}
}

void DeleteWeatherEnvironment()
{
	iBlendWeatherNum = -1;
	if (isEntity(&Weather))
	{
		DeleteClass(&Weather);
	}
	DeleteAttribute(&Weather,"");
	//WeatherParams.Tornado = false;
	//DeleteAttribute(&WeatherParams,"");

	WhrDeleteRainEnvironment();
	WhrDeleteSkyEnvironment();
	WhrDeleteSunGlowEnvironment();
	WhrDeleteLightningEnvironment();
	WhrDeleteTornadoEnvironment();
	WhrDeleteSeaEnvironment();
	WhrDeleteAstronomyEnvironment();

	DelEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor");
	DelEventHandler("frame","Whr_OnWindChange");

	bWeatherLoaded = false;
}

aref GetCurrentWeather()
{
	//Boyer fix for when iCurWeatherNum = -1...borrowed from function Whr_LoadNextWeather(int nPlus)
	if (iCurWeatherNum < 0)
		iCurWeatherNum = iTotalNumWeathers - 1;
	//End fix
	aref arWeather; 
	makearef(arWeather,Weathers[iCurWeatherNum]);
	return arWeather;
}

void CreateWeatherEnvironment()
{
	string sAttrName;
	string sSky = "";
	int iWeatherFound[MAX_WEATHERS];
	int iNumWeatherFound = 0;
	int iHour = MakeInt(GetHour());

	bool bWhrStorm = false; 
	bool bWhrTornado = false; 
	bool bRain = false;
 
																					   
																																		   

	if (CheckAttribute(&WeatherParams,"Storm")) { bWhrStorm = sti(WeatherParams.Storm); }
	if (CheckAttribute(&WeatherParams,"Tornado")) { bWhrTornado = sti(WeatherParams.Tornado); }

//navy --> Rain
	int iMonth = GetDataMonth();
	int iTmp, iChance;
	if (CheckAttribute(&WeatherParams,"Rain")) { bRain = sti(WeatherParams.Rain); } 
	if (!CheckAttribute(&WeatherParams, "Rain.ThisDay")) WeatherParams.Rain.ThisDay = false;

    //����� �����������, �.�. ��� ������ ������ ��� �����!!! �� � ��� ����������??
	if (iHour >= 5 && iHour <= 15 && !sti(WeatherParams.Rain.ThisDay))
	{
		//����.
		iChance = 0;
		//��... ��� ������� ����� ������!!!! ���! ���������� 50/50 �����, ���� ����� ���������� - ��������/������
		if (iMonth > 4 && iMonth < 9) iChance = 30;
		//��� ��� ������� �������� �� �����! �� �������.
		bRain = ((rand(50) + rand(50)) < (5 + iChance));

        //������ ��������, �������� ��, �������� ����� ��������, ����� ������� �����.
		if (bRain || CheckAttribute(pchar, "questTemp.StartRain"))
		{
			//��� ������...
			WeatherParams.Rain.ThisDay   = true;
			WeatherParams.Rain.StartTime = iHour + 2 + rand(2);
			//����������������� � ������� //1 ��� ���, ����� ���� �� ������.
			WeatherParams.Rain.Duration  = 60 + rand(120);

			iTmp = sti(WeatherParams.Rain.StartTime);

			Weathers[iTmp].Bak.Fog.Color		= Weathers[iTmp].Fog.Color;
			Weathers[iTmp].Bak.Fog.Height		= Weathers[iTmp].Fog.Height;
			Weathers[iTmp].Bak.Fog.Density		= Weathers[iTmp].Fog.Density;
			Weathers[iTmp].Bak.Fog.SeaDensity	= Weathers[iTmp].Fog.SeaDensity;
			Weathers[iTmp].Bak.Fog.IslandDensity	= Weathers[iTmp].Fog.IslandDensity;

			Weathers[iTmp].Bak.Sun.Glow.Enable		= Weathers[iTmp].Sun.Glow.Enable;
			Weathers[iTmp].Bak.Sun.Overflow.Enable	= Weathers[iTmp].Sun.Overflow.Enable;

			Weathers[iTmp].Fog.Color = argb(0,50,60,65);
			Weathers[iTmp].Fog.Height = 1000;
			Weathers[iTmp].Fog.Density = 0.003;
			Weathers[iTmp].Fog.SeaDensity = 0.0022;
			Weathers[iTmp].Fog.IslandDensity = 0.0015;

			Weathers[iTmp].Sun.Glow.Enable = false;
			Weathers[iTmp].Sun.Overflow.Enable = false;

			Log_TestInfo("Will raining in : " + WeatherParams.Rain.StartTime);
		}
	}

	//������������� ������� �����, ���� ����� ����������
	if (bRain)
	{
		iTmp = sti(WeatherParams.Rain.StartTime) + (sti(WeatherParams.Rain.Duration)/60 + 0.5);
		if (iHour > iTmp)
		{
			bRain = false;
			WeatherParams.Rain = false;
			WeatherParams.Rain.ThisDay = false;
		}
	}
//navy <-- Rain


	//Trace("bCurWeatherStorm = " + bCurWeatherStorm);

	if (iNextWeatherNum != -1)
	{
		if (iPrevWeather == -1) { iPrevWeather = iCurWeatherNum; }
		iCurWeatherHour = iHour;
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
		//Trace("Weather: used preset weather " + iCurWeatherNum);
	}
	else
	{
		// search weather for hour
		for (int i=0;i<MAX_WEATHERS;i++)
		{
			//navy --> ������ ������� ������ �� �������� ����������� �����... ����� ������������ ����� ������...
			//��� ����� ��� ������ ������� ������... �� ����� ������� ���.
			if (!bRain && sti(Weathers[i].Rain.NumDrops) > 0 && sti(Weathers[i].Rain.NumDrops) < 5100) 
			{
				Weathers[i].Rain.NumDrops = 0;
				Weathers[i].Lightning.Enable = false;
			}
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && !sti(WeatherParams.Rain.ThisDay) && CheckAttribute(&Weathers[i], "Bak")) 
			{
				Weathers[i].Fog.Color		= Weathers[i].Bak.Fog.Color;
				Weathers[i].Fog.Height		= Weathers[i].Bak.Fog.Height;
				Weathers[i].Fog.Density		= Weathers[i].Bak.Fog.Density;
				Weathers[i].Fog.SeaDensity	= Weathers[i].Bak.Fog.SeaDensity;
				Weathers[i].Fog.IslandDensity	= Weathers[i].Bak.Fog.IslandDensity;

				Weathers[i].Sun.Glow.Enable		= Weathers[i].Bak.Sun.Glow.Enable;
				Weathers[i].Sun.Overflow.Enable	= Weathers[i].Bak.Sun.Overflow.Enable;

				DeleteAttribute(&Weathers[i], "Bak");
			}
			if (!bRain) Weathers[i].Rainbow.Enable = false;	
			//navy <--
			if (!CheckAttribute(&Weathers[i], "hour")) { continue; }
			if (CheckAttribute(&Weathers[i], "skip")) 
			{ 
				if (sti(Weathers[i].skip)) { continue; }
			}

			bool bCanStorm = sti(Weathers[i].Storm);
			bool bCanTornado = sti(Weathers[i].Tornado);
			int iMin = sti(Weathers[i].Hour.Min);
			int iMax = sti(Weathers[i].Hour.Max);
			if (iMin == iMax && iMin != iHour) { continue; }
			if (iMin > iMax)
			{
				if (iHour < iMin && iHour > iMax) { continue; }
			}
			if (iMin < iMax)
			{
				if (iHour < iMin || iHour > iMax) { continue; }
			}
			if (bWhrStorm != bCanStorm) { continue; }
			if (bWhrTornado == true && bWhrTornado != bCanTornado) { continue; }
			
			iWeatherFound[iNumWeatherFound] = i;
			iNumWeatherFound++;
		}

		iCurWeatherHour = iHour;

		if (iNumWeatherFound == 0)
		{
			Trace("Error: iNumWeatherFound = 0, for hour = " + iHour);
			iCurWeatherNum = 0;
		}
		else
		{
			iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound-1)];
		}
	}

	int iCurLocation;
	int iTestWeather;
	bool bQuestlockWeather;
    float fGetTime = GetTime();

	bQuestlockWeather = false;
	sunIsShine = true;

	if(CheckAttribute(pchar, "location"))
	{
		iCurLocation = reload_location_index;
		if(iCurLocation != -1)
		{
			if(CheckAttribute(&locations[iCurLocation], "storm"))
			{
				bWhrStorm = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "tornado"))
			{
				bWhrTornado = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm"))
			{
				if (fGetTime >= 6.0 && fGetTime < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01_add";
				else { if (fGetTime >= 10.0 && fGetTime < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02_add";
				else { if (fGetTime >= 18.0 && fGetTime < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03_add";
				else { locations[iCurLocation].QuestlockWeather = "Storm04_add";
				}}}
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 2.5; //��������� ������� ����
			}
			else 
			{ 
				if(CheckAttribute(&locations[iCurLocation], "alwaysStorm_2")) //COAS escape
                {
					WeatherParams.Storm = "1";
                    if (fGetTime >= 6.0 && fGetTime < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01";
                    else { if (fGetTime >= 10.0 && fGetTime < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02";
                    else { if (fGetTime >= 18.0 && fGetTime < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03";
                    else { locations[iCurLocation].QuestlockWeather = "Storm04";
                    }}}
                    if (CheckAttribute(&locations[iCurLocation], "alwaysStorm_2.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 28.0; //40.0;
                }
			}
			if(CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
			{
				iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
				if(iTestWeather != -1)
				{
					iCurWeatherNum = iTestWeather;
					bQuestlockWeather = true;
					if (CheckAttribute(&locations[iCurLocation], "lockWeather") && locations[iCurLocation].lockWeather == "Inside")
					{
						sunIsShine = false;
					}
				}
			}
		}
		else
		{
			iCurLocation = FindIsland(pchar.location);
			if(iCurLocation != -1)
			{
				if(CheckAttribute(&Islands[iCurLocation], "storm"))
				{
					bWhrStorm = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "tornado"))
				{
					bWhrTornado = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "alwaysStorm"))
				{
					if (fGetTime >= 6.0 && fGetTime < 10.0) Islands[iCurLocation].QuestlockWeather = "Storm01";
					else { if (fGetTime >= 10.0 && fGetTime < 18.0) Islands[iCurLocation].QuestlockWeather = "Storm02";
					else { if (fGetTime >= 18.0 && fGetTime < 22.0) Islands[iCurLocation].QuestlockWeather = "Storm03";
					else { Islands[iCurLocation].QuestlockWeather = "Storm04";
					}}}
				}
				if(CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
				{
					iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
					if(iTestWeather != -1)
					{
						iCurWeatherNum = iTestWeather;
						bQuestlockWeather = true;
					}
				}
			}
		}
	}
	bWeatherIsStorm = bWhrStorm;
	bCurWeatherStorm = bWhrStorm;

	if (!bQuestlockWeather)
	{
		iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);
	}
	else
	{
		iBlendWeatherNum = -1; // ���������� ������
	}

	//������ ������, ����������� � ������� ����
	if (bMainMenu)
	{
		iTestWeather = sti(InterfaceStates.mainmenuweather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
	}
	if (startGameWeather)
	{
		iTestWeather = sti(InterfaceStates.startGameWeather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
		startGameWeather = false;
	}

	// create main module Weather
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather))
	{
		CreateEntity(&Weather, "Weather");
	}

	aref aCurWeather = GetCurrentWeather();

	sLightingPath = Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack = Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight = Whr_GetLong(aCurWeather,"Night");
	bWeatherIsLight = Whr_GetLong(aCurWeather,"Lights");

	if(CheckAttribute(pchar, "wind.angle"))
	{
		Weather.Wind.Angle = pchar.wind.angle;
		//DeleteAttribute(pchar, "wind.angle");
	}
	else
	{
		Weather.Wind.Angle = frand(PIm2);//  ����!!! ��� �� �������!!!!! frand(180.0);//Whr_GetFloat(aCurWeather,"Wind.Angle");
		pchar.wind.angle = Weather.Wind.Angle;
	}

	if (CheckAttribute(pchar, "wind.speed"))
	{
		Weather.Wind.Speed = pchar.wind.speed;
		//DeleteAttribute(pchar, "wind.speed");
	}
	else
	{
		Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
		pchar.wind.speed = Weather.Wind.Speed;
	}

	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";

	sCurrentFog = "Fog";
	if (bSeaActive) 
	{ 
		if (CheckAttribute(aCurWeather, "SpecialSeaFog")) { sCurrentFog = "SpecialSeaFog"; }	
	}

	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);

	if (iBlendWeatherNum < 0 || bQuestlockWeather) 
	{
		Weather.Time.time = GetTime();
		Weather.Time.speed = 350.0; // ���������� ������ �� ����� ������
		Weather.Time.updatefrequence = 12; // ���������� ���������� �� ����� ������
	} else {
		Weather.Time.time = GetTime();
		Weather.Time.speed = 450;
		Weather.Time.updatefrequence = 15; // ���������� ���������� �� ����� ������
		if (bSeaActive && !bAbordageStarted)
		{
			if (iArcadeSails == 1)  // �������� � ������ ������, ����� �������
			{
				Weather.Time.speed = 250; // ���������� ������ �� ����� ������
				Weather.Time.updatefrequence = 10;
			}
		}
		else
		{ // ����
			Weather.Time.speed = 350;
			Weather.Time.updatefrequence = 12; // ���������� ���������� �� ����� ������
		}
	}

	Weather.isDone = "";

	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
	SetEventHandler("frame","Whr_OnWindChange",0);

	fFogDensity = stf(Weather.Fog.Density);

	fWeatherDelta = 0.0;
	fWeatherAngle = stf(Weather.Wind.Angle);
	//fWeatherAngle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
	fWeatherSpeed = stf(Weather.Wind.Speed);
	
    // boal -->
	bRain = true; // ��� �� �������� Whr_isRainEnable(); ��-�� �� ���� :(
    string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref rLoc;
		rLoc = &Locations[iLocation];
		
		if (CheckAttribute(rLoc, "environment.weather.rain") && !sti(rLoc.environment.weather.rain))
		{
			bRain = false;
		}
		//�� ����� ��� �����������������, ���� ����� ���������� �������� environment.weather.rain,
		//�� ��� � �� �����, �� ��� �� �����������
		//��� � �����, ������, ������ �����????
		//navy
		else
		{
			if (CheckAttribute(rLoc, "type"))
			{
				// ��� ���������
				if(rLoc.type == "residence"
					|| rLoc.type == "tavern"
					|| rLoc.type == "house"
					|| rLoc.type == "shop"
					|| rLoc.type == "shipyard"
					|| rLoc.type == "church" )
				{
					//��� �����
					bRain = false;
				}
			}
		}
	}
	//����, ���� ����� ���� �����, ������� ���������
	if (bRain)
	{
		WhrCreateRainEnvironment();
	}
	//���� �� �����, �������.
	else
	{
		ClearRainEnvironment();
	}
	// boal <--

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateAstronomyEnvironment();
	WhrCreateSkyEnvironment();
	
	string sPreset = WhrGetSeaPresetFromWind(fWeatherSpeed);
    WhrSetSeaPreset(iCurWeatherNum, sPreset);
	WhrCreateSeaEnvironment();

	if(iLocation != -1)
	{
		if(CheckAttribute(&Locations[iLocation], "lockWeather"))
		{
			bWhrTornado = false;
		}
	}
	if (bWhrTornado) { WhrCreateTornadoEnvironment(); }

	Particles.windpower = 0.05 * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	Particles.winddirection.x = sin(Whr_GetWindAngle());
	Particles.winddirection.z = cos(Whr_GetWindAngle());

	bWeatherLoaded = true;

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Weather.Fog.IslandDensity;
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
	}

	//Trace("Whr: Select id = " + aCurWeather.id);
}

void Whr_UpdateWeather()
{
	if (!isEntity(&Weather)) { return; }

//������� ����� ������
//	WeatherInit();

	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
}

void Whr_LoadNextWeather(int nPlus)
{
	if (!isEntity(&Weather)) { return; }
	//WeatherInit();  //������� ����� ������

	iCurWeatherHour = MakeInt(GetHour());
	iCurWeatherNum = iCurWeatherNum + nPlus;

	if (iCurWeatherNum < 0)
	{
		iCurWeatherNum = iTotalNumWeathers - 1;
	}
	if (iCurWeatherNum >= iTotalNumWeathers)
	{
		iCurWeatherNum = 0;
	}

	if (CheckAttribute(&Weathers[iCurWeatherNum], "Skip")) 
	{ 
		if (sti(Weathers[iCurWeatherNum].skip)) 
		{ 
			Whr_LoadNextWeather(nPlus);
			return;
		}
	}
	Log_TestInfo("������: " + Weathers[iCurWeatherNum].id + " ���������: " + Weathers[iCurWeatherNum].Lighting);
	Log_TestInfo("Sun: HeightAngle: " + Weathers[iCurWeatherNum].Sun.HeightAngle);

	iNextWeatherNum = iCurWeatherNum;
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	aref	aCurWeather = GetCurrentWeather();
	iCurWeatherHour = sti(aCurWeather.Hour.Min);

	SetCurrentTime(iCurWeatherHour, 0);
	Weather.Time.time = GetTime();
}

void Whr_OnWindChange()
{
	float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 6.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

	Weather.Wind.Angle = fAng;
	Weather.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
	int		iAlpha, iColor;
	float	x, y, z;

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	if( iBlendWeatherNum < 0 )
	{
		aref aCurWeather = GetCurrentWeather();
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(aCurWeather.(sCurrentFog).Height)));

		//iColor = argb(0,0,0,0);
		int iFogColor = sti(Weather.Fog.Color);
		iColor = or(shl(iAlpha, 24), iFogColor);
	}
	else
	{
		float fBlend = stf(Environment.time) - sti(Environment.time);
		float fH = Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sCurrentFog).Height));
		int iColorTmp = Whr_BlendColor(fBlend, sti(Weathers[iCurWeatherNum].(sCurrentFog).Color), sti(Weathers[iBlendWeatherNum].(sCurrentFog).Color));

		iAlpha = 255 - MakeInt(255.0 * Clampf(y / fH));
		iColor = or(shl(iAlpha, 24), iColorTmp);
	}

	return iColor;
}

float Whr_BlendFloat(float fBlend, float f1, float f2)
{
	float f = f1 + fBlend * (f2-f1);
	return f;
}

int Whr_BlendLong(float fBlend, int i1, int i2)
{
	int i = makeint(i1 + fBlend * (i2-i1));
	return i;
}

int Whr_BlendColor(float fBlend, int col1, int col2)
{
	int r1 = shr(and(col1,16711680), 16); // get red color 1
	int r2 = shr(and(col2,16711680), 16); // get red color 2

	int g1 = shr(and(col1,65280), 8); // get green color 1
	int g2 = shr(and(col2,65280), 8); // get green color 2

	int b1 = and(col1,255); // get blue color 1
	int b2 = and(col2,255); // get blue color 2

	int r = r1 + MakeInt(fBlend * (r2-r1));
	int g = g1 + MakeInt(fBlend * (g2-g1));
	int b = b1 + MakeInt(fBlend * (b2-b1));

	return argb(0,r,g,b);
}

void Whr_TimeUpdate()
{
	float fTime = GetEventData();
	//float fBlend = fTime - makeint(fTime);

	//
	Environment.time = fTime;
	int nOldHour = sti(Environment.date.hour);
	int nNewHour = makeint(fTime);
	int nNewMin = makeint((fTime - nNewHour)*60);
	int nNewSec = makeint(((fTime - nNewHour)*60 - nNewMin)*60);
	Environment.date.min = nNewMin;
	Environment.date.hour = nNewHour;
	Environment.date.sec = nNewSec;
	worldMap.date.hour = nNewHour;
	worldMap.date.min  = nNewMin;
	if( nNewHour < nOldHour ) // ���������� ��� ������� � 23 � 0
	{
		AddDataToCurrent(0,0,1);
		Weather.Time.time = GetTime();
	} // to_do ����� ���� � CalcLocalTime
	if( iBlendWeatherNum < 0 ) {return;}
	//navy --> Rain
	string sTmp;
	int iTmp, iTime;
	bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain")) { bRain = sti(WeatherParams.Rain); } 
	//navy <-- Rain
	iCurWeatherNum = FindWeatherByHour( makeint(fTime) );
	iBlendWeatherNum = FindBlendWeather( iCurWeatherNum );

	//zagolski. ������������ ����� ������ �� �������� � �� ����
	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Weather.Fog.IslandDensity;
		Sea.Fog.SeaDensity = Weather.Fog.SeaDensity;
	}

	//navy --> Rain
	bool  bIsRainEnable = Whr_isRainEnable();
	
	if (bIsRainEnable) // �� ��� �������, ��� ���� �������
	{
		//��� ���������� ��������� �����...
		//������ ���������� � ����.
		if (bRain)
		{
			//��-��������� ��������� ������.
			int nRainDuration = sti(WeatherParams.Rain.Duration);
			iTmp = 3;

			//�������� ����� ��������� � ������ �����
			iTime = GetQuestPastMinutesParam("Rain.Duration");
			//���� ������� ������ ������ ��� ������������, ������� �����.
			if (iTime > nRainDuration)
			{
				iTmp = 3;
				bRain = false;
			}
			//������ ������.
			if (iTime < (4*nRainDuration/5))
			{
				iTmp = 2;
			}
			//������ ������.
			if (iTime < (2*nRainDuration/3))
			{
				iTmp = 1;
			}
			//������ ������.
			if (iTime < (nRainDuration/3))
			{
				iTmp = 0;
			}
			Log_TestInfo("Is Raining: " + iTime + " minutes, stage: " + iTmp);
			//� ����������� �� �������� ������ ���������� �����.
			switch (iTmp)
			{
				case 0:
					//����
					WeatherParams.Rain.Sound = true;
					break;
				case 1:
					//��������� ������, ������ ������� �����...
					if (rand(100) < 40)
					{
						Log_TestInfo("Starting the Lightning...");
						Weathers[iCurWeatherNum].Lightning.Enable = true;
						Weathers[iCurWeatherNum].Lightning.SubTexX = 4;
						Weathers[iCurWeatherNum].Lightning.SubTexY = 1;
						Weathers[iCurWeatherNum].Lightning.ScaleX = 0.7;
						Weathers[iCurWeatherNum].Lightning.ScaleY = 1.0;
						Weathers[iCurWeatherNum].Lightning.Flash.Texture = "Weather\lightning\flash.tga";
					}
					break;
				case 2:
					//3 ������...
					break;
				case 3:
					//�����������...
					if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
					{
						WeatherParams.Rain = false;
						WeatherParams.Rain.Sound = false;
						Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
						Weathers[iCurWeatherNum].Lightning.Enable = false;
						if (nNewHour > 5 && nNewHour < 20) //navy -- ������ �� �����. 5.03.07
						{
							Weathers[iCurWeatherNum].Rainbow.Enable = true;
						}
	
						DeleteAttribute(&WeatherParams, "Rain.StartTime");
					}
					WeatherParams.Rain.ThisDay = false;
					break;
			}

			if (iTmp != 0)
			{
				Weathers[iCurWeatherNum].Rain.NumDrops = 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength = 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color = argb(0,23,23,23);
			}

			if (iTmp != 3)
			{
				Weathers[iBlendWeatherNum].Rain.NumDrops = 3500 + rand(1500);
				Weathers[iBlendWeatherNum].Rain.DropLength = 4 + rand(8);
				Weathers[iBlendWeatherNum].Rain.Color = argb(0,23,23,23);

				if (!CheckAttribute(&Weathers[iBlendWeatherNum], "Bak"))
				{
					Weathers[iBlendWeatherNum].Bak.Fog.Color		= Weathers[iBlendWeatherNum].Fog.Color;
					Weathers[iBlendWeatherNum].Bak.Fog.Height		= Weathers[iBlendWeatherNum].Fog.Height;
					Weathers[iBlendWeatherNum].Bak.Fog.Density		= Weathers[iBlendWeatherNum].Fog.Density;
					Weathers[iBlendWeatherNum].Bak.Fog.SeaDensity	= Weathers[iBlendWeatherNum].Fog.SeaDensity;
					Weathers[iBlendWeatherNum].Bak.Fog.IslandDensity	= Weathers[iBlendWeatherNum].Fog.IslandDensity;

					Weathers[iBlendWeatherNum].Bak.Sun.Glow.Enable		= Weathers[iBlendWeatherNum].Sun.Glow.Enable;
					Weathers[iBlendWeatherNum].Bak.Sun.Overflow.Enable	= Weathers[iBlendWeatherNum].Sun.Overflow.Enable;
				}

				Weathers[iBlendWeatherNum].Fog.Color = argb(0,50,60,65);
				Weathers[iBlendWeatherNum].Fog.Height = 1000;
				Weathers[iBlendWeatherNum].Fog.Density = 0.003;
				Weathers[iBlendWeatherNum].Fog.SeaDensity = 0.0022;
				Weathers[iBlendWeatherNum].Fog.IslandDensity = 0.0015;

				Weathers[iBlendWeatherNum].Sun.Glow.Enable = false;
				Weathers[iBlendWeatherNum].Sun.Overflow.Enable = false;
			}
		}
		//������ �����... ���� ��������� �� �������...
		else
		{
			//��������...
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay) && sti(WeatherParams.Rain.StartTime) <= nOldHour)
			{
				//�������������.
				Weathers[iBlendWeatherNum].Rain.NumDrops = 2000 + rand(3000);
				Weathers[iBlendWeatherNum].Rain.DropLength = 2 + rand(10);
				Weathers[iBlendWeatherNum].Rain.Color = argb(0,23,23,23);

				if (!CheckAttribute(&Weathers[iBlendWeatherNum], "Bak"))
				{
					Weathers[iBlendWeatherNum].Bak.Fog.Color		= Weathers[iBlendWeatherNum].Fog.Color;
					Weathers[iBlendWeatherNum].Bak.Fog.Height		= Weathers[iBlendWeatherNum].Fog.Height;
					Weathers[iBlendWeatherNum].Bak.Fog.Density		= Weathers[iBlendWeatherNum].Fog.Density;
					Weathers[iBlendWeatherNum].Bak.Fog.SeaDensity	= Weathers[iBlendWeatherNum].Fog.SeaDensity;
					Weathers[iBlendWeatherNum].Bak.Fog.IslandDensity	= Weathers[iBlendWeatherNum].Fog.IslandDensity;

					Weathers[iBlendWeatherNum].Bak.Sun.Glow.Enable		= Weathers[iBlendWeatherNum].Sun.Glow.Enable;
					Weathers[iBlendWeatherNum].Bak.Sun.Overflow.Enable	= Weathers[iBlendWeatherNum].Sun.Overflow.Enable;
				}
				Weathers[iBlendWeatherNum].Fog.Color = argb(0,50,60,65);
				Weathers[iBlendWeatherNum].Fog.Height = 1000;
				Weathers[iBlendWeatherNum].Fog.Density = 0.003;
				Weathers[iBlendWeatherNum].Fog.SeaDensity = 0.0022;
				Weathers[iBlendWeatherNum].Fog.IslandDensity = 0.0015;

				Weathers[iBlendWeatherNum].Sun.Glow.Enable = false;
				Weathers[iBlendWeatherNum].Sun.Overflow.Enable = false;

				//��������� ����� ������ �����.
				SaveCurrentQuestDateParam("Rain.Duration");
				//���� "�����"
				WeatherParams.Rain = true;
				//����
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));
				Log_TestInfo("Rain Strated. Duration: " + WeatherParams.Rain.Duration + " minutes");
			}
		}
	}
	//navy <-- Rain

	if( nNewHour != nOldHour )
	{
		Whr_UpdateWeatherHour();
	}

	// update weather: sun lighting
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	//navy -- �������� ����� ��������, ���� ����������, ��� ��� ���. 5.03.07
	if (bIsRainEnable) 
	{
		FillRainData(iCurWeatherNum, iBlendWeatherNum);
		Rain.isDone = "";
	}

	// update sun glow: sun\moon, flares
	WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;

	// update sky: fog
	Sky.TimeUpdate = fTime;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{
	bool bOldIsDay = Whr_IsDay();
	//#20190211-01
	bool doLightChange = false;
	int i;
	
	bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum],"Lights");
	bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum],"Night");

	//#20191020-01
	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);
	FillStars(aStars);
	//FillAstronomyFadeValue();
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;

	if( Whr_IsDay() != bOldIsDay )
	{ // ������ ��������� ���������
		Whr_ChangeDayNight();
		Event("eChangeDayNight");
		//#20190211-01
        doLightChange = true;
 	}
 	if (bSeaActive && !bAbordageStarted)
	{
        bool isSeaEnt = false;
	    if (IsEntity(&Sea))
            isSeaEnt = true;
        Whr_WindChange();
		i = FindIsland(pchar.location)
        if ( i != -1)
        {
            //#20190211-01
            if (isSeaEnt) {
                if(stf(Sea.MaxSeaHeight) != SetMaxSeaHeight(i))
	
					string sPreset = WhrGetSeaPresetFromWind(fWeatherSpeed);
					WhrSetSeaPreset(iCurWeatherNum, sPreset);
                    WhrCreateSeaEnvironment(); // boal ����� ���� �� ����
	 		}
 		}
 		//#20190211-01
        if(doLightChange && isSeaEnt) {
            doShipLightChange(aCurWeather);
        }
 	}
}

void doShipLightChange(ref aCurWeather)
{
    int j, iCharIdx;

    ref rChar;
    Sea.Lights = aCurWeather.Lights;
    for(j = 0; j < iNumShips; j++) {
        iCharIdx = Ships[j];
        if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
        rChar = GetCharacter(Ships[j]);
        Ship_SetLightsAndFlares(rChar);
        SendMessage(&characters[iCharIdx], "l", MSG_SHIP_LIGHTSRESET);
    }
}

void Whr_ChangeDayNight()
{
	int loadLocationIndex = FindLoadedLocation();
	if( loadLocationIndex >= 0 )
	{
		LocationSetLights(&Locations[loadLocationIndex]);
		if( Whr_IsDay() )
		{
			SendMessage( &Locations[loadLocationIndex], "ls", MSG_LOCATION_EX_MSG, "DelFlys" );
		}
	}
}

void FillWeatherData(int nw1, int nw2)
{	
	if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	string sCurFog = Whr_GetCurrentFog();
	if( nw2<0)
	{
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
		Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
		Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
		Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity");
		Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity");

		Weather.Sun.Color = Whr_GetColor(&Weathers[nw1],"Sun.Color");
		Weather.Sun.HeightAngle = Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle");
		Weather.Sun.AzimuthAngle = Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle");
		Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
	}
	else
	{
		float fBlend = stf(Environment.Time) - sti(Environment.Time);
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start") );
		Weather.Fog.Density = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density") );
		Weather.Fog.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color") );
		Weather.Fog.IslandDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".IslandDensity") );
		Weather.Fog.SeaDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".SeaDensity") );

		Weather.Sun.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color") );
		Weather.Sun.HeightAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.HeightAngle") );
		Weather.Sun.AzimuthAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.AzimuthAngle") );
		Weather.Sun.Ambient = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient") );
	}
}

int FindWeatherByHour(int nHour)
{
	for (int n=0; n<MAX_WEATHERS; n++)
	{
		if (!CheckAttribute(&Weathers[n], "hour")) {continue;}
		if (CheckAttribute(&Weathers[n], "skip") && sti(Weathers[n].skip)==true) {continue;}
		if (CheckAttribute(&Weathers[n], "Storm") && sti(Weathers[n].Storm)==true) {continue;}

		if( sti(Weathers[n].hour.min) == nHour ) {return n;}
	}
	return -1;
}

int FindBlendWeather(int iWeatherNum)
{
	// ���� �������� return -1;
	if( iWeatherNum<0 || iWeatherNum>=MAX_WEATHERS ) {return -1;}

	if( !CheckAttribute(&Weathers[iWeatherNum], "hour") ) {return -1;}
	if( CheckAttribute(&Weathers[iWeatherNum],"Storm") && sti(Weathers[iWeatherNum].Storm)==true ) {return -1;}
	if( CheckAttribute(&Weathers[iWeatherNum],"skip") && sti(Weathers[iWeatherNum].skip)==true ) {return -1;}

	int nBlendWeatherHour = sti(Weathers[iWeatherNum].hour.min) + 1;
	if( nBlendWeatherHour>=24 ) {nBlendWeatherHour = 0;}

	return FindWeatherByHour(nBlendWeatherHour);
}

void CreateWeather(string sExecuteLayer, string sRealizeLayer)
{
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sExecuteLayer, sRealizeLayer);
}

void DeleteWeather()
{
	DeleteWeatherEnvironment();
}

void MoveWeatherToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute",&Weather);
	LayerDelObject("realize",&Weather);
	LayerDelObject(SEA_EXECUTE,&Weather);
	LayerDelObject(SEA_REALIZE,&Weather);

	sNewExecuteLayer = sExecuteLayer;
	sNewRealizeLayer = sRealizeLayer;

	LayerAddObject(sExecuteLayer,&Weather,1000000);
	LayerAddObject(sRealizeLayer,&Weather,65530);

	MoveRainToLayers(sExecuteLayer, sRealizeLayer);
	MoveLightningToLayers(sExecuteLayer, sRealizeLayer);
	MoveSkyToLayers(sExecuteLayer, sRealizeLayer);
	MoveSunGlowToLayers(sExecuteLayer, sRealizeLayer);
	MoveAstronomyToLayers(sExecuteLayer, sRealizeLayer);
}

float Whr_GetFogDensity() { return fFogDensity; }

float Whr_GetWindAngle()
{
	if (!CheckAttribute(&Weather,"Wind.Angle")) { return 0.0; }
	return stf(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
	if (!CheckAttribute(&Weather,"Wind.Speed")) { return 3.0; }
	return stf(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
	aref	aCurWeather = GetCurrentWeather();

	iShadowDensity[0] = argb(255,96,96,96);
	iShadowDensity[1] = argb(255,96,96,64);

	if (bWeatherLoaded)
	{
		iShadowDensity[0] = Whr_GetColor(aCurWeather,"Shadow.Density.Head");
		iShadowDensity[1] = Whr_GetColor(aCurWeather,"Shadow.Density.Foot");
	}
	
	return &iShadowDensity;
}

string	Whr_GetCurrentFog() { return sCurrentFog; }

string	Whr_GetInsideBack() { return sInsideBack; }
string	GetLightingPath()	
{
//navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
//navy <--
	return sLightingPath; 
}
string	GetLmLightingPath() 
{ 
//navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return "storm";
	}
//navy <--
	return sLmLightingPath; 
}

bool	Whr_IsDay() { return !bWeatherIsNight; }
bool	Whr_IsNight() { return bWeatherIsNight; }
bool	Whr_IsLight() { return bWeatherIsLight; }
bool	Whr_IsRain() { return bWeatherIsRain; }
bool	Whr_IsStorm() { return bWeatherIsStorm; }

int FindWeather(string sWeatherID)
{
	for (int i=0;i<MAX_WEATHERS;i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) 
		{ 
			continue; 
		}
		if(Weathers[i].id == sWeatherID)
		{
			return i;
		}
	}
	return -1;
}

//navy --> Rain ������
void Whr_SetRainSound(bool _set, bool _isNight)
{
//	return;
	// ���� ������, �� �������� ����� CalcLocalTime, ����� ������ ��� ����� � ������� ����

	string scheme = "land";
	//���� ������� ��, ��� �����: land, sea, town
	//����� � ������...
	if (!bSeaActive || bAbordageStarted)
	{
		if (IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
		{
			switch (loadedLocation.type)
			{
			case "town":
				scheme = "town";
				break;
			case "land":
				scheme = "land";
				break;
			case "deck":
				scheme = "deck";
				break;
			}
		}
	}
	else
	{
		scheme = "sea";
	}

	//�������� - ����/����
	if (_isNight)
    {
		scheme = scheme+"_night";
    }
	else
	{
		scheme = scheme+"_day";
	}

	//���� ������������� ���� �����
	if (_set)
	{
		scheme = scheme + "_rain";
	}

	trace(": Set Rain Sound... " + _set);
	SetSoundScheme(scheme);
}

string Whr_GetRainyLightningPath()
{
	//trace("__GET__COL__");
	return "storm1";
}
//navy <--

// boal -->
void Whr_WindChange()
{
	aref aCurWeather = GetCurrentWeather();

    if(CheckAttribute(pchar, "wind.angle"))
    {
    	Weather.Wind.Angle = stf(pchar.wind.angle) +  frand((PI/4.0)) - (PI / 8.0);
    	if (stf(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + stf(Weather.Wind.Angle);
    }
    else
    {
		Weather.Wind.Angle = frand(PIm2);
	}
	pchar.wind.angle = Weather.Wind.Angle;

	Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
	pchar.wind.speed = Weather.Wind.Speed;
	
	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";
	
	fWeatherAngle = stf(Weather.Wind.Angle);
	fWeatherSpeed = stf(Weather.Wind.Speed);

	CheckIslandChange();
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	//�� � �������
    if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(&loadedLocation)) // pchar ����������� ��� �� ����
	{
        if (CheckAttribute(&loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
		{
			bRain = false;
		}
		/*else
		{
			if (CheckAttribute(loadedLocation, "type"))
			{
				// ��� ���������
				if(loadedLocation.type == "residence"
					|| loadedLocation.type == "tavern"
					|| loadedLocation.type == "house"
					|| loadedLocation.type == "shop"
					|| loadedLocation.type == "shipyard"
					|| loadedLocation.type == "church" )
				{
					//��� �����
					bRain = false;
				}
			}
		}*/
		//� ������ ����� �������� �����
	}
	else
	{
		if (bSeaActive && bAbordageStarted ) // � ���� �� ����������� bLandInterfaceStart
		{
			if (IsEntity(&loadedLocation) && CheckAttribute(&loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
			{
				bRain = false;
			}
		}
	}
	return bRain;
}
// boal <--
