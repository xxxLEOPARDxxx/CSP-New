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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			if (Pchar.Location == Pchar.location.from_sea)
			{
				dialog.text = "����"+ GetSexPhrase("��","��") +" �������. � � �� �����, �����������. �� ����� ������ ���? ����-�� ���������.";
				link.l1 = "������ �� ���� ���. �� � ������� ��� ������, � �� �� ���� �����, � � �������� ���������������� ������ �������. ��� ���?";
				link.l1.go = "pirateStartQuest_Smuggler3_1";
			}
			else
			{
				dialog.text = "����"+ GetSexPhrase("��","��") +" �������. ������ � ������ ������� �� ����, "+ GetSexPhrase("��������","�������") +". ���� �� ������"+ GetSexPhrase("��","���") +" ����� �������?";
				link.l1 = "�����, ������������"+ GetSexPhrase("��","���") +" �� � ��� �����... ������, � �����!";
				link.l1.go = "exit";

			}
		break;
		case "pirateStartQuest_Smuggler3_1":
			dialog.text = "���, ������ �������. ��, � ������ ����������, ������� ���� �������� " + pchar.questTemp.pirateStartQuest.Name + ", ���� �� ��� ����� ���"+ GetSexPhrase("��","��") +".";
			link.l1 = "��, � �� ������������"+ GetSexPhrase("","�") +", ��� ��� ������� ������ � ���� ����. ��� �� �������� ��� �����, ��� � ���� ������ �� � ������ �����.";
			link.l1.go = "pirateStartQuest_Smuggler3_2";
		break;
		case "pirateStartQuest_Smuggler3_2":
			dialog.text = "���� ��� � ��� ������, ������. ����������, ������ ���. ����������?";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "����������. ��� �������� �����, ��������� ����� �������� ��������.";
				link.l1.go = "pirateStartQuest_Smuggler3_3";
			}
			link.l2 = "�� �������� ��������, ������� ���, ��� ���� ����� �� ����� '�������'. ���� ������, ��� ����������.";
			link.l2.go = "pirateStartQuest_Smuggler3_5";
			GiveItem2Character(npchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_pirateStartQuest");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			AddQuestRecord("pSQ", "5");
			AddQuestUserData("pSQ", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;
		case "pirateStartQuest_Smuggler3_3":
			dialog.text = "���� ���������. ����� ������, � ����������, ���� ��� ������� �� ������.";
			link.l1 = "�� ��������, ��������, ������� ���, ��� ���� ����� �� ����� '�������'. ������ �������� ������ �������� - ������, ��� ����������.";
			link.l1.go = "pirateStartQuest_Smuggler3_5";
			AddMoneyToCharacter(pchar, -15000);
			AddMoneyToCharacter(npchar, 15000);
			AddCharacterGoods(pchar, GOOD_SLAVES, 100);
			AddQuestUserData("pSQ", "sText", "� ����� ����� ������������ ����� �� �����������, �� �������� �� � �������"+ GetSexPhrase("","�") +" �� ��� 15 000 ��������.");
		break;
		case "pirateStartQuest_Smuggler3_5":
			dialog.text = "��� ����! ������ ��� �������. �������� �������� �� ���� ������ ������ � ������� � ����� ������� ��������!";
			link.l1 = "������, �� ����� �� �� ���������. ��, �������, ���� �� ������, ������� ��������� ������ ������� - �� �������� ��� �����������, ������� ���� ���� ����� � ����������, ����� ������� ���� ������ ������.";
			link.l1.go = "pirateStartQuest_Smuggler3_6";
		break;
		case "pirateStartQuest_Smuggler3_6":
			dialog.text = "��� � ������, ��� ��� ��� �����. ����� ����� ��������, � ������ ������� ���� � �� ���������, ����. � " + pchar.questTemp.pirateStartQuest.Name + " ����� ����������� ����������� �����������.";
			link.l1 = "��, ��������, ������, ���������� ���� �������...";
			link.l1.go = "pirateStartQuest_Smuggler3_7";
		break;
		case "pirateStartQuest_Smuggler3_7":
			chrDisableReloadToLocation = true;
			RemoveGeometryFromLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");

			for(i=1; i<=3; i++)
			{
				sld = CharacterFromID("psq2_" +i);
				LAi_SetImmortal(sld, false);
			}

			LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("pirateStartQuest_Smuggler_group", "OpenTheDoors");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");

			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1.location = pchar.location;
			pchar.quest.pirateStartQuest_Lether_fc.function = "pirateStartQuest_Lether_fc";
		break;
	}
}





