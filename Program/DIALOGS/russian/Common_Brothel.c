												  
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1,iColony;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	switch(Dialog.CurrentNode)
	{
		// ============= ������� ������� =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("�����-�������, ����� �������?! �� ����� �������� ��������� �������, � �� � ������� ���������!","��� �� �� ������... �� ����� �������� ��������� �������!") +"", "��� ��������� ������ ����� �� ������ � ������� ����. � �� �������, ��������� ���� � ����� ������...", "������� ��������� �� ����� ���������, ���� ����� ������ ������!"), 
					LinkRandPhrase(""+ GetSexPhrase("�������� ������ ����������� �� ���� ������� - � � ���� ������ ����� �����!","�������� ������, ��������!") +"", "�����"+ GetSexPhrase("��","��") +" ������, ��� �� ����� ���������! ������!!", "� �� ����� ����, ������"+ GetSexPhrase("��","��") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("��������� �� �����, ����...", "��������, �� �� ���� �����..."));
				link.l1.go = "exit";
				break;
			}
			//homo ������� �����
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
                                    "���� ������ ���, ����� ����.",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
                Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";
				break;
            }
			//-->> ����� ������������� � �������
			//����������
			if (npchar.questChurch == "baster")
			{
				dialog.text = "�� ����"+ GetSexPhrase("","�") +" ������, �� ������������� �� ������"+ GetSexPhrase("","�") +"! ������"+ GetSexPhrase("��","��") +", ����� ������. � �� ���� ���� ����������� � ���� ���������. ���"+ GetSexPhrase("��","��") +" ���!";
				link.l1 = "���-���, ���������!";
				link.l1.go = "exit";
				link.l2 = "��������, � �������, ��� �� �� ���� �������. � ������������� �������"+ GetSexPhrase("","�") +" ����� �����. �� � ���� ������ ���� ������, �, �������, �������� �� ���� � ����� ���������.";
				link.l2.go = "quests";//(���������� � ���� ������)
				break;
			}
			if (npchar.questChurch == "taken")
			{
				
				if (!CheckAttribute(pchar, "HellSpawnFinished"))
				{
					dialog.text = "�� ��� �� �����"+ GetSexPhrase("","�") +" ������ � �������. ������� ����, ������� � ���� - ������� ����! �� ������"+ GetSexPhrase("","�") +"!";
					link.l1 = "��, � �����. � ��������� ����.";
					link.l1.go = "exit";
					break;
				}
				else
				{
					dialog.text = "�� ��������...";
					link.l1 = "� ������ ������� ���� ������ � ������� ������ � �������. �� ��� ���������, ����� ��� � ������ ���� ���������������. � ����������  ���� ������� ������� ����� ��������. ������ ���� ������, � �� � ����� ���� ������.";
					link.l1.go = "ResultChurch_2";
					LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);
					break;
				}
			}
			if (npchar.questChurch == "yes")
			{
				dialog.text = "�� ������"+ GetSexPhrase("","�") +" �������������?";
				link.l1 = "��, � ��� ������"+ GetSexPhrase("","�") +". ����� ������ �������� ����, ��� ���� ������ ������� ��������.";
				link.l1.go = "ResultChurch_1";
				break;
			}
			if (npchar.questChurch == "no")
			{
				dialog.text = "�� ������"+ GetSexPhrase("","�") +" �������������?";
				link.l1 = "������, " + npchar.name + ", � ������ �� ����� ���� ������. � ��������� ���� �� �������.";
				link.l1.go = "ResultChurch_2";
				break;
			}
			//-->> ���� ������ ������������� � �������
			if (pchar.sex != "skeleton" || pchar.rank >= 10)
			{
				if (rand(2) == 1 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questChurch") > 45 && GetHour() < 20)
				{
					dialog.text = "��������, � ���� ��������� �� ����� ���������...";
					link.l5 = "������ �����������.";
					link.l5.go = "toChurch";
					//������ ����� ������� �� ������ ������
					npchar.questChurch = "taken";
					SaveCurrentNpcQuestDateParam(npchar, "questChurch");
					break;
				}
			}
			//<<-- ����� ������������� � �������

			//-->> ���� ������� �� ����
			if (rand(3) == 1 && pchar.questTemp.different == "free" && PChar.sex != "woman" && GetNpcQuestPastDayWOInit(npchar, "questSex") > 180 && !CheckAttribute(npchar, "quest.selected") && !CheckAttribute(npchar, "quest.NotGoneToSex.over"))
			{
				if (!CheckAttribute(npchar, "quest.NotGoneToSex"))
				{
					dialog.text = "��, ��� ������ � ����� ���������. ����� ����, ����� ������ ������� ��� ��, ������� ��� �����?";
					link.l5 = "����������! � �������� �������� ����� ���������� ����.";
					link.l5.go = "toHostessSex";
					link.l8 = "� ���������, ��� �������, " + npchar.name + ". ���-������ � ������ ���...";
					link.l8.go = "exit";
					pchar.questTemp.different = "HostessSex";
					SetTimerFunction("SmallQuests_free", 0, 0, 1); //����������� ���������� �� ���������� 
					SaveCurrentNpcQuestDateParam(npchar, "questSex");
				}
				else
				{
					dialog.text = "� ������� ���, ����� � ����� ���� � ������� �������, �� �� ������... �� ������� ���� ����.";
					link.l1 = "��, ����...";
					link.l1.go = "exit";
					npchar.quest.NotGoneToSex.over = true; //������ ������ �� �������
				}
				break;
			}
			//<<-- ������ �� ����

			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". ����� ���������� � ��� ����������. ���� ����� " + npchar.name + ", � ����� ������� ����. "+ GetSexPhrase("��� ���� ���� �������?, " + GetAddress_Form(NPChar) + "","���������, ������� �������� ������ ��� �����, " + GetAddress_Form(NPChar) + ", �� ���� ��������: �� ��������� ������ �� ������ ��������.") +"",
				                               TimeGreeting() + ". ����������� ���, "+ GetSexPhrase("����������","�������") +", � ���� �������� ���������. ��������� ������������, � "+ NPChar.Name + " - ��������� ����� ������ ��������� ������ ������. "+ GetSexPhrase("��� � ���� ���� ��� �������?","���� ��� ������ � ��� ���� ���-��� ����...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". ��� � ���� ��� ������, " + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + ". ��� � ���� ��� ��� �������, " + GetAddress_Form(NPChar) + "?");
			}
			link.l2 = npchar.name + ", � ���� �������� ����� � ����� �� ����� �������.";
			link.l2.go = "Hostess_1";
			link.l3 = "����� � �� �������"+ GetSexPhrase("","�") +" ����� ������. ����� ������� ������� ����� �� �������?";
			link.l3.go = "ForCrew";
			link.l4 = "� ���� ���� ������.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// ���������  "��������� ���������"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
			link.l4.go = "quests";//(���������� � ���� ������)
			}	
			//-->> ����� ������ ������ ����
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "��������, " + npchar.name + ", � ��� ������ �����������. �� ��� ����� � ���� �������, � ������� ���.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- ����� ������ ������ ����
			if (CheckAttribute(pchar,"drugstaken") && pchar.drugstaken >= 3)
			{
				link.l6 = "���-�� ������� � ���� ��������. �������, ������ ������ ���� ������.";
				link.l6.go = "tubeheal";
			}
			link.l9 = "�����. � ��� �����.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "tubeheal":
			pchar.questTemp.drugsprice = 1000*MOD_SKILL_ENEMY_RATE;
			dialog.text = "������, �� � ������ ������"+GetSexPhrase("��","���")+" �����-�� �����, �������. � �������, � ���� ���� ������. �� ��� ����� ��������� ����� � ����� ������ ���� "+pchar.questTemp.drugsprice+" ��������. �����"+ GetSexPhrase("���","���")+"?";
			if (sti(pchar.money) >= sti(pchar.questTemp.drugsprice))
			{
				link.l1 = "��� ������, ���� �� ��� ������.";
				link.l1.go = "tubeheal_1";		
			}
			link.l2 = "������� ���.";
			link.l2.go = "exit";
		break;
		
		case "tubeheal_1":
			AddMoneyToCharacter(pchar,-sti(pchar.questTemp.drugsprice));
			ClearDrugs();
			WasteTime(12);
			dialog.text = "�� ���, ������ ��������� ������� �����. �������, ������������ ���� �� ������ ������?";
			link.l1 = "����������! �������� �������"+GetSexPhrase("���.","���.");
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("���� �� ������, ���������?","������ ��� �����������, �������.");
				link.l1 = "��������, " + npchar.name + ", � ���������"+ GetSexPhrase("","�") +" ��� ������ � ��������� ���� ������ ���������...";
				link.l1.go = "ShipLetters_2";				
		break;
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "�����-�� ��������� ! ��... �����-�� ����������� ������� ������� ��������� ? � �����, ����� ������� ����� �������� ���������� �����.";
				link.l1 = "��������, �������� ...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "�����-�� ���������! �! ���� �� �����, ��� ����������� ����� ���������� ������� � ���������� ���������� ������ ������. � ���� ���� �������� ���������";
				link.l1	= "�������, ��� ...";
				link.l1.go = "exit";
				link.l2 = "������������! ������ ���"+ GetSexPhrase("","�") +" ������ ���������� �������� � ���������� ���������.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
		//#20171211-02 Allow reconciling with Hostess if promised donation missed.
		case "Reconcile_1":
		    sld = GetFreeHorseRef(npchar.city);
            int nRand = rand(1) + 2;
            int nPrice = sti(sld.quest.price) * nRand;
            //string sPrice = FindRussianMoneyString(nPrice);
            pchar.quest.reconcileHostess = nPrice;
            dialog.text = strreplace("���� ���, � ��������� �������, ��� ��� ��� ����, �� ���� ������, �� � ������ ������� � ����� �� ��������� �������������. ���� �� �����-������ ������ ��� ��� ����������?", "#thisamount", FindRussianMoneyString(nPrice));
            if (sti(pchar.money) >= nPrice)
            {
                link.l1 = "��, � �������, ��. ��� ������ ����, ��� �� ������ ��� #thisamount?";
                link.l1.go = "Reconcile_2";
                link.l2 = "����������.  �������.";
                link.l2.go = "exit";
            }
            else
            {
                Link.l1 = "�� �� ���.";
                Link.l1.go = "exit";
            }
        break;
        case "Reconcile_2":
            AddMoneyToCharacter(pchar, -sti(pchar.quest.reconcileHostess));
            dialog.text = "������! �� ���� � ������.";
            link.l1 = "����� ������, ����������� ���� ������. �� ����������� ����� � �������.";
            link.l1.go = "exit";
            npchar.questChurch = "";
        break;
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("�� ������ ���� �������. ����� ���, �������, �� ��� ���������� ����-�� ��� ���� ��� �����?","�� ��� ��, ��� ������� ������ ������ ����... ������. �� ����������� ����-������, ��� ���� ��� �����?") +"";
					Link.l1 = ""+ GetSexPhrase("���, ��� ����� ����� � ����������, � ��� ��� ����� - ���������. � ���� ��� ��� �����������...","�� �����, ���� �� ���� ���� �����...") +"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "��, ���� ����, "+ GetSexPhrase("��� ��� ������������...","� ��� ���� �� ��������...") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "������� � ��� �� ���� ���� ���� �������, ����� ���� � ���� ��� ���� �������. ������� ������, �������� ��� �������!";
					Link.l1 = "��, ����"+ GetSexPhrase(", � ������ ����� �� ����","") +"... �� �� �����.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "��, �� ��� �������"+ GetSexPhrase("","�") +" �������. ��� ��� ������� �� ��������, ��� �������, � �� �������� ���� �� ��������.";
				Link.l1 = "������, ��� ���.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			//#20171008-01 Brothel adjust changeover period
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > (BROTHEL_CHANGEDAYS - 2)) //98)
			{
				dialog.text = "������ � ���� ��� ��������� �������, ���� ����� ����� ����� ���� ����� ���� ����.";
				Link.l1 = "������, ��� �������.";
				Link.l1.go = "exit";	
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("�� ���, �������, �����������!","� ���� ��� ��� ������, ������ �� �����������.") +" ���� ���������� ���������� ������� �� ����� " + GetFullName(sld) + ", ��� ������ ��������. ������ ��� ������������ ����� " + FindRussianMoneyString(sti(sld.quest.price)) + ". ������"+ GetSexPhrase("��","��") +"?";
				Link.l1 = "���, �������, ��������. ����������...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = "�������, ������"+ GetSexPhrase("��","��") +", ����� ����� ���� �������?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "����, ��� � ���� ������ ����� �����...";
					Link.l1.go = "exit";
				}
			}
		break;
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				if (rand(1) == 0 && pchar.sex != "woman" && !CheckAttribute(pchar,"NoPriest") && GetCharacterSPECIALSimple(pchar, SPECIAL_L) >= 8)
				{					
					dialog.text = "�������, �������, " + sld.name + " ����� ����� ���� � ������� ��� ��������� �� ������ �����. �������, �� ������ �������� �������...");
					Link.l1 = "���, �� � �����...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.greeting = "Gr_Church";
					sld.model = "priest_2";
					sld.model.animation = "man";
					sld.name = "����� �����";
					sld.lastname = "";
					sld.Dialog.Filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Priest1";
					pchar.NoPriest = true;
				}
				else
				{
					dialog.text = "�������, �����"+ GetSexPhrase("��","���") +". " + sld.name + " ����� ����� ���� � ������� ��� ��������� �� ������ �����.";
					Link.l1 = ""+ GetSexPhrase("���, �� � �����","��, � ��������") +"...";
					Link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -sti(sld.quest.price));
					sld.dialog.currentnode = "Horse_ReadyFack";			
				}
				//--> ������ �� �������, ����� �� ����� �����
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- ������ �� �������, ����� �� ����� �����
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //��������� �������
				npchar.quest.selected = true; //���� ���� ����� � �������
				SetNPCQuestDate(npchar, "quest.date"); //���� ������ �������
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// ��������� ��������� �����
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // ���� ���� �� ���� ����
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//����� ������ � ����								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //���� -  ������ �������� � ������
					Log_QuestInfo("������ ��������� � ������� " + sld.startLocation + ", � �������� " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //����������� ���������� �� ���������� 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				
				// ��������� - "����� ��� ������"			
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20) 
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}	
				
			}
			else
			{
				dialog.text = "��� �� ���� ������, �� ���� � ���, ��� " + sld.name + " - ������� ���������, ����� " + FindRussianMoneyString(sti(sld.quest.price)) + ". � � ����, ��������� � ����, ����� ����� ���. ������� ��� ������������"+ GetSexPhrase(", ������","") +"...";
				Link.l1 = "��, ��� ��� ������...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "� ������ ����, ����� ����� ��������� � ��������� ��������� ������ �������... ������ ��� �� ���.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "��, �� ����������, � ���� ��� ����� ������� � ���������. ��������, �� ������� ��������� �� ���.";
				Link.l1 = "��, �� � ������ ��� � ��� ������������"+ GetSexPhrase("","�") +".";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "�������, ��� ����� �������� �� ���. � ����� ���������� � ����� �� ��� ����.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
				Link.l1 = "���, ������ � ���.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "���, �� � ���.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
        case "Hostess_Choice_2":
			dialog.text = "����� ���� ����� ������� �� ��� ��� ���, �������� � �����, � ��� ���� ����.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "�������, ��� ����� �������� �� ���. � ����� ���������� � ����� �� ��� ����.";
			Link.l2.go = "exit";	
		break;
		//==> �������
		case "ForCrew":
			dialog.text = "���.. �� ��� �������? ������, �����"+ GetSexPhrase("","�") +" '�������� ���' � �����? ��� �, � ���� ���� ��������� ������ ����������������� �������, ��������� �� �����... � ���� " + FindRussianMoneyString(GetCrewQuantity(pchar)*30) + ".";
			link.l1 = "������, � ������"+ GetSexPhrase("��","��") +" ��������� ��� ������.";
			link.l1.go = "ForCrew_1";
			link.l2 = "�����, ��� ��������� ���-������...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*30 && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*30));

	            AddCrewMorale(Pchar, 10);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "���, �������, �� ��� ����, �� ��� �������, ��� ���� ������� ����� ���������� �� �������, � ����� ������ � �� ������.";
			    link.l1 = "�������, ��...";
			    link.l1.go = "exit";
		    }
		break;
		case "Woman_FackYou":
			dialog.text = "���"+ GetSexPhrase("��","��") +", �� ���� ��� �����"+ GetSexPhrase("","��") +"?! ���� ��, � ������� ��������"+ GetSexPhrase("�� ���������","�� ��������") +".\n�� � ������ ��� ������ ���� �� ����, ������"+ GetSexPhrase("���","���") +". �������� ���� ��������...";
			link.l1 = "��������, ����...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//������� � ������������� � ������
		case "toChurch":
			dialog.text = "���������, � ������� ����� ���������, �������... ��, �� ������ �������, ��� ��.";
			link.l1 = "� �������.";
			link.l1.go = "toChurch_1";
		break;
		case "toChurch_1":
			dialog.text = "������... �� ��� �� ������, ��� � ���� ����� � �� �����. � �����, � ���� ������� ������������� ������. �� �������� ��� ��� ������ - ����� �������, �������������� �������...";
			link.l1 = "����. � ������ �����������, �� ����������.";
			link.l1.go = "toChurch_2";
		break;
		case "toChurch_2":
			pchar.questTemp.different.HostessChurch.money = (rand(4)+1) * 300;
			dialog.text = "������. � ��� ���� " + FindRussianMoneyString(sti(pchar.questTemp.different.HostessChurch.money)) +  ". ������ ������������� ����� �������!";
			link.l1 = "��� ������ ����� ������, ������ �� ����������.";
			link.l1.go = "toChurch_3";
			link.l2 = "�� ������, � ������ ��������� �����"+ GetSexPhrase("","�") +". ����� ������� �� ���������. ������.";
			link.l2.go = "toChurch_4";
		break;
		case "toChurch_3":
			dialog.text = "�������! ������� ����� �� ���, ����������, ��� ��� ������...";
			link.l1 = "������.";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessChurch.city = npchar.city; //�����
			pchar.questTemp.different = "HostessChurch_toChurch";
			SetTimerFunction("HostessChurch_null", 0, 0, 1); //����������� ���������� �� ���������� � ������ ���������
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.HostessChurch.money));
			ChangeCharacterReputation(pchar, 0.30);
			
			if(pchar.sex == "skeleton")
			{
				location = &locations[FindLocation(npchar.city + "_Town")];
				pchar.HellSpawnLocation = location.id;
				LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", true);
				//id ������
				//Log_Info(pchar.HellSpawnLocation);
				SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn");
				pchar.quest.HellSpawn.win_condition.l1 = "locator";
				pchar.quest.HellSpawn.win_condition.l1.location = pchar.HellSpawnLocation;
				pchar.quest.HellSpawn.win_condition.l1.locator_group = "reload";
				pchar.quest.HellSpawn.win_condition.l1.locator = "reload7_back";
				pchar.quest.HellSpawn.function = "HellSpawn";
			}
			
		break;
		case "toChurch_4":
			dialog.text = "����, ����� ����...";
			link.l1 = "���-������ � ������ ���.";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.HostessChurch");
			npchar.questChurch = ""; //����� ������ ���� ������
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ResultChurch_1":
			dialog.text = "����� �������, ��� ���� ��� �� ��� �������� � ���� �����!.. ������� ����.";
			link.l1 = "�� �� �� ���."+ GetSexPhrase(" ���� ����, " + npchar.name + ", � ����� �� ���...","") +"";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			npchar.questChurch = ""; //����� ������ ���� ������
		break;
		case "ResultChurch_2":
			if (!CheckAttribute(pchar, "HellSpawnFinished"))
			{
				dialog.text = "��� �� �����?! ��, ��, �� ����"+ GetSexPhrase("","��") +" ��������� ������� ����! � � ��� ���������...";
				link.l1 = "������, �� ��� �����...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
			else
			{
				DeleteAttribute(pchar, "HellSpawnFinished")
				dialog.text = "��, � ������ �� ����� ����� ����� ��������� � ������. �������� �� �����, ��� ��� ��������� ������� ����� �������� � ������...";
				link.l1 = "� ��������� ��� ����� ������ ��� �������, ������ ��� ��������� ������ ������� ������ ��������. �� � ���� �������� ��� �� ��������.";
				link.l1.go = "exit";
				PChar.HellSpawn.SeekRebirth = true;
				ChangeCharacterReputation(pchar, 12);
			}
			
			
			npchar.questChurch = ""; //����� ������ ���� ������
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		break;
		//������ ������ �����������
		case "TakeMayorsRing_H1":
			dialog.text = "�������� ������ � �� ��������.";
			link.l1 = "� ������� ����?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		case "TakeMayorsRing_H2":
			dialog.text = "������� ����. ���� ������ ���-�� �������� ��� ������, �� ��� ��� �������� ��� �����������. ����� ������ ����������� ��� �� ��������.";
			link.l1 = "�������... � ����� ���-�� ���-���� ����� ��� ����������?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		case "TakeMayorsRing_H3":
			dialog.text = "��� ���� ��. �������� ����������� ��������� ���� ������� ��������, � ������.";
			link.l1 = "�������... ������� ����, " + npchar.name + ".";
			link.l1.go = "exit";
		break;
		//------- ������ �� ���� ------------
		case "toHostessSex":
			dialog.text = "�� ����� ���. ��� ��� �� ���� ����������?";
			link.l1 = "���?! ��... � ��� ���! � ���� ����� �������... �-�-�... ���������... ����� �������. ���.";
			link.l1.go = "toHostessSex_1";
			link.l2 = "� ���� ������ ���� � ������� ����, � ���...";
			link.l2.go = "toHostessSex_2";
			link.l3 = "�����, � ������� ������� �� �� ���� �����...";
			link.l3.go = "toHostessSex_3";
		break;
		case "toHostessSex_1":
			dialog.text = "���� '���������' ��� �� ���������. ������...";
			link.l1 = "��� �� ���?..";
			link.l1.go = "exit";
		break;
		case "toHostessSex_2":
			if (rand(1))
			{
				dialog.text = "��������! ����� ���������������, ������ ���� ��� ��������� ���� ��������?! �������� ������������� �������, � ����� ������!";
				link.l1 = "�! �������. ��� �����! ������, ���� ���� ���...";
				link.l1.go = "SpeakHistory";
			}
			else
			{
				dialog.text = "��������! ����� ���������������, ������ ���� ��� ��������� ���� ��������?! �� ���������� �� ������, ��� �������� �������...";
				link.l1 = "��, ���� ����� ���������� ��� ��� ���������.";
				link.l1.go = "SpeakHistoryTwo";
			}
		break;
		case "toHostessSex_3":
			dialog.text = "��������� � ������� �����-������ �������� � ������. � ��� ���������� �����?! �-��, ���� ���������� ��������� �������?..";
			link.l1 = "� �� ��� ���� �����!";
			link.l1.go = "exit";
		break;
		//�������
		case "SpeakHistory":
			dialog.text = "����������� ������...";
			if (rand(1))
			{
				link.l1 = "���� � ���� ���� �������, ��� ���� ���� �� ����� �����. ������ ���������?";
				link.l1.go = "SpeakHistory_1";
			}
			else
			{
				link.l1 = "���-�� ����� �� ������ ��������, ������� ������, ������ � ����, � ���� ��������� � �����! ������ � �������!!! ������� ������, ��� � ����! ��-��! � ��� � ���� �� ����� ���� ������� �������, ����� ������, ����������, �� �� ���������� ��������...";
				link.l1.go = "SpeakHistory_2";
			}
		break;
		case "SpeakHistory_1":
			dialog.text = "�-�! �� ���� �������� �����! ��� �� ���� ������� ��������?!";
			link.l1 = "��, ����� �� �������. ������ �� ���-�� � ������ �����, �� �������, � ���� ���������� �����. ������ �� �����������, ���� ���������� �������. ��� ����� �����������, ������ � ����, ��������� ����� ���������� ���� � ����. � ��� � ������� ��������� � ��������, ��� �� ������� ������ ����������: '" + GetAddress_Form(PChar) + ", ����������! �����! �����!!!'. � ��� � �� ������! � ��� ��� ������ � ������� �� ������ ��� �����. �� � ���������!!! � ���� ��� ������ ����! � ���� ������ ��� ��������������� � ���� ����� �� ����!..";
			link.l1.go = "SpeakHistory_3";
		break;
		case "SpeakHistory_2":
			dialog.text = "������! � ���� ��������! �� ������, �������������� ���! �������� � ���� ����!";
			link.l1 = "��, �� ���?..";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_3":
			dialog.text = "�, ����! � ��� ��?!";
			link.l1 = "� �������, ��� ��� �������� � ���� �����, �������������� � �����, ��� ���� ���� � ������, ��� ������ �������� ���������� �������� �����, �� ������ ������� ����� ��������... �� ������ ���������� ����� ���� �����, � �� ���� ������ ��� ��������� �������� �������...";
			link.l1.go = "SpeakHistory_4";
		break;
		case "SpeakHistory_4":
			dialog.text = "� ��?!..";
			link.l1 = "���, �� �. ����. ��� ������� ����. ������, ��� � �� ������� ������� �� ������, � ����� ��� �����.";
			link.l1.go = "SpeakHistory_5";
		break;
		case "SpeakHistory_5":
			dialog.text = "� �� �� �������! ������?! ���� �� ������� ����� �������?";
			link.l1 = "��, ������� �������! ��� ���� �������� ���� ������ ������ - � ������� ������ ��������!";
			link.l1.go = "SpeakHistory_6";
			link.l2 = "���, �� �������. ��� ��, ����� ����� �������� ����� ���������! � ������ ��-�������...";
			link.l2.go = "SpeakHistory_7";
		break;
		case "SpeakHistory_6":
			dialog.text = "��-��... �� ���������� ����! �������� � ����, ������� � ���� ��� ������ ����?.. � ���� �� ����, �� ����� �� �������, ��� � ���! �� ���� �� �������������...";
			link.l1 = "������!! ����, ������...";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_7":
			dialog.text = "� ��� ��?! ��� �� �� ������?";
			link.l1 = "� ��� ����� �������� �����, � �����������, ��� ������ ������������� �� ���� ��������, ������ �������� �����, �������. � ��� ������ �� ����������, ����� ��� ������ ����� ��� ���� � �������, ��� ����� �������� ������ ������ ��������! � �������������, ����� ������� ������, � ���� �� �������, ���������� ��� �������� ��� �������, ��� � ������� �� �����������! � ���� �������, ����� ����� ���������� �� ����� � ��������� ����������� �� ����, � ��� ��� � ������ � ������ ������ �� ��� ���� � �������... �� ������ � ��� �������, � ���� �������� ��������� ������.";
			link.l1.go = "SpeakHistory_8";
		break;
		case "SpeakHistory_8":
			dialog.text = "�-�! �����!.. ������ ���...";
			link.l1 = "������ ������! ������ � ���� ����� ������, �����!..";
			link.l1.go = "SpeakHistory_9";
			link.l2 = "��������? �����?! ��, �, �������, �����, ��������, �� ������������� ��� ����, � �������, ���� ����� ����� �����������... � �� ���� ���� �����������������.";
			link.l2.go = "SpeakHistory_10";
		break;
		case "SpeakHistory_9":
			dialog.text = "��, ���! ������� �� ������, ��� ����� ���� � �����! �� ���� ��������!";
			link.l1 = "��, ������, �� ��� ��?..";
			link.l1.go = "exit";
		break;
		case "SpeakHistory_10":
			dialog.text = "��, ��� �� ����������! � ���� �� ��������� ������, �������� ������ ��������� �������. ��������, �� ������������� ������� ��������� �... ������������, �� � ��� ���� ����� ��������...  � �����, ��� ���-���� ��������� ���������� �� ���� �����, �������� ������, � �������, ��� ��� ����� �� �����������... � ���, ��������, �� ���� �������� ���-������ ����������...";
			link.l1 = "��, ��� ��� �������!..";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes"; 
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //������� ������� �� �����, ���� �� �� ������� � �������
		break;

		case "Hostess_inSexRoom":
			dialog.text = "��, ��� � ��...";
			link.l1 = "��� �����, ��� ��������!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //����� ������ �� �� ������
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");

			//pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            		AddCharacterExpToSkill(pchar, "Fencing", -50);
            		AddCharacterExpToSkill(pchar, "Pistol", -50);
            		AddCharacterHealth(pchar, 10);
		break;

		case "SpeakHistoryTwo":
			dialog.text = "��������?";
			link.l1 = "��������, ��� ��. ��������, ������������� ����!";
			link.l1.go = "SpeakHistoryTwo_1";
		break;
		case "SpeakHistoryTwo_1":
			dialog.text = "���������, �� ������ �� ����...";
			link.l1 = "� ����� ����! ������ � �����, ��� ��� �����! ��� ������ � ���� ������, ����� �����, �� ������ ����� ����! ����� �������������� ������� � ��� �� ��������! ����� �����, ���� ���!..";
			link.l1.go = "SpeakHistoryTwo_2";
			link.l2 = "� ���� ���������.";
			link.l2.go = "SpeakHistoryTwo_3";
		break;
		case "SpeakHistoryTwo_2":
			dialog.text = "�����, ��� ��� ����� �� ��� ����. �� ������� ���� ����, ���������� �� ���...";
			link.l1 = "������, ��� �� ���?!";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_3":
			dialog.text = "��, ����� � ���� ��������...";
			link.l1 = "� ������� ������ ������, � ������ ������ �����, ���, ���, �� ��� ���� ����� ���������, ����� �������� ��� ��. � ��� ���� � ����...";
			link.l1.go = "SpeakHistoryTwo_4";
		break;
		case "SpeakHistoryTwo_4":
			dialog.text = "������ �� ��� ������������?";
			link.l1 = "��� ���� ���� ����� ������ � ����!";
			link.l1.go = "SpeakHistoryTwo_5";
		break;
		case "SpeakHistoryTwo_5":
			dialog.text = "��� ���� ��?";
			link.l1 = "����� ���������� ���� ������, ��� ��������!";
			link.l1.go = "SpeakHistoryTwo_6";
			link.l2 = "��� ������������ ���� �������, ���� ������ � ������� ��� ������. ��� ��� ���� ������ � �����, � ��� ����� ��������� ��� �������, ������ ���� �����, ������� �������� ������ � � ����� ��������� ������, ������� ����� �� ��������� �������������� �����...";
			link.l2.go = "SpeakHistoryTwo_7";
		break;
		case "SpeakHistoryTwo_6":
			dialog.text = "��������! �� ������� ����. �� ������� ���� ����.";
			link.l1 = "����, �� ����������...";
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_7":
			dialog.text = "�-�!.. � �� ��������... � ������!";
			link.l1 = "������? ������! � ������ ������. � ������, ���, �������������. �� ��� ������, ��� ��� ����� ����������� ��� ���� ���� ����� ��������������, ���������� ��������...";
			link.l1.go = "SpeakHistoryTwo_8";
		break;
		case "SpeakHistoryTwo_8":
			dialog.text = "���-�-�?!!";
			link.l1 = "...������� ����.";
			link.l1.go = "SpeakHistoryTwo_9";
		break;
		case "SpeakHistoryTwo_9":
			dialog.text = "�! ���-�� � �� � ��� ��������. ���������, ����� ����.";
			link.l1 = "�� ������ ������, � ���� ����� �� ������ � ����� ������...";
			link.l1.go = "SpeakHistoryTwo_10";
			link.l2 = "��� �� ����� �������� � ���-�� ������? �������, � ���� ����� ������ �����.";
			link.l2.go = "SpeakHistoryTwo_15";
		break;
		case "SpeakHistoryTwo_10":
			dialog.text = "��? � � ��� �� ���? ���� ����� ������������.";
			link.l1 = "� ����� ���������� �����, � � ����� ���������� ��������, � � ���� ������������� �������, ��� ������ � �������, ����� ��������� ���� ����!";
			link.l1.go = "SpeakHistoryTwo_11";
		break;
		case "SpeakHistoryTwo_11":
			dialog.text = "������!..";
			link.l1 = "���� �����... � ��, ��������, ��������� ���� �����, ��... ����� �� ���� ���������� ������, � ����������� ����� � ���, ��� ��� ���. ��, ������, � �������...";
			link.l1.go = "SpeakHistoryTwo_12";
		break;
		case "SpeakHistoryTwo_12":
			dialog.text = "������ � ����... �...";
			link.l1 = "���?";
			link.l1.go = "SpeakHistoryTwo_13";
		break;
		case "SpeakHistoryTwo_13":
			dialog.text = "�������������� ����...";
			link.l1 = "��� � ������?";
			link.l1.go = "SpeakHistoryTwo_14";
		break;
		case "SpeakHistoryTwo_14":
			dialog.text = "���� �����... ����� ������� �����, ����� ������� ������, ��� ����������, ��� � ���������... ��������.";
			link.l1 = "� ���������� �������������!";
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes"; 
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //������� ������� �� �����, ���� �� �� ������� � �������
		break;

		case "SpeakHistoryTwo_15":
			dialog.text = "��? � � ������, ��� ��������� ���� �������, � �� ���������� ��������. ������ �����! � ���� ���, � ���������� ������ �� �� ���?!";
			link.l1 = "� �� �� ���� � ����...";
			link.l1.go = "SpeakHistoryTwo_16";
		break;
		case "SpeakHistoryTwo_16":
			dialog.text = "����, ��� �� ����� � ����! �������, � ������� �� ������! ��� ���!!! ����������! �� ��� ��������!";
			link.l1 = "�� �� ��� " + npchar.name + ", � � ������ �� ����!..";
			link.l1.go = "exit";
		break;
		// ================================== ������� ������ =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("��� ����� ���� �� ���������!", "��� ��������� ������ ����� �� ������! ��� ����� ����...", "������������ - � � ���?! ��� ��, � ������ ���..."), 
					LinkRandPhrase("��������!!", "�����"+ GetSexPhrase("��","��") +" ������, ��� ������! ������!!", "� �� ����� ����, ������"+ GetSexPhrase("��","��") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("���, �� � ���� �� ��...", "��������, �� �� ���� �����..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("������������, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", ��-��-��..") +". ��� ����� ���������� � ������� ���������, ��� ������ �������� ����� ���.", 
				"��, ��� ����� ��. ��������, �� ��� ����� ������� ������� ��� ������� � ��������. ����� ��� ������ � ���.", 
				"����������, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", � ����� �������, ��� �� ��� �� ������ � � ������ �����, � �� ������ � ����������... ���","� ���") +" ��� ����� ��� ������ � ������� ���������.", 
				"��, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", ����� �� ��... �����������!",", ��-��-��... ��, ������, ���������.") +" ��� ����� ������ � ������� ��������� ��� ���������� ������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, "+ GetSexPhrase("���������, ","") +"� �����"+ GetSexPhrase("","�") +".", "�-�, ��, �������...",
                      ""+ GetSexPhrase("������ �� �����������, ���������, � ����� � �����, ��� ���!","��-��...") +"", ""+ GetSexPhrase("��� ������, ���-�� �������... ������, �����.","������, ������.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "� ��� ��� ���������?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("����, ���������, � ����� ������ ����� �������...","�� ��������� ������ ������������, �������!") +"", ""+ GetSexPhrase("������, � ����� �� ����� ����� �������� �������!","������, � ��������� �� ��������� ����� ����������!") +"", ""+ GetSexPhrase("��, �����, �� ���������� ���������.","��, ������� ��� ��� ���������� �������... � �� ������ ��������!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> ����� ������ ������ ����
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("������, "+ GetSexPhrase("���������","�������") +", �� �� �������� ����� ������������ ������? ������� ��� ��� ���� �������...", 
					"��������, ��, �������, �� �������� � ����� ��������� ������������ ������?", 
					"��������, "+ GetSexPhrase("���� ���","�������") +", ������� �� ���������� ���� ���, �����������?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- ����� ������ ������ ����
            //--> ����. �������, ����� �8. ����� � ������� � �������.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" || pchar.questTemp.State == "SeekBible_toGirl")
            {
    			if (npchar.id == "HorseGen_"+FindLocation("FortFrance_Brothel")+"_1")
				{
					if (!CheckAttribute(npchar, "quest.HolLineTalk"))
					{
						dialog.text = "���, ��� �������� ���"+ GetSexPhrase("�� �������� �����","�� ������ �������") +", ����� ���������...";
    					link.l4 = "��������, ��������� ����� ����� � ��� ��� ������� � ��������� ������������...";
    					link.l4.go = "Step_Hol8_1";
					}
					else
					{
						dialog.text = "��������"+ GetSexPhrase("","�") +" ������?";
						link.l4 = "��� ���� ������, ������ ���������� ���, ��� ������.";
    					link.l4.go = "Step_Hol8_5";
						AddMoneyToCharacter(pchar, -1000);
					}
				}
            }
			//<-- ����. �������, ����� �8. ����� � ������� � �������.
			NextDiag.TempNode = "Horse_talk";
		break;
        case "Horse_1":
			dialog.text = "��� � ����� ��������, �� ������ ������ � ��� ������ ����� �����, ��������������� ������ �� �����, ���� ����� ����� � ������ ������� ����. �� ����� " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "�������, "+ GetSexPhrase("�����","��������") +", �������.";
			Link.l1.go = "exit";			
		break;
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("��, ���� ���, �� ���� ������� ������� �����! ������, � ������ ��������, ��� ��� ���� �� �������� ����, �� �� ���������...", "�� ������������� ��� ��������? ��� ����� � ����� �������... ��������, � ������ ��������, ��� ��� �� ������ ������� ����."+ GetSexPhrase(" � ������ ���� ���� ����� � ����� �����...","") +"", ""+ GetSexPhrase("��� ���?! ��, �� �����, � ��������, �� ����� ���������� ������� � ���� ����� ����� �����...","��, �������... ��� ���� ������� ��� ������...") +" ������, � �� ������ � ������ ������, ��� ��� � ��������� ���� ������� ����. ������, ��� �� ���������� �����"+ GetSexPhrase("��","���") +"...");
				link.l1 = "���, ������ ���� � �������!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+ GetSexPhrase("��-�-��, ��� ��� ������ ���������� ���������� ����","��� ��� ������ ����������") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //��� �����, �� �� ����� ���������
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("������ ��� � ���� �����, ����� ���? �� ����� ��� ������ ����������. ������� �����!","�� ��� ������ ����� ��� �� ������� - ������������ �� ������!") +"", ""+ GetSexPhrase("�� ���� �����������, ��� ��� ������� ����� �����? ��, ��� ����� ���... ���� ������ ���� - ����� ������� ���������, � �������� ��� �� �����.","�������, �� ��������������� �� ������ �����. ������ ��� - �������...") +"", ""+ GetSexPhrase("��� ���� �������� �������������... ����� - � � ���� �����, �� ������ ��� ����� ������� �����!","�� ����, ��������? ������ ������������ - �����, � �� ��������� ���������!") +"");
				link.l1 = "���, ����� ������!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //�� �������
			}
		break;
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " ��� ��������� � ����� ��������. ��� � ���"+ GetSexPhrase(", ��� �����,","") +" � ������ ��� ��� - " + npchar.name + ". � ���� ���� �����...";
			Link.l1 = "�������, �����, ����� ����...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //��� ���������
			SetNPCQuestDate(npchar, "quest.choice");
		break;
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("�� ��� �������"+ GetSexPhrase("","�") +" �������, ��� ���� ����, ���������� ������.", 
				"� �� ���� ������� - ���������� � ���.", 
				"������ �����������, ��� ��� �������� - ���������� � ���...", 
				"���������� ��������, �� �������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��, � ����.", "� �����.",
                      "������ �� ���������, � ��� � �����.", "��, � ��� ��� ��?..", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> ������� �� ������� ������������, ���� ����� ��� ���
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("���-�� � ���� �� �����."+ GetSexPhrase(" �� ����������� �������, �� ����� �� �������� �����. �������� ���...","") +"", 
					"����� �� ����� �������������? ��, ��� � �������, � ��� ��� �����.", 
					"��, � �� ������� ����? ������� �� - ��� � ������� ���������.", 
					"��� ������ ����� ���������� ��������, �� �� �����������, ���"+ GetSexPhrase("��","��") +"...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("��� �����, ������ ��...", "������, � ��� � ������.",
						"��-��, � �����"+ GetSexPhrase("","�") +"...", "��, ������, ��������.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "������� �� ����������. ���� �� ������ ����� ����, �� ��� � ������� ���������. ��� ��� ������...";
				Link.l1 = "�������.";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("�����, �� ��� ���������. ","") +"�� ��������� ���� ����� �����...", 
						""+ GetSexPhrase("��, ��������, �����, ���","���") +" ����� ������� ��� ���� �����, �� ���� ��� � �� ���� �������...", 
						"��������, ����� �� ���-���� ������� ��� � ��������?..", 
						"��, ���� �� ����, ��� � �������...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("�� �� �� ��� �� �����!", "�����������!",
							"��, �������!", "����, ���� � �������...", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "� ���� �����, � �� ��� � �� ����"+ GetSexPhrase("","�") +" ����! �� ���� �������, ��� � � �������� �� �����...";
					Link.l1 = "��, ��� ����������...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //��� �����, �� �� ����� ���������
				}
			}
			else
			{
				dialog.text = "��-�, ��� ����� ��, ��"+ GetSexPhrase("� ������� ������","� ������� �������") +"! ���� ���� ����� ����� �, �� ��� � ������� - �� ���������..."+ GetSexPhrase(" ������, � ���� ������, �������, ������ �� ��������� ���������� �� ���� �������� ����������, �� �� ������...","") +"";
				Link.l1 = "������� ���� ������ ����-����, "+ GetSexPhrase("���������","�������") +", � �� ����� � ����� ���������.";
				Link.l1.go = "exit";
				Link.l2 = "��� ����� �������, ��� �� ���� ���������, �� ������ �������� � ����� ���� �, ���������, �� ����.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("��� ���,"+ GetSexPhrase(" ����� ����,","") +" �������-�� ����� �����. ��� �������� �����, ��� ������ ������.", 
					""+ GetSexPhrase("��, �������� ��,","�� ��� ��") +" ��������� ���� � ����...", 
					"��������, ����� ������ ���?!", 
					"��, �� ���� ��, ������ ������"+ GetSexPhrase(", ����� ������ ������� ���������. ������ �� ���� ��������� - ��� � ������� ���������, ��������!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("��, ������"+ GetSexPhrase("","�") +"...", "��, ��� ��� ��� � �������...",
						"��, ����� ������, � ����� � ���...", "���������� � ����������"+ GetSexPhrase(", ����","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "�-�-�, ��� ����� ��! "+ GetSexPhrase("� ����� � ������� ���������� ������, ������ �� �������� � ���� ����... �","���������, �") +"��� ������ "+ GetSexPhrase("���������","������������") +" �� ���� - ����� ������� ���������, � ����� ���� ��� �����������...";
				Link.l1 = "���, ��� �� ����������...";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1_Add":
			dialog.text = "��, �� �����, ��� ���� ��� ����������... ����� ����.";
			Link.l1 = "������...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> ����
		case "Priest1":
			chrDisableReloadToLocation = true;
			dialog.text = "����������� ����, ��� ���. �� �����, ������� �������...";
			Link.l1 = "��� �� ����� ����������? ���, �� �������...";
			Link.l1.go = "exit";
			//--> ���-�� ���������
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // ��� �����
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//������� ������ � ������� - Gregg
			{      
				DeleteAttribute(PChar, "chr_ai.TraumaQ");			
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("�� ���������� �� ������� ������");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- ���-�� ���������
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //�������
			NextDiag.TempNode = "Priest2";
			AddDialogExitQuest("PlaySex_1");
			
			/// ��� �� �������
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// ��������� ��������
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Luck", 500);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "Priest2":
			dialog.text = "���� �����������? �� ��������� ��������, �� ������, ���� � �������� ����� ������������, ������ ���� � ��������� ����� ���� � ��� ������� ����";
			Link.l1 = "������ ��� ����, �����...";
			Link.l1.go = "exit_2";
			NextDiag.TempNode = "Priest3";
		break;
		
		case "Priest3":
			dialog.text = "�� ������� ����������. ������ ������� � �����.";
			Link.l1 = "������...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Priest3";
		break;
		
        case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("����� ���� ������ ���� � ������� ���������. "+ GetSexPhrase("� ��� �� ������ ��������?","�� ��� ��, ����� ������������?") +"", "�������, �� ���������"+ GetSexPhrase(", �������� ���� ��� ���� �� ��������� ��� ����.",". � ����� ����... ��������, �� ���������.") +"");
					Link.l1 = RandPhraseSimple("������� �� �����, �������...", ""+ GetSexPhrase("����� �����������, �����!","�� ����� ������ �������!") +"");
				break;
				case "1":
					dialog.text = "��, ��� � ��, ��"+ GetSexPhrase("� ������� ������! � ���-��� ������� ���� � ������ �������� ���� �����","� ������� �������! ��������� ��� ���� �� �� �������� �������") +"...";
					Link.l1 = "��, ��� ��������� ������...";	
				break;
				case "2":
					dialog.text = "�-�-�, ����"+ GetSexPhrase("��","��") +", �������-��. ��, �� ����� ������ �������!";
					Link.l1 = ""+ GetSexPhrase("�� �����, �����...","��, ������ ���, ��� �� ������...") +"";
				break;
			}
			Link.l1.go = "exit";
			//--> ���-�� ���������
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // ��� �����
			if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//������� ������ � ������� - Gregg
			{      
				DeleteAttribute(PChar, "chr_ai.TraumaQ");			
				DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
				Log_Info("�� ���������� �� ������� ������");
				CheckAndSetOverloadMode(pchar);
			}
			//<-- ���-�� ���������
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //�������
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			
			/// ��� �� �������
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// ��������� ��������
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "�������, � ���� �� ���"+ GetSexPhrase("��","��") +" �� �����������"+ GetSexPhrase("��","��") +"?";
				link.l1 = LinkRandPhrase("�� ���"+ GetSexPhrase("��","��") +" ����.", "� �������� ��� ���������.", RandPhraseSimple("� ���� �� �� ��������� �����.", "���� ��, "+ GetSexPhrase("��������","�������") +", ����� �������� ����������."));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("�� ���� ��� ������, ��� � ������ �� ��������! � ������ ������� ��������� ������� ������� � ������������","��-�, ������ �� ���-���� ��������� ������������ �������... � ���������.") +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("���� �����������?", "��, ��� �������? ��� � �������?", "��� ����,"+ GetSexPhrase(" ������, ���"," ���") +" ���������?");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("�������, ��� � �������","� �� � ������... ������") +".", ""+ GetSexPhrase("��� � �����, ������","�� ������, � ������ ��������") +".");
						Link.l1.go = "exit";
					break;
					case "1":
			  
						if (sti(npchar.quest.sexHappend) > (rand(4)+5) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
						{
							dialog.text = "��������, �� ������ �� ��� ��� �����, � ��� � ���� �����������...";
							Link.l1 = "�� � � � ���� ����, ���� ��...";	
							Link.l1.go = "HorseQuest";
						}
						else
						{
							dialog.text = LinkRandPhrase("�� ���, � ��������� ��������?", "��, ���"+ GetSexPhrase(" � ����, �����������",", ���� �����������") +"?", "� �������, "+ GetSexPhrase("�� �������, ������ ��� � �-�-����� ��������","�� ��������. � ���������") +"...");
							Link.l1 = RandPhraseSimple("��, ��� ��� ����� �����������.", ""+ GetSexPhrase("������� �������������, �� ���� �� ������!","��� ���� ������ ������������!") +"");	
							Link.l1.go = "exit";
						}
					break;
					case "2":
						dialog.text = RandPhraseSimple("�� ���, ���� ����.", "����� �����,"+ GetSexPhrase(" ������,","") +" ���� ���� �� �����.");
						Link.l1 = RandPhraseSimple("���, ����...", "�� �������� � ������� ����...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "��, ��� ��� � ��� �����������?";
				link.l1 = "������, ��������, � �� ������ �� �� ���-�� ����� �������?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("������ � ��� ��� ���-������...", "�� �������� � �� ����� ������...", "����� ���� ������ ���� � ��� ���...");
				Link.l1 = "�����...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "��� ����� ���������� �������� � ������?";
			link.l1 = "��, ���-�� ��������...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "��������� ������� � ����� �������� �� �������, �� ����� ������� ��� � ���� � ������.";
			link.l1 = "�������, �����. �� ��������.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		//==> ����� �� ���
        case "HorseQuest":
			pchar.questTemp.HorseLoot = sti(pchar.questTemp.HorseLoot) + 1;
			npchar.questTemp.HorseLoot = true; //��� ������
			dialog.text = "������ ���, � ���� ���-��� ����������, ��������, ��� ������� ����...";
			Link.l1 = "��, ������"+ GetSexPhrase(", ��������",", � ���� ������") +".";
			Link.l1.go = "HorseQuest_1";
		break;
        case "HorseQuest_1":
			dialog.text = "������� ���� ��� ������ ��� ����� ����. ��� ���, ������ �� ���-�� ��� ���� �� ��������� �����, ������ ���������...";
			Link.l1 = "�����, ������ ������ ��������.";
			Link.l1.go = "HorseQuest_2";
		break;
        case "HorseQuest_2":
			dialog.text = "����� ���� � ���. ���� �� �����, �� ������ �� ������ �����, ��� ��� ���� ���������� ������ ��� ����.";
			Link.l1 = "� � ���������� ��������������� �� ������ �� �������?";
			Link.l1.go = "HorseQuest_3";
		break;
        case "HorseQuest_3":
			sTemp = LinkRandPhrase("Shore55", "Shore9", "Shore_ship2");							
			if (sTemp == "Shore55") 
			{
				str = "������ ���-���� ���� �����";
				str1 = "box" + (rand(1)+1);
			}
			if (sTemp == "Shore9") 
			{
				str = "����� �������";
				str1 = "box1";
			}
			if (sTemp == "Shore_ship2") 
			{
				str = "������ ������, ��� ����� � �������";
				str1 = "box2";
			}
         	pchar.GenQuestBox.(sTemp) = true;
			switch (pchar.questTemp.HorseLoot)
			{
				case "1": 
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass2 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry1 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry5 = 6;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry10 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.indian11 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 15000;
				break;
				case "2": 
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass3 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry14 = 3;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry16 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry18 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.indian17 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 19000;
				break;
				case "3": 
					pchar.GenQuestBox.(sTemp).(str1).items.indian20 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian5 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian10 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass4 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian19 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 24000;
				break;
			}
			dialog.text = "�� ���-�� ������ � " + str + ".";
			Link.l1 = "��� �, ������� ���� �� ����������. ���� �������� ���-������, �� ������� ��� �����.";
			Link.l1.go = "exit";
		break;

		// --> ��������� - "����� ��� ������"
		case "Horse_ReasonToFast_1":
			dialog.text = "����� ������ ���, � ������ ���� ���� ����... �� ���"+ GetSexPhrase("�� �����, �� �� ��� ������","�� �����, �� ��, ��� ��� ������") +" - �� ��������, �� �� ��������, �� ��� ������� �������...";
			link.l1 = "� ��� ��� ��?..";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "�� ��� ����� ����� ���������� ��������. �� ������-�� � ��� �� �����, � ��� �������� ��������. ��� � ���� ������... �������-�������, ����� ������� ���� �������� � ����������� � ����� �����-��. ��� ������ ������, ���� ���� ������ �� �������, ��-��-��...";
			link.l1 = "���� �� �� �����, "+ GetSexPhrase("���������","�������") +", ����� ������ ������? ���� ������, ��� � ������� �����, ��������� - ��� � ���� ���������, � ��� - � �����, �� ��������������. "+ GetSexPhrase("��-��-��-��!..","��-��-��!") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "") { 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true; 
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- ��������� "����� ��� ������"

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_2":
			AddSimpleRumour("�� ������ ��� � ������? ��� �� ��� �����������! ������� ����� ������ ����� ������� �� ����� ������� � ������� ������� � ����� ����������� � ��������� ��������� �� ��� ����������.", sti(npchar.nation), 10, 1);
			npchar.lifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors_Priest", -1);
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		//������ ������ ����
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //���� �������� � ������
			{
				dialog.text = LinkRandPhrase("���, �������, �� ����������, � ���������. ���� �� ������, �� �� ����...", 
					"���, "+ GetSexPhrase("���������","�������") +", ������ �� ������...", 
					"� ���������, ���. �������� ������ �� ������.");
				link.l1 = "����... �� ��� ��, ������� ����.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "�� �� ������ �� ����������� �� ������ �����?";
					link.l1 = "������, ������!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("���, �������, �� ����������, � ���������. ���� �� ������, �� �� ����...", 
						"���, "+ GetSexPhrase("���������","�������") +", ������ �� ������...", 
						"� ���������, ���. �������� ������ �� ������.");
					link.l1 = "����... �� ��� ��, ������� ����.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "������, �� ������ ��� ��������! ��� ��� ���������� ��� � �� �������.";
			link.l1 = "��������?! ���?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		case "TakeMayorsRing_S3":
			dialog.text = "����� ������������, �������!";
			link.l1 = "��� �� ��� ������ ��������, ����� ������. �� ������ ������ �� ������.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		case "TakeMayorsRing_S4":
			dialog.text = "�� � � �� ����� ��� ���? ���� �� ��� �� ��� �� � ����, �� ��� ��� ��������!";
			link.l1 = "��������, ��������, ��� �� ����������. �� ����� ���� � ��� ���������? ������ ���� �����������, ���� ���������... �����, �� ����� ���� ������� ��-�� ����� ������.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "������ �����, ������ �� ��������� ��� ���� ����� ��������.";
				link.l1 = "������, ������� ���� ������ � ���� ������.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "��, �� �����. ����� ��������!..";
				link.l1 = "�������������, ��������!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		case "TakeMayorsRing_S6":
			dialog.text = "����������...";
			link.l1 = "��, �������. ������� �� ������, ��������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
//********************************* ������� ����� �� ������� �� **********************************
  		case "Step_Hol8_1":
			dialog.text = "� ���?";
			link.l1 = "������"+ GetSexPhrase("","�") +" �, ���� �� ������� ����� �����-�� ��������� � �������, ���� ������...";
			link.l1.go = "Step_Hol8_2";
		break;
  		case "Step_Hol8_2":
			dialog.text = "���� �����, �����... ��������, "+ GetSexPhrase("���������, ����� ���������� ������","�������, ������� ��� -") +" � � ������ �� ��� ���� �������. ���� ��� ����� ������ ����� 1000 �����...";
			link.l1 = ""+ GetSexPhrase("��� ����� ������ ������ ���-���...","�� ������ ���� ���-������ ������� ���������?") +"";
			link.l1.go = "Step_Hol8_3";
		break;
  		case "Step_Hol8_3":
			dialog.text = ""+ GetSexPhrase("������, ������ �� ����� ���� ������. �� ������ ������� - ����� �� ����� ��� ����������.","��-��-��... ���� ����� ���������� - ��� ����� ������. ������, ���� ���� �� ������ ����������, �� � ���-��� ���, ���� ���������� ������... � ���� ����. ������ ��� ����� ������, ��-��...") +"";
			link.l1 = ""+ GetSexPhrase("����, � ���� ������� ���...","� ���� ��� ������� �� ��������.") +"";
			link.l1.go = "Step_Hol8_4";
		break;
  		case "Step_Hol8_4":
			dialog.text = ""+ GetSexPhrase("��, ������� ������� ����� ���������!!!","��, �� ����� ����... ����� ������ - �������� ���, ��� ����.") +"";
            if (sti(pchar.money) >= 1000)
            {
    			link.l1 = "��� ���� ������, �� ������ ��� ������ ����� � ������.";
    			link.l1.go = "Step_Hol8_5";
                AddMoneyToCharacter(pchar, -1000);
            }
            else
            {
    			link.l1 = ""+ GetSexPhrase("������ � �� ���������, ����� ������ ���... ","") +"����� � ����, ��� ��������� ������...";
    			link.l1.go = "exit";
				npchar.quest.HolLineTalk = true;
            }
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Step_Hol8_5":
			dialog.text = "����� �� ���� ������� �����, ��� ����� ������� ���������� �����, ����� �� ������.";
			link.l1 = "��, � ���?";
			link.l1.go = "Step_Hol8_6";
		break;
		case "Step_Hol8_6":
			dialog.text = "��������� ��� �� � �����. �� ������� �������� ������, � ��� ���������� � ������, ��� �� �����. �������� ��� �� ���������� �����, ����� �� ���� ���� �������� �������, ��� �� ��������.";
			link.l1 = "��, ��� ��� ���������, �� � �����"+ GetSexPhrase("","�") +" �� �� ����������. ��� � ���� ����� ����� �������?";
			link.l1.go = "Step_Hol8_7";
    	break;
		case "Step_Hol8_7":
			dialog.text = "��� �������� �� �������, ��� � �������. ��� � ��� �������, ����� ��� ����� �� ����, �� ��������� ����������, ���������.";
			link.l1 = "�������, ���������� ����.";
			link.l1.go = "Step_Hol8_8";
    	break;
		case "Step_Hol8_8":
			dialog.text = "������, � ���, ������������� ��� ����� ����� �����?";
			link.l1 = "������ �������, �������� ����. � ��� �� ���� �������? ��� �����, ��� ����� � �����?";
			link.l1.go = "Step_Hol8_9";
    	break;
		case "Step_Hol8_9":
			dialog.text = "�� ������ ����������, ��� � �� ������ ����� ������. �� �� ���� ����, �� �� ������ �� �����...";
			link.l1 = "����. ������� ����, ����� ������ �� �����.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "4");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.State = "SeekBible_toTavern";
			NextDiag.TempNode = "Horse_talk";
    	break;
	}
}


ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
