
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

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
					dialog.text = "������� ����� ������� ������, ������ ������, �� �������� ����! ���� ����� �� ������...";
					link.l1 = "�������, �����, � ��������� �� ��������� ��� ����� �������� ��� ���� ������ ������������� �� ���� ������� �����... ���� ����� " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.text = "�������� ����� ������� ������!";
					link.l1 = "�������, �����, � ��������� �� ��������� ��� ����� �������� ��� ���� ������ ������������� �� ���� ������� �����... ���� ����� " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "��� ���� �����, "+ GetSexPhrase("��� ���","���� ���") +"?";
    			link.l1 = RandPhraseSimple("� ���� ������������ ������� ������, ������ ����.", "���� ������ ������������� � ������ ������, �����.");
    			link.l1.go = "donation";
				link.l2 = "�����, ��� ����� ����� ������ ����������. �� ������, ��� �� ������?";
				link.l2.go = "SeekCitizen";
				link.l3 = "���� ������ ��� ������, ������ ����.";
				link.l3.go = "int_quests";
				������
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l4 = "�����, ���� � ���-������ ������ ������ �������?";
					link.l4.go = "askCandles";
				}
				if (CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek" && CheckCharacterItem(pchar, "mineral3"))
				{
					link.l4 = "�����, ���� ������ ��� �����.";
					link.l4.go = "takeCandles";
				}
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l8 = "������ ����, � ���� ��������, ������ �� ��� ���������� � ��� ��������� ������?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek")
				{
					link.l8 = "������ ����, � ���� ��������, ������ �� ��� ���������� � ��� ��������� ������?";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "found")
				{
					link.l8 = "������ ����, ���� ������� � ��� ���������.";
					link.l8.go = "FSeekGoods";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������ ����, � ���� � ��� ��������� �����������.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "������...";
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = "� ����, "+ GetSexPhrase("��� ���","���� ���") +", ��� ���� ���� ����������. ��� ������ �� ��������� ���� ���� ��������� �� �������...";
			Link.l1 = "������ ����, ���, ������� ��� ���� ������� ����. �� ��� ������� �������� � ����� �� ���������� ������� ������, � �� ��� ��������� �������� ��� ����� �� �����. ��� �� ��� ���, �����?";
			Link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", ����� �� �������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "��� �������� ��� �����!";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "�����. ������� ��� ����� ����� ���� ������� ����� ������. �����, �� ���������� �������� ���?";
			link.l1 = "��, �� ������"+ GetSexPhrase("","�") +" ��...";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "��� ������ �� �� ������"+ GetSexPhrase("","�") +" �� �������, ���� ������� �� ����: '����� ���!', � �� �� �������? ���� ������: '�� ����� ����!', � �� �������?\n"+
				"������ ��� ������� ����� ����������, ���������� ����: ������ ����, ��� ��� ����� ��� � ��� ����. ������� ����� ������� �� �� �����������, ��� ������� ����!";
			link.l1 = "�� �����, ������ ����. � ��������� ������� ������ �� �������� ���.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "������. � ������ �� �������������!";
			link.l1 = "�� ����, �����.";
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
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!", "�������! ������!!! ����� ���, �� ������� �����!");
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
			dialog.text = LinkRandPhrase("����� ������, "+ GetSexPhrase("��� ���","���� ���") +". � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������") +"...");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
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
				Link.l1 = "�������. ������� � ��� �������� �������.";
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = "�������, � ����� ��� �����.";
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "��� ��� �� �!";
					link.l1 = "���� ��, ����� �� ��� ���"+ GetSexPhrase("��","��") +"!";
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "��-��, �����, ��� ��.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ������� ��� ��� ������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "���, ������ � ���.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ������� � ��� ��� �������� �������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "�� ���� � ������ �� � ��� ����������. �� ��������.";
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
					link.l1 = RandPhraseSimple("���, �������. ������� ���, ������ ����.", "�������, �����!");
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
					link.l1 = RandPhraseSimple("���, �������. ������� ���, ������ ����.", "�������, �����!");
					link.l1.go = "exit";
				}
			}
		break;
		//�������
		case "int_quests":
			dialog.text = "����������� ���� ������, "+ GetSexPhrase("��� ���","���� ���") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "����������, ��� ��� �� ������?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "�������, �����, � �� ���� ��� ���� ������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = "�������, �����, �� ����� ����� ������?";
				link.l3.go = "ansewer_3";
			}
			link.l10 = "��� ��������. ��������, ������ ����...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "��� ����� ���������� ��������. � ����� ������������ �����������������, � ��� ������ ����������� � ���, ����� ���������� ������� ������ �� ���� ��������.";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "� �������� �� ������� ����� ������������� ����� ����� �� ����� ���������� ����� ���������. �� ������� �������� �����...";
			link.l1 = "�� ���� �������� ��������?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "���, ��. ���� �������� ������������.";
			link.l1 = "��� �����.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "���, �� ����� �����.";
			link.l1 = "�������... � �� ������ ������-������ ���������?";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "��� ��� �����, ����� ���� �������� ����������. �������, ��� ������ ��� �������� ������ �����, � ���� ������.";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
		break;
		//��������
		case "donation":
			dialog.Text = "�������, "+ GetSexPhrase("��� ���","���� ���") +". ��� ����� �� ������ ������������ �� ���������� ������ �����?";
			Link.l1 = "��������, ������ ����, � ���������"+ GetSexPhrase("","�") +". �� ����...";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "� ���������, �������. 100 ��������.";
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
		break;

		case "No donation":
			dialog.Text = "��, ��������� ������ �� ����� �� ����� � ��������...";
			Link.l1 = "�� � �����. ��������, ������ ����, ��� ����.";
			Link.l1.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "�� ���� �������� ������ ��������� ����, "+ GetSexPhrase("��� ���","���� ���") +".";
			Link.l1 = "�� �� �� ���...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "�� ���� �������� ������ ��������� ����, "+ GetSexPhrase("��� ���","���� ���") +".";
			Link.l1 = "�� �� �� ���...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "�� ���� �������� ������ ��������� ����, "+ GetSexPhrase("��� ���","���� ���") +", �� ������ ���.";
			Link.l1 = "�� �� �� ���...";
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		//������� ������
		case "askCandles":
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +". ������ ��������� � ������, � � ��� � ������ ���-�� ����� �� ��� ����������� ����� ������. ������ ���, ������� 400 ������.";
			link.l1 = "� ��� ��� �� �����?";
			link.l1.go = "askCandles_1";
		break;
		case "askCandles_1":
			dialog.text = "���� �� � ����, ��� �����, �� ��� �� � ������ �� ����. �����, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l1 = "��... ��, ������, ������ ����, ���� ������...";
			link.l1.go = "askCandles_2";
		break;
		case "askCandles_2":
			dialog.text = "��� ��������, "+ GetSexPhrase("��� ���","���� ���") +", ������� ����� ���������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", �����. ��� ����� �������.";
			link.l1.go = "exit";
			npchar.quest.takeCandles = "seek";
			npchar.quest.takeCandles.Qty = 0; //���-�� ������
			AddQuestRecord("ISS_takeCandles", "1");
		break;

		case "takeCandles":
			iTemp = GetCharacterItem(pchar, "mineral3");
			npchar.quest.takeCandles.Qty = sti(npchar.quest.takeCandles.Qty) + iTemp;
			DeleteAttribute(pchar, "items.mineral3");
			if (sti(npchar.quest.takeCandles.Qty) < 400)
			{
				dialog.text = "��, ����� ���������. ������ �� ������"+ GetSexPhrase("","��") +" " + FindRussianQtyString(iTemp) + " ������. ����� �� ������"+ GetSexPhrase("","��") +" " + FindRussianQtyString(sti(npchar.quest.takeCandles.Qty)) + " ������. ���� �������� �������� ��� " + FindRussianQtyString(400 - sti(npchar.quest.takeCandles.Qty)) + ".";
				link.l1 = "�������. �� ��� �, �������� ������, ������ ����.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_takeCandles", "2");
				AddQuestUserData("ISS_takeCandles", "iQty", 400 - sti(npchar.quest.takeCandles.Qty));
			}
			else
			{
				dialog.text = "�������, �� ��������"+ GetSexPhrase("","�") +" ������������ ������ � ������ ������, "+ GetSexPhrase("��� ���","���� ���") +". ������ ��� ������ ������ ��� ��������� ����� �� ������ �����.";
				link.l1 = "� ���"+ GetSexPhrase("","�") +", ��� ����"+ GetSexPhrase("","��") +" ������ �������. ������ ����, � ��� ��� ������ ������� �� �����?";
				link.l1.go = "takeCandles_ok";
			}
		break;
		case "takeCandles_ok":
			dialog.text = "��, �������, ��� � ������. � �����, �� ���"+ GetSexPhrase("","�") +" ������������ ��������� � ����� ����� �����. ���, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l1 = "��, �����, ������� ���. ���� � ���������, �� ���...";
			link.l1.go = "exit";
			bDisableFastReload = false;
			npchar.quest.takeCandles = "found";
			AddQuestRecord("ISS_takeCandles", "3");
			CloseQuestHeader("ISS_takeCandles");
		break;
		//����� ������� �� ������ �� ������� �����
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("� ��� ��, "+ GetSexPhrase("��� ���","���� ���") +"?", 
				"�� ��� ���������"+ GetSexPhrase("","�") +" �� ����.", 
				"��� ���������"+ GetSexPhrase("","�") +"...",
                ""+ GetSexPhrase("��� ���","���� ���") +", ������ ���...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� ����, ��������, ��������, �����, ������, ���������...", 
				"��... ��������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "���������? � ���� ���-�� �����?";
			link.l1 = "���, ������ ����... ��� ����� ���������, ����� �������� ��� �����.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "��, ��������� � ���� �������. ������ ��� ������ ����� � ��� ������, "+ GetSexPhrase("��� ���","���� ���") +". � ������ � ������.";
			link.l1 = "� ������?";
			link.l1.go = "askCandles";
		break;
		//����� ������� �� ������ �� ������� �����
		case "FSeekGoods":
			dialog.text = NPCStringReactionRepeat("��� �����?", 
				"�� ��� ���������"+ GetSexPhrase("","�") +" �� ����.", 
				"��� ���������"+ GetSexPhrase("","�") +"...",
                ""+ GetSexPhrase("��� ���","���� ���") +", ������ ���...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("50 �����, �������, ����� ����������.", 
				"��... ��������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FSeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FSeekGoods_1":
			dialog.text = "� ����� ����, "+ GetSexPhrase("��� ���","���� ���") +"?";
			link.l1 = "���, ������ ����, ������� ���� �� ����.";
			link.l1.go = "FSeekGoods_2";
		break;
		case "FSeekGoods_2":
			dialog.text = "�� ��� ��, � �� ���������, ��� ��� ����... �� ������ ������� � ���� ����������� ���� ������ ��������. ���-�� �� �����"+ GetSexPhrase("","��") +" ���, ������ � ������ ����.";
			link.l1 = "�������, �����! �����, ��� ����� �������, �� �� �� ������ ������������ �������� ���� �������� �� '��� ��������'?";
			link.l1.go = "FSeekGoods_3";
		break;
		case "FSeekGoods_3":
			dialog.text = "������. ��� � �����, "+ GetSexPhrase("��� ���","���� ���") +", ��������� ��� �������.";
			link.l1 = "������� ��� ��������, ������ ����!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 50);
			AddQuestRecord("ISS_MainLine", "47");
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("� ��� ����, "+ GetSexPhrase("��� ���","���� ���") +"?", 
				"�� ��� �������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������, "+ GetSexPhrase("��� ���","���� ���") +".",
                "��, "+ GetSexPhrase("��� ���","���� ���") +", ���"+ GetSexPhrase("��","��") +" �� �� ���������"+ GetSexPhrase("��","��") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ������� ������� �� ���� ������� � ��������� ��� �������������� �� ���.", 
				"��... ��������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "��, ��� ���?.. �� ����������� �������, �� � �� ���� �������� ������ ������.";
			link.l1 = "������ ����, �� ������ ����� ������ �� ���������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "�� ��� ���� �������, "+ GetSexPhrase("��� ���","���� ���") +". � �������.";
			link.l1 = "�� ��� ��, ��� ������, ������ ����.";
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
