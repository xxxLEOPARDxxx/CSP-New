// ���������� ���� �2 �� �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "�� � ��� ��������.";
			link.l1 = "�����...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= ������� �������� �� ���������� =====================
            if (npchar.id == "Francisco")// ����� �2, ����� � ���������
            {
    			dialog.text = "��� �� "+ GetSexPhrase("��� �������, ������� �������","�� �������, ������� ��������") +" ������� �� ������� �� �����?";
    			link.l1 = "��, � ������ ��� �� ����.";
    			link.l1.go = "Step_S2_1";
            }
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))// ����� �2, ����� �� ���������
            {
    			dialog.text = "� ������, �� �������"+ GetSexPhrase("","�") +"!";
    			link.l1 = "����� ����� �� ��������� ����������� ��������, ���� �� ��������...";
    			link.l1.go = "Step_S2_6";
            }
            if (npchar.id == "Bandit" && CheckAttribute(pchar, "questTemp.State.Store"))// ����� �2, ������ �� 1-� �����
            {
    			dialog.text = "��� ���� ����� �����? ����������!";
    			link.l1 = "��, �������! ��� �� ������?";
    			link.l1.go = "Step_S2_11";
            }
			if (npchar.id == "JacowDeFonseka" && CheckAttribute(pchar, "questTemp.State.Store"))
			{
                dialog.text = "��� ��? ������ �� ���� ������? ����� �� �������? ��� �� ������, ��� � ��������?";
    			link.l1 = "����! ����, ���������. � ��� ��� ��������, ������ ����� � ������� �������� ���. �� ���� �� ������ ��������� ������ �����?";
    			link.l1.go = "Step_S2_14";
            }
			if (npchar.id == "PortMansBoy")  //����� �6, ��������� ���������� �����.
			{
                dialog.text = ""+ GetSexPhrase("�����","�����������") +", ���� ������ � ��� ��������� �����.";
    			link.l1 = "��, ����� ������. ��� �� ����� ��� ��������?";
    			link.l1.go = "Step_S6_1";
            }	//����� �7, ������ �������.
 			if (pchar.questTemp.State == "Sp7SavePardal_toAntigua" || pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")  
			{
                dialog.text = "������!!! ��� ��� ������ ���������� - �� �������� �������... � ��� ������"+ GetSexPhrase("��","���") +" ��...";
    			link.l1 = "��, ��� ���� � ������"+ GetSexPhrase("��","���") +", ����� ���� ������� ��������� ����������� �� ��� ������...";
    			link.l1.go = "Step_S7_1";
            }  //����� �8, ������� ������.
 			if (pchar.questTemp.State == "Sp8SaveCumana_toCumana")  
			{
                dialog.text = "����, ��������� ��������� ������!";
    			link.l1 = "���������, �������, ������� �� ����� �����������...";
    			link.l1.go = "exit";
				LAi_SetCurHPMax(npchar);
				QuestAboardCabinDialogExitWithBattle("");
            }
		break;

//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//*************************** ����� �2, ������� � ��������� �� ������ �� ��������� ***************************
 		case "Step_S2_1":
			dialog.text = "� ����, � ��� ����������� ���� �������, � ����, ��� ��� ����� �����������. ������ ������� ���������� ���� ���������� ���� �� ���� �����������, ��� ����� ������ ������.";
			link.l1 = "�� �������, ������ ������ � ����?";
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = "��������, ���, �� �� ������ ������� �� ����� - ���� ����� ���� ������� ������ �������� �����������, �� ����� ���������� ��������, ���� ���� �� ��������� ����� � ���� �����. �� �� �� ������, ��� ����� ���� ���������� ��������� � ���������������� ����������.";
			link.l1 = "��� ��� ����� ���� ���������� ���������, ���� ��� �������� �����������?!";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "��� ������ � ���� �� �������, ��� � �� � ����. ���������...";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���� ����� � ��������. �� � ��� � ���� ����� ��������?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "��������� �� ���-���������.";
			link.l1 = "������� ���, ���������. ����� ��������.";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "Inquisition_afterFrancisco";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            DialogExit();
		break;
 		case "Step_S2_6":
			dialog.text = "������ ���... � ������ �� ���� ������?";
			link.l1 = "������� ���� ����������, �������� ������� �����. ������ �����?";
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = "��� ���� ������! � �� ��� ������ ��� ����� �� ����, ����� ����� ���������! ��� �� ���� - ����������� ������!";
			link.l1 = "��� ���� �� ��������, ���� �������� ������ ������� � ������ ������...";
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = "��, ��� �����... ������, ���-�� ���� ��� ��� ����� ��������... � ���� ��� ����� �� ����?";
			link.l1 = "�� ���� - ������. ���-��� ����� �� ������ ����. �������� ���� � ���� � �����, ��������� � �����, � �����, � ������������ ������������ ���������... � �� ���� � ����� ������� ���-��� �������.";
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = "�� ������ ������� � ���� �������� ���������. �������, ��� �� ����"+ GetSexPhrase("","�") +" ����.";
			link.l1 = "�������� ���������, ������� �� ������� ����, ��������... �� � ��� �� ����.";
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
            AddQuestRecord("Spa_Line_2_Inquisition", "8");
            pchar.quest.Inquisition_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Jamaica", true);
            QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
 		case "Step_S2_11":
			dialog.text = "����������, ���� �������. ���� �������?!";
			link.l1 = "��, ���-�� ��� �� ���... � ������ �� ����, ���� �� �� �������� ��� �� ���� ������. � ��� ��� �� ����� �������? �� �� ���� �� ����� �� ������� ��������� � ��� � �����?";
			link.l1.go = "Step_S2_12";
		break;
 		case "Step_S2_12":
			dialog.text = "��-�-��... ���� ���� �� ��� ����, �������"+ GetSexPhrase("","��") +"...";
			link.l1 = "�� ���� ���������� ����� ���� �����...";
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_S2_14":
			dialog.text = "�������, �� ����. ��� � �� ��������. ������� �� ������������ � ���� ��� �� ��������, �� � ����� � ����� �� ������. � ������, ��� ��� ������� ��������� ���� ����� ������ � ���� �� ���, ��������, ��� �������� �� �������.\n"+
                          "�� ����� ������� �� ��� ������ ������ ������� ����? � �� ��� � �� �������, ��� ��� �����.";
			link.l1 = "����� " + GetFullName(pchar) + ", � ����� �������. �� ���... ��� ������� ���� � ����� �����, �� ����� ������������.";
			link.l1.go = "Step_S2_15";
		break;
 		case "Step_S2_15":
			dialog.text = "�� ���� ���������� ����������, ��, ����, ��� �� ��������� � ����������� � ����� ������, � �����, ��� �� ������� �������"+ GetSexPhrase("",", ���� � �������") +". ���� ��������� ��� �� ����� ���������.\n"+
                          "��� �� ���� ������ �� �������. � �� ������ ����������, � ���� ������ ������� ���. ���� � ���, ��� ���� ������ ������� ������� ������������ ��������� - ���������� �� ���� ���������.";
			link.l1 = "�������?";
			link.l1.go = "Step_S2_16";
		break;
 		case "Step_S2_16":
			dialog.text = "��� ������� � ��� ���-�� 20 ��� ����� ������ � �� ���������� - �������� ������.";
			link.l1 = "���-�� � ��� ������"+ GetSexPhrase("","�") +" ��� ���...";
			link.l1.go = "Step_S2_17";
		break;
 		case "Step_S2_17":
			dialog.text = "��� ���� ��. ��� ���, ������� �� ����� �� ���� ����������, �� ��������� �� ��������. ������� �������� � ���� �������� �� �������� ����������, ����� �� ������ �������� �� �������. ��� �������� �� ��������� ����� � ���� ����� ���������� �������, ����� ���� �������� ������. ������� ��������� �� ��� �� ����� � ������� � �����. �� ��� �� ��� ������ ����� ����������.";
			link.l1 = "��� ���?";
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = "�� ����� � ������� ����� - � ���. ���� �� ����� - ���������� ���������. ������ ����� ��� ��� ������ � �� ������. � ����� ��� ������ ��� ������� �����. �� �������� ���?";
			link.l1 = "��� ��-������, ������� ����� ������ ��� �����?";
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = "��� ��������! �� ������ �� �� ���� �����������?";
			link.l1 = "������ ������������ �������� - ������ ���� ������� ��������� ��������... �� � ��� ������ �� �����"+ GetSexPhrase("","�") +", ��������� �� ���������������.";
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = "������� ���!";
			link.l1 = "���� �� �� ���.";
			link.l1.go = "Step_S2_21";
		break;
 		case "Step_S2_21":
 		    LAi_SetPlayerType(pchar);
            AddQuestRecord("Spa_Line_2_Inquisition", "12");
            AddQuestRecord("Spa_Line_2_Inquisition", "13");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
            pchar.questTemp.State.SeekBible = 1; //���� �� ����� ���������
            LocatorReloadEnterDisable("Shore3", "reload2_back", true); //��������� ��� ����� ������
            DialogExit();
		break;
//*************************** ����� �6, ����� � ��������� ���������� ����� ***************************
 		case "Step_S6_1":
			dialog.text = "�����, ������� �� ��������, ������� ����� �� ����� �������. ��������, ����������� ������, ������ ��������� � �'�������, �� ������ ��� ��������� ���� ������ �� ������ �� ����������.";
			link.l1 = "�����������! ������� ���� �� ������.";
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = "�� �� �� ���. ����������� ���������� �����.";
			link.l1 = "��, ����������� �����������.";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "3");
			bDisableFastReload = true; //��������� ���� ������
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.Sp6TakeMess_Interception.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_Interception.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.Sp6TakeMess_Interception.win_condition = "Sp6TakeMess_Interception";
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
            DialogExit();
		break;
//*************************** ����� �7, ����� � ������� ��������� ��� �������� ***************************
 		case "Step_S7_1":
			dialog.text = "�� ��� ��, ���� ��� �������... ��������� - ��������� ����������.";
			link.l1 = "� ���������� �������������...";
			link.l1.go = "exit";
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
		break;


    }
}


