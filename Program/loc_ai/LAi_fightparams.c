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
	if (findsubstr(attack.model.animation, "mushketer" , 0) != -1)
	{
		min = 10.0;
		max = 20.0;
	}
	
	float atSkill = LAi_GetCharacterFightLevel(attack);
	string fencing_type = LAi_GetBladeFencingType(attack);
	/*if (CheckAttribute(attack,"chr_ai.Trauma"))
	{
		atSkill = atSkill - 0.25;
		if (atSkill < 0.0) atSkill = 0.01;
	}*/
	if (rand(1)==0) atSkill = atSkill - (rand(5)*0.02);
	else atSkill = atSkill + (rand(5)*0.02);
	if (atSkill<0.0) atSkill *= -1;
	
	float bladeDmg = min + (max - min)*atSkill);
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
	if (bAltBalance)
	{
		switch(attackType)
		{
			case "fast": // ������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.35;
					}
				}
				else
				{
					kAttackDmg = 0.7;
				}
				if (fencing_type != "Fencing") kAttackDmg *= 0.6;
			break;
			case "force": // ������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.5;
					}
				}
				else
				{
					kAttackDmg = 1.0;
				}
				if (fencing_type != "FencingLight") kAttackDmg *= 0.6;
			break;
			case "round": // �������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.3;
					}
				}
				else
				{
					kAttackDmg = 0.6;
				}
				if(CheckCharacterPerk(attack, "BladeDancer"))
				{
					kAttackDmg = kAttackDmg * 1.3;
				}
				if (fencing_type != "Fencing") kAttackDmg *= 0.6;
				break;
			case "break": // ����������� ����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 1.0;
					}
					else 
					{
						kAttackDmg = 2.0;
					}
				}
				else
				{
					kAttackDmg = 3.0;
				}
				if (fencing_type != "FencingHeavy") kAttackDmg *= 0.6;
			break;
			
			case "feintc":  // ���� ����� �������� ���� //��������� ����������� �����
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.8;
				}
				if (fencing_type != "FencingLight") kAttackDmg *= 0.6;
			break;
			
			case "feint":
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.5;
				}
			break;
		}
	}
	else
	{
		switch(attackType)
		{
			case "fast": // ������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.35;
					}
				}
				else
				{
					kAttackDmg = 0.7;
				}
			break;
			case "force": // ������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.5;
					}
				}
				else
				{
					kAttackDmg = 1.0;
				}
			break;
			case "round": // �������� �����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 0.0;
					}
					else 
					{
						kAttackDmg = 0.3;
					}
				}
				else
				{
					kAttackDmg = 0.6;
				}
				if(CheckCharacterPerk(attack, "BladeDancer"))
				{
					kAttackDmg = kAttackDmg * 1.3;
				}
				break;
			case "break": // ����������� ����
				if(isBlocked)
				{
					if(blockSave) 
					{
						kAttackDmg = 1.0;
					}
					else 
					{
						kAttackDmg = 2.0;
					}
				}
				else
				{
					kAttackDmg = 3.0;
				}
			break;
			
			case "feintc":  // ���� ����� �������� ���� //��������� ����������� �����
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.8;
				}
			break;
			
			case "feint":
				if(isBlocked && blockSave)
				{
					kAttackDmg = 0.0;
				}
				else
				{
					kAttackDmg = 0.5;
				}
			break;
		}
	}
	if (kAttackDmg > 0)  // ����������� boal
	{
		if (findsubstr(attack.model.animation, "mushketer" , 0) != -1)
		{
			string at = RecalculateMushketHitsType(attack);
			//Log_Info(at);
			if (at != "")
			{
				if (at == "break" && attackType == at) kAttackDmg += 1.5;
				if (at == "force" && attackType == at) kAttackDmg += 1.0;
			}
		}
		if(CheckCharacterPerk(attack, "Agent"))  
		{
			if (attackType == "feintc") kAttackDmg *= 2;
		}
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

string RecalculateMushketHitsType(aref attack)
{
	if (IsEquipCharacterByItem(attack, "mushket") || IsEquipCharacterByItem(attack, "mushket2"))
	{
		return "break";
	}
	if (IsEquipCharacterByItem(attack, "mushket_SeaCarbine"))
	{
		return "force";
	}
	return "";
}

//��������� ���������� ���� ��� ����� ������
//#20200522-01
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked,float dmg, bool blockSave)
{
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
	//��������� ��������� ����
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank")) ra = stf(attack.rank);
	if (CheckAttribute(enemy, "rank")) re = stf(enemy.rank);
	
	if (ra < 1.0) ra = 1.0;
	if (re < 1.0) re = 1.0;
	float exp = dmg * ((1.0 + re*0.5)/(1.0 + ra*0.5));//Lipsar �����e��� �����

	switch (attackType)
	{
	case "break":
		if (isBlocked)
		{
			exp = exp * 1.1;
		}
		else
		{
			exp = exp * 1.2;
		}
		break;
	case "feint":
		exp = exp * 1.5;
		break;
	case "feintc":
		exp = exp * 1.5;
		break;
	}
	return exp;
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
		// case "feint":
			// energy = 7.0;
		// break;
		// case "parry": 
			// energy = 20.0;
		// break;
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
	if(CheckAttribute(chr, "bonusEnergy"))
	{
		fMultiplier = fMultiplier * 2;
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
	float p = pmin + (1.0 - pmin)*(kDist/0.9)+(GetCharacterSPECIALSimple(attack, SPECIAL_P)*0.01);
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
	// ���� ����� ������ 1 - ����� 100 ��������� �����
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
	string sBullet = LAi_GetCharacterBulletType(attack);
	if(sBullet == "powder_pellet") LaunchBlastPellet(enemy);
	if(sBullet == "grenade") LaunchBlastGrenade(enemy);
	if(CheckAttribute(enemy, "cirassId"))
	{
		min = stf(attack.chr_ai.DmgMin_C);
		max = stf(attack.chr_ai.DmgMax_C);
		
		if(stf(attack.chr_ai.EnergyP_C) > 0.0 )
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}	
	}
	else
	{
		min = stf(attack.chr_ai.DmgMin_NC);
		max = stf(attack.chr_ai.DmgMax_NC);
		
		if(stf(attack.chr_ai.EnergyP_NC) > 0.0)
		{
			if(sBullet == "powder_pellet")
			{
				if(enemy.chr_ai.group != LAI_GROUP_PLAYER) Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.EnergyP_C));
			}
		}	
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
	if(CheckCharacterPerk(attack, "Buccaneer"))  
	{
		if(CheckAttribute(enemy, "chr_ai.energy"))
		{
			enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.65); //fix
		}
	}
	return dmg;
}

//��������� ���������� ���� ��� ��������� �� ���������
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
	float ra = 1.0;
	float re = 1.0;
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
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
		if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.4;
		else charge_dlt = charge_dlt*1.25;
	}
	else
	{
		if(IsCharacterPerkOn(chr, "Gunman"))
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.25;
			else charge_dlt = charge_dlt*1.1;
		}
		else
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.15;
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
	if(IsCharacterPerkOn(enemy, "Fencer") && rand(9)==1)  {Log_Info("������� �����!"); return;}
	//���� �����������, �� ��������� ���
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	string fencing_type = LAi_GetBladeFencingType(attack);
	float coeff = 0.0;
	
	int valueCrB = sti(attack.chr_ai.special.valueCrB);
	
	/*switch (fencing_type) ������ ������ ������� ����� ��� ����� �������. ���� � ������ - Gregg
	{
		case "FencingLight": coeff = makefloat(attack.Skill.FencingLight)/20; break;
		case "Fencing": coeff = makefloat(attack.Skill.Fencing)/20; break;
		case "FencingHeavy": coeff = makefloat(attack.Skill.FencingHeavy)/20; break;
	}*/
	//--->�������� ������ - Gregg
	if (isBlocked && blockSave)
	{
		if (fencing_type == "FencingHeavy") blockSave = CheckForBlockBreak(attack,enemy,true);
		else blockSave = CheckForBlockBreak(attack,enemy,false);
	}
	//<---�������� ������ ������ �������
	//��������� �����������
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked, blockSave);
	float critical = 0.0;
	int critchance = 0;
	if (IsCharacterPerkOn(attack, "SwordplayProfessional")) critchance += 10;
	if (IsCharacterPerkOn(attack, "CriticalHit")) critchance += 5;
	if (IsCharacterPerkOn(attack, "Fencer")) critchance += 5;
	if (valueCrB != 0) critchance += valueCrB;//��� ����
	if(IsCharacterPerkOn(attack, "Agent") && attackType == "feint")
	{
		if (rand(99 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= critchance+33) critical = 1.0;
	}
	if (critchance > 0 && rand(99 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= critchance) critical = 1.0;
	/*if(IsCharacterPerkOn(attack, "SwordplayProfessional"))
	{
		if(IsCharacterPerkOn(attack, "Fencer"))
		{
			if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 20)
			{
				critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
			}
		}
		else
		{
			if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 15)
			{
				critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
			}
		}
	}
	else
	{
		if(IsCharacterPerkOn(attack, "CriticalHit"))
		{
			if(IsCharacterPerkOn(attack, "Fencer"))
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 10)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
			else
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 5)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
		}
		else
		{
			if(IsCharacterPerkOn(attack, "Fencer"))
			{
				if(rand(100 - GetCharacterSPECIALSimple(attack, SPECIAL_L)) <= 5)
				{
					critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.20;
				}
			}
		}
	}*/
	float kDmg = 1.0;
	if(IsCharacterPerkOn(attack, "Rush"))
	{
		kDmg = 2.0;
	}
	float kDmgRush = 1.0;
	if(IsCharacterPerkOn(enemy, "Rush"))
	{
		kDmgRush = 0.5;
	}
	dmg = dmg*kDmg*kDmgRush;
	//����� ����� ������
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))
	{
		if(attack.chr_ai.group == enemy.chr_ai.group)
		{
			return;
			//dmg = 0.0;
			//critical = 0.0;
			//noExp = true;
		}
	}
	bool cirign = false;
	if (!blockSave && !isBlocked && dmg > 0.0)
	{
		switch (fencing_type)
		{
			case "FencingLight":
				//--->���������� ������ ������ - Gregg
				CheckForBlooding(attack,enemy,true,attackType);
				CheckForSwift(attack,enemy,false);
				CheckForStun(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,false);
				//<---���������� ������ ������
			break;
			case "Fencing":
				//--->���������� �������� ������ - Gregg
				CheckForBlooding(attack,enemy,false,attackType);
				CheckForSwift(attack,enemy,true);
				CheckForStun(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,false);
				//<---���������� �������� ������ - Gregg
			break;
			case "FencingHeavy":
				//--->���������� ������� ������ - Gregg
				CheckForBlooding(attack,enemy,false,attackType);
				CheckForSwift(attack,enemy,false);
				CheckForStun(attack,enemy);
				CheckForTrauma(attack,enemy);
				cirign = CheckForCirassBreak(attack,enemy,true);
				//<--- ���������� ������� ������ - Gregg
			break;
		}
	}
	else
    {
        if(HasSubStr(attack.equip.blade, "katar") && rand(19)==0)//������� ������� ������ - Gregg
        {
            string weaponID = GetCharacterEquipByGroup(enemy, BLADE_ITEM_TYPE);
            aref weapon;
            Items_FindItem(weaponID, &weapon);
            if(weapon.model != "unarmed" && weapon.quality != "excellent") //�� �������� � �� ����������
            {
                if(GetCharacterItem(enemy, weaponID) <= 1) RemoveCharacterEquip(enemy, weapon.groupID);
                TakeItemFromCharacter(enemy, weaponID);
                string sEquipItem = GetGeneratedItem("unarmed");
                AddItems(enemy, sEquipItem, 1);
                EquipCharacterbyItem(enemy, sEquipItem);
                if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("������ ���������� ���� �������.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
				else
				{
					Log_Info("���� ������ ���� �������.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
            }
        }
        critical = 0;
    }
	
	if(CheckAttribute(enemy, "cirassId") && !cirign && critical > 0.0)// ������ �� ������ � �����
	{
		string cirasstype = enemy.cirassId;
		switch (Items[sti(cirasstype)].id)
		{
			case "suit_1": break;
			case "suit_2": break;
			case "suit_3": break;
			case "cirass1": if (rand(9)<4) critical = 0.0; break;
			case "cirass2": if (rand(9)<6) critical = 0.0; break;
			case "cirass3": if (rand(1)==0) critical = 0.0; break;
			case "cirass4": if (rand(4)>0) critical = 0.0; break;
			case "cirass5": critical = 0.0; break;
		}
		if (critical == 0.0)
		{
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("����������� ���� ��� ������������!");
			}
			else
			{
				Log_TestInfo(""+enemy.Name+" ������������ ����!");
			}
		}
	}
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		critical += GetCharacterSPECIALSimple(attack, SPECIAL_L)*0.05;//�������� ���� ����� �� �����
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
			Log_TestInfo(" " + critical + " �����");
			
			pchar.questTemp.criticalcount = sti(pchar.questTemp.criticalcount) + 1;
			
			// ��������� ����������
			if(sti(pchar.questTemp.criticalcount) >= 100) UnlockAchievement("criticals", 1);
			if(sti(pchar.questTemp.criticalcount) >= 250) UnlockAchievement("criticals", 2);
			if(sti(pchar.questTemp.criticalcount) >= 500) UnlockAchievement("criticals", 3);
		}
	}
	kDmg = 1.0;
	if(IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	if(IsCharacterPerkOn(enemy, "AdvancedDefense")) kDmg = 0.8;
	if(IsCharacterPerkOn(enemy, "SwordplayProfessional")) kDmg = 0.7;
	if(IsEquipCharacterByArtefact(enemy, "talisman9") && CheckAttribute(attack,"sex") && attack.sex == "skeleton") kDmg -= 0.33;

	// ��� 1.2.3
	dmg = dmg*kDmg;
	if (dmg < 1) return;
	dmg = dmg *(1 + critical);//dmg + critical;
	if(CheckAttribute(enemy, "cirassId") && !cirign)//������������� ������ � �����
	{
		if (CheckAttribute(Items[sti(enemy.cirassId)],"CirassLevel.fast"))
		{
			switch (attackType)
			{
				case "fast": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.fast)); break;
				case "force": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.force)); break;
				case "round": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.round)); break;
				case "break": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.break)); break;
				case "feint": dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel.feint)); break;
			}
		}
	}
	//������� �����������
	if (IsEquipCharacterByArtefact(attack, "talisman1")) dmg *= 1.1; //�������� ����
	if(IsCharacterPerkOn(attack, "Grunt")) dmg *= 1.15; //������
	if(CheckAttribute(attack, "StrangeElixir")) dmg *= 1.1; //������� �����
	if(IsEquipCharacterByArtefact(attack, "talisman9") && CheckAttribute(enemy,"sex") && enemy.sex == "skeleton") dmg *= 1.33;
	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
	/*if(!IsCharacterPerkOn(attack, "Grunt"))
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10) + 0.5));//�������� ����
		else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
	}
	else
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10)+(dmg*0.15) + 0.5));//�������� ����
		else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg*0.15) + 0.5));
	}*/
	//�������� �� ������
	LAi_CheckKillCharacter(enemy);
	//�������� �� ����������
	MakePoisonAttackCheckSex(enemy, attack);
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
	if(LAi_IsDead(enemy) && isSetBalde)
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
		if (stf(enemy.rank) < 4) int experience = GetCharacterSPECIALSimple(attack, SPECIAL_I) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_A));
		else experience = Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_I) * re / ra;;//Lipsar �����e��� �����
		AddCharacterExpToSkill(attack, fencing_type, experience);		 
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
        AddCharacterExpToSkill(attack, fencing_type, Makefloat(exp*0.2));
    }
	
}

void CheckForBlooding(ref attack, ref enemy, bool type, string attackType)
{
	int valueB = sti(attack.chr_ai.special.valueB);
	if (type)
	{
		/*if (HasSubStr(attack.equip.blade, "blade32") && 12.5+valueB+coeff>rand(99))//��������
		{
			if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator")
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�� ������� ������������.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
					pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("��� ������� ������������ ����.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				MakeBloodingAttack(enemy, attack, coeff);
			}
		}
		if (!HasSubStr(attack.equip.blade, "blade32") && attackType == "force")//�����*/
		if (attackType == "force")//�����
		{
			float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingLight"))/20;
			if ((2.5+valueB+coeff)*10>rand(999))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� ������������.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						if(IsEquipCharacterByArtefact(enemy, "talisman9") && rand(9)>0) {log_info("������������ �������������.") return;}
						Log_Info("��� ������� ������������ ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					MakeBloodingAttack(enemy, attack, coeff);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("��� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(coeff*2)));
				}
			}
		}
	}
	else
	{
		if (valueB != 0)
		{
			if (valueB>rand(99))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� ������������.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						if(IsEquipCharacterByArtefact(enemy, "talisman9") && rand(9)>0) {log_info("������������ �������������.") return;}
						Log_Info("��� ������� ������������ ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					MakeBloodingAttack(enemy, attack, 3.0);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.bloodingcount = sti(pchar.questTemp.bloodingcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("��� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(valueB*2)));
				}
			}
		}
	}
}

void CheckForSwift(ref attack, ref enemy, bool type)
{
	int valueSS = sti(attack.chr_ai.special.valueSS);
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"Fencing"))/20;
		if ((2.5+valueSS+coeff)*10>rand(999))
		{
			if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�� ������� ������ ����.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
					pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("��� ��� ������ ������ ����.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
				}
				MakeSwiftAttack(enemy, attack, coeff);
			}
			else
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�� ������� �������� ����.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
					pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("��� ������� �������� ����.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(coeff*4)));
			}
		}
	}
	else
	{
		if (valueSS != 0)
		{
			if (valueSS>rand(99))
			{
				if(CheckAttribute(enemy, "sex") && enemy.model.animation != "Terminator" && enemy.sex != "skeleton")
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� ������ ����.");
						PlaySound("interface\Stan_"+rand(5)+".wav");
						pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("��� ������ ������ ����.");
						PlaySound("interface\Stan_"+rand(5)+".wav");
					}
					MakeSwiftAttack(enemy, attack, 3.0);
				}
				else
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
						pchar.questTemp.swiftcount = sti(pchar.questTemp.swiftcount) + 1;
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("��� ������� �������� ����.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					LAi_ApplyCharacterAdditionalDamage(enemy, MakeInt(5+(valueSS*2)));
				}
			}
		}
	}
}

void CheckForStun(ref attack, ref enemy)
{
	int valueStS = sti(attack.chr_ai.special.valueStS);
	if (valueStS != 0)
	{
		if (rand(99)<valueStS)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("���� ������� ����������.");
				PlaySound("interface\Stan_"+rand(5)+".wav");
				pchar.questTemp.stuncount = sti(pchar.questTemp.stuncount) + 1;
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("��� ��������!");
				PlaySound("interface\Stan_"+rand(5)+".wav");
			}
			MushketStun(enemy);
		}
	}
}

void CheckForTrauma(ref attack, ref enemy)
{
	int valueT = sti(attack.chr_ai.special.valueT);
	if (valueT != 0)
	{
		if (rand(99)<valueT)
		{
			if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_") && rand(6)<1) return;
			
			if (!CheckAttribute(enemy,"chr_ai.TraumaQ")) enemy.chr_ai.TraumaQ = 1;
			else enemy.chr_ai.TraumaQ = sti(enemy.chr_ai.TraumaQ)+1;
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("�� ������������ ����������.");
				PlaySound("interface\HrustBones_"+rand(2)+".wav");
				pchar.questTemp.traumacount = sti(pchar.questTemp.traumacount) + 1;
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("�� �������� ������.");
				PlaySound("interface\HrustBones_"+rand(2)+".wav");
				if (CheckAttribute(enemy,"chr_ai.TraumaQ") && sti(enemy.chr_ai.TraumaQ)>2)
				{
					Log_Info("�� �������� ������� ������");
					enemy.chr_ai.HeavyTrauma = 2;
					SetNoRun(enemy);
				}
			}
			MakeTraumaAttack(enemy, attack);
		}
	}
}

bool CheckForBlockBreak(ref attack, ref enemy, bool type)
{
	bool blockSave = true;
	int valueBB = sti(attack.chr_ai.special.valueBB);
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingHeavy"))/20;
		if (HasSubStr(attack.equip.blade, "topor") && rand(99)<8.0+(coeff*2.0)+valueBB) //15+%
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("�������� �����.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("��� ���� ������.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			blockSave = false;
		}
		if (!HasSubStr(attack.equip.blade, "topor") && rand(99)<5.0+(coeff*2.0)+valueBB) //10+%
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("�������� �����.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("��� ���� ������.");
				PlaySound("interface\Block_"+rand(1)+".wav");
			}
			blockSave = false;
		}
	}
	else
	{
		if (valueBB != 0)
		{
			if (rand(99)<valueBB)
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�������� �����.");
					PlaySound("interface\Block_"+rand(1)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("��� ���� ������.");
					PlaySound("interface\Block_"+rand(1)+".wav");
				}
				blockSave = false
			}
		}
	}
	return blockSave;
}

bool CheckForCirassBreak(ref attack, ref enemy, bool type)
{
	int valueCB = sti(attack.chr_ai.special.valueCB);
	bool cirign = false;
	if (type)
	{
		float coeff = makefloat(GetCharacterSkillSimple(attack,"FencingHeavy"))/20;
		if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
		{
			if (HasSubStr(attack.equip.blade, "topor") && rand(99)<8.0+valueCB+(coeff*2.0)) //15%
			{
				cirign = true;
				// Log_TestInfo("�����");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�� ������� ������.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("���� ������ ���� �������.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
			if (!HasSubStr(attack.equip.blade, "topor") && rand(99)<5.0+valueCB+(coeff*2.0)) //10%
			{
				cirign = true;
				// Log_TestInfo("���");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("�� ������� ������.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("���� ������ ���� �������.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
		}
	}
	else
	{
		if (valueCB != 0)
		{
			if (CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
			{
				if (rand(99)<valueCB)
				{
					cirign = true;
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("�� ������� ������.");
						PlaySound("interface\Breaking_"+rand(5)+".wav");
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("���� ������ ���� �������.");
						PlaySound("interface\Breaking_"+rand(5)+".wav");
					}
				}
			}
		}
	}
	return cirign;
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
	if(rand(10000) > p*10000)
	{
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			string missed = "";
			switch (rand(4))
			{
				case 0: missed = "������!"; break;
				case 1: missed = "������!"; break;
				case 2: missed = "������ �����!"; break;
				case 3: missed = "�� ��������� ���!"; break;
				case 4: missed = "�� �����!"; break;
			}
			Log_Info(missed);
		}
		return;
	}
	if(CheckCharacterPerk(enemy, "AgileMan"))  
	{
		if (rand(3)==0)
		{
			Log_Info("��������� �� ��������!")
			return;
		}		
	}
	// boal ���� �������� ������, � �� ���� � ����� 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId")&& !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))
	{
        if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500) 
		{	
			if(sti(enemy.index) == GetMainCharacterIndex()) Log_Info("���� ������ ������������� ���� �� ��������.");
			return;
		}
	}
	
	
	// boal 23.05.2004 <--
	//��������� �����������
	float damage = LAi_GunCalcDamage(attack, enemy);
	if (attack.chr_ai.sgun == "pistol_grapebok") damage *= 2;

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
	if (HasSubStr(attack.equip.gun, "mushket")) //��������� ��������� - Gregg
	{
		if (damage > 0 && rand(1)==0)
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("������� �� ������� ������� ����������.");
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("��� �������� ��������� �� �������.");
				//PlaySound("interface\Breaking_"+rand(5)+".wav");
			}
			MushketStun(enemy);
		}
	}
	if(CheckAttribute(enemy, "cirassId") && !HasSubStr(Items[sti(enemy.cirassId)].id, "suit_"))//�� ��������� �������
	{
		damage = damage * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
		if(sti(enemy.index) == GetMainCharacterIndex())
		{
			Log_Info("���� �� �������� ��� ������ �������");
		}
	}
	if(damage > 0.0)
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))
		{
			if (rand(4)==0)	{LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)*2); Log_Info("����������� �������");}
			else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)+25);
		}
		else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5));
		
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
	if(LAi_IsDead(enemy) && isSetBalde)
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
		if (stf(enemy.rank) < 4) int experience = GetCharacterSPECIALSimple(attack, SPECIAL_P) + rand(GetCharacterSPECIALSimple(attack, SPECIAL_I));
		else experience = Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_P) * re / ra;//Lipsar �����e��� �����
		AddCharacterExpToSkill(attack, SKILL_PISTOL, experience);		 
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
        AddCharacterExpToSkill(attack, SKILL_PISTOL, MakeFloat(exp*0.2));
    }
}

void SetBack()
{
	
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
	if (LAi_GetBladeEnergyType(chr) == "Fencing")
	{
		npc_return_tmp = npc_return_tmp * 10 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//��� ������ ����� "force", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightForce", "LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 10 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//��� ������ ����� "round", 0 - ������� �� ��������, ���� ������ <3 �� ���� �� ����������
#event_handler("NPC_Event_GetAttackWeightRound", "LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	//npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	//Boyer mod #20170318-33 Fight/difficulty level rebalancing
	if (LAi_GetBladeEnergyType(chr) == "FencingLight")
	{
		npc_return_tmp = npc_return_tmp * 2 * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * (0.8 + (0.05 * MOD_SKILL_ENEMY_RATE + 0.05));
	}
	return npc_return_tmp;
}

//��� ������ ����� "break", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightBreak", "LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	if (LAi_GetBladeEnergyType(chr) == "FencingHeavy")
	{
		npc_return_tmp = npc_return_tmp * 6 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		npc_return_tmp = npc_return_tmp * 0.5 * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	}
	return npc_return_tmp;
}

//��� ������ ����� "feint", 0 - ������� �� ��������
#event_handler("NPC_Event_GetAttackWeightFeint", "LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//���������� ������
//����������� ������� ��������� - ����� � ����� ������������ �������� 2 ���� � �������
#event_handler("NPC_Event_GetDefenceActive", "LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")

	{
		npc_return_tmp = 1 + level * 0.35;
		return npc_return_tmp;
	}
	else
	{
		npc_return_tmp = 0.35 + level * 0.35;
		return npc_return_tmp;
	}
}

// boal 20.01.08 ������� - �������, ��� ������ ��� ����, ����� ��� � ��� � �������������. ��� ��� ���������� � 0-1 �� ���� ����� �����, �� ���� ���������� ��������� �� ��������� ��� ����� ������������ ����� �� ������ �������, � �� ��������� ����
// ������ ���� ������ - ��� ����� � ������ (���� + ����)
//��� ������ �����, 0 - ������� �� ��������
#event_handler("NPC_Event_GetDefenceWeightBlock", "LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	if (LAi_GetBladeFencingType(pchar) == "FencingHeavy")
	{
		npc_return_tmp = 8.0;
	}
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));
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
