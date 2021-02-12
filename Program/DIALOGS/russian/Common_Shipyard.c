// boal 08/04/06 ����� ������ �����
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	int iShipClass = GetCharacterShipClass(PChar); // ���� ������� ���, ������ 7 (�����)
	int iRank = sti(PChar.rank);
	int iSumm;
	
	ref rRealShip;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // ����� ��������
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	// ��������� ������� �� ����� -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// ��������� ������� �� ����� <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // ������ ������, �� ������ ������, ����� ������������.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "Master_Ship";  // ����� ��� �������, ����� ��� ��-�� LoadSegment
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("� ������ ������� �������, ���� ����� ����! �� ����� ����� � �� �� ���� ����� �������������.", "��� ��������� ������ ����� �� ������ � ������� ����. � �� ����� � ������������� � ����� �� ����!", "����, "+ GetSexPhrase("��������","�������") +", ���� ������� �� ������� �� ���� ������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","��������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����"+ GetSexPhrase(", ������� �����","") +"!", "�����"+ GetSexPhrase("��","��") +" ������, ��� �� ����� ����! ������!!", "� �� ����� ����, ������"+ GetSexPhrase("��","��") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, " + GetWorkTypeOfMan(npchar, "") + ", � �� �� ����� ���� ������� ����!", "���, " + GetWorkTypeOfMan(npchar, "") + ", � ��� ���� �� - ������� ������! ��� ��� � ���� �����, ��������: ���� ���� � ������ ����..."));
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
			NextDiag.TempNode = "First time";
			
			//homo ������� �����
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
                                    "��� ������ ���, ����� ����.",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
                Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = "��� ����� ������ ������... ����� ����� ������� � ����� �����.";
    				Link.l2.go = "Blood_Shipyard1";
                }
				break;
            }
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = TimeGreeting() + "! � "+ GetFullName(NPChar) + ", �������� ���� �����.";
				Link.l1 = "���"+ GetSexPhrase("","�") +" ����������. � ������� " + GetFullName(Pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				//--->> ����� ������� ������ �� �����
				//���� ������
				if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 7 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 25)
				{
					dialog.text = "����������, � ���� ���� � ��� ���� ������ ����. �������, ������� ��� ������...";					
					link.l1 = "������� ���������, ��� �� ����.";
					link.l1.go = "ShipyardsMap_1";
					SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
					break;
				}
				//<<--- ����� ������� ������ �� �����			
				
				dialog.Text = pcharrepphrase("�, ��� ����� ��? �� �� �����, ������ �� ������.",
                                        TimeGreeting() + ", ��� � ���� ������ ���, " + GetAddress_Form(NPChar) + "?");
				Link.l1 = pcharrepphrase("���-���, � ����� - �� �������.",
                                        "����� ��������������� �������� �����.");
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY || NPChar.city == "Caiman") 
				{
					link.l11 = "��� ����� ������ �� �������.";
					link.l11.go = "Cannons";
				}	
			    link.l12 = "���� �������� ������� ��� �������.";
			    link.l12.go = "SailsGerald";
				Link.l2 = "� ������ ���� ����������.";
				Link.l2.go = "quests"; //(���������� � ���� ������)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "� �����"+ GetSexPhrase("","�") +" �� ���������� � ���� � ����� ����������.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //����� ���� - �� ����� � ����� �������
				{
					link.l7 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> ����� ����.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "������, � ���� ���� ���� ����� - ��������. ��� ����� ������������� �� �������. ������� ������� ���? � �������.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- �� ����� ����.
				//�������� ���������� ������ ������� ������ �� �����
				if (CheckCharacterItem(pchar, "ShipyardsMap") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.Id") && pchar.questTemp.different.ShipyardsMap.Id == npchar.id)
				{				
					link.l6 = "� ��������"+ GetSexPhrase("","�") +" ���� ���������. ������ �� ����� " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " � ����.";
					link.l6.go = "ShipyardsMapOk_1";
				}
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "� �� ������ ����� ������...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "��� ����� ����.";
				Link.l9.go = "exit";
			}
		break;
		
		case "Meeting":
				dialog.Text = "������, � ��� ������� � ����� ��������. ��� ����� � ����� �������.";
				Link.l1 = "�����������, " + GetFullName(NPChar) + ". ������� ��������� ��, ��� �� ������ ��� ����������.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "��� ����� ������ �� �������.";
					link.l13.go = "Cannons";
				}	
				link.l12 = "���� �������� ������� ��� �������.";
			    link.l12.go = "SailsGerald";
				Link.l2 = "� ������ ���� ����������.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "� �����"+ GetSexPhrase("","�") +" �� ���������� � ���� � ����� ����������.";
					link.l3.go = "LoanForAll";//(���������� � ���� ������)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //����� ���� - �� ����� � ����� �������
				{
					link.l7 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> ����� ����.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "������, � ���� ���� ���� ����� - ��������. ��� ����� ������������� �� �������. ������� ������� ���? � �������.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- �� ����� ����.
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "� �� ������ ����� ������...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "��� �� ������ ������� � ��������� ���� ����������?";
						link.l10.go = "ShipLetters_6";// ���������  "��������� ���������"
					}		
				}	
				Link.l11 = "� ����"+ GetSexPhrase("��","��") +" ����. ��������� ���.";
				Link.l11.go = "exit";
		break;
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "�����-�� ��������� ! ���, ������� � ���� �� ���. �����, ��� ����� ����� � ���������� �����.";
				link.l1 = "����������....";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "�����-�� ���������, �������! ���! ��� �� ������� ��������� ����� �������� �����, ����� �������, ������ �������� �������. � ������, �� ����� ���������� ��� �������, � ���� �������� �����������.";
				sTemp = sTemp + "�����, ��� ���� ��� ���������� " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " ������� �� ��� �����";
				dialog.text = sTemp;
				link.l1	= "�������, �� ����� ...";
				link.l1.go = "exit";
				link.l2 = "���������, " + GetFullName(NPChar) + "! ����������� ������ ������ �����.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","�"));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "������ ��� �����������.";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���� ��������.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "��, �������, ������� ��� �������! ��� ���? �������, �� ����������? �� ����� �����, ��� �������, ���������. ����� � � �� ������� �����? ����� ������ ��������... ����� �������, �������, � ��� ����� �� ������, ��� ���� � ���� ���� �� ����. ���! ��� �� ��-������ ������� - ��� � ����, ���� �...\n����, � ��� �� �� ���� �� ���������, ���� �� � ������ � ��� ����� �� ������� � ����� �������������� ���������... �� �� ��� ����������... ��������� ������, �����... � �������.";
			link.l1 = "�������, �� ���� � ������ ���, �� � �� �� �������"+ GetSexPhrase("��","���") +" �� ��������...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "�� ��� �� ���������?.. � ��� ���� ���� ����? ����? ���, ����� ����� - ��������, ����� � ���������...\n��... � ������ �������������� ����, ��� � ����� - ������� ����������.";
			link.l1 = "�������. � ������� � ��������. ���-�� ��� ������������, ��� ��� �� ���� �� �����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "�, ��� �� � ���� "+ GetSexPhrase("��� �������, ������� ������","�� �������, ������� ��������") +", ����� �������� ���� � ������� ��������?";
				link.l1 = "��, ��� � �����"+ GetSexPhrase("","��") +" �� �������.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "�-�, ����"+ GetSexPhrase("��, �����������","���, ���������������") +". ������ ������� ����?";
				link.l1 = "��, �� ��, ����� �������, �� ������������� �������� �� ������ ��.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "� ����� ��� ����������, ��� �� �������� �� ���� � ��������������� ��������� � ������� ��� � ������ ����� �� ����� ���������� ��������. ��������� ������������� ���, ��� ����. ������� ��� �������� ����� � ������� �� ���� �����.";
			link.l1 = "��������� ���, ��� ���� ������� �������� ���� ������� �����.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "����� �������������?! �� ��� �������������?! ���� ����, ��� ���� ������� ��� ������� ��������� ��� ������, ��� ��� � ����������� ����� �����! �� � � ��� ���� ��� ��� ���� ������. � ��, ���, �����������! � �����������, ���, ����� �� �������, � ���� �������� �����-�� ������ ���������, ������ �������, � ������������� ������������� �����������!";
			link.l1 = "��, ������ �� �� ������ � ��������� �������?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "����� ����� �������?! � ����� �������� �� ��������? ��������, ����� �������, � ���� ��... �������! ������ ��� ������ ���� ������� � ����� ����� ��������, �� � ������ �����������. �������� �� ������������� ������ ������� � ����� ���������� ����� �������. �� ����� ��� ������� �������������. ��������.";
			link.l1 = "��� �, � ��� �� �������...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","�"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		case "shipyard":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("������ ����? � ��� �� ���� �������? � ����� ��� ���!",
				                                                     "������� ��������, ���� �� �������� ����! � ����� ��� ������ �������!"),
													  pcharrepphrase("� �� ���� ������ ������� � �����, ������� " +GetFullName(pchar)+ ". �������, ��� �� '������� ���������'?",
													                 "�������, ������� ������� ����� � �����. ������������ ������� � ���������."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"����� ������������!!! �����, ������ �������, ��� ��������!",
				                                                 "� �� �����"+ GetSexPhrase("","�") +" ��� �������� " +GetFullName(npchar)+ ", ������� �� ������ ������� �������."),
												  pcharrepphrase("���. ��� ������� ���������� Black Perl. ��� ��� �� �������? ��-��! �����!",
												                 "������� �� �����, ����������� �� ������������."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("������ ����? � ��� �� ���� �������? � ����� ��� ���!",
				                                                     "������� ��������, ���� �� �������� ����! � ����� ��� ������ �������!"),
													  pcharrepphrase("� �� ���� ������ ������� � �����, ������� " +GetFullName(pchar)+ ". �������, ��� �� '������� ���������'?",
													                 "�������, ������� ������� ����� � �����. ������������ ������� � ���������."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"����� ������������!!! �����, ������ �������, ��� ��������!",
				                                                 "� �� �����"+ GetSexPhrase("","�") +" ��� �������� " +GetFullName(npchar)+ ", ������� �� ������ ������� �������."),
												  pcharrepphrase("���. ��� ������� ���������� Black Perl. ��� ��� �� �������? ��-��! �����!",
												                 "������� �� �����, ����������� �� ������������."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "������� ���� ������� ����� " +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", ��������� ����� ���� ����� " +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", ���� ����� ���� �������� ������� �� ���������.";
							  
			    link.l1 = "������� ����� ����.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "���������� ����� ����.";
			    link.l2.go = "SailsGeraldChoose";
			    
				// ������ ��
				if(!CheckForFlyingDuchmanSails(PChar))
				{
					link.l3 = "�������� �������� �������."; // �������� �������� ������, ���� ����� ������ ��
					link.l3.go = "SailsTypeChoose";
					link.l4 = "� ���� ���������� ����������� ������, ��� �� ����������� �������-��������!";
					link.l4.go = "FlyingDutchmanSails";
				}
				else
				{
					link.l4 = "� ���� ������ ����������� ������.";
					link.l4.go = "FlyingDutchmanSails_Clear";
				}
				
			    Link.l9 = "� ���������"+ GetSexPhrase("","�") +".";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("������ ����? � ��� �� ���� �������? � ����� ��� ���!",
				                                                     "������� ��������, ���� �� �������� ����! � ����� ��� ������ �������!"),
													  pcharrepphrase("� �� ���� ������ ������� � �����, ������� " +GetFullName(pchar)+ ". �������, ��� �� '������� ���������'?",
													                 "�������, ������� ������� ����� � �����. ������������ ������� � ���������."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"����� ������������!!! �����, ������ �������, ��� ��������!",
				                                                 "� �� �����"+ GetSexPhrase("","�") +" ��� �������� " +GetFullName(npchar)+ ", ������� �� ������ ������� �������."),
												  pcharrepphrase("���. ��� ������� ���������� Black Pearl. ��� ��� �� �������? ��-��! �����!",
												                 "������� �� �����, ����������� �� ������������."));
			    link.l1.go = "exit";
			}
		break;
		
		// Warship 16.06.09 ������ ��
		case "FlyingDutchmanSails":
			if(iShipClass < 4)
			{
				iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // ���� �� ��������� �������
				dialog.text = "��, � ��� ��� �������� ���������� ��������� ������: �� ���������� ������, ����� �������� � ���� �������� ������� �����. ���, ������, ����� ������ �� �������� �����. �����, ��� ������ ������� ����� �������� ����� ������ " + FindRussianMoneyString(iSumm) + ".";
				
				if(sti(PChar.money) >= iSumm)
				{
					Link.l1 = "�������! ���� ��� ����������.";
					Link.l1.go = "FlyingDutchmanSails_SetDuchman";
				}
				
				Link.l2 = "����� ���������� ����! �������� �� ����.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "�� ����� ����� ����� ������ ����� ��������� �������. �������� ����� ������������ �������...";
				Link.l1 = "���� ������, ���� ��������-��...";
				Link.l1.go = "exit";
			}
		break;
		
		case "FlyingDutchmanSails_SetDuchman":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // ���� �� ��������� �������
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "������������. ��� ������� � ������ ����.";
			Link.l1 = "�������.";
			Link.l1.go = "exit";
			
			SetShipSailsFromFile(PChar, "ships/parus_common_torn.tga"); // ������ ��
			
			WaitDate("", 0, 0, 0, 0, 10);
		break;
		
		// ������ ������ ��
		case "FlyingDutchmanSails_Clear":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // ���� �� ��������� �������
			
			dialog.text = "��, ������ ��� ������. ��� ��������� ���� � " + FindRussianMoneyString(iSumm) + ".";
			
			if(sti(PChar.money) >= iSumm)
			{
				Link.l1 = "�������! ���� ��� ����������.";
				Link.l1.go = "FlyingDutchmanSails_SetNormal";
			}
			
			Link.l2 = "����� ���������� ����! �������� �� ����.";
			Link.l2.go = "exit";
		break;
		
		case "FlyingDutchmanSails_SetNormal":
			rRealShip = GetRealShip(sti(PChar.Ship.Type));
			
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // ���� �� ��������� �������
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "������������. ��� ������� � ������ ����.";
			Link.l1 = "�������.";
			Link.l1.go = "exit";
			
			DeleteAttribute(rRealShip, "EmblemedSails.normalTex")
			
			WaitDate("", 0, 0, 0, 0, 10);
		break;
		
		case "SailsTypeChoose":
			dialog.text = "����� ����� ��� �������� ������? � ���� ������ ������ �� ��������� '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + "'.";

            Link.l1 = GetSailsType(1) + ".";
			Link.l1.go = "SailsTypeChooseIDX_1";
			Link.l2 = GetSailsType(2)  + ".";
			Link.l2.go = "SailsTypeChooseIDX_2";
			Link.l3 = GetSailsType(3)  + ".";
			Link.l3.go = "SailsTypeChooseIDX_3";
			Link.l4 = GetSailsType(4)  + ".";
			Link.l4.go = "SailsTypeChooseIDX_4";
			
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
			
		    Link.l99 = "� ���������"+ GetSexPhrase("","�") +".";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "� ���� ������ ������ �� ��������� '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) +
			              "', �� ������"+ GetSexPhrase("","�") +" ��� ����� '"+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+
						  "'. ��������� ������ " + FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) +". ������?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "��.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "���.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "������������! ��� ������� � ������ ����.";
		    Link.l9 = "�������.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 0, 10);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "����� ���� ������? ���� " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = SailsColors[i].name;
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "� ���������"+ GetSexPhrase("","�") +".";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "�������, ����� ������ �����.";
			    Link.l9 = "������.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "������������. ������ ������ � "+ GetStrSmallRegister(SailsColors[sti(NPChar.SailsColorIdx)].name) +" ����.";
		    Link.l9 = "�������.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 0, 10);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "� ���������, �� ���� ������� ������ ���������� ����.";
				    Link.l9 = "����.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "�������, ����� ������ �����.";
			    Link.l9 = "������.";
				Link.l9.go = "exit";	
			}
		break;
		// ����� ������� ������ �� �����
		case "ShipyardsMap_1":
			dialog.text = "��� ����� ��������� ���� ������ ������. ����� ������ ������...";
			link.l1 = "��. ��� �� ������ � ��� ��� �����?";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			pchar.questTemp.different = "ShipyardsMap";
			pchar.questTemp.different.ShipyardsMap = "toTarget";
			pchar.questTemp.different.ShipyardsMap.Id = npchar.id; //������������
			pchar.questTemp.different.ShipyardsMap.city = findShipyardCity(npchar);
			pchar.questTemp.different.ShipyardsMap.what = LinkRandPhrase("�������", "������", "�������");
			pchar.questTemp.different.ShipyardsMap.chance = rand(5); //�������� �������
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = false; //�� ����� ����� �� ������
			}
			else
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = true; //����� ����� �� ������
			}
			pchar.questTemp.different.ShipyardsMap.sklad = rand(3)+1; //������� ����� �������� �� ������ �� �������� �����
			pchar.questTemp.different.ShipyardsMap.fightQty = 2 + rand(3); //���������� ������ �� �����
			dialog.text = "��� ����� ��������, ��� �� ����� " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " ������� ��������� ��������� " + pchar.questTemp.different.ShipyardsMap.what + ". ��� ����� ������, �� ������� ������� ������.";
			link.l1 = "� ��� � ����"+ GetSexPhrase("��","��") +" �������?";
			link.l1.go = "ShipyardsMap_3";
		break;
		case "ShipyardsMap_3":
			dialog.text = "�������� ��� ���. �������� ����������� � ���, ��� ������, ����� ��� ��������, ��������� ��������� �� ���� � ������� �����. � ���� ���� ������ - �� ��� �����.";
			link.l1 = "� ��� �� �����������?";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "��, � ��������� ��������� ������ ���. ��� �� ��� �������� - ���� ��������. �� ��� ������ � ����� ����� ���������, ���� ������ ����� �������� �� �������������� �������� ���������� � ������� ����������.";
			link.l1 = "��� ��� ������?";
			link.l1.go = "ShipyardsMap_5";
		break;
		case "ShipyardsMap_5":
			dialog.text = "���� ������ ����� ����� ��������������� �������, � ������� ��� ����������, �� ����� ����� ���������� ������. � �������� ������ ������ �������� ����� �������... �� ���, �� �������� ������� �� ��� ����?";
			link.l1 = "���, ��� ��� �����������. �������� '���� � �����' ������� ��� ������������� �������.";
			link.l1.go = "ShipyardsMap_disagree";
			link.l2 = "�����, ��� ����� ���� ��������. ������!";
			link.l2.go = "ShipyardsMap_agree";
		break;

		case "ShipyardsMap_disagree":
			dialog.text = "��, �� ��� ��, ����� ����.";
			link.l1 = "��� ����...";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		case "ShipyardsMap_agree":
			dialog.text = "�� ��� ��, ����� ����� ���. � ���� ����� ��� � ������������. � ������ �� ����� �� ����������.";
			link.l1 = "�������...";
			link.l1.go = "exit";
			sld = ItemsFromID("ShipyardsMap");
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.ShipyardsMap.city + "_Shipyard";
			sld.startLocator = "item1";
			sld.ShipName = pchar.questTemp.different.ShipyardsMap.what;
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //����������� ���������� �� ���������� 
			ReOpenQuestHeader("ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "1");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Dat"));
			AddQuestUserData("ShipyardsMap", "sShip", pchar.questTemp.different.ShipyardsMap.what);
		break;

		case "Allarm":
			dialog.text = "�� �� ������"+ GetSexPhrase("��","��") +"! �� ��� �� ��� �������?! ��, �������, ������ ���� ��� �������. � ��, ������, �������� ������!";
			link.l1 = "������?..";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			AddCharacterExpToSkill(pchar, "FencingLight", 10);
			AddCharacterExpToSkill(pchar, "Fencing", 10);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 10);
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=sti(pchar.questTemp.different.ShipyardsMap.fightQty); i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "Allarm_1":
			dialog.text = "�� ���, �������� ��� �������"+ GetSexPhrase("","�") +"?! � ��, ������, �������� ������!";
			link.l1 = "������?..";
			link.l1.go = "fight";
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "ShipyardsMapOk_1":
			sTemp = pchar.questTemp.different.ShipyardsMap.what;
			dialog.text = "�������! ��, ������� ���������, ��� �� ��� �� �������� " + strcut(sTemp, 0, strlen(sTemp)-2) + "...";
			link.l1 = "��������.";
			link.l1.go = "ShipyardsMapOk_2";
		break;
		
		case "ShipyardsMapOk_2":
			TakeItemFromCharacter(pchar, "ShipyardsMap");
			switch (sti(pchar.questTemp.different.ShipyardsMap.chance))
			{
				case 0:
				dialog.text = "���-���... ��, �������� ��� ��������. ������ ��������� � ��� ���� �� ����. ��, �������, ������ �� �� ����������.";
				link.l1 = "�� ���������� ��, ��� ������ �� �����. ������ ��� � ��� � ������"+ GetSexPhrase("","��") +". � �� �� ���������� � ���� ��������!";
				link.l1.go = "ShipyardsMapOk_3";
				break;
				case 1:
					dialog.text = "��, ���� ������ ����� ������������ ��������. � ����� ��������� ��� �� ���� " + FindRussianMoneyString(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ". ������ ��������� ����������� ��������. �� ����������?";
					link.l1 = "���, �������! ���������!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry17", makeint(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)/100));
				break;
				case 2:
					dialog.text = "��, ���� ������ ����� ������������ ��������. � ����� ��������� ��� �� ���� " + FindRussianMoneyString(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ". ������ ��������� �������� ��������. �� ����������?";
					link.l1 = "���, �������! ���������!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry5", makeint(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)/200));
				break;
				case 3:
					dialog.text = "��, ���� ������ ����� ������������ ��������. � ����� ��������� ��� �� ���� " + FindRussianMoneyString(4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ".";
					link.l1 = "���������!";
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 4:
					dialog.text = "��, ���� ������ ����� ������������ ��������. � ����� ��������� ��� �� ���� " + FindRussianMoneyString(6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)) + ".";
					link.l1 = "���������!";
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 5:
					dialog.text = "�! ��� �����, ����� ������ ������! � ����� ��������� ��� �� ���� 60 000 �������. ������ ��������� ���������� ���������. �� ����������?";
					link.l1 = "���, �������! ���������!";
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "chest", 4);
				break;
			}
		break;

		case "ShipyardsMapOk_3":
			dialog.text = "���, �� ��� � ������ ������ �� ���� ���������. ��������, �� ��� ������ ��� �� �����.";
			link.l1 = "��, � �� ������ ��� �������� �������, �� ������� ���������� �� ����.";
			link.l1.go = "ShipyardsMapOk_4";
			link.l2 = "������� ��� ������! ����� ���� �����!";
			link.l2.go = "Allarm_1";
		break;
		case "ShipyardsMapOk_4":
			dialog.text = "������� ���� ���������, �� ����� �������� ����� ��� ���-������ �� ������. ���� ������ ������ �� �����.";
			link.l1 = "� ��� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "3");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = "�������� ��������. ������� ��� �� ����������� ������.";
			link.l1 = "�� �� �� ���...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			AddQuestRecord("ShipyardsMap", "4");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "iMoney", sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			CloseQuestHeader("ShipyardsMap");
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		
        ////////////////////////////////////////////////homo ������� �����/////////////////////////////////////////
        case "Blood_Shipyard1":
			dialog.text = "���, ��, ��� ������� �� ����, ��� ��� ���� � ����� ��� ����� � ����� �����, ������.";
			link.l1 = "����... ��� ����, ��... �� ����, ��� - �������� �������... ��, ������� �� ��� - ��� ����� ����������������..";
			link.l1.go = "Blood_Shipyard2";
			link.l2 = "��� ������� ���� - ����������, ������ ���������� ���� ����� ��� ����� �� ������� ������.";
			link.l2.go = "Blood_Shipyard3";
			link.l3 = "�� � ��� �������. �� �����... �������� ���� ������� ������� - ����� ���� ����� � ������, ������...";
			link.l3.go = "Blood_Shipyard4";
		break;
		
		case "Blood_Shipyard2":
			dialog.text = "�������? ��� ����, ������� �� ����� ���� �������, � ��������������� ������, ����� ������� � ����� �����? �� ���� ������������, ������?..";
			link.l1 = "� � ������ �� ����, ���! � ����� ����, ���, ������� ������. ��, ���... ��, � ���� � ����. �����. ��.";
			link.l1.go = "Blood_Shipyard5";

		break;
		case "Blood_Shipyard3":
			dialog.text = "� ��� �� ��� ���������?";
			link.l1 = "��� ����... ���, ����� ��� � ...! ������.";
			link.l1.go = "exit";
			CloseQuestHeader("PirateQuest");
			Pchar.questTemp.CapBloodLine.ShipForJack = false;

		break;
        case "Blood_Shipyard4":
			dialog.text = "�� ������ �������, ������ �����... �� ��� ��?";
			link.l1 = "�-�-�... ��, ��... ������. �� ��� ������?";
			link.l1.go = "Blood_Shipyard6";
		break;
		
        case "Blood_Shipyard5":
			dialog.text = "��� �, � ��� ������ �� ���� ���. ���-�� � ������ ��������� ������� �� ����� ���� ������. ���������� � ���, �� ������ ��� ����� � ���� ������.";
			link.l1 = "�������� ����������. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard6":
			dialog.text = "��� �� ��������� ���������, � � ��� ������. �� ����, ��� ��� ������� ������� �� ����, ��� ��������� � ��������� ��������. �� � ������ ����� ��� ����� '��������� � �������'. �������� ��������, � �������� �����... ����.";
			link.l1 = "���?! �� �� ������ �� ���� �� ����������... ��, � ����� � ��� ������.";
			link.l1.go = "Blood_Shipyard7";
		break;
		
        case "Blood_Shipyard7":
			dialog.text = "������ �� �� ���������� ���� - ����� ��� ��������. �������� ���� ������� ������, �� ����� ������� � �������� ��������, ������� ��������� ������ �������. ��, ������ - ��� ���� ���������� ���������� � ��� ������. ������� �� ����� � �������, �, ���� �����, ������� ����, ������� �������� � ��� ������ � ����� �� ���... ��� � ����, ��� ��� ��� ���������...";
			link.l1 = "��� �������?.. ��� ����?";
			link.l1.go = "Blood_Shipyard8";
		break;
		
        case "Blood_Shipyard8":
			dialog.text = "��� - �� ��������� ������� ���������... ����� ��� � �����. ������� ���������� ������� ��������� �� ��������� - ������ ����� ����� � �������� ������ � ����������� �������� � ���� ����� � ��������, ��� �������� � ������� ����� ��� ������� ������. ��, ������ - ��� ������ ������� ������ � �������� �� ���� ����������, ��������� ���� ��� ��������� ����� � ������... �� �, ������� - ���������... ����� �� ��� �����, �� ��� ��?\n������ ��� ���� ��� ���� ��������. ������ ������ ����� �������� ��� ��� �� - �������, �������� - �� ����������� �� ��� �� ���������. ��� � ������� �������� ���������� ����� � �����, ��� ������ ������ ������� ��� ��������������.";
			link.l1 = "����� �������������� �������. ���� ����� ���������� � ������-������ ���������. ��, ��� ������ ������� ��� �����, ��... �����������?";
			link.l1.go = "Blood_Shipyard9";
			link.l2 = "� ��� ������� ������� ��������?";
			link.l2.go = "Blood_Shipyard10";
		break;
		
        case "Blood_Shipyard9":
			dialog.text = "����� � ������ �������� �� ����� ���� ������, �� ������ ��� ������� ������. �����, �������� �� ����� ����� ����� ��� �� ������.";
			link.l1 = "�������� ����������. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard10":
			dialog.text = "������ � ������� ��� �������� - �� ������, ��� ����� ����� �� ����� ��� ���������. ��, ���-�� � ���� '�������� ��������' �� ��������... ��� � ������ ������� � ��������. ����� ��-��� ���� � �������� ����������, ����������, ��� ��� �������� �� ������ ������, �� � ������.";
			link.l1 = "��-�, � ��� �� �� ������ �������� ���������� ��������? ��, ����� ���������� �� �������.";
			link.l1.go = "Blood_Shipyard11";
		break;
		
        case "Blood_Shipyard11":
			dialog.text = "���� �� ��� �������� ���� ������, ��, ���� ������� - �� �������� � ������ ���� ����� ��� ��� � ��� ����, � ����� ���-�� �� ����������� ��������� �������� ��� ������� ������. � ����� ���� ������ ����������� �������� ����, ����������� ����� ����������� � ���, ��� � ������������� ������� �������� ������ ��������.\n����� ��� ���� ���� �� ������� � �����... � ��� ������ �� ������. ������, � ����� ��������� �����. �� ������ ��� ���� ��� � �������� ��� ������, � ���� ������� ��� ������ �� ����... �� �����, ������, ���� ������.";
			link.l1 = "����, ������� ��� �������, ��� � �������, ������ ���, ��������� ��� ����� �� ����. ������ �����������. �� ��� ��� ���������� ��� � ����� �����?";
			link.l1.go = "Blood_Shipyard12";
		break;
		
        case "Blood_Shipyard12":
			dialog.text = "��� ����� ������� ������, ���� ������ - �� ���������� ����������� ������ ��� ������������� �������. ������� ��� � ������.";
			link.l1 = "�������� ����������.";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "3");
		break;

	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� �� ���� ������
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// �������� ����� ��� ���� ����
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // ���� - ��� �����
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	switch (_type)
	{
	    case 1 : return "������";  break;
	    case 2 : return "˸�";     break;
	    case 3 : return "������";  break;
		case 4 : return "������ ��������";  break;
	}
	return "������";
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

// Warship Ghdjthrf �� ������ ��
bool CheckForFlyingDuchmanSails(ref _char)
{
	ref realShip;
	int shipType = sti(_char.Ship.Type);
	
	if(shipType == SHIP_NOTUSED) return false;

	realShip = GetRealShip(shipType);

	if(CheckAttribute(realShip, "EmblemedSails.normalTex") && realShip.EmblemedSails.normalTex == "ships/parus_common_torn.tga")
	{
		return true;
	}

	return false;
}