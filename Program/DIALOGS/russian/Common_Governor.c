// boal 25/04/04 ����� ������ Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	int Matheria1 = 4000;//����
	int Matheria2 = 3000;//�������
	int Matheria3 = 2000;//������
	int BuildPrice = 3000000;

    // ����� ������� �� ������� <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// ����� �������
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "arest":
			dialog.text = "������! ����� �"+ GetSexPhrase("��","�") +"!";
			link.l1 = "��, �� ���! ������ ��� �� ���� �� ��������!";
		    link.l1.go = "fight";	
		break; 
		
		case "Patent_Doubt":
			dialog.text = "������ �������... ��� ������ �� ��� �������� �� ���� ���� ��������. ����� ����������� ������� ���� ���, ������ ������ �� ����� ���������� ������� ������� � ���������� ����� ������. ��� � ����, � ������� ��� ������, � �����������. ������ �� ����������� ���� ������ �� ����.";
			link.l1 = "�� �� ���������, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Patent_Give";
			link.l2 = "��! ��������! ��� ���� ���� �����, � �� ���� ����� ������ ������ � ����� ��������� ������������.";
			link.l2.go = "arest_3";
		break;
		case "Patent_Give":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
            pchar.PatentPrice = 0;
			dialog.text = "����������, ������� �� ���������� ��������������. ��������� �� ��� ����� �� �������. � ���� ����� ������� ������ ������� ��� ���.";
			link.l1 = "�������. ��������, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("�� ������� ������� � �������-�����������?! ������ ���...", "��� ��� ����������� ���������, ����� �� ��� �������� ����?! ��� �����������...", "�� ��, ��� ������ ��������� �����, ��� "+ GetSexPhrase("�����-�� ����������","�����-�� �����������") +" ������ � ���� ����������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��� ������� ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","��������") +"!", ""+ GetSexPhrase("�������","�������") +" ������, ��� �� ���� ����������! ������!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("�������� ���� ���� �����...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, ��������, � �� �� ����� ���� ������� ����!", "��� ��� � ���� �����, ��������: ���� ����, � ������ ����..."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 15)
            {
                dialog.text = "�! ��� ������! ��� �� ���"+ GetSexPhrase("","�") +" " + GetFullName(pchar) + ". �� ��� ��� ������� �������� ��������� �� ��������, ����� ��� ������� ��� ����. � ������, ��� ��� ������ ��� � ����������� �����.";
                if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) == 100 && !isMainCharacterPatented())
				{
				link.l3 = "�� ������ �� ��� � ������"+ GetSexPhrase("��","��") +" ������ ������, � ������ ����������� ����� ������ � ����� �������� ����� ������� � �������� ��������. ��������� ����� ���, ����� � ������: ������� ��� ������ � ��� ���� ����� ������ �����.";
				link.l3.go = "Patent_Doubt";
				}
				link.l2 = "�... �������, ��� ����.";
				link.l2.go = "arest";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "���� � ����������! �������!!";
				link.l1 = "�-���, ������!";
				link.l1.go = "fight"; 
				break;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "� ������, ��� �� ����� ���������� ������� ���������. ���� ����� " + GetFullName(npchar) +
                              ". � �������-���������� ������� " + NationNameGenitive(sti(NPChar.nation))+ ", ��������� ������ " + NationKingsName(npchar)+
                              " � ���� �����. � ������ ������������� �������� ���� ������ ������, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "��� ��� " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("�, ��� ����� ��? �� ������ ������� ��� ����������� �������-���������� " + NationNameGenitive(sti(NPChar.nation))+ " �� ���� ���?",
                              "����� ��������� ���� �� ������ ��������������� ���? ��� ��� ������, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "����� ���������� � ���� �� ����� ����.";
				link.l2.go = "quests"; // ���� �����
				link.l10 = "����� ��������, �� ���� ���� ����.";
				link.l10.go = "exit";
				
				if (GetQuestPastDayParam("pchar.questTemp.buildSoley") >= 60 && NPchar.Nation == FRANCE && !CheckAttribute(npchar, "quest.Gave_Ship"))
				{
				
				Link.l15 = "�� ���, ������� �����?";
				link.l15.go = "get_ship";
				}
				
				
				/*
				����� � ����� ������� ������� ������: "�, ������ �� ����� �������, ��� �������� ������ ���� ����� �������, ���������� ��������� ������ ������� - ������ ��".
				� ����� ������, ���� ������� ����� �������� ������� �������, �� ������ ������� �� ����� ������� � ������� �����, ���������� ������� ��� �������".
				�� ��������� ������� - ��������� ��� �������: �����, ��������, ��, ��, � ��� ��������� ������� � ������� �����������. ���� ��������� 3 ���. ����� ������������� 1 �����.
				��, �� �� ���� � ��� �������� ��� ������� �����.
				*/
			}
		break;
		
		case "build_ship":
			dialog.Text = "��� �������� ����! ������ � ����� ��� �������� ��� �� ������������... ���� ������, �� ������ �������� ����������� �������� � �������� ������ ��������� � �������. � ��� ���������.";		
			Link.l1 = "� " + GetSexPhrase("��������","��������")+ ". ��� � � ����� ������ ����� ����� ���������?";
			Link.l1.go = "build_ship_1"
			Link.l2 = "��������, �� �� ����� � ���� ��� �� �������, �� �����.";
			Link.l2.go = "exit";
		break;
		
		case "build_ship_1":
			dialog.Text = "����, ��� ��������� ������������ �������� �����������: "+Matheria2+" ������ �������� ������, "+Matheria3+" ������� ������, "+Matheria1+" �����, ������ ��������� ����� �������� � ����� �� ���� ������ ���������� � ����� ��������. ������ �� ������ ��������� "+BuildPrice+" ������� ������ �� �� �������, � ����� ����� � ���� ������ ���� ������� ���� � ������ ��������������� ������������.";	
			
			if(makeint(Pchar.money) >= BuildPrice)
			{
				Link.l1 = "������������, ��� ������. ����� ������� ��� ��� ���������.";
				Link.l1.go = "build_ship_2"
			}
			Link.l2 = "��������, ������� ��������...";
			Link.l2.go = "exit";
		break;
		
		case "build_ship_2":
			AddMoneyToCharacter(Pchar, -BuildPrice);
			dialog.Text = "���� � �����������.";
			npchar.quest.answer_1 = "true";	

			NPChar.Tuning.Matherial1 = Matheria1; 
			NPChar.Tuning.Matherial2 = Matheria2; 
			NPChar.Tuning.Matherial3 = Matheria3;
			NextDiag.TempNode = "check_material";
			Link.l2 = "�� ��������.";
			Link.l2.go = "exit";
		break;
				
		case "check_material":
			 
				dialog.Text = "������ ����. ������"+ GetSexPhrase("","��") +", ��� � ������?";

				NextDiag.TempNode = "check_material";

				
			    Link.l1 = "��. ���-��� ������� �������.";
			    Link.l1.go = "check_material_1";
			    Link.l2 = "���. ��� �������.";
			    Link.l2.go = "Exit";
		break;
		
		case "check_material_1":
			
			checkSoleyMatherial(Pchar, NPChar, GOOD_SILK, GOOD_MAHOGANY, GOOD_EBONY);
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				
                dialog.text = "�� ��� ��������. �������! ������������� ����� ���� �������, ����� � ���� ������� ��������� ��� ����� ���������...";
				SaveCurrentQuestDateParam("pchar.questTemp.buildSoley");
				NextDiag.TempNode = "First time";
			    link.l1 = "���.";
			    link.l1.go = "exit";
				
			}
			else
			{
				dialog.Text = "���� �������� ��������:" + ", �������� ������ - "+ sti(NPChar.Tuning.Matherial2) + ", ������� ������ - "+ sti(NPChar.Tuning.Matherial3) + ", ����� - "+ sti(NPChar.Tuning.Matherial1)".";
				link.l1 = "������.";
				link.l1.go = "Exit";
			}
		break;
		
		case "get_ship":
			dialog.text = "� ��� ��! ������ �������� ��� � �����. �� ��� ������ ������� ���������� ��� �� ����� ��������� �������. ������ ����������, ��� ������� ��� �������, ���� ������� �������� �� ���� ������� ����� �����. � ������� � �������� � ������� ��� � ������ ��������� �������, ������� �� ������� ��� ����������.";
			NextDiag.TempNode = "First time";
			npchar.quest.Gave_Ship = "true";	
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain1", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Name = "����� ������";
			sld.Ship.Type = GenerateShipExt(SHIP_SOLEYRU, true, sld);
			ResetShipCannonsDamages(sld);
			SetBaseShipData(sld);			
			SetCrewQuantityFull(sld);
			SetShipSkill(sld, 50, 60, 70, 55, 95, 55, 50, 55, 50);
			Fantom_SetBalls(sld, "pirate");	
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);	
			
			sld.Dialog.TempNode = "hired";
			sld.Dialog.FileName = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			SetBaseShipData(sld);
			sld.CompanionEnemyEnable = false;
			SetCompanionIndex(pchar, -1, sti(sld.index));
			
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			//AddDialogExitQuestFunction("LandEnc_OfficerHired");
			

			link.l1 = "���������. ���������� ��� �������.";
			link.l1.go = "Exit";
		break;	
		
		case "node_1":
			dialog.text = "��� ����� ������� ��������� ��� ������ ���� � ��������� ���� �� ������ ��������������� ���?";
			link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "����� ���������� � ���� �� ����� ����.";
			link.l2.go = "quests";
			link.l10 = "��� ������ ����� ���������� � ������ �����, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "� ����� ������, � ������� ��� �������� ��� ������� � �� ������ ��� ��������.";
			link.l1 = "��, ��, �������, ��������, ��� ����������"+ GetSexPhrase("","�") +" ���.";
			link.l1.go = "exit";
		break;
		
		case "work":
            if (!CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) || !CheckAttribute(pchar, "EquipedPatentId"))
			{
    			dialog.text = "� ��� ���������� �� ����, " + GetAddress_Form(NPChar) + ". �������� ��� �������. � ���� ���� ������ � ������, ���������� �� ������ " + NationKingsName(npchar) + ".";
    			link.l1 = "�������� �� ������������. ����� � ���� ����� ������ "+NationNameGenitive(sti(NPChar.nation))+", � �������.";
    			link.l1.go = "exit";
			}
			else
			{// ���� �������
                // ������ ��������
                if (isReadyToNextTitle(sti(NPChar.nation)))
                {
                    Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
                    Items[sti(pchar.EquipedPatentId)].TitulCur = sti(Items[sti(pchar.EquipedPatentId)].TitulCur) + 1;

                    dialog.text = "� ������ ���������� ���"+ ", " + GetAddress_Form(NPChar)+". �������� � ����� ��������� �� ������ ��������� � ���������� " + NationKingsName(npchar) +
                                ". ��� ��������� ������ " + GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) +
                                " ����� " + NationNameGenitive(sti(NPChar.nation)) +".";
        			link.l1 = "�������! ������ � ������ � ������ ������� "+NationKingsCrown(npchar) + ".";
        			link.l1.go = "exit";
        			break
                }
                // ���� �������
                dialog.text = LinkRandPhrase("�� ������ ������� �� ���, "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+"?",
                                             "� ������ ���, " + GetAddress_Form(NPChar)+".",
                                             "��������, � ���� ��������.");

                //GetAddress_Form(NPChar)+", � ���, ��� "+ GetSexPhrase("����� ������","����� ������") +" "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+" �� ������ " + NationKingsName(npchar) + ".";
				if (pchar.questTemp.NationQuest == "")
                {
	    			if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8" || pchar.questTemp.LSC == "over")
					{
						link.l1 = "���� �� ����� ������ ��� �������������� �������?";
	    				link.l1.go = "work_1";
						if (!bWorldAlivePause && pchar.questTemp.State == "") //eddy. ������, ���� �� �������� �������.
						{
							link.l1.go = "onlyGenWork_Alter";
						}
					}
					else
					{
						link.l1 = "���� �� ����� ������ ��� �������������� �������?";
	    				link.l1.go = "onlyGenWork_2";
					}
    			}
    			else
    			{
    			    if (pchar.questTemp.NationQuest == NPChar.nation)
	                {
		    			link.l1 = RandPhraseSimple("� ������"+ GetSexPhrase("","�") +" �� ����, �������� ���������� � ������ �����������.", "�� ������ ����� �������...");
		    			link.l1.go = "work_1";
	    			}
	    			else
	    			{// �������� - ���
	    			    link.l1 = "���� �� ����� ������ ��� �������������� �������?";
	    				link.l1.go = "onlyGenWork_1";
	    			}
    			}

                // ����� ������ -->
				if (isHeroOwnCity(false))
				{
				    Link.l2 = "� ���� ��������� ����������� ���� ��������� ��� ���� "+ XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen") +".";
					Link.l2.go = "colony_capture";
				}
                // ����� ������ <--
                link.l9 = RandPhraseSimple("��������, � ����� �����.",
                                           "������ ����������, "+GetAddress_FormToNPC(NPChar)+". ������ ����� ����������.");
    			link.l9.go = "exit";
			}
		break;
		
		case "onlyGenWork_1":
			dialog.text = "��... � ������, ��� �� ��������� ������ ������� ��� "+ NationNameGenitive(sti(pchar.questTemp.NationQuest)) +", ������� ������ ���������� � ��� �������� ��� �� �����.";
			link.l1 = "����� ����.";
			link.l1.go = "exit";
		break;

		case "onlyGenWork_2":
			dialog.text = "����� �����, ��� �� ����� ����� ������� � ��������� ���������� ��������. ������� �� �����, ��� � ����� �������� ��� ������ �� ����� " + NationNameGenitive(sti(npchar.nation)) + ".";
			link.l1 = "��... �� ��� ��, ����� ����.";
			link.l1.go = "exit";
		break;

		case "onlyGenWork_Alter":
   			dialog.text = "� ��������� ��� ��� � � ������� ��� ����, ����������� � ������������������ ������� ��� ������� � ���� ������ ���.";
			link.l1 = "��� ��, ����� �����.";
			link.l1.go = "exit";
		break;

		/////������� �� ����������� �������.
		case "colony_capture":
   			dialog.text = "� ����� ������ ���� ����?";
   			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id);
					Link.(attrLoc).go = "CityGive_" + i;
				}
			}
			link.l99 = "� "+ GetSexPhrase("������","��������") +", ���� ��� � ������.";
			link.l99.go = "exit";
		break;
		
        case "ColonyGive":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            colony_money = TWN_CityCost(colonies[i].id) / 50;  // �� *1000 � �����
            TWN_RealeseForMoney(colonies[i].id, false);
            dialog.text = "�������� �������, "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+
                          "! ���� ������� �� ��������� ������������, �, ����������, ��� ���� �������. ��� ��� " + colony_money +
                          " ������� � �������� �������������� �� ���� ������� ����� "+NationNameAblative(sti(NPChar.nation))+
                          ". � ������ ����� ���� ��������, � ���� ����� ����� ���.";
            link.l1 = "� ����� ������, " + GetAddress_FormToNPC(NPChar) + ", �� ���� ��� ������ �����������. ����� ����������.";
            link.l1.go = "exit";

            ReOpenQuestHeader("Gen_CityCapture");
		    AddQuestRecord("Gen_CityCapture", "t8");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("c�","���"));
			AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(colonies[i].id));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen"));
		
            AddMoneyToCharacter(PChar, colony_money);
            AddTitleNextRate(sti(NPChar.nation), 1);  // ������� ������
            ChangeCharacterNationReputation(Pchar, sti(NPChar.nation), 10);
            PChar.questTemp.DontNullDeposit = true;    // ���� �� ������ ����������
            SetCaptureTownByNation(colonies[i].id, sti(NPChar.nation));
        break;
		
		//*************************** ����� "������������� ������ "�����"" **********************        
        case "Andre_Abel_Quest_Hol_Gov_Node_1":
			//if (GetCityNameByIsland(Pchar.curIslandId) == "Villemstad")
			if (pchar.location == "Villemstad_townhall")
			{
			dialog.text = "� ��� ������, �������.";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" �� ����� ������� � ���������� �������� ��� ��� ��� ������...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_2";
			TakeItemFromCharacter(PChar, "letter_1");
			Log_TestInfo("������ ������ �������-����������� �������.");
			PChar.Quest.Andre_Abel_Quest_Curasao_10Days_Left.over = "yes";
			}
			else
			{
			dialog.text = "��������� ���� �� ������ ��������������� ���? ��� ��� ������, " +GetAddress_Form(NPChar)+"?";
			link.l1 = "��� ������ ����� ���������� � ������ �����, "+GetAddress_FormToNPC(NPChar)".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_Quest_Hol_Gov_Node_1";
			}
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_2":
			dialog.text = "��... �� �������? ������... ��� �, ������� ���� ������ �� ����� �������.";
			link.l1 = "����� ���...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_3";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_3":
			dialog.text = "���?! �������� ���� �����?! ��, ���������� ������! ���� �� ���� �����, ��� �� ���� ������ ��� ��������! �������� "+ GetSexPhrase("����� ����������","��� ��������") +"!";
			link.l1 = "������! � ����� ���� "+ GetSexPhrase("���������","���������") +", � �� ���� �������� �� ���������� ������!..";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_4";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_4":
			dialog.text = "�� ������� �������, � �� "+ GetSexPhrase("����������","����������") +". ����� ����������!.. � ������� "+ GetSexPhrase("���","��") +"!";
			link.l1 = "�� ��� ����� ������ �����!!!";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
			link.l2 = "��� �, � ��������"+ GetSexPhrase("","�") +" ����������� �������! �� ��������, - ��� ������� �����, � � �� ��������"+ GetSexPhrase("","�") +" � �� ��������"+ GetSexPhrase("","�") +" ������ ��������� ������, �� ��� ���� ����� ���� �� ������������!";
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_7";
			link.l3 = "�������� �������-����������, ����� �� ����� � ������?! � ������"+ GetSexPhrase("","�") +", ��� �� ����� �� ������� ������������...";
			link.l3.go = "Andre_Abel_Quest_Hol_Gov_Node_9";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_5":
			dialog.text = "��� �� ������, "+ GetSexPhrase("��������","��������") +"! ������ "+ GetSexPhrase("���","��") +" ����������!!!";
			link.l1 = "��, ���������, ���������!..";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_6";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			LAi_SetImmortal(CharacterFromID("Andre_Abel_Quest_Officer_1"), false);
			sTemp = "hol_guard";
			LAi_group_MoveCharacter(CharacterFromID("Andre_Abel_Quest_Officer_1"), sTemp);
			LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
			QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			LAi_Group_Attack(PChar, CharacterFromID("hol_guber"));
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", "� �������, ���� � ��������� ��� ������ ������ ������ ���������");
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_7":
			//pchar.questTemp.OrionCity = GetCityNameByIsland(Pchar.curIslandId);
			dialog.text = "����� ���� ������� ��� ��� - ��� �� ��� �������... ������ "+ GetSexPhrase("���","��") +"!";
			link.l1 = "���������, ������ �� ������. � ���� ���� �������...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_8";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LocationDisableOfficersGen("Villemstad_prison",true);
			LAi_LocationDisableOfficersGen("Villemstad_fort",true);
			LAi_LocationDisableOfficersGen("Villemstad_ExitTown",true);
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto9", "Andre_Abel_Quest_In_Prison");
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_9":
			iSumm = sti(PChar.rank)*20000;
			dialog.text = "������������? ��... ��, ���� ���� ��� � �����, ������ " + iSumm + " ��������, �� � ����� ���������� ������.";
			if(sti(PChar.money) >= iSumm)
			{
				link.l1 = "�������! � �� �������"+ GetSexPhrase("","�") +", ��� ��� ����� ��������.";
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_10";
			}
			link.l2 = "���-�?! �� �� � ���� ���?! �� ����� ������ � �� ��, ��� ���� ������!.. � ���� ������� ������, ������ � ��������� �������� � ���������� � ��������!!!";
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_10":
			iSumm = sti(PChar.rank)*20000;
			AddMoneyToCharacter(PChar, -iSumm);
			dialog.text = "�� ��� � �����������. ������ ����... ������ �� ��������� ��� ������ � ��������� �����������! �� ����������� �� ����������.";
			link.l1 = "�� ����������! ��������� ����������...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_11";
		break;
			
		case "Andre_Abel_Quest_Hol_Gov_Node_11":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", "� �������, ���� � ��������� ��� �������� ������");
		break;
	}
}

void checkSoleyMatherial(ref Pchar, ref NPChar, int good1, int good2, int good3)
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
	
    amount = GetSquadronGoods(Pchar, good2) - sti(NPChar.Tuning.Matherial2);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial2);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial2);
    }
    RemoveCharacterGoods(Pchar, good2, amount);
    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;
	
		
    amount = GetSquadronGoods(Pchar, good3) - sti(NPChar.Tuning.Matherial3);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial3);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial3);
    }
    RemoveCharacterGoods(Pchar, good3, amount);
    NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;
	
}