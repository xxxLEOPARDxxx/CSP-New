
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":

            		if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,
                                LinkRandPhrase("���� ����� ", "��� ��� ", "������ �������� ���� ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". ���� ���� �����?", ". � ���� ������ ����� �� "
                                +NPCharSexPhrase(NPChar, "�����", "������")
                                +", ��� �� �����?", ". ��� �� � ��� ���� �� ���� ����?"),

        		                LinkRandPhrase("����������� ���, " + GetAddress_Form(NPChar) + ". ��� ��� " + GetFullName(npchar) + ". � ��� ����� ���?",
                                 "������������, " + GetAddress_Form(NPChar) + "! � " + GetFullName(npchar) + ". ���� � ������ ���� ���?",
                                 "��, " + GetAddress_Form(NPChar) + ". ��� �� ������? ������, ���� ����� " + GetFullName(npchar) + ". � ���?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("������� ���� ����! ", "������ ������! ", "���� ���� ����� ����! ") + "�� � ������� "+ GetFullName(Pchar)+ LinkRandPhrase(", �� ����� �� ������"+NPCharSexPhrase(NPChar,"","�")+" ��� ���, "+NPCharSexPhrase(NPChar,"�������?","?"), " � ����� ��������� ����� � ���� �����! ", " � ����������� ��� �� ���� �����, ���� ��� �� ���!"),
                                LinkRandPhrase("� " + GetFullName(Pchar) + ", �������.", "���� ����� " + GetFullName(Pchar) + ".", "������ �������� ���� ������� " + GetFullName(Pchar)));
                                Link.l1.go = "Meeting";
			}
			else
			{		    
				dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("� �� �� �����, ������� " + GetFullName(Pchar)+"?",
                                                                    "� ��� � ���� " + PChar.name+"?",
                                                                    "� ������� ����, " + GetFullName(Pchar)+".")
                                                                     + " � ������ ������, ���� ���� ����?",
                                                    LinkRandPhrase("������� �������������, ������� " + PChar.name,
                                                                    "���"+NPCharSexPhrase(NPChar, " ", "� ")+" ������ ����������, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "����� �������, ������� " + PChar.name) + ". �� ���� �� �� ������ ������ ������ ��� ���, �� ��� ��?");
				link.l1 = PCharRepPhrase("����� ���-��� ������ �� ���� ���������!", "����� ������ ���-��� � ������.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
				link.l2.go = "quests";//(���������� � ���� ������)
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

            	link.l1 = PCharRepPhrase("����� ���-��� ������ �� ���� ���������!", "����� ������ ���-��� � ������.");
			link.l1.go = "new question";
            		Link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
			Link.l2.go = "quests";
			
			Link.l5 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ ��� � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			Link.l5.go = "exit";
			NextDiag.TempNode = "Meeting";
		break;
		
		case "new question":
            		dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("�, �� � ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ����, ��� �������, ���������, ���� ������.", "������ ���������, �������? ��� �, � ����... �������� �� ��������� ����.", "��, " + PChar.name + "?"),
                                        LinkRandPhrase("��, ���� ���� ���?", "����, ������� "+PChar.name+", �� ������� ���������? ", "������� ���������, �������, ����� �� ������� �����.")),
		                PCharRepPhrase(LinkRandPhrase("��� �� ������ ������ "+ GetAddress_Form(NPChar) + "?", "� ��� ������ �������.", "��� ����� ����, ������� ����������� ������, �������."),
                                        LinkRandPhrase("������ ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ��������� �����������, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". ��������.",
                                                        "��, " + GetAddress_Form(NPChar) + "?",
                                                        "������ ���������, �������? ��� �, � ����...")));

            		link.l1 = RandPhraseSimple("���� ������ ����!", "� ���� � ��� ����.");
			link.l1.go = "quests";
			link.l2 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ ��� � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			link.l2.go = "exit";
		break;
		
		case "quests":
            		dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� ���������...", "������ ��� �� � ��� ��������");
		    	link.l1.go = "exit";
		break;


		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, ��������, ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� ������� ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����.", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;




		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
