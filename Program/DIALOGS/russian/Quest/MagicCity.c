
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� � ��� ��������.";
			link.l1 = "�����...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_orient":			
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
                LAi_ActorStay(sld);
			}
			LAi_ActorTurnByLocator(npchar, npchar.location.group, npchar.location.locator);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//��������� �� ����������� ������
		case "CitizenNotBlade":
			dialog.text = "� ���-������� �� ����� ������ � ���������� �������.";
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			NextDiag.TempNode = "DesMoinesCitizen";
		break;

		//��������� �������� � ��������
		case "CaracasMan":
			dialog.text = "��, "+ GetSexPhrase("�����","�������") +", ���� ������ �������������? ����"+ GetSexPhrase("��","��") +" �� ������!";
			link.l1 = "�����, � ����������, ���� �� ����������, � ���.";
			link.l1.go = "CaracasMan_1";
		break;
		case "CaracasMan_1":
			dialog.text = "�� ���, � �������, ��������� �����. ���, ����� ��� - ��! - �� �������� ���������, ��-��!";
			link.l1 = "�� �� ����, ��������! ���-�� ��������!";
			link.l1.go = "CaracasMan_2";
		break;
		case "CaracasMan_2":
			dialog.text = "����� ��� �����, ���� ���! � �����, ��� ��� ��������� � �� ����! � �� ������ ����, ��� ��, �������� ����������?";
			link.l1 = "���������, ��������? ��, � ���� �� ����� ��� ������? �� ������ ���!";
			link.l1.go = "CaracasMan_3";
		break;
		case "CaracasMan_3":
			dialog.text = "��� ������ �������, �������, �������! ��� ������ �� ������� - ��! - �����, ����� ������!";
			link.l1 = "�, �� ��� � ������ ���� ��������� ���������! ��-��, ���������� ����, ��������, ��� ��� �� ���������. � ���� ��� �� ���� ������� � ��� ������!";
			link.l1.go = "exit_orient";
			DeleteAttribute(&locations[reload_location_index], "reload.l41.disable");
		break;
		//��������� � ��������
		case "CaracasWervolf":
			dialog.text = "��� �� � ��� ��� �����?";
			link.l1 = "� ������� " + GetFullName(pchar) + ". � ��� �� ���? ���, �� �����, ��������� ����������� ����� ���������� � ��� � �����, � ���� �� �����, ����� ����������� ������� � ���������.";
			link.l1.go = "CaracasWervolf_1";
		break;
		case "CaracasWervolf_1":
			dialog.text = "��� ���������� ����� ����! �� ����� ���, � ���������! � ����� �� ���������, �� ��������� ���������, ������� ���������� �� ���� ������� ������ ������. �������! �� ������ ��� ������. ��� ���������� ��������������!";
			link.l1 = "�� �� ������, ��������. � �� ���������.";
			link.l1.go = "CaracasWervolf_2";
		break;
		case "CaracasWervolf_2":
			dialog.text = "�� �� ���� ������ �������� ���� ����������?";
			link.l1 = ""+ GetSexPhrase("� ������� ������� ���, ��� ������ � �������� ���� �� �����, �������, ��� ��������.","������.") +" ����� �����, ������������ ������������!";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.MC = "toCaracasPadre";
			iTemp = FindLocation("Caracas_tavern");
			DeleteAttribute(&locations[iTemp], "reload.l1.disable");
			DeleteAttribute(&locations[iTemp], "reload.l4.disable");
			LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
			locations[iTemp].reload.l2.disable = true;
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.dialog.currentnode = "CaracasMan2";  
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorWaitDialog(sld, pchar);
			}
		break;
		//�������� �������� �� ������ �� �������
		case "CaracasMan2":
			dialog.text = "��, ���? ��������� �� ������?";
			link.l1 = "��� ���, ��������� �� �� �� �����! ��� ��� �������� ��������!";
			link.l1.go = "exit_orient";
		break;
		//������ ���-������� � �����
		case "ShoreGuard":
			dialog.text = "��, ��! ����� ������ �� �����. �������� �������-���������!";
			link.l1 = "�����, ����� ���������� ����������� ������ ������ ���� ��������� ����������?";
			link.l1.go = "ShoreGuard_1";
		break;
		case "ShoreGuard_1":
			dialog.text = "��� �� �� "+ GetSexPhrase("��� �� �������������, �������","���� �� �������������, �������") +"! �� ��������� ����� ������ - ��������!";
			link.l1 = "� ��� ����� ��� ��������� ������ ���, ��� � ����?";
			link.l1.go = "ShoreGuard_2";
		break;
		case "ShoreGuard_2":
			dialog.text = "��� ����� ����� ��� �����!";
			link.l1 = "��� �, �������, ��� ����� �����?";
			link.l1.go = "ShoreGuard_3";
		break;
		case "ShoreGuard_3":
			LocatorReloadEnterDisable("Shore_ship3", "reload1", false);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("MagicCity", "3");
			DialogExit();
		break;
		//������ ���-������� �������
		case "DMCitiz":
			NextDiag.TempNode = "DMCitiz";
			dialog.text = LinkRandPhrase("��� ��� ����� � ��� � ������?", "����� � ����� ������ ���������� ����� �����. � �� ��� ������?", "�� ������ ��, ��� �� ���� ��� ��������������. ��� ��� ����� � ���-�������?");
			link.l1 = "����������, ��� ������...";
			link.l1.go = "DesMoinesCitizen_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("���� �� �������"+ GetSexPhrase("","�") +"! �����, ���� ��� ������ ��� �������...", "�����, ���� ������, ����"+ GetSexPhrase("","���") +" ��������"+ GetSexPhrase("��","��") +"...", "���� ������! � ����� � ���� ����� ������ �� �����...");
				link.l1 = "�����������!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("�������, ��� �� ����������� ������ ���. ����� ���, �������...", "�� ����������� ��� �������, "+ GetSexPhrase("������ �������","���������") +"!", "��� � �����, ����� � ��� ��� ����������!");
				link.l1 = "�����������!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = ""+ GetSexPhrase("������, �� ��� ���������","���������, �� ���� �������������") +"! �� ������ ��� �������!";
				link.l1 = "�������. ������"+ GetSexPhrase("","�") +", ������"+ GetSexPhrase("","�") +"...";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesCitizen_1":
			dialog.text = "��� � �������.";
			link.l1 = "��-�, �����������!";
			link.l1.go = "DesMoinesCitizen_2";
		break;
		case "DesMoinesCitizen_2":
			dialog.text = "�� ������� ��� ������������� � ���. ��� ������� �� ����� ������������...";
			link.l1 = "��... ��, ��� ��� ���������.";
			link.l1.go = "exit";
		break;
		//������ ���-������� �������
		case "DMSkel":
			NextDiag.TempNode = "DMSkel";
			dialog.text = LinkRandPhrase("��������� ���� �� ���!", "��� ����� �������!", "������, ��� � ���� ����������? ����� ������� ���������!");
			link.l1 = "�� ��...";
			link.l1.go = "DesMoinesSkel_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase("���� �� �������"+ GetSexPhrase("","�") +"! �����, ���� ��� ������ ��� �������...", "�����, ���� ������, ����"+ GetSexPhrase("","���") +" ��������"+ GetSexPhrase("��","��") +"...", "���� ������! � ����� � ���� ����� ������ �� �����...");
				link.l1 = "�����������!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase("�������, ��� �� ����������� ������ ���. ����� ���, �������...", "�� ����������� ��� �������, "+ GetSexPhrase("������ �������","���������") +"!", "��� � �����, ����� � ��� ��� ����������!");
				link.l1 = "�����������!";
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesSkel_1":
			dialog.text = "��� �� �� ������� ���� ���� ������, �� �������� � ������ �����, �������� �������. ����������� ������������ � ���.";
			link.l1 = "������.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", true);
		break;
		//����� ������� �������
		case "DMCitizHead":
			NextDiag.TempNode = "DMCitizHead";
			dialog.text = "������������. ����� ���������� � ��� � ���-������?";
			link.l1 = "�� ���, ����������, ��� � ����... �������, � ��� ��� ��������� � ������?";
			link.l1.go = "DMCitizHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "�������! � �� ���� ����� � ���� ����.";
				link.l1 = "��... �� � ���.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("������ �������","���������") +", ��� ������ ������� ���-�� ����� - ����� ����� ���������� ����. �� ����, �� - ���� ��������� ������� �� ���������� �����.";
				link.l1 = "������� ��� ������ ��� ������ ����� �������� ���������. ���������!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "������������, �������! ��� �������?";
				link.l1 = "� ���"+ GetSexPhrase("��","��") +" �������� �������.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "������������, �������! ��� �������?";
				link.l1 = "� �������"+ GetSexPhrase("��","���") +" �� ������ ������� '��������'. ������, ��� ��� ��������� ��� � ������ ������������.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "��� �� ����� ���������? � �����-�� ������ � ��� ��� ���������������!";
				link.l1 = "��. � ���"+ GetSexPhrase("��","��") +" ������ '��������' � ��� ������"+ GetSexPhrase("","�") +". ���"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("","�") +" ��� ������.";
				link.l1.go = "DMHeadOver";
			}
			if (CheckAttribute(pchar, "questTemp.MC.DesMoines"))
			{
				dialog.text = "������"+ GetSexPhrase("","���") +", ���"+ GetSexPhrase("","�") +" ���������"+ GetSexPhrase("","����") +"! �� ���-�� ������?";
				link.l1 = "�� ���, ������ ����������...";
				link.l1.go = "exit";
			}
		break;
		case "DMCitizHead_1":
			dialog.text = "��� ������. � ������ �� �����������?";
			link.l1 = "�� ������, ����� � �������"+ GetSexPhrase("��","���") +" �� ���� ����������� ������, �� �� ���� ������ �����-�� ����. ���������� ��������� ������.";
			link.l1.go = "DMCitizHead_2";
		break;
		case "DMCitizHead_2":
			dialog.text = "������ �� ���� ��� ������� �� ����� ������. � �� � �����, ��� ��� ���.";
			link.l1 = "�������... ���, �� ��������, � ���-������� ��� ��������.";
			link.l1.go = "DMCitizHead_3";
		break;
		case "DMCitizHead_3":
			dialog.text = "���������� ���������.";
			link.l1 = "��, �������. ��������...";
			link.l1.go = "exit";
		break;

		case "FoundLiz":
			dialog.text = NPCStringReactionRepeat("�������! � ��� �� ��������?", 
				"�� ��� �������� �� ����, �������.", 
				"�������, �� ��� �������� �� ����.",
                "�������, �� ������� �����?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������� �� �����, ��� � ������ ���� �������� ��� ���������. �� �� ����� ��������, ��� ��� �����.", 
				"��, � �����.",
                "��, �������...", 
				"� ���"+ GetSexPhrase("��","��") +", ���������"+ GetSexPhrase("��","��") +". ��� �����, ���� ���� � �� �� ���������� - ����� �������� ����! �������� ������, ��� ��� ����-������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FoundLiz_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FoundLiz_1":
			dialog.text = "�������, �������! ������� ��������� ��������� ����������! ������� ������, ��� ��� �������?";
			link.l1 = "��� ������ ����������� ������ �������. ����� ��������� ���, � �������� ������, ��� ������ ������.";
			link.l1.go = "FoundLiz_2";
		break;
		case "FoundLiz_2":
			dialog.text = "�������, ����� ���, �������� ���, ��� � ����� �����.";
			link.l1 = "� � �����.";
			link.l1.go = "exit";
		break;

		case "DMHeadOver":
			dialog.text = "������� ��� �����������! �� ���� ����� ������� � ������������� ��������� ��c � ���, ��� �� ����������� ��� ������� �� �����.";
			link.l1 = "��� �� �������?";
			link.l1.go = "DMHeadOver_1";
		break;
		case "DMHeadOver_1":
			dialog.text = "�������� ����� ��������! ����� ���� ��� ��� ��� �������, �� ��� ����� �� ��������� ����� ������� �������, ��� ��� ��� ���, ��� � ��� ����.";
			link.l1 = "�� �����, �������� ��� ������ ����. ��� ��� ������ ������.";
			link.l1.go = "DMHeadOver_2";
			link.l2 = "� �������� ���� ������.";
			link.l2.go = "DMHeadOver_3";
		break;
		case "DMHeadOver_2":
			dialog.text = "������� ��� ���. ������ ������, �� ������...";
			link.l1 = "�� �� �� ���. ������ ���������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 20);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;
		case "DMHeadOver_3":
			dialog.text = "�������! �� ��� ��, ����� ��� �������, ������"+ GetSexPhrase("","���") +".";
			link.l1 = "� ��� ����� ����������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;

		//����� ������� ������
		case "DMSkelHead":
			NextDiag.TempNode = "DMSkelHead";
			dialog.text = "� ��� �����, ����� ������� ���� ����� ������ ��������, � �� �������� �������!";
			link.l1 = "������ �����, ����������� � ��� ��� ��������! ���� ���� ������, ��� ����� ��������?";
			link.l1.go = "DMSkelHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = "�������! � �� ���� ����� � ���� ����.";
				link.l1 = "��... �� � ���.";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = ""+ GetSexPhrase("������ �������","���������") +", ��� ������ ������� ���-�� ����� - ����� ����� ���������� ����. �� ����, �� - ���� ��������� ������� �� ���������� �����.";
				link.l1 = "������� ��� ������ ��� ������ ����� �������� ���������. ���������!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = "������������, �������! ��� �������?";
				link.l1 = "� ���"+ GetSexPhrase("��","��") +" �������� �������.";
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = "������������, �������! ��� �������?";
				link.l1 = "� �������"+ GetSexPhrase("��","���") +" �� ������ ������� '��������'. ������, ��� ��� ��������� ��� � ������ ������������.";
				link.l1.go = "exit";
			}
		break;
		case "DMSkelHead_1":
			dialog.text = "��������, ���� �� ����� �������! ��� ����� �� � ���� �������� ������ �� ������.";
			link.l1 = "� �� �� ��������, ��� ��� ������ ���� ��������. �������������.";
			link.l1.go = "DMSkelHead_2";
		break;
		case "DMSkelHead_2":
			dialog.text = "���-�� �������� � ������ ���� ��������� ������ '��������'. ������ ����� ����� ��������������� �������. �������������� ����� �����...\n"+
				"������� ������ �����, � ����� � ��� ����� ����� ����� �����-�� �����. ����� ������� ����� ��������, � ��������� � ��������� �� ������� � ���� ����. � ��� ���� ��� � ��������.";
			link.l1 = "�� ��� ��������? �������� �� ������!";
			link.l1.go = "DMSkelHead_3";
		break;
		case "DMSkelHead_3":
			dialog.text = "�� ��� ��, ��� ������. ���� ��� ����, ��� ����, � ��� ������ ����� - ����� ��� ��������. ����������, ��� ��� ��-�� ������� ����, ���� ��� ��������! � ���� ��� ���� �� ����� ��������� �������������, �� ��� ����� - ����, ��� � ��� ���������, � ���� ���������� ���� �� ������ ���������. �� �������...";
			link.l1 = "�-��, ��������� �������...";
			link.l1.go = "DMSkelHead_4";
		break;
		case "DMSkelHead_4":
			dialog.text = "����, �������, �� ������ ���� ����� � ���� ����. �� ���������, ��� ������ ��� �������� ��������� �� � ����?";
			link.l1 = "� ������?";
			link.l1.go = "DMSkelHead_5";
		break;
		case "DMSkelHead_5":
			dialog.text = "� ��� ������, ��� ���-������ ��� �������� �� �����������. ������� ������ �� �����.";
			link.l1 = "� ��� ����� �� ������ ���������� �����.";
			link.l1.go = "DMSkelHead_6";
		break;
		case "DMSkelHead_6":
			dialog.text = "��� ���� ������ �� ������� ������ �� ���� ����������� ������. �� �� ��� ����� ���������� � ���. ��� ��� ������� ������ �� ����.";
			link.l1 = "� �� ������� �������� �������� ���� �����. �������"+ GetSexPhrase("��","���") +" ���� - ������� � ������...";
			link.l1.go = "DMSkelHead_7";
		break;
		case "DMSkelHead_7":
			dialog.text = "�������, ��� ���\n�������, ������ ��� ������� ����� �� �����. ��� ����� ����� ��������� ����� �� �������, � ���� �������, ������� ���������� � ������ ������... � ����� ������ ������ ����� �� ����� �������. �������, �����, ���-�� �� ���������...";
			link.l1 = "����, �� �����. �����, � ����� ���-�� ������?";
			link.l1.go = "DMSkelHead_8";		
			link.l2 = "�� ��������� �����, �������� ���. ����� ��� ���� �� ��� � ������ ���������? �������� ����!";
			link.l2.go = "DMSkelHead_bye";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", false); //��������� �� ������
		break;

		case "DMSkelHead_bye":
			dialog.text = "� ��� ���� ��, ������������"+ GetSexPhrase("��","��") +" �������.";
			link.l1 = "����. �� ��������...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -20);
			AddQuestRecord("MagicCity", "4");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("��","��"));
			pchar.questTemp.MC = "toByeBye"; //���� ������	
		break;

		case "DMSkelHead_8":
			dialog.text = "����� ��������� - ��� ���� �����. ���� � ���, ��� �� ���� �� �����, � ��� ����.";
			link.l1 = "�����... ����� ���������� ��������� ���� ������, �� ������� ���� ������? ������, ��� ��� ������������ �������.";
			link.l1.go = "DMSkelHead_9";
		break;
		case "DMSkelHead_9":
			dialog.text = "�� ������, ������� � ��� � ����� ��������� �������, �������� �������, �������, �� �����. ��� ���, ��� ���� ������� ������ ������� �� ���������, �������� � ��� � ��������� ������ ���������� �� �� ���.";
			link.l1 = "� ���?";
			link.l1.go = "DMSkelHead_10";
		break;
		case "DMSkelHead_10":
			dialog.text = "��� �������� � ������������ ��������, ��� ��������� ��� ����� ����� �������. � ��������� � ���, ����� �� ��� �����, �� ��� ��������� ������� ��� ���! ������ �� �������.";
			link.l1 = "� �� �� ���������?";
			link.l1.go = "DMSkelHead_11";
		break;
		case "DMSkelHead_11":
			dialog.text = "��������. ��� ���� �� ������ ��� � ���� ���������� ������.\n��� ���, � ���� � ��� �����������. ��� ������ �������� ������� � ������ � ��� ���������, ��� ������ � ����������� � �����, ��� ���� �������� ������� ���-�� ��������.";
			link.l1 = "��� ����������?";
			link.l1.go = "DMSkelHead_12";
		break;
		case "DMSkelHead_12":
			dialog.text = "��� ��������. � �������, ��� ��� ����, �������� �� �� ��� ������ �������. ���� ���� ���������� �� �����, ��� ��� �����.\n������ � ����� ��� ����� �� � �������� ���, ��� �� �������� �� ���� ��������� ������� � ������� '��������'.";
			link.l1 = "������, � ��� � ��������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("MagicCity", "5");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("��","���"));
			pchar.questTemp.MC = "toSeekSister"; //���� ������	
			LocatorReloadEnterDisable("Charles_town", "housePirate", false);
			//������ ��� �������
			sld = GetCharacter(NPC_GenerateCharacter("LizSheppard", "BaynesDaughterSTOK", "woman", "towngirl", 10, ENGLAND, -1, false));
			sld.name = "��������";
			sld.lastname = "�������";		
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "LizBegin"; 
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Charles_PirateHouse", "goto", "goto1");
		break;
		//�������� �������
		case "LizBegin":
			dialog.text = "������������, �������. ��� ������� ������������ ������ ��� � ���� ����?";
			link.l1 = "������������, ��������. ���� ����� " + GetFullName(pchar) + ". � ����"+ GetSexPhrase("��","��") +" ������������ � ���� �� �����... ����� ��������� ����.";
			link.l1.go = "LizBegin_1";
		break;
		case "LizBegin_1":
			dialog.text = "������ ��� �����������, �������.";
			link.l1 = "��������� ����� ����� �� �������� ��������� ��������� ��������� - ���-������. ����� ����� ���������� ������, �������� ������, � ������� ��, �������, �������, �������� ���� ��������� ���. ��� � � ������������� � ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "LizBegin_2";
		break;
		case "LizBegin_2":
			dialog.text = "�� ���� �������, �������. �����������.";
			link.l1 = "�������� ������ ��� � ������.";
			link.l1.go = "LizBegin_3";
		break;
		case "LizBegin_3":
			dialog.text = "��� � ���� ������?";
			link.l1 = "�������� ��� ��������� ������ '��������'.";
			link.l1.go = "LizBegin_4";
		break;
		case "LizBegin_4":
			dialog.text = "����� ��� ����� ���� ������?";
			link.l1 = "���� � ���, ���� ����, ��� ������ ������ ��������� � ���� ��������... ������������� ��������� ��������, ���������� �����.";
			link.l1.go = "LizBegin_5";
		break;
		case "LizBegin_5":
			dialog.text = "��������� �������� � ������� ���-�������?!";
			link.l1 = "��, ��� ���. ��� �� ������ � ���������?";
			link.l1.go = "LizBegin_6";
		break;
		case "LizBegin_6":
			dialog.text = "������� ����! ���� � ���, ��� ������� ������� '��������' - ����� ������� ��� �������. ��������� ����� � ������ ��� � ���������, ��� ������� ��������� ���� ������ � �������� ����������� ����.";
			link.l1 = "����������?";
			link.l1.go = "LizBegin_7";
		break;
		case "LizBegin_7":
			dialog.text = "�������. ���� � ���, ��� � ���� ���������� ����� ������� ��������. ��� ����, ������� �������, ��� ��������� ���������� ������� ���������!";
			link.l1 = "�-�, ��� ����� ��������, ����...";
			link.l1.go = "LizBegin_8";
		break;
		case "LizBegin_8":
			dialog.text = "��� ���, �� ���� ������� ������, � ���������� �� ������� � ��������. �������, �� ������, ��� ���?";
			link.l1 = "��� ��!";
			link.l1.go = "LizBegin_9";
		break;
		case "LizBegin_9":
			dialog.text = "��, ��� ������ ������ � �����-��������, ������� � �������� ������ ������� �����. �� ��� �� �� �����, � ������ ������� ����� ������!..";
			link.l1 = "� ���� ��� �����"+ GetSexPhrase("","�") +", ��������. ������� � ��������������� ������������ ������� - ������� ������������. ��� ��� �� ������ ��� ������� � ��������?";
			link.l1.go = "LizBegin_10";
		break;
		case "LizBegin_10":
			dialog.text = "����� ��� ������� ������ ��������� ��� ������� �� ����� ��������������.";
			link.l1 = "�-��... ��, � ��� ������ ������?";
			link.l1.go = "LizBegin_11";
		break;
		case "LizBegin_11":
			dialog.text = "����� ��������� ���������� �����, �������� ����� ����. ������ � ��� ������� ����� ����� ���������.";
			link.l1 = "� ��� �� �������, ��� �� ���������?";
			link.l1.go = "LizBegin_12";
		break;
		case "LizBegin_12":
			dialog.text = "� ���������� ������ �������.";
			link.l1 = "��������, ��� ��� �� ��������� �� ���� ����������� ������? ������ ��� ��������� ���� �� ������� ���-�������?";
			link.l1.go = "LizBegin_13";
		break;
		case "LizBegin_13":
			dialog.text = "� �� ����\n������� �����, ������ ���� �����, � ��������, ��� � ��� ���-�� �����. � ���������� ���� � ������� ��������� ������. ��� ���� ������\n� ���������. ������ ���� ��������� � ������. ������ ����� � ������, ��� ��� ��� ������� '��������'. � � ��������� ���!";
			link.l1 = "������, ����, �� - ������� ������� ������������. ����������� �������� �� ����� ����� �������� �� ������ ������ �� ������.";
			link.l1.go = "LizBegin_14";
		break;
		case "LizBegin_14":
			dialog.text = "��� �� �����, � ���������� �������� ��� ��������. ����� � ������ ������, ��� ����� � ���������, ��������� �������� '��������' � �������� ���!";
			link.l1 = "���� ������, ��� ����������! ������� �������, ��� � ���� ���� ����� ������ �������.";
			link.l1.go = "LizBegin_15";
		break;
		case "LizBegin_15":
			dialog.text = "�������, � ����� ��� ���� ����� ��������"+ GetSexPhrase("��","��") +" � ����������. �� ���������, ��� ���� ����� ����� ����!\n������, ����� ����� ����, ��� �� ����������� �� ���� ��� �� �����, � ���� ������� ��� ��������� ���������� ����� ���� �������. ��� ��� �� ��� ����, ��� �� ���������.";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "���� ����� ��� � ����, ��������.";
				link.l1.go = "LizBegin_haveSkull";
			}
			else
			{
				link.l1 = "�� ��� ��, ���� ����, � �����"+ GetSexPhrase("","�") +" ���� ��������, ���� �� � ������ � ����� ����. ������, �� ��������, ��� ���� ����� ��������� � ��������� ������?";
				link.l1.go = "LizBegin_seekSkull";
			}
		break;
		
		case "LizBegin_SeekSkull":
			dialog.text = "������ ���. � ����������� ������� ������� ������������.";
			link.l1 = "�������. ���� ��� �������� ��������� ���� �����, �� � ������ ����� ���������� ����, � ����������.";
			link.l1.go = "LizBegin_16";
			ChangeCharacterReputation(pchar, 3);
		break;
		case "LizBegin_16":
			dialog.text = "������, �������, � ���� ��� �����. ������� ���.";
			link.l1 = "�� �� �� ���...";
			link.l1.go = "exit";
			AddQuestRecord("MagicCity", "6");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("��","���"));
			pchar.questTemp.MC = "toSeekSkull"; //���� ������	
			NextDiag.TempNode = "LizCheckSkull";
		break;

		case "LizBegin_haveSkull":
			dialog.text = "��� ��� ������� ��� ���������?!";
			link.l1 = "��� ������ �������... ���������� ���, ��� ������ ������.";
			link.l1.go = "LizCheckSkull_1";
		break;
		//�������� ������
		case "LizCheckSkull":
			dialog.text = "�� �������� ���������� �����, �������?";
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = "�� � ����, ��������.";
				link.l1.go = "LizCheckSkull_Ok";
			}
			else
			{
				link.l1 = "��� ���. �� � ��������� ���� �����.";
				link.l1.go = "exit";
			}
		break;
		case "LizCheckSkull_Ok":
			dialog.text = "��� ���-���� ������� ��������� ���!";
			link.l1 = "��� ���� �������, ����� � ���... ��� ������ ������, ����?";
			link.l1.go = "LizCheckSkull_1";
		break;
		case "LizCheckSkull_1":
			dialog.text = "������ � ��� ���� ���������� ��� ������ ���������. ��� ����� �������� ������ '��������' �, ����������, ����� ��������� � ��������.";
			link.l1 = "��������� ��� �������, ��� �����, ��� ��� ��� ���������� �����, ������ ����� ������, ��� ����� �������� ������ ��������� �����. � ��� ������ - �� ��������...";
			link.l1.go = "LizCheckSkull_2";
		break;
		case "LizCheckSkull_2":
			dialog.text = "�������, ��� ����� ������ ��������� ����� � ����� � �������� '��������'. � ���� ������ ��������� ������ ��������� ���� �� ����.";
			link.l1 = "����� ����... � ��� ������ ��� ������?";
			link.l1.go = "LizCheckSkull_3";
		break;
		case "LizCheckSkull_3":
			dialog.text = "�� ����. ������ �����, ������� �������� �� ���� ����� �� �������. �������� ������������ ������, ���� ������ �� �� ����������.";
			link.l1 = "����. �� ��� ��, ������� ��������.";
			link.l1.go = "exit";
			SetDanielleInWorld();
			AddQuestRecord("MagicCity", "7");
			pchar.questTemp.MC = "toSeekQueen"; //���� ������	
			NextDiag.TempNode = "LizSeekQueen";
		break;
		case "LizSeekQueen":
			dialog.text = "�������, �� ����� ������ '��������'?";
			link.l1 = "��� ���...";
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = "�� ���-���� ����� ���������!";
				link.l1 = "��, ��� ��� �������.";
				link.l1.go = "LizOver";
			}
		break;

		case "LizOver":
			dialog.text = "�������, ��� � ���� �� ������!";
			link.l1 = "������, ��������, � ������ �� �� ������� ��� �����, ��� ������� ��� ������� - ���� ������?";
			link.l1.go = "LizOver_1";
		break;
		case "LizOver_1":
			dialog.text = "���, �� ������ ������...";
			link.l1 = "�������. �� - ���� ������ ����, ��� �������... ������, ������� ��������� �� ��� �� ������ ��������.";
			link.l1.go = "LizOver_2";
		break;
		case "LizOver_2":
			dialog.text = "����� ������. � �����, ��� �� ������� � ��� ������������, � �� ��� ������ ���� ������� ���� �������� � ���������� �����.";
			link.l1 = "��, � ����������.";
			link.l1.go = "LizOver_3";
		break;
		case "LizOver_3":
			dialog.text = "������, �������, ���� �� �� ����, � ������ �� ������������� ��� ���-������. � �������� � ������ �������� ��� ����, ��� ��������� ��� �� ����. ��� ��������� ������, ���������� ''������''. �� ������, � ��������� ������ ������� ������� ���������� ������� ����� ���������. �������, ��� �� ������� ��� ������ ������, ��� ���.";
			link.l1 = "���, � �� ���� ��� ������������ � ����� �����, ����? ���-�, � � �������� ����� ��� �������!";
			Log_Info("�� �������� ������ ''������''.");
			AddItems(pchar, "talisman4", 1);
			link.l1.go = "LizOver_4";
		break;
		case "LizOver_4":
			dialog.text = "�������, �� ���� ��. ��������, �������!";
			link.l1 = "��������, ��������.";
			link.l1.go = "exit";
			npchar.lifeDay = 30;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			NextDiag.TempNode = "LizOver_end";
		break;
		case "LizOver_end":
			dialog.text = "�� ���-�� ������, �������?";
			link.l1 = "�� ���, ������ ����������...";
			link.l1.go = "exit";
		break;
		//������� �� ��������
		case "DanAbordage":
			dialog.text = "������ ���� ���� �����!";
			link.l1 = "��, ����, ��� �� ����?! ������� ���������, ��� �� ���������� �� ����, ��� ����������� �����?!";
			link.l1.go = "DanAbordage_1";
		break;
		case "DanAbordage_1":
			dialog.text = "��� �� � ��� �������������. �� �����"+ GetSexPhrase("","�") +" �� ��� ������!";
			link.l1 = "��� ����� ���� ������� � ����������� �����, ����� �������� � ���� �� ����!.. ���������, ����� ���� ������ ���?";
			link.l1.go = "DanAbordage_2";
		break;
		case "DanAbordage_2":
			dialog.text = "��� ��� ���� ���.";
			link.l1 = "��� �� � ���� ������� ������ �������� �������... � �-�� �����"+ GetSexPhrase("","�") +", ��� ��� ������� � �������!";
			link.l1.go = "DanAbordage_3";
		break;
		case "DanAbordage_3":
			dialog.text = "�� ������ ��� ������ ��������?";
			link.l1 = "������ �� �� ��������� � �������� ������ �����. � ��, ��� � �������, �� ������� ������ ������� �������?";
			link.l1.go = "DanAbordage_4";
		break;
		case "DanAbordage_4":
			dialog.text = "�����! ��������� ��� ��������, ��� �� ���"+ GetSexPhrase("��","��") +"?";
			link.l1 = "���� ����� ������� " + GetFullName(pchar) + ". � ��������"+ GetSexPhrase("","�") +" ��� ������ ��� ����, ����� ����� ���������. ���������� ���, ��� ����������, ��� �� ��� ���� ��������� ���������� ���� �������.";
			link.l1.go = "DanAbordage_5";
		break;
		case "DanAbordage_5":
			dialog.text = "��� ��� ��� ��� ���! � � �� ��� ��� � �� �����, ��� ��� �� ������\n���� ���� �� ���� ����������� ������, � ������ ���������, � ���-�������. ��, ��������, ������, ��� � ���� �������� ��������. �������� �� ��, ��� ������� ��������, � ������ �������� ���� ����� ���� ��������� '��������'.\n"+
				"���-�� ��� �� �������� � ������ �������, �� ����� ���� ������. ��� ���� �������, ������ ������� ���� ��� �� �������. � ������� �����-�������� �� ������� ������-�� �������� �������. � ���������, � ������ �� ����, ����� �� ��� ��������� � ���������. ������� ����� ������� ���, � ������ ������� ����. ����������� �� ��� ���, ��� ������ - ����� ��� �������� ������.\n"+
				"�������, ��� ������ ���������� � ��������� �� �����. � ���-�������, �� ����� ���������� ������, � �������, ��� ��� �� ������� ������� �� ����� ����������, ��� � �������� ���. � �����, �������� ���������. �� ���� ������� ������ �������� �������� � ��������� ������� � �����. ��������, ��� �������� ���� ��������.\n"+
				"������ ������ ������������� �����. ��� ������ ������ �� ������ �������� � �����, ������ �� �������� ��������� ������� ������ � ������, �������� �������� �������, � �������� ������� �������, ��� � � ��� ������� ������ ��������. � �������.";
			link.l1 = "����� �������������� ����������� ��������.";
			link.l1.go = "DanAbordage_6";
		break;
		case "DanAbordage_6":
			dialog.text = "��� ������, ��� ������ ����������. �� � ����� �������� �� ����� ���� � ����. �� � ����� ������ �� ���� ������� ���� ���� ����������. �������, � ������� ������ ������� � ���� � ����. � ������ �������� ������ ��, ��� ��� ��������������.";
			link.l1 = "� ����� �� ������, ��� ��������� - �� �����..";
			link.l1.go = "DanAbordage_7";
		break;
		case "DanAbordage_7":
			dialog.text = "� �� �� ����. ����������� ���� ��� ����!";
			link.l1 = "�����������. ������, ��������� ���� �� ������ �� ���, �� � �� ������� ���-�������.";
			link.l1.go = "DanAbordage_8";
		break;
		case "DanAbordage_8":
			dialog.text = "��� ������!";
			link.l1 = "��� �������, �������, ��� �������� ������ ��� � �������, ��� �������� � ��� �����. � ��� ������ �����������.";
			link.l1.go = "DanAbordage_10";
		break;
		case "DanAbordage_10":
			dialog.text = "������� ��������! �� ��, ���� ����� ��� �������� �� ������\n��� ���, �������, ���� �� ������ ������� ���������, �� ������� ���!";
			link.l1 = "������, ��� ���� ��� �������. ��� ����� ���� ��������� ���������� ����� �������������� ������� � �������� ������� '��������', ��� � ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "DanAbordage_11";
		break;
		case "DanAbordage_11":
			dialog.text = "��������� �����? � ������ �� ����� ��������?";
			link.l1 = "�����, ��� ���. ��� ���������.";
			link.l1.go = "DanAbordage_12";
		break;
		case "DanAbordage_12":
			dialog.text = "�������, ��� � ���� ������������� ��� �� ��������� ������?";
			link.l1 = "����������� ������... ����, ������, � ���� ���� � ��� ������� ����������� - ����� �� ��� ��������. � "+ GetSexPhrase("�����","����� �� �������-������") +", ��� � ��. �������, �� �����������.";
			link.l1.go = "DanAbordage_13";
		break;
		case "DanAbordage_13":
			dialog.text = "�� ��� ��, ������ ���? � ��������.";
			link.l1 = "�������!";
			link.l1.go = "DanAbordage_14";
		break;
		case "DanAbordage_14":
			//������ ���� ���-�����  -->
			DeleteAttribute(NullCharacter, "capitainBase.Danielle");
			//<-- ������ ���� ���-�����
			AddQuestRecord("MagicCity", "8");
			pchar.questTemp.MC = "over"; //���� ������
			sld = GetCharacter(NPC_GenerateCharacter("DanielleOff", "Danielle", "woman", "Danielle", 30, PIRATE, -1, true));
			sld.name = "�������";
			sld.lastname = "�������";
			sld.greeting = "Gr_Danielle";
			sld.Dialog.Filename = "Enc_OfficerGirl.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 90, 60, 1, 60, 90);
			SetShipSkill(sld, 100, 10, 90, 80, 90, 20, 70, 80, 70);
			SetSPECIAL(sld, 6, 9, 9, 10, 8, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.HalfImmortal = true;  // ��������
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
	}
}

void SetDanielleInWorld()
{
	//������� �����
	ref sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danielle", "woman", "Danielle", 30, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "�������";
	sld.dialog.filename   = "Quest\MagicCity.c";
	sld.dialog.currentnode   = "DanAbordage";
	sld.greeting = "";
	sld.GenQuest.CrewSkelModeClassic = true; //������� - ������� 
	FantomMakeCoolSailor(sld, SHIP_ARABELLA, "��������", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	sld.Ship.Mode = "pirate";	

	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//� ������� ������ ����
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.city = "SantaCatalina"; //��������� �������, �� ����� ������� � �������� ������
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("������ Queen ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "������ '��������'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "Danielle"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = "MagicCity"; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "MagicCity"; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

