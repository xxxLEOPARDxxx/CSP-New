/// boal 07/06/06 переделка СЖ под нужны ВМЛ
int curQuestTop;
string CurTable, CurRow;
int iMaxGoodsStore = 50000;
string sMessageMode;
ref chrefsp;
int FState_SHIP_N_L = 0;
int FState_SHIP_L = 8;
int FState_SHIP_N_R = 0;
int FState_SHIP_R = 8;
int FState_BLADE = 0;
int FState_BLADEQ = 0;
int FState_GunQ = 0;
int FState_BONUS = 0;
int Last_Left_Ship = -1;//запоминаем выбранный в таблице корабль
int Last_Right_Ship = -1;
int rownumberach;

string GunTypeQ[4]={"poor","ordinary","good","excellent"};//фильтр оружия по качеству
string BladeTypeQ[4]={"poor","ordinary","good","excellent"};//фильтр оружия по качеству
string BladeType[3]={"FencingLight","Fencing","FencingHeavy"};//фильтр оружия по тяжести

string BonusType[7]={"backpack","Totem","indian","jewelry","cirass","talisman","mineral"};//фильтр предметов по типам
string ShipNation[5]={"england","france","holland","spain","pirate"};

void InitInterface(string iniName)
{
	InterfaceStack.SelectMenu_node = "LaunchQuestBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleQuestBook";

	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED)
	{
	string sTemp = RealShips[sti(Pchar.Ship.Type)].BaseName;
	Pchar.Encyclopedia.(sTemp) = "1";
	}
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
	SetEventHandler("CheckButtonChange", "ProcessFilter", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowPGGInfo","ShowPGGInfo",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("ShowShipsWindow","ShowShipsWindow",0);
	SetEventHandler("ShowBladeWindow","ShowBladeWindow",0);
	SetEventHandler("ShowGunWindow","ShowGunWindow",0);
	SetEventHandler("ShowFoodWindow","ShowFoodWindow",0);
	SetEventHandler("ShowBonusItemWindow","ShowBonusItemWindow",0);
	SetEventHandler("PointsEX","PointsEX",0);
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
//инфа о кораблях
void ShowShipsWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",true);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",false);
	XI_WindowShow("ENC_INFO_BONUSITEM",false);
	XI_WindowShow("ENC_INFO_ACHIEVEMENTS",false);

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
	SetNodeUsing("SHIP_TABLE_LIST_LEFT",true);
	SetNodeUsing("SHIP_TABLE_LIST_RIGHT",true);
	FillShipInfoEncy("SHIP_TABLE_LIST_LEFT");
	FillShipInfoEncy("SHIP_TABLE_LIST_RIGHT");
}

void ShowBladeWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",true);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",false);
	XI_WindowShow("ENC_INFO_BONUSITEM",false);
	XI_WindowShow("ENC_INFO_ACHIEVEMENTS",false);

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
	AddToTable("BLADE_TABLE_LIST", "blade");
}

void ShowGunWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",true);
	XI_WindowShow("ENC_INFO_FOOD",false);
	XI_WindowShow("ENC_INFO_BONUSITEM",false);
	XI_WindowShow("ENC_INFO_ACHIEVEMENTS",false);

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
	AddToTable("GUN_TABLE_LIST", "gun");
}

void ShowFoodWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",true);
	XI_WindowShow("ENC_INFO_BONUSITEM",false);
	XI_WindowShow("ENC_INFO_ACHIEVEMENTS",false);

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
	AddToTable("FOOD_TABLE_LIST", "food");
}

void ShowBonusItemWindow()
{
	XI_WindowShow("ENC_INFO_SHIP",false);
	XI_WindowShow("ENC_INFO_BLADE",false);
	XI_WindowShow("ENC_INFO_GUN",false);
	XI_WindowShow("ENC_INFO_FOOD",false);
	XI_WindowShow("ENC_INFO_BONUSITEM",true);
	XI_WindowShow("ENC_INFO_ACHIEVEMENTS",true);

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
	AddToTable("BONUSITEM_TABLE_LIST", "BonusItem");
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
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("CheckButtonChange", "ProcessFilter");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
 	DelEventHandler("QuestDeActivate","QuestDeActivate");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowPGGInfo","ShowPGGInfo");
	DelEventHandler("ShowShipsWindow","ShowShipsWindow");
	DelEventHandler("ShowBladeWindow","ShowBladeWindow");
	DelEventHandler("ShowGunWindow","ShowGunWindow");
	DelEventHandler("ShowFoodWindow","ShowFoodWindow");
	DelEventHandler("ShowBonusItemWindow","ShowBonusItemWindow");
	DelEventHandler("PointsEX", "PointsEX");

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
	HideInfoWindowEncy();
	HideAchievements();
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
	HideAchievements();
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
	HideAchievements();
	ShowButtons();
}

void selectAchievements() // Отображаем окно достижений
{
	rownumberach = 0;
	HideCashBook();
	HideQuests();
	HideStatistic();
	
	SetNodeUsing("ACHIEVEMENTS_INFO_FADER",true);
	SetNodeUsing("ACHIEVEMENTS_INFO_DUST",true);
	SetNodeUsing("ACHIEVEMENTS_INFO_FRAME",true);
	SetNodeUsing("TABLE_ACHIEVEMENTS",true);
	SetNodeUsing("SCROLL_ACHIEVEMENTS",true);
	
	SetNodeUsing("SHIP_INFO_FADER",false);
	SetNodeUsing("SHIP_INFO_DUST",false);
	SetNodeUsing("SHIP_INFO_FRAME",false);
	SetNodeUsing("SHIP_INFO_FRAME_CAPTION",false);
	SetNodeUsing("SHIP_TABLE_LIST_LEFT",false);
	SetNodeUsing("SHIP_TABLE_LIST_RIGHT",false);
	SetNodeUsing("SHIP_TABLE_SCROLL_LEFT",false);
	SetNodeUsing("SHIP_TABLE_SCROLL_RIGHT",false);
	SetNodeUsing("SHIP_TABLE_OTHER_LEFT",false);
	SetNodeUsing("SHIP_TABLE_OTHER_RIGHT",false);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_LEFT",false);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_RIGHT",false);
	SetNodeUsing("SHIP_INFO_TEXT_LEFT",false);
	SetNodeUsing("SHIP_INFO_TEXT_RIGHT",false);
	SetNodeUsing("SHIP_CLASS_LEFT",false);
	SetNodeUsing("SHIP_NATION_LEFT",false);
	SetNodeUsing("SHIP_CLASS_RIGHT",false);
	SetNodeUsing("SHIP_NATION_RIGHT",false);
	SetNewPicture("S_NATION_E_L", "");
	SetNewPicture("S_NATION_F_L", "");
	SetNewPicture("S_NATION_H_L", "");
	SetNewPicture("S_NATION_S_L", "");
	SetNewPicture("S_NATION_P_L", "");
	SetNewPicture("S_NATION_E_R", "");
	SetNewPicture("S_NATION_F_R", "");
	SetNewPicture("S_NATION_H_R", "");
	SetNewPicture("S_NATION_S_R", "");
	SetNewPicture("S_NATION_P_R", "");
	SetNodeUsing("BLADE_INFO_FADER",false);
	SetNodeUsing("BLADE_INFO_DUST",false);
	SetNodeUsing("BLADE_INFO_FRAME",false);
	SetNodeUsing("BLADE_INFO_FRAME_CAPTION",false);
	SetNodeUsing("BLADE_TABLE_LIST_SCROLL",false);
	SetNodeUsing("BLADE_TABLE_LIST",false);
	SetNodeUsing("BLADE_TYPE_CLASS",false);
	SetNodeUsing("BLADE_TYPE_Quality",false);
	SetNodeUsing("GUN_INFO_FADER",false);
	SetNodeUsing("GUN_INFO_DUST",false);
	SetNodeUsing("GUN_INFO_FRAME",false);
	SetNodeUsing("GUN_INFO_FRAME_CAPTION",false);
	SetNodeUsing("GUN_TABLE_LIST_SCROLL",false);
	SetNodeUsing("GUN_TABLE_LIST",false);
	SetNodeUsing("GUN_TYPE_QUALITY",false);
	SetNodeUsing("FOOD_INFO_FADER",false);
	SetNodeUsing("FOOD_INFO_DUST",false);
	SetNodeUsing("FOOD_INFO_FRAME",false);
	SetNodeUsing("FOOD_INFO_FRAME_CAPTION",false);
	SetNodeUsing("FOOD_TABLE_LIST_SCROLL",false);
	SetNodeUsing("FOOD_TABLE_LIST",false);
	SetNodeUsing("BONUSITEM_INFO_FADER",false);
	SetNodeUsing("BONUSITEM_INFO_DUST",false);
	SetNodeUsing("BONUSITEM_INFO_FRAME",false);
	SetNodeUsing("BONUSITEM_INFO_FRAME_CAPTION",false);
	SetNodeUsing("BONUSITEM_TABLE_LIST_SCROLL",false);
	SetNodeUsing("BONUSITEM_TABLE_LIST",false);
	SetNodeUsing("BONUSITEM_CLASS",false);
	
	FillATableHeader();
	FillATableInfo();
	
	SetNodeUsing("ACHIEVEMENTS_STR",true);
	SetNodeUsing("POINTS_EXCHANGE",true);
	SetFormatedText("ACHIEVEMENTS_INFO_FRAME_CAPTION", "Система достижений с возможностью получения различных наград");
	SetFormatedText("ACHIEVEMENTS_STR", "Очков достижений: " + sti(pchar.ach_points)); // Очки достижений
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
	SetNewPicture("SHIP_PICTURE_L", "None");
	SetNewPicture("SHIP_PICTURE_R", "None");
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
	
    if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.HullSpecial")) SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLON");
	else SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLOFF");
	if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.SailsSpecial")) SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILON");
	else SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILOFF");
	if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.CannonsSpecial")) SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSON");
	else SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSOFF");
	if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.CuBot")) SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGON");
	else SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGOFF");
	if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.BotPack")) SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOn");
	else SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOff");
	if (CheckAttribute(RealShips[sti(chrefspp.Ship.Type)],"Tuning.HighBort")) SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOn");
	else SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOff");

	XI_WindowShow("SHOW_ADV_INFO", true);
	XI_WindowDisable("SHOW_ADV_INFO", false);
	sMessageMode = "RPG_Hint";
	}
}

// Обмен очков достижений
void PointsEX() {
	IDoExit(RC_INTERFACE_POINTS_EX);		   
}

void FillATableHeader() // Заполним заголовок таблицы достижений
{
    GameInterface.TABLE_ACHIEVEMENTS.hr.td1.str = "Уровень";
	GameInterface.TABLE_ACHIEVEMENTS.hr.td1.scale = 0.9;
	GameInterface.TABLE_ACHIEVEMENTS.hr.td2.str = "Достижение";
	GameInterface.TABLE_ACHIEVEMENTS.hr.td2.scale = 0.9;
	GameInterface.TABLE_ACHIEVEMENTS.hr.td3.str = "Описание";
	GameInterface.TABLE_ACHIEVEMENTS.hr.td3.scale = 0.9;
	GameInterface.TABLE_ACHIEVEMENTS.hr.td4.str = "Прогресс";
	GameInterface.TABLE_ACHIEVEMENTS.hr.td4.scale = 0.9;
	GameInterface.TABLE_ACHIEVEMENTS.hr.td5.str = "Очки";
	GameInterface.TABLE_ACHIEVEMENTS.hr.td5.scale = 0.9;
	GameInterface.TABLE_ACHIEVEMENTS.select = 0;
}

void FillATableInfo() // Заполним таблицу достижений информацией
{
	string row;
	int  n;
	int z = 41;
	if(bPortPermission) z++;
	if(bBribeSoldiers) z++;
	if(startherotype == 1 || startherotype == 2) z++;
	
    for(n = 1; n < z+1; n++)
    {
    	row = "tr" + n;
		
		// Размеры текста
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.scale = 1.1;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.scale = 0.85;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td3.scale = 0.75;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td4.scale = 0.8;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td5.scale = 0.9;
		
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = "-";
	}
	
	aref aroot,arcur;
	makearef(aroot,pchar.achievements);
	
	string attrname;
	int i;
	
	// Сортировка по уровню выполненных достижений
	for(i=0; i<z; i++)
	{
		arcur = GetAttributeN(aroot,i);
		
		attrname = GetAttributeName(arcur);
		if(sti(pchar.achievements.(attrname)) == 3) SetTableRowByAchievement(attrname, sti(pchar.achievements.(attrname)));
	}
	
	for(i=0; i<z; i++)
	{
		arcur = GetAttributeN(aroot,i);
		
		attrname = GetAttributeName(arcur);
		if(sti(pchar.achievements.(attrname)) == 2) SetTableRowByAchievement(attrname, sti(pchar.achievements.(attrname)));
	}
	
	for(i=0; i<z; i++)
	{
		arcur = GetAttributeN(aroot,i);
		
		attrname = GetAttributeName(arcur);
		if(sti(pchar.achievements.(attrname)) == 1) SetTableRowByAchievement(attrname, sti(pchar.achievements.(attrname)));
	}
	
	for(i=0; i<z; i++)
	{
		arcur = GetAttributeN(aroot,i);
		
		attrname = GetAttributeName(arcur);
		if(sti(pchar.achievements.(attrname)) == 0) SetTableRowByAchievement(attrname, sti(pchar.achievements.(attrname)));
	}
	
	Table_UpdateWindow("TABLE_ACHIEVEMENTS");
}

void SetTableRowByAchievement(string ach_id, int level)
{
	string row;
	
	rownumberach++
	row = "tr" + rownumberach;
	
	GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.width = 64;
	GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.height = 64;
	GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.offset = "-2, 0";
	GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.group = "ACHIEVEMENTS";
	GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.image = GetAchievementIcon(ach_id);	

	if(ach_id == "WhisperLine")
	{
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.group = "FACE128_543";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.image = "face";	
	}
	if(ach_id == "CapBladLine")
	{
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.group = "FACE128_221";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.icon.image = "face";	
	}
	
	if(level == 3)
	{
		GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = "";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.icon.width = 25;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.icon.height = 25;
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.icon.offset = "-24, 40";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.icon.group = "ICONS";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.icon.image = "complete";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.str = GetAchievementName(ach_id, level);
		GameInterface.TABLE_ACHIEVEMENTS.(row).td3.str = GetAchievementDescrible(ach_id, level);
		GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = "Выполнено";
		GameInterface.TABLE_ACHIEVEMENTS.(row).td5.str = "+ 100";
		
		GameInterface.TABLE_ACHIEVEMENTS.(row).td2.color = argb(255,196,255,196);
		GameInterface.TABLE_ACHIEVEMENTS.(row).td3.color = argb(255,196,255,196);
		GameInterface.TABLE_ACHIEVEMENTS.(row).td4.color = argb(255,196,255,196);
		GameInterface.TABLE_ACHIEVEMENTS.(row).td5.color = argb(255,196,255,196);

	}
	else
	{
		if(ach_id == "Nation_quest_E" || ach_id == "Nation_quest_F" || ach_id == "Nation_quest_H" || ach_id == "Nation_quest_S" || ach_id == "Nation_quest_P" || ach_id == "Isabella_quest" || ach_id == "LSC_quest" || ach_id == "Teno_quest" || ach_id == "Killbeggars_quest" 
		|| ach_id == "Ghostship_quest" || ach_id == "Bluebird_quest" || ach_id == "Berglarsgang_quest" || ach_id == "Mummydust_quest" || ach_id == "Enchantcity_quest" 
		|| ach_id == "ships" || ach_id == "bank_money" || ach_id == "CapBladLine" || ach_id == "WhisperLine" || ach_id == "AchShipSearch")
		{
			// GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = "1 ур.";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = "1";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.fontidx = 0; // LEO Я тут лазил
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.textoffset = "38, 20";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.scale = 0.65;
			GameInterface.TABLE_ACHIEVEMENTS.(row).td2.str = GetAchievementName(ach_id, 3);
			GameInterface.TABLE_ACHIEVEMENTS.(row).td3.str = GetAchievementDescrible(ach_id, 3);
			GameInterface.TABLE_ACHIEVEMENTS.(row).td5.str = "+ 100";
		}
		else
		{
			// GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = (level+1) + " ур.";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.str = (level+1) + "";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.fontidx = 0; // LEO Я тут лазил
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.textoffset = "38, 20";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td1.scale = 0.65;
			GameInterface.TABLE_ACHIEVEMENTS.(row).td2.str = GetAchievementName(ach_id, (level+1));
			GameInterface.TABLE_ACHIEVEMENTS.(row).td3.str = GetAchievementDescrible(ach_id, (level+1));
			if(level == 2) GameInterface.TABLE_ACHIEVEMENTS.(row).td5.str = "+ 100";
			if(level == 1) GameInterface.TABLE_ACHIEVEMENTS.(row).td5.str = "+ 50";
			if(level == 0) GameInterface.TABLE_ACHIEVEMENTS.(row).td5.str = "+ 25";
			
			if(level == 2)
			{
				GameInterface.TABLE_ACHIEVEMENTS.(row).td1.color = argb(255,9,110,255);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td2.color = argb(255,179,171,255);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td3.color = argb(255,179,171,255);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td4.color = argb(255,179,171,255);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td5.color = argb(255,179,171,255);
			}
			
			if(level == 1)
			{
				GameInterface.TABLE_ACHIEVEMENTS.(row).td1.color = argb(255,255,110,9);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td2.color = argb(255,255,171,171);
				GameInterface.TABLE_ACHIEVEMENTS.(row).td3.color = argb(255,255,171,171)
				GameInterface.TABLE_ACHIEVEMENTS.(row).td4.color = argb(255,255,171,171)
				GameInterface.TABLE_ACHIEVEMENTS.(row).td5.color = argb(255,255,171,171)
			}
		}
		
		string strprogress;
		
		if((level == 2) || (level == 1) || (level == 0))
		{
			if(ach_id == "rank") strprogress = "Ранг персонажа:";
			if(ach_id == "money") strprogress = "Деньги персонажа:";
			if(ach_id == "bank_money") strprogress = "Сумма вкладов:";
			if(ach_id == "AchTreasure") strprogress = "Найдено кладов:";
			if(ach_id == "AchBlood") strprogress = "Вызвано кровотечений:";
			if(ach_id == "AchTravma") strprogress = "Нанесено травм:";
			if(ach_id == "AchStanS") strprogress = "Нанесено резких ударов:";
			if(ach_id == "AchStanH") strprogress = "Вызвано оглушений:";
			if(ach_id == "AchChest") strprogress = "Вскрыто сундуков:";
			if(ach_id == "taxes") strprogress = "Портовые сборы оплачены:";
			if(ach_id == "AchVzyatka") strprogress = "Выдано взяток:";
			if(ach_id == "kills") strprogress = "Убийств совершено:";
			if(ach_id == "ship_kills") strprogress = "Кораблей потоплено:";
			if(ach_id == "skel_kills") strprogress = "Убито нежити:";
			if(ach_id == "poisons") strprogress = "Нанесено отравляющих ударов:";
			if(ach_id == "criticals") strprogress = "Нанесено критических ударов:";
			if(ach_id == "craft") strprogress = "Создано предметов:";
			if(ach_id == "books") strprogress = "Книг прочитано:";
			if(ach_id == "officers") strprogress = "Офицеров нанято:";
			if(ach_id == "ships") strprogress = "Кораблей в эскадре:";
			if(ach_id == "heal_bottles") strprogress = "Выпито лечебных зелий:";
			if(ach_id == "AchFood") strprogress = "Скушано еды:";
			if(ach_id == "gen_quests") strprogress = "Выполнено генераторных квестов:";
			if(ach_id == "AchBuildColony") strprogress = "Отстройка колонии:";
			if(ach_id == "AchTurnir") strprogress = "Выиграно турниров:";
			if(ach_id == "AchDuelyant") strprogress = "Выиграно дуэлей:";
			if(ach_id == "AchShipOrder") strprogress = "Заказано кораблей:";
			if(ach_id == "AchShipSearch") strprogress = "Исследовано кораблей:";
			if(ach_id == "AchGoldFleet") strprogress = "Золотых флотов потоплено:";
			if(ach_id == "AchSityRobbery") strprogress = "Городов разграблено:";
			
			strprogress = strprogress + "\n";
		}
		
		int monstersall = sti(pchar.Statistic.Monster_s)+sti(pchar.Statistic.Monster_g);
		int killsall = sti(pchar.Statistic.Solder_s)+sti(pchar.Statistic.Citizen_s)+sti(pchar.Statistic.Warrior_s)+sti(pchar.Statistic.Monster_s)+sti(pchar.Statistic.Solder_g)+sti(pchar.Statistic.Citizen_g)+sti(pchar.Statistic.Warrior_g)+sti(pchar.Statistic.Monster_g);
		int killshipsall = sti(pchar.Statistic.KillShip_1)+sti(pchar.Statistic.KillShip_2)+sti(pchar.Statistic.KillShip_3)+sti(pchar.Statistic.KillShip_4)+sti(pchar.Statistic.KillShip_5)+sti(pchar.Statistic.KillShip_6)+sti(pchar.Statistic.KillShip_7)+sti(pchar.Statistic.AbordShip_1)+sti(pchar.Statistic.AbordShip_2)+sti(pchar.Statistic.AbordShip_3)+sti(pchar.Statistic.AbordShip_4)+sti(pchar.Statistic.AbordShip_5)+sti(pchar.Statistic.AbordShip_6)+sti(pchar.Statistic.AbordShip_7)+sti(pchar.Statistic.KillAbordShip_1)+sti(pchar.Statistic.KillAbordShip_2)+sti(pchar.Statistic.KillAbordShip_3)+sti(pchar.Statistic.KillAbordShip_4)+sti(pchar.Statistic.KillAbordShip_5)+sti(pchar.Statistic.KillAbordShip_6)+sti(pchar.Statistic.KillAbordShip_7);
		
		if(level == 2)
		{
			if(ach_id == "rank") strprogress = strprogress + sti(pchar.rank) + " / 40";
			if(ach_id == "money") strprogress = strprogress + MakeMoneyShow(sti(pchar.money), MONEY_SIGN,MONEY_DELIVER) + " / 15 000 000";
			if(ach_id == "taxes") strprogress = strprogress + sti(pchar.questTemp.taxescount) + " / 100";
			if(ach_id == "AchVzyatka") strprogress = strprogress + sti(pchar.questTemp.bribescount) + " / 50";
			if(ach_id == "kills") strprogress = strprogress + sti(killsall) + " / 500";
			if(ach_id == "ship_kills") strprogress = strprogress + sti(killshipsall) + " / 70";
			if(ach_id == "skel_kills") strprogress = strprogress + sti(monstersall) + " / 150";
			if(ach_id == "poisons") strprogress = strprogress + sti(pchar.questTemp.poisoncount) + " / 225";
			if(ach_id == "criticals") strprogress = strprogress + sti(pchar.questTemp.criticalcount) + " / 500";
			if(ach_id == "AchTreasure") strprogress = strprogress + sti(pchar.questTemp.treasurecount) + " / 30";
			if(ach_id == "AchBlood") strprogress = strprogress + sti(pchar.questTemp.bloodingcount) + " / 300";
			if(ach_id == "AchTravma") strprogress = strprogress + sti(pchar.questTemp.traumacount) + " / 300";
			if(ach_id == "AchStanS") strprogress = strprogress + sti(pchar.questTemp.swiftcount) + " / 300";
			if(ach_id == "AchStanH") strprogress = strprogress + sti(pchar.questTemp.stuncount) + " / 300";
			if(ach_id == "AchChest") strprogress = strprogress + sti(pchar.questTemp.chestcount) + " / 50";
			if(ach_id == "craft") strprogress = strprogress + sti(pchar.questTemp.craftcount) + " / 5000";
			if(ach_id == "books") strprogress = strprogress + sti(pchar.questTemp.bookcount) + " / 10";
			if(ach_id == "officers") strprogress = strprogress + sti(pchar.questTemp.officercount) + " / 10";
			if(ach_id == "heal_bottles") strprogress = strprogress + sti(pchar.questTemp.healcount) + " / 200";
			if(ach_id == "AchFood") strprogress = strprogress + sti(pchar.questTemp.foodcount) + " / 500";
			if(ach_id == "gen_quests") strprogress = strprogress + sti(pchar.questTemp.genquestcount) + " / 40";
			if(ach_id == "AchBuildColony") strprogress = strprogress + sti(pchar.questTemp.colonystate) + " / 3";
			if(ach_id == "AchTurnir") strprogress = strprogress + sti(pchar.questTemp.tournamentcount) + " / 10";
			if(ach_id == "AchDuelyant") strprogress = strprogress + sti(pchar.questTemp.duelcount) + " / 30";
			if(ach_id == "AchShipOrder") strprogress = strprogress + sti(pchar.questTemp.shipordercount) + " / 20";
			if(ach_id == "AchGoldFleet") strprogress = strprogress + sti(pchar.questTemp.GoldFleetNum) + " / 7";
			if(ach_id == "AchSityRobbery") strprogress = strprogress + (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "hol_GrabbingTown", 0)) + " / 15"
			GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = strprogress;
		}
		
		if(level == 1)
		{
			if(ach_id == "rank") strprogress = strprogress + sti(pchar.rank) + " / 25";
			if(ach_id == "money") strprogress = strprogress + MakeMoneyShow(sti(pchar.money), MONEY_SIGN,MONEY_DELIVER) + " / 5 000 000";
			if(ach_id == "taxes") strprogress = strprogress + sti(pchar.questTemp.taxescount) + " / 50";
			if(ach_id == "AchVzyatka") strprogress = strprogress + sti(pchar.questTemp.bribescount) + " / 25";
			if(ach_id == "kills") strprogress = strprogress + sti(killsall) + " / 150";
			if(ach_id == "ship_kills") strprogress = strprogress + sti(killshipsall) + " / 35";
			if(ach_id == "skel_kills") strprogress = strprogress + sti(monstersall) + " / 75";
			if(ach_id == "poisons") strprogress = strprogress + sti(pchar.questTemp.poisoncount) + " / 75";
			if(ach_id == "criticals") strprogress = strprogress + sti(pchar.questTemp.criticalcount) + " / 250";
			if(ach_id == "AchTreasure") strprogress = strprogress + sti(pchar.questTemp.treasurecount) + " / 15";
			if(ach_id == "AchBlood") strprogress = strprogress + sti(pchar.questTemp.bloodingcount) + " / 150";
			if(ach_id == "AchTravma") strprogress = strprogress + sti(pchar.questTemp.traumacount) + " / 150";
			if(ach_id == "AchStanS") strprogress = strprogress + sti(pchar.questTemp.swiftcount) + " / 150";
			if(ach_id == "AchStanH") strprogress = strprogress + sti(pchar.questTemp.stuncount) + " / 150";
			if(ach_id == "AchChest") strprogress = strprogress + sti(pchar.questTemp.chestcount) + " / 25";
			if(ach_id == "craft") strprogress = strprogress + sti(pchar.questTemp.craftcount) + " / 500";
			if(ach_id == "books") strprogress = strprogress + sti(pchar.questTemp.bookcount) + " / 6";
			if(ach_id == "officers") strprogress = strprogress + sti(pchar.questTemp.officercount) + " / 6";
			if(ach_id == "heal_bottles") strprogress = strprogress + sti(pchar.questTemp.healcount) + " / 100";
			if(ach_id == "AchFood") strprogress = strprogress + sti(pchar.questTemp.foodcount) + " / 250";
			if(ach_id == "gen_quests") strprogress = strprogress + sti(pchar.questTemp.genquestcount) + " / 20";
			if(ach_id == "AchBuildColony") strprogress = strprogress + sti(pchar.questTemp.colonystate) + " / 3";
			if(ach_id == "AchTurnir") strprogress = strprogress + sti(pchar.questTemp.tournamentcount) + " / 3";
			if(ach_id == "AchDuelyant") strprogress = strprogress + sti(pchar.questTemp.duelcount) + " / 15";
			if(ach_id == "AchShipOrder") strprogress = strprogress + sti(pchar.questTemp.shipordercount) + " / 10";
			if(ach_id == "AchGoldFleet") strprogress = strprogress + sti(pchar.questTemp.GoldFleetNum) + " / 3";
			if(ach_id == "AchSityRobbery") strprogress = strprogress + (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "hol_GrabbingTown", 0)) + " / 10"
			GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = strprogress;
		}
		
		if(level == 0)
		{
			if(ach_id == "rank") strprogress = strprogress + sti(pchar.rank) + " / 10";
			if(ach_id == "money") strprogress = strprogress + MakeMoneyShow(sti(pchar.money), MONEY_SIGN,MONEY_DELIVER) + " / 1 000 000";
			if(ach_id == "bank_money") strprogress = strprogress + MakeMoneyShow(sti(pchar.questTemp.depositcount), MONEY_SIGN,MONEY_DELIVER) + " / 50 000 000";
			if(ach_id == "AchShipSearch") strprogress = strprogress + sti(pchar.questTemp.shipsearchcount) + " / 124";
			if(ach_id == "taxes") strprogress = strprogress + sti(pchar.questTemp.taxescount) + " / 10";
			if(ach_id == "AchVzyatka") strprogress = strprogress + sti(pchar.questTemp.bribescount) + " / 5";
			if(ach_id == "kills") strprogress = strprogress + sti(killsall) + " / 50";
			if(ach_id == "ship_kills") strprogress = strprogress + sti(killshipsall) + " / 10";
			if(ach_id == "skel_kills") strprogress = strprogress + sti(monstersall) + " / 30";
			if(ach_id == "poisons") strprogress = strprogress + sti(pchar.questTemp.poisoncount) + " / 25";
			if(ach_id == "criticals") strprogress = strprogress + sti(pchar.questTemp.criticalcount) + " / 100";
			if(ach_id == "AchTreasure") strprogress = strprogress + sti(pchar.questTemp.treasurecount) + " / 5";
			if(ach_id == "AchBlood") strprogress = strprogress + sti(pchar.questTemp.bloodingcount) + " / 50";
			if(ach_id == "AchTravma") strprogress = strprogress + sti(pchar.questTemp.traumacount) + " / 50";
			if(ach_id == "AchStanS") strprogress = strprogress + sti(pchar.questTemp.swiftcount) + " / 50";
			if(ach_id == "AchStanH") strprogress = strprogress + sti(pchar.questTemp.stuncount) + " / 50";
			if(ach_id == "AchChest") strprogress = strprogress + sti(pchar.questTemp.chestcount) + " / 10";
			if(ach_id == "craft") strprogress = strprogress + sti(pchar.questTemp.craftcount) + " / 300";
			if(ach_id == "books") strprogress = strprogress + sti(pchar.questTemp.bookcount) + " / 3";
			if(ach_id == "officers") strprogress = strprogress + sti(pchar.questTemp.officercount) + " / 3";
			if(ach_id == "ships") strprogress = strprogress + sti(GetCompanionQuantity(pchar)) + " / " + (COMPANION_MAX);
			if(ach_id == "heal_bottles") strprogress = strprogress + sti(pchar.questTemp.healcount) + " / 50";
			if(ach_id == "AchFood") strprogress = strprogress + sti(pchar.questTemp.foodcount) + " / 100";
			if(ach_id == "gen_quests") strprogress = strprogress + sti(pchar.questTemp.genquestcount) + " / 10";
			if(ach_id == "AchBuildColony") strprogress = strprogress + sti(pchar.questTemp.colonystate) + " / 3";
			if(ach_id == "AchTurnir") strprogress = strprogress + sti(pchar.questTemp.tournamentcount) + " / 1";
			if(ach_id == "AchDuelyant") strprogress = strprogress + sti(pchar.questTemp.duelcount) + " / 5";
			if(ach_id == "AchShipOrder") strprogress = strprogress + sti(pchar.questTemp.shipordercount) + " / 5";
			if(ach_id == "AchGoldFleet") strprogress = strprogress + sti(pchar.questTemp.GoldFleetNum) + " / 1";
			if(ach_id == "AchSityRobbery") strprogress = strprogress + (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
			 Statistic_AddValue(PChar, "hol_GrabbingTown", 0)) + " / 5";
			GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = strprogress;
		}
		
		GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = strprogress;
		
		if(ach_id == "Nation_quest_E" || ach_id == "Nation_quest_F" || ach_id == "Nation_quest_H" || ach_id == "Nation_quest_S" || ach_id == "Nation_quest_P" || ach_id == "Isabella_quest" || ach_id == "LSC_quest" || ach_id == "Teno_quest" || ach_id == "Killbeggars_quest" 
		|| ach_id == "Ghostship_quest" || ach_id == "Bluebird_quest" || ach_id == "Berglarsgang_quest" || ach_id == "Mummydust_quest" || ach_id == "Enchantcity_quest" || ach_id == "CapBladLine" || ach_id == "WhisperLine")
		{
			GameInterface.TABLE_ACHIEVEMENTS.(row).td4.str = "Не завершено...";
		}
	}
}

void HideAchievements() // Скрываем окно достижений
{
	SetNodeUsing("Achievements_STR",false);
	SetNodeUsing("TABLE_ACHIEVEMENTS",false);
	SetNodeUsing("SCROLL_ACHIEVEMENTS",false);
	SetNodeUsing("POINTS_EXCHANGE",false);
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

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	ref	refBaseShip;
	string sShip;

	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
			sGroup = "GOODS";
			sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
			iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
			sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem+1]);
			CreateTooltip("#" + sHeader, sText1, argb(255,255,0,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
		break;
		case "SHIP_TABLE_LIST_LEFT":
			makeref(refBaseShip,ShipsTypes[Last_Left_Ship]);
			sShip = refBaseShip.Name;
			sPicture = "interfaces\ships\" + sShip + ".tga.tx";
			SetNewPicture("SHIP_PICTURE_L", sPicture);
		break;
		case "SHIP_TABLE_LIST_RIGHT":
			makeref(refBaseShip,ShipsTypes[Last_Right_Ship]);
			sShip = refBaseShip.Name;
			sPicture = "interfaces\ships\" + sShip + ".tga.tx";
			SetNewPicture("SHIP_PICTURE_R", sPicture);
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
	// Достижения!
	if( sNodName == "TABBTN_Achievements" )
	{
		SetControlsTabMode( 8 );
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
	int nColor8 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;
	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;

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
		case 8:
			sPic8 = "TabDeSelected";
			nColor8 = argb(255,255,255,255);
		break;
	}
	SetNewGroupPicture("TABBTN_QUEST", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_QUESTARJ", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_INFO", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_CASHBOOK", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_STATISTIC", "TABS", sPic5);
	SetNewGroupPicture("TABBTN_SHIP_PLACE", "TABS", sPic6);
	SetNewGroupPicture("TABBTN_STOREBOOK", "TABS", sPic7);
	SetNewGroupPicture("TABBTN_Achievements", "TABS", sPic8);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUEST", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUESTARJ", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_INFO", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_CASHBOOK", 8,0,nColor4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STATISTIC", 8,0,nColor5);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SHIP_PLACE", 8,0,nColor6);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STOREBOOK", 8,0,nColor7);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_Achievements", 8,0,nColor8);

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
		case 8: selectAchievements(); break; // Достижения
	}
}
void InitTableHeader()
{
	int	i;
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
	GameInterface.TABLE_NATION.hr.td2.icon.image	  = Nations[0].Name;
	GameInterface.TABLE_NATION.hr.td2.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td2.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td2.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td3.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td3.icon.image	  = Nations[1].Name;
	GameInterface.TABLE_NATION.hr.td3.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td3.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td3.icon.offset = "7, 2";
	//GameInterface.TABLE_NATION.hr.td3.str = "Англия";
	//GameInterface.TABLE_NATION.hr.td3.scale = 0.9;
 	GameInterface.TABLE_NATION.hr.td4.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td4.icon.image	  = Nations[2].Name;
	GameInterface.TABLE_NATION.hr.td4.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td4.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td4.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td5.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td5.icon.image	  = Nations[3].Name;
	GameInterface.TABLE_NATION.hr.td5.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td5.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td5.icon.offset = "7, 2";
 	GameInterface.TABLE_NATION.hr.td6.icon.group = "NATIONS"
	GameInterface.TABLE_NATION.hr.td6.icon.image	  = Nations[4].Name;
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
	int	 i, cn, n;
	string  row;
	ref	 rCity, chref;

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
					GameInterface.(_tabName).(row).index = chrefsp.id;
					GameInterface.(_tabName).(row).td1.icon.texture = "interfaces\ships\" + shipTexture + ".tga.tx";
					GameInterface.(_tabName).(row).td1.icon.uv = "0,0,1,1";
					GameInterface.(_tabName).(row).td1.icon.offset = "-2, 0";
					GameInterface.(_tabName).(row).td1.icon.width  = 40;
					GameInterface.(_tabName).(row).td1.icon.height = 40;
					GameInterface.(_tabName).(row).td2.str = refBaseShip.Class;
					GameInterface.(_tabName).(row).td2.scale = 0.8;
					GameInterface.(_tabName).(row).td3.str = XI_ConvertString(RealShips[sti(chrefsp.Ship.Type)].BaseName) + " '" + chrefsp.Ship.Name + "'";
					GameInterface.(_tabName).(row).td3.scale = 0.8;
					GameInterface.(_tabName).(row).td4.icon.texture = "INTERFACES\PORTRAITS\128\face_" + chrefsp.faceId + ".tga";
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
	int	 i, cn, n, StoreNum;
	ref	 chref;
	string  row, firstId, CityId;
	aref	curItem;
	ref	 rCity;
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
	if(CurTable == "SHIP_TABLE_LIST_LEFT") {Last_Left_Ship = sti(GameInterface.(CurTable).(CurRow).index); SetShipOTHERTableInfo("SHIP_TABLE_OTHER_LEFT");}//запоминаем новый выбранный корабль и обновляем таблицу
	if(CurTable == "SHIP_TABLE_LIST_RIGHT") {Last_Right_Ship = sti(GameInterface.(CurTable).(CurRow).index); SetShipOTHERTableInfo("SHIP_TABLE_OTHER_RIGHT");}
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
	int	 i, n;
	ref	 nulChr;
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
void FillShipInfoEncy(string _tabName)
{
	Table_Clear(_tabName, false, true, false);
	string sRow;

	GameInterface.(_tabName).hr.td1.str = "Фото";
	GameInterface.(_tabName).hr.td1.scale = 0.8;
	GameInterface.(_tabName).hr.td2.str = "Тип Корабля";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Класс";
	GameInterface.(_tabName).hr.td3.scale = 0.8;
	GameInterface.(_tabName).hr.td4.str = "Специф.";
	GameInterface.(_tabName).hr.td4.scale = 0.8;

	aref   arDest, arImt;
	string sAttr;
	int	iNum, iShip;
	ref	refBaseShip;
	string sShip;
	int k = 0;
	ref chrefsp;
	makeref(chrefsp, Characters[GenerateCharacter(4,WITHOUT_SHIP,"pirate",MAN,1,WARRIOR)]);
	for (int i = 0; i < SHIP_TYPES_QUANTITY - 1;i++)
	{
	string spectypes = "";
	sRow = "tr" + (k+1);
	makeref(refBaseShip,ShipsTypes[i]);
	sShip = refBaseShip.Name;
	chrefsp.Ship.Type = sShip;
	if (!CheckAttribute(Pchar,"Encyclopedia."+sShip) && bFillEncyShips) continue;											 

	int nClass = sti(refBaseShip.Class);
	string snation;
	if (_tabName == "SHIP_TABLE_LIST_LEFT" && FState_SHIP_L != 8 && FState_SHIP_L != nClass) continue;
	if (_tabName == "SHIP_TABLE_LIST_RIGHT" && FState_SHIP_R != 8 && FState_SHIP_R != nClass) continue;
	if (_tabName == "SHIP_TABLE_LIST_RIGHT" && FState_SHIP_N_R && !checkattribute(refBaseShip, "QuestShip")) //квестовые игнорируют выбор нации, всё равно показываются
		{snation = ShipNation[FState_SHIP_N_R-1]; if (refBaseShip.nation.(snation)) {} else continue;}
	if (_tabName == "SHIP_TABLE_LIST_LEFT" && FState_SHIP_N_L && !checkattribute(refBaseShip, "QuestShip"))
		{snation = ShipNation[FState_SHIP_N_L-1]; if (refBaseShip.nation.(snation)) {} else continue;}

	//GameInterface.(_tabName).(sRow).index = chrefsp.id;
	GameInterface.(_tabName).(sRow).index = i;
	GameInterface.(_tabName).(sRow).td1.icon.texture = "interfaces\ships\" + sShip + ".tga.tx";
	GameInterface.(_tabName).(sRow).td1.icon.uv = "0,0,1,1";
	GameInterface.(_tabName).(sRow).td1.icon.offset = "-2, 0";
	GameInterface.(_tabName).(sRow).td1.icon.width  = 60;
	GameInterface.(_tabName).(sRow).td1.icon.height = 60;
	GameInterface.(_tabName).(sRow).td2.str = refBaseShip.Class;
	GameInterface.(_tabName).(sRow).td2.str = XI_Convertstring(sShip);
	GameInterface.(_tabName).(sRow).td2.scale = 0.8;
	GameInterface.(_tabName).(sRow).td3.str = sti(refBaseShip.Class);
	
	if (refBaseShip.Type.War == true) spectypes = "Военный";
	if (refBaseShip.Type.Merchant == true) spectypes = "Торговый";
	if (refBaseShip.Type.Merchant == true && refBaseShip.Type.War == true) spectypes = "Универс.";
	GameInterface.(_tabName).(sRow).td4.str = spectypes;
	GameInterface.(_tabName).(sRow).td4.scale = 0.8;
	
	k++;
	if(!CheckAttribute(refBaseShip,"QuestShip") && bFillEncyShips) pchar.questTemp.shipsearchcount = k;
	}
	ShowInfoWindowEncyShip();
	if(bFillEncyShips && pchar.questTemp.shipsearchcount == "124") UnlockAchievement("AchShipSearch",3);
	int iselected = FindLastShip(_tabName);//если отфильтровался, то вернётся -1
	GameInterface.(_tabName).select = iselected+1;
	if (iselected < 2) GameInterface.(_tabName).top = 0; else GameInterface.(_tabName).top = iselected-2;
	if (_tabName == "SHIP_TABLE_LIST_LEFT") SetShipOTHERTableInfo("SHIP_TABLE_OTHER_LEFT"); else SetShipOTHERTableInfo("SHIP_TABLE_OTHER_RIGHT");

	Table_UpdateWindow(_tabName);
}

int FindLastShip(string _tabName)
{
	int q;
	string sRow; 
	if (_tabName == "SHIP_TABLE_LIST_LEFT")
	{
		for (q = 0; q<(SHIP_TYPES_QUANTITY+1);q++)
		{
		sRow = "tr" + (q+1);

		if (!CheckAttribute(GameInterface, "SHIP_TABLE_LIST_LEFT." + sRow + ".index")) {Last_Left_Ship = -1; return -1;}//таблица кончилась, корабль не нашли, сбрасываем выделение
		if (GameInterface.(_tabName).(sRow).index == Last_Left_Ship) return q;//корабль не отфильтровался, он в строчке q+1
		}
		Last_Left_Ship = -1;
	}
	else
	{
		for (q = 0; q<(SHIP_TYPES_QUANTITY+1);q++)
		{
		sRow = "tr" + (q+1);
		if (!CheckAttribute(GameInterface, "SHIP_TABLE_LIST_RIGHT." + sRow + ".index")) {Last_Right_Ship = -1; return -1;}
		if (GameInterface.(_tabName).(sRow).index == Last_Right_Ship) return q;
		}
		Last_Right_Ship = -1;
	}
	return -1;
}

void SetShipOTHERTableInfo(string _tabName)
{
	int iShip;
	if (_tabName == "SHIP_TABLE_OTHER_LEFT") iShip = Last_Left_Ship; else iShip = Last_Right_Ship;
	Table_Clear(_tabName, false, true, false);
	
	if (iShip > -1)
	{
		int	 i;
		string  row;
		string sShip;
		ref refBaseShip;
		makeref(refBaseShip,ShipsTypes[iShip]);
		sShip = refBaseShip.Name;
	
		GameInterface.(_tabName).select = 0;
		string std1, std2, std3, std4, sleft, sright;
		std1 = "td1"; std2 = "td2"; std3 = "td3"; std4 = "td4"; sleft = "left"; sright = "right";
		if (_tabName == "SHIP_TABLE_OTHER_RIGHT")
		{std1 = "td4"; std2 = "td3"; std3 = "td2"; std4 = "td1"; sleft = "right"; sright = "left";}
	
		GameInterface.(_tabName).hr.(std1).str = "";
		for (i=1; i<=10; i++)
		{
			row = "tr" + i;
	
			GameInterface.(_tabName).(row).(std1).icon.width = 24;
			GameInterface.(_tabName).(row).(std1).icon.height = 24;
			GameInterface.(_tabName).(row).(std1).icon.offset = "2, 1";
			GameInterface.(_tabName).(row).(std2).align = sleft;
			GameInterface.(_tabName).(row).(std2).scale = 0.8;
			GameInterface.(_tabName).(row).(std2).textoffset = "0,0";
			GameInterface.(_tabName).(row).(std3).align = sright;
			GameInterface.(_tabName).(row).(std3).scale = 0.8;
		}
		GameInterface.(_tabName).tr1.UserData.ID = "Hull";
		GameInterface.(_tabName).tr1.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr1.(std1).icon.image = "Hull";
		GameInterface.(_tabName).tr1.(std2).str = XI_ConvertString("Hull");
		GameInterface.(_tabName).tr1.(std3).str = sti(refBaseShip.hp);
	
		GameInterface.(_tabName).tr2.UserData.ID = "Sails";
		GameInterface.(_tabName).tr2.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr2.(std1).icon.image = "Sails";
		GameInterface.(_tabName).tr2.(std2).str = XI_ConvertString("Sails");
		GameInterface.(_tabName).tr2.(std3).str = sti(refBaseShip.sp);
	
		GameInterface.(_tabName).tr3.UserData.ID = "MastHP";
		GameInterface.(_tabName).tr3.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr3.(std1).icon.image = "MastHP";
		GameInterface.(_tabName).tr3.(std2).str = XI_ConvertString("MastHP");
		GameInterface.(_tabName).tr3.(std3).str = FloatToString(stf(refBaseShip.MastMultiplier),2);
	
		GameInterface.(_tabName).tr4.UserData.ID = "Speed";
		GameInterface.(_tabName).tr4.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr4.(std1).icon.image = "Speed";
		GameInterface.(_tabName).tr4.(std2).str = XI_ConvertString("Speed");
	
		GameInterface.(_tabName).tr4.(std3).str = FloatToString(stf(refBaseShip.SpeedRate),2);
	
	
		GameInterface.(_tabName).tr5.UserData.ID = "Maneuver";
		GameInterface.(_tabName).tr5.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr5.(std1).icon.image = "Maneuver";
		GameInterface.(_tabName).tr5.(std2).str = XI_ConvertString("Maneuver");
	
		GameInterface.(_tabName).tr5.(std3).str = FloatToString(stf(refBaseShip.TurnRate),2);
	
	
		GameInterface.(_tabName).tr6.UserData.ID = "AgainstWind";
		GameInterface.(_tabName).tr6.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr6.(std1).icon.image = "AgainstWind";
		GameInterface.(_tabName).tr6.(std2).str = XI_ConvertString("AgainstWind");
		GameInterface.(_tabName).tr6.(std3).str = FloatToString(stf(refBaseShip.WindAgainstSpeed),2);
	
	
		GameInterface.(_tabName).tr7.UserData.ID = "Capacity";
		GameInterface.(_tabName).tr7.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr7.(std1).icon.image = "Capacity";
		GameInterface.(_tabName).tr7.(std2).str = XI_ConvertString("Capacity");
		GameInterface.(_tabName).tr7.(std3).str = refBaseShip.Capacity;
	
		GameInterface.(_tabName).tr8.UserData.ID = "Crew";
		GameInterface.(_tabName).tr8.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr8.(std1).icon.image = "Crew";
		GameInterface.(_tabName).tr8.(std2).str = XI_ConvertString("Crew");
		GameInterface.(_tabName).tr8.(std3).str = sti(refBaseShip.MinCrew) +"/" + sti(refBaseShip.OptCrew);
	
		GameInterface.(_tabName).tr9.UserData.ID = "sCannons";
		GameInterface.(_tabName).tr9.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr9.(std1).icon.image = "Caliber";
		GameInterface.(_tabName).tr9.(std2).str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
		GameInterface.(_tabName).tr9.(std3).str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber)
	
	
		GameInterface.(_tabName).tr10.UserData.ID = "CannonType";
		GameInterface.(_tabName).tr10.(std1).icon.group = "ICONS_CHAR";
		GameInterface.(_tabName).tr10.(std1).icon.image = "Cannons";
		GameInterface.(_tabName).tr10.(std2).str = XI_ConvertString("Cannon" + "s2");
	
		if (refBaseShip.CannonsQuantity == 0)
		{
			GameInterface.(_tabName).tr10.(std3).str = "Нет пушек";
			GameInterface.(_tabName).tr10.(std3).align = sright;
			GameInterface.(_tabName).tr10.(std3).scale = 0.8;
		}
		else
		{
			GameInterface.(_tabName).tr10.(std3).str =  refBaseShip.CannonsQuantity;
			GameInterface.(_tabName).tr10.(std3).align = sright;
			GameInterface.(_tabName).tr10.(std3).scale = 0.8;
		}
	}
//-->показываем флаги, для обеих сторон, так как при фильтрации обе стороны скрываются
	if (Last_Left_Ship>-1)
	{
		ref refBaseShipL, refBaseShipR;
		makeref(refBaseShipL,ShipsTypes[Last_Left_Ship]);
		bool bQuest = false;
		if (checkattribute(refBaseShipL, "QuestShip")) bQuest = true; //не показываем флаги наций квестовым
		if (!bQuest && refBaseShipL.nation.england == true) SetNewPicture("S_NATION_E_L", "loading\Enc_Eng.tga"); else SetNewPicture("S_NATION_E_L", "");
		if (!bQuest && refBaseShipL.nation.france == true) SetNewPicture("S_NATION_F_L", "loading\Enc_Fra.tga"); else SetNewPicture("S_NATION_F_L", "");
		if (!bQuest && refBaseShipL.nation.holland == true) SetNewPicture("S_NATION_H_L", "loading\Enc_Hol.tga"); else SetNewPicture("S_NATION_H_L", "");
		if (!bQuest && refBaseShipL.nation.spain == true) SetNewPicture("S_NATION_S_L", "loading\Enc_Spa.tga"); else SetNewPicture("S_NATION_S_L", "");
		if (!bQuest && refBaseShipL.nation.pirate == true) SetNewPicture("S_NATION_P_L", "loading\Enc_Pir.tga"); else SetNewPicture("S_NATION_P_L", "");
	}
	if (Last_Right_Ship>-1)
	{
		makeref(refBaseShipR,ShipsTypes[Last_Right_Ship]);
		bQuest = false;
		if (checkattribute(refBaseShipR, "QuestShip")) bQuest = true; //не показываем флаги наций квестовым
		if (!bQuest && refBaseShipR.nation.england == true) SetNewPicture("S_NATION_E_R", "loading\Enc_Eng.tga"); else SetNewPicture("S_NATION_E_R", "");
		if (!bQuest && refBaseShipR.nation.france == true) SetNewPicture("S_NATION_F_R", "loading\Enc_Fra.tga"); else SetNewPicture("S_NATION_F_R", "");
		if (!bQuest && refBaseShipR.nation.holland == true) SetNewPicture("S_NATION_H_R", "loading\Enc_Hol.tga"); else SetNewPicture("S_NATION_H_R", "");
		if (!bQuest && refBaseShipR.nation.spain == true) SetNewPicture("S_NATION_S_R", "loading\Enc_Spa.tga"); else SetNewPicture("S_NATION_S_R", "");
		if (!bQuest && refBaseShipR.nation.pirate == true) SetNewPicture("S_NATION_P_R", "loading\Enc_Pir.tga"); else SetNewPicture("S_NATION_P_R", "");
	}
//<--показываем флаги
	if (_tabName == "SHIP_TABLE_OTHER_LEFT") SetFormatedText("SHIP_INFO_TEXT_LEFT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	if (_tabName == "SHIP_TABLE_OTHER_RIGHT") SetFormatedText("SHIP_INFO_TEXT_RIGHT", GetConvertStr(sShip, "ShipsDescribe.txt"));

	Table_UpdateWindow(_tabName);
}

void GiveItemToTraderByType(aref ch, string type)
{
	int i, irand;
	String itemID;
	ref itm;

	DeleteAttribute(ch, "items");
	for(i = 0; i < ITEMS_QUANTITY; i++)
	{
		itemID = Items[i].ID;
		irand = 1;
		itm = ItemsFromID(itemID);
		switch (type)
		{
			case "blade":
				if (CheckAttribute(itm,"groupID")){
					if (itm.groupID == BLADE_ITEM_TYPE) AddItems(ch, itemID, irand);
				}
			break;
			case "gun":
				if (CheckAttribute(itm,"groupID")){
					if (itm.groupID == GUN_ITEM_TYPE || itm.groupID == AMMO_ITEM_TYPE)
					{
						irand = 2;
						AddItems(ch, itemID, irand);
					}
				}
			break;
			case "food":
				if (CheckAttribute(itm,"ItemType") && !CheckAttribute(itm,"groupID")){
					if (itm.ItemType == "Support") AddItems(ch, itemID, irand);
				}
			break;
			case "bonusitem":
				if (HasSubStr(itm.id,"backpack") || HasSubStr(itm.id,"talisman") || HasSubStr(itm.id,"cirass") || HasSubStr(itm.id,"jewelry") || HasSubStr(itm.id,"indian") || HasSubStr(itm.id,"Totem") || HasSubStr(itm.id,"mineral")) AddItems(ch, itemID, irand);
			break;
		}
	}
}

void AddToTable(string _tabName, string type)
{
	int n, i;
	string row, sShipGroup;
	string sGood;
	int  idLngFile;
	int leftQty, rightQty;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear(_tabName, false, true, false);
	GameInterface.(_tabName).top = 0;
	GameInterface.(_tabName).select = 0;
	makeref(chrefsp, Characters[GenerateCharacter(4,WITHOUT_SHIP,"pirate",MAN,1,WARRIOR)]);
	GiveItemToTraderByType(chrefsp, type);
	switch (type)
	{
		case "blade":
			ShowInfoWindowEncyBlade();
			GameInterface.(_tabName).hr.td1.str = "Наименование предметов";
			GameInterface.(_tabName).hr.td1.scale = 1.1;
			GameInterface.(_tabName).hr.td2.str = "Урон мин/макс";
			GameInterface.(_tabName).hr.td2.scale = 1.1;
			GameInterface.(_tabName).hr.td3.str = "Класс оружия";
			GameInterface.(_tabName).hr.td3.scale = 1.1;
			GameInterface.(_tabName).hr.td4.str = "Вес";
			GameInterface.(_tabName).hr.td4.scale = 1.1;
			GameInterface.(_tabName).hr.td5.str = "Доп. свойства";
			GameInterface.(_tabName).hr.td5.scale = 1.1;
		break;
		case "gun": ShowInfoWindowEncyGun();
			GameInterface.(_tabName).hr.td1.str = "Наименование предметов";
			GameInterface.(_tabName).hr.td1.scale = 1.1;
			GameInterface.(_tabName).hr.td2.str = "Урон мин/макс";
			GameInterface.(_tabName).hr.td2.scale = 1.1;
			GameInterface.(_tabName).hr.td3.str = "Патроны, требования";
			GameInterface.(_tabName).hr.td3.scale = 1.1;
			GameInterface.(_tabName).hr.td4.str = "Точность";
			GameInterface.(_tabName).hr.td4.scale = 1.1;
			GameInterface.(_tabName).hr.td5.str = "Перезарядка";
			GameInterface.(_tabName).hr.td5.scale = 1.1;
		break;
		case "food": ShowInfoWindowEncyFood();
			GameInterface.(_tabName).hr.td1.str = "Наименование предметов";
			GameInterface.(_tabName).hr.td1.scale = 1.1;
			GameInterface.(_tabName).hr.td2.str = "Здоровья/Энергия";
			GameInterface.(_tabName).hr.td2.scale = 1.1;
			GameInterface.(_tabName).hr.td3.str = "Антидот";
			GameInterface.(_tabName).hr.td3.scale = 1.1;
			GameInterface.(_tabName).hr.td4.str = "Вес";
			GameInterface.(_tabName).hr.td4.scale = 1.1;
		break;
		case "bonusitem": ShowInfoWindowEncyBonusItem();
			GameInterface.(_tabName).hr.td1.str = "Наименование предметов";
			GameInterface.(_tabName).hr.td1.scale = 1.1;
			GameInterface.(_tabName).hr.td2.str = "Описание";
			GameInterface.(_tabName).hr.td2.scale = 1.1;
		break;
	}

	for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		row = "tr" + n;
		sGood = Items[i].id;
		// проверка на экипировку, их не продаем
		leftQty  = GetCharacterFreeItem(chrefsp, sGood);

		if (leftQty > 0)
		{
			if (type == "blade" && FState_BLADE && Items[i].FencingType != BladeType[FState_BLADE-1]) continue;//фильтрация типа легкое тяжелое

			if (type == "blade" && !checkattribute(&Items[i],"quality")) continue;//отфильтровываю "безоружный" и всякие посторонние предметы, у которых нет "качества"
			if (type == "blade" && FState_BLADEQ && Items[i].quality != BladeTypeQ[FState_BLADEQ-1]) continue;//фильтрация клинков по качеству

			if (type == "gun" && FState_GunQ) {if (Items[i].groupID == AMMO_ITEM_TYPE || !checkattribute(&Items[i],"quality")) continue;}
			if (type == "gun" && FState_GunQ && Items[i].quality != GunTypeQ[FState_GunQ-1]) continue;//фильтрация по качеству

			if (type == "bonusitem" && FState_BONUS && !HasSubStr(sGood, BonusType[FState_BONUS-1])) continue;//фильтрация типа предметов

			GameInterface.(_tabName).(row).td1.icon.group = Items[i].picTexture;
			GameInterface.(_tabName).(row).td1.icon.image = "itm" + Items[i].picIndex;
			GameInterface.(_tabName).(row).td1.icon.offset = "-2, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 60;
			GameInterface.(_tabName).(row).td1.icon.height = 60;
			GameInterface.(_tabName).(row).td1.textoffset = "60,0";
			GameInterface.(_tabName).(row).td1.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.(_tabName).(row).index = i;
			GameInterface.(_tabName).(row).td1.scale = 0.9;
			switch (type)
			{
				case "blade":
				if (CheckAttribute(Items[i],"Generation")) GameInterface.(_tabName).(row).td2.str = makeint(Items[i].Generation.dmg_min.min)+"-"+makeint(Items[i].Generation.dmg_min.max)+" / "+makeint(Items[i].Generation.dmg_max.min)+"-"+makeint(Items[i].Generation.dmg_max.max);
				else GameInterface.(_tabName).(row).td2.str = makeint(Items[i].dmg_min)+"/"+makeint(Items[i].dmg_max);
				GameInterface.(_tabName).(row).td3.str = XI_ConvertString(Items[i].FencingType);
				if (CheckAttribute(Items[i],"Generation")) GameInterface.(_tabName).(row).td4.str = FloatToString(stf(Items[i].Generation.Weight.min), 1)+" - "+FloatToString(stf(Items[i].Generation.Weight.max), 1);
				else GameInterface.(_tabName).(row).td4.str = FloatToString(stf(Items[i].Weight), 1);
				GameInterface.(_tabName).(row).td5.str = GetSpecialStrings(Items[i]);
				break;
				case "gun":
				GameInterface.(_tabName).(row).td2.str = GetGunDamage(Items[i]);
				GameInterface.(_tabName).(row).td3.scale = 0.9;
				GameInterface.(_tabName).(row).td3.str = GetAmmoTypes(Items[i])+"\n"+GetPerkInfo(Items[i]);
				GameInterface.(_tabName).(row).td4.str = GetAccuracy(Items[i]);
				GameInterface.(_tabName).(row).td5.str = GetRecharge(Items[i]);
				break;
				case "food":
				if (CheckAttribute(Items[i],"food.energy"))  GameInterface.(_tabName).(row).td2.str = makeint(Items[i].food.energy) + " EN";
				else GameInterface.(_tabName).(row).td2.str = "-------";
				if (CheckAttribute(Items[i],"potion.health"))  GameInterface.(_tabName).(row).td2.str = makeint(Items[i].potion.health) + " HP";
				if (CheckAttribute(Items[i],"potion.antidote")) GameInterface.(_tabName).(row).td3.str = "Да";
				else GameInterface.(_tabName).(row).td3.str = "-------";
				GameInterface.(_tabName).(row).td4.str = FloatToString(stf(Items[i].Weight), 1);
				break;
				case "bonusitem":
				GameInterface.(_tabName).(row).td1.icon.width = 80;
				GameInterface.(_tabName).(row).td1.icon.height = 80;
				GameInterface.(_tabName).(row).td1.textoffset = "80,0";
				GameInterface.(_tabName).(row).td2.str = GetItemDescribe(FindItem(Items[i].id));
				GameInterface.(_tabName).(row).td2.scale = 0.8;
				break;
			}
			n++;
		}
	}
	LanguageCloseFile(idLngFile);
	Table_UpdateWindow(_tabName);
}

string GetPerkInfo(ref itm)
{
	if (CheckAttribute(itm,"ReqPerk"))
	{
		if (itm.ReqPerk == "Gunman") return "***\nТребуется перк 'Стрелок'.";
		if (itm.ReqPerk == "GunProfessional") return "***\nТребуется перк 'Мушкетёр'.";
	}
	else return "***\nНе требует специальных навыков.";
	return "";
}

string GetSpecialStrings(ref itm)
{
	if (!CheckAttribute(itm,"special")) return "-------";
	string info = "";
	if (CheckAttribute(itm,"special.valueBB"))
	{
		info += "Шанс пробития блока +"+sti(itm.special.valueBB)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueCrB"))
	{
		info += "Шанс критического удара +"+sti(itm.special.valueCrB)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueCB"))
	{
		info += "Шанс пробития кирасы +"+sti(itm.special.valueCB)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueSS"))
	{
		info += "Шанс резкого удара +"+sti(itm.special.valueSS)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueStS"))
	{
		info += "Шанс оглушающего удара +"+sti(itm.special.valueStS)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueT"))
	{
		info += "Шанс травмировать +"+sti(itm.special.valueT)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueB"))
	{
		info += "Шанс кровотечения +"+sti(itm.special.valueB)+"%\n";
	}
	if (CheckAttribute(itm,"special.valueP"))
	{
		info += "Шанс отравления +"+sti(itm.special.valueP)+"%\n";
	}
	return info;
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

void HideInfoWindowEncy()
{
	SetNodeUsing("SHIP_INFO_FADER",false);
	SetNodeUsing("SHIP_INFO_DUST",false);
	SetNodeUsing("SHIP_INFO_FRAME",false);
	SetNodeUsing("SHIP_INFO_FRAME_CAPTION",false);
	SetNodeUsing("SHIP_TABLE_LIST_LEFT",false);
	SetNodeUsing("SHIP_TABLE_LIST_RIGHT",false);
	SetNodeUsing("SHIP_TABLE_SCROLL_LEFT",false);
	SetNodeUsing("SHIP_TABLE_SCROLL_RIGHT",false);
	SetNodeUsing("SHIP_TABLE_OTHER_LEFT",false);
	SetNodeUsing("SHIP_TABLE_OTHER_RIGHT",false);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_LEFT",false);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_RIGHT",false);
	SetNodeUsing("SHIP_INFO_TEXT_LEFT",false);
	SetNodeUsing("SHIP_INFO_TEXT_RIGHT",false);
	SetNodeUsing("SHIP_CLASS_LEFT",false);
	SetNodeUsing("SHIP_NATION_LEFT",false);
	SetNodeUsing("SHIP_CLASS_RIGHT",false);
	SetNodeUsing("SHIP_NATION_RIGHT",false);
	SetNewPicture("S_NATION_E_L", "");
	SetNewPicture("S_NATION_F_L", "");
	SetNewPicture("S_NATION_H_L", "");
	SetNewPicture("S_NATION_S_L", "");
	SetNewPicture("S_NATION_P_L", "");
	SetNewPicture("S_NATION_E_R", "");
	SetNewPicture("S_NATION_F_R", "");
	SetNewPicture("S_NATION_H_R", "");
	SetNewPicture("S_NATION_S_R", "");
	SetNewPicture("S_NATION_P_R", "");
	SetNodeUsing("BLADE_INFO_FADER",false);
	SetNodeUsing("BLADE_INFO_DUST",false);
	SetNodeUsing("BLADE_INFO_FRAME",false);
	SetNodeUsing("BLADE_INFO_FRAME_CAPTION",false);
	SetNodeUsing("BLADE_TABLE_LIST_SCROLL",false);
	SetNodeUsing("BLADE_TABLE_LIST",false);
	SetNodeUsing("BLADE_TYPE_CLASS",false);
	SetNodeUsing("BLADE_TYPE_Quality",false);
	SetNodeUsing("GUN_INFO_FADER",false);
	SetNodeUsing("GUN_INFO_DUST",false);
	SetNodeUsing("GUN_INFO_FRAME",false);
	SetNodeUsing("GUN_INFO_FRAME_CAPTION",false);
	SetNodeUsing("GUN_TABLE_LIST_SCROLL",false);
	SetNodeUsing("GUN_TABLE_LIST",false);
	SetNodeUsing("GUN_TYPE_QUALITY",false);
	SetNodeUsing("FOOD_INFO_FADER",false);
	SetNodeUsing("FOOD_INFO_DUST",false);
	SetNodeUsing("FOOD_INFO_FRAME",false);
	SetNodeUsing("FOOD_INFO_FRAME_CAPTION",false);
	SetNodeUsing("FOOD_TABLE_LIST_SCROLL",false);
	SetNodeUsing("FOOD_TABLE_LIST",false);
	SetNodeUsing("BONUSITEM_INFO_FADER",false);
	SetNodeUsing("BONUSITEM_INFO_DUST",false);
	SetNodeUsing("BONUSITEM_INFO_FRAME",false);
	SetNodeUsing("BONUSITEM_INFO_FRAME_CAPTION",false);
	SetNodeUsing("BONUSITEM_TABLE_LIST_SCROLL",false);
	SetNodeUsing("BONUSITEM_TABLE_LIST",false);
	SetNodeUsing("BONUSITEM_CLASS",false);
	SetNodeUsing("ACHIEVEMENTS_INFO_FADER",false);
	SetNodeUsing("ACHIEVEMENTS_INFO_DUST",false);
	SetNodeUsing("ACHIEVEMENTS_INFO_FRAME",false);
	SetNodeUsing("TABLE_ACHIEVEMENTS",false);
	SetNodeUsing("POINTS_EXCHANGE",false);
	SetNodeUsing("SCROLL_ACHIEVEMENTS",false);
}
void ShowInfoWindowEncyShip()
{
	HideInfoWindowEncy();
	SetNodeUsing("SHIP_INFO_FADER",true);
	SetNodeUsing("SHIP_TABLE_LIST_LEFT",true);
	SetNodeUsing("SHIP_TABLE_LIST_RIGHT",true);
	SetNodeUsing("SHIP_TABLE_SCROLL_LEFT",true);
	SetNodeUsing("SHIP_TABLE_SCROLL_RIGHT",true);
	SetNodeUsing("SHIP_TABLE_OTHER_LEFT",true);
	SetNodeUsing("SHIP_TABLE_OTHER_RIGHT",true);
	SetNodeUsing("SHIP_INFO_DUST",true);
	SetNodeUsing("SHIP_INFO_FRAME",true);
	SetNodeUsing("SHIP_INFO_FRAME_CAPTION",true);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_LEFT",true);
	SetNodeUsing("SHIP_INFO_FRAME_TEXT_RIGHT",true);
	SetNodeUsing("SHIP_INFO_TEXT_LEFT",true);
	SetNodeUsing("SHIP_INFO_TEXT_RIGHT",true);
	SetNodeUsing("SHIP_CLASS_LEFT",true);
	SetNodeUsing("SHIP_NATION_LEFT",true);
	SetNodeUsing("SHIP_CLASS_RIGHT",true);
	SetNodeUsing("SHIP_NATION_RIGHT",true);

	SetFormatedText("SHIP_INFO_FRAME_CAPTION", "Энциклопедия всех кораблей с полной информацией и возможностью сравнения");
}

void ShowInfoWindowEncyBlade()
{
	HideInfoWindowEncy();
	SetNodeUsing("BLADE_INFO_FADER",true);
	SetNodeUsing("BLADE_INFO_DUST",true);
	SetNodeUsing("BLADE_INFO_FRAME",true);
	SetNodeUsing("BLADE_INFO_FRAME_CAPTION",true);
	SetNodeUsing("BLADE_TABLE_LIST_SCROLL",true);
	SetNodeUsing("BLADE_TABLE_LIST",true);
	SetNodeUsing("BLADE_TYPE_CLASS",true);
	SetNodeUsing("BLADE_TYPE_Quality",true);

	SetFormatedText("BLADE_INFO_FRAME_CAPTION", "Энциклопедия всего холодного оружия с фильтрами и с максимальной информацией");
}

void ShowInfoWindowEncyGun()
{
	HideInfoWindowEncy();
	SetNodeUsing("GUN_INFO_FADER",true);
	SetNodeUsing("GUN_INFO_DUST",true);
	SetNodeUsing("GUN_INFO_FRAME",true);
	SetNodeUsing("GUN_INFO_FRAME_CAPTION",true);
	SetNodeUsing("GUN_TABLE_LIST_SCROLL",true);
	SetNodeUsing("GUN_TABLE_LIST",true);
	SetNodeUsing("GUN_TYPE_QUALITY",true);

	SetFormatedText("GUN_INFO_FRAME_CAPTION", "Энциклопедия всего огнестрельного оружия в игре со всей доступной информацией");
}

void ShowInfoWindowEncyFood()
{
	HideInfoWindowEncy();
	SetNodeUsing("FOOD_INFO_FADER",true);
	SetNodeUsing("FOOD_INFO_DUST",true);
	SetNodeUsing("FOOD_INFO_FRAME",true);
	SetNodeUsing("FOOD_INFO_FRAME_CAPTION",true);
	SetNodeUsing("FOOD_TABLE_LIST_SCROLL",true);
	SetNodeUsing("FOOD_TABLE_LIST",true);

	SetFormatedText("FOOD_INFO_FRAME_CAPTION", "Энциклопедия еды и зелий");
}

void ShowInfoWindowEncyBonusItem()
{
	HideInfoWindowEncy();
	SetNodeUsing("BONUSITEM_INFO_FADER",true);
	SetNodeUsing("BONUSITEM_INFO_DUST",true);
	SetNodeUsing("BONUSITEM_INFO_FRAME",true);
	SetNodeUsing("BONUSITEM_INFO_FRAME_CAPTION",true);
	SetNodeUsing("BONUSITEM_TABLE_LIST_SCROLL",true);
	SetNodeUsing("BONUSITEM_TABLE_LIST",true);
	SetNodeUsing("BONUSITEM_CLASS",true);

	SetFormatedText("BONUSITEM_INFO_FRAME_CAPTION", "Энциклопедия бонусных вещей с выводом баффов и дебаффов");
}

void ProcessFilter()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
//========================================//
	if (sControl == "SHIP_CLASS_RIGHT")
	{
	FState_SHIP_R = 9 - iSelectedCB;
	FillShipInfoEncy("SHIP_TABLE_LIST_RIGHT");
	return;
	}
//========================================//
	if (sControl == "SHIP_NATION_RIGHT")
	{
	FState_SHIP_N_R = -1 + iSelectedCB;
	FillShipInfoEncy("SHIP_TABLE_LIST_RIGHT");
	return;
	}
//========================================//
	if (sControl == "SHIP_CLASS_LEFT")
	{
	FState_SHIP_L = 9 - iSelectedCB;
	FillShipInfoEncy("SHIP_TABLE_LIST_LEFT");
	return;
	}
//========================================//
	if (sControl == "SHIP_NATION_LEFT")
	{
	FState_SHIP_N_L = -1 + iSelectedCB;
	FillShipInfoEncy("SHIP_TABLE_LIST_LEFT");
	return;
	}
//========================================//
	if (sControl == "BLADE_TYPE_CLASS")
	{
	FState_BLADE = -1 + iSelectedCB;
	AddToTable("BLADE_TABLE_LIST", "blade");
	return;
	}
//========================================//
	if (sControl == "BLADE_TYPE_Quality")
	{
	FState_BLADEQ = -1 + iSelectedCB;
	AddToTable("BLADE_TABLE_LIST", "blade");
	return;
	}
//========================================//
	if (sControl == "GUN_TYPE_QUALITY")
	{
	FState_GunQ = -1 + iSelectedCB;
	AddToTable("GUN_TABLE_LIST", "gun");
	return;
	}
//========================================//
	if (sControl == "BONUSITEM_CLASS")
	{
	FState_Bonus = -1 + iSelectedCB;
	
	AddToTable("BONUSITEM_TABLE_LIST", "BonusItem");
	return;
	}
//========================================//
}