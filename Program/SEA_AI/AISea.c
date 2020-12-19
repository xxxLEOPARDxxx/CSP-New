object	Sea;
object	ShipLights;

extern void InitShipLights();

void SeaAI_GetLayers()
{
	aref oTmp = GetEventData();
	SendMessage(oTmp, "lss", AI_MESSAGE_SET_LAYERS, sCurrentSeaExecute, sCurrentSeaRealize);
}

void DeleteSea()
{
	DeleteClass(&Sea);
	DeleteClass(&ShipLights);
}

void CreateSea(string sExecuteLayer, string sRealizeLayer)
{
	if (IsEntity(&Sea)) { Trace("ERROR: Sea Already Loaded!!!"); return; }

	CreateEntity(&Sea, "sea");
	MoveSeaToLayers(sExecuteLayer, sRealizeLayer);

	LayerFreeze("sea_reflection2", false);

	if (LoadSegment("sea_ai\ShipLights.c"))
	{
		InitShipLights();
		UnloadSegment("sea_ai\ShipLights.c");
	}
	CreateEntity(&ShipLights, "ShipLights");		ReloadProgressUpdate();
	LayerAddObject(sExecuteLayer, &ShipLights, 0);
	LayerAddObject(sRealizeLayer, &ShipLights, -1);
	LayerAddObject("sea_sunroad", &ShipLights, -1);

	Sea.AbordageMode = false;
}

void MoveSeaToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute", &Sea);
	LayerDelObject("realize", &Sea);
	LayerDelObject(SEA_EXECUTE, &Sea);
	LayerDelObject(SEA_REALIZE, &Sea);

	LayerAddObject(sExecuteLayer, &Sea, 4);
	LayerAddObject(sRealizeLayer, &Sea, 65530);
}

#define SAIL_TO_LOCATOR			0
#define SAIL_TO_CHARACTER		1

object	SailToFader;
int		iSailToType;
string	sSailToString;

void SeaAI_SailToEndFade()
{
	DelEventHandler("SeaAI_SailToEndFadeEvent", "SeaAI_SailToEndFade");
	SendMessage(&SailToFader, "lfl", FADER_IN, 0.5, true);

	// delete current cannonballs
	AIBalls.Clear = "";

	// reset all PLAYER_GROUP ship tracks
	for (int i=0; i<iNumShips; i++)
	{
		int iCharIndex = Ships[i];
		//Boyer fix
		if (iCharIndex >= 0 && iCharIndex < TOTAL_CHARACTERS) { //Boyer fix
			if (CheckAttribute(&Characters[iCharIndex], "SeaAI.Group.Name") && Characters[iCharIndex].SeaAI.Group.Name ==	PLAYER_GROUP) // fix
			{
				SendMessage(&Characters[iCharIndex], "l", MSG_SHIP_RESET_TRACK);
			}
		}
	}
    // fix -->
	ClearAllFire();
	//PauseParticles(true);
    // fix <--
	switch (iSailToType)
	{
		case SAIL_TO_LOCATOR:
			aref rIslLoc = FindIslandReloadLocator(pchar.Location, sSailToString);
			SendMessage(&AISea,"lffff", AI_MESSAGE_SAIL_2_LOCATOR, stf(rIslLoc.x), stf(rIslLoc.y), stf(rIslLoc.z), stf(rIslLoc.ay));
		break;
		case SAIL_TO_CHARACTER:
			SendMessage(&AISea, "laff", AI_MESSAGE_SAIL_2_CHARACTER, &Characters[sti(sSailToString)], 40.0 + frnd() * 60.0, frnd() * PIm2);
		break;
	}
	//PauseParticles(false);
}

void SeaAI_SailToCreateFader()
{
	SetEventHandler("SeaAI_SailToEndFadeEvent", "SeaAI_SailToEndFade", 0);
	PostEvent("SeaAI_SailToEndFadeEvent", 500);

	CreateEntity(&SailToFader, "fader");
	SendMessage(&SailToFader, "lfl", FADER_OUT, 0.5, false);
	SendMessage(&SailToFader, "l", FADER_STARTFRAME);

	SendMessage(&SailToFader, "ls", FADER_PICTURE, "loading\sea_" + rand(31) + ".tga");
}

void SeaAI_SailToLocator(string sLocName)
{
	iSailToType = SAIL_TO_LOCATOR;
	sSailToString = sLocName;
	SeaAI_SailToCreateFader();
}

void SeaAI_SailToCharacter(int iCharacterIndex)
{
	iSailToType = SAIL_TO_CHARACTER;
	sSailToString = "" + iCharacterIndex;
	SeaAI_SailToCreateFader();
}

// ����� �� ������������ � ��������
void AISea_ReturnFromAbordage()
{
	MoveSeaToLayers(SEA_EXECUTE,SEA_REALIZE);
	MoveWeatherToLayers(SEA_EXECUTE,SEA_REALIZE);

	LayerFreeze("realize",true);
	LayerFreeze("execute",true);

	LayerFreeze(SEA_EXECUTE,false);
	LayerFreeze(SEA_REALIZE,false);

	Sea.MaxSeaHeight = fOldMaxSeaHeight;//50.0;

}

void SeaAI_SwapShipsAttributes(ref refMyCharacter, ref refEnemyCharacter, bool SetShipNum) // to_do
{
	aref	arShipMy, arShipEnemy;
	object	oTmp;
	int 	curshipnum;

	int iMyCharacterIndex = sti(refMyCharacter.index);
	int iEnemyCharacterIndex = sti(refEnemyCharacter.index);
	
	if(SetShipNum)
	{
		if (CheckAttribute(refMyCharacter, "curshipnum")) 
		{
			curshipnum = sti(refMyCharacter.curshipnum);
			if (CheckAttribute(refEnemyCharacter."curshipnum"))
			{
				refMyCharacter.curshipnum = refEnemyCharacter.curshipnum;
				Ships[sti(refMyCharacter.curshipnum)] = iMyCharacterIndex;		
				refEnemyCharacter.curshipnum = curshipnum;
				Ships[sti(refEnemyCharacter.curshipnum)] = iEnemyCharacterIndex;
			}
		}
		else
		{
			if (CheckAttribute(refEnemyCharacter."curshipnum"))
			{
				refMyCharacter.curshipnum = sti(refEnemyCharacter.curshipnum);
				Ships[sti(refMyCharacter.curshipnum)] = sti(refMyCharacter.curshipnum);
				DeleteAttribute(refEnemyCharacter, "curshipnum");
			}				
		}
	}
	else
	{
		if (CheckAttribute(refMyCharacter, "curshipnum") && CheckAttribute(refEnemyCharacter, "curshipnum")) 
		{
			curshipnum = sti(refMyCharacter.curshipnum);
			if (CheckAttribute(refEnemyCharacter."curshipnum"))
			{
				refMyCharacter.curshipnum = refEnemyCharacter.curshipnum;
				Ships[sti(refMyCharacter.curshipnum)] = iMyCharacterIndex;		
				DeleteAttribute(refEnemyCharacter, "curshipnum");
			}
		}	
	}	
		
	makearef(arShipMy, refMyCharacter.Ship);
	makearef(arShipEnemy, refEnemyCharacter.Ship);

	CopyAttributes(&oTmp,arShipMy);
	DeleteAttribute(arShipMy,"");
	CopyAttributes(arShipMy,arShipEnemy);
	DeleteAttribute(arShipEnemy,"");
	CopyAttributes(arShipEnemy,&oTmp);
	// ��������� ������ ������� �� �����, ����� �������� ������
	/*float fExp = stf(refMyCharacter.ship.crew.experience);
	float fMor = stf(refMyCharacter.ship.crew.morale);

	refMyCharacter.ship.crew.experience = refEnemyCharacter.ship.crew.experience;
	refMyCharacter.ship.crew.morale = refEnemyCharacter.ship.crew.morale;
	refEnemyCharacter.ship.crew.experience = fExp;
	refEnemyCharacter.ship.crew.morale = fMor;*/
}
//#20190627-01
bool SeaAI_SwapShipAfterAbordage(ref refMyCharacter, ref refEnemyCharacter)
{
	if (bSeaActive)
	{
		SendMessage(&AISea, "laa", AI_MESSAGE_SWAP_SHIPS, refMyCharacter, refEnemyCharacter);
		//#20190207-01
		//restore flags in case we had surrendered ship
		Ship_FlagRefresh(&characters[sti(refMyCharacter.index)]);

        Ship_FlagRefresh(&characters[sti(refEnemyCharacter.index)]);
		RefreshBattleInterface();
		NationUpdate();
	}
	return true;
}

void SeaAI_SetCompanionEnemy(ref rCharacter)
{
	int		iCharacterIndex = sti(rCharacter.index);
	string	sGroupName = "cmpenemy_" + rCharacter.index;

	RemoveCharacterCompanion(pchar, rCharacter);

	Group_DelCharacter(rCharacter.SeaAI.Group.Name, rCharacter.id);

	rCharacter.SeaAI.Group.Name = sGroupName;
	Group_AddCharacter(sGroupName, rCharacter.id);
	Group_SetGroupCommander(sGroupName, rCharacter.id);

	SendMessage(&AISea, "la", AI_MESSAGE_SET_COMPANION_ENEMY, rCharacter);
	
	Group_SetTaskAttack(sGroupName, PLAYER_GROUP);
	Group_DeleteAtEnd(sGroupName);

	SetCharacterRelationBoth(iCharacterIndex, nMainCharacterIndex, RELATION_ENEMY);

	Event("eSwitchPerks", "l", iCharacterIndex);
	Event("eSwitchPerks", "l", nMainCharacterIndex);

	Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, 1.0);				// Parameters
	Event(SHIP_UPDATE_PARAMETERS, "lf", nMainCharacterIndex, 1.0);		// Parameters

	UpdateRelations();
	RefreshBattleInterface();
}
// boal ����������� �������� ��� ������������
void SeaAI_SetCaptainFree(ref rCharacter, ref refEnemyCharacter)
{
	// ����� ������� SeaAI_SetOfficer2ShipAfterAbordage    � SeaAI_SetCompanionEnemy   - � ������ �������� ���, ����� ��� �������� :)
	if (bSeaActive)
	{
        int		iCharacterIndex = sti(rCharacter.index);
		if (CheckAttribute(refEnemyCharacter, "SeaAI.Group.Name")) // fix 01/08/06 ������ ����� �� ����
		{
			Group_DelCharacter(refEnemyCharacter.SeaAI.Group.Name, refEnemyCharacter.id);
		}
		SendMessage(&AISea, "laa", AI_MESSAGE_SET_OFFICER_2_SHIP, rCharacter, refEnemyCharacter);
		// ��� �� ��������� ��� ��� ��, �� �� ����� ������ �� �� ����
		
		string	sGroupName = "cmpenemy_" + rCharacter.index;

        if (CheckAttribute(rCharacter, "SeaAI.Group.Name"))
		{
			Group_DelCharacter(rCharacter.SeaAI.Group.Name, rCharacter.id);
		}
		rCharacter.SeaAI.Group.Name = sGroupName;
		Group_AddCharacter(sGroupName, rCharacter.id);
		Group_SetGroupCommander(sGroupName, rCharacter.id);

		SendMessage(&AISea, "la", AI_MESSAGE_SET_COMPANION_ENEMY, rCharacter);

		Group_SetTaskRunaway(sGroupName, PLAYER_GROUP);
		Group_DeleteAtEnd(sGroupName);

		SetCharacterRelationBoth(iCharacterIndex, nMainCharacterIndex, RELATION_FRIEND);

		Event("eSwitchPerks", "l", iCharacterIndex);
		Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, 1.0);				// Parameters

		UpdateRelations();
		RefreshBattleInterface();
	}
}

bool SeaAI_SetOfficer2ShipAfterAbordage(ref refMyCharacter, ref refEnemyCharacter)
{
	int iMyCharacterIndex = sti(refMyCharacter.index);
	int iEnemyCharacterIndex = sti(refEnemyCharacter.index);
	if (bSeaActive)
	{
		if (CheckAttribute(refEnemyCharacter, "SeaAI.Group.Name")) // fix 01/08/06 ������ ����� �� ����
		{
			Group_DelCharacter(refEnemyCharacter.SeaAI.Group.Name, refEnemyCharacter.id);
		}
		SendMessage(&AISea, "laa", AI_MESSAGE_SET_OFFICER_2_SHIP, refMyCharacter, refEnemyCharacter);
		Event("eSwitchPerks", "l", iMyCharacterIndex);
		Event(SHIP_UPDATE_PARAMETERS, "lf", iMyCharacterIndex, 1.0);		// Parameters
		if (CheckAttribute(refMyCharacter, "curshipnum"))  DeleteAttribute(refMyCharacter, "curshipnum"));
		refMyCharacter.curshipnum = sti(refEnemyCharacter.curshipnum);
		DeleteAttribute(refEnemyCharacter, "curshipnum");
		Ships[sti(refMyCharacter.curshipnum)] = iMyCharacterIndex; // ��� ��� ������ �� �������� !!!!!
		
		Group_AddCharacter(PLAYER_GROUP, refMyCharacter.id);
		UpdateRelations();
		RefreshBattleInterface();
	}
	return true;
}

int SeaAI_GetRelation(int iCharacterIndex1, int iCharacterIndex2)
{
 	int iRelation = RELATION_NEUTRAL;
	/*if (bSeaActive)
	{
		SendMessage(&AISea, "laae", AI_MESSAGE_GET_RELATION, &Characters[iCharacterIndex1], &Characters[iCharacterIndex2], &iRelation);
		return iRelation;
	}*/
	return GetRelation(iCharacterIndex1, iCharacterIndex2);
}

void UpdateRelations()
{
	if (bSeaActive)
	{
		SendMessage(&AISea, "l", AI_MESSAGE_UPDATE_RELATIONS);
		// �� ���� � ���, ����� ����  ��� �������, ���� ������� RefreshBattleInterface();
	}
}
