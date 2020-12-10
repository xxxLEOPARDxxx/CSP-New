int g_LocLngFileID = -1;

object objLandInterface;
object objFastReloadTable;
object objTownStateTable;
int g_intRetVal;

bool bDisableFastReload = false;

#define	BLI_UPDATE_PERIOD 400
#event_handler("evntBattleCommandSound","procBattleCommandSound");

bool bLandInterfaceStart = false;

void procBattleCommandSound()
{
	string comName = GetEventData();
	if(comName=="deactivate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="activate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="right" || comName=="left")
	{
		PlaySound("interface\ok.wav");
	}
}

void InitBattleLandInterface()
{
	//if( IsEntity(&objLandInterface) ) {
	//	DeleteClass(&objLandInterface);
	//}
	//if(bLandInterfaceStart) {
	if( IsEntity(&objLandInterface) ) {
		EndBattleLandInterface();
		//DeleteEntity(&objLandInterface);
		//return;
	}
	bLandInterfaceStart = false;
	SetEventHandler(EVENT_LOCATION_LOAD,"StartBattleLandInterface",0);
	SetEventHandler(EVENT_LOCATION_UNLOAD,"EndBattleLandInterface",0);
	LoadLIStates();
}

void BLI_EnableShow()
{
	SetLandInterfaceShow( sti(InterfaceStates.BattleShow.Command) );
}

void BLI_DisableShow()
{
	SetLandInterfaceShow(false);
}

void SetLandInterfaceShow(bool commandosShow)
{
	SendMessage(&objLandInterface,"ll",MSG_BATTLE_LAND_SET_SHOW,commandosShow);
}

void StartBattleLandInterface()
{
	if(bLandInterfaceStart)
	{
		//BLI_SetObjectData();
		return;
	}
	bLandInterfaceStart = true;

	BLI_SetObjectData();
	BLI_SetMessageParameters();
	CreateEntity(&objLandInterface,"battle_land_interface");
	LayerAddObject("execute",&objLandInterface,-1);
	LayerAddObject("realize",&objLandInterface,-1);

	SetEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers",0);
	SetEventHandler(EVENT_DIALOG_START,"BLI_DisableShow",0);
	SetEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow",0);

	if(dialogRun) BLI_DisableShow();
	else BLI_EnableShow();

	SetEventHandler("evntBLI_Update","BLI_UpdateObjectData",0);
	SetEventHandler("BI_CommandEndChecking","BLI_CheckCommand",0);
	SetEventHandler("BI_LaunchCommand","BLI_ExecuteCommand",0);
	SetEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands",0);
	SetEventHandler("evntFindDialogChar","procFindDialogChar",0);
	SetEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation", 0);
	SetEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation", 0);
	SetEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu",0);
	SetEventHandler("Control Activation","LI_ProcessControlPress",0);
	
	Event("evntBLI_Update");
	Event("evntFindDialogChar");
}

void BLI_SetFlags()
{
	int init = 0;
	if (CheckAttribute(&objLandInterface, "DoSetFlags")) init = sti(objLandInterface.DoSetFlags);
	trace("LandInterface DoSetFlags: " + init);
	init++;
	objLandInterface.DoSetFlags = init;
	if (init >= sti(Characters[GetMainCharacterIndex()].numcoastalindocks)) 
	{
		DeleteAttribute(&objLandInterface, "DoSetFlags");
		DelEventHandler("frame", "BLI_SetFlags");
	}
} 
ref BLI_CheckCommand()
{
	string commandName = GetEventData();

	aref uiref;	makearef(uiref,objLandInterface.UserIcons);
	aref ar;
	int nq = GetAttributesNum(uiref);
	int i;

	bool bUsed = false;
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		ar.enable = false;
	}
	g_intRetVal = BI_COMMODE_USER_ICONS;

	switch(commandName)
	{
	case "cancel":
		g_intRetVal = -1;
	break;
	case "BI_FastReload":
		bUsed = SetReloadIcons();
	break;
	case "BI_ItemsUse":
		bUsed = SetUsedPotionIcons();
	break;
	case "BI_UseFood":
		bool bEnableFood = true;
		if(bEnableFood)
		{
			bUsed = SetUsedFoodIcons();
		}
		else
		{
			g_intRetVal = 0;
		}
	break;	   
	case "BI_DialogStart":
		g_intRetVal = 0;
	break;
	case "BI_ItemsChange":
		g_intRetVal = 0;
	break;
	case "BI_TakeItem":
		g_intRetVal = 0;
	break;
	case "BI_PlaceItem":
		g_intRetVal = 0;
	break;
	case "BI_OutDoor":
		g_intRetVal = 0;
	break;
	case "BI_UseBox":
		g_intRetVal = 0;
	break;
	// boal
    case "BI_DeadBox":
		g_intRetVal = 0;
	break;
	case "BI_TalkSelf":
		g_intRetVal = 0;
	break;
	case "BI_ActivateRush":
		g_intRetVal = 0;
	break;
	case "BI_Exit_Deck": //boal
		g_intRetVal = 0;
	break;
	}

	//if(!bUsed)	objLandInterface.UserIcons.cancel.enable = true;
	return &g_intRetVal;
}

void BLI_ExecuteCommand()
{
	int		chrIdx = GetEventData();
	string	commName = GetEventData();
	int		targChrIdx = GetEventData();
	string	evntName = GetEventData();

	aref arFader;
	if( FindClass(arFader,"fader") ) {return;}

	aref	uiref;
	int		curLocIdx;
	int		tmpi;

	if( commName=="cancel" || evntName=="cancel" ) {
		SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	switch(commName)
	{
	case "BI_FastReload":
		{
			curLocIdx = FindLoadedLocation();
			if(curLocIdx==-1) return;
			if( FindUserIcon(evntName,&uiref) )
			{
				string sTravelLocator = "";
				if(CheckAttribute(uiref,"locator")) {sTravelLocator=uiref.locator;}
				if(CheckAttribute(uiref,"location"))
				{
					PlayerFastTravel(curLocIdx, uiref.location, sTravelLocator);
				}
			}
		}
	break;
	case "BI_ItemsUse":
		if( FindUserIcon(evntName,&uiref) )
		{
			if(CheckAttribute(uiref,"potion"))
			{
				aref arItm;
				if( Items_FindItem(uiref.potion,&arItm) >= 0 )
				{
					if( CheckAttribute(arItm,"potion") )
					{
						DoCharacterUsedItem(pchar,arItm.id);
					}
				}
			}
		}
	break;
	case "BI_UseFood":
		if( FindUserIcon(evntName,&uiref) )
		{
			if(CheckAttribute(uiref,"Food"))
			{
				if( Items_FindItem(uiref.Food,&arItm) >= 0 )
				{
					if( CheckAttribute(arItm,"Food") )
					{
						DoCharacterUsedFood(pchar,arItm.id);
					}
				}
			}
		}
	break;
	case "BI_DialogStart":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0)	Event("dlgReady","l",tmpi);
	break;
	case "BI_ItemsChange":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0 && isOfficerInShip(GetCharacter(tmpi), true))//fix ��� ���� �� ������ � ��������
        {
            LaunchCharacterItemChange(GetCharacter(tmpi));
        }
        // boal 22.01.2004 -->
		else
		{
			if (tmpi>=0 && CheckAttribute(GetCharacter(tmpi), "IsCompanionClone")) // 1.2.4
			{
			    LaunchCharacterItemChange(GetCharacter(tmpi));
			}
			else
			{
				// ����� � �������� ������ � ����� (� �������� ��� �������!)
			    tmpi = LAi_FindNearestVisCharacter(GetMainCharacter(), 1);
			    if( tmpi>0 && IsOfficer(GetCharacter(tmpi)) && IsCharacterPerkOn(pchar,"SharedExperience") )
				{
				    LaunchCharacterItemChange(GetCharacter(tmpi));
				}
			}
		}
	break;
	case "BI_TakeItem":
		Item_OnPickItem();
	break;
	case "BI_PlaceItem":
		Item_OnUseItem();
	break;
	case "BI_OutDoor":
		Event("Control Activation","s","ChrAction");
	break;
	case "BI_UseBox":
		OpenBoxProcedure();
	break;
	// boal
	case "BI_DeadBox":
		Dead_OpenBoxProcedure();
	break;
	case "BI_TalkSelf":
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	break;
	case "BI_ActivateRush":
		ActivateCharacterPerk(pchar,"Rush");
	break;
	// boal
    case "BI_Exit_Deck":
        if (isShipInside(pchar.location) || CheckShipSituation_GenQuest())
        {
            Return2SeaAfterCabin();
        }
        else
        {
            int idxLoadLoc = FindLoadedLocation();
            if (idxLoadLoc != -1)
            {
	            UnloadLocation(&Locations[idxLoadLoc]);
            }
            wdmReloadToSea();
        }
    break;
	}
}

void EndBattleLandInterface()
{
	if(!bLandInterfaceStart) return;
	bLandInterfaceStart = false;

	DeleteAttribute( pchar, "boxname" );

	BLI_DisableShow();
	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_END);

	DeleteClass(&objLandInterface);

	DelEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers");
	DelEventHandler(EVENT_DIALOG_START,"BLI_DisableShow");
	DelEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow");
	DelEventHandler("evntBLI_Update","BLI_UpdateObjectData");
	DelEventHandler("BI_CommandEndChecking","BLI_CheckCommand");
	DelEventHandler("BI_LaunchCommand","BLI_ExecuteCommand");
	DelEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands");
	DelEventHandler("evntFindDialogChar","procFindDialogChar");
	DelEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation");
	DelEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation");
	DelEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu");
	DelEventHandler("Control Activation","LI_ProcessControlPress");

	//#20171218-01 Re-enable fast action for cabin enter during boarding
    if(CheckAttribute(&BattleInterface, "LAi_ActivateReload")) {
        Log_SetActiveAction("Reload");
    }
    else {
        Log_SetActiveAction("Nothing");
    }
}

void BLI_SetObjectData()
{
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
    int fTmp, fTmp2;
	DeleteAttribute(&objLandInterface,"");

	objLandInterface.parameters.DoShowCommandos = InterfaceStates.BattleShow.Command;
	objLandInterface.data.Alarm = 0; // ��� �������

	// ����� ������ � ����
	aref ar;
	int i,cn;
	ref curCh;
	string attrName;
	//#20170318-20
	for(i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1) continue;
		curCh = GetCharacter(cn);
		attrName = "id"+i;
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
		//ar.picture = curCh.FaceId;
		//ar.health = 0.0;
		//ar.charge = 0.0;
	}
	BLI_SetMessageParameters();
	// ��������
	int idLngFile = LanguageOpenFile("commands_name.txt");
	objLandInterface.CommandTextures.list.t0.name = "battle_interface\LandCommands.tga";
	objLandInterface.CommandTextures.list.t0.xsize = 16;
	objLandInterface.CommandTextures.list.t0.ysize = 2;

 	objLandInterface.CommandTextures.list.t1.name = "battle_interface\LandTarget_SLB.tga";
	objLandInterface.CommandTextures.list.t1.xsize = 16;
	objLandInterface.CommandTextures.list.t1.ysize = 2;

	objLandInterface.CommandTextures.list.t2.name = "battle_interface\Cancel.tga";
	objLandInterface.CommandTextures.list.t2.xsize = 2;
	objLandInterface.CommandTextures.list.t2.ysize = 1;
	objLandInterface.CommandTextures.list.t3.name = "battle_interface\UseFood.tga";
	objLandInterface.CommandTextures.list.t3.xsize = 8;
	objLandInterface.CommandTextures.list.t3.ysize = 2;													
	// boal <--
	objLandInterface.CommandTextures.CommandTexNum = 0;
	//
	DeleteAttribute(&objIconsNote,"");
	objIconsNote.1x0 = LanguageConvertString(idLngFile, "go_store");
	objIconsNote.1x1 = LanguageConvertString(idLngFile, "go_shipyard");
	objIconsNote.1x2 = LanguageConvertString(idLngFile, "go_tavern");
	objIconsNote.1x3 = LanguageConvertString(idLngFile, "go_usurer");
	objIconsNote.1x4 = LanguageConvertString(idLngFile, "go_residence");
	objIconsNote.1x5 = LanguageConvertString(idLngFile, "go_prison");
	objIconsNote.1x6 = LanguageConvertString(idLngFile, "go_church");
	objIconsNote.1x7 = LanguageConvertString(idLngFile, "go_fort");
	objIconsNote.1x8 = LanguageConvertString(idLngFile, "go_portman");
	objIconsNote.1x9 = LanguageConvertString(idLngFile, "go_brothel");
	objIconsNote.1x10 = LanguageConvertString(idLngFile, "go_port");
	objIconsNote.1x13 = LanguageConvertString(idLngFile, "go_townexit");
	// ������ ������
	objLandInterface.Commands.Cancel.enable		= false;
	objLandInterface.Commands.Cancel.picNum		= 1;
	objLandInterface.Commands.Cancel.selPicNum	= 0;
	objLandInterface.Commands.Cancel.texNum		= 2;
	objLandInterface.Commands.Cancel.event		= "Cancel";
	objLandInterface.Commands.Cancel.name		= "Cancel";
	objLandInterface.Commands.Cancel.note		= LanguageConvertString(idLngFile, "sea_cancel");

	objLandInterface.Commands.FastReload.enable		= true;
	objLandInterface.Commands.FastReload.picNum		= 27;
	objLandInterface.Commands.FastReload.selPicNum	= 11;
	objLandInterface.Commands.FastReload.texNum		= 1;
	objLandInterface.Commands.FastReload.event		= "BI_FastReload";
	objLandInterface.Commands.FastReload.note		= LanguageConvertString(idLngFile, "land_FastReload");

	objLandInterface.Commands.OutDoor.enable		= true;
	objLandInterface.Commands.OutDoor.picNum		= 28;
	objLandInterface.Commands.OutDoor.selPicNum		= 12;
	objLandInterface.Commands.OutDoor.texNum		= 1;
	objLandInterface.Commands.OutDoor.event			= "BI_OutDoor";
	objLandInterface.Commands.OutDoor.note			= LanguageConvertString(idLngFile, "land_OutDoor");

    objLandInterface.Commands.ItemsUse.enable		= true;
 	objLandInterface.Commands.ItemsUse.picNum		= 20;
	objLandInterface.Commands.ItemsUse.selPicNum		= 4;
	objLandInterface.Commands.ItemsUse.texNum		= 0;
	objLandInterface.Commands.ItemsUse.event		= "BI_ItemsUse";
	objLandInterface.Commands.ItemsUse.note			= LanguageConvertString(idLngFile, "land_ItemsUse");

    objLandInterface.Commands.UseFood.enable		= true;
 	objLandInterface.Commands.UseFood.picNum		= 20;
	objLandInterface.Commands.UseFood.selPicNum		= 4;
	objLandInterface.Commands.UseFood.texNum		= 0;
	objLandInterface.Commands.UseFood.event			= "BI_UseFood";
	objLandInterface.Commands.UseFood.note			= LanguageConvertString(idLngFile, "land_UseFood");
	objLandInterface.Commands.DialogStart.enable	= true;
 	objLandInterface.Commands.DialogStart.picNum		= 17;
	objLandInterface.Commands.DialogStart.selPicNum		= 1;
	objLandInterface.Commands.DialogStart.texNum		= 0;
	objLandInterface.Commands.DialogStart.event		= "BI_DialogStart";
	objLandInterface.Commands.DialogStart.note		= LanguageConvertString(idLngFile, "land_DialogStart");

	objLandInterface.Commands.ItemsChange.enable	= true;
 	objLandInterface.Commands.ItemsChange.picNum		= 19;
	objLandInterface.Commands.ItemsChange.selPicNum		= 3;
	objLandInterface.Commands.ItemsChange.texNum		= 0;
	objLandInterface.Commands.ItemsChange.event		= "BI_ItemsChange";
	objLandInterface.Commands.ItemsChange.note		= LanguageConvertString(idLngFile, "land_ItemsChange");

	objLandInterface.Commands.TakeItem.enable		= true;
 	objLandInterface.Commands.TakeItem.picNum		= 16;
	objLandInterface.Commands.TakeItem.selPicNum		= 0;
	objLandInterface.Commands.TakeItem.texNum		= 0;
	objLandInterface.Commands.TakeItem.event		= "BI_TakeItem";
	objLandInterface.Commands.TakeItem.note			= LanguageConvertString(idLngFile, "land_TakeItem");

	objLandInterface.Commands.PlaceItem.enable		= true;
 	objLandInterface.Commands.PlaceItem.picNum		= 16;
	objLandInterface.Commands.PlaceItem.selPicNum		= 0;
	objLandInterface.Commands.PlaceItem.texNum		= 0;
	objLandInterface.Commands.PlaceItem.event		= "BI_PlaceItem";
	objLandInterface.Commands.PlaceItem.note		= LanguageConvertString(idLngFile, "land_PlaceItem");

	objLandInterface.Commands.UseBox.enable			= true;
 	objLandInterface.Commands.UseBox.picNum		    = 16;
	objLandInterface.Commands.UseBox.selPicNum		= 0;
	objLandInterface.Commands.UseBox.texNum		= 0;
	objLandInterface.Commands.UseBox.event			= "BI_UseBox";
	objLandInterface.Commands.UseBox.note			= LanguageConvertString(idLngFile, "land_UseBox");

	objLandInterface.Commands.DeadBox.enable			= true;
 	objLandInterface.Commands.DeadBox.picNum		    = 20;
	objLandInterface.Commands.DeadBox.selPicNum		= 4;
	objLandInterface.Commands.DeadBox.texNum		= 0;
	objLandInterface.Commands.DeadBox.event			= "BI_DeadBox";
	objLandInterface.Commands.DeadBox.note			= "����� ����";
	// ������ ��� � ����� -->
	objLandInterface.Commands.TalkSelf.enable	= true;
 	objLandInterface.Commands.TalkSelf.picNum	 	= 18;
	objLandInterface.Commands.TalkSelf.selPicNum	= 2;
	objLandInterface.Commands.TalkSelf.texNum		= 0;
	objLandInterface.Commands.TalkSelf.event		= "BI_TalkSelf";
	objLandInterface.Commands.TalkSelf.note		    = "����� �����";
	// ������ ��� � ����� <--
	objLandInterface.Commands.ActivateRush.enable	= true;
	objLandInterface.Commands.ActivateRush.picNum	= 28;
	objLandInterface.Commands.ActivateRush.selPicNum		= 12;
	objLandInterface.Commands.ActivateRush.texNum		= 0;
	objLandInterface.Commands.ActivateRush.event	= "BI_ActivateRush";
	objLandInterface.Commands.ActivateRush.note		= LanguageConvertString(idLngFile, "land_ActivateRush");

	objLandInterface.Commands.Exit_Deck.enable		= true;
	objLandInterface.Commands.Exit_Deck.picNum		= 30;
	objLandInterface.Commands.Exit_Deck.selPicNum		= 14;
	objLandInterface.Commands.Exit_Deck.texNum		= 0;
	objLandInterface.Commands.Exit_Deck.event		= "BI_Exit_Deck";
	objLandInterface.Commands.Exit_Deck.note		= LanguageConvertString(idLngFile, "land_Exit");
	// boal <--
	// ������ ���������������� ��������
	LanguageCloseFile(idLngFile);
	// go to icons
	int idxloc = FindLoadedLocation();
	string outGroupName = "";
	RecalculateHireCrew(idxloc);  // to_do ������ �� ������
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;
		CreateReloadPaths(outGroupName);
	}
	// objLandInterface.ManSign.backtexturename		= "battle_interface\ShipBackIcon.tga.tx";
	objLandInterface.ManSign.backtexturename		= "battle_interface\CharBackIcon.tga";
	objLandInterface.ManSign.backcolor				= argb(255,128,128,128);
	objLandInterface.ManSign.backuv					= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.backoffset				= "0.0,0.0";
	//#20180714-01
    fTmp = makeint(108.0 * fHtRatio);
    objLandInterface.ManSign.backiconsize		= fTmp + "," + fTmp;

	objLandInterface.ManSign.alarmtexturename		= "battle_interface\alarmback.tga.tx";
	objLandInterface.ManSign.alarmhighcolor			= argb(255,168,28,28);
	objLandInterface.ManSign.alarmlowcolor			= argb(64,168,28,28);
	objLandInterface.ManSign.alarmuptime			= 0.5;
	objLandInterface.ManSign.alarmdowntime			= 1.5;
	objLandInterface.ManSign.alarmuv				= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.alarmoffset			= "0.0,0.0";
	//#20180714-01
    fTmp = makeint(108.0 * fHtRatio);
    objLandInterface.ManSign.alarmiconsize		= fTmp + "," + fTmp;

	objLandInterface.ManSign.manstatetexturename	= "battle_interface\ShipState.tga.tx";
	objLandInterface.ManSign.manstatecolor			= argb(255,128,128,128);
	objLandInterface.ManSign.manhpuv				= "0.0,0.109,0.5,0.6875";
	objLandInterface.ManSign.manenegryuv			= "0.5,0.109,1.0,0.6875";
	
	//#20180714-01
    fTmp = makeint(-26.0 * fHtRatio);
    fTmp2 = makeint(-9.0 * fHtRatio);
    objLandInterface.ManSign.manhpoffset			= fTmp + "," + fTmp2;
    fTmp = makeint(29.0 * fHtRatio);
	fTmp2 = makeint(-9.0 * fHtRatio);
    objLandInterface.ManSign.manenegryoffset		= fTmp + "," + fTmp2;
    fTmp = makeint(54.0 * fHtRatio);
	fTmp2 = makeint(61.0 * fHtRatio);
    objLandInterface.ManSign.manhpiconsize		= fTmp + "," + fTmp2;
    fTmp = makeint(54.0 * fHtRatio);
	fTmp2 = makeint(61.0 * fHtRatio);
    objLandInterface.ManSign.manenergyiconsize	= fTmp + "," + fTmp2;

	// objLandInterface.ManSign.gunchargetexturename	= "battle_interface\ShipClass.tga.tx";
	objLandInterface.ManSign.gunchargetexturename	= "battle_interface\GunCharge.tga"; // LEO: ��� � ��� ������ UI
	objLandInterface.ManSign.gunchargecolor			= argb(255,70, 130, 180); // LEO: ��� � ��� ������ UI
	objLandInterface.ManSign.gunchargebackcolor		= argb(255,0, 0, 0); // LEO: ��� � ��� ������ UI
	objLandInterface.ManSign.gunchargeuv			= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";
	
	//#20180714-01
    fTmp = makeint(-10.0 * fHtRatio);
    fTmp2 = makeint(-44.0 * fHtRatio);
    objLandInterface.ManSign.gunchargeoffset		= fTmp + "," + fTmp2;
    fTmp = makeint(54.0 * fHtRatio);
    fTmp2 = makeint(14.0 * fHtRatio);
    objLandInterface.ManSign.gunchargeiconsize	= fTmp + "," + fTmp2;
	objLandInterface.ManSign.manfacecolor			= argb(255,128,128,128);
	
	//#20180714-01
    fTmp = makeint(-10.0 * fHtRatio);
    fTmp2 = makeint(-11.0 * fHtRatio);
    objLandInterface.ManSign.manfaceoffset		= fTmp + "," + fTmp2;
    fTmp = makeint(54.0 * fHtRatio);
    objLandInterface.ManSign.manfaceiconsize		= fTmp + "," + fTmp;
    objLandInterface.ManSign.commandlistverticaloffset = -40 * fHtRatio;
    fTmp = makeint(60.0 * fHtRatio);
    fTmp2 = makeint(87.0 * fHtRatio);
	
	//#20170318-20
	for(i = 1; i<=MAX_NUM_FIGHTERS + 1; i++) {
		string sOffsetIcon = "iconoffset" + i;
		objLandInterface.ManSign.(sOffsetIcon) = fTmp + "," + (fTmp + (i-1)*fTmp2);
	}

	int nLoc = FindLoadedLocation();
	if(nLoc >= 0) {
		int nFile = LanguageOpenFile("LocLables.txt");
		if(nFile >= 0) {
			objLandInterface.textinfo.islandname.font = "interface_button";
			objLandInterface.textinfo.islandname.scale = 1.5 * fHtRatio;
			objLandInterface.textinfo.islandname.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(170 * fHtRatio));
			objLandInterface.textinfo.islandname.pos.y = RecalculateVIcon(makeint(10 * fHtRatio));
			if (CheckAttribute(&locations[nLoc],"islandId"))
			{
				if (locations[nLoc].islandId != "Mein")
				{
					objLandInterface.textinfo.islandname.text = XI_convertString("Island:") + LanguageConvertString(nFile, locations[nLoc].islandId);
				}
				else
				{
					objLandInterface.textinfo.islandname.text = LanguageConvertString(nFile, locations[nLoc].islandId);
				}
			}
			else
			{
				objLandInterface.textinfo.islandname.text = "";//XI_convertString("Open Sea");
			}
			objLandInterface.textinfo.villagename.font = "interface_button";
			objLandInterface.textinfo.villagename.scale = 1.5 * fHtRatio;
			objLandInterface.textinfo.villagename.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(170 * fHtRatio));
			objLandInterface.textinfo.villagename.pos.y = RecalculateVIcon(makeint(40 * fHtRatio));

			objLandInterface.textinfo.locationname.font = "interface_button";
			objLandInterface.textinfo.locationname.scale = 1.5 * fHtRatio;
			objLandInterface.textinfo.locationname.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(170 * fHtRatio));
			objLandInterface.textinfo.locationname.pos.y = RecalculateVIcon(makeint(70 * fHtRatio));

            if (!CheckAttribute(&locations[nLoc],"fastreload"))
			{
			    objLandInterface.textinfo.villagename.text = "";
			}
			else
			{
				objLandInterface.textinfo.villagename.text = XI_ConvertString("Colony:") + LanguageConvertString(nFile, locations[nLoc].fastreload + " Town");
			}
			objLandInterface.textinfo.locationname.text = LanguageConvertString(nFile, locations[nLoc].id.label);
			LanguageCloseFile( nFile );
		}
	}
	objLandInterface.textinfo.datatext.font = "interface_button";
	objLandInterface.textinfo.datatext.scale = 1.5 * fHtRatio;
	objLandInterface.textinfo.datatext.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(170 * fHtRatio));
	objLandInterface.textinfo.datatext.pos.y = RecalculateVIcon(makeint(100 * fHtRatio));
	RefreshLandTime();
	//objLandInterface.textinfo.datatext.text = XI_convertString("Date:") + GetQuestBookData(); //GetDataDay()+" "+XI_ConvertString("target_month_" + GetDataMonth())+" "+GetDataYear();
	objLandInterface.textinfo.datatext.refreshable = true;
	
	//Charge info
	/*objLandInterface.textinfo.chargetext.font = "interface_button";
	objLandInterface.textinfo.chargetext.scale = 1.5 * fHtRatio;
	objLandInterface.textinfo.chargetext.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(170 * fHtRatio));
	objLandInterface.textinfo.chargetext.pos.y = RecalculateVIcon(makeint(130 * fHtRatio));
	objLandInterface.textinfo.chargetext.refreshable = true;
	//Hp info
	objLandInterface.textinfo.hptext.font = "interface_button";
	objLandInterface.textinfo.hptext.scale = 1.3 * fHtRatio;
	objLandInterface.textinfo.hptext.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(52 * fHtRatio));
	objLandInterface.textinfo.hptext.pos.y = RecalculateVIcon(makeint(94 * fHtRatio));
	objLandInterface.textinfo.hptext.refreshable = true;*/

	/*objLandInterface.imageslist.textinfoback1.texture = "battle_interface\textinfo_back.tga.tx";
	objLandInterface.imageslist.textinfoback1.color = argb(128,64,64,64);
	objLandInterface.imageslist.textinfoback1.uv = "0.0,0.0,1.0,0.125";
	objLandInterface.imageslist.textinfoback1.pos = (sti(showWindow.right) - RecalculateHIcon(188)) + "," +
		RecalculateVIcon(12) + "," +
		(sti(showWindow.right) - RecalculateHIcon(20)) + "," +
		RecalculateVIcon(20);
	objLandInterface.imageslist.textinfoback2.texture = "battle_interface\textinfo_back.tga.tx";
	objLandInterface.imageslist.textinfoback2.color = argb(128,64,64,64);
	objLandInterface.imageslist.textinfoback2.uv = "0.0,0.125,1.0,0.875";
	objLandInterface.imageslist.textinfoback2.pos = (sti(showWindow.right) - RecalculateHIcon(188)) + "," +
		RecalculateVIcon(20) + "," +
		(sti(showWindow.right) - RecalculateHIcon(20)) + "," +
		RecalculateVIcon(120);
	objLandInterface.imageslist.textinfoback3.texture = "battle_interface\textinfo_back.tga.tx";
	objLandInterface.imageslist.textinfoback3.color = argb(128,64,64,64);
	objLandInterface.imageslist.textinfoback3.uv = "0.0,0.875,1.0,1.0";
	objLandInterface.imageslist.textinfoback3.pos = (sti(showWindow.right) - RecalculateHIcon(188)) + "," +
		RecalculateVIcon(120) + "," +
		(sti(showWindow.right) - RecalculateHIcon(20)) + "," +
		RecalculateVIcon(128);
		*/
	//
	/*������� � ���� ���
	objLandInterface.textinfo.timetext.font = "interface_normal";
	objLandInterface.textinfo.timetext.scale = 1.0;
	objLandInterface.textinfo.timetext.pos.x = RecalculateHIcon(940);
	objLandInterface.textinfo.timetext.pos.y = RecalculateVIcon(100);
	objLandInterface.textinfo.timetext.text = makeint(GetHour())+":"+makeint(GetMinute());
    */

    // ��� � ��� ���, � ���� ��� ���� ;) - boal
    objLandInterface.CommandList.CommandMaxIconQuantity = 15;
	objLandInterface.CommandList.CommandIconSpace = 1;
	objLandInterface.CommandList.CommandIconLeft = makeint(108 * fHtRatio);//157;
	objLandInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	objLandInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(64 * fHtRatio));

	objLandInterface.CommandList.CommandNoteFont = "interface_button";
	objLandInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	objLandInterface.CommandList.CommandNoteScale = 1.5 * fHtRatio;
	objLandInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-54 * fHtRatio));

	objLandInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga.tx";
	objLandInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	objLandInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	objLandInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(32 * fHtRatio)) + "," + RecalculateVIcon(makeint(32 * fHtRatio));
	objLandInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(-30 * fHtRatio));
	objLandInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(46 * fHtRatio));

	// ������ ��� ����� ������ �� �����, � ���������� ������ �� ����� boal
	/*objLandInterface.CommandList.ActiveIcon_Texture = "battle_interface\enter_list.tga.tx";
	objLandInterface.CommandList.ActiveIcon_Offset = RecalculateHIcon(-49) + ",0";
	objLandInterface.CommandList.ActiveIcon_Size = RecalculateHIcon(48) + "," + RecalculateVIcon(48);
	objLandInterface.CommandList.ActiveIcon_UV1 = "0.5,0.0,1.0,1.0";
	objLandInterface.CommandList.ActiveIcon_UV2 = "0.0,0.0,0.5,1.0";
	objLandInterface.CommandList.ActiveIcon_Note = XI_ConvertString("MenuNote");*/

	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_START);
}


void RefreshChargeTime()
{
	ref chr = &Characters[nMainCharacterIndex];
	aref chr_ai;
	makearef(chr_ai,Characters[nMainCharacterIndex].chr_ai);
	//charge/hp info
    /*objLandInterface.textinfo.chargetext.text = chr_ai.charge;
	objLandInterface.textinfo.hptext.text = makeint(chr.chr_ai.hp) + "/" +  makeint(chr.chr_ai.hp_max);*/
	if (CheckAttribute(chr,"chr_ai.charge"))
	{
		float gunch = chr_ai.charge;
		if (gunch > 1.0)
		{
			gunch -= makeint(gunch);
		}
		
		if (CheckAttribute(chr,"chr_ai.charge_max"))
		{
			if (MakeInt(chr.chr_ai.charge) == makeint(chr.chr_ai.charge_max))
			{
				gunch = 1.0;
			}
		}
		else
		{
			chr.chr_ai.charge_max = 1;
			chr.chr_ai.chargeprc = 1;
		}
		float gunchm = 1.0;
		DrawCharacterHPEx(makefloat(0.35/makefloat(gunchm)*makefloat(gunch)),makefloat(10.0/makefloat(gunchm)*makefloat(gunch)));
	}
	else chr_ai.charge = 0.0;
}

bool FindUserIcon(string id,ref uiref)
{
	aref arroot,ar; makearef(arroot,objLandInterface.UserIcons);
	int iMax = GetAttributesNum(arroot); //fix
	for(int i=0; i<iMax; i++)
	{
		ar = GetAttributeN(arroot,i);
		if(ar.name != id) continue;
		uiref = ar;
		return true;
	}
	return false;
}

void BLI_SetMessageParameters()
{
	objLandInterface.MessageIcons.IconWidth = RecalculateHIcon(64);
	objLandInterface.MessageIcons.IconHeight = RecalculateVIcon(24);
	objLandInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	objLandInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateHIcon(80+40);
	objLandInterface.MessageIcons.IconMaxQuantity = 4;
	objLandInterface.MessageIcons.BlendTime = 3.0;
	objLandInterface.MessageIcons.FallSpeed = 22.0;
	objLandInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	objLandInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	objLandInterface.MessageIcons.BlindUpTime = 0.5;
	objLandInterface.MessageIcons.BlindDownTime = 1.0;
	objLandInterface.MessageIcons.texture = "battle_interface\MessageIcons.tga.tx";
	objLandInterface.MessageIcons.TexHSize = 2;
	objLandInterface.MessageIcons.TexVSize = 2;
}

void BLI_UpdateObjectData()
{
	bool bIsRiskAlarm = LAi_group_IsActivePlayerAlarm();
	if(sti(objLandInterface.data.Alarm)!=bIsRiskAlarm) BLI_RefreshCommandMenu();
	objLandInterface.data.Alarm = bIsRiskAlarm;

	aref ar,arItm;
	int i,cn;
	ref curCh;
	string attrName;
	for(i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		attrName = "id"+i;
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1 || !IsEntity(&Characters[cn]))
		{
			DeleteAttribute(&objLandInterface,"data.icons."+attrName);
			continue;
		}
		curCh = GetCharacter(cn);
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
		//ar.picture = curCh.FaceId;
		//ar.health = LAi_GetCharacterRelHP(curCh);
		//ar.charge = LAi_GetCharacterRelCharge(curCh);
		//ar.shootMax = LAi_GetCharacterChargeQuant(curCh);
		//ar.shootCur = LAi_GetCharacterChargeCur(curCh);
		//ar.poison = LAi_IsPoison(curCh);
	}

	PostEvent("evntBLI_Update",BLI_UPDATE_PERIOD);
}

void BLI_SetPossibleCommands()
{
	int chrMode = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"IsFightMode");

	bool bTmpBool;
	bool bUseCommand = false;
	int i;
	aref rootcom,curcom;
	makearef(rootcom,objLandInterface.Commands);
	int iMax = GetAttributesNum(rootcom); //fix
	for(i=0; i<iMax; i++)
	{
		curcom = GetAttributeN(rootcom,i);
		curcom.enable = false;
	}

	if(chrMode==0)
	{
		bTmpBool = true;
		if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
		if(!LAi_IsCharacterControl(pchar)) bTmpBool = false;
		if(bDisableFastReload)	bTmpBool = false;
		if(!IsEnableFastTravel()) bTmpBool = false;
		// boal ������ ���� ���������
		if (chrDisableReloadToLocation) bTmpBool = false;
		if (!CheckAttribute(loadedLocation,"fastreload")) bTmpBool = false;  // � ����� ������ ����������
		if (bTmpBool) // ��� ��� ����� ����������, �������� ����� ����
		{
		    string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
			if (sNation != "none")
			{
				i = sti(sNation);
				bTmpBool = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
				if (bTmpBool && (i != PIRATE))// && !CheckAttribute(pchar, "CheckStateOk"))
				{
					bTmpBool = false;
				}
				else
				{
		    		bTmpBool = true;
				}
			}
		}
		objLandInterface.Commands.FastReload.enable	= bTmpBool;
		///// boal -->
		i = -1;
		if (CheckAttribute(pchar,"dialogready")) i=sti(pchar.dialogready);
		if (i>=0)
		{
			objLandInterface.Commands.DialogStart.enable	= true;
			if (isOfficerInShip(&Characters[i], true) || CheckAttribute(&Characters[i], "IsCompanionClone"))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
			// ������
			/*
			else
			{
				if( CheckAttribute(&Characters[i],"InterfaceFlags.ItemsChange") &&
					Characters[i].InterfaceFlags.ItemsChange != "0" )
				{
					objLandInterface.Commands.ItemsChange.enable = true;
				}
			}   */
		}
		// boal 22.01.2004 -->
		else
		// ����� � �������� ������ � ����� (� �������� ��� �������!)
		{
		    i = LAi_FindNearestVisCharacter(pchar, 1);
		    if( i>0 && IsOfficer(GetCharacter(i)) && IsCharacterPerkOn(pchar, "SharedExperience"))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
		}
		//////// <--
		bUseCommand = true;
	}
	if (objLandInterface.Commands.DialogStart.enable == false && LAi_IsCharacterControl(pchar) && !LAi_IsFightMode(pchar) && !LAi_grp_alarmactive && !chrDisableReloadToLocation)
	{
    	objLandInterface.Commands.TalkSelf.enable = true;//boal �������� � ����� ��� � �����
    	bUseCommand = true;
    }
	if(GetCharacterPerkUsing(pchar,"Rush"))
	{
		objLandInterface.Commands.ActivateRush.enable = true;
		bUseCommand = true;
	}
	if( CanBeUseItem(pchar) )
	{
		objLandInterface.Commands.ItemsUse.enable = true;
		bUseCommand = true;
	}
	if( CanBeUseFood(pchar) )
	{
		objLandInterface.Commands.UseFood.enable = true;
		bUseCommand = true;
	}
	if(CheckAttribute(pchar,"boxname"))
	{
		objLandInterface.Commands.UseBox.enable	= true;
		bUseCommand = true;
	}
	if( CheckAttribute(pchar,"activeItem") && pchar.activeItem!="" )
	{
		bUseCommand = true;
		if( CheckAttribute(pchar,"activeItem.pick") && pchar.activeItem.pick=="1" )
		{
			objLandInterface.Commands.TakeItem.enable = true;
		}
		else
		{
			objLandInterface.Commands.PlaceItem.enable = true;
		}
	}
	if( chrWaitReloadLocator != "" )
	{
		bUseCommand = true;
		objLandInterface.Commands.OutDoor.enable = true;
	}
    // boal dead can be searched 14.12.2003 -->
    i = Dead_FindCloseBody();
    if (i != -1)
    {
        objLandInterface.Commands.DeadBox.enable	= true;
		bUseCommand = true;
    }
	// boal dead can be searched 14.12.2003 <--
	// boal 20.03.2004 -->
    if (isShipInside(pchar.location) && !chrDisableReloadToLocation)
    {
       bUseCommand = true;
       objLandInterface.Commands.Exit_Deck.enable = true;
    }
	
	// ugeen  --> ����������� �������� ������ ��� �������� �� ����������� ������� --> ��������� ����� ���� ��������� �������
	if(CheckAttribute(loadedLocation, "CabinType") && !chrDisableReloadToLocation) 
	{
		if(CheckShipSituation_GenQuest())
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}	
	}
	// <-- ugeen
    // boal 20.03.2004 <--
    // boal 20.03.2004 <--
    if (pchar.location == "Ship_deck")
    {
		if (CheckQuestAttribute("Munity", "Deads"))
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}
    }
	//objLandInterface.Commands.OutDoor.enable		= true;
	if(!bUseCommand)
	{
		SendMessage(&objLandInterface,"llllll",BI_IN_SET_COMMAND_MODE,0,-1,-1,-1,-1);
	}
}

/*void BLI_evntRefreshCommandMenu()
{
	DelEventHandler("frame","BLI_evntRefreshCommandMenu");
	BLI_RefreshCommandMenu();
}
void BLI_RefreshCommandMenu()
{
	SendMessage(&objLandInterface,"lllll",BI_IN_SET_COMMAND_MODE,-1,-1,-1,-1,-1);
}*/

void procFindDialogChar()
{
	int dlgChar = -1;
	if(!LAi_IsBoardingProcess())
		dlgChar = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");

	int oldDlgChar = -1;
	if(CheckAttribute(pchar,"dialogready")) oldDlgChar = sti(pchar.dialogready);

	if(dlgChar!=oldDlgChar)
	{
		pchar.dialogready = dlgChar;
		//BLI_RefreshCommandMenu();
		LI_CareUpdateCommandList();
	}
	PostEvent("evntFindDialogChar",1000);
}

void BLI_ChrEnterToLocation()
{
	aref loc = GetEventData();
	aref chr = GetEventData();
	string group = GetEventData();
	string locator = GetEventData();
	aref locList,locCur;
	int i,n;

	if(sti(chr.index) != nMainCharacterIndex) return;

	if(group=="reload")
	{
		makearef(locList,loc.reload);
		n = GetAttributesNum(locList);
		for(i=0;i<n;i++)
		{
			locCur = GetAttributeN(locList,i);
			if(locCur.name == locator) break;
		}
		if(i<n)
		{
			i = FindLocation(locCur.go);
			if(i>=0)
			{
				if(CheckAttribute(&locations[i],"id.label"))
				{
					Log_SetStringToLog( LanguageConvertString(g_LocLngFileID,locations[i].id.label) );
				}
			}
		}
		//SetEventHandler("frame","BLI_evntRefreshCommandMenu",1);
		LI_CareUpdateCommandList();
	}
}

void BLI_ChrExitFromLocation()
{
	//SetEventHandler("frame","BLI_evntRefreshCommandMenu",1);
	LI_CareUpdateCommandList();
}

void LI_Reload()
{
	Event("Control Activation","s","ChrAction");
}

bool SetUsedPotionIcons()
{
	aref arItm, ar, uiref;
	int i, itmIdx, nq;

	bool bUsed = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"potion") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; i--;
		}
	}

	string UI_name;
	int UI_idx = 0;

	itmIdx = FindPotionFromChr(pchar, &arItm, 0);
	while(itmIdx>=0)
	{
		if(EnablePotionUsing(PChar, arItm) || EnableAntidoteUsing(PChar, arItm))
		{
			UI_idx++;
			UI_name = "potion"+UI_idx;
			objLandInterface.UserIcons.(UI_name).enable = true;
			objLandInterface.UserIcons.(UI_name).pic = GetPotionPicture(arItm);
            objLandInterface.UserIcons.(UI_name).selpic = GetPotionPicture(arItm) - 16;
			objLandInterface.UserIcons.(UI_name).tex = GetPotionTexture(arItm);
			objLandInterface.UserIcons.(UI_name).name = UI_name;
			objLandInterface.UserIcons.(UI_name).potion = arItm.id;
			bUsed = true;
		}
		itmIdx = FindPotionFromChr(pchar, &arItm, itmIdx+1);
	}
	return bUsed;
}

bool SetUsedFoodIcons()
{
	aref arItm, ar, uiref;
	int i, itmIdx, nq;

	bool bUsed = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"Food") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; i--;
		}
	}

	string UI_name;
	int UI_idx = 0;

	itmIdx = FindFoodFromChr(pchar, &arItm, 0);
	while(itmIdx>=0)
	{
		if( EnableFoodUsing(pchar,arItm) )
		{
			UI_idx++;
			UI_name = "Food"+UI_idx;
			objLandInterface.UserIcons.(UI_name).enable = true;
			objLandInterface.UserIcons.(UI_name).pic = GetFoodPicture(arItm);
            		objLandInterface.UserIcons.(UI_name).selpic = GetFoodSelectPicture(arItm);
			objLandInterface.UserIcons.(UI_name).tex = GetFoodTexture(arItm);
			objLandInterface.UserIcons.(UI_name).name = UI_name;
			objLandInterface.UserIcons.(UI_name).Food = arItm.id;
			bUsed = true;
		}
		itmIdx = FindFoodFromChr(pchar, &arItm, itmIdx+1);
	}

	return bUsed;
}

bool SetReloadIcons()
{
	int i, nq, locidx;
	aref ar, curloc, locref, locList, uiref;

	bool bUse = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"location") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--;
			i--;
		}
	}

	int idxloc = FindLoadedLocation();
	string str1,str2,fastLocName;
	string outGroupName = "";
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;

		if( CheckAttribute(&objFastReloadTable,"table."+outGroupName) )
		{
			makearef(locList,objFastReloadTable.table.(outGroupName));
			nq = GetAttributesNum(locList);
			// to port icon
			if( GetCharacterShipType(pchar)!=SHIP_NOTUSED )
			{
				if( CheckFastJump(Locations[idxloc].id, pchar.location.from_sea) )
				{
					objLandInterface.UserIcons.port.enable = true;
					objLandInterface.UserIcons.port.pic = 26;
					objLandInterface.UserIcons.port.selpic = 10;
					objLandInterface.UserIcons.port.tex = 1;
					objLandInterface.UserIcons.port.name = "reloadtoport";
					objLandInterface.UserIcons.port.location = pchar.location.from_sea;
					objLandInterface.UserIcons.port.locator = "reload1";
					objLandInterface.UserIcons.port.note = GetNodeForIcon(1, 10);
					bUse = true;
				}
			}
			for(i=0; i<nq; i++)
			{
				curloc = GetAttributeN(locList,i);
				if(!CheckFastJump(Locations[idxloc].id, curloc.location) )
				{
					continue;
				}
				fastLocName = "fr_"+(i+1);
				objLandInterface.UserIcons.(fastLocName).enable = true;
				objLandInterface.UserIcons.(fastLocName).pic = sti(curloc.pic)+16;
				objLandInterface.UserIcons.(fastLocName).selpic = curloc.pic;
				objLandInterface.UserIcons.(fastLocName).tex = 1+sti(curloc.tex);
				objLandInterface.UserIcons.(fastLocName).name = "reload"+i;
				objLandInterface.UserIcons.(fastLocName).location = curloc.location;
				objLandInterface.UserIcons.(fastLocName).note = GetNodeForIcon(1+sti(curloc.tex), sti(curloc.pic));
				bUse = true;
			}
		}
	}
	int idLngFile = LanguageOpenFile("commands_name.txt");

	return bUse;
}

void SetOfficerTexture(int officerIdx)
{
	aref ar; makearef(ar,objLandInterface.Parameters);
	string attrName = "iconTexture"+officerIdx;

	int cn = GetOfficersIndex(pchar,officerIdx);
	if(cn<0) {
		DeleteAttribute(ar,attrName);
		ar.(attrName) = "";
	} else {
		ar.(attrName) = "interfaces\portraits\64\face_"+Characters[cn].FaceID+".tga";
	}
}

void BLI_UpdateOfficers()
{
	//Boyer mod
	/*
	SetOfficerTexture(0);
	SetOfficerTexture(1);
	SetOfficerTexture(2);
	SetOfficerTexture(3);
	//Boyer mod for add'l fighters
	SetOfficerTexture(4);
	SetOfficerTexture(5);
	SetOfficerTexture(6);
	*/
	for(int i=0;i<=MAX_NUM_FIGHTERS;i++) {
		SetOfficerTexture(i);
	}
	//End Boyer mod

	/*
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 0, objLandInterface.Parameters.iconTexture0);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 1, objLandInterface.Parameters.iconTexture1);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 2, objLandInterface.Parameters.iconTexture2);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 3, objLandInterface.Parameters.iconTexture3);
	//Boyer mod for add'l fighters
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 4, objLandInterface.Parameters.iconTexture4);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 5, objLandInterface.Parameters.iconTexture5);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 6, objLandInterface.Parameters.iconTexture6);
	*/
	for(i=0;i<=MAX_NUM_FIGHTERS;i++) {
		string sTexture;
		sTexture = "iconTexture" + i;
		SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, i, objLandInterface.Parameters.(sTexture));
	}
	//End Boyer mod
	//Log_TestInfo("BLI_UpdateOfficers");
	BLI_UpdateObjectData();
	LI_CareUpdateCommandList();
	SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");  // ���� ������ ���� (������) boal
}

int GetPotionPicture(aref arItm)
{
	if( CheckAttribute(arItm,"potion.pic") ) {
		return sti(arItm.potion.pic);
	}
	trace("Item "+arItm.id+ " hav`t POTION.PIC attribute");
	return 0;
}

int GetPotionTexture(aref arItm)
{
	if( !CheckAttribute(arItm,"potion.tex") ) {
		trace("Item "+arItm.id+ " hav`t POTION.TEX attribute");
		return 0;
	}
	return sti(arItm.potion.tex);
}

int GetFoodPicture(aref arItm)
{
	if( CheckAttribute(arItm,"Food.pic") ) {
		return sti(arItm.Food.pic);
	}
	return 0;
}

int GetFoodSelectPicture(aref arItm)
{
	if( CheckAttribute(arItm,"Food.selpic") ) {
		return sti(arItm.Food.selpic);
	}
	return 0;
}

int GetFoodTexture(aref arItm)
{
	if( !CheckAttribute(arItm,"Food.tex") ) {
		return 0;
	}
	return sti(arItm.Food.tex);
}

// ����� �� ����� ���� ��� ��
bool CanBeUseItem(ref chref)
{
	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute(&Items[i],"potion") && CheckAttribute(chref,"items."+Items[i].id) ) {
			if( EnablePotionUsing(chref,&Items[i]) ) {return true;}
		}
	}
	return false;
}

bool CanBeUseFood(ref chref)
{
	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute(&Items[i],"Food") && CheckAttribute(chref,"items."+Items[i].id) ) {
			if( EnableFoodUsing(chref,&Items[i]) ) {return true;}
		}
	}
	return false;
}
object objIconsNote;
string GetNodeForIcon(int nTex, int nPic)
{
	string attrName = nTex+"x"+nPic;
	if( CheckAttribute(objIconsNote,attrName) ) return objIconsNote.(attrName);
	return "";
}

void LI_ProcessControlPress()
{
	string ControlName = GetEventData();

	switch(ControlName)
	{
		case "hk_Cure": // TO_DO �� ������� - � ���� � �� �����
			if( LAi_GetCharacterRelHP(pchar) < 1.0 )
			{
				float dhlt = LAi_GetCharacterMaxHP(pchar) - LAi_GetCharacterHP(pchar);
				string btl = FindHealthForCharacter(pchar, dhlt);
				DoCharacterUsedItem(pchar, btl);
			}
		break;

		case "LICommandsActivate":
			PlaySound("interface\ok.wav"); // boal ����� �����!
		break;
	}
}

void BLI_RefreshCommandMenu()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}
void LI_CareUpdateCommandList()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}

void SetCharacterIconData(int chrindex, aref arData)
{
	ref chref = GetCharacter(chrindex);
	arData.chrindex = chrindex;
	arData.health = LAi_GetCharacterRelHP(chref);
	arData.energy = LAi_GetCharacterRelEnergy(chref);
	arData.shootMax = LAi_GetCharacterChargeQuant(chref);
	arData.shootCur = LAi_GetCharacterChargeCur(chref);
	if( CheckAttribute(chref,"FaceId") ) {
		//arData.picture = chref.FaceId;
		arData.texture = "battle_interface\portraits\face_"+chref.FaceID+".tga.tx";
		if( CheckAttribute(chref,"FaceUV") ) {
			arData.uv = chref.FaceUV;
		} else {
			arData.uv = "0.0,0.0,1.0,1.0";
		}
	} else {
		arData.texture = "battle_interface\two.tga.tx";
		if( chrindex == 1 ) {
			arData.uv = "0.5,0.0,1.0,1.0";
		} else {
			arData.uv = "0.0,0.0,0.5,1.0";
		}
	}
	//arData.charge = LAi_GetCharacterRelCharge(chref);
	//arData.poison = LAi_IsPoison(chref);
}
