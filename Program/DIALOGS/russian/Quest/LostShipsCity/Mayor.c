
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	string NodeName = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.location == "SanAugustineResidence")
			{
				dialog.text = "��� �� �����"+ GetSexPhrase("","�") +"? �� ���������� ���� �� ��������, � �����.";
				link.l1 = "������, ��� ������ ��������"+ GetSexPhrase("","�") +" � ����.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "����� � �� � ���� � ����������, ��, � ��������, �� ����� ����������... ��� �� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = "�� ���, ������ �����"+ GetSexPhrase("","�") +" ������, ��� �� � ������� � ������.";
				link.l1.go = "NRes_1";
			}
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				pchar.questTemp.LSC = "AdmiralFoundHero";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "�-�-�, ��� � ��. ��� ������, ��� �� ���"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("��","��") +" �� ���. �� �����, ����� �� ���� ������, �� ��� � ����� �����...";
					link.l1 = "�� �� ���� ������ �� �������"+ GetSexPhrase("","�") +". ���� ����� " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
					PChar.quest.LSC_admiralOwnFind.over = "yes";
				}
				else
				{
					dialog.text = "�-�-�, ��� � ��. � ����, ����� �� ������� �� ���.";
					link.l1 = "�����������. ���� ����� " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				break;
			}
			//��������� ���� �� ������� �������
			if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
			{
				link.l4 = "�������, � ���� ���� ��� ���� ������ ����������. ��, ��� ��� �������...";
				link.l4.go = "NarvalRing_1";
			}
			if (pchar.questTemp.LSC == "NarvalDestroyed")
			{
				link.l4 = "� ��� ������"+ GetSexPhrase("","�") +", ���� '������' ���������. �������"+ GetSexPhrase("","�") +" ��� ���� ��� ������, ����� �� ����!";
				link.l4.go = "DestrNarval_1";
			}
			if (pchar.questTemp.LSC == "toAdmiralBarmenDead")
			{
				link.l4 = "�������, � �����"+ GetSexPhrase("","�") +" ���������� �� �������� ����� ��������.";
				link.l4.go = "BarmenDead_1";
			}
			if (pchar.questTemp.LSC == "fromMechanicToAdmiral")
			{
				link.l4 = "�������, � �����"+ GetSexPhrase("","�") +" ���������� � �����.";
				link.l4.go = "CasperDead_1";
			}
			//�������������� ��������� ����
			//��� ���� ������
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.ElisHusband == "toElis")
			{
				link.l5 = "�������, �����, ����������, ��� ������ ������ ������� ��� � ����?";
				link.l5.go = "ELTHusb_begin";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
			{
				link.l5 = "�������, � �����"+ GetSexPhrase("","�") +" �� ������ ������� �������.";
				link.l5.go = "ELTHusb_SF";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiralGood")
			{
				link.l5 = "�������, � ��� �����"+ GetSexPhrase("","�") +" ���-��� �� ��������������� ���� ���� � ��������.";
				link.l5.go = "ELTHusb_good";
			}
			//����� �� �������� ��������
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.lostDecster == "toAdmiral")
			{
				link.l6 = "�������, � ���� ���� � ���� ��������� ������ �� ������ ������� ��������.";
				link.l6.go = "LostDecster";
			}	
			//����� ������� �� ������
			if (pchar.questTemp.LSC == "toSeekGoods")
			{
				link.l8 = "������, � ��� ��� ���-����� ������. �� ��� �� �� ���� ��������?";
				link.l8.go = "SeekGoods";
			}
			//���� �������
			if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
			{
				link.l8 = "�������, ����������� �����...";
				link.l8.go = "SeekCrew";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NRes_1":
			dialog.text = "��, ��� ������. � ���, ��� ���� ��� ���� ������� ��� �����. �� "+ GetSexPhrase("������� ���������","������� ���������") +".";
			link.l1 = "���"+ GetSexPhrase("","�") +" ���������, �������!";
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = "����� ������, "+ GetSexPhrase("��������","�������") +", ������ ������������... � ���� ����� " + GetFullName(npchar) + ", � ������� ����� ������ ���������� ��������!"; 
			link.l1 = "��, � ���� ������"+ GetSexPhrase("","�") +" � ����! �� ��� ����� ��������� �������, ��� ����� �� ������ �� '����� �����' � ������. ��� ��� ���� �� ���������!";
			link.l1.go = "FT_1_1";
		break;
		case "FT_1_1":
			dialog.text = "��, ��� ��� ��� ������ � ��������� ����... ������, ��� ����������. ��� ��� �� ������� �� ��������� ��������, � � ���� �� ������ ����� ��������� �����... ������, ��� ��� ������� ����� �� ���, ��������� ������ ������ �, ������� � ����.";
			link.l1 = "�������...";
			link.l1.go = "FT_1_2";
		break;
		case "FT_1_2":
			dialog.text = "�� ������ �������, ������ ���� ������� �����. ��� ���, ����� � �� �������� �����, ��� �����, ��� ���� �������... ��, ������ �� �� �� ����!";
			link.l1 = "������, ��� �����. � ����������� ������, " + npchar.name + ".";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "������, ���! � ���� �������, ��� �� ����"+ GetSexPhrase("","��") +" � ���� �� ������ ������ �������, �� ����"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("����","���") +" ������, � ������ ������"+ GetSexPhrase("","�") +" ����������� ��� ������. ��� ���� �������?";
			link.l1 = "������. � ��� �� �����, ��� � ��� ����� ������������?";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "� ������� �������� ���� � � ������ ���������� ������. �� ��������� �� �� �����, ��� ��� � ������ � ��� ����������, ��-��... � ����� �� ���� ����� ����������� � ��������� �������\n"+
				"��� �������� ������ ���������� �������� ����� ����� �� �����. ��� ����� ������������ �������� �������, ������� ��������� � ������������ ��������, �� ���� � ���� ������������... ������, � �� �� ������ ���������� � �������?";
			link.l1 = "��� ���������. ������� ����� ��������, ���-�� ���������� �����, � ����� ��� ������ ����� �������.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "�� �� ���� "+ GetSexPhrase("������ ��������","������� ������") +". ��� ���"+ GetSexPhrase("","�") +" � ������� ����?";
			link.l1 = "�� ���, ������ ��, ������������"+ GetSexPhrase("","�") +"... ���"+ GetSexPhrase("","�") +" ��������� ���������, ����� ��, ��� � ��, � �����.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "�������... �� ������, ����������, ��� �� ����� ���� ���. ���� �� �� ��������� ���� �����"+ GetSexPhrase("���","���") +" ��� ������"+ GetSexPhrase("���","������") +", ������� ��� ������ ����� - ����� ��� �����. ������ �� ����"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("����","���") +" ������, �� ������ �������, ��������� �� ������� �������� ����� �� �����! ���, ��� ��������!..";
			link.l1 = "��, �������. �������� ��������������. ������, � ��������� ���� ����� ����� � �����-�� ������� ��������������. �������, ��� ��� � ���� ��� �����.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "���, ����� �� ����� ����. ���� ������ �������... ��, ���������. ����, � ������� ���, ������ � ����� ������������. ������: �� �� ������ ���������� �� ����� ������� ������. ���� �� ������ ����-��, �� ���� ���� �. ��� ����?";
			link.l1 = "��, ����...";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "��������� �����. � ��� ��� � ������ ���� ��� ����������, ��� ���������� ����� '������' � '������'. � �����, ��� ��������� ����, ������� ����� ���������������� �������� - ��� ����� � �����. �� �� �������� ��� ������� ��� ���������� ����� ���������� - ��� ���� '��� ��������' � ������ '�������'. ������� ��� ����� �� ������, ������� ����� ����� ������ �� ������\n"+
				"��� ���, �������� ������ ���� �������� ��������� �� ����� - ������ ��� �����. ���������� ��������� ������ ����� �������� � ������������� ������, � �� ���� ���������� � ��� ��������� ���� ������. ������� �� ���� ���� ��� ����� �� ����. �������?";
			link.l1 = "�������.";
			link.l1.go = "FT_7_1";
		break;
		case "FT_7_1":
			dialog.text = "������ ������. ������: ����������� ������� �������, ����� � ������ ������������. ��������� ������ ��� ����� ����������, � ��������� ����� ������.";
			link.l1 = "� ��� �������.";
			link.l1.go = "FT_7_2";
		break;
		case "FT_7_2":
			dialog.text = "������: �� ��������� � ������ ���������� �������� �����. ���� ���� ��������� ������"+ GetSexPhrase("����","����") +" � ����� ������� - �� ������������� ��������� ����������� � ����������� ��� ������. � ��� ������, ��� ����� �� ����� � ���� ������ ���...";
			link.l1 = "������ ���������... �� ��� ��, ��� ����. ��� ������?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "�� � ���������: ��� ������������ ��������, ������� ������ � �����, ����������� ������.";
			link.l1 = "��, � ��� �� ����� ������ ���������, ����������.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "���, �� ��� � ��� �����������? ���, � �������, ��, ��� ���������� ����, �����"+ GetSexPhrase("","�") +" � �����. � ������, ����� ����"+ GetSexPhrase("","�") +" ��� �������"+ GetSexPhrase("����","���") +"!\n� ��� ���� ���������, ��� ������������ ��������, ���������� �������������� ������. ��� ��� ��� ���� ������ ���� �����!";
			link.l1 = "��������! � � ����� ��������� �� ������"+ GetSexPhrase("��","��") +"!";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			if (pchar.questTemp.LSC == "AdmiralFoundHero")
			{
				dialog.text = "��� "+ GetSexPhrase("�����-�������","�������") +"! ������ �������� �� ���������, �� ������ ��������, � ���... �� � ���� ���� � ������� �������. ����, ��� �����������"+ GetSexPhrase("��","�") +" �������"+ GetSexPhrase("���","��") +" ������, ���������� 1/50 �����!";
				link.l1 = "�� ����� �� ���������!!";
				link.l1.go = "FT_11";
				pchar.money = makeint(sti(pchar.money) / 50);
			}
			else
			{
				dialog.text = "� ������ �������� ����� �� ����������. ������-��, ����� ��������� �������� ������� ������� ����� � ����� ��������� ��� �������. �� ��� ��� �� �������"+ GetSexPhrase("","�") +" �����, � ������ �� ����"+ GetSexPhrase("��","���") +" �� ��� ������� �� �������� � �����, ������ ����� ������ � ��������� ���� ���������� ���� ����. �� ���� ���� �� ��������� ������.";
				link.l1 = "��� ��� ��� ����� ������ �� ��������!";
				link.l1.go = "FT_12";
				pchar.money = 0;
			}
		break;
		case "FT_11":
			dialog.text = "������! �� ���, �� ��������� ��������... ������-��, ���� ��� ���� ��� ������� ��� �� � ����, � ��� ���� ������� �����...";
			link.l1 = "��� ��� ��� ����� ������ �� ��������!";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "�� �� ����"+ GetSexPhrase("��","��") +", "+ GetSexPhrase("��������","�������") +", ���� ��� �� ��������. �� ������, �� ������ ���, ��� ��� � ����� ���������. ��� ������� �� ���������� ����� ����, ��� ���� ��������� � ������� �����, ��� ������� �� ��������� � ���� ����������� �����.\n� ��� ������ ����� � ���, ����� ������. �, ����� � ����, � ������ �� �� ����������� - ���� �� ���, � �� ���!";
			link.l1 = "�� ��, �������������� ��� � ����...";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "�� ������� � ����� ���� ������, �� � ������ ������� ���� ������! � ���� � ����, ��� � ��������� ���, ���� �� ��� �� �����������, � ���� ������ ��������.";
			link.l1 = "�-��... �� ��� ��, �������� ���������. ������, � ���� ��� ������� ������.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "��� �����. � �� ������� ���� ��� ������, ��� ��������� �������!";
			link.l1 = "� �����...";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "�� ��� � �������... � ������ �� ������"+ GetSexPhrase("��","��") +" � ������ ������������ �� ������ ��� ������. �����, ��� ������, ����������� ������ � ������.";
			link.l1 = "��� � ��������, ���.";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			if (npchar.chr_ai.type == LAI_TYPE_ACTOR) LAi_SetLSCoutTypeNoGroup(npchar);
			AddDialogExitQuestFunction("LSC_admiralTakeAll");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//����� � ��, ���� ��� �� ������ � ��������
		case "FoundHero":
			npchar.quest.meeting = "1";
			NextDiag.TempNode = "First time";
			pchar.questTemp.LSC = "AdmiralNotFoundHero";
			dialog.text = "���, ���, ������, � ��, ������"+ GetSexPhrase("��","��") +" � ��������� ������. �����-�� ���, "+ GetSexPhrase("��������","�������") +", ������ ��� ����� � ������ ������ ���� �� ����� ������? �� ���, �� ������ ����� ��������?";
			link.l1 = "�����������. ����� ��������?";
			link.l1.go = "FoundHero_1";
		break;
		case "FoundHero_1":
			dialog.text = "������ �������, ��� �� �� ����"+ GetSexPhrase("","�") +" � ���, ��� �� ��� ����� ������� ����� ��, ��� ������ �������� � ������?";
			link.l1 = "�� ����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "FoundHero_2";
		break;
		case "FoundHero_2":
			dialog.text = "�������� ������ �� ����������� �� ���������������! � ������ ������, ��� ��.";
			link.l1 = "� ����� �������� �� ���������, � ��� �� ������"+ GetSexPhrase("","�") +" ������� ������. �������, ��� ������ ����� �����... ���� ����� " + GetFullName(pchar) + ".";
			link.l1.go = "FT_1";
		break;

		//�� ������ ������ ��������
		case "NarvalRing_1":
			dialog.text = "������.";
			link.l1 = "� ��� ������� ������"+ GetSexPhrase("","�") +" � ����� ������� '���������', � ���������� �������� ���"+ GetSexPhrase("��","��") +" ��� ���������� �������...";
			link.l1.go = "NarvalRing_2";
		break;
		case "NarvalRing_2":
			dialog.text = "��� �� �������? ������ �������, �� ����!";
			link.l1 = "��� ������. ��� ���, ��������.";
			link.l1.go = "NarvalRing_3";
		break;
		case "NarvalRing_3":
			dialog.text = "��-��, �� ��� �� ������ '�������'! ���, ��� �� ��� ���"+ GetSexPhrase("��","��") +", ��������?";
			link.l1 = "� ����� '����������'.";
			link.l1.go = "NarvalRing_4";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			BackItemName("DOjeronRing");
			BackItemDescribe("DOjeronRing");
			ref itm;
			itm = ItemsFromID("DOjeronRing");
			itm.picIndex = 2;
			itm.picTexture = "ITEMS_9";
		break;
		case "NarvalRing_3":
			dialog.text = "� ���� ��������, ��� ��� ���� ��������� �������� ����������� � �������� ����� ������?";
			link.l1 = "������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "NarvalRing_4";
		break;
		case "NarvalRing_4":
			dialog.text = "�-��, ���� ������� ���� ����������, ��� ��� ������... � �� ������"+ GetSexPhrase("","�") +" � '���������'?";
			link.l1 = "���, ���. ��� �� � ���� ������ �� �������. ���� ��� - ����� �������� ��� ����������.";
			link.l1.go = "NarvalRing_5";
		break;
		case "NarvalRing_5":
			dialog.text = "�� ��, ��� ������. �� ����� ���������� ��� ����� ������, ��� �����. ��� � ��� ���� ������. � �� ������, ��� ����������, ��� ������������ �����?";
			link.l1 = "��������, ����������. � ������������� ��������.";
			link.l1.go = "NarvalRing_6";
		break;
		case "NarvalRing_6":
			dialog.text = "��, ������... ���� � ���, ��� ������ � �������� ������, � ����� �������� ������ �������. ���� � ���������� � ���� ��� �� �����, ������� � ���� ������� ������� ������ ����� ����� ��� ������� � �������������. � ���� ������� ������������ ��� ����������� �����������, ��� � ���������� ����� '������' � '������'.";
			link.l1 = "�������... � ��� ������ ������? ���� ����������, ��� '�������' ��������� � �������� ������������ ������������� ������!";
			link.l1.go = "NarvalRing_7";
		break;
		case "NarvalRing_7":
			dialog.text = "���� ���������� �� ����� '������', ������� ��� ����� ���������������.";
			link.l1 = "���������� �������, �������!";
			link.l1.go = "NarvalRing_8";
		break;
		case "NarvalRing_8":
			dialog.text = "��� ��������! � � ������� ��� ����.";
			link.l1 = "��, ��� ���������?";
			link.l1.go = "NarvalRing_9";
		break;
		case "NarvalRing_9":
			dialog.text = "����������� '��������', "+ GetSexPhrase("��������","�������") +". ���� ��, ��� �� ����, ��������� ��� ����? ���� ��� ��������� ���� �� ������ ������!";
			link.l1 = "����! � ���-�� �� ����� ������� ������ �� �����������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "NarvalRing_10";
		break;
		case "NarvalRing_10":
			dialog.text = "�����, ��������"+ GetSexPhrase("","�") +"? �� �� ��������� ���, ��� ��� � �����?!";
			link.l1 = "�� �����. � � ���� � ���"+ GetSexPhrase("","�") +" ��������� ���������, �� �� ����������.";
			link.l1.go = "NarvalRing_11";
		break;
		case "NarvalRing_11":
			dialog.text = "�-�, �� ��� �� �����. � ��� ���� ����� ���� ����� � ������.";
			link.l1 = "��, ��� ������ ����. � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "NarvalRing_12";
		break;
		case "NarvalRing_12":
			dialog.text = "�������! ��� ����������� �� '�������' ����� ������ � ��������� ���, ��� �������. ��� ���� ����� ����� ���� �� '�������'.";
			link.l1 = "������, ���, ��� ������ � ������ ����.";
			link.l1.go = "NarvalRing_13";
		break;
		case "NarvalRing_13":
			AddQuestRecord("ISS_MainLine", "12");
			pchar.questTemp.LSC = "toDestoyAllNarval";
			int idxMent;
			pchar.questTemp.LSC.qtyOfficers = 0;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "officers", "officer_"+i);
					characters[idxMent].Dialog.CurrentNode = "OffNarval";
					characters[idxMent].cityTape = "quest"; //��� ���
					LAi_SetStayTypeNoGroup(&characters[idxMent]);
					pchar.questTemp.LSC.qtyOfficers = sti(pchar.questTemp.LSC.qtyOfficers) + 1;
				}
			}
			pchar.quest.NavalEnterOfficers.win_condition.l1 = "location";
			pchar.quest.NavalEnterOfficers.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.NavalEnterOfficers.function = "NavalEnterOfficers";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//���� ������ ���������
		case "DestrNarval_1":
			dialog.text = "�� ��� ��, ��� ������. � ��� ��� ��� ����?";
			iTemp = 0;
			for (i=1 ; i<=3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					iTemp++;
				}
			}
			if (iTemp == 0)
			{
				link.l1 = "��� �������, � ���������. ��� ����� ����...";
				link.l1.go = "DestrNarval_Bad";
			}
			else
			{
				if (iTemp == sti(pchar.questTemp.LSC.qtyOfficers))
				{
					link.l1 = "�� ��� ���������. ��� ���� � �������, ��������� �� ���� � ������� � �����������.";
					link.l1.go = "DestrNarval_Ok";
				}
				else
				{
					link.l1 = "������ �������, �� ������� �� ���. ���������� � ����� ���������.";
					link.l1.go = "DestrNarval_BadOk";
				}
				DeleteAttribute(pchar, "questTemp.LSC.qtyOfficers");
			}
		break;
		case "DestrNarval_Bad":
			dialog.text = "�-��, ��������... ������, ������ ���������, '�������' ����������, � ��� �������. ��� ��� ��� � �������.";
			link.l1 = "�� ��, ��� �����, ��� ���������...";
			link.l1.go = "DestrNarval_Bad1";
		break;
		case "DestrNarval_Bad1":
			dialog.text = "�� ��� ��, �������. � ���� ������ �� ����������, �� ������ ����.";
			link.l1 = "��... ��, �������, �������...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "16");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
		break;
		case "DestrNarval_Ok":
			dialog.text = "�������! �� ������ ��������� ������, �, �������, ������� ���� �������. ��� ����� �������! �������, ��� ����.";
			link.l1 = "��, ��� ����� ���� ������ �� �����, �� ��� ����� ������� ����.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "14");
			AddMoneyToCharacter(pchar, 100000);
		break;
		case "DestrNarval_Ok1":
			dialog.text = "�� �� ���! ��, � ���� ������ �� ����������, ��� ��� ������ �������� ���������� ������ ������.";
			link.l1 = "��... ������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
		break;
		case "DestrNarval_BadOk":
			dialog.text = "�-��, ��������� ���������... �� �� �����, ���-���� ��� ���� �����, � �� ������ �������� �� ������. � �����, � ���, ��� ��� ��������� ������. ���� ��������� ���� ������� �� ������. ������ ����� �������!";
			link.l1 = "��, ������ ����� ����� �� �����... �� ��� ����� �������.";
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "15");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
			AddMoneyToCharacter(pchar, 10000);
		break;
		//������������� � ��������
		case "Interception":
			sld = characterFromId("Blaze");
			bool bOk = false;
			float fAng;
			GetCharacterAy(sld, &fAng);
			if (fAng > -1.35 && fAng < -0.28) bOk = true;
			if (fAng > 1.8 && fAng < 2.9) bOk = true;
			if (sti(sld.questTemp.LSC.itemState) && bOk)
			{
				dialog.text = "��� ���� ������, �������.";
				link.l1 = "��� ���� � ����� '������?'";
				link.l1.go = "Interception_1";				
				sld.questTemp.LSC = "InterceptionOk";
				sld.questTemp.LSC.knowMechanic = true; //���� �� ����� � ��������
			}
			else
			{
				dialog.text = "��� ���� ������, �������.";
				link.l1 = "����... �������, �� �������� ���-�� ����. ��������� � ������ �����.";
				link.l1.go = "exit";				
				sld.questTemp.LSC = "InterceptionYouSeen";
				AddDialogExitQuestFunction("LCS_EndScriptInterception");
			}
		break;
		case "Interception_1":
			sld = characterFromId("Blaze");
			dialog.text = "�������. �������� ����� ����, ��� �� �������� �����������.";
			link.l1 = "��-��... �� ������, � ���� ��� ��������� ���� �����. �, ��� �������, ������ ������� �� ��� ������� "+ NPCharSexPhrase(sld, "����� ������","���� ������ �����") +"...";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "������ ������","����� ����� ������ �����") +"?";
			link.l1 = "�� "+ NPCharSexPhrase(sld, "����� ������ ����������","���� ����� ���������") +", " + GetFullName(sld) + " "+ NPCharSexPhrase(sld, "���","��") +" �����. ��, ��������, ������, ��� ����� ������ ����������� � ������ ��������. ��� ���, "+ NPCharSexPhrase(sld, "���� ����� ��������� ������","��� ����� ��������� ��������") +" ��� ������ �������� � ������"+ NPCharSexPhrase(sld, "","�") +", ��� ���"+ NPCharSexPhrase(sld, "��","��") +" ��� �� ����� ��������. ���� ��� � ���� ������ �������, � �� ���� ����� ����������� � ���� �����, ��� ��� ����������� ������� ������ ����������� ����� ����������, �� �������� �� ���� ����������. ������ "+ NPCharSexPhrase(sld, "����� '�����'","��� '�������'") +" �� ��������, ��� "+ NPCharSexPhrase(sld, "���","��") +" ��� ����� �� ������� � �������.";
			link.l1.go = "Interception_4";
		break;
		case "Interception_4":
		sld = characterFromId("Blaze");
			dialog.text = ""+ NPCharSexPhrase(sld, "","��� ��� �����! ") +"��, ��, ��� ��"+ NPCharSexPhrase(sld, "","�") +" �� ���� ���������"+ NPCharSexPhrase(sld, "","�") +" � ��� ���������. �� ��, �������, �� ���� "+ NPCharSexPhrase(sld, "���","��") +" � ���� ����� ���?";
			link.l1 = "���, � �� ������� "+ NPCharSexPhrase(sld, "���","��") +". �� ������� ����� ��"+ NPCharSexPhrase(sld, "","�") +" ���"+ NPCharSexPhrase(sld, "","�") +" ��������� ���������, � ����� ����� ������ ����� ���������. ���� ���� ������������ "+ NPCharSexPhrase(sld, "���","��") +" � ����� ���������, � ������ � ���������� � ������ ����.";
			link.l1.go = "Interception_5";
		break;
		case "Interception_5":
			dialog.text = "������, � ����� ����. ��� ����� ����� �������, ���� ������� �� �������� ��������� ���� ���� � �������� ���������� ����. ����� �� ������ ������������� � �������� �� ����� ������� �����?";
			link.l1 = "���� ����, � ��� �� ������ ���������� �����.";
			link.l1.go = "Interception_6";
		break;
		case "Interception_6":
			dialog.text = "��������, �� �� ����� � ��������� � ���� ������� �������! � ���� ��� ����?!!";
			link.l1 = "�� ������� �� ���� ����� � ����� �����!..";
			link.l1.go = "Interception_7";
		break;
		case "Interception_7":
			dialog.text = "������, �������, ��������� �� ����������...";
			link.l1 = "������ � ����! � ������ ������ �����������. �����, ��� ��������� �������� � ������� �����-������ ������ ����� � ������, �� � ���� ������ ������ ����� �� ������� �����. � ���� ����� ������������, � ��� ����� ��� ���� ����� � ������ � ��������� ��� ������ ������� � ������ ��� �����! ������ ���� �������?";
			link.l1.go = "Interception_8";
		break;
		case "Interception_8":
			dialog.text = "�������. �� � �� ����� ���. �� ������� ������� �������� � �����, �������� �������� � ������, � �� ���� ��� �� ������ ������� �������! � � ������ ��������� ����� ��� ���������.";
			link.l1 = "� �� � �� ������ ������ ���������, ���� ��� ������� ����. ������ ��� � ������� ����� �����.";
			link.l1.go = "Interception_9";
		break;
		case "Interception_9":
			dialog.text = "�-��, � ��� � ���� �������� ������� ��������, ����������� ��� ���������... � ��� ������ ������? �����, ��������� ��������?";
			link.l1 = "� ������. ���� ������� ���������, � ������ ��������� ������ �� ���� ������ ����� ��������. ���� ����, ������, � ��� �� ��������?";
			link.l1.go = "Interception_10";
		break;
		case "Interception_10":
			dialog.text = "���, � �� ���� ������ �����. ������� �� �������� �� ����� ������.";
			link.l1 = "������... ������, ����� ����� �������, ��� ������� ������� ������, ��� ������ �������� ����� �������. ��-��, ���������� ��������� �������...";
			link.l1.go = "Interception_11";
		break;
		case "Interception_11":
			dialog.text = "�������� ��� �����?";
			link.l1 = "�������, ���� ����� �����! ��-��! �� ��� ��, � �����, ��� �� ������ ������� ��������.";
			link.l1.go = "Interception_12";
		break;
		case "Interception_12":
			dialog.text = "�������, ��� ����� ���������.";
			link.l1 = "�������. ����������� � ���� � ����� ���� �� ������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LCS_EndScriptInterception");
		break;

		case "BarmenDead_1":
			dialog.text = "������.";
			link.l1 = "� ������, ��� ������ ���� ��������� �������������.";
			link.l1.go = "BarmenDead_2";
		break;
		case "BarmenDead_2":
			dialog.text = "��, ������� �����. ����� ����, �� � ������ ������� �� ����� �������� � ������� ���-������ ������, ��� ������ ��� �� �����������? �� �������?";
			link.l1 = "�����, � �����!";
			link.l1.go = "BarmenDead_3";
		break;
		case "BarmenDead_3":
			dialog.text = "���, "+ GetSexPhrase("���� ���","�������") +", � ���, ��� �������. ������ �� ���� ��� � �� ���� ��� ����������... �� ���� �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "��, �� �����...";
			link.l1.go = "BarmenDead_4";
		break;
		case "BarmenDead_4":
			dialog.text = "������, ������ ��� ��������� ������� �������� ����-��, � ������� ����������� ��������.";
			link.l1 = "���, ������ �����"+ GetSexPhrase("","�") +". �������� � ��� ��, ���� � ���������. ��������� ���� � ����������� � ���� ���������?";
			link.l1.go = "BarmenDead_5";
		break;
		case "BarmenDead_5":
			dialog.text = "��� ���� ��. � ������, ��� �� ����� ������� ���� ������. �� ���, ������-�������� � ������ ����? ��� ��� ���������?";
			link.l1 = "�� ������ ����������. ������ �� �������� � ���...";
			link.l1.go = "BarmenDead_6";
		break;
		case "BarmenDead_6":
			dialog.text = "��� ���, �� � �� ���� � ��� ����. �� � ������ � ������ �����. �� ���� �� ���� �������, ������ �����������. �������?";
			link.l1 = "�������, �������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekOldCitizen";
			AddQuestRecord("ISS_MainLine", "27");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��", "��"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("��", "���"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("", "��"));
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1          = "location";
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_SaveSesilGalard.function                  = "LSC_SaveSesilGalard";
		break;
		//�������� ��������
		case "CasperDead_1":
			dialog.text = "����� ����������! ��, ������, ��� ��� �� '��� ��������' ���������?";
			link.l1 = "��, �������, �� �������, ����� � �������������� �����"+ GetSexPhrase("��","���") +" ��������� ����� ��������?";
			link.l1.go = "CasperDead_2";
		break;
		case "CasperDead_2":
			dialog.text = "� ����� �������? �� ���, ��������"+ GetSexPhrase("","�") +"?!";
			link.l1 = "��, �� ��� ��� �� �������, �� � �� ��������. ��� ��� �, � ������ ����������, ���"+ GetSexPhrase("��","��") +" ������ �����. ��, � ���"+ GetSexPhrase("��","��") +" �� '��� ��������'.";
			link.l1.go = "CasperDead_3";
		break;
		case "CasperDead_3":
			dialog.text = ""+ GetSexPhrase("�����","�� ��, ���� ������") +"! � ���, �� ������� ���� �� ����� ����?";
			link.l1 = "���, �� �������, ��� � ��� �� '��� ��������' ���� ������. � �� �� ����"+ GetSexPhrase("","�") +", ��� ������ ��� ����� �����������! � �����, ����������� ��� �� ����, �� � ��� �������� ����������...";
			link.l1.go = "CasperDead_4";
		break;
		case "CasperDead_4":
			dialog.text = "� ���?";
			link.l1 = "�������"+ GetSexPhrase("��","���") +". ����� '������' ����� �� ����������... ��� ��, �������, ��� � ����� '������'. ����� ������ �������� �� �������� ���� ������!";
			link.l1.go = "CasperDead_5";
		break;
		case "CasperDead_5":
			dialog.text = "�������� �� ����...";
			link.l1 = "����� ������? ����� ���������.";
			link.l1.go = "CasperDead_6";
		break;
		case "CasperDead_6":
			dialog.text = "�� �� "+ GetSexPhrase("������ �����-��","����� ���������") +"! ��� ����� ������"+ GetSexPhrase("","�") +" ��� ���!";
			link.l1 = "�������� ��������, ��� ���� �� ��� - �� ������ ������� ����������.";
			link.l1.go = "CasperDead_7";
		break;
		case "CasperDead_7":
			dialog.text = "�-��... ����-������ ���"+ GetSexPhrase("��","��") +" �� '��� ��������'? ����� '��������', �������.";
			link.l1 = "��. ������� �� ����� ������ ������� ��������� ���� ������.";
			link.l1.go = "CasperDead_8";
		break;
		case "CasperDead_8":
			dialog.text = "������, ������� ���...";
			link.l1 = "� ���� � ��� �����? �� �� �� ���� �� �������, �� � � ��� �� ������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "CasperDead_9";
		break;
		case "CasperDead_9":
			dialog.text = "��, �� ������"+ GetSexPhrase("","�") +"... ��� ���, "+ GetSexPhrase("'������ �����'","������ ��������") +"! �� ���� ������� ������"+ GetSexPhrase("","�") +" ������ ���������. � ������ ����� ��� �� ���� � ���������, �� ��������� �� ���� �� ��� � ������ �� ���!";
			link.l1 = ""+ GetSexPhrase("�������, � ������ ��� �� ����!..","� ������-�� ��������� ������ ����� ����������� ������������. '�������' - �����������, � �...") +"";
			link.l1.go = "CasperDead_10";
		break;
		case "CasperDead_10":
			dialog.text = "��������, "+ GetSexPhrase("���������","������ ��������") +"!\n�� ��� ���"+ GetSexPhrase("","�") +" ������ ������, ��� � ���� ��������� ��� ������ �������. ��� �� �� ��� � ���� �������, � �� ���� ����� ���������� �������������. ��������, ��� �� ���� �������� '�������', � �� ���� �������� �����. ���� ����?";
			link.l1 = "��, �������.";
			link.l1.go = "CasperDead_11";
		break;
		case "CasperDead_11":
			dialog.text = "������. �� ����"+ GetSexPhrase("��","��") +" ��������, ��� ������ � ������ ��� ����������. ������ ������ ���, �������������� ������ ��� ����������, �� ������� �� ���������������� ����� ������. ���� ����?";
			link.l1 = "��, �������.";
			link.l1.go = "CasperDead_12";
		break;
		case "CasperDead_12":
			dialog.text = "���� �� ��� ����-������ ���� ������� �������...";
			link.l1 = "�������, � ���� �����. ����� �� ����� ��� ������� - ��� ��� ����� ���������.";
			link.l1.go = "CasperDead_13";
		break;
		case "CasperDead_13":
			dialog.text = "��, ������ � ����!.. �������� �������, ����� �� ����� ���� �� '��� ��������' � ����� � ��������. ����� �������� �� ������ � ������ ����� ������ �������� - ����� ��� �� �������!\n����, � ����� ����-������ �� ������� ����� � ����. ������"+ GetSexPhrase("��","��") +".";
			link.l1 = "�������, �������! ������� �����, � �����"+ GetSexPhrase("","�") +" ��� �����...";
			link.l1.go = "CasperDead_14";
		break;
		case "CasperDead_14":
			dialog.text = "��������!!";
			link.l1 = "�� ��������, ���.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "seekMillionAndHalf";
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("���������. � ����� ������� ����?", 
				"�� ��� ���������"+ GetSexPhrase("","�") +" �� ����.", 
				"��� ���������"+ GetSexPhrase("","�") +"...",
                "�� ��� ���������"+ GetSexPhrase("","�") +" ���� �� ���� �������. ������ � �� ����!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� ����� � ������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "�����?";
			link.l1 = "�����, �������...";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "���� ����� � ��������� �� ����� �� �������! �� ������"+ GetSexPhrase("","�") +" ��������� ��������� ������ ������.";
			link.l1 = "� � ��������. � ������ ������ ��� � ������� ������ ������ ��� �����.";
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = "��� ������ � ����� � ����� ����������� �������� � ������. ��� ��������� � ���� �� ������ � ����������.";
			link.l1 = "�����, ����������?..";
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = "� ����� ��� �����? �� ��� ������, ����� ���� ���, �� ������ �� ���"+ GetSexPhrase("","�") +". � ����� �� ������ �������� ����-������ ������� � �������, � ����� ��������?";
			link.l1 = "�� �� ���, �������, � �� �� ���������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = "� ����� ������������ ������ � ������ ����� � ������. �� ������ �� ��������.";
			link.l1 = "����...";
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = "������, �� ����"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("��","��") +" ����� �������. ���� �� �� ��� ��������������, �����, ��� ������� �� ���� ��� ������, ��� ��������� ��� �������.";
			link.l1 = "� �� �� �����, ������ ����?";
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = "����� �� �� �����. � ��� �����, ��� ������� �� ��� � ��������� ��� � �����.";
			link.l1 = "� �� �����"+ GetSexPhrase("","�") +", �������...";
			link.l1.go = "SeekGoods_8";
		break;
		case "SeekGoods_8":
			dialog.text = "��? ���?";
			link.l1 = "�� ���.";
			link.l1.go = "SeekGoods_9";
		break;
		case "SeekGoods_9":
			dialog.text = "�-��... ��� ������ � ����� �������, ��� ���� �� ����� ���� ������ ��������� � ������. ������� � ��������� ������� ������ �� ���� �������.\n� �������� �� �����. ����, ��� ������ �� ��������� �������� ���������� - � �������� ���� �� '��������', � ������. �� ���� �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "�����"+ GetSexPhrase("","�") +", �������...";
			link.l1.go = "SeekGoods_10";
		break;
		case "SeekGoods_10":
			dialog.text = "� ������ ���, � ���� �� ����������.";
			link.l1 = "������, ���. �� ��� �� ���...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "57");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
			pchar.questTemp.LSC.additional.powder = true; //���� �� ���� ������ ������
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("� ���?", 
				"�� ��� �������� �� ����.", 
				"�� ���� ������ ������� �� ����!",
                "��������!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���� ��������� ��������, ��� ���� ����� ����� ����� �������. �������, ����� ����� �����������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"������-������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "�-��, ���-���� ����� � ���� �������...";
			link.l1 = "� � ��������� ������� ���, ���. � ��� ���� ���� �� �������� ����� � ����������, ������ ����� ������ ����, ��� ���� �����.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "���?!!";
			link.l1 = "���� ����� ������ ��������, ��� ����� �����. �� �������� ��������� �� ���! �� ����������� ����� ����� �����, �������� �� �������� ������ ������.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "��� �� ��� ����������� � ������! ������� - ������� ���������, �� ���� � �������. �� ����� ������� ������� ������, ��� ��� ������ ��� ������ ������. � ������� ���, ����� �� ������ ���� ����� ��� ����...";
			link.l1 = "� �� � ������... �������� ����, ���, ���� ���� �� �����, � ��������� ����...";
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = "� �� ������ ������?";
			link.l1 = "������ ������. � ���� ���� ������, ������� ������������� ������.";
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = "� ����� ����� �� �������� ������� ����������. ��� ���, "+ GetSexPhrase("��������","�������") +", � ���� �����. � ������� ���������� ��� ���������, ��� ��� � ������������ ���� � ��������� ���.\n���� � ����� �������, � � ���� ������, ����� �� ����� �� ������. �������?";
			link.l1 = "���, � �� ��������� ����� ���������. �� �����, ������ �����"+ GetSexPhrase("","�") +"... �� ������ ������ ����� � ����� � ������.";
			link.l1.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = "������ �����"+ GetSexPhrase("","�") +"? ��, � ��� � ����, ��� �� �� �����������...";
			link.l1 = "�������, �� �� � ��� �������. ����� ������� ���� �����, � ������ ����! ��� ���� ����� ��� � ��������� ����������������, ���� ������� ����.";
			link.l1.go = "SeekCrew_7";
		break;
		case "SeekCrew_7":
			dialog.text = "���, �� ��� ��� � ���� ������ ��������!\n��, ��� ��, ������� �� �������������� ������. � ������ ������ ���� ������"+ GetSexPhrase("��","��") +". � �� ������� ������ �������, � �� �� � ���� ����� �������! ����, ��� ������� ���� � ������ �� �������.";
			link.l1 = "�� ��� ��, � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +". ����, ��� �� �� �������� ����...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "60");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��", "���"));
		break;
		//��������� ������
		case "fightTalking":
			dialog.text = "���� ����� �����. �� �����"+ GetSexPhrase("","�") +" � ������?";
			link.l1 = "��.. ��, � ���-�� ���������� �� �������"+ GetSexPhrase("��","���") +"...";
			link.l1.go = "fightTalking_1";
		break;
		case "fightTalking_1":
			dialog.text = "� ���� ���� ���� ������.";
			link.l1 = "� ��� �������?";
			link.l1.go = "fightTalking_2";
		break;
		case "fightTalking_2":
			dialog.text = "�� ����������� �� �����������"+ GetSexPhrase("","�") +".";
			link.l1 = "��, ����...";
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_3":
			LAi_LocationFightDisable(loadedLocation, false);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorTypeNoGroup(NPChar);
			//LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuestFunction("LSC_figtInResidence");
            DialogExit();
		break;

		//���������� ���� ���� ������
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("� ���� ��� �� �����?", 
				"� ��� ��� ������.", 
				"����� ��, �� ��� ���������.",
                "�� � "+ GetSexPhrase("������","����") +" �� ��, "+ GetSexPhrase("��������","�������") +"!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��... ��, �����������.", 
				"��-��, � �����.",
                "�������.", 
				"� �����, "+ GetSexPhrase("������ ��� ���","���� ��� ��") +". ����� ���� � ���� ��������� - ���"+ GetSexPhrase("","�") +" �� �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "������ �� �����������. ��� �� ���� ����.";
			link.l1 = "��, � �� ��������� ������, ��� �������...";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "��� ���. � �� ���� ������ �������� �� ���� �������!";
			link.l1 = "������, �������, ��� �������.";
			link.l1.go = "exit";
		break;

		case "ELTHusb_SF":
			dialog.text = "��, ������ ��� ��������� ����...";
			link.l1 = "��, ����� � ���. ������ � ���� ������ ���������� ���.";
			link.l1.go = "ELTHusb_SF_1";
		break;		
		case "ELTHusb_SF_1":
			dialog.text = "���, "+ GetSexPhrase("��������","" + pchar.name + "") +", ����� �� ������! ������, �� ���� ����� ��� ���� �����. �� ������ � ����� ������.";
			link.l1 = "�� ���, ����� ��� �����?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "� ���� �� ��� �����!\n�� ���, �� ������ ������� ����������� ����.";
			link.l1 = "����, �� ��� �� �� ������ ������? �������, ��������, ����������.";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "������, ��������. ���� � �� �������, ����� ���� ��� �����.\n���� ������� ��������� � ����� ����� ��� � ���������� ���������� ��������� ��� �����, � ������.";
			link.l1 = "������, �� ��� ���� � ������ �� ������. �����, �� ������� � ��������� � �������� ���?";
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = "��� ��, �� ��� ����� �� ��������. �, ������, � �������� �� ���� ��� ����, ����. ������� � ������� ������ ������ � ������! ����������, ������� �� ��� ����������, ���� �� �������.";
			link.l1 = "��, � � ���� �����, ��� ��� ���� ��� ��� - ��� ��������� ����.";
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = "�� ���� ����������� ��, ��� �� ���� �� ������������ � ������ ����. � ����� ������, ����� ���������� ��������� �������, �� ����� ��������� �����-������ �������? � �����, ������� ����� ����������� �� ��������.";
			link.l1 = "����, ������, �� ����...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toWaitress";
			AddQuestRecord("ISS_ElisHusband", "7");
		break;

		case "ELTHusb_good":
			dialog.text = "�� ��� ������"+ GetSexPhrase("","�") +"...";
			link.l1 = "��������, ��� ���� ���� �������� ������� � ���� ��� ��������� �� �����.";
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = "��� ���?";
			link.l1 = "���. ���� ���� ������ ��� ���������� � ����� � ���������� �� ��������� �����.";
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = "�� ��� ��, ��� ��������� ������ ����\n�������, ��� ������� ��� ���� ���� ������������.";
			link.l1 = "�������, � ������, ��� ��� ����� ���������� �������.";
			link.l1.go = "ELTHusb_good_3";
		break;
		case "ELTHusb_good_3":
			dialog.text = "� �������� ����������� �� '��������' � ��������, � �� ������ ��������� ���� � ������� ��, ��� � �������� �������.";
			link.l1 = "�������! � ��� � ������. �������, �������...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toElisGood";
			AddQuestRecord("ISS_ElisHusband", "10");
			sld = characterFromId("MaximTailor");
			ChangeCharacterAddress(sld, "none", "");
		break;
		//����� �� �������� ��������
		case "LostDecster":
			dialog.text = "�� ������ ����?!";
			link.l1 = "������� ��������.";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "��... ��, ��� ��, ������� ���� ������.";
			link.l1 = "���� �� �����? ����� �� �����. � ��, �����, ���� ������...";
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = "�� ������, � ����� ����.\n������ ������� �������� ����� ������ ���������. �� ������� ������, ��� ����� ����������. ������� �� �������.";
			link.l1 = "��� ���, �������? ��� �� ������?";
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = "�� �������� ��� ������.";
			link.l1 = "� ��� ���������?";
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = "� ��������� ����\n� ������������ ���� �����������?";
			link.l1 = "��... ��, � ��������� ����.";
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = "������. � ������ �� ����������� ���. � ���� ��� ��������� � �������?";
			link.l1 = "�������, ������ ����������. �������� �����������, �� ����� ����. �������� �����, ���������� � ������...";
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = "�������. �� ������ ��������, ��, �������, �����"+ GetSexPhrase("","�") +", ��� �� �����. ������� ��� ��� ���������� ������ �� ������.";
			link.l1 = "������, �������, ��� �������. ������� �� ��������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "seekBox";
			AddQuestRecord("LSC_findDekster", "5");	
		break;

	}
}
