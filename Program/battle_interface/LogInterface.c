#include "battle_interface\log_msg.h"

#define LOG_FOR_SEA			1
#define LOG_FOR_LAND		2
#define LOG_FOR_WORLDMAP	3

object showWindow;
object ILogAndActions;
object IBoardingStatus;
bool   bYesBoardStatus;
string g_ActiveActionName;

#event_handler("blieGetMsgIconRoot","BI_GetMsgIconRoot");
void InitLogInterface()
{
	SetEventHandler("SetWindowSize","LI_SetWindowSize",0);
	CreateEntity(&ILogAndActions,"ILogAndActions");
	DelEventHandler("SetWindowSize","LI_SetWindowSize");
	DeleteAttribute(&ILogAndActions,"");
	ILogAndActions.type = "";
	CreateLogEnvironment();
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_INIT,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	SetEventHandler(EVENT_LOCATION_LOAD,"LI_LocationLoad",0);
	SetEventHandler("BI_FastCommand","BI_FastCommand",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"SetLogInterfaceVisible",0);
	LayerAddObject("execute",&ILogAndActions,-257);
	LayerAddObject("realize",&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);

	InitActivePerkShower();
}

void Log_RemoveFromSingleLayers()
{
	LayerDelObject("execute",&ILogAndActions);
	LayerDelObject("realize",&ILogAndActions);
	LayerDelObject(SEA_EXECUTE,&ILogAndActions);
	LayerDelObject(SEA_REALIZE,&ILogAndActions);
}

void Log_MoveToSingleLayers()
{
	LayerAddObject("execute",&ILogAndActions,-257);
	LayerAddObject("realize",&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);
}

void LI_SetWindowSize()
{
	int w = GetEventData();
	int h = GetEventData();
	int bTVused = GetEventData();
	if(bTVused)	SetShowWindowParameters(bTVused,w,h,40,24,w-40,h-24);
	else	SetShowWindowParameters(bTVused,w,h,0,0,w,h);
}

void SetLogInterfaceVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&ILogAndActions,"ll",LI_SET_VISIBLE,visibleFlag);
}

void LI_LocationLoad()
{
	CreateILogAndActions(LOG_FOR_LAND);
}

void InitBattleInterfacesParameters()
{
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");
	bYesBoardStatus = false;
}

void CreateILogAndActions(int loadType)
{
	DeleteAttribute(&IBoardingStatus,"ActiveActions");
	if(loadType==LOG_FOR_SEA)
	{
		CreateSeaActionsEnvironment();
	}
	if(loadType==LOG_FOR_LAND)
	{
		CreateLandActionsEnvironment();
	}
	if(loadType==LOG_FOR_WORLDMAP)
	{
		CreateWorldMapActionsEnvironment();
	}
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_CHANGE,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	Log_SetActiveAction(g_ActiveActionName);
}

void Log_SetActiveAction(string actionName)
{
	if( ILogAndActions.type=="sea" && g_ActiveActionName!=actionName ) {
		// LDH 13Feb17 clear MoorName when leave moor location
		if (actionName != "Moor")
			pchar.MoorName = " ";
		RefreshBattleInterface();
	}
	g_ActiveActionName = actionName;
	// change text
	if( CheckAttribute(&ILogAndActions,"ActiveActions."+actionName+".Text") ) {
		ILogAndActions.ActiveActions.text2.text = ILogAndActions.ActiveActions.(actionName).Text;
	} else {
		ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");
	}
	SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,actionName);
}

void Log_SetStringToLog(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, false, strLog);
}

void Log_SetEternalString(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, true, strLog);
}

void CreateLogEnvironment()
{
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
	ILogAndActions.Log.width = sti(showWindow.sw)/2;
	ILogAndActions.Log.height = sti(showWindow.sh)- makeint(80 * fHtRatio);
	ILogAndActions.Log.right = sti(showWindow.right) - RecalculateHIcon(makeint(340 * fHtRatio));
	ILogAndActions.Log.up = sti(showWindow.top) + makeint(16 * fHtRatio);
	ILogAndActions.Log.font = "interface_normal";
	ILogAndActions.Log.fontscale = 1.5 * fHtRatio;
	ILogAndActions.Log.color = argb(0,255,255,255);
	ILogAndActions.Log.offsetString = makeint(24 * fHtRatio);
	ILogAndActions.Log.speed = 0.05;
	ILogAndActions.Log.color_speed = 0.02;
}

void CreateSeaActionsEnvironment()
{
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
	ILogAndActions.type = "sea";
	if(InterfaceStates.AltIntIcons) ILogAndActions.ActiveActions.TextureName = "battle_interface\List_icons_Konshud.tga";
	else ILogAndActions.ActiveActions.TextureName = "battle_interface\list_icons.tga";
	//ILogAndActions.ActiveActions.TextureName = "battle_interface\list_icons.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 8;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(296 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(32 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "interface_normal";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(272 * fHtRatio));
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));
	ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(272 * fHtRatio));
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));//RecalculateVIcon(102);
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActions.Moor.IconNum		= 29;
	ILogAndActions.ActiveActions.Moor.Text			= XI_ConvertString("for_quick_action_Moor");
	ILogAndActions.ActiveActions.Board.IconNum		= 30;
	ILogAndActions.ActiveActions.Board.Text			= XI_ConvertString("for_quick_action_Board");
	ILogAndActions.ActiveActions.LandTroops.IconNum	= 42;
	ILogAndActions.ActiveActions.LandTroops.Text	= XI_ConvertString("for_quick_action_LandTroops");
	ILogAndActions.ActiveActions.Map.IconNum		= 28;
	ILogAndActions.ActiveActions.Map.Text			= XI_ConvertString("for_quick_action_Map");
	ILogAndActions.ActiveActions.Reload.IconNum		= 48;
	ILogAndActions.ActiveActions.Reload.Text		= XI_ConvertString("for_quick_action_Reload_Sea");
	ILogAndActions.ActiveActions.Nothing.IconNum	= -1;
	ILogAndActions.ActiveActions.Nothing.Text		= XI_ConvertString("for_quick_action");
}

void CreateLandActionsEnvironment()
{
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
	ILogAndActions.type = "land";

	if(InterfaceStates.AltIntIcons) ILogAndActions.ActiveActions.TextureName = "battle_interface\LandCommands_Konshud.tga";
	else  ILogAndActions.ActiveActions.TextureName = "battle_interface\LandCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 4;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(284 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(32 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "interface_normal";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(260 * fHtRatio));
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));
	ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(260 * fHtRatio));
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));//RecalculateVIcon(102);
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActions.ToSea.IconNum		= 13;
	ILogAndActions.ActiveActions.ToSea.Text			= XI_ConvertString("for_quick_action_ToSea");
	ILogAndActions.ActiveActions.Talk.IconNum		= 17;
	ILogAndActions.ActiveActions.Talk.Text			= XI_ConvertString("for_quick_action_Talk");
	ILogAndActions.ActiveActions.Look.IconNum		= 16;
	ILogAndActions.ActiveActions.Look.Text			= XI_ConvertString("for_quick_action_Look");
	ILogAndActions.ActiveActions.Pick.IconNum		= 16;
	ILogAndActions.ActiveActions.Pick.Text			= XI_ConvertString("for_quick_action_Pick");
	ILogAndActions.ActiveActions.Action.IconNum		= 16;
	ILogAndActions.ActiveActions.Action.Text		= XI_ConvertString("for_quick_action_Action");
	ILogAndActions.ActiveActions.OpenBox.IconNum	= 16;
	ILogAndActions.ActiveActions.OpenBox.Text		= XI_ConvertString("for_quick_action_OpenBox");
	ILogAndActions.ActiveActions.Reload.IconNum		= 13;
	ILogAndActions.ActiveActions.Reload.Text		= XI_ConvertString("for_quick_action_Reload");
	ILogAndActions.ActiveActions.Closed.IconNum		= 29;
	ILogAndActions.ActiveActions.Closed.Text		= XI_ConvertString("for_quick_action_Closed");
	ILogAndActions.ActiveActions.Nothing.IconNum	= -1;
	ILogAndActions.ActiveActions.Nothing.Text		= XI_ConvertString("for_quick_action");
}

void CreateWorldMapActionsEnvironment()
{
	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
	ILogAndActions.type = "map";

	if(InterfaceStates.AltIntIcons) ILogAndActions.ActiveActions.TextureName = "battle_interface\WorldMapCommands_Konshud.tga";
	else ILogAndActions.ActiveActions.TextureName = "battle_interface\WorldMapCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 8;
	ILogAndActions.ActiveActions.vertQ = 2;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(284 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(32 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "interface_normal";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(260 * fHtRatio));
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));
	ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(260 * fHtRatio));
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(86 * fHtRatio));//RecalculateVIcon(102);
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActions.EnterToSea.IconNum	= 1;
	ILogAndActions.ActiveActions.EnterToSea.Text = XI_ConvertString("for_quick_action_EnterToSea");
	ILogAndActions.ActiveActions.EnterToIsland.IconNum = 0;
	ILogAndActions.ActiveActions.EnterToIsland.Text = XI_ConvertString("for_quick_action_EnterToIsland");
	ILogAndActions.ActiveActions.EnterToShip.IconNum = 4;
	ILogAndActions.ActiveActions.EnterToShip.Text = XI_ConvertString("for_quick_action_EnterToShip");
	ILogAndActions.ActiveActions.EnterToStorm.IconNum = 5;
	ILogAndActions.ActiveActions.EnterToStorm.Text = XI_ConvertString("for_quick_action_EnterToStorm");
	ILogAndActions.ActiveActions.EnterToAttack.IconNum = 2;
	ILogAndActions.ActiveActions.EnterToAttack.Text = XI_ConvertString("for_quick_action_EnterToAttack");
	ILogAndActions.ActiveActions.EnterToEnemy.IconNum	= 3;
	ILogAndActions.ActiveActions.EnterToEnemy.Text = XI_ConvertString("for_quick_action_EnterToEnemy");
}

void DrawCharacterHP(float myHP,float enemyHP)
{
	if(bYesBoardStatus==false)
	{
		CreateEntity(&IBoardingStatus,"IBoardingStatus");
		IBoardingStatus.myLeft = sti(showWindow.left)+16;
		IBoardingStatus.myTop = sti(showWindow.bottom)-140;
		IBoardingStatus.enemyLeft = sti(showWindow.left)+16;
		IBoardingStatus.enemyTop = sti(showWindow.bottom)-128;
		IBoardingStatus.height = RecalculateVIcon(8);
		IBoardingStatus.width = RecalculateHIcon(120);
		IBoardingStatus.myColor = argb(255,0,0,128);
		IBoardingStatus.enemyColor = argb(255,128,0,0);
		SendMessage(&IBoardingStatus,"l",LOG_INIT_CHARCTER_HP);
		bYesBoardStatus = true;
	}
	if(myHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	if(enemyHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	SendMessage(&IBoardingStatus,"lff",LOG_SET_CHARCTER_HP,myHP,enemyHP);
}

void DrawCharacterHPEx(float myHP,float enemyHP)
{
	float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
    int fTmp, fTmp2;
    
    if(bYesBoardStatus==false)
    {
        CreateEntity(&IBoardingStatus,"IBoardingStatus");
        // fTmp = makeint(29.5 * fHtRatio);
        fTmp = makeint(25.0 * fHtRatio);
        IBoardingStatus.myLeft = fTmp + "," + fTmp2;
        // fTmp = makeint(98.0 * fHtRatio);
        fTmp = makeint(86.0 * fHtRatio);
        IBoardingStatus.myTop = fTmp + "," + fTmp2;
		IBoardingStatus.enemyLeft = sti(showWindow.left)+230+73+makeint((14.0/1280.0*stf(showWindow.right)-4.0)/2.0);
		IBoardingStatus.enemyTop = -1000;
		IBoardingStatus.height = RecalculateVIcon(4)*fHtRatio;
		IBoardingStatus.width = RecalculateVIcon(121)*fHtRatio;
		IBoardingStatus.myColor = argb(255,200,200,200);
		IBoardingStatus.enemyColor = argb(255,128,0,0);
		SendMessage(&IBoardingStatus,"l",LOG_INIT_CHARCTER_HP);
		bYesBoardStatus = true;
	}
	
	if(enemyHP <=0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	
	SendMessage(&IBoardingStatus,"lff",LOG_SET_CHARCTER_HP,myHP,enemyHP);
}

void DrawCharacterHPExx(float myHP,float enemyHP)
{
	float fHtRatio = stf(Render.screen_y) / BI_COMPARE_HEIGHT;
    int fTmp, fTmp2;
    
    if(bYesBoardStatus==false)
    {
        CreateEntity(&IBoardingStatus,"IBoardingStatus");
        fTmp = makeint(29.5 * fHtRatio);
        IBoardingStatus.myLeft = fTmp + "," + fTmp2;
        fTmp = makeint(98.0 * fHtRatio);
        IBoardingStatus.myTop = fTmp + "," + fTmp2;
		IBoardingStatus.enemyLeft = sti(showWindow.left)+230+73+makeint((14.0/1280.0*stf(showWindow.right)-4.0)/2.0);
		IBoardingStatus.enemyTop = -1000;
		IBoardingStatus.height = RecalculateVIcon(4)*fHtRatio;
		IBoardingStatus.width = RecalculateVIcon(121)*fHtRatio;
		IBoardingStatus.myColor = argb(255,200,200,200);
		IBoardingStatus.enemyColor = argb(255,128,0,0);
		SendMessage(&IBoardingStatus,"l",LOG_INIT_CHARCTER_HP);
		bYesBoardStatus = true;
	}
	
	if(enemyHP <=0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	
	SendMessage(&IBoardingStatus,"lff",LOG_SET_CHARCTER_HP,myHP,enemyHP);
}

void BI_FastCommand()
{
	int tmpi;
	string FComName = GetEventData();

	if( LAi_IsDead(pchar) ) {return;}

	aref arFader;
	if( FindClass(arFader,"fader") ) {return;}

	bool bEC = false;

	if( ILogAndActions.type == "sea" )
	{
		switch(FComName)
		{
		case "Moor":		bEC = true; Sea_LandLoad(); break;
		case "Board":		bEC = true; Sea_AbordageLoad(SHIP_ABORDAGE,true); break;
		case "LandTroops":	bEC = true; Sea_AbordageLoad(FORT_ABORDAGE,true); break;
		case "Map":			bEC = true; Sea_MapLoad(); break; //  pchar.location = ""; ��� ��� �� �����
		case "Reload":
			if(bi_nReloadTarget!=-1)
			{
				bEC = true;
				LaunchTransferMain(pchar,GetCharacter(bi_nReloadTarget),"Transfer");
			}
		break;
		}
	}
	if( ILogAndActions.type == "land" )
	{
		if(CheckAttribute(pchar,"Quests.quest_act"))
		{
			Event("evntQuestComplete","s",Characters[nMainCharacterIndex].Quests.quest_act);
			return;
		}
		switch(FComName)
		{
			case "OpenBox":
				if (!LAi_IsFightMode(pchar)) // � ��� ������� �������� ���� ������� ������
				{
					bEC = true;
					OpenBoxProcedure();
				}
			break;
			case "Pick": bEC = true; Item_OnPickItem(); break;
			case "Action": bEC = true; Item_OnUseItem(); break;
			case "Talk":
				bEC = true;
				tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
				if(tmpi>=0)	{Event("dlgReady","l",tmpi);}
			break;
			case "Reload":
				bEC = true;
				if (bCabinStarted)   // boal
	            {
	                // ����������� ��� ��� ��������� - ����������
	                BOAL_ReloadToLoc(chrWaitReloadRef, chrWaitReloadLocator);
	            }
	            else
					Event("Control Activation","s","ChrAction");
			break;
			case "ToSea": bEC = true; Event("Control Activation","s","ChrAction"); break;
		}
	}
	if( ILogAndActions.type == "map" )
	{
		switch(FComName)
		{
		case "EnterToSea":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToIsland":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToShip":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToStorm":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToAttack":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToEnemy":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		}
	}

	if( bEC )
	{
		g_ActiveActionName = "";
		SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,"");
	}
}

void ClearAllLogStrings()
{
	SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
}

void BI_GetMsgIconRoot()
{
	aref arTmp;
	aref pARef[4];
	int i,idx,cn;
	idx = 0;

	if(bSeaActive && !bAbordageStarted)
	{
		for(i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&BattleInterface,"le", BI_MSG_SET_MSG_ICONS, &pARef);
	}


	else
	{
		for(i=0; i<4; i++)
		{
			cn = GetOfficersIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&objLandInterface,"le", MSG_BATTLE_LAND_SET_MSGICONS, &pARef);
	}
}
void LoadLIStates()
{
	pchar = GetMainCharacter();//�����, ����� �� ��������
	if(!CheckAttribute(pchar, "id")) return;
	int i,cn;
	ref chref;

	DeleteAttribute(pchar,"MessageIcons");
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
		cn = GetCompanionIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
	}
}
