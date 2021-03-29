/// boal 07/06/06 переделка СЖ под нужны ВМЛ
int curQuestTop;
string CurTable, CurRow;
int iMaxGoodsStore = 50000;
string sMessageMode;
ref chrefsp;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchQuestBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleQuestBook";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	selectJournal(1); // первый режим журнала, только активные

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);

    SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("SetScrollerPos","SetScrollerPos",0);
	SetEventHandler("ScrollPosChange","ProcScrollPosChange",0);
	SetEventHandler("ScrollTopChange","ProcScrollChange",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("QuestTopChange","QuestTopChange",0);
	SetEventHandler("BackToTitle","BackToTitle",0);
	SetEventHandler("QuestActivate","XI_QuestActivate",0);
	SetEventHandler("QuestDeActivate","QuestDeActivate",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowPGGInfo","ShowPGGInfo",0);
	SetEventHandler("ShowShipsWindow","ShowShipsWindow",0);
	SetEventHandler("ShowBladeWindow","ShowBladeWindow",0);
	SetEventHandler("ShowGunWindow","ShowGunWindow",0);
	SetEventHandler("ShowFoodWindow","ShowFoodWindow",0);
	sMessageMode = "";
	string sDate = " ";
	sDate = GetDateString();
	string sTime; 
	sTime = GetTimeString();
    SetFormatedText("CURRENT_DATE_CAPTION", sDate + " "+ sTime);
	XI_RegistryExitKey("IExit_F2");
	SetControlsTabMode(1);
	
	InitTableHeader();
}

void XI_SetQuestData(bool qtitle)
{
	aref arefTmp;
	makearef(arefTmp,pchar.TmpQuestInfo);

	XI_SetQuestTitles("QUEST_TITLE",arefTmp,0);
	curQuestTop = 0;
	
	SetNodeUsing("QUEST_TITLE",qtitle);
	if (!InterfaceStates.AltFont) SetNodeUsing("QUEST_TEXT",!qtitle);
	else SetNodeUsing("QUEST_TEXT_ALT",!qtitle);
	SetNodeUsing("QUESTSCROLL",true);
	
	ShowButtons();
	
	if(qtitle == true)
	{
		SetCurrentNode("QUEST_TITLE");
	}
	else
	{
		if (!InterfaceStates.AltFont) SetCurrentNode("QUEST_TEXT");
		else SetCurrentNode("QUEST_TEXT_ALT");
	}
}

void ShowButtons()
{

}

void ShowShipsWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",true);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",false);
	
	SetNodeUsing("TABBTN_QUEST",false);
	SetNodeUsing("TABSTR_QUEST",false);
	SetNodeUsing("TABBTN_QUESTARJ",false);
	SetNodeUsing("TABSTR_QUESTARJ",false);
	SetNodeUsing("TABBTN_INFO",false);
	SetNodeUsing("TABSTR_INFO",false);
	SetNodeUsing("TABBTN_CASHBOOK",false);
	SetNodeUsing("TABSTR_CASHBOOK",false);
	SetNodeUsing("TABBTN_SHIP_PLACE",false);
	SetNodeUsing("TABSTR_SHIP_PLACE",false);
	SetNodeUsing("TABBTN_STATISTIC",false);
	SetNodeUsing("TABSTR_STATISTIC",false);
	SetNodeUsing("TABBTN_STOREBOOK",false);
	SetNodeUsing("TABSTR_STOREBOOK",false);
	
	SetNodeUsing("I_CHARACTER_2",false);
	SetNodeUsing("I_CHARACTER",false);
	SetNodeUsing("I_SHIP_2",false);
	SetNodeUsing("I_SHIP",false);
	SetNodeUsing("I_NATIONS_2",false);
	SetNodeUsing("I_NATIONS",false);
	SetNodeUsing("I_TRADEBOOK_2",false);
	SetNodeUsing("I_TRADEBOOK",false);
	SetNodeUsing("I_ITEMS_2",false);
	SetNodeUsing("I_ITEMS",false);
	
	SetNodeUsing("QUEST_TITLE",false);
}

void ShowBladeWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",true);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",false);
	
	SetNodeUsing("TABBTN_QUEST",false);
	SetNodeUsing("TABSTR_QUEST",false);
	SetNodeUsing("TABBTN_QUESTARJ",false);
	SetNodeUsing("TABSTR_QUESTARJ",false);
	SetNodeUsing("TABBTN_INFO",false);
	SetNodeUsing("TABSTR_INFO",false);
	SetNodeUsing("TABBTN_CASHBOOK",false);
	SetNodeUsing("TABSTR_CASHBOOK",false);
	SetNodeUsing("TABBTN_SHIP_PLACE",false);
	SetNodeUsing("TABSTR_SHIP_PLACE",false);
	SetNodeUsing("TABBTN_STATISTIC",false);
	SetNodeUsing("TABSTR_STATISTIC",false);
	SetNodeUsing("TABBTN_STOREBOOK",false);
	SetNodeUsing("TABSTR_STOREBOOK",false);
	
	SetNodeUsing("I_CHARACTER_2",false);
	SetNodeUsing("I_CHARACTER",false);
	SetNodeUsing("I_SHIP_2",false);
	SetNodeUsing("I_SHIP",false);
	SetNodeUsing("I_NATIONS_2",false);
	SetNodeUsing("I_NATIONS",false);
	SetNodeUsing("I_TRADEBOOK_2",false);
	SetNodeUsing("I_TRADEBOOK",false);
	SetNodeUsing("I_ITEMS_2",false);
	SetNodeUsing("I_ITEMS",false);
	
	SetNodeUsing("QUEST_TITLE",false);
}

void ShowGunWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",true);
	XI_WindowShow("ENC_INFO_FOOD",false);
	
	SetNodeUsing("TABBTN_QUEST",false);
	SetNodeUsing("TABSTR_QUEST",false);
	SetNodeUsing("TABBTN_QUESTARJ",false);
	SetNodeUsing("TABSTR_QUESTARJ",false);
	SetNodeUsing("TABBTN_INFO",false);
	SetNodeUsing("TABSTR_INFO",false);
	SetNodeUsing("TABBTN_CASHBOOK",false);
	SetNodeUsing("TABSTR_CASHBOOK",false);
	SetNodeUsing("TABBTN_SHIP_PLACE",false);
	SetNodeUsing("TABSTR_SHIP_PLACE",false);
	SetNodeUsing("TABBTN_STATISTIC",false);
	SetNodeUsing("TABSTR_STATISTIC",false);
	SetNodeUsing("TABBTN_STOREBOOK",false);
	SetNodeUsing("TABSTR_STOREBOOK",false);
	
	SetNodeUsing("I_CHARACTER_2",false);
	SetNodeUsing("I_CHARACTER",false);
	SetNodeUsing("I_SHIP_2",false);
	SetNodeUsing("I_SHIP",false);
	SetNodeUsing("I_NATIONS_2",false);
	SetNodeUsing("I_NATIONS",false);
	SetNodeUsing("I_TRADEBOOK_2",false);
	SetNodeUsing("I_TRADEBOOK",false);
	SetNodeUsing("I_ITEMS_2",false);
	SetNodeUsing("I_ITEMS",false);
	
	SetNodeUsing("QUEST_TITLE",false);
}

void ShowFoodWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",true);
	
	SetNodeUsing("TABBTN_QUEST",false);
	SetNodeUsing("TABSTR_QUEST",false);
	SetNodeUsing("TABBTN_QUESTARJ",false);
	SetNodeUsing("TABSTR_QUESTARJ",false);
	SetNodeUsing("TABBTN_INFO",false);
	SetNodeUsing("TABSTR_INFO",false);
	SetNodeUsing("TABBTN_CASHBOOK",false);
	SetNodeUsing("TABSTR_CASHBOOK",false);
	SetNodeUsing("TABBTN_SHIP_PLACE",false);
	SetNodeUsing("TABSTR_SHIP_PLACE",false);
	SetNodeUsing("TABBTN_STATISTIC",false);
	SetNodeUsing("TABSTR_STATISTIC",false);
	SetNodeUsing("TABBTN_STOREBOOK",false);
	SetNodeUsing("TABSTR_STOREBOOK",false);
	
	SetNodeUsing("I_CHARACTER_2",false);
	SetNodeUsing("I_CHARACTER",false);
	SetNodeUsing("I_SHIP_2",false);
	SetNodeUsing("I_SHIP",false);
	SetNodeUsing("I_NATIONS_2",false);
	SetNodeUsing("I_NATIONS",false);
	SetNodeUsing("I_TRADEBOOK_2",false);
	SetNodeUsing("I_TRADEBOOK",false);
	SetNodeUsing("I_ITEMS_2",false);
	SetNodeUsing("I_ITEMS",false);
	
	SetNodeUsing("QUEST_TITLE",false);
}

void HideQuests()
{
	SetNodeUsing("QUEST_TITLE",false);
	if (!InterfaceStates.AltFont) SetNodeUsing("QUEST_TEXT",false);
	else SetNodeUsing("QUEST_TEXT_ALT",false);
	SetNodeUsing("QUESTSCROLL",false);
}

void HideStatistic()
{
	SetNodeUsing("TABLE_SHIPCLASS",false);
	SetNodeUsing("TABLE_HUMAN",false);
	SetNodeUsing("TABLE_NATION",false);
	SetNodeUsing("TABLE_OTHER",false);
	SetNodeUsing("TABLE_MONEY",false);
	CreateString(true, "LevelComplexity", "", "INTERFACE_ULTRASMALL", COLOR_NORMAL, 0, 0, SCRIPT_ALIGN_RIGHT, 1);
}

void HideCashBook()
{
	SetNodeUsing("SCROLL_DEBIT",false);
	SetNodeUsing("TABLE_DEBIT",false);
	SetNodeUsing("SCROLL_CREDIT",false);
	SetNodeUsing("TABLE_CREDIT",false);
}

void HideShipPlace()
{
	SetNodeUsing("TABLE_SHIP_PLACE",false);
	SetNodeUsing("SCROLL_SHIP_PLACE",false);
}

void HideStoreBook()
{
	SetNodeUsing("TABLE_CITY",false);
	SetNodeUsing("SCROLL_CITY",false);
	SetNodeUsing("TABLE_GOODS",false);
	SetNodeUsing("SCROLL_GOODS",false);
}

void ProcessCancelExit()
{
	if (!InterfaceStates.AltFont)
	{
		if( GetSelectable("QUEST_TEXT") )
		{
			XI_SetQuestData(true);
			return;
		}
	}
	else
	{
		if( GetSelectable("QUEST_TEXT_ALT") )
		{
			XI_SetQuestData(true);
			return;
		}
	}
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void QuestTopChange()
{
	if( GetSelectable("QUEST_TITLE") )
	{
		int newTop = curQuestTop+GetEventData();

		aref arefTmp;
		makearef(arefTmp,pchar.TmpQuestInfo);
		int maxVal = GetAttributesNum(arefTmp);
		if(newTop>=maxVal)
		{
			newTop=maxVal-1;
		}
		if(newTop<0)
		{
			newTop=0;
		}

		if(newTop!=curQuestTop)
		{
			curQuestTop=newTop;
			XI_SetQuestTitles("QUEST_TITLE",arefTmp,curQuestTop);
			XI_SetScroller(MakeFloat(newTop)/MakeFloat(maxVal));
		}
	}
}

void SetQTextShow(aref pA,int qnum)
{
	// boal Покраска, выбрали 22.06.07 -->
	aref arTopic = GetAttributeN(pA, qnum);
	DeleteQuestHeaderColor(GetAttributeName(arTopic));
	// boal <--
	if (!InterfaceStates.AltFont)
	{
		SendMessage(&GameInterface,"lsal",MSG_INTERFACE_INIT_QTEXT_SHOW,"QUEST_TEXT",pA,qnum);
		SetCurrentNode("QUEST_TEXT");
	}
	else
	{
		SendMessage(&GameInterface,"lsal",MSG_INTERFACE_INIT_QTEXT_SHOW,"QUEST_TEXT_ALT",pA,qnum);
		SetCurrentNode("QUEST_TEXT_ALT");
	}
	
}

void BackToTitle()
{
	XI_SetQuestData(true);
}

void XI_QuestActivate()
{
	int aq = curQuestTop+GetEventData();
	aref pA;
	makearef(pA,pchar.TmpQuestInfo);
	XI_SetQuestData(false);
	SetQTextShow(pA,aq);
	if (!InterfaceStates.AltFont) SetCurrentNode("QUEST_TEXT");
	else SetCurrentNode("QUEST_TEXT_ALT");
}

void XI_SetScroller(float pos)
{
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"QUESTSCROLL",pos);
}

void SetScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	XI_SetScroller(pos);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("QuestTopChange","QuestTopChange");
	DelEventHandler("BackToTitle","BackToTitle");
	DelEventHandler("QuestActivate","XI_QuestActivate");
	DelEventHandler("SetScrollerPos","SetScrollerPos");
	DelEventHandler("ScrollPosChange","ProcScrollPosChange");
	DelEventHandler("ScrollTopChange","ProcScrollChange");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
 	DelEventHandler("QuestDeActivate","QuestDeActivate");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowPGGInfo","ShowPGGInfo");
	DelEventHandler("ShowShipsWindow","ShowShipsWindow");
	DelEventHandler("ShowBladeWindow","ShowBladeWindow");
	DelEventHandler("ShowGunWindow","ShowGunWindow");
	DelEventHandler("ShowFoodWindow","ShowFoodWindow");

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
}
void QuestDeActivate()
{
	XI_SetQuestData(true);
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
	string scrollName = GetEventData();
	if( GetSelectable("QUEST_TITLE") )
	{
		aref arefTmp;
		makearef(arefTmp,pchar.TmpQuestInfo);
		int maxVal = GetAttributesNum(arefTmp);
		int newTop = makeint(newPos*maxVal);

		if(newTop!=curQuestTop)
		{
			curQuestTop=newTop;
			XI_SetQuestTitles("QUEST_TITLE",arefTmp,curQuestTop);
		}
	}
	else
	{
		if (!InterfaceStates.AltFont) SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 1,newPos);
		else SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT_ALT", 1,newPos);
	}
}

void ProcScrollChange()
{
	int changeNum = GetEventData();
	if(changeNum==0) return;
	string controlNode = "";
	if( GetSelectable("QUEST_TITLE") ) controlNode = "QUEST_TITLE";
	if (!InterfaceStates.AltFont) {if( GetSelectable("QUEST_TEXT") ) controlNode = "QUEST_TEXT";}
	else {if( GetSelectable("QUEST_TEXT_ALT") ) controlNode = "QUEST_TEXT_ALT";}

	if(controlNode!="")
	{
		if(changeNum>0) {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_DOWNSTEP);
		} else {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_UPSTEP);
		}
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
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

void selectJournal(int iMode)
{
    //Boyer fix for .complete sometimes missing
    string sAttComplete = "";

    HideStatistic();
    HideCashBook();
    HideShipPlace();
	HideStoreBook();
	// подменим квестовую ветку, зависимо от типа режима: журнал, архив, инфа
	aref arQuestInfo, arTmp;
	int  i;
	string attributeName;
	bool   ok; // копировать ли?
	aref   newAttr;
	makearef(arQuestInfo, pchar.QuestInfo);
	DeleteAttribute(pchar, "TmpQuestInfo");
	pchar.TmpQuestInfo = "";
	for(i=0; i<GetAttributesNum(arQuestInfo); i++)
    {
        arTmp = GetAttributeN(arQuestInfo, i);
        attributeName = GetAttributeName(arTmp);
	sAttComplete = "QuestInfo." + attributeName + ".Complete";
        ok = false;
		switch (iMode)
        {
            case 1:
                if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && CheckAttribute(pchar, sAttComplete) && sti(pchar.QuestInfo.(attributeName).Complete) == false)
                {
                    ok = true;
                }
            break;
            
            case 2:
                if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && CheckAttribute(pchar, sAttComplete) && sti(pchar.QuestInfo.(attributeName).Complete) == true)
                {
                    ok = true;
                }
            break;
            
            case 3:
                if (CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType"))
                {
                    ok = true;
                }
            break;
        }
        if (ok)
        { // копируем
            pchar.TmpQuestInfo.(attributeName) = "";
            makearef(newAttr, pchar.TmpQuestInfo.(attributeName));
			CopyAttributes(newAttr, arTmp);
        }
    }
	XI_SetQuestData(true);
}

void selectStatistic()
{
    SetNodeUsing("TABLE_SHIPCLASS",true);
    SetNodeUsing("TABLE_HUMAN",true);
    SetNodeUsing("TABLE_NATION",true);
    SetNodeUsing("TABLE_OTHER",true);
	SetNodeUsing("TABLE_MONEY",true);
    HideCashBook();
	HideQuests();
	HideShipPlace();
	HideStoreBook();
	ShowButtons();
	CreateString(true, "LevelComplexity", XI_ConvertString("m_Complexity") + " : " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE), "interface_ultrasmall", COLOR_NORMAL, 440, 338, SCRIPT_ALIGN_CENTER, 1.5);
}

void selectCashBook()
{
    SetNodeUsing("SCROLL_DEBIT",true);
	SetNodeUsing("TABLE_DEBIT",true);
	SetNodeUsing("SCROLL_CREDIT",true);
	SetNodeUsing("TABLE_CREDIT",true);
	HideStatistic();
	HideQuests();
	HideShipPlace();
	HideStoreBook();
	ShowButtons();
}

void selectShipPlace()
{
    SetNodeUsing("TABLE_SHIP_PLACE",true);
    SetNodeUsing("SCROLL_SHIP_PLACE",true);
	HideStatistic();
	HideQuests();
	HideCashBook();
	HideStoreBook();
	ShowButtons();
}

void selectStoreBook()
{
	SetNodeUsing("TABLE_CITY",true);
	SetNodeUsing("SCROLL_CITY",true);
	SetNodeUsing("TABLE_GOODS",true);
	SetNodeUsing("SCROLL_GOODS",true);
	HideStatistic();
	HideQuests();
	HideCashBook();
	HideShipPlace();
	ShowButtons();
}

void HideInfoWindow() 
{
	CloseTooltip();
	ExitRPGHint();
}

void ShowPGGInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
	{ // нет ПГГ в списке
	ref chrefspp = CharacterFromID(GameInterface.(CurTable).(CurRow).index);
	ref refBaseShip = GetRealShip(sti(chrefspp.ship.type));
	string shipTexture = refBaseShip.BaseName;
	SetFormatedText("SHIP_NAME", XI_ConvertString(RealShips[sti(chrefspp.Ship.Type)].BaseName) + " '" + chrefspp.Ship.Name + "'")
	SetFormatedText("SHIP_WINDOW_CAPTION", "Характеристики")
	SetFormatedText("SHIP_INFO_PLACE", "Информация по стоянке")
	SetFormatedText("PORT_INFO_PLACE", "Остров/колония:\n"+GameInterface.(CurTable).(CurRow).td6.str+" / "+GameInterface.(CurTable).(CurRow).td5.str)
	SetFormatedText("DATE_INFO_PLACE", "Дата стоянки:\n"+GameInterface.(CurTable).(CurRow).td7.str)
	SetFormatedText("MONEY_INFO_PLACE", "Цена в месяц:\n"+GameInterface.(CurTable).(CurRow).td8.str+" п.")
	SetFormatedText("SHIP_RANK", refBaseShip.Class)
	SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + shipTexture + ".tga.tx");
	SetNewPicture("SHIP_FRAME_PICTURE", "interfaces\Frame1.tga");
	string texturedata;
	if (IsCharacterPerkOn(chrefspp, "Grunt")) texturedata = "INTERFACES\Sith\Char_Master.tga";
	if (IsCharacterPerkOn(chrefspp, "Trader")) texturedata = "INTERFACES\Sith\Char_Merchant.tga";
	if (IsCharacterPerkOn(chrefspp, "Fencer")) texturedata = "INTERFACES\Sith\Char_Corsair.tga";
	if (IsCharacterPerkOn(chrefspp, "Adventurer")) texturedata = "INTERFACES\Sith\Char_Adventurer.tga";
	if (IsCharacterPerkOn(chrefspp, "Buccaneer")) texturedata = "INTERFACES\Sith\Char_Inquisitor.tga";
	if (IsCharacterPerkOn(chrefspp, "Agent")) texturedata = "INTERFACES\Sith\Char_SecretAgent.tga";
	if (IsCharacterPerkOn(chrefspp, "SeaWolf")) texturedata = "INTERFACES\Sith\Char_SeaWolf.tga";
	SetNewPicture("CHARACTER_PROFESSION", texturedata);
	string portpic;
	switch (GameInterface.(CurTable).(CurRow).td5.icon.image)
	{
		case "France": portpic = "loading\enc_fra.tga";
		break;
		case "England": portpic = "loading\enc_eng.tga";
		break;
		case "Spain": portpic = "loading\enc_spa.tga";
		break;
		case "Holland": portpic = "loading\enc_hol.tga";
		break;
		case "Pirate": portpic = "loading\enc_pir.tga";
		break;
	}
	SetNewPicture("NATION_PORT_PICTURE", portpic);
	SetShipOTHERTable("TABLE_OTHERS",chrefspp);
	SetShipQualityTable(chrefspp, "BAR_HP", "BAR_Mast", "BAR_Speed", "BAR_TurnRate", "BAR_WAS", "BAR_Capacity", "BAR_Crew");
	SetSPECIALMiniTable("TABLE_SMALLSKILL", chrefspp);
	SetOTHERMiniTable("TABLE_SMALLOTHER", chrefspp);
	SetFormatedText("OFFICER_NAME", GetFullName(chrefspp));
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + chrefspp.faceId + ".tga");
	SetNewPicture("CHARACTER_FRAME_PICTURE", "interfaces\Frame2.tga");
	
	XI_WindowShow("SHOW_ADV_INFO", true);
	XI_WindowDisable("SHOW_ADV_INFO", false);
	sMessageMode = "RPG_Hint";
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("SHOW_ADV_INFO", false);
		XI_WindowDisable("SHOW_ADV_INFO", true);
		sMessageMode = "";
	}
}

void ShowInfoWindow(int index) 
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
		    sGroup = "GOODS";
		    sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
		break;
	}

	// CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), "", argb(255,255,255,255), "", argb(255,192,255,192), "", argb(255,255,255,255), sPicture, "NATIONS", sGroupPicture, 64, 64);
}
void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	XI_WindowShow("ENCYCLOPEDIA_INFO_BUTTONS", false);
	XI_WindowDisable("ENCYCLOPEDIA_INFO_BUTTONS", true);
	if( sNodName == "TABBTN_QUEST" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_QUESTARJ" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_INFO" )
	{
		SetControlsTabMode( 3 );
		XI_WindowShow("ENCYCLOPEDIA_INFO_BUTTONS", true);
		XI_WindowDisable("ENCYCLOPEDIA_INFO_BUTTONS", false);
		return;
	}
	if( sNodName == "TABBTN_CASHBOOK" )
	{
		SetControlsTabMode( 4 );
		return;
	}
	if( sNodName == "TABBTN_STATISTIC" )
	{
		SetControlsTabMode( 5 );
		return;
	}
	if( sNodName == "TABBTN_SHIP_PLACE" )
	{
		SetControlsTabMode( 6 );
		return;
	}
	if( sNodName == "TABBTN_STOREBOOK" )
	{
		SetControlsTabMode( 7 );
		return;
	}	
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;
	int nColor6 = nColor1;
	int nColor7 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;
	string sPic6 = sPic1;
	string sPic7 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255,255,255,255);
		break;
		case 5:
			sPic5 = "TabDeSelected";
			nColor5 = argb(255,255,255,255);
		break;
		case 6:
			sPic6 = "TabDeSelected";
			nColor6 = argb(255,255,255,255);
		break;
		case 7:
			sPic7 = "TabDeSelected";
			nColor7 = argb(255,255,255,255);
		break;		
	}
	SetNewGroupPicture("TABBTN_QUEST", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_QUESTARJ", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_INFO", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_CASHBOOK", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_STATISTIC", "TABS", sPic5);
	SetNewGroupPicture("TABBTN_SHIP_PLACE", "TABS", sPic6);
	SetNewGroupPicture("TABBTN_STOREBOOK", "TABS", sPic7);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUEST", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUESTARJ", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_INFO", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_CASHBOOK", 8,0,nColor4);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STATISTIC", 8,0,nColor5);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SHIP_PLACE", 8,0,nColor6);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STOREBOOK", 8,0,nColor7);
    
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: selectJournal(1); break;  // первый режим журнала, только активные
	    case 2: selectJournal(2); break;  // только закрытые
	    case 3: selectJournal(3); break;  // только инфа
	    case 4: selectCashBook(); break;
	    case 5: selectStatistic(); break;
	    case 6: selectShipPlace(); break;
		case 7: selectStoreBook(); break;
	}
}
void InitTableHeader()
{
	int    i;
	string row;
	
	GameInterface.TABLE_SHIPCLASS.hr.td1.str = "Корабли";
	GameInterface.TABLE_SHIPCLASS.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPCLASS.hr.td2.str = "Потоплено орудиями";
	GameInterface.TABLE_SHIPCLASS.hr.td2.scale = 0.7;
	GameInterface.TABLE_SHIPCLASS.hr.td3.str = "Потоплено абордажем";
	GameInterface.TABLE_SHIPCLASS.hr.td3.scale = 0.7;
	GameInterface.TABLE_SHIPCLASS.hr.td4.str = "Захвачено абордажем";
	GameInterface.TABLE_SHIPCLASS.hr.td4.scale = 0.7;
	
    for (i = 1; i< 7; i++)
	{
        row = "tr" + i;
        GameInterface.TABLE_SHIPCLASS.(row).td1.str = "Класс " + i;
		GameInterface.TABLE_SHIPCLASS.(row).td2.str = Statistic_AddValue(pchar, "KillShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td3.str = Statistic_AddValue(pchar, "KillAbordShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td4.str = Statistic_AddValue(pchar, "AbordShip_" + i, 0);
	}

	GameInterface.TABLE_HUMAN.hr.td1.str = "Убито";
	GameInterface.TABLE_HUMAN.hr.td1.scale = 0.9;
	GameInterface.TABLE_HUMAN.hr.td2.str = "Саблями";
	GameInterface.TABLE_HUMAN.hr.td2.scale = 0.7;
	GameInterface.TABLE_HUMAN.hr.td3.str = "Пистолетами";
	GameInterface.TABLE_HUMAN.hr.td3.scale = 0.7;
	
	GameInterface.TABLE_HUMAN.tr1.td1.str = "Солдаты";
	GameInterface.TABLE_HUMAN.tr1.td2.str = Statistic_AddValue(pchar, "Solder_s", 0);
	GameInterface.TABLE_HUMAN.tr1.td3.str = Statistic_AddValue(pchar, "Solder_g", 0);
	
	GameInterface.TABLE_HUMAN.tr2.td1.str = "Горожане";
	GameInterface.TABLE_HUMAN.tr2.td2.str = Statistic_AddValue(pchar, "Citizen_s", 0);
	GameInterface.TABLE_HUMAN.tr2.td3.str = Statistic_AddValue(pchar, "Citizen_g", 0);
	
	GameInterface.TABLE_HUMAN.tr3.td1.str = "Нечисть";
	GameInterface.TABLE_HUMAN.tr3.td2.str = Statistic_AddValue(pchar, "Monster_s", 0);
	GameInterface.TABLE_HUMAN.tr3.td3.str = Statistic_AddValue(pchar, "Monster_g", 0);
	
	GameInterface.TABLE_HUMAN.tr4.td1.str = "Остальные";
	GameInterface.TABLE_HUMAN.tr4.td2.str = Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr4.td3.str = Statistic_AddValue(pchar, "Warrior_g", 0);
	
	GameInterface.TABLE_HUMAN.tr5.td1.str = "Итого";
	GameInterface.TABLE_HUMAN.tr5.td2.str = Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Monster_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr5.td3.str = Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Monster_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0);
	
	GameInterface.TABLE_OTHER.hr.td1.str = "События";
	GameInterface.TABLE_OTHER.hr.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.hr.td2.str = "Значение";
	GameInterface.TABLE_OTHER.hr.td2.scale = 0.9;
	
	GameInterface.TABLE_OTHER.tr1.td1.str = "Кораблей продано";
	GameInterface.TABLE_OTHER.tr1.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr1.td2.str = Statistic_AddValue(PChar, "SellShip", 0);
	
	GameInterface.TABLE_OTHER.tr2.td1.str = "Кораблей куплено";
	GameInterface.TABLE_OTHER.tr2.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr2.td2.str = Statistic_AddValue(PChar, "BuyShip", 0);
	
	GameInterface.TABLE_OTHER.tr3.td1.str = "Бунтов на корабле";
	GameInterface.TABLE_OTHER.tr3.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr3.td2.str = Statistic_AddValue(PChar, "ShipMunity", 0);
	
	GameInterface.TABLE_OTHER.tr4.td1.str = "Восстания рабов";
	GameInterface.TABLE_OTHER.tr4.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr4.td2.str = Statistic_AddValue(PChar, "SlavesMunity", 0);
	
	GameInterface.TABLE_OTHER.tr5.td1.str = "Кораблей отпущено";
	GameInterface.TABLE_OTHER.tr5.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr5.td2.str = Statistic_AddValue(PChar, "AbordShipFree", 0);
	
	GameInterface.TABLE_OTHER.tr6.td1.str = "Товара испорчено крысами";
	GameInterface.TABLE_OTHER.tr6.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr6.td2.str = Statistic_AddValue(PChar, "RatsEatGoods", 0);
	
	GameInterface.TABLE_OTHER.tr7.td1.str = "Save\nLoad";
	GameInterface.TABLE_OTHER.tr7.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr7.td2.str = pchar.SystemInfo.SaveCount +"\n" + pchar.SystemInfo.LoadCount;
	GameInterface.TABLE_OTHER.tr7.td2.scale = 0.9;
	
	GameInterface.TABLE_OTHER.tr8.td1.str = "Здоровья потрачено";
	GameInterface.TABLE_OTHER.tr8.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr8.td2.str = sti(pchar.Health.TotalDamg);
	
	GameInterface.TABLE_OTHER.tr9.td1.str = "Матросов погибло";
	GameInterface.TABLE_OTHER.tr9.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr9.td2.str = Statistic_AddValue(PChar, "Sailors_dead", 0);
	
	GameInterface.TABLE_OTHER.tr10.td1.str = "Кладов найдено";
	GameInterface.TABLE_OTHER.tr10.td1.scale = 0.9;
	GameInterface.TABLE_OTHER.tr10.td2.str = Statistic_AddValue(PChar, "Treasure", 0);
	
	GameInterface.TABLE_NATION.hr.td1.str = "События";
	GameInterface.TABLE_NATION.hr.td1.scale = 0.9;
 	GameInterface.TABLE_NATION.hr.td2.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td2.icon.image      = Nations[0].Name;
	GameInterface.TABLE_NATION.hr.td2.icon.width = 32;
    GameInterface.TABLE_NATION.hr.td2.icon.height = 32;
    GameInterface.TABLE_NATION.hr.td2.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td3.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td3.icon.image      = Nations[1].Name;
	GameInterface.TABLE_NATION.hr.td3.icon.width = 32;
    GameInterface.TABLE_NATION.hr.td3.icon.height = 32;
    GameInterface.TABLE_NATION.hr.td3.icon.offset = "7, 2";
	//GameInterface.TABLE_NATION.hr.td3.str = "Англия";
	//GameInterface.TABLE_NATION.hr.td3.scale = 0.9;
 	GameInterface.TABLE_NATION.hr.td4.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td4.icon.image      = Nations[2].Name;
	GameInterface.TABLE_NATION.hr.td4.icon.width = 32;
    GameInterface.TABLE_NATION.hr.td4.icon.height = 32;
    GameInterface.TABLE_NATION.hr.td4.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td5.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td5.icon.image      = Nations[3].Name;
	GameInterface.TABLE_NATION.hr.td5.icon.width = 32;
    GameInterface.TABLE_NATION.hr.td5.icon.height = 32;
    GameInterface.TABLE_NATION.hr.td5.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td6.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td6.icon.image      = Nations[4].Name;
	GameInterface.TABLE_NATION.hr.td6.icon.width = 32;
    GameInterface.TABLE_NATION.hr.td6.icon.height = 32;
    GameInterface.TABLE_NATION.hr.td6.icon.offset = "7, 2";
	GameInterface.TABLE_NATION.hr.td7.str = "Итого";
	GameInterface.TABLE_NATION.hr.td7.scale = 0.9;
	
	GameInterface.TABLE_NATION.tr1.td1.str = "Фортов разгромлено";
	GameInterface.TABLE_NATION.tr1.td1.scale = 0.9;
	GameInterface.TABLE_NATION.tr1.td2.str = Statistic_AddValue(PChar, "eng_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td3.str = Statistic_AddValue(PChar, "fra_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td4.str = Statistic_AddValue(PChar, "spa_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td5.str = Statistic_AddValue(PChar, "hol_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td6.str = Statistic_AddValue(PChar, "pir_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td7.str = (Statistic_AddValue(PChar, "pir_KillFort", 0) +
             Statistic_AddValue(PChar, "eng_KillFort", 0) +
             Statistic_AddValue(PChar, "fra_KillFort", 0) +
             Statistic_AddValue(PChar, "spa_KillFort", 0) +
             Statistic_AddValue(PChar, "hol_KillFort", 0));
             
    GameInterface.TABLE_NATION.tr2.td1.str = "Городов захвачено";
	GameInterface.TABLE_NATION.tr2.td1.scale = 0.9;
	GameInterface.TABLE_NATION.tr2.td2.str = Statistic_AddValue(PChar, "eng_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td3.str = Statistic_AddValue(PChar, "fra_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td4.str = Statistic_AddValue(PChar, "spa_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td5.str = Statistic_AddValue(PChar, "hol_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td6.str = Statistic_AddValue(PChar, "pir_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td7.str = (Statistic_AddValue(PChar, "pir_TakeTown", 0) +
             Statistic_AddValue(PChar, "eng_TakeTown", 0) +
             Statistic_AddValue(PChar, "fra_TakeTown", 0) +
             Statistic_AddValue(PChar, "spa_TakeTown", 0) +
             Statistic_AddValue(PChar, "hol_TakeTown", 0));
             
    GameInterface.TABLE_NATION.tr3.td1.str = "Городов разграблено";
	GameInterface.TABLE_NATION.tr3.td1.scale = 0.9;
	GameInterface.TABLE_NATION.tr3.td2.str = Statistic_AddValue(PChar, "eng_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td3.str = Statistic_AddValue(PChar, "fra_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td4.str = Statistic_AddValue(PChar, "spa_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td5.str = Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td6.str = Statistic_AddValue(PChar, "pir_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td7.str = (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "hol_GrabbingTown", 0));
             
    GameInterface.TABLE_NATION.tr4.td1.str = "Кораблей захвачено";
	GameInterface.TABLE_NATION.tr4.td1.scale = 0.9;
	GameInterface.TABLE_NATION.tr4.td2.str = Statistic_AddValue(PChar, "eng_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td3.str = Statistic_AddValue(PChar, "fra_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td4.str = Statistic_AddValue(PChar, "spa_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td5.str = Statistic_AddValue(PChar, "hol_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td6.str = Statistic_AddValue(PChar, "pir_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td7.str = (Statistic_AddValue(PChar, "pir_AbordShip", 0) +
             Statistic_AddValue(PChar, "eng_AbordShip", 0) +
             Statistic_AddValue(PChar, "fra_AbordShip", 0) +
             Statistic_AddValue(PChar, "spa_AbordShip", 0) +
             Statistic_AddValue(PChar, "hol_AbordShip", 0));
             
    GameInterface.TABLE_NATION.tr5.td1.str = "Кораблей потоплено";
	GameInterface.TABLE_NATION.tr5.td1.scale = 0.9;
	GameInterface.TABLE_NATION.tr5.td2.str = Statistic_AddValue(PChar, "eng_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td3.str = Statistic_AddValue(PChar, "fra_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td4.str = Statistic_AddValue(PChar, "spa_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td5.str = Statistic_AddValue(PChar, "hol_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td6.str = Statistic_AddValue(PChar, "pir_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td7.str = (Statistic_AddValue(PChar, "pir_KillShip", 0) +
             Statistic_AddValue(PChar, "eng_KillShip", 0) +
             Statistic_AddValue(PChar, "fra_KillShip", 0) +
             Statistic_AddValue(PChar, "spa_KillShip", 0) +
             Statistic_AddValue(PChar, "hol_KillShip", 0));

	GameInterface.TABLE_MONEY.tr1.td1.str = "Расходы";
	GameInterface.TABLE_MONEY.tr1.td1.scale = 0.9;
	GameInterface.TABLE_MONEY.tr1.td2.str = Statistic_AddValue(PChar, "Money_spend", 0);
	GameInterface.TABLE_MONEY.tr1.td2.scale = 0.9;
	
	GameInterface.TABLE_MONEY.tr2.td1.str = "Выплаты команде";
	GameInterface.TABLE_MONEY.tr2.td1.scale = 0.9;
	GameInterface.TABLE_MONEY.tr2.td2.str = Statistic_AddValue(PChar, "PartitionPay", 0);
	GameInterface.TABLE_MONEY.tr2.td2.scale = 0.9;
	
    Table_UpdateWindow("TABLE_SHIPCLASS");
    Table_UpdateWindow("TABLE_HUMAN");
    Table_UpdateWindow("TABLE_OTHER");
    Table_UpdateWindow("TABLE_NATION");
    Table_UpdateWindow("TABLE_MONEY");
    //  ростовщики
    GameInterface.TABLE_CREDIT.hr.td1.str = "Кредит в городе";
	GameInterface.TABLE_CREDIT.hr.td1.scale = 0.9;
	GameInterface.TABLE_CREDIT.hr.td2.str = "Сумма";
	GameInterface.TABLE_CREDIT.hr.td2.scale = 0.9;
	GameInterface.TABLE_CREDIT.hr.td3.str = "Дата";
	GameInterface.TABLE_CREDIT.hr.td3.scale = 0.9;
	GameInterface.TABLE_CREDIT.hr.td4.str = "Срок (мес.)";
	GameInterface.TABLE_CREDIT.hr.td4.scale = 0.9;
	GameInterface.TABLE_CREDIT.hr.td5.str = "%";
	GameInterface.TABLE_CREDIT.hr.td5.scale = 0.9;
	GameInterface.TABLE_CREDIT.select = 0;
	
    aref quests;
	aref quest;
	int  nQuestsNum;
	int  n;
	string sQuestName;
	i = 1;
    if (CheckAttribute(pchar, "Quest.Loans"))
    {
    	makearef(quests, pchar.Quest.Loans);

    	nQuestsNum = GetAttributesNum(quests);

    	for(n = 0; n < nQuestsNum; n++)
    	{
    		quest = GetAttributeN(quests,n);

    		sQuestName = GetAttributeName(quest);
    		row = "tr" + i;
    		i++;
    		GameInterface.TABLE_CREDIT.(row).td1.str = GetCityName(sQuestName);
			GameInterface.TABLE_CREDIT.(row).td1.scale = 0.85;
			GameInterface.TABLE_CREDIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Loans.(sQuestName).Sum), MONEY_SIGN,MONEY_DELIVER);
			GameInterface.TABLE_CREDIT.(row).td2.scale = 0.75;
			GameInterface.TABLE_CREDIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Loans.(sQuestName).StartDay),
                               sti(Pchar.Quest.Loans.(sQuestName).StartMonth),
                               sti(Pchar.Quest.Loans.(sQuestName).StartYear));
			GameInterface.TABLE_CREDIT.(row).td3.scale = 0.8;
			GameInterface.TABLE_CREDIT.(row).td4.str = Pchar.Quest.Loans.(sQuestName).Period;
			GameInterface.TABLE_CREDIT.(row).td4.scale = 0.9;
			GameInterface.TABLE_CREDIT.(row).td5.str = Pchar.Quest.Loans.(sQuestName).Interest;
			GameInterface.TABLE_CREDIT.(row).td5.scale = 0.9;
        }
    }
	Table_UpdateWindow("TABLE_CREDIT");
	
	GameInterface.TABLE_DEBIT.hr.td1.str = "Вклад в городе";
	GameInterface.TABLE_DEBIT.hr.td1.scale = 0.9;
	GameInterface.TABLE_DEBIT.hr.td2.str = "Сумма";
	GameInterface.TABLE_DEBIT.hr.td2.scale = 0.9;
	GameInterface.TABLE_DEBIT.hr.td3.str = "Дата";
	GameInterface.TABLE_DEBIT.hr.td3.scale = 0.9;
	GameInterface.TABLE_DEBIT.hr.td4.str = "%";
	GameInterface.TABLE_DEBIT.hr.td4.scale = 0.9;
	GameInterface.TABLE_DEBIT.select = 0;
	i = 1;
    if (CheckAttribute(pchar, "Quest.Deposits")) // не треться при возврате
    {
    	makearef(quests,Characters[GetMainCharacterIndex()].Quest.Deposits);

    	nQuestsNum = GetAttributesNum(quests);

    	for(n = 0; n < nQuestsNum; n++)
    	{
    		quest = GetAttributeN(quests,n);

    		sQuestName = GetAttributeName(quest);
    		if (CheckAttribute(Pchar, "Quest.Deposits."+sQuestName+".Sum"))
    		{
                row = "tr" + i;
    			i++;
                GameInterface.TABLE_DEBIT.(row).td1.str = GetCityName(sQuestName);
				GameInterface.TABLE_DEBIT.(row).td1.scale = 0.85;
				GameInterface.TABLE_DEBIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Deposits.(sQuestName).Sum), MONEY_SIGN,MONEY_DELIVER);
				GameInterface.TABLE_DEBIT.(row).td2.scale = 0.75;
				GameInterface.TABLE_DEBIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Deposits.(sQuestName).StartDay),
	                               sti(Pchar.Quest.Deposits.(sQuestName).StartMonth),
	                               sti(Pchar.Quest.Deposits.(sQuestName).StartYear));
				GameInterface.TABLE_DEBIT.(row).td3.scale = 0.8;
				GameInterface.TABLE_DEBIT.(row).td4.str = Pchar.Quest.Deposits.(sQuestName).Interest;
				GameInterface.TABLE_DEBIT.(row).td4.scale = 0.9;
			}
        }
    }
	Table_UpdateWindow("TABLE_DEBIT");
	
	FillShipPlaceTable("TABLE_SHIP_PLACE"); // 1.2.3
	
	FillPriceListTown("TABLE_CITY");
}

void FillShipPlaceTable(string _tabName)
{
    int     i, cn, n;
    string  row;
    ref     rCity, chref;

    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Фото";
    GameInterface.(_tabName).hr.td1.scale = 0.9;
	GameInterface.(_tabName).hr.td2.str = "Класс";
	GameInterface.(_tabName).hr.td2.scale = 0.9;
    GameInterface.(_tabName).hr.td3.str = "Корабль";
    GameInterface.(_tabName).hr.td3.scale = 0.9;
    GameInterface.(_tabName).hr.td4.str = "Капитан";
    GameInterface.(_tabName).hr.td4.scale = 0.9;
	GameInterface.(_tabName).hr.td5.str = "Город";
	GameInterface.(_tabName).hr.td5.scale = 0.9;
	GameInterface.(_tabName).hr.td6.str = "Локация";
	GameInterface.(_tabName).hr.td6.scale = 0.9;
	GameInterface.(_tabName).hr.td7.str = "Дата стоянки";
	GameInterface.(_tabName).hr.td7.scale = 0.9;
	GameInterface.(_tabName).hr.td8.str = "Цена в месяц";
	GameInterface.(_tabName).hr.td8.scale = 0.9;
    // <--
    cn = 1;
    for (n=0; n<MAX_COLONIES; n++)
	{
		rCity = &Colonies[n];
		for (i=1; i<MAX_CHARACTERS; i++)
    	{
    		makeref(chrefsp, Characters[i]);
    		if (CheckAttribute(chrefsp, "ShipInStockMan"))
    		{
                if (chrefsp.ShipInStockMan == (rCity.id + "_PortMan"))
		        {
                    int iShip = chrefsp.ship.type;
					ref refBaseShip = GetRealShip(iShip);
					string shipTexture = refBaseShip.BaseName;
					
                    row = "tr" + cn;
                    // GameInterface.(_tabName).(row).td1.str = cn;
                    // GameInterface.(_tabName).(row).td1.scale = 0.9;
					GameInterface.(_tabName).(row).index = chrefsp.id;
					GameInterface.(_tabName).(row).td1.icon.texture = "interfaces\ships\" + shipTexture + ".tga";
					// GameInterface.(_tabName).(row).td1.icon.texture  = "interfaces\Frame1.tga";
					GameInterface.(_tabName).(row).td1.icon.uv = "0,0,1,1";
	                GameInterface.(_tabName).(row).td1.icon.offset = "-2, 0";
	                GameInterface.(_tabName).(row).td1.icon.width  = 40;
				    GameInterface.(_tabName).(row).td1.icon.height = 40;
					GameInterface.(_tabName).(row).td2.str = refBaseShip.Class;
				    GameInterface.(_tabName).(row).td2.scale = 0.8;
				    GameInterface.(_tabName).(row).td3.str = XI_ConvertString(RealShips[sti(chrefsp.Ship.Type)].BaseName) + " '" + chrefsp.Ship.Name + "'";
				    GameInterface.(_tabName).(row).td3.scale = 0.8;
	                GameInterface.(_tabName).(row).td4.icon.texture = "INTERFACES\PORTRAITS\128\face_" + chrefsp.faceId + ".tga";
					// GameInterface.(_tabName).(row).td4.icon.texture  = "interfaces\Frame2.tga";
	                GameInterface.(_tabName).(row).td4.icon.uv = "0,0,1,1";
	                GameInterface.(_tabName).(row).td4.icon.offset = "-2, 0";
	                GameInterface.(_tabName).(row).td4.icon.width  = 40;
				    GameInterface.(_tabName).(row).td4.icon.height = 40;
				    GameInterface.(_tabName).(row).td4.str = GetFullName(chrefsp);
				    GameInterface.(_tabName).(row).td4.textoffset = "40, 0";
				    GameInterface.(_tabName).(row).td4.scale = 0.8;
                    GameInterface.(_tabName).(row).td5.icon.group  = "NATIONS";
					GameInterface.(_tabName).(row).td5.icon.image  = Nations[sti(rCity.nation)].Name;
					GameInterface.(_tabName).(row).td5.icon.width  = 40;
				    GameInterface.(_tabName).(row).td5.icon.height = 40;
				    GameInterface.(_tabName).(row).td5.icon.offset = "-2, 0";
					GameInterface.(_tabName).(row).td5.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
					GameInterface.(_tabName).(row).td5.scale = 0.8;
					GameInterface.(_tabName).(row).td5.textoffset = "30, 0";
					GameInterface.(_tabName).(row).td6.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
					GameInterface.(_tabName).(row).td6.scale = 0.8;
					GameInterface.(_tabName).(row).td7.str = chrefsp.ShipInStockMan.AltDate;
					GameInterface.(_tabName).(row).td7.scale = 0.8;
					GameInterface.(_tabName).(row).td8.str = chrefsp.ShipInStockMan.MoneyForShip;
					GameInterface.(_tabName).(row).td8.scale = 0.8;
                    
    		        cn++;
		        }
    		}
        }
	}
	Table_UpdateWindow(_tabName);
}

void FillPriceListTown(string _tabName)
{
    int     i, cn, n, StoreNum;
    ref     chref;
    string  row, firstId, CityId;
    aref    curItem;
    ref     rCity;
	ref		refStorage;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.75;
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.75;
	GameInterface.(_tabName).hr.td3.str = "Локация";
	GameInterface.(_tabName).hr.td3.scale = 0.75;
	GameInterface.(_tabName).hr.td4.str = "Загруженность";
	GameInterface.(_tabName).hr.td4.scale = 0.75;
	GameInterface.(_tabName).hr.td5.str = "Аренда";
	GameInterface.(_tabName).hr.td5.scale = 0.75;

	cn = 1;
	for (i=1; i<MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "Storage.Activate"))
		{
			row = "tr" + cn;
			CityId = chref.city;
			rCity = GetColonyByIndex(FindColony(CityId));
			StoreNum = GetStorage(CityId);
			refStorage = &stores[StoreNum];
			if (n == 0) firstId = rCity.id;
			GameInterface.(_tabName).(row).UserData.CityID  = rCity.id;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
			GameInterface.(_tabName).(row).td1.icon.height = 26;
			GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;	
			GameInterface.(_tabName).(row).td4.str = GetStorageUsedWeight(refStorage) + " / " + iMaxGoodsStore;
			GameInterface.(_tabName).(row).td4.scale = 0.8;	
			GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.MoneyForStorage);
			GameInterface.(_tabName).(row).td5.scale = 0.8;	
			cn++;
		}
	}
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_GOODS");
    if (CurTable == "TABLE_CITY")
    {
    	FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
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

void FillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
	int		StoreNum, iStoreQ;
    int     i, n;
    ref     nulChr;
    string  row;
	ref 	chref;
    ref		refStorage;
	
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
    GameInterface.(_tabName).hr.td1.scale = 0.75;
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("In the storage");
	GameInterface.(_tabName).hr.td2.scale = 0.75;
	GameInterface.(_tabName).hr.td3.str = "Пачка";
	GameInterface.(_tabName).hr.td3.scale = 0.75;
	GameInterface.(_tabName).hr.td4.str = "Вес";
	GameInterface.(_tabName).hr.td4.scale = 0.75;
	
	n = 1;
	if (attr1 != "")
	{
		StoreNum = GetStorage(attr1);
		if(StoreNum > 0)
		{
			refStorage = &stores[StoreNum];
			for (i = 0; i < GOODS_QUANTITY; i++) 
			{
				row = "tr" + n;
				sGoods = "Gidx" + i;	
				iStoreQ = GetStorageGoodsQuantity(refStorage, i); 	
				if(iStoreQ == 0) continue;
				GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
				GameInterface.(_tabName).(row).UserData.IDX = i;
				GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
				GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
				GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
				GameInterface.(_tabName).(row).td1.icon.width = 32;
				GameInterface.(_tabName).(row).td1.icon.height = 32;
				GameInterface.(_tabName).(row).td1.textoffset = "30,0";
				GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
				GameInterface.(_tabName).(row).td1.scale = 0.85;
				GameInterface.(_tabName).(row).td2.str = iStoreQ;
				GameInterface.(_tabName).(row).td3.str = Goods[i].Units;
				GameInterface.(_tabName).(row).td4.str = GetGoodWeightByType(i, iStoreQ);
				n++;
			}	
		}
	}
    Table_UpdateWindow(_tabName);
}
