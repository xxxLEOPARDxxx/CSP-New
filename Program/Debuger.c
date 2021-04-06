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
	aref    arCharShip; makearef(arCharShip, pchar.Ship);
    float x = stf(arCharShip.Pos.x);
    float y = stf(arCharShip.Pos.y);
    float z = stf(arCharShip.Pos.z);
    float bx = arCharShip.BoxSize.x;
    float by = arCharShip.BoxSize.y;
    float x1, y1;
    x1 = (frnd() - 0.5) * bx;

    y1 = 1.0 + y + frnd() * 3.0
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
    CreateParticleSystem("Blast", x + x1, y1, z, 0.0, 0.0, 0.0, 0); 
	
	/* //Korsar Maxim - �� �4 ������� ��������-��� �� ��� � ���� � ���
	ref sld = GetCharacter(NPC_GenerateCharacter("Mechanic1", "CCS_Mechanic", "man", "man", 30, PIRATE, -1, true));
	sld.name = "������";
	sld.lastname = "�������";
	sld.greeting = "Gr_questOfficer";
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.quest.meeting = true;
	sld.HalfImmortal = true;  // ��������
	SetSelfSkill(sld, 10, 10, 10, 10, 99);
	SetShipSkill(sld, 50, 50, 50, 50, 100, 100, 50, 100, 50);
	SetSPECIAL(sld, 6, 10, 9, 10, 10, 8, 10);
	SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "LightRepair");
	SetCharacterPerk(sld, "InstantRepair");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "Turn180");
	SetCharacterPerk(sld, "SailingProfessional");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "Builder");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	TakeNItems(sld, "talisman7", 1);
	sld.quest.OfficerPrice = sti(pchar.rank)*350;
	AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
	sld.OfficerWantToGo.DontGo = true; //�� �������� ����
	sld.loyality = MAX_LOYALITY;
	Log_Info("Test F4 button");
    SetRandGeraldSail(pchar, rand(4));
	pchar.VedekerDiscount = true; */
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
