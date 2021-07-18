
void ActivateTimeEvents()
{

}

//////////////////////// boal SLiB ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
        // �������� �� ������� ���� ������� -->
        int nPaymentQ = 0;
        int i, cn;
        ref chref;

		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // ������� ������ �����, � �� ����� �������������� �������!!!
				{
				    nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		// �������� �� ������� ���� ������� <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); // � ��� ������ ��� �� �������!
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // ���� �� �����
				DeleteAttribute(pchar,"Partition.MonthPart")
			}
			
			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();

			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) // ����� ��������
			{
	      		LaunchSalaryScreen("");
			}
			else
			{
		        Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
		        PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
		        PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
	        }
        }
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int iStep = GetEventData();
	float dayRandom;
	float dayRandom1;
	float dayRandom2;

	// boal -->
	/*if (bQuestCheckProcessFreeze)   // ���� � ������, �� �����������
	{
	    if(iStep < 10)
		{
			PostEvent("EvSituationsUpdate", 1000, "l", iStep);
		}
	}*/
	// boal <--

	switch(iStep)
	{
		case 0:
            DeleteAttribute(pchar, "SkipEshipIndex");// boal
			
			DailyEatCrewUpdate(); // boal
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");
			
			dayRandom = Random();
			PChar.DayRandom = dayRandom;
			Log_TestInfo("dayRandom == " + dayRandom);
			
			dayRandom1 = Random();
			PChar.DayRandom1 = dayRandom1;
			Log_TestInfo("dayRandom1 == " + dayRandom1);
			
			dayRandom2 = Random();
			PChar.DayRandom2 = dayRandom2;
			Log_TestInfo("dayRandom2 == " + dayRandom2);
			
			ChangeImport();
			CheckOfficersHPMinus(); //Korsar Maxim - ���������� ���������� ���� ��� ������������� ����
			CheckBook(); //����� - Gregg
			CheckTrauma();//������ ������
		break;
		
		case 1:
            SalaryNextDayUpdate();  // ��������
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
		break;
		
		case 2:
			// ���� � �������� ������� PGG_DailyUpdate(); // navy 
			
			ProcessDayRepair();
		break;
		
		case 3:
			//UpdateDisease();
			
			Group_FreeAllDead();
		break;
		
		case 4:
			
			QuestActions(); //eddy
		break;
		
		case 5:
			//UpdateColonyProfit();  
			
			wdmEmptyAllOldEncounter();// homo ������ ����������
		break;
		
		case 6:
			
			UpdateCrewExp();  // ��������� ����� �������
		break;
		
		case 7:
			
			UpdateCrewInColonies(); // �������� ��������� � �������
		break;
		
		case 8:
			if(IsEntity(worldMap))
			{
				EmptyAllFantomCharacter(); // ���� ���
				wdmEmptyAllDeadQuestEncounter();
			}
		break;
		
		case 9:
			
            UpdateFame();   // ��� ������ ����������� ���������
			GenerateRumour() //homo 05/07/06
		break;
		
		case 10:
			//
			
		break;
		break;
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}


//////////////////////////////// ������ ���� - �������� ////////////////////////////////
void Tut_StartGame(string sQuest)
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
    SetCharacterTask_None(GetMainCharacter());
    LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
}

void Tut_locCamera_1(string _tmp)
{
    locCameraToPos(-5, 2.5, 5.6, false);
    DoQuestFunctionDelay("Tut_locCamera_2", 10.0);
}

void Tut_locCamera_2(string _tmp)
{
    locCameraFollow();
}
void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);

	if(rand(99)==0) 
	{
		switch (rand(1))
		{
			case 0:
				sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Skelt", "man", "man2_ab", 1, PIRATE, 0, false));
				sld.name 	= "T-800";
				sld.lastname 	= "";
				sld.Dialog.CurrentNode = "Alt_start";
				sld.dialog.filename = "Quest\StartGame_dialog.c";
				sld.greeting = "";
			break;
			case 1:
				StopSound(0,0);
				PlayStereoOGG("Music\necroTown.ogg");
				sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Skel_5", "man", "man2_ab", 1, PIRATE, 0, false));
				sld.name 	= "���������";
				sld.lastname 	= "������";
				sld.Dialog.CurrentNode = "Alt_start2";
				sld.dialog.filename = "Quest\StartGame_dialog.c";
				sld.greeting = "";
			break;
		}
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Pirate_9", "man", "man", 1, PIRATE, 0, false));
		sld.name 	= "������";
		sld.lastname 	= "����";
		sld.Dialog.CurrentNode = "First time";
		sld.dialog.filename = "Quest\StartGame_dialog.c";
		sld.greeting = "Teacher_pirat";
	}

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade1");
	EquipCharacterByItem(sld, "blade1");
	// ������� ���, ������� ���
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	// ������� ������� �������, �� ���� �� ������
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "shipowner_2", "man", "man", 1, PIRATE, 0, false));
    sld.name 	= "����";
    sld.lastname 	= "�������";

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade4");
	EquipCharacterByItem(sld, "blade4");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	TakeNItems(sld, "bullet", 30);
	AddItems(sld, "GunPowder", 30);
	// ������� ���
    sld.location = "Ship_deck_Low";  // ���� �� �����, ���� ��� ���
	//��������� ��������� ��� �� ��������
	SetQuestsCharacters();
}

void Tut_RestoreState()
{
	ref sld;

	pchar.Health.Damg = 0.0; // �������� �������
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);

	sld = characterFromID("Sailor_1");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
	LAi_SetImmortal(sld, false);

	sld = characterFromID("Sailor_2");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
	LAi_SetImmortal(sld, false);

	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;

	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");

	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void Tut_StartDialog()
{
	ref sld = characterFromID("Sailor_1");

	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ // �������, ��� �������
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
//��������� ���-����������� ������ � ������ ������ �� ����� ��
void SetQuestsCharacters()
{
	ref sld;
	string sTown;
	int iNation = sti(pchar.nation);
	switch (iNation)
	{
		case 0: sTown = "PortRoyal"; break;
		case 1: sTown = "Tortuga";	break;
		case 2:	sTown = "Havana";	break;
		case 3:	sTown = "Villemstad"; break;
		case 4:
			sTown = "PortRoyal";
			iNation = ENGLAND;
		break;
	}
	//�������� �������� �����
	sld = characterFromId("PoorKillSponsor");
	sld.nation = iNation;
	sld.city = sTown;
	sld.location = sTown + "_town";
	sld.location.group = "goto";
	sld.location.locator = "goto2";
	LAi_group_MoveCharacter(sld, GetNationNameByType(iNation) + "_citizens");
}

//Korsar Maxim - ������������� �������� ����� ������ ��������.
void CheckOfficersHPMinus()
{
	ref sld;
	int i, iOfficer;
	
	for(i = 1; i < 22; i++)  //Korsar Maxim - �����: ����������� ������ ��� �� ����������. ��������� �� ���������, �� � ��� �������� ����, ������� ������ �� ����������. (��� ���� ��� - ������� ���� �������)
	{
		if (GetOfficersIndex(Pchar, i) != -1)
		{
			iOfficer = GetOfficersIndex(Pchar, i);
			sld = GetCharacter(iOfficer);
			if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;
			
			/*if(CheckAttribute(sld,"HPminus"))
			{
				int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/
			
			if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
			{
				if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
				{
					DeleteAttribute(sld, "HPminusDays");
					//DeleteAttribute(sld, "HPminus");
					DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
					//LAi_SetHP(sld, ihpm, ihpm);
					Log_Info("������ " + GetFullName(sld) + " ����������.");
				}
			}
		}
	}
	for(i=0; i<GetPassengersQuantity(pchar); i++)
	{
		iOfficer = GetPassenger(pchar, i);
		sld = GetCharacter(iOfficer);
		if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;
			
		/*if(CheckAttribute(sld,"HPminus"))
		{
			int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/
		
		if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
		{
			if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
			{
				DeleteAttribute(sld, "HPminusDays");
				//DeleteAttribute(sld, "HPminus");
				DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
				//LAi_SetHP(sld, ihpm, ihpm);
				Log_Info("������ " + GetFullName(sld) + " ����������.");
			}
		}
	}
	int iCompanionQuantity = getCompanionQuantity(pchar);
	if(iCompanionQuantity > 1)
	{
		for(int n=1; n<COMPANION_MAX; n++)
		{
			iOfficer = GetCompanionIndex(pchar, n);
			sld = GetCharacter(iOfficer);
			if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;
			
		/*if(CheckAttribute(sld,"HPminus"))
		{
			int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/
		
			if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
			{
				if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
				{
					DeleteAttribute(sld, "HPminusDays");
					//DeleteAttribute(sld, "HPminus");
					DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
					//LAi_SetHP(sld, ihpm, ihpm);
					Log_Info("������ " + GetFullName(sld) + " ����������.");
				}
			}
		}
	}
}
void CheckBook()//�������� ����� ������ �� �������� - Gregg
{
	if (CheckAttribute(pchar,"bookreadtoday"))//���� ������ �� ����, ���� ���������� ������ �� ��������
	{
		DeleteAttribute(pchar,"bookreadtoday");
		return;
	}
	if (IsEntity(&worldMap) != 0)//���� ������ �� ��������
	{
		if (CheckAttribute(pchar,"booktype"))
		{
			if (sti(pchar.booktime) > 0)
			{	
				pchar.booktime = sti(pchar.booktime)-1;
				//if (sti(pchar.booktime) != 0)Log_Info("�������� "+pchar.booktime+" ���� �� ������� �������� �����.");
				//if (sti(pchar.booktime) == 0)Log_Info("��������� ���� �������� �����!");
			}
			if (sti(pchar.booktime) <= 0)
			{
				if (pchar.booktype == "Defense") pchar.booktype = "Defence";
				if (pchar.booktype == "Defen�e") pchar.booktype = "Defence";
				AddCharacterExpToSkill(pchar, pchar.booktype, sti(pchar.bookbonus));
				int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
				Log_Info(GetFullName(pchar) + " ������ ����� ''"+LanguageConvertString(idLngFile, pchar.bookname)+"'' � �������� ����� ''"+XI_ConvertString(pchar.booktype)+"''");
				LanguageCloseFile(idLngFile);
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktime.full");
				DeleteAttribute(pchar,"bookbonus");
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktype");
				DeleteAttribute(pchar,"bookreadtoday");
				string sEquipItem = GetCharacterEquipByGroup(pchar, BOOK_ITEM_TYPE);
				RemoveCharacterEquip(pchar, BOOK_ITEM_TYPE);
				RemoveItems(pchar, sEquipItem, 1);
				
				pchar.questTemp.bookcount = sti(pchar.questTemp.bookcount) + 1;
				// ��������� ����������
				if(sti(pchar.questTemp.bookcount) >= 3) UnlockAchievement("books", 1);
				if(sti(pchar.questTemp.bookcount) >= 6) UnlockAchievement("books", 2);
				if(sti(pchar.questTemp.bookcount) >= 10) UnlockAchievement("books", 3);
			}
		}
	}
}

void CheckTrauma() //������ ������ - Lipsar � Gregg
{
    /*string sTmp;
    ref chr;
    aref arTmp;
    int i, idx;
    // �������� ��������
    makearef( arTmp, refCh.Fellows.Old.Officers );
    for(i = 1; i < MAX_NUM_FIGHTERS; i++ )
    {
        idx = GetOfficersIndex(refCh,i);
        if( idx != -1 ) 
        {
            chr = GetCharacter(idx);
            if(CheckAttribute(chr, "chr_ai.HeavyTrauma")) 
            {
                chr.chr_ai.HeavyTrauma = sti(chr.chr_ai.HeavyTrauma) - 1;
                if(sti(chr.chr_ai.HeavyTrauma) <= 0) 
                {
                    DeleteAttribute(chr, "chr_ai.HeavyTrauma");
                    Log_Info("������" + chr.Name + "��������� �� ������� ������");
					CheckAndSetOverloadMode(chr);
                }
            }
        }
    }*/
	if(CheckAttribute(PChar, "chr_ai.Trauma"))//������ ��, ��� ��� �������� �������� ������ � ��
    {
		DeleteAttribute(PChar, "chr_ai.Trauma");
		Log_Info("�� ���������� �� ������");
	}
    if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//������ ��, ��� ��� �������� �������� ������ � ��
    {        
        PChar.chr_ai.HeavyTrauma = sti(PChar.chr_ai.HeavyTrauma) - 1;
        if(sti(PChar.chr_ai.HeavyTrauma) <= 0) 
        {
			DeleteAttribute(PChar, "chr_ai.TraumaQ");
            DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
            Log_Info("�� ���������� �� ������� ������");
			CheckAndSetOverloadMode(pchar);
        }
    }
}