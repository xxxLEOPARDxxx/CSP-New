// ���� �� ������� �������, ��������� ��� ��� 29.07.06
void UpdateCrewExp()
{	
	int cn;
	ref chr;
	for (int i = 0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			chr = &characters[cn];
			if (bSeaActive || IsEntity(worldMap))  // ���� ��� �����
			{
				ChangeCrewExp(chr, "Sailors", 1);
			}
			else
			{
				ChangeCrewExp(chr, "Sailors", -1);
				ChangeCrewExp(chr, "Cannoners", -1);
				ChangeCrewExp(chr, "Soldiers", -1);
			}
		}
	}
	
}
string GetExpName(int iExp)
{
	string sExp = "Exp 1";

	if(iExp >= 12)
	{
		sExp = "Exp 2";
	}
	if(iExp >= 24)
	{
		sExp = "Exp 3";
	}
	if(iExp >= 35)
	{
		sExp = "Exp 4";
	}
	if(iExp >= 46)
	{
		sExp = "Exp 5";
	}
	if(iExp >= 57)
	{
		sExp = "Exp 6";
	}
	if(iExp >= 68)
	{
		sExp = "Exp 7";
	}
	if(iExp >= 80)
	{
		sExp = "Exp 8";
	}
	if(iExp >= 90)
	{
		sExp = "Exp 9";
	}
	/*if(iExp >= 90)
	{
		sExp = "Exp 10";
	} */

	return sExp;
}

// boal ����� ���� �� 16.01.04 -->
int GetMoneyForOfficer(ref Npchar)
{
    if (CheckAttribute(Npchar, "Payment") && makeint(Npchar.Payment) == true)
    {
	    int i, sum;
	    sum = 0;
	    for (i=1; i<15; i++)
	    {
	        sum += GetSkillValue(Npchar, SKILL_TYPE, GetSkillNameByIdx(i));
	    }
		if (!CheckAttribute(Npchar, "OfficerWantToGo.DontGo"))// aw013 �� ����������� ���� ������� 
		{ 
			return MOD_SKILL_ENEMY_RATE*4*sum;
		} 
		else 
		{ 
			return MOD_SKILL_ENEMY_RATE*8*sum; 
		}	
    }
    return 0;
}
int GetMoneyForOfficerFull(ref Npchar)
{
    float nLeaderShip = GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP);
	float nCommerce   = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	
	return makeint(GetMoneyForOfficer(Npchar)*2/(nLeaderShip + nCommerce) );
}

float SalaryCoeff_GetSetting(string _param)
{
	return stf(GetConvertStr(_param, KVL_MODS_FILE));
}

int GetSalaryForShip(ref chref)
{
    int i, cn, iMax;
    ref mchref, offref;
    int nPaymentQ = 0;
    float fExp;
    mchref = GetMainCharacter();
	float SalaryCoeff = 1.0;

	float nLeaderShip = GetSummonSkillFromNameToOld(mchref,SKILL_LEADERSHIP);
	float nCommerce   = GetSummonSkillFromNameToOld(mchref,SKILL_COMMERCE);

	float shClass = GetCharacterShipClass(chref);
	if (shClass   < 1) shClass   =7;
	if (!GetRemovable(chref) && sti(chref.index) != GetMainCharacterIndex()) return 0; // ������� ������ �����, � �� ����� �������������� �������!!!
	
	SalaryCoeff = SalaryCoeff_GetSetting("SalaryComplex_Coeff");
	if(SalaryCoeff <= 0.0)
	{
		SalaryCoeff = 1.0;
	}	
	if((SalaryCoeff > 0.0) && (SalaryCoeff <= 0.5))
	{
		SalaryCoeff = 0.5;
	}	
	
	// ������
	fExp = (GetCrewExp(chref, "Sailors") + GetCrewExp(chref, "Cannoners") + GetCrewExp(chref, "Soldiers")) / 100.00; // ������� ���� ����� 0..3
	nPaymentQ += makeint( SalaryCoeff * fExp * stf((0.5 + MOD_SKILL_ENEMY_RATE/5.0)*200*GetCrewQuantity(chref))/stf(shClass) * (1.05 - (nLeaderShip + nCommerce)/ 40.0) );
    
    // ������ ������ �������� � ��� �������� (���  ������� ����� �� ���������) ��� ��� ���������� � ��������� ����
    if(sti(chref.index) != GetMainCharacterIndex())
    {
        nPaymentQ += makeint(SalaryCoeff * GetMoneyForOfficer(chref)*2/(nLeaderShip + nCommerce) );
        // �������
        for(i = 1; i <=MAX_NUM_FIGHTERS; i++)  // � �3 ��� ���� � ���������� :(
	    {
	        cn = GetOfficersIndex(chref, i);
		    if( cn > 0 )
		    {
			    offref = GetCharacter(cn);
			    if (GetRemovable(offref)) // ������� ������ �����, � �� ����� �������������� �������!!!
			    {
			        nPaymentQ += makeint(SalaryCoeff * GetMoneyForOfficerFull(offref));
			    }
			}
		}
	}
	if(sti(chref.index) == GetMainCharacterIndex()) // ��� ��������� � ������� ��� �� �����
	{
        iMax = GetPassengersQuantity(mchref);
		for(i=0; i < iMax; i++)
        {
            cn = GetPassenger(mchref,i);
            if(cn != -1)
            {
                if(!IsCompanion(GetCharacter(cn)))
                {
                    offref = GetCharacter(cn);
                    if (GetRemovable(offref)) // ������� ������ �����, � �� ����� �������������� �������!!!
			        {
                        if(CheckAttribute(offref,"prisoned"))
    		            {
    			            if(sti(offref.prisoned)==true) continue;
    		            }
    			        nPaymentQ += makeint(SalaryCoeff * GetMoneyForOfficerFull(offref));
			        }
                }
            }
        }
    }
    return nPaymentQ;
}
// boal ����� ���� �� <--

int AddCrewMorale(ref chr, int add)
{
    int morale = MORALE_NORMAL;
	if (CheckAttribute(chr, "Ship.Crew.Morale")) morale = sti(chr.Ship.Crew.Morale);
    morale += add;
	if(morale < MORALE_MIN)	morale = MORALE_MIN;
	if(morale > MORALE_MAX)	morale = MORALE_MAX;
	chr.Ship.Crew.Morale = morale;
	
	return morale;
}

int GetCharacterRaiseCrewMoraleMoney(ref chr)
{
	float nLeaderShip = GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP);
	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_COMMERCE); // boal
	int nPaymentQ = 15 + GetCrewQuantity(chr)*(16 + MOD_SKILL_ENEMY_RATE*5 - nLeaderShip - nCommerce); // boal
	float fExp = (GetCrewExp(chr, "Sailors") + GetCrewExp(chr, "Cannoners") + GetCrewExp(chr, "Soldiers")) / 100.00; // ������� ���� ����� 0..3
	nPaymentQ = makeint(nPaymentQ * fExp + 0.5);	
	if (nPaymentQ < 5) nPaymentQ = 5;
	return nPaymentQ;
}

void DownCrewExp(ref chr, int days)
{
	ChangeCrewExp(chr, "Sailors", -makeint(days/10));
	ChangeCrewExp(chr, "Cannoners", -makeint(days/10));
	ChangeCrewExp(chr, "Soldiers", -makeint(days/10));
}

float ChangeCrewExp(ref chr, string sType, float fNewExp)
{
	if (!CheckAttribute(chr, "Ship.Crew.Exp." + sType)) chr.Ship.Crew.Exp.(sType) = (1 + rand(50));
	
	chr.Ship.Crew.Exp.(sType) = (stf(chr.Ship.Crew.Exp.(sType)) + fNewExp);
	if (stf(chr.Ship.Crew.Exp.(sType)) > 100) chr.Ship.Crew.Exp.(sType) = 100;
	if (stf(chr.Ship.Crew.Exp.(sType)) < 1) chr.Ship.Crew.Exp.(sType)   = 1;
	
	return stf(chr.Ship.Crew.Exp.(sType));	
}

float GetCrewExp(ref chr, string sType)
{
	if (!CheckAttribute(chr, "Ship.Crew.Exp." + sType)) chr.Ship.Crew.Exp.(sType) = 10;
	return stf(chr.Ship.Crew.Exp.(sType));	
}

float GetCrewExpRate()
{
	return makefloat(50 + MOD_SKILL_ENEMY_RATE);
}

int GetCharacterCrewMorale(ref chr)
{
	if(!CheckAttribute(chr, "ship.crew.morale"))
	{
		chr.ship.crew.morale = MORALE_NORMAL;
	}

	return sti(chr.ship.crew.morale);
}

// �������� ��������� � �������
void UpdateCrewInColonies()  
{
	int nNeedCrew = GetCurCrewEscadr(); // ����� ��������
	int ableCrew = GetMaxCrewAble();   // ���������� �����
	ref rTown;    
	int nPastQ, nPastM;
	int eSailors, eCannoners, eSoldiers;
	 
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		rTown = &colonies[i];
	    if (rTown.nation == "none") continue;
	    
	    if (GetNpcQuestPastDayParam(rTown, "CrewDate") >= (2+rand(2)) || !CheckAttribute(rTown, "CrewDate.control_year"))
	    {
	    	//trace("UpdateCrewInColonies " + rTown.id);
			SaveCurrentNpcQuestDateParam(rTown, "CrewDate");
			nPastQ = 0;
			//nPastM = MORALE_NORMAL;
			if (CheckAttribute(rTown,"ship.crew.quantity"))	nPastQ = sti(rTown.ship.crew.quantity);
			//if (CheckAttribute(rTown,"ship.crew.morale"))	nPastM = sti(rTown.ship.crew.morale);
		
			if (nNeedCrew >= ableCrew )
		    {
		        nNeedCrew = 1+rand(20);
		    }
		    else
		    {
		        nNeedCrew = ableCrew - nNeedCrew - rand(makeint((ableCrew - nNeedCrew)/2.0));
				if (nNeedCrew < 1) nNeedCrew = 1+rand(20);
		    }
		
			if (nPastQ > nNeedCrew)
			{	nPastM = MORALE_NORMAL/3 + rand(MORALE_MAX-MORALE_NORMAL/3);
			}
			else
			{	nPastM = MORALE_NORMAL/5 + rand(makeint(MORALE_NORMAL*1.5));
			}
			rTown.Ship.crew.quantity = nNeedCrew;
			rTown.Ship.crew.morale   = nPastM;
			// ������ ����� �� �����
			switch (sti(rTown.nation))
			{
				case ENGLAND:	
					eSailors   = 45; 
					eCannoners = 5;
					eSoldiers  = 20;
				break;
				case FRANCE:	
					eSailors   = 20; 
					eCannoners = 45;
					eSoldiers  = 5; 
				break;
				case SPAIN:		
					eSailors   = 5; 
					eCannoners = 20;
					eSoldiers  = 45; 
				break;
				case PIRATE:	
					eSailors   = 25; 
					eCannoners = 25;
					eSoldiers  = 45; 
				break;
				case HOLLAND:	
					eSailors   = 25; 
					eCannoners = 25;
					eSoldiers  = 5;
				break;
			}
			rTown.Ship.Crew.Exp.Sailors   = eSailors   + rand(2*eSailors)   + rand(10);
			rTown.Ship.Crew.Exp.Cannoners = eCannoners + rand(2*eCannoners) + rand(10);
			rTown.Ship.Crew.Exp.Soldiers  = eSoldiers  + rand(2*eSoldiers)  + rand(10);
			ChangeCrewExp(rTown, "Sailors", 0);  // ���������� � 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
		}
	}
}

int GetCrewPriceForTavern(string sColony)
{
	int iColony = FindColony(sColony);
	ref rTown = &colonies[iColony];
	
    float fExp = (GetCrewExp(rTown, "Sailors") + GetCrewExp(rTown, "Cannoners") + GetCrewExp(rTown, "Soldiers")) / 100.00; // ������� ���� ����� 0..3
	float fSkill = GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP) + GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_COMMERCE); // 0-20
    int   nCrewCost = makeint((0.5 + MOD_SKILL_ENEMY_RATE/5.0)*30 * (1.0 - fSkill / 40.0));
    
	nCrewCost = makeint(fExp*nCrewCost + 0.5);
	if (nCrewCost < 5) nCrewCost = 5; // �� ����!
	
	return nCrewCost;
}

int GetMaxCrewAble()
{
	float nLeaderShip = 0.5 + GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP);
    //MOD_SKILL_ENEMY_RATE
    return makeint(nLeaderShip*(55.0 + 10*(5-MOD_SKILL_ENEMY_RATE) + nLeaderShip * 15.0) + 2*nLeaderShip*abs(REPUTATION_NEUTRAL - sti(pchar.reputation)));
}

int GetCurCrewEscadr()
{
    int i, cn;
    int nNeedCrew = 0;

    for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(),i);
		if(cn>=0 && GetRemovable(&Characters[cn]))
		{
			nNeedCrew += GetCrewQuantity(GetCharacter(cn));
		}
	}
	return nNeedCrew;
}

void MunityOnShip(string _stat)
{
	int i;
	Statistic_AddValue(pchar, _stat, 1);
    MakeCloneShipDeck(pchar, true); // ������� ������
    i = FindLocation("Ship_deck");
    Locations[i].image = "loading\Mutiny_"+rand(3)".tga"; // ��� �������� �������, �������� ���� ��� ����������� ������
    DoQuestReloadToLocation("Ship_deck", "reload", "reload1", "Munity_on_Ship");
}
/* 20.01.08 ����� ������ =======================================================================
�������:
����� ������ ������������, ��������, ��������� ������ �� ����� (�������� ���������� �������)
��� ����� ������� ������� ���� ����� �� ������ � ����, ����� ���� � �������, �� ����� � ���� ������� ����� �����
����������, ���� ������, ������ �� ������, ���� ������, �� � ������.
����� ����� ���� �� ��������� �����, ������� ����� ������ �� ������ ��� � ��.
��������� ������ �������� �������������, ���� ������ ���, �� ����� ������ ���
������� ������ ������ -1 ������ ������ ����, ��� ����� ������, � ����� � ���, ���� ��� � ��������
����� �����������, ����, ���� ��� ������. ��� ����������, �� ���������� �� ���-�� � �� ������� ������.
����� � ������� ��������� �� �������-����������� �����, �� ���� �� �������� �� � ������� � ������ ���� �� �������� ����.
����� �� ��� ���� �����������, ��� ��� ������ �� �������� � ����������� �� �������.
������ ������ ������� ������� ����������, �� ���� ������� �������� ���� ���� ���� � �� ����� ������������� (������ ������ � ������� ��� ����).
*/
void Partition_SetValue(string state) // state = "before" || "after" - ��� ��������� ����-�����
{
	int      ret, part;
	int      i, cn, iMax;
	ref      chref;
	int      HowOff, HowComp, HowCrew;
	string   sTemp;
	// �������� �� ���� ������������, ������ � ���������� � �����������, ������� ������ �������� � ������ - ���� 0,
	// �� ��������� ������ �����, �� �������� ����
	ret = 0;
	// ������ - �� ������� �����������, �� � ���� �� ��� � �������� ������, �� ��� ����������� ��� ������
	// ������ � ���� - ��� ������ �� �� �������� �� �������, �� ������ �� - ������ ��
	HowComp = 0;
	HowCrew = 0;
	part = Partition_GetSetting("Part_HeroPart") + (10 - MOD_SKILL_ENEMY_RATE)*Partition_GetSetting("Part_HeroPart"); // ���� ��
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(Pchar, i);
		if (cn >= 0)
		{
			chref = GetCharacter(cn);
			if (GetRemovable(chref)) // ������� ������ �����
			{
				ret += sti(chref.Money);
				ret = ret + Partition_GetCargoValue(chref); // ������ �� ������� � �������
				HowComp += 1; // �� ��� ��
				HowCrew += GetCrewQuantity(chref);
				part += Partition_GetSetting("Part_CompanionShipPerClass") * (7 - GetCharacterShipClass(chref));
			}
		}
	}
	
	HowOff = 0;
	iMax = GetPassengersQuantity(Pchar);
	for(i=0; i < iMax; i++)
	{
		cn = GetPassenger(Pchar, i);
		if(cn != -1)
		{
			chref = GetCharacter(cn);
			if (GetRemovable(chref)) // ������� ������ �����
			{
				if(CheckAttribute(chref, "prisoned"))
				{
					if(sti(chref.prisoned)==true) continue;
				}
				
				ret += sti(chref.Money);
				HowOff += 1;
			}
		}
	}
	// �������� � �����
	ref loc;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)];
		
		for (i = 1; i <= 5; i++)
		{
			sTemp = "box" + i;
			if (CheckAttribute(loc, sTemp + ".money"))
			{
				ret += sti(loc.(sTemp).money);
			}
		}
	}
	
	Pchar.Partition.(state).Money   = ret;
	Pchar.Partition.(state).HowOff  = HowOff;
	Pchar.Partition.(state).HowComp = HowComp - 1;
	Pchar.Partition.(state).HowCrew = HowCrew;
	Pchar.Partition.(state).HeroPart = part;
	Log_TestInfo("Partition_SetValue." + state + " Money " + ret + " Off " + HowOff + " Comp " + (HowComp -1) + " Crew " + HowCrew);
	if (state == "after" && CheckAttribute(Pchar, "Partition.before.Money"))
	{
		if (sti(Pchar.Partition.before.Money) < sti(Pchar.Partition.after.Money))
		{  // ����� �����
			if (bPartitionSet)
			{
				int    TotalAmount;
				float  fOffPart, fCrewPart, fHeroPart;
				TotalAmount = sti(Pchar.Partition.after.Money) - sti(Pchar.Partition.before.Money);
				Log_TestInfo("����� �������� " + TotalAmount);
				
				HowOff  = Pchar.Partition.before.HowOff;
				HowComp = Pchar.Partition.before.HowComp;
				HowCrew = Pchar.Partition.before.HowCrew;
				
				HowCrew = HowCrew * Partition_GetSetting("Part_Crew");
				HowOff  = HowOff * Partition_GetSetting("Part_Officer") + HowComp * Partition_GetSetting("Part_Companion");
				fHeroPart = stf(Pchar.Partition.before.HeroPart);
				
				fCrewPart = HowCrew / (HowCrew + HowOff + fHeroPart);
				fOffPart  = HowOff / (HowCrew + HowOff + fHeroPart);
				
				if (!CheckAttribute(Pchar, "Partition.MonthPart"))           Pchar.Partition.MonthPart = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Crew"))      Pchar.Partition.MonthPart.Crew = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Officers"))  Pchar.Partition.MonthPart.Officers = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Hero"))      Pchar.Partition.MonthPart.Hero = 0;
				
				ret = makeint(fCrewPart * TotalAmount);
				Pchar.Partition.MonthPart.Crew     = sti(Pchar.Partition.MonthPart.Crew) + ret;
				Pchar.Partition.MonthPart.Officers = sti(Pchar.Partition.MonthPart.Officers) + makeint(fOffPart * TotalAmount);
				ret += makeint(fOffPart * TotalAmount);
				
				Pchar.Partition.MonthPart.Hero = sti(Pchar.Partition.MonthPart.Hero) + (TotalAmount - ret);
				Pchar.Partition.MonthPart = sti(Pchar.Partition.MonthPart) + ret;
				Log_TestInfo("���� ������� " + ret + ". ���� ����� �������� " + Pchar.Partition.MonthPart);
			}
		}
	}
}

int Partition_GetSetting(string _param)
{
	return sti(GetConvertStr(_param, "PartitionSettings.txt"));
}

int Partition_GetCargoValue(ref chref)
{
	float    ret;
	int      i, st;
	ref      rGood;
	string   sGood;
	ref      shref;
	ref      Cannon;
	
	ret = 0;
	//return 0;
	st = GetCharacterShipType(chref);
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		
		ret += sti(shref.Price) * 0.2; // 0.2 - ��������� ��������� ������� ��� �������
		// ����� ������� �� ������
		if (sti(chref.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		{
		    Cannon = GetCannonByType(sti(chref.Ship.Cannons.Type));
		    ret += sti(Cannon.Cost) * 0.33 * GetCannonsNum(chref);
		}
		for (i=0; i<GOODS_QUANTITY; i++)
		{
			sGood = Goods[i].name;
			if(i > GOOD_CANNON_8 - 1)
			{
				ret += makefloat(GetCargoGoods(chref, i) * sti(Goods[i].Cost) * 0.33 / stf(Goods[i].Units));  
			}
			else
			{
				ret += makefloat(GetCargoGoods(chref, i) * sti(Goods[i].Cost) * 0.7 / stf(Goods[i].Units));  // 0.7 - ��������� ������� ����
			}	
		}
	}
	return makeint(ret);
}