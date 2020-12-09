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
					if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "���� ����� ��� ����� �������, ������"+ GetSexPhrase("","���") +", ��� ����� �������, ��� �� ������ ��������� � ���... ���� ����� " + GetFullName(npchar) + ", � ���� ���� � �������.";
					else dialog.text = "���� ����� ��� ����� �������, ������"+ GetSexPhrase("","���") +", ��� ����� �������, ��� �� ������ ��������� � ���... ���� ����� " + GetFullName(npchar) + ".";					
					link.l1 = GetFullName(pchar) + " � ����� �������, �������. �������, � ��� ����� ����������� ���� �����?";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "������������! � ��� �������, ��� ��� ������ �� �������� �������"+ GetSexPhrase("��","��") +".";
					link.l1 = GetFullName(pchar) + " � ����� �������, �������. ��, ��� �.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = "��� ��� ����� � ���� � ����, ������"+ GetSexPhrase("","���") +"?";
				else dialog.text = "� ��� ������, ������"+ GetSexPhrase("","���") +".";
				link.l1 = "�� ������, � ��� ������ ��������. �� �������� ���?";
				link.l1.go = "SeekCitizen";
				link.l2 = "� �����"+ GetSexPhrase("","�") +" ������ ��� ������.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������, �������?", 
					"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
				link.l3.go = "rumours_LSC";
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.bombs"))
				{
					link.l8 = "�� ������, � ��� ��������� ������. �� ����� �� �� ��� ������?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.bombs") && sti(npchar.quest.bombs))
				{
					link.l8 = "� �� ������ ����.";
					link.l8.go = "TakeBombs";
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
			dialog.text = "���-�� ����� ������, ����� �� �����. ������, ����� ����� ���������� ������, ������� ���� �������.";
			link.l1 = "��, �������.";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "������, ��� �������� � ����� ������ ���������� � �������� ���� ������� � �������� �����������. ���� �� ��� �� ������� ���, �� ������� ������������.";
			link.l1 = "� ��� �� ���������, ���� ��� ������?";
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = "� ���������� ������, �� ������� '��� ��������'.";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "� ���� ����� " + GetFullName(npchar) + ". � ������� ���� �����, ��� ����� ����, ��� ��� ����� ������ �������� ��� ����������.";
			link.l1 = "�������, '���' ����� ����������.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "� ���� ��� �����. �� ��� ��, ����� ���������� � ��� ���.";
			link.l1 = "�������.";
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
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! �� ������� �����!", "�������! ������!!! ����� ���, ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!");
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
					Link.l2 = "���, � ���� � ���� �������.";
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
							dialog.text = LinkRandPhrase("��������, �� ��� ��������� ����� �����, " + npchar.quest.seekIdx.where + ". ��� ����� ���� ������������.", "��, ��� ���� �����, ����� ���!", "���� �� �� ���������� ������ ����� �����������, �� ��������� ��� ������� ��...");
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
				link.l2 = "������ ����� ����� ������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "�������, ����� �� ��� ����� ������?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "� ���� ��� � ��� ��������, ��������.";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "���� ������ ���������� ������� ���������� ��������. � ��������, ����� � ���, ���������� ������ �� ����.";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "�������� �����. ����� �������, �������, �� �� ��������...";
			link.l1 = "�� ��, ��������-�� ������!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "�������� �����, ����� ���� ���. � ���?";
			link.l1 = "�� ���, ������. � �������� ���� ������� ��� ��� �����, ����� �� ���� ������?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "��, ���, �������. �� �� ��� ���������� ������. ����, ��� �� �����...";
			link.l1 = "��, ����...";
			link.l1.go = "int_quests";
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("���� �����, ��, �������, ������.", 
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
			dialog.text = "�����... �������, � ���� ���-�� ����� ����... ��, �����! � ������� ��� ����?";
			link.l1 = "100 ���� ����� ������ ����������.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "������� ��������. ������ �� ������ ������� ���-��� � ��� ����.";
			link.l1 = "������ � ����� �������.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "��������� ��� 10 ������ ���������, ��� ������� ���� � �����. � ���� ������� ����������, � ���� ���� � ������� ������.";
			link.l1 = "� ����� ��� ���� ����?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = ""+ GetSexPhrase("�� ���� ���������? �� �����, ����� ������...","����, �� �����������.") +"";
			link.l1 = ""+ GetSexPhrase("�� � ���� ����, ������ ��� �������. ","��-�...") +"� �����, ��� ���� ������ ������� ��������� � ������ ������� ����, �� ���� �� �� ������ ���������.";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "� ��� ��� ��� �� ���� ����. ������ ��, ��� � ��� �������, � ��� ����.";
			link.l1 = "������-������, ��� �������.";
			link.l1.go = "exit";
			npchar.quest.bombs = true;
			AddQuestRecord("ISS_MainLine", "55");
		break;
		//�������� �� ����
		case "TakeBombs":
			dialog.text = "�� �������� ��, ��� � ����������?";
            if (CheckCharacterItem(pchar, "Mineral2") && CheckCharacterItem(pchar, "potionwine") && sti(pchar.items.potionwine) >= 3 && CheckCharacterItem(pchar, "potion5") && sti(pchar.items.potion5) >= 10)
            {				
				link.l1 = "��, ��� � ����. �������� ��������.";
				link.l1.go = "TakeBombs_yes";
			}
			else
			{
				link.l1 = "��� ���, �� ���� �����. �����, �� ��������� ������� ������?";
				link.l1.go = "TakeBombs_no";
			}
		break;
		case "TakeBombs_no":
			dialog.text = "���...";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;
		case "TakeBombs_yes":
			dialog.text = "������. ������ �������� ���� �����.";
			link.l1 = "�������. � ����� ���-������ �� '��� ��������' ���������? ����� ��� �����.";
			link.l1.go = "TakeBombs_1";
			TakeNItems(pchar, "Mineral2", -1);
			TakeNItems(pchar, "potionwine", -3);
			TakeNItems(pchar, "potion5", -10);
		break;
		case "TakeBombs_1":
			dialog.text = "�� '��� ��������'... �� ������, ������"+ GetSexPhrase("���","���") +". �� ���� �������� � ��� ���������. ������� ������ ����������, �� ��� �������.";
			link.l1 = "�����������! �������� ������� ��� � ����������. ��� ����� �������...";
			link.l1.go = "TakeBombs_2";
		break;
		case "TakeBombs_2":
			dialog.text = "�������..."+ GetSexPhrase(" �� �� ������, ��� � �������!","") +"";
			link.l1 = ""+ GetSexPhrase("���������... ","") +"��, ����� ��������.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddQuestRecord("ISS_MainLine", "56");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
			npchar.quest.Bombs = false;
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = "����� ����������! � �� ��� ��� �������� ��������� �����?";
			link.l1 ="� ���� ��� ������, � ������ ���� �����. ���� ������ � ����.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "��, �����������.";
			link.l1 = "���� � ���, ��� �������� ����� � ������� �������� ����������� ��������� �����. ��� �������� �������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "�������... �� ��� ��, � �������� ���� � ��� �� �������. ��� � ������ �������?";
			link.l1 = "������������� �� '��� ��������'. ������ ������� ���������� ��� �� ��� �������. � �� �������!";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "������, ����� ���� �� '��� ��������'.";
			link.l1 = "����� ���, �������...";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
