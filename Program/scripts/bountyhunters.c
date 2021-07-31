// BOAL 27/06/06 ��������� ��� ����� ���, ��� ������ � �������� ������.
void SeaHunterCheck()
{
	int    j, i;
	string typeHunter, sGroup, sCapId;
	ref    sld;
	
	SetTimerCondition("SeaHunterCheck", 0, 0, 6+rand(20), true);
    for (j=0; j< MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // �������, ���� �� ����� ������ �������� if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        typeHunter = NationShortName(j);

        if (ChangeCharacterNationReputation(pchar, j, 0) <= -10)// ����� ��� ���
        {
            sCapId = typeHunter + "Hunter0";
            sGroup = "Sea_" + sCapId + "1";
            
			Group_DeleteGroup(sGroup);
			Group_FindOrCreateGroup(sGroup);
            for (i = 1; i <= 7; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, j, 20, true));
                SetShipHunter(sld);
                sld.WatchFort = true; //������ �����
                SetFantomParamHunter(sld); //������ �����
                SetCaptanModelByEncType(sld, "war");
                sld.AlwaysEnemy = true;
                sld.DontRansackCaptain = true;
                sld.mapEnc.type = "war";
                sld.mapEnc.Name = "�������� �� ��������";
				sld.hunter = "hunter";
				//sld.mapEnc.worldMapShip = "Manowar_gold";
                Group_AddCharacter(sGroup, sCapId + i);
                
                if (i == 1 || GetCharacterShipClass(sld) == 1) SetRandGeraldSail(sld, sti(sld.Nation));
                
                if (abs(ChangeCharacterNationReputation(pchar, j, 0)) < (i * 15)) break; // ������� �������� ������ ����� ���������
            }

            Group_SetGroupCommander(sGroup, sCapId+ "1");
            Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
            Group_LockTask(sGroup);
			//Lipsar �������� �������							  
            Map_CreateHunter("", sCapId + "1", 8);// LEO: ���������. ����� �����, �������, ���� ���������� �� �������� ���.
        }
    }
}

void SetShipHunter(ref Hunter)
{
    int ShipsHunter, hcrew;

	int j, q; // LEO: --> ��� ���������� ���. �������
	int iNation = sti(Hunter.nation);
	object rShip;
	bool bOk = false;
	aref aNation; 
	string sAttr;
	
	while(!bOk)
	{
		if(makeint(pchar.rank) >= 1 && makeint(pchar.rank) <=5) ShipsHunter = 3 + rand(11); // 6 �����
		if(makeint(pchar.rank) >= 5 && makeint(pchar.rank) <=10) ShipsHunter = 15 + rand(12); // 5 �����
		if(makeint(pchar.rank) >= 10 && makeint(pchar.rank) <=15) ShipsHunter = 28 + rand(23); // 4 �����
		if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) <=20) ShipsHunter = 52 + rand(31); // 3 �����
		if(makeint(pchar.rank) >= 20 && makeint(pchar.rank) <=30) ShipsHunter = 84 + rand(20); // 2 �����
		if(makeint(pchar.rank) > 30 ) ShipsHunter = 84 + rand(40); // 2 - 1 �����
		// ����� ��� ������ ������

		rShip = GetShipByType(ShipsHunter);
		makearef(aNation, rShip.nation); 
		q = GetAttributesNum(aNation);
		for(j = 0; j < q; j++) 
		{ 
			sAttr = GetAttributeName(GetAttributeN(aNation, j)); 
			if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true) bOk = true; 
		} 
	} // <-- ��� ���������� ���. �������

    SetRandomNameToCharacter(Hunter);
    SetRandomNameToShip(Hunter);
    Hunter.Ship.Type = GenerateShipExt(ShipsHunter, 1, Hunter);
    SetBaseShipData(Hunter);
    hcrew = GetMaxCrewQuantity(Hunter);
    SetCrewQuantity(Hunter, hcrew);
    SetCrewQuantityFull(Hunter); // to_do
	RealShips[sti(Hunter.ship.type)].ship.upgrades.sails = 24 + rand(13); // LEO: ����. ������ ���
	Hunter.OZG = true;
    
    DeleteAttribute(Hunter,"ship.sails");
    DeleteAttribute(Hunter,"ship.masts");
    DeleteAttribute(Hunter,"ship.blots");

    if (Hunter.nation == PIRATE)
    {
        Fantom_SetCannons(Hunter, "pirate");
        Fantom_SetBalls(Hunter, "pirate");
		Fantom_SetUpgrade(Hunter, "pirate");
    }
    else
    {
        Fantom_SetCannons(Hunter, "war");
        Fantom_SetBalls(Hunter, "war");
		Fantom_SetUpgrade(Hunter, "war");
    }
}
// ���� �� ���� (���� � �����)
void LandHunterReactionResult(ref loc)  // ���������� ����� ����� � �������, �� ����� �����_������� �� ����
{
	int    j, i, k;
	string typeHunter, sTemp, sCapId;
	ref    sld;
	bool   ok;
	
	//if (actLoadFlag) return; // ���� ����
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // ���� ����� ������ ����� � �������� ������
	if (loc.type != "town" && loc.type != "seashore" && loc.type != "port") return;   
	if (CheckAttribute(Pchar, "GenQuest.Hunter2Pause")) 
	{
		DeleteAttribute(Pchar, "GenQuest.Hunter2Pause");
		return; 
	}
	if (LAi_grp_alarmactive == true)  return;  // ��� �� ���-�� ����
	
	//if (GetQuestPastDayParam("Land_HunterTimerHasBeen") == 0) return; // ������� ��� ����
	for (j=0; j< MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // �������, ���� �� ����� ������ �������� if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        typeHunter = NationShortName(j);
        if (GetQuestPastDayParam("Land_HunterTimer" + typeHunter) > (7 + rand(7)))
        {
			SaveCurrentQuestDateParam("Land_HunterTimer" + typeHunter); // ��������, ���� ���� ��� �����, ����� �� ��� ������� ����� �� ���� ���� � �� �����
			if (ChangeCharacterNationReputation(pchar, j, 0) <= -10)// ����� ��� ���
	        {
	            Log_QuestInfo("LandHunterReactionResult " + typeHunter);
				sCapId = typeHunter + "LandHunter0";
	            sTemp = "LAND_HUNTER"; 
				ok = true;
				arrayNPCModelHow = 0;
	            for (i = 1; i <= 8; i++)
	            {
	                sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, j, 0, true));
	                SetFantomParamHunter(sld); //������ �����
	                sld.name 	= "������� �� ��������";
	                sld.lastname 	= "";
	                sld.Dialog.CurrentNode = "First time";
	                sld.dialog.filename = "Hunter_dialog.c";
	                sld.greeting = "Gr_HUNTER";
	                sld.location = "none"; // ��� ��� �������� ������!!!!!!!!!!!
	
	                SetOZGModel(sld);
/* 	                k = 0;
					while (!CheckNPCModelUniq(sld) && k < 10)
					{
					    k++;
         				SetOZGModel(sld);
					} */
					arrayNPCModel[arrayNPCModelHow] = sld.model;
					arrayNPCModelHow++;
	                LAi_SetActorTypeNoGroup(sld);
	                LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
	                if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix ���� ����� ��� � �������
	                {
	                    ok = false;
	                    break;
	                }
	                LAi_ActorFollow(sld, pchar, "", 8.0);
	                LAi_group_MoveCharacter(sld, sTemp);
	                if (abs(ChangeCharacterNationReputation(pchar, j, 0)) < (i * 9)) break; // ����� �� ���
	            }
	            
				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);
				
				LAi_group_ClearAllTargets();
				LAi_SetFightModeForOfficers(false); 
				if (ok)
	            {
	                pchar.HunterCost = abs(ChangeCharacterNationReputation(pchar, j, 0));
	                PChar.HunterCost = makeint(PChar.HunterCost)*2000 + rand(5000); //����� �������
	                PChar.HunterCost.TempHunterType = typeHunter;
	                PChar.HunterCost.Qty = i;
	                sld = characterFromID(sCapId + "1");
	                LAi_type_actor_Reset(sld);
	                LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		    		chrDisableReloadToLocation = true;
		    		DoQuestCheckDelay("OpenTheDoors", 5.0);
	            }
	            break;
	        }
        }
    }
}