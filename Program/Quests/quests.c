
#include "quests\quests_abordage.c"
#include "quests\quests_check.c"
#include "quests\quests_movie.c"
#include "quests\characters_task.c"
#include "quests\quests_scenes.c"
#include "quests\quests_reaction.c"
#include "quests\reaction_functions.c"
#include "quests\whisper_line_functions.c"
#include "quests\mainhero_prologues_functions.c"

#event_handler("LocationWaitNihgtEnd","WaitDatePostEventControl");
#event_handler("evntQuestCameraRestore","QuestCameraRestore");
#event_handler("QuestDelayExit","DoQuestDelayExit");
#event_handler("QuitFromWorldMap","ReloadFromWMtoL_complete");
#event_handler(FORT_DESTROYED,"QuestFortDestroyed");
#event_handler(FORT_CAPTURED,"QuestFortCaptured");
#event_handler(SHIP_CAPTURED,"QuestShipCaptured");
#event_handler(EVENT_CHARACTER_GROUPDEAD,"QuestGroupDeath");
#event_handler("wdmCreateMap","QuestsCheck");
#event_handler("evntQuestsCheck","QuestsCheck");
#event_handler("evntQuestComplete","procEvntQuestComplete");

#event_handler("evntQuestUserData","GetQuestUserData");

void QuestsInit()
{
	aref postEvDelay, arTmp;
	makearef(postEvDelay,pchar.PostEventQuest.questDelay);
	int q = GetAttributesNum(postEvDelay);
	for(int i=0; i<q; i++)
	{
		arTmp = GetAttributeN(postEvDelay,i);
		DoQuestCheckDelay(arTmp.qname, stf(arTmp.delay));
	}

	SetEventHandler(EVENT_CHARACTER_DEAD,"CharacterDeadProcess",0);
	SetEventHandler(EVENT_LOCATION_LOAD,"QuestsCheck_forLocEnter",0);
	SetEventHandler(EVENT_LOCATION_LOAD,"ExecuteLocationEntryActivity",0);
	SetEventHandler(EVENT_LOCATION_UNLOAD,"QC_DoUnloadLocation",0);
	SetEventHandler(EVENT_SEA_LOGIN,"QuestsCheck",0);
	SetEventHandler(EVENT_DIALOG_EXIT,"QuestDialogExitProcedure",0);
	SetEventHandler("NextDay","QuestsCheck",0);
	SetEventHandler(SHIP_DEAD,"QuestsCheck",0);

	SetEventHandler(ABORDAGE_START_EVENT,"QuestAbordageStartEvent",0);
}

void QuestsCheck_forLocEnter()
{
	QC_DoUnloadLocation();
	QuestsCheck();
}

void CharacterDeadProcess()
{
	aref charef = GetEventData();
	ref chref = GetCharacter(sti(charef.index));
	int charType = FindFellowtravellers(pchar,chref);
	switch(charType)
	{
		case FELLOWTRAVEL_COMPANION:
			RemoveCharacterCompanion(pchar,chref);
		break;
		case FELLOWTRAVEL_OFFICER:
			//Log_testInfo("CharacterDeadProcess " + chref.id);
			CheckForReleaseOfficer(sti(chref.index)); // boal 25/06/06 ������� ������������  RemoveOfficersIndex(pchar,sti(chref.index));
			RemovePassenger(pchar,chref);
			//PostEvent(EVENT_CHANGE_OFFICERS, 300);  //fix ��������
		break;
		case FELLOWTRAVEL_PASSENGER:
			RemovePassenger(pchar,chref);
		break;
		case FELLOWTRAVEL_CAPTIVE:
			RemovePassenger(pchar,chref);
		break;
	}
	QuestsCheck();
}

//*****************************************************
// Quest information utilite
//*****************************************************
aref GetQuestData(string idQuest)
{
	aref qdat;
	makearef(qdat,pchar.QuestInfo.(idQuest));
	return qdat;
}
bool CheckQuestRecordEx(aref qref,string textId,string RefQuestID)
{
	string str_date, str_text, str_refquest;
	aref arTextList,arCurText;
	int n,q;

	if( CheckAttribute(qref,"Text") )
	{
		trace("Text found");
		makearef(arTextList,qref.Text);
		q = GetAttributesNum(arTextList);
		for(n=0; n<q; n++)
		{
			arCurText = GetAttributeN(arTextList,n);
			GetDateAndText( GetAttributeValue(arCurText), &str_date,&str_text,&str_refquest );
			if(textId==str_text && RefQuestID==str_refquest) 
			{
				trace("Text found again");
				return true;
			}
		}
	}
	trace("Text NOT found again");
	return false;
}
bool CheckQuestRecord(aref qref,string textId)
{
	return CheckQuestRecordEx(qref,textId,textId);
}

void GetDateAndText(string srcText, ref dstDate, ref dstText, ref dstRefQuest)
{
	dstDate = "";
	dstText = "";
	dstRefQuest = "";
	if(srcText=="") return;
	dstText = srcText;
	int nSrcSize = strlen(srcText);
	int nI1 = -1;
	int nI2 = -1;
	int nI3 = -1;
	nI1 = findSubStr(srcText,"@",0);
	if( nI1>=0 && nI1<nSrcSize-1 ) nI2 = findSubStr(srcText,"@",nI1+1);
	if( nI2>=0 && nI2<nSrcSize-1 ) nI3 = findSubStr(srcText,"@",nI2+1);

	if( nI1<0 || nI2<0 ) return;
	if( nI3<0 )
	{
		dstDate = strcut(srcText,nI1+1,nI2-1);
		dstText = strcut(srcText,nI2+1,nSrcSize-1);
		return;
	}
	else
	{
		dstRefQuest = strcut(srcText,nI1+1,nI2-1);
		dstDate = strcut(srcText,nI2+1,nI3-1);
		dstText = strcut(srcText,nI3+1,nSrcSize-1);
	}
}

void SetQuestHeader(string idQuest)
{
	SetQuestHeaderEx(idQuest,idQuest);
}
void SetQuestHeaderBottom(string idQuest)
{
	if(!CheckAttribute(pchar,"QuestInfo."+idQuest))
	{
		pchar.QuestInfo.(idQuest).Complete = false;
		pchar.QuestInfo.(idQuest).Text = "";
		pchar.QuestInfo.(idQuest).LogName = idQuest;
	}
}

void SetQuestHeaderColor(string idQuest,int color)
{
	if( CheckAttribute(pchar,"QuestInfo."+idQuest) )
	{
		pchar.QuestInfo.(idQuest).color = color;
	}
}
// boal ->
void DeleteQuestHeaderColor(string idQuest)
{
	if( CheckAttribute(pchar,"QuestInfo."+idQuest) )
	{
		DeleteAttribute(pchar,"QuestInfo."+idQuest+ ".color");
	}
}
// boal <-
void SetQuestHeaderEx(string idQuest, string logName)
{
	if(!CheckAttribute(pchar,"QuestInfo."+idQuest))
	{
		object refNewAttr;
		refNewAttr.(idQuest).Complete = false;
		refNewAttr.(idQuest).Text = "";
		refNewAttr.(idQuest).LogName = logName;

		aref refOldAttr; makearef(refOldAttr,pchar.QuestInfo);
		string qName;
		aref curQ, newQ,oldQ;
		int iMax = GetAttributesNum(refOldAttr); //fix
		for(int i=0; i<iMax; i++)
		{
			curQ = GetAttributeN(refOldAttr,i);
			qName = GetAttributeName(curQ);
			refNewAttr.(qName) = "";
			makearef(newQ,refNewAttr.(qName));
			makearef(oldQ,refOldAttr.(qName));
			CopyAttributes(newQ,oldQ);
		}
		CopyAttributes(refOldAttr,&refNewAttr);
	}
}

string GetQuestBookData()
{
	string sData = GetDateString();
	string sResult = sData + " " + GetTimeString();
	return sResult;
}
// boal -->	  
void ReOpenQuestHeader(string idQuest)
{
	ref mainCh = GetMainCharacter();
	if (CheckAttribute(mainCh,"QuestInfo."+idQuest))// && sti(mainCh.QuestInfo.(idQuest).Complete) == true)
	{
        object refNewAttr;
        aref   curQ, newQ,oldQ;

        refNewAttr.(idQuest) = "";
        makearef(curQ, refNewAttr.(idQuest));
        
        CopyAttributes(curQ, GetQuestData(idQuest));
    	refNewAttr.(idQuest).Complete = false;
    	DeleteAttribute(mainCh,"QuestInfo."+idQuest);
    	
		aref refOldAttr; makearef(refOldAttr, mainCh.QuestInfo);
		string qName;
		int iMax  = GetAttributesNum(refOldAttr);
		for(int i=0; i<iMax; i++)
		{
			curQ = GetAttributeN(refOldAttr,i);
			qName = GetAttributeName(curQ);
			refNewAttr.(qName) = "";
			makearef(newQ,refNewAttr.(qName));
			makearef(oldQ,refOldAttr.(qName));
			CopyAttributes(newQ,oldQ);
		}
		CopyAttributes(refOldAttr,&refNewAttr);
	}
}
//������ ���� � ������� dd.mm.yyyy
string GetCurrentDate()
{
	return GetStringDate(GetDataDay(), GetDataMonth(), GetDataYear());
}

string GetQuestBookDataDigit()
{
	string result = "";

	result = GetTimeString() + " " + GetCurrentDate();

    return result;
}
string GetDateString()
{
    int iMonth =GetDataMonth();
	string sData;
	
	//� ������ ���� � ������ ������ ���
	if (Pchar.questTemp.WhisperLine != true)
	{
		sData = GetDataDay()+" "+XI_ConvertString("target_month_" + iMonth)+" "+GetDataYear();
	}
	else
	{
		sData = GetDataDay()+" "+XI_ConvertString("target_month_" + iMonth)+" "+2077;
	}
	return sData;
}
string GetTimeString()
{
    string sTime;
	string sHour = sti(worldMap.date.hour);
	string sMinuts = sti(worldMap.date.min);
	string sAdd = "";
	if(LanguageGetLanguage() == "RUSSIAN")
	{
		if(sti(sHour) < 10)
		{
			sHour = "0" + sHour;
		}
		if(sti(sMinuts) < 10)
		{
			sMinuts = "0" + sMinuts;
		}
	}
	else
	{
		if(sti(sHour) > 12)
		{
			sHour = (24 - sti(sHour));
			sAdd = " PM";
		}
		else
		{
			sAdd = " AM";
		}

		if(sti(sHour) < 10)
		{
			sHour = "0" + sHour;
		}
		if(sti(sMinuts) < 10)
		{
			sMinuts = "0" + sMinuts;
		}
	}

	sTime = sHour + ":" + sMinuts;
	return sTime;
}
// boal <--
void AddQuestUserDataForTitle(string idQuest, string strID, string strData)
{
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false)
	{
		SetQuestHeader(idQuest);
	}
	string tmpStr = "";
	if( CheckAttribute(pchar,"QuestInfo."+idQuest+".UserData") )
	{
		tmpStr = pchar.QuestInfo.(idQuest).UserData;
	}
	pchar.QuestInfo.(idQuest).UserData = tmpStr + "@<"+strID+">" + strData;
}
void AddQuestUserData(string idQuest, string strID, string strData)
{
	if( CheckAttribute(pchar,"QuestInfo."+idQuest+".Text") == false ) return;
	aref arList; makearef( arList, pchar.QuestInfo.(idQuest).Text );
	int n = GetAttributesNum(arList) - 1;
	if( n < 0 ) return;
	aref arCur = GetAttributeN(arList,n);

	string tmpStr = "";
	if( CheckAttribute(arCur,"UserData") ) {
		tmpStr = arCur.UserData;
	}
	arCur.UserData = tmpStr + "@<"+strID+">" + strData;
}
string usrQuestData;
ref GetQuestUserData()
{
	string questID = GetEventData();
	int nRecordNum = GetEventData();
	usrQuestData = "";
	// not found quest - empty user data
	if( !CheckAttribute(pchar,"QuestInfo."+questID) ) {return &usrQuestData;}
	// title user data
	if( nRecordNum<0 ) {
		if( CheckAttribute(pchar,"QuestInfo."+questID+".UserData") ) {
			usrQuestData = pchar.QuestInfo.(questID).UserData;
		}
		return &usrQuestData;
	}
	// record user data
	string sRecLbl = "l" + nRecordNum;
	if( CheckAttribute(pchar,"QuestInfo."+questID+".Text."+sRecLbl+".UserData") ) {
		usrQuestData = pchar.QuestInfo.(questID).Text.(sRecLbl).UserData;
	}
	return &usrQuestData;
}
string FindQuestNameByLogName(string logName)
{
	if( CheckAttribute(pchar,"QuestInfo") )
	{
		aref pA;
		makearef( pA, pchar.QuestInfo );
		int attrCount = GetAttributesNum( pA );
		for( int n=0; n<attrCount; n++ )
		{
			aref pCurA = GetAttributeN(pA,n);
			if( CheckAttribute( pCurA, "LogName" ) ) {
				if( pCurA.LogName == logName ) { return GetAttributeName(pCurA); }
			} else {
				if( GetAttributeName(pCurA) == logName ) { return GetAttributeName(pCurA); }
			}
		}
	}
	return "";
}

void AddQuestRecordEx(string idQuest,string idReferenceQuest,string idText)
{
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false)
	{
		SetQuestHeaderEx(idQuest,idReferenceQuest);
	}
	string sTextLbl = "l0";
	//trace("Second Check");
	if( CheckAttribute(pchar,"QuestInfo."+idQuest+".Text") )
	{
		aref arTmp; makearef( arTmp, pchar.QuestInfo.(idQuest) );
		//trace("check: is sTextLbl empty?");
		/*if( CheckQuestRecordEx(arTmp,idText,idReferenceQuest) == true)
		{
			sTextLbl = "";
			//trace("sTextLbl is empty!");
		}
		else
		{*/
			makearef(arTmp,pchar.QuestInfo.(idQuest).Text);
			sTextLbl = "l" + GetAttributesNum(arTmp);
			//trace("sTextLbl is NOT empty!");
		//}
	}
	if( sTextLbl != "" )
	{
		pchar.QuestInfo.(idQuest).Text.(sTextLbl) = "@"+idReferenceQuest+"@"+GetQuestBookData()+"@"+idText;
		Log_SetStringToLog(XI_ConvertString("Logbook Update"));
		AddMsgToCharacter(pchar,MSGICON_LOGBOOK);
		PlayStereoSound("notebook");
		//trace("Quest ADDED");
	}
	// �������� ����� ��
	SetQuestHeaderColor(idQuest, argb(255,255,128,255));
}

// boal ����� ��� ����  -->
void SetQuestHeaderInfo(string idQuest)
{
    string logName = idQuest;
	if(!CheckAttribute(pchar,"QuestInfo."+idQuest))
	{
		pchar.QuestInfo.(idQuest).Complete = false;
		pchar.QuestInfo.(idQuest).Text = "";
		pchar.QuestInfo.(idQuest).LogName = logName;
		pchar.QuestInfo.(idQuest).InfoType = true;
	}
}

void AddQuestRecordInfo(string idQuest, string idText)
{
    string idReferenceQuest = idQuest;
    
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false)
	{
		SetQuestHeaderInfo(idQuest);
	}
	string sTextLbl = "l0";
	if( CheckAttribute(pchar,"QuestInfo."+idQuest+".Text") )
	{
		aref arTmp; makearef( arTmp, pchar.QuestInfo.(idQuest) );
		makearef(arTmp,pchar.QuestInfo.(idQuest).Text);
		sTextLbl = "l" + GetAttributesNum(arTmp);
	}
	if( sTextLbl != "" )
	{
		pchar.QuestInfo.(idQuest).Text.(sTextLbl) = "@"+idReferenceQuest+"@  @"+idText;
	}
}
// boal ����� ��� ���� <--
void AddQuestRecord(string idQuest,string idText)
{
	AddQuestRecordEx(idQuest, idQuest, idText);
}
void CloseQuestHeader(string idQuest)
{
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false) return;
	object questRef;
	CopyAttributes(&questRef,GetQuestData(idQuest));
	questRef.Complete = true;
	DeleteAttribute(pchar,"QuestInfo."+idQuest);
	aref newAttr; makearef(newAttr,pchar.QuestInfo.(idQuest));
	CopyAttributes(newAttr,questRef);
	
	if(idQuest == "GhostShipQuest") UnlockAchievement("Ghostship_quest", 3);
	if(idQuest == "Xebeca_BlueBird") UnlockAchievement("Bluebird_quest", 3);
	if(idQuest == "ISS_MainLine") UnlockAchievement("LSC_quest", 3);
	if(idQuest == "Tenochtitlan") UnlockAchievement("Teno_quest", 3);
	if(idQuest == "ISS_PoorsMurder") UnlockAchievement("Killbeggars_quest", 3);
	if(idQuest == "Romantic_Line") UnlockAchievement("Isabella_quest", 3);
	if(idQuest == "MagicCity") UnlockAchievement("Enchantcity_quest", 3);
	if(idQuest == "BerglarsGang") UnlockAchievement("Berglarsgang_quest", 3);
	if(idQuest == "Fra_Line_12_EndOfWar") UnlockAchievement("Nation_quest_F", 3);
	if(idQuest == "Hol_Line_12_OccupyMaracaibo") UnlockAchievement("Nation_quest_H", 3);
	if(idQuest == "Spa_Line_12_OccupyPortPax") UnlockAchievement("Nation_quest_S", 3);
	if(idQuest == "Pir_Line_8_Panama") UnlockAchievement("Nation_quest_P", 3);
}
bool CheckActiveQuest(string idQuest)
{
	if(CheckAttribute(pchar,"QuestInfo."+idQuest)==false) return false;
	return true;
}
void DeleteQuestHeader(string idQuest)
{
	DeleteAttribute(pchar, "QuestInfo."+idQuest);
}

//**********************************************************************************
// ������� ��� ������ � ��������
//==================================================================================

// ��������� ���� ��������� ������
//-----------------------------------------
bool CheckQuestAttribute(string attributeName, string attributeValue)
{
	if( CheckAttribute(pchar,"quest."+attributeName) )
		return (pchar.quest.(attributeName)==attributeValue);
	return false;
}
// boal -->
bool CheckNPCharQuestAttribute(ref _pchar, string attributeName, string attributeValue)
{
	if( CheckAttribute(_pchar,"quest."+attributeName) )
		return (_pchar.quest.(attributeName)==attributeValue);
	return false;
}
// boal <--

// ������� ���� ��������� ������
//------------------------------------------
void DeleteQuestAttribute(string attributeName)
{
	if( CheckAttribute(pchar,"quest."+attributeName) )
		DeleteAttribute(pchar,"quest."+attributeName);
}

float GetLocatorSqrDistanceToMe(aref locatorRef)
{
	float x,y,z;
	GetCharacterPos(pchar,&x,&y,&z);
	x = stf(locatorRef.x)-x;
	y = stf(locatorRef.y)-y;
	z = stf(locatorRef.z)-z;
	return (x*x+y*y+z*z);
}
bool GetNearLocator(string groupName, ref float_dist, ref findedLocator, float minDistance)
{
	int loadLocationIndex = FindLoadedLocation();
	if(loadLocationIndex==-1) return false;
	ref refLoadLocation; makeref(refLoadLocation,Locations[loadLocationIndex]);
	if(!CheckAttribute(refLoadLocation,"locators."+groupName)) return false;
	aref refLocators; makearef(refLocators,refLoadLocation.locators.(groupName));
	int locatorsCount = GetAttributesNum(refLocators);
	int n;
	aref refCurLocator;
	bool  bYesFind = false;
	float minDist = 4000000.0;
	float curDist;
	for(n=0;n<locatorsCount;n++)
	{
		refCurLocator = GetAttributeN( refLocators, n );
		curDist = GetLocatorSqrDistanceToMe(refCurLocator);
		if(curDist<minDistance) continue;
		if(curDist>=minDist) continue;
		minDist = curDist;
		findedLocator = refCurLocator;
		bYesFind = true;
	}
	return bYesFind;
}

// ���������� ��������� � ��������� ������� ������ goto (�� �� ����� ����������� ���������)
//--------------------------------------------------------------------------------------------
bool SetCharacterToNearLocatorFromMe(string characterID, float minDistance)
{
	int loadLocationIndex = FindLoadedLocation();
	if(loadLocationIndex==-1) return false;
	float dist;
	aref findedLocator;
	if( !GetNearLocator( "goto", &dist, &findedLocator, minDistance) )
	{
		Trace("Can't goto group locators into location "+Locations[loadLocationIndex].id);
		return false;
	}
	ChangeCharacterAddress(CharacterFromID(characterID), Locations[loadLocationIndex].id, GetAttributeName(findedLocator));
	return true;
}

// �������� ������ �� �������� ����� ��� ID-����
//------------------------------------------------------
ref CharacterFromID(string characterID)
{
    int i = GetCharacterIndex(characterID);
    if (i < 0 && MOD_BETTATESTMODE == "On")
	{
		Log_Info("Error: �� ������ ��� � characterID = "+characterID);
		trace("Error: �� ������ ��� � characterID = "+characterID);
	}
    if (i>=0)
    {
        return &characters[i];
    }
    else
    {
        return &NullCharacter;
    }
}

string sPostWaitName;
int postWaitYear,postWaitMonth,postWaitDay,postWaitHour,postWaitMinute;
void WaitDatePostEventControl()
{
	AddDataToCurrent(postWaitYear,postWaitMonth,postWaitDay);
	AddTimeToCurrent(postWaitHour,postWaitMinute);
	if(sPostWaitName!="")	CompleteQuestName(sPostWaitName, "");
	QuestsCheck();
}

// ���������� ��������� ����� � ������ ������
//----------------------------------------------------
void WaitDate(string postName,int year, int month, int day, int hour, int minute)
{
	sPostWaitName = postName;
	postWaitYear = year;
	postWaitMonth = month;
	postWaitDay = day;
	postWaitHour = hour;
	postWaitMinute = minute;
	WaitDatePostEventControl();
}

// ���������� ������ �� �������� ������� ��������� � ������� ����� ����� �������� ����� ������
//---------------------------------------------------------------------------------------------
bool SetCameraToShipView(string characterName, string questCheckName, float viewTimeInSec)
{
	int chrIdx = GetCharacterIndex(characterName);
	if(chrIdx==-1) return false;
	ref chrRef = GetCharacter(chrIdx);

	float xship = stf(chrRef.ship.pos.x);
	float zship = stf(chrRef.ship.pos.z);

	float xchar,ychar,zchar;
	if( false==GetCharacterPos(pchar,&xchar,&ychar,&zchar) ) return false;

	float dx = xchar-xship;
	float dz = zchar-zship;
	float dist = sqrt(dx*dx+dz*dz);
	dx = dx/dist;
	dz = dz/dist;

	float xcam = xchar+dx*6.0;
	float zcam = zchar+dz*6.0;

	PostEvent("evntQuestCameraRestore",makeint(viewTimeInSec*1000),"s",questCheckName);

	return locCameraToPos(xcam,ychar+3.0,zcam,false);
}

void QuestCameraRestore()
{
	string sCameraQuestCheckName = GetEventData();
	locCameraFollow();
	if(sCameraQuestCheckName!="")
	{
		CompleteQuestName(sCameraQuestCheckName, "");
		QuestsCheck();
	}
}

// ������� ��� ������ �� ���� � ������ ������������ ������ �������
//-----------------------------------------------------------------
bool QuestCloseSeaExit()
{
	int locIdx = FindLocation(pchar.location.from_sea);
	if(locIdx==-1) return false;

	aref reloadRef;
	makearef(reloadRef,Locations[locIdx].reload);

	int n = GetAttributesNum(reloadRef);
	aref locRef;
	for(int i=0;i<n;i++)
	{
		locRef = GetAttributeN(reloadRef,i);
		if( FindIsland(locRef.go) != -1 )
		{
			chrEnableReloadLocator(Locations[locIdx].id, locRef.name, false);
		}
	}
	return true;
}

// ������� ��� ������ �� ���� � ������ ������������ ������ �������
//-----------------------------------------------------------------
bool QuestOpenSeaExit()
{
	int locIdx = FindLocation(pchar.location.from_sea);
	if(locIdx==-1) return false;

	aref reloadRef;
	makearef(reloadRef,Locations[locIdx].reload);

	int n = GetAttributesNum(reloadRef);
	aref locRef;
	for(int i=0;i<n;i++)
	{
		locRef = GetAttributeN(reloadRef,i);
		if( FindIsland(locRef.go) != -1 )	chrEnableReloadLocator(Locations[locIdx].id, locRef.name, true);
	}
	return true;
}

// ����� ������� � ������� �� �����
//-----------------------------------
bool FindLocator(string locationName, string locatorName, ref locatorRef, bool fromRealLoadedLocators)
{
	int i,j,n,m,locIdx;
	aref reloadRef,locRef,locGroupRef;

	locIdx = FindLocation(locationName);
	if(locIdx==-1)	return false;

	if(!IsEntity(&Locations[locIdx]) && fromRealLoadedLocators)	return false;

	if(locatorName=="")	return false;

	if(!fromRealLoadedLocators)
	{
		makearef(reloadRef,Locations[locIdx].reload);
		n = GetAttributesNum(reloadRef);
		for(i=0;i<n;i++)
		{
			locRef = GetAttributeN(reloadRef,i);
			if(locRef.name==locatorName)
			{
				locatorRef = locRef;
				return true;
			}
		}
		return false;
	}

	makearef(reloadRef,Locations[locIdx].locators);
	m = GetAttributesNum(reloadRef);
	for(j=0;j<m;j++)
	{
		locGroupRef = GetAttributeN(reloadRef,j);
		n = GetAttributesNum(locGroupRef);
		for(i=0;i<n;i++)
		{
			locRef = GetAttributeN(locGroupRef,i);
			if(GetAttributeName(locRef)==locatorName)
			{
				locatorRef = locRef;
				return true;
			}
		}
	}
	return false;
}

// ��������� �������� �� ���������� � �������� ������� � ������� �������
bool CheckCurLocator(string group,string locator,float x,float y,float z)
{
	int locIdx = FindLoadedLocation();
	if(locIdx==-1) return false;
	if( !CheckAttribute(&Locations[locIdx],"locators."+group+"."+locator) ) return false;
	aref curloc; makearef(curloc,Locations[locIdx].locators.(group).(locator));
	float xloc = makefloat(curloc.x) - x;
	float yloc = makefloat(curloc.y) - y;
	float zloc = makefloat(curloc.z) - z;
	float rad = makefloat(curloc.radius);
	if( rad*rad > xloc*xloc+yloc*yloc+zloc*zloc ) return true;
	else return false;
}

// �������� ���� ������� �� ����� ����� �����������
//---------------------------------------------------
bool ChangeReloadData(string locationName,string locatorName, string toLocationName,string toLocatorName)
{
	aref locRef;
	if( !FindLocator(locationName,locatorName, &locRef, false) )
	{
		return false;
	}

	if(!CheckAttribute(locRef,"old.go")) locRef.old.go = locRef.go;
	if(!CheckAttribute(locRef,"old.emerge")) locRef.old.emerge = locRef.emerge;

	if(toLocationName=="") toLocationName=locRef.go;
	if(toLocatorName=="") toLocatorName=locRef.emerge;

	locRef.go = toLocationName;
	locRef.emerge = toLocatorName;
	return true;
}

// ������� �������� ������ ����� ����������
bool ChangeBackReloadData(string locationName,string locatorName)
{
	aref locRef;
	if( !FindLocator(locationName,locatorName, &locRef, false) ) return false;

	if(CheckAttribute(locRef,"old.go"))	locRef.go = locRef.old.go;
	if(CheckAttribute(locRef,"old.emerge")) locRef.emerge = locRef.old.emerge;

	if(CheckAttribute(locRef,"old"))	DeleteAttribute(locRef,"old");
	return true;
}

// ������� �������� ������ ����� �������� ����� ������
//------------------------------------------------------
//navy --> ��������� ����� ��������� �������
void DoQuestFunctionDelay(string questFunctionName, float delayInSecond)
{
	pchar.PostEventQuest.questDelay.(questFunctionName).function = questFunctionName;
	DoQuestCheckDelay(questFunctionName, delayInSecond);
}
//navy <--

void DoQuestCheckDelay(string questCheckName, float delayInSecond)
{
	bool deleteOldQuest=false;
	if( CheckAttribute(pchar,"quest."+questCheckName) )	deleteOldQuest=true;
	pchar.PostEventQuest.questDelay.(questCheckName).delay = delayInSecond;
	pchar.PostEventQuest.questDelay.(questCheckName).qname = questCheckName;
	PostEvent("QuestDelayExit",makeint(delayInSecond*1000),"sl",questCheckName,deleteOldQuest);
}

void DoQuestDelayExit()
{
	string stmp = GetEventData();
	bool deleteOldQuest = GetEventData();
	
	if (CheckAttribute(pchar, "PostEventQuest.questDelay."+stmp)) //fix boal, ����������� ������� ���������
	{
		if(stmp!="")
		{
			if(deleteOldQuest)
			{
				if( CheckAttribute(pchar,"quest."+stmp) )
				{
					DeleteAttribute(pchar,"PostEventQuest.questDelay."+stmp);
					CompleteQuestName(stmp, "");
					pchar.quest.(stmp).over = "yes";
					QuestsCheck();
					return;
				}
			}
//navy --> ��������� ����� ��������� �������
			if (CheckAttribute(pchar, "PostEventQuest.questDelay." + stmp + ".function"))
			{
				string sFunction = pchar.PostEventQuest.questDelay.(stmp).function;
				call sFunction(stmp);
			}
			else
			{
//navy <--
				CompleteQuestName(stmp, "");
				QuestsCheck();
			}
		}
		DeleteAttribute(pchar,"PostEventQuest.questDelay."+stmp);
	}
}

void ExitActAnimation()
{
	aref apchar = GetEventData();
	if(!CheckAttribute(apchar,"activity.endAnimationQuest")) return;
	ref chref = GetCharacter(sti(apchar.index));
	CharacterPlayAction(chref,"");
	string endAniQuestName = chref.activity.endAnimationQuest.Name;
	DeleteAttribute(chref,"activity.endAnimationQuest");
	if(endAniQuestName!="")
	{
		CompleteQuestName(endAniQuestName, "");
		QuestsCheck();
	}
}

// �������� ��������� ��� ������ � ����� ������� � ������
//--------------------------------------------------------
bool ShipTempRemove(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"TmpShipHolder") ) return false;
	if( !CheckAttribute(_refCharacter,"Ship") ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.TmpShipHolder);
	aref srcRef; makearef(srcRef, _refCharacter.Ship);

	CopyAttributes(dstRef,srcRef);
	return true;
}

// ������������ ������ � ����� ������ ������� �� ������
//------------------------------------------------------
bool RestoreTempRemovedShip(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"TmpShipHolder") ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.Ship);
	aref srcRef; makearef(srcRef, _refCharacter.TmpShipHolder);

	DeleteAttribute(_refCharacter,"Ship");
	CopyAttributes(dstRef,srcRef);
	DeleteAttribute(_refCharacter,"TmpShipHolder");
	return true;
}

// �������� ���� ���������� ���������
//------------------------------------
void ExchangeCharacterShip(ref oneCharacter, ref twoCharacter) // to_do
{
	object tmpObj;
	aref oneShip; makearef(oneShip,oneCharacter.Ship);
	aref twoShip; makearef(twoShip,twoCharacter.Ship);

	CopyAttributes(&tmpObj,oneShip);
	CopyAttributes(oneShip,twoShip);
	CopyAttributes(twoShip,&tmpObj);
}

void QuestProcessDialogExit()
{
	aref one_aref = GetEventData();
	aref two_aref = GetEventData();

	DeleteAttribute(one_aref,"act.disableDialog");
	DeleteAttribute(two_aref,"act.disableDialog");
}

// ������ �����, ����������� ����� ������ �� �������
//---------------------------------------------------
void AddDialogExitQuest(string questName)
{
	string attrName;
	aref ar;

	if( CheckAttribute(pchar,"DialogExitQuests") )
	{
		makearef(ar,pchar.DialogExitQuests);
		attrName = "l" + GetAttributesNum(ar);
	}
	else
	{
		attrName = "l0";
	}
	pchar.DialogExitQuests.(attrName) = questName;
}

void AddDialogExitQuestFunction(string questName) // boal new
{
	string attrName;
	aref ar;

	if( CheckAttribute(pchar,"DialogExitQuests") )
	{
		makearef(ar,pchar.DialogExitQuests);
		attrName = "l" + GetAttributesNum(ar);
	}
	else
	{
		attrName = "l0";
	}
	pchar.DialogExitQuests.(attrName) = questName;
	pchar.DialogExitQuests.(attrName).function = questName; // ����� �������, � �� �����
}

void QuestDialogExitProcedure()
{
	int i = GetEventData();
	ref othepchar = GetCharacter(i);
	aref ar, lref;
	string attrName, Lname;

	// ����� ���� �������� ����� ������ ������
	ExecuteAfterDialogTask(othepchar);
	ExecuteAfterDialogTask(pchar);

	if( CheckAttribute(pchar,"DialogExitQuests") )
	{
		makearef(ar,pchar.DialogExitQuests);
		int iMax = GetAttributesNum(ar); //fix
		for(i=0; i<iMax; i++)
		{
			lref = GetAttributeN(ar,i);
			attrName = GetAttributeValue(lref);
			// boal -->
			Lname = GetAttributeName(lref);
			if (CheckAttribute(pchar, "DialogExitQuests." + Lname + ".function"))
			{
				call attrName();
				/*pchar.quest.(attrName).function = attrName;
			    CompleteQuestName(attrName, attrName);
			    pchar.quest.(attrName).over = "yes"; // ������� �� �����
			    */
			}
			else
			{
			// boal <--
				CompleteQuestName(attrName, "");
			}
			if( CheckAttribute(pchar,"quest."+attrName+".win_condition") )	pchar.quest.(attrName).over = "yes";
		}
		DeleteAttribute(pchar,"DialogExitQuests");
	}

	QuestsCheck();
}

int idxOldLocation = -1;
string sQuestNameAfterReload = "_";
void DoDeleteFakeLocation()
{
	DelEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation");
	if(idxOldLocation!=-1)	DeleteAttribute(&Locations[idxOldLocation],"reload.fake1");
	if(sQuestNameAfterReload!="_")
	{
		CompleteQuestName(sQuestNameAfterReload, "");
		if( CheckAttribute(pchar,"quest."+sQuestNameAfterReload+".win_condition") )
			pchar.quest.(sQuestNameAfterReload).over = "yes";
		QuestsCheck();
		sQuestNameAfterReload = "_";
	}
}

// ����������� �������� ��������� � ������ ������� � �� ���������� ������� �����
//-------------------------------------------------------------------------------
bool DoQuestReloadToLocation(string idLocation, string idGroup, string idLocator, string questName)
{
	if(sQuestNameAfterReload!="_") return false;
	sQuestNameAfterReload = questName;
	// boal -->
    if (bSeaActive && bAbordageStarted) // ��� ������ � ���� � �����
	{
		return DoReloadFromDeckToLocation(idLocation,idGroup,idLocator);
	}
	// boal <--
	if(bSeaActive)
	{
		idxOldLocation = -1;
		SetEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation",0);
		return DoReloadFromSeaToLocation(idLocation,idGroup,idLocator);
	}
	if(IsEntity(worldMap))
	{
		idxOldLocation = -1;
		SetEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation",0);
		return DoReloadFromWorldMapToLocation(idLocation,idGroup,idLocator);
	}
	return DoReloadCharacterToLocation(idLocation,idGroup,idLocator);
}

// Warship -->
bool DoFunctionReloadToLocation(string idLocation, string idGroup, string idLocator, string functionName)
{
	if(sQuestNameAfterReload!="_") return false;
	if(functionName != "")
	{
		PChar.GenQuest.CallFunctionParam = functionName;
		sQuestNameAfterReload = "CallFunctionParam";
	}
	// boal -->
	if (bSeaActive && bAbordageStarted) // ��� ������ � ���� � �����
	{
		return DoReloadFromDeckToLocation(idLocation,idGroup,idLocator);
	}
	// boal <--
	if(bSeaActive)
	{
		idxOldLocation = -1;
		SetEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation",0);
		return DoReloadFromSeaToLocation(idLocation,idGroup,idLocator);
	}
	if(IsEntity(worldMap))
	{
		idxOldLocation = -1;
		SetEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation",0);
		return DoReloadFromWorldMapToLocation(idLocation,idGroup,idLocator);
	}
	return DoReloadCharacterToLocation(idLocation,idGroup,idLocator);
}
// Warship <--

// ����������� �������� ��������� � ������ �������
//-------------------------------------------------------------------------------
bool DoReloadCharacterToLocation(string idLocation, string idGroup, string idLocator)
{
	idxOldLocation = FindLoadedLocation();
	if(idxOldLocation==-1)
	{
		idxOldLocation = 0;
		loadedLocation = &Locations[idxOldLocation];
	}
	else
	{
		if(Locations[idxOldLocation].id!=loadedLocation.id)
		{
			trace("WARNING!!! FindLocation is not same loadedLocation");
			if(IsEntity(loadedLocation))
			{	idxOldLocation = FindLocation(loadedLocation.id);
			}
		}
	}
	Locations[idxOldLocation].reload.fake1.name = "fakeReload";
	Locations[idxOldLocation].reload.fake1.go = idLocation;
	Locations[idxOldLocation].reload.fake1.emerge = idLocator;
	aref rloc;
	if( FindLocator ( pchar.location, pchar.location.locator, &rloc, true ) )
	{
		Event("Location_CharacterExitFromLocator","aassf", rloc,pchar, pchar.location.group,pchar.location.locator, 1.0);
	}

	SetEventHandler(EVENT_LOCATION_LOAD,"DoDeleteFakeLocation",0);
	return TeleportCharacterFromCurLocationToLocation("fakeReload",idGroup,idLocator);
}

// ����������� �������� ��������� � ������ ������� �� ����� ����
//-------------------------------------------------------------------------------
bool DoReloadFromWorldMapToLocation(string idLocation, string idGroup, string idLocator)
{
	// ����� ���� �3 -->
	worldMap.old = "";
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);

	WdmPrepareMapForAbordage(arOldMapPos);
	// ����� ���� �3 <--
	
	if(FindLocation(idLocation)==-1) return false;
	pchar.tmpWDMtoLand.location = idLocation;
	pchar.tmpWDMtoLand.group = idGroup;
	pchar.tmpWDMtoLand.locator = idLocator;
	QuitFromWorldMap();
	return true;
}
void ReloadFromWMtoL_complete()
{
	if( !CheckAttribute(pchar,"tmpWDMtoLand") ) return;
	//ChangeCharacterAddressGroup( pchar, pchar.tmpWDMtoLand.location, pchar.tmpWDMtoLand.group, pchar.tmpWDMtoLand.locator );
	//LoadLocation(&Locations[FindLocation(pchar.tmpWDMtoLand.location)]);
	DoReloadCharacterToLocation(pchar.tmpWDMtoLand.location, pchar.tmpWDMtoLand.group, pchar.tmpWDMtoLand.locator);  // boal ���� ���� ��������

	if(CheckAttribute(pchar, "tmpWDMtoLand"))
	{
		if(FindIsland(pchar.tmpWDMtoLand.location) != -1)
		{
			pchar.ComeToIsland = "1";
			QuestsCheck();
		}
	}
	DeleteAttribute(pchar,"tmpWDMtoLand");   //fix boal
}

// ����������� �������� ��������� � ������ ������� �� ����
//-------------------------------------------------------------------------------
bool DoReloadFromSeaToLocation(string idLocation, string idGroup, string idLocator)
{
	
	if(bSeaActive)	{ DeleteSeaEnvironment(); }
	else {bSkipSeaLogin = true;}

	pchar.tmpWDMtoLand.location = idLocation;
	pchar.tmpWDMtoLand.group = idGroup;
	pchar.tmpWDMtoLand.locator = idLocator;

	SetEventHandler("FaderEvent_EndFade", "EndReloadToLocation", 0);
	CreateEntity(&reload_fader, "fader");
	if(IsEntity(&reload_fader) == 0) Trace("Reload fader not created!!!");
	float fadeOutTime = 0.5;
	SendMessage(&reload_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&reload_fader, "l", FADER_STARTFRAME);
	return true;
}
void EndReloadToLocation()
{
	DelEventHandler("FaderEvent_EndFade", "EndReloadToLocation");
	ReloadFromWMtoL_complete();
}
// boal 02.09.06 �������� � ���� � ����� � ���� �� ���� -->
void DoReloadFromDeckToLocation(string idLocation, string idGroup, string idLocator)
{
	if(idLocation != "")
	{
        Return2SeaClearNPC();
        ResetSound(); // new
		PauseAllSounds();
        if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
        boarding_location = -1;
		//�������� ���������
		Log_SetActiveAction("Nothing");
		EndBattleLandInterface();
		
		//����������� � ���������
		LAi_boarding_process = false;
	
		Go2LocationAfterAbordage();
        DoReloadFromSeaToLocation(idLocation, idGroup, idLocator);
	}
}
// boal <--
// ������� ����� �� ������ ����������� �������
//---------------------------------------------
void DeleteQuestCheck(string sQuestName)
{
	if(sQuestName=="") return;
	if( CheckAttribute(pchar,"quest."+sQuestName+".win_condition") )	
	{
		pchar.quest.(sQuestName).over = "yes";
	}
}

// �������� ������ ��� ���������
//----------------------------------
string GetCharacterFullName(string idCharacter)
{
	int idxCh = GetCharacterIndex(idCharacter);
	if(idxCh==-1) return "";
	ref chref = GetCharacter(idxCh);

	return GetFullName(chref);
}
// boal -->
string GetFullName(ref chref)
{
	string retStr = "";
	
	if(CheckAttribute(chref,"name"))
	{
		if (chref.name != "") retStr = chref.name;
	}
	if(CheckAttribute(chref,"middlename"))
	{
	    if (chref.middlename != "") retStr = retStr + " " + chref.middlename;
	}
	if(CheckAttribute(chref,"lastname"))
	{
	    if (chref.lastname != "") retStr = retStr + " " + chref.lastname;
	}
	
	return retStr;
}
// boal <--
// ��������� ��������� � ���������� �� ��������� ���������� � �������� ������� �� ����
//-------------------------------------------------------------------------------------
// to_do ����� ������, ��������� ���������, �� ���� �����������, ����������� ��������� ������ � ������� ���� ������� RestorePassengers, ����� ������ ���������� � ���
bool StorePassengers(string idCharacter)
{
	int idxCh = GetCharacterIndex(idCharacter);
	if(idxCh==-1) return false;
	ref refCh = GetCharacter(idxCh);
 	// ���� ������� ������ ��� if(CheckAttribute(refCh,"Fellows.Old")) return false;
    DeleteAttribute(refCh,"Fellows.Old");

	string sTmp;
	aref arTmp;
	int i,idx;
	// �������� ��������
	makearef(arTmp,refCh.Fellows.Old.Officers);
	for(i=1; i<4; i++)
	{
		idx = GetOfficersIndex(refCh,i);
		if(idx==-1) continue;
		sTmp = "id"+i;
		arTmp.(sTmp) = idx;
	}
	// �������� ����������
	makearef(arTmp,refCh.Fellows.Old.Passengers);
	for(i=0; GetPassengersQuantity(refCh)>0; i++)
	{
		idx = GetPassenger(refCh,0);
		if(idx==-1) break;
		sTmp = "id"+i;
		arTmp.(sTmp) = idx;
		RemovePassenger(refCh,GetCharacter(idx));
		ChangeCharacterAddress(GetCharacter(idx),"none","");
	}
	return true;
}

// ������������ ����������� ����� ���������� � �� ����������� ��������
//----------------------------------------------------------------------
bool RestorePassengers(string idCharacter)
{
	int idxCh = GetCharacterIndex(idCharacter);
	if(idxCh==-1) return false;
	ref refCh = GetCharacter(idxCh);
	if(!CheckAttribute(refCh,"Fellows.Old")) return false;

	int i,idx;
	aref arTmp,arCur;
	// �������������� ����������
	makearef(arTmp,refCh.Fellows.Old.Passengers);
	for(i=0; i<GetAttributesNum(arTmp); i++)
	{
		arCur = GetAttributeN(arTmp,i);
		idx = sti(GetAttributeValue(arCur));
		AddPassenger(refCh,GetCharacter(idx),false);
	}
	// �������������� ��������
	makearef(arTmp,refCh.Fellows.Old.Officers);
	for(i=0; i<GetAttributesNum(arTmp); i++)
	{
		arCur = GetAttributeN(arTmp,i);
		idx = sti(GetAttributeValue(arCur));
		if(idx==-1) continue;
		SetOfficersIndex(refCh,-1,idx);
	}

	// �������� ���������� ��������� ����������
	DeleteAttribute(refCh,"Fellows.Old");
	return true;
}

// ������� �� ������ ������ ���������
//--------------------------------------
bool StartLookAfterCharacter(string idCharacter)
{
	int chIdx = GetCharacterIndex(idCharacter);
	if(chIdx==-1) return false;

	CharacterTurnByChr(GetMainCharacter(),GetCharacter(chIdx));
	SetEventHandler("evntLookAfterCharacter","LookAfterCharacterProc",0);
	PostEvent("evntLookAfterCharacter",100,"l",chIdx);
	return true;
}
void LookAfterCharacterProc()
{
	int idxCh = GetEventData();
	CharacterTurnByChr(GetMainCharacter(),GetCharacter(idxCh));
	PostEvent("evntLookAfterCharacter",100,"l",idxCh);
}

// ���������� �������� �� ��������
//-----------------------------------
void EndLookAfterCharacter()
{
	DelEventHandler("evntLookAfterCharacter","LookAfterCharacterProc");
}

// ������������ �������� (�� ������, ���� �� ��� �� ����� ����)
bool ReanimateCharacter(string characterID)
{
	int idx = GetCharacterIndex(characterID);
	if(idx==-1)
	{
		trace("Not found character for function : ReanimateCharacter(" + characterID + ")");
		return false;
	}
	ref chref = GetCharacter(idx);
	LAi_SetCurHP(chref,LAi_GetCharacterMaxHP(chref));
	return true;
}

//extern void SetRandomNameToCharacter(ref chref);
// ���������� ��������� ��� ��� ���������
bool SetCharacterRandomName(string characterID)
{
	int idx = GetCharacterIndex(characterID);
	if(idx==-1)
	{
		trace("Warning!!! Missing character id = " + characterID);
		return false;
	}
	SetRandomNameToCharacter(GetCharacter(idx));
	return true;
}


// ��������� ������� �� ����������� �����
void QuestFortDestroyed()
{
	int idx = GetEventData();
	if(idx==-1) return;
	ref chref = GetCharacter(idx);
	chref.FortDestroy = "1";
	QuestsCheck();
}

void QuestFortCaptured()
{
	int idx = GetEventData();
	if(idx==-1) return;
	ref chref = GetCharacter(idx);
	chref.FortCapture = "1";
	QuestsCheck();
}

void QuestShipCaptured()
{
	int idx = GetEventData();
	if(idx==-1) return;
	ref chref = GetCharacter(idx);
	chref.ShipCapture = "1";
	QuestsCheck();
}

void QuestGroupDeath()
{
	aref chref = GetEventData();
	if( !CheckAttribute(chref,"act.team") ) return;
	string groupName = chref.act.team;
	pchar.GroupDeath.(groupName) = "1";
}

// ������������� � �������� � ���� �� ������
object questToSeaLoginer;
void QuestToSeaLogin_PrepareLoc(string islandID, string locGroup, string locName, bool sailUP)
{
	questToSeaLoginer.PlayerGroup.x = 0.0;
	questToSeaLoginer.PlayerGroup.ay = 0.0;
	questToSeaLoginer.PlayerGroup.z = 0.0;
	questToSeaLoginer.Island = islandID;
	if(!sailUP)	questToSeaLoginer.FromCoast = true;

	int		iIsland = FindIsland(islandID);
	if (iIsland >= 0)
	{
		if(locGroup=="") {locGroup="reload";}
		aref	arGroup, arLocator;
		ref		rIsland = GetIslandByIndex(iIsland);
		makearef(arGroup, rIsland.(locGroup));

		int		iGroupSize = GetAttributesNum(arGroup);
		for (int i=0; i<iGroupSize; i++)
		{
			arLocator = GetAttributeN(arGroup, i);
			if (GetAttributeName(arLocator) == locName)	break;
		}

		if(i<iGroupSize)
		{
			if(CheckAttribute(arLocator,"x"))	{questToSeaLoginer.PlayerGroup.x = arLocator.x;}
			if(CheckAttribute(arLocator,"z"))	{questToSeaLoginer.PlayerGroup.z = arLocator.z;}
			if(CheckAttribute(arLocator,"ay"))	{questToSeaLoginer.PlayerGroup.ay = arLocator.ay;}
		}
	}
}

void QuestToSeaLogin_Prepare(float x, float z, string islandID)
{
	DeleteAttribute(&questToSeaLoginer,"");
	questToSeaLoginer.PlayerGroup.x = x;
	questToSeaLoginer.PlayerGroup.ay = 0.0;
	questToSeaLoginer.PlayerGroup.z = z;
	questToSeaLoginer.Island = islandID;
}
// ����������� ��������� ��� �������� � ���� �� ������
void QuestToSeaLogin_Add(string groupName)
{
	aref arql,ar;
	makearef(arql,questToSeaLoginer.QuestGroups);
	for(int i=0; i<GetAttributesNum(arql); i++)
	{
		if( GetAttributeValue(GetAttributeN(arql,i))==groupName ) break;
	}
	if(i==GetAttributesNum(arql))
	{
		string newAttrName;
		for(i=0; i<=1000; i++)
		{
			newAttrName = "l"+i;
			if(!CheckAttribute(arql,newAttrName))
			{
				arql.(newAttrName) = groupName;
				break;
			}
		}
	}
}
// ��������� ��������� �������� � ����
void QuestToSeaLogin_Launch()
{
	SetEventHandler("FaderEvent_EndFade", "QuestToSeaLoginFade", 0);
	object fader;
	CreateEntity(&fader, "fader");
	SendMessage(&fader, "ls",FADER_PICTURE,"loading\sea_" + rand(31) + ".tga");
	SendMessage(&fader, "lfl", FADER_OUT, 1.0, true);
	int idxLoadLoc = FindLoadedLocation();
	if( idxLoadLoc!=-1 )
	{
		UnloadLocation(&Locations[idxLoadLoc]);
	}
}
void QuestToSeaLoginFade()
{
	DelEventHandler("FaderEvent_EndFade", "QuestToSeaLoginFade");
	SeaLogin(&questToSeaLoginer);
}

// �������� ���������� ��������� ����� ������
int	GetCharacterFromFantom(ref chref)
{
	/*int tmpi = FindLoadedLocation();
	if(tmpi==-1) return -1;
	string locID = Locations[tmpi].id;
	int retVal = -1;
	ref fantRef;
	int startVal = sti(chref.index)+1;
	if ( startVal < FANTOM_CHARACTERS ) startVal = FANTOM_CHARACTERS;
	for(int i=startVal; i<BOARDING_CHARACTERS; i++)
	{
		fantRef = GetCharacter(i);
		if(fantRef.location!=locID) continue;
		if(CharacterIsDead(fantRef)) continue;
		if ( CheckAttribute(fantRef,"act.team") && fantRef.act.team==chref.act.team )
		{
			retVal = sti(fantRef.index);
			break;
		}
	}
	return retVal;*/
	return -1;
}

// ������ �� ������� ���� ������ ���������� ����
void RemoveCharactersFromLocation(string idLocation, string modelName, string type)
{
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if( Characters[i].location!=idLocation ) continue;
		if( modelName!="" && modelName!=Characters[i].model ) continue;
		if( type!="" && type!=Characters[i].act.type ) continue;
		ChangeCharacterAddress(&Characters[i], "none", "");
	}
}

void CompleteQuestName(string sQuestName, string qname)
{
	if( CheckAttribute(&objQuestScene,"list."+sQuestName+".chrIdx") )
	{
		Event("qprocTaskEnd","a",GetCharacter(sti(objQuestScene.list.(sQuestName).chrIdx)));
	}
	else
	{
		QuestComplete(sQuestName, qname);
	}
}

void procEvntQuestComplete()
{
	string qname = GetEventData();

	if( CheckAttribute(pchar,"quest."+qname) )
	{
		if( CheckAttribute(pchar,"quest."+qname+".win_condition") )
		{
			CompleteQuestName(pchar.quest.(qname).win_condition, qname);
			QuestsCheck();
		}
		else
		{
			trace("WARNING! Not win condition for quest " + qname);
		}
	}
	else
	{
		trace("WARNING! Not found quest name: " + qname);
	}
}

///////////////////////////////////
///  ��� ������ ����� - �� ������������� ���� ���� �����... ������
///////////////////////////////////

// ��������� �������� � �� �� ���������� ������� �����
//------------------------------------------------------------
void ActAnimation(ref chref, string action, string questName)
{
//	chref.activity.endAnimationQuest.Name = questName;
//	actAction(chref, action, "ExitActAnimation");
}

// ���� ������� ������ ������ ������, �������� ��������� �� ���� �������.
void BreakAllAttack()
{
//	actAllarm = 0.0;
//	int idxCurLoc = FindLoadedLocation();
//	if(idxCurLoc==-1) return;
//	string curLocName = Locations[idxCurLoc].id;
//
//	for(int n=0; n<MAX_CHARACTERS; n++)
//	{
//		if(Characters[n].location == curLocName)
//		{
//			actReset(&Characters[n]);
//			if( Characters[n].act.type == "soldier" ) SetCharacterTask_GotoPoint(&Characters[n],Characters[n].location.group,Characters[n].location.locator);
//		}
//	}
}

/*
void FoundAndDeleteAllQuestForQuestNumberExceptCurrentQuest(int iQuest, string sCurrentQuest)
{

	aref aQuests, aQuestsDetailed;
	makearef(aQuests, pchar.quest);
	int q = GetAttributesNum(aQuests);
	string sCheckQuest;
	for(int i=0; i < q; i++)
	{
		aQuestsDetailed = GetAttributeN(aQuests,i);
		sCheckQuest = GetAttributeName(aQuestsDetailed);
		if(sti(aQuestsDetailed.quest) == iQuest && sCheckQuest != sCurrentQuest)
		{
			aQuestsDetailed.over = "yes";
		}
	}
}

void FoundAndDeleteAllQuestForQuestNumber(int iQuest)
{

	aref aQuests, aQuestsDetailed;
	makearef(aQuests, pchar.quest);
	int q = GetAttributesNum(aQuests);
	for(int i=0; i<q; i++)
	{
		aQuestsDetailed = GetAttributeN(aQuests,i);
		if(CheckAttribute(aQuestsDetailed, "quest"))
		{
			if(sti(aQuestsDetailed.quest) == iQuest)
			{
				aQuestsDetailed.over = "yes";
			}
		}
	}
}
*/
// boal -->
void SetTimerCondition(string _name, int _year, int _month, int _day, bool _again)
{
    PChar.quest.(_name).win_condition.l1            = "Timer";
    PChar.quest.(_name).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
    PChar.quest.(_name).win_condition               = _name;
    if (_again)
    {
        PChar.quest.(_name).again = true;
    }
    else
    {
        DeleteAttribute(Pchar, "quest."+_name+".again");
    }
}

void SetTimerFunction(string _name, int _year, int _month, int _day)
{
    PChar.quest.(_name).win_condition.l1            = "Timer";
    PChar.quest.(_name).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
    PChar.quest.(_name).function					= _name;
}

void SetTimerConditionParam(string _name, string _quest, int _year, int _month, int _day, int _hour, bool _again)
{
    while (_hour > 23)
	{
		_hour -= 23;
		_day += 1;
	}
	PChar.quest.(_name).win_condition.l1            = "Timer";
    PChar.quest.(_name).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
    PChar.quest.(_name).win_condition.l1.date.hour  = _hour;
    PChar.quest.(_name).win_condition               = _quest;
    if (_again)
    {
        PChar.quest.(_name).again = true;
    }
    else
    {
        DeleteAttribute(Pchar, "quest."+_name+".again");
    }
}
// �������� ������� �� ��������� �� �������, ����� ��� ������ ������� ��� ��������� � ��. �������� (����������)
bool isLocationFreeForQuests(string loc_id)
{
	aref quests, quest;
	int  i, nQuestsNum;
	bool bEnableEncounters = true;
	ref  chr;
	
	makearef(quests, PChar.Quest);
	nQuestsNum = GetAttributesNum(quests);
	
	for (i = 0; i < nQuestsNum; i++)
	{
        quest = GetAttributeN(quests, i);
        if (CheckAttribute(quest, "over")) continue;
        // ���������: ��������� ������ ����� �1, �� ������� ������ (�� �1) �� ������� ��������, � ������� �� �����.
		if (CheckAttribute(quest, "win_condition.l1") && quest.win_condition.l1 == "Location" && quest.win_condition.l1.Location == loc_id)
		{   // ��� ����� ������ �� ��� �������
			bEnableEncounters = false;
			break;
		}
		if (CheckAttribute(quest, "win_condition.l1") && quest.win_condition.l1 == "locator" && quest.win_condition.l1.Location == loc_id)
		{   // ��� ����� ������ �� ��� �������
			bEnableEncounters = false;
			break;
		}
	}
	if (bEnableEncounters)
	{ // ��������� ���, ������ ��� ������ ���, ���� ���� - ������
		for(i = 0; i<TOTAL_CHARACTERS; i++)
		{
			chr = &characters[i];
			if (CheckAttribute(chr, "location")	 && chr.location == loc_id)
			{
				if (!IsOfficer(chr))
				{   // ��� �� �� � ���
					bEnableEncounters = false;
					break;	
				}
			}
		}			
	}
	return bEnableEncounters;
}
// boal <--

// Warship -->
// ��������� ����� � ���������� "s" ����� ������������ ������� �����
void SetTimerEvent_String(string _event, int _year, int _month, int _day, string _string)
{
	int iMax = 30;
	String sQuestStr;

	for(int i=1; i<=iMax; i++)
	{
		sQuestStr = _event+"_"+i;
		if(!CheckAttribute(PChar, "Quest."+sQuestStr))
		{
			Log_TestInfo("SetTimerEvent_String: ������� ��������� ���������� - "+sQuestStr);
			break;
		}
		
		if(i==iMax)
		{
			Log_TestInfo("SetTimerEvent_String: ��������� ���������� ����, ��������� ������� ����������");
			return;
		}
	}
	
	PChar.Quest.(sQuestStr).win_condition.l1            = "Timer";
	PChar.Quest.(sQuestStr).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
	PChar.Quest.(sQuestStr).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
	PChar.Quest.(sQuestStr).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
	PChar.Quest.(sQuestStr).win_condition               = "SetTimerEvent";
	PChar.Quest.(sQuestStr).Event = _event;
	PChar.Quest.(sQuestStr).Event.Type = "s";
	PChar.Quest.(sQuestStr).Event.Param = _string;
}

// ���������� �� ������ � ��������
void SetFunctionTimerCondition(string _name, int _year, int _month, int _day, bool _again)
{
	PChar.quest.(_name).win_condition.l1            = "Timer";
	PChar.quest.(_name).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
	PChar.quest.(_name).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
	PChar.quest.(_name).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
	PChar.quest.(_name).function               = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

// ���������� �� ������ � �������� � ������ ����� <-- ugeen
void SetFunctionTimerConditionParam(string _name, int _year, int _month, int _day, int _hour, bool _again)
{
    while (_hour > 23)
	{
		_hour -= 23;
		_day += 1;
	}
	PChar.quest.(_name).win_condition.l1            = "Timer";
	PChar.quest.(_name).win_condition.l1.date.hour  = _hour;
	PChar.quest.(_name).win_condition.l1.date.day   = GetAddingDataDay(_year, _month, _day);
	PChar.quest.(_name).win_condition.l1.date.month = GetAddingDataMonth(_year, _month, _day);
	PChar.quest.(_name).win_condition.l1.date.year  = GetAddingDataYear(_year, _month, _day);
	PChar.quest.(_name).function               = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}
// -- > ugeen

void SetFunctionLocationCondition(string _name, string _location, bool _again)
{
	PChar.quest.(_name).win_condition.l1 = "location";
	PChar.quest.(_name).win_condition.l1.location = _location;
	PChar.quest.(_name).function = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

void SetFunctionLocationNationCondition(string _name, string _location, int _nation, bool _again)
{
	PChar.quest.(_name).win_condition.l1 = "location";
	PChar.quest.(_name).win_condition.l1.location = _location;
	PChar.quest.(_name).win_condition.l1.nation = _nation;
	PChar.quest.(_name).function = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

void SetFunctionExitFromLocationCondition(string _name, string _location, bool _again)
{
	PChar.quest.(_name).win_condition.l1 = "ExitFromLocation";
	PChar.quest.(_name).win_condition.l1.location = _location;
	PChar.quest.(_name).function = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

void SetFunctionNPCDeathCondition(string _name, string _character, bool _again)
{
	PChar.quest.(_name).win_condition.l1 = "NPC_Death";
	PChar.quest.(_name).win_condition.l1.character = _character;
	PChar.quest.(_name).function = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

void SetFunctionLocatorCondition(string _name, string _location, string _group, string _locator, bool _again)
{
	PChar.quest.(_name).win_condition.l1 = "locator";
	PChar.quest.(_name).win_condition.l1.location = _location;
	PChar.quest.(_name).win_condition.l1.locator_group = _group;
	PChar.quest.(_name).win_condition.l1.locator = _locator;
	PChar.quest.(_name).function = _name;
	if (_again)
	{
		PChar.quest.(_name).again = true;
	}
	else
	{
		DeleteAttribute(Pchar, "quest."+_name+".again");
	}
}

// ��� ��������������� -->
void SetFunctionInterruptionToShips(string _GroupID, string _GroupDeath, string _EnterMap)
{
	if(_GroupDeath != "")
	{
		PChar.FunctionParam.GroupDeathFunction = _GroupDeath;
		PChar.quest.(_GroupDeath).win_condition.l1 = "Group_Death";
		PChar.quest.(_GroupDeath).win_condition.l1.group = _GroupID;
		PChar.quest.(_GroupDeath).function = "GroupDeathFunction";
	}
	
	if(_EnterMap != "")
	{
		PChar.FunctionParam.EnterMapFunction = _EnterMap;
		PChar.Quest.(_EnterMap).win_condition.l1 = "MapEnter";
		PChar.Quest.(_EnterMap).function = "EnterMapFunction";
	}
}

void GroupDeathFunction(string sQuest)
{
	string _EnterMap = PChar.FunctionParam.EnterMapFunction;
	string _GroupDeath = PChar.FunctionParam.GroupDeathFunction;
	PChar.Quest.(_EnterMap).over = "yes";
	DoQuestFunctionDelay(_GroupDeath, 0.1);
}

void EnterMapFunction(string sQuest)
{
	string _EnterMap = PChar.FunctionParam.EnterMapFunction;
	string _GroupDeath = PChar.FunctionParam.GroupDeathFunction;
	PChar.Quest.(_GroupDeath).over = "yes";
	DoQuestFunctionDelay(_EnterMap, 0.1);
}
// ��� ��������������� <--

void DeleteQuestCondition(string sQuest)
{
	PChar.Quest.(sQuest).over = "yes";
}

void CalculateCheatsInfo() // ��� ���������� �� �����. ������������ � ���������� Debuger
{
	int i;
	string sCheat;
	
	for(i=1; i<=31; i++)
	{
		sCheat = "F" + i;
		if(Statistic_AddValue(PChar, "Cheats." + sCheat, 0) == 0)
			PChar.Statistic.Cheats.(sCheat) = 0;
	}
	
	if(Statistic_AddValue(PChar, "Cheats.ReloadByStr", 0) == 0)
		PChar.Statistic.Cheats.ReloadByStr = 0;
		
	aref arAllCheats;
	makearef(arAllCheats, PChar.Statistic.Cheats);
	int iAllCheats = GetAttributesNum(arAllCheats);
	int iAllCheatsCount = 0;
	
	SetFormatedText("INFO_TEXT2", "���������������� ����:");
	
	for(i=0; i<iAllCheats; i++)
	{
		sCheat = GetAttributeName(GetAttributeN(arAllCheats, i));
		int iCurCheatCount = Statistic_AddValue(PChar, "Cheats." + sCheat, 0);
		if(iCurCheatCount == 0) continue; // ���� ��� �� ������ - ����������
		if(HasSubStr(sCheat, "F"))
			AddLineToFormatedText("INFO_TEXT2", XI_ConvertString("D_" + sCheat) + " - " + iCurCheatCount + " ���.");
		else
			AddLineToFormatedText("INFO_TEXT2", sCheat + " - " + iCurCheatCount + " ���.");
			
		iAllCheatsCount = iAllCheatsCount + iCurCheatCount;
	}
	
	PChar.Statistic.Cheats = iAllCheatsCount;
	AddLineToFormatedText("INFO_TEXT2", XI_ConvertString("Total") + " " + iAllCheatsCount + " ���.");
	
	if(iAllCheatsCount == 0) // ���� 0, ������ ����� �� �����
		SetFormatedText("INFO_TEXT2", "����� �� ��������������!");
}

// ��� ������ ��� ������� ������ 10.07.08

// 20.08.09 ����� ��������� ��������� - ������, ������� ���� ������� ����� ����������� ��� �������
int TransferGoods_CalculateWeight(ref _character)
{
	int weight = 0;
	String goodName;
	String characterId = _character.Id;
	
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		goodName = Goods[i].Name;
		
		if(CheckAttribute(PChar, "TransferGoods." + characterId + "." + goodName))
		{
			weight += GetGoodWeightByType(i, sti(PChar.TransferGoods.(characterId).(goodName)) - GetCargoGoods(_character, i));
		}
	}
	
	return weight;
}

// ��������� � ������ ����
int TransferGoods_StartTransfer(ref rChar, string sColony) // rChar - ���� ����� ������ ����� � ����, sColony - � ����� ������� ��������
{
	int i, iNeedGood, iCost, iStoreGoodQty;
	ref rGood, rTreasurer;
	ref rStore = &Stores[FindStore(sColony)];
	string sGood;
	String characterId = rChar.Id;
	
	int buyGoodsWeight = 0;
	int iCurGoodQty, iNeedGoodsQty
	int iMoneyQty = 0;
	
	rTreasurer = GetPCharTreasurerRef(); // ��������. ��� ���� �����
	
	for(i = 0; i < GOODS_QUANTITY; i++)
	{
		rGood = &Goods[i];
		sGood = rGood.name;
		
		if(!CheckAttribute(PChar, "TransferGoods." + characterId + "." + sGood))
		{
			PChar.TransferGoods.(characterId).(sGood) = 0;
		}
		
		iCurGoodQty = GetCargoGoods(rChar, i); // ������� ����� ������ ���� ������
		iNeedGoodsQty = sti(PChar.TransferGoods.(characterId).(sGood)); // ������� ����� ����� ������� ������ (�� ��������!)
			
		if(iCurGoodQty == iNeedGoodsQty) continue; // ������ �� ����� 
		
		if (!CheckAttribute(pchar,"SellRestriction"))
		{
			if(iCurGoodQty > iNeedGoodsQty) // �������
			{
				if(CheckAttribute(rStore, "goods." + sGood + ".tradetype"))
				{	
					if(rStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND || rStore.goods.(sGood).tradetype == TRADE_TYPE_CANNONS) continue;
				}	
				iNeedGood = iCurGoodQty - iNeedGoodsQty; // ������� ����� �������
				iCost = GetStoreGoodsPrice(rStore, i, 1, PChar, 1)*iNeedGood/sti(rGood.Units); // ���� ������ ��� �������
				RemoveCharacterGoodsSelf(rChar, i, iNeedGood); // �������� ������ � ����� �����
				AddStoreGoods(rStore, i, iNeedGood); // ���������� ����� � �����
				iMoneyQty+=iCost;
				buyGoodsWeight -= iNeedGood;
			}
		}
			
		if(iCurGoodQty < iNeedGoodsQty) // ��������
		{
			if(CheckAttribute(rStore, "goods." + sGood + ".tradetype") && rStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND)
			{
				if(!CheckAttribute(PChar, "TransferGoods." + characterId + ".BuyContraband")) continue;
			}
			
			iNeedGood = iNeedGoodsQty - iCurGoodQty; // ������� ����� ������
			iStoreGoodQty = GetStoreGoodsQuantity(rStore, i); // ������� ����� ������ (����� ���� � ������)
			if(iNeedGood > iStoreGoodQty) iNeedGood = iStoreGoodQty; // ����� ������ ������, ��� ���� � ������
			iCost = GetStoreGoodsPrice(rStore, i, 0, PChar, 1)*iNeedGood/sti(rGood.Units); // ���� ������ ��� �������
			if(sti(PChar.Money) >= iCost)
			{
				AddCharacterGoodsSimple(rChar, i, iNeedGood); // ���� ������ � ���� �������
				RemoveStoreGoods(rStore, i, iNeedGood); // ������� �� ������
				iMoneyQty-=iCost;
				buyGoodsWeight += iNeedGood;
			}
		}
	}
	
	if (CheckAttribute(pchar,"BuyPersonal"))
	{
		int 	iOfficer = -1;
		int 	qty = 0;
		string itemname = "";
		for(int z = 0; z < 6 + MAX_NUM_FIGHTERS; z++)
		{
			if (z == 0) iOfficer = GetMainCharacterIndex();
			else iOfficer = GetOfficersIndex(pchar, z); 
			if(iOfficer != -1)
			{
				if (CheckAttribute(&characters[iOfficer],"fighter") || z == 0)
				{
					if (characters[iOfficer].sex != "woman") Log_Info(characters[iOfficer].Name+" "+characters[iOfficer].LastName+" ������� �������� �����������.");
					else Log_Info(characters[iOfficer].Name+" "+characters[iOfficer].LastName+" �������� �������� �����������.");
					for (int j = 0; j < 9; j++)
					{
						switch (j)
						{
							case 0: itemname = "bullet"; qty = 10; break;
							case 1: itemname = "GunPowder"; qty = 10; break;
							case 2: itemname = "Food1"; qty = rand(3)+1; break;
							case 3: itemname = "Food2"; qty = rand(2)+1; break;
							case 4: itemname = "Food3"; qty = rand(1)+1; break;
							case 5: itemname = "potion1"; qty = rand(3)+1; break;
							case 6: itemname = "potion2"; qty = rand(1)+1; break;
							case 7: itemname = "potion3"; qty = rand(1)+1; break;
							case 8: itemname = "potion4"; qty = rand(1)+1; break;
							case 9: itemname = "potion5"; qty = rand(1)+1; break;
						}
						iCost = GetTradeItemPrice1(Items_FindItemIdx(itemname), PRICE_TYPE_BUY)*qty
						if(sti(PChar.Money) >= iCost)
						{
							iMoneyQty -= iCost;		
							TakeNItems(&characters[iOfficer], itemname, qty);
						}
					}
				}
			}
		}
	}
	
	if(iMoneyQty != 0) // ���� ���� ���-�� ������� ��� ������
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) // ����� � ����� ��������
	}
	
	return buyGoodsWeight;
}
// Warship <--
int GetTradeItemPrice1(int itmIdx, int tradeType)
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