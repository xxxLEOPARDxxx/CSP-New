// ����� - ������ �� �������

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{
	case "rumours_citizen":	
		NextDiag.CurrentNode = "rumours";
		//------------- ��������� ����� ������� --------->>>>>>>>
		//��������� ��������� �����
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.Sharp.City == npchar.city && sti(pchar.questTemp.Sharp.City.rumour))
		{
			pchar.questTemp.Sharp.City.rumour = false; //���� ���
			Dialog.Text = Sharp_choiceAction();
			link.l1 = "��, �������... ��� ��� ������?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
									"����� ��������.");
			link.l2.go = "exit";
			break;
		}
			
		//����� ������ ����� �����
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.BlueBird.City == npchar.city && pchar.questTemp.BlueBird == "returnMoney")
		{
			Dialog.Text = BlueBurd_setTradeShip();
			link.l1 = "���, �������... ��� ��� ������ � ������?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
									"����� ��������.");
			link.l2.go = "exit";
			//����� ���� � ������ ������
			pchar.questTemp.BlueBird.City = GetSharpCity();
			break;
		}
		
		if (pchar.questTemp.Slavetrader == "canTakeQuest" && rand(4) == 0)
		{
			sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
			Dialog.Text = "�������, ��� ��������� �� ������� "+ XI_ConvertString("Colony" + sld.city) +" ��� �����-�� ���������� ������ ���� ��������, �� ����������� �������� ����...";
			link.l1 = "���, �������... ��� ��� ������ � ������?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
									"����� ��������.");
			link.l2.go = "exit";
			break;
		}
		
		if(pchar.questTemp.Ascold == "canTakeQuest" && rand(3) == 0)
		{
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
			Dialog.Text = "�������, ��� ������ �������� �� ������� "+ XI_ConvertString("Colony" + sld.city) +" ���� �����-�� �������, ������� ������ �� ���� ����������...";
			link.l1 = "���, �������... ��� ��� ������ � ������?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
									"����� ��������.");
			link.l2.go = "exit";
			break;
		}
		
		//<<<<<-------- ��������� ����� ������� -----------------
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 3 )
        srum = SelectRumourEx("citizen", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" ����� ��� ����...", " ��������, ��� ��� ���������.");
            posrep2 = " � � ���, �������, ���� �����-������ �������� ��� ����� �������?";
            answ1 = RandPhraseSimple(RandSwear() + "���������� ���� �� �������������, "+GetFullName(NPChar)+".",
                                 "����� �������� ��� ���...");
            answ2 = RandPhraseSimple(RandSwear() + "��� ����� ���������! ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...",
                                 "��� ������.");
            answ3 = RandPhraseSimple("���� ������ �� ��������� �� �����. ��� ����, �� ������� �������� � ���� ���. ",
                                 "� ������� �����, ��� ��� ���-������ � ������ ���.");
            answ4 = "";
        
        }
        else
        {
            posrep1 = " � ��� ������ ����� ���-���� ����������. �� ���� �� ���������� ���-�� ���������, �� ��� �� ���� ������ � �������.";
            posrep2 = " ��� ��� �������� �������. �� ����� " + GetAddress_Form(NPChar) + " ������� ���-�� �����?";
            answ1 = RandPhraseSimple("����� ��������-�� ��� �����...",
                                 RandSwear() + "�� ������ �� ������! �����, ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...");
            answ2 = RandPhraseSimple("��������, �� ������, �����, ����� ��� �����...",
                                 "��, �� ������ �� ��� �����"+NPCharSexPhrase(NPChar, "","��")+", ��, �����, �� ������ ���-�� ���?");
            answ3 = RandPhraseSimple("�� �����, ��� ���� ���-�� ���, ����� �� ��� ��������������.",
                                 "� � ������������� ���-������ ��������, �� ���-������ � ������ ���.");
            answ4 = "";
        
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
                                                srum+posrep1,
                                                srum+posrep2,
                                                RandPhraseSimple("� ���������, ������ � ������ �� ����, ��������� ��� ����.",
                                                                    "�� ������� ���� ������ �����������, ����� ���� ��������, �� ���� ���� ����."),
                                                "block", 1, npchar, Dialog.CurrentNode);
		
		//link.l1 = RandPhraseSimple(RandSwear() + "��� ����� ���������! ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...",
        //                         "��� ������.");
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
                                 "����� ��������.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---����� ��������---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" ����� ��� ����...", " ��������, ��� ��� ���������.");
            posrep2 = " � � ���, �������, ���� �����-������ �������� ��� ����� �������?";
            answ1 = RandPhraseSimple(RandSwear() + "���������� ���� �� �������������, "+GetFullName(NPChar)+".",
"����� �������� ��� ���...");
            answ2 = RandPhraseSimple(RandSwear() + "��� ����� ���������! ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...","��� ������.");
            answ3 = RandPhraseSimple("���� ������ �� ��������� �� �����. ��� ����, �� ������� �������� � ���� ���. ","� ������� �����, ��� ��� ���-������ � ������ ���.");
            answ4 = "";
        }
        else
        {
            posrep1 = " � ��� ������ ����� ���-���� ����������. �� ���� �� ���������� ���-�� ���������, �� ��� �� ���� ������ � �������.";
            posrep2 = " ��� ��� �������� �������. �� ����� " + GetAddress_Form(NPChar) + " ������� ���-�� �����?";
            answ1 = RandPhraseSimple("����� ��������-�� ��� �����...",RandSwear() + "�� ������ �� ������! �����, ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...");
            answ2 = RandPhraseSimple("��������, �� ������, �����, ����� ��� �����...","��, �� ������ �� ��� �����"+NPCharSexPhrase(NPChar, "","��")+", ��, �����, �� ������ ���-�� ���?");
            answ3 = RandPhraseSimple("�� �����, ��� ���� ���-�� ���, ����� �� ��� ��������������.","� � ������������� ���-������ ��������, �� ���-������ � ������ ���.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("� ���������, ������ � ������ �� ����, ��������� ��� ����.","�� ������� ���� ������ �����������, ����� ���� ��������, �� ���� ���� ����."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.","����� ��������.");
		link.l2.go = "exit";
	break;
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		Dialog.Text = LinkRandPhrase("��... �-��! ","��, ����� ���! ","�-��... ")+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "�� ��� ���� ������ ��� ��������...",
                                 "������. ����� ��� �� �����.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
                                 "��, ���������� ���. �����, ��� ��� ����, ������ ��������.");
		link.l2.go = "exit_sit";
		if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && npchar.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
		{
			dialog.text = "�������������, ���� ������ �� ������, �����, ��������� ���� ������ � �� �������� � ����� ��� � �����! ��, �������, ������ ����� ������?! � ����� ������� - ���������. �� ���������, � � ��� ���� �������! �! ������?! �, �� ��������, ������ �� ������, � �� ��� ��� �����. ����� ����! �����, �� ������ ���?..";
			link.l1 = "��, ��� �����...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "3");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirstUsurer";
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && npchar.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
		{
			dialog.text = "������ �� ���, ���� ���� �����, �����, ��� ���� ��� �� ������. ����� ���, ��� ��� ������... ���� ������. ���������, ��� �� ����� �������� ����������, ��-��-��. ��� ��� � ����, ��������� ����������, ����� �� ������� � ������, � ��������� �������� � ��������-�� �����...";
			link.l1 = "�� ��, ��� ���������� - ����� �������.";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "5");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecondUsurer";
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && npchar.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
		{
			dialog.text = "��� ��� ����� ��� ����� ����� ����! ���� ������ ������ ��������. ������, ���� �������, ������ ��������� �����. ����, ����! � ���� ������. ���� ��������, ���. �� ���� - ����� ����������, ���� � ������� ������� ��������. ������!";
			link.l1 = "� ���! �����...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "7");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			pchar.questTemp.piratesLine = "PPL5Hunter_toThirdUsurer";
		}
		//-->������������
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(����) ������� ��� �����-������ ����������� ���. �� ������ - ������� � ���-������� ����, ������� �����-��, � �������� �����. ������ ����� ��-�����, � ������ - ������... ��� �����, ����"+ GetSexPhrase("�","���") +", �����������. ��� ��� ���, � ����?";
            link.l1 = "�� � ���� ��� ��� ��, ��� � ������ - ���� � ������. �� ��� ����� �����, �� ������ ��, ���� ���� ��� ��������, ������� ��� ������� ������ �������? ������� ������� ��� �����.";
            link.l1.go = "Jamaica_ratH_1";
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(����) � ���-�����-���� ����� �� ���� �����-���� ���, � ��-� ���-� ������ ������ � �����-�� �����... ��, �������, ����"+ GetSexPhrase("�","���") +"! � ������ ����� �� �����, ������� ��� ������� �� � ����.";
            link.l1 = "��������, ��������! ��, � ��� ��� � ����, ��� ����������� �����?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
        }
		//<--������������
		
		//���, �����
		if(CheckAttribute(pchar, "questTemp.Headhunter"))
		{
    		if (pchar.questTemp.Headhunter == "Rat_Tavern" && npchar.location == pchar.questTemp.Headhunter.Ratrumcity + "_tavern")
            {
    			dialog.text = "(����) ������� ���������, ������� ���������, ���� �� ��������� �����... ��, ����"+ GetSexPhrase("�","���") +", ������!";
                link.l1 = "��������, ��� ��������, ��� ��� ������� � ������ �����, '��������' ����������, �������� ������ �� �����...";
                link.l1.go = "Rat_Tavern_1";
            }
		}
		//<--���, �����
		
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "��, " + GetAddress_Form(pchar) + " ��� �� ����� ����� �����... ������ ������� � �������� �� ��������!";
			link.l1 = "� ��� ��� ��, ��������?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
		}
		
		if(CheckAttribute(PChar, "HellSpawn.SeekRebirth"))
	    {
			//������� ������ ��� ������
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			pchar.quest.HellSpawn.locationId = GetAttributeName(aPlace_2); //Id ������� ������
			sld = &locations[FindLocation(pchar.quest.HellSpawn.locationId)];
			npchar.quest.HellSpawn.label = GetConvertStr(sld.id.label, "LocLables.txt"); //��� ���������� ��� ��������
			switch (npchar.quest.HellSpawn.label)
			{
				case "������": sTemp = "������ � ������� ������?"; break;
				case "����": sTemp = "������ � ������� �����?"; break;
				case "����������": sTemp = "������ � ������� ����������?"; break;
			}			
			
			dialog.text = "��, " + GetAddress_Form(pchar) + " ��� �� ����� ����� �����... ������� �� ������ �������! "+sTemp+" �������, ������ ���������� ��� ��� ������-�� ������� ������������. ";
			DeleteAttribute(PChar, "HellSpawn.SeekRebirth");
			SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn.Rit");
			
			pchar.quest.HellSpawnRitual.win_condition.l1 = "location";
			pchar.quest.HellSpawnRitual.win_condition.l1.location = pchar.quest.HellSpawn.locationId;
			pchar.quest.HellSpawnRitual.function = "HellSpawnRitual";
		}
		if (!CheckAttribute(pchar, "PGG_killed_known")) pchar.PGG_killed_known = 0;
		if (CheckAttribute(pchar, "PGG_killed") && sti(pchar.PGG_killed) > 4 && pchar.PGG_killed != pchar.PGG_killed_known)
		{
			pchar.PGG_killed_known = pchar.PGG_killed;
			dialog.text = "�������, ��� � ����� ����� "+GetSexPhrase("������� ������� �� ������� ��������, ","�������� �������� �� ������� ��������")+ GetFullName(pchar)+GetSexPhrase(" ��� "," �") + " �����. ����� ���, ������������ �� ��� ���� ���� ��������� ��� �������� " + pchar.PGG_killed + ". ��� ��������� � ���� ������ ����. ���... ���-�� ���� ������ ��������. �� �� ��-�� ����, �� �� ���� ���� �������...";
		}
		
		//BlackThorn ������
		if (CheckAttribute(pchar, "questTemp.pirateVikingQuest") && rand(100) > 60)
		{
			if (CheckAttribute(pchar, "LastHearedViking") && pchar.LastHearedViking != npchar.city)
			{
				if (pchar.questTemp.pirateVikingQuest == "4")
				{	
					if(ShipsTypes[sti(RealShips[sti(pchar.Ship.Type)].BaseType)].Type.Merchant == true && GetCompanionQuantity(pchar) == 1)
					{
						if (GetSquadronGoods(Pchar, GOOD_EBONY) >= 400 || GetSquadronGoods(Pchar, GOOD_SILK) >= 1000 || GetSquadronGoods(Pchar, GOOD_SILVER) >= 600) 
						{
							dialog.text = "����, �� - ������� �����, �������, ������ �������� ��������. �� ��� ��, ���� � ��� �� �����, �� ��� �� ��� ����� - �� �������� ������� � ����. � ��������� ����� ������ ��������� ������, ������� ��� ��� �������� �� ����� ����� ���.";
							link.l1 = "��! ������� ��� �������. �� ���� ��� ��� ������ ���������, �� ������ ��� ��� �� ���. �����, �����.";
							link.l1.go = "exit_sit";
							AddQuestRecord("pirateVikingQuest", "6");
							//����� ����� ������� ��������, ���� ��� �� �����
							//pchar.questTemp.pirateVikingQuest = "5";
							pchar.LastHearedViking = npchar.city;
							
							sld = GetCharacter(NPC_GenerateCharacter("pirateVikingQuest_Captain", "OZG_3", "man", "man", 80, PIRATE, -1, true));
							sld.mapEnc.worldMapShip = "quest_ship";
							sld.mapEnc.Name = "������ '�������'";
							sld.mapEnc.type = "war";
							FantomMakeCoolFighter(sld, 80, 100, 100, "topor_viking", "pistol3", 600);
							FantomMakeCoolSailor(sld, SHIP_XEBEKVT, "�������", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
							
							sld.name 	= "������";
							sld.lastname = "�������";
							sld.AlwaysSandbankManeuver = true;
							sld.DontRansackCaptain = true;
							sld.AnalizeShips = true;
							SetCharacterPerk(sld, "MusketsShoot");

							sld.ship.Crew.Morale = 100;
							ChangeCrewExp(sld, "Sailors", 100);
							ChangeCrewExp(sld, "Cannoners", 100);
							ChangeCrewExp(sld, "Soldiers", 100);

							GiveItem2Character(sld, "cirass3");
							EquipCharacterbyItem(sld, "cirass3");
							GiveItem2Character(sld, "jewelry9");
							SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
							TakeNItems(sld, "Food5", 30);
							TakeNItems(sld, "potion2", 15);
							sld.SaveItemsForDead = true;
							sld.DontClearDead = true;
							
							LAi_group_MoveCharacter(sld, "Vikings");
							string  sGroup = "Sea_" + sld.id;
							group_DeleteGroup(sGroup);
							Group_FindOrCreateGroup(sGroup);
							Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
							Group_LockTask(sGroup);
							Group_AddCharacter(sGroup, sld.id);
							Group_SetGroupCommander(sGroup, sld.id);
							Map_CreateWarrior("", sld.id, 8);
							SetFunctionNPCDeathCondition("PirateVikingQuest_Captain_Is_Dead", sld.id, false);
							break;
						}
						else
						{
							dialog.text = "�������, � ��������� ����� ������� ��������� ������. �� ���, �������, ������� ������. ���� � ��� � �������� �������, ��� ���� ������� ������� ������� ���� ���� �� ����� ������� ����.";
						}
					}
					else
					{
						dialog.text = "�������, � ��������� ����� ������� ��������� ������. �� ���, �������, ������� ������. ��� �������� ������ �� �������� �������� �������.";
					}
				}
				if (pchar.questTemp.pirateVikingQuest == "3")
				{
					dialog.text = "�������, ������� ������ �������� ���������� �������� � ����� ������������ ���������. ��� ����������� ���� ������� ��� �������� ������� ������ ���������� �����, ������ ������ � ������ ������! ���� ���������, ������ ��� ����������� ��������. ���������� ������� �������, ��� ��� �������� �����-�� ������, ������� ������� - ������������ �������. ��� ������� ��� ������������. ���� ����������� �� ������� ������� ����� ���, ��������� ������ �� ����, ����������� ���������, �� ������ �������� �� ����� �� �����. ������ ��� ���������, ��� �������������� ������������, � ������� � �������� ����. �� � ��� �����, � ���� �� ��� �����? �� ��� �� ���� ������� ��� ����� ������, ������ � ���� ����� ������� �������. ���� �� ������� ������� - ����� ��� ��� �������� ��.";
					AddQuestRecord("pirateVikingQuest", "4");
					AddQuestRecord("pirateVikingQuest", "5");
					pchar.questTemp.pirateVikingQuest = "4";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "2")
				{
					dialog.text = "�� ������� ��� �������� � ����, �������. ������ ��� ������ ������ ����� �� ������, � ������ �������� ��� � ����� ��������� �������! ���� ����� �� ���������� �� ����� ������������ � �������� � ����� �����, ������ �������, ��� ������ ���� �� �����. �� �������� ������� ����� �������. � ��������� ��� �������, � ������� ����� ������� ������� ��������, �������, ������� ����� �����. �� � ��������� ��� ��� �������. �������, ����� ����� ���� ������. ��� �� ������� � ������� ������!";
					AddQuestRecord("pirateVikingQuest", "3");
					pchar.questTemp.pirateVikingQuest = "3";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "1")
				{
					dialog.text = "�������, �������? � ��� ���� ������� �������� �����, ��� ������ �������������� ������ �������. ��� ������ � ���� ��� �� ������ � ������ ������. �������, � ���� ��� ����������� ������ ��� ��������� '�������'. ������� ������������ ������ ����� ���� � ��� ��������, ������ �������� �� �����. �� ������ ��������� ������ � ������ �� ����� ���������� ������. � ������ ���������� ���������, � �������������.";
					AddQuestRecord("pirateVikingQuest", "2");
					pchar.questTemp.pirateVikingQuest = "2";
					pchar.LastHearedViking = npchar.city;
					break;
				}
			}
		}
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" ��. ������ ������ �� ��������.",
                                                   strum+" � ������ ��� ����� ��������� � �����.",
                                                    RandPhraseSimple("� ���� ��� ������, ��� � ���� ��� ������� �� ������ ��������!",
                                                                        "� ������� ������� � ��� ������� ��������� ������ �������!"),
                                                                         "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "��� ����� ���������! �� ����� � ����","���������, ����� ��� ��� ����� ����."),
                                                pcharrepphrase(""+ GetSexPhrase("���� � ����","������� ���� ����") +"! ������� �����. �� � ���� ���� ��� ������.",
                                                                "��� �� ����� ������ ������ ����������� ����� � �������� � �����."),
                                                pcharrepphrase(RandSwear() +" ��� ���� ������, � � ����.","�� �����, ����� - ������."),
                                                pcharrepphrase("������ � �������, ��� � ����� ������. �����, �� ��������.",
                                                                "����� �������� ����. �������� � ����."),
                                                npchar, Dialog.CurrentNode);

			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("����, ������ ��������.",
													               "����� �������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("��������! ������ �� �����. � ��� �����.",
													               "������� ���� ��� ������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! �� ��������!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("������ ��������!",
													               "�� ��������, ��������."),
													pcharrepphrase("��! �� ��� ��� �������? ���? ���!?! �� �����, ����� ����� �������.",
													               "����� ���� ��������, � ���� ������� ���� � ������.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("���! ��� ��������!",
													               "��� ���� ����. ��������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("� �� ���� ��� ��������! ������� ��� ��� � ����� �������!",
													               "�������, ����� ���������, ��� ���� �� �������. ��������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("��� � �����, �������? ��� �� � - " +GetFullName(pchar)+ "! ��������, � ����� �����.",
													               "�����, ���� ������ ��������� ��� ������, ��� � ��� ��� ����� ����."),
													pcharrepphrase("������ ���� �������, ��������! � ��� �����.",
													               "���"+ GetSexPhrase("","�") +" ���"+ GetSexPhrase("","�") +" ��� ������, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "��� ����� ���������! ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...",
                                     "��� ������.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
                                     "����� ��������");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06

                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("�������� ����� �����. �� �������� 1000 ������� � �������� ���, ��� ����.",
                "���-�� � �����������. ��, ��������, 1000 ����� ������� ��� ������.",
                "� ����� ���������� ���, ��� ����. �� �� ��������� - 1000 �������, �� ������� � �� ��������."),
                "������ ��� ������ ��������. � ������ ����� ���� ��������, �� ���� �� ����.",
                "", "", "block", 1, npchar, Dialog.CurrentNode);
             
    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "������� �� ������ ��������? ��� ��, ����� ����-������ �������.",
                                         "�� ����� ������ � ���"+ GetSexPhrase("","�") +" ��� �����."), "����� ��������� � ���-������ ������.", "����� ��������� � ���-������ ������.", "����� ��������� � ���-������ ������.", npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("�� �� ��������, ���� � ������ ������������� ������ ��������.", "� �������, �� ������ ��� �������, ��� �� ��� ���������� ������������� ���-�� ������."),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat("� ���� ��� ����� �����.", "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;
		
		case "rumours_tavern_yes":

			//------------- ��������� ����� ���������� --------->>>>>>>>
			//�������, ����� �3
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				Dialog.Text =  "� ��������� ����� ����� ����� ��������� �������, ������, ��� �������, ��������� ������ ���������� ������� � �����. ������������ � ��������� � ����� ������ ������-�� �����... ��� ��� ������ ���������!";
				link.l1 = "������ ���������� �������, ��������? ����� ���������... � ������ ������ ��������������� �� ������?";
				link.l1.go = "rumours_tavern";
				AddQuestRecord("Pir_Line_3_KillLoy", "14");		
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","�"));		
				pchar.questTemp.piratesLine = "KillLoy_toCumana_2";
				break;
			}
			//���, ����� �� �������
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "Rat_tortuga" && npchar.location == "Tortuga_tavern")
	    		{
	    			Dialog.Text =  "�������, ������� � ����������� ������ '��������' �������� �����-�� ������ � �'�������� � ���������� ��������� �� ����. ��� ��� ������� ����� ������ ��� ������� �������������� � ������� � � ���� � �������. ����� ����, �������� �������, ������� ��... � ��� ������� ������ � ���� �������� - ������, ��� �����, �� ������� ��������. ������ �����...";
	    			link.l1 = "����� ���������... � ������ ������ ��������������� �� ������?";
	    			link.l1.go = "rumours_tavern";
	    			pchar.quest.Headhunter_PinasseTortugaOver.over = "yes";
	    			AddQuestRecord("Headhunt", "17");	
	    			pchar.questTemp.Headhunter = "Rat_officer";
	    			FreeSitLocator("Tortuga_tavern", "sit1");
	    			SetFunctionTimerCondition("Headhunter_RatOfficerOver", 0, 0, 3, false);//������
	    			break;
	    		}
			}
			//���, ����� �� �������
			//<<<<<-------- ��������� ����� ���������� -----------------
		
            string RumText = SelectRumourEx("tavern", NPChar); //fix
            //SelectRumour();
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
                link.l1 = RandPhraseSimple("� �� ����� ������� �� ������ �������, ������.", "���� �������� �� ����� � �������� ����� - �� ������ �� ��������.");

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
			  //  link.l2 = LinkRandPhrase("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
              //                       "����� ��������","�������, ��� ����. �� ��������.");
			  //  link.l2.go = "Exit";
            }
            else
            {

                AddMoneyToCharacter(pchar, -1000);

                Dialog.Text = RumText;

    			link.l1 = RandPhraseSimple("���������, ��� ���� ������. � ������ ������ �� ����������?", "������, �� �������� ���� ������ - �����. ���� ���-������ ���?");
                //RandPhraseSimple(RandSwear() + "��� ����� ���������! ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...",
                //                         "��� ������.");

    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;
    			//link.l2 = LinkRandPhrase("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
              //                           "����� ��������","�������, �� ��� ����� �����. �� ��������.");
    		//	link.l2.go = "Exit";
            }

		break;

		case "rumours_tavern_no":
			Dialog.Text = "������� ���� ���������, ��� ����� ������� �����.";
            link.l1 = "����� ��������� � ���-������ ������.";
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase("�������, ����"+ GetSexPhrase("��","��") +" �����������.",
                                     "����� ��������","�� ��������.");
			link.l2.go = "Exit";
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "��, ��� ���������. ������� ��� ������...",
										"��, ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("��, ������, ������.",
										"����� ��������, ��������.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("�� � ��� ��������, ��� ��� ��������, ��� ����.", 
					"������ � ������ �� ������, ��������...");
				Link.l1 = RandPhraseSimple("�������. �� ��� ��, ����� ��������.",
										"����. ��, �����, ��������...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "��, ��� ���������. ������� ��� ������...",
										"��, ��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("��, ������, ������.",
										"����� ��������, ��������.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("�� � ��� ��������, ��� ��� ��������, ��� ����.", 
					"������ � ������ �� ������, ��������...");
				Link.l1 = RandPhraseSimple("�������. �� ��� ��, ����� ��������.",
										"����. ��, �����, ��������...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("�������...",
										"����...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("�� � ��� ��������, ��� ��� ��������, ��� ����.", "������ � ������ �� ������, ����� ��������..."), 
					RandPhraseSimple("��������, �� � ��� ��� ��� ���������.", "������ � ������ �� �������, ��������..."));
				Link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +".", "��, ����� ��������.");
				Link.l1.go = "exit";			
			}
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		��������� ��������� Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanForAll": //��������� � ������� ��� ����
			dialog.text = LinkRandPhrase("�������? ��, ��������, ��� ������.", "���������� ������� - ��� ������ ���������. ��������, � ������ ���.", "��� ��, ������� ��������� � ��������.");
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
                    dialog.text = LinkRandPhrase("� �� �������, ��� ���������� �� ������, " + GetAddress_Form(NPChar) + "? ��� ��� " + GetFullName(npchar) + ". ��� ���� �������?",
                             "�� �������� �� ���, " + GetAddress_Form(NPChar) + "?! � " + GetFullName(npchar) + ". � ��� �� ���� � ���?",
                             "� ��� ������, " + GetAddress_Form(NPChar) + ". ��� �� ������? ������, ���� ����� " + GetFullName(npchar) + ".");
                    link.l1 = NPCharRepPhrase(pchar, "� �� ����������, �������! ������ �� �����!", "� ���� � ��� ���������� ������ �� ������ �����, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "LoanFindCitizen_1";
				    NPChar.quest.LoanFindCitizenType = rand(2); // ��� ����
                    break;
                }
            }
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l2 = "� ������"+ GetSexPhrase("","��") +" ��� ������.";
                link.l2.go = "TakeChest_2";
            }
			link.l9 = RandPhraseSimple("�-�-�, �, ������, ����"+ GetSexPhrase("��","����") +". ������� ���������� ��� � � ���� �� ����.", "��������, ������� ���������� �������� � ���� � ��� ���.");
			link.l9.go = "exit";
		break;
		// ������� ���� ����������
		case "LoanFindCitizen_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance1))
            {
                case 0 :
                    dialog.text = "��, �����. � ��� ��� ��������� ��� ��� ������.";
        			Link.l1 = "�� ��� ��, ����� ������! ����� � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "������������, ��� � ������ ��� ���!";
        			Link.l2.go = "exit";
                break;
                
                case 1 :
                    dialog.text = "���! ������ � �� �����! � ������ ����������, ������ ������.";
                    Link.l1 = "������ �� ����, � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". � �� ����� ���������� � ��-�������.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "�� ��, �������! �� ������, ����� �������, �������� ���...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
                
                case 2 :
                    dialog.text = "� ���������, � ���� ��� ���� �����.";
                    Link.l1 = "������ �� ����, � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". � �� ����� ���������� � ��-�������.";
        			Link.l1.go = "LoanFindCitizen_1_1";
        			Link.l2 = "� ������� ����?";
        			Link.l2.go = "LoanFindCitizenType_2";
        			//NPChar.quest.LoanFindCitizenType = rand(1);// ������ 2 ����
                break;
			}
		break;
		
		case "LoanFindCitizen_1_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance2))
            {
                case 0 :
                    dialog.text = "��, �����. � ��� ��� ��������� ��� ��� ������.";
        			Link.l1 = "�� ��� ��, ����� ������! ����� � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "������������, ��� � ������ ��� ���!";
        			Link.l2.go = "exit";
                break;
                
                case 1 :
                    dialog.text = "���! ������ � �� �����! � ������ ����������, ������ ������.";
                    Link.l1 = "������ �� ����, � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". � �� ����� ���������� � ��-�������.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "�� ��, �������! �� ������, ����� �������, �������� ���...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;
		
			case "LoanFindCitizen_1_2":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance3))
            {
                case 0 :
                    dialog.text = "��, �����. � ��� ��� ��������� ��� ��� ������.";
        			Link.l1 = "�� ��� ��, ����� ������! ����� � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "������������, ��� � ������ ��� ���!";
        			Link.l2.go = "exit";
                break;
                
                case 1 :
                    dialog.text = "���! ������ � �� �����! � ������ ����������, ������ ������.";
                    Link.l1 = "������ �� ����, � ���� " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". � �� ����� ���������� � ��-�������.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "�� ��, �������! �� ������, ����� �������, �������� ���...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;

		case "LoanFindCitizenType_0":
            dialog.text = "��� ��� �����.";
			Link.l1 = "������� �� ��������������!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, (sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent)));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("� ��� ���� 30 ����, ����� �������� ������������ � ������� ��� ������.");
        	AddCharacterExpToSkill(pchar, "COMMERCE", 100);  
		AddCharacterExpToSkill(pchar, "Fortune", 50);      	
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		
		case "LoanFindCitizenType_1_1":
            dialog.text = "���, ��� �� � ���� ������������.";
			Link.l1 = "�� ���� ��� ���������!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("� ��� ���� 30 ����, ����� �������� ������������ � ������� ������.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;
		
		case "LoanFindCitizenType_1":
            dialog.text = "������!! �������"+ GetSexPhrase("�","��") +" ������ ������!";
			Link.l1 = "�������!";
			Link.l1.go = "fight";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("� ��� ���� 30 ����, ����� �������� ������������ � ������� ������.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;
		
		case "LoanFindCitizenType_2":
            pchar.GenQuest.Loan.FindCitizenTempMoney = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) - rand(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
            dialog.text = "������ " + pchar.GenQuest.Loan.FindCitizenTempMoney + " �������.";
			Link.l1 = "���. ����� ��� �����!";
			Link.l1.go = "LoanFindCitizen_1_2";
			Link.l2 = "�����, ��� ����. ���"+ GetSexPhrase("","�") +" �������. ���"+ GetSexPhrase("��","��") +" � ������� ����"+ GetSexPhrase("��","��") +".";
			Link.l2.go = "LoanFindCitizenType_2_1";
			//NPChar.quest.LoanFindCitizenType = rand(1);// ������ 2 ����
		break;
		
		case "LoanFindCitizenType_2_1":
            dialog.text = "�� ����� �����! ������� �������!";
			Link.l1 = "��! ����� ���"+ GetSexPhrase("","�") +" �� ��� ����.";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, sti(pchar.GenQuest.Loan.FindCitizenTempMoney));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("� ��� ���� 30 ����, ����� �������� ������������ � ������� ��� ������.");
        	OfficersReaction("good");
        	ChangeCharacterReputation(pchar, 3);
        	AddCharacterExpToSkill(pchar, "Leadership", 30);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		//�������� ��������
        case "TakeChest_2":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                if (CheckAttribute(pchar, "GenQuest.LoanChest.Money.Discount"))
				{
					Dialog.Text = "��� ��� ������, � � �������� � ��� ������. ������, �� �� ��������� � ���������� ��� ����� ��������. ������� � �������� ��������� ������ ������ �������� �� " + pchar.GenQuest.LoanChest.Money.Discount + " ���������. ����� ��������, �� ��� ���������� �� ��������. �������� ��������...";
					link.l1 = "�������!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money)/100*sti(pchar.GenQuest.LoanChest.Money.Discount));
				}
				else
				{
					Dialog.Text = "������������! � ����� ��� ���. ��� ���� �������.";
					link.l1 = "�������!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money));
				}
				ChangeCharacterReputation(pchar, 1);
                AddCharacterExpToSkill(pchar, "Sailing", 50);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
                OfficersReaction("good");
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));    			
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
    			AddQuestRecord("Gen_LoanTakeChest", "3");
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                Dialog.Text = "������������! �� ��� �� ��� ������� � �������?";
                link.l1 = "� �� ������ ������� ������ ��� ��������?";
    			link.l1.go = "TakeChest_3";
                link.l2 = "����� �����.";
    			link.l2.go = "exit";
			}
		break;

		case "TakeChest_3":
            Dialog.Text = "���! ������ � ��������!";
            link.l1 = "�����. ����� � ���� �� ���������.";
			link.l1.go = "exit";
			//link.l2 = "�� �, ������, ����� � " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Chest)*30000) + " ������� ��������� ��������?";
			//link.l2.go = "TakeChest_4";
		break;

		/*case "TakeChest_4":
            Dialog.Text = "��, ��� ���������.";
            if (sti(pchar.Money) >= (sti(pchar.GenQuest.LoanChest.Chest)*30000))
            {
                link.l1 = "��� � ������������!";
    			link.l1.go = "TakeChest_5";
			}
			link.l2 = "������ ��� ����� ��� ����.";
			link.l2.go = "exit";
		break;

		case "TakeChest_5":
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Sailing", 30);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "COMMERCE", 30);
            OfficersReaction("good");
            Dialog.Text = "� ���� ����� ����� ����!";
            link.l1 = "�������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1*(sti(pchar.GenQuest.LoanChest.Chest)*30000));
			DeleteAttribute(pchar, "GenQuest.LoanChest");
			DeleteAttribute(Pchar, "quest.LoanChestTimer");
			AddQuestRecord("Gen_LoanTakeChest", "4");
            CloseQuestHeader("Gen_LoanTakeChest");
		break; 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		������ ����, ������������� �� ���������� �����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("�� ��� ��, ����� ������. � ���� ����� ��� ��� �����, ������� ��� �������� ��������� ���������� ���� ����� � ����. �������� ��������.\n�� ��������� �� ��� ������ � �� ������������� �� ����, ��� ����� ���� ��������������. ���������� ������������...", 
				"��, ���������. � ������ ��� �����, � �������, ��� �� ������ ���� ��������� ���������� ���� ���� ����� � ����.\n������ �������� � �� ��������� �� ��� ����� - ��� ������.");
            link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +". ��������...", "�������� � �����.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		����� ���������, ��������� ������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "AscoldTrader": //��������� ������ ������
            dialog.Text = "��������, �� ��������"+ GetSexPhrase("","�") +" ��� ������� �����, ������� � ������ ���� ���������?";
            if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = "���, ���� �� ��������"+ GetSexPhrase("","�") +"... ��������, � ��������� �� ������ ��, �������, ����, �� ���-�� ��� ������...";
            	Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = "���, ���� �� ��������"+ GetSexPhrase("","�") +"... �� � �������� ������.";
            	Link.l1.go = "quests";
			}
		break;
        case "AscoldTrader_WasSeek":
            dialog.Text = "��������, �� ��������"+ GetSexPhrase("","�") +" ��� ������� �����, ������� � ������ ���� ���������?";
            Link.l2 = "��, ���"+ GetSexPhrase("��","��") +". � ������� �� ��� �� ���� ���������?";
            Link.l2.go = "AscoldTrader_1";
        break;		
		case "AscoldTrader_1":
        	dialog.text = "� - ���������. �� � ����, ��� ����� � ���� ���.";
    		link.l1 = "��, � �����������"+ GetSexPhrase("","�") +" �� ��������� ����� ����� ������.";
    		link.l1.go = "AscoldTrader_2";
		break;
 		case "AscoldTrader_2":
        	dialog.text = "�������, �� �� ���������� � �������. ������ �����������.\n"+
                          "�� ��������� � ������ ��� ��� ����� ���� �������� ��� - �������.";
            if (Characters[GetCharacterIndex("Ascold")].quest.meeting == "0")
            {
                link.l1 = "�������� ���...";
                link.l1.go = "AscoldTrader_4";
            }
            else
            {
                link.l1 = "���� � ���, �������� ����������. ������, ����� ��������...";
                link.l1.go = "AscoldTrader_3";
            }
		break;
 		case "AscoldTrader_3":
        	dialog.text = "� ��� ���������? �������"+ GetSexPhrase("","�") +" �� ���� ��� ������ ����?";
    		link.l1 = "�� ��, �� ������ �������� ���� �� �����, ��� "+ GetSexPhrase("���������","��������") +"!";
    		link.l1.go = "AscoldTrader_4";
		break;
 		case "AscoldTrader_4":
        	dialog.text = "������� ������� ��������, �� ������� �� �������, �������. �� ������ - ��������, ���� ����� �����, ������� ����� �� ������ ������� �����, ��� ������� ��� ����, � ������ ���� ���� �� �������. ������ � �������� �������, � ���� � ����� ������ �� �������� ����������� ��������.\n"+
                          "��� � ����� �� �������� �����, � ����� �� ����, ��� � �� ����, ��� �� ����������.\n"+
                          "�� ��� �� ��������, ��� ��� � ���� � ��� �������� ����.\n"+
                          "��� ��� ������� � ����, �������������, �������, ��� �� ���� - � ��� ����� � �������. ����� �� � ���� ��� �����, ��� ��� ��� ��� �����.";
    		link.l1 = "� ���� � ����� ����� �����?";
    		link.l1.go = "AscoldTrader_5";
		break;
 		case "AscoldTrader_5":
        	dialog.text = "�� ���� �� ���������, � ������ ������ ����� ������������ �� ����� � ��� ������� ��������.";
    		link.l1 = "�������. ��� �, �������, ������� � ������ �������� ��� ������.";
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "GoToAscold";
    	    QuestSetCurrentNode("Ascold", "HaveRecomendation");
            AddQuestRecord("Ascold", "2");
		break;
 		case "AscoldTrader_6":
        	dialog.text = "������, � ����������� ��������?";
    		link.l1 = "�����, ��������...";
    		link.l1.go = "AscoldTrader_7";
		break;
 		case "AscoldTrader_7":
        	dialog.text = "�� � ��� �� �����"+ GetSexPhrase("","�") +"?.. ��� ��� � ���� �����, "+ GetSexPhrase("��������","�������") +": ������� ���� � ���. �� � ����, �������, �� � ����-�� ����� �� �������. ������� �� ���� ����������� � ���� - � � ����� ��������� ������.";
    		link.l1 = "���, �� ��� ��, ������� �� ������.";
    		link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
        //==> ����� ������ ��� ������ �����, ����� ����.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat("����� ��������� �� ���� ��������. �-�-�, ���. �� �������� �� ���, ��� ������ ������� ��������� ����������, �� ����� ��� ����������. ������� ���� ������� ��� ���� � �������, ��� ����������, ��� � ��� ������.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
  			Link.l1 = HeroStringReactionRepeat("������� �� ������ �����.", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat("��� ��� �� ����� ����� ����������: �������� �����, ������� �� �������, ������� ��� ����� � ������. ���� � �������� ���"+ GetSexPhrase("","�") +", � ����� ��� �� ����.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat("�������, " + npchar.name + ".", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[GetItemIndex("Azzy_bottle")].shown = 0; //���� ����������� ������� �����
		break;
		//==> ����� ������ ��� ������, ����� ����.
        case "GiveLamp":
			dialog.text = "�� ��������� ��������"+ GetSexPhrase(", ��� ���","�, ���� ���") +". ����������, ��� ��� ������, �� �� ����� �����, ��� ������ ������� ����� ����� �������� ������.\n"+
                          "� �� ���� ����������, ��� �� ��� ����"+ GetSexPhrase("","�") +". ������ ��������� ������ ���� ����� ����! ��� � �����.";
			link.l1 = "�������, ������ ����.";
			link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 100);
            TakeItemFromCharacter(pchar, "Azzy_bottle");
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		������ ����� ���� ���, ������� ������� � �������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("������ ����� ���� ���!!! ��� ��� �� ����� ��������?! ��, ������, "+ GetSexPhrase("��������","�������") +"...", "��, �� ���� ��� ��� ���������?! �����, �������"+ GetSexPhrase("","�") +" �������� ����? ��, ����� ���� �����...", "������, �� ���� ��� �����"+ GetSexPhrase("","��") +"? �� �� ���"+ GetSexPhrase("","����") +", �����������! ��, ������, ��� �� �������"+ GetSexPhrase("","�") +", ����"+ GetSexPhrase("��","��") +"...");
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		����� ��������� ����� �����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RBlueBird":
			dialog.text = "��, �������, �� ���������, � ��������� ��� �����. ��, �������� ���������� ����, �� ����� ���������. � �� ���� �������� ��������� '����� �����'...";
			link.l1 = "'����� �����'?";
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = "��, ��� ������� ������, ������������ ������� ������ ���� �����, ���� �� ���� � ���� ����������. ������ ������ ������� ���������. ������� ��������, ��������� �������� ���������, �� �������.";
			link.l1 = "� ������ �� �������, ��� �������� ����������? ���� ������ ��� ����� ��������� ���� � ����� ����������.";
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = "���������, �����. �� ��� ���� � ���, ��� ������ ��� ����� �������� ���������� ����������. ����� ����� ����� ���� ���� ��� �����, ����� �������� ������ � ������ ����� � ����� ����. ��� ��� - ��������!\n� ����� �� �������� ������ � ������������ - ��� ��� �� �� ��������, ���� ���� � ������� ���������.";
			link.l1 = "�������. � ��� ��� ���� ������� ����� �� ������� ������...";
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = "������ ���. ��� ����� ��� �������� �������� ����������� �������, ���� �� ����, ��� '����� �����'!";
			link.l1 = "�-��, �������� ��� ���... ��, ��� ��� �� �� ������ �� ����?";
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = "�� �����, ����� �� ���������� ��� ���������� ��������, ���� �� ��������!!!";
			link.l1 = "� ��� � ���� � ����� �����?";
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = "� ������ �� ���� ������ ��������� ������ ��� ��� �� ��� ������. ��������� ����� �������� � ���� ��� ������ �������. ������� ������ ������ ����� �� ���!";
			link.l1 = "�� ����� ������, ��������, � � ������� �� ��������. ��� ������!";
			link.l1.go = "RBlueBird_close";
			link.l2 = "��, ��� ������ ���� ����������. � �����"+ GetSexPhrase("","�") +" ������� �� ��� ����. ������ ����� ����������?";
			link.l2.go = "RBlueBird_6";
		break;
		case "RBlueBird_6":
			dialog.text = "�� �� ���������� �� �������. � ��������� �������, ��� ������� ��� ����� �������, ���� ������! ������� �� ������, �� ��� ���������� ������� ����� � ����� ����, ������ ������ ��������. ��������������...";
			link.l1 = "��� ���? �� ������ ��������� �� ���� ����������?";
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = "��, ��������� �� � ������ ���-����, ����� �� �������� ���� ���� ������ ����� �������. ������ �� �����, ��� ������ � ������� ������ �� �������, �� ������ �� �����. ���� ��� �����, ��� ��� ���������� � ���� ������� ������������...";
			link.l1 = "��-�-�-��, ��������, ��� ��� ���-��. � ������ �������� ��� ������� ������.";
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = "����������� ������, " + GetAddress_Form(NPChar) + "." ;
			link.l1 = "��� ������ ����� ����� � ����, ������ �������, ��� ������, �� ������ �� ������, ��� � ����"+ GetSexPhrase("��","���") +" �� ��� ����. � ������. �� ������, ��� �������� ���� ������� ����� ��� ��������. ��� ������ '�����'?";
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = "� ������ �������� ������� �����. �� �� �����������, �� ���� �� ������� �� ��� ������. �� - ���� ������������ ������� ����������� �����, ��� ��� ���� ��� ������. ���� �� �� �� ����������� ��� � ������� ������ - ���� ����� ������ �� �����. �� ��� ������ �� ��������� � �������� ���� ����� � ����!";
			link.l1 = "�������. ����� ������! � ��� �� ��� �����?";
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = "������� ������. �� �������� ����� �� �������� � ��������� ���������. ��� �� �������� �� ����?";
			link.l1 = "�� ���������� ��� ������� � ��������?";
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = "����������!";
			link.l1 = "����� ������. � ������� ������ � ����� ���, ������� ������ ���������.";
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = "��, ������ �� ������, �� ��� ����! �� ��� ��, �����������. ����� �������, ��� ��� ����� ��������� ���, ��� �� �������.";
			link.l1 = "�����, ������ �� �����������!";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //�������� Id ��������
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
		break;


		case "RBlueBird_close":
			dialog.text = "�� ��� ��, ����� ����. �������, �� ������ '������' � ������ �����...";
			link.l1 = "��...";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "over";
		break;
		case "RBlueBirdWon":
			dialog.text = "���������� �������, ����� � ���! �������-�� �� ������ �������� ��������� ��-����������... �� ������ �������� ������ ����� ������?";
			link.l1 = "��, ����������...";
			link.l1.go = "RBlueBirdWon_1";
			int chComp;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "XebekVML1")
        		{	
					dialog.text = "��, ���������... ��������� ��� ��������, �� ������ ���������� ������, �� �� �������� ��! ������ ��� ��������� � ����� ��������.";
					link.l1 = "��, ��� ���. �� � � ��� ��������?";
					link.l1.go = "RBlueBirdWon_10";
					break;
                }
            }
		break;

		case "RBlueBirdWon_1":
			dialog.text = "��� �������, �������� ��������. ������ � ��������. ����� ���� ������� ������ ���������� �����.";
			link.l1 = "�������, �� � �������. ����� ����� ����������... ������, � �� �� ������ ������, ��� ����� �� ���� ����?";
			link.l1.go = "RBlueBirdWon_2";
			TakeNItems(pchar, "chest", 4);
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
		break;
		case "RBlueBirdWon_2":
			dialog.text = "��, ����� ����� ��������� ������...";
			link.l1 = "��� ����� '������' �������� � ��������� ���� - ������� ������.";
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = "�� ����� ����!..";
			link.l1 = "�����. �������������, � ���������, � ���� ���, �� �� ������ � ����, ��� ������� ��� ���� �� ������.";
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = "��, ��� ��� ����� ���������... �� ��� ��, ������� ��� �� ������ � �� ����������.";
			link.l1 = "�� �� �� ���, ��� ���� ��������. ��������.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBirdWon_10":
			dialog.text = "�������� � ���, ��� ���� ��������� ������� ������ � ��� � �����. � ��, ������, ���� �����! � ��� ��� �������� ������� ��������� ����� ��� ��, ��� ��� ����� ���������� ������?";
			link.l1 = "��, ������, �������, ����������... ������, � ��������"+ GetSexPhrase("","�") +" ������!";
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = "���, �� �� �� ���������. �� �������������� � ���������� '����� �����', � �� �� ��������.";
			link.l1 = "��, ��� ������ ���! �� ��� ��, � ��� �����"+ GetSexPhrase("","�") +"... ����� ����������, ����������� ��� ��������� ������ ����� ��������.";
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = "������� �������������! ��������, � ������ ������� ���� ����� '��' � '��'.";
			link.l1 = "�����������. �� � �� ��������...";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("������ ������","������ ����"));
			pchar.questTemp.BlueBird = "returnMoney";
			pchar.questTemp.BlueBird.City = GetSharpCity();
		break;

		case "RBlueBirdDieHard":
			dialog.text = "����� � ����� ����. �� ��� ��, �� �� ����"+ GetSexPhrase("��","��") +", ��� ������� �� ��� ����, � � ���� ������ �� �������. �����, �������� ��� � ����� ���������...";
			link.l1 = "�������, ��� ������ � ����� �� ��������...";
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = "��� �� �����. ��� ����� ��� � �����, � ������ ��������, ��� ������ ������ ��� ����� ��������. �� ���, �� ����� �����, � ����� � �����\n���, ���-�� ���� �� ������ ��������.";
			link.l1 = "������... �� ��� ��, ��������.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = "�� �� ������"+ GetSexPhrase("��","��") +"! ������, ���� �������� ��������� �������!!";
			link.l1 = "� �� ��� �� ������"+ GetSexPhrase("","�") +", ���� �� �� �� ������ ����������!";
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = "�-�-���, ����! ������, ������ �"+ GetSexPhrase("��","�") +"!! ������ ���� �� ����, ������"+ GetSexPhrase("��","��") +"...";
			link.l1 = "����� �� ������� ��� ������, �������. ����� ������ ��� ������...";
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = "���� �� �������"+ GetSexPhrase("","�") +", ������"+ GetSexPhrase("��","��") +"! ��� � �����, ��� �������� � �����!! �� ���� '����� �����' ������� �� ���������� ��� ������� �������!..";
			link.l1 = "������ ���, �� ���� ��������, ����� ���� ��������� ��������.";
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = "������ ��������, ������ � ����? �� ��� �������������� ��������������! ��� �� ��� ��������, �� ������� ������!";
			link.l1 = "��� ���, �� ���� ��� �������, ��� ������� ���������� �� ��������� �������. � ����� �� ������� ����� �������������? � �����, � �����"+ GetSexPhrase("","�") +" �������� � ���� ������ �� ��������� �����...";
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = "�� ������, ���� ��� ����� �� ��� ���. ��� �� �������� ������� ������, � �� �� - ��� ���� �������!";
			link.l1 = "���! ��, ��������, ������� ������� ������ ������� � ���������. ���� � ���� ������. ���-�� ������� �� ��������, � ����� ������ ����� ��������.";
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = "��� ��� ����� �������? � ��� � ���� ���� ������ ��������������.";
			link.l1 = "��, ��� � ������� ���������. ����� � ���, ��� �� ���������� �� ����������� ������ ���� �� �����, � ������� ���. � � �����, ��� ������� ����������� � ������� ������� ����� �������.";
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = "����� �������?";
			link.l1 = "������� ����� ���������������. ��� ������ '����� �����' - � �����"+ GetSexPhrase("","�") +" ��� ��������. ���� �� �� ������ ��� ��� ������, �� � ��� � ������� �� �� ������"+ GetSexPhrase("","�") +". ��� ��� ��� ���� �������� �� ����� ��������, ��� �������...";
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = "�� �����, ��������� ���� 50 ����� � ���������� ������!";
			link.l1 = "�� ��� ������, ��� ���. ��� ���� � ���, ��� � �����"+ GetSexPhrase("","��") +" �������������� ���������� ��������, ������� ��������� ���. �� ������ ��� � ��������� ������. ������� ����� �������.";
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = "� ��� ��� �� ����� �����? �������� ��.";
			link.l1 = "��������� �� � ������ ����. 200 �����, � � ������� ��� � �����. ����� - ������. � ����� ����. ������� ���� �����, � ����� ���...";
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = "�� �� - ������"+ GetSexPhrase("","���") +"!!";
			link.l1 = "� �����, ����� ��"+ GetSexPhrase("�� ������","�� ���������") +"...";
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = "������. ��� ���� ������ - ������������ ��������. ����� ���� ������ ������� �����. � ������ ��������! � ������ ��� � �����!";
			link.l1 = "�������������. ������, ����� �� ������������ �� ����, '����� �����' ��� ����� �� ��������. ��������, ����� � ����� ������������...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //��������� �����
			TakeNItems(pchar, "chest", 14);
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Xebeca_BlueBird", "14");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("��","���"));
			CloseQuestHeader("Xebeca_BlueBird");
		break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		������� ������� �������� �������� ISS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ISS_deposit":
			dialog.text = NPCStringReactionRepeat("���������� �����. ���� ������� �������� �� ������ �������� ����� ������ ����� ��������� ���� �������������.", 
				"� ��� ������� ���, " + GetAddress_Form(NPChar) + ", ��� ������� � ����. � ��� ������������� �� ��� ������.", 
				"��� �� ����� ������������. ������� ��������� � ����, � ��� ������ ������������� �� ��� ������.",
				"��, ��� �������, �� ��������� ����������� ���� ���������. ��� ��������� ����������, ������� � ���� ������ ��������� ����� ���������. ������� �� ���� ��� ��������� � ����, �������� �� ��� ������� ����� ������������� �� ������.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������. �� ��� ��, ���������. � �����"+ GetSexPhrase("","�") +" ��, ��� �����"+ GetSexPhrase("","�") +".", 
				"���, �������...",
				"� � �� ���������� �����.", 
				"�������... ������� ���, " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "ISS_takeDeposit":
			dialog.text = "��-��, � ������� ���������� �������� ��� ���������� ��������. �������� ��������, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "��-��, ����� ������...";
			link.l1.go = "ISS_takeDeposit_1";
			AddMoneyToCharacter(pchar, 1000000);
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		case "ISS_takeDeposit_1":
			dialog.text = "���� �����, �� ������ ������� ��� ������ � ����? � ������ � ����� �������, ��� ���������...";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ���, �������. � �������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "over"; //����� ������� ���
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		//�������� ����������, ������� ������
		case "MechanicIsPrison_man":
			dialog.text = "�-�, �� ��� � ��, �������...";
			link.l1 = "� ��� ����? ������ �� ��� �� �� �������?... � ��� �������?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_man_1":
			dialog.text = "��� �� ������ � �� ����. ����� � ����"+ NPCharSexPhrase(NPChar, "��","��") +" �� '��� ��������', ��� ��� ��� �������� �����������. ���� �� �����, �� ���������, � ������� ��� ��� ������ �������.";
			link.l1 = "��������!!! ��� �� ������ ������?";
			link.l1.go = "MechanicIsPrison_man_2";
		break;
		case "MechanicIsPrison_man_2":
			dialog.text = "� ��� �������� ��� �� ��������?";
			link.l1 = "������� ��� �����. �� ������ �� ������� ������, � ��� ���������� ��� ��� ������� �� ������.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MechanicIsPrison_man_3":
			dialog.text = "����� ����� ���� � ���������� � �������, �������� ��������. �, � ���������, ��� � ���� ���� - ������� ������� �� ���� ���� ����� ����� �����...";
			link.l1 = "���, ��� � �������... ������������� �� �������, � ����� ������� � ���������. ��������� ����� �������, ���� �� �����, ��� ���.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_man_4":
			dialog.text = "��� �������, �������.";
			link.l1 = "�� ��������� ��� ��� ����. ��� ����� ������.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true; 
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		//�������� ����������, ������� ����
		case "MechanicIsPrison_woman":
			dialog.text = "�-�, �� ��� � ��, �������...";
			link.l1 = "� ��� ����? ������ �� ��� �� �� �������?... � ��� �������?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_woman_1":
			dialog.text = "��� �� ������ � �� ����. ����� � ������ �� '��� ��������', ��� ��� ��� �������� �����������. ���� �� �����, �� ���������, � ������� ��� ��� ������ �������.";
			link.l1 = "��������!!! ��� �� ������ ������?";
			link.l1.go = "MechanicIsPrison_woman_2";
		break;
		case "MechanicIsPrison_woman_2":
			dialog.text = "� ��� �������� ��� �� ��������?";
			link.l1 = "������� ��� �����. �� ������ �� ������� ������, � ��� ���������� ��� ��� ������� �� ������.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MMechanicIsPrison_woman_3":
			dialog.text = "����� ����� ���� � ���������� � �������, �������� ��������. �, ��� �������, ������ � ���� ���� ��� �� �����, � ���������.";
			link.l1 = "��� �����... ������������� �� �������, � ����� ������� � ���������. ��������� ����� �������, ���� �� �����, ��� ���.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_woman_4":
			dialog.text = "��� �������, �������.";
			link.l1 = "�� ��������� ��� ��� ����. ��� ����� ������.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true; 
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		case "SeekCrew_all":
			pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
			chrDisableReloadToLocation = true;
			float   locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			if (sti(pchar.questTemp.LSC.crew) >= 15)
			{
				DeleteAttribute(pchar, "questTemp.LSC.crew");
				pchar.questTemp.LSC = "MechanicIsArrest";
				pchar.questTemp.LSC.lastManId = npchar.index; //���� ������� ������
				NextDiag.TempNode = "MechanicIsPrison_" + npchar.sex;
				AddQuestRecord("ISS_MainLine", "63");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("��","��"));
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				npchar.cityTape = "quest";  //����� �� ������������
				DeleteAttribute(npchar, "location.going"); //����� ����� �� �����������
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
				pchar.quest.LSC_afterArestMachanic.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSC_afterArestMachanic.win_condition.l1.location = pchar.location;
				pchar.quest.LSC_afterArestMachanic.function = "LSC_afterArestMachanic";
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "62");
				AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
				AddQuestUserData("ISS_MainLine", "Sex", NPCharSexPhrase(npchar, "����������", "�����������"));
				AddQuestUserData("ISS_MainLine", "iCrew", FindRussianPeoplesString(15-sti(pchar.questTemp.LSC.crew), "Acc"));
				npchar.lifeDay = 0;
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);			
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // ����� ���� ������������� �� �������
{
	string sRetRumour = "����� ���. �������� � ��� ��, ��� Warship'�.";
	// ���� - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - ��� ��������, ����� ������ �����. ����� ����� ����� ��� �������
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // ���� ������ �������. ����� ������ ��� ����� ����
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // �����������
	STR_MAYOR[0] = "�, �������� ���������� - ������������� �������. �� ����� ��������� ����� �������� - � ������� �� ��������� � ��� �� ���� �� ������� �������� ���������\n������������ ��� ���������� - ��... ���... ������ ��������. ����, ��������, ��� �������� �����������.";
	STR_MAYOR[1] = "�, �������� ���������� - ������������� �������. �� ����� ��������� ����� �������� - � ������� �� ��������� � ��� �� ���� �� ������� �������� ���������\n������������ ��� ���������� - ��... ���... ������ ��������. ����, ��������, ��� �������� �����������.";
	STR_MAYOR[2] = "���, �������� ���������� � ��� �������... �� ����������������. ��� �� ������� ��������� � ���� - � � ����� ��������� ��������� �� ��������� ��������� ������... � �������� �� ������ ����� ����� ���� �� ��������.";
	STR_MAYOR[3] = "��... �� ������� ���� � ��� ������������. �� �������� ����� � ������� ����� ����������� - ��� ��� ���� ������� ����������.";
	STR_MAYOR[4] = "��� ���������� ��� ������������ �����. �������, �� - ��������� ������� ��� ���������� �����, ������������ �� ����� ���� ��������, ����� ��������� �������� ���� ���. �������� �� ��� ���� ������ �������, � ������ ��������������� ��������� �� �����.";
	STR_MAYOR[5] = "��... �� ������� ���� � ��� ������������. �� �������� ����� � ������� ����� ����������� - ��� ��� ���� ������� ����������.";
	STR_MAYOR[6] = "�-�... ������... ������ ������� ������� ��� ���� �� ����.";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // ����������
	STR_TAVERNKEEPER[0] = "��, � �� �� ������� ���� ��������� ����� ��������. �� ������� ���� �����������, �� ��� �������, ��� ��� ����� ���������� ������� � ����� �������\n�������, ��� �� �������� � ���������������� � �������� - � � ������� � ���� ��� ����� ������ ����� ���������!";
	STR_TAVERNKEEPER[1] = "�� ��� � ��� ����� �������! ��������, �� � ���� �� ����������. � ���� �� ����� �� �����, ������ ��������� �������� � ��������� ������������! ����, ������, �� ������ � ����� ���� ��������.";
	STR_TAVERNKEEPER[2] = "�������� �������� ���. � ���� � ������� ������ ������� ��������, �� � �������� ����� � ������� ��� � �������. � ����� ������� - �� ������ �� �������� � ������� � �� ��������� ������ ������ ����� �������� ��������������� �������.";
	STR_TAVERNKEEPER[3] = "������������ �������. ��� ���� �� ������� ���������, � ������������� ���� ��� ������ ����������. ������ �������, ��� ��� �������� ��������� ���, ��� ���������� � ����� ������. ���� ���� ���������.";
	STR_TAVERNKEEPER[4] = "�� ����, ���� �� ��� � ��� �������. ������� ��� �������. �������� �������, ��������������, � ����� ���� �������� ������ �������.";
	STR_TAVERNKEEPER[5] = "�������, �� ���� ����� ����������. � ������ �������, � ������, ��� �� �� ����� ��������� ����� � ������ ���������� ����� ���� ����. �� � ������� ��������� ����� �� ����������.";
	STR_TAVERNKEEPER[6] = "������� ��������� ��� �� ����. ��� ���� �������� ������� �� ��� ������ ������, �� ��������� ������� ������ � ������ ����������. ����� ���� ���������� ����, �������� ����� ����� �������, � ������ � ��� ���������� ��� ���.";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // ��������
	STR_SHIPYARDER[0] = "������� �� ������ ��������... � ��� � ��������, � ��� ������ ���-���� ������� - �� ����� ���� � ��������. ��������, �������� �������.";
	STR_SHIPYARDER[1] = "������� �� ������ ��������... � ��� � ��������, � ��� ������ ���-���� ������� - �� ����� ���� � ��������. ��������, �������� �������.";
	STR_SHIPYARDER[2] = "�������� �������, �� �������, ��� �� ������� �����. ��������� ���������� ���� ����������. ������� ��� ����� � ���� ��������. ������, �� ������ �� ���, ������� �� ������������.";
	STR_SHIPYARDER[3] = "�� ����� ������������ �������. �������, ��� �� ������ ��������������� � ������, ����� � ���������. � � ����� ������ �������� ����� - ����� �� ����������, � ����������� ����������\n�������, ��� �� �� ������� � ���� ����� �� ������ �����������, � ��� �������� ������ � �������.";
	STR_SHIPYARDER[4] = "��, ���� ������ ��� ������ �� �������. �� ��������� ������ � ��������� ��������, � ������, ����� ��� ���������� ���-������, ����� ��������� ��� �������.";
	STR_SHIPYARDER[5] = "�������� ������. ������ ����� ������, �������� �� ����. ���� �������, ��� � ������� ��� ��������� ���������� �� ������ ����� ���� ��������.";
	STR_SHIPYARDER[6] = "�� ��� �������� � ����� �������, ���� �� ���������, ��� � ���� ������ � ���������������. ����� ����, ��� ��� ��� ������������ �� ������ ����� ������� ���� ��������� ��� ������������ �����, ��� �������� ��� �����������, � ������ �� - ������������ ���� ������ ��������.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // �����������
	STR_TRADER[0] = "������ �������� ������� � ��� ������� �� ����. ��������������� ������, �������� ���������� ����� ������. ������� �� ������, ����� ���-������ ����� ��� ��� ��� �� ���� ������.";
	STR_TRADER[1] = "�� ������� ��������� ������ �����������, � ��� ���� ��� �������� �����. �� ���� �� ���� ����� ������. ��, ��� ���� �� � ��� ��������� ��� ������� �� ���.";
	STR_TRADER[2] = "���� ������� ���������� ����������� ��������� � ����� ������. ����� � ���� ������ ��������, � � �� �������� ������, ����� �� ����-������ ��������.";
	STR_TRADER[3] = "��������� �� �����. �������-�������, � ����� ��������. �� ����� ������� ���, �� ������. � ��� �� ������ ����� �� �������.";
	STR_TRADER[4] = "��������� �� �������, ����. �������, �� ��� ���������� �������� ������, �� ������� ��� � ����� ��������� �������. �� ����, ��� ������ �������� �������, ������� �� �������, �� ��� ������� �� ��� ������ ���������.";
	STR_TRADER[5] = "�! ��� ������� �������, � �� �� ��������� ��� ����� � ��� ������� ���\n�� ������ �������� ������� ������ ������ � ���������! � ������, ������� ��������� � ���� � �������� ������ ������� ��������.";
	STR_TRADER[6] = "�� ����� � ��� ������ ������ � �� �����. �� ������� ���� �����������, � ����� ������ ���� ����. ������� ����� ������, ����������� �� �����.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}