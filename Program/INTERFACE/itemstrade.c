// boal 26/04/06 ����� �������� ����������
int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
bool nocheck = true;

bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
//ref refStore,
ref refCharacter, refStoreChar; // ������� �� (��) � ������
int iCharQty, iStoreQty, iCharPrice, iStorePrice;
float fWeight;
int  iCurGoodsIdx;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIT_ALL			0		// Normal
#define FIT_BACKPACK	1		// Show backpack
#define FIT_TRADER		2		// Show trader
int FIT_FilterState = 0;
//// {*} BUHO END ADDITION
//----------------------------------------------------------------------------------------------------------------
void InitInterface_R(string iniName, ref pTrader)
{
    StartAboveForm(true);

	refCharacter = pchar;
	refStoreChar = pTrader;
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = "���-��";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "������������ ���������";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = "��������� ��������";//XI_ConvertString("In the store");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = "���";
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;

    FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"CharName","",FONT_NORMAL,COLOR_MONEY, 405,108,SCRIPT_ALIGN_CENTER,1.0);
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
	SetEventHandler("ShowEquipWindow", "ShowEquipWindow", 0);
	SetEventHandler("ExitEquipWindow", "ExitEquipWindow", 0);
	SetEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo", 0);
	SetEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo", 0);
	SetEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo", 0);
	SetEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo", 0);
	SetEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo", 0);
	SetEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo", 0);
	SetEventHandler("ShowPatentEquipInfo", "ShowPatentEquipInfo", 0);

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleItemsTrade"));

	SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refStoreChar.FaceId) + ".tga");
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
    // boal �������� �� �������� 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	RefreshEquippedMaps(GetMainCharacter()); // �������� �����, ���� ������	
	// boal 21.01.2004 <--
	// �������� �������, �������� ������� -->
	int i, cn;
    for(i=1;i<=MAX_NUM_FIGHTERS;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			if (CheckAttribute(refCharacter, "skill.Fencing")) //boal fix ����� �� ����� ����� ��� ���������
			{
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BLADE_ITEM_TYPE));
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,CIRASS_ITEM_TYPE)); // boal 08.10.04 ����� ��������
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BACKPACK_ITEM_TYPE));
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,TALISMAN_ITEM_TYPE));
	        }
			if (CheckAttribute(refCharacter, "skill.Pistol") && GetCharacterSkill(refCharacter,"Pistol") > 0.1 )
			{
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,GUN_ITEM_TYPE));
			}
		}
	}
	// �������� �������, �������� ������� <--
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

	DelEventHandler("ShowEquipWindow", "ShowEquipWindow");
	DelEventHandler("ExitEquipWindow", "ExitEquipWindow");
	DelEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo");
	DelEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo");
	DelEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo");
	DelEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo");
	DelEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo");
	DelEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo");
	DelEventHandler("ShowPatentEquipInfo", "ShowPatentEquipInfo");
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
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sShipGroup;
	string sGood;
	int  idLngFile;
	int leftQty, rightQty;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);
														
	// ������� ���������� ��������
	for (i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
        row = "tr" + n;
		
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		sGood = Items[i].id;
		// �������� �� ����������, �� �� �������
		leftQty  = GetCharacterFreeItem(refCharacter, sGood);
		rightQty = GetCharacterFreeItem(refStoreChar, sGood);
		
		if (leftQty > 0 || rightQty > 0)
		{
			//// {*} BUHO-FIST - ADDED CODE - Filters at work.
			if (leftQty == 0 && FIT_FilterState == FIT_BACKPACK) continue;
			if (rightQty == 0 && FIT_FilterState == FIT_TRADER) continue;
			//// {*} BUHO END ADDITION
			GameInterface.TABLE_LIST.(row).td1.str = leftQty;
			GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * leftQty, 1);
			GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);
			
			GameInterface.TABLE_LIST.(row).td6.str = rightQty;
			
	        GameInterface.TABLE_LIST.(row).td4.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td4.icon.offset = "-2, 0";
			GameInterface.TABLE_LIST.(row).td4.icon.width = 20;
			GameInterface.TABLE_LIST.(row).td4.icon.height = 20;
			GameInterface.TABLE_LIST.(row).td4.textoffset = "20,0";
			GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).index = i;
			GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
            GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY);
			GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL);
			n++;
		}
	}
	
    for (i = 0; i < ITEMS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Items[i].id;
		// �������� �� ����������, �� �� �������
		leftQty  = GetCharacterFreeItem(refCharacter, sGood);
		rightQty = GetCharacterFreeItem(refStoreChar, sGood);

		if (leftQty > 0 || rightQty > 0)
		{
			//// {*} BUHO-FIST - ADDED CODE - Filters at work.
			if (leftQty == 0 && FIT_FilterState == FIT_BACKPACK) continue;
			if (rightQty == 0 && FIT_FilterState == FIT_TRADER) continue;
			//// {*} BUHO END ADDITION
			GameInterface.TABLE_LIST.(row).td1.str = leftQty ;
			GameInterface.TABLE_LIST.(row).td2.str = FloatToString(stf(Items[i].Weight) * sti(GameInterface.TABLE_LIST.(row).td1.str), 1);
			GameInterface.TABLE_LIST.(row).td7.str = FloatToString(stf(Items[i].Weight), 1);

			GameInterface.TABLE_LIST.(row).td6.str = rightQty;

	        GameInterface.TABLE_LIST.(row).td4.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td4.icon.offset = "-2, 0";
			GameInterface.TABLE_LIST.(row).td4.icon.width = 20;
			GameInterface.TABLE_LIST.(row).td4.icon.height = 20;
			GameInterface.TABLE_LIST.(row).td4.textoffset = "20,0";
			GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).index = i;
			GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
			//GameInterface.TABLE_LIST.(row).td4.color = iColor;
            GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(i, PRICE_TYPE_BUY);
			GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(i, PRICE_TYPE_SELL);
			n++;
		}
	}
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
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
	if(!nocheck) DoChange1();
}

void DoChange1()
{
	AddToTable();
	string row = "tr"+sti(GameInterface.TABLE_LIST.select);
	if (row != "tr0") ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(row).index));
	nocheck = true;
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
		sText1 = "�������� �������� �����: ���������� ������ �� ��������, ��� ���� � ���.";
        sText3 = "�������� �������� ��������: ���������� ������ �� ��������, ��� ���� � ��������.";
		sText2 = "�������� ��� ��������: ��������, ���������� ��� ���� ��������, ��� � �������� ��������.";
	}
	else
	{// ������� ������ �� ������ � ������
        sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = "������� ���� ���� ��� Enter �� ������� ������� �������� ����� �������/������� ��������. "+ newStr() +
		         "Shift + ����/����� �� ������� ������� ������������� �������� ����� � ����������������� ����������� �������/������� �� ������������. "+ newStr() +
				 "���� �������������� ���������� � ���������� ������������� ������� ��������, � �������������� (� �������) �������."+ newStr() +
				 "������� ����/����� �������� ���������� �� ������, � Shift + ����/����� �� ����������� ���������. ������� Enter �� ����� ����������� ��, � Esc - ������." + newStr() +
				 "�������� � ������ ����� � ����� ������ � ������� �������� �����/����, ����� ������������� �������� �������� ��� �������� �������.";

        sText3 = "� ������ �� ������� ����������� ������������� ���������� ��������.";
		sText2 = "������� ������� �����: ��������� �����/���� �� ������, Shift + �����, Enter";
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void EndTooltip()
{
	CloseTooltip(); // ������ �������, ���� ���
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
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool bOk;
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

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

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

        bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if (IsOfficer(&characters[_curCharIdx]))  // boal
			{
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
    sMaxGoodsStore = "��������"; //XI_ConvertString("store");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FindRussianMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);
}

void ProcessFrame()
{
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
        XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character)];
		SetDescription();
		//FillEquipInfo();
		FillCharacterInfo();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
	}
}
void FillCharacterInfo()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
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

    fStoreWeight = 0;
}
// ���� � ��������
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
	    if(CheckAttribute(arItm, "dmg_min.old") && CheckAttribute(arItm, "dmg_max.old"))
	    {
	    	describeStr += "OldDmgMin = " + sti(arItm.dmg_min.old) + ", OldDmgMax = "+sti(arItm.dmg_max.old) + newStr();
	    }
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

	iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);

	iStoreQty = GetCharacterFreeItem(refStoreChar, Items[iGoodIndex].id);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;

	iStorePrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_SELL);
    SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));

	iCharPrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_BUY);
	SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iCharPrice));
}

//// {*} BUHO-FIST - ADDED CODE - Checkboxes processing function.
void ProcessFilter(string sButton)
{
	nocheck = false;
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
		}
		break;
	case "CB_TRADER":
	    SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1);
		if (FIT_FilterState != FIT_TRADER)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			FIT_FilterState = FIT_TRADER;
			AddToTable();
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

 	if (BuyOrSell == 1) // BUY
	{
		TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, -nTradeQuantity);

		TakeNItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		//#20200218-01
        if(CheckAttribute(&Items[iCurGoodsIdx], "shown"))
            Items[iCurGoodsIdx].shown = false;
		moneyback = makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5);
		pchar.money = sti(pchar.money)  - moneyback;
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 700.0);
    	WaitDate("",0,0,0, 0, 1);
        // boal <--
	}
 	else
	{ // SELL
	    TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);
		//#20200218-01
        if(CheckAttribute(&Items[iCurGoodsIdx], "shown"))
            Items[iCurGoodsIdx].shown = true;
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5);
  		pchar.money = sti(pchar.money)  + moneyback;
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		// boal  check skill -->
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1000.0);
    	WaitDate("",0,0,0, 0, 1);
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
		    // �������� �� ����� ��������� -->
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - 0.01; // ���� ������
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // ����������
		    }
		    // �������� �� ����� ��������� <--
		    // ��������� �� ������� -->
		    if (IsQuestUsedItem(Items[iCurGoodsIdx].id))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    // ��������� �� ������� <--
		    SetFormatedText("QTY_TypeOperation", "�������");
		    SetFormatedText("QTY_Result", "������ " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", ��� " + FloatToString(iWeight, 1) );
		}
		else
		{
			BuyOrSell = 1;
	        // �������� �� ����� ��������� -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // ���� ������
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // ����������
		    }
		    if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.money))
		    {
		        GameInterface.qty_edit.str = makeint(sti(pchar.money) / iCharPrice);
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		    }
		    // �������� �� ����� ��������� <--

			SetFormatedText("QTY_TypeOperation", "������");
			SetFormatedText("QTY_Result", "������ " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", ��� " + FloatToString(iWeight, 1) );
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
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()  // ������� ���
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

void ADD_ALL_BUTTON()  // ������ ���
{
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

void ADD_BUTTON()  // ������
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


int GetTradeItemPrice(int itmIdx, int tradeType)
{
	int itmprice = 0;
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"price"))
	{
		itmprice = sti(Items[itmIdx].price);
	}

	float skillDelta = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)
	{
		skillModify = 1.4 - skillDelta*0.019;
		if(CheckAttribute(&Items[itmIdx],"groupID"))
		{
			if(Items[itmIdx].groupID == BLADE_ITEM_TYPE || Items[itmIdx].groupID == GUN_ITEM_TYPE) skillModify *= 10.0;
		}
		if(CheckOfficersPerk(pchar,"Trader")) { skillModify -= 0.05; }
		
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify -= 0.2; }
		else
		{
			if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.1; }
		}
	}
	else
	{
		skillModify = 0.75 + skillDelta*0.019;
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	skillModify += 0.05;
		if(CheckOfficersPerk(pchar,"Trader")) { skillModify += 0.05; }
	}

	return makeint(makefloat(itmprice)*skillModify);
}

// Lugger: Equip Info -->

void ExitEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", false);
	XI_WindowDisable("EQUIP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetNodeUsing("TABLE_LIST", true);
	SetNodeUsing("SCROLL_LIST", true);
	
	SetCurrentNode("TABLE_LIST");
}

void ShowEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", true);
	XI_WindowDisable("EQUIP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("TABLE_LIST", false);
	SetNodeUsing("SCROLL_LIST", false);

	SetCurrentNode("EQUIP_WINDOW");
		
	string sBlade = GetCharacterEquipByGroup(refCharacter, "blade");
	string sGun = GetCharacterEquipByGroup(refCharacter, "gun");
	string sSpyglass = GetCharacterEquipByGroup(refCharacter, "spyglass");
	string sCirass = GetCharacterEquipByGroup(refCharacter, "cirass");
	string sBackPack = GetCharacterEquipByGroup(refCharacter, "BackPack");
	string sTalisman = GetCharacterEquipByGroup(refCharacter, "talisman");
	string sPatent = GetCharacterEquipByGroup(refCharacter, "patent");
		
	if(CheckAttribute(refCharacter, "equip.blade") && refCharacter.equip.blade != "")
	{
		SetNewGroupPicture("EQUIP_BLADE_PIC", Items[FindItem(sBlade)].picTexture, "itm" + Items[FindItem(sBlade)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BLADE_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.gun") && refCharacter.equip.gun != "")
	{
		SetNewGroupPicture("EQUIP_GUN_PIC", Items[FindItem(sGun)].picTexture, "itm" + Items[FindItem(sGun)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_GUN_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.spyglass") && refCharacter.equip.spyglass != "")
	{
		SetNewGroupPicture("EQUIP_SPYGLASS_PIC", Items[FindItem(sSpyglass)].picTexture, "itm" + Items[FindItem(sSpyglass)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SPYGLASS_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.cirass") && refCharacter.equip.cirass != "")
	{
		SetNewGroupPicture("EQUIP_CIRASS_PIC", Items[FindItem(sCirass)].picTexture, "itm" + Items[FindItem(sCirass)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_CIRASS_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.BackPack") && refCharacter.equip.BackPack != "")
	{
		SetNewGroupPicture("EQUIP_BACKPACK_PIC", Items[FindItem(sBackPack)].picTexture, "itm" + Items[FindItem(sBackPack)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BACKPACK_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.talisman") && refCharacter.equip.talisman != "")
	{
		SetNewGroupPicture("EQUIP_TALISMAN_PIC", Items[FindItem(sTalisman)].picTexture, "itm" + Items[FindItem(sTalisman)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_TALISMAN_PIC", "none", "none");
	}
	
	if(CheckAttribute(refCharacter, "equip.patent") && refCharacter.equip.patent != "")
	{
		SetNewGroupPicture("EQUIP_PATENT_PIC", Items[FindItem(sPatent)].picTexture, "itm" + Items[FindItem(sPatent)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_PATENT_PIC", "none", "none");
	}
	
	SetFormatedText("EQUIP_CAPTION", XI_ConvertString("Equipment") + ": " + refCharacter.name + " " + refCharacter.lastname);	
}

void ShowBladeEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.blade"))
	{
		return;
	}
	if(refCharacter.equip.blade == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "blade");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowGunEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.gun"))
	{
		return;
	}
	if(refCharacter.equip.gun == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "gun");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowSpyglassEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.spyglass"))
	{
		return;
	}
	if(refCharacter.equip.spyglass == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "spyglass");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowBackPackEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.BackPack"))
	{
		return;
	}
	if(refCharacter.equip.BackPack == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "BackPack");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowTalismanEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.talisman"))
	{
		return;
	}
	if(refCharacter.equip.talisman == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "talisman");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowCirassEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.cirass"))
	{
		return;
	}
	if(refCharacter.equip.cirass == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "cirass");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowPatentEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.patent"))
	{
		return;
	}
	if(refCharacter.equip.patent == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	
	string sItem = GetCharacterEquipByGroup(refCharacter, "patent");
	ref itm = ItemsFromID(sItem);
		
	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);
	
	sText1 = GetItemDescribe(FindItem(sItem));
		
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}


void ClickSaber()
{
	ClickItem("BLADE");
}

void ClickGun()
{
	ClickItem("GUN");
}

void ClickSpyGlass()
{
	ClickItem("SPYGLASS");
}

void ClickCirass()
{
	ClickItem("CIRASS");
}

void ClickBackPack()
{
	ClickItem("BACKPACK");
}

void ClickTalisman()
{
	ClickItem("TALISMAN");
}

void ClickPatent()
{
	ClickItem("PATENT");
}

void ClickItem(string sItem)
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BLADE_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_GUN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_CIRASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SPYGLASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BACKPACK_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_TALISMAN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_PATENT_PIC", 5, 0);

	string sNode = "EQUIP_" + sItem + "_PIC";
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 5, 1);
}

// Lugger: Equip Info <--