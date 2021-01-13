
int igoldpos = 0;
int GoldCapNum  = 0;
string GoldMonth;
bool isGoldFleet = false;



void GoldFleet()
{
    ref sld, chref;
    int iChar = NPC_GenerateCharacter("Head_of_Gold_Squadron", "off_spa_2", "man", "man", 5, SPAIN, 31, true);
    makeref(chref, Characters[iChar]);
    chref.ship.type = GenerateShipExt(SHIP_LINESHIP, 1, chref);
	SetBaseShipData(chref);
    SetCrewQuantityFull(chref);
    Fantom_SetCannons(chref, "war"); //fix
    Fantom_SetBalls(chref, "pirate");
	Fantom_SetGoods(chref, "war");
	SetRandomNameToShip(chref);
	SetFantomParamHunter(chref); //������ �����
    SetCaptanModelByEncType(chref, "war");//
	string sGroup = "Sea_"+chref.id

	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, chref.id);
	Group_SetGroupCommander(sGroup, chref.id);
	SetRandGeraldSail(chref, sti(chref.Nation)); // homo �����
	chref.dialog.filename = "Capitans_dialog.c"; // homo 20/01/07
	chref.dialog.currentnode = "GoldSquadron";
	chref.DeckDialogNode = "GoldSquadron";

	if(!CheckAttribute(pchar, "QuestTemp.GoldFleetMorganaTaken") && rand(3) == 1)
	{
		pchar.QuestTemp.GoldFleetMorganaTaken = true;
		chref.SaveItemsForDead = true;
		chref.DontClearDead = true;
		string sEquipItem = GetGeneratedItem("blade27");
		AddItems(chref, sEquipItem, 1);		
		EquipCharacterbyItem(chref, sEquipItem);
		Log_TestInfo("���� ��� ����� �������� �������� !");
	} 

    int nfreg = (3+rand(1));
    int ngal = (4+rand(1));
    GoldCapNum = nfreg + ngal;

    for(int k = 1; k <=(nfreg + ngal) ; k++)
	{
		iChar = NPC_GenerateCharacter("GoldCap_"+k, "off_spa_2", "man", "man", 5, SPAIN, 31, true);
        makeref(sld, Characters[iChar]);
        if (k <= nfreg)
        {
            sld.Ship.Mode = "war";
            sld.ship.type = GenerateShipExt(SHIP_FRIGATE+rand(1), 1, sld);
    	    SetBaseShipData(sld);
            SetCrewQuantityFull(sld);
            Fantom_SetCannons(sld, "war"); //fix
            Fantom_SetBalls(sld, "pirate");
    	    Fantom_SetGoods(sld, "war");
    	    SetFantomParamHunter(sld); //������ �����
            SetCaptanModelByEncType(sld, "war");//

        }
        else
        {
            sld.Ship.Mode = "trade";
            sld.ship.type = GenerateShipExt(SHIP_GALEON_L+(rand(1)*2), 1, sld);
    	    SetBaseShipData(sld);
            SetCrewQuantityFull(sld);
            Fantom_SetCannons(sld, "war"); // fix
            Fantom_SetBalls(sld, "trade");

            int iSpace = GetCharacterFreeSpace(sld, GOOD_GOLD)
            iSpace = iSpace / 5;
            Fantom_SetCharacterGoods(sld, GOOD_GOLD, ((rand(1)+1)*iSpace), 1);
            Fantom_SetCharacterGoods(sld, GOOD_SILVER, iSpace, 1);
            SetFantomParamHunter(sld); //������ �����
            SetCaptanModelByEncType(sld, "trade");//

        }

        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true; //��������� �� �������
        
        sld.dialog.filename = "Capitans_dialog.c"; // homo 20/01/07
	    sld.dialog.currentnode = "GoldSquadron";
	    sld.DeckDialogNode = "GoldSquadron";
	    
        SetRandomNameToShip(sld);
        Group_AddCharacter(sGroup, sld.id);
	}
	

    chref.AlwaysEnemy = true;
    chref.DontRansackCaptain = true; //��������� �� �������
	chref.mapEnc.type = "trade";
	chref.mapEnc.worldMapShip = "Manowar_gold";
	chref.mapEnc.Name = XI_ConvertString("GoldConvoy");

	string sQuest = "KillHeadGoldFleet";
	pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
	pchar.quest.(sQuest).win_condition.l1.character = chref.id;
	pchar.quest.(sQuest).win_condition = "KillHeadGoldFleet";
    pchar.quest.(sQuest).function= "KillHeadGoldFleet";
}

void KillHeadGoldFleet(string temp)
{
	isGoldFleet = false;
	Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");
	
}

void GoldFleetEncounter(string temp)
{
    string sQuest = "LeaveGoldleet";
    pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
    pchar.quest.(sQuest).win_condition = "LeaveGoldleet";
    pchar.quest.(sQuest).function = "LeaveGoldleet";
}

void LeaveGoldleet(string temp)
{

    if ( isGoldFleet )
    {
        if (NumDeadCapitan() > 0)
        {
            //������ ��������
            DefeatRumour(1);
            AddQuestRecord("Rumour_GoldFleet", 13+rand(2));
        }
        else
        {
            // ������ �� �������
            isGoldFleet = true;
        
        }
        if ( temp == "CheckHavanaGoldFleet" )
        {
               string sQuest = "HeadGoldFleetInHavana";
               pchar.quest.(sQuest).win_condition.l1 = "location";
               pchar.quest.(sQuest).win_condition.l1.location = "Cuba2";
               pchar.quest.(sQuest).function= "GoldfleetInHavana";
               Log_TestInfo("GoldFleet in Havana");


        }
        return;
    }
    else
    {
        // ������ �����
        Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");
    	igoldpos = 0;
    	DefeatRumour(0);
    	DefeatGoldFleet("");
    }


}

void DefeatGoldFleet(string temp)
{
    string Text;
    ref rParams;
    Group_DeleteGroup("Sea_Head_of_Gold_Squadron");
    AddQuestRecord("Rumour_GoldFleet", 4+rand(2));
    CloseQuestHeader("Rumour_GoldFleet");
    Pchar.quest.EndOfGoldFleet.over = "yes";
    Pchar.quest.HeadGoldFleetInHavana.over = "yes"; //fix
    Pchar.quest.CheckHavanaGoldFleet.over = "yes"; //fix
    Pchar.quest.LeaveGoldleet.over = "yes"; //fix
    Pchar.GoldfleetInHavana.over = "yes"; //fix
    isGoldFleet = false;
    Log_TestInfo("Defeat GoldFleet");
}

void RouteGoldFleet()
{
    ref sld;
    if (isGoldFleet==true)
    {
        switch (igoldpos)
        {
            case 0 :
                int hvx = worldMap.islands.Cuba2.Havana_town.position.x;
    	        int hvz = worldMap.islands.Cuba2.Havana_town.position.z;
                Map_CreateTraderXZ(-858.089, 897.072, hvx, hvz, "Head_of_Gold_Squadron", 3);
                Log_TestInfo("GoldFleet is near of Havana");
            break;

            case 1 :
                ClearIslandShips("Havana");
                Colonies[FindColony("Havana")].DontSetShipInPort = true;
                sld = CharacterFromID("Head_of_Gold_Squadron"); //�� �������� � ������ ������ ������������� =)
                DeleteAttribute(sld, "AlwaysEnemy");
                for(int k = 1; k <= GoldCapNum ; k++)
                {
                    sld = CharacterFromID("GoldCap_"+k);
                    DeleteAttribute(sld, "AlwaysEnemy");
                }                                        //
                Group_SetAddress("Sea_Head_of_Gold_Squadron", "Cuba2", "Quest_ships", "reload_fort1_siege");//fix 1
                string sQuest = "HeadGoldFleetInHavana";
                pchar.quest.(sQuest).win_condition.l1 = "location";
                pchar.quest.(sQuest).win_condition.l1.location = "Cuba2";
                pchar.quest.(sQuest).function= "GoldfleetInHavana";
                Log_TestInfo("GoldFleet in Havana");
                igoldpos = 0;
                return;
            break;

        }
        igoldpos++;
    }
}

void GoldfleetInHavana(string temp)
{
	 string sQuest = "CheckHavanaGoldFleet";
	 pchar.quest.(sQuest).win_condition.l1 = "MapEnter";
	 pchar.quest.(sQuest).win_condition = "LeaveGoldleet";
	 pchar.quest.(sQuest).function = "LeaveGoldleet";
}

void EndOfGoldFleet(string temp)
{
    string Text;
    string sGroupID = "Sea_Head_of_Gold_Squadron";
    Log_TestInfo("Complited GoldFleet "+NumDeadCapitan());
    Map_ReleaseQuestEncounter("Head_of_Gold_Squadron");
    Group_SetAddressNone(sGroupID);
    CloseQuestHeader("Rumour_GoldFleet");
    Group_DeleteGroup(sGroupID);
    Pchar.quest.HeadGoldFleetInHavana.over = "yes";
    Pchar.quest.CheckHavanaGoldFleet.over = "yes"; //fix
    Pchar.quest.LeaveGoldleet.over = "yes"; //fix
    Pchar.GoldfleetInHavana.over = "yes"; //fix
    igoldpos = 0;
    isGoldFleet = false;
    DeleteAttribute (&colonies[FindColony("Havana")], "DontSetShipInPort"); //���������� �����

}
void StartGoldFleet(string temp);
{
    if (Colonies[FindColony("Havana")].nation == SPAIN && Colonies[FindColony("PortoBello")].nation == SPAIN
    && !CheckAttribute(Colonies[FindColony("Havana")], "Siege") && !CheckAttribute(Colonies[FindColony("PortoBello")], "Siege"))
    {
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
            igoldpos = 0;
    }
}

void EndTime_GoldFleet(int nid)
{
    ref Prm, CurTpl;
    aref varARef;
    int ind = FindRumour(nid);
    if (ind != -1)
    {
        makeref(Prm, Rumour[ind]);
        int tNum = TplNameToNum("End_GoldFleet");
        makeref(CurTpl,  templat[tNum]);
        int StartNext =(sti(Prm.starttime) + 21)
        if ( StartNext > DateToInt(0))
        {
            CurTpl.starttime =  (StartNext - DateToInt(0));
            CurTpl.actualtime = (sti(CurTpl.actualtime)+ sti(CurTpl.starttime));
        }
    }
}

int NumDeadCapitan()
{
    int rez = 0

    //for(int k = 1; k <= GoldCapNum ; k++)
    //{
    //   if (GetCharacterIndex("GoldCap_"+k) == -1 || CharacterIsDead(CharacterFromID("GoldCap_"+k))) rez++;
    //}
    rez = GoldCapNum + 1 - Group_GetLiveCharactersNum("Sea_Head_of_Gold_Squadron");
    Log_TestInfo(GoldCapNum +" | "+rez);
    GoldCapNum = GoldCapNum - rez;
    return rez;
}

void DefeatRumour(int noall)
{
    ref CurrentRumour;
    string tid;
    int lngFileID = LanguageOpenFile("RumourTexts.txt");
    
    

    for(int Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
    {
        makeref(CurrentRumour, Rumour[Rumour_Index]);
        if ( CheckAttribute(CurrentRumour, "Name") && CurrentRumour.Name == "End_GoldFleet")
        {
            if (noall != 0)
            {
                tid = "Defeat_GoldFleet_t"+rand(2);
                CurrentRumour.text = LanguageConvertString(lngFileID, tid);
            }
            else
            {
                tid = "Attak_GoldFleet_t"+rand(2);
                CurrentRumour.text = LanguageConvertString(lngFileID, tid);

            
            }
            DeleteAttribute (CurrentRumour, "loginfo");
            return;
        }
        if (CurrentRumour.next == "End_GoldFleet" || CurrentRumour.next == "Attak_GoldFleet" )
        {
            if (noall == 0) CurrentRumour.next = "Defeat_GoldFleet";
            else CurrentRumour.next = "Attak_GoldFleet";
            DeleteAttribute (CurrentRumour, "nonation");
            DeleteAttribute (CurrentRumour, "loginfo");
            return;
        }
        
    }

}

//OnInit_GoldFleet
void OnInit_GoldFleet(ref rTmpl)
{
    object Prm;
    string tresult;
    aref varARef;
    Prm.gold_month = GoldMonth;
    makearef(varARef, Prm);
    tresult += GetAssembledString( ttttstr,	varARef);
    ttttstr = tresult;
}