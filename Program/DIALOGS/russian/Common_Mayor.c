// boal 25/04/04 ����� ������ ����
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
												
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // �������� ��������
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // ����� ��� �������� ��� ��� ����������

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool   bOk;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// ��������� ��� �� ����� -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// ��������� ��� �� ����� <--
	// ����������� ��������� ���� ��� ������� ������, ���� ��� ����
	/*if (LAi_IsCapturedLocation && CheckAttribute(NextDiag, "captureNode"))
	{
		Dialog.CurrentNode = NextDiag.captureNode;
		DeleteAttribute(NextDiag, "captureNode");
	}*/
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ������� ���� �������
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // �� �������� �� ������������ ���� :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // ������ ������
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("�� ������� ������� � �����������?! ������ ���...", "��� ��� ����������� ���������, ����� �� ��� �������� ����?! ��� �����������...", "�� ��, ��� ������ ��������� �����, ��� "+ GetSexPhrase("�����-�� ����������","�����-�� �����������") +" ������ � ���� ����������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","��������") +"?! ��� ������� ��� ����� ���� ����, ������ ���� �� ����"+ GetSexPhrase(", ������� �����","") +"!", "�����"+ GetSexPhrase("��","��") +" ������, ��� �� ���� ����������! ������!!", "� �� ����� ����, ������"+ GetSexPhrase("��","��") +"! ����� ���� ������� � �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("�������� ���� ���� �����...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, " + GetWorkTypeOfMan(npchar, "") + ", � �� �� ����� ���� ������� ����!", "��� ��� � ���� �����, ��������: ���� ����, � ������ ����..."));
				link.l1.go = "fight";
				break;
			} 
									
			if (grandfathershit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			if (grandfatherisashiteater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			if (grandfatherhater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
				{
					dialog.text = "��� ���� �����?";
					link.l1 = "����� ���������� � ���� �� ����� ����.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "��� ���� �����?";
					link.l1 = "����� ���������� � ���� �� ����� ����.";
					link.l1.go = "quests";
					break;
				}
				else
				{
					dialog.text = "��� �� � ��� ��������, � �����.";
					link.l1 = "�� � �����.";
					link.l1.go = "Exit";

					if (Pchar.BaseNation == PIRATE || bNoPirateRestrictions)
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "����� ����� ��������� ��� ���� ��������?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "� ���"+ GetSexPhrase("��","��") +" �� ����, �� ��� ����� ������ - 30 000 ��������, ����� �������� ����� �� ����.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "��������, ��� �� ������ � ���"+ GetSexPhrase("��","��") +" �� ����� ������ �� ���������������.";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "���� �������. ������ ���� ������ �� ����� �������� ���������� � �������� �������.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}

					break;
				}	
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 15)
            {
                dialog.text = "�! ��� ������! ��� �� ���"+ GetSexPhrase("","�") +" " + GetFullName(pchar) + ". �� ��� ��� ������� �������� ��������� �� ��������, ����� ��� ������� ��� ����. � ������, ��� ��� ������ ��� � ����������� �����.";
                if (sti(pchar.Money) >= ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000)
                {
                    link.l1 = "� ��� ��� ���� ������� ���� �����������.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "�... �������, ��� ����.";
				link.l2.go = "arest_1";
                /*if (CheckAttribute(NPChar, "NotHaveFort") && GetCharacterShipClass(PChar) <= 3) // to_do
                {
                    link.l3 = "�����������? �� ������? ��� ��� �����! ��, ��� ����� ���. ���� ����� ����...";
				    link.l3.go = "Town_Capture_1";
                } */
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
                              ". � ���������� ������ "+ GetCityName(NPChar.city) + " ���������� " + NationKingsName(npchar)+
                              ". � ������ ������������� �������� ���� ������ ������, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "��� ��� " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
               	//����� homo
            if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "�� ����� ��� ��� ��������, �� ��� ��?";
                        link.l1 = "��� ����� - �� ����� ��� ����� �����������.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "������ ��� ��������, �� � ������ ������ � ���� ��� �������, ����� ������� ���. ��� ��, ��������, ��� ������, �� ���� ������� ������ "+NationNamePeople(sti(aData.nation))+". � ��� ���������� ������������ ������� ������.";
                        link.l1 = "��� � ��� ��� �����"+ GetSexPhrase("","�") +" ���������� ���� ������ � ������� �����.";
                        link.l1.go = "siege_task";
                        link.l2 = "����� �� ����� ��� ����� �����������.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterReputation(PChar, 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                        //--> �����
                        SiegeRumour("������������, ��� �� ������� ��� �������� �� "+NationNameSK(sti(aData.nation))+"�� ������� - � �������� ���� �������! �� ��� ���������� ���, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- �����
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "��, ��� ��, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", ��� ��� ������. ������ ����� ��� ����� ������� - �� �������� �� "+NationNameSK(sti(aData.nation))+"�� �����������. � ���� ���� � ���� �������, ��� ���� ������� "+(sti(aData.iSquadronPower)*1500)+" �������. �������� ��������.";
                        link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ", ������� ����� � ���� ����!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> ���� ������ ����� ������ � �������
						if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 100 && sti(pchar.questTemp.HorseQty) > 5)
						{
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "����������, � ���� ���� � ��� ����, ��.. ��������� ���������� �������.";
								link.l1 = "������ ��� �����������.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- ���� ������ ����� ������ � �������    				
						dialog.text = RandPhraseSimple("�, ��� ����� ��? �� ������ ������� �� ���� ���?",
                                      "����� ��������� ���� �� ��� ���������� �������? ��� ��� ������, " +GetAddress_Form(NPChar)+"?");
        				link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation))+".";
        				link.l1.go = "work";
						
						// Warship ����� "������ �� ����������" - ����� ������� �������
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " � ��������"+ GetSexPhrase("","�") +" �������. ��� " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " ������� ������ � ���� �� �����. ���� ����� �� �������.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "����� ���������� � ���� �� ����� ����.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(���������� � ���� ������)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "� ��� ��������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " ������ ����� " + pchar.GenQuest.CaptainComission.Name + ", ��� � ���� � ��� ����������?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "������ ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ���������� ������� ���� ������ �������.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "������ ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ������ ��� ���� ������.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " � ��������" + GetSexPhrase("","�") + " �������� " + pchar.GenQuest.ShipWreck.Name + " � ��� �������, ���������� �� ����� ������� " + pchar.GenQuest.ShipWreck.BadName + ". " +
										"� ���������, �������� ������� �� ��� ����� �� ��������� ����� �� �� ����. �� � �������" + GetSexPhrase("","�") + " �� �������� � ������. ���� �������������� ����� �� ������ ������� �� � ������� " + (30 - iDay) + " ����, �� �� ����, ������� �� ������� �� ������.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " � ��������"+ GetSexPhrase("","�") +" ������� �� ������������ �������� ����� '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' �� ����� � �� ���������. " + 
										"� ���������, �������� ������� �� ��� ����� �� ��������� ����� �� �� ����. �� � �������" + GetSexPhrase("","�") + " �� �������� � ������. ���� �������������� ����� �� ������ ������� �� � ������� " + (30 - iDay) + " ����, �� �� ����, ������� �� ������� �� ������.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "��� ����� ����� �������� �������� �������.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // ���� �� � ������
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "��� ����� ��������� � ���� ��� ���������� ��������.";
        						link.l4.go = "LoanForAll";//(���������� � ��������� ���������)
        					}
        				}
						//-->> ����� ���������� � ������� ������
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "��� ������� ����� ���� ������. ��� ���.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "���� ����������� ������ � ����. ��� ���������, �� �������� ��� ����� �� ���������� �����.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- ����� ���������� � ������� ������ 
        				link.l7 = "� �� �����"+ GetSexPhrase("","�") +" ������, ��� ������ ��������� �������-���������� " + NationNameGenitive(sti(NPChar.nation)) + ".";
        				link.l7.go = "Where_guber";
        				link.l8 = "�����, �� ������ ������� ����������� �� ������ ���? ���� ���������� �������� ����� �� �����.";
        			    link.l8.go = "Play_Game";
        				link.l10 = "����� �������� ����, �� ���� ���� ����.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		

		//zagolski. ��������� ����� �� ������ ===================================
		case "pirateStartQuest":
			dialog.text = "��... ���������, ��������? � ��� ���� ����� ������, ��� �� �� ��� �������"+ GetSexPhrase("��","���") +". ��� ��� ��� ����� ������� �� �������. ���������� ���-��� ��������� � �������� ���������, � ���� ����� ��� �����, ��� �����������. ����� ����� �� ������, �� ���-��� ���������.";
			link.l1 = "��� � ������. � ��� �� ����?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "������, �� ������� � ��������� �� ����. ������...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "� ���� � ��������� - � ����� ����� ���������� � � ��������� ����� '�������' � �������� 200 �����, ����� ������� �� ������ ���������� �� ��������� ���������. ��� � ����� ��������� �����, � �������� ����������, � ��� ����� ��� ��������, ��� ��� ����� ������ � ��������� �������. ��!.. ������� � ���� �� ��������. � ������� ��������� ���������� ������� ������� � ������, ��� ����� ��� ���������� � ������ ����� - ���� � ������, �� ��� ������ � �����.";
			link.l1 = "� ���? � ����"+ GetSexPhrase("��","��") +" � ��������� ��� ��������� 200 �����, ���� �� �� ������� �������? � ��� ��� �� �������?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "���, �������. ����� � ����� �� ������? ������� � �� ����� � ����� ������. �� ��� ����� ��������������, ��� ����, ������� ��� ����������� - ��� � ���� ��� ������. � �� ������ ������� ���, ��� ��������� ��� ����� ������, � �������� ���� 10 000 ��������. ��������� ��� ������. �� ���, ��������?";
			link.l1 = "������! � ��� ��� ����� ����? ���� �����-�� �����������?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "���. ������ ��������� ����, ��������� ��� � ����� �� 10 000 - ������, �� ��������.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "���� �� � ���� ��� ���� �����, � �������� �� � ��� ����� �����. ��� �� ��� � ���� ������ ��������� �� �����. �� ���� ������ ���������� ������ - ��� ��� ������ � ����� '�������' � � ���� ���������? �� ����� ��� ������ � ��� ��������. ��������?";
			link.l1 = "��, ���� ���-�� �������������� ����������.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "���! ��� ��� � ���. ������� ���� ��������� ����������� � ������� ����� - � ���� ���� �� �������. ��� ����� ����������, � ������ - ��� ������ �� �������. ������ �� ���������, ������ ����� �� ���� �� ���� ������� ����� �� ������? ���� � �� ������, ��� ������� ���������� - ����������� ���� �������. � ��� ����� ����� �� �������...";
			link.l1 = "�������... ������, ����� ����������� ���� � �� ��������� �����. ����������� �� ������.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "�������� �����, ��������? ��� ������� �����... ���� ���� ������ 5000 ��������, ������ � ���� ������ ���. �� ���� ��������� ������� � ���� - ����� � ������ �� ��������� ������! �� ���� ����� ����� �� �������.";
			link.l1 = "����� ���� �����...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "���, �����. ��� ���������� ������.";
			link.l1 = "��� ����� � �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "��! �������� �������! � ��� ������, ��� �� � ���� ����������. �� ��� ������ ������ ���������� ����������.";
			link.l1 = "� ������ ���� ��������"+ GetSexPhrase("","�") +". ���� �������� ���� ������ �����.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "�������, ��� ��������� �������. �� �� �� �����, � ���� �������� ���� ��� ���� ����\n������� - ��� ������� �� ������� ������� ����, ������� ����� �� ������� '�������'. � ������, ��� ������ ���� � ���� ����������, ���� �� � �� �����. ��� ������� ������ � ��������� �������, ���� ������ - ��������� ����� � �������� �������. � ������ ��� �� ���� �� ������"+ GetSexPhrase("","�") +", ������� � ������ ���� �������� ��� ���� ����. ������� 15 000 ��������. ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "������! ������, ��� ��������� ������ ���� ��� ��������.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "������ ���, ������� ��� � ��� �����������... �� � �������. ������, �� � ���.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "�����-�����. ��� ���� ��������� ��� � ��� �������� ���, ��� �� ������� �������"+ GetSexPhrase("��","���") +". �� ��� �, ���� ���� �� �������� ������"+ GetSexPhrase("","�") +", ��� ��������� ������� � 15 000 ��������. � ������� ����, ������� �� ��� �����"+ GetSexPhrase("","��") +".";
			link.l1 = "��� � �������, ���"+ GetSexPhrase(" ���","� ����") +" ������! � ������ ���� ���� ����, � � ��� ����� ��������"+ GetSexPhrase("��","���") +". �� �������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

		
		// Warship ����� "������ �� ����������"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "����� ���������� �������. ��� ����������� �������� � ����� �������� � ���� ��������. � ���������� �������� �� ���� ������. ������ �������, ��� �� �����, ��� ����� ������ ��� ����� ��������� �� ��������. ��, � ��� ���������� �������������� " + FindRussianMoneyString(qty) + ".";
			link.l1 = "�������, ���� ���������. ������ ���"+ GetSexPhrase("","�") +" �������. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "���. �� ������.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // ������� � ��������
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- ����� ��� ������ -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "� ����������� ������ ���, �������.";
			link.l1 = "� ���� �������� � ���������� ������� ������� ������ ��������� � ������� (�������� �������������� ����).";
			if(sti(pchar.reputation) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;	
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// �����_�
				dialog.text = "��������� ���, �����"+ GetSexPhrase("�","���") +"! � ���������� ����� ������ ��������� �������.\n������ �� ������� �����������, � ������������� �����, ���, �����...";
				link.l1 = "���� ���������! � �����"+ GetSexPhrase("","�") +" ��� �� ���� �����...";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// �������� �����
				dialog.text = "��������� ���, �����"+ GetSexPhrase("�","���") +"! � ���������� ����� ������ ��������� �������.\n������ ���������! �� ������ ��������� ��� ������� ������� �� ����������� ������. ��� ������, ��� �� �����������, � �� ����� ������ �������!";
				link.l2 = "������ ��� ��������� ��������������...";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// ������� �������
				dialog.text = "�����"+ GetSexPhrase("�","���") +"! �� ����� �����������, ��� ���� ������ � ���������� ��� ����� ������� �� ����, �� ��� �������, ��� �� ��������� �����������, ������������ � ���� ��� ����������.";
				link.l3 = "���� ���������! �� � ��������"+ GetSexPhrase("","�") +" ��� �������� ���� �����...";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "�������, �� ���� ���������, �� ��� ���������?!! �� ������ ������ �������� ������������ ��� �������! � �� ���� ����������� ������� ������� ������ ������� � ��������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " � ��� ������ �� ��� ���� ������������! �����, �� ������ ����������, ����� ������� � ������ ���������� ������� ������� ��� ����������� ���� ��������?!!";
				link.l1 = "���� ���������! �� ������������� ������ ���� �������������...";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// �������� �����
				dialog.text = "�����-�� ��������� �� ��� �����...\n�� ���� ���� �����������? ���� ������� ������ ���������� � ��������������?";
				link.l2 = "���� ���������! �� ������������� ������ ���� �������������...";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// ������� �������
				dialog.text = "������������ ���������� ������ ������ ����������� ������. �� ��� �, �� ������� ����, ����� ����, �� �������� ��� �� ������������� ������ ������.";
				link.l3 = "���� ���������! �� ������������� ������ ���� �������������...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "��� �� �����, � ����, ����� ���� ����� ���� �������������. ���, �������� �����, ��������� � ����� ������� ���������� �������� ����������. ��������, ��� ���������� �������, �� ������������� ���������� ���������, ���� ��� ������ �����������...";
			link.l1 = "�������, �� ����� �����!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterReputation(pchar, 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // �����_�, ������� �� �������
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "���������� ������. �������� ���� ������ � �������. ��� �������, ��� � ���� ��� �������! ��.. � �������� ��� ����� ����. ������ - �� ���������� ����� ��������� �������� ���������.";
			link.l1 = "�������, �� ����� �����!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterReputation(pchar, 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // ���� �������� �����
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "��, ��������, ��������... ��� ��, � ����� �������, ��� ���� ����������� ������ ����� � �� ���� ���.";
			link.l1 = "�������, �� ����� �����!";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "�� ������ ���� �������! ��� ���� �������� ��� ������ � �����������! ������, ����� "+ GetSexPhrase("����� '�������������'","��� '�����������������'") +"!";
			link.l1 = "�� �� ���!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- ����� ��� ������ -----------------------------
		
		// --------------------------�������� '������'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "� ������ ������ ��� ����������. �� ��� ������� � ������� ����.";
			link.l1 = "��� ���? � � ��� ��� �����������?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "� ���������, ��� �� ����������, � ���������� ����. � ��� ��������� ����������, ��� ��� ����� ��������������, �� ��������� �� ���� ������� ������� - ������������� � ���������� �������� ����� ������ � ����� ������ ��. � ���� �� ������� ��� ����� �� ������ ��������� ���������� �������.";
			link.l1 = "� ��� ����������� ��������������?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "���� �� ������������ ������� ���������, � ������� �������� ������� �������� � ��������� ����, �������� ������������ ����� � ���������� ��������������� ������. " +
				"��������, ��� ���������� ������ �������� �����. � ���� ���� ���������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " �������� " + pchar.GenQuest.CaptainComission.Name + " ������������� �� ���������. ������� � ���� ������� ������� ���� �������� ��� ������ � ��������� ������, �� �� ����� �� �������� � �����.";
			link.l1 = "� ��� �� ���� ������?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "� ���� �� ����� ���� ������� ��������, ������������ ������� ��������� �������, ����� ���������� ������ ��������. ��� ��� ������ ���������� ������ ����������� ������ �������� " + pchar.GenQuest.CaptainComission.Name + ". " +
				"��� ������ �� ����� ������, ������� ���������� ����� �����.\n���� �� ������� ��� ������ � ���� ����, �� ������ ������ � ��� ���� ����� ��� ������ ������������.";
			link.l1 = "������� ���. � ������� ����� ���� ��������� �����, ����� ���������� �������� �������. ��������, ��� ����.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "�������, � �����"+ GetSexPhrase("","�") +" �����������. ������� � ���� ���� �������?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterReputation(pchar, -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "�����, ��� �� ��� ������� ������� ������ � ��� ���, ������� ������� ������������."; 
			link.l1 = "������, � ������ �� ��� ����. ������ ��� ����������� �������� � ��������� " + pchar.GenQuest.CaptainComission.Name + ". ����� ��� ���-�� ������������?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "�������, � ���� ������� �� �����, � ���������� ���������� ����� � ����� ������.";
			link.l1 = "�������. ��������� �����������.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "�����������! � ��� �� ��� ������ ��� ���������?";
			link.l1 = "���� �� ����. ������� ����� �� ��� ��� �� ������.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "��, ����� ����������! ��� �� ���� '��� �� ������' ������� �����...";
			link.l1 = "�� � ��� ���� �������.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "��� ���.\n������!.. ������������� ������������ ������� � �������.\n�� ������ ���� ��������, " + GetFullName(pchar) + ".";
			link.l1 = "��, �������� ����������...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "�����������! � ��� �� ��� ������ ��� ���������?";
			link.l1 = "� " + RandPhraseSimple(RandPhraseSimple("��������","��������"),RandPhraseSimple("���������","�����")) + " ����������� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " � �������� ����� ���� ������� ����, ���� � ������� ������� �������. ��� � ���� ������.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "�������� ������! � ��� ��� " + pchar.GenQuest.CaptainComission.Name + " ? ��� ��������, ��� �� ����� ��� �� �������� �����.";
			link.l1 = "� ���������, �� ����� � ������ � ����������������.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "��� �����... ��� ����� �����, �����"+ GetSexPhrase("���","��") +" " + GetFullName(pchar) + ". � ����� ������� ��� ��������, � ���������, ��� �������, ��������� ��������. " + 
				"�� �� �����, �������� ��� �� ����� ���� �� ��������...\n����, ��������� �� ��������� ���������� �����, ���������� ��������� ������������, �� ��� � �� �������� ���, � �� ���� �� ������������� ����� � ���������. ������� �������������� �� �� ��������... �� � ����� �� ������������� ��� ����� �� ����. ������� ��� ������� - ������ �������� ��� ������� �������� ����. ";
			link.l1 = "��������� ���. ������ ���"+ GetSexPhrase("","�") +" �������.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------�������� '������'-----------------------------
		
		// -------------------------- ��������� "���������������" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("��� �� ���� ��� �������������? �� ����� ����� ���� ��� ������ �������� ����� �� ����� ���������� ����!","������� " + GetFullName(pchar) + ", ���� ������������������ ���� ��������! ������ ������ ���� �������� �� ���� ������?");
				link.l1 = "���� �� ����, ��� ��� �� ��� ��������...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "��� ������� �������! ���� �� ��� �� ��������� ������� " + pchar.GenQuest.ShipWreck.Name + " �����. � ���������� ��������� ������������ ����������. � �������� ��� �������� �������������� �� ���� ������������� � ������� � �� ��������.";
				link.l1 = "���������, ���� ���������. ���"+ GetSexPhrase("","�") +", ��� �����" + GetSexPhrase("","�") + " ������ ��� � ����� �����. ������" + GetSexPhrase("","�") + ", -  ���������� ������ �������.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
		break;
		
		case "ShipWreck2":
			dialog.text = "��� ������ ��� ����� ��������? ����� � ������� ������� �����! � � ����� ������ ������ �� ���������, ����� ������ ���� �����.";
			link.l1 = "���� ���������, �� � �������" + GetSexPhrase("","�") + " �� ���������� ���������. �� �������, ������ ���...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterReputation(pchar, 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- ��������� "���������������" ------------
		
		// ---------------------- ����� ������ � ������� ----------------------------
		case "TakeRing_1":
			dialog.text = "��� ��������, ��� ��, ��� �� ��� �������... "+ GetSexPhrase("����������� ��������","������� � ��������") +". ������� � ����� � ��� ���������� �� �������.\n"+
				"�� ������, ������ ����������, �� � ��� ��� �������...";
			link.l1 = "��, � ����� ����� ���������? ��� � �������, �������� � ��� ����...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "��, �� � �� ����� �������. � ��� ����� ������� � ������� ����������� ������!..";
			link.l1 = "�-�-�, ��� ��������� ��������, ����������.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "��, ���������� �� ���������. ����� ������� ������. �������� �� ��������, � � ������ ������ � ���� ����� ����. � � ������ ������� - ��� �����.";
			link.l1 = "�������... � ��� ��������� �� ����� ��� ��������? �� ���-������ ������ ������� ����� ��� ����� �����?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "���, ���. ������ �� �����...";
			link.l1 = "����. �� ��� ��, ����� ������.";
			link.l1.go = "TakeRing_5";
			link.l2 = "�� ������, " + GetAddress_FormToNPC(NPChar) + ", �, �������, �������� �� ���� ������. ����� ���� ��������...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "����� ������! �� ������� - �� �������� �� ������ ��� �����.";
			link.l1 = "� �����. ����� ���� � ���������.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//����� ������ � ����
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //���� ������ �������� � ������
				Log_QuestInfo("������ ��������� � ������� " + sld.startLocation + ", � �������� " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //����������� ���������� �� ���������� 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "��� ���? ��, �� ������, �� ������... �� ��� ��, ����� ��������, �������.";
			link.l1 = "��������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;

		case "TakeRing_S1":
			dialog.text = "�������, ��� ������������� ���!! �� ��� ������ ����� ������!";
			link.l1 = "�� ��� ��...";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "��� ���� ������ �� ����������� ������. � ������, ��� � ��� ����� ����������!";
			link.l1 = "��, ���� ����� � ����...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //������� ������
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "��� ��� ��!! ���� ������ ����...";
			link.l1 = "��� �����! �� ��� ��, ��� ���� ������.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "��-��, ������� ��� ��������. � - ��� �������! ��� ���� ������ �� ����������� ������.";
			link.l1 = "������� " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //������� ������
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- ����� ������ � ������� ----------------------------

		case "node_1":
            //����� homo
			if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "�� ����� ��� ��� ��������, �� ��� ��?";
                    link.l1 = "��� ����� - �� ����� ��� ����� �����������.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "������ ��� ��������, �� � ������ ������ � ���� ��� �������, ����� ������� ���. ��� ��, ��������, ��� ������, �� ���� ������� ������ "+NationNamePeople(sti(aData.nation))+". � ��� ���������� ������������ ������� ������.";
                    link.l1 = "��� � ��� ��� �����"+ GetSexPhrase("","�") +" ���������� ���� ������ � ������� �����.";
                    link.l1.go = "siege_task";
                    link.l2 = "����� �� ����� ��� ����� �����������.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterReputation(PChar, 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                    //--> �����
                    SiegeRumour("������������, ��� �� ������� ��� �������� �� "+NationNameSK(sti(aData.nation))+"�� ������� - � �������� ���� �������! �� ��� ���������� ���, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- �����
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "��, ��� ��, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", ��� ��� ������. ������ ����� ��� ����� ������� - �� �������� �� "+NationNameSK(sti(aData.nation))+"�� �����������. � ���� ���� � ���� �������, ��� ���� ������� "+(sti(aData.iSquadronPower)*1500)+" �������. �������� ��������.";
                    link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ", ������� ����� � ���� ����!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "��� ����� ������� ��������� ��� ������ ���� � ��������� ���� �� ������ ��������������� ���?";
        			link.l1 = "� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation))+".";
        			link.l1.go = "work";
					
					// Warship ����� "������ �� ����������" - ����� ������� �������
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " � ��������"+ GetSexPhrase("","�") +" �������. ��� " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " ������� ������ � ���� �� �����. ���� ����� �� �������.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "����� ���������� � ���� �� ����� ����.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "� ��� ��������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " ������ ����� " + pchar.GenQuest.CaptainComission.Name + ", ��� � ���� � ��� ����������?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "������ ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ���������� ������� ���� ������ �������.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "������ ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ������ ��� ���� ������.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " � ��������" + GetSexPhrase("","�") + " �������� " + pchar.GenQuest.ShipWreck.Name + " � ��� �������, ���������� �� ����� ������� " + pchar.GenQuest.ShipWreck.BadName + ". " +
									"� ���������, �������� ������� �� ��� ����� �� ��������� ����� �� �� ����. �� � �������" + GetSexPhrase("","�") + " �� �������� � ������. ���� �������������� ����� �� ������ ������� �� � ������� " + (30 - iDay) + " ����, �� �� ����, ������� �� ������� �� ������.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " � ��������"+ GetSexPhrase("","�") +" ������� �� ������������ �������� ����� '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' �� ����� � �� ���������. " + 
									"� ���������, �������� ������� �� ��� ����� �� ��������� ����� �� �� ����. �� � �������" + GetSexPhrase("","�") + " �� �������� � ������. ���� �������������� ����� �� ������ ������� �� � ������� " + (30 - iDay) + " ����, �� �� ����, ������� �� ������� �� ������.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "��� ����� ����� �������� �������� �������.";
        			    link.l3.go = "sell_prisoner";
        			}
        			link.l4 = "� �� �����"+ GetSexPhrase("","�") +" ������, ��� ������ ��������� �������-���������� " + NationNameGenitive(sti(NPChar.nation)) + ".";
        			link.l4.go = "Where_guber";
        			link.l5 = "�����, �� ������ ������� ����������� �� ������ ���?";
        			link.l5.go = "Play_Game";
        			link.l10 = "��� ������ ����� ���������� � ������ �����, " + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			dialog.text = "��, � ����� ���� �� �������������?";
			link.l1 = "����������� � ����� �� �������� �������?";
			link.l1.go = "Card_Game";
   			link.l2 = "�������� ������� � �����-������?";
			link.l2.go = "Dice_Game";
			link.l10 = "����� �������� ����, �� ���� ���� ����.";
			link.l10.go = "exit";
		break;
		
		//  ����� -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "� �� ���� ������ � �������� ���� � ������� ������������!";
    			link.l1 = "��� ��� ����� ������.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "�������! ����� ������� �� ������ ��������... ������ ��������...";
	    			link.l1 = "������������.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "�� ����� �������� ����?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "���, � ���� �������� �� �������. ���� ����.";
	    			link.l1 = "��� ��� ����� ������.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "��� �, ������� ������!";
			link.l1.go = "Cards_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "������� ����������� �� �������.";
			link.l1 = "������ �� 1000 �����.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "������� �� 5000 �������.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ��������������� ������. � �� ���� � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "�������� ������, " + GetAddress_Form(NPChar) + "? � ��� ��� �����!";
                link.l1 = "������.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "���! ����� ���������� � �������, � �� ������� � ����������� � ������� � �����...";
                link.l1 = "����.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 1000 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ��������������� ������. � �� ���� � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
                link.l1 = "������� �� ����� ������ �������?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "��������, ��� ����.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "�������� ������, " + GetAddress_Form(npchar) + "? � ��� ��� 15000 �������!";
                link.l1 = "�����!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "���, ����� ������ �� ������� �� ����� ����� ������.";
                link.l1 = "��� ������.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 5000 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // ����� <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "� �� ���� ������ � �������� ���� � ������� ������������!";
    			link.l1 = "��� ��� ����� ������.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "�������! ����� ������� �� ������ ��������... ������ ��������...";
	    			link.l1 = "������������.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "�� ����� �������� ����?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "���, � ���� �������� �� �������. ���� ����.";
	    			link.l1 = "��� ��� ����� ������.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "��� �, ������� ������!";
			link.l1.go = "Dice_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "������� ����������� �� �������.";
			link.l1 = "������ �� 500 ����� �� �����.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "������� �� 2000 ������� �� �����.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ��������������� ������. � �� ���� � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "�������� ������, " + GetAddress_Form(NPChar) + "? � ��� ��� �����!";
                link.l1 = "������.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "���! ����� ���������� � ������, � �� ������� � ����������� � ������� � �����...";
                link.l1 = "����.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 500 �����.";
			link.l1 = "������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ��������������� ������. � �� ���� � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
                link.l1 = "������� �� ����� ������ �������?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "��������, ��� ����.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "�������� ������, " + GetAddress_Form(NPChar) + "? � ��� ��� 15000 �������!";
                link.l1 = "�����!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "���, ����� ������ �� ������� �� ����� ����� ������.";
                link.l1 = "��� ������.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 2000 ����� �� �����.";
			link.l1 = "������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.snd = "Voice\CHMA\CHMA004";
			dialog.text = "� ����� ������, � ������� ��� �������� ��� ������� � ����� �� ������ ��� ��������.";
			link.l1 = "��, ��, �������, ��������, ��� ����������"+ GetSexPhrase("","�") +" ���.";
			link.l1.go = "exit";
		break;

		case "Where_guber":
            offref = characterFromID(NationShortName(sti(NPChar.nation))+"_guber");

            if (NPChar.location == offref.location)
            {
                dialog.text = "������� �����, ������!! ��� " + RandPhraseSimple("�������", "���������") + " �������-���������� "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                              " ��������� ����� ����� � �������!";
    			link.l1 = "�������. �������� ��� ������������.";
    			link.l1.go = "exit";
            }
            else
            {
                if (bBettaTestMode || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) > rand(5) || CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))// ����� ����� ������
                {
                    cn = FindLocation(offref.location);
                	if(cn < 0)
                    {
                        attrLoc = "error";
                        dialog.text = "��� " + RandPhraseSimple("�������", "���������") + " �������-���������� "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                      " ����� � ������� � ������.";
                    }
                	else
                	{
                	    attrLoc = locations[cn].islandId;
                	    if (attrLoc == "Mein")
                	    {
        			    	dialog.text = "��� " + RandPhraseSimple("�������", "���������") + " �������-���������� "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(" ��������� ������ �� �������� ",
                                            " ���������� ������� ���������������� ������ �� �������� ",
                                            " ��������� � ������� �� �������� ") + " � ������ " + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
						else
						{
						    dialog.text = "��� " + RandPhraseSimple("�������", "���������") + " �������-���������� "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(" ��������� ������ �� ������� ",
                                            " ���������� ������� ���������������� ������ �� ������� ",
                                            " ��������� � ������� �� ������� ") + GetConvertStr(attrLoc, "LocLables.txt") + " � ������ " + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
                    }
        			link.l1 = "�������� �������!";
        			link.l1.go = "exit";
    			}
    			else
    			{
                    dialog.text = "������ ��� � ������ ��������� ��� ������ ��������������� �����? ������ � ����, ��� �� �� �����?";
        			link.l1 = "���, ��� ��. ����� ���� ��������.";
        			link.l1.go = "exit";
    			}
			}
		break;
		//---------------------------- ��������� ������� ���� -------------------------------
		case "work": 
            dialog.text = "��� ���� ���, ��������� ���� � ������� �����.";
        	link.l1 = "������, ��������!";
        	link.l1.go = "exit";
        	// boal ������ �� ��� -->
            if (CheckAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id))
			{
				dialog.text = "���� ���������. ����� ������! ��� ���� �������.";
				link.l1 = "���"+ GetSexPhrase("","�") +" ������� ���.";
				link.l1.go = "GhostShipDone";
				break;
			}
			if (CheckAttribute(NPChar, "from_sea") && Pchar.location.from_sea == NPChar.from_sea)
            {
    			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
                     CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins")  &&
                    GetNpcQuestPastDayWOInit(npchar, "GhostShipHelp") > 30  &&
                    !CheckAttribute(pchar, "GenQuest.GhostShipWorkId")      &&
                    dRand(2) == 1)
                {
                    dialog.text = "��, " + GetAddress_Form(NPChar) + RandPhraseSimple(", ������, ������ ������� ��� �����!! ����� �������� � ����� ������ � �����������. � �� ����, ��� ������!",
                                                       ", �� �������! ��� ��������, ��� � ����� ���� ���. ����� �������� ������. �������� ��� ���������� ��.");
    				link.l1 = RandPhraseSimple("������, �� �����!",
                                               "�! ��� ���� ��� ��� ��, ��� ��� �����!");
    				link.l1.go = "GhostShipHelp_1";
    				break;
                }
            }
            // boal ������ �� ��� <--
			//==> ���� �� �����-���� �����
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> �����, �� �� ���
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("��������� ��� ��������, �� ��� ������ ������� �� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen") + ". ���� �� ��������� ���������� ������, ����� � ��� �� ���.", 
						"��, � �� �� �� � " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Dat") + " ������� �� ���������� ����� ��������� �������� �����������? ��, ������ ���! ���� �� �� ��������� ���� �������������, ������ ������ � ��� �� ������.");
					link.l1 = RandPhraseSimple("�������...", "� �����"+ GetSexPhrase("","�") +", "+ GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";					
					break;
				}
				//<--�����, �� �� ���
				//-------- ���� ����� ����������� ����� ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("������� �� ����� ������� �� ����� " + GetFullName(arName) + " ���� ��� ��������. ����������!", 
								"�� ��� ������ ������� �� ����� ������� �� ����� " + GetFullName(arName) + ". � ��� �����������!", 
								"���� �� ��� �������������� � ���� � ����������, " + GetFullName(arName) + " ������ ����� ����������! ���������� ���������� ����������� �� ��� ���������!");
							link.l1 = RandPhraseSimple("������, " + GetAddress_FormToNPC(NPChar) + ".", "� ��������� ����, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("�����, ������ ��� �� ����� � ����������� �������, �����. � ��� �� �������, ��� ��� �����������? � � ��� ����� - " + GetFullName(arName) + " �� ��� ��� ��� � ������! �������� �����������, " + GetAddress_Form(NPChar) + ".",
								"��� �����, ��������������� ��� ��� ����������� ����� �������� �� ����� " + GetFullName(arName) + ", �����. ������, ��� �����������, ��� �������� ���. � ��� ����?");
							link.l1 = "� �� �����"+ GetSexPhrase("","�") +" ��������� ���� ������� � ���������� �����, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("����, ��� �������? �� ������ ���������� ���������� �������? " + GetFullName(arName) + " ������� ����?", "������� ��� ������ ���� - " + GetFullName(arName) + " ��� ��� �����?");
							link.l1 = "� ���������, ���, " + GetAddress_FormToNPC(NPChar) + ". ��� ������� ��������� ���, �� ���� ��������� ������� � ��� �������� ���������. ����� ��������, ���� ������ ��� �� �� �����.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("����, ��� �������? �� ������ ���������� ���������� �������? " + GetFullName(arName) + " ������� ����?", "������� ��� ������ ���� - " + GetFullName(arName) + " ��� ��� �����?");
							link.l1 = "�� �����, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 60);
							AddCharacterExpToSkill(PChar, "Sneak", 20);
						break;
					}
				}
				//------ ������ ������ ------------>>
				if (QuestName == "SeekSpy")
				{
					switch (pchar.GenQuest.SeekSpy)
					{
						case "":
							dialog.text = LinkRandPhrase("������� �� ����� ���������� ��������� � ������ ���� ��� ��������. ����������!", 
								"�� ��� ������ ������� �� ����� ���������� ������ � ������. � ��� �����������!", 
								"���� �� ��� �������������� � ���� � ����������, ��������� ���������� ������� ��������� ��������������� �����! ���������� ��������� ���������!");
							link.l1 = RandPhraseSimple("������, " + GetAddress_FormToNPC(NPChar) + ".", "� ��������� ����, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("�����, ������ ��� �� ����� ���������, �����. � � ��� �������, ��� ���������� � ��� ���.",
								"��� �����, ��������������� ��� ��� ����������� ���������� ������, �����. ������, ��� �����������, ��� �������� ���. � ��� ����?");
							link.l1 = "� �� �����"+ GetSexPhrase("","�") +" ��������� ���������, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("�� ������ ��������� ���������?", "�������, ��������� ����� ���� ������?");
							link.l1 = "��, � ���"+ GetSexPhrase("��","��") +" ��� � ����� �� ����� ������, ��� �� ��������, � ����"+ GetSexPhrase("","�") +".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 60);
							AddCharacterExpToSkill(PChar, "Sneak", 20);
						break;
						case "FoundSpy":
							dialog.text = RandPhraseSimple("���, �������, �������, ��� ������� ����� � ���� � ���� ���, ���� �� ������?", "���, ���� �� �����, �������� ����� � ���� � ���� ����� ���������� �� �������. ��� � ���� ��������� �����, �������� �� ����?");
							link.l1 = "��, � �� ����� ����. ������ ������, ����� � ���, ��� �������"+ GetSexPhrase("","�") +" ���...";
							link.l1.go = "All_Execute";	
							sld = characterFromId("MayorQuestSpy");
							sld.lifeDay = 0;
							ChangeCharacterAddress(sld, "none", "");
							LAi_SetStayType(sld);
							sTemp = npchar.city + "_town";
							LocatorReloadEnterDisable(sTemp, "gate_back", false);
							LocatorReloadEnterDisable(sTemp, "reload1_back", false);
							LocatorReloadEnterDisable(sTemp, "reload2_back", false);
							AddCharacterExpToSkill(PChar, "Leadership", 60);
							AddCharacterExpToSkill(PChar, "Sneak", 20);
						break;
					}
				}
				//------ ������������� �� ���������� ����� ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("�����, ������ ��� �� �������� ������, �����. � � ��� �������, ��� ���������� � ��� ���.",
									"��� �����, ��������������� ��� ��� �������� ������, �����. ������, ��� � �������, �������� ���. � ��� ����?");
								link.l1 = "� �� �����"+ GetSexPhrase("","�") +" ��������� ������ �������, " + GetAddress_FormToNPC(NPChar) + ".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("������� �� �������� ��� ������ ���� ��� ��������. ����������!", 
									"�� ��� ������ ������� �� �������� ��� ������ ����� � ����. � ��� �����������, ��� ����� ��� ������ ��� ����� �������!", 
									"���� �� ��� �������������� � ���� � ����������, ������ ��� ���������� �� ��� ��� � ����, ��� ������ �� ���������! ���������� ����������� � �������, ��������� ��� ������!");
								link.l1 = RandPhraseSimple("������, " + GetAddress_FormToNPC(NPChar) + ".", "������� ����� ������, "+ GetAddress_FormToNPC(NPChar) + ".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("�� ��������� ��������� ���� ������?", "�������� �� �������, ����� � ���?!");
							link.l1 = "��, � ��� ������"+ GetSexPhrase("","�") +". ��� �� � �������������� - ������ ����� � ����.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				//------ ����������� ������ ------------>>
				if (QuestName == "KillSmugglers")
				{
					switch (pchar.GenQuest.KillSmugglers)
					{
						case "":
							dialog.text = LinkRandPhrase("������� �� ����������� ��������������� ���� ��� ��������. ����������!", 
								"�� ��� ������ ������� �� ����� � ����������� ���������������. � ��� �����������!", 
								"���� �� ��� �������������� � ���� � ����������, �������������� ������� � ����� ��������� ������ ������! ���������� ���������� �� ���������� ������ �� ���� ������������!");
							link.l1 = RandPhraseSimple("������, " + GetAddress_FormToNPC(NPChar) + ".", "� ��������� ����, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("�����, ������ ��� �� ����������� ���������������, �����. � � ��� �������, ��� ���������� � ��� ���.",
								"��� �����, ��������������� ��� ��� ������ � ����������� ���������������, �����. ������, ��� �����������, ��� �������� ���. � ��� ����?");
							link.l1 = "���������, � �� �����"+ GetSexPhrase("","�") +" ��������� � ���������� �����. ��� ������, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							int lngFileID = LanguageOpenFile("LocLables.txt");
							sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.KillSmugglers.shoreId);
							dialog.text = RandPhraseSimple("�� ������ �������� �����������?", "�������, �� ���������� ���������������?");
							link.l1 = "��, � ������"+ GetSexPhrase("","��") +" �� � ����� " + sTemp + " � ���� �������"+ GetSexPhrase("","�") +".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 50);
							AddCharacterExpToSkill(PChar, SKILL_SNEAK, 100);
						break;
					}
				}
				//------ ����� ������ � ���� ------------>>
				if (QuestName == "DestroyPirate")
				{
					switch (pchar.GenQuest.DestroyPirate)
					{
						case "":
							dialog.text = LinkRandPhrase("������� �� ������ ���������� ������� ���� ��� ��������. ����������!", 
								"�� ��� ������ ������� �� ����� � ����������� ���������� �����. � ��� �����������!", 
								"���� �� ��� �������������� � ���� � ����������, ������ �������� ��������� �������� �������! ���������� ���������� �� ���������� ������ �� ���� ������������!");
							link.l1 = RandPhraseSimple("������, " + GetAddress_FormToNPC(NPChar) + ".", "� ��������� ����, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("�����, ������ ��� �� ����� � ����������� ������, �����. � � ��� �������, ��� ���������� � ��� ���.",
								"��� �����, ��������������� ��� ��� ������ � ����������� ���������� �����, �����. ������, ��� �����������, ��� �������� ���. � ��� ����?");
							link.l1 = "���������, ��� �� ������� ��������� ������� � ���������� �����. ��� ������, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("������� ��� ������ ���� - ���� ��������� ����� ��� ��� �����?", "�������, ���� ������ ����� ��� ��� ���?");
							link.l1 = "�� � ��� ������� - ���������, � ��� ������� �� ���, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Execute";	
							AddCharacterExpToSkill(PChar, "Leadership", 50);
							AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 50);
							AddCharacterExpToSkill(PChar, SKILL_SNEAK, 50);
							//����� ������� ���������
							for (i=0; i<5; i++)
							{
								Group_DeleteGroup("MQGroupAll_" + i);
							}
						break;
						case "Found":
							dialog.text = RandPhraseSimple("����, ��� �������? �� ������ ��������� �������? ���� ����������� ����� ������� ����?", "������� ��� ������ ���� - ��� ����� ��� ��� �����?");
							link.l1 = "� ���������, ���, " + GetAddress_FormToNPC(NPChar) + ". ��� ������� ��������� �������, �� ���� ��������� �������, � ��� �������� ���������. ����� ��������, ���� ����� ��� �� �� �����.";
							link.l1.go = "All_Found";		
						break;
						case "PirateIsOut":
							dialog.text = RandPhraseSimple("��� ��������, ��� �� �������� ������ � ���� � ��� ���. ������ ����������?", "��� ����� ��������, ��� �� ���� ��� ������-�� ����� � ��������� �����. ��� ��� ��� � ��� ���������?");
							link.l1 = "� ��������"+ GetSexPhrase("","�") +" ��������� �������, � �� �������� � ��������. �� � ���������, " + GetAddress_FormToNPC(NPChar) + ", ������ ������ �������� � ����� ���. ��� ����� ����...";
							link.l1.go = "All_Found";		
						break;
					}
				}
				//<<------ ������ ������ ------------
				break;
			}
			//==> ������� ��������
			sTemp = npchar.city;
			if (CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp) && sti(pchar.GenQuest.MayorQuestsList.(sTemp)) > (5 + rand(5)) && !CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) )
            {
                dialog.text = "�� ����� ������ ����������� �� ����� ����� ������, " + GetAddress_Form(NPChar) +
                              ". � ���� ����������������� �� ��� ����� �������-������������. � ���� ���� ���������� ������ ��� ��������� ������ " + NationNameGenitive(sti(NPChar.nation))+".";

    		    link.l1 = "������������. � ������ �����"+ GetSexPhrase("","�") +" �������� ������ "+ NationNameGenitive(sti(NPChar.nation))+".";
    			link.l1.go = "Patent_Give";
    			if(isMainCharacterPatented())
				{
				    link.l2 = "��� ����� �� �����. � ��� ������ �� ������ � ������� �����������!";
				}
				else
				{
    			    link.l2 = "���. ��� ��� ���������� �� ���������.";
    			}
    			link.l2.go = "exit";    			
    			pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
				break;
			}			
//navy -->
			//����� ���
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if  (GetCharacterSPECIALSimple(PChar, SPECIAL_C) >= dRand(11))   i = -1;       //WW   ������� ����� ���������� ������ � ���
			if (i != -1)
			{
				dialog.text = "���, �� ������� � ���� ������� ������ ���. ��������� �������� " + GetFullName(&Characters[i])
					+ ". ������� ������, ����� ���-�� ��������.";
				link.l1 = "��, ����!!! �� �����...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if (rand(10) > 9 && !bBettaTestMode)             // WW     � 20 ��������� �� 10 ���������   ������ ���������  ��������
				{
					dialog.text = LinkRandPhrase("������ � ���� ��� ������ ��� �����, ��� ��. ������� ������, ��� ��...", 
						"�������� ��������� ��� ��� � ���� ������� ���. �������� �����, ����� ����-������.", 
						"������� ������ ��� ������, ��� � ��� �� ��� ��������. ���� ��� ������ ��� � ������ ����.");
					link.l1 = "� �����"+ GetSexPhrase("","�") +", " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "exit";
				}
				else 
				{
					// boal 02.09.06 -->
					if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
                    {   // ���� ��� ������� � ���� ������, �� ��� ���� ������� �� ������ �� ����� - �������� � ��������, ���������� �� �����, ���� ������� ������ ����, �� � ���, ���� ��� �� ���������
                        i = 3;
                    }
                    else
                    {
                        //�������� ����������� ���� ����� ������ � ������
						if (npchar.city == "Panama") i = rand(2);							
						else {  i = dRand(4);                                                //   0-5  ��������� �����
						       //if  (IsCharacterPerkOn(pchar,"Trader"))                       i = dRand(4); 
                        	   //if  (IsCharacterPerkOn(pchar,"Adventurer"))	                 i = dRand(4);			
						       if ((IsCharacterPerkOn(pchar,"Grunt")) && dRand1(3) >= 1)      i = dRand2(1);  
							   if ((IsCharacterPerkOn(pchar,"Fencer")) && dRand1(3) >= 1)     i = dRand2(1);    // ����� ��� ��������
							   if ((IsCharacterPerkOn(pchar,"Buccaneer")) && dRand1(3) >= 1)  i = dRand2(2);
							   if ((IsCharacterPerkOn(pchar,"Agent")) && dRand1(3) >= 1)      i = dRand2(1)+2;  //  � ����� �����  ��� ���������
							   if ((IsCharacterPerkOn(pchar,"SeaWolf")) && dRand1(3) >= 1)    i = 4;        //WW   �� ������
							 }
                    }         
                    // boal <--
					switch (i)
					{					
						//========== ����� ����������� ����� ============
						case 0:
							pchar.GenQuest.DestroyGang.Terms = dRand(2) + 2; //����� ���������� �������
							pchar.GenQuest.DestroyGang.Money = ((dRand(8) + 2) * 170) + (sti(pchar.rank) * 200 + 2000); //��������������
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //��� ������� � ��������� ������	
							dialog.text = "������ ������ � ���� ���� ��� ��� �������. � �������� ���� " + XI_ConvertString("Colony"+npchar.city+"Gen") + " ��������� ����� ����������, � ��� ��������, ��� �������� � ��� �������� ����� " + GetFullName(arName) + ". �������� � ���������� ��� ����� �����������.";
							link.l1 = "� �����-�� ������� ���������"+ GetSexPhrase("","�") +" � ������?";
							link.l1.go = "DestroyGang";
						break;
						//========== ������� ��������� ============
						case 1:
							pchar.GenQuest.SeekSpy.Terms = dRand(2) + 3; //����� ���������� �������
							pchar.GenQuest.SeekSpy.Money = ((dRand(8) + 2) * 150) + (sti(pchar.rank) * 200 + 2000); //��������������
							dialog.text = "��, ������ � ���� ���� ��� ��� ������������� ���������. � ������� ���������� � ���, ��� � " + XI_ConvertString("Colony"+npchar.city+"Dat") + " ��������� ��������� ��������. ��� ���������� ��� ���������.";
							link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ", � ����������, ���������� ����, ����������?";
							link.l1.go = "SeekSpy";
						break;
						//========== ���������� �� ��������� ����� ============
						case 2:
							pchar.GenQuest.Intelligence.Terms = dRand(10) + (42 - MOD_SKILL_ENEMY_RATE); //����� ���������� �������
							pchar.GenQuest.Intelligence.Money = ((dRand(4) + 6) * 1000) + (sti(pchar.rank) * 1000 + 10000); //��������������
							pchar.GenQuest.Intelligence.City = GetSpyColony(npchar); //���������� �������
                            sTemp = ", ��� �� " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "� ���� ���� ��� ��� �������, ����������� � ��������� ������. ��� �����, ����� �� ���������� � " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc") + sTemp + ", ����������� ��� � ��������� ��������� � ��������� ��� ��, ��� �� ��� ����.";
							link.l1 = "��, �� ������"+ GetSexPhrase("","�") +" ��, ��� � " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " ����� ���� ���� ������...";
							link.l1.go = "Intelligence";
						break;
						//========== ����������� ��������������� ============
						case 3:
							dialog.text = "���� ��� ��� �������, ��������� � ����������������. � ��������� ����� � ������ ��������� ������������ ��������: � ��������� ����� �������, �� ����������� � ��������� ����� �� ���������� ������ ���. ����������, ������ ���������������... ����� ���� �������� �����.";
							link.l1 = "��� � ����"+ GetSexPhrase("��","��") +" �������?";
							link.l1.go = "KillSmugglers";
						break;
						//========== �������� ������, ��� ������ ���� ============
						case 4:
							//--> ������� ���� 
							if (sti(pchar.rank) > 6) 
							{
								if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE);
								else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE/2);
							}
							else
							{	//�������� ������� ���� �� ������ ����
								if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
								else iRank = 1;
							}	
							//<-- ������� ���� 
							LAi_group_Delete("MayorPirateGroup");
							sld = GetCharacter(NPC_GenerateCharacter("MQPirate", "", "man", "man", iRank, sti(npchar.nation), -1, true));							
							SetCaptanModelByEncType(sld, "pirate");
							DeleteAttribute(sld, "Ship");
							SetShipToFantom(sld, "pirate", false);
							sld.Ship.Mode = "Pirate";
							//sld.ShipTaskLock = true; //����� ����
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyPirate_Abordage";
							sld.DeckDialogNode = "DestroyPirate_Deck"; 
							sld.DontRansackCaptain = true;
							sld.DontCheckFlag = true;  // �� ��������� ���� ��
							sld.SaveItemsForDead = true; // ��������� �� ����� ����
							sld.DontClearDead = true; // �� ������� ���� ����� 200�
							sld.AlwaysSandbankManeuver = true;
							sld.WatchFort = true; //������ �����
							sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
							sld.greeting = "pirat_common";
							LAi_group_MoveCharacter(sld, "MayorPirateGroup");
							dialog.text = "��, � ���� ���� ��� ��� �������. ���� � ���, ��� � ����� ���� " + XI_ConvertString("Colony"+npchar.city+"Gen") + " �������� ��������� �������. ��������� �������� ����� ��� ���� ���������. ����� ����������, ��� ������������ �� ����� ������ ������ ���������� �� � ��������� �����, �� � ����� �������� ����� �������. ������, �������...";  
							link.l1 = "� ��� � ����"+ GetSexPhrase("��","��") +" �������, " + GetAddress_FormToNPC(NPChar) + "?";
							link.l1.go = "DestroyPirate";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("������� � ��� ������ �� ���� ���������� � �������� ������.", "�� ������� ������ ��� ��� ��� ���.", "�� ������� ��� ���, ������ ���. ��� ������� �� ������ ������ - ������.");
				link.l1 = RandPhraseSimple("����...", "��, ����� ����, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
			}
		//---------------------------- ��������� ������� ���� -------------------------------
		break;

		case "Patent_Doubt":
			dialog.text = "������ �������... ��� ������ �� ��� �������� �� ���� ���� ��������. ����� ����������� ������� ���� ���, ������ ������ �� ����� ���������� ������� ������� � ���������� ����� ������. ��� � ����, � ������� ��� ������, ";
			link.l1 = "�� �� ���������, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Patent_Give";
			link.l2 = "��! ��������! ��� ���� ���� �����, � �� ���� ����� ������ ������ � ����� ��������� ������������.";
			link.l2.go = "arest_3";
		break;
		case "Patent_Give":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
            pchar.PatentPrice = 0;
			dialog.text = "����������, ������� �� ���������� ��������������. ������ �� ������ �������� ������ �������-�����������. � ���� ����� ������� ����� ��������� ������� ��� ���.";
			link.l1 = "�������. ��������, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
		break;

		case "sell_prisoner":
            dialog.text = "���� �� ������ ��������� �� �����?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ������ ������ ��������
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "������.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "����, ��� ������� " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // ���� ������� �� �����������
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " � ����� �������� ���������������� �� " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " � ���� ���� �� ����� ���������� " + FindRussianMoneyString(qty) + ". � �� ����� �� ������ �������.";
                    /*if (CheckAttribute(NPChar, "from_sea"))
                    {
                        link.l2 = "�������? � ���� � �� ��� ������������?";
			            link.l2.go = "sell_prisoner_DeathExec";
			        } */
                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " �� ����� �������� � ���� ��������� �� ����� " + FindRussianMoneyString(qty) + ".";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "�� �����. �� ��������� ���, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "���. �� ������.";
			link.l3.go = "exit";
		break;

        /*case "sell_prisoner_DeathExec":
			dialog.text = "���, ��� ���������!";
			link.l1 = "�� �, ������, ����� � ����� ������ ���� ��� ����� �� ���?";
			link.l1.go = "sell_prisoner_DeathExec_1";
			link.l2 = "�� ����� ��������� ��� � ������� ��� �������...";
			link.l2.go = "sell_prisoner_3";
		break;

		case "sell_prisoner_DeathExec_1":
			dialog.text = "��... ���������� �����. ��� �, 3000 ������� - � ��� �������� � ����, ��� ��������� �����. �� ������: ���� ������� ����� �� ������ �������� ��������, � ��������� ������ ������.";
            if (sti(pchar.Money) >= 3000)
            {
			    link.l1 = "� ��������. ��� ��� '�����'.";
			    link.l1.go = "sell_prisoner_DeathExec_2";
			}
			link.l2 = "���. � ���������"+ GetSexPhrase("","�") +".";
			link.l2.go = "exit";
		break;

		case "sell_prisoner_DeathExec_2":
            AddMoneyToCharacter(pchar, -3000);
            offref = characterFromID(pchar.prisonerToSellId);
            DeleteAttribute(offref,"prisoned"); // ���������� ��������
			RemovePassenger(pchar, offref);
        	offref.location = "";
        	OfficersReaction("bad");
        	ChangeCharacterReputation(pchar, -5);

        	AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
        	AddCharacterSkill(pchar, SKILL_SNEAK, 0);

            Pchar.GenQuest.Death_Execution_location = NPChar.from_sea;
            DialogExit();
			NextDiag.CurrentNode = "First time";

			DeathExecutionStart(offref, sti(NPChar.nation));
		break;   */

		case "sell_prisoner_3":
			dialog.text = "��� � ������.";
			link.l1 = "����� ��������.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterReputation(pchar, -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // ���������� ��������
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // ���, ��� ��������

            // fix �� ������� 5 ��� �� ��� -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "�� ��� ��� �������. ��� ��� ��� �����?";
                Link.l1 = "��, �����, ����"+ GetSexPhrase("��","����") +" �������.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // ������ ������ ����� ��������� � �������
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix �� ������� 5 ��� �� ��� <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // � ����-�� ���, ������ � ���� ������
                dialog.Text = "����� ����������� ��������! ����� �������� ������������ �� �����, � ��� �� ������������!";
                Link.l2 = "� �� ��������� ������� ��� �� ��� �������. ������� ���, � �� ������� ���� �����.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // ���� �������� �����
            }
            else
            {
				dialog.Text = "�� ���� ��� ���� �����, �� ������, ��� ����� �������� ���� �������, � �� ��� ������� ����� �� ���������.";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //��������������� ������
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "�������� ���! ���� ����� ������ ����������� ���, � ���� ������� � �������� �� �������� � �������� �������. ��, �����, �������� ��� ������ � �������� �� �������.";
	    				}
	    				else
	    				{
	    					Link.l1 = "���� ����� ������ ����������� ���, � ��� ��� �������� - � ���� ���"+ GetSexPhrase("","�") +". ��, �����, ������� ����� ��������.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "������ �������? ��... ������� ��� - � �� ������� ���� �����.";
				}
				else
				{
	            	Link.l2 = "�������...����.. ������� ��� - � �� ������� ���� �����.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //�� ���� ��������� �������
	            {
					// ����������� ����� �������
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "��� ����������� ��������! ��� �� ������� ������� �� �������, ������������� " + NationNameGenitive(sti(NPChar.nation)) + "?! �� ������ ��������� �� �����, ������������ �������� ����, � �� �����, ���������� ����� �������.";
	                Link.l1 = "� ����� ������� ������� ����������� ���, � ���� ���-�� ���������� � ���� ����������, �� ���������� �������� �� ������.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "� ����������� �������� " + NationNameGenitive(sti(PChar.nation)) + " � ���������� �������, ��� ������ ��� ������� ����������� " + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "��� ������� �������� ������� ������. ���� �� �� ������ �������������, �� �� ��������� ��� �������� ����� � ����� �����, � ��� ������� �� ��������� �������.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ������
            RepairAllShips();
            Log_Info("��� ������� ���������������.");
            //  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  �� <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterReputation(GetMainCharacter(), -20); // ������ ��, �� � ��� ������
            dialog.Text = "�� ���� ��� ���� �����, �� ������, ����� �������� ���� �������, � �� ��� ������� ����� �� ���������.";
			Link.l1 = "�������� ���! ��� ������� ������ ����������� ���, � ���� ������� � �������� �� �������� � �������� �������. ��, �����, �������� ��� ������ � �������� �� �������.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "��� ��� �� ���� ��� �����?";
            Link.l1 = "������, ��� �� � ������"+ GetSexPhrase("","�") +"...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // ���� �����
		    {
				// ������ ������ ����� ��������� � �������
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "��� ������ ������ �� ��������, ��� ����������� �� ���� �������. ��������� ���� �������� ������ � ���������� �������� ���� ����� �������.";
            Link.l1 = "��������� �����������.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  �� <--
        break;

        case "Summ_patent":
            dialog.Text = "������, �� ������ ��������� ���� �������...";
            Link.l1 = "��, �� ����� ����������. ��� ��� ������?";
            Link.l1.go = "Summ";
            ChangeCharacterReputation(GetMainCharacter(), -10); // �� �� ������
        break;

        case "City_nation":
			dialog.Text = "��� �, �� �������� �� ������� �����������.";
			Link.l1 = "������� ��� ��������� �������� ������� ������, ��� ����������, ��� �� ����� �������� ��������� �������� ��������. ��������.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterReputation(GetMainCharacter(), 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // ����� ����� ������� ������ � ��������
            PChar.questTemp.DontNullDeposit = true;    // ���� �� ������ ����������
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // ��������
            //  �� -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  �� <--
			AddTitleNextRate(sti(PChar.nation), 1);  // ������� ������
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// ������ �� ����, �� �������� OtherChar - � ��� �����, �� �� � ��� ����
            UpdateRelations();

            // 22.03.05  fix ������ ������ ����� ��������� � �������
            //  ������ ������� �� ��������
            SetReturn_Gover_Dialog_Exit(NPChar);

			/*   to_do
            ref rFortCh = FindSiegeFortCommander();
            if (rFortCh.id == FortChref.id)//��� � ���� ���� ���������� ��������
            {
                if (sti(Characters[GetCharacterIndex("NatCapitan_1")].nation) == sti(rFortCh.nation)) //��� ���� �� �����
                {
                    AddDialogExitQuest("CheckFortsEndSiege_02");
                }
            }
			  */
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "��� ��� �� ���� ��� ����, �������"+ GetSexPhrase("","��") +"?";
			/*Link.l1 = "�� ����� ���, ������ �������.";
			Link.l1.go = "Strike";
			if (!CheckAttribute(NPChar, "NotHaveFort"))
			{
			    Link.l2 = "�� ��������� ����� ������������� � ����� ��� �����������.";
			    Link.l2.go = "Death_Execution_1";
            }       */
            Link.l3 = "���������"+ GetSexPhrase("","�") +", ��� ���� ����������� ��������. ��, � ������ ��� ����!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "�������? ��� �� ���� ��� �������������?";
            link.l1 = "� �����, ����� � " + ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000 + " ������� ����� ���� ������?";
			link.l1.go = "arestFree_2";
			link.l2 = "�����, ��� ����. ����� �������.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(7))
            {
    			dialog.text = "�������, ����� ������� ��� �������� ����� ��������.";
    		    link.l1 = "������������!";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
    		    AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
            }
            else
            {
    			dialog.text = "���! ���� ��������� ����� �������� ������ ������������ ��������. ������! �������� �"+ GetSexPhrase("��","�") +" � ����.";
    		    link.l1 = "��������!";
		  
		   
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 10);
            }
		break;

		case "arest_1":
			dialog.text = "������� ����, ��� ��������. ������! ����� �"+ GetSexPhrase("��","�") +"!";
		    //link.l1 = "��������!";
		    //link.l1.go = "arest_2";
		    link.l1 = "��, �� ���!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "������ ���� ���� ������! ������!";
			link.l1 = "��, �� ���! ������ ��� �� ���� �� ��������!";
		    link.l1.go = "fight";
/*			
            Pchar.GenQuest.Death_Execution_location = NPChar.from_sea;
            DialogExit();
			NextDiag.CurrentNode = "First time";

			DeathExecutionStart(Pchar, sti(NPChar.nation));
*/			
		break;   

		case "arest_3":
			dialog.text = "������! ����� �"+ GetSexPhrase("��","�") +"!";
			link.l1 = "��, �� ���! ������ ��� �� ���� �� ��������!";
		    link.l1.go = "fight";
/*			
*/			
		break; 		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	����������� �����
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "�����������. �� ���������� ����� ������� � ��� ��� " + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", ���� �������������� �� ����������� ������ ����� ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
			link.l1 = "������, � ������ �� ��� �������.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "��... ���, �������, � ��������.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //��� ������
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //���������� �������,��� �����
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id ����, ����� �����, ��� ��� �����
			if (pchar.GenQuest.DestroyGang.Location == "none") //�� ������ ������
			{
				dialog.text = "���������, � ������ ����� � ��������� �������! ���� � ���, ��� ��� ����� ��� �������� ������� ������ �������. ��� ��� � ������� �������.";
				link.l1 = "�������. �� ��� ��, ����� ����.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "�� ��� ��, �����������! ��� ��� � ���� � ���������� � ������������ ������.";
				link.l1 = "�������, ��� �� �������� ��� ����� �����, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //���� ���������� ������ ���� ������� �� �����
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> ����������� � ��������� ������� �� ����� 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	������ ���������
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "SeekSpy":
			dialog.text = "��, � ���� ���� ��������� �� ��������. �� ���������� ����� ������� � ��� ��� " + FindRussianDaysString(sti(pchar.GenQuest.SeekSpy.Terms)) + ", ���� �������������� �� ����������� ������ ����� ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.SeekSpy.Money)) + ".";
			link.l1 = "������, � ������ �� ��� �������.";
		    link.l1.go = "SeekSpy_agree";
			link.l2 = "��... ���, �������, � ��������.";
		    link.l2.go = "All_disagree";
		break;
		case "SeekSpy_agree":
			//(rand(1))
			bool boko = (rand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))     //WW 
			if  (IsCharacterPerkOn(pchar, "Fencer") || IsCharacterPerkOn(pchar, "Grunt") || boko)   //WW 
			{  			
				if (rand(100)<10)
				{//����� ������ �� ������
					pchar.GenQuest.SeekSpy.Location = npchar.city + "_town"; //���������� �������
					pchar.GenQuest.SeekSpy.City = rand(1); //���� ����� � ������, ���� - ��� ����� ������������ � �������
				}
				else
				{//����� � ����� �� ����� ������� common
					pchar.GenQuest.SeekSpy.Location = GetSpyLocation(npchar); //���������� �������
					Log_QuestInfo(pchar.GenQuest.SeekSpy.Location); //���
				if (pchar.GenQuest.SeekSpy.Location == "none") //�� ������ ������
				{
					dialog.text = "��������, � ����������, ��� ����� ��������� ��������������� ��������, ���� �� �����, ��� � ��� ��� ����� �����. ���������� � ����� ������� ��������.";
					link.l1 = "����. �� ��� ��, ����� ����.";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
					break;
				}
				else
					{
						pchar.quest.SeekSpy_login.again = true; //�� ������ ������
					}
				}
			}
			else
			{	//����� ������ �� ������
				pchar.GenQuest.SeekSpy.Location = npchar.city + "_town"; //���������� �������
				pchar.GenQuest.SeekSpy.City = rand(1); //���� ����� � ������, ���� - ��� ����� ������������ � �������
			}
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "SeekSpy"; //��� ������
			dialog.text = "�� ��� ��, �����������! ��� ��� � ���� � ���������� � ������������ �������.";
			link.l1 = "�������, ��� �� �������� ��� ����� �����, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.GenQuest.SeekSpy.MayorId  = npchar.id; //Id ����, ����� �����, ��� ��� �����
			pchar.quest.SeekSpy.win_condition.l1 = "location";
			pchar.quest.SeekSpy.win_condition.l1.location = pchar.GenQuest.SeekSpy.Location;
			pchar.quest.SeekSpy.win_condition = "SeekSpy_login";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.SeekSpy.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.SeekSpy.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.SeekSpy.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	������������� �� ���������� �����
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "� �������. ��������, �������������� � " + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + " ������ ��� ��� ������� ��������.";
			link.l1 = "��, ��� ������� ������... � ������ �� ��� �������.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "��... ���, �������, � �������� - ������� ������.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //�� ������ ������
			{
				dialog.text = "����, � �� ���� �������, ��� ���� �������� ��� � ������ ����... �������, � �� ��� ��� ��� �������.";
				link.l1 = "�-��, ������... �� ��� ��, ����� ����.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //��� ������
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id ������ ������ � ������
				dialog.text = "���������! ������ �� ����. � " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " ��� ���������� ��������� �������� " + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					", ��� ����� " + GetFullName(&characters[GetCharacterIndex(sTemp)]) + ". ��� �� �������� ��� ���, � �������� ����� ����������. �� �������� ����� ������ ����� ��� � ���� � ��� ��� " + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + ". � ������ � ����, ��� ��� ����� ������� ����. � ������ ������ ����������� � ������, ����� �� ����� ���������� ���� ����� � �� ������ �� �������. ��� ��� ����?";
				link.l1 = "��, � ��� �����"+ GetSexPhrase("","�") +", " + GetAddress_FormToNPC(NPChar) + ". ���������� ��������� � ���������� �������.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id ����, ����� �����, ��� ��� �����
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //������ ���� ��������� ������
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("��� �������. ������, �� �� ��������� � ���������� �����, ������� � �������� ��������� ����� ������ ��������������. ��� ������� ������ ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". �������� ��������.", 
				"��� ������. ������ �� �� ��������� � ���������� �����, � � ���� ��� ������ ������. �� ������� ��� �����, ������� � �������� ��������� ����� ������ ��������. ����, � ��� �� ��� ������� ��� ���������� �������������� - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". �������� ��������.");
			link.l1 = "�� ������"+ GetSexPhrase("","�") +" ��, ��� ��� ��� �������, ��, � ����� ������, ������������� ����� ������������� ���� ��������. ������� � ��������� �� ����, " + GetAddress_FormToNPC(NPChar) + ".";
		    link.l1.go = "All_Execute_1";
			//--> �����
			AddSimpleRumour(RandPhraseSimple("�� ������, ���������� " + GetFullName(npchar) + " �� ����� ������� �������������� ������� �������� " + GetMainCharacterNameGen() + ".", 
				"���������� " + GetFullName(npchar) + " �� ����� ������� ��������� " + GetMainCharacterNameDat() + ", �"+ GetSexPhrase("��","�") +" ��������"+ GetSexPhrase("","�") +" ��� ���������, �� �� �����"+ GetSexPhrase("","�") +" � ������������� �����..."), sti(npchar.nation), 5, 1);
			//<-- �����
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	����������� ������
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "KillSmugglers":
			pchar.GenQuest.questName = "KillSmugglers"; //��� ������
			pchar.GenQuest.KillSmugglers.Terms = rand(2) + 1; //����� ���������� �������
			pchar.GenQuest.KillSmugglers.Money = ((rand(8) + 2) * 200) + (sti(pchar.rank) * 200); //��������������
			dialog.text = "����� � ���������� ���� ���������������, ����������. �� ���������� ����� ������� � ��� ��� " + FindRussianDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)) + ", ������� ����� ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)) + ". �� �������� �� ��� ����?";
			link.l1 = "��, " + GetAddress_FormToNPC(NPChar) + ", ������.";
		    link.l1.go = "KillSmugglers_agree";
			link.l2 = "���, �������, �� ���� �����������...";
		    link.l2.go = "All_disagree";
		break;
		case "KillSmugglers_agree":
			dialog.text = "�� ��� ��, ���������. � ����� ������, � ��� �� ��� ������� ��������.";
			link.l1 = "�������, ��� ������ ��������, " + GetAddress_FormToNPC(NPChar) + ".";
		    link.l1.go = "exit";
			pchar.GenQuest.KillSmugglers.MayorId  = npchar.id; //Id ����, ����� �����, ��� ��� �����
			pchar.GenQuest.KillSmugglers.Areal = GetArealByCityName(npchar.city); //�����, ��� ����� ����������
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (sld.id == "Rand_Smug01" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(sld.location)]))
				{
					pchar.quest.KillSmugglers.win_condition.l1 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l1.character = "Rand_Smug01";
					pchar.quest.KillSmugglers.win_condition.l2 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l2.character = "Rand_Smug02";
					pchar.quest.KillSmugglers.win_condition.l3 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l3.character = "Rand_Smug03";
					pchar.quest.KillSmugglers.win_condition = "KillSmugglers_after";
					break;
				}
			}
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.KillSmugglers.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	����� � ����������� ������
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyPirate":
			pchar.GenQuest.questName = "DestroyPirate"; //��� ������
			pchar.GenQuest.DestroyPirate.Terms = dRand(3) + (15 - MOD_SKILL_ENEMY_RATE); //����� ���������� �������
			pchar.GenQuest.DestroyPirate.Money = ((dRand(5) + 5) * 500) + (sti(pchar.rank) * 200); //��������������
			sld = characterFromId("MQPirate");
			dialog.text = "��� �����, ����� �� ��������� � ���������� ����� ������. �������� ���, �������� �� ������� - ��� ��� �����. ��� ���� �����, ����� ���� ��������� ������, ���������� � ������� �����, �� ����� �������� " + XI_ConvertString("Colony"+npchar.city+"Gen") +
				". �� ���������� ����� ������� � ��� ��� " + FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)) + ", ���� �������������� � ������ ������ ��������������� � ������� " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)) + ". ����, �� �������� �� ��� ����?";
			link.l1 = "��, " + GetAddress_FormToNPC(NPChar) + ", ������.";
		    link.l1.go = "DestroyPirate_agree";
			link.l2 = "���, �������. ��������� �� �������� � �� ����...";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyPirate_agree":
			dialog.text = "�� ��� ��, ���������. ����� �����.";
			link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ".";
		    link.l1.go = "exit";
			pchar.GenQuest.DestroyPirate.MayorId  = npchar.id; //Id ����, ����� �����, ��� ��� �����
			pchar.GenQuest.DestroyPirate.Areal = GetArealByCityName(npchar.city); //�����, ���� ����� ������� ������
			AddDialogExitQuest("DestroyPirate_Begin");
		break;
		// -------------- ����� ����� ��� ���� ������� ���� ------------------
		case "All_disagree":
			dialog.text = "�� ��������������� ����!";
			link.l1 = "����� ��������, " + GetAddress_FormToNPC(NPChar) + ", �� �� ��� ���� � ������� �� ����.";
		    link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("��, ��� � ���� ������� - ����� �����. � ����������� �� ���, � � ����� ������� �������� �����. � �����������.", 
				"�-��, ����������, � ����������� � ��� ��������... � ���� � ���������� ������ ����� ������, �������� ��������� ����� ���������, � � ������ ����� �� ���. �-��...");
			link.l1 = "��������, " + GetAddress_FormToNPC(NPChar) + ", � ������ ���, ��� ���.";
		    link.l1.go = "exit";
			//--> �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + GetFullName(npchar) + " ����� ��������� ��������� " + GetMainCharacterNameDat() + ". �������������, ��� �� ����� ��������� ��� ���������!", 
				"���������� " + GetFullName(npchar) + " ��������� ��������� ���, ��� ����� ������� " + GetFullName(pchar) + " ������ �� ����, �� �� ����� ��������� ��� � ����. ��������...", 
				"� ������, ��� ���������� " + GetFullName(npchar) + " ����� ��������� ����, ������� " + GetFullName(pchar) + ", ��� ��� �� �� ������ ��������� ��� ������� � ������������� ����."), sti(npchar.nation), 5, 1);
			//<-- �����
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //������� �������
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //����� ��� ���� �� ����
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("� ������ � ����! ������ ��������� ����, �� �� ������������ � ����������� ���� � �������� ������������� - ���, ������ ��, ���� �������������. � �����������!", 
				"�-��, ����������, � ����������� � ���. ���� ����� ����, ����� ����� �� ����������. � ���� � ���������� ���������� ���������� �����������, ������� ��������� ������ ���� ������. ������ � �������� � ����?..");
			link.l1 = "��������, " + GetAddress_FormToNPC(NPChar) + ", �� � �� ���� ��������� ����������� ������ ��� �����������.";
		    link.l1.go = "exit";
			//--> �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + GetFullName(npchar) + " ����� ��������� ��������� " + GetMainCharacterNameDat() + ". �������������, "+ GetSexPhrase("�� �������� ��������� ������","��� ��������� ��������� ��������") +"!", 
				"���������� " + GetFullName(npchar) + " ��������� ��������� ���, ��� ����� ������� " + GetFullName(pchar) + " ����"+ GetSexPhrase("��","���") +" �� ����, �� �� �����"+ GetSexPhrase("","�") +" ��� ��������� ��-�� ����������� ���������������. ��-��, ����� �������� ��������!", 
				"� ������, ��� ���������� " + GetFullName(npchar) + " ����� ��������� ����, ������� " + GetFullName(pchar) + ". �������, �� �������� ����"+ GetSexPhrase("","���") +"..."), sti(npchar.nation), 5, 1);
			//<-- �����
			ChangeCharacterReputation(pchar, -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //������� �������
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //����� ��� ���� �� ����
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("���������� �������! �� ��� ��, ���� �������� �����. ��� ������� ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". �������� ��������.", 
				"�����������! ��� ����� ����� ��� ����... ����, ��� ������� ��� ���������� �������������� - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". �������� ��������.");
			link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("������� ����� � ���� ����!", "� ������� �������"+ GetSexPhrase("","�") +" ��������� ��������������.");
		    link.l1.go = "All_Execute_1";
			//--> �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + GetFullName(npchar) + " ����� ������ �� ���������������� ���"+ GetSexPhrase("���� ��������","�� �������") +" " + GetMainCharacterNameGen() + ".", 
				"���������� " + GetFullName(npchar) + " ����������� �������� " + GetMainCharacterNameGen() + ", �"+ GetSexPhrase("��","�") +" ����� ��������� ��� ��� ���������. ����������� ������� ��� �����������, � ��� �����...", 
				"� ������, ��� ���������� " + GetFullName(npchar) + " ����� ������� ����, ������� " + GetFullName(pchar) + ". �� ������������� ��� ��� ����������� � ��������������� �������. ������� ��� �������, �������..."), sti(npchar.nation), 5, 1);
			//<-- �����
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("��, ��� � ������. ������ �������� �� ��� ���, ��������, � ����� ��� ��� ������.", "�� ��� ��, ���������! �������, � ���� ��� ���������� ��� ������ ��������� ����.");
			link.l1 = RandPhraseSimple("�������.", "���������.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 50);
			OfficersReaction("good");
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //������� �������
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //����� ��� ���� �� ����
			// ��������� � ���� ������� �����
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- ����� homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "� ����� ������� ����� ����� ������ ����� ��� ���. �� ��������� ���� ������ - �������� ��� �������� �������, � �� ������ �������������.";
			link.l1 = "��� �� ����� �������.";
		    link.l1.go = "exit";
		break;
		//  boal �� ��� -->
		case "GhostShipDone":
            SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");
            
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddMoneyToCharacter(pchar, 5000 + rand(10) * 1000);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -20);
			sTemp = npchar.City;
   			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;

            OfficersReaction("good");
			DeleteAttribute(pchar, "GenQuest.GhostShipWorkId");
			DeleteAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id);
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

		case "GhostShipHelp_1":
            SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");
			pchar.GenQuest.GhostShipWorkId = NPChar.id;

			bDisableFastReload              = true;

			SetLocationCapturedState(NPChar.Default, true);

			Pchar.quest.GhostShipHelp.win_condition.l1          = "location";
    	    Pchar.quest.GhostShipHelp.win_condition.l1.location = NPChar.from_sea;
    	    Pchar.quest.GhostShipHelp.win_condition             = "GhostShipHelp";

			Pchar.GenQuest.Hunter2Pause            = true;

			ReOpenQuestHeader("GhostShipQuest");
			AddQuestRecord("GhostShipQuest", "help_t1");
			AddQuestUserData("GhostShipQuest", "sCity", GetCityName(npchar.City));
			
   			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> �� ������ ������
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[dRand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //���� ���� ����� �� �������� ������
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //��������� �����
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != npchar.City)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}
