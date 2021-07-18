// Интерфейс закупки товара казначеем
int	nCurScrollNumS = 0;
int iCurCompanion = 0;
int iCurGoodIndex;
string sCurGoodRow;

int	nCurScrollNumC = 0;
int iCurFighter = 0;
int iCurItemIndex;
string sCurItemRow;

bool isGoodTable;

void InitInterface(string iniName)
{
	FillShipsScroll();
	FillCharactersScroll();//перенести и просмотр одетого снаряжения
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);//не знаю, что, но если выше ставить, не показываются портретики офицеров, обновляет интерфейс???
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
	SetEventHandler("UnShowTGWindow", "UnShowTGWindow", 0);
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
	
	if(CheckAttribute(PChar, "SellRestriction"))
	{
		CheckButton_SetState("CHECK_RESTRICTSELL", 1, false);//меняю логику - если есть атрибут, то запрет выключен
	}
	else
	{
		CheckButton_SetState("CHECK_RESTRICTSELL", 1, true);
	}
}

void ShowMainWindow(bool _truefalse)
{
	if(_truefalse)
	{	// Видим главное окно
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", true);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", false);
		SetCurrentNode("MAIN_BACK");
	}
	else
	{
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("GOODS_TRANSFER_WINDOW", false);
		XI_WindowShow("GOODS_TRANSFER_WINDOW", true);
		SetCurrentNode("TG_CANCEL_BUTTON");
	}
}

void UnShowTGWindow()
{
	ShowMainWindow(true);
}

void ShowTransferGoods()
{
	string describeStr = "";
	string sHeader;
	int buyCount;

	if (isGoodTable)
	{	//показ товара левой таблицы
		String sGood = Goods[iCurGoodIndex].name;
		SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "TG_GOODS_PICTURE", 6, "GOODS", sGood);//картинка
		sHeader = XI_ConvertString(sGood);
		describeStr = GetAssembledString(GetConvertStr(sGood + "_descr", "GoodsDescribe.txt"), &Goods[iCurGoodIndex]);

		String companionId = Characters[iCurCompanion].Id;
		if (CheckAttribute(Characters[iCurCompanion], "TransferGoods." + sGood)) buyCount = sti(Characters[iCurCompanion].TransferGoods.(sGood)); else buyCount = 0;
	}
	else 
	{	//показ предмета правой таблицы
		SetNewGroupPicture("TG_GOODS_PICTURE", Items[iCurItemIndex].picTexture, "itm" + Items[iCurItemIndex].picIndex);//картинка
		String FighterId = Characters[iCurFighter].Id;
		string sItem = Items[iCurItemIndex].name;
		int	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
		sHeader = LanguageConvertString(lngFileID, sItem);
		LanguageCloseFile(lngFileID);
		describeStr = GetItemDescribe(iCurItemIndex);
		sItem = Items[iCurItemIndex].id;
		if (CheckAttribute(Characters[iCurFighter], "TransferItems." + sItem)) buyCount = sti(Characters[iCurFighter].TransferItems.(sItem)); else buyCount = 0;
	}
		SetFormatedText("TG_GOODS_CAPTION", sHeader);//заголовок
		SetFormatedText("TG_GOODS_INFO", describeStr);//описание
		GameInterface.TG_EDIT.str = buyCount;
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
	DelEventHandler("UnShowTGWindow", "UnShowTGWindow");
	DelEventHandler("frame","ProcessFrame");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
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
	if (isGoodTable && iNum > 15000/sti(rGood.Weight)*_Units) iNum = 15000/sti(rGood.Weight)*_Units;//максимум 15000 грузоподъемности, хотя и 10000 много было бы
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
	int iMult = 1;//правой кнопкой множитель x5
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
				UnShowTGWindow();
			}
			break;
			
		case "TG_OK_BUTTON":
			if(comName == "click" || comName == "activate")
			{
				if (isGoodTable)
				{
					rGood = &Goods[iCurGoodIndex];
					sGood = rGood.name;
					iNum =  sti(GameInterface.TG_EDIT.str);
					if (iNum >999999) iNum = 999999;
//НАДО ЛИ это затирание? Может, наоборот при закрытии все строчки заполнять, чтоб чекатрибут не делать?
					if (iNum == 0) DeleteAttribute(&Characters[iCurCompanion],"TransferGoods." + sGood); else Characters[iCurCompanion].TransferGoods.(sGood) = iNum; // Прибавим в список закупок
					GameInterface.GOODS_TABLE_LIST.(sCurGoodRow).td2.str = iNum;
					Table_UpdateWindow("GOODS_TABLE_LIST");
					UnShowTGWindow();
				}
				else 
				{
					String FighterId = Characters[iCurFighter].Id;
					String sItem = Items[iCurItemIndex].id;
					iNum =  sti(GameInterface.TG_EDIT.str);
					if (iNum >9999) iNum = 9999;
//НАДО ЛИ это затирание? Может, наоборот при закрытии все строчки заполнять, чтоб чекатрибут не делать?
					if (iNum == 0) DeleteAttribute(&Characters[iCurFighter],"TransferItems." + sItem); else Characters[iCurFighter].TransferItems.(sItem) = iNum; // Прибавим в список закупок
					GameInterface.CONSUME_TABLE_LIST.(sCurItemRow).td2.str = iNum;
					Table_UpdateWindow("CONSUME_TABLE_LIST");
					UnShowTGWindow();
				}
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
			//SetDescription(); //TODO - заполнить полезную информацию
		}
	}

	if (GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		if (sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNumC)
		{
			nCurScrollNumC = sti(GameInterface.CHARACTERS_SCROLL.current);
			FillItemsTable();
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
	if (iNewState) Characters[iCurCompanion].TransferGoods.BuyContraband = true; else DeleteAttribute(&Characters[iCurCompanion], "TransferGoods.BuyContraband");
	return;
	}
//========================================//
	if (sControl == "CHECK_RESTRICTSELL")
	{
	if (iNewState) DeleteAttribute(PChar, "SellRestriction"); else PChar.SellRestriction = false;
	return;
	}
//========================================//
}
//TO DO - пушки тоже задавать??? чтобы была возможность продавать при автозакупке
//TO DO - прикрутить показ параметров компаньона по ПКМ на портрете
//TO DO - прикрутить показ снаряжения Абордага по ПКМ на портрете
//TO DO - сделать чекбоксы и кнопки автоподбора товаров и расходников под текущие параметры - сколько пушек и их перезарядка, какой пистолет и его перезарядка и т.д. - под длительность ведения боя
//оружие и лекарства под численность экипажа
//товарам скупку и продажа по заданной вилке цен

void ShowItemInfo()
{
	if (GetCurrentNode() == "GOODS_TABLE_LIST") isGoodTable = true; else isGoodTable = false;
	ShowMainWindow(false);
	ShowTransferGoods();
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
	int i, n, buyCount;
	string attributeName = "pic" + (nCurScrollNumS+1);
	iCurCompanion = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
	String companionId = Characters[iCurCompanion].Id;
	ref refCharacter = characterFromID(companionId);
	SetNewPicture("CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
	SetFormatedText("SHIP_NAME", XI_ConvertString(RealShips[sti(refCharacter.Ship.Type)].BaseName) + " '" + refCharacter.Ship.Name + "'");
	SetFormatedText("COMP_NAME", GetFullName(refCharacter));

	Table_Clear("GOODS_TABLE_LIST", false, true, false);
	GameInterface.GOODS_TABLE_LIST.hr.td1.str = "Товар";
	GameInterface.GOODS_TABLE_LIST.hr.td2.str = "Кол-во";
	GameInterface.GOODS_TABLE_LIST.hr.td3.str = "Пачка";
	GameInterface.GOODS_TABLE_LIST.hr.td4.str = "Вес";

	for (i = 0, n = 1; i< GOODS_QUANTITY; i++)
	{
		row = "tr" + n;
		sGood = Goods[i].name;
		if (checkattribute(Goods[i],"CannonIdx")) continue;//без пушек???

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
		GameInterface.GOODS_TABLE_LIST.(row).td3.str = Goods[i].Units;//в пачке
		GameInterface.GOODS_TABLE_LIST.(row).td4.str = Goods[i].Weight;//вес
		n++;
	}
	GameInterface.GOODS_TABLE_LIST.select = 1;
	Table_UpdateWindow("GOODS_TABLE_LIST");
}

void FillItemsTable()
{
	string sItem, row;
	int i, n, buyCount;
	string attributeName = "pic" + (nCurScrollNumC+1);
	iCurFighter = GameInterface.CHARACTERS_SCROLL.(attributeName).character;
	string FighterId = Characters[iCurFighter].Id;//проверить выбор абордажника
	SetFormatedText("CHAR_NAME", GetFullName(Characters[iCurFighter]));
	
	Table_Clear("CONSUME_TABLE_LIST", false, true, false);
	GameInterface.CONSUME_TABLE_LIST.hr.td1.str = "Предмет";
	GameInterface.CONSUME_TABLE_LIST.hr.td2.str = "Кол-во";
	GameInterface.CONSUME_TABLE_LIST.hr.td3.str = "Вес";
	for(i = 0, n = 1; i < ITEMS_QUANTITY; i++)
	{
		if (!checkattribute(Items[i],"sortIndex")) continue;//в списке только расходники
		//но, возможно, лучше напрямую список предметов в массиве указывать... не весь список предметов проверяться будет, и при добавлении новых не возникнет неожиданностей
		if (Items[i].id == "Lockpick") continue;//отмычки пропускаем
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
		GameInterface.CONSUME_TABLE_LIST.(row).td3.str = FloatToString(stf(Items[i].Weight), 1);//TO DO - добавить вычисление buyCount* - суммировать ожидаемый вес и выводить текстом ниже таблицы
		n++;
	}
	Table_UpdateWindow("CONSUME_TABLE_LIST");
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