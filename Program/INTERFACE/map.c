string totalInfo = "";
bool isSkipable = false;
bool bEncType   = false;
bool bShowVideo; // ��� ������ ��������� �������, ���� �����
string  sQuestSeaCharId = "";

void InitInterface(string iniName)
{
	EngineLayersOffOn(true);
	SetTimeScale(0.0);
	
	// ����� ����� � �����
    bQuestCheckProcessFreeze = true;
    bEncType = false; // ������� ���
    bShowVideo = false;
    
    GameInterface.title = "title_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
    SetFormatedText("MAP_CAPTION", XI_ConvertString("title_map"));
	SetFormatedText("INFO_TEXT_QUESTION", XI_ConvertString("MapWhatYouWantToDo"));
	SetCurrentNode("INFO_TEXT_QUESTION");
	SetNewPicture("INFO_PICTURE", "loading\SeaEnc_"+rand(3)+".tga");

	CalculateInfoData();
	SetFormatedText("INFO_TEXT",totalInfo);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // ����� �� ����
	SetEventHandler("exitCancel","ProcessCancelExit",0); // ����� �� ���� �� �������� ��� Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // ����� �� ����� ������ ��� (�� ���)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // ����� �� ����������
	
	EI_CreateFrame("INFO_BORDERS", 250,152,550,342);
	PlayVoice("interface\_EvShip"+rand(3)+".wav");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	wdmReloadToSea();
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	wdmReloadToSea();
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

    SetTimeScale(1.0);
	TimeScaleCounter = 0; //boal
	if(IsPerkIntoList("TimeSpeed"))
	{	
		DelPerkFromActiveList("TimeSpeed");
	}
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);//boal 230804 ��������� �������� �������
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	ref chr;
	switch(nodName)
	{
	case "B_OK":
		if(comName=="activate" || comName=="click")
		{
			if (sQuestSeaCharId != "")
			{
				wdmEnterSeaQuest(sQuestSeaCharId);
			}
			// �������
   			IDoExit(RC_INTERFACE_MAP_EXIT);
			wdmReloadToSea();
			if(CheckAttribute(PChar, "GenerateShipWreck.ShipInMap"))
			{
				if(GetCharacterIndex(PChar.GenerateShipWreck.ShipInMap) != -1)
				{
					chr = CharacterFromID(PChar.GenerateShipWreck.ShipInMap);
					if(CheckAttribute(chr, "ShipWreck")) 
					{ 
						ShipWreckInSea(chr); 
					}
				}
			}
				
		}
		if(comName=="downstep")
		{
			if(GetSelectable("B_CANCEL"))	{SetCurrentNode("B_CANCEL");}
		}
	break;

	case "B_CANCEL":
		if(comName=="activate" || comName=="click")
		{
			//����������
			//PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_MAP_EXIT);
			pchar.SkipEshipIndex = pchar.eshipIndex;
			IDoExit(RC_INTERFACE_MAP_EXIT);
		}
		if(comName=="upstep")
		{
			if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
		}
	break;
	}
}
void wdmRecalcReloadToSea()
{
	worldMap.encounter.type = "";
	totalInfo = "";
	int iRand;
	//Encounters
	int numEncounters = wdmGetNumberShipEncounters();
	int isShipEncounterType = 0;
	Log_TestInfo("�������� ���������� �����������");
	for(int i = 0; i < numEncounters; i++)
	{
		if(wdmSetCurrentShipData(i))
		{
		   if(MakeInt(worldMap.encounter.select) == 0) continue;
			isShipEncounterType++;

			string encID = worldMap.encounter.id;
			
			aref rEncounter;
			makearef(rEncounter, worldMap.encounters.(encID).encdata);

			int iRealEncounterType = sti(rEncounter.RealEncounterType);

			if (isShipEncounterType > 1 && iRealEncounterType < ENCOUNTER_TYPE_BARREL)
			{
			    totalInfo = totalInfo + XI_ConvertString("But in the same way");
			}

			int iNumMerchantShips = 0;
			int iNumWarShips = 0;
			if(CheckAttribute(rEncounter, "NumMerchantShips"))
			{
				iNumMerchantShips = sti(rEncounter.NumMerchantShips);
			}
			if(CheckAttribute(rEncounter, "NumWarShips"))
			{
				iNumWarShips = sti(rEncounter.NumWarShips);
			}


			if (CheckAttribute(rEncounter, "CharacterID"))
			{
                iNumWarShips = GetCharacterIndex(rEncounter.CharacterID);
                if (iNumWarShips != -1)
                {
					sQuestSeaCharId = characters[iNumWarShips].id; // ��������� 
					PChar.GenerateShipWreck.ShipInMap = sQuestSeaCharId;
					if (CheckAttribute(&characters[iNumWarShips], "mapEnc.Name"))
					{
						totalInfo = totalInfo + characters[iNumWarShips].mapEnc.Name;
					}
					else
					{
						totalInfo = totalInfo + "'" + characters[iNumWarShips].ship.name + "'."
					}
				}
				bEncType = true;
			}
			else
			{
				if(iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("of traders");
				}
				if(iRealEncounterType >= ENCOUNTER_TYPE_MERCHANT_GUARD_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_GUARD_LARGE)
				{
					totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}
				if(iRealEncounterType >= ENCOUNTER_TYPE_ESCORT_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_ESCORT_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Trade caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PATROL_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PATROL_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Patrol") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_PIRATE_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PIRATE_LARGE)
				{
					totalInfo = totalInfo + XI_ConvertString("Pirates") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType >= ENCOUNTER_TYPE_SQUADRON && iRealEncounterType <= ENCOUNTER_TYPE_ARMADA)
				{
					totalInfo = totalInfo + XI_ConvertString("Naval squadron") + GetTextOnShipsQuantity(iNumWarShips);
				}

				if(iRealEncounterType == ENCOUNTER_TYPE_PUNITIVE_SQUADRON)
				{
					totalInfo = totalInfo + XI_ConvertString("Punitive expedition") + GetTextOnShipsQuantity(iNumWarShips);
				}
				if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
				{
					totalInfo = totalInfo + XI_ConvertString("SailingItems");
				}
			
				if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
				{
					totalInfo = totalInfo + XI_ConvertString("ShipWreck");
				}				
			}
			if(sti(rEncounter.Nation) < 0)
			{
        		totalInfo = totalInfo + "���� -1.";
      		}
	        
			if(iRealEncounterType != ENCOUNTER_TYPE_BARREL && iRealEncounterType != ENCOUNTER_TYPE_BOAT)
            {
                string nationname = "";
                switch(sti(rEncounter.Nation))
                {                
                    case ENGLAND:        
                        totalInfo = totalInfo + XI_ConvertString("under english flag");
                        nationname = "Eng";
                    break;
                    case FRANCE:        
                        totalInfo = totalInfo + XI_ConvertString("under french flag");
                        nationname = "Fra";
                    break;
                    case SPAIN:        
                        totalInfo = totalInfo + XI_ConvertString("under spanish flag");
                        nationname = "Spa";
                    break;
                    case HOLLAND:        
                        totalInfo = totalInfo + XI_ConvertString("under dutch flag");
                        nationname = "Hol";
                    break;
                    case PIRATE:        
                        totalInfo = totalInfo + ".";
                        nationname = "Pir";
                    break;
                }
                SetNewPicture("ENC_NATIONS_PICTURE", "loading\Enc_"+nationname+".tga");
            }    

			if(GetNationRelation2MainCharacter(sti(rEncounter.Nation)) != RELATION_ENEMY)
			{
				isSkipable = true;
			}
		}
	}
	Log_TestInfo("isShipEncounterType :" + isShipEncounterType);
	if (isShipEncounterType > 1)
    {
       totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("battle on course") + totalInfo;
       SetNewPicture("ENC_NATIONS_PICTURE", "loading\EncFight.tga");
    }
	else
	{
		if(iRealEncounterType == ENCOUNTER_TYPE_BARREL || iRealEncounterType == ENCOUNTER_TYPE_BOAT)
		{		
			if(iRealEncounterType == ENCOUNTER_TYPE_BARREL) 
			{
				SetNewPicture("INFO_PICTURE", "loading\BarrelEnc_"+rand(2)+".tga");
			}
			if(iRealEncounterType == ENCOUNTER_TYPE_BOAT) 
			{
				SetNewPicture("INFO_PICTURE", "loading\BoatEnc_"+rand(5)+".tga");
			}
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("SpecialSituation") + totalInfo;
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#"+XI_ConvertString("GetItemToBort"));
		}
		else
		{
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + totalInfo;
		}
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    wdmRecalcReloadToSea();
    
	if (IsCharacterPerkOn(GetMainCharacter(), "SailingProfessional") || pchar.space_press == "1")
	{
		isSkipable = true;
	}
	SetCurrentNode("B_OK");
	
	
    float iSKILL_SNEAK = GetSummonSkillFromNameToOld(pchar, SKILL_SNEAK);

    if (iSKILL_SNEAK < 1) iSKILL_SNEAK = 1;
    
    SetSelectable("B_CANCEL",true);
	if( (rand(100) / iSKILL_SNEAK) > GetSummonSkillFromNameToOld(pchar, SKILL_SAILING) )// ������� ���� ����� ��������� ��� ������� ������ ���
	{
        if (!isSkipable && !bBettaTestMode)
        {
            SetSelectable("B_CANCEL",false);
        }
	}
	if (pchar.space_press == "1") bEncType = false;
	
	if (bEncType && !bBettaTestMode) // ���� ��� �� ����������
	{
        SetSelectable("B_CANCEL",false);
	}
	pchar.space_press = 0;
}