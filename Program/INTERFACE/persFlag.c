#define CONFIRMMODE_FLAG_DELETE		1
#define CONFIRMMODE_FLAG_SELECT		2

#define FLAGIMAGE_UPDATE_TIME	0
#define FLAG_IMAGE_LIST_COUNT 60
#define FLAG_IMAGE_LIST_PERLINE 10

#define FLAG_TEXTURES_COUNT 143
#define PERS_FLAG_PICTURES_GROUP "PERSONAL_FLAG"

int g_nInterfaceFileID = -1;
string currentProfile;

int g_nCurrentItemIndex = 0;
int g_nFirstItemIndex = -1;
int g_nItemQuantity = 0;

object g_oItemList[FLAG_IMAGE_LIST_COUNT];
object g_oItemContainer;

int g_nConfirmMode;
string g_sConfirmReturnWindow;
bool hasPersFlgPerk = false;
int nPersFlagNum = -1;
string sMessageMode = "";
bool bReplaceAllFlags = false;
bool bApplySquad = false;

void InitInterface_BB(string iniName, bool isSave, bool isMainMenu)
{
    hasPersFlgPerk = CheckCharacterPerk(pchar, "FlagPers");
    bReplaceAllFlags = CheckAttribute(pchar, "persFlag.replaceAll");
    bApplySquad = CheckAttribute(pchar, "persFlag.applySquad");

	GameInterface.title = "titlePersFlag";

	g_nInterfaceFileID = LanguageOpenFile("interface_strings.txt");

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	// by default first item is selected
	SendMessage( &GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "SAVEIMG1", 5, true );

	SetSelectable("BTN_SETFLAG", hasPersFlgPerk);
	SetSelectable("BTN_DELETE", hasPersFlgPerk);

	if(hasPersFlgPerk) {
        if(CheckAttribute(pchar, "persFlag"))
            nPersFlagNum = sti(pchar.persFlag);
	}
	else {
        SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SETFLAG", 0, "needPerk" );
	}
	SetNewGroupPicture("CURRENT_FLAG", PERS_FLAG_PICTURES_GROUP, "flg" + nPersFlagNum);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHECK_REPLACEALL", 2, 1, bReplaceAllFlags );
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHECK_APPLYSQUAD", 2, 1, bApplySquad );

	InitItemObjList();

	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("eventBtnAction","procBtnAction",0);
	SetEventHandler("eventSelecterActivate","procSelecterActivate",0);
	SetEventHandler("eventSelecterMove","procSelecterMove",0);
	SetEventHandler("eventItemClick","procItemClick",0);
	SetEventHandler("evLoadOneItemInfo","procLoadOneItemInfo",0);
	SetEventHandler("eventConfirm","procConfirm",0);
	SetEventHandler("ScrollPosChange","ScrollPosChange",0);
	SetEventHandler("ItemLoad","ItemLoad",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
    SetEventHandler("CheckButtonChange","procCheckBoxChange",0);

	PostEvent( "evLoadOneItemInfo",1 );

	SetCurrentItem();
}

void SetCurrentItem()
{
	// fill item list
	DeleteAttribute( &g_oItemContainer,"" );
	string attr;
    int i;

	for(i = 0; i< FLAG_TEXTURES_COUNT, i++) {
        attr = "s" + i;
		g_oItemContainer.(attr).savename = "flg" + i;
	}
	g_oItemContainer.picTexture = PERS_FLAG_PICTURES_GROUP;
	g_oItemContainer.listsize = FLAG_TEXTURES_COUNT;
	g_nItemQuantity = FLAG_TEXTURES_COUNT;
	g_nFirstItemIndex = -1;
	FillItemList( (g_nCurrentItemIndex/FLAG_IMAGE_LIST_COUNT) * FLAG_IMAGE_LIST_COUNT );
	setInitSelection(nPersFlagNum);
	SetClickable("ITEMSCROLL",g_nItemQuantity>FLAG_IMAGE_LIST_COUNT);
}

void setInitSelection(int _sel)
{
    if(_sel < 0 || _sel >= FLAG_TEXTURES_COUNT) {
        _sel = 0;
    }
    int nTimeout = 500;
    int nLinesPer = (FLAG_IMAGE_LIST_COUNT / FLAG_IMAGE_LIST_PERLINE) - 1;
    int nLineQ = g_nItemQuantity / FLAG_IMAGE_LIST_PERLINE;
    int nLine = 0;
    if(nLineQ != 0)
        nLine = makeint( makefloat(nLineQ) * (makefloat(_sel / FLAG_IMAGE_LIST_PERLINE) / makefloat(nLineQ) ));
    int imgIdx = _sel + 1;
    if(nLine > nLinesPer) {
        FillItemList(nLine * FLAG_IMAGE_LIST_PERLINE);
        imgIdx = (_sel + 1) % FLAG_IMAGE_LIST_PERLINE;
        nTimeout = 350;
    }
    if(imgIdx != 1)
        SetSelecting(0,false);
    string sName = "SAVEIMG" + imgIdx;
    PostEvent("eventItemClick", nTimeout, "ls", 0, sName);
}

void ShowInfoWindow()
{

}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "CHECK_REPLACEALL") {
        bReplaceAllFlags = bBtnState;
        return;
	}
	if(sNodName == "CHECK_APPLYSQUAD") {
        bApplySquad = bBtnState;
        return;
	}
}

void ProcessCancelExit()
{
	DelEventHandler("ScrollPosChange","ScrollPosChange");
	DelEventHandler("eventConfirm","procConfirm");
	DelEventHandler("evLoadOneItemInfo","procLoadOneItemInfo");
	DelEventHandler("eventItemClick","procItemClick");
	DelEventHandler("eventSelecterActivate","procSelecterActivate");
	DelEventHandler("eventSelecterMove","procSelecterMove");
	DelEventHandler("eventBtnAction","procBtnAction");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ItemLoad","ItemLoad");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
    DelEventHandler("CheckButtonChange","procCheckBoxChange");

	IDoExit(RC_INTERFACE_TO_SHIP);
}

void IDoExit(int exitCode)
{
    exitCode = RC_INTERFACE_TO_SHIP;
	LanguageCloseFile(g_nInterfaceFileID);

    interfaceResultCommand = exitCode;
	EndCancelInterface(false);
}

void procSelecterActivate()
{
	ItemSelectCurrentIntoSlot();
}

void procBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( iComIndex == ACTION_RIGHTSTEP ) {
		if( sNodName == "BTN_SETFLAG" ) {
			if( GetSelectable("BTN_DELETE") ) {
				SetCurrentNode("BTN_DELETE");
			} else {
				sNodName = "BTN_DELETE";
			}
		}
		if( sNodName == "BTN_DELETE" ) {
			SetCurrentNode("BTN_EXIT");
		}
		return;
	}
	if( iComIndex == ACTION_LEFTSTEP ) {
		if( sNodName == "BTN_EXIT" ) {
			if( GetSelectable("BTN_DELETE") ) {
				SetCurrentNode("BTN_DELETE");
			} else {
				sNodName = "BTN_DELETE";
			}
		}
		if( sNodName == "BTN_DELETE" ) {
			if( GetSelectable("BTN_SETFLAG") ) {
				SetCurrentNode("BTN_SETFLAG");
			} else {
				sNodName = "BTN_SETFLAG";
			}
		}
		return;
	}
	if( iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK ) {
		if( sNodName == "BTN_SETFLAG" ) {
			ItemSelectCurrentIntoSlot();
		}
		if( sNodName == "BTN_DELETE" ) {
			DoConfirm(CONFIRMMODE_FLAG_DELETE);
		}
	}
}

void ItemSelectCurrentIntoSlot()
{
    if( g_nCurrentItemIndex<0 || g_nCurrentItemIndex>=g_nItemQuantity ) {
        return;
    }
    DoConfirm(CONFIRMMODE_FLAG_SELECT);
}

void procSelecterMove()
{
	int iComIndex = GetEventData();

	int nLeft,nTop,nRight,nBottom;
	bool bMakeMove = false;

	switch( iComIndex )
	{
	case ACTION_RIGHTSTEP:
		bMakeMove = GetMoveToOtherItem( g_nCurrentItemIndex+1, &nLeft,&nTop,&nRight,&nBottom );
	break;
	case ACTION_LEFTSTEP:
		bMakeMove = GetMoveToOtherItem( g_nCurrentItemIndex-1, &nLeft,&nTop,&nRight,&nBottom );
	break;
	case ACTION_UPSTEP:
		bMakeMove = GetMoveToOtherItem( g_nCurrentItemIndex-FLAG_IMAGE_LIST_PERLINE, &nLeft,&nTop,&nRight,&nBottom );
	break;
	case ACTION_DOWNSTEP:
		bMakeMove = GetMoveToOtherItem( g_nCurrentItemIndex+FLAG_IMAGE_LIST_PERLINE, &nLeft,&nTop,&nRight,&nBottom );
	break;
	}
	if( bMakeMove ) {
		SendMessage( &GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE,"ITEM_SELECTER",0, nLeft,nTop,nRight,nBottom );
	}
}

void SetSelecting(int nSlot,bool bSelect)
{
	string sNodeName;
	int nColor;
	sNodeName = "SAVEIMG"+(nSlot+1);
	if( bSelect ) {
		nColor = argb(255,255,255,255);
	} else {
		nColor = argb(255,148,148,148);
	}
	SendMessage( &GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 5, bSelect );
}

bool GetMoveToOtherItem( int nNewItemIndex, ref rLeft, ref rTop, ref rRight, ref rBottom )
{
	if( nNewItemIndex < 0 ) return false;

	if( g_nCurrentItemIndex == nNewItemIndex ) return false;

	int nMaxQ = (g_nItemQuantity + (FLAG_IMAGE_LIST_PERLINE-1))/ FLAG_IMAGE_LIST_PERLINE * FLAG_IMAGE_LIST_PERLINE + FLAG_IMAGE_LIST_PERLINE;
	if( nNewItemIndex > nMaxQ ) return false;

	int nOldIdx = g_nCurrentItemIndex - g_nFirstItemIndex;
	int nNewIdx = nNewItemIndex - g_nFirstItemIndex;

	if( nNewIdx < 0 ) {
		if( g_nFirstItemIndex > 0 ) {
			FillItemList(g_nFirstItemIndex - FLAG_IMAGE_LIST_PERLINE);
		}
		nNewIdx = nNewItemIndex - g_nFirstItemIndex;
	}
	if( nNewIdx > ( FLAG_IMAGE_LIST_COUNT - 1)) {
		FillItemList(g_nFirstItemIndex + FLAG_IMAGE_LIST_PERLINE);
		nNewIdx = nNewItemIndex - g_nFirstItemIndex;
	}
	string sNodName = "SAVEIMG"+(nNewIdx+1);

	if( nNewIdx>0 && GetSelectable(sNodName)==false ) {
		nNewIdx = g_nCurrentItemIndex - g_nFirstItemIndex;
		nNewItemIndex = g_nCurrentItemIndex;
		if( nNewIdx == nOldIdx ) {
			return false;
		}
	}
	if( g_nCurrentItemIndex>=0 && nOldIdx>=0 && nOldIdx<FLAG_IMAGE_LIST_COUNT ) {
		SetSelecting(nOldIdx,false);
	}
	SetSelecting(nNewIdx,true);

	g_nCurrentItemIndex = nNewItemIndex;

	int nLeft = 0;
	int nTop = 0;
	int nRight = 0;
	int nBottom = 0;

	switch( nNewIdx )
	{
	case 0: nLeft=24; nTop=56; nRight=91; nBottom=125; break;
    case 1: nLeft=100; nTop=56; nRight=168; nBottom=125; break;
    case 2: nLeft=175; nTop=56; nRight=243; nBottom=125; break;
    case 3: nLeft=249; nTop=56; nRight=317; nBottom=125; break;
    case 4: nLeft=324; nTop=56; nRight=392; nBottom=125; break;
    case 5: nLeft=400; nTop=56; nRight=468; nBottom=125; break;
    case 6: nLeft=475; nTop=56; nRight=543; nBottom=125; break;
    case 7: nLeft=550; nTop=56; nRight=618; nBottom=125; break;
    case 8: nLeft=624; nTop=56; nRight=692; nBottom=125; break;
    case 9: nLeft=700; nTop=56; nRight=768; nBottom=125; break;
    case 10: nLeft=24; nTop=132; nRight=91; nBottom=200; break;
    case 11: nLeft=100; nTop=132; nRight=168; nBottom=200; break;
    case 12: nLeft=175; nTop=132; nRight=243; nBottom=200; break;
    case 13: nLeft=249; nTop=132; nRight=317; nBottom=200; break;
    case 14: nLeft=324; nTop=132; nRight=392; nBottom=200; break;
    case 15: nLeft=400; nTop=132; nRight=468; nBottom=200; break;
    case 16: nLeft=475; nTop=132; nRight=543; nBottom=200; break;
    case 17: nLeft=550; nTop=132; nRight=618; nBottom=200; break;
    case 18: nLeft=624; nTop=132; nRight=692; nBottom=200; break;
    case 19: nLeft=700; nTop=132; nRight=768; nBottom=200; break;
    case 20: nLeft=24; nTop=208; nRight=91; nBottom=276; break;
    case 21: nLeft=100; nTop=208; nRight=168; nBottom=276; break;
    case 22: nLeft=175; nTop=208; nRight=243; nBottom=276; break;
    case 23: nLeft=249; nTop=208; nRight=317; nBottom=276; break;
    case 24: nLeft=324; nTop=208; nRight=392; nBottom=276; break;
    case 25: nLeft=400; nTop=208; nRight=468; nBottom=276; break;
    case 26: nLeft=475; nTop=208; nRight=543; nBottom=276; break;
    case 27: nLeft=550; nTop=208; nRight=618; nBottom=276; break;
    case 28: nLeft=624; nTop=208; nRight=692; nBottom=276; break;
    case 29: nLeft=700; nTop=208; nRight=768; nBottom=276; break;
    case 30: nLeft=24; nTop=284; nRight=91; nBottom=352; break;
    case 31: nLeft=100; nTop=284; nRight=168; nBottom=352; break;
    case 32: nLeft=175; nTop=284; nRight=243; nBottom=352; break;
    case 33: nLeft=249; nTop=284; nRight=317; nBottom=352; break;
    case 34: nLeft=324; nTop=284; nRight=392; nBottom=352; break;
    case 35: nLeft=400; nTop=284; nRight=468; nBottom=352; break;
    case 36: nLeft=475; nTop=284; nRight=543; nBottom=352; break;
    case 37: nLeft=550; nTop=284; nRight=618; nBottom=352; break;
    case 38: nLeft=624; nTop=284; nRight=692; nBottom=352; break;
    case 39: nLeft=700; nTop=284; nRight=768; nBottom=352; break;
    case 40: nLeft=24; nTop=360; nRight=91; nBottom=428; break;
    case 41: nLeft=100; nTop=360; nRight=168; nBottom=428; break;
    case 42: nLeft=175; nTop=360; nRight=243; nBottom=428; break;
    case 43: nLeft=249; nTop=360; nRight=317; nBottom=428; break;
    case 44: nLeft=324; nTop=360; nRight=392; nBottom=428; break;
    case 45: nLeft=400; nTop=360; nRight=468; nBottom=428; break;
    case 46: nLeft=475; nTop=360; nRight=543; nBottom=428; break;
    case 47: nLeft=550; nTop=360; nRight=618; nBottom=428; break;
    case 48: nLeft=624; nTop=360; nRight=692; nBottom=428; break;
    case 49: nLeft=700; nTop=360; nRight=768; nBottom=428; break;
    case 50: nLeft=24; nTop=435; nRight=91; nBottom=503; break;
    case 51: nLeft=100; nTop=435; nRight=168; nBottom=503; break;
    case 52: nLeft=175; nTop=435; nRight=243; nBottom=503; break;
    case 53: nLeft=249; nTop=435; nRight=317; nBottom=503; break;
    case 54: nLeft=324; nTop=435; nRight=392; nBottom=503; break;
    case 55: nLeft=400; nTop=435; nRight=468; nBottom=503; break;
    case 56: nLeft=475; nTop=435; nRight=543; nBottom=503; break;
    case 57: nLeft=550; nTop=435; nRight=618; nBottom=503; break;
    case 58: nLeft=624; nTop=435; nRight=692; nBottom=503; break;
    case 59: nLeft=700; nTop=435; nRight=768; nBottom=503; break;
	}

	rLeft = nLeft;
	rTop = nTop;
	rRight = nRight;
	rBottom = nBottom;
	return true;
}

void procItemClick()
{

	int iComIdx = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "SAVEIMG1" ) { SelectItemImage( g_nFirstItemIndex + 0 ); return; }
	if( sNodName == "SAVEIMG2" ) { SelectItemImage( g_nFirstItemIndex + 1 ); return; }
	if( sNodName == "SAVEIMG3" ) { SelectItemImage( g_nFirstItemIndex + 2 ); return; }
	if( sNodName == "SAVEIMG4" ) { SelectItemImage( g_nFirstItemIndex + 3 ); return; }
	if( sNodName == "SAVEIMG5" ) { SelectItemImage( g_nFirstItemIndex + 4 ); return; }
	if( sNodName == "SAVEIMG6" ) { SelectItemImage( g_nFirstItemIndex + 5 ); return; }
	if( sNodName == "SAVEIMG7" ) { SelectItemImage( g_nFirstItemIndex + 6 ); return; }
	if( sNodName == "SAVEIMG8" ) { SelectItemImage( g_nFirstItemIndex + 7 ); return; }
	if( sNodName == "SAVEIMG9" ) { SelectItemImage( g_nFirstItemIndex + 8 ); return; }
	if( sNodName == "SAVEIMG10" ) { SelectItemImage( g_nFirstItemIndex + 9 ); return; }

	if( sNodName == "SAVEIMG11" ) { SelectItemImage( g_nFirstItemIndex + 10 ); return; }
	if( sNodName == "SAVEIMG12" ) { SelectItemImage( g_nFirstItemIndex + 11 ); return; }
	if( sNodName == "SAVEIMG13" ) { SelectItemImage( g_nFirstItemIndex + 12 ); return; }
	if( sNodName == "SAVEIMG14" ) { SelectItemImage( g_nFirstItemIndex + 13 ); return; }
	if( sNodName == "SAVEIMG15" ) { SelectItemImage( g_nFirstItemIndex + 14 ); return; }
	if( sNodName == "SAVEIMG16" ) { SelectItemImage( g_nFirstItemIndex + 15 ); return; }
	if( sNodName == "SAVEIMG17" ) { SelectItemImage( g_nFirstItemIndex + 16 ); return; }
	if( sNodName == "SAVEIMG18" ) { SelectItemImage( g_nFirstItemIndex + 17 ); return; }
	if( sNodName == "SAVEIMG19" ) { SelectItemImage( g_nFirstItemIndex + 18 ); return; }
	if( sNodName == "SAVEIMG20" ) { SelectItemImage( g_nFirstItemIndex + 19 ); return; }

	if( sNodName == "SAVEIMG21" ) { SelectItemImage( g_nFirstItemIndex + 20 ); return; }
	if( sNodName == "SAVEIMG22" ) { SelectItemImage( g_nFirstItemIndex + 21 ); return; }
	if( sNodName == "SAVEIMG23" ) { SelectItemImage( g_nFirstItemIndex + 22 ); return; }
	if( sNodName == "SAVEIMG24" ) { SelectItemImage( g_nFirstItemIndex + 23 ); return; }
	if( sNodName == "SAVEIMG25" ) { SelectItemImage( g_nFirstItemIndex + 24 ); return; }
	if( sNodName == "SAVEIMG26" ) { SelectItemImage( g_nFirstItemIndex + 25 ); return; }
	if( sNodName == "SAVEIMG27" ) { SelectItemImage( g_nFirstItemIndex + 26 ); return; }
	if( sNodName == "SAVEIMG28" ) { SelectItemImage( g_nFirstItemIndex + 27 ); return; }
	if( sNodName == "SAVEIMG29" ) { SelectItemImage( g_nFirstItemIndex + 28 ); return; }
	if( sNodName == "SAVEIMG30" ) { SelectItemImage( g_nFirstItemIndex + 29 ); return; }

	if( sNodName == "SAVEIMG31" ) { SelectItemImage( g_nFirstItemIndex + 30 ); return; }
	if( sNodName == "SAVEIMG32" ) { SelectItemImage( g_nFirstItemIndex + 31 ); return; }
	if( sNodName == "SAVEIMG33" ) { SelectItemImage( g_nFirstItemIndex + 32 ); return; }
	if( sNodName == "SAVEIMG34" ) { SelectItemImage( g_nFirstItemIndex + 33 ); return; }
	if( sNodName == "SAVEIMG35" ) { SelectItemImage( g_nFirstItemIndex + 34 ); return; }
	if( sNodName == "SAVEIMG36" ) { SelectItemImage( g_nFirstItemIndex + 35 ); return; }
	if( sNodName == "SAVEIMG37" ) { SelectItemImage( g_nFirstItemIndex + 36 ); return; }
	if( sNodName == "SAVEIMG38" ) { SelectItemImage( g_nFirstItemIndex + 37 ); return; }
	if( sNodName == "SAVEIMG39" ) { SelectItemImage( g_nFirstItemIndex + 38 ); return; }
	if( sNodName == "SAVEIMG40" ) { SelectItemImage( g_nFirstItemIndex + 39 ); return; }

	if( sNodName == "SAVEIMG41" ) { SelectItemImage( g_nFirstItemIndex + 40 ); return; }
	if( sNodName == "SAVEIMG42" ) { SelectItemImage( g_nFirstItemIndex + 41 ); return; }
	if( sNodName == "SAVEIMG43" ) { SelectItemImage( g_nFirstItemIndex + 42 ); return; }
	if( sNodName == "SAVEIMG44" ) { SelectItemImage( g_nFirstItemIndex + 43 ); return; }
	if( sNodName == "SAVEIMG45" ) { SelectItemImage( g_nFirstItemIndex + 44 ); return; }
	if( sNodName == "SAVEIMG46" ) { SelectItemImage( g_nFirstItemIndex + 45 ); return; }
	if( sNodName == "SAVEIMG47" ) { SelectItemImage( g_nFirstItemIndex + 46 ); return; }
	if( sNodName == "SAVEIMG48" ) { SelectItemImage( g_nFirstItemIndex + 47 ); return; }
	if( sNodName == "SAVEIMG49" ) { SelectItemImage( g_nFirstItemIndex + 48 ); return; }
	if( sNodName == "SAVEIMG50" ) { SelectItemImage( g_nFirstItemIndex + 49 ); return; }

	if( sNodName == "SAVEIMG51" ) { SelectItemImage( g_nFirstItemIndex + 50 ); return; }
	if( sNodName == "SAVEIMG52" ) { SelectItemImage( g_nFirstItemIndex + 51 ); return; }
	if( sNodName == "SAVEIMG53" ) { SelectItemImage( g_nFirstItemIndex + 52 ); return; }
	if( sNodName == "SAVEIMG54" ) { SelectItemImage( g_nFirstItemIndex + 53 ); return; }
	if( sNodName == "SAVEIMG55" ) { SelectItemImage( g_nFirstItemIndex + 54 ); return; }
	if( sNodName == "SAVEIMG56" ) { SelectItemImage( g_nFirstItemIndex + 55 ); return; }
	if( sNodName == "SAVEIMG57" ) { SelectItemImage( g_nFirstItemIndex + 56 ); return; }
	if( sNodName == "SAVEIMG58" ) { SelectItemImage( g_nFirstItemIndex + 57 ); return; }
	if( sNodName == "SAVEIMG59" ) { SelectItemImage( g_nFirstItemIndex + 58 ); return; }
	if( sNodName == "SAVEIMG60" ) { SelectItemImage( g_nFirstItemIndex + 59 ); return; }
}

void SelectItemImage( int nItemIndex )
{
	int nLeft,nTop,nRight,nBottom;
	bool bMakeMove = GetMoveToOtherItem( nItemIndex, &nLeft,&nTop,&nRight,&nBottom );
	if( bMakeMove ) {
		SendMessage( &GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE,"ITEM_SELECTER",0, nLeft,nTop,nRight,nBottom );
	}
	SetCurrentNode( "ITEM_SELECTER" );
}

void FillItemList(int nFirstItemIndex)
{
	if( nFirstItemIndex<0 ) nFirstItemIndex = 0;
	nFirstItemIndex = nFirstItemIndex / FLAG_IMAGE_LIST_PERLINE;
	nFirstItemIndex = nFirstItemIndex * FLAG_IMAGE_LIST_PERLINE;

	bool bNoRebuildSaveList = (g_nFirstItemIndex>=0);
	int nDelta = nFirstItemIndex - g_nFirstItemIndex;
	g_nFirstItemIndex = nFirstItemIndex;

	if( bNoRebuildSaveList && (nDelta==FLAG_IMAGE_LIST_PERLINE) ) {
		MoveItemLine(1,0);
		MoveItemLine(2,1);
		MoveItemLine(3,2);
		MoveItemLine(4,3);
		MoveItemLine(5,4);
		FillItemLine(5,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE*5);
		return;
	}
	if( bNoRebuildSaveList && (nDelta==-FLAG_IMAGE_LIST_PERLINE) ) {
	    MoveItemLine(4,5);
	    MoveItemLine(3,4);
	    MoveItemLine(2,3);
	    MoveItemLine(1,2);
		MoveItemLine(0,1);
		FillItemLine(0,nFirstItemIndex);
		return;
	}
	FillItemLine(0,nFirstItemIndex);
	FillItemLine(1,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE);
	FillItemLine(2,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE*2);
	FillItemLine(3,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE*3);
	FillItemLine(4,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE*4);
	FillItemLine(5,nFirstItemIndex+FLAG_IMAGE_LIST_PERLINE*5);
}

void FillItemLine(int nLine, int nBegIndex)
{
	int nBeg = nLine * FLAG_IMAGE_LIST_PERLINE;
	int i,n;
	string attr;

	for(i=0; i<FLAG_IMAGE_LIST_PERLINE; i++) {
		n = nBegIndex + i;
		attr = "s" + n;
		if( CheckAttribute(&g_oItemContainer,attr) ) {
			LoadInfo(nBeg+i, n, g_oItemContainer.(attr).savename);
		} else {
			FillEmptyItemSlot(nBeg+i);
		}
	}
}

void FillEmptyItemSlot(int nSlot)
{
	ClearItemInfoByIndex( nSlot );
	g_oItemList[nSlot].saveidx = -1;
	g_oItemList[nSlot].savefile = "";
	g_oItemList[nSlot].loaded = 1;
	ShowDataForItem(nSlot,"empty","");
}

void ShowDataForItem(int nSlot, string picname, string picpointer)
{
    string nodname = "SAVEIMG" + (nSlot+1);
	bool bClickable = false;
	if( picname!="" ) {
		if( picname == "empty" ) {
			SendMessage( &GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, nodname, 2, 0,"interfaces\SaveIcons\SaveEmpty.tga.tx" );
		}
		if( picname == "loading" ) {
			SendMessage( &GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, nodname, 2, 0,"interfaces\SaveIcons\SaveLoading.tga.tx" );
		}
	}
	if( picpointer!="" ) {
		SetNewGroupPicture(nodname, g_oItemContainer.picTexture, picpointer);
		bClickable = true;
	}
	SetSelectable( nodname, bClickable );
}

void MoveItemLine(int nSrcLine, int nDstLine)
{
	int nSrc = nSrcLine * FLAG_IMAGE_LIST_PERLINE;
	int nDst = nDstLine * FLAG_IMAGE_LIST_PERLINE;
	for( int i=0; i<FLAG_IMAGE_LIST_PERLINE; i++ )
	{
		MoveItemInfo(nSrc+i,nDst+i);
	}
}

void InitItemObjList()
{
	int i;
	for(i=0; i<FLAG_IMAGE_LIST_COUNT; i++)
	{
		g_oItemList[i].saveidx = -1;
	}
}

void ClearItemInfoByIndex(int i)
{
	if( g_oItemList[i].saveidx == -1 ) {return;}
	DeleteAttribute( &g_oItemList[i], "" );
	g_oItemList[i].saveidx = -1;
}

void MoveItemInfo(int nSrc, int nDst)
{
	CopyAttributes( &g_oItemList[nDst], &g_oItemList[nSrc] );
	DeleteAttribute( &g_oItemList[nSrc], "" );
	g_oItemList[nSrc].saveidx = -1;

	// copy info from src control to dst control
	string sDstImgNod = "SAVEIMG"+(nDst+1);
	string sSrcImgNod = "SAVEIMG"+(nSrc+1);
	SetSelectable( sDstImgNod, GetSelectable(sSrcImgNod) );
	SendMessage( &GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sDstImgNod, 8, sSrcImgNod );

	// set src control to empty
	ShowDataForItem( nSrc, "empty", "" );
}

void LoadInfo(int nInfoIdx, int nSaveIdx, string sSaveName)
{
	ClearItemInfoByIndex( nInfoIdx );
	g_oItemList[nInfoIdx].saveidx = nSaveIdx;
	g_oItemList[nInfoIdx].savefile = sSaveName;
	g_oItemList[nInfoIdx].loaded = 0;
	ShowDataForItem(nInfoIdx,"loading","");
}

void procLoadOneItemInfo()
{
	int i;

	for( i=0; i<FLAG_IMAGE_LIST_COUNT; i++ )
	{
		if( g_oItemList[i].saveidx != "-1" )
		{
			if( !CheckAttribute(&g_oItemList[i],"loaded") || g_oItemList[i].loaded=="0" )
			{
				g_oItemList[i].loaded = 1;
				ShowDataForItem(i,"", g_oItemList[i].savefile);
				break;
			}
		}
	}
	PostEvent( "evLoadOneItemInfo",FLAGIMAGE_UPDATE_TIME );
}

void ProcessSelectedFlag()
{
    if(g_nCurrentItemIndex > -1 && g_nCurrentItemIndex < FLAG_TEXTURES_COUNT) {
        pchar.persFlag = g_nCurrentItemIndex;
        if(bReplaceAllFlags)
            pchar.persFlag.replaceAll = true;
        else
            DeleteAttribute(pchar, "persFlag.replaceAll");
        if(bApplySquad)
            pchar.persFlag.applySquad = true;
        else
            DeleteAttribute(pchar, "persFlag.applySquad");
        for(int i=0; i<COMPANION_MAX; i++)
        {
            int chrIdx = GetCompanionIndex(pchar,i);
            if(chrIdx > -1)
            {
               Ship_FlagRefresh(&characters[chrIdx]);
            }
        }
    }
	IDoExit(RC_INTERFACE_TO_SHIP);
}

void ProcessRemovedFlag()
{
    if(DeleteAttribute(pchar, "persFlag")) {
        Ship_FlagRefresh(&characters[nMainCharacterIndex]);
    }
	IDoExit(RC_INTERFACE_TO_SHIP);
}

void DoConfirm( int nConfirmMode )
{
	g_sConfirmReturnWindow = "MAIN_WINDOW";
	XI_WindowDisable( g_sConfirmReturnWindow, true );
	// enable confirm window
	XI_WindowDisable( "CONFIRM_WINDOW", false );
	XI_WindowShow( "CONFIRM_WINDOW", true );
	SetCurrentNode( "CONFIRM_YES" );

	g_nConfirmMode = nConfirmMode;
	switch( nConfirmMode )
	{
	case CONFIRMMODE_FLAG_DELETE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete persflag confirm") );
		break;
	case CONFIRMMODE_FLAG_SELECT:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Confirm personal flag") );
		break;
	}
	SetNewGroupPicture("CONFIRM_CURRENT_FLAG", PERS_FLAG_PICTURES_GROUP, "flg" + g_nCurrentItemIndex);
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5 );
}

void procConfirm()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( iComIndex==ACTION_ACTIVATE || iComIndex==ACTION_MOUSECLICK ) {
		if( sNodName=="CONFIRM_YES" ) {
			UndoConfirm(true);
		} else {
			UndoConfirm(false);
		}
	}
	if( iComIndex==ACTION_DEACTIVATE ) {
		UndoConfirm(false);
	}
}

void UndoConfirm(bool bPositiveChoose)
{
	// disable confirm
	XI_WindowDisable( "CONFIRM_WINDOW", true );
	XI_WindowShow( "CONFIRM_WINDOW", false );
	// enable window where confirm was started
	XI_WindowDisable( g_sConfirmReturnWindow, false );

	int nTmp = g_nConfirmMode;
	if( bPositiveChoose ) {
		switch( nTmp )
		{
		case CONFIRMMODE_FLAG_DELETE: ProcessRemovedFlag(); break;
		case CONFIRMMODE_FLAG_SELECT: ProcessSelectedFlag(); break;
		}
	}
	switch( nTmp )
	{
	case CONFIRMMODE_FLAG_DELETE:
		if(GetSelectable("BTN_DELETE")) {SetCurrentNode("BTN_DELETE");}
		else {SetCurrentNode("ITEM_SELECTER");}
	break;
	case CONFIRMMODE_FLAG_SELECT: SetCurrentNode("BTN_SETFLAG"); break;
	}
}

void ScrollPosChange()
{
	float fPos = GetEventData();
	string sNod = GetEventData();
	if( sNod == "ITEMSCROLL" ) {
		if( g_nCurrentItemIndex>=0 ) {
			int nOldIdx = g_nCurrentItemIndex - g_nFirstItemIndex;
			SetSelecting(nOldIdx,false);
		}
		int nLineQ = g_nItemQuantity / FLAG_IMAGE_LIST_PERLINE;
		int nLine = makeint( makefloat(nLineQ) * fPos );
		FillItemList(nLine * FLAG_IMAGE_LIST_PERLINE);
		SetSelecting(0,true);
		SelectItemImage(g_nFirstItemIndex);
	}
}

void ItemLoad()
{
	int iComIdx = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "SAVEIMG1" ) { SelectItemImage( g_nFirstItemIndex + 0 ) }
	if( sNodName == "SAVEIMG2" ) { SelectItemImage( g_nFirstItemIndex + 1 ) }
	if( sNodName == "SAVEIMG3" ) { SelectItemImage( g_nFirstItemIndex + 2 ) }
	if( sNodName == "SAVEIMG4" ) { SelectItemImage( g_nFirstItemIndex + 3 ) }
	if( sNodName == "SAVEIMG5" ) { SelectItemImage( g_nFirstItemIndex + 4 ) }
	if( sNodName == "SAVEIMG6" ) { SelectItemImage( g_nFirstItemIndex + 5 ) }
	if( sNodName == "SAVEIMG7" ) { SelectItemImage( g_nFirstItemIndex + 6 ) }
	if( sNodName == "SAVEIMG8" ) { SelectItemImage( g_nFirstItemIndex + 7 ) }
	if( sNodName == "SAVEIMG9" ) { SelectItemImage( g_nFirstItemIndex + 8 ) }
	if( sNodName == "SAVEIMG10" ) { SelectItemImage( g_nFirstItemIndex + 9 ) }

	if( sNodName == "SAVEIMG11" ) { SelectItemImage( g_nFirstItemIndex + 10 ) }
	if( sNodName == "SAVEIMG12" ) { SelectItemImage( g_nFirstItemIndex + 11 ) }
	if( sNodName == "SAVEIMG13" ) { SelectItemImage( g_nFirstItemIndex + 12 ) }
	if( sNodName == "SAVEIMG14" ) { SelectItemImage( g_nFirstItemIndex + 13 ) }
	if( sNodName == "SAVEIMG15" ) { SelectItemImage( g_nFirstItemIndex + 14 ) }
	if( sNodName == "SAVEIMG16" ) { SelectItemImage( g_nFirstItemIndex + 15 ) }
	if( sNodName == "SAVEIMG17" ) { SelectItemImage( g_nFirstItemIndex + 16 ) }
	if( sNodName == "SAVEIMG18" ) { SelectItemImage( g_nFirstItemIndex + 17 ) }
	if( sNodName == "SAVEIMG19" ) { SelectItemImage( g_nFirstItemIndex + 18 ) }
	if( sNodName == "SAVEIMG20" ) { SelectItemImage( g_nFirstItemIndex + 19 ) }

	if( sNodName == "SAVEIMG21" ) { SelectItemImage( g_nFirstItemIndex + 20 ) }
	if( sNodName == "SAVEIMG22" ) { SelectItemImage( g_nFirstItemIndex + 21 ) }
	if( sNodName == "SAVEIMG23" ) { SelectItemImage( g_nFirstItemIndex + 22 ) }
	if( sNodName == "SAVEIMG24" ) { SelectItemImage( g_nFirstItemIndex + 23 ) }
	if( sNodName == "SAVEIMG25" ) { SelectItemImage( g_nFirstItemIndex + 24 ) }
	if( sNodName == "SAVEIMG26" ) { SelectItemImage( g_nFirstItemIndex + 25 ) }
	if( sNodName == "SAVEIMG27" ) { SelectItemImage( g_nFirstItemIndex + 26 ) }
	if( sNodName == "SAVEIMG28" ) { SelectItemImage( g_nFirstItemIndex + 27 ) }
	if( sNodName == "SAVEIMG29" ) { SelectItemImage( g_nFirstItemIndex + 28 ) }
	if( sNodName == "SAVEIMG30" ) { SelectItemImage( g_nFirstItemIndex + 29 ) }

	if( sNodName == "SAVEIMG31" ) { SelectItemImage( g_nFirstItemIndex + 30 ) }
	if( sNodName == "SAVEIMG32" ) { SelectItemImage( g_nFirstItemIndex + 31 ) }
	if( sNodName == "SAVEIMG33" ) { SelectItemImage( g_nFirstItemIndex + 32 ) }
	if( sNodName == "SAVEIMG34" ) { SelectItemImage( g_nFirstItemIndex + 33 ) }
	if( sNodName == "SAVEIMG35" ) { SelectItemImage( g_nFirstItemIndex + 34 ) }
	if( sNodName == "SAVEIMG36" ) { SelectItemImage( g_nFirstItemIndex + 35 ) }
	if( sNodName == "SAVEIMG37" ) { SelectItemImage( g_nFirstItemIndex + 36 ) }
	if( sNodName == "SAVEIMG38" ) { SelectItemImage( g_nFirstItemIndex + 37 ) }
	if( sNodName == "SAVEIMG39" ) { SelectItemImage( g_nFirstItemIndex + 38 ) }
	if( sNodName == "SAVEIMG40" ) { SelectItemImage( g_nFirstItemIndex + 39 ) }

	if( sNodName == "SAVEIMG41" ) { SelectItemImage( g_nFirstItemIndex + 40 ) }
	if( sNodName == "SAVEIMG42" ) { SelectItemImage( g_nFirstItemIndex + 41 ) }
	if( sNodName == "SAVEIMG43" ) { SelectItemImage( g_nFirstItemIndex + 42 ) }
	if( sNodName == "SAVEIMG44" ) { SelectItemImage( g_nFirstItemIndex + 43 ) }
	if( sNodName == "SAVEIMG45" ) { SelectItemImage( g_nFirstItemIndex + 44 ) }
	if( sNodName == "SAVEIMG46" ) { SelectItemImage( g_nFirstItemIndex + 45 ) }
	if( sNodName == "SAVEIMG47" ) { SelectItemImage( g_nFirstItemIndex + 46 ) }
	if( sNodName == "SAVEIMG48" ) { SelectItemImage( g_nFirstItemIndex + 47 ) }
	if( sNodName == "SAVEIMG49" ) { SelectItemImage( g_nFirstItemIndex + 48 ) }
	if( sNodName == "SAVEIMG50" ) { SelectItemImage( g_nFirstItemIndex + 49 ) }

	if( sNodName == "SAVEIMG51" ) { SelectItemImage( g_nFirstItemIndex + 50 ) }
	if( sNodName == "SAVEIMG52" ) { SelectItemImage( g_nFirstItemIndex + 51 ) }
	if( sNodName == "SAVEIMG53" ) { SelectItemImage( g_nFirstItemIndex + 52 ) }
	if( sNodName == "SAVEIMG54" ) { SelectItemImage( g_nFirstItemIndex + 53 ) }
	if( sNodName == "SAVEIMG55" ) { SelectItemImage( g_nFirstItemIndex + 54 ) }
	if( sNodName == "SAVEIMG56" ) { SelectItemImage( g_nFirstItemIndex + 55 ) }
	if( sNodName == "SAVEIMG57" ) { SelectItemImage( g_nFirstItemIndex + 56 ) }
	if( sNodName == "SAVEIMG58" ) { SelectItemImage( g_nFirstItemIndex + 57 ) }
	if( sNodName == "SAVEIMG59" ) { SelectItemImage( g_nFirstItemIndex + 58 ) }
	if( sNodName == "SAVEIMG60" ) { SelectItemImage( g_nFirstItemIndex + 59 ) }

	ItemSelectCurrentIntoSlot();
}
