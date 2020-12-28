
#define REAL_SHIPS_QUANTITY 900

object	RealShips[REAL_SHIPS_QUANTITY];
#define SAILSCOLOR_PRICE_RATE    0.1 
#define SAILSGERALD_PRICE_RATE   0.2 

#define SAIL_COST_PERCENT 10
#define HULL_COST_PERCENT 20

ref GetRealShip(int iType) 
{ 
	if(iType >= REAL_SHIPS_QUANTITY)
	{
		trace ("--- Wrong Ship Index. iType is " + iType);
		Log_TestInfo("--- Wrong Ship Index. iType is " + iType);
		return &ShipsTypes[SHIP_TYPES_QUANTITY + 1]; // ��� ������
	}
	return &RealShips[iType]; 
}

// isLock - ��������, ����� ���������� (26.05.06 boal)
// ����� ����� isLock (04.07.06) ������ ��� ������� ������������ (�� ���� �� �����)
// ���� 1 - ����������, ���� ���������, 0 - ������ ��������� - ����� �����������.
int GenerateShip(int iBaseType, bool isLock)
{
	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    //Boyer change for ERAS2 #20170318-49
    if(CheckAttribute(rRealShip, "hullNums")) {
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
        //Trace("Hull nums = " + rRealShip.hullNums);
    }
    else {
        rRealShip.ship.upgrades.hull = 1 + rand(2);
    }
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // ������ ���������� �������
	
	if (!CheckAttribute(rRealShip, "isFort"))
	{
	    int iCaliber = sti(rRealShip.MaxCaliber);
	    if (sti(rRealShip.Class) != 7)
	    {  // ���� �� ���� ������� � 16�
		    switch(iCaliber)
		    {
                case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
				case 42:
					iCaliber = 7;
				break;
		    }
			//iCaliber = iCaliber - rand(1);
		    iCaliber = iCaliber; //Jason: �������� ����� ������� ������ ������ ������ ���� ���������, �� ���� �������� ������ �� ������� ������, � ������ - ������ �� �����������, �� ���. ������ �����, ����������� ��� ���������
		    if (iCaliber < 0) iCaliber = 0;
		    if (sti(rRealShip.Class) == 1)
		    {
		    	if (iCaliber > 7) iCaliber = 7;
		    }
		    else
		    {
		    	if (iCaliber > 6) iCaliber = 6;
		    }
		    switch(iCaliber)
		    {
                case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
				case 7:
					iCaliber = 42;
				break;
		    }
		    rRealShip.MaxCaliber = iCaliber;
	    }
	    rRealShip.SpeedRate	       = stf(rRealShip.SpeedRate) + frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0;
	    rRealShip.TurnRate         = stf(rRealShip.TurnRate) + frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0;
	    //rRealShip.Price            = sti(rRealShip.Price) + rand(makeint(sti(rRealShip.Price)/2)) - makeint(sti(rRealShip.Price)/4);
	    rRealShip.HP               = sti(rRealShip.HP) + rand(makeint(sti(rRealShip.HP)/5)) - makeint(sti(rRealShip.HP)/10);
	    rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + frandSmall(stf(rRealShip.WindAgainstSpeed)/5.0) - stf(rRealShip.WindAgainstSpeed)/10.0;
	}
    rRealShip.Capacity        = sti(rRealShip.Capacity) + rand(makeint(sti(rRealShip.Capacity)/4)) - makeint(sti(rRealShip.Capacity)/8);
    rRealShip.OptCrew         = makeint(sti(rRealShip.OptCrew) + rand(makeint(sti(rRealShip.OptCrew)/3)) - makeint(sti(rRealShip.OptCrew)/6));
    rRealShip.MaxCrew         = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);  // 25% ���������
    rRealShip.MinCrew         = makeint(sti(rRealShip.MinCrew) + rand(makeint(sti(rRealShip.MinCrew)/3)) - makeint(sti(rRealShip.MinCrew)/6));

	rRealShip.Weight		  = sti(rRealShip.Weight) + rand(sti(rRealShip.Weight)/20) - rand(sti(rRealShip.Weight)/20);
	
	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = sti(rRealShip.OptCrew);
    // to_do del <--
    
	int iDiffWeight			= sti(rRealShip.Weight) - sti(rBaseShip.Weight);
	int iDiffCapacity		= sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
	int iDiffMaxCrew		= sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
	int iDiffMinCrew		= sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
	float fDiffSpeedRate	= stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
	int iDiffTurnRate		= sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
	int iDiffHP	    		= sti(rRealShip.HP) - sti(rBaseShip.HP);

	rRealShip.Price	= GetShipPriceByTTH(iShip, &NullCharacter); //(iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + sti(rRealShip.Price);

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = isLock;  // ������������

	return iShip;
}

// -> added by ugeen 25.01.09 (�� ������ GenerateShip(.....)) - ������������� ���-�� ������� �� �����
// 31.01.09 - ������� ������ � ����������� ������ ���� ���-�� ������ �� ����� < ��������
int GenerateShipExt(int iBaseType, bool isLock, ref chr)
{
	string  attr, sCity;
	int 	i;
	aref 	refShip;
	float	�dckyrd = 1.0;
	bool	isShipyard = false; 
	
	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	//Boyer change for ERAS2 #20170318-49
    if(CheckAttribute(rRealShip, "hullNums")) {
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
        //Trace("Hull nums = " + rRealShip.hullNums);
    }
    else {
        rRealShip.ship.upgrades.hull = 1 + rand(2);
    }
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // ������ ���������� �������
	
	// ugeen --> ���� �������� ��������� �� �����, ������� ������ ����� �����
	if (CheckAttribute(chr, "City")) 
	{
		sCity = chr.City; 
		if(CheckCharacterID(chr, sCity + "_shipyarder"))
		{
			�dckyrd 	= 0.8;
			isShipyard 	= true;
		}
	}	
	// ugeen

	if (!CheckAttribute(rRealShip, "isFort"))
	{
		int iCaliber = sti(rRealShip.MaxCaliber);
		if (sti(rRealShip.Class) != 7 && !CheckAttribute(rRealShip, "QuestShip"))
		{  // ���� �� ���� ������� � 16�
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
				case 42:
					iCaliber = 7;
				break;
			}
			//iCaliber = iCaliber - rand(1);
			iCaliber = iCaliber; //Jason: �������� ����� ������� ������ ������ ������ ���� ���������, �� ���� �������� ������ �� ������� ������, � ������ - ������ �� �����������, �� ���. ������ �����, ����������� ��� ���������
			if (iCaliber < 0) iCaliber = 0;
			if (sti(rRealShip.Class) == 1)
			{
				if (iCaliber > 7) iCaliber = 7;
			}
			else
			{
				if (iCaliber > 6) iCaliber = 6;
			}
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
				case 7:
					iCaliber = 42;
				break;
			}
			rRealShip.MaxCaliber = iCaliber;
		}

		int   iCannonDiff 		= 0;
		int   iDiffClass  		= 5 - makeint(sti(rRealShip.Class)/2);
		
		switch(rRealShip.BaseName)
		{
			// 7-� �����
			case "WAR_TARTANE": 
				iCannonDiff = rand(1);  // 8, 6
			break;
			case "BERMSLOOP": 
				iCannonDiff = rand(1);  // 8, 6
			break;
			case "EMPRESS": 
				iCannonDiff = rand(1);  // 10, 8
			break;
			case "PINK": 
				iCannonDiff = rand(1);  // 12, 10
			break;
			case "LUGGER": 
				iCannonDiff = rand(1);  // 12, 10
			break;
			case "LUGGER_H": 
				iCannonDiff = rand(1);  // 12, 10
			break;
			
			// 6-� �����
			case "SPEEDY":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "FR_SLOOP":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "POLACCA":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "SLOOP":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "GALEOTH_H":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "DERFFLINGER":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BARQUE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "NEPTUNUS":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "CASTELF":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BARKENTINE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIGANTINE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIG":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIGHEAVY":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "SLOOP_B":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "PINNACE":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "SOPHIE":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "FLEUT":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "INTERCEPTOR":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			
			// 5-� �����
			case "FR_POSTILLIONEN":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "SCHOONER":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "COLONIALSCHOONER":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "DUTCHPINNACE":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "PO_FLEUT50":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "GALEON_L":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "XEBEC":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "BATTLEXEBEC":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "SCHOONERLIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "SHNYAVA":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "POLACRE":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "XEBECLIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "ENSLAVER":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "GREYHOUND":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "CORVETTELIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "PACKET_BRIG":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "MIRAGE":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "PDN":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "ENTERPRISE":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "POLACRE_H":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			
			// 4-� �����
			case "CRIMSONBLOOD":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "XEBEKVT":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "FELIPE":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "PINNACELIGHT":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "CARAVEL":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "FRIGATEMEDIUM":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "CARAVEL2":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "CORVETTE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "FRIGATE_l":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "BLACKANGEL":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "BATTLECORVETTE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "COASTALFRIGATE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "RAAFRIGATE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "FLEUTWAR":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "FLEUTWARSAT":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "GALEONTRADER":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "JAMAICASHIP":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "LYDIA":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "THEBLACKPEARL":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "FR_FRIGATE":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "GALEON_H":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "GALEON1":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "LA_MARIANNA":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "PIRATFASTGAL":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "UNICORN":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			
			// 3-� �����
			case "REVENGE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "GALEON50":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "LINEFRIGATE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "LIGHTFRIGATE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "BOUSSOLE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "FASTFRIGATE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "SURPRISE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "SALAMANDER":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "FRIGATE_SAT":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "BATTLEFRIGATE":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "NIGHTMARE":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "FRIGATE":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "FR_ESSEX":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "MORDAUNT":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "FRIGATE_H":
				iCannonDiff = rand(4);  // 50, 48, 46, 44, 42
			break;
			case "AMSTERDAM":
				iCannonDiff = rand(4);  // 50, 48, 46, 44, 42
			break;
			case "WARGALLEON2":
				iCannonDiff = rand(4);  // 52, 50, 48, 46, 44
			break;
			case "NL_PINNACEOFWAR47":
				iCannonDiff = rand(4);  // 54, 52, 50, 48, 46
			break;
			case "HOLLGALEON_H":
				iCannonDiff = rand(4);  // 54, 52, 50, 48, 46
			break;
			case "CARRACA":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "CONSTITUTION":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "FEARLESS":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "NL_FWZP":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "LINESHIP":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "OXFORD":
				iCannonDiff = rand(4);  // 58, 56, 54, 52, 50
			break;
			
			// 2-� �����
			case "DUTCHLINESHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "DUTCHSHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "NL_CONVOISHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "COURONNE":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "ALEXIS":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "LINESHIPHEAVY":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "WARSHIP":
				iCannonDiff = rand(4);  // 66, 64, 62, 60, 58
			break;
			case "POSEIDON":
				iCannonDiff = rand(4);  // 66, 64, 62, 60, 58
			break;
			case "HMS_CENTURION":
				iCannonDiff = rand(4);  // 68, 66, 64, 62, 60
			break;
			case "RESOLUTION":
				iCannonDiff = rand(4);  // 70, 68, 66, 64, 62
			break;
			case "FR_SUPERIORWARSHIP1":
				iCannonDiff = rand(4);  // 74, 72, 70, 68, 66
			break;
			case "HEAVYWARSHIP":
				iCannonDiff = rand(4);  // 74, 72, 70, 68, 66
			break;
			case "LINK":
				iCannonDiff = rand(4);  // 78, 76, 74, 72, 70
			break;
			case "SUPERBE":
				iCannonDiff = rand(4);  // 78, 76, 74, 72, 70
			break;
			
			// 1-� �����
			case "BATTLESHIP":
				iCannonDiff = rand(5);  // 80, 78, 76, 74, 72, 70
			break;
			case "HEAVYLINESHIP":
				iCannonDiff = rand(5);  // 82, 80, 78, 76, 74, 72
			break;
			case "LINK2":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "BELLONA":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "LINEARSHIP":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "SHARK":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "INTREPIDE":
				iCannonDiff = rand(5);  // 90, 88, 86, 84, 82, 80
			break;
			case "FR_TRINITY":
				iCannonDiff = rand(5);  // 96, 94, 92, 90, 88, 86
			break;
			case "MANOWAR_FAST":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "BATTLEMANOWAR":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "MANOWAR_GUB":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "PRINCE":
				iCannonDiff = rand(5);  // 102, 100, 98, 96, 94, 92
			break;
			case "MANOWAR":
				iCannonDiff = rand(5);  // 102, 100, 98, 96, 94, 92
			break;
			case "HMS_VICTORY":
				iCannonDiff = rand(5);  // 104, 102, 100, 98, 96, 94
			break;
			case "SP_SANFELIPE":
				iCannonDiff = rand(5);  // 108, 106, 104, 102, 100, 98
			break;
			
			//������ �� ���������  ����� ���� ������� ��������
			case "SoleyRu":
				iCannonDiff = rand(5);  // 112, 110, 108,106,104,102
			break;
			case "BrigQeen":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "BrigSW":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "XebekVML":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "Corvette_quest":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "ArabellaShip":
				iCannonDiff = rand(3);  // 52, 50, 48, 46
			break;
			case "Flyingdutchman":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
		}
		if(CheckAttribute(rRealShip, "QuestShip") || isShipyard) iCannonDiff = 0;
		
		if(rRealShip.BaseName == "FrigateQueen") iCannonDiff = 2; // ������ ������ "��������" 48-� ��������
		
		// ���������� ��� ������ �������
		makearef(refShip, chr.Ship);
		ResetShipCannonsDamages(chr);
		
		// ����-���� ������� ����������� ��������� ���-�� ������ (����� ����� �����, ���� ������� ��������������� �� ���� ����)
		rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);		
		// �������������� ������ ! ����� ������ ����������� ����� ������ ! 	
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
			rRealShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
			rRealShip.Cannons.Borts.rcannon.damages.(attr) = 1.0; 
			rRealShip.Cannons.Borts.lcannon.damages.(attr) = 1.0; 
			
			refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
			refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
			refShip.Cannons.Borts.rcannon.damages.(attr) = 1.0; 
			refShip.Cannons.Borts.lcannon.damages.(attr) = 1.0; 
		}
				
		rRealShip.rcannon = sti(rRealShip.rcannon) - iCannonDiff;				
		rRealShip.lcannon = sti(rRealShip.lcannon) - iCannonDiff;
		
		rRealShip.cannonr = sti(rRealShip.rcannon);
		rRealShip.cannonl = sti(rRealShip.lcannon);
		rRealShip.cannonf = sti(rRealShip.fcannon);
		rRealShip.cannonb = sti(rRealShip.bcannon);
/*
		refShip.cannonr = sti(rRealShip.rcannon);
		refShip.cannonl = sti(rRealShip.lcannon);
		refShip.cannonf = sti(rRealShip.fcannon);
		refShip.cannonb = sti(rRealShip.bcannon);
*/		
		rRealShip.Cannons = sti(rRealShip.CannonsQuantityMax) - iCannonDiff * 2;
		rRealShip.CannonsQuantity = sti(rRealShip.Cannons);
		
		//� ������ ������� ������ ������� � ��������� ��� ����������		
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonr.damages.(attr) = 0.0; 
			rRealShip.Cannons.borts.cannonl.damages.(attr) = 0.0; 
			rRealShip.Cannons.borts.rcannon.damages.(attr) = 0.0; 
			rRealShip.Cannons.borts.lcannon.damages.(attr) = 0.0; 
			
			refShip.Cannons.borts.cannonr.damages.(attr) = 0.0; 
			refShip.Cannons.borts.cannonl.damages.(attr) = 0.0; 
			refShip.Cannons.borts.rcannon.damages.(attr) = 0.0; 
			refShip.Cannons.borts.lcannon.damages.(attr) = 0.0; 
		}	

		for (i = 0; i < sti(rRealShip.fcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonf.damages.(attr) = 0.0; 			
			rRealShip.Cannons.borts.fcannon.damages.(attr) = 0.0; 			
			refShip.Cannons.borts.cannonf.damages.(attr) = 0.0; 
			refShip.Cannons.borts.fcannon.damages.(attr) = 0.0; 
		}
		
		for (i = 0; i < sti(rRealShip.bcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonb.damages.(attr) = 0.0; 			
			rRealShip.Cannons.borts.bcannon.damages.(attr) = 0.0; 			
			refShip.Cannons.borts.cannonb.damages.(attr) = 0.0; 
			refShip.Cannons.borts.bcannon.damages.(attr) = 0.0; 		
		}
		
		refShip.Cannons.Borts.cannonl = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.cannonr = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.cannonf = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.cannonb = sti(rRealShip.bcannon);
		
		refShip.Cannons.Borts.lcannon = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.rcannon = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.fcannon = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.bcannon = sti(rRealShip.bcannon);
		
		refShip.Cannons = sti(rRealShip.Cannons);
		// <-- ������ �������
		
		rRealShip.Bonus_Capacity 	= 0;
		rRealShip.Bonus_HP			= 0;
		rRealShip.Bonus_SpeedRate   = 0.0;
		rRealShip.Bonus_TurnRate	= 0.0;
		
		if(!CheckAttribute(rRealShip, "QuestShip"))
		{	
			rRealShip.Bonus_Capacity 	= makeint((sti(rRealShip.Capacity)*iCannonDiff)/(15 * iDiffClass));
			rRealShip.Bonus_HP 			= makeint((sti(rRealShip.HP)*iCannonDiff)/(15 * iDiffClass));  
			rRealShip.Bonus_SpeedRate   = (stf(rRealShip.SpeedRate)*iCannonDiff)/(15 * iDiffClass);
			rRealShip.Bonus_TurnRate    = (stf(rRealShip.TurnRate)*iCannonDiff)/(15 * iDiffClass);
		
			rRealShip.SpeedRate	   		= stf(rRealShip.SpeedRate) + �dckyrd * (frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0);
			rRealShip.TurnRate         	= stf(rRealShip.TurnRate) + �dckyrd * (frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0);
			//rRealShip.Price            = sti(rRealShip.Price) + rand(makeint(sti(rRealShip.Price)/2)) - makeint(sti(rRealShip.Price)/4);
			rRealShip.HP               	= sti(rRealShip.HP) + makeint(�dckyrd * (rand(makeint(sti(rRealShip.HP)/5)) - makeint(sti(rRealShip.HP)/10)));
			rRealShip.WindAgainstSpeed 	= stf(rRealShip.WindAgainstSpeed) + �dckyrd * (frandSmall(stf(rRealShip.WindAgainstSpeed)/5.0) - stf(rRealShip.WindAgainstSpeed)/10.0);
		}	
	}
	
	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		rRealShip.Capacity        = sti(rRealShip.Capacity) + makeint(�dckyrd * (rand(makeint(sti(rRealShip.Capacity)/4)) - makeint(sti(rRealShip.Capacity)/8)));
		rRealShip.OptCrew         = makeint(sti(rRealShip.OptCrew) + �dckyrd * (rand(makeint(sti(rRealShip.OptCrew)/3)) - makeint(sti(rRealShip.OptCrew)/6)));
		rRealShip.MaxCrew         = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);  // 25% ���������
		rRealShip.MinCrew         = makeint(sti(rRealShip.MinCrew) + �dckyrd * (rand(makeint(sti(rRealShip.MinCrew)/3)) - makeint(sti(rRealShip.MinCrew)/6)));
		rRealShip.Weight		  = sti(rRealShip.Weight) + makeint(�dckyrd * (rand(sti(rRealShip.Weight)/20) - rand(sti(rRealShip.Weight)/20)));
	}	
	
	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = sti(rRealShip.OptCrew);
	// to_do del <--
	
	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		if(CheckAttribute(rRealShip, "Bonus_Capacity"))	rRealShip.Capacity = sti(rRealShip.Capacity) + sti(rRealShip.Bonus_Capacity);
		if(CheckAttribute(rRealShip, "Bonus_HP")) rRealShip.HP = sti(rRealShip.HP) + sti(rRealShip.Bonus_HP);
		if(CheckAttribute(rRealShip, "Bonus_SpeedRate")) rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + stf(rRealShip.Bonus_SpeedRate);
		if(CheckAttribute(rRealShip, "Bonus_TurnRate"))	rRealShip.TurnRate = stf(rRealShip.TurnRate) + stf(rRealShip.Bonus_TurnRate);
	}	
    
	int iDiffWeight			= sti(rRealShip.Weight) - sti(rBaseShip.Weight);
	int iDiffCapacity		= sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
	int iDiffMaxCrew		= sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
	int iDiffMinCrew		= sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
	float fDiffSpeedRate	= stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
	int iDiffTurnRate		= sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
	int iDiffHP	    		= sti(rRealShip.HP) - sti(rBaseShip.HP);

	rRealShip.Price	= GetShipPriceByTTH(iShip, chr); //(iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + sti(rRealShip.Price);

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = isLock;  // ������������

	return iShip;
}
// -> ugeen

/*
//Jason, ��������� ������� � ��������� �������; ����� ����� ������ - ������ ����.
int GenerateShipHand(ref chr, int iType, int cc, int cp, int cr, int hp, int pr, float sr, float tr, float aw)
{
	aref 	refShip;

	int iShip = CreateBaseShip(iType);

	if (iShip == -1) return SHIP_NOTUSED;

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    rRealShip.ship.upgrades.hull  = 1;//������ ������
	rRealShip.ship.upgrades.sails = 3;// ������ ������
	
	rRealShip.MaxCaliber = cc;
	rRealShip.SpeedRate = sr;
	rRealShip.TurnRate = tr;
	rRealShip.HP = hp;
	rRealShip.BaseHP = hp;
	rRealShip.WindAgainstSpeed = aw;
    rRealShip.Capacity = cp;
    rRealShip.OptCrew = cr;
    rRealShip.MaxCrew = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);
    rRealShip.MinCrew = makeint(sti(rRealShip.MinCrew) + makeint(sti(rRealShip.MinCrew)/4)) - makeint(sti(rRealShip.MinCrew)/7);
	rRealShip.Weight = sti(rRealShip.Weight) + sti(rRealShip.Weight)/20 - sti(rRealShip.Weight)/20;
	rRealShip.Price	= pr;
	
	makearef(refShip, chr.Ship);
	ResetShipCannonsDamages(chr);
	rRealShip.CannonsQuantityMax	= sti(rRealShip.CannonsQuantity);		

	rRealShip.Cannons 				= sti(refShip.CannonsQuantityMax);
	rRealShip.CannonsQuantity 		= sti(rRealShip.Cannons);		
	refShip.Cannons 				= sti(rRealShip.Cannons);
	
	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = sti(rRealShip.OptCrew);
    // to_do del <--

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = false;

	return iShip;
}*/

int CreateBaseShip(int iBaseType)
{
	int iShip = FindFirstEmptyShip();

	if(iShip == -1)
	{
        trace("Can not find empty ship slot");
		return SHIP_NOTUSED;
	}

	ref rBaseShip = GetShipByType(iBaseType);
	ref rRealShip = GetRealShip(iShip);
	DeleteAttribute(rRealShip, "");
	CopyAttributes(rRealShip, rBaseShip);
    rRealShip.index = iShip;
    rRealShip.BaseType = iBaseType;
    if (!CheckAttribute(rRealShip, "ship.upgrades.hull")) // ���� ������ � ����, �� ��������� ���, �� ����������
    {
    	rRealShip.ship.upgrades.hull = 1;  //������� ������� ������
    }
	rRealShip.ship.upgrades.sails = 1;
	
    rRealShip.BaseName = rRealShip.name; // ����������� ��� ����, �� ����� ���� "��������"
	if (rRealShip.name != "Fort" && rRealShip.name != "Boat") // �� ���� ����� :(
	{
		rRealShip.name = rRealShip.name + "1"; // ��� ����� �����, �� ������!!!!!!!!!!!!!!
		// ������� - ����� � ������� ����� �� ����� 1, ��� � �����
	}
    rRealShip.Stolen = 0;  // ������������ - �������
    
	if (iArcadeSails == 0) // ������ ������� ���� ��� �������
	{
	    rRealShip.InertiaAccelerationY = stf(rRealShip.InertiaAccelerationY) / 2.0;
	}
    
	return iShip;
}

void ResetShipCannonsDamages(ref refCharacter)
{
	aref refShip;
	
	makearef(refShip, refCharacter.Ship);
	refShip.Cannons.Borts = "";

	if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); }		
		
	if (CheckAttribute(refShip, "Cannons.Borts.fcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.fcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.bcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.bcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.lcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.lcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.rcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.rcannon.damages"); }
}

// ��������� ������� ��� �����
int GenerateStoreShip(int iBaseType)
{
	int iShip = GenerateShip(iBaseType, 0); // ������� 

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
    rRealShip.StoreShip = true;  // ������� �� �����, ������ ��������� �������
    
	return iShip;	
}

// ����������� ������ 26.05.06 boal

// -> ugeen 25.01.09 -> ��� �����
int GenerateStoreShipExt(int iBaseType, ref chr)
{
	int iShip = GenerateShipExt(iBaseType, 0, chr); // ������� 

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
	rRealShip.StoreShip = false;  // ������� �� �����, ������ ��������� �������
    
	return iShip;	
}
// <- ugeen

// ����: ���� ��� �������, ��� ��� ���-���������, ��� ����� �����
void EmptyAllFantomShips()
{
	int  i;
	ref  chr;
	// ����������� ��� - ��� �������, � �� ��������� ����. � ������ ���� ������ ���� �����������, ����� �����������, ��� ���� ���
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        DeleteAttribute(&RealShips[i], "lock");
	}
	// ����� ������, �� �� ����� ������ ��� �� ��������� MAX_CHARACTERS
	//RealShips[sti(Characters[BOAT_CHARACTER].ship.type)].lock = true;
	// ������ ���-����
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
        // ������� ��� �����
		if (CheckAttribute(chr, "shipyard"))
		{
		    FreeShipFromShipyard(chr);
		}
	}
	for (i = FANTOM_CHARACTERS; i < TOTAL_CHARACTERS; i++) // ������� � ����
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
		else
		{
			InitCharacter(&Characters[i], i);	//ugeen : ������ ����� ��� �������� ������ �������� (�������������)
		}
	}
	// ������ ������ ������
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if (!CheckAttribute(&RealShips[i], "lock") && !CheckAttribute(&RealShips[i], "StoreShip"))  // �� ����� ������� �� ����
        {
			DeleteAttribute(&RealShips[i], "");
		}
	}
}

int GetRealShipsCount()
{ // ����� ��� �������
	int result = 0;

	for (int i= 0; i< REAL_SHIPS_QUANTITY; i++)
	{
		if (checkAttribute(&RealShips[i], "name"))
		{
			result++;
		}
	}

	return result;
}

// ����� ������� �����
int FindFirstEmptyShip()
{
	for(int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!checkAttribute(&RealShips[i], "name"))
		{
			//#20170912-02 Fix for RealShips/Character sails
		    DeleteAttribute(&RealShips[i], "ship.upgrades");
		    DeleteAttribute(&RealShips[i], "EmblemedSails");
		    DeleteAttribute(&RealShips[i], "GeraldSails");
			return i;
		}
	}

	return -1;
}


/*
float SpeedByHullUpgrade(aref refCharacter)
{
	int iHull = sti(refCharacter.ship.upgrades.hull) - 1;

	float fResult = 1.0 - (0.05 * iHull);

	return fResult;
}


float SpeedBySailsUpgrade(aref refCharacter)
{
	int iSails = sti(refCharacter.ship.upgrades.sails) - 1;
	iSails = iSails * 5;
	float fResult = 1.0 + (0.01 * iSails);

	return fResult;
}
*/
//Boyer add for new game #20170301-6
void ResetRealShipArray()
{
	for(int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		DeleteAttribute(&RealShips[i], "name");
	}
	return;
}

float FindShipSpeed(aref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);
	
	float	fMaxSpeedZ = stf(rShip.SpeedRate);  // ������� ��������
	float fShipHp = stf(refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.8 + fSpeedFromHp*0.3;

	if(fSpeedFromHp > 1.0) // ����� ����� ����� ��������� ��������
	{
		fSpeedFromHp = 1.0;
	}

	fMaxSpeedZ = fMaxSpeedZ * AIShip_isPerksUse(CheckCharacterPerk(refCharacter, "MapMaker"), 1.0, 1.05);
	float fSailsDamage = stf(refCharacter.ship.sp);

	float	fTRFromSailDamage = Bring2Range(0.1, 1.0, 0.1, 100.0, fSailsDamage); //0.3

	float fTRFromShipState = fSpeedFromHp * fTRFromSailDamage;
    if(!CheckAttribute(refCharacter, "Cargo")) RecalculateCargoLoad(refCharacter);
	float	fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float	fTRFromWeight = Clampf(1.03 - stf(rShip.SpeedDependWeight) * fLoad);
	float   fTRFromSkill = SpeedBySkill(refCharacter);
	// �� �������
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	fTRFromPeople = 0.85 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.15;
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	 
	fMaxSpeedZ = fMaxSpeedZ * fTRFromWeight * fTRFromSkill * fTRFromShipState * fTRFromPeople;

	return fMaxSpeedZ;
}

float SpeedBySkill(aref refCharacter)
{
	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);

	float fTRFromSkill = 0.7 + (0.03 *  fSkill);

	//float fSpeedByHullUpgrade = SpeedByHullUpgrade(refCharacter);
	//float fSpeedBySailsUpgrade = SpeedBySailsUpgrade(refCharacter);

	//fTRFromSKill = fTRFromSKill * fSpeedByHullUpgrade * fSpeedBySailsUpgrade;
    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipSpeedUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
    
	return fTRFromSKill*fSpeedPerk;
}

float FindShipTurnRate(aref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);

	float fShipHp = stf(refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.7 + fSpeedFromHp * 0.3;
    if(!CheckAttribute(refCharacter, "Cargo")) RecalculateCargoLoad(refCharacter);
	float fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float fTRFromWeight;
	if (iArcadeSails == 1)
	{
		fTRFromWeight = Clampf(1.03 - stf(rShip.TurnDependWeight) * fLoad);
	}
	else
	{
		fTRFromWeight = Clampf(1.03 - 2.0*stf(rShip.TurnDependWeight) * fLoad); // ������� ���� ������
	}
	// �� �����������, ������ 1 float fTRFromSpeed = 1.0 - stf(rShip.TurnDependSpeed);
	// �� �������
	//float fCrewMin = stf(rShip.MinCrew);
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	if (iArcadeSails == 1)
	{
		fTRFromPeople = 0.3 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.7;
	}
	else
	{
		fTRFromPeople = 0.05 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.95;
	}
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	
	float fTRFromSKill = TurnBySkill(refCharacter);

	float fTRFromSailDamage = Bring2Range(0.05, 1.0, 0.1, 100.0, stf(refCharacter.ship.sp));

	float fTurn = fTRFromWeight * fTRFromSkill * fTRFromPeople * fTRFromSailDamage * fSpeedFromHp;

	//Log_info(refCharacter.id + "  " + fTurn);
	return fTurn;	
}

float TurnBySkill(aref refCharacter)
{
	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
	float fTRFromSKill;

    if (iArcadeSails == 1)
	{
		fTRFromSKill = 0.5 + (0.05 * fSkill);
	}
	else
	{
		fTRFromSKill = 0.3 + (0.07 * fSkill);
	}
	
    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipTurnRateUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
    float fFastTurn180 = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "Turn180"), 1.0, 4.0);
    
	return fTRFromSKill*fSpeedPerk*fFastTurn180;
}

int GetCannonsNum(aref chr)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);
	int iCannons = GetBortIntactCannonsNum(chr, "fcannon", sti(refBaseShip.fcannon)) + GetBortIntactCannonsNum(chr, "bcannon", sti(refBaseShip.bcannon)) + GetBortIntactCannonsNum(chr, "lcannon", sti(refBaseShip.lcannon)) + GetBortIntactCannonsNum(chr, "rcannon", sti(refBaseShip.rcannon));
	return iCannons;
}

// ugeen  02.02.09 
int GetCannonsNumMax(aref chr)
{
	int nShipType = sti(chr.ship.type);
	ref refBaseShip = GetRealShip(nShipType);

	int iCannons = sti(refBaseShip.CannonsQuantityMax);
		
	return iCannons;
}
// ugeen

// boal
int GetBortCannonsQty(aref chr, string  sType)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);

	int iCannons = GetBortIntactCannonsNum(chr, sType, sti(refBaseShip.(sType)));

	return iCannons;
}

int GetBortCannonsMaxQty(aref chr, string  sType)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);

	int iCannons = sti(refBaseShip.(sType));

	return iCannons;
}

int GetBortCannonsBaseQty(ref chr, string sBort)
{
	int nShipType = sti(chr.ship.type);
	ref rRealShip = GetRealShip(nShipType);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	
	int iCannons = sti(rBaseShip.(sBort));
	
	return iCannons;
}
///////////////////////  ����� //////////////////////
void SetShipyardStore(ref NPChar)
{
    int    iTest_ship, i;
	string attrName;
	
	if (CheckAttribute(NPChar, "shipyard")) return; // ��� ���� ������� � ���� ����
	
	SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // ���� ���������� �����
    
    if (bBettaTestMode)
    {
        for (i = 1; i <=SHIP_TYPES_QUANTITY; i++)
        {
            attrName = "ship" + i;
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(i-1, NPChar), attrName);
        }
        return;
    }
    
																					
	
					  
					 
  
	FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1"); // ������������ �� �����
  
					 
  
																					
  

	iTest_ship = rand(5); // 7 �����
	if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship2");
	if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PLOT, NPChar), "ship2");
	if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WAR_TARTANE, NPChar), "ship2");

	iTest_ship = rand(5); // 7 �����
	if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship3");
	if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PLOT, NPChar), "ship3");
	if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WAR_TARTANE, NPChar), "ship3");

    if (sti(PChar.rank) > 1) // 6 �����
    {
		iTest_ship = rand(10);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BERMSLOOP, NPChar), "ship4");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_EMPRESS, NPChar), "ship4");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINK, NPChar), "ship4");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship4");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER_H, NPChar), "ship4");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SPEEDY, NPChar), "ship4");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_SLOOP, NPChar), "ship4");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEOTH_H, NPChar), "ship4");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship4");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP_B, NPChar), "ship4");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NEPTUNUS, NPChar), "ship4");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SOPHIE, NPChar), "ship4");

		iTest_ship = rand(10);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BERMSLOOP, NPChar), "ship5");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_EMPRESS, NPChar), "ship5");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINK, NPChar), "ship5");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship5");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER_H, NPChar), "ship5");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SPEEDY, NPChar), "ship5");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_SLOOP, NPChar), "ship5");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEOTH_H, NPChar), "ship5");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP, NPChar), "ship5");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SLOOP_B, NPChar), "ship5");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NEPTUNUS, NPChar), "ship5");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SOPHIE, NPChar), "ship5");
	}
	if (sti(PChar.rank) > 5) // 5 �����
    {
		iTest_ship = rand(20);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACCA, NPChar), "ship6");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARQUE, NPChar), "ship6");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_POSTILLIONEN, NPChar), "ship6");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER, NPChar), "ship6");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COLONIALSCHOONER, NPChar), "ship6");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBEC, NPChar), "ship6");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLEXEBEC, NPChar), "ship6");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBECLIGHT, NPChar), "ship6");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONERLIGHT, NPChar), "ship6");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_MIRAGE, NPChar), "ship6");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship6");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENSLAVER, NPChar), "ship6");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHNYAVA, NPChar), "ship6");
	
		iTest_ship = rand(20);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACCA, NPChar), "ship7");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARQUE, NPChar), "ship7");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_POSTILLIONEN, NPChar), "ship7");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER, NPChar), "ship7");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COLONIALSCHOONER, NPChar), "ship7");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBEC, NPChar), "ship7");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLEXEBEC, NPChar), "ship7");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBECLIGHT, NPChar), "ship7");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONERLIGHT, NPChar), "ship7");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_MIRAGE, NPChar), "ship7");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship7");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENSLAVER, NPChar), "ship7");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHNYAVA, NPChar), "ship7");
	
		iTest_ship = rand(20);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACCA, NPChar), "ship8");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARQUE, NPChar), "ship8");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_POSTILLIONEN, NPChar), "ship8");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONER, NPChar), "ship8");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COLONIALSCHOONER, NPChar), "ship8");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBEC, NPChar), "ship8");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLEXEBEC, NPChar), "ship8");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBECLIGHT, NPChar), "ship8");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SCHOONERLIGHT, NPChar), "ship8");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_MIRAGE, NPChar), "ship8");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE, NPChar), "ship8");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENSLAVER, NPChar), "ship8");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHNYAVA, NPChar), "ship8");
	}
	if (sti(PChar.rank) > 10) // 4 �����
    {
		iTest_ship = rand(30);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship9");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGHEAVY, NPChar), "ship9");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARKENTINE, NPChar), "ship9");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship9");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CASTELF, NPChar), "ship9");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DERFFLINGER, NPChar), "ship9");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_INTERCEPTOR, NPChar), "ship9");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship9");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PO_FLEUT50, NPChar), "ship9");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship9");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GREYHOUND, NPChar), "ship9");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTELIGHT, NPChar), "ship9");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PACKET_BRIG, NPChar), "ship9");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PDN, NPChar), "ship9");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENTERPRISE, NPChar), "ship9");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE_H, NPChar), "ship9");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship9");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATEMEDIUM, NPChar), "ship9");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_RAAFRIGATE, NPChar), "ship9");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL2, NPChar), "ship9");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWAR, NPChar), "ship9");
		if (iTest_ship == 22) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWARSAT, NPChar), "ship9");
		if (iTest_ship == 23) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEONTRADER, NPChar), "ship9");
		if (iTest_ship == 24) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LYDIA, NPChar), "ship9");
	
		iTest_ship = rand(30);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship10");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGHEAVY, NPChar), "ship10");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARKENTINE, NPChar), "ship10");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship10");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CASTELF, NPChar), "ship10");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DERFFLINGER, NPChar), "ship10");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_INTERCEPTOR, NPChar), "ship10");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship10");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PO_FLEUT50, NPChar), "ship10");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship10");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GREYHOUND, NPChar), "ship10");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTELIGHT, NPChar), "ship10");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PACKET_BRIG, NPChar), "ship10");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PDN, NPChar), "ship10");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENTERPRISE, NPChar), "ship10");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE_H, NPChar), "ship10");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship10");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATEMEDIUM, NPChar), "ship10");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_RAAFRIGATE, NPChar), "ship10");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL2, NPChar), "ship10");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWAR, NPChar), "ship10");
		if (iTest_ship == 22) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWARSAT, NPChar), "ship10");
		if (iTest_ship == 23) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEONTRADER, NPChar), "ship10");
		if (iTest_ship == 24) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LYDIA, NPChar), "ship10");
	
		iTest_ship = rand(30);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIG, NPChar), "ship11");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGHEAVY, NPChar), "ship11");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BARKENTINE, NPChar), "ship11");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BRIGANTINE, NPChar), "ship11");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CASTELF, NPChar), "ship11");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DERFFLINGER, NPChar), "ship11");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_INTERCEPTOR, NPChar), "ship11");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUT, NPChar), "ship11");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PO_FLEUT50, NPChar), "ship11");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_L, NPChar), "ship11");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GREYHOUND, NPChar), "ship11");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTELIGHT, NPChar), "ship11");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PACKET_BRIG, NPChar), "ship11");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PDN, NPChar), "ship11");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ENTERPRISE, NPChar), "ship11");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POLACRE_H, NPChar), "ship11");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL, NPChar), "ship11");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATEMEDIUM, NPChar), "ship11");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_RAAFRIGATE, NPChar), "ship11");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARAVEL2, NPChar), "ship11");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWAR, NPChar), "ship11");
		if (iTest_ship == 22) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FLEUTWARSAT, NPChar), "ship11");
		if (iTest_ship == 23) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEONTRADER, NPChar), "ship11");
		if (iTest_ship == 24) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LYDIA, NPChar), "ship11");
    }
    if (sti(PChar.rank) > 20) // 3 �����
    {
		iTest_ship = rand(50);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACE, NPChar), "ship12");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DUTCHPINNACE, NPChar), "ship12");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACELIGHT, NPChar), "ship12");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBEKVT, NPChar), "ship12");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FELIPE, NPChar), "ship12");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CRIMSONBLOOD, NPChar), "ship12");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship12");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_l, NPChar), "ship12");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLECORVETTE, NPChar), "ship12");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BLACKANGEL, NPChar), "ship12");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COASTALFRIGATE, NPChar), "ship12");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_FRIGATE, NPChar), "ship12");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_JAMAICASHIP, NPChar), "ship12");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_THEBLACKPEARL, NPChar), "ship12");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship12");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON1, NPChar), "ship12");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LA_MARIANNA, NPChar), "ship12");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PIRATFASTGAL, NPChar), "ship12");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_UNICORN, NPChar), "ship12");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_REVENGE, NPChar), "ship12");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINEFRIGATE, NPChar), "ship12");
		if (iTest_ship == 22) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LIGHTFRIGATE, NPChar), "ship12");
		if (iTest_ship == 23) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BOUSSOLE, NPChar), "ship12");
		if (iTest_ship == 24) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SURPRISE, NPChar), "ship12");
		if (iTest_ship == 25) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SALAMANDER, NPChar), "ship12");
		if (iTest_ship == 26) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_SAT, NPChar), "ship12");
		if (iTest_ship == 27) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLEFRIGATE, NPChar), "ship12");
		if (iTest_ship == 28) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NIGHTMARE, NPChar), "ship12");
		if (iTest_ship == 29) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_MORDAUNT, NPChar), "ship12");
		if (iTest_ship == 30) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE, NPChar), "ship12");
		if (iTest_ship == 31) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_AMSTERDAM, NPChar), "ship12");
		if (iTest_ship == 32) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARRACA, NPChar), "ship12");
	
		iTest_ship = rand(50);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACE, NPChar), "ship13");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DUTCHPINNACE, NPChar), "ship13");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PINNACELIGHT, NPChar), "ship13");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_XEBEKVT, NPChar), "ship13");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FELIPE, NPChar), "ship13");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CRIMSONBLOOD, NPChar), "ship13");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CORVETTE, NPChar), "ship13");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_l, NPChar), "ship13");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLECORVETTE, NPChar), "ship13");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BLACKANGEL, NPChar), "ship13");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COASTALFRIGATE, NPChar), "ship13");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_FRIGATE, NPChar), "ship13");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_JAMAICASHIP, NPChar), "ship13");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_THEBLACKPEARL, NPChar), "ship13");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON_H, NPChar), "ship13");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON1, NPChar), "ship13");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LA_MARIANNA, NPChar), "ship13");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_PIRATFASTGAL, NPChar), "ship13");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_UNICORN, NPChar), "ship13");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_REVENGE, NPChar), "ship13");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINEFRIGATE, NPChar), "ship13");
		if (iTest_ship == 22) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LIGHTFRIGATE, NPChar), "ship13");
		if (iTest_ship == 23) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BOUSSOLE, NPChar), "ship13");
		if (iTest_ship == 24) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SURPRISE, NPChar), "ship13");
		if (iTest_ship == 25) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SALAMANDER, NPChar), "ship13");
		if (iTest_ship == 26) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_SAT, NPChar), "ship13");
		if (iTest_ship == 27) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLEFRIGATE, NPChar), "ship13");
		if (iTest_ship == 28) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NIGHTMARE, NPChar), "ship13");
		if (iTest_ship == 29) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_MORDAUNT, NPChar), "ship13");
		if (iTest_ship == 30) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE, NPChar), "ship13");
		if (iTest_ship == 31) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_AMSTERDAM, NPChar), "ship13");
		if (iTest_ship == 32) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CARRACA, NPChar), "ship13");
    }
    
    if (sti(PChar.rank) > 25) // 2 �����
    {	
		iTest_ship = rand(100);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_GALEON50, NPChar), "ship14");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FASTFRIGATE, NPChar), "ship14");
 
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_ESSEX, NPChar), "ship14");
		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FRIGATE_H, NPChar), "ship14");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WARGALLEON2, NPChar), "ship14");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NL_PINNACEOFWAR47, NPChar), "ship14");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_HOLLGALEON_H, NPChar), "ship14");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FEARLESS, NPChar), "ship14");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINESHIP, NPChar), "ship14");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NL_FWZP, NPChar), "ship14");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_CONSTITUTION, NPChar), "ship14");
		if (iTest_ship == 12) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_OXFORD, NPChar), "ship14");
		if (iTest_ship == 13) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DUTCHLINESHIP, NPChar), "ship14");
		if (iTest_ship == 14) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_DUTCHSHIP, NPChar), "ship14");
		if (iTest_ship == 15) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_NL_CONVOISHIP, NPChar), "ship14");
		if (iTest_ship == 16) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_COURONNE, NPChar), "ship14");
		if (iTest_ship == 17) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_ALEXIS, NPChar), "ship14");
		if (iTest_ship == 18) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINESHIPHEAVY, NPChar), "ship14");
		if (iTest_ship == 19) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_WARSHIP, NPChar), "ship14");
		if (iTest_ship == 20) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_HEAVYWARSHIP, NPChar), "ship14");
		if (iTest_ship == 21) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_HEAVYLINESHIP, NPChar), "ship14");
    }
	
	if (sti(PChar.rank) > 30) // 1 �����
    {	
		iTest_ship = rand(150);
		if (iTest_ship == 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_POSEIDON, NPChar), "ship15");
		if (iTest_ship == 2) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_HMS_CENTURION, NPChar), "ship15");
		if (iTest_ship == 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_RESOLUTION, NPChar), "ship15");

		if (iTest_ship == 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_FR_SUPERIORWARSHIP1, NPChar), "ship15");
		if (iTest_ship == 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINK, NPChar), "ship15");
		if (iTest_ship == 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SUPERBE, NPChar), "ship15");
		if (iTest_ship == 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BATTLESHIP, NPChar), "ship15");
		if (iTest_ship == 8) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINK2, NPChar), "ship15");
		if (iTest_ship == 9) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_BELLONA, NPChar), "ship15");
		if (iTest_ship == 10) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LINEARSHIP, NPChar), "ship15");
		if (iTest_ship == 11) FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_SHARK, NPChar), "ship15");
    }
}

void FreeShipFromShipyard(ref NPChar)
{
	if (GetNpcQuestPastDayParam(NPChar, "shipyardDate") > (3 + rand(6)))
	{
        aref   arDest, arImt;
		string sAttr;
		int    iNum, i, iShip;
		makearef(arDest, NPChar.shipyard);
		iNum = GetAttributesNum(arDest);
		for (i = 0; i < iNum; i++)
		{
	    	arImt = GetAttributeN(arDest, i);
	    	iShip = sti(arImt.Type); //GetAttributeValue(arImt));
	    	DeleteAttribute(&RealShips[iShip], "StoreShip"); // ����� ������
	    }
        DeleteAttribute(NPChar, "shipyard");
	}
}

void RemoveCannonsFromBortShipyard(ref chr, string sBort)
{
//	int     maxQty = GetBortCannonsMaxQty(chr, sBort);
	int     maxQty = GetBortCannonsBaseQty(chr, sBort);
	int     i;
	string  attr;
	string  sBort_real = sBort;

		
	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";
	
	// ����� ���-�� ����� �� �����
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		// �������� �� 100%, �� �����, �� ��� ��
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;  
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0; 
	}
	
	RecalculateCargoLoad(chr);  // ��������, �� ����� �������
}

void RemoveAllCannonsShipyardShip(ref NPChar)
{
    RemoveCannonsFromBortShipyard(NPChar, "fcannon");
    RemoveCannonsFromBortShipyard(NPChar, "bcannon");
    RemoveCannonsFromBortShipyard(NPChar, "rcannon");
    RemoveCannonsFromBortShipyard(NPChar, "lcannon");
}

void FillShipParamShipyard(ref NPChar, int _iType, string _sShipNum)
{
    aref    arTo, arFrom;
    
	DeleteAttribute(NPChar, "ship");
    NPChar.Ship.Type = _iType;
    
	SetRandomNameToShip(NPChar);

    SetBaseShipData(NPChar);
    SetCrewQuantity(NPChar, 0);
    if (sti(NPChar.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
    {
    	NPChar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS8; // to_do ���������� �� ������� ��� ������ ������
    }
	RemoveAllCannonsShipyardShip(NPChar);	//����� ����� .. ���� ��������� ����� ����
    DeleteAttribute(NPChar, "Ship.Cargo");  //������ ����
    SetGoodsInitNull(NPChar);
    RecalculateCargoLoad(NPChar);
    
    FillShipyardShipBack(NPChar, _sShipNum);
}

void FillShipyardShip(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

	DeleteAttribute(NPChar, "ship");

    makearef(arFrom,   NPChar.shipyard.(_sShipNum));
    NPChar.Ship = "";
	makearef(arTo, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

void FillShipyardShipBack(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

  	DeleteAttribute(NPChar, "shipyard." + _sShipNum);
    NPChar.shipyard.(_sShipNum) = "";
    makearef(arTo,   NPChar.shipyard.(_sShipNum));
	makearef(arFrom, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

int GetSailsTuningPrice(ref _chr, ref _shipyard, float _rate)
{
	int st  = GetCharacterShipType(_chr);
	ref shref;
	
	if (st==SHIP_NOTUSED) return 0;
	shref = GetRealShip(st);

	return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price) * _rate / 10) * 10; // ������ 10
}

// Warship 26.07.09 ����� ����
// int st - GetCharacterShipType(_character)
// ref _shipyard - �������� �� ��������
int GetShipPriceByType(int st, ref _shipyard)
{
	if(st==SHIP_NOTUSED) return 0;
	ref shref = GetRealShip(st);

	return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price));
}

// ����� ������ ���� ������� ������� ��������� � ������ ���� ������ (��� �����)
int GetShipSellPrice(ref _chr, ref _shipyard)
{
	int st = GetCharacterShipType(_chr);
	int price = GetShipPriceByType(st, _shipyard);
	price = makeint(price - 1.5*GetSailRepairCost(st, GetSailDamagePercent(_chr), _shipyard));
	price = makeint(price - 1.5*GetHullRepairCost(st, GetHullDamagePercent(_chr), _shipyard));

	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE) + 0.001;

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
	if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

	price = price - price / (nCommerce*10.5);

	ref rRealShip = GetRealShip(st);

	if (sti(rRealShip.Stolen) == true) //�������� �� ����������
	{
    	price = makeint(price/4);
    }
    if (price < 0 && sti(_chr.Ship.Type) != SHIP_NOTUSED)
	{
	   price = 0;
	}

	return price;
}

// ����� ������ ���� ������� ������� ��������� � ������ ���� ������ (��� �����)
int GetShipBuyPrice(int iType, ref _shipyard)
{
	// boal ���� ������ �������� 22.01.2004 -->
	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
    if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

    return makeint(GetShipPriceByType(iType, _shipyard) + GetShipPriceByType(iType, _shipyard)/(nCommerce*10));
    // boal 22.01.2004 <--
}

int GetSailRepairCost(int shipType, int repairPercent, ref _shipyard)
{
	float fConstanta = 2.0;
	float fSkillDepend = fConstanta + (SKILL_TO_OLD*1.5) - (GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE));
	fSkillDepend *= 0.1 + (MOD_SKILL_ENEMY_RATE * 0.01);
	float SailRepairCoeff = 1.0 * fSkillDepend;
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) SailRepairCoeff *= 2;
	float scost = SailRepairCoeff * (shipPrice*SAIL_COST_PERCENT+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

int GetHullRepairCost(int shipType,int repairPercent, ref _shipyard)
{
	float fConstanta = 4.0;
	float fSkillDepend = fConstanta + (SKILL_TO_OLD*1.75) - (GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE));
	fSkillDepend *= 0.1 + (MOD_SKILL_ENEMY_RATE * 0.01);
	float HullRepairCoeff = 1.0 * fSkillDepend;
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) HullRepairCoeff *= 2;
	float scost = HullRepairCoeff * (shipPrice*HULL_COST_PERCENT+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

/* // ����� ����� �������
int GetHullRepairCost(int shipType,int repairPercent, ref _shipyard)
{
	float DifficultDepend = 1 * 0.1; 
	float fSkillDepend = 0.5 * abs(( GetCharacterSkill(pchar, SKILL_REPAIR) + GetCharacterSkill(pchar, SKILL_COMMERCE)) * 0.45 - SKILL_MAX_TOTAL); 
	float HullRepairCoeff = 1.0 + fSkillDepend * DifficultDepend;
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) HullRepairCoeff *= 3;
	float scost = HullRepairCoeff * (shipPrice*HULL_COST_PERCENT+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}
*/ // ����� ����� �������

int GetSailDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetSailPercent(_chr));
}

int GetHullDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetHullPercent(_chr));
}
///////////////////////////////////////////////////////////////   �����  <--
// ������ �� ���� �������
string GetShip_deck(ref chr, bool map2sea)
{
	string ret, add;
	int    iType = sti(chr.Ship.Type);
	if (map2sea)
	{
	    ret = "Ship_deck_";
	}
	else
	{
	    ret = "Deck_Near_Ship_";
	}
	add = "Low"; // ���� ��� ����
	if (iType != SHIP_NOTUSED)
	{
        ref rRealShip = GetRealShip(iType);
        
		add = rRealShip.DeckType;
	}
	
	return ret + add;
}

void MakeCloneShipDeck(ref chr, bool map2sea)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string locId, toLocId;
    
    locId = GetShip_deck(chr, map2sea);
    if (map2sea)
	{
	    toLocId = "Ship_deck";
	}
	else
	{
	    toLocId = "Deck_Near_Ship";
	}
	
	iOrg = FindLocation(locId);
	iClone = FindLocation(toLocId);

	if(iOrg < 0 || iClone < 0) {
        Trace("MakeCloneShipDeck error: iOrg " + iOrg + ", iClone " + iClone);
        return;
	}

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;
}

void MakeCloneFortBoarding(string fromLocId)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string toLocId;
    
    toLocId = "BOARDING_FORT";

	iOrg = FindLocation(fromLocId);
	iClone = FindLocation(toLocId);

	if(iOrg < 0 || iClone < 0) {
        Trace("MakeCloneFortBoarding error: iOrg " + iOrg + ", iClone " + iClone);
        return;
	}

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;
	
    rClone.type = "fort_attack";
	LAi_LocationFantomsGen(rClone, false);
	DeleteAttribute(rClone, "reload");
	//��� ������������� ������� ����� ���������. ��� ��� goto, soldiers � ��. ���� rld � ������.�������
	if (rClone.models.always.locators == "fortV_locators") 
	{
		rClone.models.always.locators = "fortV_lAttack";
		rClone.models.always.fortV = "fortV_attack";	
	}
	else
	{
		rClone.models.always.locators = "fortVRight_lAttack";
		rClone.models.always.fortV = "fortVRight_attack";
	}
	rClone.boarding.locatorNum = 15;
	rClone.boarding = "false";
	rClone.boarding.nextdeck = "Boarding_fortyard"; // Jason
	rClone.image = "loading\FortShturm_" + rand(2) + ".tga";
}

int GetPortManPrice(int Price, ref NPChar)
{
    if (!CheckAttribute(NPChar, "PortManPrice"))
	{
		NPChar.PortManPrice = (0.06 + frnd()*0.1);
	}
	return makeint(Price * stf(NPChar.PortManPrice) /10 ) * 10;
}

// ugeen --> �������������� ������ ������� ������� � ��
int GetPortManPriceExt(ref NPChar, ref chref)
{
	float fLeadership 	= 1.8 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; 	// ��������� ���������
	float fCommerce 	= 1.8 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; 	// ��������� ��������
	float fRelation 	= 1.0; 															// ���������  - ������ ����� ��� ���

	if(sti(NPChar.nation) == GetBaseHeroNation()) fRelation = 0.5; 						// ���� ����� ������- ������� ���� � ��� ����
	int price = makeint(100 * MOD_SKILL_ENEMY_RATE * 1.56 * sqr(6.7 - sti(RealShips[sti(chref.Ship.Type)].Class)) * (2 + 0.5 * GetNationRelation2MainCharacter(sti(NPChar.nation))) * fRelation * fLeadership * fCommerce);
	price = price + sti(chref.Ship.Crew.Quantity) * 10; // LEO: �� ������� ������� ������ �� 10 ������
	
	return price;
}
//<-- �������������� ������ ������� ������� � ��

// Warship 31.05.09 ��������� �� ������� ��������� ������������� ������
// ���� ������������ ����� Textures
bool SetShipSailsFromFile(ref _char, String _sailTexturePath)
{
	ref realShip;
	int shipType = sti(_char.Ship.Type);

	if(shipType == SHIP_NOTUSED) // ���� �� ������� ������
	{
		return false;
	}

	realShip = GetRealShip(shipType);
	
	realShip.EmblemedSails.normalTex = _sailTexturePath;
	
	return true;
}

string GetLocalShipAttrib(ref ship, string attrib) 
{
	if (CheckAttribute(ship, attrib)) return ship.(attrib);
	return ""; 
}

bool CheckShipAttribute(ref ship, string attrib)
{
	if(CheckAttribute(ship, attrib)) return true;
	return false;
}

string GetBaseShipParamFromType(int iType, string _param)
{
	object rBaseShip = GetShipByType(iType);
	return rBaseShip.(_param);
}

//Mett: --> ������� ��������� �������� �� ���
int GetShipPriceByTTH(int iType, ref rChar)
{
	ref rRealShip = GetRealShip(iType);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	int iSumm = 100;//������� ��������� sti(rBaseShip.price);
	int shipClass = sti(rRealShip.class);
 
	//������
	int hp_price = 1;
	switch(shipClass)
	{
		case 7: hp_price = 5; break;
		case 6: hp_price = 10; break;
		case 5: hp_price = 20; break;
		case 4: hp_price = 30; break;
		case 3: hp_price = 40; break;
		case 2: hp_price = 50; break;
		case 1: hp_price = 60; break;
	}
	int SummHP = sti(rRealShip.HP) * hp_price;
 
	//����
	int capacity_price = 1;
	switch(shipClass)
	{
		case 7: capacity_price = 5; break;
		case 6: capacity_price = 10; break;
		case 5: capacity_price = 20; break;
		case 4: capacity_price = 30; break;
		case 3: capacity_price = 40; break;
		case 2: capacity_price = 50; break;
		case 1: capacity_price = 60; break;
	}
	int SummCapacity = sti(rRealShip.Capacity) * capacity_price;
 
	//�������
	int crew_price = 1;
	switch(shipClass)
	{
		case 7: crew_price = 5; break;
		case 6: crew_price = 40; break;
		case 5: crew_price = 60; break;
		case 4: crew_price = 80; break;
		case 3: crew_price = 120; break;
		case 2: crew_price = 140; break;
		case 1: crew_price = 160; break;
	}
	int SummCrew = sti(rRealShip.MaxCrew) * crew_price;
 
	//������
	int caliber_price = 5000;
	switch(sti(rRealShip.MaxCaliber))
	{
		case 8: caliber_price = 5000; break;
		case 12: caliber_price = 10000; break;
		case 16: caliber_price = 30000; break;
		case 20: caliber_price = 45000; break;
		case 24: caliber_price = 60000; break;
		case 32: caliber_price = 120000; break;
		case 36: caliber_price = 200000; break;
		case 42: caliber_price = 300000; break;
		case 48: caliber_price = 600000; break;
	}
	int SummMaxCaliber = caliber_price;
	
	//���������� �����
	int cannon_price = 100;
	int iCannonsQuantity = 0;
	if(CheckAttribute(rRealShip, "CannonsQuantity"))
	{
		if(sti(rRealShip.CannonsQuantity) > 0)
		{
			if(CheckAttribute(rChar, "Ship.Cannons.Type"))
			{
				ref rCannon = GetCannonByType(sti(rChar.Ship.Cannons.Type));
				cannon_price = sti(rCannon.cost);
			}
			else
			{
				cannon_price = 1500; //������������� �������� ��� NullCharacter
			}
			iCannonsQuantity = sti(rRealShip.CannonsQuantity);
		}
		else
		{
			cannon_price = 0;
		}
	}
	else
	{
		trace("GetShipPriceByTTH: � " + rRealShip.BaseName + " ����������� ������� CannonsQuantity");
	}
	int SummCannons = iCannonsQuantity * cannon_price; //2
 
	//���������
	int was_price = 10;
	switch(shipClass)
	{
		case 7: was_price = 50; break;
		case 6: was_price = 1000; break;
		case 5: was_price = 2500; break;
		case 4: was_price = 20000; break;
		case 3: was_price = 50000; break;
		case 2: was_price = 100000; break;
		case 1: was_price = 200000; break;
	}
	int SummWAS = stf(rRealShip.WindAgainstSpeed) * was_price;
 
	//��������
	int speed_price = 10;
	switch(shipClass)
	{
		case 7: speed_price = 30; break;
		case 6: speed_price = 200; break;
		case 5: speed_price = 400; break;
		case 4: speed_price = 1000; break;
		case 3: speed_price = 5000; break;
		case 2: speed_price = 10000; break;
		case 1: speed_price = 20000; break;
	}
	int SummSpeed = stf(rRealShip.SpeedRate) * speed_price;
 
	//�������������
	int turn_price = 10;
	switch(shipClass)
	{
		case 7: turn_price = 10; break;
		case 6: turn_price = 50; break;
		case 5: turn_price = 200; break;
		case 4: turn_price = 500; break;
		case 3: turn_price = 3000; break;
		case 2: turn_price = 6000; break;
		case 1: turn_price = 12000; break;
	}
	int SummTurn = stf(rRealShip.TurnRate) * turn_price;
 
	iSumm += SummHP + SummCapacity + SummCrew + SummMaxCaliber + SummCannons + SummWAS + SummSpeed + SummTurn;
	
	// Log_TestInfo("SummHP " + SummHP); 
	// Log_TestInfo("SummCapacity " + SummCapacity); 
	// Log_TestInfo("SummCrew " + SummCrew); 
	// Log_TestInfo("SummMaxCaliber " + SummMaxCaliber); 
	// Log_TestInfo("SummCannons " + SummCannons); 
	// Log_TestInfo("SummWAS " + SummWAS); 
	// Log_TestInfo("SummSpeed " + SummSpeed); 
	// Log_TestInfo("SummTurn " + SummTurn); 
	// Log_TestInfo("iSumm " + iSumm);

	return iSumm;
}
//Mett: <-- ������� ��������� �������� �� ���