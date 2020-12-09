
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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("������, � ���������� ����!!!", "���������� �������, ������!!!");
					link.l1 = "�� ��, ����� ���������� �� �������...";
					link.l1.go = "fight";			
			}
			else
			{
				if (pchar.questTemp.MC == "toByeBye" && findsubstr(npchar.id, "Incquisitor_", 0) != -1)
				{
					dialog.text = "��� ���� ����� � ������ ������ ����������!";
					link.l1 = "������ ����, � ���� ���� � ��� ����. �� �������� "+ GetSexPhrase("����������� ��������","���������� ���������") +" � ������ ��������.";
					link.l1.go = "MCIncq";
					pchar.questTemp.MC = "Incquisitio";
					break;
				}
				
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����������, "+ GetSexPhrase("��� ���","���� ���") +". ������ �������� � ���?..", "��� ������ ���� � ����� �������, "+ GetSexPhrase("��� ���","���� ���") +". ����� ���������"+ GetSexPhrase("","�") +"?"),
							""+ GetSexPhrase("��� ���","���� ���") +", �� ��� �������� � ����� �������. ���� ����� ���-�� ���?", ""+ GetSexPhrase("��� ���","���� ���") +", ����������� ������ ������ �� �������� ��������. ��� ��� ���� ���������: ���� ���-������ �����?",
							RandPhraseSimple("������ ��������� � ���������� ������ � ��������� ������ �� ������. ����� � �� ��������� �� �����...", ""+ GetSexPhrase("��� ���","���� ���") +", � �� ����� ����� ������������� ���������. ���� � �� ����� ����� �� �����."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("�� ���, ��������"+ GetSexPhrase("","�") +" �� �����, ������ ����...", "��� �� �����, �����. �������, ��� ����� - "+ GetSexPhrase("����","���") +" � �������..."), 
							"�� ���, ������ ����...", "���, �����, ������ �����"+ GetSexPhrase("","�") +" ���������...", RandPhraseSimple("��...", "��, ��� ������, ������ ����..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //����� �� �������
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "���� ������, ��� �����! ����� ���!!!";
					link.l1 = "��������!!";
					link.l1.go = "fight";
					StartIncquisitioAttack();
				}
				else
				{
					dialog.text = LinkRandPhrase("��� ���������� ������, ���� ���� ������������� ��������!!!", "���� � �� ����� ���� ������� - �������� �������.", "���� ��� ������ ���� ������ - � ���� �����...");
					link.l1 = RandPhraseSimple("����, ������.", "�������...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //�����������
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("��-��, �� ���� �� ������ ��������, ��� '�������' ������������ �������� � ��!", "�������, ������� ���� ���-�� ��������� ������� �� �����!!", "� ��� �� ����� �� ���� ����� - �����... �� �� ��������"+ GetSexPhrase("","�") +" ��� ��������� ������������ � �����. �������...");
					link.l1 = RandPhraseSimple("���!", "����...");
					link.l1.go = "exit";
					//==> ����� �7, ����� � ���� ���������. 
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = "��������, �� �� ������ ����� ������ �������� - ��� ��������?";
						link.l1.go = "Step_F7_2";
					}
					//<== ����� �7, ����� � ���� ���������. 
				}
				else
				{
					dialog.text = LinkRandPhrase("��� ������ �������� � ���� '������'. ������� ��� ����� - ������ �� � ��� �� ���� ����...", "���������� ��������� � �����! � ���� � �� �� � ��� �� ������� ����� ��������!!!", "����� ���� ��� ����� �� ������, ��� ��� ��� ������ ��� �� ����... � ������� ��� ��������?..");
					link.l1 = RandPhraseSimple("��... ��, �� ����...", "��� ��, �������...");
					link.l1.go = "exit";
					//==> ����� �7, ����� � ���� ���������. 
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = "��������, �� �� ������ ����� ������ �������� - ��� ��������?";
						link.l1.go = "Step_F7_1";
					}
					//<== ����� �7, ����� � ���� ���������. 
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

//**************************** ��. �������. ����� �7, �������� ���� ��������� ********************************
 		case "Step_F7_1":
			dialog.text = "����, � ������� ������ �����, ��� ������� ��� ���� �������. ��������� �����...";
			link.l1 = "������� ����!";
			link.l1.go = "exit";
		break;
 		case "Step_F7_2":
			dialog.text = "� ������� ������ ������ �� �����, ���, ��� ����� �������, ���� �� ��� �� ����"+ GetSexPhrase("","�") +"...";
			link.l1 = "���, �������... ������� ����.";
			link.l1.go = "exit";
		break;
		
//**************************** ����� ������������ ���-������ ********************************
		case "MCIncq":
			dialog.text = "������ ����, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l1 = "���� �������� ��� � ����������� �����, ��� ������� ����� �� �����!";
			link.l1.go = "MCIncq_1";
		break;
		case "MCIncq_1":
			dialog.text = "������.";
			link.l1 = "��� ������� ���-������, ��� ��������� � ������ ���������. ����� ������ ����� ��� ��� �� ���!";
			link.l1.go = "MCIncq_2";
		break;
		case "MCIncq_2":
			dialog.text = "���... �� �������� ����, "+ GetSexPhrase("��� ���","���� ���") +". ������� ���������� ���� �� ������ ������ ������.";
			link.l1 = "���"+ GetSexPhrase("","�") +" ���������!";
			link.l1.go = "MCIncq_3";
		break;
		case "MCIncq_3":
			dialog.text = "� ����� �� � � ���������� "+ GetSexPhrase("��������","���������") +" ��� �������, ����� � ������� �� ����� 10 ����� ��������.";
			link.l1 = "�������� "+ GetSexPhrase("����������","����������") +", ���� ������������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterReputation(pchar, -10);
		break;
	}
}
