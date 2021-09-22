
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
		case "First time":
			if (NPChar.id == "GWIK_char") dialog.text = "����������� ���. � - " + GetFullName(NPChar) + ", ������������� ����� ����������� ����-������� �������� �������� �� ������� �������. �������������, ����������.";
			else dialog.text = "����������� ���. � - " + GetFullName(NPChar) + ", ������������� ����� ����������� ����-������� �������� �������� �� ������� ��� ������. �������������, ����������.";
			Link.l1 = "������������, " + GetFullName(NPChar) + ". � " + GetFullName(PChar) + ", ������� ������� '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;
		
		case "Meet_2":
			if (!CheckAttribute(npchar,"met")) dialog.text = "������� �������������, �������. �� ������ ������ �����?";
			else dialog.text = "�� ������ ������ �����, �������?";
			if (!CheckAttribute(npchar,"Timer"))
			{
				Link.l1 = "� �� �����"+ GetSexPhrase("","�")+" ���������� � ��� ���������� � ����� � ��������� �� ����������.";
				link.l1.go = "trade_info";
			}
			Link.l2 = "������ ���"+ GetSexPhrase("��","���")+" �������������, ����� �������.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;
		
		case "trade_info":
			dialog.text = "��, � ���������� ����� ����������� � ���� � ����������. � ��� 50000 ��������.";
			if (sti(pchar.money) >= 50000)
			{
				Link.l1 = "������, ��� ���� ������.";
				link.l1.go = "trade_info_2";
			}
			Link.l2 = "������� � ���������"+ GetSexPhrase("","�")+". ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "trade_info_2":
			for (int i = 0; i< MAX_COLONIES; i++)
			{
                ref rcolony = &Colonies[i];
			    if (rcolony.id != "Caiman" && rcolony.id != "Panama" && rcolony.nation != "none") SetPriceListByStoreMan(rcolony);
            }
			log_info("������� ������ ��� �� ���� ��������� ���������� ����������.");
			PlayStereoSound("notebook");
			AddMoneyToCharacter(pchar,-50000);
			
			dialog.text = "...�������, ����� ��� ������ ��� ����������. ����� �������!";
			Link.l1 = "��������� ���. �� ��������!";
			link.l1.go = "exit";
			npchar.Timer = true;
			SetTimerFunction("RefreshGWIK", 0, 0, 15);
		break;
	}
}
