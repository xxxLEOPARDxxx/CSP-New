// ���������� ���� �1 �� ���������
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
            if (npchar.id == "Bandit2" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")// �������� �� ��������, �������� ������
            {
    			dialog.text = "����������, ���� ���"+ GetSexPhrase("","�") +"...";
    			link.l1 = "���� ����� "+ GetFullName(pchar) +". � ��� ������ ������� ���������.";
    			link.l1.go = "Step_H1_1";
            }// ����� ����������� ��������, ����� ����� � �����������
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")
            {
    			dialog.text = "�������, �� ������ ��� �����! ��� �� � ��� ����� �������?";
    			link.l1 = "���� ����� "+ GetFullName(pchar) +". � ��� ������ ������� ���������.";
    			link.l1.go = "Step_H1_3";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_GoToVillemstad")
            {
    			dialog.text = "� ���������� ��� �� ������ ������������� �����������. � ���������� ������� �� ��, ��� �� ��� ������� ��������� � ���-�������. � �������, �� ���������� ���.";
    			link.l1 = "� �������������.";
    			link.l1.go = "Step_H1_6";
            }// ����� �3, ��������� � ������.
            if (npchar.id == "Alan_MacLine" && pchar.questTemp.State == "WormEnglPlans_SaveOfficer")
            {
    			dialog.text = "��, � ���� ��� �������... ��� ��?";
    			link.l1 = "� ����"+ GetSexPhrase("��","��") +" ���������� ���!";
    			link.l1.go = "Step_H3_1";
            } // ����� �5, ����� � �� ���� � ������ ���������
            if (npchar.id == "Talker" && pchar.questTemp.State == "ThreeFleutes_toLaVega")
            {
    			dialog.text = "��, � ��������� ����� �� ������"+ GetSexPhrase("��","���") +" � ���... �������� ����.";
    			link.l1 = "��� ����?!";
    			link.l1.go = "Step_H5_1";
            } // ����� �7, ���������� �� �������
            if (npchar.id == "Stranger_HL7" && pchar.questTemp.State == "DelivLettTortuga_SnapMeeting")
            {
    			dialog.text = "�������, �� �� ��� ��"+ GetSexPhrase("��","��") +", ��� ������"+ GetSexPhrase("��","��") +" �������-����������� �������?";
    			link.l1 = "� ��� �� ������?";
    			link.l1.go = "Step_H7_1";
            } // ����� �7, ������� � ������� �������
            if (npchar.id == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_toStranger")
            {
    			dialog.text = "�, ��� � ��, �������...";
    			link.l1 = "�� ������ ���� ������? ��� ��?";
    			link.l1.go = "Step_H7_4";
            }
            if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
            {
    			dialog.text = "���������! �� ����� ����� ������� ����, �� ��� ��� ������...";
    			link.l1 = "����������, �������. ����� ��������� ���� ������������� ������. ������ ������ ��� ����� ��������� �� ���� ��������.";
    			link.l1.go = "Step_H7_6";
            } // ����� �8, ����� ���� �������
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toAaron")
            {
    			dialog.text = "��� ������ ���, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". ����� ����������?";
    			link.l1 = "������, � ��������������"+ GetSexPhrase("","�") +" � ���� ������������ ������� �����������.";
    			link.l1.go = "Step_H8_1";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toBermudes")
            {
    			dialog.text = "� ����������� ������ ������ ������� � �������.";
    			link.l1 = "� ��������� ����, ���������� �����...";
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafIsDead")
            {
    			dialog.text = "� ����������� ������ ������ ������� � �������.";
    			link.l1 = "������, ��� ������� ��������, ��� �������� ������� ������������ �����. ����� ����������� ����� ����� �� ����. ������, �����, ��� ��� �� �����. ����� � ������"+ GetSexPhrase("��","���") +" �� ���� � ������� ���������, �� ��� ��� � ����� ������ ��������� ��������. ��� �� ������� ������ ��� ������, ��� ����� ������ ������ � ��������. �����, ��� ��� ���, ����� ����� ������ ������ ����������.";
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafDieHard")
            {
    			dialog.text = "� ����������� ������ ������ ������� � �������.";
    			link.l1 = "������, ��� ������� ��������, ��� �������� ������� ������������ �����. ����� ����������� ����� ����� �� ����. ����� � ���"+ GetSexPhrase("��","��") +" ��� ���� ���������, �� ��� ��� � ����� ������ ��������� ��������. � �� ����"+ GetSexPhrase("","��") +" ����� ������ �� �����, ���� ���� ������� �������. ��� �������� �������� ���� ���.";
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_BadResult")
            {
    			dialog.text = "��� ����� ������ ��� �������. ������������� � ����������.";
    			link.l1 = "������, ������.";
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_WeWon")
            {
    			dialog.text = "� ����������� ������ ������ ������� � �������.";
    			link.l1 = "��� ������ �� ������� ��������. � ��������"+ GetSexPhrase("","�") +" ��������� ������.";
    			link.l1.go = "Step_H8_12";
    			link.l2 = "��� ���, ������, ����� ��������... �� ����� �� ���"+ GetSexPhrase("��","��") +" ����... ������ �������� ������...";
    			link.l2.go = "exit";
			}			
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_IHaveMap")
            {
                dialog.text = "� ����������� ������ ������ ������� � �������.";
    			link.l1 = "��� ������ �� ������� ��������. � ��������"+ GetSexPhrase("","�") +" ��������� ������.";
    			link.l1.go = "Step_H8_12";
				if (CheckCharacterItem(pchar, "Bible"))
				{
           			link.l2 = "��� ������� ������ �����-�� �����. �� ����, �� �� ���, ��� �� �����, �� ����� �� ������� ����� ����.";
        			link.l2.go = "Step_H8_13";
                }
                else
                {
        			link.l2 = "� ���� �� �����"+ GetSexPhrase("","�") +" ��������� �����, �� � �������� � ������. ��� ����� ���������...";
        			link.l2.go = "exit";
                }
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_GoodResult")
            {
    			dialog.text = "� � ��� ���� ������ ������� �� ���...";
    			link.l1 = "���, �������...";
    			link.l1.go = "exit";
            }

        break;

//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* ������ ��������, �������� ������. ����� �1 **********************************
 		case "Step_H1_1":
			dialog.text = "� �� ������ ���� - ����������, �� �� ������ �����.";
			link.l1 = "������-��, � ������ ������ �������, ������ ������� ����� ������. � ��� �� ���� �����, ������, ���� ���������...";
			link.l1.go = "Step_H1_2";
		break;
 		case "Step_H1_2":
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_H1_3":
			dialog.text = "��� �.";
			link.l1 = "���� ������� �� ���� ����� ���������, � ����"+ GetSexPhrase("��","��") +" ��������� ��� � �������. � ��� ������ � ����� ���� ��� ��������� ����?";
			link.l1.go = "Step_H1_4";
		break;
 		case "Step_H1_4":
			dialog.text = "������, ��� ��� ������� ����. ���� � ���, ��� � ��� �������� �� ������ ��� ������ ����, � ����� ��������� � �����, � ���� �� ������� ��� ���, ������ ��� ���������. � ���� ������ � �������� ������� � ������ � ��� �������, ���� �� ��������� ������� ������ ��������� ��� ������ ����.";
			link.l1 = "�� ��� ��, ��� ������, ��� ������ ���������. ����������� � ����� ���������� �� ���� ����� ���������. ��������� ���� ���, ������� ����������.";
			link.l1.go = "Step_H1_5";
		break;
 		case "Step_H1_5":
            AddQuestRecord("Hol_Line_1_Chumakeiro", "2");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("��","��"));
	AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex1", GetSexPhrase("","�"));
		    pchar.questTemp.State = "SeekChumakeiro_GoToVillemstad";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1.location = "Villemstad_townhall";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition = "SeekChumakeiro_intoResidence";
			DialogExit();
		break;
 		case "Step_H1_6":
			dialog.text = "� ������ ����� ��� ������� �� ���� ��������� �������������� - 30000 �����.";
			link.l1 = "������������ �� ����, �������.";
			link.l1.go = "Step_H1_7";
		break;
 		case "Step_H1_7":
            LAi_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 30000);
			RemovePassenger(pchar, npchar);
			AddQuestRecord("Hol_Line_1_Chumakeiro", "3");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("","�"));
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DialogExit();
		break;

//********************************* ������ ���������� � ������. ����� �3 **********************************
 		case "Step_H3_1":
			dialog.text = "�� ��, �� ��� �� �������! ���� ������ �� ����� �������� � ���� ������� � ����� ������� � ���� ������?";
			link.l1 = "��� ����� ���-��� ������ �� ���.";
			link.l1.go = "Step_H3_2";
		break;
 		case "Step_H3_2":
			dialog.text = "���� � ����� �������. ������ ������� ������� ������� ����� �������������� ����� ��� ����� ������������� ������.";
			link.l1 = "� ������, ��� ������ ���� �� �������. �� ������� � ����"+ GetSexPhrase("��","��") +" �������� ����������� ��� ����������. � ���� �����, ���� �������� ������� ������� �������.";
			link.l1.go = "Step_H3_3";
		break;
 		case "Step_H3_3":
			dialog.text = "����� ���� � ��������� ����������� ���� �����.";
			link.l1 = "���� ������, ��� ��������� ������ �� ���! � ����� ���� �����: �� �������� � ������ ���� ���� ������. ������.";
			link.l1.go = "Step_H3_4";
		break;
 		case "Step_H3_4":
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(characterFromId("Henry Morgan"));
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "14");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("","�"));
 		    pchar.questTemp.State = "WormEnglPlans_GoodRusultWorm";
            ChangeCharacterAddressGroup(npchar, "SentJons_prison", "goto", "goto23");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
            DialogExit();
		break;

//********************************* ����� � �� ���� � ������ ���������. ����� �5 **********************************
  		case "Step_H5_1":
			dialog.text = "������� ������ �� ���. ������ �������� ������ �������.";
			link.l1 = "��� ��� ��! ���� �������, ������� ��� ������.";
			link.l1.go = "Step_H5_2";
		break;
 		case "Step_H5_2":
			chrDisableReloadToLocation = false;
 		    AddQuestRecord("Hol_Line_5_ThreeFleutes", "2");
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1 = "location";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1.location = "Hispaniola1";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition = "ThreeFleutes_BackToCuracao";
            DialogExit();
		break;

//********************************* ����� � ����������� �� �������. ����� �7 **********************************
  		case "Step_H7_1":
			dialog.text = "� ������� ��� ���� ���������� ���� ����������.";
			link.l1 = "� ��� ���� ����� �� ����?";
			link.l1.go = "Step_H7_2";
		break;
  		case "Step_H7_2":
			dialog.text = "������� ������������ �������-�����������, ��� ���������� ���������� � ��� ������������.";
			link.l1 = "��... �� ��� ��, ������.";
			link.l1.go = "Step_H7_3";
		break;
  		case "Step_H7_3":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "DelivLettTortuga_toStranger";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = GetCharacter(NPC_GenerateCharacter("AntonioDeBarras", "officer_9", "man", "man", 40, SPAIN, -1, true));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	sld.name 	= "�������";
        	sld.lastname = "�� ������";
        	LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_WARSHIP, "��������", CANNON_TYPE_CULVERINE_LBS32, 100, 100, 100);
            FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol5", 150);
          	ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
            DialogExit();
		break;

        case "Step_H7_4":
			dialog.text = "���� ����� �������, �� ��� ���, � �����. � ����,\n"+
                          "�� � ��! �� ������, ��� � ��� ���������!";
			link.l1 = "�?..";
			link.l1.go = "Step_H7_5";
		break;
  		case "Step_H7_5":
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", false);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
            LAi_SetActorType(npchar);
            LAi_SetActorType(pchar);
            LAi_ActorTurnToLocator(pchar, "reload", "reload1_back");
            DoQuestFunctionDelay("DelivLettTortuga_Digress", 1.0);
            DialogExit();
		break;

        case "Step_H7_6":
			dialog.text = "� ��� ��� ����� �� �������?";
			link.l1 = "�� ������ �������� �� �������, �� ������ �������� ����� � ���� �������� � ���� �� ������. ������ �������� ������� - �� ����� ������� �� �����. ������� ����?";
			link.l1.go = "Step_H7_7";
		break;
        case "Step_H7_7":
			dialog.text = "��... ������, � ������ ���������� ������ ��� ���������� ����� ��� ������. ��� ��� ������� ���� �������, � ��� �����.";
			link.l1 = "������ ����� ����: ��� �� � ��� ����� �� �������?";
			link.l1.go = "Step_H7_8";
		break;
        case "Step_H7_8":
			dialog.text = "���� ����� ������� �� ������, � ��������� �����. �� ������� � �� ���� ������ ����, ������ �������� ���������� �� ����������. ���������� ����������� �������, �������� � ����, �� ������. �� � ����� �� �������� ��������"+ GetSexPhrase("��","���") +" � �'�������, ��� ����� ����.";
			link.l1 = "������... ������ ����� ���: ��� ������?";
			link.l1.go = "Step_H7_9";
		break;
        case "Step_H7_9":
			dialog.text = "��� � ����. ����������, �������...";
			link.l1 = "����� ������, � ���"+ GetSexPhrase("","�") +" �� ���� ������... �� � ������ �� ����, ��������� - � �����������. � �������, �� ������� ��� ����������, ������ �������, �������� ��� ������� ����������� �����?";
			link.l1.go = "Step_H7_10";
            GiveItem2Character(pchar,"letter_1");
		break;
        case "Step_H7_10":
			dialog.text = "�����, ��� � ������ ���������� ������ ��� ������� � ���� ������� �� �����...";
			link.l1 = "�� �����, ������ �������, ��� �����.";
			link.l1.go = "Step_H7_11";
		break;
        case "Step_H7_11":
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "11");
            pchar.questTemp.State = "DelivLettTortuga_LetterFound";
            pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
            pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            QuestAboardCabinDialogSurrender();
            DialogExit();
		break;
		
//********************************* ������ ������. ����� �8 **********************************
        case "Step_H8_1":
			dialog.text = "�-�-�, ��� ����� �������, ��� ������ �� ������ �������� ��� � �������. ��� ��� �������� ������ ��� � ����.";
			link.l1 = "� ����� ������� ���� ����? ��������� ������ ����������� �� ������...";
			link.l1.go = "Step_H8_2";
		break;
        case "Step_H8_2":
			dialog.text = "��� �����, "+ GetSexPhrase("���� ���","" + pchar.name + "") +"
. �� ������� �� �������.\n"+
                          "������ ������������ ������ �������, �������� �� ������ � ������� ����� �������� ��� �����, ��� ����� ������� ������. �� ��� ����� ������� ���������, � ������� ��� ������� ����� ����������� �������� �� ������������ ������ � ����� ���������� ���������� � ������� ���� ����� � ����� ������������ ��������. ���� ���� �� ��� ����� ���������.\n"+
                          "������ ��������"+ GetSexPhrase("����","���") +", ��, ��������, ������ ������ � ����� ������?";
			link.l1 = "��� � ���� �������, �� ��� �����...";
			link.l1.go = "Step_H8_3";
		break;
        case "Step_H8_3":
			dialog.text = "� ������ �� ��, ��� ���������� ������, �������� �� ������ �����������, �� �������� ����������������, ��� �������...";
			link.l1 = "��� ��� ��������?";
			link.l1.go = "Step_H8_4";
		break;
        case "Step_H8_4":
			dialog.text = "���� � ���, ��� ������ �� �������� ����� �� ����� ����������� ������. ������ ���������� ����� �������, ������ ��� �������� ������� ����������� �������������� ����� � ������������� ������������� ���������, ���� �������� ���� � ������ ������.\n"+
                          "��� �����-�� � ��������� ��������� ������� �����, ��� ���������� � �� ����� � ����� ������. ����� ���� � ������ ���������� ��� ��������, ���������, ��� ��������� ���� ����� ������������ ���� �����. ����� ��� �������� ��������� ����� �� ����� ������� ������, ��� � ����������� ������� ������������ ����, ����� �� ������� ��� ��� ���� �������� ��������.";
			link.l1 = "����� ���������. �� ����� ��� ��������� ����� � ����� �������?";
			link.l1.go = "Step_H8_5";
		break;
        case "Step_H8_5":
			dialog.text = "��������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +", � ��� ��� ������ ����.\n"+
                          "����, ������ ���� �������� ������ � ���� ������������, ���� ��������� ��� ������� � �������, ��� �������� ��� ����� �� ���� ����� �� �������������� ���������. �� ������� ��� �������! �� ��������������� ����� �� ����� ��������� �������-����������� � ��� ������ �� ������ �������� ���������� ����������� ������ ���������!\n"+
                          "������� ���������� ����� �� ������� �����, �� ��������� ������������ ��� ��������� �� ������ ����. � ���������� ���� ���������� � ������������ ������� ������� �����, ��� ������ � ������� � ������ �� ���������� ��������� ��������� ���-�� �����, � ���������� ����������.";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" ����� ����� ��� ������?";
			link.l1.go = "Step_H8_6";
		break;
        case "Step_H8_6":
			dialog.text = "���, � ���� ��� �������� ������. �� ������ ����� ��������� �������.";
			link.l1 = "���� �� ����������� ����, �� ��� ����� ����������, � ���� ������ ������...";
			link.l1.go = "Step_H8_7";
		break;
        case "Step_H8_7":
			dialog.text = "������� ����, ������ ��� � ������� ������������� ����, ��� � �������� ��� � ����������.";
			link.l1 = "������ ��� �����������, �����.";
			link.l1.go = "Step_H8_8";
		break;
        case "Step_H8_8":
			dialog.text = "�� ���� ����� �����, ��� ���� �� ���������� ������� � ��������� ��������� �� �������� ����������� ������� ������ ������������ �����, ���������� �� ����������� ��� �����.";
			link.l1 = "��, �� ���� ���� ����������, �� ��� �� ���������, ��� ����� ������������?";
			link.l1.go = "Step_H8_9";
		break;
        case "Step_H8_9":
			dialog.text = "�� ������������ �������� �� �����, "+ GetSexPhrase("���� ���","" + pchar.name + "") +".";
			link.l1 = "�������... ������, ��� ��� ����� ������?";
			link.l1.go = "Step_H8_10";
		break;
        case "Step_H8_10":
			dialog.text = "� �� ����.";
			link.l1 = "��� ���... �� ��� ��, �������, � ����� ������ � ��� ���, � ��� ��� ����� ������.";
			link.l1.go = "Step_H8_11";
		break;
        case "Step_H8_11":
			dialog.text = "� ������ � ���� ����������� �� ��� ���������. �����������, "+ GetSexPhrase("���� ���","" + pchar.name + "") +". � ������ ������ ������� ����� ����� �������.";
			link.l1 = "��� �������������� �������, ����������, ������� ��� ������. �� �������, �����, � ���������� ��������� � �������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toBermudes";
            AddQuestRecord("Hol_Line_8_SeekBible", "2");
            QuestSetCurrentNode("Jackman", "HolLine8_quest");
		break;
        case "Step_H8_12":
			dialog.text = "��� ����� � ����� �����... �� ��� ��, �� ��� ������ �� �����. ������������� ������� � ����������.";
			link.l1 = "������, ������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_BadResult";
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
        case "Step_H8_13":
			dialog.text = "���, ������� ���������... ��, ��� ������ ��, ��� �� ��������! �� ����� ��������� ��������� ������� ������! �������, ����� ����!!!";
			link.l1 = "����, � ������, � ������ �����. �����.";
			link.l1.go = "Step_H8_14";
			TakeItemFromCharacter(pchar, "Bible");
		break;
        case "Step_H8_14":
			dialog.text = GetFullName(pchar) + ", � ������ ���, ��� ������� ���� ����� ����� �������. �� ������� �� ������� ���� ������?";
			link.l1 = "��, � ���� ���� ��������� �������, � ��������"+ GetSexPhrase("","�") +" 235 ����� �� �������. ���, ��� �� ���������� ��� ����� ������ �����, � ����� �������� ��������.";
			link.l1.go = "Step_H8_15";
		break;
        case "Step_H8_15":
			dialog.text = "����� ����� � �������� ��� ���� �������. � ������������ �������� ����� ������ �� ��������� ����, �������, ������, ����� ������...";
			link.l1 = "���, ������� - ��� �������, ���� ����� �������! � ��� ��� �� ��� ����� ����� ����������?";
			link.l1.go = "Step_H8_16";
		break;
        case "Step_H8_16":
			dialog.text = "������� ������������� ������������ �� ���� ����� - �������� �����. �� ����� ��� ������ � �����, � ����, � ���� ��������...";
			link.l1 = "�� ��� ��������? ���������, ��������� ��� ��� ���������� �� ��������� ����� ������������ �����. �� �� �����... ��, �������, �������� �������� ����� ��������, � � ������� ����� ����������� ������ - ������ ����. � ����� ������ � ������� ��� ��� ������ �������� ������������� �������� ��� ����� ����� �������� �����.";
			link.l1.go = "Step_H8_17";
		break;
        case "Step_H8_17":
			dialog.text = "��������, � �� ������ ��� �������!";
			link.l1 = "� ��� ����� ������ ����������. ��������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1235000);
            pchar.questTemp.State = "SeekBible_GoodResult";
            AddQuestRecord("Hol_Line_8_SeekBible", "10");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("","�"));
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
    }
}
