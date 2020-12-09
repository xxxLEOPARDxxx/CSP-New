
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
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = "�� ��� ���"+ GetSexPhrase("��","��") +"?!";
			link.l1 = "����, ���� �� ��������. ���� ������� ���� ��������, ��� � �������� �����. " + pchar.questTemp.jailCanMove.Deliver.name + ", ������ ������?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		case "Step_1":
			dialog.text = "��� ��������, ��� �� �� �� �������������� �����?";
			link.l1 = "������� ������ ��������. ��� ���.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
		dialog.text = "���...(������). ��� ����! ���� �� ��� ���� ��� �������� ���������... ��, ����� ���� ���������... ������, ����"+ GetSexPhrase("�","���") +", ��, ������, "+ GetSexPhrase("������ ��������","������ ������") +". �� � ������, �� �������, ������. �� ������ �������������? � �� � �������� ������, � ��� ���������.";
					link.l1 = "������������� - ��� � ������ ����. ��� �� �����������?";
					link.l1.go = "Step_3";
		
			break;
			
			case "Step_3":
			dialog.text = "���� ���������� �����������. ��� ��� ������ �� � ���� - �� ������ ���, � ���� ����� ���������. ������ �� ��������� - ���"+ GetSexPhrase("","�") +" ���������, ��� ����� �����. ���� ��������, ������.";
			link.l1 = "������� �� ������?";
			link.l1.go = "Step_4";
		break;
		
		case "Step_4":
			dialog.text = "50 000 �������.";
			if(makeint(Pchar.money) >= 50000)
			{
			link.l1 = "��, ������. �� ���� ���� ���� �����... ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "Step_5";
			}
			link.l2 = "���. � �� �������"+ GetSexPhrase("","�") +" ������� ���������� �� ���. �������� ����� � ������ � �� ���������.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://������� �������
					dialog.text = "���-���, �������, "+ GetSexPhrase("�������, �������","��������, ������") +". ��-��, ���� ���� ���� �������!";
				link.l1 = "�� ������. � ���� �������� �������, ��� ������ � ���� ������.";
				link.l1.go = "Step_fight";
				break;
				case 1://��������
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "������, ������. ��� ����� ���������� ��������, ��� � ��������� " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " � ������� "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" ����� ��������� ��� "+ pchar.questTemp.jailCanMove.Deliver.add1 +" ���������� ������� - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' � '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', � �������, ������� "+ pchar.questTemp.jailCanMove.Deliver.add +". ������ ���������� �� �����������.";
					link.l1 = "�������! �������, � ������� �������"+ GetSexPhrase("��","���") +" � ���� ����������.";
					link.l1.go = "Step_lay";
				break;
				case 2://������� �� �������� �������
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "������, ������. ��� ����� ���������� ��������, ��� � ��������� " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " � ������� "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" ����� ��������� ��� "+ pchar.questTemp.jailCanMove.Deliver.add1 +" ���������� ������� - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' � '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', � �������, ������� "+ pchar.questTemp.jailCanMove.Deliver.add +". ������ ���������� �� �����������.";
					link.l1 = "�������! �������, � ������� �������"+ GetSexPhrase("��","���") +" � ���� ����������.";
					link.l1.go = "Step_trader";
				break;
				case 3://������� �� ���������� �������
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "������, ������. ��� ����� ���������� ��������, ��� � ��������� " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " � ������� "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" ����� ��������� ���������� ������� "+ pchar.questTemp.jailCanMove.Deliver.add2 +" ��� ��������� '"+ pchar.questTemp.jailCanMove.Deliver.ShipName +"'. �� ��������� ����� ���� ��������������. ������ ���������� ��� �����������.";
					link.l1 = "�������! �������, � ������� �������"+ GetSexPhrase("��","���") +" � ���� ����������.";
					link.l1.go = "Step_cureer";
				break;
			}
			break;
			
		case "Step_fight":
			dialog.text = "���� �� �� �� ��� ����� ��������, �� ��� �� ��� � �������, � �� ����� � ��������. ��� ��� ��� ������� ����� ��� � ������, ��-��-��! � ������ ������� �� �����, ����� " + GetSexPhrase("�����","�����") + " ������ �� �������.";
			link.l1 = "��, ��� �� ������ ��������...";
			link.l1.go = "quest_fight";
			link.l2 = "�����, ��������� ������... ���� �� �� ���� �������.";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "��� � "+ GetSexPhrase("�������","������") +". � ������ �� ���� ��� ����� ����... ��-��, ����� ���������. � �����, ����� ������ ��-������...";
			link.l1 = "������ �� ��������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;
		
		case "Step_lay":
			dialog.text = "�������, �������... ���, � ������ �����, ��������������. � ������ ��������, �������� �� ���������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//���������� � �������
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//������ - � ��� �����
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//������
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_trader":
			dialog.text = "�������, �������... ���, � ������ �����, ��������������. � ������ ��������, �������� �� ���������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//���������� � �������
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//�������� ��������
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//������
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_cureer":
			dialog.text = "�������, �������... ���, � ������ �����, ��������������. � ������ ��������, �������� �� ���������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//���������� � �������
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//�������� ��������
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//������
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_no":
			dialog.text = "��, ��� ������. ����� ����������, �� � ��� ��� � ����� ������ ���������.";
			link.l1 = "�����, ������.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "16");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("��","���"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = "�� ���� ���? ������� �� - ���� ��-������.";
			link.l1 = "�����, ��� ���...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "�� ���, " + GetSexPhrase("�������, ���","������, ����") + " �� ������ ������?!";
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//������� ������ ��� �������� � �������
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	} 
	pchar.questTemp.jailCanMove.Deliver.Island.Town = FindTownOnIsland(pchar.questTemp.jailCanMove.Deliver.Island);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Caiman" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Terks" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Dominica")
	{
	pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
	pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//������� ����� ��� ��������
{
switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "������� ������";
			break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "�������� ������";
			break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SANDAL;
			pchar.questTemp.jailCanMove.Deliver.add = "�������";
			break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "����";
			break;
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SILK;
			pchar.questTemp.jailCanMove.Deliver.add = "�����";
			break;
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "���������";
			break;
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "������";
			break;
	}
}

void GetBandersTradeNation()//������� ����� ������� � �������
{
switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "���������";
			pchar.questTemp.jailCanMove.Deliver.add2 = "��������� ����-������� �������� ��������";
			break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "�����������";
			pchar.questTemp.jailCanMove.Deliver.add2 = "����������� ����-������� �������� ��������";
			break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "�����������";
			pchar.questTemp.jailCanMove.Deliver.add2 = "����������� ����-������� �������� ��������";
			break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "����������";
			pchar.questTemp.jailCanMove.Deliver.add2 = "���������� ����-������� �������� ��������";
			break;
	}
}



