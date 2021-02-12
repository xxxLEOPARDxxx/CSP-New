// Warship 06.09.08 ��������� ���������� ������ ������, ������ � ����� � �������
// ������� ����� ���������� - ��� ��������� �������/������� ���������

#define INTERFACETYPE_EXCHANGE_ITEMS		"ExchangeItems"
#define INTERFACETYPE_CHEST					"Chest"
#define INTERFACETYPE_DEADMAN				"Deadman"
#define INTERFACETYPE_BARREL				"Barrel"
#define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE	10

int nCurScrollNum = 0;
int iCharCapacity, iCharQty, iStoreQty, iCurGoodsIdx;
float fCharWeight, fStoreWeight, fWeight;
bool bShowChangeWin = false;
bool DelLogin = false;
int  BuyOrSell = 0;
string sChrId, sFaceID;
ref refCharacter;
bool bBoxUsed = false; // ������-��?
aref refToChar, arChest, arDeadChar;
String sCharactersArroy[INTERFACE_ITEMSBOX_CHAR_ARROYSIZE] = {"", "", "", "", "", "", "", "", "", ""};

int iTableAddAllBtnX = 270;
int iTableAddAllBtnY = 160;
int iTableRemoveAllBtnX = 504;
int iTableRemoveAllBtnY = 160;

int iCurrentTabMode = 3; // ������� ����� ����������

int iLinesCount = 0;

void InitInterface_RS(string iniName, ref itemsRef, string faceID)
{
	sFaceID = faceID;
	String sInterfaceType = sGetInterfaceType();
	if(sInterfaceType == INTERFACETYPE_BARREL)
	{
		StartAboveForm(true);
	}
	else
	{
		StartAboveForm(false); // Warship fix 17.04.09 ������� ��� ��� ����. ���� false - �� �������. ����� ��� ������� �������� - �����
	}	
	String Tab3Caption;
	refCharacter = GetMainCharacter();
	makearef(refToChar, itemsRef);
	
	if(CheckAttribute(itemsRef, "Money"))
	{
		Log_TestInfo("����� - "+itemsRef.money);
	}
	
	LAi_SetActorTypeNoGroup(PChar); // ��� ������ - ���� � ���� ����� ����������, ���� ������� � �������
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // ���� ������ ��� �����
	{
		if(!LAi_boarding_process) 
		{
			QuestCheckTakeBoxes(itemsRef); // ��������
		}
		
		makearef(arChest, itemsRef);
		bBoxUsed = true;
	}
		
	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS || sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if(sInterfaceType == INTERFACETYPE_DEADMAN) // ���� ����� �����
		{
			makearef(arDeadChar, itemsRef);
			Tab3Caption = "�������� �� �����";
		}
		
		iSetCharIDToCharactersArroy(itemsRef); // �� ����� ���, �� � �� ��������
		bBoxUsed = false;
		
		// boal -->
		if(!CheckAttribute(itemsRef, "HoldEquip") && CheckAttribute(itemsRef, "rank"))
		{
			if(sti(itemsRef.rank) < sti(refCharacter.rank)) // ������, ���� ���� ������
			{
				RemoveCharacterEquip(itemsRef, GUN_ITEM_TYPE);
				if(!IsEquipCharacterByItem(itemsRef, "unarmed"))
				{
					RemoveCharacterEquip(itemsRef, BLADE_ITEM_TYPE);
				}
				
				RemoveCharacterEquip(itemsRef, CIRASS_ITEM_TYPE); //����� 081004 boal
				RemoveCharacterEquip(itemsRef, BACKPACK_ITEM_TYPE); //����� 081004 boal
			}
		}
		// boal <--
	}
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_DEADMAN) // �������� ��������� �������� � ����� ���� ���� ������ ��� ����� �����
	{
		ShipSituation_SetQuestSituation(ShipSituation_0);
	}
	
	GameInterface.TABLE_LIST.hr.td1.str = "���-��";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "�����\n���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td3.str = "������������ ���������";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "�����\n���";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td5.str = "���-��";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	
	FillCharactersScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CreateString(true, "CharName", "", FONT_NORMAL, COLOR_MONEY, 405, 108, SCRIPT_ALIGN_CENTER, 1.0);
	
	InterfaceInitButtons(refCharacter);
	
	// ��� ���������� ������ ������ �� �������
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // ������ ���� ������ - � ���� ������� ������ ����
	{
		/* CreateString(true, "VersionInfo", VERSION_NUMBER1 + GetVerNum(), FONT_CAPTION, COLOR_NORMAL, 400, 550, SCRIPT_ALIGN_CENTER, 0.8);
		CreateString(true, "DevTeam", VERSION_NUMBER3, FONT_CAPTION, COLOR_NORMAL, 400, 566, SCRIPT_ALIGN_CENTER, 0.8); */
		
		if(sInterfaceType == INTERFACETYPE_CHEST)	Tab3Caption = "�������� � �������";
		if(sInterfaceType == INTERFACETYPE_BARREL)	Tab3Caption = "�������� � �������";		
	}
	
	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // ��������� ������ � �������
	{
		GameInterface.strings.CharName = GetFullName(refToChar);
		Tab3Caption = "�������� � �������";
	}
	else
	{
		GameInterface.strings.CharName = GetFullName(refCharacter);
	}
	
	SetCharWeight();
	SetDescription();
	
	SetCharacterMoneyToGold(refCharacter); // ��������� ������ �� � ������
	SetCharacterMoneyToGold(itemsRef);
	iSetCharIDToCharactersArroy(refCharacter); // ������� � ������ ��
	
	AddToTable(itemsRef);
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
	FillCharactersImages();

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
	SetEventHandler("eTabControlPress", "procTabChange", 0); // ������� ����� ��������

	if (csmCA(pchar, "CSM.LootCollector.Run"))
		SetFormatedText("STORECAPTION1", "��� ��� ������ �� ������ ������, ���!"));
	else
		SetFormatedText("STORECAPTION1", XI_ConvertString(sGetInterfaceTypeStr("titleExchangeItems", "titleItemsBox", "titleDeadItems","titleBarrel")));

	if (csmCA(pchar, "CSM.LootCollector.Run") && !csmCA(pchar, "CSM.LootCollector.Tutor"))
	{
		string sHeader, sText1, sText2, sText3;

		// 2do: ����� �������� -->
		string sPicture = "none";
		string sGroup = "none";
		string sGroupPicture = "none";
		// <--

		sHeader = "����� ������� ���� ��� ��������";
		sText1 = "����� �� ����� ����������� � ������ ���� ��� ������!\n\n" +
				 "��� ���� �� �������� � � ������ ����� ������� �����.\n" +
				 "� ����������� ������ ������� ������ ������� �������.";
		sText2 = "������ ������� � ������� �������� � ����� ������ ����� ��������� ���\n" +
				 "������� ������� �� ���������: '������', ��� �� '�'\n" +
				 "����� ������������� � ���������� ����.";
		sText3 = "������� ������ ������ ����, ����� ������ ��� ���������";
		
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,255,130), sText3, argb(255,175,255,175), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
	
	CreateString(true, "TabCaption1", "��� ��������", FONT_NORMAL, COLOR_NORMAL, 230, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption2", "�������� �����", FONT_NORMAL, COLOR_NORMAL, 348, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption3", Tab3Caption, FONT_NORMAL, COLOR_NORMAL, 467, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption4", "������ � �����", FONT_NORMAL, COLOR_NORMAL, 587, 525, SCRIPT_ALIGN_CENTER, 0.8);
}

void InterfaceInitButtons(ref _refCharacter)
{
	String sInterfaceType = sGetInterfaceType();
	
	SetNodeUsing("GETALL_BUTTON", false);
	SetNodeUsing("DELBODY_BUTTON", false);
	SetNodeUsing("SKULL_BUTTON", false);
	
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNodeUsing("GETALL_BUTTON", true);
		break;
		
		case INTERFACETYPE_DEADMAN:
			SetNodeUsing("GETALL_BUTTON", true);
			SetNodeUsing("DELBODY_BUTTON", true);
			
			// �������� �� ����������� ������������� ������
			if(CheckCharacterItem(_refCharacter, "SkullAztec") && LAi_IsDead(characters[sti(arDeadChar.index)]) && CheckNPCQuestDate(_refCharacter, "AztecSkull"))
			{
				SetNodeUsing("SKULL_BUTTON", true);
			}
		break;
		
		case INTERFACETYPE_CHEST:
			if (csmCA(pchar, "CSM.LootCollector.Run"))
			{
				SetNodeUsing("GETALL_BUTTON", true);
			}
		break;
		
		case INTERFACETYPE_BARREL:
		
		break;
	}
}

void SetCharacterMoneyToGold(aref rChar) // � ���������� ��������� � �������� ��� � ��������� "gold"
{
	string sInterfaceType = sGetInterfaceType();
	bool bOk = sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL;
	if(bOk && !CheckAttribute(rChar, "ID"))
	{				
		if(!CheckAttribute(rChar, "Items.Gold")) rChar.Items.Gold = 0;
		rChar.items.gold = sti(rChar.items.gold)+sti(GetAttrValue(rChar, "money")); // �� ������� ������� ����� ������, � �� ������		
	}
	else
	{
		rChar.items.gold = sti(GetAttrValue(rChar, "money"));
	}
}

int iSetCharIDToCharactersArroy(ref _rChar)
{
	string sCurArroyID;
	string sCharID = _rChar.id;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID == sCharID) return i;
		
		if(sCurArroyID == "")
		{
			sCharactersArroy[i] = sCharID;
			return i;
		}
	}
	
	// �� ����, �������� �� �������� ���������, ���� define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE 10
	sCharactersArroy[0] = sCharID; // ��������� ����, �� ���������-�� �����
	return 0;
}

void MakeMoneyFromGoldWithowtChest()
{
	string sCurArroyID;
	ref arCurChar;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID != "")
		{
			arCurChar = CharacterFromID(sCurArroyID);
			arCurChar.money = GetCharacterItem(arCurChar, "Gold");
			DeleteAttribute(arCurChar, "items.gold");
		}
	}
}

void MakeMoneyFromGoldWithChest(aref arChest)
{
	arChest.money = GetCharacterItem(arChest, "Gold");
	DeleteAttribute(arChest, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

void MakeMoneyFromGoldWithDeadMan(aref arDeadChar)
{
	arDeadChar.money = GetCharacterItem(arDeadChar, "Gold");
	DeleteAttribute(arDeadChar, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

string sGetInterfaceType()
{
	string sRetStr = INTERFACETYPE_EXCHANGE_ITEMS;
	if(sFaceID == "") // ������
	{
		sRetStr = INTERFACETYPE_CHEST;
	}
	
	if(sFaceID == "Barrel") // �������
	{
		sRetStr = INTERFACETYPE_BARREL;
	}
	
	if(sFaceID == "666") // �������
	{
		sRetStr = INTERFACETYPE_DEADMAN;
	}
	
	return sRetStr;
}

string sGetInterfaceTypeStr(string sExchangeItems, string sChest, string sDeadMan, string sBarrel)
{
	string sType = sGetInterfaceType();
	string sRetStr="";
	
	switch(sType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			sRetStr = sExchangeItems;
		break;
		
		case INTERFACETYPE_CHEST:
			sRetStr = sChest;
		break;
		
		case INTERFACETYPE_BARREL:
			sRetStr = sBarrel;
		break;
		
		case INTERFACETYPE_DEADMAN:
			sRetStr = sDeadMan;
		break;
	}
	
	return sRetStr;
}

void SetCharactersMoneyOnExit() // �������� ������
{
	string sInterfaceType = sGetInterfaceType();
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			MakeMoneyFromGoldWithowtChest();
		break;
		
		case INTERFACETYPE_CHEST:
			MakeMoneyFromGoldWithChest(arChest);
		break;
		
		case INTERFACETYPE_BARREL:
			MakeMoneyFromGoldWithChest(arChest);
		break;		
		
		case INTERFACETYPE_DEADMAN:
			MakeMoneyFromGoldWithDeadMan(arDeadChar);
		break;
	}
}

void ShowItemsWeight()
{
	string sInterfaceType = sGetInterfaceType();
	int iWeight, iMaxWeight;
	CreateString(true, "ToCharacterWeightStr", "", FONT_NORMAL, COLOR_NORMAL, 601, 110, SCRIPT_ALIGN_CENTER, 0.9);
	
	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS)
	{
		GameInterface.strings.ToCharacterWeightStr =  XI_ConvertString("Weight") + ": " + FloatToString(GetItemsWeight(refToChar), 1) + " / " + GetMaxItemsWeight(refToChar);
	}
	else
	{
		GameInterface.strings.ToCharacterWeightStr = "";
	}
	
	CreateString(true, "MyCharacterWeightStr", XI_ConvertString("Weight") + ": " + FloatToString(GetItemsWeight(refCharacter), 1) + " / " + GetMaxItemsWeight(refCharacter), FONT_NORMAL, COLOR_NORMAL, 215, 110, SCRIPT_ALIGN_CENTER, 0.9);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit()
{
	if(bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
	}
}

void IDoExit(int exitCode)
{
	ref arCurChar;
	string sCurArroyID;
	// boal �������� �� �������� 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	// boal 21.01.2004 <--
	SetCharactersMoneyOnExit(); // ��������� ������ "gold" � �������
	RefreshEquippedMaps(GetMainCharacter()); // �������� �����, ���� ������
	ref sld;
	
	if(!bBoxUsed)
	{	
		for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
		{
			sCurArroyID = sCharactersArroy[i];
			if(sCurArroyID != "")
			{
				arCurChar = CharacterFromID(sCurArroyID);
				if(IsMainCharacter(arCurChar)) continue;
				
				if(CheckAttribute(arCurChar, "skill.Fencing")) //boal fix ����� �� ����� ����� ��� ���������
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar,BLADE_ITEM_TYPE));
				}
		
				if(CheckAttribute(arCurChar, "skill.Fencing") &&  GetCharacterSkill(arCurChar, "Fencing") > 0.1)
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, CIRASS_ITEM_TYPE)); // boal 08.10.04 ����� ��������
				}

				if(CheckAttribute(arCurChar, "skill.Pistol") && GetCharacterSkill(arCurChar,"Pistol") > 0.1 )
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, GUN_ITEM_TYPE));
				}
		
				if(CheckAttribute(arCurChar, "RealCompanionIdx")) // 1.2.4 ����� � �����������
				{
					sld = GetCharacter(sti(arCurChar.RealCompanionIdx));
					ChangeAttributesFromCharacter(sld, arCurChar, false); //��� �������� � ������
				}			
			}
		}	
	}
	else
	{
		bMainCharacterInBox = false; // ������� ���� '� �����'
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
	
	DelEventHandler("eTabControlPress", "procTabChange"); // ������� ����� ��������

	interfaceResultCommand = exitCode;
	
	string sInterfaceType = sGetInterfaceType();
	if (sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (DelLogin)
		{
			//Log_Info("������ ���������");
			Dead_DelLoginedCharacter(refToChar);
		}		
	}
	
	EndCancelInterface(true);
	
	LAi_SetPlayerType(PChar); // ���������� ��� ������
	
	// CSM -->
	if (csmCA(pchar, "CSM.LootCollector.Run"))
	{
		csmHideLootCollectorBox(false);

		if (!csmCA(pchar, "CSM.LootCollector.Tutor"))
		{
			pchar.CSM.LootCollector.Tutor = true;
			ClearAllLogStrings();
			Log_Info("������� ������� ������� � �������: ������, ��� �� ������� '�'");
			Log_Info("����� �������� �� ������ � ���������� ����");
			PlaySound("interface\notebook.wav");
		}
	}

	csmDA(pchar, "CSM.LootCollector.Run");
	// CSM <--
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "TABLE_ADD_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				ADD_ALL_BUTTON();
				TransactionOK();
			}
		break;
		
		case "TABLE_REMOVE_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				REMOVE_ALL_BUTTON();
				TransactionOK();
			}
		break;
		
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
		
		case "GETALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onGetAllBtnClick();
			}
		break;
		
		//navy --> ������ ���� ;)
		case "DELBODY_BUTTON":
			if(comName=="downstep" && GetSelectable("SKULL_BUTTON"))
			{
				SetCurrentNode("SKULL_BUTTON");
			}
		
			if(comName=="activate" || comName=="click")
			{
				//������� ������ �� DEV ������... �����, ������ �� ���� �������, ��� � ���-�� ���������.
				/*if (MOD_BETTATESTMODE == "On")
				{
					Dead_DelLoginedCharacter(refToChar);
					CharacterExitFromLocation(&Characters[sti(refToChar.index)]);
				}*/
				//��� ����� ������.. �� ������� :(
				//PostEvent("LAi_event_Character_Dead", 10, "i", &Characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
		//navy <--
		
		case "SKULL_BUTTON":
			if(comName=="upstep")
			{
				SetCurrentNode("DELBODY_BUTTON");
			}
			
			if(comName=="activate" || comName=="click")
			{
				SetNPCQuestDate(refCharacter, "AztecSkull"); //�������� ����
				OfficerReincarnation(&characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
	}
}

void procTabChange()
{
	int comIndex = GetEventData();
	String nodName = GetEventData();
	SetCurrentNode("TABLE_LIST");
	
	// ���� �������� ��������� ������-�� ������������� - �������� �� ������
	switch(nodName)
	{
		case "TABSTR_1":
			SetControlsTabMode(1)
		break;
		
		case "TABSTR_2":
			SetControlsTabMode(2)
		break;
		
		case "TABSTR_3":
			SetControlsTabMode(3)
		break;
		
		case "TABSTR_4":
			SetControlsTabMode(4)
		break;
	}
}

void SetControlsTabMode(int _mode)
{
	String Pic1 = "TabSelected";
	String Pic2 = Pic1;
	String Pic3 = Pic1;
	String Pic4 = Pic1;
	
	switch(_mode)
	{
		case 1:
			Pic1 = "TabDeSelected";
		break;
		
		case 2:
			Pic2 = "TabDeSelected";
		break;
		
		case 3:
			Pic3 = "TabDeSelected";
		break;
		
		case 4:
			Pic4 = "TabDeSelected";
		break;
	}
	
	iCurrentTabMode = _mode;
	
	// �������� ������� � ������
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;
	
	// ��� ���� ������� ���������
	AddToTable(refToChar);
	
	// ������� ������� �������
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
    
	SetNewGroupPicture("TABBTN_1", "TABS", Pic1);
	SetNewGroupPicture("TABBTN_2", "TABS", Pic2);
	SetNewGroupPicture("TABBTN_3", "TABS", Pic3);
	SetNewGroupPicture("TABBTN_4", "TABS", Pic4);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
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
	string sInterfaceType = sGetInterfaceType();
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
	
	string sCharID = "";
	int iCharIDX;

	int m = 0;
	if(sInterfaceType != INTERFACETYPE_EXCHANGE_ITEMS)
	{
		attributeName = "pic" + (m + 1);
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
		m++;
	}
	else // ��� ������ ���������� � ���� ������ �������� - ������ ���
	{
		sCharID = refToChar.ID;
		iCharIDX = GetCharacterIndex(sCharID);
		attributeName = "pic" + (m + 1);
		
		SetCharacterMoneyToGold(refToChar);
		iSetCharIDToCharactersArroy(refToChar); // ������� ��� ��� �������� ������ � ���� �����
		
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = iCharIDX;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(refToChar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + refToChar.FaceID);
		m++;
	}

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);
		
		bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if(IsOfficer(&characters[_curCharIdx]) && PChar.location == Characters[_curCharIdx].location)  // boal // fix - �� � ��� ������ ���� � ����� �������
			{
				if(sCharID == characters[_curCharIdx].ID) continue;
				
				SetCharacterMoneyToGold(GetCharacter(_curCharIdx));
				iSetCharIDToCharactersArroy(GetCharacter(_curCharIdx)); // ������� ��� ��� �������� ������ � ���� �����
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
}

void AddToTable(ref rChar)
{
	string sList, sItem;
	int n, i, iLeftQty, iRightQty, Index, iSelLine;
	ref rItem;
	bool ok;
	bool ok1 = false;
	n = 1;
	int iRightQtyTotal=0;
	
	// Warship fix 31.05.09 - ������� ������� ������� + �������� �������/������ ���
	// ����-���� ���������� ��� ��
	ok = iCurrentTabMode == 2 || iCurrentTabMode == 3; // �������� ����� �� �������� � � ��� � ����� ���������, ��� �� ��������
	if(ok && iLinesCount > 2)
	{
		if(sti(GameInterface.TABLE_LIST.select) + 1 == iLinesCount)
		{
			iLinesCount -= 2;
			GameInterface.TABLE_LIST.select = iLinesCount;
			
			iSelLine = iLinesCount;
			
			if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
			{
				if(sti(GameInterface.TABLE_LIST.top) > 0)
				{
					GameInterface.TABLE_LIST.top = sti(GameInterface.TABLE_LIST.top) - 1;
				}
				
				iSelLine = iLinesCount - sti(GameInterface.TABLE_LIST.top);
			}
			
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 30 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY + 30 * (iSelLine - 1) + 30, 0);
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 30 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30 * (iSelLine - 1) + 30, 0);
			
			sList = "tr" + sti(GameInterface.TABLE_LIST.select);
			iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
			ShowGoodsInfo(iCurGoodsIdx);
		}
		else
		{
			GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) + 1;
			
			ok1 = true; // ��. ���� �������� if(ok1) - ����-������ �������, �� ��-������� �� ����������
		}
	}
	
	iLinesCount = 1;
	
	Table_Clear("TABLE_LIST", false, true, false);
	
	iLeftQty  = GetCharacterFreeItem(refCharacter, "Gold");
	iRightQty = GetCharacterFreeItem(rChar, "Gold");
	if (iRightQty>0) iRightQtyTotal += 1;
	
	// ���� - ������ ���� ������, ����� � ����� ���� ������� ���������
	//if(iLeftQty > 0 || iRightQty > 0)
	//{
		sList = "tr" + n;
		Index = FindItem("Gold");
		rItem = &Items[Index];
		sItem = rItem.id;
		GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
		GameInterface.TABLE_LIST.(sList).td1.scale = 0.8;
		GameInterface.TABLE_LIST.(sList).td2.str = "-";
		GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
		GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_LIST.(sList).td3.icon.offset = "-2, 0";
		GameInterface.TABLE_LIST.(sList).td3.icon.width = 30;
		GameInterface.TABLE_LIST.(sList).td3.icon.height = 30;
		GameInterface.TABLE_LIST.(sList).td3.textoffset = "50, 0";
		GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
		GameInterface.TABLE_LIST.(sList).index = Index;
		GameInterface.TABLE_LIST.(sList).td3.scale = 1.0;
		GameInterface.TABLE_LIST.(sList).td4.str = "-";
		GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
		GameInterface.TABLE_LIST.(sList).td5.scale = 1.0;
		n++;
		
		iLinesCount++;
	//}
	
	// ������� ��������� ������������ �������
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		sList = "tr" + n;
		rItem = &Items[i];
		
		if(!CheckAttribute(rItem, "ID"))
		{
			continue;
		}
		
		sItem = rItem.id;
		
		if(sItem == "Gold") continue; // ������ ����
		
		// �������� �� ����������
		iLeftQty  = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);
		if (iRightQty>0) iRightQtyTotal += 1;
		
		if (iLeftQty > 0 || iRightQty > 0)
		{
			if(iCurrentTabMode == 2 && iLeftQty < 1) continue; // ���������� "� �����"
			if(iCurrentTabMode == 3 && iRightQty < 1) continue; // ���������� "� �������"
			
			if(iCurrentTabMode == 4) // ���������� "������ � �����"
			{
				if(CheckAttribute(&rItem, "groupID"))
				{
					// �������� �� ������
					if(rItem.groupID != BLADE_ITEM_TYPE && rItem.groupID != GUN_ITEM_TYPE)
					{
						continue;
					}
				}
				else
				{
					// �������� �� �����
					if(!HasSubStr(sItem, "potion"))
					{
						continue;
					}
				}
			}
			
			GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
			GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);	
	        GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td3.icon.offset = "-2, 0";
			GameInterface.TABLE_LIST.(sList).td3.icon.width = 30;
			GameInterface.TABLE_LIST.(sList).td3.icon.height = 30;
			GameInterface.TABLE_LIST.(sList).td3.textoffset = "50, 0";
			GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).index = i;
			GameInterface.TABLE_LIST.(sList).td3.scale = 1.0;
			GameInterface.TABLE_LIST.(sList).td4.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
			GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
			n++;
			
			iLinesCount++;
		}
	}
	
	for(i = 0; i < ITEMS_QUANTITY; i++)
	{
		sList = "tr" + n;
		rItem = &Items[i];
		sItem = rItem.id;
		
		if(sItem == "Gold") continue; // ������ ����
		
		// �������� �� ����������
		iLeftQty  = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);
		if (iRightQty>0) iRightQtyTotal += 1;
		
		if (iLeftQty > 0 || iRightQty > 0)
		{
			if(iCurrentTabMode == 2 && iLeftQty < 1) continue; // ���������� "� �����"
			if(iCurrentTabMode == 3 && iRightQty < 1) continue; // ���������� "� �������"
			
			if(iCurrentTabMode == 4) // ���������� "������ � �����"
			{
				if(CheckAttribute(&rItem, "groupID"))
				{
					// �������� �� ������
					if(rItem.groupID != BLADE_ITEM_TYPE && rItem.groupID != GUN_ITEM_TYPE)
					{
						continue;
					}
				}
				else
				{
					// �������� �� �����
					if(!HasSubStr(sItem, "potion"))
					{
						continue;
					}
				}
			}
			
			GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
			GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);	
	        GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td3.icon.offset = "-2, 0";
			GameInterface.TABLE_LIST.(sList).td3.icon.width = 30;
			GameInterface.TABLE_LIST.(sList).td3.icon.height = 30;
			GameInterface.TABLE_LIST.(sList).td3.textoffset = "50, 0";
			GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).index = i;
			GameInterface.TABLE_LIST.(sList).td3.scale = 1.0;
			GameInterface.TABLE_LIST.(sList).td4.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
			GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
			n++;
			
			iLinesCount++;
		}
	}
	
	if(ok1)
	{
		GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) - 1;
		sList = "tr" + sti(GameInterface.TABLE_LIST.select);
		
		// Warship 10.07.09 fix - ����� �� ����, ��� ����������� � ������ ��� ������������ ����������
		if(CheckAttribute(GameInterface, "TABLE_LIST." + sList + ".index"))
		{
		iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
		ShowGoodsInfo(iCurGoodsIdx);
		}
	}
	
	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
	string sInterfaceType = sGetInterfaceType();
	if (sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (iRightQtyTotal == 0)
		{
			DelLogin = true;
			//Log_Info("���������� ��������� � �����: "+iRightQtyTotal);
		}
	}	
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

void ShowHelpHint()
{
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if(!bShowChangeWin) // ������� ������ �� ������ � ������
	{
		sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = "������� ���� ���� ��� Enter �� ������� ������� �������� ����� ������ ���������� "+ newStr() +
			"Shift + ����/����� �� ������� ������� ������������� �������� ����� � ����������������� ����������� �������/������� �� ������������. "+ newStr() +
			"���� �������������� ���������� � ���������� ������������� ��������� ��������, � �������������� (� �������) ������."+ newStr() +
			"������� ����/����� �������� ���������� �� ������, � Shift + ����/����� �� ����������� ���������. ������� Enter �� ����� ����������� ��, � Esc - ������." + newStr() +
			"�������� � ������ ����� � ����� ������ � ������� �������� �����/����, ����� ������������� �������� �������� ��� �������� �������.";
		
		sText3 = "� ������ �� ����� ����������� ������������� ���������� ��������.";
		sText2 = "������� ������ �����: ��������� �����/���� �� ������, Shift + �����, Enter";
		
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
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
	if(bShowChangeWin) // ���� ����, ����� ������ �� �������
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
	String sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
	
	// Warship 26.04.09 fix - ��� ��������� ����� �������� �� �����, ����������� ������������ ������� �����
	int iSelLine = iSelected;
	
	if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
	}
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 30 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY + 30 * (iSelLine - 1) + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 30 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30 * (iSelLine - 1) + 30, 0);
	
	String sList = "tr" + iSelected;
	SetCharWeight();
	SetVariable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sList).index));
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	ShowItemsWeight(); // ���������
}

void SetCharacterName()
{
	string sInterfaceType = sGetInterfaceType();
	
	aref arChar;
	ref rChar;
	
	string sAttr = "pic" + (nCurScrollNum + 1);
	int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
	
	string sFullName = GetFullName(&characters[iCurCharImageIndex]);
	
	GameInterface.strings.CharName = sFullName;
}

void ProcessFrame()
{	
	aref arCurCharFromImage;
	string sInterfaceType = sGetInterfaceType();
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
		
		switch(sInterfaceType)
		{
			case INTERFACETYPE_EXCHANGE_ITEMS:
				makearef(refToChar, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_CHEST:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_BARREL:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_DEADMAN:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
		}

		SetDescription();
		AddToTable(refToChar);
		FillCharactersImages();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		SetCharacterName();
		
		// �������� �� ������ �������
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	}
}

void FillCharactersImages()
{
	string sInterfaceType = sGetInterfaceType();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refCharacter.FaceId + ".tga");
	
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNewPicture("OTHER_PICTURE", "interfaces\portraits\128\face_" + refToChar.FaceId + ".tga");
		break;
		
		case INTERFACETYPE_CHEST:
			SetNewGroupPicture("OTHER_PICTURE", "BOX_IMAGE", "BoxImage");
		break;
		
		case INTERFACETYPE_BARREL:
			SetNewGroupPicture("OTHER_PICTURE", "BARREL_IMAGE", "BarrelImage");
		break;
		
		case INTERFACETYPE_DEADMAN:
			SetNewPicture("OTHER_PICTURE", "interfaces\portraits\128\face_666.tga");
		break;
	}
}

void SetDescription()
{
	SetVariable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);
    fStoreWeight = GetItemsWeight(refToChar);
}

// �������� �� ������ "����� ���"
void onGetAllBtnClick()
{
	int iItemsQty;
	String itemID;
	
	int maxItemsToAdd;
	float weight;
	bool bOk = false;
	
	for(int i=0; i<TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "ID"))
		{
			itemID = Items[i].id;
			iItemsQty = GetCharacterFreeItem(refToChar, itemID);
			if(iItemsQty < 1) continue;
			
			// ���� ��������� -->
			//maxItemsToAdd = GetMaxItemsToTake(refCharacter, itemID)
			float itemWeight = stf(Items[GetItemIndex(itemID)].weight);
			if(itemWeight == 0)
			{
				RemoveItems(refToChar, itemID, iItemsQty);
				AddItems(refCharacter, itemID, iItemsQty);
				continue;
			}
			else
			{
				int maxWeight = GetMaxItemsWeight(refCharacter);
				maxItemsToAdd = makeint((maxWeight-fCharWeight)/itemWeight);
				
				if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
				// <-- ���� ���������
				
				if(iItemsQty < 1) continue;
				

				RemoveItems(refToChar, itemID, iItemsQty);
				AddItems(refCharacter, itemID, iItemsQty);
				
				bOk = true;
					
				weight = iItemsQty * stf(Items[i].weight);
				fCharWeight += weight; // ��� ��������� ��� ������ GetMaxItemsToTake, ����� �������
				fStoreWeight -= weight;
			}
		}
	}
	
	if(bOk) WaitDate("", 0, 0, 0, 0, 1);
	
	// Warship fix 10.06.09 -->
	// ���������� �������� ���� � �.�.
	SetCharWeight();
	SetVariable();
	
	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST.select = 1;
	
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(iCurGoodsIdx);
	
	AddToTable(refToChar); // ������� �������
	// ������ ������� ���������
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	// <-- Warship fix 10.06.09
}

// ������ �� ��������� ��������� "����� ��� �������� ������ ����"
void onTableAddAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refToChar, item);
	
	// ���� ���������
	int maxItemsToAdd = GetMaxItemsToTake(refCharacter, item);
	
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refToChar, item, iItemsQty);
		AddItems(refCharacter, item, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// ���������� �������� ���� � �.�.
		SetCharWeight();
		SetVariable();
		
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
}

// ������ �� ��������� ��������� "������ ��� �������� ������ ����"
void onTableRemoveAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refCharacter, item);
	
	if(IsQuestUsedItem(item) && item != "Gold") return; // ��������� �� ������, ������ ������
	
	// ���� ��������� (� ������� � ����� ����� ������ ������� ������)
	int maxItemsToAdd = GetMaxItemsToTake(refToChar, item);
	
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refCharacter, item, iItemsQty);
		AddItems(refToChar, item, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// ���������� �������� ���� � �.�.
		SetCharWeight();
		SetVariable();
				
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
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

	if(bBettaTestMode)
	{
		describeStr += "id = " + Items[iGoodIndex].id + NewStr();
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
	iStoreQty = GetCharacterFreeItem(refToChar, Items[iGoodIndex].id);
		
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

void TransactionOK()
{
	int nTradeQuantity;
	String list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if(BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if(BuyOrSell == 1) // ��������
	{
		RemoveItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		AddItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
    	WaitDate("",0,0,0, 0, 1);
	}
 	else // ������
	{
		AddItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		RemoveItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		WaitDate("",0,0,0, 0, 1);
	}
	
	AddToTable(refToChar);
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
	float iWeight;
	float fRefCharWeight, fRefCharMaxWeight;
	string sInterfaceType = sGetInterfaceType();
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if(sti(GameInterface.qty_edit.str) == 0)
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
		    
		    if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // ������� � ����� ��������
		    {
				fRefCharWeight = GetItemsWeight(refToChar);
				fRefCharMaxWeight = GetMaxItemsWeight(refToChar);
				iWeight = (fWeight * sti(GameInterface.qty_edit.str));
				if((fRefCharWeight + iWeight) > fRefCharMaxWeight)
				{
					iWeight = fRefCharMaxWeight - fRefCharWeight - 0.01; // ���� ������
					GameInterface.qty_edit.str = makeint(iWeight / fWeight );
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
					GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // ����������
				}
		    }
		    // �������� �� ����� ��������� <--
		    // ��������� �� ������� -->
		    if (IsQuestUsedItem(Items[iCurGoodsIdx].id) && Items[iCurGoodsIdx].id != "Gold")
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    // ��������� �� ������� <--
		    SetFormatedText("QTY_TypeOperation", "������");
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
		    if((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // ���� ������
				
				if(iWeight < 0) iWeight = 0;
				
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // ����������
		    }
		    // �������� �� ����� ��������� <--
			
			SetFormatedText("QTY_TypeOperation", "�������");
		}
	}
	// ���� �������� ����
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
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
	if(!bShowChangeWin)
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
	if(!bShowChangeWin)
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
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if(BuyOrSell == -1)
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
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if(BuyOrSell == 1)
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

// ������� ��� ����� ������� ���������� ��������, � ������
int GetMaxItemsToTake(ref _char, String _item)
{
	float curWeight;
	
	// Warship MEGA FIX 10.07.09
	if(_char == refToChar)
	{
		curWeight = fStoreWeight;
	}
	else
	{
		curWeight = fCharWeight;
	}
	
	int maxWeight = GetMaxItemsWeight(_char);
	
	float itemWeight = stf(Items[GetItemIndex(_item)].weight);
	
	if(itemWeight == 0) // ��� ������ � ������ ����� - ����� ������ ������� �� ����
	{
		return 1000000000;
	}
	
	return MakeInt((maxWeight - curWeight) / itemWeight);
}

void OfficerReincarnation(ref rPassanger);
{
	ref rOff = GetCharacter(NPC_GenerateCharacter("Clon", "none", rPassanger.sex, rPassanger.model.animation, 1, sti(rPassanger.nation), -1, false));
	ChangeAttributesFromCharacter(rOff, rPassanger, true);
	if (CheckAttribute(rPassanger,"PerkValue.HPPlus")) rOff.PerkValue.HPPlus = 0;
	rOff.id = rPassanger.id;
	LAi_SetCurHPMax(rOff);
	RemoveCharacterEquip(rOff, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(rOff, GUN_ITEM_TYPE);
	RemoveCharacterEquip(rOff, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(rOff, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, MAPS_ITEM_TYPE);
	DeleteAttribute(rOff, "items");
	rOff.items = "";
	DeleteAttribute(rOff, "isMusketer.weapon");
	DeleteAttribute(pchar, "items.mushket2x2");
	AddPassenger(pchar, rOff, false);
	Log_Info("���������� " + GetFullName(rOff) + " ������������.");
}