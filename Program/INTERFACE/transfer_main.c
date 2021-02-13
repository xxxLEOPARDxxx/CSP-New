/// BOAL 01.08.06 ����� ������-������� �������
#define FOOD_BY_ENEMY_CREW 			10
#define RUM_BY_ENEMY_CREW 			20
#define MEDICAMENT_BY_ENEMY_CREW 	30
#define WEAPON_BY_ENEMY_CREW		10
#define HP_BY_ENEMY_CREW			50
#define HP_PER_BOAT					25  
int nCurScrollOfficerNum;
ref xi_refCharacter, refEnemyCharacter;
ref refCharacter;

string CurTable, CurRow;
int iSelected; // ������ � �������

// ��� �����������
int iShipQty, iUnits, iCurGoodsIdx;

int	iCrewQty = 0;
int iBackCrew = 0;
int iGetHired = 0;
string sMessageMode;
bool  bTransferMode;
bool  bSwap;
// pchar - ��, xi_refCharacter - ���� ��� ��� ���������, �� ������ �����
void InitInterface_RS(string iniName, ref _chr, string _type)
{
    bQuestCheckProcessFreeze = true;

	xi_refCharacter   = _chr;
	refEnemyCharacter = _chr; // ����������� ���
	refCharacter = pchar;
	
	if(refEnemyCharacter.id == "ShipWreck_BadPirate") 
	{
		xi_refCharacter = CharacterFromID("ShipWreck_0");
		refEnemyCharacter = xi_refCharacter;
	}	
	if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		RecalculateCargoLoad(xi_refCharacter);
		xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	if (CheckAttribute(pchar, "Ship.Cargo.RecalculateCargoLoad") && sti(pchar.Ship.Cargo.RecalculateCargoLoad))
	{
		RecalculateCargoLoad(pchar);
		pchar.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	if (_type == "Transfer")
    {
		GameInterface.title = "titleTransfer";
		bTransferMode = true;
	}
	else
	{
		DeleteAttribute(pchar, "abordage_active"); // �� �3, ���� ������ �� ���� �����
		GameInterface.title = "titleRansack";
		bTransferMode = false;
		if (_type == "") // ����� �� ����������� ����� ��������, ��� �����
		{
			if(xi_refCharacter.Id != "PiratesOnUninhabited_BadPirate" && !CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion"))
			{
				LAi_SetCurHP(xi_refCharacter, 0.0); // ����, ���� �� ����� ������ �� ���
			}
		}
		
		SetShipRemovable(xi_refCharacter, true);
		SetCharacterRemovable(xi_refCharacter, true); // ��������� ����� ����� ��������

		DeleteParticles();
		CreateParticleEntity();
	}

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitCrewWindow","ExitCrewWindow",0);
	SetEventHandler("ExitCaptureWindow","ExitCaptureWindow",0);
	SetEventHandler("ExitCaptureCrewWindow","ExitCaptureCrewWindow",0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("HireTransactionOK", "HireTransactionOK", 0);
	SetEventHandler("HireTransactionCancel", "HireTransactionCancel", 0);
	SetEventHandler("HIRE_ADD_ALL_BUTTON", "HIRE_ADD_ALL_BUTTON", 0);
	SetEventHandler("HIRE_ADD_BUTTON","HIRE_ADD_BUTTON",0);
	SetEventHandler("HIRE_REMOVE_BUTTON", "HIRE_REMOVE_BUTTON", 0);
	SetEventHandler("HIRE_REMOVE_ALL_BUTTON", "HIRE_REMOVE_ALL_BUTTON", 0);
    //////////////////
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",9,53,219,313); // tak from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 14,284,214,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 14,78,214,1, 4);

    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER2",582,53,792,313); // tak from SHIP_BIG_PICTURE2
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER2", 586,284,788,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER2", 586,78,788,1, 4);

    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 431, 214, 573, 1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 431, 85, 573, 1, 4);
    EI_CreateVLine("SHIP_BIG_PICTURE_BORDER", 431, 57, 249, 1, 4);

    EI_CreateHLine("CREW_FRAME_BORDER", 228, 435, 573, 1, 4);

    SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetNewGroupPicture("CREW_PICTURE2", "SHIP_STATE_ICONS", "Crew");

    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

    SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));

    GameInterface.TABLE_LIST.hr.td1.str = "���-��";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.8;
	GameInterface.TABLE_LIST.hr.td2.str = "���";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.8;
	GameInterface.TABLE_LIST.hr.td3.str = "������";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.8;
	GameInterface.TABLE_LIST.hr.td4.str = "���-��";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.8;
	GameInterface.TABLE_LIST.hr.td5.str = "���";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.8;
	GameInterface.TABLE_LIST.hr.td6.str = "�����/���";
	GameInterface.TABLE_LIST.hr.td6.scale = 0.8;
	GameInterface.TABLE_LIST.select = 0;
	OnShipScrollChange();
	sMessageMode = "";
	SetGoodsArrows();
	trace("xi_refCharacter.id : " + xi_refCharacter.id);
	// ��������� � �������
	if(!bTransferMode && !LAi_IsDead(xi_refCharacter) && _type != "MaryCelesteTransfer" && xi_refCharacter.Id != "ShipWreck_0" &&
		xi_refCharacter.Id != "PiratesOnUninhabited_BadPirate" && !CheckAttribute(refCharacter,"GenQuest.ShipSituation")) //�������
	{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_1"));
		iGetHired = GetEnemyHiredCrew();
		if(iGetHired > 0)
		{
			xi_refCharacter.Ship.Crew.Hire = iGetHired;
			SetBackupQty();	
			SetBackupExp();		
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_" + _type)+"\n"+XI_ConvertString("Surrendered_wishes")); 
		}
		else
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_" + _type)); 
		}	
		sMessageMode = "Surrendered_Ok";
		ShowOkMessage();
	}
	bSwap = false;
	if(!bTransferMode) 
	{ 
	int stolenShip = sti(xi_refCharacter.Ship.Type); 
	RealShips[stolenShip].Stolen = true; 
	}
}

void ProcessExitCancel()
{
	ref realShip;

	// Warship 09.07.09 ���� ������
	if(xi_refCharacter.id == "MaryCelesteCapitan")
	{
		realShip = GetRealShip(GetCharacterShipType(xi_refCharacter));
		realShip.TurnRate = 1; // �������� �������������, ����� �� ��������� ������
		IDoExit(-1);
		return;
	}

	// Warship 20.08.09 ����� "������ �� ����������"
	if(xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate")
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // ����� ���
		return;
	}
	
	if(xi_refCharacter.Id == "ShipWreck_0")
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // ����� ���	
		return;
	}
	
	// Ugeen - �������� "����� �� ��������� �������"
	if(CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion") || CheckAttribute(refCharacter,"GenQuest.ShipSituation.Epidemy"))
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // ����� ���
		return;		
	}
	if (sMessageMode == "CREW_WINDOW")
	{
		ExitCrewWindow();
		return;
	}
	if (!isCompanion(xi_refCharacter))
	{ // �� ��� �������, ����� �����, �� ������ �������
		if (LAi_IsDead(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_exit_1")); // ������� ������� ��� ��������. �������� ���?
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "ShipDeadAsk";
			ShowShipChangeMenu();
		}
		else
		{//������� ���, ����� ���
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_2"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_exit_2")); // ��������� ������ � ��������� ���������� �������� � ��� ������?
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "ShipGoFreeAsk";
			ShowShipChangeMenu();
		}
	}
	else
	{  // ��� ���������, ������� ���, ��� ��
	    if (bSwap) SeaAI_SwapShipAfterAbordage(pchar, refEnemyCharacter);
	    if (xi_refCharacter.id != refEnemyCharacter.id) // ����� ����������
	    {
			SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter); // to_do ������ ���� ��� �� �������� ����� ���� ���� �� ������������ ������ � ����
			//DeleteAttribute(xi_refCharacter, "ship"); // ���� �������
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;  // ���� ��� ��� ������, �� �� ��� �������� �����
			
			// ��� ���������, �� �� == 0 �����, � ��� ������, ����� ��� ��� �������� refEnemyCharacter.LifeDay = 0; // ������� ��� ������, ���� ��� ��� �� ������� �������
		    refEnemyCharacter.location = "none"; 
		    
			if (bSeaActive)
			{
				if (!bTransferMode)
				{
					PostEvent("evntQuestsCheck", 400);
					ShipTaken(sti(refEnemyCharacter.index), KILL_BY_ABORDAGE, sti(pchar.index));
					UpdateRelations();
					RefreshBattleInterface();
				}
			}
			//DeleteAttribute(refEnemyCharacter,"ship");
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;
			ClearShipTypeForPassenger();
		}
		if (bTransferMode)
		{
			IDoExit(RC_INTERFACE_ANY_EXIT);
		}
		else
		{
			IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
		}
	}
}

void IDoExit(int exitCode)
{

	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitCrewWindow","ExitCrewWindow");
	DelEventHandler("ExitCaptureWindow","ExitCaptureWindow");
	DelEventHandler("ExitCaptureCrewWindow","ExitCaptureCrewWindow");
	
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	
	DelEventHandler("HireTransactionOK", "HireTransactionOK");
	DelEventHandler("HireTransactionCancel", "HireTransactionCancel");
	DelEventHandler("HIRE_ADD_ALL_BUTTON", "HIRE_ADD_ALL_BUTTON");
	DelEventHandler("HIRE_ADD_BUTTON","HIRE_ADD_BUTTON");
	DelEventHandler("HIRE_REMOVE_BUTTON", "HIRE_REMOVE_BUTTON");
	DelEventHandler("HIRE_REMOVE_ALL_BUTTON", "HIRE_REMOVE_ALL_BUTTON");
	UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
    DoQuestCheckDelay("NationUpdate", 1.5);

	PostEvent("StopQuestCheckProcessFreeze", 100);

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
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "REMOVE_OK":
			if(comName=="click" || comName=="activate")
			{
				if(sMessageMode == "Surrendered_Ok") { ShowCrewCaptureHire(); }
			}
		break;
		case "CAPTURE_CAPTAIN_PRISON":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyToPrisoner();
			}
		break;

		case "CAPTURE_CAPTAIN_KILL":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyToKilled();
			}
		break;

		case "CAPTURE_CREW_PRISON":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToPrisoner();
			}
		break;

		case "CAPTURE_CREW_KILL":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToKilled();
			}
		break;

		case "CAPTURE_CREW_FREE":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToFree();
			}
		break;
		case "EXIT_BTN":
			if (comName=="click")
			{
				ExitCrewWindow();
			}
		break;

		case "CREW_RIGHT":
			if (comName=="click")
			{
				GiveCrew(1);
			}
			if (comName=="rclick")
			{
				GiveCrew(10);
			}
		break;

		case "CREW_LEFT":
	        if (comName=="click")
			{
				TakeCrew(1);
			}
			if (comName=="rclick")
			{
				TakeCrew(10);
			}
		break;

		case "CREW_Win_fix":
			if(comName=="leftstep")
			{
				TakeCrew(1);
			}
			if(comName=="rightstep")
			{
				GiveCrew(1);
			}
			if(comName=="speedleft")
			{
				TakeCrew(9000); // ����� �����
			}
			if(comName=="speedright")
			{
				GiveCrew(9000); // ����� �����
			}
		break;

		case "B_RIGHT":
			if (comName=="click")
			{
				GiveGoods(1);
			}
			if (comName=="rclick")
			{
				GiveGoods(10);
			}
		break;

		case "B_LEFT":
	        if (comName=="click")
			{
				TakeGoods(1);
			}
			if (comName=="rclick")
			{
				TakeGoods(10);
			}
		break;

		case "TABLE_LIST":
			if(comName=="leftstep")
			{
				TakeGoods(1);
			}
			if(comName=="rightstep")
			{
				GiveGoods(1);
			}
			if(comName=="speedleft")
			{
				TakeGoods(9000000); // ����� �����
			}
			if(comName=="speedright")
			{
				GiveGoods(9000000); // ����� �����
			}
		break;
		////////////////
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

		case "TABLE_OTHER":
			if(comName=="click")
			{
			    ShowShipFoodInfo(pchar);
			}
		break;

		case "TABLE_OTHER2":
			if(comName=="click")
			{
			    ShowShipFoodInfo(xi_refCharacter);
			}
		break;

		case "SWAP_BUTTON":
			if(comName=="click" || comName=="activate")
			{
			    SwapProcess();
			}
		break;

		case "CAPTAN_BUTTON":
			if(comName=="click" || comName=="activate")
			{
				ExitCrewWindow(); // ��� ������������
				ShipChangeCaptan();
			}
		break;

		case "TAKE_GOODS":
			if(comName=="click" || comName=="activate")
			{
				TakeAllGoods();
			}
		break;
/*��������� � ������ ������ �����*/
		case "CANNONS_REMOVE_ALL":
			//if(comName=="click")//�� ���� � ��� �������, �� ����� ��� ���� ���. �����, ��� ��� ��� �����������, ��� ����� ���������� � ���������� ��� ���������� ���������
			if(comName=="click" || comName=="activate")
			{
			    CanonsRemoveAll();   
			}
		break;
/*��������� � ������ ������ �����*/		
		case "CREW_BUTTON":
			if(comName=="click" || comName=="activate")
			{
				ShowCrewWindow();
			}
		break;
		
		case "HIRE_QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
	            HIRE_ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            HIRE_REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		HIRE_ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            HIRE_REMOVE_ALL_BUTTON();
			}
		break;

		case "HIRE_QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
	            HIRE_ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            HIRE_REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		HIRE_ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            HIRE_REMOVE_ALL_BUTTON();
			}
		break;	
	}		
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();
	if (sNode == "PASSENGERSLIST" && sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if (sNode != "TABLE_LIST")
	{
		SetNodeUsing("B_RIGHT",  false);
		SetNodeUsing("B_LEFT", false);
	}
}
void OnShipScrollChange()
{
	ShowShipInfo(pchar, "");
	ShowShipInfo(xi_refCharacter, "2");
	ShowShipFoodInfo(pchar);
	FillGoodsTable();
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	if (isCompanion(xi_refCharacter))
	{ // ��� �������

		SetNodeUsing("MAIN_CHARACTER_PICTURE2", true);
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Remove Captain"));
		if (GetRemovable(xi_refCharacter))
		{ // ����� � ����������
		    if (GetShipRemovable(xi_refCharacter))
		    {
				SetSelectable("CAPTAN_BUTTON", true);
				SetSelectable("SWAP_BUTTON", true);
				SetSelectable("CANNONS_REMOVE_ALL", true);
			}
			else
			{
			    SetSelectable("CAPTAN_BUTTON", false);
				SetSelectable("SWAP_BUTTON", false);
				SetSelectable("CANNONS_REMOVE_ALL", false);
			}
			SetSelectable("CREW_BUTTON", true);
			SetSelectable("TAKE_GOODS", true);
		}
		else
		{
			SetSelectable("CAPTAN_BUTTON", false);
			SetSelectable("SWAP_BUTTON", false);
			SetSelectable("CREW_BUTTON", false);
			SetSelectable("TAKE_GOODS", false);
		}
	}
	else
	{  // �� ���, ������ ���� ��� ������
		// Warship 09.07.09 ���� ������ � (20.08.09) ����� "������ �� ����������"
		if(xi_refCharacter.id == "MaryCelesteCapitan" || xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate" || CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion") || xi_refCharacter.Id == "ShipWreck_0")
		{
			SetSelectable("CAPTAN_BUTTON", false);
			SetSelectable("SWAP_BUTTON", false);
			SetSelectable("CREW_BUTTON", false);
		}
		else
		{
		if (LAi_IsDead(xi_refCharacter))
		{
			SetNodeUsing("MAIN_CHARACTER_PICTURE2", false); // ������ ���
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Set Captain"));
			SetSelectable("SWAP_BUTTON", true);
		}
		else
		{
			SetNodeUsing("MAIN_CHARACTER_PICTURE2", true); // ����� ����
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Remove Captain"));
			SetSelectable("SWAP_BUTTON", false);
		}
		}
	}
}

void ShowShipInfo(ref chr, string sAdd)
{
	SetNewPicture("MAIN_CHARACTER_PICTURE" + sAdd, "interfaces\portraits\128\face_" + chr.FaceId + ".tga");

	int iShip = sti(chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE" + sAdd, "interfaces\ships\" + sShip + ".tga.tx");

		SetFormatedText("SHIP_NAME" + sAdd, chr.ship.name);
		SetFormatedText("SHIP_TYPE" + sAdd, XI_ConvertString(refBaseShip.BaseName));
		SetFormatedText("SHIP_RANK" + sAdd, refBaseShip.Class);
		SetShipOTHERTable("TABLE_OTHER" + sAdd, chr);
	}
}

void ShowShipFoodInfo(ref chr)
{
	SetFormatedText("FOOD", chr.ship.name);
	// ��� -->
	// �� ����� �������
	SetFoodShipInfo(chr, "FOOD_SHIP");
	// ��� <--
	SetFormatedText("MONEY_SHIP", "");

	if (GetRemovable(chr) && isCompanion(chr)) // ������� ������ �����, � �� ����� �������������� �������!!!
	{
	    // ��� ������� ������� ��������� ����� � ������� ��������
	    SetFormatedText("MONEY_SHIP", "���������� �������: " + NewStr() + FindRussianMoneyString(GetSalaryForShip(chr)));
	}
}
void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem, iCharacter;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName, sCharacter;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;
	ref Cannon;
	ref chr;
	bool  bShowHint = true;
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
		    iShip = sti(pchar.ship.type);
		    refBaseShip = GetRealShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
		break;

		case "SHIP_BIG_PICTURE2":
		    iShip = sti(xi_refCharacter.ship.type);
		    refBaseShip = GetRealShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
		break;

		case "MAIN_CHARACTER_PICTURE":
			// ��������� �����
			bShowHint = false;
			ShowRPGHint();
		break;

		case "MAIN_CHARACTER_PICTURE2":
			// ��������� �����
			bShowHint = false;
			ShowRPGHint2();
		break;

		case "TABLE_LIST":
			sHeader = XI_Convertstring("Goods");
			sText1  = GetRPGText("GoodsCargo_hint");
			sText2  = GetConvertStr("TakeAllGoods_hint", "ShipsDescribe.txt");
			sText3  = GetConvertStr("GoodsKeys_hint", "ShipsDescribe.txt");
		break;

		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(pchar.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	Cannon = GetCannonByType(sti(pchar.Ship.Cannons.Type));
		    	sText2 = "���: " + XI_ConvertString(GetCannonType(sti(pchar.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "������: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(pchar.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "���������: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "����: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "�����������: "  + sti(GetCannonReloadTime(Cannon)) + " ���.";
		    	sText2 = sText2 + NewStr() + "���: "  + sti(Cannon.Weight) + " �.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(pchar.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(pchar.Ship.Cannons.Type));
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "������� ����� ���� ������ ������������, �� ��� �������� �������� � ������� ����� �� ������� ���������� ��������, ��� ������ ���������� ������� ������. � ������� ����� ����� �� ���� �� 25% ������ ��������."; 
				sText2 = sText2 + NewStr() + "������������ ���������� ������� � ������ ���������: " + GetMaxCrewQuantity(pchar);
			}
			// ������� �������
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(pchar), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(pchar), 1) + " %";
			}
			// ����
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "������: " + FloatToString((stf(GetCargoLoad(pchar))  /  stf(GetCargoMaxSpace(pchar))) * 100.0, 1)+ " %";
			}
		break;

		case "TABLE_OTHER2":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(xi_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	Cannon = GetCannonByType(sti(xi_refCharacter.Ship.Cannons.Type));
		    	sText2 = "���: " + XI_ConvertString(GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "������: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "���������: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "����: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "�����������: "  + sti(GetCannonReloadTime(Cannon)) + " ���.";
		    	sText2 = sText2 + NewStr() + "���: "  + sti(Cannon.Weight) + " �.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type));
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "������� ����� ���� ������ ������������, �� ��� �������� �������� � ������� ����� �� ������� ���������� ��������, ��� ������ ���������� ������� ������. � ������� ����� ����� �� ���� �� 25% ������ ��������."; 
				sText2 = sText2 + NewStr() + "������������ ���������� ������� � ������ ���������: " + GetMaxCrewQuantity(xi_refCharacter);
			}
			// ������� �������
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(xi_refCharacter), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(xi_refCharacter), 1) + " %";
			}
			// ����
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "������: " + FloatToString((stf(GetCargoLoad(xi_refCharacter))  /  stf(GetCargoMaxSpace(xi_refCharacter))) * 100.0, 1)+ " %";
			}
		break;
		case "CREW_Win_fix":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break;
		case "HIRE_TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 
		case "HIRE_TABLE_CREW2":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 
		
		case "PASSENGERSLIST":
			nChooseNum = SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"PASSENGERSLIST", 2 );
			sAttributeName = "pic" + (nChooseNum+1);
			if(CheckAttribute(GameInterface, "PASSENGERSLIST." + sAttributeName))
			{
				if(CheckAttribute(GameInterface, "PASSENGERSLIST." + sAttributeName + ".character"))
				{
					sCharacter = GameInterface.PASSENGERSLIST.(sAttributeName).character;
					sHeader = XI_ConvertString("OfficerJob");
					sText1 = GetOfficerPosition(sCharacter);
				}
			}
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_OTHER");
    NullSelectTable("TABLE_OTHER2");
    NullSelectTable("TABLE_CREW");
    SetGoodsArrows();
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

void ShowRPGHint()
{
	SetSPECIALMiniTable("TABLE_SMALLSKILL2", pchar);
    SetOTHERMiniTable("TABLE_SMALLOTHER2", pchar);
    SetFormatedText("RPG_NAME", GetFullName(pchar));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void ShowRPGHint2()
{
	SetSPECIALMiniTable("TABLE_SMALLSKILL2", xi_refCharacter);
    SetOTHERMiniTable("TABLE_SMALLOTHER2", xi_refCharacter);
    SetFormatedText("RPG_NAME", GetFullName(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void FillGoodsTable()
{
	int n, i, qty2, qty1;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	Table_Clear("TABLE_LIST", false, true, false);
	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
	}
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		qty1 = GetCargoGoods(pchar, i);
		qty2 = GetCargoGoods(xi_refCharacter, i);
		if (qty2 <= 0 && qty1 <= 0) continue; // ������ �� ����

		GameInterface.TABLE_LIST.(row).index = i;

		GameInterface.TABLE_LIST.(row).td1.str = qty1;
		GameInterface.TABLE_LIST.(row).td1.scale = 0.81;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, qty1);
		GameInterface.TABLE_LIST.(row).td2.scale = 0.81;
		GameInterface.TABLE_LIST.(row).td4.str = qty2;
		GameInterface.TABLE_LIST.(row).td4.scale = 0.81;
		GameInterface.TABLE_LIST.(row).td5.str = GetGoodWeightByType(i, qty2);
		GameInterface.TABLE_LIST.(row).td5.scale = 0.81;
		GameInterface.TABLE_LIST.(row).td6.str = Goods[i].Units + " / " + Goods[i].Weight;
		GameInterface.TABLE_LIST.(row).td6.scale = 0.81;

        GameInterface.TABLE_LIST.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td3.icon.offset = "-2, -1";
		GameInterface.TABLE_LIST.(row).td3.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td3.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td3.textoffset = "27,0";
		GameInterface.TABLE_LIST.(row).td3.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).td3.scale = 0.85;
		n++;
	}
	Table_UpdateWindow("TABLE_LIST");
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ShowItemInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // ��� ������ ������
	{
	    ShowGoodsInfo(sti(GameInterface.(CurTable).(CurRow).index));
		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", true);
		SetCurrentNode("QTY_CANCEL_BUTTON");
	}
}

void GoodsExitCancel()
{

	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_LIST");
	// ����������� ����� ��������� �� ����
	if (iShipQty != GetCargoGoods(pchar, iCurGoodsIdx))
	{
		SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty); // ������ �������
		OnShipScrollChange();
	}
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", ����� " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	//fWeight = stf(Goods[iGoodIndex].weight);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}

    SetFormatedText("QTY_TypeOperation", "��������?");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);

	iShipQty = GetCargoGoods(pchar, iGoodIndex);
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty))
    SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iGoodIndex, iShipQty)));

    SetFormatedText("QTY_INFO_STORE_PRICE", "��� � �����");
    SetFormatedText("QTY_INFO_SHIP_PRICE",  "���������� � �����");
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);

    SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty);
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // �������� ������� � ����
		iShipQty = GetCargoGoods(pchar, iCurGoodsIdx);
	}
	ShipSituation_SetQuestSituation(ShipSituation_1);
	GoodsExitCancel();

	//SetShipOTHERTable("TABLE_OTHER", xi_refCharacter);
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	GameInterface.qty_edit.str = abs(sti(GameInterface.qty_edit.str));  // ���������� � �����

	string GoodName = goods[iCurGoodsIdx].name;

    // �������� �� ����� ��������� -->
    if (sti(GameInterface.qty_edit.str) > iShipQty)
    {
        GameInterface.qty_edit.str = iShipQty;
    }
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty - sti(GameInterface.qty_edit.str)))
	SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iCurGoodsIdx, (iShipQty - sti(GameInterface.qty_edit.str)))));
	// ����������� ����� � �����
	iWeight = sti(GameInterface.qty_edit.str);
	SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(pchar, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
	///iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
	//GameInterface.TABLE_OTHER.tr6.td3.str = (GetCargoLoad(xi_refCharacter) - iWeight) + " / " + GetCargoMaxSpace(xi_refCharacter);
	//Table_UpdateWindow("TABLE_OTHER");
}

void REMOVE_ALL_BUTTON()  // ������� ���
{
	GameInterface.qty_edit.str = iShipQty;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // ������ ���
{
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // �������
{
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // ������
{
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
	if (sti(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void DropGoodsToSeaFromInterface(int iGoodIndex, int iQuantity)
{
	ref rGood;
	string sGood;

	sGood = Goods[iGoodIndex].name;

	if (CheckAttribute(pchar, "Ship.Cargo.Goods."+sGood))
	{
		RemoveCharacterGoods(pchar, iGoodIndex, iQuantity);
		if (bSeaActive && !bAbordageStarted)  // ����, �� �� �����
		{
			iQuantity = iQuantity / sti(Goods[iGoodIndex].Units);

			int iSwimQuantity = rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4);

			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}

			RecalculateCargoLoad(pchar);

			if (CheckAttribute(&Goods[iGoodIndex], "Swim"))
			{
				float fTime = stf(Goods[iGoodIndex].Swim.Time);
				string sModel = Goods[iGoodIndex].Swim.Model;

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(pchar, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
		}
	}
}

void ShipChangeCaptan()
{
	if (isCompanion(xi_refCharacter))
	{ // ��� �������
		if (!CheckAttribute(xi_refCharacter, "Tasks.Clone")) //zagolski. ��� � ���������� � �����
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Captain"));
			SetFormatedText("REMOVE_WINDOW_TEXT", "�������� ��������?");
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "ShipChangeCaptanRemove";
			ShowShipChangeMenu();
		}
		else
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Captain"));
			SetFormatedText("REMOVE_WINDOW_TEXT", "� ������ ������ ���� ������� �� ����� ���� ������.");
			sMessageMode = "ShipChangeCaptanMessage";
			ShowOkMessage();
		}
	}
	else
	{
		// ���� �������
		if (!LAi_IsDead(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_2"));
			if (!CheckAttribute(xi_refCharacter, "Tasks.Clone")) SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_text_2"));
			else SetFormatedText("REMOVE_WINDOW_TEXT", "���� ������� � ������ ������ �� ����� ���� ����.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "SurrenderedCaptanRemove";
			ShowShipChangeMenu();
		}
		else
		{
			//Boyer add
			FlagPerkForCapturedShip(xi_refCharacter);
			/// �������� ��� ������
			if ((GetCrewQuantity(xi_refCharacter) + GetCrewQuantity(pchar)) < (GetMinCrewQuantity(xi_refCharacter) + GetMinCrewQuantity(pchar)))
			{
				SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
				SetFormatedText("REMOVE_WINDOW_TEXT", "���������� ������� �������� �� ����������� ������� ��� ����� ��������.\n ���������� �������� ����������.");
				sMessageMode = "ShipChangeCaptanMessage";
				ShowOkMessage();
			}
			else
			{
				// �������� �� 5 ��������
				if (GetCompanionQuantity(PChar) < COMPANION_MAX)
				{
					FillPassengerScroll();
				    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
				    SetCurrentNode("PASSENGERSLIST");
					ProcessFrame();
					SetOfficersSkills();

					XI_WindowShow("OFFICERS_WINDOW", true);
					XI_WindowDisable("OFFICERS_WINDOW", false);
					XI_WindowDisable("MAIN_WINDOW", true);
				}
				else
				{
				    SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
					SetFormatedText("REMOVE_WINDOW_TEXT", "� ������� ����� ����� ���� ������ ������ ��������.");
					sMessageMode = "ShipChangeCaptanMessage";
					ShowOkMessage();
				}
			}
		}
	}
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

    if (1)//sMessageMode == "ShipChangeCaptanMessage")
    {
		SetCurrentNode("CAPTAN_BUTTON");
	}
	sMessageMode = "";
}

void GoToShipChange() // ������� �� �� �������� ��-������
{
	ref     sld;
	aref    arTo, arFrom;

	switch (sMessageMode)
	{
		case "SurrenderedCaptanRemove":  // ������ ���������� ��������
			ExitShipChangeMenu();
			// ������ ������ - ��� ��� ���
			SetFormatedText("CAPTURE_TEXT", XI_ConvertString("Surrendered_captain_capture"));
			SetNewPicture("CAPTUR_PICTURE", "interfaces\portraits\128\face_" + xi_refCharacter.FaceId + ".tga");
			ShowCaptureWindow();
			SetNodeUsing("CAPTURE_CREW_KILL",  false);
			SetNodeUsing("CAPTURE_CREW_PRISON",  false);
			SetCurrentNode("CAPTURE_CANCEL");
		break;

		case "ShipChangeCaptanRemove":  // ����� ����
			sld = GetCharacter(NPC_GenerateCharacter("DeadShipCap", "off_hol_2", "man", "man", 60, sti(pchar.nation), 0, true)); // ������, �� �����
			sld.faceId = 666;
			sld.name = "";
			sld.lastname = "";
			DeleteAttribute(sld,"ship");
			sld.ship = "";
			LAi_SetCurHP(sld, 0.0); // ����

			makearef(arTo,   sld.ship);
			makearef(arFrom, xi_refCharacter.Ship);
			CopyAttributes(arTo, arFrom);

			//SeaAI_SetOfficer2ShipAfterAbordage(sld, xi_refCharacter); // to_do ������ ���� ��� �� �������� ����� ���� ���� �� ������������ ������ � ����
			// ����� �� ������
			//DeleteAttribute(xi_refCharacter,"ship"); // ���� �������
			//xi_refCharacter.ship.type = SHIP_NOTUSED;
			// ������ ���������� � ��� -->
			RemoveCharacterCompanion(pchar, xi_refCharacter);
			AddPassenger(pchar, xi_refCharacter, false);
			DelBakSkill();
			// ������ ���������� � ��� <--
			xi_refCharacter = sld;
			ExitShipChangeMenu();
			CheckQuestAboardCabinSituation(xi_refCharacter);
			OnShipScrollChange();
		break;

		case "ShipDeadAsk": // ����� � �������� �������
            if (bSwap) {
				ShipSituation_SetQuestSituation(ShipSituation_3);
				SeaAI_SwapShipAfterAbordage(pchar, refEnemyCharacter);
			}	
			if (xi_refCharacter.id != refEnemyCharacter.id) // ����� ����������
			{
				ShipSituation_SetQuestSituation(ShipSituation_2);
				SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter); // to_do ������ ���� ��� �� �������� ����� ���� ���� �� ������������ ������ � ����
			}
			// ����� �� ������
			if (bSeaActive)
			{
				if (bTransferMode)
				{
					ShipDead(sti(xi_refCharacter.index), KILL_BY_SELF, sti(pchar.index));  // ���� �� � �����
				}
				else
				{
					ShipDead(sti(xi_refCharacter.index), KILL_BY_ABORDAGE, sti(pchar.index));
				}
			}
			CheckQuestAboardCabinSituation(xi_refCharacter);
			//DeleteAttribute(refEnemyCharacter,"ship");
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;
			ClearShipTypeForPassenger();
			if (bTransferMode)
			{
				IDoExit(RC_INTERFACE_ANY_EXIT);
			}
			else
			{
				IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
			}
		break;
		
		case "ShipGoEscape":
		
		break;
		// ��������� ����
		case "ShipGoFreeAsk":
			sld = GetCharacter(NPC_GenerateCharacter(refEnemyCharacter.id + "_free", "off_hol_2", "man", "man", 60, sti(refEnemyCharacter.nation), 0, true)); // ������, �� �����
			ChangeAttributesFromCharacter(sld, refEnemyCharacter, false);
			DeleteAttribute(sld, "ship");
			sld.ship = "";

			makearef(arTo,   sld.ship);
			makearef(arFrom, refEnemyCharacter.Ship);
			CopyAttributes(arTo, arFrom);
			if(CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion")){ LAi_SetCurHP(refEnemyCharacter, 0.0); }
			sld.AlwaysFriend = true;
			sld.Abordage.Enable    = false; // ������ ��������
			// �� ������ �������� �� ������ �����
			if(xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate")
			{
				sld.Dialog.Filename = "GenQuests_Dialog.c";
				sld.greeting        = "Gr_MiddPirate";
				sld.DeckDialogNode  = "PiratesOnUninhabited_50_Deck1";
			}
			else
			{
				sld.Dialog.Filename = "Capitans_dialog.c";
				sld.greeting        = "Gr_Commander";
				sld.DeckDialogNode  = "Go_away";
			}
			xi_refCharacter = sld;
			// ������ ��������� ��� ���
			//SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter);
			SeaAI_SetCaptainFree(xi_refCharacter, refEnemyCharacter);
		    refEnemyCharacter.location = "none";

			if (bSeaActive)
			{
				if (!bTransferMode)
				{
					PostEvent("evntQuestsCheck", 400);
					ShipTakenFree(sti(refEnemyCharacter.index), KILL_BY_ABORDAGE, sti(pchar.index)); // ��� ���� �������� ���, �������� ���
					SetCharacterRelationBoth(sti(xi_refCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
					UpdateRelations();
					RefreshBattleInterface();
					CheckQuestAboardCabinSituation(xi_refCharacter);
					DoQuestCheckDelay("NationUpdate", 1.5);
				}
			}
			ClearShipTypeForPassenger();
			if (bTransferMode)
			{
				IDoExit(RC_INTERFACE_ANY_EXIT);
			}
			else
			{
				IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
			}
		break;
	}
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

    SetNodeUsing("REMOVE_OK", false);
	SetNodeUsing("REMOVE_ACCEPT_OFFICER", true);
	SetNodeUsing("REMOVE_CANCEL_OFFICER", true);

	SetCurrentNode("REMOVE_CANCEL_OFFICER");
}

void ShowOkMessage()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

    SetNodeUsing("REMOVE_OK", true);
	SetNodeUsing("REMOVE_ACCEPT_OFFICER", false);
	SetNodeUsing("REMOVE_CANCEL_OFFICER", false);

	SetCurrentNode("REMOVE_OK");
}

void ShowOtherClick()
{
	// test �� ��������  :( CreateMessageBox("sCaptionID", "sMessageID", "", "", "", "");
}

void SwapProcess()
{
	SeaAI_SwapShipsAttributes(pchar, xi_refCharacter, true);
	//if (xi_refCharacter.id == refEnemyCharacter.id)
	//{
	//	SeaAI_SwapShipAfterAbordage(pchar, xi_refCharacter);
	//}
	//#20200329-02
	if(!IsCompanion(xi_refCharacter)) {
        int nSwapCrew = GetCrewQuantity(xi_refCharacter);
        TakeCrew(nSwapCrew);
	}
	bSwap = !bSwap;
    // ����������� ������ -->
    DelBakSkill();
    // ����������� ������ <--
	OnShipScrollChange();
	ExitCrewWindow(); // ��� ������������
}

//////////////
void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CAPTAN_BUTTON");
}

void AcceptAddOfficer()
{
	string  attributeName2 = "pic"+(nCurScrollOfficerNum+1);
    ref     sld;
	aref    arTo, arFrom;
    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
        // ���������� ������ ����, ��������, ���� ��� ��� �� ���, �� ��� ���� ��� ����
        sld = GetCharacter(iChar);
		
		if(sld.id != "pet_crab")
		{
			DeleteAttribute(sld,"ship");
			sld.ship = "";

			makearef(arTo,   sld.ship);
			makearef(arFrom, xi_refCharacter.Ship);
			CopyAttributes(arTo, arFrom);
			// ������ ��������� -->
			CheckForReleaseOfficer(iChar);
			RemovePassenger(pchar, sld);
			// ������ ��������� <--
			SetCompanionIndex(pchar, -1, iChar);

			xi_refCharacter = sld;
			DelBakSkill();
		}
	}
	ExitOfficerMenu();
	// ����������� ������ -->
    DelBakSkill();
    // ����������� ������ <--
	OnShipScrollChange();
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
	        return;
        }
	}
    Table_Clear("TABLE_SMALLSKILL", false, true, true);
    Table_Clear("TABLE_SMALLOTHER", false, true, true);
    SetFormatedText("OFFICER_NAME", "");
    SetSelectable("ACCEPT_ADD_OFFICER", false);
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	int _curCharIdx;
	ref _refCurChar;
	bool  ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = nListSize;

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";
	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		_curCharIdx = GetPassenger(pchar,i);

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
				GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
				GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // �� ���� �����, �� ��� ������������� � '����'
}

void DelBakSkill()
{
	DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);
    SetEnergyToCharacter(xi_refCharacter);
    DeleteAttribute(xi_refCharacter, "TmpSkillRecall");

    DelBakSkillAttr(pchar);
    ClearCharacterExpRate(pchar);
    RefreshCharacterSkillExpRate(pchar);
    SetEnergyToCharacter(pchar);
    DeleteAttribute(pchar, "TmpSkillRecall");
}

void ClearShipTypeForPassenger()
{
	int iPassenger;

	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // ����� �������� � ���� ���� ����������� ����� ������� ���� ���� ���� ��� �� �� ����
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			characters[iPassenger].ship.type = SHIP_NOTUSED; //��������� �� ����������� �� ����� ����� �������
		}
	}
}

void TakeAllGoods()
{
	int i, j, idx, qty;
	float fMaxCost;

	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1;
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(xi_refCharacter, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight)) // ����� ���������� ������
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				}
			}
		}
		if (fMaxCost > 0)
		{
			qty = AddCharacterGoodsSimple(pchar, idx, GetCargoGoods(xi_refCharacter, idx));
			if (qty > 0)
			{
				RemoveCharacterGoodsSelf(xi_refCharacter, idx, qty);
			}
			else
			{   // ��� �����
				OnShipScrollChange();
				ShipSituation_SetQuestSituation(ShipSituation_1);
				return;
			}
		}
	}
	OnShipScrollChange();
	ShipSituation_SetQuestSituation(ShipSituation_1);
	ExitCrewWindow(); // ��� ������������
}

/*���� ��������� ������� ������ �����*/
//������� ���� �� ����������� ������ ����� �������������. �� ����� �� �������� ����� ������� � ����� ����� ��� �� �������. ���� ����� � �� �����. �� ����� �� �����������. 
void CanonsRemoveAll()
{
	SetCannonsToBort(xi_refCharacter, "fcannon", 0);
	SetCannonsToBort(xi_refCharacter, "bcannon", 0);
	SetCannonsToBort(xi_refCharacter, "rcannon", 0);
	SetCannonsToBort(xi_refCharacter, "lcannon", 0);

	OnShipScrollChange();
}


void SetCannonsToBort(ref chr, string sBort, int iQty)//��� ����� ������ iQty=0, �� ������� ��� ��� �������������
{
	int     curQty = GetBortCannonsQty(chr, sBort);
	int     maxQty = GetBortCannonsMaxQty(chr, sBort);
	int     i;
	string  attr;
	string  sBort_real;
		
	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";
	
	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));

	if (iQty < curQty)
	{// ������ �� �����
		SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // ���� �����, �� �������� ����� ����, �  AddCharacterGoodsSimple ����� ��������
	}
	// ����� ����� ����� �� ����� � ������������ ������ �� ������ (��� ��� �� ������ �� ������� �� ����, ������, ��� ������)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // �������� �� 100 ���������, �� �����, �� ��� ��
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0; // �������� �� 100 ���������, �� �����, �� ��� ��
	}

	RecalculateCargoLoad(chr);  // ��������, �� ����� �������
}
/*���� ��������� ������� ������ �����*/

void SetGoodsArrows()
{
    int  idx;
    int  iLine;
	if (CurTable == "TABLE_LIST")
	{
	    if (GetRemovable(xi_refCharacter) && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // � ������� ������
	    {
			idx = sti(GameInterface.(CurTable).(CurRow).index);
		    iLine = iSelected - 1 - sti(GameInterface.TABLE_LIST.top);
			if  (GetCargoGoods(pchar, idx) > 0 && GetGoodQuantityByWeight(idx, GetCargoFreeSpace(xi_refCharacter)) > 0)
	        {
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_RIGHT",0, 438 ,286 + 20*iLine, 458, 286 + 20 + 20*iLine, 0);
				SetNodeUsing("B_RIGHT", true);
	        }
	        else
	        {
	        	SetNodeUsing("B_RIGHT",  false);
	        }
	        if (GetCargoGoods(xi_refCharacter, idx) > 0 && GetGoodQuantityByWeight(idx, GetCargoFreeSpace(pchar)) > 0)
	        {
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_LEFT",0, 280,286 + 20*iLine,300,286 + 20 + 20*iLine, 0);
	            SetNodeUsing("B_LEFT",  true);
	        }
	        else
	        {
	        	SetNodeUsing("B_LEFT", false);
	        }
	        return;
        }
	}
	SetNodeUsing("B_RIGHT",  false);
	SetNodeUsing("B_LEFT", false);
}

void TakeGoods(int inc)
{  // ����
	int  idx;
	int  qty;

	if (!GetRemovable(xi_refCharacter)) return; // � ������� ������

	if (CurTable == "TABLE_LIST")
	{
		idx = sti(GameInterface.(CurTable).(CurRow).index);
		inc = sti(Goods[idx].Units) * inc;
		if (inc > GetCargoGoods(xi_refCharacter, idx)) inc = GetCargoGoods(xi_refCharacter, idx);
		if (inc > 0)
		{
			qty = AddCharacterGoodsSimple(pchar, idx, inc);
			if (qty > 0)
			{
				RemoveCharacterGoodsSelf(xi_refCharacter, idx, qty);
			}
			OnShipScrollChange();
			SetGoodsArrows();
			ShipSituation_SetQuestSituation(ShipSituation_1);
		}
	}	
}

void GiveGoods(int inc)
{  // �����
	int  idx;
	int  qty; 
	
	if (!GetRemovable(xi_refCharacter)) return; // � ������� ������
	
	if (CurTable == "TABLE_LIST")
	{
		idx = sti(GameInterface.(CurTable).(CurRow).index);	
		inc = sti(Goods[idx].Units) * inc;
		if (inc > GetCargoGoods(pchar, idx)) inc = GetCargoGoods(pchar, idx);
		if (inc > 0)
		{
			qty = AddCharacterGoodsSimple(xi_refCharacter, idx, inc);
			if (qty > 0)
			{
				RemoveCharacterGoodsSelf(pchar, idx, qty);
			}
			OnShipScrollChange();
			SetGoodsArrows();
			ShipSituation_SetQuestSituation(ShipSituation_1);
		}
	}	
}
////////////////////////////// crew ///////////////
void ShowCrewWindow()
{
	if (sMessageMode == "CREW_WINDOW")
	{
		ExitCrewWindow();
	}
	else
	{
		if (!isCompanion(xi_refCharacter) && !LAi_IsDead(xi_refCharacter))// ������� ���
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_1"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_text_1")); // ���������� ���������� ������ ����� �� ������ ���������. ...
			sMessageMode = "SurrenderedCrewOkMessage";
			ShowOkMessage();
		}
		else
		{
			SetCrewVariable();

			XI_WindowShow("CREW_WINDOW", true);
			XI_WindowDisable("CREW_WINDOW", false);

			SetCurrentNode("CREW_Win_fix");
			sMessageMode = "CREW_WINDOW";
		}
	}
}
void SetCrewVariable()
{
	string sText, sTextSecond;
	int iColor;

	SetCrewExpTable(pchar, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");

	SetFormatedText("CREW_QTY", ""+GetCrewQuantity(pchar));
	if (GetCrewQuantity(pchar) > GetOptCrewQuantity(pchar) || GetCrewQuantity(pchar) < GetMinCrewQuantity(pchar))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(pchar.ship.crew.morale)));
	SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(pchar.Ship.crew.morale))));

	////  ���������� 2
	SetCrewExpTable(xi_refCharacter, "TABLE_CREW2", "BAR_Sailors2", "BAR_Cannoners2", "BAR_Soldiers2");

	SetFormatedText("CREW_QTY2", ""+GetCrewQuantity(xi_refCharacter));
	if (GetCrewQuantity(xi_refCharacter) > GetOptCrewQuantity(xi_refCharacter) || GetCrewQuantity(xi_refCharacter) < GetMinCrewQuantity(xi_refCharacter))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY2", 8,-1,iColor);
	SetNewGroupPicture("CREW_MORALE_PIC2", "MORALE_SMALL", GetMoraleGroupPicture(stf(xi_refCharacter.ship.crew.morale)));
	SetFormatedText("CREW_MORALE_TEXT2", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(xi_refCharacter.Ship.crew.morale))));
}

void ExitCrewWindow()
{
	XI_WindowShow("CREW_WINDOW", false);
	XI_WindowDisable("CREW_WINDOW", true);

	SetCurrentNode("CREW_BUTTON");
	sMessageMode = "";
}

void TakeCrew(int inc)
{  // ����
    float fTemp;
	if (inc > GetCrewQuantity(xi_refCharacter)) inc = GetCrewQuantity(xi_refCharacter);
	if ( (GetCrewQuantity(pchar) + inc) > GetMaxCrewQuantity(pchar)) inc = GetMaxCrewQuantity(pchar) - GetCrewQuantity(pchar);
	if ( inc > GetCargoFreeSpace(pchar)) inc = GetCargoFreeSpace(pchar);
	if (inc > 0)
	{
		fTemp =  stf(GetCrewQuantity(pchar) + inc);
        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
		                                        stf(xi_refCharacter.Ship.Crew.Exp.Sailors)*inc) / fTemp;
		pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
		                                        stf(xi_refCharacter.Ship.Crew.Exp.Cannoners)*inc) / fTemp;
		pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
			                                        stf(xi_refCharacter.Ship.Crew.Exp.Soldiers)*inc) / fTemp;

		pchar.Ship.Crew.morale   = (stf(pchar.Ship.Crew.morale)*GetCrewQuantity(pchar) +
			                                        stf(xi_refCharacter.Ship.Crew.morale)*inc) / fTemp;

		pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + inc;
		xi_refCharacter.Ship.Crew.Quantity = sti(xi_refCharacter.Ship.Crew.Quantity) - inc;
		OnShipScrollChange();
		SetCrewVariable();
	}
}

void GiveCrew(int inc)
{  // �����
	float fTemp;
	if (inc > GetCrewQuantity(pchar)) inc = GetCrewQuantity(pchar);
	if ( (GetCrewQuantity(xi_refCharacter) + inc) > GetMaxCrewQuantity(xi_refCharacter)) inc = GetMaxCrewQuantity(xi_refCharacter) - GetCrewQuantity(xi_refCharacter);
	if ( inc > GetCargoFreeSpace(xi_refCharacter)) inc = GetCargoFreeSpace(xi_refCharacter);
	if (inc > 0)
	{
		fTemp =  stf(GetCrewQuantity(xi_refCharacter) + inc);
        xi_refCharacter.Ship.Crew.Exp.Sailors   = (stf(xi_refCharacter.Ship.Crew.Exp.Sailors)*GetCrewQuantity(xi_refCharacter) +
		                                           stf(pchar.Ship.Crew.Exp.Sailors)*inc) / fTemp;
		xi_refCharacter.Ship.Crew.Exp.Cannoners   = (stf(xi_refCharacter.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(xi_refCharacter) +
		                                            stf(pchar.Ship.Crew.Exp.Cannoners)*inc) / fTemp;
		xi_refCharacter.Ship.Crew.Exp.Soldiers   = (stf(xi_refCharacter.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(xi_refCharacter) +
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*inc) / fTemp;

		xi_refCharacter.Ship.Crew.morale   = (stf(xi_refCharacter.Ship.Crew.morale)*GetCrewQuantity(xi_refCharacter) +
			                                        stf(pchar.Ship.Crew.morale)*inc) / fTemp;

		xi_refCharacter.Ship.Crew.Quantity = sti(xi_refCharacter.Ship.Crew.Quantity) + inc;
		pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) - inc;
		OnShipScrollChange();
		SetCrewVariable();
	}
}
/////////////////////////////// capture_window
void ExitCaptureWindow()
{
	XI_WindowShow("CAPTURE_WINDOW", false);
	XI_WindowDisable("CAPTURE_WINDOW", true);
    XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CAPTAN_BUTTON");
	sMessageMode = "";
}

void ShowCaptureWindow()
{
	XI_WindowShow("CAPTURE_WINDOW", true);
	XI_WindowDisable("CAPTURE_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "CAPTURE_WINDOW";
}

void ExitCaptureCrewWindow()
{
	XI_WindowShow("CAPTURE_CREW_WINDOW", false);
	XI_WindowDisable("CAPTURE_CREW_WINDOW", true);
    XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CAPTAN_BUTTON");
	sMessageMode = "";
}

void ShowCaptureCrewWindow()
{
	XI_WindowShow("CAPTURE_CREW_WINDOW", true);
	XI_WindowDisable("CAPTURE_CREW_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "";
}

void ShowHireCrewWindow()
{
	XI_WindowShow("HIRE_CREW_WINDOW", true);
	XI_WindowDisable("HIRE_CREW_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "";
}

void ExitHireCrewWindow()
{
	XI_WindowShow("HIRE_CREW_WINDOW", false);
	XI_WindowDisable("HIRE_CREW_WINDOW", true);
    XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CAPTAN_BUTTON");
	sMessageMode = "";	

	OnShipScrollChange();
}
void SetEnemyToPrisoner()
{
	ExitCaptureWindow();
	SetCharToPrisoner(xi_refCharacter);
	LAi_SetCurHP(xi_refCharacter, 0.0); // ����
	//Boyer add
	FlagPerkForCapturedShip(xi_refCharacter);
	// ��� ��������� ���� - ����� ��� ������ ��������
	OnShipScrollChange();
	// ������ ������ - ������ �������
	ShowCrewCaptureAsk();
}

void SetEnemyToKilled()
{
	ExitCaptureWindow();
	LAi_SetCurHP(xi_refCharacter, 0.0); // ����
	//Boyer add
	FlagPerkForCapturedShip(xi_refCharacter);
	ChangeCharacterReputation(pchar, -2); // ������ ����
	OfficersReaction("bad");
	OnShipScrollChange();
	// ������ ������ - ������ �������
	ShowCrewCaptureAsk();
}

void ShowCrewCaptureHire()
{
	if (GetCrewQuantity(xi_refCharacter) > 0 && iGetHired > 0) 		
	{
		InitVariable();
		SetVariable();		
		ShowHireCrewWindow();
	}
}

void ShowCrewCaptureAsk()
{
	if (GetCrewQuantity(xi_refCharacter) > 0)
	{
		// ������ ������ - �������
		SetFormatedText("CAPTURE_TEXT_CREW", XI_ConvertString("Surrendered_crew_capture"));
		SetNewGroupPicture("CAPTUR_CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
		ShowCaptureCrewWindow();
		
		int iMode = CheckEnemyShipHPFree();
		switch (iMode)
		{
			case 0:
				SetSelectable("CAPTURE_CREW_FREE", false);
				SetCurrentNode("CAPTURE_CREW_PRISON");
			break;
			case 1:
				SetCurrentNode("CAPTURE_CREW_FREE");
			break;
			case 2:
				SetCurrentNode("CAPTURE_CREW_FREE");
			break;
		}
	}
}

void SetEnemyCrewToPrisoner()
{
	ExitCaptureCrewWindow();
	ChangeCharacterReputation(pchar, -1); // ������ ����
	OfficersReaction("bad");
	SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + sti(xi_refCharacter.Ship.Crew.Quantity))); // � ��������, ����� ��� �������
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

void SetEnemyCrewToKilled()
{
	ExitCaptureCrewWindow();
	ChangeCharacterReputation(pchar, -3); // ������ ����
	OfficersReaction("bad");
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

void SetEnemyCrewToFree()
{
	ExitCaptureCrewWindow();
	if(SetEnemyCrewGoods() == true)
	{
		ChangeCharacterReputation(pchar, 1); // ������� ����
		OfficersReaction("good");
	}
	RemoveEnemyShipHPFree();	
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

// ugeen --> ��������� ��������� ������, ����������  �� �������
bool SetEnemyCrewGoodOne(int iGood, int iGoodRateEat)
{
	int iQty, iGoodQty;
	int iCrewQty = GetCrewQuantity(xi_refCharacter);
	
	iGoodQty = makeint(iCrewQty/iGoodRateEat + 1);
	iQty = GetCargoGoods(xi_refCharacter, iGood);
	if(iQty >= iGoodQty) 
	{
		iQty = RemoveCharacterGoodsSelf(xi_refCharacter,iGood,iGoodQty); // ������� �� ������� ����������
		return iQty;
									
					 
		
			  
									 
					 
		
			   
									  
					 
		
	}
	else
	{	
		iQty = GetCargoGoods(pchar, iGood);
		if(iQty >= iGoodQty)	
		{
			iQty = RemoveCharacterGoodsSelf(pchar,iGood,iGoodQty); // ���� ��� � ����� - ������  � �������� ��
			return iQty;
		}
	}	
	return false;
}

int CheckEnemyShipHPFree()
{
	int iHP = makeint(GetCrewQuantity(xi_refCharacter)/HP_BY_ENEMY_CREW + 1) * HP_PER_BOAT;
	if(stf(xi_refCharacter.ship.hp) > iHP + 100) 
	{   // ��������� HP � �������������
		return 1;
	}
	else 
	{
		// c�������� HP � �������������
		if(stf(pchar.ship.hp) > iHP + 200)
		{
			return 2;
		}		
	}
	return 0; // ��������� ������ 
}

void RemoveEnemyShipHPFree()
{
	int iCrewQty = GetCrewQuantity(xi_refCharacter)/HP_BY_ENEMY_CREW;
	int iHP = makeint(iCrewQty + 1) * HP_PER_BOAT;
	if(stf(xi_refCharacter.ship.hp) > iHP + 100) 
	{
		xi_refCharacter.ship.hp = stf(xi_refCharacter.ship.hp) - iHP;
	}
	else
	{
		pchar.ship.hp = stf(pchar.ship.hp) - iHP;
	}
}

bool SetEnemyCrewGoods() // ������� ���������� ���� ����������� 
{
	bool bOk;
	
	bOk = SetEnemyCrewGoodOne(GOOD_FOOD, FOOD_BY_ENEMY_CREW);
	bOk = bOk && SetEnemyCrewGoodOne(GOOD_RUM, RUM_BY_ENEMY_CREW);
	bOk = bOk && SetEnemyCrewGoodOne(GOOD_MEDICAMENT, MEDICAMENT_BY_ENEMY_CREW);
	SetEnemyCrewGoodOne(GOOD_WEAPON, WEAPON_BY_ENEMY_CREW);
		
	return bOk;
}
// ugeen <--

int GetEnemyHiredCrew()
{
	int iEnemyHiredCrew = 0;

	if(CheckAttribute(refCharacter,"GenQuest.ShipExplode")) return iEnemyHiredCrew;
	
	if (CheckAttribute(xi_refCharacter, "Ship.Mode") && xi_refCharacter.Ship.Mode == "War") 
	{
		iEnemyHiredCrew = makeint(GetCrewQuantity(xi_refCharacter) * rand( makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)*0.2))/100.0 + GetCrewQuantity(xi_refCharacter) * rand( makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)*0.2))/100.0 );
	}
	else // ��� ���������
	{
		iEnemyHiredCrew = makeint(GetCrewQuantity(xi_refCharacter) * rand(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)*0.7))/100.0);
	}
	int iDiffCrew = GetMaxCrewQuantity(refCharacter) - GetCrewQuantity(refCharacter);
	// ���� ���� ������� -- ���� ��� ����� �� �������, �� � ������� �� ������ :(
	if(iDiffCrew > GetCargoFreeSpace(refCharacter))
	{
		iDiffCrew = GetCargoFreeSpace(refCharacter);
	}
		
	if(iEnemyHiredCrew > iDiffCrew) 
	{
		iEnemyHiredCrew = iDiffCrew;
	}		
	return iEnemyHiredCrew;
}

void SetShipInfoPic(ref chr, string sAdd)
{	
	int iShip = sti(chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("MAIN_SHIP_PICTURE" + sAdd, "interfaces\ships\" + sShip + ".tga");	
	}
}

void InitVariable()
{
	int nShipType = sti(refCharacter.ship.type);
		
	ref refBaseShip = GetRealShip(nShipType);
	
	SetShipInfoPic(refCharacter, "1");
	SetShipInfoPic(xi_refCharacter, "2");
	
	if (CheckAttribute(refCharacter, "ship.name"))
	{
		SetFormatedText("CAPACITY", refCharacter.ship.name);
	}
	else
	{
		SetFormatedText("CAPACITY", "");
	}	
	if (CheckAttribute(xi_refCharacter, "ship.name"))
	{
		SetFormatedText("HIRE_CAPACITY", xi_refCharacter.ship.name);
	}
	else
	{
		SetFormatedText("HIRE_CAPACITY", "");
	}	

	SetNewPicture("MAIN_HERO_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
	SetFormatedText("MAIN_HERO_NAME", GetFullName(refCharacter));
	
	SetNewGroupPicture("HIRE_CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetNewGroupPicture("HIRE_CREW_PICTURE2", "SHIP_STATE_ICONS", "Crew");
	
	SetFormatedText("HIRE_CREW_CAPACITY", "�������:\n���. "+GetMinCrewQuantity(refCharacter) + ", ���. " + GetOptCrewQuantity(refCharacter) + ", ����. " + GetMaxCrewQuantity(refCharacter));
	SetFormatedText("HIRE_QTY_TypeOperation", "�������� ������� � ��� � �������");		
}

void SetVariable()
{
	int iColor;
	string sText;
	
	SetCrewExpTable(refCharacter, "HIRE_TABLE_CREW", "HIRE_BAR_Sailors", "HIRE_BAR_Cannoners", "HIRE_BAR_Soldiers");
	
	SetFormatedText("HIRE_CREW_QTY", ""+GetCrewQuantity(refCharacter));
	if (GetCrewQuantity(refCharacter) > GetOptCrewQuantity(refCharacter) || GetCrewQuantity(refCharacter) < GetMinCrewQuantity(refCharacter))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HIRE_CREW_QTY", 8,-1,iColor);
	SetNewGroupPicture("HIRE_CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(refCharacter.ship.crew.morale)));
	SetFormatedText("HIRE_CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(refCharacter.Ship.crew.morale))));
	
	// �������� �� ������� ��
	sText = "��������� �� �������:\n�� ";
	int iFood = CalculateShipFood(refCharacter);
	sText = sText + FindRussianDaysString(iFood);
	SetFormatedText("HIRE_FOOD_SHIP", sText);

	// ��� �� ������� ��
	sText = "���� �� �������:\n�� ";
	int iRum = CalculateShipRum(refCharacter);
	sText = sText + FindRussianDaysString(iRum);
	SetFormatedText("HIRE_RUM_SHIP", sText);
	
	//  ���������� ����������
	SetCrewExpTable(xi_refCharacter, "HIRE_TABLE_CREW2", "HIRE_BAR_Sailors2", "HIRE_BAR_Cannoners2", "HIRE_BAR_Soldiers2");
	
	SetFormatedText("HIRE_CREW_QTY2", ""+GetCrewQuantity(xi_refCharacter));
	SetNewGroupPicture("HIRE_CREW_MORALE_PIC2", "MORALE_SMALL", GetMoraleGroupPicture(stf(xi_refCharacter.ship.crew.morale)));
	SetFormatedText("HIRE_CREW_MORALE_TEXT2", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(xi_refCharacter.Ship.crew.morale))));

	SetFormatedText("HIRED_CREW", ""+sti(xi_refCharacter.Ship.Crew.Hire));	
}

// ����� ��������, �� ����������
void SetBackupQty()
{
	aref    arTo, arFrom;
	NullCharacter.CrewBak.Hero = "";
	NullCharacter.CrewBak.ECrew = "";
	
	makearef(arTo, NullCharacter.CrewBak.Hero);
	makearef(arFrom, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo, NullCharacter.CrewBak.ECrew);
	makearef(arFrom, xi_refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void GetBackupQty()
{
	aref    arTo, arFrom;
	
	makearef(arFrom, NullCharacter.CrewBak.Hero);
	makearef(arTo, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom, NullCharacter.CrewBak.ECrew);
	makearef(arTo, xi_refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void SetBackupExp()
{
	aref    arTo, arFrom;
	NullCharacter.CrewBak.Exp = "";
	NullCharacter.CrewBak.Morale = "";
	
	makearef(arTo, NullCharacter.CrewBak.Exp);
	makearef(arFrom, refCharacter.Ship.Crew.Exp);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo, NullCharacter.CrewBak.Morale);
	makearef(arFrom, refCharacter.Ship.Crew.Morale);
	CopyAttributes(arTo, arFrom);
}

void GetBackupExp()
{
	aref    arTo, arFrom;
	
	makearef(arFrom, NullCharacter.CrewBak.Exp);
	makearef(arTo, refCharacter.Ship.Crew.Exp);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom, NullCharacter.CrewBak.Morale);
	makearef(arTo, xi_refCharacter.Ship.Crew.Morale);
	CopyAttributes(arTo, arFrom);
}

void HireTransactionCancel()
{
	GetBackupQty();
	DeleteAttribute(xi_refCharacter, "Ship.Crew.Hire");
	ExitHireCrewWindow();
}

void HireTransactionOK()
{
	DeleteAttribute(xi_refCharacter, "Ship.Crew.Hire");
	ExitHireCrewWindow();
}

void HIRE_ChangeQTY_EDIT()
{
	float fQty;
	string sText, sTextSecond;
	int iColor;
	
	GetBackupExp();
	
	fQty = stf(GetCrewQuantity(refCharacter) + iCrewQty);
			
	refCharacter.Ship.Crew.Exp.Sailors   = (stf(refCharacter.Ship.Crew.Exp.Sailors)*GetCrewQuantity(refCharacter) + 
			                                        stf(xi_refCharacter.Ship.Crew.Exp.Sailors)*iCrewQty) / fQty; 
	refCharacter.Ship.Crew.Exp.Cannoners = (stf(refCharacter.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(refCharacter) + 
			                                        stf(xi_refCharacter.Ship.Crew.Exp.Cannoners)*iCrewQty) / fQty;
	refCharacter.Ship.Crew.Exp.Soldiers  = (stf(refCharacter.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(refCharacter) + 
			                                        stf(xi_refCharacter.Ship.Crew.Exp.Soldiers)*iCrewQty) / fQty;
	refCharacter.Ship.Crew.Morale        = (stf(refCharacter.Ship.Crew.Morale)*GetCrewQuantity(refCharacter) + 
			                                        stf(xi_refCharacter.Ship.Crew.Morale)*iCrewQty) / fQty;
																											
	SetCrewQuantity(refCharacter, GetCrewQuantity(refCharacter) + iCrewQty - iBackCrew);
	SetCrewQuantity(xi_refCharacter, GetCrewQuantity(xi_refCharacter) - iCrewQty + iBackCrew);
	
	iBackCrew = iCrewQty;
	
	SetVariable();	
}

void HIRE_REMOVE_ALL_BUTTON()
{
	if(iCrewQty > 0)
	{
		xi_refCharacter.Ship.Crew.Hire = sti(xi_refCharacter.Ship.Crew.Hire) + iCrewQty;
		iCrewQty = 0;
		HIRE_ChangeQTY_EDIT();
	}	
}

void HIRE_ADD_ALL_BUTTON()
{
	if(sti(xi_refCharacter.Ship.Crew.Hire) > 0)
	{
		iCrewQty = iCrewQty + sti(xi_refCharacter.Ship.Crew.Hire);
		xi_refCharacter.Ship.Crew.Hire = 0;
		HIRE_ChangeQTY_EDIT();
	}
}

void HIRE_REMOVE_BUTTON()  
{
	if(iCrewQty > 0)
	{
		iCrewQty = iCrewQty -1;
		xi_refCharacter.Ship.Crew.Hire = sti(xi_refCharacter.Ship.Crew.Hire) + 1;
		HIRE_ChangeQTY_EDIT();
	}	
}

void HIRE_ADD_BUTTON()  
{
	if(sti(xi_refCharacter.Ship.Crew.Hire) > 0)
	{
		iCrewQty = iCrewQty +1;
		xi_refCharacter.Ship.Crew.Hire = sti(xi_refCharacter.Ship.Crew.Hire) - 1;		
		HIRE_ChangeQTY_EDIT();
	}
}

/* Vorius 09/06/2009 -- ����� � PiratesAhoy
   returns a string representing the given officer's position */
string GetOfficerPosition(string sCharacter)
{	
	if (CheckAttribute(pchar,"Fellows.Passengers.navigator") && sCharacter == sti(pchar.Fellows.Passengers.navigator))
		return XI_ConvertString("navigator");
	if (CheckAttribute(pchar,"Fellows.Passengers.boatswain") && sCharacter == sti(pchar.Fellows.Passengers.boatswain))
		return XI_ConvertString("boatswain");
	if (CheckAttribute(pchar,"Fellows.Passengers.cannoner") && sCharacter == sti(pchar.Fellows.Passengers.cannoner))
		return XI_ConvertString("cannoner");
	if (CheckAttribute(pchar,"Fellows.Passengers.doctor") && sCharacter == sti(pchar.Fellows.Passengers.doctor))
		return XI_ConvertString("doctor");
	if (CheckAttribute(pchar,"Fellows.Passengers.treasurer") && sCharacter == sti(pchar.Fellows.Passengers.treasurer))
		return XI_ConvertString("treasurer");
	if (CheckAttribute(pchar,"Fellows.Passengers.carpenter") && sCharacter == sti(pchar.Fellows.Passengers.carpenter))
		return XI_ConvertString("carpenter");
	
	for(int i=1; i<4; i++)
	{	
		if (sti(GetOfficersIndex(pchar, i)) == sti(sCharacter))
			return XI_ConvertString("fighter");
	}

	return XI_ConvertString("passengership");
}