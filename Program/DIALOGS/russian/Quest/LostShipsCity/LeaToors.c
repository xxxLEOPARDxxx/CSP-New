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
					if (npchar.location == "PlutoStoreSmall") dialog.text = "����������� ���, "+ GetSexPhrase("������","�������") +", � ���� ����, �� ������ ��������� � ���� ���� �����. ���� ����� " + GetFullName(npchar) + ".";
					else dialog.text = "����������� ���, ������. ���� ����� " + GetFullName(npchar) + ".";					
					link.l1 = "� � - ������� " + GetFullName(pchar) + ". ��������� �����, ��������?";
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = "����������� ���, "+ GetSexPhrase("������","�������") +", � ���� ����. ���� ����� " + GetFullName(npchar) + ".";
					else dialog.text = "����������� ���, "+ GetSexPhrase("������","�������") +". ���� ����� " + GetFullName(npchar) + ".";
					link.l1 = "� � - ������� " + GetFullName(pchar) + ". �������������� ���� ���� ��������, ��� ����"+ GetSexPhrase("��","��") +" �������...";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "� ���� ��� ���-������ ������, "+ GetSexPhrase("������","�������") +"?";
				link.l1 = "�� ������, � ��� ������ ��������. �� �������� ���?";
				link.l1.go = "SeekCitizen";
				link.l2 = "� �����"+ GetSexPhrase("","�") +" ������ ��� ������.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
					"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
				link.l3.go = "rumours_LSC";
				//����� �� �������� ��������
				if (CheckActiveQuest("LSC_findDekster") && !CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
				{
					link.l4 = "���, � ������"+ GetSexPhrase("","�") +", ��� �� ������ ���-�� � ����� ������� ��������...";
					link.l4.go = "LostDecster";
				}
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.grapes"))
				{
					link.l8 = "����������, � ��� ��������� ������.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.grapes") && sti(npchar.quest.grapes))
				{
					link.l8 = "� �� ������ �������.";
					link.l8.go = "TakeGrapes";
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
			dialog.text = "��, �� ������ ���������� ����� ����� ������. ����� ������, ��� ������ ������ ���� � ������ ������ ������ ����� ����������� �� ����� ������� ������. ������ ��� ��� ����� �����.";
			link.l1 = "��, ��� �������... �� ��� ��, �������� ��� �������.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "� �������, ��� ��� ������� �������� ���. �� �� �� ��������!";
			link.l1 = "��-��, �������...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "����������, ��� �� ����� �����������. � ������� ��� ������� ���������� � ���� �����, ����� �� ��� �� � �����, ��� ����� ���������� �� ������ ������.";
			link.l1 = "������� ��� �� ���������.";
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
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!", "�������! ������!!! ����� "+ GetSexPhrase("���","��") +", ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!");
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
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
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
							dialog.text = LinkRandPhrase("��������, �� �� ��������� ����� �����, " + npchar.quest.seekIdx.where + ". ��� ����� ���� ����������"+ GetSexPhrase("��","��") +".", "��, �� ���� �����, ����� ���!", "���� �� �� ���������� ������ ����� �����������, �� ��������� ��� ������� ���...");
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
			if (!CheckAttribute(NextDiag, NodeName+".l1") && npchar.location == "PlutoStoreSmall")
			{
				link.l1 = "� ������ ��� ���� �������� ����� ����?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = "�������, � �� ����� ����� ������?";
				link.l2.go = "ansewer_2";
			}
			link.l10 = "� ���� ��� � ��� ��������, ��������.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "������ ���������, ������ ��. � ���� ��� ��� ���������, ��� ��� - ��� ��������.";
			link.l1 = "��� �������.";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "� �� ��������� ���-�� � ���� ����������, � ������ �� ���� �����!";
			link.l1 = "�� � ���� ����!";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "���, ����� ���� ����� ����.";
			link.l1 = "�������... �������, � �� �� ������ ����-������ �� ������� ����������, ��� ��� ����� ����� ����� �����?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "�����. ��� ���� �������.";
			link.l1 = "��, ��� ��� ��������. ������ ��� �������� - �� �����...";
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = "��, ������� �������! � ���������� ����������, � ���� ��.";
			link.l1 = "��� �����... �� �����, ����� ��� ����������, ���.";
			link.l1.go = "int_quests";
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("� ��� � ���� ��� ������?", 
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
			dialog.text = "� ���� �� ������� ���� �������. ������� ��� �����?";
			link.l1 = "5 ��������� ����� ������ ����������.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "������, � ����� �� ���. ������ ������� ��������� ��� 10 �������� ����.";
			link.l1 = "����?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "� ����, ����� �� �������� ��� 10 �������� ����. ��� ��� �����������? � ����� � ����� ��� �������.";
			link.l1 = "������, ����� ��� ���� ����.";
			link.l1.go = "exit";
			npchar.quest.grapes = true;
			AddQuestRecord("ISS_MainLine", "53");
		break;
		//�������� �� ����
		case "TakeGrapes":
			dialog.text = "�� �������� ��� ������ ��������?";
            if (CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) >= 10)
            {				
				link.l1 = "��, ��� � ����, � � �����"+ GetSexPhrase("","�") +" ��� �� �������.";
				link.l1.go = "TakeGrapes_yes";
			}
			else
			{
				link.l1 = "��� ���, �� ���� �����. �����, ���-������ ��-������� �����������?";
				link.l1.go = "TakeGrapes_no";
			}
		break;
		case "TakeGrapes_no":
			dialog.text = "� �� ��������!";
			link.l1 = "��, ����...";
			link.l1.go = "exit";
		break;
		case "TakeGrapes_yes":
			dialog.text = "�����������! �� ��� ��, �� ������ �������� ���� �������.";
			link.l1 = "�������. ��, ��� �� ��������� �� �� '��� ��������'?..";
			link.l1.go = "TakeGrapes_1";
			TakeNItems(pchar, "Mineral10", -10);
		break;
		case "TakeGrapes_1":
			dialog.text = "��... �� ��� ��, � ��������� ��� ��������, � ������ ������ ���. ��������� �� '��� ��������' � ��� ��������� ����, ����� �������� ������ � ���� �����...";
			link.l1 = "�������! � ���� �� ����, ��� ��� �����������.";
			link.l1.go = "TakeGrapes_2";
		break;
		case "TakeGrapes_2":
			dialog.text = "�� �� ��� ��, �� �����. ��� � �������.";
			link.l1 = "����� ��������.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddQuestRecord("ISS_MainLine", "54");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "��"));
			npchar.quest.grapes = false;
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = "��� ��� ��!.. �� �� ������?";
			link.l1 = "�� � ���� ����.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "�� ������, ��� ����� ��� �������� �������. ��� ���, ���� �� �������� ������, �� � ��������.";
			link.l1 = "�� ������� ���������� �����, ���� ��� �������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "����� �� ��� �������. ���, ��� ��� ������ ������?";
			link.l1 = "������������� �� '��� ��������'. ������ ������� ���������� ��� �� ��� �������. � �� �������!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "������, ����� ���� �� '��� ��������'.";
			link.l1 = "����� ���, �������...";
			link.l1.go = "SeekCrew_all";
		break;
		//����� �� �������� ������� ��������
		case "LostDecster":
			dialog.text = "��, � ������ �� �����������?";
			link.l1 = "��, ��� �������?.. ��� ������ ��������� �����.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "��������� ��������, ��� �������� ���� ���������������� � ��-���� ������� �����������...";
			link.l1 = "��� ��� ��������?";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "���� �� ������ �������� � �������������� � ���������, ��, �����, ��� ���� ������ ����������� �������.";
			link.l1 = "���, ��� �� �����? � ��� � ��� ��������� ������?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "�� �������, ��� ������ ��� �����?";
			link.l1 = "���������.";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "�� ������, � ��������\n��, �������, ��� ������, ��� ������� ��� �������, ��� � ��� ������, ����������. ������� ��� ������� ����������. ���, ����� ���� ���������, ��� �� �������� ������� ����������� '���������'. �������, �� ������, ��� ��� ���� ������?";
			link.l1 = "��... ��, �������, ��� ��� ��������.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "�� ����� ��� ���� ��������� ������ �����. ���-�� � ������ �������� ������� �������, ������� ��������� ��� ������ �� �������. � ���� ���� � ������, �, � �����, � ��� ����������� �� ��������\n� ���, ����� � ����� �� ������, �� �������� ��� ������ - ���� � �������. ��� ������� � �������...";
			link.l1 = "���... � ��� ���� ������?";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "������ ���� ��������� ������� ���������� ������. � �� ����, � ��������� ���� �������� � '���������'. ������ � ������ �� ����, �� � ��� ��� ����� �� ����� ������� ��������.";
			link.l1 = "�� �������, ��� ��� ��� ���������?";
			link.l1.go = "LostDecster_7";
		break;
		case "LostDecster_7":
			dialog.text = "�� ����, �� ����� �� �� ������.";
			link.l1 = "�������... ������, ��� ��� ��������� �� '���������'?";
			link.l1.go = "LostDecster_8";
		break;
		case "LostDecster_8":
			dialog.text = "���� �� �����.";
			link.l1 = "����. ������� ��� �� �������������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "toAdmiral";
			AddQuestRecord("LSC_findDekster", "3");	
		break;
	}
	NextDiag.PrevNode = NodeName;
}
