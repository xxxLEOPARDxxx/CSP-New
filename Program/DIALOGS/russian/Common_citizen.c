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
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // �����
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
		
		if (grandfathershit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
		if (grandfatherisashiteater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
		if (grandfatherhater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("�����? ������!!!!!", "������! � ������ ����!");
				link.l1 = "��������! � ��� �����.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // ��� ���������
				{
				    dialog.text = RandPhraseSimple("����� ����, ��� �� � ���� ������"+ GetSexPhrase("��","���") +" ����� ������, "+ GetSexPhrase("���","����") +".", "����� �������� �������, ���"+ GetSexPhrase("","�") +" ����� ������ �������"+ GetSexPhrase("��","���") +" �� ��� � ��������.");
					link.l1 = RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +". �����!", "������ ���������� �����. �� ��������.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
					link.l2.go = "quests";//(���������� � ���� ������)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("���� �������� ���������� ����.", "���������� ��������...");
							link.l3.go = "LoanForAll";//(���������� � ��������� ���������)
						}
					}
					break;
				}
				else
				{ // ������, �� ����
				    dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
					link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("���� �������� ����.", "������� ��������, ����� ���� ������.");
					link.l2.go = "quests";//(���������� � ���� ������)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("���� �������� ���������� ����.", "���������� ��������...");
							link.l3.go = "LoanForAll";//(���������� � ��������� ���������)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("���� ����� ", "��� ��� ", "������ �������� ���� ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". ���� ���� �����?", ". � ���� ������ ����� �� "
                                +NPCharSexPhrase(NPChar, "�����", "������")
                                +", ��� �� ���"+ GetSexPhrase("��","��") +"?", ". ��� �� � ��� ���� �� ���� ����?"),

        		                LinkRandPhrase("����������� ���, " + GetAddress_Form(NPChar) + ". ��� ��� " + GetFullName(npchar) + ". � ��� ����� ���?",
                                 "������������, " + GetAddress_Form(NPChar) + "! � " + GetFullName(npchar) + ". ���� � ������ ���� ���?",
                                 "��, " + GetAddress_Form(NPChar) + ". ��� �� ������? ������, ���� ����� " + GetFullName(npchar) + ". � ���?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("������� ���� ����! ", "������ ������! ", "���� ���� ����� ����! ") + "�� � ������� "+ GetFullName(Pchar)+ LinkRandPhrase(", �� ����� �� ������"+NPCharSexPhrase(NPChar,"","�")+" ��� ���"+NPCharSexPhrase(NPChar,", �������?","?"), " � "+ GetSexPhrase("����� ��������� �����","����� ��������� �������-�����") +" � ���� �����! ", " � ����������� ��� �� ���� �����, ���� ��� �� ���!"),
                                LinkRandPhrase("� " + GetFullName(Pchar) + ", �������.", "���� ����� " + GetFullName(Pchar) + ".", "������ �������� ���� ������� " + GetFullName(Pchar)));

                //LinkRandPhrase("� " + GetFullName(Pchar) + ", �������.", "���� ����� " + GetFullName(Pchar) + ".", "������ �������� ���� ������� " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "�������, �� �� ����� �� ������ ��� � ����� ����?";
					link.l1 = LinkRandPhrase("������, ���. � ���� ������ ����� ���� �������.", "������, �� ����. ����...", "���, �� ����. � ���� ������ ����� ����� ������ ���.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("�������. ��� �� ����?", "��, ������. ���������� ���, ��� ��� �� ����...", "���������� ��� �� ���� ���� �����������...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "�� �������, � ��� ������.";
					link.l1 = NPChar.name + ", � ���"+ GetSexPhrase("��","��") +" ���� ����������� ������.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("�����"+ GetSexPhrase("","�") +" ���-��� ������ �� ���� ���������!", "�����"+ GetSexPhrase("","�") +" ������ ���-��� � ������.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// ���������  "��������� ���������"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(���������� � ���� ������)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("���� �������� ���������� ����.", "���������� ��������...");
						link.l3.go = "LoanForAll";//(���������� � ��������� ���������)
					}
				}
				// --> ��������� ��������� ����, ����� ����� �� �����. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
						"���������� ����! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
						"������, ��������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������."), 
						LinkRandPhrase("�������, ������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
						"�������, � ����"+ GetSexPhrase("��","��") +" ��� ���������! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
						"������, ���������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������..."));
					link.l4.go = "SitySpy";
				}
				// <-- ��������� ��������� ����, ����� ����� �� �����
				
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("�� � �����", "�� ������", "�� ������ ���-������ � ���") + ", ��� ������� ���� ��������� ������� �������?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- ��������� ��������� ����������. ����� �2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("�, ��� �� "+GetFullName(Pchar)
                        +" "+ GetSexPhrase("- ������ ��������","- ��������� ������") +"", "��� ���� ������, "+ GetSexPhrase("�������","���������") +" "
                        + Pchar.name, "�, �� ��� �� "+ GetSexPhrase("��� �������","����") +" "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(". �����, ���� ��� ��� �� ���� �����!", ". �, ��������, "+ GetSexPhrase("��� ������ ����.","��� ������ ��������.") +"", ". �, ��� ����, ��� �� �������!")
                                        +LinkRandPhrase(" ��, ������, ���� ���� �����?", " ���� ���� �� ���� ���?", " ����� ��������� ���� �� ��������?"),
                                        LinkRandPhrase(TimeGreeting() + ", ������� ", "������������, "+GetAddress_Form(NPChar)+" ", "����������� ���, ������� ")+GetFullName(Pchar)
                                        +LinkRandPhrase(". ��� ����� ���� ����� "+ GetSexPhrase("������ ���������� ��������","����� ������ �������") +", ��� ��, �� ����?", ". ����� �� ������?", ". ��� �� ���� ��� �� ������ ������?")

                                        ),
                                        
                        PCharRepPhrase(LinkRandPhrase("������������, ������� ", "�����������, �� ��� �� "+GetAddress_Form(NPChar)+" ", "�, ������� ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", � �����"+NPCharSexPhrase(NPChar, " ", "� ")+"�� ������ � ���� �� ����������,",
                                                         ", �� �����, ��� ���"+NPCharSexPhrase(NPChar, " ", "� ")+"��� ������, ��", ", ����, �� ��� ����, ����������, �")
                                        +LinkRandPhrase(" ��� ��� �����?", " ����� �� ������?", " ��� ���� ���� "+NPCharSexPhrase(NPChar, "�������?", "�������?")),
                                        LinkRandPhrase(TimeGreeting() + ", ������� " + GetFullName(Pchar) + ". ��� ���� ������?",
                                        "�, �� ��� �� ���"+ GetSexPhrase("","�") +" ������� " + GetFullName(Pchar) + "! ��� �� ������ ������ �� ���� ���?",
                                        "������������, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". �� ���-�� ������?"))
                                        );                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ �"+ GetSexPhrase("��","��") +" � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "����� �������?";
			link.l1 = "��� ������ �� ������� ��� � ���� �������?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("��� ��� ���� �� ���������� �����, �� � ������ � �� ����. �������� � ����������, ��, �������, � ����������� ������� ������.",
										"������� �� ���� � ��� �� ��������, ������������� ��� ������� ����� ������, ������� " + GetFullName(Pchar) + ".", 
										"���� �� ���� ��� ��� ������, ������� " + GetFullName(Pchar) + ". ���������� ���������� � ����������, ����� �� �����?");
			link.l1 = "� ������������� ������������ ����� �������!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("� �� �� �����, ������� " + GetFullName(Pchar)+"?",
                                                                    "� ��� � ���� " + PChar.name+"?",
                                                                    "� ������� ����, " + GetFullName(Pchar)+".")
                                                                     + " � ������ ������, ���� ���� ����?",
                                                    LinkRandPhrase("������� �������������, ������� " + PChar.name,
                                                                    "���"+NPCharSexPhrase(NPChar, " ", "� ")+" ������ ����������, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "����� �������, ������� " + PChar.name) + ". �� ���� �� �� ������ ������ ������ ��� ���, �� ��� ��?");

            link.l1 = PCharRepPhrase("�����"+ GetSexPhrase("","�") +" ���-��� ������ �� ���� ���������!", "�����"+ GetSexPhrase("","�") +" ������ ���-��� � ������.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// ���������  "��������� ���������"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(���������� � ���� ������)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("���� �������� ���������� ����.", "���������� ��������...");
					link.l3.go = "LoanForAll";//(���������� � ��������� ���������)
				}
			}
			// --> ��������� ��������� ����, ����� ����� �� �����. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					"���������� ����! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
					"������, ��������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������."), 
					LinkRandPhrase("�������, ������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					"�������, � ����"+ GetSexPhrase("��","��") +" ��� ���������! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
					"������, ���������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������..."));
				link.l4.go = "SitySpy";
			}
			// <-- ��������� ��������� ����, ����� ����� �� �����
			// ��������� ��������� ����������. ����� �2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("�� � �����", "���� ���-������ �������� � ���", "�� ������ ���-������ � ���") + ", ��� ������� ���� ��������� ������� �������?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- ��������� ��������� ����������. ����� �2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ �"+ GetSexPhrase("��","��") +" � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("�, �� � ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ����, ��� �������, ���������, ���� ������.", "������ ���������, �������? ��� �, � ����... �������� �� ��������� ����.", "��, " + PChar.name + "?"),
                                        LinkRandPhrase("��, ���� ���� ���?", "����, ������� "+PChar.name+", �� ������"+ GetSexPhrase("�","��") +" ���������? ", "�������"+ GetSexPhrase("","�") +" ���������, �������, ����� �� �������"+ GetSexPhrase("","�") +" �����.")),
		                PCharRepPhrase(LinkRandPhrase("��� �� ������ ������ "+ GetAddress_Form(NPChar) + "?", "� ��� ������ �������.", "��� ����� ����, ������� ����������� ������, �������."),
                                        LinkRandPhrase("������ ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ��������� �����������, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". ��������.",
                                                        "��, " + GetAddress_Form(NPChar) + "?",
                                                        "������ ���������, �������? ��� �, � ����..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("����� ����� � ���� � ������� �������?",
                                    "��� ���������� � ���� �����?",
                                    "��� ����� ����� �� ����?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("�� ��������� ��� ������?", "���-�� � ����� �� ����� ������ ���-����...", "���������� ������...");
			link.l2.go = "town";  //(���������� � ���� ������)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("���� ������, ��� ��� ������� �� ����� ��������.", "�� ������, ��� ������� ��� �� ����� �������?", "�������� �� ������ ���-��� � ������� �������.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(���������� � ���� ������)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. ������ ��-������� - � ������ ������� ������ ����� ���� ������.
				}
			}
			else
			{
				link.l3 = "���������� ��� � ����� �������.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("���� ������ ����!", "� ���� � ��� ����.");
			link.l4.go = "quests";  //(���������� � ���� ������)
			link.l5 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ �"+ GetSexPhrase("��","��") +" � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "� ��� �� ������� �� ������ ������?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "� �����������.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "� ������� ������� �������.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "� ������� �����.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "� ������� ������� ��������.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "�� � ���. ������.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "�������.";
			link.l1.go = "exit";
			// ����� ����� ������ �������� �� �������, ����� ���� �����
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("������ ������, � �� �������-�� ���������� � ����. �� ���-��� ���� ����������.",
                           "��� �� ��� ���������� � ����� �������?", "������ ����������. � ��� �� ������ ��������?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "��� ��� �� �����?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "��� �� ������ � �����, ���������� �����?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "��������� � ���-������ ������.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "�, �� �� �����������? ��� ������? ���������� � ������ ���� ������.";
			link.l1 = "�����, �����.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "������ ��� ��� �� ����.";
			link.l1 = "����.";
		    link.l1.go = "exit";
		break;
		//============================ ��������� ����. ����� �� ������� ������ �� ����� ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, "��, � � ����� ��� ���? � ������� ������!", "��, � � �� ����� ��� ���? � ���� � ���� ������, � ����� ������ ������ �� �����!"), 
				NPCharSexPhrase(npchar, "��� ����� ��� �� ���� �����? ������� ��� ���, ��� � �� �����!", "� �� �������� ��� ���, ��� � �������!"), 
				NPCharSexPhrase(npchar, "��, ������� �����? ��������� �� ����, � ������� ������!", "�� ��� �� ����� �� ��� ��������� �� ������ ��������� �����������?"), 
				NPCharSexPhrase(npchar, "���, �����?! �� ��� �� � ����� ������ �� �����!!!", "����������, ��������� �� ���� �������, ����� ���!!"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� ����������� ���� �����?", "��, ��������, � ��� ��� ���������"+ GetSexPhrase("","�") +"...",
                      "��������, ������� ������...", "������, ������...", npchar, Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> �������� ��������������
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //������ ����������
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //��� ��� �����
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //������
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //�� ������ ������
			{
				dialog.text = "�� ��� ������! ����������, ��� �� ���� ��������?! ���� � ��� �����-�� ��������, �� ��������� � �����������, � ��� ��������!",
				link.l1 = "��... �������, �� ����� ��� ��������� ���. � ��� ����...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "��� ������ � ���� ������! " + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + " ����� ��� �������, ����� " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], "��", "���") + " � ���� �����.",
				"��, �������, �� ���, ���� �� " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_FormToNPC(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + " �����.");				
			link.l1 = "��� �, ������� ���������...";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //����� �� ���������
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //������� ������� �����
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ���� ������ ����. ����� ������ �� �����, ����� ��������� ==================
		case "SeekSpy_Checking":
			dialog.text = "��, � �����������, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "�� ������������� ������� ������.", "��� ������������� ������� ����������.");
			link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +". ������� �� ������.", "��� ����. ������� �� ������.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// ���� ����� �� ����� ������������ ������ -->
		case "CitizenFindItem_1":
			dialog.text = "���� � ���, ��� � ����� ������������� �� ������� � �������� ���� ����������� ������... "+ GetSexPhrase("�������, �� �� ����� �� �������� ���?","�������, ����������, �������� ��� ��� �����!") +"";
			link.l1 = "������� "+ GetSexPhrase("����! ���� ����� ���������� ������� � ����� ������� ���, ��� ������!","������. ������� ���� �������� ��������.") +"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("���, �� ����. ������. � ���� ����� ����� ���.", "������, �� ����. � ����� ��������"+ GetSexPhrase("","�") +", ��� � ���� ��� �������� ���� �� ����������� ������...", "� ���� ������ ����� ���� �������, ��� ��� ������ � ����� �� �����...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+ GetSexPhrase("�������","�������") +", ��� �� ���������! ����������, ������� ��� ������, ���� ����� " + sti(NPChar.LifeDay) + " ��� ��������� ��� ��� � � �� ������ ��, ����� �� ���� ������ ��� ������������ ������.";
			link.l1 = RandPhraseSimple("��� �� �������, ��� �� ��� ��������?", "��� ��� �� ��� ��������?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "����� �� ���������� ��������...";
			link.l1 = "��, ����� � ���"+ GetSexPhrase("��","��") +" ������...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "��, ��������. � ������������. �������, � ��� ���� ����� " + sti(NPChar.LifeDay) + " ���.";
			link.l1 = "�����.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // �.�. ����� ����������, ��� ��� ����� ����� �� �������. � ��� ���.
			sTemp = "randitem1";
			Log_TestInfo("������ ����� � �������� - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // ��� ������� ����� ������ �� ����
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+ GetSexPhrase("�������","�������") +"! � ��� ����! ��� � ���� ��� �������������?";
			link.l1 = "�� ���� ��������������, � �����"+ GetSexPhrase("","�") +" ��� ���������� �����������.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "��� �� �������� �� �����-������ ��������...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "��, "+ GetSexPhrase("�������, ����� �� ���������� �������","�������, �� ����� �����������") +"! � ����������� �������� �� ��� � ������! �� ��������...";
			link.l1 = "��������, " + NPChar.name + ".";
			link.l1.go = "exit";
			ChangeCharacterReputation(PChar, 1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "�� ��, �������. ��� ��� " + FindRussianMoneyString(iTemp) + ". ��� ���, ��� � ���� ����. �������� ��... � ��������.";
			link.l1 = "�� ��������, " + GetFullName(NPChar) + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- ���� ����� �� ����� ������������ ������
		
		//=================== ���� ������ ����������. ����� ���������� (����� �2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("���, � ������ �� ���� �� ����.", "��� ������ �� �������� �� ����� �������.", "� ������ �� ����.");
					link.l1 = LinkRandPhrase("�����, ������.", "����, �������.", "������, ������.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("� ������ �� ���� �� ����, �� �� ������ ����������� ������������ � ������� - ��� �� ����� ���-������ ��� ���������.", "� ��� ������ ������� �� ����, �������� ����� ����-������ � �������.", "��� ������ ����������� �� ��������, �� � ������, ��� �� ���� ��������� � �������.");
				link.l1 = "������� � �� ���.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//��������� �� ����������� ������
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
