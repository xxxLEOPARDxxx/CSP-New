////    boal 31/03/06 STORE
// ugeen --> ���������� � ��������� ������ ��  28.01.10
string totalInfo = "";
int  	TableSelect = 0;
int		nCurScrollNum = 0;
int 	iShipCapacity;
int 	iTotalSpace;
float 	fShipWeight, fStoreWeight;
int 	iMaxGoodsStore = 50000;

bool 	bShowChangeWin = false;
int  	BuyOrSell = 0; // 1-buy -1 sell
string 	sChrId;
ref 	refStore, refCharacter, refShipChar;
int 	iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float 	fWeight;
int  	iCurGoodsIdx;
string 	sCurRow;
int 	iFOODQty, iRUMQty;
bool 	ok; // for if
int iColor2;

void InitInterface_R(string iniName, ref pStore)
{
 	StartAboveForm(true);

    refStore = pStore;
	refCharacter = pchar;
	iColor2 = argb(255,128,96,96);//���� �����������
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("In the storage");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = "�����";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = "���";
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;

    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

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

	SetEventHandler("frame","ProcessFrame",1);

	SetFormatedText("STORECAPTION1", XI_ConvertString("Colony" + refStore.Colony) + ": " + XI_ConvertString("titleStorage"));
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_STORAGE_EXIT );
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit( RC_INTERFACE_STORAGE_EXIT );
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
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "TABLE_LIST":
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;
		case "QTY_STORAGE_REMOVE_GOOD":
	        REMOVE_ALL_GOOD();
		break;
	}
}

void REMOVE_ALL_GOOD()
{
	SetStorageGoods(refStore, iCurGoodsIdx, 0);
	iStoreQty = 0;
	AddToTable();
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    AddToTable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, newrow, sShipGroup;
	
	ref rShip;
	string sGood;
	string sBuy, sSell, sStoreWeight;
	int iShipQ, iStoreQ, iColor;
	aref aNextRow, aCurRow, refGoods;
	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		makearef(refGoods,refStore.Storage.Goods.(sGood));
                        
		iShipQ = GetCargoGoods(refCharacter, i);
		iStoreQ = GetStorageGoodsQuantity(refStore, i); 
		
		if(i == GOOD_SLAVES) continue; // ����� ����� !!
		
		if (iStoreQ < 0) {iStoreQ = 0; refGoods.quantity = 0;}
		if (iStoreQ == 0 && iShipQ == 0) continue; // ������ �� ����

		GameInterface.TABLE_LIST.(row).td5.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td1.str = iShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, iShipQ);
		GameInterface.TABLE_LIST.(row).td4.str = iStoreQ;
		GameInterface.TABLE_LIST.(row).td6.str = GetGoodWeightByType(i, iStoreQ);
		iColor = argb(255,255,255,255);
		if(checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest")) iColor = argb(255,255,192,255);
        GameInterface.TABLE_LIST.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td3.icon.offset = "0, -1";
		GameInterface.TABLE_LIST.(row).td3.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td3.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td3.textoffset = "20,0";
		GameInterface.TABLE_LIST.(row).td3.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td3.color = iColor;

		if (CheckAttribute(refStore, "Storage.Goods." + sGood + ".Bought.Coeff") && refStore.Storage.Goods.(sGood).Bought.Coeff == "0")
		{
			if(sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Time) <= GetNpcQuestPastDayParam(refStore, "Storage.Goods_Clear_"+sGood))//Time �� �����, �� ������� � ������� ������� ���������� �������
			{
				refStore.Storage.Goods.(sGood).Bought.Coeff = "1";
				refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = iStoreQ;//�� ��������
			}
		}
		else {refStore.Storage.Goods.(sGood).Bought.Coeff = 1; refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = iStoreQ;}//�� ���� �������� �����������

		if (makeint(Goods[i].Cost)/makeint(Goods[i].Weight) > 45)
		{
			if (refStore.Storage.Goods.(sGood).Bought.Coeff == "0" || refCharacter.Goods.(sGood).Bought.Coeff == "0")
			{
				if (sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty) + sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) == 0) {newrow = row;}//�������� ���, ������ � ������� �� ���������
				else
				{
				n++
				newrow = "tr" + n;//������ ������ � ����������
				makearef(aCurRow, GameInterface.TABLE_LIST.(row));
				makearef(aNextRow, GameInterface.TABLE_LIST.(newrow));
				CopyAttributes(aNextRow, aCurRow);
				GameInterface.TABLE_LIST.(row).td4.str = sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty);
				GameInterface.TABLE_LIST.(row).td6.str = GetGoodWeightByType(i, sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty));
				GameInterface.TABLE_LIST.(row).td1.str = sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty);
				GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty));
				}

				GameInterface.TABLE_LIST.(newrow).td3.color = iColor2;
				GameInterface.TABLE_LIST.(newrow).td4.str = iStoreQ - sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty);
				GameInterface.TABLE_LIST.(newrow).td6.str = GetGoodWeightByType(i, iStoreQ - sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty));
				GameInterface.TABLE_LIST.(newrow).td1.str = iShipQ - sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty);
				GameInterface.TABLE_LIST.(newrow).td2.str = GetGoodWeightByType(i, iShipQ - sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty));
			}
		}
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
        sHeader = "��������� ���������� �� ����� ��� �� ������ �� �������";
		sText1 = "������� ���� ���� ��� Enter �� ������� ������� �������� ����� ���������� ������. "+ newStr() +
		         "Shift + ����/����� �� ������� ������� ������������� �������� ����� � ����������������� ����������� ���������� �� ������������. "+ newStr() +
				 "���� �������������� ���������� � ���������� ������������� ���������� ������ �� ������, � �������������� (� �������) �� �����."+ newStr() +
				 "������� ����/����� �������� ���������� �� ������, � Shift + ����/����� �� ����������� ���������. ������� Enter �� ����� ����������� ��, � Esc - ������." + newStr() +
				 "�������� � ������ ����� � ����� ������ � ������� �������� �����/����, ����� ������������� �������� ������ ��� �������� �������.";
				 
        sText2 = "������� ���������� �����: ��������� �����/���� �� ������, Shift + �����, Enter";
        
        sText3 = "";
        
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
    sCurRow = "tr" + (iSelected);
	SetShipWeight();
	SetVariable();
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sCurRow).index));
}

void OnTableClick()
{
/*
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();
	sCurRow = "tr" + (iRow+1);

    Table_UpdateWindow(sControl);
*/
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 8);

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

	sMaxGoodsStore = XI_ConvertString("storage");

	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);
	
	sText = "����� ������������� ������ : " + GetStorageUsedWeight(refStore) + " / " + iTotalSpace + " �.";
	SetFormatedText("STORAGE_INFO", sText);

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

	fStoreWeight = 0;
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
    string goodsDescr = "";

	goodsDescr += GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", ����� " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	fWeight = stf(Goods[iGoodIndex].weight);

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);

	iShipQty = sti(GameInterface.TABLE_LIST.(sCurRow).td1.str);
	iStoreQty = sti(GameInterface.TABLE_LIST.(sCurRow).td4.str);
	iFOODQty = GetCargoGoods(refCharacter, GOOD_FOOD);
	iRUMQty = GetCargoGoods(refCharacter, GOOD_RUM);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;
	
	ShowFoodInfo();
}

void ShowFoodInfo()
{
	if(iCurGoodsIdx == GOOD_FOOD)
	{
		// ���� ��������� ��� ��� �����, ������ �� ����� ����� �� ���������
		SetCharacterGoods(refCharacter, GOOD_FOOD, iFOODQty + BuyOrSell*sti(GameInterface.qty_edit.str));
		SetFoodShipInfo(refCharacter, "FOOD_SHIP");
		SetCharacterGoods(refCharacter, GOOD_FOOD, iFOODQty);
	}
	else
	{
		if(iCurGoodsIdx == GOOD_RUM) // Warship 11.07.09 �� ������� ������ ����
		{
			// ���� ��������� ��� ��� �����, ������ �� ����� ����� �� ���������
			SetCharacterGoods(refCharacter, GOOD_RUM, iRUMQty + BuyOrSell*sti(GameInterface.qty_edit.str));
			SetRumShipInfo(refCharacter, "FOOD_SHIP");
			SetCharacterGoods(refCharacter, GOOD_RUM, iRUMQty);
		}
		else
		{
			SetFormatedText("FOOD_SHIP", "");
		}
	}
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	string sGood = Goods[iCurGoodsIdx].Name;
	if (BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}
    if (!GetRemovable(refCharacter)) return;
    
 	if (BuyOrSell == 1)//�������� �� ������
	{
		if(CheckAttribute(refCharacter,"Storage.Goods."+sGood+".Bought.Coeff") && refCharacter.Storage.Goods.(sGood).Bought.Coeff == "0") //��������, ������ �� ��������
		{
			if(sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Time) <= GetNpcQuestPastDayParam(refStore, "Storage.Goods_Clear_"+sGood)) //characterfromid(refStore.colony + "_trader")
			{
				refStore.Storage.Goods.(sGood).Bought.Coeff = "1";
				refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = iStoreQty;//�� ��������
			}
		}
		if(sti(GameInterface.TABLE_LIST.(sCurRow).td3.color) != iColor2) //�������� �������
		{
			refCharacter.Goods.(sGood).Bought.Coeff.Qty = sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) + nTradeQuantity;
			refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty) - nTradeQuantity;
			if (sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty) <= 0) 
				{refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = 0; refStore.Storage.Goods.(sGood).Bought.Coeff = 0;}//�� ������� �������
		}
		RemoveStorageGoods(refStore, iCurGoodsIdx, nTradeQuantity);
		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
	}
 	else
	{//���������� �� �����
		if (sti(GameInterface.TABLE_LIST.(sCurRow).td3.color) == iColor2)//���� ���������� - ��������� ���� ������� - ��� ���, ��� ��� �������� ������� ����������
		{
			refStore.Storage.Goods.(sGood).Bought.Coeff = 0;
			refStore.Storage.Goods.(sGood).Bought.Coeff.Time = 5;//��������� ����� �� 5 ����//������� ������ �� �������, ������ � ��� ���� �� ��������
			SaveCurrentNpcQuestDateParam(refStore, "Storage.Goods_Clear_"+sGood);
		}
		else
		{	//������� �� �����
			refCharacter.Goods.(sGood).Bought.Coeff.Qty = sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) - nTradeQuantity;
			refStore.Storage.Goods.(sGood).Bought.Coeff.Qty = sti(refStore.Storage.Goods.(sGood).Bought.Coeff.Qty) + nTradeQuantity; 
			if(sti(refCharacter.Goods.(sGood).Bought.Coeff.Qty) < 0) //�� ������� ������
				{refCharacter.Goods.(sGood).Bought.Coeff.Qty = "0";	refCharacter.Goods.(sGood).Bought.Coeff = "1";}
		}	
      	AddStorageGoods(refStore, iCurGoodsIdx, nTradeQuantity);
		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);				
	}
   	WaitDate("",0,0,0,0,5);
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
		    SetFormatedText("QTY_TypeOperation", "��������� �� �����");
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
			SetFormatedText("QTY_TypeOperation", "��������� � ����");
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
	if (!bShowChangeWin) ShowItemInfo();
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iShipQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // ������ ���
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) ShowItemInfo();
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // �������
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
  	if (BuyOrSell == 0) GameInterface.qty_edit.str = -iUnits;
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
	if (!bShowChangeWin)return;
	if (BuyOrSell == 0) GameInterface.qty_edit.str = iUnits;
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