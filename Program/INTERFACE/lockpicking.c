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
	
	PlaySound("interface\lockpicking\ui_lockpicking_enter_01.wav"); // Звук начала процедуры
	chestID = pchar.questTemp.lockpicking.ID;
	
	correctposition = 1+rand(179);
	
	if(correctposition < 15) correctposition = 15;
	if(correctposition > 165) correctposition = 165;
	
	sHeader = "Вскрытие замков";
	sText1 = "Взлом замков позволяет открыть некоторые закрытые сундуки, чтобы заполучить их содержимое. Вскрытие производится путем подбора правильного положения отмычки, вставленной в цилиндр. Клавиша 'Ctrl' - поворот цилиндра. Движение мыши по вертикали - смена угла вставленной отмычки. Клавиша 'Esc' - выход.");
	sText2 = "Передвигая мышь вверх-вниз, подбирайте положение отмычки. Когда ее угол выбран, нажмите и удерживайте клавишу 'Ctrl' для того, чтобы начать вращать цилиндр. Для открытия замка необходимо, чтобы цилиндр был повернут на 90 градусов."
	sText3 = "Если цилиндр в процессе вращения неожиданно остановился, это значит, что положение отмычки выбрано неправильно. В этом случае, отпустите клавишу 'Ctrl' и дождитесь, когда цилиндр вернется в исходное положение, чтобы разблокировать отмычку. Помните, чем ближе к правильному положению вы выставите отмычку, тем на больший угол цилиндр будет повернут.";
	
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
		
		if(XI_IsKeyPressed("control")) // Двигаем цилиндр, если нажата кнопка Ctrl
		{
			checkingstagenum = checkingstagenum + 4;
			
			if(cylinderstarted == false) // Звук начала поворота цилиндра
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = true;
			}
		}
		else // Если кнопка не нажата, то возвращаем в исходное положение
		{
			checkingstagenum = checkingstagenum - 4;
			
			if(cylinderstarted == true) // Звук начала поворота цилиндра
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
		
		if(checkingstagenum == 460) OpenProcedure(); // Если цилиндр повернут на 90 градусов, то запускаем процесс открытия
		
		if(checkingstagenum != 10 && checkingstagenum != 460 && checkingstagenum != makeint((1.0 - dmultiplier)*460.0)) // Поскрипывания цилиндра при его движении
		{
			if(rand(160) == 0)
			{
				squeaksound = rand(11)+1;
				
				if(squeaksound < 10) PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_0"+ squeaksound +".wav");
				else PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_"+ squeaksound +".wav");
			}
		}
		
		// Меняем визуальное положение цилиндра
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

void OpenProcedure() // Процесс открытия
{
	int randsound = rand(2)+1;
	
	openingstarted = true;
	PlaySound("interface\lockpicking\ui_lockpicking_unlock_0"+ randsound +".wav"); // Звук щелчка замка
}

void OpenChest()
{
	string nameitm[10];
	int itmq[10];
	
	int iRand;
	
	for (i = 0; i < 10; i++)
	{
		nameitm[i] = "";
	}
	
	if(chestID == "Chest") // Обычный сундук с монетами (ростовщик, клады)
	{
		TakeItemFromCharacter(pchar, chestID);
		
		if(rand(1) == 0)
		{
			nameitm[0] = "gold";
			itmq[0] = 12000 + rand(10)*1000;
		}
		else
		{
			nameitm[0] = "gold";
			itmq[0] = 6000 + rand(4)*1000;
			
			if(rand(2) == 0)
			{
				nameitm[1] = "jewelry1";
				itmq[1] = 1 + rand(9);
			}
			
			if(rand(2) == 0)
			{
				nameitm[2] = "jewelry2";
				itmq[2] = 1 + rand(2);
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					if(rand(1) == 0)
					{
						nameitm[4] = "jewelry4";
						itmq[4] = 1 + rand(4);
					}
					else
					{
						nameitm[4] = "jewelry3";
						itmq[4] = 1 + rand(6);
					}
				}
				else
				{
					nameitm[4] = "jewelry17";
					itmq[4] = 1 + rand(40);
				}
			}
		}
	}
	
	if(chestID == "Chest_ammo") // Оруженый сундук
	{
		TakeItemFromCharacter(pchar, chestID);
		
		if(rand(1) == 0)
		{
			nameitm[0] = RandPhraseSimple(RandPhraseSimple("blade5","pistol1"),RandPhraseSimple("pistol2","pistol3"));
			itmq[0] = 0;
			
			if(pchar.rank >= 15 && rand(6) == 1)
			{
		    	nameitm[1] = "pistol6";
		    	itmq[1] = 1;
			}
			else
			{
				if(rand(6) == 2)
				{
			    	nameitm[1] = RandPhraseSimple(RandPhraseSimple("blade5","pistol1"),RandPhraseSimple("pistol2","pistol3"));
			        itmq[1] = 1;
				}
			}
		}
		else
		{
			iRand = 30 + rand(20);
			
			nameitm[0] = "bullet";
			itmq[0] = iRand;
			
			nameitm[1] = "gunpowder";
			itmq[1] = iRand;
			
			if(rand(2) == 0)
			{
				nameitm[2] = "potion1";
				itmq[2] = 3 + rand(3);
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					if(rand(1) == 0)
					{
						nameitm[3] = "potion2";
						itmq[3] = 2 + rand(2);
					}
					else
					{
						nameitm[3] = "jewelry3";
						itmq[3] = 2 + rand(6);
					}
				}
				else
				{
					nameitm[3] = "jewelry17";
					itmq[3] = 1 + rand(40);
				}
			}
		}
	}	
	
	if(chestID == "Chest_treasure") // Малый сундук
	{
		TakeItemFromCharacter(pchar, chestID);
		
		if(rand(1) == 0)
		{
			nameitm[0] = "gold";
			itmq[0] = 22000 + rand(10)*2000;
		}
		else
		{
			nameitm[0] = "gold";
			itmq[0] = 10000 + rand(4)*2000;
			
			if(rand(1) == 0)
			{
				nameitm[1] = "jewelry5";
				itmq[1] = 21 + rand(9);
			}
			
			if(rand(2) == 0)
			{
				nameitm[2] = "jewelry2";
				itmq[2] = 11 + rand(2);
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					if(rand(1) == 0)
					{
						nameitm[4] = "jewelry4";
						itmq[4] = 26 + rand(4);
					}
					else
					{
						nameitm[4] = "jewelry3";
						itmq[4] = 24 + rand(6);
					}
				}
				else
				{
					nameitm[4] = "jewelry17";
					itmq[4] = 15 + rand(45);
				}
			}
		}
	}
	
	if(chestID == "Chest_quest") // Квестовый сундук
	{
		iRand = rand(6);
		
		TakeItemFromCharacter(pchar, chestID);
		
		if(rand(1) == 0)
		{
			nameitm[0] = "gold";
			itmq[0] = 50000 + rand(10)*2500;
		}
		else
		{
			nameitm[0] = "gold";
			itmq[0] = 6000 + rand(4)*1000;
			
			if(iRand == 1)
			{
				nameitm[1] = "pistol6";
				itmq[1] = 1;
			}
			if(iRand == 4)
			{
				nameitm[2] = "pistol5";
				itmq[2] = 1;
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					if(rand(1) == 0)
					{
						if(!CheckSkull("Sculma3"))
						{
					    	nameitm[4] = "Sculma3";
				    		itmq[4] = 1;
						}
						else
						{
							nameitm[4] = "indian20";
				    		itmq[4] = 1;
						}
					}
					else
					{
						nameitm[4] = "indian21";
						itmq[4] = 1;
					}
				}
				else
				{
					nameitm[4] = "indian22";
					itmq[4] = 1;
				}
			}
		}
	}
	
	for (i = 0; i < 10; i++)
	{
		if(nameitm[i] != "")
		{
			if(nameitm[i] == "gold") AddMoneyToCharacter(pchar, itmq[i]);
			else 
			{
		    	if(HasSubstr(nameitm[i], "blade"))TakeNItems(pchar, GetGeneratedItem(nameitm[i]), itmq[i]);
		    	TakeNItems(pchar, nameitm[i], itmq[i]);
			}
			
			if(i == 0) nameitm[i] = "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " в количестве " + itmq[i];
			else nameitm[i] = NewStr() + "- " + GetConvertStr("itmname_"+nameitm[i], "ItemsDescribe.txt") + " в количестве " + itmq[i];
		}
	}
	
	TakeNItems(pchar, "Lockpick", -1);
	EngineLayersOffOn(true);
	CreateTooltip("#" + "Содержимое сундука", "Вы открыли сундук и нашли следующие предметы:", argb(255,255,255,255), "", argb(255,255,192,192), nameitm[0]+nameitm[1]+nameitm[2]+nameitm[3]+nameitm[4]+nameitm[5]+nameitm[6]+nameitm[7]+nameitm[8]+nameitm[9], argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
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
				sHeader = "Вскрытие замков";
				sText1 = "Взлом замков позволяет открыть некоторые закрытые сундуки, чтобы заполучить их содержимое. Вскрытие производится путем подбора правильного положения отмычки, вставленной в цилиндр. Клавиша 'Ctrl' - поворот цилиндра. Движение мыши по вертикали - смена угла вставленной отмычки. Клавиша 'Esc' - выход.");
				sText2 = "Передвигая мышь вверх-вниз, подбирайте положение отмычки. Когда ее угол выбран, нажмите и удерживайте клавишу 'Ctrl' для того, чтобы начать вращать цилиндр. Для открытия замка необходимо, чтобы цилиндр был повернут на 90 градусов."
				sText3 = "Если цилиндр в процессе вращения неожиданно остановился, это значит, что положение отмычки выбрано неправильно. В этом случае, отпустите клавишу 'Ctrl' и дождитесь, когда цилиндр вернется в исходное положение, чтобы разблокировать отмычку. Помните, чем ближе к правильному положению вы выставите отмычку, тем на больший угол цилиндр будет повернут.";
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
	
	if((rand(99)+1) <= 10*(MOD_SKILL_ENEMY_RATE/2) && opened == false) //Korsar Maxim - доработка взлома. Шанс поломки отмычки при отмене взлома
    {
	    TakeNItems(pchar, "Lockpick", -1);
	    PlaySound("interface\lockpicking\lockpick_breaks.wav"); // Звук поломки
	    Log_info("А-а-ать, Черт! Отмычка сломалась!");
	}
	else
	{
		if(broken)
		{
			TakeNItems(pchar, "Lockpick", -1);
			PlaySound("interface\lockpicking\lockpick_breaks.wav"); // Звук поломки
			Log_info("А-а-ать, Черт! Отмычка сломалась во время взлома!");
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