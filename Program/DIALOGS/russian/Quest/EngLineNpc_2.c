// ������ ���������� � ������
void ProcessDialogEvent()
{
	ref NPChar;
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
            // ==> ������ ������� ��������
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Bocman_Willams")// �������� �� ���������� ������� ��������
            {
    			dialog.text = "���, �������, ��, �������, ������"+ GetSexPhrase("��","���") +" �������� � ����?";
    			link.l1 = "��, � �����. � ���� ��� �� ���� �� ����� � ��� ��?";
    			link.l1.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "MorrisWillams_GoToHimselfBussines" && npchar.id == "Bocman_Willams")// �������� �� ���������� ������� �������� ������ ���
            {
    			dialog.text = "�������, ������ ����. ��� ����� �, ������ � '��������'.";
    			link.l1 = "��� ������� �� ���� ���?";
    			link.l1.go = "Step_E6_4";
            }
			// ==> ������� ���������.
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoWomen" && npchar.id == "Gillian Atterbury") // ����.������� ����� �6, �������� � �������� ���������
            {
    			dialog.text = "��� �� ������ �� ����?";
                link.l2 = "����������, ������ ���� ����������� ��� ���������� � ���.";
                link.l2.go = "Step_E6_25";
            }
			if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Gillian Atterbury") // ����.������� ����� �6, �������� � �������� ��������� ����� ���� �������
            {
    			dialog.text = "�� ���-������ ������ � ���� ����, "+ GetSexPhrase("���","����") +"?";
    			link.l1 = "���� ���, �� � ���� ���������. � ������ ���, ����� �������� ���.";
    			link.l1.go = "exit";
            }
			if (npchar.id == "Gillian Atterbury" && CheckAttribute(npchar, "TempQuest.SavedHusband")) // �������� � �������� ���������, ���� �� ������ �� ����
            {
                dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("���","����") +", � ������� �� ������, ��� �� ��� ��� �������. �� ������ ����� ����� ���� � �������� ���� ����� �� ������. �� ������� ������ ������� � ���� �����.",
                         "��� ����� ��, "+ GetSexPhrase("���","����") +". � ��� ���� ��� ������!", ""+ GetSexPhrase("���","����") +", �� ������� � ���� ��� � ������� ��� �������. ��� ������ ���������!",
                         ""+ GetSexPhrase("���","����") +", ������� �� �� �� ���������� �� ���, ������, ��� � ��� ������ ����.", "block", 1, npchar, Dialog.CurrentNode);
    			link.l1 = HeroStringReactionRepeat("�� ��� ��, ������... �� ������, ��� ����� �������...",
                                               "������...",
                                               "� ���� ��� �����...",
                                               "��, �� ���� �������! �������.", npchar, Dialog.CurrentNode);
    			link.l1.go = "exit";
    			//ChangeCharacterReputation(pchar, 1); // ���, �� ���� �� ���-�� ������ TO_DO eddy
            }
            // ==> ���� �� �������� � ������, ������������ ���� �������
            if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Bandit3")   // ����� � ������ ����� �������
            {
    			dialog.text = "����...";
    			link.l1 = "��� �� � ��� �� ����� �������?!!";
    			link.l1.go = "Step_E6_30";
            }
            // ==> ��� �������
            if (pchar.questTemp.State == "MorrisWillams_AfterFight" && npchar.id == "Jillians_Husband")   // ����� � ������ � �����, ����.�������, ����� �6
            {
    			dialog.text = "�� ������ ��� �����! �������!";
    			link.l1 = "������������� �����. ���� ����� ��� ���������?";
    			link.l1.go = "Step_E6_32";
            }
            // ==> ���������� ����� � ��������� ����������
            if (pchar.questTemp.State == "ToMansfield_GoOn")   // �������� �� ��������� ������, ���.�������, ����� �8
            {
    			dialog.text = "���������� �����! ����� �������!";
    			link.l1 = "��� ����� ���������?";
    			link.l1.go = "Step_E8_1";
            }
            if (pchar.questTemp.State == "ToMansfield_CatchToPardal")   // ���������� �������� �� ��������� ������
            {
    			dialog.text = "���� ����� �������. ������� ���� ����� ����� �����, �� ������ �� ������.";
    			link.l1 = "��, � ����. �������������, ����� �������...";
    			link.l1.go = "exit";
            }


        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
//*************************************** ������ ������� ������� �������� *********************************
 		case "Step_E6_1":
			dialog.text = "� ������ � ������� '�������'. ������ ������� � ����� ���� � ��� �� ������, �� �������"+ GetSexPhrase("","�") +" � �����...";
			link.l1 = "�����, ���������.";
			link.l1.go = "Step_E6_2";
		break;

 		case "Step_E6_2":
			dialog.text = "��� ��� � �������, �� ��� ����� ����� ������� ����. �� ������ ���� ����� ����. �� ����, ��� ������.";
			link.l1 = "������, ��� ����������.";
			link.l1.go = "Step_E6_3";
		break;

 		case "Step_E6_3":
			chrDisableReloadToLocation = false;
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = characterFromID("Morris_Willams");
            LAi_SetHuberTypeNoGroup(sld);
			FreeSitLocator("PortRoyal_tavern", "sit10");
            ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit10");
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //�� ������ ������, ����� ������ �� ������.
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
            NextDiag.TempNode = "First time";
            DialogExit();
		break;

 		case "Step_E6_4":
			dialog.text = "�������� ����, ������, ������ ������. ��� ��� ������� ������ ��� ��� ��������� �� ������ �� �������.\n"+
                          "������� ������ ������ �������� ���, ��������� ������ ������� ��� �����-�� ������, � ���� �����.";
			link.l1 = "� �� �� ��������� �� ����? ��� ���� �������?";
			link.l1.go = "Step_E6_5";
		break;

 		case "Step_E6_5":
			dialog.text = "������� ���, �������, ��� �����������. �������� ��������� ������� �� �������. �� � �������-�� ���� ���������...\n"+
                          "� �����, ���� ���� �����, ����� �����...";
			link.l1 = "� ��� � ���������� ������, ����� ��� � ����. �� ������, ��� �� ���� �������� � ����� �� ��������. ������ � ������ ��������, ������ �� �����������.";
			link.l1.go = "Step_E6_6";
		break;

 		case "Step_E6_6":
			chrDisableReloadToLocation = false;
    	    npchar.LifeDay = 1; // ������ ��� �� ����.����.
    	    SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			pchar.questTemp.State = "MorrisWillams_ArrestedToPrison";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "15");
            ref sld = characterFromID("Morris_Willams");
			LAi_SetStayType(sld);
            ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
            RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
            LAi_SetPlayerType(pchar);
			DialogExit();
		break;

//*********************************** ������� �������� ��������� *************************************
		case "Step_E6_25":
			dialog.text = "� ��� ����, "+ GetSexPhrase("���","����") +"?";
			link.l1 = "�� ���������, � �� ������� ��� ���. ��� ����� ���� ����� ������ ����� � �����������. ��������� � �������, � ��� ����� ��������.";
			link.l1.go = "Step_E6_26";
		break;

        case "Step_E6_26":
			dialog.text = "(�����) "+ GetSexPhrase("���","����") +", ��� ������. ��� ��� ��� ������.";
			link.l1 = "����������� � ���������� ���������, ����������.";
			link.l1.go = "Step_E6_27";
		break;

        case "Step_E6_27":
			dialog.text = "�� ��������� ���������� ������ � �� ��������� ���� �������. ����� �� ������ � ��� ����� � ������ ����, ��� ������ ��� � ������, ���� � ������� ������ �� �� ������ ���� � ����������.\n"+
                     "�� ������ ���, ��� � ��� ����, �� ��� �� ������� ���������, ���������� �� ��� �� ����� �����.\n"+
                     "��� ������ ��� �� �������� �������, �� ������� ���� ��� ������ ������� �� ������� ���������� �����.\n"+
                     "����� ��� ����� ������ ������. ����� �� �� ��������, �� ����� ����� �����, ���, �� ��� ������, �������� ��� �� ������� ��������� � ������.\n"+
                     "����� �� ���� ���� �������� � ������, ����� �������� �� ������, �������� � ���� � ����. �� �� ��� ��� �� ��������. � ����� �����!";
			link.l1 = "� ���� �� �����? �� ���� ���-������ ������?";
			link.l1.go = "Step_E6_28";
		break;

        case "Step_E6_28":
			dialog.text = "�� ������ ������, ��� ���� �� �����. ������ ������, �� ����� ������ (������). "+ GetSexPhrase("���","����") +", � ������ ���, �������� ��� ����� ����� ����!";
			link.l1 = "� ������ ���, ��� � ���� �����.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_SeekHusband";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "20");
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1.location = "Jamaica_Grot";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition = "MorrisWillams_HusbandInCave";
		break;



//**************************** ������� ������� � ������, ������ ���� �������� ****************************
 		case "Step_E6_30":
			dialog.text = "�������� "+ GetSexPhrase("���","��") +", ��� ��������� �� � ����...";
			link.l1 = "��...";
			link.l1.go = "Step_E6_31";
		break;

 		case "Step_E6_31":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "MorrisWillams_AftreFightingInCave");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//************************************** ������� ���� �������� ***********************************
 		case "Step_E6_32":
			dialog.text = "��, � ������ �� ������? ���� ��� �������, � ��� ��� ������ ������, ��� ��������� ��������!";
			link.l1 = "�������� ���, ��� ���������?";
			link.l1.go = "Step_E6_33";
		break;

 		case "Step_E6_33":
			dialog.text = "���� �� ���� � ���� ������... ���-�� ��� ����� �� ����� ����� � ���� � ����������...";
			link.l1 = "��� ��� ��� ��������, ����������� � ���� �������, ��� �� ���� �� ����� �����. ��� �� �������� � ����������?";
			link.l1.go = "Step_E6_34";
		break;

 		case "Step_E6_34":
			dialog.text = "���� ������ �������� ������ � ����������������! ����� � �������, ��� � ��� ��� � ������� ���� ����� �������� ����������. � ��������, ����� �� ������, � ���������� �� ���.\n"+
                          "��� ������� ���������� �� ��� ����������� �� ����� �����, ����� � ����� � ������. ���� �������� � ���������� ����. ��� ������ ����� ����, �� ������ ������� ��������, ��� �, � ��������, ���������� �� ���� ��������.\n"+
                          "�� ������� �������, "+ GetSexPhrase("���","����") +". ��������� ��� �� ����� ������!";
			link.l1 = "��� ����. ������ ���� � ����� � ����, ��� ����� �������� ����� �������������. ��������, ��� ������ ����� ���������� ���. �� �� ���� ���� ������ �� �����, � ����� �������� �� ������.";
			link.l1.go = "Step_E6_35";
		break;

 		case "Step_E6_35":
			Characters[GetCharacterIndex("Gillian Atterbury")].TempQuest.SavedHusband = 1; // ���� �������� ������� �� ������...
            AddQuestRecord("Eng_Line_6_MorrisWillams", "21");
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            pchar.questTemp.State = "MorrisWillams_AfterFightGoRedmond";
			DialogExit();
		break;

//************************************** ������� ���������� ��������� ***********************************
  		case "Step_E8_1":
			dialog.text = "������� �� ���� �������� ������� � �����, ���������� � ����� ���� ��������� �������.";
			link.l1 = "���� ������! � ��� ��������?";
			link.l1.go = "Step_E8_2";
		break;

   		case "Step_E8_2":
			dialog.text = "����, ��� � ������ ������. ����� �������� ���������� ������ ��������� �� ���������. � ������, ��� ��� ����, ����� ����� ������ �� ����.";
			link.l1 = "���-�� � �� ����� ����������. ����� ��� �� ��������� ����� ���������?";
			link.l1.go = "Step_E8_3";
		break;

   		case "Step_E8_3":
			dialog.text = "�� ���� ����� ����� � ��������� ��� ���� ����� ������.\n"+
                          "��� ����� � �������� ��������� � ������ ������������� ���, ����� ��� �� �������� ����� �� ����� �� �������.\n"+
                          "�� ����������� ������� �� ��������� �������, �� ��� ����� ���������� ������� ���������� ��� ��������� ������.\n"+
                          "����� �� ������ �� ����� - ��� ������� ��� �� ��������� � ����������, � �� ������ ������ �������...";
			link.l1 = "���� ������! � �������"+ GetSexPhrase("","�") +" � ��������� �� ��������� ���������. � ����"+ GetSexPhrase("��","��") +" ������� �������������� ��� ���� ������.";
			link.l1.go = "Step_E8_4";
		break;

   		case "Step_E8_4":
			dialog.text = "��� ������� �������. �������� �����.";
			link.l1 = "��� ��� �� ������ �������?";
			link.l1.go = "Step_E8_5";
		break;

   		case "Step_E8_5":
			dialog.text = "� ����, ��� ��� ���� �� ����, � ��������.";
			link.l1 = "������ �� ��� ������?";
			link.l1.go = "Step_E8_6";
		break;

   		case "Step_E8_6":
			dialog.text = "����� ���� ��������� �������, � ����������� ������� � ����� ��� ���, � �������.\n"+
                          "� ������� ������� ��-�������� � ������ �������� �� ��������, ��� ��� ����� ��������.\n"+
                          "��� �������� ���������, ��������� �� ������� ���, ��� ����� � ���� �� ��������. �� ������ ������, ���������� � �����. ���� �� ���������, ��� � ������ �� ��������.";
			link.l1 = "�������... �� �� ������� �� ��� ������ �������? ��� ����� ������������ ��������� ������ � ���� �����? ��... �����, ������� ����. ����� �������� ���� ��������. ������� ��, ��� � ������.";
			link.l1.go = "Step_E8_7";
		break;

   		case "Step_E8_7":
			dialog.text = "�������. ���� ������ ������� �������� � ����, �� ����������.";
			link.l1 = "�� ��������, �������-�� �� � ����� �������.";
			link.l1.go = "exit";
			pchar.questTemp.State = "ToMansfield_CatchToPardal";
			AddQuestRecord("Eng_Line_8_ToMansfield", "2");
		break;
		
        case "You_baster":
            dialog.text = "� � ����������� ���� �� ���, ��� �� �� ���� ��� ���������...";
            link.l1 = "���������� ���, ���: '��� ������ ��� ����� �������. �������� ������ ������ ����������, ������ � ������ � ������� ���������... �������-������������.' ��������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "You_baster";
			pchar.questTemp.jailCanMove = true;
        break;
    }
}
