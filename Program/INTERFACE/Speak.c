//Philippe, de AoP1
#define NOTHING		0
#define NEUTRAL		1
#define ENEMY		2
#define TAX			3
#define CAPTURE		4

#define SPEAK_DEBUG	0

string totalInfo = "";
//#20171207-01 remove unused variables
//string sMessageMode;
int step = 0;
bool isCommander = false;

int iFlag = NOTHING;

bool isRansom = false;
bool isAskForRansom = false;
bool isDeniedRansom = false;
bool isTax = false;

string sTarget = "";
int iWhoSpeak = -1;
ref rSpeakCharacter;
//#20171207-01 remove unused variables
//int refEnemyCharacter;

int iStringsQuantity = 5;
string sGlobalMode = "";
//#20200329-03
#define DSENC_SECONDS_TIMEOUT 8
int nTimeout = 0;
int DSENC_TIMEOUT = 90;

void InitInterface_RIS(string iniName, aref chr, int whospeak, string sMode)
{
	sGlobalMode = sMode;
	rSpeakCharacter = CharacterFromID(chr.id);
	sTarget = chr.id;
	iWhoSpeak = whospeak;

	if (!CheckAttribute(rSpeakCharacter, "surrendered"))
	{
		DeleteAttribute(rSpeakCharacter, "speak.capture");
	}

	GameInterface.title = "titleSpeak";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CalculateInfoData();

	SetFormatedText("INFO_TEXT",totalInfo);

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("exitNews","exitNews",0);
	SetEventHandler("exitCapture","exitCapture",0);
	SetEventHandler("OkCapture","OkCapture",0);
	SetEventHandler("CalculateNews", "CalculateNews", 0);
	SetEventHandler("Trade","Trade",0);
	SetEventHandler("FTChange","FTChange",0);
	SetEventHandler("ShipGoFreeAsk","ShipGoFreeAsk",0);
	//#20200329-03
	SetEventHandler("frame","IProcessFrame",0);

	string sText = "";
	int iColor = argb(255,255,255,255);

	sText = " " + XI_ConvertString("Speak_news");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);
	sText = " " + XI_ConvertString("Speak_Trade");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);
	sText = " " + XI_ConvertString("Speak_ransom");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);
	sText = " " + XI_ConvertString("Speak_capture");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);
	sText = " " + XI_ConvertString("Speak_tax");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);
	sText = " " + XI_ConvertString("Speak_cancel");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 0,&sText);

	SetNodeUsing("RANSOM_ANSWERS", false);

	switch(sMode)
	{
		/*  No longer does a ship spontaneously ask this, they just raise the white flag
		 case "capture":
			AskForCapture();
		break;
		*/
		case "ransom":
			isRansom = true;  //already checked for ransom in seaspeak.c
			AskForRansom();
		break;
		case "tax":
			AskForTax();
		break;
            /*    case "ShipGoFreeAsk":
			ShipGoFreeAsk();
		break;*/
	}
	SetDefaultColorsForAnswers();
	SetSelectedColorsForAnswers(0);

	SetNewPicture("PORTRAIT_PICTURE", "interfaces\portraits\128\face_" + rSpeakCharacter.FaceId + ".png");
	SetNewPicture("PLAYER_PORTRAIT_PICTURE", "interfaces\portraits\128\face_" + pchar.FaceId + ".png");

	sText = XI_ConvertString("ChooseSpeakAnswers");
	SetFormatedText("HELP", stext);
	DSENC_TIMEOUT = GetFPS() * DSENC_SECONDS_TIMEOUT;
}
//#20200329-03
void IProcessFrame() //Interface screens cannot use event delay
{
    nTimeout++;
}

void ProcessCancelExit()
{
	if(iFlag == CAPTURE) { Ship_Surrender(sti(rSpeakCharacter.index)); }
	IDoExit( RC_INTERFACE_SPEAK_EXIT, true );
}

void IDoExit(int exitCode, bool bCode)
{
	//SetTimeScale(1.0);
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("exitNews","exitNews");
	DelEventHandler("exitCapture","exitCapture");
	DelEventHandler("OkCapture","OkCapture");
	DelEventHandler("CalculateNews", "CalculateNews");
	DelEventHandler("Trade","Trade");
	DelEventHandler("FTChange","FTChange");
	DelEventHandler("ShipGoFreeAsk","ShipGoFreeAsk");

	interfaceResultCommand = exitCode;

	if (interfaceResultCommand != RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE)
	{
		if (iFlag == NEUTRAL)
		{
			AnalizeSituations(rSpeakCharacter);
            if (SPEAK_DEBUG) trace("etape neutre speak");
		}
		if (iFlag == TAX)
		{
			AnalizeSituationsTax(rSpeakCharacter);
			if (SPEAK_DEBUG) trace("etape taxe speak");
		}
		if (iFlag == ENEMY)
		{
			AnalizeSituationsEnemy();
			if (SPEAK_DEBUG) trace("etape ennemi speak");
		}
	}
	pchar.speakchr = rSpeakCharacter.id;
	EndCancelInterface(bCode);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	//#20200329-03
	if(nTimeout < DSENC_TIMEOUT) return;
	switch(nodName)
	{
		case "B_CANCEL":
			if(comName=="activate" || comName=="click")
			{
				PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SPEAK_EXIT);
				//SetTimeScale(1.0);
			}
		break;
		case "ANSWERS":
			if(comName=="activate" || comName=="click" || comName=="dblclick")
			{
				RecognizeAnswer();
				if (SPEAK_DEBUG) trace("etape reconansw speak");
			}
		break;
		case "RANSOM_ANSWERS":
			if(comName=="activate" || comName=="click")
			{
				RecognizeRansomAnswer();
				if (SPEAK_DEBUG) trace("etape reconrans speak");
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode, true);
}

void CalculateInfoData()
{
	int iRelation = GetRelation(sti(rSpeakCharacter.index), nMainCharacterindex);

	if (iWhospeak == sti(pchar.index))
	{
		if (iRelation == RELATION_ENEMY)
		{
			totalinfo = XI_ConvertString("Speak_1");
			if (SPEAK_DEBUG) trace("etape relenn speak");
		}
		if (iRelation == RELATION_FRIEND)
		{
			totalinfo = XI_ConvertString("Speak_2");
			if (SPEAK_DEBUG) trace("etape relami speak");

			if(CheckAttribute(rSpeakCharacter, "issmuggler"))
			{
				totalinfo = XI_ConvertString("Speak_smg");
			}
		}
		if (iRelation == RELATION_NEUTRAL)
		{
			totalinfo = XI_ConvertString("Speak_3");
			if (SPEAK_DEBUG) trace("etape relneutre speak");
			if(CheckAttribute(rSpeakCharacter, "issmuggler"))
			{
				totalinfo = XI_ConvertString("Speak_smg");
			}
		}
	}
	else
	{
		totalinfo = XI_ConvertString("Speak_23");
		if (SPEAK_DEBUG) trace("etape speak_23 speak");
	}
}

void CalculateNews()
{
	string sText = "";
	SetFormatedText("INFO_TEXT", "");

	DeleteAttribute(&GameInterface,"INFO_TEXT");

	int iColor = argb(255,255,255,255);
	int iAnswerColor = argb(255,255,255,255);

	if(!CheckAttribute(rSpeakCharacter, "speak.news"))
	{
		sText = SelectRumourExSpecial("capitan", rSpeakCharacter);
		iColor = argb(255,255,192,255);
	}
	else
	{
		sText = XI_ConvertString("Speak_No_News");
		//SetSelectable("B_NEWS", false);
		iAnswerColor = argb(255,128,128,128);
	}

	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 0,&sText);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 8,-1,iColor);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8, 0, iAnswerColor);
}

void ExitNews()
{
	SetNodeUsing("B_OK_NEWS",false);
	ProcessShowMainMenu();
}

void ProcessHideMainMenu()
{
	SetNodeUsing("B_NEWS",false);
	SetNodeUsing("B_RANSOM",false);
	SetNodeUsing("B_CAPTURE",false);
	SetNodeUsing("B_TAX",false);
	SetNodeUsing("B_CANCEL",false);
	SetNodeUsing("B_TRADE",false);
}

void ProcessShowMainMenu()
{
	SetNodeUsing("B_NEWS",true);
	SetNodeUsing("B_RANSOM",true);
	SetNodeUsing("B_CAPTURE",true);
	SetNodeUsing("B_TAX",true);
	SetNodeUsing("B_CANCEL",true);
	SetNodeUsing("B_TRADE",true);

	totalinfo = XI_ConvertString("Speak_4");

	SetFormatedText("INFO_TEXT",totalInfo);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 1, "B_NEWS");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "B_RANSOM");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "B_CAPTURE");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "B_TAX");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "B_CANCEL");

	SetCurrentNode("B_CANCEL");

	if (iWhoSpeak == 1)
	{
		SetSelectable("B_RANSOM",false);
		SetSelectable("B_CAPTURE",false);
		SetSelectable("B_TAX",false);
	}

	if(isCommander == false)
	{
		SetSelectable("B_TAX",false);
	}

	int iNation = sti(characters[GetCharacterIndex(sTarget)].nation);

	if (GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
	{
		SetSelectable("B_TRADE",true);
	}
	else
	{
		SetSelectable("B_TRADE",false);
	}
}

void AskForRansom()
{
	if (SPEAK_DEBUG) trace("etape demande_ranc speak");
	string sText = "";
	string sAnswerText = "";
	SetFormatedText("RANSOM_ANSWERS", sAnswerText);

	if (!isRansom)
	{
		isRansom = CalculateForRansom(rSpeakCharacter);
	}

	SetNodeUsing("ANSWERS", false);
	SetNodeUsing("RANSOM_ANSWERS", true);

	int iColor = argb(255,255,255,128);

	if(isRansom == true)
	{
		sText = XI_ConvertString("Speak_7");
		sText = sText + FormatMoneyString(CalculateSumm(rSpeakCharacter));
		sText = sText + "\n" + XI_ConvertString("Speak_8");

		sAnswerText = " " + XI_ConvertString("Yes");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		sAnswerText = " " + XI_ConvertString("No");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 8,0,iColor);
		iStringsQuantity = 2;
	}
	else
	{
		sText = XI_ConvertString("Speak_10");
		sAnswerText = " " + XI_ConvertString("Cancel");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 8,0,iColor);
		iStringsQuantity = 1;
	}

	SetCurrentNode("RANSOM_ANSWERS");

	SetFormatedText("INFO_TEXT", sText);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	if(!CheckAttribute(rSpeakCharacter, "speak.ransom.asked"))
	{
		rSpeakCharacter.speak.ransom.asked = 1;
		int iNation = sti(rSpeakCharacter.nation);
		ChangeCharacterReputation(pchar, -1);// iNation);
	}
}

void DisAgreeRansom()
{
	if (SPEAK_DEBUG) trace("etape 1 speak");
	iStringsQuantity = 5;
	SetNodeUsing("ANSWERS", true);
	SetNodeUsing("RANSOM_ANSWERS", false);
	SetCurrentNode("ANSWERS");
	CalculateInfoData();

	SetFormatedText("INFO_TEXT",totalInfo);

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	sGlobalMode = "";

	if(!CheckAttribute(rSpeakCharacter, "last_speak"))
	{
		rSpeakCharacter.last_speak = 90;  //ask again in 90 ticks?
	}
}

void AgreeRansom()
{
	if (SPEAK_DEBUG) trace("etape 2 speak");

	int iSumm = CalculateSumm(rSpeakCharacter);

	iStringsQuantity = 5;
	SetNodeUsing("ANSWERS", true);
	SetNodeUsing("RANSOM_ANSWERS", false);
	SetCurrentNode("ANSWERS");

	string sText = "";
	sText = XI_ConvertString("Speak_13");
	SetFormatedText("INFO_TEXT", sText);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);
	rSpeakCharacter.speak.ransom.taked = 1;
	SetDefaultColorsForAnswers();
	SetSelectedColorsForAnswers(2);

	iFlag = NEUTRAL;

	AddMoneyToCharacter(pchar, iSumm);
}

void AskForCapture()
{
	bool bResult;

	bResult = CalculateForCapture(rSpeakCharacter);
	string sText = "";

	if (bResult == true)
	{
		sText = XI_ConvertString("Speak_18");
		iFlag = CAPTURE;
		rSpeakCharacter.speak.capture = 1;
	}
	else
	{
		sText = XI_ConvertString("Speak_19");
	}

	SetFormatedText("INFO_TEXT",sText);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetDefaultColorsForAnswers();
	SetSelectedColorsForAnswers(3);
}

void exitCapture()
{
	characters[GetCharacterIndex(sTarget)].ransom = 3;
	SetNodeUsing("B_NOT_OK_CAPTURE",false);
	ProcessShowMainMenu();
}

void OkCapture()
{
	Ship_Surrender(GetCharacterIndex(sTarget));
	ProcessCancelExit();
	//IDoExit(RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE, false);
}

void AskForTax()
{
	if (SPEAK_DEBUG) trace("etape demande_taxe speak");

	sGlobalMode = "tax";
	string sText = XI_ConvertString("Speak_23");

	int iEnemyLeadership = sti(rSpeakCharacter.skill.leadership);
	int iEnemyRank = sti(rSpeakCharacter.rank);
	int iOurLeadership = GetSummonSkillFromName(pchar, SKILL_LEADERSHIP);

	ref refOwnShip = GetRealShip(sti(pchar.ship.type));
	int iShipClass = sti(refOwnShip.Class);

	int iTax = sti(pchar.rank) * 10 + iEnemyRank * 10 + (SHIP_CLASS_7 - iShipClass)*100;

	string sNation = GetNationNameByType(sti(rSpeakCharacter.nation));
	if (SPEAK_DEBUG) trace("etape 4 speak");

	if(CheckAttribute(pchar, "bounty."+sNation+".money"))
	{
		if(sti(pchar.bounty.(sNation).money) > 0)
		{
			iTax = iTax + sti(pchar.bounty.(sNation).bounty);
		}
	}
	SetNodeUsing("ANSWERS", false);
	SetNodeUsing("RANSOM_ANSWERS", true);

	sText = sText + FormatMoneyString(iTax);

	SetFormatedText("INFO_TEXT",sText);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	string sAnswerText = "";
	SetFormatedText("RANSOM_ANSWERS", sAnswerText);

	int iColor = argb(255,255,255,128);

	int iMoney = sti(pchar.money);
	if(iMoney >= iTax)
	{
		sAnswerText = " " + XI_ConvertString("Yes");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		sAnswerText = " " + XI_ConvertString("No");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 8,0,iColor);
		iStringsQuantity = 2;
	}
	else
	{
		sAnswerText = " " + XI_ConvertString("Cancel");
		SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 0,&sAnswerText);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 8,0,iColor);
		iStringsQuantity = 1;
	}
	SetCurrentNode("RANSOM_ANSWERS");
}

void OkTax()
{
	if (SPEAK_DEBUG) trace("etape 5 speak");
	int iEnemyLeadership = sti(rSpeakCharacter.skill.leadership);
	int iEnemyRank = sti(rSpeakCharacter.rank);
	int iOurLeadership = GetSummonSkillFromName(pchar, SKILL_LEADERSHIP);

	ref refOwnShip = GetRealShip(sti(pchar.ship.type));
	int iShipClass = sti(refOwnShip.Class);

	int iTax = sti(pchar.rank) * 10 + iEnemyRank * 10 + (SHIP_CLASS_7 - iShipClass) * 100;

	string sNation = GetNationNameByType(sti(rSpeakCharacter.nation));

	if(CheckAttribute(pchar, "bounty."+sNation+".money"))
	{
		if(sti(pchar.bounty.(sNation).money) > 0)
		{
			iTax = iTax + sti(pchar.bounty.(sNation).bounty);
		}
	}
	AddMoneyToCharacter(pchar, -iTax);
	characters[GetCharacterIndex(sTarget)].speak.tax = 1;

	iFlag = TAX;
	if (SPEAK_DEBUG) trace("etape 5 speak");
	ShipGoFreeAsk();// Philippe
	DisAgreeRansom();
	//AgreeRansom();
}

void Trade()
{
	FillShipStore(rSpeakCharacter);
	pchar.shiptrade.character = rSpeakCharacter.id;
	IDoExit(RC_INTERFACE_SPEAK_EXIT_AND_TRADE, true);
}

void FTChange()
{
	string sTemp = GetEventData();
	float fNewPos = GetEventData();
	int iStep = 0;
	int iColor = argb(255,255,255,255);
	float fStep = 0.0;

	if(sTemp == "ANSWERS")
	{
		fStep = iStringsQuantity * fNewPos;
		fStep = fStep + 0.5;
		iStep = sti(fStep);

		SetDefaultColorsForAnswers();
		SetSelectedColorsForAnswers(iStep);

		SetCurrentNode("ANSWERS");
	}

	if(sTemp == "RANSOM_ANSWERS")
	{
		fStep = iStringsQuantity * fNewPos;
		fStep = fStep + 0.5;
		iStep = sti(fStep);
		SetCurrentNode("RANSOM_ANSWERS");
	}
}

void SetSelectedColorsForAnswers(int iStep)
{
	int iColor = argb(255,255,255,128);

	if(CheckAttribute(rSpeakCharacter, "speak.capture"))
	{
		iColor = argb(255,128,128,128);
		for(int i = 0; i <= iStringsQuantity - 1; i++)
		{
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,i,iColor);
		}
		return;
	}

	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,iStep,iColor);

	int iRelation = GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex);
	if(iRelation != RELATION_ENEMY && iStep == 4)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,4,iColor);
	}
	if(iRelation == RELATION_ENEMY && iStep == 0)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,0,iColor);
	}
	if(iRelation == RELATION_ENEMY && iStep == 1)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,1,iColor);
	}
	if(iRelation != RELATION_ENEMY && iStep == 2)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,2,iColor);
	}
	if(iRelation != RELATION_ENEMY && iStep == 3)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,3,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.news") && iStep == 0)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,0,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.ransom.taked") && iStep == 2)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,2,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.ransom") && iStep == 1)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,1,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.ransom") && iStep == 3)
	{
		iColor = argb(255,192,192,192);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,3,iColor);
	}
}

void SetDefaultColorsForAnswers()
{
	int iColor = argb(255,255,255,255);

	if(CheckAttribute(rSpeakCharacter, "speak.capture"))
	{
		iColor = argb(255,128,128,128);
	}
	for(int i = 0; i <= iStringsQuantity; i++)
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,i,iColor);
	}
	int iRelation = GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex);
	if(iRelation != RELATION_ENEMY)
	{
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,4,iColor);
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,2,iColor);
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,3,iColor);
	}
	else
	{
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,0,iColor);
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,1,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.news"))
	{
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,0,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.ransom.taked"))
	{
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,2,iColor);
	}
	if(CheckAttribute(rSpeakCharacter, "speak.ransom"))
	{
		iColor = argb(255,128,128,128);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,1,iColor);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,3,iColor);
	}
	iColor = argb(255,255,255,255);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 8,5,iColor);
}

void RecognizeAnswer()
{
	int iStep = SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"ANSWERS", 11);
	switch(iStep)
	{
		case 0:
			if (SPEAK_DEBUG) trace("case_0");
			if(!CheckAttribute(rSpeakCharacter, "speak.capture"))
			{
				if(!CheckAttribute(rSpeakCharacter, "speak.news"))
				{
					if(GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex) != RELATION_ENEMY)
					{
						CalculateNews();
						if (SPEAK_DEBUG) trace("etape recoansw1 speak");
					}
				}
			}
		break;
		case 1:
			if (SPEAK_DEBUG) trace("case_1");
			if(!CheckAttribute(rSpeakCharacter, "speak.capture"))
			{
				if(!CheckAttribute(rSpeakCharacter, "speak.ransom"))
				{
					if(GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex) != RELATION_ENEMY)
					{
						Trade();
						if (SPEAK_DEBUG) trace("etape recoansw2 speak");
					}
				}
			}
		break;
		case 2:
			if (SPEAK_DEBUG) trace("case_2");
			if(!CheckAttribute(rSpeakCharacter, "speak.capture"))
			{
				if(!CheckAttribute(rSpeakCharacter, "speak.ransom.taked"))
				{
					//AskForRansom();
					if(GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex) == RELATION_ENEMY)
					{
						AskForRansom();
						if (SPEAK_DEBUG) trace("etape recoansw3 speak");
					}
				}
			}
		break;
		case 3:
			if (SPEAK_DEBUG) trace("case_3");
			if(!CheckAttribute(rSpeakCharacter, "speak.capture"))
			{
				if(GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex) == RELATION_ENEMY)
				{
					AskForCapture();
					if (SPEAK_DEBUG) trace("etape recoansw4 speak");
				}
			}
		break;
		case 4:
			if (SPEAK_DEBUG) trace("case_4");
			if(GetRelation(sti(rSpeakCharacter.index), nMainCharacterIndex) == RELATION_ENEMY)
			{
				AskForTax();
				if (SPEAK_DEBUG) trace("etape recoansw5 speak");
			}
		break;
		case 5:
			if (SPEAK_DEBUG) trace("case_5");
			if(!CheckAttribute(rSpeakCharacter, "speak.capture"))
			{
				ProcessCancelExit();
				//ShipGoFreeAsk();// Philippe
				if (SPEAK_DEBUG) trace("etape recoansw6 speak");
			}
			else
			{
				OkCapture();
				if (SPEAK_DEBUG) trace("etape recoansw7 speak");
			}
		break;
    }
}

void ShipGoFreeAsk()
{
	//  int xi_refCharacter;
	//  rSpeakCharacter = GetCharacter(NPC_GenerateCharacter(rSpeakCharacter.id + "_free", "off_hol_2", "man", "man", 60, sti(rSpeakCharacter.nation), 0, true));
	//#20171207-01 remove unused variables
	//int iEnemyLeadership = sti(rSpeakCharacter.skill.leadership);// Dernier ajout
	//int iEnemyRank = sti(rSpeakCharacter.rank);// Dernier ajout

	//sld = rSpeakCharacter; derniere modif
	//   CopyAttributes(rSpeakCharacter, sld);
	//#20171207-01 remove unused variables
	//ChangeAttributesFromCharacter(rSpeakCharacter, refEnemyCharacter, false);//rSpeakCharacter au lieu de sld

	rSpeakCharacter.Abordage.Enable    = false; //rSpeakCharacter au lieu de sld

	SetCharacterRelationBoth(sti(rSpeakCharacter.index), GetMainCharacterIndex(), RELATION_NEUTRAL);//RELATION_FRIEND);
	//#20181101-01
	NationUpdate();
	DoQuestCheckDelay("NationUpdate", 1.5);
}

void RecognizeRansomAnswer()
{
	int iStep = SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"RANSOM_ANSWERS", 11);

	if(sGlobalMode != "tax")
	{
		switch(iStep)
		{
			case 0:
				if(iStringsQuantity == 1)
				{
					DisAgreeRansom();
					if (SPEAK_DEBUG) trace("etape 7 speak");
				}
				else
				{
					AgreeRansom();
					if (SPEAK_DEBUG) trace("etape 8 speak");
				}
			break;
			case 1:
				DisAgreeRansom();
				if (SPEAK_DEBUG) trace("etape 9 speak");
			break;
		}
	}
	else
	{
		switch(iStep)
		{
			case 0:
				if(iStringsQuantity == 1)
				{
					DisAgreeRansom();
					if (SPEAK_DEBUG) trace("etape 10 speak");
				}
				else
				{
					OkTax();
					if (SPEAK_DEBUG) trace("etape 11 speak");
				}
			break;
			case 1:
				DisAgreeRansom();
				if (SPEAK_DEBUG) trace("etape 12 speak");
			break;
		}
	}
}
