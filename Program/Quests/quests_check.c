
bool TestIntValue(int nValue, int nCompareValue, string sOperation)
{
	switch(sOperation)
	{
	case ">=":
			if(nValue >= nCompareValue) return true;
			return false;
	break;
	case "<=":
			if(nValue <= nCompareValue) return true;
			return false;
	break;
	case "=":
			if(nValue == nCompareValue) return true;
			return false;
	break;
	case ">":
			if(nValue > nCompareValue) return true;
			return false;
	break;
	case "<":
			if(nValue < nCompareValue) return true;
			return false;	
	break;
	}
	trace("ERROR: invalid operation(" + sOperation + ")");
	return false;
}

bool ProcessCondition(aref condition)
{
	bool bTmp;
	int i;
	int iNation, iLocation;
	ref tmpRef;
	ref refCharacter;
	string sConditionName;
	string sTmpString;
	string locGroup;
	string sLocation; 
	float fx,fy,fz;

	sConditionName = GetAttributeValue(condition);
	// boal -->
	if(CheckAttribute(condition,"character"))
	{
  		//condition.characterIdx = "" + GetCharacterIndex(condition.character);
		// ������������� � ����� ������, ��� � character ������ �� ID (������), � IDX (�����) -->
		i = GetCharacterIndex(condition.character);
		if (i != -1) condition.characterIdx = i;
		else condition.characterIdx = sti(condition.character); // ������ �����, ��� ��� �����
		// ������������� � ����� ������, ��� � character ������ �� ID (������), � IDX (�����) <--
		DeleteAttribute(condition,"character");
	}
	if(CheckAttribute(condition,"characterIdx"))
	{
		refCharacter = GetCharacter(sti(condition.characterIdx));
	}
	else
	{
		refCharacter = GetMainCharacter();
	}
	// boal <--

	switch(sConditionName)
	{
		// boal ����������� -->
		case "MapEnter":
    		return IsEntity(worldMap);
    	break;

    	case "ExitFromLocation":
    		return refCharacter.location != condition.location;
    	break;

        case "location":
    		if(refCharacter.location==condition.location) 
			{
				bLandEncountersGen = false;
				return !CharacterIsDead(refCharacter);
			}
    		return false;
    	break;

        case "Timer":
    		if( GetDataYear() < sti(condition.date.year) ) return false;
    		if( GetDataYear() > sti(condition.date.year) ) return true;
    		if( GetDataMonth() < sti(condition.date.month) ) return false;
    		if( GetDataMonth() > sti(condition.date.month) ) return true;
    		if( GetDataDay() < sti(condition.date.day) ) return false;
    		if (CheckAttribute(condition, "date.hour") && GetDataDay() <= sti(condition.date.day))  //fix
			{				
				if(GetHour() < stf(condition.date.hour)) return false;
				if(GetHour() >= stf(condition.date.hour)) return true;
			}
    		return true;
    	break;

    	case "locator":
    		if(refCharacter.location == condition.location)
    		{
    			locGroup = condition.locator_group;
    			if( !CheckAttribute(refCharacter,"Quests.LocatorCheck."+locGroup) )
    			{
    				if(IsEntity(refCharacter))
    				{
    					refCharacter.Quests.LocatorCheck.(locGroup) = "";
    					if( GetCharacterPos(refCharacter,&fx,&fy,&fz) )
    					{
    						if( CheckCurLocator(locGroup,condition.locator, fx,fy,fz) )
    							refCharacter.Quests.LocatorCheck.(locGroup) = condition.locator;
    					}
    					AddCharacterLocatorGroup(refCharacter,locGroup);
    				}
    				else
    				{
    					Trace("character "+refCharacter.id+" not entity");
    					return false;
    				}
    			}
    			if(refCharacter.Quests.LocatorCheck.(locGroup)==condition.locator)	return true;
    		}
    		return false;
    	break;

    	case "NPC_Death":
    		return CharacterIsDead(refCharacter);
    	break;
        case "NotBording":
			return !bAbordageStarted;
		break;
		//navy -->
		case "Location_Type":
			if (IsEntity(loadedLocation))
			{
				if (loadedLocation.type == condition.location_type) return !CharacterIsDead(refCharacter);
			}
			return false;
		break;
		//navy <--

		case "Nation_City":
			if (IsEntity(loadedLocation))
			{
				if (loadedLocation.type == "town") 
				{
					iNation = sti(condition.nation);
					sLocation = refCharacter.location;
					iLocation = FindLocation(sLocation);
					if(CheckAttribute(&Locations[iLocation], "fastreload"))
					{
						sLocation = Locations[iLocation].fastreload;
						if(iNation == sti(Colonies[FindColony(sLocation)].nation)) return true;
					}
				}	
			}
			return false;
		break;
		
        // boal  260804 -->  TO_DO
        /*
        case "location_port": // ����� �������� �������
            if (IsEntity(loadedLocation))
            {
    			if (loadedLocation.type == "port") return !CharacterIsDead(refCharacter);
    		}
    		return false;
    	break;

    	case "location_seashore": // ����� �����
            if (IsEntity(loadedLocation))
            {
    			if (loadedLocation.type == "seashore") return !CharacterIsDead(refCharacter);
    		}
    		return false;
    	break;

    	case "Location_Coast": // ����� ����� ��� ����
            if (IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
            {
    			if (loadedLocation.type == "seashore" || loadedLocation.type == "port") return !CharacterIsDead(refCharacter);
    		}
    		return false;
    	break;
    	*/
        // boal <--

        case "Goods":
    		return TestIntValue(GetCargoGoods(refCharacter,sti(condition.goods)),sti(condition.quantity),condition.operation);
    	break;

    	case "item":  // to_do  ���� � ������ ���������  ����, �� �� ������������
			// Warship ��� ����� ������� ��������� ��� �����������
			// Ugeen -- > ��� ����� ������� ��������� ��������� ������� CheckCharacterItem(), ������ ����� ���������
    		return CheckCharacterItem(refCharacter,condition.item);
    	break;

        case "Character_Capture":
    		if( CheckAttribute(refCharacter,"Killer.status") && sti(refCharacter.Killer.status)==KILL_BY_ABORDAGE ) return true;
    		return false;
    	break;

        //a&m --> 03/02
        case "Character_sink":
    		if( CheckAttribute(refCharacter,"Killer.status") && sti(refCharacter.Killer.status) != KILL_BY_ABORDAGE ) return true;
    		return false;
    	break;
        //a&m <--  03/02
        case "Ship_location":
    		if( CheckAttribute(refCharacter,"location.from_sea") && refCharacter.location.from_sea==condition.location ) return true;
    		return false;
    	break;
    	case "Group_Death":
			sTmpString = condition.group;
			return Group_isDead(sTmpString);
		break;
	// boal <--
	
		case "ComeToIsland":
			if(CheckAttribute(refCharacter,"ComeToIsland") && refCharacter.ComeToIsland=="1")
			{
				DeleteAttribute(refCharacter, "ComeToIsland");
				return true;
			}
			return false;
		break;

		case "EnterToSea":
			if(bSeaActive == true)
			{
				return true;
			}
			return false;
		break;

		case "ExitFromSea":
			if (bSeaActive == false)
			{
				return true;
			}
			return false;
		break;

		case "nation_location":
			iNation = sti(condition.nation);
			sLocation = refCharacter.location;
			iLocation = FindLocation(sLocation);
			if(iLocation != -1)
			{
				if(CheckAttribute(&Locations[iLocation], "fastreload"))
				{
					sLocation = Locations[iLocation].fastreload;
					int iCurrentNation = sti(Colonies[FindColony(sLocation)].nation);
					if(iNation == iCurrentNation)
					{
						return true;
					}
				}
			}
			return false;
		break;

		case "Fort_capture":
			if( CheckAttribute(refCharacter,"FortCapture") && refCharacter.FortCapture=="1" )
			{
				DeleteAttribute(refCharacter, "FortCapture");
				return true;
			}
			return false;
		break;

		case "Ship_capture":
			if(CheckAttribute(refCharacter,"ShipCapture") && refCharacter.ShipCapture=="1")
			{
				DeleteAttribute(refCharacter, "ShipCapture");
				return true;
			}
			return false;
		break;
		
		case "Coordinates":
			if(IsEntity(worldMap)) // ���� �� ���������� �����
			{
				if( GetMapCoordDegreeX(makefloat(worldMap.playerShipX)) == sti(condition.coordinate.degreeX) &&
				    GetMapCoordDegreeZ(makefloat(worldMap.playerShipZ)) == sti(condition.coordinate.degreeZ) &&
					GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) == sti(condition.coordinate.minutesX) && 
					GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) == sti(condition.coordinate.minutesZ))
				{	
					return true;	
				}	
				else return false;	
			}
			else
			{
				if (bSeaActive && !bAbordageStarted) // ���� � ������ "����"
				{
					if (CheckAttribute(pchar, "Ship.pos.x"))
					{
						if( GetSeaCoordDegreeX(makefloat(pchar.Ship.pos.x)) == sti(condition.coordinate.degreeX) &&
							GetSeaCoordDegreeZ(makefloat(pchar.Ship.pos.z)) == sti(condition.coordinate.degreeZ) &&
							GetSeaCoordMinutesX(makefloat(pchar.Ship.pos.x)) == sti(condition.coordinate.minutesX) && 
							GetSeaCoordMinutesZ(makefloat(pchar.Ship.pos.z)) == sti(condition.coordinate.minutesZ))
						{	
							return true;	
						}	
						else return false;	
					}
				}
			}
		break;
	}
	trace("ERROR: unidentified condition type()" + condition);
	return false;
}

bool bQuestCheckProcess = false;
bool bQuestCheckProcessFreeze = false;// boal 230804 fix ������������ �������� �������

void QuestsCheck()
{
	if(bQuestCheckProcess || bQuestCheckProcessFreeze || dialogRun) return;//boal
	bQuestCheckProcess = true;
	aref quests;
	aref quest;
	aref conditions;
	aref condition;
	int  nQuestsNum;
	int  nConditionsNum;
	int  n,m;
	string sQuestName;
	bool bQuestCompleted;
	
	
	makearef(quests,pchar.quest);
		
	nQuestsNum = GetAttributesNum(quests);
	
	for(n = 0; n < nQuestsNum; n++)
	{
        if (bQuestCheckProcessFreeze || dialogRun) continue;  // boal 230804 fix ������������ �������� �������
        
        quest = GetAttributeN(quests,n);

		sQuestName = GetAttributeName(quest);

		if(CheckAttribute(quest,"win_condition"))
		{
			if(quest.win_condition == "no")
			{
				// quest with no win condition; completed on first check
				OnQuestComplete(quest, sQuestName);
				nQuestsNum = GetAttributesNum(quests);
				continue;
			}
			makearef(conditions,quest.win_condition);
			nConditionsNum = GetAttributesNum(conditions);
			if(nConditionsNum == 0)
			{
				// quest with no win condition; completed on first check
				OnQuestComplete(quest, sQuestName);
				nQuestsNum = GetAttributesNum(quests);
				continue;
			}
			bQuestCompleted = true;
			for(m = 0; m < nConditionsNum; m++)
			{
				condition = GetAttributeN(conditions,m);
				if(ProcessCondition(condition) == false) 
				{
					bQuestCompleted = false;
					break;
				}
			}
			if(bQuestCompleted) 
			{
				OnQuestComplete(quest, sQuestName);
				nQuestsNum = GetAttributesNum(quests);
			}
		}
		
		if(CheckAttribute(quest,"fail_condition"))
		{
			makearef(conditions,quest.fail_condition);
			nConditionsNum = GetAttributesNum(conditions);
			if(nConditionsNum == 0) continue;
			for(m = 0; m < nConditionsNum; m++)
			{
				condition = GetAttributeN(conditions,m);
				if(ProcessCondition(condition) == true) 
				{
					OnQuestFailed(quest, sQuestName);
					nQuestsNum = GetAttributesNum(quests);
					break;
				}
			}
		}
	}
    nQuestsNum = GetAttributesNum(quests); // ����������� fix boal
	for(n = 0; n < nQuestsNum; n++)
	{
		quest = GetAttributeN(quests,n);
		if(CheckAttribute(quest,"over") && quest.over=="yes")
		{
			// delete quests already completed or failed
			DeleteAttribute(quests,GetAttributeName(quest));
			n--;
			nQuestsNum--;
		}
	}
	bQuestCheckProcess = false;
}

void OnQuestComplete(aref quest, string sQuestname)
{
	if(!CheckAttribute(quest,"over") && CheckAttribute(quest,"win_condition"))
	{
		if(!CheckAttribute(quest,"again")) // boal 04.04.04  �� ����������� ����������, � ������ �� ������, ����� ����� ����������� over = yes
        {
            quest.over = "yes";
        }
		QuestComplete(quest.win_condition, sQuestName);
	}
}

void OnQuestFailed(aref quest, string sQuestName)
{
	if(CheckAttribute(quest,"fail_condition"))
	{
		quest.over = "yes";
		QuestComplete(quest.fail_condition, sQuestName);
	}
}

void QC_DoUnloadLocation()
{
	DeleteAttribute(GetMainCharacter(),"GroupDeath");
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		DeleteAttribute(GetCharacter(n),"Quests.LocatorCheck");
	}
}

void SetPossibleAction(ref chref, aref condition, bool setting)
{
	if(setting)
	{
		if(CheckAttribute(condition,"act"))
		{
			condition.oldact = g_ActiveActionName;
			Log_SetActiveAction(condition.act);
		}
		chref.Quests.quest_act = GetAttributeName(condition);
	}
	else
	{
		if(CheckAttribute(condition,"oldact"))
		{
			Log_SetActiveAction(condition.oldact);
			DeleteAttribute(condition,"oldact");
		}
		DeleteAttribute(chref,"Quests.quest_act");
	}
}