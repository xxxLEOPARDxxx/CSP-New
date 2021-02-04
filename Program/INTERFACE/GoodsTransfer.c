// Интерфейс закупки товара казначеем

int iCurGoodIndex;
int iCurCompanion = 0;
bool g_bToolTipStarted = false;

void InitInterface(string iniName)
{
	string sGood;
	int i;
	int X = 50; //LEO: двигает всю таблицу по ширине
	int Y = 120; //LEO: двигает столбец по высоте

	GameInterface.title = "titleGoodsTransfer";

	for(i = 0; i < GOODS_QUANTITY; i++)	// Картинки товаров
	{
		if(i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30 || i == 35)	// Другой столбец
		{
			X += 100;
			Y = 120; //LEO: всю таблицу по высоте
		}
		
		sGood = goods[i].name;
				
		// Это к магазину никакого отношения не имеет
		if(HasSubStr(sGood, "Cannon") || HasSubStr(sGood, "Culverine")) continue;
				
		GameInterface.GOODS_ICONS.imagelist.(sGood).group = "GOODS";
		GameInterface.GOODS_ICONS.imagelist.(sGood).width = 50;
		GameInterface.GOODS_ICONS.imagelist.(sGood).height = 50;
		GameInterface.GOODS_ICONS.imagelist.(sGood).x = X;
		GameInterface.GOODS_ICONS.imagelist.(sGood).y = Y;
		GameInterface.GOODS_ICONS.imagelist.(sGood).pic = sGood;
		
		Y += 80; // Интервал между картинками
	}
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	
	// Нужно после инициализации интерфейса
	CreateGoodNamesStrings();
	
	// Тут, т.к. изначально все по нулям и на кнопку можно не нажать
	if(!CheckAttribute(PChar, "TransferGoods.AllGoodsWeight")) PChar.TransferGoods.AllGoodsWeight = 0;
		
	SetCheckButtonsStates();
	
	CreateString(true, "CurCompanion", XI_ConvertString(GetShipTypeName(PChar)) + " '" + PChar.Ship.Name + "'", FONT_NORMAL, COLOR_NORMAL, 400, 12, SCRIPT_ALIGN_CENTER, 1.0);
	
	// CreateString(true, "GameVersionInfo1", VERSION_NUMBER1, FONT_CAPTION, COLOR_NORMAL,150, 10, SCRIPT_ALIGN_CENTER, 0.8);
	// CreateString(true, "GameVersionInfo2", GetVerNum(), FONT_CAPTION, COLOR_NORMAL, 650, 10, SCRIPT_ALIGN_CENTER, 0.8);
	
	SetEventHandler("UnShowTGWindow", "UnShowTGWindow", 0);
	SetEventHandler("ShowItemsWindow", "ShowItemsWindow", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("ShowInfo","ShowInfo",0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
}

void HideInfo()
{
	if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

void SetCheckButtonsStates()
{
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	if(CheckAttribute(PChar, "TransferGoods." + companionId + ".BuyContraband"))
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, true);
	}
	else
	{
		CheckButton_SetState("CHECK_BUYCONTRABAND", 1, false);
	}
	
	if(CheckAttribute(PChar, "BuyPersonal"))
	{
		CheckButton_SetState("BUY_PERSONAL", 1, true);
	}
	else
	{
		CheckButton_SetState("BUY_PERSONAL", 1, false);
	}
	
	if(CheckAttribute(PChar, "SellRestriction"))
	{
		CheckButton_SetState("RESTRICT_SELL", 1, true);
	}
	else
	{
		CheckButton_SetState("RESTRICT_SELL", 1, false);
	}
}

void CreateGoodNamesStrings()
{
	int x, y;
	int buyCount;
	String sGood;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	for(int i = 0; i < GOODS_QUANTITY; i++)	// Названия товаров
	{
		sGood = Goods[i].name;
		
		if(CheckAttribute(GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			x = MakeInt(GameInterface.GOODS_ICONS.imagelist.(sGood).x);
			y = MakeInt(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 46;
			
			if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
			{
				buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
			}
			else
			{
				buyCount = 0;
			}
			
			// Строки
			SendMessage(&GameInterface,"lslsssllllllfl",MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 0, sGood, XI_ConvertString(sGood), FONT_NORMAL, X, Y, COLOR_NORMAL, COLOR_NORMAL, SCRIPT_ALIGN_CENTER, true, 0.8, 100);
			SendMessage(&GameInterface,"lslsssllllllfl",MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 0, "Transfer" + sGood, XI_ConvertString("BuyGoods") + buyCount, FONT_NORMAL, x, y + 12, COLOR_NORMAL, COLOR_NORMAL, SCRIPT_ALIGN_CENTER, true, 0.8, 100);
		}
	}
}

void RefreshGoodsCountStrings()
{
	int buyCount;
	int curString = 2; // Со второй, т.к. первая - название
	String sGood;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	for(int i = 0; i < GOODS_QUANTITY; i++)	// Названия товаров
	{
		sGood = Goods[i].name;
		
		if(CheckAttribute(GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
			{
				buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
			}
			else
			{
				buyCount = 0;
			}
			
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "GOODS_NAMES", 1, curString, "#" + XI_ConvertString("BuyGoods") + buyCount);
			curString += 2;
		}
	}
}

void ShowItemsWindow()	// Принцип тот-же, что и в интерфейса отличной карты
{
	float fMouseX = stf(GameInterface.mousepos.x) - 6.0 + 5;
	float fMouseY = stf(GameInterface.mousepos.y) - 50.0 + 5;
	
	float fOffsetX, fOffsetY;
	GetXYWindowOffset(&fOffsetX, &fOffsetY);
	
	fMouseX = (fMouseX - fOffsetX) * stf(GameInterface.GOODS_ICONS.scale.x);
	fMouseY = (fMouseY - fOffsetY) * stf(GameInterface.GOODS_ICONS.scale.y);

	string sGood;
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		sGood = goods[i].name;
		if(CheckAttribute(&GameInterface, "GOODS_ICONS.imagelist." + sGood))
		{
			if(fMouseX >= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).x) - 32)
			{
				if(fMouseX <= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).x) + 32.0)
				{
					if(fMouseY >= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 80)
					{
						if(fMouseY <= stf(GameInterface.GOODS_ICONS.imagelist.(sGood).y) - 16)
						{
							ShowMainWindow(false);
							ShowTransferGoods(i);
						}
					}
				}
			}
		}
	}
}

void ShowMainWindow(bool _truefalse)
{
	if(_truefalse)
	{	// Видим главное окно
		CreateGoodNamesStrings(); // Обновим
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

void ShowTransferGoods(int iGood)
{
	string sText;
	String sGood = Goods[iGood].name;
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	int buyCount;
	
	iCurGoodIndex = iGood; // Какой товар выбрали
	
	if(CheckAttribute(PChar, "TransferGoods." + companionId + "." + sGood))
	{
		buyCount = sti(PChar.TransferGoods.(companionId).(sGood));
	}
	else
	{
		buyCount = 0;
	}
	
	GameInterface.TG_EDIT.str = buyCount;
	
	sText = XI_ConvertString("titleGoodsTransfer"); // Заголовок
	SetFormatedText("TG_GOODS_CAPTION", sText);
	
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "TG_GOODS_PICTURE", 6, "GOODS", sGood); // Ставим картинку
	sText = GetConvertStr(sGood, "GoodsDescribe.txt") + NewStr(); // описание товара
	sText = sText + GetAssembledString(GetConvertStr(sGood + "_descr", "GoodsDescribe.txt"), &Goods[iGood]);
	SetFormatedText("TG_GOODS_INFO", sText);
	
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_GOODS_TRANSFER);
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	sHeader = XI_ConvertString("BuyPersonal");
	sText1 = "Закупать боеприпасы (по 10 пуль и пороха), еду (варьируемо, но не менее 3 единиц случайной еды) и лечилки (варьируемо, не менее 3 малых) всем активным абордажникам и ГГ";
			
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void IDoExit(int exitCode)
{
	SetContrabandBuyFromCheckBox();
	SetBuyPersonal();
	SetSellRestriction();
	
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("evntDoPostExit", "DoPostExit");
	DelEventHandler("UnShowTGWindow", "UnShowTGWindow");
	DelEventHandler("ShowItemsWindow", "ShowItemsWindow");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfo","ShowInfo");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	int iNum = 0;
	string sGood;
	int iTemp = 0;
	ref rGood;
	
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
	switch(nodName)
	{
		case "TG_ADD_ALL_BUTTON":
			GameInterface.TG_EDIT.str = 10000;
			break;
	
		case "TG_ADD_BUTTON":
			OnAddBtnClick();
			break;
			
		case "TG_REMOVE_ALL_BUTTON":
			GameInterface.TG_EDIT.str = 0;
			break;
			
		case "TG_REMOVE_BUTTON":
			OnRemoveBtnClick();
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
				rGood = &Goods[iCurGoodIndex];
				sGood = rGood.name;
				iNum =  sti(GameInterface.TG_EDIT.str);
				
				PChar.TransferGoods.(companionId).(sGood) = iNum; // Прибавим в список закупок
				
				UnShowTGWindow();	
			}
			break;
		
		// Warship 19.08.09 Выбор корабля, для кого запукаем
		case "BTN_CHOOSESHIP_LEFT":
			SetCurrentCompanion(iCurCompanion - 1);
		break;
		
		case "BTN_CHOOSESHIP_RIGHT":
			SetCurrentCompanion(iCurCompanion + 1);
		break;
	}
}

void SetCurrentCompanion(int _num)
{
	ref character;
	int characterIndex = GetCompanionIndex(PChar, _num);
	
	if(characterIndex > 0)
	{
		character = &Characters[characterIndex];
		
		if(GetRemovable(character))
		{
			SetContrabandBuyFromCheckBox();
			
			iCurCompanion = _num;
			GameInterface.Strings.CurCompanion = XI_ConvertString(GetShipTypeName(character)) + " '" + character.Ship.Name + "'";
			
			SetCheckButtonsStates();
			RefreshGoodsCountStrings();
		}
	}
}

void OnAddBtnClick()
{
	ref rGood;
	int iNum = MakeInt(GameInterface.TG_EDIT.str);
	
	if(iNum < 10000)
	{
		rGood = &Goods[iCurGoodIndex];
		GameInterface.TG_EDIT.str = iNum + sti(rGood.Units);
	}
}

void OnRemoveBtnClick()
{
	ref rGood;
	int iNum = MakeInt(GameInterface.TG_EDIT.str);;
	
	if(iNum > 0)
	{
		rGood = &Goods[iCurGoodIndex];
		GameInterface.TG_EDIT.str = iNum - sti(rGood.Units);
	}
}

void SetContrabandBuyFromCheckBox()
{
	String companionId = Characters[GetCompanionIndex(PChar, iCurCompanion)].Id;
	
 	if(SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "CHECK_BUYCONTRABAND", 3, 1))
	{
		PChar.TransferGoods.(companionId).BuyContraband = true;
	}
	else
	{
		DeleteAttribute(PChar, "TransferGoods." + companionId + ".BuyContraband");
	}
}

void SetBuyPersonal()
{
 	if(SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "BUY_PERSONAL", 3, 1))
	{
		PChar.BuyPersonal = true;
	}
	else
	{
		DeleteAttribute(PChar, "BuyPersonal");
	}
}

void SetSellRestriction()
{
 	if(SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "RESTRICT_SELL", 3, 1))
	{
		PChar.SellRestriction = true;
	}
	else
	{
		DeleteAttribute(PChar, "SellRestriction");
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}
