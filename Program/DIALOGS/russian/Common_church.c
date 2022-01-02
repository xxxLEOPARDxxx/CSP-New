// boal 25/04/04 ����� ������ �������
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
        npchar.quest.BadMeeting = "";
    }
	if (!CheckAttribute(npchar, "quest.Fooled"))
    {
        npchar.quest.Fooled = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("��� ���","���� ���") +", � ���������, � �� ���� ���� ���� �������. ����!", "��� ��������� ������ ����� �� ������ � ������� ����, "+ GetSexPhrase("��� ���","���� ���") +". ������� ������� ��� ����������, �� � �� ���� ������������ ���� �������...", ""+ GetSexPhrase("��� ���","���� ���") +", ���� ���� ������! ����� ����, �� ����� � ����!"), 
					LinkRandPhrase("��� �� ������� � ������, ������ ����? � ������, ����� �� ������"+ GetSexPhrase("��","���") +" ����������, ���� ������� �� ��������� � �� �������� ����� �����!", "���������� ������ ����, ��������"+ GetSexPhrase("�","��") +"! � �� ���������� �� ���"+ GetSexPhrase("���","��") +", ��� ��!", "���������� ������ ���� �����! ��� �� ����� ����� ��������!!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("�� ����� ����, �����...", "�� �� ����� ��� ���� ������..."), 
					LinkRandPhrase("������ ����, ����� �� ������� ��� ������...", "����, �� ����������...", "�����, �� �������, �� �� ����, �� ����"));
				link.l1.go = "fight";
				break;
			} 
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				Dialog.Text = "����� ���������� ��� ���� ������ �������, "+ GetSexPhrase("��� ���","���� ���") +".";
				link.l1 = "�����, ������� �������� ����� ����������� �������. �������, ��� ��� ����� ���������, �� � �������"+ GetSexPhrase("","�") +" � ��� � �����"+ GetSexPhrase("","�") +" ����� ���� ������������� ��������. �� ����� ��������������!";
				link.l1.go = "MC_CaracasChirch";
				Link.l2 = "��� ����.";
				Link.l2.go = "exit";
				break;
			}
			if (IsEquipCharactersByItem(pchar, "DHGlove") && npchar.quest.BadMeeting != lastspeak_date)
			{
				Dialog.Text = "��... ������! ��� �� ������, ������� ����������, ������� � ���� �����?! ������� ���, ���� ��������� �� ����� �� ����!";
				Link.l1 = "������ ��������... � ���������� ������ ������?";
				Link.l1.go = "DHreaction";
				break;
			}
			if (startherotype == 2 && npchar.quest.BadMeeting != lastspeak_date && npchar.quest.Fooled != lastspeak_date && !IsEquipCharacterByItem(pchar, "glasses") && 80 > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				Dialog.Text = "���� �����... ������ ���� �������, ������� ���! ��� � ����� �� � ��� ��������!";
				Link.l2 = "�� �������������, ������ ����. � ����� ��������, � ���������� �� ����� ���� ��������� ��������� ��������.";
				Link.l2.go = "fool_priest";
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit";
				break;
			}
			
			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				Dialog.Text = "������ ���� �������, ������� ���! ��� � ����� �� � ��� ��������!";
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit";
				Link.l2 = "������� � ����� �� ���� � ������ ����!";
				Link.l2.go = "exit";
				break;
			}
			
            if (npchar.quest.BadMeeting != lastspeak_date )
			{
				if(Pchar.questTemp.CapBloodLine == false)
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
					{
						dialog.text = "...����� ������ �� � ������ ��������! �� ������ ��...";
						link.l1 = RandPhraseSimple("��! �� �������"+ GetSexPhrase("","�") +", �����?", "��� ��� ����!");
						link.l1.go = "GenQuest_Church_2_Start_1";
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // ���������� ����� �� ���� ���� � �����
						break;
					}
				
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("��� ���","���� ���") +", � ��� ����� ������ ���!";
						link.l1 = "� � ���"+ GetSexPhrase("","�") +" ������ ��� � ������ �������, ���� " + NPChar.name + "...";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
						break;
					}
				
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						Dialog.Text = ""+ GetSexPhrase("��� ���","���� ���") +"! ��� ����� ������ ���� � ������ ������� � ������� ����������. ������, ��� ������������� ����������� ���������� ������ ����?";
						link.l1 = "��, " + RandPhraseSimple("�����", "������ ����") + ", ���� � ��� ������ � �� ������ ��� �������� �����, ���� � � ��������"+ GetSexPhrase("","�") +" ��������� ������ �������, ��� � �����, �� � ����� ���� ��������� ���������.";
						link.l1.go = "GenQuest_Church_1_Complete_1";
						break;
					}
				}
				Dialog.Text = "����� ���������� ��� ���� ������ �������, "+ GetSexPhrase("��� ���","���� ���") +".";
				link.l1 = "������������, ������ ����.";
				link.l1.go = "node_3";
				Link.l2 = "�� ��� �� ����, � �� ���� ��� ������ ����������.";
				Link.l2.go = "node_2";

				if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
				{
					Dialog.Text = "��� �����! ��� � ���� ������?";
					Link.l2 = "�����, � ��� �����.";
					Link.l2.go = "exit";
				}
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// ���� �� ��� �������, �� ���� �� ���� ����.
			}
			if (npchar.quest.BadMeeting == lastspeak_date)
			{
				Dialog.Text = "������ ���� �������, ����������"+ GetSexPhrase("�","��") +"! ��� � ����� �� � ��� ��������!";
				if (pchar.sex == "Skeleton" || startherotype == 2)
				{
					Dialog.Text = "������ ���� �������, �������! ��� � ����� �� � ��� ��������!";
				}
				Link.l1 = "�� �����-�� � ��������.";
				Link.l1.go = "exit";
			}
			
			NextDiag.TempNode = "First time";
		break;
		
		case "DHreaction":
			dialog.text = "��������! ��� �� � ��� � ����� ��������!";
			link.l1 = "���... �� �� ������ �������.";
			link.l1.go = "exit";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -5);
			npchar.quest.BadMeeting = lastspeak_date;
		break;
		
		case "fool_priest":
			if (drand(80) > sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)))
			{
				dialog.text = "���� �� �������� ����! ����� ������, ���� �� ���������� ����� ������������ ���� �����!";
				link.l1 = "������!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 5 + 5 * sti(pchar.rank));
				ChangeCharacterReputation(pchar, -1);
				npchar.quest.BadMeeting = lastspeak_date;
			}
			else
			{
				dialog.text = "�������� �����������, �� �����. ��� ������� ��������� ����� �������� ������ ��������� ��������?";
				link.l1 = "���� ���� ������.";
				AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50 + 10 * sti(pchar.rank));
				link.l1.go = "node_3";
				npchar.quest.Fooled = lastspeak_date;
				
			}
		break;
		
		case "node_2":
			dialog.text = "��, �� ����������"+ GetSexPhrase("�","��") +"! � �� ����� ������, ���� �� ���������� ����� ������������ ���� �����!";
			link.l1 = "�� � � ��� �� �������"+ GetSexPhrase("��","���") +" ����� �������������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = "�� ����������� ������� ��� � ���� ����... �� ������ �� ��� � �����-�� �����?";
			if (startherotype == 2 && !IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.text = "� � ����� �������. ���, ��� ������.";
			}
			//������������ ����� -->
  			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				link.l1 = "�����, ������� �������� ����� ����������� �������. �������, ��� ��� ����� ���������, �� � �������"+ GetSexPhrase("","�") +" � ��� � �����"+ GetSexPhrase("","�") +" ����� ���� ������������� ��������. �� ����� ��������������!";
				link.l1.go = "MC_CaracasChirch";
				break;
			}
  			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "��������� ����� �������� �� ���. � ��������� ��� �����, � ������.";
				link.l1 = "� �����"+ GetSexPhrase("","�") +", �����.";
				link.l1.go = "exit";
				break;
			}
			//<-- ������������ ����� 
			//homo ������� �����
            if (Pchar.questTemp.CapBloodLine != true)
            {
    			link.l1 = RandPhraseSimple("� ���� ������ �������������.", "���� ������������ �� ������ ����.");
    			link.l1.go = "donation";
				if (startherotype !=2)
				{
					link.l2 = RandPhraseSimple("�����, ������� ����� ��������.","��� ����� ���������, "+RandPhraseSimple("�����.", "������ ����."));
					link.l2.go = "ispoved";
				}
    			link.l3 = RandPhraseSimple("� ���� � ��� ����, " + RandPhraseSimple("�����.", "������ ����."),
                                           "� ������"+ GetSexPhrase("","�") +" �� ����, " + RandPhraseSimple("�����.", "������ ����."));
    			link.l3.go = "work";//"quest lines";
            }

			link.l6 = "��������, ��� ���� ����.";
			link.l6.go = "exit";
		break;

		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...� ������� ������! �� �������� �� ���� ���� ���������� �� �����������...";
				link.l1 = LinkRandPhrase("������ ����", "�����", "����") + ", �� ������� �� �� ������������? ��� ������� � ���� ��������.";
				link.l1.go = "GenQuest_Church_2_Start_2";
				link.l2 = RandPhraseSimple("�-�... �� ���� ��� ������...", "�, �������, �� ������� - �����, �������...");
				link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "�, "+ GetSexPhrase("��� ���","���� ���") +", ��������� ������� ���������, ����������� �� ������������! ��������� �������!!! �� ��� ��� �����, ��� ��������� ���� ������� ���� ����� � ������ �������!";
				link.l1 = "��, ��� ��� ���!.. � ��� �� ��� ���������?";
				link.l1.go = "GenQuest_Church_2_Start_3";
				link.l2 = LinkRandPhrase("��� ���, �������, ��������, �� �, �������, �����...", "����������, �����, �� ��� ��� ����...", "�������� �� ������� ����������� �� �������, ����� ���� ����� ������� ��������. ����� �, �������...");
				link.l2.go = "exit";
			break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "�����-�� �������� ��� �������� ���� ������� ���, ��� ���� ������� �������! � ���������� ���� ����������, ����������!";
				link.l1 = "�� ��, �������... ��, � �������, �� ����������� �����-�� ����?.. �� ������� ������, ��� �������.";
				link.l1.go = "GenQuest_Church_2_Start_4";
			break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "� ��! �������!! � ������� ����������� ���������� �� ������! � ������ ������ �� ���� �������.";
				link.l1 = "�� ����������, ��� ��� ����� ����������� ����. �� � ����"+ GetSexPhrase("","�") +" � ���� ����� ����� ����������. ������������ ������, � �������.";
				link.l1.go = "GenQuest_Church_2_Start_5";
			break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +", ��� ����� ������� ���������, ��������� ������ ������������� ���? ��� ������� ��������� ��� ������ ������ - ��������� � ��������  ������������, ��� ��������� �������� � ���������� � �������� �������! �������, ��� �� � ������ �����!";
				link.l1 = RandPhraseSimple("��, � ������"+ GetSexPhrase("","�") +", ��� ����� ����� ������� ���������������, ������ ��������� �� ���. �������, �� ���� ��� ������. ����� �������.", "��, �� ��� ���� ��� ���� ��� ������ ������� ����������� � �������� - �� ������ ������ � � �� �� �������"+ GetSexPhrase("��","���") +". �������, ��� ��� ����. ����� ������� � ����� ������� �����.");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("������ ����", "�����", "����") + ", �� ���� � �������� ������� �� ������"+ GetSexPhrase("","�") +", � � ����������� ������ ������� ���������� ��� ���������.";
				link.l2.go = "GenQuest_Church_2_Start_5_1";
			break;
		case "GenQuest_Church_2_Start_5_1": //���� - ����� �� ������� ��� ������������� - �������, ������
			dialog.text = "� ���� �������� �� ����," + GetSexPhrase("��� ���","���� ���") + "! ��� � ������ ���� ���������� �� �������!";
				link.l1 = "������ �� �����������, " + RandPhraseSimple("�����.", "������ ����.");
				link.l1.go = "GenQuest_Church_2_Start_6";
			break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// �����, � ������� ����������
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // �� ����� ������� ���������� ��������
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		//	AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "��, ����� ��������� ��������� ����� ��� � ���� �� ���������� ����� �����, ���� �������� �� ����� �� ������...";
				link.l1 = "��������, �� �������, ���, ��������, ��������... ��� ��� �� ��� ����������, �����?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // ��������� �������� ������������...
			{
				dialog.text = "������� ������... ������� ��, ��������... �� �����... ����������? �� �� �����?";
					link.l1 = "��� ������ ������ ���������, ������� �������� ������� ������� ����������� � ������������: �� ����, �� ������, �� ��������� ���������������� ������ �������� ������. ����� ����� �������� �� �������������� �������? � �� ��� �����, �������� �������?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "����� ����� �����... ��� �� ����� ����������? �� �� �����?..";
					link.l1 = "��� ������ ������ ���������, ������� �������� ������� ������� ����������� � ������������: �� ����, �� ������, �� ��������� ���������������� ������ �������� ������. ����� ����� �������� �� �������������� �������? � �� ��� �����, �������� �������?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
			break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("��� ���, ������","���� ���, ��������") +"... ������� ������... ����� ������, ����� ���������... ���� �������, ����! �� ������... ����� ���� �� �������... ����������� �������� �������, �������� ��������, �������� ������� ����... ��������� ����� �, �����������, ������ ������ �� ����� ���� - ����� ���� �������� �� ����������, ������� ��� �� ����, �������� ���������...";
				link.l1 = LinkRandPhrase("������ ����", "�����", "����") + ", �����������. �������, ��� ��� ������ ������ �� ����������... � �� ���������. ������, ��� ����������� ������ ��� ���� ��� ���������, ������� � ��� � ������"+ GetSexPhrase("","��") +".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
			break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "��������� ����, ����! �������� ������� ������������ ����, ������������� ��������, ���������� � ������� � ������...";
				link.l1 = "���������� ����� ������... ������, ���� ���� ��������� ���������, � ����� ���: ������� �� ��������, � ��������� �������. ���� �� ������ ��� ���, ������ �� ����� ������ �� �����. � �� ���������� ��� ��� �� ������ �������, ��� �� ������ ���� � ����� � ��� �������...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
			break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // ��������� ����� ������� �� �����
			{
				dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +"... �� ������� ��������� � ������������� �������� �� ��� ����. ������� � ������������ ����� ���� �������� ����. �� ����� ������ ������������ ��� � ������ ������� ��� �������� �������������� � ������� " + FindRussianMoneyString(iMoneyToCharacter) + "... �������, ��� ������ ���� �������?";
					// �� �� ����� ������. �������� ����
					link.l1 = "��� ������, ���� " + NPChar.name + ". � � ��� �����"+ GetSexPhrase("��","��") +", � ��� ������ ����������� �� ����� ����� ��������.";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					// �� ����� ������
					link.l2 = "���������, " + LinkRandPhrase("������ ����", "�����", "����") + ", ����� ������ ����������.";
					link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +"... �� ������� ��������� � ������������� �������� �� ��� ����, ��� ���� ������ ������� � ��������. ������� � ������������ ����� ���� �������� ����. �� ����� ������ ������������ ���!";
					link.l1 = "������� �� �������������, " + LinkRandPhrase("�����", "����") + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
					link.l1 = "�������������, �������, ���� ������, �� ������� �� ���������� ��� ���-�� ����� ������������, ��� ��� � ������ � �����"+ GetSexPhrase("","��") +" ������� �����...";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			
			// ���� ����� ���� - ����� �� ��������!
			ChurchGenQuest2_RemoveCup();
			break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("c�","���"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "��, ���� ��, ������ �����... �������, ��� �������� ����� � ������� " + FindRussianMoneyString(iMoneyToCharacter) + " ������ ���� �������?";
				link.l1 = "��, " + LinkRandPhrase("�����", "����") + ", �������.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
			break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "� �� ������� ����� ������, "+ GetSexPhrase("��� ���","���� ���") +", � ��� ��� �� ��������?!";
				link.l1 = "� ������ � �������� �����, ������� �������� ��������� � ��������� ��������. � �� ���� ���� ��� ���������, ������� � �������"+ GetSexPhrase("","�") +" �� ����������, ����� ���������� ���� �������... �� ���-�� ������ �������?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
			break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "� �����, ���� ��, ��� �� ������ ������������� � ����� ��������� ������, � ��� �� ������ �� ���� ��������. � ��� ���� � ������� ����, �� ���� �� ������� ������������ � � ������ �������, ��...";
				link.l1 = "�������, �����, �� � �� ��������, ���� �� �����������.";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
			break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // ������ ��������� ������ �������� �������
			{
				dialog.text = "��� � ������ ��� ���������?! �� �� "+ GetSexPhrase("����� �������","����� �������") +", � ���� ������ �������� - ��, ��� ���������� ��� ���������� � ���, ��� � �� ����� ����� - ��� �� ������ ����! ������� �������� ���� ����������� �� ������ �� ���������, �� � �� ����������������!";
					link.l1 = "�������� ������� � �����! ������ �� ������, ��� ������� ��� �� ����������, �� ������� �� ���� ���������? �����, � ����"+ GetSexPhrase("","�") +" �� ������, ��� ��� ������ �������� � ����� ������� ��������?";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "��� �� � ��� � ���� ��������, �� �� ��������� �������������, ������� ����� ����� �������, �������������� � �����, ��������� ������������� ����������, �������� ��������� �������, ������� ���������� ���������� ����� ����! � ����������� ����, ��� � �� ���� �����������, ����� ��������� ��� � ��������!";
					link.l1 = "��� �... � ����, �� �������� � ����� ���������, ��� �� ������� �������� ����. �� ���� ������ ���, ����� ������� ��� �� ���� ��� ������ ����������. �������� ���� '��������� ������' � ��������� � ���, �������� �� �� ����������� � ���, ���� " + NPChar.name + ".";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
					link.l2 = "�������� ��� ��������, ������ ����, ��� ������ ������������ �����, � ���� � ��������. �������� ���� � ������������ ����.";
					link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
			break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "�-�-�... "+ GetSexPhrase("��� ���... ������... ��������","���� ���... ��������... �������") +" " + PChar.name + "... � ����� ����� ��� ���������... ����������� ���� �����������.... �������������� ���� �������� ������� ��� ���� �������� ������ � ������� " + FindRussianMoneyString(iMoneyToCharacter) + "... �������, � ��� ������, ���� �� �� ������� ��������� � ��� ���� �����������...";
			// ��� ���� �������� ���� �������
			link.l1 = "� ������ �� ��������� ���������. ��������� ����! � �� �������, ��� � ������ ������, ������� �� ������ �������� �� �������� ����� ��������!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// ��� ���� - ��������
			link.l2 = "� ������ �� ��������� ���������. �������� ����! ��� ������ � ���� ���� ������, ��� ��������"+ GetSexPhrase("","�") +" �� ��� ������� ����� ������� � �����, �� ����� �� ������������ �� �������� ������������� � ���!";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
			
			// ���� ����� ���� - ����� �� ��������!
			break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","��"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("","��"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","��"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			
		// ������ �� �������� ����������.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
		{
			link.l1 = "�������� ��������������, " + LinkRandPhrase("������ ����", "�����", "����") + ": ��������� ��������� ����� ������� � �����������, ��� ��� �� ������� ������� ��������� ������...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
			break;
		}
		
		// �������� ���������� ������ ����.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
		{
			link.l1 = "�������� ��������������, " + LinkRandPhrase("������ ����", "�����", "����") + ": ��� ������� ������� �����������, �� ���� ������������ ������� ��������� ��� ��� ���� ��� ���������.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}
		
		// �������� ���������� � ������ � ����.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "������"+ GetSexPhrase("","�") +", ��� �������� ��� �������� - � �������� �������"+ GetSexPhrase("","�") +" ���������� � ������"+ GetSexPhrase("","�") +" � ��� ���������� ������, � ����� ��� ��� ���� ��� ���������.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}
			
			// ������ ����� ��������.
			link.l2 = LinkRandPhrase("������ ����", "�����", "����") + ", � ������"+ GetSexPhrase("","��") +" ������ �����... ��� �������� ��������� ����� �������, ��� � �������, ����� ��������� ���������, ��, ����� � ��-���� ������"+ GetSexPhrase("��","���") +" �� ���, ���������, ��� ��� ������ ������� � ��������� ��, ����� ��� ���� ���� ��� ���������...";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}
		
		// ��������� - ���.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
		{
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ����� �� ���� ���������? ��� ��� ���� ����� ���������� � ������, � ��� ������ ����� - ������ �������� � ������ - ��� ����� ������ � �������� ������ ������������ ��������...";
				link.l1 = "������� ����� �� � ����� ���������� ����� ������ ���������� ���������?";
				link.l1.go = "GenQuest_Church_2_Thief_2";
			break;
		}
		
		// �������� ������� ����������� ������.
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
		{
			if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "������"+ GetSexPhrase("","�") +", ��� �������� ��� �������� - � �������� �������"+ GetSexPhrase("","�") +" ���������� � ������"+ GetSexPhrase("","��") +" ���������� ������.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}
			
			// ������ ����� ��������.
			link.l2 = LinkRandPhrase("������ ����", "�����", "����") + "... � ��������"+ GetSexPhrase("","�") +" ��� ��������. � �����������"+ GetSexPhrase("","�") +" ���������� �� ����� ����������, ���������"+ GetSexPhrase("","�") +" ��������� ���������� � �������, ����� �������"+ GetSexPhrase("��","���") +" � � �����-������ ������"+ GetSexPhrase("","��") +" ��, �� ���... ��� ��� ������ ��������� ��������� ������.";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
		}
		
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // �� ����� �������� ������...
		if(rand(1) == 0)	// ��������� ����� �� �� �� ���� �����...
		{
			if(rand(4) == 3) // ����� "������" ����� �������.
			{
				dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +". ���� ����� �������� ���� � �������� ������, �� �� � ��������, ��� �������� - �������� ����! ������� �������� �� ��� ��������� ���������, ����� �������� ���� ����.";
					link.l1 = "�����, ������ ����...";
					link.l1.go = "exit";
					sQuestTitle = NPChar.City + "ChurchGenQuest2";
					AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
					AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
					CloseQuestHeader(sQuestTitle);
					ChangeCharacterReputation(PChar, -2);
					DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", �� ��� ��������� ������� ������.";
					link.l1 = "��� ����, ����, ��, ������� ����� ������� - � ������ ������...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
			}
		}
		else
		{
			// ��������� ���� ������ ��...
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +". ���� ����� �������� ���� � �������� ������, �� �� � ��������, ��� �������� - �������� ����! ������� �������� �� ��� ��������� ���������, ����� �������� ���� ����. ������ ���� ������ � ������� ������ ���� �������������, ���� � �� �������� ������. �������� ��� ��������� ����� - " + FindRussianMoneyString(iMoneyToCharacter) + " -  � ����������� ��� ��������� ����!";
				link.l1 = "�-��!... �������, �����, � �������� ��� ������ �� ����������� ����.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
				link.l2 = LinkRandPhrase("������ ����", "�����", "����") + "... �� ������� ���� � �������� ���������. � �� ���� ������� �� ��� �������������� �� ������������� ������, ����� �������� �� ��� ������ ������.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
		}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
		if(rand(6) == 3)
		{
			dialog.text = "������, � ���� ����, "+ GetSexPhrase("��� ���","���� ���") +". ������� ���������� ��� ���������� ���������, ����� �������� ���� ����.";
				link.l1 = "�����...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
			break;
		}
			dialog.text = "��������"+ GetSexPhrase("��","��") +", ������� �� �����"+ GetSexPhrase("","�") +", ��� ������"+ GetSexPhrase("��","��") +" �������� ������� ������? ���� �� �������"+ GetSexPhrase("","�") +"! �������� ����� � �����, ��� ��� ������ �� �������� ���� ������� ������!";
				link.l1 = "��� �� ���!.. �����!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterReputation(PChar, -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterReputation(PChar, -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // �������.
			{
				dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +". ���� ����� �������� ���� � �������� ������, �� �� � ��������, ��� �������� - �������� ����! ������� �������� �� ��� ��������� ���������, ����� �������� ���� ����.";
					link.l1 = "�����, ������ ����...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // ������� ����, �.�. ���� � ����.
			}
			else
			{
				dialog.text = "��, ��� �� ����� ����, ������� ������� ������ � ��������... ��... ���� �� ������ �, �� ������ �� ������� � ������? ��� ���� ������� �����, � ������� ��������� �� ����� � ��� ����� ���������... "+ GetSexPhrase("��� ���","���� ���") +", �������, ��� ��� ������� �����, ������ ����� ������ ��������� �������, �� ��� � �������������������� �� �����, ����� ����� �������!!";
					link.l1 = "���� " + NPChar.name + ", � ���� ����� �� �����"+ GetSexPhrase("��","���") +", ������� ��� ����, �����"+ GetSexPhrase("","�") +" ���������� ���, ����� �� ��������, ��� ���� �������. � ��� �� ������ � ����� �������� �� ��� �����������!";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "������ �����, �����"+ GetSexPhrase("�","���") +", � ����������� ���������, ������� �������� ���� ������ �������, ��� ���� �� ���� ������� �� ��� �� ��������� ���"+ GetSexPhrase("��","�����") +" � �������"+ GetSexPhrase("���","���") +"!";
				link.l1 = "��� �� ���?! " + LinkRandPhrase("������ ����", "�����", "����") + "!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +". ���� ����� �������� ���� � �������� ������, �� �� � ��������, ��� �������� - �������� ����! ������� �������� �� ��� ��������� ���������, ����� �������� ���� ����.";
				link.l1 = "�����, ������ ����...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "����, ��������� ����! �� ��������� ������� �������, ���� ��! � ����, ��� ���� ��� �������� �������� ��� ������ ���� � �� ������� ����� �������! � ����������� �������, � ���...";
				link.l1 = "������-��, � ����� ����� ������ ������ �� ������, ��� �� ������, �����. ��, ������, ��� ������������� ������� ���� �������.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", � ���� ������������ ��� �� �����������, ��� ��"+ GetSexPhrase(", ��� �������� ������ ������ ������ ������,","") +" ��������� ��� ���� � ������...";
				link.l1 = "������ ����, �� ������� ��������������� ��� �������� �������. �������� ��� ��������� ����� �������...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			break;

	//================================================================================================================
		
		
		case "donation":
			if (startherotype != 2 || IsEquipCharacterByItem(pchar, "glasses"))
			{
				dialog.Text = "�������, "+ GetSexPhrase("��� ���","���� ���") +". ������� �� ������� ������������ ������ ������?";
				Link.l1 = "��������, ������ ����, �� ������������� �� �����.";
				Link.l1.go = "No donation";
				if(makeint(PChar.money)>=100)
				{
					Link.l2 = "��� ����� ����� ��������. ����� 100 ��������.";
					Link.l2.go = "donation paid_100";
				}
				if(makeint(PChar.money)>=1000)
				{
					Link.l3 = "1000 ��������. � �����, ����� ������.";
					Link.l3.go = "donation paid_1000";
				}
				if(makeint(PChar.money)>=5000)
				{
					Link.l4 = "��� ����� � ��������, ������� � ��������� 5000 ��������.";
					Link.l4.go = "donation paid_5000";
				}
			}
			else
			{
				dialog.Text = "��� �����. ���� ���� ��������� ����� ��� ����� ������ ����� �����.";
				Link.l1 = "��� ������. ����� ��� ������...";
				Link.l1.go = "node_3";
				
			}
			//-->> ����� ������������� ������� �������
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "������ ����, � ���� ������� ������������� �� �� ����. � ����� ��� �� ���������.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- ����� ������������� ������� �������
		break;

		case "No donation":
			dialog.Text = "��... ��� ���� �������, � �� ������ ��� ��������. �� �� ���������, ��� ��� �������� ��� �� �������� ����.";
			Link.l1 = "� �� ������ ���. ������� ����� ������ ����.";
			Link.l1.go = "node_3";
			Link.l2 = "��������, ������ ����, ��� ����.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "�� ���� ������ ������ ��������� ���, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ���.";
			Link.l1 = "��� ���� ���������� � ����, ������ ����.";
			Link.l1.go = "node_3";
			Link.l2 = "��������, ������ ����, ��� ����.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "�� ���� ������ ������ ��������� ���, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ���.";
            Link.l1 = "��� ���� ���������� � ����, ������ ����.";
			Link.l1.go = "node_3";
			Link.l2 = "��������, ������ ����, ��� ����.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "�� ���� ������ ������ ��������� ���, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ���.";
            Link.l1 = "��� ���� ���������� � ����, ������ ����.";
			Link.l1.go = "node_3";
			Link.l2 = "��������, ������ ����, ��� ����.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "������� ��, "+ GetSexPhrase("��� ���","���� ���") +", � ���� ������.";
			link.l1 = "� ���������"+ GetSexPhrase("","�") +". ����� ���� � ������ ���.";
			link.l1.go = "exit";
			link.l2 = "� ��� ����"+ GetSexPhrase("��","��") +", ������ ����. ����� ����������� ��� ��� �����������, �� ������ ������ ���...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "��� �� ������, ���� ��...";
			link.l1 = "��, �� �� ���� ������� ������ �������� ����� ���� ����� �������. � ������"+ GetSexPhrase("","�") +" � �����"+ GetSexPhrase("","�") +" �������...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "� �������, ����� ��� �� ���� �����, ��� ������ ��� ������ " + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = "���, �������, ������ ����.";
			link.l1.go = "ispoved_3";
			link.l2 = "������ ����, ������ ����... ������.";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "����� ������� ������� ���� ��� �����. ��� ��� ��� ������, � ��������� �������� ������ ��������, �� �������� ����� ������ ��� ���������.";
			link.l1 = "�������, ������ ����, �� ���� ����� �������... � �����.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "������� ������� �� ������� ������ �����! ������ � �����, ����� � ������! ���� ���� ������ - � ���������!";
			link.l1 = "� ��������� ������� ��������. �� � ���� �����, �� ������� ����. ��������...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "�������, "+ GetSexPhrase("��� ���","���� ���") +", �� ������ ��� ������������ ������. � ���� ��� ��������� ��� �������� �� ������, ��� ����� �������.";
				link.l1 = "��������, " + RandPhraseSimple("�����", "������ ����") + ", ��� ���� ��������� ����� ���������. ���� " + PChar.GenQuest.ChurchQuest_1.PriestName + " �� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " ������� ��������� � ���� ���������� ����������� ����� ������������ ����������, � ������ ������� ��� ������� �� ����, ���� ����� ������.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "����� ���� ������� ����, "+ GetSexPhrase("��� ���","���� ���") +"?";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" �� ������ ��� ���� ������, �����...";
			link.l1.go = "quests"; // ������ � ���
            link.l2 = RandPhraseSimple("� ���� ���������� � ������ �� ����� ������ " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        "��� ���� ���� � �������, �� ����� �� ����� ������?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("������ ����", "�����") + ", � �����"+ GetSexPhrase("","�") +" �� ���������� � ���� � ���������� ��������."; //(��������� � �������)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "� �������� � ���������.";
                link.l4.go = "healthAdd_1";
				//Lipsar ����� ������� ������ ������
				if(CheckAttribute(PChar,"Luke.BadPoison"))				
				{
						link.l4 = "�����, �������� ���. ���� �������� �����-�� ����� ������� ����, ��� ��� ������?";
						link.l4.go = "LukePoison";
				}
            }
			// BlackThorn - ��������� ����������
			if (CheckAttribute(PChar,"UnexpectedInheritance"))
            {
				if(!CheckAttribute(pchar, "UnexpectedInheritance_translator"))
				{
					link.l10 = "������ ����, ��� ����� � ���� ���� ���������� �����. �� �� ������. ���� � ��������� ��� ������� �������?";
					link.l10.go = "UnexpectedInheritance_translate";
				}
				else
				{
					if(npchar.id == pchar.UnexpectedInheritance_translator && GetNpcQuestPastDayWOInit(npchar, "UnexpectedInheritance_translate") > 0 && sti(pchar.money) >= 1000)
					{
						link.l10 = "������ ����, � �� ������ ��������. � ���, ����������, �������� �� ����� �������.";
						link.l10.go = "UnexpectedInheritance_translate_end";
					}
				}
            }
            //==> ������� ����, ����� ����, ����������� ����� �����.
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
                link.l6 = "������ ����, � ���� ���� ����, ������� � ���� ������ ���. ��� �������� �������� �����, ����������.";
                link.l6.go = "GiveLamp";
            }
			//<== ������� ����, ����� ���� ����������� ����� �����.
			//����� ���� - �� ����� � ����� �������
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("������ ����", "�����") + ", � ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//==> ��������� ������� � �������
			if (CheckAttribute(npchar, "quest.DestroyGhost") && npchar.quest.DestroyGhost == "GoodResult")
			{
				switch (npchar.quest.DestroyGhost.label)
				{
					case "������": sTemp = "������ �������"; break;
					case "������": sTemp = "������ �������"; break;
					case "����": sTemp = "���� ������"; break;
					case "����": sTemp = "���� ������"; break;
					case "����������": sTemp = "���������� �������"; break;
					case "����������": sTemp = "���������� �������"; break;
				}
				link.l5 = "������ ����, " + sTemp + " �� �������. ���� �������, ������ ������� ����� �� �����������.";
                link.l5.go = "GhostShip_S1";
			}
			//==> ������ ������ � ������
			if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different.Church_NightGuard == npchar.location)
			{
	            link.l8 = RandPhraseSimple("������ ����", "�����") + ", � ���� ���������� � ��������� ���������� � �������� ������� �������.";
	            link.l8.go = "NightGuard_result";
            }
			//<== ������ ������ � ������
			link.l99 = "� ���������"+ GetSexPhrase("","�") +", ���� ���� ����.";
			link.l99.go = "exit";
		break;

		case "UnexpectedInheritance_translate":
			dialog.text = "����� ��������, �� � �������� ����� ������ ������ ����� ������� � �������� ��������. ��� � �� ���� ������� �� � ���, �� � ������.";
			link.l1 = "����� ����.";
			link.l1.go = "exit";
			if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // ���������
			{
				dialog.text = "������, � ��������. ��������� ������, "+GetSexPhrase("��� ���","���� ���")+", � �� ��������� � �����������.";
				SaveCurrentNpcQuestDateParam(npchar, "UnexpectedInheritance_translate");
				pchar.UnexpectedInheritance_translator = npchar.id;
				link.l1 = "��������� ���, ������ ����.";
				link.l1.go = "exit";
			}
			
		break;
		
		case "UnexpectedInheritance_translate_end":
			dialog.text = "���������� ��� �������. ���, ��� � ���� ����������.";
			link.l1 = "�������, ����.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			UnexpectedInheritanceTranslatePart(pchar.UnexpectedInheritance);
			DeleteAttribute(pchar, "UnexpectedInheritance_translator");
			DeleteAttribute(pchar, "UnexpectedInheritance");
			
		break;

		case "prihod":
			//��������� �������
			if (rand(2)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.DestroyGhost") && GetNpcQuestPastDayWOInit(npchar, "Ghost") > 7)
			{
                dialog.text = "��� �� ������ ������ �� ���� ��������, �� � ���� ��� ������� ������. � ����� ��� ��������� �����. � �� ���� ����� ���� ����������. ����� ����, �� � ���� �� ������ ��������, ������� ���������� ��� ��� ����������� �������, ������������ ���� �����.";
        		link.l1 = RandPhraseSimple("��� �� ������ �������, ������ ����, ��� ��� ��� ��������? ��� ������ ���� �����?",
                                            "� ����� ���, ����������� ������, ������ ����.");
        		link.l1.go = "DestroyGhost_1";
				SaveCurrentNpcQuestDateParam(npchar, "Ghost");
				npchar.quest.add = true;
				break;
			}
			//��������� ������� �����
			if (!CheckAttribute(npchar, "quest.add") && rand(4)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.GuardNightChurch") && !CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && GetNpcQuestPastDayWOInit(npchar, "NightChurch") > 60 && GetHour() < 23)
			{
                dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", � ���� ���� ��� ���� ��������� ���������. ��� ����� ������ ������, �� �� ������ � ���������� � �� ����������� ����������. ��� ���� � ���, ��� � ��������� ����� '������' ������� ����������. �����-�� �������� ���� ����� �������� � �������, �� �� �������, � ������ ������� �� ��������...";
        		link.l1 = "� ��� ��� ���������, ������ ����?";
				link.l1.go = "NightChurch_1";
				SaveCurrentNpcQuestDateParam(npchar, "NightChurch");
				break;
			}
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        		dialog.text = "��� ���������. ������ � ���� ������� ���, "+ GetSexPhrase("��� ���","���� ���") +", �� ������ ��������� � ���� �������� �������� ������ ������ ����� ������.";
						link.l1 = LinkRandPhrase("�����", "������ ����", "���� ���") + ", � ������� ������"+ GetSexPhrase("��","��") +" ��������"+ GetSexPhrase("��","��") +", � ��� ��������� ��������� ������-������ - ��������."+ GetSexPhrase(" ��� �� ������ � ������, ���� �� ����� ������ ������, ��� �?","") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // ���������� ����� �� ���� ���� � �����
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// ���� �� ��� �������, �� ���� �� ���� ����.
			}	
            dialog.text = "� ��� � ������� ��� ��������, "+ GetSexPhrase("��� ���","���� ���") +". ������� �� �����������.";
    		link.l2 = "��, ��� ��� ������, � ����� �� ����� �����.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// ���� �� ��� �������, �� ���� �� ���� ����.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "�� ��� �, ���� � ���� ���� ���������� ���������, ���������� �������� ��������� �� ������ ������� ��������, �� � ������� ���������, � ����� �������� ���...";
				link.l1 = LinkRandPhrase("�����", "������ ����", "���� ���") + ", � ���� ��������"+ GetSexPhrase("","�") +" ������� ��� ����� ������, ���� ���� ��� ����� ��� ������� ������������� � ���� �����������! �� � ������ ���� �������.";
				link.l1.go = "GenQuest_Church_1_Start_2";
			break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "��� ���! ��� ������... �� ���� ������ ����������... ��������� ����� ����� ���������� ������ " + PChar.GenQuest.ChurchQuest_1.ToName + " �� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + ", ��� �� " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Dat") + " �������� � ���� �� ����� ��������� ������������ ������ � ������� ��������� �� ��������� ����������. ��� ��� ������� ���� ����������� ����������� ������������ �� �������������� ��������������� ����������� ����� ������, �������� � �� ���, ���� � �����������, ��� ��������� ������� ����������� �� �������� ��� ������� �������� � ����...\n�� ����� �� �� ���������������� ���������� ���� ��������?";
			link.l1 = "�����, " + LinkRandPhrase("�����", "������ ����", "���� ���") + ", ��� �� �������� ������ �������. ���� ������� ����������, � ��� ��� ������� ����� ���� �������� ����������.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("�����", "������ ����", "���� ���") + ", ���� ��������� �� �������������� ��� �������. � ������� �� ���������� � ����.";
			link.l2.go = "GenQuest_Church_1_Start_3";
			break;
			
		case "GenQuest_Church_1_Start_3":	// ����� ����
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
			break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// ����� 2�
			{
				dialog.text = "�!.. ��... �������������, ����������... ��, "+ GetSexPhrase("��� ���","���� ���") +", ��� ��������� ����� �������, ������ �����������, ��� �������� ����������� ������ ���� ���������� � ����� �� ��������� � ������!";
				link.l1 = "������, " + LinkRandPhrase("�����", "������ ����", "���� ���") + ", ���� �������� ���� " + PChar.GenQuest.ChurchQuest_1.PriestName + " ����� �� ��������� � ��������, � ��� ���� ������ �� ����� ��������� ������� �������� � ����������� � ����� ����������.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// ����� 2�-� � 2�-�
			{
				dialog.text = "�, ��!.. �������������... "+ GetSexPhrase("��� ���","���� ���") +", ��� ��������� ����� �������, ������ �����������, ��� �������� ������� ������ ���� ����������, ��� �, � ����� ������, ��������� ���������� � �� ������������ ���������...";
				link.l1 = "������, " + RandPhraseSimple("�����", "������ ����") + ", ������. ������� ���� " + PChar.GenQuest.ChurchQuest_1.PriestName + " � ������� ��� ��������� ��� ����� ����� ��� � ����.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // ����� 2�
			dialog.text = "� �������, ���� ��, �� ����� �� �������� �� ����������� ������� �������: '� ������ ���, ��� �� ������� ��������� �����'? � ���� ������� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " ���������� ������ ����� ��������� �������.";
			link.l1 = "��, ������ ����, �� �����, �� � ������ ��� ������ ������ ���������� ������: '�� ��� ����� �����, ��� �� ��� ������������ ��� ������, � ����� ��� ��� ����������, � ������� ��� �������, ��� ����� ����!' � ����� " + PChar.GenQuest.ChurchQuest_1.PriestName + " ��� ����������� ������������ �������� � ����� ������������, ���� � ��� ���������"+ GetSexPhrase("","�") +", ��������� ���� ������.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "�-�-������������?! � ����� ������!.. �� ����� ��, ����� ��? � � ��� ����� ����� �������� ��� ����� ��������� ����� ����� �� ������, �� ���-�� �� �� ���������� ������� ������. �� � ����, "+ GetSexPhrase("��� ���","���� ���") +", � ����� ���������� ����� �������. ���, ������ ����� � ��������, ������� �� ���� " + PChar.GenQuest.ChurchQuest_1.PriestName + " � ������� � ����������� � ����������� ��� ����������� �������������.";
			link.l1 = "���������������� ������������, " + LinkRandPhrase("�����", "������ ����", "����") + ". ����������������.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// ������� "��������" -->
			AddItems(PChar, "Bible", 1);	// ���� ��������
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// ������ ���. ����� �������� �������!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // ������ ��������. ����� �������� �������!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // ����������. ����� �������!
			// <-- ������� "��������"
			break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// ����� 2�-� � 2�-�
			// ������� ���� -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "officer_" + (rand(63)+1), "man", "man", 15, NPChar.nation, -1, true));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade24", "pistol3", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS24, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // ���� �� ��������� �� ��������
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
		//	sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1"; // ���������� ���� ������� �� ������ �������
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- ������� ����
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // ����� 2�-�
			{
				dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +"... ���� � ���, ��� �� ������� ������ ��� �������� ����������� � ��������� ����� '" + sld.Ship.Name + "', ���� ���� �������� ��� ���������� ���������� �������. � ���� ������� ������� ������� " + GetFullName(sld) + " �������, ��� ������������ � " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". � ���� �� �� ������� �� �����, ������ ���������� ������, ������ ����, ��� � ���� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " �� ���������� �����. ������� ��, � �������������� �������, ������� ����� � ���� ������ ��������� � ������ �� ���������� ������ �������.";
					link.l1 = "��, � �� �������, ��� ����� �������� ����� ��������?.. ���������� �� �� �������� �������� ��������� ��� ������ � �������� ������������ ���������?";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // ����� 2�-�
			{
				dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +"! �� �������� ��������� �� ��������� �����! � ��� �������� ����� ���� " + PChar.GenQuest.ChurchQuest_1.PriestName + " � ��������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". ����� ���� �������������� ������� ������ �� �������� � ����������, ��� ������� ��� ����� ������������ � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". � ���� �������� ������� �� ������� �� �����, ������ ���������� ������, ������ ����, ��� � ���� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " �� ���������� �����.";
					link.l1 = LinkRandPhrase("�����", "������ ����", "���� ���") + "... � �� �������, ��� ����� �������� ����� ��������?.. � ��� � �����"+ GetSexPhrase("","�") +" �� ������, ��� ���������� ��� �����.";
					link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2�-�
			dialog.text = "� ���� �����, "+ GetSexPhrase("��� ���","���� ���") +", ���� ��� �� ������� �� ������ � �������, � � ������ ���� ����� ����� �����!";
				link.l1 = "�-��. ��� ������ ��������. �� ��� �... ������������ ����, ������ ����, � ��������� ����� � ������� ����� ��������.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // ������ ���� � ����
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "����� ������ �����, "+ GetSexPhrase("��� ���","���� ���") +". � ��� ������� �, � ���������, ������ ������� �� ����.";
				link.l1 = "� �� ������ ������ �������� ��������, ���� �� ������������ ������ �������� ��� �����?!!";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "������ ��, "+ GetSexPhrase("��� ���","���� ���") +", ������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + " ����� �������������� ��...";
				link.l1 = "��� � ��� ������"+ GetSexPhrase("","�") +", " + LinkRandPhrase("�����", "������ ����", "����") + ".";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "��������, "+ GetSexPhrase("������� �������","�������") +"! ������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + " ����� �����������, � ��� ����� �� ��������� ��� ���������� ����� ������, ��� ����������������� �� �������� ����������� ��� ���� ��������! ������� �� �������� � ������ ��������� ���� �� ��� ��������. ���, �������� ������, ������� ���� ������ �������� ����, ��������, ���� ������� ����, ��� ������� ��� ��������� ������������� ���� � �������� ����...";
				link.l1 = "� �����"+ GetSexPhrase("","�") +", " + LinkRandPhrase("�����", "������ ����", "����") + ", � �����"+ GetSexPhrase("","�") +"! �������������� ������� " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", ��������� ���� ������� ��������� � �������, ��������� ������ �������� ������� ������������� ��� ������?..";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "�� ����� ����������"+ GetSexPhrase("��","���") +", "+ GetSexPhrase("��� ���","���� ���") +". ������ ����� ������� � �� ����, ��, ����������, ��� ����� ����� �����������.";
				link.l1 = "��, " + RandPhraseSimple("�����", "������ ����") + "... ��������� ��� �� ��. � ���������� �� ��� ������� ����...";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
			break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "��, ���� ��! � ������ �������, � ��� �� ����������� ��� ������ �����! �� ���� ������ � ������, "+ GetSexPhrase("��� ���","���� ���") +", ���� ���������� ���� ������� ���� � ���������� ��...";
				link.l1 = RandPhraseSimple("�����", "����") + ", �� �������� �� ������ ������ � ����, ����� ���������, �� ���������. � �����, ����� �������� ������� ���������, ������� ����� ������ ������������ �����...";
				link.l1.go = "GenQuest_Church_1_Complete_2";
			break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "��-��, "+ GetSexPhrase("��� ���","���� ���") +", ��-��. � ���������� ���� �� �����������. ���, ������ ���, � �����, ��� ��� ���������� ��� ����������, ������� ��������� ������� � ������ ������ � ����������� ������� �������!";
				link.l1 = "���������, " + LinkRandPhrase("�����", "������ ����", "���� ���") + ". �������� ���� ������������ ����� � ��������, � ���������� �� ��� ������� ����... ��������";
				link.l1.go = "GenQuest_Church_1_Complete_3";
			break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			//PChar.GenQuest.ChurchQuest_1.AwardSumm = (rand(8) + 2) * 500;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterReputation(PChar, 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // ����� � ���������
			AddCharacterExpToSkill(PChar, "Fortune", 50); // ����� � �����
			//AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_1.AwardSumm));
			TakeNItems(pchar, "chest", 3+drand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // ���� ����
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // ���������, ���� ����� ��������
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			break;
		// <-- Church GenQuest_1	
		
		//--->> ��������� �������
		case "DestroyGhost_1":
			npchar.quest.DestroyGhost = "toCave"; //������ ���� ���������� �� ������ �����
			//������� ������ ��� ������
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			npchar.quest.DestroyGhost.locationId = GetAttributeName(aPlace_2); //Id ������� ������
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			npchar.quest.DestroyGhost.label = GetConvertStr(sld.id.label, "LocLables.txt"); //��� ���������� ��� ��������
			switch (npchar.quest.DestroyGhost.label)
			{
				case "������": sTemp = "���� � ���, ��� ������, ����������� ����� ������ ������, ����� ���������� �������!"; break;
				case "������": sTemp = "���� � ���, ��� ������, ����������� ����� ������ ������, ����� ���������� �������!"; break;
				case "����": sTemp = "���� � ���, ��� ����, ����������� ����� ������ ������, ���� ���������� �������!"; break;
				case "����": sTemp = "���� � ���, ��� ����, ����������� ����� ������ ������, ���� ���������� �������!"; break;
				case "����������": sTemp = "���� � ���, ��� ����������, ����������� ����� ������ ������, ����� ���������� �������!"; break;
				case "����������": sTemp = "���� � ���, ��� ����������, ����������� ����� ������ ������, ����� ���������� �������!"; break;
			}			
			dialog.text = "��� ������ � ������ ����� ������������ � �������� �������������. " + sTemp + " ������ �� ���� ����� ����� ����� �����, ��� � � �������� ��� �� ���������. ���� ��������, ����� ��������� � �� ������...";
			link.l1 = "��� � ���� ��� ������, ������ ����?";
			link.l1.go = "DestroyGhost_2";
		break;
		case "DestroyGhost_2":
			dialog.text = "�� - "+ GetSexPhrase("������ �������","������� �������") +". ������� ������� ������� � ���� �����! ���������� �������! � �������� ��� ����� ��������� ������ �����...";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", �����!";
			link.l1.go = "DestroyGhost_3";
			link.l2 = "������ ����, � �� ���� ������� ���� �����������. ���-������ � ������ ���.";
			link.l2.go = "DestroyGhost_out";
		break;
		case "DestroyGhost_out":
			dialog.text = "�����, "+ GetSexPhrase("��� ���","���� ���") +", ����� �����. � �������� �� ����!";
			link.l1 = "� �����, ��� �������� �� ��������...";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DestroyGhost");
			ChangeCharacterReputation(pchar, -3);
		break;
		case "DestroyGhost_3":
			dialog.text = "����� ������, "+ GetSexPhrase("��� ���","���� ���") +". ����������� ����, � �� �������� � ����� ����!";
			link.l1 = "��� ����� � �������, ������ ����.";
			link.l1.go = "exit";
			pchar.questTemp.different = "DestroyGhost";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //����������� ���������� �� ���������� 
			//���� ������ �� �������, ���� �� ����� ������ ������� ����������
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sld.DestroyGhost = npchar.index; 
			LAi_LocationResetMonGenTimer(sld.id);
			sTitle = sld.id + "Church_DestroyGhost";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "1");
			AddQuestUserDataForTitle(sTitle, "sLocation", GetStrSmallRegister(npchar.quest.DestroyGhost.label));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sLocation", npchar.quest.DestroyGhost.label);
		break;

		case "GhostShip_S1":
			dialog.text = "�������, "+ GetSexPhrase("��� ���","���� ���") +"! �� ������"+ GetSexPhrase("","�") +" ����������� ����. ����, ��� ��������� � ���� " + NationNameGenitive(sti(NPChar.nation)) + " ������ �����.";
			link.l1 = "� ��������"+ GetSexPhrase("","�") +", �����...";
			link.l1.go = "GhostShip_S2";
		break;
		case "GhostShip_S2":
			dialog.text = "� ���� �������� �� ����. ��� "+ GetSexPhrase("��� ���","���� ���") +", � ���� ����"+ GetSexPhrase("��","��") +" ����� ����� �������� � �������� �����.";
			link.l1 = "������, ������ ����.";
			link.l1.go = "exit";
			switch (npchar.quest.DestroyGhost.label)
			{
				case "������": sTemp = "������"; break;
				case "������": sTemp = "������"; break;
				case "����": sTemp = "����"; break;
				case "����": sTemp = "����"; break;
				case "����������": sTemp = "����������"; break;
				case "����������": sTemp = "����������"; break;
			}
			AddSimpleRumourCity(LinkRandPhrase("��� ������ ����, " + GetFullName(npchar) + ", ��������� � ���, ��� �� �������� �� ������� " + sTemp + " ���� ������ ������. ����������� ����, ����� � ���...", 
				"�� �������, "+ GetSexPhrase("����� �������","����� �������") +" �� ������� ������ ������� ���� �������"+ GetSexPhrase("","�") +" �� ������� " + sTemp + " ����� � ����� �������."+ GetSexPhrase(" ����� �������!","") +"", 
				""+ GetSexPhrase("�������","�������") +", ��� �� �������� " + sTemp + " ����� � ����� ������� �� �������? ������, ��� �� ��� ��� ����� ����������!"), npchar.city, 10, 1, "");
			ChangeCharacterReputation(pchar, 5);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sTitle = sld.id + "Church_DestroyGhost";
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader(sTitle);
			
			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			
			DeleteAttribute(npchar, "quest.DestroyGhost");
			//#20170727-01 Bug fix church skeleton quest infinite reputation
			//Attribute set in SetSkeletonsToLocation, QuestsUtilite.c
			DeleteAttribute(npchar, "DestroyGhost");
		break;
        //<<--- ��������� �������
		//--->> ������ ������
		case "NightChurch_1":
			dialog.text = "������ ���. � ������ ���, ��� ��� ���������. ����� ���������� ����� ����, �� ��� �������� ������ ��������� ��������� ����������. ���� �� �����, ����-�� ������������ ��������� ������\n�� ���, �� ������"+ GetSexPhrase("��","��") +" �������� ��������� ����� � ������?";
			link.l1 = "���, �������, ��������, ������ ����. ����� ���� ��������.";
			link.l1.go = "exit";
			link.l2 = "� ��������, � ������"+ GetSexPhrase("��","��") +". �� ������� ����� ��� ���� ����� �������� �������? �����, ����� � �� ��������, � ���� �������� ���� - ������� ����������, ������� ������ ���������� �� ����� ��������� ���� ����������� �������.";
			link.l2.go = "NightChurch_2";
		break;
		case "NightChurch_2":
			dialog.text = "��, ����� � ���, �� ��� ������������. � �����, ���� ����� ����� ���������� ����� ��� ����. ���� ����� ��� � �� ��������, �� ����� �������, ��� ���� ������ ��������� �������.";
			link.l1 = "��� ��, ��� ���� ����������. � ������"+ GetSexPhrase("��","��") +"!";
			link.l1.go = "NightChurch_3";
		break;
		case "NightChurch_3":
			dialog.text = "����� ��������� � ����������� ����. � �����, ��� �� ����"+ GetSexPhrase("��","��") +" ��������� � ������ ���������� � �������� �� ����� ����.";
			link.l1 = "����, ������ ����. ��� ���� ������ ���� �������� �� ���� ������.";
			link.l1.go = "exit";
			pchar.questTemp.different = "Church_NightGuard";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //����������� ���������� �� ���������� 
			pchar.questTemp.different.Church_NightGuard = npchar.location; //���� ������������ ���� �����
			pchar.questTemp.different.Church_NightGuard.NightQty = 0; //���-��� ������������ �����
			pchar.questTemp.different.Church_NightGuard.chance = rand(3); //������ �� ��������� ����������
			pchar.questTemp.different.Church_NightGuard.fight = false; //���� ������
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //������� ����
			sTitle = npchar.location + "Church_NightGuard";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_NightGuard", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "NightGuard_result":
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0)
			{
				dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", �� ��� �� ��������"+ GetSexPhrase("","�") +" �� ����� ����. ���, �������� ���� ������, �� ����� ���...";
				link.l1 = "������, ������ ����.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) > 0 && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", �� �� ��������"+ GetSexPhrase("","�") +" ������ �� �����, �� �������������� � ���� �����...";
				link.l1 = "��, � �����... �������� ���������.";
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
			{
				if (sti(pchar.questTemp.different.Church_NightGuard.fight))
				{
					dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", ��� ��� �������� � ���, ��� �� �����"+ GetSexPhrase("","�") +" ������� ��������� �����. � ���� �������� � ������ ����� �������� - ����, �� ������� �������� ���� ���.";
					link.l1 = "�������, ������ ����...";
					link.l1.go = "NightGuard_fight";
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", �� ������ ����������"+ GetSexPhrase("","�") +" � ������ �� �����. ������ ��������� �� �����"+ GetSexPhrase("","�") +"?";
					link.l1 = "���, ������ ����, ��� ���� ��������. ������ �� �����"+ GetSexPhrase("","�") +" ������.";
					link.l1.go = "NightGuard_noLook";
				}
			}
		break;

		case "NightGuard_noLook":
			dialog.text = "��, ������, �� ���������... �� ��� ��, ���������� ���������! � �������� ������� � �� ��������� ���� �����, �� ���� �������, ��� ����� ���� ����� �������� ����� � " + NationNameAblative(sti(npchar.nation)) + " ����� ���������.";
			link.l1 = "�������, ������ ����.";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			
			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddSimpleRumourCity(LinkRandPhrase("�������, ��� �� �������� � ����� ������ �� �����...", 
				"������ ��������� � ������ - ���� �����������. ������� ���.", 
				"��� ������ ����, " + GetFullName(npchar) + ", ��������, ��� �� ����� ������ �� ����� � ����� ������."), npchar.city, 10, 1, "");
		break;
		case "NightGuard_fight":
			dialog.text = "������ �����, � � ����� ��������� ���� ����� ����� " + NationNameAblative(sti(npchar.nation)) + ", ��� � ������. � ���� ��, � ���� �������� �� ���� ��������, �, �������, ����� �� ������������ ���������� ���� ������� ������� ������!";
			link.l1 = "�������� �������, ������ ����!";
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			
			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddCharacterMaxHealth(pchar, 2);
			AddSimpleRumourCity(LinkRandPhrase("�������, ��� �� ����� �� ������� �������� � ����� ������! �������� ��� �������!", 
				"�� ������, ��� ������ ������ ���������� ��� �� ��, ��� �� �� ��������� ��������� ����� ������. ������� ���!", 
				"��� ������ ����, " + GetFullName(npchar) + ", ������ � ��� � �������, ��� �� ������ ���� ��������� ������ ��� �����..."), npchar.city, 10, 1, "");
		break;

		//<<--- ������ ������
		//Lipsar ����� ������� ������ ������
		case "LukePoison":
			dialog.text = GetSexPhrase("��� ���","���� ���") +", ��� ��� ���� ���������... ������� �������! ��� �� �������� ���� ��, � ������� � ����� �� �����������. ���� ����� ������ ����� ����, ��� ������� ����, ����� ��� �������� �� ���������� �������!";
			link.l1 = "����� ����, �����, ��� �� �� ������ ��� ������.";
			link.l1.go = "exit";
			if (NPChar.City == "Bridgetown")
			{
				dialog.text = GetSexPhrase("��� ���","���� ���") +", ��� ��� ���� ���������... ������� �������! � ����, ��� ��� �� ��! �� ����� ������, ����� ���������� �������� �������! � ������ ����.";
				link.l1 = "���� �� �� ���?! � � �������� ����� ���� ������!";
				link.l1.go = "exit";
				AddDialogExitQuest("HealingPoison");
			}
		break;
        case "healthAdd_1":
            if (GetHealthMaxNum(pchar) == 6) // �������
            {
                dialog.text = "�������� ���� " + GetHealthNameMaxSmall(pchar) + ", � ���� ������� ����. ����� ������ �������� ������������� � �������� ��� ��������.";
    			link.l1 = "�������, ����������. ���������� ��������� ����� �� ����������� � �����.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "�������� ���� " + GetHealthNameMaxSmall(pchar) + ", � ���� ���� ������� ����, ���� �� �������� ��� ���������.";
    			link.l1 = "��� ��� ����� �����?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "� ������ ������ ��� �������� ��������?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "����� ������, "+ GetSexPhrase("��� ���","���� ���") +", �� ��������� ����, ����� ���� �����. ��� �� �������� ���������, �������� ���� ����������� ������ �����, � � ���������� �� ����������� ����"+ GetSexPhrase("","�") +" � ��������� ��� �� � �����.\n ������� ����, ���� �������� ������, ������ � ���� ��������. �� ���� �� ��������� ����� ���������� � ������ ������ �������� �������������. ������������� ����� � ����������� ������� ������� ���������� ������ ������ ���.";
			link.l1 = "�������, �� ���� ����������.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "������� � ����� �� �������, "+ GetSexPhrase("��� ���","���� ���") +". ����� ������� ������ ���� ��������� �����.";
			link.l1 = "� �� �� ����� �� ��������� �� ����?";
			link.l1.go = "healthAdd_3";
			link.l2 = "�� ���� - �����? ��.. ����������, �������.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "�? �������, ��� ��������. �� ���� ��������� ������ �������� � ��� ������.";
    			link.l1 = pcharrepphrase("�������?", "� ��������! ����� ��� ������?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "� �� ���-������ ���"+ GetSexPhrase("","�") +"...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", � ��� ������ � ����� ������������. ������� ������ ��� ��� ����� �� ����� ������.";
    			link.l1    = "�������, "+RandPhraseSimple("�����.", "������ ����.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "��� ����� ������� ����� ������ ����������� ������ �� ���� ���������.";
			link.l1 = pcharrepphrase("�������!!! �� �� � ���� ���?! � ������� ����� �����, ����� ��������� ���� �������.", "��� ���� ��� ������� �����. ����� ������ ������� - �������� �� ������ �� ������.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "� ������"+ GetSexPhrase("��","��") +"!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // ����� �� ���������, �� ���� ������ 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "������. ���� �������� ������� ���������. �� ���� ����� �������� ������ � ������ ����, ����� ������ ������ �� ���. ��� ����� ����� ����� �������� � �������� � ����� ������� ����.";
			link.l1 = "�������. ���� ���, � ����� ����� ����� �����.";
			link.l1.go = "exit";
		break;
		// ������ ��� �������� �� ������
		case "Prison_Temp":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "��� �� � ��� ����� ��������.";
			link.l1 = "�� � �� �����.";
			link.l1.go = "Exit";
		break;

		case "Prison_Cell":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = "��������� ����, �� ������ �� �� �������� � ������ �����, �������� ���� � ��������� ������ ����?";
			link.l1 = "� ��, ����������, ���?";
			link.l1.go = "Prison_Cell_Info";
			link.l2 = "� ����������� � ���������, �����.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "�������� �����, �������.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info":
			dialog.text = "� ������� ��������, �������� ������ �������, ��������� �� � ������� ����� ���������� ��������� ���������, ��� ���������� ����� ������ ������� �� �������.";
			link.l1 = "� ������ ����� ����� ������� � ��������� ������?";
			link.l1.go = "Prison_Cell_Info_2";
			link.l2 = "� �����"+ GetSexPhrase("","�") +" ���������, �����.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "� ���������� �� �����"+ GetSexPhrase("��","��") +". ��� ��� ��� �� �����.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info_2":
			dialog.text = "�������, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� �������� �� ��������� ���������, ������ �������� �������� ������ �������. �����"+ GetSexPhrase("","�") +" �� �� �������� � ����� ������?";
			link.l2 = "� �����"+ GetSexPhrase("","�") +" ���������, �����.";
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = "� ���������� �� �����"+ GetSexPhrase("��","��") +". ��� ��� ��� �� �����.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_None":
			dialog.text = "�������� � ����� � �������������� ������� �� �������� ���� � �������� �����. ��������� � �������!";
			link.l1 = "� ���������, ��� ��� �� �����. ������ �����!";
			link.l1.go = "Prison_Cell_death";//"Exit";
			//AddDialogExitQuest("MoveToPrison_Cell");
		break;

		case "Prison_Cell_Talk":
			dialog.text = "� ������ ����, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l2 = "� ����"+ GetSexPhrase("��","��") +", �����, ������ ��������� �� ���� �����, � ������"+ GetSexPhrase("","�") +" � ������"+ GetSexPhrase("","�") +" ��������, �� ����������"+ GetSexPhrase("","�") +" � �� ��"+ GetSexPhrase("��","��") +". ��� �������� ������ ���������. �� ������ �������� �� �� ���� ��������?";
			link.l2.go = "Prison_Cell_Talk_2";
			link.l3 = "� ���������"+ GetSexPhrase("","�") +". �������� ����.";
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Talk_2":
			dialog.text = "��� �� ��� � ������� ������������? � ������� ���� ����������� ����� �������� ������? �� ������ �����! � ������� ���� ���������� �� ����� ���������.";
			link.l1 = "�� � ����� �� ��, � ��� ���� �������!";
			link.l1.go = "Prison_Cell_death";
		break;

		case "Prison_Cell_death":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   			sld = &Characters[sti(PChar.GenQuest.ToPrisonCmdIdx)];
			// to_do DeathExecutionStart(Pchar, sti(sld.nation));
		break;
		//����� ������������� ������� �������
		case "HostessChurch":
			dialog.text = "� ��� �� ��� ������ ����, ��� ��������?";
			link.l1 = "��... ��� ������� �������� �������.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "� �� �������"+ GetSexPhrase("��","��") +" �� �������� ����. ���� ����� �� ���� ��������� �������������!";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //���� �� �����������
		break;
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //������ ������ �� �����
				{
					dialog.text = "���"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("�","��") +", ��� �� �������� � �������? � ����� ���� �������"+ GetSexPhrase("","�") +" �� �����, ���� ��� �� ����� �������� ����������!";
					link.l1 = "��� �����. �������, ������� ����� �������� �� ���... ��� ��� ������ �������������?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "�����, ������!!! ������� ���� ���������� ������ � �������� ������!";
					link.l1 = "������ ����, ��� �� ���?! �� � ��� �� ���� �����, � ��...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //������ ������ �� �������
				{
					dialog.text = "� ���, ��� �� ��������� ��������� ������� ���� � ������� ������. �� ��� ���� ��������� �� �������!";
					link.l1 = "��� ���� �� �������! ��� ��� ������ �������������?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "� �� ���� ������� ������, ������� �� �����. ����� �� ���� ��������, "+ GetSexPhrase("��� ���","���� ���") +". ����� ������ ���� � ������� �� ��������.";
					link.l1 = "����� ����, ��� �� ���������� ��. ����� ����...";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "����� ��� ������, ���� �� ����, �� ���� ���...";
				link.l1 = "��, �����, ������ ���. ������� ������������� �� ������� ������!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "����� ��� ������, ���� �� ����, �� ���� ���? �� � ��� ���"+ GetSexPhrase("��","��") +"?! � �����, �� ���� ������� - �����!!";
				link.l1 = "������ ����, �� ���� ������� - �����...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "� �������� ���, "+ GetSexPhrase("��� ���","���� ���") +". �����, ������ �������� ��� ��������.";
			link.l1 = "������, �����. �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//���� ������� ��� ��������� ������� ����
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_ok_1":
			dialog.text = "� �������� ���, "+ GetSexPhrase("��� ���","���� ���") +". ������ �������� ���������.";
			link.l1 = "������, �����. �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//���� ������� ��� ��������� ������� ����
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_bad":
			dialog.text = "��������, ������� ���!!! � �� ���� ������������ ��� �� �����!";
			link.l1 = "���, �� ������.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//���� ������� ��� ��������� ������� ����
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_1":
			dialog.text = "������ ��� �������. ��� � �����, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l1 = "��������, �����.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//���� ������� ��� ��������� ������� ����
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_2":
			dialog.text = "��� �� ��� �������, ��������"+ GetSexPhrase("��","��") +"! �������� �� ����� � �� ����������� ��� �� �����!";
			link.l1 = "���? �� ����������, ����...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//���� ������� ��� ��������� ������� ����
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		//������������ �����. ����� ����� � ��������
		case "MC_CaracasChirch":
			dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", ������� ������� ���������. ���������, ����� � �������� ���������� �� ���� �������� ������ ����������. ��� ������� ��������, ���� ������� ������� �� ����� �������. ��� �� �����, ����� �����������?";
			link.l1 = "�� ���� �� � ������ �� �������? �������: ���"+ GetSexPhrase(", �������,","") +" ���������� ������� � ������� ����������!";
			link.l1.go = "MC_CaracasChirch_1";
		break;
		case "MC_CaracasChirch_1":
			dialog.text = "�� ����������, "+ GetSexPhrase("��� ���","���� ���") +". ���� ��� ���� �������, �� ��� ������� � ���! �� ���� � ��������� ������� ���\n�������, ���� ������ ���������. ����������� ������� �� ������ ����� � ���� �����. ���� �� ��������� ��� ����, � �� ������� ��� ���� �������� - �������, � �� ������ ��� � ��������.";
			link.l1 = "� ������� ���!";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toCaracasTavern";
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.lifeDay = 0;
			}
			//��� �� ������
			locations[FindLocation("Caracas_town")].hidden_effects = true;
		break;

	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	//string sColony = FindNonEnemyColonyForAdventure(GetCityNation(PChar.GenQuest.ChurchQuest_1.QuestTown), PChar.GenQuest.ChurchQuest_1.QuestTown, true);
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// ���� ����� ����� �� ��������... ����� ����� ����� � ������, ���������� � ����� ������.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2� (������ ������� � ���������� ��������)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2�-� (����� ����. � ��� ���� ������ ����).");
		break;
		
		case "2": // ���� ���� ��� �� ���������, �.�. ���� ��� ���, ��� ����, ��-������ ���� ����
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("��������� ��������� 1: �������� ����� - 2�-� (����� ����. �������� ���� ����������.)"); 
		break;
	}
}
