////  ���� ��� �������� � �����, ���� � ������������
void GenerateIslandShips(string sIslandID)
{
	//if (!TestRansackCaptain) return; // to_do
	
	int iColonyQuantity = sti(Islands[FindIsland(sIslandID)].colonyquantity);
	int iNation;
	int iShipsQuantity;
	int iChar;
	int iType = 0;

	int MainDefenderChar = -1;

	for (int i = 0; i< MAX_COLONIES; i++)
	{
		MainDefenderChar = -1;
		if (Colonies[i].island == sIslandID)
		{
			if (colonies[i].nation != "none" && !CheckAttribute(&colonies[i], "HasNoFort") && !CheckAttribute(&colonies[i], "DontSetShipInPort"))
			{
				if (!CheckAttribute(&colonies[i], "GenShipDate") || GetNpcQuestPastDayParam(&colonies[i], "GenShipDate") > 0)
				{
                    SaveCurrentNpcQuestDateParam(&colonies[i], "GenShipDate"); // ���� ����������
                    
					iNation = sti(Colonies[i].nation);
					float fChecker = frand(1.0);
					bool FortDefender = false;

					int defendersCount = 4; 
					iShipsQuantity = makeint(fChecker * 4.0) + defendersCount;
					ref FortChref = GetFortCommander(colonies[i].id); 
					if(sti(FortChref.Fort.Mode) == FORT_ABORDAGE || sti(FortChref.Fort.Mode) == FORT_DEAD || iNation == PIRATE) 
					{ 
						iShipsQuantity = 0; 
					}
						
					while (iShipsQuantity > 0)
					{
						if(defendersCount > 0) iChar = GenerateCharacter(iNation, DEFENDER_FORT, "soldier", MAN, -1, WARRIOR); 
						else iChar = GenerateCharacter(iNation, WITH_SHIP, "soldier", MAN, -1, WARRIOR); //-1 - ��� 1 ����
						if(defendersCount > 0) FortDefender = true; 
						else FortDefender = false;
						
						if(defendersCount > 0 && MainDefenderChar == -1) MainDefenderChar = iChar;

						PlaceCharacterShip(iChar, iNation, sIslandID, i, FortDefender, MainDefenderChar);

                            characters[iChar].IslandShips = Colonies[i].id; // ����� ������, ���� ������ �� ������� ������ to_do
							if (iNation == PIRATE)
							{ // ��� �����
								characters[iChar].AlwaysFriend        = true;
								SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
							}
							iType = rand(1);
							if(iType == 0)
							{
								characters[iChar].Ship.Mode = "war";
							}
							else
							{
								characters[iChar].Ship.Mode = "trade";
							}
						if(defendersCount > 0) characters[iChar].Ship.Mode = "war";
						if (rand(4) == 1 || GetCharacterShipClass(&characters[iChar]) == 1) SetRandGeraldSail(&characters[iChar], sti(characters[iChar].Nation));
						characters[iChar].AlwaysSandbankManeuver = true;  // ����� ������ ������ �� �����
						characters[iChar].AnalizeShips = true; //��������� ��������� �������
						characters[iChar].location.from_sea = colonies[i].from_sea;
						SetCaptanModelByEncType(&characters[iChar], characters[iChar].Ship.Mode); // boal
						Fantom_SetCannons(&characters[iChar], characters[iChar].Ship.Mode);
						Fantom_SetBalls(&characters[iChar], characters[iChar].Ship.Mode);
						Fantom_SetGoods(&characters[iChar], characters[iChar].Ship.Mode);
						Fantom_SetUpgrade(&characters[iChar], characters[iChar].Ship.Mode);
						iShipsQuantity = iShipsQuantity - 1;
						if(defendersCount > 0) defendersCount = defendersCount - 1;
					}
				}
			}
		}
	}
}

void PlaceCharacterShip(int iChar, int iNation, string sIslandID, int iColonyIdx, bool isFortDefender, int defendersGroup)
{
	int iColonyNum = sti(colonies[iColonyIdx].num);
	
	string sColonyID = colonies[iColonyIdx].id;
	
	string sGroup = "IslandGroup" + iChar;
	string sLocatorGroup = "IslandShips" + iColonyNum;
	string sLocator = "Ship_"+(rand(4)+2);
	
	if(isFortDefender)
	{
		sGroup = "IslandGroup" + defendersGroup;
	}
	
	Group_AddCharacter(sGroup, characters[iChar].id);
	
	if(isFortDefender)
	{
		Group_SetGroupCommander(sGroup, characters[defendersGroup].id);
		sLocator = "Ship_1";
	}
	else
	{
		Group_SetGroupCommander(sGroup, characters[iChar].id);
	}
	
	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);

	//trace("sLocatorGroup is " + sLocatorGroup + " sLocator is " + sLocator);

	int iTask = rand(1);
	if(isFortDefender) 
	{ 
		iTask = 3;
		characters[iChar].fortDefender = 1;
	}
	
	float x, z;
	if (iTask == 0)
	{
		x = rand(1000000);
		z = rand(1000000);
		Group_SetTaskMove(sGroup, x, z);
	}
	else
	{
		//Ship_SetTaskDrift(SECONDARY_TASK, iChar);
		Group_SetTaskNone(sGroup);
	}

	if (sti(characters[iChar].nation) != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
	{
		Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	}
}
// �������� ����
void ClearIslandShips(string _city)
{
	if (!bSeaActive)
	{
		for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
		{
			// ��������� ��� �������� boal -->
			if (CheckAttribute(&characters[i], "IslandShips") && characters[i].IslandShips == _city)
			{
				InitCharacter(&characters[i], i);
			}
			if (CheckAttribute(&characters[i], "fortDefender") && sti(characters[i].fortDefender) == 1)
			{
				InitCharacter(&characters[i], i);
			}
		}
		// ������ ������ ������
		Group_FreeAllDead();
	}
}