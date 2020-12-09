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
			dialog.text = "�� ���� �������������.";
			link.l1 = "��, �������...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "�������, ������"+ GetSexPhrase("","���") +", �� �� �� "+ GetFullName (pchar) +"?";
			link.l1 = "��, ������ ���. ��� ���� �������?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "��-�� ��� � �����. � ������, ���� ������. � �� ��������� ����������, � ������� �� � ���������� - ���� � ����������� ���������.";
			link.l1 = "�� ���������, ����� ������? �� ������� �� ��, ��� � ����� ������ � ����� �����.";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "�� �������� ��� ������. ������ ������� ������, ������� ������ ��� �������� - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + ", � ����� ����� �������. ��� �� ������ �� �����.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "�� �� �� ��� �� �������� ����� �� ���������? ����� ���� ��� ���������� - � ��������"+ GetSexPhrase("","�") +" ��� � ��������. ��� ��� ������������, ���� ��� �� ��������"+ GetSexPhrase("","�") +" ������.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "�� �� �� ��� �� �������� ����� �� ���������? ��������� ���, ��� ������ ������ � ������� ����, ����� ������� � ��!";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "������, ��������� ���� ������� ������, ��������!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "� ���� �� ���...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "�� ��� �, ������ ����� ���� ������ - ������� � �������� ��� �� ��������, ������ ��� ������ ������� ������ ��������� ���� � �����.";
			link.l1 = "����� ���������������.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "��-��, ������ ����� ��� ������ - ������� �� ��������. �� ��� ��� ���� �� ���� - ������ �� ������� �� � ��� ��������.";
			link.l1 = "� ��� �������� �������...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "��, ������!! � �� ������� ����� �"+ GetSexPhrase("��","�") +" �� ������!";
			link.l1 = "��, �� ���� �����������...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "��� � ������. ����� �� ���� � ����������, �������!";
			link.l1 = "���...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","�"));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}





