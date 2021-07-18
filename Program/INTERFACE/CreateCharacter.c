int curmodel = 0;
int curmanim = 0;
string sCurmanim{10} = {"","начало боя","быстрая атака","мощная атака","attack_feintc_","attack_break_1","parry_","attack_feint_","прыжок","конец боя"};

string totalInfo;
string totalInfo1;
string costume = "обычный";
int idLngFile = -1;

int iType = 1;
int iTypeQty = 1;
int iTypeCount = 1;
int iVarCount = 1;

int FState_SEX[3] = {0,0,0};//на старте все три "пола" включены, муж/жен/скелет
bool FState_ANIM = false;

void InitInterface(string iniName)
{
    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetNodeUsing("FRAME1", false);

	GameInterface.NAME_STRING.str = "Name (Кто?)";
	GameInterface.NAME_STRING_2.str = "Name 2 (Кого?)";
	GameInterface.NAME_STRING_3.str = "Name 3 (Кому?)";
	GameInterface.LAST_NAME_STRING.str = "Last Name (Кто?)";
	GameInterface.LAST_NAME_STRING_2.str = "Last Name 2 (Кого?)";
	GameInterface.LAST_NAME_STRING_3.str = "Last Name 3 (Кому?)";

	PChar.CreateCharacter = 1;
	PChar.CreateCharacter.Select.Count = 1;
	PChar.CreateCharacter.Select.NationCount = 5;
	
	PChar.CreateCharacter.Create.TypeCount = 1;
	PChar.CreateCharacter.Create.TypeCount.VariantCount = 1;
	PChar.CreateCharacter.Create.TypeCount.Variants = 12;

	SetDataInformation();
	StartAboveForm(false);
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	//SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("CheckButtonChange", "ProcessFilter", 0);
	SetEventHandler("NameUptade","NameUptade",0);
	SetEventHandler("Name2Uptade","Name2Uptade",0);
	SetEventHandler("Name3Uptade","Name3Uptade",0);
	SetEventHandler("LastNameUptade","LastNameUptade",0);
	SetEventHandler("LastNameUptade","LastName2Uptade",0);
	SetEventHandler("LastNameUptade","LastName3Uptade",0);
	
	LAi_SetActorTypeNoGroup(PChar);
	SelectOperation(true);
	SetNodeUsing("RETURN_TO_QUESTION", false);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	//DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("CheckButtonChange", "ProcessFilter");
	DelEventHandler("NameUptade","NameUptade");
	DelEventHandler("Name2Uptade","Name2Uptade");
	DelEventHandler("Name3Uptade","Name3Uptade");
	DelEventHandler("LastNameUptade","LastNameUptade");
	DelEventHandler("LastName2Uptade","LastName2Uptade");
	DelEventHandler("LastName3Uptade","LastName3Uptade");

	EndAboveForm(true);
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	
	EndQuestMovie();
	//locCameraFollow();
	LAi_SetPlayerType(pchar);
    	
	EndSelectMainCharacter(pchar);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "SELECT_CHARACTER":
			if(comName=="activate" || comName=="click")
			{
				SelectOperation(true);
			}
		break;
		
		case "CREATE_CHARACTER":
			if(comName=="activate" || comName=="click")
			{
				SelectOperation(false);
			}
		break;
		
		case "RETURN_TO_QUESTION":
			if(comName=="activate" || comName=="click")
			{
				ReturnToQuestion();
			}
		break;
		
		case "ENGLAND":
			if(comName=="activate" || comName=="click")
			{
				SetNationCount(1);
			}
		break;
		
		case "FRANCE":
			if(comName=="activate" || comName=="click")
			{
				SetNationCount(2);
			}
		break;
		
		case "SPAIN":
			if(comName=="activate" || comName=="click")
			{
				SetNationCount(3);
			}
		break;
		
		case "HOLLAND":
			if(comName=="activate" || comName=="click")
			{
				SetNationCount(4);
			}
		break;
		
		case "SELECT_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacter(true);
			}
		break;
		
		case "SELECT_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacter(false);
			}
		break;
		
		case "COSTUMES_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleCirass(false);
			}
		break;
		
		case "COSTUMES_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleCirass(true);
			}
		break;
		
		case "ANIMATION_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleAnimation(false);
			}
		break;
		
		case "ANIMATION_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleAnimation(true);
			}
		break;
		
		case "SELECT_CHARACTER_DONE":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacterDone();
			}
		break;
		
		case "CREATE_CHARACTER_DONE":
			if(comName=="activate" || comName=="click")
			{
				CreateCharacterDone();
			}
		break;
		
		case "SELECT_TYPE_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectCharacterType(true);
			}
		break;
		
		case "SELECT_TYPE_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectCharacterType(false);
			}
		break;
		
		case "CREATE_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectCharacterVariant(true);
			}
		break;
		
		case "CREATE_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectCharacterVariant(false);
			}
		break;
	}
}

void CycleAnimation(bool dir)
{
	string anim;
	if (!dir)
	{
		if (curmanim == 0) curmanim = 9;
		else curmanim--;
	}
	if (dir)
	{
		if (curmanim == 9) curmanim = 0;
		else curmanim++;
	}
	LAi_SetActorTypeNoGroup(pchar);
	switch (curmanim)
	{
		case 0:
			LAi_ActorAnimation(pchar, "idle_"+sti(rand(10)+1), "", 0.6);
		break;
		case 1: 
			LAi_ActorAnimation(pchar, "normal to fight", "", 0.6);
		break;
		case 2: 
			LAi_ActorAnimation(pchar, "attack_fast_"+sti(rand(3)+1), "", 0.6);
		break;
		case 3: 
			LAi_ActorAnimation(pchar, "attack_force_"+sti(rand(3)+1), "", 0.6);
		break;
		case 4:
			LAi_ActorAnimation(pchar, "attack_feintc_"+sti(rand(3)+1), "", 0.6);
		break;
		case 5: 
			LAi_ActorAnimation(pchar, "attack_break_1", "", 0.6); 
		break;
		case 6: 
			LAi_ActorAnimation(pchar, "parry_"+sti(rand(3)+1), "", 0.6); 
		break;
		case 7: 
			LAi_ActorAnimation(pchar, "attack_feint_"+sti(rand(3)+1), "", 0.6); 
		break;
		case 8:
			LAi_ActorAnimation(pchar, "jump", "", 0.6); 
		break;
		case 9: 
			LAi_ActorAnimation(pchar, "fight to normal", "", 0.6);
		break;
	}
}

void CycleCirass(bool dir)
{
	string itemID;
	if (!dir)
	{
		if (curmodel == 0) curmodel = 8;
		else curmodel--;
	}
	if (dir)
	{
		if (curmodel == 8) curmodel = 0;
		else curmodel++;
	}
	switch (curmodel)
	{
		case 0:
			pchar.model = GetSubStringByNum(pchar.HeroModel, 0);
			DeleteAttribute(pchar, "cirassId");
			SetNewModelToChar(pchar);//boal
			costume = "обычный";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 1: 
			itemID = "cirass1";
			costume = "кираса 1";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 2: 
			itemID = "cirass2";
			costume = "кираса 2";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 3: 
			itemID = "cirass3";
			costume = "кираса 3";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 4: 
			itemID = "cirass4";
			costume = "кираса 4";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 5: 
			itemID = "cirass5";
			costume = "кираса 5";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 6: 
			itemID = "suit_1";
			costume = "обноски";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 7: 
			itemID = "suit_2";
			costume = "негоциант";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
		case 8: 
			itemID = "suit_3";
			costume = "дворянин";
			SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
		break;
	}
	if (curmodel != 0) ShowCirassOnCharacter(pchar, CIRASS_ITEM_TYPE, itemID);
}

void ShowCirassOnCharacter(ref chref, string groupID, string itemID)
{
	object emptyItm;
	aref arItm;
	string modelName = "";
	makearef(arItm,emptyItm);
 	int itemNum; // boal 23.01.2004

	if(itemID!="")
	{
		itemNum = Items_FindItem(itemID,&arItm);// boal 23.01.2004
	}

	switch(groupID)
	{
    case CIRASS_ITEM_TYPE:
        if (CheckAttribute(chref, "HeroModel")) // все, у кого есть что одеть
        {
            if (CheckAttribute(arItm, "model"))
            {
                chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
				if (startherotype == 2 && sti(arItm.model) == 5 && findsubstr(chref.HeroModel, "Whisper" , 0) != -1 && CheckCharacterItem(pchar,"hatWhisper") &&  !CheckAttribute(pchar, "Whisper.NanoCostume"))
				{
					chref.model = "PGG_Whisper_5_Cirass"
				}
                chref.cirassId = itemNum;
            }
            else
            {
                chref.model = GetSubStringByNum(chref.HeroModel, 0);
                DeleteAttribute(chref, "cirassId");
            }
        }
        else
        {
            // тут анализ модели офицера или пирата
            if(CheckAttribute(arItm, "model"))
            {
                chref.cirassId = itemNum;
            }
            else
            {
                DeleteAttribute(chref, "cirassId");
            }
        }
        SetNewModelToChar(chref);//boal
	break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void NameUptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}

void Name2Uptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}

void Name3Uptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}

void LastNameUptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}

void LastName2Uptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}

void LastName3Uptade()
{	
	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;
	string sCharacterName = sName + " " + sLastName;
	
	GameInterface.strings.CreateCharacterHeader = sCharacterName;
}


void SelectCharacterType(bool bLeft)
{
	SetSelectable("ENGLAND", true);
	SetSelectable("FRANCE", true);
	SetSelectable("SPAIN", true);
	SetSelectable("HOLLAND", true);
	SetSelectable("PIRATE", true);
	
	
	int TextFile = LanguageOpenFile("CreateCharacter.txt");
	int iQtyMax = sti(LanguageConvertString(TextFile, "types_qty"));
	
	if(bLeft) { iTypeCount--; } else { iTypeCount++; } 
	if(iTypeCount < 1) { iTypeCount = iQtyMax; }
	if(iTypeCount > iQtyMax) { iTypeCount = 1; }
	iVarCount = 1;
	
	SetNationCount(1);
	
	UptadeCreateInformation();
	LanguageCloseFile(TextFile);
}

void SelectCharacterVariant(bool bLeft)
{
	int TextFile = LanguageOpenFile("CreateCharacter.txt");
	int iQtyMax = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_qty"));
	
	if(bLeft) { iVarCount--; } else { iVarCount++; } 
	if(iVarCount < 1) { iVarCount = iQtyMax; }
	if(iVarCount > iQtyMax) { iVarCount = 1; }
	
	UptadeCreateInformation();
	LanguageCloseFile(TextFile);
}

void UptadeCreateInformation()
{
	int TextFile = LanguageOpenFile("CreateCharacter.txt");
	int iQtyMax = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_qty"));
	string sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount);
	string sModelTypeName = LanguageConvertString(TextFile, "type_" + iTypeCount + "_name");
	string ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_ani");
	string sNeedNation = LanguageConvertString(TextFile, "type_" + iTypeCount + "_nn");
	string sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_sex");
	string sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_mush");
	
	string sModel = "";
	int iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_face"));
	int iFaceNumber = 0;
	int iNationCount = sti(PChar.CreateCharacter.Select.NationCount);
	
	string sName = "";
	string sLastName = "";
	string sCharacterName = "";
	
	string SelectCharacterNation = "";
	string sNationPrefix = "";
	string sNationSoldierPrefix = "";
	
	switch(iNationCount)
	{
		case 1: SelectCharacterNation = "England"; sNationPrefix = "eng"; break;
		case 2: SelectCharacterNation = "France"; sNationPrefix = "fra"; break;
		case 3: SelectCharacterNation = "Spain"; sNationPrefix = "spa"; break;
		case 4: SelectCharacterNation = "Holland"; sNationPrefix = "hol"; break;
		case 5: SelectCharacterNation = "Pirate"; sNationPrefix = ""; break;
	}
	
	if(sNeedNation == "yes")
	{
		sModelType += sNationPrefix + "_";
		sMush = sNationPrefix + sMush;
	}
	
	if(sModelType == "Other")
	{
		sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_model");
		ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_ani");
		sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_sex");
		sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_mush");
		sModel = sModelType;
		iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_face"));
	}
	else
	{
		sModel = sModelType + iVarCount;
	}
	
	
	sName = GameInterface.NAME_STRING.str;
	sLastName = GameInterface.LAST_NAME_STRING.str;

	sCharacterName = sName + " " + sLastName;
	
    	if(PChar.SuccessPrice.CreateCharacter == true)
    	{
    		sCharacterName = GetName(PChar, "f");
    	}
    	
	string sType = sModelTypeName;
	
	PChar.model = sModel;
	PChar.model.animation = ani;
	PChar.sex = sSex;
	PChar.FaceId = iFaceID;
	SetNewModelToChar(PChar);
	
	CreateString(true,"CreateCharacterName", "Вариант " + iVarCount + " из " + iQtyMax, FONT_CAPTION, COLOR_NORMAL, 405,18,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterHeader", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 140,18,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringName", "Имя: ", FONT_CAPTION, COLOR_NORMAL, 140,58,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringName2", "Имя в родительном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,118,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringName3", "Имя в дательном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,178,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringLastName", "Фамилия: ", FONT_CAPTION, COLOR_NORMAL, 140,243,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringLastName2", "Фамилия в родительном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,303,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringLastName3", "Фамилия в дательном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,363,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringTypeCharacter", "Тип внешности: ", FONT_CAPTION, COLOR_NORMAL, 140,432,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterType", sType, FONT_CAPTION, COLOR_NORMAL, 140,458,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringNation", "Выбор по нации: ", FONT_CAPTION, COLOR_NORMAL, 140,495,SCRIPT_ALIGN_CENTER,1.0);
	LanguageCloseFile(TextFile);
	
    	if(PChar.SuccessPrice.CreateCharacter == true && PChar.SuccessPrice.CreateCharacter.Model == PChar.model)
    	{
    		SetSelectable("CREATE_CHARACTER_DONE", false);
    	}
    	else
    	{
    		SetSelectable("CREATE_CHARACTER_DONE", true);
    	}
}	

void SelectMainCharacterDone()
{
	int iCount = sti(PChar.CreateCharacter.Select.Count);
	
	PlaySound("notebook");
	PChar.Selected = true;
	
    	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;
	Log_SetStringToLog("Выбран персонаж " + sCharacterName + ".");
	
	PChar.DefaultModel = PChar.model;
	
	SetNewModelToChar(PChar);
	FaceMaker(PChar);
	
	startHeroType = iCount;
	DeleteAttribute(pchar,"items");
	DeleteAttribute(pchar,"equip");
	
	ProcessCancelExit();
}

void SelectMainCharacter(bool bLeft)
{
    	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
    	string sQuantity = LanguageConvertString(idLngFile, "hero_qty");
    	int iQuantity = sti(sQuantity);
	string sSex, sAnim, sName;

	while (1)
	{
		if(bLeft)
		{
		PChar.CreateCharacter.Select.Count = sti(PChar.CreateCharacter.Select.Count) - 1;
		if(sti(PChar.CreateCharacter.Select.Count) <= 0) {PChar.CreateCharacter.Select.Count = iQuantity;}
		}
		else
		{
		PChar.CreateCharacter.Select.Count = sti(PChar.CreateCharacter.Select.Count) + 1;
		if(sti(PChar.CreateCharacter.Select.Count) > iQuantity) {PChar.CreateCharacter.Select.Count = 1;}
		}

		startHeroType = sti(PChar.CreateCharacter.Select.Count);
		sSex = LanguageConvertString(idLngFile, "sex_" + startHeroType);
		sAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
		if (FState_SEX[0] && sSex == "man") {continue;}
		if (FState_SEX[1] && sSex == "woman") {continue;}
		if (FState_SEX[2] && sSex == "skeleton") {continue;}
		sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
		if (FState_ANIM) {if (sAnim == "man" || sAnim == "skeleton" || sAnim == "YokoDias"  || sAnim == "Milenace") {} else continue;}
		break;//выходим из цикла, если все иф не сработали = перс подходит
	}

	sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;
	
    	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
    	PChar.HeroModel = sHeroModel;
	string sModel = GetSubStringByNum(PChar.HeroModel, 0);
	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	string sMush = LanguageConvertString(idLngFile, "heroMush_" + startHeroType);
	
	PChar.model = sModel;
	PChar.model.animation = sAni;
	SetNewModelToChar(PChar);

	CreateString(true,"SelectCharacterName", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 395,545,SCRIPT_ALIGN_CENTER,1.0);
    	LanguageCloseFile(idLngFile);
	
	curmodel = 0;
	costume = "обычный";
	SetFormatedText("ANIMATION", "Анимации");
	SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
	UpdateHeroInfo();
}

void SetNationCount(int iNation)
{
	PChar.CreateCharacter.Select.NationCount = iNation;
	
	int iNationCount = sti(PChar.CreateCharacter.Select.NationCount);
	
	string SelectCharacterNation = "";
	
	switch(iNationCount)
	{
		case 1: SelectCharacterNation = "England"; break;
		case 2: SelectCharacterNation = "France"; break;
		case 3: SelectCharacterNation = "Spain"; break;
		case 4: SelectCharacterNation = "Holland"; break;
		case 5: SelectCharacterNation = "Pirate"; break;
	}

	if(PChar.CreateCharacter != 1)
	{
		UptadeCreateInformation();
	}
}

string GetTypeToCharacter(int iType)
{
	string sType = "";
	
	switch(iType)
	{
		case 1: sType = "CreateCharacterCitizen"; break;
		case 2: sType = "CreateCharacterBarmen"; break;
		case 3: sType = "CreateCharacterTrader"; break;
		case 4: sType = "CreateCharacterUsurer"; break;
		case 5: sType = "CreateCharacterOfficer"; break;
		case 6: sType = "CreateCharacterOfficerNation"; break;
		case 7: sType = "CreateCharacterSoldier"; break;
		case 8: sType = "CreateCharacterShipyarder"; break;
		case 9: sType = "CreateCharacterSkel"; break;
		case 10: sType = "CreateCharacterPirate"; break;
		case 11: sType = "CreateCharacterAztecCitizen"; break;
		case 12: sType = "CreateCharacterAztecWarrior"; break;
	}
	
	return sType;
}

void SelectOperation(bool bSelect)
{
	SetNodeUsing("FRAME1", true);
	SetNodeUsing("FRAME2", true);
	SetNodeUsing("FRAME3", true);
	SetNodeUsing("FRAME4", true);
	SetNodeUsing("CREATE_CHARACTER", false);
	SetNodeUsing("SELECT_CHARACTER", false);
	SetNodeUsing("MAIN_QUESTION_RECTANGLE", false);
	SetNodeUsing("MAIN_QUESTION_TEXT", false);
	SetNodeUsing("ANIMATION", false);
	SetNodeUsing("COSTUME", false);
	
	GameInterface.strings.QuestionHeader = "";

	SetNodeUsing("RETURN_TO_QUESTION", true);
	
	int iFaceNumber = 0;
	int iNationCount = sti(PChar.CreateCharacter.Select.NationCount);
	
	string sName = "";
	string sLastName = "";
	string sCharacterName = "";
	
	string SelectCharacterNation = "";
	
	switch(iNationCount)
	{
		case 1: SelectCharacterNation = "England"; break;
		case 2: SelectCharacterNation = "France"; break;
		case 3: SelectCharacterNation = "Spain"; break;
		case 4: SelectCharacterNation = "Holland"; break;
		case 5: SelectCharacterNation = "Pirate"; break;
	}
		
	if(bSelect)
	{		
		SetSelectInformation();
	}
	else
	{
		SetCreateInformation();
		UptadeCreateInformation();
	}
}

void UpdateHeroInfo()
{
	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	totalInfo1 = LanguageConvertString(idLngFile, "hero_" + startHeroType);
	SetFormatedText("INFO_TEXT", totalInfo1);
    SetVAligmentFormatedText("INFO_TEXT");
	LanguageCloseFile(idLngFile);
}

void SetSelectInformation()
{
    	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
    	string sQuantity = LanguageConvertString(idLngFile, "hero_qty");
    	int iQuantity = sti(sQuantity);
    	
	PChar.CreateCharacter = 1;

	SetNodeUsing("SELECT_CHARACTER_DONE", true);
	SetNodeUsing("SELECT_CHARACTER_PICTURE", true);
	SetNodeUsing("SELECT_LEFT_BUTTON", true);
	SetNodeUsing("SELECT_RIGHT_BUTTON", true);
	SetNodeUsing("COSTUMES_LEFT_BUTTON", true);
	SetNodeUsing("CHECK_HERO_SEX", true);
	SetNodeUsing("CHECK_HERO_ANIM", true);
	SetNodeUsing("COSTUMES_RIGHT_BUTTON", true);
	SetNodeUsing("ANIMATION_LEFT_BUTTON", true);
	SetNodeUsing("ANIMATION_RIGHT_BUTTON", true);
	SetNodeUsing("ANIMATION", true);
	SetNodeUsing("COSTUME", true);
	SetNodeUsing("INFO_TEXT", true);
	
	SetFormatedText("ANIMATION", "Анимации");
	SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);

	SetNodeUsing("ENGLAND", false);
	SetNodeUsing("FRANCE", false);
	SetNodeUsing("SPAIN", false);
	SetNodeUsing("HOLLAND", false);

	sCharacterName = sName + " " + sLastName;
	CreateString(true,"SelectCharacterName", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 395,545,SCRIPT_ALIGN_CENTER,1.0);
	
	int iCount = sti(PChar.CreateCharacter.Select.Count);
	startHeroType = iCount;
	
	LanguageConvertString(idLngFile, "hero_" + startHeroType);
	
	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;
	
    	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
    	PChar.HeroModel = sHeroModel;
	string sModel = GetSubStringByNum(PChar.HeroModel, 0);
	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	string sMush = LanguageConvertString(idLngFile, "heroMush_" + startHeroType);
	
	PChar.model = sModel;
	PChar.model.animation = sAni;
	SetNewModelToChar(PChar);

	UpdateHeroInfo();
	CreateString(true,"SelectCharacterName", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 395,545,SCRIPT_ALIGN_CENTER,1.0);
	
    LanguageCloseFile(idLngFile);
}

void SetCreateInformation()
{
    	if(PChar.SuccessPrice.CreateCharacter == true)
    	{
		SetNodeUsing("RETURN_TO_QUESTION", false);
		SetSelectable("NAME_STRING", false);
		SetSelectable("NAME_STRING_2", false);
		SetSelectable("NAME_STRING_3", false);
		SetSelectable("LAST_NAME_STRING", false);
		SetSelectable("LAST_NAME_STRING_2", false);
		SetSelectable("LAST_NAME_STRING_3", false);
		
		GameInterface.NAME_STRING.str = "...";
		GameInterface.NAME_STRING_2.str = "...";
		GameInterface.NAME_STRING_3.str = "...";
		GameInterface.LAST_NAME_STRING.str = "...";
		GameInterface.LAST_NAME_STRING_2.str = "...";
		GameInterface.LAST_NAME_STRING_3.str = "...";
    	}

	PChar.CreateCharacter = 2;
	
	int TextFile = LanguageOpenFile("CreateCharacter.txt");
	int iQtyMax = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_qty"));
	string sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount);
	string sModelTypeName = LanguageConvertString(TextFile, "type_" + iTypeCount + "_name");
	string ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_ani");
	string sNeedNation = LanguageConvertString(TextFile, "type_" + iTypeCount + "_nn");
	string sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_sex");
	string sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_mush");
	string sModel = "";
	int iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_face"));
	
	int iFaceNumber = 0;
	int iNationCount = sti(PChar.CreateCharacter.Select.NationCount);
	
	string sName = "";
	string sLastName = "";
	string sCharacterName = "";
	
	string SelectCharacterNation = "";
	string sNationPrefix = "";
	string sNationSoldierPrefix = "";
	
	switch(iNationCount)
	{
		case 1: SelectCharacterNation = "England"; sNationPrefix = "eng"; break;
		case 2: SelectCharacterNation = "France"; sNationPrefix = "fra"; break;
		case 3: SelectCharacterNation = "Spain"; sNationPrefix = "spa"; break;
		case 4: SelectCharacterNation = "Holland"; sNationPrefix = "hol"; break;
		case 5: SelectCharacterNation = "Pirate"; sNationPrefix = ""; break;
	}
	
	if(sNeedNation == "yes")
	{
		sModelType += sNationPrefix + "_";
		sMush = sNationPrefix + sMush;
	}
	
	if(sModelType == "Other")
	{
		sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_model");
		ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_ani");
		sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_sex");
		sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_mush");
		sModel = sModelType;
		iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_face"));
	}
	else
	{
		sModel = sModelType + iVarCount;
	}
	
	SetNodeUsing("CREATE_CHARACTER_DONE", true);
	
	SetNodeUsing("ENGLAND", true);
	SetNodeUsing("FRANCE", true);
	SetNodeUsing("SPAIN", true);
	SetNodeUsing("HOLLAND", true);
	SetNodeUsing("PIRATE", true);

	SetNodeUsing("FRAME1", true);
	SetNodeUsing("FRAME2", true);
	SetNodeUsing("FRAME3", true);
	SetNodeUsing("FRAME4", true);
	SetNodeUsing("BORDERS", true);
	SetNodeUsing("CREATE_LEFT_BUTTON", true);
	SetNodeUsing("CREATE_RIGHT_BUTTON", true);
	SetNodeUsing("SELECT_TYPE_LEFT_BUTTON", true);
	SetNodeUsing("SELECT_TYPE_RIGHT_BUTTON", true);
	SetNodeUsing("CREATE_CHARACTER_PICTURE", true);
	SetNodeUsing("NAME_STRING", true);
	SetNodeUsing("NAME_STRING_2", true);
	SetNodeUsing("NAME_STRING_3", true);
	SetNodeUsing("LAST_NAME_STRING", true);
	SetNodeUsing("LAST_NAME_STRING_2", true);
	SetNodeUsing("LAST_NAME_STRING_3", true);

	sName = GameInterface.NAME_STRING.str;
	sLastName = GameInterface.LAST_NAME_STRING.str;

	sCharacterName = sName + " " + sLastName;
	
    	if(PChar.SuccessPrice.CreateCharacter == true)
    	{
    		sCharacterName = GetName(PChar, "f");
    	}
    	
	string sType = GetTypeToCharacter(iType);
	
	PChar.model = sModel;
	PChar.model.animation = ani;
	PChar.sex = sSex;
	PChar.FaceId = iFaceID;
	SetNewModelToChar(PChar);
	FaceMaker(PChar);

	CreateString(true,"CreateCharacterName", "Вариант " + iVarCount + " из " + iQtyMax, FONT_CAPTION, COLOR_NORMAL, 405,18,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterHeader", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 140,18,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringName", "Имя: ", FONT_CAPTION, COLOR_NORMAL, 140,58,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringName2", "Имя в родительном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,118,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringName3", "Имя в дательном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,178,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringLastName", "Фамилия: ", FONT_CAPTION, COLOR_NORMAL, 140,243,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringLastName2", "Фамилия в родительном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,303,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterStringLastName3", "Фамилия в дательном падеже: ", FONT_CAPTION, COLOR_NORMAL, 140,363,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringTypeCharacter", "Тип внешности: ", FONT_CAPTION, COLOR_NORMAL, 140,432,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CreateCharacterType", sType, FONT_CAPTION, COLOR_NORMAL, 140,458,SCRIPT_ALIGN_CENTER,1.0);
	
	CreateString(true,"CreateCharacterStringNation", "Выбор по нации: ", FONT_CAPTION, COLOR_NORMAL, 140,495,SCRIPT_ALIGN_CENTER,1.0);
	LanguageCloseFile(TextFile);
    	
    	if(PChar.SuccessPrice.CreateCharacter == true && PChar.SuccessPrice.CreateCharacter.Model == PChar.model)
    	{
    		SetSelectable("CREATE_CHARACTER_DONE", false);
    	}
    	else
    	{
    		SetSelectable("CREATE_CHARACTER_DONE", true);
    	}
}

void CreateCharacterDone()
{	
	int TextFile = LanguageOpenFile("CreateCharacter.txt");
	int iQtyMax = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_qty"));
	string sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount);
	string sModelTypeName = LanguageConvertString(TextFile, "type_" + iTypeCount + "_name");
	string ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_ani");
	string sNeedNation = LanguageConvertString(TextFile, "type_" + iTypeCount + "_nn");
	string sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_sex");
	string sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_mush");
	int iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_face"));
	
	int iNationCount = sti(PChar.CreateCharacter.Select.NationCount);
	
	string sModel = "";
	string sAnimation = "";

	string SelectCharacterNation = "";
	string sNationPrefix = "";
	string sNationSoldierPrefix = "";
	
	int iNation = 0;
	
	switch(iNationCount)
	{
		case 1: sNationPrefix = "eng"; iNation = ENGLAND; break;
		case 2: sNationPrefix = "fra"; iNation = FRANCE; break;
		case 3: sNationPrefix = "spa"; iNation = SPAIN; break;
		case 4: sNationPrefix = "hol"; iNation = HOLLAND; break;
		case 5: sNationPrefix = ""; iNation = PIRATE; break;
	}
	
	if(sNeedNation == "yes")
	{
		sModelType += sNationPrefix + "_";
		sMush = sNationPrefix + sMush;
	}
	
	if(sModelType == "Other")
	{
		sModelType = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_model");
		ani = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_ani");
		sModel = sModelType;
		sSex = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_sex");
		sMush = LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_mush");
		iFaceID = sti(LanguageConvertString(TextFile, "type_" + iTypeCount + "_" + iVarCount + "_face"));
	}
	else
	{
		sModel = sModelType + iVarCount;
	}
	string sType = sModelTypeName;
	
	PChar.model = sModel;
	PChar.model.animation = ani;
	PChar.sex = sSex;

	string sName = GameInterface.NAME_STRING.str;
	string sLastName = GameInterface.LAST_NAME_STRING.str;

    	if(PChar.SuccessPrice.CreateCharacter != true)
    	{
		PChar.name = sName;
		PChar.lastname = sLastName;
		PChar.Created = true;
		PChar.Created.Name2 = GameInterface.NAME_STRING_2.str;
		PChar.Created.Name3 = GameInterface.NAME_STRING_3.str;
		PChar.Created.LastName2 = GameInterface.LAST_NAME_STRING_2.str;
		PChar.Created.LastName3 = GameInterface.LAST_NAME_STRING_3.str;
	}
	
	string sCharacterName = sName + " " + sLastName;
    	if(PChar.SuccessPrice.CreateCharacter == true)
    	{
    		sCharacterName = GetName(PChar, "f");
    	}
    	
	PlaySound("notebook");
	if(PChar.SuccessPrice.CreateCharacter != true)
	{
		Log_SetStringToLog("Создан персонаж " + sCharacterName + ".");
	}
	
	PChar.FaceId = iFaceID;
	SetNewModelToChar(PChar);
	FaceMaker(PChar);
	
		
	LanguageCloseFile(TextFile);
	
    	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
    	string sQuantity = LanguageConvertString(idLngFile, "hero_qty");
    	int iQuantity = sti(sQuantity) + 1;
	LanguageCloseFile(idLngFile);
    	
	PChar.DefaultModel = PChar.model;
	
    	if(PChar.SuccessPrice.CreateCharacter != true)
    	{
		startHeroType = iQuantity;
		initNewMainCharacter();
	}
	
	if(PChar.model == "Hero1" || PChar.model == "Blood5")
	{
		PChar.DefaultMusketeerModel.NotChange = true;
	}
	
	ProcessCancelExit();
}

void ReturnToQuestion()
{
	SetNodeUsing("FRAME1", false);
	SetNodeUsing("FRAME2", true);
	SetNodeUsing("CREATE_CHARACTER", true);
	SetNodeUsing("SELECT_CHARACTER", true);
	SetNodeUsing("MAIN_QUESTION_RECTANGLE", true);
	SetNodeUsing("MAIN_QUESTION_TEXT", true);
	
	SetNodeUsing("CREATE_CHARACTER_DONE", false);
	SetNodeUsing("SELECT_CHARACTER_DONE", false);
	SetNodeUsing("RETURN_TO_QUESTION", false);
	SetNodeUsing("BORDERS", false);
	SetNodeUsing("SELECT_CHARACTER_PICTURE", false);
	SetNodeUsing("SELECT_LEFT_BUTTON", false);
	SetNodeUsing("SELECT_RIGHT_BUTTON", false);
	SetNodeUsing("COSTUMES_LEFT_BUTTON", false);
	SetNodeUsing("CHECK_HERO_SEX", false);
	SetNodeUsing("CHECK_HERO_ANIM", false);
	SetNodeUsing("COSTUMES_RIGHT_BUTTON", false);
	SetNodeUsing("ANIMATION_LEFT_BUTTON", false);
	SetNodeUsing("ANIMATION_RIGHT_BUTTON", false);
	SetNodeUsing("ANIMATION", false);
	SetNodeUsing("COSTUME", false);
	SetNodeUsing("INFO_TEXT", false);
	
	GameInterface.strings.Header = "";
	GameInterface.strings.SelectCharacterName = "";
	
	GameInterface.pictures.SelectCharacterNation.tex = "";
	GameInterface.pictures.SelectCharacterNation.pic = "";
	
	PChar.CreateCharacter = 1;
	PChar.CreateCharacter.Select.Count = 1;
	PChar.CreateCharacter.Select.NationCount = 5;
	
	SetSelectable("ENGLAND", true);
	SetSelectable("FRANCE", true);
	SetSelectable("SPAIN", true);
	SetSelectable("HOLLAND", true);
	
	SetNodeUsing("ENGLAND", false);
	SetNodeUsing("FRANCE", false);
	SetNodeUsing("SPAIN", false);
	SetNodeUsing("HOLLAND", false);
	
	SetNodeUsing("FRAME1", true);
	SetNodeUsing("FRAME2", true);
	SetNodeUsing("FRAME3", true);
	SetNodeUsing("FRAME4", true);
	SetNodeUsing("BORDERS", false);
	SetNodeUsing("CREATE_LEFT_BUTTON", false);
	SetNodeUsing("CREATE_RIGHT_BUTTON", false);
	SetNodeUsing("SELECT_TYPE_LEFT_BUTTON", false);
	SetNodeUsing("SELECT_TYPE_RIGHT_BUTTON", false);
	SetNodeUsing("CREATE_CHARACTER_PICTURE", false);
	SetNodeUsing("NAME_STRING", false);
	SetNodeUsing("NAME_STRING_2", false);
	SetNodeUsing("NAME_STRING_3", false);
	SetNodeUsing("LAST_NAME_STRING", false);
	SetNodeUsing("LAST_NAME_STRING_2", false);
	SetNodeUsing("LAST_NAME_STRING_3", false);
	
	GameInterface.strings.CreateCharacterName = "";
	GameInterface.strings.CreateCharacterHeader = "";
	GameInterface.strings.CreateCharacterStringName = "";
	GameInterface.strings.CreateCharacterStringLastName = "";
	GameInterface.strings.CreateCharacterStringTypeCharacter = "";
	GameInterface.strings.CreateCharacterType = "";
	GameInterface.strings.CreateCharacterStringName2 = "";
	GameInterface.strings.CreateCharacterStringName3 = "";
	GameInterface.strings.CreateCharacterStringLastName2 = "";
	GameInterface.strings.CreateCharacterStringLastName3 = "";
	GameInterface.strings.CreateCharacterStringNation = "";
	LAi_SetActorTypeNoGroup(PChar);
	LAi_ActorAnimation(pchar,"idle_"+(rand(10)+1),"",0.6);
}

void SetDataInformation()
{
	CreateString(true,"Header","", FONT_CAPTION, COLOR_NORMAL, 395,63,SCRIPT_ALIGN_CENTER,1.0);
	
	SetFormatedText("MAIN_QUESTION_TEXT", "Открыть меню выбора персонажа.");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"MAIN_QUESTION_TEXT",5);
	
	GameInterface.strings.SelectCharacterName = "";
	
	GameInterface.pictures.SelectCharacterNation.tex = "";
	GameInterface.pictures.SelectCharacterNation.pic = "";
	
	SetNodeUsing("ENGLAND", false);
	SetNodeUsing("FRANCE", false);
	SetNodeUsing("SPAIN", false);
	SetNodeUsing("HOLLAND", false);
	SetNodeUsing("PIRATE", false);
	
	SetNodeUsing("CREATE_CHARACTER_DONE", false);
	SetNodeUsing("SELECT_CHARACTER_DONE", false);
	SetNodeUsing("RETURN_TO_QUESTION", false);
	SetNodeUsing("BORDERS", false);
	SetNodeUsing("SELECT_CHARACTER_PICTURE", false);
	SetNodeUsing("BORDERS_SELECT_CHARACTER", false);
	SetNodeUsing("SELECT_LEFT_BUTTON", false);
	SetNodeUsing("SELECT_RIGHT_BUTTON", false);
	SetNodeUsing("COSTUMES_LEFT_BUTTON", false);
	SetNodeUsing("CHECK_HERO_SEX", false);
	SetNodeUsing("CHECK_HERO_ANIM", false);
	SetNodeUsing("COSTUMES_RIGHT_BUTTON", false);
	SetNodeUsing("ANIMATION_LEFT_BUTTON", false);
	SetNodeUsing("ANIMATION_RIGHT_BUTTON", false);
	SetNodeUsing("ANIMATION", false);
	SetNodeUsing("COSTUME", false);
	SetNodeUsing("INFO_TEXT", false);
	
	SetNodeUsing("FRAME1", true);
	SetNodeUsing("FRAME2", true);
	SetNodeUsing("FRAME3", true);
	SetNodeUsing("FRAME4", true);
	SetNodeUsing("BORDERS_CREATE_CHARACTER", false);
	SetNodeUsing("CREATE_LEFT_BUTTON", false);
	SetNodeUsing("CREATE_RIGHT_BUTTON", false);
	SetNodeUsing("SELECT_TYPE_LEFT_BUTTON", false);
	SetNodeUsing("SELECT_TYPE_RIGHT_BUTTON", false);
	SetNodeUsing("CREATE_CHARACTER_PICTURE", false);
	SetNodeUsing("NAME_STRING", false);
	SetNodeUsing("NAME_STRING_2", false);
	SetNodeUsing("NAME_STRING_3", false);
	SetNodeUsing("LAST_NAME_STRING", false);
	SetNodeUsing("LAST_NAME_STRING_2", false);
	SetNodeUsing("LAST_NAME_STRING_3", false);
	
	GameInterface.strings.CreateCharacterName = "";
	GameInterface.strings.CreateCharacterHeader = "";
	GameInterface.strings.CreateCharacterStringName = "";
	GameInterface.strings.CreateCharacterStringLastName = "";
	GameInterface.strings.CreateCharacterStringTypeCharacter = "";
	GameInterface.strings.CreateCharacterType = "";
	GameInterface.pictures.CreateCharacterNation.tex = "";
    	GameInterface.pictures.CreateCharacterNation.pic = "";
    	
    	if(PChar.SuccessPrice.CreateCharacter == true)
    	{
		SetFormatedText("MAIN_QUESTION_TEXT", "");
    		SelectOperation(false);
    	}
}

void ProcessFilter()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
	int idLngFile;
//========================================//
	if (sControl == "CHECK_HERO_SEX")
	{
	FState_SEX[iSelectedCB-1] = iNewState;
	if (!iNewState && FState_SEX[0]+FState_SEX[1]+FState_SEX[2] == 1)//нужно разлочить кнопку
	{
		for(i=1;i<4;i++) {SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 5, i, 0);} //разблочим все кнопки
	}
	if (FState_SEX[0]+FState_SEX[1]+FState_SEX[2] == 2) //блочим оставшийся единственным ненажатым чекбокс. иначе вообще все герои будут недоступны и бесконечный цикл
	{
		for(i=1;i<4;i++)
		{
			if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 3, i)) continue;
				else {SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 5, i, 1); break;}//блочим ненажатую кнопку и выходим из цикла, так как она одна
		}
	}
	if (iNewState) //отключили какой-то пол
	{
	idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sSex = LanguageConvertString(idLngFile, "sex_" + startHeroType);
	switch (iSelectedCB-1)
		{
		case 0: if (sSex == "man") SelectMainCharacter(0); break;//если был выбран муж. и мы сняли чекбокс муж., то переходим к следующему персу
		case 1: if (sSex == "woman") SelectMainCharacter(0); break;
		case 2: if (sSex == "skeleton") SelectMainCharacter(0); break;
		}
	LanguageCloseFile(idLngFile);
	}
	return;
	}
//========================================//
	if (sControl == "CHECK_HERO_ANIM")
	{
	FState_ANIM = iNewState;
	if (iNewState) //отключили анимки
	{
	idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	if (FState_ANIM) {if (sAnim == "man" || sAnim == "skeleton" || sName == "Виспер") {} else SelectMainCharacter(0);}
	LanguageCloseFile(idLngFile);
	}
	return;
	}
}