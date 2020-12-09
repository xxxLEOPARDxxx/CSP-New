// BOAL ������� �� F12 �������� ���� ���. ��� ����� ������� � alt-tab � ����, ��������� ����� �����
//native string GetHello();
//#library "b_engine"

void ActiveINSERTControl()
{
    //DoReloadCharacterToLocation(Pchar.location, "goto", "goto2");
    //DoReloadCharacterToLocation("PlutoStoreSmall", "reload", "reload1");
	//DoReloadCharacterToLocation("SantaFlorentinaShipInside4", "goto", "goto1");
}

void ActiveF4Control()
{
	/*Log_Info("Test F4 button");
    SetRandGeraldSail(pchar, rand(4));*/
}

// Warship. ���� ������� ���� ���������� - �� �12 �� ����� ���
void ActiveF5Control()
{
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 15);
	ref characterRef;
	
    if(characterIndex != -1)
    {
        characterRef = GetCharacter(characterIndex);
		
		trace("==================== " + characterRef.ID + " ====================");
		DumpAttributes(characterRef);
		trace("========================================");
	}

	Log_Info("���� ���������� ���������� ���������");
}

void ActiveF7Control()
{
	// Warship. ����� ���������� ���������
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 25);
	ref characterRef;
	
    if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];
		
		if(!LAi_IsImmortal(characterRef)) // ���������
		{
			LAi_KillCharacter(characterRef);
			Log_Info("����� ��������� � ID == " + characterRef.Id);
		}
		else
		{
			Log_Info("������ ����� ��������� � ID == " + characterRef.Id);
		}
	}
}

void ActiveF10Control()
{
	Log_Info("Test F10 button");
    LaunchPsHeroScreen();
    trace("===================RUMOURS=======================");
    for(int i = 0; i < MAX_RUMOURS; i++)
	{
        DumpAttributes(&Rumour[i]);
    	trace("===================");
	}
	Log_Info(GetStrSmallRegister(GetRussianNumberString(rand(999) - rand(999))));
}

///  ����� ��������� � �����
void ActiveF12Control()
{
    ref mainCh = GetMainCharacter();

    //����� ���������� �������� ��������� � �������� �������
    int res = LAi_FindNearestVisCharacter(mainCh, 15);
    if (res != -1)
    {
        ref findCh = GetCharacter(res);
        res = findCh.chr_ai.hp;
        Log_SetStringToLog("" + GetFullName(findCh) +
                           " "+XI_ConvertString("Rank")+" " + findCh.rank + " "+XI_ConvertString("Health")+" "+res + "/" + LAi_GetCharacterMaxHP(findCh));

		if (bBettaTestMode)
        {
            Log_SetStringToLog("Id= " + findCh.id);
            Log_SetStringToLog("Idx= " + findCh.index);
            if(CheckAttribute(findCh, "LifeDay"))
		Log_Info("LifeDay - " + findCh.LifeDay);
		
	    if(CheckAttribute(findCh, "City"))
	    	Log_Info("City - " + findCh.City);
            if (CheckAttribute(findCh, "equip.blade"))
            {
                Log_SetStringToLog("Blade= " + findCh.equip.blade);
            }
            if (CheckAttribute(findCh, "equip.pistol"))
            {
                Log_SetStringToLog("Pistol= " + findCh.equip.pistol);
            }
            Log_SetStringToLog("model= " + findCh.model);
            Log_SetStringToLog("face= " + findCh.faceId);
            Log_SetStringToLog("chr_ai.type= " + findCh.chr_ai.type);
            Log_SetStringToLog("Group= "+findCh.location.group + " locator= " + findCh.location.locator);
            if (CheckAttribute(findCh, "cirassId"))
            {
                Log_SetStringToLog("cirassId= " + sti(findCh.cirassId));
            }
            else
            {
                Log_SetStringToLog("��� �����");
            }
            if (CheckAttribute(findCh, "chr_ai.FencingType"))
            {
                Log_SetStringToLog("chr_ai.FencingType= " + findCh.chr_ai.FencingType));
            }
            else
            {
                Log_SetStringToLog("��� FencingType - error");
            }
            /*int dchr_index;
            ref deadCh;
            dchr_index = Dead_FindCloseBody();
            if (dchr_index != -1)
            {
                deadCh = &Dead_Characters[dchr_index];
                Log_SetStringToLog("Dead=" + deadCh.id);
            } */
			Log_SetStringToLog("�����: " + findCh.nation);
			Log_SetStringToLog("���: " + findCh.sex);
			Log_SetStringToLog("������: " + findCh.chr_ai.group);
			Log_SetStringToLog("��������: " + findCh.chr_ai.tmpl);
			Log_SetStringToLog("�����: " + findCh.chr_ai.tmpl.state);
			dumpattributes(findCh);

            mainCh.SystemInfo.OnlyShowCharacter = true;
			LaunchCharacter(findCh);
        }
        else
        {
            if (MOD_BETTATESTMODE == "Test")
	        {
	            Log_SetStringToLog("Id= " + findCh.id);
	        }
        }
    }
}

///////////////////////////// test //////////////
void TestColonyCommanders()
{
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // ����������
		// ������� ������� ����� �������
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // ��� ����
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// �������� �������� �� �������, � ��� ��� ������, ����� �� ���������?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
}
// �������� ����������� ������ - ����-���, ��� �������� - ������� � ������.��� ������, ������ �������� ���� ������� �� ����� �����
void TestGoodsLiquidity()
{
	int i, j, idx;
	float fMaxCost;

	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1;
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight))
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				}
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
}
