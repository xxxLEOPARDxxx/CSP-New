string totalInfo = "";
int  TableSelect = 0;
int	nCurScrollNum = 0;
int iShipCapacity;
int iTotalSpace;
float fShipWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
bool nocheck = true;

bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
ref refStore, refCharacter, refShipChar;
int iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float fWeight;
int  iCurGoodsIdx;
bool ok;

// BUHO - Fist state variable
#define FIS_ALL		0		// Normal
#define FIS_SHIP	1		// Show ship
#define FIS_STORE	2		// Show store
int FIS_FilterState;

void InitInterface_R(string iniName, ref pStore)
{
 	StartAboveForm(true);
	
	refStore = pStore;
	refCharacter = pchar;
	SetQuestGoodsToStore(refStore); // ��������� ��������� ������� � ���
	if(CheckAttribute(pchar, "shiptrade.character"))
	{
		refShipChar = CharacterFromID(pchar.shiptrade.character);
	}
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	if(refStore.Colony == "none")
	{
		GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("In the hold");
	}
	else
	{
		GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("In the store");
	}
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = "�����";
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td8.str = "��� �����";
	GameInterface.TABLE_LIST.hr.td8.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td9.str = "����� ���";
	GameInterface.TABLE_LIST.hr.td9.scale = 0.9;

	FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if (checkattribute(pchar, "StoreFilter")) FIS_FilterState = sti(pchar.StoreFilter); else FIS_FilterState = 0; 
	switch (FIS_FilterState)
	{
	case FIS_ALL: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1); break;
	case FIS_SHIP: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_SHIP", 2, 1, 1); break;
	case FIS_STORE: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_STORE", 2, 1, 1); break;
	}

	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 405,108,SCRIPT_ALIGN_CENTER,1.0);

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
	SetEventHandler("Autotrade_All", "Autotrade_All", 0);
	SetEventHandler("Autotrade_This", "Autotrade_This", 0);

	SetEventHandler("frame","ProcessFrame",1);

	if(refStore.Colony == "none")
	{
		SetFormatedText("STORECAPTION1", "�������: '" + refShipChar.ship.name + "'");
		SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refShipChar.FaceId) + ".tga");
		SetNodeUsing("AUTOTRADE_ALL", false);//������� ����������� � ����
	}
	else
	{
		SetFormatedText("STORECAPTION1", XI_ConvertString("Colony" + refStore.Colony) + ": " + XI_ConvertString("titleStore"));
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
	pchar.StoreFilter = FIS_FilterState;
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
	DelEventHandler("Autotrade_All", "Autotrade_All");
	DelEventHandler("Autotrade_This", "Autotrade_This");

	// boal 27.02.05 -->
	if (CheckAttribute(pchar, "PriceList.StoreManIdx"))
	{
		SetPriceListByStoreMan(&Colonies[sti(pchar.PriceList.StoreManIdx)]);
		DeleteAttribute(pchar, "PriceList.StoreManIdx");
	}
	// boal 27.02.05 <--
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
		// BUHO-FIST - ADDED CODE - Response to checkboxes.
		case "CB_SHIP":		if (comName == "click")ProcessFilter(nodName); break;
		case "CB_ALL":		if (comName == "click")ProcessFilter(nodName); break;
		case "CB_STORE":	if (comName == "click")ProcessFilter(nodName); break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
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
		sShipQ = GetCargoGoods(refCharacter, i);
		if(sShipQ == "0")
		{
			refCharacter.Goods.(sGood).Bought.Coeff = "1";
			refCharacter.Goods.(sGood).Bought.Coeff.Qty = "0";
		}
		if(!CheckAttribute(refCharacter,"Goods."+sGood+".Bought.Coeff")) refCharacter.Goods.(sGood).Bought.Coeff = "0";
		if(!CheckAttribute(refCharacter,"Goods."+sGood+".Bought.Coeff.Qty")) refCharacter.Goods.(sGood).Bought.Coeff.Qty = "0";
		makearef(refGoods,refStore.Goods.(sGood));
		tradeType = MakeInt(refGoods.TradeType);
		if (tradeType == TRADE_TYPE_CANNONS) continue; // �� �����


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
		//// {*} BUHO-FIST - ADDED CODE - Filters at work.
		if (sti(sStoreQ) == 0 && FIS_FilterState == FIS_STORE) continue;
		if (sti(sShipQ) == 0 && FIS_FilterState == FIS_SHIP) continue;
		//// {*} BUHO END ADDITION

		GameInterface.TABLE_LIST.(row).td1.str = sShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, sti(sShipQ));
		GameInterface.TABLE_LIST.(row).td7.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td6.str = sStoreQ;
		GameInterface.TABLE_LIST.(row).td8.str = Goods[i].Weight;
		GameInterface.TABLE_LIST.(row).td9.str = GetGoodWeightByType(i, sti(sStoreQ));

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
			case TRADE_TYPE_AGGRESSIVE:
				iColor = argb(255,255,173,51);
			break;
		}
		if(CheckAttribute(refCharacter,"Goods."+sGood+".Bought.Coeff") && refCharacter.Goods.(sGood).Bought.Coeff == "0") iColor = argb(255,255,192,255);

		GameInterface.TABLE_LIST.(row).td4.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td4.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td4.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td4.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td4.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td4.textoffset = "20,0";
		GameInterface.TABLE_LIST.(row).td4.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td4.color = iColor;

		if (tradeType == TRADE_TYPE_CONTRABAND)
		{
			GameInterface.TABLE_LIST.(row).td5.str = "-";
		}
		else
		{
			GameInterface.TABLE_LIST.(row).td5.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, refCharacter, 1);
			if(CheckAttribute(refCharacter,"Goods."+sGood+".Bought.Coeff") && refCharacter.Goods.(sGood).Bought.Coeff == "0") GameInterface.TABLE_LIST.(row).td5.color = argb(255,255,192,255);
			// � ����
			if (refStore.Colony == "none")
			{
				GameInterface.TABLE_LIST.(row).td5.str = makeint(sti(GameInterface.TABLE_LIST.(row).td5.str) / 2);
				if (sti(GameInterface.TABLE_LIST.(row).td5.str) < 1) GameInterface.TABLE_LIST.(row).td5.str = 1;
			}
		}
		if ((tradeType == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
		{
			GameInterface.TABLE_LIST.(row).td3.str = "-"; // ������ ������ � ����
		}
		else
		{
			GameInterface.TABLE_LIST.(row).td3.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
		}
		n++;
	}
	NextFrameRefreshTable();
	nocheck = false;
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
	if(!nocheck) DoChange();
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

void ShowHelpHint()
{
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";
	if (bShowChangeWin) return;

	bool bCheckboxes = False;
	string sNode = GetCurrentNode();
	switch (sNode)
	{
		case "CB_SHIP":		bCheckboxes = True; break;
		case "CB_ALL":		bCheckboxes = True; break;
		case "CB_STORE":	bCheckboxes = True; break;
	}
	if (bCheckboxes)
	{
		sHeader = "�������";
		sText1 = "������ �������: ���������� ������ �� ������, ��� ���� �� ����� �������.";
		sText2 = "��� ������: ��������, ���������� ������ ��� �� �������, ��� � ��������.";
		sText3 = "������ ��������: ���������� ������ �� ������, ��� ���� � ��������.";
		CreateTooltip("#" + sHeader,
					  sText1, argb(255,255,255,255),
					  sText2, argb(255,192,192,192),
					  sText3, argb(255,255,255,255),
					  "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}

	else
	{// ������� ������ �� ������ � ������
		sHeader = "��������� ��������";
		sText1 = "������� ���� ���� ��� Enter �� ������� ������� �������� ����� �������/������� ������. "+ newStr() +
				 "Shift + ����/����� �� ������� ������� ������������� �������� ����� � ����������������� ����������� �������/������� �� ������������. "+ newStr() +
				 "���� �������������� ���������� � ���������� ������������� ������� ������, � �������������� (� �������) �������."+ newStr() +
				 "������� ����/����� �������� ���������� �� ������, � Shift + ����/����� �� ����������� ���������. ������� Enter �� ����� ����������� ��, � Esc - ������." + newStr() +
				 "�������� � ������ ����� � ����� ������ � ������� �������� �����/����, ����� ������������� �������� ������ ��� �������� �������.";

		sText2 = "������� ������� �����: ��������� �����/���� �� ������, Shift + �����, Enter";

		sText3 = "����� ���� ������:" + newStr() +
				 "- ������ : ������������ ������" + newStr() +
				 "- ����� : ��������� ������" + newStr() +
				 "- ������� : ������������� ������" + newStr() +
				 "- ���������� : ������ ������������ ������";

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

	if (TableSelect != sti(GameInterface.TABLE_LIST.select))
	{
		TableSelect = sti(GameInterface.TABLE_LIST.select);
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

void DoChange()
{
	AddToTable();
	string row = "tr"+sti(GameInterface.TABLE_LIST.select);
	if (row != "tr0") ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(row).index));
	nocheck = true;
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
		//// {*} BUHO-PT - ADDED CODE - Food and rum in store.
		int iFoodDays = CalculateShipFood(refCharacter);
		int iRumdays = CalculateShipRum(refCharacter);
		sMaxGoodsStore = "��������:\n" + "���: " + iFoodDays + "�");
		sMaxGoodsStore = sMaxGoodsStore + "\n" + "���: " + iRumDays + "�");
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
	AddToTable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
	AddToTable();
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
	string goodsDescr = "";
	if (bBettaTestMode)
	{
		goodsDescr += NewStr() + "BaseNorm " + goods[iGoodIndex].Norm + " BaseCost " + goods[iGoodIndex].Cost + " StoreNorm " + refStore.Goods.(GoodName).Norm;
		goodsDescr += NewStr() + "NormPrMod " + FloatToString(stf(refStore.Goods.(GoodName).NormPriceModify), 4) + " CurPrMod " +
								 FloatToString(stf(refStore.Goods.(GoodName).RndPriceModify), 4) + " Delta " +
								 FloatToString(stf(stf(refStore.Goods.(GoodName).Quantity) / stf(refStore.Goods.(GoodName).Norm)), 3);
		goodsDescr += NewStr();
	}
	goodsDescr += GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
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
	if (MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_CONTRABAND)
	{
		iStorePrice = 0;
		SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + "-");
	}
	else
	{
		iStorePrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		// ��� ����, ���� ���� �� �������
	 	if(refStore.Colony == "none")
		{
			iStorePrice /= 2;
			if (iStorePrice < 1) iStorePrice = 1;
		}
		SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));
	}
	if ((MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
	{
		iShipPrice = 0;
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else
	{
		iShipPrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iShipPrice));
	}
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
		if(iCurGoodsIdx == GOOD_RUM) // Warship 11.07.09 �� ������� ������ ����
		{
			// ���� ��������� ��� ��� �����, ������ �� ����� ����� �� ���������
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
			SetRumShipInfo(refCharacter, "FOOD_SHIP");
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty);
		}
		else
		{
		SetFormatedText("FOOD_SHIP", "");
		}
	}
}

// BUHO-FIST - ADDED CODE - Checkboxes processing function.
void ProcessFilter(string sButton)
{
	nocheck = false;
	switch (sButton)
	{
	case "CB_SHIP":
		/*
		Radio-button semantics:
		- If the button was selected the user is deselecting it, so reselect it and exit.
		- If the button was not selected, deselect all others, set the state variable and
		  reload the table.
		*/
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_SHIP", 2, 1, 1);
		if (FIS_FilterState != FIS_SHIP)
		{
			// Button being selected.
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_STORE", 2, 1, 0);
			FIS_FilterState = FIS_SHIP;
			AddToTable();
		}
		break;
	case "CB_ALL":
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1);
		if (FIS_FilterState != FIS_ALL)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_SHIP", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_STORE", 2, 1, 0);
			FIS_FilterState = FIS_ALL;
			AddToTable();
		}
		break;
	case "CB_STORE":
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_STORE", 2, 1, 1);
		if (FIS_FilterState != FIS_STORE)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_SHIP", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			FIS_FilterState = FIS_STORE;
			AddToTable();
		}
		break;
	}
}

void TransactionOK()
{
	int nTradeQuantity, moneyback;
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
		string sGood = Goods[iCurGoodsIdx].Name;
		if(GetCargoGoods(refCharacter, iCurGoodsIdx) == "0" || GetCargoGoods(refCharacter, iCurGoodsIdx) == refCharacter.Goods.(sGood).Bought.Coeff.Qty) refCharacter.Goods.(sGood).Bought.Coeff = "1";
		refCharacter.Goods.(sGood).Bought.Coeff.Qty = sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) + nTradeQuantity;
		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money)  - moneyback;
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / (1800.0 - sti(GetCharacterSPECIALSimple(pchar, SPECIAL_I)) * sti(GetCharacterSPECIALSimple(pchar, SPECIAL_C)) * 10));
		WaitDate("",0,0,0, 0, 5);
		// boal <--
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
		sGood = Goods[iCurGoodsIdx].Name;
		if(refCharacter.Goods.(sGood).Bought.Coeff == "1")
		{			
			refCharacter.Goods.(sGood).Bought.Coeff.Qty = sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) - nTradeQuantity;
			if(sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) <= 0) refCharacter.Goods.(sGood).Bought.Coeff = "0";
		}
		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
  		pchar.money = sti(pchar.money)  + moneyback;
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / (2600.0 - sti(GetCharacterSPECIALSimple(pchar, SPECIAL_I)) * sti(GetCharacterSPECIALSimple(pchar, SPECIAL_C)) * 10));
		WaitDate("",0,0,0, 0, 5);
		// boal <--
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
			SetFormatedText("QTY_TypeOperation", "�������");
			SetFormatedText("QTY_Result", "������ " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
							", ��� " + iWeight + " �");
		}
		else
		{
			// �� ����� � ����� � ���� �������� ����� � ����, � �� ����� ��� ����������
			if ((MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
			{
				GameInterface.qty_edit.str = 0;
			}
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
			if (makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(pchar.money))
			{
				GameInterface.qty_edit.str = makeint(sti(pchar.money)*iUnits / iShipPrice);
				iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
			}
			// �������� �� ����� ��������� <--

			SetFormatedText("QTY_TypeOperation", "������");
			SetFormatedText("QTY_Result", "������ " + makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
							", ��� " + iWeight + " �");
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

void Autotrade_All()
{
	int i, cn;
	ref chref;

	if (!IsPCharHaveTreasurer()) {Log_Info("��� ��������. ������� ������ ���������!"); return;}

	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(PChar, i);
		if(cn > 0)
		{
			chref = GetCharacter(cn);
			if(!GetRemovable(chref)) continue;
			Autotrade_Goods(chref);
		}
		//TO DO - ��������� ������� � ������� �� ��� �������, � ������ ������� ��������� �������, � ����� ��������
		//TO DO - ���������������� ����� ����������� �������������� ������ �������, ���� �� ������ � �������
	}
	AddToTable();
	EndTooltip();
}

void Autotrade_This()
{
	if (!IsPCharHaveTreasurer()) {Log_Info("��� ��������. ������� ������ ���������!"); return;}
	if(!GetRemovable(refCharacter)) return;
	Autotrade_Goods(refCharacter);
	AddToTable();
	EndTooltip();
}

int Autotrade_Goods(ref rChar)
{
	int i, iNeedGood, iCost, iStoreGoodQty;
	ref rGood, rTreasurer;
	string sGood;
	float fNeedCargo;
	int buyGoodsWeight = 0;
	int iCurGoodQty, iNeedGoodsQty, iFreeCargo;
	int iMoneyQty = 0;

	rTreasurer = GetPCharTreasurerRef(); // ��������. ��� ���� �����

	for(i = 0; i < GOODS_QUANTITY; i++)
	{
		rGood = &Goods[i];
		sGood = rGood.name;

		if(!CheckAttribute(rChar, "TransferGoods." + sGood))
		{
			rChar.TransferGoods.(sGood) = 0;
		}

		iCurGoodQty = GetCargoGoods(rChar, i); // ������� ����� ������ ���� ������
		iNeedGoodsQty = sti(rChar.TransferGoods.(sGood)); // ������� ����� ����� ������� ������ (�� ��������!)
//����� �� ������ �������, ���� �� �������� - ��������� ����

		if(iCurGoodQty == iNeedGoodsQty) continue; // ������ �� �����

		if (CheckAttribute(pchar,"SellRestriction"))//����� ������ - ���� ���� �������, �� ������ ��������
		{
			if(iCurGoodQty > iNeedGoodsQty) // �������
			{
				if(CheckAttribute(refStore, "goods." + sGood + ".tradetype"))
				{
					if(refStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND || refStore.goods.(sGood).tradetype == TRADE_TYPE_CANNONS) continue;
				}
				iNeedGood = iCurGoodQty - iNeedGoodsQty; // ������� ����� �������

				if(refStore.Colony == "none")//���� ������ �� ������� � ����//�������� ������ �������� � ����, ���� �������� ���� �� �����
//������ ��������� ����������� � ����? ���� ���. ������, ��� �� ��������� � �������
				{
					iFreeCargo = GetCargoFreeSpace(refShipChar); //���������, ��� ����������� ��� ��������, ���� �������
					if (fNeedCargo > iFreeCargo) iNeedGood = iFreeCargo / sti(rGood.weight) * sti(rGood.Units);
				}

				iCost = GetStoreGoodsPrice(refStore, i, 1, PChar, 1)*iNeedGood/sti(rGood.Units); // ���� ������ ��� �������
				RemoveCharacterGoodsSelf(rChar, i, iNeedGood); // �������� ������ � ����� �����
				AddStoreGoods(refStore, i, iNeedGood); // ���������� ����� � �����
				//WaitDate("", 0, 0, 0, 0, 5);
				iMoneyQty += iCost;
				buyGoodsWeight -= iNeedGood;
			}
		}

		if(iCurGoodQty < iNeedGoodsQty) // ��������
		{
			if(CheckAttribute(refStore, "goods." + sGood + ".tradetype") && refStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND)
			{
				if(!CheckAttribute(rChar, "TransferGoods.BuyContraband")) continue;
			}

			iNeedGood = iNeedGoodsQty - iCurGoodQty; // ������� ����� ������
			iStoreGoodQty = GetStoreGoodsQuantity(refStore, i); // ������� ����� ������ (����� ���� � ������)
			if (iNeedGood > iStoreGoodQty) iNeedGood = iStoreGoodQty; // ����� ������ ������, ��� ���� � ������
			fNeedCargo = iNeedGood * stf(rGood.weight) / stf(rGood.Units);
			iFreeCargo = GetCargoFreeSpace(rChar); //���������, ��� ����������� ��� ��������, ���� �������
			if (fNeedCargo > iFreeCargo) iNeedGood = iFreeCargo / sti(rGood.weight) * sti(rGood.Units);

			iCost = GetStoreGoodsPrice(refStore, i, 0, PChar, 1)*iNeedGood/sti(rGood.Units); // ���� ������ ��� �������
			if(sti(PChar.Money) >= iCost)
			{
				AddCharacterGoodsSimple(rChar, i, iNeedGood); // ���� ������ � ���� �������
				RemoveStoreGoods(refStore, i, iNeedGood); // ������� �� ������
				//WaitDate("", 0, 0, 0, 0, 5);
				iMoneyQty -= iCost;
				buyGoodsWeight += iNeedGood;
			}
		}
	}

	if(iMoneyQty != 0) // ���� ���� ���-�� ������� ��� ������
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) // ����� � ����� ��������
	}

	return buyGoodsWeight;//TO DO - ����� ������? �������������� � ��������, ���� �������� ���� �� ���� ���-�� ������� ��� ���
}

void SellExcessGoods(ref chr)
{

}

int GetGoodsLimit(ref chr, string _itemname)
{
	return 0;
}

void AddResult(string sTableName, string Result, bool isFail)
{

}