#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";			
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "������������, "+ GetSexPhrase("���","����") +". � ����� ����, �� ������ �������� ����� ���� ������� ����������... ����, ��� ��������, �� ��� ����� ��� ������... �� ������, ����� ���� ����� ����������, � ���������� � ��� ����� ����������. ��, ���� ����� " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " � ����� �������, ����... �������, ����� ������� ������ � ��� ������ ����������?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "������������, "+ GetSexPhrase("���","����") +". � ����� ����, �� ������ �������� ����� ���� ������� ����������... ����, ��� ��������, �� ��� ����� ��� ������. ��, ���� ����� " + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + " � ����� �������, ����...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "��� ��� �����?";
				link.l1 = "�� ������, � ��� ������ ��������. �� �������� ���?";
				link.l1.go = "SeekCitizen";
				link.l2 = "� �����"+ GetSexPhrase("","�") +" ������ ��� ������.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
					"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
				link.l3.go = "rumours_LSC";
				//��� ���� ������
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
				{
					link.l7 = "� ������"+ GetSexPhrase("","�") +", ��� �� ����� ������ � ����� ����...";
					link.l7.go = "ELTHusb_begin";
				}	
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "���� ������ � ��� ��� ���, ������ ������.";
					link.l7.go = "ELTHusb_toElis";
				}	
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElisGood")
				{
					link.l7 = "����, ������� ��������� ������ ����.";
					link.l7.go = "ELTHusb_good";
				}
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "����������, � ��� ��������� ������.";
					link.l8.go = "SeekGoods";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, � ������� �������, ����� ���� ������. � ��������� ��� ���� �� ���� �� ������� �����.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "������...";
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = "���, ��� ������ �� ���, � ���������. �������� � ��� �������� �����, � ��� ����� ����� ��� ����������� ��������. �� ����, ������... �, ������, � ������.";
			link.l1 = "�-�, ��������...";
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = "������. � �������.";
			link.l1 = "�-�, ��������...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "������, ���� �� ��� �� ���� � ������ �����, �������� ���� �������, �� ��� ����� ������������. �����, �� ��� � ��� ������.";
			link.l1 = "��, �������.";
			link.l1.go = "exit";
		break;

		//����������� �� � ��������
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!", "�������! ������!!! ����� ���, ��"+ GetSexPhrase("","�") +" ��������"+ GetSexPhrase("","�") +" �����!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "��, ���, ������, ���?! �� �������� ������ ��������?! ������ �������� � ������� ������ ����, ��� ������ ������!";
			link.l1 = "��� ����!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//��������� �� ����������� ������
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("������, �� �� �����"+ GetSexPhrase("","�") +" ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� ��� ���������, ������� ���, ������ ������? ����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������") +"...");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","��� ������") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//���� ��������
		case "SeekCitizen":
			dialog.text = "� ������������� ��� ������, ���� �����, �������. ��� ���� �� �����?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "��������, �� � ���������� �� �������, � ��� �� ��������. ����� ��� ������, ��� ����� ��� � �������.";
				Link.l1 = "��. ������� � �������� ��� ��� �� �������.";
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = "��������� ���, �� ����� � ���"+ GetSexPhrase("","�") +" �����.";
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "��, ��������, �� �� ����� ����. ��� �.";
					link.l1 = "���� ��!";
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", �� ��� ������ � ����?";
					Link.l1 = "������ ���.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, � ����"+ GetSexPhrase("","�") +" � ���� �������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "�����, ������ � ���.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. �����, � ��� ��� �������� �������?";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "�� ������, � ��� ����� ��������"+ GetSexPhrase("��","��") +", �� � �� ���� ������ �� � ��� ����������.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "����� ��� �������� ��� ��� ������� ��� � �������.";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		
		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase("������� �� ����, ��� ��.", "�� ��������� ������������� �� ����, ��� �� ������.", "� �� ������ ��� ��� �������� �����. ��� ��� �� ���� �����.");
					link.l1 = RandPhraseSimple("�������.", "����... ��� ��, �������.");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("������� �� ����, ��� ���.", "�� ��������� ������������� �� ����, ��� �� ������.", "� �� ������ �� ��� �������� �����. ��� ��� �� ���� �����.");
					link.l1 = RandPhraseSimple("�������.", "����... ��� ��, �������.");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase("�� �����, �� ���� �������. �������� ������������, ����������.", "��, ��� ���� �� ������ �� ���� �������...", "�� �� ���� �������, �������, ��� �� ��� �� �����������.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ������ ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "�� ������, � ������� ��������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� ����� ��� ���.", "��������� ��� ��������, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��������, �� �� ��������� ����� �����, " + npchar.quest.seekIdx.where + ". ��� ����� ���� ������������.", "��, �� ���� �����, ����� ���!", "���� �� �� ���������� ������ ����� �����������, �� ��������� ��� ������� ���...");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ������ ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� ��������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� �� ������� ������� ��� ���.", "��������� ��� ��������, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ���!", "������� ��� ��������.");
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase("��� �����, �� ���� �������. �������� ������������, ����������.", "��, ��� ���� ��� ������ �� ���� �������...", "��� �� ���� �������, �������, ��� �� ��� �� �����������.");
						}
						else
						{
								dialog.text = LinkRandPhrase("� ������ �� ������ ������� " + npchar.quest.seekIdx.where + ".", "�� ������, � ������� ��������� �� " + npchar.quest.seekIdx.where + ". ��� ��� ����� �� ���.", "��������� ��� ��������, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��������, �� ��� ��������� ����� �����, " + npchar.quest.seekIdx.where + ". ��� ����� ���� ����������"+ GetSexPhrase("��","��") +".", "��, ��� ���� �����, ����� ���!", "���� �� �� ���������� ������ ����� �����������, �� ��������� ��� ������� ��...");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ������ �� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� ��������� �� " + npchar.quest.seekIdx.where + ". ��� ��� �� ������� ������� �� ���.", "��������� ��� ��������, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ���!", "������� ��� ��������.");
					link.l1.go = "exit";
				}
			}
		break;		
		//�������
		case "int_quests":
			dialog.text = "����������� ��� ������.";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "����������, ��� ��� �� ������?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "�� ����������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "�������, �� ����� ��� ������ � ������?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "� ���� ��� � ��� ��������, ��������.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "���, �� ��� �� ������? ��� ����� ���������� ��������. � �� ����� ��� - ���������� ����... ��, �� ���� �� ��� ��� �������!";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "��, � ����������. � ���?";
			link.l1 = "� ����� ����� �������� ������?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "�������, �� � �� �������. �� ������, ����� ���������� ��� �����, ����� �� �����. ��� ������ ������ �� � ��� �� ������� � �� �� ��� �� ������.";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "��, � ����������. � ���?";
			link.l1 = "� ����� ����� �������� ������?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "�� �����, ����� ��������.";
			link.l1 = "����.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("����� ������?", 
				"�� ��� ���������� �� ����.", 
				"��� ����������...",
                "�� ��� ���������� ���� �� ���� �������. ������ � �� ����!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ��� ����, �����, �������, ��������, ��������, ���������...", 
				"��... ��������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "��, ��������� � �������� � ���� ���. � ��� ���� �� ������� �������� �������� ����� ��� � ��� ������, ����� �� ����� ��� �������. � ������� ��� �����?";
			link.l1 = "100 ���� ������ ������.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "�� ������, ���������.";
			link.l1 = "������� ��������! � �� ����������, ��� ����� ���������� �� �� '��� ��������'?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "��, ��, �� ����... ��������� ������� �������!";
			link.l1 = "������, ����������� ��� � ��������. �������!";
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.balls = true;
			AddQuestRecord("ISS_MainLine", "49");
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = "������... � ������ � ������ ������ ���?";
			link.l1 ="�� ������ ��� �� ������. �� ���� �� �� ������ ������ �� ����, �� ��������� ���������. ���� � ���, ��� ������������� ����� �������� �����.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "� ������ �� ������?";
			link.l1 = "��� �������� �������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "��, � ���� ��������, ������, ��� � ����������\n�� ��� ��, � ��������.";
			link.l1 = "������. ������ ������������� �� '��� ��������'. ������ ������� ���������� ��� �� ��� �������.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "������������.";
			link.l1 = "������ �� �������������� �����!";
			link.l1.go = "SeekCrew_all";
		break;
		//���������� ����
		case "ELTHusb_begin":
			dialog.text = "������ ���, "+ GetSexPhrase("���","����") +". ��� ���, ���� ������ ������, ����� ����� � ������. ���� ������ ��� � ��������� ���.";
			link.l1 = "��������� � �������, �� ������ ��������� ��� �� ������.";
			link.l1.go = "ELTHusb_begin_1";
		break;
		case "ELTHusb_begin_1":
			dialog.text = "�����. �������� ���, � � ����� ��� �������������.";
			link.l1 = "���, ��������� ��������?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "��, �� ���"+ GetSexPhrase("�� ���������","�� ���������") +" ������. � ���� ���� ��� ����� ������ ����.";
			link.l1 = "��� ������?";
			link.l1.go = "ELTHusb_begin_3";
		break;
		case "ELTHusb_begin_3":
			dialog.text = "���� �� ������, �� ������� ���������� ��� ������� � ������.";
			link.l1 = "��� ������������� ������ ����. � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "��������, ��� ��� �� �����.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;
		case "ELTHusb_begin_disagree":
			dialog.text = "��, ��� ��, ����� ����. ����� ������ � ������ �����.";
			link.l1 = "���������.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //��������
		break;
		case "ELTHusb_begin_4":
			dialog.text = "����� ������. ����� � ���� ����� ������ ����.";
			link.l1 = "� ��� ������, ��������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "5");
			AddQuestUserData("ISS_ElisHusband", "sSex", GetSexPhrase("", "�"));
			pchar.questTemp.LSC.ElisHusband = "seekFreeMotod";
			sld = characterFromId("MaximTailor");
			sld.dialog.currentnode = "DontRemember";
		break;

		case "ELTHusb_toElis":
			dialog.text = "� ���� ����� ���� ��������?";
			link.l1 = "� ��� �������, ��� �� ����� ����� �� ������.";
			link.l1.go = "ELTHusb_toElis_1";
		break;
		case "ELTHusb_toElis_1":
			dialog.text = "��� � �� ���� ������!..";
			link.l1 = "����������, �� ������ �������� ��� ������ ��� ���? ���� ������, �� � ���"+ GetSexPhrase("","��") +" �� ������ � ���� ����.";
			link.l1.go = "ELTHusb_toElis_2";
		break;
		case "ELTHusb_toElis_2":
			dialog.text = "������, � �������� ���� ������. ���������� ���, � � ��� ��� ����� ������ ������.";
			link.l1 = "��... � ��� ������, ��������� ��� ��������?";
			link.l1.go = "ELTHusb_toElis_3";
		break;
		case "ELTHusb_toElis_3":
			dialog.text = "���� �� ������, ��� ��������� ������� � ������.";
			link.l1 = "��� ������ �����, � ������"+ GetSexPhrase("��","��") +"!";
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = "��������, ��� ��� �� �����.";
			link.l2.go = "ELTHusb_begin_disagree";
		break;

		case "ELTHusb_good":
			dialog.text = "���� ���, ������� ��� ������? ��� ��� ������� ��� �������?";
			link.l1 = "��, � ���-��� �������"+ GetSexPhrase("","�") +" � ���������"+ GetSexPhrase("","�") +" �� ���� ��������. ��� ���������� ���� ������ ���� ��� ���� ���� ������������.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "�������! �����, ��� ����� ����� �������� �� ������ �� ����� ��� ����.";
			link.l1 = "����� �� ��� �������.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "�� �������� ���� �����, � � ������ ����. �������� �������� ����.";
			link.l1 = "������� ���, �� ��� ������������� �����.";
			link.l1.go = "ELTHusb_good_3";
			GiveItem2Character(pchar, "key1");
		break;
		case "ELTHusb_good_3":
			dialog.text = "�� ������ � ����, ��� ��� �� ����� ������ �� ����� ��������. ���� ��� ���������, �� ��� �����.";
			link.l1 = "� ��� �������, �������.";
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //��������
			SetTimerFunction("LSC_ElisHusbandSet", 0, 0, 1);
		break;

	}
	NextDiag.PrevNode = NodeName;
}
