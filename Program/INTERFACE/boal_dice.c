// boal 10.06.05
//   DICE GAME
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start;
bool openExit;
int  money_i, moneyOp_i;
string money_s;
//Fix per Dmitry
bool bDice1Open = true;
bool bDice2Open = true;
bool bDice3Open = true;
bool bDice4Open = true;
bool bDice5Open = true;

ref npchar;

int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;
int iHeroLose, iHeroWin;
int iTurnGame; // count for time

object  DiceState;

bool  bLockClick;
bool  bSetRandDice; // ����� �����

string ResultStr;

void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eContinueGame","ContinueGame",0);
	SetEventHandler("My_eNewNextGame","NewNextGame",0);
	SetEventHandler("My_eCompTurn","CompTurn",0);
	SetEventHandler("My_eCheckGame","CheckGame",0);
	/*
	gold, silver   - 100x100
	screen: -40..680 x -30..510  (720x540)
	cup: 219x178
	dice: 92x84
	������� (� �������� �������� ����������)
	1) ����� - 5 ����������
	2) ����� ���.����� - 2,3,4,5,6 ���.����� - 1,2,3,4,5
	3) ���� - 4 ����������
	4) ��� - 3 + 2
	5) ������ - 3 ����������
	6) ��� ���� 2 + 2
	7) ���� ���� 2- ����������
	8) ������ ���
	*/
	
    sgxy = 50;
    ssxy = 70;
    
    scx = 82;
    scy = 77;
    
    spx = 274;
    spy = 222;
    
    openExit = false;  // ����� �� �������� ����
    
    pchar = GetMainCharacter();
    
    iRate  = sti(pchar.GenQuest.Dice.iRate); // ������ �������
    
    npchar = GetCharacter(sti(pchar.GenQuest.Dice.npcharIdx));
    
  /*  switch (iRate)
    {
        case 50 :
            money_s = "silver";
            iExpRate = 1;
        break;
        
        case 200 :
            money_s = "gold";
            iExpRate = 2;
        break;
        
        case 500 :
            money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\sith\card_sukno.tga");
            iExpRate = 4;
        break;

        case 2000 :
            money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\sith\card_sukno.tga");
            iExpRate = 8;
        break;
    } */
	
	if (iRate <= 99)            //WW  �������� �������  �� ����� ������
         {   money_s = "silver";  
            iExpRate = 1;
	     } 		
       if (iRate > 100)
         {    money_s = "silver";
            iExpRate = 2;          
          } 
		
		 if (iRate > 250)
          {   money_s = "silver";
            iExpRate = 3;
          } 
		
		  if (iRate > 500)
         {   money_s = "silver";
            iExpRate = 4;
         } 

           if (iRate > 1000)
         {    money_s = "gold";
            iExpRate = 5;
         } 

            if (iRate > 2000)
         {    money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\sith\card_sukno.tga");
            iExpRate = 6;
         } 
		
		  if (iRate > 5000)
         {    money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\sith\card_sukno.tga");
            iExpRate = 8;
         } 

           if (iRate > 10000)
         {    money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\sith\card_sukno.tga");
            iExpRate = 10;
         } 
		 
    if (money_s == "gold")
    {
        smxy = sgxy;
    }
    else
    {
        smxy = ssxy;
    }
	CreateImage("DiceCup","DICE","cup", 460, 40, 460 + spx, 40 + spy); // ���� ����
	
	CreateImage("GOLD","GOLD","GOLD", 482,444,524,486);
	
	SetNewPicture("ICON_1", "interfaces\PORTRAITS\64\face_" + Npchar.faceId+ ".tga");
    SetNewPicture("ICON_2", "interfaces\PORTRAITS\64\face_" + pchar.faceId+ ".tga");
    
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY,613,508,SCRIPT_ALIGN_CENTER,1.1);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,452,SCRIPT_ALIGN_CENTER,1.3);
    
    if (rand(1) == 1)
    {
        dir_i  = -1;  // ��� ����� - ����
    }
    else
    {
        dir_i  = 1;  // ��� ����� - ��
    }
    dir_i_start = dir_i; // �������� ��� �����
    
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 250, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_DiceN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 170, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_DiceP", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 465, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_TXT", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 555, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 555, SCRIPT_ALIGN_LEFT,1.0);
    iHeroLose = 0;
    iHeroWin  = 0;
    iTurnGame = 1;
    // ����� ����
    NewGameBegin(true);
}

void ProcessBreakExit()
{
	Exit();
}

void ProcessCancelExit()
{
	Exit();
}

void Exit()
{
    if (openExit || bBettaTestMode)
    {
        DelEventHandler("InterfaceBreak","ProcessBreakExit");
    	DelEventHandler("exitCancel","ProcessCancelExit");
    	DelEventHandler("ievnt_command","ProcessCommandExecute");
    	DelEventHandler("My_eventMoveImg","MoveImg");
    	DelEventHandler("My_eStartGame","StartGame");
    	DelEventHandler("My_eContinueGame","ContinueGame");
    	DelEventHandler("My_eNewNextGame","NewNextGame");
    	DelEventHandler("My_eCompTurn","CompTurn");
    	DelEventHandler("My_eCheckGame","CheckGame");

        if (sti(pchar.GenQuest.Dice.SitType) == true)
    	{
            DoQuestCheckDelay("exit_sit", 0.6);
    	}
        interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

    	Statistic_AddValue(Pchar, "GameDice_Win", iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*4*iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
    	Statistic_AddValue(Pchar, "GameDice_Lose", iHeroLose);
		NPChar.Quest.HeroLose = (iHeroWin < iHeroLose); //navy -- � ����� �������� ��� �������. (�� �� �������.)

    	bQuestCheckProcessFreeze = true;
    	WaitDate("",0,0,0, 0, iTurnGame*15);
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
    	EndCancelInterface(true);

	}
	else
    {
        PlaySound("interface\knock.wav");
    }

}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

    if (bLockClick) return;
    
	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   // ��� ���� ����
                	dir_i = -dir_i_start;
                	dir_i_start = dir_i;
                    ClearDiceOnTable();
                    iTurnGame++;
                    NewGameBegin(true);
                }
                else
                {
					// �� ������������� ����� �������
					// �� ������� ������ ������ ��� �������
					if (dir_i == 1 && CheckCupForDice())
					{
                        bLockClick = true;
						move_i = 0;
				        PlaySound("interface\dice_mix.wav");
						PostEvent("My_eventMoveImg", 100);
					}
					else
					{
					    PlaySound("interface\knock.wav");
					}
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
				if (dir_i_start == 1 && bStartGame == 2)  // ������� ����
				{
				    CheckGame();
				    break;
				}
				if (dir_i_start == -1 && bStartGame == 3)  // ������� ����
				{
				    CheckGame();
				    break;
				}
				PlaySound("interface\knock.wav");
    		}
    	break;
    	
    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                //PlaySound("interface\knock.wav");
    		}
    	break;
    	
    	case "B_HeroDice1":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(1, bDice1Open);
    		}
    	break;
    	
    	case "B_HeroDice2":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(2, bDice2Open);
    		}
    	break;
    	case "B_HeroDice3":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(3, bDice3Open);
    		}
    	break;
    	case "B_HeroDice4":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(4, bDice4Open);
    		}
    	break;
    	case "B_HeroDice5":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(5, bDice5Open);
    		}
    	break;
	}
}

void MoveImg()
{
    move_i++;
    if (move_i < 10)
    {
        CreateImage("DiceCup","DICE","cup", 460 - move_i*25, 40 + move_i*15, 460 - move_i*25 + spx, 40 +move_i*15 + spy);
        PostEvent("My_eventMoveImg", 100);
    }
    else
    {
        if (move_i <= 20)
        {
            CreateImage("DiceCup","DICE","cup", 460 - (20 - move_i)*25, 40 + (20 - move_i)*15, 460 - (20 - move_i)*15 + spx, 40 +(20 - move_i)*25 + spy);
            
            if (move_i == 20) // ��� - ������� ������ � ������
			{
            	PostEvent("My_eventMoveImg", 2000);
            }
			else
			{
            	PostEvent("My_eventMoveImg", 100);
            }
        }
        // �����
        if (move_i == 12)
        {
            PlaySound("interface\dice_end.wav");
			if (bSetRandDice)
			{
            	SetDiceForTableRand(); // ��������, 2� ��� ����� ����� �������!!!
            }
            else
            {
                bSetRandDice = true;
            }
            PutDiceOnTable();
        }
		// ��� - ������� ������ � ������
        if (move_i == 21)
        {
            SetLineAfterDeck();
        }
    }
}

void PutNextCoin()
{
    CreateImage("Money_"+money_i,"CARDS",money_s, 530+money_i*3, 310-money_i*3, 530+money_i*3 + smxy, 310-money_i*3 + smxy);
}
void PutNextCoinOp()
{
    CreateImage("Money_"+(28+moneyOp_i),"CARDS",money_s, 630+moneyOp_i*3, 310-moneyOp_i*3, 630+moneyOp_i*3 + smxy, 310-moneyOp_i*3 + smxy);
}

void RedrawDeck(bool _newGame, bool _clearDice)
{
    // ������� � �������
    int i;
    if (_newGame)
    {
	    for (i=55; i>=0; i--)
		{
	        CreateImage("Money_"+i,"","", 0, 0, 0, 0);
		}
		money_i = 0; // ������ �������
	    moneyOp_i = 0;
	    iChest = 0; // �� ����
    }
	// ����� ��� ������
	if (_clearDice)
	{
		CreateImage("HeroDice1","DICE","", 60, 486, 60 + scx, 486 + scy);
		CreateImage("HeroDice2","DICE","",  140, 486,  140 + scx, 486 + scy);
		CreateImage("HeroDice3","DICE","", 220, 486, 220 + scx, 486 + scy);
		CreateImage("HeroDice4","DICE","", 300, 486, 300 + scx, 486 + scy);
		CreateImage("HeroDice5","DICE","", 380, 486, 380 + scx, 486 + scy);

		CreateImage("CompDice1","DICE","", 60, 42, 60 + scx, 42 + scy);
		CreateImage("CompDice2","DICE","",  140, 42,  140 + scx, 42 + scy);
		CreateImage("CompDice3","DICE","", 220, 42, 220 + scx, 42 + scy);
		CreateImage("CompDice4","DICE","", 300, 42, 300 + scx, 42 + scy);
		CreateImage("CompDice5","DICE","", 380, 42, 380 + scx, 42 + scy);
    }
    iMoneyP = sti(pchar.Money);
    iMoneyN = sti(npchar.Money);
    ShowMoney();
    
    SetNextTip();
    BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
    }
    else
    {
    }
}

void BetaInfo()
{
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_MoneyN = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_DiceN  = "Beta_DiceN Type: " + DiceState.Comp.Result.Type + " Rate1: " + DiceState.Comp.Result.Rate1 + " Rate2: " +DiceState.Comp.Result.Rate2;
        GameInterface.strings.Beta_DiceP  = "Beta_DiceP Type: " + DiceState.Hero.Result.Type + " Rate1: " + DiceState.Hero.Result.Rate1 + " Rate2: " +DiceState.Hero.Result.Rate2;
        GameInterface.strings.Beta_TXT    = "dir_i_start " + dir_i_start + " dir_i " + dir_i + " Position " + bStartGame;
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameDice_Win", 0) + iHeroWin)+ " Lose " + (Statistic_AddValue(Pchar, "GameDice_Lose", 0) + iHeroLose)+ " Turn " + iTurnGame;
		if (CheckAttribute(NPchar, "Quest.DiceCheats")) GameInterface.strings.Beta_WinLose = GameInterface.strings.Beta_WinLose + " Cheats " + NPchar.Quest.DiceCheats;
    }
}

// ����� �����
void StartGame()
{
	int i;
	move_i = 0;

    PlaySound("interface\took_item.wav");
	if (dir_i == -1) // ���� ������
	{
        PlaySound("interface\dice_mix.wav");
		SetFormatedText("INFO_TEXT","� ������.");
		PostEvent("My_eventMoveImg", 100);
    }
	else
	{
	    SetFormatedText("INFO_TEXT","�� ����"+ GetSexPhrase("��","��") +". ����, �� ����������.");
	    bLockClick = false;
	}
	// ��� ������
	for (i=0; i<5; i++)
	{
		PutNextCoin();
        money_i++;
        iMoneyP = iMoneyP - iRate;
    }
    for (i=0; i<5; i++)
	{
		PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
	}
    iChest += 10*iRate;
    PlaySound("interface\took_item.wav");
    ShowMoney();
}

void ShowMoney()
{
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

void NewGameBegin(bool _newGame)
{
    InitDiceState();
	RedrawDeck(_newGame, true); // ����� ����
    bStartGame = 0;
    if (_newGame)
    {
    	SetFormatedText("INFO_TEXT","�������� ����. "+NewStr()+"������ ������.");
    }
    else
    {
        SetFormatedText("INFO_TEXT","���������� ����. "+NewStr()+"������ ������.");
    }
    bSetRandDice = true;
    PostEvent("My_eStartGame", 1000);
    bLockClick = true;
    openExit = false;
    BetaInfo();
    //Fix per Dmitry
    bDice1Open = true;
    bDice2Open = true;
    bDice3Open = true;
    bDice4Open = true;
    bDice5Open = true;
}
// ������ � ������
void EndGameCount(int who)
{
    //openExit = true;
    if (who == 1) // ��
    {
        AddMoneyToCharacter(pchar, iChest - (sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar,  -(sti(npchar.Money) - iMoneyN));
    }
    if (who == -1)
    {
        AddMoneyToCharacter(pchar, -(sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar, iChest - (sti(npchar.Money) - iMoneyN));
    }
    if (who == 0)// �����
    {
        AddMoneyToCharacter(pchar, -(sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar, -(sti(npchar.Money) - iMoneyN));
    }
    iMoneyP = sti(pchar.Money);
    iMoneyN = sti(npchar.Money);
}

// ��������� ������ ��� ���� ����
bool CheckNextGame()
{
    bool ret = true;
    if (iRate*6 > iMoneyN) ret = false;
    if (iRate*6 > iMoneyP) ret = false;
    
    return ret;
}

void PutDiceOnTable()
{
    int ix, iy;
    if (DiceState.Desk.d1.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice1","DICE","dice_"+DiceState.Desk.d1+"_" + rand(2), 160+ix, 180+iy, 160 +ix+ + scx, 180 +iy+ scy);
    }
    if (DiceState.Desk.d2.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice2","DICE","dice_"+DiceState.Desk.d2+"_" + rand(2), 280+ix, 150+iy, 280 +ix+ + scx, 150 +iy+ scy);
	}
	if (DiceState.Desk.d3.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice3","DICE","dice_"+DiceState.Desk.d3+"_" + rand(2), 150+ix, 280+iy, 150 +ix+ + scx, 280 +iy+ scy);
	}
	if (DiceState.Desk.d4.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice4","DICE","dice_"+DiceState.Desk.d4+"_" + rand(2), 260+ix, 310+iy, 260 +ix+ + scx, 310 +iy+ scy);
    }
    if (DiceState.Desk.d5.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice5","DICE","dice_"+DiceState.Desk.d5+"_" + rand(2), 350+ix, 260+iy, 350 +ix+ + scx, 260 +iy+ scy);
    }
}

void ClearDiceOnTable()
{
    CreateImage("Dice1","","", 0, 0, 0, 0);
    CreateImage("Dice2","","", 0, 0, 0, 0);
    CreateImage("Dice3","","", 0, 0, 0, 0);
    CreateImage("Dice4","","", 0, 0, 0, 0);
    CreateImage("Dice5","","", 0, 0, 0, 0);
}

void InitDiceState()
{
	DeleteAttribute(&DiceState, "");
	
	DiceState.Desk.d1 = "";
    DiceState.Desk.d2 = "";
    DiceState.Desk.d3 = "";
    DiceState.Desk.d4 = "";
    DiceState.Desk.d5 = "";
    
    DiceState.Desk.d1.Mix = true; //�����
    DiceState.Desk.d2.Mix = true;
    DiceState.Desk.d3.Mix = true;
    DiceState.Desk.d4.Mix = true;
    DiceState.Desk.d5.Mix = true;
    
    DiceState.Hero.d1 = "";
    DiceState.Hero.d2 = "";
    DiceState.Hero.d3 = "";
    DiceState.Hero.d4 = "";
    DiceState.Hero.d5 = "";
    DiceState.Hero.Result.Type  = ""; // ��� ����������
    DiceState.Hero.Result.Rate1 = ""; // �������� ������� ����
    DiceState.Hero.Result.Rate2 = "";
    
    DiceState.Hero.d1.Mix = false;
    DiceState.Hero.d2.Mix = false;
    DiceState.Hero.d3.Mix = false;
    DiceState.Hero.d4.Mix = false;
    DiceState.Hero.d5.Mix = false;
    
    DiceState.Comp.d1 = "";
    DiceState.Comp.d2 = "";
    DiceState.Comp.d3 = "";
    DiceState.Comp.d4 = "";
    DiceState.Comp.d5 = "";
    DiceState.Comp.Result.Type  = ""; // ��� ����������
    DiceState.Comp.Result.Rate1 = ""; // �������� ������� ����
    DiceState.Comp.Result.Rate2 = ""; // �������� ������� ���� (���� ����, ��� ��������� ��� � ��� ����, ����� ������� �����)
    DiceState.Comp.Result.d1 = ""; // 1-6 ����� �����
    
    DiceState.Comp.d1.Mix = false;
    DiceState.Comp.d2.Mix = false;
    DiceState.Comp.d3.Mix = false;
    DiceState.Comp.d4.Mix = false;
    DiceState.Comp.d5.Mix = false;
}

void ClickHeroDice(int d, bool isfree)
{
	if (bLockClick) return;
	if (bStartGame < 2 || bStartGame > 3)  return;
	//Fix per Dmitry
	switch(d)
    {
        case 1: bDice1Open = false; break;
        case 2: bDice2Open = false; break;
        case 3: bDice3Open = false; break;
        case 4: bDice4Open = false; break;
        case 5: bDice5Open = false; break;
    }
	if (iMoneyP >= iRate && isfree)
	{
		CreateImage("HeroDice" + d ,"","", 0,0,0,0);
		sGlobalTemp = "d"+d;
		DiceState.Hero.(sGlobalTemp).Mix = true;
		DiceState.Desk.(sGlobalTemp).Mix = true;
		PutNextCoin();
	    money_i++;
	    iMoneyP = iMoneyP - iRate;
	    iChest += iRate;
	    PlaySound("interface\took_item.wav");
	    ShowMoney();
    }
    else
    {
        PlaySound("interface\knock.wav");
    }
}

void SetLineAfterDeck()
{
    int i;
    ClearDiceOnTable();

	if (dir_i == -1) // ���� ������
	{
        for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (DiceState.Desk.(sGlobalTemp).Mix == true)
	        {
	            DiceState.Comp.(sGlobalTemp)     = DiceState.Desk.(sGlobalTemp);
	            DiceState.Comp.(sGlobalTemp).Mix = false;
	            if (bStartGame >0 ) DiceState.Desk.(sGlobalTemp).Mix = false;

			}
		}
		SortDiceOnHand("Comp");
		RecalcDiceOnHand("Comp");
		RecalcAIDice("Comp");
		PutCompLine();
	}
	else
	{
        for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (DiceState.Desk.(sGlobalTemp).Mix == true)
	        {
	            DiceState.Hero.(sGlobalTemp)     = DiceState.Desk.(sGlobalTemp);
	            DiceState.Hero.(sGlobalTemp).Mix = false;
	            if (bStartGame >0) DiceState.Desk.(sGlobalTemp).Mix = false;
			}
		}
		SortDiceOnHand("Hero");
		RecalcDiceOnHand("Hero");
		RecalcAIDice("Hero");
		PutHeroLine();
	}
	CheckGame();
}

bool CheckGame()
{
    int i;

	if (dir_i == -1) // ���� ������
	{
		dir_i = 1;
		bLockClick = false;
		if (bStartGame <1 )// ������ �����
		{
			SetFormatedText("INFO_TEXT","������ ���� ���. ����, �� ����������.");
		}
		else
		{
			SetFormatedText("INFO_TEXT","����� ���� �����. �����, ��� �����������.");
		}
	}
	else
	{
        dir_i = -1;
        bLockClick = true;
		if (bStartGame <1 )// ������ �����
		{
			SetFormatedText("INFO_TEXT","���, ������ ��� ���.");
			move_i = 0;
	        PlaySound("interface\dice_mix.wav");
	        PostEvent("My_eventMoveImg", 500);
        }
        else
        {
			if (bStartGame <3)
			{
				// ������ ������ �� ������
	            SetFormatedText("INFO_TEXT","���, �������... � �����, ��� �����������.");
	            PostEvent("My_eCompTurn", 800);
            }
        }
	}
	bStartGame++;
	if (bStartGame > 3)
	{
		// ������ �����
		openExit = false;
		bLockClick = true;
		if (EndTurnGame())
		{
			PostEvent("My_eNewNextGame", 2000);
		}
		else
		{
			PostEvent("My_eContinueGame", 3500);
		}
	}
	BetaInfo();
	return true;
}

void PutCompLine()
{
	int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (DiceState.Comp.(sGlobalTemp).Mix == false)
        {
			CreateImage("CompDice" + i,"DICE","dice_" + DiceState.Comp.(sGlobalTemp) + "_1", 60 + 80*(i-1), 42, 60 + 80*(i-1) + scx, 42 + scy);
		}
	}
}

void PutHeroLine()
{
	int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (DiceState.Hero.(sGlobalTemp).Mix == false)
        {
			CreateImage("HeroDice" + i,"DICE","dice_" + DiceState.Hero.(sGlobalTemp) + "_1", 60 + 80*(i-1), 486, 60 + 80*(i-1) + scx, 486 + scy);
		}
	}
}

bool CheckCupForDice()
{
    int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.Desk.(sGlobalTemp).Mix) == true)
        {
            return true;
		}
	}
	return false;
}
// ��������� ����������
void RecalcDiceOnHand(string _whom)
{
	int    i, k, iOk;
	string sTemp;
	bool   ok;
	// 1) ����� - 5 ����������
	ok = true;
	for (i = 2; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.(_whom).d1) != sti(DiceState.(_whom).(sGlobalTemp)))
        {
            ok = false;
            break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = 1;
        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).d1);
        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).d1);
		return;
	}
    // 2) ����� ���.����� - 2,3,4,5,6 ���.����� - 1,2,3,4,5
	ok = true;
	for (i = 1; i<=4; i++)
	{
        sGlobalTemp = "d"+i;
        sTemp       = "d"+(i+1);
        if (sti(DiceState.(_whom).(sGlobalTemp)) != (sti(DiceState.(_whom).(sTemp)) - 1) )
        {
            ok = false;
            break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = 2;
        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).d5);
        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).d5);
		return;
	}
	// 3) ���� - 4 ����������
	ok = true;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 4)
		{
	        DiceState.(_whom).Result.Type  = 3;
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp));
			return;
		}
	}
	// 4) ��� - 3 + 2
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 3)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
	    ok = false;
	    for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate1)) continue;
			
			for (i = 1; i<=5; i++)
			{
		        sGlobalTemp = "d"+i;
		        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
		        {
		            iOk--;
				}
			}
		 	if (iOk >= 2)
			{
		        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp));
		        ok = true;
		        break;
			}
		}
	}
 	if (ok)
	{
        DiceState.(_whom).Result.Type  = 4;
		return;
	}
	// 5) ������ - 3 ����������
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 3)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = 5;
        DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 6) ��� ���� 2 + 2
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 2)
		{
	        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp)); // �������
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
	    ok = false;
	    for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate2)) continue;

			for (i = 1; i<=5; i++)
			{
		        sGlobalTemp = "d"+i;
		        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
		        {
		            iOk--;
				}
			}
		 	if (iOk >= 2)
			{
		        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp)); // �������
		        ok = true;
		        break;
			}
		}
	}
 	if (ok)
	{
        DiceState.(_whom).Result.Type  = 6;
		return;
	}
	// 7) ���� ���� 2- ����������
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 2)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = 7;
        DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 8) ������ ���
	DiceState.(_whom).Result.Type  = 8;
    DiceState.(_whom).Result.Rate1 = 0;
	DiceState.(_whom).Result.Rate2 = 0;
}
// ��������� �� �����������, ����� ��� ������������ � ��������� ���������� ����������
void SortDiceOnHand(string _whom)
{
    int  j,k,w,m;
    string sTemp;
    /*
	����� ����������� (������� �����).

  ��� ������ ������� ������� ���������� ������� � ������ ��� �� ������ �����,
����� ���������� �� ����������...
	*/
	
	for (k = 1; k<=4; k++)
	{
        sGlobalTemp = "d"+k;
        w = sti(DiceState.(_whom).(sGlobalTemp));
		j = k;
		for (m = k+1; m<=5; m++)
		{
            sGlobalTemp = "d"+m;
			if (sti(DiceState.(_whom).(sGlobalTemp)) < w)
			{
			    j = m;
			    w = sti(DiceState.(_whom).(sGlobalTemp));
			}
		}
		sGlobalTemp = "d"+j;
		sTemp       = "d"+k;
		DiceState.(_whom).(sGlobalTemp) = DiceState.(_whom).(sTemp);
		DiceState.(_whom).(sTemp) = w;
	}
}
// ��������� ����������
int GetResult()
{
	if (sti(DiceState.Hero.Result.Type) < sti(DiceState.Comp.Result.Type))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Type) > sti(DiceState.Comp.Result.Type))
	{
	    return -1;
	}
	if (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Rate1) < sti(DiceState.Comp.Result.Rate1))
	{
	    return -1;
	}
	if (sti(DiceState.Hero.Result.Rate2) > sti(DiceState.Comp.Result.Rate2))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Rate2) < sti(DiceState.Comp.Result.Rate2))
	{
	    return -1;
	}
	return 0; // �����
}


bool EndTurnGame()
{
    string sTemp;
    int   ok = 0;
    bool  ret = true;

	ok = GetResult();
	sTemp = "� ���� " + GetTypeName(sti(DiceState.Comp.Result.Type)) + ". � ���� " + GetTypeName(sti(DiceState.Hero.Result.Type)) + ".";
    if (ok == 0)
    {
        sTemp += NewStr() + "��! �� � ��� �����!! ���������.";
		ret = false;
    }
    if (ok == -1)
    {
        sTemp += NewStr() + "� �������.";
        iHeroLose++;
    }
    if (ok == 1)
    {
        sTemp += NewStr() +  RandSwear() + "�� �������"+ GetSexPhrase("","�") +".";
        iHeroWin++;
    }
    EndGameCount(ok);
    ResultStr = sTemp;
    SetFormatedText("INFO_TEXT", sTemp);
    return ret;
}

void ContinueGame()
{
	if (CheckNextGame())
	{
		dir_i       = -dir_i_start;
	    dir_i_start = dir_i;
		NewGameBegin(false);
	}
	else
	{
        if (iRate*6 > iMoneyP)
    	{
    	    ResultStr = "�� �� ����, � �������!" + NewStr() + "���, � ���� ������!";
			SetFormatedText("INFO_TEXT",ResultStr);
    	    EndGameCount(-1);
    	    iHeroLose++;
    	}
		else//if (iRate*6 > iMoneyN)
	    {
	        ResultStr = "� �� ����, �� �������"+ GetSexPhrase("","�") +"!" + NewStr() + "���, � ���� ������!";
	        SetFormatedText("INFO_TEXT",ResultStr);
	        EndGameCount(1);
	        iHeroWin++;
	    }
     	RedrawDeck(true, true);
		openExit = true;
	    bLockClick = true;
	}
}

void NewNextGame()
{
    RedrawDeck(true, false);
    openExit = true;
	if (CheckNextGame() && rand(10) < 10) // ���� ������ �� ����
    {
        ResultStr += NewStr() + "��� �����?";
		bLockClick = false;
	}
	else
	{
        ResultStr += NewStr() + "���, � ���� ������!";
		bLockClick = true;
	}
	SetFormatedText("INFO_TEXT",ResultStr);
}

string GetTypeName(int _type)
{
	string ret = "������ ���";
	
	switch (_type)
	{
	    case 1:
	        ret = "�����";
	    break;
	    
	    case 2:
	        ret = "�����";
	    break;
	    
	    case 3:
	        ret = "����";
	    break;
	    
	    case 4:
	        ret = "���";
	    break;
	    
	    case 5:
	        ret = "������";
	    break;
	    
	    case 6:
	        ret = "��� ����";
	    break;
	    
	    case 7:
	        ret = "����";
	    break;
	}
	return ret;
}

void SetDiceForTableRand()
{
	int i;

	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.Desk.(sGlobalTemp).Mix) == true)
        {
            DiceState.Desk.(sGlobalTemp) = (rand(5)+1);
		}
	}
}
/////////////////////////// AI //////////////////////////////////
void CompTurn()
{
    int i, d, j;
    bool ok, ok2, ok3, b;
    
	// ���� ���� ����� ��������� � � ���� ��� ������, �� ����� ��� �������???
	ok = true;
	if (GetResult() == -1 && dir_i_start == 1 && bStartGame == 3) // ������� ����
	{
        ok = false;
	}
	if (ok)
	{
    	if (sti(DiceState.Comp.Result.Type) == 8 && sti(DiceState.Hero.Result.Type) >= 2)
    	{
            //���������� ������ ������ ����� (��� 100 ��������� 1)
            SetFormatedText("INFO_TEXT","� ��������� ���� �����...");
    		// for test
    		ClickCompDice(1);
    		move_i = 0;
            PlaySound("interface\dice_mix.wav");
            PostEvent("My_eventMoveImg", 500);
            return;
    	}

    	// ��� ���� ������� �� ��� (���� �����)
        ok3 = (sti(DiceState.Comp.Result.Type) == 6) && (sti(DiceState.Hero.Result.Type) >= 5);
        ok  = (sti(DiceState.Comp.Result.Type) == 6) && (sti(DiceState.Hero.Result.Type) == 4) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate2));
        ok3 = ok3 || ok;
        // ���� ������� ������, ���� ��� ��� ����, � ����� ����??
        ok = (sti(DiceState.Comp.Result.Type) == 7) || (sti(DiceState.Comp.Result.Type) == 5);
        ok = ok && (sti(DiceState.Hero.Result.Type) >= 3);
        // ����, �� � �� ������
        ok2 = (sti(DiceState.Hero.Result.Type) == 3) && (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1));
        b   = (sti(DiceState.Hero.Result.Type) == 1) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate1));
        ok2 = ok2 || b;
        ok2 = (sti(DiceState.Comp.Result.Type) == 3) && ok2;
        if (ok || ok2 || ok3)
        {
            ok = false;
            SetFormatedText("INFO_TEXT","� ��������� ���...");
            for (i = 1; i<=6; i++)
    		{
    	        sGlobalTemp = "d"+i;
    	        if (sti(DiceState.Comp.Result.(sGlobalTemp)) == 1)
    	        {
                    d = i; // �� �� �����
                    for (j = 1; j<=5; j++)
            		{
            	        sGlobalTemp = "d"+j;
            	        if (sti(DiceState.Comp.(sGlobalTemp).Mix) == true) continue;
            	        if (sti(DiceState.Comp.(sGlobalTemp)) == d)
            	        {
                            ok = ClickCompDice(j) || ok;
                            break;
            			}
            		}
    			}
    		}

    		if (ok)
    		{
                move_i = 0;
    	        PlaySound("interface\dice_mix.wav");
    	        PostEvent("My_eventMoveImg", 500);
    	        return;
    		}
        }

        // ����� �����!!!!! -->
        if (sti(DiceState.Comp.Result.Type) > sti(DiceState.Hero.Result.Type) && GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(12) && rand(4) > 1)
        {
			//navy --> ������� �����������
			if (!CheckAttribute(npchar, "Quest.DiceCheats")) npchar.Quest.DiceCheats = 0;
			npchar.Quest.DiceCheats = sti(npchar.Quest.DiceCheats) + 1;
			//navy <--
            SetFormatedText("INFO_TEXT","� ��������� ���...");
            ok = false;
            if (sti(DiceState.Hero.Result.Type) == 1)
            {
                d = sti(DiceState.Hero.Result.Rate1) + 1;
            }
            else
            {
                d = rand(5) + 1;
            }
            if (d > 6) d = 6;

    		for (i = 1; i<=5; i++)
    		{
    	        sGlobalTemp = "d"+i;
    	        if (sti(DiceState.Comp.(sGlobalTemp)) != d)
    	        {
                    ok = ClickCompDice(i) || ok;
    	            DiceState.Desk.(sGlobalTemp) = d;
    			}
    		}
    		if (ok)
    		{
        		move_i = 0;
        		bSetRandDice = false;
                PlaySound("interface\dice_mix.wav");
                PostEvent("My_eventMoveImg", 500);
                return;
            }
        }
        // �����!!!!! <--
    }
	// ������ �� �������������
	SetFormatedText("INFO_TEXT","�� ���� �������������.");
	PostEvent("My_eCheckGame", 800);
}

bool ClickCompDice(int d)
{
    sGlobalTemp = "d"+d;
    
	if (iMoneyN >= iRate && sti(DiceState.Comp.(sGlobalTemp).Mix) == false)
	{
		CreateImage("CompDice" + d ,"","", 0,0,0,0);

		DiceState.Comp.(sGlobalTemp).Mix = true;
		DiceState.Desk.(sGlobalTemp).Mix = true;
  		PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
	    iChest += iRate;
	    PlaySound("interface\took_item.wav");
	    ShowMoney();
	    return true;
    }
    return false;
}
// ��������� ������ �������� �����
void RecalcAIDice(string _whom)
{
    int    i;
	string sTemp;
	bool   ok;
	
	for (i = 1; i<=6; i++)
	{
        sGlobalTemp = "d"+i;
        DiceState.(_whom).Result.(sGlobalTemp) = 0;
	}
	
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d" + i;
        sTemp       = "d" + sti(DiceState.(_whom).(sGlobalTemp));
        DiceState.(_whom).Result.(sTemp) = sti(DiceState.(_whom).Result.(sTemp)) + 1;
	}
}

string lMsg(string _str)
{
	return CARDS_RULE;
}
