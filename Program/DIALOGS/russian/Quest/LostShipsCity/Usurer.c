
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "���, ��� ��� �� � ��� �� ���������� ���������� �������? ��, ��� ��, ����� ����������.";
				link.l1 = "�������. ���� ����� " + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "����������. �� ���-�� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = "��� ����� ������.";
				link.l1.go = "GiveMoney";
				link.l10 = "���, ������ ��� ��������"+ GetSexPhrase("","�") +" � ����.";
				link.l10.go = "Exit";
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, ���� ��������� ��������. � ������� �������.";
					link.l8.go = "SeekCrew";
				}
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FT_1":
			dialog.text = "����� �������. � ���� ������� �����. ����� �������.";
			link.l1 = "������.";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "���� ���� ����� ����� ������ - ������ �� ���, � c���� ��������.";
			link.l1 = "�������, ���� �����...";
			link.l1.go = "Exit";
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
			dialog.text = "��, "+ GetSexPhrase("��������","�������") +", �� ������, � ��� ������"+ GetSexPhrase("��","���") +"! � ������ ���� �����...";
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
			dialog.text = "��, ������... ����� ������.";
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
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� ������� ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("� ����.", 
				"�� ��� �������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������.",
                "������, ������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������? ������?", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "��� ������ ��������... �� �����"+ GetSexPhrase("","�") +" ������� ���� � �����?";
			link.l1 = "��. �� �������� ����� �� ��� � �������?";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "���. � �������� ����� �� ���������� �������.";
			link.l1 = "������, �� ����� ��������, ���� ��������� ������. �� ����� ����������� ���� ���������� ����.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "� ����, �� ��� ����� ��������. ��� ������ �� ��������.";
			link.l1 = "�������� ��... �� ��� ������.";
			link.l1.go = "exit";
		break;

		//������ �����
		case "GiveMoney":
			if (CheckAttribute(npchar, "quest.loan"))
			{
				if (sti(npchar.quest.loan.qtyMoney) >= 1000000)
				{
					dialog.text = "�� �������� ��������"+ GetSexPhrase("","�") +" ���������� �����. ��������� ����� ���� �������.";
					link.l1 = "����.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "� ����� ����������� ���� �������.";
					link.l1 = "�������!";
					link.l1.go = "GiveMoney_1";
				}
			}
			else
			{
				dialog.text = "������. � �� ������ �������, �� ������� � ������������ �����?";
				link.l1 = "���� ���. ��, �������, �� ��� ����������.";
				link.l1.go = "GiveMoneyKn_1";
				npchar.quest.loan = true;
				npchar.quest.loan.qtyMoney = 0; //���-�� ������ �����
			}
		break;

		case "GiveMoneyKn_1":
			dialog.text = "�����������. ����, ������ ����� �������������� ����� ��������� ��������. �� ������ ����� � ���� ����� ����� � ���� ��������.";
			link.l1 = "�������. � ��� ����� ������� �������?";
			link.l1.go = "GiveMoneyKn_2";
		break;
		case "GiveMoneyKn_2":
			dialog.text = "� ���� ��� �����������, ���������� �� �������. �� ������ ����"+ GetSexPhrase("��","��") +" ������ ������� ��� � ���� ��� ������� ����� �� ������� ���������� ����� ����������� ����.";
			link.l1 = "����?!!!";
			link.l1.go = "GiveMoneyKn_3";
		break;
		case "GiveMoneyKn_3":
			dialog.text = "� ���� �������� �� ������?";
			link.l1 = "���, ������ � ������� ������"+ GetSexPhrase("","�") +"...";
			link.l1.go = "GiveMoneyKn_4";
		break;
		case "GiveMoneyKn_4":
			dialog.text = "������ ������� � ���� ���, ��� � ����������� ���� �� �� �� ����.";
			link.l1 = "��, �������...";
			link.l1.go = "GiveMoney_1";
		break;

		case "GiveMoney_1":
			dialog.text = "����� ����� �� ������� ������ � ����?";
			Link.l1.edit = 4;
			Link.l1 = "";
			link.l1.go = "GiveMoney_2";
			Link.l2 = "��, �������, ���� �������� �� �����.";
			link.l2.go = "GiveMoney_disAgree";
		break;
		case "GiveMoney_2":
			iTemp = sti(dialogEditStrings[4]);
			if ((iTemp + sti(npchar.quest.loan.qtyMoney)) > 1000000)
			{
				dialog.text = "������������� ����� ��������� ������������� ����� � �������. � ���� ���� ���� " + FindRussianMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)) + ", �� �����.";
				link.l1 = "�������...";
				link.l1.go = "exit";
			}
			else
			{
				if (iTemp <= 0)
				{
					dialog.text = "�����"+ GetSexPhrase("�","��") +", ��? �� ������� ���������� �� ����.";
					link.l1 = "��, �����...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "������, � ����������� ������ ���� ��������� �����.";
					link.l1 = "�����������! �� ������� ���� �������, �������.";
					link.l1.go = "GiveMoney_3";
					AddMoneyToCharacter(pchar, iTemp);
					npchar.quest.loan.qtyMoney = sti(npchar.quest.loan.qtyMoney) + iTemp;
				}
			}
		break;
		case "GiveMoney_3":
			dialog.text = "����� ���. �������, ��� �� ������ ������� �� �������� �������� �� ��������������� ����. ����� �������� �����, �� ����"+ GetSexPhrase("��","��") +" ������ ������� �����, � ���� ��� ����������� ������ �����. � �� ������ ������, ��� " + FindRussianMoneyString(sti(npchar.quest.loan.qtyMoney) * 5) + ".";
			link.l1 = "��, � �����. � ��� �����, ���� � �� ����� �� ����� �������?";
			link.l1.go = "GiveMoney_4";
		break;
		case "GiveMoney_4":
			dialog.text = "��, �����, ���� �� ��� � ���� ����"+ GetSexPhrase(", ��������","") +". ������������, ����� ������, ����� �������. �����...";
			link.l1 = "����. �� ��� ��, ���� ��������.";
			link.l1.go = "exit";
		break;
		case "GiveMoney_disAgree":
			dialog.text = "��, ��� ������. ���������� ��� �������, �����, � ��������� ���.";
			link.l1 = "��, �������...";
			link.l1.go = "exit";
		break;
	}
}
