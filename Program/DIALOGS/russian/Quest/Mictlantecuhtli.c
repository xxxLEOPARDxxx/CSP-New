
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
			dialog.text = "�� ����� �������������.";
			link.l1 = "��� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//������ ���������� ���
		case "ClimeUsurer":
			dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ����� ������ �� ����� ������� �����!";
			link.l1 = "�?.. �-�, �� ��, ���� ����... ��, �� ������ � �� ����"+ GetSexPhrase("","�") +", ��� �� ���� �����.";
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = "��� �� �����, ��� ���. �� ����"+ GetSexPhrase("��","��") +" ������ ��� ���������� " + FindRussianMoneyString(sti(pchar.questTemp.LSC_climeUsurer.qtyMoney )) + ". � ���� ���� ����� ������?";
			if (sti(pchar.money) >= sti(pchar.questTemp.LSC_climeUsurer.qtyMoney))
			{
				link.l1 = "��, �������...";
				link.l1.go = "ClimeUsurer_yes";
			}
			else
			{
				link.l1 = "���-�� ��� ��� ����������... � �� �� ����"+ GetSexPhrase("","�") +", ��� ��� ������ ���� ����� ������������.";
				link.l1.go = "ClimeUsurer_no";
			}
		break;
		case "ClimeUsurer_yes":
			dialog.text = "������. ����� � �������� ����.";
			link.l1 = "�������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LSC_climeUsurer.qtyMoney));
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;
		case "ClimeUsurer_no":
			dialog.text = "�� ����"+ GetSexPhrase("","�") +"?!!\n����� �� ���������� � ����� ������ �������! ����� ������� ������, ����� ������...";
			link.l1 = "��� �� ��� ���?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_noMoney");
		break;

		//� ������� ����� �������� ����� �������
		case "InGreateTemple":
			dialog.text = "��� �� ������"+ GetSexPhrase("","�") +", ������"+ GetSexPhrase("��","��") +"?!!";
			link.l1 = "���-��!.. ���� �� ��������, �� �� � ���� ��� ����� ��� �������.";
			link.l1.go = "InGreateTemple_1";
		break;
		case "InGreateTemple_1":
			dialog.text = "��� ���\n� ����� �������� �� �����, ���� �������� �� ������������ �������� ����. �� ������ �� ����"+ GetSexPhrase("","�") +" ������� ����� ������, � ��� ��� �� ������...";
			link.l1 = "���������, ��������� ���, ��� ������� ���� ����� ������� ����� �����, ��� �������� ����� ����������� �� �������.";
			link.l1.go = "InGreateTemple_2";
		break;
		case "InGreateTemple_2":
			dialog.text = "���������? ��-��, ����� �� ����������. ����, ����� � ���� �� �����.\n�� ��� ��, �� ��������"+ GetSexPhrase("��","���") +" �� ����������� ������, � ��� �������� �������������. �� �� �����"+ GetSexPhrase("","�") +" �������������� ������, ������� ������� �� ������ ��������\n����� ����� �� ����� ������ �������� �������� ��������. �� �������"+ GetSexPhrase("","�") +", ��� ��������� ������� ������,"+ GetSexPhrase(""," �������� �� ��, ��� �� �������,") +" ������� � ��� ���� ���� ������. ������, ��� �� ������� ����, � �� ������� ���� ������.";
			link.l1 = "��� � ����"+ GetSexPhrase("��","��") +" �������?";
			link.l1.go = "InGreateTemple_3";
		break;
		case "InGreateTemple_3":
			dialog.text = "��������� �� ����. ������!";
			link.l1 = "�������� ������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_fightInTemple");
		break;

		//� ������� ����� �������� ����� ������
		case "WinInTemple":
			dialog.text = "�� ��� ��, �� �������"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("��","���") +". ������ �� ������ ���� ������ ���"+ GetSexPhrase("��","��") +".";
			link.l1 = "��-�-�... ���� ������, � ������ ����� �� �����.";
			link.l1.go = "WinInTemple_1";
		break;
		case "WinInTemple_1":
			dialog.text = "�� ����, � ���� ����� �����. ����� ������ ����� ����, �� ��� ��������"+ GetSexPhrase("","�") +".";
			link.l1 = "������� ���, ��������� ���.";
			link.l1.go = "WinInTemple_2";
		break;
		case "WinInTemple_2":
			dialog.text = "������ ��� �� ������, � ���� ���������� ����, ��� ����� ���������.";
			link.l1 = "����� ��������� ���������.";
			link.l1.go = "WinInTemple_3";
		break;
		case "WinInTemple_3":
			dialog.text = "��� ��������� ������, ��������� ����� ������� �������. 150 ��� ����� �� ������ ����� ������ ������, ����� ��������� ������������ � ���������� ������������ � �������� ������������\n"+
				"��, ���� �������, �� �������� ��� ������������� � �������� ���������, ���� � ����� ����� ���� ����� �������� ���� � ����. ����� ������� ������ �.";
			link.l1 = "��������, ���� ����? � ����?";
			link.l1.go = "WinInTemple_4";
		break;
		case "WinInTemple_4":
			dialog.text = "���� ����� ������ �����, ����� �� ����������� ����. ���� ����� ��������, �� �� ���������� ���� � ����, ��� ��������. � ������� �� ����� ������ ������, ��� ������ ��� ����������� ���� ����� �������, ��� ��� ������ ���� ���������� ���������, ��������� ��� ����� ������.\n"+
				"� ������� ������� ���������� ������� ���� ���� ����� ������. ���� �������� ������������, � �������� ������ ��� ������� ��� ������� ������.\n"+
				"��������� �� �������, ��� ������ ��� � ������� �������, � �� ��������� ����� ������ �� ������� ����� ������� � �������� �� ������ ������ ������.";
			link.l1 = "��� ��� �������?!";
			link.l1.go = "WinInTemple_5";
		break;
		case "WinInTemple_5":
			dialog.text = "����� � ��� �������. ������ �� ������, ��� ����� ����� �� ������ �������. � ����, ��� ���������� ����� ����� ������ ��� ��������, � ��� �� ����� ������ ��������� �����\n������, ����.";
			link.l1 = "�� ��������, ��������� �������... �������...";
			link.l1.go = "WinInTemple_6";
		break;
		case "WinInTemple_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			AddQuestRecord("Tenochtitlan", "4");
			AddQuestUserData("Tenochtitlan", "sSex", GetSexPhrase("","�"));
			DialogExit();
		break;
		
		case "Samil":
			dialog.text = "�� ���������"+ GetSexPhrase("","�") +" ����, ������"+ GetSexPhrase("��","��") +". ��� ������ �� ��������� ������� �� ������ ����������. ���� ��, ��� �� ������ ������ �� ������ �� �����!";
			link.l1 = "��... ����? � ��������"+ GetSexPhrase("","�") +" � ���� ���� �� ����������, �� �� ���"+ GetSexPhrase("��","��") +" ����� ��������� ������, ����� ����� ����� ������.";
			link.l1.go = "Samil_2";
			if (pchar.sex != "woman") LAi_CharacterPlaySound(NPChar, "Samil_1_man");
			else LAi_CharacterPlaySound(NPChar, "Samil_1_woman");
		break;
		
		case "Samil_2":
			dialog.text = "������� �� ������ ���, ��� �������� ��� �������� �� ���...";
			link.l1 = "�������, ������ � ������ �����. � ������� �� ������"+ GetSexPhrase("","�") +" � ����.";
			link.l1.go = "Samil_3";
			LAi_CharacterPlaySound(NPChar, "Samil_2");
		break;
		
		case "Samil_3":
			dialog.text = "�������, ������ ������ ���� ����� ���� ����������� �����������. ��� ���������� � �������, ������� ��� ��-�� ���������� ������� ���� �� ��������...";
			link.l1 = "...";
			link.l1.go = "Samil_4";
			LAi_CharacterPlaySound(NPChar, "Samil_3");
		break;
		
		case "Samil_4":
			dialog.text = "���-�, �� ����� � ��������. �� ������� ���� � ������������ �������. �����, ���� ������ ����������� ������� ���� ����������.";
			link.l1 = "��������� ����, �� ������.";
			link.l1.go = "Samil_5";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			log_info("�� �������� ���������� �������� �� �� ������");
			TakeNItems(pchar,"blade201",1);
			if (pchar.sex != "woman") LAi_CharacterPlaySound(NPChar, "Samil_4_man");
			else LAi_CharacterPlaySound(NPChar, "Samil_4_woman");
		break;
		
		case "Samil_5":
			dialog.text = "�����, ������ ����� �����������. �������� �� ���� ������� �����. �� ���� ���� ������� �������, ��� ��� ������... �� ���� ����� ������� ���� � ����������, ������� �� ������ � ��� ��������. ������, ����.";
			link.l1 = "������ ������� �� �������� ����� �������. ������!";
			link.l1.go = "Samil_6";
			LAi_CharacterPlaySound(NPChar, "Samil_5");
		break;
		
		case "Samil_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			pchar.quest.treasure_portal.win_condition.l1 = "locator";
			pchar.quest.treasure_portal.win_condition.l1.location = "Treasure_alcove";
			pchar.quest.treasure_portal.win_condition.l1.locator_group = "teleport";
			pchar.quest.treasure_portal.win_condition.l1.locator = "teleport6";
			pchar.quest.treasure_portal.win_condition = "treasure_portal";
			DialogExit();
		break;
	}
}
