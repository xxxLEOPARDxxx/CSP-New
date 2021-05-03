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
		
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("�����? ������!!!!!", "������! � ������ ����!");
				link.l1 = "��������! � ��� �����.";
				link.l1.go = "fight";
				break;
			}*/
			
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
				link.l1 = PCharRepPhrase("�����"+ GetSexPhrase("","�") +" ���-��� ������ �� ���� ���������!", "�����"+ GetSexPhrase("","�") +" ������ ���-��� � ������.");
				link.l1.go = "new question";
				// ��������� ��������� ����������. ����� �2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l2 = LinkRandPhrase("�� � �����", "�� ������", "�� ������ ���-������ � ���") + ", ��� ������� ���� ��������� ������� �������?");
					link.l2.go = "Citiz_GenQuest_Church_2_1";
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
	   			link.l3 = "������, � ���������" + GetSexPhrase(".","�.");
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
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
			// ��������� ��������� ����������. ����� �2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l2 = LinkRandPhrase("�� � �����", "���� ���-������ �������� � ���", "�� ������ ���-������ � ���") + ", ��� ������� ���� ��������� ������� �������?");
				link.l2.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- ��������� ��������� ����������. ����� �2.
			
			link.l3 = "������, � ���������" + GetSexPhrase(".","�.");
			Link.l3.go = "exit";
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
			link.l2 = "������, � ���������" + GetSexPhrase(".","�.");
			link.l2.go = "exit";
		break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "�������.";
			link.l1.go = "exit";
			// ����� ����� ������ �������� �� �������, ����� ���� �����
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
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

		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� "+ GetSexPhrase("���, ��������! ������, ����� ���","�������! ������, ����� ��") +"!!!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ����� "+ GetSexPhrase("����","�������") +"!!!", "������! ������!!! ����� "+ GetSexPhrase("����","�������") +"!!!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}
