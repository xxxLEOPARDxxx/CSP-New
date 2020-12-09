
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //��������� ���� � ���
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- ����� ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("� ������ ������� �������. ������, � ��� ���� ������� �� ������...", "�� �� �� ����� �� ������� ��� ��������� ������?.. �� ���, �������!!!", "� ���� ������ �� �� �������. ���� ������� ��������� ������ �������� ����� ��� �����!"), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","��������") +"!", ""+ GetSexPhrase("�������","�������") +" ������! ������!!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("������, ���� ���� �������...", "���, � �� ������� �� �������� ������ ��������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("����������� � ��!", "���, ���� ���� �������� ��������� ������..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "� ���� �����������. � ������ "+ GetSexPhrase("���","����") +" ������, ���������� ��� ���...";
					link.l1 = "���!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "��� ���� ���� � ���� ����, �������"+ GetSexPhrase("","��") +"?! ��� ���� ������ ������, ����� �� ������� ������!";
					link.l1 = LinkRandPhrase("���, � ����� ���� �����!", "����� ��� ���� ������� ����...", "��, �������.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("��� �������������� ��� � ���� ����. �� �� ���� �� ���?", 
						"��� � ���� ��� ������?", 
						"��, ��� � ���� ������� ��� ���?",
						"��������, ���� � ��� �� �����, � ������� ��� ���� �� ����������...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("���, ������ ���������� �����, ���������� � ��������...", 
						"�� ���, ����� ���������...",
						"������...", 
						"������, ��� �������.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("��������, �� �� ������� ��������� � ���� ���� - ���� �� �����. � ����� ��� �������� ��� ���!", 
						"� ��� �������, ��� ����� �������. ����� ��� ����.", 
						"�� ���� ���������� ������, �� � ���������, ����� �� ���������� �������� ��� ���!",
						"���� ������, ��� ��� �����?! ������, ����!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("������, � �������...", 
						"��, ������...",
						"�����, �� ��������.", 
						"��������, ����� ����?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "�-�, ��������� ������������� - " + GetFullName(npchar) + ". �� ���� ��� ������, ������ �������������� ��� ������ ������ - �� ������ ����.";
			link.l1 = GetFullName(pchar) + ", � ������ ����������...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� "+ GetSexPhrase("���, ��������! ������, ����� ���","�������! ������, ����� ��") +"!!!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ����� "+ GetSexPhrase("����","�������") +"!!!", "������! ������!!! ����� "+ GetSexPhrase("����","�������") +"!!!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- ���� ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("������������, ��� ����� ����� ������ ��� ���! ��� �� �� �� ����� ����...", "�� �����, ��� ��� ������� �������. � ������, ��� ����� ����� ������ ������ ��� ���!", "��� ��� ����� ����� ����, ��� ���������� ����� ���� ������!"), 
					LinkRandPhrase("��, ����, ���� ��� ����... ��������!!!", "������� ������, ��� �� ����� ����! ������!!", ""+ GetSexPhrase("����� ��������","������ ��������") +"... ����� ������ ��� ��� � ���������, ������ ����� � ���� �����!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("���, ������� ����...", "���, ����� ���� �� ���������, �����..."), 
					RandPhraseSimple("������ ���� �����, � �� �� ����� ������...", "� �������� ����� ������, ������� ������. � �� ���� ����, �� �� ���� �����..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "� ���� ������������. ��������, ��� ����� ����!";
					link.l1 = "���� ����� - ����...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "��� ���� ���� � ���� ����, "+ GetSexPhrase("�������","���������") +"?! ���� �� �� ��������� ����� ������ ������, �� � ������ ������!";
					link.l1 = "��� ����...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("� ���� ��� ������ � ����� ����. ���� ����� " + GetFullName(npchar) + ". ��� � ���� ��� ������?", 
						"�� ��� �����?", 
						"��, ��������, �� ��� �� �������, ��� �� ��� ���������� � ���?",
						"� ����� ��� �� �������������� ����� ���������������.", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + " � ����� �������. � ��� ���"+ GetSexPhrase("��","��") +" ��� ����������� ����, �������������.", 
						"��� �����.",
						"��, ��� �������...", 
						"������.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("��, �������, ��� �� ��� �� ���������� � ��� � ����� �����! ����� �������� ����... ����� ��� ����, ��������� � ��� ������.", 
						"������ ��, ����� ���! "+ GetSexPhrase("� �������� �������!","") +"", 
						"� ��������� ��� ������ ����� ��� �������� ��� ���!",
						"�� ��� �� ��� ��������?!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("�� �������, � ������ ������� ��� �� ������.", 
						"������, �� ���� �����������...",
						"�����.", 
						"� ��� ����?", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "������, ������ ���� ������. ������ ����� ��� �� ������������"+ GetSexPhrase(" � ����, ��� ��� � �������...",", � ���� ����� ����� ���.") +"";
			link.l1 = "�-�, ��, �������...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "��, ���, ������, ���?! � ��� ������� � ��� ��� ����"+ GetSexPhrase("�","��") +", � �� �� ��������� ������ ��������?! ������-�-�!!!";
			link.l1 = "��������, ����...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "������� � ���� ������� ��-�������� �������� �� ����! ��, ������... ��������! ������!!!";
			link.l1 = "�������� ����, � ��� �����?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- �������� ---------------------------------
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("� ������ ������� �������. ������, � ��� ���� ������� �� ������...", "�� �� �� ����� �� ������� ��� ��������� ������?.. �� ���, �������!!!", "� ���� ������ �� �� �������. ���� ������� ��������� ������ �������� ����� ��� �����!"), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","��������") +"!", ""+ GetSexPhrase("�������","�������") +" ������! ������!!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("������, ���� ���� �������...", "���, � �� ������� �� �������� ������ ��������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("����������� � ��!", "���, ���� ���� �������� ��������� ������..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = "��� ���� ����� �����?.. ������, �, �������, ���� ����... ������, ����� ������"+ GetSexPhrase("��","��") +"!!!";
				link.l1 = "������ �� ��������� ������...";
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("���������� ���! ���� ����� " + GetFullName(npchar) + ". � ����� ������� ����, ��� ��� �� ������� ���������� ���-�� � �����...", 
					"���� ���� ��������. � �����, ��� � ������ �� �����.", 
					"���� �� �� ������ � ������� - ��� � �������, ������ ���������� �����. ������ ��� ������...",
					RandPhraseSimple("��, ����� ��� ��������!", "��, ���� ������, ��� �� ��������?.."), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("������, �� ���������.", 
					"�������!",
					"�������...", 
					"��, �������� � ���� ���������...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				//���������� ����� ����� �� ������ ������������� ��������
				if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
				{
					link.l2 = "��������, ��������, ���� ���������� � ����� ����������.";
					link.l2.go = "ShipyardsMap_1";
					pchar.questTemp.different.ShipyardsMap = "toResult";
				}
			}
		break;
		case "ShipyardsMap_1":
			dialog.text = "��! ��, ����� ���������.";
			link.l1 = "��� ����� ������� �� ����� �����, ����� ������ ���.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "��� ��� ��! ��, ������, ��� ��� �����������!!!";
				link.l1 = "����� ���?! � ���������� "+ GetSexPhrase("�����","������") +"!..";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingLight", 5);
				AddCharacterExpToSkill(pchar, "Fencing", 5);
				AddCharacterExpToSkill(pchar, "FencingHeavy", 5);
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "��! ��, �� ����� "+ GetSexPhrase("��������. ������","�������. ������") +" �� ����� ����� � ����� ��������!";
				link.l1 = "��� �� �� ����� ����, � �� �����. ���� � �� �����...";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "����� ���� ���?";
			link.l1 = "���� ��������, ����. � "+ GetSexPhrase("�����","������") +" ���������...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "��, ��� ����������... � �����, ���! ���� " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", � ��������� ����� ������� ����� ����� � ���� ��������� ��������.";
			link.l1 = "��� ������� ������ ��� ����. ��������...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "������, � "+ GetSexPhrase("��������","��������") +". ������� ������ � �����, ��� ������������.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "�� ��������, ��� ������.";
			link.l1 = "������, ����...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//������� close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//������ ������ �� ������� close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
