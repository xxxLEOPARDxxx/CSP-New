void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// ��������� ����� � 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- ��������� ����� � 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//������ ����� �������� ��� ���������� ���� (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DeleteAttribute(npchar,"pricevalue");
			DeleteAttribute(npchar,"pricev");
			DeleteAttribute(npchar,"itemtype");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToSmuggler(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;
		
		case "Smuggling_exit":
			PChar.CurrentSmuggler = npchar.id;
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":			
		UpdateSmugglers();
		//���
			if (CheckAttribute(pchar,"contrabandmoneyback") && sti(pchar.contrabandmoneyback) >= 3000000+(MOD_SKILL_ENEMY_RATE*100000) && !CheckCharacterPerk(pchar,"UnlimitedContra"))
			{
				dialog.text = "�������, �� �������� ���� �� ���������� �������� �������� ��� ����� �������������� �������. ������ � ������ ��� ����� ��������������� ��������� ������� ������.";
				link.l1 = "��������� ��� �� �������.";
				link.l1.go = "First time";
				Log_info("������������� ���� ''������� �������������''");
				SetCharacterPerk(pchar, "UnlimitedContra");
				NPChar.quest.meeting = "1"; 
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				dialog.text = "�������, � �� ����� ���������� � ���� �� ����� ����. ��, ��� � ����, ������� �� ���������� �����, � ���� �� �������� � ��������� ��������... ��������, �� ������ �"+ GetSexPhrase("��","�") +", ��� ���"+ GetSexPhrase("��","��") +".";
				link.l1 = "��... ���������. ���������, ��� � ��� �� ����.";
				link.l1.go = "Give_vector";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "��� ��� ����, �������? � �� ���� ������ �����, � �� ���� ������� ��� ����.";
				Link.l1 = "� ������� " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
				if (CheckAttribute(pchar,"RimalieGood") && npchar.id == "PortSpein_Smuggler" && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l18 = "� �� �����"+ GetSexPhrase("","�") +" ���������� �� ������ ��������, �������� ����������� �� ���� �������.";
					Link.l18.go = "Rimalie";
				}
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "������� ������� ������ �� �����. �� ���� ������ ����� �������, ���������� ���� ����, ������� ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ����� ����������� � ������-�� ������ � �������.";
						link.l1 = "� ��� ��� ������� " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "������� ������� ������ �� �����.";
						link.l1 = "�������.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "������� ������� ������ �� �����.";
					link.l1 = "�������.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "��� �� �������� �� ���� ���, �������?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("������ �������, "+ GetSexPhrase("��������","�������") +", ��� ���� ����? � ��, ������ ��, ������ �� �����!", "�� �����, ������� ������� ���� ����! �� ����� �������� ������, �� �� ������ �����, ������ ��...");
				}
				if(FindFirstContrabandGoods(PChar) != -1)
				{
					Link.l1 = "� ������"+ GetSexPhrase("","��") +" ������� ������� �� �������.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "������ �������...";
				else
					Link.l2 = "��� ����� ��������� ���-����.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "� ���� ���� '���������' �����, ����� ���� ����� ���������. �������!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				
				// ��������� ��������� �2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "��� ����� ���-��� ��������, ��������.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "���� ������� � ��� ������ �������� �� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " ������, ��� �� � ����� ������ ����.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- ��������� ��������� �2
				
		    	////////////////////////////////////////////////////////	
		    	//zagolski. ��������� ����� ������
		    	if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
		    	{
			    	link.l4 = "������, ��� ������� ����� ����� ������ �����. ��� � �� ����, � ���� ����������.";
			    	link.l4.go = "pirateStartQuest_Smuggler";
			    }
				
				if (CheckAttribute(pchar,"contratrade.time"))
				{
					if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
					{
						Link.l17 = "(��������) � ������"+ GetSexPhrase("","�") +", ��� � ��� ����� ������ ���-�� ����������.";
						Link.l17.go = "Trade";
					}
				}
				if (!CheckAttribute(pchar,"contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(��������) � ������"+ GetSexPhrase("","�") +", ��� � ��� ����� ������ ���-�� ����������.";
					Link.l17.go = "Trade";
				}
				if (CheckAttribute(pchar,"RimalieGood") && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l18 = "� �� �����"+ GetSexPhrase("","�") +" ���������� �� ������ ��������, �������� ����������� �� ���� �������.";
					Link.l18.go = "Rimalie";
				}
				
				Link.l7 = "������. �� �������.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "Rimalie":
			if (!CheckAttribute(pchar,"RimalieWait"))
			{
				Dialog.Text = "��� ��, ������ � ��. ������ �� ���� ������ ��������� ��-�� ����. �� ������ ���� ������ � ������� ����� �������, ���� ��� ������� �������.";
				Link.l1 = "����� � �� ���"+ GetSexPhrase("","��") +" ���������� ������ ��-�� ��� ��������?";
				Link.l1.go = "Rimalie_2";
			}
			else
			{
				Dialog.Text = "����� � ��...? 50000 �������� ����� ������. ���� �������� - �� �������� �� ����.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "�������.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "� ��� ������� �� ����� ������.";
				Link.l2.go = "exit";
			}
		break;
		
		case "Rimalie_2":
			if (ChangeContrabandRelation(pchar, 0) >= 70)
			{
				Dialog.Text = "�� �������� ��������� ������ ��� ����� ����������� � �����"+ GetSexPhrase("","��") +" ������ �������. ���� ���� �� ������ ����� �� ������� � ���������� ��� ������������ ���� ����� ������. ������� �� ��������� ���� �����? � ������� ����� �������� ��������� ����� � ����������������� � �����. �� �������?";
				Link.l1 = "���� �������� �������-�������� �� ���� � ��������. ��������� ��� �� ������!";
				Link.l1.go = "exit";
				pchar.RimalieDone = true;
				DeleteAttribute(pchar,"RimalieGood");
				DeleteAttribute(pchar,"RimalieWait");
			}
			else 
			{
				pchar.RimalieWait = true;
				Dialog.Text = "�� ���������� ������� �� �����... 50000 �������� ����� ������. ���� �������� - �� �������� �� ����.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "�������.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "� ��� ������� �� ����� ������.";
				Link.l2.go = "exit";
			}
		break;
		
		
		case "Rimalie_3":
			AddMoneyToCharacter(pchar,-50000);
			Dialog.Text = "� ����� ������� ����� ����. �� ������� �� ��������� ���� �����? � ������� ����� �������� ��������� ����� � ����������������� � �����. �� �������?";
			Link.l1 = "���� �������� �������-�������� �� ���� � ��������. �� �������!.";
			Link.l1.go = "exit";
			pchar.RimalieDone = true;
			DeleteAttribute(pchar,"RimalieGood");
			DeleteAttribute(pchar,"RimalieWait");
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "� ������� �����, ��� �� ��� ��� ����?.. ������� � ����� ������ ����� ������ ������� �����, ��� ������� ����, � ����� �� ��������� � �����. ��� ���, ���� �� �������� ��� ��� �����, ���� �� ������� � �������.";
				link.l1 = "��������, �� �� ������ ������ �� ������� ������. ������� ��� �� �������� ������ �������� " + pchar.GenQuest.CaptainComission.Name + "?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "�� �������, ��������. ������� ��� ������� ������ � ��������. � � ���������-�� �� �������, ��� ����� ���� ���������.";
				link.l1 = "� ������ �� ������, ��� ����� ������������ �������?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "�� ��������� ��� ��� �� ����� ���� �� ��������. � ����� ��������� ���� �����, ��� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name"))) + " ��� ׸���� ��������. � �����, ������ ����� ����, �� ������� � ������� ������ �������, ����� �����-������ �������. �� ��� ����� ������ ����� ���� ������� ����� �� �����.";
			link.l1 = "� ����� ��� �� ��������, ��� ������ �������� " + pchar.GenQuest.CaptainComission.Name +"? �� �� ������ ������ �� ������� ������.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "���. �� ��� ���� ����, �� �� ��� ����, ����� ���������� �����������...";
			link.l1 = "�������... ��, ��������� ����������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
		break;
		
		case "CapComission_4":
			dialog.text = "���. �� ��� ���� ����, �� �� ��� ����, ����� ���������� �����������, ��-��...";
			link.l1 = "�������... ��, ��������� ����������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "������ �� ��� �����"+ GetSexPhrase("","�") +"? � ������� ����������. ��� ������� ����������.";
				link.l1 = "������� � �� ����....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "��� �������? ����� ����, � ���������� ���� '�����'. ���� " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " �������, � ������ �� ����.";
					link.l1 = "�������, ���.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "��, �� ������, ��� ������� ��������!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "�����! ��� ��� �� ������ ���������. �����, ���� ������� ���� "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +" �������, �� � ���� ������ ������ �� ���������, ��� �� ��� � ���� �������.";
						link.l1 = "�������, ���.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "��, �� ������, ��� ������� ��������!";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "��� ��� ���� ��������� �������! ��� �����, ����� ���������. ����� ���: � ����� ���� " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " �������, � �� ������� ���, ��� �����"+ GetSexPhrase("","�") +" ��������� �� �����?";
						link.l1 = "�������, ���.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "��, �� ������, ��� ������� ��������!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "��-��, ������ �� ������ ������.";
			link.l1 = "� �� ������������ �� �������!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterReputation(pchar, -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "������� ������� ������ �� �����. �� ���� ������ ����� �������, ���������� ���� ����, ������� ������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " ����� ����������� � ������-�� ������ � �������.";
					link.l1 = "� ��� ��� ������� " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "������� ������� ������ �� �����.";
					link.l1 = "�������.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "������� ������� ������ �� �����.";
				link.l1 = "�������.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "��� ���� ���� ������� ���, �������?";
			if(FindFirstContrabandGoods(PChar) != -1)
			{
				Link.l1 = "� ���� ���-��� �������.";
				Link.l1.go = "Meeting_1";
			}
			Link.l2 = "��� ����� ��������� ���-����.";
			Link.l2.go = "Travel";				
			// ��������� ��������� �2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "��� ����� ���-��� ��������, ��������.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "���� ������� � ��� ������ �������� �� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " ������, ��� �� � ����� ������ ����.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- ��������� ��������� �2

			////////////////////////////////////////////////////////	
			//zagolski. ��������� ����� ������
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				link.l4 = "������, ��� ������� ����� ����� ������ �����. ��� � �� ����, � ���� ����������.";
				link.l4.go = "pirateStartQuest_Smuggler";
			}

            if (CheckAttribute(pchar,"contratrade.time"))
			{
				if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(��������) � ������"+ GetSexPhrase("","�") +", ��� � ��� ����� ������ ���-�� ����������.";
					Link.l17.go = "Trade";
				}
			}
			if (!CheckAttribute(pchar,"contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
			{
				Link.l17 = "(��������) � ������"+ GetSexPhrase("","�") +", ��� � ��� ����� ������ ���-�� ����������.";
				Link.l17.go = "Trade";
			}

			Link.l5 = "�����. �����!";
			Link.l5.go = "Exit";				
		break;

		////////////////////////////////////////////////////////	
		//zagolski. ��������� ����� ������
		case "pirateStartQuest_Smuggler":
		if (!CheckAttribute(pchar, "GenQuest.contraTravel.active") && !CheckAttribute(Pchar, "quest.Contraband.Active"))
		{
			dialog.text = "���-�� ����� ����� ����� �� �����. �� ������ ������ ������ � ������� � �������� ��������� ����������.";
			link.l1 = "���� ��� �����, � � ���� ���� �����. ������� ������ �� ��������.";
			link.l1.go = "pirateStartQuest_Smuggler_1";
		}
		else
		{
			dialog.text = "�������, ��������, ������� �������. � ����� ��� �� ���� ���������.";
			link.l1 = "�����.";
			link.l1.go = "exit";
		}
		break;
		case "pirateStartQuest_Smuggler_1":
			dialog.text = "���� �� ���� ������, ���� � �� ���� ��� ���� ��������! ��, ���� �������� ������� ���� ������ � �������� ��������, ���� ����� ������ ���� �� ���.";
			link.l1 = "� �� ����, � ��� �� ��������. ��� ���������� ����� �� ������ �������, ������� � ���������, ���� ����� ��������.";
			link.l1.go = "pirateStartQuest_Smuggler_2";
		break;
		case "pirateStartQuest_Smuggler_2":
			dialog.text = "� ������� ����� ���� �����?";
			link.l1 = "����� 100 �����. ������ �������!";
			link.l1.go = "pirateStartQuest_Smuggler_3";
		break;
		case "pirateStartQuest_Smuggler_3":
			dialog.text = "��� ��������� ���� � 30 000 ��������, �� 300 �� ����. ���� �������?";
			link.l1 = "�� �����.";
			link.l1.go = "pirateStartQuest_Smuggler_4";
		break;
		case "pirateStartQuest_Smuggler_4":
			pchar.questTemp.pirateStartQuest.Shore = SelectQuestShoreLocation();
			dialog.text = "�����. ������� � �������� � ����� ��� ��������� " + XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore) + ", ��� � ���������...";
			link.l1 = "������, ����. ������ �� ������� ������ ���� �� ��� - � ���� ������� ��� � ���� ������.";
			link.l1.go = "exit";

			pchar.questTemp.pirateStartQuest = "3";
			pchar.questTemp.pirateStartQuest.City2Nation = npchar.nation;
			AddQuestRecord("pSQ", "3");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
			AddQuestUserData("pSQ", "sShore", XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore));

			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1.location = pchar.questTemp.pirateStartQuest.City2 + "_ExitTown";
			pchar.quest.pirateStartQuest_Smuggler_fc.function = "pirateStartQuest_Smuggler_fc";

			AddGeometryToLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Shore;
			pchar.quest.pirateStartQuest_Smuggler_fc2.function = "pirateStartQuest_Smuggler_fc2";
		break;
		//--------------------------------------------------

		// ��������� ��������� �2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "� ���� �� ��������. � ���-��� �������� ����� ������ ���� ��������.";
				link.l1 = "��. ��� ����� ������ �����, ������� �� ����� " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "����� ���� ���� ������. � ����, �� ����� ����� ����� �� �������.";
				link.l1 = "��� ����� � �� ����. ���������, ��������"+ GetSexPhrase("��","���") +" � ��� � ��������. �������"+ GetSexPhrase("","�") +" �� �������, � ��� �� ����� �����...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "���, �� � ���� �� ���� �����! �������, ����� ������������...";
				link.l1 = "�����.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
			dialog.text = "� � ����� ������?";
				link.l1 = "� ������ �� ���, ������ ������� � ��� ���� �� ����. ��� � � �������"+ GetSexPhrase("","�") +", ����� ����, ��� �� ����� ������� �������� ������ �� ����� ������?..";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "��� ��� ���... ��, ���� ����. ������� ����, �������, ��� �� ������ ����� ����������, � ��� ���� ������� ����. �� � ����� ������� ������� �� ����������, ���� ��  ���� �������. � ��� ����� ���� � " + XI_ConvertString("Colony" + sColony + "Acc") + ", ��� ��������� �� " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + ", ���� ��� � �����������. ����� � ���� ����������, ���� � ���� �������.";
			link.l1 = "�������, � ��� ����� �������.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
			break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "� ����� � ���� �� ���� ������� ���.";
				link.l1 = "��, ��� ������ �������. �� ��� ����� �� �������� ���� ���� ������, � �������� � ��������"+ GetSexPhrase("��","���") +".";
				link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
			break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "��, �� �������� �� " + XI_ConvertString(sGenLocation + "Dat") + "... ������, ����� �� ��� � ������� ��������� ���� ��������, ����� �� � �� ��������� �� ����������.";
			link.l1 = "������� �� ������, �� � ��������"+ GetSexPhrase("","�") +" � ����� �������"+ GetSexPhrase("��","���") +".";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
			break;
		// <-- ��������� ��������� �2

		case "Meeting_1":
			Dialog.Text = "��... ������ ����� �? ��������, �� �� ���� �����, �������. ����� � ������� - ��� � �������� ����� ��, ��� �� ��������.";
			Link.l1 = "�����, ��� ��� ����� ������ ��.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "������� �� �����. ����� ��������.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "����� ��?";
			Link.l1 = "� ���� ������� ��, ��� �� ����� �� ���� �������� �� ���� �������.";
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			if (sti(npchar.SmugglingMoney) < 200000)
			{
				Dialog.Text = "� ��� �� ������ ���� ���������� ������. � ���� ���� ��� ����� �� ����� �����, ������� ����� �����-������.";
				Link.l1 = "� ���� ���� � ������� ������� �����, ������ ��... �� �����, �����.";
            	Link.l1.go = "exit";
				break;
			}
			
			if (CheckCharacterPerk(pchar, "UnlimitedContra")) 
			{
				if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None" && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "� ����, � ����� ����� ����� ����. �� ����� ����� ���� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "��... ��������, ���������� � ��������. �� ����� ����� ��� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "������. �� �������.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
							}
							else
							{
								Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
							}
            				Link.l1 = "������.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "� ����� ����� �� �������, ��� ���-�� ������� �������� � �����? �������, ��� �� ��� �� ������� ������� ����� �� ����� �������. ��������!";
        				Link.l1 = "��... ������ �� ������ ��� ����� ���������������.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
					{
						Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
					}
					else
					{
						Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
					}
    				Link.l1 = "������.";
    				Link.l1.go = "Exit";
				}
				break;
			}
			if (GetCompanionQuantity(pchar) > 1 && GetBaseHeroNation() != PIRATE)
			{
				dialog.text = NPCStringReactionRepeat("������� �������� �� ����� �������. ��� ������� ���������. �� �� ����� ��� ���������. ������� �� ����� �������, � ���� �� ��� �� ������ ����� ��� �������.", 
					"� ���, ��������� ���������? �������� - ������� �������!", 
					"�� ���, ���"+ GetSexPhrase("��","��") +"? ���-��, ������ ���� - ���-�� �������, �� ���, �� ���, � ����! ������ �����"+ GetSexPhrase("","�") +"?",
					"��, � ��� ����� ���"+ GetSexPhrase("����","") +" ����� �����...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("������, � ���� �����"+ GetSexPhrase("","�") +". ���� ��� ����.", 
					"��� �������, ������ �������� �����"+ GetSexPhrase("","�") +".",
					"���, �� ���"+ GetSexPhrase("��","��") +", ������ ����"+ GetSexPhrase("��","��") +" �����. �������"+ GetSexPhrase("","�") +", ����� ���������� ���, � ����� ������ ����� ��������...", 
					"�� �� �� ������ - ����� ���-��...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}

		//���������� �����, �� ��-������� �� ��������-����� ������� �� ��������� �������� �� �����������, � �� ���
			int iClass, ipClass;
			ipClass = 4-sti(RealShips[sti(pchar.ship.type)].Class);
			iClass = 3;//�.�. �� ������� �� ����� �������� � ����� ������
		if (GetBaseHeroNation() == PIRATE)
		{
			ipClass = sti(ipClass)-1;
			int iChIdx, i;
			// ����� �������� ������ ����������
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
					iClass = GetCharacterShipClass(sld);
				}
			}
		}
			if (sti(ipClass) > 0 || 3 - sti(iClass) > 0)
			{
				dialog.text = NPCStringReactionRepeat("�� �� ��� �� ����������� �������� ����"+ GetSexPhrase("��","���") +". �� ���� �������� �� ���� ������ �� �����. �� �� ����� ��������� ������ ��������. ������� �� ������� �������, � ������ �� �����.", 
					"� ���, ��������� ���������? ����� ���� ��������� ��������, ����� � �������.", 
					"�� ���, ������ ��� �������������? ������ �� ���� - ����� ���� �����, �� ���� �� ������� ������, ��� ������ �� ���������.",
					"��, � ��� ����� ���"+ GetSexPhrase("����","") +" ����� �����...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("������, � ���� �����"+ GetSexPhrase("","�") +". ����� �����, ��� �������� �����.", 
					"�� ��� �������, ������ �������� �����"+ GetSexPhrase("","�") +".",
					"���, �� ������, ������ ������. �������"+ GetSexPhrase("","�") +", ����� ���������� ���. � �� ��� ���� ������� � ����� ���������"+ GetSexPhrase("","�") +"...", 
					"�� �� �� ������ - ����� ���-��...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // ���������
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				if (makeint(environment.time) < 19.0)
				{
					Dialog.Text = "������, "+ GetSexPhrase("������","������") +", � ��� ��� ���� ����. ����� �������, ����� ��� ����� 7, ����� ��� �����������.";
					if (ChangeContrabandRelation(pchar, 0) > 5 && sti(pchar.money) >= 1000 && !bOk && !bOk2 && !bOk && npchar.quest.trade_date != lastspeak_date)
					{
						Link.l1 = "� ������ �� ������, �� �������� �������������� ���, ��� ������, � 1000 ��������?";
						Link.l1.go = "AntiPGGContra";
					}
					Link.l2 = "����...";
					Link.l2.go = "Exit";
					break;
				}
				else
				{
					if (bOk || bOk2 || bOk3)
					{
						Dialog.Text = "�����, ����� ��������� ���� ���� ������, ��� ������� �� ������?";
						Link.l1 = "�������, �� ����.";
						Link.l1.go = "Exit";				
					}
					else
					{
						if (npchar.quest.trade_date != lastspeak_date)
						{
							npchar.quest.trade_date = lastspeak_date;
							
							if (ChangeContrabandRelation(pchar, 0) > 5)
							{
								Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
								Pchar.quest.contraband.City = NPChar.city;
								if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
								{
									if (ChangeContrabandRelation(pchar, 0) >= 70)
									{
										Dialog.Text = "� ����, � ����� ����� ����� ����. �� ����� ����� ���� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									else
									{
										Dialog.Text = "��... ��������, ���������� � ��������. �� ����� ����� ��� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									Link.l1 = "������. �� �������.";
									Link.l1.go = "Smuggling_exit";
								}
								else
								{   //boal fix
									if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
									{
										Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
									}
									else
									{
										Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
									}
									Link.l1 = "������.";
									Link.l1.go = "Exit";
								}
							}
							else
							{
								Dialog.Text = "� ����� ����� �� �������, ��� ���-�� ������� �������� � �����? �������, ��� �� ��� �� ������� ������� ����� �� ����� �������. ��������!";
								Link.l1 = "��... ������ �� ������ ��� ����� ���������������.";
								Link.l1.go = "Exit";
							}
						}
						else
						{
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
							}
							else
							{
								Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
							}
							Link.l1 = "������.";
							Link.l1.go = "Exit";
						}
					}
				}
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "�����, ����� ��������� ���� ���� ������, ��� ������� �� ������?";
				Link.l1 = "�������, �� ����.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "� ����, � ����� ����� ����� ����. �� ����� ����� ���� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "��... ��������, ���������� � ��������. �� ����� ����� ��� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "������. �� �������.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
							}
							else
							{
								Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
							}
            				Link.l1 = "������.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "� ����� ����� �� �������, ��� ���-�� ������� �������� � �����? �������, ��� �� ��� �� ������� ������� ����� �� ����� �������. ��������!";
        				Link.l1 = "��... ������ �� ������ ��� ����� ���������������.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar,"Whisper.Contraband"))
					{
						Dialog.Text = "�������, � ���� ��� ��������� ���� ������, � ���-�� �� �������. �������, ����� �����������.";
					}
					else
					{
						Dialog.Text = "������� ������ ������ �� �����. ������� ������.";
					}
    				Link.l1 = "������.";
    				Link.l1.go = "Exit";
				}
			}
		break;
		
		case "AntiPGGContra":
			AddMoneyToCharacter(pchar,-1000);
			bool canDeal = GetCompanionQuantity(pchar) == 1 && sti(RealShips[sti(pchar.ship.type)].Class) > 2
			if (CheckCharacterPerk(pchar, "UnlimitedContra") || canDeal) 
			{
				npchar.quest.trade_date = lastspeak_date;
				Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
				Pchar.quest.contraband.City = NPChar.city;
				if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
				{
					if (ChangeContrabandRelation(pchar, 0) >= 70)
					{
						Dialog.Text = "� ����, � ����� ����� ����� ����. �� ����� ����� ���� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					else
					{
						Dialog.Text = "��... ��������, ���������� � ��������. �� ����� ����� ��� � �����, ������������ " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					Link.l1 = "������. �� �������.";
					Link.l1.go = "Smuggling_exit";
				}
			}
			else
			{
				Dialog.Text = "������, ��� � ��� ������ �� ������! �� �� ��� �� ����������� �������� ����"+ GetSexPhrase("��","���") +". ������� �� ��������� �������, � ������ �����, ����� � ���������. � ������ ���� � ������, � �������� ����� �� �����.";
				Link.l1 = RandSwear();
				Link.l1.go = "exit";
			}
		break;
		
		case "Trade"://�������� � �������� - Gregg
			int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
			Dialog.Text = "(��������) ���... ��, ��� ���. ";
			switch (makeint(drand(7)))
			{
				case 0:
					npchar.itemtype = "Lockpick";//������� �� ����� 
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type = npchar.pricev;
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� ������� �������. ����������? �� 3 ����� ����� ����� 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"��.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type)) >= 5)
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;
				case 1:
					npchar.itemtype = "Totem_"+(drand2(13)+1);//�����, �� ����-������
					npchar.pricevalue = 30000+drand1(20000);
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". ����������? �� ���� � ����� "+npchar.pricevalue+" ��������.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue)) 
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;
				/*case 2:
					npchar.itemtype = "sculMa"+(drand2(2)+1);//����������� �����
					npchar.pricevalue = 75000+drand1(25000);
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� ��������� ���������, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". ����������? �� ���� � ����� "+npchar.pricevalue+" ��������.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue)) 
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;*/
				case 2:
					npchar.itemtype = "indian"+(drand2(21)+1);//������, �� ��������
					if (npchar.itemtype == "indian11") npchar.itemtype = "indian"+(22-drand1(2));
					aref ind;
					Items_FindItem(npchar.itemtype, &ind);
					npchar.pricevalue = sti(ind.price)*10;
					if (CheckAttribute(ind,"groupID") && sti(ind.price) < 100) npchar.pricevalue = sti(npchar.pricevalue)*25;
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� ��������� ����������, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". ����������? �� �� � ����� "+npchar.pricevalue+" ��������.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue)) 
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;
				case 3:
					npchar.itemtype = "jewelry"+(drand2(3)+1);//����� �� �����
					npchar.pricev = "j";
					npchar.pricevalue = 20000+drand1(5000);
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� ����������� �����, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+"�. ����������? �� ��������� �� 25 ���� � ����� "+npchar.pricevalue+" ��������.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue)) 
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;
				case 4:
					npchar.itemtype = "Lockpick";//������� �� �����
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type1 = npchar.pricev;
					Dialog.Text = dialog.text+ "������� � ������� � ���� ���� ������� �������. ����������? �� 3 ����� ����� ����� 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"��.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type1)) >= 5)
					{
						Link.l1 = "��� ��, ������� ����������.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "���, ������ ��������� �����.";
					Link.l2.go = "Exit";
				break;
				else
					Dialog.Text = "���, ������� ������ ����������� � ���� � ������� ���.";
					Link.l2 = "��, ����� �������. ��, ����� �� �������.";
					Link.l2.go = "Exit";
				break;
			}
			/*Dialog.Text = "(��������) ���... ��, ��� ���. ������� ���-�� ������ ������?";
			Link.l1 = "��, �������� ���� ������.";
			Link.l1.go = "Trade_exit";
			Link.l2 = "���, ������ ��������� �����.";
			Link.l2.go = "Exit";*/
		break;
		
		case "Trade_2":
		{
			int idLngFile1 = LanguageOpenFile("ItemsDescribe.txt");
			if (CheckAttribute(npchar,"pricev"))
			{
				if (npchar.itemtype == "Lockpick")
				{
					Log_Info("�� ������ 5 "+LanguageConvertString(idLngFile1, "itmname_"+npchar.pricev)+"��.");
					Log_Info("�� �������� 3 �������.")
					TakeNItems(pchar, npchar.pricev, -5);
					TakeNItems(pchar, npchar.itemtype, 3);
				}
			}
			if (CheckAttribute(npchar,"pricevalue"))
			{
				if (npchar.itemtype != "Lockpick")
				{
					AddMoneyToCharacter(pchar, -sti(npchar.pricevalue));
					if (CheckAttribute(npchar,"pricev"))
					{					
						TakeNItems(pchar, npchar.itemtype, 25);
						Log_Info("�� �������� 25 "+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+"��.");
					}
					else
					{ 
						GiveItem2Character(pchar, npchar.itemtype);
						Log_Info("�� �������� "+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+".");
					}
				}
			}
			LanguageCloseFile(idLngFile1);
			DeleteAttribute(npchar,"pricevalue");
			DeleteAttribute(npchar,"pricev");
			DeleteAttribute(npchar,"itemtype");
			pchar.contratrade.time = GetDataDay();
			ChangeContrabandRelation(pchar, 5)
			Dialog.Text = "�����! � ����� ������� ����� ����. �������, ��� ����������.";
			Link.l2 = "���������. �� �������!";
			Link.l2.go = "Exit";
		}
		break;
		
////////////////////////////////////////////////////////////////////////////////
//	���������� �����
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
/* //navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "������, "+ GetSexPhrase("������","������") +", � ��� ��� ���� ����. ����� ����� ���� ����.";
				Link.l1 = "����...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <-- */
			//���� ��� ������� � �� � ��� ����������� ��� ��
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//������ ���� ��� ���� ����
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//������ ���
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "��, ������� ��� ������������?";
						Link.l2 = "��, �����!";
					}
					//�� ������, ������ ����� ���������� ���� �� ����� ����.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "������"+ GetSexPhrase("","��") +" ������?";
							Link.l1 = "��.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "� ���������"+ GetSexPhrase("","�") +"....";
							Link.l3.go = "Travel_abort";
							Link.l2 = "��� ����.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "� ���� ��� ��� ������.";
								Link.l2 = "�����.";
								Link.l1 = "� ���������"+ GetSexPhrase("","�") +"....";
								Link.l1.go = "Travel_abort";
							}
							else // ���������
							{
							    Dialog.Text = "������� � ����� �� ���� ������. ������� ����� ���� ����, �����, ��� � �����.";
								Link.l2 = "����.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//���� �� ���� ��������, ������������ �������
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//���� ���������� ��������� � ���������� ������� ������ 20, ��������....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//�����...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//�� ������� �������� 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//���� ����� �������, � ��� ���������� � ��, � ��� ������� �� ��������, ���� ��������� �����, � ���� ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "��� �, ����� ��������� ���� �� ����� " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " ���� " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " �� " + pchar.GenQuest.contraTravel.price + " �������. ��������� ������ ����� " +
								FindRussianDaysString(nDay) + ". ������� ����� ����� ���� � ����� ��� ��������� " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " ����� �����.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "������, ���� ����������.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "���, �������.";
						}
						else
						{
							Dialog.Text = "������� � ����� �� ���� ������. ������� ����� ���� ����, ����� ��� � �����.";
							Link.l2 = "����.";
						}
					}
					//���, �������� � ���
					else
					{
                        Dialog.Text = "� ����� ����� �� �������, ��� ���-�� ������� �������� � �����? �������, ��� �� ��� �� ������� ������� ����� �� ����� �������. ��������!";
        				Link.l2 = "��... ������ �� ������.";
					}

				}
			}
			//������� ����, �������� � ���...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "���, �� �� ������� ���. ������ ������.";
					Link.l2 = RandSwear() + " � �� �����!";
				}
				else
				{
					Dialog.Text = "� ���� ������� ���� �����? ���, �� ���� �� ����������.";
					Link.l2 = "�����, �� ������...";
				}
			}
			Link.l2.go = "Exit";
			break;

		//������
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "��, ��� ������...";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//�� �������� �����
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//���������� �����
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//�� �������� �������
		case "Travel_pay":
			//����� �������?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//������ ���� ������
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "������� ����� � ����� ����. ������� ����, �� �������.";
				Link.l1 = "����������.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","�"));
				
				//������ ������.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//������� �� ������ � �����....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "pirate_6", "man", "man", 5, PIRATE, Sum + 2, true));
				//���������...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_SILVER));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//���, �������� � ���...
			else
			{
				Dialog.Text = "������, � ���� �������� � �����������."
				Link.l1 = "����, ����� �����.";
			}
			Link.l1.go = "Exit";
			break;  
			
		case "Give_vector":
			dialog.text = "��� ��������� ����, �������� ���, � ������� �����, �������� ������� �� ���������, � �� �������. �� ���� ���������� ��������, �������������� � ��������� ��������\n� ���� ���� �����-�� �������. � ������ ������ ��� � �������� ������ ��������. ��� ��� ��������� ��� ����������� �� ��������� � ���������� � ���� ������. ��������� � ���� ��� - � ������� �� ����� �� ����������.";
			link.l1 = "� ��� �� ���� �� ����� ����������? �� � �����?";
			link.l1.go = "Give_vector_1";
		break;
		
		case "Give_vector_1":
			dialog.text = "���. �� � ��������� ����� ���� ����� �������. ���������� � ���� - �� ��� ��� ��� ���������.";
			link.l1 = "������, � ����������� ������� � ����.";
			link.l1.go = "Give_vector_2";
			link.l2 = "��... ������, � ���� � ����"+ GetSexPhrase("��","�") +" ������� ����� �������, ����� ������ ��� � �����. ���� �� ���������, ���� �� ���� ����, ��� ������ ������ ����� �� ���� �����? ��������, �� ��� �� ��� ����.";
			link.l2.go = "exit_quest";
		break;
		
		case "Give_vector_2":
			dialog.text = "������ ����� �� ����������� � �������, �������.";
			link.l1 = "��, �������. ���� ������������� ���� �����������. ����� ������� � ����� ���!";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "vector_barmen";
            AddQuestRecord("Headhunt", "1_1");
			AddQuestUserData("Headhunt", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;
		
		case "exit_quest":
			dialog.text = "����� ������� �� ���� ���������. ��������.";
			link.l1 = "����� �������.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "end_quest";
		break;
			
////////////////////////////////////////////////////////////////////////////////
//	END OF ���������� �����
////////////////////////////////////////////////////////////////////////////////
	}
}
