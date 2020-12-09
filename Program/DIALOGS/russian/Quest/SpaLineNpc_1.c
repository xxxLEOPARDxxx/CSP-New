// ���������� ���� �1 �� �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
            //����� �1, �������� ���� �������.
            if (npchar.id == "SpaPrisoner1" || npchar.id == "SpaPrisoner2" || npchar.id == "SpaPrisoner3")
            {
    			if (pchar.questTemp.State == "SaveFromMorgan_toPrison")
    			{
                    dialog.text = "������"+ GetSexPhrase("","���") +", ��� ��?";
        			link.l1 = "� ����� ���������, ������ � �������� ���, � �� �������� �����. ��� ��� �������� ���������� �������?.. ���������������� �, �� ��������� ��������, ������������� � ����� �������. ���� ������ - ��������� �� ����� ������� ������. ����� ��������� ����� � ������ ��������� ���������, ������� �������� ��������, ��� ��� ��� ����� �����. � �������, ��� ��� �������?";
        			link.l1.go = "Step_S1_1";
                }
                else
                {
                    dialog.text = LinkRandPhrase("������� ������� ���� �������!", "���� �� �� �����, ��� �� ���� ��� ������...", "������� ������� �������-�����������, �� �� ����� � ���...");
        			link.l1 = "��, ��... �� ����� ���, �� ���� �������� ���� �� �� ��������� ������...";
        			link.l1.go = "exit";
                }
            }
            if (pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")// ����� �3, ��� ��������� � ����� �� ��������
            {
    			dialog.text = "�� "+ GetSexPhrase("�������, ��������� ��������","��������, ��������� �������") +".";
    			link.l1 = "����� ������, ��� �� ����� �������. � � ���� �� ������ ���, � � ������������.";
    			link.l1.go = "Step_S3_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toTortuga")// ����� �4, ����� �� ������ �'����� ���������������.
            {
    			dialog.text = "��� �� ������, "+ GetSexPhrase("�����","�����������") +"? ������� ��� ����.";
    			link.l1 = "�������...";
    			link.l1.go = "exit";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre")// ����� �4, ����� �� ������ �'�����
            {
    			dialog.text = "��� �� ������, "+ GetSexPhrase("�����","�����������") +"?";
    			link.l1 = "��� ����� ���� ������, ���� �'�����.";
    			link.l1.go = "Step_S4_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre_1")// ����� �4, ����� �� ������ �'�����
            {
    			dialog.text = ""+ GetSexPhrase("�����","�����������") +", ��� ����� ���������������!";
    			link.l1 = "��, � �����.";
    			link.l1.go = "exit";
            }
            if (npchar.id == "AnryDEstre")// ����� �4, ����� � ����� �'�����
            {
    			dialog.text = "���� ������, �������� ���������� ����������� - ������ �� ����������� ����?!!";
    			link.l1 = "��� ����� ���� ������ ���������� � ����, ����� ���� ��������, �����...";
    			link.l1.go = "Step_S4_2";
            }
            if (npchar.id == "LaVega_Comendant") // ==>  ����� �5, ������ ���������� ��� ������ �� ����
            {
    			dialog.text = "��, ��� �������, ����������� ������?";
    			link.l1 = "������� �� �������� ������ ���� � �����������. �� ��� ������ ����������, � ��������� ����� �������� ������ ���������� �����������!";
    			link.l1.go = "Step_S5_1";
            }
            if (npchar.id == "Boozer") // ==>  ����� �6, ����� � ������� � �������
            {
    			dialog.text = "�?.. �� �� ����?!";
    			link.l1 = "�� ������ ����������. ������ �����"+ GetSexPhrase("","�") +" ���� ���� ��������� ����� - �� ���� ���������, � ��� �������� ���������...";
    			link.l1.go = "Step_S6_1";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_waitMessanger") //����� �6, ����� � ����������� ��������
            {
    			dialog.text = "��� �� ������?";
    			link.l1 = "� - ���������� ���� �������-����������� �������. ��� ���������� ������������ � ����. ������� ������� � �������, ����������...";
    			link.l1.go = "Step_S6_8";
    			link.l2 = "� ����, ����� �� ����� ��� ��������������� ���������. � ����� ��-������, � �� ������ �����...";
    			link.l2.go = "Step_S6_11";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_Action") //����� �6, ����� � ����������� ��������
            {
    			dialog.text = "��� �������, ��� ����� ���� ������� ���������� ���� ����������. ��� �� � ��� ��� �����?";
    			link.l1 = "��� � - �������, � ����� ��� ���� ������.";
    			link.l1.go = "Step_S6_13";
			}
            if (npchar.id == "OurCaptain_1") //����� �7, ����� � �������� ��� �� ������� �� �����
            {
    			dialog.text = "���� ������, �� ����� ��� ��������! ���� ������� �������, ������ ���!!!";
    			link.l1 = "������.";
    			link.l1.go = "Exit";
			}
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_GoodWork") //����� �7, ����� � �������� ��� �� �������
            {
    			dialog.text = "������, �� ������"+ GetSexPhrase("��","���") +" ����� ��� ������ �������! ���� �� ����, ��� �� � ����� ��� ����� ������... ����� ���, ���� � ������ ����� ���������?";
    			link.l1 = "���� ����� " + GetFullName(pchar) +". � ������ ���� � ���� �� ������� ��������� ������-�-������. ��� ����� ��������, ��� ������� ����������� �������� ����� ���������� ��� ��� � �����.";
    			link.l1.go = "Step_S7_1";
			}		
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_2GoodWork") //����� �7, ����� � �������� ��� �� �������
            {
    			dialog.text = "����������, � ������ �� ����...";
    			link.l1 = "������"+ GetSexPhrase("��","��") +"...";
    			link.l1.go = "exit";
			}				
            if (npchar.id == "SpaTalkOfficer" && pchar.questTemp.State == "Sp10Maracaibo_TalkWithOfficer") //����� �10, ����� c ����� �� ������
            {
    			dialog.text = "������!!!";
    			link.l1 = "�������, ��������! ���� ��� �� ��� ��������?";
    			link.l1.go = "Step_S10_1";
			}

		break;
//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* �������� ���� �������. ����� �1 **********************************
 		case "Step_S1_1":
			dialog.text = "��, ������"+ GetSexPhrase("","���") +". ������� � �� ������ ��� �������!";
			link.l1 = "�����! � ������ ������������...";
			link.l1.go = "Step_S1_2";
		break;
 		case "Step_S1_2":
            AddQuestRecord("Spa_Line_1_SaveCitizens", "2");
			pchar.questTemp.State = "SaveFromMorgan_OutOfPrison";
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto12");
                LAi_SetActorType(sld);
                LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
                AddPassenger(pchar, sld, false);
                SetCharacterRemovable(sld, false);
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
//********************************* ������ �� ����������. ����� �3 **********************************
 		case "Step_S3_1":
			dialog.text = "��� �� �����������?";
			link.l1 = "����������� ������� � ����������� ������� �� �����.";
			link.l1.go = "Step_S3_2";
		break;
 		case "Step_S3_2":
			dialog.text = "�� ���� ������, ��� ���?";
			link.l1 = "����� ������ ������� � ������ ����������, ������� �����. ��� ��� ���� �������.";
			link.l1.go = "Step_S3_3";
		break;
 		case "Step_S3_3":
			dialog.text = "��� ���������, �������, ��� ������. ����� �� ��� ������� � ���, ��� �������...";
			link.l1 = "��������. �� � ������ ��� ����, � �������� ��� ���� � �����������.";
			link.l1.go = "Step_S3_4";
		break;
 		case "Step_S3_4":
 		    pchar.questTemp.State = "TakeRockBras_RockTaken";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "5");
            pchar.quest.TakeRockBras_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Maracaibo", true);
		    QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
//********************************* ������������� ��������. ����� �4 **********************************
 		case "Step_S4_1":
			dialog.text = "�� ����� �� �����, ����� ����� ����. �� ����-�� ����� ���������, �� ��� ��������� ���������� �������� ���������� � ������ �����. �������� �� �������� ������ � ������� �� ����� �����. ��� ��� ���� ������ ������� ��� - ������������.";
			link.l1 = "������, �������...";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toDEstre_1";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1.location = "Tortuga_town";
			pchar.quest.Sp4Detection_Race_1.win_condition = "Sp4Detection_Race_1";
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
 		case "Step_S4_2":
			dialog.text = "������, �������... � ��� ���� ����� �������������?";
			link.l1 = "���� ����� " + GetFullName(pchar) + ". � ����"+ GetSexPhrase("��","��") +" ������ � ���, ��� ����� ����� ����, ������� �� ��������� ����� �'�������? ";
			link.l1.go = "Step_S4_3";
		break;
 		case "Step_S4_3":
			dialog.text = "��, �����"+ GetSexPhrase("�","���") +", ����� ���� ��� �� ����, ���� �����. ��� ����� ��������� ��� ��� ������ ��������...";
			link.l1 = "� ��� ����. �� ��� �� �����, � ��� ��� ������ ���: �� �������� �� ����� ���� �����, � ������ ��� ������, ���������� ������ ���� ����� �������� �� �����?";
			link.l1.go = "Step_S4_4";
		break;
 		case "Step_S4_4":
			dialog.text = "���� ��� ��� � ����, �� ���?";
			link.l1 = "�����, ������, � ��������"+ GetSexPhrase("","�") +" ���� ����� ���.";
			link.l1.go = "Step_S4_5";
		break;
 		case "Step_S4_5":
			dialog.text = "������ ������������� �����������. �� � ������ �� ����� - � �����? ����� ���, ��������� ��� �� �������� ������, � �� �������� �������� �����. �� ���������, ��� � ���������, ��� ������ ����� ������ ������� ������ ��������� �����.";
			link.l1 = "������� ������ - ������ �����. �� ��������� �� �� ������������� ��� - ������� ������� �������. ��� ���� ����� ���� �������!";
			link.l1.go = "Step_S4_6";
		break;
 		case "Step_S4_6":
			dialog.text = "�-�-�, �� �� ������ ����������� �� ���� ���� �����������, ���� ������, �������� ��������� �������� � �������� �� ��� ����... � ���������. ��� ��� �� ��, �����"+ GetSexPhrase("�","���") +"?";
			link.l1 = "� ��������� �����, � ������ ��������� �������������� �������� ���������� ������ � ������������ ��� �����. ��, ������ �����"+ GetSexPhrase("","�") +" - �� ��������� �������-����������� ������ ���� ��������� ������-�-�������.";
			link.l1.go = "Step_S4_7";
		break;
 		case "Step_S4_7":
			dialog.text = "���, ��� ������ ��� ��� ����, � � �������� ���� ���������� ��� �� ��� ����. � ������, ������"+ GetSexPhrase("","���") +"!";
			link.l1 = "�������������, ������!";
			link.l1.go = "Step_S4_8";
		break;
 		case "Step_S4_8":
            LAi_SetPlayerType(pchar);
			pchar.questTemp.State = "Sp4Detection_toDEstre_2";
            LAi_SetHP(npchar, 300, 300);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Sp4Detection_YouWin");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ����������� �� ����. ����� �5 **********************************
 		case "Step_S5_1":
			dialog.text = "����, "+ GetSexPhrase("��������� ���","��������� �����") +"! ������ �������� ������ ������� ���� �����...";
			link.l1 = "��, ���� ����������� �� ���� ����...";
			link.l1.go = "Step_S5_2";
			AfterTownBattle();
		break;
 		case "Step_S5_2":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, LAI_GROUP_TmpEnemy);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Sp5LaVegaAttack_AfterFight");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* �������� ���������� ���������. ����� �6 **********************************
 		case "Step_S6_1": //�����
			dialog.text = "�-�-�, ��� ���� ������! ����� ������...";
			link.l1 = "������� ���-��� ������ ��� ����, ����� �������� ���� ������.";
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = "�-��, � � ���� �����������... ��� � ������ �������?";
			link.l1 = "����� ��������� ����� �� ���������� ������ ��������� � ���������� � ����, �� �������. ���� ����� �������� ���, ��� �, ���������� ���� �������-����������� ����������, ��� ��� � ������� �������, �������.";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			dialog.text = "� ������� �� ��� ����?";
			link.l1 = "��, �� �� ����� ������ ����� ������������.";
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
			dialog.text = "��� ����� ������ �� - � � ��� ������. � ��� � ����� ��� �� ���������� - ������ ��������...";
			link.l1 = "����� ���� ������. � ���������� �� ����, � ���.";
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
			dialog.text = "�� �� ��������, ������ ������� ��������� - � ��� ���� �����...";
			link.l1 = "���������� �� �����������, �� �������� ���������. � �����, � ��� ��������� � ������� ������� �������!";
			link.l1.go = "Step_S6_6";
            AddMoneyToCharacter(pchar, -100);
		break;
 		case "Step_S6_6":
			pchar.questTemp.State = "Sp6TakeMess_Action";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "4");
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1.location = "Tortuga_tavern_upstairs";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition = "Sp6TakeMess_WaitMessanger";
			pchar.quest.Sp6TakeMess_Interception.over = "yes";
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", true);
            DialogExit();
		break;
		//=====>>> �������� ��� ������� ����� ��� � ������.
		case "Step_S6_11": 
			dialog.text = "��, �� �����, ��������...";
			link.l1 = "����!";
			link.l1.go = "Step_S6_7";
		break;
 		case "Step_S6_7":
			LAi_RemoveCheckMinHP(sld);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
		break;
 		case "Step_S6_8":
			dialog.text = NPCStringReactionRepeat("���� �� ������ ��� ���-���� �������, �� �������� ���������� � �����.",
                          "����� ��? � �� ������ ����, ��� ������ �� �����!", "�� ���, �� ���� ������"+ GetSexPhrase("","�") +"... ������, ����� �"+ GetSexPhrase("��","��") +", ��� �����"+ GetSexPhrase("","��") +"!", "none", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������� ������� � �������...", "����������...", "�, ���?!", "none", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_9", "Step_S6_12", "Step_S6_7", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_9":
			dialog.text = "�� � ����� ������� � ���� �� ���������. ��������, ��� � ��� �� ���?";
			link.l1 = "������... ��...";
			link.l1.go = "Step_S6_10";
		break;
 		case "Step_S6_10":
			dialog.text = "�������... �, �������, ������ � ����� ���� ������� � ����� �������� ���������... �������, ������ ��� �� ��� ������ ����� �������� ���� �����.";
			link.l1 = "��...";
			link.l1.go = "Step_S6_12";
		break;
 		case "Step_S6_12":
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
            LAi_Actor2WaitDialog(npchar, pchar);
            DialogExit();
		break;
		//=====>>> �������� ������� � ������� �������.
 		case "Step_S6_13":
			dialog.text = "��� ��������������� ���������, �� ������ ��������...";
			link.l1 = "� ����, �� ���� �� �� ������ ��� �� �����������, �� ��� �������� ����� �� � ������ ����. ������� � ����� ��� ������.";
			link.l1.go = "Step_S6_14";
		break;
 		case "Step_S6_14":
			dialog.text = "� �����, � ������! �������, � ����� �������� �� ���� ����� �����...";
			link.l1 = "��, �� ��� ������...";
			link.l1.go = "Step_S6_15";
		break;
		case "Step_S6_15":
			bDisableFastReload = false; // ������� ��������.
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", false);
			LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* �������� �������. ����� �7 **********************************
 		case "Step_S7_1": 
			dialog.text = "������, � ��� �� ������ ���, ��� � ����. ����� ������, � ���� ����� ����������� ������������� ���.";
			link.l1 = "�������. �� ��� ��, � ����"+ GetSexPhrase("��","��") +" ������������ � ������ � �������-�����������. ����� �������� ��� �� ������� ���������� ����.";
			link.l1.go = "Step_S7_2";
		break;
 		case "Step_S7_2":
			dialog.text = "�, �������, ��� ��������� � ���� �����. ��������, ��� �������...";
			link.l1 = "����� ���� �����, �������. ������.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp7SavePardal_2GoodWork";
		break;
//********************************* �������� �������. ����� �7 **********************************
 		case "Step_S10_1": 
			dialog.text = "���������!!";
			link.l1 = "��� �� ������?";
			link.l1.go = "Step_S10_2";
		break;
 		case "Step_S10_2": 
			dialog.text = "� ������, ��� � ������ �������� ������� ���������� �������! ������, ����� ���! �� ��� �� ���������� � ��������� �����...";
			link.l1 = "������, ��� � ��� ������ �������...";
			link.l1.go = "Step_S10_3";
		break;
 		case "Step_S10_3": 
			dialog.text = "���?.. �-�-�, ����� ������ ������"+ GetSexPhrase("","���") +", ��� ����� ��������� �������-�����������...";
			link.l1 = "���������, ������.";
			link.l1.go = "Step_S10_4";
		break;
 		case "Step_S10_4": 
			pchar.questTemp.State = "Sp10Maracaibo_toGovernor";
			AddQuestRecord("Spa_Line_10_Maracaibo", "2");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("","�"));
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", true);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", true);
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
            DialogExit();
		break;




    }
}
