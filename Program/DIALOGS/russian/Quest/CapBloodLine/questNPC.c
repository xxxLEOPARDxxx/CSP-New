// ����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator, sTemp;
    int iTime, n, iChar;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);




	switch(Dialog.CurrentNode)
	{

		// ----------------------------------- ������ ������ - ������ �������
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Exit_Away":
            
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        


        
        case "sfight":
        
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            LAi_group_Attack(NPChar, Pchar);

		break;
        
        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
            AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = false;
            LAi_CharacterPlaySound(npchar, "toArm");

		break;
		
        case "Qfight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_FightGroups(GetNationNameByType(ENGLAND) + "_citizens", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = true;
			//#20190120-03
			LAi_group_SetCheck("TmpEnemy", "OpenTheDoors");

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
			link.l1.go = "Qfight";
		break;
		
        case "Draguns_0":
			dialog.text = LinkRandPhrase("��� �� - ����� ���!", "������ ��� ������!", "� �� ����!");
			link.l1 = LinkRandPhrase("������!!", "��� �� �� ���!", "�-���, ����!");
			link.l1.go = "Draguns_1";
 		     NextDiag.TempNode = "Draguns_0";
		break;

        case "Draguns_1":
        
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
		break;

		case "First time":
        	dialog.text = "������";
            link.l1 = "...";
            link.l1.go = "Exit";
            

            if (CheckAttribute(npchar, "CityType") && npchar.CityType == "soldier")
            {

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape2_1")
                {
                    dialog.text = "������� ����� ������� � �� �������� ����.";
					link.l1 = "�����, ���� ���������. � ����� ����� ��������� ��������, �������� ����, �������. �� ���������� � ��� ����������, � ������ ����� � �������� ������� �������.";
					link.l1.go = "SQStep_0";
					Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_2";
				    break;
                }
                
               	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY || ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
                {

    				dialog.text = RandPhraseSimple("����! ����� ������! ��������� �� ����!", "������ ���! ���������� �������� ���!");
    				link.l1 = RandPhraseSimple("��������, �����������!", "��� �� �� ���!");
    				link.l1.go = "sfight";
    				break;
				}

        		switch (rand(5))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "� ���� ��� ��� �������� ��� ��� ����?";
							link.l1 = "� �������� ��������� ���������� ������.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "�, ��� ��, ������ ����. �� ������ ����, ����� ���� ������� � ''����� �� �����''";
							link.l1 = "� ���, ��� �� ����������.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "���� �����, ���!";
							link.l1 = "� ���� ��� ���� ������, ��� � �� �� ���.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "����� ������, � � �������� ������ �����. ��� ������������ ����������� ����������� � ��������� ��� �� ������ ����.";
							link.l1 = "����������. �� ����� �� ���� ������, ������ � ���� �����.";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "���� ���� ������� ���������, �� ������� ���� ����-������ �������, � ����� ����������� �� ���������.";
							link.l1 = "����������.";
							link.l1.go = "exit";
						break;



						case 5: ////////////////////////////////////////////
							dialog.text = "������� ����� ������� � �� �������� ����.";
							link.l1 = "��� �������, ������.";
							link.l1.go = "exit";
						break;


					}
    		}
    		
    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen")
    		{
            	dialog.text = TimeGreeting() + ", ������.";
        		link.l1 = "������������.";
        		link.l1.go = "Exit";
        		if( Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
        		{
                    link.l2 = RandPhraseSimple("�� ����������, ��� ��� ����� ������� ������?", "��� ����� ������ �����. �� ������ ���?");
                    link.l2.go = "Citizen_0";
                }
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = RandPhraseSimple("���� �� ���-���� ��������� - �� ���������� ���������� ��������?", "� ��� ��������, ������� �������� ����� ����� ���-���� �� ��������� �����. ��� �� ���� �� �������?");
    				Link.l2.go = "Citizen_1";
                }
    		}
    		
    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && npchar.location.group == "merchant")
    		{
                if(findsubstr(Pchar.questTemp.CapBloodLine.stat, "PrepareToEscape" , 0) != -1)
                {
                        if (CheckAttribute(npchar, "quest.bGoodMerch") && sti(Pchar.reputation) >= 55)
                        {
                            dialog.text = "�, ������ ����, ������������! � ��� � �� ������������"+NPCharSexPhrase(NPChar, " ", "� ")+" ��� ����� �� �������� ����� ���������� ����, � ��� �� ��� ��� ����� ��������� � �������. ��� ������, ��� � �������� ��� �������!";
                            link.l1 = "�������������, ��� ������, ��� ���� ��������� ������������� � ����� ���������� ������. �� ���������� ��, "+NPCharSexPhrase(NPChar, "������� ���� ", "��� ������� ")+", ��� � ���� � ���������� ����� ��������� ����������� ����������� ������� � �����-������� ���������� ��� ������� ���� � �����?";
                            link.l1.go = "Merchant_0";
                            break;
                        }
                }
                if (CheckAttribute(npchar, "quest.bGoodMerch"))
                {
                    dialog.text = TimeGreeting() + ", ������.";
                    link.l1 = "������������.";
                }
                else
                {
                    dialog.text = "�� ��� ����� �������������. � �� ����, ������ �������!";
                    link.l1 = "��� �����.";
                }
        		link.l1.go = "Exit";
    		}
    		//���� �� ���������� - ���������� ������
    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
			    dialog.text = RandPhraseSimple(RandPhraseSimple("� ��� ����� - ������ � ��� ������.", "��� ������ ��� ��� ����!"), RandPhraseSimple("��� ������ ������� ������� ��� ����.", "������������ ��� �� �������� ������ ����� �� ���� �����!"));
				if(CheckAttribute(pchar,"GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
				{
					link.l1 = RandPhraseSimple("��, ����� � ������ ��� ������ ���������. � �����, ��� �� ����� ��� " + pchar.GenQuest.CaptainComission.SlaveName + "?","��, ���� �� �����������... ���-�� �� ��������� ������ �������� ��������� �� ����� " + pchar.GenQuest.CaptainComission.SlaveName + ". �� � ��� �������� �� ������?");
					link.l1.go = "CapComission_1";
				}
				else
				{				
					link.l1 = RandPhraseSimple("����������, ��������.", "��� ���� ����.");
					link.l1.go = "exit";
				}	
    		}
    		
    		if (npchar.id == "Bridgetown_Poorman")
    		{
            	dialog.text = "��, ������, ������� �������... �, ��� ��, ������ ����.";
        		link.l1 = "�����.";
        		link.l1.go = "Exit";
    		}
    		
    		if (npchar.id == "QuestCitiz_Bridgetown")
    		{
            	dialog.text = TimeGreeting() + ", ������.";
        		link.l1 = "� ���.";
        		link.l1.go = "Exit";
    		}
    		
    		if (npchar.id == "SolderTakeBlades")
    		{
                dialog.text = RandPhraseSimple("� ����� ��� ��� ���� �����������, ��� ������, � �������?", "�� �� ��� ���������� ������, ������ �� ��������?");
        		link.l1 = RandPhraseSimple("�-�-�...", "��� �� �����...");
        		link.l1.go = "STBStep_0";
    		}
    		
    		if (npchar.id == "Winterwood")
    		{

                if(npchar.location == "Bridgetown_Brothel_room")
                {
                    dialog.text = "������ ����� ���� ����� ����?! �������� ����������!";
                    link.l1 = "����� ��������, �� ��� ������� ���.";
                    link.l1.go = "WWStep_7";
                    break;
                }
                dialog.text = "������ ����� ���� ����� ����?! �������� ����������!";
        		link.l1 = "�� ����� ��� �������! � ���� � ��� ����.";
        		link.l1.go = "WWStep_0";
    		}
    		
    		if (npchar.id == "Quest_Habitue")
    		{
				dialog.text = "�-��! �, ������, �� ��������� ������� ������� ������! �����, ������ ��� ��������� ����?";
				link.l1 = "����� � � ������� ����, ������ ��� �� ������, ��� � ���� ����� ������ �����...";
				link.l1.go = "exit";
    		}
    		
    		if (npchar.id == "Weston")
    		{
				dialog.text = "����� ����� �� ����� ����!";
				link.l1 = "��� �����.";
				link.l1.go = "exit";
    		}
    		
    		if (npchar.id == "MoneySpy")
    		{
                if(npchar.quest.meeting == "1")
                {
                    dialog.text = "����������!";
    				link.l1 = "��� �����.";
    				link.l1.go = "exit";
                }
                else
                {
                    npchar.quest.meeting = "1";
                    dialog.text = "�������-��! � ��� �����, �� �� �������! ���, ��-�, ���� ������� ������ ���-������?";
    				link.l1 = "�� ���� ������� �� ����-�� �������.";
    				link.l1.go = "MSStep_0";
    				link.l2 = "�-�-�-�... ��, ����������.";
    				link.l2.go = "MSStep_1";
                }
    		}
    		
    		if (npchar.id == "Fisherman")
    		{
                dialog.text = "�� ��������� ��� ���������, �? ��..";
    			link.l1 = "�� �����.";
                link.l1.go = "exit";
    		}
    		
    		if (npchar.id == "QStranger")
    		{
                dialog.text = "��� ��� �����?";
    			link.l1 = "� �����, ����� ������, �� �������� �� �� �������� �����, ������� � ���, ��� ������ �������� ����� ���-����?";
                link.l1.go = "QSTStep_0";
    			link.l2 = "��, �������, �� ����? ������ ���� �������?";
                link.l2.go = "QSTStep_1";
    			link.l3 = "�����, ��������� ���� ���������. ���� �����, �-�... ���, ��� �������. ���� �� ���������� �� ������� 30 000 ����������, ���� �������� ������� ��!";
                link.l3.go = "QSTStep_2";
    		}


		break;
		
		case "CapComission_1":
			dialog.text = "��� ������� �� �������. ������� ������� � �������� � �������. �� ������ ����� ��� �� ����� �������. �����, �� ����� �� �������� �� ����� ���������...";
			link.l1 = "�������, ��������.";
			link.l1.go = "exit";
		break;
		
		
		case "Citizen_0":
		
            if (!CheckAttribute(npchar, "quest.btmp"))
            {
                npchar.quest.btmp = true;
                if(rand(3)==2)
                {
                    dialog.text = LinkRandPhrase("����� � ������� �������� - ��� ���. �� ������ ���������� ��� �������.", "������� ����� � �������, �����. ���� ��������� �����, �� �������.", "�������� � ����� ������ ���... � ��������, ��� ��?");
                    link.l1 = "�������.";
                    link.l1.go = "Exit";
                }
                else
                {
                    dialog.text = RandPhraseSimple(RandPhraseSimple("�� ����, �����!", "����� �� ���� ������."), RandPhraseSimple("� �� ����, ������ �������!", "� ��� ���? � ���� ������ ������� �����... �, ��� ��, ������������."));
                    link.l1 = "�������.";
                    link.l1.go = "Exit";
                }
                
            }
            else
            {
                dialog.text = "������, �� ��� ���������� � ���� �� ����.";
                link.l1 = "��������.";
                link.l1.go = "Exit";
            }

		break;
		
		case "Citizen_1":

            dialog.text = LinkRandPhrase("����� �� ���� ��� ������.", "��� ���� ��������, ������, � ����� ��������� �� ����� �� ���� ����������.", "���, ��� ������ ��� ���������������, ������ ����.");
            link.l1 = "�������.";
            link.l1.go = "Exit";

		break;
		
		case "Merchant_0":
		
        	dialog.text = "� �� ���� ����������, ��� ���� ��� ��� ������������, � ���� ���� �������, ��� �� �������� ����� � �������������. ��� �� �����, ����� � ���� �������� �� ����� ��� �����������, ��� ���...";
    		link.l1 = "����������� �� ��� ������� ����� �������, ��� ������������ � ������������� ����������� ��������� ������ � ���������� ������� ������ �����, ��� ��� � ���������� ��������. ���� �� ��������� ����� ����� ������...";
    		link.l1.go = "Merchant_1";
    		
		break;
		
		case "Merchant_1":

        	dialog.text = "��� ��� ������ ��� ������, �������, ��� � �. ���, ��������, ������ ����. � ����� ���!";
    		link.l1 = "�������� ����������.";
    		link.l1.go = "Exit";
            NextDiag.TempNode = "Merchant_2";
            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape") Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";//fix ���� �� �������
            GiveItem2Character(Pchar, "Weapon_for_escape");                                                                 //��� ������� ��������
            AddQuestRecord("WeaponsForEscape", "10");
    		CloseQuestHeader("WeaponsForEscape");

		break;
		
		case "Merchant_2":

        	dialog.text = "� ����� ���, ������ ����!";
    		link.l1 = "���������.";
    		link.l1.go = "Exit";
    		NextDiag.TempNode = "Merchant_2";

		break;
		
		
		// ==> �������� ������, �������.
		case "STBStep_0":
        	dialog.text = "� ��, ���������� ���� ��� ������! ������� �������� ���������� ������, ����� �� ������ ���� ��� �������...";
    		link.l1 = "���, ��������, � ������� �� ����.";
    		link.l1.go = "STBStep_1";
            link.l2 = "������ �� ���������, ��� ���� �������!";
            link.l2.go = "fight";
		break;

		case "STBStep_1":
		
                dialog.text = "�, �����, ����������.";
                link.l1.go = "Exit_Away";
                Pchar.questTemp.sLocator = "reload1_back";
                Pchar.questTemp.iTime = 40;
                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
                while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "" && !HasSubStr(FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE), "blade5"))
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));

                }
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //GiveItem2Character(Pchar, "unarmed");
                //EquipCharacterByItem(Pchar, "unarmed");
                SetNewModelToChar(Pchar);
                //��������
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";
                chrDisableReloadToLocation = false;

		break;
		
		case "STBStep_2":
        	dialog.text = "��������� ����� ���� ���������. ���������� ����������� �� ���������...";
    		link.l1 = "��� �������.";
            link.l1.go = "Exit_Away";
            //link.l1.go = "finish";
            Pchar.questTemp.sLocator = "gate1_back";
            Pchar.questTemp.iTime = -1;
            
            chrDisableReloadToLocation = false;
            pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
            pchar.quest.CapBloodEscape2.win_condition.l1.location = "Bridgetown_Plantation";
            pchar.quest.CapBloodEscape2.function                  = "ReturnToPlantation2";
            
            sld = characterFromID("Hugtorp");
            sld.Dialog.CurrentNode = "HTStep_14";
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto18");
		break;
		
		//��������� �� ����������� ������
		case "SoldierNotBlade":

            if (Pchar.questTemp.CapBUnarmed == false )
            {
                dialog.text = LinkRandPhrase("������ ����� �� ������� �� ������ � ���������� �������? ���������� ����� ������!", "���������� ��� ���������� ������ ������ � �����!", "��, ��������, �������� ������ �����! ����� ������ � �����.");
                link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
    			link.l1.go = "exit";
                link.l2 = LinkRandPhrase("����� � ���!", "��������...", "����� ��������, � �������.");
                link.l2.go = "fight";
			}
            else
            {
                dialog.text = RandPhraseSimple("� ����� ��� ��� ���� �����������, ��� ������ � �������?", "�� �� ��� ���������� ������, ������ �� ��������?")+"\n� ��, ���������� ����  ��� ������! ������� �������� ���������� ������, ����� �� ������ ���� ��� �������...";
                link.l1 = "��� ��������, � ������� �� ����.";
                link.l1.go = "SoldierNotBladeEx";
                link.l2 = "������ �� ���������, ��� ���� ������!";
                link.l2.go = "fight";
            }
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
		
		case "SoldierNotBladeEx":

                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
                while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "" )
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));

                }
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //��������
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";

                iChar = GetCharacterIndex("SolderTakeBlades");
                if (iChar != -1)
                {
                    sld = &characters[iChar];
                    LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
                    chrDisableReloadToLocation = false;
                }
                NextDiag.CurrentNode = NextDiag.TempNode;
                DialogExit();

		break;
		

        // --> ��������� ������


 		case "SQStep_0":

            dialog.text = "�������? �� �� �����������!.. ������� �� ���... ���...?";
        	link.l1 = "������ ���, ��� ��� �������.";
            link.l1.go = "SQStep_1";
		break;
		
 		case "SQStep_1":

            dialog.text = "� ���������� ����������� ����. ��� ��������� ���� ���?";
        	link.l1 = "��� ��� ������� ��������, �� ���������� �� ������� �����������.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.sLocator = "houseSp2";
            Pchar.questTemp.iTime = 20;
            
            string smodel = NPChar.model;
            if (findsubstr(smodel, "eng_mush" , 0) != -1) smodel = "sold_eng_"+(rand(7)+1);
            sld = GetCharacter(NPC_GenerateCharacter("CPBQuest_Solder", smodel, "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            SetFantomParamHunter(sld); //������ �����
            sld.SaveItemsForDead = true; // ��������� �� ����� ����
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "reload","reload3");

            sld = &characters[GetCharacterIndex("Griffin")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "barmen","bar1");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "goto","goto2");
            LAi_SetStayTypeNoGroup(sld);
            sld = &characters[GetCharacterIndex("Spain_spy")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "goto","goto2");
            sld.dialog.currentnode = "SSStep_3";
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", 0, 0);
             //#20190120-02
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);

            
            pchar.quest.PrepareToEscape2_3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2_3.win_condition.l1.location = "CommonFlamHouse";
            pchar.quest.PrepareToEscape2_3.function                  = "_DeadSolder";

            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_3";
            DoQuestFunctionDelay("SpainSpyAttack", 20.0);
            
		break;
        // --> ��������� ���
        
        case "SLQStep_0":

            dialog.text = "������������, ������ ����, �� ����� ��� � ��� ������? �� �� ������ ��� �����-������ �������� �� �������� ����? � �� ����� ������ ��� �����, ��� ��������� ����������.";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
           	    link.l0 = "��� ������� ��� �������� - ��� ������� ���� �������.";
                link.l0.go = "SLQStep_3";
            }
        	link.l1 = "� ���������, �� �������� ���� � ���� ������ ���. � ��������� ����� ����� �� ������� ������������ ���������, ������ ����� �� ����, ��� ��� �������, ��� ��� ������� � ��� ����� �� ��������. ���, �� � ���� ������ ������������ - ������ ��������, ����� ��� ��������.";
            link.l1.go = "SLQStep_1";

        break;
        
        case "SLQStep_1":

            dialog.text = "������, � ���� ��������� ��������� ������ ������ ��������������. ����� � ���� ���, �� ���� ���-���, ��� ����� ������ ��� �����������. ���, ��� ���� ��� ���-���� ������� ��������� ���-������ ��� ����, �� � � ����� �� ��������.";
        	link.l1 = "������, � ��������� ��������� �����-������ ��������� ��� ����.";
            link.l1.go = "Exit";
           	NextDiag.TempNode = "SLQStep_2";

        break;
        
        case "SLQStep_2":

            dialog.text = "�� ������ ��� ���������, ������?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
            	link.l1 = "��, � ������ ��������� �� �������.";
                link.l1.go = "SLQStep_3";
           		link.l2 = "������� ���.";
                link.l2.go = "Exit";
             }
             else
             {
            	link.l1 = "���, ��� ���� �� ������� ������� ������ ��������.";
                link.l1.go = "Exit";
             }
           	NextDiag.TempNode = "SLQStep_2";

        break;
        
        case "SLQStep_3":

            dialog.text = "��������� ���, ������. � ���� ������������� ������� ��� ���� ������, � ����� ������ ��� �� �������������, ��, �����, ��� �� ����������� ������.";
        	link.l1 = "��, �� ����� ������ ����� ������!";
            link.l1.go = "SLQStep_4";
            TakeItemFromCharacter(Pchar, "migraine_potion");
            GiveItem2Character(Pchar, GetGeneratedItem("blade5"));

        break;
        
        
        case "SLQStep_4":

            dialog.text = "�� ������������ ������, ��� ����� �������� ��� �������, ��� ��� ����� ������ �� �������. ���� ������ �� �� ������� ����������� �� ����� ���������.";
        	link.l1 = "���������, ���� ���, �����������.";
            link.l1.go = "Exit";
            NPChar.talker = 0;
           	NextDiag.TempNode = "First time";

        break;
        
		
        // --> ���������
        
        case "WWStep_0":

            dialog.text = "��� �� ������, ������� �����?! ����� � ���� ����� ���� �� ��� ����?!";
        	link.l1 = "��� ����� ��� ��� ������...";
            link.l1.go = "WWStep_1";
        
        break;
        
        case "WWStep_1":

            dialog.text = "������?! �� � �� ������ ���� ��� �� �� ����� ������! ��� � ���� ���� ������ � �����-������ ��������, ������� ���������� ����� ���� � �����!";
        	link.l1 = "��� ����� �� ������ ��� ������, �� � ����� �� ������� ��� ������.";
            link.l1.go = "WWStep_2";

        break;
        
        case "WWStep_2":

            dialog.text = "�� ������ ��������� �� ���� �����!";
        	link.l1 = "� ��� � ����. ����� ���� ����� ������ ��� ����������. ������� ����� ��� �� ����� � �����.";
            link.l1.go = "WWStep_3";

        break;
        
       	case "WWStep_3":
		Dialog.Text = "�� ��� �, ���������� �� �������� ����� ���. � ���� ������� ��� ���� �����-������ �������, ����� ��� ���� ������� �������� �� �����.";
		link.l1 = "�� ������ �������.";
		link.l1.go = "WWStep_4";
        break;
		
		//��� �, ������ ������
	case "WWStep_4":
	
        PChar.quest.CapBloodLineTimer_3.win_condition.l1            = "Timer";
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.hour  = sti(GetTime() + 1);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.function = "WinterwoodDuel";

		NextDiag.CurrentNode = "WWStep_5";
		DialogExit();
    break;

    case "WWStep_5":

		Dialog.Text = "��, ���� ���� ���?";
		link.l1 = "� ���� ���� �������, � ���� ��������� � ����� ����� ������!";
		link.l1.go = "WWStep_5_1";
		link.l2 = "������ ����� ��������� ���� � ����� �������.";
		link.l2.go = "Exit";
		NextDiag.TempNode = "WWStep_5";
        break;

    case "WWStep_5_1":
		Dialog.Text = "��, �� ��� ������ ���� ������!";
		link.l1 = "��������� � ����.";
		link.l1.go = "WWStep_6";
    break;

	case "talk_off_town":
		Dialog.Text = "�� ���, �� ����� ����������� � ��?";
		link.l1 = "��. ������ ���������, ��� ����!";
		link.l1.go = "WWStep_6";
		GiveItem2Character(Pchar, "blade2");
        EquipCharacterByItem(Pchar, "blade2");
        chrDisableReloadToLocation = false;
    break;

	//����� ����!
	case "WWStep_6":
		AddDialogExitQuestFunction("Winterwood_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		
	break;
	
    case "WWStep_7":

        dialog.text = "��� �� ������, ������� �����?!";
    	link.l1 = "� ���� ���� ����� � ���, ��� �������� ������������������� ����������.";
        link.l1.go = "WWStep_8";

    break;
    
    case "WWStep_8":

        dialog.text = "� ���� ���� ��� �������, ����� �������� ����, ������ �� ������, � ��������, ����� �� ������ �� �������������.";
    	link.l1 = "� ���� ���� ���� �������. ����� �� ����������� � �������� ���� �� �����, � � ���� ������ �������.";
        link.l1.go = "WWStep_3";
        n = FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = true;

    break;
        
    // --> �����

    case "QHStep_0":

		dialog.text = "�-��! �, ������, �� ��������� ������� ������� ������! �����, ��������� �� ���������� ����? � ������.";
		link.l1 = "����� � � ������� ����, ������ ��� �� ������, ��� � ���� ���� � ��� ������.";
		link.l1.go = "exit";
		link.l2 = "� � ��� � �������� ������������ � ����, �� ��������.";
		link.l2.go = "QHStep_1";
		NextDiag.TempNode = "QHStep_0";

    break;
    
	case "QHStep_1":
		NextDiag.TempNode = "begin_sit";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

	case "begin_sit":
		NextDiag.TempNode = "first time";
		dialog.snd = "Voice\HADI\HADI028";
		dialog.text = "��! ���, ��� � �������! ��� ��� ��-������! ������� � ������!";
		link.l1 = "����������, ����!";
		link.l1.go = "QHStep_2";
	break;

	case "QHStep_2":
		WaitDate("",0,0,0, 0, 30);
		dialog.text = LinkRandPhrase("�� ��������� ����! ����� �� ����������!",
		                             "��! ����� ���! ��... ���������!",
									 "�� ���� ��������, � �� ���� ��������� ������������!");
		link.l1 = "����� ���, ������, ����� ����� ����� �� ��������?";
		link.l1.go = "QHStep_3";
	break;
	
	case "QHStep_3":
		dialog.text = "�� ������ �������� ������... ������� ������� �����-�� ����� ������ � ������. ������������, ������ ����� ������ ����. ���� ������ �� �����, �� ����� ������ �������� ���������� ������. ����������� � ����� �� ����� ������, ���������� ������� ��� ��� ����-���.";
		link.l1 = "��, ������ ��������, ��, ��� ����.";
		link.l1.go = "exit_sit";
		NextDiag.TempNode = "First time";
		
		if (CheckNationLicence(ENGLAND)) TakeNationLicence(ENGLAND);
		sTemp = NationShortName(ENGLAND)+"TradeLicence";
		ref rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate();
		rItem.Validity = FindRussianDaysString(60);
		rItem.Validity.QtyDays = 60;
		
       // pchar.GenQuestBox.CommonStoneHouse = true;
       // pchar.GenQuestBox.CommonStoneHouse.stay = true;
        
        n = FindLocation("CommonStoneHouse");
        locations[n].private1.items.indian1 = 1;
        locations[n].private1.items.EngTradeLicence = 1;
        locations[n].private1.money = 6000;
					  
																	   

        
       // pchar.GenQuestBox.CommonStoneHouse.box1.money = 6000;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.EngTradeLicence = 1;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.indian1 = 1;

        //������ ������
       	sld = GetCharacter(NPC_GenerateCharacter("Weston", "trader_3", "man", "man", 10, ENGLAND, 1, false));
        sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
        sld.name = "������";
        sld.lastname = "������";
		sld.greeting = "Gr_bankeer";
        FantomMakeCoolFighter(sld, 7, 100, 50, "topor2", "", 10);
       	LAi_SetImmortal(sld, true);
       	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(sld, sTemp);
        LAi_SetOwnerTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "CommonStoneHouse", "barmen","stay");
        
        pchar.quest.MoneyForDieke.win_condition.l1 = "item";
        pchar.quest.MoneyForDieke.win_condition.l1.item= "EngTradeLicence";
        pchar.quest.MoneyForDieke.function = "MoneyForDieke";
        AddQuestRecord("DiekeQuest", "3");

	break;
	
	case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
	break;
	
    //�����
	
    case "MSStep_0":

        dialog.text = "����� ��������!";
    	link.l1 = "";
        link.l1.go = "Exit";

    break;
    
    case "MSStep_1":

        dialog.text = "��� ������� ��?";
    	link.l1 = "��� ��� ���.";
        link.l1.go = "MSStep_2";
       	link.l2 = "�� ������.";
        link.l2.go = "MSStep_3";
       	link.l3 = "�� ������, ��� � ���� ���������.";
        link.l3.go = "MSStep_4";

    break;
    
    case "MSStep_2":

        dialog.text = "���? � ��� ��?! ����� �����, ��������� ����������!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_3":

        dialog.text = "������... ��. ����� �������. ��� ���������?";
    	link.l1 = "� ��� ������ ������, ��� �� ���������� ��� �������.";
        link.l1.go = "MSStep_5";
       	link.l2 = "���, ��� ����� ���� �������� �����.";
        link.l2.go = "MSStep_6";

    break;
    
    case "MSStep_4":

        dialog.text = "��... ���?! � �� ��� �� ����� ����, ����! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_5":

        dialog.text = "� ��� � ����! ��� ������� ������ �� ������! ��� ���������� ��� ���� ��� ��� ��� �����?";
    	link.l1 = "��� �������������� �����, ���������� ����������.";
        link.l1.go = "MSStep_7";
       	link.l2 = "��� �������� �������� � ����������� ���-������ � ����.";
        link.l2.go = "MSStep_8";

    break;
    
    case "MSStep_6":

        dialog.text = "�����? �� �����������!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_7":
    
        dialog.text = "����������? (�������) �����, ���� � ���������������! ��� � �������!";
    	link.l1 = "...";
        link.l1.go = "exit";
        
    break;
    
    case "MSStep_8":

        dialog.text = "������ ��� �� ������ ����. ��� ��� ������ � �����?";
    	link.l1 = "''����� ������'' �������������� - ��� ������ �� ���.";
        link.l1.go = "MSStep_9";
       	link.l2 = "��� ���������� � ����� ����� ����� �������.";
        link.l2.go = "MSStep_10";
       	link.l3 = "��� ���� ����� �������� �����, ������ �� ������������.";
        link.l3.go = "MSStep_11";

    break;
    
    case "MSStep_9":

        dialog.text = "��... �������? ��... �� �����! ��������� ��! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_10":

        dialog.text = "�������... ��������? �� ������! ����������. ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_11":

        dialog.text = "�����, � ������, ��� ����� �� ������. �����, �� ������ ���������, ������. � ��� ��... ��� ���?";
    	link.l1 = "�������.";
        link.l1.go = "MSStep_12";
       	link.l2 = "������.";
        link.l2.go = "MSStep_13";
       	link.l3 = "�������� �� ��������.";
        link.l3.go = "MSStep_14";

    break;
    
    case "MSStep_12":

        dialog.text = "�������� �������... �����, ��� ��� ��������� ����. ������ �����.";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_13":

        dialog.text = "������? (������) � �� ������ ���������. �������� � �������� �������!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;
    
    case "MSStep_14":

        dialog.text = "������� ���� ������. ������� ���, ��� � ������� ����� �������.";
    	link.l1 = "...";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, 1000);
        AddCharacterExpToSkill(pchar, "Sneak", 80);
        AddCharacterExpToSkill(pchar, "Fortune", 30);
    break;
    
    case "FStep_1":

        dialog.text = "��-�... �������, �������, ������ �. ��� � �����, � ���������, � ������ ���� � ��� ���, ���... �������, �������.";
        if(makeint(Pchar.money) >=4 )
        {
            link.l1 = "��� ��, ������� ��� �������� ������� ������������� ������!";
            link.l1.go = "FStep_1_2";
        }
       	link.l2 = "��� �������, ����������... ���.";
        link.l2.go = "FStep_1_3";

    break;
    
   	case "FStep_1_2":
		NextDiag.TempNode = "FStep_2";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;
	
	case "FStep_1_3":
		NextDiag.TempNode = "FStep_3";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

    
    case "FStep_2":

        AddMoneyToCharacter(pchar, -2);
        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "�� ���������� ����, ���� ������! �� ��� � ������!";
    	link.l1 = "�� ������� ������! (��������� ���������� ������ � �����) ��� ����� �� ���� �����������, ����?";
        link.l1.go = "FStep_4";

    break;
    
    case "FStep_3":

        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "� ��� ���� �� ��������? ������, �� � ������ ����� �� ���� ����������!";
    	link.l1 = "��������� ���� ������ ���, ��� ���� ���... � ���� �����... ����.";
        link.l1.go = "FStep_5";
		  

    break;
    
    case "FStep_4":

        AddMoneyToCharacter(pchar, -2);
        dialog.text = "��� �� ������ ������� ���, ����. �� ������ �������... �� ������ ������ �� ����, ����� ���...";
    	link.l1 = "������ ������ �� ����? �����, ������ ��� �� �����!";
        link.l1.go = "FStep_6";

    break;
    
    case "FStep_5":

        dialog.text = "���? ��� ����?! ���� ����� �����, ��������! � ����� ���������� �����... ���� ����������� �� ������ �� ���� - ������� ���������!";
    	link.l1 = "�����... � ���� ����� �����, ����� �����... ��� ��� ����, � ���� ���. � ����� ������ ����� - ������������� ��� ����!";
        link.l1.go = "FStep_7";

    break;
    
    case "FStep_6":

        dialog.text = "������... � ��� �����... ����� �����... ���...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "��? ��� �� �����?!";
        link.l2.go = "FStep_Fail";

    break;
    
    case "FStep_7":

        dialog.text = "�� ������ �� ������! � ���� �������� ����, ��� ���... ������ ���...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "��? ��� �� �����?!";
        link.l2.go = "FStep_Fail";

    break;
    
    case "FStep_8":

        Pchar.questTemp.CapBloodLine.fishplace = "��� ������ �����.";
        dialog.text = "...��� ������ �����. "+Pchar.questTemp.CapBloodLine.fishplace;
    	link.l1 = "����������!.. �� ��� ��� ����.";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";
        AddQuestRecord("FishermanQuest", "2");

    break;
    
    case "FStep_Fail":

        dialog.text = "�� ��... ����� �����, ������� ��������!..";
    	link.l1 = "�� ���� ���� ������� ������ ������!";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";

    break;
    
    case "QSTStep_0":

        dialog.text = "��� �� ����� ������? ��� ��� ����� ������, � ��������! ��������, � �� ��������� ���� � ������ ������� � �������� �� ��� � ������� � �����!";
    	link.l1 = "��...";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
   		CloseQuestHeader("UsurerQuest");

    break;
    
    case "QSTStep_1":

        dialog.text = "�-�-�... �� �������? � ��� ������, ��� ����?..";
    	link.l1 = "�������, ���! ��... ���� �� ����� ��� ���� ����, ��...";
        link.l1.go = "QSTStep_3";

    break;
    
    
    case "QSTStep_2":

        dialog.text = "� ��� �� ��������? � �� ���� �������� ����������!.. �... ���������!";
    	link.l1 = "����� ��� ������, � � ������� ����������� �����, ��� �� ����������� ������ ��, � ���� ������.";
        link.l1.go = "QSTStep_6";

    break;
    
    case "QSTStep_3":

        dialog.text = "� �����... �������. �����. ���, ����� �� �� ������ ��� ����?";
    	link.l1 = "���� �����, ���� ���... ��� �� ����� �� �������? �����, ����� �����?";
        link.l1.go = "QSTStep_4";

    break;
    
    case "QSTStep_4":

        dialog.text = "���?!";
    	link.l1 = "�� ������ ����, ������! ��-�� ���� � ������� �����!.. �� ������!";
        link.l1.go = "QSTStep_5";

    break;
    
    case "QSTStep_5":
    
        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 55000);
        ChangeCharacterReputation(PChar, -10);
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        dialog.text = "���, �������... ������... � ���� ���� 55 000!.. ������� ���!";
    	link.l1 = "�������� ����������, ������� ����.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "3");

    break;
    
    case "QSTStep_6":
    
        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 30000);
        dialog.text = "��... �����. ���, ������, �������, ����! ";
    	link.l1 = "�������� ����������, ������� ����.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "4");

    break;
    
    //��� �������
    
    case "JSTStep_0":

        dialog.text = "����������, ����������. �� ����� �� ����? ���� ��� - ���������.";
    	link.l1 = "�� �����-�� �������... � �� ��� �����? �� ������, ����� �������� ��� ���������.";
        link.l1.go = "JSTStep_1";

    break;
    
    case "JSTStep_1":

        dialog.text = "����� ����... ��� ������, ��� �� �� �������, �, ���� ���?";
    	link.l1 = "�� ���� ����� ���� ����� ������. ����� ���������... �� �����? ��� ������� ���?";
        link.l1.go = "JSTStep_2";

    break;
    
    case "JSTStep_2":

        dialog.text = "�� ����������� �������������! ������� �� ������� � �������� ������� �������?";
    	link.l1 = "� ������ ��� �������?";
        link.l1.go = "JSTStep_3";

    break;
    
    case "JSTStep_3":

        dialog.text = "��, �������, � �������� ���� ������� ������ ����� ��������������. ����, ����� �������������! ������� ������� �������, �� �� - ����������� ���! �������� �������������� � �����! �������� �� ���� ���� ����� �� �������� �����, ��...";
    	link.l1 = "��� �� ����� ���������, ������ - ��� ��, �������� �������������� � ������-������, ����� �������?";
        link.l1.go = "JSTStep_4";
    break;

    case "JSTStep_4":

        dialog.text = "�? ��� ����� �����... ��-�, ��, ������� - �� ��, ��� � ��! ��, ������! ����� ��� �� ���� ��������?";
    	link.l1 = "������? ��� ������ ��� ��������������?";
        link.l1.go = "JSTStep_6";

    break;
    
    case "JSTStep_6":

        dialog.text = "����� ��������, ���� �� �� ������ ������, ���? ����� ��� �������� ����������� � ���� �������, � ���� �����, ��� ������ �������, �� ������ ������ ��������� ����� ��������, �� ������ ��?";
    	link.l1 = "�� �� ��������� ��������� � ����������? ������� �����, � �� ������ ������. ����� - ��� ������ ����� ����� ������, ������ ����� ����������, ��� ���, �������, �� ��� ����.";
        link.l1.go = "JSTStep_7";

    break;

    case "JSTStep_7":

        dialog.text = "��-��, �� �������, ������! �������, ��������� �������� � �������� - � ��� ���, �� ������ �����������, �������� ����������� ��������... �, ���� �� �������� ���������� ���� ����������, ����� �� ��� ����� ������� � ���. ��, ������ ���, � ���� ���������� ������������?";
    	link.l1 = "���-�� ������������ ���, ��� ��� ������������ ����� ������ �� �����������...";
        link.l1.go = "JSTStep_8";

    break;
    
    case "JSTStep_8":

        dialog.text = "�� ���, �� ����� �� '��'. ��� ������ ���� - �� ��������? ������� ���� ������ ��� �������� ������� �� ����, ��� ������ ���� ����� � �������?";
    	link.l1 = "�� ����������� ���������� � ��������� ���. � � ������ ����� � ��...";
        link.l1.go = "JSTStep_9";

    break;

    case "JSTStep_9":

        dialog.text = "������� ����������� - ����� ��� ����, ��� ���������� ��������� ���� � �����-����� �� ��� ������, � � ��� ���� �������. �� �����? �����, � ����� ��������� �� ���� ���� ������ �� �����?";
    	link.l1 = "��... ���������� �����������. �� � �������� �� �� ����. �� �����.";
        link.l1.go = "JSTStep_10";
       	link.l2 = "������, ��� �� ��... �������� ������ ���������� �������������� ��������! � ���� ���������� �� �������.";
        link.l2.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;
        
    break;
    
    case "JSTStep_10":

        dialog.text = "���� �������, ��� ����� - ������� ����. ��, �� ���� - ��� �������, ���� ������... � ��� ��... ����� - � ��� �����... ���... ����� �����, ��� � �������� ���� ����!";
    	link.l1 = "���� ����?.. ������. �����, � ���-������ ��������.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("PirateQuest", "1");
        Pchar.questTemp.CapBloodLine.ShipForJack = true;
       	sld = characterFromID("Bridgetown_trader");
   	    LAi_RemoveLoginTime(sld);

    break;
    
    case "JSTStep_11":

        dialog.text = "��� ���� ������, ��� ����� ����. ����, ������� �� ���� ������� ���... �� ������, � ������� �� ��������������?";
    	link.l1 = "������ '�������� ��������' �������� ����� ������� ��� ���.";
        link.l1.go = "JSTStep_12";

    break;

    case "JSTStep_12":

        dialog.text = "��, ��� � ���� ������� - ������ � ������� ������� ����, �...";
    	link.l1 = "������� ������, �������.";
        link.l1.go = "JSTStep_13";

    break;

    case "JSTStep_13":

        dialog.text = "�������-�������! � ������ ����� �������� ���� ���� ��������� ��������������� � ���������� �������� ����� ������������ ����, ���� �������� ���������� ������ ��� ���������� ������, ������� ������...";
    	link.l1 = "������� ������! � ���... ��� ����� ����.";
        link.l1.go = "JSTStep_14";

    break;
    
    case "JSTStep_14":

        dialog.text = "���� ��! ���, ��� ���� ������!..";
    	link.l1 = "���������.";
        link.l1.go = "Exit";
        AddMoneyToCharacter(pchar, 1500);
        AddQuestRecord("PirateQuest", "5");
        CloseQuestHeader("PirateQuest");
        NextDiag.TempNode = "JSTStep_15";
        NPChar.lifeDay = 0;

    break;
    
    case "JSTStep_15":

        dialog.text = "� ���������� ����... ����. ��� - ������� ���� ������ �� ���-������ ��������.";
    	link.l1 = "� ���� �����... ��.";
        link.l1.go = "Exit";
        NextDiag.TempNode = "JSTStep_15";

    break;
    
    //���� ������
    
    case "MNStep_0":

        dialog.text = "���� ������, ������� ������� '�������� ��������', � ����� �������. ��� ���� ������?";
    	link.l1 = "������ ����, ��� ��� ����� ����. ���� � ������� ��� �� ���������, �������? ������ �����, ��... ����� ����� ����� ��������� �� ����� �����, � �� ����� ������������ � ����� �������� ��������.";
        link.l1.go = "MNStep_1";

    break;

    case "MNStep_1":

        dialog.text = "���� � ������ ��� ������ �����, ������ ����?";
    	link.l1 = "�������. ��� �����... �... � ����� �� - ���, �� ����� ����, ���...";
        link.l1.go = "MNStep_2";
       	link.l2 = "�������. ��� ��� ������� �������, ������?..";
        link.l2.go = "MNStep_3";
       	link.l3 = "���.";
        link.l3.go = "MNStep_4";

    break;

    case "MNStep_2":

        dialog.text = "�������? ��� ����... � ������ �������, ���������� � ����� �����?";
    	link.l1 = "� ������ ���? �����-����� ������ ��������������� ����. ������ ��, ������� ���� �� �����������?";
        link.l1.go = "MNStep_5";

    break;
    
    case "MNStep_3":

        dialog.text = "�... ������, ��. ��� �, � ��� ��� �� �����. ������� �� ��������� �����, ������ ����.";
    	link.l1 = "��������� - ������ ������������. ����� ����������. �������, �� �� ��������� � ����� �������.";
        link.l1.go = "MNStep_Exit";

    break;
    
    
    case "MNStep_4":

        dialog.text = "���? ��� � ���� ����������� ����� ���������, ���� ���� �� ���� ��� �����?!";
    	link.l1 = "������ ������. ������ ���, ��� ����� ������ ������... ��, ������ ��� - ������ ������, �������... ������� ���� ��� ��� ������ �������, ���� �� ����������� �������� �������.";
        link.l1.go = "MNStep_6";

    break;
    
    case "MNStep_5":

        dialog.text = "������, � ������ ���... �. ��������� ���� ������� ����������, ��� '�������� ��������' ����� � �������.";
    	link.l1 = "���������.";
        link.l1.go = "MNStep_Exit";
        AddCharacterExpToSkill(pchar, "Sneak", 50);

    break;
    
    case "MNStep_6":

        dialog.text = "����� �� ��� � ��������! �� ����� - ��� ���� ������, �� �����.";
    	link.l1 = "������ ������, � ������ ����������. ����� �������, �������.";
        link.l1.go = "MNStep_Exit";

    break;
    
   	case "MNStep_Exit":
   	
            AddQuestRecord("PirateQuest", "4");
            sld = characterFromID("Jack");
            sld.Dialog.CurrentNode = "JSTStep_11";
            LAi_SetSitTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit4");
            LAi_SetActorType(npchar);
 			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
	break;
	

    //�������� ��������

    case "ASStep_0":

        dialog.text = "�� ������ ����? ��� ��?!";
    	link.l1 = "� ����� ����, �-�-�... ������� ����. �� ������ �����, ���� � ��������� ��� ���� ���������? � ��� �����, ���� ������, ����������?";
        link.l1.go = "ASStep_1";
        ChangeCharacterReputation(pchar, 5);

    break;
    
    case "ASStep_1":

        dialog.text = "�������... ���... ��� ������� �������, �������� ������� ��������� ��� �������� ����� ��� ����� ������ � ���� �����, �������� ��������� �������. ��� �������� � ������ �������� ����������� ���������, ���, �� �������� ����������, �� ����������� ����� � ����� � ����������� ����� � ���� �������� ������ �� �������� �����...";
    	link.l1 = "� ������, ��� � �������, ������ ����� ������ ������ �����?";
        link.l1.go = "ASStep_2";

    break;
    
    case "ASStep_2":

        dialog.text = "��, � ������ ������ ��� �������� ������ � ������ ��������� �������� ����� ��������� ����������.";
    	link.l1 = "��� ��� � ���������� ������������� �������������� ������. ���� ���� ���� ������ �����, ��� �� ����� ����� ������! � �� - ������ � ��� � ���������, �� ��� ��� ���� ������� �� ������� �����.";
        Pchar.questTemp.CapBloodLine.SpainInBridgetown = true;
        Pchar.questTemp.sLocator = "gate1_back";
        Pchar.questTemp.iTime = -1;
        link.l1.go = "Exit_RunAway";
        AddQuestRecord("EscapeFormBarbados", "3");

    break;


	}
}

