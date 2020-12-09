// ���������� ���� �2 �� ��. �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	float locx, locy, locz;
	string sTemp;

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
            if (pchar.questTemp.State == "Fr1Legran_toLeMaren")// ����� �1, ����� � �������� 
            {
    			dialog.text = "��, "+ GetSexPhrase("��������","�������") +"! ��� ����� ����������� � ����� �������. ������-�� � �������� � �� ����� - �������� ������...";
    			link.l1 = "��, �������, ��� ����� ������ ��� �������� � ������. � ���������� ���� ���!";
    			link.l1.go = "Step_F1_1";
            }
            //����� �2, �������� ������ � �������.
            if (pchar.questTemp.State == "Fr2Letter_Arrest")// ����� �2, ����� � ������� ��� ������
            {
    			dialog.text = "������ ���� ������! � �� ��������� ��������������!";
    			link.l1 = "�� ������, ���� ��-������. � ������ ������, ��� ������� � ������ � ��������...";
    			link.l1.go = "Step_F2_1";
            }
            if (pchar.questTemp.State == "Fr2Letter_PrisonTalk")// ����� �2, ����� � ����������
            {
    			dialog.text = "������, ������ �������? ������ � ���� �������� ��-����������, ��� �����������"+ GetSexPhrase("���","��") +" � ��������, � �� ��� ������, ��-��!";
    			link.l1 = "��, ���� �� ����� ���� �� ���-�� ���������...";
    			link.l1.go = "Step_F2_2";
            }
            if (pchar.questTemp.State == "Fr2Letter_VisitGovernor")// ����� �2, ����� � �������� ������ � ������
            {
    			dialog.text = "������������, �������.";
    			link.l1 = "����� ���������... ������ ��������?!";
    			link.l1.go = "Step_F2_8";
            }
            if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// ����� �2, ����� � ����� �������, �������
            {
    			dialog.text = ""+ GetSexPhrase("������ ������","������� �����") +"!";
    			link.l1 = "������, ��������� ���! � ����� ���� ���� ��������. �������� ������ - ������ ����.";
    			link.l1.go = "Step_F2_12";
            }
			if (npchar.id == "AnnaDeLeiva")// ����� �3, ����� ���� � �������
            {
    			dialog.text = "����! ��� ���������? �� ������� �� ��������? ��� ��� ��� �� ���?";
    			link.l1 = "��������, �� ����, ��������� ��� ��� ��� ������� ��� ���, �� � ���"+ GetSexPhrase("","�") +" ��������"+ GetSexPhrase("","�") +" ����� ������ �������. � ��� ��� ������� �� ����������� � ��������, ����� ���������� ������! �������-���������� ������� ������� �'������ ���� ���.";
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")// ����� �5, �����
            {
    			dialog.text = "������"+ GetSexPhrase("","���") +", ��� ��? � ��� ��� ����� � ���� ����?";
    			link.l1 = "�������, � ������"+ GetSexPhrase("","�") +" ���� �� ��������� ����� ����, ����� �������. ��������� ��� ��������, �� ��������� �� � ����� ���������...";
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = "������������, ������"+ GetSexPhrase("","���") +". � ������ ��� - ����� ����� ���� ����� �� �������...";
    			link.l1 = "��� ����� � �������, ��������� ����, �� ������������.";
    			link.l1.go = "exit";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")
            {
    			dialog.text = "�� ���, �������, ����� �������?";
    			link.l1 = "��� � �������, ������� � �������������� ����� ���� ����� �� ����������...";
    			link.l1.go = "Step_F5_4";
            }
			if (npchar.id == "Captain_1" || npchar.id == "Captain_2")//����� �6, ����� � ������
            {
    			dialog.text = ""+ GetSexPhrase("�����","�����������") +", ��� ����� �� ���� ������� ���� � ������. �� ������� ��c����, �������� - � ��� �� ����� ������! �� �� ������ ������ ��������...";
    			link.l1 = "��, ��� �� �� ����� ������� �����? ��������� ����������...";
    			link.l1.go = "exit";
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "Fr7RockBras_toSeekPlace")//����� �7, ����� � ����������. 
            {
    			dialog.text = NPCStringReactionRepeat("��� ��� ��! ��� ��� ��������� �� �����?!", "��, ����� ��������� ��� ��������. ��� ��� �� �� ���"+ GetSexPhrase("��","��") +", ����"+ GetSexPhrase("�","���") +" ������ �������?", "���������? ��� ��� �� ���"+ GetSexPhrase("��","��") +"?", "��, ����� �������� ��� ��������. ��� �� ���"+ GetSexPhrase("��","��") +"?", "block", 0, npchar, Dialog.CurrentNode);
    			if (LAi_group_GetTarget(pchar) <= 0)
				{
					link.l1 = HeroStringReactionRepeat("� �������"+ GetSexPhrase("��","���") +". ����� ���� "+GetFullName(pchar)+". � ����"+ GetSexPhrase("��","��") +", ����� �������� ���� ������.", "����� ���������... ���� ����� "+GetFullName(pchar)+", � ����"+ GetSexPhrase("��","��") +" �� �����.", "���� ����� "+GetFullName(pchar)+", � ����"+ GetSexPhrase("��","��") +" �� �����.", "����� ��������, �� ������. ���� ����� "+GetFullName(pchar)+", � ����"+ GetSexPhrase("��","��") +" �� �����.", npchar, Dialog.CurrentNode);
    				link.l1.go = "Step_F7_1";
				}
				else
				{
					link.l1 = "������ �� ����� ��������, ���� ����������� �� ����� � ���� �����!";
    				link.l1.go = "Step_F7_Late";
				}
				// --> ���� �������...
				if (GetQuestPastDayParam("questTemp") > 8)
				{
    				dialog.text = "��� ��?..";
    				link.l1 = "� ����"+ GetSexPhrase("��","��") +" �� �����, ���� ������ �'������...";
    				link.l1.go = "Step_F7_8";
				}
				else SaveCurrentQuestDateParam("questTemp"); //����� �� �������� �� ����� ���
				// <-- ���� �������...
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "empty")//����� �7, ����� � ���������� � ���������� ��������. 
            {
    			dialog.text = "�������, � ��� �� ���� ����������� ������������� ����.";
    			link.l1 = "��� � �������, ������� ���...";
    			link.l1.go = "Step_F7_5";
            }
			if (npchar.id == "CaptainGay")//����� �8, ����� � ����� ����. 
            {
    			dialog.text = "�� ��� ���"+ GetSexPhrase("��","��") +"?";
    			link.l1 = "�������, ��� �. ���� ������ �� ����� �������. �� ����� ����� ������������� � ����� ������� ��������.";
    			link.l1.go = "Step_F8_1";
            }			
		break;
//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* �������� ���� �������. ����� �1 **********************************
 		case "Step_F1_1":
			dialog.text = "�� ���"+ GetSexPhrase("","�") +" ��������"+ GetSexPhrase("��","���") +"! �������� � ������...";
			link.l1 = "��, �� �������� �� ���� ���...";
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Legran");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Fr1Legran_afterFightBandits");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* ����� �� � ����������. ����� �2 **********************************
 		case "Step_F2_1":
			bDisableCharacterMenu = true; //��������� �2
			LAi_SetPlayerType(pchar);
            DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto9");
			//StoreEquippedMaps(pchar); // ugeen
			pchar.MapsAtlasCount = 0;
			SetTempRemoveParam(pchar, "items");
			pchar.questTemp.money = sti(pchar.money)/2;
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
			pchar.money = 0;
			DeleteAttribute(pchar, "items");
			DoQuestCheckDelay("Fr2Letter_intoPrison_1", 20);
			AddQuestRecord("Fra_Line_2_DelivLetter", "2");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("������������ ����������","����������� ����������"));
            DialogExit();
		break;
 		case "Step_F2_2":
			dialog.text = "���-���, ��� �� � ���?";
			link.l1 = "� ���, ��� �� ��� ����� �� ���������� �������. ���� ������� �� ��������� ��������� ��������, ���� �� ������ ��������� ������ ����������� ����� �� ���� �������.";
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = "� ��� ���� �����?";
			link.l1 = "�����, ����� �� ����������� � ����� ��������, ������� �������� � ������. ����� ������, ��� � ������������� ������"+ GetSexPhrase("��","��") +" �������-����������� �������.";
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			dialog.text = "�-�-�, �������... �� ��� ��, ��� � ���� ��������, ���� �� �������� ���������� - ��� �����.";
			link.l1 = "�� �����, �� ���������. ��������, � �� �� ������, ������ ���� ��������? ������ ������ �� ����...";
			link.l1.go = "Step_F2_5";
		break;
 		case "Step_F2_5":
			dialog.text = "������, ��� ���... � �� ���� ����� ������, ��� �� �����.";
			link.l1 = "��� � �� � �� ������"+ GetSexPhrase("","�") +"... �����, ��������, �� ����� �������, ��������� � ����. � �� ���� ����� ������� �� �� ���.";
			link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = "������. ��, ��� ���� ������� ������ ������� � ���������� - ��� � ���� ������. �� � ��� ������, ����� ������ ��� ���� �������������.\n"+
				          "�� � ��������� ���������� ��� ����� ��� ������� �� ����� ������. �� ����������?";
			link.l1 = "�������, ���! ��, �� ����� �������, ���� ���.";
			link.l1.go = "Step_F2_7";
		break;	
 		case "Step_F2_7":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
            DialogExit();
			DoQuestCheckDelay("Fr2Letter_intoPrison_3", 10);
		break;	
 		case "Step_F2_8":
			dialog.text = "�� ���������, �������, ��� ������������.\n"+
				          "���� �� ���� �������� ����� ��������� ���� �����. �� ����� ����������� ��������� ������, ������ ������� ������ � ��� ������ �� ���� �����.\n"+
						  "��� �����, �� ������������� ���������� �� ������ �������. � �� ���������, ��� ����� �������. �� ��������, �������.";
			link.l1 = "����� ���"+ GetSexPhrase("","�") +". ����� ���� �� ������� �� �� ���.";
			link.l1.go = "Step_F2_9";
		break;		
 		case "Step_F2_9":
			dialog.text = "��� ������ ���, ��� ���� � ��� ������������. ����������� ��� ��������� ��������� ��������. � ������ ��������� �� �������� ���� - � ��������� ����� ���� ������� �������� ���� ����� ���.";
			link.l1 = "��� ������, ������?";
			link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = "������ ��������, �������, ������ ��������... �� �� �����, ��� �� ����� ���� ���. ��������.";
			link.l1 = "��������, ����� �������-����������.";
			link.l1.go = "exit";
			bDisableCharacterMenu = false; //��������� �2
			AddDialogExitQuestFunction("FrLine_HoverGoOnPrison");
		break;

 		case "Step_F2_12":
			dialog.text = "������� �, " + GetFullName(npchar) + ", ��������� �����, �� ������� ����� ��������! � ������� � ������������ ������� �������� ��������, ��� ��� ���� ���� �� ��������. ����� ������� ������, �� ��������� �����!";
			link.l1 = "�� ��� ��, ����� ������, ��� ��� �������. � �����"+ GetSexPhrase("","�") +" ���, ��� �����...";
			link.l1.go = "Step_F2_13";
		break;
 		case "Step_F2_13":
			AddQuestRecord("Fra_Line_2_DelivLetter", "5");
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.questTemp.State = "Fr2Letter_NiceResult";
			DialogExit();
		break;
//********************************* ��������� ����� ����. ����� �3 **********************************
 		case "Step_F3_1":
			dialog.text = "���� �����... ����� �������, � ����� �� ������... �� ����� ������, ������� � ������ ���, � ����� ���� �����...";
			link.l1 = "� ����, �������, �������"+ GetSexPhrase("��","���") +"... � ����� ��� ��������� �� ����. ������ �����������, ��������...";
			link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			pchar.questTemp.State = "Fr3TakeAnna_HavanaOut";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1.location = "Cuba2";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition = "Fr3TakeAnna_DelivShip";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
//********************************* �������� ����� ����. ����� �5 **********************************
 		case "Step_F5_1":
			dialog.text = "��, ��� ���. ������"+ GetSexPhrase("","���") +", ����� �� ����� ������ ����������� ���������! �������-���������� ������ ��������� ������-�-������ ���������� ������������� �� ����� ������ � ������� ��� �������������� ������� ����� ���� �� �������.\n"+
				          "���, ��� �� �����, �� ������� ������������� ������� ���� ����. � ��� ���� ������� �� ����� - ������� ���������� ������������ ����. �� ������� ����� ����� ���� ������ ����������� �� ���� ����������.";
			link.l1 = "�� ������� �� �� ���������...";
    		link.l1.go = "Step_F5_2";
		break;
 		case "Step_F5_2":
			dialog.text = "����������, ������"+ GetSexPhrase("","���") +". ���� ��� ������� ���������� ������ ���� ����. ��� �������� �� ������, � �������� ���, ��� ��������� ����������. ����� ����������� �������� �������� �����, ��� �� ������� ��� ������!";
			link.l1 = "��, ������� � �� �� ������, ���� ���� ���������� ����������� ��������. �� ����������, ��� � ���� �� �����?";
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = "����� ��� ����������� � �������, � ������ �� ���. �� ���� ���������, ��� ���������� ��������� � ����������������, ����� ������� ���������� �� �������.";
			link.l1 = "���� ������ ����������� �� � ��������! ���� ��� ������ ��������� � �����, ��� �������� ������� �� ���� ��������� ����������. ������� ���, ��������� ����. � ������� �� �����"+ GetSexPhrase("","�") +" � ������� ������, �� ��, �������� �������, ������� ���� � ��������. ��������.";
    		link.l1.go = "exit";
			pchar.questTemp.State = "Fr5AnnaHant_SeekHoseBrothers";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "3");	
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex1", GetSexPhrase("��","��"));
		
			npchar.LifeDay = 1; // ������ ���
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			locations[FindLocation("Mayak10")].DisableEncounters = true; //��������� �������
			LAi_LocationDisableOfficersGen("Mayak10", true); //�������� �� �������
			Pchar.quest.Fr5Anna_InShore.win_condition.l1 = "location";
			Pchar.quest.Fr5Anna_InShore.win_condition.l1.location = "Mayak10";
			Pchar.quest.Fr5Anna_InShore.win_condition = "Fr5Anna_InShore";
		break;
 		case "Step_F5_4":
			dialog.text = "���, ��� ����� ������. ������ ����� ���� ����� ����� ��������� ��������...";
			link.l1 = "�������, ��� ��.";
    		link.l1.go = "exit";
		break;
//********************************* ���������� ���� ���������. ����� �7 **********************************
 		case "Step_F7_1":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "� ��� � ��������, "+ GetSexPhrase("��������","�������") +". �� ���� � �� ����, �����, �� �������, ��� ���� ���� ��������?";
				link.l1 =  "�� ��� ����, ��� ����� ������� �'������. �������, �� ������, ��� ���... �� �����, ������ ����� ��������� ������ �� �������, ��� ���� �� �������. �� ������ ������� ������?";
    			link.l1.go = "Step_F7_2";
			}
			else
			{
				dialog.text = "� ����� ���...";
				link.l1 = "��������� �����, ���� ����������� ��� �� �����...";
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_2":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "���, ���. ������� ������ ���� ���������� ��� ����...";
				link.l1 =  "��� �����... ����� ������ �� ���� �� ����� - ����� �����������.";
    			link.l1.go = "Step_F7_3";
			}
			else
			{
				dialog.text = "���, ���...";
				link.l1 = "��������� �����, ���� ����������� �� ����� �����!";
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_3":
			dialog.text = "������, ��� �������. � ���� ����� �������...";
			link.l1 = "����� ������, ������! � �� ��������.";
    		link.l1.go = "Step_F7_4";
		break;
 		case "Step_F7_4":
			bDisableFastReload = false;
			AddQuestRecord("Fra_Line_7_RockBras", "2");
			AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("��","��"));
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1.location = "Cuba1";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition = "Fr7RockBras_DelivShip";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
 		case "Step_F7_5":
			dialog.text = "��������, � ���� ���� ������������� �� �������� ���� �����. �������� ������ �� ���� - � ������ ������ �������� ����� � ����� �������.\n"+
				          "�� � ���� ���� ���� ������, ������� ������ ��� ������� ������� ������, ��� ������.";
			link.l1 = "������������ �� ����, ��� �����, ��� ��� ����� ���������...";
    		link.l1.go = "Step_F7_6";
		break;
		case "Step_F7_6":
            dialog.text = "� �����, ������ ���� �����������... ��� ������� ���� �� �����, ��� �� ���������, ���� ����������. � ���� ���������� � ���� ���������� ���� ����� ������ � ������ ������ ����� �������...\n"+
				          "��� ��� - �������� �� ����, ���"+ GetSexPhrase("","�") +" �������... � �����, � ���� ���� ��, ��� �� ��� �������.";
			link.l1 = "������, ��������� �������, ����� ������... �� �� �����, �������� ���� � ���� �� ������. ������, ���, �������������...";
            link.l1.go = "Step_F7_7";
        break;
		case "Step_F7_7":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "none", "", "", "", 6.0);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // ������ ���
			pchar.GenQuestRandItem.FortFrance_Dungeon = true;
			pchar.GenQuestRandItem.FortFrance_Dungeon.randitem3 = "cirass5";
			DialogExit();
        break;
 		case "Step_F7_8":
			dialog.text = "�� �������"+ GetSexPhrase("","�") +"... ��� ��� ������ ��� ������ ����... ������... ���� ��� ����� �� ������... �-�-���...";
			link.l1 = "���� ������, �� ����!";
    		link.l1.go = "Step_F7_9";
		break;
 		case "Step_F7_9":
			bDisableFastReload = true;
			LAi_KillCharacter(npchar);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // ������ ���
			pchar.questTemp.State = "Fr7RockBras_RockIsAgony";
			DialogExit();
		break;
 		case "Step_F7_Late":
			bDisableFastReload = true;
			LAi_ActorWaitDialog(npchar, pchar);
			DialogExit();
		break;
//********************************* �������� ���� ��������. ����� �8 **********************************
        case "Step_F8_1":
            dialog.text = "���, ���� �������� ��� �� ����� ������ �� ���� � �������� ����� �����������! �������, ���� ����, ������ ��� ������� � ��, ������ ������� ���, ��� ���� �������, ��� �������...";
            link.l1 = "������. �������� �����, �������...";
            link.l1.go = "Step_F8_2";
        break;
 		case "Step_F8_2":
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", true);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CanFightCurLocation");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	}
}
