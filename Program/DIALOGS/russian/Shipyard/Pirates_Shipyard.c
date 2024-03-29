// ������ �� �������
// ��� ������ �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    if ( sti(Pchar.Ship.Type) != SHIP_NOTUSED)
    {
	    int   	cannonQ       = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity);
		int   	cannonMax     = sti(RealShips[sti(Pchar.Ship.Type)].MaxCaliber);
		int		cannonMaxQ    = 0; 
		if (CheckAttribute(&RealShips[sti(Pchar.Ship.Type)],"CannonsQuantityMax")) cannonMaxQ = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax); 
		int   	shipClass     = sti(RealShips[sti(Pchar.Ship.Type)].Class);
		//int   shipPrice     = sti(RealShips[sti(Pchar.Ship.Type)].Price);
		int   	shipCapacity  = sti(RealShips[sti(Pchar.Ship.Type)].Capacity);
		float 	shipSpeedRate = stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);
		float 	MastMulti     = stf(RealShips[sti(Pchar.Ship.Type)].MastMultiplier);
		int   	shipMaxCrew   = sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew);
		int   	shipHP        = sti(RealShips[sti(Pchar.Ship.Type)].HP);
		float 	shipTurnRate  = stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);
		float 	shipWindAgainst = stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed);
		int		cannonDiff		= cannonMaxQ - cannonQ;
		int 	iCaliber;

/*		
		if(cannonDiff >= 2) 
		{ 
			cannonDiff = 2;
			cannonMaxQ = cannonQ + cannonDiff;
		}
		else 
		{ 
			cannonDiff = 0;
		}
*/		
		float fQuestShip = 1.0;
		
		if(CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "QuestShip")) fQuestShip = 1.2;
		
		//int  zWorkPrice  = makeint(8000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE) * fQuestShip);
		int sundukSum = makeint(((7-shipClass)*1.0) * fQuestShip);
		
	    int  cannonMatherial1 = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20) * fQuestShip);
	    int	 cannonMatherial2 = makeint((7-shipClass)/2 * fQuestShip);
		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
	    int	 cannonMatherial3 = sundukSum;
		int  cannonWorkPrice  = makeint((100 * cannonQ * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  capacityMatherial1 = makeint((35 * (7-shipClass) + shipCapacity * 7/100) * fQuestShip);
	    int	 capacityMatherial2 = makeint((10 * (7-shipClass)+10) * fQuestShip);
	    int  capacityMatherial3 = sundukSum;
		int  capacityWorkPrice  = makeint((2 * shipCapacity * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  SpeedRateMatherial1 = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	    int	 SpeedRateMatherial2 = makeint(5 * (7-shipClass) * fQuestShip);
	    int	 SpeedRateMatherial3 = sundukSum;
		int  SpeedRateWorkPrice  = makeint((100 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
		
		int  MastMultiplierMatherial1 = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	    int	 MastMultiplierMatherial2 = makeint(5 * (7-shipClass) * fQuestShip);
	    int	 MastMultiplierMatherial3 = sundukSum;
		int  MastMultiplierMatherialWorkPrice  = makeint((100 * MastMulti * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  MaxCrewMatherial1 = makeint((shipMaxCrew * 6/10 + 50 * (7-shipClass)) * fQuestShip);
	    int	 MaxCrewMatherial2 = makeint((6 * (7-shipClass)+3) * fQuestShip);
	    int	 MaxCrewMatherial3 = sundukSum;
		int  MaxCrewWorkPrice  =  makeint((15 * shipMaxCrew * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  TurnRateMatherial1 = makeint((shipHP * 25/1000 + 375/shipClass+20) * fQuestShip);
	    int	 TurnRateMatherial2 = makeint((5 * (7-shipClass)+2) * fQuestShip);
	    int	 TurnRateMatherial3 = sundukSum;
		int  TurnRateWorkPrice  = makeint((30 * shipTurnRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  HPMatherial1 = makeint((35 * (7-shipClass) + shipHP * 7/100) * fQuestShip);
	    int	 HPMatherial2 = makeint(5 * ((7-shipClass)*3) * fQuestShip);
	    int	 HPMatherial3 = sundukSum;
		int  HPWorkPrice  = makeint((shipHP * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
	    int  WindAgainstMatherial1 = makeint((shipHP * 25/1000 + 750/shipClass+20) * fQuestShip);
	    int	 WindAgainstMatherial2 = makeint((6 * (7-shipClass)+1) * fQuestShip);
	    int	 WindAgainstMatherial3 = sundukSum;
		int  WindAgainstWorkPrice  = makeint((300 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);
	    
		int quantityMatherial1 = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20) * fQuestShip);
		int quantityMatherial2 = makeint((7-shipClass)/2 * fQuestShip);
			if (quantityMatherial2 < 1) quantityMatherial2 = 1;
		int quantityMatherial3 = sundukSum;
		int cannonQWorkPrice = makeint((100 * cannonMaxQ * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		int AllMatherial1 = cannonMatherial1 + quantityMatherial1;
		int AllMatherial2 = cannonMatherial2 + quantityMatherial2;
		int AllMatherial3 = cannonMatherial3 + quantityMatherial3;
		int cannonAllWorkPrice = cannonWorkPrice + cannonQWorkPrice;
		//int  zWorkPriceAll  = zWorkPrice * 2;
		
		
		float discount = 1.0;
  		if (CheckAttribute(NPChar, "Discount"))
		{
		    discount = 0.75;
		}
		
	    cannonMatherial1 = cannonMatherial1 * discount;
	    cannonMatherial2 = cannonMatherial2 * discount;
		cannonMatherial3 = cannonMatherial3 * discount;
		if (cannonMatherial3 < 1) cannonMatherial3 = 1;
	    cannonWorkPrice  = cannonWorkPrice * discount;

		quantityMatherial1 = quantityMatherial1 * discount;
		quantityMatherial2 = quantityMatherial2 * discount;
		quantityMatherial3 = quantityMatherial3 * discount;
		if (quantityMatherial3 < 1) quantityMatherial3 = 1;
		cannonQWorkPrice = cannonQWorkPrice * discount;

		AllMatherial1 = AllMatherial1 * discount;
		AllMatherial2 = AllMatherial2 * discount;
		AllMatherial3 = AllMatherial3 * discount;
		if (AllMatherial3 < 1) AllMatherial3 = 1;
		cannonAllWorkPrice = cannonAllWorkPrice * discount;

	    capacityMatherial1 = capacityMatherial1 * discount;
	    capacityMatherial2 = capacityMatherial2 * discount;
		capacityMatherial3 = capacityMatherial3 * discount;
		if (capacityMatherial3 < 1) capacityMatherial3 = 1;
	    capacityWorkPrice  = capacityWorkPrice * discount;

	    SpeedRateMatherial1 = SpeedRateMatherial1 * discount;
	    SpeedRateMatherial2 = SpeedRateMatherial2 * discount;
		SpeedRateMatherial3 = SpeedRateMatherial3 * discount;
		if (SpeedRateMatherial3 < 1) SpeedRateMatherial3 = 1;
	    SpeedRateWorkPrice  = SpeedRateWorkPrice * discount;
		
		MastMultiplierMatherial1 = MastMultiplierMatherial1 * discount;
	    MastMultiplierMatherial2 = MastMultiplierMatherial2 * discount;
		MastMultiplierMatherial3 = MastMultiplierMatherial3 * discount;
		if (MastMultiplierMatherial3 < 1) MastMultiplierMatherial3 = 1;
	    MastMultiplierMatherialWorkPrice  = MastMultiplierMatherialWorkPrice * discount;

	    MaxCrewMatherial1 = MaxCrewMatherial1 * discount;
	    MaxCrewMatherial2 = MaxCrewMatherial2 * discount;
		MaxCrewMatherial3 = MaxCrewMatherial3 * discount;
		if (MaxCrewMatherial3 < 1) MaxCrewMatherial3 = 1;
	    MaxCrewWorkPrice  = MaxCrewWorkPrice * discount;

	    TurnRateMatherial1 = TurnRateMatherial1 * discount;
	    TurnRateMatherial2 = TurnRateMatherial2 * discount;
		TurnRateMatherial3 = TurnRateMatherial3 * discount;
		if (TurnRateMatherial3 < 1) TurnRateMatherial3 = 1;
	    TurnRateWorkPrice  = TurnRateWorkPrice * discount;

	    HPMatherial1 = HPMatherial1 * discount;
	    HPMatherial2 = HPMatherial2 * discount;
		HPMatherial3 = HPMatherial3 * discount;
		if (HPMatherial3 < 1) HPMatherial3 = 1;
	    HPWorkPrice  = HPWorkPrice * discount;

	    WindAgainstMatherial1 = WindAgainstMatherial1 * discount;
	    WindAgainstMatherial2 = WindAgainstMatherial2 * discount;
		WindAgainstMatherial3 = WindAgainstMatherial3 * discount;
		if (WindAgainstMatherial3 < 1) WindAgainstMatherial3 = 1;
	    WindAgainstWorkPrice  = WindAgainstWorkPrice * discount;

		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
		if (quantityMatherial2 < 1) quantityMatherial2 = 1;
	}
	
	int iTemp;
	string attr, attrLoc;
	int amount;
	ref shTo;
    string sTemp;
    string s1;
    
	switch (Dialog.CurrentNode)
	{
		
		// -----------------------------------������ ������ - ������ �������
		case "First time":  // �������� ��������� �������, ������ ���� ���
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "���... ��� �� �������� ������... ���� ����� " + GetFullName(npchar) + ", �, ������ ���� ������, � ������ ������� �� ���� ������� ����� ��������. �� ��� ������� ������ ����� ���� � ���...";
				Link.l1 = pcharrepphrase("������ ����, ������ ����������� ��������� ��� �� �������. ��� ��� " + GetFullName(pchar) + ", �����, �� ��� ��� �������.",
					"��� �� �������, ��� ��������, ���������. ���� ����� " + GetFullName(pchar) + ", �����, �� ��� ��� �������.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // �����, ���� �� ������� ����� ����� ��  "First time"
			{
				dialog.text = "�, ��� ����� ��, ����� �� ������ ����������... ���... ���.";
				link.l1 = pcharrepphrase("�� �����, ��� ����� �. �� ������� ��������� � �����, ���� �� �� ������ ���� ����.",
					"� ��� ������� ������, � ������, ���� ���������, ������� �������� � ����� ���������� ��������.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("�� ������� ���� ����� ����������. ��������.",
					"��� ����, ��������, ��� �����������"+ GetSexPhrase("","�") +".");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
			dialog.text = "�, ��� ����� ��, ����� �� ������ ����������... ���... ���.";
			link.l1 = pcharrepphrase("�� �����, ��� ����� �. �� ������� ��������� � �����, ���� �� �� ������ ���� ����.",
	            "� ��� ������� ������, � ������, ���� ���������, ������� �������� � ����� ���������� ��������.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("�� ������� ���� ����� ����������. ��������.",
				"��� ����, ��������, ��� �����������"+ GetSexPhrase("","�") +".");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "��������-��������, �� ��������� �� ��� �������� ��������. ������� ������, ������� ����, ��� ��� ��� ����?";
			link.l1 = pcharrepphrase("��� �����. �� ���� ��� ������ ����� �������� �����, � ������, ���� ����� ��� ������...",
				"���-�� ������������ ���, ��� �� � ���� ������� ���� ���� �� ���������� ������ ��������� � ��������. ����� �� ���?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "�� ������ �������, "+ GetSexPhrase("�����","��������") +"!";
			link.l1 = pcharrepphrase("�����-�����, �� �������, � �� ���� ������. �� ����, ���� ���� �������� � ������ ������� �������� �� �������. �������-�� ����� �������� � ������.",
				"� ������ ��� ��� ��������, ������ �� �������� � ������ ��������. � ������, ���� �� ���������, ������� ����� �������� � �����.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("���, � ���� ������ �����������! ��������!",
				"� ����, ������ ����� �� �� ������. ��������.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "���, ���... �� ���� ������� �����. ��� ��� ����� �� ���� �����, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = pcharrepphrase("��� ���� ��������������� �������� �����.","� ���� ��������������� �������� ����� �����.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "� ���� ������.";
			Link.l2.go = "quests"; //(��������� � ���� ������)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "� �����"+ GetSexPhrase("","�") +" �� ���������� � ���� � ����� ����������.";
				link.l3.go = "LoanForAll";//(���������� � ���� ������)
			}
			link.l9 = pcharrepphrase("����, � ���� ���� ���� ���������� ���, �� ��������.", "��� ��� ����, ��������.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":
			dialog.Text = "���� ���������� ������ �� �������� �������� - ������� �������������� ������� ��������. ����� ���������� �� ����� ������� ���������� �������.";
			Link.l1 = "������������! ��� ��� ��� ����� ������� �� ��� ���� ��������. ����� ���������, ��� ����� �������?";
			Link.l1.go = "ship_tunning_start";
			link.l2 = "���, ��� �� ����� ���������, � ���� ������ ��������������� �������� �����.";
			link.l2.go = "shipyard";

			if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
			{
			link.l5 = "� ����� � ��� �� ����� �������� �������, ���������� ���� ������ �������������?";
			link.l5.go = "Shipyard1";
			}
			else
			{
			link.l5 = "����� �� ���������� ���� �������?";
			link.l5.go = "shiporder1";
			}

			link.l3 = "��� ����� ������ �� �������.";
			link.l3.go = "Cannons";
			link.l4 = "���� �������� ������� ��� �������.";
			link.l4.go = "SailsGerald";
			Link.l9 = "�� ���� � ���� �����������. � ������� ����� ������ ���������� ����� �������� �������. �� ��������.";
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "Discount_1":
			dialog.Text = "�������? ��, ������� � ����� ���� ������ � 20 ��������� �� ���� �������, �� ������ �������������, �������������� � ����������� ����.";
			Link.l1 = "���������, ����� ���� ���������������� �������, � ���� ������� � ���� �� ���� �� �������. ������� ������!";
			Link.l1.go = "Discount_2";
			Link.l9 = "�����... �������, �������� �������� ��� ������.";
			Link.l9.go = "ship_tunning_start";
		break;
		
		case "Discount_2":
			dialog.Text = "���������������� �������, ��������? �� ��� �� ������ ��������!";
			Link.l1 = "������� ��� ����� ������!";
			Link.l1.go = "Discount_3";
			LockControl("DlgDown3", true);
			LockControl("DlgUp3", true);
		break;
		
  		case "Discount_3":
            NPChar.SeaQuestions = rand(sti(NullCharacter.SeaQuestions));
            sTemp = sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);

   			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";
			Link.l9 = "�������, �������� �������� ��� ������.";
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "Discount_4":
   			sTemp = "a" + NPChar.SeaQuestions;
			if (NullCharacter.SeaQuestions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "�����!! ������������� ������� �������"+ GetSexPhrase("",", ���� � �������") +". �� ��������� ������!";
				link.l1 = "� �� �������"+ GetSexPhrase("","�") +", ��� ����. � ����.";
				link.l1.go = "ship_tunning_start";
				NPChar.Discount = true;
				LockControl("DlgDown3", false);
				LockControl("DlgUp3", false);
			}
			else
			{
				dialog.text = "���, �������. ����� ����� ����������� ���?";
				link.l1 = "��, �������� ��� ���.";
				link.l1.go = "Discount_5";
				link.l2 = "���, ���� ������ ������� ������ ��� ����.";
				link.l2.go = "ship_tunning_not_now";
			}
		break;
		
		case "Discount_5":
            sTemp = sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);
   			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";
			Link.l9 = "���, ����� �� �����.";
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_again":
			dialog.Text = RandPhraseSimple("�... ��� ����� ��... ����� ������ ���� �������� ���������?",
			RandPhraseSimple("����������� ���������� �������. ���, ����� �������� �� ����������?",
                                           "��... �� ������ ����� ���, �� ����� ������� ���������������.. ����� ��������� ������������?"));
			Link.l1 = "��. ���� ����� ����. ����� ���������, ��� ����� ������� ���?";
			Link.l1.go = "ship_tunning_start";
			link.l2 = "���, ��� �� ����� ���������, � ���� ������ ��������������� �������� �����.";
			link.l2.go = "shipyard";

			if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
			{
			link.l6 = "� ����� � ��� �� ����� �������� �������, ���������� ���� ������ �������������?";
			link.l6.go = "Shipyard1";
			}
			else
			{
			link.l6 = "����� �� ���������� ���� �������?";
			link.l6.go = "shiporder1";
			}

			link.l3 = "��� ����� ������ �� �������.";
			link.l3.go = "Cannons";
			link.l31 = "���� �������� ������� ��� �������.";
			link.l31.go = "SailsGerald";
            Link.l4 = "� ���� ������.";
			Link.l4.go = "quests"; //(��������� � ���� ������)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "� �����"+ GetSexPhrase("","�") +" �� ���������� � ���� � ����� ����������.";
				link.l5.go = "LoanForAll";//(��������� � ���� ������)
			}
			Link.l9 = "���. ���� ���������� ��, ��� ����";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
        case "ship_tunning_not_now_2":
			dialog.Text = "�� ��, � �������, ��� � �������! ������ �������! �������, ����� �������� � �� �������� ���� �� ��������.";
			Link.l1 = RandPhraseSimple("�������! ����� ��������.", "����, ������. ����� � ��� ��������.");
			Link.l1.go = "ship_tunning_not_now";
		break;
        		
        case "ship_tunning_start":
			if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "�������-�� ���? ��� �� ��� ��� ������ ��������?!";
			    Link.l1 = "� �� ������.. ��� ��� �... ���������";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "�, �������, ����������, �� � � ���� ���� ��������� �����. ��������� �����!";
			        Link.l1 = "�������...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if (shipClass == 7)
                    {
						dialog.Text = "���.. ������� � �� ���������. ������ ������� � ���������, ������� ��� ��� �� ������.";
    			        Link.l1 = "�������...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }

                    s1 = "���-���... ���������, ��� ��� � ��� ����... ��� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " ��! �� �������-�� ������� �� � ����� �����. ��-�� �� ����� ��������. ������ ���������� � ���� ����? ����� ����... � ����.";
    			    }
    			    s1 = s1 + " ��� �� �� �����"+ GetSexPhrase("","�") +" � ��� ������?";
                    dialog.Text = s1;

					if (RealShips[sti(Pchar.Ship.Type)].BaseName == "Wh_corvette_quest")
					{//��������� ���
						dialog.text = "����, 'ϸ� �����'. ��� ����� � ��� ������?";
						if(!CheckAttribute(npchar, "WarDogUpgrade"))
						{
							npchar.WarDogUpgrade = "start";
							dialog.text = "���������... ���! ��� ���, �����? 'ϸ� �����'? ������ ����������� ��� ������ ����?";
							link.l1 = "���? � ��� ��?";
							link.l1.go = "WarDogUpgrade_1";
							break;
						}
						if(CheckAttribute(pchar, "TitanicIsDown"))
						{
							link.lWarDogUpgrade = "��� ������? ������������� �������. ��������� ������ ������� �������� �������� � �����. ";
							link.lWarDogUpgrade.go = "WarDogUpgrade_8";
						}
						if(CheckAttribute(npchar, "WarDogUpgradePayment") && sti(pchar.money) >= 1000000)
						{
							link.lWarDogUpgrade = "� �������� ��� �������. ������� ���� ������ ������������� ���� �����.";
							link.lWarDogUpgrade.go = "WarDogUpgrade_pay";
						}
						
					}
					
					if (cannonMax < 36 && cannonDiff > 0 && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
					{
						Link.l1 = "��������� ������ � ������������ ���������� ������.";
						Link.l1.go = "ship_tunning_cannon_all";
					}
					else 
					{
                    if (cannonMax < 36 && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
                    {
                        Link.l1 = "��������� ������ ������.";
    			        Link.l1.go = "ship_tunning_cannon";
    			    }
						else
						{
							if (cannonDiff > 0)
							{
								Link.l1 = "��������� ������������ ���������� ������.";
								Link.l1.go = "ship_c_quantity";
							}
						}
					}
										
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
                    {
    			        Link.l2 = "��������� �������.";
    			        Link.l2.go = "ship_tunning_Capacity";
    			    }
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MastMultiplier"))
                    {
    			        Link.l3 = "��������� ��������� ����.";
    			        Link.l3.go = "ship_tunning_MastMultiplier";
    			    }
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
                    {
    			        Link.l4 = "��������� ��������.";
    			        Link.l4.go = "ship_tunning_SpeedRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
                    {
    			        Link.l5 = "��������� �������������.";
    			        Link.l5.go = "ship_tunning_TurnRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
                    {
    			        Link.l6 = "��������� ����� ��� �������.";
    			        Link.l6.go = "ship_tunning_MaxCrew";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
                    {
    			        Link.l7 = "��������� ��������� �������.";
    			        Link.l7.go = "ship_tunning_HP";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
                    {
    			        Link.l8 = "��������� ��� � ���������.";
    			        Link.l8.go = "ship_tunning_WindAgainst";
    			    }
    			    Link.l10 = "��������! � ���������"+ GetSexPhrase("","�") +".";
    			    Link.l10.go = "ship_tunning_not_now_2";
			    }
			}
		break;

		////////////////////////////////////////// ������ � ���������� ������  ////////////////////////////////////////////////////
		case "ship_tunning_cannon_all":
			s1 = "������� ���������, ��� ����� �������. ������ ������ �� ����� ������� " + cannonQ + ", ����������� ��������� ���������� - " + cannonMaxQ + ",";
			s1 = s1 + " ������������ ������ - " + cannonMax + ". ��� �������� �������� � ���������� ������� ��� �����������: ������� ������ - "+AllMatherial1 + ".";
			s1 = s1 + " � ����, � �� ��������� ����� ����� � ���� ����, ������� �� ������ ������: �������� - "+AllMatherial2 + ", �������� � ������� - "+AllMatherial3 + ",";
			s1 = s1 + " ���� - " + cannonAllWorkPrice + " �������� �� ������� �������. �� �� ��������� - ���� ���������... �� �� - � ������ ������.";

			dialog.Text = s1;		
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_cannon_all_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = "� ������ ��� ������? ������ �� ���-�� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_cannon_all_complite";
			}
		break;
		
		case "ship_tunning_cannon_all_start":
			amount = cannonAllWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;

				NPChar.Tuning.Matherial1 = AllMatherial1; // ������ ������
				NPChar.Tuning.Matherial2 = AllMatherial2; // ����
				NPChar.Tuning.Matherial3 = AllMatherial3;
				NPChar.Tuning.ShipType       = Pchar.Ship.Type;
				NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");
			    
				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.text = "��� � ������. ��� �������� � ��� �������������.";
				link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
				link.l1.go = "Exit";
			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� ������� � ���������� ������ �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
					" ������-������� ����������: ������� ������ - " + NPChar.Tuning.Matherial1 + ", �������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}				
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
				dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����";
				link.l1.go = "Exit";
			}
		break;
		
		case "ship_tunning_cannon_all_again":		
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
			{
				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
				Link.l1 = "��. ���-��� ������� �������.";
				Link.l1.go = "ship_tunning_cannon_all_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������..";
				Link.l1 = "���� ����. ������, ��� ������� ������...";
				Link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "Lose");
				AddQuestUserData("ShipTuning", "sSex", GetSexPhrase("","�"));
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_tunning_cannon_all_again_2":		
		    checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");
		
			if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
				link.l1 = "���.";
				link.l1.go = "ship_tunning_cannon_all_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.Text = "���� �������� ��������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}		
		break;
		
		case "ship_tunning_cannon_all_complite":
			AddTimeToCurrent(8, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");	

			// ������� ������ ������
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 6) iCaliber = 6;
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
			}
			shTo.MaxCaliber = iCaliber;			

			// ������� ���������� ������
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff/2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);		
		
			Pchar.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			Pchar.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			Pchar.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			Pchar.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			Pchar.Ship.Cannons = sti(shTo.CannonsQuantity);			
			shTo.Tuning.Cannon = true;
			
			// finish <--
			NextDiag.TempNode = "ship_tunning_again";
			s1 = "... �� ���, ����� �� ���... ������ ����������� ������ � �������� ������.";
			s1 = s1 + " ���, ������, ����� ������� � �� ���� �����.";
			dialog.Text = s1;		
			Link.l1 = "�������! ����������� �� �������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;		

		
		////////////////////////////////////////// ������ ���������� ������  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			s1 = "������� ���������, ��� ����� �������. ������ ������ �� ����� ������� " + cannonQ + ", ����������� ��������� ���������� - " + cannonMaxQ + ".";			
			s1 = s1 + " ��� ��� ���� ��������� ��������, ��� ����� ��������� ������� ��� �����������: ������� ������ - "+quantityMatherial1+ ",";
			s1 = s1 + " ����� ����, �� ������ � ������: �������� - "+quantityMatherial2+ ", �������� � ������� - "+quantityMatherial3+ ",";
			s1 = s1 + " ���� - " + cannonQWorkPrice + " �������� �� ������� �������. �� �� ��������� - ���� ���������... �� �� - � ������ ������.";
			dialog.Text = s1;		
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = "� ������ ��� ������? ������ �� ���-�� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_c_quantity_complite";
			}

		break;
		
		case "ship_c_quantity_start":
			amount = cannonQWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;
				
				NPChar.Tuning.Matherial1 = quantityMatherial1; // ������ ������
				NPChar.Tuning.Matherial2 = quantityMatherial2; // ����				
			        NPChar.Tuning.Matherial3 = quantityMatherial3;				
				NPChar.Tuning.ShipType       = Pchar.Ship.Type;
				NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");
											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "��� � ������. ��� �������� � ��� �������������.";
				link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
				link.l1.go = "Exit";
			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� ���������� ������ �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ������� ������ - " + NPChar.Tuning.Matherial1 + ", �������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now";
				dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
				Link.l1 = "��. ���-��� ������� �������.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
				Link.l1 = "���� ����. ������, ��� ������� ������...";
				Link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");
		
			if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
				link.l1 = "���.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "���� �������� ��������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			
			// ������� ���������� ������
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff/2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);		
		
			Pchar.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			Pchar.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			Pchar.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			Pchar.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			Pchar.Ship.Cannons = sti(shTo.CannonsQuantity);
			shTo.Tuning.Cannon = true;
			// finish <--
			NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ �������� �������������� ������.";
			Link.l1 = "�������!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		////////////////////////////////////////// ������ ������ ������ ////////////////////////////////////////////////////								
		case "ship_tunning_cannon":
			s1 = "������� ���������, ��� ����� �������. ������ ������ �� ����� ������� " + cannonQ + ", ������������ ������ - " + cannonMax + ".";
			
			s1 = s1 + " ��� �������� �������� � ������� ������� ������ ��� �����������: ������� ������ - "+ cannonMatherial1 + ".";
			s1 = s1 + " � �� ������ � ������: �������� - "+ cannonMatherial2 + ", �������� � ������� - "+ cannonMatherial3 + ",";
			s1 = s1 + " ���� - " + cannonWorkPrice + " �������� �� ������� �������. �� �� ��������� - ���� ���������... �� �� - � ������ ������.";
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_cannon_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ���-�� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_cannon_complite";
			}
		break;
		
		case "ship_tunning_cannon_start":
		    amount = cannonWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;
			    NPChar.Tuning.Matherial1 = cannonMatherial1; // ������ ������
			    NPChar.Tuning.Matherial2 = cannonMatherial2; // ����
			    NPChar.Tuning.Matherial3 = cannonMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			    
				NextDiag.TempNode = "ship_tunning_cannon_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� ������� ������ �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ������� ������ - " + NPChar.Tuning.Matherial1 + ", �������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_cannon_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_cannon_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_cannon_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������..";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_cannon_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_cannon_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_cannon_again";
				dialog.Text = "���� �������� ��������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_cannon_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// ������� ������ ������
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 6) iCaliber = 6;
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
			}
			shTo.MaxCaliber = iCaliber;
			shTo.Tuning.Cannon = true;
			// finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ ������ ������ - �������� ����������.";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
				
		////////////////////////////////////////// ���� ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			s1 = "������� ���������, ��� ����� �������. ������ ������� ������ ����� - "+ shipCapacity;
			
			s1 = s1 + ". ��� ����������� ��������� ��� �����������: ������� - "+ capacityMatherial1 + ".";
			s1 = s1 + " � ������ �� ���� ������ � ������: ������� ������� - "+ capacityMatherial2 + ", �������� � ������� - "+ capacityMatherial3 + ",";
			s1 = s1 + " ���� - " + capacityWorkPrice + " �������� �� ������� �������. ����� �� ��. �� �� - ������ ������.";
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_Capacity_complite";
			}

		break;
		
		case "ship_tunning_Capacity_start":
		    amount = capacityWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = capacityMatherial1; // ������� ������ GOOD_MAHOGANY
			    NPChar.Tuning.Matherial2 = capacityMatherial2; //  GOOD_OIL
			    NPChar.Tuning.Matherial3 = capacityMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� �������� �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ������� - " + NPChar.Tuning.Matherial1 + ", ������� ������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "������� ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL, "jewelry5", "chest");
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "���� �������� ��������: ������� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}			
	        shTo.Tuning.Capacity = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ ��������� �� ������ - �������� ������ ����������.";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			s1 = "������� ���������, ��� ����� �������. ������ �������� ������ ������� " + shipSpeedRate;
			
			s1 = s1 + " �����. ��� ����� ������� ��� �����������: ����� - "+ SpeedRateMatherial1 + ".";
			s1 = s1 + " � ����, � �� ��������� ����� ����� � ���� ����, ������� �� ������ ������: �������� � ������� - "+ SpeedRateMatherial3 + ", ������� �������� ������� - "+ SpeedRateMatherial2 + ", ���� - " + SpeedRateWorkPrice + " �������� �� ������� �������. ����� �� ��. �� �� - � ������ ������.";

            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_SpeedRate_complite";
			}

		break;
		
		case "ship_tunning_SpeedRate_start":
		    amount = SpeedRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = SpeedRateMatherial1; // GOOD_SAILCLOTH
			    NPChar.Tuning.Matherial2 = SpeedRateMatherial2; //  GOOD_SILK
			    NPChar.Tuning.Matherial3 = SpeedRateMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� �������� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ����� - " + NPChar.Tuning.Matherial1 + ", ������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SILK, "jewelry2", "chest");
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "���� �������� ��������: ����� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "��� �������� �������: ����� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}		
	        shTo.Tuning.SpeedRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ ������ ����� ������� ��������. ��������!";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// MastMultiplier ////////////////////////////////////////////////////
		case "ship_tunning_MastMultiplier":
			s1 = "������� ���������, ��� ����� �������. ������ ��������� ���� ������ ������� " + MastMulti;
			
			s1 = s1 + ". ��� ���������� ���� ��� �����������: ����� - "+ MastMultiplierMatherial1 + ".";
			s1 = s1 + " � ����, � �� ��������� ����� ����� � ���� ����, ������� �� ������ ������: �������� � ������� - "+ MastMultiplierMatherial3 + ", ������� ��������� ������� - "+ MastMultiplierMatherial2 + ", ���� - " + MastMultiplierMatherialWorkPrice + " �������� �� ������� �������. ����� �� ��. �� �� - � ������ ������.";

            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_MastMultiplier_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_MastMultiplier_complite";
			}

		break;
		
		case "ship_tunning_MastMultiplier_start":
		    amount = SpeedRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = MastMultiplierMatherial1; // GOOD_SAILCLOTH
			    NPChar.Tuning.Matherial2 = MastMultiplierMatherial2; //  GOOD_SILK
			    NPChar.Tuning.Matherial3 = MastMultiplierMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			
				NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "�� ���� ������ �� ���������� ���� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ����� - " + NPChar.Tuning.Matherial1 + ", ��������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MastMultiplier_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_MastMultiplier_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MastMultiplier_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_PLANKS, "jewelry9", "chest");
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_MastMultiplier_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
				dialog.Text = "���� �������� ��������: ����� - "+ sti(NPChar.Tuning.Matherial1) + ", ��������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "��� �������� �������: ����� - "+ sti(NPChar.Tuning.Matherial1) + ", ��������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_MastMultiplier_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
			shTo.MastMultiplier        = stf(shTo.MastMultiplier) - 0.3;
	
	        shTo.Tuning.MastMultiplier = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ ������ ������ ������� �������� ���� ������ ��������. ��������!";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			s1 = "������� ���������, ��� ����� �������. ������ ������������ ������ ������ ����� � ������ ���������  " + shipMaxCrew + " �������.";
			
			s1 = s1 + " ��� �������������� ������� � ������ �������� ��� �����������: ���� - "+ MaxCrewMatherial1 + ".";
			s1 = s1 + " � ������ ������: �������� - "+ MaxCrewMatherial2 + ", �������� � ������� - "+ MaxCrewMatherial3 + ", ���� " + MaxCrewWorkPrice + " �������� �� ������� �������. �������, ��. �� �� - � ������ ������."; 
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_MaxCrew_complite";
			}
		break;
		
		case "ship_tunning_MaxCrew_start":
		    amount = MaxCrewWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = MaxCrewMatherial1; // GOOD_FRUITS
			    NPChar.Tuning.Matherial2 = MaxCrewMatherial2; //  GOOD_CLOTHES
			    NPChar.Tuning.Matherial3 = MaxCrewMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "�� ���� ������ �� ���������� ������� �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ���� - " + NPChar.Tuning.Matherial1 + ", �������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "���� ���. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_LEATHER, "jewelry1", "chest");
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "���� �������� ��������: ���� - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ���� - "+ sti(NPChar.Tuning.Matherial1) + ", �������� - "+ sti(NPChar.Tuning.Matherial2) + ", ��������  - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������� ��������, ���� ����� ������.";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			s1 = "������� ���������, ��� ����� �������. ������ ������������� ����� ������� - " + shipTurnRate;
			
			s1 = s1 + " ��� �������������� �������, ���� ��� �����������, ��� �����������: ������� - "+ TurnRateMatherial1 + ".";
			s1 = s1 + " � �� ������ � ������: �������� � ������� - "+ TurnRateMatherial3 + ", ������� - "+ TurnRateMatherial2 + ", ���� - " + TurnRateWorkPrice + " �������� �� ������� �������. �� �� ���������, ��� � �� �������� ������� �� ���� �������... ���, �������, ��. �� �� - ������ ������.";
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_TurnRate_complite";
			}

		break;
		
		case "ship_tunning_TurnRate_start":
		    amount = TurnRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = TurnRateMatherial1; // GOOD_PLANKS
			    NPChar.Tuning.Matherial2 = TurnRateMatherial2; //  GOOD_LINEN
				NPChar.Tuning.Matherial3 = TurnRateMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "�� ���� ������ �� ���������� ������������� �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ������� - " + NPChar.Tuning.Matherial1 + ", ������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������, ������ ��� ��� �� ��������������. ��� � - � ������� ���� ��������...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "������ ���. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� ���������.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_LINEN, "jewelry3", "chest");
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "���� �������� ��������: ������� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������� - "+ sti(NPChar.Tuning.Matherial1) + ", ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	
	        shTo.Tuning.TurnRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... ������ ������� �������.";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			s1 = "������� ���������, ��� ����� �������. ������ ����� ������ " + shipHP;
			
			s1 = s1 + ". ����� �������� �������, ��� �����������: �������� ������ - "+ HPMatherial1 + ".";
			s1 = s1 + " �� ������ ������: ���������� ������� - "+ HPMatherial2 + ", �������� � ������� - "+ HPMatherial3 + ", ���� - " + HPWorkPrice + " �������� �� ������� �������... ����� ����� ����� ���� ����� � ������, �� �������, ������ ��, ������������ � ������� ������... ���, ������� � ��. �� �� - ������ ������.";
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_HP_complite";
			}

		break;
		
		case "ship_tunning_HP_start":
		    amount = HPWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = HPMatherial1; // GOOD_EBONY
			    NPChar.Tuning.Matherial2 = HPMatherial2; //  GOOD_SANDAL
				NPChar.Tuning.Matherial3 = HPMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");
			
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "�� ���� ������ �� ���������� ��������� ������� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: �������� ������ - " + NPChar.Tuning.Matherial1 + ", ���������� ������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������... �������, ��� � ������ �������� - ���, ��������, ������ ����.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "ship_tunning_HP_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_MAHOGANY, "jewelry17", "chest");
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "���� �������� ��������: �������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", ���������� ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: �������� ������ - "+ sti(NPChar.Tuning.Matherial1) + ", ���������� ������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}	
	        shTo.Tuning.HP = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			if(shTo.BaseName == "Flyingdutchman") // ��
			{
				dialog.text = "�� ��... ������� �������� � ������� �� ���� ����, �� ����� ����� � ��������� � ����������� ����� �� ������� ��� �������. �� �� ������ ��� ������"+ GetSexPhrase("��","���") +" ��� ��! �������, �� ����������� ����� � �������� ������ - ���� ������ ��������� �������� �����.";
				Link.l1 = "�������! ������� �����������.";
				Link.l1.go = "Exit";
				shTo.CabinType = "Cabin_Quest";
			}
			else
			{
				dialog.Text = "... ����� �� ���... ����������, ��� ��������� ���� �������� ������ ����� ����� ��������!";
				Link.l1 = "�������! �� � ���� ����� �� ������������������.";
				Link.l1.go = "Exit";
			}	
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			s1 = "������� ���������, ��� ����� �������. ��������� ������ " + FloatToString(shipWindAgainst, 2);

			s1 = s1 + ". ����� ��������� ��� ������ ����� ��� �����������: ������ - "+ WindAgainstMatherial1 + ",";
			s1 = s1 + " � � �������� ������ ������: ��������� - "+ WindAgainstMatherial2 + ", �������� � ������� - "+ WindAgainstMatherial3 + ", ���� - " + WindAgainstWorkPrice + " �������� �� ������� �������. ����-�� ���������... ����� �� ��. �� �� - ������ ������.";
            dialog.Text = s1;
			Link.l1 = "�������. � �������� �������. �� ����������� ����� ����������.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "���. ���� ��� �� ����������.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "� ������ ��� ������? ������ �� ������� ��������?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "����� ����������!";
				Link.l4.go = "ship_tunning_WindAgainst_complite";
			}
		break;

		case "ship_tunning_WindAgainst_start":
		    amount = WindAgainstWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1     = WindAgainstMatherial1;
			    NPChar.Tuning.Matherial2     = WindAgainstMatherial2;
			    NPChar.Tuning.Matherial3     = WindAgainstMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
                DeleteAttribute(NPChar, "Discount");
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "��� � ������. ��� �������� � ��� �������������.";
			    link.l1 = "�������"+ GetSexPhrase("","�") +" �� ����...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "�� ���� ������ �� ���������� ���� � ��������� �� ������� " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" ������-������� �������: ������ - " + NPChar.Tuning.Matherial1 + ", ��������� - "+ NPChar.Tuning.Matherial2+ ", �������� � ������� - " + NPChar.Tuning.Matherial3 + ". � �������� ������� ���� �������� " + NPChar.Tuning.Money + " �������. ������ ������ � ��� �������� �� ���� ����������.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "�� ���� �������...";
				link.l1 = "� ����� �����.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "��������� ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";
			    Link.l1 = "��. ���-��� ������� ���������.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
				Link.l2 = "� ���� ��������������� �������� �����.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "���. ��� �������.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "������� ���, �����"+ GetSexPhrase("�","���") +", ��� �� �������� ������� �� ������� ������ �������. ��������� ��� ������ �����������...";
			    Link.l1 = "���� ����. ������, ��� ������� ������...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_COTTON, "jewelry4", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "��� ������"+ GetSexPhrase("","��") +". �������! ������� ������...";
			    link.l1 = "���.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "���� �������� ��������: ������ - "+ sti(NPChar.Tuning.Matherial1) + ", ��������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "������.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "��� �������� �������: ������ - "+ sti(NPChar.Tuning.Matherial1) + ", ��������� - "+ sti(NPChar.Tuning.Matherial2) + ", �������� - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // �������
	        shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) + 0.5* stf(shTo.WindAgainstSpeed) / stf(shTo.Class) + 0.005, 2);
	        shTo.Tuning.WindAgainst = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... ����� �� ���... �������� ������ ����� ������ ������ �����.";
			Link.l1 = "�������! ������� �����������.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		///////////////////////////////  ��������� �����
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "� ���� �� �����, �� � ������ � ������, � ����� ����������� �������������� �� �����.",
                          "�� ��� �� �������? ��� ���� - ������� �������, ������� ���� � ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "��, ������...", "�������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "��������, � ���� ������, � ����� �������...";
				link.l2.go = "Step_Door_1";
			}
        // ==> �������� �� ������
            if (CheckAttribute(pchar, "questTemp.State.SeekBible"))// ����� �2, ����� ���������
            {
                if (!CheckCharacterItem(pchar, "Bible"))
                {
                    dialog.text = "��������...";
        			link.l2 = "����������, � ���� ������, ���� �� ����� ����� ���������� ����� �������, ����������� �� �������������?";
        			link.l2.go = "Step_S2_1";
                }
                else
                {
                    dialog.text = "�-�-�, ��� ������ ����. ������, �� ��� � ���� ���� ������� - ���"+ GetSexPhrase("","�") +" �����"+ GetSexPhrase("","�") +" � ���� �� ��� ����� �������"+ GetSexPhrase("","�") +"... �� �����, ��� ��� ���?";
        			link.l2 = "����� ���� ����� �� �����, ����� ������ ���������. ��, ������, ��� ��� �������, ��� ������ �����.";
        			link.l2.go = "exit";
                }
            }
			if (pchar.questTemp.piratesLine == "KillLoy_toAlexus")
			{
				link.l1 = "� ��� ������ ��� �������?";
				link.l1.go = "PL_Q3_1";
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.T1"))
            {
				if (pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork")
				{
					link.l1 = "������� ������� ��� '�������� �����'!";
					link.l1.go = "PL_Q3_SW1";
				}
				if (pchar.questTemp.piratesLine.T1 == "KillLoy_LoyIsDied")
				{
					link.l1 = "� ���� �� ����� ������� ������� ������������ ������ �����, ������� ��� ����...";
					link.l1.go = "PL_Q3_SW2";
				}
			}
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "���� ���������� ������.";
				link.l1.go = "Al_ShipLetters_1";// ���������  "��������� ���������"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if (pchar.questTemp.BlueBird == "toSeekBermudes") //������ ����� �����
			{
				link.l1 = "����������, ��� ����� ����� ���� ���� ���������� ������ ����������...";
				link.l1.go = "BlueBird_1";
			}
			if (CheckCharacterItem(pchar, "Ship_Print_1")) NPChar.print1 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_2")) NPChar.print2 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_3")) NPChar.print3 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_4")) NPChar.print4 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_5")) NPChar.print5 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_6")) NPChar.print6 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_1") || CheckCharacterItem(pchar, "Ship_Print_2") || CheckCharacterItem(pchar, "Ship_Print_3") || CheckCharacterItem(pchar, "Ship_Print_4") || CheckCharacterItem(pchar, "Ship_Print_5") || CheckCharacterItem(pchar, "Ship_Print_6"))
            {
				if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
				{
					link.l3 = "� ��� ����� ���-�� ��������� � ��� ������ ������ �� �����, �� ���������?";
					link.l3.go = "blueprint";
				}
				
			}
        // <== �������� �� ������
		break;
		
		case "blueprint":
			dialog.text = "��... �� �������� ��� �������� �������� ����. ���, ��� �� ����� � ��������� ��������� �����. ��� �������� �������������� ������� � ��������������������, ������ ����� ���������. � ��� ������� ����� �������� ��������� ������������ ������ ������ �������. ���� ������, � �� �������������� ���� ����������� ������� �����-������ �������. �� ��� ���?"
			link.l1 = "���� �����, ������� ���������.";
			link.l1.go = "blueprint_ordership";
			link.l2 = "��� ������� ����� ���������, �� ������� � ������ ���.";
			link.l2.go = "exit";
		break;
		
		case "blueprint_ordership":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchShipyard2(npchar);
		break;
//*************************** ��������� - "��������� ������� ���������" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "��������� �������.";
			s1 = "� ����, �� ���������� �����������, �������� ��������� ��������� ����� ������� ����������, ��� �� ���������� � ������.";
			s1 = s1 + "����� �� ����� � �� ��������� �� �������, �� ������������. ������ ������-�������� ��������� �������� ��� ������...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "�����-�� ���������! �������������, ������� ������ ������. ��� ��, ����� ��� ����������, �����"+ GetSexPhrase("�","���") +"! ";
			s1 = s1 + "��� ��� ��� ����������� ������ ����� ��������, � �, � ���� ������� ��������� ��� " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " �������. ��� �������?";
			dialog.text = s1;
			link.l1 = "�������� ����������� ��������! ������� �� � ������"+ GetSexPhrase("��","��") +"!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "�������, ���.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterReputation(pchar, -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
//*************************** �������, ����� �3, ������ ��� ***************************
		case "PL_Q3_1":
			dialog.text = "�������... � ��� �� ����� �����?";
			link.l1 = "�-�, ��� � �������� �� ������� �� ������� �� ��������� �������� �����. �� ����������� ��� ��������, ������, � �� ����� ��������� �� ��� �������.";
			link.l1.go = "PL_Q3_3";
			link.l2 = "� ��� ����, ����� �� ��������, � ��� � ������� �������, ��� �� ������� ����...";
			link.l2.go = "PL_Q3_2";
		break;
		case "PL_Q3_2":
			dialog.text = "���. ����, ������. ��� ������... ��� ������ ������������! ��, ��� ���, ��� � ��������, �����, ��� ����� ������ ����� ������� ���. ������� ���� �������\n����� ����, ���� ���� ��� � ����. ���, ���, ��� � �����������, ��������"+ GetSexPhrase("��","���") +", ����.";
			link.l1 = "�������! ��� ����!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "10");
			pchar.questTemp.piratesLine = "KillLoy_toJackman";
		break;
		case "PL_Q3_3":
			dialog.text = "��� �� ��� ������������ �� ������� �������? ��, ���� ���-�� ������� ���� ���������! �������������? �� ���� �������! ������ ������ �� ��������, � �������� ������ '�������� �����' �������� ���� ������...";
			link.l1 = "'�������� �����'?";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "'������� ����' ��� ����. ��� ����! ����� ������ ��� ��������! ��� ���� � ���� ������. �� ���������, ����������� � ����������! ����� ������ �� ������ ������������ ������ ��� ������, �� ���� ���������� �������� ������. �� �������, ����� �������� ��������� ������, �� ������� ��������������� ������ ��������! � ��� �� �������� �� ������...";
			link.l1 = "���, ������, ����� �������� � ������ ���.";
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = "��������? �, ��. ������ ���. ����-�� � �������� �����, �������� �����, � ��� ��, ���, � �������. � �����, ����� � ����, � ����� ����� �� �������� � ��������, ���������, ��� ������ ����������. ������� �����������... ������... ����� ������.\n����� ���� ������ ��... �-�-�...  ����� � ������ ������, ������� ������: '� ��� ������ ������, �� ���� ���� �������'. ��� � ��� � �������, ��� �� �� ��� ����� ����� ��� �����, ����� � ��� ���� ������ �������?";
			link.l1 = "������, � ���, �������, ������, �� ������, ���� �� ���������� ��������� � ������ ��� �������: ��� ���?!";
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = "��� �������� ������� �������. ����������, ��� ����� �����, ��� ��� ���� �����. ��������� �����, ���� ���� �� ��� ����� ���� �������.";
			link.l1 = "���� ��, ������� ������� ����"+ GetSexPhrase("","�") +" �������. �����, �������, ������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "11");
			pchar.questTemp.piratesLine = "KillLoy_toTavernAgain";
			//����� �������� ����� � �������
			sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "officer_9", "man", "man", 20, PIRATE, -1, true));
			sld.name = "�������";
			sld.lastname = "�����";
			sld.rank = 20;
			sld.city = "Pirates";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "CapGoodly";
			sld.greeting = "Gr_EvilPirate";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
            FreeSitLocator("Pirates_tavern", "sit2");
         	ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit2");
		break;

		case "PL_Q3_SW1":
			dialog.text = "�����, �����, ���� ��������. �� ���������, ����� �� �������� ���������.\n��������� �������. ���������� � ������� ����! ����"+ GetSexPhrase("","��") +" �������.";
			link.l1 = "��� �� � ����"+ GetSexPhrase("","��") +"...";
			link.l1.go = "exit";
		break;
		case "PL_Q3_SW2":
			dialog.text = "����! � ��� � ����... � ���?";
			link.l1 = "�� ������, �������....";
			link.l1.go = "PL_Q3_SW3";
		break;
		case "PL_Q3_SW3":
			dialog.text = "�� ��, ��� �����.";
			link.l1 = "�� �� ��������� ��, ��� ���������...";
			link.l1.go = "exit";
		break;
//*************************** ������ ����� ����� ***************************
		case "BlueBird_1":
			dialog.text = "��� �� ���. ��������, � ������� ���� ������ �� ������� ���� �� �� �����.";
			link.l1 = "�-�, �� �������. ������ ���������� ����������� ��� � ���. �� �������� �� ����� ��� ���������� ������ � �����?";
			link.l1.go = "BlueBird_2";
		break;
		case "BlueBird_2":
			dialog.text = "��-��, ���, �������, ���� ���������� � ��������. �������� ����, ��� ����� ������� ���� ����, ����� �� ���� ������� ����� �� ���� ����, ����� ����� ������ ����� ������� � �������� �������� ��� �� ����.";
			link.l1 = "��, � ���� ���-�� �� �����, ����� �� ���� ������ � ������?";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "� �� �������, ��� ���� ���-�� ������ ������� ����� �� ���� ����� � �����, ����� ����� �� �������?";
			link.l1 = "��, ��, �����... ��� ������, ����� ������ �� �������� ����� ���� �����?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "���, ����� ������ �� ��������, ������ ���� �������"+ GetSexPhrase("��","��") +".";
			link.l1 = "�� ��� ��, �������� ��� �������!";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "5");
			pchar.questTemp.BlueBird = "toCavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1 = "locator";
			pchar.quest.BlueBird_inCavern.win_condition.l1.location = "Bermudes_Cavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator_group = "quest";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator = "BlueBird";
			pchar.quest.BlueBird_inCavern.function = "BlueBird_inCavern";
			LAi_LocationDisableMonstersGen("Bermudes_Cavern", true); //�������� �� ��������
			LAi_LocationDisableOfficersGen("Bermudes_Cavern", true); //�������� �� �������
		break;	
//*************************** ���������� ����� ***************************
 		case "Step_Door_1":
			dialog.text = "��� �����. ����� ����� ������, ���� ���� ��������� ��� 20000 �����. �� ��������� - �� ������, � ���� ����� �� ��������� ����. �� � ���� ��� ������� �� ������� - �� � �����...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "��� ���� ������, ��������.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "��� � ���� ����� �����.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "��� ���! ������� �� �����-�� �����.";
    		link.l2.go = "exit";
		break;
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "�������, ����� �������. � �� ���������!";
			link.l1 = "�� ���� �� ���, ������� ����, " + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
 		case "Step_Door_3":
			dialog.text = "�� ��� ����� �����, ����� � �������. � ��� � �� ���������� - ����������...";
			link.l1 = "����, �� ���� ������ ������� ���!";
			link.l1.go = "exit";
		break;
//*************************** ����� �2, ������� � ��������� �� ������ �� ��������� ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("�-�-�, ������� ������... � ����� �� ��� �����?", "� ��� ��� ������ - ����� �������.", "��� ��� ��������� - ����� �������.", "��������, �� ������� �����, �?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ���� ���� �����, ������� ��� �� �����������. �� ���.", "� �����"+ GetSexPhrase("","�") +"...", "�������...", "��� ���"+ GetSexPhrase("��","��") +" � ��������� ���������"+ GetSexPhrase("��","��") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = "�������. �� ������, ��� ��������������, �������, ��� ���������� ���� �� ����. ����� �������� �����-�� �������� � ���� ������� ���������. � �� ������ �� ������.";
			link.l1 = "������?";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "�� ������� ����� �� ���� ����� - �� ���� ��, ���� �� ��� ���� �������... ���� ���� �������, ��, �����, "+ GetSexPhrase("�� �� ���������, �� � ������...","������� ������, ��������� ������ ������.") +"";
			link.l1 = "���� �� ��� �������?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "����, ���� ����� ��� �������. � ��� �����, ��� ������ �� ����.";
			link.l1 = "� ���, �� ������? � ������ �� ������ ���� �� ��������?";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = "�� ������ ����������, ��� ��� �������� - ��� ��������, ����� � ���� ����� ��������, ��� ��� ����. � �� ������ ������, ��� ������ ���, ����� ������. ������� ���, ������, ��� � ������...\n"+
                          "����� ��� �� ���� ���, ��� ���. �� ����� ����� ������ ����� ���������, ��� ����� � ����� ������...";
			link.l1 = "��� ��� ����... ��, �� ��� ��, ��������.";
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = "�������, �������... ������, ��� ����� ���� ��� �� ���� �����.";
			link.l1 = "�������, �� ����������.";
			link.l1.go = "exit";
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            LocatorReloadEnterDisable("Shore3", "reload2_back", false);
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1.location = "Bermudes_Dungeon";
            Pchar.quest.Inquisition_fightInDangeon.win_condition = "Inquisition_fightInDangeon";
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry5 = 200;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry17 = 300;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade33 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade28 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade34 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade32 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade23 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry7 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potionwine = 3;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry1 = 100;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry2 = 80;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry3 = 60;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry4 = 45;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.icollection = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.chest = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian11 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian15 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian12 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.Bible = 1;
		break;
		case "PayToRapair1":
			if (pchar.paytorepair != pchar.dayRandom && CheckAttribute(PChar,"paytorepair")) DeleteAttribute(PChar,"paytorepair");
			dialog.text = "�������" + GetSexPhrase("��","��") + ", � ��� ���������� ��� ��� ��������� ������ �������, �� ������ ��� �� � ��� ��� ��� ������?!";
			link.l1 = "� ��� ����" + GetSexPhrase("�","��") + ". ������� 15000 ����� �������� ������ ���� ������?"
			link.l1.go = "PayToRapair2";
			link.l2 = "�����, ������ �� �����.";
			link.l2.go = "exit";
			if (CheckAttribute(PChar,"paytorepair")) 
			{
				dialog.text = "����� ����� ���������� �� ����� ��������! �� ��� ��� ������� �� �������... �����, ��� ��� �����?";
				link.l1 = "��� ����� �������� �������."
				link.l1.go = "shipyard";
				link.l2 = "��� ����� ������ �� �������.";
				link.l2.go = "Cannons";
			}
			
		break;
		case "PayToRapair2":
			pchar.paytorepair = pchar.dayRandom;
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "���, ������ ����! ��� ��� �����?";
			link.l1 = "��� ����� �������� �������."
			link.l1.go = "shipyard";
			link.l2 = "��� ����� ������ �� �������.";
			link.l2.go = "Cannons";
		break;
		
		//��������� ���
		case "WarDogUpgrade_1":
			dialog.text = "�� ��? ��� ����� �� ������� �� ������, ��� ��� ����� � ��� �������������.";
			link.l1 = "��� ��� ���� ����������? ������ ����������, �� ���������� �� �����.";
			link.l1.go = "WarDogUpgrade_2";
		break;

		case "WarDogUpgrade_2":
			dialog.text = "��, �� ������� ����. � �� ����, ��� ��� ���������. ����� � ��� �����, ��� �������, �������, ������. ���� �� � ����� ������������� ��� ������, �� �������� �� ������ ������.";
			link.l1 = "������� ��� ��������� �����? �� ��� ��� �������� ��� ��� ��������. ������� ������ �������, ��� � ����������� �� �������.";
			link.l1.go = "WarDogUpgrade_3";
		break;

		case "WarDogUpgrade_3":
			dialog.text = "�� ��� �� ���� ���� �������, �����������, ������... ";
			link.l1 = "������? � �� ������ ��� ����������? �������� ������ ��� ��������, ��� �������.";
			link.l1.go = "WarDogUpgrade_4";
		break;

		case "WarDogUpgrade_4":
			dialog.text = "���� ��. � ���� ������ ����� ������ ���������� ���, � '���' ����� ����������� ������, �� ������� ����� ������ ������� � ���. � ���� ��, ���� ��� �� ��... � ��������� ����� ��� �������� ������������ � ����� ������ ��������. ����\n���� ������� ��� ���� ������, ����, ��� � ����, � ������� �� ����. ";
			link.l1 = "���� �� ������?";
			link.l1.go = "WarDogUpgrade_5";
		break;

		case "WarDogUpgrade_5":
			dialog.text = "���� ��� �� ���������� ���� �������-��������, �� ���� ������ �������. �� �������� ���� ������ �� ���� ����, ���� ����� ����, � �� ���������� ���������� ���� ��� ������ ���������� �����������\n���� �� �� ������������ �����, ��� ��� ����, ��� ��� ��� '���������� ����' - �� ����� ���� ��� ������ �������, ������� � �� ��� ��� ���� ������� ��������. ������ ��, �� ��� ���� ��������, ���� ������� �� ����� ��� ������������� � ����� ��������������� �������� � ������ � ����������\n� ������� �� ������, ����� ������ ������������� �������. '�������' - ��� �� ��� ������. ����� ����������! ����!";
			link.l1 = "'�������'... ������ �������. ��� �� � ����� ��� �������?.. �������, �������, ���������.";
			link.l1.go = "WarDogUpgrade_5_1";
		break;

		case "WarDogUpgrade_5_1":
			dialog.text = "�� ������ ��� ������-�� ����������� ������, � ��� ���������� ����� ��� ������� �� ��������� ����� �� ��������. �������, ���� ������� ���� ��������� ����������, ��� ��� ��� ����� �� ������������ ���� �������, ���� ��� �� ����� �������, ���� ������ �������� ����� ��� ����������. �� ���� ������� - ���� �������, ����� �� ���� � ������������� �������.\n� ����, ����� �� ������ ������������� ������� � ���� ����� ������� � ������� ��� �������. ������ '��������������', � � ��������� ��� �������� '���'.";
			link.l1 = "� ��� �����, ����� ����� ����������� ����� ��� �� �������? ����� �� � ������ �������������?";
			link.l1.go = "WarDogUpgrade_6";
			
		break;

		case "WarDogUpgrade_6":	
			dialog.text = "���� ��� ������ ������ ������� �� �������, �������� ��� � ������ ����� ����������. �� � ����������, ��� ���� ������� ��� �������� ������ �������, �������� � ���� ��������. � ���� ��, �� ������ �����, ���� ������ ��� ����� �� ���������, ��� ��� �������� ����� � ���� ����� ������ ����\n� �� �������� � ������ ������! ���� ����, ��� ������� ��� ������, ����� �������� ���� �������, � ���� �� �� ���� ����������� ���� � ��� ��������������� - ���, �������� ��� ����� ������ ���� �������� ��� ������. ������ ����� ��� �� ���.";
			link.l1 = "���� �����-������ ������, ��� ��� �������?";
			link.l1.go = "WarDogUpgrade_6_2";
		break;

		case "WarDogUpgrade_6_2":
			dialog.text = "���� �� ����... ���� ������, � ������ ������� �� ����, ��� ����� �� ������ ������. �� ������ ����������� ������ ������� ����-������ ������ � ������������ �� ��� ��������, ���� ������� ������� ������� ������� �������� ������ �������.";
			link.l1 = "�����-�� �� ������� ����������� � ���� ������. � ��������, ��� ������ �� ������. �����, ���-������ ���������. ��� ��� ������ ���� �������?";
			link.l1.go = "WarDogUpgrade_6_1";
		break;

		case "WarDogUpgrade_6_1":
			sld = GetCharacter(NPC_GenerateCharacter("W_Titanic", "off_eng_1", "man", "man", 99, ENGLAND, -1, true));
			FantomMakeCoolestSailor(sld, SHIP_BATTLEMANOWAR, "�������", CANNON_TYPE_CANNON_LBS48, 100, 100, 100);
			ref W_Titanic = &RealShips[sti(sld.Ship.Type)];
			W_Titanic.HP = 30000;
			W_Titanic.MastMultiplier = 0.01;
			W_Titanic.TurnRate = 40;
			W_Titanic.MaxCrew = 3500;
			W_Titanic.MinCrew = 3000;
			W_Titanic.SpeedRate = 14;
			W_Titanic.WindAgainstSpeed = 4;
			//W_Titanic.HullArmor = 60;
			W_Titanic.Capacity = 100000;
			
			SetCrewQuantityFull(sld);
			ProcessHullRepair(sld, 100.0);
			
			sld.ship.Crew.Morale = 100;
			ChangeCrewExp(sld, "Sailors", 50);
			ChangeCrewExp(sld, "Cannoners", 50);
			ChangeCrewExp(sld, "Soldiers", 50);

			AddItems(sld, "talisman3", 1);
			EquipCharacterByItem(sld,"talisman3");
			
			SetHalfPerksToChar(sld, true);
			SetCharacterPerk(sld, "CannonProfessional");

			sld.rank = 60;
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);

			SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
			SetCharacterGoods(sld,GOOD_FOOD,5000);
			SetCharacterGoods(sld,GOOD_BALLS,50000);
			SetCharacterGoods(sld,GOOD_GRAPES,0);
			SetCharacterGoods(sld,GOOD_KNIPPELS,0);
			SetCharacterGoods(sld,GOOD_BOMBS,50000);
			SetCharacterGoods(sld,GOOD_POWDER,100000);
			SetCharacterGoods(sld,GOOD_PLANKS,150);
			SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
			SetCharacterGoods(sld,GOOD_RUM,200);
			SetCharacterGoods(sld,GOOD_WEAPON,600);
			SetCharacterGoods(sld,GOOD_MEDICAMENT,300);
			
			sld.Abordage.Enable = false;
			sld.Tasks.CanBoarding = false;
			sld.CantBoardEnemies = true;
			//sld.AlwaysFriend = true;
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.AlwaysSandbankManeuver = true;
			Group_FindOrCreateGroup("WarDog");
			Group_SetType("WarDog", "pirate");
			Group_AddCharacter("WarDog", sld.id);
			Group_SetGroupCommander("WarDog", sld.id);
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			
			LAi_SetImmortal(sld, false);
			//Group_SetPursuitGroup("WarDog", PLAYER_GROUP);
			Group_SetTaskAttack("WarDog", PLAYER_GROUP);
			Group_LockTask("WarDog");
			
			WhisperTitanic_ToRandomTown()
			Group_SetAddress("WarDog", pchar.TitanicCity, "Quest_ships", "reload_fort1_siege");	
			pchar.TitanicIsKicking = true;
			SetFunctionNPCDeathCondition("WhisperTitanic_Is_Dead", "W_Titanic", false);
			pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1          = "location";
			pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1.location = pchar.TitanicCity;
			pchar.quest.WhisperTitanic_SurrenderFort.function             = "WhisperTitanic_SurrenderFort";	
			
			SetQuestHeader("WhisperTitanic");
			AddQuestRecord("WhisperTitanic", 1);
			AddQuestUserData("WhisperTitanic", "sCity", XI_ConvertString("Colony" + pchar.TitanicCity + "Gen"));
			dialog.text = "�������, �� ������ ���� � ����� . ������� �� � ���� ��������� ������������, �� '�������' ����� ������� �� ��������. ������ ����� �� ��� ��� ������� ����������, ���� �� ������� ����� �������. � ��� ������, ������ ����������\n� ���� �� �� ����, ������ �������� ��� '���' �����-�� �� ����� ��������� ���������. ��� ������ � ���������� � ������������ �������.";
			link.l1 = "��, ���������, ��� ����� ��������.";
			link.l1.go = "ship_tunning_start";
		break;

		case "WarDogUpgrade_7":
			dialog.text = "��, ��� ��������� �������?";
			link.l1 = "���� �����.  ";
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "TitanicIsDown"))
			{
				link.l1 = "������������� �������. ��������� ������ ������� �������� �������� � �����. ��, ������ �������� ������ ���� �������� �� ������, ���� ��������.  ";
				link.l1.go = "WarDogUpgrade_8";
			}
		break;

		case "WarDogUpgrade_8":
			DeleteAttribute(pchar, "TitanicIsDown");
			dialog.text = "��, ������� �������. ������ � ���� ������ ����������� ��������. �������, '�������' ����� ����-�� �� �����, ��� ��������� �� �������� ������, ��� ������������ ������� ��� �������.";
			link.l1 = "��� ������ ���� ����� ����? � ����� �������� ���!";
			link.l1.go = "WarDogUpgrade_9";
		break;

		case "WarDogUpgrade_9":
			dialog.text = "������? �� �����, �����, ����.";
			link.l1 = "��� ��� ������ ��������� ��� ���? �� ������ �������� ��, ���� � ������ � '���������'.";
			link.l1.go = "WarDogUpgrade_10";
		break;

		case "WarDogUpgrade_10":
			dialog.text = "�� ��... � ������ ���� ����� ��������, �������� ��� ����� ��������\n������� ��� ������ ������ ������, ��� ��� ��� ���� ��������� � ������� ��������. ";
			link.l1 = "���?! �� � ����� �� ��������������.";
			link.l1.go = "WarDogUpgrade_11";
		break;

		case "WarDogUpgrade_11":
			npchar.WarDogUpgradePayment = true;
			AddQuestRecord("WhisperTitanic", 3);
			dialog.text = "�������, ��� ����������� ������������ ������. ��������, ��� ������ �������� � �� ���������� ������� ������, ��� ��� �� ������ ������. � ��� ����� ���, ����� � �� ����� � ������, ���� ���� ��������.";
			if(sti(pchar.money) >= 1000000)
			{
				link.l1 = "��� ���� �������, ������ ���������.";
				link.l1.go = "WarDogUpgrade_pay";
			}
			link.l2 = "�� ��. ��� ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "WarDogUpgrade_pay":
			DeleteAttribute(npchar, "WarDogUpgradePayment");
			dialog.text = "��� �, ���������...";
			addMoneyToCharacter(pchar, -1000000);
			link.l1 = "�����, � � ��������.";
			link.l1.go = "WarDogUpgrade_pay_2";
		break;
		
		case "WarDogUpgrade_pay_2":
			AddQuestRecord("WhisperTitanic", 4);
			CloseQuestHeader("WhisperTitanic");
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
			}
			iCaliber = iCaliber + 1;
			switch(iCaliber)
			{
				case 5:
					iCaliber = 36;
				break;
				case 6:
					iCaliber = 42;
				break;
			}
			shTo.MaxCaliber = iCaliber;
			
			GetBaseShipParam_ToUpgrade(shTo, "SpeedRate", 2.0);
			GetBaseShipParam_ToUpgrade(shTo, "TurnRate", 10.0);
			GetBaseShipParam_ToUpgrade(shTo, "HP", 1000);
			GetBaseShipParam_ToUpgrade(shTo, "MaxCrew", 120);
			GetBaseShipParam_ToUpgrade(shTo, "WindAgainstSpeed", 1.0);
			GetBaseShipParam_ToUpgrade(shTo, "Capacity", 700);
			shTo.HullArmor = 30;
			shTo.OptCrew = 300;
			
			DeleteAttribute(npchar, "WarDogUpgradePayment");
			DialogExit();
			AddCharacterExpToSkill(pchar, "Repair", 5000);
			SetLaunchFrameFormParam("������ �����. �������� �� ������� ��������, �� ������ ����� ������ � ��������������� � ���������� �������.", "", 0.1, 15.0);
			LaunchFrameForm();
			WaitDate("",0,0,30, 0, 20);
			npchar.dialog.currentnode = "WarDogUpgrade_pay_1";
		break;
		
		case "WarDogUpgrade_pay_1":
			dialog.text = "�� ��� � ��. ������ ��� ������������� �� ������ �������� '���' ����� �� ����� �����. ��� ������ �������� � ����. ������ ������������ ���, �� ����, ����� ��� ����� ����� ��������.";
			link.l1 = "�����, ����� ���������.";
			link.l1.go = "exit";
		break;
		//<-��������� ���
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

void checkMatherial(ref Pchar, ref NPChar, int good1, int good2, int good3)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial1);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial1);
    }
    RemoveCharacterGoods(Pchar, good1, amount);
    NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

    amount = GetCharacterItem(pchar, good2) - sti(NPChar.Tuning.Matherial2);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial2);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial2);
    }
    TakeNItems(pchar, good2, -amount);
    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;

    amount = GetCharacterItem(pchar, good3) - sti(NPChar.Tuning.Matherial3);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial3);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial3);
    }
    TakeNItems(pchar, good3, -amount);
    NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;
}

void GetBaseShipParam_ToUpgrade(ref shTo, string param, float num)
{
	string sAttr = "Bonus_"+param;
	Log_Info(sAttr);
	int iRealShipType = sti(shTo.basetype);
	string sParam =	GetBaseShipParamFromType(iRealShipType, param);
	if(CheckAttribute(shTo, sAttr))
	{
		shTo.(param) = stf(shTo.(param)) - stf(shTo.(sAttr));
		shTo.(sAttr) = stf(shTo.(sAttr)) + num; 
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
	else
	{
		shTo.(sAttr) = num; 
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}	
}
