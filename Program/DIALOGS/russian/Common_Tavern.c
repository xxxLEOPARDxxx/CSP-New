#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // ����� 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("� ������ ������� �������, ���� ����� ����! �� ����� ����� � �� �� ���� ����� �������������.", "��� ��������� ������ ����� �� ������ � ������� ����. � �� ����� � ������������� � ����� �� ����!", "����, "+ GetSexPhrase("��������","�������") +", ���� ������� �� ������� �� ���� ������..."),
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","��������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����"+ GetSexPhrase(", ������� �����!","") +"", "�����"+ GetSexPhrase("��","��") +" ������, ��� �� ����� ����! ������!!", "� �� ����� ����, ������"+ GetSexPhrase("��","��") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."),
					RandPhraseSimple("������ ���� �����, " + GetWorkTypeOfMan(npchar, "") + ", � �� �� ����� ���� ������� ����!", "���, " + GetWorkTypeOfMan(npchar, "") + ", � ��� ���� �� - ������� ������! ��� ��� � ���� �����, ��������: ���� ���� � ������ ����..."));
				link.l1.go = "exit";
				break;
			}
            // homo ������� �������� �����
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
                                    "��� ������ ���, ����� ����.",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
                Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
            		link.l2 = "�� ���������� ��, ������� " + NPChar.name + ", ��� ����� ������� ������?";
            		link.l2.go = "TStep_0";
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {
            		link.l2 = "� ���� � ��� ���� ���������� ����.";
            		link.l2.go = "TStep_1";
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && pchar.questTemp.CapBloodLine.QuestRaff == true)
                {
            		link.l2 = "���� ���������� ������� �� ����� ������� ������. ��� ��� ��� �����?";
            		link.l2.go = "TStep_5";
                }
                break;
    		}

			//������������ ����� -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = "���� ����, �������, �������! ��� ���, ��� �������! ��� �������!";
				link.l1 = "��� �� ���������, ��� ��?";
				link.l1.go = "MCTavern";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasWervolf" && npchar.city == "Caracas")
			{
				dialog.text = "�������, �� ������ ����� � ��������...";
				link.l1 = "� �����.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				dialog.text = "��, ��� �������, �������? �� ����� ���?";
				link.l1 = "���"+ GetSexPhrase("��","��") +". �� ������ �� ����� �������������, ����� ��� ��������...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "�������, ��� ��� ������!";
				link.l1 = "��� ��������� � ���� ����� �����������?";
				link.l1.go = "MCCaracasAfter";
				break;
			}
			//<-- ������������ ����� 

			if(NPChar.quest.meeting == "0")
			{
				if (npchar.city == "Pirates")
				{
					dialog.Text = "��, ��� � ��� "+ GetSexPhrase("���� ����� �������","���� �������� �������") +" �� ������ ���������"+ GetSexPhrase("","�") +"! ��������������, �����"+ GetSexPhrase("�","���") +". ���� ����� ���� �����, � � ������ � ����� �������. ������� ������� ������, �� ������ ��? ������� ����?";
					Link.l1 = "��� �� ������ ���� �����? �� �������? ��� �� �� �����"+ GetSexPhrase("","�") +", ��� ����� ������� ���� ���������!";
					Link.l1.go = "Pirates_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Charles")
				{
					dialog.Text = "����� ����������, " + GetAddress_Form(NPChar) + ". ���, ������� � ����������� - ��� �� ��������� �����! ���� ����� " + GetFullName(npchar) + ". � �������� ���� �������.";
					Link.l1 = "���������� ����? � ������"+ GetSexPhrase("","�") +" � ����. ���� ������������, ��� � �������� ������� �� ����������� ������ �� ���������� ���������. ���-�� � ������ �������...";
					Link.l1.go = "Charles_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Portobello")
				{
					dialog.Text = "����� ����������, " + GetAddress_Form(NPChar) + ". ���, ������� � ����������� - ��� �� ��������� �����! ���� ����� " + GetFullName(npchar) + ", �� ����� ��������, ��� ����������� ���. � �������� ���� �������.";
					Link.l1 = "����������� ���? ������"+ GetSexPhrase("","�") +" � � ����. ���� �������, ��� �� ������� ������� ��������� �������� �� ��������� - �� �����-�� ������� �������� � ������ ��������� ������� ���� � ����� ��� ��������� ��-��� ���� � �����.";
					Link.l1.go = "Portobello_1";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.Text = "����� ����������, " + GetAddress_Form(NPChar) + ". ���, ������� � ����������� - ��� �� ��������� �����!";
				Link.l1 = "���������... � " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// ��������� ��������� ����������. ����� �1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "�� ��� ���, �� �������� ��� " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "��, ������"+ GetSexPhrase("","��") +". ��� ���...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "���, ��� �� ������"+ GetSexPhrase("","��") +"...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "���� ��������, ��������"+ GetSexPhrase("�� ��������","�� �������") +"?";
						link.l1 = "������� ���� ����� ��������, ��� �� ��� ��������.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- ��������� ��������� ����������. ����� �1.
			
				////////////////
				//������� ������
				////////////////
				if(startherotype == 2 && CheckAttribute(pchar, "Whisper.FindDesouza") && !CheckAttribute(pchar,"Whisper.Contraband") && (sti(pchar.money) >= 10000) && pchar.rank >=10 && npchar.nation!=3)
				{
					dialog.Text = "�������, �� ����� ����������� � ����� ����. � ������ ���������� ����� � ������� ������� � ����� �� ������ �����. ���� �� ����������, ��� ��.";
					DeleteAttribute(pchar, "Whisper.FindDesouza")
					Link.l1 = "��� �� ���� �� ����� �������?";
					Link.l1.go = "w_find_desouza";
					break;
				}
				// <-- ������� ������
				
				dialog.Text = LinkRandPhrase("��, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "�, ����� � ��� �����! ��� ������ ���, " + GetAddress_Form(NPChar) + " " + PChar.name + ".",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ����� ����� ������� ��� �����?");
				Link.l1 = "���� �� ������� �����, ������� ���� � ��������?";
				Link.l1.go = "crew hire";
				Link.l2 = "� �������, �� ������� �������� �� ���� ��������.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "������, ��� ����� ���������� � ���������� �����.";
					link.l21.go = "LoanForAll";//(���������� � ��������� ���������)
				}
				
				
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("�� ���-������ ������ ������� �� �������� ���������� ������?", "��� �� ������ �� �������� ���������� ������� ������?", "�� ���-������ ������ �� �������� ���������� ������� ������?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- ��������� ��������� ����������. ����� �2.
				link.l3 = pcharrepphrase("���� �� � ����� ���������� ��������� ������?", "��� �� � ���� ��������� �������, � �����"+ GetSexPhrase("","�") +" �� ������������ ����� �� ��������� �����.");
				link.l3.go = "room";
				Link.l4 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l4.go = "exit";
			}
		break;
		
		case "Meeting":
			// ��������� ��������� ����������. ����� �1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "���� ��������, ��������"+ GetSexPhrase("�� ��������","�� �������") +"?";
				link.l1 = "������� ���� ����� �������� ��� �� ��� ��������.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- ��������� ��������� ����������. ����� �1.
			if (npchar.city == "Pirates")
			{
				dialog.Text = "�, �� �� ������ ��� ������ � ������ ��� �����, " + GetAddress_Form(NPChar) + ". � ����� ���������, �� �� ����� ������ ������������... ��, ������ ��� �����������, �������.";
				Link.l1 = "��� ����� �������, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", ����� ���������...";
				Link.l2.go = "int_quests";
				
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "������, ��� ����� ���������� � ���������� �����.";
					link.l21.go = "LoanForAll";//(���������� � ��������� ���������)
				}
				
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("�� ���-������ ������ ������� �� �������� ���������� ������?", "��� �� ������ �� �������� ���������� ������� ������?", "�� ���-������ ������ �� �������� ���������� ������� ������?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				
				// <-- ��������� ��������� ����������. ����� �2.
				link.l3 = pcharrepphrase("���� �� � ����� ���������� ��������� ������?", "��� �� � ���� ��������� �������, � �����"+ GetSexPhrase("","�") +" �� ������������ ����� �� ��������� �����.");
				link.l3.go = "room";
				Link.l4 = "�������, ������� � ���� �������.";
				Link.l4.go = "exit";
				break;
			}
			
			if (npchar.city == "Charles")
			{
				dialog.Text = "�� � � �����-�� ������ ��� ���������� � �������� ������������... ��, ��� ��� �� ������, " + GetAddress_Form(NPChar) + "?";
				Link.l1 = "��� ����� �������, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", ����� ���������...";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "������, ��� ����� ���������� � ���������� �����.";
					link.l21.go = "LoanForAll";//(���������� � ��������� ���������)
				}
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("�� ���-������ ������ ������� �� �������� ���������� ������?", "��� �� ������ �� �������� ���������� ������� ������?", "�� ���-������ ������ �� �������� ���������� ������� ������?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- ��������� ��������� ����������. ����� �2.
				link.l3 = pcharrepphrase("���� �� � ����� ���������� ��������� ������?", "��� �� � ���� ��������� �������, � �����"+ GetSexPhrase("","�") +" �� ������������ ����� �� ��������� �����.");
				link.l3.go = "room";
				Link.l4 = "�������, ������� � ���� �������.";
				Link.l4.go = "exit";
				break;
			}
			
			if (npchar.city == "Portobello")
			{
				dialog.Text = "�, � ������ ��� ���������, �������. ���� ������ �� ��� ����, ������ ���, " + GetAddress_Form(NPChar) + ". ��� �� �������?";
				Link.l1 = "��� ����� �������, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", ����� ���������...";
				Link.l2.go = "int_quests";
				
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "������, ��� ����� ���������� � ���������� �����.";
					link.l21.go = "LoanForAll";//(���������� � ��������� ���������)
				}
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("�� ���-������ ������ ������� �� �������� ���������� ������?", "��� �� ������ �� �������� ���������� ������� ������?", "�� ���-������ ������ �� �������� ���������� ������� ������?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				
				// <-- ��������� ��������� ����������. ����� �2.
				link.l3 = pcharrepphrase("���� �� � ����� ���������� ��������� ������?", "��� �� � ���� ��������� �������, � �����"+ GetSexPhrase("","�") +" �� ������������ ����� �� ��������� �����.");
				link.l3.go = "room";
				Link.l4 = "�������, ������� � ���� �������.";
				Link.l4.go = "exit";
				break;
			}
			dialog.Text = "�, �� ���� � ���� ���������, " + GetAddress_Form(NPChar) + ". ���� ����� " + GetFullName(npchar) + ". � �������� ���� �������.";
			Link.l1 = "��� ����� �������, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", ����� ���������...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "������, ��� ����� ���������� � ���������� �����.";
				link.l21.go = "LoanForAll";//(���������� � ��������� ���������)
			}
			// ��������� ��������� ����������. ����� �2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("�� ���-������ ������ ������� �� �������� ���������� ������?", "��� �� ������ �� �������� ���������� ������� ������?", "�� ���-������ ������ �� �������� ���������� ������� ������?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- ��������� ��������� ����������. ����� �2.
			link.l3 = pcharrepphrase("���� �� � ����� ���������� ��������� ������?", "��� �� � ���� ��������� �������, � �����"+ GetSexPhrase("","�") +" �� ������������ ����� �� ��������� �����.");
			link.l3.go = "room";
			Link.l4 = "�������, ������� � ���� �������.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			/* ����� ������ ������� 
			if (!ok)
			{
				Dialog.text = "� �� ��� ���� �������? ���-�� �� ���� ������ ������� � �����.";
				link.l1 = RandPhraseSimple("�����... � ��� ������������"+ GetSexPhrase("","�") +" �� � ��� �����.", "�����"+ GetSexPhrase("","�") +" ����� � ����...");
				link.l1.go = "exit";
				break;
			} */
			//����� ����� ���� 
            if (makeint(environment.time) > 24.0 || makeint(environment.time) < 0.0)
			{
				Dialog.text = "������ � ���� � ������� ����� �����, �������� ����� ���������, �� ������ ������� ������, � ��� ������ ���������� ������ �����. ����� ����, �� ������ ����� �������, � ��������� ��?";
				link.l1 = "������. � ���� ���� ��������� �������?";
				link.l1.go = "room";
				link.l2 = "���� �� ���������� ������� �� ������ ������. �� �������.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "� �� �������, � ���� ���-�� ������, ����� �� � ���� �� ������? ����� �������, ��� ������ �� ����.";
					link.l1 = "�������.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 1 && GetCrewQuantity(rColony) == 0 && drand(100) > 90)
					{
						Dialog.text = "��������, �� ������ ��� ������. ��� ���� � �������� ����� " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "��, ����!";
						link.l1.go = "exit";
					}
					else
					{
						if(bPartitionSet)
						{	
							if((Partition_GetSetting("Part_Crew") == 0) || GetPartitionAmount("CrewPayment") > 0)
							{
								dialog.text = "�������, ������������, ��� �� ���������. � ���� ��� �������� ����� � ���� �������.";
								link.l1 = "�������...";
								link.l1.go = "exit";
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //�� ���� ������.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();							
							}
						}
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //�� ���� ������.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();
						}
					}
				}
			}
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "� ���� ��������.";
			link.l1 = "� ��� ������. �� �������� ���?";
			link.l1.go = "work";
			//homo 15/06/06 �����
			link.l2 = LinkRandPhrase("�������� ��� ��������� �������?","��� ���������� � ���� �����?",
                                    "��� ����� ����� �� ����?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "� �� ������� ����.";
			link.l3.go = "quests";
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //����� ���� �� ������ ������
			{
				link.l4 = "� �������� �� ��������� �����������. ����� ���, �� �� ������� ������ ��������������� � ��������� ����� � ������?";
				if (pchar.GenQuest.SeekSpy.City == "0")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "�� ������, ��� ��� ����� " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "�� ����������, ��� ��� ������ " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek"))
			{	
				link.l8 = "�� ����������, ��� ��� ������ ����� �����?";
				link.l8.go = "Andre_Abel_Quest_TavernOwner_Dialog_1";			
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "�� ���, �� ������� " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "�� ����������, ��� ��� ������ " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "�� �� ������, ��� � ���� ����� �������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "�� ���, �� ������� " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "�� ���-������ ������, � �������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "�� ����������, ��� ��� ����� ��������� �� ����� " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "� ���������� �������� ���������� ���"+ GetSexPhrase("��","��") +" ������� ���������....";
				link.l11.go = "ShipLetters_4";			
			}

                        //���
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if(pchar.questTemp.Headhunter == "hunt_carlos" && npchar.city == pchar.questTemp.Headhunter.City)
	    		{	
	    			link.l12 = "�� ����������, ��� ��� ������ ������� �������?";
	    			link.l12.go = "Seek_Carlos";			
	    		}
			}
			
			//zagolski. ��������� ����� ������
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "1" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				if (!CheckAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo"))
				{
					link.l12 = "������, �������, �� ����������, � ��� ����� ����� ������ �� ��������������?";
					link.l12.go = "pirateStartQuest_Tavern";
				}
				else
				{
					if (sti(pchar.money) >= 500)
					{
						link.l12 = "������ � ���� 500 ��������. ������ ��� ������.";
						link.l12.go = "pirateStartQuest_Tavern_2";
					}
				}
			}
			//Lipsar ����� ������� ������ ������--->
				if(CheckAttribute(Pchar,"Quest.Luke") && Pchar.Quest.Luke == "1" && NPChar.City == "LaVega")
				{
					link.l13 = "��������, � ��� ��������, ��� ����� �� �������� ������ �� �����. �� �� ������ ��� ��?";
					link.l13.go = "LukeQuest_1";
					sld = CharacterFromID("Maks");
					ChangeCharacterAddressGroup(sld,"none","none","none");
				}
				if(CheckAttribute(Pchar,"Luke.SpawnMaks") && Pchar.Luke.SpawnMaks == "1")
				{
					sld = CharacterFromID("Maks");
					if(NPChar.Location == sld.City)
					{
						link.l13 = "��������, � ��� ��������, �� ����� ����������� �����. �� �� ������ ��� ��?";
						link.l13.go = "MaksQuest_1";
					}
				}
				//<---Lipsar ����� ������� ������ ������
			
			link.l14 = "�� �������� �� �������� �����������, ��� ��� ���� � ���� ������ �� ����?";
			link.l14.go = "PGGInfo";

			link.l15 = "�������, ������. �� ��������.";
			link.l15.go = "exit";
		break;
		
		//-------------------------------------------
		case "PGGInfo":
			int rep = pchar.reputation;
			int repcheck = 40;
			if (IsCharacterPerkOn(pchar, "Adventurer"))
			{
				repcheck = 10;
			}
			
			if (rep <= repcheck)
			{
				dialog.text = "�����-�� ����� � ����, �� �������� � ����� ���������� ����� �������� �������� ������. ��� ��� ���������� � ������ ��������� ���� ��������, ���!";
				link.l1 = "�� � �����, ��������!";
				link.l1.go = "exit";
			}
			else
			{
				int cost = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE/2);
				if (IsCharacterPerkOn(pchar, "Agent"))
				{
					cost = makeint(cost/2);
				}
				dialog.text = "��, �� ��� �, ����� ���-�� � ����... �� ��� ����� �������, ���. � ������� � ���� �� ��� "+cost+" � �� �������� ������! ����������?";
				if (sti(pchar.money) >= cost)
				{
					link.l1 = "������, ��� ���� ������. ������ ������ ��� ������.";
					link.l1.go = "PGGInfo_2";
				}
				link.l2 = "������� ���-������ �����.";
				link.l2.go = "exit";
			}
		break;
		
		case "PGGInfo_2":
			int cost1 = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE/2);
			if (IsCharacterPerkOn(pchar, "Agent"))
			{
				cost1 = makeint(cost1/2);
			}
			AddMoneyToCharacter(pchar, -cost1);
			AddDialogExitQuestFunction("OpenPGGInformation");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "pirateStartQuest_Tavern":
			dialog.text = "��, �� ���"+ GetSexPhrase("��","��") +" � ���� ��������! � �������� ��������� � ������� ����� ���� �������� ����� ������.";
			link.l1 = "���"+ GetSexPhrase("","�") +"  � ���. ������ � ��� ������ ���, � ����� � �� ���� - ����� �������� ������ ���������. � ���� ������� ����� ���� ����, ����� �� � �� ����� �����.";
			link.l1.go = "pirateStartQuest_Tavern_1";
		break;
		case "pirateStartQuest_Tavern_1":
			dialog.text = "��, �� ��� �, ����� ���-�� � ����... �� ����������� �������� �� ����, � �������������������� �� ���������. ��� ���������� ����� 500 ��������. ����� ��� �����.";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "������, ��� ���� 500 ��������... ������ ��� ������.";
				link.l1.go = "pirateStartQuest_Tavern_2";
			}
			else
			{
				link.l1 = "� ���� ��� ����� �����... �������, ����� ���������.";
				link.l1.go = "exit";
				pchar.questTemp.pirateStartQuest.TavernInfo = "";
			}
		break;
		case "pirateStartQuest_Tavern_2":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = "��, �� ����. ���� ��� ���������, ������� ����� �������� ���� ����� �� ���������. ���������� ���� �������, ��� ������ ����� ������. ����� ��� � ��������������� �����������. �� ������ ���� ������ ����� � ����� ��������, ���� �� ��� ����� ������� ���������� �� �� ���������...";
			link.l1 = "����. � �� ������, ����� '�������' ������� � ��� � ���� �� ��������?";
			link.l1.go = "pirateStartQuest_Tavern_3";
		break;
		case "pirateStartQuest_Tavern_3":
			dialog.text = "'�������'? ���, ����� �� ��������. �� � �������� ��� ��� �� �������.";
			link.l1 = "������, �������. �� ��� ������� �����. �� �������.";
			link.l1.go = "exit";

			PChar.questTemp.pirateStartQuest = "2";
			pchar.questTemp.pirateStartQuest.City2 = npchar.city;
			DeleteAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo");
			AddQuestRecord("pSQ", "2");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;

		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("��� �� ��������? " + pchar.GenQuest.Hold_GenQuest.Name + "? ��, ������� �� ������ � �����.",
						"�� ����� ������, ��� �� ������ �� ������ ���������? ������ �� �������� � ����� �� ����.",
						"� ����� ��������� ������ �������� �� ����. ������� ����� ���� - �� ������.");
					link.l1 = "� �� �������?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "� �������";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "�� �����";						
								pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "� �������";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "� ����������";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "� �������";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "������� " + pchar.GenQuest.Hold_GenQuest.foundStr + ", �� ��� ����� ������.";
					link.l1 = "�������, ����� ����������.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("��� �� ��������? " + pchar.GenQuest.Hold_GenQuest.Name + "? ��, ������� �� ������ � �����. � �� �������, ��� �� ������ �� ������ ���������?",
						"�-��-��... ����� ���� ������� ��� �����, ��� ������ ��� ������ - �� �� �� �������, �� �� � �����������. ����� ��... ��� ������ ��� ��� �����, � �� � �� ������������, ����������, �� ��� ����� �� ���� �������..."),
						RandPhraseSimple("�� ������ �� ��� ���, �� ���� ����� ��� �����. �� ��� ����� ����� ��, �� ����� ���������... �������� ��� ��������... � ����� ������� ����� ���! � ���������, ������������, ����� ���� ������, ��� �� ������� �������! � ���� � �� - ������ ������� - � �������, ��� �����...",
						"��, ���������! �� ������ ����� ��. �� �� � ����� �������, �� �� � ������ - ������ �� ��������. ������ ������ ������� � ��������."),
						"�-�, ��� �� ���� �� " + pchar.GenQuest.Hold_GenQuest.Name + " �� �����, ��� ����� ���������� � ����� ���� ��� � ����� ��������? � ���� ���� �������, ����� � ��� � ���� ����� ��������! �� � �� ��� ���� ��� ������ �������. ��� ���� � �� - ������� ��� ������! ���, �� ������ ���� �����...");
					link.l1 = "����. ��, ������� � �� ����.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "� ��� �� ��� ������, ���� �� � ��� � �������? �� ����� ��������� ���������� - ����� ������ ����� ��������, ��-��. �� ������� �������, ���� �� ��������, � �����, ���� ��� ��������.";	
					link.l1 = "�������, �����.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "��� �� �� ���� ���������-��, ���� � ���� ������� ����������, ��� ������ ����. ��� �� ������ ��� ������� �����. "+
				"� �� ���� � ������ ����� ������� - ���� ���� ����� �����, ��� ������ ��� � ������ ������ � ������ ����������, � ���� � ������ ���������� �����������. � �� ��� - '�������'!";
			link.l1 = "�� �����, ������� � �� ����...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("��","��"));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("�� ��������� ���� �������, �� ������ ���-�� �� �����. ������������ �� ��� ����� �� �������, ���� �� ��������, � �����, ���� ��� ��������.","�� ����� ����� ������. ���� �� ������ �����, �� ��������� ��� ���������.","�������� ����� �� �������, �� ����� ����� ����������. � �������, ��� �� ��� ������.");
			link.l1 = "�������, ����� �������...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "�������. ������ ������ ���-�� �����...";
			link.l1 = "�������.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "��� �� � �� �� �����? ��� ��� ������� ���� � ��������� ������ �� ���� � �������.";
			link.l1 = "������ ���������� ���������?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "� �����, ������� ����� �������� ������ � ������ ��� �������, ������ ����� �������� �� ����������, ����� ������� � �����... �� ���? � ������������� ��������� ����� ������ ��������, ��� �� �� ����� �������������� ����� ������ �� ��� ���������� � ��������� �����, � ����� �� ��� ����� �������.\n"+
				"�� ������� � ��� � ������, ������ ���, �� ��������� ����� �����, �� ����� ��� � �� �����... �� ��� ��� ��� ����� �����������.";
			link.l1 = "���, ����� �� ������� �� ���������, ��� ������?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "�� ����!.. �� ������ � ����, ������ ���������� ��� ����� ������� ����� ������? ���� ������� " + pchar.GenQuest.CaptainComission.Name + " ��� �� ������� �����, � ��� ������� ������ - ����� ������� ����������, �� �������� ����� �����.";
			link.l1 = "� ��� ��� ������ ���������� � ����� ������ �������?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "��, ����� �� � �� ����, ������ �� ����... ���� ���, ���� �������, �� ����� �� ���� ��� ���� �� �����. �� ����������, ��������� ��� � " + pchar.GenQuest.CaptainComission.Name + ". ��� ����� ��� �������� � �����-�� ����� ������ ��� ��� ����� ���� ������������ ������. ������� � ��������� ����������, ��� �����, � ����� ���� ������� ������ ������ - �������� � ������� � �������� �����������, �� ����� ������, ��� ��-���� ����� ������.";
			link.l1 = "��� �� ������ � ���������?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "��, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " ��� �����, ������ ���� �������, ��� �����������. ���� � ��� �����, ����� - ���� ��� ��������.";
			link.l1 = "�������, � ����� ���������.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "��� �� �����? ���� �������. � ��� �� �� ���?";
			link.l1 = "���� � ���� � ����.";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "�� ��, " + GetAddress_Form(pchar) + ", ������������ � ���� '�����'. " + pchar.GenQuest.CaptainComission.Name + " ������� �� ���������� � ��������� ������������, � ������ �� ����� ������� ����� �������������� ������ � ������� ��� ����������.";
			link.l1 = "������... � ��� �� ����� ��������?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "�� ���� ��������� ��� ������, �� �������, ��� �� ������� ����, ������� ����������� � ����������� ���� ���������� �����. ������ ��� �� ������, �� ����� ����� ������ �� �������. �� ������ � ����, ������ ���������� ��� ����� ������� ����� ������? ���� ������� " + pchar.GenQuest.CaptainComission.CapName + " ��� �� ������� �����, � ����� �� ��������, �� �������� ����� �����, " + GetAddress_Form(pchar) + ".";
			link.l1 = "��, �������, ��� �����������. ����� ��������.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "� ��� ��� ����� ������������?";
			link.l1 = "���� � ��� ����...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "� �������� ������� ������ ��������� � ��� ���� ����. ���� �� ������� � �������, �� ������� ���������� �� �� ��������� ������.";
			link.l1 = "�-��. "+ GetSexPhrase("������, � ���� � ����� ������� �������. ���� � ��� ����� ����������, �����, ����� �������� �� ����","�������") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "�� ��������� ���� ������� � ������� ��������� ������, �� ������ ���-�� �� �����. ������������ �� ��� ����� �� �������, ���� �� ��������, � �����, ���� ��� ��������.";
			link.l1 = "�������, ����� �������...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "�, ��� �� � ���� "+ GetSexPhrase("��� �������, ������� �����","�� �������, ������� ��������") +" ����� �������� ���� � ������� ��������?";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "�����-�� ��������� ! ��... �� �� ���� - �������. �����, ��� ����� ����� � ���������� �����.";
				link.l1 = "������� �� �����.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "�����-�� ���������! �! ���� �� �����, ��� ����������� ������ ����� ����������� ����������, ������ ���������� ��������. � ���� ��� �������� ��������� ���������.";
				link.l1	= "�������, ��� ...";
				link.l1.go = "exit";
				link.l2 = "���"+ GetSexPhrase("","�") +", ��� ����"+ GetSexPhrase("","��") +" ���� ��� �����"+ GetSexPhrase("��","��") +".";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//������-���������
		case "work":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("��� ��� ������� ���� ����������� - ������ �� ����� ��������������. �� ��� �������� ���� � �� �����, ��� ��� �� ����"+ GetSexPhrase("��","��") +" ��� ������ " + NationNameGenitive(sti(pchar.nation)) + ".", "� ����� ���� ������� ������ �������, �� ������������ � " + NationNameAblative(sti(pchar.nation)) + " �������� ������� �� ����.");
				link.l1 = RandPhraseSimple("��, ���� �����...", "��, ��� ������...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("���������� ������ �������. ������ ���� �� ����� ��� �������� ����� ����������, ����� ������� �������������� �� ����� �����. ������ ����� ����� ������� ����, � ��������� �������� �������� ��� ��������� �����.", "�� ��� ����� ���������� ��������, ������� ����� �������������. �� ������ ����� ����� �� ����� �� �����, � � ������ �� ����� ������������� ���� ������. ��� ���� ��������� ������.");
				link.l1 = RandPhraseSimple("�� �� ���� �������� ������ ��������...", "�� ��, ���� ��� �� �����������...", "��, ���������� ����� ������� �����...");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "������ ��������, ���� �� ������� ������ � ��������� ��������� ��� � ����� ��������� �����. �� ��� ������ ������ �� ���� � ���������� - �� ����� ������������� ����, �� ���������, ������� � �������� ���������� ���� �� ��������. ���-�� ���������� ����������?";
			link.l1 = "��, ��� �� �������. � �� ����"+ GetSexPhrase("��","���") +" �� ������.";
			link.l1.go = "work_1";
			link.l2 = "��������� ����? ������, ���� � ����� � ����, ���� �� ������ �������.";
			link.l2.go = "work_2";
			link.l3 = "���, ����� ������ �� �� ���. �������.";
			link.l3.go = "exit";
		}
		else
		{
		dialog.text = "� ������� ���� ���? ������� ���� ����� � �����, ����� � � ������ ���������.";
		link.l1 = "��, � �� �����...";
		link.l1.go = "exit";
		}
		break;

		case "work_1":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//��� ������ ���������� � �� 7 ����� �� ����
				{
				dialog.text = "��������, �� �������� ����������� � ���� ������ � ���� � ���� ���.";
				link.l1 = "�������. ��� �������.";
                link.l1.go = "exit";
				break;
				}
				//������
                if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
                {
					if (GetCompanionQuantity(PChar) == COMPANION_MAX)
					{
						dialog.text = "��, �� ��� ������� � ���� ������� ������� �������. ���� �� ���� ������� �� ���������, � �� ��, ���� ����� �������.";
						link.l1 = "�� ����� ����, ����-�� � �� ��������, ����� ��� ������� �������... �����, ����� �����, ���� �������.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(8) > 1)
						{
							if (!CheckAttribute(PChar, "QuestTemp.AndreAbelQuest_StartQuest") && PChar.location == "FortFrance_tavern"  && pchar.questTemp.piratesLine == "begin" && sti(pchar.rank) > 4) // �� ����� ��������� ������� 
							{
								dialog.text = "�������� ��� � ��� ������, ������ �� �������. � ���� ����� �� ��������";
								link.l1 = "�������, ��� � � ���"+GetSexPhrase("��","��")+" ������";
								link.l1.go = "exit";
								Log_TestInfo("������������� ������ '�����' - ���������� ������������ � sit, sit7");
								PChar.QuestTemp.AndreAbelQuest_StartQuest = true;
								PChar.QuestTemp.AndreAbelQuest = true;
				
								// �������� ��� ������ ����� ���� -->
								sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
								FantomMakeCoolFighter(sld, 10, 30, 35, "blade9", "pistol2", 10);
								FantomMakeCoolSailor(sld, SHIP_FLEUT, "�����", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
								sld.name = "�����";
								sld.lastname = "�����";
								sld.SaveItemsForDead = true; // ��������� �� ����� ����
								sld.DontClearDead = true; // �� ������� ���� ����� 200�
								sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
								sld.greeting = "cit_quest";
								LAi_SetSitType(sld);
								LAi_SetImmortal(sld, true);	// �� ���� ������ �����
								SetCharacterGoods(sld, GOOD_SILK, 700);
								SetCharacterGoods(sld, GOOD_TOBACCO, 500);
								FreeSitLocator("FortFrance_tavern", "sit7");
								ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
								SetFunctionTimerCondition("Andre_Abel_Quest_1Day_Left", 0, 0, 1, false);
								// <-- �������� ��� ������ ����� ����
							}
							else
							{
							dialog.text = "��, ����� �������� ��� � ��� �����, ��� � ������� �����. �� ������� � ������������� ���������.";
							link.l1 = RandPhraseSimple("�� ��� ������ ������? �����, ����� �����?", "� ��� �� �����? ����� � ��� ���� �����?");
							link.l1.go = "ConvoyAreYouSure";
							}
						}
            			else
            			{
            				dialog.text = "�������, ��� �����, ����� �� �������� ������ �������������. ������� ����� ���� ����, �����, ��� � ��������.";
							link.l1 = RandPhraseSimple("�����, �� ��� � ���� ���.", "��, �� ������... �� �����, ������.");
							link.l1.go = "exit";
						}
            		}
                }
				else
				{
					dialog.text = "�� ��� - ������� ������� �����"+ GetSexPhrase("","�") +"? � ���� �� ���� ��������������, ������� � ��� �������, ����� �� ������� ���. ����� �� ������ �����, ���� �������� � ������ ���������.";
					link.l1 = RandPhraseSimple("��� ��������... �� �����, ����� ��������.", "��, �������������, �� �������"+ GetSexPhrase("","�") +". �� �����, ������.");
					link.l1.go = "exit";
        		}
    		}
    		else
    		{
				dialog.text = "������� ��� ������ ���. �������� ����� ���� ����.";
				link.l1 = "������. ��� �������.";
                link.l1.go = "exit";
    		}
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//��� ������ ���������� � �� 7 ����� �� ����
				{
				dialog.text = "��������, �� �������� ����������� � ���� ������ � ���� � ���� ���.";
				link.l1 = "�������. ��� �������.";
                link.l1.go = "exit";
				break;
				}
		         // ��������
				if (drand(6) > 1)
				{
					dialog.Text = "��� ��� � ������� �����, �� ������� �������� ����� ���������, ����-�� ��������� �����. ���� ������, ���������� � ���.";
					link.l1 = RandPhraseSimple("� ��� �� ���? ����� ���������� �����, ��� � �������?", "� ��� �� �����? ������� � ��� �� �����?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "���, ������� �� ���� �� ���������. �����, � ������ ����...";
					link.l1 = RandPhraseSimple("�� ���, ��� ���. ���� �� ���...", "��, �� ������... �� �����, ��������.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "������� ��� ������ ���. �������� ����� ���� ����.";
				link.l1 = "������. ��� �������.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("�� ��� � ��� �����. �� �������"+ GetSexPhrase("","�") +" - � �������.", "��, ��� �� ���� ����"+ GetSexPhrase("��","�") +" ������. � �� ��� �� �� ���� �� ���������.", "����� ���"+ GetSexPhrase("","�") +", �� ��� ������ ����������. ��� �� �������, � �� ���������� �����������.");
			Link.l1 = "�� �������, ������ �����������.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("�� ��� � ��� �����. �� �������"+ GetSexPhrase("","�") +" - � �������.", "��, ��� �� ���� ����"+ GetSexPhrase("��","�") +" ������. � �� ��� �� �� ���� �� ���������.", "����� ���"+ GetSexPhrase("","�") +", �� ��� ������ ����������. ��� �� �������, � �� ���������� �����������.");
			Link.l1 = "����, ������ ������� ��� ��� �� ���.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			/*if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //���-�� ������ ������� � ��.
			{
				dialog.text = "������ ������� ������, " + GetAddress_Form(NPChar) + ", ����� �� ���� ������.";
				link.l1 = "����, ����� ����...";
				link.l1.go = "exit";
				break;
			}*/
			if (CheckAttribute(pchar, "questTemp.State.Open") && npchar.id == "Tortuga_tavernkeeper")//���.�������, ����� �6, ���������� ����� � �������
			{
				dialog.text = "�� ��������� ��� �� ������ ������, � �� ���� ����� � ��� ��� ������. ������� ����, ����� � ���������...";
				link.l1 = "������, ��������, �������.";
				link.l1.go = "exit";
				break;
			}
			//-->> ����� ����������
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "�� ������ ����� �������? �� ��������. � ��� 100 ����� - � ������ ���� ������.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "������� ���� ������, �������� �������, ��������...";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "��, �, �������, ������� �������...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//����� ����������
			{
				dialog.text = "������� ����, ����� � ���������...";
				link.l1 = "������, ��������, �������.";
				link.l1.go = "exit";
				break;
			}
			//<<-- ����� ����������
			// --> ����� "������ � ��������"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "�� ������ ����� �������? �� ��������. � ��� 50 ����� - � ������ ���� ������.";
					if (sti(pchar.money) >= 50)
					{
						link.l1 = "������� ���� ������, �������� �������, ��������...";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -50);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "��, �, �������, ������� �������...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//�����  �� �������� ����� � ��������
				{
					dialog.text = "������� ����, ����� � ���������...";
					link.l1 = "������, ��������, �������.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- ����� "������ � ��������"
			dialog.text = "�� ����� ���� �� ���������� ������������?";
			if(!isDay())
			{
				link.l1 = "�� ����.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "�� ����.";
				link.l1.go = "room_night";
				link.l2 = "�� ���������� ����.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "��� ��������� ��� � 5 �������.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "����. ��� ���� ������.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("�� ������ ����������� �����? ��� ��, �� ����� ���� � ����� ������ � ����� ����.",
            "���, ������, ����� �������, ��� ��� �� �������, �� ��� ����� ��������. � ��������� � ����� ����.");
			link.l2.go = "hall_day_wait";
			link.l3 = "�� ������. ����� ��������� � ���-������ ������.";
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = "��� ��������� ��� � 10 �������.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "����. ��� ���� ������.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("�� ������ ����������� �����? ��� ��, �� ����� ���� � ����� ������ � ����� ����.",
            "���, ������, ����� �������, ��� ��� �� �������, �� ��� ����� ��������. � ��������� � ����� ����.");
			link.l2.go = "hall_day_wait";
			link.l3 = "�� ������. ����� ��������� � ���-������ ������.";
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = "��� ��������� ��� � 5 �������.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "����. ��� ���� ������.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("�� ������ ����������� �����? ��� ��, �� ����� ���� � ����� ������ � ����� ����.",
            "���, ������, ����� �������, ��� ��� �� ������� �� ��� ����� ��������. � ��������� � ����� ����.");
			link.l2.go = "hall_night_wait";
			link.l3 = "�� ������. ����� ��������� � ���-������ ������.";
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "��������, �������"+ GetSexPhrase("��","��") +"! ������ ��� � ����� ���� ����������� �� ���������.";
				link.l1 = "�����, �����... ��� �����.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "��������, �������"+ GetSexPhrase("��","��") +"! ������ ��� � ����� ���� ����������� �� ���������.";
				link.l1 = "�����, �����... ��� �����.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "���������, ����� ��� ���������� ��� ���������� � ���� �������, ��� � ������ ����������!";
			link.l1 = "�����, �����, � ��� �����.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		//==> eddy. ����� ����, ������� �� ������� �� ������
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat("��, ��� ��������... �� ������, ���� ���� ���, ������� ����� ��� ������� �� �������. �� ���� ������� ���������, �� �������� �� ���, �� � ������ �������, ������� � ���� ��������. ���� �� ���� �� �������� - � ��� ����� �����, � ��� � ������ �����.", 
				"�� ��� �������� �� ��� ����, ����� ��� ������� ���� ������.", "����� �� �� �����... � ��� ��� ���� ������.", "������� ����� ���������� �� ����� � ��� ��?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, ����, ��������. ��� ��, ����� ������ ����� ����.", "��, �� ������...",
                      "��, �� ��...", "������, ��������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat("���, ������ �� �����, ����� � ���� ���������� �������.", 
				"�� ��� �������� �� ��� ����, ����� ��� ������� ���� ������.", "����� �� �� �����... � ��� ��� ���� ������.", "������� ����� ���������� ���� � �� ��?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� ��, � �� ���� �������, ��������.", "��, �� ������...",
                      "��, �� ��...", "������, ��������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		//==> homo ������� �����
		case "TStep_0":
			dialog.text = "����� �� ��������. � � ����� �� ������������.";
			link.l1 = "���������.";
			link.l1.go = "Exit";
			int n= FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = false;
		break;
		
		case "TStep_1":
			dialog.text = "��� �� ���� �� ��� � ���, ��������� ������?";
			link.l1 = "���� ���������... ��� �� �� ��������, �� ������ ������, ��������� ���������� ������ � ���� ����������, ������� ����. �� ���� ������ ��� �������� ��� ������� �� ��������, ������� ��� �� ����� �������� ����������? �� �� ������, � ������� ��� ���� ��� ������...";
			link.l1.go = "TStep_2";
		break;
		
		case "TStep_2":
			dialog.text = "��, ����������, ���.";
			link.l1 = "�� ������? ��� ��� ������?";
			link.l1.go = "TStep_3";
            if (makeint(pchar.money) >= 500)
            {
    			link.l1 = "� ����� �� ��������, ��� � ���� ��� �������� �������� �������� ������ � �������... ��, ������, ���� ����� ��������? �� � ���������, ��� � ����� ���� ����, �� ����� ����� ��� � �������.";
    			link.l1.go = "TStep_4";
            }
		break;
		
		case "TStep_3":
			dialog.text = "����� �� ���� ������, ������.";
			link.l1 = "����� ����������.";
			link.l1.go = "exit";
		break;
		
		case "TStep_4":
			dialog.text = "�������, � ���� ���� ��, ��� ��� �����, ������ ����. ������ �������, �������� �� �� ��� ����� ��������� �������, �� ����� ������ ���������. ��� ��� ��������� ���������� �� �������� ����������� ����� - ������� � ����. ������, �� �� ������� ���.";
			link.l1 = "����� ����������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1";
			AddQuestRecord("WeaponsForEscape", "2");

		break;
		
		case "TStep_5":
            pchar.questTemp.CapBloodLine.QuestRaff = false;
			dialog.text = "�������, � ���������� ������... ��� ��� ��� �� ��... ����� �� ��...";
            if (makeint(pchar.money) >= 200)
            {
    			link.l1 = "��� ����� ������� ���� ������������?";
    			link.l1.go = "TStep_6";
            }
			link.l2 = "��� �� ��� ���?";
			link.l2.go = "TStep_7";
		break;
		
		case "TStep_6":
            AddMoneyToCharacter(pchar, -200);
			dialog.text = "��� ��! �������, ��� ��! ������� ������ �������, ������� ���-�� ��� ������� �������... � ����� �� ����, ������ � � ����.";
			link.l1 = "� ��� �� ������? ��� �������, �� 200 �������� ����� ���������� ���� ��� ������ ������������, ������ ������ ��� ����, ��� �� ����� �����.";
			link.l1.go = "TStep_8";
		break;
		
		case "TStep_7":
			dialog.text = "���, ���... ����� �� ��. ������ - ������.";
			link.l1 = "�������...";
			link.l1.go = "TStep_10";
		break;
		
		case "TStep_8":
			dialog.text = "�����, �� ��� ������� �� �����, ���� ������������.";
			link.l1 = "�������� ����������.";
			link.l1.go = "TStep_9";
		break;
		
		case "TStep_9":
            AddQuestRecord("UsurerQuest", "2");
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "�����";       //fix �����
            sld.lastname = "������";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_Shipyard", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "TStep_10":
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "�����";    //fix �����
            sld.lastname = "������";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH7", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		//������������ �����
		case "MCTavern":
			dialog.text = "���, ���! ��� �������, ���������, �������, �� � ������ ���������\n�������, �� "+ GetSexPhrase("������ �������","�������� �������") +", ������, �������� ���-������! ���� ���� �������� ���, � �����... � ����� �����������, ��� �����!";
			link.l1 = "� �� ����, ��� �� ��� ������ ������ � �� ��� ��, ������� �� ������. �����, �������� � ����� �����������.";
			link.l1.go = "exit";
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.MC = "toCaracasWervolf";
			DeleteAttribute(&locations[reload_location_index], "reload.l2.disable");
			sld = GetCharacter(NPC_GenerateCharacter("CaracasWervolf", "trader_14", "man", "man", 10, PIRATE, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasWervolf";  
			sld.location	= "Caracas_tavern_upstairs";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.BreakTmplAndFight = true;
			sld.reactionOnFightModeOn = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "EnemyFight");	
		break;

		case "MCCaracasAfter":
			dialog.text = "����� ����, � ��������� �� ����! ��� �������� ������� �����, ���� ����������� �� ����� ���� ��� �������! ���� �������� ������� ���� - �������� �����...";
			link.l1 = "� ���������, ��� � �����������?";
			link.l1.go = "MCCaracasAfter_1";
		break;
		case "MCCaracasAfter_1":
			dialog.text = "�, � ���������-��? �� ������ ��� ���������, � ��� ��. �� ����� ��� �� ������ �� �����"+ GetSexPhrase("","�") +", ��� ���� �� ������ �"+ GetSexPhrase("��","��") +"? ��� ��� �� � ��������, ��������� ����...";
			link.l1 = "��, � ������ �� ������, ��� � ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MC_endCaracas");
		break;
		
		//*************************** ����� "������������� ������ "�����"" **********************
		case "Andre_Abel_Quest_TavernOwner_Dialog_1":
			dialog.text = "��, ������� " + GetFullName(pchar) + "! ����� ����� ���� ��� ��� �����. ������ ��������� ��� ����� � ����� � �������... ��, ��� ����! ����� �������� ��� ������� - ������, �������������, ������� ������ �� �������, � ����� �� ����������. � ���, ���� � �� - ����� ������! ��-��-��...";
			link.l1 = "���!.. ������ �������� � ����� �� ������"+ GetSexPhrase("","�") +". �������� ���� �������, �������� ����...";
			link.l1.go = "Andre_Abel_Quest_TavernOwner_Dialog_2";
		break;
			
		case "Andre_Abel_Quest_TavernOwner_Dialog_2":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "13");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			CloseQuestheader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek");
		break;
		
		//******************* ���� ������ ����������. ����� ���������� (����� � 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "��� �� ���� ���� ��� ��������... ������ ����� ����-������ �� ������������.";
			link.l1 = "����, �������.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ���� ������ ����������. ������� �������� (����� � 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "�� �� ����������� � ����, �����"+ GetSexPhrase("�","���") +".";
			link.l1 = "� ������"+ GetSexPhrase("","��") +" �������������� ������� �������, ��������. ��� ����� ��� �� ��������� ������?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "��������, �����"+ GetSexPhrase("���","��") +" �������, �� ��� ���� ��������, � � �������...";
			link.l1 = "�������� �����, ��������, � ����������� ����������. ��� ������� ���� ������ ��� ���������� ����?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*10;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "���� �� ������� � ����� �����"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", �����"+ GetSexPhrase("���","��") +" �������, � �� ������� � ����� ��������� ����� - ��� ��, ��� � ���� ���� ��� ���� �������.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "����� ������ � ����� ���� �����������. �� ����������, ��� ���� �� ������� ���, � ������� ������ �����������!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "������� �������... ������ � ������� ���� ��� ������";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "���� �� �� �������"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", �����"+ GetSexPhrase("���","��") +" �������.";
				link.l1 = "� ������ ��� ���� � ������ ��, ��� �� ������� � �����.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// ���� ��������
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// ������ ���. ����� �������� �������!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // ������ ��������. ����� �������� �������!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // ����������. ����� �������!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // ����� ��������
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "���, �����"+ GetSexPhrase("�","���") +", ��� �� �����.";
			link.l1 = "��� ������ '�� �����'?! �� ���� ����������� ��� ���� - �� �������. �� ��������� ���� ������ - �� �������. ��� ���������� ����� - � �����"+ GetSexPhrase("��","���") +". ��� ��������, � ���� ������. ������ ��� '�� �����'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "������, �����"+ GetSexPhrase("���","��") +" �������, ��� ��� �� ����� ������. � ������� ������ ���� ����� ������ ��������, � ���� �� ��������, ��� �����-������ �� ������ ������������, � ��������� ����� ��� ��������.";
			link.l1 = "��� ��� - �� ����� ������? ������, �� ����� �������� ���� �����? �� �����, �� ��� �������?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "��� ��� �� ��� �������, �����"+ GetSexPhrase("�","���") +". ��� ��������� ��� ��� ����� �����, � �� � ����� ���� ����, ��� ���������� �� ����, ���� ��������� ������� ���� �� ���������. ����� ���������� �����������, ������ ��� � ������, � ������ �� ������ ��������� ���� ����. � ��� ��� ��� ������� ���������� ������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + " � ��������� � ����� ��������� �����. � �� ��� ��������� ������ ������������ - ����� �� ������� �������������� ������ ������ - � ����� ������� �� ������������ ����� ������ ����������� ����������.";
			link.l1 = "�������� ���, ���� ������, �� ���� ������� �����, ��� ��� ����������� ����������� ������� ����������, �� ���� ���� �� ����������, � ��������������� ��������, ����� ��������� ����������, ������� ����� �����������, � �������� � �������� ����, ��� �� ��� ��������... � �����"+ GetSexPhrase("","�") +" �� �������� �� � ���� � ��������� ��� � ������� � �����������.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "�����"+ GetSexPhrase("�","���") +"... �����"+ GetSexPhrase("���","��") +" �������... �������, � �����, � �� ����� ������� �����. ������ ��������� �������� ����� ���������, ����� �� ����������� ��� � ����� ���������� �����...";
			link.l1 = "����������, ��������, ���� ��� � ����� �������, ������ ��� ��, ���-�����, ������������ ��������, ������ �������� �� ��������������, � �� � ����� ������� - �� �����, ��� ��� ����� ����� �����. �����-�� �� ����, � ����� ����...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// ���� ��������
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// ������ ���. ����� �������� �������!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // ������ ��������. ����� �������� �������!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // ����������. ����� �������!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // ����� ��������
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		case "Pirates_1":
			dialog.text = "����� ���, ������������"+ GetSexPhrase(""," � ����") +" �����, ������� ���������! ������ �� ������� ������ �������... �� �� �������, � ���� �����, ��� ����������� ������� - ��� ������. �����, �������?\n������-��, ��� ��� - ������� �'�����, ����.. ���� �� ��� ��� ��� �� ������. ����� ����� ��� ������������ ��������, ��-��. �� �� �����.";
			link.l1 = "��������... �������, ����������. �� - ��� ����� �����, ��� ���������� � ����������� ������� � ����� ���� ��� �����! ������ � ��� ����! ��� ��� �������! � � ������"+ GetSexPhrase("","�") +", ��� �������-�� ����� ���������� �������� �������� �� ��������� �� ������ ������!";
			link.l1.go = "Pirates_2";
		break;
		case "Pirates_2":
			dialog.text = "�������-�� �� ������... �����"+ GetSexPhrase("�","���") +". ��� ����� ������� � ������ ����� ����������. ���� ���������, � ��� � ������.";
			link.l1 = "��, �������, �� �����. ������� ������ ��������� � �������� � �����. ";
			link.l1.go = "meeting";
		break;
		
		case "Charles_1":
			dialog.text = "�� � ���������, ��� �� ������. ���� ����... ��, ����������� ������� ��������� �������, ������� ��������� �������, ��� � �������� ��������� ��� �� ������. �� � ������ �� ���� �����, � ����� ����, ��-��-��...";
			link.l1 = "��, ����-�� �� �� �������������... �����, �� ���� ���������������. �������� � �����.";
			link.l1.go = "meeting";
		break;
		
		case "Portobello_1":
			dialog.text = "��-��-��, ��� ��� � ����, " + GetAddress_Form(NPChar) + "! ������ ���� �������. � �������� ������������ ���� ����� ��� �� ����������!";
			link.l1 = "� ��� ��� ���������� �������, ��� �� �� � ����� � ��������. � ��� �� ����� ������� � ������ ����-�����. � ��, ��� �� ����� �� ���������, ������������ ���� ������...";
			link.l1.go = "Portobello_2";
		break;
		
		case "Portobello_2":
			dialog.text = "�-�-�... �� ����� �� ���� �������� ��� ������, "+ GetSexPhrase("��������","�������") +". ������� ��� ���... �������. ��, � ������� ���� ����� ������� �� �������, ��-��.";
			link.l1 = "�����, " + npchar.name + ", ���������, ������ �������� � �����.";
			link.l1.go = "meeting";
		break;								
		
		//���
		case "Seek_Carlos":
		if (pchar.questTemp.Headhunter.Chance == 1)
		{
			dialog.text = "��! ��� �� ���-�� �����, � �������! � ��� ����� ����� ���� �����. �������, �� ������ ���� ���.";
		}
		else
		{
			dialog.text = "��... ��� �� � ���� � ��� �����. � ������ ���� - � �������, ����� ��, ���������.";
		}
		link.l1 = "�������! �� ��� ������� �����!";
		link.l1.go = "exit";
		pchar.questTemp.Headhunter = "hunt_carlos_fight";
		break;
		//���
		
		//������
		case "w_find_desouza":
			dialog.text = "�� �������� ���� ���� ����, ������� ��������. ��� ������� �� �� �������, ��� �� ���������� ��������, �� ���� �� ���������. � ����� �������� ������ � ����� �������� � ������ �� ��������. ����� ����������� ������ ������ ������������, ����� �������� � ���� �����.";
			link.l1 = "� �� ����� ������������, ��� ��� �������� �����������. �� ������ �� ����� ��� ���������� ��� ��� �����, � �� �� ��� ����?";
			link.l1.go = "w_find_desouza_1";
		break;
		case "w_find_desouza_1":
			dialog.text = "�� �� ������ � �� ����� ����� ������������, � �� ������ ��� ��� ����� ������. ��, � ������ �������, ������ ���� ��������������, ����.";
			link.l1 = "� ���� ��?";
			link.l1.go = "w_find_desouza_2";
		break;
		case "w_find_desouza_2":
			dialog.text = "� ��� ������ �� ������� � ������� �������, ������ � ���� ��� ��� �����������. ����� ����, ����� ���������� ����� �����. ������ �����.";
			link.l1 = "������. �� �����, ������, �� ����.";
			link.l1.go = "w_find_desouza_3";
		break;
		case "w_find_desouza_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "�, ������ ������ ����. � ����������� ��� � ����������� ����.";
			link.l1 = "� ����������?";
			link.l1.go = "w_find_desouza_4";
		break;
		case "w_find_desouza_4":
			dialog.text = "���������� �� ����, �� � ���������� �� ��� �� ����� ������ �� �������, ��������� �������.";
			AddQuestRecord("WhisperQuestline", "4");
			pchar.Whisper.FindDesouzaHol = true;
			link.l1 = "�����, ������.";
			link.l1.go = "exit";
		break;
		//������
		
		//Lipsar ����� ������� ������ ������
		case "MaksQuest_1":
			dialog.text = "�������� �� ����� ���� ������� ����, � ����� � ������� �������.";
			link.l1 = "�������, �����.";
			link.l1.go = "exit";
			DeleteAttribute(Pchar,"Luke.SpawnMaks");
		break;
		case "LukeQuest_1":
			bDisableFastReload = true;
			dialog.text = "��� ������ �� ����, � ������� ����� ����� �� ����, ���������� � ���, � ��� ���� ������. � ����, � ���� �� ����.";
			link.l1 = "��� �� ��! ��� ��� ��������� �� ����������?";
			link.l1.go = "LukeQuest_2";
		break;
		case "LukeQuest_2":
			dialog.text = "�������� ������, ������ ���������� � �� ��������� �� ����.";
			link.l1 = "�����, ������� �� ����������.";
			link.l1.go = "exit";
			link.l2 = "�����, ������� �� ����������. �����, � ���� �������������.";
			link.l2.go = "Pay1000";
			Pchar.Luke.Info = "Fight";
			AddDialogExitQuest("ChangeLukesHome");
		break;
		case "Pay1000":
			dialog.text = "�������, " + GetSexPhrase("���","�����") + ", �� ������."
			link.l1 = "��� �� ������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(Pchar, -1000);
			Pchar.Luke.Info = "Peace";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� �� ���� ������
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� �� ���� ������
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
