//  интерфейс Выбора герба на парус (boal 08.02.08)
ref    shref;
int    price;
bool sails = false;

void InitInterface_R(string iniName, ref _shipyarder)
{
    StartAboveForm(true);
    // лочим квест и карту
    bQuestCheckProcessFreeze = true;
    int st = GetCharacterShipType(pchar);
    shref = GetRealShip(st);
    
    price = GetSailsTuningPrice(Pchar, _shipyarder, SAILSGERALD_PRICE_RATE);
    
    SetEventHandler("GetInterfaceTexture", "ScrollGetTexture", 0);
	if (_shipyarder.sailsgerald == "sails") sails = true;
	if (sails) 
	{
		if (bNewSails && _shipyarder.name == "Мастер") EnumerateIcons("resource\textures\ships", "parus_sail_*", "SCROLL_GERALD", 0);
		else EnumerateIcons("resource\textures\ships\PlayerSails", "*.tga.tx", "SCROLL_GERALD", 0);
	}
    else EnumerateIcons("resource\textures\ships\gerald", "*.tga.tx", "SCROLL_GERALD", 0);
    
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
    
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage", 0);
	
	if(!CheckAttribute(&GameInterface,"SCROLL_GERALD.current"))
	{
		GameInterface.SCROLL_GERALD.current = 0;
	}
	CheckChangeSailStatus();
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
    DelEventHandler("GetInterfaceTexture", "ScrollGetTexture");
    DelEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage");
    
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100);//заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                SetNewSailsGerald();
    		}
    	break;
    	
    	case "B_REMOVE":
    		if(comName=="activate" || comName=="click")
    		{
                ClearSailsGerald();
    		}
    	break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

int ScrollGetTexture()
{
	string sName = GetEventData();
	int iPicIndex = GetEventData();
	string sScrollID = GetEventData();
	int iTexture = GetTexture(sName);
	//Trace("ScrollGetTexture: " + iTexture + ", " + sName);

	return iTexture;
}

void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();
	if (sNod == "SCROLL_GERALD")
	{
		GameInterface.SCROLL_GERALD.current = nIdx;
		CheckChangeSailStatus();
	}
}

void CheckChangeSailStatus()
{
	if (sails) SetFormatedText("INFO_CAPTION", "Выбрать материал парусов");
	bool bNewValue = true;
	
	if (CheckAttribute(shref, "ShipSails.Gerald_Name"))
	{
		bNewValue = false;

		int nEmblem = sti(GameInterface.SCROLL_GERALD.current);

		string sattr = "pic"+(nEmblem+1);
		if (!sails)
		{
			if (GameInterface.SCROLL_GERALD.(sattr).FileName.Name != (shref.ShipSails.Gerald_Name + ".tga"))
			{
				bNewValue = true;
			}
		}
		else
		{
			if (nEmblem+1 != shref.ship.upgrades.sails)
			{
				bNewValue = true;
			}
		}
		
	}
	SetSelectable("B_OK", bNewValue);
	SetSelectable("B_REMOVE", !bNewValue);
	if (price > sti(pchar.money))
	{
		SetSelectable("B_OK", false);
		SetSelectable("B_REMOVE", false);
	}
}

void SetNewSailsGerald()
{
	int nEmblem = sti(GameInterface.SCROLL_GERALD.current);

	string sattr = "pic"+(nEmblem+1);
	string geraldname = GameInterface.SCROLL_GERALD.(sattr).FileName.Name;
	switch (geraldname)
	{
		case "eng_1.tga":shref.ShipSails.Gerald_Name = "eng_1";break;
		case "eng_2.tga":shref.ShipSails.Gerald_Name = "eng_2";break;
		case "eng_3.tga":shref.ShipSails.Gerald_Name = "eng_3";break;
		case "eng_4.tga":shref.ShipSails.Gerald_Name = "eng_4";break;
		case "eng_5.tga":shref.ShipSails.Gerald_Name = "eng_5";break;
		case "fra_1.tga":shref.ShipSails.Gerald_Name = "fra_1";break;
		case "fra_2.tga":shref.ShipSails.Gerald_Name = "fra_2";break;
		case "fra_3.tga":shref.ShipSails.Gerald_Name = "fra_3";break;
		case "fra_4.tga":shref.ShipSails.Gerald_Name = "fra_4";break;
		case "fra_5.tga":shref.ShipSails.Gerald_Name = "fra_5";break;
		case "fra_6.tga":shref.ShipSails.Gerald_Name = "fra_6";break;
		case "Ing_1.tga":shref.ShipSails.Gerald_Name = "Ing_1";break;
		case "Ing_2.tga":shref.ShipSails.Gerald_Name = "Ing_2";break;
		case "Ing_3.tga":shref.ShipSails.Gerald_Name = "Ing_3";break;
		case "Ing_4.tga":shref.ShipSails.Gerald_Name = "Ing_4";break;
		case "Ing_5.tga":shref.ShipSails.Gerald_Name = "Ing_5";break;
		case "Ing_6.tga":shref.ShipSails.Gerald_Name = "Ing_6";break;
		case "Ing_7.tga":shref.ShipSails.Gerald_Name = "Ing_7";break;
		case "Ing_8.tga":shref.ShipSails.Gerald_Name = "Ing_8";break;
		case "Ing_9.tga":shref.ShipSails.Gerald_Name = "Ing_9";break;
		case "Ing_10.tga":shref.ShipSails.Gerald_Name = "Ing_10";break;
		case "Ing_11.tga":shref.ShipSails.Gerald_Name = "Ing_11";break;
		case "Ing_12.tga":shref.ShipSails.Gerald_Name = "Ing_12";break;
		case "Ing_13.tga":shref.ShipSails.Gerald_Name = "Ing_13";break;
		case "Ing_14.tga":shref.ShipSails.Gerald_Name = "Ing_14";break;
		case "Ing_15.tga":shref.ShipSails.Gerald_Name = "Ing_15";break;
		case "Ing_16.tga":shref.ShipSails.Gerald_Name = "Ing_16";break;
		case "Ing_17.tga":shref.ShipSails.Gerald_Name = "Ing_17";break;
		case "Ing_18.tga":shref.ShipSails.Gerald_Name = "Ing_18";break;
		case "Ing_19.tga":shref.ShipSails.Gerald_Name = "Ing_19";break;
		case "Ing_20.tga":shref.ShipSails.Gerald_Name = "Ing_20";break;
		case "Ing_21.tga":shref.ShipSails.Gerald_Name = "Ing_21";break;
		case "Ing_22.tga":shref.ShipSails.Gerald_Name = "Ing_22";break;
		case "Ing_23.tga":shref.ShipSails.Gerald_Name = "Ing_23";break;
		case "Ing_24.tga":shref.ShipSails.Gerald_Name = "Ing_24";break;
		case "Ing_25.tga":shref.ShipSails.Gerald_Name = "Ing_25";break;
		case "Ing_26.tga":shref.ShipSails.Gerald_Name = "Ing_26";break;
		case "Ing_27.tga":shref.ShipSails.Gerald_Name = "Ing_27";break;
		case "Ing_28.tga":shref.ShipSails.Gerald_Name = "Ing_28";break;
		case "Ing_29.tga":shref.ShipSails.Gerald_Name = "Ing_29";break;
		case "Ing_30.tga":shref.ShipSails.Gerald_Name = "Ing_30";break;
		case "Ing_31.tga":shref.ShipSails.Gerald_Name = "Ing_31";break;
		case "Ing_32.tga":shref.ShipSails.Gerald_Name = "Ing_32";break;
		case "Ing_33.tga":shref.ShipSails.Gerald_Name = "Ing_33";break;
		case "Ing_34.tga":shref.ShipSails.Gerald_Name = "Ing_34";break;
		case "Ing_35.tga":shref.ShipSails.Gerald_Name = "Ing_35";break;
		case "Ing_36.tga":shref.ShipSails.Gerald_Name = "Ing_36";break;
		case "Ing_37.tga":shref.ShipSails.Gerald_Name = "Ing_37";break;
		case "Ing_38.tga":shref.ShipSails.Gerald_Name = "Ing_38";break;
		case "Ing_39.tga":shref.ShipSails.Gerald_Name = "Ing_39";break;
		case "Ing_40.tga":shref.ShipSails.Gerald_Name = "Ing_40";break;
		case "Ing_41.tga":shref.ShipSails.Gerald_Name = "Ing_41";break;
		case "Ing_42.tga":shref.ShipSails.Gerald_Name = "Ing_42";break;
		case "Ing_43.tga":shref.ShipSails.Gerald_Name = "Ing_43";break;
		case "Ing_44.tga":shref.ShipSails.Gerald_Name = "Ing_44";break;
		case "Ing_45.tga":shref.ShipSails.Gerald_Name = "Ing_45";break;
		case "Ing_46.tga":shref.ShipSails.Gerald_Name = "Ing_46";break;
		case "Ing_47.tga":shref.ShipSails.Gerald_Name = "Ing_47";break;
		case "Ing_48.tga":shref.ShipSails.Gerald_Name = "Ing_48";break;
		case "Ing_49.tga":shref.ShipSails.Gerald_Name = "Ing_49";break;
		case "Ing_50.tga":shref.ShipSails.Gerald_Name = "Ing_50";break;
		case "Ing_51.tga":shref.ShipSails.Gerald_Name = "Ing_51";break;
		case "Ing_52.tga":shref.ShipSails.Gerald_Name = "Ing_52";break;
		case "Ing_53.tga":shref.ShipSails.Gerald_Name = "Ing_53";break;
		case "Ing_54.tga":shref.ShipSails.Gerald_Name = "Ing_54";break;
		case "Ing_55.tga":shref.ShipSails.Gerald_Name = "Ing_55";break;
		case "Ing_56.tga":shref.ShipSails.Gerald_Name = "Ing_56";break;
		case "Ing_57.tga":shref.ShipSails.Gerald_Name = "Ing_57";break;
		case "Ing_58.tga":shref.ShipSails.Gerald_Name = "Ing_58";break;
		case "Ing_59.tga":shref.ShipSails.Gerald_Name = "Ing_59";break;
		case "Ing_60.tga":shref.ShipSails.Gerald_Name = "Ing_60";break;
		case "Ing_61.tga":shref.ShipSails.Gerald_Name = "Ing_61";break;
		case "Ing_62.tga":shref.ShipSails.Gerald_Name = "Ing_62";break;
		case "Ing_63.tga":shref.ShipSails.Gerald_Name = "Ing_63";break;
		case "Ing_64.tga":shref.ShipSails.Gerald_Name = "Ing_64";break;
		case "Ing_65.tga":shref.ShipSails.Gerald_Name = "Ing_65";break;
		case "Ing_66.tga":shref.ShipSails.Gerald_Name = "Ing_66";break;
		case "Ing_67.tga":shref.ShipSails.Gerald_Name = "Ing_67";break;
		case "Ing_68.tga":shref.ShipSails.Gerald_Name = "Ing_68";break;
		case "Ing_69.tga":shref.ShipSails.Gerald_Name = "Ing_69";break;
		case "Ing_70.tga":shref.ShipSails.Gerald_Name = "Ing_70";break;
		case "Ing_71.tga":shref.ShipSails.Gerald_Name = "Ing_71";break;
		case "Ing_72.tga":shref.ShipSails.Gerald_Name = "Ing_72";break;
		case "hol_1.tga":shref.ShipSails.Gerald_Name = "hol_1";break;
		case "hol_2.tga":shref.ShipSails.Gerald_Name = "hol_2";break;
		case "hol_3.tga":shref.ShipSails.Gerald_Name = "hol_3";break;
		case "hol_4.tga":shref.ShipSails.Gerald_Name = "hol_4";break;
		case "pir_1.tga":shref.ShipSails.Gerald_Name = "pir_1";break;
		case "pir_2.tga":shref.ShipSails.Gerald_Name = "pir_2";break;
		case "pir_3.tga":shref.ShipSails.Gerald_Name = "pir_3";break;
		case "pir_4.tga":shref.ShipSails.Gerald_Name = "pir_4";break;
		case "pir_5.tga":shref.ShipSails.Gerald_Name = "pir_5";break;
		case "pir_6.tga":shref.ShipSails.Gerald_Name = "pir_6";break;
		case "pir1.tga":shref.ShipSails.Gerald_Name = "pir1";break;
		case "pir2.tga":shref.ShipSails.Gerald_Name = "pir2";break;
		case "pir3.tga":shref.ShipSails.Gerald_Name = "pir3";break;
		case "pir4.tga":shref.ShipSails.Gerald_Name = "pir4";break;
		case "pir5.tga":shref.ShipSails.Gerald_Name = "pir5";break;
		case "pir6.tga":shref.ShipSails.Gerald_Name = "pir6";break;
		case "spa_1.tga":shref.ShipSails.Gerald_Name = "spa_1";break;
		case "spa_2.tga":shref.ShipSails.Gerald_Name = "spa_2";break;
		case "spa_3.tga":shref.ShipSails.Gerald_Name = "spa_3";break;
		case "spa_4.tga":shref.ShipSails.Gerald_Name = "spa_4";break;
		case "spa_5.tga":shref.ShipSails.Gerald_Name = "spa_5";break;
		case "parus_common.tga":shref.ship.upgrades.sails = 1;break;
		case "parus_pat.tga":shref.ship.upgrades.sails = 2;break;
		case "parus_silk.tga":shref.ship.upgrades.sails = 3;break;
		case "parus_silkblack.tga":shref.ship.upgrades.sails = 4;break;
		case "parus_usual_1.tga":shref.ship.upgrades.sails = 5;break;
		case "parus_usual_2.tga":shref.ship.upgrades.sails = 6;break;
		case "parus_usual_3.tga":shref.ship.upgrades.sails = 7;break;
		case "parus_usual_4.tga":shref.ship.upgrades.sails = 8;break;
		case "parus_usual_5.tga":shref.ship.upgrades.sails = 9;break;
		case "parus_usual_6.tga":shref.ship.upgrades.sails = 10;break;
		case "parus_usual_7.tga":shref.ship.upgrades.sails = 11;break;
		case "parus_usual_8.tga":shref.ship.upgrades.sails = 12;break;
		case "parus_usual_9.tga":shref.ship.upgrades.sails = 13;break;
		case "parus_usual_10.tga":shref.ship.upgrades.sails = 14;break;
		case "parus_usual_11.tga":shref.ship.upgrades.sails = 15;break;
		case "parus_usual_12.tga":shref.ship.upgrades.sails = 16;break;
		case "parus_usual_13.tga":shref.ship.upgrades.sails = 17;break;
		case "parus_usual_14.tga":shref.ship.upgrades.sails = 18;break;
		case "parus_usual_15.tga":shref.ship.upgrades.sails = 19;break;
		case "parus_usual_16.tga":shref.ship.upgrades.sails = 20;break;
		case "parus_usual_17.tga":shref.ship.upgrades.sails = 21;break;
		case "parus_usual_18.tga":shref.ship.upgrades.sails = 22;break;
		case "parus_usual_19.tga":shref.ship.upgrades.sails = 23;break;
		case "parus_usual_20.tga":shref.ship.upgrades.sails = 24;break;
		case "parus_usual_21.tga":shref.ship.upgrades.sails = 25;break;
		case "parus_usual_22.tga":shref.ship.upgrades.sails = 26;break;
		case "parus_usual_23.tga":shref.ship.upgrades.sails = 27;break;
		case "parus_usual_24.tga":shref.ship.upgrades.sails = 28;break;
		case "parus_usual_25.tga":shref.ship.upgrades.sails = 29;break;
		case "parus_usual_26.tga":shref.ship.upgrades.sails = 30;break;
		case "parus_usual_27.tga":shref.ship.upgrades.sails = 31;break;
		case "parus_usual_28.tga":shref.ship.upgrades.sails = 32;break;
		case "parus_usual_29.tga":shref.ship.upgrades.sails = 33;break;
		case "parus_usual_30.tga":shref.ship.upgrades.sails = 34;break;
		case "parus_sail_torn_black_pirate_1.tga":shref.ship.upgrades.sails = 35;break;
		case "parus_sail_torn_black_pirate_2.tga":shref.ship.upgrades.sails = 36;break;
		case "parus_sail_torn_black_pirate_3.tga":shref.ship.upgrades.sails = 37;break;
		case "parus_sail_torn_black_pirate_4.tga":shref.ship.upgrades.sails = 38;break;
		case "parus_sail_torn_black_pirate_5.tga":shref.ship.upgrades.sails = 39;break;
		case "parus_sail_torn_black_pirate_6.tga":shref.ship.upgrades.sails = 40;break;
		case "parus_sail_torn_black_pirate_7.tga":shref.ship.upgrades.sails = 41;break;
		case "parus_sail_torn_black_pirate_8.tga":shref.ship.upgrades.sails = 42;break;
		case "parus_sail_torn_black_pirate_9.tga":shref.ship.upgrades.sails = 43;break;
		case "parus_sail_torn_black_pirate_10.tga":shref.ship.upgrades.sails = 44;break;
		case "parus_sail_torn_black_pirate_11.tga":shref.ship.upgrades.sails = 45;break;
		case "parus_sail_torn_black_pirate_12.tga":shref.ship.upgrades.sails = 46;break;
		case "parus_sail_torn_black_pirate_13.tga":shref.ship.upgrades.sails = 47;break;
		case "parus_sail_torn_black_pirate_14.tga":shref.ship.upgrades.sails = 48;break;
		case "parus_sail_whole_black_pirate_1.tga":shref.ship.upgrades.sails = 49;break;
		case "parus_sail_whole_black_pirate_2.tga":shref.ship.upgrades.sails = 50;break;
		case "parus_sail_whole_black_pirate_3.tga":shref.ship.upgrades.sails = 51;break;
		case "parus_sail_whole_black_pirate_4.tga":shref.ship.upgrades.sails = 52;break;
		case "parus_sail_whole_black_pirate_5.tga":shref.ship.upgrades.sails = 53;break;
		case "parus_sail_whole_black_pirate_6.tga":shref.ship.upgrades.sails = 54;break;
		case "parus_sail_whole_black_pirate_7.tga":shref.ship.upgrades.sails = 55;break;
		case "parus_sail_whole_black_pirate_8.tga":shref.ship.upgrades.sails = 56;break;
		case "parus_sail_whole_black_pirate_9.tga":shref.ship.upgrades.sails = 57;break;
		case "parus_sail_whole_black_pirate_10.tga":shref.ship.upgrades.sails = 58;break;
		case "parus_sail_whole_black_pirate_11.tga":shref.ship.upgrades.sails = 59;break;
		case "parus_sail_whole_black_pirate_12.tga":shref.ship.upgrades.sails = 60;break;
		case "parus_sail_whole_black_pirate_13.tga":shref.ship.upgrades.sails = 61;break;
		case "parus_sail_whole_black_pirate_14.tga":shref.ship.upgrades.sails = 62;break;
		case "parus_sail_whole_black_pirate_15.tga":shref.ship.upgrades.sails = 63;break;
		case "parus_sail_whole_black_pirate_16.tga":shref.ship.upgrades.sails = 64;break;
		case "parus_sail_whole_black_pirate_17.tga":shref.ship.upgrades.sails = 65;break;
		case "parus_sail_whole_white_pirate_1.tga":shref.ship.upgrades.sails = 66;break;
		case "parus_sail_whole_white_pirate_2.tga":shref.ship.upgrades.sails = 67;break;
		case "parus_sail_whole_white_pirate_3.tga":shref.ship.upgrades.sails = 68;break;
		case "parus_sail_whole_white_pirate_4.tga":shref.ship.upgrades.sails = 69;break;
		case "parus_sail_whole_white_pirate_5.tga":shref.ship.upgrades.sails = 70;break;
		case "parus_sail_whole_white_pirate_6.tga":shref.ship.upgrades.sails = 71;break;
		case "parus_sail_whole_white_pirate_7.tga":shref.ship.upgrades.sails = 72;break;
		case "parus_sail_whole_white_pirate_8.tga":shref.ship.upgrades.sails = 73;break;
		case "parus_sail_whole_white_pirate_9.tga":shref.ship.upgrades.sails = 74;break;
		case "parus_sail_whole_white_pirate_10.tga":shref.ship.upgrades.sails = 75;break;
		case "parus_sail_whole_white_pirate_11.tga":shref.ship.upgrades.sails = 76;break;
		case "parus_sail_whole_white_pirate_12.tga":shref.ship.upgrades.sails = 77;break;
		case "parus_sail_whole_white_pirate_13.tga":shref.ship.upgrades.sails = 78;break;
		case "parus_sail_whole_white_pirate_14.tga":shref.ship.upgrades.sails = 79;break;
		case "parus_sail_whole_white_pirate_15.tga":shref.ship.upgrades.sails = 80;break;
		case "parus_sail_whole_white_pirate_16.tga":shref.ship.upgrades.sails = 81;break;
		case "parus_sail_whole_white_pirate_17.tga":shref.ship.upgrades.sails = 82;break;
		case "parus_sail_whole_white_pirate_18.tga":shref.ship.upgrades.sails = 83;break;
		case "parus_sail_whole_white_pirate_19.tga":shref.ship.upgrades.sails = 84;break;
		case "parus_sail_whole_white_pirate_20.tga":shref.ship.upgrades.sails = 85;break;
	}
	if (!sails) Log_testInfo(shref.ShipSails.Gerald_Name);
	else Log_testInfo(shref.ship.upgrades.sails);
	if (sails && CheckAttribute(shref,"EmblemedSails")) DeleteAttribute(shref,"EmblemedSails");
	AddMoneyToCharacter(Pchar, -price);
	WaitDate("",0,0,0, 1, 30);
	ProcessCancelExit();
}

void ClearSailsGerald()
{
    AddMoneyToCharacter(Pchar, -price);
	DeleteAttribute(shref, "ShipSails.Gerald_Name");
	WaitDate("",0,0,0, 1, 30);
	ProcessCancelExit();
}