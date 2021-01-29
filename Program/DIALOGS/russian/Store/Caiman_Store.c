// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bGoldMine, bSilverMine, bIronMine;
	bGoldMine = false;
	bSilverMine = false;
	bIronMine = false;
	
	if(CheckAttribute(PChar, "ColonyBuilding.GoldMine.BuildingTime"))
	{
		bGoldMine = PChar.ColonyBuilding.GoldMine == true && PChar.ColonyBuilding.GoldMine.BuildingTime == false;
	}	
	if(CheckAttribute(PChar, "ColonyBuilding.SilverMine.BuildingTime"))
	{
		bSilverMine = PChar.ColonyBuilding.SilverMine == true && PChar.ColonyBuilding.SilverMine.BuildingTime == false;
	}	
	if(CheckAttribute(PChar, "ColonyBuilding.IronMine.BuildingTime"))
	{
		bIronMine = PChar.ColonyBuilding.IronMine == true && PChar.ColonyBuilding.IronMine.BuildingTime == false;
	}	
	
	int iCost = 0;
	string sString = "";
	int iQty = 0;
	
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("���������, ���� �� ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��������, ��� �������, ����� ���� �������� ���-��. �� �������� ����!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, ����� ���-��...",
                      "�� ��, ������������� � ������ ���...", "��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			link.l2 = "�������� �� ���������� � ��������� ������� ������������ ��������.";
			link.l2.go = "Colony_1";
			
			link.l3 = "� ���� ���������� � ����� � ����-����� ���������� ��� � ������� �� �������� � ���������.";
			link.l3.go = "AutoSell_1";
		break;
		
	
		case "Colony_1":
			dialog.Text = "��, �� �� ����. ��� ������ ��� ����������?";
			Link.l1 = "��������� ��������� ��������� ��������.";
			Link.l1.go = "Cost";
			Link.l2 = "�������� ��������� �� ����.";
			Link.l2.go = "AutoPurchase";
			
			if(PChar.ColonyBuilding.Colony.AutoPurchase == false)
			{
				Link.l3 = "�������� �� ��������������� ������������ ��������� �������.";
				Link.l3.go = "Colony_AutoPurchase";
			}
			else
			{
				Link.l3 = "���������� ������������� ��������� �������.";
				Link.l3.go = "Colony_OffAutoPurchase";
			}
			
			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.ColonyBuilding.Mines.AutoPurchase == false)
				{
					Link.l4 = "�������� �� ��������������� ������������ ��������� ��������.";
					Link.l4.go = "Mines_AutoPurchase";
				}
				else
				{
					Link.l4 = "���������� ������������� ��������� ��������.";
					Link.l4.go = "Mines_OffAutoPurchase";
				}
			}
			
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.ColonyBuilding.Plantation.AutoPurchase == false)
				{
					Link.l5 = "�������� �� ��������������� ������������ ��������� ���������.";
					Link.l5.go = "Plantation_AutoPurchase";
				}
				else
				{
					Link.l5 = "���������� ������������� ��������� ���������.";
					Link.l5.go = "Plantation_OffAutoPurchase";
				}
			}
			
			Link.l6 = "������, " + NPChar.name + ", ��� ���������� �����������.";
			Link.l6.go = "exit";
		break;
	
		case "Colony_AutoPurchase":
			dialog.Text = "�������, �������! �� ������������, ������� � ����� ��� � ������� ������� ����.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "Colony_AutoPurchase_Yes";
			Link.l2 = "�-�.. � ���������.";
			Link.l2.go = "exit";
		break;
		
		case "Colony_AutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Mines_AutoPurchase":
			dialog.Text = "�������, �������! �� ������������, ������� � ����� ��� � ������� ������� ����.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "Mines_AutoPurchase_Yes";
			Link.l2 = "�-�.. � ���������.";
			Link.l2.go = "exit";
		break;
		
		case "Mines_AutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Plantation_AutoPurchase":
			dialog.Text = "�������, �������! �� ������������, ������� � ����� ��� � ������� ������� ����.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "Plantation_AutoPurchase_Yes";
			Link.l2 = "�-�.. � ���������.";
			Link.l2.go = "exit";
		break;
		
		case "Plantation_AutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Colony_OffAutoPurchase":
			dialog.Text = "�� �������, �������?";
			Link.l1 = LinkRandPhrase("�������. ������� ������� ������������.", "������.", "������� ������.");
			Link.l1.go = "Colony_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("�-�.. �� �����, �� ����� ����� ������.", "��... � ���������.", "���������!");
			Link.l2.go = "exit";
		break;
		
		case "Colony_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Mines_OffAutoPurchase":
			dialog.Text = "�� �������, �������?";
			Link.l1 = LinkRandPhrase("�������. ������� ������� ������������.", "������.", "������� ������.");
			Link.l1.go = "Mines_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("�-�.. �� �����, �� ����� ����� ������.", "��... � ���������.", "���������!");
			Link.l2.go = "exit";
		break;
		
		case "Mines_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Plantation_OffAutoPurchase":
			dialog.Text = "�� �������, �������?";
			Link.l1 = LinkRandPhrase("�������. ������� ������� ������������.", "������.", "������� ������.");
			Link.l1.go = "Plantation_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("�-�.. �� �����, �� ����� ����� ������.", "��... � ���������.", "���������!");
			Link.l2.go = "exit";
		break;
		
		case "Plantation_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		
		case "Cost":
			dialog.Text = "����� ������� �� ������ � ����? ������ ��������� ��� � ������ �������� ���������� �������?";
			Link.l1 = "������ ��������� ��������� �������.";
			Link.l1.go = "Cost_Colony_Full";
			Link.l2 = "��������� ��������� ������� � ������ �������� ���������� �������.";
			Link.l2.go = "Cost_Colony";
			
			if(bGoldMine || bSilverMine || bIronMine)
			{
				Link.l3 = "������ ��������� ��������� ��������.";
				Link.l3.go = "Cost_Mines_Full";
				Link.l4 = "��������� ��������� �������� � ������ �������� ���������� �������.";
				Link.l4.go = "Cost_Mines";
			}
			
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l5 = "������ ��������� ��������� ���������.";
				Link.l5.go = "Cost_Plantation_Full";
				Link.l6 = "��������� ��������� ��������� � ������ �������� ���������� �������.";
				Link.l6.go = "Cost_Plantation";
			}
			
			Link.l7 = "������, " + NPChar.name + ", ��� ���������� �����������.";
			Link.l7.go = "exit";
		break;

		case "Cost_Colony_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", false);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ������ ��������� ��������� ������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "Cost_Colony":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", true);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ��������� ��������� ������� � ������ �������� ���������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", false);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ������ ��������� ��������� �������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", true);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ��������� ��������� �������� � ������ �������� ���������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", false);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ������ ��������� ��������� ��������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", true);
			dialog.Text = "�� ������ ������, � ������ ����������� �������, ��������� ��������� ��������� � ������ �������� ���������� ����������: " + iCost + " ��������.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "quests";
		break;

		case "AutoPurchase":
			dialog.Text = "������������� ��������� ��������� ������������� ���������� ������� ������� � ������ �������� ����������� ����������� ������� ������ ������������� - ����������, ������������� � ���� �������������. ������� ������������ ���������� ���� ������� ������ ��������� ������� ����� � �������. \n ������������� ���������� ��������� � ������ ������� ��������� �������� �������� � ������. ��������, ����� ��������� ����� ������� ��������� � ������������� � ������ ������ ����������� " + GetSumAutoPurchaseColonyGoods("Colony", true) + " ��������. ��������� �� ������� �� ��������������� - �������� ��������� ����� �������� ��� ������� � ���������. \n ������ ��������� ���� ������������ ��������� ��������� ���� ��������, � ���� ����� ������� ����� ����� ����������� �����, �� �� ������ �������. ����� ����, ��� ��� ������ � ���� ���������, ������� ������ ����� ������ �������� �������, ������ � ������ ��������. ���� �� �������� ��������������� ���� ������������ - �� ������ ������� ��� �� ����.";
			Link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			Link.l1.go = "exit";
		break;
		
		//////////////////////////////////////////////////////////////////////////
		// ���� ����
		//////////////////////////////////////////////////////////////////////////
		case "AutoSell_1":
			dialog.text = "��� ������ �� ������ ������ �� ����, �������?";
			link.l1 = "�������� �� ������������ ������� ����-�����.";
			link.l1.go = "AutoSell_SetAction";
			link.l2 = "� ���� ���������� ���������� ���������� ������.";
			link.l2.go = "AutoSell_SetQty";
			link.l3 = "��������� ����, �� ������� �������� �����.";
			link.l3.go = "AutoSellCosts";
			link.l4 = "� ���� ������ ��������� �� ����.";
			link.l4.go = "AutoSellInfo";
			link.l5 = "��������, � ���� ���� ���.";
			link.l5.go = "exit";
		break;
		
		case "AutoSell_SetAction":
			dialog.text = "��, ������� ���������. " + GetColonyAutoSellWork();
			
			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.ColonyBuilding.Mines.AutoSell == false)
				{
					link.l1 = "� ����, ����� ����� ���������� �� ������ ��������.";
					link.l1.go = "AutoSell_Mines_On_1";
				}
				else
				{
					link.l1 = "� ���� ������������� ������� ������ �� ������ ��������.";
					link.l1.go = "AutoSell_Mines_Off_1";
				}
			}
			
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{	
				if(PChar.ColonyBuilding.Plantation.AutoSell == false)
				{
					link.l2 = "� ����, ����� ����� ���������� �� ������ ���������.";
					link.l2.go = "AutoSell_Plantation_On_1";
				}
				else
				{
					link.l2 = "� ���� ������������� ������� ������ �� ������ ���������.";
					link.l2.go = "AutoSell_Plantation_Off_1";
				}
			}
			
			link.l3 = "�������, � ���������.";
			link.l3.go = "exit";
		break;
		
		case "AutoSell_Mines_On_1":
			dialog.text = "�� �������, �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������.");
			link.l1.go = "AutoSell_Mines_On_2";
			link.l2 = LinkRandPhrase("��... �������, �� ����� - ����� �������� ���.", "� ���������.", "���... ���, �� ������.");
			link.l2.go = "exit";
		break;
		
		case "AutoSell_Mines_On_2":
			PChar.ColonyBuilding.Mines.AutoSell = true;
			dialog.text = "������, �������! � ������������ ��� ������� ���� ��������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;
		
		case "AutoSell_Plantation_On_1":
			dialog.text = "�� �������, �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������.");
			link.l1.go = "AutoSell_Plantation_On_2";
			link.l2 = LinkRandPhrase("��... �������, �� ����� - ����� �������� ���.", "� ���������.", "���... ���, �� ������.");
			link.l2.go = "exit";
		break;
		
		case "AutoSell_Plantation_On_2":
			PChar.ColonyBuilding.Plantation.AutoSell = true;
			dialog.text = "������, �������! � ������������ ��� ������� ���� ��������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;
		
		case "AutoSell_Mines_Off_1":
			dialog.text = "�� ������������� ������ ������������� ���� ������� �� �������� �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������.");
			link.l1.go = "AutoSell_Mines_Off_2";
			link.l2 = LinkRandPhrase("���������!", "�, �������, ��������� - ��� ���������� ������������ ������� �������.", "���... ���, �� ������.");
			link.l2.go = "exit";
		break;
		
		case "AutoSell_Mines_Off_2":
			PChar.ColonyBuilding.Mines.AutoSell = false;
			dialog.text = "��� ���������, �������. � ����� ������, ��� �������� ����� ����������� ���� ������ � �������� - ���������.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
		
		case "AutoSell_Plantation_Off_1":
			dialog.text = "�� ������������� ������ ������������� ���� ������� �� ��������� �������?";
			link.l1 = LinkRandPhrase("��.", "���������� �����.", "������� ��, ������.");
			link.l1.go = "AutoSell_Plantation_Off_2";
			link.l2 = LinkRandPhrase("���������!", "�, �������, ��������� - ��� ���������� ������������ ������� �������.", "���... ���, �� ������.");
			link.l2.go = "exit";
		break;
		
		case "AutoSell_Plantation_Off_2":
			PChar.ColonyBuilding.Plantation.AutoSell = false;
			dialog.text = "��� ���������, �������. � ����� ������, ��� �������� ����� ����������� ���� ������ � ��������� - ���������.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
		
		case "AutoSell_SetQty":
			if(PChar.ColonyBuilding.Mines.AutoSell == false && PChar.ColonyBuilding.Plantation.AutoSell == false)
			{
				dialog.text = "�������, �� ������ ������ ����-���� ������� �� ������������� �� �� ��������, �� �� ���������.";
				link.l1 = LinkRandPhrase("�������.", "����.", "������.");
				link.l1.go = "exit";
				break;
			}
			
			dialog.text = "������� ���������� ���������� ������ ��� ��������: " + GetColonyAutoSellCurrentQty("Mines") + ", � ��� ���������: " + GetColonyAutoSellCurrentQty("Plantation") + ". ������������ ���������� ���������� ������ ��� ��������: " +AUTO_SELL_MINES_MAX+ ", ��� ��������� ��: " +AUTO_SELL_PLANTATION_MAX+ ".";
			
			if(PChar.ColonyBuilding.Mines.AutoSell == true)
			{
				link.l1 = "���������� �������� ���������� ���������� ������ �� ��������.";
				link.l1.go = "AutoSell_SetQty_Mines_1";
			}
				
			if(PChar.ColonyBuilding.Plantation.AutoSell == true)
			{
				link.l2 = "���������� �������� ���������� ���������� ������ �� ���������.";
				link.l2.go = "AutoSell_SetQty_Plantation_1";
			}
			
			link.l3 = "�������, � ���������.";
			link.l3.go = "exit";
		break;
		
		case "AutoSell_SetQty_Mines_1":
			dialog.text = "����, ����� ���������� �� ������ ���������� ��� ����� ������ �� ��������?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Mines_2";
		break;
		
		case "AutoSell_SetQty_Mines_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);
			
			if(iQty <= 0)
			{
				dialog.text = "������ ��������?";
				link.l1 = "������� ��� ��� ���������...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "� ���������.";
				link.l2.go = "exit";
				break;
			}
			
			if(iQty > AUTO_SELL_MINES_MAX)
			{
				dialog.text = iQty + "? �������, � �� ��� ������������, ��� ������������ ���������� ��� ����� ������, �������� �� ��������, ����� " + AUTO_SELL_MINES_MAX + " ��.";
				link.l1 = "������� ��� ��� ���������...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "� ���������.";
				link.l2.go = "exit";
				break;
			}
			
			dialog.text = iQty + "? ��� �, ��� ���������� �����. �� ������� � ���� �������?";
			link.l1 = "��, ���������.";
			link.l1.go = "AutoSell_SetQty_Mines_3";
			link.l2 = "���, � ���������.";
			link.l2.go = "exit";
		break;
		
		case "AutoSell_SetQty_Mines_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);
			
			PChar.ColonyBuilding.Mines.AutoSell.Qty = iQty;
			dialog.text = "������, �������� �������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;
		
		case "AutoSell_SetQty_Plantation_1":
			dialog.text = "����, ����� ���������� �� ������ ���������� ��� ����� ������ �� ���������?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Plantation_2";
		break;
		
		case "AutoSell_SetQty_Plantation_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);
			
			if(iQty <= 0)
			{
				dialog.text = "������ ��������?";
				link.l1 = "������� ��� ��� ���������...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "� ���������.";
				link.l2.go = "exit";
				break;
			}
			
			if(iQty > AUTO_SELL_PLANTATION_MAX)
			{
				dialog.text = iQty + "? �������, � �� ��� ������������, ��� ������������ ���������� ��� ����� ������, �������� �� ���������, ����� " + AUTO_SELL_PLANTATION_MAX + " ��.";
				link.l1 = "������� ��� ��� ���������...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "� ���������.";
				link.l2.go = "exit";
				break;
			}
			
			dialog.text = iQty + "? ��� �, ��� ���������� �����. �� ������� � ���� �������?";
			link.l1 = "��, ���������.";
			link.l1.go = "AutoSell_SetQty_Plantation_3";
			link.l2 = "���, � ���������.";
			link.l2.go = "exit";
		break;
		
		case "AutoSell_SetQty_Plantation_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);
			
			PChar.ColonyBuilding.Plantation.AutoSell.Qty = iQty;
			dialog.text = "������, �������� �������.";
			link.l1 = "��� � ������.";
			link.l1.go = "exit";
		break;
		
		case "AutoSellCosts":
			dialog.text = "������: " + GetCurrentGoodBaseCostForAutoSell(GOOD_GOLD) + " �������; �������: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SILVER) + " �������; ������: " + GetCurrentGoodBaseCostForAutoSell(GOOD_IRON) + " �������; �����: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SUGAR) + " �������; ����: " + GetCurrentGoodBaseCostForAutoSell(GOOD_COFFEE) + " �������.";
			link.l1 = "������� �� ����������. ����� ��� ��������� � �������.";
			link.l1.go = "AutoSell_1";
			link.l2 = "������� �� ����������. �, �������, �����.";
			link.l2.go = "exit";
		break;
		
		case "AutoSellInfo":
			dialog.text = "����� ��������� � ������� ������������ ��������� ����� �������, �� ������ ��������������� ����-�������� ������� �� ������� ������ ��� ����� ������������ ����� �� ������ ��� � �������. \n ������ ��� �� ������� �� ������� ����� �������� ��������� ���� ����� �������. \n ���������� ������������ ����� ���������� ��� � ������� ��� ������� ������� - ������ ���� � �������� �� ������ ������� �� ����� " +AUTO_SELL_MINES_MAX+ " ��., � ������, ������� �� ���������, �� ����� " +AUTO_SELL_PLANTATION_MAX+ " ��. \n ���� ���������� ������ �� ������ ����� ������ ���������� ���� ���������� ��� �������, �� �������� ���� ��������� ����� ������� ����. \n ���� ����� ����� ����������� �������� ������� - �� ������ �������� ��������� � ������ �������� ��������. ����� ������, ��� ������� ��� � ������� ����� ����������� �� �����, ������� �������, ��� ��� ��������������� �������, ��� ��� ��� ������� �� ����� ����������� � ��������������� � ���� �� ����.";
			link.l1 = LinkRandPhrase("�������.", "����.", "������.");
			link.l1.go = "exit";
		break;
	}
	
	UnloadSegment(NPChar.FileDialog2);
}

