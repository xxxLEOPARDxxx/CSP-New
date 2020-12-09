// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l1 = "������, � ����, � ��� ����� ����������� ���. ���� � ���-�� ������?";
				link.l1.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l2 = "����� ��������, ��� ���� ������ ���������. ����� ������ ������ ��� ���������.";
				link.l2.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l3 = "���� ���������� �� ������ �������� �� �������� ������. ��� ��������� ������� ��������...";
				link.l3.go = "zpq_fld2";
			}
			link.l4 = "� "+ GetSexPhrase("������","��������") +". ����� ��������.";
			link.l4.go = "Exit";
		break;

		case "zpq_prs1":
		if(!isBadReputation(pchar, 70))
		{
			dialog.text = "��, ��������-��������... �������, ��������� ����� ������� ���������, ������ ��� ����������. � ��������� ������, � �� ���� �� ���� ������������� �� �������� ����. ���� � ���, ��� ��� ����� �������� ������� ������ ���������� �����, ��� ��� ��� ����������� ����� � ������� ������ � ���������� ���������. � �� ������ ���������, ��� ���������� ���������� ��������� �������� ��� ����������� ����\n���� ��� ������� ���� �� ���� �� ������� - ������� �� ���� �����. � �����, �� ���� ���������...";
			link.l1 = "���������� ���������� ������. � ���� � �� �����������, � ����� ����� ���� ����, ��� �� �����"+ GetSexPhrase("","�") +" ��������, ���� ������ ����� ���������. � ����� ������, � ��� �����.";
			link.l1.go = "zpq_prs2";
			link.l2 = "���, �������... ������ ��� ����� ������ ���� ������� �� ����, ������� ��� �������������� ��� ������ ������������. � �� ����� ����������� � ����...";
			link.l2.go = "zpq_fld";
		}
		else
		{
			dialog.text = "���� ��������� �� ��������� ��� ����� � ���� �������-������ ��������� ���. ����� ��� ���������� ���������. �� ���� � ��������� ������ ���� ��������.";
			link.l1 = "�� ��� �, �������...";
			link.l1.go = "exit";
		}		
		break;
		case "zpq_fld":
			dialog.text = "��, �� ������� ����, �� ���������� ������ � �� ����� ��������... �� ���� ��� �����������.";
			link.l1 = "��������.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_fld2":
			dialog.text = "��, ����������, �� ������ � ������ �����������. �������� ������� ��� ���������... � ������� ��� �������� �� ���������� ���������� ����������.";
			link.l1 = "����� ���� ��������...";
			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -10);

			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_prs2":
			dialog.text = "��� � �����������. ���� � ���, ��� �������� �������� ����� �������� �������� ���������� ���������� ������ � ��������� ������ �����. �������, ��� �� ����� ��������� � ����� ���������� ��������� �� ���������. � ������ ��������� �����, ���� ���� �� ������ ������� ��������� �����, �� ����� �� �����������.";
			link.l1 = "������ ����, ��� �� ���� ��� �����������. � � ����� ���������� ��� ����?";
			link.l1.go = "zpq_prs3";
		break;
		case "zpq_prs3":
			dialog.text = "��� ����� 50 000 �������� ���������� ������. �� ��� ������ � ������� 300 000 ��������... ��� ����� ������� ����, ���� ���������. ���� ��������� ��������� ���� �� �������� ��������, ���� ��� ������ ������� ������ ������� � ���� ��������������� ��������... ����� ������� �� ��� ����������� ��������������� �������� �������� ���������, �� � ����������� ����� ����� ��� �� � ����...";
			link.l1 = "�������... ���� � ������ ������. ������, �� ��������� � �����-�� �����.";
			link.l1.go = "zpq_prs4";
		break;
		case "zpq_prs4":
			dialog.text = "� ���� � ����, ��� ����� ���������� ������ � ����� ����� ���� ����� ������� ��� ���������������. �� ���� ������ ���� ��������� ������� ������ ����� �� ��������� �����, � �� ���� � ����� �������... ��� ��������� ���� ������ �������� �������� �� ������ �������������� ��������, ���� ���� ��� �������� - ���� � ����� ��������!..";
			link.l1 = "����... �� � ����� �� ����� �� ������ - ��������, ��� ����� ������.";
			link.l1.go = "zpq_prs5";
			link.l2 = "�� ��, ������... �������� ���� �� �������������... ���-�� ��� ����������� � ��� �����������.";
			link.l2.go = "zpq_fld2";
		break;
		case "zpq_prs5":
			dialog.text = "��� � ���������, � ����� ���, ��� �� ������������. ������������ ����� �� ����� ��������, ������ ������ ����� �� �����������\n���� ����� �� �����, ��� ����� ������, ��� ��� � ����� ������� ��� ����� ����� � ����. ���� � �������, ��� ������� ����� ������ ����� ��������, � ����������� �� ������� ��� �� ���, ��� �� ������������ �� ����������.";
			link.l1 = "��� �� ��������� ����, ������. ��������� ����������.";
			link.l1.go = "zpq_prs5_ok";
		break;
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		case "zpq_ex":
			dialog.text = "�� �������-��! � �� �������, ��� �� ������ � ����� ��������. ������ ����������� �������� ������ ��� ��������. ��������� � ������� �� ������ �����, ��-��!";
			link.l1 = "��� ��� ���������, ������, �� � ��������"+ GetSexPhrase("","�") +" ��������� �� ������.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            		pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            		pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            		pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		case "zpq_ex2":
			dialog.text = "��-��, �������. ��� ������ �� �������� 150 000 ��������, �������� ������ �������.";
			link.l1 = "��, �����, ������, ������?! ������� ��� �� 300 000, � � �� �������"+ GetSexPhrase("","�") +" �������� �� �������!";
			link.l1.go = "zpq_ex3";
			link.l2 = "� ������� ������, ��� �� ������ ���� ��������, ������� ��� ����� 450 000 �������� � ������ �� ����!";
			link.l2.go = "zpq_ex4";
			link.l3 = "��... ����, �������������� ����������. ��� � � �����"+ GetSexPhrase("","�") +" ������� ��������� �����, ���� �� �������� ����������.";
			link.l3.go = "zpq_ex5";
		break;
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = "�� ��-�... �����! 300 000 ��������. �����������, ����� ���� ��������. �������, ������ ��, ��� �� ���, �������... �������, ��� ���� ������. ������� ���� ����� � ���� ����. � ������ ����� ���� ��������, ���� ����...";
				link.l1 = "��� ���� �������, ������. ����� ��� ��������.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "���-�?!! ������� ������ � ��������� ���, ����� ������ � ���� ���������!";
				link.l1 = "�� ��, ������, ����������� ����! ��������� ��-�������� ������ ������, � ������� �� �������������� ��� � ������� �����!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "����� ���� ��������... ������, � ������ ������������ �����, � �� ����������.";
				link.l2.go = "zpq_ex5";
			}
		break;
		case "zpq_ex4":
				dialog.text = "����� ��������! � ��� �� ��� �� ����� � ���������� ����� �����, ��� ��� ������ ��� �� 300 000 ��\n... �� ����! ���� �� ������� ���� ������!";
				link.l1 = "�� ����������. ����� ��������� � ���, ��� � ���� ������ ����� ����� ������� �������, ������� ������� �������. ��� ���������� ������ ��������� � �� ����� ���������� ���� ����� ���������.";
				link.l1.go = "zpq_ex6";
		break;
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = "��-��... ������ ��������. 450 000 ��������, ��������? ���, ������� ���� ������... � ������ ����� ���� ��������, ���� ����...";
				link.l1 = "����� ��� ��������, ������. ��������.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            			AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "���?! � ������ ������! �� ���� ������ �������"+ GetSexPhrase(", ������","�, ��������") +"?! ������, ����� �"+ GetSexPhrase("��","�") +"!!";
				link.l1 = "�� ���������, ����� ����������...";
				link.l1.go = "zpq_ex_war";
			}
		break;
		case "zpq_ex5":
			dialog.text = "���������! �� ������� ���������� �����. �������� ������ � ��������. � ���� ������� ���� ����� ����. ��-��-��!";
			link.l1 = "��������...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            		AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		case "zpq_ex_agry":
			dialog.text = "�� �� ������"+ GetSexPhrase("��","��") +"!! ������, ����� �"+ GetSexPhrase("��","�") +"!!";
			link.l1 = "����!! �������� ������� ������ � ������ �����...";
			link.l1.go = "zpq_ex_war";
		break;
        	case "zpq_ex_war":

			DialogExit();

			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			pchar.questTemp.zpq = "failed";
            		AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade20");
			EquipCharacterbyItem(npchar, "blade20");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");

			chrDisableReloadToLocation = true;

			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";

			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");

			AddSimpleRumour("�� � ���� � ��� ����������!! ������������, ��� � ������ �����-�� ����������� �������� �� ���������, ������� ��� ������ �����, ������� ����� � ��� �����! ��, ����-�!..", SPAIN, 5, 1);

		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

