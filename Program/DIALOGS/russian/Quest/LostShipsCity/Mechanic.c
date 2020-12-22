
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	string sTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "������������! ��� �� � ���� "+ GetSexPhrase("��� �����, ��� �����","�� �������, ��� ������") +" ��������� �� ���?";
			link.l1 = "��, ��� � � ����.";
			link.l1.go = "FT_1";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!", "�������! ������!!! ����� "+ GetSexPhrase("���, �� �������","��, ��� ��������") +" �����!");
			link.l1 = "�-���, ������!!!";
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
			dialog.text = LinkRandPhrase("������, �� �� �����"+ GetSexPhrase("","�") +" ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� ��� ���������, ������� ���, ������ ������? ����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������") +"...");
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
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","��� ������") +" ����� ������ ���� � ������� �����������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		case "FT_1":
			dialog.text = "������, ����� ������... ������ �����, �������� ����, "+ GetSexPhrase("��� ����������� ����","���������� ��������") +".";
			link.l1 = "���� ����� ������� " + GetFullName(pchar) + ". � ��, ��������� � ���� ������, - ������ �������, �� �������� �������.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "�����!.. � ������ �� ���� ������?";
			link.l1 = "��, ����� �� �����������, ������ �������...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "���-����, � �� ��������. ���������, � ������ ����� ��� ����� ������� � ����������� ������. '�������' - � �� �� ���� ��������� �� ��������. ������, � ����� '������'. �� ���, �� ���� �������?";
			link.l1 = "���� �� �������. � �� ����� � ������"+ GetSexPhrase("","�") +" ��� ��� ��� � ���� '������'.";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "��-��, ��� ����� ������ ����� �����������? �-��, ������ �����, ��� ���������\n��, � ������ ���������� ���, ����������, ���� ���� �� ��������� ��� ������������ �������.";
			link.l1 = "��� ��� �������... ���������, � �� ����������� ���������� �����"+ GetSexPhrase("","�") +" �� ���� ������, ��������� ������ ������ ����. �� � ������ ���� �������� ������.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "������ ����? �� ����� ������?";
			link.l1 = "����������� ����� �� ��������, �� ���� �������, ��� �� ������������ �������� �� ������� �����. � ���������, ��� ����� ������ ����������� ����-������� ��������.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "����. �� ������, � ���� ��� � �������� ��� ����, �� ������� �� ���� ������ � �����.";
			link.l1 = "��?! � ��� �� �� �� ��� �������� ����� '��������'?";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "�� ����� ������ �� '�������� ���������'. � ���� �� ����� �������� � ��� � ���� �� ���������, ������� ����������...";
			link.l1 = "����������?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "��... ����� �������. ��� ���, �� �������������, ����������, � � ������ ���, ����� �� ����� ������ � ��������� ����� �� ���� �������.";
			link.l1 = "���� �� � �������� �� ����, �� ������ �������� � ������ ����� �������� ��� ������. ����������� ����-������� �������� ��������, ��� � ������ ������������� �������� ���������, � �� ������ ��������� �� ����� ����� �� �������� ����. � ���� ������ ��������� ������� � ������ ��������.";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "����. ������, ����� ���-���� ������� ������ ��� �������� �� �����, ���� �������� �� ������ ����� �����. ���� ������, ��� ����, ��� �� �����!";
			link.l1 = "����, �������. �� ������, ������� ������� ����� ������ �� ��������� �����, ��� � ��� �����"+ GetSexPhrase("","�") +" ������...";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "��, �� ����� � ��������. �� ������, ��� ���� ����������� �������� ����� ������ ��������� ������. ��� ���� ������ ���. � ��� ������ - ��� �����...";
			link.l1 = "��������? � ������ �� ������?";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "����� ������������ �������... �� �����, ���, ����� ��, �����. ������ ���������� ���, "+ GetSexPhrase("���� ���","����� �������") +", ��� �������� � ������ � ����� �� ������ �� ���.";
			link.l1 = "� ������ ����������� ������� ��� ������. �������� ������ ����� �������� ���������� ������, ���� �� ������� ��������� ������� ����� ������������ ��������. ��, � � �������� �����"+ GetSexPhrase("","�") +" � �������� � �����"+ GetSexPhrase("","�") +" ������������ � ���� ����� �����. ���, ����������, � ���...";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "��� ������ ������ ������ ������ ��������� �������, ��� � ������...";
			link.l1 = "��, � �� �� ������"+ GetSexPhrase("","�") +", ��� ������. ��� ����� ���������� ���� �� ������, ���������� �������� �������. ���� ���������� ��������� � ��� ��������, ���� ��� � �� ����������� ������ ����������� ������������!";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "�� ������, "+ GetSexPhrase("���� ���","�������") +", � ���������� �� ��������, ���� ��������, ��� �� ���� ������������ � ������ ��� ��� ����� ����� �������.";
			link.l1 = "��, �� ������. ������ � ���� ���� ����. � �������������� ����� - ���������� ����� '������' �� ����� '��� ��������'.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "��, '�������' ����������� � ������ � ��������, ������� �������� � ���� �����������... �� ��� ��, ��������� ��� ����� � ������ �������� ����������...";
			link.l1 = "�����! � ������ � ��������� �������� ������ ��������. ���� ��������� ���� ����������� �� ��� ���������.";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "����� ������, "+ GetSexPhrase("���� ���","�������") +"! ����� ������� ���� �����, ���� ��� �� ������...";
			link.l1 = "� ��� ��� ��?";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "�� ������, ������ ���� ����� ���������?";
			link.l1 = "����. �� ��������� ������ ��������� �������� ������ ����� �����. �� � ������, ��������� � ������"+ GetSexPhrase("","�") +", ���������� ���-������ ������ ��� ��� �� ��������.";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "������. ��, ��������, ���������, ��� � ���� � ������ ������, ��� ����� ������ ������. � ���� ��, ������ � �� ����� �������������, � ������ ��� ��������� �����, ��� ��� ������ �������� ������ ���������� �������� ��� �����.";
			link.l1 = "��� �����?";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = "��. ��������� ��� ����� � ��������� ������ ��� ������� ��� �����. � ���� ������� � ��������� ��� ���� ����� ���, ���� ���� ����� �����������. � ��� ��� � ��� ����� - ����� ��������� ����� �������� ������� �����.";
			link.l1 = "��������� � ����, ������ ����� �� ��������...";
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = "���, � �� ����! �� ������� �� ����, ��� ������ ����� � ������!";
			link.l1 = "������-������... ��� ��� �� ��� �������� ��� ������� ��� �����?";
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = "� ��������� ��� ����, ������ ����. ��� ���, ����� �������� ����� �� ���� ��������, ������� ���������� �� ����. ��������� ������� �������� �������� � ����� �����! ���������, ��� ��� ������?";
			link.l1 = "�-��, ��������� ��� ����������... � ��� �����, ���� ����� ���������? �� ����� � �����?";
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = "������ ���������! �� ������ �� ���, ���� ������� ������ �� �� �����. �� ������� �����, ��� ��� ���������� ������ ����� ����������� � �����, ������ ����� ������� �����.";
			link.l1 = "����������� �����-��... � ����� ��� ����������?";
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = "�� ����. � ������, � �� ������\n� ������, ��� ����� ��������� � ����� ����.";
			link.l1 = "��... � ��� ������?";
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = "� ���� ������ ���, ���� �� �������� ���.";
			link.l1 = "���������� �����������. ���������� ���������, ����������.";
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = "���� � ���, ��� � ���� ���� ������� �� �����. ���� ��� ����� � ������ ������� ������ � ��������� ��������� � �����, � � ����� ��� ��������. ���� � ���� ���� ����� �����������...";
			link.l1 = "�� ��� ��������� ��� ���������� � �����-�� ��������� �����������...";
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = "�-�, �� ��� ����������� ���������� ��� ���� � ���� �������. ���� � ���, ��� ��� ����� �������� ����������� �����, ������� ����� �� ��� � ���� ���, ��� ������. ��� � � �� ������ ������ ����������. � ���� ������, � �� ����...";
			link.l1 = "�������. ��� ��� � ����"+ GetSexPhrase("��","��") +" �������?";
			link.l1.go = "FT_26";
		break;
		case "FT_26":
			dialog.text = "������� �� ������ ������ � ���� ������. ����� ������� �� ��� ���-���, ��� ���� �� �� ������ ���������� ������ �� ������������ ��� ��������.";
			link.l1 = "������?! ��, � �� ���, �� �������������� ���� ������ � ������ ���� �����? ���� � ������ ������������� ���� ������������, ��������� � �� ����!";
			link.l1.go = "FT_27";
		break;
		case "FT_27":
			dialog.text = "��, � �� �� ���� �����, ����� �������� ����������. � ���� ��, � ����, ��� �� "+ GetSexPhrase("������� ������ � ����������","������� ������ � ����������") +", � ��� ������ �� ����� ����� ��������� ��� �������. ��� �����, ��� � ����� �� �����, ����� ���� ������� �������� �� ������ � ����������� ���� ��� ���������� ��� ����.";
			link.l1 = "������� ��������?! � �� �������"+ GetSexPhrase("��","���") +"?";
			link.l1.go = "FT_28";
		break;
		case "FT_28":
			dialog.text = "���, ��� �����.";
			link.l1 = "�� � ���� ��� ����� �����!";
			link.l1.go = "FT_29";
		break;
		case "FT_29":
			dialog.text = "��, ������ ����� �� ��������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". �����, �, �������, ��� ����� ������� ������ ��� �����, ��� ��� ����� ��������� �������� ����������. � ���� ��, ����� ������ � ������� ������, �� ������ ���� � ���� �� �������� �����.";
			link.l1 = "���, ��� ���� ����� ������ ����� ���������... �������, ��� �� ������������.";
			link.l1.go = "FT_30";
		break;
		case "FT_30":
			dialog.text = "�� ���, � �� ���� ��. ����������, � ������, ���������� ��� �����... �� � ������, � ��� ��� ����������� ���������� �� ����, � ��� ����� ��� ������!";
			link.l1 = "��, �� ��� �� � �����-�� ����� �������!";
			link.l1.go = "FT_30_1";
		break;
		case "FT_30_1":
			dialog.text = "�� �� �� ���������� � '���������', ���������� � � ���� ���������... ��, ��� �� �� �������?! ��� ����� ��� �� �� ������ ��� �������� ����� ���� �����������...";
			link.l1 = "������, � ������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "FT_31";
		break;
		case "FT_31":
			dialog.text = "��, ��� � �������! ��� ��� � ��������, "+ GetSexPhrase("���� ���","����") +", � ��� ������ ������ ������. ������ ��� ����� ������� � ���� �������, ���������� ���, ��� � �����������, ��� �������... ������ ������� �������! ����� �� ����� ���.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ��� ������ ���� �� �����.";
			link.l1.go = "FT_32";
		break;
		case "FT_32":
			dialog.text = "��� ������ �� ���������, ��� � ���... � �����, ����������� ���� �� ���� ������, ��������� ��� �� ����������� '��������'. �� �����, ��� ��� ��� ��������, �� ������� ��� �����.";
			link.l1 = "�����?";
			link.l1.go = "FT_33";
		break;
		case "FT_33":
			dialog.text = "�� �� �� ��� ����� ������, ���� ��� �� �����. ������, ������ �� ���� ��������� ��� �� ���� ��������� ���������, ��� �������. � ����� ����� ����� ���� ����� ���������, �����...";
			link.l1 = "��� �����?";
			link.l1.go = "FT_34";
		break;
		case "FT_34":
			dialog.text = "����� �� ��������� ���, "+ GetSexPhrase("���� ���","�������") +". �� ����� ����� ��������, � �� ��� �������. ��� ���� ���� � '���������', � � ������ � ����������, ��� �� ��������� ������ � ���� �� ������.";
			link.l1 = "���������... � ������ �� ��������� �� �������?";
			link.l1.go = "FT_35";
		break;
		case "FT_35":
			dialog.text = "����� ����� �� ����� � ������ ������ ����������� ����� �����.";
			link.l1 = "�������... �� ��� ��, � ��� �����"+ GetSexPhrase("","�") +". ���"+ GetSexPhrase("��","��") +" ���������� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CheckMillion";
			pchar.questTemp.LSC = "fromMechanicToAdmiral";
			Npchar.quest.money = 0; //������� �����, ��������� ��������
			AddQuestRecord("ISS_MainLine", "40");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��", "���"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "�"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("��", "��"));
		break;

		//�������� ��������
		case "CheckMillion":
			dialog.text = "�� ���, ��� ��� ���� � ����� ��������?";
			if (sti(pchar.money) < 20000)
			{
				link.l1 = "���� �� ���������"+ GetSexPhrase("","�") +" ����������� ������.";
				link.l1.go = "CheckMillion_noMoney";
			}
			else
			{
				link.l1 = "���-��� �������. � �����"+ GetSexPhrase("","�") +" ������� ��� ��������� �����.";
				link.l1.go = "OffM_GiveMoney";
			}
			NextDiag.TempNode = "CheckMillion";
		break;
		case "CheckMillion_noMoney":
			dialog.text = "�� ��� ��, ����������, � �����, ��� ��� � ��� ���������.";
			link.l1 = "� ���� ��� �����.";
			link.l1.go = "exit";
		break;
		case "OffM_GiveMoney":
			dialog.text = "�������?";
			link.l1 = "";
			Link.l1.edit = 6;
			link.l1.go = "OffM_GiveMoney_1";			
		break;
		case "OffM_GiveMoney_1":
			iTemp = sti(dialogEditStrings[6]);
			if (iTemp <= 0)
			{
				dialog.text = "������ ��������?";
				link.l1 = "��, ��������, �������� �����..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "��, ����� ����� � ��� ��� ���� ���, � ���������. ������� ��� ���������...";
				link.l1 = "��... ������.";
				link.l1.go = "exit";
				break;
			}
			Npchar.quest.money = sti(Npchar.quest.money) + iTemp;
			AddMoneyToCharacter(pchar, -iTemp);
			if (sti(Npchar.quest.money) < 1500000)
			{
				dialog.text = "�� ��� ��, �������! ������ �� ������ ��� " + FindRussianMoneyString(iTemp) + ", ����� �� �������� ��� " + FindRussianMoneyString(sti(Npchar.quest.money)) + ". ��� �������� ��������� ��� " + FindRussianMoneyString(1500000 - sti(Npchar.quest.money)) + ".";
				link.l1 = "�������� ������.";
				link.l1.go = "exit";
				AddQuestRecord("ISS_MainLine", "41");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("ISS_MainLine", "iMoney1", sti(Npchar.quest.money));
				AddQuestUserData("ISS_MainLine", "iMoney2", 1500000 - sti(Npchar.quest.money));
			}
			else
			{
				dialog.text = "�� ��� ��, ���� �������. � ������� ��������� �����, ������ ������ ���.";
				link.l1 = "����� ������. ��� ������?";
				link.l1.go = "FreeCorvett";
			}
		break;
		//����������� �������
		case "FreeCorvett":
			dialog.text = "������ ������ ����� ����������. ���� � ���, ��� �� ��������� �� ������� ������ ������������ ����� ������� � ������� ��������� �� ���� ������.";
			link.l1 = "�� � ��� ��� �������?";
			link.l1.go = "FreeCorvett_1";
		break;
		case "FreeCorvett_1":
			dialog.text = "� ��� ��� ����������. � ���� �� ��������� ����� �������, � ��� � ��������� ������� ������ �������. ��� ��� ����� ������ �������� �������� � �������� - � �����, ������ ��������!";
			link.l1 = "������ ���������. � � ��� ������?";
			link.l1.go = "FreeCorvett_2";
		break;
		case "FreeCorvett_2":
			dialog.text = "��, ������ ������������� �������. � ������ ���������� �� ��������� ������� � ����. ��� ���������� ����� ������� �� ���.";
			link.l1 = "��-��... ���� ��� �� �������� ������, �� ��������, ��� � ��� ���� ������ ��� ������� ��� �����. � ��� ��� � ��������� ����������� ����� �� ���?";
			link.l1.go = "FreeCorvett_3";
		break;
		case "FreeCorvett_3":
			dialog.text = "��, ������ ���. � �� � ��� ����� ��� ������, �� ����� �����. ��� ��� ����������� �����!..";
			link.l1 = "� �� �� ������?";
			link.l1.go = "FreeCorvett_4";
		break;
		case "FreeCorvett_4":
			dialog.text = "�����, �, ���������� ������, ��������� �� ������... ��� ��� �������� �� ���������. � ������, ���, �������, ������ �������������, ��� ��� ������� ���������� ��� ����������� ���������.";
			link.l1 = "��, ����� ��� ����������? ������ �� ������, ��� ��� ����������?";
			link.l1.go = "FreeCorvett_5";
		break;
		case "FreeCorvett_5":
			dialog.text = "��� ��� ����� ���, ��� ������������ �� ���� �������� ������! ��� ������������ �������, �� ������� ��� ����� ����� �����.";
			link.l1 = "�������... �� ��� ��, � �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "FreeCorvett_6";
		break;
		case "FreeCorvett_6":
			dialog.text = "����, ������� � ��������, ��� ������������ ��������. ������ ������������ ������ ��������, ������� �� � ������. ������� ������� �� 6 ����� ������������� ������� ��� �����. �� ��� ����� �� ������ ������ ������� �� �����������. ���� ����� �� ���������� - ��� �����. ��� �������?";
			link.l1 = "�������, ��� � ���������"+ GetSexPhrase("","�") +" �� ������� ���������� ��� �����. ��������� ���������.";
			link.l1.go = "FreeCorvett_7";
		break;
		case "FreeCorvett_7":
			dialog.text = "� ��� �������, ��� ��� ����� �������. ������ �� ������ ���� �� ���������, ������ ��������� ���, ��������� �������� �� ���� ����������. �������, �� ����������� ��� �����, ��� ��� ������. �������, ��� ����������� ����� ������ ����, � ������ �� ������������ �����. ����� ������������� ��������� ������ ���� ��, ��� �����. ����� ��� � ��������� ����!";
			link.l1 = "�������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor";
			pchar.questTemp.LSC = "toUnderwater";
			pchar.questTemp.LSC.immersions = 0; //���������� ����������� ����������
			pchar.questTemp.LSC.immersions.model = pchar.model; //�������� �������� ��
			pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
			pchar.questTemp.LSC.immersions.pay = true; //��������
			pchar.questTemp.LSC.immersions.pinion = false; //���� ��������� ����������
			AddQuestRecord("ISS_MainLine", "42");
			pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, false, pchar);
			SetBaseShipData(pchar);
			pchar.Ship.name = "ϸ� �����";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCharacterGoods(pchar, GOOD_BALLS, 0);
			SetCharacterGoods(pchar, GOOD_GRAPES, 0);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
			SetCharacterGoods(pchar, GOOD_BOMBS, 0);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 0);
			SetCharacterGoods(pchar, GOOD_PLANKS, 0);
			SetCharacterGoods(pchar, GOOD_POWDER, 0);
			SetCharacterGoods(pchar, GOOD_FOOD, 0);
			SetCharacterGoods(pchar, GOOD_WEAPON, 0);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 0);
			SetCrewQuantity(pchar, 0);
			AddSimpleRumourCityTip("�� ������, � ������ �������� ����� �������. � �������, ��� �� ��������� ������! ���� ��...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("�� ������� � ������� ��������? ��� ��� ����! �����������, ��� ������� �������� �� '��� ��������' ����� ���.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("�������, ��� �����-������ ������ ������, ����� ������ �������, ����� ��������� �������.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("� � �� ����, ��� ���� ������� ��� ����� ��� ������. ������� ���� ��� ����, �������� � ���...", "LostShipsCity", 10, 1, "LSC", "");		
			// ����� �������� � �����
			ref loc;
			int n;
			if (Pchar.SystemInfo.CabinType != "")
			{
				loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

				for (n = 1; n <= 4; n++)
				{
					sTemp = "box" + n;
					DeleteAttribute(loc, sTemp + ".items");
					loc.(sTemp).items = "";
					loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
					loc.(sTemp).money = 0;
				}
			}
			loc = &locations[FindLocation("My_Deck")];
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}	
		break;
		//
		case "takeArmor":
			dialog.text = "��, ��� � ��� ����?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "��������� � ����������. ����� ������, ��� ��� ������.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "��� ����� ��� ��� ���������� �� ���. �� �����"+ GetSexPhrase("","�") +" ������� ��� ���, ��� �����"+ GetSexPhrase("","�") +".";
				link.l1.go = "DeepAgain";			
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "� ���"+ GetSexPhrase("��","��") +" ����������, ��� ���!";
					link.l2.go = "FoundPinion";
				}
			}
		break;

		case "DeepAgain":
			dialog.text = "� �� ������, ������ ������ � ����� ������������. ������ �� ������ ���������� � �������� � ��� ����� 30 ����� ��������. ��� ��� ������ �� �����.";
			link.l1 = "����� ������ �����? � �� ������"+ GetSexPhrase("","��") +" ��� ������� ��������!";
			link.l1.go = "DeepAgain_1";
		break;
		case "DeepAgain_1":
			dialog.text = "��� ������ - ����� �� ������ � �� ���� ����������. � �� ������ ��� ������� ������, �� �������� � ����. � ���� ��� ��� � ������. ����������� � ��� ����...";
			link.l1 = "����� �����������?";
			link.l1.go = "DeepAgain_2";
		break;
		case "DeepAgain_2":
			dialog.text = "����� ������������, �� �� ���� �� �����? � �����, ������� ����������. �������� ����� - � �� ������������ � �������� ������� �� �������. ��� ����� - ��� ����������.";
			link.l1 = "�-��, �������...";
			link.l1.go = "DeepAgain_3";
		break;
		case "DeepAgain_3":
			dialog.text = "� �� �������, �� ��� �� ���������. � ��� ��� ����������� ���������� ������� ������. ���� �� ��� ����� ����� ���������. ���� �� ���� �� �������� ����������, �� �������� ����... � �����, ����� ���� ����� ���������"+ GetSexPhrase("��","��") +" ���, �� ���.";
			link.l1 = "����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "takeArmor2":
			dialog.text = "��, ��� ��� ����?";
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = "��������� � ������ ��� ���������� ����������.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "� ���� ��� ��� ���������� �� ���.";
				link.l1.go = "DeepAgain2";			
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = "� ���"+ GetSexPhrase("��","��") +" ����������, ��� ���!";
					link.l2.go = "FoundPinion";
				}
			}
			if (sti(pchar.questTemp.LSC.immersions.pinion))
			{
				link.l3 = "���, � ��������"+ GetSexPhrase("","�") +" � ������������. ����� ��������� ������� ���� �� ����������.";
				link.l3.go = "endImmersion";
			}
		break;

		case "DeepAgain2":
			dialog.text = "����������� ������?";
			if (sti(pchar.money) >= 30000)
			{
				link.l1 = "��, �����"+ GetSexPhrase("","�") +" ���������.";
				link.l1.go = "DeepAgain2_1";
			}
			else
			{
				link.l1 = "��� ���... �� � �� ��������� �����������.";
				link.l1.go = "exit";
			}
		break;
		case "DeepAgain2_1":
			dialog.text = "�������! ��������� ������, � ���������� ������ � ������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -30000);
			SaveCurrentQuestDateParam("questTemp.LSC.immersions");
			NextDiag.TempNode = "readyArmor";
		break;
		case "readyArmor":
			if (GetQuestPastDayParam("questTemp.LSC.immersions") > 1)
			{
				dialog.text = "��� � �������, ������ �������� � ��������� ��������. � �����, ��� ������ � ����������. ����� �����.";
				link.l1 = "�������.";
				link.l1.go = "exit";
				pchar.questTemp.LSC.immersions.pay = true; //��������
				NextDiag.TempNode = "takeArmor2";
			}
			else
			{
				dialog.text = "������ �� ����� � ������. ��������� ������.";
				link.l1 = "������.";
				link.l1.go = "exit";
			}
		break;

		case "FoundPinion":
			dialog.text = "�����������! ������� �� �������...";
			link.l1 = "��, �������.";
			link.l1.go = "FoundPinion_1";
		break;
		case "FoundPinion_1":
			dialog.text = "�� ��� ��, ������ � ���� �������� ��������������� ��������� �������. �������, �� ��� ������ ��������� ����������?";
			link.l1 = "��, ���� ����� �������� ����������� ���.";
			link.l1.go = "FoundPinion_deep";
			link.l2 = "���, ��������� ������� ���� ����� �� ����������.";
			link.l2.go = "endImmersion";
			TakeItemFromCharacter(pchar, "Pinion");
			pchar.questTemp.LSC.immersions.pinion = true; //����� ����������
			AddQuestRecord("ISS_MainLine", "44");
		break;
		case "FoundPinion_deep":
			dialog.text = "�� ��� ��, ������� �����. ��� ������� �� ������ - 30 ����� ����� �� ������ ����������. ��������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "endImmersion":
			dialog.text = "�� ��� ��, ��� �������. ����� � ����������� ������.";
			link.l1 = "��� ������.";
			link.l1.go = "endImmersion_1";
		break;
		case "endImmersion_1":
			dialog.text = "������, ����� � ���� ���� ��� �����������, � ������� ��������������� ��������� �������, ������� ��������� ��� ������. ��� ������ � ���� ������������ �����. ��� �� ���� �� ������� �������� �� ������, � ����� �������� ��� ������ ���������������� �����������.";
			link.l1 = "��� �� ������ � ����?";
			link.l1.go = "endImmersion_2";
		break;
		case "endImmersion_2":
			dialog.text = "��� ������ ���������� ������� ���� �����������. ���� ����� �����������, ��������������, ������... ��, �� ��� ��� �����. ��� ��������� ����������� �� '��� ��������', � ����������� ����� ����� �� ������ � ������� ���.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ���������� ��� �������.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.immersions");
			AddQuestRecord("ISS_MainLine", "45");
			pchar.questTemp.LSC = "toSeekGoods";
			NextDiag.TempNode = "takeGoods";
		break;
		//�������������� ������� ��������
		case "takeGoods":
			NextDiag.TempNode = "takeGoods";
			dialog.text = "�����������. ��, ��� ���� � ����������� ����� �������?";
			npchar.quest.LSC.Balls = false;
			npchar.quest.LSC.Grapes = false;
			npchar.quest.LSC.Knippels = false;
			npchar.quest.LSC.Bombs = false;
			npchar.quest.LSC.Sailcloth = false; //�������
			npchar.quest.LSC.Planks = false; //�������
			npchar.quest.LSC.Powder = false;
			npchar.quest.LSC.Food = false; //�������
			npchar.quest.LSC.Weapon = false;
			npchar.quest.LSC.Medicament = false;
			iTemp = 0;
			npchar.quest.LSC.s0 = "";
			npchar.quest.LSC.s1 = "";
			if (GetCargoGoods(pchar , GOOD_BALLS) >= 100) 
			{
				npchar.quest.LSC.Balls = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Balls;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ����,";
			if (GetCargoGoods(pchar , GOOD_GRAPES) >= 100) 
			{
				npchar.quest.LSC.Grapes = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Grapes;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " �������,";
			if (GetCargoGoods(pchar , GOOD_KNIPPELS) >= 100) 
			{
				npchar.quest.LSC.Knippels = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Knippels;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ��������,";
			if (GetCargoGoods(pchar , GOOD_BOMBS) >= 100) 
			{
				npchar.quest.LSC.Bombs = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Bombs;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " �����,";
			if (GetCargoGoods(pchar , GOOD_SAILCLOTH) >= 50) 
			{
				npchar.quest.LSC.Sailcloth = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Sailcloth;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ��������,";
			if (GetCargoGoods(pchar , GOOD_PLANKS) >= 50) 
			{
				npchar.quest.LSC.Planks = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Planks;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " �����,";
			if (GetCargoGoods(pchar , GOOD_POWDER) >= 200) 
			{
				npchar.quest.LSC.Powder = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Powder;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " �����,";
			if (GetCargoGoods(pchar , GOOD_FOOD) >= 200) 
			{
				npchar.quest.LSC.Food = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Food;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ��������,";
			if (GetCargoGoods(pchar , GOOD_WEAPON) >= 50) 
			{
				npchar.quest.LSC.Weapon = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Weapon;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " ������,";
			if (GetCargoGoods(pchar , GOOD_MEDICAMENT) >= 50) 
			{
				npchar.quest.LSC.Medicament = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Medicament;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + " �����������,";
			if (iTemp < 10)
			{
				if (iTemp == 0)
				{
					link.l1 = "���� ������ �� ��������"+ GetSexPhrase("","�") +", �� � ��������.";			
				}
				else
				{
					sTemp = npchar.quest.LSC.s0;
					npchar.quest.LSC.s0 = strcut(sTemp, 0, (strlen(sTemp)-2));
					sTemp = npchar.quest.LSC.s1;
					npchar.quest.LSC.s1 = strcut(sTemp, 0, (strlen(sTemp)-2));
					link.l1 = "���-��� ��� ����. ������� ������� " + npchar.quest.LSC.s1 + ". �������� ��������� " + npchar.quest.LSC.s0 + ".";
				}
				link.l1.go = "takeGoods_again";
			}
			else
			{
				link.l1 = "���, ��� ����� ��� ��������, � ���� � �����.";
				link.l1.go = "TakeCrew";
				DeleteAttribute(pchar, "questTemp.LSC.Balls");
				DeleteAttribute(pchar, "questTemp.LSC.Grapes");
				DeleteAttribute(pchar, "questTemp.LSC.Knippels");
				DeleteAttribute(pchar, "questTemp.LSC.Bombs");
				DeleteAttribute(pchar, "questTemp.LSC.Sailcloth");
				DeleteAttribute(pchar, "questTemp.LSC.Planks");
				DeleteAttribute(pchar, "questTemp.LSC.Powder");
				DeleteAttribute(pchar, "questTemp.LSC.Food");
				DeleteAttribute(pchar, "questTemp.LSC.Weapon");
				DeleteAttribute(pchar, "questTemp.LSC.Medicament");
				DeleteAttribute(pchar, "questTemp.LSC.additional");
			}
		break;
		case "takeGoods_again":
			dialog.text = "�� ��� ��, �������. � ������������ �� ������ � ���� �����.";
			link.l1 = "��� � ���� ���������.";
			link.l1.go = "exit";
		break;
		//����� �������
		case "TakeCrew":
			dialog.text = "���������, "+ GetSexPhrase("���� ���","������� ���") +", ��� ��� ��������� � ����� ������ �������. ������ ��� ����� ������� ������� �� ������� ������. ���� ���������, ������ �� � �������� �� ���������.";
			link.l1 = "���, � ������ ������ ���� �� ���� �������? � �������"+ GetSexPhrase("","�") +" ���� ����� � ������� ������� �� ������, ������ ���"+ GetSexPhrase("","��") +" �� � ������� �������.";
			link.l1.go = "TakeCrew_1";
		break;
		case "TakeCrew_1":
			dialog.text = "��, ��-������, ���� �� �� ��� ����������� ��������. � ��-������, � �� �����-�� � ���������. �� ������ ���� ��������� ����� ��������� ������.";
			link.l1 = "��� �� ������ � ����?";
			link.l1.go = "TakeCrew_2";
		break;
		case "TakeCrew_2":
			dialog.text = "������ ��, � ������� ��� ��� ���� ��������� ��� ����, ��� �������� �����, ��� ����� � ��������� ��� �����������. �� ��� ����� � ��������� ������, ������� ���������� ����������� �������. � ��� ������ '����������'! �������������, ������ ��, �����...";
			link.l1 = "��� � ���, ��� �� �������... ���, ��� ��� ������ ���������� ������� ���?";
			link.l1.go = "TakeCrew_3";
		break;
		case "TakeCrew_3":
			dialog.text = "�-�, �� ��... ��� ���, ��� ���������� ����������, ��� �� ����� �������� �� ������ �����, � ��������� ����. ���� �� ����, ����� ���� - ������ �����������.";
			link.l1 = "����������, ��� ����� ������?";
			link.l1.go = "TakeCrew_4";
		break;
		case "TakeCrew_4":
			dialog.text = "������ ���, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". � ���� ������� � ����� ������� ����� �����������, ��� ������ ����� ����� ��������. ��� ��� ������������.";
			link.l1 = "������, � ��� � ������. ������, �� ������ ���������� ������?";
			link.l1.go = "TakeCrew_5";
		break;
		case "TakeCrew_5":
			dialog.text = "��� ���, �� ��������� �������, ��� � ������ ����������. ��������������� � ������, ����� ��� ��������� ����, � � ���� ������������ �� �� �������. ��� ����� ���� �� ���������� �������, ����� �������. ��� ������ �� �������� ����������� ���������� - ����� �� ������ ����. �� ������ �������� �� '��� ��������', �� ����������� ������� � ��������� ������.";
			link.l1 = "������, � ��� �����"+ GetSexPhrase("","�") +". ����� ��������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TakeCrewNew";
			AddQuestRecord("ISS_MainLine", "59");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","��"));
			pchar.questTemp.LSC = "toSeekPeopleInCrew";
			pchar.questTemp.LSC.crew = 0; //���������� ����������� �����.
			AddDialogExitQuestFunction("LSC_SmallStormIsBegin");
		break;
		//����� ������ � �������
		case "TakeCrewNew":
			if (sti(pchar.questTemp.LSC.crew) > 0)
			{
				dialog.text = "�� ��� �� ������� ������������ ���������� ����� ��� ��������. ����� �� ��� ������� " + FindRussianPeoplesString(sti(pchar.questTemp.LSC.crew), "Acc") + ". �����������, � ����� ��� - �������...";
			}
			else
			{
				dialog.text = "�� ��� ������ �� ��������� ����� � ��� � �������. ������������!";
			}
			link.l1 = "������.";
			link.l1.go = "exit";
		break;
		//�������� � ������
		case "inPrison":
			dialog.text = "���, ��� � ��!";
			link.l1 = "�����! ����"+ GetSexPhrase("��","��") +" �� �������.";
			link.l1.go = "inPrison_1";
		break;
		case "inPrison_1":
			dialog.text = "�� ��� ��, �������, �� ������... ������ ��� ���.";
			link.l1 = "��� ������?";
			link.l1.go = "inPrison_2";
		break;
		case "inPrison_2":
			dialog.text = "� ������ � ���� ������, � ���� �������� ������ ��������. ��� ��� ��� ������ ���������� ������. ��� �� ��������� �� ���� ������.";
			link.l1 = "�������� ������ ���, � ��������"+ GetSexPhrase("��","���") +" � ���. �� �������� ����� �� �������"+ GetSexPhrase("","�") +"... � ������� � �����!";
			link.l1.go = "inPrison_3";
			if (CheckCharacterItem(pchar, "key_mechanic"))
			{
				link.l2 = "�������� ������ ���, � ��������"+ GetSexPhrase("��","���") +" � ���. ��� �� ��� ��� ���� ����. ���?";
				link.l2.go = "inPrison_3_alt";
			}
		break;
		case "inPrison_3":
			dialog.text = "������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". ���� �������� ����.";
			link.l1 = "� �����!";
			link.l1.go = "inPrison_4";
		break;
		case "inPrison_4":
			dialog.text = "���, ��� ���� ��. �� � �� ����� ��������� �������� � ������� �������� �����, ��� ��� ��������� �� ���. ��������, ��� ��� ����� �������...";
			link.l1 = "������, � ����� � �������� ���.";
			link.l1.go = "inPrison_5";
		break;
		case "inPrison_5":
			dialog.text = "� �����, ��� �������. �������, ��� ���������, ������, ������������ ����� ������. ������� ���� ��� ������� - ������ ������������ ������� ���������� � ����� ����� ���������.\n� ���� ��, ��������, � ��������, � ����� ������ ����� �������� ������. ����� ���������� ����� ������ ����� �����, ��� ������ � ��������.";
			link.l1 = "�� �������?";
			link.l1.go = "inPrison_6";
		break;
		case "inPrison_6":
			dialog.text = "��, � ��� �����. � ������ ��������, ��� �� ������ �������, ����� ������� �� ���� ������.";
			link.l1 = "� ������.";
			link.l1.go = "inPrison_7";
		break;
		case "inPrison_7":
			dialog.text = "������������� �� ������ ����� '������� ����������', ������ �� ������� ��� ����� ������. � ����� ������������ ������� �� ������ � �������� �������, ���������� ������. ������ �� � ��������� ���������� �� ������.\n����� �������� ����, �����, ��� ������ ��� �������� �������... ��� ������ �� '���������', �� ������ ����� ������������ ����, ���� ����������� - ������� ������. ����� � ���� ����� �� ���������. � ��� ��� �������, ��� �� ������ ��������� �� ����������� �� ������ ����� '�������� ����������'.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ������� ���... ����� ����, ���-���� ���������� ������� ��� ������� ������?";
			link.l1.go = "inPrison_8";
		break;
		case "inPrison_8":
			dialog.text = "��������, ��� ���� ������� ����� � ���� ����. ������ ��� ������ - �� ���� ������...";
			link.l1 = "��������, ������ �������. ����� ��� ������ � ���� ������.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "67");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","���"));
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
		case "inPrison_3_alt":
			dialog.text = "��� �����. ������� ��� ����, ������.";
			link.l1 = "�������. ��� ������?";
			link.l1.go = "inPrison_4_alt";
		break;
		case "inPrison_4_alt":
			dialog.text = "������������� �� ������ ����� '������� ����������', ������ �� ������� ��� ����� ������. � ����� ������������ ������� �� ������ � �������� �������, ���������� ������. ������ �� � ��������� ���������� �� ������.\n����� �������� ����, �����, ��� ������ ��� �������� �������... ��� ������ �� '���������', �� ������ ����� ������������ ����, ���� ����������� - ������� ������. ����� � ���� ����� �� ���������. � ��� ��� �������, ��� �� ������ ��������� �� ����������� �� ������ ����� '�������� ����������'.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ������� ���.";
			link.l1.go = "inPrison_5_alt";
		break;
		case "inPrison_5_alt":
			dialog.text = "� ���� ������ �� ����. �������, �� �������.";
			link.l1 = "� ����... � ����...";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "71");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
			//������
			ref sld = GetCharacter(NPC_GenerateCharacter("Mechanic", "Mechanic", "man", "man", 30, SPAIN, -1, true));
			sld.name = "������";
			sld.lastname = "�������";
			sld.greeting = "Gr_questOfficer";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 10, 10, 10, 10, 99);
			SetShipSkill(sld, 50, 50, 50, 50, 100, 100, 50, 100, 50);
			SetSPECIAL(sld, 6, 10, 9, 10, 10, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LightRepair");
			SetCharacterPerk(sld, "InstantRepair");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "Turn180");
			SetCharacterPerk(sld, "SailingProfessional");
			SetCharacterPerk(sld, "Carpenter");
			SetCharacterPerk(sld, "Builder");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			TakeNItems(sld, "talisman7", 1);
			sld.quest.OfficerPrice = sti(pchar.rank)*350;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
	}
}
