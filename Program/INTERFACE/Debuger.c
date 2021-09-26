#include "ITEMS\initItems.c"

//  boal 14.02.06 ���� ��������
string totalInfo;
int idLngFile = -1;
int remInt = 0;

void InitInterface(string iniName)
{
 	StartAboveForm(true);
 	//SetTimeScale(0.0);
	//locCameraSleep(true);

	//EngineLayersOffOn(true);
	
	GameInterface.title = "titleBoal_Debug";
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CalculateInfoData();

	CalculateCheatsInfo(); // Warship. ���������� - ������� ����� �����

	SetFormatedText("INFO_TEXT",totalInfo);//"���������� ���������");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);


	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); 
	SetEventHandler("exitCancel","ProcessCancelExit",0); 
	SetEventHandler("evntDoPostExit","DoPostExit",0); 
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("SetScrollerPos","SetScrollerPos",0);
	SetEventHandler("ScrollPosChange","ProcScrollPosChange",0);
	SetEventHandler("ScrollTopChange","ProcScrollChange",0);

    GameInterface.reload_edit.str = "Pirates_Shipyard, reload, reload1";//"Pearl_town_1, reload, reload1";
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_QUICK_SAVE );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_QUICK_SAVE );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    //SetTimeScale(1.0);
	//locCameraSleep(false);
	
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ievnt_command","ProcCommand");
 	DelEventHandler("SetScrollerPos","SetScrollerPos");
	DelEventHandler("ScrollPosChange","ProcScrollPosChange");
	DelEventHandler("ScrollTopChange","ProcScrollChange");

	if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	// ��� ����������� ������ ���������� � ������� � totalInfo - ������������� -->
	totalInfo = "��� ��������. ��������� ��������� �������� ������������ �������. ������: "+NewStr();
	totalInfo = totalInfo + "1 - " + descF1 + NewStr() +
	                        "2 - " + descF2 + NewStr() +
	                        "3 - " + descF3 + NewStr() +
	                        "4 - " + descF4 + NewStr() +
	                        "5 - " + descF5 + NewStr() +
	                        "6 - " + descF6 + NewStr() +
	                        "7 - " + descF7 + NewStr() +
	                        "8 - " + descF8 + NewStr() +
	                        "9 - " + descF9 + NewStr() +
	                        "10 - " + descF10 + NewStr() +
	                        "11 - " + descF11 + NewStr() +
	                        "12 - " + descF12 + NewStr() +
	                        "13 - " + descF13 + NewStr() +
	                        "14 - " + descF14 + NewStr() +
	                        "15 - " + descF15 + NewStr() +
	                        "16 - " + descF16 + NewStr() +
	                        "17 - " + descF17 + NewStr() +
	                        "18 - " + descF18 + NewStr() +
                            "19 - " + descF19 + NewStr() +
                            "20 - " + descF20 + NewStr() +
                            "21 - " + descF21 + NewStr() +
                            "22 - " + descF22 + NewStr() +
                            "23 - " + descF23 + NewStr() +
	                        "24 - " + descF24 + NewStr() +
	                        "25 - " + descF25 + NewStr() +
	                        "26 - " + descF26 + NewStr() +
	                        "27 - " + descF27 + NewStr() +
	                        "28 - " + descF28 + NewStr() +
	                        "29 - " + descF29 + NewStr() +
	                        "30 - " + descF30 + NewStr() +
							"31 - " + descF31 + NewStr() +
	                        "32 - " + descF32 + NewStr() +
							"33 - " + descF33 + NewStr() +
	                        "34 - " + descF34 + NewStr() +
							"35 - " + descF35 + NewStr() +
	                        "36 - " + descF36 + NewStr() +
	                        "37 - " + descF37 + NewStr() +
	                        "38 - " + descF38 + NewStr() +
	                        "39 - " + descF39 + NewStr() +
	                        "40 - " + descF40 + NewStr() +
                            "41 - " + descF41 + NewStr() +
                            "42 - " + descF42 + NewStr() +
                            "43 - " + descF43 + NewStr() +
	                        "44 - " + descF44 + NewStr() +
	                        "45 - " + descF45 + NewStr() +
	                        "46 - " + descF46 + NewStr() +
	                        "47 - " + descF47 + NewStr() +
							"48 - " + descF48 + NewStr() +
							"49 - " + descF49 + NewStr() +
							"50 - " + descF50 + NewStr() +
							"51 - " + descF51 + NewStr() +
							"52 - " + descF52 + NewStr() +
							"53 - " + descF53 + NewStr() +
							"54 - " + descF54 + NewStr() +
							"55 - " + descF55 + NewStr() +
							"56 - " + descF56 + NewStr() +
							"57 - " + descF57 + NewStr() +
							"58 - " + descF58 + NewStr() +
							"59 - " + descF59 + NewStr() +
							"60 - " + descF60 + NewStr() +
							"61 - " + descF61 + NewStr() +
							"62 - " + descF62 + NewStr() +
							"63 - " + descF63 + NewStr() +
							"64 - " + descF64 + NewStr() +
							"65 - " + descF65 + NewStr() +
							"66 - " + descF66 + NewStr() +
							"67 - " + descF67 + NewStr() +
							"68 - " + descF68 + NewStr() +
							"69 - " + descF69 + NewStr() +
							"70 - " + descF70 + NewStr() +
							"71 - " + descF71 + NewStr() +
							"72 - " + descF72 + NewStr() +
							"73 - " + descF73 + NewStr() +
							"74 - " + descF74 + NewStr() +
							"75 - " + descF75 + NewStr() +
							"76 - " + descF76 + NewStr() +
							"77 - " + descF77 + NewStr() +
							"78 - " + descF78 + NewStr() +
							"79 - " + descF79 + NewStr() +
							"80 - " + descF80 + NewStr() +
							"81 - " + descF81 + NewStr() +
							"82 - " + descF82 + NewStr() +
							"83 - " + descF83 + NewStr() +
							"84 - " + descF84 + NewStr() +
							"85 - " + descF85 + NewStr() +
							"86 - " + descF86 + NewStr() +
							"87 - " + descF87 + NewStr() +
							"88 - " + descF88;
	// ������� ������ (�� ������� � ���� �� �����) +LanguageConvertString(idLngFile,"new_string");
    // ��� ����������� ������ ���������� � ������� � totalInfo <--
}
void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	    case "B_F1":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF1();
		  }
	    break;
	    case "B_F2":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF2();
		  }
	    break;
	    case "B_F3":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF3();
		  }
	    break;
	    case "B_F4":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF4();
		  }
	    break;
	    case "B_F5":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF5();
		  }
	    break;

	    case "B_F6":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF6();
		  }
	    break;

	    case "B_F7":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF7();
		  }
	    break;

	    case "B_F8":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF8();
		  }
	    break;

	    case "B_F9":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF9();
		  }
	    break;

	    case "B_F10":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF10();
		  }
	    break;

	    case "B_F11":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF11();
		  }
	    break;

	    case "B_F12":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF12();
		  }
	    break;

	    case "B_F13":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF13();
		  }
	    break;

	    case "B_F14":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF14();
		  }
	    break;

	    case "B_F15":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF15();
		  }
	    break;

	    case "B_F16":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF16();
		  }
	    break;

	    case "B_F17":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF17();
		  }
	    break;

	    case "B_F18":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF18();
		  }
	    break;
	    
	    case "B_F19":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF19();
		  }
	    break;

        case "B_F20":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF20();
		  }
	    break;
	    
	    case "B_F21":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF21();
		  }
	    break;
	    case "B_F22":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF22();
		  }
	    break;
	    case "B_F23":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF23();
		  }
	    break;
	    case "B_F24":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF24();
		  }
	    break;
	    case "B_F25":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF25();
		  }
	    break;
	    case "B_F26":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF26();
		  }
	    break;
	    case "B_F27":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF27();
		  }
	    break;
	    case "B_F28":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF28();
		  }
	    break;
	    case "B_F29":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF29();
		  }
	    break;
	    case "B_F30":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF30();
		  }
	    break;
	    case "B_F31":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF31();
		}
	    break;
	    case "B_F32":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF32();
		}
	    break;
		case "B_F33":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF33();
		}
	    break;	
		case "B_F34":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF34();
		}
	    break;
		case "B_F35":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF35();
		}
	    break;
		case "B_F36":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF36();
		}
	    break;	
		case "B_F37":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF37();
		}
	    break;	
		case "B_F38":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF38();
		}
	    break;	
		case "B_F39":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF39();
		}
	    break;	
		case "B_F40":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF40();
		}
	    break;	
		case "B_F41":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF41();
		}
	    break;	
		case "B_F42":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF42();
		}
	    break;	
		case "B_F43":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF43();
		}
	    break;	
		case "B_F44":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF44();
		}
	    break;
	    case "B_F45":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF45();
		  }
	    break;
	    case "B_F46":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF46();
		  }
	    break;
	    case "B_F47":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF47();
		  }
	    break;
	    case "B_F48":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF48();
		  }
	    break;
	    case "B_F49":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF49();
		  }
	    break;

	    case "B_F50":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF50();
		  }
	    break;

	    case "B_F51":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF51();
		  }
	    break;

	    case "B_F52":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF52();
		  }
	    break;

	    case "B_F53":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF53();
		  }
	    break;

	    case "B_F54":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF54();
		  }
	    break;

	    case "B_F55":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF55();
		  }
	    break;

	    case "B_F56":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF56();
		  }
	    break;

	    case "B_F57":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF57();
		  }
	    break;

	    case "B_F58":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF58();
		  }
	    break;

	    case "B_F59":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF59();
		  }
	    break;

	    case "B_F60":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF60();
		  }
	    break;

	    case "B_F61":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF61();
		  }
	    break;

	    case "B_F62":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF62();
		  }
	    break;
	    
	    case "B_F63":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF63();
		  }
	    break;

        case "B_F64":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF64();
		  }
	    break;
	    
	    case "B_F65":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF65();
		  }
	    break;
	    case "B_F66":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF66();
		  }
	    break;
	    case "B_F67":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF67();
		  }
	    break;
	    case "B_F68":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF68();
		  }
	    break;
	    case "B_F69":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF69();
		  }
	    break;
	    case "B_F70":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF70();
		  }
	    break;
	    case "B_F71":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF71();
		  }
	    break;
	    case "B_F72":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF72();
		  }
	    break;
	    case "B_F73":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF73();
		  }
	    break;
	    case "B_F74":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF74();
		  }
	    break;
	    case "B_F75":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF75();
		}
	    break;
	    case "B_F76":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF76();
		}
	    break;
		case "B_F77":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF77();
		}
	    break;	
		case "B_F78":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF78();
		}
	    break;
		case "B_F79":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF79();
		}
	    break;
		case "B_F80":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF80();
		}
	    break;	
		case "B_F81":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF81();
		}
	    break;	
		case "B_F82":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF82();
		}
	    break;	
		case "B_F83":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF83();
		}
	    break;	
		case "B_F84":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF84();
		}
	    break;	
		case "B_F85":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF85();
		}
	    break;	
		case "B_F86":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF86();
		}
	    break;	
		case "B_F87":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF87();
		}
	    break;	
		case "B_F88":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF88();
		}
	    break;
	    case "B_BETA":
		  if(comName=="activate" || comName=="click")
		  {
              IDoExit(RC_INTERFACE_DO_BOAL_BETA);
		  }
	    break;
	    case "B_RELOAD":
		  if(comName=="activate" || comName=="click")
		  {
              ReloadByStr();
		  }
	    break;
	}
	
	CalculateCheatsInfo(); // ���������� �� �����
}

////////////////////////////////////////////////////////////////////////
string descF1 = "������ + 500 000";

void CalculateInfoDataF1()
{
	totalInfo = descF1;
	Pchar.money = sti(Pchar.money) + 500000;
	totalInfo = totalInfo + GetAssembledString(" ����� � #sName#� ������ #dmoney#",	Pchar);
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);

	Statistic_AddValue(PChar, "Cheats.F1", 1);
}

////////////////////////////////////////////////////////////////////////
string descF2 = "CreateSiege";

void CalculateInfoDataF2()
{
	// -->
	totalInfo = descF2;
	//TraderHunterOnMap();
	CreateSiege("");
    // <
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);

	ProcessCancelExit();
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F2", 1);
}
////////////////////////////////////////////////////////////////////////
string descF3 = "ID ������� ������� + ����� ";

void CalculateInfoDataF3()
{
	// -->
	totalInfo = descF3;
	ref mc;
	mc = GetMainCharacter();

	float locx, locy, locz, locay;
	if (bSeaActive && !bAbordageStarted)
	{
	    if (CheckAttribute(mc, "Ship.pos.x"))
		{
		    totalInfo = totalInfo + NewStr() + mc.location + "     ship(x,z)= "+mc.Ship.pos.x +", "+mc.Ship.pos.z;
			totalInfo = totalInfo + NewStr() + " Sea_Coord.X " + Sea_GetRealCoordX(makefloat(mc.Ship.pos.x)) + " Sea_Coord.Z " + Sea_GetRealCoordZ(makefloat(mc.Ship.pos.z));
		    if (false)//CheckAttribute(mc, "WMShip.Pos.x") && worldMap.island != "")
	        {
	            string sTemp = mc.curIslandId;
	            float r1 = stf(worldMap.islands.(sTemp).GoMapRadius);

				r1 *= WDM_MAP_TO_SEA_SCALE;
	            float d2 = GetDistance2D(stf(mc.Ship.Pos.x),
	                              stf(mc.Ship.Pos.z),
	                              stf(worldMap.islands.(sTemp).position.rx),
	                              stf(worldMap.islands.(sTemp).position.rz));

	            totalInfo = totalInfo + "         ���������� ��� ����� radius= " + r1 + "   GetDistance2D= " + d2 + "      ";
	        }
		}
	}
	else
	{
  		if (IsEntity(loadedLocation))
  		{
  		    float xx,zz,xz,zx;

			GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
			GetCharacterAy(GetMainCharacter(), &locay);
			xx = -sin(locay - PId2);
            zz = xx;
            xz = -cos(locay - PId2);
            zx = -xz;
			totalInfo = totalInfo + "id = " + mc.location + " (x,y,z, xx,zz)= "+locx + ", " +locy + ", "+locz + ", "+xx + ", "+xz;
			totalInfo = totalInfo + NewStr() + "filespath.models = " + loadedLocation.filespath.models;
			totalInfo = totalInfo + NewStr() + "image = " + loadedLocation.image;
			totalInfo = totalInfo + NewStr() + "models.locators = " + loadedLocation.models.always.locators;
   
  
			
			if(CheckAttribute(LoadedLocation, "islandId"))
			{
				totalInfo = totalInfo + NewStr() + "islandId = " + LoadedLocation.islandId;
			}
			
			if(CheckAttribute(LoadedLocation, "townsack"))
			{
				totalInfo = totalInfo + NewStr() + "townsack = " + LoadedLocation.townsack;
			}
		}
	}
/*	
	aref rootItems;
    makearef(rootItems, worldMap);  //Islands[0]
	DumpAttributes(rootItems);
*/	
	totalInfo = totalInfo + NewStr() + " MapShipX " +	worldMap.playerShipX + " MapShipZ " + worldMap.playerShipZ + " X " + worldMap.island.x + " Z " + worldMap.island.z;
	
	totalInfo = totalInfo + NewStr() + " Map_Coord.X " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)) + " Map_Coord.Z " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ));
	
	totalInfo = totalInfo + NewStr() + " Zero_Point_X " + makefloat(worldMap.zeroX) + " Zero_Point_Z " + makefloat(worldMap.zeroZ);
    // <
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	GetRealCoordsObjects();
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F3", 1);
}
////////////////////////////////////////////////////////////////////////
string descF4 = "���� ������� +10";

void CalculateInfoDataF4()
{
	// -->
	totalInfo = descF4;
	//locCameraLock(3);    ������ ������������� �� ���� (������ ������)
	///mc.model.animation = "man";
	//mc.model = "napitan";
	//SetNewModelToChar(mc);
    ChangeCrewExp(pchar, "Sailors", 10);
	ChangeCrewExp(pchar, "Cannoners", 10);
	ChangeCrewExp(pchar, "Soldiers", 10);

	//float mhp = LAi_GetCharacterMaxHP(mc) + 5;
	//LAi_SetHP(mc,mhp,mhp);
	//totalInfo = totalInfo+ " iNumShips="+iNumShips+" iNumFantoms="+iNumFantoms;
	//ddCharacterExp(mc, 3000);
    // <
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F4", 1);
}
////////////////////////////////////////////////////////////////////////
string descF5 = "���� 1000 ������ ��� �������";
int BOAL_debug_num = 1;
void CalculateInfoDataF5()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF5;
    /*  pchar.PatentNation = "eng";
      GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
      EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);
      */
    pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 1000;
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F5", 1);
}
////////////////////////////////////////////////////////////////////////
string descF6 = "�������, �� � 48-�� ��������, 20-�� ����";

void CalculateInfoDataF6()
{
	ref mc;
	string sEquipItem;
	totalInfo = descF6;
	mc = GetMainCharacter();
	// SetRandSelfSkill(mc, 50, 85);
	// SetRandShipSkill(mc, 50, 85);
	// mc.rank = 20;
	
	SetRandSelfSkill(mc, 100, 100);
	SetRandShipSkill(mc, 100, 100);
	mc.rank = 50;
	LAi_SetHP(mc, 6500.0, 6500.0);
	// mc.Ship.Type = GenerateShipExt(SHIP_LUGGERQUEST, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_BRIGQEEN, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_BRIGSW, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_FRIGATEQUEEN, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_FLYINGDUTCHMAN, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_SANTISIMA, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_SOLEYRU, true, mc);
	// mc.Ship.Type = GenerateShipExt(SHIP_WH_CORVETTE_QUEST, true, mc);
	mc.Ship.Type = GenerateShipExt(SHIP_PRINCE, true, mc);
	SetBaseShipData(mc);
	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
	// mc.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS24;
	SetCrewQuantityFull(mc);
	AddCrewMorale(mc, 100);
	ChangeCrewExp(mc, "Sailors", 100);
	ChangeCrewExp(mc, "Cannoners", 100);
	ChangeCrewExp(mc, "Soldiers", 100);

	SetCharacterGoods(mc, GOOD_BALLS, 2000);
	SetCharacterGoods(mc, GOOD_GRAPES, 2000);
	SetCharacterGoods(mc, GOOD_KNIPPELS, 2000);
	SetCharacterGoods(mc, GOOD_BOMBS, 2000);;
	//SetCharacterGoods(mc, GOOD_FOOD, 2000);
	SetCharacterGoods(mc, GOOD_FOOD, 10000);
	SetCharacterGoods(mc, GOOD_MEDICAMENT, 1000);
	SetCharacterGoods(mc, GOOD_POWDER, 3000);
	SetCharacterGoods(mc, GOOD_WEAPON, 1500);

	sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);

	AddMoneyToCharacter(mc, 1000000);
	AddItems(mc, "spyglass4", 1);
	AddItems(mc, "pistol7", 1);
	AddItems(mc, "Map_Best", 1);
	
	// sEquipItem = GetGeneratedItem("blade27"); 				// ������� 			(��)
	// sEquipItem = GetGeneratedItem("blade32"); 				// ��������			(��)
	// sEquipItem = GetGeneratedItem("katar"); 					// �����			(��)
	// sEquipItem = GetGeneratedItem("toporAZ"); 				// ����������		(��)
	// sEquipItem = GetGeneratedItem("topor_viking"); 			// ����� �������	(��)
	// sEquipItem = GetGeneratedItem("blade28");				// �����			(��)
	sEquipItem = GetGeneratedItem("blackbeard_sword_baron");	// ��� �������		(��)
	AddItems(mc, sEquipItem, 1);
	
	AddItems(mc, "cirass5", 1);

	EquipCharacterbyItem(mc, "spyglass4");
	EquipCharacterbyItem(mc, "pistol7");
	GiveGunAmmunition(mc,"pistol7");
 	EquipCharacterbyItem(mc, sEquipItem);
 	EquipCharacterbyItem(mc, "cirass5");
 	
 	SetHalfPerksToChar(mc, false);
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F6", 1);
}
////////////////////////////////////////////////////////////////////////
string descF7 = "�������� ��� ������ ������ �� 1";

void CalculateInfoDataF7()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF7;

	SetRandSelfSkill(PChar, 1, 1);
    
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F7", 1);
}
////////////////////////////////////////////////////////////////////////
string descF8 = "�������� �� ��������";

void CalculateInfoDataF8()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF8;
	ref mc, ch;
	int n, idx;
	mc = GetMainCharacter();
    idx = GetCharIDXByParam("TavernMan", "location", mc.location);
    bool ok = true;
    while (ok)
    {
        for(n=0; n<MAX_CHARACTERS; n++)
    	{
    		makeref(ch,Characters[n]);
    		if (CheckAttribute(ch, "TavernMan"))
    		{
                if (ch.location == "none") continue; // ���� ��� �����, ��������� �� ���� ��������
                if (n > idx)
                {
                    ok = false;
                    if (GetCityFrom_Sea(ch.City) != "")
                    {
						setCharacterShipLocation(mc, GetCityFrom_Sea(ch.City));
                        setWDMPointXZ(GetCityFrom_Sea(ch.City));
                    }
                    DoQuestReloadToLocation(ch.location,"reload","reload1", "");
                    Log_Info(ch.location);
                    break;
                }
    		}
        }
        idx = -1;
    }
	// <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F8", 1);
}

string descF9 = "������ ���������� ��� ��������� �������";
void CalculateInfoDataF9()
{
	SetCharacterGoods(pchar, GOOD_BALLS, 2000);
	SetCharacterGoods(pchar, GOOD_GRAPES, 2000);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 2000);
	SetCharacterGoods(pchar, GOOD_BOMBS, 2000);;
	SetCharacterGoods(pchar, GOOD_FOOD, 6000);
	SetCharacterGoods(pchar, GOOD_POWDER, 3000);
	SetCharacterGoods(pchar, GOOD_SLAVES, 3000);
	SetCharacterGoods(pchar, GOOD_BRICK, 2500);
	SetCharacterGoods(pchar, GOOD_MAHOGANY, 1500);
	SetCharacterGoods(pchar, GOOD_EBONY, 1500);
	SetCharacterGoods(pchar, GOOD_PLANKS, 3000);
	SetCharacterGoods(pchar, GOOD_TOOLS, 1500);
	SetCharacterGoods(pchar, GOOD_MEDICAMENT, 10000);
	
	totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F19", 1);
}

////////////////////////////////////////////////////////////////////////
string descF10 = "���������� ���/����";

void CalculateInfoDataF10()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF10;
	ref mc;
	mc = GetMainCharacter();
			if(LAi_IsImmortal(mc))
			{
				LAi_SetImmortal(mc, false);
				Log_SetStringToLog("God mode OFF");
			}else{
				LAi_SetImmortal(mc, true);
				Log_SetStringToLog("God mode ON");
			}
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F10", 1);
}
////////////////////////////////////////////////////////////////////////
string descF11 = "��������� � ����";

void CalculateInfoDataF11()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	totalInfo = descF11;
	// -->

    int i, cn;
    ref mc;
	mc = GetMainCharacter();

    if ( sti(mc.reputation) < REPUTATION_MAX)
	{
	   mc.reputation = sti(mc.reputation) + 10;
	   if (sti(mc.reputation) > REPUTATION_MAX)
	   {
	       mc.reputation = REPUTATION_MAX;
	   }
	}
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F11", 1);
}
////////////////////////////////////////////////////////////////////////
string descF12 = "��� � ���� ����� -50";//�������� ������� ������� �� ��";  //"LaunchMunityCapture";;

void CalculateInfoDataF12()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF12;
    for (int j=0; j< MAX_NATIONS; j++)
	{
        ChangeCharacterNationReputation(pchar, j, -50);
    }
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������! ";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F12", 1);
}

string descF13 = "Worldmap encounters ON/OFF";

void CalculateInfoDataF13()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF13;

    ref mc;
	mc = GetMainCharacter();
    if(CheckAttribute(mc,"worldmapencountersoff") == 0)
	{
		mc.worldmapencountersoff = "1";
		Log_SetStringToLog("Worldmap encounters OFF");
	}
	else
	{
		if(mc.worldmapencountersoff == "1")
		{
			mc.worldmapencountersoff = "0";
			Log_SetStringToLog("Worldmap encounters ON");
		}
		else
		{
			mc.worldmapencountersoff = "1";
			Log_SetStringToLog("Worldmap encounters OFF");
		}
	}
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F13", 1);
}

string descF14 = "Shotgun mode ON\OFF";

void CalculateInfoDataF14()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF14;
    if(globalSGMode != false)
	{
		globalSGMode = false;
		Log_SetStringToLog("Shotgun mode OFF");
	}else{
		globalSGMode = true;
		Log_SetStringToLog("Shotgun mode ON");
	}
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������! Qfreze=";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F14", 1);
}

string descF15 = "������� ����� ��������� �����";

void CalculateInfoDataF15()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF15;

    DoQuestCheckDelay("Nation_Legend_Map", 2.0);
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    ProcessCancelExit();
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F15", 1);
}

string descF16 = "+5 ����";

void CalculateInfoDataF16()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF16;

    LAi_Fade("", "");
    for (int i = 1; i<=5; i++)
    {
		AddDataToCurrent(0, 0, 1);
	}
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F16", 1);
}

string descF17 = "������ ������� � pchar";

void CalculateInfoDataF17()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF17;

    aref  curItem;
	aref  arItem;
	aref rootItems;
	int i, j, n;
	string attributeName;
	ref ch;

	//makeref(ch,Characters[GetCharacterIndex("Oxbay Commander")]);
	//makearef(rootItems,ch.Ship);
    //makearef(rootItems,Characters[GetMainCharacterIndex()].Items);
    //makearef(rootItems,ShipsTypes[Characters[GetMainCharacterIndex()].Ship.Type].Cannons.Borts.cannonl);

    makearef(rootItems, pchar.quest);

    //aref qst = makearef(qst, pchar.quest);

    trace("=================================================");
    DumpAttributes(rootItems);//&GameInterface);
    trace("=================================================");
    Log_Info("DumpAttributes");
    /*for(i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		j = sti(GetAttributeValue(curItem));
		totalInfo = totalInfo+"   "+i+"= "+//LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                    GetAttributeName(curItem)+" value="+j;

        for(n=0; n<GetAttributesNum(curItem); n++)
        {
                 arItem = GetAttributeN(curItem,n);
		         j = sti(GetAttributeValue(arItem));
		         totalInfo = totalInfo+//LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                    "   --> "+n+"= "+GetAttributeName(arItem)+" value="+j;
        }

    }*/
    remInt++;
    totalInfo = totalInfo + " page " + remInt;
    for(i=0; i<GetAttributesNum(rootItems); i++)
    {
        if (i > remInt*60 || i < (remInt-1)*60) continue;

        curItem = GetAttributeN(rootItems, i);
		j = sti(GetAttributeValue(curItem));
		totalInfo = totalInfo+"   "+i+"= "+//LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                    GetAttributeName(curItem);// + " : " + GetAttributeValue(curItem);

        /*for(n=0; n<GetAttributesNum(curItem); n++)
        {
                 arItem = GetAttributeN(curItem,n);
		         j = sti(GetAttributeValue(arItem));
		         totalInfo = totalInfo+//LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                    "   --> "+n+"= "+GetAttributeName(arItem)+" value="+j;
        } */

    }
    if (i <= remInt*60) remInt = 0;
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F17", 1);
}

//string descF18 = "ChangeShowIntarface - ��� ������� ��� ��������";
string descF18 = "������ 10 ��������";
void CalculateInfoDataF18()
{
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	// -->
	totalInfo = descF18;

    //LandEncTemplate[4].enc1.chance = 1.0;
    //LandEncTemplate[4].enc2.chance = 1.0;
    //
    /*if (bSeaActive)
    {
        Weathers[iCurWeatherNum].Wind.Speed.Min = 9.9;
    	Weathers[iCurWeatherNum].Wind.Speed.Max = 10.1;
	} */
	//ChangeShowIntarface();
    //
	for(i=1; i<11; i++)
    {
		ref sld = GetCharacter(NPC_GenerateCharacter("DebugOfficer_"+i, "officer_"+i, "man", "man", 30, PIRATE, -1, true));
		sld.greeting = "Gr_questOfficer";
		sld.Dialog.Filename = "Enc_Officer_dialog.c";
		sld.quest.meeting = true;
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
		SetSPECIAL(sld, 6, 10, 9, 10, 10, 8, 10);
		SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
		SetCharacterPerk(sld, "BasicBattleState");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "LightRepair");
		SetCharacterPerk(sld, "InstantRepair");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "Turn180");
		SetCharacterPerk(sld, "SailingProfessional");
		SetCharacterPerk(sld, "Carpenter");
		SetCharacterPerk(sld, "Builder");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "Doctor2");
		sld.quest.OfficerPrice = sti(pchar.rank)*100;
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
		sld.OfficerWantToGo.DontGo = true; //�� �������� ����
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		sld.location = "None";
		sld.Dialog.CurrentNode = "hired";
		sld.Payment = true;
		sld.DontClearDead = true;
		DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
		DeleteAttribute(sld, "LifeDay")
		SaveCurrentNpcQuestDateParam(sld, "HiredDate"); // ���� �����
	}
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "������� ���������� �������!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F18", 1);
}

string descF19 = "�������-������� +1 ���� (35 ����� ������)";
void CalculateInfoDataF19()
{
    totalInfo = descF19;
	// -->
    if (sti(pchar.Fellows.Passengers.navigator) != -1)
	{
	    ref chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));

    	chr.Skill.FreeSkill  = sti(chr.Skill.FreeSkill) + 35;
    }
    else
    {
        totalInfo = "��� �������";
    }
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F19", 1);
}

string descF20 = "���������� ����� �� ������";
void CalculateInfoDataF20()
{
    totalInfo = descF20;
	// -->
	Sea_CreateLighthouse("Jamaica");
	Sea_CreateLighthouse("Cuba1");
	Sea_CreateLighthouse("Cuba2");
	SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION,-116.0, 55.0, -1568.5, 1, 0, 0, 0, 1, 0, 0, 0, 1);
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F20", 1);
}

//string descF21 = "��������� ������ � ����� (-5, 2, -5) ������������ ��";
string descF21 = "��������� ������ ������ �� 35 �� Y ������������ ��";
void CalculateInfoDataF21()
{
    totalInfo = descF21;
	// -->
	//locCameraRotateAroundHero(0.0, 3.0, 0.0, 0.03, 0.0, 3.0, 0.0, 200);
	//locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.0, 0.01, 5.0, 0.0, 150);
	//locCameraRotateAroundHero(0.0, 1.0, 0.0, -0.03, 0.03, 7.0, 0.0, 225);
	//locCameraFlyToPosition(stf(Camera.pos.x), stf(Camera.pos.y), stf(Camera.pos.z), stf(Camera.pos.x), stf(Camera.pos.y) + 30, stf(Camera.pos.z), 0.9, -1);
	// locCameraFlyToPosition(stf(Camera.pos.x), stf(Camera.pos.y), stf(Camera.pos.z), stf(Camera.pos.x), stf(Camera.pos.y) + 35, stf(Camera.pos.z), 0.05, -1);
	locCameraLockNearHero(-5.0, 2.0, -5.0, 200, true);

    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F21", 1);
}

string descF22 = "������� ����";
void CalculateInfoDataF22()
{
    totalInfo = descF22;
	// -->
    {
		totalInfo = "��������� ������ ������: " + pchar.questTemp.Ascold.TraderId + NewStr() +
					"��������� �������(�������): " + pchar.questTemp.Ascold.MerchantColony + NewStr() +
					"��������� �������: " + pchar.questTemp.Ascold.ShipyarderId + NewStr()+
					"�������� �������: " + Items[GetItemIndex("Rock_letter")].startLocation + NewStr()+
					"�������� �������: " + Items[GetItemIndex("Rock_letter")].startLocator;
					if (pchar.questTemp.BlueBird.City != "")
					{
						totalInfo = totalInfo + NewStr()+ "��� ����� ����� �� ������ ��������: " + pchar.questTemp.BlueBird.City;
					}
					else
					{
						totalInfo = totalInfo + NewStr()+ "����� �� ������� ��������� ��� �� ������������.";
					}
    }
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F22", 1);
}

string descF23 = "���� ���������� ������";
void CalculateInfoDataF23()
{
    totalInfo = descF23;
	// -->
    DumpAttributes(&Camera);
	totalInfo += "\n\nCamera.pos.x == " + Camera.pos.x +
		"\nCamera.pos.y = " + Camera.pos.y +
		"\nCamera.pos.z == " + Camera.pos.z +
		"\n\nCamera.ang.z == " + Camera.ang.y +
		"\nCamera.ang.y == " + Camera.ang.z +
		"\nCamera.ang.x == " + Camera.ang.y + "\n\n";
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F23", 1);
}

string descF24 = "��������";
void CalculateInfoDataF24()
{
    totalInfo = descF24;
	// -->
    GiveNationLicence(sti(pchar.nation), 30);
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F24", 1);
}

string descF25 = "�������� ������� - ��� �����";
void CalculateInfoDataF25()
{
    totalInfo = descF25;
	// -->
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
    ProcessCancelExit();
    if( bSeaActive && !bAbordageStarted )
    {
    	Sea_ReloadStart();
	}
	else
	{
	    DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
	}
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F25", 1);
}

string descF26 = "���� ��������� ��";
void CalculateInfoDataF26()
{
	totalInfo = descF26;
	// -->
    ref characterRef = GetMainCharacter();
		
	trace("==================== " + characterRef.ID + " ====================");
	DumpAttributes(characterRef);
	trace("========================================");

	ref realShip;
	int shipType = sti(characterRef.Ship.Type);

	if(shipType != SHIP_NOTUSED) // ���� �� ������� ������
	{
		realShip = GetRealShip(shipType);	
		DumpAttributes(realShip);
	}
		
	Log_Info("���� ���������� ��");			
	// <--
	totalInfo = totalInfo + NewStr() + NewStr() +
		"������� ���������� �������!";
	SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.26", 1);
}

string descF27 = "��������� �� � �����";
void CalculateInfoDataF27()
{
    totalInfo = descF27;
	// -->
	if ( sti(pchar.reputation) > 1)
	{
	   pchar.reputation = sti(pchar.reputation) - 10;
	   if (sti(pchar.reputation) < 1)
	   {
	       pchar.reputation = 1;
	   }
	}
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F27", 1);
}

string descF28 = "������� �� �� �����";
void CalculateInfoDataF28()
{
    totalInfo = descF28;
	// -->
	GhostShipOnMap();
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F28", 1);
}

string descF29 = "��� � ���� ����� +50";
void CalculateInfoDataF29()
{
    totalInfo = descF29;
	// -->
	for (int j=0; j< MAX_NATIONS; j++)
	{
        ChangeCharacterNationReputation(pchar, j, 50);
    }
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F29", 1);
}

string descF30 = "+20 ����";
void CalculateInfoDataF30()
{
    totalInfo = descF30;
	// -->
	LAi_Fade("", "");
	AddDataToCurrent(0, 0, 20);
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "������� ���������� �������!";
    SetFormatedText("INFO_TEXT",totalInfo);
    
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F30", 1);
}

string descF31 = "��������, 32 ������, ������ �������� ��, ��� �����, �������� + ���������� ������";
void CalculateInfoDataF31()
{
	ref mc;
	string sEquipItem;
	totalInfo = descF31;
	mc = GetMainCharacter();
	SetRandSelfSkill(mc, 100, 100);
	SetRandShipSkill(mc, 100, 100);
	LAi_SetHP(mc, 380.0, 380.0);
	mc.rank = 25;
//	mc.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, true, mc);
	mc.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, mc);
//	mc.Ship.Type = GenerateShipExt(SHIP_FRIGATEQUEEN, true, mc);
	SetBaseShipData(mc);
	int iShip = pchar.ship.type;
	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
//	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(mc);
	AddCrewMorale(mc, 100);
	ChangeCrewExp(mc, "Sailors", 100);
	ChangeCrewExp(mc, "Cannoners", 100);
	ChangeCrewExp(mc, "Soldiers", 100);

	SetCharacterGoods(mc, GOOD_BALLS, 1000);
	SetCharacterGoods(mc, GOOD_GRAPES, 1000);
	SetCharacterGoods(mc, GOOD_KNIPPELS, 1000);
	SetCharacterGoods(mc, GOOD_BOMBS, 1000);;
	SetCharacterGoods(mc, GOOD_FOOD, 6000);
	SetCharacterGoods(mc, GOOD_MEDICAMENT, 1000);
	SetCharacterGoods(mc, GOOD_POWDER, 4000);
	SetCharacterGoods(mc, GOOD_WEAPON, 500);

	sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, BACKPACK_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);

	AddMoneyToCharacter(mc, 10000000);
	AddItems(mc, "spyglass5", 1);
	AddItems(mc, "pistol5", 1);
	AddItems(mc, "Mushket", 1);
	AddItems(mc, "BackPack5", 1);
	
	// ��� �������� -->
	AddItems(mc, "Food5", 30);
	AddItems(mc, "potion2", 30);
	AddItems(mc, "HealthTube", 3);
	AddItems(mc, "EnergyTube", 3);
	AddItems(mc, "StrangeElixir", 3);
	// ��� �������� <--
	
	sEquipItem = GetGeneratedItem("blade32");
	AddItems(mc, sEquipItem, 1);
	
	AddItems(mc, "bullet", 50);
	AddItems(mc, "GunPowder", 50);
	AddItems(mc, "Map_Best", 1);
	AddItems(mc, "cirass5", 1);

	EquipCharacterbyItem(mc, "spyglass5");
	EquipCharacterbyItem(mc, "pistol5");
 	EquipCharacterbyItem(mc, sEquipItem);
 	EquipCharacterbyItem(mc, "cirass5");
	EquipCharacterbyItem(mc, "BackPack5");
 	
 	SelAllPerksToChar(mc, false);
	 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
		
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F31", 1);
}

string descF32 = "������� �������, �������� �������� ��";
void CalculateInfoDataF32()
{
	ref mc;
	string sEquipItem;
	totalInfo = descF32;
	mc = GetMainCharacter();
	SetRandSelfSkill(mc, 40, 75);
	SetRandShipSkill(mc, 40, 75);
	mc.rank = 10;
//	mc.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, mc);
	mc.Ship.Type = GenerateShipExt(SHIP_BRIGSW, true, mc);
	SetBaseShipData(mc);
	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(mc);
	AddCrewMorale(mc, 80);
	ChangeCrewExp(mc, "Sailors", 50);
	ChangeCrewExp(mc, "Cannoners", 50);
	ChangeCrewExp(mc, "Soldiers", 50);

	SetCharacterGoods(mc, GOOD_BALLS, 700);
	SetCharacterGoods(mc, GOOD_GRAPES, 700);
	SetCharacterGoods(mc, GOOD_KNIPPELS, 700);
	SetCharacterGoods(mc, GOOD_BOMBS, 700);;
	SetCharacterGoods(mc, GOOD_FOOD, 3000);
	SetCharacterGoods(mc, GOOD_MEDICAMENT, 500);
	SetCharacterGoods(mc, GOOD_POWDER, 2000);
	SetCharacterGoods(mc, GOOD_WEAPON, 500);

	sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);

	AddMoneyToCharacter(mc, 1000000);
	AddItems(mc, "spyglass3", 1);
	AddItems(mc, "pistol5", 1);
	
	sEquipItem = GetGeneratedItem("blade27");
	AddItems(mc, sEquipItem, 1);
	
	AddItems(mc, "bullet", 50);
	AddItems(mc, "GunPowder", 50);
	AddItems(mc, "cirass4", 1);
	AddItems(mc, "talisman1", 1);
	AddItems(mc, "talisman2", 1);
	AddItems(mc, "talisman3", 1);
	AddItems(mc, "talisman4", 1);
	AddItems(mc, "talisman6", 1);
	AddItems(mc, "talisman7", 1);
	AddItems(mc, "talisman8", 1);

	EquipCharacterbyItem(mc, "spyglass3");
	EquipCharacterbyItem(mc, "pistol5");
 	EquipCharacterbyItem(mc, sEquipItem);
 	EquipCharacterbyItem(mc, "cirass4");
 	
 	SetHalfPerksToChar(mc, false);
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F32", 1);
}

string descF33 = "������ ������ +1";
void CalculateInfoDataF33()
{
 	ref mc;
	totalInfo = descF33;
	mc = GetMainCharacter();
 	mc.perks.FreePoints_self = sti(mc.perks.FreePoints_self) + 1;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F33", 1);
}

string descF34 = "����������� ������ +1";
void CalculateInfoDataF34()
{
 	ref mc;
	totalInfo = descF34;
	mc = GetMainCharacter();
 	mc.perks.FreePoints_ship = sti(mc.perks.FreePoints_ship) + 1;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F34", 1);
}

string descF35 = "��������� ������� +1";
void CalculateInfoDataF35()
{
 	ref mc;
	totalInfo = descF35;
	mc = GetMainCharacter();
 	mc.rank_exp = 99;
	ApplayNewSkill(mc, "", 1);
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F35", 1);
}

string descF36 = "������� ����� ��� �����";
void CalculateInfoDataF36()
{
	totalInfo = descF36;
 	LoginDummy();
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F36", 1);
}

string descF37 = "��������� ������� ������� 1";
void CalculateInfoDataF37()
{
	CreateSmallColonyCaiman();
	PChar.ColonyBuilding.Stage.FirstStage = "3";
	Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_7";
	PlayStereoSound("notebook");
	Log_SetStringToLog("����� ������������� ������� �� ������� ������ ������ ������� � �����. ����� ��������� ����� ������.");
	LAi_SetCitizenType(CharacterFromID("Builder"));
	LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Shore17", "goto", "goto13");
	PChar.quest.ColonyBuilding_2_1.win_condition.l1 = "location";
	PChar.quest.ColonyBuilding_2_1.win_condition.l1.location = "Shore17";
	PChar.quest.ColonyBuilding_2_1.win_condition = "ColonyBuilding_2_1";
	
	DoQuestReloadToLocation("Shore17","reload","reload1", "");
	setCharacterShipLocation(pchar, "Shore17");
	setWDMPointXZ("Shore17");
			
	totalInfo = descF37;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F37", 1);
}

string descF38 = "��������� ������� ������� 2 + ������";
void CalculateInfoDataF38()
{
	PChar.ColonyBuilding.Stage.SecondStage = "3";
	LAi_SetCitizenType(CharacterFromID("Builder"));
	LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
	Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_4";
	ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_town", "goto", "goto8");
	LAi_SetActorType(CharacterFromID("Builder"));
	LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 15.0, 1.0);
	PlayStereoSound("notebook");
	Log_SetStringToLog("����� ���������� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' ������ ������� � �����.");
	CreateModificyColonyCaiman();
	LAi_QuestDelay("LiveOfTheColonyUptade_1", 0.5);
	LAi_QuestDelay("CheckDefenceColonyUptade_1", 0.5);
	DoQuestReloadToLocation("Caiman_town","reload","reload1", "");
	setCharacterShipLocation(pchar, "Caiman_town");
	setWDMPointXZ("Caiman_town");
	
	PChar.quest.Store_build_1.win_condition.l1 = "location";
	PChar.quest.Store_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Store_build_1.win_condition = "Store_build_1";
	PChar.quest.Shipyard_build_1.win_condition.l1 = "location";
	PChar.quest.Shipyard_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Shipyard_build_1.win_condition = "Shipyard_build_1";
	PChar.quest.Tavern_build_1.win_condition.l1 = "location";
	PChar.quest.Tavern_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Tavern_build_1.win_condition = "Tavern_build_1";
	PChar.quest.Church_build_1.win_condition.l1 = "location";
	PChar.quest.Church_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Church_build_1.win_condition = "Church_build_1";
	PChar.quest.Bank_build_1.win_condition.l1 = "location";
	PChar.quest.Bank_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Bank_build_1.win_condition = "Bank_build_1";
	PChar.quest.HeadPort_build_1.win_condition.l1 = "location";
	PChar.quest.HeadPort_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.HeadPort_build_1.win_condition = "HeadPort_build_1";
	PChar.quest.StoreHouse_build_1.win_condition.l1 = "location";
	PChar.quest.StoreHouse_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.StoreHouse_build_1.win_condition = "StoreHouse_build_1";
	PChar.quest.StoreHouse_resize_1.win_condition.l1 = "location";
	PChar.quest.StoreHouse_resize_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.StoreHouse_resize_1.win_condition = "StoreHouse_resize_1";
	
	PChar.quest.Expidition_build_1.win_condition.l1 = "location";
	PChar.quest.Expidition_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Expidition_build_1.win_condition = "Expidition_build_1";
	
	PChar.quest.Plantation_build_1.win_condition.l1 = "location";
	PChar.quest.Plantation_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Plantation_build_1.win_condition = "Plantation_build_1";
	PChar.quest.Plantation_resize_1.win_condition.l1 = "location";
	PChar.quest.Plantation_resize_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.Plantation_resize_1.win_condition = "Plantation_resize_1";
	
	PChar.quest.GoldMine_build_1.win_condition.l1 = "location";
	PChar.quest.GoldMine_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.GoldMine_build_1.win_condition = "GoldMine_build_1";
	PChar.quest.SilverMine_build_1.win_condition.l1 = "location";
	PChar.quest.SilverMine_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.SilverMine_build_1.win_condition = "SilverMine_build_1";
	PChar.quest.IronMine_build_1.win_condition.l1 = "location";
	PChar.quest.IronMine_build_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.IronMine_build_1.win_condition = "IronMine_build_1";
	PChar.quest.GoldMine_resize_1.win_condition.l1 = "location";
	PChar.quest.GoldMine_resize_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.GoldMine_resize_1.win_condition = "GoldMine_resize_1";
	PChar.quest.SilverMine_resize_1.win_condition.l1 = "location";
	PChar.quest.SilverMine_resize_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.SilverMine_resize_1.win_condition = "SilverMine_resize_1";
	PChar.quest.IronMine_resize_1.win_condition.l1 = "location";
	PChar.quest.IronMine_resize_1.win_condition.l1.location = "Caiman_town";
	PChar.quest.IronMine_resize_1.win_condition = "IronMine_resize_1";
	
	totalInfo = descF38;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F38", 1);
}

string descF39 = "��������� �������� �������� �������";
void CalculateInfoDataF39()
{
	PChar.ColonyBuilding.Stage.SecondStage = "3";
	LAi_SetCitizenType(CharacterFromID("Builder"));
	LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
	Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_6";
	ChangeCharacterAddressGroup(CharacterFromID("Builder"), "LandGuardingPort", "goto", "goto1");
	LAi_SetActorType(CharacterFromID("Builder"));
	LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 15.0, 1.0);
	PlayStereoSound("notebook");
	Log_SetStringToLog("����� ���������� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' ������ ������� � �����.");
	CreateModificyColonyCaiman();
	LAi_QuestDelay("LiveOfTheColonyUptade_1", 0.5);
	LAi_QuestDelay("CheckDefenceColonyUptade_1", 0.5);
	DoQuestReloadToLocation("LandGuardingPort","reload","reload1", "");
	setCharacterShipLocation(pchar, "Caiman_town");
	setWDMPointXZ("Caiman_town");
	
	PChar.quest.Store_build_1.win_condition.l1 = "location";
	PChar.quest.Store_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Store_build_1.win_condition = "Store_build_1";
	PChar.quest.Shipyard_build_1.win_condition.l1 = "location";
	PChar.quest.Shipyard_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Shipyard_build_1.win_condition = "Shipyard_build_1";
	PChar.quest.Tavern_build_1.win_condition.l1 = "location";
	PChar.quest.Tavern_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Tavern_build_1.win_condition = "Tavern_build_1";
	PChar.quest.Church_build_1.win_condition.l1 = "location";
	PChar.quest.Church_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Church_build_1.win_condition = "Church_build_1";
	PChar.quest.Bank_build_1.win_condition.l1 = "location";
	PChar.quest.Bank_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Bank_build_1.win_condition = "Bank_build_1";
	PChar.quest.HeadPort_build_1.win_condition.l1 = "location";
	PChar.quest.HeadPort_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.HeadPort_build_1.win_condition = "HeadPort_build_1";
	PChar.quest.StoreHouse_build_1.win_condition.l1 = "location";
	PChar.quest.StoreHouse_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.StoreHouse_build_1.win_condition = "StoreHouse_build_1";
	PChar.quest.StoreHouse_resize_1.win_condition.l1 = "location";
	PChar.quest.StoreHouse_resize_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.StoreHouse_resize_1.win_condition = "StoreHouse_resize_1";
	
	PChar.quest.Expidition_build_1.win_condition.l1 = "location";
	PChar.quest.Expidition_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Expidition_build_1.win_condition = "Expidition_build_1";
	
	PChar.quest.Plantation_build_1.win_condition.l1 = "location";
	PChar.quest.Plantation_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Plantation_build_1.win_condition = "Plantation_build_1";
	PChar.quest.Plantation_resize_1.win_condition.l1 = "location";
	PChar.quest.Plantation_resize_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.Plantation_resize_1.win_condition = "Plantation_resize_1";
	
	PChar.quest.GoldMine_build_1.win_condition.l1 = "location";
	PChar.quest.GoldMine_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.GoldMine_build_1.win_condition = "GoldMine_build_1";
	PChar.quest.SilverMine_build_1.win_condition.l1 = "location";
	PChar.quest.SilverMine_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.SilverMine_build_1.win_condition = "SilverMine_build_1";
	PChar.quest.IronMine_build_1.win_condition.l1 = "location";
	PChar.quest.IronMine_build_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.IronMine_build_1.win_condition = "IronMine_build_1";
	PChar.quest.GoldMine_resize_1.win_condition.l1 = "location";
	PChar.quest.GoldMine_resize_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.GoldMine_resize_1.win_condition = "GoldMine_resize_1";
	PChar.quest.SilverMine_resize_1.win_condition.l1 = "location";
	PChar.quest.SilverMine_resize_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.SilverMine_resize_1.win_condition = "SilverMine_resize_1";
	PChar.quest.IronMine_resize_1.win_condition.l1 = "location";
	PChar.quest.IronMine_resize_1.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.IronMine_resize_1.win_condition = "IronMine_resize_1";
	
	PChar.quest.ColonyFortBuilding_6.win_condition.l1 = "location";
	PChar.quest.ColonyFortBuilding_6.win_condition.l1.location = "LandGuardingPort";
	PChar.quest.ColonyFortBuilding_6.win_condition = "ColonyFortBuilding_6";
	
	totalInfo = descF39;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F39", 1);
}

string descF40 = "������ ������������ �������";
void CalculateInfoDataF40()
{
	totalInfo = descF40;
 	ref mc;
	mc = GetMainCharacter();
//	mc.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, true, mc);
	mc.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, mc);
//	mc.Ship.Type = GenerateShipExt(SHIP_FRIGATEQUEEN, true, mc);
	SetBaseShipData(mc);
	int iShip = pchar.ship.type;
	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(mc);
	AddCrewMorale(mc, 100);
	ChangeCrewExp(mc, "Sailors", 100);
	ChangeCrewExp(mc, "Cannoners", 100);
	ChangeCrewExp(mc, "Soldiers", 100);

	SetCharacterGoods(mc, GOOD_BALLS, 1000);
	SetCharacterGoods(mc, GOOD_GRAPES, 1000);
	SetCharacterGoods(mc, GOOD_KNIPPELS, 1000);
	SetCharacterGoods(mc, GOOD_BOMBS, 1000);;
	SetCharacterGoods(mc, GOOD_FOOD, 2000);
	SetCharacterGoods(mc, GOOD_MEDICAMENT, 1000);
	SetCharacterGoods(mc, GOOD_POWDER, 2000);
	SetCharacterGoods(mc, GOOD_WEAPON, 300);
	ref refBaseShip = GetRealShip(iShip);
	refBaseShip.WindAgainstSpeed = 30.0;
	refBaseShip.SpeedRate = 200.0;
	refBaseShip.TurnRate = 90.0;
	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F40", 1);
}

string descF41 = "���� ���� ����";
void CalculateInfoDataF41()
{
	totalInfo = descF41;
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // ����������
		// ������� ������� ����� �������
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // ��� ����
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// �������� �������� �� �������, � ��� ��� ������, ����� �� ���������?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	SetFormatedText("INFO_TEXT", totalInfo);
	Statistic_AddValue(PChar, "Cheats.F40", 1);
}

string descF42 = "�������� ����������� ������"; // �������� ����������� ������ - ����-���, ��� �������� - ������� � ������.��� ������, ������ �������� ���� ������� �� ����� �����
void CalculateInfoDataF42()
{
	totalInfo = descF42;
	int i, j, idx;
	float fMaxCost;

	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1;
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight))
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				}
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	SetFormatedText("INFO_TEXT", totalInfo);
	Statistic_AddValue(PChar, "Cheats.F40", 1);
}

string descF43 = "���������� ������� ����";
void CalculateInfoDataF43()
{
	totalInfo = descF43;
	
	Log_TestInfo("start GoldFleet");
	AddTemplRumour("Start_GoldFleet", id_counter+1);
	string sQuest = "EndOfGoldFleet";
	SetTimerCondition(sQuest, 0, 0, 29, false);
	pchar.quest.(sQuest).win_condition = "EndOfGoldFleet";
	pchar.quest.(sQuest).function= "EndOfGoldFleet";
	GoldFleet();
	int pbx = worldMap.islands.PortoBello.PortoBello_town.position.x;
	int pbz = worldMap.islands.PortoBello.PortoBello_town.position.z;
	Map_CreateTraderXZ(pbx, pbz, -858.089, 897.072, "Head_of_Gold_Squadron", 22);
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F43", 1);
}

string descF44 = "������� �������";
void CalculateInfoDataF44()
{
	totalInfo = descF44;
 	
	totalInfo = totalInfo + NewStr() +  + "pchar.Ship.Ang.y _ " + stf(pchar.Ship.Ang.y) + NewStr() + "pchar.Ship.Pos.x _ " + stf(pchar.Ship.Pos.x) + NewStr() + "pchar.Ship.Pos.z _ " + stf(pchar.Ship.Pos.z) + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	trace("reload,reload_fort1," + cos(-stf(pchar.Ship.Ang.y)) + ",0,"	+ sin(-stf(pchar.Ship.Ang.y)) + ",0,1,0," + sin(stf(pchar.Ship.Ang.y)) + ",0," + cos(stf(pchar.Ship.Ang.y)) + "," + stf(pchar.Ship.Pos.x) + ",1.364242E-12," + stf(pchar.Ship.Pos.z) + ",1,0,0,0,0,0,0,0,0");	
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F44", 1);
}

string descF45 = "���������� �������: ��������, �������, �������, ��������, �����";
void CalculateInfoDataF45()
{
	totalInfo = descF45;
	
    InitItems();
    ShipsInit();
    IslandsInit();
    LocationInit();
    ColoniesInit();
    CreateColonyCommanders();
	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F45", 1);
}

string descF46 = "������� ������ �� ����";
void CalculateInfoDataF46()
{
	float locx0, locy0, locz0, locAy0;
	GetCharacterPos(pchar, &locx0, &locy0, &locz0);
	GetCharacterAy(pchar, &locAy0);

	totalInfo = descF46;
  
 	totalInfo = totalInfo + "locX: " + locx0 + " | locY: " + locy0 + " | locZ: " + locz0 + " | locAy: " + locAy0 + "������� ���������� �������!";

	trace("reload,reload1," + cos(-stf(locAy0)) + ",0," + sin(-stf(locAy0)) + ",0,1,0," + sin(stf(locAy0)) + ",0," + cos(stf(locAy0)) + "," + locx0 + "," + locy0 + "," + locz0 + ",1,0,0,0,0,0,0,0,0,");
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F46", 1);
}

string descF47 = "������ 20 �������� � 20 �������";
void CalculateInfoDataF47()
{
	totalInfo = descF47;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	AddItems(pchar, "chest_ammo", 5);
	AddItems(pchar, "chest_treasure", 5);
	AddItems(pchar, "chest_quest", 5);
	AddItems(pchar, "chest_craftsmans", 5);
	AddItems(pchar, "lockpick", 20);
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F47", 1);
}

string descF48 = "��������� ��� �������� � ���� � ����� ����������";
void CalculateInfoDataF48()
{
	totalInfo = descF48;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	float locx, locy, locz;
	aref aroot, arcur;
	string attrname;
	makearef(aroot,loadedLocation.reload);
	int num = GetAttributesNum(aroot);
	for(int i=0; i<num; i++)
	{
		arcur = GetAttributeN(aroot,i);
		attrname = GetAttributeName(arcur);
		//Log_info(attrname);
		DeleteAttribute(loadedLocation, "reload."+attrname+".disable");
	}
	
	chrDisableReloadToLocation = false;
	InterfaceStates.DisFastTravel = false
	bDisableCharacterMenu = false;
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F48", 1);
}

string descF49 = "��������� ������� � ��������� ������ ����";
void CalculateInfoDataF49()
{
	totalInfo = descF49;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	pchar.GiantEvilSkeleton = true;
	pchar.MalteseInfo = true;
	pchar.MalteseOrderOnHold = true;
	pchar.MalteseOrder = true;
	BuildMalteseOrder("");
	DoQuestReloadToLocation("Reefs_Chapter","reload","reload1","");
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F49", 1);
}

string descF50 = "��� ����������";
void CalculateInfoDataF50()
{
	totalInfo = descF50;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F50", 1);
}

string descF51 = "��� ����������";
void CalculateInfoDataF51()
{
	totalInfo = descF51;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F51", 1);
}

string descF52 = "��� ����������";
void CalculateInfoDataF52()
{
	totalInfo = descF52;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F52", 1);
}

string descF53 = "��� ����������";
void CalculateInfoDataF53()
{
	totalInfo = descF53;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F53", 1);
}

string descF54 = "��� ����������";
void CalculateInfoDataF54()
{
	totalInfo = descF54;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F54", 1);
}

string descF55 = "��� ����������";
void CalculateInfoDataF55()
{
	totalInfo = descF55;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F55", 1);
}

string descF56 = "��� ����������";
void CalculateInfoDataF56()
{
	totalInfo = descF56;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F56", 1);
}

string descF57 = "��� ����������";
void CalculateInfoDataF57()
{
	totalInfo = descF57;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F57", 1);
}

string descF58 = "��� ����������";
void CalculateInfoDataF58()
{
	totalInfo = descF58;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F58", 1);
}

string descF59 = "��� ����������";
void CalculateInfoDataF59()
{
	totalInfo = descF59;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F59", 1);
}

string descF60 = "��� ����������";
void CalculateInfoDataF60()
{
	totalInfo = descF60;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F60", 1);
}

string descF61 = "��� ����������";
void CalculateInfoDataF61()
{
	totalInfo = descF61;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F61", 1);
}

string descF62 = "��� ����������";
void CalculateInfoDataF62()
{
	totalInfo = descF62;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F62", 1);
}

string descF63 = "��� ����������";
void CalculateInfoDataF63()
{
	totalInfo = descF63;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F63", 1);
}

string descF64 = "��� ����������";
void CalculateInfoDataF64()
{
	totalInfo = descF64;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F64", 1);
}

string descF65 = "��� ����������";
void CalculateInfoDataF65()
{
	totalInfo = descF65;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F65", 1);
}

string descF66 = "��� ����������";
void CalculateInfoDataF66()
{
	totalInfo = descF66;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F66", 1);
}

string descF67 = "��� ����������";
void CalculateInfoDataF67()
{
	totalInfo = descF67;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F67", 1);
}

string descF68 = "��� ����������";
void CalculateInfoDataF68()
{
	totalInfo = descF68;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F68", 1);
}

string descF69 = "��� ����������";
void CalculateInfoDataF69()
{
	totalInfo = descF69;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F69", 1);
}

string descF70 = "��� ����������";
void CalculateInfoDataF70()
{
	totalInfo = descF70;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F70", 1);
}

string descF71 = "��� ����������";
void CalculateInfoDataF71()
{
	totalInfo = descF71;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F71", 1);
}

string descF72 = "��� ����������";
void CalculateInfoDataF72()
{
	totalInfo = descF72;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F72", 1);
}

string descF73 = "��� ����������";
void CalculateInfoDataF73()
{
	totalInfo = descF73;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F73", 1);
}

string descF74 = "��� ����������";
void CalculateInfoDataF74()
{
	totalInfo = descF74;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F74", 1);
}

string descF75 = "��� ����������";
void CalculateInfoDataF75()
{
	totalInfo = descF75;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F75", 1);
}

string descF76 = "��� ����������";
void CalculateInfoDataF76()
{
	totalInfo = descF76;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F76", 1);
}

string descF77 = "��� ����������";
void CalculateInfoDataF77()
{
	totalInfo = descF77;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F77", 1);
}

string descF78 = "��� ����������";
void CalculateInfoDataF78()
{
	totalInfo = descF78;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F78", 1);
}

string descF79 = "��� ����������";
void CalculateInfoDataF79()
{
	totalInfo = descF79;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F79", 1);
}

string descF80 = "��� ����������";
void CalculateInfoDataF80()
{
	totalInfo = descF80;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F80", 1);
}

string descF81 = "��� ����������";
void CalculateInfoDataF81()
{
	totalInfo = descF81;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F81", 1);
}

string descF82 = "��� ����������";
void CalculateInfoDataF82()
{
	totalInfo = descF82;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F82", 1);
}

string descF83 = "��� ����������";
void CalculateInfoDataF83()
{
	totalInfo = descF83;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F83", 1);
}

string descF84 = "��� ����������";
void CalculateInfoDataF84()
{
	totalInfo = descF84;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F84", 1);
}

string descF85 = "��� ����������";
void CalculateInfoDataF85()
{
	totalInfo = descF85;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F85", 1);
}

string descF86 = "��� ����������";
void CalculateInfoDataF86()
{
	totalInfo = descF86;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F86", 1);
}

string descF87 = "��� ����������";
void CalculateInfoDataF87()
{
	totalInfo = descF87;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F87", 1);
}

string descF88 = "��� ����������";
void CalculateInfoDataF88()
{
	totalInfo = descF88;
 	
	totalInfo = totalInfo + NewStr() + NewStr() + "������� ���������� �������!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	
	// ���������� �� �����
	Statistic_AddValue(PChar, "Cheats.F88", 1);
}

//������� "����� ��� �����"
void LoginDummy()
{
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	
	//������ �����
	ref sld = GetCharacter(NPC_GenerateCharacter("DummyCharacter", "mictlantecuhtli", "man", "man", 50, PIRATE, 0, true));
	sld.name = "�������";
	sld.lastname = "���������";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	//����������
    // FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "pistol5", 99999); 	// ������� 		(��)
	
    // FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "", 99999); 	// ������� 		(��)
    // FantomMakeCoolFighter(sld, 100, 100, 100, "blade32", "", 99999); 	// ��������		(��)
    // FantomMakeCoolFighter(sld, 100, 100, 100, "katar", 	"", 99999); 	// �����		(��)
    // FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "", 99999); 	// ����������	(��)
    FantomMakeCoolFighter(sld, 100, 100, 100, "blade28", "", 99999); 		// �����		(��)
	//���������� SPECIAL
	SetSPECIAL(sld, 10,10,10,10,10,10,10); // SPECIAL (����, ����������, ������������, ���������, �����������, �������, �����)
	//���������� ��
	LAi_SetHP(sld,9999,9999);
	
	//���������� ���
	LAi_SetWarriorType(sld);
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("teno_monsters_group", LAI_GROUP_PLAYER, true);
	
	//�����
	sld.perks.list.BasicDefense = "1";
	sld.perks.list.AdvancedDefense = "1";
	sld.perks.list.CriticalHit = "1";
	sld.perks.list.Ciras = "1";
	sld.perks.list.SwordplayProfessional = "1";
	sld.perks.list.Grus = "1";
	sld.perks.list.Rush = "1";
	sld.perks.list.Tireless = "1";
	sld.perks.list.HardHitter = "1";
	sld.perks.list.BladeDancer = "1";
	sld.perks.list.Sliding = "1";
	sld.perks.list.Gunman = "1";
	sld.perks.list.GunProfessional = "1";
	sld.perks.list.IronWill = "1";
	sld.perks.list.Medic = "1";
	sld.perks.list.HPPlus = "1";
	sld.perks.list.EnergyPlus = "1";
	sld.perks.list.Trustworthy = "1";
	sld.perks.list.ShipEscape = "1";
	
	sld.perks.list.FlagPir = "1";
	sld.perks.list.FlagEng = "1";
	sld.perks.list.FlagFra = "1";
	sld.perks.list.FlagSpa = "1";
	sld.perks.list.FlagHol = "1";
	sld.perks.list.FastReload = "1";
	sld.perks.list.ImmediateReload = "1";
	sld.perks.list.HullDamageUp = "1";
	sld.perks.list.SailsDamageUp = "1";
	sld.perks.list.CrewDamageUp = "1";
	sld.perks.list.CriticalShoot = "1";
	sld.perks.list.LongRangeShoot = "1";
	sld.perks.list.CannonProfessional = "1";
	sld.perks.list.LongRangeGrappling = "1";
	sld.perks.list.MusketsShoot = "1";
	sld.perks.list.GrapplingProfessional = "1";
	sld.perks.list.BasicBattleState = "1";
	sld.perks.list.AdvancedBattleState = "1";
	sld.perks.list.ShipDefenseProfessional = "1";
	sld.perks.list.LightRepair = "1";
	sld.perks.list.InstantRepair = "1";
	sld.perks.list.ShipSpeedUp = "1";
	sld.perks.list.ShipTurnRateUp = "1";
	sld.perks.list.StormProfessional = "1";
	sld.perks.list.Turn180 = "1";
	sld.perks.list.SailingProfessional = "1";
	sld.perks.list.Brander = "1";
	sld.perks.list.Troopers = "1";
	sld.perks.list.BasicCommerce = "1";
	sld.perks.list.AdvancedCommerce = "1";
	sld.perks.list.Carpenter = "1";
	sld.perks.list.Builder = "1";
	sld.perks.list.WindCatcher = "1";
	sld.perks.list.SailsMan = "1";
	sld.perks.list.Doctor1 = "1";
	sld.perks.list.Doctor2 = "1";
	sld.perks.list.EmergentSurgeon = "1";
	sld.perks.list.ByWorker = "1";
	sld.perks.list.ByWorker2 = "1";
	
	//���������� �� � ��
	SetSelfSkill(sld, 100, 100, 100, 100, 100); //�����, �������, ������, ��������, �����
	SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100); // ���������, ��������, ��������, �����, ���������, ������, �������, ������, ����������
}

void ReloadByStr()
{
	// ������ ������
	string loc = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 0));
	string grp = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 1));
	string ltr = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 2));
	
	if (loc=="�����")
	{
		grp = GetSubStringByNum(GameInterface.reload_edit.str, 1);
		for(int j = 0; j < GOODS_QUANTITY; j++)
		{
			if (grp == XI_ConvertString(Goods[j].name))
			{
				string good = Goods[j].name;
				if (sti(ltr)>-1 && sti(ltr) < 999999) pchar.Ship.Cargo.Goods.(good) = sti(ltr);
				else break;
				Log_info("����� "+XI_ConvertString(good)+" ������� � ���������� "+ltr);
				break;
			}
		}
	}
	if (sti(loc) > 0 && sti(loc) < 13)
	{
		if (sti(grp) > 0 && sti(grp) < 32)
		{
			if (sti(ltr) > -1 && sti(ltr) < 25)
			{
				Environment.date.month = sti(loc);
				Environment.date.day = sti(grp);
				SetCurrentTime(sti(ltr),0);
				DoQuestReloadToLocation(loadedLocation.id, "reload", "reload1", "");
				return;
			}
		}
	}
    int i = FindLocation(loc);
    if (i != -1)
    {
        if(CheckAttribute(&locations[i],"fastreload"))
        {
			if (GetCityFrom_Sea(locations[i].fastreload) != "")
		    {
		        setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		        setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		    }
	    }
	    else
	    {
	        if (locations[i].type == "seashore" || locations[i].type == "mayak")
	        {
	            setCharacterShipLocation(pchar, loc));
		        setWDMPointXZ(loc);
	        }
	    }
	    DoQuestReloadToLocation(loc, grp, ltr, "");
	    Log_Info(loc);
		// ���������� �� �����
		Statistic_AddValue(PChar, "Cheats.ReloadByStr", 1);
    }
    else
    {
        Log_Info("��� �������");
    }
}

void XI_SetScroller(float pos)
{
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"QUESTSCROLL",pos);
}

void SetScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	XI_SetScroller(pos);
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, newPos);
}

void ProcScrollChange()
{
	int changeNum = GetEventData();
	if(changeNum==0) return;
	string controlNode = "";
	if( GetSelectable("INFO_TEXT") ) controlNode = "INFO_TEXT";

	if(controlNode!="")
	{
		if(changeNum>0) {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_DOWNSTEP);
		} else {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_UPSTEP);
		}
	}
}

void GetRealCoordsObjects()
{
	trace("---------");
	trace("Barbados (island)					: " + Map_GetRealCoordX(946.0062) + " " + Map_GetRealCoordZ(-486.9014));
	trace("��������� 							: " + Map_GetRealCoordX(903.6217) + " " + Map_GetRealCoordZ(-522.2799));
	trace("Mayak2 (���� ���������)				: " + Map_GetRealCoordX(918.619) + " " + Map_GetRealCoordZ(-506.827));
	trace("Shore4 (��� ��������)				: " + Map_GetRealCoordX(919.808) + " " + Map_GetRealCoordZ(-448.061));
	trace("Shore5 (��� ������ �����)			: " + Map_GetRealCoordX(983.787) + " " + Map_GetRealCoordZ(-518.14));	
	trace("---------");
	trace("Antigua (island)						: " + Map_GetRealCoordX(903.9222) + " " + Map_GetRealCoordZ(109.0605));
	trace("����-����� 							: " + Map_GetRealCoordX(852.4083) + " " + Map_GetRealCoordZ(128.9092));
	trace("Shore1 (��� ���)						: " + Map_GetRealCoordX(880.892) + " " + Map_GetRealCoordZ(148.897));
	trace("Shore2 (����� ��������)				: " + Map_GetRealCoordX(931.028) + " " + Map_GetRealCoordZ(74.5353));
	trace("---------");
	trace("Curacao (island) 					: " + Map_GetRealCoordX(383.4142) + " " + Map_GetRealCoordZ(-691.11));
	trace("����������� 							: " + Map_GetRealCoordX(396.1) + " " + Map_GetRealCoordZ(-722.8));	
	trace("Shore22 (��������� �����)			: " + Map_GetRealCoordX(354.604) + " " + Map_GetRealCoordZ(-678.54));
	trace("Shore23 (��� ������������)			: " + Map_GetRealCoordX(347.313) + " " + Map_GetRealCoordZ(-705.112));
	trace("Shore24 (����� ����� ��������������)	: " + Map_GetRealCoordX(455.427) + " " + Map_GetRealCoordZ(-740.655));
	trace("---------");
	trace("SentMartin (island)					: " + Map_GetRealCoordX(921.559) + " " + Map_GetRealCoordZ(523.596));
	trace("������ 								: " + Map_GetRealCoordX(900.0994) + " " + Map_GetRealCoordZ(501.6531));	
	trace("Shore40 (����� ��������)				: " + Map_GetRealCoordX(924.442) + " " + Map_GetRealCoordZ(554.385));	
	trace("Shore41 (����� ���������� �����)		: " + Map_GetRealCoordX(898.877) + " " + Map_GetRealCoordZ(522.703));	
	trace("---------");
	trace("Guadeloupe (island)					: " + Map_GetRealCoordX(537.114) + " " + Map_GetRealCoordZ(-25.3853));	
	trace("���-��� 								: " + Map_GetRealCoordX(462.2107) + " " + Map_GetRealCoordZ(-73.0837));		
	trace("Mayak4 (���� ���������)				: " + Map_GetRealCoordX(465.076) + " " + Map_GetRealCoordZ(-38.9423));		
	trace("Shore28 (����� ���� �'�)				: " + Map_GetRealCoordX(536.636) + " " + Map_GetRealCoordZ(26.1279));		
	trace("Shore29 (���� �������)				: " + Map_GetRealCoordX(507.669) + " " + Map_GetRealCoordZ(-75.4176));		
	trace("Shore30 (����� ���� ���)				: " + Map_GetRealCoordX(549.807) + " " + Map_GetRealCoordZ(-69.7107));		
	trace("Shore31 (��� �����������)			: " + Map_GetRealCoordX(589.889) + " " + Map_GetRealCoordZ(-65.0601));		
	trace("---------");
	trace("Martinique (island) 					: " + Map_GetRealCoordX(538.524) + " " + Map_GetRealCoordZ(-385.567));		
	trace("����-��-����� 						: " + Map_GetRealCoordX(513.51) + " " + Map_GetRealCoordZ(-397.645));		
	trace("��-������� 							: " + Map_GetRealCoordX(559.008) + " " + Map_GetRealCoordZ(-368.16));		
	trace("Shore38 (���� ��������)				: " + Map_GetRealCoordX(481.181) + " " + Map_GetRealCoordZ(-340.832));		
	trace("Shore39 (����� �� �����)				: " + Map_GetRealCoordX(557.181) + " " + Map_GetRealCoordZ(-422.987));		
	trace("---------");
	trace("Bermudes (island)					: " + Map_GetRealCoordX(920.738) + " " + Map_GetRealCoordZ(920.767));		
	trace("��������� ��������� 					: " + Map_GetRealCoordX(931.059) + " " + Map_GetRealCoordZ(928.281));		
	trace("Shore3 (����� ����)					: " + Map_GetRealCoordX(915.745) + " " + Map_GetRealCoordZ(966.469));		
	trace("Shore_ship1 (����� ��������� ������) : " + Map_GetRealCoordX(968.947) + " " + Map_GetRealCoordZ(923.636));		
	trace("---------");
	trace("Maracaibo (areal) 					: " + Map_GetRealCoordX(178.51) + " " + Map_GetRealCoordZ(-870.37));		
	trace("��������� 							: " + Map_GetRealCoordX(134.82) + " " + Map_GetRealCoordZ(-939.65));		
	trace("Shore37 (����� �������)				: " + Map_GetRealCoordX(140.753) + " " + Map_GetRealCoordZ(-828.99));		
	trace("Shore_ship3 (��� ����������� ������)	: " + Map_GetRealCoordX(198.162) + " " + Map_GetRealCoordZ(-994.035));		
	trace("---------");
	trace("Beliz (areal) 						: " + Map_GetRealCoordX(-896.084) + " " + Map_GetRealCoordZ(230.227));		
	trace("Shore_ship2 (����� ������)			: " + Map_GetRealCoordX(-1022.94) + " " + Map_GetRealCoordZ(629.355));		
	trace("Shore6 (��� ������)					: " + Map_GetRealCoordX(-909.655) + " " + Map_GetRealCoordZ(629.079));		
	trace("Shore7 (����� ��������)				: " + Map_GetRealCoordX(-915.581) + " " + Map_GetRealCoordZ(409.002));		
	trace("Shore8 (����� ��������)				: " + Map_GetRealCoordX(-963.489) + " " + Map_GetRealCoordZ(281.628));		
	trace("����� 								: " + Map_GetRealCoordX(-978.396) + " " + Map_GetRealCoordZ(158.751));		
	trace("Shore9 (����� �������)				: " + Map_GetRealCoordX(-1017.2) + " " + Map_GetRealCoordZ(-33.7293));		
	trace("Shore10 (������ ���������)			: " + Map_GetRealCoordX(-818.198) + " " + Map_GetRealCoordZ(-177.208));		
	trace("---------");
	trace("Jamaica (island)						: " + Map_GetRealCoordX(-298.0) + " " + Map_GetRealCoordZ(-128.0));		
	trace("����-����� 							: " + Map_GetRealCoordX(-250.157) + " " + Map_GetRealCoordZ(-150.839));		
	trace("Shore35 (��� ������)					: " + Map_GetRealCoordX(-446.951) + " " + Map_GetRealCoordZ(-107.118));			
	trace("Shore36 (����� ��������)				: " + Map_GetRealCoordX(-281.543) + " " + Map_GetRealCoordZ(-164.245));			
	trace("Mayak3 (���� ���� �����)				: " + Map_GetRealCoordX(-224.127) + " " + Map_GetRealCoordZ(-163.435));			
	trace("---------");
	trace("PuertoRico (island) 					: " + Map_GetRealCoordX(506.489) + " " + Map_GetRealCoordZ(460.815));			
	trace("���-���� 							: " + Map_GetRealCoordX(528.645) + " " + Map_GetRealCoordZ(484.18));				
	trace("Shore44 (����� ���������)			: " + Map_GetRealCoordX(392.82) + " " + Map_GetRealCoordZ(501.808));				
	trace("Shore45 (���� �������)				: " + Map_GetRealCoordX(602.049) + " " + Map_GetRealCoordZ(458.322));				
	trace("---------");
	trace("Cuba1 (areal) 						: " + Map_GetRealCoordX(-358.027) + " " + Map_GetRealCoordZ(819.223));				
	trace("�������� 							: " + Map_GetRealCoordX(-339.796) + " " + Map_GetRealCoordZ(771.839));					
	trace("������-�������� 						: " + Map_GetRealCoordX(-282.032) + " " + Map_GetRealCoordZ(839.056));					
	trace("Shore11 (��� ��������)				: " + Map_GetRealCoordX(-386.907) + " " + Map_GetRealCoordZ(883.044));				
	trace("Shore12 (����� ���� �����)			: " + Map_GetRealCoordX(-468.486) + " " + Map_GetRealCoordZ(838.497));				
	trace("Mayak9 (���� ��������)				: " + Map_GetRealCoordX(-333.295) + " " + Map_GetRealCoordZ(723.486));				
	trace("---------");
	trace("Cuba2 (areal) 						: " + Map_GetRealCoordX(-640.61) + " " + Map_GetRealCoordZ(870.058));					
	trace("������ 								: " + Map_GetRealCoordX(-663.685) + " " + Map_GetRealCoordZ(913.862));					
	trace("Shore13 (����� ��������)				: " + Map_GetRealCoordX(-613.56) + " " + Map_GetRealCoordZ(886.009));				
	trace("Shore14 (����� ��������)				: " + Map_GetRealCoordX(-653.269) + " " + Map_GetRealCoordZ(871.013));				
	trace("Shore15 (��� ��� �������)			: " + Map_GetRealCoordX(-715.129) + " " + Map_GetRealCoordZ(797.212));				
	trace("Mayak10 (���� ������)				: " + Map_GetRealCoordX(-647.18) + " " + Map_GetRealCoordZ(925.046));				
	trace("---------");
	trace("Tortuga (island) 					: " + Map_GetRealCoordX(102.328) + " " + Map_GetRealCoordZ(852.912));				
	trace("������� 								: " + Map_GetRealCoordX(116.875) + " " + Map_GetRealCoordZ(817.942));				
	trace("Shore58 (���� ���� ����)				: " + Map_GetRealCoordX(131.064) + " " + Map_GetRealCoordZ(849.44));				
	trace("Mayak6 (���� �������)				: " + Map_GetRealCoordX(103.23) + " " + Map_GetRealCoordZ(812.356));				
	trace("---------");
	trace("Trinidad (island)					: " + Map_GetRealCoordX(889.76) + " " + Map_GetRealCoordZ(-774.746));				
	trace("����-��-����� 						: " + Map_GetRealCoordX(848.282) + " " + Map_GetRealCoordZ(-822.588));				
	trace("Shore59 (����� ��������)				: " + Map_GetRealCoordX(937.322) + " " + Map_GetRealCoordZ(-737.478));				
	trace("Shore60 (��� ������)					: " + Map_GetRealCoordX(906.25) + " " + Map_GetRealCoordZ(-757.928));				
	trace("Mayak1 (���� ��������� � ������)		: " + Map_GetRealCoordX(821.24) + " " + Map_GetRealCoordZ(-847.69));				
	trace("---------");
	trace("Nevis (island)						: " + Map_GetRealCoordX(681.595) + " " + Map_GetRealCoordZ(256.013));				
	trace("���������� 							: " + Map_GetRealCoordX(658.918) + " " + Map_GetRealCoordZ(241.972));				
	trace("Shore42 (����� �������)				: " + Map_GetRealCoordX(690.047) + " " + Map_GetRealCoordZ(291.621));					
	trace("Shore43 (���� ���)					: " + Map_GetRealCoordX(684.026) + " " + Map_GetRealCoordZ(212.793));					
	trace("Mayak5 (���� ������)					: " + Map_GetRealCoordX(663.418) + " " + Map_GetRealCoordZ(228.281));					
	trace("---------");
	trace("Hispaniola1 (areal) 					: " + Map_GetRealCoordX(198.977) + " " + Map_GetRealCoordZ(588.696));					
	trace("�����-������� 						: " + Map_GetRealCoordX(198.683) + " " + Map_GetRealCoordZ(547.97));					
	trace("��-���� 								: " + Map_GetRealCoordX(166.708) + " " + Map_GetRealCoordZ(662.952));					
	trace("Shore32 (��� �������)				: " + Map_GetRealCoordX(130.591) + " " + Map_GetRealCoordZ(682.362));						
	trace("Shore33 (����� ������)				: " + Map_GetRealCoordX(229.081) + " " + Map_GetRealCoordZ(593.727));						
	trace("Mayak8 (���� �����-�������)			: " + Map_GetRealCoordX(168.314) + " " + Map_GetRealCoordZ(520.218));						
	trace("---------");
	trace("Hispaniola2 (areal) 					: " + Map_GetRealCoordX(-47.1762) + " " + Map_GetRealCoordZ(625.596));					
	trace("����-�-����� 						: " + Map_GetRealCoordX(22.521) + " " + Map_GetRealCoordZ(592.233));					
	trace("Shore34 (����� ������)				: " + Map_GetRealCoordX(0.999614) + " " + Map_GetRealCoordZ(643.122));							
	trace("Mayak7 (���� ����-�-������)			: " + Map_GetRealCoordX(-14.9756) + " " + Map_GetRealCoordZ(606.258));						
	trace("---------");
	trace("Dominica 							: " + Map_GetRealCoordX(783.057) + " " + Map_GetRealCoordZ(-256.833));					
	trace("Shore27 (��� ����� ���)				: " + Map_GetRealCoordX(779.89) + " " + Map_GetRealCoordZ(-295.002));								
	trace("Shore26 (���� ���� ����)				: " + Map_GetRealCoordX(803.577) + " " + Map_GetRealCoordZ(-252.617));								
	trace("---------");
	trace("����� 								: " + Map_GetRealCoordX(443.257) + " " + Map_GetRealCoordZ(939.102));						
	trace("Shore57 (����� �����)				: " + Map_GetRealCoordX(434.944) + " " + Map_GetRealCoordZ(923.524));								
	trace("Shore56 (����� ��������)				: " + Map_GetRealCoordX(444.298) + " " + Map_GetRealCoordZ(954.975));								
	trace("---------");
	trace("������ 								: " + Map_GetRealCoordX(-489.6) + " " + Map_GetRealCoordZ(362.455));						
	trace("Shore17 (����� ����������)			: " + Map_GetRealCoordX(-505.038) + " " + Map_GetRealCoordZ(348.115));									
	trace("Shore16 (��������� ����)				: " + Map_GetRealCoordX(-449.837) + " " + Map_GetRealCoordZ(366.308));
	trace("---------");
	trace("Panama (areal) 						: " + Map_GetRealCoordX(-395.198) + " " + Map_GetRealCoordZ(-972.801));							
	trace("������ 								: " + Map_GetRealCoordX(-389.965) + " " + Map_GetRealCoordZ(-949.118));							
	trace("Shore63 (����� ��� ������) 			: " + Map_GetRealCoordX(-328.166) + " " + Map_GetRealCoordZ(-1023.72));
	trace("---------");
	trace("PortoBello (areal) 					: " + Map_GetRealCoordX(-435.73) + " " + Map_GetRealCoordZ(-895.763));							
	trace("�����-����� 							: " + Map_GetRealCoordX(-427.183) + " " + Map_GetRealCoordZ(-907.277));
	trace("Shore46 (������ ������)				: " + Map_GetRealCoordX(-627.474) + " " + Map_GetRealCoordZ(-940.853));
	trace("Shore47 (����� ��������)				: " + Map_GetRealCoordX(-486.49) + " " + Map_GetRealCoordZ(-976.966));
	trace("Shore48 (���������� �����)			: " + Map_GetRealCoordX(-279.316) + " " + Map_GetRealCoordZ(-1005.49));
	trace("---------");
	trace("Cartahena (areal) 					: " + Map_GetRealCoordX(-51.2104) + " " + Map_GetRealCoordZ(-851.77));								
	trace("��������� 							: " + Map_GetRealCoordX(-26.7669) + " " + Map_GetRealCoordZ(-872.535));								
	trace("Shore25 (����� ��������)				: " + Map_GetRealCoordX(-115.589) + " " + Map_GetRealCoordZ(-937.387));
	trace("Mayak11 (���� ���������)				: " + Map_GetRealCoordX(-65.6347) + " " + Map_GetRealCoordZ(-842.072));
	trace("---------");
	trace("Caracas (areal) 						: " + Map_GetRealCoordX(435.126) + " " + Map_GetRealCoordZ(-936.197));								
	trace("������� 								: " + Map_GetRealCoordX(440.684) + " " + Map_GetRealCoordZ(-960.339));
	trace("Shore21 (��� �����)					: " + Map_GetRealCoordX(410.688) + " " + Map_GetRealCoordZ(-913.531));
	trace("---------");
	trace("Cumana (areal) 						: " + Map_GetRealCoordX(767.999) + " " + Map_GetRealCoordZ(-936.266));								
	trace("������ 								: " + Map_GetRealCoordX(691.343) + " " + Map_GetRealCoordZ(-896.619));								
	trace("Shore20 (���� ��� �����)				: " + Map_GetRealCoordX(574.327) + " " + Map_GetRealCoordZ(-929.042));
	trace("Shore19 (����� ��������)				: " + Map_GetRealCoordX(768.622) + " " + Map_GetRealCoordZ(-914.469));
	trace("Shore18 (����� ���� �� �� ������)	: " + Map_GetRealCoordX(924.423) + " " + Map_GetRealCoordZ(-969.921));
	trace("---------");
	trace("SantaCatalina (areal) 				: " + Map_GetRealCoordX(-742.269) + " " + Map_GetRealCoordZ(-563.205));									
	trace("�����-�������� 						: " + Map_GetRealCoordX(-769.375) + " " + Map_GetRealCoordZ(-537.051));
	trace("Shore53 (����� ��������)				: " + Map_GetRealCoordX(-792.718) + " " + Map_GetRealCoordZ(-331.728));
	trace("Shore54 (��� ������)					: " + Map_GetRealCoordX(-760.343) + " " + Map_GetRealCoordZ(-484.106));
	trace("Shore55 (����� ��� ���� ���� �����)	: " + Map_GetRealCoordX(-736.763) + " " + Map_GetRealCoordZ(-756.295));
	trace("---------");
	trace("���									: " + Map_GetRealCoordX(-938.667) + " " + Map_GetRealCoordZ(938.654));										
	trace("---------");
	trace("Teno (areal)							: " + Map_GetRealCoordX(-966.062) + " " + Map_GetRealCoordZ(-294.232));										
	trace("����������� 							: " + Map_GetRealCoordX(-969.194) + " " + Map_GetRealCoordZ(-305.237));										
	trace("Shore61 (���������) 					: " + Map_GetRealCoordX(-955.553) + " " + Map_GetRealCoordZ(-281.197));
	trace("Shore62 (����������)					: " + Map_GetRealCoordX(-935.811) + " " + Map_GetRealCoordZ(-316.162));
	trace("---------");	
}