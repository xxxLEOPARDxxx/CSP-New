
//------------------------------------------------------------------------------------------
//Login
//------------------------------------------------------------------------------------------

//���������� ����� �������� ���������
void LAi_SetLoginTime(aref chr, float start, float end)
{
	if(start < 0) start = 0;
	if(start >= 24) start = 23.99999999;
	if(end < 0) end = 0;
	if(end >= 24) end = 23.99999999;
	chr.location.stime = start;
	chr.location.etime = end;
}

//������� ����� �������� ���������
void LAi_RemoveLoginTime(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "stime");
	DeleteAttribute(loc, "etime");
}

//������ �������� �������� ��������, � � ����������� ����� ���������� � ������
void LAi_SetFanatic(aref chr, string churchID, string group, string locator, float start, float end)
{
	chr.location.church = churchID;
	chr.location.church.group = group;
	chr.location.church.locator = locator;
	chr.location.church.stime = start;
	chr.location.church.etime = end;
}

//������� ������� ��������
void LAi_RemoveFanatic(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "church");
}

//��������� ������������ ��������� ����� ��������
void LAi_NoRebirthEnable(aref chr)
{
	chr.location.norebirth = "1";
}

//��������� ������������ ��������� ����� ��������
void LAi_NoRebirthDisable(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "norebirth");
}

//������������ ��� �� ������ ������
void LAi_RebirthOldName(aref chr)
{
	chr.location.rebirthOldName = true;
}

//���������/��������� ��������� ����������� � ����������� �������
void LAi_LoginInCaptureTown(aref chr, bool isEnable)
{
	aref loc;
	makearef(loc, chr.location);
	if(isEnable)
	{
		loc.loadcapture = "1";
	}else{
		DeleteAttribute(loc, "loadcapture");
	}
}

//------------------------------------------------------------------------------------------
//Fight, hp
//------------------------------------------------------------------------------------------

//���������� ���������
void LAi_SetHP(aref chr, float cur, float max)
{
	if(max < 1) max = 1;
	if(cur < 0) cur = 0;
	if(cur > max) cur = max;
	chr.chr_ai.hp = cur;
	chr.chr_ai.hp_max = max;
}

//���������� ������� ���������
void LAi_SetCurHP(aref chr, float cur)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	if(cur < 0) cur = 0;
	if(cur > maxHP) cur = maxHP;
	chr.chr_ai.hp = cur;
	if (cur == 0.0 && CheckAttribute(chr, "PGGAi"))
	{
		PGG_CheckDead(chr);
	}
}

//���������� ������� ��������� � ������� �������������
void LAi_SetCurHPMax(aref chr)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	chr.chr_ai.hp = maxHP;

	chr.chr_ai.energy    = LAi_GetCharacterMaxEnergy(chr); // �������������� ���, ��� ��� ��
}

//�������� ��������� �� � �������
void LAi_SetDltHealth(aref chr, float healthPerSec)
{
	//if(healthPerSec < 0) healthPerSec = 0;
	chr.chr_ai.hp_dlt = healthPerSec;
}

//������������ ���������-�������
void LAi_UseHealthBottle(aref chr, float healthInBottle)
{
	if(healthInBottle <= 0) return;	
	if(!CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		chr.chr_ai.hp_bottle = "0";
	}
	chr.chr_ai.hp_bottle = stf(chr.chr_ai.hp_bottle) + healthInBottle;
}
// boal
void LAi_UseHealthBottleSpeed(aref chr, float healthSpeed)
{
	if (healthSpeed <= 0) return;
	
	chr.chr_ai.hp_dlt_bottle = healthSpeed;
}

// Energy Item -->
void LAi_UseEnergyBottle(aref chr, float EnergyInBottle)
{
	if(EnergyInBottle <= 0) return;	
	if(!CheckAttribute(chr, "chr_ai.Energy"))
	{
		chr.chr_ai.Energy = 0;
	}
	chr.chr_ai.Energy = stf(chr.chr_ai.Energy) + EnergyInBottle;
}
// Energy Item <--

//navy -->
void LAi_AlcoholSetDrunk(aref chr, float alcoholDegree, float time)
{
	//������� �� �����������.
	if (CheckAttribute(chr, "chr_ai.drunk")) return;
	//float energyMax;

	chr.chr_ai.drunk = time;
	//����� ���� � �������
	if (alcoholDegree > 70)
	{
		chr.chr_ai.drunk.skill.FencingLight = -20;
		chr.chr_ai.drunk.skill.Fencing 	    = -20;
		chr.chr_ai.drunk.skill.FencingHeavy = -20;
		chr.chr_ai.drunk.skill.Pistol       = -20;
		chr.chr_ai.drunk.skill.Fortune      = -20;
		chr.chr_ai.drunk.skill.Sneak        = -20;
		chr.chr_ai.drunk.skill.Leadership   = -20;
	}
	else
	{
		//���
		if (alcoholDegree > 50)
		{
			chr.chr_ai.drunk.skill.FencingLight = -10;
			chr.chr_ai.drunk.skill.FencingHeavy = 10;
		}
		//����
		else
		{
			chr.chr_ai.drunk.skill.FencingLight = 10;
			chr.chr_ai.drunk.skill.FencingHeavy = -10;
		}
		chr.chr_ai.drunk.skill.Fortune = 5;
		chr.chr_ai.drunk.skill.Pistol = -20;
	}

	//����� ����� � ���� ������� �������, �� ��� �� ������� �������� :) ���� ���.. � ��� ����� �����.
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		/*
		energyMax = stf(chr.chr_ai.energyMax);
		if(energyMax < 1) energyMax = 1;
		chr.chr_ai.drunk.energyMax = energyMax*0.2;
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) + stf(chr.chr_ai.drunk.energyMax);
		*/
		chr.chr_ai.energy = stf(chr.chr_ai.energy) + 20;
	}
}

void LAi_SetAlcoholNormal(aref chr)
{
	/*
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) - stf(chr.chr_ai.drunk.energyMax);
	}
	*/
	if (CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");

	DeleteAttribute(chr, "chr_ai.drunk");
}
//<--

//������������ ���������-�����������
void LAi_UseAtidoteBottle(aref chr)
{
	DeleteAttribute(chr, "chr_ai.poison");
}

//��������
bool LAi_IsPoison(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.poison")) return true;
	return false;
}

//������� ��������� �����������
void LAi_SetImmortal(aref chr, bool isImmortal)
{
	if(isImmortal)
	{
		chr.chr_ai.immortal = "1";
	}else{
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "immortal");
	}
}

//������ ��������� ��������� � ����������
bool LAi_IsImmortal(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		if(sti(chr.chr_ai.immortal) != 0)
		{
			return true;
		}
	}
	return false;
}


//�������� �� ���������
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//�������� ������������ �� ���������
float LAi_GetCharacterMaxHP(aref chr)
{
	float max_hp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		max_hp = stf(chr.chr_ai.hp_max);
	}
	if(max_hp < 0.0) max_hp = 0.0;
	chr.chr_ai.hp_max = max_hp;
	return max_hp;
}

//�������� ������������� �� ��������� 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}

//�������� ������������� ������� ��������� 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}

float LAi_GetCharacterEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		return stf(chr.chr_ai.energy);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}
// boal
float LAi_GetCharacterMaxEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		return stf(chr.chr_ai.energyMax);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}

//���������� ������������ ��, ���� �� ����������� ������ ���, ������� �����
void LAi_SetCheckMinHP(aref chr, float min, bool immortal, string quest)
{
	if(min < 0.9999999) min = 0.9999999;
	chr.chr_ai.hpchecker = min;
	chr.chr_ai.hpchecker.quest = quest;
	chr.chr_ai.hpchecker.immortal = immortal;
}

//������� ������������ ��
void LAi_RemoveCheckMinHP(aref chr)
{
	aref chr_ai;
	makearef(chr_ai, chr.chr_ai);
	DeleteAttribute(chr_ai, "hpchecker");	
}

//����� ���������
void LAi_KillCharacter(aref chr)
{
	chr.chr_ai.hp = "0";
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		string old = chr.chr_ai.immortal;
		chr.chr_ai.immortal = "0";
		LAi_CheckKillCharacter(chr);
		chr.chr_ai.immortal = old;
	}else{
		LAi_CheckKillCharacter(chr);
	}
}

//���� �� ��������
bool LAi_IsDead(aref chr)
{
	if (chr.id == "0") return true; // boal ���� ������� ���, �� ��� ����
	if(CheckAttribute(chr, "chr_ai.hp") == false) return true;
	if(stf(chr.chr_ai.hp) < 1.0) return true;
	return false;
}


//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//�������� �� �������� �����������
bool LAi_IsCharacterControl(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_PLAYER) return true;
	}
	return false;
}

//��������� ������ � ����������
void LAi_CharacterDisableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "1";
}

//��������� ������ � ����������
void LAi_CharacterEnableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "0";
}

//��������� ��� ������ ��������� �������
void LAi_CharacterReincarnation(aref chr, bool isEnable, bool isUseCurModel)
{
	LAi_CharacterReincarnationEx(chr, isEnable, isUseCurModel, "");
}

//��������� ��� ������ ��������� �������
void LAi_CharacterReincarnationEx(aref chr, bool isEnable, bool isUseCurModel, string locgroup)
{
	if(isEnable)
	{
		if(isUseCurModel)
		{
			chr.chr_ai.reincarnation = "0";
		}else{
			chr.chr_ai.reincarnation = "1";
		}
		if(locgroup == "") locgroup = "goto";
		chr.chr_ai.reincarnation.group = locgroup;
	}else{
		chr.chr_ai = "";
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "reincarnation");
	}	
}

bool LAi_CharacterIsReincarnation(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false) return false;
	return true;
}

bool LAi_CharacterReincarnationMode(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false)
	{
		Trace("LAi_CharacterReincarnationMode -> no field chr.chr_ai.reincarnation");
		return false;
	}
	if(sti(chr.chr_ai.reincarnation) != 0) return true;
	return false;
}

string LAi_CharacterReincarnationGroup(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation.group") == false)
	{
		Trace("LAi_CharacterReincarnationGroup -> no field chr.chr_ai.reincarnation");
		return "goto";
	}
	if(chr.chr_ai.reincarnation.group != "") return chr.chr_ai.reincarnation.group;
	return "goto";
}

//eddy. ���������� ���������� ��� ��������� ����� ������� ��� ������������.
bool LAi_SetReincarnationRankStep(aref _chr, int _step) 
{
	if(CheckAttribute(_chr, "chr_ai.reincarnation"))
	{
		_chr.chr_ai.reincarnation.step = _step;
		_chr.baseIndex = _chr.index; //������ ��� ����������������� ������� ����� ������� ������ ������ �����������.
		return true;
	}
	else Trace("LAi_SetReincarnationRankStep -> no field chr.chr_ai.reincarnation");
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//��������� ����
void LAi_CharacterPlaySound(aref chr, string soundname)
{
	SendMessage(chr, "s", soundname);
}

//������������� � ����� ��� � �������
void LAi_SetFightMode(aref chr, bool isFightMode)
{
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
}
// boal
void LAi_SetFightModeForOfficers(bool isFightMode)
{
    ref chr;
    int j, cn;
    for(j=1; j<=MAX_NUM_FIGHTERS; j++)
    {
        cn = GetOfficersIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        chr = GetCharacter(cn);
	        LAi_type_officer_Init(chr);
	        //LAi_group_UpdateTargets(chr);
            SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
	    }
	}
}

//������������� ������� ����� (!!! ������������ ��� ����� ������� !!!)
void LAi_LockFightMode(aref chr, bool isLockFightMode)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", isLockFightMode);
}

//�������� ����� ��� (�������� �� �����)
bool LAi_CheckFightMode(aref chr)
{
	return SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode");
}

//------------------------------------------------------------------------------------------
//Weapons
//------------------------------------------------------------------------------------------


//�������� ������������� ����� ���������
float LAi_GetCharacterRelCharge(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		if(CheckAttribute(chr, "chr_ai.chargeprc"))
		{
			if(sti(chr.chr_ai.chargeprc))
			{
				if(!CheckAttribute(chr, "chr_ai.charge_max")) return 0.0;
				float charge = stf(chr.chr_ai.charge);
				float chargemax = stf(chr.chr_ai.charge_max);
				if(chargemax <= 0) return 0.0;
				if(charge >= chargemax) charge = chargemax;
				charge = charge/chargemax;
				if(charge < 0.0) charge = 0.0;
				if(charge > 1.0) charge = 1.0;
				return charge;
			}else{
				return 1.0;
			}
		}else{
			chr.chr_ai.chargeprc = "1";
		}
	}
	return 0.0;
}

//�������� ������������ ���������� ������� ���������
int LAi_GetCharacterChargeQuant(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge_max"))
	{
		return sti(chr.chr_ai.charge_max);
	}
	return 0;
}

//�������� ������� ���������� ������� ���������
int LAi_GetCharacterChargeCur(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		float charge = stf(chr.chr_ai.charge);
		return MakeInt(charge);
	}
	return 0;
}

//���������� ���������� �������
void LAi_GunSetChargeQuant(aref chr, int quant)
{
	if(quant < 0) quant = 0;
	if(quant > 6) quant = 6;
	chr.chr_ai.charge_max = quant;
	
	// Warship. ���������
	
	/*// boal ���� ������� �������� �� ������� ���� gun bullet-->
	int bulletNum = GetCharacterItem(chr, "bullet");
	
	if (bulletNum > 0)
	{
	    if (bulletNum > quant)
	    {
			chr.chr_ai.charge = quant;
	    }
	    else
	    {
	       chr.chr_ai.charge = bulletNum;
	    }
	}
	else
	{
	    chr.chr_ai.charge = 0;
	}*/
	// boal ���� ������� �������� �� ������� ���� gun bullet <--
	
	int iCharge = iGetPistolChargeNum(chr, quant);
	chr.chr_ai.charge = iCharge;
	
	chr.chr_ai.chargeprc = "1";
}

// Warship. ������ �� ������� ������� -->
int iGetMinPistolChargeNum(ref rChar) // ���� ������, ������ ��� ����?
{
	int iBulletQty = GetCharacterItem(rChar, "bullet");
	int iGunPowderQty = GetCharacterItem(rChar, "GunPowder");
	int iChargeQty = func_min(iBulletQty, iGunPowderQty); // ������, ���� ������
	
	return iChargeQty;
}

int iGetPistolChargeNum(ref rChar, int iQuant) // ����� ����� ��������
{
	int iChargeQty = iGetMinPistolChargeNum(rChar);

	if(iChargeQty == 0) return 0;
	if(iChargeQty >= iQuant) return iQuant;
	if(iChargeQty < iQuant) return iChargeQty;
}
// <-- ������ �� ������� �������

//��������� �������
void LAi_GunSetUnload(aref chr)
{
	chr.chr_ai.charge = "0";
	chr.chr_ai.chargeprc = "1";
}

//���������� �������� ������ ���������
void LAi_GunSetChargeSpeed(aref chr, float speed)
{
	if(speed < 0.0) speed = 0.0;
	if(speed > 4.0) speed = 4.0;
	chr.chr_ai.charge_dlt = speed;
}

//���������� ����������� ���� �� ���������
void LAi_GunSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmggunmin = min;
}

//���������� ������������ ���� �� ���������
void LAi_GunSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmggunmax = max;
}

//���������� ����������� ��������� �� ������������ ��������� ��������
void LAi_GunSetAccuracy(aref chr, float accuracy)
{
	if(accuracy < 0.0) accuracy = 0.0;
	if(accuracy > 1.0) accuracy = 1.0;
	chr.chr_ai.accuracy = accuracy;
}

//���������� ����������� ���� �� �����
void LAi_BladeSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmgbldmin = min;
}

//���������� ������������ ���� �� �����
void LAi_BladeSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmgbldmax = max;
}

//���������� ����������� ��������
void LAi_BladeSetPiercing(aref chr, float piercing)
{
	if(piercing < 0.0) piercing = 0.0;
	if(piercing > 1.0) piercing = 1.0;
	chr.chr_ai.piercing = piercing;
}

//���������� ����������� ��������������
void LAi_BladeSetBlock(aref chr, float block)
{
	if(block < 0.0) block = 0.0;
	if(block > 1.0) block = 1.0;
	chr.chr_ai.block = block;
}
// ��� ����� boal
void LAi_BladeFencingType(aref chr, string FencingType)
{
	chr.chr_ai.FencingType = FencingType;
}

string LAi_GetBladeFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.FencingType"))
	{
        return chr.chr_ai.FencingType;
    }
    return SKILL_FENCING;
}

void LAi_BladeEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.EnergyType = fEnergyType;
}

float LAi_GetBladeEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.EnergyType"))
	{
        return stf(chr.chr_ai.EnergyType);
    }
    return 1.0;
}

//------------------------------------------------------------------------------------------
//Internal
//------------------------------------------------------------------------------------------

//������������ ���� ����������� ����������
void LAi_AllCharactersUpdate(float dltTime)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//��������
			aref chr_ai;
			makearef(chr_ai, Characters[idx].chr_ai);
			ref chr = &Characters[idx];
			if(LAi_IsDead(chr)) continue;
			//������������� �����
			float dlthp = LAI_DEFAULT_DLTHP;
			if(CheckAttribute(chr_ai, "hp_dlt")) dlthp = stf(chr_ai.hp_dlt);
			float hp = stf(chr_ai.hp) + dlthp*dltTime;
			float oldhp = hp;
			if(CheckAttribute(chr_ai, "hp_bottle"))
			{
				float bottle = stf(chr_ai.hp_bottle);
				if(bottle > 0)
				{
					//�������� ����������� �� �������
					float bottledlthp = LAI_DEFAULT_DLTBLTHP;
					if(CheckAttribute(chr_ai, "hp_dlt_bottle"))
					{
						bottledlthp = stf(chr_ai.hp_dlt_bottle);
					}
					//���������� ��������� �� �� ������� ������ �������
					bottledlthp = bottledlthp*dltTime;				
					if(bottledlthp > bottle)
					{
						bottledlthp = bottle;
					}
					bottle = bottle - bottledlthp;
					hp = hp + bottledlthp;
					chr_ai.hp_bottle = bottle;
				}else{
					//��� ������ �������
					DeleteAttribute(chr_ai, "hp_bottle");
					DeleteAttribute(chr_ai, "hp_dlt_bottle");//fix
				}
			}
			if(CheckAttribute(chr_ai, "poison"))
			{
				chr_ai.poison = stf(chr_ai.poison) - dltTime;
				if(stf(chr_ai.poison) <= 0.0)
				{
					DeleteAttribute(chr_ai, "poison");
				}else{
					hp = hp - dltTime*2.0;
					if (!CheckAttribute(chr, "poison.hp") || hp < sti(chr.poison.hp)-1.0)
					{
						chr.poison.hp = hp;
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			//navy --> ����� �������� �������
			if(CheckAttribute(chr_ai, "drunk"))
			{
				chr_ai.drunk = sti(chr_ai.drunk) - 1;
				if(sti(chr_ai.drunk) < 1) LAi_SetAlcoholNormal(chr);
			}
			//<--
			if(CheckAttribute(chr_ai, "blooding"))
			{
				chr_ai.blooding = stf(chr_ai.blooding) - dltTime;
				if(stf(chr_ai.blooding) <= 0.0)
				{
					DeleteAttribute(chr_ai, "blooding");
					if(sti(chr.index) == GetMainCharacterIndex())
					{
						Log_Info("������������ ������������.")
					//DelPerkFromActiveList("BloodingPerkA");	// ������� ����, ���� ������������ ��������
					//pchar.questTemp.bloodingperk = "false"; // ����-���
					}
				}else{
					hp = hp - dltTime*(MakeFloat(chr.chr_ai.hp_max)/100); // -1 �� � ���.
					hp = hp - GetCharacterRegenHP(chr, false)*dltTime; // ���� ������������, �� ��������� �����. �� (��� ����� ������� �� ���������)
					if (!CheckAttribute(chr, "blooding.hp") || hp < sti(chr.blooding.hp)-1.0)
					{
						chr.blooding.hp = hp;
						LAi_CharacterPlaySound(chr, "blooddrop");
						LaunchBlood(chr, 1.6, true);
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			if(LAi_IsImmortal(chr))
			{
				if(hp < oldhp) hp = oldhp;
			}
			float maxhp = stf(chr_ai.hp_max);
			if(hp > maxhp)
			{
				hp = maxhp;
				DeleteAttribute(chr_ai, "bottle");
			}
			chr_ai.hp = hp;
			//�������� ������ �� hp
			LAi_ProcessCheckMinHP(chr);
			//�������� �� ������
			LAi_CheckKillCharacter(chr);
			//������������� ������
			float chargemax = 0.0;
			if(CheckAttribute(chr_ai, "charge_max"))
			{
				chargemax = stf(chr_ai.charge_max);
			}
			//if(!CheckAttribute(chr_ai, "chargeprc")) chr_ai.chargeprc = "1";
			if(chargemax > 0.0)
			{
				if(sti(chr_ai.chargeprc))
				{
					// boal 22/07/05 ������� �� � ���. eddy.�� ���� ��������, �� �����
					if (bRechargePistolOnLine || !LAi_IsFightMode(chr) || chr.model.animation == "mushketer")
					{
						float charge = stf(chr_ai.charge);
	                    // boal ���� ������� �������� �� ������� ���� gun bullet-->
	                    if((iGetMinPistolChargeNum(chr) - charge) > 0) // Warship. ���������, �.�. �������� �����
		                {
							//zagolski. ������� ������� ��� �������
							if(!CheckAttribute(chr_ai, "charge_pSkill"))
							{
						//�������� �������
								chr_ai.charge_pSkill = LAi_GunReloadSpeed(chr);
							}

							float dltcharge = stf(chr_ai.charge_pSkill);
						//����������� ��������
						charge = charge + dltcharge*dltTime;
						if(charge >= chargemax)
						{
							charge = chargemax;
							chr_ai.chargeprc = "0";
								DeleteAttribute(chr_ai, "charge_pSkill");
							// boal 24.04.04 ������� ������� ������� -->
								if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
								{
									PlaySound("People Fight\reload1.wav");
								}
						}
						chr_ai.charge = charge;
						}
						// boal ���� ������� �������� �� ������� ���� gun bullet <--
					} // boal 22/07/05 ������� �� � ���
				}
			}
			else
			{
				chr_ai.charge = "0";
			}
			//������������� �������
			if(CheckAttribute(chr_ai, "energy"))
			{
				float energy = Lai_UpdateEnergyPerDltTime(chr, stf(chr_ai.energy), dltTime);
				if(energy < 0.0)
				{
					energy = 0.0;
				}
				if(energy > LAi_GetCharacterMaxEnergy(chr))   // boal
				{
					energy = LAi_GetCharacterMaxEnergy(chr);
				}
				chr_ai.energy = energy;
			}
		}
	}
	RefreshChargeTime();
}

void LAi_ProcessCheckMinHP(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hpchecker"))
	{
		float minhp = stf(chr.chr_ai.hpchecker);
		float hp = stf(chr.chr_ai.hp);
		if(hp < minhp)
		{
			if(sti(chr.chr_ai.hpchecker.immortal))
			{
				LAi_SetImmortal(chr, true);
				chr.chr_ai.hp = minhp;
			}
			if(chr.chr_ai.hpchecker.quest != "")
			{
				LAi_QuestDelay(chr.chr_ai.hpchecker.quest, 0.0);
			}
			LAi_RemoveCheckMinHP(chr);
		}
	}
}

void LAi_CharacterSaveAy(aref chr)
{
	float ay = 0.0;
	if(GetCharacterAy(chr, &ay) == false) ay = 0.0;
	chr.chr_ai.type.ay = ay;	
}

void LAi_CharacterRestoreAy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.type.ay"))
	{
		float ay = stf(chr.chr_ai.type.ay);
		aref type;
		makearef(type, chr.chr_ai.type);
		DeleteAttribute(type, "ay");
		CharacterTurnAy(chr, ay);
	}
}

//Gregg
float GetCharacterRegenHP(aref chr, bool useItms) // ����� ������� ������� ����������� ����� (Rasteador) (ver. 0.3.0)
{
	float fMultiplier = LAi_GetCharacterMaxHP(chr)/450.0; // �������� �����������, � ����������� �� ����. ���-�� ��

	if(fMultiplier > 2.0) fMultiplier = 2.0; // �����
	
	return fMultiplier;
}