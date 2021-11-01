// ��������� ������� ������ ���������
int	nCurScrollNumS = 0;
int iCurCompanion = 0;
int iCurGoodIndex;
string sCurGoodRow;

int	nCurScrollNumC = 0;
int iCurFighter = 0;
int iCurItemIndex;
string sCurItemRow;

bool isGoodTable;
int curBuyGoodsWeight;
float curBuyItemsWeight;

void InitInterface(string iniName)
{
	FillShipsScroll();
	FillCharactersScroll();//��������� � �������� ������� ����������
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);//���� ���� �������, �� ������������ ���������� ��������
	FillItemsTable();
	FillGoodsTable();
	SetCheckButtonsStates();

	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("MouseRClickUP","HideInfo", 0);
	SetEventHandler("CheckButtonChange", "ProcessCheckBox", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("UnShowWindow", "UnShowWindow", 0);
	SetEventHandler("ShowSAWindow", "ShowSAWindow", 0);
	SetEventHandler("SaveGOODSet", "SaveGOODSet", 0);
	SetEventHandler("LoadGOODSet", "LoadGOODSet", 0);
	SetEventHandler("SaveITEMSet", "SaveITEMSet", 0);
	SetEventHandler("LoadITEMSet", "LoadITEMSet", 0);
//ShowInfoWindow - �������� ���������� ������ ������ ��� ���������
}

void IDoExit(int exitCode)
{
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("evntDoPostExit", "DoPostExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("CheckButtonChange", "ProcessCheckBox");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("UnShowWindow", "UnShowWindow");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ShowSAWindow", "ShowSAWindow");
	DelEventHandler("SaveGOODSet", "SaveGOODSet");
	DelEventHandler("LoadGOODSet", "LoadGOODSet");
	DelEventHandler("SaveITEMSet", "SaveITEMSet");
	DelEventHandler("LoadITEMSet", "LoadITEMSet");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_GOODS_TRANSFER);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void HideInfo()
{
	CloseTooltip();
}

void SetCheckButtonsStates()
{
	String companionId = Characters[iCurCompanion].Id;
	
	if(CheckAttribute(Characters[iCurCompanion], "TransferGoods.BuyContraband"))
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, true);
	}
	else
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, false);
	}

	if(CheckAttribute(Characters[iCurCompanion], "TransferGoods.SellRestriction"))
	{
		CheckButton_SetState("CHECK_RESTRICTSELL", 1, true);
	}
	else
	{
		CheckButton_SetState("CHECK_RESTRICTSELL", 1, false);
	}

	if(CheckAttribute(Characters[iCurFighter], "TransferItems.SellRestriction"))
	{
		CheckButton_SetState("CHECK_RESTRICTSELL_I", 1, true);
	}
	else
	{
		CheckButton_SetState("CHECK_RESTRICTSELL_I", 1, false);
	}

	if(CheckAttribute(Characters[iCurFighter], "TransferItems.AutoBuyAmmo"))
	{
		CheckButton_SetState("CHECK_BUYAMMO", 1, true);
		SetNodeUsing("SETBUYAMMO", true);
	}
	else
	{
		CheckButton_SetState("CHECK_BUYAMMO", 1, false);
		SetNodeUsing("SETBUYAMMO", false);
	}
}

void ShowWindow(int WindowNum)
{
	switch (WindowNum)
	{
	case 0:
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", true);
		XI_WindowDisable("SETITEM_AUTO_WINDOW", true);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", false);
		XI_WindowShow("SETITEM_AUTO_WINDOW", false);
		SetCurrentNode("MAIN_BACK");
		break;
	case 1:
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", false);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", true);
		SetCurrentNode("TG_CANCEL_BUTTON");
		break;
	case 2:
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("SETITEM_AUTO_WINDOW", false);
		XI_WindowShow("SETITEM_AUTO_WINDOW", true);
		SetCurrentNode("SA_CANCEL_BUTTON");
		break;
	}
}

void UnShowWindow()
{
	ShowWindow(0);
}

void ShowTransferGoods()
{
	string describeStr = "";
	string sHeader;
	int buyCount;

	if (isGoodTable)
	{	//����� ������ ����� �������
		String sGood = Goods[iCurGoodIndex].name;
		SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "TG_GOODS_PICTURE", 6, "GOODS", sGood);//��������
		sHeader = XI_ConvertString(sGood);
		describeStr = GetAssembledString(GetConvertStr(sGood + "_descr", "GoodsDescribe.txt"), &Goods[iCurGoodIndex]);

		String companionId = Characters[iCurCompanion].Id;
		if (CheckAttribute(Characters[iCurCompanion], "TransferGoods." + sGood)) buyCount = sti(Characters[iCurCompanion].TransferGoods.(sGood)); else buyCount = 0;
	}
	else 
	{	//����� �������� ������ �������
		SetNewGroupPicture("TG_GOODS_PICTURE", Items[iCurItemIndex].picTexture, "itm" + Items[iCurItemIndex].picIndex);//��������
		String FighterId = Characters[iCurFighter].Id;
		string sItem = Items[iCurItemIndex].name;
		int	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
		sHeader = LanguageConvertString(lngFileID, sItem);
		LanguageCloseFile(lngFileID);
		describeStr = GetItemDescribe(iCurItemIndex);
		sItem = Items[iCurItemIndex].id;
		if (CheckAttribute(Characters[iCurFighter], "TransferItems." + sItem)) buyCount = sti(Characters[iCurFighter].TransferItems.(sItem)); else buyCount = 0;
	}
		SetFormatedText("TG_GOODS_CAPTION", sHeader);//���������
		SetFormatedText("TG_GOODS_INFO", describeStr);//��������
		GameInterface.TG_EDIT.str = buyCount;
}

void OnAddBtnClick(int _add)
{
	ref rGood;
	int iNum = MakeInt(GameInterface.TG_EDIT.str);;
	int _Units = 1;

	if (isGoodTable)
	{
	rGood = &Goods[iCurGoodIndex];
	_Units = sti(rGood.Units);
	_add = _add * abs(_add);
	}
	else
	{
	rGood = &Items[iCurItemIndex];
	}

	iNum = iNum + _add*_Units; 
	if(iNum < 0) iNum = 0;
	if (!isGoodTable && iNum > 200/stf(rGood.Weight)) iNum = 200/stf(rGood.Weight);
	if (isGoodTable && iNum > 15000/sti(rGood.Weight)*_Units) iNum = 15000/sti(rGood.Weight)*_Units;//�������� 15000 ����������������, ���� � 10000 ����� ���� ��
	GameInterface.TG_EDIT.str = iNum;
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	int iNum = 0;
	string sGood;
	int iTemp = 0;
	ref rGood;
	int iMult = 1;//������ ������� ��������� x5
	if (comName == "rclick") iMult=5;
	String companionId = Characters[iCurCompanion].Id;

	switch(nodName)
	{
		case "TG_ADD_ALL_BUTTON":
			OnAddBtnClick(10*iMult);
			break;
	
		case "TG_ADD_BUTTON":
			OnAddBtnClick(1*iMult);
			break;
			
		case "TG_REMOVE_ALL_BUTTON":
			OnAddBtnClick(-10*iMult);
			break;
			
		case "TG_REMOVE_BUTTON":
			OnAddBtnClick(-1*iMult);
			break;	
			
		case "TG_CANCEL_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				UnShowWindow();
			}
			break;

		case "SA_CANCEL_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				UnShowWindow();
			}
			break;

		case "SA_OK_BUTTON":
			if(comName == "click" || comName == "activate")
			{
//���� ��� ���������� �������� ���������� ���-�� �����������	
				UnShowWindow();
			}
			break;

		case "TG_OK_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				if (isGoodTable)
				{
					rGood = &Goods[iCurGoodIndex];
					sGood = rGood.name;
					if (!checkattribute(Characters[iCurCompanion],"TransferGoods." + sGood)) Characters[iCurCompanion].TransferGoods.(sGood) = 0;
					iNum =  sti(GameInterface.TG_EDIT.str);
					if (iNum >999999) iNum = 999999;
					curBuyGoodsWeight = curBuyGoodsWeight + (iNum - sti(Characters[iCurCompanion].TransferGoods.(sGood)))*stf(rGood.weight)/sti(rGood.Units);//��� ����� ���������� - ��� � ���
//���� �� ��� ���������? �����, �������� ��� �������� ��� ������� ���������, ���� ���������� �� ������?
					if (iNum == 0) DeleteAttribute(&Characters[iCurCompanion],"TransferGoods." + sGood); else Characters[iCurCompanion].TransferGoods.(sGood) = iNum; // �������� � ������ �������
					GameInterface.GOODS_TABLE_LIST.(sCurGoodRow).td2.str = iNum;
					Table_UpdateWindow("GOODS_TABLE_LIST");
					SetFormatedText("GOODS_SET_SUM", "��� ���������� ���������: " + curBuyGoodsWeight + " �.");
				}
				else 
				{
					String sItem = Items[iCurItemIndex].id;
					if (!checkattribute(Characters[iCurFighter],"TransferItems." + sItem)) Characters[iCurFighter].TransferItems.(sItem) = 0;
					iNum =  sti(GameInterface.TG_EDIT.str);
					if (iNum >9999) iNum = 9999;
					curBuyItemsWeight = curBuyItemsWeight + (iNum - sti(Characters[iCurFighter].TransferItems.(sItem)))*stf(Items[iCurItemIndex].weight);
//���� �� ��� ���������? �����, �������� ��� �������� ��� ������� ���������, ���� ���������� �� ������?
					if (iNum == 0) DeleteAttribute(&Characters[iCurFighter],"TransferItems." + sItem); else Characters[iCurFighter].TransferItems.(sItem) = iNum; // �������� � ������ �������
					GameInterface.CONSUME_TABLE_LIST.(sCurItemRow).td2.str = iNum;
					Table_UpdateWindow("CONSUME_TABLE_LIST");
					SetFormatedText("ITEMS_SET_SUM", "��� ���������� ���������: " + FloatToString(curBuyItemsWeight,1));
				}
				UnShowWindow();
			}
			break;
	}
}

void ProcessFrame()
{
	if (GetCurrentNode() == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current) != nCurScrollNumS)
		{
			nCurScrollNumS = sti(GameInterface.SHIPS_SCROLL.current);
			FillGoodsTable();
			SetCheckButtonsStates();
			//SetDescription(); //TODO - ��������� �������� ���������� - ����� ����� � ���������������� � �.�.
		}
	}

	if (GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		if (sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNumC)
		{
			nCurScrollNumC = sti(GameInterface.CHARACTERS_SCROLL.current);
			FillItemsTable();
			SetCheckButtonsStates();
		}
	}
}

void ProcessCheckBox()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
	string companionId = Characters[iCurCompanion].Id;
//========================================//
	if (sControl == "CHECK_BUYCONTRABAND")
	{
	if (iNewState) Characters[iCurCompanion].TransferGoods.BuyContraband = true; 
		else DeleteAttribute(&Characters[iCurCompanion], "TransferGoods.BuyContraband");
	return;
	}
//========================================//
	if (sControl == "CHECK_RESTRICTSELL")
	{
	if (iNewState) Characters[iCurCompanion].TransferGoods.SellRestriction = true; 
		else DeleteAttribute(&Characters[iCurCompanion], "TransferGoods.SellRestriction");
	return;
	}
//========================================//
	if (sControl == "CHECK_RESTRICTSELL_I")
	{
	if (iNewState) Characters[iCurFighter].TransferItems.SellRestriction = true; 
		else DeleteAttribute(&Characters[iCurFighter], "TransferItems.SellRestriction");
	return;
	}
//========================================//
	if (sControl == "CHECK_BUYAMMO")
	{
	if (iNewState) Characters[iCurFighter].TransferItems.AutoBuyAmmo = true;
		else DeleteAttribute(&Characters[iCurFighter], "TransferItems.AutoBuyAmmo");
	SetNodeUsing("SETBUYAMMO", iNewState); 
	FillItemsTable();//TODO - ���������, ��� ��� ���� ������� �� ����������� ��� ����� ���������, ���� �������� ��������� ������� ��������
	return;
	}
//========================================//
}
//TO DO - ����� ���� ��������??? ����� ���� ����������� ��������� ��� �����������
//TO DO - ���������� ����� ���������� ���������� �� ��� �� ��������
//TO DO - ���������� ����� ���������� �������� �� ��� �� ��������
//TO DO - ������� �������� � ������ ����������� ������� � ����������� ��� ������� ��������� - ������� ����� � �� �����������, ����� �������� � ��� ����������� � �.�. - ��� ������������ ������� ���
//������ � ��������� ��� ����������� �������
//������� ������ � ������� �� �������� ����� ���

void ShowItemInfo()
{
	if (GetCurrentNode() == "GOODS_TABLE_LIST") isGoodTable = true; else isGoodTable = false;
	ShowWindow(1);
	ShowTransferGoods();
}
void ShowSAWindow()
{
	ShowWindow(2);
//����, � ���� ��������� ����������� � ���������� ������ ����� �������� ��� ����� ��������� ����� ��������, ���� ���������� - �� ����������� ��� ����� �������? 
//����� �������� ������ �� ������ ����������?? ����� ������������ � ��� �������� ���� � ��� 
//����������� - ��������� �������� �������� ���� ��� ����� �������������� �������, � ����� ������������ �����
	AutoCalcAmmo(&Characters[iCurFighter]);
}

void FillShipsScroll()
{
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", COMPANION_MAX);
	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current")) GameInterface.SHIPS_SCROLL.current = 0;
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

void FillGoodsTable()
{
	string sGood, sItem, row;
	int i, n, buyCount, buyCount2;
	string attributeName = "pic" + (nCurScrollNumS+1);
	iCurCompanion = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
	String companionId = Characters[iCurCompanion].Id;
	ref refCharacter = characterFromID(companionId);
	SetNewPicture("CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
	SetFormatedText("SHIP_NAME", XI_ConvertString(RealShips[sti(refCharacter.Ship.Type)].BaseName) + " '" + refCharacter.Ship.Name + "'");
	SetFormatedText("COMP_NAME", GetFullName(refCharacter));
	Table_Clear("GOODS_TABLE_LIST", false, true, false);
	GameInterface.GOODS_TABLE_LIST.hr.td1.str = "�����";
	GameInterface.GOODS_TABLE_LIST.hr.td2.str = "���-��";
	GameInterface.GOODS_TABLE_LIST.hr.td3.str = "� ���-\n�������";//"����-\n������";
	GameInterface.GOODS_TABLE_LIST.hr.td4.str = "���/\n�����";
	GameInterface.GOODS_TABLE_LIST.hr.td5.str = "����\n��. ����\n(�������)";
	GameInterface.GOODS_TABLE_LIST.hr.td5.scale = 0.8;
	curBuyGoodsWeight = 0;

	for (i = 0, n = 1, bool isDone = 0; i< GOODS_QUANTITY; i++)
	{
//��� ����� �������� ��������� � ������� //�������, ���� �� �����������: ����� �� ��������, ���� � ������� �������� ������� �������
		if (i==6) i = 16;
		if (i==16 && isDone) continue;
		if (i==17 && !isDone) {i=6; isDone = 1;}
		row = "tr" + n;
		sGood = Goods[i].name;
		if (checkattribute(Goods[i],"CannonIdx")) continue;//��� �����???

		GameInterface.GOODS_TABLE_LIST.(row).index = i;
		GameInterface.GOODS_TABLE_LIST.(row).td1.icon.group = "GOODS";
		GameInterface.GOODS_TABLE_LIST.(row).td1.icon.image = sGood;
		GameInterface.GOODS_TABLE_LIST.(row).td1.icon.offset = "-3, -1";
		GameInterface.GOODS_TABLE_LIST.(row).td1.icon.width = 42;
		GameInterface.GOODS_TABLE_LIST.(row).td1.icon.height = 42;
		GameInterface.GOODS_TABLE_LIST.(row).td1.textoffset = "39,0";
		GameInterface.GOODS_TABLE_LIST.(row).td1.str = XI_ConvertString(sGood);
		GameInterface.GOODS_TABLE_LIST.(row).td1.align = "left";
		if (CheckAttribute(Characters[iCurCompanion], "TransferGoods." + sGood)) buyCount = sti(Characters[iCurCompanion].TransferGoods.(sGood)); else buyCount = 0;
		GameInterface.GOODS_TABLE_LIST.(row).td2.str = buyCount;
		buyCount2 = GetConsumeLimit(Characters[iCurCompanion], sGood);
		GameInterface.GOODS_TABLE_LIST.(row).td3.str = buyCount2;
		if (!buyCount2) GameInterface.GOODS_TABLE_LIST.(row).td3.color = argb(255,160,160,160);
		GameInterface.GOODS_TABLE_LIST.(row).td4.str = Goods[i].Weight + " / " + Goods[i].Units;//���/�����
		GameInterface.GOODS_TABLE_LIST.(row).td5.str = sti(Goods[i].Cost)/sti(Goods[i].Weight) + "\n(" + Goods[i].Cost + ")";
		curBuyGoodsWeight = curBuyGoodsWeight + (buyCount+buyCount2)*stf(Goods[i].Weight)/sti(Goods[i].Units);
		n++;
	}
	GameInterface.GOODS_TABLE_LIST.select = 0;
	Table_UpdateWindow("GOODS_TABLE_LIST");
	SetFormatedText("GOODS_SET_SUM", "��� ���������� ���������: " + curBuyGoodsWeight + " �.");
}

void FillItemsTable()
{
	string sItem, row;
	int i, n, buyCount, buyCount2;
	string attributeName = "pic" + (nCurScrollNumC+1);
	iCurFighter = GameInterface.CHARACTERS_SCROLL.(attributeName).character;
	string FighterId = Characters[iCurFighter].Id;
	SetFormatedText("CHAR_NAME", GetFullName(Characters[iCurFighter]));
	
	Table_Clear("CONSUME_TABLE_LIST", false, true, false);
	GameInterface.CONSUME_TABLE_LIST.hr.td1.str = "�������";
	GameInterface.CONSUME_TABLE_LIST.hr.td2.str = "���-��";
	GameInterface.CONSUME_TABLE_LIST.hr.td3.str = "� ���-\n�������";//"����-\n������";
	GameInterface.CONSUME_TABLE_LIST.hr.td4.str = "���";
	curBuyItemsWeight = 0;

	for(i = 0, n = 1; i < ITEMS_QUANTITY; i++)
	{
		if (!checkattribute(Items[i],"sortIndex"))
		{
			if (!HasSubStr(Items[i].id,"CompCraft")) continue;//� ������ ������ ����������
		}
		else 
		{
			if (Items[i].SortIndex == 1 || Items[i].SortIndex == 2 || Items[i].ItemType == "CRAFTCOMPONENTS") {} 
			else continue; //� ������ ���������� � �����
			
		}
		//��, ��������, ����� �������� ������ ��������� � ������� ���������... �� ���� ������ ��������� ����������� �����, � ��� ���������� ����� �� ��������� ��������������
		if (Items[i].id == "Lockpick") continue;//������� ����������
		if (Items[i].id == "CompCraft_Tools" || Items[i].id == "CompCraft_Locksmith" || Items[i].id == "CompCraft_Puleleyka") continue; //���������� ��������� ����� ����
		row = "tr" + n;

		GameInterface.CONSUME_TABLE_LIST.(row).index = i;
		GameInterface.CONSUME_TABLE_LIST.(row).td1.icon.group = Items[i].picTexture;
		GameInterface.CONSUME_TABLE_LIST.(row).td1.icon.image = "itm" + Items[i].picIndex;
		GameInterface.CONSUME_TABLE_LIST.(row).td1.icon.offset = "-2,0";
		GameInterface.CONSUME_TABLE_LIST.(row).td1.icon.width = 40;
		GameInterface.CONSUME_TABLE_LIST.(row).td1.icon.height = 40;
		GameInterface.CONSUME_TABLE_LIST.(row).td1.textoffset = "40,0";
		GameInterface.CONSUME_TABLE_LIST.(row).td1.align = "left";
		GameInterface.CONSUME_TABLE_LIST.(row).td1.str = GetConvertStr(Items[i].name, "ItemsDescribe.txt");
		sItem = Items[i].id;
		if (CheckAttribute(Characters[iCurFighter], "TransferItems." + sItem)) buyCount = sti(Characters[iCurFighter].TransferItems.(sItem)); else buyCount = 0;
		GameInterface.CONSUME_TABLE_LIST.(row).td2.str = buyCount;
		buyCount2 = GetConsumeLimit(Characters[iCurFighter], sItem);
		GameInterface.CONSUME_TABLE_LIST.(row).td3.str = buyCount2;
		if (!buyCount2) GameInterface.CONSUME_TABLE_LIST.(row).td3.color = argb(255,160,160,160);
		GameInterface.CONSUME_TABLE_LIST.(row).td4.str = FloatToString(stf(Items[i].Weight), 1);
		curBuyItemsWeight = curBuyItemsWeight + (buyCount+buyCount2)*stf(Items[i].Weight);
		n++;
	}
	GameInterface.CONSUME_TABLE_LIST.select = 0;
	Table_UpdateWindow("CONSUME_TABLE_LIST");
	SetFormatedText("ITEMS_SET_SUM", "��� ���������� ���������: " + FloatToString(curBuyItemsWeight,1));
}

void TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	string sRow = "tr" + (iSelected);

	switch (sControl)
	{
		case "GOODS_TABLE_LIST": iCurGoodIndex = sti(GameInterface.GOODS_TABLE_LIST.(sRow).index); sCurGoodRow = sRow; break;
		case "CONSUME_TABLE_LIST": iCurItemIndex = sti(GameInterface.CONSUME_TABLE_LIST.(sRow).index); sCurItemRow = sRow; break;
	}
}

int GetConsumeLimit(ref xi_refCharacter, string _itemname)//TODO - ������� � �������, ��� ��� � � ������ ����������� ������ ����������//��������� �� ��� ������� - ������/��������
{
	return 0;
}

void AutoCalcAmmo(ref xi_refCharacter)
{
}

void SaveGOODSet(){return;}
void LoadGOODSet(){return;}
void SaveITEMSet(){return;}
void LoadITEMSet(){return;}