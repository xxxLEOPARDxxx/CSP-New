////    boal ������ ��������-������ 17.10.06 ����� store.c
string totalInfo = "";
int  TableSelect = 0;
int	nCurScrollNum = 0;
int iShipCapacity;
int iTotalSpace;
float fShipWeight, fStoreWeight;
int iMaxGoodsStore = 50000;

bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
ref refStore, refCharacter, refShipChar;
int iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float fWeight;
int  iCurGoodsIdx;
bool ok; // for if

void InitInterface_R(string iniName, ref pStore)
{
    LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
	StartAboveForm(true);

    refStore = &stores[sti(pStore.StoreNum)];
	refCharacter = pchar;
	
	if(CheckAttribute(pchar, "shiptrade.character"))
	{
		refShipChar = CharacterFromID(pchar.shiptrade.character);
	}
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	if(refStore.Colony == "none")
	{
	    GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("In the hold");
	}
	else
	{
		GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("In the store");
	}
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = "�����";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = "��� �����";
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;

    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 405,113,SCRIPT_ALIGN_CENTER,1.0);

    SetShipWeight();
	SetDescription();
	SetFormatedText("INFO_TEXT",totalInfo);

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);


	SetEventHandler("frame","ProcessFrame",1);

	//SetEventHandler("RefreshTable","RefreshTable",0);
	//PostEvent("RefreshTable", 1000);


	if(refStore.Colony == "none")
	{
		SetFormatedText("STORECAPTION1", "�������: '" + refShipChar.ship.name + "'");
	}
	else
	{
		SetFormatedText("STORECAPTION1", XI_ConvertString("Colony" + refStore.Colony) + ": �����");
	}

 	if (refStore.Colony == "none")
	{
		SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refShipChar.FaceId) + ".tga");
	}
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
	}
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
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

		case "TABLE_LIST":
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
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    AddToTable();
	//SetCurrentNode("B_OK");
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sShipGroup;
	ref rShip;
	string sGood;
	string sBuy, sSell, sShipQ, sStoreQ, sStoreWeight;
	int tradetype, iColor;
	aref refGoods;
	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		makearef(refGoods,refStore.Goods.(sGood));
        tradeType = MakeInt(refGoods.TradeType);
        if (tradeType == TRADE_TYPE_CANNONS) continue; // �� �����
        
		sShipQ = GetCargoGoods(refCharacter, i);

		if(refStore.Colony != "none")
		{
			sStoreQ = GetStoreGoodsQuantity(refStore, i);
		}
		else
		{
			sStoreQ = GetCargoGoods(refShipChar, i);
		}

		if(sti(sStoreQ) < 0)
		{
			sStoreQ = 0;
			refGoods.quantity = 0;
		}
		if (sStoreQ == 0 && sShipQ == 0) continue; // ������ �� ����

		GameInterface.TABLE_LIST.(row).td1.str = sShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, sti(sShipQ));
		GameInterface.TABLE_LIST.(row).td5.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td6.str = Goods[i].Weight;

		GameInterface.TABLE_LIST.(row).td4.str = sStoreQ;


		
		switch(tradeType)
		{
			case TRADE_TYPE_NORMAL:
				iColor = argb(255,255,255,255);
			break;
			case TRADE_TYPE_EXPORT:
				iColor = argb(255,196,255,196);
			break;
			case TRADE_TYPE_IMPORT:
				iColor = argb(255,196,196,255);
			break;
			case TRADE_TYPE_CONTRABAND:
				iColor = argb(255,255,196,196);
			break;
			case TRADE_TYPE_AMMUNITION:
			    if (refStore.Colony == "none")
				{
					iColor = argb(255,196,196,196);
				}
				else
				{
					iColor = argb(255,255,255,255);
				}
			break;
		}
		if(checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
		{
			iColor = argb(255,255,192,255);
		}

        GameInterface.TABLE_LIST.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td3.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td3.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td3.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td3.textoffset = "20,0";
		GameInterface.TABLE_LIST.(row).td3.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td3.color = iColor;
		n++;
	}
	NextFrameRefreshTable();
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
	//Log_InfoOwn("OnTableClick  " + sRow + "   " + iColumn);
    Table_UpdateWindow(sControl);
}

void ChangePosTable()
{
}

void ShowHelpHint()
{
    string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";
	
	if (!bShowChangeWin)
	{// ������� ������ �� ������ � ������
        sHeader = "��������� ������� ������";
		sText1 = "������� ���� ���� ��� Enter �� ������� ������� �������� ����� ����������� ������. "+ newStr() +
		         "Shift + ����/����� �� ������� ������� ������������� �������� ����� � ����������������� ����������� �� ������������. "+ newStr() +
				 "���� �������������� ���������� � ���������� ������������� ������ ������, � �������������� (� �������) �������� �����������."+ newStr() +
				 "������� ����/����� �������� ���������� �� ������, � Shift + ����/����� �� ����������� ���������. ������� Enter �� ����� ����������� ��, � Esc - ������." + newStr() +
				 "�������� � ������ ����� � ����� ������ � ������� �������� �����/����, ����� ������������� �������� ������ ��� �������� �������.";
				 
        sText2 = "������� ������ �����: ��������� �����/���� �� ������, Shift + �����, Enter";
        
        sText3 = "�����: ������� - �����������, ����� - ������, ������� - �������";
        
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}
void EndTooltip()
{
	CloseTooltip(); // ������ �������, ���� ���
    GameInterface.qty_edit.str = 0;
	SetShipWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // ���� ����, ����� ������ �� �������
	{
	    TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
		if (GetRemovable(refCharacter))
		{
		    SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
		    SetSelectable("QTY_OK_BUTTON", false);
		}
	}
}

void RefreshTable()
{
    PostEvent("RefreshTable", 100);

    //SetFormatedText("INFO_TEXT",GameInterface.TABLE_LIST.select);

    if (TableSelect != sti(GameInterface.TABLE_LIST.select))
    {
        TableSelect = sti(GameInterface.TABLE_LIST.select);
        ChangePosTable();
    }
}

void Log_InfoOwn(string _str)
{
    SetFormatedText("INFO_TEXT", _str);
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    TableSelect = iSelected;
    string sRow = "tr" + (iSelected);
	SetShipWeight();
	SetVariable();
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", COMPANION_MAX);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	int nShipType = sti(refCharacter.ship.type);
	ref refBaseShip = GetRealShip(nShipType);

	iShipCapacity = sti(refBaseShip.Capacity);
	sText  = iShipCapacity;

	sText  = makeint(fShipWeight) + " / " + sText;
	sText = sText;
	SetFormatedText("CAPACITY", XI_ConvertString("Capacity") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
	if(refStore.Colony == "none")
	{
		iTotalSpace = sti(RealShips[sti(refShipChar.ship.type)].capacity);
		sMaxGoodsStore = XI_ConvertString("Capacity") + ":\n" + makeint(fStoreWeight) + " / " + iTotalSpace;
	}
	else
	{
	    sMaxGoodsStore = "�����";
	}
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FindRussianMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
	}
	else
	{
	    GameInterface.strings.shipname = "";
	}
}

void ProcessFrame()
{
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!=nCurScrollNum)
		{
            XI_WindowDisable("QTY_WINDOW", true);
			XI_WindowShow("QTY_WINDOW", false);
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			SetDescription();
   			GameInterface.TABLE_LIST.select = 1;
			GameInterface.TABLE_LIST.top = 0;
		}
	}
}

void SetDescription()
{
 	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			SetShipWeight();
			//iFullPrice = 0;

		}
	}
    CalculateInfoData();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
	SetVariable();
}

void SetShipWeight()
{
    if (CheckAttribute(refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{   // ������� � ����
		RecalculateCargoLoad(refCharacter);
		refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	fShipWeight  = makeint(GetCargoLoad(refCharacter)+ 0.4);

    if(refStore.Colony == "none")
	{
		fStoreWeight = makeint(GetCargoLoad(refShipChar)+ 0.4);
	}
	else
	{
	    fStoreWeight = 0;
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
	fWeight = stf(Goods[iGoodIndex].weight);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);

	if(refStore.Colony != "none")
	{
		iStoreQty = GetStoreGoodsQuantity(refStore, iGoodIndex);
	}
	else
	{
		iStoreQty = GetCargoGoods(refShipChar, iGoodIndex);
	}

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;
    iStorePrice = 1;
    //SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + "-");
    iShipPrice = 1;
    //SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	ShowFoodInfo();
}

void ShowFoodInfo()
{
	if (iCurGoodsIdx == GOOD_FOOD)
	{
		// ���� ��������� ��� ��� �����, ������ �� ����� ����� �� ���������
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
		SetFoodShipInfo(refCharacter, "FOOD_SHIP");
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty);
	}
	else
	{
		SetFormatedText("FOOD_SHIP", "");
	}
}
void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}
    if (!GetRemovable(refCharacter)) return;
    
 	if (BuyOrSell == 1) // BUY
	{
        if(refStore.Colony != "none")
		{
   			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty - nTradeQuantity);
		}
		else
		{
   			RemoveCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		WaitDate("",0,0,0, 0, 15);
	}
 	else
	{ // SELL
        if(refStore.Colony != "none")
		{
      		SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty + nTradeQuantity);
		}
		else
		{
   			AddCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		WaitDate("",0,0,0, 0, 15);
	}
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //������� ��� ���������
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	SetShipWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	
	string GoodName = goods[iCurGoodsIdx].name;
	
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
            BuyOrSell = -1;
            if (MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_CONTRABAND)
            {  // ����������� ������ �������
                GameInterface.qty_edit.str = 0;
            }
		    // �������� �� ����� ��������� -->
		    if (sti(GameInterface.qty_edit.str) > iShipQty)
		    {
		        GameInterface.qty_edit.str = iShipQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - fWeight;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // ����������
		    }
		    // �������� �� ����� ��������� <--
		    SetFormatedText("QTY_TypeOperation", "��������");
		    SetFormatedText("QTY_Result", "��� " + iWeight + " �");
		}
		else
		{
			BuyOrSell = 1;
         	// �������� �� ����� ��������� -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fShipWeight + iWeight) > iShipCapacity)
		    {
		        iWeight = iShipCapacity - fShipWeight - fWeight;
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // ����������
		    }
		    // �������� �� ����� ��������� <--

			SetFormatedText("QTY_TypeOperation", "�����");
			SetFormatedText("QTY_Result", "��� " + iWeight + " �");
		}
	}
	// ���� �������� ����
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetShipWeight();
    fShipWeight  = fShipWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
    ShowFoodInfo();
}

void REMOVE_ALL_BUTTON()  // ������� ���
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iShipQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // ������ ���
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // �������
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -iUnits;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // ������
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = iUnits;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}
