//ugeen 12.01.10 --> ��������� ���� ��� �������, ����� ��� ���� �����������
string GenQuest_GenerateGoodBlade() // ��������� ������� ������� ��� ������ � ��������
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = GetGeneratedItem("blade19"); // "��������"
		break;
		case 1:
			itemID = GetGeneratedItem("blade22"); // "���. ������"
		break;
		case 2:
			itemID = GetGeneratedItem("blade31"); //  "������"
		break;
		case 3:
			itemID = GetGeneratedItem("blade34"); // "�������"
		break;
		case 4:
			itemID = GetGeneratedItem("blade15"); // "������"
		break;
		case 5:
			itemID = GetGeneratedItem("blade21"); // "�������"
		break;
	}
	return itemID;
}

string GenQuest_GenerateBestBlade() // ��������� �������� ������� ��� ������ � ��������
{
	string itemID;
	switch(rand(10))
	{
		case 0:
			itemID = GetGeneratedItem("blade13"); // "���������"
		break;
		case 1:
			itemID = GetGeneratedItem("blade13"); // "���������"
		break;
		case 2:
			itemID = GetGeneratedItem("blade20"); // "�������"
		break;
		case 3:
			itemID = GetGeneratedItem("blade23"); //  "������"
		break;
		case 4:
			itemID = GetGeneratedItem("blade24"); // "�������"
		break;
		case 5:
			itemID = GetGeneratedItem("blade24"); // "�������"
		break;
		case 6:
			itemID = GetGeneratedItem("blade25"); // "��������"
		break;
		case 7:
			itemID = GetGeneratedItem("blade26"); // "������������"
		break;
		case 8:
			itemID = GetGeneratedItem("blade30"); // "������"
		break;
		case 9:
			itemID = GetGeneratedItem("blade33"); // "���������� �����"
		break;		
		case 10:
			itemID = GetGeneratedItem("blade24"); // "�������"
		break;		
	}	
	return itemID;
}

string GenQuest_GenerateArtefact() // ���������
{
	string itemID;
	switch(rand(17))
	{
		case 0:
			itemID = "indian1";
		break;
		case 1:
			itemID = "indian2"; 
		break;
		case 2:
			itemID = "indian3"; 
		break;
		case 3:
			itemID = "indian5"; 
		break;
		case 4:
			itemID = "indian7"; 
		break;
		case 5:
			itemID = "indian7"; 
		break;
		case 6:
			itemID = "indian10"; 
		break;
		case 7:
			itemID = "indian12"; 
		break;
		case 8:
			itemID = "indian12"; 
		break;
		case 9:
			itemID = "indian14"; 
		break;
		case 10:
			itemID = "indian14"; 
		break;
		case 11:
			itemID = "indian17"; 
		break;
		case 12:
			itemID = "indian17"; 
		break;
		case 13:
			itemID = "indian2"; 
		break;
		case 14:
			itemID = "indian19"; 
		break;
		case 15:
			itemID = "indian22"; 
		break;		
		case 16:
			itemID = "indian6"; 
		break;	
		case 17:
			itemID = "indian15"; 
		break;			
	}
	return itemID;
}

string GenQuest_GenerateTotem() // ������ ��� ��������
{
	string itm;
	for(int i = 1; i <= 10; i++)
	{
		if(!CheckMainHeroTotem("Totem_" + i) && rand(15) == 1) 
		{ 
			itm = "Totem_" + i; 	
			return itm; 
		} 	
	}
	
	if(rand(12) > 2) itm = GenQuest_GenerateArtefact();
	else			 itm = GenQuest_GenerateBestBlade();
	return itm;
}

string GenQuestCommon_GenerateItem()
{
	string itm;
	if(rand(1) == 0) itm = GenQuest_GenerateTotem();
	else
	{
		if(rand(1) == 0 )
		{
			if (GetCharacterItem(pchar, "map_full") == 0) 
			{
				if (GetCharacterItem(pchar, "map_part1") == 0) { itm = "map_part1"; }
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0) { itm = "map_part2"; }
					else itm = GenQuest_GenerateGoodBlade();
				}
			} 					
		}
		else itm = GenQuest_GenerateGoodBlade();
	}
	return itm;
}

string GenQuest_GetQuestTreasureMapDescription(ref itmRef) // ������� �� ��������� �����
{
	string MapDescription;
	int i;

	i = FindLocation(itmRef.MapLocId);  // ���� �����
	if (i != -1 && locations[i].islandId != "Mein")
	{
		string MapLocation = GetConvertStr(locations[i].islandId, "LocLables.txt");
		MapDescription = GetConvertStr("type_quest_0_isl", "MapDescribe.txt") + " " + MapLocation;
	}
	else
	{
		MapDescription = GetConvertStr("type_quest_0_mein", "MapDescribe.txt");
	}
	itmRef.MapIslName = MapDescription;
	
	MapDescription = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
	itmRef.MaplocName = MapDescription;

	MapDescription = itmRef.MapOwnId;
	itmRef.MapOwner = MapDescription;	
		
	MapDescription = GetConvertStr("type_quest_0", "MapDescribe.txt");
	MapDescription = GetAssembledString(MapDescription, itmRef);
	
	itmRef.MapDescription = MapDescription; 
	return MapDescription;   	
}

