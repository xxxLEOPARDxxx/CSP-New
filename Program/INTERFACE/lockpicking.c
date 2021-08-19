int checkingstagenum = 10;
int pickposition = 90;
int openingcount = 0;

int correctposition;

string wrenchtex, picktex;
string chestID;

bool openingstarted = false;
bool cylinderstarted = false;
bool lockclick = false;
bool g_bToolTipStarted = false;

bool	LckPckngProcessBooster	 = true;

bool firsttime;
bool opened = false;
bool broken = false;

bool mousechangepos = true;
string mpos;
string ompos;

void InitInterface_gm(string iniName)
{
	string sHeader = "TEST";

	string sText1, sText2, sText3;
	LAi_SetActorTypeNoGroup(pchar);
	locCameraSleep(true);
	SetTimeScale(0.0);

	if(LckPckngProcessBooster == false) EngineLayersOffOn(true);
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("eSlideChange","procSlideChange",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	
	if (CheckAttribute(pchar, "questTemp.lockpicking.firsttime"))
	{
		if(makeint(pchar.questTemp.lockpicking.firsttime) == 1) firsttime = true;
		else firsttime = false;
	}
	else
	{
		firsttime = true;
	}
	
	PlaySound("interface\lockpicking\ui_lockpicking_enter_01.wav"); // ���� ������ ���������
	chestID = pchar.questTemp.lockpicking.ID;
	
	correctposition = 1+rand(179);
	
	if(correctposition < 15) correctposition = 15;
	if(correctposition > 165) correctposition = 165;
	
	sHeader = "�������� ������";
	sText1 = "����� ������ ��������� ������� ��������� �������� �������, ����� ���������� �� ����������. �������� ������������ ����� ������� ����������� ��������� �������, ����������� � �������. ������� 'Ctrl' - ������� ��������. �������� ���� �� ��������� - ����� ���� ����������� �������. ������� 'Esc' - �����.");
	sText2 = "���������� ���� �����-����, ���������� ��������� �������. ����� �� ���� ������, ������� � ����������� ������� 'Ctrl' ��� ����, ����� ������ ������� �������. ��� �������� ����� ����������, ����� ������� ��� �������� �� 90 ��������."
	sText3 = "���� ������� � �������� �������� ���������� �����������, ��� ������, ��� ��������� ������� ������� �����������. � ���� ������, ��������� ������� 'Ctrl' � ���������, ����� ������� �������� � �������� ���������, ����� �������������� �������. �������, ��� ����� � ����������� ��������� �� ��������� �������, ��� �� ������� ���� ������� ����� ��������.";
	
	if(firsttime == true) CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
    switch(nodName)
	{
		
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();
}

void IProcessFrame()
{
	int randsound;
	int squeaksound;
	int randclicksound;
	
	int difference;
	float dmultiplier;
	
	float mouseposition;
	int movsound;
	
	if (CheckAttribute(GameInterface,"mousepos")) mouseposition = 600.0-(stf(GameInterface.mousepos.y));
	
	if(mouseposition > 600) mouseposition = 600;
	if(mouseposition < 9) mouseposition = 9;
	
	pickposition = mouseposition*0.3;
	picktex = "interfaces\LockPicking\pick\" + makeint(pickposition/2) + ".tga";
	SetNewPicture("PICK_PIC",picktex);
	
	if(lockclick == false)
	{
		SetRealMouseSensitivity();
	}
	else
	{
		XI_SetMouseSensitivity(0.0, 0.0);
	}
	
	if(checkingstagenum < 460)
	{
		if(mousechangepos == false)
		{
			mpos = GameInterface.mousepos.y;
			
			if(mpos != ompos)
			{
				if(rand(20) == 0)
				{
					movsound = rand(11)+1;
					
					if(movsound < 10) PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_0"+ movsound +".wav");
					else PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_"+ movsound +".wav");
				}
			}
			
			mousechangepos = true;
		}
		
		if(mousechangepos == true)
		{
			if (CheckAttribute(GameInterface,"mousepos")) ompos = GameInterface.mousepos.y;
			mousechangepos = false;
		}
	}
	
	if(checkingstagenum < 460)
	{
		if((pickposition - correctposition) <= 0) difference = correctposition - pickposition;
		else difference = pickposition - correctposition;
		
		dmultiplier = makefloat(difference)/180.0;
		
		if(XI_IsKeyPressed("control")) // ������� �������, ���� ������ ������ Ctrl
		{
			checkingstagenum = checkingstagenum + 10;
			
			if(cylinderstarted == false) // ���� ������ �������� ��������
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = true;
			}
		}
		else // ���� ������ �� ������, �� ���������� � �������� ���������
		{
			checkingstagenum = checkingstagenum - 10;
			
			if(cylinderstarted == true) // ���� ������ �������� ��������
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = false;
			}
		}
		
		if(makeint(dmultiplier*100.0) > 2)
		{
			if(checkingstagenum > makeint((1.0 - dmultiplier)*460.0))
			{
				checkingstagenum = makeint((1.0 - dmultiplier)*460.0);
				
				if(lockclick == false)
				{
					lockclick = true;
					
					randclicksound = rand(2)+1;
					PlaySound("interface\lockpicking\cylstop\ui_lockpicking_cylinderstop_0"+ randclicksound +".wav");
					if (rand(20)==0 && pickposition != 0)
					{
						broken = true;
						IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
					}
				}
				
			}
		}
		
		if(checkingstagenum > 460) checkingstagenum = 460;
		
		if(checkingstagenum < 10)
		{
			checkingstagenum = 10;
			lockclick = false;
		}
		
		if(checkingstagenum == 460) OpenProcedure(); // ���� ������� �������� �� 90 ��������, �� ��������� ������� ��������
		
		if(checkingstagenum != 10 && checkingstagenum != 460 && checkingstagenum != makeint((1.0 - dmultiplier)*460.0)) // ������������� �������� ��� ��� ��������
		{
			if(rand(160) == 0)
			{
				squeaksound = rand(11)+1;
				
				if(squeaksound < 10) PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_0"+ squeaksound +".wav");
				else PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_"+ squeaksound +".wav");
			}
		}
		
		// ������ ���������� ��������� ��������
		wrenchtex = "interfaces\LockPicking\wrench\" + makeint(checkingstagenum/10) + ".tga";
		SetNewPicture("WRENCH_PIC",wrenchtex);
	}
	
	if(openingstarted == true)
	{
		openingcount = openingcount + 4;
		
		if(openingcount > 200)
		{
			openingstarted = false;
			opened = true;
			
			SetNodeUsing("BACK_PIC",false);
			SetNodeUsing("LOCK_PIC",false);
			SetNodeUsing("WRENCH_PIC",false);
			SetNodeUsing("PICK_PIC",false);
			SetNodeUsing("PICKSLIDE",false);
			
			OpenChest();
		}
	}
}

void OpenProcedure() // ������� ��������
{
	int randsound = rand(2)+1;
	
	openingstarted = true;
	PlaySound("interface\lockpicking\ui_lockpicking_unlock_0"+ randsound +".wav"); // ���� ������ �����
}

void OpenChest()
{
	AddCharacterExpToSkill(PChar, "Fortune", 50);
	AddCharacterExpToSkill(PChar, "Repair", 50);
	TakeItemFromCharacter(pchar, chestID);
	pchar.questTemp.chestcount = sti(pchar.questTemp.chestcount) + 1;
	// ��������� ����������
	if(sti(pchar.questTemp.chestcount) >= 10) UnlockAchievement("AchChest", 1);
	if(sti(pchar.questTemp.chestcount) >= 25) UnlockAchievement("AchChest", 2);
	if(sti(pchar.questTemp.chestcount) >= 50) UnlockAchievement("AchChest", 3);
	string nameitm[35];
	int itmq[35];
	int value;
	int value_alt;
	switch (chestID)
	{
		case "Chest_treasure":
			value = chest_treasure[sti(pchar.Chest_treasure)];
			pchar.Chest_treasure = sti(pchar.Chest_treasure) + 1;
			if (sti(pchar.Chest_treasure) > 99) pchar.Chest_treasure = 0;
			value_alt = chest_treasure2[sti(pchar.Chest_treasure2)];
			pchar.Chest_treasure2 = sti(pchar.Chest_treasure2) + 1;
			if (sti(pchar.Chest_treasure2) > 99) pchar.Chest_treasure2 = 0;
		break;
		case "Chest_Craftsmans":
			value = chest_craftsmans[sti(pchar.Chest_Craftsmans)];
			pchar.Chest_Craftsmans = sti(pchar.Chest_Craftsmans) + 1;
			if (sti(pchar.Chest_Craftsmans) > 99) pchar.Chest_Craftsmans = 0;
			value_alt = chest_craftsmans2[sti(pchar.Chest_Craftsmans2)];
			pchar.Chest_Craftsmans2 = sti(pchar.Chest_Craftsmans2) + 1;
			if (sti(pchar.Chest_Craftsmans2) > 99) pchar.Chest_Craftsmans2 = 0;
		break;
		case "Chest_ammo": 
			value = chest_ammo[sti(pchar.chest_ammo)];
			pchar.chest_ammo = sti(pchar.chest_ammo) + 1;
			if (sti(pchar.chest_ammo) > 99) pchar.chest_ammo = 0;
			value_alt = chest_ammo2[sti(pchar.chest_ammo2)];
			pchar.chest_ammo2 = sti(pchar.chest_ammo2) + 1;
			if (sti(pchar.chest_ammo2) > 99) pchar.chest_ammo2 = 0;
		break;
		case "Chest_quest":
			value = chest_quest[sti(pchar.Chest_quest)];
			pchar.Chest_quest = sti(pchar.Chest_quest) + 1;
			if (sti(pchar.Chest_quest) > 99) pchar.Chest_quest = 0;
			value_alt = chest_quest2[sti(pchar.Chest_quest2)];
			pchar.Chest_quest2 = sti(pchar.Chest_quest2) + 1;
			if (sti(pchar.Chest_quest2) > 99) pchar.Chest_quest2 = 0;
		break;
	}
	int value2 = 999 - value;
	int value3 = 999 - value_alt;
	//� ������ ������� ����� ��������������� �� 10 ��������� (������� � �������� �� 0 �� 9) �� ������� ������. ������������� �������� 4 ����� ����.
	
	if(chestID == "Chest_treasure") // �����
	{
		switch (makeint(value/111))
		{
			case 0:
				nameitm[1] = "jewelry4"; // �������
				itmq[1] = 10;
				nameitm[2] = "jewelry8"; // ��������� ������
				itmq[2] = 10;
				nameitm[3] = "jewelry9"; // ��������� �������
				itmq[3] = 10;
				nameitm[4] = "jewelry15"; // ���������� ��������
				itmq[4] = 10;
				nameitm[9] = "gold"; // ������
				itmq[9] = 4000;
			break;
			case 1:
				nameitm[1] = "jewelry1"; // ������
				itmq[1] = 10;
				nameitm[2] = "jewelry2"; // �����
				itmq[2] = 10;
				nameitm[3] = "jewelry3"; // �����
				itmq[3] = 10;
				nameitm[9] = "gold"; // ������
				itmq[9] = 18000;
			break;
			case 2:
				nameitm[1] = "jewelry5"; // ������� ������
				itmq[1] = 4;
				nameitm[2] = "jewelry6"; // ���������� ������ � ��������
				itmq[2] = 9;
				nameitm[3] = "jewelry7"; // ������� ������ � ���������
				itmq[3] = 8;
				nameitm[9] = "gold"; // ������
				itmq[9] = 12000;
			break;
			case 3:
				nameitm[1] = "jewelry10"; // ������� ������ � ��������
				itmq[1] = 10;
				nameitm[2] = "jewelry11"; // ������� ���������
				itmq[2] = 10;
				nameitm[3] = "jewelry12"; // ��������� ���������
				itmq[3] = 10;
				nameitm[4] = "jewelry13"; // �����
				itmq[4] = 10;
				nameitm[5] = "jewelry14"; // ������� �����
				itmq[5] = 10;
				nameitm[9] = "gold"; // ������
				itmq[9] = 6000;
			break;
			case 4:
				nameitm[1] = "jewelry16"; // ��������
				itmq[1] = 10;
				nameitm[2] = "jewelry17"; // ���������� ������
				itmq[2] = 5;
				nameitm[3] = "jewelry18"; // ������� ������ � �������
				itmq[3] = 3;
				nameitm[9] = "gold"; // ������
				itmq[9] = 16000;
			break;
			case 5:
				nameitm[1] = "jewelry5"; // ������� ������
				itmq[1] = 7;
				nameitm[2] = "jewelry7"; // ������� ������ � ���������
				itmq[2] = 8;
				nameitm[3] = "jewelry10"; // ������� ������ � ��������
				itmq[3] = 10;
				nameitm[4] = "jewelry14"; // ������� �����
				itmq[4] = 10;
				nameitm[5] = "jewelry18"; // ������� ������ � �������
				itmq[5] = 6;
				nameitm[9] = "gold"; // ������
				itmq[9] = 10000;
			break;
			case 6:
				nameitm[1] = "jewelry6"; // ���������� ������ � ��������
				itmq[1] = 20;
				nameitm[2] = "jewelry17"; // ���������� ������
				itmq[2] = 20;
				nameitm[9] = "gold"; // ������
				itmq[9] = 20000;
			break;
			case 7:
				nameitm[1] = "jewelry6"; // ���������� ������ � ��������
				itmq[1] = 15;
				nameitm[2] = "jewelry7"; // ������� ������ � ���������
				itmq[2] = 15;
				nameitm[3] = "jewelry8"; // ��������� ������
				itmq[3] = 15;
				nameitm[4] = "jewelry10"; // ������� ������ � ��������
				itmq[4] = 15;
				nameitm[9] = "gold"; // ������
				itmq[9] = 7000;
			break;
			case 8:
				nameitm[1] = "jewelry5"; // ������� ������
				itmq[1] = 25;
				nameitm[2] = "jewelry11"; // ������� ���������
				itmq[2] = 25;
				nameitm[3] = "jewelry12"; // ��������� ���������
				itmq[3] = 25;
				nameitm[4] = "jewelry17"; // ���������� ������
				itmq[4] = 25;
				nameitm[9] = "gold"; // ������
				itmq[9] = 1000;
			break;
			case 9:
				nameitm[1] = "jewelry8"; // ��������� ������
				itmq[1] = 10;
				nameitm[2] = "jewelry9"; // ��������� �������
				itmq[2] = 10;
				nameitm[9] = "gold"; // ������
				itmq[9] = 15000;
			break;
			case 10:
				nameitm[1] = "jewelry8"; // ��������� ������
				itmq[1] = 10;
				nameitm[2] = "jewelry9"; // ��������� �������
				itmq[2] = 10;
				nameitm[9] = "gold"; // ������
				itmq[9] = 15000;
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		itmq[9] += makeint(value/3);
		if (value < 100) {nameitm[3] = "Mineral2"; itmq[3] = 1;}
		if (value >= 200 && value < 400) {nameitm[3] = "Mineral4"; itmq[3] = 1;}
		if (value >= 800) {nameitm[3] = "Mineral8"; itmq[3] = 1;}
	}
	
	if(chestID == "Chest_Craftsmans") // ������������
	{
		switch (makeint(value/83))
		{
			case 0:
				nameitm[1] = "CompCraft_Parchment"; // ������
				itmq[1] = 150;
			break;
			case 1:
				nameitm[1] = "CompCraft_Nails"; // ������
				itmq[1] = 50;
				nameitm[2] = "CompCraft_Lead"; // ������
				itmq[2] = 12;
				nameitm[3] = "CompCraft_Grindstone"; // ������
				itmq[3] = 5;
			break;
			case 2:
				nameitm[1] = "CompCraft_Magnesium"; // ������
				itmq[1] = 10;
				nameitm[2] = "CompCraft_Flint"; // �������
				itmq[2] = 11;
				nameitm[3] = "CompCraft_Copper"; // ����
				itmq[3] = 15;
				nameitm[4] = "CompCraft_Sulfur"; // ����
				itmq[4] = 17;
			break;
			case 3:
				nameitm[1] = "CompCraft_SulfurCrush"; // ������������ ����
				itmq[1] = 30;
				nameitm[2] = "CompCraft_PowderMixture"; // ��������� �����
				itmq[2] = 31;
				nameitm[3] = "CompCraft_Parchment"; // ������
				itmq[3] = 32;
			break;
			case 4:
				nameitm[1] = "CompCraft_Nails"; // ������
				itmq[1] = 200;
				nameitm[2] = "CompCraft_Parchment"; // ������
				itmq[2] = 100;
			break;
			case 5:
				nameitm[1] = "CompCraft_Copper"; // ����
				itmq[1] = 83;
			break;
			case 6:
				nameitm[1] = "CompCraft_Flint"; // �������
				itmq[1] = 45;
			break;
			case 7:
				nameitm[1] = "CompCraft_Magnesium"; // ������
				itmq[1] = 57;
			break;
			case 8:
				nameitm[1] = "CompCraft_Nails"; // ������
				itmq[1] = 10;
				nameitm[2] = "CompCraft_Magnesium"; // ������
				itmq[2] = 10;
				nameitm[3] = "CompCraft_Flint"; // �������
				itmq[3] = 10;
				nameitm[4] = "CompCraft_Lead"; // ������
				itmq[4] = 10;
				nameitm[5] = "CompCraft_Copper"; // ����
				itmq[5] = 10;
				nameitm[6] = "CompCraft_Sulfur"; // ����
				itmq[6] = 10;
				nameitm[7] = "CompCraft_SulfurCrush"; // ������������ ����
				itmq[7] = 10;
				nameitm[8] = "CompCraft_PowderMixture"; // ��������� ����� ����
				itmq[8] = 10;
				nameitm[9] = "CompCraft_Parchment"; // ������
				itmq[9] = 10;
				nameitm[10] = "CompCraft_Grindstone"; // ������
				itmq[10] = 5;
			break;
			case 9:
				nameitm[1] = "CompCraft_SulfurCrush"; // ������������ ����
				itmq[1] = 100;
				nameitm[2] = "CompCraft_PowderMixture"; // ��������� ����� ����
				itmq[2] = 100;
			break;
			case 10:
				nameitm[1] = "CompCraft_Grindstone"; // ������
				itmq[1] = 15;
			break;
			case 11:
				nameitm[1] = "slave_01"; // ������
				itmq[1] = 15;
			break;
			case 12:
				nameitm[1] = "CompCraft_Grindstone"; // ������
				itmq[1] = 11;
				nameitm[2] = "slave_01"; // ������
				itmq[2] = 12;
			break;
			case 13:
				nameitm[1] = "CompCraft_Grindstone"; // ������
				itmq[1] = 11;
				nameitm[2] = "slave_01"; // ������
				itmq[2] = 12;
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		if (itmq[6] > 0) itmq[6] += makeint(value/50);
		if (itmq[7] > 0) itmq[7] += makeint(value/50);
		if (itmq[8] > 0) itmq[8] += makeint(value/50);
		if (itmq[9] > 0) itmq[9] += makeint(value/50);
		if (itmq[10] > 0) itmq[10] += makeint(value/50);
		
		if (value < 333) {nameitm[11] = "CompCraft_HealthTobacco"; itmq[11] = 1;}
		if (value >= 333 && value < 666) {nameitm[12] = "CompCraft_EnergyTobacco"; itmq[12] = 1;}
		if (value >= 666) {nameitm[13] = "CompCraft_StrengthTobacco"; itmq[13] = 1;}
		if (value >= 700) {nameitm[14] = "CompCraft_Scissors"; itmq[14] = 1;}
	}
	
	if(chestID == "Chest_ammo") // ����������
	{
		switch (makeint(value/59)) // �� 0 �� 14
		{
			case 0:
				nameitm[1] = "bullet"; // ��������� ����
				itmq[1] = 37;
				nameitm[2] = "gunpowder"; // ��������������� �����
				itmq[2] = 35;
				nameitm[4] = "grapeshot"; // �������
				itmq[4] = 33;
				nameitm[5] = "cartridge"; // �������� ������
				itmq[5] = 31;
			break;
			case 1:
				nameitm[1] = "bullet"; // ��������� ����
				itmq[1] = 52;
				nameitm[2] = "gunpowder"; // ��������������� �����
				itmq[2] = 55;
			break;
			case 2:
				nameitm[1] = "bullet"; // ��������� ����
				itmq[1] = 154;
				nameitm[2] = "gunpowder"; // ��������������� �����
				itmq[2] = 151;
			break;
			case 3:
				nameitm[1] = "grapeshot"; // �������
				itmq[1] = 53;
				nameitm[2] = "cartridge"; // �������� ������
				itmq[2] = 31;
			break;
			case 4:
				nameitm[1] = "grapeshot"; // �������
				itmq[1] = 155;
				nameitm[2] = "cartridge"; // �������� ������
				itmq[2] = 101;
			break;
			case 5:
				nameitm[1] = "powder_pellet"; // �������
				itmq[1] = 10;
				nameitm[2] = "grenade"; // �������
				itmq[2] = 5;
			break;
			case 6:
				nameitm[1] = "powder_pellet"; // �������
				itmq[1] = 32;
				nameitm[2] = "grenade"; // �������
				itmq[2] = 15;
			break;
			case 7:
				nameitm[1] = "powder_pellet"; // �������
				itmq[1] = 50;
			break;
			case 8:
				nameitm[2] = "grenade"; // �������
				itmq[2] = 32;
			break;
			case 9:
				nameitm[1] = "harpoon"; // ������
				itmq[1] = 16;
			break;
			case 10:
				nameitm[1] = "harpoon"; // ������
				itmq[1] = 26;
			break;
			case 11:
				nameitm[1] = "GunEchin"; // ������ �����
				itmq[1] = 15;
			break;
			case 12:
				nameitm[1] = "GunEchin"; // ������ �����
				itmq[1] = 28;
			break;
			case 13:
				nameitm[1] = "bullet"; // ��������� ����
				itmq[1] = 52;
				nameitm[2] = "gunpowder"; // ��������������� �����
				itmq[2] = 54;
				nameitm[3] = "grapeshot"; // �������
				itmq[3] = 31;
				nameitm[4] = "cartridge"; // �������� ������
				itmq[4] = 23;
				nameitm[5] = "powder_pellet"; // �������
				itmq[5] = 11;
				nameitm[6] = "grenade"; // �������
				itmq[6] = 5;
				nameitm[7] = "harpoon"; // ������
				itmq[7] = 5;
				nameitm[8] = "GunEchin"; // ������ �����
				itmq[8] = 5;
			break;
			case 14:
				nameitm[1] = "potion1"; // �������� �����
				itmq[1] = 31;
				nameitm[2] = "potion2"; // �������
				itmq[2] = 15;
				nameitm[3] = "potionrum"; // ������� ����
				itmq[3] = 23;
			break;
			case 15:
				nameitm[1] = "potion1"; // �������� �����
				itmq[1] = 72;
			break;
			case 16:
				nameitm[1] = "potion2"; // �������
				itmq[1] = 31;
			break;
			case 17:
				nameitm[1] = "potionrum"; // ������� ����
				itmq[1] = 43;
			break;
			case 18:
				nameitm[3] = "potionrum"; // ������� ����
				itmq[3] = 43;
			break;
		}
		if (itmq[0] > 0) itmq[0] += makeint(value/50);
		if (itmq[1] > 0) itmq[1] += makeint(value/50);
		if (itmq[2] > 0) itmq[2] += makeint(value/50);
		if (itmq[3] > 0) itmq[3] += makeint(value/50);
		if (itmq[4] > 0) itmq[4] += makeint(value/50);
		if (itmq[5] > 0) itmq[5] += makeint(value/50);
		if (itmq[6] > 0) itmq[6] += makeint(value/50);
		if (itmq[7] > 0) itmq[7] += makeint(value/50);
		if (itmq[8] > 0) itmq[8] += makeint(value/50);
		if (itmq[9] > 0) itmq[9] += makeint(value/50);
		if (value >= 800) {nameitm[9] = "GunCap_colt"; itmq[9] = 5;}
	}
	
	if(chestID == "Chest_quest") // ��������
	{
		switch (makeint(value/62))
		{
			case 0:
				nameitm[0] = "indian4"; // �������� ������
				itmq[0] = 1;
				nameitm[1] = "indian8"; // ���������� �����
				itmq[1] = 1;
				nameitm[2] = "indian9"; // ������������ �����
				itmq[2] = 1;
				nameitm[3] = "indian13"; // ������� ������������
				itmq[3] = 1;
				nameitm[4] = "indian16"; // ������������ �����
				itmq[4] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 9000;
			break;
			case 1:
				nameitm[0] = "indian3"; // ���������� �����
				itmq[0] = 1;
				nameitm[1] = "indian5"; // ������� �����
				itmq[1] = 1;
				nameitm[2] = "indian10"; // ������ ��������
				itmq[2] = 1;
				nameitm[3] = "indian2"; // �������� �������
				itmq[3] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 10000;
			break;
			case 2:
				nameitm[0] = "indian6"; // ������ ���������
				itmq[0] = 1;
				nameitm[1] = "indian7"; // ���� ������� ������
				itmq[1] = 1;
				nameitm[2] = "indian12"; // �����-����� ������������
				itmq[2] = 1;
				nameitm[3] = "indian14"; // ���� ��������
				itmq[3] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 11000;
			break;
			case 3:
				nameitm[0] = "indian18"; // ���� ������
				itmq[0] = 1;
				nameitm[1] = "indian19"; // ��������� �������
				itmq[1] = 1;
				nameitm[2] = "indian21"; // �������������� �����
				itmq[2] = 1;
				nameitm[3] = "indian22"; // ������ ����� ������� ����
				itmq[3] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 12000;
			break;
			case 4:
				nameitm[0] = "indian15"; // ����������� ������
				itmq[0] = 1;
				nameitm[1] = "indian17"; // ������� �������
				itmq[1] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 13000;
			break;
			case 5:
				nameitm[0] = "indian1"; // ������ ��������������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 27000;
			break;
			case 6:
				nameitm[0] = "indian2"; // �������� �������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 36000;
			break;
			case 7:
				nameitm[0] = "indian3"; // ���������� �����
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 25000;
			break;
			case 8:
				nameitm[0] = "indian5"; // ������� �����
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 24000;
			break;
			case 9:
				nameitm[0] = "indian6"; // ������ ���������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 14000;
			break;
			case 10:
				nameitm[0] = "indian7"; // ���� ������� ������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 15000;
			break;
			case 11:
				nameitm[0] = "indian12"; // �����-����� ������������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 16000;
			break;
			case 12:
				nameitm[0] = "indian14"; // ���� ��������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 17000;
			break;
			case 13:
				nameitm[0] = "indian18"; // ���� ������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 18000;
			break;
			case 14:
				nameitm[0] = "indian19"; // ��������� �������
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 19000;
			break;
			case 15:
				nameitm[0] = "indian21"; // �������������� �����
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 23000;
			break;
			case 16:
				nameitm[0] = "indian22"; // ������ ����� ������� ����
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 22000;
			break;
			case 17:
				nameitm[0] = "indian22"; // ������ ����� ������� ����
				itmq[0] = 1;
				nameitm[30] = "gold"; // ������
				itmq[30] = 21000;
			break;
		}
		itmq[30] += makeint(value/3);
		
        if (value >= 1 && value < 80) {nameitm[15] = "BackPack2"; itmq[15] = 1;}     		// ������� ������
        if (value_alt >= 80 && value_alt < 160) {nameitm[15] = "BackPack3"; itmq[15] = 1;}  // ������� ������
        if (value2 >= 160 && value2 < 240) {nameitm[15] = "BackPack4"; itmq[15] = 1;} 		// �������� ������
		
        if (value3 >= 240 && value3 < 320) {nameitm[15] = "cirass2"; itmq[15] = 1;}     	// ���������� �������
        if (value >= 320 && value < 400) {nameitm[15] = "cirass3"; itmq[15] = 1;}     		// ����������� ������
        if (value_alt >= 400 && value_alt < 480) {nameitm[15] = "cirass4"; itmq[15] = 1;}   // ���������� ������
		
        if (value2 >= 480 && value2 < 560) {nameitm[15] = "Totem_1"; itmq[15] = 1;}     	// ����� ����������
        if (value3 >= 560 && value3 < 640) {nameitm[15] = "Totem_2"; itmq[15] = 1;}     	// ����� ��������������
        if (value >= 640 && value < 720) {nameitm[15] = "Totem_3"; itmq[15] = 1;}     		// ����� ������������
        if (value_alt >= 720 && value_alt < 800) {nameitm[15] = "Totem_4"; itmq[15] = 1;}   // ����� ���������
        if (value2 >= 800 && value2 < 880) {nameitm[15] = "Totem_7"; itmq[15] = 1;}     	// ����� ������������
        if (value3 >= 880 && value3 < 999) {nameitm[15] = "Totem_8"; itmq[15] = 1;}     	// ����� �������
		
        if (value >= 1 && value < 40) {nameitm[16] = "blade19"; itmq[16] = 1;}     			// �������� ��
        if (value_alt >= 40 && value_alt < 80) {nameitm[16] = "blade22"; itmq[16] = 1;}     // ��������� ������ ��
        if (value2 >= 80 && value2 < 120) {nameitm[16] = "blade36"; itmq[16] = 1;}     		// ����������� ��
        if (value3 >= 120 && value3 < 160) {nameitm[16] = "blade37"; itmq[16] = 1;}     	// ���������� ����� ��
		
        if (value >= 160 && value < 200) {nameitm[16] = "blade31"; itmq[16] = 1;}     		// ������ ��
        if (value_alt >= 200 && value_alt < 240) {nameitm[16] = "blade34"; itmq[16] = 1;}   // ������� ��
        if (value2 >= 240 && value2 < 280) {nameitm[16] = "blade39"; itmq[16] = 1;}    		// �������� ��
        if (value3 >= 280 && value3 < 320) {nameitm[16] = "blade40"; itmq[16] = 1;}    		// ������� ��
        if (value >= 320 && value < 360) {nameitm[16] = "blade46"; itmq[16] = 1;}    		// ���������� ������� ��
		
        if (value_alt >= 360 && value_alt < 400) {nameitm[16] = "blade15"; itmq[16] = 1;}   // ������ ��
        if (value2 >= 400 && value2 < 440) {nameitm[16] = "blade21"; itmq[16] = 1;}    		// ������� ��
        if (value3 >= 440 && value3 < 480) {nameitm[16] = "blade202"; itmq[16] = 1;}     	// ���������� ��
        if (value >= 480 && value < 520) {nameitm[16] = "blade42"; itmq[16] = 1;}     		// ������ ��
        if (value_alt >= 520 && value_alt < 560) {nameitm[16] = "topor2"; itmq[16] = 1;}    // ���������� ����� ��
		
        if (value2 >= 560 && value2 < 600) {nameitm[16] = "blade23"; itmq[16] = 1;}       	// ������ ��
        if (value3 >= 600 && value3 < 640) {nameitm[16] = "blade32"; itmq[16] = 1;}     	// �������� ��
        if (value >= 640 && value < 680) {nameitm[16] = "blade26"; itmq[16] = 1;}     		// ������������ ��
		
        if (value_alt >= 680 && value_alt < 720) {nameitm[16] = "blade30"; itmq[16] = 1;}   // ������ ��
        if (value2 >= 720 && value2 < 760) {nameitm[16] = "blade24"; itmq[16] = 1;}     	// ������� ��
        if (value3 >= 760 && value3 < 800) {nameitm[16] = "blade25"; itmq[16] = 1;}     	// �������� ��
		
        if (value >= 800 && value < 840) {nameitm[16] = "blade13"; itmq[16] = 1;}     		// ��������� ��
        if (value_alt >= 840 && value_alt < 880) {nameitm[16] = "blade20"; itmq[16] = 1;}   // ������� ��
        if (value2 >= 880 && value2 < 920) {nameitm[16] = "blade33"; itmq[16] = 1;}     	// ���������� ����� ��
        if (value3 >= 920 && value3 < 999) {nameitm[16] = "blade28"; itmq[16] = 1;}     	// ����� ��
		
		if (value >= 1 && value < 150) {nameitm[17] = "pistol_grapebok"; 		itmq[17] = 1;} // ������������ ��������
		if (value_alt >= 200 && value_alt < 350) {nameitm[17] = "pistol6"; 		itmq[17] = 1;} // ���-��������
		if (value2 >= 400 && value2 < 550) {nameitm[17] = "pistol9"; 			itmq[17] = 1;} // ����������� ��������
		if (value3 >= 600 && value3 < 750) {nameitm[17] = "pistol4"; 			itmq[17] = 1;} // ��������������� ��������
		if (value >= 800 && value < 900) {nameitm[17] = "pistol5"; 				itmq[17] = 1;} // ���������� ��������
		if (value_alt >= 900 && value_alt < 950) {nameitm[17] = "mushket"; 		itmq[17] = 1;} // ��������� ������
		if (value >= 950 && value < 999) {nameitm[17] = "mushket_drob"; 		itmq[17] = 1;} // ��������
		
		if (value >= 10 && value < 30) {nameitm[18] = "mushket_spanish"; 			itmq[18] = 1;} // ��������� ��������
		if (value_alt >= 150 && value_alt < 170) {nameitm[18] = "mushket_english"; 	itmq[18] = 1;} // ���������� ��������
		if (value >= 600 && value < 620) {nameitm[18] = "mushket_france"; 			itmq[18] = 1;} // �������c��� ��������
		if (value_alt >= 900 && value_alt < 920) {nameitm[18] = "mushket_holland"; 	itmq[18] = 1;} // ����������� ��������
	}
	// LEO: ��� ���������. ��� �� � �������� ��������� ��� ������ ����� � ���������. � ��� ������ ������� ����� ����� �����������, ��� �� ��� ��� ������� ������. ������ �� ����. ���� �� �� �����, ������� �� ������ ��� ��� ������� ������� (� ��� ��� �������), ����� ��� ���� ������� ������������ � ������� ��� �� ���������, ����� �� �� ����� ��������� ��.
	// LEO: ��� �������, � ��� ���� ��� ������. ��� � 2013 ����, ����� � ������� �������� ��������� � ����� � ����� ��� ������ ���� � ������ ���� �������, ��� ����� ���� ��� �� �����. ������ ��� ��� ��� �� ������� ����� ������������ �������, ��������� �� ����� ��� ������. �� ���, ��� �� � ��� ���� �������� � ������ �������. ���� ��� ������� ��� � ����� ������-���������. �.�. � �� ��� � ���� � ���� ������ :)
	// LEO: �� � ��, ��� Gregg � �� ��� ������ ���� ������ ���������� � ���� ������ � ���� � �����. �� ��� �� �������� � �������� ��� ����������� ����.
	for (i = 0; i < 35; i++)
	{
		if (itmq[i] == 0) continue;
		if(nameitm[i] != "")
		{
			if(nameitm[i] == "gold") AddMoneyToCharacter(pchar, itmq[i]);
			else 
			{
		    	if(HasSubstr(nameitm[i], "blade"))TakeNItems(pchar, GetGeneratedItem(nameitm[i]), itmq[i]);
		    	else TakeNItems(pchar, nameitm[i], itmq[i]);
			}
			
			if(i == 0) nameitm[i] = "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " � ���������� " + itmq[i];
			else nameitm[i] = NewStr() + "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " � ���������� " + itmq[i];
		}
	}
	
	TakeNItems(pchar, "Lockpick", -1);
	EngineLayersOffOn(true);
	CreateTooltip("#" + "���������� �������", "�� ������� ������ � ����� ��������� ��������:", argb(255,255,255,255), "", argb(255,255,192,192), nameitm[0]+nameitm[1]+nameitm[2]+nameitm[3]+nameitm[4]+nameitm[5]+nameitm[6]+nameitm[7]+nameitm[8]+nameitm[9]+nameitm[10]+nameitm[11]+nameitm[12]+nameitm[13]+nameitm[14]+nameitm[15]+nameitm[16]+nameitm[17]+nameitm[18]+nameitm[19]+nameitm[20]+nameitm[21]+nameitm[22]+nameitm[23]+nameitm[24]+nameitm[25]+nameitm[26]+nameitm[27]+nameitm[28]+nameitm[29]+nameitm[30], argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
}

void ShowInfo()
{
	if(firsttime == false && opened == false)
	{
		g_bToolTipStarted = true;
		string sHeader = "TEST";
		string sNode = GetCurrentNode();

		string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
		sPicture = "none";
		sGroup = "none";
		sGroupPicture = "none";

		switch (sNode)
		{
			case "BACK_PIC":
				sHeader = "�������� ������";
				sText1 = "����� ������ ��������� ������� ��������� �������� �������, ����� ���������� �� ����������. �������� ������������ ����� ������� ����������� ��������� �������, ����������� � �������. ������� 'Ctrl' - ������� ��������. �������� ���� �� ��������� - ����� ���� ����������� �������. ������� 'Esc' - �����.");
				sText2 = "���������� ���� �����-����, ���������� ��������� �������. ����� �� ���� ������, ������� � ����������� ������� 'Ctrl' ��� ����, ����� ������ ������� �������. ��� �������� ����� ����������, ����� ������� ��� �������� �� 90 ��������."
				sText3 = "���� ������� � �������� �������� ���������� �����������, ��� ������, ��� ��������� ������� ������� �����������. � ���� ������, ��������� ������� 'Ctrl' � ���������, ����� ������� �������� � �������� ���������, ����� �������������� �������. �������, ��� ����� � ����������� ��������� �� ��������� �������, ��� �� ������� ���� ������� ����� ��������.";
			break;
		}

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfo()
{
	if(firsttime == false && opened == false)
	{
		if( g_bToolTipStarted ) 
		{
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("PICKSLIDE");
		}
	}
}

void ProcessCancelExit()
{
	if(openingstarted == false)
	{
		if(firsttime == false || opened == true)
		{
			CloseTooltip();
			IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
		}
		else
		{
			firsttime = false;
			pchar.questTemp.lockpicking.firsttime = false;
			CloseTooltip();
			SetCurrentNode("PICKSLIDE");
		}
	}
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");
	
	LAi_SetPlayerType(pchar);
	SetRealMouseSensitivity();

	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);
	
	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DeleteAttribute(pchar, "pause");
	DelPerkFromActiveList("TimeSpeed");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) 
	{
		DeleteEntitiesByType("scrshoter");
	}
	
	if((rand(99)+1) <= 10*(MOD_SKILL_ENEMY_RATE/2) && opened == false) //Korsar Maxim - ��������� ������. ���� ������� ������� ��� ������ ������
    {
	    TakeNItems(pchar, "Lockpick", -1);
	    PlaySound("interface\lockpicking\lockpick_breaks.wav"); // ���� �������
	    Log_info("�-�-���, ����! ������� ���������!");
	}
	else
	{
		if(broken)
		{
			TakeNItems(pchar, "Lockpick", -1);
			PlaySound("interface\lockpicking\lockpick_breaks.wav"); // ���� �������
			Log_info("�-�-���, ����! ������� ��������� �� ����� ������!");
		}
	}
	
	EndCancelInterface(bClear);
}

bool CheckSkull(string SkullId)
{
    if(CheckCharacterItem(pchar, "sculMa1") || CheckAttribute(pchar, "OwnsSkull1"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull1")) pchar.OwnsSkull1 = true;
		return true;
	}
    if(CheckCharacterItem(pchar, "sculMa2") || CheckAttribute(pchar, "OwnsSkull2"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull2")) pchar.OwnsSkull2 = true;
		return true;
	}
    if(CheckCharacterItem(pchar, "sculMa3") || CheckAttribute(pchar, "OwnsSkull3"))
	{
		if(!CheckAttribute(pchar, "OwnsSkull3")) pchar.OwnsSkull3 = true;
		return true;
	}
    return false;
}