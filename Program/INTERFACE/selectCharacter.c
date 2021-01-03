///  BOAL ��������� ��� SLib 02.07.06
#define DEFAULT_NAME "Player"
#define DEFAULT_PASS ""

bool isOkExit = false;
 int idLngFile = -1;
string sCharacterName;

bool g_bToolTipStarted = false;
int heroQty = 0;
string totalInfo;
string totalInfoChar;

void InitInterface(string iniName)
{
	GameInterface.title = "titleCharacterSelect";
	GameInterface.faces.current = 1;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetNewGroupPicture("ENGLAND", "NATIONS", "England");
	SetNewGroupPicture("FRANCE", "NATIONS", "France");
	SetNewGroupPicture("SPAIN", "NATIONS", "Spain");
	SetNewGroupPicture("HOLLAND", "NATIONS", "Holland");
	SetNewGroupPicture("PIRATE", "NATIONS", "Pirate");

	SetMainCharacterIndex(1);

	sCharacterName = pchar.id;

	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"BLAZE", 5, 1);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"FRANCE", 5, 1);

	GameInterface.PROFILE_NAME.str = DEFAULT_NAME;
	GameInterface.PROFILE_PASS.str = DEFAULT_PASS;

    LoadStartGameParam(); // boal
    MOD_EXP_RATE =  10; // ������ � ������ ���� (�����, �� 5 �� 15, 10 - �������� �� ���������, 15 - �������)
    GameInterface.nodes.EXP_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"EXP_SLIDE", 0, 0.5);
	
	MOD_OFFICERS_RATE = 3;
	GameInterface.nodes.OFF_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"OFF_SLIDE", 0, 0.5);
	
	MOD_DEAD_CLEAR_TIME = 100;
	GameInterface.nodes.DEAD_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"DEAD_SLIDE", 0, 0.5);
	
	MOD_DEFENDERS_RATE = 4;
	GameInterface.nodes.DEFENDERS_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"DEFENDERS_SLIDE", 0, 0.5);

    if (startHeroType < 1) startHeroType = 1; // fix
    if (startHeroType > sti(GetNewMainCharacterParam("hero_qty"))) startHeroType = sti(GetNewMainCharacterParam("hero_qty")); // fix

	SetEventHandler("exitCancel", "exitCancel", 0);
	SetEventHandler("exitOk", "exitOk", 0);
	SetEventHandler("selectEngland", "selectEngland", 0);
	SetEventHandler("selectFrance", "selectFrance", 0);
	SetEventHandler("selectSpain", "selectSpain", 0);
	SetEventHandler("selectHolland", "selectHolland", 0);
	SetEventHandler("selectPirate", "selectPirate", 0);
	SetEventHandler("confirmChangeProfileName", "confirmChangeProfileName", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("ShowInfo","ShowInfo",0);

	SetEventHandler("noteOk","procNoteOk",0);

	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);


	if (!CheckAttribute(&GameInterface, "SavePath"))
		GameInterface.SavePath = GetSaveDirectory();

	EI_CreateFrame("CHARACTER_BIG_PICTURE_BORDER",50,76,300,358); // tak from CHARACTER_BIG_PICTURE
    EI_CreateHLine("CHARACTER_BIG_PICTURE_BORDER", 54,107,296,1, 4);

    heroQty   = sti(GetNewMainCharacterParam("hero_qty"));

    if (!CheckAttribute(&NullCharacter, "HeroParam.HeroType") || !CheckAttribute(&NullCharacter, "HeroParam.nation"))
    {   // ����� ��� �������� � ������ ��, ������� ��������� � ���� �������
		SetVariable(true);
	}
	else
	{
	    SetVariable(false);
	}
	TmpI_ShowLevelComplexity();
	TmpI_ShowOffAmount();
	SetByDefault();
}

void SetByDefault()
{
    CheckButton_SetState("CHECK_ENCOUNTERS", iEncountersRate, true);

	if (iArcadeSails == 1)// 1 0
    {
    	CheckButton_SetState("CHECK_ARCADESAIL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_ARCADESAIL", 2, true);
    }
    if (bRechargePistolOnLine)// 1 0
    {
    	CheckButton_SetState("CHECK_PISTOL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PISTOL", 1, false);
    }
    if (bPartitionSet)// 1 0
    {
    	CheckButton_SetState("CHECK_PARTITION", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PARTITION", 1, false);
    }
	if (bSailorsWeight)// 1 0
    {
    	CheckButton_SetState("CHECK_CREWWEIGHT", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_CREWWEIGHT", 1, false);
    }
	if (bNewSails)// 1 0
    {
    	CheckButton_SetState("CHECK_SAILS", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_SAILS", 1, false);
    }
	if (bNoPirateRestrictions)// 1 0
    {
    	CheckButton_SetState("CHECK_NOPIRATE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_NOPIRATE", 1, false);
    }
	if (bHigherShipRate)// 1 0
    {
    	CheckButton_SetState("CHECK_LOWERSHIP", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_LOWERSHIP", 1, false);
    }
    if (bHardcoreGame)// 1 0
    {
    	CheckButton_SetState("CHECK_HARDCORE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_HARDCORE", 1, false);
    }
    if (bQuestMark)// 1 0
    {
    	CheckButton_SetState("CHECK_MARK", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_MARK", 1, false);
    }
}

void IProcessFrame()
{
	TmpI_ShowOffAmount();
	TmpI_ShowDeadAmount();
	TmpI_ShowDefendersAmount();
	if(GetCurrentNode() == "PROFILE_NAME")
	{
		if(!CheckAttribute(&characters[GetCharacterIndex(sCharacterName)], "profile.name"))
		{
			confirmChangeProfileName();
		}

		if(characters[GetCharacterIndex(sCharacterName)].profile.name!= GameInterface.PROFILE_NAME.str)
		{
			confirmChangeProfileName();
		}
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 1))
	{
		iEncountersRate = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 2))
	{
		iEncountersRate = 2;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 3))
	{
		iEncountersRate = 3;
	}
	////
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 1))
	{
		iArcadeSails = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 2))
	{
		iArcadeSails = 0;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PISTOL", 3, 1))
	{
		bRechargePistolOnLine = true;
	}
	else
	{
		bRechargePistolOnLine = false;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HARDCORE", 3, 1))
	{
		bHardcoreGame = true;
	}
	else
	{
		bHardcoreGame = false;
	}
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PARTITION", 3, 1))
	{
		bPartitionSet = true;
	}
	else
	{
		bPartitionSet = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_CREWWEIGHT", 3, 1))
	{
		bSailorsWeight = true;
	}
	else
	{
		bSailorsWeight = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SAILS", 3, 1))
	{
		bNewSails = true;
	}
	else
	{
		bNewSails = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_NOPIRATE", 3, 1))
	{
		bNoPirateRestrictions = true;
	}
	else
	{
		bNoPirateRestrictions = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_LOWERSHIP", 3, 1))
	{
		bHigherShipRate = true;
	}
	else
	{
		bHigherShipRate = false;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_MARK", 3, 1))
	{
		bQuestMark = true;
	}
	else
	{
		bQuestMark = false;
	}
}

void exitCancel()
{
	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		isOkExit = true;
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU, true);
		return;
	}
	IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	ReturnToMainMenu();
}

void exitOk()
{
	if( !IsCorrectProfileName() )
	{
		ShowNoteText(true);
		return;
	}

	confirmChangeProfileName();

	if (!ProfileExists())
	{
		CreateProfileFolders();

        isOkExit = true;
		IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	}
	else
	{

		ShowConfirmWindow(true);
	}
}

bool IsCorrectProfileName()
{
	int n,nLen;
	string str,sCurProfileName;

	sCurProfileName = GameInterface.PROFILE_NAME.str;
	nLen = strlen(sCurProfileName);
	if( nLen==0 ) {return false;}

	for( n=0; n<nLen; n++ )
	{
		str = GetSymbol(&sCurProfileName,n);
		if( str=="*" ) {return false;}
		if( str=="?" ) {return false;}
		if( str=="\" ) {return false;}
		if( str=="/" ) {return false;}
	}
	return true;
}

void ShowNoteText(bool bShow)
{
	if( bShow ) {
		XI_WindowDisable("MAIN_WINDOW", true);

		XI_WindowDisable("NOTE_WINDOW", false);
		XI_WindowShow("NOTE_WINDOW", true);

		SetCurrentNode("NOTE_WINDOW_OK");
	} else {
		XI_WindowDisable("MAIN_WINDOW", false);

		XI_WindowDisable("NOTE_WINDOW", true);
		XI_WindowShow("NOTE_WINDOW", false);

		SetCurrentNode("PROFILE_NAME");
	}
}

void procNoteOk()
{
	ShowNoteText(false);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
        case "LEFTCHANGE_COMPLEX":
		if(comName=="click")
		{
		    if (MOD_SKILL_ENEMY_RATE > 1)
		    {
               MOD_SKILL_ENEMY_RATE--;
            }
            TmpI_ShowLevelComplexity();
		}
		break;

		case "RIGHTCHANGE_COMPLEX":
			if(comName=="click")
			{
			    if (MOD_SKILL_ENEMY_RATE < 10)
			    {
	               MOD_SKILL_ENEMY_RATE++;
	            }
	            TmpI_ShowLevelComplexity();
			}
		break;
		
		case "OFF_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowOffAmount();
			}
		break;
		
		case "DEAD_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowDeadAmount();
			}
		break;
		
		case "DEFENDERS_SLIDE":
			if(comName=="click" || comName=="leftstep" || comName=="speedleft" || comName=="rightstep" || comName=="speedright" || comName=="deactivate" || comName=="rclick")
			{
				TmpI_ShowDefendersAmount();
			}
		break;

		case "CONFIRM_WINDOW_MB_YES":

			if (comName == "click" || comName == "activate")
			{
				//DeleteProfile();
				//exitOk();
				isOkExit = true;
				SaveStartGameParam(); // boal
				IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
			}

			if (comName == "deactivate")
			{

				ShowConfirmWindow(false);
			}

			break;

		case "CONFIRM_WINDOW_MB_NO":

			if (comName == "click" || comName == "activate")
			{
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate")
			{

				ShowConfirmWindow(false);
			}

			break;

		////////////////////////////////
		case "OK_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	case "CANCEL_BUTTON":
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
    	case "SETUP_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
			//	 ProcessSetGameOptionsExit();
    		}
    		if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		case "LEFTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    	break;

    	case "RIGHTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteRight();
    		}
    	break;

    	case "LEFTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeLeft();
    		}
    	break;

    	case "RIGHTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeRight();
    		}
    	break;

    	case "FACEPICT":
    		if(comName=="click")
    		{
          		totalInfo = GetConvertStr("hero_" + startHeroType, "HeroDescribe.txt");
				SetInfoText();
    		}
    	break;
	}

}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDERS",190,190,610,360);

	}
	else
	{
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void CreateProfileFolders()
{
	String folder = GameInterface.SavePath + "\";
	folder+= pchar.profile.name;

	if (CheckFolder(folder)) return;

	if(!CreateFolder(folder))
		trace("Could not create profile folder");
}
//----------------------------------------------------------------------------------------------------
void DeleteProfile()
{
	String folder;

	folder = GameInterface.SavePath + "\"+ pchar.profile.name;

	int nSaveNum= 0;
	string saveName;
	int nSaveSize;

	String path = GameInterface.SavePath;
	GameInterface.SavePath = folder;

    while( SendMessage(&GameInterface,"llee",MSG_INTERFACE_SAVE_FILE_FIND,nSaveNum,&saveName,&nSaveSize)!=0 )
    {
		nSaveNum++;
		SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,saveName);
    }

	GameInterface.SavePath = path;
	DeleteFolder(folder);
}
//----------------------------------------------------------------------------------------------------
bool ProfileExists()
{
	String folder = GameInterface.SavePath + "\";


	folder+= pchar.profile.name;

	return (CheckFolder(folder));
}
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void SelectNation(int iNation)
{
	/////////////////////////////////////////////////////
	string sNationPict;
	for (int i=0; i<MAX_NATIONS; i++)
	{
		sNationPict = GetNationNameByType(i);

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 0);
	}

	sNationPict = GetNationNameByType(iNation);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 1);
	/////////////////////////////////////////////////////
	NullCharacter.HeroParam.Nation = iNation;
	totalInfo = GetRPGText(Nations[iNation].Name + "_descr");
	SetInfoText();
}

void selectEngland()
{
	SelectNation(ENGLAND);
}

void selectFrance()
{
    //homo ���������� ����� ��� ������ �����
    if (startHeroType == 1) SelectNation(ENGLAND);
	else SelectNation(FRANCE);

}

void selectSpain()
{
    //homo ���������� ����� ��� ������ �����
    if (startHeroType == 1) SelectNation(ENGLAND);
	else SelectNation(SPAIN);

}

void selectHolland()
{
    //homo ���������� ����� ��� ������ �����
    if (startHeroType == 1) SelectNation(ENGLAND);
	else SelectNation(HOLLAND);

}

void selectPirate()
{
    	//homo ���������� ����� ��� ������ �����
	if (startHeroType == 1) SelectNation(ENGLAND);
	else SelectNation(PIRATE);
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("exitCancel", "exitCancel");
	DelEventHandler("exitOk", "exitOk");
	DelEventHandler("selectEngland", "selectEngland");
	DelEventHandler("selectFrance", "selectFrance");
	DelEventHandler("selectSpain", "selectSpain");
	DelEventHandler("selectHolland", "selectHolland");
	DelEventHandler("selectPirate", "selectPirate");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfo","ShowInfo");

	DelEventHandler("noteOk","procNoteOk");

	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

	if(isOkExit == false)
	{
		EndCancelInterface(bCode);
	}
	else
	{
        MOD_EXP_RATE = makeint(5 + 10.0 * (1.0 - stf(GameInterface.nodes.EXP_SLIDE.value)));  // 0� 5 �� 15
		trace("MOD_EXP_RATE = " + MOD_EXP_RATE);
		
		MOD_OFFICERS_RATE = makeint(10 - 7.0 * (1.0 - stf(GameInterface.nodes.OFF_SLIDE.value)));  // 0� 3 �� 10
		trace("MOD_OFFICERS_RATE = " + MOD_OFFICERS_RATE);
		
		MOD_DEAD_CLEAR_TIME = makeint(500 - 400.0 * (1.0 - stf(GameInterface.nodes.DEAD_SLIDE.value)));  // 0� 100 �� 500
		trace("MOD_DEAD_CLEAR_TIME = " + MOD_DEAD_CLEAR_TIME);
		
		MOD_DEFENDERS_RATE = makeint(5 - 5.0 * (1.0 - stf(GameInterface.nodes.DEFENDERS_SLIDE.value)));  // 0� 0 �� 5
		trace("MOD_DEFENDERS_RATE_RATE = " + MOD_DEFENDERS_RATE);
		
		interfaceResultCommand = exitCode;
		EndCancelInterface(bCode);
	}
}

void confirmChangeProfileName()
{
	PlayerProfile.name = GameInterface.PROFILE_NAME.str;
	pchar.profile.name = GameInterface.PROFILE_NAME.str;
}


void confirmChangeProfilePass()
{
	PlayerProfile.password = GameInterface.PROFILE_PASS.str;
	pchar.profile.pass = GameInterface.PROFILE_PASS.str;
	SetCurrentNode("OK_BUTTON");
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

	switch(sNode)
	{
		case "ENGLAND":
			sHeader = XI_ConvertString("England");
			sText1 = GetRPGText("England_descr");
		break;

		case "FRANCE":
			sHeader = XI_ConvertString("France");
			sText1 = GetRPGText("France_descr");
		break;

		case "HOLLAND":
			sHeader = XI_ConvertString("Holland");
			sText1 = GetRPGText("Holland_descr");
		break;

		case "SPAIN":
			sHeader = XI_ConvertString("Spain");
			sText1 = GetRPGText("Spain_descr");
		break;

		case "PIRATE":
			sHeader = XI_ConvertString("Pirate");
			sText1 = GetRPGText("Pirate_descr");
		break;

		case "COMPLEX_TYPE":
			sHeader = XI_ConvertString("m_Complexity");
			sText1 = GetRPGText("LevelComplexity_desc");
		break;

		case "CHECK_ENCOUNTERS":
			sHeader = XI_ConvertString("EncountersRate");
			sText1 = GetRPGText("EncountersRate_desc");
		break;

		case "CHECK_ARCADESAIL":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;

		case "CHECK_PISTOL":
			sHeader = XI_ConvertString("New Fight Mode");
			sText1 = GetRPGText("RechargePistolOnLine_desc");
		break;

		case "CHECK_HARDCORE":
			sHeader = XI_ConvertString("HardcoreGame");
			sText1 = GetRPGText("HardcoreGame_desc");
		break;

		case "CHECK_PARTITION":
			sHeader = XI_ConvertString("Partition Set");
			sText1 = GetRPGText("Partition_hint");
		break;
		
		case "CHECK_CREWWEIGHT":
			sHeader = XI_ConvertString("CrewWeight");
			sText1 = GetRPGText("CrewWeight_hint");
		break;
		
		case "CHECK_SAILS":
			sHeader = XI_ConvertString("NewSails");
			sText1 = GetRPGText("NewSails_hint");
		break;
		
		case "CHECK_NOPIRATE":
			sHeader = XI_ConvertString("NoPirate");
			sText1 = GetRPGText("NoPirate_hint");
		break;
		
		case "CHECK_LOWERSHIP":
			sHeader = XI_ConvertString("LowerShip");
			sText1 = GetRPGText("LowerShip_hint");
		break;
		
		case "CHECK_MARK":
			sHeader = XI_ConvertString("QuestMark");
			sText1 = GetRPGText("QuestMark_desc");
		break;
		
		case "EXP_SLIDE":
			sHeader = GetRPGText("EXP_SLIDE");
			sText1 = GetRPGText("EXP_SLIDE_desc");
		break;
		
		case "OFF_SLIDE":
			sHeader = GetRPGText("OFF_SLIDE");
			sText1 = GetRPGText("OFF_SLIDE_desc");
		break;
		
		case "DEAD_SLIDE":
			sHeader = GetRPGText("DEAD_SLIDE");
			sText1 = GetRPGText("DEAD_SLIDE_desc");
		break;
		
		case "DEFENDERS_SLIDE":
			sHeader = GetRPGText("DEFENDERS_SLIDE");
			sText1 = GetRPGText("DEFENDERS_SLIDE_desc");
		break;
	}
	//sHeader = XI_ConvertString("Nation");
	//sText1 = GetRPGText("Nation_hint");
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

void ProcessCommandExecuteLeft()
{
    if (startHeroType > 1)
    {
       startHeroType--;
    }
    else
    {
       startHeroType = heroQty;
    }
    SetVariable(true);
}

void ProcessCommandExecuteRight()
{
    if (startHeroType < heroQty)
    {
       startHeroType++;
    }
    else
    {
       startHeroType = 1;
    }
    SetVariable(true);
}

void SetVariable(bool _init)
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    SetFormatedText("HERO_NAME", GetNewMainCharacterName());
    if (_init)
    {
    	NullCharacter.HeroParam.HeroType = GetNewMainCharacterType(startHeroType);
    	NullCharacter.HeroParam.nation = GetNewMainCharacterNation(startHeroType);
	}
    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    SetNewPicture("FACEPICT", "interfaces\portraits\256\face_" + GetNewMainCharacterFace() + ".tga");
    SelectNation(sti(NullCharacter.HeroParam.nation));
    totalInfo = LanguageConvertString(idLngFile, "hero_" + startHeroType);
    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
	MainChAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
    SetInfoText();
    SetInfoChar();
    LanguageCloseFile(idLngFile);
}


string GetCharacterType(string type, int direction)
{
     switch (type)
	{
        case "Master":
            if (direction > 0)
            {
    	    	type = "Merchant";
    	    }
    	    else
    	    {
    	        type = "SeaWolf";
    	    }
	    break;

	    case "Merchant":
            if (direction > 0)
            {
    	    	type = "Corsair";
    	    }
    	    else
    	    {
    	        type = "Master";
    	    }
	    break;

	    case "Corsair":
            if (direction > 0)
            {
    	    	type = "Adventurer";
    	    }
    	    else
    	    {
    	        type = "Merchant";
    	    }
	    break;
		
	    case "Adventurer":
            if (direction > 0)
            {
    	    	type = "Inquisitor";
    	    }
    	    else
    	    {
    	        type = "Corsair";
    	    }
	    break;
		
	    case "Inquisitor":
            if (direction > 0)
            {
    	    	type = "SecretAgent";
    	    }
    	    else
    	    {
    	        type = "Adventurer";
    	    }
	    break;
		
	    case "SecretAgent":
            if (direction > 0)
            {
    	    	type = "SeaWolf";
    	    }
    	    else
    	    {
    	        type = "Inquisitor";
    	    }
	    break;
		
		case "SeaWolf":
            if (direction > 0)
            {
    	    	type = "Master";
    	    }
    	    else
    	    {
    	        type = "SecretAgent";
    	    }
	    break;
	}

	return type;
}

void ProcessCommandExecuteTypeLeft()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, -1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
    SetInfoChar();
    LanguageCloseFile(idLngFile);
}

void ProcessCommandExecuteTypeRight()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, 1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfoChar = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
    SetInfoChar();
    LanguageCloseFile(idLngFile);
}

void SetInfoText()
{
    SetFormatedText("INFO_TEXT", totalInfo);
    SetVAligmentFormatedText("INFO_TEXT");
}

void SetInfoChar()
{
    SetFormatedText("INFO_CHAR", totalInfoChar);
    SetVAligmentFormatedText("INFO_CHAR");
}
void TmpI_ShowLevelComplexity()
{
    SetFormatedText("COMPLEX_TYPE", GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
}
void TmpI_ShowOffAmount()
{
    SetFormatedText("OFF_COUNT", "" + makeint(10 - 7.0 * (1.0 - stf(GameInterface.nodes.OFF_SLIDE.value))));
}
void TmpI_ShowDeadAmount()
{
    SetFormatedText("DEAD_COUNT", "" + makeint(500 - 400.0 * (1.0 - stf(GameInterface.nodes.DEAD_SLIDE.value))));
}
void TmpI_ShowDefendersAmount()
{
    SetFormatedText("DEFENDERS_COUNT", "" + makeint(5 - 5.0 * (1.0 - stf(GameInterface.nodes.DEFENDERS_SLIDE.value))));
}
