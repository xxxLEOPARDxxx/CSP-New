//#20180919-02
int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fChestWeight;
int iMaxGoodsStore = 50000;

bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
//ref refStore,
ref refCharacter;
aref refChest;
int iCharQty, iChestQty;
float fWeight;
int  iCurGoodsIdx;
int nMoney;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIT_ALL			0		// Normal
#define FIT_BACKPACK	1		// Show backpack
#define FIT_CHEST		2		// Show trader
int FIT_FilterState = 2;
//// {*} BUHO END ADDITION

void InitInterface_R(string iniName, ref itemsRef)
{
    LAi_SetActorTypeNoGroup(pchar);
    nMoney = FindItem("Gold");
    DelBakSkillAttr(GetMainCharacter());
    ClearCharacterExpRate(GetMainCharacter());
    if (!LAi_boarding_process) QuestCheckTakeBoxes(itemsRef);

    StartAboveForm(true);

	refCharacter = pchar;
	refChest = itemsRef;
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = MsgIS("Items2");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = MsgIS("Weight");
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	//GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	//GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = MsgIS("Item name");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	//GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	//GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = MsgIS("Chest items");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = MsgIS("Weight pcs");
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;

	SortItems(refCharacter);
	SortItems(itemsRef);

    FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"CharName","",FONT_NORMAL,COLOR_MONEY, 405,105,SCRIPT_ALIGN_CENTER,1.0);
	SetCharWeight();
	SetDescription();
	FillCharacterInfo();

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

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleItemsBox"));
	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 1, 1, XI_ConvertString("FIST_CB_Chest"));
    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1);

	SetNewGroupPicture("OTHER_PICTURE","BOX_IMAGE","BoxImage");
	//SetNewPicture("OTHER_PICTURE", "interfaces\\portraits\\256\\face_" + its(refChest.FaceId) + ".tga.tx");
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
    //#20190210-01
    reCheckCrosshair(true);
    CheckAndSetOverloadMode(GetMainCharacter());
	int i, cn;

	bMainCharacterInBox = false;
	//#20170318-20
    for(i=1;i<=MAX_NUM_FIGHTERS;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
            CharacterCheckEquipAll(refCharacter);
		}
	}
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
	LAi_SetPlayerType(pchar);
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
		//// {*} BUHO-FIST - ADDED CODE - Response to checkboxes.
		case "CB_BACKPACK":		if (comName == "click")ProcessFilter(nodName); break;
		case "CB_ALL":			if (comName == "click")ProcessFilter(nodName); break;
		case "CB_TRADER":		if (comName == "click")ProcessFilter(nodName); break;
		//// {*} BUHO END ADDITION
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
    if(CheckAttribute(&GameInterface, "TABLE_LIST.tr1"))
        ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
    bool showMoney = true;
	int n, i;
	string row, sShipGroup;
	string sGood;
	int  idLngFile;
	int leftQty, rightQty;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);

	if(!CheckAttribute(refCharacter, "Money")) refCharacter.Money = 0;
	if(!CheckAttribute(refChest, "Money")) refChest.Money = 0;
	leftQty  = sti(refCharacter.Money);
    rightQty = sti(refChest.Money);

	if (leftQty > 0 || rightQty > 0)
	{
	    row = "tr" + n;
	    /*
		GameInterface.one_itemslist.pic1.img1 = GetItemPictureName("Gold");
		GameInterface.one_itemslist.pic1.tex1 = GetItemPictureTexture("one_itemslist.ImagesGroup","Gold");
		GameInterface.one_itemslist.pic1.itemID = "Money";
		GameInterface.one_itemslist.pic1.str1 = "#"+refCharacter.Money;
		*/

        //// {*} BUHO-FIST - ADDED CODE - Filters at work.
        if (leftQty == 0 && FIT_FilterState == FIT_BACKPACK) showMoney = false;
        if (rightQty == 0 && FIT_FilterState == FIT_CHEST) showMoney = false;
        //// {*} BUHO END ADDITION

        if(showMoney) {
            GameInterface.TABLE_LIST.(row).td1.str = leftQty ;
            //GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * sti(GameInterface.TABLE_LIST.(row).td1.str), 1);
            //GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);
            GameInterface.TABLE_LIST.(row).td6.str = rightQty;
            GameInterface.TABLE_LIST.(row).td4.icon.group = Items[nMoney].picTexture;
            GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[nMoney].picIndex;
            GameInterface.TABLE_LIST.(row).td4.icon.offset = "3, 0";
            GameInterface.TABLE_LIST.(row).td4.icon.width = 32;
            GameInterface.TABLE_LIST.(row).td4.icon.height = 32;
            GameInterface.TABLE_LIST.(row).td4.textoffset = "31,0";
            GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[nMoney].name);
            GameInterface.TABLE_LIST.(row).index = nMoney;
            GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
            //GameInterface.TABLE_LIST.(row).td4.color = iColor;
            //GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY);
            //GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL);
            n++;
        }
	}
	int inbox = rightQty;
    int chritems = leftQty;
    for (i = 0; i< ITEMS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Items[i].id;
		leftQty  = GetCharacterFreeItem(refCharacter, sGood);
		rightQty = GetCharacterFreeItem(refChest, sGood);

		if (leftQty > 0 || rightQty > 0)
		{
			//// {*} BUHO-FIST - ADDED CODE - Filters at work.
			if (leftQty == 0 && FIT_FilterState == FIT_BACKPACK) continue;
			if (rightQty == 0 && FIT_FilterState == FIT_CHEST) continue;
			//// {*} BUHO END ADDITION

			GameInterface.TABLE_LIST.(row).td1.str = leftQty ;
			GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * sti(GameInterface.TABLE_LIST.(row).td1.str), 1);
			GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);

			GameInterface.TABLE_LIST.(row).td6.str = rightQty;

	        GameInterface.TABLE_LIST.(row).td4.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td4.icon.offset = "3, 0";
			GameInterface.TABLE_LIST.(row).td4.icon.width = 32;
			GameInterface.TABLE_LIST.(row).td4.icon.height = 32;
			GameInterface.TABLE_LIST.(row).td4.textoffset = "31,0";
			GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).index = i;
			GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
			//GameInterface.TABLE_LIST.(row).td4.color = iColor;
            //GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY);
			//GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL);
			n++;
		}
		inbox += rightQty;
        chritems += leftQty;
	}
    if(FIT_FilterState == FIT_BACKPACK && chritems == 0)
    {
        SetSelectable("TABLE_LIST", false);
    }
    else {
        if(FIT_FilterState == FIT_CHEST && inbox == 0)
            SetSelectable("TABLE_LIST", false);
        else
            SetSelectable("TABLE_LIST", true);
    }
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
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
    Table_UpdateWindow(sControl);
}

void ChangePosTable()
{
}
//// {*} BUHO-FIST - REPLACEMENT - ShowHelpHint.
void ShowHelpHint()
{
    string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";
	bool bCheckboxes = False;

	if (bShowChangeWin) return;

	string sNode = GetCurrentNode();

	switch (sNode)
	{
		case "CB_BACKPACK":		bCheckboxes = True; break;
		case "CB_ALL":			bCheckboxes = True; break;
		case "CB_TRADER":		bCheckboxes = True; break;
	}
	if (bCheckboxes)
	{
		sHeader = XI_ConvertString("titleFilter");
		sText1 = MsgIS("Chest_filter_hint_1");
        sText3 = MsgIS("Chest_filter_hint_2");
		sText2 = MsgIS("Chest_filter_hint_3");
	}
	else
	{
        sHeader = XI_ConvertString("titleItemsBox");
		sText1 = MsgIS("Trader_items_hint_1");
        sText3 = MsgIS("Trader_items_hint_2");
		sText2 = MsgIS("Trade_interface_hint_2");
	}
	CreateTooltip("#" + sHeader,
                  sText1, argb(255,255,255,255),
                  sText2, argb(255,192,192,192),
                  sText3, argb(255,255,255,255),
                  "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}
// {*} BUHO END REPLACEMENT

void EndTooltip()
{
	CloseTooltip();
    GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin)
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
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    string sRow = "tr" + (iSelected);
	SetCharWeight();
	SetVariable();
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	int _curCharIdx;

	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;

	int nNotUsed = 3;
	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	int m = 0;
	attributeName = "pic" + (m + 1);
	GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
	GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
	GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
	m++;

	for(i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		_curCharIdx = GetOfficersIndex(pchar, i);
		if(_curCharIdx!=-1 && _curCharIdx < MAX_CHARACTERS && characters[_curCharIdx].location == pchar.location)
		{
		    attributeName = "pic" + (m + 1);
            GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
            GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
            GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
            m++;
            nNotUsed--;
		}
	}
	if(nNotUsed < 0) nNotUsed = 0;
	GameInterface.CHARACTERS_SCROLL.NotUsed = nNotUsed;
	GameInterface.CHARACTERS_SCROLL.ListSize = m;
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
    sMaxGoodsStore = MsgIS("Chest");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FormatMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);
}

void ProcessFrame()
{
    int idxChar = -1;
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
        XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		idxChar = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
		//#20190528-01
		if(idxChar < 0 || idxChar >= MAX_CHARACTERS) return;
		refCharacter = &characters[idxChar];
		if(refCharacter.id == "0") return;
		SetDescription();
		//FillEquipInfo();
		FillCharacterInfo();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
	}
}
void FillCharacterInfo()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\\portraits\\256\\face_" + refCharacter.FaceId + ".tga.tx");
	GameInterface.strings.CharName = GetFullName(refCharacter);
}
void SetDescription()
{
 	if(GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "CHARACTERS_SCROLL." + attributeName))
		{
			SetCharWeight();
		}
	}
    CalculateInfoData();
	SetVariable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);

    fChestWeight = 0;
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

    iCurGoodsIdx = iGoodIndex;

    string describeStr = "";

    if (bBettaTestMode)
	{
	    describeStr += " id = " + Items[iGoodIndex].id + NewStr();
	}
	describeStr += GetItemDescribe(iGoodIndex);

	fWeight = stf(Items[iGoodIndex].weight);

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	if(iGoodIndex == nMoney) {
        iCharQty = sti(refCharacter.Money);
        iChestQty = sti(refChest.Money);
	}
	else {
        iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
        iChestQty = GetCharacterFreeItem(refChest, Items[iGoodIndex].id);
	}
	SetFormatedText("QTY_INFO_STORE_QTY", its(iChestQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

//// {*} BUHO-FIST - ADDED CODE - Checkboxes processing function.
void ProcessFilter(string sButton)
{
	switch (sButton)
	{
	case "CB_BACKPACK":
		/*
		Radio-button semantics:
		- If the button was selected the user is deselecting it, so reselect it and exit.
		- If the button was not selected, deselect all others, set the state variable and
		  reload the table.
		*/
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 1);
		if (FIT_FilterState != FIT_BACKPACK)
		{
			// Button being selected.
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
			FIT_FilterState = FIT_BACKPACK;
			AddToTable();
			GameInterface.TABLE_LIST.select = 1; GameInterface.TABLE_LIST.top = 0;
		}
		break;
	case "CB_ALL":
	    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1);
		if (FIT_FilterState != FIT_ALL)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
			FIT_FilterState = FIT_ALL;
			AddToTable();
			GameInterface.TABLE_LIST.select = 1; GameInterface.TABLE_LIST.top = 0;
		}
		break;
	case "CB_TRADER":
	    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1);
		if (FIT_FilterState != FIT_CHEST)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			FIT_FilterState = FIT_CHEST;
			AddToTable();
			GameInterface.TABLE_LIST.select = 1; GameInterface.TABLE_LIST.top = 0;
		}
		break;
	}
}
//// {*} BUHO END ADDITION

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
	if(iCurGoodsIdx == nMoney) {
        if (BuyOrSell == 1) // BUY
        {
            refChest.Money = sti(refChest.Money) - nTradeQuantity;
            refCharacter.Money = sti(refCharacter.Money) + nTradeQuantity);
        }
        else
        { // SELL
            refChest.Money = sti(refChest.Money) + nTradeQuantity;
            refCharacter.Money = sti(refCharacter.Money) - nTradeQuantity;
        }
	}
	else {
        if (BuyOrSell == 1) // BUY
        {            //#20180611-03
            if(Items[iCurGoodsIdx].id=="bookcrunch_3")
                pchar.ee1 = true;
            TakeNItems(refChest, Items[iCurGoodsIdx].id, -nTradeQuantity);
            TakeNItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
            //#20200218-01
            if(CheckAttribute(&Items[iCurGoodsIdx], "shown"))
                Items[iCurGoodsIdx].shown = false;
        }
        else
        { // SELL
            TakeNItems(refChest, Items[iCurGoodsIdx].id, nTradeQuantity);
            TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);
            //#20200218-01
            if(CheckAttribute(&Items[iCurGoodsIdx], "shown"))
                Items[iCurGoodsIdx].shown = true;
        }
	}
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx);
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float  iWeight;
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
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
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fChestWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fChestWeight - 0.01;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		    }
		    if (iCurGoodsIdx != nMoney && IsQuestUsedItem(Items[iCurGoodsIdx].id))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    SetFormatedText("QTY_TypeOperation", MsgIS("Leave"));
		    //SetFormatedText("QTY_Result", MsgIS("Gold") +" " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
			//                MsgIS("__weight") +" " + FloatToString(iWeight, 1) );
		}
		else
		{
			BuyOrSell = 1;
		    if (sti(GameInterface.qty_edit.str) > iChestQty)
		    {
		        GameInterface.qty_edit.str = iChestQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01;
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		    }
		    //if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.money))
		    //{
		    //    GameInterface.qty_edit.str = makeint(sti(pchar.money) / iCharPrice);
		    //    iWeight = fWeight * sti(GameInterface.qty_edit.str);
		    //}

			SetFormatedText("QTY_TypeOperation", MsgIS("Take"));
			//SetFormatedText("QTY_Result", MsgIS("Gold") + " " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
			//                MsgIS("__weight")+ " " + FloatToString(iWeight, 1) );
		}
	}
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iChestQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fChestWeight = fChestWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()
{
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()
{
    if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iChestQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()
{
    if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -1;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()
{
    if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = 1;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}
