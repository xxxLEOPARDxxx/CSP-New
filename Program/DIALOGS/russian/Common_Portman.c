#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	int license_price = sti(PChar.rank) * (2500) * (0.01 * (120 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));;
	int license_expires = rand(2);
	
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ��� ������
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

	// ����� ������� �� ������� -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int i, cn;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;
	
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 ����� "��������� �����". ���� ������ �� - ���� �������, �� ��������� ����� ������ �� ���� �����
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // ����� ��������
	ref rColony;
	string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //��� ������ �����

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}

	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // ����� � �����
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // ����� � �����
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//������

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //��������� ��������
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//�����-�� ������� ������� �������, ���� ��� ��� � �� ������ ����
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);
		// ������ ��������� -->
		CheckForReleaseOfficer(iChar);//���������� ������� � ����������, ���� �� �� ������ ��������
		RemovePassenger(pchar, compref);
		// ������ ��������� <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);

		DeleteAttribute(chref, "ShipInStockMan");
		chref.id = "ShipInStockMan";//���������� ������ � ������������, ����� ���� ����� ������� � ��������� ��� ����� ���� ������
		DeleteAttribute(chref,"ship");//�������� ������ ������� � �������
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//��� � ������� ������, ���� ����� ��������� �� �������? 

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//��������� ������, ��� ���� ������������� ��� �� �����������
	}

	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // ����� � �����
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // ����� � �����
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // ����� � �����
		Dialog.CurrentNode = "BurntShip19";
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		case "First time":
			NextDiag.TempNode = "First time";
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
			//homo
			//homo ������� �����
			if (Pchar.questTemp.CapBloodLine == true )
			{
				dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
									"��� ������ ���, ����� ����.",
									"������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
				Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";
				break;
			}
			//homo
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "����������� ���, " + GetAddress_Form(NPChar) + ". ��, �������, �� �������. � "  + GetFullName(npchar)+ " - ��������� �����.";
				Link.l1 = "������������, " + GetFullName(NPChar) + ". � " + GetFullName(PChar) + ", ������� ������� '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("����������� ���, " + GetAddress_Form(NPChar) + ". �� �� ��� �� ����?",
									"������������, " + GetFullName(Pchar) + ". � �����, ��� ��� ������� ����� � ����, � ��� ������, ��� �� �� ��� �������.",
									"�, ������� " + GetFullName(Pchar) + ". ��� ������� ��� �� ���?");
				Link.l1 = "������������, " + GetFullName(NPChar) + ". � ���� � ���� ����������.";
			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// ��������� ��������� 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "���������. � � ����� �������, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// �������� ������ ����
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "���, ��� ��� � ��������? �� �������� ��� ���� �� 1000 ��������?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "��, ������"+ GetSexPhrase("","��") +". ��� ����� ������ �������. ������ ����������!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("���, ��� �� ������"+ GetSexPhrase("","��") +"...", "��� ���...", "��� �� ������"+ GetSexPhrase("","��") +", �� ����� �������...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "��������� �������� ��� ���� �������. � ��������"+ GetSexPhrase("��","���") +" �� ����� ������ ������, ��������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", ����� �� ��������� �����, � � ���� � ���� ������� ����. ������ ������� ��� ��������, �� �, � ���������, �� ����������"+ GetSexPhrase("","�") +", � ����� ����������� �� �����.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// ������ ���� ��� ����
				{
					link.l1 = "�������� ��������� �����, ��� ����� ���������� � ����� '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "', �������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // �� �����, � ���� �������!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // ���������� � ��������� �������
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
		
			dialog.text = "���������. � � ����� �������, " + GetFullName(PChar) + ".";
			if(NPChar.city != "Pirates")
			{
				Link.l2 = "����� ����� ��������� ������? ��� ��������?";
				Link.l2.go = "node_4";
				Link.l13 = LinkRandPhrase("� ��� ��������� ���������� �����, ������������� ������������� ��� ����� ��������. ��� �� ����� �������?","��� �� � ��� �� ������� ����������, �������� ��������� �� ������ �������?","� ���� �������� �������, � � ���� ������������� �������� ������ ��� ��������� ����������. ��� �� � ��� �����?"));
				Link.l13.go = "work_PU";
				Link.l3 = "���� � �������� ���� �� ����� �������� �� �����?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "� ���� ������� ���� ������� �������.";
				Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "� � ��� �� ���������� �����.";
				link.l5.go = "LoanForAll";//(���������� � ��������� ���������)	
			}
 			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //����� ���� - �� ����� � ����� �������
			{
				link.l7 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "���� ���������� ��������, ������� ���������� � ����� �������� ����������.";
			link.l6.go = "CapitainList";
			if (bBribeSoldiers ==true && GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
				if (!CheckNationLicence(sti(npchar.nation)))
				{
					link.l77 = "� ��� ������� ��� �������� ��������, �� �������� ����? ����� �������� �� ������-������ ��������? ";
					link.l77.go = "BuyLicense";
				}
				}
			//���
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "Houm" && npchar.nation == ENGLAND)
				{
					link.l12 = "�� ����������, �� �������������� �� � ��� ������� '������� ������' � ��������� ���������� ������?";
					link.l12.go = "Houm_portman_1";
				}
			}
			
			link.l8 = "� �� ������� �������.";
			// Warship 26.07.09 ����� "��������� �����"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // ����������
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "� �� ������ ����� ������ ...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "� �� ����������� ���"+ GetSexPhrase("��","��") +" ��� ���� ����� ������� ����������.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "� �� ����������� ���"+ GetSexPhrase("��","��") +" ��� ����, ��������� ���-�� ���������, ����� ������� ����������.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}
			if (CheckAttribute(pchar,"Whisper.ActiveChardQuest") && !CheckAttribute(pchar,"Whisper.PortmanAtSea") && GetNpcQuestPastDayWOInit(npchar, "Whisper.LastSeenPortman") > 7 && GetNpcQuestPastDayWOInit(pchar, "Whisper.LastSeenPortman") > 7)
			{
				Link.l11 = "� ��� �������� �� ����� ����� �������. � ��� � ������� ����� �� ���������?";
				Link.l11.go = "Whisper_chard_quest";
			}
			
			Link.l15 = "���������. �� ��������.";
			Link.l15.go = "exit";
		break;

		case "Whisper_chard_quest":
			SaveCurrentNpcQuestDateParam(npchar,"Whisper.LastSeenPortman");
			if (!CheckAttribute(pchar,"Whisper.PortmanTries"))
			{
				pchar.Whisper.PortmanTries = 0;
			}
			pchar.Whisper.PortmanTries = sti(pchar.Whisper.PortmanTries)+1;
			if (npchar.nation != HOLLAND && npchar.nation != SPAIN)
			{
				if (sti(pchar.Whisper.PortmanTries) > 2)
				{
					WhisperSpawnPortman(npchar);
					SaveCurrentNpcQuestDateParam(pchar,"Whisper.LastSeenPortman");
					//SaveCurrentQuestDateParam("Whisper.LastSeenPortman");
					dialog.text = "��� �����. �� ������ ������� ������� ����. �������, ���������� � ������� "+XI_ConvertString("Colony" + pchar.Whisper.PortmanTargetCity)+". ���� ������������, �����, ��� ������� ��� �������.";
					link.l1 = "���������, � �����. �� ��������.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "��... ���, ����� � ���� ���� �� ���������.";
					link.l1 = "��������� �� ����������, � �����. �� ��������.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "���? ���� ��� ����������, �� ���� ��. �� �� ������� � ���� ������ � �������������� �������.";
				link.l1 = "������� � �� ���, � �����. �� ��������.";
				link.l1.go = "exit";
			}
		break;
		
		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "���� �������� ����� ���������. �� ������ ���������� � ������ ��������� ������ ���������, � �������� ��� ��������� ���������� � �������� ����� ������ �����.";
			link.l1 = "� ���������, �� �� ��� ������. ������ � ����� ����� ��� ���� ������ �������� �����... �� ����������� ����������.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "���. ��� ��� �������. ��� ����� ������� ������ � ������� �������, ��� ��������� �������. � � ���� ���, ��� ��������, ����� - ������...";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "� ��� ��������� �������, �-� " + GetFullName(NPChar) + ", � �����"+ GetSexPhrase("","�") +" �������� ������� ���� �����... � �������, ������, 1000 �������.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // ����� ����� ��������.
				link.l1 = "�-��... � �����-�� � ���� � ����... ������� �����...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "�������! ������ ���������, ��� ��� � ���... ������... ���... ���, ����������. � ������� ������� �������� ��������������, � �����, ���������� ������ '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' ��� ����������� �������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + " ����������� ������� � ������� " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "�-�-�!... �� ����, ��, �� ������� �� �����������, ��� ��� � �����, ����� ������� �������. ������... ���... ���, ����������. � ������� ������� �������� ��������������. �����, ���������� ������ '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' ��� ����������� �������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + " ������ ������� � ������� " + XI_ConvertString("Colony" + sColony + "Gen") + ".";			
				link.l1 = "��������� ���, ������, �� ������� ��� ������������� ������� ������.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","��"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "��� ������ �� ������ ������?";
			link.l1 = "�������, �� �������� �� ����� ����� �������� � ��� ����?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "��... ��������� ������, � ����� ����� �� ��� ������������?";
			link.l1 = "� ���� � ���� ����. ���� �� �� ��� � ����� ����� ��� �� ��...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "�� ���. �� - ����� ������ ��������� - �� ����� ��� ������� �����, ������� ���������� ������� ���, �������, �� ������ �������� � ���������� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". � ���, ����������, �������� ���� ������, ���� ��������� ����� � ��� ����.";
			link.l1 = "� ����� ������ ��������� ��� �����, � ��������� �� ������.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Dat"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // ���������� �������� � �������, ���� ���������� ���.
			if(rand(2) == 1) 
			{
				Log_TestInfo("��������� ������� - ���������");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // ���� - ��������� ������� ����� ���������
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "��� ������ ��� ����������, �����"+ GetSexPhrase("���","��") +" " + GetFullName(PChar) + "?";
			link.l1 = "�������, �� ������� �� � ��� ���� ���� �������?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "��, �������... ��� �����, ��� � � ����������� ������, ����� �� ������� ��� ���������������� ����.";
			link.l1 = "�� ����, ��� ����� �� ��� ��������� �����?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "��, ��������"+ GetSexPhrase("�� ��������","�� �������") +". ���� ����, �� ���������� �������� �� ����� ���������� ������, ������� � ��� ��������� ������������� �������. ����� ������ ��� ����� �� ������ ����, ��� �������� ����������� ������, � ��� ���������� ������� ����� ������������� � ������ ���������, � ����������� ��� ������ �������� ����� ��� �������� �������. �� ��� ������ ���������� � ��������� ������� ������� ��� �� ����... �� ���� ����, �� ���� ���� � ������������ �������!";
			link.l1 = "�����������, �������� " + NPChar.Name + ", � ��������� � ���, ��� ����-�� ������ ������� �������, ��� ���. �� ��� ������ ����� ��� ���������, � ��� ������ ��������� ����������� � ���� ���������... ��������� �����������.";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // ���������� �������
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // ������� � ���������
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // ������ ���� � ����� �������
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // ������ �����, ���� ������ �� ����
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // ������ �� ����������
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "�����-�� ���������! ��, � ���� ���������� ���� �������� �������� ����������������. �� ������ �����, ��� ����� ����� ��������� �� ��� � �������� ������. ��������� �����, �������!";
			link.l1 = "���������!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook");			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "�����-�� ���������! ��, � ���� ���������� �������� � ��� �����, � ��� ��������. ";
			s1 = s1 + "���� ��������������, �������, ������ ��� �����! ����������, ���� ����� ������ ���� �������������. ";
			dialog.text = s1 + "������, " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " ������� �� ������� ��������� �������?";
			link.l1 = "���������� ���!";
			link.l1.go = "exit";
			link.l2 = "��� ��, ������ �������� �����, �� � ������ �� ������. ��, � �������� ���� �����������, "  + npchar.name +" .";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "�� �������� ������� ��� �����������?";
			link.l1 = "����������, ���!";
			link.l1.go = "exit";
			link.l2 = "�������. ���� ������"+ GetSexPhrase("","�") +", ��� ��� ������ ����� ������.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "6");			
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
			dialog.text = "�� ��� �� ���������?.. � ��� ���� ���� ����? ����? ���, ����� ����� - ��������, ����� � ���������...\n��... � ������ �������������� ����, ��� � ����� - �������, ����������.";
			link.l1 = "�������. � ������� � ��������. ���-�� ��� ������������, ��� ��� �� ���� �� �����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "�, ��� �� � ���� �"+ GetSexPhrase("�� �������, ������� �����","� �������, ������� ��������") +" ����� �������� ���� � ������� ��������?";
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
		
		case "node_4":
			//--> �������� ����������� ���������� �����. 
			if (npchar.quest == "PortmansJornal") //���� ����� �� ������� ������
			{
				dialog.text = "�� ������ ���� ����� �������� �� ����� " + npchar.quest.PortmansJornal.capName + " � ������� ��� ������� ������. �� ������� ���?";
				link.l1 = "���, �� ���������� ����...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //���� ����� �� ������ ����������� �������
			{
				dialog.text = "�� ����������� ��������� ���������� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. ���� �� �� ��������� ��� �������, �� � ����� ������ ���������� �� ����� ���� � ����.";
				link.l1 = "� �������� ������, �����.";
				link.l1.go = "exit";
				link.l2 = "���� ���������� �� ���������� ������ ���������.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //���������� ������� ���� �� �������
			{
				dialog.text = "�� ������� ��� ��������� ���������� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. �� ������� ���?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName &&
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//���� ������ ������� - � ��
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}
				if (bOk)
				{
					link.l1 = "��, � ���"+ GetSexPhrase("��","��") +" ���, ����� � ����� �� �����. ������ ��������.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "� �������� ������, �����.";
					link.l1.go = "exit";
				}
				link.l2 = "���� ���������� �� ���������� ������ ���������.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- �������� ����������� ���������� �����. 

			//--> ���� ����������� ���������� �����. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("��, ���� ������! � ���� ���� ��� ��� ������!", 
					"��! �� ��� ������ �������! � ���� ���� ���� ��������, ��������� ����������.", 
					"��� ��! �������, � ���� ���� ������! ��������, ������ ��, ������ ��������...");
				link.l1 = "��������� ���� ����, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 ����� "��������� �����"
			if(dRand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "����! ������� " + GetFullName(PChar) + ", �� ��� ������ �������! ������������ ����� ���������, ����� ���������... � ��� �� ����� ������� �����, ����������� �� ��������� ��������� ����������! �� ���������� �������� ������� �������... �� ����� ����������...\n" +
					"�������, �� ��� �� ��� ����� ���������-��? ���� ������� ��� ����� � �������...";
				link.l1 = "��, ��� �������� - ����� �������. � ��������� �������� �� ���? ��� �� ��� �� ������������?.. � ����� ��������, ��� �������. � ������ ���� �� ������� �������, ��...";
				link.l1.go = "BurntShip4";
				link.l2 = "� ������ ��������� ��� �� ������� �� ����� �����, � �� �� ���. �� ���� ������� ��� ���� ������ �����������, ���� ����� ��������. � �� �������������"+ GetSexPhrase("","����") +", ��� ��� ��������, �� �� ������...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- ���� ����������� ���������� �����.

			dialog.text = "���������� ������ �� ������������ ������ - � ���� ������ ���� ������. �����, � ������� ����� ���� ���������������� �����, �� � ������� ������ �������� ���������.";
			Link.l1 = "��� ���� ������.";
			Link.l1.go = "node_2";
			Link.l2 = "���������. �� ��������.";
			Link.l2.go = "exit";
		break;


		/////////////////////////////////////////////////////////==========================/////////////////////////////////////////////////////
		//������-���������
		case "work_PU":
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("����� ��� ������ ��� ���, ��� ���� ��� ������ " + NationNameGenitive(sti(pchar.nation)) + "! �������� ��� ������� ����������!", "� �� ������� ������������ � " + NationNameAblative(sti(pchar.nation)) + ". ��� ������!");
				link.l1 = RandPhraseSimple("��, ���� �����...", "��, ��� ������...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("� ���� � ������� ����� ������ ����������, ������� ���� �������� �����. �� �����, ����� ��� �� ������� ������, ������� �� ���������� �������������� ��� ����� �������. ���������, ������ ��, ����� ������, � ������ ����� �� ������� �����������, ��� ����� � �����...", "�� ��� ��������� ���������� ��������, ������� ����� ������. �� ������ ������������ ������, � �� ��������� ���� ����������� ����� �� �������. �������� ������ �����, ������� ����� �� ���� �� �����, �� ���� �������� ��� ��������� �� ������.");
				link.l1 = LinkRandPhrase("����-�?! �� ���� �� ����.", "������ ��� ���� ������?! ��, ������, ���� �� ���.", "��� �� ������� ����� �����! ������� �� � ���� - ����� ���������� �����!");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "�� ��� �� ���� ������� ��������� ������ �� ������, � ����������, ������� ������ ��������� ������������� ��� �������� ���� � ������ ����� ����������. ���� ����� ���-�� ���������, �� ����� ����� ����������.";
			link.l1 = "� �������� �������� �� ������, ���� �� ���� �����.";
			link.l1.go = "work_PU_1";
			link.l2 = "���������� �����? � ���� ��� ��� ���� ��������� �����.";
			link.l2.go = "work_PU_2";
		}
		else
		{
			dialog.text = "� ������� ���� ���? �� ��� - �� ����������� ����� ���������� ������ ������"+ GetSexPhrase("��","���") +"?";
			link.l1 = "��, � �� �����...";
			link.l1.go = "exit";
		}
		break;

		case "work_PU_1":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
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
						dialog.text = "�� ��� ������� ���� ������� ����������. �� ������ �������� � ����� �������, ������� ��� �� ���� ����� �������� ������������� ��������.";
						link.l1 = "�����, �� �������"+ GetSexPhrase("","�") +". �����, ����� �����, ���� ���������� �����.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(6) > 1)
						{
							dialog.text = "�� ����, ����� �� �� ����, �� ���� �����, ��� ����� �������������, ������ ��� � ���� ���... �-�-�, ��� ��� ��� � �� ��������!";
							link.l1 = RandPhraseSimple("�� ��� ������ ������? ������������� �������� ��� ���������� �����?", "� ��� �� �����? � ��� ����� ����� ����?");
							link.l1.go = "ConvoyAreYouSure_PU";

						}
						else
						{
									dialog.text = "������ � ���� ����� ���������, ������� ����� �������������, �� ������, ��� �����, ������ ���. ����� ����, � ������ ���� ��� ������� ������.";
							link.l1 = RandPhraseSimple("�����, �� ��� � ���� ���.", "��, �� ������... �� �����, ������.");
							link.l1.go = "exit";
						}
					}
			  	}
				else
				{
					dialog.text = "�� � ��� ��� ���� ��������������. � ������ ��������� ��� �� �������� ��������� ����� ������������ - ������� ���-�� ����������. �� ���� �������� �� ��� �� �����. ��� ��� ������� ��������� �������, ����� �� ���������.";
					link.l1 = RandPhraseSimple("���� ����� �������� ���������� �����. � �������� �� �� � ��������, �� ����� ���������... ��, �� �����, ��������.", "��� ��������... �� �����, ����� ��������.");
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

		case "work_PU_2":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
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
					dialog.Text = "����� - �� �����, � ���� ��� ������� ��� ��������� ��� �������, �������� ����� �����. �� ��� � �� �����!";
					link.l1 = RandPhraseSimple("��� �� �������, ����� ��� �� ���� �����?", "� ��� �� �������? ����� � ��� ���� �����?");
					Link.l1.go = "PassangerAreYouSure_PU";
				}
				else
				{
					dialog.text = "� ���������, ���������� ������� ���. ��� ��� �� ����������...";
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

		case "ConvoyAreYouSure_PU":
			dialog.text = RandPhraseSimple("�� ������ �������� ��������. � �� ���� - ��� �� �� ���-������ ���� �����������, ��� � ��� �� ��������.", "�� ��� � ����, � ���� ������ �� ���������. ���� �� � ���� �������.");
			Link.l1 = "����. ������ �������, ���� ��� �����.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity_PU(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;

		case "PassangerAreYouSure_PU":
			dialog.text = RandPhraseSimple("�� ������ ���������� ��������.", "������ �� ���? ������ ������������� ��������.");
			Link.l1 = "�������, ������ � ����������.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity_PU(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;


		case "PortmanQuest_NF":
			dialog.text = "��, ��� �����. � ����� ������, �� � ����� ����� ������ � ���� �� ����� ���� � ����.";
			link.l1 = "�������. ��� ��� ��� �����"+ GetSexPhrase("","�") +" �������...";
			link.l1.go = "node_2";
		break;
		
		// Warship 25.07.09 ����� "��������� �����"
		/*case "BurntShip1":
			dialog.text = "�� �����, �������, �� ��� ���� �����, ��� � �������-�� �� ������ ����... � ��� �� ����� ������� �����, ����������� �� ��������� ��������� ����������! �� ���������� �������� ������� �������... �� ����� ����������\n" +
				"�������, �� ��� �� ��� ����� ���������-��? ���� ������� ��� ����� � �������...";
			link.l1 = "���, ��������, ������� �� �� �������, ����� �� �� � ��� �� �����������.";
			link.l1.go = "BurntShip3";
			link.l2 = "� ������ ��������� ��� �� ������� �� ����� �����, � �� �� ���. �� ���� ������� ��� ���� ������ �����������, ���� ����� ��������. � �� �������������"+ GetSexPhrase("","����") +", ��� ��� ��������, �� �� ������...";
			link.l2.go = "BurntShip2";
		break;*/
		
		case "BurntShip2":
			dialog.text = "����� ����, �������... ����� ����, ��� �� �� ������ ��� ������.";
			link.l1 = "��� �� � ������� ����, ���������. �� �� ���� ���������... �� ��������...";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		/*case "BurntShip3":
			dialog.text = "��, ��, �������. � �����, ��������� ��������... �� ��� ��� ������ ������� ������ ��������� �� ���������. ��� ����� ������ ������ ���������� � ���� ������ ����.";
			link.l1 = "��, ��� �������� - ����� �������. � ��������� �������� �� ���? ��� �� ��� �� ������������?.. � ����� ��������, ��� �������. � ������ ���� �� ������� �������, ��...";
			link.l1.go = "BurntShip4";
		break;*/
		
		case "BurntShip4":
			dialog.text = "�� ��� ��, �������?! ��������� ����!.. ��� �����?! � ��� ���� ����� ����, ��� ������� ��� �����. � ��������� �������� ����, � ��������� ������� ������� ������ ����������, � ����� ��������� �������, ������ ���.";
			link.l1 = "���������, ��� � ��� �� ���� ��������? �� ������ ���������� �����-������, � ���������� ����, �  ��� ���������� � ���� �� ����������?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "�� �� ���� �� ����, ���� �� ����, - ������� �������, ����� �� �� ������� ��� ������. ��������� ���� ���, ��� ���� ���� ���, ����� ���� �������, ��������� ���� �����!\n" +
				"� ��� �������� � ���, ��� �����-�� �����������... ������ ������������, ���������� �� ��� ������ ��������� " + sCapitainId + ". � ��������� ��� � ������ �� ����������, � ������������� ����������������. " +
				"� ���� ������ �������� ����� �������� � ��������� ��� �� ������, ������ ������, ������ �������... ��� � ������ ��� �����? ���� � ����� ����, ��-����...";
			link.l1 = "�-�, ����, �� ������� ������. � ��� � ���� �� ��� ����, ��� � ���� �����? �� ����, ��� � ���� ��������� ���� �������� ��� ��������?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "� ��� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " �������� �� ����� ���� ����� " + NPChar.Quest.BurntShip.ShipNeededValue + " �����. ��� ������ ��� ��������� �������� ����... �� ������ ����� ����� ���������� �������� ���� �� ���! ׸�� ����� ��� � ���� ������ ������ � ��� ��������� ��������...";
				break;
				
				case "turnrate":
					attrL = "� ��� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " ������������ ���� ����� " + NPChar.Quest.BurntShip.ShipNeededValue + " ������. ��� ��� ����� ��������� �������� ����... �� ����� ������ ���� ������������! ׸�� ��� �������� �������� � ���� ���� ��������...";
				break;
				
				case "capacity":
					attrL = "� ��� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " ������� ��� ����� " + NPChar.Quest.BurntShip.ShipNeededValue + " ������ �������������. ��� ����� ��� ��������� �������� ����... �� ���� ��� ���� ����������. ׸�� ��� ����� ������ � ���� ��� ������ ��������!";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "� ��� �� ����� �������? ������� ����� ����� ��������� ����������?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "����� �� ������. � �� � �� �������� ������ ����� � ��������. �������, ��� �� �������� ������ ���� �������. �� ��� ��, - � ��� �������. �������� ������ �� ������ ����� ��������� ���������, ��� �� ������������. ���� �� ������ ��� ������� ���������. ����� ��� �� �������� ����� ��������� �������� �������� ��� ����. � �� ��� ����� ���������, ���������, ���� ������ �� � ��������� ���\n" +
				"� ����� �����������, � ��������� �������� �� ����������. ����-�� ������������, ���� ���������. ���� ����� � ��������� � ������ ������������ ��������� �������?";
			link.l1 = "��, ���� �� �������. � ������� � ���� ���� �������?";
			link.l1.go = "BurntShip8";
			link.l2 = "���, ��������, �� �������� � �� ���. �� � �������� ����� �� ����, ��� ����� � ��������� ���������������� ����������. �� ��������...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "�����, ����� ����, ����. ������ ����� � ������ � ����� �������� �� ��������.";
			link.l1 = "��� �, ������. �������� � ��� �������� �����. �� ������, ���� ������ ��������� � ���������� - ����� ��� ����� � ��� �� ������!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "�� ��� ��, �������? ��� �����? � �� �������, ��� ��� �� ������� �� ������ ���� ��������, ��� ����� �����������... �� ������ ��������� �����, � �� �� ������������. ������ �������...";
			link.l1 = "�������... ����� ���� � �������� �������. �� ��������.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 120, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "��������. � " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " �������� �� ����� ������ ���� �� ����� " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "������������. � " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " ������������ ������ ���� �� ����� " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "�����. � " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " ���� ������ ���� �� ����� " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // ������� ���
			
			DialogExit();
		break;
		
		// �������, ����� �� ��������� � �����
		case "BurntShip10":
			dialog.text = "� ��� �� ������ ����������?";
			link.l1 = "� ��� ������� ��������� ��������� ����������, �������� " + NPChar.Quest.BurntShip.LastPortmanName + "? � ���� � ���� ����.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "� ��� ���... �������������? �� ��� ����� ������ ���������� ��������� � ����������� ��������� �����. ���� ������ ����������� ��� � ����, �� ��� ����� � �������� � ������� � ������. ����� ����, �?..";
			link.l1 = "��, ��� �������� ��� �������. ��������, ��� ����...";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// �� ���������� - ��������� �������
		case "BurntShip12":
			dialog.text = "� ��� �� ������ ����������?";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ��� ����� � ������������ ���������������. ��� ���������� ��������������.";
			link.l1.go = "BurntShip14";
			link.l2 = "������, " + GetFullName(NPChar) + ", ����� ��� �� ���������� ���� � ���������� ���� ���������������. ������� � �������� �� ����� ���������. ��������, ���� ������"+ GetSexPhrase("","�") +"...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "����� ����, �������... ����� ����, ��� �� �� ������ ��� ������.";
			link.l1 = "��� �� � ������� ����, ���������. �� �� ���� ���������... �� ��������...";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "��� ���! � ��� �� ���������� ���� ����� �����?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "��������, � ����� �����.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "��, �������, � ���, ��� �� ������ � ���! ���"+ GetSexPhrase("��","��") +" �� ��-���� �������, ������ ������ ���� �� ������... � ��� ����� �������, ������� �� �������� ��� ����� ���. ������������, ������ ��, � ���������� ��������� ����� ����� �������... � �� ���� ��������� ����� � �������. ��, ������ ��������, �������� ���������, �����������, ����� ��, �� ��������...";
			link.l99 = "�� �� ������, ��� � ������"+ GetSexPhrase("","�") +", ���� �������� ���������� � ��������?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "���-���, ���� �����! � ��� ����� ������, �� ����������. ������, ����, ��� ��������� ��� ����� ��, ��� �������, ���������� �������, � ������� ��������� ����� � ����. �� �� ������� ���� ���������...";
			link.l1 = "� ��� �����, ����� ������� ����� ������ � ��� �������. �� �������.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // �������� ����
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // ��������� ���������� �� �����
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "� ��� �� ������ ����������?";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" �� ���������������. ������ ��� ����� ��-�������� � ����.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "���������, ����������, ��� ��������. � �� � ����� ������������ ������, ������ ��, ������ �� ��������.";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "��������, � ����� �����.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "��, �����������! � ����� ������ ���� ��������������, " + FindRussianMoneyString(cn) + ". ������ ��� ��������� ������� ������� ��������� �����. ��������� ��������� ���������� ��������� - �������� ����� ���, ��������.";
			link.l1 = "� ���, ����� ����� ���� �� �������. � ������"+ GetSexPhrase("","�") +", ��� ��� ����� ����� ������� ������.";
			link.l1.go = "BurntShip21";
			link.l2 = "��� ��� ������ ������ ����. � ���"+ GetSexPhrase("","�") +", ��� ����"+ GetSexPhrase("","��") +" ��� ������. �� �������.";
			link.l2.go = "BurntShip20_exit";
			
			NPChar.Quest.BurntShip.Money = cn;
			
			//sTitle = "BurntShipQuest" + NPChar.location;
			//PChar.Quest.(sTitle).over = "yes"; // ��������� ���������� �� �����
		break;
		
		case "BurntShip20_exit":
			//AddMoneyToCharacter(PChar, sti(NPChar.Quest.BurntShip.Money));
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterReputation(PChar, 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "�� ��� ��, �������?! �������� ���, � ����, ��� ������. �� ����� ������ �� ����� �� ������ ��� �������� �����!";
			link.l1 = "����� � ������� ��� ����. �� ����� ��� ��� ������������... ��������.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterReputation(PChar, -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> ���������� ��������
		case "PortmanQuest":
			if (cRand(2) == 2)
			{	//����� ������� � �������� ������� ������
				dialog.text = "� ���� ����� ������� ������ ���� �������. ��� �� ���� ���� ����� �������!.. � �����, ����� ��� ������� � ������� �������.";
				link.l1 = "��, ��� �����... �� ��� ������ � ������!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "���, �� ���� ���� ����������. ��� ��� ��������, ����������...";
				link.l2.go = "node_2";
			}
			else
			{	//����� ��������� ���������� �������
				dialog.text = "� ���� �� ������� �������� ��� ������� �������. � ����, ����� �� ��������� � ������� ��� ���.";
				link.l1 = "��, �� ��� ��, � �����"+ GetSexPhrase("","�") +" ������� �� �������.";
				link.l1.go = "SeekShip_1";
				link.l2 = "��������, �� �������� �������� � �� ���������.";
				link.l2.go = "node_2";
			}
		break;
		// -------------------------------- ����� �������� �������� ������� �� ���������� ���� --------------------------
		case "PortmanQuest_1":
			dialog.text = "�������, ��� ��� ������... ��-�, ����� ���� � ���� �����! ������ �������� ������� - ����� ����������, ��������� � �� ����� ���������.";
			link.l1 = "��� �����, ���������� �����! ��, � ������ ���������� ��� ��������� �� ���� ���������� ��������.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //����������� ���������� �� ����������
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "��, �������! ��� ����� " + npchar.quest.PortmansJornal.capName + ", �� ������� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")) + " � ������ '" + npchar.quest.PortmansJornal.shipName + "'. ����� �� � ���� �������, � ���������� � " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "�������. �� ��� ��, � ��� ����������� �����. ��� ���� � �������?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " ��� � ���� ������������, ��� � ��� ���������. ������ ������������ ����� ��� �������, � ��� ����� ���������.";
			link.l1 = "����. ��, � ���"+ GetSexPhrase("��","��") +"...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}
		break;
		// -------------------------------- ����� ������� ����������� ������� ----------------------------------
		case "SeekShip_1":
			dialog.text = "���������! �� ������, ���������� ������� ����������� �� ���������� ��������, ��� ��� �� ����� ����� ��� ����. � ������� ������� �� ������...";
			link.l1 = "�������. ���������� ���������, ��� �� �������, ��� ����� ��������������� ��� �������.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //����������� ���������� �� ����������
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " � ������ '" + npchar.quest.PortmansSeekShip.shipName + "'. ������� ��� ����� " + FindRussianDaysString(rand(5)+10) + " �����. ��������� ����.";
			link.l1 = "��, ��� ��� ������ ����, ������, ��������. � �����, � ������� ������ �������� �� ����������...";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "��, �����. �� � ������ ��� ����� ������ ��������� �� ����. ������� ���� � �������, �� �������� ������� � �����, � ��� �� ������ ��, ��� ��� �����.";
			link.l1 = "�������. �� ��� ��, ��������� � �������. �������, ��� �������.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;
		case "SeekShip_break":
			dialog.text = "��, �� ��� ��, ����� ����. ����, �� ����� ������ ���� ������������...";
			link.l1 = "��, ������� ����� ������� ������ � ������� �����.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "�� ��� ��, ������� �� ��������� ������, ���� ��� � �� ���������� �������.";
			link.l1 = "�� �� ���...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� �� �������
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//���� ���-��� ��� ��� - ������� ���
			if (cn > 0)
			{
				characters[cn].LifeDay = 0;
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //����������� ������ ���� ������ ��� ��������
			ChangeCharacterReputation(pchar, -7);
		break;
		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "�������! ������, �������, ��� ��� �� ������ ��� �������, ��� ��� �������... ����, ����������, ��� �����! � ���� ��� � ���.";
				link.l1 = "��, �������������...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //������� ������
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "�����������! �� ��� ����� �������. �����������, ��������� ��� ���� ������.";
				link.l1 = "��, �������������...";
				ChangeCharacterReputation(pchar, 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
				AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "� ����� ��������� ��� ��������������. ��� ���������� " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " � ��������. ������ � ��������� �� ����, � ���������.";
			link.l1 = "�� ��� ��, ����� ���� ����������. ������� � ����� ��������.";
			link.l1.go = "exit";
			//AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			
			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //����������� ������ ���� ������ ��� ��������
		break;

		//------------------------------> ���� �� ���� �������� �����
		//��������. � �������� ������ ��������� ������� ������ �� �������   PortmansBook_Delivery  #TEXT   5
		//� ������ �������� ������� �����, ��������� � ����� ������ �� quest_text.txt
		//������: � ����� ������  void SetCapitainFromCityToSea(string qName)
		case "BuyLicense":
				dialog.text = "���� � ���� ���� ��������, ���� �������� ���-��� �������. �� ����, ����� �� ����-���� ����� ������������, �� � ������ ��� ���������� �� ���� �������. �� ������������ �����, �������. " + license_price + ". ������?";
				if(makeint(Pchar.money) >= license_price)
				{
					link.l1 = "����.";
					link.l1.go = "LicenseBought";
				}
				link.l2 = "���. �������.";
				link.l2.go = "exit";
		break;
		case "LicenseBought":
				AddMoneyToCharacter(Pchar, -license_price);
				GiveNationLicence(sti(NPChar.nation), license_expires);
				
				dialog.text = "�������.";
				link.l1 = "�� ��������.";
				link.l1.go = "exit";
				license_expires = rand(2);
		break;
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "���� ������������ ��������. ��� ��������� ��� ����������?";
				makearef(arCapBase, npchar.quest.capitainsList);
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
					arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", ������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "� ���� � ������� ��� ���������, ��������� ��� ��������������.";
				link.l1 = "�������. ������� �� ����������.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("��-�-��, ������� ���������... ���, ����! ", "���-���... ���, �����! ", "������, ���. ") +
				"������� " + GetFullName(sld) + " " + arCapLocal.date + " ���� ���� �� ������ ����� � " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "�������. �������� �� ���������� ������ ������...";
			link.l1.go = "CapitainList";
			link.l2 = "���, �������� ���� ����� �� ����������.";
			link.l2.go = "node_2";
			//������� ������ � ��
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//������� �� ������
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("��-�-��, ������� ���������... ���, ����! ", "���-���... ���, �����! ", "������, ���. ") +
				"������� " + GetFullName(sld) + " " + arCapLocal.date + " ���� ���� �� ������ ����� � " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "�������. �������� �� ���������� ������ ������...";
			link.l1.go = "CapitainList";
			link.l2 = "���, �������� ���� ����� �� ����������.";
			link.l2.go = "node_2";
			//������� ������ � ��
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//������� �� ������
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("��-�-��, ������� ���������... ���, ����! ", "���-���... ���, �����! ", "������, ���. ") +
				"������� " + GetFullName(sld) + " " + arCapLocal.date + " ���� ���� �� ������ ����� � " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "�������. �������� �� ���������� ������ ������...";
			link.l1.go = "CapitainList";
			link.l2 = "���, �������� ���� ����� �� ����������.";
			link.l2.go = "node_2";
			//������� ������ � ��
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//������� �� ������
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("��-�-��, ������� ���������... ���, ����! ", "���-���... ���, �����! ", "������, ���. ") +
				"������� " + GetFullName(sld) + " " + arCapLocal.date + " ���� ���� �� ������ ����� � " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "�������. �������� �� ���������� ������ ������...";
			link.l1.go = "CapitainList";
			link.l2 = "���, �������� ���� ����� �� ����������.";
			link.l2.go = "node_2";
			//������� ������ � ��
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//������� �� ������
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("��-�-��, ������� ���������... ���, ����! ", "���-���... ���, �����! ", "������, ���. ") +
				"������� " + GetFullName(sld) + " " + arCapLocal.date + " ���� ���� �� ������ ����� � " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "�������. �������� �� ���������� ������ ������...";
			link.l1.go = "CapitainList";
			link.l2 = "���, �������� ���� ����� �� ����������.";
			link.l2.go = "node_2";
			//������� ������ � ��
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", ��� ��������� �� " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//������� �� ������
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		//<--------------------------- ���� �� ���� �������� �����

		case "ShipStock_1":
				ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "����� ������ ������� �� ������ ��������?";
					for(i=1; i<COMPANION_MAX; i++)//������ ������ ���� ������������ ������� �����?
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;
							if(RealShips[sti(chref.Ship.Type)].BaseName == SHIP_SOLEYRU) continue; //�������� �������� �� ��������� �����
	
							attrL = "l"+i;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'. � ��� ��������� ������� " + GetFullName(chref) + ".";
							Link.(attrL).go = "ShipStockMan11_" + i;
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' ��� ����� �������.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
					Link.l17 = "�������, �� �����.";
					Link.l17.go = "exit";
				}
				else
				{
					dialog.text = "��. � �� ���� ����� �������� � �����.";
					Link.l1 = "��, � ������ �����"+ GetSexPhrase("","�") +" ������ � ����������� �������.";
					Link.l1.go = "exit";
				}
		break;

		case "ShipStock_Choose":
			dialog.text = "���������, ��� ��� �� �������.";
			Link.l1 = "������.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (pchar.location != "Caiman_PortOffice")  NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			else NPChar.MoneyForShip = 0;
			if (pchar.location != "Caiman_PortOffice") 
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', ����� " + RealShips[sti(chref.Ship.Type)].Class +
					 ", ��������� ������� " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " � �����, ������ �� ����� ������.";
			}
			else
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', ����� " + RealShips[sti(chref.Ship.Type)].Class +
					 ", ��������� ������� - ��� ��� ��������� ���������.";
			}
			Link.l1 = "��. ��� ���� ����������.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
				Link.l1.go = "ShipStock_3";
			}
			else
			{
				Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "���� ���� ��� �������, ���� � ��� ����� ������ �����.";
			Link.l1 = "���... ����� �����.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix �� ����������� � ��� 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // ��� ������
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // ��� �������
			//chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan", "PKM_rab_"+(rand(3)+1), "man", "man", rand(5)+1, NPChar.nation, -1, false));
			chref.id = chref.id + "_" + chref.index; //������ ID �� ������������
			chref.reputation = (1 + rand(44) + rand(44));
			chref.lastname = chref.name;//"������ ����" ����� ��� "������ ������"?
			chref.name = "������";
			DeleteAttribute(chref,"ship");
			chref.ship = "";

			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // ��� ������
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // ��� �������

			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//���������, � �������� ���� ������� �������

			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;//����������� - ��� ���. �� ���� �����, ��� ��� ������������.

			dialog.text = "������. ��������, ����� ����� �����.";
			Link.l1 = "�������.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "����� ������ ������� �� ��������?";
					cn = 1;
					for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i;
								}
								else
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' � ������ " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
					Link.l9 = "���, � ���������"+ GetSexPhrase("","�") +".";
					Link.l9.go = "exit";
				}
				else
				{
					dialog.text = "��� �� � ��� ����� ��� ��� ������ �������?";
					Link.l1 = "��, �����. �������.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "��. � �� ���� ������ �������� � �����. � ������� ���� ������� �� ������ ������ �����.";
				Link.l1 = "������, � ������� �� ���� �������.";
				Link.l1.go = "exit";
			}
		break;
	  	case "ShipStockManBack":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);

			//if (sti(NPChar.StoreWithOff)) string sTextAdd = ""; else string sTextAdd = "� ��� �� ����� �������� ������ ���?"; 

			if (sti(NPChar.MoneyForShip) > 0)
			{
				dialog.Text = "���������? � ��� �� �������� ��� " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "���������?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "��.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2":
			if (sti(NPChar.StoreWithOff))
			{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{
			dialog.Text = "���� �� ����� �������� �������� ���?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
						if (sld.id != "pet_crab" && sld.id != "Albreht_Zalpfer")
						{
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]);
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "�����" + GetSexPhrase("","�") + " �������� ��� ����� ������� � ����� ��������.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "���, � ���������"+ GetSexPhrase("","�") +".";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//���, ����
		case "Houm_portman_1":
			if (pchar.questTemp.Headhunter.City == npchar.city)
			{
				dialog.text = "��, ��������������. �� ������ ����� ������������� ��� �������� � ������.";
				link.l1 = "�������! �� ��� ����� �������.";
				link.l1.go = "Houm_portman_yes";
			}
			else
			{
				dialog.text = "���, ������� ����� � �����.";
				link.l1 = "��... �����, ����� ������ ������.";
				link.l1.go = "exit";
			}
		break;
		
		case "Houm_portman_yes":
			pchar.questTemp.Headhunter = "houm_tavern";
			CreateHoum();
			AddQuestRecord("Headhunt", "5");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			DialogExit();
		break;
		//���, ����
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.33 + frandSmall(0.27)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}


// Warship 25.07.09 ����� "��������� �����". ��������� ����� ��� �������� - ��� �������������� �����, ���������� �������������� � �.�.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO ������������ ����������� �� �����
	if(rank <= 45)
	{
		shipType = SHIP_LUGGER + rand(128);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
//				neededValue = 16.74 + fRandSmall(0.15);
				else
				{
					if(temp == 1)
					{
//						neededValue = 42.12 + fRandSmall(0.4);
						shipAttribute = "turnrate";
					}
				else
					{
//						neededValue = 864 + rand(8);
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_LUGGER_H:
			temp = rand(3);
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else	
				{	
					if(temp == 1)	
				{	
							shipAttribute = "turnrate";	
				}	
				else	
				{	
							 shipAttribute = "capacity";	
				}	
				}	
			break;	
			
			case SHIP_SLOOP:
				temp = rand(3);
				
				if(temp == 2)
				{
//					neededValue = 14.9 + fRandSmall(0.14);
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
//						neededValue = 42.12 + fRandSmall(0.4);
						shipAttribute = "turnrate";
					}
					else
					{
//						neededValue = 864 + rand(8);
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_BERMSLOOP:
				temp = rand(3);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_EMPRESS:
				temp = rand(3);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						//neededValue = 864 + rand(8);
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_PINK:
				temp = rand(3);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_SPEEDY:
				temp = rand(3);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
				
			case SHIP_FR_SLOOP:
				temp = rand(3);
					
				if(temp == 2)	
				{	
					shipAttribute = "speedrate";	
				}	
				else	
				{	
					if(temp == 1)	
					{	
						shipAttribute = "turnrate";	
					}	
					else	
					{	
						shipAttribute = "capacity";	
					}	
				}	
			break;	
			
			case SHIP_Galeoth_h:
				temp = rand(3);
					
				if(temp == 2)	
				{	
					shipAttribute = "speedrate";	
				}	
				else	
				{	
					if(temp == 1)	
					{	
						shipAttribute = "turnrate";	
					}	
					else	
					{	
						shipAttribute = "capacity";	
					}	
				}	
			break;	
			
			case SHIP_SLOOP_B:
				temp = rand(3);
					
				if(temp == 2)	
				{	
					shipAttribute = "speedrate";	
				}	
				else	
				{	
					if(temp == 1)	
					{	
						shipAttribute = "turnrate";	
					}	
					else	
					{	
						shipAttribute = "capacity";	
					}	
				}	
			break;	
			
			case SHIP_NEPTUNUS:
				temp = rand(3);
					
				if(temp == 2)	
				{	
					shipAttribute = "speedrate";	
				}	
				else	
				{	
					if(temp == 1)	
					{	
						shipAttribute = "turnrate";	
					}	
					else	
					{	
						shipAttribute = "capacity";	
					}	
				}	
			break;	
			
			case SHIP_SOPHIE:
				temp = rand(3); 
					
				if(temp == 2)	
				{	
					shipAttribute = "speedrate";	
				}	
				else	
				{	
					if(temp == 1)	
					{	
						shipAttribute = "turnrate";	
					}	
					else	
					{	
						shipAttribute = "capacity";	
					}	
				}	
			break;
			
			case SHIP_SCHOONER:
				if(rand(3) == 0)
				{
					neededValue = 14.04 + fRandSmall(0.13);
					shipAttribute = "speedrate";
				}
				else
				{
					neededValue = 37.8 + fRandSmall(0.35);
					shipAttribute = "turnrate";
				}
				else				
				{				
					neededValue = 1836 + rand(170);
					shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_POLACCA:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";			
				}			
				else			
				{				
					shipAttribute = "turnrate";			
				}			
				else							
				{									
					shipAttribute = "capacity";			
				}							
			break;	
			
			case SHIP_FR_POSTILLIONEN:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";		
				}			
				else			
				{				
					shipAttribute = "turnrate";			
				}			
				else							
				{									
					shipAttribute = "capacity";			
				}							
			break;	
			
			case SHIP_COLONIALSCHOONER:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;	
			
			case SHIP_XEBEC:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;
			
			case SHIP_BATTLEXEBEC:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;			
			
			case SHIP_XEBECLIGHT:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;			
			
			case SHIP_SCHOONERLIGHT:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;
			
			case SHIP_MIRAGE:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";	
				}			
				else			
				{				
					shipAttribute = "turnrate";		
				}			
				else							
				{									
					shipAttribute = "capacity";		
				}							
			break;	
			
			case SHIP_POLACRE:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";
				}			
				else			
				{				
					shipAttribute = "turnrate";	
				}			
				else							
				{								
					shipAttribute = "capacity";	
				}							
			break;
			
			case SHIP_ENSLAVER:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";
				}			
				else			
				{				
					shipAttribute = "turnrate";	
				}			
				else							
				{								
					shipAttribute = "capacity";	
				}							
			break;
			
			case SHIP_SHNYAVA:			
				if(rand(3) == 0)			
				{				
					shipAttribute = "speedrate";
				}			
				else			
				{				
					shipAttribute = "turnrate";	
				}			
				else							
				{								
					shipAttribute = "capacity";	
				}							
			break;
			
			case SHIP_BARQUE:
				neededValue = 1836 + rand(170);
				shipAttribute = "capacity";
			break;
			
			case SHIP_CARAVEL:
				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
			break;
			
  
 
							
  
									   
  
				  
   
			case SHIP_BARKENTINE:
				neededValue = 43.2 + fRandSmall(0.4);
				shipAttribute = "turnrate";
			break;
			
			case SHIP_BRIGANTINE:
				if(rand(3) == 1)
				{
					neededValue = 16.74 + fRandSmall(0.16);
					shipAttribute = "speedrate";
				}
				else
				{
					neededValue = 54.0 + fRandSmall(0.5);
					shipAttribute = "turnrate";
				}
				else
				{
				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_CASTELF:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_DERFFLINGER:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_INTERCEPTOR:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_PO_FLEUT50:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}				
			break;
			
			case SHIP_FLEUT:
				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
			break;
			
			case SHIP_BRIG:
				if(rand(3) == 1)
				{
					neededValue = 15.66 + fRandSmall(0.15);
					shipAttribute = "speedrate";
				}
				else
				{
					neededValue = 48.6 + fRandSmall(0.45);
					shipAttribute = "turnrate";
				}
				else
				{
				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_BRIGHEAVY:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_GREYHOUND:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_CORVETTELIGHT:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_PACKET_BRIG:
				if(rand(3) == 1)
				{	
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_PDN:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_ENTERPRISE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_POLACRE_H:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FRIGATEMEDIUM:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
											
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_RaaFrigate:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_CARAVEL2:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FLEUTWAR:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FLEUTWARSAT:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_GALEONTRADER:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_LYDIA:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
				shipAttribute = "capacity";
				}
			break;
			
			case SHIP_GALEON_L:
				neededValue = 3672 + rand(34);
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(3) == 1)
				{
					neededValue = 17.5 + fRandSmall(0.16);
					shipAttribute = "speedrate";
				}
				else
				{
					neededValue = 59.4 + fRandSmall(0.55);
					shipAttribute = "turnrate";
				}
				else
				{
					neededValue = 4320 + rand(40);
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_CRIMSONBLOOD:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FRIGATE_l:
 
							
  
									 
  
				  
   
					  
				if(rand(3) == 1)
				{
											 
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_BATTLECORVETTE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_BLACKANGEL:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_COASTALFRIGATE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FR_FRIGATE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_UNICORN:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_LINEFRIGATE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_LIGHTFRIGATE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_BOUSSOLE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_SURPRISE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_SALAMANDER:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_FRIGATE_SAT:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_BATTLEFRIGATE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_NIGHTMARE:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_MORDAUNT:
				if(rand(3) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_GALEON_H:
				neededValue = 5022 + rand(47);
				shipAttribute = "capacity";
			break;
			
			case SHIP_PINNACE:
				if(rand(3) == 1)
				{
					neededValue = 14.04 + fRandSmall(0.13);
					shipAttribute = "speedrate";
				}
				else
				{
					neededValue = 59.4 + fRandSmall(0.55);
					shipAttribute = "turnrate";
				}
				else
				{
					neededValue = 4320 + rand(40);
					shipAttribute = "capacity";
				}
			break;
			
			case SHIP_DUTCHPINNACE:			
				if(rand(3) == 1)			
				{			
					shipAttribute = "speedrate";			
				}			
				else			
				{			
					shipAttribute = "turnrate";			
				}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;			
			
			case SHIP_PINNACELIGHT:			
				if(rand(3) == 1)			
				{			
					shipAttribute = "speedrate";			
				}			
				else			
				{			
					shipAttribute = "turnrate";			
				}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;		
			
			case SHIP_XEBEKVT:			
				if(rand(3) == 1)			
				{			
					shipAttribute = "speedrate";			
				}			
				else			
				{			
					shipAttribute = "turnrate";			
				}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;	
			
			case SHIP_FELIPE:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;			
			
			case SHIP_JAMAICASHIP:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;		
			
			case SHIP_THEBLACKPEARL:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;
			
			case SHIP_GALEON1:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;	
			
			case SHIP_LA_MARIANNA:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;	
			
			case SHIP_PIRATFASTGAL:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;	
			
			case SHIP_REVENGE:			
				if(rand(3) == 1)			
			 	{			
			 		shipAttribute = "speedrate";		
			 	}			
				  else			
			 	{			
			 		shipAttribute = "turnrate";			
			 	}			
				else			
				{			
					shipAttribute = "capacity";			
				}			
			break;		
			
			case SHIP_FRIGATE:
				temp = rand(3);
				
				if(temp == 0)
				{
					neededValue = 15.44 + fRandSmall(0.14);
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						neededValue = 41.04 + fRandSmall(0.38);
						shipAttribute = "turnrate";
					}
					else
					{
						neededValue = 3240 + rand(30);
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_AMSTERDAM:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_CARRACA:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;		
			
			case SHIP_GALEON50:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FASTFRIGATE:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FR_ESSEX:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FRIGATE_H:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_WARGALLEON2:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_NL_PINNACEOFWAR47:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_HOLLGALEON_H:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FEARLESS:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_NL_FWZP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_CONSTITUTION:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_OXFORD:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_DUTCHLINESHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_DUTCHSHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_NL_CONVOISHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_COURONNE:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_ALEXIS:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINESHIPHEAVY:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_WARSHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HEAVYWARSHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_POSEIDON:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HMS_CENTURION:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_RESOLUTION:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_FR_SUPERIORWARSHIP1:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINK:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SUPERBE:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BATTLESHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINK2:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BELLONA:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINEARSHIP:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SHARK:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_ZEVENPROVINCIEN:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_FR_TRINITY:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR_FAST:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BATTLEMANOWAR:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR_GUB:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_PRINCE:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HMS_VICTORY:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SP_SANFELIPE:
				temp = rand(3);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
		}
	}
	
	
	
	if(rank > 45)
	{
		shipType = SHIP_FRIGATE + rand(1);
		
		switch(shipType)
		{
			case SHIP_FRIGATE:
				temp = rand(2);
				
				if(temp == 0)
				{
//					neededValue = 15.44 + fRandSmall(0.14);
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
//						neededValue = 41.04 + fRandSmall(0.38);
						shipAttribute = "turnrate";
					}
					else
					{
//						neededValue = 3240 + rand(30);
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_AMSTERDAM:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_CARRACA:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;		
			
			case SHIP_GALEON50:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FASTFRIGATE:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FR_ESSEX:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FRIGATE_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_WARGALLEON2:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_NL_PINNACEOFWAR47:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_HOLLGALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_FEARLESS:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;			
			
			case SHIP_NL_FWZP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_CONSTITUTION:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_OXFORD:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_DUTCHLINESHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_DUTCHSHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_NL_CONVOISHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_COURONNE:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_ALEXIS:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINESHIPHEAVY:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_WARSHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HEAVYWARSHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_POSEIDON:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HMS_CENTURION:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_RESOLUTION:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_FR_SUPERIORWARSHIP1:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINK:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SUPERBE:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BATTLESHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINK2:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BELLONA:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_LINEARSHIP:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SHARK:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_ZEVENPROVINCIEN:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_FR_TRINITY:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR_FAST:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_BATTLEMANOWAR:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR_GUB:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_PRINCE:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_MANOWAR:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_HMS_VICTORY:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			case SHIP_SP_SANFELIPE:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;	
			
			// ��� ������
			case SHIP_LINESHIP:
//				neededValue = 38.88 + fRandSmall(0.36);
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // ����� ���� � ����������� �� �������
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}


void SetJornalCapParam(ref npchar)
{
	//������� ����������� ����
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true));
	SetCaptanModelByEncType(sld, "trade");
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//� ������� ������ ����
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//���������� ������ � ��������� �������� � ����
	npchar.quest = "PortmansJornal"; //������ ���� ������ ��� ��������
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //��� ����
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //��� �������
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //�������� �������
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //��������� �������, ���� ���� ���
	sld.quest = "InMap"; //������ ���� ����������� ����
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //������������ �������-���� � ��������� ����
	sld.quest.firstCity = npchar.city; //�������� ����� ������ ����� � ����� ������
	sld.quest.stepsQty = 1; //���������� ������� � ����
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //��������������
	Log_TestInfo("���������� ��� " + sld.id + " ���������� �: " + sld.quest.targetCity);
	//��������� �����, ���� ������� ���������. ����� ����� �� ��������� ����� �� � ������
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//�� �����
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//��������� ������ ������������ ��������� �����
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
	makearef(arCapBase, npchar.quest.capitainsList);
	int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId;
	for (int i=0; i<Qty; i++)
	{
		arCapLocal = GetAttributeN(arCapBase, i);
		sCapitainId = GetAttributeName(arCapLocal);
		if (GetCharacterIndex(sCapitainId) > 0) //���� ��� ���
		{
			bResult++;
		}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
	}
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//������� ����-����
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true));
	SetCaptanModelByEncType(sld, "pirate");
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//� ������� ������ ����
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//���������� ������ � ��������� �������� � ����
	npchar.quest = "PortmansSeekShip"; //������ ���� ������ ��� ��������
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //��� ����-����
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //��� ����������� �������
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //�������� ����������� �������
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //��� ����������� �������
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //��������������
	npchar.quest.chest = 7-sti(RealShips[sti(sld.Ship.Type)].Class); //� ��������
	sld.quest = "InMap"; //������ ���� ����-����
	sld.city = SelectAnyColony(npchar.city); //��������� �������, ������ ���-��� ������
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //��������� �������, ���� �� ������
	Log_TestInfo("���-��� " + sld.id + " ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //�����, ������ ���-��� ���� �������
	//�� �����
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //���� ������� ���� � �������
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//���������� �� �������
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//���������� �� ���������� ��� ��������
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // �����
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry17"; 
		break;
	}
	return itemID;
}

string findTraderCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //�� ���� ������
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

void DelBakSkill(ref _compref)
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}