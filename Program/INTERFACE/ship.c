/// BOAL ���� �������
int nCurScrollNum;
ref xi_refCharacter;
int shipIndex;

string CurTable, CurRow;
int iSelected; // ������ � �������

// ��� �����������
int iShipQty, iUnits, iCurGoodsIdx;

string sMessageMode;
void InitInterface_R(string iniName, ref _chr) // _chr ����� ��� �������� ��������� ��� � ����
{
    InterfaceStack.SelectMenu_node = "LaunchShipState"; // ����������, ��� ����� �� �2
	GameInterface.title = "titleShip";

	xi_refCharacter = _chr;

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
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ShipChange", "ShipChange", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("ExitPartitionWindow", "ExitPartitionWindow", 0);

    XI_RegistryExitKey("IExit_F2");
    //////////////////
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,78,366,313); // tak from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,284,361,1, 4);
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,85,134,199);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,225,147,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,204,147,1, 4);

    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 657,214,789,1, 4);
    SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

    SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));

    GameInterface.TABLE_LIST.hr.td1.str = "������ � �����";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "���-��";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = "���";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "�����";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = "��� �����";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.select = 0;
	SetCurrentNode("SHIPS_SCROLL");
	OnShipScrollChange();
	sMessageMode = "";
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
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ShipChange", "ShipChange");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");

	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("ExitPartitionWindow", "ExitPartitionWindow");

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
	//#20200329-01
	if(bSeaActive) RefreshBattleInterface();
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		/////  ����� -->
        case "CANNONS_OK":
			if(comName=="click")
			{
				HideCannonsMenu(); // ��������� ��� ��� ���������
				OnShipScrollChange();
				Ship_ResearchCannons(xi_refCharacter);
			}
		break;

		case "CANNONS_REMOVE_ALL":
			if(comName=="click")
			{
			    CanonsRemoveAll();
			}
		break;

		case "CANNONS_SET_ALL":
			if(comName=="click")
			{
			    CanonsSetAll(xi_refCharacter);
			}
		break;

		case "CANNONS_LEFT_F":
			if(comName=="click")
			{
				ChangeCannonNum("cannonf", -1);
			}
		break;
		case "CANNONS_RIGHT_F":
			if(comName=="click")
			{
    			ChangeCannonNum("cannonf", 1);
			}
		break;

		case "CANNONS_LEFT_B":
			if(comName=="click")
			{
                ChangeCannonNum("cannonb", -1);
			}
		break;
		case "CANNONS_RIGHT_B":
			if(comName=="click")
			{
                ChangeCannonNum("cannonb", 1);
			}
		break;

		case "CANNONS_LEFT_R":
			if(comName=="click")
			{
                ChangeCannonNum("cannonr", -1);
			}
		break;
		case "CANNONS_RIGHT_R":
			if(comName=="click")
			{
                ChangeCannonNum("cannonr", 1);
			}
		break;

		case "CANNONS_LEFT_L":
			if(comName=="click")
			{
                ChangeCannonNum("cannonl", -1);
			}
		break;
		case "CANNONS_RIGHT_L":
			if(comName=="click")
			{
                ChangeCannonNum("cannonl", 1);
			}
		break;
		/////  ����� <--
		case "CREW_MORALE_BUTTON":
			if(comName=="click")
			{
			    ShowMoraleMessage();
			}
		break;

		case "PARTITION_OK":
			if(comName=="click")
			{
			    DoPartitionPay();
			}
		break;
		
		case "CREW_PARTITION":
			if(comName=="click")
			{
			    ShowPartitionWindow();
			}
		break;

		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;
		// ���� 07.07.07
		case "QTY_BOMB_BUTTON":
			if(comName=="click")
			{
			    SetMineFree(xi_refCharacter, 1);
			    iShipQty = GetCargoGoods(xi_refCharacter, GOOD_POWDER);
			    OnShipScrollChange();
			}
		break;
		/////////////////////////////////////////////
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
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
		cn = GetCompanionIndex(xi_refCharacter, i);
		if(cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				attributeName = "pic" + (m+1);
				//Boyer change #20170430-03
				//iShipType = sti(RealShips[iShipType].basetype);
				//shipName = ShipsTypes[iShipType].Name;

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
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+"����� "+ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = shipName;
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
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	GameInterface.SHIPS_SCROLL.NotUsed = COMPANION_MAX - m + 1;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();
	if(sNode == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum)
		{
			DeleteAttribute(&GameInterface, "TABLE_LIST.BackUp");
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
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
			}
			return;
		}
	}
}
void OnShipScrollChange()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	// ����� ��� �����, �� ������� ����� �� ����
	SetFormatedText("SHIP_RANK","");
	SetFormatedText("CREW_QTY","");
	SetFormatedText("FOOD", "");
	SetFormatedText("FOOD_SHIP", "");
	SetFormatedText("MONEY_SHIP", "");
	SetFormatedText("CREW_MORALE_TEXT", "");
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(1));
	SetSelectable("CREW_MORALE_BUTTON", false);
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_OTHER", false, true, false);
	Table_Clear("TABLE_CREW", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	int iShip = sti(xi_refCharacter.ship.type);

	SetNodeUsing("CREW_PARTITION", false);
	if (iShip != SHIP_NOTUSED)
	{
        xi_refCharacter.ship.sp = CalculateShipSP(xi_refCharacter);
		// ����������� ������ -->
	    DelBakSkillAttr(xi_refCharacter);
	    ClearCharacterExpRate(xi_refCharacter);
	    RefreshCharacterSkillExpRate(xi_refCharacter);
	    // ����������� ������ <--

		if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(xi_refCharacter);
			xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga.tx");

		GameInterface.edit_box.str = xi_refCharacter.ship.name;
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		FillGoodsTable();

		SetShipOTHERTable("TABLE_OTHER", xi_refCharacter);
		// ��� -->
		int iColor, iFood;
		string sText;
		// � �������
		if (GetCompanionQuantity(pchar) > 1) // ������ 1 ��
		{
			sText = "��������� � ������� �� ";
			iFood = CalculateFood();
			sText = sText + FindRussianDaysString(iFood);
			SetFormatedText("FOOD", sText);
			if(iFood >= 5)
			{
				iColor = argb(255,255,255,192);
			}
			if(iFood > 10)
			{
				iColor = argb(255,192,255,192);
			}
			if(iFood < 5)
			{
				iColor = argb(255,255,192,192);
			}
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FOOD", 8,-1,iColor);
		}
		// ��� -->
		// �� ����� �������
		SetFoodShipInfo(xi_refCharacter, "FOOD_SHIP");
		// ��� <--
		if (GetRemovable(xi_refCharacter)) // ������� ������ �����, � �� ����� �������������� �������!!!
		{
		    // ��� ������� ������� ��������� ����� � ������� ��������
		    SetFormatedText("MONEY_SHIP", "���������� �������: " + NewStr() + FindRussianMoneyString(GetSalaryForShip(xi_refCharacter)));
		}
		SetFormatedText("CREW_QTY", ""+GetCrewQuantity(xi_refCharacter));
		if (GetCrewQuantity(xi_refCharacter) > GetOptCrewQuantity(xi_refCharacter) || GetCrewQuantity(xi_refCharacter) < GetMinCrewQuantity(xi_refCharacter))
		{
			iColor = argb(255,255,64,64);
		}
		else
		{
			iColor = argb(255,255,255,255);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
		SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(xi_refCharacter.ship.crew.morale)));
		SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(xi_refCharacter.Ship.crew.morale))));
		if (sti(xi_refCharacter.Ship.crew.morale) < MORALE_MAX && GetCrewQuantity(xi_refCharacter) > 0)
		{
			SetSelectable("CREW_MORALE_BUTTON", true);
		}
		SetNodeUsing("BAR_Sailors", true);
		SetNodeUsing("BAR_Cannoners", true);
		SetNodeUsing("BAR_Soldiers", true);
		SetNodeUsing("BAR_CrewMoral", true);
		SetCrewExpTable(xi_refCharacter, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");
		//BAR_CrewMoral
		GameInterface.StatusLine.BAR_CrewMoral.Max   = 100;
    	GameInterface.StatusLine.BAR_CrewMoral.Min   = 0;
    	GameInterface.StatusLine.BAR_CrewMoral.Value = sti(xi_refCharacter.Ship.crew.morale);
    	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral", 0);
    	if (xi_refCharacter.id == pchar.id)
    	{
    		SetNodeUsing("CREW_PARTITION", true);
    	}
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga.tx");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetNodeUsing("BAR_Sailors", false);
		SetNodeUsing("BAR_Cannoners", false);
		SetNodeUsing("BAR_Soldiers", false);
		SetNodeUsing("BAR_CrewMoral", false);
	}
	Table_UpdateWindow("TABLE_LIST");
	Table_UpdateWindow("TABLE_OTHER");
	Table_UpdateWindow("TABLE_CREW");
}

void confirmShipChangeName()
{
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	//SetCurrentNode("SHIP_INFO_TEXT");
	SetCurrentNode("SHIPS_SCROLL");
}

void CheckForRename()
{
	if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}
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
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break;

		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break;

		case "MAIN_CHARACTER_PICTURE":
			// ��������� �����
			bShowHint = false;
			ShowRPGHint();
		break;

		case "TABLE_LIST":
			sHeader = XI_Convertstring("Goods");
			sText1  = GetRPGText("GoodsCargo_hint");
		break;

		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(xi_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(xi_refCharacter.Ship.Cannons.Type));
		    	sText2 = "���: " + XI_ConvertString(GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "������: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "���������: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "����: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "�����������: "  + sti(GetCannonReloadTime(Cannon)) + " ���.";
		    	sText2 = sText2 + NewStr() + "���: "  + sti(Cannon.Weight) + " �.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type));

				sText3 = "������� ���� ��� Enter �� ����� ���� �������� ��������� ���������� ������ �� ������, ��� �� ����� ����� ��� ���������� �� ������� � �����.";
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "������� ����� ���� ������ ������������, �� ��� �������� �������� � ������� ����� �� ������� ���������� ��������, ��� ������ ���������� ������� ������. � ������� ����� ����� �� ���� �� 25% ������ ��������."; 
				sText2 = sText2 + NewStr() + "������������ ���������� ������� � ������ ���������: " + GetMaxCrewQuantity(xi_refCharacter);
			}
			// ������� �������
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
                if (GetHullPercent(xi_refCharacter)<100.0 )
                {
					sText2 = "������ " + FloatToString(GetHullRepairDay(xi_refCharacter, false),2) + " % � ����, ������ " + makeint(GetHullRepairDay(xi_refCharacter, true)) + " ��. �����";
				}
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(xi_refCharacter), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
                if (GetSailPercent(xi_refCharacter)<100.0 )
                {
					sText2 = "������ " + FloatToString(GetSailRepairDay(xi_refCharacter, false),2) + " % � ����, ������ " + makeint(GetSailRepairDay(xi_refCharacter, true))+ " ��. ��������";
				}
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(xi_refCharacter), 1) + " %";
			}
			// ����
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "������: " + FloatToString((stf(GetCargoLoad(xi_refCharacter))  /  stf(GetCargoMaxSpace(xi_refCharacter))) * 100.0, 1)+ " %";
			}
		break;
		case "CREW_PARTITION":
			sHeader = XI_Convertstring("PartitionCaption");
			sText1  = GetRPGText("Partition_hint");
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
    NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_OTHER");
    NullSelectTable("TABLE_CREW");
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
	SetSPECIALMiniTable("TABLE_SMALLSKILL", xi_refCharacter);
    SetOTHERMiniTable("TABLE_SMALLOTHER", xi_refCharacter);
    SetFormatedText("OFFICER_NAME", GetFullName(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void FillGoodsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
	}
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		qty = GetCargoGoods(xi_refCharacter, i);
		if (qty <= 0) continue; // ������ �� ����

		GameInterface.TABLE_LIST.(row).index = i;

		GameInterface.TABLE_LIST.(row).td2.str = qty;
		GameInterface.TABLE_LIST.(row).td3.str = GetGoodWeightByType(i, qty);
		GameInterface.TABLE_LIST.(row).td4.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td5.str = Goods[i].Weight;

        GameInterface.TABLE_LIST.(row).td1.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td1.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td1.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td1.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td1.textoffset = "10,0";
		GameInterface.TABLE_LIST.(row).td1.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).td1.scale = 0.88;
		n++;
	}
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ShowItemInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // ��� ������ ������
	{
	    ShowGoodsInfo(sti(GameInterface.(CurTable).(CurRow).index));
		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", true);
		SetCurrentNode("QTY_CANCEL_BUTTON");
		if (GetRemovable(xi_refCharacter))
		{
		    SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
		    SetSelectable("QTY_OK_BUTTON", false);
		}
		// ����
	    if (sti(GameInterface.(CurTable).(CurRow).index) == GOOD_POWDER)
	    {
	        SetNodeUsing("QTY_BOMB_BUTTON", true);
	        if (bSeaActive && !bAbordageStarted && GetRemovable(xi_refCharacter))
	        {
	            SetSelectable("QTY_BOMB_BUTTON", true);
	        }
	        else
	        {
	            SetSelectable("QTY_BOMB_BUTTON", false);
	        }
		}
		else
		{
		    SetNodeUsing("QTY_BOMB_BUTTON", false);
		}
	}
}

void GoodsExitCancel()
{

	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_LIST");
	// ����������� ����� ��������� �� ����
	if (iShipQty != GetCargoGoods(xi_refCharacter, iCurGoodsIdx))
	{
		SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty); // ������ �������
		OnShipScrollChange();
	}
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", ����� " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	//fWeight = stf(Goods[iGoodIndex].weight);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}

    SetFormatedText("QTY_TypeOperation", "��������?");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);

	iShipQty = GetCargoGoods(xi_refCharacter, iGoodIndex);
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty))
    SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iGoodIndex, iShipQty)));

    SetFormatedText("QTY_INFO_STORE_PRICE", "��� � �����");
    SetFormatedText("QTY_INFO_SHIP_PRICE",  "���������� � �����");
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();

	nTradeQuantity = sti(GameInterface.qty_edit.str);

    SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);

    if (!GetRemovable(xi_refCharacter)) return;
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // �������� ������� � ����
		iShipQty = GetCargoGoods(xi_refCharacter, iCurGoodsIdx);
	}
	GoodsExitCancel();

	//SetShipOTHERTable("TABLE_OTHER", xi_refCharacter);
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	GameInterface.qty_edit.str = abs(sti(GameInterface.qty_edit.str));  // ���������� � �����

	string GoodName = goods[iCurGoodsIdx].name;

    // �������� �� ����� ��������� -->
    if (sti(GameInterface.qty_edit.str) > iShipQty)
    {
        GameInterface.qty_edit.str = iShipQty;
    }
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty - sti(GameInterface.qty_edit.str)))
	SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iCurGoodsIdx, (iShipQty - sti(GameInterface.qty_edit.str)))));
	// ����������� ����� � �����
	iWeight = sti(GameInterface.qty_edit.str);
	SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(xi_refCharacter, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
	///iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
	//GameInterface.TABLE_OTHER.tr6.td3.str = (GetCargoLoad(xi_refCharacter) - iWeight) + " / " + GetCargoMaxSpace(xi_refCharacter);
	//Table_UpdateWindow("TABLE_OTHER");
}

void REMOVE_ALL_BUTTON()  // ������� ���
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = iShipQty;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // ������ ���
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // �������
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // ������
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
	if (sti(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void DropGoodsToSeaFromInterface(int iGoodIndex, int iQuantity)
{
	ref rGood;
	string sGood;

	sGood = Goods[iGoodIndex].name;

	if (CheckAttribute(xi_refCharacter, "Ship.Cargo.Goods."+sGood))
	{
		RemoveCharacterGoods(xi_refCharacter, iGoodIndex, iQuantity);
		if (bSeaActive && !bAbordageStarted)  // ����, �� �� �����
		{
			iQuantity = iQuantity / sti(Goods[iGoodIndex].Units);

			int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}

			RecalculateCargoLoad(xi_refCharacter);
	        xi_refCharacter.Tmp.SpeedRecall = 0; // ���� ������������� �������� � ������

			if (CheckAttribute(&Goods[iGoodIndex], "Swim"))
			{
				float fTime = stf(Goods[iGoodIndex].Swim.Time);
				string sModel = Goods[iGoodIndex].Swim.Model;

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(xi_refCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			PlaySound("Ships\jakor_002.wav");
		}
	}
}

void ShipChange()
{
	bool bOk;
	if (xi_refCharacter.id != pchar.id && sti(pchar.ship.type) != SHIP_NOTUSED)
	{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("companionship"));
		SetFormatedText("REMOVE_WINDOW_TEXT", "������� � ����� ������ ����� ���������?");
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		bOk = !bSeaActive && LAi_grp_alarmactive;
		if (bDisableMapEnter || bOk || chrDisableReloadToLocation)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "�� ����� ��� ����� � ��������� �������� ������ ���� � �����.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		if (bSeaActive && GetShipEscape())
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "������������� ����������� '�������� �� ������' ��������� ������������ � ��������� � ���. ����������?");
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		}
		if (!GetRemovable(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "����� � �������� ����� ���������� ����������.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		if (sti(pchar.ship.type) == SHIP_NOTUSED)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "����� ����������. � ����� ��� �������.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		sMessageMode = "ShipChange";
		ShowShipChangeMenu();
	}
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("REMOVE_CANCEL_OFFICER");
}

bool GetShipEscape()
{
    if (CheckCharacterPerk(PChar, "ShipEscape") && GetHullPercent(PChar) <= 15.0)
    {
        return true;
    }
    return false;
}

void ShowOtherClick()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".UserData.ID") && GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

void GoToShipChange()
{
	if (sMessageMode == "MoraleMessage") // ������
	{
		AddMoneyToCharacter(pchar, -GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		Statistic_AddValue(pchar, "PartitionPay", GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		AddCrewMorale(xi_refCharacter, 10);
		ExitShipChangeMenu();
		OnShipScrollChange();
	}
	if (sMessageMode == "ShipChange") // ����� � ��������
	{
		pchar.TransferChar = xi_refCharacter.index;
		InterfaceStates.ReloadMenuExit = true;
		IDoExit(RC_INTERFACE_ANY_EXIT);
		PostEvent("LaunchIAfterFrame",1,"sl", "TransferMain", 2);
	}
}

void ShowMoraleMessage()
{
	int  sum = GetCharacterRaiseCrewMoraleMoney(xi_refCharacter);
	SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("RaiseMorale"));
	SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("RaiseMoraleMoney") + FindRussianMoneyString(sum));

	if (sum <= sti(pchar.money))
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
	}
	else
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", false);
	}
	sMessageMode = "MoraleMessage";
	ShowShipChangeMenu();
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

    SetBackupCannons(); // ���������, ��� ������

    bool bOk  = !bSeaActive && LAi_grp_alarmactive;
    bool bOk2 = bAbordageStarted && !bCabinStarted; // � �������� �� ���� �����
	if (bDisableMapEnter || bOk || bOk2)
    { // ���� ���, ������ ����� ������
    	SetSelectable("CANNONS_OK", false);
	}
	else
	{
		SetSelectable("CANNONS_OK", true);
	}
	if (!GetRemovable(xi_refCharacter))
	{
		SetSelectable("CANNONS_OK", false);
	}
    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}
void CannonsMenuRefresh()
{
	int idx = GetCannonGoodsIdxByType(sti(xi_refCharacter.Ship.Cannons.Type));
	if (idx != -1)
	{
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));

		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(xi_refCharacter, "cannonf")));
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(xi_refCharacter, "cannonb")));
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(xi_refCharacter, "cannonr")));
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(xi_refCharacter, "cannonl")));
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
	FillCannonsTable();
}
void ExitCannonsMenu()
{
	HideCannonsMenu();

	GetBackupCannons(); // ������
	OnShipScrollChange();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

/// ���������� ������ �� ����� (������ ��������� ������ ���� ����� - ������ � ������)
void SetCannonsToBort(ref chr, string sBort, int iQty)
{
	int     curQty = GetBortCannonsQty(chr, sBort);
	int     maxQty = GetBortCannonsMaxQty(chr, sBort);
	int     i, delta;
	string  attr;
	int     center, left, right; // �������� ������ ��� �������������
	bool    bLeft; // ����������� ����
	string  sBort_real;
		
	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";

	if (iQty > maxQty) iQty = maxQty;
	if (iQty < 0) iQty = 0;

	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    delta = iQty - curQty;
    if (delta > 0)
    {
    	if (GetCargoGoods(chr, idx) < delta) iQty = curQty + GetCargoGoods(chr, idx);
    }
	if (iQty > curQty)
	{ // ������� �� ������
		RemoveCharacterGoodsSelf(chr, idx, (iQty - curQty));
	}
	else
	{
		if (iQty < curQty)
		{// ������ �� �����
			SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // ���� �����, �� �������� ����� ����, �  AddCharacterGoodsSimple ����� ��������
		}
	}
	// ����� ����� ����� �� ����� � ������������ ������ �� ������ (��� ��� �� ������ �� ������� �� ����, ������, ��� ������)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // �������� �� 100%, �� �����, �� ��� ��
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0; // �������� �� 100%, �� �����, �� ��� ��
	}
	// ������������
	if (iQty > 0)
	{
		center = makeint(maxQty / 2); // ������������� �������
		left   = center - 1;
		right  = center;
		i = 0; // ������� ������������ ���
		bLeft = true;
		while (i < iQty)
		{
			if (bLeft)
			{
				if (left >= 0)
				{
					attr = "c" + left;
					left--;
				}
				else
				{
					attr = "c" + right;
					right++;
				}
				if (right < maxQty) bLeft = false;
			}
			else
			{
				if (right < maxQty)
				{
					attr = "c" + right;
					right++;
				}
				else
				{
					attr = "c" + left;
					left--;
				}
				if (left >= 0) bLeft = true;
			}
			chr.Ship.Cannons.borts.(sBort).damages.(attr) = 0.0; // �����, �� �����
			chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 0.0; // �����, �� �����
			i++;
		}
	}
	RecalculateCargoLoad(chr);  // ��������, �� ����� �������
}

void CanonsRemoveAll()
{
    SetCannonsToBort(xi_refCharacter, "cannonf", 0);
    SetCannonsToBort(xi_refCharacter, "cannonb", 0);
    SetCannonsToBort(xi_refCharacter, "cannonr", 0);
    SetCannonsToBort(xi_refCharacter, "cannonl", 0);
    OnShipScrollChange();
    CannonsMenuRefresh();
}

// ����� ��������, �� ����������
void SetBackupCannons()
{
	aref    arTo, arFrom;
	NullCharacter.ShipBak.Cannons = "";
	NullCharacter.ShipBak.Cargo   = "";

	makearef(arTo,   NullCharacter.ShipBak.Cannons);
	makearef(arFrom, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);

	makearef(arTo,   NullCharacter.ShipBak.Cargo);
	makearef(arFrom, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void GetBackupCannons()
{
	aref    arTo, arFrom;

	makearef(arFrom,   NullCharacter.ShipBak.Cannons);
	makearef(arTo, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);

	makearef(arFrom,   NullCharacter.ShipBak.Cargo);
	makearef(arTo, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void CanonsSetAll(ref chr)
{
    if (GetCannonQuantity(chr) <= 0) return;
    //if (GetCannonQuantity(chr) <= GetCannonsNum(chr)) return;
	// ������� ��� ������
    if (GetCannonsNum(chr) > 0)
    {
		SetCannonsToBort(chr, "cannonf", 0);
	    SetCannonsToBort(chr, "cannonb", 0);
	    SetCannonsToBort(chr, "cannonr", 0);
	    SetCannonsToBort(chr, "cannonl", 0);
    }
    //����� ������ ���������
    if (CurTable == "CANNONS_TABLE" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
    {
		chr.Ship.Cannons.Type = sti(Goods[sti(GameInterface.(CurTable).(CurRow).index)].CannonIdx);
	}
    // ����� ��� ��������� �������� �� ������
    int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    int fb, lb, rb, bb;
    int qty;

    if (idx != -1)
    {
    	qty = GetCargoGoods(chr, idx);

    	rb = GetBortCannonsMaxQty(chr, "cannonr");

    	if (rb  > (qty / 2)) rb = qty / 2;
    	qty = qty - rb;
    	if (qty < 0) qty = 0;

    	lb = GetBortCannonsMaxQty(chr, "cannonl");
    	if (lb > qty) lb = qty;
    	qty = qty - lb;
    	if (qty < 0) qty = 0;

    	bb = GetBortCannonsMaxQty(chr, "cannonb");
    	if (bb > qty) bb = qty;
    	qty = qty - bb;
    	if (qty < 0) qty = 0;

    	fb = GetBortCannonsMaxQty(chr, "cannonf");
    	if (fb > qty) fb = qty;

    	SetCannonsToBort(chr, "cannonf", fb);
	    SetCannonsToBort(chr, "cannonb", bb);
	    SetCannonsToBort(chr, "cannonr", rb);
	    SetCannonsToBort(chr, "cannonl", lb);
    }
    // ������
    OnShipScrollChange();
    CannonsMenuRefresh();
}

void ChangeCannonNum(string sBort, int add)
{
    SetCannonsToBort(xi_refCharacter, sBort, GetBortCannonsQty(xi_refCharacter, sBort) + add);
    OnShipScrollChange();
	CannonsMenuRefresh();
}

void FillCannonsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	Table_Clear("CANNONS_TABLE", false, true, false);
	GameInterface.CANNONS_TABLE.hr.td1.str = "������ � �����";
	GameInterface.CANNONS_TABLE.hr.td1.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td2.str = "���-��";
	GameInterface.CANNONS_TABLE.hr.td2.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td3.str = "������.";
	GameInterface.CANNONS_TABLE.hr.td3.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td4.str = "����";
	GameInterface.CANNONS_TABLE.hr.td4.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td5.str = "�����";
	GameInterface.CANNONS_TABLE.hr.td5.scale = 0.8;

	if (!CheckAttribute(&GameInterface, "CANNONS_TABLE.BackUp"))
	{
		GameInterface.CANNONS_TABLE.select = 0;
		GameInterface.CANNONS_TABLE.top    = 0;
		GameInterface.CANNONS_TABLE.BackUp = true;
	}
	if (GetCannonQuantity(xi_refCharacter) > 0)
	{
	    for (i = 0; i< GOODS_QUANTITY; i++)
		{
	        row = "tr" + n;
			sGood = Goods[i].name;
			qty = GetCargoGoods(xi_refCharacter, i);
			if (qty <= 0) continue; // ������ �� ����

	        if (!CheckAttribute(&Goods[i], "type")) continue;
	        if (sti(Goods[i].type) != TRADE_TYPE_CANNONS) continue;

	        if (GetCannonCaliber(sti(Goods[i].CannonIdx)) > GetMaximumCaliber(xi_refCharacter)) continue;
			GameInterface.CANNONS_TABLE.(row).index = i;

			GameInterface.CANNONS_TABLE.(row).td2.str = qty;
			GameInterface.CANNONS_TABLE.(row).td2.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td3.str = sti(Goods[i].FireRange);
			GameInterface.CANNONS_TABLE.(row).td3.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td4.str = "x"+FloatToString(stf(Goods[i].DamageMultiply), 1);
			GameInterface.CANNONS_TABLE.(row).td4.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td5.str = sti(Goods[i].ReloadTime);
			GameInterface.CANNONS_TABLE.(row).td5.scale = 0.85;

	        GameInterface.CANNONS_TABLE.(row).td1.icon.group = "GOODS";
			GameInterface.CANNONS_TABLE.(row).td1.icon.image = sGood;
			GameInterface.CANNONS_TABLE.(row).td1.icon.offset = "0, 0";
			GameInterface.CANNONS_TABLE.(row).td1.icon.width = 32;
			GameInterface.CANNONS_TABLE.(row).td1.icon.height = 32;
			GameInterface.CANNONS_TABLE.(row).td1.textoffset = "28,0";
			GameInterface.CANNONS_TABLE.(row).td1.str = XI_ConvertString(sGood);
			GameInterface.CANNONS_TABLE.(row).td1.scale = 0.75;
			n++;
		}
	}
	Table_UpdateWindow("CANNONS_TABLE");
}

void ShowPartitionWindow()
{
    string str;
	string sTitul = "";
	if (isMainCharacterPatented())
	{
		sTitul = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))
	}
	
	str = "������� ����: " + GetDateString() + " " + GetTimeString() + NewStr();
	if(CheckAttribute(pchar, "paymentdate"))
	{
		str += "���� ����������� �������: " + pchar.paymentdate + NewStr();
	}	
	str += sTitul + " " + GetFullName(pchar) + NewStr() + XI_ConvertString("Rank") + ": " + sti(pchar.rank) + NewStr();
	str += XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE) + NewStr() +
			XI_ConvertString("OurMoney") + FindRussianMoneyString(sti(pchar.money)) + NewStr() + "*****" + NewStr();
    str += "���� � ������� ������:" + NewStr() + "���� ��������: " + GetPartitionAmount("Partition.MonthPart.Hero") + NewStr() +
		  "���� ��������: " + GetPartitionAmount("Partition.MonthPart.Officers") + NewStr() +
		  "���� ��������: " + GetPartitionAmount("Partition.MonthPart.Crew") + NewStr() + // + "-----" + NewStr() +
		  "���� �������� ������: " + GetPartitionAmount("Partition.MonthPart") + NewStr();
	str += "*****" + NewStr() + "���� �� ������� �����: " + GetPartitionAmount("CrewPayment");

	SetFormatedText("PARTITION_WINDOW_TEXT", str);
    SetSelectable("PARTITION_OK", false);
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	{
		if (sti(Pchar.Money) > 0)
		{
			SetSelectable("PARTITION_OK", true);
		}
	}
	XI_WindowShow("PARTITION_WINDOW", true);
	XI_WindowDisable("PARTITION_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("PARTITION_CANCEL");
}

void ExitPartitionWindow()
{
	XI_WindowShow("PARTITION_WINDOW", false);
	XI_WindowDisable("PARTITION_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void DoPartitionPay()
{
	int sum = 0;
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	if (GetPartitionAmount("CrewPayment") > 0)
	{
	    sum = GetPartitionAmount("CrewPayment");
	    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
        Pchar.CrewPayment = sti(Pchar.CrewPayment) - sum;
        if (sti(Pchar.CrewPayment) <= 0) DeleteAttribute(Pchar, "CrewPayment");
	}
	else
	{
		if (GetPartitionAmount("Partition.MonthPart") > 0)
		{
		    sum = GetPartitionAmount("Partition.MonthPart");
		    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
	        Pchar.Partition.MonthPart = sti(Pchar.Partition.MonthPart) - sum;
	        AddCrewMorale(xi_refCharacter, 2);
		}
	}
	pchar.paymentdate = GetDateString() + " " + GetTimeString();
	AddMoneyToCharacter(Pchar, -sum);
	Statistic_AddValue(pchar, "PartitionPay", sum);
	OnShipScrollChange();
	ExitPartitionWindow();
}

int GetPartitionAmount(string _param)
{
    if (!CheckAttribute(Pchar, _param)) return 0;
    return sti(Pchar.(_param));
}