// ����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator;
    int iTime, n;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

/*
	switch(Pchar.questTemp.CapBloodLine.stat)
    {
  		case "1":
            Dialog.CurrentNode = "First Bishop";
		break;
		
		case "2":
            Dialog.CurrentNode = "First Guard";
		break;
		
		case "3":
            Dialog.CurrentNode = "First Stid";
		break;
		
		case "4":
            Dialog.CurrentNode = "First MsStid";
		break;

    }
    */


	switch(Dialog.CurrentNode)
	{
	    // --> �����
		// ----------------------------------- ������ ������ - ������ �������
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Exit_Away":
            
            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
        case "GFight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            sld = &characters[GetCharacterIndex("Dragun_0")];
            LAi_SetCheckMinHP(sld, 1, true, "Dragun_0_CheckMinHP");
            LAi_SetImmortal(sld, false);
   	        LAi_SetWarriorTypeNoGroup(sld);//fix
   	        LAi_warrior_DialogEnable(sld, false);//fix
            LAi_group_MoveCharacter(sld, "TmpEnemy");
            //LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            LAi_group_Attack(sld, Pchar);
            LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);//fix
            LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_ActorRunToLocation(NPChar, "goto", "goto6", "none", "", "", "", 20);
			LAi_ActorGoToLocator(NPChar, "goto", "goto6", "", -1);

		break;
        
        case "fight1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true)
			AddDialogExitQuest("MainHeroFightModeOn");
			Spain_spyDie("");
			AddQuestRecord("WeaponsForEscape", "5");
			
		break;
		
        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");

		break;
		
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RestoreBridgetown();
			initMainCharacterItem();
            ref mc = GetMainCharacter();
            mc.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, mc);
            mc.Ship.name="��������";
            SetBaseShipData(mc);
            mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,2000);
        	SetCharacterGoods(mc,GOOD_BALLS,2000);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,400);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,2000);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,2000);
            SetCharacterGoods(mc,GOOD_PLANKS,10);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,2000);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("������ ����� ���� ���!!! ��� ��� �� ����� ��������?! ��, ������, ��������...", "��, �� ���� ��� ��� ���������?! �����, ������� �������� ����? ��, ����� ���� �����...", "������, �� ���� ��� �����? �� �� ���, �����������! ��, ������, ��� �� �������, ������...");
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			//if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "NextQuest":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Pchar.questTemp.CapBloodLine.stat = "";
            CapBloodLineInit("");
		break;


          


		

		case "First time":
        	dialog.text = "������";
            link.l1 = "...";
            link.l1.go = "Exit";
            npchar.quest.meeting = "1";
            
            if (npchar.id == "Pitt")
            {
     			if (bBettaTestMode)
                {
			        link.l0 = "BetaTest - ���������� � ������ ����.";
			        link.l0.go = "Finish";
                }
                
                if (Pchar.questTemp.CapBloodLine.stat == "Begining")
                {
                    dialog.text = "���� ������ ������ �����... �� �����, � ����... � ��������� ��� ����... �� ������ ���� �� ����... ������ � ����! ������!";
            		link.l1 = "�������, ����... � ����� � ����, � �� �������� ��� �, ���� �������, ��� ���� ������ ����������� �������, ���������� ���������� ���.";
                    link.l1.go = "Exit_Away";
                    Pchar.questTemp.CapBloodLine.sLocator = "reload1";
                    Pchar.questTemp.CapBloodLine.iTime = -1;
           			if (bBettaTestMode)
                    {
				        link.l3 = "BetaTest - �� ������� ������.";
				        link.l3.go = "NextQuest";
                    }
            		break;
        		}
        		
                if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                    dialog.text = "�����, ��������� ����� ����������� ���� ���� �����, � ���� ����������� ����� �������. ���� ����� ������ ���� � ���������� ����������� �����.";
            		link.l1 = "�������, ����, �� ������ ���.";
            		link.l1.go = "Exit";
            		break;
        		}
                if (Pchar.questTemp.CapBloodLine.stat == "WakerOfferComplited")
                {
                    dialog.text = "��� ������, ���� ���?";
            		link.l1 = "������ ������, ��� �� ����� ���������� ���� ���������� ������, �������.";
            		link.l1.go = "PStep_0";
            		break;
        		}
        		
                dialog.text = "������, �����, ��� ����� ���� ��������.";
        		link.l1 = "������, ���.";
        		link.l1.go = "Exit";

    		}
    		
            if (npchar.id == "Beyns")
            {
                dialog.text = "�, ������������, ������ ����, ��� ������, ��� �� ������. ���� ������ ������ �����... �� ����� ������ � ������� �� ������ �����, � �������� ����� ����...";
        		link.l1 = "� ������, ��� ������ ����. � ���������� ��������� � ����, � �� ���� ����������� ������� ���� � ������� �������.";
        		link.l1.go = "EBStep_0";
    		}
    		
            if (npchar.id == "CapGobart")
            {
                dialog.text = "� - ������� ������ �� ������ ���������� �����. �� ��������� ����������? ��� �� ������ ����� �� ������ �����?";
        		link.l1 = "�� �� �������� ����������, ���. ���� ���������� �����...";
        		link.l1.go = "CGStep_1";
        		DragunInvansion4();
    		}
            
            if (npchar.id == "Bridgetown_Mayor" )
            {
                if( Pchar.questTemp.CapBloodLine.stat == "CureMisStid" )
                {
                    dialog.text = "� ��� ����� ���� ������� �� �������. ������ ��� �����?";
            		link.l1 = "� �������� ��� �����������. ����� ��������, ����������.";
            		link.l1.go = "SStep_0";
            		link.l2 = "���� ���� ��������� ����, ���������� ����. ��� ����������, ���� ������� �������� ����������, � ��� ��� - ��������� ����������� ������� ������������ ��� � ���� ������� ��������� ������.";
            		link.l2.go = "SStep_1";
            		break;
                }
                
                if( Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape3" )
                {
                    dialog.text = "�����������, ������ ����. ���� ������ �� ��� �����?";
            		link.l1 = "������ ����, ����������. � ������ ��� ����������������� ��������� ��� ����� ������� � ����� �� ����� ����������� ��������� ��.";
            		link.l1.go = "SStep_9";
            		break;
                }
                dialog.text = "��� ��� ������ ������ ����?";
          		link.l1 = "���, ������, �������� �� ������������.";
          		link.l1.go = "Exit";
 		         NextDiag.TempNode = "First time";
    		}
    		
    		if (npchar.id == "MisStid" && Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
    		{
            	dialog.text = "�, ������ ����! �������-��... ����������, �������� ���!";
        		link.l1 = "������ �����, ������ ����. �� ����������, �� ������ ����������� � ��������� ��������� - ��������� � ���������� �� ����, ��� ����� ������ ���� �����.";
        		link.l1.go = "MSStep_0";
    		}
    		
    		if (npchar.id == "Nettl" ) // && Pchar.questTemp.CapBloodLine.stat == "CureMisStid"
    		{
            	dialog.text = "��, ������... � � ������ ��� �... �... �������. ����� ����... �������? �� ��, �������... ��, �������. �� ������ ��, ��� ����� ���... ��������� ���-��, �... � ����� �������� ���-��... ���-�� ������ �� ���, ���... �� ���, ��� �����?";
	            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
                {
                	link.l1 = "������ ����������, ��� ���� ��� ��� ���� �������� �����.";
                    link.l1.go = "NStep_6";
                }
                else
                {
            		link.l1 = "� �� � ��� ����� ��� �����, �������.";
            		link.l1.go = "NStep_0";
                }
    		}
    		
    		if (npchar.id == "Waker")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                	dialog.text = "������ ����, ��� � ��� ��� ������! � ����� ��� �������, �� ������ ��� �� ���������� ������� - �� �������������� �� ������, ������ �������.";
            		link.l1 = "����� �������. ��� � ���� ����� ������� ����?" ;
            		link.l1.go = "WStep_0";
            		link.l2 = "������ �����. ��� � ���� ����� ������� ����?";
            		link.l2.go = "WStep_1";
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
                	dialog.text = "� ������, ������ ���� �������� � ��� ���� �������. ��� �, ��������� � ��������������� ���������, ������ ����! ��������� � �������! ��� ���� ����� �������� ������������, �������� ����� �� ����� ���!";
            		link.l1 = "��� �������, � �������� ���� �����. ���������� �� �� �� ����, � � ������������ ������. ���� �����, ��� ��� ���������. ���� � ��� ���, �� � ������ ����������..." ;
            		link.l1.go = "WStep_3";

                }
    		}
    		
    		if (npchar.id == "Den")
    		{
            	dialog.text = "����� ������, ������ ����. ���� � ������, ��� �� ������ � ���� ����?";
        		link.l1 = "� ������ ���� ������� �������, ���� ������ ������� � ���. � �������� �� � �������� ��� ����������� � ��� � ����� ������� ��� �� ����������� ����������. �� ��������� ��� ����, � ����� ���������, �� ��� ��������� �������." ;
        		link.l1.go = "DStep_0";
    			if (GetCharacterItem(pchar,"migraine_potion") > 0)
    			{
            			link.l2 = "� ������ ���� ������� �������, ���� ������ ������� � ���. � �������� �� � �������� ��� ����������� � ��� � ����� ������� ��� �� ����������� ����������. �� ����� ��� ���������, � �������� ���� ����� ��������� ��� ���������� - �������� ������ ���������. ����� ��������.";
            			link.l2.go = "DStep_1";
    			}
        		link.l3 = "� ������ ����� ��������, ��� ��� ���������� ������ �����, ������ ���.";
        		link.l3.go = "DStep_2";
    		}
    		


    		if (npchar.id == "Griffin")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1" && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "������ ������� �� ������������ ��� �����, ���������... �, ��� ��, ������ ����!";
            		link.l1 = "������ ����, ������ �������. ����� �������� �� ������������� ���������, �� � ���� � ��� ����, �� �������� �������������.";
            		link.l1.go = "GRStep_0";
            		break;
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {

                    dialog.text = "�� ��� �����, ������ ���� �������?!";
            		link.l1 = "� ������ ����, ���� ����������." ;
            		link.l1.go = "GRStep_10";
            		break;

                }
                
                dialog.text = "��� �� ����� �����, ������ ���� �������?!";
                link.l1 = "� ������ ����, ��� �����." ;
                link.l1.go = "Exit";
    		}
    		
    		if (npchar.id == "Hells")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_1")
                {
                	dialog.text = "������ ������� ��� ���� ����?! ���������!..";
            		link.l1 = "��������, � - ����� ����, ���� ����������. � �� ������� ��� �����.";
            		link.l1.go = "HStep_0";
            		link.l2 = "��� �� �� �������...";
            		link.l2.go = "fight1";
            		break;
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
                {
                	dialog.text = "�, ��� ������, ��� �� �����...";
            		link.l1 = "��� ���� ������?";
            		link.l1.go = "HStep_5";
            		break;
                }

                dialog.text = "��� �� ����� �����, ������ ���� �������?!";
                link.l1 = "� ������ ����, ��� �����." ;
                link.l1.go = "Exit";
    		}
    		
    		if (npchar.id == "Quest_Smuggler")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape" && sti(Pchar.reputation) >= 50  && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "������ � ���, ������ ����. �� �����, � �����-�� ����, �������� ��������� ����� ������� �����, ��� ����� �� ����������. ��� �� � ���� ��� ��������?";
            		link.l1 = "� ������ ����������, �� ����� �������� ����. ��� ���� � ���, ��� ��� ����� ������...";
            		link.l1.go = "QSStep_0";
            		break;
                }

                dialog.text = "������������, ������ ����, ���� ������, ��� �� �� ���� �������������, �� ��� ������� �� ������. ��� ��� ��� ������ ���� ����� �������.";
                link.l1 = "���� ���� �������� �� ������ � ��� �����... ���� �� ����� - ��� ����." ;
                link.l1.go = "Exit";
    		}
    		
    		if (npchar.id == "Spain_spy" )
    		{
            	dialog.text = "��, ��! �������...";
        		link.l1 = "��� ���� ������?";
        		link.l1.go = "SSStep_0";
    		}
    		
    		 if(npchar.id == "Volverston")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "�-�, �����, ��� ���� ������!";
                    link.l1 = "�� ������ ��������� ��� � ��� ���������� ����� ������� �� ��������� �������� �� ���� � ����������� ������� ������� ���������� �����?";
                    link.l1.go = "VLStep_0";
              		break;
                }
                dialog.text = "�-�, �����, ��� ���� ������!.";
                link.l1 = "����������, ����������. ������, �� ��� ����� ����.";
                link.l1.go = "Exit";
                
    		 }
			 
    		 if(npchar.id == "Hugtorp")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "� ��� � �����, �����. ������� ������ ������� ��� ����, ��, ���, � �������� �������� ����.";
                    link.l1 = "�� ������? �� ������������ � ���-��?";
                    link.l1.go = "HTStep_1";
              		break;
                }
                dialog.text = "�����������, �����. ����, ������� �� ��� ��������� - ������ ������, �������.";
                link.l1 = "� ���, ��� �� ����������.";
                link.l1.go = "Exit";
                
    		 }
    		 
    		 if(npchar.id == "Dieke")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "��� ���� ���� ������� ���, ������?";
                    link.l1 = "������, ����� ���� ������, �������. ���� ��� ��������� ����, ��� �� ��������?";
                    link.l1.go = "DKStep_0";
              		break;
                }
                dialog.text = "��� ���� ���� ������� ���, ������?";
                link.l1 = "���, ������, ������ ��� ����.";
                link.l1.go = "Exit";
    		 }
    		 
    		 if(npchar.id == "Ogl")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = TimeGreeting() + ", ������ ����.";
                    link.l1 = "��� ������ ������, ���? ���� ��� ����� � ������������?";
                    link.l1.go = "OGLStep_0";
              		break;
                }
                dialog.text = TimeGreeting() + ", ������ ����.";
                link.l1 = "������.";
                link.l1.go = "Exit";
    		 }


            
		break;
		
		
		case "First Bishop":
            if(NPChar.quest.meeting == "0")
            {
            	dialog.text = "� ���� ����������� ����� �������. ���������� ����������� � ���������� ����� � ����� ��, ��� ������.\n����� ���������, ���� ����� ����... � �� ��� ���� ���� ��������� ���� ��������� ���������!\n������ � �����, ��� ���� ������ ��������. ����...";
                link.l1 = "...���� ����� � �������, ������� �� ������ ������ ��������������� �����������, ���������� �� ��� ������������ ��������� �� ���������. ����� �� ���, �� ��� �� ���� ������������ � ������������. � ���� �� ������, ���� ���������� ���� ��������� �������� � ��������� �������, � �������� ���� ��� ��������, � ����� ����������� � �������� � ��������� ��.";
                link.l1.go = "BStep_0";
                npchar.quest.meeting = "1";
            }
            else
            {
           	    dialog.text = "�������� ������, ��������� ����������, � �� � ������� �������� ���� � �������!";
                link.l1 = "��� �������.";
                link.l1.go = "Exit";
            }
		break;
		
		case "BStep_0":
        	dialog.text = "�� �������� ���, ���!\n���� ������ ������� ��������� ������, ��� ��������������� ��������� � ���� �������� �������� �������� �������� ����������� ��������.\n����� ���������, ��� ���� ���������� �������� ����� �� ��������� ������ ����, ����� �������� �������� �� ������! ����� ���� �����, ���.";
    		link.l1 = "�������, �� ������ ��������, ���������� ����, ����� ������ ���� ��������� � ������ ������.";
    		link.l1.go = "Bishop_Away";
            LAi_LockFightMode(pchar, false);
            chrDisableReloadToLocation = false;
            LAi_LocationFightDisable(loadedLocation, false);
            Pchar.questTemp.CapBloodLine.stat = "CureMisStid";
            NextDiag.TempNode = "First Bishop";
			
            //����� 4 ����
            PChar.quest.CapBloodLineTimer_1.win_condition.l1            = "Timer";
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.hour  = 4;
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.function = "CapBloodLine_q1_Late";
            AddQuestRecord("CapBloodLine_q1", "1");

		break;
		
		case "BStep_1":
        	dialog.text = "���� �� ������ ������ ���� ��� � ��� ����, ��� �������� ���-��� �����������, ��������, ����� �� �� ���������� � �� ������������� ��������������� ���� ��������. �� �������, ��� �� ���������� ���������!";
            link.l1 = "��� ��� ����� �� ���� ����������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
		break;
		
		case "BStep_2":
        	dialog.text = "�� �������� ��� ���� ������ �����! ��������� ��� ��������, � ����������� � ��� ������� ��� � �������. �� �� ������� �� ���� ������ � ����� �� ����?";
            link.l1 = "�� ����������� ������� �������� �����?";
            link.l1.go = "BStep_3";
		break;
		
		case "BStep_3":
        	dialog.text = "...� �� ��� ���� ��� ����� �����... ���? ����� ���� ���� �� ����� �����������, ���?";
            link.l1 = "���� � ���, ��� � ����... ��, � ���� ������ �������� �������...";
            link.l1.go = "BStep_4";
		break;
		
		
		case "BStep_4":
        	dialog.text = "��� �� ������? �� ���� �������� � ��� ����, ����� � �������� ���� ��������, �������������� ������� �� ����������!..";
            link.l1 = "��������������� �� ������� ����� ��...";
            link.l1.go = "BStep_5";
		break;
		
		case "BStep_5":
        	dialog.text = "�������! � � ����� ����� �������� ��������, � ��� ������ ���������! �������� � ���� �����!";
            link.l1 = "�����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
            sld = characterFromID("Quest_Habitue");
            sld.Dialog.CurrentNode = "QHStep_0";
            AddQuestRecord("DiekeQuest", "2");
            
		break;
		
		case "Bishop_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Plantation_Sp1", "goto", "goto1", "BishopOnHouse", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit()
		break;
		
		// -->����� �����

		case "EBStep_0":

            dialog.text = " � ������� ���, ��� �� �������. ����� ���, ���������, ������ ������ ����!";
        	link.l1 = "� ������ ���, ��� � ���� �����.";
            link.l1.go = "Exit_RunAway";
            DeleteAttribute(npchar, "talker");
            Pchar.questTemp.CapBloodLine.sLocator = "Reload5";
            Pchar.questTemp.CapBloodLine.iTime = -1;
            
		break;
		
		case "EBStep_1":

            dialog.text = "������, � ���������� ���, ��� �� �������.";
        	link.l1 = "�������, ��������� ���.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_2";
            AddDialogExitQuestFunction("CureLordMovie");

		break;
		
		case "EBStep_2":

            dialog.text = "��� � ������ �������? �� �������?";
        	link.l1 = "������ ��� ������. � ��������� ����, ��� ���������, ������ �� ����������, �� ��� ����� ������ �����...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";
            AddDialogExitQuestFunction("DragunInvansion");

		break;
		
		case "EBStep_3":

            dialog.text = "��� �������, ��� ������� ��������������� ������� ������� ����� � ��������� ���� ������.";
        	link.l1 = "������, � ��� � ��������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";

		break;
		
		//--> ������� ������

		case "CGStep_1":
        	dialog.text = "��� ���� ��� ����! ��� ����� ����������, ��� ����� ���� ��������� ��������... ����� ���, ������!";
    		link.l1 = "�� ��� ������������, ���! ��  ����� � ������, � �� � �������. ���� ������� ������ �����, ��� ������ ������� ��� ��������� ��� �����.";
    		link.l1.go = "CGStep_2";

		break;
		
		case "CGStep_2":
        	dialog.text = "��, ��� � ��� ������ ���������� � �������� ����������! ���� ������! �� �������, ��� �� ����� ��� ������? ����� ���� ������ �� ������� �� ����������� ����������� ��������, � �� �������� ��� ����� �� ���. ��������� ���� ������ ���� �������-������������ ���-���� ������, � ��� ����� ������� �� ����, ����� � ��������!";
    		link.l1 = "���������, �� ���� �� ��� ��������, �����, ��� ������ ����� �������� ���. �� �� ����������� � ��������� �����, ������� �� ������ ���������, �� ������� ��������. �� ����� ����� ��������� ����, ���� �����.";
    		link.l1.go = "CGStep_3";

		break;
		
		case "CGStep_3":
        	dialog.text = "���� �����?";
    		link.l1 = "����������. ����� �������, ���� �� �� ����� ��� �� ������, ������ ��� �������� �������� �� ��������, ������� �� ��� �������. ���� ������� - ���� ������.";
    		link.l1.go = "CGStep_4";

		break;
		
		case "CGStep_4":
        	dialog.text = "���� ������� - ��������, � ��� �������� � ����������, � ������.";
    		link.l1 = "�� �� ��������� ����� ����. ��� ������ ������ �������.";
    		link.l1.go = "CGStep_5";

		break;
		
		case "CGStep_5":
        	dialog.text = "��� ���� ��� ����. ��� ���� - ������������ ����������!\n� ��� ��� �� ���, ������� �������� � ������? ��� ���� ��������? ���-�� � �� ����� ������ ������������ ������.";
    		link.l1 = "�� �������, �������. ��� ������ ����, ���������� ���� ���� ������ �������, �������� �� �������� ����� ���� - ������ ������ ����������.";
    		link.l1.go = "CGStep_6";

		break;

		case "CGStep_6":
        	dialog.text = "�� �����, �� ������ ��? ������� �����, �� ���������� ���� ����!";
    		link.l1 = "���� �� � ����  �������, �� �������� ��� � �������, ��� � ���� �������.";
    		link.l1.go = "CGStep_7";
		break;

		case "CGStep_7":
        	dialog.text = "������. �� ��� �� �����, ���� �� ���� ������? � ��� �� ����� ��������?";
    		link.l1 = "��� ��� ����� ����, � ����, � ���� �������� ���� ��� �������� ������ ��������.";
    		link.l1.go = "CGStep_8";
		break;
		
		case "CGStep_8":
        	dialog.text = "�� � ��� �� ���� ���������? ���������?\n����� ���! ������� � ���� ����. �� ������� ���, ��� �������� ����������!";
    		link.l1 = "��, �� ���. ����� � ��������� �� ����!";
    		link.l1.go = "GFight";
    		NextDiag.TempNode = "CGStep_9";
			EndQuestMovie(); 
		break;
		
        case "CGStep_9":
			dialog.text = LinkRandPhrase("��� �� - ����� ���!", "������ ��� ������!", "� �� ����!");
			link.l1 = LinkRandPhrase("������!!", "��� �� �� ���!", "�-���, ����!");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapGobartAttack");
            NextDiag.TempNode = "CGStep_9";
		break;
		
		
		// -->�������� �� �����
		
		case "First Guard":
        	dialog.text = "�� ���� ��������?";
    		link.l1 = "��� ��� ����� ����, � ����� �� ������������ ���������� ������ - ��� ��������� ������� ��� ������� � ������� ������� �����������.";
    		link.l1.go = "GStep_0";

		break;
		
		case "GStep_0":

            dialog.text = "��, ���������� ����. �� ����� ����� ����� � ������ � ''����� �� �����'', � ����� ��� ��� ��������� �����, ��� ����� �������.\n������� ��� ����... � �� ��� ���������, ����� ��� � ������, ������� ��� � �����. ����� ������� ����� ����� - ��������, � ����� ��� �� �����.";
        	link.l1 = "����� ��������, �� � ������ ������ ������������ ������� �����������, � ���������� ����, �� �������� ��������� � ����� ������ � ''��������� ������''.";
            link.l1.go = "Exit";
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//�������� ����������
            //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            //������� �� �����
            LAi_SetLoginTime(npchar, 6.0, 23.0);
            npchar.protector = false;
            npchar.protector.CheckAlways = 0;
            npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

		break;
		
		case "GStep_1":

            dialog.text = "�, ������ ����! �� ���� ��� � ���-�� �� � �����, ����� ���������� ���� ������� �� ����. ��� ��� �����?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
       	        link.l1 = "� ���� �� ����� ��������� ��� ������������ �������. ��� ������ ������� � ���, ����� ��������� ��� ������ ���� � ��������� ��. �� ��������, ����������� ���� � ����� ������ - ������� �����?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//�������� ����������
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //������� �� �����
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

            }
            else
            {
           	    link.l1 = "��� �� � �����, ������� ���������, ��� ��� ����� ������� � �����������.";
                link.l1.go = "GStep_2";
            }

		break;
		
 		case "GStep_2":

            dialog.text = "��� ��� ���. �� ��� �� � ��� ���������, ������� ����� ���������, ��� � ��� ����� ��� ����� �� �������, ���� � �� ����� � ��������������� ������������, �������� ������������ ������.";
        	link.l1 = "� ����� ������, �� ���� ����� ��� ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "GStep_3";
            AddQuestRecord("WeaponsForEscape", "12");
		break;
		
		case "GStep_3":

            dialog.text = "�� ��� ���?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
       	        link.l1 = "� ���� �� ����� ��������� ��� ������������ �������. ��� ������ ������� � ���, ����� ��������� ��� ������ ���� � ��������� ��. �� ��������, ����������� ���� � ����� ������ - ������� �����?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//�������� ����������
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //������� �� �����
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                NextDiag.TempNode = "First time";

            }
            else
            {
            	link.l1 = "�������� - ��� �� ��� ���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GStep_3";
            }

		break;

        // --> ����


 		case "SStep_0":

            ChangeCharacterReputation(PChar, 5);
            dialog.text = "��� �� ��� �� ����, ������ ������� - ��� ����. � ��� ����� ������� �������, ��� �������������� � ��������� ��� ������� ������� �� � �������!";
        	link.l1 = "���� � ������� ��?";
            link.l1.go = "SStep_2";
		break;
		
 		case "SStep_1":

            dialog.text = "��� �� ��� �� ����, ������ ������� - ��� ����. � ��� ����� ������� �������, ��� �������������� � ��������� ��� ������� ������� �� � �������!";
        	link.l1 = "���� � ������� ��?";
            link.l1.go = "SStep_2";
		break;

 		case "SStep_2":

            dialog.text = "��-��, ������� - ��� � ������� �� ������ �����. ��� ��� - ����� ������ �� ��� � ����� �� ��������. ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_3";

			sld = GetCharacter(NPC_GenerateCharacter("MisStid", "AnnaDeLeiva", "woman", "towngirl2", 10, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = "������";
			sld.lastname = "����";
			sld.greeting = "Gr_Dama";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto","goto5");
			AddQuestRecord("CapBloodLine_q1", "2");
		break;
		
		
		case "SStep_3":

            sld = &characters[GetCharacterIndex("MisStid")];
            if (sld.quest.meeting != "1")
            {
                dialog.text = "������ ����, ��������� ��� ���� ��������.";
                link.l1 = "��� ���.";
                link.l1.go = "Exit";
            }
            else
            {
                dialog.text = "��� ���, ������? ��...";
                link.l1 = "��� ����� � �������, ���������� ����, �� ��� ���������� ���������� ����������� �� ������� ����������� ����� � ��������. ������ ����� ��������� ��� � �����������.";
                link.l1.go = "SStep_4";
                
                link.l2 = "��� ����� � �������, ���������� ����, ���� ��� ������� ������� ���� ������� ���� � ��������� ���. ������ ����� ���������, � � ����� ��� ������ ��� �������� ��� �� �������.";
                link.l2.go = "SStep_5";
            }
		break;
		
		case "SStep_4":

            dialog.text = "����� ���, ������������!";
            link.l1 = "��� ���.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";

		break;
		
		case "SStep_5":

            dialog.text = "�, �������, ����������... ������� ��� �����?";
            link.l1 = "500 ��������.";
            link.l1.go = "SStep_6";
            link.l2 = "1000 ��������.";
            link.l2.go = "SStep_7";
            link.l3 = "2500 ��������, ���. ��� ����� ������� ����������� ��������.";
            link.l3.go = "SStep_8";

		break;
		
		case "SStep_6":

            AddMoneyToCharacter(pchar, 500);
            dialog.text = "��� �������� 500 ��������.";
            link.l1 = "� ������ ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 500);

		break;
		
		case "SStep_7":

            AddMoneyToCharacter(pchar, 1000);
            dialog.text = "���, �������� 1000 ��������, � �������, ��� ��� ��� ������� ����.";
            link.l1 = "� ������ ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 1000);

		break;
		
		case "SStep_8":

            AddMoneyToCharacter(pchar, 2500);
            dialog.text = "��� ������� �����, ������. � ����� ��, �� ����� ���������� �� ����������� - � ��� �������.";
            link.l1 = "� ������ ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "5");


		break;
		
		case "SStep_9":

            dialog.text = "����� �����, �������, � ��� ��� ����� �����������. �� ��������, ������� ��������� ������ ��������?";
            link.l1 = "� ������ ����, ����� ������������� ���, ���. � ������ ����������...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3_1";

		break;

        //--> ������ ����

        case "MSStep_0":

            dialog.text = "�� ������ ���-�� �������, ������?";
        	link.l1 = "������, ����� �� �������� ��� ��������, �� ������ ����� �������. ��� �������� ����� � ������� ���� �����, ����� �������� ��� �����������. ������� ������ ���� � ����� ����, � ������� ��� �����, ��� ������ �����!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_1";
            
            sld = GetCharacter(NPC_GenerateCharacter("Waker", "usurer_5", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "������";
            sld.lastname = "�����";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto","goto6");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);
            
            pchar.quest.CureMisStid.win_condition.l1 = "item";
			pchar.quest.CureMisStid.win_condition.l1.item= "migraine_potion";
			pchar.quest.CureMisStid.function = "CapBloodLine_q1_End";
			
			sld = ItemsFromID("migraine_potion");
			sld.shown = true;
			sld.startLocation = "CommonPirateHouse";
			sld.startLocator = "item1";
			
			AddQuestRecord("CapBloodLine_q1", "3");


		break;
		
        case "MSStep_1":

            dialog.text = "�� �������� ���������, ������?";
            if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid_Complite")
            {
                link.l1 = "��, ��� ������ �������� ��� �� ����.";
                link.l1.go = "MSStep_2";
                TakeItemFromCharacter(Pchar, "migraine_potion");

            }
            else
            {
                link.l1 = "��� ���, � ��� ��� ��� �� ����.";
                link.l1.go = "Exit";
            }

		break;
		
        case "MSStep_2":
        
        NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		//������� ����� � �������, ��������� ����� questFadeOut, ������� �� �������, ��������� ����� questFadeIn
        //LAi_Fade("", "CapBloodLine_q1_Complited");
        CapBloodLine_q1_Complited("");

		break;
		
        case "MSStep_3":

            dialog.text = "������������, ������ ����. ��� ����������� ����� �, ������, � ������������� ����� �� �������� - ��� ��������� ���.";
        	link.l1 = "���������, ������ ����. � �����, �����...";
            link.l1.go = "MSStep_4";
            DeleteAttribute(npchar, "talker");

		break;
		
        case "MSStep_4":

            dialog.text = "� ����, �� �� ������� ���� � ����� �������... ���� �����, ��� ����?";
        	link.l1 = "��... ���?";
            link.l1.go = "MSStep_5";
           	link.l1 = "���, ���, ��� ����������� �� ���.";
            link.l1.go = "MSStep_5";

		break;
		
        case "MSStep_5":

            dialog.text = "���� � ���, ��� ��� � �� ���. ��������� ����� ��������� ������ � ���� �� ����, �� ������� ����� � ���������� ��� ���, ��� ��� ��������� ������. ��, ���� �� ��� ��� �� ��� ������ � ���, ��� �� ����� ��������� ������ �� ��� �� ����, � ����� ��������� ����� ������ �� ���, �� ��...";
        	link.l1 = "����� ���������.";
            link.l1.go = "MSStep_6";

		break;
		
        case "MSStep_6":

            dialog.text = "������� �����������, ��� �������. �� ��� �����, �� � ��������� ���, ������ ����. ��� �� ��� �� ����, ��� ��� �� � ����.";
        	link.l1 = "��� ��, ������ ����! � �� ���� ������� ���... �������, � ���� ����������� �������� ��� ���, ��� ��� � ��� ���� ������.";
            link.l1.go = "MSStep_7";

		break;
		
        case "MSStep_7":

            dialog.text = "����� ����� ���. � ������ � ��������� ������� ��� �������� ����.";
        	link.l1 = "���, � ������ ��� ��� ������� ���������������� ���������, ��� � ���� ����������� ����� ����� ������. ����� ����������.";
            TakeItemFromCharacter(Pchar, "migraine_potion");
            AddQuestRecord("WeaponsForEscape", "15");
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";


		break;
		
        case "MSStep_8":

            dialog.text = "�� ��������, ������ ����.";
        	link.l1 = "����� �������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";
		break;
		

		

        //--> �������

        case "NStep_0":

            dialog.text = "�-�... ���� �������... ���� ������ �������, ��... ���� �� ����� - � ������. ���... ������.";
        	link.l1 = "�����������-�� �����, ������ ������� ����. ���� ���� �������.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_1";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;
		
        case "NStep_1":

            dialog.text = "���� ��������, ������! ��-�-�!";
            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
            {
                link.l1 = "� ���� � ���� ���� ��������.";
                link.l1.go = "NStep_2";
            }
            else
            {
                link.l1 = "��� ���� ����� - ����� ����� � ��������.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_1";
            }
		break;
		
        case "NStep_2":

            dialog.text = "� � �����, ������� ���� ��� ���������...";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "��� ���� �������� ���� �����. ������� �������� � ����� �������������� ������ ����������, ����. �� �������.";
                link.l1.go = "NStep_3";
            }
            else
            {
                link.l1 = "���� �����, ��� ������ � ������ ����������� ����� �����, �� ��������� �������� �����.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;
		
        case "NStep_3":

            AddMoneyToCharacter(pchar, -25000);
            dialog.text = "��, ����� � ���� �������... ������.";
        	link.l1 = "����������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
            NPChar.lifeDay = 0;
       		CloseQuestHeader("CapBloodLine_q2");
            CapBloodLine_q3_Complited();
            
		break;
		
        case "NStep_4":

            dialog.text = "��� ������ ����� ���� ��� � ����� �� �����.";
        	link.l1 = "����������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
		break;
		
        case "NStep_5":

            dialog.text = "�� ������ ������?";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "��� ���� �������� ���� �����. ������� �������� � ����� �������������� ������ ����������, ����. �� �������.";
                link.l1.go = "NStep_3";
            }
            else
            {
               	link.l1 = "���� ���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;
		
		case "Nettl_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NettlOnTavern", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
		
        case "NStep_6":

            dialog.text = "��... ���� ��������! � ��� ��� ����� �������?";
        	link.l1 = "��, � �����, � ��� ������ �� ����. ���� ����� �����-������� ����� �� ����� � ������ ����, ������ � ���� �������. ����������� � �������, � �� ����� �� ����� ��������� � �����.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_5";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;
		
        //--> �����

        case "WStep_0":
        
            AddCharacterExpToSkill(pchar, "Sneak", 50);
            dialog.text = "� �� � ��� ��� ������, ��� ��. ��� ��� ����� ��� ����� ���, � ��� ��� ��� � ���. �� �� ������ �� ������� � �������?\n� ��� ���, � ���� � ��� ��������...";
        	link.l1 = "� ����� ���������, ������ �����, ��� ���������� ����� ������� ���� ��� ����� ������. �������� ������� ��������.";
            link.l1.go = "WStep_2";

		break;
		
        case "WStep_1":

            dialog.text = "� �� � ��� ��� ������, ��� ��. ��� ��� ����� ��� ����� ���, � ��� ��� ��� � ���. �� �� ������ �� ������� � �������?\n� ��� ���, � ���� � ��� ��������...";
        	link.l1 = "� ����� ���������, ������ �����, ��� ���������� ����� ������� ���� ��� ����� ������. �������� �������� ��������.";
            link.l1.go = "WStep_2";

		break;
		
        case "WStep_2":

            dialog.text = "��� �, � � ��� �� � ���������� ��������� ��� ��, ��� �������� ����������, ������ ����� � ������. �, �������, �����, � ��, ���� ������, ��������� ����. ��������� ������. ��� ������ ������� ��������� ������, ��������� � �������. ����� �� ��� �������.";
        	link.l1 = "�� ��������.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = 5;

            sld = GetCharacter(NPC_GenerateCharacter("Den", "usurer_1", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "������";
            sld.lastname = "���";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "BridgeTown_town", "goto","goto3");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);
            AddQuestRecord("CapBloodLine_q2", "1");

		break;
		//����������� ������ - ������ �������
        case "WStep_3":

            dialog.text = "�� ������ ��� ����������, ��� ����. �� ����������� ������, � ���� ����� �� ���� ����� ������. � ���� ������ ���!\n���� ������� ������ ���� ����� ��������� ��� ������ ������������ ��������, ��� ��.";
        	link.l1 = "����� ����������������!";
            link.l1.go = "WStep_4";

		break;
		
        case "WStep_4":

            dialog.text = "� �� �����, ������� �������. � ���� �������� �������� � ���� ���� �������, ��� �� ������.";
        	link.l1 = "�� ������� ���� � ����, ���� �������, � ��� ����� �.";
            link.l1.go = "WStep_5";

		break;
		
        case "WStep_5":

            dialog.text = "�� ��� �������� � �� ����, ����� �� �������� ������������� � ������� ����. � �� ���������, ��� � �� ���� ����� ������?\n���� �� ��� ������� �������� �� ����� ���, �� ����� ��, ��� ��������� �������, � ������������� � ������� ��� ���� ������� �������� ����� ���������, ���������� ������� �� ���������.\n��� �����, �, ����� ������, ���� ��� ����� �����, ��� ������ ��������, ��� ��, ������ ����� ��������. ������ ���������� �������, ���� � ������.\n������ ������ �������� �� ����������� ������� �������. � ��� ����� ���� ���� ������ ����� ��������� ���� �� ��������� �����. ������� ����� ����� �������� � �������� ���. �� ��������� ����� ����, ��� ������ �� ������������ �� �����.\n��� �� �� ��� �������?";
        	link.l1 = "� ���� ��� �����, � ���� ��� ������ ����������� �� ����������� ������.";
            link.l1.go = "WStep_6";

		break;
		
        case "WStep_6":

            dialog.text = "����� � �� ������, ��� ���� ���� ����� ������?";
        	link.l1 = "������?";
            link.l1.go = "WStep_7";
           	link.l2 = "��� ����� ���������� � ����� �������, �������. ������ ��� �������� �� � �, ���� �� ��� ������������ �������� ������.";
            link.l2.go = "WStep_8";
            
		break;
		
        case "WStep_7":

            dialog.text = "�� ���� �� �������������, ��� ���������� ������ ��� ������ ��� ���� �������, ����������� � ������� � ��������� ����������� ��������� �� ���� ���� �������� �����������! � ���� ��� �������� � ������, ���� � ��������� �����, ����� �� ������ ����������� � ���������, ������� ���� ��� ���� �������� �����...\n�� � ��� �������� ���� ������ � ����������... �-��?..";
        	link.l1 = "��� ������, ������ ��������, ����� � ������. ���� ��������, ��������, ����� � ��������.";
            link.l1.go = "WStep_9";

		break;
		
        case "WStep_8":

            dialog.text = "������, �� ��������?";
        	link.l1 = "��� ������, ������ ��������, ����� � ������. ���� ��������, ��������, ����� � ��������.";
            link.l1.go = "WStep_9";

		break;
		
        case "WStep_9":

            dialog.text = "������ �� ��������! ��� ����� ����, ������� �� ��� ������... ������� ���, ����� �������.";
        	link.l1 = "��� ���������� �������������, ��� �������� � ����������� � ������� ������. ������ �� ��������� ���� ������. �� ���������� ��� ����� �������, �������!";
            link.l1.go = "Exit";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "WakerOfferComplited";
            AddQuestRecord("CapBloodLine_q2", "4");
            NextDiag.TempNode = "WStep_10";

		break;
		
        case "WStep_10":

            dialog.text = "�� ������, �������.";
        	link.l1 = "�� ��������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_10";

		break;
		
		//����������� ������ - ����������
		
        case "WStep_11":

            dialog.text = "������ ����, ������ ����. � ���� ���.";
        	link.l1 = "������, ������ �����. ��� �, � ������ ����� � ��� �����������. ��� ������ ��������� �����.";
			npchar.LifeDay = 0;
            link.l1.go = "WStep_12";

		break;
		
        case "WStep_12":

            dialog.text = "��� ���� � ���, ��� � ���� �� ����� ������ 18 000 ��������, � ��� ����������� �������� 25 000. ��� �� �����, � ������, �� ������� ��������� ���������� �����.";
        	link.l1 = "��� ����� ��������������, �� ������ � ���� ���. ��� ������ �����? ����� �� ����� �� ������ ������ ������ �� ����� � ��������� ���� ����, ��� �� � ��� �� ������.";
            link.l1.go = "WStep_13";
            AddMoneyToCharacter(pchar, 18000);

		break;
		
        case "WStep_13":

            dialog.text = "��, ��, ��� ������, �����, ������. �� ���� � �� �������...";
            if(Pchar.questTemp.CapBloodLine.TalkWithNettl == false)
            {
            	link.l1 = "�� ������ ����-��, ��� ����� ������?";
                link.l1.go = "WStep_14";
            }
            else
            {
            	link.l1 = "���� �������, �������. � ����� ��� ���-�� � ������.";
                link.l1.go = "WStep_15";
            }

		break;
		
        case "WStep_14":

            dialog.text = "�� ������� ���� �� ������ ����������, �� � ��������, ����, ���������� ������ �� �����. ��� ����� ��������� ���������� ���� ������. � �����, ����� �� ��� � �������� ������������� ������������ ������.";
        	link.l1 = "���������, �������!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;
		
        case "WStep_15":

            dialog.text = "�������... ��, ����������� ������� ����� ������� ����������. ���� �� � ���� �������� ������� ��� ��������. ��� �, ��������, ������ ����. � ����� ���!";
        	link.l1 = "���������, �������!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;
		
        case "WStep_16":

            dialog.text = "����� ���!";
        	link.l1 = "���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";

		break;
		
        //--> ������ ���

        case "DStep_0":

            dialog.text = "����� ������! ���, � ���� ���� � ����� ������� - ��������. ��� ������� �� ������ ����, � ������ ������ ����� ��� ����. �� ������, � ���� �������� ��� �������. ������ �����, ������ - ��� �� ��� ����������� ����!";
        	link.l1 = "����� �������.";
            link.l1.go = "Exit_Away";
            GiveItem2Character(Pchar, "migraine_potion");
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_1":

            dialog.text = "��� ��! �� ���� �������� ������ ���� - �� ��������� ���������! ������������ ��!";
        	link.l1 = "����� �������.";
            link.l1.go = "Exit_Away";
            ChangeCharacterReputation(PChar, 5);
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;
		
        case "DStep_2":

            dialog.text = "��... ����.";
        	link.l1 = "����� �������.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;
		
        case "DStep_3":

            dialog.text = "������������, ������ ����. ��� ���� ��� ������?";
        	link.l1 = "������ ����, ������ ���. � ����� �� ������������ ��� ������������������ ����������� �����. ��� ������ ��������� ��� ������ �������� ��� ������������ �������.";
            link.l1.go = "DStep_4";

		break;
		
        case "DStep_4":

            dialog.text = "�, �������, ��� �������� - � ���� ������� ��������. ��������� ������ �� ���� �����������.";
        	link.l1 = "��������� ���. ��������� �����������.";
            link.l1.go = "Exit";
            GiveItem2Character(Pchar, "migraine_potion");
            NextDiag.TempNode = "DStep_5";
            AddQuestRecord("WeaponsForEscape", "13");

		break;
		
        case "DStep_5":

            dialog.text = "��� ���-�� ����������?";
        	link.l1 = "���, �������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "DStep_5";

		break;
		
		//--> ������� ����

		 case "PStep_0":

            dialog.text = "���? � ��� �� ��������?";
        	link.l1 = "� ������ � ����������� ���������� ����� ��������� ���� �� �����, ������� ����� � ��������� � �� ������ - ����������, ������������� ���, ���� ����� �������� - � ����������� � ��������� �� ���-�����, � ����������� ������� �������.";
            link.l1.go = "PStep_1";

		break;

        case "PStep_1":

            dialog.text = "�� � ����� �� ��, ������? �� �����, �� ������� ����� �����, �� �������� � ������ - ������ ����� � ��� ��� � ���� �� �����.";
        	link.l1 = "�������� ����, ������� ����. �� - ������������ ������� ����� ���. ��� ���� ��� �� ��������� �� ������� �����, ���� ���� � ������ ����� � ������������ ������� �� ����� ������� �� ������� ����������� ���. �� ����� ��� ������ ��� ��, ��� � �����-�� ��� ����� ���� � ������� ��������...";
        	link.l1.go = "PStep_2";  //(+ ��������� ������� ����������)
        	link.l2 = "������ �� �������� ������ ��� ���?";
        	link.l2.go = "PStep_3";

		break;

        case "PStep_2":

            dialog.text = "������, � �����, � ��� �����. ������ ���, ��� � ���� �����, ����� ������...";
        	link.l1 = "�����, ���, ����� ����, �� �������� ���: ���� �� - ������������ ������� ����� ���, � ��� ���� ������� ����������.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            Pchar.questTemp.CapBloodLine.Officer = 0;
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");

		break;
		
        case "PStep_3":

            dialog.text = "������, � �����, � ��� �����. ������ ���, ��� � ���� �����, ����� ������...";
        	link.l1 = "�����, ���, ����� ����, �� �������� ���: ���� �� - ������������ ������� ����� ���, � ��� ���� ������� ����������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");
		break;
		
        case "PStep_4":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
            {
                dialog.text = "����� ������, �����?";
                link.l1 = "� �������� ������ � ����������� � �������. �������� ������ ������ ����. ������ � ������ �� ����� ������ ������!";
                link.l1.go = "PStep_9";
                while (GetCharacterItem(pchar,"Weapon_for_escape") > 0)//homo fix 06/02/08 �������� ��� ��������� ������
                {
                    TakeItemFromCharacter(Pchar, "Weapon_for_escape");
                }
                //link.l10 = "���������� ����.";
                //link.l10.go = "finish";
                NextDiag.TempNode = "PStep_10";
                break;

            }
            dialog.text = "������ ����� � ��������� ��� �����������. � ���� ����� ���� �����.";
        	link.l1 = "�� �������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
		break;
		
        case "PStep_5":

            dialog.text = "�����, ���� ������ ������� ����������� �����, ��� ���� ���������� ���������...";
        	link.l1 = "�����, ��� ������ �������, ���� �� ����� � ������������ ������, � ��������� �� ����� � �������� � � ����, ��� �� �������. � ��� ����� ����� ����-������ ���������.";
            link.l1.go = "PStep_6";
            //NextDiag.TempNode = "SStep_4";
            
		break;
		
        case "PStep_6":

            dialog.text = "������, � �������� � �������� �����, �� �� ����� ������ ���������� �����, �� ����� ������. � � ���� ��� ���� �����, ����� �������� �� ����.\n������ ���, � ������� �� �� ������� � �������. � �������, ������� ���-��� �������� � �������.";
        	link.l1 = "�������, � ����� �� ���, ��, �������, ��� ��� �� �����������.";
            link.l1.go = "Exit_RunAway";
			//������ ���� �� ����
			sld = ItemsFromID("key3");
			sld.shown = true;
			sld.startLocation = "Estate";
			sld.startLocator = "item1";

            Pchar.questTemp.CapBloodLine.sLocator = "reload2";
            Pchar.questTemp.CapBloodLine.iTime = 5;
            AddDialogExitQuestFunction("DragunInvansion2");
            
		break;
		
        case "PStep_7":

            dialog.text = "����������, �����. ������� ����������� ����� �����, ��� �� �������� �� �������� ���������� ���������� ������. ����� ��� �������, ��� �� ����� �� ��� ������� - ��� ������ ��� ����������. ��� ��������� ��������, ��� ������ ������� � ���\n������ ����� ������ ������ �� ����������� � ��������� ��������� ��� �������� ������� �������, � �� ����� ���� ���������� ���������� ������������ �����. ����� ���-�� ������ �����, ����� �� �� ������� � �� ����.";
        	link.l1 = "� ���������  ����� �� ����, �� ������ ������ ������, ��� �����-���� ��������� ����� ������� ����������, ����� ���� �� ���� �������, ������� ���������  ������ ��� ������ ����� � ��� ������.  ��� ��������, � ����� ������ ��  ��� ����� ''�.�.'', ����� �� ����� ����� ��� �����, ��� ��� ������ ���������.";
            link.l1.go = "PStep_8";
        break;
        
        case "PStep_8":
            dialog.text = "� ������� ��� ����������, �� ���� �� ������\n�� � ������ � ���� �� ���������� �� ������, � ����� ��������, ��� ���� �����-�� ����������� �����. ���������� �� ����� ���, � �� �� ������� �������� ��� ����� ��������� ������.";
        	link.l1 = "�������, ����, ����� � ����� � ����, � ������, ��� ���� ������, ��� ������.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = -1;
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "";
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("ChangePIRATES");
		break;
		
        case "PStep_9":

            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            CapBloodLine_q2_Complited();

		break;
		
        case "PStep_10":
        
            dialog.text = "�����, ���� ������� ������ ����?";
        	link.l1 = "��� ���.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_10";
            
		break;
		
        case "PStep_11":

            dialog.text = "������, �����, ���... ��� ��������� ����...";
        	link.l1 = "���������, ����, ������� ��� ��� ���������. ��, ��������, �������, ����� �� ��������� ��� ��������, ���� ��� ����  ������� ������ ����� ���� �� ����� ����?";
            link.l1.go = "PStep_12";

		break;
		
        case "PStep_12":

            dialog.text = "�� �����, �����, ��� ������� ������ �����������.";
        	link.l1 = "���, ��� �����?";
            link.l1.go = "PStep_13";

		break;
		
        case "PStep_13":

            dialog.text = "������� ������.";
        	link.l1 = "� ����� ��������! �� ���-������ ���������. �������� ����, � ����� ������! ������� � ��������� ��� ���� ��� � ������, ����� ������������ ��, ���� �� �� ��������!";
            link.l1.go = "PStep_14";

		break;
		
        case "PStep_14":

            dialog.text = "����� ���� � ����� � ���������� ���������, �� ���� �� ������ ��������� �����.";
        	link.l1 = "��� ��� ���, ����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";
            chrDisableReloadToLocation = false;
           	LAi_group_SetHearRadius("TmpEnemy", LAI_GROUP_GRD_HEAR - 3);
   	        LAi_group_SetSayRadius("TmpEnemy", LAI_GROUP_GRD_SAY - 1);
   	        LAi_group_SetLookRadius("TmpEnemy", LAI_GROUP_GRD_LOOK - 1);
            AddQuestRecord("EscapeFormBarbados", "2");

		break;
		
        case "PStep_15":

            dialog.text = "���� � �����!";
        	link.l1 = "�� ������� ����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";

		break;
		
        case "PStep_16":

            dialog.text = "����������, �����, ������ ���������� ��� ��� ��� � ���������. ����, ��� ���� � ���� �� ����! �� ������� ��� �� ��������� � ����� ���������� �������!";
        	link.l1 = "��� ������ ���� �� ����� �������. � ���������, ��� �� ���������. ��� ��� ����� ����� � �������� ���� � ������, ���� �� ����������.";
            link.l1.go = "PStep_17";

		break;
		
        case "PStep_17":

            dialog.text = "��, � ������ ��� ��� �������� - ��� ��� ����� �� �������. � ������� ��� ��������� �� ����� �� � ������� ������������. �� �� �������� � ���� �������. �������� ������ ����������� �������, ��� � �������.";
        	link.l1 = "�����, � ��� ��� ����� ����� ������������ ��� ����. � ������ ������ ������ �������, ��, ��� ������� �� ������ - �� ������ � �� ������ � ����� ������, ��� �  �������� ���-�� �������. ����� ������� �������� � ������������� � �������.";
            link.l1.go = "PStep_18";

		break;
		
        case "PStep_18":

            dialog.text = "�� ��� ��� ��������! ��� �����, ���� �� ��� ����� ���������, �����.";
			DeleteAttribute(pchar, "LockBloodWeaponsOptions");
        	link.l1 = "��, ���� ���������� ���, ����� ������� ������� � ���. �� ������ ���������, �������, ��� ��� �� ������������ �� ��� ������ ��������� ��������.";
            link.l1.go = "PStep_19";

		break;
		
        case "PStep_19":

            dialog.text = "����, �������.";
        	link.l1 = "";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;
            
        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;
       		
            AddPassenger(pchar, NPChar, false);
       		
            Pchar.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, Pchar);
            Pchar.Ship.name="����� ������";
            SetBaseShipData(Pchar);
            Pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantity(Pchar, GetMinCrewQuantity(Pchar));

            SetCharacterGoods(Pchar,GOOD_FOOD,70);
        	SetCharacterGoods(Pchar,GOOD_BALLS,300);//2000);
            SetCharacterGoods(Pchar,GOOD_GRAPES,100);//700);
            SetCharacterGoods(Pchar,GOOD_KNIPPELS,100);//700);
            SetCharacterGoods(Pchar,GOOD_BOMBS,200);//1500);
            SetCharacterGoods(Pchar,GOOD_POWDER,500);
//            SetCharacterGoods(Pchar,GOOD_PLANKS,10);
//            SetCharacterGoods(Pchar,GOOD_RUM,40);//600);
            SetCharacterGoods(Pchar,GOOD_WEAPON,50);//2000);
            
            n = FindLocation("Bridgetown_town");
            
            locations[n].reload.ship1.name = "reloadShip";
            locations[n].reload.ship1.go = "Barbados";
            locations[n].reload.ship1.emerge = "reload_1";
            locations[n].reload.ship1.autoreload = "1";
            locations[n].reload.ship1.label = "Sea";
            
            Pchar.location.from_sea = "Bridgetown_town";
            setWDMPointXZ("Bridgetown_town");
            
            string sQuest = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";
            pchar.quest.(sQuest).win_condition = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).function = "CapBloodLaspEpisode";
            
            AddDialogExitQuestFunction("SpaCrewAtack");


		break;
		
		//-->��������� �������

        case "GRStep_0":

            dialog.text = "��� ���� ��������, ������, ����� ��, ���������, ������������... ��������� � �������� ����� ���� ���������� ����!";
        	link.l1 = "�������, ��� ������ ��� �� � ������ ������������ ����. ���� �����, � ���� ��� ���-�� ������, ����� ���� �� ���� ����������?";
            link.l1.go = "GRStep_1";

		break;
		
        case "GRStep_1":

            dialog.text = "������ ���? ��?! ��� ����� ����������� ��� ������...";
        	link.l1 = "������, �� �������������� ����, ������ �������. ��� �, ��� � ������ ������ ��� ��������� �� ���� ��������!";
            link.l1.go = "GRStep_2";
        	link.l2 = "������ ���? � �������� � ����� ������ �, ������, ���������� ���� � ������ �������� ����� ��� ������ ��������.";
            link.l2.go = "GRStep_3";
		break;
		
        case "GRStep_2":

            AddQuestRecord("WeaponsForEscape", "4");
            dialog.text = "�������� �����, ������!";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";

		break;
        case "GRStep_3":

            dialog.text = "��� �, ���������. ���� � ���, ��� ������� �� ��� ����� �������. �� �� ������ ������ �����, �� � �� ������ �����, ��� ������� ���� ����� �� ���. �� ����, ������ �� ������ � ��� ����� � �����, �� ��� ����� ���� ������. ��, ������, � ���������... � ������ �� ���� ���������� � ������� ������, ������ ��� ������ ��� ������� ��� ������. ������� ��������� �����, ���� � ��������� �����, � ���� ��� ��������� �� ����� - ��������� ���������� ������, ��������������� ������ � ���� ����������. ��������� ��������� �����!";
        	link.l1 = "...����, ���� - ''� �������� �������''.";
            link.l1.go = "GRStep_2";
            NextDiag.TempNode = "GRStep_2";
           	link.l2 = "�� �� ������� ������?";
            link.l2.go = "GRStep_4";

		break;
        case "GRStep_4":

            dialog.text = "� ������� ������! �� ���������� ������������� ��� ���! ���� �� ������� � ��� � ���� ������� � �����, ���-�� ����������� ��� ������� �� � ��� ��� ��� ������� ���� ��� ������! ������ ����� ��� ������� ������� ����� �� ��� ������.";
        	link.l1 = "���� �� ������� ���, ���� ���������� �������, � �������� ������ ���� ��������. ������ � ���� ����� ������ ��� ��, ��� ������ ���� �������.";
            link.l1.go = "GRStep_5";

		break;
		
        case "GRStep_5":

            dialog.text = "������ � ���� ������ �� ������ � ������� ��� ����... �� �����, � �������, �������?! �� ������ ����� ������ �� ����������� ������� ������ � ��������!";
        	link.l1 = "�������, �����, �������. ������. � ����� ��� ������, � �� ������ � ����������� ���� ����������� ��� ���� ��������� ���������� ������ � ���������� ��� ����� ��������������� ������. ����?";
            link.l1.go = "GRStep_6";

		break;
		
        case "GRStep_6":

            dialog.text = "��������� ��������� ���������� ����, ������. �� ���� ��� �� ��������. ����� ��� ���������, � � ������ ��� ���� ��, ��� �� �������. �� ������� ������ ��������. �� ���������� � ���� � ������ �������, ��� ��� ���������� �� ���� �������� ����.";
        	link.l1 = "� ����� �������, ����������� ������ �������. �������� ��� �����������.";
            link.l1.go = "GRStep_7_1";
           	link.l2 = "�� ������� �� ����� �� �������? � � ��� ���� ������ ������ ���� ����� ���������. ������, � �� ������ ������.";
            link.l2.go = "GRStep_7_2";

            sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "shipowner_13", "man", "man", 7, ENGLAND, -1, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "";
            sld.lastname = "�������";
            GiveItem2Character(sld, "Griffins_Weapon");
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto","goto2");
			
																		   
            sld = &characters[GetCharacterIndex("Hells")];
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 1.0, 0);

		break;
		
        case "GRStep_7_1":

            dialog.text = "������, ������������.";
        	link.l1 = "��� �� �������� ����� �����.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1500;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1500);

		break;
		
        case "GRStep_7_2":

            dialog.text = "������, ������������.";
        	link.l1 = "��� �� �������� ����� �����.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1000;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1000);

		break;
		
        case "GRStep_8":

            dialog.text = "�� ������ ������, ��� � ������ ��� �������. ��� ���������?";
            if (GetCharacterItem(pchar,"Griffins_Weapon") > 0)
            {
            	link.l1 = "��� ���� ���������, ������ ������� - ��� �� �������. ��������� ��������� ����� �� ������������ ���������.";
                link.l1.go = "GRStep_9";
                TakeItemFromCharacter(Pchar, "Griffins_Weapon");
            }
            else
            {
            	link.l1 = "� ������ ����� ��� ���������.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_8";
            }

		break;
		
        case "GRStep_9":

            dialog.text = "��... ��� �, ���� ���� �� ����������, ��� ��� ��� ������� � ������ �� �� ����� � ��������. ������� ����� ��� ����� ����� �� ������� ����� ����� ��� ���. � ������ ������� ���� ��������, ��������������, �������, ������� ��� ����.";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
           	    link.l1 = "��, ����������, ������� ������ �������. ��� ���� ������. � ����� � ����������� ���.";
                link.l1.go = "Exit";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
                NextDiag.TempNode = "GRStep_12";
            }
            else
            {
           	    link.l1 = "� ���� ������ ��� ��� ���� ������ �����, � ����� �������.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }
            //Pchar.questTemp.CapBloodLine.GriffinTime = GetHour();
            SaveCurrentQuestDateParam("questTemp.CapBloodLine.GriffinTime");
            AddQuestRecord("WeaponsForEscape", "6");

		break;
		
        case "GRStep_10":

            dialog.text = "��, ���-�� ����������. �� ������ ����� ���� ����� ����?";
        	link.l1 = "���... �� �������� �� ���-��� �� ������ ������������.";
            link.l1.go = "GRStep_11";

		break;
		
        case "GRStep_11":

            dialog.text = "���?! ������... ����?! �� ����� � ���, ������� ������! ��������!";
        	link.l1 = "";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";


		break;
		
        case "GRStep_12":

            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_3" && GetQuestPastTimeParam("questTemp.CapBloodLine.GriffinTime") >= 1)
            {
                dialog.text = "���, ��������, �� ������� - � ��� ��� ����� �� �����.";
                link.l1 = "�������.";
                link.l1.go = "Exit";
                GiveItem2Character(Pchar, "Weapon_for_escape");
                NextDiag.TempNode = "First time";
          		CloseQuestHeader("WeaponsForEscape");
                Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            }
            else
            {
                dialog.text = "������ ��� ��� ��� �� ������, ��������� �������.";
                link.l1 = "������.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";
            
            }

		break;
		
        case "GRStep_13":

            dialog.text = "�� �������� ������?";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
                link.l1 = "��, ��� ���� ������. � ����� � ����������� ���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
            }
            else
            {
           	    link.l1 = "� ���� ������ ��� ��� ���� ������ �����, � ����� �������.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }


		break;
		
        case "GRStep_14":

            dialog.text = "���� ������!..";
        	link.l1 = "�� ������. ��� �� �����, � ����� ������ - ���� �����, �� ����������?..";
            link.l1.go = "GRStep_15";

		break;
		
        case "GRStep_15":

            dialog.text = "�-��... ���������?";
        	link.l1 = "������, ��������� ������ �������. ��� ����� ������. ����� ���� ��������� ���������� ������ � ���� ����������, ���� ��� �� ���������.";
            link.l1.go = "GRStep_16";

		break;

        case "GRStep_16":

            dialog.text = "�... � �� ����, ���. ��� ���� �������, ���� ��... �������!";
        	link.l1 = "�����������, ��� ����� �� �����, ����� �� ���-�� ������ ����������. ������� ��������������� ���������� �� �����, ������� ����� � ������� - ��� ���� � �����. ����� � ������� �� ������ � ���, ��� ��� ���������.";
            link.l1.go = "GRStep_17";

		break;
		
        case "GRStep_17":

            dialog.text = "���... �����, ������. � ���� ���� ��� ���, ��� - ��������. �������, ����� ����������.";
        	link.l1 = "����� ���. �������� ����������.";
            link.l1.go = "Exit";
            
            GiveItem2Character(Pchar, "Weapon_for_escape");
            AddQuestRecord("WeaponsForEscape", "9");
       		CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            NextDiag.TempNode = "First time";

		break;


        //-->����� ������
		
        case "HStep_0":

            dialog.text = "����... ��� ���� ����� ����?";
        	link.l1 = "��� ����� ��� �������, ��� ����������� ���� ������ ����� � ����� ���.";
            link.l1.go = "HStep_1";

		break;
		
        case "HStep_1":

            dialog.text = "������� ��������� �� �������-������? �����, �����!";
        	link.l1 = "�� ������� ����������, ������ ������. � ������� ��� ��������������. ���� � ���, ��� � ���� ���� ������������� ��� �� ���������� ���� ������. � ����� � ����� ���������� ���-������ ���������, ������� ���� ������� �������� ���� �������������� �������� � ������� ��������.";
            link.l1.go = "HStep_2";

		break;
		
        case "HStep_2":

            dialog.text = "� �� ����� ��� ������! ������� ����� �� ����, � �� ������ ������...";
        	link.l1 = "...������� ������, ���� �� ��������� �������������� ��� ���������. ������ ������. ��� ������ �� �������������� ����������� ���.";
            link.l1.go = "HStep_3";

		break;
		
        case "HStep_3":

            dialog.text = "������ �������, ���, � �����, ��� ������ �� � ����.";
        	link.l1 = "���������.";
            link.l1.go = "HStep_4";
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_2";
		break;
		
        case "HStep_4":
        
            NextDiag.CurrentNode = NextDiag.TempNode;
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(NPChar, sTemp);
            LAi_SetOwnerTypeNoGroup(NPChar);
            DialogExit();
            Spain_spyDie("");
		break;
		
        case "HStep_5":

            dialog.text = "� ���� �������� ��� ���� ���-����� ������, ���� ���� ���������. ����, ������, ��� ��� ������ ������. ��� ���� ����� ������.";
        	link.l1 = "�������?";
            link.l1.go = "HStep_6";

		break;
		
        case "HStep_6":

            dialog.text = "� ����� ��������� ���� ��� ������ �� ���-����� ����������. ���� � ���, ��� ������� ���������� - ��� ��������� - ����� �����-�� �����... ����� ������ �����. �� �������� ����! ����� ����� �����, ��� �� �������� ���� ����, � � � �������� ���������� � ����� ��������. ����?";
        	link.l1 = "����.";
            link.l1.go = "HStep_7";
           	link.l2 = "��� �� ��� ����.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";
		break;
		
        case "HStep_7":
        
            AddQuestRecord("FishermanQuest", "1");
            sld = &characters[GetCharacterIndex("Fisherman")];
            sld.dialog.currentnode = "FStep_1";
            NextDiag.TempNode = "HStep_9";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;
		
        case "HStep_8":

            dialog.text = "��� �� �� �������� ���?";
        	link.l1 = "������.";
            link.l1.go = "HStep_7";
           	link.l2 = "���.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";

		break;
		
        case "HStep_9":

            dialog.text = "����?";
            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
            {
            	link.l1 = "� ��� �������, ������ ������.";
                link.l1.go = "HStep_10";
            }
            else
            {
            	link.l1 = "���� �������� ���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HStep_9";
            }

		break;
		
        case "HStep_10":

            dialog.text = "�� ����� ����! ���? ��� �� �������� ����?";
        	link.l1 = "�� ����������� ���� � ���� ������ �����.";//+Pchar.questTemp.CapBloodLine.fishplace;
            link.l1.go = "HStep_11";

		break;
		
        case "HStep_11":

            dialog.text = "������, ��� �� � ������ �� ���������!.. �����, ��� ���� ������.";
        	link.l1 = "�������������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            AddMoneyToCharacter(pchar, 2000);
       		CloseQuestHeader("FishermanQuest");
		break;
		
		
        //-->��������� �����
        
        case "SSStep_0":
        
            dialog.text = "��� ����� ���������. ��� ���������?";
        	link.l1 = "��� ��� ��� ����������. ��-�-�� ���.";
            link.l1.go = "SSStep_1";
           	link.l2 = "� ���� ��� ��� ��������� ���� ����? ��� ���� ����� �� ����������?";
            link.l2.go = "SSStep_2";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_1";
            chrDisableReloadToLocation = false;
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", true);
            
		break;
		
        case "SSStep_1":

            dialog.text = "*������� ����*";
        	link.l1 = "";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;
		
        case "SSStep_2":

            dialog.text = "����� ����������, ���� � ���� �� ����������.";
        	link.l1 = "��� ���� �� �������������.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;
		
        case "SSStep_3":

            dialog.text = "(��������): ���������� ������!.. � ���� ������� � ���� ������, � ����� � ����, ������� ������! �� �� ���������, ���-��� ''����� ������''... � �� ��� ��� �������?!";
        	link.l1 = "��������� ��� ��������.";
            link.l1.go = "SSStep_4";
		break;
		
        case "SSStep_4":

            dialog.text = "��� �, ��� �� �� ������... �� ���������!";
        	link.l1 = "���, �������, � ���� ����������...";
            link.l1.go = "fight";
            sld = &characters[GetCharacterIndex("Griffin")];
            sld.dialog.currentnode = "GRStep_14";

		break;
		
		//--> �������������
		
        case "QSStep_0":

            dialog.text = "����, ����, ����... ������� � ����� ������ �������� �����, ��� ������� ���� ������ ��� ������. ������, ������� ��� � ���� ������ � �� ������ � ��� ������� ������, ��� ���� �� ���� ������, � ���� ���� ��� ����� ����������, �� ������! ���� ���� ��������� ���������� ������� � ������� ��������, ����� �� ���� ��������� � �������, ������ ����������������� �����. � ��� ������� �������� ����� ����, ����� ����������� ������ ��� � ����...";
        	link.l1 = "��� �� �� ����� �����������, ������, ������� ��� � ���� ����, �������� ���� ������������ � ����.";
            link.l1.go = "QSStep_1";
		break;
		
        case "QSStep_1":

            dialog.text = "�� ����� �������������, ������. ��� �, �� ���� �������� - �� �����. ���� ���������� ���-���, ��, �����, �� �������� �� ����������...";
        	link.l1 = "� ��� �� ����?";
            link.l1.go = "QSStep_2";
		break;
		
        case "QSStep_2":

            dialog.text = "� ����, ��� � ��� ���� ������ � ������� �����������...";
        	link.l1 = "�� ����� ����������. � ������ ���������, � ����, ��� ����������� ��� ��� ������� ������ ������ �� ����, �������� ���. � ���� �������� ������ � ������� ��� ���� �������.";
            link.l1.go = "QSStep_3";

		break;
		
        case "QSStep_3":

            dialog.text = "������, ���� ������� ���������� ������ � ���������� ��������, ��� ������� � ���� �� ���������� ����������� ����� ��� ����, � �����, ������, ���� ����� ������ ��������� �����, �� ������� ������ ������� � �����������.";
        	link.l1 = "��� �� ���� ���������?.";
            link.l1.go = "QSStep_4";

		break;
		
        case "QSStep_4":

            dialog.text = "��������� �������. ����� ����.";
        	link.l1 = "�������? ��� �� ���� ��� �������, ��� � �����. � ��� ��������� ��� ����� � ��������?..";
            link.l1.go = "QSStep_5";

		break;
		
        case "QSStep_5":

            dialog.text = "���� �� ��� ����� ���, ��� ������� ������. ��� �� �����, ��� � ���. ��������� ������� ������� - �������, ��� ��� �������, �� ��������� ��� ���� ������. ������� ���� ��� �� ���� ���� �� ����� ���� ����, ��� ��������� �. ������ �� �����������, ������. ������ ��������.";
			pchar.LockBloodWeaponsOptions = true;
        	link.l1 = "������� ��� ������, ��� ������ �����. ����������� ������ � �����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "QSStep_6";
            
            sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.Dialog.CurrentNode = "GStep_1";
            sld.protector = true;
            sld.protector.CheckAlways = 1 ;
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true);
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);
            
            sld = characterFromID("MisStid");
            sld.Dialog.CurrentNode = "MSStep_3";
        	sld.talker = 10;
            ChangeCharacterAddressGroup(sld, "Bridgetown_TownhallRoom", "barmen","bar1");
            
            sld = characterFromID("Den");
            LAi_SetCitizenTypeNoGroup(sld);
            //LAi_SetStayTypeNoGroup(sld);
            LAi_SetOwnerTypeNoGroup(sld);
            sld.Dialog.CurrentNode = "DStep_3";
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto","goto6");
            
            sld = ItemsFromID("MsStid_ring");
			sld.shown = true;
			sld.startLocation = "Bridgetown_TownhallRoom";
			sld.startLocator = "item1";
			
            pchar.quest.PrepareToEscape3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape3.win_condition.l1.location = "Bridgetown_TownhallRoom";
            pchar.quest.PrepareToEscape3.function                  = "FindMsStid_ring";
			AddQuestRecord("WeaponsForEscape", "11");
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3";

		break;
		
		
        case "QSStep_6":

            if (GetCharacterItem(pchar,"MsStid_ring") > 0)
			{
                dialog.text = "������ ��������! ������������!";
                link.l1 = "��� �� ������ ��� ������?";
    			link.l1.go = "QSStep_7";
                link.l2 = "��� ���� ����. ��� ��� � ������� � �������?";
    			link.l2.go = "QSStep_12";
			}
			else
			{
                dialog.text = "���-�� ���?";
            	link.l1 = "���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "QSStep_6";
            }

		break;
		
        case "QSStep_7":

            dialog.text = "�����? ������� ������, � � ��� �� ��������� ������� �� ����.";
        	link.l1 = "���� ������ ����������� ��� �����. ��� ��� �� ������? ������ ���?";
            link.l1.go = "QSStep_8";

		break;
		
        case "QSStep_8":

            dialog.text = "��� ������� ������ ������ ��� ����, �� ��� �� ���� �������� �����. ��� ������� ����� ������� ���, � ������ � ����� ��������� ���� ����� ������ � ������ ��� ��� ��, ��� ������.";
        	link.l1 = "� �����, ��� �� ��� ������ �� �� �����, ����� � ������ ��� ���� � ����-������? ���� �����, ��� ��������� �� �������� �������? ������� ��� ������ ��� ������������.";
            link.l1.go = "QSStep_10";

		break;
		
        case "QSStep_10":

            dialog.text = "*������* ����������� ������� ���� ��� ������ ���� � ����� � ����� �����... ��� ����!";
        	link.l1 = "� ������, ���, ��� ����� ������� ��� ��� ������� � ���������, ������ �� ������� ���� ���������.";
            link.l1.go = "QSStep_11";
            TakeItemFromCharacter(Pchar, "MsStid_ring");

		break;
		
        case "QSStep_11":

            dialog.text = "�� ����� �� ��� ���� ����������� �����, ����� ����. ��� ���� ������ � ������ - ����������. ��� �����, ���� �����, ������ ����� ��� ����������.";
        	link.l1 = "��� �, �����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;
		
        case "QSStep_12":

            dialog.text = "�������� ����������. ��� ���� ������ � ��� �����������. ��������.";
        	link.l1 = "����� ����������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            TakeItemFromCharacter(Pchar, "MsStid_ring");
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;

		  //--> ����������

        case "VLStep_0":
            dialog.text = "� �� � ��������, �� ����� ����� �� ���� ����� �������.";
        	link.l1 = "��� ��� ������?";
            link.l1.go = "VLStep_0_1";
            NextDiag.TempNode = "VLStep_1";
		break;
		
		case "VLStep_0_1":
            dialog.text = "�� ��� ������ ������ ������� � �� ���� � ��� �� �����, � �� ������� ������ ����� ���� ���������. �� ��� �� �� �������� ��� ��������� ����?";
			SetQuestHeader("VolversonRum");
			AddQuestRecord("VolversonRum", "1");
			pchar.SeekVolverstonRum = true;
        	link.l1 = "������, � ���� ��� ������. ��� ������ ������� � ������ ����� ����� ������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";
		break
		
		case "VLStep_0_2":
            dialog.text = "�� ������ ��, ��� � ������?";
			if(CheckCharacterItem(pchar, "potionrum"))
			{
				link.l1 = "���, �����.";
				link.l1.go = "VLStep_0_3";
			}
			link.l2 = "��� ���.";
            link.l2.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";
            
		break;
		
		case "VLStep_0_3":
            dialog.text = "(�� �� ��������� ��������� �������� ��� ������� �� ��������� �����) ��...  ��� ������� �����. �� ������� � ������? � � ����.";
			RemoveItems(PChar, "potionrum", 1);
			AddQuestRecord("VolversonRum", "2");
			CloseQuestHeader("VolversonRum");
			DeleteAttribute(pchar, "SeekVolverstonRum")
        	link.l1 = "���� ��������� ���� ��� �����������. ������� �� ������ �� ���������� �� ��������� � �� ���������� ��� �������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_1";
            //Pchar.questTemp.CapBloodLine.Volverston = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
		break;

        case "VLStep_1":

            dialog.text = "������, ����� �� ��� �������� ��� ������� ����?!";
        	link.l1 = "������� ��������, ��� ����. ������ ����� �� �������� � ����� ���������� �������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "VLStep_1";

		break;
		
		 case "VLStep_11":

            dialog.text = "������� � ��������! ����, ��� ������� ����� ���� ��������� ����� �������� ������ �� ������ - ��� � ����������� ��, ��-��!";
        	link.l1 = "���� �� ��� ��� ���� �����, �� �����, �� �����, ��� ��� ���� �� ������, ��� ����.";
            link.l1.go = "VLStep_12";

		break;
		
        case "VLStep_12":

            dialog.text = "��, �����, ��������, �� ��� ������ ����.";
        	link.l1 = "�� � �� � ��� ����� � ����� ����������. ����������, �� ������� ����, ��������� � ����� � ���� ����� �� ������, �� �, �����, ���� ���� ������� �������� ��� �������, �� ������� �������� ������ ����������. ������� �� ��� ��������?";
            link.l1.go = "VLStep_13";

		break;

        case "VLStep_13":

            dialog.text = "������� ������� ������, ����� ��������� �������, ��������� � ���� ������ �������, ��� �� ����, ������ ���� ����, ����� ������, ������, ���? � �������� ������������!";
        	link.l1 = "� ����, ��� �� �����������.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("VolverstonAdd");

		break;
        //--> ��������� �������

        case "HTStep_0":

            dialog.text = "��� ������� ������ ������ ��� ����, �� ��� �� ���� �������� �����. ��� ������� ����� ������� ���, � ������ � ����� ��������� ���� ����� ������ � ������ ��� ��� ��, ��� ������.";
        	link.l1 = "� �����, ��� �� ��� ������ �� �� �����, ����� � ������ ��� ���� � ����-������? ���� �����, ��� ��������� �� �������� �������? ������� ��� ������ ��� ������������.";
            link.l1.go = "HTStep_1";

		break;
		
        case "HTStep_1":

            dialog.text = "� ���� �����... �������� ������������� ����, ����.";
        	link.l1 = "������, �� ��������� ��� ���������� � � ���� �������. �� ������������ ��� � ���� ��������, � � �� ���� ��������� ���� ��������, ������ ������� ����.";
            link.l1.go = "HTStep_2";

		break;

        case "HTStep_2":

            dialog.text = "*������* � ��������� ������ ����, �� ������. �� ��� ���� �����, � ������ ��������� ��, ��� �����.";
        	link.l1 = "����� � ����� ���� ���������� �� ����. ��� �� ���� � ��� � ���� ������?";
            link.l1.go = "HTStep_3";

		break;

        case "HTStep_3":

            dialog.text = "������� ���� ������ ������� �� ����� ������ ���������. ������� �� �� ���� - �� ����, �� �� - ��� �������. ��-�� ���� � ������� �����: �����, �����, �����. ��-�� ���� � ����� ����!..";
        	link.l1 = "��� ���������?";
            link.l1.go = "HTStep_4";

		break;

        case "HTStep_4":

            dialog.text = "��������� �� �������! ��� ��� �� ����� ��������. � �����, ��� ������ ������� �� ����� ��� ����, ��� �� �������������� ������� �� ��� ���� ����� ���� ��������� ������������� �� ���� ��������... �� ������, ����� ������������ ��� �������� �� �����? ��� ���������� ����� ���� �� ���������� ������, ���� ������!";
        	link.l1 = "��� �, ����� ����� ���. ��� ��� ��� �����?";
            link.l1.go = "HTStep_5";

		break;

        case "HTStep_5":

            dialog.text = "�������, �������... �� ���-�� ���, ������! ��������� � ����, ������ � �����! �� ��� ���� ��� ����������� ������, ���� ��� ���� ��� ����! ������� ��� ������ ������ � �������.";
        	link.l1 = "��� �������, �� ������ �������� � ��� ������.";
            link.l1.go = "HTStep_13";
            NextDiag.TempNode = "HTStep_10";
        	link.l2 = "�� ������, ��� ������ �����, �������? ��� ������ �� �������� ����� ���.";
            link.l2.go = "HTStep_6";
		break;
		
        case "HTStep_6":

            dialog.text = "���� �� � ���� �� ��� ������������, ��� ���� ��� ������, � �� �� ���� ��� �������� � ��� ��������.";
        	link.l1 = "��� �� �����, �� ������ ���������. �������, ����� �� ������� ��� ������, ������ ����? �� �����...";
            link.l1.go = "HTStep_7";

		break;
		
        case "HTStep_7":

            dialog.text = "������ ���� �������, ����! ��� ���� �����, � �� ������! ������� ���������, �� ���������� ������ ��� - �� ����! �������� � �������� ������� � ��� ����!";
        	link.l1 = "������, �������. � ���� ���.";
            link.l1.go = "HTStep_13";
           	link.l2 = "��� ����? ���� �� ��������, �� ��� ������� ������... �������� ����. �� ����� ������ ���� � ���� � ������ ����� �����, � �� ���� ��� ������ ��������� ��������� ���������� � ���������, ��� ��������, ��� ����� ��� ����������� �����. ��������� ��� �� ���-���, ������ ���� ��� ������ �� �������!";
            link.l2.go = "HTStep_8";
            NextDiag.TempNode = "HTStep_10";

		break;
		
        case "HTStep_8":

            dialog.text = "��... �� ��������� ���������� ����, ����� ���� ���� � ���� ��� �����?!";
            if(Pchar.SPECIAL.Charisma >= 5)
            {
            	link.l0 = "��... ��, ��� ���� � �������.";
                link.l0.go = "HTStep_9";
            }
            else
            {
                AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            }
           	link.l1 = "������, �������. � ���� ���.";
            link.l1.go = "HTStep_13";

		break;
		
        case "HTStep_9":

            dialog.text = "�����, � ��������! � ����� ���������� �� ��������� ���. � ������������ � ����.";
        	link.l1 = "�� �����.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 150);
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "2");
            CloseQuestHeader("HugtorpTrouble");

		break;
        case "HTStep_10":

            dialog.text = "�� ��� ��������? �� �����?";
            if (GetCharacterItem(pchar,"DOjeronRing") > 0)
            {
                link.l1 = "������� ������. ��� ��, ��� �� ������.";
                link.l1.go = "HTStep_11";
                TakeItemFromCharacter(Pchar, "DOjeronRing");
                ref itm = ItemsFromID("DOjeronRing"); //���������� ��� ��� ����
                BackItemName("DOjeronRing");
                BackItemDescribe("DOjeronRing");
                itm.picIndex = 2;
                itm.picTexture = "ITEMS_9";
            }
            else
            {
                link.l1 = "���, ������ ����� ������, �� ��������� �� �� - ��-��������, ���.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HTStep_10";
            }
		break;
		
        case "HTStep_11":

            dialog.text = "��� �... �������-��... � ������������ � ������ ������, ����. � ������� ����.";
        	link.l1 = "�� �����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "4");
            CloseQuestHeader("HugtorpTrouble");

		break;
		
        case "HTStep_12":

            dialog.text = "��� ������? ��� �� ���� ���������?";
        	link.l1 = "���� ��� ���, � ������, ����� ������ �����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";

		break;
		
        case "HTStep_13":

            LoginWinterwood();
			Pchar.HugtorpQuestStart = true;
            AddQuestRecord("HugtorpTrouble", "1");
            NextDiag.CurrentNode = "HTStep_10";
			DialogExit();

		break;
		
        case "HTStep_14":

            dialog.text = "�����, ������ ����� - ���� ���������� ������ ��������� ������� �����, ��� ��� � ��� ������, ����� �� ������ ������� ��� ������. �� ���� ����� ��������, ���, ��� ��� ������� ���������� ���-����� ������ � ������� ����� ������� - �� ���� ���������.";
        	link.l1 = "��� � ������?";
            link.l1.go = "HTStep_15";
            chrDisableReloadToLocation = false;

		break;
		
        case "HTStep_15":

            dialog.text = "��� ������, �����, ����� ��� �� ���������� � ����� �� ������ ��� ���� � ����, ���� �� �� ������ ����������.";
        	link.l1 = "�������. ����� �����-�� ������ ���� �� ������, ��������, � ���� ��� �����������...";
            link.l1.go = "HTStep_16";



		break;
		
        case "HTStep_16":

            dialog.text = "���� ��������, �� ���� ����� �� ������ � ����������, �� ����� ��������� �������� ���� ��� �����. ����� ������ ������ �� ������������� - �������� �������. � ��� ��������, �������� ������ � ��������� �������.";
        	link.l1 = "��, ��� � ��������, � ������� ������������� �����, � �� � �������� ������� ����� � �����. ����������?";
            link.l1.go = "HTStep_17";

		break;
		
        case "HTStep_17":

            dialog.text = "��, �����, �� ����� ����� ���� �� �����. � ����������� �������� - ���� ������ ������ ������� ���� ��� �������.";
        	link.l1 = "� ���� ���������.";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("ReturnToPlantation3");
            AddQuestRecord("EscapeFormBarbados", "1");

		break;
		
        case "HTStep_18":

            dialog.text = "������ �������, �����...";
            if(Pchar.questTemp.CapBloodLine.SpainInBridgetown == false)
            {
               	link.l1 = "��� ���������?";
                link.l1.go = "HTStep_19";
            }
            else
            {
               	link.l1 = "� ��� � �����.";
                link.l1.go = "HTStep_20";
            }
		break;

        case "HTStep_19":

            dialog.text = "������� ��������� ���������. ������� � ��� ���� ��� ����� ������ ����� ������� �������. ��� ��� ��������� �����. ��� �������� � ������ �������� ����������� ���������, ���, �� �������� ����������, �� ����������� ����� � ����� � ����������� ����� � ���� �������� ������ �� �������� �����.";
        	link.l1 = "��� ��� � ���������� ������������� �������������� ������. ���� ���� ���� ������ �����, ��� �� ����� ����� ������!";
            link.l1.go = "HTStep_20";
            AddQuestRecord("EscapeFormBarbados", "3");

		break;
		
        case "HTStep_20":

            dialog.text = "� ��� �� ��� ���� ������? ������ ������, ���� ������ ���������...";
        	link.l1 = "���� �������� - �� �������� ������ �������.";
            link.l1.go = "HTStep_21";

		break;
		
        case "HTStep_21":

            dialog.text = "����� ������?";
        	link.l1 = "���, ��� ����� ������ �� �����. �����, ��� ������� ����� ������� ������ ������������ �� ������, ��� ��� �� ����� ������ ��������� ���.";
            link.l1.go = "HTStep_22";

		break;
		
        case "HTStep_22":

            dialog.text = "����� ����� �������� � ��� � ���������, ��� ����� ����� �� ���������� ������! ���� ���, �����!";
        	link.l1 = "����������� ����������� ���������...";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("CapBloodOfficers");
            AddQuestRecord("EscapeFormBarbados", "4");
            NextDiag.TempNode = "HTStep_22b";

		break;
		
        case "HTStep_22b":

            dialog.text = "����� ����������, �����?";
        	link.l1 = "��� �� ����, �� ���� �� �����.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_22b";
            AddDialogExitQuestFunction("CapBloodOfficers");

		break;
		
        case "HTStep_23":

            dialog.text = "����� ������?";
        	link.l1 = "���, ��� ����� ������ �� �����. �����, ��� ������� ����� ������� ������ ������������ �� ������, ��� ��� �� ����� ������ ��������� ���.";
            link.l1.go = "HTStep_22";

		break;
		
        case "HTStep_24":

            dialog.text = "�� ��� ����, �����. ��� �����, ��� �� � ������, �� �������� ���� ���������� �������� ����� ��� ������.";
        	link.l1 = "��, �������, �� �����, ��� ������ ����������. ��� �������, �� �������� �����. ������� �� ��� ��������?";
            link.l1.go = "HTStep_25";

		break;
		
        case "HTStep_25":

            dialog.text = "�����, �� ������ � ���������� �������, ����� *�����* ��� ���� �� ������ ����, �� ����������� ����, ������������ ������� � �������� �����. ���� ������������, � ����� �� ���� �����.";
        	link.l1 = "�������, ���������, �� ������ �� ���� ����� � ���� ��� ����� �����, � ������ ��� ��� ����� ��������� �� ����� ���.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("HugtorpAdd");
		break;
		
        //--> ������� ����

        case "DKStep_0":

            dialog.text = "���, ���, � ������ �� ����. ��������, �� ��� �� �����... �� ��� ��� �������.";
        	link.l1 = "�������? ��� ���������?";
            link.l1.go = "DKStep_1";

		break;

        case "DKStep_1":

            dialog.text = "��������� ����� ������� ����. ����� � ����� ������ ����������, �������� ����� ���, ������� �������� � ������� �����. �����, ��� ������ ������ �������...";
        	link.l1 = "������?.. ��. ��� �, ���������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
            sld = characterFromID("Bishop");
            sld.Dialog.CurrentNode = "BStep_2";
            AddQuestRecord("DiekeQuest", "1");
		break;
		
        case "DKStep_2":

            dialog.text = "� �������, ��� ��� �����.";
        	link.l1 = "��� �� ��� ���������, ���.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
		break;

        case "DKStep_3":

            dialog.text = "������� �� ���������� �������� �����-�� ����, �� ���������� ����... ������, ������ ���-��� ���������.";
        	link.l1 = "���������, �������. ������, ��������������� ��� ������� ����, ��� ������� �� ��� �� ����������. �� ������������� � ���� ������ �����.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Dieke = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "DKStep_4";
            CloseQuestHeader("DiekeQuest");

		break;
		
        case "DKStep_4":

            dialog.text = "� ���, �� ������� ���������� ����!";
        	link.l1 = "� ����, ���.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_4";
            
		break;
		
        case "DKStep_5":

            dialog.text = "�� �����, ��� �� ���� � ������� �������� ������� ������� �����.";
        	link.l1 = "�������, �� ������� ������, �� ���� ������ �������� ������. ������� � ����?";
            link.l1.go = "DKStep_6";

		break;
		
        case "DKStep_6":

            dialog.text = "���� ������, � ���� �� ���� ��� ������... � ����� �������� ����, ������ �� ����, ����� ��������� ���� � ������ ��������� ������. ������ � ������ �������� ���, � �������� � ���������� �� �� ��������, ��������� ������ �������, �� ��� ��� ������, ��� ������� �� ����, ������, ��� ����� �� ������ � ���� �������� ����.\n�� ���������� �� � ����� ����������� � �����, ������ � ������� ������������. � ����� � ���� �� ������, �� ����� ������� ����� � � ��� �� ������ ���������� �� ������, �� ����� ����.";
        	link.l1 = "������, � ���� ���. � ������ ��� ��������, �� ��� ��� �� �� �������.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("DiekeAdd");
		break;
		
        //--> ��� ���

        case "OGLStep_0":

            dialog.text = "�� � ���, ������ ���� �������?";
        	link.l1 = "� � �������� ����������� ����� ���� �� ������� ���������� �����.";
            link.l1.go = "OGLStep_1";

		break;

        case "OGLStep_1":

            dialog.text = "������ �� ������? �� ��������, ��� ��� ������? �� �� ������ ���������-������, �� � �������� ������������ ������� �� ����������������...";
        	link.l1 = "��� �������� ��� ���� ����. �� ��� ����� ��������, ��� ���-��� ����� ����� ��� ������. ��� �����, ��� ���� ����������� �������� �� ����.";
            link.l1.go = "OGLStep_2";
		break;

        case "OGLStep_2":

            dialog.text = "��� �, ����� � ���� ������ ������������ ���� � ����� �����������...";
        	link.l1 = "�� ������, ��� ���������� ����. � �����, ����� ���������� ���� ����������� � ����.";
            link.l1.go = "OGLStep_3";
		break;
		
        case "OGLStep_3":

            dialog.text = "�����, ��� �� ��� ����� �� ��������, � �� ����.";
        	link.l1 = "� ��� ��������?";
            link.l1.go = "OGLStep_4";
		break;
		
        case "OGLStep_4":

            dialog.text = "��-�-�... �������� � �������.";
        	link.l1 = "������? ��...";
            link.l1.go = "OGLStep_5";
		break;
		
        case "OGLStep_5":

            dialog.text = "� ���� ���� ��������� ����� �����. ��������� �������� ���� ����, � ��� ��� ���� ����� �����. �� ����� ���, � � ��� �� � ��� ��������, ����� ���� ����� �����������\n�� ���� ����� �� ������ �����.";
        	link.l1 = "�� ��� �� �������� � ����������?";
            link.l1.go = "OGLStep_6";
		break;
		
		
        case "OGLStep_6":

            dialog.text = "� �� ���������, �� ��� ����� - �������� �����-�� � ����������.";
        	link.l1 = "�����, �����... � �� ���� ���� ��� ��������, � ����� ����, � ������ ��� �� �����. ������� �� ������?";
            link.l1.go = "OGLStep_7";
		break;
		
        case "OGLStep_7":

            dialog.text = "� ������ ���� �����, ��� ��� ������, ����. ����� ��������� �� �������, ���� �� ����������� �������.";
        	link.l1 = "��� �, ���������.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "OGLStep_8";
            Pchar.questTemp.CapBloodLine.Ogl = false;
            AddQuestRecord("OglQuest", "1");
            
		break;
		
        case "OGLStep_8":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == true)
            {
                dialog.text = "��, �����?";
            	link.l1 = "���� ���� �������, ���. ������ � �� �������� ������.";
                link.l1.go = "OGLStep_9";
            }
            else
            {
                NextDiag.TempNode = "OGLStep_8";
                dialog.text = "��, �����?";
            	link.l1 = "���, � ��� �����.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "OGLStep_8";
            }
		break;

        case "OGLStep_9":

            dialog.text = "���? �� ����� �� ���� ������?";
        	link.l1 = "��� ���� ������������ ������ � ������.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Ogl = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "OGLStep_10";
            AddQuestRecord("OglQuest", "3");
            CloseQuestHeader("OglQuest");

		break;

        case "OGLStep_10":

            dialog.text = "����� ����� ������������?";
        	link.l1 = "���� �������, ���.";
            link.l1.go = "exit";
            NextDiag.TempNode = "OGLStep_10";

		break;
		
        case "OGLStep_11":

            dialog.text = "������ ���� �������, �������. ����� ��� � ��� �� �������, ��� �������.";
        	link.l1 = "���, ���� �� ��������, �� �����-�� ��� ��������� �� ����������� �����?";
            link.l1.go = "OGLStep_12";

		break;
		
        case "OGLStep_12":

            dialog.text = "� ������� ���������� ��� � ��� ������ ��������� �� ���� ����� ��� ����������!";
        	link.l1 = "�����, ��� �� � ������� ����� �����, ������� �� ��� ������� ���������?";
            link.l1.go = "OGLStep_13";

		break;
		
        case "OGLStep_13":
            dialog.text = "���� ������, � ���� �� ���� ��� ������... � ����� �������� ����, ������ �� ����, ����� ��������� ���� � ������ ��������� ������. ������ � ������ �������� ���, � �������� � ���������� �� �� ��������, ��������� ������ �������, �� ��� ��� ������, ��� ������� �� ����, ������, ��� ����� �� ������ � ���� �������� ����.\n�� ���������� �� � ����� ����������� � �����, ������ � ������� ������������. � ����� � ���� �� ������, �� ����� ������� ����� � � ��� �� ������ ���������� �� ������, �� ����� ����.";
        	link.l1 = "������, � ���� ���. � ������ ��� ��������, �� ��� ��� �� �� �������.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("OglAdd");

		break;

	}
}
