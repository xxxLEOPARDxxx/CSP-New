
int LAi_loginedcharacters[MAX_CHARS_IN_LOC];
int LAi_numloginedcharacters = 0;


bool LAi_CharacterLogin(aref chr, string locID)
{
	string func;
	//�������� ����� ������
	if(CheckAttribute(chr, "location") == false)
	{
		Trace("Character <" + chr.id + "> have not field [location]");
		return false;
	}
	if(chr.id == "0")
	{
		chr.location = "none";
		return false;
	}
	bool isLogin = false;
	if(chr.location == locID)
	{
		if(sti(chr.index) == nMainCharacterIndex) isLogin = true;
		if(CheckAttribute(chr, "location.stime") != false)
		{
			if(CheckAttribute(chr, "location.etime") != false)
			{
				//�������� ����� ������
				if(LAi_login_CheckTime(stf(chr.location.stime), stf(chr.location.etime))) 
				{
					isLogin = true;
				}
			}
			else 
			{
				isLogin = true;
			}
		}
		else 
		{
			isLogin = true;
		}
	}
	//��������� ��������������
	if(!LAi_IsBoarding)
	{
		if(CheckAttribute(chr, "location.follower") != false)
		{
			chr.location = pchar.location;
			chr.location.group = pchar.location.group;
			chr.location.locator = pchar.location.locator;
			isLogin = true;
			if(LAi_restoreStates)
			{
				LAi_SetCurHPMax(chr);
			}
		}
	}
	//�������� �� ������������� �������
	if(LAi_IsCapturedLocation)
	{
		if(GetMainCharacterIndex() != sti(chr.index))
		{
   			// boal fix fort officers -->
			if(!IsOfficer(chr))
			{
				if(CheckAttribute(chr, "location.loadcapture") == 0)
				{
					isLogin = false;
				}else{
					if(sti(chr.location.loadcapture) == 0)
					{
						isLogin = false;
					}
				}
			}
			// boal fix fort officers <--
		}
	}
	if(!isLogin) return false;
	//���� ���������� ������ ������������� �����, ����������� ������
	if(LAi_numloginedcharacters >= MAX_CHARS_IN_LOC)
	{
		Trace("LAi_CharacterLogin -> many logined characters in location > " + MAX_CHARS_IN_LOC);
		return false;
	}
	//������������� ����������� ����, ���� ����
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		chr.chr_ai.type = LAI_DEFAULT_TYPE;
	}
	if(CheckAttribute(chr, "chr_ai.tmpl") == false)
	{
		chr.chr_ai.tmpl = LAI_DEFAULT_TEMPLATE;
	}
	if(CheckAttribute(chr, "chr_ai.group") == false)
	{
		chr.chr_ai.group = LAI_DEFAULT_GROUP;
	}
	if(CheckAttribute(chr, "chr_ai.alarmreact") == false)
	{
		chr.chr_ai.alarmreact = LAI_DEFAULT_ALARMREACT;
	}
	if(CheckAttribute(chr, "chr_ai.grpalarmr") == false)
	{
		chr.chr_ai.grpalarmr = LAI_DEFAULT_GRPALARMR;
	}
	if(CheckAttribute(chr, "chr_ai.hp") == false)
	{
		chr.chr_ai.hp = LAI_DEFAULT_HP;
	}
	if(CheckAttribute(chr, "chr_ai.hp_max") == false)
	{
		chr.chr_ai.hp_max = LAI_DEFAULT_HP_MAX;
	}
	if(CheckAttribute(chr, "chr_ai.charge") == false)
	{
		chr.chr_ai.charge = LAI_DEFAULT_CHARGE;
	}
	/*if(CheckAttribute(chr, "chr_ai.energy") == false)
	{
		chr.chr_ai.energy = LAI_DEFAULT_ENERGY; // to_do to max
	}*/
	SetEnergyToCharacter(chr);  // boal
	
	//��������� ���������
	float hp = stf(chr.chr_ai.hp);
	float hpmax = stf(chr.chr_ai.hp_max);
	if(hpmax < 1) hpmax = 1;
	chr.chr_ai.hp_max = hpmax;
	if(hp > hpmax) hp = hpmax;
	if(hp < 0) hp = 0;
	chr.chr_ai.hp = hp;
	if(!actLoadFlag)
	{
		if(hp < 1)
		{
			if(CheckAttribute(chr, "location.norebirth") != false)
			{
				if(sti(chr.location.norebirth) != 0) return false;
			}
			//���� ���������� ���������
			chr.chr_ai.hp = hpmax;
			hp = hpmax;
			if (!CheckAttribute(chr, "location.rebirthOldName"))
			{
				SetRandomNameToCharacter(chr);
			}
			func = chr.chr_ai.type;
			chr.chr_ai.type = "";
			chr.chr_ai.tmpl = "";
			if(func != "")
			{
				func = "LAi_type_" + func + "_Init";
				call func(chr);
			}
		}
	}
	if(hp < 1) return false;
	//��������� ���������
	if(LAi_CheckCharacter(chr, "LAi_CharacterLogin") == false) return false;
	//���������� ����� ��� ��������
	//LAi_AdjustFencingSkill(chr);
	
	//������� ���������
	func = chr.chr_ai.type;
	bool res = true;
	if(func != "")
	{
		func = "LAi_type_" + func + "_CharacterLogin";
		res = call func(chr);
	}
	if(res == false) return false;
	//#20210221-01
	chr.isLogin = true;
	chr.chr_ai.login = true;
	LAi_AddLoginedCharacter(chr);

	/*if(CheckAttribute(chr, "quest.type"))
	{
		if(chr.quest.type == "trader")
		{
			if(!CheckAttribute(chr, "quest.questflag") || sti(chr.quest.questflag) == -1)
			{
				GenerateTraderQuests(chr);
			}
		}
	}
	*/
	if(CheckAttribute(chr, "quest.questflag"))
	{
		CheckQuestForCharacter(chr);
		//if(chr.chr_ai.type == LAI_TYPE_CITIZEN)
		//{
			//chr.chr_ai.group = "";
		//}
	}
	if(CheckAttribute(chr, "currentquest"))
	{
		CheckQuestForCharacter(chr);
		if(chr.chr_ai.type == LAI_TYPE_CITIZEN)
		{
			chr.chr_ai.group = "";
		}
	}
	return true;
}

void LAi_CharacterPostLogin(ref location)
{
	ref chr;
	int idx;
	//����������� ��������������
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//������������� ��������������
			chr = &Characters[idx];
			if(CheckAttribute(chr, "location.follower") != false)
			{
				//������� ���������� ������
				float x, y, z;
				if(GetCharacterPos(pchar, &x, &y, &z) == false)
				{
					x = 0.0; y = 0.0; z = 0.0;
				}
				//���� ��������� ��������� �������
				string locator = LAi_FindNearestFreeLocator("goto", x, y, z);
				if(locator != "")
				{
					TeleportCharacterToLocator(chr, "goto", locator)
					CharacterTurnByChr(chr, pchar);
				}else{
					Trace("Can't find good locator for follower character <" + chr.id + ">");
				}
			}
			if (findsubstr(chr.model, "ghost" , 0) != -1 )
			{
				object persRef = GetCharacterModel(chr);
				SendMessage(persRef, "ls", MSG_MODEL_SET_TECHNIQUE, "DLightMark");
			}
		}
	}
	if(!actLoadFlag)
	{
		QuestsCheck(); // � ������ ������, ����� ��� ���������
		// ���������� ��������� �������
		CreateCitizens(location);
		CreateHabitues(location);
		CreateIncquisitio(location);
		CreateMayak(location);
		CreateBrothels(location);
		CreatePearlVillage(location);
		CreateInsideHouseEncounters(location);
		CreateInsideResidenceEncounters(location);
		CreateSkladInsideEncounters(location);
		CreateJail(location);
		CreateFortsNPC(location);
		CreateLostShipsCity(location);
		CreatPlantation(location); // homo ���������
		CreatUnderwater(location);
		CreatTenochtitlan(location);
		CreatTenochtitlanInside(location);
		CreatDesMoines(location);
		
		// Lugger -->
		CreateArenaCitizens(location);
		CreateCaimanCitizens(location);
		CreateCaimanGuardingBase(location);
		CreateCaimanMinesCitizens(location);
		CreateCaimanPlantationCitizens(location);
		CreateCaimanShoreSlaves(location);
		GenerateShipWreck(location);
		// Lugger <--
		
		//����������� ��������� �����������
		LAi_CreateEncounters(location); //eddy. ������� �� ����� �����
		/// ����
		LandHunterReactionResult(location);
		//�������� ���� ������������ ��� ����������� ������
		CopyPassForAztecSkull();
		if(CheckAttribute(pchar, "MushketSwap"))
		{
			DeleteAttribute(pchar, "MushketSwap");
		}
		if(bDisableLandEncounters || !CheckAttribute(pchar,"quest.SimulatePGGLife") || Pchar.questTemp.CapBloodLine == true)
		{
			pchar.quest.SimulatePGGLife = true;
			//Log_TestInfo("����� �������� ��� ������������");
		}
		else
		{
			SimulatePGGLife();
		}
		SecondChanceRefresh();
		GenerateSpySeeker(location);
		if(CheckAttribute(pchar,"catorga.on")) DeleteAttribute(pchar,"catorga");
		if(CheckAttribute(pchar, "catorga")) pchar.catorga.on = "1";
		if(HasSubStr(location.id,"Crypt") && !HasSubStr(location.id, "Big")) location.id.label = "Crypt";
		
		PGG_GraveyardCheckIsPGGHere(location);
		UniqueHeroEvents();
		CheckHighOnDrugs();
		CheckLootCollector();
		CheckBSFinish();
	}
	
}

void CheckBSFinish()
{
	//���� �� ��� �� ��������, ������ ��� ������� �� �����
	if(!bWorldAlivePause && !CheckAttribute(pchar, "BSFinish"))
	{
		if(pchar.questTemp.Headhunter == "end_quest_full" || pchar.questTemp.BlueBird == "over")
		{
			if (!CheckAttribute(pchar, "BSInProgress"))	pchar.BSStart = true;
			bWorldAlivePause = true;
		}
		else
		{
			DeleteAttribute(pchar, "BSStart");
			pchar.BSInProgress = true;
		}
	}
}
void CheckLootCollector()
{
	if (CheckCharacterPerk(pchar, "AboardCollector"))
	{
		csmHideLootCollectorBox(true);
		pchar.CSM.LootCollector.Enable = true;
		pchar.CSM.LootCollector.CanBeRun = true;
	}
}
void CheckHighOnDrugs()
{
	ref chr;
	int idx;
	if (CheckAttribute(pchar, "HighOnDrugs"))
	{
		if (pchar.sex == "woman")
		{
			PlaySound("interface\baba_kxe_kxe.wav");
		}
		else
		{
			PlaySound("interface\man_kxe_kxe.wav");
		}
		pchar.GenQuest.CamShuttle = 1;
		for(int j = 0; j < LAi_numloginedcharacters; j++)
		{
			idx = LAi_loginedcharacters[j];
			if(idx >= 0)
			{
				chr = &Characters[idx];
				if(!CheckAttribute(chr, "BeforeDrugsModel") && chr.model.animation == "man")
				{
					chr.BeforeDrugsModel = chr.model;
					switch (rand(2))
					{
						case 0: 
							chr.model = GetRandSkelModel();
						break;
						case 1: 
							chr.model = GetRandSkelModelClassic();
						break;
						case 2: 
							chr.model = "Canib_"+(rand(5)+1);
						break
					}
					if (rand(10) == 0)
					{
						switch (rand(1))
						{
							case 0: 
								chr.model = "PotCMobCap";
							break;
							case 1: 
								chr.model = "Canib_boss";
							break;
						}
					}
					SetNewModelToChar(chr);
				}
			}
		}
	}
}
void UniqueHeroEvents()
{

	if (startherotype == 7 && IsEquipCharactersByItem(pchar, "DHGlove") && rand (10) == 0)
	{
		Log_info("���������� ���� ������������ ����������.");
		Log_info("��������� ������������������ �����:");
		Log_info(" - �������� - ");
		DoQuestFunctionDelay("DHmessages",4.0);
	}
}

void SecondChanceRefresh()
{
	for(int i = 0; i < MAX_CHARACTERS; i++)
	{
		ref chr;
		makeref(chr,Characters[i]);
		if(CheckAttribute(chr, "id"))
		{
			DeleteAttribute(chr, "Adventurers_Luck");
		}
		if (findsubstr(chr.model, "ghost" , 0) != -1 )
		{
			object persRef = GetCharacterModel(chr);
			SendMessage(persRef, "ls", MSG_MODEL_SET_TECHNIQUE, "DLightMark");
		}
	}
}

void SimulatePGGLife()
{
	if (findsubstr(pchar.location, "_town", 0) != -1 || findsubstr(pchar.location, "_ExitTown", 0) != -1 || findsubstr(pchar.location, "_Bank", 0) != -1 || findsubstr(pchar.location, "_store", 0) != -1 || findsubstr(pchar.location, "_Shipyard", 0) != -1 || findsubstr(pchar.location, "_church", 0) != -1 || findsubstr(pchar.location, "_SecBrRoom", 0) != -1 || findsubstr(pchar.location, "_PortOffice", 0) != -1 || findsubstr(pchar.location, "_Fort", 0) != -1 || findsubstr(pchar.location, "_Dungeon", 0) != -1)
	{
		int heroSelected = 1;
		for (i = 1; i <= PsHeroQty; i++)
		{
			sld = CharacterFromID("PsHero_"+i);
			if (findsubstr(pchar.location, sld.PGGAi.location.town, 0) != -1 && !LAi_IsDead(sld) && sld.PGGAi.location != "Dead") //������ �������������.
			{
				if (IsCompanion(sld) || IsOfficer(sld) || CheckAttribute(sld, "PGGAi.Task.SetSail") || CheckAttribute(sld, "PGGAi.SeenToday") || sld.sex == "skeleton")
				{
					continue;
				}
				else
				{
					if (rand(2) == 0)
					{
						heroSelected = 0;
						pchar.chosenHero = sld.id;
					}
				}
			}
		}
		if(heroSelected == 0)
		{
			if (findsubstr(pchar.location, "_prison", 0) != -1 || findsubstr(pchar.location, "_townhall", 0) != -1 || findsubstr(pchar.location, "_tavern", 0) != -1 || findsubstr(pchar.location, "_Brothel", 0) != -1)
			{
				Log_TestInfo("��� �������� ��� �� ���������");
			}
			else
			{
				Log_TestInfo("��� ������ ����������");
				sld = CharacterFromID(pchar.chosenHero);
				LAi_SetActorTypeNoGroup(sld);
				sld.PGGAi.SeenToday = true;
				sld.PGGAi.location.town.backup = sld.PGGAi.location.town;
				sld.PGGAi.location.backup = sld.PGGAi.location;
				GetCharacterPos(pchar, &locx, &locy, &locz);
				string locatorPGG = LAi_FindFarLocator("goto", locx, locy, locz);
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", locatorPGG);
				//chrDisableReloadToLocation = true;
				ref chr;
				if (findsubstr(pchar.location, "_town", 0) != -1)
				{
					if (findsubstr(pchar.location, "LaVega", 0) != -1 || findsubstr(pchar.location, "LeFransua", 0) != -1 || findsubstr(pchar.location, "FortOrange", 0) != -1 || findsubstr(pchar.location, "PuertoPrincipe", 0) != -1)
					{
						LAi_ActorGoToLocation(sld, "reload", "reload5", sld.PGGAi.location.town.backup, "", "", "PGGLeft", -1);
					}
					LAi_ActorGoToLocation(sld, "reload", "reload4_back", sld.PGGAi.location.town.backup, "", "", "PGGLeft", -1);
					
					sld.PGGOfficers = 2+sti(sld.rank)/15;
					for (i = 0; i < sti(sld.PGGOfficers); i++)
					{
						chr = GetCharacter(NPC_GenerateCharacter("PGGOfficer" + i, "officer_" + (rand(63) + 1), "man", "man", sld.rank, PIRATE, 0, true));
						LAi_SetActorTypeNoGroup(chr);
						ChangeCharacterAddressGroup(chr, PChar.location, "goto", locatorPGG);
						LAi_ActorFollow(chr, sld, "", -1);
						LAi_SetImmortal(chr, true);
					}
				}
				if (findsubstr(pchar.location, "_ExitTown", 0) != -1)
				{
					LAi_ActorRunToLocation(sld, "reload", "reload3", sld.PGGAi.location.town.backup, "", "", "PGGLeft", -1);
					
					sld.PGGOfficers = 2+sti(sld.rank)/15;
					for (i = 0; i < sti(sld.PGGOfficers); i++)
					{
						chr = GetCharacter(NPC_GenerateCharacter("PGGOfficer" + i, "officer_" + (rand(63) + 1), "man", "man", sld.rank, PIRATE, 0, true));
						LAi_SetActorTypeNoGroup(chr);
						ChangeCharacterAddressGroup(chr, PChar.location, "goto", locatorPGG);
						LAi_ActorFollow(chr, sld, "", -1);
						LAi_SetImmortal(chr, true);
					}
				}
				if (findsubstr(pchar.location, "_Dungeon", 0) != -1)
				{
					locatorPGG = LAi_FindNearestFreeLocator2Pchar("monsters")
					ChangeCharacterAddressGroup(sld, PChar.location, "monsters", locatorPGG);
					
					sld.PGGOfficers = 2+sti(sld.rank)/15;
					for (i = 0; i < sti(sld.PGGOfficers); i++)
					{
						chr = GetCharacter(NPC_GenerateCharacter("PGGOfficer" + i, "officer_" + (rand(63) + 1), "man", "man", sld.rank, PIRATE, 0, true));
						LAi_SetActorTypeNoGroup(chr);
						ChangeCharacterAddressGroup(chr, PChar.location, "monsters", locatorPGG);
						LAi_ActorFollow(chr, sld, "", -1);
						LAi_SetImmortal(chr, true);
					}
				}
				if (findsubstr(pchar.location, "_fort", 0) != -1)
				{
					LAi_ActorRunToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), sld.PGGAi.location.town.backup, "", "", "PGGLeft", -1);
					
					sld.PGGOfficers = 2+sti(sld.rank)/15;
					for (i = 0; i < sti(sld.PGGOfficers); i++)
					{
						chr = GetCharacter(NPC_GenerateCharacter("PGGOfficer" + i, "officer_" + (rand(63) + 1), "man", "man", sld.rank, PIRATE, 0, true));
						LAi_SetActorTypeNoGroup(chr);
						ChangeCharacterAddressGroup(chr, PChar.location, "goto", locatorPGG);
						LAi_ActorFollow(chr, sld, "", -1);
						LAi_SetImmortal(chr, true);
					}
				}
				LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), sld.PGGAi.location.town.backup, "", "", "PGGLeft", -1);
				LAi_SetImmortal(sld, true);
				
				PChar.quest.PGGWalkEnd.win_condition.l1 = "ExitFromLocation";
				PChar.quest.PGGWalkEnd.win_condition.l1.location = PChar.location;
				PChar.quest.PGGWalkEnd.function = "PGGWalkEnd";
			}
		}
	}
}

void PGGWalkEnd(string qName)
{
	if (CheckAttribute(pchar, "chosenHero"))
	{
		sld = CharacterFromID(pchar.chosenHero);
		DeleteAttribute(pchar, "chosenHero");
		string futureLoc = sld.PGGAi.location.town.backup + "_Tavern";
		ChangeCharacterAddressGroup(sld, futureLoc, "goto", "goto1");
		LAi_SetImmortal(sld, false);
		if (CheckAttribute(sld, "PGGOfficers"))
		{
			DeleteAttribute(sld, "PGGOfficers")
		}
	}
}
	
bool LAi_CharacterLogoff(aref chr)
{
	chr.chr_ai.login = false;	
	//chr.location = "none";
	if(LAi_CheckCharacter(chr, "LAi_CharacterLogoff") == false) return false;
	LAi_DelLoginedCharacter(chr);
	string func = chr.chr_ai.type;
	bool res = true;
	if(func != "")
	{
		func = "LAi_type_" + func + "_CharacterLogoff";
		res = call func(chr);
	}
	if(res == false) return false;
	return true;
}

void LAi_AddLoginedCharacter(aref chr)
{
	int index = sti(chr.index);
	LAi_loginedcharacters[LAi_numloginedcharacters] = index;
	LAi_numloginedcharacters = LAi_numloginedcharacters + 1;
}

void LAi_DelLoginedCharacter(aref chr)
{
	int index = sti(chr.index);
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		if(LAi_loginedcharacters[i] == index)
		{
			LAi_loginedcharacters[i] = LAi_loginedcharacters[LAi_numloginedcharacters - 1];
			LAi_numloginedcharacters = LAi_numloginedcharacters - 1;
		}		
	}
	if(LAi_numloginedcharacters < 0) LAi_numloginedcharacters = 0;
}

bool LAi_login_CheckTime(float start, float end)
{
	float curTime = GetTime();
	if(start <= end)
	{
		if((curTime >= start) && (curTime <= end)) return true;
	}else{
		if(curTime >= start) return true;
		if(curTime <= end) return true;
	}
	return false;
}

void LAi_PostLoginInit(aref chr)
{
	if(!IsEntity(chr)) return;
	//��������� � ������
	LAi_group_MoveCharacter(chr, chr.chr_ai.group);
	//�������������� ������
	string func = chr.chr_ai.tmpl;
	if(func != "")
	{
		func = "LAi_tmpl_" + func + "_InitTemplate";
		bool res = call func(&chr);
		if(res == false)
		{
			chr.chr_ai.tmpl = LAI_DEFAULT_TEMPLATE;
		}
	}
	//�������������� ���
	func = chr.chr_ai.type;
	if(func != "")
	{
		func = "LAi_type_" + func + "_Init";
		call func(&chr);
	}
}
//����� � ��������� ���������� Lipsar//
void GenerateSpySeeker(ref location)
{
		bool bOK = 	CheckAttribute(pchar, "GenQuest.questName") && pchar.GenQuest.questName != "SeekSpy";
		bool bOK2 = !CheckAttribute(pchar, "GenQuest.questName");
		if(!CheckAttribute(pchar, "SpySeeker.dayrandom")) pchar.SpySeeker.dayrandom = 0;
		if(CheckAttribute(pchar,"questTemp.CapBloodLine")) return;
		if(HasSubStr(location.id, "Common") && rand(1000) > 750 && pchar.dayrandom != pchar.SpySeeker.dayrandom && !HasSubStr(location.id, "Crypt") && GetCityNation(location.fastreload) != 4) 
		{
			if(bOK || bOK2)
			{
				chrDisableReloadToLocation = true;
				ref rChar = GetCharacter(NPC_GenerateCharacter("SpySeeker", "officer_"+ (1 + drand(63)), "man", "man", pchar.rank, GetCityNation(location.fastreload), -1, false));
				rChar.Dialog.FileName = "Common_Seeker.c";
				LAi_SetImmortal(rChar, true);
				rChar.saveItemsForDead = true;
				SetCharacterPerk(rChar, "Fencer");
				FantomMakeCoolFighter(rChar, sti(pchar.rank), sti(PChar.skill.Fencing), sti(PChar.skill.Pistol), BLADE_LONG, "pistol3",100);
				int iRel = GetNationRelation(GetCityNation(location.fastreload), GetBaseHeroNation());
				if(iRel == RELATION_ENEMY) pchar.SpySeeker = "Enemy";
				else pchar.SpySeeker = "Friend";
				ChangeCharacterAddressGroup(rChar, PChar.location, "goto", "goto1");
				LAi_SetActorType(rChar);
				LAi_ActorDialogDelay(rChar, PChar, "", 2.0);
				rChar.Dialog.CurrentNode = "FirstTime";
				pchar.SpySeeker.dayrandom = pchar.dayrandom;
				for(int i = 0; i<2 + rand(2); i++)
				{
				GiveItem2Character(rChar, "Lockpick");
				}
			}
		}
}
//����� � ��������� ���������� Lipsar//