/// BOAL ���� ���������
ref xi_refCharacter;
int nCurScrollNum, nCurScrollOfficerNum;
string CurTable, CurRow;
int iSelected; // ������ � �������
bool bChangePIRATES;

void InitInterface_R(string iniName, ref _char)
{
	xi_refCharacter = _char;
	GameInterface.title = "titleCharacter";

    bChangePIRATES = false;
    if (CheckAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES"))
    {
    	bChangePIRATES = true;
    	DeleteAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES");
	}
	GameInterface.StatusLine.LOYALITY.Max = 1;
    GameInterface.StatusLine.LOYALITY.Min = 0;
    GameInterface.StatusLine.LOYALITY.Value = 0;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ChoosePerk","ChoosePerk",0);
	SetEventHandler("ExitPerkMenu","ExitPerkMenu",0);
	SetEventHandler("AcceptPerk","AcceptPerk",0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);

    EI_CreateFrame("CHARACTER_BIG_PICTURE_BORDER",369,78,579,315); // take from CHARACTER_BIG_PICTURE
    EI_CreateHLine("CHARACTER_BIG_PICTURE_BORDER", 373,104,575,1, 4);

    SetVariable();
    SetCurrentNode("TABLE_OTHER");
    SetFormatedText("LOYALITY_STR", XI_ConvertString("Loyality"));
    HideSkillChanger();
    SetNodeUsing("GAME_ACCEPT", false);
    SetNodeUsing("GAME_CANCEL", false);
    if (bChangePIRATES)
    {
    	ShowMsgMenu(); // ���� �� ������ � ������
    }
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	if (bChangePIRATES)
	{
		xi_refCharacter.skill.FreeSPECIAL = 0; // ���� �� ��� �����������, ��� �����
		
		if (startherotype > 11)//��� ���������� ������� ���� ������ ������
		{
    		ref sld = characterFromID("Sailor_1");
    		LAi_SetActorTypeNoGroup(pchar);
    	    LAi_SetActorTypeNoGroup(sld);
    	    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
    	    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
        }//homo
    }
		    
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ChoosePerk","ChoosePerk");
	DelEventHandler("ExitPerkMenu","ExitPerkMenu");
	DelEventHandler("AcceptPerk","AcceptPerk");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");

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
        case "B_SKILLUP":
			if (comName=="click")
			{
                IncreaseSkill(1);
			}
			if (comName=="rclick")
			{
                IncreaseSkill(5);
			}
		break;

		case "B_SKILLDOWN":
	        if (comName=="click")
			{
			    DecreaseSkill(1);
			}
			if (comName=="rclick")
			{
			    DecreaseSkill(5);
			}
		break;
		/////////////////////// menu ///////////////
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}

void SetVariable()
{
	FillSkillTables();
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + xi_refCharacter.FaceId + ".tga");
	string texturedata;
	if (IsCharacterPerkOn(xi_refCharacter, "Grunt")) texturedata = "INTERFACES\Sith\Char_Master.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "Trader")) texturedata = "INTERFACES\Sith\Char_Merchant.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "Fencer")) texturedata = "INTERFACES\Sith\Char_Corsair.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "Adventurer")) texturedata = "INTERFACES\Sith\Char_Adventurer.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "Buccaneer")) texturedata = "INTERFACES\Sith\Char_Inquisitor.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "Agent")) texturedata = "INTERFACES\Sith\Char_SecretAgent.tga";
	if (IsCharacterPerkOn(xi_refCharacter, "SeaWolf")) texturedata = "INTERFACES\Sith\Char_SeaWolf.tga";
	SetNewPicture("CHARACTER_PROFESSION", texturedata);
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));

    // ������ ��� ����������
    GameInterface.StatusLine.LOYALITY.Max   = MAX_LOYALITY;
    GameInterface.StatusLine.LOYALITY.Min   = 0;
    GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);
    if (xi_refCharacter.id == pchar.id)
    {
	    GameInterface.StatusLine.BAR_HEALTH.Max   = 54;
	    GameInterface.StatusLine.BAR_HEALTH.Min   = 1;
	    GameInterface.StatusLine.BAR_HEALTH.Value = makeint(pchar.Health.HP);
	    if (sti(pchar.Health.HP) > 54 )
	    {
	        GameInterface.StatusLine.BAR_HEALTH.Value = 54;
	    }
    }
    else
    {
        GameInterface.StatusLine.BAR_HEALTH.Max = 1;
        GameInterface.StatusLine.BAR_HEALTH.Min = 0;
        GameInterface.StatusLine.BAR_HEALTH.Value = 0;
    }
    GameInterface.StatusLine.BAR_REPUTATION.Max   = REPUTATION_MAX;
    GameInterface.StatusLine.BAR_REPUTATION.Min   = REPUTATION_MIN;
    GameInterface.StatusLine.BAR_REPUTATION.Value = makeint(xi_refCharacter.reputation);

    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LOYALITY",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_HEALTH",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_REPUTATION",0);

    if (sti(xi_refCharacter.Skill.FreeSkill) > 0)
	{
        SetFormatedText("FREE_SKILL", xi_refCharacter.Skill.FreeSkill);
    }
    else
    {
        SetFormatedText("FREE_SKILL", "");
    }
    if (sti(xi_refCharacter.Skill.FreeSPECIAL) > 0)
	{
        SetFormatedText("FREE_SPECIAL", xi_refCharacter.Skill.FreeSPECIAL);
    }
    else
    {
        SetFormatedText("FREE_SPECIAL", "");
    }
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	string text5, text6;
	if (IsCharacterPerkOn(xi_refCharacter, "Grunt")) {text5 = "������"; text6 = GetConvertStr("Master", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "Trader")) {text5 = "��������";  text6 = GetConvertStr("Merchant", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "Fencer")) {text5 = "������������";  text6 = GetConvertStr("Corsair", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "Adventurer")) {text5 = "����������";  text6 = GetConvertStr("Adventurer", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "Buccaneer")) {text5 = "��������";  text6 = GetConvertStr("Inquisitor", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "Agent")) {text5 = "������ �����";  text6 = GetConvertStr("SecretAgent", "HeroDescribe.txt");}
	if (IsCharacterPerkOn(xi_refCharacter, "SeaWolf")) {text5 = "������� ����";  text6 = GetConvertStr("SeaWolf", "HeroDescribe.txt");}

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_SPECIAL":
		    sHeader = XI_ConvertString("Characteristics");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SKILL_1":
		    sHeader = XI_ConvertString("Personal skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SKILL_2":
		    sHeader = XI_ConvertString("Ship skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "LOYALITY_STR":
		    sHeader = XI_ConvertString("Loyality");
		    sText1  = GetRPGText("Loyality");
		break;
		case "TABBTN_1":
		    sHeader = XI_ConvertString("Personal abilities");
		    sText1  = GetRPGText("Personal_abilities");
		break;
		case "TABBTN_2":
		    sHeader = XI_ConvertString("Ship abilities");
		    sText1  = GetRPGText("Ship_abilities");
		break;
		case "TABLE_OTHER":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SHIP_OTHERS":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_BLADES_OTHERS":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_CHAR_OTHERS":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_PERKS":
		    sHeader = GetRPGText("TABLE_PERKS");
		    sText1  = GetRPGText("TABLE_PERKS_desc");
		break;
		case "PERK_TABLE_NEED":
		    sHeader = GetRPGText("PERK_TABLE_NEED");
		    sText1  = GetRPGText("PERK_TABLE_NEED_desc");
		break;
		case "CHARACTER_PROFESSION":
		    sHeader = text5;
			sText1 = text6;
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}

void HideInfoWindow()
{
	CloseTooltip();
}

void FillSkillTables()
{
	int     i;
	string  row, skillName;
    int     diff, skillVal;

    // boal ����������� ������ -->
    DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);

    SetEnergyToCharacter(xi_refCharacter);
    // boal ����������� ������ <--

    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self") )
		xi_refCharacter.perks.FreePoints_self = 0;
    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship") )
		xi_refCharacter.perks.FreePoints_ship = 0;

    SetFormatedText("TABSTR_1", XI_ConvertString("Personal_abilities") + " " +xi_refCharacter.perks.FreePoints_self);
    SetFormatedText("TABSTR_2", XI_ConvertString("Ship_abilities") + " " + xi_refCharacter.perks.FreePoints_ship);
    SetControlsTabMode(3);

	GameInterface.TABLE_SPECIAL.select = 0;
	GameInterface.TABLE_SPECIAL.hr.td1.str = "";
	SetFormatedText("STR_1", XI_ConvertString("Characteristics"));

	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

        GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "3,-5";
		GameInterface.TABLE_SPECIAL.(row).td1.scale = 0.75;
		GameInterface.TABLE_SPECIAL.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_SPECIAL.(row).td2.scale = 0.9;
		GameInterface.TABLE_SPECIAL.(row).td2.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td3.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td4.scale = 0.8;
		GameInterface.TABLE_SPECIAL.(row).td4.fontidx = 1;
		GameInterface.TABLE_SPECIAL.(row).td4.textoffset = "0,-1";

		GameInterface.TABLE_SPECIAL.(row).td1.str = XI_ConvertString(skillName + "T");
		GameInterface.TABLE_SPECIAL.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, skillName);
		GameInterface.TABLE_SPECIAL.(row).td4.str = skillVal;
		// ������� ������
		diff = GetCharacterSPECIAL(xi_refCharacter, skillName) - skillVal;
		if (diff == 0)
		{
     		GameInterface.TABLE_SPECIAL.(row).td3.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SPECIAL." + row + ".td3.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(+" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,255,196,196);
	       }
		}
	}
    GameInterface.TABLE_SKILL_1.select = 0;
    GameInterface.TABLE_SKILL_1.hr.td1.str = "";
	SetFormatedText("STR_2", XI_ConvertString("Personal skill"));
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

        GameInterface.TABLE_SKILL_1.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_1.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.width = 22;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.height = 22;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_SKILL_1.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td2.scale = 0.85;
		GameInterface.TABLE_SKILL_1.(row).td2.textoffset = "0,0";
		GameInterface.TABLE_SKILL_1.(row).td3.scale = 0.85;
		GameInterface.TABLE_SKILL_1.(row).td4.scale = 0.85;
		GameInterface.TABLE_SKILL_1.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_1.(row).td5.scale = 0.65;
		GameInterface.TABLE_SKILL_1.(row).td5.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td5.textoffset = "-1,0";

		GameInterface.TABLE_SKILL_1.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_1.(row).td5.str = skillVal;
		// ������� ������
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_1.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_1.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_1.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_1." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	GameInterface.TABLE_SKILL_2.select = 0;
	GameInterface.TABLE_SKILL_2.hr.td1.str = "";
	SetFormatedText("STR_3", XI_ConvertString("Ship skill"));
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

        GameInterface.TABLE_SKILL_2.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_2.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.width = 22;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.height = 22;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_SKILL_2.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td2.scale = 0.85;
		GameInterface.TABLE_SKILL_2.(row).td2.textoffset = "0,0";
		GameInterface.TABLE_SKILL_2.(row).td3.scale = 0.85;
		GameInterface.TABLE_SKILL_2.(row).td4.scale = 0.85;
		GameInterface.TABLE_SKILL_2.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_2.(row).td5.scale = 0.65;
		GameInterface.TABLE_SKILL_2.(row).td5.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td5.textoffset = "-1,0";

		GameInterface.TABLE_SKILL_2.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_2.(row).td5.str = skillVal;
		// ������� ������
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_2.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_2.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_2.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_2." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	////  ���������
	GameInterface.TABLE_OTHER.select = 0;
	GameInterface.TABLE_OTHER.hr.td1.str = "";
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.TABLE_OTHER.(row).td1.icon.width = 26;
    	GameInterface.TABLE_OTHER.(row).td1.icon.height = 26;
    	GameInterface.TABLE_OTHER.(row).td1.icon.offset = "-1, 0";
		GameInterface.TABLE_OTHER.(row).td2.align = "left";
		GameInterface.TABLE_OTHER.(row).td2.scale = 0.9;
		GameInterface.TABLE_OTHER.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_OTHER.(row).td3.align = "right";
	}
	GameInterface.TABLE_OTHER.tr1.UserData.ID = "Rank";
	GameInterface.TABLE_OTHER.tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr1.td1.icon.image = "Rank";
	GameInterface.TABLE_OTHER.tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.TABLE_OTHER.tr1.td3.str = sti(xi_refCharacter.rank);
	GameInterface.TABLE_OTHER.tr1.td3.scale = 0.9;

	GameInterface.TABLE_OTHER.tr2.UserData.ID = "Life";
	GameInterface.TABLE_OTHER.tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr2.td1.icon.image = "Life";
	GameInterface.TABLE_OTHER.tr2.td2.str = XI_ConvertString("Life");
	GameInterface.TABLE_OTHER.tr2.td3.str = MakeInt(LAi_GetCharacterHP(xi_refCharacter)) + " / " + MakeInt(LAi_GetCharacterMaxHP(xi_refCharacter));
	GameInterface.TABLE_OTHER.tr2.td3.scale = 0.9;

    GameInterface.TABLE_OTHER.tr3.UserData.ID = "Health";
	GameInterface.TABLE_OTHER.tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr3.td1.icon.image = "Health";
	// GameInterface.TABLE_OTHER.tr3.td2.textoffset = "0,-2";
	GameInterface.TABLE_OTHER.tr3.td2.str = XI_ConvertString("Health");
	GameInterface.TABLE_OTHER.tr3.td3.str = GetHealthName(xi_refCharacter);
	GameInterface.TABLE_OTHER.tr3.td3.scale = 0.9;

	if (GetHealthNum(xi_refCharacter) >= GetHealthMaxNum(xi_refCharacter))
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));
    }
    else
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_NORMAL, GetAlphaFromSkill(makeint(GetHealthNum(xi_refCharacter)* 1.9)));
    }

    GameInterface.TABLE_OTHER.tr4.UserData.ID = "Energy";
	GameInterface.TABLE_OTHER.tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr4.td1.icon.image = "Energy";
	GameInterface.TABLE_OTHER.tr4.td2.str = XI_ConvertString("Energy");
	GameInterface.TABLE_OTHER.tr4.td3.scale = 0.9;
	GameInterface.TABLE_OTHER.tr4.td3.str = sti(Lai_CharacterGetEnergy(xi_refCharacter)) + " / " + sti(LAi_GetCharacterMaxEnergy(xi_refCharacter));
	diff = sti(LAi_GetCharacterMaxEnergy(xi_refCharacter) - GetCharacterMaxEnergyABSValue(xi_refCharacter));
	if (diff != 0)
	{
	   if (diff > 0)
	   {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,196,255,196);
       }
       else
       {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,255,196,196);
       }
	}
	else
	{
		DeleteAttribute(&GameInterface, "TABLE_OTHER.tr4.td3.color");
	}

	GameInterface.TABLE_OTHER.tr5.UserData.ID = "Money";
	GameInterface.TABLE_OTHER.tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr5.td1.icon.image = "Money";
	GameInterface.TABLE_OTHER.tr5.td2.str = XI_ConvertString("Money");
	GameInterface.TABLE_OTHER.tr5.td3.str = MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER);
	GameInterface.TABLE_OTHER.tr5.td3.scale = 0.9;
	//GameInterface.TABLE_OTHER.tr5.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));

    GameInterface.TABLE_OTHER.tr6.UserData.ID = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr6.td1.icon.image = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td2.str = XI_ConvertString("Reputation");
	// GameInterface.TABLE_OTHER.tr6.td2.textoffset = "0,-2";
	GameInterface.TABLE_OTHER.tr6.td3.str = XI_ConvertString(GetReputationName(sti(xi_refCharacter.reputation)));
	GameInterface.TABLE_OTHER.tr6.td3.scale = 0.9;

	GameInterface.TABLE_OTHER.tr7.UserData.ID = "weight";
	GameInterface.TABLE_OTHER.tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr7.td1.icon.image = "weight";
	GameInterface.TABLE_OTHER.tr7.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_OTHER.tr7.td3.str = FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter);
	GameInterface.TABLE_OTHER.tr7.td3.scale = 0.9;

    GameInterface.TABLE_OTHER.tr8.UserData.ID = "Title";
	GameInterface.TABLE_OTHER.tr8.td1.icon.group = "ICONS_CHAR";
	GameInterface.TABLE_OTHER.tr8.td1.icon.image = "Title";

	DeleteAttribute(&GameInterface, "TABLE_OTHER.tr8.td2");
	GameInterface.TABLE_OTHER.tr8.td2.str = XI_ConvertString("Title");
	GameInterface.TABLE_OTHER.tr8.td2.align = "left";
	GameInterface.TABLE_OTHER.tr8.td2.scale = 0.9;
	GameInterface.TABLE_OTHER.tr8.td2.textoffset = "5,0";

    DeleteAttribute(&GameInterface, "TABLE_OTHER.tr8.td3");
    GameInterface.TABLE_OTHER.tr8.td3.str = "";
	GameInterface.TABLE_OTHER.tr8.td3.scale = 0.9;

	if (xi_refCharacter.id == pchar.id && isMainCharacterPatented())
    {
        GameInterface.TABLE_OTHER.tr8.td3.str = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur));
		GameInterface.TABLE_OTHER.tr8.td3.align = "right";
        GameInterface.TABLE_OTHER.tr8.td2.icon.group = "NATIONS";
		GameInterface.TABLE_OTHER.tr8.td2.icon.image = GetNationNameByType(sti(Items[sti(pchar.EquipedPatentId)].Nation));
		GameInterface.TABLE_OTHER.tr8.td2.icon.offset = "120, 1";
		GameInterface.TABLE_OTHER.tr8.td2.icon.width = 26;
		GameInterface.TABLE_OTHER.tr8.td2.icon.height = 26;
    }
    else
    {
        GameInterface.TABLE_OTHER.tr8.td3.str = "��� ������";
		GameInterface.TABLE_OTHER.tr8.td3.align = "right";
    }

	GameInterface.TABLE_OTHER.tr9.UserData.ID = "NextExp";
	GameInterface.TABLE_OTHER.tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr9.td1.icon.image = "NextExp";
	GameInterface.TABLE_OTHER.tr9.td2.str = XI_ConvertString("NextExp");
	GameInterface.TABLE_OTHER.tr9.td3.str = "";
	GameInterface.TABLE_OTHER.tr9.td3.scale = 0.8;

	// ����������
	Table_UpdateWindow("TABLE_SPECIAL");
    Table_UpdateWindow("TABLE_SKILL_1");
    Table_UpdateWindow("TABLE_SKILL_2");
    Table_UpdateWindow("TABLE_PERKS");
    Table_UpdateWindow("TABLE_OTHER");
}

//������ ������� ����������� � ������� - Gregg
string ShowStatValue(string type)
{
	switch (type)
	{
		case "crit":
			return CheckForSpecial(type);
		break;
		case "regenhp":
			string value = FloatToString(GetCharacterRegenHP(xi_refCharacter, false),2);
			return value;
		break;
		case "energychar":
			float fMultiplierE = 1.6666667;
			if(CheckCharacterPerk(xi_refCharacter, "Energaiser")) // ������� ���� ������ � ��
			{
				fMultiplierE = fMultiplierE * 1.5;
			}
			if(CheckCharacterPerk(xi_refCharacter, "Tireless")) 
			{
				fMultiplierE = fMultiplierE * 1.15;
			}
			return FloatToString(fMultiplierE,2);
		break;
		case "accuracy":
			int accuracy = makeint(LAi_GunCalcProbability(xi_refCharacter, 0.01)*100.0);
			if (accuracy > 100) return "100%";
			else return accuracy+"%";
		break;
		case "gundamage":
			float min = 0.0;
			float max = 0.0;
			if(CheckAttribute(xi_refCharacter, "chr_ai.dmggunmin"))
			{
				min = stf(xi_refCharacter.chr_ai.dmggunmin);
			}
			if(CheckAttribute(xi_refCharacter, "chr_ai.dmggunmax"))
			{
				max = stf(xi_refCharacter.chr_ai.dmggunmax);
			}
			return makeint((min + (max - min)*(LAi_GetCharacterGunLevel(xi_refCharacter)*0.5))) + " ��.";
		break;
		case "breakchance":
			return CheckForSpecial(type);
		break;
		case "blooding":
			return CheckForSpecial(type);
		break;
		case "swiftstrike":
			return CheckForSpecial(type);
		break;
		case "poison":
			if (CheckAttribute(xi_refCharacter,"chr_ai.poison")) return its(sti(FloatToString(xi_refCharacter.chr_ai.poison,0)));
			else return "0";
		break;
		case "stun":
			return CheckForSpecial(type);
		break;
		case "trauma":
			return CheckForSpecial(type);
		break;
		case "poisonattack":
			return CheckForSpecial(type);
		break;
		case "recharge":
			string rechargetime = "0";
			if(IsCharacterPerkOn(xi_refCharacter, "GunProfessional"))
			{
				if(IsCharacterPerkOn(xi_refCharacter, "Buccaneer")) rechargetime = "40";
				else rechargetime = "25";
			}
			else
			{
				if(IsCharacterPerkOn(xi_refCharacter, "Gunman"))
				{
					if(IsCharacterPerkOn(xi_refCharacter, "Buccaneer")) rechargetime = "25";
					else rechargetime = "10";
				}
				else
				{
					if(IsCharacterPerkOn(xi_refCharacter, "Buccaneer")) rechargetime = "15";
				}
			}
			string weaponID = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
			if (weaponID != "")
			{
				aref weapon;
				Items_FindItem(weaponID, &weapon);
				string retime = "";
				if (rechargetime != "0") retime = FloatToString(sti(weapon.chargespeed) * (1.0 - stf(rechargetime)/100),1);
				else retime = its(weapon.chargespeed);
			}
			return rechargetime+"%/"+retime+" ���.";
		break;
		case "shipspeed":
			float fMultiplier = FindShipSpeedBonus(xi_refCharacter);
			return ""+FloatToString((fMultiplier)*100,2)+"%";
		break;
		case "shipturn":
			float fMultiplierT = FindShipTurnRateBonus(xi_refCharacter);
			return ""+FloatToString((fMultiplierT)*100.0,2)+"%";
		break;
		case "shipchargetime":
			float fMultiC = Cannon_GetRechargeTimeValue(xi_refCharacter);
			return ""+FloatToString(fMultiC,1)+" c��.";
		break;
	}
	return "";
}

string CheckForSpecial(string type)
{
	string weaponID = GetCharacterEquipByGroup(xi_refCharacter, BLADE_ITEM_TYPE);
	int critvalue = 0;
	bool addluck = false;
	int critdamage = 100;
	float coeff = 0.0;
	int blod = 0;
	if (weaponID != "")
	{
		aref weapon;
		Items_FindItem(weaponID, &weapon);
		if (CheckAttribute(weapon,"special"))
		{
			switch (type)
			{
				case "blooding":
					if (CheckAttribute(weapon,"special.valueB")) blod += sti(weapon.special.valueB);
					if (LAi_GetBladeFencingType(xi_refCharacter) == "FencingLight")
					{
						return FloatToString(2.5+blod+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20),1)+"%/"+(FloatToString(10.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20)*5,1))+" ���.";
					}
					else return FloatToString(makefloat(blod),1)+"%/"+(FloatToString(10.0+15.0,1))+" ���.";
				break;
				case "crit":
					if(IsCharacterPerkOn(xi_refCharacter, "Fencer"))
					{
						critvalue += 5;
						addluck = true;
					}
					if(IsCharacterPerkOn(xi_refCharacter, "SwordplayProfessional"))
					{
						critvalue += 10;
						addluck = true;
					}
					if(IsCharacterPerkOn(xi_refCharacter, "CriticalHit"))
					{
						critvalue += 5;
						addluck = true;
					}
					if (CheckAttribute(weapon,"special.valueCrB")) critvalue += sti(weapon.special.valueCrB);
					if (addluck) critvalue += GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L);
					critdamage = 100 + (GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L)*5);
					return its(critvalue)+"%/"+its(critdamage)+"%"
				break;
				case "swiftstrike":
					if (LAi_GetBladeFencingType(xi_refCharacter) == "Fencing")
					{
						if (CheckAttribute(weapon,"special.valueSS"))
						{
							return FloatToString(2.5+sti(weapon.special.valueSS)+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1)+"%/"+(FloatToString(5.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1))+" ���.";
						}						
						return FloatToString(2.5+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1)+"%/"+(FloatToString(5.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1))+" ���.";
					}
					else
					{
						if (CheckAttribute(weapon,"special.valueSS"))
						{
							return FloatToString(sti(weapon.special.valueSS),1)+"%/"+(FloatToString(5.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1))+" ���.";
						}						
						else return FloatToString(0.0,1)+"%/"+(FloatToString(0.0,1))+" ���.";
					}
					
				break;
				case "breakchance":
					float BB = 0.0;
					float CB = 0.0;
					if (CheckAttribute(weapon,"special.valueBB")) BB = sti(weapon.special.valueBB);
					if (CheckAttribute(weapon,"special.valueCB")) CB = sti(weapon.special.valueCB);
					if (LAi_GetBladeFencingType(xi_refCharacter) == "FencingHeavy")
					{
						coeff = makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingHeavy"))/20;
						if(HasSubStr(xi_refCharacter.equip.blade, "topor")) return FloatToString(15.0+BB+(coeff*4),1)+"%/"+FloatToString(15.0+CB+(coeff*4),1)+"%";
						return FloatToString(10.0+BB+(coeff*4),1)+"%/"+FloatToString(10.0+CB+(coeff*4),1)+"%";
					}
					else return FloatToString(makefloat(BB),1)+"%/"+FloatToString(makefloat(CB),1)+"%";
				break;
				case "stun":
					int stunchance = 0;
					if (CheckAttribute(weapon,"special.valueStS")) stunchance = sti(weapon.special.valueStS);
					return stunchance+"%/1-3 ���.";
				break;
				case "trauma":
					int trauma = 0;
					if (CheckAttribute(weapon,"special.valueT")) trauma = sti(weapon.special.valueT);
					return trauma+"%/20-60 ���.";
				break;
				case "poisonattack":
					int poisonattackV = 0;
					if (CheckAttribute(weapon,"special.valueP")) poisonattackV = sti(weapon.special.valueP);
					return poisonattackV+"%/50-110 ���.";
				break;
			}
		}
		else
		{
			switch (type)
			{
				case "blooding":
					return FloatToString(2.5+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20),1)+"%/"+(FloatToString(10.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20)*5,1))+" ���.";
				break;
				case "crit":
					if(IsCharacterPerkOn(xi_refCharacter, "Fencer"))
					{
						critvalue += 5;
						addluck = true;
					}
					if(IsCharacterPerkOn(xi_refCharacter, "SwordplayProfessional"))
					{
						critvalue += 15;
						addluck = true;
					}
					if(!IsCharacterPerkOn(xi_refCharacter, "SwordplayProfessional"))
					{
						if(IsCharacterPerkOn(xi_refCharacter, "CriticalHit"))
						{
							critvalue += 5;
							addluck = true;
						}
					}
					if (addluck) critvalue += GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L);
					critdamage = 100 + (GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L)*5);
					return its(critvalue)+"%/"+its(critdamage)+"%"
				break;
				case "swiftstrike":
					return FloatToString(2.5+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1)+"%/"+(FloatToString(5.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1))+" ���.";
				break;
				case "breakchance":
					coeff = makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingHeavy"))/20;
					if(HasSubStr(xi_refCharacter.equip.blade, "topor")) return FloatToString(15.0+(coeff*4),1)+"%/"+FloatToString(15.0+(coeff*4),1)+"%";
					return FloatToString(10.0+(coeff*4),1)+"%/"+FloatToString(10.0+(coeff*4),1)+"%";
				break;
				case "stun":
					return 0+"%";
				break;
				case "trauma":
					return 0+"%";
				break;
				case "poisonattack":
					return 0+"%";
				break;
			}
		}
	}
	else
	{
		switch (type)
		{
			case "blooding":
				return FloatToString(2.5+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20),1)+"%/"+(FloatToString(10.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingLight"))/20)*5,1))+" ���.";
			break;
			case "crit":
				if(IsCharacterPerkOn(xi_refCharacter, "Fencer"))
				{
					critvalue += 5;
					addluck = true;
				}
				if(IsCharacterPerkOn(xi_refCharacter, "SwordplayProfessional"))
				{
					critvalue += 15;
					addluck = true;
				}
				if(!IsCharacterPerkOn(xi_refCharacter, "SwordplayProfessional"))
				{
					if(IsCharacterPerkOn(xi_refCharacter, "CriticalHit"))
					{
						critvalue += 5;
						addluck = true;
					}
				}
				if (addluck) critvalue += GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L);
				critdamage = 100 + (GetCharacterSPECIALSimple(xi_refCharacter, SPECIAL_L)*5);
				return its(critvalue)+"%/"+its(critdamage)+"%"
			break;
			case "swiftstrike":
				return FloatToString(2.5+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1)+"%/"+(FloatToString(5.0+(makefloat(GetCharacterSkillSimple(xi_refCharacter,"Fencing"))/20),1))+" ���.";
			break;
			case "breakchance":
				coeff = makefloat(GetCharacterSkillSimple(xi_refCharacter,"FencingHeavy"))/20;
				return FloatToString(10.0+(coeff*4),1)+"%/"+FloatToString(10.0+(coeff*4),1)+"%";
			break;
			case "stun":
				return 0+"%";
			break;
			case "trauma":
				return 0+"%";
			break;
			case "poisonattack":
				return 0+"%";
			break;
		}
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    //sti(GameInterface.(sControl).(sRow).index);
 	NullSelectTable("TABLE_SPECIAL");
    NullSelectTable("TABLE_SKILL_1");
    NullSelectTable("TABLE_SKILL_2");
    NullSelectTable("TABLE_PERKS");
    NullSelectTable("TABLE_OTHER");
    // ���������� ����� �����
    GameInterface.TABLE_OTHER.tr9.td3.str = "";
    if (CurTable == "TABLE_OTHER" && CurRow == "tr1")
    {
    	GameInterface.TABLE_OTHER.tr9.td3.str = GetCharacterRankRateCur(xi_refCharacter) + "/" + GetCharacterRankRate(xi_refCharacter);
    }
    sti(xi_refCharacter.rank_exp)
	if (CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2")
	{
        string skillName;
        int skillVal;
        skillName = GameInterface.(CurTable).(CurRow).UserData.ID;
        skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		if (skillVal != SKILL_MAX && skillVal != 0)
		{
	       GameInterface.TABLE_OTHER.tr9.td3.str = sti(GetSkillValueExp(xi_refCharacter, skillName))+ "/" + makeint(skillVal * GetCharacterExpRate(xi_refCharacter, skillName));
		}
	}
	Table_UpdateWindow("TABLE_OTHER");
	// ��������� ����������, ���� �����
	HideSkillChanger();
    SetSkillArrows();
}

void SetSkillArrows()
{
   	bool ok;
	int  minP;
	ok = CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2";
	if (sti(xi_refCharacter.skill.freeskill) > 0 && ok && !bChangePIRATES)  //��� ������ ���� ���
	{
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 670, 234 + 22*(iSelected-1), 690, 234 + 22 + 22*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 670, 412 + 22*(iSelected-1), 690, 412 + 22 + 22*(iSelected-1), 0);
			}
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SKILL_MAX)
        {
            if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 716, 234 + 22*(iSelected-1),736, 234 + 22 + 22*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 716, 412 + 22*(iSelected-1),736, 412 + 22 + 22*(iSelected-1), 0);
			}
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	ok = sti(xi_refCharacter.skill.freeskill) > 0 || sti(xi_refCharacter.skill.FreeSPECIAL) > 0 || bChangePIRATES;  //��� ������ ����
	if (ok && CurTable == "TABLE_SPECIAL")
	{
        minP = 1;
        if (bChangePIRATES)
        {
            minP = 3;
        }
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0,670,77 + 19*(iSelected-1), 690, 77 + 20 + 19*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 715,77 + 19*(iSelected-1),735,77 + 20 + 19*(iSelected-1), 0);
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
}
void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}


void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_PERKS");
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode( 3 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;

	switch (nMode)
	{
		case 1: //
			SetNodeUsing("STR_5",false);
			SetNodeUsing("STR_51",false);
			SetNodeUsing("TABLE_CHAR_OTHERS",false);
			SetNodeUsing("TABLE_BLADES_OTHERS",false);
			SetNodeUsing("TABLE_SHIP_OTHERS",false);
			SetNodeUsing("SUBSTRATE6",false);
			SetNodeUsing("SUBSTRATE7",false);
			SetNodeUsing("SCROLL_PERKS",true);
			SetFormatedText("STR_4", "�����������");
			SetFormatedText("STR_5", "");
			SetFormatedText("STR_51", "");
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
			// ����� �����
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self_exp"))
            {
               xi_refCharacter.perks.FreePoints_self_exp = 0;
            }
            GameInterface.TABLE_OTHER.tr9.td3.str = sti(xi_refCharacter.perks.FreePoints_self_exp)+ "/" + GetFreePoints_SelfRate(xi_refCharacter);
		break;
		case 2:
			SetNodeUsing("STR_5",false);
			SetNodeUsing("STR_51",false);
			SetNodeUsing("TABLE_CHAR_OTHERS",false);
			SetNodeUsing("TABLE_BLADES_OTHERS",false);
			SetNodeUsing("TABLE_SHIP_OTHERS",false);
			SetNodeUsing("SUBSTRATE6",false);
			SetNodeUsing("SUBSTRATE7",false);
			SetNodeUsing("SCROLL_PERKS",true);
			SetFormatedText("STR_4", "�����������");
			SetFormatedText("STR_5", "");
			SetFormatedText("STR_51", "");
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
			// ����� �����
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship_exp"))
            {
               xi_refCharacter.perks.FreePoints_ship_exp = 0;
            }
            GameInterface.TABLE_OTHER.tr9.td3.str = sti(xi_refCharacter.perks.FreePoints_ship_exp)+ "/" + GetFreePoints_ShipRate(xi_refCharacter);
		break;
		case 3:
			SetNodeUsing("STR_5",true);
			SetNodeUsing("STR_51",true);
			SetNodeUsing("TABLE_CHAR_OTHERS",true);
			SetNodeUsing("TABLE_BLADES_OTHERS",true);
			SetNodeUsing("TABLE_SHIP_OTHERS",true);
			SetNodeUsing("SUBSTRATE6",true);
			SetNodeUsing("SUBSTRATE7",true);
			SetNodeUsing("SCROLL_PERKS",false);
			SetFormatedText("STR_4", "��������������");
			SetFormatedText("STR_5", "���. �������� ��");
			SetFormatedText("STR_51", "�������������� ��");
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
            GameInterface.TABLE_OTHER.tr9.td3.str = "";
			UpdateStatsValues();
		break;
	}
    Table_UpdateWindow("TABLE_OTHER"); // ����� �����
    
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);

	FillControlsList(nMode);
	HideSkillChanger();
}

void UpdateStatsValues()
{
	//-----------------> ���������������� ���������
	GameInterface.TABLE_CHAR_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_CHAR_OTHERS.tr1.UserData.ID = "HealthChar";
	GameInterface.TABLE_CHAR_OTHERS.tr1.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_CHAR_OTHERS.tr1.td1.icon.image = "HealthChar";
	GameInterface.TABLE_CHAR_OTHERS.tr1.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr1.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr1.td2.str = "�����. �����";
	GameInterface.TABLE_CHAR_OTHERS.tr1.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr1.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr1.td3.str = ShowStatValue("regenhp")+" � ���.";
	GameInterface.TABLE_CHAR_OTHERS.tr1.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr1.td3.align = "right";
	
	GameInterface.TABLE_CHAR_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_CHAR_OTHERS.tr2.UserData.ID = "EnergyChar";
	GameInterface.TABLE_CHAR_OTHERS.tr2.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_CHAR_OTHERS.tr2.td1.icon.image = "EnergyChar";
	GameInterface.TABLE_CHAR_OTHERS.tr2.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr2.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr2.td2.str = "�����. �������";
	GameInterface.TABLE_CHAR_OTHERS.tr2.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr2.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr2.td3.str = ShowStatValue("energychar")+" � ���.";
	GameInterface.TABLE_CHAR_OTHERS.tr2.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr2.td3.align = "right";
	
	GameInterface.TABLE_CHAR_OTHERS.tr3.UserData.ID = "PoisonChar";
	GameInterface.TABLE_CHAR_OTHERS.tr3.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_CHAR_OTHERS.tr3.td1.icon.image = "PoisonChar";
	GameInterface.TABLE_CHAR_OTHERS.tr3.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr3.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr3.td2.str = "����������";
	GameInterface.TABLE_CHAR_OTHERS.tr3.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr3.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr3.td3.str = ShowStatValue("poison")+" ���.";
	GameInterface.TABLE_CHAR_OTHERS.tr3.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr3.td3.align = "right";
	
	GameInterface.TABLE_CHAR_OTHERS.tr4.UserData.ID = "ReloadGun";
	GameInterface.TABLE_CHAR_OTHERS.tr4.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_CHAR_OTHERS.tr4.td1.icon.image = "ReloadGun";
	GameInterface.TABLE_CHAR_OTHERS.tr4.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr4.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr4.td2.str = "����� �����������";
	GameInterface.TABLE_CHAR_OTHERS.tr4.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr4.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr4.td3.str = "-"+ShowStatValue("recharge");
	GameInterface.TABLE_CHAR_OTHERS.tr4.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr4.td3.align = "right";
	
	GameInterface.TABLE_CHAR_OTHERS.tr5.UserData.ID = "AccuracyGun";
	GameInterface.TABLE_CHAR_OTHERS.tr5.td1.icon.group = "ICONS_SPEC_NA";
    GameInterface.TABLE_CHAR_OTHERS.tr5.td1.icon.image = "AccuracyGun";
	GameInterface.TABLE_CHAR_OTHERS.tr5.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr5.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr5.td2.str = "�������� ��������";
	GameInterface.TABLE_CHAR_OTHERS.tr5.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr5.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr5.td3.str = ShowStatValue("accuracy");
	GameInterface.TABLE_CHAR_OTHERS.tr5.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr5.td3.align = "right";
	
	GameInterface.TABLE_CHAR_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_CHAR_OTHERS.tr6.UserData.ID = "GunDamage";
	GameInterface.TABLE_CHAR_OTHERS.tr6.td1.icon.group = "ICONS_SPEC_NA";
    GameInterface.TABLE_CHAR_OTHERS.tr6.td1.icon.image = "GunDamage";
	GameInterface.TABLE_CHAR_OTHERS.tr6.td1.icon.width = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr6.td1.icon.height = 20;
	GameInterface.TABLE_CHAR_OTHERS.tr6.td2.str = "�������� ��������";
	GameInterface.TABLE_CHAR_OTHERS.tr6.td2.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr6.td2.align = "left";
	GameInterface.TABLE_CHAR_OTHERS.tr6.td3.str = ShowStatValue("gundamage");
	GameInterface.TABLE_CHAR_OTHERS.tr6.td3.scale = 0.8;
	GameInterface.TABLE_CHAR_OTHERS.tr6.td3.align = "right";
	//<----------------- ���������������� ���������
	
	//-----------------> �������������� �������� ��
	GameInterface.TABLE_BLADES_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_BLADES_OTHERS.tr1.UserData.ID = "Blood";
	GameInterface.TABLE_BLADES_OTHERS.tr1.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr1.td1.icon.image = "Blood";
	GameInterface.TABLE_BLADES_OTHERS.tr1.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr1.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr1.td2.str = "������������";
	GameInterface.TABLE_BLADES_OTHERS.tr1.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr1.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr1.td3.str = ShowStatValue("blooding");
	GameInterface.TABLE_BLADES_OTHERS.tr1.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr1.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr2.UserData.ID = "StanS";
	GameInterface.TABLE_BLADES_OTHERS.tr2.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr2.td1.icon.image = "StanS";
	GameInterface.TABLE_BLADES_OTHERS.tr2.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr2.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr2.td2.str = "������ ����";
	GameInterface.TABLE_BLADES_OTHERS.tr2.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr2.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr2.td3.str = ShowStatValue("swiftstrike");
	GameInterface.TABLE_BLADES_OTHERS.tr2.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr2.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr3.UserData.ID = "BlockKirass";
	GameInterface.TABLE_BLADES_OTHERS.tr3.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr3.td1.icon.image = "BlockKirass";
	GameInterface.TABLE_BLADES_OTHERS.tr3.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr3.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr3.td2.str = "�������� �/�";
	GameInterface.TABLE_BLADES_OTHERS.tr3.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr3.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr3.td3.str = ShowStatValue("breakchance");
	GameInterface.TABLE_BLADES_OTHERS.tr3.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr3.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr4.UserData.ID = "CriticalChance";
	GameInterface.TABLE_BLADES_OTHERS.tr4.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr4.td1.icon.image = "CriticalChance";
	GameInterface.TABLE_BLADES_OTHERS.tr4.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr4.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr4.td2.str = "����/���� �����";
	GameInterface.TABLE_BLADES_OTHERS.tr4.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr4.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr4.td3.str = ShowStatValue("crit");
	GameInterface.TABLE_BLADES_OTHERS.tr4.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr4.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr5.UserData.ID = "StanH";
	GameInterface.TABLE_BLADES_OTHERS.tr5.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr5.td1.icon.image = "StanH";
	GameInterface.TABLE_BLADES_OTHERS.tr5.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr5.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr5.td2.str = "���������";
	GameInterface.TABLE_BLADES_OTHERS.tr5.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr5.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr5.td3.str = ShowStatValue("stun");
	GameInterface.TABLE_BLADES_OTHERS.tr5.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr5.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr6.UserData.ID = "Travma";
	GameInterface.TABLE_BLADES_OTHERS.tr6.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr6.td1.icon.image = "Travma";
	GameInterface.TABLE_BLADES_OTHERS.tr6.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr6.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr6.td2.str = "�������������";
	GameInterface.TABLE_BLADES_OTHERS.tr6.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr6.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr6.td3.str = ShowStatValue("trauma");
	GameInterface.TABLE_BLADES_OTHERS.tr6.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr6.td3.align = "right";
	
	GameInterface.TABLE_BLADES_OTHERS.tr7.UserData.ID = "Poison";
	GameInterface.TABLE_BLADES_OTHERS.tr7.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_BLADES_OTHERS.tr7.td1.icon.image = "Poison";
	GameInterface.TABLE_BLADES_OTHERS.tr7.td1.icon.width = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr7.td1.icon.height = 20;
	GameInterface.TABLE_BLADES_OTHERS.tr7.td2.str = "�������� ������";
	GameInterface.TABLE_BLADES_OTHERS.tr7.td2.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr7.td2.align = "left";
	GameInterface.TABLE_BLADES_OTHERS.tr7.td3.str = ShowStatValue("poisonattack");
	GameInterface.TABLE_BLADES_OTHERS.tr7.td3.scale = 0.8;
	GameInterface.TABLE_BLADES_OTHERS.tr7.td3.align = "right";
	//<----------------- �������������� �������� ��
	
	//-----------------> ����������� ��������������
	GameInterface.TABLE_SHIP_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_SHIP_OTHERS.tr1.UserData.ID = "SpeedBonus";
	GameInterface.TABLE_SHIP_OTHERS.tr1.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_SHIP_OTHERS.tr1.td1.icon.image = "SpeedBonus";
	GameInterface.TABLE_SHIP_OTHERS.tr1.td1.icon.width = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr1.td1.icon.height = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr1.td2.str = "��������";
	GameInterface.TABLE_SHIP_OTHERS.tr1.td2.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr1.td2.align = "left";
	GameInterface.TABLE_SHIP_OTHERS.tr1.td3.str = ShowStatValue("shipspeed");
	GameInterface.TABLE_SHIP_OTHERS.tr1.td3.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr1.td3.align = "right";
	
	GameInterface.TABLE_SHIP_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_SHIP_OTHERS.tr2.UserData.ID = "ManevrBonus";
	GameInterface.TABLE_SHIP_OTHERS.tr2.td1.icon.group = "ICONS_STATS_CHAR";
    GameInterface.TABLE_SHIP_OTHERS.tr2.td1.icon.image = "ManevrBonus";
	GameInterface.TABLE_SHIP_OTHERS.tr2.td1.icon.width = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr2.td1.icon.height = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr2.td2.str = "�������������";
	GameInterface.TABLE_SHIP_OTHERS.tr2.td2.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr2.td2.align = "left";
	GameInterface.TABLE_SHIP_OTHERS.tr2.td3.str = ShowStatValue("shipturn");
	GameInterface.TABLE_SHIP_OTHERS.tr2.td3.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr2.td3.align = "right";
	
	GameInterface.TABLE_SHIP_OTHERS.hr.td1.str = "";
	GameInterface.TABLE_SHIP_OTHERS.tr3.UserData.ID = "ChargeTime";
	GameInterface.TABLE_SHIP_OTHERS.tr3.td1.icon.group = "SHIP_STATE_ICONS";
    GameInterface.TABLE_SHIP_OTHERS.tr3.td1.icon.image = "Cannons";
	GameInterface.TABLE_SHIP_OTHERS.tr3.td1.icon.width = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr3.td1.icon.height = 20;
	GameInterface.TABLE_SHIP_OTHERS.tr3.td2.str = "����� �������";
	GameInterface.TABLE_SHIP_OTHERS.tr3.td2.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr3.td2.align = "left";
	GameInterface.TABLE_SHIP_OTHERS.tr3.td3.str = ShowStatValue("shipchargetime");
	GameInterface.TABLE_SHIP_OTHERS.tr3.td3.scale = 0.8;
	GameInterface.TABLE_SHIP_OTHERS.tr3.td3.align = "right";
	//<----------------- ����������� ��������������
	
	Table_UpdateWindow("TABLE_CHAR_OTHERS");
	Table_UpdateWindow("TABLE_BLADES_OTHERS");
	Table_UpdateWindow("TABLE_SHIP_OTHERS");
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillPerksTable("Self", true); break;  // ������ �����
	    case 2: FillPerksTable("Ship", true); break;  // ����������� �����
	}
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
        }
        else
        {
            Table_Clear("TABLE_SMALLSKILL", false, true, true);
            Table_Clear("TABLE_SMALLOTHER", false, true, true);
            SetFormatedText("OFFICER_NAME", "");
            SetSelectable("ACCEPT_ADD_OFFICER", false);
        }
	}
	else
    {
        Table_Clear("TABLE_SMALLSKILL", false, true, true);
        Table_Clear("TABLE_SMALLOTHER", false, true, true);
        SetFormatedText("OFFICER_NAME", "");
        SetSelectable("ACCEPT_ADD_OFFICER", false);
    }
}

void HideSkillChanger()
{
    SetNodeUsing("B_SKILLUP",  false);
	SetNodeUsing("B_SKILLDown",  false);
}

void IncreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
		if (sti(xi_refCharacter.skill.freeskill) < _add) _add = sti(xi_refCharacter.skill.freeskill);
		if ((GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) + _add) > SKILL_MAX)
		{
		    _add = SKILL_MAX - GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName);
		}
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) - _add;
	    }
	    else return;
    }
    else
    {
        if (sti(xi_refCharacter.skill.FreeSPECIAL) < _add) _add = sti(xi_refCharacter.skill.FreeSPECIAL);
		if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
		{
		    _add = SPECIAL_MAX - GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName);
		}
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) - _add;
	    }
	    else return;
	    
	    if (bChangePIRATES)
	    { //��� ������ ���� �������� ������
	    	// ��������� ����� ������
		    InitStartParam(xi_refCharacter);
		    SetEnergyToCharacter(xi_refCharacter);
	    }
    }
	SetVariable();
	SetSkillArrows();
}

void DecreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) - 1;
	    }
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) + _add;
	    }
	    else return;
    }
    else
    {
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 1;
	    }
	    if (bChangePIRATES && (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - _add) < 3)
        {
            _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 3;
		}
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) + _add;
	    }
	    else return;
	    
	    if (bChangePIRATES)
	    { //��� ������ ���� �������� ������
	    	// ��������� ����� ������
		    InitStartParam(xi_refCharacter);
		    SetEnergyToCharacter(xi_refCharacter);
	    }
    }
    SetVariable();
    SetSkillArrows();
}
///////////////////////////////////////  PERKS /////////////////////////
void FillPerksTable(string _type, bool _refresh)
{
	int perksQ, i, n;
	string perkName, row, icoGroup;
	aref arPerksRoot;

    Table_Clear("TABLE_PERKS", false, true, false);
	GameInterface.TABLE_PERKS.hr.td1.str = "";
	if (_refresh)
	{
	    GameInterface.TABLE_PERKS.select = 0;
	    GameInterface.TABLE_PERKS.top = 0;
	}
	SetFormatedText("STR_4", XI_ConvertString("Abilities"));

	makearef(arPerksRoot,ChrPerksList.list); // ����� ������
	perksQ = GetAttributesNum(arPerksRoot);
	n = 1;
	for(i=0; i<perksQ; i++)
	{
	    row = "tr" + n;

        perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if (xi_refCharacter.id == pchar.id && CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;
        if (xi_refCharacter.id != pchar.id && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue;
        if (CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;

        if (!CheckAttribute(arPerksRoot, perkName + ".BaseType")) // to_DO
        {
            arPerksRoot.(perkName).BaseType = "self";
        }
		if (CheckAttribute(arPerksRoot, perkName + ".BaseType") && arPerksRoot.(perkName).BaseType == _type)
		{
			GameInterface.TABLE_PERKS.(row).UserData.ID   = perkName;
			GameInterface.TABLE_PERKS.(row).UserData.Type = _type;
            if (CheckCharacterPerk(xi_refCharacter, perkName))
            {
                icoGroup = "PERK_ENABLE";
                GameInterface.TABLE_PERKS.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERK_DISABLE";
                GameInterface.TABLE_PERKS.(row).td2.color = argb(255,196,196,196);
            }
			GameInterface.TABLE_PERKS.(row).td1.icon.group  = icoGroup;
			GameInterface.TABLE_PERKS.(row).td1.icon.image  = perkName;
			GameInterface.TABLE_PERKS.(row).td1.icon.width  = 20;
		    GameInterface.TABLE_PERKS.(row).td1.icon.height = 20;
		    GameInterface.TABLE_PERKS.(row).td1.icon.offset = "-1, 0";
			GameInterface.TABLE_PERKS.(row).td2.str = GetConvertStr(perkName, "AbilityDescribe.txt");
			GameInterface.TABLE_PERKS.(row).td2.scale = 0.8;
			n++;
		}
	}

	// ����������
	Table_UpdateWindow("TABLE_PERKS");
}

void ChoosePerk()
{
	bool ok = true;
	bool showCondition = true;
	string  perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
	string  descr    = GetConvertStr("perk" + perkName, "AbilityDescribe.txt");
	aref rootItems;
	int    i;
	string row, perkCond, icoGroup;

	SetNewGroupPicture("PERK_PICTURE", "PERK_ENABLE", perkName);
    SetFormatedText("PERK_WINDOW_CAPTION", GetConvertStr(perkName, "AbilityDescribe.txt"));

    if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
    {
        descr += "\n\n ����������� ����� �������� � � ��� ������, ���� �������� ������ " + XI_ConvertString(ChrPerksList.list.(perkName).OfficerType)+ ", � �������� ��� ����.";
    }
    SetFormatedText("PERK_WINDOW_TEXT", descr);
    SetVAligmentFormatedText("PERK_WINDOW_TEXT");

    if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
    {
        SetFormatedText("PERK_TEXT_FREE", XI_ConvertString("Personal abilities") + ": " +xi_refCharacter.perks.FreePoints_self);
		if (sti(xi_refCharacter.perks.FreePoints_self) <= 0) ok = false;
	}
	else
	{
		SetFormatedText("PERK_TEXT_FREE", XI_ConvertString("Ship abilities") + ": " + xi_refCharacter.perks.FreePoints_ship);
		if (sti(xi_refCharacter.perks.FreePoints_ship) <= 0) ok = false;
    }
	// �������� �� ���������� ����� -->
	if (CheckAttribute(&ChrPerksList, "list." + perkName + ".condition"))
	{
        makearef(rootItems, ChrPerksList.list.(perkName).condition);
		Table_Clear("PERK_TABLE_NEED", false, true, false);
		GameInterface.PERK_TABLE_NEED.select = 0;
		GameInterface.PERK_TABLE_NEED.hr.td1.str = "";
		GameInterface.PERK_TABLE_NEED.top = 0;
		for (i=0; i<GetAttributesNum(rootItems); i++)
    	{
    	    row = "tr" + (i+1);
    	    perkCond = GetAttributeName(GetAttributeN(rootItems, i));
    	    if (CheckCharacterPerk(xi_refCharacter, perkCond))
            {
                icoGroup = "PERK_ENABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERK_DISABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,196,196,196);
                ok = false;
            }
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.group  = icoGroup;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.image  = perkCond;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.width  = 32;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.height = 32;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.offset = "-2, -1";

			GameInterface.PERK_TABLE_NEED.(row).td2.str = GetConvertStr(perkCond, "AbilityDescribe.txt");
			GameInterface.PERK_TABLE_NEED.(row).td2.scale = 0.8;
		    GameInterface.PERK_TABLE_NEED.(row).td2.textoffset = "10, -1";
    	}
		Table_UpdateWindow("PERK_TABLE_NEED");
	}
	else
	{
	    showCondition = false;
	}
	// �������� �� ���������� ����� <--
	XI_WindowShow("PERK_WINDOW", true);
	XI_WindowDisable("PERK_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	if (CheckCharacterPerk(xi_refCharacter, perkName))
 	{
 	    SetNodeUsing("PERK_ON", true);
 	    ok = false; // ��� ����
 	}
 	else
 	{
 	    SetNodeUsing("PERK_ON", false);
 	    SetNewGroupPicture("PERK_PICTURE", "PERK_DISABLE", perkName);
 	}

    SetSelectable("PERK_ACCEPT", ok);
    SetNodeUsing("PERK_TABLE_NEED", showCondition);
	SetCurrentNode("PERK_CANCEL");
}

void ExitPerkMenu()
{
	XI_WindowShow("PERK_WINDOW", false);
	XI_WindowDisable("PERK_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_PERKS");
}

void AcceptPerk()
{
    string  perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
    {
		xi_refCharacter.perks.FreePoints_self = sti(xi_refCharacter.perks.FreePoints_self) - 1;
	}
	else
	{
		xi_refCharacter.perks.FreePoints_ship = sti(xi_refCharacter.perks.FreePoints_ship) - 1;
    }
    SetCharacterPerk(xi_refCharacter, perkName);
    // ���������� ��� -->
    SetFormatedText("TABSTR_1", XI_ConvertString("Personal_abilities") + " " +xi_refCharacter.perks.FreePoints_self);
    SetFormatedText("TABSTR_2", XI_ConvertString("Ship_abilities") + " " + xi_refCharacter.perks.FreePoints_ship);
    FillPerksTable(GameInterface.(CurTable).(CurRow).UserData.Type, false);
    // ���������� ��� <--
	ExitPerkMenu();
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
}

void ShowMsgMenu()
{
	SetFormatedText("MSG_WINDOW_CAPTION", "������� ������ �����");
	SetFormatedText("MSG_WINDOW_TEXT", "��� ��������� ���������� ����� ������� �������������� � ��������� ���������������� ����. ������ ������������� ������������� �� ��������� PIRATES. �������� ����� ��������� ��� Esc, ����� ������������� ����� ���������.");
	
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_OK");
}
