/*

	��������� ���� ����� attackType:
	"fast" ������� �����
	"force" �������
	"round" ��������
	"break" ����������� ����
	"feint" ����� ����� �����


*/

//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//��������� ����������� ��� ���������
//#20200522-01
float LAi_CalcDamageForBlade(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	//����������� ����������� �� �����
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmgbldmin"))
	{
		min = stf(attack.chr_ai.dmgbldmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmgbldmax"))
	{
		max = stf(attack.chr_ai.dmgbldmax);
	}
	//float bladeDmg = min + frand((max - min));//*(rand(10)*0.1);
	float bladeDmg = min + (max - min)*frandSmall(LAi_GetCharacterFightLevel(attack));
	//���������� � ����������� �� ������
	float aSkill = LAi_GetCharacterFightLevel(attack);
	float eSkill = LAi_GetCharacterFightLevel(enemy);
	//float kSkillDmg = 1.0;
	//kSkillDmg = 1.0 * (1.0 + (0.3 * aSkill));
    if (aSkill < eSkill)
	{
		bladeDmg = bladeDmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	
	// Warship 27.08.09 ��� ������� �����������
	// ���� ������� ������ ������� (���������� ��������), �� ������ ����� ��� ����� ������
	if(sti(enemy.Rank) > 50)
	{
		bladeDmg = bladeDmg * 45 / sti(enemy.Rank);
	}
	
	if(CheckAttribute(loadedLocation, "CabinType") && sti(enemy.index) == GetMainCharacterIndex())
	{
		bladeDmg = bladeDmg * (1.0 + stf(attack.rank)/100);
	}
	//���������� � ����������� �� �����
	float kAttackDmg = 1.0;
	
	// TO_DO ����������� �� ����� ����������
	//if (sti(attack.index) == GetMainCharacterIndex()) Log_Info(attackType);
	switch(attackType)
	{
		case "fast":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}else{
				kAttackDmg = 0.7;
			}
			break;
		case "force":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}else{
				kAttackDmg = 1.0;
			}
			break;
		case "round":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}else{
				kAttackDmg = 0.6;
			}
			if(CheckCharacterPerk(attack, "BladeDancer"))
			{
				kAttackDmg = kAttackDmg * 1.3;
			}
			break;
		case "break":
			if(isBlocked)
			{
				//#20200510-03
                if(blockSave) {
                    kAttackDmg = 1.0;
                }
				else {
                    kAttackDmg = 2.0;
				}
			}else{
				kAttackDmg = 3.0;
			}
		break;
		
		case "feintc":  // ���� ����� �������� ���� //��������� ����������� �����
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}else{
				kAttackDmg = 0.8;
			}
		break;
		
		case "feint":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}else{
				kAttackDmg = 0.5;
			}
		break;
	}
	if (kAttackDmg > 0)  // ����������� boal
	{
		//�������������� ������
		float dmg = bladeDmg * kAttackDmg; // *kArcadeDmg * kSkillDmg
		if(CheckCharacterPerk(attack, "HardHitter"))  
		{
			if(CheckAttribute(enemy, "chr_ai.energy"))
			{
				enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.9); //fix
			}
		}
		// ��������� ���� �������� 
		if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))
		{
			if (enemy.chr_ai.group == LAI_GROUP_PLAYER)
			{
				dmg = dmg / MOD_Complexity_1_DMG;
			}
		}
		if (attack.model.animation == "mushketer" && IsMainCharacter(attack))															   
		{
			dmg = dmg / 3.0;
		}
		
		//Boyer mod #20170318-33 difficulty level rebalancing
		//if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())
		if (MOD_SKILL_ENEMY_RATE < 10 && sti(enemy.index) == GetMainCharacterIndex())
		{
			dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
		}
		return dmg;
	}
	return 0.0;
}

//��������� ���������� ���� ��� ����� ������
//#20200522-01
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked, float dmg, bool blockSave)
{
	//��������� ��������� ����
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));

	switch(attackType)
	{
		case "break":
			if(isBlocked)
			{
				//#20200510-03
                if(blockSave) {
                    dmg = dmg*0.85;
                }
				else {
                    dmg = dmg*1.1;
				}
			}else{
				dmg = dmg*1.2;
			}
		break;
		case "feint":
			dmg = dmg*1.5;
		break;
		case "feintc":
			dmg = dmg*1.5;
		break;
	}
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
	return dmg;
}

//�������, ����������� ��� ������� ��������
float LAi_CalcUseEnergyForBlade(aref character, string actionType)
{
	float energy = 0.0;
	switch(actionType)
	{
		case "fast":
			energy = 10.0;
		break;
		case "force":
			energy = 7.0;
		break;
		case "round":
			energy = 14.0;
		break;
		case "break":
			energy = 25.0;
		break;
		//case "feint":
		//	energy = 7.0;
		//break;
		//case "parry": 
		//	energy = 20.0;
		//break;
		case "hit_parry":  // boal fix ��� ������� ������ �� ���������, � ��������� � �������� fgt_hit_parry
			energy = 20.0;
		break;
		case "feintc":
			energy = 7.0; // ������ ��� ������ �����
		break;
	}
	/*if(CheckCharacterPerk(character, "BladeDancer"))  // to_do
	{
		energy = energy * 0.9;
	}*/
	 // ������ ��� ����
	/*if(character.id == pchar.id || character.chr_ai.group == LAI_GROUP_PLAYER)
	{
		energy = energy * (1.05 - (0.025 * MOD_SKILL_ENEMY_RATE));
	} */
	if (energy > 0.0)  // �����������
	{
		float fSkill = LAi_GetCharacterFightLevel(character);  // stf(character.skill.fencing) - �� ��� ��� ������!!
		fSkill = (1.0 - (0.3 * fSkill));
		energy = energy * fSkill * LAi_GetBladeEnergyType(character);  // ������������� �� ����
	}
	return energy;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float fMultiplier = 1.6666667;

	if(CheckCharacterPerk(chr, "Energaiser")) // ������� ���� ������ � ��
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless")) 
	{
		fMultiplier = fMultiplier * 1.15;
	}
    // ������ ��� ����
	/*
	if(chr.id == pchar.id || chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
		fMultiplier = fMultiplier * (1.0 + (0.025 * MOD_SKILL_ENEMY_RATE));
	}
	*/
	float fEnergy;
	fEnergy = curEnergy + dltTime * fMultiplier; 

	return fEnergy;
}


//--------------------------------------------------------------------------------
//Gun parameters
//--------------------------------------------------------------------------------

//��������� ����������� ���������
float LAi_GunCalcProbability(aref attack, float kDist)
{
	//���� ������, �� ������ �����
	if(kDist >= 0.9) return 1.0;
	//��������� ����������� �� ����� �������
	float pmin = 0.3;
 	if(CheckAttribute(attack, "chr_ai.accuracy")) // boal ��� �������� ������ ���������, � �� ����!
	{
		pmin = stf(attack.chr_ai.accuracy);
	}
 	//�������� ������� �� �����
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//����������� ��������� � ������� �������
	float p = pmin + (1.0 - pmin)*(kDist/0.9);
 	//������ �������
	if(IsCharacterPerkOn(attack, "GunProfessional"))
	{
		p = p + 0.25;
	}else{
		if(IsCharacterPerkOn(attack, "Gunman"))
		{
			p = p + 0.1;
		}
	}
	// ���� ����� ������ 1 - ����� 100% �����
	return p;
}

//�������� ����������� �� ���������
float LAi_GunCalcDamage(aref attack, aref enemy)
{
	//����������� �����������
	float min = 10.0;
	float max = 10.0;
	if(CheckAttribute(attack, "chr_ai.dmggunmin"))
	{
		min = stf(attack.chr_ai.dmggunmin);
	}
	if(CheckAttribute(attack, "chr_ai.dmggunmax"))
	{
		max = stf(attack.chr_ai.dmggunmax);
	}
	//��������� �����
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck
	
	float dmg = min + (max - min)*frandSmall(aSkill);
	//�������������� ����������� �� pistol � ������ ������
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	// ��������� ���� �������� 
	if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))
	{
		if (enemy.chr_ai.group == LAI_GROUP_PLAYER)
		{
			dmg = dmg * MOD_Complexity_1_DMG;
		}
	}
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	//if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())
	if (MOD_SKILL_ENEMY_RATE < 10 && sti(enemy.index) == GetMainCharacterIndex())
	{
		dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
	}
	return dmg;
}

//��������� ���������� ���� ��� ��������� �� ���������
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
    //��������� ��������� ����
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
    return dmg;
}

//��������� ������� �������� ����������� ���������
float LAi_GunReloadSpeed(aref chr)
{
	//������� ������� ��������� �������� �������
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai.charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.charge_dlt);
	}
	//������������ ������
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//���� �������
	if(IsCharacterPerkOn(chr, "GunProfessional"))
	{
		charge_dlt = charge_dlt*1.25;
	}else{
		if(IsCharacterPerkOn(chr, "Gunman"))
		{
			charge_dlt = charge_dlt*1.1;
		}
	}
	return charge_dlt;
}

//--------------------------------------------------------------------------------
//All
//--------------------------------------------------------------------------------

/*float LAi_CalcDeadExp(aref attack, aref enemy)
{
	//��������� ��������� ����
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	float dmg = (0.5 + 4.0*LAi_GetCharacterFightLevel(enemy))*LAi_GetCharacterMaxHP(enemy);
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));
	return dmg*0.5;
} */

//--------------------------------------------------------------------------------
//Calculate total
//--------------------------------------------------------------------------------

//���������� ����������� ��� ����� �����
//#20200522-01
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	//���� �����������, �� ��������� ���
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//��������� �����������
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked, blockSave);
	float critical = 0.0;
	if(IsCharacterPerkOn(attack, "SwordplayProfessional"))
	{
		if(rand(100) <= 15)
		{
			critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
		}
	}else{
		if(IsCharacterPerkOn(attack, "CriticalHit"))
		{
			if(rand(100) <= 5)
			{
				critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
			}
		}
	}

	float kDmg = 1.0;
	if(IsCharacterPerkOn(attack, "Rush"))
	{
		kDmg = 3.0;
	}
	float kDmgRush = 1.0;
	if(IsCharacterPerkOn(enemy, "Rush"))
	{
		kDmgRush = 0.5;
	}
	dmg = dmg*kDmg*kDmgRush;
	//������ ����� ������
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))
	{
		if(attack.chr_ai.group == enemy.chr_ai.group)
		{
			dmg = 0.0;
			critical = 0.0;
			noExp = true;
		}
	}
	if(isBlocked || CheckAttribute(enemy, "cirassId"))// ���� ������ ��� ����, �� �������� ����������
	{
		critical = 0;
	}
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
			Log_TestInfo(" " + critical + " �����");
		}
	}
	kDmg = 1.0;
	if(IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	if(IsCharacterPerkOn(enemy, "AdvancedDefense")) kDmg = 0.8;
	if(IsCharacterPerkOn(enemy, "SwordplayProfessional")) kDmg = 0.7;

	// ��� 1.2.3
	dmg = dmg*kDmg;
	dmg = dmg *(1 + critical);//dmg + critical;
	if(CheckAttribute(enemy, "cirassId"))
	{
		dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
	}
	if(dmg > 0.0)
	{
		//������� �����������
		LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
		//�������� �� ������
		LAi_CheckKillCharacter(enemy);
		//�������� �� ����������
		MakePoisonAttackCheckSex(enemy, attack);
	}
	//���� �� ������ � ����
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//��������� �����
	float exp = LAi_CalcExperienceForBlade(attack, enemy, attackType, isBlocked, dmg, blockSave);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	} */
	if(LAi_IsDead(enemy))
	{
		//�������� �� ��������
		//exp = exp + LAi_CalcDeadExp(attack, enemy);
		//exp = LAi_GetCharacterMaxHP(enemy) * 10;
		//noExp = false;
		//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
		/*if(!isSetBalde)
		{
			//LAi_ChangeReputation(attack, -3);
		}*/
		// boal  check skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), makefloat(10.0 + ((1 + re) / (1+ra))*6.5));
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_s");
        // boal statistic info 17.12.2003 <--
        LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(!isSetBalde)
	{
		exp = 0.0;
	}
	
	if (!noExp)
    {
        //AddCharacterExp(attack, MakeInt(exp*0.5 + 0.5));
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), Makefloat(exp*0.2));
    }
	
}
//boal 19.09.05 -->
void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBalde)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBalde)
			{
				LAi_ChangeReputation(attack, -1);   // to_do
				if (rand(1) && CheckAttribute(enemy, "City"))
				{
					ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 1);
				}
			}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		// ����� ����� �� �������� � ������ boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// ����� �������� �� ����� � ������
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // ����������
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
	}
}
// boal <--

//���������� ����������� ��� ���������
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist)
{
	Lai_CharacterChangeEnergy(attack, -4); // ���� ������� �� ������� boal 20/06/06
	//���� �����������, �� ��������� ���
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//����������� ���������
	float p = LAi_GunCalcProbability(attack, kDist);
	//���� ������������, �� ������
	if(rand(10000) > p*10000) return;	  
	// boal ���� �������� ������, � �� ���� � ����� 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId"))
	{
        if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500) return;
	}
	// boal 23.05.2004 <--
	//��������� �����������
	float damage = LAi_GunCalcDamage(attack, enemy);

	//������ ����� ������
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group"))
	{
		if(CheckAttribute(enemy, "chr_ai.group"))
		{
			if(attack.chr_ai.group == enemy.chr_ai.group)
			{
				damage = 0.0;
				noExp = true;
			}
		}
	}
	if(damage > 0.0)
	{
		LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5));	
		//�������� �� ������
		LAi_CheckKillCharacter(enemy);
	}
	//���� �� ������ � ����
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//��������� ����
	float exp = LAi_GunCalcExperience(attack, enemy, damage);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	}  */
	if(LAi_IsDead(enemy))
	{
		//�������� �� ��������
		//exp = exp + LAi_CalcDeadExp(attack, enemy);
		//exp = LAi_GetCharacterMaxHP(enemy) * 10;
		//noExp = false;
		//if(!isSetBalde)
		//{
			//LAi_ChangeReputation(attack, -3);
		//	exp = 0.0;
		//}
		//DoCharacterKilledStatistics(sti(attack.index), sti(enemy.index));
		// boal skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
        AddCharacterExpToSkill(attack, SKILL_PISTOL, makefloat(15.0 + ((1 + re) / (1+ra))*12.0));
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal skill <--
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--
        
        //�������� �� ��������
		/*exp = exp + */
        //LAi_CalcDeadExp(attack, enemy); // ��������� ������ �� ���� � ������
  		LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(!isSetBalde)
	{
		//LAi_ChangeReputation(attack, -1);
		exp = 0.0;
	}
	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, Makefloat(exp*0.85));
    }
}

//--------------------------------------------------------------------------------
//��������� NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//�����
//�������� ���������� ����������� ����� � �������  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//��� ������ ����� "fast", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	return npc_return_tmp;
}

//��� ������ ����� "force", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightForce","LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	return npc_return_tmp;
}

//��� ������ ����� "round", 0 - ������� �� ��������, ���� ������ <3 �� ���� �� ����������
#event_handler("NPC_Event_GetAttackWeightRound","LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	return npc_return_tmp;
}

//��� ������ ����� "break", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightBreak","LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//��� ������ ����� "feint", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightFeint","LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//���������� ������
//����������� ������� ��������� - ����� � ����� ������������ �������� 2 ���� � �������
#event_handler("NPC_Event_GetDefenceActive","LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	//npc_return_tmp = 0.05 + level*0.4;
	npc_return_tmp = 0.3 + level*0.35;
	/*if (!iArcadeFencingAI)	// to_do
	{
		npc_return_tmp = npc_return_tmp + 0.2;
	}*/
	return npc_return_tmp;
}

// boal 20.01.08 ������� - �������, ��� ������ ��� ����, ����� ��� � ��� � �������������. ��� ��� ���������� � 0-1 �� ���� ����� �����, �� ���� ���������� ��������� �� ��������� ��� ����� ������������ ����� �� ������ �������, � �� ��������� ����
// ������ ���� ������ - ��� ����� � ������ (���� + ����)
//��� ������ �����, 0 - ������� �� ��������
#event_handler("NPC_Event_GetDefenceWeightBlock","LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));   // boal
	return npc_return_tmp;
}

//��� ������  ������������, 0 - ������� �� ��������
//����� � ����� ������������ �������� 2 ���� � �������
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//�������� �� ������
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//��������� ��������
//����������� ������� ���������� - ����� � ����� ������������ �������� 2 ���� � �������
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal ���� ������� ����� �� ���� ������� -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal ���� ������� ����� �� ���� ������� <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.1 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
	}
	//if (npc_return_tmp > 0.5) npc_return_tmp = 0.5;
	
	return npc_return_tmp;
}

//�������� �� �������
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
	/*float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmpb = false;
	if(!iArcadeFencingAI)
	{
		level = level + 0.02;
	}
	else
	{
		level = level - 0.01;
	}
	if(level > 0.1) npc_return_tmpb = true;
	return npc_return_tmpb;    */
}

//�������� �� ��������� ��������� ���� ����� ������� - ������������ ���������
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		npc_return_tmpb = false;
	}else{
		npc_return_tmpb = true;
	}
	return npc_return_tmpb;
}


//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//������� ���� �� �����
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//������� �����������
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg));
	//�������� �� ������
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	return npc_return_tmpb;
}
//#20200510-03
#event_handler("Event_ChrFeint_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrBlock_Init", "LAi_BlockInitTime");
#event_handler("Event_ChrParry_Init", "LAi_BlockInitTime");
void LAi_BlockInitTime()
{
	aref chr = GetEventData();
	float fSet = GetEventData();
	chr.chr_ai.BlockInitTime = fSet;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
}

//�������� ������������� ������������� �������
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//���������� ������� ����������� ������ �������������� �������� �����
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//���������� ������� ����������� ������ �������������� �������� �������
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}
