// 11.08.05 Boal ������ ��� ����� ��� ������� S.P.E.C.I.A.L
// ����� ��� ������������� � .��� ������ (������ SKILLCHANGER)
#include "scripts\Pusher.c"
#include "scripts\Utils2.c"

// ����� �����
int GetCharacterRankRate(ref _refCharacter)
{
    return 35 - GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
}
int GetCharacterRankRateCur(ref _refCharacter)
{
    if(!CheckAttribute(_refCharacter, "rank_exp"))
	{
		_refCharacter.rank_exp = 0;
	}
    return sti(_refCharacter.rank_exp);
}
// ������� ��
int GetCharacterAddHPValue(ref _refCharacter)
{
    int E = sti(_refCharacter.SPECIAL.Endurance);
    int ret = makeint(2 + E * 0.55 + 0.5);
    return ret;
}

int GetCharacterBaseHPValue(ref _refCharacter)
{
	int ret = makeint(30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_S)*GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E)*0.5);
	/*if (CheckCharacterPerk(_refCharacter, "HPPlus"))
	{
		ret = ret + 20;
	}
	if (CheckAttribute(_refCharacter, "PerkValue.HPPlus"))
	{
  		ret = ret + sti(_refCharacter.PerkValue.HPPlus);
	} */
	return ret;
}

float GetCharacterMaxEnergyValue(ref _refCharacter)
{
    float ret = (30.0 + GetCharacterSPECIAL(_refCharacter, SPECIAL_A)*10);
    if (CheckCharacterPerk(_refCharacter, "EnergyPlus"))
	{
		ret = ret + 60;
	} 
	if (CheckCharacterPerk(_refCharacter, "EnergyPlusFixed"))
	{
  		ret = ret + 45;
	}
	if (CheckCharacterPerk(_refCharacter, "Grunt"))
	{
  		ret = ret + 30;
	}
	if(CheckAttribute(_refCharacter, "bonusEnergy"))
	{
		ret = ret + stf(_refCharacter.bonusEnergy);
	}
	return ret;
}

float GetCharacterMaxEnergyABSValue(ref _refCharacter)
{
    // �������� ������ to_do
    float ret = (30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_A)*10);
	if (CheckCharacterPerk(_refCharacter, "EnergyPlus"))
	{
		ret = ret + 60;
	}  
	if (CheckCharacterPerk(_refCharacter, "EnergyPlusFixed"))
	{
  		ret = ret + 45;
	}
	if (CheckCharacterPerk(_refCharacter, "Grunt"))
	{
  		ret = ret + 30;
	}
	return ret;
}

//--> ��������� � ������� �������� ������� ��� �����
void AddBonusEnergyToCharacter(ref _refCharacter, int iEnrg)
{
	if(CheckAttribute(_refCharacter, "bonusEnergy"))
	{//������ ������ ����������� � �� ������������ ���� �����
		_refCharacter.bonusEnergy = sti(_refCharacter.bonusEnergy) + iEnrg;
	}
	else
	{
		_refCharacter.bonusEnergy = iEnrg;
	}
	SetEnergyToCharacter(_refCharacter);
}

void RemoveBonusEnergyFromCharacter(ref _refCharacter, int howMuch)
{
	_refCharacter.bonusEnergy = sti(_refCharacter.bonusEnergy) - howMuch;
	if (sti(_refCharacter.bonusEnergy) <= 0)
	{
		DeleteAttribute(_refCharacter, "bonusEnergy");
	}
	SetEnergyToCharacter(_refCharacter);
}
//<-- ��������� � ������� �������� ������� ��� �����

void SetEnergyToCharacter(ref _refCharacter)
{
	_refCharacter.chr_ai.energyMax = GetCharacterMaxEnergyValue(_refCharacter);
	if (!CheckAttribute(_refCharacter, "chr_ai.energy"))
	{
		_refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	}
	else
	{
	    if (sti(_refCharacter.chr_ai.energy) > sti(_refCharacter.chr_ai.energyMax))
	    {
	        _refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	    }
	}
}

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
	int skillN = sti(_refCharacter.Skill.Leadership);
	//Log_Info(""+makeint(skillN/20));
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2+makeint(skillN/20);
}

int AddCharacterExp(ref _refCharacter,int _exp)
{
	int retVal = false;
	// boal now use AddCharacterExpToSkill

	return retVal;
}

int CalculateExperienceFromRank(int _Rank)
{
	if(_Rank<2) return 0;
	int retVal = 100;//(MakeInt(1000 * pow(_Rank-1,2.3))/1000)*1000;
	return retVal;
}

int GetFreePoints_SelfRate(ref _chref)
{
	if (bHigherSelfRate) return 30 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
    else return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}

int GetFreePoints_ShipRate(ref _chref)
{
	if (bHigherShipRate) return 30 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
    else return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}
/////////////////////////////////////////////////////////////////////////

void SetSelfSkill(ref _refCharacter, int _fl, int _f, int _fh, int _p, int _fr)
{
    _refCharacter.Skill.FencingLight  = _fl;
    _refCharacter.Skill.Fencing       = _f;
    _refCharacter.Skill.FencingHeavy  = _fh;
    _refCharacter.Skill.Pistol        = _p;
    _refCharacter.Skill.Fortune       = _fr;
//    _refCharacter.Skill.Leadership = _ld;
//    _refCharacter.Skill.Sneak      = _sn;
}

void SetShipSkill(ref _refCharacter, int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn)
{
    _refCharacter.Skill.Leadership = _ld;
    _refCharacter.Skill.Commerce   = _cr;
    _refCharacter.Skill.Accuracy   = _ac;
    _refCharacter.Skill.Cannons    = _cn;
    _refCharacter.Skill.Sailing    = _sl;
    _refCharacter.Skill.Repair     = _re;
    _refCharacter.Skill.Grappling  = _gr;
    _refCharacter.Skill.Defence    = _de;
    _refCharacter.Skill.Sneak      = _sn;
}

void SetSPECIAL(ref _refCharacter, int _s, int _p, int _e, int _c, int _i, int _a, int _l)
{
    _refCharacter.SPECIAL.Strength   = _s;
    _refCharacter.SPECIAL.Perception = _p;
    _refCharacter.SPECIAL.Endurance  = _e;
    _refCharacter.SPECIAL.Charisma   = _c;
    _refCharacter.SPECIAL.Intellect  = _i;
    _refCharacter.SPECIAL.Agility    = _a;
    _refCharacter.SPECIAL.Luck       = _l;
}

void SetRandSPECIAL(ref _refCharacter)  // ��� ���� 
{
    SetSPECIAL(_refCharacter,
               (4 + rand(6)),
               (2 + rand(8)),
               (4 + rand(6)),
               (2 + rand(8)),
               (4 + rand(6)),
               (4 + rand(6)),
               (2 + rand(8)));
}
 
 void SetRandSPECIAL_PGG(ref _refCharacter)  //WW ��� ���
 {
    SetSPECIAL(_refCharacter,
               (6 + rand(4)),
               (4 + rand(6)),
               (6 + rand(4)),
               (4 + rand(6)),
               (6 + rand(4)),
               (7 + rand(3)),
               (4 + rand(6)));
}
void SetRandSPECIAL_F(ref _refCharacter)  // ��� ������������
{
    SetSPECIAL(_refCharacter,
               (6 + rand(4)),
               (2 + rand(6)),
               (6 + rand(4)),
               (2 + rand(6)),
               (4 + rand(4)),
               (7 + rand(3)),
               (2 + rand(8)));
}

void SetRandSPECIAL_K(ref _refCharacter)  // ��� ���������-���������
{
    SetSPECIAL(_refCharacter,
               (4 + rand(4)),
               (4 + rand(6)),
               (4 + rand(4)),
               (4 + rand(6)),
               (4 + rand(6)),
               (4 + rand(4)),
               (2 + rand(8)));
}

/// ������ ������ �� �������
int ApplayNavyPenalty(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//����� ����� ��� ����������� ���� sti(_refCharacter.index) == GetMainCharacterIndex()) // ������ ��� ��������, ���� �� ��������� ��� ����
    {
        int sailSkill;
        // ����� ������ ���������
        sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
        int shipClass = GetCharacterShipClass(_refCharacter);
        int needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = makeint((needSkill - sailSkill)/10.0 + 0.9); // ���������� �� ��� ������
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return  sumSkill;
}
// �������� � �����
int ApplayNavyPenaltyToSkill(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//����� ����� ��� ����������� ���� sti(_refCharacter.index) == GetMainCharacterIndex()) // ������ ��� ��������, ���� �� ��������� ��� ����
    {
        int sailSkill;
        /*if (skillName == SKILL_SAILING)
        {
            sailSkill = sumSkill;
        }
        else
        { */
            // ����� ������ ���������
            sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
        //}

        int shipClass = GetCharacterShipClass(_refCharacter);
        int needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = needSkill - sailSkill;
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
		if (CheckAttribute(_refCharacter,"chr_ai.Trauma")) sumSkill = sumSkill - 20; //����� �� ������ - Gregg
		if (CheckAttribute(_refCharacter,"chr_ai.HeavyTrauma")) sumSkill = sumSkill - 30; //����� �� ������� ������ - Gregg
    }
	else
	{
		if (CheckAttribute(_refCharacter,"chr_ai.Trauma")) sumSkill = sumSkill - makeint(sumSkill*0.4); //����� �� ������ - Gregg
	}
    return  sumSkill;
}
// � �������� � ������ +1
int GetCharacterSPECIAL(ref _refCharacter, string skillName)
{
    int skillN;

	skillN = GetCharacterSPECIALSimple(_refCharacter, skillName);

 	skillN = ApplayNavyPenalty(_refCharacter, skillName, skillN);

    return skillN;
}

int GetCharacterSPECIALSimple(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName) )
    {
        return 3;
    }
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
    // Health
    if (sti(_refCharacter.index) == GetMainCharacterIndex() && MOD_SKILL_ENEMY_RATE > 1) // �� ������
    {
        skillN = skillN + GetHealthNum(_refCharacter) - 6; // max -5
    }

	if(skillName == SPECIAL_S)
	{

	}
	
	if(skillName == SPECIAL_P)
	{
		
	}
	
	if(skillName == SPECIAL_E)
	{
		/* if(IsEquipCharacterByItem(_refCharacter, "cirass1")) skillN = skillN - 1;
		if(IsEquipCharacterByItem(_refCharacter, "cirass2")) skillN = skillN - 1;
		if(IsEquipCharacterByItem(_refCharacter, "cirass3")) skillN = skillN - 1;
		if(IsEquipCharacterByItem(_refCharacter, "cirass4")) skillN = skillN - 1; */
	}
	
	if(skillName == SPECIAL_C)
	{
		
	}
	
	if(skillName == SPECIAL_I)
	{
		
	}
	
	if(skillName == SPECIAL_A)
	{
		/* if(IsEquipCharacterByItem(_refCharacter, "cirass1")) skillN = skillN - 2;
		if(IsEquipCharacterByItem(_refCharacter, "cirass2")) skillN = skillN - 1; */
	}

	if(skillName == SPECIAL_L)
	{
		
	}
	
	if (skillN <= 1) skillN = 1;
	if( skillN > SPECIAL_MAX ) skillN = SPECIAL_MAX;

	return skillN;
}

void InitRPGType()
{
    NullCharacter.SPECIALType.Strength = true;
    NullCharacter.SPECIALType.Perception = true;
    NullCharacter.SPECIALType.Endurance = true;
    NullCharacter.SPECIALType.Charisma = true;
    NullCharacter.SPECIALType.Intellect = true;
    NullCharacter.SPECIALType.Agility = true;
    NullCharacter.SPECIALType.Luck = true;
    NullCharacter.SelfType.Leadership = true;
	NullCharacter.SelfType.FencingLight = true;
    NullCharacter.SelfType.Fencing = true;
    NullCharacter.SelfType.FencingHeavy = true;
    NullCharacter.SelfType.Pistol = true;
    NullCharacter.SelfType.Fortune = true;
    NullCharacter.SelfType.Sneak = true;
    // ��������� �����������
    NullCharacter.ShipType.Commerce = true;
    NullCharacter.ShipType.Accuracy = true;
    NullCharacter.ShipType.Cannons = true;
    NullCharacter.ShipType.Sailing = true;
    NullCharacter.ShipType.Repair = true;
    NullCharacter.ShipType.Grappling = true;
    NullCharacter.ShipType.Defence = true;
}

bool isSPECIALTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SPECIALType." + _param);
}

bool isShipTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "ShipType." + _param);
}
bool isSelfTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

string GetRPGText(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("RPGDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

string GetSkillNameByIdx(int idx)
{
    string ret = "";
    switch (idx)
    {
        case 1:    ret = SKILL_F_LIGHT;   break;
        case 2:    ret = SKILL_FENCING;   break;
        case 3:    ret = SKILL_F_HEAVY;   break;
        case 4:    ret = SKILL_PISTOL;    break;
        case 5:    ret = SKILL_FORTUNE;   break;
        case 6:    ret = SKILL_LEADERSHIP; break;
        case 7:    ret = SKILL_COMMERCE;   break;
        case 8:    ret = SKILL_ACCURACY;   break;
        case 9:    ret = SKILL_CANNONS;    break;
        case 10:   ret = SKILL_SAILING;    break;
        case 11:   ret = SKILL_REPAIR;     break;
        case 12:   ret = SKILL_GRAPPLING;  break;
        case 13:   ret = SKILL_DEFENCE;    break;
        case 14:   ret = SKILL_SNEAK;      break;
        case 15:   ret = SPECIAL_S;   break;
        case 16:   ret = SPECIAL_P;   break;
        case 17:   ret = SPECIAL_A;   break;
        case 18:   ret = SPECIAL_C;   break;
        case 19:   ret = SPECIAL_I;   break;
        case 20:   ret = SPECIAL_E;   break;
        case 21:   ret = SPECIAL_L;   break;
    }
    return ret;
}
//  _type   ShipType SelfType  SPECIALType
string GetSkillNameByTRIdx(string _type, int idx)
{
    string ret = "";

	switch (_type)
	{
		case "SelfType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_LEADERSHIP; break;
				case 2:    ret = SKILL_F_LIGHT;   break;
		        case 3:    ret = SKILL_FENCING;   break;
		        case 4:    ret = SKILL_F_HEAVY;   break;
		        case 5:    ret = SKILL_PISTOL;    break;
		        case 6:    ret = SKILL_FORTUNE;   break;
                case 7:    ret = SKILL_SNEAK;      break;
		    }
		break;
		case "ShipType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_SAILING; break;
				case 2:    ret = SKILL_ACCURACY;   break;
		        case 3:    ret = SKILL_CANNONS;   break;
		        case 4:    ret = SKILL_GRAPPLING;   break;
		        case 5:    ret = SKILL_DEFENCE;    break;
		        case 6:    ret = SKILL_REPAIR;   break;
                case 7:    ret = SKILL_COMMERCE;      break;
		    }
		break;
		case "SPECIALType" :
		    switch (idx)
		    {
                case 1:   ret = SPECIAL_S;   break;
		        case 2:   ret = SPECIAL_P;   break;
		        case 3:   ret = SPECIAL_A;   break;
		        case 4:   ret = SPECIAL_C;   break;
		        case 5:   ret = SPECIAL_I;   break;
		        case 6:   ret = SPECIAL_E;   break;
		        case 7:   ret = SPECIAL_L;   break;
		    }
		break;
    }
    return ret;
}
// �� ����� ����� ������� ��������
int GetSkillValue(ref _refCharacter, string _type, string _skillName)
{
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        return sti(_refCharacter.(_type).(_skillName));
    }
    return 0;
}

float GetSkillValueExp(ref _refCharacter, string _skillName)
{
    string skillName_exp = _skillName + "_exp";
    if (!CheckAttribute(_refCharacter, "Skill."+skillName_exp))
	{
		_refCharacter.Skill.(skillName_exp) = 0;
	}
    return stf(_refCharacter.Skill.(skillName_exp));
}
int AddSPECIALValue(ref _refCharacter, string _skillName, int _add)
{
    string _type = SPECIAL_TYPE;
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        _refCharacter.(_type).(_skillName) = sti(_refCharacter.(_type).(_skillName)) + _add;
    }
    else
    {
        _refCharacter.(_type).(_skillName) = _add;
    }
    if (sti(_refCharacter.(_type).(_skillName)) < 1) {_refCharacter.(_type).(_skillName) = 1;}
    if (sti(_refCharacter.(_type).(_skillName)) > SPECIAL_MAX) {_refCharacter.(_type).(_skillName) = SPECIAL_MAX;}
    return sti(_refCharacter.(_type).(_skillName));
}

int AddCharacterSkill(ref _chref, string _skill, int _addValue)
{
    string  _skill_exp = _skill + "_exp";

    if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	}
    _chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	_chref.skill.(_skill_exp) = 0;
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
	return sti(_chref.skill.(_skill));
}

void AddCharacterSkillDontClearExp(ref _chref, string _skill, int _addValue)
{
    /*if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	} */
	_chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
}

void ApplayNewSkill(ref _chref, string _skill, int _addValue)
{
	if (_chref == pchar)
	{
		float P = makefloat(GetCharacterSPECIALSimple(_chref, SPECIAL_P)*10);
		//Enemy ship	
		worldMap.enemyshipViewDistMin = 60.0+P;		//��������� �� ������� ������� �������� ��������
		worldMap.enemyshipViewDistMax = 120.0+P;		//��������� �� ������� ������� �������� ���������
		worldMap.enemyshipBrnDistMin = 80.0+P;		//����������� ��������� �� ������� �������� �������
		worldMap.enemyshipBrnDistMax = 130.0+P;		//������������ ��������� �� ������� �������� �������
		//storm
		worldMap.stormViewDistMin = 90.0+P;			//��������� �� ������� ����� �������� ��������
		worldMap.stormViewDistMax = 180.0+P;			//��������� �� ������� ����� �������� ���������
		worldMap.stormDistKill = 190.0+P;				//���������� �� ������� ������� �����
		worldMap.stormBrnDistMin = 100.0+P;			//����������� ��������� �� ������� �������� �����
		worldMap.stormBrnDistMax = 140.0+P;			//������������ ��������� �� ������� �������� �����
		
		if(sti(pchar.questTemp.bloodingcount) >= 50) UnlockAchievement("AchBlood", 1);
		if(sti(pchar.questTemp.bloodingcount) >= 100) UnlockAchievement("AchBlood", 2);
		if(sti(pchar.questTemp.bloodingcount) >= 200) UnlockAchievement("AchBlood", 3);
		if(sti(pchar.questTemp.swiftcount) >= 50) UnlockAchievement("AchStanS", 1);
		if(sti(pchar.questTemp.swiftcount) >= 150) UnlockAchievement("AchStanS", 2);
		if(sti(pchar.questTemp.swiftcount) >= 300) UnlockAchievement("AchStanS", 3);
		if(sti(pchar.questTemp.stuncount) >= 50) UnlockAchievement("AchStanH", 1);
		if(sti(pchar.questTemp.stuncount) >= 150) UnlockAchievement("AchStanH", 2);
		if(sti(pchar.questTemp.stuncount) >= 300) UnlockAchievement("AchStanH", 3);
		if(sti(pchar.questTemp.traumacount) >= 50) UnlockAchievement("AchTravma", 1);
		if(sti(pchar.questTemp.traumacount) >= 150) UnlockAchievement("AchTravma", 2);
		if(sti(pchar.questTemp.traumacount) >= 300) UnlockAchievement("AchTravma", 3);
		if(sti(pchar.rank) == 10) UnlockAchievement("rank", 1); // 10 �������
		if(sti(pchar.rank) == 25) UnlockAchievement("rank", 2); // 25 �������
		if(sti(pchar.rank) == 40) UnlockAchievement("rank", 3); // 40 �������	
	}
	
    // ���� ���
    CheckAttribute(_chref, "BakSkill." + _skill);
	if (CheckCharacterPerk(_chref, "HPPlus"))
	{
		if (LAi_IsDead(_chref)) return;
		if (!CheckAttribute(_chref, "PerkValue.HPPlus"))
		{
			_chref.PerkValue.HPPlus = 0;
			float npchp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
			LAi_SetHP(_chref,npchp+80,npchp+80);
		}
	}
	if (CheckCharacterPerk(_chref, "HPPlusFixed"))
	{
		if (!CheckAttribute(_chref, "PerkValue.HPPlusFixed"))
		{
			_chref.PerkValue.HPPlusFixed = 0;
			float nphp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
			LAi_SetHP(_chref,nphp+60,nphp+60);
		}
	}
	//if (CheckCharacterPerk(_chref, "Buldozer"))
	//{
	//	SM_PusherSwitch();
	//}
	if (CheckCharacterPerk(_chref, "AboardCollector"))
	{
		pchar.CSM.LootCollector.Enable = true;
	}
	if (CheckCharacterPerk(_chref, "AgileMan"))
	{
		if (_chref.model.animation == "man") _chref.model.animation = "man_fast";
		// if (_chref.model.animation == "man_A") _chref.model.animation = "man_A_fast";
		if (_chref.model.animation == "Jessika") _chref.model.animation = "Jessika_fast";
		if (_chref.model.animation == "YokoDias") _chref.model.animation = "YokoDias_fast";
		if (_chref.model.animation == "Milenace") _chref.model.animation = "Milenace_fast";
		if (_chref.model.animation == "Danielle") _chref.model.animation = "Danielle_fast";
		if (_chref.model.animation == "Giant") _chref.model.animation = "Giant_fast";
		if (_chref.model.animation == "Moscovit") _chref.model.animation = "Moscovit_fast";
		if (_chref.model.animation == "Chani") _chref.model.animation = "Chani_fast";
		if (_chref.model.animation == "skeleton") _chref.model.animation = "skeleton_fast";
	}
	// boal 05.05.04 ���������� �� ������� -->
	if (isSelfTypeSkill(_skill))
    {
       if(CheckAttribute(_chref,"perks.FreePoints_self_exp"))
       {
           _chref.perks.FreePoints_self_exp = sti(_chref.perks.FreePoints_self_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_self_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_self_exp) >= GetFreePoints_SelfRate(_chref))
       {
           _chref.perks.FreePoints_self_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_self"))
           {
               _chref.perks.FreePoints_self = sti(_chref.perks.FreePoints_self) + 1;
           }
           else
           {	_chref.perks.FreePoints_self = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
               Log_SetStringToLog(XI_ConvertString("Personal abilities") + " + 1");
           }
       }
    }
    else
    {
       if(CheckAttribute(_chref,"perks.FreePoints_ship_exp"))
       {
           _chref.perks.FreePoints_ship_exp = sti(_chref.perks.FreePoints_ship_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_ship_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_ship_exp) >= GetFreePoints_ShipRate(_chref))
       {
           _chref.perks.FreePoints_ship_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_ship"))
           {
               _chref.perks.FreePoints_ship = sti(_chref.perks.FreePoints_ship) + 1;
           }
           else
           {	_chref.perks.FreePoints_ship = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
               Log_SetStringToLog(XI_ConvertString("Ship abilities") + " + 1");
           }
       }
    }
    // boal 05.05.04 ���������� �� ������� <--

    if(!CheckAttribute(_chref, "rank_exp"))
    {
      _chref.rank_exp = 0;
    }
    _chref.rank_exp = sti(_chref.rank_exp) + _addValue;

    if (sti(_chref.rank_exp) >= GetCharacterRankRate(_chref)) // use classic mode - 2 skill = 1 rank
    {
        _chref.rank_exp = 0;
        _chref.rank = sti(_chref.rank) + 1;
        float mhp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
        LAi_SetHP(_chref,mhp,mhp);

        if (CheckCharacterPerk(_chref, "EnergyPlus"))
		{
			SetEnergyToCharacter(_chref);
		}
		if (CheckCharacterPerk(_chref, "EnergyPlusFixed"))
		{
			SetEnergyToCharacter(_chref);
		}
		if (CheckCharacterPerk(_chref, "Grunt"))
		{
			SetEnergyToCharacter(_chref);
		}
		if (CheckAttribute(_chref, "bonusEnergy"))
		{
			SetEnergyToCharacter(_chref);
		}
        // ��������� � ���
        if(IsOfficer(_chref) || IsCompanion(_chref))
        {
            AddMsgToCharacter(_chref,MSGICON_LEVELUP);
            if(_chref.id == "Blaze")
            {
            Log_Info("�� �������� ����� �������!");
            PlayStereoSound("interface\new_level.wav");
            }
            else
            {
                Log_Info("����� ������� � "+ _chref.name + " "+_chref.lastname);
            }
        }
		if (sti(_chref.index) == GetMainCharacterIndex())
		{
			if(sti(_chref.rank) == 10)
			{
				UnexpectedInheritance();
			}
		}
    }
}

void ClearHPTubeEffect(string qName)
{
	float nphp = LAi_GetCharacterMaxHP(pchar) + GetCharacterAddHPValue(pchar);
	LAi_SetHP(pchar,nphp-sti(pchar.PerkValue.HPBONUS),nphp-sti(pchar.PerkValue.HPBONUS));
	DeleteAttribute(pchar,"chr_ai.bonushptube");
	DeleteAttribute(pchar,"PerkValue.HPBONUS");
}

void ClearENTubeEffect(string qName)
{
	DeleteAttribute(pchar,"chr_ai.bonusentube");
	RemoveBonusEnergyFromCharacter(pchar, sti(pchar.tubeBonusEnergy));
	RestoreModelsBeforeDrugs();
}

void ClearSTubeEffect(string qName)
{
	DeleteAttribute(pchar,"chr_ai.bonusweighttube");
	RestoreModelsBeforeDrugs();
}

void ClearDrugs()
{
	DeleteAttribute(pchar,"drugstaken");
	RestoreModelsBeforeDrugs();
}

void RestoreModelsBeforeDrugs()
{
	Log_Info("������ ���������");
	DeleteAttribute(pchar, "HighOnDrugs")
	DeleteAttribute(pchar, "GenQuest.CamShuttle")
	for(int i = 0; i < MAX_CHARACTERS; i++)
	{
		ref chr;
		makeref(chr,Characters[i]);
		if(CheckAttribute(chr, "BeforeDrugsModel"))
		{
			chr.model = chr.BeforeDrugsModel;
			DeleteAttribute(chr, "BeforeDrugsModel");
			SetNewModelToChar(chr);
		}
	}
}
// �� ������� ����������� �����
void InitStartParam(ref _chref)
{
    int i;
    string  skillName;
    ClearCharacterExpRate(_chref);
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        _chref.skill.(skillName) = makeint(MOD_EXP_RATE / GetCharacterExpRate(_chref, skillName) + 0.5);
    }
    LAi_SetHP(_chref, GetCharacterBaseHPValue(_chref), GetCharacterBaseHPValue(_chref));
	MAX_NUM_FIGHTERS=MOD_OFFICERS_RATE;
}
// ����� ���������� ����� (���������)
float GetCharacterExpRate(ref _chref, string _skill)
{
    string  skill_rate = _skill + "_rate";

    if (!CheckAttribute(_chref, "skill." + skill_rate))
    {
        float  divBy = 1.0;

        switch (_skill)
        {
            case SKILL_F_LIGHT:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_P)*0.1;
            break;
            case SKILL_FENCING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_A)*0.4;
            break;
            case SKILL_F_HEAVY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.1;
            break;
            case SKILL_PISTOL:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
            case SKILL_FORTUNE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_L);
            break;
            case SKILL_LEADERSHIP:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.1 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.9;
            break;
            case SKILL_COMMERCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.2;
            break;
            case SKILL_ACCURACY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.2;
            break;
            case SKILL_CANNONS:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_S)*0.4;
            break;
            case SKILL_SAILING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8;
            break;
            case SKILL_REPAIR:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.8;
            break;
            case SKILL_GRAPPLING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.7 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.3;
            break;
            case SKILL_DEFENCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_C)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.5;
            break;
            case SKILL_SNEAK:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
        }
        _chref.skill.(skill_rate) = makefloat(MOD_EXP_RATE / divBy);
    }
    return  stf(_chref.skill.(skill_rate));
}

// table service
string GetReputationName(int reputation)
{
    if(reputation<11)
        return "REPUTATIONT_BAD_4";
    if(reputation<21)
        return "REPUTATIONT_BAD_3";
    if(reputation<31)
        return "REPUTATIONT_BAD_2";
    if(reputation<41)
        return "REPUTATIONT_BAD_1";
    if(reputation<51)
        return "REPUTATIONT_NEUTRAL";
    if(reputation<61)
        return "REPUTATIONT_GOOD_1";
    if(reputation<71)
        return "REPUTATIONT_GOOD_2";
    if(reputation<81)
        return "REPUTATIONT_GOOD_3";
    if(reputation<=90)
        return "REPUTATIONT_GOOD_4";

	return "REPUTATIONT_GOOD_4";
}
// to_do  del
string GetFameName(int fame)
{
   return "TO_DO for del";
}

string GetMoraleName(int morale)
{
	if(morale<10)
		return MoraleTable[MORALET_TREACHEROUS];
	if(morale<20)
		return MoraleTable[MORALET_AWFUL];
	if(morale<30)
		return MoraleTable[MORALET_LOW];
	if(morale<40)
		return MoraleTable[MORALET_POOR];
	if(morale<50)
		return MoraleTable[MORALET_NORMAL];
	if(morale<60)
		return MoraleTable[MORALET_ELATED];
	if(morale<70)
		return MoraleTable[MORALET_GOOD];
	if(morale<80)
		return MoraleTable[MORALET_HIGH];
	if(morale<90)
		return MoraleTable[MORALET_EXCELLENT];
	if(morale<=100)
		return MoraleTable[MORALET_HEROIC];
	return "";
}

string GetLoyalityName(int iLoyality)
{
	if(iLoyality<10)
		return LoyalityTable[MORALET_TREACHEROUS];
	if(iLoyality<20)
		return LoyalityTable[MORALET_AWFUL];
	if(iLoyality<30)
		return LoyalityTable[MORALET_LOW];
	if(iLoyality<40)
		return LoyalityTable[MORALET_POOR];
	if(iLoyality<50)
		return LoyalityTable[MORALET_NORMAL];
	if(iLoyality<60)
		return LoyalityTable[MORALET_ELATED];
	if(iLoyality<70)
		return LoyalityTable[MORALET_GOOD];
	if(iLoyality<80)
		return LoyalityTable[MORALET_HIGH];
	if(iLoyality<90)
		return LoyalityTable[MORALET_EXCELLENT];
	if(iLoyality<=100)
		return LoyalityTable[MORALET_HEROIC];
	return "";
}

// boal 15/01/04 ���� ����� ������ � ���� ����� ��� �������� ������ ����� -->
int SetCharacterSkillByItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
	int iRetValue = 0;

	if(_skillName == _itemSkillName && GetCharacterItem(_refCharacter, _item) > 0)
	{
		iRetValue = _addValue;
	}

	return iRetValue;
}

int SetCharacterSkillByItemEquipped(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)//����� ��� ����������� �������/�����/������ - Gregg
{
	int iRetValue = 0;

	if (IsEquipCharacterByItem(_refCharacter, _item))
	{
		if(_skillName == _itemSkillName && GetCharacterItem(_refCharacter, _item) > 0)
		{
			iRetValue = _addValue;
		}
	}

	return iRetValue;
}

int SetCharacterSkillBySculArtefact(ref _refCharacter, string _skillName)
{
    if (_skillName == SKILL_CANNONS || _skillName == SKILL_DEFENCE || _skillName == SKILL_GRAPPLING || _skillName == SKILL_SAILING)
	{
       if (GetCharacterItem(_refCharacter, "sculMa1")>0 && GetCharacterItem(_refCharacter, "sculMa2")>0 && GetCharacterItem(_refCharacter, "sculMa3")>0)
       {
           switch (_skillName)
           {
               case  SKILL_CANNONS:
                   return 20;
               break;

               case  SKILL_DEFENCE:
                   return 20;
               break;

               case  SKILL_GRAPPLING:
                   return 20;
               break;

               case  SKILL_SAILING:
                   return 20;
               break;
           }
       }
       else
       {
		if (GetCharacterItem(_refCharacter, "sculMa1")>0)
		{
			           switch (_skillName)
           				{
               					case  SKILL_GRAPPLING:
                   				return 10;
               					break;
           				}
		}

		if (GetCharacterItem(_refCharacter, "sculMa2")>0)
		{
			           switch (_skillName)
           				{
               					case  SKILL_CANNONS:
                   				return 10;
               					break;
           				}
		}

		if (GetCharacterItem(_refCharacter, "sculMa3")>0)
		{
			           switch (_skillName)
           				{
               					case  SKILL_DEFENCE:
                   				return 10;
               					break;
           				}
           }
       }
    }
    return 0;
}

// Warship 25.10.08 ���� ������
int SetCharacterSkillBySuit(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;
	
	switch(sSuit)
	{
		case "suit_1": // �������
			if(sSkillName == SKILL_SNEAK)
			{
				iValue = 20;
			}
		break;
		
		case "suit_2": // ������ ��������
			if(sSkillName == SKILL_COMMERCE)
			{
				iValue = 20;
			}
		break;
		
		case "suit_3": // ������ ���������
			if(sSkillName == SKILL_LEADERSHIP)
			{
				iValue = 20;
			}
		break;
	}
	
	return iValue;
}
// boal 15/01/04 ���� ����� ������ � ���� ����� ��� �������� ������ ����� <--
float GetCharacterSkillToOld(ref _refCharacter, string skillName)
{
    return makefloat(GetCharacterSkill(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetCharacterSkill(ref _refCharacter, string skillName)
{
    int skillN;

    // boal 051104 ����� �������� ������� - �������� +1 �����, ����� ����� ��� � 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 20 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }
	skillN = GetCharacterSkillSimple(_refCharacter, skillName);
    // 14.03.05 �������� �� ������ ������� -->
 	skillN = ApplayNavyPenaltyToSkill(_refCharacter, skillName, skillN);
	// 14.03.05 �������� �� ������ ������� <--
	_refCharacter.BakSkill.(skillName)      =  skillN; // ��������
    _refCharacter.BakSkillCount.(skillName) = rand(5); // ������� ������� �������� ��������

    return skillN;
}

int GetCharacterSkillNoBonus(ref _refCharacter, string skillName)
{
	return sti(_refCharacter.Skill.(skillName));
}

float GetCharacterSkillNoBonusToOld(ref _refCharacter, string skillName)
{
	return GetCharacterSkillNoBonus(_refCharacter,skillName)/SKILL_TO_OLD;
}

int GetCharacterSkillSimple(ref _refCharacter, string skillName)
{
	if( !CheckAttribute(_refCharacter,"Skill."+skillName) ) return 1;
	int skillN = sti(_refCharacter.Skill.(skillName));
	if (CheckAttribute(_refCharacter,"HPminusDaysNeedtoRestore")) skillN -= 50; //����� �� �������� - Gregg

	bool   bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());

	if (bHero)
	{
		if (CheckAttribute(pchar,"drugstaken") && pchar.drugstaken >= 3) skillN -= 50; //����� �� ��������
		if (skillName == "Leadership")
		{
			if (CheckAttribute(pchar,"LeadershipLose"))	skillN -= 200;
		}
	}

    // boal ���� ����� -->
    if (bHero || CheckAttribute(_refCharacter, "Payment")) //IsCompanion(_refCharacter) || IsOfficer(_refCharacter))
    {
        // Health
        if (bHero && MOD_SKILL_ENEMY_RATE > 1) // �� ������
        {
            if (isSelfTypeSkill(skillName))
            {
                skillN = skillN + 5*(GetHealthNum(_refCharacter) - 6); // max -5
            }
        }
		///////////// ������ -->
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "topor_emperor", 20);			// {������������� �����}
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "topor_emperor", -30);				// {������������� �����}
		///////////// ������ <--
		
		///////////// ������ ����� (�����/���������)  -->
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "jewelry4", 10);			// {�������}							(+10 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "jewelry8", 10);				// {��������� ������} 					(+10 � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian5", 10);				// {������� �����}						(+10 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_F_HEAVY, "indian12", 10);				// {�����-����� ������������}			(+10 ������� ������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "Dozor_HorseShoe", 15);		// {���������� �������}					(+15 � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "jewelry15", 10);				// {���������� ��������} 				(+10 � ����������)
		
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "indian7", 10);				// {���� ������� ������} 				(+10 � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian17", 10);				// {������� �������}					(+10 � ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_REPAIR, STATUE1, 30);					// {��������� ���������}				(+30 ������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_COMMERCE, "indian3", 10);				// {���������� �����}					(+10 ��������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "jewelry9", 10);				// {��������� �������} 					(+10 � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FENCING, "indian6", 10);				// {������ ���������}					(+10 ������� ������)
		///////////// ������ ����� (�����/���������) <--
		
		///////////// ������ �� ������ (����������� ���� �� ������)  -->
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "DeSouzaCross", 30);			// {����� ������� �� �����} 			(+30 � �������, +20 � ����������, +10 � ��������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "DeSouzaCross", 20);		// {����� ������� �� �����} 			(+30 � �������, +20 � ����������, +10 � ��������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_COMMERCE, "DeSouzaCross", 10);		// {����� ������� �� �����} 			(+30 � �������, +20 � ����������, +10 � ��������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "DHGlove", -15);		// {������������ ����������} 			(-15 � ����������, +25 � ���������� ��� �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "DHGlove", 25);		// {������������ ����������} 			(-15 � ����������, +25 � ���������� ��� �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian1", 10);			// {������ ��������������}				(+10 ��������� � ����������, -20 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian1", 10);				// {������ ��������������}				(+10 ��������� � ����������, -20 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_PISTOL, "indian1", -20);				// {������ ��������������}				(+10 ��������� � ����������, -20 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_PISTOL, "indian10", 20);				// {������ ��������}					(+20 ���������, +10 ��������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian10", -20);				// {������ ��������}					(+20 ���������, +10 ��������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_ACCURACY, "indian10", 10);			// {������ ��������}					(+20 ���������, +10 ��������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian14", -20);			// {���� ��������}						(+20 ��������, -20 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_COMMERCE, "indian14", 20);			// {���� ��������}						(+20 ��������, -20 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian15", 10);			// {����������� ������}					(+10 ��������� � ������, -10 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_DEFENCE, "indian15", 10);				// {����������� ������}					(+10 ��������� � ������, -10 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "indian15", -10);			// {����������� ������}					(+10 ��������� � ������, -10 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SAILING, "indian18", 20);				// {���� ������}						(+20 ���������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian18", -20);				// {���� ������}						(+20 ���������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_ACCURACY, "indian19", 20);			// {��������� �������}					(+20 ��������, +10 ������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_CANNONS, "indian19", 10);				// {��������� �������}					(+20 ��������, +10 ������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian19", -20);				// {��������� �������}					(+20 ��������, +10 ������, -20 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian20", 20);			// {�������������� ���}					(+20 ��������� � -10 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "indian20", -10);			// {�������������� ���}					(+20 ��������� � -10 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian21", 20);			// {�������������� �����}				(+20 ���������, -10 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "indian21", -10);				// {�������������� �����}				(+20 ���������, -10 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_F_LIGHT, "indian22", 10);				// {������ ����� ������� ����}			(+20 ������, +10 ������ ������, -10 ��������� � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_DEFENCE, "indian22", 20);				// {������ ����� ������� ����}			(+20 ������, +10 ������ ������, -10 ��������� � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "indian22", -10);			// {������ ����� ������� ����}			(+20 ������, +10 ������ ������, -10 ��������� � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "indian22", -10);			// {������ ����� ������� ����}			(+20 ������, +10 ������ ������, -10 ��������� � �������)
		///////////// ������ �� ������ (����������� ���� �� ������) <--

    	///////////// ������ ������ (������ �������/���������) -->
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "Totem_1", 5);				// {����� ����������} 					(+5 �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "Totem_2", 5);					// {����� ��������������} 				(+5 ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_PISTOL, "Totem_5", 5);				// {����� ������������}					(+5 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "Totem_6", 5);			// {����� �������������}				(+5 ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FENCING, "Totem_7", 5);				// {����� ������������}					(+5 ������� ������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_F_LIGHT, "Totem_8", 5);				// {����� �������}						(+5 ������ ������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_F_HEAVY, "Totem_9", 5); 				// {����� ��������}						(+5 ������� ������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "Dozor_Mirror", 15);			// {��������� �������}					(+15 � ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SAILING, "hatWhisper", 5);			// {��������� �������}					(+15 � ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_LEADERSHIP, "hatWhisper", 5);			// {��������� �������}					(+15 � ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_GRAPPLING, "hatWhisper", 5);			// {��������� �������}					(+15 � ����������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "hatWhisper", -5);				// {��������� �������}					(+15 � ����������)
		
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_DEFENCE, "Totem_3", 5);				// {����� ������������} 				(+5 ������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_ACCURACY, "Totem_4", 5);				// {����� ���������}					(+5 ��������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_COMMERCE, "Totem_10", 5); 			// {����� �������������}				(+5 ��������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_CANNONS, "Totem_11", 5); 				// {����� ��������}						(+5 ������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SAILING, "Totem_12", 5);				// {����� ���������}					(+5 � ���������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_REPAIR, "Totem_15", 5);				// {����� ����-������}					(+5 � �������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SAILING, "Dozor_Storm", 15);			// {�����-�����}						(+15 � ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "glasses", 15);				// {�����-�����}						(+15 � ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_PISTOL, "glasses", -5);				// {�����-�����}						(+15 � ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_ACCURACY, "glasses", -5);				// {�����-�����}						(+15 � ���������)
    	skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_CANNONS, "glasses", -5);				// {�����-�����}						(+15 � ���������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_COMMERCE, "PDM_PJ_BsRL", 5);			// {������� � ������� ���������}			(+5 �������, +5 ��������, -5 ����������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_FORTUNE, "PDM_PJ_BsRL", 5);			// {������� � ������� ���������}			(+5 �������, +5 ��������, -5 ����������)
		skillN = skillN + SetCharacterSkillByItemEquipped(_refCharacter, skillName, SKILL_SNEAK, "PDM_PJ_BsRL", -5);			// {������� � ������� ���������}			(+5 �������, +5 ��������, -5 ����������)
		///////////// ������ ������ (������ �������/���������) <--
		
		///////////// ��� ����/������ �� ��������� -->
        skillN = skillN + SetCharacterSkillBySculArtefact(_refCharacter, skillName);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Cursed_idol", -40);			// {���� ������������������}				(-40 �������)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Coins", -50);				// {��������� ���������}				(-50 �������)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Mineral8", -10);			// {������}								(-10 �������)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "mineral4", -10);			// {������}								(-10 ��������� �  -10 ����������)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "mineral4", -10);				// {������}								(-10 ��������� �  -10 ����������)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian2", -10);			// {�������� �������} 					(-10 ���������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "SkullAztec", -20);			// {���������� �����}					(-20 �������, +10 ���������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "SkullAztec", 10);		// {���������� �����}					(-20 �������, +10 ���������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "KnifeAztec", -30);			// {������������ �������������� ���} 	(-30 ���������, -20 �� ��� ��������� ���� ������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "KnifeAztec", -20);			// {������������ �������������� ���} 	(-30 ���������, -20 �� ��� ��������� ���� ������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "KnifeAztec", -20);			// {������������ �������������� ���} 	(-30 ���������, -20 �� ��� ��������� ���� ������)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "KnifeAztec", -20);			// {������������ �������������� ���} 	(-30 ���������, -20 �� ��� ��������� ���� ������)
		///////////// ��� ����/������ �� ��������� <--

		// Warship 25.10.08 ����� ���� ������
		skillN += SetCharacterSkillBySuit(_refCharacter, skillName);
		
		//Gregg ����� �� ��������� ������
	
		//navy --> �������� ��������
		if (CheckAttribute(_refCharacter, "chr_ai.drunk.skill." + skillName))
		{
			skillN += sti(_refCharacter.chr_ai.drunk.skill.(skillName));
		}
    	// boal ���� ��������� 19.01.2004 -->
    	if ( GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
   	        skillN -= 20;
    	}
    	// boal ���� ��������� 19.01.2004 <--
	}
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SKILL_MAX ) skillN = SKILL_MAX;

	return skillN;
}
// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 100; break; // LEO: ������� ������ ���������� ��������� 01.12.2021
            case 2 : needSkill = 85; break;
            case 3 : needSkill = 70; break;
            case 4 : needSkill = 50; break;
            case 5 : needSkill = 30; break;
            case 6 : if (MOD_SKILL_ENEMY_RATE == 10) needSkill = 10; else needSkill = 1; break; // LEO: ��������������� �������� 07.12.2021
            case 7 : needSkill = 0; break;
    }
    return needSkill;
}
// boal 20.03.2004 <--
void DelBakSkillAttr(ref _refCharacter) // boal ����������� ������
{
    DeleteAttribute(_refCharacter, "BakSkill");
    DeleteAttribute(_refCharacter, "BakSkillCount");
}
// ����� ���� ������� (����� �������, ��������������� �� ����� +1)
void ClearCharacterExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        DeleteAttribute(_chref, "skill." + name + "_rate");
    }
}
// ����� �������� ����� ����, ����� �������� ����, ����� ����� �� 120 ���������
void RefreshCharacterSkillExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        AddCharacterExpToSkill(_chref, name, 0.0);
        ApplayNewSkill(_chref, name, 0); // ����� �����  ����� 23/22
    }
}

float GetSummonSkillFromNameToOld(ref _refCharacter, string skillName)
{
    return (GetSummonSkillFromName(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetSummonSkillFromName(ref _refCharacter, string skillName)
{
    int sumSkill;

    // boal 051104 ����� �������� ������� - �������� +1 �����, ����� ����� ��� � 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 25 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }
    sumSkill = GetSummonSkillFromNameSimple(_refCharacter, skillName);
    // boal 27.01.2004 �������� �� ������ ������� -->
    sumSkill = ApplayNavyPenaltyToSkill(_refCharacter, skillName, sumSkill);
    // boal 27.01.2004 <--

    _refCharacter.BakSkill.(skillName)      =  sumSkill; // ��������
    _refCharacter.BakSkillCount.(skillName) = rand(5); // ������� ������� �������� ��������

    return sumSkill;
}

int GetSummonSkillFromNameSimple(ref _refCharacter, string skillName)
{
    int sumSkill = GetCharacterSkillSimple(_refCharacter,skillName);

	if (sti(_refCharacter.index) == sti(pchar.index))
	{
	    int iOfficer = -1;
		int iOffSkill = -1;
		switch (skillName)
		{
			/*case SKILL_LEADERSHIP:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;*/
			case SKILL_SAILING:
				iOfficer = sti(pchar.Fellows.Passengers.navigator);
			break;
			case SKILL_CANNONS:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;
			case SKILL_ACCURACY:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;
			case SKILL_GRAPPLING:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;
			case SKILL_DEFENCE:
				iOfficer = sti(pchar.Fellows.Passengers.doctor);
			break;
			case SKILL_REPAIR:
				iOfficer = sti(pchar.Fellows.Passengers.carpenter);
			break;
			case SKILL_COMMERCE:
				iOfficer = sti(pchar.Fellows.Passengers.treasurer);
			break;
		}
		if(iOfficer != -1)
		{
			iOffSkill = GetCharacterSkillSimple(&characters[iOfficer], skillName);
			if (bNoBonusSkillOff) 
			{
				if ((iOffSkill - sumSkill) > 25) sumSkill = sumSkill + 25;
				else
				{
					if (iOffSkill > sumSkill)
					{
						sumSkill = iOffSkill;
					}
				}
			}
			else
			{
				if (iOffSkill > sumSkill)
				{
					sumSkill = iOffSkill;
				}
			}
		}
	}
	return sumSkill;
}

void AddPartyExp(ref _refCharacter,int _exp)
{
	/*int cn,i;
	ref chref;
	i = GetOfficersQuantity(_refCharacter);
	_exp = (_exp+i)/(i+1);
	for(i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		cn = GetOfficersIndex(_refCharacter,i);
		if(cn!=-1)
		{	AddCharacterExp(GetCharacter(cn),_exp);
		}
	}*/
}

void AddExpAndShow(ref chref, int _exp)
{
	// boal Log_SetStringToLog("+" + _exp + XI_ConvertString("add experience"));
	//AddCharacterExp(chref, _exp);
}
// boal -->

void AddCharacterExpToSkillSquadron(ref _refCharacter, string _skill, float _addValue)
{
    int cn,i;
	ref chref;

	for(i=0; i<7; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{    // � ��������� ����
			AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue);
		}
	}
}
void AddCharacterExpToSkill(ref _chref, string _skill, float _addValue)
// _chref - character _skill - name ex -"Fencing"  _skill_exp = "Fencing_exp"   _addValue = 100
{
    string  _skill_exp = _skill + "_exp";
    if (!CheckAttribute(_chref, "skill." + _skill_exp))
    {
        _chref.skill.(_skill_exp) = 0;
    }
    if (bExpLogShow && _addValue > 0)
    {
	   if (IsOfficer(_chref))  Log_Info(_chref.id + " take " + FloatToString(_addValue, 2) + " exp to " + _skill);
    }
    // boal 300804 ������� ����� -->
    if (_addValue < 0)
    {
        if(CheckAttribute(_chref, "skill." + _skill_exp))
        {
            _chref.skill.(_skill_exp) = sti(_chref.skill.(_skill_exp)) + _addValue;
            if (sti(_chref.skill.(_skill_exp)) < 0)
            {
                _chref.skill.(_skill_exp) = 0;
            }
        }
        return;
    }
    // boal 300804 ������� ����� <--
    if (CheckAttribute(_chref, "skill." + _skill) && sti(_chref.skill.(_skill)) < SKILL_MAX)// && sti(_chref.skill.(_skill)) > 0)
    { // if skill = 0 then it is great loser
        _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) + _addValue;

        while ( makeint(sti(_chref.skill.(_skill)) * GetCharacterExpRate(_chref, _skill)) <= stf(_chref.skill.(_skill_exp))
                && sti(_chref.skill.(_skill)) < SKILL_MAX )
        {
            _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) - makeint(sti(_chref.skill.(_skill)) * GetCharacterExpRate(_chref, _skill));
            /*if (sti(_chref.index) == GetMainCharacterIndex())
            {
               Log_SetStringToLog(XI_ConvertString(_skill)+" UP");
            } */
            AddCharacterSkillDontClearExp(_chref, _skill, 1);
            // ����������� ������
            DeleteAttribute(_chref, "BakSkill." + _skill);
            DeleteAttribute(_chref, "BakSkillCount." + _skill);
        }
    }
    /// officers
    if (_addValue > 0 && sti(_chref.index) == GetMainCharacterIndex()) // ������ ��� ��
    {
		int cn, i, iPas;
		iPas = GetPassengersQuantity(_chref); // ����������
		if (CheckCharacterPerk(_chref, "SharedExperience"))
		{
			for(i=0; i<iPas; i++)
			{
				cn = GetPassenger(_chref,i);
				if(cn!=-1)
				{
				   if (isOfficerInShip(GetCharacter(cn), true))
				   {
				       AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 1.0);
				   }
				   else
				   {
				       AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 4.0);
				   }
				}
			}
	        for(i=1; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(_chref,i);
				if(cn!=-1)
				{
					AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 1.0);
				}
			}
		}
		else
		{
		    for(i=0; i<iPas; i++)
			{
				cn = GetPassenger(_chref,i);
				if(cn!=-1)
				{
				   if (isOfficerInShip(GetCharacter(cn), true))
				   {
				       AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 4.0);
				   }
				   else
				   {
				       AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 20.0);
				   }
				}
			}
	        for(i=1; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(_chref,i);
				if(cn!=-1)
				{
					AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 6.0);
				}
			}
		}
    }
}

string GetPerkListText(ref _chref, string _type)
{
    int    perksQ,i;
    int    lngFilePerkID = -1;
	string perkName;
	string ret;
	aref   arPerksRoot;

    lngFilePerkID = LanguageOpenFile("AbilityDescribe.txt");
	// �������� ������, ������� ����� ��������
	makearef(arPerksRoot, _chref.perks.list);
	perksQ = GetAttributesNum(arPerksRoot);
	ret = "";
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));

        if (CheckAttribute(&ChrPerksList, "list." + perkName) && CheckAttribute(&ChrPerksList, "list." + perkName + ".BaseType"))
        {
            if (ChrPerksList.list.(perkName).BaseType == _type)
            {
                ret += "* " + LanguageConvertString(lngFilePerkID, perkName) + " ";
            }
        }
	}
	LanguageCloseFile(lngFilePerkID);
	return ret;
}
// boal ��� ��������� 19.01.2004 -->
float GetItemsWeight(ref _chref)
{
    float   Amount = 0;
    int     j;
    string  itemID;
    ref     itm;

    if (bCabinStarted || bAbordageStarted || !bSeaActive || !CheckAttribute(_chref, "ItemsWeight") || CheckForExchangeAllowed(_chref))
    {
        for (j=0; j<TOTAL_ITEMS; j++)
		{
    		makeref(itm,Items[j]);
			
			if(CheckAttribute(itm, "ID"))
			{
				itemID = itm.id;
				if (CheckAttribute(_chref, "items."+itemID) && itemID != "MapsAtlas")      // ugeen - ����� ���� �� ��������� !!
				{
					Amount += sti(_chref.items.(itemID))*stf(itm.Weight);
				}
			}
        }
        _chref.ItemsWeight = Amount; // ����������� �������� � ��� �� ����
    }
    else
    {
        Amount = stf(_chref.ItemsWeight);
    }
    return Amount;
}

bool CheckForExchangeAllowed(ref _chref)
{
	if(!LAi_group_IsActivePlayerAlarm())
	{
		if (bSeaActive || CheckAttribute(loadedLocation,"fastreload") || CheckAttribute(loadedLocation,"townsack") || _chref.location == pchar.location)
		{
			bool ok = CheckAttribute(_chref, "prisoned") && sti(_chref.prisoned) == true;
			if (!ok && !CheckAttribute(_chref,"isquest") && !CheckAttribute(_chref,"nonremovable")) return true;
		}
		
	}
	else {return false;}
	return false;
}

int GetMaxItemsWeight(ref _chref)
{
	if (CheckAttribute(_chref, "Skill.Fencing"))
    {
        int iBonus = 0;
        //if (IsCharacterPerkOn(_chref, "Grus")) iBonus = 30;
		if (IsCharacterPerkOn(_chref, "EnergyPlus")) iBonus = 30;
		if (IsCharacterPerkOn(_chref, "EnergyPlusFixed")) iBonus = 30;
		if (IsCharacterPerkOn(_chref, "Trader")) iBonus += 35;
		// Lugger -->
	        if(CheckAttribute(_chref, "equip.backpack"))
	        {
	        	if(_chref.equip.backpack != "")
	        	{
	        		ref BackPack = ItemsFromID(_chref.equip.backpack);
	        		int iBackPack = sti(BackPack.BackPackWeight);
	        		
	        		iBonus += iBackPack;
	        	}
	        }
		// Lugger <--
        //������� ��������  ���� ������ GetCharacterSPECIAL
		if (CheckAttribute(_chref, "chr_ai.bonusweighttube")) iBonus += 60 + sti(_chref.rank);
        if (bDifficultyWeight) iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12);
		else iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12 - MOD_SKILL_ENEMY_RATE);
        return  iBonus;
    }
    else
    {
        return 10000; // ������ ��� ���� �� ������ ����� � �����������
    }
}
// boal 19.01.2004 <--

// boal -->
int Statistic_AddValue(ref _chref, string _attrName, int _add) // set and get(_add==0) value
{
    // KillShip_ 1 ..7
    // AbordShip_ 1..7
    // KillAbordShip_ 1..7
    // Solder_s  Solder_g ( s=sword g=gun)
    // Citizen_s  Citizen_g
    // Monster_s Monster_g
    // Warrior_s  Warrior_g
    // Fort
	if(!CheckAttribute(_chref, "index")) return 0;
	
    if (sti(_chref.index) != GetMainCharacterIndex()) return 0; // �����������
    if( !CheckAttribute(_chref,"Statistic." + _attrName) )
    {
        _chref.Statistic.(_attrName) = 0;
    }
    _chref.Statistic.(_attrName) = sti(_chref.Statistic.(_attrName)) + _add;

    if (sti(_chref.Statistic.(_attrName)) < 0)
    {
        _chref.Statistic.(_attrName) = 0;
    }
	//��������� ����������
	// --->
	if(_add > 0)
	{
		int monstersall = sti(_chref.Statistic.Monster_s)+sti(_chref.Statistic.Monster_g);
		int killsall = sti(_chref.Statistic.Solder_s)+sti(_chref.Statistic.Citizen_s)+sti(_chref.Statistic.Warrior_s)+sti(_chref.Statistic.Monster_s)+sti(_chref.Statistic.Solder_g)+sti(_chref.Statistic.Citizen_g)+sti(_chref.Statistic.Warrior_g)+sti(_chref.Statistic.Monster_g);
		int aboardships = sti(_chref.Statistic.AbordShip_1)+sti(_chref.Statistic.AbordShip_2)+sti(_chref.Statistic.AbordShip_3)+sti(_chref.Statistic.AbordShip_4)+sti(_chref.Statistic.AbordShip_5)+sti(_chref.Statistic.AbordShip_6)+sti(_chref.Statistic.AbordShip_7)+sti(_chref.Statistic.KillAbordShip_1)+sti(_chref.Statistic.KillAbordShip_2)+sti(_chref.Statistic.KillAbordShip_3)+sti(_chref.Statistic.KillAbordShip_4)+sti(_chref.Statistic.KillAbordShip_5)+sti(_chref.Statistic.KillAbordShip_6)+sti(_chref.Statistic.KillAbordShip_7);
		int killshipsall = sti(_chref.Statistic.KillShip_1)+sti(_chref.Statistic.KillShip_2)+sti(_chref.Statistic.KillShip_3)+sti(_chref.Statistic.KillShip_4)+sti(_chref.Statistic.KillShip_5)+sti(_chref.Statistic.KillShip_6)+sti(_chref.Statistic.KillShip_7)+aboardships;
		
		/*
		string statshipinfo;
		for (i = 1; i< 8; i++)
		{
			statshipinfo = "KillShip_" + i;
			killshipsall += sti(_chref.Statistic.(statshipinfo));
			
			statshipinfo = "AbordShip_" + i;
			killshipsall += sti(_chref.Statistic.(statshipinfo));
			
			statshipinfo = "KillAbordShip_" + i;
			killshipsall += sti(_chref.Statistic.(statshipinfo));
		}*/
		
		// �������� ������
		if(monstersall >= 30) UnlockAchievement("skel_kills", 1);
		if(monstersall >= 75) UnlockAchievement("skel_kills", 2);
		if(monstersall >= 150) UnlockAchievement("skel_kills", 3);

		// ����� ��������
		if(killsall >= 50) UnlockAchievement("kills", 1);
		if(killsall >= 150) UnlockAchievement("kills", 2);
		if(killsall >= 500) UnlockAchievement("kills", 3);
		
		// ���������� ��������
		if(killshipsall >= 10) UnlockAchievement("ship_kills", 1);
		if(killshipsall >= 35) UnlockAchievement("ship_kills", 2);
		if(killshipsall >= 70) UnlockAchievement("ship_kills", 3);
		
		if(!CheckCharacterPerk(pchar,"AboardCollector") && killsall >= 200 && aboardships >= 20) {SetCharacterPerk(pchar, "AboardCollector"); log_info("�� �������� ''�����������''.");}
	}
	// <---								
    return sti(_chref.Statistic.(_attrName));
}
void Statistic_KillChar(aref _attack, aref _enemy, string _attrName)
{
	if (sti(_attack.index) != GetMainCharacterIndex()) return; // �����������
	string  name = GetCharType(_enemy);

	name = name + _attrName;

	Statistic_AddValue(_attack, name, 1);
}
string GetCharType(aref _enemy)  //TO_DO ���������� �� ��� � ���
{
    string  name  = "Warrior"; // define
    string  model = _enemy.model;
	string  sex = _enemy.sex;
    switch (_enemy.chr_ai.type)
	{
		case LAI_TYPE_PATROL :
		    name = "Solder";
		break
		case LAI_TYPE_GUARDIAN :
		    name = "Solder";
		break
		case LAI_TYPE_OFFICER :
		    name = "Solder";
		break;
        // Citizen
		case LAI_TYPE_ACTOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_BARMAN :
		    name = "Citizen";
		break;
		case LAI_TYPE_CITIZEN :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBER :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBERSTAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_MERCHANT :
		    name = "Citizen";
		break;
		case LAI_TYPE_POOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_PRIEST :
		    name = "Citizen";
		break;
		case LAI_TYPE_SIT :
		    name = "Citizen";
		break;
		case LAI_TYPE_STAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_WAITRESS :
		    name = "Citizen";
		break;
		case LAI_TYPE_OWNER :
		    name = "Citizen";
		break;
		case LAI_TYPE_WARRIOR : // to_do ��������� ���
		    if (model == "mummy" || HasSubStr(model,"Skel") || sex == "skeleton")
		    {
		        name = "Monster";
		    }
		    else
		    {
                if (findsubstr(model, "off_" , 0) != -1)
                {
                    name = "Solder";
                }
                else
                {
                    if (findsubstr(model, "sold_" , 0) != -1)
	                {
	                    name = "Solder";
	                }
                }
		    }
		break;
	}
	return  name;
}
// boal statistic info 17.12.2003 <--

// boal ���� �������� �� -->
int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0); // �� ������

    return i;
}

int GetHealthMaxNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.maxHP) + 9) / 10.0); // �� ������

    return i;
}
string GetHealthName(ref ch)
{
    string name = "";

    switch (GetHealthNum(ch))
    {
        case 1:
            name = "�������";
        break;
        case 2:
            name = "������";
        break;
        case 3:
            name = "��������";
        break;
        case 4:
            name = "�������";
        break;
        case 5:
            name = "�������";
        break;
        case 6:
            name = "��������";
        break;
    }
    return name;
}

string GetHealthNameMaxSmall(ref ch)
{
    string name = "";

    switch (GetHealthMaxNum(ch))
    {
        case 1:
            name = "�������";
        break;
        case 2:
            name = "������";
        break;
        case 3:
            name = "��������";
        break;
        case 4:
            name = "�������";
        break;
        case 5:
            name = "�������";
        break;
        case 6:
            name = "��������";
        break;
    }
    return name;
}

void SetNewDayHealth()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.Damg);
    int   add   = 0;

    mainChr.Health.Damg = 0.0;

    //if (IsCharacterPerkOn(mainChr, "Medic"))
    if (IsCharacterPerkOn(mainChr, "HPPlusFixed"))
	{
        add = 1;
    }
    if (damg >= (maxhp / 1.5) )
    {
        if ((damg / maxhp) > add)
        {
            AddCharacterHealth(mainChr, -damg / maxhp + add);
        }
    }
    else
    {
        if (!IsEntity(worldMap)) // �� �� �����
        {
            AddCharacterHealth(mainChr, 1 + add);
        }
        else
        {
            AddCharacterHealth(mainChr, 0.5 + add / 2.0);
        }
    }
}

void SetNewDayHealthMax()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.weekDamg);

    mainChr.Health.weekDamg = 0.0;

    if (damg > (maxhp * 3.5))
    {
        AddCharacterMaxHealth(mainChr, -1);
    }
}

void AddCharacterHealth(ref mainChr, float add)
{
	//Lipsar ����� ������� ������ ������
	if(CheckAttribute(PChar,"Luke.BadPoison")) return;
    float maxhp = stf(mainChr.chr_ai.hp_max);
    int   remHP = GetHealthNum(mainChr);

    mainChr.Health.HP = makefloat(stf(mainChr.Health.HP) + add);
    if (stf(mainChr.Health.HP) < 1)
    {
        mainChr.Health.HP = 1.0;
    }
    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
    if (GetHealthNum(mainChr) > remHP)
    {
        Log_Info("�������� ����� �����");
    }
    if (GetHealthNum(mainChr) < remHP)
    {
        Log_Info("�������� ����� ����");
    }
}

void AddCharacterMaxHealth(ref mainChr, float add)
{
    mainChr.Health.maxHP = makefloat(stf(mainChr.Health.maxHP) + add);

    if (stf(mainChr.Health.maxHP) < 1)
    {
        mainChr.Health.maxHP = 1.0;
    }
    if (stf(mainChr.Health.maxHP) > 60)
    {
        mainChr.Health.maxHP = 60.0;
    }
    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
}
// boal ���� �������� �� <--

// ���������� �������� ������� �� ������ -->
int ChangeCharacterHunterScore(ref chref, string _huntName, int incr)
{
	int prevVal = -5; // ��� �����

	if (_huntName == "pirhunter") return 0;
	if (CheckAttribute(chref, "GenQuest.HunterScore2Pause")) incr = 0;

	if (CheckAttribute(chref, "reputation." + _huntName) )	prevVal = sti(chref.reputation.(_huntName));

	int newVal = prevVal + incr;
	if (newVal < -100)  newVal = -100;
	if (newVal > 100)   newVal = 100;

	chref.reputation.(_huntName) = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return newVal;

	if (newVal >= 10)
	{
	 	if (prevVal < newVal)
		{
			Log_SetStringToLog(XI_ConvertString(_huntName) + " ��������� ������� �� ���� ������");
		}

	    if (prevVal > newVal)
		{
	        Log_SetStringToLog(XI_ConvertString(_huntName) + " ������� ������� �� ���� ������");
		}
	}
	else
	{
		int iNation = 0;
		switch (_huntName) // ��� ��� ������������� �� ������
		{
		    case "enghunter":  iNation = ENGLAND; break;
		    case "frahunter":  iNation = FRANCE; break;
		    case "spahunter":  iNation = SPAIN; break;
		    case "holhunter":  iNation = HOLLAND; break;
		}
		string prevName = GetNationReputationName(iNation, -prevVal);
		string newName  = GetNationReputationName(iNation, -newVal);
		if (prevName!=newName)
		{
			string outString = XI_ConvertString("Your reputation with country")+ XI_ConvertString(Nations[iNation].Name + "Gen") +" ";
			if (incr<0)	{outString+=XI_ConvertString("increase");}
			else	{outString+=XI_ConvertString("decrease");}
			outString += " "+XI_ConvertString("to")+" "+newName;
			Log_SetStringToLog(outString);
		}
	}
	return newVal;
}

int ChangeCharacterNationReputation(ref chref, int _Nation, int incr)
{
	return -ChangeCharacterHunterScore(chref, NationShortName(_Nation) + "hunter", -incr); // ��� ��������, - ��� ������, + ���� ���
}

string GetNationReputation(ref chref, int _Nation)
{
    return GetNationReputationName(_Nation, ChangeCharacterNationReputation(chref, _Nation, 0));
}

string GetNationReputationName(int _Nation, int i)
{
	if (i <= -10)  return "������� �� ������ " + (-i*10000);
    if (i < 0 )    return "����������";
    if (i <= 20 )  return "�����������";
    if (i <= 50 )  return "�������";
    if (i <= 80 )  return "��������";
    if (i <= 100 ) return "����������";

    return "��������";
}
// boal 04.04.04
string NationShortName(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return "eng";
		break;
		case FRANCE:
            return "fra";
		break;
		case SPAIN:
            return "spa";
		break;
		case HOLLAND:
			return "hol";
		break;
		case PIRATE:
			return "pir";
		break;
	}
	return "eng";
}
// ���������� �������� ������� �� ������ <--

void setWDMPointXZ(string _location)
{
    // ���������� �� ������ ����� -->
    int n;
	string sTemp;

    n = FindIslandBySeaLocation(_location);
	if(n!=-1)
	{
		worldMap.island = Islands[n].id;
		Pchar.curIslandId = worldMap.island; // fix
		sTemp = worldMap.island;
		if (CheckAttribute(&worldMap, "islands." + sTemp))
		{
		    worldMap.zeroX = worldMap.islands.(sTemp).position.x;
			worldMap.zeroZ = worldMap.islands.(sTemp).position.z;
			if (CheckAttribute(&worldMap, "islands." + sTemp + "." + _location))
			{
			    worldMap.playerShipX = worldMap.islands.(sTemp).(_location).position.x;
				worldMap.playerShipZ = worldMap.islands.(sTemp).(_location).position.z;
				//trace(sTemp + "." + _location);
			}
			else
			{// ��� ���� � ����������� ������������
			    worldMap.playerShipX = worldMap.zeroX;
				worldMap.playerShipZ = worldMap.zeroZ;
			}
		}
	}
	// ���������� �� ������ ����� <--
}
// ����� �� ����������� ��� � �������� �������
void ChangeAttributesFromCharacter(ref CopyChref, ref PastChref, bool _dialogCopy)
{
    aref arToChar;
    aref arFromChar;
	
	DeleteAttribute(CopyChref,"model");
	DeleteAttribute(CopyChref,"heromodel");
	
    CopyChref.model            = PastChref.model;
    CopyChref.model.animation  = PastChref.model.animation;
	if (CheckAttribute(PastChref,"heromodel")) CopyChref.heromodel = PastChref.heromodel;
	if (CheckAttribute(PastChref,"VISUAL_Ci")) CopyChref.heromodel = PastChref.heromodel;
    CopyChref.sex              = CopyChref.sex;
    CopyChref.headModel        = PastChref.headModel;
    CopyChref.FaceId           = PastChref.FaceId;
    CopyChref.nation           = PastChref.nation;

	CopyChref.name             = PastChref.name;
    CopyChref.lastname         = PastChref.lastname;

    CopyChref.rank             = PastChref.rank;
    CopyChref.reputation       = makeint(PastChref.reputation);
	CopyChref.baseCapIdx       = PastChref.index; //Id ������������� � ��������� �����

    if (CheckAttribute(PastChref, "loyality"))
    {
    	CopyChref.loyality         = PastChref.loyality;
	}
	else DeleteAttribute(CopyChref, "loyality");
	if (CheckAttribute(PastChref, "alignment"))
	{
    	CopyChref.alignment        = PastChref.alignment;
    }
    else DeleteAttribute(CopyChref, "alignment");

    CopyChref.Money            = PastChref.Money;

    CopyChref.chr_ai.hp         = makeint(PastChref.chr_ai.hp);
    if (CheckAttribute(PastChref,"PerkValue.HPPlus")) CopyChref.chr.chr_ai.hp_max = makeint(PastChref.chr_ai.hp_max)-80;
	else CopyChref.chr.chr_ai.hp_max = makeint(PastChref.chr_ai.hp_max);
	
	if (CheckAttribute(PastChref,"PerkValue.HPPlus")) LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max)-80, makeint(PastChref.chr_ai.hp_max)-80);
    else LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max), makeint(PastChref.chr_ai.hp_max));
	
	LAi_SetCurHPMax(CopyChref);
	//�������� ��������� quest �� ������������� ����, ����� ����� �� ������� :)
	if (CheckAttribute(PastChref, "quest"))
    {
	    aref arToCharQuest, arFromCharQuest;
		makearef(arFromCharQuest, PastChref.quest);
		makearef(arToCharQuest, CopyChref.quest);
		DeleteAttribute(arToCharQuest, "");
		CopyAttributes(arToCharQuest, arFromCharQuest);
	}
	if (CheckAttribute(PastChref, "quest.officertype"))
    {
        CopyChref.quest.officertype     =   PastChref.quest.officertype;
    }
    else
    {
        DeleteAttribute(CopyChref, "quest.officertype");
    }
    if (CheckAttribute(PastChref, "Payment"))
    {
        CopyChref.Payment     =   PastChref.Payment; // ������� ��
    }
    else
    {
        DeleteAttribute(CopyChref, "Payment");
    }
    if (CheckAttribute(PastChref, "HoldEquip"))
    {
        CopyChref.HoldEquip   =   PastChref.HoldEquip; // �� �������� ����� � �������
    }
	else
    {
        DeleteAttribute(CopyChref, "HoldEquip");
    }
    if (CheckAttribute(PastChref, "SaveItemsForDead"))
    {
        CopyChref.SaveItemsForDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "SaveItemsForDead");
    }
    if (CheckAttribute(PastChref, "DontClearDead"))
    {
        CopyChref.DontClearDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "DontClearDead");
    }
    if (CheckAttribute(PastChref, "OfficerWantToGo.DontGo"))
    {
        CopyChref.OfficerWantToGo.DontGo   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "OfficerWantToGo.DontGo");
    }
    // skill
    DeleteAttribute(CopyChref, "skill");
    CopyChref.skill = "";

    makearef(arToChar, CopyChref.skill);
    makearef(arFromChar, PastChref.skill);

    CopyAttributes(arToChar,arFromChar);

    // SPECIAL
    DeleteAttribute(CopyChref, "SPECIAL");
    CopyChref.SPECIAL = "";

    makearef(arToChar, CopyChref.SPECIAL);
    makearef(arFromChar, PastChref.SPECIAL);

    CopyAttributes(arToChar,arFromChar);

    // Statistic
    DeleteAttribute(CopyChref, "Statistic");
    CopyChref.Statistic = "";

    makearef(arToChar, CopyChref.Statistic);
    makearef(arFromChar, PastChref.Statistic);

    CopyAttributes(arToChar,arFromChar);

    // perks
    DeleteAttribute(CopyChref, "perks");
    CopyChref.perks = "";

    makearef(arToChar, CopyChref.perks);
    makearef(arFromChar, PastChref.perks);

    CopyAttributes(arToChar,arFromChar);
    // items
    DeleteAttribute(CopyChref, "Items");
    CopyChref.Items = "";

    makearef(arToChar, CopyChref.Items);
    makearef(arFromChar, PastChref.Items);

    CopyAttributes(arToChar,arFromChar);

    /*if (CheckAttribute(PastChref, "equip.blade"))
    {
		CopyChref.equip.blade =   PastChref.equip.blade;
	}
	if (CheckAttribute(PastChref, "equip.gun"))
    {
		CopyChref.equip.gun   =   PastChref.equip.gun;
	}*/
	makearef(arToChar, CopyChref.equip);
    makearef(arFromChar, PastChref.equip);
    CopyAttributes(arToChar,arFromChar);
	if (CheckAttribute(PastChref, "curammo"))
    {
		makearef(arToChar, CopyChref.curammo);
		makearef(arFromChar, PastChref.curammo);
		CopyAttributes(arToChar,arFromChar);
	}
	if (CheckAttribute(PastChref, "cirassId"))
    {
		CopyChref.cirassId =   PastChref.cirassId;
	}
	// health
	if (CheckAttribute(PastChref, "Health.TotalDamg"))
    {
		CopyChref.Health.TotalDamg =   PastChref.Health.TotalDamg;
	}
	else
	{
        CopyChref.Health.TotalDamg = 0;
	}
	// ugeen --> ����� ��� ��������� ��������� �������� � ����� ��������������� ����
	if (CheckAttribute(PastChref,"Situation")) // ���� � ����� ���� �������� �������� 
	{
		CopyChref.Situation = PastChref.Situation;
		CopyChref.Situation.type = PastChref.Situation.type;
	}
	
	if (CheckAttribute(PastChref,"EncType"))
	{
		CopyChref.EncType = PastChref.EncType;
	}
	
	if (CheckAttribute(PastChref,"RealEncounterType"))
	{
		CopyChref.RealEncounterType = PastChref.RealEncounterType;
	}
/*	
	if (CheckAttribute(PastChref,"curshipnum"))
	{
		CopyChref.curshipnum = PastChref.curshipnum;
	}
*/	
	if (CheckAttribute(PastChref,"Ship"))
	{
		makearef(arToChar, CopyChref.Back.Ship);
		makearef(arFromChar, PastChref.Ship);
		CopyAttributes(arToChar, arFromChar);		
	}
	// <-- ugeen
	if (CheckAttribute(PastChref,"TransferGoods"))
	{
		makearef(arToChar, CopyChref.TransferGoods);
		makearef(arFromChar, PastChref.TransferGoods);
		CopyAttributes(arToChar, arFromChar);		
	}
	if (CheckAttribute(PastChref,"TransferItems"))
	{
		makearef(arToChar, CopyChref.TransferItems);
		makearef(arFromChar, PastChref.TransferItems);
		CopyAttributes(arToChar, arFromChar);		
	}	
	if (CheckAttribute(PastChref,"selectedSet"))
	{
		makearef(arToChar, CopyChref.selectedSet);
		makearef(arFromChar, PastChref.selectedSet);
		CopyAttributes(arToChar, arFromChar);
		for (int i = 1; i < 7; i++)
		{
			if (CheckAttribute(PastChref,"Set"+i))
			{
				string SetNum = "Set"+i;
				makearef(arToChar, CopyChref.(SetNum));
				makearef(arFromChar, PastChref.(SetNum));
				CopyAttributes(arToChar, arFromChar);
			}
		}
	}
	if (_dialogCopy && CheckAttribute(PastChref, "Dialog.Filename"))
	{
	    CopyChref.Dialog.Filename    = PastChref.Dialog.Filename;
	    CopyChref.Dialog.CurrentNode = PastChref.Dialog.CurrentNode;
	    if (CheckAttribute(PastChref, "greeting")) CopyChref.greeting = PastChref.greeting; //eddy.��� �����!
		else
		{
			DeleteAttribute(CopyChref, "greeting");
		}
	}
	SetEnergyToCharacter(CopyChref);
	//SetNewModelToChar(CopyChref);  // ���� ����� ���� ����������
}

int GetCharacterLoyality(ref chr)
{
    if (CheckAttribute(chr, "loyality"))
    {
        if (sti(chr.loyality) > MAX_LOYALITY)
        {
            chr.loyality = MAX_LOYALITY;
        }
        if (sti(chr.loyality) < 0)
        {
            chr.loyality = 0;
        }
        return sti(chr.loyality);
    }
    else
    {
        return  0; // ��� ������� � ��
    }
}

// boal 091004 ����� ������  -->
// boal 23.01.2004 ����� ���������-->
void setNewMainCharacter(ref ch, int num)
{
	string heroModel, heroFaceId;
	int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    totalInfo = LanguageConvertString(idLngFile, "heroFace_" + num);
    heroFaceId  = sti(totalInfo);
    ch.FaceId   = heroFaceId;

    totalInfo = LanguageConvertString(idLngFile, "heroModel_" + num);
    ch.HeroModel = totalInfo;
    ch.model	= GetSubStringByNum(ch.HeroModel, 0);
    ch.headModel = "h_" + ch.model;

    totalInfo = LanguageConvertString(idLngFile, "heroName_" + num);
    ch.name 	=  totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "heroLastname_" + num);
    ch.lastname = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "sex_" + num);
    ch.sex = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "animation_" + num);
    ch.model.animation = totalInfo;

    if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}
    LanguageCloseFile(idLngFile);

    // ��� ���
    ch.HeroParam.HeroType = GetNewMainCharacterType(num);
    ch.nation             = GetNewMainCharacterNation(num);

}

void SetAllAchievements(int level)
{
	if (level == 0)
	{
		pchar.Statistic.Solder_g = 0
		pchar.Statistic.Solder_s = 0
		pchar.Statistic.Citizen_g = 0
		pchar.Statistic.Citizen_s = 0
		pchar.Statistic.Monster_g = 0
		pchar.Statistic.Monster_s = 0
		pchar.Statistic.Warrior_g = 0
		pchar.Statistic.Warrior_s = 0
		for(int i=1; i<8; i++)
		{
			string KS = "KillShip_"+i;
			string AS = "abordship_"+i;
			string KAS = "killabordship_"+i;
			pchar.Statistic.(KS) = 0;
			pchar.Statistic.(AS) = 0;
			pchar.Statistic.(KAS) = 0;
		}
		
		pchar.questTemp.depositcount = 0;
		pchar.questTemp.taxescount = 0;
		pchar.questTemp.bribescount = 0;
		pchar.questTemp.treasurecount = 0;
		pchar.questTemp.craftcount = 0;
		pchar.questTemp.stonescount = 0;
		pchar.questTemp.bookcount = 0;
		pchar.questTemp.poisoncount = 0;
		pchar.questTemp.criticalcount = 0;
		pchar.questTemp.bloodingcount = 0;
		pchar.questTemp.swiftcount = 0;
		pchar.questTemp.stuncount = 0;
		pchar.questTemp.traumacount = 0;
		pchar.questTemp.craftcount = 0;
		pchar.questTemp.healcount = 0;
		pchar.questTemp.genquestcount = 0;
		pchar.questTemp.officercount = 0;
		pchar.questTemp.chestcount = 0;
		pchar.questTemp.colonystate = 0;
		pchar.questTemp.foodcount = 0;
		pchar.questTemp.duelcount = 0;
		pchar.questTemp.tournamentcount = 0;
		pchar.questTemp.shipordercount = 0;
		pchar.questTemp.shipsearchcount = 0;
		pchar.questTemp.GoldFleetNum = 0;
	}
	pchar.achievements.rank = level; // ���������� �� ���� 175
	
	pchar.achievements.money = level; // ���������� �� ����� ���-�� ����� 175
	pchar.achievements.bank_money = level; // ����� ����� ������� � ���� 100
	
	if(bPortPermission) pchar.achievements.taxes = level;	// ���-�� ���������� �������� ������ 175 ---
	if(bBribeSoldiers) pchar.achievements.AchVzyatka = level; // ���-�� �������� ������  175 ---
	
	pchar.achievements.AchTreasure = level; // ���������� �� ����� 175
	pchar.achievements.AchChest = level; // ���������� �� ������� 175
	
	pchar.achievements.kills = level; // ���-�� ������� 175
	pchar.achievements.ship_kills = level; // ���-�� ����������� �������� 175
	pchar.achievements.skel_kills = level; // ���-�� ������� ������ 175
	pchar.achievements.poisons = level; // ���-�� ����������� ������ 175
	pchar.achievements.criticals = level; // ���-�� ����������� ������ 175
	pchar.achievements.AchBlood = level; // ���������� �� ������������ 175
	pchar.achievements.AchTravma = level; // ���������� �� ������ 175
	pchar.achievements.AchStanS = level; // ���������� �� ������ 175
	pchar.achievements.AchStanH = level; // ���������� �� ����� 175
	
	pchar.achievements.craft = level; // ���-�� ��������� ��������� 175
	pchar.achievements.books = level; // ���-�� ����������� ���� 175
	
	pchar.achievements.officers = level; // ���-�� ������� �������� 175
	pchar.achievements.ships = level; // ���-�� �������� � ������� 175
	
	pchar.achievements.heal_bottles = level; // ���-�� ������� ����� 175
	pchar.achievements.AchFood = level; // ���������� �� ��� 175
	
	pchar.achievements.AchTurnir = level; // ������� 175
	pchar.achievements.AchDuelyant = level; // ������� 175
	pchar.achievements.AchShipOrder = level; // ������ ����� :) 175
	pchar.achievements.AchSityRobbery = level; //������ ������� 175
	pchar.achievements.AchGoldFleet = level; //���������� �� 175
	if(bFillEncyShips) pchar.achievements.AchShipSearch = level; // ������� ��� ��������� 100
	pchar.achievements.AchBuildColony = level; // ���������� �� ������� 175
	pchar.achievements.gen_quests = level; // ����� ���-�� ����������� ������������ ������� 175
	
	pchar.achievements.AchOrion = level; // ������� 100 ---
	pchar.achievements.AchRabotorg = level; // �������� 100 ---
	pchar.achievements.AchKondotier = level; // ������ 100 ---
	pchar.achievements.AchTich = level; // ���������� 100 ---
	pchar.achievements.AchRagnar = level; // ������� ������ 100 ---
	pchar.achievements.AchSalazar = level; // ������ ������� 100 ---
	pchar.achievements.AchKaskos = level; // ������� ������� ������� 100 ---
	pchar.achievements.AchUmSamil = level; // ������� ���� �������-������ 100 ---
	pchar.achievements.LSC_quest = level; // ���������� ������ "���" 100
	pchar.achievements.Teno_quest = level; // ���������� ������ "�����������" 100
	pchar.achievements.Ghostship_quest = level; // ���������� ������ "�������-�������" 100
	pchar.achievements.Enchantcity_quest = level; // ���������� ������ "������������ �����" 100
	
	pchar.achievements.Killbeggars_quest = level; // ���������� ������ "����� ���� �����" 100
	pchar.achievements.Bluebird_quest = level; // ���������� ������ "���������� ������ ��" 100
	pchar.achievements.Berglarsgang_quest = level; // ���������� ������ "����� ���������� � ����� ������" 100
	pchar.achievements.Mummydust_quest = level; // ���������� ������ "������ ������� �����" 100
	if(pchar.sex != "woman") pchar.achievements.Isabella_quest = level; // ���������� ������ "������� ���������� ��������" 100
	if(Pchar.questTemp.CapBloodLine == 1) pchar.achievements.CapBladLine = level; // ���������� ������� ����� 100
	if(startherotype == 2) pchar.achievements.WhisperLine = level; // ���������� ������� ������ 100
	pchar.achievements.Nation_quest_E = level; // ���������� ������������ ������� ������� 100 ---
	pchar.achievements.Nation_quest_F = level; // ���������� ������������ ������� ������� 100 ---
	pchar.achievements.Nation_quest_H = level; // ���������� ������������ ������� ������� 100 ---
	pchar.achievements.Nation_quest_S = level; // ���������� ������������ ������� ������� 100 ---
	pchar.achievements.Nation_quest_P = level; // ���������� ������������ ������� ������� 100 ---
	
	// ����� ����� ��������� ��� ���������: 7500 (�� 100-175 �� ������ ����������) - ��� ���� ������������� (����������� ������, �����, ������! (c) LEOPARD :) )
	// �������������� ����� �������� 6700 ����� ����������, ���� ��������� 4 ������� �����, ������� �� ���������� � ����������
	// ����� ����������: 46
	// ��� ��������� ��������� � ��������� � 1 ������ ��� �������� �... 5050
}

void CreateOreModels()
{
	int ore1 = 0;
	int ore2 = 0;
	int ore3 = 0;
	int ore4 = 0;
	
	string locid;
	
	for(int i=0; i<nLocationsNum; i++)
	{
		if(locations[i].filespath.models == "locations\inside\DungeonDuffer1")
		{
			locid = locations[i].id;
			pchar.GenQuestRandItem.(locid).stay = true;
			pchar.GenQuestRandItem.(locid).randitem1 = "ore_mining1";
			pchar.GenQuestRandItem.(locid).randitem2 = "ore_mining3";

			ore1++;
			ore3++;
		}
		
		if(locations[i].filespath.models == "locations\inside\DungeonDuffer2")
		{
			locid = locations[i].id;
			pchar.GenQuestRandItem.(locid).stay = true;
			pchar.GenQuestRandItem.(locid).randitem1 = "ore_mining1";
			pchar.GenQuestRandItem.(locid).randitem2 = "ore_mining2";
			pchar.GenQuestRandItem.(locid).randitem3 = "ore_mining3";
			pchar.GenQuestRandItem.(locid).randitem4 = "ore_mining4";

			ore1++;
			ore2++;
			ore3++;
			ore4++;
		}
		
		if(locations[i].filespath.models == "locations\inside\grotto1")
		{
			locid = locations[i].id;
			pchar.GenQuestRandItem.(locid).stay = true;
			pchar.GenQuestRandItem.(locid).randitem1 = "ore_mining1";
			
			ore1++;
		}
		
		if(locations[i].filespath.models == "locations\inside\grotto2")
		{
			locid = locations[i].id;
			pchar.GenQuestRandItem.(locid).stay = true;
			pchar.GenQuestRandItem.(locid).randitem1 = "ore_mining2";
			
			ore2++;
		}
	}
	
	
	Log_TestInfo("������� ��������� �����: " + nLocationsNum);
	Log_TestInfo("�������� ��� �������: " + ore1);
	Log_TestInfo("���������� ��� �������: " + ore2);
	Log_TestInfo("������� ��� �������: " + ore3);
	Log_TestInfo("�������� ��� �������: " + ore4);
}
void initNewMainCharacter()
{
	ref ch = GetMainCharacter();
	string sTemp;
	int    iTmp, i;
	pchar.ach_points = 0; // ������������� ����� ���-�� ����� ���������� �� 0 

    setNewMainCharacter(ch, startHeroType);
    // �������� ������ -->
    ch.VersionNumber              = GetVerNum();
    ch.VersionNumberCompatibility = VERSION_NUM;
    // �������� ������ <--
    ch.nation     = NullCharacter.HeroParam.nation;
    ch.BaseNation = NullCharacter.HeroParam.nation;
    //MOD_EXP_RATE =  10;  ������ � ������ ���� (�����, �� 5 �� 15, 10 - �������� �� ���������)
    //MOD_EXP_RATE =  MOD_EXP_RATE + (MOD_SKILL_ENEMY_RATE)*6; // ������ ������ ��� ����
    MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666); // ������ ������ ��� ����
    if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10; // ����� ����� ������ ����������� ������, ����� ��������� ������ ��� ���� ����������.
    // ���� ������
	if (sti(ch.nation) != PIRATE)
	{
		if (sti(ch.nation) != SPAIN) ch.HeroParam.ToCityId = FindAlliedColonyForNation(sti(ch.nation), true);
			else ch.HeroParam.ToCityId = FindAlliedColonyForNationExceptColony("Caracas"); //������� �� �����, ��� ���������
	}
	else
	{
		ch.HeroParam.ToCityId = FindAlliedColonyForNationExceptColony("Pirates"); //������� �� �����, ���� ��� ���������� ����
	}
	//ch.HeroParam.ToCityId = "Santiago";
	// ������ ������
	ch.HeroParam.FromCityId  = Colonies[FindNonEnemyColonyForAdventure(sti(ch.nation), ch.HeroParam.ToCityId, true)].id;

	// ��� ��������
	if (sti(ch.nation) != PIRATE)
	{
	ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
	ch.HeroParam.Group    = "reload";
	ch.HeroParam.Locator  = "reload1";
	}
	else
	{
		ch.HeroParam.Location = ch.HeroParam.ToCityId + "_port";
		ch.HeroParam.Group    = "reload";
		ch.HeroParam.Locator  = "sea";
		if(startherotype == 2)
		{
			ch.HeroParam.Location = "PuertoPrincipe_port";
		}
	}
	if(startherotype == 3 || startherotype == 4)
	{
		ch.HeroParam.Location = "Shore57";
		ch.HeroParam.Group    = "reload";
		ch.HeroParam.Locator  = "boat";
	}
	setCharacterShipLocation(ch, ch.HeroParam.Location);
    setWDMPointXZ(ch.HeroParam.Location);  // ����� �� �����
	SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true); // to_do ��������� � ���� ����� ���������
	//��������� �������� �� ������� �������� ��� � 5 ����
	SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
    SetTimerCondition("Nation_Legend", 0, 0, 25 + rand(10), true);

	///  �������� ������������
	SetGovenourToCity(ENGLAND, "PortRoyal");
    SetGovenourToCity(SPAIN, "Havana");
    SetGovenourToCity(FRANCE, "Tortuga");
    SetGovenourToCity(HOLLAND, "Villemstad");
    // to_do PrepareVisitCity(); // ������ ����� �� ��������� ������ ��� ��������� ��� �� �����

    AddQuestRecordInfo("Tutorial_Dictonary", "1");
	AddQuestRecordInfo("Tutorial_Eng", "1");
	AddQuestRecordInfo("Tutorial_Fra", "1");
	AddQuestRecordInfo("Tutorial_Spa", "1");
	AddQuestRecordInfo("Tutorial_Hol", "1");
	AddQuestRecordInfo("Tenochtitlan_info", "9");
	AddQuestRecordInfo("Tenochtitlan_info", "8");
	AddQuestRecordInfo("Tenochtitlan_info", "7");
	AddQuestRecordInfo("Tenochtitlan_info", "6");
	AddQuestRecordInfo("Tenochtitlan_info", "5");
	AddQuestRecordInfo("Tenochtitlan_info", "4");
	AddQuestRecordInfo("Tenochtitlan_info", "3");
	AddQuestRecordInfo("Tenochtitlan_info", "2");
	AddQuestRecordInfo("Tenochtitlan_info", "1");
	AddQuestRecordInfo("Tutorial_Sharp", "1");
	AddQuestRecordInfo("Tutorial_Fight_Info", "1");
	AddQuestRecordInfo("Tutorial_ChangeLog_CSP", "1");
	AddQuestRecordInfo("Tutorial_WhoIsQUESTS_CSP", "1");

	ReloadProgressUpdate();
	pchar.questTemp.Achievements.Points = "0" // ���� ���������� �� ����

 	SetNationRelations();
 	// �� ���� �������
 	ch.HeroParam.EnemyNation  = FindEnemyNation2Nation(sti(ch.nation));
    // boal ������ ���������� �� ��������� ������� (��� ���� � �����) -->
    SetTimerCondition("SeaHunterCheck", 0, 0, 6, true);
    SaveCurrentQuestDateParam("Land_HunterTimerEng");
    SaveCurrentQuestDateParam("Land_HunterTimerFra");
    SaveCurrentQuestDateParam("Land_HunterTimerSpa");
    SaveCurrentQuestDateParam("Land_HunterTimerHol");
    //SaveCurrentQuestDateParam("Land_HunterTimerHasBeen");
    // boal ������ ���������� �� ��������� ������� (��� ���� � �����) <--
    LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP);

    ch.HeroParam.HeroType = NullCharacter.HeroParam.HeroType;

	SetSPECIAL(ch, 4,4,4,4,4,4,4); //���� ��� ��������� ������� ��� �� � ����� - ���� ����
	switch (ch.HeroParam.HeroType)
	{
        case "Master":	//������
    	    SetSPECIAL(ch, 10,5,10,4,7,8,6); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break; 

        case "Merchant":	//��������
    	    SetSPECIAL(ch, 8,6,5,9,9,3,10); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break;

	    case "Corsair":	//������������
         	SetSPECIAL(ch, 9,3,9,3,10,10,6); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break;
	    case "Adventurer":	//����������
    	    SetSPECIAL(ch, 7,8,7,8,8,5,7); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break;

		case "Inquisitor":	//��������
    	    SetSPECIAL(ch, 8,10,7,6,7,6,6); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)   
	    break;

	    case "SecretAgent":	//������ �����
    	    SetSPECIAL(ch, 7,7,6,10,6,7,7); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break;
		
		case "SeaWolf":	//������� ����
    	    SetSPECIAL(ch, 6,8,6,9,8,7,6); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	    break;

	}
	ch.skill.freeskill   = 0;
	ch.Skill.FreeSPECIAL = 0;
	sGlobalTemp   = "Flag" + NationShortName(sti(pchar.nation));
	SetCharacterPerk(pchar, sGlobalTemp); // ���� ����� �����
	if (sti(ch.nation) != PIRATE || startHeroType == 1) SetCharacterPerk(pchar, "FlagPir");
	else
	{
/* 		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "LongRangeGrappling"); */
		//pchar.reputation.spahunter = 20+rand(5);
	} 
	SetCharacterPerk(pchar, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
	// ��������� ����� ������
    InitStartParam(pchar);
    SetEnergyToCharacter(pchar);
    initMainCharacterItem();
    DeleteAttribute(pchar, "Ship");
    if (sti(ch.nation) != PIRATE)
	{
		pchar.Ship.Type = GenerateShipExt((SHIP_BERMSLOOP + rand(11)), 0, pchar);
		SetBaseShipData(pchar);
		pchar.Ship.Name = RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple("������� �����", "������ ����"), "�����������"), "��������"), "������"), "������"), "�������"), "����������"), "�������");
		SetCrewQuantityFull(pchar);
		ChangeCrewExp(pchar, "Sailors", 50);
		ChangeCrewExp(pchar, "Cannoners", 50);
		ChangeCrewExp(pchar, "Soldiers", 50);
		SetCharacterGoods(pchar, GOOD_SAILCLOTH, 20 + rand(50));
		SetCharacterGoods(pchar, GOOD_PLANKS, 20 + rand(50));
		SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
	}
	else
	{
		pchar.Ship.Type = GenerateShipExt((SHIP_BERMSLOOP + rand(11)), 0, pchar);
		SetBaseShipData(pchar);
		pchar.Ship.Name = "���������";
		SetCrewQuantityFull(pchar);
		ChangeCrewExp(pchar, "Sailors", 50);
		ChangeCrewExp(pchar, "Cannoners", 50);
		ChangeCrewExp(pchar, "Soldiers", 50);
		SetCharacterGoods(pchar, GOOD_SLAVES, 10 + rand(20));
		SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
	}
	// ������ �������
	pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)*0.05) * (MOD_SKILL_ENEMY_RATE);
	SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
	//Tutorial - ������ ����
    if (startHeroType == 1) //21/07/07 homo ��� ����� ���� ������ ������
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Estate";
    	pchar.quest.Tut_start.function                  = "Blood_StartGame";
		Pchar.questTemp.WhisperLine = false;
    }
    if (startHeroType == 2)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Bermudes_Dungeon";
    	pchar.quest.Tut_start.function                  = "Whisper_StartGame";
        Pchar.questTemp.CapBloodLine = false;
    }
	if (startHeroType == 3 || startHeroType == 4)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Shore57";
    	pchar.quest.Tut_start.function                  = "Sharp_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
    }
	if (startHeroType == 5 || startHeroType == 6)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Shore_ship2";
    	pchar.quest.Tut_start.function                  = "SharleMary_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
    }
	if (startHeroType > 6)
    {
    	pchar.quest.Tut_start.win_condition.l1          = "location";
    	pchar.quest.Tut_start.win_condition.l1.location = "Ship_deck_Low";
    	pchar.quest.Tut_start.function                  = "Tut_StartGame";
        Pchar.questTemp.CapBloodLine = false;
		Pchar.questTemp.WhisperLine = false;
        
    }
	
	// Warship ��� ������ �������
	// �����: ������� MaryCelesteInit() ������ ���� ���, � �� � initStartState2Character()
	// �.�. � ��� ���� ������� �������, ������� � ������� initStartState2Character() ��� �� ���������
	OtherQuestCharactersInit(); // ������������� ������ �������
	
	MaryCelesteInit(); // Warship 07.07.09 �������� "���� ������"
	
	// ��������� ��������� ������� ������
	PChar.DayRandom = Random();
	SetAllAchievements(0); // �������� ��� ����������	
}

void initMainCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
    //trace("initMainCharacterItem "  + ch.HeroParam.HeroType);
	switch (ch.HeroParam.HeroType)
	{
        case "Master":	// ������
			SetCharacterPerk(pchar, "Grunt");
            TakenItems(Pchar, "potion1", rand(10));
            TakenItems(Pchar, "potion2", rand(5));
            TakenItems(Pchar, "indian12", 1);
            TakenItems(Pchar, "Food1", rand(6)+4);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					GiveItem2Character(Pchar, "pistol2");
					EquipCharacterbyItem(Pchar, "Pistol2");
					TakeNItems(Pchar, "bullet", 5);
					AddItems(Pchar, "GunPowder", 5);
					GiveItem2Character(Pchar, "Spyglass1");
					EquipCharacterbyItem(Pchar, "Spyglass1");
					pchar.money = 1500/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					pchar.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					itemID = GetGeneratedItem("topor1");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					GiveGunAmmunitionPchar(Pchar,itemID,5);
					GiveItem2Character(Pchar, "Spyglass1");
					EquipCharacterbyItem(Pchar, "Spyglass1");
					pchar.money = 1000/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					itemID = GetGeneratedItem("pistol" + (rand(2)+1));
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					GiveGunAmmunitionPchar(Pchar,itemID,5);
				break;
				case SPAIN:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
					pchar.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

        case "Merchant":	// ��������
			SetCharacterPerk(pchar, "Trader");
			itemID = GetGeneratedItem("blade1");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			GiveItem2Character(Pchar, "Ship_Print_6");
			TakenItems(Pchar, "potion1", rand(10));
			TakenItems(Pchar, "Food1", (rand(6)+4));
			switch (sti(ch.nation))
			{
				case ENGLAND:
					GiveItem2Character(Pchar, "Map_bad");
					TakeNItems(Pchar, "indian3", 1);
					pchar.money = 15000/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					TakenItems(Pchar, "potion1", 2);
					TakeNItems(Pchar, "indian3", 1);
					GiveItem2Character(Pchar, "Spyglass1");
					EquipCharacterbyItem(Pchar, "Spyglass1");
					pchar.money = 10000/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					TakeNItems(Pchar, "indian3", 1);
					GiveItem2Character(Pchar, "Spyglass3");
					EquipCharacterbyItem(Pchar, "Spyglass3");
					pchar.money = 11000/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					GiveItem2Character(Pchar, "Map_Normal");
					GiveItem2Character(Pchar, "pistol2");
					EquipCharacterbyItem(Pchar, "Pistol2");
					TakeNItems(Pchar, "bullet", 10);
					AddItems(Pchar, "GunPowder", 10);
					GiveItem2Character(Pchar, "Spyglass1");
					EquipCharacterbyItem(Pchar, "Spyglass1");
					pchar.money = 5000/MOD_SKILL_ENEMY_RATE;
				break;
				case SPAIN:
					TakeNItems(Pchar, "indian14", 1);
					TakeNItems(Pchar, "jewelry8", 1);
					TakeNItems(Pchar, "jewelry9", 1);
					pchar.money = 8000/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

	    case "Corsair":	// ������������
			SetCharacterPerk(pchar, "Fencer");
			itemID = GetGeneratedItem("Spyglass" + (rand(2)+1));
			GiveItem2Character(Pchar, itemID);
			EquipCharacterbyItem(Pchar, itemID);
			itemID = GetGeneratedItem("blade" + (rand(8)+1));
			GiveItem2Character(Pchar, itemID);
			EquipCharacterbyItem(Pchar, itemID);
			TakenItems(Pchar, "potion1", rand(10));
            TakenItems(Pchar, "Food1", rand(6)+4);
			itemID = GetGeneratedItem("pistol" + (rand(2)+1));
			GiveItem2Character(Pchar, itemID);
			EquipCharacterbyItem(Pchar, itemID);
			GiveGunAmmunitionPchar(Pchar,itemID,10);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					pchar.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					GiveGunAmmunitionPchar(Pchar,itemID,10);
					pchar.money = 1000/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					pchar.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					GiveItem2Character(Pchar, "Map_part1");
				break;
				case SPAIN:
					pchar.money = 2000/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

	    case "Adventurer":	// ����������
			SetCharacterPerk(pchar, "Adventurer");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			TakenItems(Pchar, "potion1", rand(10));
			GiveItem2Character(Pchar, "Totem_" + rand(15));
			GiveItem2Character(Pchar, "Totem_" + rand(15));
			GiveItem2Character(Pchar, "Totem_" + rand(15));
	        itemID = GetGeneratedItem("Spyglass" + rand(3));
			GiveItem2Character(Pchar, itemID);
			EquipCharacterbyItem(Pchar, itemID);
			pchar.money = 3000/MOD_SKILL_ENEMY_RATE;
            TakenItems(Pchar, "Food1", rand(1)+2);
			itemID = GetGeneratedItem("pistol" + (rand(2)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			GiveGunAmmunitionPchar(Pchar,itemID,10);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					itemID = GetGeneratedItem("blade7");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
				break;
				case FRANCE:
					GiveGunAmmunitionPchar(Pchar,itemID,10);
					itemID = GetGeneratedItem("blade12");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
				break;
				case HOLLAND:
					itemID = GetGeneratedItem("blade3");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
				break;
				case PIRATE:
					GiveGunAmmunitionPchar(Pchar,itemID,10);
					itemID = GetGeneratedItem("blade1");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
				break;
				case SPAIN:
					itemID = GetGeneratedItem("blade18");
					GiveItem2Character(Pchar, itemID);
					EquipCharacterbyItem(Pchar, itemID);
				break;
			}
	    break;

	    case "Inquisitor":	// ��������
			SetCharacterPerk(pchar, "Buccaneer");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			itemID = GetGeneratedItem("mushket_drob");
            GiveItem2Character(Pchar, itemID);
			TakeNItems(Pchar, "bullet", 30);
			AddItems(Pchar, "GunPowder", 30);
			GiveGunAmmunitionPchar(Pchar,itemID,30);
			TakenItems(Pchar, "potion1", rand(10));
			pchar.money = 1000/MOD_SKILL_ENEMY_RATE;
            TakenItems(Pchar, "Food1", rand(6)+4);
	    break;

	    case "SecretAgent":	// ������ �����
			SetCharacterPerk(pchar, "Agent");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			TakenItems(Pchar, "Food1", rand(6)+4);
			TakenItems(Pchar, "jewelry15", 1);
			TakenItems(Pchar, "Totem_2", 1);
			TakenItems(Pchar, "indian5", 1);
			TakenItems(Pchar, "indian17", 1);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					GiveItem2Character(Pchar, "patent_eng");
				break;
				case FRANCE:
					GiveItem2Character(Pchar, "patent_fra");
				break;
				case HOLLAND:
					GiveItem2Character(Pchar, "patent_hol");
				break;
				case PIRATE:
					SetCharacterPerk(pchar, "FlagEng");
					SetCharacterPerk(pchar, "FlagFra");
					SetCharacterPerk(pchar, "FlagSpa");
					SetCharacterPerk(pchar, "FlagHol");
				break;
				case SPAIN:
					GiveItem2Character(Pchar, "patent_spa");
				break;
			}
	    break;
		
		case "SeaWolf":	// ������� ����
			SetCharacterPerk(pchar, "SeaWolf");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			GiveItem2Character(Pchar, "Ship_Print_6");
			itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
	        itemID = GetGeneratedItem("Spyglass" + rand(3));
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
			GiveGunAmmunitionPchar(Pchar,itemID,10);
			TakenItems(Pchar, "potion1", rand(8));
			pchar.money = 2000/MOD_SKILL_ENEMY_RATE;
            TakenItems(Pchar, "Food1", rand(6)+4);
	    break;
	}
}
int GetNewMainCharacterFace()
{
    return sti(GetNewMainCharacterParam("heroFace_" + startHeroType));
}

string GetNewMainCharacterName()
{
    return GetHeroName(startHeroType);
}

string GetMainCharacterNameGen()  // ==> eddy. ����������� ����� ������� ����� ��
{
    return GetHeroNameGen(startHeroType);
}
string GetMainCharacterNameDat()  // ==> eddy. ��������� ����� ������� ����� ��
{
    return GetHeroNameDat(startHeroType);
}

string GetHeroName(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroName_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastname_" + _n);

    return totalInfo;
}

string GetHeroNameGen(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameGen_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameGen_" + _n);

    return totalInfo;
}
string GetHeroNameDat(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameDat_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameDat_" + _n);

    return totalInfo;
}
int GetNewMainCharacterNation(int _startHeroType)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, "heroNation_" + _startHeroType);
    LanguageCloseFile(idLngFile);

    switch(totalInfo)
	{
		case "������":
            return ENGLAND;
		break;
		case "�������":
            return FRANCE;
		break;
		case "�������":
            return SPAIN;
		break;
		case "���������":
			return HOLLAND;
		break;
		case "��������� ��������":
			return PIRATE;
		break;
		case "ENGLAND":
            return ENGLAND;
		break;
		case "FRANCE":
            return FRANCE;
		break;
		case "SPAIN":
            return SPAIN;
		break;
		case "HOLLAND":
			return HOLLAND;
		break;
		case "PIRATE":
			return PIRATE;
		break;
	}
	return PIRATE;
}

string GetNewMainCharacterType(int _startHeroType)
{
    string ret = GetNewMainCharacterParam("heroType_" + _startHeroType);

    switch (ret) // ����� �� ��������� ��� ���������
	{
        case "��������":
    	    ret = "Merchant";
	    break;

	    case "������":
    	    ret = "Master";
	    break;

	    case "������������":
            ret = "Corsair";
	    break;

	    case "����������":
            ret = "Adventurer";
	    break;

	    case "��������":
            ret = "Inquisitor";
	    break;

	    case "������ �����":
            ret = "SecretAgent";
	    break;
		
		case "������� ����":
            ret = "SeaWolf";
	    break;
	}
    return ret;
}

string GetNewMainCharacterParam(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// ������� ������� ����� �� ��� ������
int GetBaseHeroNation()
{
	if (isMainCharacterPatented())
	{
	    return sti(Items[sti(pchar.EquipedPatentId)].Nation);
	}
	return sti(pchar.BaseNation);
}