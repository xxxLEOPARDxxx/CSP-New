
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
		case "Meet":
			dialog.text = "����������� ���. � - " + GetFullName(NPChar) + ", ��������� ��������� ���������. �������������, ����������.";
			Link.l1 = "������������, " + GetFullName(NPChar) + ". � " + GetFullName(PChar) + ", ������� ������� '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;
		
		case "Meet_2":
			if (!CheckAttribute(npchar,"met")) dialog.text = "������� �������������. �� ������ ������ �����?";
			else dialog.text = "�� ������ ������ �����, �������?";
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > 0 && sti(npchar.SlavesLimit)>0)
			{
				Link.l1 = "� �� �����"+ GetSexPhrase("","�")+" ��� ���������� ������... �����.";
				link.l1.go = "trade_good";
			}
			Link.l2 = "������ ����������"+ GetSexPhrase("��","���")+", ����� �������.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;
		
		case "trade_good":
			dialog.text = "�����? �� ������ �������, �����?";
			Link.l1 = "��, ������.";
			link.l1.go = "trade_good_2";
			Link.l2 = "������� � ���������"+ GetSexPhrase("","�")+". ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "trade_good_2":
			dialog.text = "������ ��������� ��������� ����������� �� 1000 ����� ������ ��� ������ � ������� ���. ������� �� ������ ����������?";
			Link.l1 = "���� � ���������� "+sti(pchar.Ship.Cargo.Goods.Slaves)+".";
			link.l1.go = "trade_good_3";
			Link.l2 = "������� � ���������"+ GetSexPhrase("","�")+". ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "trade_good_3":
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > sti(npchar.SlavesLimit)) dialog.text = "������ � ���� ������ � ��� �� "+npchar.SlavesLimit+ " ����� ����� �� 215 �� �������. �����, "+FindRussianMoneyString(sti(npchar.SlavesLimit)*215)+". ����������?";
			else dialog.text = "������ � ���� ������ � ��� �� "+npchar.SlavesLimit+ " ����� ����� �� 215 �� �������. �����, "+FindRussianMoneyString(sti(pchar.Ship.Cargo.Goods.Slaves)*215)+". ����������?";
			Link.l1 = "������.";
			link.l1.go = "trade_good_4";
			Link.l2 = "������� � ���������"+ GetSexPhrase("","�")+". ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "trade_good_4":
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > sti(npchar.SlavesLimit))
			{
				AddMoneyToCharacter(pchar, 215*sti(npchar.SlavesLimit));
				pchar.Ship.Cargo.Goods.Slaves = sti(pchar.Ship.Cargo.Goods.Slaves) - sti(npchar.SlavesLimit);
				npchar.SlavesLimit = 0;
			}
			else
			{
				AddMoneyToCharacter(pchar, 215*sti(pchar.Ship.Cargo.Goods.Slaves));
				npchar.SlavesLimit = sti(npchar.SlavesLimit)-sti(pchar.Ship.Cargo.Goods.Slaves);
				pchar.Ship.Cargo.Goods.Slaves = 0;
			}
			SetTimerFunction("RefreshSlavesLimit", 0, 0, 14);
			dialog.text = "�������, ��� ���� ������.";
			Link.l1 = "��������� ���.";
			link.l1.go = "exit";
		break;
	}
}
