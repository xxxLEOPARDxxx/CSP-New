/// BOAL �����
#define sailCostPercent		10
#define hullCostPercent		20
#define paintCostPercent 0.75
int nCurScrollNum;
ref xi_refCharacter;
ref refNPCShipyard;
int shipIndex;

int nCurScrollOfficerNum;

string CurTable, CurRow;
int iSelected; // ������ � �������

string sMessageMode, sFrom_sea, sShipId;

float shipCostRate;
bool  bShipyardOnTop, bEmptySlot;

int RepairHull, RepairSail;
int timeHull, timeRig, timePaint;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIS_ALL		0		// Normal
#define FIS_1		1		// C1
#define FIS_2		2		// C2
#define FIS_3		3		// C3
#define FIS_4		4		// C4
#define FIS_5		5		// C5
#define FIS_6		6		// C6
#define FIS_7		7		// C7
int FIS_FilterState = FIS_ALL;
//// {*} BUHO END ADDITION

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleShipyard";

	xi_refCharacter = pchar;

    refNPCShipyard  = _shipyarder;
    SetShipyardStore(refNPCShipyard);

    shipCostRate = stf(refNPCShipyard.ShipCostRate);

    int iTest = FindColony(refNPCShipyard.City); // ����� ��������
    ref rColony;
    sFrom_sea = "";
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea; // ����� �����, � ���������� ����� ���, ������ ����� ����������
	}

	FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("ExitRepairMenu", "ExitRepairMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
    SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("BuyShipEvent","BuyShipEvent",0);
    //////////////////
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,40,366,275); // tak from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,246,361,1, 4);
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,46,134,161);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,187,147,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,166,147,1, 4);

    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
    SetNewGroupPicture("REPAIR_Money_PIC", "ICONS_CHAR", "Money");

    SetNewGroupPicture("REPAIR_Hull_PIC", "SHIP_STATE_ICONS", "Hull");
    SetNewGroupPicture("REPAIR_Sails_PIC", "SHIP_STATE_ICONS", "Sails");

    FillShipyardTable();

	SetCurrentNode("SHIPS_SCROLL");
	bShipyardOnTop = false;
	OnShipScrollChange();
	bEmptySlot = false;
	sMessageMode = "";
	SetButtionsAccess();
	timeHull = 0;
	timeRig = 0;
	timePaint = 0;
}

void ProcessExitCancel()
{
    // boal ����� �� ������ -->
    if (timeRig > 0 || timeHull > 0 || timePaint > 0)
    {
        LAi_Fade("", "");
        bQuestCheckProcessFreeze = true;
    	WaitDate("",0,0,0, 0, makeint( (timeHull/4.0 + timeRig/6.0 + timePaint/6.0) * 60.0));
    	RecalculateJumpTable();
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
	}
	if (sti(pchar.ship.type) == SHIP_NOTUSED) PChar.nation = GetBaseHeroNation();
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
    DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRepairMenu", "ExitRepairMenu");
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
        case "BUTTON_SELL":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;

		case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;
		//#20180922-01
		case "BUTTON_PAINT":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo2();
			}
		break;
		
		case "CLASS_ALL":
			if (comName == "click")ProcessFilter(); 
		break;

		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
			    MessageOk();
			}
		break;

		case "BUTTON_REPAIR":
			if (comName=="click" || comName=="activate")
			{
			    ShowRepairMenu();
			}
		break;

		case "REPAIR_LEFT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", -5);
			}
		break;

		case "REPAIR_RIGHT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", 5);
			}
		break;

		case "REPAIR_LEFT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", -5);
			}
		break;

		case "REPAIR_RIGHT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", 5);
			}
		break;

		case "REPAIR_OK":
			if (comName=="click" || comName=="activate")
			{
			    RepairOk();
			}
		break;

		case "REPAIR_ALL":
			if (comName=="click" || comName=="activate")
			{
			    RepairAll();
			}
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
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
				iShipType = sti(RealShips[iShipType].basetype);
				shipName = ShipsTypes[iShipType].Name;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+"����� "+ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str4 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).str3 = "#" + MakeMoneyShow(GetShipSellPrice(&characters[cn], refNPCShipyard), MONEY_SIGN,MONEY_DELIVER);
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup","SHIPS_"+shipName);
				m++;
			}
			else
			{
				attributeName = "pic" + (m+1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
				m++;
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
			m++;
		}
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
			NullSelectTable("TABLE_SHIPYARD"); // ������ �����
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
				// boal ����������� ������ -->
			    DelBakSkillAttr(xi_refCharacter);
			    ClearCharacterExpRate(xi_refCharacter);
			    RefreshCharacterSkillExpRate(xi_refCharacter);

			    SetEnergyToCharacter(xi_refCharacter);
			    // boal ����������� ������ <--
				OnShipScrollChange();
			}
			else
			{
				shipIndex= -1;
				bEmptySlot = true;
			}
			SetButtionsAccess();
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
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga");

		GameInterface.edit_box.str = _chr.ship.name;
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		SetShipOTHERTable("TABLE_OTHER", _chr);
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga");
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
	// ����� ��� �����, �� ������� ����� �� ����
	SetFormatedText("SHIP_RANK","");
	Table_Clear("TABLE_OTHER", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
    FillShipParam(xi_refCharacter);
}

void confirmShipChangeName()
{
	/*
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	SetCurrentNode("SHIP_INFO_TEXT");   */
}

void CheckForRename()
{
	/*if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}    */
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
	    rChr = refNPCShipyard;
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
			// ��������� �����
			bShowHint = false;
			ShowRPGHint();
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
		    	sText2 = "���: " + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "������: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "���������: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "����: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "�����������: "  + sti(GetCannonReloadTime(Cannon)) + " ���.";
		    	sText2 = sText2 + NewStr() + "���: "  + sti(Cannon.Weight) + " �.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = "������� ���� ��� Enter �� ����� ���� �������� �������� ���������� ������ �� ������.";
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "������� ����� ���� ������ ������������, �� ��� �������� �������� � ������� ����� �� ������� ���������� ��������, ��� ������ ���������� ������� ������. � ������� ����� ����� �� ���� �� 25% ������ ��������.";
				sText2 = sText2 + NewStr() + "������������ ���������� ������� � ������ ���������: " + GetMaxCrewQuantity(rChr);
			}
			// ������� �������
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// ����
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "������: " + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;
		case "TABLE_SHIPYARD" :
		    sHeader = XI_Convertstring("Shipyard");
			sText1  = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
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
    // �� ������ ����� �� �����

    // ����������
    if (CurTable == "TABLE_SHIPYARD")
	{
        FillShipyardShip(refNPCShipyard, GameInterface.(CurTable).(CurRow).sShipId);
		FillShipParam(refNPCShipyard);
		bShipyardOnTop = true;
		SetButtionsAccess();
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
	if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

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
	    rChr = refNPCShipyard;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	int idx = GetCannonGoodsIdxByType(sti(rChr.Ship.Cannons.Type));
	if (idx != -1)
	{
		int nShipType = GetCharacterShipType(rChr);
		ref refBaseShip = GetRealShip(nShipType);
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));

		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(rChr, "fcannon")) + "/" + refBaseShip.fcannon);
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(rChr, "bcannon")) + "/" + refBaseShip.bcannon);
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(rChr, "rcannon")) + "/" + refBaseShip.rcannon);
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(rChr, "lcannon")) + "/" + refBaseShip.lcannon);
		/// ����� GetCannonsNum(xi_refCharacter)
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

////////////// ���������������

int GetBuyPrice(int iType)
{
	// boal ���� ������ �������� 22.01.2004 -->
	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
    if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

    return makeint(GetShipPriceByType(iType) + GetShipPriceByType(iType)/(nCommerce*10));
    // boal 22.01.2004 <--
}

int GetSellPrice(ref _chr)
{
	int st = GetCharacterShipType(_chr);
	int price = GetShipPriceByType(st);
	price = makeint(price - 1.5*GetSailRepairCost(st, GetSailDamagePercent(_chr)));
	price = makeint(price - 1.5*GetHullRepairCost(st, GetHullDamagePercent(_chr)));

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
    	price = makeint(price/3);
    }
    if (price < 0 && sti(_chr.Ship.Type) != SHIP_NOTUSED)
	{
	   price = 0;
	}

	return price;
}

void FillShipyardTable()
{
    Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = "�������";
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = "�����";
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = "������";
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = "�������";
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = "����";
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;
	int k = 0;

	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	for (i = 0; i < iNum; i++)
	{
        row = "tr" + (k+1);

		arImt = GetAttributeN(arDest, i);
		//Log_Info(GetAttributeName(arImt));
		sAttr = GetAttributeName(arImt);
    	FillShipyardShip(refNPCShipyard, sAttr); // ������� � �������� ������� �� �����

    	iShip = sti(refNPCShipyard.Ship.Type);
    	refBaseShip = GetRealShip(iShip);
		sShip = refBaseShip.BaseName;
		
		GameInterface.TABLE_SHIPYARD.(row).sShipId = sAttr;
		
		int nClass = sti(refBaseShip.Class);
		if (FIS_FilterState != FIS_ALL)
		{
			if (sti(FIS_FilterState) != nClass)
			{
				DeleteAttribute(&GameInterface,"TABLE_SHIPYARD.row");
				continue;
			}
		}
		k++;
		
        GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\\ships\\" + sShip + ".tga.tx";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
    	GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "53,0";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + "\n\n"+refNPCShipyard.ship.name;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td1.scale = 0.82;
		GameInterface.TABLE_SHIPYARD.(row).td2.str = refBaseShip.Class;
		GameInterface.TABLE_SHIPYARD.(row).td3.str = sti(refBaseShip.CannonsQuantity);
		GameInterface.TABLE_SHIPYARD.(row).td4.str = GetCargoMaxSpace(refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td5.str = GetShipBuyPrice(iShip, refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td5.color = argb(255,255,228,80);
    }

	Table_UpdateWindow("TABLE_SHIPYARD");
}

void ProcessFilter()
{
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 1))
	{
		FIS_FilterState = FIS_ALL;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 2))
	{
		FIS_FilterState = FIS_7;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 3))
	{
		FIS_FilterState = FIS_6;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 4))
	{
		FIS_FilterState = FIS_5;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 5))
	{
		FIS_FilterState = FIS_4;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 6))
	{
		FIS_FilterState = FIS_3;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 7))
	{
		FIS_FilterState = FIS_2;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 8))
	{
		FIS_FilterState = FIS_1;
		FillShipyardTable();
		return;
	}
}

void SetButtionsAccess()
{
    SetSelectable("BUTTON_REPAIR", false);
    SetSelectable("BUTTON_SELL", true);
    SetSelectable("BUTTON_BUY", true);
	//#20180922-01
    SetSelectable("BUTTON_PAINT", true);

    if (bShipyardOnTop)
    {
        SetSelectable("BUTTON_REPAIR", false);
    	SetSelectable("BUTTON_SELL", false);
    	//#20180922-01
    	SetSelectable("BUTTON_PAINT", false);
    	if (shipIndex == -1)// �������� �� ����
    	{
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > sti(pchar.Money) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
   			if (bEmptySlot && sti(pchar.ship.type) == SHIP_NOTUSED)
   			{ // ������ ������ ������� ����������, ���� � �� ����
   			    SetSelectable("BUTTON_BUY", false);
   			}
    	}
    	else
    	{
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > (GetShipSellPrice(xi_refCharacter, refNPCShipyard) + sti(pchar.Money)) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
    	    if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
    	}
    }
    else
    {
        SetSelectable("BUTTON_BUY", false);

        if (GetHullPercent(xi_refCharacter) < 100 || GetSailPercent(xi_refCharacter) < 100)
        {
            SetSelectable("BUTTON_REPAIR", true);
        }
        if (shipIndex == -1)
        {
            SetSelectable("BUTTON_SELL", false);
            SetSelectable("BUTTON_REPAIR", false);
            //#20180922-01
            SetSelectable("BUTTON_PAINT", false);
        }
        else
        {

            if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
    	    {
    	        SetSelectable("BUTTON_SELL", false);
                //#20180922-01
                SetSelectable("BUTTON_PAINT", false);
    	    }
    	    else {
                //#20180922-01
                SetSelectable("BUTTON_PAINT", true);
    	    }
    	    if (xi_refCharacter.id == pchar.id && GetCompanionQuantity(pchar) > 1)
    	    { // ������ ������� ������� ��, ���� ���� ��� ����������
    	        SetSelectable("BUTTON_SELL", false);
    	    }
		}
    }
}

//////////////// ���������� ��������  //////////////////////////////////////////////////////////////////////
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
        // ���������� ������ ����, ��������, ���� ��� ��� �� ���, �� ��� ���� ��� ����
        sld = GetCharacter(iChar);
		
		if(sld.id != "pet_crab")
		{
			DeleteAttribute(sld, "ship");
			sld.ship.Type = SHIP_NOTUSED;

			// ������ ��������� -->
			CheckForReleaseOfficer(iChar);
			RemovePassenger(pchar, sld);
			// ������ ��������� <--
			SetCompanionIndex(pchar, -1, iChar);

			xi_refCharacter = sld;
			DoBuyShip();
		}
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
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // �� ���� �����, �� ��� ������������� � '����'
}
// ������ ������ ��� � ��, ���� ��� ����� ��� ����������
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

	if (bShipyardOnTop) // �� ������� ����� (������)
    {
        bBuy = true;
		if (shipIndex == -1)// �������� �� ����
    	{
    	    iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
    	}
    	else
    	{
            iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) - GetShipSellPrice(xi_refCharacter, refNPCShipyard);
    	}
    }
    else  // �������
    {
        bBuy = false;
        iMoney = GetShipSellPrice(xi_refCharacter, refNPCShipyard);
    }
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));

	if (bBuy)
	{
		if (iMoney < 0) add = "-";
		SetFormatedText("MSG_WINDOW_TEXT", "������ ������� �� " + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipBuy";
	}
	else
	{
	    SetFormatedText("MSG_WINDOW_TEXT", "������� ������� �� " + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipSell";
	}
	ShowMsgMenu();
}

//#20180922-01
void ShowMessageInfo2()
{
    ref rShip;
	bool bShipOK = false;
	float iMoney = 0.0;
	string sText;
    int nClass, nMinClass = 1;

	if(bShipyardOnTop) return;

    int iShip = sti(xi_refCharacter.ship.type);
	SetFormatedText("MSG_WINDOW_CAPTION", "��������");
    SetSelectable("MSG_OK", false);
    //Check ship and add msg can/can't do based on class, size, hull avail, etc.  If not, disable MSG_OK
    if (shipIndex != -1 && iShip != SHIP_NOTUSED)
    {
        rShip = GetRealShip(iShip);
        nClass = sti(rShip.Class);
        bShipOK = true;
		iMoney = rShip.price;
		iMoney /= 25;
    }
    if(bShipOK)
    {
        if(iMoney > sti(pchar.money)) {
            sText = "� ��� ������������ �������.";
        }
        else {
			sText = "� ��������� ���� ���� � ��������� ��������, ����� �������� ����� �������� �� ��� �������. ��� �������� ��� � " + makeint(iMoney) + " ��������. ��������?";
            SetSelectable("MSG_OK", true);
            
        }
    }
    else {
        sText = "� ���������, �� ���� ������������ ��� ������ ������ ������. ������� ���� ��������� ���������.";
    }
    SetFormatedText("MSG_WINDOW_TEXT", sText);
    sMessageMode = "ShipPaint";
	ShowMsgMenu();
}

void MessageOk()
{
	switch (sMessageMode)
	{
	    case "ShipSell" :
	        DoSellShip(true);
	        ExitMsgMenu();
	    break;

	    case "ShipBuy" :
	        DoBuyShipMain();
	    break;
		//#20180922-01
	    case "ShipPaint" :
	        DoPaintShipMain();
	    break;
	}
}

void DoSellShip(bool _refresh)
{
	ref chref = xi_refCharacter;
	if (shipIndex != -1 && sti(chref.ship.type) != SHIP_NOTUSED)
	{
    	int sellPrice = GetShipSellPrice(chref, refNPCShipyard);

    	AddMoneyToCharacter(pchar, sellPrice);
        AddCharacterExpToSkill(pchar, "Commerce", sellPrice / 1600.0);
        WaitDate("",0,0,0, 0, 10);
        Statistic_AddValue(pchar, "SellShip", 1);

    	DeleteAttribute(chref,"ship.sails");
    	DeleteAttribute(chref,"ship.blots");
        DeleteAttribute(chref,"ship.masts");

        // � ������ �� �������. -->
        AddShip2Shipyard(chref);
        // � ������ �� �������. <--
    	chref.ship.type = SHIP_NOTUSED;
    	// ����� ���� -->
    	if (_refresh)
		{
	    	if (sti(chref.index) != GetMainCharacterIndex())
	    	{
	            RemoveCharacterCompanion(pchar, chref);
				AddPassenger(pchar, chref, false);
				DelBakSkill();
				//navy --> ������, � �� ������ :)
				if (CheckAttribute(chref, "PGGAi") && CheckAttribute(chref, "PGGAi.OwnShip")) //�� ������� ������ ��, ������ ��.
				{
					chref.Payment = true;
					DeleteAttribute(chref, "PGGAi.OwnShip")
					Log_Info("������ �� ���� ������� ������ ���������.");
					AddMoneyToCharacter(pchar, -(sellPrice));
				}
				//navy <--
	    	}
	    	else
	    	{
          		pchar.location.from_sea = ""; // ��� ������� � �����
	    	}
    		RefreshShipLists();
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

	FillShipyardTable();
	bShipyardOnTop = false;
}

void AddShip2Shipyard(ref _chr)
{
    aref    arTo, arFrom;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;

    iShip = sti(_chr.ship.type);
    RealShips[iShip].StoreShip = true;  // ������ �� �����, ������ ��������� �������
    RealShips[iShip].Stolen = 0; // ��� �� ����������
	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	if (iNum == 0)
	{
	    sAttr = "ship1";
	}
	else
	{
	    arImt = GetAttributeN(arDest, iNum - 1);
	    sAttr = GetAttributeName(arImt) + "2";
	}
	makearef(arTo,   refNPCShipyard.ship);
	makearef(arFrom, _chr.Ship);
	CopyAttributes(arTo, arFrom);
	// ����� ������ � ����
	SetCrewQuantity(refNPCShipyard, 0);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");  //������ ����
	SetGoodsInitNull(refNPCShipyard);
    RecalculateCargoLoad(refNPCShipyard);

	FillShipyardShipBack(refNPCShipyard, sAttr);
	// ������� �������� ����� � ��������
	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
 	refNPCShipyard.BakCargo = "";
	makearef(arTo,   refNPCShipyard.BakCargo);
	makearef(arFrom, _chr.Ship.Cargo);
	CopyAttributes(arTo, arFrom);

	refNPCShipyard.BakCrew = "";
	makearef(arTo,   refNPCShipyard.BakCrew);
	makearef(arFrom, _chr.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void DoBuyShip()
{
    aref    arTo, arFrom;
	int     iBuyMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);

 	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
	DoSellShip(false);
	AddMoneyToCharacter(pchar, -iBuyMoney);

    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
    WaitDate("",0,0,0, 0, 10);
    Statistic_AddValue(pchar, "BuyShip", 1);

    FillShipyardShip(refNPCShipyard, sShipId); // ��, ��� ��������

    makearef(arTo,   xi_refCharacter.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCShipyard, "shipyard." + sShipId);

    int iShip = sti(xi_refCharacter.ship.type);
    DeleteAttribute(&RealShips[iShip], "StoreShip"); // ����� ������

	if (CheckAttribute(refNPCShipyard, "BakCargo")) // ���� ����� �������
	{
        DeleteAttribute(xi_refCharacter, "Ship.Cargo");
		DeleteAttribute(xi_refCharacter, "Ship.Crew");

		xi_refCharacter.Ship.Cargo = "";
		makearef(arTo,   xi_refCharacter.Ship.Cargo);
		makearef(arFrom, refNPCShipyard.BakCargo);
		CopyAttributes(arTo, arFrom);

        xi_refCharacter.Ship.Crew = "";
		makearef(arTo,   xi_refCharacter.Ship.Crew);
		makearef(arFrom, refNPCShipyard.BakCrew);
		CopyAttributes(arTo, arFrom);

		AddCharacterCrew(xi_refCharacter, 0); // �������� ��������
	    RecalculateCargoLoad(xi_refCharacter);
	}
	if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
	{
  		pchar.location.from_sea = sFrom_sea; // ������� � �����
	}
	DelBakSkill();
	RefreshShipLists();
}

void DoBuyShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
	    sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		if (!bEmptySlot) // ��� ������� ��� �� ��� �������
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

void DoPaintShip()
{
    ref rRealShip;
    int nHulls = 3;
    int nCurrHull = 1;
    int nRandHull;
    int iShip = sti(xi_refCharacter.ship.type);

    timePaint = 0;
	if (iShip != SHIP_NOTUSED)
	{
	    rRealShip = GetRealShip(iShip);	
		int iBuyMoney = rRealShip.price;
		iBuyMoney /= 25;
	    if(CheckAttribute(rRealShip, "BaseType")) {
           if(CheckAttribute(&ShipsTypes[sti(rRealShip.BaseType)], "hullNums"))
             nHulls = ShipsTypes[sti(rRealShip.BaseType)].hullNums;
        }
        if(nHulls < 2)
            return;
	    timePaint = timePaint + (8-GetCharacterShipClass(xi_refCharacter));
	    AddMoneyToCharacter(pchar, makeint(-iBuyMoney));
	    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
        if(CheckAttribute(rRealShip, "ship.upgrades.hull"))
            nCurrHull = sti(rRealShip.ship.upgrades.hull);
        nRandHull = nCurrHull;
        while(nCurrHull == nRandHull) {
            nRandHull = rand(nHulls-1) + 1;
        }
        rRealShip.ship.upgrades.hull = nRandHull;
	}
}

void DoPaintShipMain()
{
	if (shipIndex != -1 && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
	{
		DoPaintShip();
	}
	ExitMsgMenu();
}

int ScrollGetTexture()
{
	string sName = GetEventData();
	int iPicIndex = GetEventData();
	string sScrollID = GetEventData();

	//Boyer change #20170301-2 to new function as NFGetFile (NF) functions no longer exist in our source
	int iTexture = GetTexture(sName); //NFGetTexture(sScrollID, sName);

	return iTexture;
}

//////////////////// ������ ///////////////
void ExitRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", false);
	XI_WindowDisable("REPAIR_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", true);
	XI_WindowDisable("REPAIR_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

    SetRepairData();
	SetCurrentNode("REPAIR_CANCEL");
}

void SetRepairData()
{
	RepairSail = 0;
	RepairHull = 0;
 	RepairStatShow();
}

void RepairMoneyShow()
{
    int st = GetCharacterShipType(xi_refCharacter);

	SetFormatedText("REPAIR_WINDOW_TEXT", its(GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)));
}

void RepairStatShow()
{
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));

	SetFormatedText("REPAIR_QTY_H", (hp+RepairHull) + "%");
	SetFormatedText("REPAIR_QTY_S", (sp+RepairSail) + "%");
	RepairMoneyShow();
}

void ClickRepairArror(string _type, int add)
{
    int st = GetCharacterShipType(xi_refCharacter);
    int i;
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));

	if (_type == "hull")
	{
		if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull + add, refNPCShipyard)))
		    {
		        RepairHull = RepairHull + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetHullRepairCost(st, 1, refNPCShipyard); // �� ������� ������
		        RepairHull = RepairHull + i;
		    }
		    if ((RepairHull + hp) > 100)  RepairHull = 100 - hp;
	    }
	    else
	    {
            RepairHull = RepairHull + add;
			if (RepairHull < 0)  RepairHull = 0;
	    }
	}
	else
	{
	    if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail+ add, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)))
		    {
		        RepairSail = RepairSail + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetSailRepairCost(st, 1, refNPCShipyard); // �� ������� ������
		        RepairSail = RepairSail + i;
		    }
		    if ((RepairSail+sp) > 100)  RepairSail = 100 - sp;
	    }
	    else
	    {
            RepairSail = RepairSail + add;
			if (RepairSail < 0)  RepairSail = 0;
	    }
	}
	RepairStatShow();
}

void RepairOk()
{
    int st = GetCharacterShipType(xi_refCharacter);
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));
	float ret;

	if (RepairHull > 0)
	{
		timeHull = timeHull + RepairHull * (8-GetCharacterShipClass(xi_refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairHull * (7-GetCharacterShipClass(xi_refCharacter)) / 2.5));
		AddMoneyToCharacter(pchar, -GetHullRepairCost(st, RepairHull, refNPCShipyard));

		ret = ProcessHullRepair(xi_refCharacter, stf(RepairHull));
	}
	if (RepairSail > 0)
	{
	  	timeRig = timeRig + RepairSail * (8-GetCharacterShipClass(xi_refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairSail * (7-GetCharacterShipClass(xi_refCharacter)) / 3.5));
		AddMoneyToCharacter(pchar,-GetSailRepairCost(st, RepairSail, refNPCShipyard));

		ret = ProcessSailRepair(xi_refCharacter, stf(RepairSail));
	}
	if ((hp + RepairHull) >= 100)
	{
        xi_refCharacter.ship.hp = GetCharacterShipHP(xi_refCharacter);
		DeleteAttribute(xi_refCharacter, "ship.blots");
	}
	if ((sp+RepairSail) >= 100)
	{
		xi_refCharacter.ship.sp = GetCharacterShipSP(xi_refCharacter);
		DeleteAttribute(xi_refCharacter, "ship.sails");
		DeleteAttribute(xi_refCharacter, "ship.masts");
	}
	///
	ExitRepairMenu();
	st = sti(GameInterface.SHIPS_SCROLL.current);
	FillShipsScroll();
	GameInterface.SHIPS_SCROLL.current = st;
	nCurScrollNum = st;
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
	OnShipScrollChange();
	SetButtionsAccess();
}

void RepairAll()
{
    ClickRepairArror("sail", 100);
    ClickRepairArror("hull", 100);
}

void BuyShipEvent()
{
	if (GetSelectable("BUTTON_BUY"))
	{
	    ShowMessageInfo();
	}
}
