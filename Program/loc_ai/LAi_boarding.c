//  ������ ��������, ����������� boal 28.04.06
#define BRDLT_SHIP	0
#define BRDLT_FORT	1

#define BRDLT_MAXCREW 44

#define LOCINITBRD_DEFAULTLOCATION "BOARDING_U_H_CS_T12"
#define LOCINITBRD_DEFAULTLOCATION_FORT "Any_fort_1"

#define MAX_GROUP_SIZE   13

bool   IsFort = false; 
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;


int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; //boal
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; //sd

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; //sd

ref    boarding_enemy;
object boarding_adr[4];
float  boarding_exp = 0;
float  boarding_player_hp = 40;
float  boarding_enemy_hp = 40;
int    boarding_echr_index = -1;
int    boarding_erank = 10;
bool   LAi_boarding_process = false;
bool   Surrendered = false; // ����� � ����

int inside_ecrew_1, inside_ecrew_2;
//������ ��������
bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}

//�������� �������� ��� �������� � �������
string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;// boal 110804 fix ������ �����
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return Locations[locID].image;
			}
		}
	}
	return "loading\battle_" + rand(24) + ".tga";
}

//������ ������� � ������� ����������
void LAi_StartBoarding(int locType, ref echr, bool isMCAttack)
{
    SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // ��������� �������� ���������, ���� ����� � ����.
	//ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	
	bQuestCheckProcessFreeze = true;//fix
	
	EmptyAbordageCharacters();
	// NK -->
	if(locType == BRDLT_FORT)
    {
        isMCAttack = true;
        IsFort = true;
    }
	else
    {
        IsFort = false;
    }
    // NK <--
	//��������� ���������� �� �������� ������
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	//�������� ���������
	DeleteBattleInterface();
	InitBattleLandInterface();
	//StartBattleLandInterface();
	//�������� ������ �����
	boarding_echr_index = sti(echr.index);
	//��������� ����������� ������
	ref mchr = GetMainCharacter();
	int mclass = GetCharacterShipClass(mchr);
	int mcrew = GetCrewQuantity(mchr);
	
	// Saving enemy captain rank for future use in CalculateAppropriateSkills (Gray 12.02.2005)
	mchr.EnemyRank = echr.rank
	
	DeleteAttribute(pchar, "abordage_active");
	// boal ���� ������ 21.01.2004 -->
	Log_TestInfo("����� �� ������ " + mcrew);
	mcrew = GetWeaponCrew(mchr, mcrew);
	
	// boal 21.01.2004 <--
	int eclass = GetCharacterShipClass(echr);
	int ecrew = GetCrewQuantity(echr);
	int ecrewBak;

    Log_TestInfo("����� � ������� " + mcrew + " ������ " + ecrew);
    
    boarding_location_type = locType;
	// ����� � ���� -->
	bool ok = (TestRansackCaptain) && (boarding_location_type != BRDLT_FORT);
    if (!CheckAttribute(echr, "DontRansackCaptain")) //��������� �� �������
    {
    	if (CheckForSurrender(mchr, echr, 1) || ok) // 1 - ��� ���� ������ ���, �� ����� �� ������
    	{
    		echr.ship.crew.morale = 5;// ����� ������� � ��� ������ �����

    		if (mclass < eclass)
			{
				AddCrewMorale(mchr, ( 3 + 2*rand(eclass-mclass)));
			} 
			else
			{
				AddCrewMorale(mchr, 3);
			}
			SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // ��������� �������� ���������, ���� ����� � ����.
            //��������� ������� ���
			DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
			boarding_location = -1;
			
			// Saved value is not needed anymore... (Gray 14.02.2005)
			DeleteAttribute(GetMainCharacter(), "EnemyRank");
		    bQuestCheckProcessFreeze = false;//fix
		    
			//�������� ���������
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
            //����������� � ���������
            
			ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
			LaunchRansackMain(pchar, echr, "crew"); 
			// �� ���� ��������� LaunchRansackMain �� ����� ������ - ��� ������������� �� ������ - ��� ��� � ������� � ���� �������� - �� � ������������
			// �� ��� ������������ � ����������  crew - ��� ������ �����
    		LAi_boarding_process = false;  
			Event(SHIP_CAPTURED, "l", sti(echr.index));
    		return;
    	}
	}
	// ����� � ���� <--

	// MusketsShoot --> 
	float tmpDefence;
    if (CheckOfficersPerk(mchr, "MusketsShoot") && IsFort == false)
    {
        tmpDefence   = MakeFloat(GetSummonSkillFromName(echr, SKILL_DEFENCE)) / SKILL_MAX;
		ecrewBak = makeint(mcrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(mchr, "EmergentSurgeon"), 1.0, 0.75));//aw013 
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0); 
		if (ecrewBak > ecrew) ecrewBak = ecrew;//aw013 
		PlaySound("INTERFACE\_musketshot_" + rand(3) + ".wav");
		ecrew = ecrew - ecrewBak; 
		Log_SetStringToLog("��������� ������ ����� " + ecrewBak + " ������� ������� ����������."); 
	} 
	if (CheckOfficersPerk(echr, "MusketsShoot") && IsFort == false) 
	{ 
		tmpDefence  = MakeFloat(GetSummonSkillFromName(mchr, SKILL_DEFENCE)) / SKILL_MAX; 
		ecrewBak = makeint(ecrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(echr, "EmergentSurgeon"), 1.0, 0.75));//aw013 
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0); 
		if (ecrewBak > mcrew) ecrewBak = mcrew;//aw013 
		PlaySound("INTERFACE\_musketshot_" + rand(3) + ".wav");
		mcrew = mcrew - ecrewBak; 
		Log_SetStringToLog("��������� ������ ����� " + ecrewBak + " ������� ����� �������."); 
		Statistic_AddValue(mchr, "DeadCrewBoard", ecrewBak); 
    }
    // MusketsShoot <--
    
	if(ecrew < 0) ecrew = 0;
	if(mcrew < 0) mcrew = 0;
	boarding_erank = sti(echr.rank);

	// ���� ��� �������
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;
	
	//���������� ���������� ��� ������ - ���� ����� ������
	GetBoardingHP(mchr, echr, &boarding_player_hp, &boarding_enemy_hp);
	
	//���������� ���� ������� ��� ��������
	boarding_location = -1;

	string deckID = "";
	isMCAttack   = true;// boal 110804 fix ������ �����
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID == "")
	{
		if(locType == BRDLT_FORT)
		{
			deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
		}else{
			deckID = LOCINITBRD_DEFAULTLOCATION;
		}
		locID = FindLocation(deckID);
	}
	if (locID < 0)
	{   // �������������� ��������
		Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");
		// Saved value is not needed anymore... (Gray 14.02.2005)
		DeleteAttribute(GetMainCharacter(), "EnemyRank");
	    bQuestCheckProcessFreeze = false;//fix
		    
		if(boarding_location_type == BRDLT_SHIP)
		{
            ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
            SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // ��������� �������� ���������, ���� ����� � ����.
			LaunchRansackMain(GetMainCharacter(), echr, "captain");	  // �� ���� ��������� LaunchRansackMain �� ����� ������ - ��� ������������� �� ������
            LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index)); // to_do can be harmfull
		}
		else
		{
			if (boarding_location_type == BRDLT_FORT)
			{
                ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
                SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // ��������� �������� ���������, ���� ����� � ����.
				Event(FORT_CAPTURED, "l", sti(echr.index));
				echr.Ship.Crew.Quantity = 10 + rand(350); // ���� (������� ��������)
                LaunchFortCapture(echr);
                LAi_boarding_process = false;
			}else{
				Trace("Boarding: unknow boarding location type");
			}
		}
		return;
	}

	pchar.abordage = 0;
	//���������� ������� ������
	boarding_enemy = echr;
	//������������ ���������� ������� �� �������
	int maxcrew = MAX_GROUP_SIZE;
	
    if(CheckAttribute(&Locations[locID], "boarding.locatorNum"))
	{
		maxcrew = sti(Locations[locID].boarding.locatorNum);
	}
    //  ������������ �� ������ ������� ���
    int iMaxcrew  = func_min(mclass, eclass); // ����� 1 - ���� ����� 7 - �����
    switch (iMaxcrew)
    {
        case 7:
			iMaxcrew = 4;
		break;
		case 6:
			iMaxcrew = 5;
		break;
		case 5:
			iMaxcrew = 6;
		break;
		case 4:
			iMaxcrew = 7;
		break;
		case 3:
			iMaxcrew = 8;
		break;
		case 2:
			iMaxcrew = 11;
		break;
		case 1:
			iMaxcrew = 13;
		break;
    }
    if (iMaxcrew < maxcrew) maxcrew = iMaxcrew;
    
	if (boarding_location_type == BRDLT_SHIP && eclass != 7)  // �� ������� ����� ���
	{
    	boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	// boal check -->
	if(maxcrew > BRDLT_MAXCREW)
	{
	    maxcrew = BRDLT_MAXCREW;
	}
	// boal check <--

	//��������� ������

	// fort -->
	// boal 21.01.2004 -->
	int cn, j, compCrew;
    ref officer;
    if(IsFort)
    {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); // ���� ��� �����, �� �����
        boarding_player_base_crew = mcrew;// ���� ���� ��������
        //������������ ���������� �������
        Log_TestInfo("�����: �� ������� mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
    }
    // boal 21.01.2004 <--
    // fort <--
	
	float rel;
	if(mcrew > ecrew)
	{
        // ��� ����c boal
        boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus(mcrew, ecrew);
		if (boarding_player_hp > 1000) boarding_player_hp = 1000;
		
        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
		// boal 30.01.2004 -->
		boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus(mcrew, ecrew);
		if (boarding_enemy_hp > 1500) boarding_enemy_hp = 1500;
		// boal 30.01.2004 <--
        if(ecrew > maxcrew)
		{       
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;

    Log_TestInfo("����� ���������� mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
	//Jason: ������������� ����� ����� �� ������ �������
	// ������� ������ ��������� ��� ��������� �� ����������, �� ������� 15 ��������� HP � ������ ����������, �� ������ ������� ����� ���������� �����, �� ��� ����������� �� ������������� ��� ���������� ������������ ��� �����
	inside_ecrew_1 = makeint(ecrew*0.3+0.5); // 30 ��������� - ������ ������� �������
	inside_ecrew_2 = makeint(ecrew*0.2+0.5); // 20 ��������� - ������ ������� �������
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	//���������� ��������
	boarding_officers = 0;
	int passq;
	for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0)
		{
            // boal 05.09.03 offecer need to go to abordage -->
		    // to_do if(makeint(Characters[GetOfficersIndex(GetMainCharacter(), i)].AbordageMode) == 0) continue;	// �� �����
			// boal 05.09.03 offecer need to go to abordage <--
			boarding_officers = boarding_officers + 1;   
			LAi_SetOfficerType(&characters[passq]);
		}
	}
  
    //boarding_player_crew_per_chr = (curplayercrew + boarding_officers)/(mcrew + boarding_officers);
    boarding_player_crew_per_chr = makefloat(boarding_player_base_crew / makefloat(mcrew)); //���������� ����
	// START MOD Code by Stone-D : 30/07/2003
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); // Stone-D : For calculating final crew numbers
	// END MOD Code by Stone-D : 30/07/2003

	//�������� ������ � �������� ������������ ����� � �������� ������
	LAi_SetCurHPMax(mchr);
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group    = mchr.location.group;
	boarding_adr[0].locator  = mchr.location.locator;
	for(i = 1; i <= MAX_NUM_FIGHTERS; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		//Boyer mod
		int k = i % 3;
		if(k==0) k = 3;
		if(idx < 0)
		{
			//Boyer mod
			boarding_adr[k].location = "";
			boarding_adr[k].group	= "";
			boarding_adr[k].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[k].location = Characters[idx].location;
		boarding_adr[k].group	= Characters[idx].location.group;
		boarding_adr[k].locator  = Characters[idx].location.locator;
	}
	//��������
	LAi_boarding_process = true;
	LAi_LoadLocation(deckID, locType);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//��������� ������� ��������
void LAi_LoadLocation(string locationID, int locType)
{
//	Log_TestInfo("LoadLocation()");
	ReloadProgressStart();
	//���� �������
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
    Dead_Char_num = 0; // boal dead body
	if(locIndex >= 0)
	{
		//������������� �������� ���������
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		// boal random place to star battle 28/11/03 -->
		int locNum[20];
		int locI;
		int maxLocators = 2;
		
		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		// ����������� ������� �� ������
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
		    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
		}

		mchr.location.locator = sLocType + locNum[locI];
		// ��� ����� ���������
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
		    mchr.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		// boal random place to star battle 28/11/03 <--
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ // �� ������ ����, ���� �����
	        //������������� ��������, ���� ����� ����
	        int logined = 0;
			//Boyer mod
			for(int i = 1; i <= MAX_NUM_FIGHTERS ; i++)
			{
				int idx = GetOfficersIndex(mchr, i);
				if(idx < 0) continue;
				//Log_TestInfo("Load Off " + Characters[idx].id);
				if (logined > maxLocators) break;

	            // boal 05.09.03 offecer need to go to abordage -->
//			    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// �� �����
				// boal 05.09.03 offecer need to go to abordage <--
				DeleteAttribute(&Characters[idx], "location");
				//Characters[idx].location = locationID;
				// boal ���� ��������� � ������ -->
				Characters[idx].location.loadcapture = true;
			    // boal ���� ��������� � ������ <--
				//Characters[idx].location.group = "rld";
				// boal random place to star battle 28/11/03 -->
				iLoc = rand(5);//3

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(5);//3
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				    //Boyer mod to fix stack error
				    okLoc = true;
				}
				locI++;
			    locNum[locI] = iLoc;
				//Characters[idx].location.locator = sLocType + locNum[locI];
				// boal random place to star battle 28/11/03 <--
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;
				
			}
			boarding_player_crew = boarding_player_crew - logined;
		}
		//������������� � �������
		boarding_location = locIndex;
		if(LoadLocation(&Locations[boarding_location]))
		{
			//������ � �������� � ����� boal -->
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}  
			//����������� ����������
			LAi_SetBoardingActors(locationID);
			// boal <--
			//������� �����
			SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			//�������� ������
			dialogDisable = true;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
	pchar.OfficerAttRange = 100.0;//������� ������������ �� ������
}

//������������� � ��������� �������
void LAi_ReloadBoarding()
{
//	Log_TestInfo("ReloadBoarding()");
	//�������� �������
	dialogDisable = false;
	//�������� ���������� �������
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}
	
	csmHideLootCollectorBox(true);
	
	//���������� �������� ��� ���������
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	//������ ������ � ���������
	CreateEntity(&boarding_fader, "fader");
	
	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(nextDeck)].image);
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	//��������� �������
 //ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void LAi_ReloadEndFade()
{        
	bool bCaptanSurrender = false;
	//��������� ��������� �������
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	//��������� ����������� ����������� ����������
	bool canReload = true;
	
	// Jason: �� ���� �������� � ���������� �������� ����� ����� ��������� ����� �2, �� ���.������ ��������, ����� �������������� �� ����� ��������.
	if(CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		boarding_enemy_crew = inside_ecrew_1*2; // ����������� ������ ����� ����� �����
	}
	else boarding_enemy_crew = inside_ecrew_2*2; // ����������� ������ ����� ����� �����
	
	if(IsFort)
    {
		if(CheckAttribute(&Locations[boarding_location], "insidenext")) boarding_enemy_crew = inside_ecrew_2*2;
		else boarding_enemy_crew = inside_ecrew_1*2;
	}
	//if(boarding_enemy_crew <= 0) canReload = false;
	if(!CheckAttribute(&Locations[boarding_location], "boarding.nextdeck")) canReload = false;
	if(Locations[boarding_location].boarding.nextdeck == "") canReload = false;
	
 	if(canReload) //Jason ���������� �������
	{
		Trace("Boarding: go to inside location");
		LAi_LoadLocation(Locations[boarding_location].boarding.nextdeck, -1); 
	}
    else
    {
		if (CheckAttribute(boarding_enemy, "ShipCabinLocationId"))
		{
            if (!CheckAttribute(boarding_enemy, "DontRansackCaptain")) //��������� �� �������
	        {
	            Surrendered = (Surrendered) || (TestRansackCaptain);
	    		if (Surrendered && (boarding_location_type == BRDLT_SHIP))
	    		{
	    		    bCaptanSurrender = true;    // ��� ��� �� ������ ������ �����, ������ ������ ����
	   			}
	    	}
    		if (!bCaptanSurrender)
    		{
				boarding_enemy_crew = 1;
				if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image"))
				{
					SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image);
				}
				LAi_LoadLocation(boarding_enemy.ShipCabinLocationId, -1);
				DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); // ���� �� �����������
				return;
			}
	}

  		if (CheckAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender")) // ��������� ����� � ���� ����
		{
		    DeleteAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender"); // ������
		    bCaptanSurrender = true;
		}
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // ��������� �������� ���������, ���� ����� � ����.
		//��������� ������� ���
		DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
		boarding_location = -1;
		//������������� ������� ������

		float crew = boarding_player_crew * boarding_player_crew_per_chr; // �������� ������� - ��� �� �������� �� ������ ������
		// boal 22.01.2004 -->
		ref mchar       = GetMainCharacter();
		float fDefenceSkill = 0.9 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;
		int deadCrew    = makeint((boarding_player_base_crew - crew) / fDefenceSkill + 0.3 + AIShip_isPerksUse(CheckOfficersPerk(mchar, "EmergentSurgeon"), 0.0, 0.9)); // ����� ��������
		int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); // ��� ������
		float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);
		int iTemp;
		if (leaderSkill < 1) leaderSkill = 1; //fix
		
		// ������ �������� -->
		iTemp = deadCrewWOMedic - deadCrew;
		if(CheckShipSituationDaily_GenQuest(pchar) > 1) 
		{
			if(iTemp > 0) 
			{
				deadCrew += deadCrewWOMedic; // ���� �������� - ������� �� �������, ��������� �� ������������
			}	
		}	
		else
		{
			if (iTemp > 0)
			{
				if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < iTemp)
				{
					deadCrewWOMedic = iTemp - GetCargoGoods(mchar, GOOD_MEDICAMENT); // ������ �� ���
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, GetCargoGoods(mchar, GOOD_MEDICAMENT)); // ��� �����
					deadCrew += deadCrewWOMedic; // ������ ������
					Log_Info("��-�� �������� ������������ �� ��� ������ " + deadCrewWOMedic + " ��������");
				}
				else
				{
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, iTemp);
					if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < 16)
					{
						Log_Info("�� ������� " + mchar.Ship.Name + " �������� ���� ������������");
					}
				}
			}
			// ������ �������� <--
			// Saved value is not needed anymore... (Gray 14.02.2005)
			DeleteAttribute(mchar, "EnemyRank");
			bQuestCheckProcessFreeze = false;//fix
			
			RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, deadCrew);
			
			crew = boarding_player_base_crew - deadCrew; // �������� � �������
			Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
			Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
			AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); //������ ������
			AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));
						
			// ����� ��� ������ ������
			if (deadCrew > makeint(crew+0.3)) // ������� ������, ��� ������
			{
				AddCrewMorale(mchar, sti(-20 / leaderSkill));
			}
			else
			{  //������, ���� ������ ����
				AddCrewMorale(mchar, sti(leaderSkill));
			}

			// boal 22.01.2004 <--
			SetCrewQuantityOverMax(GetMainCharacter(), MakeInt(crew + 0.3)); // ������ ���� �� ��� �������� �������
			Log_TestInfo("----- � ����� ����� " + crew +" �������� ---");
			//������������� ������� ���������
			crew = 0;// ����� ��� ����? ��� �����! boarding_enemy_base_crew*(0.1 + rand(20)*0.01);
			if (boarding_echr_index >= 0)
			{
				SetCrewQuantity(&Characters[boarding_echr_index], MakeInt(crew + 0.3));
				boarding_echr_index = -1;
			}

			//�������� ����
			//AddCharacterExp(GetMainCharacter(), MakeInt(boarding_exp));
					
			//�������� ���������
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
			//���������� ������
			ref mchr = GetMainCharacter();
			mchr.location         = boarding_adr[0].location;
			mchr.location.group   = boarding_adr[0].group;
			mchr.location.locator = boarding_adr[0].locator;
			
			for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
			{
				int idx = GetOfficersIndex(GetMainCharacter(), i);
				//Boyer mod
				int k = i % 3;
				if(k==0) k = 3;
				if(idx < 0) continue;
				Characters[idx].location			= boarding_adr[k].location;
				Characters[idx].location.group	= boarding_adr[k].group;
				Characters[idx].location.locator = boarding_adr[k].locator;
			}
			//����������� � ���������
			LAi_boarding_process = false;
			// START MOD Code by Stone-D : 27/07/2003
			if (bCaptanSurrender)
			{
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"), 4.0, 8.0));
				LAi_SetCurHPMax(boarding_enemy);  // �����, ���� ��� �����!!!
				SetCrewQuantity(boarding_enemy, MakeInt(boarding_enemy_base_crew*(rand(20)*0.01))); // ��� ��� �����, �� ����� ������� ����������
				LaunchRansackMain(pchar, boarding_enemy, "captain"); //������� � ����
				LAi_boarding_process = false;
				Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
				return;
			}
			// END MOD Code by Stone-D : 27/07/2003
			if(boarding_location_type == BRDLT_SHIP)
			{       
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),5.0, 10.0));
				// ������ ��� ������ �� �����, �������� ����� "" LAi_SetCurHP(boarding_enemy, 0.0); // ����, ���� �� ����� ������ �� ���
				LaunchRansackMain(pchar, boarding_enemy, ""); //�� ������
				LAi_boarding_process = false;	 
				Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
				return;
			}
			if(boarding_location_type == BRDLT_FORT)
			{
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),7.0, 14.0));
				Event(FORT_CAPTURED, "l", sti(boarding_enemy.index));
				boarding_enemy.Ship.Crew.Quantity = 10 + rand(350); // ���� (������� ��������)
				LaunchFortCapture(boarding_enemy);
				LAi_boarding_process = false;
				return;
			}
			Trace("Boarding: unknow boarding location type");
			Log_TestInfo("Boarding - unknown boarding location type : " + boarding_location_type);
		}
	}
}

//��������� ���������� �� ��������� ������
#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
    //Log_Testinfo("LAi_BoardingGroupKill boardM = " + boardM);
	if (boardM == 1)
	{
	//	Trace("��������� ���� ��������");
		//ResetSound();
		ResetSoundScheme(); //���� ������ ������ Scheme, ����� �������� ����� �� �������, �������, � ������ - �� �����
		//StopSound(abordageSoundID, 0);
		SetSoundScheme("deck"); // ������� �����
		SetMusic("music_bitva");
		boardM = -1;
		//Log_Testinfo("��������� ���� �������� " + abordageSoundID);
	}
	Surrendered = CheckForSurrender(GetMainCharacter(), boarding_enemy, 2); // �������� ����� � ����, ����� ������ 2 - ������ ���� ������
	
	if (csmCA(pchar, "CSM.LootCollector.Enable") && loadedLocation.type != "boarding_cabine")
	{
		pchar.CSM.LootCollector.CanBeRun = true;
		csmLootCollector();
	}
	PostEvent("csmEvent_RefreshReload", 100);
    //#20171218-01 Re-enable fast action for cabin enter during boarding
    BattleInterface.LAi_ActivateReload = true;
	SetEventHandler("Control Activation","LAi_ActivateReload",1);
	Log_SetActiveAction("Reload");
	//����� �����
	ref mchr = GetMainCharacter();
	SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", 0);
	
	// sd -->
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	// sd <--
	
	//����� �������� ������� � ����
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if(!LAi_IsDead(chr) && !CheckAttribute(chr,"AboardFantomMush")) // boal && sd �� ����� ������� ��� ��������
				{
					if(chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						//LAi_tmpl_stay_InitTemplate(chr);  // 05.02.08 ������� ��������� ����, ��� � �� ������ �� �� ������� ������ - ������� ��� �� ��������, ��� ����� ����� !
						//LAi_SetStayType(chr); // � ��� ��� �� ����� !!  <-- ugeen
						if (!IsOfficer(chr)) LAi_SetHuberStayType(chr); //����� �� ������, ���-����� �������� ! ����� ���������� �� ������
					}
				}
				/*
				// Fix ������� ������� ! - �������, �������
				if(chr.model.animation == "mushketer" && !IsOfficer(chr)) //���������� ������� � ������
				{
                    ChangeCharacterAddress(chr, "none", "");
				}
				*/
			}
		}
	}
	// Jason: ���������� ������ �������� � ���������� ��������� ������
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); // ����� ������� ����������
	if (CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 4: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 5: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: Locations[boarding_location].boarding.nextdeck = ""; break;
		}
	}
	if (IsFort && Locations[boarding_location].boarding.nextdeck == "Boarding_bastion")
	{
		Locations[boarding_location].boarding.nextdeck = "Boarding_bastion"+(drand(1)+1);
	}
	// END MOD Code by Stone-D : 01/08/2003 -->
	Log_TestInfo("New boarding_player_crew: " + boarding_player_crew);
	Log_TestInfo("Next Location: " + Locations[boarding_location].boarding.nextdeck);
    Log_TestInfo("Enemy ship class: " + eclass);
	// END MOD Code by Stone-D : 01/08/2003 <--
}

//��������� ���������� �� ��������� ������
void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	if (CheckAttribute(pchar, "GenQuest.CannotReloadBoarding")) return; // Jason
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	//#20171218-01 Re-enable fast action for cabin enter during boarding
    DeleteAttribute(&BattleInterface, "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}

//���������� ���������� ��� ���
void LAi_SetBoardingActors(string locID)
{
    int    limit, i, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	int    mclass = GetCharacterShipClass(GetMainCharacter());
	int    eclass = GetCharacterShipClass(boarding_enemy);
	ref    mchr = GetMainCharacter(); // boal star with new loc always
    int    locMChar;
    
	limit = MAX_GROUP_SIZE;
	// ��������� ������ ����� �� ������� :( ��������� ��� �� ���� �� ���� boal 01.01.05  +1 ������ ��� ��
	chr = &Locations[locIndex];
	
	if(CheckAttribute(chr, "boarding.locatorNum")) limit = sti(chr.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + " � " + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + " � " + boarding_enemy_crew_per_chr);

	//��������� ��������� �� �������
	// boal ������ ����� ������ ��������, ������� � ����� ������-�� ��� -->
	/*if (IsFort) // boal 21.01.05 �� ������ � ����... ������� � ������ ����� - ���������
	{
        for(i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(mchr, i);
			if(idx < 0) continue;
            // boal 05.09.03 offecer need to go to abordage -->
		    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// �� �����
		    // ������ ���� �������� ��� � ��� �������
		    chr = &Characters[idx];
		    PlaceCharacter(chr, mchr.location.group, mchr.location);
		}
	} */
	// boal ������ ����� ������ ��������, ������� � ����� ������-�� ��� <--
    string sLocType = "loc";
	// ����������� ������� �� ������
	if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
	{
	    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
	}
	if (!CheckAttribute(&Locations[locIndex], "CabinType"))
	{ // �� ������ �������� � �����
		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = LAi_GetBoardingModel(mchr, &ani);
			// boal star with new loc always  -->
			if (mchr.location.locator == (sLocType + i))
			{ // ������� �� ����, ��� ���� ������� ������ < 4 ������� ����� ������������� � �������� ���� � ����������.
	           locMChar = rand(3);
	           while (mchr.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);// 0-������ ��������, ���� �������� ���, � i != 0, �� �� ����� ����
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			// boal star with new loc always  <--

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

			boarding_player_crew = boarding_player_crew - 1;
			// boal ������ ��� � ���������� �������� -->
			//LAi_SetAdjustFencingSkill(chr, 3.0, 6.0);
			//LAi_AdjustFencingSkill(chr);

			// boal <--
			if (!IsFort)
			{
	            SetFantomParamAbordOur(chr);
			}
			else
			{
			    SetFantomParamFortOur(chr);
			}
			SetNewModelToChar(chr); //����� ����� �� ��, ��� �������
			chr.AboardFantom = true;
			AddCharHP(chr, boarding_player_hp); // �������� ����� � ������ � ��
			/*if (!bNewFantomGenerator)
	        {
				xhp = GetBoarding_player_hp(boarding_player_hp);
				LAi_SetHP(chr, xhp, xhp);
			}*/
			if (IsCharacterPerkOn(chr, "Ciras") && rand(4)==0)
			{
				string cirnum;
				switch (rand(4))
				{
					case 0: cirnum = "cirass1"; break;
					case 1: cirnum = "cirass1"; break;
					case 2: cirnum = "cirass2"; break;
					case 3: cirnum = "cirass3"; break;
					case 4: cirnum = "cirass4"; break;
				}
				chr.cirassId = Items_FindItemIdx(cirnum);
				Log_TestInfo("�������� "+chr.name+" ������� ������ "+cirnum);
			}
		}
		//������ ����� ���������� -->
		if (CheckOfficersPerk(mchr, "MusketsShoot") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 7;
			else iQty = 3;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{			
					model = LAi_GetBoardingMushketerModel(mchr);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(mchr.nation), 0, false));
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.AboardFantomMush = true;
					if (!IsFort) chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
			}
			if (!IsFort)
			{
	            SetMushketerParamAbordOur(chr);
			}
			else
			{
			    SetMushketerParamFortOur(chr);
			}
			AddCharHP(chr, boarding_player_hp); // �������� ����� � ������ � ��
		}
		//<-- ������ ����� ����������
	}
	//��������� ������
	if (sLocType == "loc")
	{
	    sLocType = "aloc";
	}
	else
	{
	    sLocType = "loc";
	}
	trace("sLocType = " + sLocType);
	if (HasSubStr(boarding_enemy.model,"trader_")) boarding_enemy.Ship.Mode = "Trade";
	for(i = 0; i < limit; i++) // <= �� loc0 .. loc4 = 5
	{
		if(boarding_enemy_crew <= 0) break;
		model = LAi_GetBoardingModel(boarding_enemy, &ani);
		if (i == 0 && CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt")) //������� �����
		{
		    chr = LAi_CreateFantomCharacterEx(model, ani, "rld", Locations[locIndex].boarding.Loc.Capt);
		}
		else
		{
			chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
		}

		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
		
		boarding_enemy_crew = boarding_enemy_crew - 1;
		// boal ������ ��� � ���������� �������� -->
		//LAi_SetAdjustFencingSkill(chr, 2.0, 6.0);
		//LAi_AdjustFencingSkill(chr);

		if (!IsFort)
		{
            SetFantomParamAbordEnemy(chr);
		}
		else
		{
            SetFantomParamFortEnemy(chr);
			//xhp = GetBoarding_enemy_hp(LAi_GetCharacterMaxHP(chr));
		}
		// �������� � �����!!! boal
		if (i == 0 && CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			ChangeAttributesFromCharacter(chr, boarding_enemy, true);
			chr.CaptanId = boarding_enemy.id; // ����� � ������� ���� ��   // to_do ��������� ��������
			boarding_enemy.CaptanId = boarding_enemy.id;
			chr.SuperShooter = true; // ����� ������� (����������� ������ ����, �� ���������, ���� ��� � ������� ����)
			if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
			SetCharacterPerk(chr, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			if (CheckAttribute(chr,"Situation"))
			{
				if(bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
				else DeleteAttribute(chr,"Situation");
			}
			else
			{
				CaptainComission_GenerateSituation(chr);
				SetQuestAboardCabinDialog(chr); /// �������� �� �����
			}	
			// ���� ��� ����� ����������, �� ��� ���� ����, ���� �� ������� ������� � ����
			// 1.2.3 ������ ������
			//if (CheckCharacterPerk(chr, "Ciras"))
			//{
		    xhp = makeint((MOD_SKILL_ENEMY_RATE*2+sti(chr.rank))/10.0);

		    if (xhp > 0)
		    {
		        if (xhp >= 5) xhp = 5;
		        // �������� � 3  � 4 �������� (������)
		        if (xhp == 3)
				{
					xhp = 4;
				}
				else
				{
				    if (xhp == 4) xhp = 3;
				}
				model = "cirass" + xhp;
				chr.cirassId  = Items_FindItemIdx(model);
				Log_TestInfo("�� �������� ������ " + model);
		    }
			//}
		}
		SetNewModelToChar(chr); //����� ����� �� ��, ��� �������
		string weaponID = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
		aref weapon;
		Items_FindItem(weaponID, &weapon);
		chr.chr_ai.fencingtype = weapon.FencingType;
		chr.AboardFantom = true;
		AddCharHP(chr, boarding_enemy_hp); // �������� ����� � ������ � ��
		if (IsCharacterPerkOn(chr, "Ciras") && rand(4)==0)
		{
			string cirnum1;
			switch (rand(4))
			{
				case 0: cirnum1 = "cirass1"; break;
				case 1: cirnum1 = "cirass1"; break;
				case 2: cirnum1 = "cirass2"; break;
				case 3: cirnum1 = "cirass3"; break;
				case 4: cirnum1 = "cirass4"; break;
			}
			chr.cirassId = Items_FindItemIdx(cirnum1);
			Log_TestInfo("�������� "+chr.name+" ������� ������ "+cirnum1);
		}
	}
	//������ ��������� ���������� -->
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		if (!CheckAttribute(&Locations[locIndex], "CabinType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 7;
			else iQty = 3;	
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(boarding_enemy);		
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(boarding_enemy.nation), 0, false));
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
			}
			if (!IsFort)
			{
				SetMushketerParamAbordEnemy(chr);
			}
			else
			{
				SetMushketerParamFortEnemy(chr);
			}
			AddCharHP(chr, boarding_enemy_hp); // �������� ����� � ������ � ��			
		}
	}
	//<-- ������ ��������� ����������
	//�������� ������� ��� 2 ������
	LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}

//�������� ������
void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if(group != LAI_GROUP_BRDENEMY) return;
	// �������� ��� �������� (������� ���������� ��� ������ � sound.c)

	PostEvent("LAi_event_boarding_EnableReload", 1000);
}

//�������� ��� ����������� ���������
string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;
	
	
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
    {
        model = GetRandSkelModel();
		ani = "man";
		return model;
    }	
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelModeClassic"))
    {
        model = GetRandSkelModelClassic();
		ani = "man";
		return model;
    }	
    if (CheckAttribute(rCharacter, "OZG") == true)
    {
        model = "OZG_" + (rand(8) + 1);
	    ani = "man";
		return model;
    }

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        // boal 290904 ����� ������ -->
        if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
        {
            model = GetRandSkelModel();
			ani = "man";
			return model;
        }
		if (CheckAttribute(rCharacter, "OZG") == true)
        {
            model = "OZG_" + (rand(9) + 1);
			ani = "man";
			return model;
        }
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //����� ������ �� ������ �������
        {
            atr = "boardingModel.enemy";
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            atr = "boardingModel.player";
        }
        // boal 290904 ����� ������ <--
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            atr = "boardingModel.merchant";
        }
		else
        {//boal <--
            atr = "boardingModel.enemy";
        }
	}
	
	if (iNation < 0) iNation = PIRATE;
	//eddy. ���������������� ������� ���� ���� ���������
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	Nations[iNation].boardingModel.player = "";
	Nations[iNation].boardingModel.enemy = "";
	Nations[iNation].boardingModel.merchant = "";

	aref models;
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "pirate_1";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	return model;
}

string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);
	
	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //����� ������ �� ������ �������
        {
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            iNation = PIRATE;
        }
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            iNation = PIRATE;
        }
		else
        {//boal <--
            iNation = sti(rCharacter.nation);
        }
	}
	
	if (iNation < 0) iNation = PIRATE;
	//eddy. ���������������� ������� ���� ���� ���������
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate") iNation = PIRATE;
	if(iNation == PIRATE)
	{
		model = GetPirateMushketerModel();
	}
	else
	{
		model = NationShortName(iNation) + "_mush_" + (rand(2)+1);
	}	
	return model;
}

// boal 03/08/06 ��������� ��������� ����� Stone-D �� 27/07/2003
bool CheckForSurrender(ref mchr, ref echr, int _deck)
{
    if(boarding_location_type == BRDLT_FORT) return false; // Forts don't surrender.
    
    if (GetPrisonerQty() > PRISONER_MAX) return false; // ����� ����� ������
    
	if (sti(echr.rank) > (50 - MOD_SKILL_ENEMY_RATE)) return false; //max ������� �����

	if (!IsCharacterPerkOn(mchr,"SeaDogProfessional")) //������� ����-��������
	{
		if (sti(mchr.rank) < (sti(echr.rank) - MOD_SKILL_ENEMY_RATE / 2))  return false; // 26/06/07 �������� �� ����
	}
    
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) return false; // 1 ����� �� ������� � ��������
	
	float fCrewRate = 0.5;  
	if (sti(echr.Nation) == PIRATE)
	{
		fCrewRate = 0.2;
	}
	else
	{
		if (CheckAttribute(echr, "Ship.Mode") && echr.Ship.Mode == "Trade") // �������� ������� �������
		{
			fCrewRate = 0.9; 
		}
	}
	
	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // ������� ���� � �������
	float ecrew = stf(GetCrewQuantity(echr));
	
	float fRep    = abs(REPUTATION_NEUTRAL - sti(mchr.reputation)) / 50.0; // ���������� � 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1  ��� ������
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromNameToOld(mchr, "Leadership") + GetSummonSkillFromNameToOld(mchr, "Grappling")) / 20.0;  // 0..10
	float eskill  = (GetCharacterSkillToOld(echr, "Leadership") + GetCharacterSkillToOld(echr, "Defence")) / 20.0;    // 0..10

    mcrew = mcrew * (mcrew * GetCrewExp(mchr, "Soldiers")) / (GetOptCrewQuantity(mchr) * GetCrewExpRate()); 
    ecrew = ecrew * (ecrew * GetCrewExp(echr, "Soldiers")) / (GetOptCrewQuantity(echr) * GetCrewExpRate());  // ��� ������, � ������ �����������
    mcrew = mcrew *(0.5 + mmorale);
    ecrew = ecrew *(0.5 + emorale); // ������ �  emorale - ��� ����
    
    mcrew = mcrew * (0.2 + mskill)*(0.05 + fRep)*fCrewRate;
    ecrew = ecrew * (0.2 + eskill);
	// ������� ����������� � ������  -->
    int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "")
    {
    	eShip = Group_GetLiveCharactersNum(sGroupID);
    }
    else
    {
    	eShip = 1;
    }
	// <--
	float fStep = 1;
	if (_deck == 2)
	{
		fStep = 1.4;
	}
    mcrew = mcrew * (1.0 + mclass / 20.0) * fStep; // ������� ������ ����������, �� ���� � �������
    ecrew = ecrew * (1.0 + eclass / 20.0);  // ����� ����� ������ ��������, ���� ����� ������
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);
    if (bBettaTestMode) // ����� ������ ������.��� � ��������
    {
    	Log_Info("Surrender Hero = "+ mcrew + "    Enemy = " + ecrew + " eShipQty = " + eShip);
    }
    if (mcrew > ecrew)
	{
		return true; // Yay! Surrender!
	}
	return false; // �� ������
}

// boal 03/12/05 ����� �������� �� ������� ��� - ���������, ���� - �������-->
string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
    string sLoc = "loc";
    
	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
	    sLoc = "aloc";
	}
	
    return sLoc;
}
// boal 03/12/05 <--
// CSM -->
#event_handler("csmEvent_RefreshReload", "csmRefreshReload");
void csmRefreshReload()
{
	if (!LAi_IsBoardingProcess() || !IsEntity(&loadedLocation))
	{
		csmDA(pchar, "CSM.LootCollector.CanBeRun");
		return;
	}

	if (loadedLocation.type == "boarding_cabine" && csmCA(pchar, "CSM.LootCollector.Enable"))
		csmDA(pchar, "CSM.LootCollector.CanBeRun");

	if (g_ActiveActionName == "" || g_ActiveActionName == "Nothing")
		Log_SetActiveAction("Reload");

	PostEvent("csmEvent_RefreshReload", 250);
}
// CSM <--