
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
		//--------------------------------- �������� � ���������� ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("���","���") +" �� �� ������, " + GetAddress_Form(NPChar) + ". ������ ������� "+ GetSexPhrase("������ ����","����� ������") +" � ���� � �����������...", "�����, "+ GetSexPhrase("���������","����������") +"! ��� ������ �� ���� �����"+ GetSexPhrase("","�") +"?..", "�� � ������� �������. ������ �������� ������� �� ���� ����������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!");
				link.l1 = RandPhraseSimple("�������, ����...", "���������� � ����������...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("������������. � ����������� �����������. ���� ����� " + GetFullName(NPChar) + ".", "� ��������� ������� � ���� �������, " + GetAddress_Form(NPChar) + ".", "�� ������, " + GetAddress_Form(NPChar) + ", ��� ���������� - ������� �������, � ������� ������ ��������...");
				link.l1 = RandPhraseSimple("����� ������.", "��, ���������...");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "��, ��� �� ��� ��������?! � �-��, ����, ����, ������ �� �������... ������!!!";
			link.l1 = "��������, ����...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- ����� � ���������� ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("����� ��� ������, ��������","����� ��� ������, ��������") +"!", "���������� �������� �� ���� �����������, "+ GetSexPhrase("�������","���������") +"!", "��� ��� ���� �� ����, ��� ���� ����� � ���� ����������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". �� ��� ���� ����� - �������� ������!");
				link.l1 = RandPhraseSimple("�������, ������...", "������, �� �������� ������ �������!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("������������. � - ����� �����������. ���� ����� " + GetFullName(NPChar) + ".", "� ������������ ����� �� ��������, " + GetAddress_Form(NPChar) + ".", "�� ������, " + GetAddress_Form(NPChar) + ", ��� ���������� - ������� �������, � ������� ������ ��������...");
				link.l1 = RandPhraseSimple("����� ������.", "��, ���������...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "�� �� ����� "+ GetSexPhrase("�������","��������") +" ���������� �����������?! ������, ����� "+ GetSexPhrase("����","�������") +"!!";
			link.l1 = "������ �����...";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- ������ � ���������� ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("��� �� ������, ��������","��� �� ������, �������") +"...", "���������� ������!", "��, �����, ������ �� "+ GetSexPhrase("������","��������") +"? ��� ��� ����������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". ���� ����� ����!");
				link.l1 = RandPhraseSimple("����, ����� ������!", "�� ���� �� � ���� ����...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("������� ���� ��������� � ����� � �����������. �������� �����...", "� ������� ��� �����������, " + GetAddress_Form(NPChar) + ".", "��� ������ - �������� ��� �����������.");
				link.l1 = RandPhraseSimple("�������.", "��, �������...");
				link.l1.go = "exit";
			}
		break;
	}
}
