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
int FIT_FilterState;
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

	if (checkattribute(pchar, "ItemTradeFilter")) FIT_FilterState = sti(pchar.ItemTradeFilter); else FIT_FilterState = 0; 
	switch (FIT_FilterState)
	{
	case FIT_ALL: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1); break;
	case FIT_BACKPACK: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 1); break;
	case FIT_TRADER: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1); break;
	}

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
	SetEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo", 0);
	SetEventHandler("Show1EquipInfo", "Show1EquipInfo", 0);
	SetEventHandler("Show2EquipInfo", "Show2EquipInfo", 0);
	SetEventHandler("Show3EquipInfo", "Show3EquipInfo", 0);
	SetEventHandler("Show4EquipInfo", "Show4EquipInfo", 0);
	SetEventHandler("Show5EquipInfo", "Show5EquipInfo", 0);
	SetEventHandler("Autotrade_All", "Autotrade_All", 0);
	SetEventHandler("Autotrade_This", "Autotrade_This", 0);

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleItemsTrade"));

	switch (refCharacter.sex)
	{
		case "man": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
		break;
		case "woman": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
		break;
		case "skeleton": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
		break;
	}

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
	pchar.ItemTradeFilter = FIT_FilterState; 
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
	DelEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo");
	DelEventHandler("Show1EquipInfo", "Show1EquipInfo");
	DelEventHandler("Show2EquipInfo", "Show2EquipInfo");
	DelEventHandler("Show3EquipInfo", "Show3EquipInfo");
	DelEventHandler("Show4EquipInfo", "Show4EquipInfo");
	DelEventHandler("Show5EquipInfo", "Show5EquipInfo");
	DelEventHandler("Autotrade_All", "Autotrade_All");
	DelEventHandler("Autotrade_This", "Autotrade_This");

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
	int n, i, iTemp;
	string row, sShipGroup;
	string sGood, sTemp;
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

			iTemp = CheckItemInSets(refCharacter, sGood);
			if (iTemp > 0) 
			{
				GameInterface.TABLE_LIST.(row).td4.str = GameInterface.TABLE_LIST.(row).td4.str + " (�" + iTemp + ")"; 
				//sTemp = "Set" + iTemp;
				//GameInterface.TABLE_LIST.(row).td4.str = GameInterface.TABLE_LIST.(row).td4.str + " (" + refCharacter.(sTemp).nameset + ")"; 
				GameInterface.TABLE_LIST.(row).td4.color = argb(255,196,196,255);//������������ �������� �� ����������
				GameInterface.TABLE_LIST.(row).td1.color = argb(255,196,196,255);
			}

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
		if (IsQuestUsedItem(Items[i].id)) continue;
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

			iTemp = CheckItemInSets(refCharacter, sGood);
			if (iTemp > 0) 
			{
				GameInterface.TABLE_LIST.(row).td4.str = GameInterface.TABLE_LIST.(row).td4.str + " (�" + iTemp + ")"; 
				//sTemp = "Set" + iTemp;
				//GameInterface.TABLE_LIST.(row).td4.str = GameInterface.TABLE_LIST.(row).td4.str + " (" + refCharacter.(sTemp).nameset + ")"; 
				GameInterface.TABLE_LIST.(row).td4.color = argb(255,196,196,255);//������������ �������� �� ����������
				GameInterface.TABLE_LIST.(row).td1.color = argb(255,196,196,255);
			}

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
	//AddToTable();
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
		sText1 = "�������� �����: ���������� ������ �� ��������, ��� ���� � ���.";
		sText3 = "�������� ��������: ���������� ������ �� ��������, ��� ���� � ��������.";
		sText2 = "��� ��������: ��������, ���������� ��� ���� ��������, ��� � �������� ��������.";
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
		switch (refCharacter.sex)
		{
			case "man": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
			break;
			case "woman": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
			break;
			case "skeleton": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
			break;
		}
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
	ref	arItm = &Items[iGoodIndex];
	int	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
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

// Lugger: Equip Info -->

void ExitEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", false);
	XI_WindowDisable("EQUIP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetNodeUsing("TABLE_LIST", true);
	SetNodeUsing("SCROLL_LIST", true);

	SetNodeUsing("CB_BACKPACK", true);//TO DO - ������ �������� ��������? ������� ������� ���������� ��������, �� �� ��������� ���������� �� �����. ������ ������� ��������
	SetNodeUsing("CB_ALL", true);
	SetNodeUsing("CB_TRADER", true);
	SetNodeUsing("AUTOTRADE_ALL", true);

	SetCurrentNode("TABLE_LIST");

}

void ShowEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", true);
	XI_WindowDisable("EQUIP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("TABLE_LIST", false);
	SetNodeUsing("SCROLL_LIST", false);

	SetNodeUsing("CB_BACKPACK", false);
	SetNodeUsing("CB_ALL", false);
	SetNodeUsing("CB_TRADER", false);
	SetNodeUsing("AUTOTRADE_ALL", false);

	SetCurrentNode("EQUIP_WINDOW");

	string sBlade = GetCharacterEquipByGroup(refCharacter, "blade");
	string sGun = GetCharacterEquipByGroup(refCharacter, "gun");
	string sSpyglass = GetCharacterEquipByGroup(refCharacter, "spyglass");
	string sCirass = GetCharacterEquipByGroup(refCharacter, "cirass");
	string sBackPack = GetCharacterEquipByGroup(refCharacter, "BackPack");
	string sTalisman = GetCharacterEquipByGroup(refCharacter, "talisman");
	string sBook = GetCharacterEquipByGroup(refCharacter, "book");
	string sShow1 = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_left");
	string sShow2 = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_right");
	string sShow3 = GetCharacterEquipByGroup(refCharacter, "indian_center");
	string sShow4 = GetCharacterEquipByGroup(refCharacter, "idols_left");
	string sShow5 = GetCharacterEquipByGroup(refCharacter, "idols_right");

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

	if(CheckAttribute(refCharacter, "equip.book") && refCharacter.equip.book != "")
	{
		SetNewGroupPicture("EQUIP_BOOK_PIC", Items[FindItem(sBook)].picTexture, "itm" + Items[FindItem(sBook)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BOOK_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.jewelry_indian_left") && refCharacter.equip.jewelry_indian_left != "")
	{
		SetNewGroupPicture("EQUIP_SHOW1_PIC", Items[FindItem(sShow1)].picTexture, "itm" + Items[FindItem(sShow1)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW1_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.jewelry_indian_right") && refCharacter.equip.jewelry_indian_right != "")
	{
		SetNewGroupPicture("EQUIP_SHOW2_PIC", Items[FindItem(sShow2)].picTexture, "itm" + Items[FindItem(sShow2)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW2_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.indian_center") && refCharacter.equip.indian_center != "")
	{
		SetNewGroupPicture("EQUIP_SHOW3_PIC", Items[FindItem(sShow3)].picTexture, "itm" + Items[FindItem(sShow3)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW3_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.idols_left") && refCharacter.equip.idols_left != "")
	{
		SetNewGroupPicture("EQUIP_SHOW4_PIC", Items[FindItem(sShow4)].picTexture, "itm" + Items[FindItem(sShow4)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW4_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.idols_right") && refCharacter.equip.idols_right != "")
	{
		SetNewGroupPicture("EQUIP_SHOW5_PIC", Items[FindItem(sShow5)].picTexture, "itm" + Items[FindItem(sShow5)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW5_PIC", "none", "none");
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

void ShowBookEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.book"))
	{
		return;
	}
	if(refCharacter.equip.book == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "book");
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

void Show1EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.jewelry_indian_left"))
	{
		return;
	}
	if(refCharacter.equip.jewelry_indian_left == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_left");
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

void Show2EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.jewelry_indian_right"))
	{
		return;
	}
	if(refCharacter.equip.jewelry_indian_right == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_right");
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

void Show3EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.indian_center"))
	{
		return;
	}
	if(refCharacter.equip.indian_center == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "indian_center");
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

void Show4EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.idols_left"))
	{
		return;
	}
	if(refCharacter.equip.idols_left == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "idols_left");
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

void Show5EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.idols_right"))
	{
		return;
	}
	if(refCharacter.equip.idols_right == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "idols_right");
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

void ClickBook()
{
	ClickItem("BOOK");
}

void ClickShow1()
{
	ClickItem("SHOW1");
}

void ClickShow2()
{
	ClickItem("SHOW2");
}

void ClickShow3()
{
	ClickItem("SHOW3");
}

void ClickShow4()
{
	ClickItem("SHOW4");
}

void ClickShow5()
{
	ClickItem("SHOW5");
}

void ClickItem(string sItem)
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BLADE_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_GUN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_CIRASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SPYGLASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BACKPACK_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_TALISMAN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BOOK_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW1_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW2_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW3_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW4_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW5_PIC", 5, 0);

	string sNode = "EQUIP_" + sItem + "_PIC";
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 5, 1);
}

// Lugger: Equip Info <--

void Autotrade_All()
{
	if (!IsPCharHaveTreasurer()) {Log_Info("��� ��������. ������� ������ ���������!"); return;}
	int iOfficer = -1;
	ref _chr;

	for(int z = 0; z < MAX_NUM_FIGHTERS+6; z++)
	{
		iOfficer = GetOfficersIndex(pchar, z);
		if(iOfficer != -1)
		{
			_chr = &characters[iOfficer];
			SellExcessConsume(_chr);
		}
	}
	for(z = 0; z < MAX_NUM_FIGHTERS+6; z++)
	{
		iOfficer = GetOfficersIndex(pchar, z);
		if(iOfficer != -1)
		{
			_chr = &characters[iOfficer];
			BuyConsume(_chr);
		}
	}
//����� ������� ������� ��������� �� ����, � ����� �������� - ��� �������� "����������" ������� ����� ��������. �� ��� ����� �������� ������ �� ������� ���.
//TO DO - � ����� ������� - ��� ����� �� ��������, � ������ - ���������. ����� �������� �������� ������������ ������������ �������� ����� ����������???

	AddToTable();
	EndTooltip();
}

void Autotrade_This()
{
	if (!IsPCharHaveTreasurer()) {Log_Info("��� ��������. ������� ������ ���������!"); return;}
	SellExcessConsume(refCharacter);
	BuyConsume(refCharacter);
	AddToTable();
	EndTooltip();
}

void BuyConsume(ref chr)
{
	int 	qty = 0;
	int 	i, n, iCost;
	int		curqty = 0;
	int		curTraderQty = 0;
	int		iMoneyQty = 0;
	string 	itemname = "";
	bool	bAdded, bNotEnough, bNotOverWeight, bNotEnoughTrader;
	float	freeWeight, fItemWeight;

//if (CheckAttribute(chr,"fighter") || z == 0)

	string sTemp = "";
	if (chr.sex == "woman") sTemp = "�";

	freeWeight = GetMaxItemsWeight(chr) - GetItemsWeight(chr);
	if (freeWeight < 0.1)
	{
		Log_Info(GetFullName(chr) + " ����������" + sTemp + ". ��������� ���������� �� �������.");
		return;
	}

	bAdded = false;//����� �� ���� ���� ������� ��������
	bNotOverWeight = false;//������� �� ����� � ���������
	bNotEnough = false;//������� �� ��� �����
	bNotEnoughTrader = false;//������� �� � ��������

	for(i = 0, n = 1; i < ITEMS_QUANTITY; i++)
	{
		if (!checkattribute(Items[i],"sortIndex")) continue;//� ������ ������ ����������
		itemname = Items[i].id;
		if (itemname == "Lockpick") continue;//������� ����������
		curTraderQty = GetCharacterItem(refStoreChar, itemname);

//if (curTraderQty == 0) continue;//� �������� ������ ���, ����� ��������� �������//TO DO - ���� ��� ��� ����������� �������� �� �������
//row = "tr" + n;
		if (checkattribute(chr,"TransferItems."+itemname)) qty = sti(chr.TransferItems.(itemname)); else qty = 0;
		qty = qty + GetConsumeLimit(chr, itemname);
		//if (qty == 0) continue; //������ �� ��������� ��������
		curqty = GetCharacterItem(chr,itemname);
		if (qty > curqty) {qty = qty - curqty;}
			else continue;//����� ������� ��� ���� ����������
//TO DO - ����� �� ������ ������ ��� �������� ����������, ���� ������� �� ����� ������ ���� ������� �������
//Log_TestInfo("������� - " + itemname + "|" + qty + "|" + curqty + "|" + curTraderQty);
		if (qty > curTraderQty) {qty = curTraderQty; bNotEnoughTrader = true;}//TO DO - ���� ��� ��� ����������� �������� �� �������
		if (qty == 0) continue; //������ ������ � ��������

		bNotEnough = true;//���� ���� ����� ���� ��� �� ����, ������ ����-�� �� ������� �� ������

		fItemWeight = stf(Items[GetItemIndex(itemname)].weight);
		if (qty > makeint(freeWeight / fItemWeight)) qty = makeint(freeWeight / fItemWeight);
		if (qty == 0) continue; //�� ������� ����� ���� ��� ������ ������ ��������
		bNotOverWeight = true;//������� ����� ���� �� ��� ������ ��������

		iCost = GetTradeItemPrice(Items_FindItemIdx(itemname), PRICE_TYPE_BUY);
		if (qty > sti(PChar.Money) / iCost)) qty = sti(PChar.Money) / iCost;//TO DO - ����� - ������������� ������� � ���������� - ��� ����� �������� �� ���� ������� ������, ��� ���� ����� � �������. 
		if (qty == 0) continue; //�� ������� ����� ���� �� ���� ����� �������

		iMoneyQty -= iCost*qty;
		TakeNItems(chr, itemname, qty);
		TakeNItems(refStoreChar, itemname, -qty);
		//WaitDate("", 0, 0, 0, 0, 1);// ������ ����� �� ������ ����� - ��������� ��� ������� �� ������
		freeWeight -= fItemWeight*qty;
		bAdded = true;//���-�� ������� ��������
	}

	if(iMoneyQty != 0) // ���� ���� ���-�� ������
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		ref rTreasurer = GetPCharTreasurerRef();//��������. ��� ���� �����
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) //������������ � ���, ��� ���� �� �������� ������� ��������, � �� �����?
		//TO DO - ��� ���������� ����� �� �������� ��������, �������������, ��� �� �������� ������� �� ���
	}

	if (bAdded) 		{Log_Info(GetFullName(chr)+" ��������" + sTemp + " �������� �����������.");	return;}
	if (bNotOverWeight)	{Log_Info(GetFullName(chr)+" �� �������" + sTemp + " ����� �����������. ��������� ������."); return;}
	if (bNotEnough) 	{Log_Info(GetFullName(chr)+" �� �������" + sTemp + " ����� ����������� ��-�� ���������."); return;}
	if (bNotEnoughTrader) 	{Log_Info(GetFullName(chr)+" �� �������" + sTemp + " ����� �����������. �� ���� � ������� � ��������."); return;}
						 Log_Info(GetFullName(chr)+" ��� ����" + sTemp + " ������ �������� �����������.");
	//TO DO - ������� ��������� � �������� ����� ����������
	//TO DO - ���������� ������� ������� �� ����������� ����� ������ ������� � �������� - ���������, �� � ������� ������ � ������� ���� ��������� ����
}

void SellExcessConsume(ref chr)
{
	if (!checkattribute(chr,"TransferItems.SellRestriction")) return;//�� �������� ���������� ���������
	int 	qty = 0;
	int 	i, n, iCost;
	int		curqty = 0;
	int		iMoneyQty = 0;
	string 	itemname = "";

	string sTemp = "";
	if (chr.sex == "woman") sTemp = "�";

	for(i = 0, n = 1; i < ITEMS_QUANTITY; i++)
	{
		if (!checkattribute(Items[i],"sortIndex")) continue;//� ������ ������ ����������
		itemname = Items[i].id;
		if (itemname == "Lockpick") continue;//������� ����������
		if (checkattribute(chr,"TransferItems."+itemname)) qty = sti(chr.TransferItems.(itemname)); else qty = 0;
		qty = qty + GetConsumeLimit(chr, itemname);
		curqty = GetCharacterItem(chr,itemname);
		if (curqty > qty) qty = curqty - qty; else continue;
		iCost = GetTradeItemPrice(Items_FindItemIdx(itemname), PRICE_TYPE_SELL);
		iMoneyQty += iCost*qty;
		TakeNItems(chr, itemname, -qty);
		TakeNItems(refStoreChar, itemname, qty);
		//WaitDate("", 0, 0, 0, 0, 1);// ������ ����� �� ������ ����� - ��������� ��� ������� �� ������
	}
	if(iMoneyQty != 0) // ���� ���� ���-�� �������
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		ref rTreasurer = GetPCharTreasurerRef();//��������. ��� ���� �����
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) //������������ � ���, ��� ���� �� �������� ������� ��������, � �� �����?
		//TO DO - ��� ���������� ����� �� �������� ��������, �������������, ��� �� �������� ������� �� ���
		//TO DO - ��������� ���� �������� ����� �� ������ �������� � ����� ���� �� ������ ����� - ���� �� ��� ������? �������� ���� �� ������ ������� ��� � ��������� ������� ��������� ����� �� ����� ������?
		Log_Info(GetFullName(chr)+" ������" + sTemp + " ������� �����������.");
	}
}

int GetConsumeLimit(ref chr, string _itemname)
{
	return 0;
}

void AddResult(string sTableName, string Result, bool isFail)
{

}