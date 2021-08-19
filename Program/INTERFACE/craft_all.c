string CraftType; // ��� ������ (Blacksmith, Jewelry ��� Alchemy)
aref craft, draw;

int lngFileID;
int qnt, qntMAX;

void InitInterface_gm(string iniName)
{
	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	CraftType = pchar.questTemp.CraftType;
	DeleteAttribute(pchar,"questTemp.CRAFT_ITEMS."+CraftType);
	makearef(craft,pchar.questTemp.CRAFT_ITEMS.(CraftType));
	bool HasPerk = IsCharacterPerkOn(pchar, "Craft");
	
	for (i = 0; i < ITEMS_QUANTITY; i++) {
		if (CheckAttribute(&Items[i], "PerkReq") && !HasPerk) continue;
		if (CheckAttribute(&Items[i], "CraftedItem")) {
			string recipe = Items[i].id;
			pchar.questTemp.CRAFT_ITEMS.Blacksmith.(recipe).id = recipe;
		}
		if (CheckAttribute(&Items[i], "ResultNum")) {
			string result = Items[i].ResultNum;
			pchar.questTemp.CRAFT_ITEMS.Blacksmith.(recipe).ResultNum = result;
		}
	}
	
	switch(CraftType)
	{
		case "Blacksmith":
			GameInterface.title = "Craft Blacksmith";
		break;
	}
	
	SetTimeScale(0.0);
	LAi_SetActorTypeNoGroup(pchar);
	locCameraSleep(true);

	EngineLayersOffOn(true);
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("TableSelectChange", "SelectTable", 0);

	InterfaceStates.showGameMenuOnExit = true;
	
	SetNodeUsing("ITEMS_LIST",true);
	SetNodeUsing("COMPONENTS_LIST",true);
	SetNodeUsing("SCROLL_ITEMS",true);
	
	SetNodeUsing("INFO_PIC", false);
	
	qnt = 0;
	qntMAX = 0;
	
	FillItemsTab();
	SetComTabHeaders();
	
	SetCraftInfo(0);
}

void SetComTabHeaders()
{
	GameInterface.COMPONENTS_LIST.hr.td1.str = "����������";
	GameInterface.COMPONENTS_LIST.hr.td1.scale = 0.95;
	
	GameInterface.COMPONENTS_LIST.hr.td2.str = "���-��";
	GameInterface.COMPONENTS_LIST.hr.td2.scale = 0.95;
	
	string row;
	
	for(int i=1; i<9; i++)
	{
		row = "tr" + i;
		
		GameInterface.COMPONENTS_LIST.(row).td1.str = "";
		GameInterface.COMPONENTS_LIST.(row).td1.scale = 0.8;
		GameInterface.COMPONENTS_LIST.(row).td2.scale = 0.85;
	}
	
	GameInterface.COMPONENTS_LIST.select = 0;
	Table_UpdateWindow("COMPONENTS_LIST");
}

void FillItemsTab() // ��������� ������� ��������� ��������
{
	aref drawning;
	int num = GetAttributesNum(craft); // ���-�� ��������� �������� �����
	
	string row;
	GameInterface.ITEMS_LIST.hr.td2.str = "��������� �������";
	GameInterface.ITEMS_LIST.hr.td2.scale = 0.9;
	GameInterface.ITEMS_LIST.hr.td3.str = "���-��";
	GameInterface.ITEMS_LIST.hr.td3.scale = 0.9;

	for(int i=0; i<num; i++)
	{
		drawning = GetAttributeN(craft, i);
		row = "tr" + (i + 1);
		
		GameInterface.ITEMS_LIST.(row).td1.icon.group = Items[GetItemIndex(drawning.ID)].picTexture;
		GameInterface.ITEMS_LIST.(row).td1.icon.image = "itm" + Items[GetItemIndex(drawning.ID)].picIndex;
		GameInterface.ITEMS_LIST.(row).td1.icon.offset = "-2, 0";
		GameInterface.ITEMS_LIST.(row).td1.icon.width = 48;
		GameInterface.ITEMS_LIST.(row).td1.icon.height = 48;
		GameInterface.ITEMS_LIST.(row).td2.str = LanguageConvertString(lngFileID, Items[GetItemIndex(drawning.ID)].name);
		GameInterface.ITEMS_LIST.(row).td2.scale = 0.9;
		if (CheckAttribute(Items[GetItemIndex(drawning.ID)],"ResultNum")) GameInterface.ITEMS_LIST.(row).td3.str = Items[GetItemIndex(drawning.ID)].ResultNum;
		else GameInterface.ITEMS_LIST.(row).td3.str = 1;
		GameInterface.ITEMS_LIST.(row).td3.scale = 0.9;
	}
	
	Table_UpdateWindow("ITEMS_LIST");
	
	SetFormatedText("CRAFT_QTY", ""+qnt);
	SetSelectable("CONFIRM_BUTTON", false);
	SetSelectable("QTY_ADD_BUTTON", false);
	SetSelectable("QTY_REMOVE_BUTTON", false);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
    switch(nodName)
	{
		case "QTY_REMOVE_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				qnt = qnt - 1;
				if(qntMAX != 0 && qnt < 1) qnt = 1;
				
				SetFormatedText("CRAFT_QTY", ""+qnt);
			}
		break;
		
		case "QTY_ADD_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				qnt = qnt + 1;
				
				if(qnt > qntMAX) qnt = qntMAX;
				
				SetFormatedText("CRAFT_QTY", ""+qnt);
			}
		break;
		
		case "CONFIRM_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				CreateItem();
			}
		break;
	}
}

void CreateItem()
{
	DumpAttributes(draw);
	if (CheckAttribute(draw,"ResultNum")) TakeNItems(pchar, draw.ID, qnt*sti(draw.ResultNum));
	else TakeNItems(pchar, draw.ID, qnt); // ������ ����������� �������
	
	int qntCom;
	int drIDX = GetItemIndex(draw.ID);
	int ComIDX;
	
	int n;
	
	// �������� ����������
	for(int i = 1; i <= sti(Items[drIDX].ComponentsNum); i++)
	{
		string CI = "Component"+i;
		string CIN = "Component"+i+"Num";
		qntCom = sti(Items[drIDX].(CIN)) * qnt;
		ComIDX = GetItemIndex(Items[drIDX].(CI));
		if (Items[drIDX].(CIN) == "0") continue;
		if(CraftType == "Blacksmith" || CraftType == "Jewelry")
		{
			for(n = 1; n <= qntCom; n++)
			{
				
				TakeNItems(pchar, Items[drIDX].(CI), -1);
			}
		}
		else
		{
			TakeNItems(pchar, Items[drIDX].(CI), -qntCom);
		}
	}
	
	if (CheckAttribute(draw,"ResultNum")) Log_Info("������ ������� '" + LanguageConvertString(lngFileID, Items[drIDX].name) + "' � ���-�� " + qnt*sti(draw.ResultNum) + " ��.");
	else  Log_Info("������ ������� '" + LanguageConvertString(lngFileID, Items[drIDX].name) + "' � ���-�� " + qnt + " ��.");
    PlaySound("Interface\Craft.wav");
	
	int addedEXP;
	float AlchemyModificator = 1.0;
	
	pchar.questTemp.craftcount = sti(pchar.questTemp.craftcount) + qnt;
			
	// ��������� ����������
	if(sti(pchar.questTemp.craftcount) >= 300) UnlockAchievement("craft", 1);
	if(sti(pchar.questTemp.craftcount) >= 500) UnlockAchievement("craft", 2);
	if(sti(pchar.questTemp.craftcount) >= 5000) UnlockAchievement("craft", 3);
	
	ProcessCancelExit();
}

void SelectTable()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    string CurTable = sControl;
    string CurRow   =  "tr" + (iSelected);
	
	int SelectedLine = iSelected - 1;

	// Fill components table
	SetCraftInfo(SelectedLine);
}

void SetCraftInfo(int idx)
{
	draw = GetAttributeN(craft, idx);
	
	string row;
	
	int craftable = GetItemIndex(draw.ID);
	int itmidx;
	
	bool craftOn = true;
	
	ClearComTable();
	
	for(int i = 1; i <= sti(Items[craftable].ComponentsNum); i++)
	{
		row = "tr" + i;
		string CI = "Component"+i;
		string CIN = "Component"+i+"Num";
		itmidx = GetItemIndex(Items[craftable].(CI));

		GameInterface.COMPONENTS_LIST.(row).td1.str = LanguageConvertString(lngFileID, Items[itmidx].name);
		GameInterface.COMPONENTS_LIST.(row).td1.scale = 1.0;
		GameInterface.COMPONENTS_LIST.(row).td2.scale = 1.0;
		GameInterface.COMPONENTS_LIST.(row).td2.str = GetCharacterItem(pchar, Items[craftable].(CI)) + " / " + Items[craftable].(CIN);
		
		if(GetCharacterItem(pchar, Items[craftable].(CI)) < sti(Items[craftable].(CIN)))
		{
			GameInterface.COMPONENTS_LIST.(row).td1.color = argb(255,255,171,171);
			GameInterface.COMPONENTS_LIST.(row).td2.color = argb(255,255,171,171);
			if(craftOn) craftOn = false;
		}
		else
		{
			GameInterface.COMPONENTS_LIST.(row).td1.color = argb(255,196,255,196);
			GameInterface.COMPONENTS_LIST.(row).td2.color = argb(255,196,255,196);
		}
		
		if (Items[craftable].(CIN) == "0" && GetCharacterItem(pchar, Items[craftable].(CI)) == 0)
		{
			GameInterface.COMPONENTS_LIST.(row).td1.color = argb(255,255,171,171);
			GameInterface.COMPONENTS_LIST.(row).td2.color = argb(255,255,171,171);
			if(craftOn) craftOn = false;
			GameInterface.COMPONENTS_LIST.(row).td2.str = "�����������";
		}			
		if (Items[craftable].(CIN) == "0" && GetCharacterItem(pchar, Items[craftable].(CI)) >= 1) GameInterface.COMPONENTS_LIST.(row).td2.str = "� �������";
		
		GameInterface.COMPONENTS_LIST.(row).td1.icon.group = Items[itmidx].picTexture;
		GameInterface.COMPONENTS_LIST.(row).td1.icon.image = "itm" + Items[itmidx].picIndex;
		GameInterface.COMPONENTS_LIST.(row).td1.icon.offset = "-2, 0";
		GameInterface.COMPONENTS_LIST.(row).td1.icon.width = 48;
		GameInterface.COMPONENTS_LIST.(row).td1.icon.height = 48;
		GameInterface.COMPONENTS_LIST.(row).td1.textoffset = "36,0";
	}
	
	Table_UpdateWindow("COMPONENTS_LIST");
	
	SetNewGroupPicture("INFO_PIC", Items[craftable].picTexture, "itm" + Items[craftable].picIndex);
	SetNodeUsing("INFO_PIC", true);
	
	SetFormatedText("INFO_TEXT", GetItemDescribe(FindItem(Items[craftable].id)));
	
	int qntCur;
	
	if(craftOn)
	{
		for(int n = 1; n <= sti(Items[craftable].ComponentsNum); n++)
		{
			CI = "Component"+n;
			CIN = "Component"+n+"Num";
			if (Items[craftable].(CIN) == "0" && GetCharacterItem(pchar, Items[craftable].(CI)) >= 1) continue;
			if(n == 1)
			{
				qntMAX = GetCharacterItem(pchar, Items[craftable].(CI)) / sti(Items[craftable].(CIN));
			}
			else
			{
				qntCur = GetCharacterItem(pchar, Items[craftable].(CI)) / sti(Items[craftable].(CIN));
				
				if(qntMAX > qntCur) qntMAX = qntCur;
			}
		}
		
		qnt = 1;
		SetFormatedText("CRAFT_QTY", ""+qnt);
		SetSelectable("CONFIRM_BUTTON", true);
		SetSelectable("QTY_ADD_BUTTON", true);
		SetSelectable("QTY_REMOVE_BUTTON", true);
	}
	else
	{
		qnt = 0;
		qntMAX = 0;
		
		SetFormatedText("CRAFT_QTY", ""+qnt);
		SetSelectable("CONFIRM_BUTTON", false);
		SetSelectable("QTY_ADD_BUTTON", false);
		SetSelectable("QTY_REMOVE_BUTTON", false);
	}
}

void ClearComTable()
{
	int trnum;
	string trdone;
	
	for (i = 0; i < 8; i++)
	{
		trnum = i+1;
		trdone = "tr" + trnum;
		
		GameInterface.COMPONENTS_LIST.(trdone).td1.icon.width = 1;
		GameInterface.COMPONENTS_LIST.(trdone).td1.icon.height = 1;
		GameInterface.COMPONENTS_LIST.(trdone).td1.str = "";
		GameInterface.COMPONENTS_LIST.(trdone).td2.str = "";
	}
}

void IProcessFrame()
{
	
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{	
	LanguageCloseFile(lngFileID);
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("TableSelectChange", "SelectTable");
	
	LAi_SetPlayerType(pchar);

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);
	DeleteAttribute(pchar, "pause");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) {
		DeleteEntitiesByType("scrshoter");
	}
	
	EndCancelInterface(bClear);
}