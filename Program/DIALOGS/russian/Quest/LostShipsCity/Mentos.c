
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

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
					dialog.text = LinkRandPhrase("��, ���"+ GetSexPhrase("��","��") +" �������"+ GetSexPhrase("��","��") +"! �������, ��� ����� �� �������� ��� �������������. � - " + GetFullName(npchar) + ", ������ � ������� �������.", 
						"��� �� � ���� ����������"+ GetSexPhrase("��","��") +" �����"+ GetSexPhrase("����","����") +" � ���������� ������� � ���� ������? �� ��� ��, ����� ���������� � �����. ���� ����� " + GetFullName(npchar) + ", � ������� � �������.",
						"���� ���"+ GetSexPhrase("���","��") +" �������"+ GetSexPhrase("���","��") +" ������! ����� ����������, ��� ���������, � �� ����� ��� ������ �� �������� ��������. ��� ��� - " + GetFullName(npchar) + ", � ������� � ������� �������.");
					link.l1 = RandPhraseSimple("������, � - " + GetFullName(pchar) + ". ��� �� �������?", "�����������. ���� ����� " + GetFullName(pchar) + ". � ��� ��� �� �������?");
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.text = LinkRandPhrase("��, ���"+ GetSexPhrase("��","��") +" �������"+ GetSexPhrase("��","��") +"! ��, ���������� � ����� ����������. � - " + GetFullName(npchar) + ", ������ � ������� �������.", 
						"��� �� � ���� ����������"+ GetSexPhrase("��","��") +" �����"+ GetSexPhrase("����","����") +" � ���������� �������? �� ��� ��, ����� ���������� � �����. ���� ����� " + GetFullName(npchar) + ", � ������� � �������.",
						"���� ������ ���������� ������! ����� ����������, ��� ���������. ��� ��� - " + GetFullName(npchar) + ", � ������� � ������� �������.");
					link.l1 = RandPhraseSimple("������, � - " + GetFullName(pchar) + " ��� �� �������?", "�����������. ���� ����� " + GetFullName(pchar) + " � ��� ��� �� �������?");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("���-�� ������������?", "� ��� ����, � ������ ����������?", "���-�� ���������?");
				link.l1 = RandPhraseSimple("������, � ��� ������ ��������. �� ������, ��� �� ������?", "��� ����� ����� ������ ��������. �� �� ����� ��� ���-������ ����������?");
				link.l1.go = "SeekCitizen";
				link.l2 = RandPhraseSimple("���� ������ ���� ������.", "� ���� ���� � ���� ������.");
				link.l2.go = "int_quests";
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.additional.powder") && sti(pchar.questTemp.LSC.additional.powder))
				{
					link.l8 = "������, ��� ����� ����� ����� � ������. ������� �� ����� ��� ������ ������, � ��� ����� �����...";
					link.l8.go = "SeekGoods";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && !CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "�����������, �������. �� ��� ��, ����� ������. �� ������.";
					link.l8.go = "SeekCrew";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = "��, ��� ����?";
					link.l8.go = "SeekCrew2";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "�� ���, �������, ������, ��� ����� ������.";
					link.l8.go = "SeekCrew3";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = "��������, �� ���-�� �������� � ���, ��� �� ������ ���� �� ���� � ����� ���������� �������.";
					link.l8.go = "SeekCrew4";
				}
				link.l10 = "���, ��� ���������.";
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = LinkRandPhrase("������� ������������ ������� � ���������� ������ ���������� ������.", 
				"������� ������� ��� �� ���� ������������. � �����, ��� ������ � ������...", 
				"� ������� ������� ���� ���������� � ���������� ������. ����� ���������� - ��� �������, � �������� - ��� ��, �����������.")
			link.l1 = RandPhraseSimple("�������...", "������ ����, ������� �� �����������.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �����������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//���� ��������
		case "SeekCitizen":
			dialog.text = "� ���� �� �����?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "� �� �������, � ��� �� ��������. ��� ����� ����� ��� � ������� ����� ��������.";
				Link.l1 = "�������. ����� � ��� �������� �������.";
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = "�������, � ����� ���"+ GetSexPhrase("","�") +" �����.";
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "��� ��� �� �!";
					link.l1 = "���� ��, ����� �� ���� ���"+ GetSexPhrase("��","��") +"!";
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "��-��, �����, ��� ��.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ����� ��� ��� ������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "���, ������ � ���.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ������, ����� � ��� ��� �������� �������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "������, �� ���� � ������ �� � ��� ����������. �� ��������.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "����� ������ ��� ��� ��� � �������.";
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
					dialog.text = LinkRandPhrase("�� ����, ����� ��� �� �����.", "���� ��� �����, ��� ��...", "�� ����� ��� ��� ��������, ��� ��� �� �����.");
					link.l1 = RandPhraseSimple("�������.", "����...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("�� ����� �� ��� �������� �����, �������.", "������� �� ����, ��� ��� ������.", "��, � �� ����, ��� ��� ����� ������ ����.");
					link.l1 = RandPhraseSimple("����.", "����...");
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
							dialog.text = LinkRandPhrase("�� �����, �� ���� �������. ��� ������������.", "��, ��� �� �����, �� ���� �������!", "�� �� ���� �������, �������, ��� �� ��� �� ������"+ GetSexPhrase("","�") +" ���.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� ��� ��� ���.", "��������� � ����, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��� �� �����, " + npchar.quest.seekIdx.where + ". ������ ������������.", "��� ���� �� �����, ����� ���!", "���� �� ��������? �� �� ����� ���������.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� ��� ��� ���.", "��������� � ����, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ����, ��������.", "������� ����!");
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
							dialog.text = LinkRandPhrase("��� �����, �� ���� �������. ��� ������������.", "��, ��� ��� �����, �� ���� �������!", "��� �� ���� �������, �������, ��� �� ��� �� ������"+ GetSexPhrase("","�") +" ��.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� �� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� �� " + npchar.quest.seekIdx.where + ". �� ���� ����������.", "��������� � ����, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��� ��� �����, " + npchar.quest.seekIdx.where + ". ������ ������������.", "��� ���� ��� �����, ����� ���!", "���� �� ��������? ��� �� ���-�� ����� �����.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� �� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� �� " + npchar.quest.seekIdx.where + ". �� ���� ���������� � ���.", "��������� � ����, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ����, ��������.", "������� ����!");
					link.l1.go = "exit";
				}
			}
		break;
		//�������
		case "int_quests":
			dialog.text = LinkRandPhrase("����������� ���� ������, "+ GetSexPhrase("�������","���������") +".", "������, � ������.", "����������� ������.");
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = LinkRandPhrase("��������, ��� ��� �� ������?", "��� ��� �� ������ ��������?", "������, �������, � ��� ��� �� ������ �����?");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = LinkRandPhrase("� �� �� �������� ��������� ������?", "�����, ���� ����������� ������� � ����� �����?", "�� �������� ������ ������?");
				link.l2.go = "ansewer_2";
			}
			link.l10 = RandPhraseSimple("��� ��������. ������, �������...", "���-�� �� ������ ��������, �����"+ GetSexPhrase("","�") +"...");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = LinkRandPhrase("���� ������ ���������� ������� ���������� ��������. �� ������ ��������� ����� ������.", 
				"����� ��������� �����, �� ������ ��? ������ ���������� ������� ���������� ��������. ������ � �� ������ ���� � ����.", 
				"��� ����� ���������� ��������. ���� ������ ������� �� ��������, ������� ���� ������� ��������...");
			link.l1 = RandPhraseSimple("�������.", "����...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = LinkRandPhrase("� �����? ��� � ����� ������� ������...", 
				"��� ��������� �������. � ������-��, ����� � � �� ����, ���� ����� ��� ����������.", 
				"�� ������, ����� ���� ���, ��� � ����� �������� �� �����. ����� ��� ������ ������ ����?");
			link.l1 = RandPhraseSimple("�������.", "����...");
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//������ ����� ���� �� �������
		case "OffNarval":
			dialog.text = LinkRandPhrase("�� ������ � �����, ����.", "��������� ���� ���... ��, �����, �� �����.", "�������� ���� '��������' � ������ ��������!");
			link.l1 = "������!";
			link.l1.go = "exit";
		break;
		//������ ����� ���� �� �������
		case "AffterFightN":
			dialog.text = LinkRandPhrase("�� ����������!", "��-��, ������� ����� �������...", "���, ����� '������' ����� �� ����������!");
			link.l1 = "����� � ��� �� ����������.";
			link.l1.go = "exit";
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("� ����� ���� ����� � ������? ����� ��� - ������� ����.", 
				"��� ������.", 
				"� ��� ������.",
                "��, � ���������"+ GetSexPhrase("��","��") +" �� ��.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("����� - ��. �� ���� �����, ��� ��� ������ ����������.", 
				"�������!",
                "�-�, �� ��.", 
				"���.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "��������, � ��������?";
			link.l1 = "��... ��, �����������.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "�������... ������, � ������ ����, ���� �� �������� ���� � �����.";
			link.l1 = "������"+ GetSexPhrase("��","��") +", ��� �����, ��� ������� �������� ��� ������ ����������.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "������. � ���� ������� �������� �� ������ ������... ������� ���� ����� ������ � ������, � ���� ��� ���������?";
			link.l1 = "��� ����� 10 ��������� ������ � 50 ������ ������. ��������� ��� ����� �� ���� '��� ��������'.";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "������, � ��� ������. �� ������ ������� ���� �����!";
			link.l1 = "�� �� ���, ��� � ���� ���������, �������. �����.";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_WEAPON, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 200);
			AddQuestRecord("ISS_MainLine", "58");
			pchar.questTemp.LSC.additional.powder = false;
		break;
		//������ ������� �� ������
		case "SeekCrew":
			dialog.text = "�������! �����?";
			link.l1 = "� ������ ��� ��� ������� ������� �� �������, ��� ��� ����� ����������. ����������� �� '��� ��������'. ������ �������, ������� ��� ���������, ���������� ���� �� ��� ������.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "��, ��� ���� �� �������. �� �� ������, � ���� ������� �����.";
			link.l1 = "�����?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "������� ����� ����� ���������. �������, ��� �� ��������� ���������� ����. ������� � ������� �����, ��������, ��� ����� ������. ���� � ���� �������� �������� � ����� - � ����� �������� ���� �����.";
			link.l1 = "��, ��� ���� �� �������. ������, �������, ����� ��� ��� �����������, � ���� ����� ���� �������� � ���� �� ������. ����������� ��������� ����������.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "���������� �����������. �������, ���������. ��, � ���� ����� ����������� ������� ���, ����� '��� ���' ����������� ������������ ��� ���.";
			link.l1 = "��� �����! �� ��� ��, ������ �����.";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.LSC.crew.ment_6 = true; 
			npchar.quest.LSCofficer = true; 
			AddQuestRecord("ISS_MainLine", "61");
		break;

		case "SeekCrew2":
			dialog.text = "���� ��� � �������, �� ����� ��� ������! ���� �������� ���������, �� � ����� �� ������.";
			link.l1 = "�������! ������� ����.";
			link.l1.go = "exit";
		break;

		case "SeekCrew3":
			dialog.text = "� �����. ������ � ����������, � ����� ���� ���� �����.";
			link.l1 = "������������!";
			link.l1.go = "exit";
		break;

		case "SeekCrew4":
			dialog.text = "��, ��� ���. � ��� �������?";
			link.l1 = "���� �� �������� ��� ������, �� � �����"+ GetSexPhrase("","�") +" ����� ���� �������� � ��������� ����������� �������. �� ������, � ���� ������ ��� ����� ����� ������.";
			link.l1.go = "SeekCrew4_1";
		break;
		case "SeekCrew4_1":
			dialog.text = "� ��������. ��� � ���� ������ ����?";
			link.l1 = "���� �� �����, ������ ����� ��������� ��������� � ����������. ���� �� ��������� �� ���� �������, ��, ������, �� �����.";
			link.l1.go = "SeekCrew4_2";
		break;
		case "SeekCrew4_2":
			dialog.text = "��, ������� - ��������� ����. �� � ����� ��������!";
			link.l1 = "�������! ����� ����������� ���: ��� �����, �� ���� �������� �����, �� ������� � ��� ����������.";
			link.l1.go = "SeekCrew4_3";
		break;
		case "SeekCrew4_3":
			dialog.text = "������. � �� �������, �������.";
			link.l1 = "�� ��� � ������...";
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.quest.LSCofficer = true; 
			AddQuestRecord("ISS_MainLine", "68");
		break;
		//��������� �������� �����_6 ����� �������� �� ������
		case "MentOffIsLife":
			dialog.text = "�� ���, ������, �� ��������.";
			link.l1 = "��... ������� ����, �������, �� ������� �����. � � ���� � �����.";
			link.l1.go = "MentOffIsLife_1";
		break;
		case "MentOffIsLife_1":
			Npchar.quest.OfficerPrice = (rand(4)+1)*1000;
			dialog.text = "��� �������. � ����� ���� � ���� � ������� ��������. ��� �� ��� ����������?";
			link.l1 = "�������, ������ �� ����� ��� ��������. ������� ���� ��������� ���, ����� ����������...";
			link.l1.go = "MentOffIsLife_2";
		break;
		case "MentOffIsLife_2":
			dialog.text = "������, ��� �������...";
			link.l1 = "������, ������� ��������� ��������. �� �� � �����, ��� ��?";
			link.l1.go = "MentOffIsLife_3";
		break;
		case "MentOffIsLife_3":
			dialog.text = "� ������, �������. ��� ��������� �� '��������'.";
			link.l1 = "�������, �� ��� ������� �����. ������ ����������� �� '��� ��������', ��� ���� ����������� ������� �� ��� ������. ��������� �������� ������, ���������� ���� �� ����, ��� ���. ����� ��� � ���������.";
			link.l1.go = "MentOffIsLife_4";
		break;
		case "MentOffIsLife_4":
			dialog.text = "������, �������. � ������ ��������� ����� �������...";
			link.l1 = "������, �� �� ��������� �� �������.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
			AddQuestRecord("ISS_MainLine", "66");
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "Gr_questOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
	}
	NextDiag.PrevNode = NodeName;
}
