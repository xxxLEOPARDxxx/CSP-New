
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (CheckAttribute(npchar, "quest.takeMap")) Log_SetStringToLog("������: " + npchar.quest.takeMap);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "������ �����! ���� ��� ����� �� �����... � ��� �������, ��� �� - "+ GetSexPhrase("����� ���������","����� ���������") +" ������.";
					link.l1 = "������� " + GetFullName(pchar) + " ����������� ��������. � ����� - �� ����!";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "�-�, �� ��� �� � �� ��� ���������"+ GetSexPhrase("","�") +". � ��� �������, ��� �� - "+ GetSexPhrase("����� ���������","����� ���������") +" ������.";
					link.l1 = "������� " + GetFullName(pchar) + " ����������� ��������.";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "������� ���-������ ������ ��� �������?";
				link.l1 = "������, ��� ��� � ���� ����.";
				link.l1.go = "Trade_exit";
				//����� ��������� ����� -->
				if (!CheckAttribute(npchar, "quest.takeMap"))
				{
					link.l2 = "�������, � ������"+ GetSexPhrase("","�") +", ��� � ���� ���� ����� ������. �� ������, � ������ ������ ��� �� ��� ����� �����������. � �� ����� �����, ��� ������ �������, �� ������"+ GetSexPhrase("��","���") +" ���...";
					link.l2.go = "tekeMap_begin";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "mapIsToken" && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l2 = "��������, �� ����� �� ��������? ����� ������ �� �������� ������ ������, ����� ��������� ������ ������?";
					link.l2.go = "tekeMap_off";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "discount")
				{
					link.l2 = "��������, �������, " + npchar.quest.takeMap.name + " ������� ���� ������������ � ����� ��� ��� �� ������ ����� ������.";
					link.l2.go = "tekeMap_on";
				}
				//<-- ����� ��������� �����
				link.l3 = "�������, �� ����������.";
				link.l3.go = "exit";
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(pchar, "questTemp.LSC.goods.trader"))
				{
					link.l8 = "������, � ���� ������ � ���� ���-��� ���������.";
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.goods.trader") && sti(pchar.questTemp.LSC.goods.trader))
				{
					link.l8 = "� �� ������ ������� ��� �������, ��� �� ��� ������.";
					link.l8.go = "SeekGoodsOk";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, ���� ��������� ��������. � ������� �������.";
					link.l8.go = "SeekCrew";
				}
				NextDiag.TempNode = "First time";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = "� �� ������ ������, ��� ����, � ��� ���?.. �����, ������ � ���� ���������� �������. ���� ����� " + GetFullName(npchar) + ", � ������ ����� ��������. ����� �������.";
			link.l1 = "�����.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "�������! � ���� ����� " + GetFullName(npchar) + ", � ������ ����� ��������. ����� �������.";
			link.l1 = "�����.";
			link.l1.go = "exit";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date") || npchar.quest.takeMap == "changePrice")
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
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
			dialog.text = LinkRandPhrase("������ ����� �� ������ �� ��� � ������! ������ ������ �� ������? �� �����, ������ �������...", "��, �������"+ GetSexPhrase("��","��") +", �� ��� ��� ����������? ����� ��������� ���� ��� ���������! � ���� ������...", "������, �� ���� ��� �����"+ GetSexPhrase("","��") +"? � ��� � ������ ������� ���!! ��, ������ �������...");
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
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
			dialog.text = LinkRandPhrase("������, �� �� �����"+ GetSexPhrase("","�") +" ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� �'��������, ������� ���, ������ ������? ����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = "������ � ����� �������, "+ GetSexPhrase("��������","" + pchar.name + "") +". ���������!";
			link.l1 = "������, ����� ������� � ����� ������������ � ��� �� ��������"+ GetSexPhrase("","�") +". ��� �����, �������, �����, ��������, ��������, �����, ���������...";
			link.l1.go = "SeekGoods_1";
		break;
		case "SeekGoods_1":
			dialog.text = "��, �� ����, ��� �� ����������"+ GetSexPhrase("","�") +", ����� � ���� ������ �������� � ��������, ����� � ���������. ��������� ������ ������ �� �����.";
			link.l1 = "� � ���� ���-������ ����?";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "�������� ���� ���� �������. �� �������� �������.";
			link.l1 = "��� ����� 20 ���������. ������� ��� ����� ������?";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "�������� ���� ����� �����.";
			link.l1 = "�������?! � �� �������?";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "������, �� ������ �� �������������. � �������� ������� ���� �������� � ����� �� ���� ����� �������. �����, ���� �� ������� ��� ��� ����������, �� ������ 40 �����.";
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = "� �����"+ GetSexPhrase("","�") +" ���������.";
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = "� ���� ��� ����� �����.";
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		case "SeekGoods_notMoney":
			dialog.text = "��, �������, ����� �����.";
			link.l1 = "������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.goods.trader = true;
		break;

		case "SeekGoods_5":
			dialog.text = "�������, "+ GetSexPhrase("�������","" + pchar.name + "") +". ���� ���� ��� ��� ��������?";
			link.l1 = "������, ������� ��� ��� �� '��� ��������'. '��������' ��� ��� ���, ���� �� �� � �����...";
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = "� � �����. ��� ������.";
			link.l1 = "������� ����, ��������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "46");
			AddMoneyToCharacter(pchar, -40000);
			AddCharacterGoods(pchar, GOOD_FOOD, 200);
			AddCharacterGoods(pchar, GOOD_PLANKS, 50);
			AddCharacterGoods(pchar, GOOD_SAILCLOTH, 50);
			pchar.questTemp.LSC.goods.trader = false;
		break;

		case "SeekGoodsOk":
			dialog.text = "��������"+ GetSexPhrase("","�") +" ������?";
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = "��. � �����"+ GetSexPhrase("","�") +" ���������.";
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = "��� ���...";
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("����� �������?", 
				"�� ��� �������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������.",
                "������, ������"+ GetSexPhrase("","�") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� �������. � ����� �� ������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "���, � �� ������ �������... �� ���� ������, ��� ��������� ����� ������?";
			link.l1 = "����. �� � ������ ���� �����. ���� � ���, ��� ����� ����� �������� ������������� �������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "�-��, � � ������� �� ����...";
			link.l1 = "�� ��� �� ������?";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "���, �� ����. � �� ���� ������ �� ���� ��������.";
			link.l1 = "��... �� ��� ������.";
			link.l1.go = "exit";
		break;
		//����� ��������� ����� ������
		case "tekeMap_begin":
			dialog.text = "�������, � ������ ���������� ������ ���...";
			link.l1 = "�� ��� ���, ����� � ���� ����?";
			link.l1.go = "tekeMap_begin_1";
		break;
		case "tekeMap_begin_1":
			dialog.text = "����, ���� �� ��������.";
			link.l1 = "�������, ��� ��� �����.";
			link.l1.go = "tekeMap_begin_2";
		break;
		case "tekeMap_begin_2":
			dialog.text = "�� ��� �������. ��� ������, ����� ������ ������� ��� �������.";
			link.l1 = "�����"+ GetSexPhrase("","�") +"!";
			link.l1.go = "First time";
			npchar.quest.takeMap = "firstGiveMap";
		break;
		case "tekeMap_off":
			dialog.text = "�� �� �����"+ GetSexPhrase("","�") +". �� �� ������, � �� ��, ��� �� ��� ����������.\n� ������, �� �������� - �� �������. ����� ��������?";
			link.l1 = "��� ����� ��� �����. �� ��� ������� ������!!!";
			link.l1.go = "tekeMap_off_1";
		break;
		case "tekeMap_off_1":
			dialog.text = "�������"+ GetSexPhrase("��","��") +", � �� ��������. ������ ������, ��� "+ GetSexPhrase("�����","�������") +" �� ������ - �����. �� ������ - ���� ������.\n������ ��� ������ ���� ������� �� ����� ������.";
			link.l1 = "�� ��� ����� ����� ��� �����! ����� ����, ������ � ����.";
			link.l1.go = "tekeMap_off_2";
		break;
		case "tekeMap_off_2":
			dialog.text = ""+ GetSexPhrase("��������","�������") +", �������������������� ���������� � ������, � � ���� ������. ��� ��� ���� �� ����� - ����������.";
			link.l1 = "�-���, ����!..";
			link.l1.go = "exit";
			npchar.quest.takeMap = "notTrade"; //���������� � ���, ��� �� ��������� 
		break;
		case "tekeMap_on":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				dialog.text = "�����, ����� ����, ��� � ����...";
				link.l1 = "������� ����! � ������� �� ��������� �� ��� ������?";
				link.l1.go = "tekeMap_on_1";
			}
			else
			{
				dialog.text = "� �� � �����. " + npchar.quest.takeMap.name + " ��� ��� ������ �� ��������.";
				link.l1 = "��������, ��� �� ������. ����� �����, ��� � ��������� �� ��� ����.";
				link.l1.go = "exit";
			}
		break;
		case "tekeMap_on_1":
			dialog.text = "����� ��������� �����-������� ��������� � ���������� �����. �� ����� � ����������������.";
			link.l1 = "������, ��� �������.";
			link.l1.go = "exit"; 
			npchar.quest.takeMap = "changePrice"; //������� ����
		break;

	}
}
