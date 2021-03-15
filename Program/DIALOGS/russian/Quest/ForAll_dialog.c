
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� � ��� ��������.";
			link.l1 = "�����...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//--------------------------- ������� ��� --------------------------------
		//�������� ���������� ���� �����
		case "Begin_PoorKill":
			dialog.text = "������ ����, �������. �� ���������� ������������ �� ���� �� ����� ����?";
			link.l1 = "������ �� ����������? � �������������!";
			link.l1.go = "Begin_PoorKill_1";
		break;

		case "Begin_PoorKill_close":
			dialog.text = "��, �������... �� ��� ��, ����� ����.";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterReputation(pchar, 10);
			pchar.questTemp.LSC = "PoorIsGood";
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "12");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("��","��"));
		break;

		case "Begin_PoorKill_1":
			dialog.text = "���������! ����� ����� �������� ��������.";
			link.l1 = "����� � ����, ��������.";
			link.l1.go = "Begin_PoorKill_2";
		break;
		case "Begin_PoorKill_2":
			dialog.text = "��-��, ��� �������� ���� ������!\n�� ��� ��, ��� ������ ��������� �������������. ���� ����� " + GetFullName(npchar) + ". ��������, �� � ����� ������� � ��� � ����, ��� �� - ������� " + GetFullName(pchar) + ". ����� ��� ��������, ��� �� �����. ��� ���?";
			link.l1 = "�����. ��� ��� �� ����������� ������. � ��� �� �� �� ���� ����� ������������?";
			link.l1.go = "Begin_PoorKill_3";
		break;
		case "Begin_PoorKill_3":
			dialog.text = "� - ������� �������, ������ ���.";
			link.l1 = "���������. � ��� �� ���� � ��� �� ���?";
			link.l1.go = "Begin_PoorKill_4";
		break;
		case "Begin_PoorKill_4":
			dialog.text = "��, ����������, ������ ��� "+ GetSexPhrase("������ �������� ��������","����� ������� �������") +", ��� ��. ���� � ���, ��� ��� ������������ ������� ���������� ���������� ������ � �������������� �� �������� ���������� ����. ��-��, ������ ���!";
			link.l1 = "���"+ GetSexPhrase("","�") +" �� ������ ������������. ������ �������� �� ���� ��������...";
			link.l1.go = "Begin_PoorKill_5";
		break;
		case "Begin_PoorKill_5":
			dialog.text = "���� '������� ����' ����� ����������!";
			link.l1 = "� ��� ��� ��? ���������: ����� � ����, ��������...";
			link.l1.go = "Begin_PoorKill_6";
		break;
		case "Begin_PoorKill_6":
			dialog.text = "��, ������. ��� �����, ����� �� �������� ��� �� ����� � ��������� � �������. ������ �����, � ������ ������, ���������� �� ������������ ��������������. �� ��� ������ �� ������ ��� ��������� ������� ��������!";
			link.l1 = "���, ���������. ������� �� ������ �� ��������...";
			link.l1.go = "Begin_PoorKill_7";
			link.l2 = "�� �� ���� ���� ����������? �� �����"+ GetSexPhrase("���","��") +" ������?! ����-�� ������, ��������, ���� ���...";
			link.l2.go = "Begin_PoorKill_close";
		break;
		case "Begin_PoorKill_7":
			dialog.text = "�����"+ GetSexPhrase("�� ���","�� ���") +", �� �� �������� � ��� �����. �������� ������ �� ����� �������� �������� �� ������, �� �� �����������, ��-��...";
			link.l1 = "�� �� ������, ��� � �������! ������� ������� ������.";
			link.l1.go = "Begin_PoorKill_8";
		break;
		case "Begin_PoorKill_8":
			dialog.text = "� �������������! ����, � ����� ����� � ������� �������� �� ���� ��� � ����������, ��, �����������, ����� ������. �������. �� ���������� ������ �� ��� ������ ������ �������.";
			link.l1 = "� �����? ��� ����������� ����� ��������������.";
			link.l1.go = "Begin_PoorKill_9";
		break;
		case "Begin_PoorKill_9":
			dialog.text = "�������, �� �� ������ �� ����� ���� � ����. ��� ���������� �����������.";
			link.l1 = "��, ��������... � �����? � ���-������ ���������"+ GetSexPhrase("","�") +" � ������?";
			link.l1.go = "Begin_PoorKill_10";
		break;
		case "Begin_PoorKill_10":
			dialog.text = "����������� ���. ������ �������� ��� - � ��������� ���� �������. �������, �� �� ������ ������ �����, ��-��...";
			link.l1 = "��, ����� �� ����. ��� � ����� � ���� �������������� � ������� �������� �� ��� ���?";
			link.l1.go = "Begin_PoorKill_11";
		break;
		case "Begin_PoorKill_11":
			dialog.text = "� �������� ����������, ������� ��. � ������� ���� ������� �� ������� �� ����� �����������. ����� � �� ����� ����� �� ������ �������, � ��� �� ��� ����� ���������� � ���������� ���� ������������.";
			link.l1 = "�� ��� ��, ����� �� �����!";
			link.l1.go = "Begin_PoorKill_12";
		break;
		case "Begin_PoorKill_12":
			dialog.text = "��, ��� � ���������. ��� ��, � ���� �� ������ �� ��������, ��������. � ���, ��� ���� �������� �� ��� ������ ���� ��������. ������� �� ��������� ���������� ���������.";
			link.l1 = "��������. ������, � ��� ��� �� ������������, �������� ��� ������ ��� ���������?";
			link.l1.go = "Begin_PoorKill_13";
		break;
		case "Begin_PoorKill_13":
			dialog.text = "��������, �� ����� � ������� �� ����.";
			link.l1 = "��, �� �����. ��������...";
			link.l1.go = "Begin_PoorKill_14";
		break;
		case "Begin_PoorKill_14":
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "1");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			pchar.quest.ISS_Murder1.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder1.win_condition.l1.character = "SentJons_Poorman";
			pchar.quest.ISS_Murder1.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder2.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder2.win_condition.l1.character = "Bridgetown_Poorman";
			pchar.quest.ISS_Murder2.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder3.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder3.win_condition.l1.character = "Beliz_Poorman";
			pchar.quest.ISS_Murder3.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder4.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder4.win_condition.l1.character = "Caracas_Poorman";
			pchar.quest.ISS_Murder4.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder5.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder5.win_condition.l1.character = "Cartahena_Poorman";
			pchar.quest.ISS_Murder5.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder6.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder6.win_condition.l1.character = "Cumana_Poorman";
			pchar.quest.ISS_Murder6.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder7.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder7.win_condition.l1.character = "BasTer_Poorman";
			pchar.quest.ISS_Murder7.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder8.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder8.win_condition.l1.character = "Havana_Poorman";
			pchar.quest.ISS_Murder8.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder9.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder9.win_condition.l1.character = "PortRoyal_Poorman";
			pchar.quest.ISS_Murder9.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder10.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder10.win_condition.l1.character = "FortFrance_Poorman";
			pchar.quest.ISS_Murder10.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder11.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder11.win_condition.l1.character = "Charles_Poorman";
			pchar.quest.ISS_Murder11.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder12.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder12.win_condition.l1.character = "PortoBello_Poorman";
			pchar.quest.ISS_Murder12.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder13.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder13.win_condition.l1.character = "PortPax_Poorman";
			pchar.quest.ISS_Murder13.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder14.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder14.win_condition.l1.character = "Santiago_Poorman";
			pchar.quest.ISS_Murder14.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder15.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder15.win_condition.l1.character = "Marigo_Poorman";
			pchar.quest.ISS_Murder15.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder16.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder16.win_condition.l1.character = "Tortuga_Poorman";
			pchar.quest.ISS_Murder16.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder17.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder17.win_condition.l1.character = "PortSpein_Poorman";
			pchar.quest.ISS_Murder17.function = "ISS_MurderSignExecute";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "SignOnPoorMurder";
			pchar.questTemp.LSC.killCost = 17; //������� ������ ����� �� ���������
			pchar.questTemp.LSC.usurerId = npchar.city + "_usurer"; //���� �� ������� � ����������
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "gate_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������� ����� 
		case "GiveKeyMan":
			dialog.text = "���?";
			link.l1 = "��, ��������, ��� �� ������ ������?";
			link.l1.go = "GiveKeyMan_1";
		break;
		case "GiveKeyMan_1":
			dialog.text = "�. � �� ��� ���"+ GetSexPhrase("��","��") +"?";
			link.l1 = "���� ����� ������� " + GetFullName(pchar) + ".";
			link.l1.go = "GiveKeyMan_2";
		break;
		case "GiveKeyMan_2":
			dialog.text = "� ��� ���� �����, ������� " + GetFullName(pchar) + "?";
			link.l1 = "��������, ��� �� ����� ������� � ���� �������-����������� ����������? ���� �������� ���� ����� ��, � ������.";
			link.l1.go = "GiveKeyMan_3";
		break;
		case "GiveKeyMan_3":
			dialog.text = "���, ��� � ������, ����� �. � ���� ������� ��� �������������, ��� �� �������"+ GetSexPhrase("��","���") +" �� ������. � ����� ��������� ������ ������! ����, ������, ����� � ���� - ���������� �����, �� �� ��� � � �������� �� �������. ��� ��� ������ � � ���� ��������� ������ ������!";
			link.l1 = "��, �������! ������, ��� ��� � �����. ��� ����� ����� ����� �� ������, ��� � �������-�����������.";
			link.l1.go = "GiveKeyMan_4";
		break;
		case "GiveKeyMan_4":
			dialog.text = "���, ���������� ������� � �� ����� - �� �����������, ������ ��! � ���� ������ ������� - ������� ������. �� � ��� ��� ������, ���������� ����� �������? ���� ����� ����� ���������.";
			link.l1 = "������, ��������, ��� ��� � ���� �� �����, � ��� � ���� ����...";
			link.l1.go = "GiveKeyMan_5";
		break;
		case "GiveKeyMan_5":
			dialog.text = "��! �� �� "+ GetSexPhrase("��������� ��������","��������� ���������") +", ��� � �������...";
			link.l1 = "��� ������, �������!!! �� ��������� ����� - ��������� �������...";
			link.l1.go = "GiveKeyMan_6";
		break;
		case "GiveKeyMan_6":
			dialog.text = "��������� �������, ��������?.. � ��� �������, ��� ���� ����� ������ ����.";
			link.l1 = "������ ���.";
			link.l1.go = "GiveKeyMan_7";
		break;
		case "GiveKeyMan_7":
			npchar.quest.price = makeint((6666 * ((sti(pchar.rank))/2)*MOD_SKILL_ENEMY_RATE*(100-(GetCharacterSkill(pchar, SKILL_LEADERSHIP)/2)))/100);
			Log_Info(""+npchar.quest.price);
			if (sti(pchar.money) >= sti(npchar.quest.price))
			{
				dialog.text = "�-�... ������! � ���� �� ���� ���� " + FindRussianMoneyString(sti(npchar.quest.price)) + ".";
				link.l1 = "��������, �������� ����!";
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = "��-�-�, "+ GetSexPhrase("��������, �� �� ����������","�������, �� �� ����������") +"!!! � ����� ��������� � ����� ����� ��������?! ������, � ���� ����� � �������� ������, ��� ���� �������� �� ��������. � ���� � ������ �������?";
				link.l1 = "��� ��� ������?!";
				link.l1.go = "GiveKeyMan_8";
			}
		break;
		case "GiveKeyMan_8":
			dialog.text = "��� ������, "+ GetSexPhrase("��������","�������") +", ��� ���� ��� ������� ������ ���� �� �� �������, �� ������ ��� � �����������. �������, ��� ����������� ��������, � ������ �� ���� �� ���.";
			link.l1 = "�����, ����� ���� �����...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeysNoMoney";
			NextDiag.TempNode = "GiveKeyMan_NoMoney";
		break;
		case "GiveKeyMan_NoMoney":
			npchar.quest.price = makeint((6666 * ((sti(pchar.rank))/2)*MOD_SKILL_ENEMY_RATE*(100-(GetCharacterSkill(pchar, SKILL_LEADERSHIP)/2)))/100);
			Log_Info(""+npchar.quest.price);
			if (sti(pchar.money) >= sti(npchar.quest.price))
			{
				dialog.text = "�� ���, ��� �����, ��� ���������... ����� �������� � ������ ��������� � �����. � �����, � ����� ��� ���� �������, �����������, �� " + FindRussianMoneyString(sti(npchar.quest.price)) + ".";
				link.l1 = "��-��, �������!!";
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = "���� � �� ���� �� ��� �� ������ �������������. �� ��� ���"+ GetSexPhrase("","�") +" ��� ����� � �������, ��� � �����"+ GetSexPhrase("��","���") +". ����� ������� ��� �� �����.";
				link.l1 = "��, ��������� ��� �������.";
				link.l1.go = "exit";
			}
		break;
		case "GiveKeyMan_10":
			dialog.text = "���������� �� ������. ���"+ GetSexPhrase("","�") +" ���������, � �� ������ ������! � �����, �������������� � ���� � ������. ����� �����!";
			link.l1 = "��, ������, ��� �������� ����� ������... ������, � �����, ������� ����?";
			link.l1.go = "GiveKeyMan_11";
		break;
		case "GiveKeyMan_11":
			dialog.text = "���, "+ GetSexPhrase("��������","�������") +". �� �� ���"+ GetSexPhrase("","�") +" ���������, � ��� �������...";
			link.l1 = "�������. ��� ��� ����?";
			link.l1.go = "GiveKeyMan_12";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
		break;
		case "GiveKeyMan_12":
			dialog.text = "��� ���� ����������. ������� �� ��� ������ ����� ���. � ���� � ���� �������� �� �������� � �������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			SetTimerFunction("LSC_openMasterHouse", 0, 0, 2);
			LocatorReloadEnterDisable("Villemstad_town", "houseSp5", true);
			npchar.location = "none";
			AddQuestRecord("ISS_PoorsMurder", "6");
		break;

		case "GiveKeyManInside":
			dialog.text = "���, ��� � ��!";
			link.l1 = "���, ��� � �! ��� ��� ����?";
			link.l1.go = "GiveKeyManInside_1";
		break;
		case "GiveKeyManInside_1":
			dialog.text = "����?.. ��, �� ������, ��� ��������� ��� ��������, �� � ����� ����� ������ ������������ �������-����������.";
			link.l1 = "�� ��� ��, ��������, ��������?!";
			link.l1.go = "GiveKeyManInside_2";
		break;
		case "GiveKeyManInside_2":
			dialog.text = "� ��� �� �����"+ GetSexPhrase("","�") +"? � �� �� ���� ��� ����... � �����, ��� �������, ��� ���� ��������...";
			link.l1 = "�� ��, �������! ��� � �� ����� ������ ����?!";
			link.l1.go = "GiveKeyManInside_3";
		break;
		case "GiveKeyManInside_3":
			dialog.text = "�� ������. ����-�� � ������, ��� � ������. � ����� ���� �����!";
			link.l1 = "��-��...";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("LSC_enterSoldiers");			
		break;
		//�������������� ������
		case "MK_HollOfficer":
			dialog.text = "��������� �� ����, �������!";
			link.l1 = "���� ���?";
			link.l1.go = "MK_HollOfficer_1";
		break;
		case "MK_HollOfficer_1":
			dialog.text = "� �������� ���������� ����������. �� ���������, ��� �������... � �� ��������� ������, ����� � ���� �������� ��������� ����!";
			link.l1 = "��, ������, ��� ���� � ���, ��� � � ���� ��������"+ GetSexPhrase("","�") +" ��������� ����...";
			link.l1.go = "MK_HollOfficer_2";
		break;
		case "MK_HollOfficer_2":
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//�������� ����� � ������
		case "PKInMarigo":
			dialog.text = "��, � �� ���������� ����������� � ���� ��� ���! �� ��� ��������� �������? �������� � ���������?";
			link.l1 = "�� ���, � ��������� ��� � �������. �� ������, ���� � ���, ��� � ����� �� ���� ����� ������ ������� - ������ ����.";
			link.l1.go = "PKInMarigo_1";
		break;
		case "PKInMarigo_1":
			dialog.text = "� ��� ������ �� ����������, �� ��� ��� �� �������. ������������ �� ���������.";
			link.l1 = "�������... �� � ���-����, ��� �����?";
			link.l1.go = "PKInMarigo_2";
		break;
		case "PKInMarigo_2":
			dialog.text = "� ���, ������ ������? ����� ��� � ��������� ������ �� ������. �� ��������� ����?";
			link.l1 = "�������, �������. �� ���-����, ����� �������� �� ������, ��� ��.";
			link.l1.go = "PKInMarigo_3";
		break;
		case "PKInMarigo_3":
			dialog.text = "���-�� ��� �� �������� ���� �������������. ���� ������ ���������� � ��� �� ����, �� ���������� �������� �� �������.";
			link.l1 = "������, �� �����...";
			link.l1.go = "PKInMarigo_4";
		break;
		case "PKInMarigo_4":
			dialog.text = "������� �� ������. � ������ �������� ����������� ������������ ������ �����������!";
			link.l1 = "������. � ����, ��� �� ��������� �������������� ����������� ����-������� �������� � ��������� ����. ���� �����, ��� �� ������ ���� � �������-������������ �����������. � ��� � ���� �����, ������ ����� ��� �� ������� ������� �������.";
			link.l1.go = "PKInMarigo_5";
		break;
		case "PKInMarigo_5":
			dialog.text = "� �� ������� �� ����� �� ������?";
			link.l1 = "��� ��� �� ��� ��� ������� � ���. � ���� ����� �� �������!";
			link.l1.go = "PKInMarigo_6";
		break;
		case "PKInMarigo_6":
			dialog.text = "�� ���� ���������, �� ��� ������, �������? �������� ���� �� ��������, ������� ��������� ��������� - ��� �� �������. �� ��� ����� � ���� ��������, ������� ����������� ����� ��������� ����� - ��� �������.\n"+
				"���������� ������ �� ���� �������������, �������� ������� - � ����������� ���������� �� ��������, ����� ��� ������� �� ������. � ��� ���� ����������� ����� ������ ������ ��� � ������. � ��� ��� ��������� ����, �������, ���� ������ � �����.";
			link.l1 = "�������, ��� ���� ������ � ������������ �� ����. � ���� ����� ��� ��� � � ��������� �������, ������� ��� �� ������� �� ��� ����������...";
			link.l1.go = "PKInMarigo_7";
		break;
		case "PKInMarigo_7":
			dialog.text = "�-�-�, �������, �����, ��� ���� ������� �����. ��� ������� ���� ��� ��������, ���� ��������: '� ������� ����� ����...'.";
			link.l1 = "�� � ��� �� ��������, ���� ����-�������?";
			link.l1.go = "PKInMarigo_8";
		break;
		case "PKInMarigo_8":
			dialog.text = "����. ������ ����� ������!";
			link.l1 = "��������� �� �������, ����� ������� ������...";
			link.l1.go = "PKInMarigo_9";
		break;
		case "PKInMarigo_9":
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_Attack(npchar, pchar);
			pchar.quest.PQ8_afterFight.win_condition.l1 = "NPC_Death";
			pchar.quest.PQ8_afterFight.win_condition.l1.character = "PoorKillSponsor";
			pchar.quest.PQ8_afterFight.win_condition = "OpenTheDoors";
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//���� � ����������
		case "LSCQuestMent":
			dialog.text = "��, ������, ��� ��� � ���� �� �������?";
			link.l1 = "�� ��� � ���?";
			link.l1.go = "LSCQuestMent_1";
		break;
		case "LSCQuestMent_1":
			dialog.text = "������ �������������! ����� ��� ��� ��������� � ����� �������.";
			link.l1 = "��� �����!..";
			link.l1.go = "LSCQuestMent_2";
		break;
		case "LSCQuestMent_2":
			dialog.text = "����� ����� � ��������������� ��������� ������. � ��� ���� �������� ��� ��� ���������� � ������ ����, ����� ������ ����� ����� ���������� �������.";
			link.l1 = "��� �� ��� �� �����? �� ���� ��� �� ���������!.. ��, �����, ���� �������� �������.";
			link.l1.go = "LSCQuestMent_3";
		break;
		case "LSCQuestMent_3":
			dialog.text = "���?!! �����, �� ���!";
			link.l1 = "��, ��� ������� �� ������? � ��� ���� �����������!";
			link.l1.go = "LSCQuestMent_4";
		break;
		case "LSCQuestMent_4":
			AddQuestRecord("ISS_MainLine", "9");
			pchar.questTemp.LSC = "afterFightInProtector";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = characterFromId("AndreLabor");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//��������� ������, �������� ���� ��������
		case "LSCQuestNarval":
			dialog.text = "��� �� ��� �������?!";
			link.l1 = "�? ��, ��� ���� �������...";
			link.l1.go = "LSCQuestNarval_1";
		break;
		case "LSCQuestNarval_1":
			dialog.text = "�� ���, "+ GetSexPhrase("��������","������") +", �� ������, ��� ��� - ���������� '��������'?";
			link.l1 = "�� ����...";
			link.l1.go = "LSCQuestNarval_2";
		break;
		case "LSCQuestNarval_2":
			dialog.text = "�� ���, "+ GetSexPhrase("��������","��������") +", ������ �����?";
			link.l1 = "��, ��... ������ ����� ������. ������, ��������, �� ��� �������� ���� �����.";
			link.l1.go = "LSCQuestNarval_3";
		break;
		case "LSCQuestNarval_3":
			AddQuestRecord("ISS_MainLine", "11");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","���"));
			pchar.questTemp.LSC = "toAdmNarvalRing";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--------------------------- ���� ������ ����� ����� --------------------------------
		//������� ������ ����� �����
		case "SharpCapitain":
			dialog.text = "������ ����� �� �������, "+ GetFullName(pchar) + "?";
			link.l1 = "������ �������, ������ ������. ��� ���������� ������ ������� �� ��������� ����� �������.";
			link.l1.go = "SharpCapitain_1";
			link.l2 = "� ����� ���������, ���������!";
			link.l2.go = "SharpCapitain_fight";
		break;
		
		case "SharpCapitain_1":
			dialog.text = "������... �� ������ �� ���������, ����� ����� ���������� ����� �� �������� �� ���" + GetSexPhrase("","�") + " �� � ���� ������ ��� �� ����� ������������ ����� ������ ������������. �� ������ ��� ������, ��� ����������� ������� ������ ������� �������� ������� ��� ���...";
			link.l1 = "������ ��� ������, ��� ������ �� ����� ������ ��������. � ���� � ����� ���������� ���������� ���������. ������� �� ��� � ������� � ������ �������� � ����������!";
			link.l1.go = "SharpCapitain_2";
			link.l2 = "� ����� ���������, ���������!";
			link.l2.go = "SharpCapitain_fight";
		break;
		
		case "SharpCapitain_2":
			dialog.text = "� ���� ������� ��������� ����� ���� �� ������������... ���������, ��������? ��� ��, � � ����� �������, �������!";
			link.l1 = "����� ���������� � �������, ������!";
			link.l1.go = "Sharp_hired";
		break;
		
		case "Sharp_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Sharp")].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("SharpOf", "Sharp", "man", "man", 20, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade25", "pistol6", 120);
			sld.name = "����������";
			sld.lastname = "����";
			sld.greeting = "Gr_Officer";
			sld.rank = 20;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // ��������
			//SetSelfSkill(sld, 30, 30, 30, 30, 30);
			//SetShipSkill(sld, 30, 50, 30, 35, 80, 35, 30, 35, 30);
			SetSelfSkill(sld, 40, 40, 40, 40, 40);
			SetShipSkill(sld, 50, 50, 50, 50, 60, 40, 30, 40, 30);
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 10);
			LAi_SetHP(sld, 200.0, 200.0);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();	
		break;
		
		case "SharpCapitain_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		
		case "zpqCapitain":
			dialog.text = "� ���� ��� ���������� ���� ����� ����. ������� ������ �� �����, "+ GetFullName(pchar) + ", ���� ������ ����.";
			if(makeint(Pchar.money) >= 300000)
			{
				link.l1 = "���� ������� ��������, � ��� ������� ��������. �� ������� �� ������ �������. � ��������� ��������� ���� ����� � ���� ������ ������ �� �����, ���� ������� ������� ��� ���� �������. ����...";
				link.l1.go = "zpqCapitain_1";
			}
			
			link.l2 = "� �� ����� ������� ������! �� ���� �� ������ ������ ��� ����� ��������!";
			link.l2.go = "zpqCapitain_fight";
		break;
		
		case "zpqCapitain_1":
			dialog.text = "�� ����� ����������. ����� ��� �� ����� ������ �� ����. � ��������.";
			AddMoneyToCharacter(Pchar, -300000);
			link.l1 = "����� ���������� � �������, ������!";
			link.l1.go = "zpq_hired";
		break;
		
		case "zpq_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex(npchar)].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("zpqCaptainOf", "Lil_Jim", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 40, 105, 105, "blade23", "pistol3", 120);
			sld.name 	= "���������";
			sld.lastname = "������";
			sld.greeting = "Gr_Officer";

			sld.rank = 30;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // ��������
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 70, 75, 75, 75, 80, 70, 70, 70, 70);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "Medic");
			AddItems(sld, "talisman3", 1);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
            DialogExit();	
		break;
		
		case "zpqCapitain_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		
		case "BlueBirdCapitain":
			dialog.text = "����� �� � �����, ��� �� ���"+ GetSexPhrase("��","��") +"...";
			link.l1 = "���� ����� " + GetFullName(pchar) + ". � - �����.";
			link.l1.go = "BlueBirdCapitain_1";
		break;
		case "BlueBirdCapitain_1":
			dialog.text = "� ������ ������� �� �����"+ GetSexPhrase("","�") +" �� ��� ������?!!";
			link.l1 = "��� �����, � ����"+ GetSexPhrase("��","��") +" ������� ��� �� ���. �� ������� �� ��������� ��������� � ����������...";
			link.l1.go = "BlueBirdCapitain_2";
		break;
		case "BlueBirdCapitain_2":
			dialog.text = "� ��� ����� �������?! ���"+ GetSexPhrase("","�") +"-�� �� ����, ������, ��������� �� �������...";
			link.l1 = "��� ������, ��������, ������ �������. �� ��� ��� ��� ����� �����, ��� �� � �������� ����� �������������? ��� ������ ���������, �� ����� ������ ������ ��� ����.";
			link.l1.go = "BlueBirdCapitain_3";
		break;
		case "BlueBirdCapitain_3":
			dialog.text = "�� ���� ����, ��������! �� ��������� ��������� ���� �������, � ������ ���������!";
			link.l1 = "��, ������...";
			link.l1.go = "BlueBirdCapitain_4";
		break;		
		
			case "BlueBirdCapitain_4":
			dialog.text = "�������... ��������, � �������� ���� ������. �� "+ GetSexPhrase("��������� � �������� ������","��������� � �������� �������") +", � �... � �������� ���� ����. � ���� ��� ������ �����, � ��� ��� ������� - �� �������"+ GetSexPhrase("","�") +" �������. ���� ���� ��� �������� ���� ������ �����, ����� ��� ����� ����\n�����, ����� ��������� ����? � ��������� ������� ������ �� ��� � ����� �������� � �����, ��� ����� �������.";
			link.l1 = "���, ���. � ���� �� ����. ������� - �� ��� ������, � ������ - �������� ������ � �����? ���� ��������� ���� ��������������!";
			link.l1.go = "BlueBirdCapitain_5";
			link.l2 = "��! ��� ��� ���������! � �� ������, ��� - � ������"+ GetSexPhrase("��","��") +". ������ �������, ��� ��, ��� �������� ����. �� ������ - �������� ����� ������ - ����� �� ���� ��������!";
			link.l2.go = "BlueBirdCapitain_6";
		break;
		
		case "BlueBirdCapitain_6":
			dialog.text = "�������������� �������, �������. ��� ���� ������ ����� ���������� ����� �� ���������� - ���� ��������. ������ �� ��� �� �����������. � ���, ��� �� ������������.";
			link.l1 = "����� ���������� � �������, ������!";
			link.l1.go = "Ja_hired";
		break;
		
		case "Ja_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Jafar")].lifeDay = 0;
			sld = GetCharacter(NPC_GenerateCharacter("Jafarry", "QuestCaptain", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade14", "pistol6", 100);
			sld.name = "���";
			sld.lastname = "�������";
			sld.greeting = "Gr_Officer";
			sld.rank = 30;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // ��������
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 70, 75, 75, 75, 80, 70, 70, 70, 70);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "Medic");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
		
		case "BlueBirdCapitain_5":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		//�������� ������� ���������
		case "BlueBirdTrader":
			dialog.text = "���� ������, ������ �� ������ �� ���?!!";
			link.l1 = "��� ��������� ������ �������, ��������. ������ ���� � ������ �� ����.";
			link.l1.go = "BlueBirdTrader_1";
		break;
		case "BlueBirdTrader_1":
			dialog.text = "������� �������...";
			link.l1 = "������ ������ ������, � � ��������� ������� ������ ������������ � �������. �����, ��� " + GetFullName(pchar) + " �������� ��� ������.";
			link.l1.go = "BlueBirdTrader_2";
		break;
		case "BlueBirdTrader_2":
			dialog.text = "������ ������� �����������.";
			link.l1 = "����� �� ���� ���. ���� ����...";
			link.l1.go = "BlueBirdTrader_3";
		break;
		case "BlueBirdTrader_3":
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
		//--------------------------- ��������� ��������, ���� --------------------------------
		//������� ����, ������ ����� �� ������
		case "DeckSharp":	//�� ������
			dialog.text = ""+ GetSexPhrase("����������, ��������. ���� ������ �� ������������ ������ ���� �� ���� �����","��-�, ����� � ��� �����! ���� ������ �� ������������ ������ ���� �� ���� �����, ���������� ��������") +"?";
			link.l1 = "����������� �������� ���������� �����! � ������ ��������"+ GetSexPhrase("","�") +" ����...";
			link.l1.go = "DeckSharp_1";
			npchar.quest.meeting = true;
			//���������� ����������, ���� ���� ������ �� �������
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("��������","�������") +", � ������ �����! ����� ���� ������ �� ����. ��� ����...";
				link.l1 = "�� �����, �������...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "DeckSharp_1":
			dialog.text = "��, ��� �������... ��� ��� ������� ���� �� ���"+ GetSexPhrase("",", ���������") +"?";
			link.l1 = "�� ������, ��������, � ���� �� ��������� �������� ����������. �������������, ��� �������...";
			link.l1.go = "DeckSharp_2";
		break;
		case "DeckSharp_2":
			dialog.text = "�-�-�, ����������� ����!!! ��� ����� ��������? �����������!";
			link.l1 = "�������� � ���, ��� � �� ����, ��� ��� �������� �����. ��� �� ����� �������� � ������������ ���������! ���, ����"+ GetSexPhrase("��","��") +" � ���� �� ������� ��� � ����������� � ���� ����.";
			link.l1.go = "DeckSharp_3";
		break;
		case "DeckSharp_3":
			dialog.text = "��, �� ��, ����� ������� ����� ������ �����, ������ ������ �� �� ��������\n�� ��� ��, ������ ���� ��� ������� ����, ��� ������� �� ��������.";
			link.l1 = "��, ����, �������, ������� ����!";
			link.l1.go = "DeckSharp_4";
		break;
		case "DeckSharp_4":
			dialog.text = "�� ���� �� ���, �� ����� ��������������\n� �����, ������ ��������� ������ ����. ����, ����� ������� ����� ���� ����� ���������, ���������� ������ � ����������� �������� ��� �������� �� ����������, ��� �������\n������� ���������� ����� �� �����������, ��� ���, ����� ��� � ���� � ���������!";
			link.l1 = "������, � ��� �� �������, ��� ��� ����� � ������ ������?";
			link.l1.go = "DeckSharp_5";
		break;		
		case "DeckSharp_5":
			dialog.text = "��� ��� ������� ������. �� ����� ������"+ GetSexPhrase("",", ���� ����� �������, ��� ��") +", ���� �� �����!";
			link.l1 = "��, �� �����, ��� ������...";
			link.l1.go = "DeckSharp_6";
		break;
		case "DeckSharp_6":
			GetPerlShore(); //��� �������� �������
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add; 
			dialog.text = "������, ������. ���� �� " + XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Dat") + " �����, ��� ��������� " + GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") +
				sTemp + ". ���� �� ������� ���� �� " + FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)) + ", �� ����� ������� ����� ���.";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ������� ����, ����������.";
			link.l1.go = "DeckSharp_7";
		break;
		case "DeckSharp_7":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("���� ���� ������� ����! ��� ��� ������ ��������","��� ���� - ������ �����, ���������") +".", ""+ GetSexPhrase("� �����������, ����� ���� �������� ������� ����","��� ����� �������, ��� �� - ������ �����") +"!");
			link.l1 = "��, ����. ������� ����, "+ GetSexPhrase("������� ����","�����") +". �� ��� ������� �����!";
			link.l1.go = "DeckSharp_8";
		break;
		case "DeckSharp_8":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("�� �� �� ���, ��������, ����� ��� - ���������...","��������� ���, ��� ���������. � �����, ���-������ ����������, ��� �������, � ������������� ����������?") +"",""+ GetSexPhrase("�������� �������� - ��������� ����, ��� �������... ������ ���, ��� ����� - ������!","������ ���, ��� ����� - ������. " + pchar.name + ", � �����, ��������� ���� �������...� ������, ����� ������ �����?") +"");
			link.l1 = ""+ GetSexPhrase("�������������, ������� ����!!","�� ������������ �������, �����. ��� ��������!") +"";
			link.l1.go = "DeckSharp_8exit";
		break;	
		case "DeckSharp_8exit":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add; 
			NextDiag.TempNode = "DeckSharp_over";
			npchar.DeckDialogNode = "NewDeckSharp"; //����� ���� �� ������
			pchar.questTemp.Sharp = "toPearl"; //���� ������ - �� ��������!!!
			AddQuestRecord("SharpPearl", "5");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase("��, �������� �����!","�������� �����..."));
			AddQuestUserData("SharpPearl", "iDay", FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
			AddQuestUserData("SharpPearl", "sAreal", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Dat"));
			AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") + sTemp);
			pchar.quest.SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.SeaPearl_login.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
			pchar.quest.SeaPearl_login.function = "SeaPearl_login";
			SetTimerFunction("SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������� ����, ����������� ��������� �� ������
		case "NewDeckSharp":
			dialog.text = "�-�-�, ���� � ����?! ����������� "+ GetSexPhrase("���������������","����, ���������") +"!";
			link.l1 = "����������, ������� ����. ��� ���������?";
			link.l1.go = "NewDeckSharp_1";
			//���������� ����������, ���� ���� ������ �� �������
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("��������","�������") +", � ������ �����! ����� ���� ������ �� ����. ��� ����...";
				link.l1 = "�� �����, �������...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "NewDeckSharp_1":
			dialog.text = "�� ��� �����, "+ GetSexPhrase("��������","��������") +", ���������� ����\n��, �����������, ����� ���������"+ GetSexPhrase("","�") +" �� ���� ���?";
			link.l1 = "�� ��� �� ��� ��, ��������, �� �������� �� ��������...";
			link.l1.go = "NewDeckSharp_2";
		break;
		case "NewDeckSharp_2":
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow" || pchar.questTemp.Sharp.SeekSpy == "over")
			{
				dialog.text = "�� ������, "+ GetSexPhrase("��������","��������") +", � ���� � ���� ����� ��������. ������ � ���� ���� ���������� ������� �� �������, � � ���... ��, � �����, �� ���� �, ��� �����.";
				link.l1 = "�-��, ��������... �� ��� ��, ������ �����. ������, ����.";
				link.l1.go = "exit";
				CloseQuestHeader("SharpPearl");
				NextDiag.TempNode = "DeckSharp_noWork";
				pchar.questTemp.Sharp = "over";
			}
			else
			{
				dialog.text = "��, ���� ���, �������, �������. �� � �� ���� ������������ ���� ������ �� ����,  "+ GetSexPhrase("��������,","��������,") +" ��� ������ ���� ����!";
				link.l1 = "����� ������ ������������?";
				link.l1.go = "NewDeckSharp_3";
			}
		break;
		case "NewDeckSharp_3":
			dialog.text = "������������. "+ GetSexPhrase("�� ���� ����, ����������","�� ������������, ��� ����� �� �����") +".\n� �����, � ���� ������� ���� ����, �� �� ������ ���. �� ����"+ GetSexPhrase("��","��") +" ������ ��� �������������� ��������� ������, "+ GetSexPhrase("��������","��������") +".";
			link.l1 = "��, �� � ������� �� ������?";
			link.l1.go = "NewDeckSharp_4";
		break;
		case "NewDeckSharp_4":
			dialog.text = "��, �������, ��� ����� � " + FindRussianMoneyString(sti(pchar.questTemp.Sharp.price)) + " ���� �������.";
			link.l1 = "��, ���� ������� ����, ��� �� ����? ��� ������� ����� ��� ���� �� ������ ������! ���� ������, ������ ����.";
			link.l1.go = "NewDeckSharp_noMoney";
			if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
			{
				link.l2 = "�� ��� ��, � ������"+ GetSexPhrase("��","��") +", ��������. ������� ���� �����������!";
				link.l2.go = "NewDeckSharp_GiveMoney";
			}
		break;

		case "NewDeckSharp_GiveMoney":
			dialog.text = "��, ��� � �������! ����� ������ ��� �� ����, "+ GetSexPhrase("��������","��������") +".";
			link.l1 = "��� �������. ��� ��� ��� � ��������?";
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_noMoney":
			if ((sti(pchar.questTemp.Sharp.price)*10) < sti(pchar.money))
			{
				if (pchar.location == "Deck_Near_Ship")
				{			
					dialog.text = ""+ GetSexPhrase("���� ������! �� ����, " + pchar.name + ", ���� �����?! � �� �� ����� �����, � ������� ����!! ������ �����, �����?! �������, � �� ����, ��� ����� � ���� �������� �������? ����, ��������, ��� ��� ��������� ��������. ��� ���, �����, �������������� ��� ���� � ���� ������ �� ��� ������ ������� ������������ ����-�����!","���� ������! " + pchar.name + ", ��, �������, ������ �������� � ������, ������ � � �� ����� �����, � ������� ����! ������ �����! �������, � �� ����, ��� ����� � ���� �������� �������? ����, ��������, ��� ��� ��������� ��������. � ��� � ����� ������� ���������...���, ����, ������, ��� ������ �������. � �����, ��� ��������������, ��� ��� ����������� ��������������") +"..";
					link.l1 = ""+ GetSexPhrase("����������, �� ���� �������?! ��������, ��� �������... � � ���� �� ������ ������ �������� � �� ����� ������. ��� ��� �� ���������� � ����������. �����, � ��� ��������������","����������, �� ���� ������������? �� ���, ���������� � ����������, � ���� �� �����-������ ��� ����� ����������, �� ������� �����") +"...";
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("��-�� � �� �����, �� ���� �� ���� �������? �� ���� ���� ������, �������, � �� ����, ��� ����� � ���� �������� �������? ����, ��������, ��� ��� ��������� ��������. ��� ���, �����, �������������� ��� ��� ������ ������� ���-������ �� ����-����-��� ������, � �������","��, " + pchar.name + ", �� ���, ���� �������� ���������? �� ���, �������, � �� ����, ��� ����� � ���� �������� �������? ����, ���������, ��� ��� ��������� ��������. � ��� � ����� ������� ���������... �� ������� ����, ����. ��� ���, ��� ������ �� ����, ��� ������ ������� ���-������ �� ����-����-��� ������, � �������") +"...";
					link.l1 = "����������, �� �� ��������, � �� ��������, ��� �������. �����, � ��� ��������������...";
				}
				link.l1.go = "NewDeckSharp_5";
			}
			else
			{
				if (sti(pchar.questTemp.Sharp.price.evil))
				{	//���� �� � ����������
					dialog.text = "���, "+ GetSexPhrase("��������","��������") +", ������ �� �������! � ���� ������ ���� ���� �������, � ��� ��� �� �� ������ ���������. � �������� � �� �����������. ������ �� �����, � �����...";
					link.l1 = "�-��, ����, ����, ����� ����. � �����"+ GetSexPhrase("","�") +", �� ��������� ����...";
					link.l1.go = "NewDeckSharp_7";
					if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
					{
						link.l2 = "��, �������� ������. �� �� ������ ��� ������� �� ������� ��� ������� ���������� �������... ������� ���� �����������!";
						link.l2.go = "NewDeckSharp_GiveMoney";
					}
				}
				else
				{
					dialog.text = "�� �����, ��� �� � ����, ������� � ������ ����-�� �� � ����... ������ ����!";
					link.l1 = "��� ��� ���������! ��� ��� ��-��������-�������!.. ��� ��� ��� � ��������, ����������� ����?";
					link.l1.go = "DeckSharp_6";
				}
			}
		break;
		case "NewDeckSharp_5":
			dialog.text = "�����, ������, �����������. ������, ��� ���� ���� �� ������. �� ���� ���� ���"+ GetSexPhrase("��","��") +" �������, " + pchar.name + ", ��� ����� ���������� �� ����� ����... � �����, ������ �� �����, ��� ������� �� �� ��������.";
			link.l1 = "�� ������, ������� ���� �����������!";
			link.l1.go = "NewDeckSharp_6";
			link.l2 = "��-�, ������� � �� ����� ����. ����� ���-������...";
			link.l2.go = "NewDeckSharp_7";
		break;
		case "NewDeckSharp_6":
			dialog.text = "�� ���, ��� ������ ����! ������ ��������, ������� � �������"+ GetSexPhrase("��","��") +"!"+ GetSexPhrase(""," � ������, ������ ������������� �������!") +"";
			link.l1 = "�������, ����, �������. ��, ��� ��� ��� � ��������?";
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_7":
			dialog.text = "��, ��� ������. ������!";
			link.l1 = "����� ��������...";
			link.l1.go = "NewDeckSharp_7exit";
		break;
		case "NewDeckSharp_7exit":
			AddQuestRecord("SharpPearl", "10");
			CloseQuestHeader("SharpPearl");
			pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
			pchar.questTemp.Sharp.brothelChance = rand(10);
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
		break;

		case "DeckSharp_over":
			dialog.text = "�� ��� ��������, "+ GetSexPhrase("��������","�������") +". �� ����� ����� � �� �� ���� ������ �������.";
			link.l1 = "��, ������� ����.";
			link.l1.go = "exit";
		break;
		case "DeckSharp_overBad":
			dialog.text = "���������� ���...";
			link.l1 = "�� ��...";
			link.l1.go = "exit";
		break;
		case "DeckSharp_noWork":
			dialog.text = "����� �� ���� ������, "+ GetSexPhrase("�������","��������") +". ��� ������� ��� ����. ������ �������� ����� �� ��������� ��������...";
			link.l1 = "��, � ������������, ��������!";
			link.l1.go = "exit";
			CloseQuestHeader("SharpPearl");
		break;
		//������� ����, ������ �������� � ������ �� �����
		case "CitySharp":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "�-�-�, ������� " + pchar.lastname + "! ������ ���� �����������.";
				link.l1 = "����������, � ��� ���"+ GetSexPhrase("","�") +" �������! �������� ���� ��������, �� � ���� ������ �������...";
				link.l1.go = "CitySharp_1";
				npchar.quest.meeting = true;
			}
			else
			{
				dialog.text = "��, ���� � ���� � ���� ������?! ��� �� "+ GetSexPhrase("������� " + pchar.lastname + ", ��� �������� � ��������������","" + pchar.name + ", ��� ��������� � ���������������! �� ���������, ��� �������") +"!";
				link.l1 = "��, ����������, ��� �"+ GetSexPhrase(" ����������� ��������",". ������� �� ����������") +".";
				link.l1.go = "CitySharp_2";
			}
		break;

		case "CitySharp_1":
			dialog.text = "���, ���� ������ �� ����� ��������?";
			link.l1 = "���������, � ��� ������"+ GetSexPhrase("��","���") +" ���������� �� ��������� ��������, � �� � ���� ���� ���������� ����������.";
			link.l1.go = "DeckSharp_2";
		break;
		case "CitySharp_2":
			dialog.text = ""+ GetSexPhrase("��, �������, ��� ���� ������! �� ���, ������, �������... ������� � �����, ����� �� ������. �� ����� �������������, ������� ��� �����? � ���� ��� ����� ����� - �����������","�-�-�, " + pchar.name + ", ����� � ���� ����, � ���� ������ �� ��������") +"!";
			link.l1 = "������, "+ GetSexPhrase("����","����������") +", ��� ������ �� �� "+ GetSexPhrase("�����","������") +", ������. � �� ���� � ����.";
			link.l1.go = "CitySharp_3";
			//���������� ����������, ���� ���� ������ �� �������
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("��������","��������") +", � ������ �����! ����� ���� ������ �� ����. ��� ����...";
				link.l1 = "�� �����, �������...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "CitySharp_3":
			dialog.text = "��-�-�, "+ GetSexPhrase("��� �� ���������","��� ��� ������") +"... � ��� �� ����?";
			link.l1 = "�� ���, �����"+ GetSexPhrase("","�") +" �������� ������ ������� �� �������...";
			link.l1.go = "NewDeckSharp_2";
		break;
		//������� ���� � �������
		case "BrothelSharp":
			dialog.text = ""+ GetSexPhrase("�-�-�, " + pchar.lastname + ", �������!! ������ �� ���� ������, ��� ��� ������!!!","�-�-�, " + pchar.name + ", ��� ��, ���������? �� ���, ������ � ����� ���� ����� ������ ������ ������ � ����...") +"";
			link.l1 = ""+ GetSexPhrase("���, ��������, ������ �� ����, �����.","�� ����� ����, ����������, ������ �� ������ �����..") +". � � ���� �� ����";
			link.l1.go = "BrothelSharp_1";
			//���������� ����������, ���� ���� ������ �� �������
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = ""+ GetSexPhrase("��������","��������") +", � ������ �����! ����� ���� ������ �� ����. ��� ����...";
				link.l1 = "�� �����, �������...";
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //����� �������� � ��������
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "BrothelSharp_1":
			dialog.text = ""+ GetSexPhrase("������...","��, ������ ���� ������, " + pchar.name + ". �� �����, ��� ��� � ����?") +"";
			link.l1 = "���� ����� ���������� � ������ �������, �������� �� �������.";
			link.l1.go = "NewDeckSharp_2";
		break;
		//������ ������. � ����� ���-���� ���� �����
		case "SharpSeekSpy_Emi":
			dialog.text = "������, ��� ������������!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog");
		break;
		case "SharpSeekSpy_fri":
			dialog.text = "�-�-�, �� ��� �� ������� " + pchar.lastname + "! ��� �� �� ������ ��� ����� �������...";
			link.l1 = "���, �������! � � ���� ����, ��������?";
			link.l1.go = "SharpSeekSpy_fri_1";
		break;
		case "SharpSeekSpy_fri_1":
			dialog.text = "��, ��� �������... ��, ����� ����, ���� �� �����������, �� � ��� �������� ������, ����� �� �������� ��� ���� '����������'.";
			link.l1 = "��! ��� �� �� ������� �����?! ������, � ������"+ GetSexPhrase("","�") +" ����� �� ������.";
			link.l1.go = "SharpSeekSpy_fri_2";
		break;
		case "SharpSeekSpy_fri_2":
			dialog.text = "�� ������� ������ ����������, �������.";
			link.l1 = "���������, ��������, ��� ���� ����� ��������� ������, ��� �� ���� ������� ����� �� ������� ������. ������ �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "SharpSeekSpy_fri_3";
		break;
		case "SharpSeekSpy_fri_3":
			dialog.text = "�������, �� ��� ����� ���� ����� � �����...";
			link.l1 = "���, � ��� � "+ GetSexPhrase("������� � �����","����������") +". � ���� �� ��� ����� ����� ����� ����� ���-��� �� ��������� ���������...";
			link.l1.go = "SharpSeekSpy_fri_4";
		break;
		case "SharpSeekSpy_fri_4":
			dialog.text = "� ��� �� ���� �������� ����?";
			link.l1 = "�-�-�...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_2");
		break;
		case "SharpSeekSpy_Emi_1":
			dialog.text = "� ���, �� ����? �������, ���-�� �� ��������!\n������, ���� ������ "+ GetSexPhrase("���","��") +". �� ����...";
			link.l1 = "��, ����������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_3");		
		break;
		//--------------------------- ����� ���������� --------------------------------
		//���������
		case "WaitressBerglar":
			dialog.text = "�����, ��������, ����������� �������.";
			link.l1 = "����?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "����! ����� �������, ��� ����������. �� ����� � �����...";
			link.l1 = "��� ��� ��������!! � " + pchar.questTemp.different.FackWaitress.Name + " � ����� � ���� ��������, ��� ��?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "� ����, � ����... ����������� �������, �� �� ������ ����!";
			link.l1 = "����� � ���! �� ���� ������� � ��� ���� ������ ������...";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "�������, ��������! �� ��� ��� ��� ������ � ��� �� ������...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "�������, �� ������, ��� �� ������? ��, ������ �������. � ����� - �� ����� �� ��������, ����� �� ���� ���������� � ���� ��������. ������ ������ �����!";
			link.l1 = "��� �����!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "��, ��� ������...";
			link.l1 = "����, ����, ��������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//����������
		case "Waitress":
			dialog.text = "� ��� � �! �� ����������, ���������?";
			link.l1 = "�� �����...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "��, ����� �� ����� ������ �������!";
			link.l1 = "��, ��������!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		//--------------------------- ������� ����, ����������� ������� ������ --------------------------------
		//�������� � ������
		case "PortmansCap":
			dialog.text = "������������. ���� ����� " + GetFullName(npchar) + ". � ������� " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'."; 
			link.l1 = "�������! �������-�� � ���� ���"+ GetSexPhrase("��","��") +"...";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "���"+ GetSexPhrase("��","��") +"?!";
			link.l1 = "���. � �����, � ������"+ GetSexPhrase("","��") +" ���� ���� ������� ������. ������� �� ����� � ���������� ����� " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "������, ��� ��� ��� � ��� '������'! �� ��, ��� ������� ���� ���� �� ������� � ����� �� �������...";
			link.l1 = "��, ��� ������, ��� ������ ���������. ������� ���� ������ � ����� ��������� � ���� �������� �� �����.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "����� ������ � ��� �� �����, ��� ��� ���������, ������� ������� �������� �� ����, ��� ���� ���� ���������. " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ������� ���� ������ ��������������.";
				link.l1 = "��, �������. ������� ���� ������.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //��������� ��������������
					dialog.text = "��, �� ������, � ��� ����� ����� ������. ��� �� �����, ������ ������ ��� ����� ���, ���������� ��� ��������� � �����. ��� ��� � ���� ������� ��� �� " + FindRussianMoneyString(sti(npchar.quest.money)) + ". � ������� ���� ������ ��������������.";
					link.l1 = "�� ��� ��, ������������. ������� ���� ������!";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "��� � ����� ����� ������ ���. � ��� ������ ������� �� ������ ������� ����, ��� ��� ����� � �����. ��� ��� ��� ������ ������ ������ �������� �� �����. � ������ ��������� �� ���� � �� ����.";
					link.l1 = "������ ������? ��� �, ��� �� ����� �����"+ GetSexPhrase("��","���") +"?";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "������� ����. ��, ����� ��������, "+ GetSexPhrase("��������","�������") +".";
			link.l1 = "� ���� ���� ��...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //������� ������ �� ����� � ����
			npchar.LifeDay = 2; // ����� ���� ���� ������� ����
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //������ ������, �� ������ ������
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //����������� ������ ���� ������ ��� ��������
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "��, ���� �� ����"+ GetSexPhrase("��","���") +" ��������, �� ���� ���� �����������.";
			link.l1 = "��, ���� �����... �� �����, ������� ���� ������ ������ ���.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //������� ������ �� ����� � ����
			npchar.LifeDay = 2; // ����� ���� ���� ������� ����
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //������ ������, �� ������ ������
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //����������� ������ ���� ������ ��� ��������
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//������ � ����
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "����������� ���� �� ������ ����� �����. ������ ������, � ��, ����, ��������� - �����, ��� ��� ���������� ���� ������ ����� ����������� �� ����...";
				link.l1 = "�� ���, ��������, ������� � ����"+ GetSexPhrase("��","��") +". � ����������"+ GetSexPhrase("","�") +" ����, ����� ������.";
			}
			else
			{
				dialog.text = "����������� ���� �� ���� ������! ��� �� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = "����������"+ GetSexPhrase("","�") +" ����, ��������. ��� ������"+ GetSexPhrase("","�") +"...";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "����������"+ GetSexPhrase("","�") +"? � �����?";
			link.l1 = "�� ����� ���� ������� ������ � ���������� ����� " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ". ������ � ����! ������� � ����������"+ GetSexPhrase("","�") +", ����� ������.";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "����, ���, ������, ��� ��� � ��� �������!.. ��� ������ ������, "+ GetSexPhrase("�������, ","") +"��� ����. � �� � ���� ������������ ������� �� �������... ������� ���� �������.";
				link.l1 = "��� ������ ��������������?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //��������� ��������������
					dialog.text = "����, ���, ������, ��� ��� � ��� �������!.. ������� ����, �������, �� ���� � ���, ��� �� ����� ���� �����"+ GetSexPhrase("","�") +", � � ��� ����� �����. ������, ��������� ���-��� ��� ������ �����, ������� � ������ ������ � ����. �� ����� ��������� �� ����...";
					link.l1 = "� ������� ������?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "����, ���, ������, ��� ��� � ��� �������!.. ������� ����, �������, �� ���� � ���, ��� �� ����� ���� �����"+ GetSexPhrase("","�") +", � � ��� ����� �����. ������ ������ ������� �� ������, ��� ��� ��� �� �� �����.";
					link.l1 = "���, ������ ���� ������ ������ �� �����? ������?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "� ����� ��������� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ���� �������� ������� ����� ������ ��������������. ��� ���, ��� � ���� ���� ���������.";
			link.l1 = "��, ������. ��� ���� ������.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "������� ��� ���. ������, "+ GetSexPhrase("�������, ","") +"� ���� ������"+ GetSexPhrase("","�") +".";
			link.l1 = "� ���� ��������.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // ����� ������ ���� ������� ����
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //���� ���� ����� ��������. �������� �������� �� ���������� � ��������
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //����������� ������ ���� ������ ��� ��������
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "���������"+ GetSexPhrase(", �������","") +". �� ������� ����� ���� �����"+ GetSexPhrase("","�") +", ����� ���� ������������.";
			link.l1 = "���, ����� ���� �� ������ �������, ����� � � �� �� �����"+ GetSexPhrase("��","���") +" ��� �����. �� �� �����, ������� ���� ������ �����, ��� �� ���� �� �����.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // ����� ������ ���� ������� ����
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //���� ���� ����� ��������. �������� �������� �� ���������� � ��������
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //����������� ������ ���� ������ ��� ��������
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "�����, ��� ������ ���.";
			link.l1 = "��, ��� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- ������ ����������� ������� --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "�����������. ��� ���� ����� � ���� �� �������?";
			link.l1 = "�� ���, ��������� ���������� �����"+ GetSexPhrase("","�") +". �����, ��� ��������� � ����...";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "������ �� ���������, � �������� � ���� ���. � ������, ������ ������, ���� ����������� � ���� �� ������ ������������. �������, ���� ���������?";
			link.l1 = "�� ���� �� �����... �� �����, �����, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "������ ��, ��� ���� ��� ������ ������!";
			link.l1 = "�������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//�������
		case "SeekCap":
			dialog.text = "����� �� �����"+ GetSexPhrase("","�") +" �� ���?!!";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" ������� ������� ��� ���������.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "������ ���������?! � � ���� ��������!";
			link.l1 = "���, ��� �� ���. ��� ������� �������� - � � ���"+ GetSexPhrase("","�") +" �� ����, �� � ����, ��� ������� ������� �� ������� ������ �� ������. � ����"+ GetSexPhrase("��","��") +" ��� ������� �� �����.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "������! ��, ��� ���� ��� �� ��� ��������. � ���-���� ��������� ��������� ���� �� ��� ����...";
			link.l1 = "��, ���������...";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		//--------------------------- ������ ������ � ������ --------------------------------
		case "ChurchBerglar":
			dialog.text = "��� ��� ��! �� ���� ��� ��� �������?!";
			link.l1 = "�? ������� �������.";
			link.l1.go = "ChurchBerglar_1";
		break;
		case "ChurchBerglar_1":
			dialog.text = "��, �� ���� ��... � ��� ������?";
			link.l1 = "������, ��� ����.";
			link.l1.go = "ChurchBerglar_2";
		break;
		case "ChurchBerglar_2":
			dialog.text = "��, �������, ������, "+ GetSexPhrase("�������","�������") +", �� ���"+ GetSexPhrase("��","��") +" ���� ������ �� ����. ��� ����� ����, �� ���� ���� ���� ������� �� ��� ������...";
			link.l1 = "��! � ��� ��� �� ����. ������ ������� - ��� �������. ��� ��� ��� ������ ��������� �������� ���� � ��������.";
			link.l1.go = "ChurchBerglar_fight";
		break;
		case "ChurchBerglar_fight":
			LAi_LocationFightDisable(&locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- ����� �����, ���� ������ ����������� --------------------------------
		//========= ������ ������� ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("������������, �������. ���� ������� ��� ������ ���.", 
				"�������! �� ������� ��� ������? ���� � ���, ��� � �������� � ������.", 
				"�������, � ����� ��� � ������!");
			link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +", �� �������!", "� ������ ������ � ���� ��� ������� ��� �����������.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("��� � ��� ���������?", "��������� ���� ��������. ��������, � ����� ������.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//����� ���� ����, ��� ��������� ������������ ��� ���������
			sld = &locations[FindLocation(npchar.location)];
			if(!CheckAttribute(sld,"questSeekCap")) sld.questSeekCap = 0;
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//����� ���� ����, ��� ��������� ������������ ��� ���������
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //�������	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ������������
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//�������� �����
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "��� ����� ���� ������� ������ ��������� ���� " + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + ". �� �� ����� ��� ������� � ��� ������ � ����, � ����� ������ � �������. �� ���� ��������� � �������� � �������� ������, ��������� ��� ��������� �� ����� ����� � ������... � �����, � ���� ��������� ����� '�����', ��� � ��� ���.";
					link.l1 = "� ������? ������ �������, ��� �� �������.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "���� � ���, ��� � ���� �������� ����. ���� �������, ����� �� ������, ���������� ��� �� ���, ��� ������ ���. ���� ���� ����� ���� �� �������� �� ����, ��������� �� ��� ��������. � ������� �������� ��������� ������ � ���� �������� - ��������������. � ��� ���������, ����������...";
					link.l1 = "���� ���������?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "�� ������, � ��� ������ �������, � ������� ��� ���� ����� �� ����������� ���� �� ������� ����� � ������� ����� �����. ��� ���������, ��� � ������ �� �������� ���� �����. �� ������� � �����, ��� ��� ������ ���� �������� ���������! � ������� ��� �����, �� ��� � ���� ���������� �� ����.";
					link.l1 = "������? ��������� ���������, ������� ����, ����� ��������� ��� ���� ������.";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// ����� ������� ����, �������� �������-��� ���� � ����
		case "SCQ_Slave":
			dialog.text = "� ����, ����� �� ����� ��� � ��������� �� ��� ����. � ��������� ���� ���������, ��� ������ ������ �� ����...";
			link.l1 = "�������... �����, ��� ����� ��� ������ ��� ������. �������� ��� ��� �������� � �������, �� ������� �� �����.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "��������, ���� ��� �� ����������.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "�������� ����� " + npchar.quest.SeekCap.capName + ". ����� �� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'. � ������� ��� �� ��� ������ " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ��� ���� ������ �������������.";
			link.l1 = "����. �� ��� ��, � ���� ��������"+ GetSexPhrase("��","���") +" ��� ������������� �� ���������� ����. ���� ������� ����� ����, �� ��� ������...";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "�� ����� ������ � � ������� �� ����������. ��� ������ � ������ �����.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "���-�, ��� ��, ��� � ��� ������ ��������!.. �-�, ��� � ������ ����! ���� �� ����������...";
			link.l1 = "�����, ��������. ��� ������� ������ - ����� ���� �����, � ������.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "������, � ���� ����� ��� � ������� ������. ����� � ����������� � ����.";
			link.l1 = "������.";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//����� ������� ���� � ��������
		case "SCQ_RapeWife":
			dialog.text = "��� ������������� ����������� ������� � ��������� �����������. ���� �������� ������� ��� ���� � ���� �� �� ����� ������� � ����. � ����� ��� ����� ����� �������!";
			link.l1 = "��, �� � ����� ��� ��������� � ���������?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - ��� ���� ��������
			forName.lastname = npchar.lastname; //������� ��� � � ���� ����
			dialog.text = "� �������, �� � �������� ����� ���, ��� � ���� ����! ���� �� ���������� ��� ���� � ��������� �� �� ���, �� � ������� ��� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ����� ��� ���� ������ �������������.";
			link.l1 = "��, �� ��� ��, � �����"+ GetSexPhrase("","�") +" �������� ���� �����. ��� ����� ����� �������������� ����, ����� � ���� �������? ��, � ��� ����� ���� ����?";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "���, ��������, �� ����� ������ � �� �������� �� ��� ����. �������...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "�� ����� " + npchar.quest.SeekCap.name + ". ��������-�������� ����� " + npchar.quest.SeekCap.capName + ", ������� �� �� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "������� ��������� �������� ����������������� ��������, ��������. � �������� - �����...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "��-��, �������, ��������! � ���� �� �����, ��� ��� ���� ���������...";
			link.l1 = "�� ��� ���������, �� �����������. � �����, ������ �������� ���� � ������������ �������.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "������� ��� ��������! � ���� ����� ��� � ������� ������. ������ � ������ ��� - �������. � ����� �������� �� ����...";
			link.l1 = "������ ���, ��� �����. �����.";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
		break;
		//������ �������
		case "SCQ_Friend":
			dialog.text = "���� � ���, ��� ��� ������ ��� � �� ��������� ����� �������������. ��� ��� - ��� ��� �������. ������� ��� ����� ������ ��� ��������, �� ��������� � ��������. � � �� ���� ��������� ���� ������� ����� �� ����������� �����������, � �������� ������������ ���� �� �����.";
			link.l1 = "���� � ��� ��� �����, �� � ����� �� ����� ��� ������...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "� ���� ��������� ��� �� ������ " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ����� ��� ���� ������ �������������. ��� ���, ��� � ���� ���� ��������� �� ������ ������.";
			link.l1 = "����� ���� ����������, � �����"+ GetSexPhrase("","�") +" ������� �� ��� ����. ��, ������, ������ ����� �� ��� ����������, ����� ��� �� �������� ������ � �������, ����� �� ����� ������.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "��� ������� ���� ��� ����. ��� ��� ������� ����-������ ������� ��� ����� ����.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "���, �, �������, �������� �����. ����������, ������� ��������� ������, � � ���� ����� ������ �� ������� �����. � ����� � ���� ���� ������.";
			link.l1 = "�������. �� ��� ��, ������ ���������� ���, ��� ��� ���� � ����� � ���� �������.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "��� ����� " + npchar.quest.SeekCap.capName + ". ��������� ��� ��������, �� ����� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "����. �� ��� ��, ��� ������ ������� ������ �������, �� ����������� �������� ���, ��� �� ��� �����.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "������� ���. � ���� ����� ������ �������� � ������� ������. �������, ��� ������ ��� ����� ����� ������ ����� ����, ��� ������ ����� ���������.";
			link.l1 = "�������. ��, ����� ��������, �������� ���������� �������.";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","��"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("","�"));
		break;

		// --- ���������� ������� ������� ---
		case "SCQ_manResult":
			dialog.text = "������������, �������. ���� �����-������ ���������� �� ����� ����?";
			link.l1 = "�������, ��� ��� � ����?..";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "�� ������ ���� �����������, ��� � �������-�� �������. ��� ���?";
					link.l1 = "������. " + npchar.quest.SeekCap.capName + " �����, � ��� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " �� ���.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "�� ��������� ��� ����! ��� ������?!";
					link.l1 = "������. ��� � ���� �� ������� � �������� ���������. ������ �� ��������, ���� " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " � ���� ���� ����...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "������������, �������. �� ����� ����� �������?";
					link.l1 = "���"+ GetSexPhrase("��","��") +" � ���������"+ GetSexPhrase("","�") +", ��� �� ��� ����� �����. ��� ��� ��� ����� ������.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "���, �� ������, ��� � ����� ��� ��������� �������� �� ����� " + npchar.quest.SeekCap.capName + " �� ���, ����������� ���� � �������?!";
					link.l1 = "�� ������ � �� �����"+ GetSexPhrase("","�") +". ��������� ����, ���.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "���� �� ����! �� ������, ��� ������� ��� ��������� � ���������� ��� ����? �� ������� ����� �� ����� " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "�� �����"+ GetSexPhrase("","�") +" � � ����� ����. ������ ������� ���� �� �������� ����������. ��� ��� �� ��� ������, ���...";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "���������... �� ���, ������ � ����� �������� ����� ����� �������, ��������� �������� �� ����� " + npchar.quest.SeekCap.capName + "?";
					link.l1 = "�� �����"+ GetSexPhrase("","�") +", �� ���� �� ���"+ GetSexPhrase("��","��") +". ���...";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "�����������, � � ��� �� ��������! ����, ��� �� � ��������������, ��� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � �������������. ������� �� ����.";
			link.l1 = "��, �� �� �� ���...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "���� ���, �� ��������� ������� ���� � �����! �������� �������� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � �������������. � ������, ��� �� ����� �������� �� ��� �� ����� �����!";
			link.l1 = "��������, � �� ������.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "�������!.. ��� ��, ��� � ��� ������ - " + FindRussianMoneyString(sti(npchar.quest.money)) + " � �������������. � ������� ���, �������.";
			link.l1 = "�� �� ���, �������. ������...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= ������ ��� ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("������������, �������. � ������ ��������� ��� �� ����� ���������.", 
				"�������! �������� �������, ������ ��� �����...", 
				"�������, �� �������� "+ GetSexPhrase("����","���") +" � ������.");
			link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +", ���������, �� �������!", "����� ��������, " + GetAddress_FormToNPC(NPChar) + ", �� � ������ ������ � �� ���� �������...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("��� � ��� ���������, " + GetAddress_FormToNPC(NPChar) + "?", "��������� ���� ��������, " + GetAddress_FormToNPC(NPChar) + ". � ���������� ��� ������.");
			link.l2.go = "SCQ_woman_1";
		break;
		//�������� �����
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "��� ��� ���������� ���������� - ���������� ����� ��������� �� ���� ������. ��� ���, �� ���� � ���� ��� ������ ���� ������� �����, � �� ��� ��� �� ��������!";
					link.l1 = "�� �������, � ��� ���-�� ���������?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+ GetSexPhrase("�������, ��� ������ � �� ��� � ���� ������� ��������, ��������� ����������","�������, � ���� �� ������� � �������� �������, ������ ������ �� ���� ��������") +"...";
					link.l1 = "��� �� � ����, " + GetAddress_FormToNPC(NPChar) + "?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "�������, �������� ���, ������� ���! ��� ��� ����� � �������! �� ������ ������ ���?";
					link.l1 = "���������, ���-�� � �� ����� �������, ��� � ���� �����...";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//������ ����������� ����-��������
		case "SCQ_Hasband":
			dialog.text = "�� ����, �� ����� �������, ��� �� ������ ����� �� ������. ���� ��� �� ��������� ��������, ����� ����, ��� � ��������!";
			link.l1 = "� ���� ������ ����������, ������ ����� ���������...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "���! �� ���������, � ��� � ������. �� ���� �� "+ GetSexPhrase("������� ������","������� ������") +", ������� � � ������ ��������� ��� � ���, ����� �� ����� ����� ����. �� ��� � ������ ��������� ��� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ����� ���� �������������.";
			link.l1 = "������. ���� � ������� ������ ���� � ���� ��� ���-������ ���, �� ������ ��� � ����� ������������. � ������� ���, ��� ����� ������ ������� � ��� � ���� �� �������.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "����� ������ ���� �� ����������. � ���������, � ��������"+ GetSexPhrase("","�") +" ����������...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "��� ����� " + npchar.quest.SeekCap.capName + ". � �������� �� �� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "�������. �� ��� ��, ������ ��������. � ������������ ���������� ��������������� � �����, ����� � �� �����"+ GetSexPhrase("","�") +" ��� �� ������...";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//����� ����������� �������
		case "SCQ_Revenge":
			dialog.text = ""+ GetSexPhrase("��� � � ����, ��������, ��� � ���� ������ ��� �� ������� ����������, ��� �������... ","� ����, ����� �� ������� ���. �������, ��� �� ���� �������, ��� �������. ") +"��� �������� ������� ���� �������, � �����, ����� �� ����.";
			link.l1 = "�-��-��! ��� ��� ��! � ��� �� �� ��� ������, ���� ����������?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "���� �������� ������� ����. �� ����� ���, ��� � ��� ��������, ���� �������� �� ����. � ���������, ��� ��� ����� ���-��� �� ����� ����! � ����� ���� ���������� ������� ������, ����� ���������, ��� ������ ������ �� �� ���� � ����...";
			link.l1 = "��, � �����, � ����?..";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "� ���, ��-������, ����?! �� ���� �������� ���������� �� ������ ��������?";
			link.l1 = "�� ���, ��� ��...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "�� ������ �������������� ����, ���� ��������! ������� ��� ����� �� �����!..";
			link.l1 = "��... "+ GetSexPhrase("�","��, ������� �� ��� ��������. ��,") +" �����, �� ��������? ��, ������� ����-������, � ��� ���������...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "���������?! "+ GetSexPhrase("�� �� �������� �����-��, � �� �����","������, �� ������� �� ������ � ����� ��������! �� ��, ��� �� �������... � � ����� ���� ������ �������...") +"!";
			link.l1 = ""+ GetSexPhrase("�� ��� ��! ","") +"� ������ ���� �����, ��������� ���� ��������� ��������.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "���� ������, "+ GetSexPhrase("�� ������ �� ������, ��� ����� ����� ����������� �������","�� �� �������, � ������ ��������, ������ ��� - ���� �����������! � ���� ���������") +"!..";
			link.l1 = ""+ GetSexPhrase("��� �����, ���-�� �� ��������","��, ������, ��������� ������ �������� � ���") +"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+ GetSexPhrase("��������, ��� ��� �������. ����������� � ��������� � ����� ��������� ������� - ��� �����, ������ � ����! ��� ������, ���������� �������� �� ����","� ��� � �� �����. � ��� ������, ��� ����� �������� ��� ����") +"!\n��� ��� � ����, ����� �� ����� ��� �����. � ����� ������� �� ������ ������, ��� ��� ��� �����������...";
			link.l1 = "��, ���� �� ���� ��� �������... � ������� �� ������ �� ��� ���������?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "���, ��� � ���� ����. � ����� ��� ��� ������������� � " + FindRussianMoneyString(sti(npchar.quest.money)) + "! �������?";
			link.l1 = "�� ��� ��, ��� ��� ���������. ���������� ���, ��� ��� �������, ��������� ������ ������� �� ��������?";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = ""+ GetSexPhrase("�������, � ������� ������� ������������. ","") +"��������, ��� ����...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "����� ������� ����� " + npchar.quest.SeekCap.capName + ", �� �������� ��������� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "��������, ��� ��� ����� ������ � ����������, " + GetAddress_FormToNPC(NPChar) + ". � ������ ����� ���� � ������� ������. �������, ������ ��� ���� ������� ��������...";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("��","��"));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("","�"));
		break;
		//��� ������� ����� � ���� � �������
		case "SCQ_Pirates":
			dialog.text = "������ � ��� �������. ���� � ���, ��� ���, ���������� ������� �������, ��� �������� ��������! ��� ������� ����, ������ �� ������...";
			link.l1 = "������, ������� ������ ������� �������������. ���� �� ��� �������, ������ �� �� �������.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "����� ����, �� ��� ��� ��� ���������� �� ��� ���. �� ��� ������� ���������� �� ���� �������. ��� ���, ����� ������ ���� �����, ��� �������� �������, ��� �� �������� �����. ������ ��� ��������, � ���� �� ������� � ����.";
			link.l1 = "� ������ �� ������?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "���� ������� ��������� ��� ������, ��� �� �����, ��� � ��� ��� � �������. ��� ������ � �����, �� ��� ������ ���������.";
			link.l1 = "� ��� �� �������� ������? ��� ����� ������������ �� �����. ���� ��� ������ ������ ��� ��������.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "�� ���� ���� �����? ��-��, � ����... ������ ���, �������� ���, ������� ����� ����! � ������ �� ������ ��������� ������� � ������ ��� ��������. ��� ���� ����� ���������� ������ ����� ���!";
			link.l1 = "�� ��� ��� � ������, ��� ��� �������. ��� �������� - �������� ���� ������������ ������� ����. �� � �� ���� � ������� ��� �� �������� ����.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "�� �� �� ������ ����������! � ���� ��, ����� �� ������ ����. ��� ��� ������ �� �����, �� �������� ����������� �� ������� �����, ��� ��� ������ �� ������� �� ���� ����� ���������� - ����� �� ���� ����� ������. ���� �� ���������� ���, �� � ����� ��� ���, ��� � ���� ����!";
			link.l1 = "� ��� � ��� ����?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //������ ���� �������� �� �����
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "�������, " + FindRussianMoneyString(sti(npchar.quest.money)) + " � ��� ��� �������������... �� � ���� �������� �� ���� ���� �� ����� �����!";
			link.l1 = "�� ��, ������������� �������... �� �� �����, � �����"+ GetSexPhrase("","�") +" ������ ��� ��� ������.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "�������, �� ��� ������� ���� ��� ����, ����� � �����"+ GetSexPhrase("","�") +" �� ������ �������, ����� ���������� ��������.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "������� ���, �������!!";
			link.l1 = "���� ��� ���������, ����� � ������ �����������, � ���� �� �����. ����������-�� �����, ��� ����� ������ ���� � ���, ��� �� ������ �� ���� �������.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - ��� ���� ��������
			forName.lastname = npchar.lastname; //������� ��� � � ���� ����
			dialog.text = "���� ����� " + GetFullName(forName) + ". �������� ������� ����� " + npchar.quest.SeekCap.capName + ", �� ���������� �� " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " � ������ '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "����. �� ��� ��, ������ �������� � ���������, ��� ��� ������� � ��������. ������������ ���������� � ������, ����� � ���"+ GetSexPhrase("","��") +" ��� ��� ������ �����.";
			link.l1.go = "exit";
			//==> ������ ������������ � �������
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("","�"));
		break;
		// --- ���������� ������� ������� ---
		case "SCQ_womanResult":
			dialog.text = "��, �������, � ��� ���� ��� ������! ���������� ��� �������, ��� �� ������ �� ����� ����?";
			link.l1 = "��, ���������, " + GetAddress_FormToNPC(NPChar) + ", � ����� ���� ���� ����?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "��, �������, � �������� ������ �� ����! � ��� �� �����, ��� �� ����� ���.";
					link.l1 = "��, ��� �����, " + GetAddress_FormToNPC(NPChar) + ". ��� ���, " + npchar.quest.SeekCap.capName + ", ��� � ������. �� ������ �����������, ��� �������...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "��� �������, �������? �� ������� ��, � ��� � ��� �������? ������� " + npchar.quest.SeekCap.capName + " �����?";
					link.l1 = "��, �� �����, " + GetAddress_FormToNPC(NPChar) + ". ����� ������� �� �����, ��� ���� �������� ��� ������. ���������, ��� �� ������ � ���� ����� - ���� ���.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "�� ���-���� ���������� ����� ����! ������ ���, ������� ���, ��� ���?!!";
					link.l1 = "��, ������ �� ��������� � ���� �� �������. ������ ��� ��������, ���� " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " � ���� ��� ���...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "�� ���, ������, ��� ������� ��� ����� ����� ����? ��� ����� " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "�-�, ��, �������... ������ � �� �����"+ GetSexPhrase("","�") +", ������ � ���� ��� � �� �����"+ GetSexPhrase("","�") +" ��� ���������.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "� ���-�� �� ������! �� ������, ��� ������ ��������� �� ��� ���� ����� ��������, �������� �� ����� " + npchar.quest.SeekCap.capName + "?!";
					link.l1 = "�� ��� ��, " + GetAddress_FormToNPC(NPChar) + ", �� � ���� ����. ��� ����� � ������, ��������...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "�������, �������, �� ������, ��� ������� ��������� ����� ���� �� �����?!";
					link.l1 = "� ������ �� �����"+ GetSexPhrase("","�") +", ������� ��� ����. �����, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "���� ���, ��� � ��� ����������! ��, ������, ��� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + ". � ��� ��� �������!";
			link.l1 = "��, �� �� �� ���...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "�������! �� ��� ��, ��� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + " � �������������. ��������.";
			link.l1 = "��������...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			TakeNItems(pchar, "jewelry14", rand(3));
			TakeNItems(pchar, "jewelry13", rand(3));
			TakeNItems(pchar, "jewelry10", rand(3));
			TakeNItems(pchar, "jewelry15", rand(3));
			TakeNItems(pchar, "jewelry16", rand(3));
			TakeNItems(pchar, "jewelry18", rand(3));
			TakeNItems(pchar, "jewelry6", rand(3));
			TakeNItems(pchar, "jewelry7", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "�������, ��� ��!!! �������, �������, ��� �� � ��� ����������! ��� ���� " + FindRussianMoneyString(sti(npchar.quest.money)) + ". � ���� �������� �� ��� ������ ����, ���� ����!";
			link.l1 = "��� �������, ��������...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����������-������������
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= ������������� �������-������������ ===========
		case "CitizCap": //������� �� ����
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "����������� �������. ��� �� �����"+ GetSexPhrase(", �������","�, �������") +"?";
					link.l1 = "���� ����� " + GetFullName(npchar) + ", �� ��� ��?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "��, ��� �����!";
			link.l1 = "����� ���� �� �������. � ������ ������ ���� ���� ���, � �� ���������� ��������� ����� ��������. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". �� ������������?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "��, ����������...";
			link.l1 = "��� ���, �� ����� �� ���� ������, ��������. ��� ��� ������ ����� ������������ �� ��, ��� �� ������ ���������� �������� � �������.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "������������?! ��� �� � ���?";
			link.l1 = "� ���, ��� � �������� ���� ����� �����.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "�� �������, "+ GetSexPhrase("�������","�������") +", ���� ���� �� ����������! ��� �� ���������� ��������� �����������. ��� ����� ����� - �� ���������� ���������!";
			link.l1 = "��, �� ���� ����� ������������. ��� ��� �������� �������� �� ���������!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "��! �� ��� ��, ������, ��� ����!";
			link.l1 = "�����-�����...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //������� �� ������
			dialog.text = "��� ���� ����� � ���� �� ������?";
			link.l1 = "���� �������� ����, �� ����������� �� �� ������� ����������?";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "� ���� ����� ����?";
			link.l1 = "�� ������ ��� ���������...";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "������ ���... ������, ��������-�� �� ������, ���� ��� ���� ����� �����������. �� ��������� �� ���!";
			link.l1 = "�����, �����, �� ��������. ��� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "���������� ���, �� ���������!";
			link.l1 = "�� � �� ���������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= ������������� ���, ���������� ����� ���� ===========
		case "RapeWifeCap":  //������� �� ����
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "����������� �������! �� ���-�� �����"+ GetSexPhrase(", �������","�, �������") +",?";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ������, �� �� �� ������ �� " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " �������, �� ����� " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "���, ��� � ����, ��� � ���� � �����! ������, ��������!.. � ����� �� �����������?";
			link.l1 = "��������, ��� ���� �������. �� ������� �������� �������!";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "�� � ��� � ����? ��� ��� ��������, � ���� � ������. � � �� ������� ������-�� ��������� ����������� � ���� ��������� ������ ������, ��� �� �� ���, ������ ��!..";
			link.l1 = "������� ���� ��������, ��� ��������� �������� ����� ��� ������� �� ��������.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "�� ���, ������ ��� ��� ������ �������"+ GetSexPhrase("","�") +"? ��������� �������� � ����� ���� �������� ��������� �� �����, ��� ��� ���� ��������� �� � ���� �� ��������. ��� ���, � �����!";
			link.l1 = "�� ��������, � ������ �������������"+ GetSexPhrase("��","���") +"... ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "���������� ��� � ��������. ������ �� ����� ��� ���������!";
			link.l1 = "�����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //������� �� ������
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "��� �������������� ������� � ���� �� ������! ��� �� �����"+ GetSexPhrase("","�") +" �������� �� ����, "+ GetSexPhrase("�������","�������") +"?";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ������, �� �� �� ������ �� " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " �������, �� ����� " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "���, ��� � ����, ��� � ���� � �����! ������, ��������!.. � ����� �� �����������?";
			link.l1 = "��������, ��� ���� �������. �� ������� �������� �������!";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "�� � ��� � ����? ��� ��� ��������, � ���� � ������. � � �� ������� ������-�� ��������� ����������� � ���� ��������� ������ ������, ��� �� �� ���, ������ ��!..";
			link.l1 = "������� ���� ��������, ��� ��������� �������� ����� ��� ������� �� ��������.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "�� ���, ������ ��� ��� ������ �������"+ GetSexPhrase("","�") +"? ��������� �������� � ����� ���� �������� ��������� �� �����, ��� ��� ���� ��������� �� � ���� �� ��������. ��� ���, � �����!";
			link.l1 = "�� ��������, � ������ �������������"+ GetSexPhrase("��","���") +"... � �����, �����, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //�������
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "��� ���� �����, �������?!!";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" �� ��������, ��� �� ����� � ����. ������� " + XI_ConvertString("Colony"+npchar.quest.cribCity) + "! �� ����� " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "������!! ���� �� ������ �� ��� ����� ����!";
			link.l1 = "��, �����!! ���� ��� � ���� � �������! � ���� ������ ������...";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // ������ �����
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //���� ������ ��� ���
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//����� ��� ���
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "girl_"+(rand(7)+1); //������ ��� ���
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //�������� ����� ��� ���
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //��� � ������� ��� ���
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= ���������� ���� ===========
		case "manRapeWife_Board":
			dialog.text = "��� ��?";
			link.l1 = "������������. � ����"+ GetSexPhrase("��","��") +" �� ���� �� ��������� ������ ����. ������, ����� �� ��������, ��� ����� ������� ��� � ����.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "������� ��� �� ���?! ��� ������?!";
			link.l1 = "��������� ������, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "����� ������� �����������!!! � ������, ������� ������� ����� ������!";
			link.l1 = "������, " + GetAddress_FormToNPC(NPChar) + ", ���������� � ����������� �����, � ����.";
			link.l1.go = "exit";
			//������ ���� �� �����
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= ������������� ������-�������� ��� ===========
		case "FriendCap": //������� �� ����
			dialog.text = "������������! ��� �������������� ��������, �������, ��� �������, �� ����...";
			link.l1 = TimeGreeting() + " � � ���"+ GetSexPhrase("��","��") +" ��� �� ����.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "������ ��� �����������.";
			link.l1 = "���� � ���, ��� ��� ���� ��� ������, � ������� �� ����������� ���� �� ������� �����. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ", �������� ���?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "��, ��� ��! � ��� �� �����?";
			link.l1 = "� " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ". � ���������"+ GetSexPhrase("","�") +" ��� ����������� �� ����, �� �� ���������. ������ ��� ������� � ����.";
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = "�������, � ��� ������. ������� ��� �������!.. �� ������, �� ������ ���� � ������ ��, ��� �� �����!";
			link.l1 = "��� � ����. �� � ������� ����"+ GetSexPhrase("��","��") +", ��� ��� ���� �� � ��� �����������. ����� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //������� ������������� ������ �� ����� � ����
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			//������� ������ � ���� �����
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "��� ���������, ��� �������? ��������, � ������� ���������...";
			link.l1 = "��� � �������, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //������� �� ������
			dialog.text = TimeGreeting() + ". ��� ��� ����� �� ����? � ����� ���� �������� �������, �...";
			link.l1 = "� ����, ��������. �� ��������� ���, �������, ��� ������ ��� ��������. � � ���� �� ����.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "�� ������ ����?";
			link.l1 = "���� ���� ���� ������ " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". ������ ������?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "�-�-�, ������� ���-����! ����� ������... �� ���� �������� �� ������ �����, �, ������ ��, ������� ����� �������, ��� �� �����.";
			link.l1 = "��� � ����. �� ���� ���� ������ �� ��������. ���� ������� �������� ���� ���������, ��� � � ������"+ GetSexPhrase("","�") +". ���� ������, ������, ����� � �������� � " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ".";
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "��� ��� ��!.. �� - "+ GetSexPhrase("����������� �������","����������� �������") +". ������� ���!";
			link.l1 = "�� �� ���. ������ � ���� ������, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //������� �� ������ ����� - � ��������
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			//������� ������ � ���� �����
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= ������������� ���-�������� ===========
		case "HasbandCap": //������� �� ����
			dialog.text = "������������. �� ���-�� ������?";
			link.l1 = "��� ����� " + GetFullName(npchar) + ", �� ��� ��?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "��, ��� �.";
			link.l1 = "���, �������, ������ �����, �� ���� ���� ������� ���� ��������, ��� ����� �� ��� ���������.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "��! ��, ��� �������... ������-�� � ��������� ���������� � �������, ��� ��� �� �� ��� ������. �������� ����������� ������� ���� �� �������, � �� ���� �������� ��������� ������ ������ ������, ��� ��� ���� ���������.";
			link.l1 = "��� �������, �� �� ����� ���� �� �������� ��, ��� � ���� ��� � �������.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "��, �� �����. ���������� �� ������!.. ������� ��� �������� �� ������� � ����� �������� �����!";
			link.l1 = "�� �� ���, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //������� ������������� ������ �� ����� � ����
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //������� ���������� ������ ����
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			//������� ������ � ���� �����
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //������� �� ������
			dialog.text = "������������. ���� ������ �� ����� ������ ��� � ���� �� �������?";
			link.l1 = "��� ����� " + GetFullName(npchar) + ", �� ��� ��?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "��, ��� �.";
			link.l1 = "���, �������, ������ �����, �� ���� ���� ������� ���� ��������, ��� ����� �� ��� ���������.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "��, ����! � �, ������ ������, ��������� - �����, ��� ��� ���������� ������� �� ������� - ���������� ���� ������ �� ���� ��������. ��, ������, ��� ������...\n�� ������, � ��������� ���������� � �������, ��� ��� �� �� ��� ������. �������� ����������� ������� ���� �� �������, � �� ���� �������� ��������� ������ ������ ������, ��� ��� ���� ���������.";			
			link.l1 = "��� �������, �� �� ����� ���� �� �������� ��, ��� � ���� ��� � �������.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "��, �� �����. � ��� ����������� ������ � ������ �� ����� �� ���������... ������� ��� �������� �� ������� � ����� �������� �����!";
			link.l1 = "�� �� ���, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //������� �� ������ ����� - � ��������
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			//������� ������ � ���� �����
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "��� ��� ������� ��� �������������...";
			link.l1 = "�� �� �����, ��� � �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= ������������� �������-�������� ===========
		case "RevengeCap": //������� �� ����
			dialog.text = "��� ������ ��� � ���� ���������, �������. ��� ���-�� ����� �� ����?";
			link.l1 = ""+ GetSexPhrase("������, �������... ���, ���� �� ����, ��� ��� �������!","��, �����.") +"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+ GetSexPhrase("��������, ��� ����.","���������, � ��� ��?") +"";
			link.l1 = ""+ GetSexPhrase("��, ��� � ��������... � �����, �","�") +" ���� � ��� ������. �� ������� � ����� �� ����� " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "���, �� ��, ������. ����, ��� �������, ��������� �������� � ���. �������� ����, ���� ��� �������...";
			link.l1 = "��... ��� ���, ��� �������� ���� ������ ���� ����� ���"+ GetSexPhrase(", �������. ��� ���-��..","") +".";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "��, ��� ��� ������ ������...";
			link.l1 = ""+ GetSexPhrase("���� �� �� ���� ��� �������... �������, �� �� ����","������ �������� � ���� ���. �� ����") +" ������ ��������� �������. � � �������"+ GetSexPhrase("","�") +" �� ��������.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "��-��!.. �� �� ������, �������?";
			link.l1 = ""+ GetSexPhrase("���, ���� ���...","���� �� ������!") +"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+ GetSexPhrase("�� ����� �� ��� ����, �����?! �� � ���������-�� ��������� �� ������. ���, ����������� �� ���������� � �������� �����","���� ������! ���� �������� ����� ������ ������! ��� �� ��� �� ���� ����� ��������?") +"!";
			link.l1 = ""+ GetSexPhrase("��� ���?!","�� ����������� �� � ����� ��������� �����, ��� ��� ������ ���������� ����, ��� ��� ������ ���������.") +"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+ GetSexPhrase("�� � ��� �� �����, ����� � ���� �������? ���� ��� ������, ����-�� �� ���������...","������� ������������, ��?!") +"";
			link.l1 = ""+ GetSexPhrase("","������, �������, � ��� ����. ") +"�������� ���� ������!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //���� ������ ��� ������ � ���������� �� ��������
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "� ����� � ���� ��� ��� ��������. "+ GetSexPhrase("����� ���, ��������","��������, ������") +"...";
			link.l1 = ""+ GetSexPhrase("��������","������") +"?! �� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //������� �� ������
			dialog.text = "��� ������ ��� � ���� �� ������, �������. ����� ����������?";
			link.l1 = "� ���� � ��� ������. �� ������� � ����� �� ����� " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "���, �� ��, ������. ����, ��� �������, ��������� �������� � ���. �������� ����, ���� ��� �������...";
			link.l1 = "���, ��� ��� ��� �������� ���� ������ ���� ����� ���"+ GetSexPhrase(", �������. ��� ���-��..","") +".";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "��-��... �������, �� ������� ����. ���� � ��� ������ ��� �� ��� ���, �� ��������.";
			link.l1 = "�� ��� ��, ��������. �� ������ � ���� ��, ��� � ��� ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "�����������, �������, ��� �� �����?!";
			link.l1 = "����� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //���� ������ ��� ������ � ���������� �� ��������
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "� ������ �� ���� �������� �� ��� ����, �������. ��� ������.";
			link.l1 = "��, ��� ������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //�������
			dialog.text = "��� ����������, ���� ������?! ����� �� ������ �� ��� �������?!";
			link.l1 = "�� ��������� "+ GetSexPhrase("����� ����,","�������") +" �� ����� " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". ��� ����� ��� �������?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "������!!! �������� �� ����..."+ GetSexPhrase(""," ���� ������� ����� ������ ������!") +"";
			link.l1 = ""+ GetSexPhrase("� ��������.","������ ���� ����� �������� �� ���� ������ �������!") +"";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "�� ��� ��, � ��� ������ ������� �� �������. �� �������� �������, �� �������� ��� ���. "+ GetSexPhrase("�� ���������� ","� �������� ") +"���� ����� � ���� ���-���� ��������� �� ��� ����!";
			link.l1 = "����������, ��� � ��� ���� �������?..";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> ���� ������ ������ � ������������� ����
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // ������ �����
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= ���������� ���� �� ��������� ��������� =========
		case "PiratesCap_inDeck": //������� �� ������
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "��� ������ ��� � ���� �� ������. � ���-�� ���� ������ ���?";
			link.l1 = "��������, ��. � ��� ��������, �� ����� " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "���� ������� - ��� �������, � � �������� �������� �� ���� ������� �����.";
			link.l1 = "� ���� ��� ��������.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "�������, �� ��� ����������. ���� ��� ���, �� � ����� ��� �������� ��� �������.";
			link.l1 = "������, �������, ��� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCapCap_exit":
			dialog.text = "�� ��� �������� � ���� ��������. ������ �� ����������.";
			link.l1 = "�������...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //������� �� ����
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "�����������, �������. � ���-�� ���� ��� ������?";
			link.l1 = "��������, ��. � ��� ��������, �� ����� " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "���� ������� - ��� �������, � � �������� �������� �� ���� ������� �����.";
			link.l1 = "� ���� ��� ��������.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "�������, �� ��� ����������.";
			link.l1 = "����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCap_Board": //�������
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "������! ������ �����?!!";
			link.l1 = "��� ����� ���� �������, �� ����� " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "��! �� �� ���, ������ ����� ��� ����...";
			link.l1 = "��� ��� ����� ������.";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // ������ �����
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //���� ������ ��� ���
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//����� ��� ���
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+1); //������ ��� ���
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //�������� ����� ��� ���
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //��� � ������� ��� ���
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= ������� ��� ===========
		case "womanPirates_Board":
			dialog.text = "��� ��?";
			link.l1 = "� ������� " + GetFullName(pchar) + ". �� �� ����������, � ����"+ GetSexPhrase("��","��") +" �� ���� ��� ����, ����� ������� � ����.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "���� ������, ������� ��� �� ���?!";
			link.l1 = "������ ���, ��� �� ���... �� ��� ��, ���� �������, ������ ������ ������.";
			link.l1.go = "exit";
			//������ ���� �� �����
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //��������� ���� ����� �� '��������'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//���������� ��������
		case "OffMushketer":
			dialog.text = "����������� "+ GetSexPhrase("�����","���������� ������") +" � ���� ����. ��� �� ������ �����?";
			link.l1 = "�������������. ���� ����� ������� " + GetFullName(pchar) + ".";
			link.l1.go = "OffM_1";
		break;
		case "OffM_1":
			dialog.text = "��� ����������, �������. ��� � ���� ��� ������?";
			link.l1 = "�� ���, ����� ���������... � �� �� ���� ������� �������. ��� �� ������ ��������?";
			link.l1.go = "OffM_2";
		break;
		case "OffM_2":
			dialog.text = "��� ���, ������.";
			link.l1 = "�������. � ��� ���� � �����?";
			link.l1.go = "OffM_4";
		break;
		case "OffM_4":
			dialog.text = "����������. � ��� ������ �������� � �����!";
			link.l1 = "��, ����� ���� ��� �����. �� ������� ����� ������� �������� �� ��� � �������?";
			link.l1.go = "OffM_5";
		break;
		case "OffM_5":
			dialog.text = "������� �� �����������, �� �������� ����������.";
			link.l1 = "�������, � ������? ���� �� ������, �������...";
			link.l1.go = "OffM_6";
		break;
		case "OffM_6":
			dialog.text = "��� ���� � ����������� ������. �� ���� ����� � ���� ������!";
			link.l1 = "������� ��� ���. � ��� �� �� ������� � �����?";
			link.l1.go = "OffM_7";
		break;
		case "OffM_7":
			dialog.text = "���������, ��� � ���� ����� �������� ���������� ������, ����� ����. ��� ������, ������������������� �������� �����, ����������� �������� �������. � �����, ��������� ������������ ���������, ������ �������.\n"+
				"� ��� � � ����� ������ ����������, ��� ������� ������ �� �������.";
			link.l1 = "� ��� ���� ����-������ ������?";
			link.l1.go = "OffM_8";
		break;
		case "OffM_8":
			dialog.text = "��-�, ���� ���������� ������... ����� � ���� ���� �� ������� �����, �� ��� ������ ������. � ����� ������� �� ��� �����, � �������� ���, ������ �� ������ ���� �����������. �� ���� �� ������� ����������� �� ���� � ��������!..";
			link.l1 = "������ ���, ��� ��������� ���������. �� ���� �� �������� ����.";
			link.l1.go = "OffM_9";
		break;
		case "OffM_9":
			dialog.text = "���, �� ��� ����� �������! � ��� ��� �� �����!..";
			link.l1 = "��, ����� ������ ��������, ��������...";
			link.l1.go = "OffM_10";
		break;
		case "OffM_10":
			dialog.text = "��������?.. ��, ����������, ���� �� ������� ��� ������������ ������, �� � ����� � ��� � �������. ������.";
			link.l1 = "�� ��� ��, � ��� �����"+ GetSexPhrase("","�") +". � ��� �������� ��� �������, ����� ��� ����?";
			link.l1.go = "OffM_11";
		break;
		case "OffM_11":
			dialog.text = "���� ��� ��� ���� ��� �����, � ��� ��� � �����. ��� ���� �� ������ - � �� �����, ����� ��������� � ������ �� ������. ������� � �����-�� ������ ������, �� ��� ��� ����� - ��� �� ��������.";
			link.l1 = "�-��, ��������... �� ��� ��, ��� ���������, ����� ������. ���� ��� ��� ������ ���������, �� ����������� ������� ��� ����.";
			link.l1.go = "OffM_12";
		break;
		case "OffM_12":
			dialog.text = "������� ���. ���� ����� � �����������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2 = true;
			AddQuestRecord("SeekDoubleMushket", "1");
			NextDiag.TempNode = "OffM_result";	
		break;

		case "OffM_result":
			dialog.text = "�� ����� ��� ������?";
			if (CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "��, �������, ���"+ GetSexPhrase("��","��") +". ��� ��, ������������ ������, ������� ������ ���.";
				link.l1.go = "OffM_result_1";
			}
			else
			{
				link.l1 = "��� ���. �� � ��������� ����.";
				link.l1.go = "exit";
			}
		break;
		case "OffM_result_1":
			dialog.text = "�������! ��, ����� ������ ����������!";
			link.l1 = "������. ������ � ��� ���������� ������ �������� ����� ���� ��������.";
			link.l1.go = "OffM_result_2";
			TakeItemFromCharacter(pchar, "mushket2x2");
			Npchar.quest.OfficerPrice = sti(pchar.rank)*300;
		break;
		case "OffM_result_2":
			dialog.text = "��� ����� ��������. � �����. ������ ������� ������� ������ ����� ��������. �� ���� ������ ������ � ���� �������� " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + " � �����.";
			link.l1 = "� ��� �� �������, ��� ��� ��������?";
			link.l1.go = "OffM_trade";
			link.l1 = "��, ������, � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_trade":
			dialog.text = "���, � ���� ������� ������.";
			link.l1 = "��, ������, � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_Ok":
			Npchar.quest.OfficerPrice.add = sti(pchar.rank)*1000;
			dialog.text = "������. �� ��� ��� �� ���. � ������ ��������������� �������, ��� �������. ������������ ��� ������, ��� � ���� �������� �����. �����, ��� " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " ���� �������.";
			link.l1 = "����?!!";
			link.l1.go = "OffM_Ok_1";
		break;
		case "OffM_Ok_1":
			dialog.text = "����! � ����� �����... � �����, �������.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "��� � ���� ����� �����.";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "��� ����� ������ ��� ����.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "������, � ������"+ GetSexPhrase("��","��") +".";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "OffM_noMoney":
			dialog.text = "������, ���������, ��� ������������. �����.";
			link.l1 = "�������...";
			link.l1.go = "exit";
		break;
		case "OffM_Ok_3":
			dialog.text = "���, ������ ������ ������ ����! � ����� ��� ������� ����� � �������.";
			link.l1 = "�������. ����� ���������� � �������.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			AddQuestRecord("SeekDoubleMushket", "3");
			CloseQuestHeader("SeekDoubleMushket");
			AddMoneyToCharacter(pchar, -sti(Npchar.quest.OfficerPrice.add));
			npchar.perks.list.Gunman = "1";
			AddItems(npchar, "bullet", 50);
			AddItems(npchar, "GunPowder", 50);
			npchar.IsMushketer = true;
			Npchar.CanTakeMushket = true;
			npchar.model = "MusketeerEnglish_2";
			//Korsar Maxim - �������� ���� ������� ��� �����. -->
        	npchar.HeroModel = "MusketeerEnglish_2,MusketeerEnglish_2_1,MusketeerEnglish_2_2,MusketeerEnglish_2_3,MusketeerEnglish_2_4,MusketeerEnglish_2_5,MusketeerEnglish_2,MusketeerEnglish_2,MusketeerEnglish_2";
	        //Korsar Maxim - �������� ���� ������� ��� �����. <-- 			
			npchar.model.animation = "mushketer";
			GiveItem2Character(npchar, "mushket2x2");
			npchar.IsMushketer.LastGunID = -1;
			npchar.equip.gun = "mushket2x2";
			npchar.IsMushketer.MushketID = "mushket2x2";
			npchar.MusketerDistance = 5;
			npchar.greeting = "Gr_questOfficer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		case "OffM_TWO":
			dialog.text = "�� ���, ��� ��� � ��� ���� � ���������? �������, ��� � ���� " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " ��������������� ������� � " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + " ������������ ���������.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "���, �� ������ ����...";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "��� ����� ������ ��� ����.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "������, � ������"+ GetSexPhrase("��","��") +".";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
	}
}


void GetPerlShore()
{	
	switch (rand(4))
	{
		case 0:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Beliz";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore_ship2";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = ". ��� ����� � �������";
			break;
		case 1:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Cumana";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore18";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = ". ��� ����� � �������";
			break;
		case 2:
			pchar.questTemp.Sharp.PearlAreal = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Island = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore26";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_3";
			break;
		case 3:
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
		case 4:
			pchar.questTemp.Sharp.PearlAreal = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Island = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore17";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
	}
	pchar.questTemp.Sharp.PearlAreal.terms = rand(5) + 5; //�����
	pchar.questTemp.Sharp.PearlAreal.qtyShips = rand(6) + 6; //���-�� ������ ������
	pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //��� ��������� ��������
	pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//������� �����
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true));
	switch (npchar.quest.SeekCap)
	{
		case "manSlave": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
		break;
		case "manRapeWife": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
		break;
		case "manFriend": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
		break;
		case "womanHasband": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
		break;
		case "womanRevenge": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
		break;
		case "womanPirates": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//� ������� ������ ����
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//���������� ������ � ��������� �������� � ����
	npchar.quest.SeekCap.capId = sld.id //Id �������� ����
	npchar.quest.SeekCap.capName = GetFullName(sld); //��� �������� ����
	npchar.quest.SeekCap.shipName = sld.Ship.name; //��� ����������� �������
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //�������� ����������� �������
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //��������������
	npchar.quest.gem = GenQuestCitizen_GenerateGem(); //�������
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.quest.SeekCap = npchar.quest.SeekCap; //������� ���� ���� ������
	sld.quest.nation = iNation; //�������� ������� ����� ����
	sld.city = SelectAnyColony(npchar.city); //��������� �������, ������ ���-��� ������
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //��������� �������, ���� �� ������
	Log_TestInfo("������������� ��� " + sld.id + " ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //�����, ��� ��������� ������������
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	switch (npchar.quest.SeekCap)
	{
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//���������� �� ������ ����
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//���������� �� ������ ������������
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestCitizen_GenerateGem() // �����
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry4"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry17"; 
		break;
	}
	return itemID;
}