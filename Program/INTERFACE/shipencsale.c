//#20180914-02
#define sailCostPercent		10
#define hullCostPercent		20

int nCurScrollNum;
ref xi_refCharacter;
ref refNPCShipSell;
int shipIndex;
int nCurScrollOfficerNum;

string CurTable, CurRow;
int iSelected;

string sMessageMode, sFrom_sea, sShipId;

float shipCostRate;
bool  bShipyardOnTop, bEmptySlot;

void InitInterface_RI(string iniName, ref _shipowner, int nonUse )
{
	GameInterface.title = "titleShipSell";

	xi_refCharacter = pchar;

	refNPCShipSell  = _shipowner;
	if(!CheckAttribute(refNPCShipSell, "ShipCostRate"))
        refNPCShipSell.shipcostrate = 0.35 + frnd()*0.4; //Same value as LAi_utilites.c
	shipCostRate = stf(refNPCShipSell.ShipCostRate);

	int iTest = FindColony(refNPCShipSell.City);
	ref rColony;
	sFrom_sea = "";
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
    FillShipsScroll();

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
    SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    SetEventHandler("MouseRClickUp","HideInfoWindow",0);
    SetEventHandler("TableSelectChange", "TableSelectChange", 0);
    SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
    SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
    SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
    SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
    SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
    SetEventHandler("BuyShipEvent","BuyShipEvent",0);

    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,40,366,275); // take from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,246,361,1, 4);
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,46,134,161);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,187,147,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,166,147,1, 4);

    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

    FillShipSellTable();

    SetCurrentNode("SHIPS_SCROLL");
    bShipyardOnTop = false;
    OnShipScrollChange();
    bEmptySlot = false;
    sMessageMode = "";
    SetButtonsAccess();
}

void ProcessExitCancel()
{
    IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
    DelEventHandler("InterfaceBreak","ProcessExitCancel");
    DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
    DelEventHandler("MouseRClickUp","HideInfoWindow");
    DelEventHandler("TableSelectChange", "TableSelectChange");
    DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
    DelEventHandler("ShowOtherClick", "ShowOtherClick");
    DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
    DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
    DelEventHandler("acceptaddofficer","AcceptAddOfficer");
    DelEventHandler("BuyShipEvent","BuyShipEvent");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

    switch(nodName)
	{
        case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;
		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
			    MessageOk();
			}
		break;
	}
}

void FillShipsScroll()
{
    DeleteAttribute(&GameInterface, "SHIPS_SCROLL");
	nCurScrollNum = -1;
	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
	string attributeName;
	string shipName;
	int iShipType, cn;
	GameInterface.SHIPS_SCROLL.ImagesGroup.t0 = "BLANK_SHIP2";

	FillShipList("SHIPS_SCROLL.ImagesGroup", xi_refCharacter);
	GameInterface.SHIPS_SCROLL.BadTex1 = 0;
	GameInterface.SHIPS_SCROLL.BadPic1 = "Not Used2";

	int m = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				attributeName = "pic" + (m+1);
				//Boyer change #20170430-03
				//iShipType = sti(RealShips[iShipType].basetype);
				//shipName = ShipsTypes[iShipType].Name;

				//Boyer change #20170430-03
                ref rBaseShip = GetRealShip(iShipType);
                iShipType = rBaseShip.basetype;
                //#20170430-03 Companion ships are appended with a "1"
                if(strlen(rBaseShip.Name)>2)
                    shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                else
                    shipName = "";
                string shipClass = rBaseShip.Class;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				//Boyer change #20170430-03
				//GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+ xiStr("Class_") +ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+ xiStr("Class_") + shipClass;
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).str3 = "#" + MakeMoneyShow(0, MONEY_SIGN,MONEY_DELIVER);
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup","SHIPS_"+shipName);
			}
			else
			{
				attributeName = "pic" + (m+1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
			}
		}
		else
		{
		    attributeName = "pic" + (m+1);
			GameInterface.SHIPS_SCROLL.(attributeName).character = -1;
			GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
			GameInterface.SHIPS_SCROLL.(attributeName).str2 = "";
			GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
			GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
		}
		m++;
	}
	GameInterface.SHIPS_SCROLL.ListSize = m;
	//GameInterface.SHIPS_SCROLL.NotUsed = 5 - m + 1;
	GameInterface.SHIPS_SCROLL.NotUsed = 0;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();

    if (sNode == "PASSENGERSLIST" && sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if(sNode == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum || CurTable != "")
		{
            CurTable = "";
			NullSelectTable("TABLE_SHIPYARD");
			bShipyardOnTop = false;

			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				bEmptySlot = false;
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (sti(xi_refCharacter.ship.type) == SHIP_NOTUSED)
				{
					shipIndex= -1;
				}
				DelBakSkillAttr(xi_refCharacter);
			    ClearCharacterExpRate(xi_refCharacter);
			    RefreshCharacterSkillExpRate(xi_refCharacter);

			    SetEnergyToCharacter(xi_refCharacter);
			    OnShipScrollChange();
			}
			else
			{
				shipIndex= -1;
				bEmptySlot = true;
			}
			SetButtonsAccess();
		}
	}
}

void FillShipParam(ref _chr)
{
    int iShip = sti(_chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
        if (CheckAttribute(_chr, "Ship.Cargo.RecalculateCargoLoad") && sti(_chr.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(_chr);
			_chr.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\\ships\\" + sShip + ".tga.tx");

		GameInterface.edit_box.str = _chr.ship.name;
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		SetShipOTHERTable("TABLE_OTHER", _chr);
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\\blank_ship2.tga.tx");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetFormatedText("FRAME_INFO_CAPTION","");
		SetFormatedText("INFO_TEXT","");
	}
	Table_UpdateWindow("TABLE_OTHER");
}

void OnShipScrollChange()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	SetFormatedText("SHIP_RANK","");
	Table_Clear("TABLE_OTHER", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
    FillShipParam(xi_refCharacter);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;

	bool  bShowHint = true;

	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipSell;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1 || bShipyardOnTop)
			{
			    iShip = sti(rChr.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;
		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				//sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;
		case "MAIN_CHARACTER_PICTURE":
			bShowHint = false;
			ShowRPGHint();
		break;
		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
		    	sText2 = xiStr("MSG_Transfer_3") + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_4") + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_5")  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_6")  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_7")  + sti(GetCannonReloadTime(Cannon)) + xiStr("MSG_Transfer_8");
		    	sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_9")  + sti(Cannon.Weight) + xiStr("MSG_Transfer_10");

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = xiStr("MSG_SHP_1");
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = xiStr("MSG_Transfer_11");
				sText2 = sText2 + NewStr() + xiStr("MSG_Transfer_12") + GetMaxCrewQuantity(rChr);
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("MSG_Transfer_20") + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;
		case "TABLE_SHIPYARD" :
		    sHeader = XI_Convertstring("titleShipSell");
			sText1  = GetConvertStr("Shipsell_hint", "ShipsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_OTHER");
    if (CurTable == "TABLE_SHIPYARD")
	{
        FillShipParam(refNPCShipSell);
		bShipyardOnTop = true;
		SetButtonsAccess();
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("RPG_TABLE_SMALLSKILL", xi_refCharacter);
    SetOTHERMiniTable("RPG_TABLE_SMALLOTHER", xi_refCharacter);
    SetFormatedText("RPG_OFFICER_NAME", GetFullName(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_CANCEL");
}

void ShowOtherClick()
{
    //#20201017-01
    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}
//#20201017-01
void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}

void CannonsMenuRefresh()
{
	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipSell;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	int idx = GetCannonGoodsIdxByType(sti(rChr.Ship.Cannons.Type));
	if (idx != -1)
	{
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));

		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(rChr, "cannonf")));
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(rChr, "cannonb")));
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(rChr, "cannonr")));
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(rChr, "cannonl")));
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
		SetFormatedText("CANNONS_TEXT", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}
}

void ExitCannonsMenu()
{
	HideCannonsMenu();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

int GetShipPriceByType(int st)
{
	if(st==SHIP_NOTUSED) return 0;
	ref shref = GetRealShip(st);

	return makeint(shipCostRate * sti(shref.Price));
}

int GetBuyPrice(ref _chr)
{
	float nCommerce = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

    if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}
	//JA 5/6/11 Add relative cannon cost to ship price
	int iShipPrice = GetShipPriceByType(sti(_chr.Ship.Type)) + CannonRelCost(_chr) - GetHullRepairCost(sti(_chr.Ship.Type), 100);
	return makeint(iShipPrice + iShipPrice/(nCommerce*10));
}

int CannonRelCost(ref _chr)
{
	//Get cost of cannons on board compared to stock ship
	int st = GetCharacterShipType(_chr);
	ref rRealShip = GetRealShip(st);
	int iBaseType = sti(rRealShip.basetype);
	ref rBaseShip = &ShipsTypes[iBaseType];
	int iBaseCannonCost = GetCannonsSellCost(sti(rBaseShip.Cannon), sti(rBaseShip.CannonsQuantity));
	int iCurCannonCost =  GetCannonsSellCost(sti(_chr.Ship.Cannons.Type), GetCannonsNum(_chr));

	int iRelCost = iCurCannonCost - iBaseCannonCost;

	return iRelCost;
}

int GetCannonsSellCost(int iCannonType, int iCannonNum)
{
	if (iCannonType == CANNON_TYPE_NONECANNON || iCannonNum == 0) return 0;

	int iCannonGood = GetCannonGoodsIdxByType(iCannonType);
	int iStoreID = FindStore(refNPCShipSell.city)
	ref rStore = &Stores[iStoreID];

	return GetStoreGoodsPrice(rStore, iCannonGood, PRICE_TYPE_SELL, pchar, iCannonNum);
}

void FillShipSellTable()
{
    Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = xiStr("Ship");
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = xiStr("ShipClass");
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = xiStr("Cannons");
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = xiStr("Capacity");
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = xiStr("Cost");
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	int    i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;

	if(CheckAttribute(refNPCShipSell, "Ship.Type"))
	{
        row = "tr" + (i+1);

		iShip = sti(refNPCShipSell.Ship.Type);
    	refBaseShip = GetRealShip(iShip);
		sShip = refBaseShip.BaseName;
		//
		GameInterface.TABLE_SHIPYARD.(row).sShipId = "1";
        GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\ships\" + sShip + ".tga.tx";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
    	GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "53,0";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + "\n\n"+refNPCShipSell.ship.name;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td1.scale = 0.82;
		GameInterface.TABLE_SHIPYARD.(row).td2.str = refBaseShip.Class;
		GameInterface.TABLE_SHIPYARD.(row).td3.str = sti(refBaseShip.CannonsQuantity);
		GameInterface.TABLE_SHIPYARD.(row).td4.str = GetCargoMaxSpace(refNPCShipSell);
		GameInterface.TABLE_SHIPYARD.(row).td5.str = GetBuyPrice(refNPCShipSell);
		GameInterface.TABLE_SHIPYARD.(row).td5.color = argb(255,255,228,80);
    }
	Table_UpdateWindow("TABLE_SHIPYARD");
}

void SetButtonsAccess()
{
    //XI_DeleteNode("BUTTON_REPAIR");
    //XI_DeleteNode("BUTTON_SELL");
    SetNodeUsing("BUTTON_REPAIR", false);
    SetNodeUsing("BUTTON_SELL", false);
    SetNodeUsing("BUTTON_PAINT", false);
    SetSelectable("BUTTON_BUY", true);

    if (bShipyardOnTop)
    {
    	if (shipIndex == -1)
    	{
    	    if (GetBuyPrice(refNPCShipSell) > sti(pchar.Money) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
   			if (bEmptySlot && sti(pchar.ship.type) == SHIP_NOTUSED)
   			{
   			    SetSelectable("BUTTON_BUY", false);
   			}
    	}
    	else
    	{
    	    //Can't sell a ship already allocated
            SetSelectable("BUTTON_BUY", false);
    	}
    }
    else
    {
        SetSelectable("BUTTON_BUY", false);
    }
}

void ShipChangeCaptan()
{
	FillPassengerScroll();
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
    SetCurrentNode("PASSENGERSLIST");
	ProcessFrame();
	SetOfficersSkills();

	XI_WindowShow("OFFICERS_WINDOW", true);
	XI_WindowDisable("OFFICERS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
}

void AcceptAddOfficer()
{
	string  attributeName2 = "pic"+(nCurScrollOfficerNum+1);
    ref     sld;

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
        sld = GetCharacter(iChar);
		DeleteAttribute(sld, "ship");
		sld.ship.Type = SHIP_NOTUSED;

		CheckForReleaseOfficer(iChar);
		RemovePassenger(pchar, sld);
		SetCompanionIndex(pchar, -1, iChar);

		xi_refCharacter = sld;
		DoBuyShip();
	}
	ExitOfficerMenu();
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
	        return;
        }
	}
    Table_Clear("TABLE_SMALLSKILL", false, true, true);
    Table_Clear("TABLE_SMALLOTHER", false, true, true);
    SetFormatedText("OFFICER_NAME", "");
    SetSelectable("ACCEPT_ADD_OFFICER", false);
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	int _curCharIdx;
	ref _refCurChar;
	bool  ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = nListSize;

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";
	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		_curCharIdx = GetPassenger(pchar,i);

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
				GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
				GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2;
}

void DelBakSkill()
{
	DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);
    SetEnergyToCharacter(xi_refCharacter);

    DelBakSkillAttr(pchar);
    ClearCharacterExpRate(pchar);
    RefreshCharacterSkillExpRate(pchar);
    SetEnergyToCharacter(pchar);
}

void ShowMessageInfo()
{
	bool   bBuy;
	int    iMoney;
	string add = "";

	if (bShipyardOnTop)
    {
        bBuy = true;
		if (shipIndex == -1)
    	{
    	    iMoney = GetBuyPrice(refNPCShipSell);
    	}
    	else //Can't sell allocated ship
    	{
            iMoney = 0;
    	}
    }
    else
    {
        bBuy = false;
        iMoney = 0; //Can't sell allocated ship
    }
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));

	if (bBuy)
	{
		if (iMoney < 0) add = "-";
		SetFormatedText("MSG_WINDOW_TEXT", xiStr("MSG_SHP_2") + add + FormatMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipBuy";
	}
	ShowMsgMenu();
}

void MessageOk()
{
	switch (sMessageMode)
	{
	    case "ShipBuy" :
	        DoBuyShipMain();
	    break;
	}
}

void MoveCrewToFleet(ref fromChar)
{
	int i, cn, iFreeCrew, iNewCrew;
	ref rComp;
	iNewCrew = GetCrewQuantity(fromChar);
	if (iNewCrew > 0)
	{
		for(i=0; i<COMPANION_MAX && iNewCrew > 0; i++)
		{
			cn = GetCompanionIndex(GetMainCharacter(),i);
			rComp = GetCharacter(cn);

			if(cn>=0 && GetRemovable(&Characters[cn]) && rComp.id != fromChar.id)
			{
				iNewCrew = MoveCrew(rComp, fromChar, iNewCrew);
			}
		}
	}
}

void RefreshShipLists()
{
    xi_refCharacter = pchar;
	FillShipsScroll();
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
    SetCurrentNode("SHIPS_SCROLL");
	ProcessFrame();

	FillShipSellTable();
	bShipyardOnTop = false;
}

void DoBuyShip()
{
    aref    arTo, arFrom;
	int     iBuyMoney = GetBuyPrice(refNPCShipSell);

 	DeleteAttribute(refNPCShipSell, "BakCargo");
 	DeleteAttribute(refNPCShipSell, "BakCrew");
	AddMoneyToCharacter(pchar, -iBuyMoney);

	refNPCShipSell.Dialog.CurrentNode = "ShipSold";
    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
    Statistic_AddValue(pchar, "BuyShip", 1);

    makearef(arTo,   xi_refCharacter.ship);
	makearef(arFrom, refNPCShipSell.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCShipSell, "ship");

    int iShip = sti(xi_refCharacter.ship.type);

	if (CheckAttribute(refNPCShipSell, "BakCargo"))
	{
        DeleteAttribute(xi_refCharacter, "Ship.Cargo");
		DeleteAttribute(xi_refCharacter, "Ship.Crew");

		xi_refCharacter.Ship.Cargo = "";
		makearef(arTo,   xi_refCharacter.Ship.Cargo);
		makearef(arFrom, refNPCShipSell.BakCargo);
		CopyAttributes(arTo, arFrom);

        xi_refCharacter.Ship.Crew = "";
		makearef(arTo,   xi_refCharacter.Ship.Crew);
		makearef(arFrom, refNPCShipSell.BakCrew);
		CopyAttributes(arTo, arFrom);

		AddCharacterCrew(xi_refCharacter, 0);
	    RecalculateCargoLoad(xi_refCharacter);
	}
	if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
	{
  		pchar.location.from_sea = sFrom_sea;
	}
	DelBakSkill();
	RefreshShipLists();
}

void DoBuyShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
	    sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		if (!bEmptySlot)
		{
		    DoBuyShip();
		    ExitMsgMenu();
		}
		else
		{
		    ExitMsgMenu();
		    ShipChangeCaptan();
		}
	}
}

int GetSailDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetSailPercent(_chr));
}

int GetHullDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetHullPercent(_chr));
}

int GetSailRepairCost(int shipType, int repairPercent)
{
	int shipPrice = GetShipPriceByType(shipType);
	if(shipPrice<=0) return 0;
	float scost = (shipPrice*sailCostPercent+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

int GetHullRepairCost(int shipType,int repairPercent)
{
	int shipPrice = GetShipPriceByType(shipType);
	if(shipPrice<=0) return 0;
	float scost = (shipPrice*hullCostPercent+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

void BuyShipEvent()
{
	if (GetSelectable("BUTTON_BUY"))
	{
	    ShowMessageInfo();
	}
}

// PHILIPPE COULEUR DES VOILES (JA convert to COAS)
void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();
	if( sNod=="SHIP_WINDOW_EMBLEME" )
	{
		GameInterface.SHIP_WINDOW_EMBLEME.current = nIdx;
	}
}
