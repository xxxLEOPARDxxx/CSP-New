// ���������� ���� �1 �� ��. �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
    float locx, locy, locz;
	string sTemp, attrName;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "�� � ��� ��������.";
			link.l1 = "�����...";
            link.l1.go = "exit";

//>>>>>>>>>>>>========= ������� �������� �� ���������� =====================
            //����� �1, ������������� �������.
            if (pchar.questTemp.State == "Fr1Legran_toTavern")// ����� �1, ������ � �������
            {
    			dialog.text = "������ ���, ��� �� ������?";
    			link.l1 = "�����, ��������� � ����, �� - ���� ������.";
    			link.l1.go = "Step_F1_1";
            }
            if (pchar.questTemp.State == "Fr1Legran_afterFightBand")// ����� �1, ������� ����� ���.
            {
    			dialog.text = "��� ���� ���������������, ��� �������...";
    			link.l1 = "�����, � ��������"+ GetSexPhrase("","�") +" ��� �� �����, ��� ������ ���������...";
    			link.l1.go = "Step_F1_3";
    			link.l2 = "� �� ��� ������! � �����"+ GetSexPhrase("","�") +", ��� ���� ������� ��� ����"+ GetSexPhrase("��","�") +" ����������.";
    			link.l2.go = "Step_F1_5";
            } 
            //����� �2, �������� ������ �� �������
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// ����� �2, �������� ���� � �������
            {
    			dialog.text = "...�� ��������� �����.";
				link.l1 = "(��� ����) ���-���, ��������� �����...";
    			link.l1.go = "Step_F2_1";
            }
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems" && pchar.location == "Shore22")// ����� �2, �������� ���� � �����
            {
    			dialog.text = "...��� ������ ��� ������ ���� �����.";
				link.l1 = "(��� ����) ���-���, ������...";
    			link.l1.go = "Step_F2_5";
            }
			if (npchar.id == "DeLeiva")// ����� �3, ���� � ����� ����� ����
            {
    			dialog.text = "�� ��� ��, ��� �� � ��������� ������ �����. ����� ���������� �� ����, "+ GetSexPhrase("�����","�����������") +". ������� ����� ��� ��� ������� - ������ ��������� �����!";
				link.l1 = "��� ��� �������! � � ��� ����?!";
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toAnna")// ����� �5, ����� ���� � ���������� �������
            {
    			dialog.text = "��� ������� ������ �'������?";
    			link.l1 = "��, �����. ��� ���� ���� �����"+ GetSexPhrase("��","��") +"?";
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")
            {
    			dialog.text = "�������������, ������"+ GetSexPhrase("","���") +", ��� �� ������?";
    			link.l1 = "���� ������. �� � ��������� ���� �����, �� ������������, �����...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = "�������������, ������"+ GetSexPhrase("","���") +", ��� �� ������?";
    			link.l1 = "���� ������. �� � ��������� ���� �����, �� ������������, �����...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "DeLeivaBrother_1" || npchar.id == "DeLeivaBrother_2")// ����� �5, ������ �� �����
            {
    			dialog.text = "��� ���� ����� �����?";
    			link.l1 = "�������, �� �� �� ������������ ���� ���� �������� �� �����?";
    			link.l1.go = "Step_F5_2";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")// ����� �5, ����� ���� ����� ���������� ������
            {
				dialog.text = NPCStringReactionRepeat("������"+ GetSexPhrase("","���") +", �� ��� ������ ��� �������� ��� �����. ������, ��� � ���� ���� �� ������ ������� �����.",
					         "������������ �����, �������. ���� ��� ������.", "� ��� ��� ������������ �������...", "������� ��� �� ���: ������������, �������...", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("�������, ���������� �������� ���� ������ ��� ����������� ��� ����������� ���������, � ����� �� ��, ��� ��� � ��� ����������... �� ����� ������, ����� ����, ��� ������ � ��� ������� �������� � ��������.", 
					      "� � ��� ���"+ GetSexPhrase("","�") +" ������ ��� ��.", "� ��� ��� � ���"+ GetSexPhrase("","�") +" ��� ������...", "������������, �������...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);

            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "empty")// ����� �5, ����� ���� ����� ���������� ������
            {
				dialog.text = NPCStringReactionRepeat("������"+ GetSexPhrase("","���") +", �� ��� ������ ��� �������� ��� �����. ������, ��� � ���� ���� �� ������ ������� �����.",
					         "������������ �����, �������. ���� ��� ������.", "� ��� ��� ������������ �������...", "������� ��� �� ���: ������������, �������...", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("�������, ���������� �������� ���� ������ ��� ����������� ��� ����������� ���������, � ����� �� ��, ��� ��� � ��� ����������... �� ����� ������, ����� ����, ��� ������ � ��� ������� �������� � ��������.", 
					      "� � ��� ���"+ GetSexPhrase("","�") +" ������ ��� ��.", "� ��� ��� � ���"+ GetSexPhrase("","�") +" ��� ������...", "������������, �������...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_toGuadeloupe")// ����� �6, ����� � ���� �����
            {
				dialog.text = NPCStringReactionRepeat("�����"+ GetSexPhrase("�","���") +", ��� ���, ������� ������� �������?! �� ��� � ��� ��� ����������� �� ����� ������� �����!",
					         "�� ����� �� ��� ��������...", "��� ���-��?", "����� �� �� �����, ������� �����?!", "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("��� ����������� ��� ���. ��� ��� - ��� ������� ����� �� �������-����������� �'�������.", 
					      "��, �����...", "�� ���, ��� ���������...", "�� ����� ����, �� ��������...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F6_1", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_FoundMoney") //������ � �������
            {
    			dialog.text = "�� ���"+ GetSexPhrase("��","��") +" ���� �����?";
    			link.l1 = "��, ��� � �������. � �������, �� ������ ������� - ������ � ����.";
    			link.l1.go = "Step_F6_14";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //�������� �������
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_WeLate") //������ ����
            {
    			dialog.text = "�� ���"+ GetSexPhrase("��","��") +" ���� �����?";
    			link.l1 = "���, ��������...";
    			link.l1.go = "Step_F6_10";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //�������� �������
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toBonrepo") //����� �8. ������ ������� � ���-����
            {
    			dialog.text = "� ��� ���� �����?..";
    			link.l1 = "������� " + GetFullName(pchar) + ". � ������"+ GetSexPhrase("","�") +" � ��� �� ������������ �������-����������� �`�������.";
    			link.l1.go = "Step_F8_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek") 
            {
    			dialog.text = "����, ��� ������� ������������ ���� ������?";
    			if (sti(pchar.questTemp.Count) == 3)
				{
					link.l1 = "��� ���������. ��� ���� �� ����� ����������� � ����� �� ������� ������.";
    				link.l1.go = "Step_F8_9";
				}
				else
				{
					link.l1 = "���� ��� �� ������� ����������� �� �����, �� � ������� ��� ����.";
    				link.l1.go = "exit";
				}
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr12EndWar_toBorepo")
            {
    			dialog.text = "�-�-�, �����"+ GetSexPhrase("","����") +"! ��� ��� ������. ����� ������ - � ���� ���...";
    			link.l1 = "���"+ GetSexPhrase("","�") +" ��� ������ ��� ��, ������.";
    			link.l1.go = "Step_F12_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "EndOfQuestLine")
            {
    			dialog.text = "���, �����"+ GetSexPhrase("","����") +", � ��� ������ �� ����������. ��������...";
    			link.l1 = "��������, ������...";
    			link.l1.go = "exit";
            }
		break;
//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* �������� ������� �� ���������. ����� �1 **********************************
 		case "Step_F1_1":
			dialog.text = "��, ��� ���.";
			link.l1 = "���� ����� "+ GetFullName(pchar) +". � �������"+ GetSexPhrase("","�") +" � ��� �������-������������ �'��������. ���� ��������� ���� � ��������� ��������� ��� �� ��������� � ����� �� �����.";
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			dialog.text = "���� ��� �������� �������-����������, �� ������� � �. ����� �� ������������?";
			link.l1 = "��� ����� ������. ����� ���� �� ���� �������.";
			link.l1.go = "Step_F1_exit";
		break;
 		case "Step_F1_exit":
			locations[FindLocation("Shore39")].DisableEncounters = true; //���������� �������
    		pchar.questTemp.State = "Fr1Legran_toLeMaren";
            AddQuestRecord("Fra_Line_1_LegranDis", "2");
			LAi_SetStayType(npchar);
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1 = "location";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1.location = "Shore39";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition = "Fr1Legran_intoLeMaren";
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            DialogExit();
		break;
 		case "Step_F1_3":
			dialog.text = "��, ��, ���������, �� ��������� ��������� ������ �� ���� �������������. ��������� ������������� ��� ������� �������: ����� � 20000 ������� ���������, �������, ������ ��������?";
			link.l1 = "������...";
			link.l1.go = "Step_F1_4";
		break;
 		case "Step_F1_4":
			dialog.text = "��� ������ ����, �������� ��������.\n"+
				          "�������� � ������ �������, "+ GetSexPhrase("�����","�����������") +".";
			link.l1 = "��������, ������. � ����� ��� ������� ������ �����, �� �������... ��������!";
			link.l1.go = "Step_F1_4_exit";
		break;
		case "Step_F1_4_exit":
			pchar.questTemp.State = "Fr1Legran_backGovernor";
			AddQuestRecord("Fra_Line_1_LegranDis", "3");
			AddMoneyToCharacter(pchar, 20000);
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
			NPChar.LifeDay = 0;
			RemovePassenger(pchar, npchar);
            DialogExit();
		break;
 		case "Step_F1_5":
			dialog.text = "�� ��, ������"+ GetSexPhrase("��","��") +"! � ������ �������-�����������, ���"+ GetSexPhrase("�� ������� ������","�� ��������� ��������") +" � ���� � �������!";
			link.l1 = "������� �������� � �����, �����!";
			link.l1.go = "Step_F1_6";
		break;
 		case "Step_F1_6":
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
			AddQuestRecord("Fra_Line_1_LegranDis", "4");
			pchar.questTemp.State = "Fr1Legran_LegranKilled";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ����� �� � ����������. ����� �2 **********************************
 		case "Step_F2_1":
			dialog.text = "��, ���� ���� ����� ����, ���� �����"+ GetSexPhrase("","�") +"? �� ���� ������ �� ����������.";
			link.l1 = "���� ����� ������� " + GetFullName(pchar) + ", � ������ ��� � �������... �� ������� �� ��� � �������?";
    		link.l1.go = "Step_F2_2";
		break;
 		case "Step_F2_2":
			dialog.text = "���, �� ������!";
			link.l1 = "� ���� ������� �������, ���������... �����, ������? �������-�� � � ��� �������...";
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = "������ � �������, �������. ��, � ��� ����.";
			link.l1 = "�-�-�, �� �����...";
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			chrDisableReloadToLocation = true; 
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetStayType(sld);
				if (i==2) ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "tables", "stay2");
				else ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "goto", "goto3");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", 10);
			}
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1 = "location";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1.location = "Villemstad_town";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition = "Fr2Letter_OutTavern_2";
			locations[FindLocation("Shore22")].DisableEncounters = true; //��������� ������ ��������
			LAi_SetPlayerType(pchar);
            DialogExit();
		break;

 		case "Step_F2_5":
			dialog.text = "����� ��? � ��� ��� �� ������� �����?";
			link.l1 = "���� ������ ���-���. �� ��� �������� ��� �����-�� ��� ������...";
    		link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = "� ���� ������ ����. ������� ���...";
			link.l1 = "� ��� ������!";
    		link.l1.go = "Step_F2_7";
		break;
 		case "Step_F2_7":
			dialog.text = "� ��� �� ���"+ GetSexPhrase("��","��") +", ����� ��������� ������?";
			link.l1 = "� �� �����������"+ GetSexPhrase("��","���") +", ���� ��� �� �������� ������. ��� ��� ����������, ��� ����� ������� � ��� ����� �����������?!";
    		link.l1.go = "Step_F2_8";
		break;
 		case "Step_F2_8":
			dialog.text = "��� ����� ����������� - ��� ��������. �� �������� ��� ���������.";
			link.l1 = "��� ��� �������� ������ �������...";
    		link.l1.go = "Step_F2_9";
		break;
 		case "Step_F2_9":
			dialog.text = "�����... �����, ������ ������� ����������� ��� ����������� ���������� �������� �������� - ����� "+ GetSexPhrase("�� ����","��� ����") +". �� ����� ������ �������...";
			link.l1 = "��� �� ��, �������! � ��� �� ��� ������, �� �� ��������!";
    		link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = "�� ���� ��� ������ �����, �� ���-��� ������ ������� �����. ������ �� ������ ���, �� ������ ��� ���� �� ����������...";
			link.l1 = "��, ��� ��� �������. �������, ���� ���������� �� ���� ����������� �����...";
    		link.l1.go = "Step_F2_11";
		break;
 		case "Step_F2_11":
			DeleteAttribute(&locations[FindLocation("Shore22")], "DisableEncounters"); //��������� ������
			chrDisableReloadToLocation = true;
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1 = "location";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1.location = "Curacao";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition = "Fr2Letter_FightWithGaleon";
			AddQuestRecord("Fra_Line_2_DelivLetter", "4");
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ����� � ����� �� �����. ����� �3 **********************************
 		case "Step_F3_1":
			dialog.text = "���, �� ��� ��� ��������... � ����� ��� ������� ���� ����������� "+ GetSexPhrase("�������","�����-�� ����������� �����") +", � ����� ����������: '� � ��� ����?!'\n"+
				          "�� ������� �� ���� �����"+ GetSexPhrase("�","��") +"! ��� ���� �������, � ����� � ��� ��� ������� ������ �'�������.";
			link.l1 = "��� ����... �� ��� ��, ������� ��� ���� ��� ����, ����� �������� ��� ������, ������� �� ��������� ��� �������.";
    		link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			dialog.text = "������ �������!";
			link.l1 = "������, �������...";
    		link.l1.go = "Step_F3_3";
		break;
 		case "Step_F3_3":
			LAi_LocationFightDisable(loadedLocation, false); 
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ����� ���� �� �����. ����� �5 **********************************
 		case "Step_F5_1":
			dialog.text = "� �������� ������ �� ������ �� ���� ������� ���� �� ��� �������. �������-���������� ������ ���������� ������������� ������ ����� ���� � �������, ��� � ���� ������� �. ��, ��� ��� � ����! �� ��� ���������������� ��������� �����, ��� ������ ������ ��� ���������, � � �� ����, ��� ��������.\n"+
				          "�����"+ GetSexPhrase("�","���") +", � ����� ��� ����������� � ������ � ��������, ��������� ��� ��������.";
			link.l1 = "�����, �� ������ ������������ �� ����.";
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Fr5AnnaHant_toHavana";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "2");			
			sld = GetCharacter(NPC_GenerateCharacter("InesDeLasCierras", "girl_8", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = "����";
			sld.lastname = "�� ��� �������";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_houseSp2", "goto","goto2");
		break;
 		case "Step_F5_2":
			dialog.text = "����� ���� �� ����� ����?";
			link.l1 = "�� ���� �� ����, �� ���������"+ GetSexPhrase("","�") +" ��, �������� ��...";
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = "��������. � ��� ���� ����� �� ���?";
			link.l1 = "� ��� �����"+ GetSexPhrase("","�") +", �� ��������� ��������� �� ���� ����?";
    		link.l1.go = "Step_F5_4";
		break;
 		case "Step_F5_4":
			dialog.text = "���������� ������, ��� ��. ����� � ������ ���� ���� ������� ����.";
			link.l1 = "� "+ GetSexPhrase("���","��") +", ��� ��������"+ GetSexPhrase("","�") +" ���������� ���� ���� �� ��� ����. ��� � ���� ��� ���� ��, ����� �� ��������.";
    		link.l1.go = "Step_F5_5";
		break;
 		case "Step_F5_5":
			dialog.text = "����, ����� ������� � ����! ������� �������, ����, �������� ����� ��� ������ ����, � �� ����� ������������ �����.";
			link.l1 = "� ��� �� �?!";
    		link.l1.go = "Step_F5_6";
		break;
 		case "Step_F5_6":
			dialog.text = "� ���� ��� ���... ������, ����, �������� � "+ GetSexPhrase("���� ���������","���� ������") +"!";
			link.l1 = "� � ����� ���������� ����� ����� �� ������"+ GetSexPhrase("��","��") +". � ����! ��, ������� ������...";
    		link.l1.go = "Step_F5_7";
		break;
 		case "Step_F5_7":
			LAi_LocationDisableOfficersGen("Mayak10", false); //�������� �������
			pchar.questTemp.State = "Fr5AnnaHant_GoodWork";
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], false); 			
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=2; i++)
            {				
				LAi_group_MoveCharacter(characterFromId("DeLeivaBrother_"+i), "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
		break;
 		case "Step_F5_8":
			dialog.text = "�� ������ ���� ��������� � �� � ������������� ����������.";
			link.l1 = "��� ������ ����� �� ������, �������� ���. � �����"+ GetSexPhrase("","�") +" ����������� ���� ������� ����������...";
    		link.l1.go = "Step_F5_9";
		break;
 		case "Step_F5_9":
			dialog.text = "��, ������"+ GetSexPhrase("","���") +" " + pchar.name + ", ��� � ���� ������������� ���?";
			link.l1 = "����� ����, � ����� ��� ���������� � ����� ��������, �� ���� �����������.";
    		link.l1.go = "Step_F5_10";
		break;
 		case "Step_F5_10":
			dialog.text = "���������� ������� ���� �������, � �������� �������� �������� �� ������ ����� �� ����������.";
			link.l1 = "�����, �� ������� ���� ������������ �������� ������. �������, �� � �������.";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.over = "yes";
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
		break;
//********************************* ������� �����. ����� �6 **********************************
 		case "Step_F6_1":
			dialog.text = "�-a-a! ��, ��� ������ ����. ��������������, ���� � ������ ������.";
			link.l1 = "����� ������, �����, ���� �������� ���, ��� ���� ������� ������ �������������� �������. ��� ���� �������� ������� �������, ����� ����������� ��� �������.";
    		link.l1.go = "Step_F6_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
		break;
 		case "Step_F6_2":
			dialog.text = "�������, ��� �� �����, ������, ������� �� ����� �������� ������ �������� �������, ��-��! ��, ��� ���� � �����, ��� �� �������� ����� ������������ �������-����������� � �������������. ��� ���, �������� ������ � �������, �� ������� � ���, � ����� �`������� ������� ������. ������� ����� ���������������. ������, ��� �� ������������� �� ��������?";
			link.l1 = "� ����� ������?";
    		link.l1.go = "Step_F6_3";
		break;
 		case "Step_F6_3":
			dialog.text = "� ���� ������� ��� ������� � �������. � ���� ���������� ������� � ���������� ������. � ���� ������ �������-���������� ��������, ��� � ����� ������ ������ ��������� ������ �� ����� �� ������ ������� ����� ������. � ���� �������� ��� �������, �� �������� - ��� ����������. ��������������� � � ������, �������� ������� ��������, ������� �� ��������. ��, ���?";
			link.l1 = "� ��������� ������ �������.";
    		link.l1.go = "Step_F6_WantMoney";
			link.l2 = "����� �� ������ ��������� �� �������, �� ��������� ����! ����������, � � ����!";
    		link.l2.go = "Step_F6_4";
			SaveCurrentQuestDateParam("questTemp");
		break;
 		case "Step_F6_WantMoney":
			dialog.text = "��� �������. ��� ���� �������.";
			link.l1 = "�������, �������. �� � ������, �, �������, ������ �� �������...";
    		link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddMoneyToCharacter(pchar, 10000);
			pchar.questTemp.State = "Fr6Olone_TakeMoney";
			AddQuestRecord("Fra_Line_6_Olone", "2");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("","�"));
		break;
 		case "Step_F6_4":
            if (GetCompanionQuantity(pchar) == 1)   // ���������� ������� ���������� �� ������ �������.
            {
				if (GetQuestPastDayParam("questTemp") < 6)
				{
					dialog.text = "�� ��� ��, �� �����"+ GetSexPhrase("","�") +" � ����, ����� ������ ����� � ����� �������. ����� ���������� � ������ � ������!";
					link.l1 = "����� ������! �������, ����� ���� �������� �� ��� ��������?";
    				link.l1.go = "Step_F6_5";
				}
				else
				{
					dialog.text = "��, � ��� �� ��������"+ GetSexPhrase("","�") +" ������� �������?";
					link.l1 = "�� ���, ��������"+ GetSexPhrase("��","���") +" �� ��������, ��� �� � ������.";
    				link.l1.go = "Step_F6_7";
				}
            }
            else
            {
				dialog.text = "�������, �� � ���� ����� � ��� ���� ���� ���"+ GetSexPhrase("���","�") +", �� ��������, ��� ���� ���� - ��������� �����. ������ ��� ���������� �� ���������. ������� �������� �� ������ ��������, ���� ������ �����������. � ���������!";
				link.l1 = "������, �������, � ����� �������.";
    			link.l1.go = "exit";
				link.l2 = "��, �� ����� ������� � �� ������"+ GetSexPhrase("��","��") +". ������� �, �������, ����� ������ ���� ���� ������... ";
    			link.l2.go = "Step_F6_WantMoney";
				NextDiag.TempNode = "Step_F6_4";
             }
		break;
 		case "Step_F6_5":
			dialog.text = "���� ���������� �����. �� �������� ���� � ����� ������ �������. ����� ������� ������, ����� � ����������� ������ �� ����� �����.";
			link.l1 = "�����������. �� ��� ��, � �����"+ GetSexPhrase("","�") +".";
    		link.l1.go = "Step_F6_6";
		break;
 		case "Step_F6_6":
			dialog.text = "����� ������ �� ������, � ��� ����� �������!";
			link.l1 = "����� ������, ��������...";
    		link.l1.go = "Step_F6_GoOn";
		break;
		case "Step_F6_GoOn": 
			//==> ��������� �������
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 5, false);
			for (i=1; i<=2; i++)
			{
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "officer_"+(rand(63)+1), "man", "man", 20, FRANCE, -1, true));
                FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS24, 70, 80, 40);
                FantomMakeCoolFighter(sld, 20, 90, 70, BLADE_LONG, "pistol4", 120);
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				sld.CompanionEnemyEnable = false; 
				sld.Abordage.Enable = false; // ������!
				sld.RebirthPhantom = true; 
                SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.DeckDialogNode = "HaveHotBussines";
				SetCharacterRemovable(sld, false);
				LAi_LoginInCaptureTown(sld, true);
			}
            // ==> ������� ����, � �������-����������� ������ ����� ������
            SaveCurrentQuestDateParam("questTemp");            
            pchar.TempPerks.QuestTroopers = true; //���� ���������� �������
            // ==> �������������� ���� ����������� ������
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "FraLine6Quest_Attack"; 
			npchar.DeckDialogNode = "HaveHotBussines";
			AddQuestRecord("Fra_Line_6_Olone", "3");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("��","���"));
			DialogExit();
		break;
		case "Step_F6_7":
			dialog.text = "�������"+ GetSexPhrase("��","���") +"?";
			link.l1 = "��, �������.";
    		link.l1.go = "Step_F6_8";
		break;
 		case "Step_F6_8":
			dialog.text = "� ���� ���������� � �������� �����������, �� ������ �� ������ �� �����.";
			link.l1 = "��� �� �����?!";
    		link.l1.go = "Step_F6_9";
		break;
 		case "Step_F6_9":
			dialog.text = "����� ������, "+ GetSexPhrase("��� ���","��������") +". ������ � ������ ��� ���, ��� �������. ��� ��� � ����� ������ ���������� ����� ������ ��� 200 ����� ������. ��� ���-��...";
			link.l1 = "���� ������, �������... �� ��� ��, ����� � ������ �� ������, ������� ��� ����������� �� �������� ������.";
    		link.l1.go = "Step_F6_WantMoney";
		break;
 		case "HaveHotBussines":
			dialog.text = "�������, ��� ������ ������ �������, ����� ������ ����� ������, ���� ������ �� ����������.";
			link.l1 = "��, �������, �� ����������� ������...";
    		link.l1.go = "exit";
		break;
 		case "Step_F6_10":
			dialog.text = "���-�� ��� �� �������� ���� �����, " + pchar.name + ".";
			link.l1 = "�� ��������, �������. ���� � ���, ��� ������ ��� ���� � ������ ���� � ������ ���� �����. ��� ���� ����������...";
    		link.l1.go = "Step_F6_11";
		break;
 		case "Step_F6_11":
			dialog.text = "� ��� �� �����, "+ GetSexPhrase("��� ���","��������") +". � ����� � ��, ��� ��� ��-�� ���� �� ������ �������!";
			link.l1 = "������� �����������, ���� �����. ����� �������...";
    		link.l1.go = "Step_F6_12";
		break;
 		case "Step_F6_12":
			dialog.text = "�������, ������ ����� ��������� ��� �����. � ������, �����"+ GetSexPhrase("�","���") +"! ��������� ���� ����� �� ����...";
			link.l1 = "����� ���, � �� ���� � ����� �������!";
    		link.l1.go = "Step_F6_13";
		break;
 		case "Step_F6_13":
			dialog.text = "����� � ���� ���� ��� ��������� ������! ��������� ���� - ������ �� ������.";
			link.l1 = "�� ������, ������� ��� ��� ��� ����... �� ��� ����������.";
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "4");
		break;
 		case "Step_F6_fight":			
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Captain_"+i);
				sld.LifeDay = 0;
				DeleteAttribute(sld, "RebirthPhantom");
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F6_14":
			if (sti(pchar.money) >= 200000)
			{
				dialog.text = "�������, ���������! ����� ������ - � �� �����.";
				link.l1 = "������, �����. � ������������ ��� ������� � ������...";
    			link.l1.go = "Step_F6_15";
				link.l2 = "� � ��� �����, ��� �� ������"+ GetSexPhrase("","�") +" � ����� ��������. ��� ������ ������"+ GetSexPhrase("","�") +" �!";
    			link.l2.go = "Step_F6_20";
			}
			else
			{
				dialog.text = "������ �� ���"+ GetSexPhrase("��","��") +", � � ���� �� ��� � �������. ������� �������"+ GetSexPhrase("","�") +"?!";
				link.l1 = "�� �� ���, �������?!";
    			link.l1.go = "Step_F6_17";			
			}
		break;
 		case "Step_F6_15":
			dialog.text = "������������, �� ������ ������� �� ������������ - ����� ����� ���� �������.";
			link.l1 = "������, �������. ���� ������...";
    		link.l1.go = "Step_F6_16";
			AddMoneyToCharacter(pchar, -150000);
		break;
 		case "Step_F6_16":
			chrDisableReloadToLocation = true;
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
				}
			}
			AddQuestRecord("Fra_Line_6_Olone", "5");
			pchar.questTemp.State = "Fr6Olone_OloneIsLive";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], true);
            DialogExit();
		break;
 		case "Step_F6_17":
			dialog.text = "� � ��� �����, �������, "+ GetSexPhrase("��������","�������") +"... �� ���� ������ ��� �������� - �������� ���� ������.";
			link.l1 = "�������?";
    		link.l1.go = "Step_F6_18";
		break;
 		case "Step_F6_18":			
			dialog.text = "������ ���. ����� ���� ��������...";
			link.l1 = "�� �����, �� ��� ����������.";
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "6");
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> ����� � ������� �����, �������� �� ������� ���������.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));	
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
		break;
 		case "Step_F6_20":
			dialog.text = "���, ������, ���?! ��, ����� �������� � �������...";
			link.l1 = "������ �����"+ GetSexPhrase("","�") +", �������...";
    		link.l1.go = "Step_F6_21";
		break;
 		case "Step_F6_21":
			NPChar.LifeDay = 0;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "8");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("","�"));
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> ����� � ������� �����, �������� �� ������� ���������.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));	
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ������ �������. ����� �8 **********************************
 		case "Step_F8_1":
			dialog.text = "���, �������-��! � � ��� ����� �����������. �������-���������� �'������ ������� ��� � ��� ����� ��������. � �������, ��� �� ��������� ���������� ��� � ��� �������. � ������: ���, ��� �� ����� ��������, ������� �� ������ ����� ��������� ����-����, ����� ���.";
			link.l1 = "� ������������"+ GetSexPhrase("","�") +" �� ����...";
    		link.l1.go = "Step_F8_2";
		break;
 		case "Step_F8_2":
			dialog.text = "�����������! ����, � ����.\n"+
				          "������ � ����������� �������� ����� ������� ���������. ��������� ��������� �������� ����� ����� ������� � ����������, � ��� ������� ������-������ ������� XIV �������� ������������� ����� � ��������.";
			link.l1 = "��������, ������... ����� �����? �������������?!";
    		link.l1.go = "Step_F8_3";
		break;
 		case "Step_F8_3":
			dialog.text = "��... �� ��, ������ �� ����� �������� ������.\n"+
				          "������������� ����� - ��� ����� �� �������������� ����� �� ��������� ����������. ����� ��� �������, ����������, �������� ����� �������� � ���������, ����������� ������ ��� ��������� ������������. ��� ������ ����, ��������� ��������� ��� ��� ����� ��� ��������� �������� ��� ��������� ��������, ��������� � ��������� ����.\n"+
						  "��� ��������� ������� ����� �� � ������� ������� ��������� � ������� ����������, ��� ��� ���������� �������� ��������� �������� �� �� �������. ������� ������������ ����� ���-������ �������, �������, �� ������, ��� ���...";
			link.l1 = "����� ������� � ����"+ GetSexPhrase("��","��") +" ��� �������?";
    		link.l1.go = "Step_F8_4";
		break;
 		case "Step_F8_4":
			dialog.text = "��������� � ��������� �������� �� ����, ���� �������-���������� ������ ��� ����� �������� �� ������� ������������. � � ���� ����� ��� ����� ������������ ������ �� ������ ��������� ��������, ������� ��� � ��������� � ��������� ��������.\n"+
				          "�����, ��� ��� �� �������� �������� �� ��� �����, ����� ����: ����� ������ �� ������, ������� - � ��������� ��������� �� ��������, ���� ������ �� ���������. ���� ������ � ����������� � ������ �� ��� � ������� �� � ���� ������ �� �������� �� ����������� ������� � ����. ��� ���� ������ ������� - ������, ��� ��� ������� �� �������!";
			link.l1 = "� ��� �� � ����"+ GetSexPhrase("��","��") +" ����� ��� ��������?";
    		link.l1.go = "Step_F8_5";
		break;
 		case "Step_F8_5":
			dialog.text = "���������, �� ���� �������. ��� ������������� ���, ��� �� �������� ������ � ����������� ��������! ���� �� ��� �������� � ���� ���� - �����, ������������, ������������ �� ���� ������? �������, �� ������ ����������, ��...";
			link.l1 = "�� ��� �����?";
    		link.l1.go = "Step_F8_6";
		break;
 		case "Step_F8_6":
			dialog.text = "����� ��� �������� ��������� ��� � ������. �� ����, "+ GetSexPhrase("��������","�������") +", ����� ���������"+ GetSexPhrase("��","������") +" ��������������� �����! � ������ �������� ���������� ���� �� ������� �� �����������.";
			link.l1 = "������� ���� ���� ���������, � ��� �� ���-�� ������!";
    		link.l1.go = "Step_F8_Fight";
			link.l2 = "�� ��� �, ���� ������ �� ����� �������� ��� ���� ��������, ��� � ����, � ������ ���!";
    		link.l2.go = "Step_F8_7";
		break;
 		case "Step_F8_Fight":
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            for (i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, "Sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, 0, true));
				FantomMakeCoolFighter(sld, 30, 65, 50, BLADE_LONG, "pistol3", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			NPChar.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "2");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F8_7":
			dialog.text = "��� ���������! �'������ � ��� �� ��������. ����, � ��� ��� � �������� ���������.";
			link.l1 = "� ��� ������, ������.";
    		link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "3");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.State = "Fr8ThreeCorsairs_toSeek";
			SaveCurrentQuestDateParam("questTemp");
            // ==>  �������� ������� �� ������� � ���� ���� ������� � �������
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "FraLine8_talk");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  ������� � �������� ����� ������� � ��������� � ���� ���� ������� � �������
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name 	= "����";
        	sld.lastname = "������";
            sld.Dialog.Filename = "Quest\JohnMorris.c"; 
			sld.greeting = "Gr_HeadPirates";
           	LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
        	LAi_SetLoginTime(sld, 0.0, 24.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  ���� ���� ������� � ������� ����� �������
            QuestSetCurrentNode("John Morris", "FraLine8_talk");
            // ==>  ���� ���� ������� � ������� ��������
            QuestSetCurrentNode("Jackman", "FraLine8_talk");
            // ==>  ��������� ������� ��������� ��������, � ����� ������ == 3
            pchar.questTemp.Count = "0";
		break;
 		case "Step_F8_9":
			dialog.text = "������ ��������, ��� ��� ���� ���� �� ����� ��������� ��������������� ���������, ������� � ����� ����-����. ��������, ������� ��� �������� ����������� � ��������� ������, ������ �� �������� ������ � �������������. �� �������, ��� ���� ���������� ���������� ��� "+ GetSexPhrase("��������� �����","����� ���������") +"! ����� ����, ��� ��, ����� �������!";
			link.l1 = "�-�... �... "+ GetSexPhrase("��������� �����","����� ���������") +"? � ��� ���� � �������, ������� � �����"+ GetSexPhrase("","��") +"?..";
    		link.l1.go = "Step_F8_10";
		break;
 		case "Step_F8_10":
			dialog.text = "��, ����� ������ ��������� �������! ��-��!\n"+
				          "��������, "+ GetSexPhrase("��������","�������") +", � ��� ��� ������� ������, ��� ���������� ������! � ��� ��� ����� � �������� ������ ������! � ������ �� ���� ��� �����������, ��� ���� �������-���������� �'������. �������, � ���� ��� ��� ����� �����-�� ������ ����... ��������.";
			link.l1 = "��������, ��������� �������...";
    		link.l1.go = "Step_F8_11";
		break;
 		case "Step_F8_11":
			pchar.questTemp.State = "Fr8ThreeCorsairs_backGovernor";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "8");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("���� ����������","����� ���������"));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex1", GetSexPhrase("��","�"));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex2", GetSexPhrase("��","��"));
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 6.0);
			if (PChar.sex == "woman")
			{
			pchar.name = "��������� " + pchar.name;
			}
			else
			{
			pchar.name = "����� " + pchar.name;
			}
            DialogExit();
		break;
//********************************* ����� �����. ����� �12 **********************************
 		case "Step_F12_1":
			dialog.text = "����, ��� �� ��� ������, ������������� ����� � �������� ���������. ������� ���������!";
			link.l1 = "��, ������, ������������ �������.";
    		link.l1.go = "Step_F12_2";
		break;
 		case "Step_F12_2":
			dialog.text = "���� ������� ������� �� ����������� - � ��� ������ ����� ��� �������...";
			link.l1 = "������, ������ ������, ��� �� �������� ��������� ���� ������ ���� ������ ����� ��������.";
    		link.l1.go = "Step_F12_3";
		break;
 		case "Step_F12_3":
			dialog.text = "��� �� ������ � ����?";
			link.l1 = "� ������ � �������� ����������� ����� ������ � ���� �����. � �� ����� ������ �����"+ GetSexPhrase("","��") +" ����� ������ �������� � ��������� � �����"+ GetSexPhrase("","�") +" �� �������� �����������.";
    		link.l1.go = "Step_F12_4";
		break;
 		case "Step_F12_4":
			dialog.text = "����������, �� ����� ������"+ GetSexPhrase("����","���") +", � ��� ����� ����! ��� ����� ����?!";
			link.l1 = "��� ����� ��������� - ��� ������, ��� �����. �� � � ������ ������ - � �������...";
    		link.l1.go = "Step_F12_5";
		break;
 		case "Step_F12_5":
			dialog.text = "�����"+ GetSexPhrase("","����") +", �� ������� �� ���� ������, � �� �� ������ � ��� ������ � ����������� � ������� �������. ��� � ���� ��� �������.";
			link.l1 = "��, ������ ����...";
    		link.l1.go = "Step_F12_6";
		break;
 		case "Step_F12_6":
			dialog.text = "����� ������, ��� �� ��������� ��� ������, �����"+ GetSexPhrase("","����") +". � ������ � ���� - '����� ������' ��������� �� ������� ����� �������.";
			link.l1 = "�������...";
    		link.l1.go = "Step_F12_7";
		break;
 		case "Step_F12_7":
			dialog.text = "����� ����� � ��������� ���� ������������ ������� � ������ ����. ��� ��� � ���������� ��� �� ��, ��� �� ��������� ��� � ���������� ����.";
			link.l1 = "������� �� �������������, ������...";
    		link.l1.go = "Step_F12_8";
		break;
 		case "Step_F12_8":
			dialog.text = "�� �����, �����"+ GetSexPhrase("","����") +"... �� ��� ��, �� ���� ��� ����������� �����, �� ��������.";
			link.l1 = "����� ��������, ������.";
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // ����� �������
			AddQuestRecord("Fra_Line_12_EndOfWar", "2");
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex1", GetSexPhrase("��","�"));
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			//==> � ������� ������ ����� ������ ����� ����� ����.			
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			Group_SetType("SoleiRoyal", "war");
			Group_AddCharacter("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetGroupCommander("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetAddress("SoleiRoyal", "Guadeloupe", "Quest_ships", "quest_ship_1");
			SetTimerCondition("Fr12EndOfWar_TakeOutShip", 0, 0, 30, false);
			AddTitleNextRate(sti(NPChar.nation), 5);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//�����
			AddSimpleRumour("�������, ��� �� ������ �����"+ GetSexPhrase("","����") +"! �� �������� ������, �������...", sti(npchar.nation), 5, 1);
		break;
    }
}
