// DEFINES
#define MUSIC_CHANGE_TIME  3000
#define MUSIC_SILENCE_TIME 180000.0
#define SOUNDS_FADE_TIME   200

#event_handler ("LoadSceneSound", "LoadSceneSound")
#event_handler ("ReloadStaticSound", "ReloadStaticSound")
// PLAY
int Play3DSound(string name, float x, float y, float z)
{
	InitSound();
	//Trace("Play3DSound : "+name);
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, false, 0, x, y, z);
}

int Play3DSoundRet(string name, float x, float y, float z)
{
	InitSound();
	//Trace("Play3DSound : "+name);
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, false, 0, x, y, z);
}

int Play3DSoundCached(string name, float x, float y, float z)
{
	InitSound();
	//Trace("Play3DSoundCached : "+name);
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, true, 0, x, y, z);
}

int Play3DSoundComplex(string name, float x, float y, float z, bool bLooped, bool bCached)
{
	InitSound();
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, bLooped, bCached, 0, x, y, z);
}

int PlayStereoSound(string name)
{
	InitSound();
	//Trace("PlayStereoSound : "+name);
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, false, false);
}

int PlayVoiceSound(string name)
{
	InitSound();
	//Trace("PlayStereoSound : "+name);
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
}

int PlayStereoSoundLooped(string name)
{
	InitSound();
	//Trace("PlayStereoSoundLooped : "+name);
	return SendMessage(Sound,"lsllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, true, false);
}

int PlayStereoSoundLooped_JustCache(string name)
{
	InitSound();
	//Trace("PlayStereoSoundLooped : "+name);
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, true, true, false);
}

int PlayStereoOGG(string name)
{
	InitSound();
	//Trace("PlayStereoSound : "+name);
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_FX, false, false, false, 0); //fix boal
}

// OTHER METHODS
void StopSound(int id, int fade)
{
	InitSound();
	//Trace("StopSound : "+id);
	SendMessage(Sound, "lll", MSG_SOUND_STOP, id, fade);
}

void ResumeSound(int id, int fade)
{
	InitSound();
	//Trace("ResumeSound : "+id);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, id, fade);
}

void ReleaseSound(int id)
{
	InitSound();
	//Trace("ReleaseSound : "+id);
	SendMessage(Sound, "ll", MSG_SOUND_RELEASE, id);
}

// SOUND SCHEMES
void ResetSoundScheme()
{
	InitSound();
	//Trace("ResetSoundScheme");
	SendMessage(Sound,"l",MSG_SOUND_SCHEME_RESET);
}

void SetSoundScheme(string schemeName)
{
	InitSound();
	//Trace("SetSoundScheme: "+schemeName);
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_SET,schemeName);
}

void AddSoundScheme(string schemeName)
{
	InitSound();
	//Trace("AddSoundScheme: "+schemeName);
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_ADD,schemeName);
}

/* ����� ��� ������� ���������� �������� ����� � ���� �� ����!. ������ �����������
��� ������, ��� � �����. ������� ��� ����, ��� �� �� ���� ����, �������
�� �������� ���������� �� ������ ��� �������, ��� ��� ��-���� ��������
� ������������� */

void SetWeatherScheme(string scheme)
{
	if (Whr_IsStorm())
	{
		if (Whr_IsNight())
		{
			SetSoundScheme(scheme+"_night_storm");
		}
		else
		{
			SetSoundScheme(scheme+"_day_storm");
		}
	}
	else 
	{ 
		if (Whr_IsRain())
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night_rain");
			}
			else
			{
					SetSoundScheme(scheme+"_day_rain");
			}					
		}
		else
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night");
			}
			else
			{
					SetSoundScheme(scheme+"_day");
			}
		}
	}
}

/* void SetTimeScheme(string scheme)
{
	if (Whr_IsNight())
	{
		AddSoundScheme(scheme+"_night");
	}
	else
	{
		AddSoundScheme(scheme+"_day");
	}
}
*/
void SetSchemeForLocation (ref loc)
{
    ref mchref = GetMainCharacter();
    mchref.GenQuest.God_hit_us = false; // ����� �������� :)  (������ � �����)
    int iColony = -1; //boal music
    
    if(CheckAttribute(loc,"type"))
	{
		ResetSoundScheme();
		SetMusicAlarm(""); // ������ �� ������, ���� ���������� ��� ��������� ����� ����� - �����x boal 28.06.06
		switch (loc.type)
		{
			case "town":
				SetWeatherScheme("town");
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
					if (Whr_IsDay()) SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_day");
					else SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_night");
				}
				else
				{
					SetMusicAlarm("music_gorod");
				}
			break;
			
			case "land": // �������� ����, �������� � ��� �����
				SetWeatherScheme("land");
				SetMusicAlarm("music_jungle");
			break;
			
			case "jungle":
				SetWeatherScheme("land");
				if (loc.id.label == "ExitTown" || loc.id.label == "Incas Temple")
				{
					switch (loc.id.label)
					{
						case "ExitTown":
							if (Whr_IsDay()) SetMusicAlarm("music_exittown");
							else SetMusicAlarm("music_nightjungle");
						break;
						case "Incas Temple":
							SetMusicAlarm("music_teno");
						break;
					}
				}
				else
				{
					if (Whr_IsDay()) SetMusicAlarm("music_jungle");
					else SetMusicAlarm("music_nightjungle");
				}
				DeleteAttribute(pchar, "CheckStateOk"); // ������ ���� ������������� �����������
			break;
			
			case "mayak":
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm("music_mayak");
			break;
			
			case "seashore": 
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm("music_shore");
				DeleteAttribute(pchar, "CheckStateOk"); // ������ ���� ������������� �����������
			break;
			
			case "cave": 
				SetSoundScheme("cave");
				SetMusicAlarm("music_cave");
				bMonstersGen = false; //�������� ���� ��������
			break;
			
			case "dungeon": 
				SetSoundScheme("dungeon");
				SetMusicAlarm("music_cave");
				if (pchar.questTemp.WhisperLine != true)
				{
					bMonstersGen = false; //�������� ���� ��������
				}
			break;
			
			case "inca_temple": // �� ������������
				SetSoundScheme("inca_temple");
				SetMusicAlarm("music_teno_inside");
			break;
			
			case "questisland":
				ResetSoundScheme();
				if (loc.id.label == "jungle") SetWeatherScheme("land");
				else SetWeatherScheme("seashore");
				SetMusicAlarm("music_questislands");
			break;
			
			case "plantation":
				ResetSoundScheme();
				SetWeatherScheme("land");
				SetMusicAlarm("music_plantation");
			break;
			
			case "house":
				SetSoundScheme("house");
				if (CheckAttribute(loc,"brothel") && sti(loc.brothel) == true)
				{
					SetMusicAlarm("music_brothel");
				}
				else
				{
					if (CheckAttribute(loc,"id.label") && loc.id.label == "portoffice")
					{
						SetMusicAlarm("music_portoffice");
					}
					else
					{
						SetMusicAlarm("music_gorod");
					}
				}
				mchref.GenQuest.God_hit_us = true; // ����� �������� :)
			break;
			
			case "tavern":
				SetSoundScheme("tavern");
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_tavern");
				}
				else
				{
					SetMusicAlarm("music_tavern");
				}
			break;
			
			case "shop":
				SetSoundScheme("shop");
				if (CheckAttribute(loc,"id.label") && loc.id.label == "Usurer House")
				{
					SetMusicAlarm("music_bank");
				}
				else
				{
					SetMusicAlarm("music_shop");
				}
			break;
			
			case "residence":
				SetSoundScheme("residence");
				if (CheckAttribute(loc,"fastreload"))   // boal
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_gubernator");
				}
				else
				{
					SetMusicAlarm("music_deck");
				}
			break;
			
			case "church":
				SetSoundScheme("church");
				SetMusicAlarm("music_church");
			break;
			
			case "shipyard":
				SetSoundScheme("shipyard");
				SetMusicAlarm("music_shipyard");
			break;
			
			case "fort_attack": // ������� ����, ���������� �������			
				SetSoundScheme("fort_attack");
				SetMusicAlarm("music_bitva");
			break;
			
			case "fort": // ���� ��� ������ ��������
				SetWeatherScheme("seashore");
				if (CheckAttribute(loc, "parent_colony"))
				{
					iColony = FindColony(loc.parent_colony);
				}
				if (iColony != -1)
				{
					if (Whr_IsDay()) SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_day");
					else SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_night");
				}
				else
				{
					SetMusicAlarm("music_gorod");
				}
			break;
			
			case "deck": // ������ ������
				SetSoundScheme("deck");
				if (Whr_IsDay()) SetMusic("music_deck");
				else SetMusic("music_sea_night");
			break;
			
			case "deck_fight": // ������ ������
				SetSoundScheme("deck_fight");
				SetMusic("music_abordage");
			break;
			
			case "boarding_cabine":
				SetSoundScheme("cabine");
				SetMusicAlarm("music_abordage");
			break;
			
			case "sailing_cabine":
				SetSoundScheme("sail_cabine");
				if (Whr_IsDay()) SetMusicAlarm("music_sea_day");
				else SetMusicAlarm("music_sea_night");
			break;
			
			case "jail":
				SetSoundScheme("jail");
				SetMusicAlarm("music_jail");
			break;
			
			case "ammo":
				SetSoundScheme("jail");
				SetMusicAlarm("music_jail");
			break;
			
			case "LostShipsCity":
				SetWeatherScheme("LostShipsCity");
				SetMusicAlarm("music_LostShipsCity");
			break;
			
			case "LSC_inside":
				SetWeatherScheme("LSC_inside");
				SetMusicAlarm("music_LostShipsCity");
			break;
			
			case "underwater":
				SetSoundScheme("underwater");
				SetMusicAlarm("music_underwater");
			break;
			
			case "teno":
				SetWeatherScheme("land");
				SetMusicAlarm("music_teno");
			break;
			
			case "teno_inside":
				SetSoundScheme("teno_inside");
				SetMusicAlarm("music_teno_inside");
			break;
		}
	}
	SetStaticSounds(loc);
}

void SetStaticSounds (ref loc)
{
	if(IsEntity(loc) != true) return;
	string locatorGroupName = "locators.sound";
	if(CheckAttribute(loadedLocation, locatorGroupName) == 0) return;
	aref locatorGroup;
	makearef(locatorGroup, loc.(locatorGroupName));
	int locatorCount = GetAttributesNum(locatorGroup);
	if(locatorCount <= 0) return;
	string locatorName, locatorType;
	int locatorNameLength;

	for(int i = 0; i < locatorCount; i++)
	{
		aref locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		locatorNameLength = strlen(locatorName);
		locatorType = strcut(locatorName, 0, locatorNameLength-3);
		if ((locatorType == "nightinsects")||(locatorType == "torch"))
		{
			if (Whr_IsDay() && loc.type != "Dungeon" && loc.type != "cave" && loc.type != "fort_attack") continue;
   		}
		if (locatorType == "shipyard")
		{
			if (Whr_IsNight()) continue;
   		}
		if (locatorType == "church")
		{
			if (Whr_IsNight()) continue;
   		}
		if (locatorType == "windmill")
		{
			continue;
   		}

		//trace("Create 3D Sound <"+locatorType+ "> for locator <"+locatorName+ "> into pos:("+locator.x+","+locator.y+","+locator.z+")" );
		SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, locatorType, SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
	
}

void SetSchemeForSea ()
{
	ResetSoundScheme();

	// AddSoundScheme("sea");
	if (Whr_IsNight())
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_night_storm");
			SetMusic("music_storm");
		}
		else 
		{ 
			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				SetMusic("music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic("music_sea_day");
				else SetMusic("music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_night_rain");
			}
			else
			{
				AddSoundScheme("sea_night");
			}
		}
	}
	else // if Whr_IsDay
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_day_storm");
			SetMusic("music_storm");
		}
		else 
		{ 
   			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				SetMusic("music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic("music_sea_day");
				else SetMusic("music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_day_rain");
			}
			else
			{
				AddSoundScheme("sea_day");
			}
		}
	}
	ResumeAllSounds();
}

void SetSchemeForMap ()
{
	ResetSoundScheme();
	AddSoundScheme("sea_map");
	SetMusic("music_map");
	ResumeAllSounds();
	bFortCheckFlagYet = false; //eddy. ������ ���� ������������� ������ �����
}

// MUSIC
int musicID = -1;
int oldMusicID = -1;
int boardM = -1;
string musicName = "";
string oldMusicName = "";
void SetMusic(string name)
{
	if (pchar.location == "UnderWater") return; //�� ������ ����� ��� �����
	InitSound();
	//Trace("SETTING MUSIC: " + name);

	if (name == musicName)
	{
		SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
		return;
	}

	//Trace("SetMusic : "+name);
	if (oldMusicID >= 0)
	{
		SendMessage(Sound, "ll", MSG_SOUND_RELEASE, oldMusicID);
		oldMusicID = -1;
	}

	if (musicID >= 0)
	{
		SendMessage(Sound, "lll", MSG_SOUND_STOP, musicID, MUSIC_CHANGE_TIME);
		oldMusicID = musicID;
	}

	//int silenceTime = 20000 + MakeInt(frnd() * MUSIC_SILENCE_TIME);
	//musicID = SendMessage(Sound, "lslllllll", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, MUSIC_CHANGE_TIME, silenceTime);
	//SendMessage(Sound, "llf", MSG_SOUND_SET_VOLUME, musicID, 1.0);
	// fix �������� - ��� ��������� �����
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, 0, MUSIC_CHANGE_TIME, 1.0);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, MUSIC_CHANGE_TIME);
	
	oldMusicName = musicName;
	musicName = name;
}

void FadeOutMusic(int _time)
{
    //#20180920-05
    if(_time < 100)
        _time *= 1000;
	if (musicID >= 0)
	{
		StopSound(musicID, _time);
		musicID = -1;
		musicName = "";
	}
}

// RELOAD
void PauseAllSounds()
{
	//Trace("PauseAllSounds");
	SendMessage(Sound,"lll",MSG_SOUND_STOP, 0, SOUNDS_FADE_TIME);
}

void ResumeAllSounds()
{
	//Trace("ResumeAllSounds");
	SendMessage(Sound,"lll",MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
}

// OLD VERSIONS
int PlaySoundDist3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

int PlaySoundLoc3D(string name, float x, float y, float z)
{
	return Play3DSoundCached(name, x,y,z);
}

int PlaySound3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

void Sound_SetVolume(int iSoundID, float fVolume)
{
	SendMessage(Sound, "llf", MSG_SOUND_SET_VOLUME, iSoundID, fVolume);
}

int PlaySound(string name)
{
	return PlayStereoSound(name);
}

int PlayVoice(string name)
{
	return PlayVoiceSound(name);
}

int PlaySoundComplex(string sSoundName, bool bSimpleCache, bool bLooped, bool bCached, int iFadeTime)
{
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY,VOLUME_FX,sSoundName,SOUND_WAV_3D,bSimpleCache,bLooped,bCached,iFadeTime);
}

void StopMusic()
{
}

void PlayMusic(string n)
{
}
//--------------------------------------------------------------------
// Sound Section
//--------------------------------------------------------------------
object Sound;

int alarmed = 0;
int oldAlarmed = 0;
bool seaAlarmed = false;
bool oldSeaAlarmed = false;
//Boyer add #20170328-02
string battleMusicScheme = "music_bitva";

void SetBattleMusicAlarm(string name)
{
    battleMusicScheme = name;
}
//End Boyer add

void SetMusicAlarm(string name)
{
	//Log_TestInfo("SetMusic: " + name);
	if (alarmed == 0)
	{
		SetMusic(name);
	}
	else
	{
  		SetMusic("music_bitva");
        //Log_TestInfo("SetMusicAlarm: music_bitva");
		if (LAi_boarding_process != 0)
		{
			/*if (!CheckAttribute(loadedLocation, "CabinType") && !bBettaTestMode)//pchar.location != "CaptainCabine" && pchar.location != "CaptainCabineBig")
			{   // TO_DO ������� �������� � �������� - ��������� ���� (���������� ������ �� ����)
				//Trace("�������� ���� ��������");
				abordageSoundID = PlayStereoSoundLooped("Abordage");
				boardM = 1;
			}*/
			if (!CheckAttribute(loadedLocation, "CabinType"))
			{
				boardM = 1; // ����� ������� ���� � �����
			}
		}
	}
}

void Sound_OnAllarm()
{
	Sound_OnAlarm(GetEventData());
}

int abordageSoundID;

void Sound_OnAlarm(bool _alarmed)
{
	alarmed = _alarmed;
	if (alarmed == oldAlarmed)
		return;

	if (alarmed != 0)
	{ //alarm on!
		if (loadedLocation.id == "shore67") SetMusic("music_q_battle");
		else SetMusic("music_bitva");
	}
	else
	{ //alarm off
		SetMusic(oldMusicName);
	}
	oldAlarmed = alarmed;
}

void Sound_OnSeaAlarm(bool _seaAlarmed)
{
	seaAlarmed = _seaAlarmed;
	if (seaAlarmed == oldSeaAlarmed)
		return;

	if (seaAlarmed)
	{ //alarm on!
		SetMusic("music_sea_battle");
	}
	else
	{ //alarm off
		SetMusic(oldMusicName);
	}
	oldSeaAlarmed = seaAlarmed;
}

// set music without any checks
void Sound_OnSeaAlarm555(bool _seaAlarmed, bool bHardAlarm)
{
	if (bHardAlarm) { oldSeaAlarmed = !_seaAlarmed; }
	
	Sound_OnSeaAlarm(_seaAlarmed);
}

void InitSound()
{
	//Trace("InitSound");
	if (!IsEntity(&Sound))
	{
		CreateEntity(&Sound, "Sound");
		SetEventHandler("eventAllarm", "Sound_OnAllarm", 0);
	}
	//SendMessage(Sound,"lf",MSG_SOUND_SET_MASTER_VOLUME,1.0);
}

void ResetSound()
{
	// fix -->
	if (musicID > 0)
	{
		StopSound(musicID,0);
	}
	if (oldMusicID > 0)
	{
		StopSound(oldMusicID,0);
	}
	ResetSoundScheme();
	// fix <--
	StopSound(0,0);
	ReleaseSound(0);
	musicName = "";
	oldMusicName = "";
	musicID = -1;    //fix boal �� ���� ������� ��
    oldMusicID = -1;
}

void LoadSceneSound()
{
	int i = FindLoadedLocation();
	if (i != -1)
		SetSchemeForLocation(&Locations[i]);
}

void ReloadStaticSound()
{
	int i = FindLoadedLocation();
	if (i != -1)
		SetStaticSounds(&Locations[i]);
    else {
        if(bSeaActive) {
            if(Whr_IsStorm()) SetSchemeForSea();
            Ship_RecreateStaticSounds();
        }
    }
}
//#20180815-03
void SoundEnviron(int rvbEnviron, int rSetting, float fWet);
{
    float cHall = 1.0;

    SendMessage(&Sound, "lllf", MSG_SOUND_ENVIRONMENT, RVB_I_MUSIC, RVB_CONCERTHALL, cHall);
	SendMessage(&Sound, "lllf", MSG_SOUND_ENVIRONMENT, RVB_I_EFFECTS, rSetting, fWet);
}