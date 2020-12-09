
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTermsValidity;
	
	int iNation;
	int LicenceValidity;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;	
		case "exit_over":			
			npchar.lifeDay = 0;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;	
		case "good_all":
			dialog.text = NPCStringReactionRepeat("���" + NPCharSexPhrase(npchar, "","�") + " ������ ��� �����. �� ���-�� ��� ������?", 
				"�-�, ����� ��? ������� � ��� ��� ��� ��������. ���-�� ����������?", 
				"��, �����, ������ ��������� ��� ��� ����?!",
                "��-�-�, ������ ��� �� ����� ����������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���, ������ ������...", 
				"���, ��� ���������.",
                "��, �������, ������...", 
				"��, �� ��� �� ���, ���������� � ���� ��� ����. ������� ��!", npchar, Dialog.CurrentNode);
			link.l1.go = "Exit";
			NextDiag.TempNode = "good_all";
		break;
		case "All_disagree":
			npchar.lifeDay = 0;
			NextDiag.TempNode = "All_bye";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "All_bye":
			dialog.text = "� �� ����� � ���� �������������, ��������.";
			link.l1 = "���, �� � �� ����.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "All_bye";
		break;
		//================================== � ���� �� ������ ======================================
		case "PortSpein":
			NextDiag.TempNode = "PortSpein";
			dialog.text = "������������, �������. �� ������ ���������� � ���, ��� ���, ��� ��������, ����������?";
			link.l1 = "���, �� ����.";
			link.l1.go = "exit_over";			
			link.l2 = "� ������ �� ������, ��� ����� ���� ��������������?";
			link.l2.go = "PortSpein_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortSpein_1":
			dialog.text = "�����, " +  GetAddress_Form(NPChar) + ", ��� ����� ��������...";
			link.l1 = "���, �� �����, ���������.";
			if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
			{
				link.l1.go = "PortSpein_2";
			}
			else
			{
				link.l1.go = "PortSpein_2_pistol";
			}
		break;
		case "PortSpein_2":
			dialog.text = "�������, ��� ��� ����� ��������� ����... ����, ��� �������.";
			link.l1 = "���������.";
			link.l1.go = "PortSpein_3";
		break;
		
		case "PortSpein_2_pistol":
			dialog.text = "�������, ��� ��� ����� ��������� ���������� � ��������������� ����� ����� ������ ������.";
			link.l1 = "���������.";
			link.l1.go = "PortSpein_3_pistol";
		break;
		
		case "PortSpein_3":
			dialog.text = "����� ������. �� � ������ ���� ������, ��� ��� ���� ������� ������ ����, ��� ������ ����� �� ������������� - � ������ ��� ������ ��������. ������� � ��������� ��� �������� �� ���� ������, ����� � ��� ������, ������������� �� �� �"+ GetSexPhrase("��","�") +", ��� ��� ���"+ GetSexPhrase("��","��") +". ��������?";
			link.l1 = "���... ��, ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "PortSpein_4";
			link.l2 = "����� ����-������ ������� � ���� � ��� ������. � - ���.";
			link.l2.go = "All_disagree";
		break;
		
		case "PortSpein_3_pistol":
			dialog.text = "����� ������. �� � ������ ���� ������, ��� ��� ���� ������� ������ ����, ��� ������ ����� �� ������������� - � ������ ��� ������ ��������. ������� � ��������� ��� �������� �� ���� ������, ����� � ��� ������, ������������� �� �� �"+ GetSexPhrase("��","�") +", ��� ��� ���"+ GetSexPhrase("��","��") +". ��������?";
			link.l1 = "���... ��, ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "PortSpein_4";
			link.l2 = "����� ����-������ ������� � ���� � ��� ������. � - ���.";
			link.l2.go = "All_disagree";
		break;
		
		case "PortSpein_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "� ����� ������, �������� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";	
		break;
		case "PortSpein_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "���������� �����! �� ������������� "+ GetSexPhrase("������� ���","������������ � ������� ����, �������") +".";
				link.l1 = "���, ��� ��! ������, ��� ��� � ���� �� ������.";
				if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
				{
					link.l1.go = "PortSpein_ok";
				}
				else
				{
					link.l1.go = "PortSpein_ok_pistol";
				}
			}
			else
			{
				dialog.text = "����� ��������. �����, ��������� � ������� ���������� �����?";
				link.l1 = "��, �������� ��� ���.";
				link.l1.go = "PortSpein_5";
				link.l2 = "���, � �� ���� ������ �� ���� ������.";
				link.l2.go = "PortSpein_6";
			}
		break;
		case "PortSpein_ok":
			dialog.text = "��� ������ ����� ��������. �������, �� ������� ��� ��� ������ �����. ����� �� ���, �������� ������� ���� ����� - �������� �� ��� � ���� �������� ������. ����� ��� � �������!";
			link.l1 = "�� ��� ��, � �����"+ GetSexPhrase("","�") +" ����. ����� ������!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			GiveItem2Character(pchar, "map_full");
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		
		case "PortSpein_ok_pistol":
			dialog.text = "��� �������� ��������� ������! �� �� �� � ����, � ������ ����, ��� ��� ����� ���������. � ��������� ��������� �� ���� ����� ����� �� ��� ����� �� ����� - ��� � ����� �������� ��� ������. �����!";
			link.l1 = "�� ��� ��, � �����"+ GetSexPhrase("","�") +" ����. ����� ������!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.LaVega_town = true;
			pchar.GenQuestRandItem.LaVega_town.randitem4 = "mushket";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1_1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		
		case "PortSpein_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "����� ������! ����� ������� ���� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_6":
			dialog.text = "����� ����, �� � ����� ������ � �� ���� ������ ��� ��, ��� ��������������� �������� ����.\n�� � ����� ��������� ��� ����� � ������ �����, ���� �� ������� ���� �������. � ���� � ������ ��� ���� ������ ������.";
			link.l1 = "������, ���� ����� ����� - ��������� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortSpein_again";
		break;
		case "PortSpein_again":
			dialog.text = "�-�, ��� � �� �����. ������ �����?";
			link.l1 = "�������, �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "PortSpein_5";
		break;
		//================================== ���������� ======================================
		case "Villemstad":
			NextDiag.TempNode = "Villemstad";
			dialog.text = "������������, �������. � ���� � ��� ���� ��������� ����.";
			link.l1 = "�� ����� �������������.";
			link.l1.go = "exit_over";
			link.l2 = "��� �� ��������! � ��� ��� �� ���� ����� �����������?";
			link.l2.go = "Villemstad_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Villemstad_1":
			dialog.text = "������� �� �������������, � ����� �����������!";
			link.l1 = "��������... ��� ��� �� ���� � ��� �� ���, " +  GetAddress_FormToNPC(NPChar) + "?";
			link.l1.go = "Villemstad_2";
		break;
		case "Villemstad_2":
			dialog.text = "�� � ����� ���� ����� ���� � ������-��������, �� ����� �� ���� �� ������ � ������...";
			link.l1 = "��������.";
			link.l1.go = "Villemstad_3";
		break;
		case "Villemstad_3":
			dialog.text = "��, �� ��������.\n�� ��� ���, ���-����� ��� ���� �������� � ����, � ���� �� ��� �� ��������� ������ ����������� "+ GetSexPhrase("������ ��������","����� ������ �������-��������") +", ��� ��.";
			link.l1 = "�������, ��������. � �����"+ GetSexPhrase("","�") +" ������ � ��� ���.";
			link.l1.go = "Villemstad_4";
		break;
		case "Villemstad_4":
			dialog.text = "��� �� ���������, ��� ������ � ����! �� � �� ����, ����� ��� ������ ��� ����, � ����, ����� ��� ���� ��������� ������ ��������� �������.\n"+
				"������� � ��������� ��� �������� �� ���� ������, ����� � ����� ������������� � ��� ��� � �����������.";
			link.l1 = "��, �� ��� ��, ��������� ���� ������, � �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "Villemstad_5";
			link.l2 = "��� ���, ������ ������. ���, ��������, ��������� ���-������.";
			link.l2.go = "All_disagree";
		break;
		case "Villemstad_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "����� ������. ����, �������, ��� ��� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Villemstad_check";	
		break;
		case "Villemstad_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "�������, ��� ���������� �����!";
				link.l1 = "������� � ���� �� �����... ��, � ������ � ����. ��� ��� �� ������, ��� ��� ����� �����?";
				link.l1.go = "Villemstad_ok";
			}
			else
			{
				dialog.text = "�����������, ��� �������� ����� �� ��� ������. ��������� ����������� ��� ���.";
				link.l1 = "��, �����, �����.";
				link.l1.go = "Villemstad_6";
				link.l2 = "���, �� ����� � � ������� ������.";
				link.l2.go = "Villemstad_7";
			}
		break;
		case "Villemstad_ok":
			dialog.text = "��� �������� ��������� �����. ��� �������� � ����� �� ����� ������ ����� � ������-��������, ����� �� ����������.";
			link.l1 = "�������. �� ��� ��, ������� ���� � ������.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.PuertoPrincipe_town = true;
			pchar.GenQuestRandItem.PuertoPrincipe_town.randitem1 = "spyglass3";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "2");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "Villemstad_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "������. �������, ��� ������� ��������� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Villemstad_check";
		break;
		case "Villemstad_7":
			dialog.text = "�� ������� - ��� ������. ��������, "+ GetSexPhrase("������ �������","�������") +"...";
			link.l1 = "�� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Villemstad_again";
		break;
		case "Villemstad_again":
			dialog.text = "�� ������! ��� ��� ��� �����?";
			link.l1 = "���� ��� ��� ����������� �������� �� ���� �������, " +  GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Villemstad_6";
		break;
		//================================== ����-�-����� ======================================
		case "PortPax":
			NextDiag.TempNode = "PortPax";
			dialog.text = "������������, �������. � ���� ���� ����������� � ���.";
			link.l1 = "�������� ��� ������ �����������.";
			link.l1.go = "exit_over";
			link.l2 = "������ ��� �����������, " +  GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "PortPax_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortPax_1":
			dialog.text = "�� ������, ��� ���������, ��� ��� �������� ����� ��������������� ����� ����, ������� ����� �������� ���������, � ��������. ��, � ��� ��� ��������� �� � ����.";
			link.l1 = "� ���?";
			link.l1.go = "PortPax_2";
		break;
		case "PortPax_2":
			dialog.text = "� ���� ������ �� ���. �� �� ������ ���, � ������ ���� ���� �������, ��� �� ��������� �� �������������, � �� ��������� ������� ���������� ���������.";
			link.l1 = "��, ������� ���, " +  GetAddress_FormToNPC(NPChar) + ", ��� ��� �� ����, � � ��� ��� �����.";
			link.l1.go = "PortPax_3";
		break;
		case "PortPax_3":
			dialog.text = "��� ���� ����� ������� ���������� ��������, ��� �� ��� ��������.\n� ����� ��� ���� ������, � � ������ ����������� ������ �� �������� ���� �������.";
			link.l1 = "���� ������! ��, ��� �� �������� ���� � ������� � ������! ������� � ��� ������ �������, � ���� ������.";
			link.l1.go = "PortPax_4";
		break;
		case "PortPax_4":
			dialog.text = "���, �������, ��� ������ - ��� �����. ��������?";
			link.l1 = "�� ������, �������� ��� ��������.";
			link.l1.go = "PortPax_5";
			link.l2 = "���, ��� ��� �� ���������.";
			link.l2.go = "All_disagree";
		break;
		case "PortPax_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "����� ������. ����, �������, ��� ��� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortPax_check";	
		break;
		case "PortPax_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "���������, "+ GetSexPhrase("�������","�������") +"! ��� ���������� �����!";
				link.l1 = "�����������, � �� ����������... ��� ��� ��� �� ����, � ������� ��� ����?";
				link.l1.go = "PortPax_ok";
			}
			else
			{
				dialog.text = "��, �� ���, "+ GetSexPhrase("�������","�������") +". �� ��������. ��������� ��������� �������.";
				link.l1 = "������� - �� �����. ����� ��������.";
				link.l1.go = "PortPax_6";
				link.l2 = "���, ������ � ����, ��������. � ��� ���� � ������ ������ �� �����.";
				link.l2.go = "PortPax_7";
			}
		break;
		case "PortPax_ok":
			dialog.text = "��� ������������ ������, ��������� ���� ����������� ����! ������� �� � ���������� ��� ��������, � ����� �� �������. �������� ��������.";
			link.l1 = "������, ���� ��. ��������������� ������� ��� - ��� ����� ����� ��� ��������. ������� ����.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Tortuga_Cave = true;
			pchar.GenQuestRandItem.Tortuga_Cave.randitem1 = "suit_2";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "3");
			AddQuestUserData("QuestionsMessages", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "PortPax_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "��? �� �����, �������, ��� ������� ��������� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortPax_check";
		break;
		case "PortPax_7":
			dialog.text = "�� �������? ��, ��������. "+ GetSexPhrase("� ��� ����� ������� ��������� ��������?","������� �������, ��� ������� � ���� ������ ������.") +"..";
			link.l1 = "��, ��, �������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortPax_again";
		break;
		case "PortPax_again":
			dialog.text = "��� ��� �����? �������, �� ��� ��������.";
			link.l1 = "�� ������, �������, � ���� ���������� �����.";
			link.l1.go = "PortPax_6";
		break;
		//================================== ���-���� ======================================
		case "SanJuan":
			NextDiag.TempNode = "SanJuan";
			dialog.text = "����������� ���, �������. ���� ���-��� ��� ����������.";
			link.l1 = "���, ���� ��� �� ����������.";
			link.l1.go = "exit_over";
			link.l2 = "����������� ��� ������, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "SanJuan_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "SanJuan_1":
			dialog.text = "���� � ���� ���� ����� ������ ��������� ����, �������, ��� ��������, ������������ ���.";
			link.l1 = "��� ����� ����������� ��� ������. ��� ��� �� ����?";
			link.l1.go = "SanJuan_2";
		break;
		case "SanJuan_2":
			dialog.text = "��������, � �� ������, �������� ��� �� ������ � �� ������������ ��������. � ������ ��� ����� ������� �������� ��� ��������, ������� � ���� ������������� ��������� � ������� ����.";
			link.l1 = "��� ���? ��, � ��� �� ��� �� ������������ ��������?";
			link.l1.go = "SanJuan_3";
		break;
		case "SanJuan_3":
			dialog.text = "� ���� ������� ��� ��� ������ ����� ����, ��� �� �������� ��� �� ���� ������.";
			link.l1 = "��� ��� �� ������?";
			link.l1.go = "SanJuan_4";
		break;
		case "SanJuan_4":
			dialog.text = "������ �� ����� ���� ��� �����. � ������ ����� ������������ ����, � ��� ���� ����.";
			link.l1 = "�� ������, ������� ���� ������ �� ����� ����.";
			link.l1.go = "SanJuan_5";
			link.l2 = "�� �� ����� �������� ������� � �������� �� �����.";
			link.l2.go = "All_disagree";
		break;
		case "SanJuan_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "����� ������. ����, �������, ��� ��� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";	
		break;
		case "SanJuan_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "�����������, "+ GetSexPhrase("�������","�������") +"! ���������� ���������!";
				link.l1 = "�� ���!.. ��� ��� ��� �� ������������ ��������?";
				link.l1.go = "SanJuan_ok";
			}
			else
			{
				dialog.text = "���, "+ GetSexPhrase("�������","�������") +", ����� ��������. ��������� ���-���� ���� ���������� �����.";
				link.l1 = "��������...";
				link.l1.go = "SanJuan_6";
				link.l2 = "���, ������ � ���� ��������.";
				link.l2.go = "SanJuan_7";
			}
		break;
		case "SanJuan_ok":
			iNation = 5;
			LicenceValidity = 40; 
			for (int i=0; i<4 ; i++)
			{
				if (GetRelation2BaseNation(i) == RELATION_ENEMY)
				{
					iNation = i;
					break;
				}
			}
// -> ugeen fix   31.01.09 (��� ������� � �� �������� � �������� ������ > 40-� ���� ���������� ������ �������� ������ ����� �� 40 ���� (����� ����� ����� ������� !)
// ������ ������ �������� ���������   :  ���� � �� ��������� �������� 50 ����, �� ������ �������� ������� ������ �� 70 ����  			
// ����� ������� �� ������� ( ���� �������, ��� ����������) �� �������� ���������� �� 40 ����
			if (iNation == 5) // ���� �� ����� � ����, �� ������� �������� ��������� ����� ������ 40 ����
			{
				iNation = rand(3);
				GiveNationLicence(iNation, LicenceValidity);
			}
			else // ���� � ��� -�� � ������������  ����������, �� �������� ������� � ���������� ��������
			{
				iTermsValidity = GetDaysContinueNationLicence(iNation); // GetValidityNationLicence(iNation); // fix
				if(iTermsValidity == -1) // �������� ����������
				{
					GiveNationLicence(iNation, LicenceValidity); // ���� ������� �� 40 ���� �� �������
				}
				else // �������� ���� � �� ����������
				{
					LicenceValidity = (makeint(iTermsValidity/10)) * 10 + 20;
				}
			}	
// -> ugeen fix			
			dialog.text = "��� " + GetRusNameNationLicence(iNation) + " ������ �� " + LicenceValidity + " ����! � ������������� ������ �� ���.";
			link.l1 = "���, �������� ������� ��������! �� ��� ��, ������� ���, " + GetAddress_FormToNPC(NPChar) + ", �� ��������� ������. ��������.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
		break;
		case "SanJuan_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "���������. ������ ����� ������ ��������� ��� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_7":
			dialog.text = "��, ������ - ��� ������. ��������, "+ GetSexPhrase("�������","�������") +"...";
			link.l1 = "����� ����� ����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SanJuan_again";
		break;
		case "SanJuan_again":
			dialog.text = "������ ��� �����������, �������. ������� ������ ��������� ������� � �������� �� �������� ������?";
			link.l1 = "��, �������, ��� �������� ���������� �����.";
			link.l1.go = "SanJuan_6";
		break;
		//================================== ������ ======================================
		case "Cumana":
			NextDiag.TempNode = "Cumana";
			dialog.text = "����������� ���, �������! � ���� � ��� ���� ��������� ������. �� �� ������� ��� ������ ��������?";
			link.l1 = "���, �� �����.";
			link.l1.go = "exit_over";			
			link.l2 = "�� ��� �������, ������ ����.";
			link.l2.go = "Cumana_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Cumana_1":
			dialog.text = "����� ������. ����� ���������� ��� ��������� ������. � ���� ���� ����� �������, ������� ����� ��� ��������������.";
			link.l1 = "�����, ��� ��� �� ������� � ������ ����.";
			link.l1.go = "Cumana_2";
		break;
		case "Cumana_2":
			dialog.text = "����� �� ���� � �� ������, ��� ����� ����� �������� ��� �� ���� ������. ���� ����� ����� ����� - ������� ���.";
			link.l1 = "����� �������. � ������ ���� �� �����?";
			link.l1.go = "Cumana_3";
		break;
		case "Cumana_3":
			dialog.text = "���, ������ ���� �����, ������ � ���� ������ ��� ������ ���� ������. � �� ���� ������ ��������� ������� ����� ���������, ������ ������� - �� ��� ���.";
			link.l1 = "��, �������, ��� ��. ����"+ GetSexPhrase("��","�") +" ��������� �����.";
			link.l1.go = "Cumana_4";
			link.l2 = "���, ���, � ��� ��� ���. ������.";
			link.l2.go = "All_disagree";
		break;
		case "Cumana_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "���, �� ���� ������ �� ��� �������� ���������. � ������ ������� ������� ����� ���! �������� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";	
		break;
		case "Cumana_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "�����������! ��� ���������� �����!";
				link.l1 = "������� ����... ��� ��� ��� �� �������, ��������"+ GetSexPhrase("��","��") +" ���������"+ GetSexPhrase("��","������") +" �������� � ������ �������?";
				link.l1.go = "Cumana_ok";
			}
			else
			{
				dialog.text = "����� ����, "+ GetSexPhrase("�������","�������") +". ��� ������������� ����� ����... ����� ��������! ���������� ��� ���?";
				link.l1 = "��������!";
				link.l1.go = "Cumana_6";
				link.l2 = "���, �������...";
				link.l2.go = "Cumana_7";
			}
		break;
		case "Cumana_ok":
			dialog.text = "��� ������, ������ ����������� ����������� ����� ��������� ������ �������. �������� ��� � ����� ���� ����� �����. ���������� ��� ����� - ������ ������. ����������� ��� ��� ���������, � �� ������� ���� ��������. �����, �������!";
			link.l1 = "������, ��� ������������� �������� ������ ��� ����. ������� ����.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore46 = true;
			pchar.GenQuestRandItem.Shore46.randitem1 = "STATUE1";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "4");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "Cumana_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "��, ����� ��������� ������! " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_7":
			dialog.text = "��, �� ������ - ��� ������. ��������, ������� ��������...";
			link.l1 = "����?..";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cumana_again";
		break;
		case "Cumana_again":
			dialog.text = "� ��� ��� ����� �� ����?";
			link.l1 = "� ���� ��� ��� ����������� �������� �� ���� �������.";
			link.l1.go = "Cumana_6";
		break;
		//================================== ���� ����� ======================================
		case "PortRoyal":
			NextDiag.TempNode = "PortRoyal";
			dialog.text = "������ ����, �������. ����������, ��� �������, ��� �� ������ �"+ GetSexPhrase("��","�") +", ��� ��� ���"+ GetSexPhrase("��","��") +"...";
			link.l1 = "� ��� � ��� �� �����.";
			link.l1.go = "exit_over";			
			link.l2 = "� ��� ����, " + GetAddress_FormToNPC(NPChar) + "?";
			link.l2.go = "PortRoyal_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortRoyal_1":
			dialog.text = "� ���� ���������� ��� �����. ���� � ���, ��� � ���� ������� ����, ������� ��� ���������� �� � ����, ��, � ��� ���������� �� �����.";
			link.l1 = "� ��� �� ������ ������?";
			link.l1.go = "PortRoyal_2";
		break;
		case "PortRoyal_2":
			dialog.text = "������ ����������. � ���� �����, ��� ��� ���� � �������� �����.";
			link.l1 = "�� ��� ���� - ��� ����� � ������������� �������� �����. ������ �� �����������.";
			link.l1.go = "PortRoyal_3";
		break;
		case "PortRoyal_3":
			dialog.text = "������ ����, �� ��� �� �������. �������� �� ���� ��� ������ - � ���� ����.";
			link.l1 = "������� ���� ������, ��� ������ �����!";
			link.l1.go = "PortRoyal_4";
			link.l2 = "�������� ���-������...";
			link.l2.go = "All_disagree";
		break;
		case "PortRoyal_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "��, ������ ���������� �����. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";	
		break;
		case "PortRoyal_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "� ���� � �� �����������, ��� �� ��������� ��������.";
				link.l1 = "�����������, ������� � ���� �� �����. ���, �� � ��� ��� �� ����, ������� ��� ���?";
				link.l1.go = "PortRoyal_ok";
			}
			else
			{
				dialog.text = "����� ��������, "+ GetSexPhrase("�������","�������") +". ��� ����� ���������� �����. ��� �����������?";
				link.l1 = "��, ��������� ���!";
				link.l1.go = "PortRoyal_6";
				link.l2 = "���, �� ����� � � ������� ������.";
				link.l2.go = "PortRoyal_7";
			}
		break;
		case "PortRoyal_ok":
			dialog.text = "��� ����������� ������. ����� �� �� ������� �� ������ � ����� ��������.";
			link.l1 = "��, � ��� ��� ����� ������, "+ GetSexPhrase("� ������� �� ����� �� � ����","��� ����� ����������") +". ������� ����.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore36 = true;
			pchar.GenQuestRandItem.Shore36.randitem2 = "cirass4";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "5");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "PortRoyal_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "������. �������, ��� ������� ��������� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_7":
			dialog.text = "�� ������� - ��� ������. ��, � �� ��� "+ GetSexPhrase("����� �������� �������","����� ������ �������") +"...";
			link.l1 = "��� �� ������ ���� �������?";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_again";
		break;
		case "PortRoyal_again":
			dialog.text = "�� ������! ��� ��� ��� �����?";
			link.l1 = "���� ��� ��� ����������� �������� �� ���� �������.";
			link.l1.go = "PortRoyal_6";
		break;
		//================================== �������� ======================================
		case "Santiago":
			NextDiag.TempNode = "Santiago";
			dialog.text = "����������� ��� � ��������, �������! � ����� � ���� ���������� �� ������ ���������� ������. �� �� ������?";
			link.l1 = "�� ����� �������������.";
			link.l1.go = "exit_over";			
			link.l2 = "�� � ���� ����. � � ����� �������.";
			link.l2.go = "Santiago_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Santiago_1":
			dialog.text = "���������! ����� ���������. ������������� ������ ��������� � ���� �� ���� ������, ��� �����, ���� ������...";
			link.l1 = "����, ����� ����! ������� ��������.";
			link.l1.go = "Santiago_2";
		break;
		case "Santiago_2":
			dialog.text = "�-��, �� ��� ��, �������. ����, � ���� ���������� ��� ����, ��� ��������, ������ ��� �������. ������ ��� �� ��� ������ �� �����, � ���� ���� �������� ����� �� ���� ������������ ���� ������.";
			link.l1 = "� ��� ��� �� ������?";
			link.l1.go = "Santiago_3";
		break;
		case "Santiago_3":
			dialog.text = "������ ���������, �� ����� ���������. ���������, � ���� ���� ��������� ������� ����� ������. ��� ����������� �������. �� ��������?";
			link.l1 = "��, ���� � � �� �������, ����� ��� ���, ��� �� �����, � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "Santiago_4";
			link.l2 = "���, ������������ ���������! ������ ������, ���� �� ������...";
			link.l2.go = "All_disagree";
		break;
		case "Santiago_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "������������! ����, ��������, ����������, ��� ������. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";	
		break;
		case "Santiago_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "�������, ��� ���������� �����! ����������.";
				link.l1 = "������� �� ������������, ��� ����� �������. � ����� ��� ������� ���� �������, ������� � ������� �������� � �������� ����� ������...";
				link.l1.go = "Santiago_ok";
			}
			else
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +", ���� ����� ���� �������� �� �����. �� ������������! ����� ���, ���������� ��� ���...";
				link.l1 = "�������, ��������.";
				link.l1.go = "Santiago_6";
				link.l2 = "���, ��������. �������.";
				link.l2.go = "Santiago_7";
			}
		break;
		case "Santiago_ok":
			sTemp = GetConvertStr("itmname_pistol6", "ItemsDescribe.txt");
			dialog.text = "��� " + sTemp + "! �� ������ �������� ��� � ����� �� ����, ����� ���� �������, ��� ����� ����� �� ����� � ����������� �� ��������. �� �����������, ��� ����� ������ - ����, ������ ��� � ������� �������.";
			link.l1 = "�� ��, � ���� �� ���������. �� ��� ��, �������� �����������. ������� ��� � ����� ��������.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Cuba_Grot = true;
			pchar.GenQuestRandItem.Cuba_Grot.randitem1 = "pistol6";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "6");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			AddQuestUserData("QuestionsMessages", "sBladeName", sTemp);
		break;
		case "Santiago_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "���������! � ����� ������, ������� ��� ���. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_7":
			dialog.text = "�� �������������? ��� �������?! ��, �� ����� ������� - ���� ���������! �������, ��� �� ����� ���� ���, ��������...";
			link.l1 = "����� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Santiago_again";
		break;
		case "Santiago_again":
			dialog.text = "��� � ���� ��� ������?";
			link.l1 = "���� �������� �� ��� ������.";
			link.l1.go = "Santiago_6";
		break;
	}
}
