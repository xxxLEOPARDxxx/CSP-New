// ����� �� ���

//  ����� ��������  ��������� -->
string GetIslandForTreasure()
{
	int iNum, m;
	ref Itm;
	aref arDest, arImt;
	string sAttr;
	
	m = 0;
	string sCurIsland = GetCharacterCurrentIslandId(pchar);
	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);
	
	string sArray[50]; // ������������ ������� � ������ �� ����������� :(
	for (int i = 0; i<iNum; i++)
	{
		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + sAttr + ".Treasure"))
		{
			if(sCurIsland == sAttr || CheckTreasureMaps(sAttr)) continue;
			else
			{
				sArray[m] = sAttr;
				m++;		
			}	
		}
	}
	m = rand(m-1);
	return sArray[m];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;
	
	if(GetCharacterItem(pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}		
	if(GetCharacterItem(pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}	
	return false;
}

string GetLocationForTreasure(string island)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure);
	iNum = GetAttributesNum(arDest);
	if (iNum == 0) iNum=iNum;
    else iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeName(arImt);
}

string GetBoxForTreasure(string island, string location)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	iNum = GetAttributesNum(arDest);
	if (iNum == 0) iNum=iNum;
    else iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeValue(arImt);  // ��� �� �������, � �������
}
// �� ��� ����....
string GetFileMapForTreasure(string island)
{
    int n;

    for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		if (CheckAttribute(&Items[n], "MapIsland") )
		{
            if (Items[n].MapIsland == island)
            {
                return Items[n].imageTga;
            }
		}
    }
    return "";
}

void GenerateMapsTreasure(ref item, int iProbability1, int iProbability2)
{		
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) item.BoxTreasure.map_jam = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) item.BoxTreasure.map_cayman = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) item.BoxTreasure.map_barbados = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) item.BoxTreasure.map_trinidad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) item.BoxTreasure.map_Curacao = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) item.BoxTreasure.map_martiniqua = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) item.BoxTreasure.map_dominica = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) item.BoxTreasure.map_puerto = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) item.BoxTreasure.map_cuba = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) item.BoxTreasure.map_hisp = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) item.BoxTreasure.map_nevis = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) item.BoxTreasure.map_guad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) item.BoxTreasure.map_antigua = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) item.BoxTreasure.map_TORTUGA = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) item.BoxTreasure.map_terks = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) item.BoxTreasure.map_sm = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) item.BoxTreasure.map_bermudas = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) item.BoxTreasure.map_Pearl = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) item.BoxTreasure.map_beliz = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) item.BoxTreasure.map_santa = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) item.BoxTreasure.map_maine_1 = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) item.BoxTreasure.map_maine_2 = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) item.BoxTreasure.map_panama = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) item.BoxTreasure.map_maracaibo = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) item.BoxTreasure.map_cumana = 1;
}

void FillMapForTreasure(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    item.MapTypeIdx = rand(2);

    // ������� ����
    DeleteAttribute(item, "BoxTreasure");
	if (GetCharacterSPECIALSimple(pchar, SPECIAL_L) > rand(10)) FillBoxForTreasure(item, rand(1));
    else FillBoxForTreasure(item, rand(3));
    FillBoxForTreasureAddition(item);
	Xzibit(item);

    if (!CheckAttribute(Pchar, "GenQuest.TreasureBuild"))
    {
        if (rand(12+GetCharacterSPECIALSimple(pchar, SPECIAL_L)) == 1) item.MapTypeIdx = -1;
    }
    else
    {// �� �������� ���� ����� ����
       /*while (item.MapLocId == "Muelle_town_04" || item.MapLocId == "Havanna_town_04") // �� ��� ������
       {
            item.MapIslId   = GetIslandForTreasure();
            item.MapLocId   = GetLocationForTreasure(item.MapIslId);
            item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
       } */
       FillBoxForTreasureSuper(item);
	   if (GetCharacterSPECIALSimple(pchar, SPECIAL_L) > rand(10)) FillBoxForTreasureSuper(item);
	   if (rand(100)==0) item.BoxTreasure.mushket_Shtuzer = 1;
    }
    DeleteAttribute(Pchar, "GenQuest.TreasureBuild"); //�������

    if (sti(item.MapTypeIdx) != -1)
    {
        Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
        Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
        Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
    }
}

void Xzibit(ref item)
{
	switch (rand(2))
	{
		case 0: item.BoxTreasure.Chest_ammo = 1; break;
		case 1: item.BoxTreasure.Chest_treasure = 1; break;
		case 2: item.BoxTreasure.Chest_quest = 1; break;
	}
}

void FillBoxForTreasure(ref item, int i)
{
	// ���������� ���
	switch (i)
	{
		// good
		case 0:
		    if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry2 = 2 + rand(30);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry3 = 10 + rand(3);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry3 = 1 + rand(30);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry5 = 5 + rand(60);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry7 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry10 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry14 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry17 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry18 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral2 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral5 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_2 = 1;
	        }
			GenerateMapsTreasure(item, 35, 70);
	    break;
	    // best
	    case 1:
            if (rand(2) == 1)
	        {
            	item.BoxTreasure.chest = 1 + rand(14);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry12 = 10 + rand(3);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.icollection = 1 + rand(4);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry1 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry12 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry11 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry6 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_3 = 1;
	        }
	    break;
	    // bad
	    case 2:
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.rabble = 5 + rand(100);
	        }
	        else
	        {
                item.BoxTreasure.blade1 = 5 + rand(100);//fix
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade1 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry16 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian4 = 15 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian8 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian16 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.suit_1 = 1;
	        }
	    break;

	    case 3:
	        FillBoxForTreasure(item, 0);
	    break;
	}
}

void FillBoxForTreasureAddition(ref item)
{
    float   nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);

    if (5*nLuck > rand(55))
    {
	    if (GetCharacterItem(Pchar, "map_part1") == 0)
	    {
	        item.BoxTreasure.map_part1 = 1;
	    }
	    else
	    {
	        if (GetCharacterItem(Pchar, "map_part2") == 0)
		    {
		        item.BoxTreasure.map_part2 = 1;
		    }
	    }
	}
	// +1 ����
	switch (rand(40))
	{
		case 1:
		    item.BoxTreasure.STATUE1 = 1;
		break;
		case 2:
		    item.BoxTreasure.jewelry9 = 1;
		break;
		case 3:
		    item.BoxTreasure.jewelry15 = 1;
		break;
		case 4:
		    item.BoxTreasure.jewelry8 = 1;
		break;
		case 5:
		    item.BoxTreasure.indian7 = 1;
		break;
		case 6:
		    item.BoxTreasure.indian2 = 1;
		break;
		case 7:
		    item.BoxTreasure.jewelry4 = 1;
		break;
		case 8:
		    item.BoxTreasure.indian3 = 1;
		break;
		case 9:
		    item.BoxTreasure.indian1 = 1;
		break;
		case 10:
		    item.BoxTreasure.indian5 = 1;
		break;
		case 11:
		    item.BoxTreasure.indian6 = 1;
		break;
		case 12:
		    item.BoxTreasure.indian10 = 1;
		break;
		case 13:
		    item.BoxTreasure.indian12 = 1;
		break;
		case 14:
		    item.BoxTreasure.indian14 = 1;
		break;
		case 15:
		    item.BoxTreasure.indian15 = 1;
		break;
		case 16:
		    item.BoxTreasure.indian17 = 1;
		break;
		case 17:
		    item.BoxTreasure.indian18 = 1;
		break;
		case 18:
		    item.BoxTreasure.indian19 = 1;
		break;
		case 19:
		    item.BoxTreasure.indian20 = 1;
		break;
		case 20:
		    item.BoxTreasure.indian21 = 1;
		break;
		case 21:
		    item.BoxTreasure.indian22 = 1;
		break;
		case 22:
		    item.BoxTreasure.Mineral3 = 1;
		break;
		case 23:
		    item.BoxTreasure.Mineral8 = 1;
		break;
		case 24:
		    item.BoxTreasure.Coins = 1;
		break;
		case 25:
		    item.BoxTreasure.sculMa1 = 1;
		break;
		case 26:
		    item.BoxTreasure.sculMa2 = 1;
		break;
		case 27:
		    item.BoxTreasure.sculMa3 = 1;
		break;
	}
	GenerateMapsTreasure(item, 10, 20);
	//������� ������
	string sName = "Totem_" + (rand(9)+1);
	if (!CheckMainHeroTotem(sName) && rand(20)==1) item.BoxTreasure.(sName) = 1;
}

void FillBoxForTreasureSuper(ref item)
{
    float     nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
	int     i;
	string  itmName;

    if (3*nLuck > rand(21))// ��� ���� ����� 2 �����
    {
		i = 0;
		itmName = "";
		while (itmName == "" && i < 15)
		{
            switch (rand(20))
			{
                case 0:
                	itmName = GetGeneratedItem("blade13");
				break;
				case 1:
        			itmName = GetGeneratedItem("blade20");
				break;
				case 2:
        			itmName = GetGeneratedItem("blade23");
				break;
				case 3:
        			itmName = GetGeneratedItem("blade24");
				break;
				case 4:
        			itmName = "pistol4";
				break;
				case 5:
        			itmName = "indian11";//"idol";
				break;
				case 6:
                    itmName = GetGeneratedItem("topor2"); // to_do
					//itmName = "map_good";
				break;
				case 7:
        			itmName = "spyglass4";
				break;
				case 8:
        			//itmName = "cirass5";
        			itmName = "cirass3";
				break;
				case 9:
        			itmName = "indian11";
				break;
				case 10:
        			itmName = "cirass4";
        			/*if (GetCharacterItem(Pchar, "cirass5") > 0)
        			{
                        itmName = "";
        			} */
				break;

				case 11:
        			itmName = "spyglass5";
				break;
				case 12:
        			itmName = GetGeneratedItem("blade25");
				break;
				case 13:
        			itmName = GetGeneratedItem("blade26");
				break;
				case 14:
        			itmName = GetGeneratedItem("blade30");
				break;
				case 15:
        			itmName = GetGeneratedItem("blade33");
				break;				
				case 16:
        			itmName = "mushket";
				break;					
				case 17:
        			itmName = "Map_Best";
				break;
				case 18:
					itmName = "BackPack5";
					break;
				case 19:
					itmName = "talisman8";
					break;
				case 20:
					itmName = "talisman1";
					break;
			}
			/*if (itmName == "idol" && CheckAttribute(pchar, "QuestTemp.IdolUseYet"))
			{
			    itmName = "";
			} */
			if (GetCharacterItem(Pchar, itmName) > 0)
		    {
          		itmName = "";
		    }
		    i++;
	    }
	    if (itmName != "")
	    {
	        item.BoxTreasure.(itmName) = 1;
	    }
	}
}

void SetTreasureBoxFromMap()
{
    aref   item;
    ref    loc;
    string box;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(Pchar, "map_full")>0 )
    {
        Log_Info("��������� ���-�� �����!");
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(Pchar, "Treasure", 1);
        // ������� ������� �����
        TraderHunterOnMap();
        if( CheckAttribute(Pchar,"location.from_sea") )
        {
            if (rand(2) == 1) //33 ��������
            {
                Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
                Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
                Pchar.quest.SetTreasureHunter.win_condition             = "";
                Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
            }
        }

        Items_FindItem("map_full", &item);

        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; // ������� ��������� � �������

        DeleteAttribute(item, "MapIslId");
        TakeNItems(Pchar, "map_full", -1);
    }
}
//  ����� ��������  ��������� <--

// ������� �� �� �� �����
void  TraderHunterOnMap()
{
    // ������� ������� �����
    ref  sld;
    int  i;

    string sCapId = "Follower0";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true));
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //������ �����
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "����������� �����";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateWarrior("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // ���� ����� ������ ����� � �������� ������
	
    Pchar.GenQuest.Hunter2Pause            = true;
    
    j = GetOfficersQuantity(Pchar) + 2;
    
	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 0, true));
        SetFantomParamHunter(sld); //������ �����
        sld.Dialog.CurrentNode = "TreasureHunter";
        sld.dialog.filename = "Hunter_dialog.c";
        sld.greeting = "Gr_HUNTER";
        sld.location = "none"; // ��� ��� �������� ������!!!!!!!!!!!

        SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
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
        //LAi_Actor2WaitDialog(sld, pchar); // ����� ������, �� ������
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //����� �������
        //#20180912-02 Fix
        PChar.HunterCost.Qty = j; //i;
        PChar.HunterCost.TempHunterType = "";
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}

ref SetFantomSkeletForts(string group, string locator, string enemygroup, string _type)
// _type = "GhostShipCrew"   _type = "ParamHunter"  _type = "none"
{
    string emodel;
    ref    Cr;

    emodel = GetRandSkelModel();

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		if (_type == "GhostShipCrew" || _type == "ParamHunter")
		{
			SetFantomParamHunter(Cr);
		}
		else
		{
		    SetFantomParam(Cr);
		}
		LAi_SetWarriorType(Cr);
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //�� ���������� ������ ��� ����� � �������
	    LAi_LoginInCaptureTown(Cr, true); // ��� ������ ����
	    if (_type == "GhostShipCrew")
	    {
		    // �������� ���� ������ �� ������ ������ Cr.DontClearDead = true;
		    Cr.GhostShipCrew = true;
	    }
    }
    return Cr;
}

///////////////////////////////////////////   ����� �������� ��������� /////////////////////////////////
// ������� ���������
void  GhostShipOnMap()
{
    ref  sld;
    int  i;
    ref  rRealShip;
    
    sld = characterFromID("GhostCapt");
    // ����� ������� � SetBaseShipData DeleteAttribute(sld, "ship.cannons");
    
    SetBaseShipData(sld);
    rRealShip = GetRealShip(sti(sld.Ship.Type));
    rRealShip.ShipSails.SailsColor = argb(255, 60, 60, 60);  // 1.2.3 ��������� ����� ������ �� ���
    
    DeleteAttribute(sld,"ship.sails");
    DeleteAttribute(sld,"ship.masts");
    DeleteAttribute(sld,"ship.blots");

    Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));

    if (CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
    {
		rRealShip.EmblemedSails.normalTex =  "ships\parus_common_torn.tga";

		sld.Ship.Type = GenerateShipExt(SHIP_FLYINGDUTCHMAN, true, sld);
		SetBaseShipData(sld);

        DeleteAttribute(rRealShip, "ShipSails.SailsColor");  // ����� �����

        sld.ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS36;

        Character_SetAbordageEnable(sld, true);
    }
    else
    {
        sld.ship.hp = 52000; // 13 ���������
    }

    SetCrewQuantityOverMax(sld, 666);
    sld.mapEnc.type = "war";
    sld.mapEnc.Name = "������� ���������";
	sld.mapEnc.worldMapShip = "pirates_manowar";

    sld.ship.Crew.Morale = 90;
    ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);

    Fantom_SetBalls(sld, "pirate");
    Fantom_SetCharacterGoods(sld, GOOD_BALLS,  3900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_BOMBS,  2900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_POWDER, 6900 + rand(300), 0);

    LAi_SetCurHPMax(sld); // ���� �� ����
    string sGroup = "Sea_GhostCapt";  // ��������� "Sea_" + �� �����
    Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, "GhostCapt");
    Group_SetGroupCommander(sGroup, "GhostCapt");

    SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);

    Map_CreateWarrior("", "GhostCapt", 3);
    
    Pchar.quest.GhostShip_Dead.win_condition.l1 = "NPC_Death";
	Pchar.quest.GhostShip_Dead.win_condition.l1.character = "GhostCapt";
	Pchar.quest.GhostShip_Dead.win_condition = "GhostShip_Dead";
}

void Survive_In_Sea_Go2Land()
{
    string  sTemp;
    int     iDay;
    ref 	ch;
	int 	n, i, idx;
    int 	storeArray[30];
    int 	howStore = 0;
    
    // ���� ���� ���� � �����������, �� ���������
    iDay = GetPassengersQuantity(pchar);
    i = 0;
    n = 0;
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // ������ ������ � ������� �� ���������, ���� �� ����
		if (idx==-1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // ��������� �� �������
		{
		    ch.LifeDay = 1; // ���� �� ����� �������
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}

	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // �� ������� ��������� � ���
			{
			    ch.LifeDay = 1; // ���� �� ����� �������
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
	
	DeleteAttribute(pchar, "ship");
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	pchar.money = 0;

	SetCharacterShipLocation(pchar, "");

	// ����� ������ ���� �����
    for (n = 0; n < MAX_COLONIES; n++)
	{
  		if (colonies[n].nation == "none") continue; // ����������
  		if (sti(colonies[n].nation) == PIRATE) continue;
  		if (colonies[n].from_sea == "") continue; // ����������
  		if (!CheckAttribute(&Colonies[n], "islandLable") || Colonies[n].islandLable == "Mein") continue; // ������ �������
  		
        storeArray[howStore] = n;
   		howStore++;
    }

    makeref(ch,colonies[storeArray[rand(howStore-1)]]);
    setWDMPointXZ(ch.from_sea);
    pchar.location = ch.from_sea; // ��� ����, ���� ���� �����

    // ����� �������� � �����
    ref loc;
    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
	Pchar.GenQuest.Hunter2Pause = true;
    iDay = 5+rand(17);
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,iDay, rand(10), 1); // ������ �����
    bQuestCheckProcessFreeze = false;
    
	// ����� ������
    pchar.location = SelectSmugglingLocation();
    
    pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*40;
	// ���� ��� � + � - AddCharacterHealth(pchar, -30);
	Log_Info("� ����! � ���!");
	if (sti(PChar.GenQuest.GhostShip.KillMe) <= 1)
	{
		AddQuestRecord("GhostShipQuest", "Survive_1");
	}
	else
	{
	    AddQuestRecord("GhostShipQuest", "Survive_2");
	    // �������� ������� �102
	    if (sti(PChar.GenQuest.GhostShip.KillMe) == 2)
		{
			Log_Info("�� ����� ����� �������� �������.");
			TakeNItems(Pchar, "term_arm", 1);
	    	pchar.QuestTemp.TakeShotgun = true;
	    }
	}
	sGlobalTemp = "afterFDsink";
	bDisableMapEnter           = false;   // ���, ��� ��� � ��
	
	SetLaunchFrameFormParam("������ " + iDay + " ����." + NewStr() +
	                        "������ " + GetConvertStr(ch.islandLable, "LocLables.txt")+","+ NewStr() +
							"" + GetConvertStr(pchar.location, "LocLables.txt") + ".",
						                        "Reload_To_Location", 0.1, 7.0);
    SetLaunchFrameReloadLocationParam(pchar.location, "Smugglers", "Smuggler01", "");
	LaunchFrameForm();
}

void GhostShipInit()
{
	ref sld;
	//============> ������� ��������
	sld = GetCharacter(NPC_GenerateCharacter("GhostCapt", "PotCMobCap", "skeleton", "skeleton", 55, PIRATE, -1, true));
	sld.dialog.filename      = "Quest\GhostShip_dialog.c";
	sld.dialog.currentnode   = "GhostCapt";
	sld.name 	= "�����";
	sld.lastname = "�����";
	sld.reputation = 15;
	LAi_NoRebirthDisable(sld); 
	LAi_RebirthOldName(sld);
	sld.RebirthPhantom     = true;
	sld.AlwaysEnemy        = true;
	sld.DontHitInStorm     = true; // �� �������� � �����
	sld.DontRansackCaptain = true; //��������� �� �������
	sld.SinkTenPercent     = false;  // �� ������ ����� 10 ��������� �������
	sld.Abordage.Enable    = false; // ������ ��������
	sld.SaveItemsForDead   = true; // ��������� �� ����� ����
	sld.cirassId           = Items_FindItemIdx("cirass5");  // �������� ���, �� �������� ����
	sld.AlwaysSandbankManeuver = true;  // ����� ������ ������ �� �����
	sld.GenQuest.CrewSkelMode  = true; // �� �������� �������
	LAi_SetHP(sld, 666, 666);
	SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
    sld.SuperShooter  = true;
    
	DeleteAttribute(sld, "items");
	GiveItem2Character(sld, "topor2");
	EquipCharacterByItem(sld, "topor2");
	GiveItem2Character(sld, "pistol6");
	EquipCharacterByItem(sld, "pistol6");
	TakeNItems(sld, "bullet", 10);
	AddItems(sld, "GunPowder", 10);
	TakeNItems(sld,"potion2", 10);
	sld.money = 70000;
	
//	LAi_SetLoginTime(sld, 6.0, 21.99); // <---  � ��� ��� ��� ������� ���� ? ugeen
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	sld.Ship.Type = CreateBaseShip(SHIP_FLYINGDUTCHMAN);
	sld.Ship.Name = "������� ���������";
	
	ref rRealShip = GetRealShip(sti(sld.Ship.Type));
	//sld.ship.sailscolor = argb(255,60,60,60);
	rRealShip.ship.upgrades.sails = 3;
	rRealShip.EmblemedSails.normalTex =  "ships\parus_common_torn.tga";
	rRealShip.ShipSails.SailsColor = argb(255,60,60,60);
	rRealShip.MaxCaliber = 48;
    rRealShip.Cannon     = CANNON_TYPE_CANNON_LBS48;
    rRealShip.MaxCrew    = 525;
    rRealShip.OptCrew    = 400;
    rRealShip.Capacity   = 5000;
    rRealShip.HP         = 400000;
    rRealShip.WindAgainstSpeed = 10.0;
    rRealShip.SpeedRate	 = 15.0;
	rRealShip.TurnRate   = 60.0;
	rRealShip.Price      = 500000;
	
	pchar.GenQuest.GhostShip.ShipType   = sti(sld.Ship.Type); // ��������, ����� ����������, ����� ����� ����� ������� �� �����
}

// ����� ������� - ����������� �-102 ��������� � ������� �������
void QuestShotgunT102()
{
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("T102", "Terminator", "man", "man", 55, PIRATE, 0, false));
	sld.dialog.filename      = "Quest\T102_dialog.c";
	FantomMakeCoolFighter(sld, 80, 80, 80, "katar", "", 80);
    
    sld.name  = "Terminator";
    sld.lastname = "";
	LAi_SetHP(sld, 1500.0, 1500.0);
	AddBonusEnergyToCharacter(sld, 200);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "SwordplayProfessional");
	
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetActorType(sld);
    LAi_SetActorType(pchar);

	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
}
