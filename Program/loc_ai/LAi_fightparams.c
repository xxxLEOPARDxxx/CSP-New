/*

	Возможные типы атаки attackType:
	"fast" быстрая атака
	"force" обычная
	"round" круговая
	"break" пробивающая блок
	"feint" атака после финта


*/

//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//Расчитать повреждение для персонажа
//#20200522-01
float LAi_CalcDamageForBlade(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	//Расчитываем повреждение от сабли
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
	//Коэфициент в зависимости от скилов
	float aSkill = LAi_GetCharacterFightLevel(attack);
	float eSkill = LAi_GetCharacterFightLevel(enemy);
	//float kSkillDmg = 1.0;
	//kSkillDmg = 1.0 * (1.0 + (0.3 * aSkill));
    if (aSkill < eSkill)
	{
		bladeDmg = bladeDmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	
	// Warship 27.08.09 Для сильных противников
	// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
	if(sti(enemy.Rank) > 50)
	{
		bladeDmg = bladeDmg * 45 / sti(enemy.Rank);
	}
	
	if(CheckAttribute(loadedLocation, "CabinType") && sti(enemy.index) == GetMainCharacterIndex())
	{
		bladeDmg = bladeDmg * (1.0 + stf(attack.rank)/100);
	}
	//Коэфициент в зависимости от удара
	float kAttackDmg = 1.0;
	
	// TO_DO оптимизация на ветку параметров
	//if (sti(attack.index) == GetMainCharacterIndex()) Log_Info(attackType);
	switch(attackType)
	{
		case "fast":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				kAttackDmg = 0.7;
			}
			break;
		case "force":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				kAttackDmg = 1.0;
			}
			break;
		case "round":
			if(isBlocked && blockSave)
			{
				kAttackDmg = 0.0;
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
		case "break":
			if(isBlocked)
			{
				//#20200510-03
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
		
		case "feintc":  // фикс после изучения ядра //Атакующие продолжение финта
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
	if (kAttackDmg > 0)  // оптимизация boal
	{
		if (attack.model.animation == "mushketer")
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
		//Результирующий демедж
		float dmg = bladeDmg * kAttackDmg; // *kArcadeDmg * kSkillDmg
		if(CheckCharacterPerk(attack, "HardHitter"))  
		{
			if(CheckAttribute(enemy, "chr_ai.energy"))
			{
				enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.9); //fix
			}
		}
		// упрощение игры новичкам 
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

//Расчитать полученный опыт при ударе саблей
//#20200522-01
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, float dmg, bool isBlocked, bool blockSave)
{
	if (blockSave) return 0.0;
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	float currhp = stf(enemy.chr_ai.hp);
	float exp = currhp/Lai_GetCharacterMaxHP(enemy)*GetCharacterSPECIALSimple(attack, SPECIAL_I);//Lipsar передeлка опыта
	if (CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if (CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if (ra < 1.0)
		ra = 1.0;
	if (re < 1.0)
		re = 1.0;
	exp = exp * ((1.0 + re * 0.5) / (1.0 + ra * 0.5));

	switch (attackType)
	{
	case "break":
		if (isBlocked)
		{
			//#20200510-03
			if (blockSave)
			{
				exp = exp * 0.85;
			}
			else
			{
				exp = exp * 1.1;
			}
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

//Энергия, необходимая для запуска действия
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
		case "hit_parry":  // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
			energy = 20.0;
		break;
		case "feintc":
			energy = 7.0; // расход при успехе финта
		break;
	}
	/*if(CheckCharacterPerk(character, "BladeDancer"))  // to_do
	{
		energy = energy * 0.9;
	}*/
	 // честно все всем
	/*if(character.id == pchar.id || character.chr_ai.group == LAI_GROUP_PLAYER)
	{
		energy = energy * (1.05 - (0.025 * MOD_SKILL_ENEMY_RATE));
	} */
	if (energy > 0.0)  // оптимизация
	{
		float fSkill = LAi_GetCharacterFightLevel(character);  // stf(character.skill.fencing) - не так это далеют!!
		fSkill = (1.0 - (0.3 * fSkill));
		energy = energy * fSkill * LAi_GetBladeEnergyType(character);  // энергоемкость от веса
	}
	return energy;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float fMultiplier = 1.6666667;

	if(CheckCharacterPerk(chr, "Energaiser")) // скрытый перк боссов и ГГ
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless")) 
	{
		fMultiplier = fMultiplier * 1.15;
	}
    // честно все всем
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

//Расчитаем вероятность попадания
float LAi_GunCalcProbability(aref attack, float kDist)
{
	//Если близко, то попадём точно
	if(kDist >= 0.9) return 1.0;
	//Расчитаем вероятность на конце отрезка
	float pmin = 0.3;
 	if(CheckAttribute(attack, "chr_ai.accuracy")) // boal это меткость самого пистолета, а не скил!
	{
		pmin = stf(attack.chr_ai.accuracy);
	}
 	//Применим разброс от скила
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//Вероятность попадания в текущей позиции
	float p = pmin + (1.0 - pmin)*(kDist/0.9)+(GetCharacterSPECIALSimple(attack, SPECIAL_P)*0.01);
 	//Учесть абилити
	if(IsCharacterPerkOn(attack, "GunProfessional"))
	{
		p = p + 0.25;
	}else{
		if(IsCharacterPerkOn(attack, "Gunman"))
		{
			p = p + 0.1;
		}
	}
	// путь будет больше 1 - тогда 100 процентов попал
	return p;
}

//Получить повреждение от пистолета
float LAi_GunCalcDamage(aref attack, aref enemy)
{
	//Расчитываем повреждение
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
	//Учитываем скилы
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck
	
	float dmg = min + (max - min)*frandSmall(aSkill);
	//Модифицировать повреждение от pistol с учетом скилов
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	// упрощение игры новичкам 
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

//Расчитать полученный опыт при попадании из пистолета
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
	if (dmg == 0) return 0.0;
	float currhp = stf(enemy.chr_ai.hp);
	if (dmg > Lai_GetCharacterMaxHP(enemy)) currhp = Lai_GetCharacterMaxHP(enemy);
	int bonus = 1;
	if (rand(GetCharacterSPECIALSimple(attack, SPECIAL_I)) > 7) bonus = GetCharacterSPECIALSimple(attack, SPECIAL_I);
	float exp = currhp/Lai_GetCharacterMaxHP(enemy) * GetCharacterSPECIALSimple(attack, SPECIAL_P) *  bonus +(1+rand(GetCharacterSPECIALSimple(attack, SPECIAL_L)-1) * currhp/Lai_GetCharacterMaxHP(enemy));//Lipsar передeлка опыта
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank"))//Lipsar переделка опыта
	{
		ra = stf(attack.rank);
	}
	if (CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if (ra < 1.0)
		ra = 1.0;
	if (re < 1.0)
		re = 1.0;
	exp = exp * ((1.0 + re * 0.5) / (1.0 + ra * 0.5));
	return exp;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(aref chr)
{
	//Получим текущее состояние скорости зарядки
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai.charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.charge_dlt);
	}
	//Модифицируем скилом
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//УчтЈм абилити
	if(IsCharacterPerkOn(chr, "GunProfessional"))
	{
		if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.4;
		else charge_dlt = charge_dlt*1.25;
	}else{
		if(IsCharacterPerkOn(chr, "Gunman"))
		{
			if(IsCharacterPerkOn(chr, "Buccaneer")) charge_dlt = charge_dlt*1.25;
			else charge_dlt = charge_dlt*1.1;
		}
	}
	return charge_dlt;
}

//--------------------------------------------------------------------------------
//All
//--------------------------------------------------------------------------------

/*float LAi_CalcDeadExp(aref attack, aref enemy)
{
	//Вычисляем полученый опыт
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

//Начисление повреждений при атаке мечём
//#20200522-01
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string attackType, bool isBlocked, bool blockSave)
{
	if(IsCharacterPerkOn(enemy, "Fencer") && rand(9)==1)  {Log_Info("Избежал удара!"); return;}
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	string fencing_type = LAi_GetBladeFencingType(attack);
	float coeff = 0.0;
	/*switch (fencing_type) старый расчёт чистого стата без учёта бонусов. Ниже с учётом - Gregg
	{
		case "FencingLight": coeff = makefloat(attack.Skill.FencingLight)/20; break;
		case "Fencing": coeff = makefloat(attack.Skill.Fencing)/20; break;
		case "FencingHeavy": coeff = makefloat(attack.Skill.FencingHeavy)/20; break;
	}*/
	switch (fencing_type)
	{
		case "FencingLight": coeff = makefloat(GetCharacterSkillSimple(attack,"FencingLight"))/20; break;
		case "Fencing": coeff = makefloat(GetCharacterSkillSimple(attack,"Fencing"))/20; break;
		case "FencingHeavy": coeff = makefloat(GetCharacterSkillSimple(attack,"FencingHeavy"))/20; break;
	}
		//--->Пробитие блоков тяжёлым оружием - Gregg
	if (isBlocked && blockSave)
	{
		if (coeff != 0.0)
		{
			if (fencing_type == "FencingHeavy")
			{
				if (coeff*7>rand(99))
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Пробитие блока.");
						PlaySound("interface\Block_"+rand(1)+".wav");
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Ваш блок пробит.");
						PlaySound("interface\Block_"+rand(1)+".wav");
					}
					isBlocked = false;
					blockSave = false;
				} 
			}
		}
	}
	//<---Пробитие блоков тяжёлым оружием
	//Вычисляем повреждение
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked, blockSave);
	float critical = 0.0;
	if(IsCharacterPerkOn(attack, "SwordplayProfessional"))
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
	}else{
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
	}
	if(IsCharacterPerkOn(attack, "Agent") && attackType == "feint")
	{
		if (rand(2)==0) critical = 1.0;
	}
	float kDmg = 1.0;
	bool rushmiss = false;
	if(IsCharacterPerkOn(attack, "Rush"))
	{
		kDmg = 3.0;
		bool heavyw = false;
		if (fencing_type == "FencingHeavy") heavyw = true;//тяжёлое ли оружие
		if (heavyw)
		{
			if (35+25-(coeff*5)-GetCharacterSPECIALSimple(attack, SPECIAL_L)>rand(99) && attackType != "break")//шанс промаха
			{
				Log_SetStringToLog("Вы промахнулись!");
				return;
			}
			if (attackType == "break" && 35+50-(coeff*5)-GetCharacterSPECIALSimple(attack, SPECIAL_L)>rand(99))
			{
				Log_SetStringToLog("Вы промахнулись!");
				return;
			}
		}
		if (!heavyw && 35-GetCharacterSPECIALSimple(attack, SPECIAL_L)>rand(99))
		{
			Log_SetStringToLog("Вы промахнулись!");
			return;
		}
		rushmiss = true;
	}
	float kDmgRush = 1.0;
	if(IsCharacterPerkOn(enemy, "Rush"))
	{
		kDmgRush = 0.5;
	}
	dmg = dmg*kDmg*kDmgRush;
	//Аттака своей группы
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
	//--->Функционал лёгкого оружия - Gregg
	if (coeff != 0.0)
	{
		if (fencing_type == "FencingLight" && !blockSave && attackType == "force")//выпад
		{
			if (HasSubStr(attack.equip.blade, "blade32") && rand(9)==0)//фламберж
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы вызвали кровотечение.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Вам нанесли кровоточащую рану.");
					PlaySound("interface\Krovotok_"+rand(4)+".wav");
				}
				if(CheckAttribute(enemy, "model.animation") && CheckAttribute(enemy, "sex") && enemy.model.animation != "skeleton" && enemy.model.animation != "Terminator" && enemy.sex != "skeleton") MakeBloodingAttack(enemy, attack, coeff);
			}
			else//прочее
			{
				if (coeff*10>rand(999))
				{
					if(sti(attack.index) == GetMainCharacterIndex())
					{
						Log_Info("Вы вызвали кровотечение.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					if(sti(enemy.index) == GetMainCharacterIndex())
					{
						Log_Info("Вам нанесли кровоточащую рану.");
						PlaySound("interface\Krovotok_"+rand(4)+".wav");
					}
					if(CheckAttribute(enemy, "model.animation") && CheckAttribute(enemy, "sex") && enemy.model.animation != "skeleton" && enemy.model.animation != "Terminator" && enemy.sex != "skeleton") MakeBloodingAttack(enemy, attack, coeff);
				}
			}
			
		}

	}
	//<---Функционал лёгкого оружия
	
	//--->Функционал среднего оружия - Gregg
	if (fencing_type == "Fencing" && !blockSave)
	{
		if (coeff != 0.0)
		{
			if (coeff*10>rand(999))
			{
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Вы нанесли резкий удар.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Вам был нанесён резкий удар.");
					PlaySound("interface\Stan_"+rand(5)+".wav");
				}
				if(CheckAttribute(enemy, "model.animation") && CheckAttribute(enemy, "sex") && enemy.model.animation != "skeleton" && enemy.model.animation != "Terminator" && enemy.sex != "skeleton") MakeSwiftAttack(enemy, attack, coeff);
			}
		}
	}
	//<---Функционал среднего оружия - Gregg
	
	if (blockSave)
    {
        if(HasSubStr(attack.equip.blade, "katar") && rand(19)==0)//Поломка катаром оружий - Gregg
        {
            string weaponID = GetCharacterEquipByGroup(enemy, BLADE_ITEM_TYPE);
            aref weapon;
            Items_FindItem(weaponID, &weapon);
            if(weapon.model != "unarmed" && weapon.quality != "excellent") //Не отличное и не безоружный
            {
                if(GetCharacterItem(enemy, weaponID) <= 1) RemoveCharacterEquip(enemy, weapon.groupID);
                TakeItemFromCharacter(enemy, weaponID);
                string sEquipItem = GetGeneratedItem("unarmed");
                AddItems(enemy, sEquipItem, 1);
                EquipCharacterbyItem(enemy, sEquipItem);
                if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Оружие противника было сломано.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
				else
				{
					Log_Info("Ваше оружие было сломано.");
					PlaySound("interface\Crash_"+rand(2)+".wav");
				}
            }
        }
        critical = 0;
    }
	
	//--->Функционал тяжёлого оружия - Gregg
	bool heavy = false;
	if (fencing_type == "FencingHeavy") heavy = true;//тяжёлое ли оружие
	if (heavy && 75+(coeff*5)<rand(100) && !rushmiss && attackType != "break")//шанс промаха не пробивающим
	{
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_Info("Вы промахнулись!");
		}
		if(sti(enemy.index) == GetMainCharacterIndex())
		{
			Log_Info(""+attack.Name+" промахнулся.");
		}
		return;
	}
	if (heavy)
	{
		if (attackType == "break" && 50+(coeff*5)<rand(100) && !rushmiss)//шанс промаха пробивающим
		{
			if(sti(attack.index) == GetMainCharacterIndex())
			{
				Log_Info("Вы промахнулись!");
			}
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info(""+attack.Name+" промахнулся.");
			}
			return;
		}			
		if (attackType == "break")//модификация урона пробивающего
		{
			if (CheckAttribute(enemy, "cirassId"))
			{
				dmg *= 2.5;
			}
			else
			{
				dmg *= 5;
			}
		}
		if (attackType != "break")//модификация урона не пробивающего
		{
			if (!CheckAttribute(enemy, "cirassId"))
			{
				dmg *= 2;
			}
		}
	}
	bool cirign = false;
	if (coeff != 0)
	{
		if (CheckAttribute(enemy, "cirassId"))
		{
			if (HasSubStr(attack.equip.blade, "topor") && rand(6-coeff)==0 && !blockSave)
			{
				cirign = true;
				// Log_TestInfo("топор");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Ваша атака игнорирует сопротивления кирасы противника.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Нанесённая по вам атака игнорирует сопротивления кирасы.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
			if (!HasSubStr(attack.equip.blade, "topor") && fencing_type == "FencingHeavy" && coeff*7>rand(100) && !blockSave)
			{
				cirign = true;
				// Log_TestInfo("тяж");
				if(sti(attack.index) == GetMainCharacterIndex())
				{
					Log_Info("Ваша атака игнорирует сопротивления кирасы противника.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
				if(sti(enemy.index) == GetMainCharacterIndex())
				{
					Log_Info("Нанесённая по вам атака игнорирует сопротивления кирасы.");
					PlaySound("interface\Breaking_"+rand(5)+".wav");
				}
			}
		}
	}
	//<--- Функционал тяжёлого оружия - Gregg
	
	if(CheckAttribute(enemy, "cirassId") && !cirign && critical > 0.0)// защиты от критов у кирас
	{
		string cirassId = enemy.cirassId;
		if (Items[sti(enemy.cirassId)].id == "cirass1" && rand(9)<4) critical = 0.0;
		if (Items[sti(enemy.cirassId)].id == "cirass2" && rand(9)<6) critical = 0.0;
		if (Items[sti(enemy.cirassId)].id == "cirass3" && rand(1)==0) critical = 0.0;
		if (Items[sti(enemy.cirassId)].id == "cirass4" && rand(4)>0) critical = 0.0;
		if (Items[sti(enemy.cirassId)].id == "cirass5") critical = 0.0;
		if (critical == 0.0)
		{
			if(sti(enemy.index) == GetMainCharacterIndex())
			{
				Log_Info("Критический удар был предотвращен!");
			}
			else
			{
				Log_TestInfo(""+enemy.Name+" заблокировал крит!");
			}
		}
	}
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		critical += GetCharacterSPECIALSimple(attack, SPECIAL_L)*0.05;//бонусный урон крита от удачи
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
			Log_TestInfo(" " + critical + " хитов");
		}
	}
	kDmg = 1.0;
	if(IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	if(IsCharacterPerkOn(enemy, "AdvancedDefense")) kDmg = 0.8;
	if(IsCharacterPerkOn(enemy, "SwordplayProfessional")) kDmg = 0.7;

	// ГПК 1.2.3
	dmg = dmg*kDmg;
	dmg = dmg *(1 + critical);//dmg + critical;
	if(CheckAttribute(enemy, "cirassId") && !cirign)//сопротивления уронам у кирас
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
	if(dmg > 0.0)
	{
		//Наносим повреждение
		if(!IsCharacterPerkOn(attack, "Grunt"))
		{
			if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10) + 0.5));//Пернатый Змей
			else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
		}
		else
		{
			if(IsEquipCharacterByArtefact(attack, "talisman1"))	LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg/10)+(dmg*0.15) + 0.5));//Пернатый Змей
			else  LAi_ApplyCharacterDamage(enemy, MakeInt(dmg+(dmg*0.15) + 0.5));
		}
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
		//проверим на отравление
		MakePoisonAttackCheckSex(enemy, attack);
	}
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//Начисляем опыта
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
		//Начислим за убийство
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
		else experience = MakeInt(Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_I));//Lipsar передeлка опыта
		AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), experience);		 
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
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
	}
}
// boal <--

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist)
{
	Lai_CharacterChangeEnergy(attack, -4); // жрем энергию за выстрел boal 20/06/06
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Вероятность поподания
	float p = LAi_GunCalcProbability(attack, kDist);
	//Если промахнулись, то выйдем
	if(rand(10000) > p*10000)
	{
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			string missed = "";
			switch (rand(4))
			{
				case 0: missed = "Промах!"; break;
				case 1: missed = "Мазила!"; break;
				case 2: missed = "Целься лучше!"; break;
				case 3: missed = "Да прицелься уже!"; break;
				case 4: missed = "Не попал!"; break;
			}
			Log_Info(missed);
		}
		return;
	}
	if(CheckCharacterPerk(enemy, "AgileMan"))  
	{
		if (rand(3)==0)
		{
			Log_Info("Уклонился от выстрела!")
			return;
		}		
	}
	// boal брон работает всегда, а не токо в блоке 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId"))
	{
        if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500) return;
	}
	// boal 23.05.2004 <--
	//Начисляем повреждение
	float damage = LAi_GunCalcDamage(attack, enemy);

	//Аттака своей группы
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
	if(CheckAttribute(enemy, "cirassId") && Items[sti(enemy.cirassId)].id != "suit_1" && Items[sti(enemy.cirassId)].id != "suit_2" && Items[sti(enemy.cirassId)].id != "suit_3")//не учитываем костюмы
	{
		damage = damage * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
		if(sti(enemy.index) == GetMainCharacterIndex())
		{
			Log_Info("Урон от выстрела был снижен кирасой");
		}
	}
	if(damage > 0.0)
	{
		if(IsEquipCharacterByArtefact(attack, "talisman1"))
		{
			if (rand(5)==0)	{LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)*2); Log_Info("Критический выстрел");}
			else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5)+25);
		}
		else LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5));	
		
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade"));//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//Начисляем опыт
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
		//Начислим за убийство
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
		else experience = MakeInt(Lai_GetCharacterMaxHP(enemy)/stf(enemy.rank) + GetCharacterSPECIALSimple(attack, SPECIAL_P));//Lipsar передeлка опыта
		AddCharacterExpToSkill(attack, SKILL_PISTOL, experience);		 
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal skill <--
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--
        
        //Начислим за убийство
		/*exp = exp + */
        //LAi_CalcDeadExp(attack, enemy); // начисляем только за удар и смерть
  		LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(!isSetBalde)
	{
		//LAi_ChangeReputation(attack, -1);
		exp = 0.0;
	}
	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, MakeFloat(exp*0.5));
    }
}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
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

//Вес выбора удара "force", 0 - никогда не выбирать
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

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то удар не выбирается
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

//Вес выбора удара "break", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightBreak","LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint","LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду
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

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock","LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));   // boal
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//Параметры стрельбы
//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
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

//Разрешён ли выстрел
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

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
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
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg));
	//Проверим на смерть
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

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}
