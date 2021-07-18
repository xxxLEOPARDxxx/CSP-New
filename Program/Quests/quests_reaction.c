
void QuestComplete(string sQuestName, string qname)
{
	// Lugger -->
	int iBuild = rand(3) + 3;
	// Lugger <--
	// boal -->
	ref sld, npchar;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, ShipType, Rank, iRank; // ����� ��� ���������� ����� ����� (�����)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // ����� ������ ��� ����������
	bool   bOk;
	int iChurchGenBanditsCount;

	//#20190329-01
	iTemp = 10;
	//Boyer mod
    float nTimeAdd;

	if (bQuestLogShow)
    {
	    Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}

	switch(sQuestName)
	{	
		// boal -->
		// ����� ��������� �� �������
        // boal ��� ������ ����������� 15-25 ���� ��� ������� ��������� ���� = ��������� � 5 ��������� - ����(100) > 95
        case "Nation_Legend":
            SetTimerCondition("Nation_Legend", 0, 0, 15+rand(10), true);
			// ��� ����� ������������ -->
			if (!bSeaActive && !bAbordageStarted)
            {
              //  RepairAllDefenderFortShips();
            }
            // ��� ����� ������������ <--
            if (rand(100) > 93 && !bWorldAlivePause)
            {
                if(IsEntity(worldMap))
                {
                    LaunchNationLegend();
                }else{
                    if (!bQuestCheckProcessFreeze) // ����� ��������
					{
					    DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
	      				Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
	                    Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
			        }
                }
        	}
        break;

        case "Nation_Legend_Map":
            if (!bQuestCheckProcessFreeze) // ����� ��������
			{
                LaunchNationLegend();
            }else{
                Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
                Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
            }
        break;
		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz)); 
		break;
		// ������ ����, ��������
		case "Tut_StartGame_CheckMinHP_1":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			bOk = false;
			if (sti(pchar.HeroParam.Teach_beat) == 1 && sti(pchar.HeroParam.Teach_battle) == 1)
			{
				bOk = true;
			}
			else
			{
				if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
				{
					bOk = true;
					pchar.HeroParam.Teach_beat = 3; // �������, ��� �������
				}
			}
			if (bOk)
			{
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_2":
        	if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_2");
   			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
			{
				sld = characterFromID("Sailor_1");
				LAi_SetActorTypeNoGroup(sld);
				pchar.HeroParam.Teach_beat = 3; // �������, ��� �������
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_Hero":
        	// ������ �������
        	LAi_SetActorTypeNoGroup(pchar);
        	sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
            PChar.GenQuest.CallFunctionParam = "Tut_StartDialog";
			DoQuestCheckDelay("CallFunctionParam", 2.0);
        break;
		//  ����� ��������  ��������� -->
        case "SetTreasureFromMap":
            SetTreasureBoxFromMap();
        break;
        //  ����� ��������  ��������� <--
        
		case "ArestInResidenceEnd":
            //LAi_LocationFightDisable(&Locations[FindLocation(Pchar.quest.ArestInResidenceEnd.ResidenceLocation)], true);
		    LAi_LockFightMode(Pchar, false); // ������� ������
        break;
        // ����
        case "Battle_Hunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            //LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            //#20190708-01
            LAi_group_SetCheck("LAND_HUNTER", "LandHunter_Afterword");
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("ENGLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			LAi_group_SetRelation("FRANCE_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			LAi_group_SetRelation("SPAIN_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//������ ������ ������� �� ���
			LAi_group_SetRelation("HOLLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//04.03 fix Lipsar ������ ������ ������ ��, ����� ��� ���� ��������
        break;
		case "Battle_PGGHunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            if (i == 1)
				{
					sld = characterFromID(pchar.chosenTreasureHero);
					DeleteAttribute(pchar,"chosenTreasureHero");
				}
				else
				{
					sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				}
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            //LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            //#20190708-01
            LAi_group_SetCheck("LAND_HUNTER", "LandHunter_Afterword");
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
			//LAi_group_SetRelation("ENGLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			//LAi_group_SetRelation("FRANCE_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);
			//LAi_group_SetRelation("SPAIN_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//������ ������ ������� �� ���
			//LAi_group_SetRelation("HOLLAND_CITIZENS",LAI_GROUP_PLAYER,LAI_GROUP_FRIEND);//04.03 fix Lipsar ������ ������ ������ ��, ����� ��� ���� ��������
        break;
        //#20190708-01
        case "LandHunter_Afterword":
		    LAi_group_SetAlarm("LAND_HUNTER", LAI_GROUP_PLAYER, 0.0);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"ENGLAND_CITIZENS",LAI_GROUP_NEITRAL);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"FRANCE_CITIZENS",LAI_GROUP_NEITRAL);//������ ������ �� ��� �� ���������� ����
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"SPAIN_CITIZENS",LAI_GROUP_NEITRAL);
			LAi_group_SetRelation(LAI_GROUP_PLAYER,"HOLLAND_CITIZENS",LAI_GROUP_NEITRAL);
		break;
        case "GoAway_Hunters_Land":
            //LAi_SetActorType(Pchar);
            //DoQuestCheckDelay("pchar_back_to_player", 4.0);
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				//LAi_RemoveCheckMinHP(sld);  ����� �������� � �����, ����� �� ���� ����� ���
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
		case "GoAway_PGGHunters_Land":
            //LAi_SetActorType(Pchar);
            //DoQuestCheckDelay("pchar_back_to_player", 4.0);
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            if (i == 1)
				{
					sld = characterFromID(pchar.chosenTreasureHero);
					DeleteAttribute(pchar,"chosenTreasureHero");
				}
				else
				{
					sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				}
				//LAi_RemoveCheckMinHP(sld);  ����� �������� � �����, ����� �� ���� ����� ���
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
        //#20190804-01
        case "genericAlarmDown":
            if(CheckAttribute(pchar, "tmpKillGroup")) {
                LAi_group_SetAlarm(pchar.tmpKillGroup, LAI_GROUP_PLAYER, 0.0);
                DeleteAttribute(pchar, "tmpKillGroup");
            }
        break;
        
		// ������� ��������!
        case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
            iTemp = NPC_GeneratePhantomCharacter("citizen", sti(sld.Nation), MAN, -1);  // ������� ����
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                if (CheckAttribute(sld, "PGGAi"))
	            {
	            	sTemp = npchar.id; // ����� ��������� ��
					DeleteAttribute(npchar, "");// ��� ����, � ��� � �����!
					CopyAttributes(npchar, sld);
					if (CheckAttribute(sld,"PerkValue.HPPlus")) npchar.PerkValue.HPPlus = 0;
	
					npchar.index = iTemp;
					// �������� ��, ������ ������, ����� �����
					sld.id = sTemp; //navy (��� fix) 26.12.06
					// ��� ���� ������������ ����� � ������� 290704 BOAL -->
					DeleteAttribute(npchar, "Ship");
					npchar.ship.type = SHIP_NOTUSED;
                    npchar.location = "none";
                    npchar.location.from_sea = "";
					
					DeleteAttribute(npchar, "Fellows"); // ��� �������
					// ��� � �������� ���
					sld.LifeDay = 0;
                    DeleteAttribute(sld, "PGGAi");
	            }
	            else
	            {
	                ChangeAttributesFromCharacter(npchar, sld, true);
	                
	    			sld.location = "none";
	    			sld.location.from_sea = "";
    			}
    			PlayVoice("interface\_EvShip1.wav");
    			LAi_SetCurHPMax(npchar);
    			AddPassenger(Pchar, npchar, false);
    			Log_Info("������ " + GetFullName(npchar) + " �������� �� ����.");
            }
        break;
		case "Get_TreasureBarrel":
			Set_TreasureBarrel();
		break;
        // ����� ��������� �� ������� homo
        case "Survive_In_SeaPrisoner":  //homo 22/06/07
            sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
            iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                PlayVoice("interface\_EvShip1.wav");
                // ������, ����� ��� � ��� ��� if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (��� fix)
                LAi_SetCurHPMax(npchar);
				//������ ����� ��������� ��� ����������
				if (!IsCharacterPerkOn(npchar, "Grunt") && !IsCharacterPerkOn(npchar, "Trader") && !IsCharacterPerkOn(npchar, "Fencer") && !IsCharacterPerkOn(npchar, "Buccaneer") && !IsCharacterPerkOn(npchar, "Agent") && !IsCharacterPerkOn(npchar, "SeaWolf"))
					SetCharacterPerk(npchar, PerksChars());
    			sld.location = "none";
    			sld.location.from_sea = "";
                Log_Info(GetFullName(npchar) + " ������ � ����.");
            }
        break;
        //  ��
        case "Survive_In_Sea":
            DeleteSeaEnvironment();
            PChar.GenQuest.GhostShip.KillMe      = sti(PChar.GenQuest.GhostShip.KillMe) + 1;
            PChar.GenQuest.GhostShip.AskAbout    = 2; // ����� �����
            Survive_In_Sea_Go2Land();
        break;
        case "GhostShip_Start":
			AddQuestRecord("GhostShipQuest", "3_1");
			n = FindIsland("KhaelRoa");
			Islands[n].alwaysStorm = true;
			Islands[n].storm = true;
			Islands[n].tornado = true;
			pchar.GhostCap.Fight = true;
			if (!CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle")) Pchar.Abordage.Enable = false;
			break;
        case "GhostShip_Dead":
            if (CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
            {
                Log_Info("������� ���������, ������ �� �� ��������.");
                AddQuestRecord("GhostShipQuest", "Dead_2");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","�"));
                CloseQuestHeader("GhostShipQuest");

                AddCharacterExpToSkill(PChar, "Leadership", 300);
    		    AddCharacterExpToSkill(PChar, "Sailing", 500);
    		    AddCharacterExpToSkill(PChar, "Accuracy", 500);
    		    AddCharacterExpToSkill(PChar, "Cannons", 500);
    		    AddCharacterExpToSkill(PChar, "Repair", 500);
    		    AddCharacterExpToSkill(PChar, "Defence", 500);
    		    AddCharacterExpToSkill(PChar, "Sneak", 300);
    		    PChar.GenQuest.GhostShip.LastBattleEnd = true;
    		    // ������ ����� � �������, ���� ������� ���� ��
				sld = GetRealShip(sti(pchar.GenQuest.GhostShip.ShipType));
				DeleteAttribute(sld, "EmblemedSails.normalTex");
				AddSimpleRumourTip(LinkRandPhrase("�, ����� ���� �����! ��� �� � ���� "+ GetSexPhrase("��� ����� �������","�� �������") +", ��� ����"+ GetSexPhrase("","�") +" '�������� ���������'?! ������� ���� ����! �������, ��������, ���� �������! �������, ������ �������, ��� ��� ������ ������� ����� ������ � ����� ������� ��������? � � ������� � ���� ���� ������ ��������� � ����������� �������� ������, ���������� ������ ����� �����?",
					"�������, � �� ����� ������ ��������! ����� �����, ��� ��� �� �������� ������� ����� ������ � ������� ��� ���������. ��� �� ��� ��������, ��� '������� ���������' ���������� ���� ���������! �������� �������, ��� �� ������... ��� � ��� ����� �������� � ���� ���� ����� ������, ��-��. ������ �� �� �� �����, ������� ����� ������ ��� � ����� �������...",
					"�������, ��� '������� ���������' - ���� ���������� � ���������� �������� ���� ������� ������, ����� ���� �����? � �������� - �� ������ �������� �����! ������ �, ���� ������� ���� ��������� ��������� � ���� ������� ������� ������, ��� �������� �����... ��� ���-��, � �����, ��������� � ����������� ���������� ������������ �������-��������."), 
					60, 5, "habitue", "");	
            }
            else
            {
                Log_Info("������� ���������, �� ����� �� �� ���������?");
                AddQuestRecord("GhostShipQuest", "Dead_1");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("��","���"));
                AddCharacterExpToSkill(PChar, "Leadership", 600);
    		    AddCharacterExpToSkill(PChar, "Sailing", 1000);
    		    AddCharacterExpToSkill(PChar, "Accuracy", 1000);
    		    AddCharacterExpToSkill(PChar, "Cannons", 1000);
    		    AddCharacterExpToSkill(PChar, "Repair", 1000);
    		    AddCharacterExpToSkill(PChar, "Defence", 1000);
    		    AddCharacterExpToSkill(PChar, "Sneak", 500);
    		    PChar.GenQuest.GhostShip.DeadByMe = sti(PChar.GenQuest.GhostShip.DeadByMe) + 1;
    		    PChar.GenQuest.GhostShip.AskAbout    = 2; // ����� �����

    		    /*PChar.GenQuest.VideoAVI        = "Ending";
                PChar.GenQuest.VideoAfterQuest = "";

                DoQuestCheckDelay("PostVideo_Start", 0.1); */
            }
			n = FindIsland("KhaelRoa");
			DeleteAttribute(&Islands[n], "alwaysStorm");
			DeleteAttribute(&Islands[n], "storm");
			DeleteAttribute(&Islands[n], "tornado");
			DeleteAttribute(&Islands[n], "QuestlockWeather");
			DeleteAttribute(&Islands[n], "MaxSeaHeight");
			Pchar.Abordage.Enable = true;
			DeleteAttribute(pchar,"GhostCap.Fight");
        break;
        
		case "GhostCapt_OfferPrize":
			Sea_CabinStartNow();
			pchar.quest.GhostShipCapInCabin.win_condition.l1          = "location";
			pchar.quest.GhostShipCapInCabin.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.GhostShipCapInCabin.win_condition             = "GhostShipCapInCabinOffer";					
		break;
		
		case "GhostShipCapInCabinOffer":
			chrDisableReloadToLocation = true;
			LAi_LockFightMode(pchar, true);	
			sld = CharacterFromID("GhostCapt");
			sld.dialog.currentnode = "GhostCapt_Prize";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "GhostShipCapInCabinDied":
			sld = CharacterFromID("GhostCapt");
			LAi_SetCurHP(sld, 0.0);
		break;
		
        case "GhostShipHelp": // ����� � �����
            chrDisableReloadToLocation = true;
            Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // �� ����� ����! :(
            for (i = 0; i < MAX_TOWN_CREW; i++)
            {
				sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
                    sTemp = "rld";
					sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
            }
            // ����
            Pchar.GenQuestFort.FarLocator = false;
            // ������ �������
            iTemp = sti(Characters[GetCharacterIndex(pchar.GenQuest.GhostShipWorkId)].nation);

            for (i = 0; i < MAX_ESCADRA_CREW; i++) //������ 5 ����
            {
            	SetFantomDefenceForts("goto", "", iTemp, LAI_GROUP_PLAYER);
            }
            //#20190505-03
            int nTmpEsc = makeint(MOD_SKILL_ENEMY_RATE);
            for (i = 0; i < nTmpEsc; i++)
            {
            	SetFantomDefenceForts("goto", "", iTemp, LAI_GROUP_PLAYER);
            }
            // ��������
            LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
            LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
            LAi_SetFightMode(Pchar, true);
        break;

		case "GhostShipHelp_Finish":
            LAi_SetFightMode(Pchar, false);
            LAi_grp_alarmactive = false; // ����� �������
            //#20190505-03
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, "TOWN_BATTLE_SOLDIERS", 0.0);
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, "SKEL_BATTLE_SOLDIERS", 0.0);
            if (!CheckAttribute(pchar , "GenQuest.GhostShip.ChurchHelpStart"))
            {  // �����
                sTemp = "GhostShipDone_" + pchar.GenQuest.GhostShipWorkId;
                pchar.GenQuest.(sTemp) = true;
                Log_Info("�� ��������!");
                Statistic_AddValue(Pchar, "QuestGhostShipHelp_Done", 1);
                AddQuestRecord("GhostShipQuest", "help_t2");
            }
            else
            { // �����
                pchar.GenQuest.GhostShip.ChurchHelp = true;
                Log_Info("������� ������ ���������!");
                DeleteAttribute(pchar , "GenQuest.GhostShip.ChurchHelpStart")
                //AddQuestTemplate("GhostShipQuest", "church_t2");
                Statistic_AddValue(Pchar, "QuestChurchHelpGhostShip_Done", 1);
            }
            PlaySound("interface\door_locked.wav");
            chrDisableReloadToLocation = false;
            bDisableFastReload         = false;
            SetLocationCapturedState(pchar.location, false);
        break;
        // ������ ������
        case "GhostShipChurchShorePlace":
            Pchar.GenQuest.Hunter2Pause            = true;

            Pchar.GenQuest.GhostShip.ChurchHelpStart = true;

            chrDisableReloadToLocation = true;
            Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // �� ����� ����! :(
            iTemp = 3 + rand(4);
            for (i = 0; i < iTemp; i++)
            {
				sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
                    sTemp = "reload"; // ������ - ����� ���� �����!
					sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
            }
            Pchar.GenQuestFort.FarLocator = false;

            // ��������
            LAi_group_SetHearRadius("SKEL_BATTLE_SOLDIERS", 100.0);
            LAi_group_FightGroupsEx("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck("SKEL_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
            LAi_SetFightMode(Pchar, true);
        break;
        // GhostShipHelp <--
		////////////////////////////////////����� ������� �� ������///////////////////////////////////////////////////////
        case "SeaHunterCheck":
            SeaHunterCheck();
        break;

		case "CheckMaxHealthQuest":
            SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
            SetNewDayHealthMax();
        break;
        
		case "My_Deck_Battle_End":  // ������ ���� � ����� -����� ����� �������
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], true);
            LAi_SetFightMode(Pchar, false);
        break;
		//  boal 290804 ��������� ������ ����� -->
        case "PunishmentAction":
            LAi_SetActorTypeNoGroup(PChar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
			LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToCharacter(pchar, sld);
            LAi_ActorAnimation(pchar, "attack_force_3", "", 0.9);
            DoQuestCheckDelay("PunishmentAction_1", 0.5);
         break;

         case "PunishmentAction_1":
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            LAi_ActorAnimation(sld, "hit_attack_2", "PunishmentAction_2", 0.6);
         break;

         case "PunishmentAction_2":
            Lai_SetPlayerType(pchar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            switch (pchar.GenQuest.PunishmentActionManType)
            {
                case "LAi_SetHuberStayType":
                    LAi_SetHuberStayTypeNoGroup(sld);
                    break;

                case "LAi_SetStayType":
                    LAi_SetCitizenTypeNoGroup(sld);
                    break;
            }
		break;
		//  boal 290804 ��������� ������ ����� <--
		// ������������ -->
		case "donation":
			int iDonation = makeint(pchar.questTemp.donate);
			int iRep      = makeint(pchar.reputation);
			int iRepIncr;
			if (iRep <10)
			{
				if (iDonation >= 1000)
				{
					iRepIncr = iDonation / 1000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep < 20 && iRep >= 10)
			{
				if (iDonation >= 2000)
				{
					iRepIncr = iDonation/2000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <30 && iRep >=20)
			{
				if (iDonation >= 3000)
				{
					iRepIncr = iDonation/3000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <40 && iRep >=30)
			{
				if (iDonation >= 4000)
				{
					iRepIncr = iDonation/4000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <50 && iRep >=40)
			{
				if (iDonation >= 5000)
				{
					iRepIncr = iDonation/5000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <60 && iRep >=50)
			{
				if (iDonation >= 6000)
				{
					iRepIncr = iDonation/6000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <70 && iRep >=60)
			{
				if (iDonation >= 7000)
				{
					iRepIncr = iDonation/7000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <80 && iRep >=70)
			{
				if (iDonation >= 8000)
				{
					iRepIncr = iDonation/8000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep < REPUTATION_MAX && iRep >=80)
			{
				if (iDonation >= 10000)
				{
					iRepIncr = iDonation/10000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
		break;
	    // ������������ <--
		case "SetNPCInShipDeck":  // ����� ������ ������ �������
            if (Pchar.location == Get_My_Cabin())//"My_Cabin" || Pchar.location == "My_Cabin_Small")
	        {
                SetOfficersInCabin();
            }
            else
            {
                if (Pchar.location == "My_Deck")// ����
                {
                    SetPrisonerInHold();
                }
                else
                {
	                if (Pchar.location == "My_Campus")// ����-��������
	                {
	                    SetOfficersInCampus();
	                }
                }
            }
        break;
        
		case "SetQuestHoldBox":
			if (Pchar.location == "My_Deck")// ����
            {
                FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
            }
		break;
		
        case "Munity_on_Ship_Map":
            if (IsEntity(worldMap) && GetCrewQuantity(pchar) > 0)
        	{
                MunityOnShip("ShipMunity");
            }
        break;

        case "Munity_on_Ship":
            pchar.quest.Munity = "";
            pchar.GenQuest.MunityStart = true;
            PlayVoice("INTERFACE\_GTMutiny_"+rand(2)+".wav");
            InterfaceStates.Buttons.Save.enable = 0;
            LAi_SetFightMode(Pchar, true);

            if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
                    if (i >= (sti(PChar.Ship.Crew.Quantity)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterCrew(PChar, (8-GetCharacterShipClass(PChar))*8);
                }
                PChar.Ship.Crew.Morale = 25;
                ChangeCrewExp(PChar, "Soldiers", 2); // ����� �� ����������
            }
            else
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
                    if (i >= (GetCargoGoods(PChar, GOOD_SLAVES)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (8-GetCharacterShipClass(PChar))*8);
                }
                DeleteAttribute(pchar, "GenQuest.SlavesMunity");
                ChangeCrewExp(PChar, "Soldiers", 3); // ����� �� ����������
            }
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
        break;

        case "Dead_Munity":
		if (Pchar.questTemp.MunityOfficerIDX.begin == "1")
		{
			Log_SetStringToLog("������� ���� ����������� ���������� � ��������� ������� �����������");
			Pchar.questTemp.MunityOfficerIDX.begin = "0";
		}
		else Log_SetStringToLog("��������� ���� ���������");
            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_group_SetAlarm(LAI_GROUP_PLAYER, LAI_GROUP_TmpEnemy, 0.0);
            LAi_SetFightMode(Pchar, false);
            DeleteAttribute(pchar, "GenQuest.MunityStart");
        break;
        
		///  ������ ����� - �����
        case "FreeCaptureForts": // ������ ������, ������� ����� (�� ���� ������) ��� ������ �� �����
            TWN_FreeCaptureForts();
        break;
        // ������ � ���� �� ������� ���� (��������)
        case "Town_Capture_Land":
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            //Pchar.GenQuestFort.SoundOff = true;
            DeleteQuestAttribute("Union_with_Escadra");

            SetLocationCapturedState(sld.Default, true);

            DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
        break;
        
        case "Capture_Town_Siege":
            PrepareTownBattle(); // ��� ������ ������� ��� ����� ������

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
            	PlayVoice("INTERFACE\_GTTown2.wav");
            	AddCharacterExpToSkill(Pchar, "Leadership", 100);
			    AddCharacterExpToSkill(Pchar, "Sneak", 100);
            }
            else
            {
                DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
            }
        break;
        // ����������� ������������ ������ ������� // boal ��������� 251204
        case "Return_Gover_Dialog":
            Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
        break;

        case "Return_Gover_Dialog_Exit":
            DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
        break;
        // ����� ����� � ����� ����
        case "Capture_Forts":
            TWN_Capture_Forts();
        break;

        case "FightInTown":
            TWN_FightInTown();
        break;

        case "FightInTown_OpenNext":
            TWN_FightInTown_OpenNext();
        break;

        case "FightInTown_Finish":
			// � ������� �������� - � �� ����� ������� �������
            //chrDisableReloadToLocation = false;
            //bDisableFastReload = false; // ������ ����� ����� �������
            //LAi_SetFightMode(Pchar, false);
            LAi_grp_alarmactive = false; // ����� �������
            LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
            //LAi_LocationFightDisable(&Locations[FindLocation(Pchar.location)], true); eddy. �� ������ ������ � ����������
			LAi_LockFightMode(pchar, false);
            LAi_SetFightMode(Pchar, false);
        break;

        //��� ���� ������� �����
        // 1 ������ � ������� - � ������� ����

        // 2 ���� ��������� ���� ����
        case "Residence_Captured_Any":
            TWN_Residence_Captured_Any();
        break;

        case "Residence_Captured_Any_02":
   			TWN_Residence_Captured_Any_02();
        break;

        case "Back_Mayor_Type":
            TWN_Back_Mayor_Type();
        break;

        case "CapturedToOurCity":
            LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
            FadeOutMusic(3);
			PlayStereoOGG("music_ship_victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            //DeleteQuestHeader("tales_" + sld.City);  // to_do
            //AddQuestRecord("tales_" + sld.City, "1");

            Log_Info("����� " + GetCityName(sld.City) + " ������ ���!");

			// ������ ��������������
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // �� ����� ����
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // ��� ������ ������ � �������� �������
			}
            SetCaptureTownByHero(sld.City);
            LaunchColonyInfoScreen(); // ��������   to_do ���� ����� :(
			// ������ ��� �������
			//if (!isCityHasFort(sld.City)) // ���������� �����
			sTemp = "Attack_Fort_" + sld.City;
            SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
            PChar.Quest.(sTemp).CityId   = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
        break;
		///////////////////////////////// ������ ������ <--
		//  ��������� ����
		case "PostVideo_Start":
            bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
        break;

        case "PostVideo_After":
            PostEvent("DoInfoShower",100,"s","");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
        break;
        
        case "SetTimerEvent":
        	attrName = PChar.Quest.(qname).Event;
        	sTemp = PChar.Quest.(qname).Event.Type;
        	Model = PChar.Quest.(qname).Event.Param;
        	SetEventHandler(attrName, attrName, 0);
        	Event(attrName, sTemp, Model);
        	break;

        case "CallFunctionParam":
            attrName = PChar.GenQuest.CallFunctionParam;
            call attrName();
        break;
        
	// Warship. CallFunctionParam �� ����� �������� � ���������, ������� ����������� ����� ���...
	case "NextFunction":
		DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;
        
        // ����� �������� � � ��� �����..
        case "LaunchFrameForm":
            PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
        break;
        
        case "Move_Govenour":  // ���������� ����������� � ������ �����
            SetTimerCondition("Move_Govenour", 0, 0, 25+rand(10), true);
            Move_Govenour();
        break;
        
		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

        case "God_hit_us": // ��� ����� ������ - ������������� � ������� ��� ��������(boal)
			iTemp = 10+rand(15);
			if ((MakeInt(pchar.chr_ai.hp)-iTemp) > 0)
            {
    			LAi_SetActorType(PChar);
                LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
            }
			LAi_ApplyCharacterDamage(pchar, iTemp);
			SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
			LAi_CheckKillCharacter(pchar);
		break;
		// ������ � �� ���������
        case "TalkSelf_Start":
            StartActorSelfDialog("TalkSelf_Main");
        break;
        // ������ � �� ��������� �������
        case "TalkSelf_Quest":
            StartActorSelfDialog("First time");
        break;
        /////  ����� �� ������ � ������� ->
        case "alc":
			LAi_Fade("alc_2_prepare", "alc2");
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

            sld = characterFromID(pchar.questTemp.friend_in_tavern);
            FreeSitLocator(sld.Default, sld.Default.ToLocator);  // ������� ����
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
   			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			PlaceCharacter(pchar, "tables", pchar.location); // ������� � �����
		break;
		// ������� ���������� � ������� ���� -->
		case "tavern_keeper":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
            attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// ������� ���������� � ������� ���� <--
 		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("",0,0,0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info("���-�� ������� � ��������.");

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			aref stelsTavern;
			makearef(stelsTavern, pchar.questTemp.stels);
			if (!CheckAttribute(stelsTavern,"tavern")) pchar.questTemp.stels.tavern = 0;
			if (sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50+oSum/100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

   			sld = characterFromID(loadedLocation.fastreload + "_waitress");
   			pchar.questTemp.officiantLocator = sld.location.locator;
   			pchar.questTemp.officiantGroup   = sld.location.group;   // ���������, ��� ����
			PlaceCharacter(sld, "goto", pchar.location);
			sld.dialog.currentnode = "without_money";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
            sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group   = pchar.questTemp.officiantGroup;
		break;
		//  ������ ����� � ������� -->
        case "NationUpdate":
             NationUpdate();
            if(bSeaActive)
            {
                RefreshBattleInterface();
            }
		break;

        case "pir_flag_rise":
			Flag_PIRATE();
		break;
		// ������ � �������� -->
        case "any_patent_take":
            AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

            RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
            EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

            Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // ����� ������ �������
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // ������� ������ �������
		break;

        case "fra_flag_rise":
            Flag_FRANCE();
        break;

        case "eng_flag_rise":
            Flag_ENGLAND();
        break;

        case "spa_flag_rise":
            Flag_SPAIN();
        break;

        case "hol_flag_rise": 
            Flag_HOLLAND();
        break;

        case "QuestAboardCabinDialog":  // ������ � ��������, � ����� ��� ���������� �����
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // ������, ���� ���� ��������
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;
		
		case "LAi_ReloadBoarding": // �������� �����
			LAi_EnableReload();
		    DelEventHandler("Control Activation", "LAi_ActivateReload");
		    //#20171218-01 Re-enable fast action for cabin enter during boarding
            DeleteAttribute(&BattleInterface, "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;
		// boal <---
		//Blackthorn - ������ �������� ������
		case "PGGContra_close":
			CloseQuestHeader("Gen_StrangeInfo");
			DeleteAttribute(pchar, "questTemp.PGGContra.Know");
			chr = CharacterFromID(pchar.PGG_Contra_Current);
			if (chr.PGGAi.location != "Dead")
			{
				chr.PGGAi.location.town = chr.PGGAi.location.town.back;
				DeleteAttribute(chr, "PGGAi.location.town.back");
			}
		break;
		//������� ������
		//������������� ���� �����
		case "W_Smuggling":
			if (CheckAttribute(pchar,"Whisper.Contraband"))	
			{
				DeleteAttribute(pchar, "Whisper.Contraband");
				AddQuestRecord("WhisperContraband", "4");
				CloseQuestHeader("WhisperContraband");
			}
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				WhisperRemoveSmugglersFromShore();
				AddQuestRecord("WhisperContraband", "4");
				CloseQuestHeader("WhisperContraband");
			}
		break;
		//����� ��� �����
		case "Whisper_WarDog":
			WhisperWarDogSeaBattle();
		break;
        ////////////////////////////////////////////////////////////////////////
		//  ��������� ����� ��������������� - ����������� �� �������
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
			//������� ������ ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";  
			RemoveSmugglersFromShore();
		break;

		//���������� ���������� � ������� �������� ���������������
		case "Rand_ContrabandInterruption":
			pchar.ContraInter = true;
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			// ������� � ������
			iTemp = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loadedLocation)));
			if(iTemp == -1) 
			{
				iTemp = sti(pchar.GenQuest.Contraband.GuardNation);// ����� �������
			}	
			Pchar.quest.contraband.SoldierQty = makeint(2*GetOfficersQuantity(Pchar) + 3);
			for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
    			attrName = "SoldierIDX"+i;
    			Pchar.quest.contraband.(attrName) = sld.index;
    			LAi_SetActorType(sld);
    			LAi_ActorFollow(sld, Pchar, "", 38);
    			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "Gr_Costal_Guards";
            }
			// ������� ����������!!!! �� ��� :) SetCoastalGuardPursuit();

			// ������ � �����
            sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
			Pchar.quest.contraband.SoldierIDX1 = sld.index;
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
			sld.Dialog.CurrentNode = "First time";
			sld.greeting = "Gr_Costal_Guards";

			LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - �������� �����!!!
			LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
			pchar.quest.CoastG.win_condition.l1 = "NPC_Death";
			pchar.quest.CoastG.win_condition.l1.character = sld.id;
			pchar.quest.CoastG.win_condition.function = "Rand_ContraFinal";
			//LAi_SetActorType(Pchar); //fix
			//LAi_ActorFollow(PChar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], "", 35);
			//Lai_QuestDelay("Rand_CoastalPatrolAppear", 3.0);
		break;

		case "Rand_ContraFinal":
			pchar.quest.Rand_ContraFinal.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Rand_ContraFinal.win_condition.l1.location = pchar.location;
			pchar.quest.Rand_ContraFinal.win_condition.function = "Rand_Clear";
		break;
		
		case "Rand_Clear":
			DeleteAttribute(pchar,"ContraInter");
		break;
		/*case "Rand_CoastalPatrolAppear":
			//Trace("QUEST Rand_CoastalPatrolAppear reports: Soldier Idx = " + Pchar.quest.contraband.SoldierIDX1);
			//StartQuestMovie(true, true, true);
			//LAi_SetActorTypeNoGroup(Pchar);
			LAi_SetActorType(Pchar);
			LAi_ActorTurnToCharacter(Pchar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)]);
			LAi_ActorWaitDialog(Pchar, &Characters[makeint(Pchar.quest.contraband.SoldierIDX1)]);
			//LAi_SetPlayerType(Pchar);
		break;*/

		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("� ��� ������ ������� � ����� ����. �����-�� ������� ������� ������� ������� ������ �����������, ��� ��� ���������� ������� �� ����� ����� �������. � ��������, ������. "+ 
				"������� ���� - ���� ����� �������������, � � ������� ����� ����� ����� ���������! �� ������ ��� ����� ��. �������-�� - �������� ������, � �������� ����������, � ������� ����� ����. ��� ����, � ����� ���� ������� �������! ��� �� ����� ������� - ����� ������ ����������!", Pchar.quest.contraband.City, 3, 5, "");	
		break;

		case "ContraSneakGot":
			DeleteAttribute(pchar,"quest.Contraband.SneakGot");
		break;
		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("� ��� ������ ������� � ����� ����. �����-�� ������� ������� ������� ������� ������ �����������, ��� ��� ���������� ������� �� ����� ����� �������. � ��������, ������. "+ 
				"������� ���� - ���� ����� �������������, � � ������� ����� ����� ����� ���������! �� ������ ��� ����� ��. �������-�� - �������� ������, � �������� ����������, � ������� ����� ����. ��� ����, � ����� ���� ������� �������! ��� �� ����� ������� - ����� ������ ����������!", Pchar.quest.contraband.City, 3, 5, "");				
		break;
		case "CoastalGuardsAllDead":
			for (i=1; i<3+makeint(MOD_SKILL_ENEMY_RATE/2); i++)
			{
				sTemp = "Rand_Smug0" + i;
				LAi_SetGuardianTypeNoGroup(CharacterFromID(sTemp));
			}
			LAi_grp_alarmactive = false; // ����� �������
		break;
		//  ����������� <--
		
		/////////////////////////////////////////////////////////////////////////////////
		// ������ ������ - �������� �������� ����������� � ���� �����
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// ����� ������ - �������� �������� ����������� � ���� �����
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// ����� �������� ������ � �������
		/////////////////////////////////////////////////////////////////////////////////		
		case "HabitueSpeakDisable_End":
			DeleteAttribute(pchar,"questTemp.HabitueSpeakDisable");
			DeleteAttribute(pchar,"questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// ����� �������� ������ � �������
		/////////////////////////////////////////////////////////////////////////////////				
		
		/////////////////////////////////////////////////////////////////////////////////
		//	��������� ����
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
			break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth	= sti(PChar.AutoQuest.delayMonth);
			iDay	= sti(PChar.AutoQuest.delayDay);
			iHour	= sti(PChar.AutoQuest.delayHour);
			iMin	= sti(PChar.AutoQuest.delayMin);

			if(iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
                bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	��������� ����
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ���
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
			break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
			break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ���
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	���������� �����
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship")) 
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","�"));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
			break;

		case "Travel_talkOnDeck":
			//������� ���������������
			RemoveSmugglersFromShore();
			//���������� ������� ���� :)
			sld = CharacterFromID("Abracham_Gray");
			//���������..
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //���� �� ����
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//��������....
			iTemp = 3 + rand(3);
			for(i = 0; i < iTemp; i++)
			{
				sTemp = "pirat" + (2 + rand(5));
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceForts("goto", attrName, PIRATE, "TmpEnemy");
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
			break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","�"));
			StartActorSelfDialog("GenTravel_Main");
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ���������� �����
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// ������ ������ - �������� �����
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
            AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			//������ �����
			SetTimerCondition("generate_trade_quest", 0, 0, (sti(pchar.CargoQuest.iDaysExpired) + 1), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city+"Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            attrName = "";
            if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
            {
                attrName = ", ��� ��������� �� " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
            }
            AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            // ������� ������� �����
            TraderHunterOnMap();
		break;
		
		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog("����� ��� �������� ����� �������.");
				ChangeCharacterReputation(pchar, -10);
				OfficersReaction("bad");
                AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// ����� ������ - �������� �����
		/////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////
		// ������ ������ - ���� � �������
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			if (CheckAttribute(pchar, "QuestTemp.TakeShotgun") && rand(1) == 1 && !CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd")) // ��������
			{
			    DeleteAttribute(pchar, "QuestTemp.TakeShotgun");
			    PChar.GenQuest.CallFunctionParam = "QuestShotgunT102";
			    DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "CallFunctionParam");
			}
			if (CheckAttribute(pchar,"cursed.waitingSkull"))
			{
				if (GetQuestPastDayParam("pchar.questTemp.Cursed") >= 30 || CheckAttribute(pchar,"cursed.Skullbought"))
				{
					PChar.GenQuest.CallFunctionParam = "QuestCursedSceleton";
					
					
					DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "CallFunctionParam");
				}
				else
				{
					DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
				}
			}
			else
			{
				DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
			}
		break;
		
		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i=1; i<=MAX_NUM_FIGHTERS; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}			
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// ����� ������ - ���� � �������
		/////////////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  ������    LOAN - ����������� �� �������
		////////////////////////////////////////////////////////////////////////
		case "LoanFindCitizenTimer": // �������
            Log_SetStringToLog("�� �� ������� ������ �������� ������������.");
            LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.Loan.FindCitizenNpcharId)], MOD_SKILL_ENEMY_RATE+30);
            //DeleteAttribute(pchar, "GenQuest.Loan");
		break;

		case "LoanChestTimer": // ������
            Log_SetStringToLog("�� �� ��������� ������ �� ����������.");
            LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.LoanChest.ChestNpcharId)], MOD_SKILL_ENEMY_RATE+15); // ��� ���
            LoansMoneyAvengerAmount(&Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)], MOD_SKILL_ENEMY_RATE+15);// ���� �����
            pchar.GenQuest.LoanChest.Money.Discount = (rand(3)+1)*10; //������� ��������� �������� �� ���������
			//DeleteAttribute(pchar, "GenQuest.LoanChest");
            AddQuestRecord("Gen_LoanTakeChest", "2");
            //CloseQuestHeader("Gen_LoanTakeChest");
		break;

		case "LoansForAll":			
			sTemp = pchar.quest.(qname).CityId;
			LoansMoneyAvenger(&Characters[GetCharacterIndex(sTemp + "_usurer")]);
			Characters[GetCharacterIndex(sTemp + "_usurer")].Dialog.CurrentNode = "DeadMotherfucker";
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    LOAN - ����������� �� �������
		////////////////////////////////////////////////////////////////////////				
		
 		////////////////////////////////////////////////////////////////////////
		//  ������	��������� ������
		////////////////////////////////////////////////////////////////////////
		
		// ��������� �� ��������
		case "Church_GenQuest2_AskedBand":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			PChar.GenQuest.ChurchQuest_2.AskContra_1 = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","��"));
			Log_TestInfo("�� ������, ��� �� ���� ������� ������ ����� ����.");
			break;
			
		case "Church_GenQuest2_BanditsIsEnemies":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			iChurchGenBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iChurchGenBanditsCount; i++)
			{
				sld = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_Group_MoveCharacter(sld, "Church_GenQuest2_Bandits_Group");
			}
			LAi_SetFightMode(PChar, true);
			LAi_Group_SetRelation("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, true);
			SetFunctionExitFromLocationCondition("Church_GenQuest2_BanditsIsEnemies_2_Clear", PChar.location, false);
			LAi_Group_SetCheckFunction("Church_GenQuest2_Bandits_Group", "Church_GenQuest2_DeadBandits");
			break;
        
		////////////////////////////////////////////////////////////////////////
		//  �����	��������� ������
		////////////////////////////////////////////////////////////////////////	
		
 		////////////////////////////////////////////////////////////////////////
		//  ������    ������������� ��������
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_convoy_quest":
			iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
            sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true));
			SetCaptanModelByEncType(sld, "trade");
			sld.reputation = (1 + rand(44) + rand(44));
			sld.Dialog.Filename = "convoy_traider.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "Gr_ConvoyTrader";
			sld.BakNation = sld.nation;		
		    sld.Abordage.Enable = true;
			sld.CompanionEnemyEnable = true;
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			pchar.quest.generate_convoy_quest_progress = "begin";
			Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "convoy_refused":
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			if (checkquestattribute("generate_convoy_quest_progress", "completed"))
			{
				OfficersReaction("good");
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				AddQuestRecord("convoy_quest", "4");
				CloseQuestHeader("convoy_quest");
				AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
				ChangeCharacterReputation(pchar, 1);
				RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
				CloseQuestHeader("convoy_quest");
				
				pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
				if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
				if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
				if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			}
			pchar.quest.generate_convoy_quest_progress = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(characterFromID("QuestTrader"));
			LAi_ActorGoToLocation(characterFromID("QuestTrader"), "reload", LAi_FindFarLocator("reload", locx, locy, locz), "none", "", "", "", 20.0);
		break;
		
		case "generate_convoy_quest_timer":
            AddQuestRecord("convoy_quest", "2");
			CloseQuestHeader("convoy_quest");            
            sld = characterFromID("QuestTrader");
            ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5+rand(10));// �������
			RemoveCharacterCompanion(Pchar, sld);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -10);
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
		break;
		
		case "generate_convoy_quest_failed": // �������� ����
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
            RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
            pchar.quest.generate_convoy_quest_timer.over  = "yes";            
            AddQuestRecord("convoy_quest", "3");
			CloseQuestHeader("convoy_quest");
		break;
		
		case "generate_convoy_quest_completed":
			sld = characterFromID("QuestTrader");
			if (IsCompanion(sld))
			{
				sld.dialog.currentnode = "complete_convoy_quest";
				PlaceCharacter(sld, "goto", pchar.location);			
				Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.			
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10+rand(10));// �������
				OfficersReaction("bad");
				pchar.quest.generate_convoy_quest_progress = "";				
				pchar.quest.generate_convoy_quest_failed.over = "yes";
				pchar.quest.generate_convoy_quest_completed.over = "yes";
				pchar.quest.generate_convoy_quest_timer.over  = "yes";  
				AddQuestRecord("convoy_quest", "5");
				CloseQuestHeader("convoy_quest");
			}
		break;		

		case "convoy_agreeded":
			sld = characterFromID("QuestTrader");
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", "reload1_back", 3.0, false);
            ReOpenQuestHeader("convoy_quest");
			AddQuestRecord("convoy_quest", "1");
			AddQuestUserData("convoy_quest", "sSex", GetSexPhrase("��","���"));
			sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") + ",";
			AddQuestUserData("convoy_quest", "sCity", sTemp);
			AddQuestUserData("convoy_quest", "sDay", FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)));
            AddQuestUserData("convoy_quest", "sMoney", FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			// �� ������ ������ ��� ����
            attrName = GetPortByCityName(pchar.quest.destination);            
			pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
			pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
			pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";			
			if (rand(2) == 1) TraderHunterOnMap();
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    ������������� ��������
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  ������    �������� ���������
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_passenger_quest":
			iTemp = sti(colonies[FindColony(sGlobalTemp)].nation);
            Rank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true);
			sld = &characters[Rank];
			sld.id = sld.id + "_" + sld.index; //������ ID �� ������������
			sld.reputation = (1 + rand(44) + rand(44));
			SetCaptanModelByEncType(sld, "trade");
			SetRandomNameToCharacter(sld);
			sld.Dialog.Filename = "convoy_passenger.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);            
		break;

		case "AllPassangersDead": // �������� ����
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			ChangeCharacterReputation(pchar, -5);
            RemovePassenger(PChar, sld);
			sTemp = sld.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //��������� �� ��������� �����������
			//--> ������� Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- ������� Deck
			attrName = sld.index + "convoy_passenger";
			AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
            CloseQuestHeader(attrName);
            //#20170629-01 Dialog/follow bug in Passenger quest
            DeleteAttribute(pchar, "tempDlgInterruptPass"));
		break;
		
		case "AllPassangersTimeOver":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id;
			Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //� ��������� �����������
			if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
			{
				Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
        		Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
			}
		break;
		
		case "AllPassengerDeck": // �������� �� ������			
            MakeCloneShipDeck(pchar, true); // ������� ������
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
    		iTemp = GetAttributesNum(arAll);
    		for (i=0; i<iTemp; i++)
    		{
    			arPass = GetAttributeN(arAll, i);
				sld = &characters[sti(arPass)];				
				ChangeCharacterAddress(sld, "Ship_deck", "goto4");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
    		}
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
			ReloadFromWMtoL_complete();
            pchar.quest.Munity = "";  // ������� ������ � ������
            LAi_LockFightMode(Pchar, true);
        break;
        
		case "AllPassangersComplited":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id + "_TimeOver";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
			chrDisableReloadToLocation = true;
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", "random_must_be");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);     
			//#20170629-01 Dialog/follow bug in Passenger quest
			pchar.tempDlgInterruptPass = pchar.quest.(qname).Idx;
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    �������� ���������
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  ������   ���� ����������
		//////////////////////////////////////////////////////////////////////// 
		//------------------- ����� ���������� -------------------------
		case "LandEnc_RaidersBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Gang"+ pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0); 
			for(i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);				
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_RaidersBeforeDialog": //���� ������� �� �������
			attrName = locations[reload_location_index].index;
			sTemp = "EncRaiders_" + attrName;
			// iTemp = sti(pchar.quest.(sTemp).EncQty);	// LEO
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			pchar.quest.(sTemp).over = "yes";
			Model = "RaidersGroup_" + attrName; //��� ������
			sTemp = "Gang"+ attrName + "_";
			for(i = 0; i < iTemp; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				//#20190329-01
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, Model);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//#20190329-01
            LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_RaidersAfrer");
		break;

		case "LandEnc_RaidersAfrer": //������ �� �����
			attrName = locations[reload_location_index].index;
			sTemp = "TimeRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "RaidersGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//#20190328-03
			LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0.0);
			Gun = "Raiders_" + attrName; 
			AddSimpleRumour(LinkRandPhrase("�� �������, ������� " + GetFullName(pchar) + " �������"+ GetSexPhrase("��","���") +" � �������� �� ����� " + pchar.GenQuest.(Gun).name + ". �"+ GetSexPhrase("��","�") +" ������ ��������, � ��"+ GetSexPhrase("","�") +" �� �������"+ GetSexPhrase("","�") +" �������. ����"+ GetSexPhrase("�� ���","�� �������") +" - ��"+ GetSexPhrase("","�") +" ������ ��� ����"+ GetSexPhrase("","�") +".", 
				"�� ������, ������� �� ������� ���� ������� - �� �������� �� ����� " + GetFullName(pchar) + " ������ �������, �������� ������... �-�, ��� �� �� � ���� "+ GetSexPhrase("��� �������","�� �������") +", ��� ��������"+ GetSexPhrase("","�") +" � �������� ����� �������� �� ����� " + pchar.GenQuest.(Gun).name + "! ���������� ������, ����� � ���...", 
				"�� �� ������� � ���, ��� ������� ����� �������� ��� ����������������� ������� " + pchar.GenQuest.(Gun).name + " ������ �� �������� �� ����� " + GetFullName(pchar) + "? �"+ GetSexPhrase("��","�") +" �������"+ GetSexPhrase("��","���") +" ������� � �������"+ GetSexPhrase("","�") +" ��������."), sti(pchar.GenQuest.(Gun).nation), 5, 1);				
			DeleteAttribute(pchar, "GenQuest." + Gun); //���� ����� � ���			
		break;

		case "LandEnc_RaidersOver": //������ �� �����
			sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
			iTemp = sti(pchar.quest.(sTemp).EncQty);
			sTemp = "Gang" + pchar.quest.(qname).LocIdx + "_";
			for(i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "RaidersGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			//#20190328-03
			LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0.0);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
			sTemp = pchar.quest.(qname).LocIdx;
			DeleteAttribute(pchar, "GenQuest." + sTemp); //���� ����� � ���
		break;
		//------------------- ����� � ������� -------------------------
		case "LandEnc_RapersTalk":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
			}
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
		break;

		case "LandEnc_RapersBeforeDialog": //���� ������� �� �������
			if (GetCharacterIndex("CangGirl") != -1) LAi_RemoveCheckMinHP(CharacterFromID("CangGirl"));			
			for(i = 1; i <= 3; i++)
			{				
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				//#20190329-01
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//#20190329-01
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");			 
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
		break;

		case "LandEnc_RapersAfrer":
		    //#20190328-03
			LAi_group_SetAlarm("EnemyFight", LAI_GROUP_PLAYER, 0.0);
			sGlobalTemp = "Saved_CangGirl";
			sld = CharacterFromID("CangGirl");
			sld.greeting = "Enc_RapersGirl_2";
			sld.dialog.currentnode = "ThanksForHelp";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LandEnc_RapersBadExit":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				sld.lifeDay = 0;
			}
			if (GetCharacterIndex("CangGirl") == -1) // ���� �� ��������������� ������ �����
			{
				ChangeCharacterReputation(pchar, -3);
				AddSimpleRumour(LinkRandPhrase("�� �������, ���-�� ���� � �������� ���������� ������� �� ����� " + pchar.GenQuest.EncGirl.name + ". �������� �� �������� � ���������!", 
					"�� ������, ������� " + GetFullName(pchar) + ", ���-�� ���� ���������� ������� �� ����� " + pchar.GenQuest.EncGirl.name  + ", ����� �� �� ����� ����������� �� �����. ��� ����, ��� ���� ����� �������...", 
					"�� ����� " + pchar.GenQuest.EncGirl.name  + ", � ��� ������� � ��������. � ������ �������������, ����� � ���, �� ������� ��� ����������..."), sti(pchar.GenQuest.EncGirl.nation), 5, 1);			
			}
			else
			{
				characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
				if (sGlobalTemp == "Saved_CangGirl") // ������ �����
				{
					if(pchar.GenQuest.EncGirl == "close") // .. � ������� �� ���� ��������
					{
						characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
						DeleteAttribute(pchar, "GenQuest.EncGirl");
					}
					else
					{		
						if(!CheckAttribute(pchar, "GenQuest.EncGirl.Ransom")) 
						{
							ChangeCharacterReputation(pchar, 5);
							AddSimpleRumour(LinkRandPhrase("�� �������, "+ GetSexPhrase("�����-�� �������","�����-�� �������") +" ����"+ GetSexPhrase("","��") +" ������� �� ����� " + pchar.GenQuest.EncGirl.name + " �� ��������, ��������� ������� �� �� �� ���!"+ GetSexPhrase(" ����� ���������� ������� � ��������� �������.","") +"", 
								"�� ������, ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("","��") +" ������� �� ����� " + pchar.GenQuest.EncGirl.name + " �� ����������� � ��������... �-�, ��� ��� �� ��!! � ���� ����������...", 
								"������� �� ����� " + pchar.GenQuest.EncGirl.name + " ������� ������� - ������� �� ��� ������ ������� � ��������, ������ ������������, ������. �� ������ � ��� �� �����, ��-��, � ����������� ��� ������ �������� " + GetMainCharacterNameGen() + "!"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);	
						}		
					}	
				}
				else // ������� �� ����������� ��������
				{	
					for(i = 1; i <= 3; i++)
					{
						if (GetCharacterIndex("GangMan_" + i) == -1) continue;
						sld = CharacterFromID("GangMan_" + i);
						LAi_RemoveCheckMinHP(sld);
						sld.lifeDay = 0;
					}		
					characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
					if(pchar.GenQuest.EncGirl == "Begin_11")
					{
						ChangeCharacterReputation(pchar, -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_22")
					{
						ChangeCharacterReputation(pchar, -8);
					}
					if(pchar.GenQuest.EncGirl == "Begin_33")
					{
						ChangeCharacterReputation(pchar, -5);
					}
					AddSimpleRumour(RandPhraseSimple("�� ��, ������� " + GetFullName(pchar) + ", ����� �� �����, ��� �� �������� �������� ����������� ������� �� ��������� ��������. ������ " + pchar.GenQuest.EncGirl.name + ", � ���� ��� ����...", 
						"������, �������, "+ GetSexPhrase("�� ��������� ��������","�� ������ �� ��� ������") +". ��� �� ����� ������� ����������� ������� � ��������? �� ���� ������������� ����, ��� ��� � ��� �������? ������ " + pchar.GenQuest.EncGirl.name + ", �� ������ ����� �� ������� �����..."), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
					DeleteAttribute(pchar, "GenQuest.EncGirl"); //���� ����� � ���	
				}
			}			
			DeleteAttribute(pchar, "GenQuest.EncGirl"); //���� ����� � ���
		break;
		//------------------- ����� ������ ������ ������� -------------------------
		case "Enc_FriendGirl_after": //���� ������� �� �������
			ChangeCharacterReputation(pchar, -(rand(4)+1));
			if (rand(1))
			{
				AddSimpleRumour(LinkRandPhrase("�� �������, �����-�� ������� ���� � �������� ���������� ������� �� ����� " + pchar.GenQuest.EncGirl.name + ". �������� �� �������� � ���������!", 
					"�� ������, ������� " + GetFullName(pchar) + ", ���-�� ���� ���������� ������� �� ����� " + pchar.GenQuest.EncGirl.name  + ", ����� �� �� ����� ����������� �� �����. ��� ����, ��� ���� ����� �������...", 
					"�� ����� " + pchar.GenQuest.EncGirl.name  + ", � ��� ������� � ��������. � ������ �������������, ����� � ���, �� ������� ��� ����������..."), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			}
		break;
		case "Enc_FriendGirl_afterGang":
			DeleteAttribute(pchar, "GenQuest.EncGirl"); 
		break;
		//------------------- ������� � �������� -------------------------
		case "LandEnc_PatrolBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Patrol"+ pchar.quest.(qname).LocIdx + "_";
			npchar = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorDialog(npchar, pchar, "", fTemp, 0); 
			for(i = 1; i < iTemp; i++)
			{
				sld = characterFromId(sTemp + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1); 
			}
		break;

		case "LandEnc_PatrolBeforeDialog": //���� ������� �� �������
			attrName = locations[reload_location_index].index;
			sTemp = "EncPatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "PatrolGroup_" + attrName; //��� ������
			sTemp = "Patrol"+ attrName + "_";
			for(i = 0; i < iTemp; i++)
			{				
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_PatrolAfrer");
		break;

		case "LandEnc_PatrolAfrer": //������ �� �����
			attrName = locations[reload_location_index].index;
			sTemp = "TimePatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "PatrolGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//�����
			AddSimpleRumour(LinkRandPhrase("������� �� ������� ����� ������� ������ ������� � ��������� ��� ������. ��� ��� �� �����? �����?..", 
				"��� �������� ��������� ���������� �� ����� �������, �� ������ ���� �� ����, ��� ����� ������. ������� ������ ����� �������� � ��������...", 
				"���� ������, ���-�� �� ������� ������� ���� ������, ��� ������������� ����������..."), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �������� � �������� �� ������ " + NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)) + " � ���� �� �������. ���, " + NationNamePeople(sti(pchar.GenQuest.(attrName).nation)) + " - ������ �������� �����...", sti(pchar.GenQuest.(attrName).nation)+10, 5, 1);
			DeleteAttribute(pchar, "GenQuest." + attrName); //���� ����� �������, ���� ����
		break;

		case "LandEnc_PatrolOver": //������ �� �����
			sTemp = pchar.quest.(qname).LocIdx;
			//�����
			AddSimpleRumour(LinkRandPhrase("�� �������, �������� " + GetMainCharacterNameGen() + " �������� ��� ������� �� �������...", 
				"��, ��������� � ����, ��� ������� �������� ��� ������� �� �������. �� ����, ��������� ��� ���� ����������...", 
				"��� ��������� ������ �������������� ����������� � ������ ����������. �� �� � ���� �� ���� ������, ��� �� ������� ��������� � ��������..."), sti(pchar.GenQuest.(sTemp).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + sTemp); //���� ����� �������, ���� ����
			sTemp = "PatrolGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncPatrol_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
		break;

		case "DeleteGroupOnExitLocation": //������ �����
			sTemp = pchar.quest.DeleteGroupOnExitLocation.GroupName;
			LAi_group_Delete(sTemp);
		break;

        case "Followers_activate": //��������� ������
			for(i = 1; i <= 2; i++)
			{				
				if (GetCharacterIndex("Walker_" + i) == -1) continue;
				sld = CharacterFromID("Walker_" + i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("Walker"), "", -1);
			}
			
			for(i = 1; i <= 2; i++)
			{			
				if (GetCharacterIndex("Walker_sold_" + i) == -1) continue;
				sld = CharacterFromID("Walker_sold_" + i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("Walker"), "", -1);
			}
			
			for(i = 1; i <= 2; i++)	
			{	
				if (GetCharacterIndex("WalkerGirl_husband_"+i) == -1) continue;
				sld = CharacterFromID("WalkerGirl_husband_"+i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerGirlGuardHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("WalkerGirl"), "", -1);
			}
			
            for(i = 1; i <= 2; i++)
			{			
				if (GetCharacterIndex("WalkerGirl_sold_"+i) == -1) continue;
				sld = CharacterFromID("WalkerGirl_sold_"+i);
				LAi_SetActorType(sld);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_WalkerGirlGuardHit");
				LAi_group_MoveCharacter(sld, "LandEncGroup");
				LAi_ActorFollow(sld, characterFromID("WalkerGirl"), "", -1);
			}
		break;		
		
		case "LandEnc_WalkerGirlGuardHit": //���� ������� � ������
			sld = CharacterFromID("WalkerGirl_sold");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
			
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerGirlHitAfrer");
		break;		
		
		case "LandEnc_WalkerGirlHusbandHit": //���� ������� � ������
			sld = CharacterFromID("WalkerGirl_husband");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
			
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerGirlHitAfrer");
		break;
		
		case "LandEnc_WalkerHit": //���� ������� � ������
		    sld = CharacterFromID("Walker");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
			
			for(i = 1; i < 5; i++)
			{				
				if (GetCharacterIndex("Walker_" + i) == -1) continue;
				sld = CharacterFromID("Walker_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
				
				if (GetCharacterIndex("Walker_sold_" + i) == -1) continue;
				sld = CharacterFromID("Walker_sold_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LandEncGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LandEncGroup", "LandEnc_WalkerHitAfrer");
		break;

		case "LandEnc_WalkerHitAfrer": //������ �� �����
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			//�����
/* 			AddSimpleRumour(LinkRandPhrase("������� �� ������� ����� ������� ������ �������� ������. ��� ��� �� �����? �����?..", 
				"��� �������� ��������� ���������� �� ����� �������, �� ������ ���� �� ����, ��� ����� ������. ������� ������ ����� �������� � ��������...", 
				"���� ������, ���-�� �� ������� ������� ���� ������, ��� ������������� ����������..."), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �������� � �������� �� ������ " + NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)) + " � ���� �� �������. ���, " + NationNamePeople(sti(pchar.GenQuest.(attrName).nation)) + " - ������ �������� �����...", sti(pchar.GenQuest.(attrName).nation)+10, 5, 1); */
		break;	

		case "LandEnc_WalkerGirlHitAfrer": //������ �� �����
			LAi_group_SetRelation("LandEncGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			//�����
/* 			AddSimpleRumour(LinkRandPhrase("������� �� ������� ����� ������� ���� �������. ��� ��� �� �����? �����?..", 
				"��� �������� ��������� ���������� �� ����� �������, �� ������ ���� �� ����, ��� ����� ������. ������� ������ ����� �������� � ��������...", 
				"���� ������, ���-�� �� ������� ������� ���� ������, ��� ������������� ����������..."), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour("�������, ��� ������� " + GetFullName(pchar) + " �������� � �������� �� ������ " + NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)) + " � ���� �� �������. ���, " + NationNamePeople(sti(pchar.GenQuest.(attrName).nation)) + " - ������ �������� �����...", sti(pchar.GenQuest.(attrName).nation)+10, 5, 1); */
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����   ���� ����������
		//////////////////////////////////////////////////////////////////////// 

 		////////////////////////////////////////////////////////////////////////
		//  ������    ����������� �����
		////////////////////////////////////////////////////////////////////////  
		case "AllMayorsQuests_Late": //���������� ���������� �� ��� ������ ����
			sTemp = pchar.GenQuest.questName;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� �� �����
			pchar.GenQuest.(sTemp) = "Late"; //���� �������
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			AddQuestRecord("MayorsQuestsList", "20");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));			
			//������� ��������� ������ � ���������
			if (sTemp == "DestroyPirate") 
			{
				Group_DeleteGroup("MQGroupPirate");
				LAi_group_Delete("MayorPirateGroup");
				for (i=0; i<5; i++)
				{
					Group_DeleteGroup("MQGroupAll_" + i);
				}
			}
		break;

		case "DestroyGang_fight":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.			
				LAi_group_Delete("EnemyFight");
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //������� ������� ������������ ����������					
				ref location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //����� ����������� ������ ����� �� ������, ��� ������
				string encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));
				iTemp = LAi_CalculateRaidersQuantity(GetAttributesNum(arAll)); // ���-�� ������� � �����
				if (iTemp <= 0 ) iTemp = 1; //���� ��������� ������ �������
				//--> ������� ���� 
				if (sti(pchar.rank) > 6) 
				{
					if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*4/iTemp);
					else Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/iTemp);
				}
				else  
				{	//�������� ������� ���� �� ������ ����
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else 
					{
						Rank = 1;
						iTemp = 1;
					}
				}	
				//<-- ������� ���� 
				string iModel[25];
				iModel[0] = "pirate_1";
				iModel[1] = "pirate_2";
				iModel[2] = "pirate_3";
				iModel[3] = "pirate_4";
				iModel[4] = "pirate_5";
				iModel[5] = "pirate_6";
				iModel[6] = "pirate_7";
				iModel[7] = "pirate_8";
				iModel[8] = "pirate_9";
				iModel[9] = "pirate_10";
				iModel[10] = "pirate_11";
				iModel[11] = "pirate_12";
				iModel[12] = "pirate_13";
				iModel[13] = "pirate_14";
				iModel[14] = "pirate_15";
				iModel[15] = "pirate_16";
				iModel[16] = "pirate_17";
				iModel[17] = "pirate_18";
				iModel[18] = "pirate_19";
				iModel[19] = "pirate_20";
				iModel[20] = "pirate_21";
				iModel[21] = "pirate_22";
				iModel[22] = "pirate_23";
				iModel[23] = "pirate_24";
				iModel[24] = "pirate_25";
				i = 0;
				while(i < iTemp)
				{
					ShipType = rand(24);
					if (iModel[ShipType] != "")
					{
						if (i == 0) 
						{   //������� �����
							int iMainGang = NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true);
							sld = &characters[iMainGang];
							sld.name = pchar.GenQuest.DestroyGang.name;  //��� �������
							sld.lastname = pchar.GenQuest.DestroyGang.lastname;
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyGang_begin";
							sld.greeting = "Enc_Raiders"; 
							sld.SaveItemsForDead   = true; // ��������� �� ����� ����
							sld.DontClearDead = true;  // �� ������� ���� ����� 200�
						}
						else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true));
						LAi_SetActorType(sld);
						SetFantomParamFromRank(sld, Rank, true);
						//������� ������� ��� ������
						attrName = GetAttributeName(GetAttributeN(arAll, 1));
						ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);					
						LAi_SetActorType(sld);
						if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0); 
						else LAi_ActorFollow(sld, &characters[iMainGang], "", -1);
						i++;
						iModel[ShipType] = "";
					}
				} 				
			}
		break;
		
		case "Kamikazi":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.			
				LAi_group_Delete("EnemyFight");
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //������� ������� ������������ ����������					
				location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //����� ����������� ������ ����� �� ������, ��� ������
				encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));
				
				iMainGang = NPC_GenerateCharacter("MayorQuestGang_0", "Skel_6", "skeleton", "man2_ab", 100, PIRATE, 0, true);
				sld = &characters[iMainGang];
				sld.name = pchar.GenQuest.DestroyGang.name;  //��� �������
				sld.lastname = pchar.GenQuest.DestroyGang.lastname;
				sld.dialog.filename = "Kamikazi.c";
				sld.dialog.currentnode = "Kamikazi";
				sld.greeting = ""; 
				sld.SaveItemsForDead   = true; // ��������� �� ����� ����
				sld.DontClearDead = true;  // �� ������� ���� ����� 200�
				LAi_SetActorType(sld);
				SetFantomParamFromRank(sld, Rank, true);
				//������� ������� ��� ������
				attrName = GetAttributeName(GetAttributeN(arAll, 1));
				ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);					
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
				PlaySound("Interface\P_Kamikadze_SS.wav");
			}
		break;

		case "DestroyGang_SuddenAttack":
			for(i = 0; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
		break;

		case "DestroyGang_Afrer":
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //������� ����� ������
			Delay_DeleteGroup("EnemyFight");
			//#20190328-03
			LAi_group_SetAlarm("EnemyFight", LAI_GROUP_PLAYER, 0.0);
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //���� �������� �������
			sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// ������� ������
			AddQuestRecord("MayorsQuestsList", "2");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arAll));
			// �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + sTemp + " ������� ����"+ GetSexPhrase("��� ��������","� �������") +" " + GetMainCharacterNameDat() + " ���������� ���������� ������� �� ����� " + GetFullName(arAll) + ". �, �������, ��� "+ GetSexPhrase("������� ��������","��� ���������") +" ������� �����������...", 
				""+ GetSexPhrase("�����-�� ������ ������� ��������","�����-�� ������ ������� ���������") +" ����� � ���������� �������� ������� �� ����� " + GetFullName(arAll) + ". �, ������, ��"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("","�") +" ���!", 
				"��, �������-�� ��� ���������� ������ �� ��������� ������� � �������� - �� ������� �������� " + GetMainCharacterNameDat() + " ��������� � �������� � ����� �������� ���������� �������. � �� �����, ���� ������, " + GetFullName(arAll) + " - �����!"), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    ����������� �����
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  ������    ����� ��������� � ������
		//////////////////////////////////////////////////////////////////////// 
        case "SeekSpy_login":
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City"))
			{	//����� �� �����
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //������� ������� ������������ ����������	
				sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "man", "man", Rank, PIRATE, sti(pchar.GenQuest.SeekSpy.Terms), false));
				sld.dialog.filename = "MayorQuests_dialog.c";
				sld.dialog.currentnode = "SeekSpy_street";
				sld.city = characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city;
				sld.greeting = "cit_common";
				LAi_SetLoginTime(sld, 6.0, 21.99);
				//SetFantomParamFromRank(sld, Rank, true);
				LAi_SetCitizenType(sld);
				iTemp = sti(characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].nation);
				sTemp = GetNationNameByType(iTemp) + "_citizens";
				LAi_group_MoveCharacter(sld, sTemp);
				PlaceCharacter(sld, "goto", "random");
			}
			else
			{	//����� � ��������
				iTemp = reload_location_index;
				if (locations[iTemp].fastreload == characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city)
				{
					chrDisableReloadToLocation = true;  
					LAi_group_Delete("EnemyFight");
					sTemp = pchar.GenQuest.questName;
					pchar.quest.(sTemp).over = "yes"; //������� ������� ����������	
					pchar.quest.AllMayorsQuests_Late.over = "yes"; //������� ����� ������
					//--> ������� ���� 
					if (sti(pchar.rank) > 6) 
					{
						if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10);
						else Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5);
					}
					else  
					{	//�������� ������� ���� �� ������ ����
						if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
						else 
						{
							Rank = 1;
							if (iTemp > 2) iTemp = 2;
						}
					}	
					//<-- ������� ���� 
					// sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "spy", "spy", Rank, PIRATE, 0, true)); // LEO: ����� �� �������� ����������� - Gregg :)
					sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_"+(rand(11)+1), "man", "man", Rank, PIRATE, 0, true));
					sld.dialog.filename = "MayorQuests_dialog.c";
					sld.dialog.currentnode = "SeekSpy_house";
					sld.greeting = "cit_common"; 
					sld.money =  1000 + rand(5000);
			        sld.SaveItemsForDead  = true; 
					AddBonusEnergyToCharacter(sld, 30);
					FantomMakeCoolFighter(sld, Rank + 0.25, 20+rand(60), 30, "blade12", "pistol3", 70);
					DeleteAttribute(sld, "perks.list");
					DeleteAttribute(sld, "items.spyglass3")
					SetCharacterPerk(sld, "BasicDefense");
					SetCharacterPerk(sld, "CriticalHit");
					SetCharacterPerk(sld, "HardHitter");
					SetCharacterPerk(sld, "Energaiser");
					SetCharacterPerk(sld, "Ciras");
					SetCharacterPerk(sld, "Gunman");
                    SetCharacterPerk(sld, "Tireless");
                    TakeNItems(sld, "Lockpick", 1+rand(2));
					PlaceCharacter(sld, "goto", "random");
					LAi_SetCitizenType(sld);
					//LAi_ActorDialog(sld, pchar, "", -1, 0); 
				}
			}
        break;

		case "SeekSpy_Afrer":
			LAi_group_Delete("EnemyFight");
			pchar.GenQuest.SeekSpy = "Execute"; //���� �������� �������
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			// ������� ������
			AddQuestRecord("MayorsQuestsList", "4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// �����
			AddSimpleRumour(RandPhraseSimple("�� ������, ���������� " + sTemp + " ������� ����"+ GetSexPhrase("��� ��������","� �������") +" " + GetMainCharacterNameDat() + " ����� � ������ ���������� ���������. � �� ������, ��"+ GetSexPhrase("","�") +" ��� ���"+ GetSexPhrase("��","��") +" � ����"+ GetSexPhrase("","�") +"!", 
				"��� ���������� ��� ������� �������� " + GetMainCharacterNameDat() + " ��������� � ������ ���������� ������. � "+ GetSexPhrase("���� ������� ����� � ���������","��� ����� � ����������") +" ���������! ���������� ������, ����� � ���..."), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    ����� ��������� � ������
		//////////////////////////////////////////////////////////////////////// 

 		////////////////////////////////////////////////////////////////////////
		//  ������    ����� ��� ������
		//////////////////////////////////////////////////////////////////////// 		
		
		case "ReasonToFast_PatrolDied":
			sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);	
			if(pchar.questTemp.ReasonToFast == "PatrolAfterHunter") 
			{
				AddQuestRecord("ReasonToFast", "6");
				AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","�"));
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolAfter")
			{				
				AddQuestRecord("ReasonToFast", "8");
			}	
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				AddQuestRecord("ReasonToFast", "4");
			}
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); //����� �������� � �������	

			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1 = "Timer";
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.function = "ReasonToFast_SpeakMayor";

			DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), sti(pchar.questTemp.ReasonToFast.relation));
			pchar.questTemp.ReasonToFast = "PatrolDied";
			pchar.questTemp.ReasonToFast.speakAfterPatrolDied = false;
			DeleteAttribute(pchar, "GenQuest.HunterScore2Pause"); //������� ���������� ���
			DeleteAttribute(pchar, "GenQuest.ReputationNotChange"); //������� ����� ���� 
		break;
				
		case "ReasonToFast_MeetHunter":
			ReasonToFast_GenerateHunter();
		break;
		
		case "ReasonToFast_PatrolAngry":
			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";				
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter3";			
			LAi_SetActorType(pchar); 
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;
		
		case "ReasonToFast_HunterGoOut":
			sld = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetActorType(sld); 
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1); 
			sld.LifeDay = 0;
			pchar.questTemp.ReasonToFast = "MeetHunterSuccess";
	
			sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Enc_Patrol.c";				
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter1";
			LAi_SetActorType(pchar); 
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
		break;
				
		case "ReasonToFast_MeetWithSailor":
			Sea_DeckBoatStartNow(pchar);
		break;
		
		case "ReasonToFast_ClearVictim":
			pchar.quest.ReasonToFast_SetShip_1.over = "yes";
			pchar.quest.ReasonToFast_SetShip_2.over = "yes";
			sld = characterFromId("VictimCap_1");
			sld.lifeDay = 0;
			Group_DeleteGroup("Sea_Victim_1");
			AddQuestRecord("ReasonToFast","19");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
		break;
		
		case "ReasonToFast_TrHuntersDied":
			LAi_group_RemoveCheck("LAND_HUNTER");
			LAi_group_Delete("LAND_HUNTER");
			bDisableLandEncounters = false;	
			if(pchar.questTemp.ReasonToFast == "GetMap")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "������");
			}	
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "����������");
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", "��������");
			}
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "23");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");
				DeleteAttribute(pchar, "questTemp.ReasonToFast");
			}
		break;
		
		case "ReasonToFast_LakeyGoOut":
			sld = CharacterFromID("ReasonToFastLakey_1");
			LAi_SetActorType(sld); 
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1); 
			sld.LifeDay = 0;		
		break;
		
		case "ReasonToFast_GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(pchar.HunterCost.Qty); i++)
			{
				sld = characterFromID("LandHunter0" + i);
				LAi_SetActorType(sld); 
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
				iTemp = GetCharacterIndex("LandHunter0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			bDisableLandEncounters = false;	
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
        break;

 		////////////////////////////////////////////////////////////////////////
		//  �����    ����� ��� ������
		//////////////////////////////////////////////////////////////////////// 		

 		////////////////////////////////////////////////////////////////////////
		//  ������    ����������� ������
		//////////////////////////////////////////////////////////////////////// 
        case "KillSmugglers_after":
            if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[reload_location_index]))
            {
				pchar.GenQuest.KillSmugglers = "Execute"; //���� �������� �������
				pchar.quest.AllMayorsQuests_Late.over = "yes"; //������� ����� ������
				ChangeContrabandRelation(pchar, -30); //���� ������ ����
				Pchar.quest.Contraband.over = "yes";
				CloseQuestHeader("Gen_Contraband");
				pchar.GenQuest.KillSmugglers.shoreId = pchar.location; //����� ��������, ����� ����� :)
				sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)]);
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "9");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", sTemp));
				// �����
				AddSimpleRumour(RandPhraseSimple("�� ������, ���������� " + sTemp + " ������� ����"+ GetSexPhrase("��� ��������","� �������") +" " + GetMainCharacterNameDat() + " ����� � ���������� ���������������. � ����� � ���, ��"+ GetSexPhrase("","�") +" ��� ������"+ GetSexPhrase("","�") +".",
					"��� ���������� " + sTemp + " ��� ������� �������� " + GetMainCharacterNameDat() + " ��������� ��������������� � ������������ ������. ��"+ GetSexPhrase("","�") +" ���"+ GetSexPhrase("��","��") +" �� � ����"+ GetSexPhrase("","�") +", ������ ���� � ��������� ����� ���������..."), sti(characters[sti(pchar.GenQuest.KillSmugglers.MayorId)].nation), 5, 1);
			}
		break;

        case "KillSmugglers_outShore":
			pchar.quest.KillSmugglers.over = "yes"; //������� ������� ����������
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    ����������� ������
		//////////////////////////////////////////////////////////////////////// 

 		////////////////////////////////////////////////////////////////////////
		//  ������    ����� � ����������� ������
		//////////////////////////////////////////////////////////////////////// 
 		case "DestroyPirate_Begin":
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			int islandIdx = FindIsland(pchar.GenQuest.DestroyPirate.Areal);	
			aref arQuestLoc, arPlTarget, arLocator;	
			makearef(arPlTarget, Islands[islandIdx].reload);
			string locatorName, captainId, GroupName;
			//--> ������� ���� 
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + 2; //15
				else Rank = sti(pchar.rank);  //10
			}
			else
			{
				Rank = sti(pchar.rank);
			}	
			//<-- ������� ���� 
			//���������� �������� ��� ���������� ���������
			makearef(arQuestLoc, Islands[islandIdx].Quest_ships);
			iTemp = GetAttributesNum(arQuestLoc)-1; 
			int n = 0;
			int iRand = rand(4);			
			for (i=iTemp; n<5; i--)
			{
				arLocator = GetAttributeN(arQuestLoc, i);
				locatorName = GetAttributeName(arLocator);
				sTemp = "l" + n;
				if (findsubstr(locatorName, "Quest" , 0) != -1)
				{
					if (iRand == n)
					{
						//==> ������ ������
						Group_AddCharacter("MQGroupPirate", "MQPirate");			
						Group_SetType("MQGroupPirate", "pirate");
						Group_SetGroupCommander("MQGroupPirate", "MQPirate");
						Group_LockTask("MQGroupPirate");
						Group_SetAddress("MQGroupPirate", pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);						
						int iShore = GetAttributesNum(arPlTarget)-1;
						arLocator = GetAttributeN(arPlTarget, iShore);
						locatorName = GetAttributeName(arLocator);						
						Group_SetTaskMove("MQGroupPirate", stf(arPlTarget.(locatorName).ships.(sTemp).x), stf(arPlTarget.(locatorName).ships.(sTemp).z))
					}
					else
					{
						//������ ���������
						captainId = "MQCaptain_" + n;
						GroupName = "MQGroupAll_" + n;
						sld = GetCharacter(NPC_GenerateCharacter(captainId, "", "man", "man", Rank, sti(npchar.nation), -1, true));					
						SetCaptanModelByEncType(sld, "trade");
						DeleteAttribute(sld, "Ship");
						SetShipToFantom(sld, "trade", true);
						sld.Ship.Mode = "Trade";
						sld.AlwaysSandbankManeuver = true;
						sld.DontRansackCaptain = true;  //fix
						Group_AddCharacter(GroupName, captainId);
						Group_SetGroupCommander(GroupName, captainId);
						Group_SetAddress(GroupName, pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);					
						Group_SetTaskMove(GroupName, stf(arPlTarget.l1.ships.(sTemp).x), stf(arPlTarget.l1.ships.(sTemp).z));
					}
					n++;
				}
			}
			//���������� ������ � ����� �������, ����������
			sld = characterFromId("MQPirate"); 
			iTemp = RealShips[sti(sld.ship.type)].basetype; 
			pchar.GenQuest.DestroyPirate.ShipType = GetShipSexWord(ShipsTypes[iTemp].name, "��������� ", "��������� ") + XI_ConvertString(ShipsTypes[iTemp].name+"Gen");
			//���������� �� ������ ������
			pchar.quest.DestroyPirate.win_condition.l1 = "NPC_Death";
			pchar.quest.DestroyPirate.win_condition.l1.character = "MQPirate";
			pchar.quest.DestroyPirate.win_condition = "DestroyPirate_after";
			//������
			SetTimerCondition("DestroyPirate_Late", 0, 0, sti(pchar.GenQuest.DestroyPirate.Terms), false);
			//������� ������
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));			
		break;
		
		case "DestroyPirate_WithoutFight":	
			pchar.quest.Munity = "Deads";  // ������� �����
			sld = characterFromId("MQPirate");
			sld.money = pchar.money;
			pchar.money = 0;
			Ship_SetTaskRunaway(SECONDARY_TASK, sti(sld.index), 1); //���������
		break;

		case "DestroyPirate_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			Rank = 5 + sti(MOD_SKILL_ENEMY_RATE);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<Rank; i++)
			{				
				iTemp = GetCharacterIndex("saylor_0"+i);
				if ( iTemp == -1) 
				{
					iTemp = NPC_GenerateCharacter("saylor_0" + i, "pirate_"+(rand(9)+1) , "man", "man", 10, PIRATE, 0, true);
					ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				}
				LAi_group_MoveCharacter(&characters[iTemp], "EnemyFight");
			}
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DestroyPirate_TeamIsDead");
		break;

		case "DestroyPirate_TeamIsDead":
      		Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
			Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";			
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			DoQuestCheckDelay("TalkSelf_Quest", 0.4); //������ ���-��-���
		break;

		case "DestroyPirate_PirateIsOut":
			pchar.quest.DestroyPirate_Late.over = "yes"; //������� ������
			pchar.GenQuest.DestroyPirate = "PirateIsOut"; //���� ����� ������
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i=0; i<5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			// �����
			AddSimpleRumour(LinkRandPhrase("�� ������� � �������� ��� �������� " + GetMainCharacterNameGen() + " � ��������? �������, ��� ������ ������ ����������� �� ��"+ GetSexPhrase("��","�") +"...", 
				"�������, ��� �� ����� �������� ���� �������?! �-��, ����� � ����� ����...", 
				"��, ������� " + GetFullName(pchar) + ", ��� �� ��� �� �������� ���� �������, �? ��� ������ ����� � ����..."), sti(npchar.nation), 5, 1);
		break;

		case "DestroyPirate_after":
			pchar.quest.DestroyPirate_PirateIsOut.over = "yes"; //������� ���������� �� ���� � ���� ���
			pchar.quest.DestroyPirate_Late.over = "yes"; //������� ������
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			pchar.GenQuest.DestroyPirate = "Execute"; //���� �������� �������
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			// ������� ������
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "ShipType", GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));			
			// �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + GetFullName(npchar) + " ������� ������� �������� " + GetMainCharacterNameDat() + " ����� � ���������� ������, ������� ��������� �������� � ��������� �����. ��� ���, ��� ���"+ GetSexPhrase("��","��") +" � �������"+ GetSexPhrase("","�") +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!", 
				""+ GetSexPhrase("�����-�� ������ ������� ��������","�����-�� ������ ������� ���������") +" ����� � ���������� ������, ��������� ����� ���������. �, ������, ��"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("","�") +" ��� - �������"+ GetSexPhrase("","�") +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!", 
				"��, �������-�� ��� ���������� ������ �� ����������� ����������� �������� � ����� " + XI_ConvertString("Colony"+npchar.city+"Gen") + " - �� ������� �������� " + GetMainCharacterNameDat() + " ��������� ������, �� ��������� ����� ����� ���������. � �� ������, ��"+ GetSexPhrase("�� �������","� �������") +" �������"+ GetSexPhrase("","�") +" " + GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType) + "!"), sti(npchar.nation), 5, 1);			
		break;

		case "DestroyPirate_Late":
			if (bSeaActive)
			{
      			Pchar.quest.AllMayorsQuests_Late.win_condition.l1 = "ExitFromSea";
				Pchar.quest.AllMayorsQuests_Late.win_condition = "AllMayorsQuests_Late";
			}
			else
			{
				DoQuestCheckDelay("AllMayorsQuests_Late", 0.1);
			}
		break;

		case "DestroyPirate_toShore":
			sTemp = pchar.GenQuest.questName;
			pchar.quest.DestroyPirate_Late.over = "yes"; //������� ������
			pchar.GenQuest.(sTemp) = "Found";
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			int lngFileID = LanguageOpenFile("LocLables.txt");
			attrName = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
			//������� ������
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "Shore", attrName);			
			// �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + GetFullName(npchar) + " ������� ������� �������� " + GetMainCharacterNameDat() + " ����� � ���������� ������, ��� ������ ��������� � ��� ��� �����. � ��� �� �������, �� ������� � �������� " + GetMainCharacterNameGen() + " ����!", 
				"�������, ��� ��� ����������� �� ��������� �������? ���������? ��� ��� �� �������? ��-��-��!!", 
				"�-�-�, �������, � ������ ��� ������� ��������� �������, ��-��... ��� ��� ������� ������? �� ������ ��� �� ��������? ��-��-��!!"), sti(npchar.nation), 5, 1);
			//������� ��������� ������ � ���������
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i=0; i<5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			pchar.money = 0;
			pchar.quest.Munity = "Deads";
			pchar.location.from_sea = npchar.city + "_town";
			//--> ��� ����� ����� �� ������ �� ������ � �����
			DoReloadFromDeckToLocation(pchar.GenQuest.DestroyPirate.outShoreId, "reload", "sea");
			//<-- ��� ����� ����� �� ������ �� ������ � �����
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����    ����� � ����������� ������
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  ������   ��������� - ��������� �������� "�������� '������'"
		//////////////////////////////////////////////////////////////////////// 		

		case "CaptainComission_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
			LAi_group_Delete("EnemyFight");
			for (i=1; i < 5; i++) 
			{	
				sld = characterFromID("saylor_0" + i);
				sld.rank = Rank;
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CaptainComission_TeamIsDead");
		break;
		
		case "CaptainComission_TeamIsDead":
      		pchar.quest.CaptainComission_CapIsOut.win_condition.l1 = "ExitFromSea";
			pchar.quest.CaptainComission_CapIsOut.function = "CaptainComission_CapIsOut";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapIsDead.function = "CaptainComission_CapIsDead";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			DoQuestCheckDelay("TalkSelf_Quest", 0.4); //������ ���-��-���
		break;		
				
		case "CaptainComission_TalkCanoneer":
			LAi_Fade("CaptainComission_TalkCanoneer_prepare", "CaptainComission_TalkCanoneer2");
		break;
		
		case "CaptainComission_TalkCanoneer_prepare":
			LAi_SetSitType(pchar);
			sld = characterFromID("CapComission_Canoneer");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);			
			ChangeCharacterAddressGroup(pchar, pchar.GenQuest.CaptainComission.City + "_tavern", "sit", "sit_front2");
		break;
		
		case "CaptainComission_TalkCanoneer2":
			LAi_ActorDialogNow(characterFromID("CapComission_Canoneer"), pchar, "", -1);
		break;
		
		case "CaptainComission_exit_sit":
			if (pchar.location.group == "sit")
			{
				LAi_Fade("CaptainComission_exit_sit_2", "");
			}
		break;

		case "CaptainComission_exit_sit_2":
   			sld = characterFromID("CapComission_Canoneer");
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location); // ������� � �����
		break;

		case "CaptainComission_GangDialog_1":
			sld = characterFromID("Gang_0");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		break;
				
		case "CaptainComission_MapEnterAfterShoreBattle":
			for (i = 1; i <=3; i++)
			{
				iTemp = GetCharacterIndex("Pirate_Captain0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			Group_DeleteGroup("Pirate_Guards"); 
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_GenerateCapJail":
			sld = characterFromID("CapComission_1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.CaptainComission.City + "_prison", "goto", "goto9");
			LAi_group_MoveCharacter(sld, "Prisoner_Group"); 
			LAi_SetCitizenType(sld);	
		break;
		
		case "CaptainComission_PrisonFree_Death":			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			AddQuestRecord("CaptainComission2", "22");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_DeletePrisonGroup":
			LAi_group_Delete("CapComission_Prison");
		break;

		case "CaptainComission_ExitFromPrison":
			iTemp = GetCharacterIndex("CapComission_1");
			if (iTemp != -1)
			{
				pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";           	
				pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";						
				pchar.GenQuest.CaptainComission.canSpeakCaptain = true;
				pchar.TownEscape = true;
			}
		break;
		
		case "CaptainComission_MeetWithCaptain":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "CaptainComission_MapEnterCapDied":
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;
		
		case "CaptainComission_ShoreGangDialog":
			SetMainCharacterIndex(1);
			pchar = GetMainCharacter();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar)
			locCameraFollow();
			EndQuestMovie(); 	
			ChangeShowIntarface();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;			
			DoQuestFunctionDelay("CaptainComission_BattleInShore", 8.0); 
		break;
 		////////////////////////////////////////////////////////////////////////
		//  �����   ��������� - ��������� �������� "�������� '������'"
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  ������   ��������� - "���������������"
		//////////////////////////////////////////////////////////////////////// 		
		
		case "ShipWreck_RemoveSailorsFromShore":
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				iTemp = GetCharacterIndex("ShipWreck_" + i);		
				if(iTemp != -1)
				{
					Characters[iTemp].LifeDay = 0;
				}
			}	
			DeleteAttribute(pchar, "GenQuest.ShipWreck");		
		break;
		
		////////////////////////////////////////////////////////////////////////
		//  �����   ��������� - "���������������"
		//////////////////////////////////////////////////////////////////////// 				
		
  		////////////////////////////////////////////////////////////////////////
		//  ������    ��������� � �������
		//////////////////////////////////////////////////////////////////////// 		
		case "Berglars_Ostin": 
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("Ostin", "Ostin", "man", "man", 30, SPAIN, -1, false));
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.name 	= "��������";
			sld.lastname = "������";
			sld.rank = 30;
			sld.dialog.filename   = "Quest\Berglars.c";
			sld.dialog.currentnode = "Final_fight";
			sld.greeting = "Gr_OliverTrast";
			sld.money = 30670;
			sld.SaveItemsForDead  = true; 
			sld.DontClearDead = true;
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			TakeNItems(sld, "jewelry1", 20+rand(5));
			TakeNItems(sld, "jewelry2", 14+rand(5));
			TakeNItems(sld, "jewelry3", 18+rand(5));
			TakeNItems(sld, "jewelry4", 16+rand(5));
			//��������
			TakeNItems(sld, "talisman8", 1);
			GiveItem2Character(sld, "icollection");
			GiveItem2Character(sld, "spyglass4");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
  		////////////////////////////////////////////////////////////////////////
		//  �����    ��������� � �������
		//////////////////////////////////////////////////////////////////////// 

   		////////////////////////////////////////////////////////////////////////
		//  ������   �������
		//////////////////////////////////////////////////////////////////////// 
        case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //��������� �������
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname+"_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //������� ���� � �������
			//==> ���� ������
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
        break;	
		////////////////////////////////////////////////////////////////////////
		//  �����    �������
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  ������    ������ ���������� ��������
		//////////////////////////////////////////////////////////////////////// 
        //--------------------- �������� ����� ����� ���-���� ���� ����� � ���������� -----------------------
		case "PearlGen_checkSantaCatalina":
			if (locations[reload_cur_location_index].id == "Pearl_CaveEntrance")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlSantaCatalina") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlSantaCatalina") > 30)
				{				
					LAi_group_Delete("PearlGroup_2");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //�������������� �������� �����, �� �����-��������
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlSantaCatalina");
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_2", "pirate_"+(rand(9)+1), "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+RandFromThreeDight(3, 4, 8));
					sld.city = "SantaCatalina"; //��� �����-��������
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "PearlGroup_2");
					locations[FindLocation("Pearl_town_2")].pearlVillage = true; //���� �������� �����������
					bOk = true;	//���
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{	
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) 
							{
								Log_SetStringToLog("�������� ���������� ����������!");
								LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);					
								bOk = false; //�����
							}
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //�������� ����
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_2" && GetCharacterIndex("HeadMan_2") == -1)
				{
					iTemp = 0;
					for(i=0; i<MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_2")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //������� ������� ������������� ���������� � ����� ����������
					{
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1.location = "Pearl_Jungle_06";
			pchar.quest.PearlGen_SetNewInterrapt_2.function = "PearlGen_SetSantaCatalina";
		break;

		//----------------------------------- �������� ����� ����������� --------------------------------------
        case "PearlGen_checkTeno":
			if (locations[reload_cur_location_index].id == "Pearl_Jungle_03")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlTeno") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlTeno") > 30)
				{				
					LAi_group_Delete("PearlGroup_1");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //�������������� �������� �����, �� �����-��������
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlTeno");
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_1", "pirate_"+(rand(9)+1), "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+RandFromThreeDight(1, 9, 8));
					sld.city = "SantaCatalina"; //��������� ���
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "PearlGroup_1");
					locations[FindLocation("Pearl_town_1")].pearlVillage = true; //���� �������� �����������
					bOk = true;	//���
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{	
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) 
							{
								Log_SetStringToLog("�������� ���������� ����������!");
								LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);					
								bOk = false; //�����
							}	
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //�������� ����
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_1" && GetCharacterIndex("HeadMan_1") == -1)
				{
					iTemp = 0;
					for(i=0; i<MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_1")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //������� ������� ������������� ���������� � ����� ����������
					{
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1.location = "Pearl_Jungle_02";
			pchar.quest.PearlGen_SetNewInterrapt_1.function = "PearlGen_SetTeno";
        break;

        case "PearlToShore_ForSale":
			chrDisableReloadToLocation = false;
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.quest.PearlToShore_ForSale.idx)]);
        break;

        case "Pearl_GuardManIsLife":
			sld = &characters[sti(pchar.quest.Pearl_GuardManIsLife.idx)];
			sld.dialog.Filename = "Pearl_dialog.c";
 			sld.dialog.currentnode = "GuardManAllarm";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);			
        break;

		////////////////////////////////////////////////////////////////////////
		//  �����    ������ ���������� ��������
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  ������ �������� ������
		//////////////////////////////////////////////////////////////////////// 
        case "GivePrisonFree":
			chrDisableReloadToLocation = true;
			LAi_LocationDisableMonstersGen(pchar.location, true);
			pchar.quest.GivePrisonFree_Death.over = "yes";
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			sld.dialog.currentnode = "PrisonerInPlace";
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;

        case "GivePrisonFree_Death":
			AddQuestRecord("GivePrisonFree", "2");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.GivePrisonFree.over = "yes";
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "GivePrisonFree_Over":
			AddQuestRecord("GivePrisonFree", "6");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
			if (iTemp > 0) 
			{
				characters[iTemp].lifeDay = 0;
				ChangeCharacterAddress(&characters[iTemp], "none", "");	
			}
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "DeliverToBander":
			if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
			{
				LAi_group_Delete("EnemyFight");
				chrDisableReloadToLocation = true;
				pchar.quest.DeliverToBander.over = "yes";
				pchar.quest.DeliverToBander_over.over = "yes";
				//--> ������� ���� 
				if (sti(pchar.rank) > 6) 
				{
					Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
				}
				else  
				{	//�������� ������� ���� �� ������ ����
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else 
					{
						Rank = 1;
					}
				}	
				//<-- ������� ����
				GetCharacterPos(pchar, &locx, &locy, &locz);
				for (i=1; i<=2; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Bander_"+i, "pirate_"+(rand(9)+1), "man", "man", Rank, PIRATE, 0, true));
					sld.dialog.filename = "quest\Banders_dialog.c";
					sld.dialog.currentnode = "First time";
					sld.greeting = "cit_common"; 
					SetFantomParamFromRank(sld, Rank, true);
					if (i == 1)
					{
						LAi_SetOwnerType(sld);
						sld.dialog.currentnode = "Second time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
					}
					else
					{
						LAi_SetActorType(sld);
						sld.dialog.currentnode = "First time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
					}
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_ActorDialog(sld, pchar, "", 1.0, 0); 
			}
		break;

        case "DeliverToBander_over":
			AddQuestRecord("GivePrisonFree", "9");
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.DeliverToBander.over = "yes";
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeliverToBander_Dead":
			AddQuestRecord("GivePrisonFree", "10");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			CloseQuestHeader("GivePrisonFree");
			
			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			
            chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeletePrisonGroup":
			LAi_group_Delete("DeliveQuest_Prison");
		break;
		////////////////////////////////////////////////////////////////////////
		//  �����  �������� ������
		//////////////////////////////////////////////////////////////////////// 

		// ������������� �������������� (�� �����  SetActorDialogAny2Pchar)
        case "ActorDialog_Any2Pchar":
            LAi_SetActorType(PChar);
            LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
            LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
        break;

        case "OpenTheDoors":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
			//#20190804-01
			if(CheckAttribute(pchar, "tmpKillGroup")) {
                LAi_group_SetAlarm(pchar.tmpKillGroup, LAI_GROUP_PLAYER, 0.0);
                DeleteAttribute(pchar, "tmpKillGroup");
            }
        break;
		//�������
		case "Dovahkiin":
            PlaySound("Interface\P_Dovahkiin.wav");
			Log_TestInfo("������ ���� ����");
			pchar.Dovahkiin = 1;
        break;
		case "PGGLeft":
			Log_TestInfo("��� ����");
			sld = CharacterFromID(pchar.chosenHero);
			DeleteAttribute(pchar, "chosenHero");
			string futureLoc = sld.PGGAi.location.town.backup + "_Tavern";
			ChangeCharacterAddressGroup(sld, futureLoc, "goto", "goto1");
			LAi_SetImmortal(sld, false);
			if (CheckAttribute(sld, "PGGOfficers"))
			{
				for (i = 0; i < sti(sld.PGGOfficers); i++)
				{
					chr = CharacterFromID("PGGOfficer" + i);
					ChangeCharacterAddressGroup(chr, futureLoc, "goto", "goto1");
				}
				DeleteAttribute(sld, "PGGOfficers");
			}
        break;

        case "CanEnterToMap":
            bQuestDisableMapEnter = false;
        break;

        case "CloseBermudesDungeonDoor":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
        break;

        case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
        break;

        case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
        break;
        //#20190527-01
        case "CannotFightCurLocationAStop":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
			LAi_group_SetAlarm(LAI_GROUP_PLAYER, "EnemyFight", 0.0);
        break;

        case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
        break;

        case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
        break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;
		
		case "MayorSitBack": //�������� ���� �������
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			}
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START ���������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==========================   ����� N1, ������������� ������� ���������� ========================

        case "fight_withSpanish_Albermal":                      //  ����� ������� �� ��� ������� � �����������
            bQuestDisableMapEnter = true;
            Island_SetReloadEnableGlobal("Antigua", false);

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_2", "man", "man", 15, SPAIN, 0, true));
            FantomMakeCoolSailor(sld, SHIP_NIGHTMARE, "", CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
            FantomMakeCoolFighter(sld, 20, 90, 50, "blade25", "pistol3", 80);
            sld.DontRansackCaptain = true; //��������� �� �������
            sld.SinkTenPercent = true; //������ � �������������
            
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Antigua", "", "");
			Group_LockTask("Spa_Attack");

			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1 = "NPC_Death";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition = "after_fight_withSpanish_Albermal";
        break;

        case "after_fight_withSpanish_Albermal":                  // ��������� ����� �� ��� ��� ��������
            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1 = "location";
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1.location = "SentJons_townhall";
			pchar.quest.goto_Oxbay_Albermal.win_condition = "goto_SentJons_Albermal";
            AddQuestRecord("Eng_Line_1_Albermal", "3");
            group_DeleteGroup("Spa_Attack");
        break;

        case "goto_SentJons_Albermal":
            sld = characterFromID("Albermal");                    //  ���������� � ���������� �����������
            ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
			sld.dialog.currentnode = "in_the_SentJons";
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Albermal", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

//==========================   ����� N3, ��������� �� ����� ========================
        case "time_over_Beliz_attack":
            // 50 ���� �� ������ ������, ������� � ������ �� ����� ��������, ���� ������ �����, ��� ��� ��� �����
            if (IsEntity(worldMap))
            {
                if (!bQuestCheckProcessFreeze) // ����� ��������
				{
	        		pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // �����, ���� ��� �����������
	        		pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";
                   
                    makearef(arOldMapPos, worldMap.old);
                    WdmPrepareMapForAbordage(arOldMapPos);
                    MakeCloneShipDeck(pchar, true); // ������� ������
                    DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
	                ReloadFromWMtoL_complete();
	                
                    sld = characterFromID("Henry Morgan");
                    ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
                    LAi_SetWarriorType(sld);
	                LAi_warrior_DialogEnable(sld, true);
	                sld.dialog.currentnode = "time_over_Beliz";
   	                // ==> �������
                    for (i=1; i<5; i++)
        			{
                        attrName = "pirate_" + i;
                        sld = GetCharacter(NPC_GenerateCharacter(attrName, attrName, "man", "man", 15, PIRATE, 1, true));
                        sld.dialog.Filename = "Quest\sailors_dialog.c";
	                    sld.dialog.currentnode = "Morgan_wait_you";
                    	LAi_SetWarriorType(sld);
                    	LAi_warrior_DialogEnable(sld, true);
                    	LAi_SetLoginTime(sld, 0.0, 24.0);
                    	LAi_SetHP(sld, 100.0, 100.0);
                    	ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto"+i);
                    }
                	pchar.quest.Munity = "";  // ������� ������ � ������ (�������, � �� ����� �� ��������)
            		LAi_LockFightMode(pchar, true);
				}
				else
				{   // ������� �� ���������� (������ ��������)
      				Pchar.quest.time_over_Beliz_attack_Map_01.win_condition.l1 = "MapEnter";
                    Pchar.quest.time_over_Beliz_attack_Map_01.win_condition = "time_over_Beliz_attack";
		        }
			}
			else
			{   // �������� ������ �� �����, ��� ����� ������, �� �� �� �� ���
			    Pchar.quest.time_over_Beliz_attack_Map_02.win_condition.l1 = "MapEnter";
                Pchar.quest.time_over_Beliz_attack_Map_02.win_condition = "time_over_Beliz_attack";
			}
        break;

//==========================   ����� N4, ������������ � ������� ========================
        case "Intelligence_Curacao_GoToShore":    //  ������� � ������ ���� �������.
            if (pchar.questTemp.State == "Intelligence_Curacao_FightGard" || pchar.questTemp.State == "Intelligence_Curacao_OutPrison")
            {
                LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_Bank")], true); // ������� ������ �� ������
                sld = characterFromID("Villemstad_usurer");
                ChangeCharacterAddressGroup(sld, "Villemstad_Bank", "goto", "goto1");
	            LAi_SetBarmanType(sld);
                LAi_SetHP(sld, 80, 80); //������� ���������� ���� ����
                pchar.quest.Intelligence_Curacao_OutTown.over = "yes";
            }
            else    //==> ������ � ����������� ������
            {
                bQuestDisableMapEnter = true;
                Island_SetReloadEnableGlobal("Curacao", false);

				pchar.questTemp.abordage = 0; // ��������� ������� �������� - ��� ����� �������

                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_hol_2", "man", "man", 23, HOLLAND, 0, true));
                FantomMakeCoolSailor(sld, SHIP_BRIGHEAVY, "", CANNON_TYPE_CANNON_LBS32, 95, 95, 95);
                FantomMakeCoolFighter(sld, 25, 90, 50, BLADE_LONG, "pistol3", 100);
                sld.DontRansackCaptain = true; //��������� �� �������
                sld.SinkTenPercent = true; // ������ � �������������
				sld.Ship.name = "��������";
                
    			Group_FindOrCreateGroup("Hol_Attack");
    			Group_SetType("Hol_Attack", "war");
    			Group_AddCharacter("Hol_Attack", "CaptainAttack_1");
    			Group_SetGroupCommander("Hol_Attack", "CaptainAttack_1");			    
			    Group_SetAddress("Hol_Attack", "Curacao", "", "");
				Group_SetPursuitGroup("Hol_Attack", PLAYER_GROUP);
                Group_SetTaskAttack("Hol_Attack", PLAYER_GROUP);
				Group_LockTask("Hol_Attack");
    			//==> ������� ���������� ������ � ����� ����
    			pchar.questTemp.EngLineQ4_PutLetter = 1;

    			pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1 = "Character_Capture";
    			pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1.character = "CaptainAttack_1";
    			pchar.quest.Intelligence_Curacao_Boarding.win_condition = "Intelligence_Curacao_Boarding";

    			pchar.quest.Intelligence_Curacao_Sink.win_condition.l1 = "Character_sink";
    			pchar.quest.Intelligence_Curacao_Sink.win_condition.l1.character = "CaptainAttack_1";
    			pchar.quest.Intelligence_Curacao_Sink.win_condition = "Intelligence_Curacao_Sink";
            }
        break;

        case "Intelligence_Curacao_Sink":   // ����������� ���� ��������
            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.questTemp.State = "Intelligence_Curacao_Sink";
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "8");
            group_DeleteGroup("Hol_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
            BackItemDescribe("letter_1");
            pchar.quest.Intelligence_Curacao_Boarding.over = "yes";
        break;

        case "Intelligence_Curacao_Boarding":   // ����������� ���� ��������
            pchar.quest.Intelligence_Curacao_Sink.over = "yes";
			if (CheckCharacterItem(pchar, "letter_1"))
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "9");
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("��","��"));
                pchar.questTemp.State = "Intelligence_Curacao_Boarding";
                TakeItemFromCharacter(pchar, "letter_1");
                ChangeItemDescribe("letter_open", "itmdescr_letter_open_EngLineQ4");
                GiveItem2Character(pchar, "letter_open");
            }
            else
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "11");
                pchar.questTemp.State = "Intelligence_Curacao_BoardingNotFoundLetter";
            }

            bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.Intelligence_Curacao_Sink.over = "yes";
            group_DeleteGroup("Hol_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
            BackItemDescribe("letter_1");
        break;

		case "Intelligence_Curacao_KickYozef":  // �� �������� � ���� � ����������.
            LAi_SetFightMode(pchar, false);
            DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto9");
			LAi_SetImmortal(pchar, false);
            // ==> �������� ������, ������� � ������.
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
            while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
            {
                TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
            }
            while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
            {             
                TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
            }
            pchar.money = 0;
            // <== �������� ������, ������� � ������.
			TakeNationLicence(HOLLAND);
            DoQuestCheckDelay("Intelligence_Curacao_GoPrisonMan", 10);
            sld = GetCharacter(NPC_GenerateCharacter("Hoverd_Tantum", "citiz_11", "man", "man", 15, ENGLAND, 3, false));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	sld.name 	= "������";
        	sld.lastname = "������";
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
        break;

        case "Intelligence_Curacao_GoPrisonMan":
            sld = characterFromID("Hoverd_Tantum");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Intelligence_Curacao_TalkingPrisonMan", -1);
        break;

        case "Intelligence_Curacao_TalkingPrisonMan":
            sld = characterFromID("Hoverd_Tantum");
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
        break;

//==========================   ����� N5, ��������� �� ���� ����� ========================
        // boal ����� ���������� �� ���������� ������� � ���� -->
		case "AttackFortOrange_GoToFort":
    	    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState(sld.city + "_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);
            Log_SetStringToLog("�� �����, ����!");
            // ��������� ������ ������ � ���������� ��� ������� ������
            //string _city, string _method, bool _majorOff
            SetCaptureResidenceQuest("FortOrange", "", true); // ��, ��� ������, ����������� � ���
            
            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1.location = "FortOrange_townhall";
            Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition = "AttackFortOrange_FightWithCommendant";
        break;

        case "AttackFortOrange_FightWithCommendant":
            chrDisableReloadToLocation = true; // ������� ����� �� �������
            bDisableFastReload = true; // ������� ��������.
			//--> ����� � �������
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;		
			//<-- ����� � �������

            sld = GetCharacter(NPC_GenerateCharacter("Orange_Comendant", "off_hol_2", "man", "man", 25, HOLLAND, 0, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	LAi_SetWarriorType(sld);
            LAi_warrior_DialogEnable(sld, true);
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
            sld.DontClearDead = true; // �� ������� ���� ����� 200�
            sld.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
            LAi_LoginInCaptureTown(sld, true);
            FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 30);
            Statistic_AddValue(Pchar, "hol_GrabbingTown", 1); // ����������
           	ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.2);
        break;

        case "AttackFortOrange_AfterFightWithCommendant":
            AfterTownBattle();
            chrDisableReloadToLocation = false; 
            bDisableFastReload = false; 
            pchar.questTemp.State = "AttackFortOrange_WeWin";
            AddQuestRecord("Eng_Line_5_AttackFortOrange", "2");
        break;
        
//==========================   ����� N6, ������ ������� ========================
        case "MorrisWillams_ShipToPort":
            Log_QuestInfo("�� ����� ���� ����� ���������� ������ ������� ��������.");
            sld = GetCharacter(NPC_GenerateCharacter("Morris_Willams", "MorrisWillams", "man", "man", 25, ENGLAND, -1, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
        	sld.name 	= "������";
        	sld.lastname = "�������";
        	sld.Abordage.Enable = false; // ������!
			sld.greeting = "Gr_MiddPirate";
            LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_SALAMANDER, "�������", CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
            FantomMakeCoolFighter(sld, 28, 70, 40, BLADE_LONG, "pistol4", 100);
            sld.Ship.Stopped = true;
            sld.DeckDialogNode = "First time";
			sld.Ship.Mode = "Pirate";
            
			Group_FindOrCreateGroup("Willams_Group");
			Group_AddCharacter("Willams_Group", "Morris_Willams");
			Group_SetGroupCommander("Willams_Group", "Morris_Willams");
            Group_SetAddress("Willams_Group", "Jamaica", "quest_ships", "quest_ship_1");

			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1 = "NPC_Death";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1.character = "Morris_Willams";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition = "MorrisWillams_WillamsAttack";
        break;

        case "MorrisWillams_WillamsAttack":
            sld = characterFromID("Morris_Willams");
    	    sld.LifeDay = 1; // ������ ��� �� ����.����.
    	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
            pchar.questTemp.State = "QuestLineBreake";
            ChangeCharacterReputation(pchar, -20);
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
        break;

        case "MorrisWillams_MeetWithManFromWillams":
			chrDisableReloadToLocation = true;
            Log_QuestInfo("������ ������� � �������� ��������.");
            pchar.quest.MorrisWillams_WillamsAttack.over = "yes"; // ������� ���������� �� ���������� �������

            sld = GetCharacter(NPC_GenerateCharacter("Bocman_Willams", "officer_15", "man", "man", 25, ENGLAND, -1, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	sld.name 	= "����";
        	sld.lastname = "����";
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "MorrisWillams_InTavernWithWillams":
            sld = characterFromID("Morris_Willams");            
            FreeSitLocator("PortRoyal_tavern", "sit11");
			LAi_SetSitTypeNoGroup(sld);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit11");
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //�� ������ ������, ����� ������ �� ������.
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
        break;

        case "MorrisWillams_CheckTimeForForward":
            if (GetQuestPastTimeParam("questTemp") < 2)
            {
                Log_QuestInfo("����� ����� � ���� �� ��� ���� �������� �������. ����� ������ ���� �� �����.");
                Pchar.quest.MW_AttackPinnace.win_condition.l1 = "location";
                Pchar.quest.MW_AttackPinnace.win_condition.l1.location = "PuertoRico";
                Pchar.quest.MW_AttackPinnace.win_condition = "MW_AttackPinnace";
                SetTimerCondition("MorrisWillams_PinaceTimeOver", 0, 0, 16, false);
            }
            else
            {
                Log_QuestInfo("�� ����� ����� � ���� �� ��� ���� �������� �������. ������ �� �����.");
                pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
                characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
            }
        break;

        case "MorrisWillams_PinaceTimeOver":
            pchar.quest.MW_AttackPinnace.over = "yes";
            Log_QuestInfo("����� �� ��������, �� ����� �� 16 ����.");
            pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
            characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
        break;

        case "MW_AttackPinnace":
            Log_QuestInfo("����� ���������� ����� ������ � ��������� ���������.");
            Island_SetReloadEnableGlobal("PuertoRico", false);
            characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 28, SPAIN, 0, true));
            sld.SinkTenPercent = true; // ������ � �������������
            sld.DontRansackCaptain = true; //��������� �� �������

            FantomMakeCoolSailor(sld, SHIP_PINNACE, "����� ������", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 100);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "trade");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetAddress("Spa_Attack", "PuertoRico", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
//            Group_SetTaskMove("Spa_Attack", 1930.0, -315.0);
            Group_LockTask("Spa_Attack");

            //==> ������� ���������� ������ � ������
            pchar.questTemp.EngLineQ6_PutMoney = 1;
            pchar.questTemp.QtyMoneyTillBoarding = pchar.money;  // ��������� ���-�� ����� �� ��������, ����� ��� ����������� ���� �� �� ����� �� ������� � �����

			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition = "MorrisWillams_PinnaceBoarding";

			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1 = "Character_sink";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition = "MorrisWillams_PinnaceSink";

			pchar.quest.MorrisWillams_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.MorrisWillams_DieHard.win_condition = "MorrisWillams_DieHard";
            pchar.quest.MorrisWillams_PinaceTimeOver.over = "yes";  // ������� ������ �� �������� ������ � �������
        break;


        case "MorrisWillams_PinnaceBoarding":
			iTemp = sti(pchar.money) - sti(pchar.questTemp.QtyMoneyTillBoarding);
            if (iTemp >= 140000)
            {
                Log_QuestInfo("����� ���� �� �������, ������ �������.");
                AddQuestRecord("Eng_Line_6_MorrisWillams", "10");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex1", GetSexPhrase("��","��"));
                pchar.questTemp.State = "MorrisWillams_PinnaceBoard";
            }
            else
            {
                Log_QuestInfo("����� ���� �� �������, ������ �� �������. ������ ���������.");
                AddQuestRecord("Eng_Line_6_MorrisWillams", "23");
                pchar.questTemp.State = "MorrisWillams_PinnaceBoardNotFoundMoney";
            }
            Island_SetReloadEnableGlobal("PuertoRico", true);
            group_DeleteGroup("Spa_Attack");
            Pchar.quest.MorrisWillams_DieHard.over = "yes";
            pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_PinnaceSink":
            Log_QuestInfo("����� ��������.");
            Island_SetReloadEnableGlobal("PuertoRico", true);
            Pchar.quest.MorrisWillams_DieHard.over = "yes";
            pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
            pchar.questTemp.State = "MorrisWillams_PinnaceSink";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "11");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_DieHard":
            Log_QuestInfo("�� ����� ����� �����. ������ ������ ���.");
            Island_SetReloadEnableGlobal("PuertoRico", true);
            pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
            pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
            pchar.questTemp.State = "MorrisWillams_DieHard";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "12");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
            DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
        break;

        case "MorrisWillams_Arrest":
            Log_QuestInfo("������ ������� � �������� ��������.");
			chrDisableReloadToLocation = true;
            sld = characterFromID("Bocman_Willams");
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "MorrisWillams_HusbandInCave":
            Log_QuestInfo("������ � ����� ������. ����� ������ � ��������� � �� �����.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 20, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 50);
            	LAi_SetWarriorType(sld);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Jamaica_Grot", "monsters",  "monster"+i);
            }
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.5);

            npchar = GetCharacter(NPC_GenerateCharacter("Jillians_Husband", "citiz_3", "man", "man", 10, ENGLAND, 0, false));
            npchar.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	npchar.name 	= "���";
        	npchar.lastname = "���������";
            ChangeCharacterAddressGroup(npchar, "Jamaica_Grot", "monsters", "monster4");
            LAi_SetActorType(npchar);
            LAi_SetImmortal(npchar, true);
            LAi_ActorWaitDialog(npchar, pchar);
        break;

        case "MorrisWillams_AftreFightingInCave":
            pchar.questTemp.State = "MorrisWillams_AfterFight";
            LAi_SetActorType(pchar);
            sld = characterFromID("Jillians_Husband");
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		    chrDisableReloadToLocation = false; // ������� ����� �� �������.
        break;

        case "MorrisWillams_SeekCirassa":
			Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
			LAi_LocationDisableOffGenTimer("Shore_ship2", 1); //�������� �� ������� 1 ����
            for (i=1; i<=7; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Skelet"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 25, PIRATE, 0, true));
                if (i == 2)
                {
                	sld.name 	= "�������";
                	sld.lastname = "�����";
                    sld.SaveItemsForDead = true; // ��������� �� ����� ����
                    sld.DontClearDead = true;
                    FantomMakeCoolFighter(sld, 40, 100, 70, BLADE_LONG, "pistol3", 110);
                    GiveItem2Character(sld, "cirass5");
                    GiveItem2Character(sld, "map_nevis");
                    GiveItem2Character(sld, "map_normal");
                    GiveItem2Character(sld, "spyglass4");
                    TakeNItems(sld, "jewelry5", 150);
					TakeNItems(sld, "jewelry1", 54);
					TakeNItems(sld, "jewelry2", 32);
					TakeNItems(sld, "jewelry3", 41);
					TakeNItems(sld, "jewelry5", 25);
                }
                else FantomMakeCoolFighter(sld, 25, 80, 60, BLADE_LONG, "pistol3", 70);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
               	ChangeCharacterAddressGroup(sld, "Shore_ship2", "goto", sTemp);
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "MorrisWillams_AfterFightInShore");
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition = "MorrisWillams_SeekCirassaAgain";
			chrDisableReloadToLocation = true;
        break;

        case "MorrisWillams_AfterFightInShore":
            Pchar.quest.MorrisWillams_SeekCirassaAgain.over = "yes";
			chrDisableReloadToLocation = false;
        break;

        case "MorrisWillams_SeekCirassaAgain":
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
        break;
        
//==========================   ����� N8, � ������� ��������� �� ������� ========================
        case "ToMansfield_IntoTheTown":
            sld = GetCharacter(NPC_GenerateCharacter("Dick_Manson", "pirate_8", "man", "man", 10, ENGLAND, 5, true));
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
        	sld.name 	= "���";
        	sld.lastname = "������";
        	LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "LaVega_tavern", "goto", "goto2");
            LAi_SetStayTypeNoGroup(sld);
			DoQuestCheckDelay("TalkSelf_Quest", 2.0); //������ ���-��-���
        break;

        case "ToMansfield_OutFromFort":
            Log_QuestInfo("���������� �������� ����� �� �����.");
            characters[GetCharacterIndex("Dick_Manson")].lifeDay = 0;
            if (pchar.questTemp.State == "ToMansfield_CatchToPardal")
            {
                Log_QuestInfo("����������� ���������� �� ��������� ������� ����� ����.");
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1 = "location";
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1.location = "Cuba1";
                Pchar.quest.ToMansfield_FightNearSantiago.win_condition = "ToMansfield_FightNearSantiago";
                SetTimerCondition("ToMansfield_NotFoundGaleon", 0, 0, 12, false);
            }
            else
            {
                AddQuestRecord("Eng_Line_8_ToMansfield", "3");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("��","��"));
                pchar.questTemp.State = "ToMansfield_DidNotFindBecaners";
            }
        break;

        case "ToMansfield_NotFoundGaleon":
            // ==> ������� ��� ����������, ������� ����� ���� �����������
            Pchar.quest.ToMansfield_FightNearSantiago.over = "yes";
            pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
            AddQuestRecord("Eng_Line_8_ToMansfield", "4");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","�"));		
            Log_QuestInfo("�� ����� ������� �� ����. ������ ���� � ����� ��������.");
        break;

        case "ToMansfield_FightNearSantiago":
            Log_QuestInfo("������ ��������� � ����� ����� ��������. ������ ���� ������ ����� � �����.");
            Pchar.quest.ToMansfield_NotFoundGaleon.over = "yes"; // ������� ������ �� ��������� �������

            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_2", "man", "man", 31, SPAIN, 0, true));
            sld.SinkTenPercent = true; // ������ � �������������
            sld.DontRansackCaptain = true; //��������� �� �������

            FantomMakeCoolSailor(sld, SHIP_GALEON1, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
            FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 120);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
            Group_SetAddress("Spa_Attack", "Cuba1", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_LockTask("Spa_Attack");
            //==> ������� ���������� ������ � ������
            pchar.questTemp.ELQ8_PutLetter = 1;

			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition = "ToMansfield_GaleonBoarding";

			pchar.quest.ToMansfield_GaleonSink.win_condition.l1 = "Character_sink";
			pchar.quest.ToMansfield_GaleonSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonSink.win_condition = "ToMansfield_GaleonSink";
			pchar.quest.ToMansfield_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.ToMansfield_DieHard.win_condition = "ToMansfield_DieHard";
        break;

        case "ToMansfield_GaleonBoarding":
            if (CheckCharacterItem(pchar, "letter_2"))
            {
                Log_QuestInfo("������ ������� � �������� � ��������.");
                AddQuestRecord("Eng_Line_8_ToMansfield", "5");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("��","��"));
                pchar.questTemp.State = "ToMansfield_Boarding";
                TakeItemFromCharacter(pchar, "letter_2");
                ChangeItemDescribe("letter_open", "itmdescr_letter_open_EngLineQ8");
                GiveItem2Character(pchar, "letter_open");
            }
            else
            {
                Log_QuestInfo("������ �� �������.");
                AddQuestRecord("Eng_Line_8_ToMansfield", "6");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","�"));
                pchar.questTemp.State = "ToMansfield_BoardingNotFoundLetter";
            }
            pchar.quest.ToMansfield_GaleonSink.over = "yes";
            Pchar.quest.ToMansfield_DieHard.over = "yes"; // ������� ������ �� ������ �������
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;

        case "ToMansfield_GaleonSink":
            Log_QuestInfo("������ ��������.");
            pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
            Pchar.quest.ToMansfield_DieHard.over = "yes"; // ������� ������ �� ������ �������
            pchar.questTemp.State = "ToMansfield_GaleonSink";
            AddQuestRecord("Eng_Line_8_ToMansfield", "7");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("","�"));	
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;

        case "ToMansfield_DieHard":
            Log_QuestInfo("������ ����.");
            pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
            pchar.quest.ToMansfield_GaleonSink.over = "yes";
            pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
            AddQuestRecord("Eng_Line_8_ToMansfield", "4");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
            BackItemDescribe("letter_2");
        break;
        
//==========================   ����� N9, ��������� �� ������� ========================
        case "AttackSantiago_FightWithPardal":
            Log_QuestInfo("������� ������� �����������, ����� ��������.");
            Island_SetReloadEnableGlobal("Cuba1", false);
            PChar.questTemp.ELQ9_Diffrent = 1;
            Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ������� ������� �������
            for (i=1; i<=4; i++)
            {
                attrName = "off_spa_1";
                Rank = 27;
                ShipType = SHIP_GALEON_H;
                if (i==1)
                {
                    attrName = "SpaOfficer1";
                    Rank = 40;
                    ShipType = SHIP_BATTLESHIP;
                }
                if (i==2)
                {
                    attrName = "off_spa_2";
                    Rank = 30;
                    ShipType = SHIP_FRIGATE_SAT;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, attrName, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
                FantomMakeCoolFighter(sld, Rank, 95, 70, BLADE_LONG, "pistol3", 120);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
                if (i==1)
                {
                    sld.Ship.Name = "������";
                    sld.name 	= "������� ������";
                	sld.lastname = "�������";
                }
            }
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
            Group_SetAddress("Spa_Attack", "Cuba1", "", "");
            Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_LockTask("Spa_Attack");

            pchar.quest.AttackSantiago_AfterFight.win_condition.l1 = "Group_Death";
			pchar.quest.AttackSantiago_AfterFight.win_condition.l1.group = "Spa_Attack";
			pchar.quest.AttackSantiago_AfterFight.win_condition = "AttackSantiago_AfterFight";
			pchar.quest.AttackSantiago_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.AttackSantiago_DieHard.win_condition = "AttackSantiago_DieHard";
			// ==> ������ ������ �� ����� �� 6��� ���� ����, � �� ���� ���������� �������
            // === �� ����� ����� �� ������ � ��� ������ ����� ���.
            if (pchar.location.from_sea == "Santiago_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "AttackSantiago_AfterFight":
			Log_QuestInfo("������� ������� �������.");
            pchar.questTemp.State = "AttackSantiago_GoodWork";
            AddQuestRecord("Eng_Line_9_AttackSantiago", "3");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
            ChangeCharacterReputation(pchar, 3);
            pchar.quest.AttackSantiago_DieHard.over = "yes"; //fix
            Island_SetReloadEnableGlobal("Cuba1", true);
        break;

        case "AttackSantiago_DieHard":
			pchar.quest.AttackSantiago_AfterFight.over = "yes";
			pchar.questTemp.State = "AttackSantiago_GoodWork";
            Log_QuestInfo("������� ������� �����.");
            AddQuestRecord("Eng_Line_9_AttackSantiago", "4");
            group_DeleteGroup("Spa_Attack");
            DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
            AddCharacterExpToSkill(pchar, "Leadership", -1650);
			AddCharacterExpToSkill(pchar, "Defence", -1300);
			AddCharacterExpToSkill(pchar, "Cannons", -1600);
			AddCharacterExpToSkill(pchar, "Sailing", -1400);
			AddCharacterExpToSkill(pchar, "Sneak", -1350);
			AddCharacterExpToSkill(pchar, "Grappling", 1200);
			AddCharacterExpToSkill(pchar, "Repair", -950);
			AddCharacterExpToSkill(pchar, "Pistol", -1200);
			AddCharacterExpToSkill(pchar, "Accuracy", -1510);
			AddCharacterExpToSkill(pchar, "Fencing", -1900);
			ChangeCharacterReputation(pchar, -5);
			Island_SetReloadEnableGlobal("Cuba1", true);
        break;
        
//==========================   ����� N10, ������ ����� �������� �� ����-����� ========================
        case "SpanishAttack_Battle":
            Log_QuestInfo("��������� ������� �����������, ����� ������ ��������.");
            Island_SetReloadEnableGlobal("Jamaica", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 40;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_LINK2;
                        Model = "off_spa_1";
                        Rank = 33;
                        Blade = "blade24";
                    break;
                    case 4:
                        ShipType = SHIP_FR_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 5:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 27;
                        Blade = "blade26";
                    break;
                    case 6:
                        ShipType = SHIP_BATTLESHIP;
                        Model = "off_spa_2";
                        Rank = 33;
                        Blade = "blade28";
                    break;
                    case 7:
                        ShipType = SHIP_ZEVENPROVINCIEN;
                        Model = "off_spa_1";
                        Rank = 39;
                        Blade = "blade32";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Jamaica", "quest_ships", "quest_ship_3");
			Group_LockTask("Spa_Attack");
			// �������� ������������
			//Group_SetTaskAttack("JamaykaSquadron", "Spa_Attack"); // ����������� ����� ��������, ����� �����
			//Group_LockTask("JamaykaSquadron");
            // ==> ���������� �� ������� �������
            pchar.quest.SpanishAttack_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpanishAttack_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpanishAttack_AfterBattle.win_condition = "SpanishAttack_AfterBattle";
			pchar.quest.SpanishAttack_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpanishAttack_DieHard.win_condition = "SpanishAttack_DieHard";

            if (pchar.location.from_sea == "PortRoyal_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "SpanishAttack_AfterBattle":
            /*if (!Group_isDead("JamaykaSquadron"))
			{
            	Group_SetTaskNone("JamaykaSquadron");
            }*/
			Log_QuestInfo("��������� ������� �������.");
            pchar.questTemp.State = "SpanishAttack_GoodWork";
            AddQuestRecord("Eng_Line_10_SpanishAttack", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            pchar.quest.SpanishAttack_DieHard.over = "yes";
        break;
        
        case "SpanishAttack_DieHard":
            /*if (!Group_isDead("JamaykaSquadron"))
            {
            	Group_SetTaskNone("JamaykaSquadron");
            } */
            Log_QuestInfo("������ � ���� ���, ������� �����.");
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Eng_Line_10_SpanishAttack", "3");
			CloseQuestHeader("Eng_Line_10_SpanishAttack");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            pchar.quest.SpanishAttack_AfterBattle.over = "yes";
            SetCaptureTownByNation("PortRoyal", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
            SetGovenourToCity(ENGLAND, "PortSpein");
        break;

//==========================   ����� N12, ������� ���������� ����� � ����� ��������� ========================
        case "ColonelLinch_IntoTheResidence":
            sld = GetCharacter(NPC_GenerateCharacter("Thomas_Linch", "ThomasLinch", "man", "man", 30, ENGLAND, 10, true));
            sld.name 	= "��������� �����";
        	sld.lastname = "����";
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_military";
            ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Thomas_Linch", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

        case "ColonelLinch_AfterFight":
            pchar.nation = ENGLAND;
            Ship_FlagRefresh(PChar); //���� �� ����
            bDisableFastReload = false; // ������� ��������.
            chrDisableReloadToLocation = false; // ������� ����� �� �������.
            pchar.questTemp.State = "ColonelLinch_ModifordArrested";
            //LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
            sld = GetCharacter(NPC_GenerateCharacter("Thomas_Modiford", "Modyford", "man", "man", 10, ENGLAND, 40, false));
            sld.name 	= "�����";
        	sld.lastname = "��������";
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
            sld.dialog.currentnode = "You_baster";
			LAi_SetImmortal(sld, true);
        	FaceMaker(sld);
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            DoReloadCharacterToLocation("PortRoyal_prison",  "goto", "goto23");
            ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
			LAi_SetActorType(sld);
            LAi_ActorDialog(sld, Pchar, "", 1.5, 0);
			pchar.quest.ColonelLinch_Exit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.ColonelLinch_Exit.win_condition.l1.location = pchar.location;
			pchar.quest.ColonelLinch_Exit.win_condition = "ColonelLinch_Exit";
        break;

        case "ColonelLinch_Exit":
            sld = characterFromID("eng_guber");   //  ����.����� ����� ������� ������.
            sld.model = "ThomasLinch";
            sld.name 	= "��������� �����";
        	sld.lastname = "����";
        	sld.model.animation = "man"
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
			SetGovenourToCity(ENGLAND, "PortRoyal");
            AddQuestRecord("Eng_Line_12_ColonelLinch", "3");
            LAi_SetHuberStayType(sld);
            LAi_SetImmortal(sld, false);
            LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), false);
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END ���������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START ����������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==========================   ����� N1, �������� ������ ������� ��������� ========================
        case "SeekChumakeiro_intoMarigoHouse":
            Log_QuestInfo("�������� ������ �� ����.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
			LAi_group_Delete("EnemyFight");            
            for (i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 20, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 18, 70, 60, BLADE_LONG, "pistol2", 10);
            	LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, false);
            	sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Marigo_houseF1", "goto",  "goto"+i);
            }
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "SeekChumakeiro_intoResidence":
            sld = characterFromID("Chumakeiro");                    //  ��������� � ���������� �����������
            ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto2");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar("Chumakeiro", "", 0.0, 1.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;

//==========================   ����� N4, ������ ����� �����   ========================
        case "DefenceOrange_FightNearJamaica":
            if (GetQuestPastDayParam("questTemp") < 12)
            {
                Log_QuestInfo("����������� ���������� �������.");
                Island_SetReloadEnableGlobal("Jamaica", false);
                //bQuestDisableMapEnter = true;
        		Group_FindOrCreateGroup("Eng_Attack");
    			Group_SetType("Eng_Attack", "war");
                // ==> ���������� ����
                for (i=1; i<=3; i++)
                {
                    switch (i)
                    {
                        case 1:
                            ShipType = SHIP_SALAMANDER;
                            Model = "off_eng_1";
                            Rank = 23;
                            Blade = "blade33";
                        break;
                        case 2:
                            ShipType = SHIP_BRIGHEAVY;
                            Model = "off_eng_2";
                            Rank = 19;
                            Blade = "blade28";
                        break;
                        case 3:
                            ShipType = SHIP_CORVETTE;
                            Model = "off_eng_1";
                            Rank = 21;
                            Blade = "blade24";
                        break;
                    }
                    sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, ENGLAND, 0, true));
                    FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 80, 70, 95);
                    FantomMakeCoolFighter(sld, Rank, 70, 50, Blade, "pistol3", 75);
        			Group_AddCharacter("Eng_Attack", "CaptainAttack_"+i);
                }
                // ==> ������������
    			Group_SetGroupCommander("Eng_Attack", "CaptainAttack_1");
    			Group_SetTaskAttack("Eng_Attack", PLAYER_GROUP);
    			Group_SetAddress("Eng_Attack", "Jamaica", "quest_ships", "quest_ship_8");
    			Group_LockTask("Eng_Attack");
                // ==> ���������� �� ������� �������
                pchar.quest.DefenceOrange_AfterBattle.win_condition.l1 = "Group_Death";
    			pchar.quest.DefenceOrange_AfterBattle.win_condition.l1.group = "Eng_Attack";
    			pchar.quest.DefenceOrange_AfterBattle.win_condition = "DefenceOrange_AfterBattle";
    			pchar.quest.DefenceOrange_DieHard.win_condition.l1 = "MapEnter";
                pchar.quest.DefenceOrange_DieHard.win_condition = "DefenceOrange_DieHard";
            }
            else
            {
                SetLocationCapturedState("FortOrange_town", true);
                pchar.questTemp.State = "DefenceOrange_LateRiseOrange";
				//--> ����� � �������
				locations[FindLocation("FortOrange_town")].hidden_effects = true;
				locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;	
				//<-- ����� � �������
            Log_QuestInfo("�� ����� ������� �������, ���� ����� �������.");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "3");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","�"));
            }
        break;

        case "DefenceOrange_AfterBattle":
			Log_QuestInfo("���������� ������� �������, ������ ������� �� ��������.");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "2");
            pchar.questTemp.State = "DefenceOrange_SquadronDestroyed";
            group_DeleteGroup("Eng_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            bQuestDisableMapEnter = false;
            Pchar.quest.DefenceOrange_FightInShore.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightInShore.win_condition.l1.location = "Shore35";
            Pchar.quest.DefenceOrange_FightInShore.win_condition = "DefenceOrange_FightInShore";
        break;

        case "DefenceOrange_FightInShore":
            Log_QuestInfo("������� � ���������� �������� �� ������.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=15; i++)
            {
                if (i == 3 || i == 7 || i == 11)
                {
                    Model = "off_eng_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_eng_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 70, 60, Blade, Gun, 70);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Shore35", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
            for (i=1; i<=8; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
                ChangeCharacterAddressGroup(sld, "Shore35", "goto", sTemp);
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1.location = "FortOrange_ExitTown";
            Pchar.quest.DefenceOrange_FightInExitTown.win_condition = "DefenceOrange_FightInExitTown";
        break;

        case "DefenceOrange_FightInExitTown":
            Log_QuestInfo("������� � ���������� �������� � ����� �����.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=18; i++)
            {
                if (i == 3 || i == 7 || i == 11 || i == 17)
                {
                    Model = "off_eng_" + (rand(1)+1);
                    Blade = "blade24";
                    Rank = 25;
                    Gun = "pistol4";
                }
                else
                {
                    Model = "sold_eng_" + (rand(7)+1);
                    Rank = 20;
                    Blade = BLADE_LONG;
                    Gun = "pistol3";
                }
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, Model, "man", "man", 25, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 100, 70, Blade, Gun, 70);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
            }
            for (i=1; i<=15; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("pirate_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 25, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, Rank, 60, 50, Blade, Gun, 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
                ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld",  LAi_FindNearestLocator("rld", locx, locy, locz));
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DefenceOrange_WeWon");
        break;

        case "DefenceOrange_WeWon":
            chrDisableReloadToLocation = false; // ������� ����� �� �������.
			Log_QuestInfo("���������� ������ ���������.");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "4");
            pchar.questTemp.State = "DefenceOrange_LandingDestroyed";
            pchar.quest.DefenceOrange_DieHard.over = "yes";
            //==> ����� ��� ���� ������ ��������� � �����.
            QuestSetCurrentNode("FortOrange_Mayor", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_waitress", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_tavernkeeper", "DefenceOrange");
            QuestSetCurrentNode("FortOrange_trader", "DefenceOrange");
        break;
        
        case "DefenceOrange_DieHard":
            pchar.quest.DefenceOrange_AfterBattle.over = "yes";
            pchar.quest.DefenceOrange_FightInShore.over = "yes";
            AddQuestRecord("Hol_Line_4_DefenceOrange", "5");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex1", GetSexPhrase("","�"));
            SetLocationCapturedState("FortOrange_town", true);
            group_DeleteGroup("Eng_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            bQuestDisableMapEnter = false;
            pchar.questTemp.State = "DefenceOrange_DieHard";
			//--> ����� � �������
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;	
			//<-- ����� � �������
        break;
        
//==========================   ����� N5, ������������� ���� ������� �� �� ���� � �������  ========================
        case "ThreeFleutes_TalkIntoLaVega":
			chrDisableReloadToLocation = true;
            //===> ������ ���� :( ������ �� ����� ����� ������� �����.
            sld = characterFromID("Edward Mansfield");
            sld.name 	= "�������";
        	sld.lastname = "�����";
        	sld.model.animation = "man"
            sld.model = "officer_8";
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
			//===> � �� �������� ����� � �������� � ������ ���������
			sld = GetCharacter(NPC_GenerateCharacter("Talker", "officer_6", "man", "man", 25, PIRATE, 0, true));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	LAi_SetStayTypeNoGroup(sld);
            GetCharacterPos(pchar, &locx, &locy, &locz);
            ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
        break;
        
        case "ThreeFleutes_BackToCuracao":
            Log_QuestInfo("������ ��������, � ���.");
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //������ �� � ��������, � �� ��� � ��������.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY); 
            Island_SetReloadEnableGlobal("Hispaniola1", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=4; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_1";
                        Rank = 28;
                        Blade = "blade24";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 26;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_CARAVEL;
                        Model = "off_spa_1";
                        Rank = 31;
                        Blade = "blade33";
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade33";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
                FantomMakeCoolFighter(sld, Rank, 90, 70, Blade, "pistol3", 75);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola1", "", "");
			Group_LockTask("Spa_Attack");
            // ==> ���������� �� ������� �������
            pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition = "ThreeFleutes_AfterBattle";
			pchar.quest.ThreeFleutes_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.ThreeFleutes_DieHard.win_condition = "ThreeFleutes_DieHard";
        break;

        case "ThreeFleutes_AfterBattle":
            Island_SetReloadEnableGlobal("Hispaniola1", true);
            pchar.quest.ThreeFleutes_DieHard.over = "yes";
			group_DeleteGroup("Spa_Attack");
			//--> ������� � ��� ������� �� �����������
			iTemp = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_FLEUT) iTemp++;
                }
            }
			//--> ��������� � ��
			if (iTemp < 3)
            {
                pchar.questTemp.State = "ThreeFleutes_LostFleuts";
                if (iTemp < 1)
                {
                    AddQuestRecord("Hol_Line_5_ThreeFleutes", "6");
					AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("","�"));
                }
                else
                {
                    AddQuestRecord("Hol_Line_5_ThreeFleutes", "5");
                    AddQuestUserData("Hol_Line_5_ThreeFleutes", "QtyFleutes", iTemp);
                }
            }
            else
            {
                AddQuestRecord("Hol_Line_5_ThreeFleutes", "4");
				AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("","�"));
                pchar.questTemp.State = "ThreeFleutes_AllFleuts";
            }
        break;
        
        case "ThreeFleutes_DieHard":
            pchar.quest.ThreeFleutes_AfterBattle.over = "yes";
            AddQuestRecord("Hol_Line_5_ThreeFleutes", "3");
            pchar.questTemp.State = "ThreeFleutes_DieHard";
            Island_SetReloadEnableGlobal("Hispaniola1", true);
            group_DeleteGroup("Spa_Attack");
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
        break;

//==========================   ����� N7, �������� ������ �� �������  ========================
        case "DelivLettTortuga_SnapMeeting":
			chrDisableReloadToLocation = true;
            Log_QuestInfo("������� � �����������.");
            sld = GetCharacter(NPC_GenerateCharacter("Stranger_HL7", "citiz_2", "man", "man", 15, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	sld.name 	= "�����";
        	sld.lastname = "�����";
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "DelivLettTortuga_2KickPhar":
            LAi_SetCitizenType(characterFromId("AntonioDeBarras"));
            LAi_ActorAnimation(pchar, "death_2", "DelivLettTortuga_3KickPhar", 3.0);
        break;

        case "DelivLettTortuga_3KickPhar":
            LAi_ActorSetLayMode(pchar);
            DoQuestCheckDelay("DelivLettTortuga_KickPhar", 1.0);
            sld = characterFromID("AntonioDeBarras");
            ChangeCharacterAddress(sld, "None", "");
        break;

        case "DelivLettTortuga_KickPhar":
            SetLaunchFrameFormParam("������ ���-�� ����� ����...", "", 0, 3);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 1, 10); //������ ���
        	RecalculateJumpTable();
			pchar.questTemp.State = "DelivLettTortuga_AfterRape";
            //LAi_SetStayType(sld);
            TakeItemFromCharacter(pchar, "letter_1");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "4");
            LAi_SetPlayerType(pchar);
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);
        break;
        
        case "DelivLettTortuga_BrigTimeOver":
            pchar.quest.DelivLettTortuga_AttackBrig.over = "yes";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
            pchar.questTemp.State.KingResult = "BrigNotFound"; //���� �� ������ �� �����
        break;

        case "DelivLettTortuga_AttackBrig":
            Log_QuestInfo("���� ������, �� �������!");
            pchar.quest.DelivLettTortuga_BrigTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //������ �� � �������.
            Island_SetReloadEnableGlobal("PuertoRico", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "officer_15", "man", "man", 30, PIRATE, 0, true));
            sld.Dialog.Filename    = "Quest\HolLineNpc_2.c";
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_BRIGHEAVY, "�� ������", CANNON_TYPE_CULVERINE_LBS24, 90, 80, 80);
            FantomMakeCoolFighter(sld, 30, 100, 40, "blade24", "pistol3", 80);
			Group_AddCharacter("Pirate_Attack", "CaptainAttack_1");
            // ==> ������������
			Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PuertoRico", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> ����������
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition = "DelivLettTortuga_AfterBrigSunk";
			pchar.quest.DelivLettTortuga_BrigDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.DelivLettTortuga_BrigDieHard.win_condition = "DelivLettTortuga_BrigDieHard";
        break;
        
        case "DelivLettTortuga_BrigDieHard":
            pchar.quest.DelivLettTortuga_AfterBrigSunk.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("PuertoRico", true);
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
            pchar.questTemp.State.KingResult = "BrigNotFound"; //���� �� ������ �� �����
        break;

        case "DelivLettTortuga_AfterBrigSunk":
            pchar.quest.DelivLettTortuga_BrigDieHard.over = "yes";
            Island_SetReloadEnableGlobal("PuertoRico", true);
            group_DeleteGroup("Pirate_Attack");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "6");
            pchar.questTemp.State.KingResult = "BrigSunk"; //���� �� ������
        break;
        
        case "DelivLettTortuga_WarshipTimeOver":
            pchar.quest.DelivLettTortuga_AttackWarship.over = "yes";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
        break;

        case "DelivLettTortuga_AttackWarship":
            Log_QuestInfo("������� ������ ������, �� �������!");
            pchar.quest.DelivLettTortuga_WarshipTimeOver.over = "yes";
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //������ �� � ��������.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY); 
            Island_SetReloadEnableGlobal("SantaCatalina", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "AntonioDeBarras");
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "AntonioDeBarras");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SantaCatalina", "", "");
			Group_LockTask("Spa_Attack");
            // ==> ����������
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1.character = "AntonioDeBarras";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition = "DelivLettTortuga_AfterWarshipSunk";
			pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition = "DelivLettTortuga_WarshipDieHard";
        break;

        case "DelivLettTortuga_WarshipDieHard":
            pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
        break;

        case "DelivLettTortuga_AfterWarshipSunk":
            pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            group_DeleteGroup("Spa_Attack");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "10");
            pchar.questTemp.State.KingResult = "WarshipSunk"; //���� �� ������
        break;

//==========================   ����� N8, ������ ������  ========================
        case "SeekBible_SaveDeGraf":
            Log_QuestInfo("����� ������ ������ �� �����!");
            Island_SetReloadEnableGlobal("Cartahena", false);
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //������ �� � ��������. 
            SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=5; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_BELLONA;
                        Model = "SpaOfficer2";
                        Rank = 28;
                        Blade = "blade24";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 26;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_1";
                        Rank = 34;
                        Blade = "blade28";
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 30;
                        Blade = "blade33";
                    break;
                    case 5:
                        ShipType = SHIP_FRIGATEMEDIUM;
                        Model = "off_spa_1";
                        Rank = 36;
                        Blade = "blade28";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 85);
                FantomMakeCoolFighter(sld, Rank, 96, 80, Blade, "pistol3", 85);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Cartahena", "", "");
            // ==> �� ����
            sld = GetCharacter(NPC_GenerateCharacter("LoranDeGraf", "officer_14", "man", "man", 45, HOLLAND, -1, true));
            sld.DeckDialogNode = "First time";
            sld.Dialog.Filename = "Quest\HolLineNpc_2.c";
        	sld.name 	= "�����";
        	sld.lastname = "�� ����";
			sld.greeting = "Gr_MiddPirate";
			sld.ShipEnemyDisable = true; //��� ��������� �� ���������
        	sld.Abordage.Enable = false; // ������!
            LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_BATTLEFRIGATE, "�������", CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
            FantomMakeCoolFighter(sld, 45, 90, 70, "topor2", "pistol3", 100);
            Group_AddCharacter("Quest_Group", "LoranDeGraf");
            Group_SetType("Quest_Group", "war");
            Group_SetGroupCommander("Quest_Group", "LoranDeGraf");
            Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
            Group_SetAddress("Quest_Group", "Cartahena", "", "");
			// ==> ������������
			Group_SetTaskAttack("Spa_Attack", "Quest_Group");
            Group_SetTaskAttack("Quest_Group", "Spa_Attack");
            Group_LockTask("Quest_Group");
			Group_LockTask("Spa_Attack");
            pchar.quest.SeekBible_WeWon.win_condition.l1 = "Group_Death";
			pchar.quest.SeekBible_WeWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SeekBible_WeWon.win_condition = "SeekBible_WeWon";
    		pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1 = "NPC_Death";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1.character = "LoranDeGraf";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition = "SeekBible_NotSavedDeGraf";
			pchar.quest.SeekBible_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SeekBible_DieHard.win_condition = "SeekBible_DieHard";
        break;
        
        case "SeekBible_WeWon":
            pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
            pchar.quest.SeekBible_DieHard.over = "yes";
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Cartahena", true);
            AddQuestRecord("Hol_Line_8_SeekBible", "8");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","�"));
            pchar.questTemp.State = "SeekBible_WeWon";  
        break;

        case "SeekBible_DieHard":
            if (pchar.questTemp.State == "SeekBible_DeGrafIsDead")
            {
                group_DeleteGroup("Spa_Attack");
            }
            else
            {
                pchar.quest.SeekBible_WeWon.over = "yes";
                pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
                group_DeleteGroup("Spa_Attack");
                group_DeleteGroup("Quest_Group");
                Island_SetReloadEnableGlobal("Cartahena", true);
                AddQuestRecord("Hol_Line_8_SeekBible", "6");
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("��","���"));
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","��"));
                pchar.questTemp.State = "SeekBible_DeGrafDieHard";
            }
        break;
        
        case "SeekBible_NotSavedDeGraf":
            pchar.quest.SeekBible_WeWon.over = "yes";
            Island_SetReloadEnableGlobal("Cartahena", true);
            AddQuestRecord("Hol_Line_8_SeekBible", "7");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("","�"));
            pchar.questTemp.State = "SeekBible_DeGrafIsDead";
        break;
        
        case "SeekBible_DeGrafToTavern":
            sld = characterFromId("LoranDeGraf");
            FreeSitLocator("Tortuga_tavern", "sit3");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");			
            LAi_SetSitTypeNoGroup(sld);
            group_DeleteGroup("Quest_Group");
        break;
        
//==========================   ����� N10, ������� �������.  ========================
        case "SpaAttackCuracao_Battle":
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //������ �� � ��������.
            SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
            Log_QuestInfo("��������� ������� �����������, ����� ������ ��������.");
            Island_SetReloadEnableGlobal("Curacao", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 45;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 35;
                        Blade = "blade28";
                    break;
                    case 3:
                        ShipType = SHIP_BATTLESHIP;
                        Model = "off_spa_1";
                        Rank = 33;
                        Blade = "blade24";
                    break;
                    case 4:
                        ShipType = SHIP_FR_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 5:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                    case 6:
                        ShipType = SHIP_ZEVENPROVINCIEN;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                    case 7:
                        ShipType = SHIP_POSEIDON;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "topor2";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "", "");
			Group_LockTask("Spa_Attack");
			// �������� ������������
			//Group_SetTaskAttack("CuracaoSquadron", "Spa_Attack"); // ����������� ����� ��������, ����� �����
			//Group_LockTask("CuracaoSquadron");
            // ==> ���������� �� ������� �������
            pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition = "SpaAttackCuracao_AfterBattle";
			pchar.quest.SpaAttackCuracao_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpaAttackCuracao_DieHard.win_condition = "SpaAttackCuracao_DieHard";

            if (pchar.location.from_sea == "Villemstad_town")
            {
                bQuestDisableMapEnter = true;
                DoQuestCheckDelay("CanEnterToMap", 400);
            }
        break;

        case "SpaAttackCuracao_AfterBattle":
            /*if (!Group_isDead("CuracaoSquadron"))
			{
            	Group_SetTaskNone("CuracaoSquadron");
            }*/
			Log_QuestInfo("��������� ������� �������.");
            pchar.questTemp.State = "SpaAttackCuracao_GoodWork";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.SpaAttackCuracao_DieHard.over = "yes";
        break;

        case "SpaAttackCuracao_DieHard":
            /*if (!Group_isDead("CuracaoSquadron"))
            {
            	Group_SetTaskNone("CuracaoSquadron");
            } */
            Log_QuestInfo("������ � ���� ���, ������� �����.");
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "3");
			CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Curacao", true);
            pchar.quest.SpaAttackCuracao_AfterBattle.over = "yes";
            SetCaptureTownByNation("Villemstad", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
            SetGovenourToCity(HOLLAND, "Marigo");
        break;

//==========================   ����� N11, ������ ������ �� ��������� ��������.  ========================
        case "SpaAttackSentMartin_YouLate":
            Log_QuestInfo("�������. ������ �������� ���������.");
            pchar.questTemp.State = "SpaAttackSentMartin_Late";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "4");
			AddQuestUserData("Hol_Line_11_SpaAttackSentMartin", "sSex", GetSexPhrase("","�"));
            pchar.quest.SpaAttackSentMartin_Battle.over = "yes";
            SetCaptureTownByNation("Marigo", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;

        case "SpaAttackSentMartin_Battle":
            Log_QuestInfo("��������� ������� �����������, ����� ������ ��������.");
            pchar.quest.SpaAttackSentMartin_YouLate.over = "yes";
            Island_SetReloadEnableGlobal("SentMartin", false);
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_SP_SANFELIPE;
                        Model = "off_spa_1";
                        Rank = 42;
                        Blade = "blade33";
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_1";
                        Rank = 42;
                        Blade = "blade33";
                    break;
                    case 3:
                        ShipType = SHIP_WARSHIP;
                        Model = "off_spa_2";
                        Rank = 32;
                        Blade = "blade28";
                    break;
                    case 4:
                        ShipType = SHIP_BELLONA;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade24";
                    break;
                    case 5:
                        ShipType = SHIP_FR_TRINITY;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade34";
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Model = "off_spa_2";
                        Rank = 29;
                        Blade = "blade26";
                    break;
                    case 7:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_2";
                        Rank = 33;
                        Blade = "blade28";
                    break;
                    case 8:
                        ShipType = SHIP_ZEVENPROVINCIEN;
                        Model = "off_spa_1";
                        Rank = 39;
                        Blade = "blade32";
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SentMartin", "quest_ships", "quest_ship_4");
			Group_LockTask("Spa_Attack");
			// �������� ������������
			//Group_SetTaskAttack("SentMartinSquadron", "Spa_Attack"); // ����������� ����� ��������, ����� �����
			//Group_LockTask("SentMartinSquadron");
            // ==> ���������� �� ������� �������
            pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition = "SpaAttackSentMartin_AfterBattle";
			pchar.quest.SpaAttackSentMartin_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.SpaAttackSentMartin_DieHard.win_condition = "SpaAttackSentMartin_DieHard";
        break;

        case "SpaAttackSentMartin_AfterBattle":
            /*if (!Group_isDead("SentMartinSquadron"))
			{
            	Group_SetTaskNone("SentMartinSquadron");
            }*/
			Log_QuestInfo("��������� ������� �������.");
            pchar.questTemp.State = "SpaAttackSentMartin_GoodWork";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "2");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SentMartin", true);
            pchar.quest.SpaAttackSentMartin_DieHard.over = "yes";
        break;

        case "SpaAttackSentMartin_DieHard":
            /*if (!Group_isDead("SentMartinSquadron"))
            {
            	Group_SetTaskNone("SentMartinSquadron");
            } */
            Log_QuestInfo("������ � ���� ���, ������� �����.");
            pchar.questTemp.State = "QuestLineBreake";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "3");
			CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("SentMartin", true);
            pchar.quest.SpaAttackSentMartin_AfterBattle.over = "yes";
            SetCaptureTownByNation("Marigo", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END ����������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START ��������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//========================  ����� N2, ������� ����������.  =======================
        case "Inquisition_MeetFrancisco":
			chrDisableReloadToLocation = true;
            Log_QuestInfo("������� � ���������.");
            sld = GetCharacter(NPC_GenerateCharacter("Francisco", "priest_4", "man", "man", 15, SPAIN, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
        	sld.name 	= "���������";
        	sld.lastname = "�� ���-���������";
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Inquisition_afterFightAndrew":
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], true);
            sld = characterFromId("Villemstad_usurer");
            LAi_IsDead(sld) LAi_SetHP(sld, 100, 100);
        	sld.location	= "Villemstad_Bank";
        	sld.location.group = "barmen";
        	sld.location.locator = "stay";
        	LAi_SetBarmanType(sld);
        	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
        break;
        
        case "Inquisition_LuggerTimeOver":
            pchar.quest.Inquisition_AttackLugger.over = "yes";
            AddQuestRecord("Spa_Line_2_Inquisition", "7");
        break;

        case "Inquisition_AttackLugger":
            Log_QuestInfo("������ ������, �� �������!");
            pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //������ �� � �������.
            Island_SetReloadEnableGlobal("Jamaica", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("JansenDeFonceicao", "shipowner_5", "man", "man", 25, PIRATE, -1, true));
            sld.Dialog.Filename    = "Quest\SpaLineNpc_2.c";
        	sld.name 	= "����� �����";
        	sld.lastname 	= "�� ��������";
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_LUGGER, "���������", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
            FantomMakeCoolFighter(sld, 25, 60, 40, "blade24", "pistol3", 70);
            Group_AddCharacter("Pirate_Attack", "JansenDeFonceicao");
            // ==> ������������
			Group_SetGroupCommander("Pirate_Attack", "JansenDeFonceicao");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Jamaica", "quest_ships", "quest_ship_7");
			Group_LockTask("Pirate_Attack");
            // ==> ����������
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1 = "NPC_Death";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1.character = "JansenDeFonceicao";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition = "Inquisition_AfterLuggerSink";
			pchar.quest.Inquisition_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Inquisition_DieHard.win_condition = "Inquisition_DieHard";
        break;
        
        case "Inquisition_DieHard":
            pchar.quest.Inquisition_LuggerSink.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("Jamaica", true);
            AddQuestRecord("Spa_Line_2_Inquisition", "7");
        break;

        case "Inquisition_AfterLuggerSink":
			if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.quest.Inquisition_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Jamaica", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_2_Inquisition", "9");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "JansenDeFonceicao";
			}
        break;
        
        case "Inquisition_fightForJacow":
            Log_QuestInfo("���� �����.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            sld = GetCharacter(NPC_GenerateCharacter("Bandit", "pirate_10", "man", "man", 25, PIRATE, 0, true));
            FantomMakeCoolFighter(sld, 25, 70, 60, "blade21", "pistol2", 30);
        	LAi_SetStayType(sld);
        	sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
            LAi_group_MoveCharacter(sld, "EnemyFight");
           	ChangeCharacterAddressGroup(sld, "Panama_houseSp1", "goto",  "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
            Pchar.quest.Inquisition_fightForJacow2.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightForJacow2.win_condition.l1.location = "Panama_houseSp1_Room";
            Pchar.quest.Inquisition_fightForJacow2.win_condition = "Inquisition_fightForJacow2";
       break;

       case "Inquisition_fightForJacow2":
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            sld = GetCharacter(NPC_GenerateCharacter("JacowDeFonseka", "trader_7", "man", "man", 10, HOLLAND, -1, false));
            ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto",  "goto4");
           	sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			sld.name 	= "���� �����";
			sld.lastname 	= "�� �������";            
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "pirate_"+i, "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol3", 30);
            	LAi_SetStayType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightJacow");
       break;

       case "Inquisition_afterFightJacow":
            chrDisableReloadToLocation = false;
            LAi_SetActorType(pchar);
            sld = characterFromID("JacowDeFonseka");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
       break;

       case "Inquisition_fightInDangeon":
            Log_QuestInfo("�� ��������� ���� ���������.");
            chrDisableReloadToLocation = true;
            for (i=1; i<=40; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Skelet"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 1, PIRATE, 0, true));
				sld.rank = 1;
				sld.skill.Fencing = 1;                
				sld.skill.Pistol = 1;
				LAi_SetHP(sld, 1, 1);
				DeleteAttribute(sld, "Items");
				GiveItem2Character(sld, "blade1");
				EquipCharacterbyItem(sld, "blade1");
				GiveItem2Character(sld, "pistol1");
				EquipCharacterbyItem(sld, "pistol1");
				TakeNItems(sld,"bullet", 1);
				AddItems(sld, "GunPowder", 1);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters",  "monster"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightSkel");
       break;

       case "Inquisition_afterFightSkel":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
            chrDisableReloadToLocation = false;
       break;
//========================  ����� N3, ������ ���� ���������.  =======================
       case "TakeRockBras_toRock":
            Log_QuestInfo("������ ���� ������, �� �������!");
			pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
            pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
            //SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //������ �� � �������.
            Island_SetReloadEnableGlobal("Maracaibo", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "war");
            sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "officer_15", "man", "man", 30, PIRATE, -1, true));
            sld.Dialog.Filename    = "Quest\SpaLineNpc_1.c";
        	sld.name 	= "���";
        	sld.lastname 	= "��������";
			sld.DontRansackCaptain = true;
            FantomMakeCoolSailor(sld, SHIP_CRIMSONBLOOD, "�������������", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
            FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol3", 80);
            Group_AddCharacter("Pirate_Attack", "RockBrasilian");
            // ==> ������������
			Group_SetGroupCommander("Pirate_Attack", "RockBrasilian");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Maracaibo", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> ����������
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1 = "NPC_Death";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1.character = "RockBrasilian";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition = "TakeRockBras_AfterCorvetteSink";
			pchar.quest.TakeRockBras_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.TakeRockBras_DieHard.win_condition = "TakeRockBras_DieHard";
       break;
        
        case "TakeRockBras_DieHard":
            pchar.questTemp.State = "TakeRockBras_DieHardRock";
            pchar.quest.TakeRockBras_AfterCorvetteSink.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            AddQuestRecord("Spa_Line_3_RockBrasilian", "3");
        break;

        case "TakeRockBras_AfterCorvetteSink":
            if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.questTemp.State = "TakeRockBras_RockSink";
				pchar.quest.TakeRockBras_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Maracaibo", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_3_RockBrasilian", "4");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "RockBrasilian";
			}
        break;
//========================  ����� N4, ������������� �������� ����������.  =======================
        case "Sp4Detection_Race_1":
			LAi_LocationDisableMonstersGen("Tortuga_Cave", true); //�������� �� ��������
			LAi_LocationDisableOfficersGen("Shore58", true); //�������� �� �������
            sld = GetCharacter(NPC_GenerateCharacter("AnryDEstre", "BigPirate", "man", "man", 40, FRANCE, 10, false));
        	sld.name 	= "�����";
        	sld.lastname = "�'�����";
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            sld.money = 21340;
            FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol4", 100);
            TakeNItems(sld,"jewelry7", 1);
            ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto7");
            LAi_SetHP(sld, 1, 1);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            LAi_SetActorTypeNoGroup(sld);            
            LAi_ActorRunToLocation(sld, "reload", "basement1", "Tortuga_Cave", "goto", "goto1", "", -1);
			pchar.quest.Sp4Detection_Race_2.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_2.win_condition.l1.location = "Tortuga_Cave";
			pchar.quest.Sp4Detection_Race_2.win_condition = "Sp4Detection_Race_2";
        break;

        case "Sp4Detection_Race_2":
            sld = characterFromId("AnryDEstre");
            LAi_ActorRunToLocation(sld, "reload", "reload2", "Shore58", "goto", "goto15", "", -1);
			pchar.quest.Sp4Detection_Race_3.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_3.win_condition.l1.location = "Shore58";
			pchar.quest.Sp4Detection_Race_3.win_condition = "Sp4Detection_Race_3";
        break;
        
        case "Sp4Detection_Race_3":
            sld = characterFromId("AnryDEstre");
        	sld.DontClearDead      = true;
        	sld.SaveItemsForDead   =   true;
            LAi_SetActorType(pchar);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
        break;

        case "Sp4Detection_YouWin":
			LAi_LocationDisableOfficersGen("Shore58", false); //�������� �������
			LAi_LocationDisableMonstersGen("Tortuga_Cave", false); //�������� ��������
            pchar.questTemp.State = "Sp4Detection_DEstreIsDead";
            AddQuestRecord("Spa_Line_4_MirderDetection", "6");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","�"));
        break;

//==========================   ����� N5, ��������� �� ���� ========================
		case "Sp5LaVegaAttack_AttackGoOn":
    	    Pchar.GenQuestFort.fortCharacterIdx = GetCharacterIndex("Edward Mansfield");
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState(sld.city + "_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);
            Log_SetStringToLog("�� �����, ����!");
            //==> ������� �����������, �� ����������.
            ChangeCharacterAddress(characterFromID("Edward Mansfield"), "None", "");
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1 = "location";
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1.location = "LaVega_townhall";
            Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition = "Sp5LaVegaAttack_FightWithMayor";
        break;

        case "Sp5LaVegaAttack_FightWithMayor":
            chrDisableReloadToLocation = true; // ������� ����� �� �������
            bDisableFastReload = true; // ������� ��������.
			//--> ����� � �������
			locations[FindLocation("LaVega_town")].hidden_effects = true;
			locations[FindLocation("LaVega_ExitTown")].hidden_effects = true;	
			//<-- ����� � �������
            sld = GetCharacter(NPC_GenerateCharacter("LaVega_Comendant", "Mansfield", "man", "man", 35, PIRATE, -1, true));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
        	sld.name 	= "������";
        	sld.lastname = "��������";
	        sld.City = "LaVega";
			LAi_LoginInCaptureTown(sld, true);
            sld.DontClearDead = true; // �� ������� ���� ����� 200�
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
            sld.cirassId           = Items_FindItemIdx("cirass5");
            FantomMakeCoolFighter(sld, 45, 90, 70, "blade17", "pistol3", 50);
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "goto", "goto1");
			Statistic_AddValue(Pchar, "pir_GrabbingTown", 1); // ����������
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.8);
        break;

        case "Sp5LaVegaAttack_AfterFight":
            AfterTownBattle();
            chrDisableReloadToLocation = false; 
            bDisableFastReload = false;
            pchar.questTemp.State = "Sp5LaVegaAttack_WeWon";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "3");
        break;
//=================== ����� N6, �������� ������������ ��������� �� ������� ===================
        case "Sp6TakeMess_waitingBoy":
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1.location = "Tortuga_tavern";
            Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition = "Sp6TakeMess_TalkWithBoy";
        break;

        case "Sp6TakeMess_TalkWithBoy":
            //==> �����
            sld = GetCharacter(NPC_GenerateCharacter("Boozer", "citiz_3", "man", "man", 10, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            LAi_SetSitType(sld);
			FreeSitLocator("Tortuga_tavern", "sit2");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit2");
            //==> ���������
			chrDisableReloadToLocation = true;
            sld = GetCharacter(NPC_GenerateCharacter("PortMansBoy", "shipowner_10", "man", "man", 10, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
         	ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "goto", "goto2");
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

		case "Sp6TakeMess_Interception":
			if (GetQuestPastTimeParam("questTemp") < 3)
			{
				Log_QuestInfo("������ �� ��������!");
				//==> ��������.
				sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_2", "man", "man", 30, FRANCE, 30, false));
				sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
				FantomMakeCoolFighter(sld, 30, 70, 50, "blade34", "pistol5", 60);
         		ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "reload3");
				ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7"); //���� �� �� ������, ��� ���� �� ���������
				GiveItem2Character(sld,"letter_1");
				sld.money = 18430;
				sld.DontClearDead = true; // �� ������� ���� ����� 200�
				sld.SaveItemsForDead = true; // ��������� �� ����� ����
				LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Sp6TakeMess_AttackMessanger");
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
				LAi_Actor2WaitDialog(sld, pchar);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
				//==> ������� ���������� � �����
				for (i=1; i<=10; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AddSolder"+i, "Sold_fra_"+(rand(7)+1), "man", "man", 25, FRANCE, 0, true));
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.city = "Tortuga";
					sld.citytype = "soldier";
					FantomMakeCoolFighter(sld, sti(pchar.rank)+6, 70, 50, BLADE_LONG, "pistol3", 60);
            		LAi_SetPatrolType(sld);
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto",  "goto"+(rand(20)+1));         
					LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				}
				LAi_group_SetLookRadius("FRANCE_CITIZENS", 50);
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1 = "location";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1.location = "Tortuga";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition = "Sp6TakeMess_FightInPort";
			}
        break;

        case "Sp6TakeMess_AttackMessanger":
			iTemp = GetCharacterIndex("Messanger");
			if (iTemp != -1)
			{			
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");			
				LAi_group_Attack(sld, Pchar);			
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			}
        break;

        case "Sp6TakeMess_MessengerOut":
			ChangeCharacterAddress(characterFromID("Messanger"), "None", "");
        break;
		
		case "Sp6TakeMess_FightInPort":
			if (GetCharacterIndex("Messanger") == -1)
			{
				bDisableFastReload = false; //��������� ���� ������
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
				Island_SetReloadEnableGlobal("Tortuga", false);
    			Group_FindOrCreateGroup("Fra_Attack");
				Group_SetType("Fra_Attack", "war");
				// ==> ����������� ����
				for (i=1; i<=8; i++)
				{
					iTemp = FRANCE;
					switch (i)
					{
						case 1:
							ShipType = SHIP_SURPRISE;
							Model = "off_fra_1";
							Rank = 42;
							Blade = "blade33";
						break;
						case 2:
							ShipType = SHIP_BRIG;
							Model = "off_fra_1";
							Rank = 42;
							Blade = "blade33";
						break;
						case 3:
							ShipType = SHIP_SURPRISE;
							Model = "off_fra_2";
							Rank = 32;
							Blade = "blade28";
						break;
						case 4:
							ShipType = SHIP_SURPRISE;
							Model = "off_fra_1";
							Rank = 35;
							Blade = "blade24";
						break;
						case 5:
							ShipType = SHIP_BATTLECORVETTE;
							Model = "off_fra_1";
							Rank = 35;
							Blade = "blade34";
						break;
						case 6:
							ShipType = SHIP_BRIGHEAVY;
							Model = "off_hol_2";
							Rank = 29;
							Blade = "blade26";
							//iTemp = HOLLAND;
						break;
						case 7:
							ShipType = SHIP_DUTCHPINNACE;
							Model = "off_fra_2";
							Rank = 33;
							Blade = "blade28";
						break;
						case 8:
							ShipType = SHIP_CORVETTE;
							Model = "off_fra_1";
							Rank = 39;
							Blade = "blade32";
						break;
					}
					sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, Model, "man", "man", Rank, iTemp, -1, true));
					FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS24, 80, 70, 90);
					FantomMakeCoolFighter(sld, Rank, 80, 60, Blade, "pistol3", 75);
    				Group_AddCharacter("Fra_Attack", "CaptainAttack_"+i);
				}
				// ==> ������������
				Group_SetGroupCommander("Fra_Attack", "CaptainAttack_1");
				Group_SetTaskAttack("Fra_Attack", PLAYER_GROUP);
				Group_SetPursuitGroup("Fra_Attack", PLAYER_GROUP);
				Group_SetAddress("Fra_Attack", "Tortuga", "", "");
				Group_LockTask("Fra_Attack");
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition.l1 = "MapEnter";
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition = "Sp6TakeMess_OpenTortuga";
			}
			else characters[GetCharacterIndex("Messanger")].lifeDay = 0;
        break;

		case "Sp6TakeMess_OpenTortuga":
			Island_SetReloadEnableGlobal("Tortuga", true);		
        break;
  
		case "Sp6TakeMess_WaitMessanger":
            chrDisableReloadToLocation = true; // ������� ����� �� �������
            bDisableFastReload = true; // ������� ��������.
			DoQuestCheckDelay("Sp6TakeMess_2WaitMessanger", 10.0);			
        break;

		case "Sp6TakeMess_2WaitMessanger":
            sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_2", "man", "man", 40, FRANCE, 0, false));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            FantomMakeCoolFighter(sld, 40, 95, 80, "blade34", "pistol5", 100);
         	ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "reload", "reload1_back");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7"); //���� �� �� ������, ��� ���� �� ���������
            GiveItem2Character(sld,"letter_1");
            sld.money = 18430;
            sld.DontClearDead = true; // �� ������� ���� ����� 200�
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
	        LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;
//=================== ����� N7, ������ ������� ===================
        case "Sp7SavePardal_FightNearAntigua":
            Log_QuestInfo("������� �������, �� �� ������ ���� ��������.");
			PChar.questTemp.SLQ7_Diffrent = 1; //������ �������� � �����
            Island_SetReloadEnableGlobal("Antigua", false);
			// ==> ������� 
            Group_SetType("Quest_Group", "war");
    		Group_FindOrCreateGroup("Quest_Group");
            for (i=1; i<=3; i++)
            {			
                switch (i)
                {			
                    case 1:
                        ShipType = SHIP_BATTLESHIP;
                        Model = "SpaOfficer1";
                        Rank = 30;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Model = "off_spa_1";
                        Rank = 27;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_GALEON_L;
                        Model = "off_spa_2";
                        Rank = 24;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS16;
                    break;
				}
                sld = GetCharacter(NPC_GenerateCharacter("OurCaptain_"+i, Model, "man", "man", Rank, SPAIN, 0, true));
				sld.ShipEnemyDisable = true; //��� ��������� �� ���������
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
                FantomMakeCoolFighter(sld, Rank, 70, 40, Blade, "pistol3", 50);
				if (sld.id == "OurCaptain_1")
				{
					sld.DeckDialogNode = "First time";
					sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
        			sld.name 	= "�������";
        			sld.lastname = "������ �������";
					sld.greeting = "Gr_military";
        			sld.Abordage.Enable = false; // ������!
					sld.Ship.Name = "������";
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Quest_Group", "OurCaptain_"+i);
			}
            Group_SetGroupCommander("Quest_Group", "OurCaptain_1"); //��� �������
			Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
			Group_SetAddress("Quest_Group", "Antigua", "", "");
			// ==> �����������
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            for (i=1; i<=7; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_NIGHTMARE;
                        Rank = 31;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_WARSHIP;
                        Rank = 33;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 29;
                        Blade = "blade24";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 34;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 32;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 28;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
				}
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(57)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
        			sld.name 	= "������";
        			sld.lastname = "�������";
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = "������";
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }            
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Antigua", "", "");
			// ==> ������������
			Group_SetTaskAttack("Pir_Attack", "Quest_Group");
            Group_SetTaskAttack("Quest_Group", "Pir_Attack");
            Group_LockTask("Quest_Group");
			//Group_LockTask("Pir_Attack");			
			// ==> ���������� �� ������� �������
            pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition = "Sp7SavePardal_AfterBattle";
    		pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1 = "NPC_Death";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1.character = "OurCaptain_1";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition = "Sp7SavePardal_NotSavedPardal";
			pchar.quest.Sp7SavePardal_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp7SavePardal_DieHard.win_condition = "Sp7SavePardal_DieHard";
        break;

        case "Sp7SavePardal_AfterBattle":
			Log_QuestInfo("�������������� ������� ������� �������.");
            pchar.questTemp.State = "Sp7SavePardal_GoodWork";
            AddQuestRecord("Spa_Line_7_SavePardal", "2");
			AddQuestUserData("Spa_Line_7_SavePardal", "sSex", GetSexPhrase("��","��"));
            Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
        break;

        case "Sp7SavePardal_DieHard":
			group_DeleteGroup("Pir_Attack");
			group_DeleteGroup("Quest_Group");
            if (pchar.questTemp.State != "Sp7SavePardal_PardalIsSink" && pchar.questTemp.State != "Sp7SavePardal_GoodWork" && pchar.questTemp.State != "Sp7SavePardal_2GoodWork")
			{
				Log_QuestInfo("������ � ���� ���, ����� �����.");
				pchar.questTemp.State = "Sp7SavePardal_DieHard";
				AddQuestRecord("Spa_Line_7_SavePardal", "3");
				Island_SetReloadEnableGlobal("Antigua", true);
				pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
				pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
			}
        break;

        case "Sp7SavePardal_NotSavedPardal":
            pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
            Island_SetReloadEnableGlobal("Antigua", true);
            AddQuestRecord("Spa_Line_7_SavePardal", "4");
            pchar.questTemp.State = "Sp7SavePardal_PardalIsSink";
        break;
//=================== ����� N8, ������ ������ ===================
        case "Sp8SaveCumana_RescueTimeOver":
            Log_QuestInfo("�������. ������ ��������.");
            pchar.questTemp.State = "Sp8SaveCumana_YouLate";
            AddQuestRecord("Spa_Line_8_SaveCumana", "2");
            pchar.quest.Sp8SaveCumana_Battle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
			//TO_DO �������� � ������
        break;

        case "Sp8SaveCumana_Battle":
            Log_QuestInfo("��������� ������� �����������.");
            pchar.quest.Sp8SaveCumana_RescueTimeOver.over = "yes";
			PChar.questTemp.SLQ8_Diffrent = 1; //�������� ������ � �����
            Island_SetReloadEnableGlobal("Cumana", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 42;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_NIGHTMARE;
                        Rank = 34;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_WARSHIP;
                        Rank = 36;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 32;
                        Blade = "blade24";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 37;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 33;
                        Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 33;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 8:
                        ShipType = SHIP_NIGHTMARE;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(57)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
        			sld.name 	= "�������";
        			sld.lastname = "������";
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = "����";
					LAi_SetStayTypeNoGroup(sld);
				}
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Cumana", "", "");
			Group_LockTask("Pir_Attack");
            pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition = "Sp8SaveCumana_AfterBattle";
			pchar.quest.Sp8SaveCumana_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp8SaveCumana_DieHard.win_condition = "Sp8SaveCumana_DieHard";
        break;

        case "Sp8SaveCumana_AfterBattle":
			Log_QuestInfo("��������� ������� �������.");
            pchar.questTemp.State = "Sp8SaveCumana_GoodWork";
            AddQuestRecord("Spa_Line_8_SaveCumana", "3");
			AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("","�"));
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Cumana", true);
            pchar.quest.Sp8SaveCumana_DieHard.over = "yes";
        break;

        case "Sp8SaveCumana_DieHard":
            Log_QuestInfo("������ � ���� ���, ����� �����.");
            pchar.questTemp.State = "Sp8SaveCumana_DieHard";
            AddQuestRecord("Spa_Line_8_SaveCumana", "4");
	    AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("","�"));
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Cumana", true);
            pchar.quest.Sp8SaveCumana_AfterBattle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
			//TO_DO �������� � ������
        break;
//=================== ����� N9, ������������� ������� �������� ===================
        case "Sp9SaveCumana_toCaimanBattle":
            Log_QuestInfo("������ �������, � ���.");
			pchar.questTemp.State = "Sp9SaveCumana_BackHavana";
            Island_SetReloadEnableGlobal("Caiman", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=5; i++)
            {
                switch (i)
                {
                    case 1:
                        ShipType = SHIP_LINESHIP;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON_H;
                        Rank = 26;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_CARAVEL;
                        Rank = 25;
                        Blade = "blade25";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 4:
                        ShipType = SHIP_GALEON_H;
                        Rank = 27;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_WARSHIP;
                        Rank = 30;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(57)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 90, 80, 80);
                FantomMakeCoolFighter(sld, Rank, 90, 70, Blade, "pistol3", 75);
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Caiman", "", "");
			Group_LockTask("Pir_Attack");
            // ==> ���������� �� ������� �������
            pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition = "Sp9SaveCumana_AfterBattle";
			pchar.quest.Sp9SaveCumana_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp9SaveCumana_DieHard.win_condition = "Sp9SaveCumana_DieHard";
        break;

        case "Sp9SaveCumana_AfterBattle":
            Island_SetReloadEnableGlobal("Caiman", true);
            pchar.quest.Sp9SaveCumana_DieHard.over = "yes";
			group_DeleteGroup("Pir_Attack");
			//--> ������� � ��� ������� �� �����������
			iTemp = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_GALEON_L) iTemp++;
                }
            }
			//--> ��������� � ��
			if (iTemp < 4)
            {
                if (iTemp == 1)
                {
                    AddQuestRecord("Spa_Line_9_FourGolgGaleons", "3");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","�"));
                }
                else
                {
                    AddQuestRecord("Spa_Line_9_FourGolgGaleons", "4");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","�"));
                    AddQuestUserData("Spa_Line_9_FourGolgGaleons", "QtyGaleons", iTemp);
                }
            }
            else 
			{
				AddQuestRecord("Spa_Line_9_FourGolgGaleons", "5");
				AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("","�"));
	        }	    	
        break;
        
        case "Sp9SaveCumana_DieHard":
            pchar.quest.Sp9SaveCumana_AfterBattle.over = "yes";
            AddQuestRecord("Spa_Line_9_FourGolgGaleons", "6");
            Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Pir_Attack");
            for (i=1; i<=4; i++)
            {
                sld = characterFromID("Captain_"+i);
                if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
        break;
//=================== ����� N10, ������ ���������  ===================
        case "Sp10Maracaibo_TalkWithOfficer":
            Log_QuestInfo("������������ � �������� �� ������ �� ����������.");
            sld = GetCharacter(NPC_GenerateCharacter("SpaTalkOfficer", "off_spa_2", "man", "man", 20, SPAIN, 0, true));
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
         	ChangeCharacterAddressGroup(sld, "Maracaibo_town", "goto", "goto8");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Sp10Maracaibo_Battle":
            Log_QuestInfo("��������� ������� �����������.");
            Island_SetReloadEnableGlobal("Maracaibo", false);
    		Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=8; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_MANOWAR_GUB;
                        Rank = 45;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 2:
                        ShipType = SHIP_NIGHTMARE;
                        Rank = 34;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_WARSHIP;
                        Rank = 37;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_CRIMSONBLOOD;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 5:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 39;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 36;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 7:
                        ShipType = SHIP_MANOWAR_GUB;
                        Rank = 42;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
                    break;
                    case 8:
                        ShipType = SHIP_NIGHTMARE;
                        Model = "off_spa_1";
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "officer_"+(rand(57)+1), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
                FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol3", 150);
    			Group_AddCharacter("Pir_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Maracaibo", "", "");
			Group_LockTask("Pir_Attack");
            pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition = "Sp10Maracaibo_AfterBattle";
			pchar.quest.Sp10Maracaibo_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Sp10Maracaibo_DieHard.win_condition = "Sp10Maracaibo_DieHard";
        break;

        case "Sp10Maracaibo_AfterBattle":
			Log_QuestInfo("��������� ������� �������.");
            pchar.questTemp.State = "Sp10Maracaibo_GoodWork";
            AddQuestRecord("Spa_Line_10_Maracaibo", "3");
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            pchar.quest.Sp10Maracaibo_DieHard.over = "yes";
        break;

        case "Sp10Maracaibo_DieHard":
            Log_QuestInfo("������ � ���� ���, ������� �����.");
            pchar.questTemp.State = "Sp10Maracaibo_DieHard";
            AddQuestRecord("Spa_Line_10_Maracaibo", "4");
            group_DeleteGroup("Pir_Attack");
            Island_SetReloadEnableGlobal("Maracaibo", true);
            pchar.quest.Sp10Maracaibo_AfterBattle.over = "yes";
            SetCaptureTownByNation("Maracaibo", ENGLAND);
            UpdateRelations();
            RefreshBattleInterface();
        break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END ��������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  START ����������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//=================== ����� N1, �������� ����� ������� �� ���������  ===================
        case "Fr1Legran_intoLeMaren":			
            GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = characterFromId("Legran");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore39", "goto",  LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            for (i=1; i<=6; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("FraBandit"+i, "Pirate_"+(rand(9)+1), "man", "man", 20, PIRATE, 0, true));
                sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 20, 65, 30, BLADE_LONG, "pistol2", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Shore39", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Fr1Legran_afterFightBandits":
			DeleteAttribute(&locations[FindLocation("Shore39")], "DisableEncounters"); //��������� ������
			chrDisableReloadToLocation = false;
			sld = characterFromId("Legran");
			if (!LAi_IsDead(sld))
			{
				pchar.questTemp.State = "Fr1Legran_afterFightBand";
				LAi_SetActorType(pchar);
				LAi_SetActorType(sld);
				SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.0);
			}
			else
			{
				pchar.questTemp.State = "Fr1Legran_LegranIsDead";
				AddQuestRecord("Fra_Line_1_LegranDis", "5");
			}
        break;
//=================== ����� N2, �������� ������ � �������  ===================
        case "Fr2Letter_intoPrison_1":		
			sld = GetCharacter(NPC_GenerateCharacter("HolPrisoner", "citiz_5", "man", "man", 15, HOLLAND, 0, false));
            sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
            LAi_SetStayTypeNoGroup(sld);
            LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_2", -1);
        break;

        case "Fr2Letter_intoPrison_2":
			pchar.questTemp.State = "Fr2Letter_PrisonTalk";
            sld = characterFromID("HolPrisoner");
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

		case "Fr2Letter_intoPrison_3":
            WaitDate("", 0, 0, 1, 0, 0); //������ ����
			SetCurrentTime(9, 20);
        	RecalculateJumpTable();
            SetLaunchFrameFormParam("������ ���� ����...", "", 0, 6);
            LaunchFrameForm();
			npchar = characterFromId("hol_guber");
			sld = GetCharacter(NPC_GenerateCharacter("GoverFantom", npchar.model, "man", npchar.model.animation, 15, HOLLAND, 0, false));
			sld.name  = "�����";
   			sld.lastname = "���������";
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
            LAi_SetStayTypeNoGroup(sld);
            LAi_LoginInCaptureTown(sld, true);
            ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_4", -1);
        break;

        case "Fr2Letter_intoPrison_4":
			pchar.questTemp.State = "Fr2Letter_VisitGovernor";
            sld = characterFromID("GoverFantom");
			LAi_SetActorType(pchar);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Fr2Letter_OutTavern_1":
			if (!CheckAttribute(pchar, "questTemp.Out"))
			{
				chrDisableReloadToLocation = false;
				bDisableFastReload = true; 
				DoQuestCheckDelay("TalkSelf_Quest", 0.2); //������ ���-��-���
				pchar.quest.Fr2Letter_shore22.win_condition.l1 = "locator";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.location = "Shore22";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator_group = "quest";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator = "detector1";
				pchar.quest.Fr2Letter_shore22.function = "Fr2Letter_shore22";
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Bandit_"+i);
				LAi_SetActorTypeNoGroup(sld);
				sTemp = "goto14";
				if (i==1) sTemp = "goto13";
				ChangeCharacterAddressGroup(sld, "Shore22", "goto", sTemp);
			}
        break;

        case "Fr2Letter_OutTavern_2":
			bDisableFastReload = false; 
			if (GetQuestPastMinutesParam("questTemp") < 5) 
			{
				Log_QuestInfo("����� �������� �� �������.");
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Villemstad_town", "officers", "houseS1_2");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "gate_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1.location = "Villemstad_ExitTown";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition = "Fr2Letter_OutTavern_3";
			}
			else Log_QuestInfo("�� ����� �������� �� �������, ����� � ����� ��������� �����.");	
        break;

        case "Fr2Letter_OutTavern_3":
			if (GetQuestPastMinutesParam("questTemp") < 13) 
			{
				Log_QuestInfo("����� ��������.");
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "goto", "goto11");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1.location = "Curacao_jungle_01";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition = "Fr2Letter_OutTavern_4";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("�� �����, ����� � ����� ��������� �����.");	
        break;

        case "Fr2Letter_OutTavern_4":
			if (GetQuestPastMinutesParam("questTemp") < 19) 
			{
				Log_QuestInfo("����� ��������.");
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_01", "goto", "goto5");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);

				}
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1.location = "Curacao_jungle_02";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition = "Fr2Letter_OutTavern_5";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("�� �����, ����� � ����� ��������� �����.");	
        break;

        case "Fr2Letter_OutTavern_5":
			if (GetQuestPastMinutesParam("questTemp") < 24) 
			{
				Log_QuestInfo("����� ��������.");
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "goto", "goto4");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1.location = "Curacao_jungle_03";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition = "Fr2Letter_OutTavern_6";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("�� �����, ����� � ����� ��������� �����.");	
        break;

        case "Fr2Letter_OutTavern_6":
			if (GetQuestPastMinutesParam("questTemp") < 32) 
			{
				Log_QuestInfo("����� ��������.");
				for (i=1; i<=2; i++)
				{
					sld = characterFromId("Bandit_"+i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_03", "goto", "goto7");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
			}
			else Log_QuestInfo("�� �����, ����� � ����� ��������� �����.");	
        break;

        case "Fr2Letter_FightWithGaleon":
			Log_QuestInfo("������ ������, �� �������!");
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 30, SPAIN, 0, true));
			sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, "���������", CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			FantomMakeCoolFighter(sld, 30, 70, 50, "blade28", "pistol3", 50);
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			// ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			//Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "quest_ships", "Quest_ship_6");
			Group_LockTask("Spa_Attack");
		break;

        case "Fr2Letter_FightAfterShot":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddQuestRecord("Fra_Line_2_DelivLetter", "7");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("��","���"));
        break;
//=================== ����� N3, ��������� ����� ����  ===================
		case "Fr3TakeAnna_FightInHouse":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, true); 
			LAi_group_Delete("PeaceGroup");
			sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = "���� �������";
			sld.lastname = "�� �����";
			sld.greeting = "Gr_Dama";
			sld.RebirthPhantom = true; 
			LAi_NoRebirthEnable(sld);
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Havana_houseS1Bedroom", "goto","goto7");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_group_Delete("EnemyFight");
			//#20171007-02 Rescale fight stats
			int nRank = sti(pchar.rank)+ round((MOD_SKILL_ENEMY_RATE + 1.1) / 4) + 1;
			string sGoto = "goto2";
			Model = "SpaOfficer1";
			iTemp = nRank + 3;
			attrName = "DeLeiva";
            		if(Itemp > 23)
               		iTemp = 23;
			for (i=1; i<=5; i++)
			{
				Model = "Sold_spa_"+(rand(7)+1);
				iTemp = 18;
				attrName = "SpaFighter"+i;
				if (i==1) 
				{	
					Model = "SpaOfficer1";
					iTemp = 23;
					attrName = "DeLeiva";
				}
				sld = GetCharacter(NPC_GenerateCharacter(attrName, Model, "man", "man", iTemp, SPAIN, 0, true));
				//#20171007-02 Rescale fight stats French Quest line
				//FantomMakeCoolFighter(sld, sTemp, 70, 50, BLADE_LONG, "pistol2", 40);
				FantomMakeCoolFighter(sld, iTemp, (50 + round(4 * MOD_SKILL_ENEMY_RATE / 2)), (30 + round(4 * MOD_SKILL_ENEMY_RATE / 2)), BLADE_LONG, "pistol2", (20 + round(10 * MOD_SKILL_ENEMY_RATE / 2)));
				LAi_SetWarriorType(sld);
				if (i==1) 
				{
					sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
					sld.name = "����";
					sld.lastname = "������� �� �����";
					//ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto2");					
				}
				else 
				{
					LAi_warrior_DialogEnable(sld, false);
					//ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto5");
				}
				ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", sGoto);
				Model = "Sold_spa_"+(rand(7)+1);
				iTemp = nRank;
				if(iTemp > 18)
                    iTemp = 18;
				attrName = "SpaFighter"+i;
				sGoto = "goto5";
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("DeLeiva");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DoQuestCheckDelay("MainHeroFightModeOff", 1.0);
		break;

		case "Fr3TakeAnna_DelivShip":
			sld = characterFromId("AnnaDeLeiva");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "5");
				pchar.questTemp.State = "Fr3TakeAnna_BadResult";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "4");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr3TakeAnna_NiceResult";
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
		break;

		case "Fr3_AfterAnna_IKnowYou": //��������� �� � ������� ������.				
			sld = characterFromId("Havana_waitress");
			if (sti(sld.nation) == SPAIN)
			{
				chrDisableReloadToLocation = true;
				LAi_LocationFightDisable(&Locations[FindLocation("Havana_tavern")], false);
				sld.dialog.currentnode = "Allarm";			
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
			}
		break;

//=================== ����� N4, ����� ������, ������������� �� ���������  ===================
		case "Fr4SoleiRoyal_Fight":
            Log_QuestInfo("��������� ������� �����������.");
            Island_SetReloadEnableGlobal("Dominica", false);
			group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=4; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_GALEON1;
                        Rank = 23;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON1;
                        Rank = 21;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_GALEON1;
                        Rank = 23;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS24;
                    break;
                    /*case 4:
                        ShipType = SHIP_WARSHIP;
                        Rank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_GALEON_H;
                        Rank = 24;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 6:
                        ShipType = SHIP_GALEON_H;
                        Rank = 32;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;*/
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, 0, true));
				if (i==3) 
				{
					sld.name = "����";
					sld.lastname = "�������";
					sld.DontRansackCaptain = true;
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 80, 60);
					FantomMakeCoolFighter(sld, Rank, 77, 80, Blade, "pistol5", 80);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
					FantomMakeCoolFighter(sld, Rank, 80, 90, Blade, "pistol3", 50);
				}
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Dominica", "", "");
			Group_LockTask("Spa_Attack");
            pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition = "Fr4SoleiRoyal_WiWon";
			pchar.quest.Fr4SoleiRoyal_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Fr4SoleiRoyal_DieHard.win_condition = "Fr4SoleiRoyal_DieHard";
        break;

        case "Fr4SoleiRoyal_WiWon":
			Log_QuestInfo("��������� ������� �������.");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Dominica", true);
			pchar.quest.Fr4SoleiRoyal_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "4");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("��","����"));
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";

			}
			else
			{
				pchar.questTemp.State = "Fr4SoleiRoyal_GoodWork";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "3");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("��","����"));
			}
        break;

        case "Fr4SoleiRoyal_DieHard":
            Log_QuestInfo("������ � ���� ���, ����� �����.");
            pchar.questTemp.State = "Fr4SoleiRoyal_DieHard";
            AddQuestRecord("Fra_Line_4_SoleiRoyal", "5");
			AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("��","����"));
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Dominica", true);
            pchar.quest.Fr4SoleiRoyal_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
        break;
		//=================== ����� N5, ������� ������� ����� ����  ===================
        case "Fr5Anna_InShore":	
			chrDisableReloadToLocation = true;
			//==> ������� � �����.          
			for (i=1; i<=2; i++)
            {
				if (i==1) sTemp = "officer_12";
				else sTemp = "officer_2";
				sld = GetCharacter(NPC_GenerateCharacter("DeLeivaBrother_"+i, sTemp, "man", "man", 35, SPAIN, -1, true));
				if (i==1)
				{
					sld.name = "�����";
					sld.lastname = "������� �� �����";
					sld.money = 34780;
					FantomMakeCoolFighter(sld, 37, 95, 70, "blade25", "pistol5", 100);
				}
				else
				{
					sld.name = "�������";
					sld.lastname = "�������� �� �����";
					sld.money = 41340;
					FantomMakeCoolFighter(sld, 34, 95, 70, "blade33", "pistol4", 100);
				}				
				sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
				sld.SaveItemsForDead = true; // ��������� �� ����� ����
				sld.DontClearDead = true; // �� ������� ���� ����� 200�	
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_warrior_DialogEnable(sld, true);
				ChangeCharacterAddressGroup(sld, "Mayak10", "goto", "goto12");
				LAi_group_MoveCharacter(sld, "PeaceGroup");
			}	
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], true); 
        break;		
//=================== ����� N6, �������� ������ �����  ===================
        case "Fr6Olone_GuadeloupeBattle":			
            Log_QuestInfo("������� ����������.");
			AddQuestRecord("Fra_Line_6_Olone", "7");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("��","����"));
            bQuestDisableMapEnter = true;
			group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ���
            sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_1", "man", "man", 35, SPAIN, -1, true));
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_CONSTITUTION, "", CANNON_TYPE_CULVERINE_LBS32, 100, 95, 95);
            FantomMakeCoolFighter(sld, 35, 100, 90, BLADE_LONG, "pistol3", 150);
    		Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Guadeloupe", "", "");
			Group_LockTask("Spa_Attack");
			pchar.quest.CanEnterToMap.win_condition.l1 = "NPC_Death";
			pchar.quest.CanEnterToMap.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.CanEnterToMap.win_condition = "CanEnterToMap";
        break;

        case "Fr6Olone_TalkWithOlone":
            //==> �����
			GetCharacterPos(pchar, &locx, &locy, &locz);
			chrDisableReloadToLocation = true;
            sld = characterFromID("Olone");
			LAi_SetCurHPMax(sld);
         	ChangeCharacterAddress(sld, "Cumana_town", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
//=================== ����� N7, �������� �������� ���� ���������  ===================
		case "Fr7RockBras_DelivShip":
			sld = characterFromId("RockBrasilian");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_7_RockBras", "4");
				AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Fra_Line_7_RockBras", "sSex1", GetSexPhrase("","��"));
				pchar.questTemp.State = "Fr7RockBras_RockIsDead";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_7_RockBras", "3");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr7RockBras_RockIsSaved";
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
		break;
//=================== ����� N9, ������ ��������� �� ����-�-�����  ===================
		case "Fr9GuardPP_Late":
			pchar.quest.Fr9GuardPP_Fight.over = "yes";
			pchar.questTemp.State = "Fr9GuardPP_Late";
			AddQuestRecord("Fra_Line_9_GuardPortPax", "5");
			AddQuestUserData("Fra_Line_9_GuardPortPax", "sSex", GetSexPhrase("","�"));
            SetCaptureTownByNation("PortPax", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
		break;

		case "Fr9GuardPP_Fight":
            Log_QuestInfo("��������� ������� �����������. ��� ����� ������� �����...");
			pchar.quest.Fr9GuardPP_Late.over = "yes";
            Island_SetReloadEnableGlobal("Hispaniola2", false);
    		group_DeleteGroup("Spa_Attack");
    		Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
            // ==> ��������� ����
            for (i=1; i<=6; i++)
            {
                switch (i)
                {
					case 1:
                        ShipType = SHIP_SP_SANFELIPE;
                        Rank = 40;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
                    break;
                    case 2:
                        ShipType = SHIP_GALEON1;
                        Rank = 30;
                        Blade = "blade31";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 3:
                        ShipType = SHIP_LINK2;
                        Rank = 38;
                        Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    case 4:
                        ShipType = SHIP_WARSHIP;
                        Rank = 35;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_GALEON1;
                        Rank = 31;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 6:
                        ShipType = SHIP_LINESHIP;
                        Rank = 36;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
                    break;
                    /*case 7:
                        ShipType = SHIP_GALEON_H;
                        Rank = 30;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 8:
                        ShipType = SHIP_BATTLESHIP;
                        Rank = 37;
                        Blade = "blade35";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;*/
                }
                sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, 0, true));
				if (i==2 || i==5 || i==7) 
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 90, 70);
					FantomMakeCoolFighter(sld, Rank, 90, 90, Blade, "pistol3", 100);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 100, 90);
					FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol5", 200);
				}
    			Group_AddCharacter("Spa_Attack", "CaptainAttack_"+i);
            }
            // ==> ������������
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola2", "", "");
			Group_LockTask("Spa_Attack");
            pchar.quest.Fr9GuardPP_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr9GuardPP_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr9GuardPP_WiWon.win_condition = "Fr9GuardPP_WiWon";
			pchar.quest.Fr9GuardPP_DieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Fr9GuardPP_DieHard.win_condition = "Fr9GuardPP_DieHard";
        break;

        case "Fr9GuardPP_WiWon":
			Log_QuestInfo("��������� ������� �������.");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			pchar.quest.Fr9GuardPP_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_9_GuardPortPax", "3");
				pchar.questTemp.State = "Fr9GuardPP_SoleiRoyalSunk";

			}
			else
			{
				pchar.questTemp.State = "Fr9GuardPP_GoodWork";
				AddQuestRecord("Fra_Line_9_GuardPortPax", "2");
			}
        break;

        case "Fr9GuardPP_DieHard":
            Log_QuestInfo("������ � ���� ���, ������� �����.");
            pchar.questTemp.State = "Fr9GuardPP_DieHard";
            AddQuestRecord("Fra_Line_9_GuardPortPax", "4");
            group_DeleteGroup("Spa_Attack");
            Island_SetReloadEnableGlobal("Hispaniola2", true);
            pchar.quest.Fr9GuardPP_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
            SetCaptureTownByNation("PortPax", SPAIN);
            UpdateRelations();
            RefreshBattleInterface();
        break;
//=================== ����� N12, ����� �����  ===================
        case "Fr12EndOfWar_TakeOutShip":
			group_DeleteGroup("SoleiRoyal");
        break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  END ����������� �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////   �������� ������   //////////////////////////////////////////
        case "Romantic_Pirat_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			FreeSitLocator("Pirates_tavern", "sit2");
			DoQuestReloadToLocation("Pirates_tavern", "sit", "sit2", "");			
			sld = characterFromID("Atilla");        
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
        break;

        case "Romantic_Pirat_toTavern_end":
			chrDisableReloadToLocation = false; 
			bDisableFastReload = false; 
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //������ ��������� ��� ��������
			pchar.RomanticQuest = "toSalvator";
			AddQuestRecord("Romantic_Line", "3");
			LAI_SetPlayerType(pchar);           
            DoQuestReloadToLocation("Pirates_tavern", "tables", "stay3", "");
            sld = CharacterFromID("Atilla");
            LAI_SetSitType(sld);
            Pchar.quest.Romantic_TalkInShop.win_condition.l1 = "location";
            Pchar.quest.Romantic_TalkInShop.win_condition.l1.location = "SanJuan_Store";
            Pchar.quest.Romantic_TalkInShop.win_condition = "Romantic_TalkInShop";
            PChar.quest.Romantic_TalkInShop.again = true; // ������ �� �����, �� �� ����, ��� Pchar.RomanticQuest.TalkInShop = true; ����
            PChar.quest.Romantic_TalkInShop.DontCheck = true;            
            Pchar.RomanticQuest.PriestAsk = true;
        break;

        case "RP_afterVisitBedroom":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			sld = characterFromID("Husband");        
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", -1, 0);
        break;

        case "RP_talkWithHusbandIsOver":     
			LAi_SetStayType(characterFromID("Husband"));
        break;

        case "Romantic_TalkInShop":
            if(CheckAttribute(Pchar, "RomanticQuest.TalkInShop"))
            {
                PChar.quest.Romantic_TalkInShop.over = "yes";
                characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_1";
                sld = CharacterFromID("Isabella");
        		LAi_SetStayType(sld);
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
                sld.dialog.currentnode = "TalkInShop";
    			LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "Romantic_TalkInShop_3", -1, 0);
            }
        break;

        case "Romantic_TalkInShop_2":
			sld = characterFromID("Isabella");
            LAi_ActorDialog(sld, Pchar, "", 1.0, 0);
        break;

        case "Romantic_TalkInShop_3":
            sld = CharacterFromID("SanJuan_trader");
			LAi_SetActorType(sld);
            LAi_ActorDialog(sld, Pchar, "", 0.0, 0);
        break;

        case "Romantic_TalkInShop_end": 
			chrDisableReloadToLocation = false;
            LAi_SetStayType(characterFromID("SanJuan_trader"));
            LAI_SetPlayerType(Pchar);
            AddQuestRecord("Romantic_Line", "4");
			sld = CharacterFromID("Isabella");
			LAi_SetCitizenType(sld);
            sld.dialog.currentnode = "TalkInChurch";
			DoQuestFunctionDelay("SetIsabellaTalker", 4.0);
        break;
        
        case "Romantic_Battle_in_Bedroom_1":
            sld = CharacterFromID("Husband");
            ChangeCharacterAddressGroup(sld, "SanJuan_houseS1Bedroom", "reload", "reload1");
            LAi_SetActorType(Pchar);
			LAi_SetActorType(sld);
            LAi_ActorFollow(sld, Pchar, "Romantic_Battle_in_Bedroom_2", 3.0);
        break;

        case "Romantic_Battle_in_Bedroom_2":
            sld = CharacterFromID("Husband");
            sld.Dialog.CurrentNode = "Romantic_Battle_in_Bedroom";
            LAi_ActorWaitDialog(Pchar, sld);
		    LAi_ActorDialog(sld, Pchar, "", 2.0, 0);
        break;
        
        case "Romantic_Battle_in_Bedroom_3":
			pchar.quest.RP_afterVisitBedroom.over = "yes";
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;             
            LAi_SetPlayerType(pchar);
            ChangeCharacterReputation(pchar, -15);  
			sld = CharacterFromID("Husband");
            Lai_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
	        LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
	        LAi_group_SetCheck("TmpEnemy", "Romantic_Battle_in_Bedroom_End");
        break;
        
        case "Romantic_Battle_in_Bedroom_End":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
            sld = CharacterFromID("Isabella");
            sld.Dialog.CurrentNode = "Murder";
            AddQuestRecord("Romantic_Line", "1");
            CloseQuestHeader("Romantic_Line");
        break;
        
        case "Romantic_Battle_in_Bedroom_4":
            LAi_SetPlayerType(pchar);
            sld = CharacterFromID("Husband");
            LAi_ActorRunToLocation(sld, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto5", "Romantic_Battle_in_Bedroom_5", 2.0);
	        AddQuestRecord("Romantic_Line", "2");
        break;
        
        case "Romantic_Battle_in_Bedroom_5":
            sld = CharacterFromID("Husband");
            LAi_SetHuberStayType(sld);
	        LAi_SetStayHuberPointWindow(sld, "goto", "goto1");
	        LAi_SetStayHuberPointMap(sld, "goto", "goto2");
        break;
        // �������      
        case "Romantic_TalkInChurch_end":
            sld = CharacterFromID("Isabella");
            LAi_SetStayType(sld);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
        break;
        // �������� � ������ � ����� ������ -->
        case "Romantic_Brother":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
            Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
			sld = GetCharacter(NPC_GenerateCharacter("MigelDeValdes", "citiz_9", "man", "man", 5, SPAIN, -1, true));
            sld.name 	= "������";
	        sld.lastname = "�� �������";
			sld.SaveItemsForDead = true; // ��������� �� ����� ����
			sld.DontClearDead = true; // �� ������� ���� ����� 200�
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
	        sld.dialog.currentnode = "Romantic_Brother_1";	
			sld.greeting = "Gr_YoungMan";
            PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);			
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
        break;
        
        case "Romantic_Brother_port":
			chrDisableReloadToLocation = true; 
            Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
            sld = CharacterFromID("MigelDeValdes");
	        sld.dialog.currentnode = "Romantic_Brother_port_1";
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            //PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);
        break;		
		// --> �������� � ���� � ������, ����� 8
        case "Romantic_Brother_House":
            sld = CharacterFromID("Isabella");
            sld.dialog.currentnode = "Brother_1";
            ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto3");
            LAi_SetActorType(sld);            
            sld = CharacterFromID("MigelDeValdes");
            sld.dialog.currentnode = "Romantic_Brother_port_1";
            ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto4");
            LAi_SetActorType(sld);           
			pchar.RomanticQuest = "exitFromDetector";
        break;
        
        case "Romantic_Brother_House_3":
            // �� �������
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie();            
            LAi_SetCitizenType(characterFromID("Isabella"));
			sld = characterFromID("MigelDeValdes");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "Romantic_Brother_Thanks";
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "WeWaitYouTonight";
			pchar.RomanticQuest = "DelivMigel"; //���� "������ ���������"
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //��������� �����, ����� �� �������� �� ���� ����� ������������
        break;
		// --> ������ �����
        case "Romantic_DeadBrother_1":
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			chrDisableReloadToLocation = true; 
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();	
			npchar = characterFromID("MigelDeValdes");
			LAi_group_MoveCharacter(npchar, "BrotherGroup");
			sld = characterFromID("Husband");			
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", "BrotherGroup", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", "BrotherGroup", true);
			LAi_group_SetCheck("BrotherGroup", "Romantic_DeadBrother_2");	
			LAi_LockFightMode(pchar, true); //����� �� �������
			EndQuestMovie();
        break;

		case "Romantic_DeadBrother_2":         
			LAi_group_Delete("BrotherGroup");
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "SeenMainHero";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
        break;

		case "Romantic_DeadBrother_3":         
			sld = characterFromID("Husband");
			LAi_SetStayType(sld);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true); //������� ����, � �� ����� ���� �������
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], true); 
			// ������ �������� � ��� �� �������� ��� ������� � ���������� ����� ������
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
		break;

		case "Romantic_DeadBrother_Cancel": //���� �� �� ����� � ���� �������� � ������� �����        
			pchar.RomanticQuest = "QuestOver";
			//LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //��������� ����� � ��� ��������
			ChangeCharacterAddress(CharacterFromID("Husband"), "none", "");
			ChangeCharacterAddress(CharacterFromID("MigelDeValdes"), "none", "");
			CloseQuestHeader("Romantic_Line");
		break;
		// --> ������� ������ ��
		case "Romantic_ArrestInHouse":
			// ������ �������� � ��� �� �������� ��� ������� � ���������� ����� ������
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
			//��������� ������� �� �����   
			npchar = characterFromID("Husband");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto3", "", 5.0);
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //����� ���������, ����� �� �� ���� �� ������� � ���
			//������� �� ����� ��
			iTemp = FindColony("SanJuan");
			sTemp = NationShortName(sti(colonies[iTemp].nation));
            for (i=1; i<=3; i++)
            {
				if (i==1) 
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "officer_18";
					}
					else
					{
						Model = "off_" + sTemp + "_1";
					}
					Rank = sti(pchar.rank)+ MOD_SKILL_ENEMY_RATE + 6;
					Blade = "blade20";
				}
				else 
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "pirate_" + i;
					}
					else
					{
						Model = "sold_" + sTemp + "_" +(rand(7)+1);
					}
					Rank = sti(pchar.rank)+ MOD_SKILL_ENEMY_RATE + 2;
					Blade = "blade24";
				}
				sld = GetCharacter(NPC_GenerateCharacter("Soldier_"+i, Model, "man", "man", Rank, sti(colonies[iTemp].nation), 0, true));
				//FantomMakeCoolFighter(sld, Rank, 100, 90, Blade, "pistol5", 200);
				//Boyer mod
				FantomMakeCoolFighter(sld, Rank, (80 + round(4 * MOD_SKILL_ENEMY_RATE / 2)), (70 + round(4 * MOD_SKILL_ENEMY_RATE / 2)), Blade, "pistol5", (140 + round(10 * MOD_SKILL_ENEMY_RATE / 2)));
				sld.City = colonies[iTemp].id;
				sld.CityType = "soldier";
				sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
				sld.dialog.currentnode = "ArrestInHome_2";
				LAi_SetWarriorType(sld);
				if (i != 1) LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, GetNationNameByType(sti(colonies[iTemp].nation)) + "_citizens");
				ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "reload", "reload1");
			}
			sld = characterFromID("Soldier_1");
			LAi_SetActorTypeNoGroup(sld);
			//LAi_ActorDialog(sld, pchar, "", 1.5, 0);
			//Boyer mod #20170318-33...give slightly more time...to find cover maybe?
			nTimeAdd = MOD_SKILL_ENEMY_RATE * 0.13;
        break;
		//����� ��� ������ ������ - � ���
		case "Romantic_AtillaToHouse":
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode =  "AtillaInHouse";
        break;
		//������ � ���� ���������� � ���-�����
		case "Romantic_AmbushInHouse":
            Log_QuestInfo("������ ����������.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], true);
            LAi_group_Delete("EnemyFight");
			for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+10), "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol2", 20);
            	LAi_SetStayType(sld);  
				LAi_CharacterDisableDialog(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto",  "goto"+i);
            }
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushBandit";
			LAi_CharacterEnableDialog(sld);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
		//����� ����� � ���������
        case "Romantic_BrigTimeOver":
			Log_QuestInfo("�� ����� � ����� � ����� �����. �������� �������.");
            pchar.quest.Romantic_AttackBrig.over = "yes";
            AddQuestRecord("Romantic_Line", "14");
            QuestSetCurrentNode("Atilla", "Brig_Late"); //���� ������ �� �������
        break;

        case "Romantic_AttackBrig":
            Log_QuestInfo("���� ������, �� �������!");
            pchar.quest.Romantic_BrigTimeOver.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", false);
    		Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
            sld = GetCharacter(NPC_GenerateCharacter("IsaAttackCap", "officer_14", "man", "man", 20, PIRATE, 0, true));
            sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "BrigAbordage";
            FantomMakeCoolSailor(sld, SHIP_BRIG, "������������", CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
            FantomMakeCoolFighter(sld, 20, 70, 50, "blade24", "pistol3", 20);
			sld.DontRansackCaptain = true;
			Group_AddCharacter("Pirate_Attack", "IsaAttackCap");
            // ==> ������������
			Group_SetGroupCommander("Pirate_Attack", "IsaAttackCap");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
            Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PortoBello", "", "");
			Group_LockTask("Pirate_Attack");
            // ==> ����������
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1.character = "IsaAttackCap";
			pchar.quest.Romantic_AfterBrigSunk.win_condition = "Romantic_AfterBrigSunk";
			pchar.quest.Romantic_BrigDieHard.win_condition.l1 = "MapEnter";
            pchar.quest.Romantic_BrigDieHard.win_condition = "Romantic_BrigDieHard";
        break;
        
        case "Romantic_BrigDieHard":
            pchar.quest.Romantic_AfterBrigSunk.over = "yes";
            group_DeleteGroup("Pirate_Attack");
            Island_SetReloadEnableGlobal("PortoBello", true);
            AddQuestRecord("Romantic_Line", "16");
            QuestSetCurrentNode("Atilla", "Brig_DieHard"); //���� ������ �� ���� ���� �� ������
        break;

        case "Romantic_AfterBrigSunk":
            pchar.quest.Romantic_BrigDieHard.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", true);
            group_DeleteGroup("Pirate_Attack");
            AddQuestRecord("Romantic_Line", "15");
            QuestSetCurrentNode("Atilla", "Brig_Sunk"); //���� ������ ���� ������
        break;

        case "Romantic_TaklInCabinBrig": 
			sld = characterFromID("Isabella");
			sld.dialog.currentnode = "BrigAbordage";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
        break;
		//������ � ����� �����
		case "Romantic_AmbushInPortoBello":
            Log_QuestInfo("������ ����������.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], true);
			LAi_group_Delete("EnemyFight");
            for (i=4; i<=5; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+i, "man", "man", 30, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 30, 80, 70, "topor2", "pistol3", 40);
            	LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "PortoBello_houseF2", "goto",  "goto"+i);
            }
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushPotroBello";
			LAi_CharacterEnableDialog(sld);
            LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

		case "Romantic_TalkPortoBello":
			chrDisableReloadToLocation = false; 
            sld = CharacterFromID("Isabella");
	        sld.dialog.currentnode = "AmbushPortoBello";
            ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 1.5);
        break;
		//����� � ��������� � ���� ������
        case "Romantic_BelizCityTalk":
			chrDisableReloadToLocation = true; 
            Pchar.GenQuest.Hunter2Pause = true; // ���� �� �����.
            sld = CharacterFromID("Isabella");
	        sld.dialog.currentnode = "BelizTalk";
            ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto17");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;
		//������ ��������� �������� � ������
        case "Romantic_BanditIsDead":
            sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;
		//��������� � ������
        case "Romantic_SalvatorInCave":
			LAi_LockFightMode(pchar, true); //����� �� �������
            sld = CharacterFromID("Husband");
	        sld.dialog.currentnode = "TalkInCave";
			sld.items.jewelry5 = 100;
			sld.items.jewelry13 = 7;
			sld.items.jewelry14 = 6; 
			sld.items.jewelry15 = 5; 
			sld.items.jewelry17 = 30; 
			sld.items.jewelry18 = 12; 
			sld.items.indian1 = 1; 
			sld.items.indian5 = 1; 
			sld.items.indian6 = 1; 
			sld.items.indian10 = 2; 
			sld.items.indian12 = 1; 
			sld.items.indian14 = 1; 
			sld.items.jewelry12 = 12; 
			sld.items.jewelry11 = 6; 
			sld.items.jewelry10 = 20; 
			sld.items.jewelry7 = 21; 
			sld.items.jewelry6 = 11; 
			sld.items.jewelry4 = 7; 
			sld.items.jewelry3 = 15;
			sld.items.jewelry2 = 18;
			sld.items.jewelry1 = 31;
			sld.money = 350535;
			Lai_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;

        case "Romantic_SalvatorIsDead":
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", false); //�������� �������
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", false); //�������� ��������
			QuestSetCurrentNode("Isabella", "SalvatorIsDead");
            sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
        break;

		// --> �������� �������� � ������� � ���� ����� ������������ ��������
        case "Romantic_DelivToRosita": 
			if (GetCharacterIndex("Isabella") == -1)
			{
				QuestSetCurrentNode("Rosita", "IsabellaIsDead_Beliz");
			}
			else
			{
				pchar.RomanticQuest = "Beliz_exitFromDetector";
				QuestSetCurrentNode("Rosita", "SavedIsabella");
			}
        break;
        
        case "Romantic_DelivToRosita_2":
            // �� �������
            SetMainCharacterIndex(1);
            PChar = GetMainCharacter();
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie();            
            LAi_SetCitizenType(characterFromID("Rosita"));
			sld = characterFromID("Isabella");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "RositaHouse";
			//����� ����� �������� - � ���-����
			SetTimerCondition("Romantic_IsabellaToSanJuan", 0, 1, 0, false);
        break;

        case "Romantic_IsabellaToSanJuan":
			sld = CharacterFromID("Isabella");
			ChangeCharacterAddressGroup(sld , "SanJuan_houseSp6", "goto",  "goto1");
			sld.dialog.currentnode = "InSanJuanAgain";
        break;

        case "Romantic_OutFromHouse":
			DoReloadCharacterToLocation("SanJuan_town", "reload", "houseSp6");
        break;

		case "Romantic_Widding_Cancel": //���� �� �� ����� � � ������� ��� �������� � ������� �����        
			pchar.quest.Isabella_widding.over = "yes";
			pchar.RomanticQuest = "QuestOver";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //��������� ���
			sld = characterFromID("Isabella");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "Cancel_Widding";
			ChangeCharacterAddressGroup(sld , "SanJuan_houseSp6", "goto",  "goto1");
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
		break;
		//������� �������� � ��. �����������!!!!!
        case "Romantic_Padre":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "barmen", "stay");
			DoQuestCheckDelay("Romantic_Padre_1", 1.0);
        break;

        case "Romantic_Padre_1":
            SetLaunchFrameFormParam("�� ����� ������ ������ ����� �����.", "Romantic_Padre_2", 0, 3);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 0, 40);
        	RecalculateJumpTable();
        break;

        case "Romantic_Padre_2":
			StartQuestMovie(true, true, true);
			locCameraToPos(-1.52, 3.25, -3.36, false);
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.currentnode = "Romantic_2";
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("SanJuan_Priest", "", 0.0, 0.0);
		    LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Romantic_Padre_3":
            LAi_SetPlayerType(PChar);
			locCameraTarget(PChar)
            locCameraFollow();
            EndQuestMovie(); 
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			DoQuestCheckDelay("Romantic_fightInChurch", 2.0);
        break;
		//��������� �������� � ������
        case "Romantic_fightInChurch":
            Log_QuestInfo("��������� ������� ����������.");
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
			LAi_group_Delete("EnemyFight");
			iTemp = sti(2+(MOD_SKILL_ENEMY_RATE/1.5));
			Rank = 10+MOD_SKILL_ENEMY_RATE*2;
            for (i=1; i<=iTemp; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+3), "man", "man", Rank, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, Rank, 80, 70, "topor2", "pistol1", 40);
				sld.equip.gun = "";
            	LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
            	sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";				
                LAi_group_MoveCharacter(sld, "EnemyFight");				
               	ChangeCharacterAddressGroup(sld, "SanJuan_church", "reload",  "reload1");
            }
			sld.dialog.currentnode = "AmbushInChurch";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
        break;

		case "Romantic_fightInChurch_1":
			sld = characterFromID("Isabella");
 			sld.dialog.currentnode = "AmbushInChurch";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);       
		break;

		case "Romantic_fightInChurch_2":		
			LAi_LocationFightDisable(loadedLocation, false); 
			//����� � �������
			sld = characterFromID("SanJuan_Priest");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar2", "", -1);
			//�������
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("EnemyFight", "SPAIN_CITIZENS", LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Romantic_afterFightInChurch");
			//�������� � �������
			sld = characterFromID("Isabella");
			//LAi_SetImmortal(sld, false); // ��� ������
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			LAi_SetFightMode(sld, false);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar1", "", -1);	
        break;

		case "Romantic_afterFightInChurch":
            chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, true);
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld = CharacterFromID("Isabella");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Romantic_Line", "25");
				pchar.RomanticQuest = "IsabellaIsDead";
				QuestSetCurrentNode("Atilla", "IsabellaIsDead");
				QuestSetCurrentNode("Rosita", "IsabellaIsDead");
			}
			else
			{
				AddQuestRecord("Romantic_Line", "26");
				pchar.RomanticQuest = "IsabellaIsMyWife";
				QuestSetCurrentNode("Atilla", "IsabellaIsMyWife");
				QuestSetCurrentNode("Rosita", "IsabellaIsMyWife");
				LAi_SetCitizenType(CharacterFromID("Isabella"));
				QuestSetCurrentNode("Isabella", "IsabellaIsMyWife");
			}
        break;
		//����� ��������� �����.
		case "Romantic_afterFirstTime":
			SaveCurrentQuestDateParam("RomanticQuest");
			IsabellaSetCurrentState("all");  //����������� ������� ����������
			IsabellaCheckBreachState(); //��� �� ��������� ��� ��������� ����� ��
			pchar.RomanticQuest.HorseCheck = pchar.questTemp.HorseQty; //���������� ������� ���-�� ��������� ��������
			IsabellaNullBudget(); //����� �������� ������
			sld = CharacterFromID("Isabella");
			sld.greeting = "Gr_Isabella_1";
			SaveCurrentNpcQuestDateParam(sld, "sex"); //���������� ��������� ���� 
			sld.sex.control_year = sti(sld.sex.control_year) - 1; //-1 ��� (��� ������� ����)
			QuestSetCurrentNode("Rosita", "IsabellaIsWife"); //������ ����, �� ������� ��� �������� ����� � ����������
			pchar.RomanticQuest = "NewLifeForHero";
			AddQuestRecord("Romantic_Line", "28");
			AddQuestUserData("Romantic_Line", "IsabellaBuget", FindRussianMoneyString(MOD_SKILL_ENEMY_RATE*10000));
			//���������� �� ���� � ��� ��������
			Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
			Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
			Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
		break;
		//��������� �������� �� ��������� ������� �� ����� � ���
		case "Romantic_EnterHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				IsabellaCheckBreachState();
				pchar.RomanticQuest.Cheking = "";
				QuestSetCurrentNode("Isabella", "NewLife_hello");
				Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
				Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
			}     
		break;

		case "Romantic_OutHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				pchar.RomanticQuest = "NewLifeForHero";     //��� �������� ������ ��������� �� ��������� ����
				SaveCurrentQuestDateParam("RomanticQuest"); //��� ����� ����� � ��������
				Pchar.quest.Romantic_EnterHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_EnterHome.win_condition.l1.location = "SanJuan_houseSp6";
				Pchar.quest.Romantic_EnterHome.win_condition = "Romantic_EnterHome";
			}     
		break;
		//��� ���� ������.
		case "Romantic_Sex":			
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			if (GetNpcQuestPastMinutesParam(sld, "sex") > 10)
			{
				QuestSetCurrentNode("Isabella", "NewLife_Sex_Late");
				LAi_ActorDialog(sld, pchar, "", 1.0, 0);    
			}
			else
			{
				DoQuestCheckDelay("PlaySex_1", 3.0);
			}
		break;

		case "PlaySex_1":
			ResetSound();
			iTemp = rand(13)+1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			sGlobalTemp = iTemp;
			//LAi_FadeDelay(fTemp, "loading\inside\censored1.tga");
			//StartPictureAsVideo( "loading\inside\censored1.tga", fTemp );
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
            LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);			
		break;

		case "PlaySex_2":
			PlayStereoSound("sex\sex" + sGlobalTemp + ".wav");
            AddTimeToCurrent(2, rand(30));
			if (pchar.location == "SanJuan_houseS1Bedroom")
			{
			    QuestSetCurrentNode("Isabella", "NewLife_afterSex");
			    LAi_SetStayType(CharacterFromID("Isabella"));
			}
			//����� ����������
			if (pchar.questTemp.different == "FackWaitress_facking")
			{
				sld = characterFromId("WairessQuest");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterHealth(pchar, 3);
            	AddCharacterExpToSkill(pchar, "Fencing", -15);
            	AddCharacterExpToSkill(pchar, "Pistol", -15);
				ChangeCharacterReputation(pchar, -1);
				if (sti(pchar.questTemp.different.FackWaitress.Kick) != 1) 
				{
					pchar.questTemp.different = "FackWaitress_fackNoMoney";
					AddCharacterExpToSkill(pchar, "Fortune", 100);
				}
				pchar.money = sti(pchar.money) / sti(pchar.questTemp.different.FackWaitress.Kick);
				chrDisableReloadToLocation = false;
			}
			//����� ������� ������� �������
			if (pchar.questTemp.different == "HostessSex" && CheckAttribute(pchar, "questTemp.different.HostessSex.city"))
			{
				sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
				ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
				LAi_SetOwnerTypeNoGroup(sld);
				DeleteAttribute(pchar, "questTemp.different.HostessSex");
				pchar.questTemp.different = "free";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "EncGirl_facking")
			{
				sld = characterFromId("CangGirl");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
            	AddCharacterExpToSkill(pchar, "Fencing", -20);
            	AddCharacterExpToSkill(pchar, "Pistol", -20);
				AddCharacterHealth(pchar, 5);
				ChangeCharacterReputation(pchar, -1);
				pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/15);
				chrDisableReloadToLocation = false;
				SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
			}
		break;

		case "Romantic_IsabellaBackToHall":
			Pchar.quest.Romantic_Sex.over = "yes";
            sld = CharacterFromID("Isabella");
            LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto",  "goto1"); 
			QuestSetCurrentNode("Isabella", "NewLife");
		break;

		case "sleep_in_home":
			DoQuestReloadToLocation("SanJuan_houseS1Bedroom", "goto", "goto4", "restore_hp");
		break;

/////////////////////////////////////   �������� �����   //////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ����� �������� ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
			int iCannonType, iShipType;
			string sShipName;
        case "Ascold_AttackTenManowars":
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", true); //������� �� ���� ����
			Island_SetReloadEnableGlobal("Caiman", false);
            pchar.questTemp.Ascold = "ILookedThisAss";
            // ==> �������, ���� �������� ��������
            i = rand(5)+1;
            pchar.questTemp.Ascold.Ship = "AscoldCaptainAttack_" + i;
			Log_QuestInfo("������ � �������� � ID ����: " + pchar.questTemp.Ascold.Ship);
            // ==> ������ ��������� �������� �������
            ChangeItemDescribe("ShipsJournal", "itmdescr_ShipsJournal_Ascold");
    		Group_FindOrCreateGroup("Ascold_Spa_Attack");
			Group_SetType("Ascold_Spa_Attack", "war");
            // ==> ��������� ����
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			for (i = 1; i <=6; i++)
			{                
				Rank = 30 + rand(5);
				sTemp = "AscoldCaptainAttack_"+i;
				switch (i)
				{
					case 1:
						iCannonType = CANNON_TYPE_CANNON_LBS42;
						iShipType = SHIP_SANTISIMA;
						sShipName = "���������";
						Blade = "blade20";
					break;
					case 2:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_BELLONA;
						sShipName = "";
						Blade = "topor2";
					break;
					case 3:
						iCannonType = CANNON_TYPE_CULVERINE_LBS32;
						iShipType = SHIP_WARSHIP;
						sShipName = "";
						Blade = "blade15";
					break;
					case 4:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_WARSHIP;
						sShipName = "";
						Blade = "blade31";
					break;
					case 5:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_BATTLECORVETTE;
						sShipName = "";
						Blade = "blade21";
					break;
					case 6:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_CORVETTE;
						sShipName = "";
						Blade = "blade34";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter(sTemp, "off_spa_"+(rand(1)+1), "man", "man", Rank, SPAIN, -1, true));	
				FantomMakeCoolSailor(sld, iShipType, sShipName, iCannonType, 90, 90, 90);
				FantomMakeCoolFighter(sld, Rank, 90, 90, Blade, "pistol3", 100);
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.SuperShooter  = true;
				sld.ship.Crew.Morale = 100;
				ChangeCrewExp(sld, "Sailors", 100);
				ChangeCrewExp(sld, "Cannoners", 100);
				ChangeCrewExp(sld, "Soldiers", 90);
				SetRandGeraldSail(sld, sti(sld.Nation)); 
				Group_AddCharacter("Ascold_Spa_Attack", sTemp);
			}
            // ==> ������������
			Group_SetGroupCommander("Ascold_Spa_Attack", "AscoldCaptainAttack_1");			
			//Group_SetPursuitGroup("Ascold_Spa_Attack", PLAYER_GROUP); //TO_DO
			Group_SetAddress("Ascold_Spa_Attack", "Caiman", "quest_ships", "quest_ship_6");
			Group_SetTaskAttack("Ascold_Spa_Attack", PLAYER_GROUP);
			Group_LockTask("Ascold_Spa_Attack");
            // ==> ���������� �� ������� �������
            pchar.quest.Ascold_VictoryManowar.win_condition.l1 = "Group_Death";
			pchar.quest.Ascold_VictoryManowar.win_condition.l1.group = "Ascold_Spa_Attack";
			pchar.quest.Ascold_VictoryManowar.win_condition = "Ascold_VictoryManowar";
			pchar.quest.Ascold_DieHardManowar.win_condition.l1 = "MapEnter";
			pchar.quest.Ascold_DieHardManowar.win_condition = "Ascold_DieHardManowar";
			//SetTimerCondition("Ascold_ManowarRepair", 0, 0, 10, true);
        break;

        case "Ascold_VictoryManowar":
			//PChar.quest.Ascold_ManowarRepair.over = "yes";
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", false); //������� ����
			Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_DieHardManowar.over = "yes";
            pchar.questTemp.Ascold = "Ascold_ManowarsDead";
            DeleteAttribute(PChar, "questTemp.Ascold.Ship");
            AddQuestRecord("Ascold", "9");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("","�"));
            Pchar.quest.Ascold_FightNearTemple.win_condition.l1 = "location";
            Pchar.quest.Ascold_FightNearTemple.win_condition.l1.location = "Temple";
            Pchar.quest.Ascold_FightNearTemple.win_condition = "Ascold_FightNearTemple";
        break;

		case "Ascold_DieHardManowar":
            Island_SetReloadEnableGlobal("Caiman", true);
            group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_VictoryManowar.over = "yes";
            pchar.questTemp.Ascold = "Ascold_ManowarsNoDead";
			DeleteAttribute(PChar, "questTemp.Ascold.Ship");
            AddQuestRecord("Ascold", "9_1");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("","�"));
        break;
/*
        case "Ascold_ManowarRepair": //������ ���������
			if (pchar.location != "Beliz")
			{
				for (i=1; i<=10; i++)
				{
					iTemp = GetCharacterIndex("AscoldCaptainAttack_" + i);
					if (iTemp != -1)
					{
						sld = &characters[iTemp];
						SetCrewQuantityFull(sld);
						DeleteAttribute(sld, "ship.sails");// ������ ���� �� �������
						DeleteAttribute(sld, "ship.blots");
						DeleteAttribute(sld, "ship.masts");// ������� ������ �����
						SetBaseShipData(sld);
					}
				}
			}
        break;
*/
        case "Ascold_FightNearTemple":
            chrDisableReloadToLocation = true; // ������� ����� �� �������
			LAi_group_Delete("EnemyFight");
            for (i=1; i<=20; i++)
            {
                if (i==1 || i==8 || i==11 || i==15) 
                {					
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "off_spa_"+(rand(1)+1), "man", "man", 25, SPAIN, 0, true));	
					FantomMakeCoolFighter(sld, 25, 80, 80, BLADE_LONG, "pistol5", 100);
                }
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, 0, true));	
					FantomMakeCoolFighter(sld, 20, 50, 50, BLADE_LONG, "pistol3", 40);
				}
            	LAi_SetWarriorType(sld);				
				if (i < 16) LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "EnemyFight");				
               	ChangeCharacterAddressGroup(sld, "Temple", "goto",  "goto"+i);		
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            //LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Ascold_WinNearTemple");
        break;

        case "Ascold_WinNearTemple":
            chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location, "reload2", false);            
            AddQuestRecord("Ascold", "14");
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1 = "location";
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1.location = "Temple_Inside";
			pchar.quest.Ascold_fightInsideTemple.function = "Ascold_fightInsideTemple";	
        break;
        
        case "Ascold_InGraveAfterFight":
			pchar.questTemp.Ascold = "Ascold_MummyIsLive";
		    LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], true); 
			sld = GetCharacter(NPC_GenerateCharacter("LeifEricson", "Mummy", "skeleton", "skeleton", 100, PIRATE, -1, true));	
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade28", "", 3000);
			sld.name = "����";
			sld.lastname = "�������";
			sld.Dialog.Filename = "Quest\LeifEricson.c";
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
			GiveItem2Character(sld, "Azzy_bottle");
            sld.DontClearDead = true; // �� ������� ���� ����� 200�
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "locator1");
			LAi_SetImmortal(sld, true);
			LAi_CharacterPlaySound(sld, "Gr_LeifEricson");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("LeifEricson", "", -1, 0.0);
		    LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
        break;

        case "Ascold_MummyFightTown":
            for (i=1; i<=6; i++)
            {
				sld = characterFromId("MySkel"+i);	
				sld.LifeDay = 0;
				ChangeCharacterAddress(sld, "none", "");
            }
    	    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
    	    DeleteQuestAttribute("Union_with_Escadra");
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            SetLocationCapturedState("BasTer_town", true);
            DoQuestCheckDelay("Capture_Forts", 0.5);
            Ship_NationAgressive(sld, sld);
            Log_SetStringToLog("�� ���� ���� � �c������� ���� ������������ �� ���� �������!");
			characters[GetCharacterIndex("BasTer_Mayor")].dialog.captureNode = "Ascold_MummyAttack"; //�������������� ���� ����
        break;

        case "Ascold_AzzyIsFree":
  		    LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Azzy")], "Shore28", "goto", "goto25");
            DoReloadCharacterToLocation("Shore28","goto","goto24");
            DoQuestCheckDelay("Azzy_IsFree", 4.0);
        break;

        case "Azzy_IsFree":
            LAi_SetActorType(PChar);
            sld = characterFromID("Azzy");
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Azzy_PlusSkill":
            DeleteAttribute(pchar, "questTemp.Azzy.AddSpecial");
            // boal ����������� ������ -->
            DelBakSkillAttr(pchar);
            ClearCharacterExpRate(pchar);
            RefreshCharacterSkillExpRate(pchar);
            // boal ����������� ������ <--
        	WaitDate("",0,0,2,0,1);
        	RecalculateJumpTable();
        	StoreDayUpdate();
			SetLaunchFrameFormParam("� ������...", "", 0, 4);
			LaunchFrameForm();
            //DoReloadCharacterToLocation("Tortuga_town", "reload", "reload91");
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ����� ��������-���� �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� �������     ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "PiratesLine_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			FreeSitLocator("PuertoPrincipe_tavern", "sit2");
			DoQuestReloadToLocation("PuertoPrincipe_tavern", "sit", "sit2", "");			
			sld = characterFromID("QuestPirate1");        
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);		
		break;

		case "PiratesLine_q1_MorganGoTo":
            sld = characterFromID("Henry Morgan");
			sld.Dialog.CurrentNode = "PL_Q1_1";
            LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		case "PQ5_Morgan_2":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Henry Morgan"));
			sld = characterFromID("CapGoodly"); 
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "PQ5_Morgan_3", -1.0);
		break;

		case "PQ5_Morgan_3":
			SetMainCharacterIndex(GetCharacterIndex("CapGoodly"));
			PChar   = GetMainCharacter();			
			locCameraToPos(2.49, 2.65, -11.076, false);
			LAi_SetActorType(PChar);
			LAi_ActorDialog(PChar, characterFromID("Henry Morgan"), "", 0, 0);
		break;

		case "PQ6_afterBattle":
			//������� ����� �����
			chrDisableReloadToLocation = false;
			group_DeleteGroup("LidsGroup");
			LocatorReloadEnterDisable("Shore7", "boat", false); //������� ����� � ����
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "4");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("��������� ������ '�������������', ����� �� ��� �� ���� ����� ������. ��� ��, ������, ��� ���������","���������� ���� '���������', ������ ��� ���� �� ���� ����� ������. ��� ���, ������, ��� ����������"));
			QuestSetCurrentNode("Jackman", "PL_Q6_after");
		break;
		

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  ��������� �������     �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "CitizSeekCap_afterCabinFight":
		    //#20191003-01
            LAi_group_SetAlarm(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, 0.0);
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.WifeCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, pchar.GenQuest.CitizSeekCap.nation, -1, false));
			sld.name = pchar.GenQuest.CitizSeekCap.WifeName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.WifeLastname;
			sld.dialog.filename   = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = pchar.GenQuest.CitizSeekCap.label + "_Board";
			sld.quest.SeekCap = pchar.GenQuest.CitizSeekCap.label;
			sld.quest.cribCity = pchar.GenQuest.CitizSeekCap.WifeCity;
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "PQ8_jungle_afterFight":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "Panama_inJungleIsOver";
			iTemp = GetCharacterIndex("Richard_Soukins");
			if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
				for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSpirate_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSmush_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i=1; i<=3; i++)
				{
					iTemp = GetCharacterIndex("RSofficer_"+i);
					if(iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
			}
		break;

		case "PQ8_ExitTown_afterFight":
			LocatorReloadEnterDisable("Shore48", "boat", false); //������� ����� �� �����
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false); //��������� ������� � ������
			SetLocationCapturedState("Panama_town", true); //������� ���� �� ������
			sld = characterFromId("Henry Morgan");
			sld.dialog.currentNode = "PL_Q8_ExTPanama";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "NarvalDestroyed":
			chrDisableReloadToLocation = false;
			pchar.questTemp.LSC = "NarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "13");
			int idxMent;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					characters[idxMent].Dialog.CurrentNode = "AffterFightN";
					LAi_SetWarriorType(&characters[idxMent]);
					LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER_OWN);
				}
			}
			pchar.quest.NavalExitVelasco.win_condition.l1 = "ExitFromLocation";
			pchar.quest.NavalExitVelasco.win_condition.l1.location = pchar.location;
			pchar.quest.NavalExitVelasco.function = "NavalExitVelasco";
		break;

		case "LSC_EnterComplite_1":			
			sld = characterFromId("LSCMayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay1");
			LAi_SetStayType(sld);
			sld = characterFromId("Casper_head");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{				
 				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar   = GetMainCharacter();			
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_EnterComplite_2":			
			sld = characterFromId("Casper_head");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay2");
			LAi_SetStayType(sld);
			sld = characterFromId("LSCMayor");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{			
 				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar   = GetMainCharacter();			
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_SesilAfraid":	
			sld = characterFromID("SesilGalard");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, false);
		break;

		case "LSC_SesilAfterFight":
			chrDisableReloadToLocation = false;			
			iTemp = GetCharacterIndex("SesilGalard");
			if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				while (FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE) != "")
				{
					TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
				}
				sld.dialog.currentnode = "First time";
				sld.greeting = "Enc_RapersGirl_2";
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TmpEnemy");
				LAi_ActorWaitDialog(sld, pchar);
				AddQuestRecord("ISS_MainLine", "28");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","��"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","�"));
				pchar.questTemp.LSC = "toKnowAboutMechanic";
				AddSimpleRumourCityTip("�� �������, ���� ��������� ��������� �� ����� ������!", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("�������, ��� �� ������ ����� ������, ����� �� �� ������.", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("�� ����� ������ ������ � �� �� ����, �� ������� '���'!", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("������, ��� �� ������ ������ �����! ���� ������� �������, ���������...", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("�-��, ���� ��� ������ ������, �� ��� �������� ���������� �� �������� � ���� � �����, ��� ��� ������� ����� ������.", "LostShipsCity", 10, 1, "LSC", "");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "29");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","��"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","�"));
				pchar.questTemp.LSC = "SessilIsDead";
				AddSimpleRumourCityTip("�� �������, ����� ������ ����� � � �� ����!", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("�������, ��� �� �� ������ �������� ������ ����� ������...", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("�-��, ��������� ������ ������� � ���������. ������, ��� ������ �� ��������� � ������, �������� ������� ���� �� ������. ������ ��� � ����� ������...", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("����, ��� ��� �� ������� ������ �����. ��� ���� ����� ������� ���������...", "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip("��������� ��������. ������, ���, ����� ������ ������. � ���� ��� ���� ��������� ������� ������...", "LostShipsCity", 10, 1, "LSC", "");
			}
		break;

		case "LSC_casperIsGone":			
			sld = &characters[sti(pchar.questTemp.LSC.Armo.casperIdx)];
			LAi_ActorTurnByLocator(sld, "quest", "target");
			sld.checkChrDistance = 5; //��������� ��������� �� ����������
			sld.checkChrDistance.id = "Blaze"; //Id ����������
			sld.checkChrDistance.time = 0; //����� ��������� ��������
			sld.checkChrDistance.node = sld.id; //���� �������
		break;

		case "LSC_PrisonerAfterFight":		
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			if (!LAi_IsDead(&characters[iTemp]))
			{
				LAi_SetFightMode(pchar, false);
				characters[iTemp].dialog.currentnode = "AfterFightCasper";
				LAi_SetActorTypeNoGroup(&characters[iTemp]);
				LAi_ActorDialog(&characters[iTemp], pchar, "", -1.0, 0);
			}
		break;

		case "LSC_PedroOpenedDoor":		
			sld = characterFromId("PedroHurtado");
            LAi_ActorTurnToLocator(sld, "goto", "goto04_5");
            LAi_ActorAnimation(sld, "Barman_idle", "LSC_EndOpenDoor", 1.5);
            DoQuestFunctionDelay("LSC_Click", 1.0);
		break;

		case "LSC_EndOpenDoor":		
			sld = characterFromId("PedroHurtado");
			sld.dialog.currentNode = "StStart_Opened";
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Teno_youWinFight":
			pchar.questTemp.Teno = "YouWinGod"; //���� ����� ������� ����
			LAi_SetFightMode(pchar, false);
			iTemp = GetCharacterIndex("AztecCitizen_1");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec1AF";
			iTemp = GetCharacterIndex("AztecCitizen_2");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec2AF";
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", true);
			sld = characterFromId("Montesuma");
			sld.lastname = "II";
			sld.dialog.currentnode = "AfterGTemple";
			DeleteAttribute(sld, "reactionOnFightModeOn"); 
			DeleteAttribute(sld, "BreakTmplAndFight"); 
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "teleport", "fire1");
			pchar.quest.Teno_exitFromTeno.win_condition.l1 = "locator";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator_group = "teleport";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator = "fire1";
			pchar.quest.Teno_exitFromTeno.function = "Teno_exitFromTeno";
			sld = characterFromId("DeadmansGod");
			sld.dialog.currentnode = "WinInTemple";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Teno_MontesumaArrived":
			sld = characterFromId("Montesuma");
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_warrior_SetStay(sld, true);
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  homo  ������� �����     ������
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//case "CureLord":
        //    CureLord();
		//break;
		
		case "CureLordMovie_Con1":
            CureLordMovie_Con1();
		break;
		
		case "CureLordMovie_Con2":
            CureLordMovie_Con2();
		break;
		
		case "CureLordMovie_Con3":
            CureLordMovie_Con3();
		break;
		
		case "CapBloodLineInit":
            CapBloodLineInit("");
		break;
		
		case "CapBlood_CheckMinHP":
            LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            InterfaceStates.Buttons.Save.enable = false;
            InterfaceStates.Launched = true;
            LAi_SetFightMode(pchar, false);
            DoQuestFunctionDelay("Blood_StartGame_End", 1.5);
            //CapBloodLineInit();
		break;
		
		case "Whisper_PC_CheckHP":
            LAi_group_SetRelation("wl_Pirate", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
            InterfaceStates.Buttons.Save.enable = false;
            LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			Pchar.model="PGG_Whisper_0_NoHat";
			DoQuestFunctionDelay("WhisperHold", 0.5);
		break;
		
		case "WhisperLine_IncqGuard_bad_speaks":			
			sld = characterFromId(pchar.Whisper.IncqGuard_bad);
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;
		
		
		case "PGG_CheckHP":
		if (CheckAttribute(pchar, "PGG_FightOnShore"))
            {
				sld = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
				LAi_SetImmortal(sld, true);
				PChar.Quest.PGGQuest1_PGGDead.PGG_Dead = "yes";
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", 10.0);
			}
		break;
		
		case "PGG_CheckHPDuel":
			sld = CharacterFromID(PChar.questTemp.duel.enemy);
			DoQuestCheckDelay("hide_weapon", 1.0);
			sld.Dialog.CurrentNode = "Duel_Won";
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				DeleteAttribute(pchar, "questTemp.LocationClone");
			}
			if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
			{
				sld = &Locations[FindLocation(pchar.location)];
				LAi_LocationFightDisable(sld, true);
				DeleteAttribute(pchar, "questTemp.LocFightEnable");
			}
		break;
		
		case "Sharp_Prologue_CheckHP":
			LAi_group_SetRelation("SharpSibling", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			sld = CharacterFromID("Sharp_Sibling");
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;

		case "Dragun_0_CheckMinHP":
            for (i=0; i<=2; i++)
            {
                sld = characterFromID("Dragun_"+i);
                if (i == 0)
                {
                    LAi_RemoveCheckMinHP(sld);
                    LAi_KillCharacter(sld);
                }
                else
                {
                    string sQuest = "CapGobartAttack_"+i;
                    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
                    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
                    pchar.quest.(sQuest).function= "CapGobartAttack";
                    LAi_SetImmortal(sld, false);
                    LAi_SetWarriorTypeNoGroup(sld);//fix
                    LAi_warrior_DialogEnable(sld, false);//fix
                    LAi_group_MoveCharacter(sld, "TmpEnemy");
                }
            }
            //LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
		break;
		
		case "BishopOnHouse":
            sld = characterFromID("Bishop");
            sld.talker = 10;
            LAi_SetCitizenType(sld);
            LAi_SetOwnerTypeNoGroup(sld);
       	    //LAi_SetStayTypeNoGroup(sld);

        break;
        
        case "NettlOnTavern":
            sld = characterFromID("Nettl");
   	        LAi_SetSitTypeNoGroup(sld);
   	        //sld.dialog.currentnode = "NStep_1";
            ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit8");

        break;
        
        case "SaveArabelaServiceAfraid":
        
            ref chr;
            chr = characterFromID("ArabelaService");
            sld = characterFromID("SpaRaider");
            LAi_ActorAfraid(chr, sld, true);
            LAi_SetPatrolTypeNoGroup(sld);
            //sld.talker = 10;
            //LAi_ActorDialog(sld, pchar, "",  3.0, 0);

        break;
        
        case "ShipGuardsDie":
            ShipGuardsDie();
        break;

        case "move_slave_2":
			//Boyer fix to minimize daily iterations
			SaveCurrentQuestDateParam("PGG_DailyUpdate");
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1          = "location";
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1.location = "Plantation_S1";
			pchar.quest.CapBloodLine_firstEnterHome.function      = "CapBloodLine_firstEnterHome"; 
			StartPictureAsVideo("Loading\finalbad2.tga", 1);
			DoReloadCharacterToLocation("Plantation_S1", "goto", "goto1");
			LAi_FadeEndFadeOut();
			InterfaceStates.Buttons.Save.enable = true;
        break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "ColonyBuilding":
			SetQuestHeader("ColonyBuilding");
			AddQuestRecord("ColonyBuilding", "1");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ColonyBuilding", "sSex1", GetSexPhrase("��","���"));
			string sArchitecorName = Characters[GetCharacterIndex("Builder")].name + " " + Characters[GetCharacterIndex("Builder")].lastname;
			AddQuestUserData("ColonyBuilding", "sArchitecorName", sArchitecorName);
			
			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = true;
			
			PChar.ColonyBuilding.Stage.FirstStage = "0";
			PChar.ColonyBuilding.Action = true;
			
			PChar.quest.ColonyBuildingTerks_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingTerks_1.win_condition.l1.location = "Shore57";
			PChar.quest.ColonyBuildingTerks_1.win_condition = "ColonyBuildingTerks_1";
			PChar.quest.ColonyBuildingDominica_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingDominica_1.win_condition.l1.location = "Shore27";
			PChar.quest.ColonyBuildingDominica_1.win_condition = "ColonyBuildingDominica_1";
			PChar.quest.ColonyBuildingCayman_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuildingCayman_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyBuildingCayman_1.win_condition = "ColonyBuildingCayman_1";
			
			PChar.quest.ColonyBuilding_6.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_6.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_6.win_condition = "ColonyBuilding_6";
			
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			SetCharacterRemovable(&Characters[GetCharacterIndex("Builder")], false);
			AddPassenger(PChar, &Characters[GetCharacterIndex("Builder")], 0);
		break;
		
		case "ColonyBuildingTerks":
			AddQuestRecord("ColonyBuilding", "2");
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_8";
			LAi_SetStayType(CharacterFromID("Builder"));
			PChar.quest.ColonyBuilding_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_5.win_condition = "ColonyBuilding_4";
		break;
		
		case "ColonyBuildingDominica":
			AddQuestRecord("ColonyBuilding", "11");
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_8";
			LAi_SetStayType(&Characters[GetCharacterIndex("Builder")]);
			PChar.quest.ColonyBuilding_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_5.win_condition = "ColonyBuilding_4";
		break;
		
		case "ColonyBuildingTerks_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore57", "goto", "goto2");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_Terks";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
		break;
		
		case "ColonyBuildingDominica_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore27", "encdetector", "enc01");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_Dominica";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
		break;
		
		case "ColonyBuildingCayman_1":
			StartQuestMovie(true, false, true);
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Shore17", "goto", "goto13");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_2";
			LAi_SetActorType(&Characters[GetCharacterIndex("Builder")]);
			LAi_ActorDialog(&Characters[GetCharacterIndex("Builder")], PChar, "", 20.0, 1.0);
			AddQuestRecord("ColonyBuilding", "3");
		break;
	
		case "ColonyBuildingCayman":
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			AddQuestRecord("ColonyBuilding", "4");
			PChar.ColonyBuilding.Stage.FirstStage = "1";
			PChar.quest.ColonyBuildingDominica_1.over = "yes";
			PChar.quest.ColonyBuildingTerks_1.over = "yes";
			
			PChar.BuildingColony.Blocks = 500;
			PChar.BuildingColony.Planks = 1000;
			PChar.BuildingColony.Mahogany = 500;
			PChar.BuildingColony.Ebony = 250;
			PChar.BuildingColony.Slaves = 200;
			PChar.BuildingColony.Food = 400;
			
			LAi_SetStayType(&Characters[GetCharacterIndex("Builder")]);
			//LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER_OWN);
			RemovePassenger(PChar, &Characters[GetCharacterIndex("Builder")]);
		break;
	
		case "ColonyBuildingCayman_2":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;
	
		case "ColonyBuilding_1":
			AddQuestRecord("ColonyBuilding", "5");
			PChar.ColonyBuilding.Stage.FirstStage = "2";
			int iColonyBuildingTime = sti(PChar.BuildingColony.ColonyTime);
            		SetTimerCondition("ColonyBuilding_2", 0, 0, iColonyBuildingTime, false);
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore17";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;
	
		case "ColonyBuilding_2":
			CreateSmallColonyCaiman();
			
			PChar.ColonyBuilding.Stage.FirstStage = "3";
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyBuilding_7";
			PlayStereoSound("notebook");
			Log_SetStringToLog("����� ������������� ������� �� ������� ������ ������ ������� � �����. ����� ��������� ����� ������.");
			
			PChar.quest.ColonyBuilding_2_1.win_condition.l1 = "location";
			PChar.quest.ColonyBuilding_2_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyBuilding_2_1.win_condition = "ColonyBuilding_2_1";
		break;
	
		case "ColonyBuilding_2_1":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 15.0, 1.0);
		break;
	
		case "ColonyBuilding_3":
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = true;
			bDisableQuestInterface = true;
			
			AddQuestRecord("ColonyBuilding", "6");
			PChar.ColonyBuilding.Stage.FirstStage = "end";
			PChar.ColonyBuilding.Action = false;
			
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			
			PChar.quest.ColonyBuilding_4.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyBuilding_4.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyBuilding_4.win_condition = "ColonyBuilding_4";
			
			PChar.ColonyBuilding.SlavesInShore.CurShore = "none";
			DeleteAllFantomCharactersFromLocation(&Locations[FindLocation(PChar.location)]);
			
			LAi_SetActorType(PChar);
            		DoQuestCheckDelay("ColonyBuilding_EnterName", 2.5);
            		
		break;
		
		case "ColonyBuilding_EnterName":
			PChar.ColonyBuilding.FirstBuild = true;
			LaunchColonyBuilding(true, false);
			
			bDisableCharacterMenu = false;
			bDisableQuestInterface = false;
			LAi_SetPlayerType(PChar);
		break;
		
		case "ColonyBuilding_4":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
			ChangeCharacterAddressGroup(&Characters[GetCharacterIndex("Builder")], "Caiman_town", "goto", "goto5");
			LAi_SetCitizenType(&Characters[GetCharacterIndex("Builder")]);
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
		break;
		
		case "ColonyBuilding_5":
			ChangeCharacterAddress(&Characters[GetCharacterIndex("Builder")], "None", "");
		break;
		
		case "ColonyBuilding_6":
			LAi_SetCitizenType(&Characters[GetCharacterIndex("Builder")]);
			ChangeCharacterAddress(&Characters[GetCharacterIndex("Builder")], "None", "");
		break;
		
// Colony Modification
		case "ColonyModification":
			AddQuestRecord("ColonyBuilding", "7");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ColonyBuilding", "sColonyName", PChar.ColonyBuilding.ColonyName);
			
			PChar.ColonyBuilding.Stage.SecondStage = "0";
			PChar.ColonyBuilding.Action = true;
			
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorGoToLocation(CharacterFromID("Builder"), "reload", "reload1", "none", "", "", "", -1);
	
			PChar.quest.ColonyModification_1.win_condition.l1 = "location";
			PChar.quest.ColonyModification_1.win_condition.l1.location = "Shore17";
			PChar.quest.ColonyModification_1.win_condition = "ColonyModification_1";
		break;
	
		case "ColonyModification_1":
			PChar.ColonyBuilding.Stage.SecondStage = "1";
			PChar.BuildingColony.Blocks = 1000;
			PChar.BuildingColony.Planks = 2000;
			PChar.BuildingColony.Mahogany = 750;
			PChar.BuildingColony.Ebony = 500;
			PChar.BuildingColony.Slaves = 600;
			PChar.BuildingColony.Food = 1500;
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Shore17", "goto", "goto13");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_1";
		break;
	
		case "ColonyModification_1_1":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_3";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;
	
		case "ColonyModification_2":
			AddQuestRecord("ColonyBuilding", "9");
			PChar.ColonyBuilding.Stage.SecondStage = "2";
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			int iColonyModificationTime = sti(PChar.BuildingColony.ColonyModification);
            		SetTimerCondition("ColonyModification_3", 0, 0, iColonyModificationTime, false);
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore17";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;
	
		case "ColonyModification_3":
			PChar.ColonyBuilding.Stage.SecondStage = "3";
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_4";
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_town", "goto", "goto8");
			PlayStereoSound("notebook");
			Log_SetStringToLog("����� ���������� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' ������ ������� � �����.");
			
			CreateModificyColonyCaiman();
			
			int idxLoadLoc = FindLoadedLocation();
            if (idxLoadLoc != -1)
            {
				if (locations[idxLoadLoc].islandId == "Caiman")
				{					
					DoQuestReloadToLocation("Caiman_town","reload","reload1", "");
					setCharacterShipLocation(pchar, "Caiman_town");
					setWDMPointXZ("Caiman_town");
				}
			}
			
			PChar.ColonyBuilding.SlavesInShore.CurShore = "none";
			PChar.quest.ColonyModification_6.win_condition.l1 = "location";
			PChar.quest.ColonyModification_6.win_condition.l1.location = "Caiman_town";
			PChar.quest.ColonyModification_6.win_condition = "ColonyModification_6";
		break;
	
		case "ColonyModification_4":
			EndQuestMovie();
			AddQuestRecord("ColonyBuilding", "10");
			AddQuestUserData("ColonyBuilding", "sColonyName", PChar.ColonyBuilding.ColonyName);
			PChar.ColonyBuilding.Stage.SecondStage = "end";
			PChar.ColonyBuilding.Action = false;

			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "ColonyModification_5":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
		break;
		
		case "ColonyModification_6":
			chrDisableReloadToLocation = true;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 25.0, 1.0);
		break;
		
		case "ColonyModification_7":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyModification_2";
			LAi_SetActorType(PChar);
			LAi_ActorWaitDialog(PChar, CharacterFromID("Builder"));
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;
		
// Set Hovernor
		case "SetHovernorToColonyResidence":
			LAi_SetHuberType(CharacterFromID(PChar.ColonyBuilding.Hovernor));
		break;
		
// Colony Fort Building
		case "ColonyFortBuilding_1":
			AddQuestRecord("ColonyBuilding", "12");
			PChar.quest.ColonyFortBuilding_2.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyFortBuilding_2.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyFortBuilding_2.win_condition = "ColonyFortBuilding_2";
			PChar.quest.ColonyFortBuilding_3.win_condition.l1 = "location";
			PChar.quest.ColonyFortBuilding_3.win_condition.l1.location = "Shore16";
			PChar.quest.ColonyFortBuilding_3.win_condition = "ColonyFortBuilding_3";
			
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorRunToLocation(CharacterFromID("Builder"), "reload", "gate_back", "none", "", "", "", -1);
		break;

		case "ColonyFortBuilding_1_1":
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_4";
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;
	
		case "ColonyFortBuilding_2":
			ChangeCharacterAddress(CharacterFromID("Builder"), "None", "");
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "First time";
		break;

		case "ColonyFortBuilding_3":
			PChar.BuildingColony.Blocks = 2500;
			PChar.BuildingColony.Planks = 1500;
			PChar.BuildingColony.Mahogany = 300;
			PChar.BuildingColony.Ebony = 200;
			PChar.BuildingColony.Slaves = 500;
			PChar.BuildingColony.Food = 1000;
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_3";
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Shore16", "goto", "goto8");
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
		break;

		case "ColonyFortBuilding_4":
			AddQuestRecord("ColonyBuilding", "13");
		break;

		case "ColonyFortBuilding_5":
			AddQuestRecord("ColonyBuilding", "14");
			
			LAi_SetCitizenType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			
			int iColonyFortTime = sti(PChar.BuildingColony.ColonyFort);
            		SetTimerCondition("ColonyFortBuilding_6", 0, 0, iColonyFortTime, false);
            		
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "Shore16";
			CreateCaimanShoreSlaves(&Locations[FindLocation(PChar.location)]);
		break;
		
		case "ColonyFortBuilding_6":
			PlayStereoSound("notebook");
			Log_SetStringToLog("����� ������������� �������� ���� ���� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' ������ ������� � �����.");
			CreateFortInCaiman();
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "LandGuardingPort", "goto", "goto1");
			LAi_SetStayType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], LAI_GROUP_PLAYER);
			Characters[GetCharacterIndex("Builder")].Dialog.CurrentNode = "ColonyFortBuilding_6";
			PChar.ColonyBuilding.Stage = "3";
			
			PChar.ColonyBuilding.SlavesInShore.CurShore = "LandGuardingPort";
			PChar.quest.ColonyFortBuilding_6_1.win_condition.l1 = "location";
			PChar.quest.ColonyFortBuilding_6_1.win_condition.l1.location = "LandGuardingPort";
			PChar.quest.ColonyFortBuilding_6_1.win_condition = "ColonyFortBuilding_6_1";
		break;

		case "ColonyFortBuilding_6_1":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorDialog(CharacterFromID("Builder"), PChar, "", 5.0, 1.0);
		break;

		case "ColonyFortBuilding_7":
			chrDisableReloadToLocation = false;
			AddQuestRecord("ColonyBuilding", "15");
			CloseQuestHeader("ColonyBuilding");
			
			LAi_Fade("", "");
			PChar.ColonyBuilding.SlavesInShore.CurShore = "None";
			DeleteAllFantomCharactersFromLocation(&Locations[FindLocation(PChar.location)]);
			
			LAi_SetActorType(CharacterFromID("Builder"));
			LAi_ActorRunToLocation(CharacterFromID("Builder"), "reload", "reload1_back", "none", "", "", "", -1);
			
			PChar.quest.ColonyFortBuilding_8.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyFortBuilding_8.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyFortBuilding_8.win_condition = "ColonyFortBuilding_8";
		break;

		case "ColonyFortBuilding_8":
			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Builder"), "BuilderHouse", "sit", "sit1");
			LAi_SetHuberType(CharacterFromID("Builder"));
			LAi_group_MoveCharacter(&Characters[GetCharacterIndex("Builder")], "ENGLAND_CITIZENS");
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� ������ � ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "Store_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Store_build_1", 0, 0, iBuild, false);
		break;
		
		case "Store_build_1":
			Log_SetStringToLog("������� ������.");
			ChangeColonyMorale(5, false);
			PChar.ColonyBuilding.Store.BuildingTime = false;
			PChar.ColonyBuilding.Store = true;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_trader"), "Caiman_store", "barmen", "stay");
			Locations[FindLocation("Caiman_town")].reload.l6.disable = false; 
			
		break;
		
		case "Shipyard_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Shipyard_build_1", 0, 0, iBuild, false);
		break;
		
		case "Shipyard_build_1":
			Log_SetStringToLog("����� �������.");
			ChangeColonyMorale(5, false);
			PChar.ColonyBuilding.Shipyard.BuildingTime = false;
			PChar.ColonyBuilding.Shipyard = true;
			Locations[FindLocation("Caiman_town")].reload.l5.disable = false; 
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_shipyarder"), "Caiman_shipyard", "sit", "sit1");
		break;
		
		case "Tavern_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Tavern_build_1", 0, 0, iBuild, false);
		break;
		
		case "Tavern_build_1":
			Log_SetStringToLog("������� �������.");
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.Tavern.BuildingTime = false;
			PChar.ColonyBuilding.Tavern = true;
			Locations[FindLocation("Caiman_town")].reload.l4.disable = false; 
			Locations[FindLocation("Caiman_town")].reload.l41.disable = false; 
			Locations[FindLocation("Caiman_tavern")].habitues = 1; 
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_tavernkeeper"), "Caiman_Tavern", "barmen", "stay");
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_waitress"), "Caiman_Tavern", "waitress", "barmen");
		break;
		
		case "Church_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Church_build_1", 0, 0, iBuild, false);
		break;
		
		case "Church_build_1":
			Log_SetStringToLog("������� �������.");
			ChangeColonyMorale(20, false);
			PChar.ColonyBuilding.Church.BuildingTime = false;
			PChar.ColonyBuilding.Church = true;
			Locations[FindLocation("Caiman_town")].reload.l7.disable = false;
			Locations[FindLocation("Caiman_town")].reload.l71.disable = false; 
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_Priest"), "Caiman_church", "barmen", "stay");
		break;
		
		case "Bank_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("Bank_build_1", 0, 0, iBuild, false);
		break;
		
		case "Bank_build_1":
			Log_SetStringToLog("��� ���������� ������.");
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.Bank.BuildingTime = false;
			PChar.ColonyBuilding.Bank = true;
			Locations[FindLocation("Caiman_town")].reload.l8.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_usurer"), "Caiman_bank", "barmen", "stay");
		break;
		
		case "HeadPort_build":
			iBuild = rand(2) + 1;
            		SetTimerCondition("HeadPort_build_1", 0, 0, iBuild, false);
		break;
		
		case "HeadPort_build_1":
			Log_SetStringToLog("�������� ���������� �������.");
			ChangeColonyMorale(10, false);
			PChar.ColonyBuilding.HeadPort.BuildingTime = false;
			PChar.ColonyBuilding.HeadPort = true;
			Locations[FindLocation("Caiman_town")].reload.l10.disable = false;
			ChangeCharacterAddressGroup(CharacterFromID("Caiman_PortMan"), "Caiman_PortOffice", "sit", "sit1");
		break;
		
		case "Expidition_build":
			iBuild = rand(3) + 2;
            		SetTimerCondition("Expidition_build_1", 0, 0, iBuild, false);
		break;
		
		case "Expidition_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Expidition_End";
			}
			
			Log_SetStringToLog("���������� ���������.");
			PChar.ColonyBuilding.Expidition.BuildingTime = false;
			PChar.ColonyBuilding.Expidition = true;
		break;
		
		case "Plantation_build":
			iBuild = rand(5) + 20;
            		SetTimerCondition("Plantation_build_1", 0, 0, iBuild, false);
		break;
		
		case "Plantation_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Plantation_End";
			}
			CreatePlantationInCaiman();
			
			Log_SetStringToLog("��������� ���������.");
			PChar.ColonyBuilding.Plantation.BuildingTime = false;
		break;
		
		case "Plantation_resize":
			iBuild = rand(5) + 10;
            		SetTimerCondition("Plantation_resize_1", 0, 0, iBuild, false);
		break;
		
		case "Plantation_resize_1":
			Log_SetStringToLog("��������� ���������.");
			PChar.Plantation.Size.Resize.BuildingTime = false;
			PChar.ColonyBuilding.Plantation.Resize.BuildingTime = false;
			PChar.Plantation.Size = 2;
			PChar.Plantation.Slaves.MaxQuantity = 500;
			PChar.Plantation.Guardians.MaxQuantity = 500;
			PChar.Plantation.Food.MaxQuantity = 8000;
			PChar.Plantation.Medicament.MaxQuantity = 4500;
			PChar.Plantation.Items.MaxQuantity = 550;
			PChar.Plantation.Sugar.MaxQuantity = 10000;
		break;
		
		case "StoreHouse_build":
			iBuild = rand(2) + 2;
            		SetTimerCondition("StoreHouse_build_1", 0, 0, iBuild, false);
		break;
		
		case "StoreHouse_build_1":
			Log_SetStringToLog("����� ��������.");
			PChar.ColonyBuilding.StoreHouse.BuildingTime = false;
			PChar.ColonyBuilding.StoreHouse = true;
			
			if(PChar.ColonyBuilding.Stage == "1")
			{
				Locations[FindLocation("Caiman_town")].reload.l11.label = "Caiman Store House";
				Locations[FindLocation("Caiman_town")].reload.l11.disable = false;
				Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = "reload4";
			}
			else
			{
				Locations[FindLocation("Caiman_town")].reload.l11.label = "Caiman Store House";
				Locations[FindLocation("Caiman_town")].reload.l11.disable = false;
				Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = Locations[FindLocation("Caiman_town")].reload.l11.name;
				
				if(Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge == "")
				{
					Locations[FindLocation("Caiman_StoreHouse")].reload.l1.emerge = "houseS1";
				}
			}
		break;
		
		case "GoldMine_build":
			iBuild = rand(5) + 12;
            		SetTimerCondition("GoldMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "GoldMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}
			
			Log_SetStringToLog("������� ������ ��������.");
			PChar.Mines.GoldMine = true;
			PChar.ColonyBuilding.GoldMine = true;
			PChar.Mines.GoldMine.BuildingTime = false;
			PChar.ColonyBuilding.GoldMine.BuildingTime = false;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "SilverMine_build":
			iBuild = rand(5) + 10;
            		SetTimerCondition("SilverMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "SilverMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}
			
			Log_SetStringToLog("����������� ������ ��������.");
			PChar.Mines.SilverMine = true;
			PChar.Mines.SilverMine.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine = true;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "IronMine_build":
			iBuild = rand(5) + 5;
            		SetTimerCondition("IronMine_build_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "IronMine_build_1":
			if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1 && GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != nMainCharacterIndex && PChar.ColonyBuilding.MineMessage == false)
			{
				Characters[GetCharacterIndex(PChar.ColonyBuilding.Hovernor)].Dialog.CurrentNode = "ColonyBuilding_Mines_End";
			}
			Log_SetStringToLog("�������� ������ ��������.");
			PChar.Mines.IronMine = true;
			PChar.Mines.IronMine.BuildingTime = false;
			PChar.ColonyBuilding.IronMine.BuildingTime = false;
			PChar.ColonyBuilding.IronMine = true;
			CreateMinesInCaiman();
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "GoldMine_resize":
			iBuild = rand(2) + 7;
            		SetTimerCondition("GoldMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "GoldMine_resize_1":
			Log_SetStringToLog("������� ������ ��������.");
			PChar.ColonyBuilding.GoldMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.GoldMine.Resize = true;
			PChar.Mines.GoldQuantity.Max = 5000;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "SilverMine_resize":
			iBuild = rand(2) + 5;
            		SetTimerCondition("SilverMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "SilverMine_resize_1":
			Log_SetStringToLog("����������� ������ ��������.");
			PChar.ColonyBuilding.SilverMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.SilverMine.Resize = true;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.SilverQuantity.Max = 7500;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "IronMine_resize":
			iBuild = rand(2) + 3;
            		SetTimerCondition("IronMine_resize_1", 0, 0, iBuild, false);
            		PChar.Mines.Defence.Block = true;
		break;
		
		case "IronMine_resize_1":
			Log_SetStringToLog("�������� ������ ��������.");
			PChar.ColonyBuilding.IronMine.Resize.BuildingTime = false;
			PChar.ColonyBuilding.IronMine.Resize = true;
			PChar.Mines.FoodQuantity.Max = sti(PChar.Mines.FoodQuantity.Max) + 1000;
			PChar.Mines.MedicamentQuantity.Max = sti(PChar.Mines.MedicamentQuantity.Max) + 1000;
			PChar.Mines.IronQuantity.Max = 10000;
			PChar.Mines.MaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity) + 100;
			PChar.Mines.MaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity) + 100;
            		PChar.Mines.Defence.Block = false;
		break;
		
		case "StoreHouse_resize":
			iBuild = rand(3) + 2;
            		SetTimerCondition("StoreHouse_resize_1", 0, 0, iBuild, false);
		break;
		
		case "StoreHouse_resize_1":
			Log_SetStringToLog("����� ��������.");
			Stores[STORE_HOUSE].max_weight = sti(Stores[STORE_HOUSE].max_resize_weight);
			PChar.ColonyBuilding.StoreHouse.Resize.BuildingTime = false;
			PChar.ColonyBuilding.StoreHouse.Resize = true;
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� ������ � ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ����� � ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "SetCommanderToMinesOffice":
			LAi_SetStayType(CharacterFromID(PChar.Mines.Commander));
		break;

		/*
                        PChar.quest.LiveOfTheColonyUptade_1.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_2.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_3.over = "yes";
                        PChar.quest.LiveOfTheColonyUptade_4.over = "yes";
                */
                
		case "LiveOfTheColonyUptade_1":
			SetTimerCondition("LiveOfTheColonyUptade_2", 0, 0, 0, false);
		break;  
		
		case "LiveOfTheColonyUptade_2":
			SetTimerCondition("LiveOfTheColonyUptade_3", 0, 0, 7, false);
		break;  
		
		case "LiveOfTheColonyUptade_3":
			LiveOfTheColonyUptade();
			SetTimerCondition("LiveOfTheColonyUptade_4", 0, 0, 1, false);
		break;
		
		case "LiveOfTheColonyUptade_4":
			SetTimerCondition("LiveOfTheColonyUptade_3", 0, 0, 6, false);
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ����� � ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� �� ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "CheckDefenceColonyUptade_1":
			SetTimerCondition("CheckDefenceColonyUptade_2", 0, 0, 0, false);
		break;  
		
		case "CheckDefenceColonyUptade_2":
			SetTimerCondition("CheckDefenceColonyUptade_3", 0, 0, 40, false);
		break;  
		
		case "CheckDefenceColonyUptade_3":
			CheckDefenceColony();
			SetTimerCondition("CheckDefenceColonyUptade_4", 0, 0, 38, false);
		break;
		
		case "CheckDefenceColonyUptade_4":
			SetTimerCondition("CheckDefenceColonyUptade_3", 0, 0, 2, false);
		break;
		
		case "ClearMutinyColony":
			ClearMutinyColony("");
		break;
		
		case "ClearLandDefenceColony":
			ClearLandDefenceColony("");
		break;
		
		case "ColonyNotSetDead":
			PChar.ColonyBuilding.Defence.DeadInTown = false;
			
			if(CheckAttribute(&Locations[FindLocation("Caiman_town")], "hidden_effects"))
			{
				DeleteAttribute(&Locations[FindLocation("Caiman_town")], "hidden_effects");
			}
			if(CheckAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects"))
			{
				DeleteAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects");
			}
		break;
		
		case "MinesNotSetDead":
			PChar.Mines.Defence.DeadInTown = false;
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� �� ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "SetCommanderToPlantationOffice":
			LAi_SetStayType(CharacterFromID(PChar.Plantation.Commander));
		break;
		
		case "PlantationUptade1":
			SetTimerCondition("PlantationUptade2", 0, 0, 0, false);
		break;  
		
		case "PlantationUptade2":
			SetTimerCondition("PlantationUptade3", 0, 0, 14, false);
		break;  
		
		case "PlantationUptade3":
			UptadeLivedInPlantation();
			SetTimerCondition("PlantationUptade4", 0, 0, 1, false);
		break;
		
		case "PlantationUptade4":
			SetTimerCondition("PlantationUptade3", 0, 0, 13, false);
		break;

		case "PlantationUptade5":
			PChar.Plantation.Defence.Block = false;
			Log_TestInfo("������ �� ������ �� ��������� ����.");
		break;

		case "PlantationNotSetDead":
			PChar.Plantation.Defence.DeadInTown = false;
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ��������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "MinesUptade1":
			SetTimerCondition("MinesUptade2", 0, 0, 0, false);
		break;  
		
		case "MinesUptade2":
			SetTimerCondition("MinesUptade3", 0, 0, 14, false);
		break;  
		
		case "MinesUptade3":
			UptadeLivedInMines();
			SetTimerCondition("MinesUptade4", 0, 0, 1, false);
		break;
		
		case "MinesUptade4":
			SetTimerCondition("MinesUptade3", 0, 0, 13, false);
		break;

		case "MinesUptade5":
			PChar.Mines.Defence.Block = false;
			Log_TestInfo("������ �� ��������� �� ������� ����.");
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////
		// ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// �������� � ����� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
	        case "AcademyLand_Winner":
			AcademyLandTrainingEnd(true);
	        break;
	        
	        case "AcademyLand_Loose":
			AcademyLandTrainingEnd(false);
	        break;
	        
	        case "ArenaDuelCheckNewRound":
	        	ArenaDuelCheckNewRound();
	        break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// �������� � ����� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		//homo
		//-->������������
		case "Slavetrader_findTortugaRat"://������ ��������
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
			sld = GetCharacter(NPC_GenerateCharacter("Ratlover", "girl_8", "woman", "towngirl", 10, FRANCE, -1, false));
            ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "barmen",  "bar2");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_lover"; // ���������� ����
			sld.name 	= "�����";
			sld.lastname 	= "�������";            
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
			
            sld = GetCharacter(NPC_GenerateCharacter("SLBanditHead", "pirate_10", "man", "man", 25, PIRATE, 0, true));
            FantomMakeCoolFighter(sld, 45, 100, 100, "blade26", "pistol6", 80);
			sld.cirassId = Items_FindItemIdx("cirass5");
        	LAi_SetStayType(sld);
        	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_bandos";
            LAi_group_MoveCharacter(sld, "EnemyFight");
           	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto1");
            LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
       break;

       case "Slavetrader_findTortugaRat1"://������ ��������
            for (i=3; i<=5; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SVBandit"+i, "pirate_"+i, "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 35, 100, 100, "blade33", "pistol6", 80);
            	LAi_SetStayType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto"+i);
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat2");
       break;

       case "Slavetrader_findTortugaRat2":
            chrDisableReloadToLocation = false;
            LAi_SetActorType(pchar);
            sld = characterFromID("Ratlover");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
       break;
	   
	   case "Slavetrader_EscapeSlaves_Win":
            chrDisableReloadToLocation = false;
			sld = GetCharacter(NPC_GenerateCharacter("Slavewoman", "horse07", "woman", "towngirl", 10, PIRATE, -1, false));
            ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto31");
           	sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Slave_woman"; // ���������� ����
			sld.name 	= "������";
			sld.lastname 	= "";            
			LAi_SetImmortal(sld, true);
            LAi_SetStayTypeNoGroup(sld);
			LAi_SetActorType(pchar);
            sld = characterFromID("Slavewoman");
            LAi_SetActorType(sld);
            LAi_ActorTurnToCharacter(sld, pchar);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			
        break;
		//<--������������

		//���, ������ ������
		case "CarlosDie":
			if (CheckAttribute(PChar, "quest.CarlosPlace")) Pchar.quest.CarlosPlace.over = "yes";
			if (CheckAttribute(PChar, "quest.HeadhunterTimer")) Pchar.quest.HeadhunterTimer.over = "yes";
			DoQuestCheckDelay("hide_weapon", 1.0);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", false); //�������� �������
			locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = false; //��������� �������
			AddQuestRecord("Headhunt", "2");
			pchar.questTemp.Headhunter = "hunt_carlos_yes";
		break;
		
		//���, ������� �����
		case "RatHunters_Dead":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Headhunt", "28");
			pchar.questTemp.Headhunter = "halen_still";
		break;
		
		case "Headhunter_FightInPort":
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			iTemp = GetCharacterIndex("Halen");
			if (iTemp != -1)
			{			
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");			
				LAi_group_Attack(sld, Pchar);			
				SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
			}
		break;
		
		case "Headhunter_HalenOut":
			ChangeCharacterAddress(characterFromID("Halen"), "None", "");
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		break;
		
		case "FindJa":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Headhunt", "35");
		break;
		
		case "IndianInJungleClearGroup":
			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ���. ����� - ������� - ������
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "QuestDuelTalkWifeWithDuelist":
			QuestDuelTalkWifeWithDuelist();
		break; 
		
		case "QuestDuelTalkMainCharacterWithDuelist":
			QuestDuelTalkMainCharacterWithDuelist();
		break; 
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		// ���. ����� - ������� - �����
		////////////////////////////////////////////////////////////////////////////////////////////////
		
// --> ����� �����-�����
		case "LSC_RingTalkLook": // ������� �� ������
			LAi_SetPlayerType(pchar);
			LSC_RingRishardTalk("ring_13");
        break;
		
		case "LSC_RingEnterInside": // ������ � ���� ��������� �������
			chrDisableReloadToLocation = true;//������� �������
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			// ������ ����������
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*30+sti(pchar.rank)*5;
			LAi_group_Register("EnemyCrab");
			for (i=1; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabInside_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.name = "���������� ����";
				sld.lastname = "";
				DeleteAttribute(sld, "items");
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "ExternalRingInside", "goto", "goto"+i);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 13.0);
			LAi_group_SetHearRadius("EnemyCrab", 5.0);
			LAi_group_SetSayRadius("EnemyCrab", 8.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingInsideCrabsDead");
			LAi_SetFightMode(pchar, true);
        break;
		
		case "LSC_RingInsideCrabsDead": // �������� ������
			PlayStereoOGG("music_LostShipsCity");
			LAi_group_Delete("EnemyCrab");
			sld = characterFromId("LSC_Rishard");
			ChangeCharacterAddressGroup(sld, "ExternalRingInside", "reload", "reload1");
			LSC_RingRishardTalk("ring_15");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "LSC_RingDialog": // ��������� ��������
			sld = characterFromId("LSC_Rishard");
			LSC_RingRishardTalk(sld.quest.diagnode);
        break;
		
		case "LSC_RingEnterDeck": // ������ �� ������ ��������� �������
			chrDisableReloadToLocation = true;//������� �������
			// ������ ����������
			iRank = 25+MOD_SKILL_ENEMY_RATE*2;
			iTemp = 150+MOD_SKILL_ENEMY_RATE*30+sti(pchar.rank)*5;
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabDeck_"+i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.name = "���������� ����";
				sld.lastname = "";
				DeleteAttribute(sld, "items");
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 15.0);
			LAi_group_SetHearRadius("EnemyCrab", 6.0);
			LAi_group_SetSayRadius("EnemyCrab", 12.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingDeckCrabsDead");
			LSC_RingRishardTalk("ring_22");
        break;
		
		case "LSC_RingDeckCrabsDead": // �������� ������
			PlayStereoOGG("music_LostShipsCity");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", true);
			LAi_group_Delete("EnemyCrab");
			LSC_RingRishardTalk("ring_24");
			AddComplexSelfExpToScill(150, 150, 150, 150);
        break;
		
		case "LSC_RingEnterCabin": // ����� � �����
			chrDisableReloadToLocation = true;
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_31";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "LSC_RingDialog", -1);
        break;
		
		case "LSC_RingSetToBarman": // 
			sld = characterFromId("LSC_Rishard");
			LAi_SetBarmanType(sld);
        break;
		
		case "LSC_RingFinalStage": // 
			sld = characterFromId("LSC_Rishard");
			sld.quest.ring_final = true;
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "", 7.0);
			DoQuestFunctionDelay("LSC_RingOver", 3.0); // ��������� �����
			SetFunctionTimerCondition("LSC_RingDeleteItemsBoxes", 0, 0, 2, false); // ����� 2 ��� ����� ��������
        break;
		
		case "LSC_RingFindGold": // ����� ������ 
			PlaySound("Ambient\LAND\door_001.wav");
			PlaySound("Ambient\LAND\door_004.wav");
			PlayVoice("Types\warrior03.wav");
			PlayVoice("Types\warrior04.wav");
			SetLaunchFrameFormParam("�� �������� ������ ����"+ NewStr() +"������ �������� '�����-�����' �������!", "", 0, 6);//��������
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //������ �����
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_46";
			DoQuestCheckDelay("LSC_RingDialog", 6.0);
        break;
		// <-- ����� �����-�����	
	// <-- ����� �����-�����
//������� ������ ������, ������� Lipsar//;
	case "Taverna":
		chrDisableReloadToLocation = true;
		pchar = GetMainCharacter();
		sld = characterFromID("Old Friend");
		DoQuestReloadToLocation("LaVega_tavern", "sit", "sit5", "");
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit6");
		sld.Dialog.CurrentNode = "StartQuest_4";
		LAi_SetSitType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, PChar, "", 1.5);
		chrDisableReloadToLocation = false;
	break;
	case "AfterDialog":
		pchar = GetMainCharacter();
		sld = characterFromID("Old Friend");
		Lai_SetPlayerType(PChar);
		LAi_SetSitType(sld);
		DoQuestReloadToLocation("LaVega_tavern", "tables", "stay4", "");
	break;
	case "GiveLetter":
		sld = characterFromID("Maks");
		pchar = GetMainCharacter();
		TakeItemFromCharacter(pchar, "Lukes_letter");
		PlaySound("Interface\important_item");
		LAi_SetStayType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, PChar, "", 1.5);
	break;
	case "Plata1":
		sld = characterFromID("Maks");
		pchar = GetMainCharacter();
		PlaySound("Interface\took_item");
		AddMoneyToCharacter(pchar, 10000);
		LAi_SetSitType(sld);
		Lai_SetPlayerType(pchar);
	break;
	case "ChangeLukesHome":
			sld = CharacterFromID("Old Friend");
			sld.City = RandomCityEnemy();
			Log_TestInfo(sld.City);
			ChangeCharacterAddressGroup(sld,RandomHouse(sld),"goto","goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar,"", 20.0,10.0)
			Pchar.Luke.City = sld.City;
			DeleteAttribute(Pchar,"Quest.Luke");
			AddQuestRecord("Silence_Price","4");
			AddQuestUserData("Silence_Price","sSex",GetSexPhrase("��","���"));
			Pchar.quest.GetSpawnPirate.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.GetSpawnPirate.win_condition.l1.location = Pchar.location;
			Pchar.quest.GetSpawnPirate.function = "GetSpawnPirate";
	break;
	case "PirateGoOut":
		sld = CharacterFromID("Anri");
		LAi_ActorRunToLocation(sld,"reload", "reload1","none","","","",20.0);
		AddQuestRecord("Silence_Price","5");
		chrDisableReloadToLocation = false;
		
		Pchar.quest.PirateComeToIsabella.win_condition.l1 = "Timer";
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		Pchar.quest.PirateComeToIsabella.function = "PirateComeToIsabella";

		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1 = "Timer";
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.hour = 3;
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		Pchar.quest.PirateComeToIsabellaLoose.function = "PirateComeToIsabellaLoose";
	break;
	case "PirateGoOut1":
		sld = CharacterFromID("Anri");
		LAi_ActorRunToLocation(sld,"reload", "reload1","none","","","",20.0);
		AddQuestRecord("Silence_Price", "5_3");
		AddQuestUserData("Silence_Price", "sCityName", XI_ConvertString("Colony" + Pchar.Luke.City + "Acc"));
		LAi_LocationDisableOfficersGen("Shore32", false);
		GiveItem2Character(pchar,"book2_7");
		GiveItem2Character(pchar,"book2_6");
		PlaySound("Interface\important_item.wav");
	break;
	case "PrepareFightAnri":
		sld = CharacterFromID("Anri");
		sTemp = "AnriChrist";
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, sTemp);
		LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
		LAi_SetFightMode(pchar, true);
		LAi_Group_SetCheck(sTemp, "AfterBatleAnri");
	break;
	case "AfterBatleAnri":
		AddQuestRecord("Silence_Price", "5_2");
		AddQuestUserData("Silence_Price", "sCityName", XI_ConvertString("Colony" + Pchar.Luke.City + "Acc"));
		LAi_LocationDisableOfficersGen("Shore32", false);
	break;
	case "LukeFight":
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Old Friend");
		sTemp = "Artist";
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, sTemp);
		GiveItem2Character(sld,"cirass5");
		EquipCharacterbyItem(sld,"cirass5");
		LAi_SetCheckMinHP(sld, 1, true, "QuestPreEnd");
		LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar,true);
	break;
	case "QuestPreEnd":
		sld = CharacterFromID("Old Friend");
		sld.Dialog.CurrentNode = "SecondQuest_4";
		LAi_SetFightMode(sld, false);
		LAi_SetFightMode(pchar, false);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, Pchar, "", 20.0, 1.0);
	break;
	case "LukeOut":
		sld = CharacterFromID("Old Friend");
		LAi_SetActorType(pchar);
		LAi_SetImmortal(sld, true);
		LaunchBlastGrenade(pchar);
		PlaySound("People Fight\rifle_fire1.wav");
		pchar.chr_ai.poison = 1 + 30 + 20 + 40;
		pchar.chr_ai.Blooding = 50;
		MarkCharacter(pchar,"FX_Blood");
		Log_Info("�� �������� ����������");
		Log_Info("� ��� �������� ������������");
		AddCharacterHealth(pchar, -20);
		StartLookAfterCharacter(sld.id);
		LAi_ActorRunToLocation(sld,"reload","reload1", "none", "", "", "", 2.0);
		DoQuestFunctionDelay("MaksCome", 2.0);
	break;
	case "AddGuardians":
	for (i = 0; i < 3; i++)
	{
		sTemp = "off_" + NationShortName(sti(Colonies[FindColony(Pchar.Luke.City)].nation)) + "_" + i;
		sld = GetCharacter(NPC_GenerateCharacter("Maks_Guard" + i, sTemp, "man", "man", 30, sti(Colonies[FindColony(Pchar.Luke.City)].nation), -1, false));
		SelAllPerksToNotPchar(sld);
		sld.dialog.filename = "Quest\SilencePrice\Maks.c";
		sld.Dialog.CurrentNode = "Guardians";
		LAi_group_MoveCharacter(sld, "Maks1");
		FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol5",300);
		ChangeCharacterAddressGroup(sld, Pchar.Luke.City.Loc, "reload", "reload1");
		GiveItem2Character(sld,"cirass3");
		EquipCharacterbyItem(sld,"cirass3");
		if(i < 2)
		{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", 20.0, 1.0);
		}
	}
	LAi_group_SetCheck("Maks1", "QuestEnd1");
	LAi_SetFightMode(pchar,false);
	sld = CharacterFromID("Maks");
	break;
	case "FightGuardians":
		LAi_group_FightGroups("Maks1", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar,true);
	break;
	case "QuestEnd1":
		chrDisableReloadToLocation = false;
		Pchar.quest.LukesEscape.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.LukesEscape.win_condition.l1.location = Pchar.Luke.City.Loc;
		Pchar.quest.LukesEscape.function = "LukesEscape";
	break;
	case "HealingPoison":
		SetLaunchFrameFormParam("������ ����� ������� ���������, � �� ���������� ���.", "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam("Bridgetown_church", "barmen","bar1", "");
		LaunchFrameForm();
		AddDataToCurrent(0, 1, 0);
		DeleteAttribute(PChar,"Luke.BadPoison");
		AddCharacterHealth(pchar, 50);
		AddQuestRecord("Silence_Price", "6_1");
	break;
		//����� ������� ������ ������
		//����� � ��������� ���������� Lipsar//
	case "SeekerFight":
		sld = CharacterFromID("SpySeeker");
		LAi_SetImmortal(sld, false);
		LAi_Group_MoveCharacter(sld, "SpySeeker");
		LAi_group_SetRelation("SpySeeker", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_Group_FightGroups(PLAYER_GROUP, "SpySeeker", true);
		LAi_SetFightMode(sld, true);
		LAi_SetFightMode(pchar, true);
		LAi_Group_SetCheck("SpySeeker","OpenTheDoors");
	break;
	case "SpySeekerGood":
		sld = CharacterFromID("SpySeeker");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5.0);
		chrDisableReloadToLocation = false;
	break;
	//����� � ��������� ���������� Lipsar//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////  	������ "��������� ������� �����" ������  	///	 		����� Sinistra				//////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================  ����� "��������".  =======================	
		case "PDM_Albreht_Saditsya_na_korabl":
			sld = CharacterFromID("Albreht_Zalpfer")   //��������� �� ���������
			AddPassenger(pchar, sld, false);    // �������� ���������
			SetCharacterRemovable(sld, true);   // ����� ������� �� ���������
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*10;
			sld.OfficerWantToGo.DontGo = true;
			sld.rank = 4;
			SetSelfSkill(sld, 5, 40, 5, 5, 5);
			SetShipSkill(sld, 5, 5, 5, 5, 5, 35, 5, 5, 5);
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
			GiveItem2Character(sld, "topor_05");
			EquipCharacterByItem(sld, "topor_05");
			
			bDisableFastReload = false;          //������� �����������
			chrDisableReloadToLocation = false;      //���������� ���� �������
        break;

		case "PDM_Albreht_Vhod":
			chrDisableReloadToLocation = false;   //���������� ���� �������
            sld = CharacterFromID("Albreht_Zalpfer");  //��������� �� ���������
	        sld.dialog.currentnode = "Ja_1";         //�������� �������
			sld.greeting = "Albrecht_Zalpfer";    //�����������	
			LAi_SetActorType(sld);            //���� ��� ������
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);  //�������� ��������
			PlaceCharacter(sld, "goto", PChar.location);   //��� �����	
			Locations[FindLocation("PortRoyal_town")].reload.l23.disable = false;   //��������� �����������
        break;

		case "PDM_Albreht_Vihod":
			sld = CharacterFromID("Albreht_Zalpfer")   //��������� �� ���������
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "none", "");   //�����������
        break;

//========================  ����� "��������� ����".  =======================
		
		case "PDM_Callow_RodjerVozvrat":	
			sld = CharacterFromID("PDM_LeFransua_Mayor_Klon")   //������� �����
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "none", "");   //�����������
			
			sld = CharacterFromID("LeFransua_Mayor")   //���������� �����������
			ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "sit", "sit1");   //�����������
		break;

		case "PDM_Callow_RodjerFin":
			sld = CharacterFromID("James_Callow")   //��������� �� ���������
			sld.dialog.filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "CollowRad_1";
		break;
		
		case "PDM_Callow_RadPoka":
			sld = CharacterFromID("James_Callow")   //��������� �� ���������
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");   //�����������
		break;
		
		case "PDM_FraOff_Bitva_1_Posle":
			chrDisableReloadToLocation = false;   //������ ����� ����
			bDisableFastReload = false;	         	//��������� ������� �����������
			sld = CharacterFromID("James_Callow")   //��������� �� ���������
			sld.dialog.filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_1";
		break;
		
		case "PDM_Pobeda_nad_Callow":
			AddQuestRecord("PDM_Cursed_Idol", "6");							//����� ��� ������� � ��
			CloseQuestHeader("PDM_Cursed_Idol"); 								//��������� ����� � ��
			AddCharacterExpToSkill(PChar, "Leadership", 100);
    		AddCharacterExpToSkill(PChar, "Sailing", 100);
    		AddCharacterExpToSkill(PChar, "Accuracy", 100);
    		AddCharacterExpToSkill(PChar, "Cannons", 100);
			AddCharacterExpToSkill(PChar, "Repair", 100);
    		AddCharacterExpToSkill(PChar, "Defence", 100);
    		AddCharacterExpToSkill(PChar, "Sneak", 100);
			PChar.quest.PDM_NEPobeda_nad_Callow.over = "yes";
		break;
		
		case "PDM_Callow_poradomoy":
			sld = CharacterFromID("James_Callow")
			sld.dialog.filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_1";
			AddQuestRecord("PDM_Cursed_Idol", "9");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_LocationFightDisable(loadedLocation, true); //��������� ������
		break;
//========================  ����� "����� ������".  =======================		

		case "PDM_HugoSeaHavana":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
		break;
//========================  ����� "������ �� �����".  =======================	

		case "PDM_Lesopilka_Vremy":
			AddQuestRecord("PDM_Novaya_Rodina", "8");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			Group_SetAddress("PDM_HUGO_GAL", "none", "", "");
		break;

		case "PDM_Lesopilka_SJ":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
			sld.dialog.currentnode   = "Final_1";
			PChar.quest.PDM_Lesopilka_Vremy.over = "yes";
		break;
		
		case "PDM_Lesopilka_SJNashel":
			AddQuestRecord("PDM_Novaya_Rodina", "7");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			PChar.quest.PDM_Lesopilka_Vremy.over = "yes";
			PChar.quest.PDM_Lesopilka_SJ.over = "yes";
			
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.win_condition.l1 = "location";
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.win_condition.l1.location = "Shore27";
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.function = "PDM_Zoloto_ne_tonet_BITVA_na_sushe";
			
			PChar.quest.PDM_ZNT_SJ_GLOBAL.win_condition.l1 = "MapEnter";
			PChar.quest.PDM_ZNT_SJ_GLOBAL.win_condition = "PDM_ZNT_Otmena_SOKR";
		break;
		
		case "PDM_ZolNeTon_PobNaSush":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"Havana_Town","goto","goto2");
			sld.city = "Havana";
			sld.dialog.filename   = "Quest/PDM/Novaya_Rodina.c";
			sld.dialog.currentnode   = "Final_1";
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			TakeItemFromCharacter(pchar, "PDM_SJ_Angl_Gal");
			chrDisableReloadToLocation = false;
			pchar.GenQuestBox.Dominica_Grot.box1.items.icollection = 1;
			pchar.GenQuestBox.Dominica_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 20;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry17 = 60;
			SetQuestHeader("PDM_Novaya_Rodina");
			AddQuestRecord("PDM_Novaya_Rodina", "9");	
			PChar.quest.PDM_ZNT_SJ_GLOBAL.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingLight", 30);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
			AddCharacterExpToSkill(pchar, "Fencing", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "PDM_ZNT_Otmena_SOKR":
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"none","","");
			PChar.quest.PDM_Zoloto_ne_tonet_BITVA_na_sushe.over = "yes";
			AddQuestRecord("PDM_Novaya_Rodina", "10");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("PDM_Novaya_Rodina");
			AddCharacterExpToSkill(pchar, "Leadership", -30);
			AddCharacterExpToSkill(pchar, "FencingLight", -30);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -30);
			AddCharacterExpToSkill(pchar, "Fencing", -30);
			AddCharacterExpToSkill(pchar, "Pistol", -30);
			AddCharacterExpToSkill(pchar, "Fortune", -30);
		break;
		
//========================  ����� "����� �� ������".  =======================

		case "PDM_ONV_BARTO_Ischezni":
			sld = CharacterFromID("PDM_Isp_sekr_guber")
			ChangeCharacterAddressGroup(sld,"none","","");			
		break;
		
		case "PDM_ONV_Clara_Ischezni":
			sld = CharacterFromID("PDM_ONV_Carla")
			ChangeCharacterAddressGroup(sld,"none","","");			
		break;
		
		case "PDM_ONV_Vkomnate":
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload1", true);
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload2", true);
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload3", true);
			LocatorReloadEnterDisable("Havana_townhall", "reload2", true);
			LocatorReloadEnterDisable("Havana_townhall", "reload1_back", true);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld,"Havana_TownhallRoom","goto","goto9");
			LAi_KillCharacter(sld);
			
			pchar.GenQuestBox.Havana_TownhallRoom.box2.items.PDM_ONV_Kluch = 1;
			
			PChar.quest.PDM_ONV_TRUP_1.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_1.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_1.win_condition.l1.locator_group = "reload";
			PChar.quest.PDM_ONV_TRUP_1.win_condition.l1.locator = "reload2";
			PChar.quest.PDM_ONV_TRUP_1.win_condition = "PDM_ONV_Vkomnate_Trup";
			
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.locator_group = "goto";
			PChar.quest.PDM_ONV_TRUP_2.win_condition.l1.locator = "goto5";
			PChar.quest.PDM_ONV_TRUP_2.win_condition = "PDM_ONV_Vkomnate_Trup";
			
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.locator_group = "box";
			PChar.quest.PDM_ONV_TRUP_3.win_condition.l1.locator = "box2";
			PChar.quest.PDM_ONV_TRUP_3.win_condition = "PDM_ONV_Vkomnate_Trup";
			
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.locator_group = "barmen";
			PChar.quest.PDM_ONV_TRUP_4.win_condition.l1.locator = "bar2";
			PChar.quest.PDM_ONV_TRUP_4.win_condition = "PDM_ONV_Vkomnate_Trup";
		break;
		
		case "PDM_ONV_Vkomnate_Trup":
			PChar.quest.PDM_ONV_TRUP_1.over = "yes";
			PChar.quest.PDM_ONV_TRUP_2.over = "yes";
			PChar.quest.PDM_ONV_TRUP_3.over = "yes";
			PChar.quest.PDM_ONV_TRUP_4.over = "yes";
			AddQuestRecord("PDM_Ohota_na_vedmu", "4");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			
			PChar.quest.PDM_ONV_kluch.win_condition.l1 = "item";				//�������
			PChar.quest.PDM_ONV_kluch.win_condition.l1.item = "PDM_ONV_kluch";
			PChar.quest.PDM_ONV_kluch.win_condition = "PDM_ONV_VstaemKDveri";
		break;
		
		case "PDM_ONV_VstaemKDveri":
			PChar.quest.PDM_ONV_LOCA.win_condition.l1 = "locator";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.locator_group = "reload";
			PChar.quest.PDM_ONV_LOCA.win_condition.l1.locator = "reload1";
			PChar.quest.PDM_ONV_LOCA.win_condition = "PDM_ONV_VhodKGubernatoru";			
		break;
		
		case "PDM_ONV_VhodKGubernatoru":
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload1", false);	
			PlaySound("Interface\key.wav");
			TakeItemFromCharacter(pchar, "PDM_ONV_kluch");
			
			sld = CharacterFromID("spa_guber")
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Havana_Mayor")
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Glavny_Guber_KLON", "Gaskon", "man", "man", 10, SPAIN, -1, false));
			sld.name 	= "���������";
			sld.lastname = "������-�-������";
			sld.city = "Havana";
			ChangeCharacterAddressGroup(sld, "Havana_townhall", "sit", "sit1");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "RazgovorSGuberom";
			LAi_SetHuberType(sld);
			LAi_SetImmortal(sld, true);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_SoldatGub_1", "sold_spa_1", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Havana";
			ChangeCharacterAddressGroup(sld, "Havana_townhall", "goto", "governor1");
			FantomMakeCoolFighter(sld, 50, 100, 100, "blade27", "pistol6", 50);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Soldat15";
			sld.greeting = "GR_Spainguard";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_SoldatGub_2", "sold_spa_3", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Havana";
			ChangeCharacterAddressGroup(sld, "Havana_townhall", "goto", "goto6");
			FantomMakeCoolFighter(sld, 50, 100, 100, "blade27", "pistol6", 50);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Soldat15";
			sld.greeting = "GR_Spainguard";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
		break;
		
		case "STRAJIschezni":
			sld = CharacterFromID("PDM_ONV_SoldatGub_1")
			ChangeCharacterAddressGroup(sld,"none","","");
			sld = CharacterFromID("PDM_ONV_SoldatGub_2")
			ChangeCharacterAddressGroup(sld,"none","","");			
		break;
		
		case "PDM_ONV_SVOBODA_URA":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload1", false);
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload2", false);
			LocatorReloadEnterDisable("Havana_TownhallRoom", "reload3", false);
			LocatorReloadEnterDisable("Havana_Townhall", "reload3", false);
			LocatorReloadEnterDisable("Havana_Townhall", "reload2", false);
			LocatorReloadEnterDisable("Havana_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Havana_town", "reload3_back", false);
			LocatorReloadEnterDisable("Havana_town", "reload2_back", false);
			LocatorReloadEnterDisable("Havana_town", "reload1_back", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload3_back", false);

			sld = CharacterFromID("PDM_ONV_Glavny_Guber_KLON")
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("spa_guber")
			ChangeCharacterAddressGroup(sld, "Havana_townhall", "sit", "sit1");
			sld = CharacterFromID("Havana_Mayor")
			ChangeCharacterAddressGroup(sld, "Havana_townhall", "goto", "governor1");

			pchar.questTemp.PDM_ONV_Detectiv_Tavern_1 = "Tevern_NET";
		break;
		
		case "PDM_ONV_Vzaimno":
			LAi_KillCharacter(pchar);
		break;
		
		case "PDM_ONV_KaznVedmi":		
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload8_1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.lifeday = 0;
			sld.dialog.currentnode   = "Inqizitor_Kazn_nachalo_1";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_1", "girl_2", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto17");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_2", "citiz_7", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload10_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_3", "citiz_4", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload10_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Podjigatel", "off_spa_1", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "reload8_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_4", "citiz_8", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_5", "citiz_1", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_6", "citiz_2", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_7", "citiz_10", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_8", "girl_8", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_9", "girl_9", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", "goto18");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_10", "girl_10", "woman", "woman", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Jitel_11", "citiz_5", "man", "man", 10, SPAIN, -1, false));
			ChangeCharacterAddressGroup(sld, "Santiago_town", "officers", "houseSp21_3");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("PDM_ONV_Carla")
			ChangeCharacterAddressGroup(sld, "Santiago_town", "merchant", "mrcActive2");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
		break;
		
		case "PDM_ONV_PodjIschezni":
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "PDM_ONV_InqIschzni":
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
//========================  ����� "���������� ������".  =======================

		case "PDM_PK_Ubita":
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet")
			sld.dialog.currentnode   = "Konets";
			
			AddCharacterExpToSkill(pchar, "FencingLight", 60);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 60);
			AddCharacterExpToSkill(pchar, "Fencing", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -5);
		break;
		
//========================  ����� "�������� ��������".  =======================	

		case "PDM_NK_Viktor":
			AddCharacterExpToSkill(pchar, "FencingLight", 100);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 100);
			AddCharacterExpToSkill(pchar, "Fencing", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 100);
			AddCharacterExpToSkill(pchar, "Sneak", -50);
			AddCharacterExpToSkill(pchar, "Commerce", -50);
			
			AddQuestRecord("PDM_Neputyovy_kaznachey", "4");
			
			sld = CharacterFromID("Andreas_Fickler")
			sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Fickler_11";
		break;
		
		case "PDM_NK_Litsenzia":
			if (GetDaysContinueNationLicence(HOLLAND) < 30) GiveNationLicence(HOLLAND, 30);
			if (GetDaysContinueNationLicence(SPAIN) < 30) GiveNationLicence(SPAIN, 30);
			if (GetDaysContinueNationLicence(ENGLAND) < 30) GiveNationLicence(ENGLAND, 30);
			if (GetDaysContinueNationLicence(FRANCE) < 30) GiveNationLicence(FRANCE, 30);
			TakeItemFromCharacter(pchar, "Litsenzia");
		break;
		
		case "PDM_NK_NaKorabl":
			sld = CharacterFromID("Andreas_Fickler")
			SetCharacterRemovable(sld, true);
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*50;
			sld.OfficerWantToGo.DontGo = true;
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;

//========================  ����� "���� ��������".  =======================

		case "PDM_CL_Lodka":
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_group_SetRelation("", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		break;
		
		case "PDM_CL_Antonio_Ubit":
			sld = CharacterFromID("PDM_CL_Antonio")
			LAi_KillCharacter(sld);
			sld = CharacterFromID("PDM_CL_Anto2")
			LAi_KillCharacter(sld);
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_2_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			AddQuestRecord("PDM_Clan_Lambrini", "3");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("��","��"));
		break;
		
		case "PDM_CL_PVT":
			sld = CharacterFromID("PDM_CL_Pokupatel")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
		break;
		
		case "PDM_CL_Na_Plyaj":
			sld = CharacterFromID("PDM_CL_Antonio3")
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.lifeday = 0;
			sld.dialog.currentnode   = "Antonio_6_1";		
		break;
		
		case "PDM_CL_Na_Plyaj_2":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PDM_CL_Pokupatel")
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.lifeday = 0;
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_6_1";		
		break;
		
		case "PDM_CL_Finish":
			LAi_SetFightMode(pchar, false);
			
			sld = CharacterFromID("PDM_CL_Antonio3")
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "none", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio4", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
			sld.name = "�������";
			sld.lastname = "�� �������";
			sld.greeting = "GR_Spainguard";
			sld.equip.blade = "blade39";
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.lifeday = 0;
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_8_1";
		break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   	������ "��������� ������� �����" �����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

		// ���������
		case "TichingituFree":
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_9";
			ChangeCharacterAddressGroup(sld, "BasTer_exittown", "rld", "aloc14"); // 170712
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "topor_05");
			EquipCharacterbyItem(sld, "topor_05"); // 151012
		break;
	}
}

//Lipsar �������� ������ ��� ������� --->
void FrameGiveMushket()
{
	sld = CharacterFromID("OffMushketer");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	SetLaunchFrameFormParam("�� ������ ������ ������...", "", 0.1, 2.0);
	LaunchFrameForm();
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld,"reload","reload1","none","","","",4.0);
}
//<--- Lipsar
void FrameAscoldVodka()
{
	pchar.GenQuest.CamShuttle = 2;
	WaitDate("",0,0,0,5,5);
	pchar.chr_ai.drunk = 600;
	SetLaunchFrameFormParam("������ ��������� ����� �������� ���������...", "Reload_To_Location", 0.1, 2.0);
	SetLaunchFrameReloadLocationParam("BasTer_houseSp1", "barmen","bar1", "");
	LaunchFrameForm();
}

// boal -->
////////////////////////   ����� ������ //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
    Pchar.AutoQuest.NPCharId = _charId;
    Pchar.AutoQuest.Quest    = _doQuest;
    Pchar.AutoQuest.Time1    = time1;
    Pchar.AutoQuest.Time2    = time2;
}

//��� ��������������� (navy 17.10.05)
//�c������� ��� ��������� �� � ����� ������� � ��������� ��� ���. 
//��� ����������� ������ ����. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
    ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth	= delayMonth;
	PChar.AutoQuest.delayDay	= delayDay;
	PChar.AutoQuest.delayHour	= delayHour;
	PChar.AutoQuest.delayMin	= delayMin;

	PChar.AutoQuest.idLocation	= idLocation;
	PChar.AutoQuest.idGroup		= idGroup;
	PChar.AutoQuest.idLocator	= idLocator;
	PChar.AutoQuest.questName	= questName;
}

// ��������� �������� � ��� ����� �� ����  -->
// _FrameText - �����  ������� ������ ������ "�����"+ NewStr() +"�����"
// _FrameQuest - ����� ����� ���������� ��������, ���� == "Reload_To_Location" ��. SetLaunchFrameReloadLocationParam
// ���� �� ����� == "Run_Function" ��. SetLaunchFrameRunFunctionParam
// _delay - ����� � �. ��������� ������ �������� (����� ��� ����������� � ��������� �������� �������, ���-�� 0.1-1.5�)
// _autoEnd - ����� � �. �������������� ������ ��������, 4-6� �� �����
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
    pchar.AutoQuest.FrameText    = _FrameText;
    pchar.AutoQuest.FrameQuest   = _FrameQuest;
    pchar.AutoQuest.FrameDelay   = _delay;
    pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
    pchar.AutoQuest.FramePic    = _FramePic;
}
// ����� ��� ��������� �������� ����� ��������
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
    pchar.AutoQuest.FrameLocation      = idLocation;
    pchar.AutoQuest.FrameGroup         = idGroup;
    pchar.AutoQuest.FrameLocator       = idLocator;
    pchar.AutoQuest.FrameLocationQuest = questName;
}
// ����� ��� ������ ������ �� ���� ����� �������� _func - �����, _delay - �������� ������ ������ ����� �������� � �.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
    pchar.AutoQuest.FrameFunction      = _func;
    pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// ��������� �������� � ��� ����� �� ����  <--

void WaitNextHours(string qName)
{
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = "������ ��������� �����...";
	if(sti(pchar.quest.waithours) == 1)		sHour = "������ ���� ���...";
	if(sti(pchar.quest.waithours) == 24)	sHour = "������ ���� �����...";
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	
	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
    if (CheckCharacterItem(Pchar, "patent_eng"))
    {
        TakeItemFromCharacter(pchar, "patent_eng");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_fra"))
    {
        TakeItemFromCharacter(pchar, "patent_fra");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_spa"))
    {
        TakeItemFromCharacter(pchar, "patent_spa");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_hol"))
    {
        TakeItemFromCharacter(pchar, "patent_hol");
        ChangeCharacterReputation(pchar, -10);
    }
}

void StartActorSelfDialog(string _CurrentNode)
{
    LAi_SetActorType(pchar);
    LAi_CharacterSaveAy(pchar);
    locCameraSleep(true);
    if (stf(pchar.chr_ai.type.ay) > 0)
    {
    	CharacterTurnAy(pchar,  -PI + abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    else
    {
    	CharacterTurnAy(pchar,  PI - abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    pchar.Dialog.CurrentNode = _CurrentNode;
    LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

//#20181102-03
void NationUpdate()
{
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
    }
}

// ������ ������
void Flag_PIRATE()
{
	PChar.nation	= PIRATE;
	Ship_FlagRefresh(PChar); //���� �� ����
	SetNationToOfficers(PIRATE);
	
	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	
	LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_PIRATE_SOLDIERS();
	
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if(bSeaActive)
	{
	    RefreshBattleInterface();
	    //#20181021-01
	    SetSchemeForSea();
	}
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation));
}

void Flag_FRANCE()
{
	PChar.nation	= FRANCE;
    Ship_FlagRefresh(PChar); //���� �� ����
    SetNationToOfficers(FRANCE);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, FRANCE));
    SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(FRANCE, SPAIN));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);

    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(FRANCE, HOLLAND));

    LAi_group_SetRelation("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); //LAI_GROUP_FRIEND);
    //Relation_FRANCE_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
        //#20181021-01
	    SetSchemeForSea();
    }
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation));
}

void Flag_ENGLAND()
{
	PChar.nation	= ENGLAND;
    Ship_FlagRefresh(PChar); //���� �� ����
    SetNationToOfficers(ENGLAND);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(ENGLAND, HOLLAND));

    LAi_group_SetRelation("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_ENGLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
        //#20181021-01
	    SetSchemeForSea();
    }
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation));
}

void Flag_SPAIN()
{
	PChar.nation = SPAIN;
    Ship_FlagRefresh(PChar); //���� �� ����
    SetNationToOfficers(SPAIN);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(SPAIN, HOLLAND));

    LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_SPAIN_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
        //#20181021-01
	    SetSchemeForSea();
    }
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation));
}

void Flag_HOLLAND()
{
	PChar.nation	= HOLLAND;
    Ship_FlagRefresh(PChar); //���� �� ����
    SetNationToOfficers(HOLLAND);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, HOLLAND));
    SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, HOLLAND));
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(SPAIN, HOLLAND));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, RELATION_FRIEND);

    LAi_group_SetRelation("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_HOLLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface();
        //#20181021-01
	    SetSchemeForSea();
    }
    else { if(IsEntity(worldMap))
        SetSchemeForMap();
    }
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_FLAG_SET,  sti(pchar.nation));
}

void Flag_Rerise()
{
	switch (sti(PChar.nation))
	{
    	case ENGLAND:	Flag_ENGLAND();	break;
    	case FRANCE:	Flag_FRANCE();	break;
    	case SPAIN:		Flag_SPAIN();	break;
    	case PIRATE:	Flag_PIRATE();	break;
    	case HOLLAND:	Flag_HOLLAND();	break;
	}
}

// blackthorn - ��������� "��������� ������"
void QuestCursedSceleton()
{
	ref sld;
	//sld = GetCharacter(CharacterFromID("CursedSkeleton"));
	sld = GetCharacter(NPC_GenerateCharacter("CursedSkeleton", "PGG_Skeletcap_"+sti(rand(5)), "skeleton", "skeleton", sti(pchar.rank)+20, PIRATE, 1, true));
	FantomMakeCoolFighter(sld, sti(pchar.rank)+20, 100, 100, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
	DeleteAttribute(sld, "SuperShooter");
	int hitpoints = rand(sti(pchar.rank)*15)+1000;
	LAi_SetHP(sld, hitpoints, hitpoints);
			
	sld.name = "��������� �������";
	sld.lastname = "";
	AddBonusEnergyToCharacter(sld, 200);
				
	sld.Dialog.CurrentNode = "First time";
	sld.dialog.filename = "Cursed_Skeleton.c";
	
	LAi_group_Delete("cursed");
	Group_FindOrCreateGroup("cursed");
	Group_AddCharacter("cursed", sld.id);
	//LAi_group_SetRelation("cursed", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//LAi_group_SetRelation("cursed", LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);
	
	chrDisableReloadToLocation = true;
	pchar.quest.CursedSceleton.win_condition.l1 = "NPC_Death";
	pchar.quest.CursedSceleton.win_condition.l1.character = sld.id;
	pchar.quest.CursedSceleton.win_condition = "OpenTheDoors";
	
	sld.cirassId = Items_FindItemIdx("cirass5");  // �������� ���, �� �������� ����
	sld.SaveItemsForDead = true;
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	//LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetActorType(sld);
    LAi_SetActorType(pchar);
	sld.quest.meeting = "2";
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
}