// boal 25/04/04 ����� ������ Usurer
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
 
	// ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "���, ������������, " + pchar.name + ". � � ����� ���������...";
					link.l1 = "������ � ����!";
					link.l1.go = "exit";
					break;
				}
				//������������
			
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
			
			//homo ������� �����
            if (Pchar.questTemp.CapBloodLine == true )
            {
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff"))
                {
                    dialog.text = "������ ����, ������ ����. �� ������ �� ������ ��� � ����� ������? ����������, �� �������� ������ ������.";
                    Link.l1 = "���������, ��� �� ������?";
    				Link.l1.go = "CapBloodUsurer_5";
                    break;
                }
                dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
                                    "��� ������ ���, ����� ����.",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
                Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == false)//homo ������� �����
                {
                    Link.l2 = "� � ��� �� ����.";
    				Link.l2.go = "CapBloodUsurer_1";
                }
				break;
            }
			//�������, ����� �5, �������� �� ������� ����� -->
			if (CheckAttribute(npchar, "PLQ5Money"))
			{
				dialog.text = "�� �������� ��� ��� 50 �����?";
				link.l1 = "��� ���, � ���� ���������. �����.";
				link.l1.go = "exit";
				link.l2 = "�����, ��� � ���� ������ �� ������ � ���� �����. ��������, ��� � �������"+ GetSexPhrase("��","���") +".";
				link.l2.go = "StepPL5End_close";
				if (sti(pchar.money) >= 50000)
				{
					link.l3 = "��, � ������"+ GetSexPhrase("","�") +" ���� 50 ����� � �����"+ GetSexPhrase("","�") +" �� ��� �������.";
					link.l3.go = "StepPL5End_1";
				}
				break;
			}
			//<--�������, ����� �5, �������� �� ������� �����
			
			//-->������������
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "��, �������-�� �� ��� ��������"+ GetSexPhrase(" ��������� �������","� ��������� ����") +", � �� ��� ���������� ���������, ������� ������, ��� � �� ������� ��������� �� ���������� ������� ����� � ������ ����� ������� ������, ���� ����������� �� ��������\n��� ������ �� ������ �����, ���������� �� ����������, �� ����� ��������� ���������� ���� ������� ����������, ����� ������ �� ������� � ������ � ��� ���� �� ����������� ������ ���� � ���������.";
				Link.l1 = "�����, ���� ��������� �� ������������ ��, ������� ����� ����� �� ��������, �������� ��� �������� ���� ����������.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//����� ������ �� ������
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "��, ������ �����, ������ ���� �������� ������� �����������, ����� ��������� ��� ���! �� ������� � ����� ������ ����� ���� ��������� ����� ���� ������! ��� ���� ������� ���������� � ����! � ����� �"+ GetSexPhrase("��","��") +", ��� ��� ���������� � �������������!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "�-�-�, ��� � ��, �������! �� ����� ���������� ��� ����� ����� � ����� ������� ������. ��� ��� ������!";
				Link.l1 = "� �� �������"+ GetSexPhrase("��","��") +" ������������ ����� �����... �� ����� ��� �������.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "�� �������� ���� ����� �����?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
				Link.l1 = "��, ������"+ GetSexPhrase("","��") +". ��� � ���� � ������.";
				Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "���, � ��� ������� ��� ����.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "��... �� ��� ����? �������... ��, �����, ��� ���������. �������! �� ������! ����� ������!";
				link.l1 = "��� ���� ���!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "������ ����. ���� ����� " + GetFullName(npchar) + ". ��� ���� ���� ��� �������?";
				link.l1 = "�! � ��� �� ��� �������, ���������?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<--������������
			
			//-->> ���� ������ ����� ���������� ����������� ������
			if (rand(1) && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel") && npchar.city != "Charles" && !CheckAttribute(npchar, "quest.slave"))
			{
				dialog.text = "������������, �� ��� ������ �������! ���� �������� ��� ���� ����.";
				link.l1 = "����������� ������. ��� �� ����?";
				link.l1.go = "usurersJewel_1";
				npchar.quest.usurersJewel = "inSeek"; //������ ���� ���������� �� ������ �����
				SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
				break;
			}
			//<<-- ���� ������ ����� ���������� ����������� ������
			dialog.text = NPCStringReactionRepeat("������������, " + GetAddress_Form(npchar) + ". ��� � ���� ��� ������?", 
				"�, ��� ����� ��? ����� ����������, " + GetAddress_Form(npchar) + " ��� �� ������ �� ���� ���?", 
				"��, ����� ��, " + GetAddress_Form(npchar) + "... �� ��� ��, ��� ��� ������ ������� ��� ��� �� ����. ��� �� �������?",
                "��, " + GetAddress_Form(npchar) + ", �� ���� ����������� �� ������, �� ���� ����� ������ ��������� �������... ��� ��� ������?" , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�����, � ������ ���"+ GetSexPhrase("��","��") +" ���������� � ����������.", 
				"����� �. � ����� ������ ��� ���������� �����"+ GetSexPhrase("","�") +".",
                "���, ����� �. � ����� ��� ����������� ���� ���"+ GetSexPhrase("��","��") +" ����������.", 
				"��-�-�, ������ ���������� ����������� �����... � ��� �� ��� ������ �� �����, ������ ��������� �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "� ���� �������� ���� ���������� ���������������.";
			link.l2.go = "LoanUsurer";//(�� ��������� ���������)
			link.l3 = "��� ����� ���-����� ����������... � �����, ���� ������.";
			link.l3.go = "quests";//(���������� � ���� ������)
			//������� ���, �������� �������� �� �������
			if (CheckAttribute(pchar, "questTemp.LSC.usurerId") && pchar.questTemp.LSC.usurerId == npchar.id)
			{
				if (pchar.questTemp.LSC == "SignOnPoorMurder")
				{
					link.l4 = "����������, ��� ������ ��� ��������� ������� �� ��� ���.";
					link.l4.go = "ISS_deposit";
				}
				if (pchar.questTemp.LSC == "PoorMurderExecute")
				{
					link.l4 = "��� ���������� ����� ������� �� ������� ��������, ��� ��������� � ���.";
					link.l4.go = "ISS_takeDeposit";
					DeleteAttribute(pchar, "questTemp.LSC.usurerId");
				}
			}
			//������ ����, ������������� �� ���������� �����
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //����� ���� - �� ����� � ����� �������
			{
				link.l7 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
				link.l7.go = "IntelligenceForAll";
			}
			//<<<<---------------- �������, ����� �5. --------------------
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1") && npchar.city == pchar.questTemp.piratesLine.Q5.city_1)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirstUsurer")
				{
					link.l5 = "�������, ��� �� ����� ������ ��������.";
					link.l5.go = "StepPL5First_1";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst")
				{
					link.l5 = "����������, �� �������� �� �� ����� ������?";
					link.l5.go = "StepPL5First_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2") && npchar.city == pchar.questTemp.piratesLine.Q5.city_2)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecondUsurer")
				{
					link.l5 = "�������, � ��� ���� �������� � ������ ������...";
					link.l5.go = "StepPL5Second_0";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond")
				{
					link.l5 = "����������, �� �������� �� �� ����� ������ ��� ���������� ���������?";
					link.l5.go = "StepPL5Second_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3") && npchar.city == pchar.questTemp.piratesLine.Q5.city_3)
			{
				if (pchar.questTemp.piratesLine == "PPL5Hunter_toThirdUsurer" || pchar.questTemp.piratesLine == "PPL5Hunter_toThird")
				{
					link.l5 = "� ��� ����� ������, � ��� �� �� ���������?";
					link.l5.go = "StepPL5Third_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_4") && npchar.city == pchar.questTemp.piratesLine.Q5.city_4)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFourth")
				{
					link.l5 = "� ������"+ GetSexPhrase("","�") +", � ��� ��������� ���������, ��������, ��� ����������� ������?";
					link.l5.go = "StepPL5Four_1";
				}
			}
			//-------------------- �������, ����� �5. ---------------->>>>
			//-->> ����� ������ ����� ���������� ����������� ������
			if (CheckCharacterItem(pchar, "UsurersJew") && CheckAttribute(npchar, "quest.usurersJewel.type"))
			{
				link.l6 = "� ���"+ GetSexPhrase("��","��") +" ��� " + npchar.quest.usurersJewel.type + ". ��� ��.";
				link.l6.go = "usurersJewel_R1";
			}
			//<<-- ����� ������ ����� ���������� ����������� ������
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "���� ����������, ��� ������������ ����� �������� ���� ����������.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			//-->������������
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "� �� ������ ������ ��������� � �������� �����.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������������, " + NPChar.name + ", � �� ������ ������ ���������.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������������, " + NPChar.name + ", � �� ������ ������ ���������.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������������, " + NPChar.name + ", � �� ������ ������ ���������.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "� ����"+ GetSexPhrase("��","��") +", ��� �� � ��������������. ��� ��� ������ ���������?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "��� �� � ��������������, � ����"+ GetSexPhrase("��","��") +". ��� ��� ������ ���������?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������ ����, " + npchar.name + ". ��� ���� ����? ���� ����� �������?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "���� ������� ���������. ��� ������� ��������� ������ �����, ���� ��� ���� � ��������.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������ ����, " + npchar.name + ". � ����"+ GetSexPhrase("��","��") +", ��� �� � ��������������, �� ��������� �������� �������.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "� ���� ������ �������, " + npchar.name + ". ��� �� ������� ��������� ����������.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "��������, " + npchar.name + ". � ������"+ GetSexPhrase("","��") +" ����������, �� ������� ����� �� ���"+ GetSexPhrase("��","��") +". �� ������, ��� ��� ��� ����?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "� ���� ������� �������, " + npchar.name + ". ��� ������� ������� ���������� � ������� ������. ��� ���.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������ ����, " + npchar.name + ". �� ���, �� ��� ����������� ��� ���� ����� ����?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", ��� ������� ����������� ��� ��� ���������� '������'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", ��� ����� ����, �� � �� ����"+ GetSexPhrase("","��") +" ��������� ���� ������.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������ ����, " + npchar.name + ". � ����"+ GetSexPhrase("��","��") +" �� ������ ��������.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", ���� ������� ���������. �������� ������� �����, ��� � ��� ��� �������.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", ��� ����� ����, � �������"+ GetSexPhrase("","�") +" ������� ��������, ���� ���"+ GetSexPhrase("","�") +" ��� �� ����� �������. �� ��� ��� ������� �������� �� ����� ������� ����� � ���� ��-��� ����.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "������ ����, " + npchar.name + ". ��, �������������, ��� �� ������� ���� �� ��� �����������.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--������������
			NextDiag.TempNode = "First time";
		break;

		//<<<<----------��������� -"������� ���������". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "����� ������������ �������� �� ����� �������� ����� ����� �������, � ��� ����� ����� ������.";
			link.l1 = "����� ���� " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " ������� ������������ ���� �����?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "���� ����. ��������!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "�����-�� ���������! ���, ������� ���� ��� ���. �������� ������ � �������� ����������.";
				link.l1 = "���������, �� �� �� ������������, ��� �� ���������� ��� �� ���� ��������!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "�� ��� �� ... � ���� ��������� ����� �������. �� ����� � �� ����� �������, �� ������ ������������ �������. ";
				dialog.text = s1 + "������������, ��� �� ��� ����� � ������� ������� ������������. �� ��� �� �� ������ �������� ?";
				link.l1 = "��� ���������, ��� ����� ������� ����� ....";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "�-��.... ���� � �� ����, ������� �� ��� � ��������. ";
				dialog.text = s1 + "��������� ��������� �� ��� ������������ ���������� �������, � ��� ������� �������� ����� ����������������� � ���������� ������.";
				link.l1 = "����������? � ������� ����������?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "�� ������������, ��� � �������� ��� ������, �� ����� ����. �� ���� ��� ������ �����������.";
			link.l1 = "������� � �� ����...";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "������ ������ ���. ��� ��������� ��������� '���������������', �� ������������� � ����? � ��� ���� �� ���������� �������� ���������...";
			link.l1 = "�����������. �������, ��������!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "������ ���. ������, �� ����� �������� ����� ������� ��� ������� ��������������. ";
			dialog.text = s1 + "��� � ��� �������, �������� ���� ����� ������ ����� � �� ������ ����������� ������.";
			link.l1 = "�����������. �������, ��������!";
			link.l1.go = "exit";		
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
			dialog.text = "����� �������������? �� ��� �������������? ���� ����, ��� ���� ������� ��� ������� ��������� ��� ������, ��� ��� � ����������� ����� �����! �� � � ��� ���� ��� ��� ���� ������. � ��, ���, �����������! � �����������, ���, ����� �� �������, � ���� �������� �����-�� ������ ���������, ������ �������, � ������������� ������������� �����������!";
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
			dialog.text = "����� ����� �������?! � ����� �������� �� ��������? ��������, ����� �������, � ���� ��... �������! ������ ��� ������ ���� ������� � ����� ����� �������� �� � ������ �����������. �������� �� ������������� ������ ������� � ����� ���������� ����� �������. �� ����� ��� ������� �������������. ��������.";
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
		
		//<<<<---------------- �������, ����� �5. --------------------
		case "StepPL5First_1":
			dialog.text = "�������, � �� ��������� ��������� � ���� ����������. ������, ��-��, �������, � ������� �� ��� �������, ��� ��������� �������� ��������� � ���� ���������.";
			link.l1 = "� �� �� ������, ���� ����������? �����, ��� ������ ���������� ������ �����?";
			link.l1.go = "StepPL5First_2";
		break;
		case "StepPL5First_2":
			dialog.text = "��� ����� �� ����, ����� �������� ���� �� ��������.";
			link.l1 = "��� �������, ��� �� ��������. ��, �����, �������� ���-�� ����?..";
			link.l1.go = "StepPL5First_3";
		break;
		case "StepPL5First_3":
			pchar.questTemp.piratesLine.Q5.city_2 = GetQuestNationsCity(SPAIN); 
			dialog.text = "�� ����� �� ��������� �� ����� ����� ���� �������, � ��������. � ���� ����� - �� �����... ���� ���������, ���-�� �� ������� � " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Dat") + ". �� ���� ���������, ��� �� ������������� �� �������.";
			link.l1 = "�����"+ GetSexPhrase("","�") +". �������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "4");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Acc"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_2) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecond";
		break;

		case "StepPL5Second_0":
			dialog.text = "�-�-�, �� �� ����� ��������...";
			link.l1 = "��, ��� �� �������� ���?";
			link.l1.go = "StepPL5Second_1";
		break;
		case "StepPL5Second_1":
			dialog.text = "�������. ������ �� ��������, ���� ������ ������. ������ � ������� ���� ������� ������, ���, �����, ����� � �������� �����, ����������� ����������� ����� �����, � ��� ������ ����, ������� �� ����.\n"+
				"����� ���, ���������� �� �������, ��� ����� �����, � ������ ���� �������, ���� ������ �������?! ������� ������, �������, ���� �� � ������, ��� ������� �������� ����� ������...\n"+
				"� �����, � �������� � �����������, ����� ���� ������ ����-�� ����� �� ������ ������. � ������, ������� � ��� �� �����!";
			link.l1 = "����. � ���� �� ����������, ��, �������, �� � �����...";
			link.l1.go = "StepPL5Second_2";
		break;
		case "StepPL5Second_2":
			pchar.questTemp.piratesLine.Q5.city_3 = GetQuestNationsCity(FRANCE);
			dialog.text = "�����, � ��������� ������� ���� ��������. �������� ����� ��� �������� ��� �������� � �������. ���� � ������� �� �����, �� �� ������� ���������� ����� ���������...";
			link.l1 = "���������, ��� ��� �����, ��� �� ��� ������. ������� ��� �� ���������� �� ������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "6");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_3) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toThird";
		break;

		case "StepPL5Third_1":
			dialog.text = "���� ������������ ��������� ��� ������, ��� ������ ������� �������� ��� ����...";
			link.l1 = "� ��� �� ����� ������ ����������?";
			link.l1.go = "StepPL5Third_2";
		break;
		case "StepPL5Third_2":
			dialog.text = "��� ������ ���� ������ ��������. ���������, ��� ����������� ���� �����, �� �� ����� �� �����������. ������ � �������, ������ ������� ���� �������, �������� �������. ������� � ������ �������� ����� �� �����...";
			link.l1 = "�������... ��, ����� ����, ���� ���� �����-�� �����������, ���� �� ��� �����������?";
			link.l1.go = "StepPL5Third_3";
		break;
		case "StepPL5Third_3":
			pchar.questTemp.piratesLine.Q5.city_4 = GetQuestNationsCity(Holland);
			dialog.text = "���� ��� ���������� ��� ������, �� �����, ��� �� ���������� � " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4) + ".";
			link.l1 = "��... � ������� ������� ������������� � ���� ��������?";
			link.l1.go = "StepPL5Third_4";
		break;
		case "StepPL5Third_4":
			dialog.text = "�������. ������ ��, ���� � ���, ��� � " + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Dat") + " ������� ��� �������� ���������.";
			link.l1 = "�-�-�, � ��� �����"+ GetSexPhrase("","�") +"! ������� ��������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "8");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_4) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFourth";
		break;

		case "StepPL5Four_1":
			dialog.text = "���, ���, �������. ������ ��� �� �����, � ������ ����� ����� ����� ������, �� ������ � ���� ����! �, �� ����������, �� ���� ��"+ GetSexPhrase("��","��") +" �� ������, ������ ������ ����� �� ��� ������ ���... �-�-�, ��������, ��� �� �������, ��� �����?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "StepPL5Four_2";
		break;
		case "StepPL5Four_2":
			dialog.text = "��, ��, � � ��� ������... �������... ��� � ��� � �����������? � ��, �������������, ��������� ������ ��������, ����������� ��� � �����, � �������� ���� �������! ����!!! ���������� ��������, ������� ���� ���...";
			link.l1 = "��������, ��� ���������, �� �� ���, ������, � ���?";
			link.l1.go = "StepPL5Four_3";
		break;
		case "StepPL5Four_3":
			dialog.text = "...������� ����� �������. ��� � ���?! � ���������, �������! ��, ��� ������! ��, ������, ���� ������ ��� �������! ������ - ��� ����! ����!.. �� ���� �������� �����������, ��� ���, ���� � ���� �������, ��� �� �������� �������...";
			link.l1 = "���? ������?!";
			link.l1.go = "StepPL5Four_4";
		break;
		case "StepPL5Four_4":
			dialog.text = "��, ������ ����� ������? ���������, �������! ��������, ��� �� ���� ��� ����� �����������?!";
			link.l1 = "��������. � ���� � ������� ��� ������������? ��� ��� �� ������ �������?";
			link.l1.go = "StepPL5Four_5";
		break;
		case "StepPL5Four_5":
			dialog.text = "�-�-�... ��... ���, � ��������, ��� �����, ��� ������ ������, �� � ������ �� ������������ ����. ���� ���� � ��� ���� �� ��������.";
			link.l1 = "������� �������. ���� � ������ ���� ��� �� ��������. ��� � ����� ����� ���� ����?";
			link.l1.go = "StepPL5Four_6";
		break;
		case "StepPL5Four_6":
			dialog.text = "��������� �����! ���� �� ��� ��� ��� ���������, ���� ������� �������� ���� �����.";
			link.l1 = "��� ����� ���������?";
			link.l1.go = "StepPL5Four_7";
		break;
		case "StepPL5Four_7":
			dialog.text = "�� �������, �� ��� ������������?! ��� �� ������ ����� �������� ����������? ����� ������, ���� �������� �������� �� �������.";
			link.l1 = "������. �� �����! ����� ����, � �����!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "9");
			pchar.questTemp.piratesLine = "PL5Hunter_toBermudes";
			npchar.PLQ5Money = true; //����� �� ����������, �������� ������ �����
			//����� ������ ���������� �� ���� � ��� ���� �� ��������
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1 = "location";
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1.location = "Pirates_houseS1";
            Pchar.quest.PQ5_inOrryHouse.function = "PQ5_inOrryHouse";
		break;

		case "StepPL5End_close":
			dialog.text = "�����, � ���� ����� �����������. ��� �������, ��� �� ���-�� ���������������... �� �� �����.";
			link.l1 = "��� ������! ��� ���������, ��������.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "PLQ5Money");
    		ChangeCharacterReputation(pchar, -50);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -20);
		break;

		case "StepPL5End_1":
			dialog.text = "���� ������, � ���! �������, � ��� ��������� � ��� ���������, ������� ������� ����?";
			link.l1 = "�� ������� �� ��������, ������ �� ��� �� �����������...";
			link.l1.go = "StepPL5End_2";
		break;
		case "StepPL5End_2":
			dialog.text = "�����������, �� ��� ��, � ����� ��������� ��� ������. ������� ������...";
			link.l1 = "�������� ��������.";
			link.l1.go = "StepPL5End_3";
		break;
		case "StepPL5End_3":
			dialog.text = "�������! ������ �����������! ��� � �������. ��� ���� 5 �����, ��� � ��������������.";
			link.l1 = "�������...";
			link.l1.go = "StepPL5End_4";
			DeleteAttribute(npchar, "PLQ5Money");
			AddMoneyToCharacter(pchar, -45000);
    		ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
		break;
		case "StepPL5End_4":
			dialog.text = "�� ��� ��, � ������ ��� ��� ������ � ����. � ���� ��� �������, ��� ���� �������� � ����� ���������������� � ���������. ������ ������ ��� �� ����, �� ���������� ����"+ GetSexPhrase("��","��") +"...";
			link.l1 = "����� � ������ ��������... �� �����, ��������.";
			link.l1.go = "exit";
		break;
		//-------------------- �������, ����� �5. ---------------->>>>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		��������� ��������� Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer": 
			dialog.text = "������� �������. ����������� ��� ������.";
			link.l1 = "���� �� � ��� ����, ��������� ��������� ������?";
			link.l1.go = "Loan_GiveWork";
			//����� ��������
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = "� �� ������ ������� � ��������.";
                link.l2.go = "FindCitizen_1";
            }
			//��������� ������
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = "� �� ������ ������� � �������� �������.";
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = "� ������"+ GetSexPhrase("","��") +" ��� ������.";
                link.l4.go = "TakeChest_2";
            }
			//�������
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "� ����"+ GetSexPhrase("��","��") +" ��� "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(". � �����"+ GetSexPhrase("","�") +" ������� ����.", ". � ������ ������ � � ��������� ��������� ��� ����.", ". ������� �����, �������, ������������.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("� ���� ������ �����.", "��� ������ ������������ ����-������ ��������.", "��� ������ ���������� �������?");
				Link.l6.go = "loan";	
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("� �� �����"+ GetSexPhrase("","�") +" ������ ������ � ����.","������� �� �������� ��������� ������?", "��������� �� ������ ���� �������� �����?");
					Link.l7.go = "deposit";				
				}
			}
			if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear),makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth),makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Deposits.(NPC_Area).Interest))*iPastMonths;
				Link.l8 = LinkRandPhrase("� ���� ������� ���� �����.", "������ ����� ������� ��� ������, ��� � ��� ��������.", "��� ����� ��� ������ � ���������� ��������.");
				Link.l8.go = "Deposit_return";									
			}
			//�����
			if (sTemp == "credit")
			{
				link.l9 = LinkRandPhrase("� �����, ��� ����"+ GetSexPhrase("","�") +" � ��� ������, �� ����������� ���� �� �����"+ GetSexPhrase("","�") +"...", "� ����, ��� ����"+ GetSexPhrase("��","��") +" ���, �� ������ � ���� ��� �����. ����� �����...", "� �����, ��� ����"+ GetSexPhrase("��","��") +" ���, �� � ������ ������ �� ���� ����������� ������� ��� ��������� �������. � ������ ��� �����.");
				link.l9.go = "Loan_Remind";
			}
			else
			{
				link.l9 = "� ����"+ GetSexPhrase("��","����") +", ������� ���������� ��� � ���� � ���� ���. ��������.";
				link.l9.go = "exit";
			}
		break;
		//=============================  ���� ��� �� ���� ������ - ������� � ��������
		case "Loan_GiveWork": 
            // �������� �� ���� ����������� -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "�� ���� " + GetFullName(pchar)+ ", �� ��� ��? � ���� " +
                              RandPhraseSimple("����� ������� �����","������� �� ������ �������") + ", � �� ���� ����� � ����� ����.";
				link.l1 = RandPhraseSimple("��... ����� �������� ����������, � ��� ����� � ���� �������.", RandSwear() + "�� � �� ����!");
				link.l1.go = "exit";
                break;
            }
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//��� ������ ���������� �� ����
			{
            dialog.text = "���, � �������, � ���� ��� ������.";
			link.l9 = "��������, ��� ����.";
		    link.l9.go = "exit";
			break;
			}
            // �������� �� ���� ����������� <--
            dialog.text = "���, � �������, � ���� ��� ������.";

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(1);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // ������ ������
                }
                switch (iNum)
                {
                    case 0 : // ����� ��������
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;
                        
                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // �������� �� ���� ��� �������
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (7 + cRand(sti(PChar.rank)))*1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = ", ��� �� " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "��, �� �������. ���� � ���� ���������� ������, ��������� �������. "+
                                     GetFullName(chr) + ", ������� � " + XI_ConvertString("Colony"+chr.city+"Dat") + sTemp + ", �������� ��� " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     ". ���� �� ������� ��� ��� �����, �� ���������� �������� ������ �������� ����. ���, ������, ���������� " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = "� ������!";
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;

                    case 1: // ��������� �������
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;
                        
                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + drand(2);
                            pchar.GenQuest.LoanChest.Money      = (3 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*250;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = ", ��� �� " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "��� ����� ����������� ������� ��� ������ ������. ����� ��������� ������ - " + pchar.GenQuest.LoanChest.Chest + 
									" ������� � ������� � "+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + " ��� �������� �� ����� " +
									GetFullName(chr) + ". �� ������� " + GetWorkTypeOfMan(chr, "") +
									". �� ������ �������� " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + ". ��� ����� ������� �� " + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = "� �����"+ GetSexPhrase("","�") +"!";
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                     break;
    			}
    		}
            else
            {
                dialog.text = "� ��� ��� ��� ������.";
            }
            link.l9 = "��������, ��� ����.";
		    link.l9.go = "exit";
		break;
		//============== boal ���������� �������� ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = "������������. ��� ��� ��� ����� ������.";
			link.l9 = "�� �������!";
			link.l9.go = "exit";			
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];     
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = ", ��� �� " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Dat") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //�������� ���������� ������
            dialog.text = "� ���� ��������.";
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = "���� ��������� ���������!";
                link.l1.go = "finish_work";
                link.l2 = "��� ������� ����� ��������, �� �� ������� ������ �� ���� �����.";
                //if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
               // {
                //    link.l2.go = "finish_work_bad";
                //}
               // else
               // {
                    link.l2.go = "finish_work_lie";
              //  }
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = "��� ������� ����� ��������, �� �� ������� ������ �� ���� �����.";
                link.l1.go = "finish_work_bad";
            }
            link.l3 = "� �����"+ GetSexPhrase("","�") +" ������������ ��� ����� �� ������ �������� - ��� �� ��� ����.";
            link.l3.go = "finish_work_cancel";
            //link.l9 = "���. ������.";
			//link.l9.go = "exit";
		break; 

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = "��� � ������!";
    			link.l9 = "����������!";
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterReputation(pchar, 1);
    			OfficersReaction("good");    			
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = "������������! �� ��� ��� ������? �����-�� ����.";
    			link.l9 = "����� �����!";
    			link.l9.go = "exit";
    		}
		break;
		
		case "finish_work_bad":
            dialog.text = "����� � ����� �����! �� �� � ��������� ������ ���� ������!";
			link.l9 = "���� ������� ������ ��� �� �����������, �� �� ����� - ��� ��� ������.";
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("��","���"));
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;
		
		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = "� ��� �������, �� ���� �����������! � ����� ����, ��� �� � ��� ��������. ������� ��� ������!";
                link.l1 = "��, �� �����, ��� ������.";
    			link.l1.go = "finish_work";
    			link.l2 = "�� �� ��������� �������!";
    			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			//link.l9 = "��� ������ �������. � ����� �����.";
    			//link.l9.go = "exit";
    			//ChangeCharacterReputation(pchar, -1);
			}
            else
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "�����, � ��� ����������� �� ���.";
                link.l1 = "��, �� �����, �� ������ �����.";
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("��","���"));
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;
		
		case "finish_work_bad_2":
			ChangeCharacterReputation(pchar, -3);
            dialog.text = "�� ��� ��������, ��� ������� �� ���. ������� ��� ������!";
			link.l1 = "�� ������ �� - ��� � ���� �����!";
    		link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
            link.l2 = "��, �� �����, ��� ������.";
    		link.l2.go = "finish_work";
			}
		break;
		
		case "finish_work_lie":
            dialog.text = "��, �����?";
            link.l1 = "�������!";
    		link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
            dialog.text = "�� ��� ���? � �� �������, ��� � ��� ��� ��� �������? � ��� ����� ������� ������������, ������� ��������� ��� ����� ������ ���� �����, � ��� ������. ����������!";
            link.l1 = "�� ���������. ��������� ����������!";
    		link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
    		DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    		AddQuestRecord("Gen_LoanFindCitizen", "7");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal �������� �������� ===============
		case "LoanUsurer_ChestWork_1": 
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = "� �� ��� ����� �����������.";
			link.l9 = "�� �������!";
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// ������� ������� �����
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = ", ��� �� " + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = "� ���� ��������.";
            link.l1 = "� �����"+ GetSexPhrase("","�") +" ������������ ��� ����� �� �������� ������� - ��� �� ��� ����.";
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = "���. ������.";
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = "�����, � ��� ����������� �� ���.";
                link.l1 = "��, �� �����, �� ������ �����.";
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("��","���"));
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = "��������, � ����� �������� ���������� ����� ������, ���� �� ������� ��� ��� �������.";
                link.l1 = "����� �����.";
    			link.l1.go = "Exit";
			}
		break;
		//============== ������� ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "���, ����� �� ���� ������. � ����� ����������� ����� � ���� ���������� ������ ������ �������� �����.";
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "������, ������� ����������� � ������.";
	                Link.l1.go = "deposit";
				}
                Link.l2 = "��� ��� �� ���������.";
				link.l2.go = "exit";
                break;
            }
			// �������� �� ���� ����������� -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "�� ���� " + GetFullName(pchar)+ ", �� ��� ��? � ���� " +
                              RandPhraseSimple("����� ������� �����","������� �� ������ �������") + ", � �� ���� ����� � ����� ����.";
				link.l1 = RandPhraseSimple("��.. ����� �������� ����������, � ��� ����� � ���� �������.", RandSwear() + "�� � �� ����!");
				link.l1.go = "exit";
                break;
            }
            // �������� �� ���� ����������� <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "�, ������ ����������. ����� ����� ��� ����������?";
			Link.l1 = "��� ����� ������������� ������ �� ��������� �����";
			Link.l1.go = "Small";
			Link.l2 = "���� ��������� ����� �� ������� ����";
			Link.l2.go = "Medium";
			Link.l3 = "��� ����� ������������ ������ �� ������ ������������ �����.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 5000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "�������. � ���������� ������� ������ ����� - ������ �����. � ���� ���������� ��� " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "������������. ��� ����� ��������?";
			Link.l1.go = "Interest_1";
			Link.l2 = "���, ��� ����� �� �������. �������-�� �� �������.";
			Link.l2.go = "Loan";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
			//Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 10000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "�� ��������. �������, ��� " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " ������� ��� ������ ���� ��������. ��� ������ ������������ �����.";
			Link.l1 = "������������. ��� ����� ��������?";
			Link.l1.go = "Interest_2";
			Link.l2 = "���, ��� ����� �� �������. �������-�� �� �������.";
			Link.l2.go = "Loan";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 20000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "�-��... ����������... �� �����, � ����� ������������ ��� ���� �� ����� � " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". ��� �� ���������, �������, ��� ������������� ������� ������. ����� ����� ��� �������� ��������� � ����� ����.";
			Link.l1 = "������������. ��� ����� ��������?";
			Link.l1.go = "Interest_3";
			Link.l2 = "���, ��� ����� �� �������. �������-�� �� �������.";
			Link.l2.go = "Loan";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = PcharReputation();
		break;

		case "Interest_1":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " ��������� � �����. ����������� �� ���, ��� � � ��� ����, � �� ���� ���������� ��� ������ ������ �������."; 
			Link.l1 = "���� ��� ������ ����������. �������� ���������� ����.";
			Link.l1.go = "Period_1";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest_2":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " ��������� � �����. ����������� �� ���, ��� � � ��� ����, � �� ���� ���������� ��� ������ ������ �������."; 
			Link.l1 = "���� ��� ������ ����������. �������� ���������� ����.";
			Link.l1.go = "Period_2";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;
		
		case "Interest_3":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + " ��������� � �����. ����������� �� ���, ��� � � ��� ����, � �� ���� ���������� ��� ������ ������ �������."; 
			Link.l1 = "���� ��� ������ ����������. �������� ���������� ����.";
			Link.l1.go = "Period_3";
			Link.l3 = "�����, ��� ����� �� ������� � �����. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;
		
		case "Period_1":
			Pchar.Quest.Loans.(NPC_Area).Period = 3;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "�������� ��, ��� � � ��� ������, " + Pchar.name + ", � ���� ����� �������� ����� ������� " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". ����� ����, ��� �� ���������, � ����� ����."; 
			Link.l1 = "��� ��, � � ������������� �������� ���� �������... � ���� ������.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "���, �� � ���� �� ������������. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period_2":
			Pchar.Quest.Loans.(NPC_Area).Period = 6;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "�������� ��, ��� � � ��� ������, " + Pchar.name + ", � ���� ����� �������� ����� ������� " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". ����� ����, ��� �� ���������, � ����� ����."; 
			Link.l1 = "��� ��, � � ������������� �������� ���� �������... � ���� ������.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "���, �� � ���� �� ������������. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;
		
		case "Period_3":
			Pchar.Quest.Loans.(NPC_Area).Period = 12;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "�������� ��, ��� � � ��� ������, " + Pchar.name + ", � ���� ����� �������� ����� ������� " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". ����� ����, ��� �� ���������, � ����� ����."; 
			Link.l1 = "��� ��, � � ������������� �������� ���� �������... � ���� ������.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "���, �� � ���� �� ������������. �� ��������.";
			Link.l3.go = "ExitDelLoan1";
		break;
		
		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "�������� ����� ���. �� ��������� ��� ��� ������������. � ����� ��������� ����� ����� � ����, ��� ������� ��������� ��������. ��� ��� ���� � ��� � ���� ����� ����� ������������ ��� ������, ����� �������� ��\n�� ���� ��� ������� - ������ ������������.";
			Link.l1 = "��... ��-��. ����� ��������.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "��, ��������... �������� ������. �� � ������� � ��� �������� �� ��� �� �����.";
			Link.l1 = "�� ����������. �� �������.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // ���� � ��������� ����
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("�, ��� ������ �������! � ����� �����, ��� ��� ����������� ������ - � � ����� �������.", "���������. ����� ������� ����� ���� � ������� ���������, ������� ������� ������� ����. � �� ������, ������ ������...",  "�, �� ��� � ��� � ��� ����� ������, " + GetAddress_Form(NPChar) + "! �������, ��� �� ��������� ���, ����� �� ���������� � ���� �������!");
			Link.l1 = LinkRandPhrase("� ���� ������ �����.", "��� ������ ������������ ����-������ ��������.", "��� ������ ���������� �������?");
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("� �� �����"+ GetSexPhrase("","�") +" ������ ������ � ����.","������� �� �������� ��������� ������?", "��������� �� ������ ���� �������� �����?");
				Link.l2.go = "deposit";				
			}
			Link.l3 = "�� ��������, " + NPchar.name + ".";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("� ����� ��������� ��������! ��� ������� ����� �� ������ ������ � ����?", "������. �������� ���, �� �����, ��� �� ��� �������, ����� ����� ��� � ������� � �����������, � ���� � ����������... �, ������, ������ ��� �����?", "� ������, �� ���������, ��� � ���� � ���� �����. ������� �� ������ ������ ��� �� ��������?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;

		case "result":
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "������ ��������?";
				link.l1 = "��, ��������, �������� �����..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "��, ����� ����� � ��� ��� ���� ���, � ���������. ������� ��� ���������...";
				link.l1 = "��... ������.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "������. ��������� ��� ��� ����� � ����� ��� ����������... ��... ������, " + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + ". ����������, � �����.";
			Link.l1 = "���� ��� ����������.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "����� � ������ �����.";
			Link.l2.go = "Deposit";
			Link.l3 = "�������, ��� �� ����� ������������ � ��������. ����� ��������.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)+".Result"))
			{
			    Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "�������� ����, �������, �� ��� ����� ������� ������ ��� ��������������� �����. ��� ������ ����� ������������ ������ ����� �����, ����� ����� ����������� ����������� �������� �� ������ ��������. �� � ���������� ��������� ������, ������ ��... ��, �������, �� ���� ��������� ���������? � �����, � ���� ������� �� ��� � ����� �� ����� " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "����� ����, �������� ���������� � ������� ����������.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "������ �� ������ ���� �������, ��� ���� ����� �������� ���� �� ������� ��� ��� ������� � �������������. ���� �� �� ������ ������� �����, �� ��������� � ����� �����.";
				Link.l1 = "������. ����� ��������.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum      = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			// ����� ����
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			DialogExit();
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "������ �� ���������, ������� �� ��������� � ������� ���, � �������� ��������� �����, � ���������, ��� ������ ��� " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + "... �� �������, ��� ������ ������� ��� ������";
			Link.l1 = "���������. ������� �� ����.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "������, �� �����. ����� ��� ��� ������� �������. ����� ��������.";			
			Link.l2.go = "Exit";		
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "��... ���� ���� � ���� ������������. � � ��� ��� ���-�� ������. ��� �� - ��������� �� ��� ���.";			
			Link.l1 = "���� ����������� - �����. ��������� ����������.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "�� ��� ����? ��������, ������ ������� ��� ������? � �����! ��-�� ��� � ������� �������, ������� �� ��� � ����� �� ����������! � �� ���������, ���� �� ����� ��� ����!";
            Link.l1 = "� ��� ��� ���� ������� ���� ���� �����.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("��, ����� ���������! ������ ����, ��� �� � ��� ����� ������ ����� ������!", "��������� ���?! �� ������, ���������, ��� �� �����������...", "������ - �� ������� � �����. ��� ��� �� ����� ���� ���� ��� ��� ��������� ������ � ������� ������.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "���������� �� ����� ����! ����� ��� ��� �� �� ������!";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal ����������� ��������� -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "��? � ��� �� �����������?";
			Link.l1 = "�� ������� � ����"+ GetSexPhrase("��","��") +" ��� ����� � " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". ��������� �� ���.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "����� �������� ���������, ��������� ������� ��� ����� ����� � ������� " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "��� ������ ����! � ���� ��� �� ����� ����� ����.";
			Link.l1 = "�������. ������ �� �������.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // ���� � ��������� ����
		break;
		//������ ������������ ����� �� ������
		case "usurersJewel_1":
			sld = ItemsFromID("UsurersJew");
			switch (rand(3))
			{
				case 0: 
					sld.JevelType = "���������";  
					sld.model = "DiamondA";
					sld.picIndex = 2;
					sld.Jewel = "jewelry5";
				break;
				case 1: 
					sld.JevelType = "�����";  
					sld.model = "RubyA";
					sld.picIndex = 3;
					sld.Jewel = "jewelry5";
				break;
				case 2: 
					sld.JevelType = "�������";  
					sld.model = "EmeraldA";
					sld.picIndex = 4;
					sld.Jewel = "jewelry5";
				break;
				case 3: 
					sld.JevelType = "������";  
					sld.model = "SapphireA";
					sld.picIndex = 1;
					sld.Jewel = "jewelry5";
				break;
			}			
			dialog.text = "�� ������, �� ���� ��������� �������� ���������. � ������� " + sld.JevelType + " ���������� ������. �� ����� ���������� ���� �� ���. ����� ������, ��� ������ - �� ���!";
			link.l1 = "�� � ���? ������ ������ " + sld.JevelType + " � ���� � ������.";
			link.l1.go = "usurersJewel_2";
			npchar.quest.usurersJewel.type = sld.JevelType; //��� �����
			npchar.quest.usurersJewel.money = (cRand(6)+2) * 500 + 1000; //��������������
			npchar.quest.usurersJewel.jewel = sld.Jewel;//�������
		break;
		case "usurersJewel_2":
			dialog.text = "��, ���� �� ��� ���� ��� ������! ���� � ���, ��� ���� " + npchar.quest.usurersJewel.type + " �������� � ����� ����. ���� ������ ������� ��� �������� ��� ������������ �������. ��������� ���-������ �������� �� ������� � ����� � �� ���� �����������...";
			link.l1 = "�-��, ��� ������������� ��������. ��, � ��� �� � ���� ��� ������?";
			link.l1.go = "usurersJewel_3";
		break;
		case "usurersJewel_3":
			dialog.text = "������� " + npchar.quest.usurersJewel.type + ", ������ � �����!";
			link.l1 = "� ��� �� ��� ��������?";
			link.l1.go = "usurersJewel_4";
		break;
		case "usurersJewel_4":
			dialog.text = "� ��������, ����� �� �������. � ������ ����� ����������� ��� � ������. ��� �����������...";
			link.l1 = "���������, � ������� ��������� ������ ���������. � �� ����� � �� "+ GetSexPhrase("�����","��������") +". ������ ���������� ���� ����� ��� �� ���������.";
			link.l1.go = "usurersJewel_out";
			link.l2 = "��, �� ��� ��, � �����"+ GetSexPhrase("","�") +" ������� �� ������ ����������� �����. ������ �������������� �� ������?";
			link.l2.go = "usurersJewel_5";
		break;

		case "usurersJewel_out":
			dialog.text = "�-��, ����� ����. ������, � � ��� ������. ����� ���� ��������...";
			link.l1 = "�� �� ��������.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.usurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "usurersJewel_5":
			dialog.text = "���� �� ������� ��������� " + npchar.quest.usurersJewel.type + ", �� � ������ �������. ���� ��������, ��� ����� ������.";
			link.l1 = "��, ��� ������. �� ��� ��, � ����������� �� ������. �������� ����������.";
			link.l1.go = "exit";
			pchar.questTemp.different = "SeekUsurersJewel";
			pchar.questTemp.different.SeekUsurersJewel = true;
			//����� ������
			sld = ItemsFromID("UsurersJew");
			sld.shown = true;
			sld.startLocation = npchar.city + "_ExitTown";
			sld.startLocator = "item" + (rand(14)+1);
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			Log_QuestInfo("������ ��������� � �������� " + sld.startLocator);
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //����������� ���������� �� ���������� 
			sTitle = npchar.city + "UsurersJewel";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SeekUsurersJewel", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sJewType", npchar.quest.usurersJewel.type);
		break;

		case "usurersJewel_R1":
			dialog.text = "���������! ��-��, ��� ��, ��� ����� ���������� " + npchar.quest.usurersJewel.type + "... �� ��� ��, � �������, ����� �������. � ����� ��������� ��� ������� �� ������.";
			link.l1 = "����� ������.";
			link.l1.go = "usurersJewel_R2";
			TakeItemFromCharacter(pchar, "UsurersJew");
		break;
		case "usurersJewel_R2":
			dialog.text = "������� ��� ��� ���. �� ������ � ����� ����� ���������� �� ���, � ������ �������� ���.";
			link.l1 = "�������, ���� ��...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fortune", 25);
			AddMoneyToCharacter(pchar, sti(npchar.quest.usurersJewel.money));
			TakeNItems(pchar, npchar.quest.usurersJewel.jewel, 1);
			Log_Info("�� �������� ������� ������");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			sTitle = npchar.city + "UsurersJewel";
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.usurersJewel");
		break;

        //============== ������� ����� =============== homo
    	
		case "CapBloodUsurer_1":
			dialog.text = "� �� ����� ������� ����� ������������� ����������, ���.";
			link.l1 = "��� �� �����, �� ��� �������.";
			link.l1.go = "CapBloodUsurer_2";
		break;
		
		case "CapBloodUsurer_2":
			dialog.text = "���?! � ��� �� ��������?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "��������. � ������ ��� ����, ������� ���� ������ ����������� ���. ����� ���� �����.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "� ������ ��� ��� ����, ������� ���� ������ ����������� ���. ����� ���� �����. � ������ ��� �� ����.";
    			link.l1.go = "CapBloodUsurer_4";
            }
		break;
		
		
		case "CapBloodUsurer_3":
            AddMoneyToCharacter(pchar, -5000);
            Pchar.questTemp.CapBloodLine.Ogl = true;
            AddQuestRecord("OglQuest", "2");
			dialog.text = "��... ��������� ���, ���.";
			link.l1 = "����� ����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "CapBloodUsurer_4":
			dialog.text = "�� �������� ������ �� ����?";
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = "���������� �����.";
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = "� ���������, ���, �� ����� �������.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_4";
            }
		break;
		
		case "CapBloodUsurer_5":
			dialog.text = "������� ���� ����� � ���� ���� ���� ������� �� ������. ���� � ���, ���... �� ���� �������. �� �������� ������ ������� �������, ������� ��������� �� ��� �������, �, ����������, ������� �� ���� �����. � ��� ��� ���� � ������� 30 000 ��������, �� ����� ����� ��� �...";
			link.l1 = "�� ������, ����� � ����� ����� ��������? ������ �� �������, ��� �� ��� � ������?";
			link.l1.go = "CapBloodUsurer_6";
		break;
		
		case "CapBloodUsurer_6":
			dialog.text = "�� � ������, ������ ���. ������� ��� ����� �� ��������. � �� � �������� ������ �������� 10 ���������, �� ���� - 3000 ��������. ��� �������?";
			link.l1 = "������, �������, � ��� ������.";
			link.l1.go = "CapBloodUsurer_7";
			link.l2 = "�� ���� �� �������������.";
			link.l2.go = "Exit";
			NextDiag.TempNode = "First time";
			PChar.questTemp.CapBloodLine.QuestRaff = false;
		break;
		
		case "CapBloodUsurer_7":
		
            AddQuestRecord("UsurerQuest", "1");
            PChar.questTemp.CapBloodLine.QuestRaff = true;
            NextDiag.CurrentNode = "CapBloodUsurer_8";
			DialogExit();
		break;
		
		case "CapBloodUsurer_8":
			dialog.text = "�� ���, ���� �������?";
			if (sti(pchar.money) >= 27000)
			{
    			link.l1 = "��, ��� ���� ������ �� ������� ���� ������ ���������.";
    			link.l1.go = "exit";
    			AddMoneyToCharacter(pchar, -27000);
                Pchar.quest.QUsurer.over = "yes";
                NextDiag.TempNode = "First time"; // fix ������������ ������ �����
		   		CloseQuestHeader("UsurerQuest");
            }
            else
            {
    			link.l1 = "� ���������, ���, �� ����� �������.";
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_8";
            }
		break;
		//������������
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "�� ��������! �� � ���� ��������� ����, � �� � ���� ������������ �� �������� ���� ���� ��������, ������� ������ ��������� �� ��������� ������, �� ��� ���� � ������� �� ���������, ����� ������� �� ���� ���\n� ��� ��������, �������� ���� ���������� ��������� ����. �������� ��������� � �����������, �������� � �������������, �� �� �������������... �-��... �������� �������������� � �������� ������. � ����� ������� ����� ������ �������� � ����� ����.";
			Link.l1 = "��� �� ������ ����� �������� �� ����, ������ ���� '����' �� ����������� ��� ����������.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			dialog.Text = "������, ��������. ������ ��� �� ���� ������� ���������� ����, ��� ������������. � �� ���������, �� � ���� ���� �������� ���������� �� ���� �����, � �� ����\n� �����, ��� ����� ���� � ���������� " + pchar.questTemp.Slavetrader.iSlaveQuantity + " ����. �� ������� � ����� ��������� �� 250 �������� - ��� �������� ����, �����������. ����� ����� ������ �������� " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + " �������.";
			Link.l1 = "���, ������������� � �� ���������. ����� ���� ������� ���������, �� ������������� �������� �������.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "��, ����������� ������������� ����������. � �� ����"+ GetSexPhrase("��","���") +". ��� ������ ��� ����� ��� ����?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "�-�-��, ���� ��� ����� ���������� �����, ���� ������� ������, ������� �������� ����� ��� ������. � �����������... ��������, � �� ��������� ������� � ����� ��������� - � ���� ������� ����...";
			Link.l1 = "� ����, ��� � ��� '�������' ����... �������, ��� � ����. ����� ��������.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "� ������ � ��� �� �����������, �� ��� �� ������������ ���������. ����� �� '������ �������� �����' �������. ���� �� �������������� ���� � ���� ������ � ������� �������, �������� ������ ������ ��������� ��� ��� �������, ������.";
			Link.l1 = "������ ����. ��� ��, ����� ������� ��������.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // ��� ���� ����� ������ � ��������� ������
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "�� ���, ������� ��� ������ ����������� ������ '������� ������'?";
            if (amount < 0)
			{
				Link.l1 = "���� ���. ������ �����"+ GetSexPhrase("","�") +" ���������, ��� ��� ������ ��� � ����.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "�������. ��� ������ � ���� � ������.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "�������! ��� ���� �� �������... ������ ������� � ���������� ����� �� ������������. � ���� ���� ������ ��������� �� ������� ����, ��� ��� ������� �� �����, � � ����������� ��� ����� �� �������.";
			Link.l1 = "������, � ��� ����� ��� ��� ��������! ��� ������ ������?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "����������, ��������... � ���� �� ����� �� ������. ��������� �� ����, �������, � ����� � ��� ����� ������� ��������, ��� ��� �� ��������� ����������� ����� ������!";
			Link.l1 = "������ ��... �� � ��� ������?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "������? � ������ - ������� ������ ����� ���, � ���� ��� ��� ����� �������� �����. �����, � ���� ������� ��� ��� ��������.";
			Link.l1 = "������������. �� �������...";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//��������� ����
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//�������� ������ �������
			{
				dialog.Text = "������ �����. �� ���� �������� - � ��� �������� �������. � �� ���� ��������� ����, �� � ��� �������� �� ������ ������ ���� ��� �������. ��������� ����� ������, ������������ �������� ����������, �� ������ ����������, � ����� ������ ��� �����������. ��, �������, �� ������� ������. � �� �����������, �� ����� �������� ������.";
				Link.l1 = "�������, ���� ������ �����. �� �������.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "�������-��! � ��� ����. ������ � ���� ����. ��� �� ���������, � ����� ������� ���� ����������. ������� ������� � � ����. ��� ������ ������������� ������� ������ ������� ������ ������� ��-��� ������ ����! � �����, � ���� ��������� ������ ������ �������� � ���������� ���������� �� ����.";
				Link.l1 = "� �"+ GetSexPhrase("���","��") +" ��������.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//����� �����
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "�����������. ��� ���. ���� ����������, �� ������ " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + ", ������ �� ������ ���� �����, � ������ ����������� � ����� " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", ��� ������ " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + ". �� ���� ��� ���������������. ��� ������ ���������� '" + pchar.questTemp.Slavetrader.ShipName + "'. ��� ������ ����� �������, �� ��� �� �� �� �����!";
			link.l1 = "��, � ��� ������ � ������? �� ������ �� ��!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "� ����� �����? " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " �� ����� ������ �����, � ����� �� �����������, ���� �� ��������. �� ������������ ������, ��� ������ ����������� � ������, ����� ��������� ���, � � ��� ������. �� ���� ���������, � ���� �� ����� ��������� �� ����� �������� ����� ����� - �������� ������.";
			Link.l1 = "���! ������������� ������. ��� ������ �������� �� ������?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "���, ���������, ��� ������� �� �� ���. � ����� ����� ��� ��������� � ����������������?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "��-�, ������, � � ��� ������... ��������, � �������� � ����� ���������. �, ���� �� ������ �������������, ������� �� ���������������� � ���, ��� ����� �������. ��� �� ��� ����� ���������, � ���� � ������ ��� ��������. � ���� �� ������� � ���������� ������������ '" + pchar.questTemp.Slavetrader.ShipName + "' �������������� - � ����������, ����� ��� ��������� �� ��������. ������ ��� � ����.";
			Link.l1 = "������ �� ���������� - � �� ��������� ��������. � ��� ������ � ������ ��� ���� �� �����. ����� �������.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//����� ������, �������� ������� ������
		break;
		
		case "Takeslaves_6":
			dialog.Text = "� ������ ����, ��� � ��� ������ ���������� � ��������������� �����, �������� ��� �� ������������� ��������� ���� � ������� ������, ������ �����, ��� �� ���� ���������, ��������� ����. �� 200 �������� �� ������� ����. �� ��� ��� ����� �������� ����� - ������� ������� �����, ���� ��� ������� �������.";
			Link.l1 = "�������. ������� � ���� ������� �� ��������?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "��-��! �� �������� ���, ����� ��� ���� ���� �������� ������, ����� ����������� �� ��� � ����! ������, ����� ��� ���� ����������� ������ ��� ������� �� ����� ���������� ����? ��������� ��������������, ��� � �� ����� ���� ����������.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "�����, �� ������ ���� ������. ���� ��������� - �� ������ ����������� � ������ ����� ������.";
			link.l1 = "�������� ������������. ����� ���� � �������� ���������. �� �������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Dat"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//���������� � �������
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//�������� ��������
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//������
			pchar.questTemp.Slavetrader = "wait1";	//��� ��������
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "�� ���, " + GetFullName(pchar) + ", ��� ������ ��������? ���� �� ������ ������� ����, �� �� ���������.";
			link.l1 = "�� �����, ���� ������... �... ��, ���... �������"+ GetSexPhrase("","�") +" � �������. ��, ������, ��� ���� ������, ��� ��� � ������ �� ���"+ GetSexPhrase("��","��") +". ���� ���� �������� ���� � ��������� - ��������� ��� ��������� �����, ���� �� �������...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "�� ���, " + GetFullName(pchar) + ", ����� ����� ����? ��� ��� ��������, ��� " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " ������� ������.";
			link.l1 = "��, � ��������"+ GetSexPhrase("","�") +" ��� ��� �������! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " ���������� ����� �� ������� ���������������. �������� � ��� ����������� ������ ��������� �� �������� � ���� ������, ��� ��� ����������� � ��� ����������� �����������.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "��, ������, � � ���� ������. �� �������"+ GetSexPhrase("","�") +"? � �����, ������ �������"+ GetSexPhrase("","�") +", ������� ���� ���? �����. ������ ��� ��� �� ����� ��������. �� �������"+ GetSexPhrase("","�") +" �������� ����, � � ����� �� ����� ����� � ����� ���. ����������, � ������ ��� ����, ��� �� ����� �����"+ GetSexPhrase("","�") +" � ������"+ GetSexPhrase("","�") +".";
			link.l1 = "�� ��� ��, ��������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "����, � � ��� �� ������ - "+ GetSexPhrase("��������� �� �����","������� �� �����") +". ����� ������� ��� � �����. �� ����������� ���������� � ������������ ������� - � ��� � ������ ������ �������� ����� �����! ��, � ���������, � ���� ������� ������ ������ �������� ������ ������ - �� ������� � ���� ������ ������ ��� �����. ��������� ����� ��� �������� ����� ��������������. ����, ���� ������� ���������� 320 000 ��������.";
				link.l1 = "���������. ������� ����� � ���� ����, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6_1");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "����, � � ��� �� ������ - "+ GetSexPhrase("��������� �� �����","������� �� �����") +". ����� ������� ��� � �����. �� ����������� ���������� � ������������ ������� - �������� "+ sTemp +" �����. ���� ������� ���������� " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "���������. ������� ����� � ���� ����, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "�� ��� ��, �� � ������ ����� �� ������� ��������. � ���� ������ ������, ��� � ������, � ��� ����� �������. ����, �� �������� "+ sTemp +" �����. ���� ������� ���������� " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "���������. ������� ����� � ���� ����, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "�� ��... ��� ������� ��� �������, �� � ����������� �� �������. �� �������� ����� ���� "+ sTemp +" �����. ��, �� �����, � ������ ������� - �� ��������� �����������, ��� ���� ����-�� �����. ���� ������� ���������� " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "���������. ������� �� ���������, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "��� ������� ������ ������������, ��... ��... ������, � � ���� ������. ��� �� ��� ������"+ GetSexPhrase("","��") +"? "+ sTemp +" �����? � ��� ��������� �����? � ������ �� ������, ��� �� ��� ������"+ GetSexPhrase("","�") +". �� ������"+ GetSexPhrase("","�") +" ��� ���������������, ���, ��� ��� ���� - �������� ������ � ������. �������� � ���� �����, �� ����� ������ ����� � ����� ������� ���.";
				link.l1 = "��������� ����������.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "��� ������� ������ ������������, ��... ��� ����? ��� ��� �����? � ������ �� ������, ��� �� ��� ������"+ GetSexPhrase("","�") +". �� ������"+ GetSexPhrase("","�") +" ��� ���������������, ���, ��� ��� ���� - �������� ������ � ������. �������� � ���� �����, �� ����� ������ ����� � ����� ������� ���.";
			link.l1 = "��������� ����������.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "��� ��� �� ���. � ������ �� �������� ������ ���� �� ���! � �� ���� ����������� �� ����������� - � �������� ���� ��������, �� ����������. � ������ ����������!";
			link.l1 = "���� �� ���� ������ � ����� �������������!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "� ����, �� �����������, " + pchar.name + ". � ����� ����� ���. �������� �� ��� �������� ����� ����� - ��������, � ������� ������ �� ������ �������. � ���� ��� ��� ���������� ���-���.";
			link.l1 = "����� �����������! �������������� � ���� �������� �������� ���������.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "��� �������� ��� ����� ���������... ��, ��� ����� ������, " + pchar.name + ": �� ����� �������� �� ������ ������ � ����� ������� �� ��������?";
			link.l1 = "���, ������ ������ ���������� ��� �� �����������. � ���, ���-�� ������ ���� ����?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "statue1"))
			{
				link.l2 = "�� ������ � ���� ��� ��� ������?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "�����, ������, � �����, � �� ������... �����, �� �������� - ��� �� ��������. ��� ��� ����� �����. �� ��������!";
			link.l1 = "�� �������, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "��, ������! ��� ������ �������� ���������� ����� ���������. ������, ��� ���-���� ���� � ����� ����� ��������... ���������, � ������� �������?";
			link.l1 = "�������, �������.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "statue1", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("�� ������ ������ ���������");
			PlaySound("interface\important_item.wav");
			dialog.text = "���-���... ��� ��������, ��� ���. ����������, " + pchar.name + ", �������� ��� ��� ������. � ����� ��������� �� ��� ��� ����� �������.";
			link.l1 = "��� �����? ��... � ������"+ GetSexPhrase("��","��") +". ���������!";
			link.l1.go = "Buystatue";
			link.l2 = "���, �� ������. �������� ���� ��������� ������ �� � ������, ������� ����� �� ��� ��������. � ���������� � ��������� ���������� ������.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "�����������! � ���, ��� �� ������������. �������� ���� ������. � ��� ��� ����� �����. �� ��������.";
			link.l1 = "�� �������, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "���������, �� ��� ����� ����� ��� ������! � ��������� � ���� �������� - ��� ����� �� �������� - ����� ������������ ������ �� �������� ��� �� ��� � ���� �����. �� �� � ������ ������ ���� � ��������� �������, ���� ������������� ������� �� �� ����� �����\n��� �� �� ������ �� ��� �����, �� � ��������� �����. � ���� ���� ���-���, ��� ����� ��� ��������������. ���, ����������. ������������ ���������� �������! ����� �� ������! ������ �� ������� �� �������. �� ������ ���������� ����� ���������� ��������. �������!\n��� ����� ����� ������ ��� �����, �� ��� �������� ��������, ��� �� ���������, ���� �������� ������ �� ��������. ��������� ��� ��� ������� � ����� �� ������. ��� �� ������������ ����� �� �������. �� ����"+ GetSexPhrase("�","���") +", �� ������� �������� ���� ���. � ��� ��� �������. ��, ��� ���, ��������?";
			link.l1 = "���... �������, � ������"+ GetSexPhrase("��","��") +". ������� ��� ��� ������, � �������� ������ ����.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "���. ������ ����� ��� ���� ������� ��������, ������ ��� ������������ ������. � ������� �� ����.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "�����������! � ���, ��� �� ������������. ��� �������������� ������� ������ ����. ��������. � ��� ��� ����� �����. �� ��������.";
			link.l1 = "�� �������, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "suit_3", 1);
			Log_Info("�� �������� ���������� ������");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "����, ����� ����... �� ��� ��, �������� �� �����. � �� ������� ��� - ������ ������������� ����� ��� ������. ��� ��� ����� �����. �� ��������.";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
			TakeNItems(pchar, "statue1", 1);
			Log_Info("�� �������� ������ ���������");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "�� �������, " + pchar.name + ". ������� ����, ���� �� ������ ���������� � ��� ���������� ����� ������.";
			link.l1 = "�������, �����"+ GetSexPhrase("","�") +". ��� ����� � ���� � ����"+ GetSexPhrase("��","���") +".";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "�������! ������ �� ��������. �� ������� ��������� �������?";
			link.l1 = "��... � ��� ��� ��? �������� �����, � ������ ���� - �����.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "��� ������� �������� ��������������� ������ ����. �� ������� ��������� ����� �������� ����� ����� �� ��� ������� ������ �����! ������� ������ ������ ���, ������ ������� �������� � ������ ��������� ����������� ��������.";
			link.l1 = "���������. �����������.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "�� ��� �� ������ ������� - ��� ����������� ������� �������� � �������! ���������. ��������� ������ � ������. �� ��� �������... ����� ��, ��� � ����� ��� ����������� �� �������, �������� ��� ����������� ������������, ����� ���� �������� � ���������\n�� �, �������, �� �������� � ���� ������������ ����������, �� ������� �������� �� ���� ������ ��������� ������, � �������� ���. �� ������� ���� � ������� �� 300 �������� - � ������, ��� ����� ������� ����.";
			link.l1 = "������ ����. ���� ���� �� �������. ����� ���� � �������� ���������.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "������, � �� ��� �� ��������. � �� ����� �������� ������� � �����, ������� �������� ��, ������ ������. ��� �� ���������.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "����, ����� ����... �� ���� � �� ��� ������� � ����� ������������ ������... � �����, ��� ����, ��� ����� ����� ���� �������������� ������������ �� �����. �� ��������.";
			link.l1 = "����� �������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "��-��! �� �� �� ������ ����������� ���������� � ��������� ��������, �� ��� � �������� ����� ������ ����������� ���������� - "+ sTemp +" �����. �� "+ sNum +" ����� ���� �� �� ������ � �������. � ������� �� ��� �� 100 �������� �� �������. �������, � ������� �� �� ����������. ���� ������� ���������� 330 000 �������� �� �������� ������ �����, � " + FindRussianMoneyString(iSlaveMoneyH) + " �� ���������� �����, ��� �������.";
				link.l1 = "��-��-��, � ��� �� ���������! ������"+ GetSexPhrase("��","��") +", ���� ��-������, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "�� ����������� ��������� ��������� ������ � �������� "+ sTemp +" �����. ���� ������� ���������� " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "���������. ������� ����� � ���� ����, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "�� ��������� ������� �������, � ���� ������ ������, ��� � ������, � ��� ����� �������. ����, �� �������� "+ sTemp +" �����. ���� ������� ���������� " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "���������. ������� ����� � ���� ����, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "�����? ��... �� � ��� �� ��� ��������? "+ sTemp +" �����? � ��� ��������� �����? � ������ �� ��������, ��� �� ��� �������. �� ������� ��� ���������������, ���, ��� ��� ���� - �������� ������ � ������. ���������� � ���� �����, �� ����� ������ ����� � ���� ������� ���.";
				link.l1 = "��������� ����������.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "�����? � ��� ����? ��� ��� �����? � ������ �� ��������, ��� �� ��� �������. �� ������� ��� ���������������, ���, ��� ��� ���� - �������� ������ � ������. ���������� � ���� �����, �� ����� ������ ����� � ����� ������� ���.";
			link.l1 = "��������� ����������.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "� ������ ������� ����, " + pchar.name + ". ����� �������. ��������� ����� �����, � ���������� � ����� ������� ��������� �������� ��� ��� ����� ������.";
			link.l1 = "� ���� ���"+ GetSexPhrase("","�") +" ������ ��������������, " + npchar.name + ". ����� ����� ����������� ��������.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "�� ����� ������� ���������, " + pchar.name + ". ��� ��� ��� ��������� ������ ��������� � �� ����� ������������ ������, ��-��. �� ������ ��������� ��� ���������?";
			link.l1 = "��, � ��� ����������� ������.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "�� ���� ��� ��� ��������� ������. ������� � " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " ����� �� ����� ����� '" + pchar.questTemp.Slavetrader.ShipName + "' ��� ������ " + NationNameGenitive(sti(npchar.nation)) + ". �� ���� �����, ��� ������ ������� ���������������, ��� ��������� ������� ������ '������� ������', �� ����� ���� ����� �����\n������� ������ - ������������ �������� ��������, ������� - ������. � �����, ���������� �����. ������ ���� - ��� ������: ������������ �����, ����� - ������� � �������� ���. ������ - �������� ����� �����, �� 200 �������� �� ������� ������. ���, ��� ������.";
			link.l1 = "��... �� ������, ��� � ������� ���. �� ����������� ��� ������� �� ������� ����� �����������������!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "� ���-�� �� ������ ����� ���, " + pchar.name + ". ����� �������, ����� ����� ��� �����? ��� ��� ��� ��� ����� �������������� ��������?";
			link.l1 = "���? �� ���-�� ���������, � ������ ��� ��������������! ���� ������ ��������� �������...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "��, �����. ��������� � " + NationNameAblative(sti(npchar.nation)) + " � �� �������"+ GetSexPhrase("","�") +".";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "��� ���? �� ���, ������? �� ��� ����� ����, ����� ������������. � �������� ��� ����, ��� ����� ������ � �������!";
			link.l1 = "��������� ����������, " + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "��� ��� �������? ��� ��� ���� ����������� �������������� ������� �����? ������, ��� � ����, � �������, ��� �� ��� ����� �� ��������. ���� ����, �������� �������������� ����������� ������ ������ ��� ����������������� �������, ���� ��, �������, �� ��������� �������� ���� ��� �� �������\n�� ������� ��������� ��� ���������. ����� � ���� - ����� ����� � ����� ��������� �� ��������, ��� ��� ������� � ��� ������ �������. �� ������ ���������� � ��������?";
			link.l1 = "��, " + npchar.name + ", ��������� ����������.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "�������. � �� �� ������� �� ���������� � ������ ������ �����������. ����� ���, " + pchar.name + ".";
			link.l1 = "�������! �� �������.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//���������� � �������
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//�������� ��������
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//������
			pchar.questTemp.Slavetrader = "wait1";	//��������
		break;
			
		case "Pinas_lose":
		dialog.text = "�� ���, " + GetFullName(pchar) + ", ��� ������ ��������? ���� �� ������ ������� ����, �� �� ���������.";
			link.l1 = "�� �����, ���� ������... �... ��, ���... �������"+ GetSexPhrase("","�") +". ��������"+ GetSexPhrase("��","���") +" � �������, � ����� ���"+ GetSexPhrase("��","��") +" � ���� - ��� ������ �� ���"+ GetSexPhrase("��","��") +".";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" + pchar.name + ", ����� ���, �����������. ��� �� ��� ����! ������, ��� �������� ������� ������... ��� �������������! ���� ��������� ���� �� ���� ���������� �����!";
			link.l1 = "�����, ����, ��� �� �����. �� ���� ������� ������� ������ ����� ������� �����������, ��� ���� ���� ��������. ���� �� �� ��� ��� �����, � �� ��� ���������"+ GetSexPhrase("","�") +" ����... �� �� �� �������, ������ �������� �����, ��� � ���� ����� �� ������� ��� ��������!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "������ ���� ������������ �� �������� ��������, ����� � �� ��� ���� �� ����... " + pchar.name + ", ������ �� ����� ��� ������ � �����������. �� � ���� ��� � ����������� ��������� - ��� ����� ���� �� ���� ������� �����������\n��� ������� ������, ��� ��� ��������� �������������� - ����� ����� - ������ ��������� � ���� � ������ �������-�����������. ���� ��� ������� � ���� � ���� - ��� �����! � ���, ������, � ������ �������.";
			link.l1 = "��� ��� ��� ���� � ���� ���� ������� �������!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //����� �������, ���� ���������� ������
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Tortuga";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//��� ����������
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "�������� �����������. � ��� ���� ��� ����. ����� ��������� ����������� '" + pchar.questTemp.Slavetraderbrig.ShipName + "'. ��� ������������, ��� � ����. ������ ����� �������-�����������, � ��� ���������� �� ������� " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". �� ������ ����������� ��, ����� �� ������� � ����� ���� ���������.";
			link.l1 = "�������� ��� �� ��������. �� ��� ��, ��������, � �� ����, � �� ����, � ���������, ��� � �� ������. � ����� ������� - �� ��� ��������� ��� ��������. � �� �������, ��� � ��� ��� ��� ��� �������!";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//���������� � �������
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//�������� ����������
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//������
			pchar.questTemp.Slavetrader = "wait1";	//��� ���� ��������, ������
		break;
		
		case "Slaveshore_8":
			dialog.text = "������� - ������� �����! � ���� ������ � ����� ������������, ������ ���� �� ��������� ��� ���... ��� ����... " + pchar.name + ", �������, � ��� ��������...";
			link.l1 = "��� ��� �����?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "���������... � � ��� ��������, �� ���, " + pchar.name + ". �� ��� ��, ������ ������� ��� �� � ���� ����� �� �����. ���� ��� �� �������� ���������� �� ���������, � ���� �������� ������. �� � ��� �� ������� ����� ���������� - ������� ����� ��������� � ����� ������. ��������.";
			link.l1 = "��������, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "����. � ��� ���� ����������. �� ��� ��, ������ ������� ��� �� � ���� ����� �� ����� - ��� ������ �����������. ��������.";
			link.l1 = "��������, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "�����������! � �� ������ �� ���������� � ���, " + pchar.name + ". ����������, ��������� ������ ���, ����� � ���� ���� �� �� �����.";
			link.l1 = "�������.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "�������... ������ ����� ���� ���������. �������-���������� �� � ��� �� ������, � � �������� �������� ��� ������� � ��� ������, ���� �������� ����������� �������, ����� � ���.";
			link.l1 = "��� ��� �������, ������, �� �� �� ��������, ��� ������ �������������� ��� ��������� � ������������ ���� ��-�� ����� ������������� ��������?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "����������, " + pchar.name + ". ����� ����, � ������ ��� ����� ������. � ������ ����������� �� ����������� ������ ��������������. �� ����� ��� ����� � ��� ��������� - � ����� �������� ����� - ���������� ����������� � ���������� ����� ��������. ����� ����, �������� ������ �������� ����������� ������ � ���� ����������...";
			link.l1 = "�� ������ �������, ��� �� �������� ��������� ��� ������?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "�� ����������, " + pchar.name + ". � ���� ������ � ������ �������� � ��������, ������� ��������� ��� ������ ��������� ����� ����.";
			link.l1 = "����� � ��� ����������� ������.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "����� ���� ����� � ������ ��������� ����� ��� � ����������� ������ ������� �����. ������� ������� � ����� ���� ���� �� �� ������, � ���� �� ����� ��� ������������ �������, �� ������ ������� �� ����� ��� ���� - ������� � ���������������, � ������� ���� ������� ������ ������ � ��������� �������. ����� ��� ������, � ���������� ��������� �� ��������� �����\n�����, ���� ���� ��������, �� ��� ������ �������. ��� ������� �� ��������, ������� ������� ������ � ���������������, � ��� ��������� � ��� �����. � ��� � �������� �������� ������� ���� �� ������\n�� ������������ ��������� �� ������, �� ��������� �� ��������� � �� �������. ������, ��� ������� ������ ������� �������� �� ��������� ���� �����, � ������ � ��� ����. �� �� - "+ GetSexPhrase("������� ������� � ��������","������� ������� � ��������") +" - ������ ���������� � ���� ������ �����������\n� �������������� ��� ������������� ����� - ������� ��� ���������� ���� ������, � ����� ������� �� ���������� �� ������ �����.";
			link.l1 = "��... �����. �����, �������, ���������� � ������. �������, �� ��� �� �����. ������ � ����: ���������� ���� ������ - �� ��� ����� �������!";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "������ ���� �������, " + pchar.name + ", ��� ��������� - ������. ��, � ��� ��� �������� ����� ����� - � ��� ������� ���� ����, ������� �������� �������� ������������� ������� ����� �������. �� �������.";
			link.l1 = "�� �������, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			pchar.GenQuestRandItem.Shore18 = true;
			pchar.GenQuestRandItem.Shore18.randitem1 = "sculMa1";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "��� � ��, " + pchar.name + ". ������������, ��, ��� ������, �������. ������, ��� ������� � ���� �������, � �� ����� ������� ������ ��� � ���� ���, ������� �������� �� ���������� ������ ����� �����������. �����, ��� ��� ����� �������. ������ �� ��, ��� �������� ����� '�������������'?";
			link.l1 = "��... ���, " + npchar.name + ", � �� ����, ��� ��� �����. ��, ���� �� �������� - ������ � ����, ����� ���-�� � ����-�� ��������. � ����"+ GetSexPhrase("","�") +"?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "��, �����, ���� �������. � ���� �� ����� �� ����? ����������!";
			link.l1 = "���������� ������, � ��� �����, �������� ������, ������� �������� ��������. ��������� ����������.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "�� ����� ������ � ������, " + pchar.name + ". ������ ��������, � ��������� - �������. ������������� - ��� ������������ ������ ������ ����������� �������� ��� ������������ ������-��������� ���������� - ������ �����, ��� �������. ����������� ���������� �������� �� ��������� � ��������� ��������� �����. ��� ��������� �������� �����������?";
			link.l1 = "������ �� � ���?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "������������� ��������� ������ �������� ��������� ���������. � ��� ���, ��������� �������� ����� � ��� ��������� ������ �����, ���������� �������� �������� � ��� �� ������������ ����� ������ ������ �� ������ �����: ������ ����, ������ ������ � ���� ��������. ������ � ����\n������ ������������ ������ �������, ��������, ���, �������� ������������ � ������� �����. ���� ������� �� ����� ������������ - � ��� ���� ����� � ������ - ������� �������� � ����� ����� ���������������� �������� ��������� ����� �� �����, ��� ����, ����� ���������� ���� � '��������� ����������� �����'\n���� ���������, ��� ����� � ���� ��������� ��� ������� ��� ������� �� ������������. ��� ��� ���� ���������� ����������� ������ �������� �� ��������� ��������� ��������� � �������� �������� ������.";
			link.l1 = "���, �� ��� �� ����... � ������� �� ��������������, ����� �� ������ � �������? ��� ��� �� ��������?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "��������, ��������, �� ������� ���������, ����� ���� ����� ������ � �������� �������� ������ �����, ���� ��� ������������. �������, �������� ������� ���� ����������� � ��������� ������ ������ - ����� ��� �������, ��������, ��� �������. � ������������� ��� � ��������, � ��� �����, ���������, ����� ��� �� ������� - ��� � ����-�� �� ������ ��������\n��, � ������ �������� ��������������� � ����� ������.";
			link.l1 = "� ��� �������� ����� ������� �����! ������ ���, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "�� ���� " + sTemp + " ������ ������� ������ ��� ��������� " + pchar.questTemp.Slavetrader.ShipName + ". �� ��������� �������� ������ ����� - ����� 3 000 ������� - ��������, ������������ �� ��������� ��������� ������� �������, ����������� �������� ������� �������������\n������ ���� � �������� - �������� ��������� ���� ����� ��������� � ������� �����. ���� ������ - ��������� ���� ������ ������ � ������. ������ �� ����� - ��� ������, �� 200 �������� �� �������.";
			link.l1 = "���! ������ ���������. � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "������, ���-�� �� �������� ��� ��� ���� �������������, ������� �� ��� �������. �������, � �� ����� ���������� ���� �����.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "�� ��� ��, ����� � ����� ��� �����. ������ � ����: ���� �������� ��������� ����� ������� ������� �����. ��� � ��� ����� ��������, ��� ��� �������������, ��� �������. � �� ������� ������� - ��� ����������� ���� ����������-��������, ����� ��������� " + sTemp + " �� ��������. ������������ �� �������� ���, �������� � ��� - ���� ������ �� ����� �������� �� ������ ��������\n��! ���� �� �����! ����� ����, �� ������� ����� ����� ������ ��������� ���������� - ����������� ������ ����� �������������� ����� ������� � ���������� ������. ���� ���������� �� ������� ���-������ ��������� - ����������� ���������� � ��������� ��� - � ����� ������� �� ������ ������ �������.";
			link.l1 = "� ��� �����"+ GetSexPhrase("","�") +". ���������� ����������.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 21, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "��, " + pchar.name + ", ��� ���� ��� ��������� �������... ������� � ������� ���� ��� - ��� ����� ����� ��� � ��� ����� �� ���� �� ����������... ��� ��������� - � �� ����. �� ��� ��, ����� ���������. ����� ��������� ������� � ������������� �� ��� ��������� ������, ��� ��� ��������� �����������. � ����������� �������, �, ��������, ��� �������� �������� ���� �����. �� � ��� �� ���� - ������ ���� ����� ���������. ��-�... ��������, " + pchar.name + ".";
			link.l1 = "��� ����� ����, " + npchar.name + ", ��� ��� ��� ����������. ������� �����. �����, ��� ��� ����������. �� ��������.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "���, ������ � ���� ��������... �� ��� � ��� ���������, �� ���... � � ���� ����� ������? ���-�� �� ���?";
				link.l1 = "� � ����, ���������, ��� ��� ������ ��� ������ �� ������... ��, ��� ����� ������� ������... ������!! ��� ��� �������� �������! � �� ���� �� ���� �� ������������! ��� �� �����, � �������"+ GetSexPhrase("��","���") +" ��� ���������. � ���� � ������ ��������� "+ sTemp +" �����, � � �����"+ GetSexPhrase("","�") +" ��� �� ��������. �������� ������ �������, �� ������ ��� " + FindRussianMoneyString(iSlaveMoney) + ". � �� ������ �� ��� � ����������� �� �������������.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "����� ������? � ��� ����? ��� ������ ���� ���� �� ������ ���� ����� �����! ���� ������, ������ ���� ������� � ���������! ��� �� ����-����, � �� ��� � ����� �� ������... �� ���� ���� ��������� ��������\n��, ��� ���... �������, � ������� ������� ������ ��������� � ����� �� �������, �� ������ ���, ��� �� ���� ����� �������� ���� ���� " + NationNameGenitive(sti(npchar.nation)) + "! ���������� � ���� ���� �����!";
				link.l1 = "��-�...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "�� �� ���! �������, � �� ���� �����. ������ ��� ����� ������ ������� ������, �� ����� �� �������� �������! ������, � ��������� ������ ���-�� ����������... �� �� �� ����������!\n������ ����� � ����������� ����� ����������� �������� � ��������� ��������, ��� �������, �� ���� ���� �������������� ������������� ���� - � ���� ������ ��� ������ ����� ������� �����. �������� ��������... ��, �� � ���� ��� ������. �� ������ �� ����������, " + pchar.name + ", ���� ����. �� ��������� ��� �����, � ��� �������� - �������� ��� ����\n����� ����� ���� ���� � ���� ����� ��� �����, � � ��������� ����������� � ����. ������ �� �����������. � ��� ����� �����������, � ����� ���� ��� ��� ����������, ��� � ���� ���� �� ������ ������ - ��� ��� �������.";
			link.l1 = "��... � �����������"+ GetSexPhrase("","�") +" �������� ������ ������. ����� �� ��, ����� ��� ��� �������� ���������! �, �����... ����� � ���� ���������. �� ������ � ����: ������ ���������� ���� ������ - � ������ �������!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "������, ���, " + npchar.name + ", �������� �� ���� ��������. �� ��� �� ��������������. �� ���� �� �������������, ����� ��� ��� �������� ���������. � ������� ���� ����� ���� � �������� �� ��� ������ ��������������.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "�� ���, ������, ��� �� ����������! ������, ���� ���������� " + npchar.name + " ��� ��� ��� ������ �������, ��� ��� ����������, � ��� ������ ���� ��������� ��������, �� ������ ����������� ����� ���� � ����� ���� ��������������. ��� ���� �� ����� ������, ��� ������� �� ��� ������ �������� �� ����\n��, ��� ���... �������, � ������� ������� ������ ��������� � ����� �� �������, �� ������ ���, ��� �� ���� ����� �������� ���� ���� " + NationNameGenitive(sti(npchar.nation)) + "! ���������� � ���� ���� �����!";
			link.l1 = "�� ����� ����, ������ �������� �����. ���� ���� � ������� ������. ��������� ����������!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "������� �� ���������, " + pchar.name + ". ������, ��� ����� � ������ ����, ��� ��� ���� ������ ����� �� � ����\n�������� ��� ��� � �������� ������. ����� ���������� ��������. ������ ������ � ����� ��� ������������� �������, � ���� �������� ���� � �������� ����������� ���������� ������. �� ��������� �������� ����� ���� ����.\n�� �������� �������� ��� ��������� ��������, ������� ����� �� ����������� �������... ���� �����, �������. ������ ��� ��� ����� ������ ��� �� ��� ����������.";
			link.l1 = "����� ����� ���� ����, " + npchar.name + ". ����� ����� ���� ����...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "��� � � ������, " + pchar.name + ", � ����� � ���� ������������. ���� �������, �������� �������, � �� � ���� ����. �� ������� ������ ������������� ��� ����� ���������� " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". ����� ���, �������� ���� ������.";
			link.l1 = "�����������, " + npchar.name + ". ������� ����� ���� � ���������, ��������� ������� ���� �����...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "�� ������ ������ ������ ����� �����, " + pchar.name + ". � ��� �� ���� �� ��� ��� ������ ���������� � ����. ��� ����� � ������. ��������� ��������� ���� � ������ - ��� ��������� ������ � ����� ���������� �������\n������ �� ��������� ����������. �����������, ��� � ��� ��� ����, � �� �, ��� ������� ������������, ��� ���� �������.";
			link.l1 = "���... ��������, ����������.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "indian15"))
			{
				dialog.text = "���! ������������! ����������� ������ ��������! ��� ������ ��������. � ����� ����� ����� �� � ����� ���������. ��������� ��� �� ��� 30 000, ��� ����� �� ��������� �������, � ���� ����� ���.";
				link.l1 = "� ������ ������.";
				link.l1.go = "BG_money";
				link.l2 = "� ����� ���� ������� �� ��������� �������.";
				link.l2.go = "BG_change";
				link.l3 = "� ������� ���� �������� ����.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "���-���... � ���������, ��� ������ ������, ��� ����� �� ���� ��������������.";
				link.l1 = "��, ��� ��� ���, ��� �������.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "������������! ��� ���� 30 000, � ��� ���������� ������ ������ ���.";
			link.l1 = "���������. ��, ���� ��� ���, ��� ��� ��������������...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("�� ������ ����������� ������");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
		break;
			
		case "BG_change":
			dialog.text = "������������! ��� ���� ���������, � ��� ���������� ������ ������ ���.";
			link.l1 = "���������. ��, ���� ��� ���, ��� ��� ��������������...";
			link.l1.go = "BG_PF";
			Log_Info("�� ������ ����������� ������");
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian15", 1);
			TakeNItems(pchar, "indian19", 1);
		break;
			
		case "BG_no":
			dialog.text = "��, ��� ������. ���� ����, ����� ����...";
			link.l1 = "��, ���� ��� ���, ��� ��� ��������������...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "������! ����� ����� ��� �����...";
			link.l1 = "����������, ��������, ���������.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "indian2"))
			{
				dialog.text = "���! � �� ����� �� �������! ���� ���������� ��� ��� ������� ���������� �����. ����� �������� �������, ����� � ���... � ����� ��������� �� ��� 20 000 ��������, ���� �������� �� ������ ���������.";
				link.l1 = "� ������ ������.";
				link.l1.go = "PF_money";
				link.l2 = "� ����� ���� ������� �� ������ ���������.";
				link.l2.go = "PF_change";
				link.l3 = "� ������� ���� �������� ����.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "���, ��... ���-���� ������ ������� ��� � ��� ���.";
				link.l1 = "�� � �����! �� ��� � ���� ���.";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "������������! ��� ���� 20 000, � ��� ������� ������ ���.";
			link.l1 = "���������. ���� ���� ������ ������ ��������.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("�� ������ �������� �������");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
		break;
			
		case "PF_change":
			dialog.text = "������������! ��� ��� ������, � ��� ������� ������ ���.";
			link.l1 = "���������. ���� ���� ������ ������ ��������.";
			link.l1.go = "FindRat_3";
			Log_Info("�� ������ �������� �������");
			Log_Info("�� �������� ������ ���������");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "indian2", 1);
			TakeNItems(pchar, "indian6", 1);
		break;
			
		case "PF_no":
			dialog.text = "��, ��� ������. ���� ����, ����� ����...";
			link.l1 = "��� ��������� ��� ����� ����"+ GetSexPhrase("��","�") +", ��������.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "�� ��� ��... �������� ���� ������... ��������, �������� �������, �� ��������� ������ ����. � ��� ������ ��������������, " + pchar.name + ". ����� ���, ��������, � ���� �� ���� �� ������ ������.";
			link.l1 = "�������"+ GetSexPhrase("","�") +", �� �����. �� �� ��������� ��������������� ��� �������...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "� ������ ���������� ��������. � ������ ������, ��� �� ��������� ����� ����������� �������������, � ������, ��� � ��� ��������� �������, � ����� ��� ��������� ��� ��������� ���������.";
			link.l1 = "���! ����������! ������ �����������. ��� ��������� ������ � ������?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "�� ���� ��� � ���� ����� ��� ��� ���� �������, �� ������� ��������� � �����. �� ��������? � ������ ������� �� ���������� ����� ���������... ����� ������ �������.";
			link.l1 = "������� ����� � ����.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "��� ���� �������� ������� � ��������� ���������, � ������� ��, ����� ������, ���� ����� ���������... ����, ��� ��� ��������, � ��������� �� ������ �������� �������� - �������������. ����� ��� ��������, ��� � ������� ��� ���������� ��������� �������, �����, ��� ��\n������� ���� �� ���� �����, �� ���������� ���������� ��� �������, ������ ���� - �������� ����� � ������ ��������������, ��������� ���� � ���� ���������� ��� � ���������� �������� ������. ����������� �� ������ - �� �������� ������� ���� ������ ������� � ���������, ��... ��������� �� ������\n��� � ������� ������ ������� ������������� ��������, � ����� ������ �������������� ����������� ������ � �������� ������ � ���� ����. ��� �� ���������, ������������� �� ����� �������� �������������. ����� ����, � �� ���� ���� � �������� ��������, ����, ��� ��� ����� ���� � ����������� �� ����������. � �������� �� ����� ������� ��������� �� ��������, �� ���� ��������� �������\n� ����� ��� ����� �������� ���� �����. ��� �����, ��� ������������� ����� �������� ��������� ��������������� � ���.";
			link.l1 = "��... ����� ������� ������� ��������� �� ���-���! �������� ��� ����� ��������� ���������� � ���, �� �, �������, ������ �������� �� ������.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "������ �������������� �� ������������. � ����� ������� ��� �� ��� �����������, � �� ������ ��������. � �� ������� ������ ����� �� ����� ��������� ���������. ������ � ���. ��� ����� ����� ������� �������\n�������, ����� ������� ����� - ��� �� �����, ��� � �� ��� ������� - �� ������ ���� ������ �� ����� �� ������ ���������� � �������. ��� ������� �������� � ����� ������, ��� ��� ������� ������ � ������. �������, ��� ����� ������ ������ ������ ������.";
			link.l1 = "�� ��� ��, ���������� ����������.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "����� ��� �����. � ������ ���������: ������� ������� ������ ������� �����, � ����������� �������� ��������� �����������. ������ ��� ������, ������� ��������� �� ����� ��������.";
			link.l1 = "� �� ����� ������� ������... �� � ����� � �������� ���� �����. �� ��������, � ������ ������� - � ����� ��� ���� � �����������.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "�����������! ����� ������ ������� ���� ������ �������. ����� �� ����� ������ ��� ������������! ������� ���, " + pchar.name + ", �� ������ ����������� �������.";
			link.l1 = "�������, " + npchar.name + ", �� ������� ������ ���� ��������. ��� ������ ������?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "��, �������. �� ��� ���������� ������ � ����������� ��������������� �������. � ����� ��� ������������ �������� ���� ��������� - ��������� ������. �������, �� � �����, ��� ��� �� ������� ����������?";
			link.l1 = "�� ��, ����� �������! ��, � ����, ��� '������� ���', ���������� ������. ����� ������ ���� ��� ������.";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "����� ����, � ������� ��� 100 000 �������� ������ � 50 000 �������� �� �������� �������� ��������.";
			link.l1 = "�������, " + npchar.name + ". � ��������� ��� ��������� - � ���� ������� ��������.";
			link.l1.go = "Wincorvette_3";
			Log_Info("�� �������� ���� ������");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "indian18", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "��, � ��� ������, ����� �����, � ��� ��� � ����. ��������� ����� ���������� ����, � ��� ����������� ������ ���������� �������. �����, ���������� � ���� ������ �������� � �������������, ��� �������. ���� ���� �������, �� � ���� ������ ��������.";
			link.l1 = "������, " + npchar.name + ". ������� �� ���������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "����, ����� ����... ��� ��, �� ��������������� ������: �� �� ����"+ GetSexPhrase("��","��") +", ���� �� ������� ������� ����� ����������. ������, � ��� ����� ��� �������\n�� � ��� � ��� ����� �����. ��������� ����� ���������� ����, � ��� ����������� ������ ���������� �������. �����, ���������� � ���� ������ �������� � �������������, ��� �������. ���� ���� �������, �� � ���� ������ ��������.";
			link.l1 = "������, " + npchar.name + ". ������� �� ���������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "�� ����� �������, " + pchar.name + "! � ��� ���� ����� �����������, � ��������� ������� �� ���� ������ ��������\n��-�, ���������! ������ �� ���� ��� ����� ���� ����� ������ ����� ���������, �� � �������������� ����� ���������������. ����� ����������� �������� �� �������� �������, ��� ������.";
			link.l1 = "��� ��� ����! ������ ��� �����������, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "� ������� ���������� ������ � ������ �� ����� �����, ������� ��������, ��������� ������������ �������, ����� ����, ���� ������� �� ������ � ������������ ��������� �������� � '������ �������� ������'. � ������ ������ � ������, �� �������� ������� �����, ��������� �� ������ ���� ����� �����.";
			link.l1 = "�������� �, ��� ���� ������ �� ������, �� ������, ��� � ������ ������.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "�� ��� ��������� ���������, " + pchar.name + ". ������ ��� � � ���� ��� ��������. ��� � ������ ���. �� �����, ��� ���-���� �� ���� ������ ������� ������ �������� ����� ��������� ��������\n�� ����, ����������, ���������� �� ��� ����?";
			link.l1 = "������ �������, " + npchar.name + ", � ��������� ��������"+ GetSexPhrase("","�") +". �� �����"+ GetSexPhrase("","�") +" �, ��� ���� ������������ �����... ���������. ������ �������. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "������ ���, " + npchar.name + ", ��� ��� �� � ����� ������ �� �����. ���� ������� ���� ��������. � ����� ��������� ������ ��� �������� ���� ������ �� �������. ���� ��� ����� ��� ���� - ��������� ������ �����.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "�� ������ � �� ��� �����. �� ������... ���� ������, ��� � ������ ����� ���������? �����. �� ������ - ��� ������, ���� ������ ������� �����������. ��������, " + pchar.name + ". �� �����, ��� � ���� ������ ������������ ������ ��������. � ������� - �� ����������� ������� ����, ������� ����� ���������� ���� ����� �������� �� �������� ������.";
			link.l1 = "���� ����� �� �����������. �� ������� �� ������� ��������� '������� ����� ��� �����'? ����� �������, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "� �� ����������, ��� ������ ������ ����� �����. ������� ������������: ���� ������ � ��� ����� ��������, �� ������ ��� ������ ����� ��� �������\n� ������� ������ � ������ ������ ��������� ���������� ��� �������� ������� - �������� �������� � ������ � ����. ��� ����� ����� ���������� �� ���� ��������, ������ ��� ���������� � ������...";
			link.l1 = "�������. ��� �� ������� ����� �������� ������ �������� ��������. ������� � ���� �������?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "�������. ������ ���, �� ������. ����� ����� ���� ����� ���������� �� ��������� �������� ����. ��� ��� ��� ������� ������������.";
			link.l1 = "����� �� ����� �������. � �����������!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "���� �������! " + pchar.name + ", � ��� � ���� ������� �� ���� ������������� � �����������. �� ��� �� ���� ��������� ��� � ����������� � ������� ��������� ���. � ����������� �� ���, � �� ���� ������������ ��������\n� �, � ��, ��� ������� � ��� ����������� ���� � ��������, � ����������� - ��� ��������� ����������, ������� � ��� ������ �����������. ��� ����������� ����, ��� ���� ����� ������ ������, ������ ���� ���������� ��� � ������� � �����������\n� ��������� ������ �� ������ ����� � ����� ����������� ���� � ��������� ���. ����� ��� �� ��������� �� ��� ��������������, � ������ ������� � ��������.";
			link.l1 = "������ �� ����������, " + npchar.name + ", � �������, ��� ����� ������. �� �������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//���������� � �������
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//�������� �������� ��������
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//������
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //�������������� ���� ����
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "��-�, ������ ���������� ����� ������ � ������������, ��� �������, �����������?";
				link.l1 = "� ���� � ������ ��������� " + sTemp + " �����.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "���-���... �� ���, ������, ��� � ��� �������? �� ������ ���� �������� ��� �� ������ ���� ����� �����, � � ��� �� ������-�� ����� " + sTemp + ". ��� ��� ����������?";
				link.l1 = "��... �� ��� ��������� ������ � ������ ���� �� ������...";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "���-���... �� ������ ���� ������? �� ���, ������, ��� � ��� �������? ��� ��� ����? ��� ���, � ��� ���������?!";
			link.l1 = "��... ��� ����� ���� �����...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "�����. �� ����� ������� ����������. � ��� ��� ������ �� ��, ����� �� ��������� ��� �������� ������ �������� �� ������ ���� ����� �����. � ��������� ������ - ������� �� ����!";
			link.l1 = "������, ������, �� ����������, ����� ��� ���� ���� ����� �����!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "�����������! �� ��� ������, ������� ���������� � ���� ����������. � ������ � ������ ���� �������.";
			link.l1 = "� ���� ����� �����"+ GetSexPhrase("��","���") +"... �� ��� ������ ���� �����"+ GetSexPhrase("��","���") +", ����� ������ ������ �� �����.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "��� ��, � ����� ����� � ����� ���. �������� �� ����������, �� �������� ���������� � ���� ��������.";
			link.l1 = "��, � ������ � ���� �������� ������ �� �����.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "��, ����������. � ������� ����� ���������, �� ������������, � �� �������� ���� ������. ���, ��� � ������� ���. ������� ���������: �� �������� " + sTemp + " �����. ��������������, ������������� ��� ����� ���������� " + FindRussianMoneyString(iSlaveMoney) + ". ����� ������ ��������� �� ��� �� ��������.";
			link.l1 = "������, " + npchar.name + ", ������������. ����� ���� ����� ������. �� ��������...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + ", ����� ���, �� ���� ����������. �� �� ��������, � ����� ���������� �� ����� ���� ������ � ���������. � ������ ��� �������� ������ - �� �� ��������, � ������ ��� ���������� ������� - ��� � ��� ����. � ������������� ���� ������� � �������� ���� ������� ���� � ����� ������� ��� ����� ������� �������. �� ������ ������������, ��� � ���� ��� �� ������� �����?";
			link.l1 = "��... ���.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "��� ������... " + pchar.name + ", �� ��� ������ �����, � � ����������� ����� � ���� ������ � ����������. �����, ������ ��� ��������� ����������� ��� ���� ���������, �� ��� � �����... ������ �����?";
			link.l1 = "������, " + npchar.name + ". ������ �� � ���� �������: ������� - �� ��������� �����.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "� ��� ��������� �������, �� � �� �������, ��� ����� ���� ������� �����������, � ������ ����� �������� ������.";
			link.l1 = "�����. ����� �������, ��� �� ���� ����� ������.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "��� � ������������. ����� ������ ��� ��� � ����. � ������ ��� ����� �������� ����������� ������ � ����������.";
			link.l1 = "����� �� ���� ������. �� ������� ����� ������, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//����� �� ����� ������ ���� ������
		break;

		case "Usurer_Escape":
			dialog.text = "��� � ����� �����? ��... ��� ��� ����. � ��������� ���� ���� ����� ��� ��������. ���, ��� ������� �������, ���� ���������� ����� �������� ������� ��������...";
			link.l1 = "� ����� �������! ��� " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "����, ����, �� �������! ��� ��� ����� ����� ���.";
			link.l1 = "��� ���?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "� �� �� � �����? �� ����� ������ �����. ����� ������������, ��� �� ��������� � ����� ������� ���� ����� ����������. �������, ���� ���������� ���������. ��� ���� �� ������, � � ������� ��� � ������.";
			link.l1 = "���� �����? ���?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "������, ��� �� ����� �� ����� �������... ����, ��� �� ���� ������... �����?";
			link.l1 = "������ ��������! ��, � ��� ����� ��� ����� �������! ���� �� ������, ����������? �� ����� �������?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "����� �� �����. ������. ������. �� ������ ���������. ��� - � ���. � ��� ���� �� ������ ����� �����, �� �� '��������', �� �� '��������' - �������, �� ��� �� � �������.";
			link.l1 = "��� ���������! ��� �� ���� ���� - ���������� ������ ��������! �� ���� �� �� ������ ����� ���������! � �, ����������, �������"+ GetSexPhrase("","�") +", ��� �� ������������� ��������! �� �� ��� ������� ��������... �����, " + npchar.name + ", ����� ���� �������� �� ��������... �� ��������.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
		string sColony;
		sColony = npchar.city;
		SetNull2Deposit(sColony);
			dialog.text = "�� ������, � ��� �������. ���� ��� ����������� ������, ��� ��������, �������� ������� ����� - � ������ � ����� �������.";
			link.l1 = "�������. �� ����� � ���� ������� ������ ��� ����. ����� �������.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("��","��"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
		break;

		//<--������������																																
	}	
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(npchar.nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(colonies[nation].nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// ��������
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // ����
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // ������ �� ����� ������
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //����������� ����� �� ����
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
        // ��������
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// ����������
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
	    // ����������
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}		
		// ����������
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
		// ���������� ������
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
            continue;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}

void SlavetraderGalleonInWorld()
{
	//������� ������ � ������
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, -1, true));
 	SetCaptanModelByEncType(sld, "war");
	FantomMakeCoolSailor(sld, SHIP_WARSHIP, sName, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//�������� ������� ����	
	sld.Ship.Mode = "war";	
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	sld.WatchFort = true; //������ �����
	sld.AlwaysEnemy = true;
	sld.SuperShooter  = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//�������� � ���� �����
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//� ������� ������ ����
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";//������� ������
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";//����� ������ ����������
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";//��� ������
	sld.city = pchar.questTemp.Slavetrader.Island; //��������� �������, �� ����� ������� ������
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("��� ������� ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������ '" + sName + " '";
	int daysQty = 20; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//��� ��, ��� ������ ����������
	sld.lifeDay = 20;
}		


int PcharReputation()
{
	return makeint((100-makeint(pchar.reputation))*0.5)+1;
}