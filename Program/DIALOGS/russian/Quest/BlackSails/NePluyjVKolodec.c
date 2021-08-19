
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
		
		case "BS_NPVK_1":	//��������
			dialog.text = "�������, ������ �������, �� ����� ����������� ����� ��������� ����� ���� � ����. ������� ������, ��������";
			link.l1 = "��������, �� � �� �������. ��� ���������?";
			link.l1.go = "BS_NPVK_2";
		break;
			
		case "BS_NPVK_2":
            dialog.text = "���������� � ���� �����, ��� ������� ������� � ������ � ����� ��� �������� ������ � �������. ��� ������� � ��� � �������� �������.";
            link.l1 = "��. ����� ��� � �� ��������. ������, �� �������.";
			link.l1.go = "exit";
		break;	
		
		case "BS_NPVK_3":	//�����
            dialog.text = "�, ��� � ��� ���������� �������! ������ ������� �����������? ������� ������, �� ������������ � ��� ����� � ��������� ����� �� ������ ��� �����.";
            link.l1 = "��. ���� � ���, ��� �������� � �������� � ���� ������ ��������� ����� �� ���� ����, �������, ��� ��� �� ���� ��������. ���� � ����������������, � ��� ����?";
			link.l1.go = "BS_NPVK_4";
		break;

		case "BS_NPVK_4":
            dialog.text = "���� � ����� ������������������, � ��� � �����, � ����������� � ����� ������ �����. ��������� ���������.";
            link.l1 = "������ ���.";
			link.l1.go = "BS_NPVK_5";
		break;
		
		case "BS_NPVK_5":
            dialog.text = "������� �������� ����� ��������, ����� ������, ���, ����� �������, ���������� ����� �����. ���� ������� ��������, � ����� � �������� �����, ��� ��������, ���������� ������ ��������� � �������� ������� ����. � ��� ����� � ������������ � ����������� ������� ������.\n"+
							"� �����, ����� ������ ������� ������, ��� ��� ������� �� ���� � �������� ������� ����. ������, �����"+ GetSexPhrase("��","��") +" ��"+ GetSexPhrase("�","�") +" � ����� �����.\n";
            link.l1 = "��� '����������' ���, �� ���� ��� ������� � ����� �������� �� ����������. �� ��� ��������� ��������� �������� �� ����� ����������, � � �����"+ GetSexPhrase("","�") +" �������� � ���� ����� ��� � ������������. �� �������, ����� � ��� � ���� ����� ���� �����������?";
			link.l1.go = "BS_NPVK_6";
		break;
		
		case "BS_NPVK_6":
            dialog.text = "�������. ��� ��� � ���� ������� �� ����������� � ����������� ���� �����, �� ������������: ��� ����� � �������� ����� ������!";
            link.l1 = "�� ��� �� ���� ���������, �����?";	//�����
			link.l1.go = "Fight_gatri";
			link.l2 = "������� ������ ��� � ����� ������� ����� '�����������'.";
			link.l2.go = "BS_NPVK_7";
		break;
		
		case "Fight_gatri":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "BS_NPVK_7":
            dialog.text = "600 ��� ������� ����. ����� ��� ������� � �� ��� �����. � �� ������� ��� �������������.";
            link.l1 = "�������?! �� �� � ���� ���? ��� �� ����������!";
			link.l1.go = "BS_NPVK_8";
		break;
		
		case "BS_NPVK_8":
            dialog.text = "������ ������� ������� ������� ��� ����� � � ������� �� ����� �������. �������, ������ ���� ������?";
            link.l1 = "� ��� ��������� �������� ����� ���������� ������? ���� �������� � ��� ��� ��������!";
			link.l1.go = "BS_NPVK_9";
		break;
		
		case "BS_NPVK_9":
            dialog.text = "�� �� ������� �����? �����? ����������? ������� �������� ������� ���� ���������? ������� ����. ���� � ���� �����. ����� ��� �������� �� �������� � ����� � ������ �����, ����� ��������� �������� �������� ��� ���� ������.";
            link.l1 = "��, � ���"+ GetSexPhrase("��","��") +".";
			link.l1.go = "exit";
			AddQuestRecord("BSPrologue", "2");
			pchar.BSPrologue.GatriGold = 600;
			SetTimerCondition("Gatri_Hunters", 0, 0, 30, true);//������ ������� �� ���
			NextDiag.TempNode = "BS_NPVK_10";
		break;
		
		case "BS_NPVK_10":	//�����, ������� ������� �� ���������
            dialog.text = "�� ���������?";
			if (GetSquadronGoods(Pchar, GOOD_GOLD) > 0)
			{
				link.l1 = "���, ��� ��� ������� ������.";
				link.l1.go = "BS_NPVK_11"
			}
			//SetCharacterGoods(pchar, GOOD_GOLD, 400);//test
			link.l2 = "��� �����.";
			link.l2.go = "exit"
		break;
		
		case "BS_NPVK_11":
			int ammount = GetSquadronGoods(Pchar, GOOD_GOLD);
			if (sti(pchar.BSPrologue.GatriGold) > ammount)
			{
				RemoveCharacterGoods(Pchar, GOOD_GOLD, ammount);
				pchar.BSPrologue.GatriGold = sti(pchar.BSPrologue.GatriGold) - ammount;
				dialog.text = "�������� ������, ��� �������� ��� "+pchar.BSPrologue.GatriGold+" ���.";
				link.l1 = "��, � ���"+ GetSexPhrase("��","��") +".";
				link.l1.go = "exit";
			}
			else
			{
				RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.BSPrologue.GatriGold));
				dialog.text = "����, ����� ���. �� ������ ������, ���� ����������� �������. ������ ���� ������ ��������������� � ������������ ���������. �������� ���!";
				if (CheckAttribute(pchar, "BSPrologue.GatriHunters"))
				{
					link.l1 = "������ �� ������� ����� ���������?";
					link.l1.go = "BS_NPVK_12";
				}
				link.l2 = "�� ��������.";
				link.l2.go = "end_quest";
			}
		break;	
		
		case "end_quest":
			SaveCurrentQuestDateParam("BSPrologueEnded");
			AddQuestRecord("BSPrologue", "3");
			CloseQuestHeader("BSPrologue");
			DeleteAttribute(pchar, "BSStart")//������� ���������� �������� � ����������� ���������� ���
			pchar.BSInProgress = true;
			NPChar.Dialog.Filename = "Common_store.c";
			NPChar.Dialog.CurrentNode = "Second time";
			//NextDiag.TempNode = "Second time";
			DialogExit();
		break;	
		
		case "BS_NPVK_12":
			dialog.text = "�����, � ����� �� ����� ������, �� ���� �������� �� ���� ��� ��������. ������ ��������� �� ��������� ����� ����������\n������ ��� ����� ��������, ������� �������, � ��������� ������ ���������� ����� ���� ������� �������. ��, � �������, �� ���������� ������� � ������� ���������� �� ����� ���������. �� ����� ������� ���� ���� ����������, ��� �� �������� � ��� ����� ��������.";
			link.l2 = "��� ����� ������� ��� ��������, ��, �������, � ����������. �� ��������.";
			link.l2.go = "end_quest";
		break;
	}
}
