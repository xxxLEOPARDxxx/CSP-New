// ������ ���������� � ������
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
            //����������, ����.�������, ����� �1
            if (npchar.id == "Albermal")
            {
                dialog.text = "� ��� ����������� ������.";
                link.l1 = "���� ����� " + GetFullName(pchar) + ". � �������"+ GetSexPhrase("","�") +" ����������� ���������� �� ����������� ���������.";
                link.l1.go = "Step_E1_1";
            }
            // �������� � �������, ����� �4
            if (npchar.id == "Hoverd_Tantum")
            {
    			dialog.text = "���, "+ GetSexPhrase("�������, ������","��������, �������") +"?";
    			link.l1 = "�����������?";
    			link.l1.go = "Step_E4_1";
            }
            // ==> ��������� ����� �����,  ����� �5
            if (npchar.id == "Orange_Comendant")
            {
    			dialog.text = "����... ��������� ���������� ���! ���� "+ GetSexPhrase("������","�����") +" ����� �������� �����...";
    			link.l1 = "��������...";
    			link.l1.go = "Step_E5_1";
            }
            // ==> ����� �6, ������ �������
            if (npchar.id == "Morris_Willams")
            {
                dialog.text = "���� ������� ��� ����, ����� �� ���"+ GetSexPhrase("��","��") +" �� ��� �� ������...";
                link.l1 = "��, ��� �� ���...";
                link.l1.go = "exit";
            }  
            if (pchar.questTemp.State == "MorrisWillams_GoToMorrisBegin" && npchar.id == "Morris_Willams")
            {
    			dialog.text = "�����������! ������ �������� � ���� �� ������?";
    			link.l1 = "����"+ GetSexPhrase("��","��") +" ���������� �� ���������� ������. �������, �� ���� ��� ��������� �������!";
    			link.l1.go = "Step_E6_20";
            }
            if (pchar.questTemp.State == "MorrisWillams_AfterFirstTalkingWithMorris" && npchar.id == "Morris_Willams")
            {
    			dialog.text = "�� �� ��� ��� �������� " + pchar.name + ". � ���������� ��� ��������� � ���� �����.";
    			link.l1 = "����� ������.";
    			link.l1.go = "exit";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Morris_Willams")
            {
                LAi_ActorSetSitMode(pchar);
                dialog.text = "���� ������! � ���������� ����, ����� � ���� � � ���� ��� �� ������������ ����! �� ���������"+ GetSexPhrase("","�") +" ����!";
                link.l1 = "���? ��� �����������?";
                link.l1.go = "Step_E6_2";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordPolitic" && npchar.id == "Morris_Willams")
            {
                dialog.text = "��, ��� ������ ���� ���� �������� � ������� �����������?";
                link.l1 = "��� ������ ��� ����������, ��, ������, ��� ������. �������� �� ������ ���� �����.";
                link.l1.go = "Step_E6_6";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceNotFound" || pchar.questTemp.State == "MorrisWillams_2PinnaceNotFound")
            {
                dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ��� ������?";
                link.l1 = "� ������"+ GetSexPhrase("��","���") +" �� �������, �� �� ����"+ GetSexPhrase("","��") +" ������� ���� ��� �����, �� ���� �� ����. ������...";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoard" && npchar.id == "Morris_Willams")
            {
                dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ��� ������?";
                link.l1 = "� ������� ���-����� � ��������"+ GetSexPhrase("","�") +" ��� ����� ��������� �����. ������ � ������ �� ��������� �� ������, �� �������, �� �������� ������.";
                link.l1.go = "Step_E6_10";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoardNotFoundMoney" && npchar.id == "Morris_Willams")
            {
                dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ��� ������?";
                link.l1 = "� ������� ���-���� � ��������"+ GetSexPhrase("","�") +" ��� ����� ��������� �����. ������ � ������ �� ��������� �� ������, �� �������, �� �������� ������. � �������"+ GetSexPhrase("","�") +" ���� �������, �� ������ ������� �� ���"+ GetSexPhrase("��","��") +", ������.";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_DieHard" && npchar.id == "Morris_Willams")
            {
                dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ��� ������?";
                link.l1 = "������, �� ���� ����� �������� ��� �� �� �����. � �� �����"+ GetSexPhrase("","�") +" ����� ���.";
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceSink" && npchar.id == "Morris_Willams")
            {
                dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ��� ������?";
                link.l1 = "������ ����� ����� �� ���, � ������ � ��� � ���� ���� ����. � ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +", ������.";
                link.l1.go = "Step_E6_11";
            }
			// ==> ����� �12, ������� � ����������� ������� ������
            if (pchar.questTemp.State == "ColonelLinch_GoToKingstown")
            {
                dialog.text = "� ��� � ���� ����� �������������? �������������!";
                link.l1 = "� ���������� �����, ���. ��� ��� - " + GetFullName(pchar) + ".";
                link.l1.go = "Step_E12_1";
            }

            if (pchar.questTemp.State == "ColonelLinch_ArrestModiford")
            {
                dialog.text = "�� ������ ���������� ���������. ������������.";
                link.l1 = "������, ���.";
                link.l1.go = "exit";
            }
        break;

//<<<<<<<<<<<<===== ������� �������� �� ���������� =====================
        case "Step_E1_1":
            if (GetQuestPastDayParam("questTemp") < 2)
            {
                dialog.text = "�� � ��� ������� ������ � ���������� ������?";
                link.l1 = "� �����"+ GetSexPhrase("","�") +", ������������ ����������.";
                link.l1.go = "Go_with_Albermal";
                link.l2 = "�����, ��� ����� ��������� ������. ����������� ����� �������.";
                link.l2.go = "exit";
			}
			else
			{
				dialog.text = "�� ������������ �������������� � ����������� ������� ��� ���������! �� �� ������, ��� � ��������� �� �������. ������� ����� �����?";
				link.l1 = "���, ����� �������� �� ��������, �� ��� ���� ������� ��������������. ������ � �����"+ GetSexPhrase("","�") +", ��������� ����������!";
				link.l1.go = "Go_with_Albermal";
				link.l2 = "���, ��� ����� �������� ��� ��� ���������������� �����������. � �� ���� ���������� ���� ����� �������������� ����� ��-�� ������������� ���������� ��������. ����� ��� ��������� ��� �������.";
				link.l2.go = "exit";
				ChangeCharacterReputation(pchar, -1);
            }
            NextDiag.TempNode = "Step_E1_1";
        break;

        case "Go_with_Albermal":
            AddQuestRecord("Eng_Line_1_Albermal", "2");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1          = "location";
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1.location = "Antigua";
			pchar.quest.fight_withSpanish_Albermal.win_condition             = "fight_withSpanish_Albermal";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "in_the_SentJons":
            if (GetQuestPastDayParam("questTemp") < 14)
            {
                dialog.text = "� ���������� ��� �� ���� ����. �� �������� ��������� ������� � �������� � ��������� �����������. � ���� ��, � ����-����� �� ������ � ����. � ��� ��� ������ ��� ���� ������ ���������, ��������� ��� ������ ��� ����� � ����. ��������!";
                link.l1 = "������� ������ �� ������! ��������, ���.";
                link.l1.go = "Albermal_go_out";
                pchar.questTemp.State = "Albermal_good_time";
            }
            else
            {
                dialog.text = "� ���������� ��� �� �������, ����������� � �������� � ���������. �� ��-�� ����� �������������� ������� ��� ��� �����! � ������� � ���� ������ ��� ���������. ��������, � ��� ������ �� ����������.";
                link.l1 = "����� ����������, ���.";
                link.l1.go = "Albermal_go_out";
                ChangeCharacterReputation(pchar, -4);
                pchar.questTemp.State = "Albermal_late";
            }
            GiveItem2Character(pchar, "letter_Albermal");
            NextDiag.TempNode = "in_the_SentJons";
        break;

        case "Albermal_go_out":
            AddQuestRecord("Eng_Line_1_Albermal", "4");
            RemovePassenger(pchar, npchar);
            DialogExit();
            // ������
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload2", "none", "", "", "", 10.0);
            LAi_SetPlayerType(pchar);
    	    NPChar.LifeDay = 1; // ������ ��� �� ����.����.
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* ������� ��������� �� ���������� ������ �������� **********************************
 		case "Step_E4_1":
			dialog.text = "���, ���������. ������"+ GetSexPhrase("��","���") +" �� ��������. � ��� ��������� ��? ��� �� ��� ��� � ������ ��-�� ����?";
			link.l1 = "��� ��������� ����� ����� �� ��������� - ���������� ��������. � ���� ���� � ���� ������� �����������, ��, ����� �� �� ������������, �� ������ ������ � ���� ����������, ������� ������ � ������. ������ � ��������� � ��������.";
			link.l1.go = "Step_E4_2";
		break;

 		case "Step_E4_2":
			dialog.text = "��, ������ �� ������ ������... � ��� �� ���� �� ��� ���������"+ GetSexPhrase("","�") +"?";
			link.l1 = "������ ������������� � ���-����� ��������� �������. � ������, �� �����"+ GetSexPhrase("","�") +" ���� �� �������, �����"+ GetSexPhrase("","�") +" ����� ������ ����������.";
			link.l1.go = "Step_E4_3";
		break;

 		case "Step_E4_3":
			dialog.text = "���, ������ ������-��������"+ GetSexPhrase("",", � ��� ����� ��������-��������") +" � ������ �� ����, �� ��� ���������, ������. ������, ��� ���� ����, ����� ���� �� ����� ����������� ���� ����� �����, ����� �� �� ��������"+ GetSexPhrase("","�") +" �������, ���� ����� � ��������� � ����� ������������ ��� �� � ����. ��, ����� ���, ��������� ������� � ������.";
			link.l1 = "�������� ��� ��������� - � � ����� �� ��������.";
			link.l1.go = "Step_E4_4";
		break;

 		case "Step_E4_4":
			dialog.text = "� ������ ���� ����� �� �������. �� ������� �����, ��� ������ � ����. ����� ��� �� �����, � ���� � ������� ���� �����...";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ��� �, ������� ����.";
			link.l1.go = "Step_E4_5";
		break;

 		case "Step_E4_5":
			dialog.text = "������ ���������� ���"+ GetSexPhrase("","�") +", ����� � ���� �� ��������. ������, ��� � ���� ��� ������, ��� ���� ����� �� ��������� ��������.\n"+
                          "������. �������, ����� ����� ����� � ���������.";
			link.l1 = "��� �� �� ����������. ������, ����. ��� ��� ������� �� ������.";
			link.l1.go = "Step_E4_6";
		break;

 		case "Step_E4_6":
            DoQuestReloadToLocation("Villemstad_prison", "goto", "goto12", "");
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "7");
            ChangeCharacterReputation(pchar, -1);  // �� �����.
            GiveItem2Character(pchar,"blade1");   // �������� �����; � ����� �� �� �����, �� ��� ������ ������� �� ��������.
            EquipCharacterbyItem(pchar, "blade1");
            pchar.questTemp.State = "Intelligence_Curacao_OutPrison";
			pchar.questTemp.jailCanMove = false; //�� ������ ������
			//==> ������ ������ ��������, � �� ���� ���������� 
			for (int i=1; i<=4; i++)
			{
				sld = characterFromId("VillemstadJailSold_"+i);
				if (sld.location.locator != "soldier3")
				{
					ChangeCharacterAddress(sld, "None", "");
				}
			}
			ChangeCharacterAddress(npchar, "None", "");
			DialogExit();
		break;
//*************************************** ������ ���������� ����� ����� *********************************
        case "Step_E5_1":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "AttackFortOrange_AfterFightWithCommendant");
            ChangeCharacterHunterScore(pchar, "holhunter", 70);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//**************************************** ������� ������� �������� **************************************
        case "Step_E6_2":
            dialog.text = "��������, �� ��� ������������.";
            link.l1 = "������ �� �������. ����� ������������?";
            link.l1.go = "Step_E6_3";
        break;

        case "Step_E6_3":
            dialog.text = "���� �������� ���������� ������������.";
            link.l1 = "� ����� ���� �� ����! � ���, �� � ��������� ������?";
            link.l1.go = "Step_E6_4";
        break;

        case "Step_E6_4":
            dialog.text = "���� ��� �����!";
            link.l1 = "� ���������, ��� ���� �����.";
            link.l1.go = "Step_E6_5";
        break;

        case "Step_E6_5":
            AddQuestRecord("Eng_Line_6_MorrisWillams", "4");
            pchar.questTemp.State = "MorrisWillams_ToModifordForCoolTalking";
            NextDiag.CurrentNode = "Willams_waiting";
            DialogExit();
        break;

        case "Willams_waiting": // ���� �� �������� � ������� � �������� �� ���������� ��������� � ����������
            dialog.text = "�� ���, �����"+ GetSexPhrase("","�") +" ���-������?";
            link.l1 = "���� ���, �� � ����������� ��������� � ���� �����. ��� � ������ �� ����� �� �������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_waiting";
        break;

        case "Step_E6_6":
            dialog.text = "�� ������ ���������"+ GetSexPhrase("","�") +" ����. ���� ����� ��� � ���� � ��������� ������.\n"+
                          "��� ������ � ����� �� ����� � �����, �� � ������ ����������� ��������� �����, ��� ��� ��� �������� �������� ������ ������� ���������. �� ������������ ��� ����� � ����, � ��� ������� ��������� ��� ������� ������� �����. ��� ���!";
            link.l1 = "������� �� ������?";
            link.l1.go = "Step_E6_7";
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); //��������� ����� �� ������
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
        break;

        case "Step_E6_7":
            dialog.text = "��� ���� ���������� ��� ����� �����.";
            link.l1 = "������ ���, ���� ���� - ���� ��������. �� �������� � ���� ������.";
            link.l1.go = "Willams_GoogBye";
            link.l2 = "� ���� ���� 140 000. � �������"+ GetSexPhrase("","�") +" ����� �����, ���� ��-�� ���� �� ����� � �������. ��� ��� ���� � ����� ���� ��������.";
            link.l2.go = "Willams_GiveMoney";
            link.l3 = "� ����� ���� �����.";
            link.l3.go = "Willams_BackGoods";
        break;
        
        case "Willams_GoogBye":
            dialog.text = "� ���� ��������, ������� ���� (� �������).";
            link.l1 = "�� ����� �� ��� �������, �����... ������.";
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.Waiting_time = "10";
            pchar.questTemp.CurQuestNumber = "7";
            ChangeCharacterReputation(pchar, -100); 
            AddCharacterExpToSkill(pchar, "Leadership", -350);
            AddCharacterExpToSkill(pchar, "Accuracy", -50);
            AddCharacterExpToSkill(pchar, "Commerce", -150);
            AddCharacterExpToSkill(pchar, "Sneak ", -150);
            AddCharacterExpToSkill(pchar, "Fencing  ", -100);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "6");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            NextDiag.TempNode = "Willams_Fack";
			//�����
			AddSimpleRumour("�������, ����� �����, ��� �� ��������� � �������� ��������� �� ������ �������...", ENGLAND, 5, 1);
        break;

        case "Willams_Fack":
            dialog.text = "�� ������ ������������ �������, ������� " + GetFullName(pchar) + ". � �� ����� � ���� �������������.";
            link.l1 = "��� ������, �������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_Fack";
			//�����
			AddSimpleRumour("������ ������� ������������ � ��� ����� ������ ����! ��������� ���, ��� �� �������"+ GetSexPhrase("�� ��������","�� ��������") +"...", ENGLAND, 5, 1);
        break;

        case "Willams_GiveMoney":
            dialog.text = "��� ��� ��, ����� ����� � ���� ���. ��� �, � ���� ����� ����� � �������, ���� �� �� ��������.";
            link.l1 = "��, �����, �������"+ GetSexPhrase("","�") +" �� ����... �� ������, � ����� �������, ����� ����� ���� �� ��������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Step_E6_7";
            if (sti(pchar.money) >= 140000)
            {
                dialog.text = "�� �����"+ GetSexPhrase("��","��") +" � ���������"+ GetSexPhrase("�� �������","�� �������") +", �������. ������ ���������� �������� ��� ���� �� ������ ����. � ������ ��� ������, ��� ��� ��� ��� ������ ����������. ��������� ����.";
                link.l1 = "�� ����� ��������������, ��� ���� � ��� ����. ��� �������� ���� �����, ������� ��������� ���� � ����. �� ��������, ����.";
                link.l1.go = "exit";
                SaveCurrentQuestDateParam("questTemp");
                pchar.questTemp.State = "empty";
                pchar.questTemp.Waiting_time = "5";
                pchar.questTemp.CurQuestNumber = "7";
                ChangeCharacterReputation(pchar, 20);
                AddCharacterExpToSkill(pchar, "Leadership", 150);
                AddCharacterExpToSkill(pchar, "Commerce", 250);
                AddCharacterExpToSkill(pchar, "Sneak ", 50);
                AddCharacterExpToSkill(pchar, "Defence", 150);
                AddQuestRecord("Eng_Line_6_MorrisWillams", "7");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("","�"));
                CloseQuestHeader("Eng_Line_6_MorrisWillams");
                AddMoneyToCharacter(pchar, -140000);
                NextDiag.TempNode = "Willams_NiceTalking";
				//�����
				AddSimpleRumour("�������, �������, �� ������� �������� ��������, ������� ��� ����. �� ����������� �������, �������, ��� ���� ����� ������������� � ����!", ENGLAND, 5, 1);
            }
        break;

        case "Willams_NiceTalking":
            dialog.text = "����� ��� ������ ������ �����! ��� ���������, ������� " + GetFullName(pchar) + "?";
            link.l1 = "��� � �������, ������. �������, � ���� ���� ��� � �������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_NiceTalking";
        break;

        case "Willams_BackGoods":
            dialog.text = "����� �� � ������� �� ���, �� �� ����, ��� ������� � ����� �� �������.\n"+
                          "� ���� ������� �����. �������������� ����� ������� ��� ������ ���� �������. ���� ����� ������, ����� �������� ��� ���������� ��� �������, � ����� - ���� �� �����!";
            link.l1 = "��-������, ��� ����� ��� �����?";
            link.l1.go = "Step_E6_8";
        break;
        
        case "Step_E6_8":
            dialog.text = "���� ���� �������� � ������ �������, ��� �� ���!\n"+
                          "� ��� �� ����, ����������� � �������, � �������, � �����, � ����� � �� ����� ��������� ������� ��������.";
            link.l1 = "������ ������, ����� �� ����.";
            link.l1.go = "Step_E6_9";
        break;

        case "Step_E6_9":
            dialog.text = "�� ��, ����������, ����������. ��� ���� - ������� ������, ������� � ������, ��������� ���� ���� �������.";
            link.l1 = "������. ��� ���� �����, � ���� ����� � ���������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
            pchar.questTemp.State = "MorrisWillams_SeekSpanishGoods";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "8");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("��","���"));
        break;

        case "Willams_WaitSeek":
            dialog.text = "��������"+ GetSexPhrase("","�") +" ���-������? ����� � ������ ���� ����?";
            link.l1 = "� ���� ���������, ���.";
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
        break;

        case "Step_E6_10":
            dialog.text = "���� ������! � ���� �� ������� ��� �����?";
            link.l1 = "������� �� ����, ��������, ������� ������������ ���-�� �� ������. ������.";
            link.l1.go = "MorrisWillams_NotGiveMoney";
            link.l2 = "�������, ������� ������� ��� �� ������. � ����� �������� � ���"+ GetSexPhrase("��","��") +" ��� ����� ����� �����! ��� ���� ������, ������ �� ������ ������������ � �������.";
            link.l2.go = "MorrisWillams_GiveMoney";
            NextDiag.TempNode = "Willams_NiceTalking";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
        break;

        case "MorrisWillams_NotGiveMoney":
            dialog.text = "���, � ������. ��� �, "+ GetSexPhrase("�������","�������") +", ������� ����, �� ������"+ GetSexPhrase("","�") +" ���, ��� ���"+ GetSexPhrase("","��") +".";
            link.l1 = "�����, ������. ����� ���� ��������� ������.";
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.Waiting_time = "10";
            ChangeCharacterReputation(pchar, -100);
            AddCharacterExpToSkill(pchar, "Leadership", -150);
            AddCharacterExpToSkill(pchar, "Accuracy", -200);
            AddCharacterExpToSkill(pchar, "Commerce", -250);
            AddCharacterExpToSkill(pchar, "Sneak ", -170);
            AddCharacterExpToSkill(pchar, "Fencing  ", -140);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "13");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("","�"));
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			//�����
			AddSimpleRumour("�������, �������, ��� �� ����� ���� ������ ������� �������� ��� ����� � �������...", ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GiveMoney":
        if (sti(pchar.money) >= 140000)
        {
            dialog.text = "�� �������"+ GetSexPhrase("","�") +" �����, �������! ������ �� ��� ���� ��������. ��� ����� ���� ������ �������������. ������... ���� ���� ������, �������� ������� � ����� ���� ������ �����������. �� "+ GetSexPhrase("������� �����������","������� �����������") +" �, ��������, ������� ������� ��, �� ��� � � ��� ������� �������� ��� � �� ������.";
            link.l1 = "��, �������������. ������ ������, ��� ��� �� ������ � �� ��� �� �������� ����� ��������� ����������.";
            link.l1.go = "Step_E6_14";
        }
        else
        {
            dialog.text = "� ��� ������? � ���� �� �� ���!";
            link.l1 = "��� ����, �����"+ GetSexPhrase("","�") +" � �����. ������ ������, � ��� 140000 ����� � ����, �� ��������.";
            link.l1.go = "exit";
            NextDiag.TempNode = "MorrisWillams_GiveMoney";
        }
        break;

        case "Step_E6_14":
            dialog.text = "������ - ��� ������, ������ ����� �� �������, �������, ���. �� �������� ������ ������... \n"+
                          "��� � ��������� ���� ����� ��� ������ ����� ������� �� ���� �� ������ �����, � ����� ������. �� ���� ��������� ������ ����� ������ �������� ���� �������. ��������� ��� � �������� ������ �� ������.\n"+
                          "����� ��������� � �� ������ ���� �������� � ��� �������� ������, ��������� ������� ����� - ��������� ��������� �������.\n"+
                          "��� � ���� ��, ����� ������ ���������� ��������, � ���� �� ����� ������, ��������� ������������ ��������� � � ������� ������� �������� ������. ����� � ���� ��������� � ������� �����, �� ��� ���������� � ����� ���������� � ������ ��������� ���� �� ������ �����.\n"+
                          "� ��� ���� � ���, ��� ����� �������� �� ���-��� ��������� �� ������ ��������, ��� ��� ��������� ����������� �������� �����, ������� ��������� ��� �� �������. �� �������� ���� ������� �� ���� ������� �������� ������� ���� �� ������� � ���� ������, � ����� � ����� �������� ��������.\n"+
                          "��� � ������� - ����� ���� ������� ������������� �������������, ������. ����� �� ��������� ������, ����������� ��� ���� �������. ������ ��� ������ �� ����� �� �����, �� ���, �� ������. ��� ��� � �� ��� ��� �� ����, ��� ��� ������� � ��� � ����. �� �� ����� �������� ������ �������, �������, ������������� �� ������.\n"+
                          "�� � �� ������ ���"+ GetSexPhrase("","�") +", ������ � ����������. ��������, ��� ������ ������ ������ � �������� �������� � ������ ���� ��� ��� ����. ��� ��� �����...\n"+
                          "� ������, ���� �� ����, �������� �����. � �� � ������� ����, � � ���������� ������������ �������� � ����� � ���.";
            link.l1 = "��� �, ��������� ����, ����. � �������, ����� � ���������.";
            link.l1.go = "exit";
            pchar.questTemp.Waiting_time = "2";
            ChangeCharacterReputation(pchar, 20);
            AddCharacterExpToSkill(pchar, "Leadership", 250);
            AddCharacterExpToSkill(pchar, "Accuracy", 100);
            AddCharacterExpToSkill(pchar, "Commerce", 250);
            AddCharacterExpToSkill(pchar, "Sneak", 70);
            AddCharacterExpToSkill(pchar, "Fencing", 150);
            AddCharacterExpToSkill(pchar, "Defence", 150);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "14");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("","�"));
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            AddMoneyToCharacter(pchar, -140000);
            NextDiag.TempNode = "Willams_NiceTalking";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
			//�����
			AddSimpleRumour("������ ������� ����� ������ � �������, ���"+ GetSexPhrase("��","��") +" �� �������"+ GetSexPhrase("��","��") +" ������, ���������� ��� � �����"+ GetSexPhrase("�� �������","�� �������") +". ��������������, ������, ������ ������������! �� ����� ����, ��� ��� ����� ����� ���� �� �����.", ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GoAway":
			chrDisableReloadToLocation = true;
            LAi_SetActorType(npchar);
            ChangeCharacterAddressGroup(npchar, "PortRoyal_tavern", "tables", "stay8");
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
            NextDiag.CurrentNode = "First time";
            DialogExit();
        break;

        case "Step_E6_11":
            dialog.text = "�� ���"+ GetSexPhrase("��","��") +" �� �� ������ �����������. ��� ������ ������, � �� ��������� �������...";
            link.l1 = "�������� �� ������� � �������, � ��� �� ��������� ���� ������.";
            link.l1.go = "Step_E6_12";
            link.l2 = "������, ���� ������� ��� ��� �������� �������. � �����-�� ������, � ���� ����� �� ������"+ GetSexPhrase("","�") +". ������ � ���� ������.";
            link.l2.go = "Willams_GoogBye";
        break;

        case "Step_E6_12":
            dialog.text = "�� ��� �, ���� ���������� �� ����� ������. � ��� �� ����������� �����������?";
            link.l1 = "���� �� ����. ����� ���������, ��� ����� ������, � ����� ��� ����� ��������� �������.";
            link.l1.go = "Step_E6_13";
        break;

        case "Step_E6_13":
            dialog.text = "���� ��-������. " + pchar.name + ", ������� ��� �� �������� ���� � ����. ������ ��� ����� ���� �� �����, �������� �����.";
            link.l1 = "�� ���������, ��� ����� ������.";
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.State = "MorrisWillams_GoToHimselfBussines"
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1.location = "PortRoyal_tavern";
            Pchar.quest.MorrisWillams_Arrest.win_condition = "MorrisWillams_Arrest";
        break;

        case "Step_E6_20":
			dialog.text = "��� � ����. ��� ������� ����������� ��������� �������, ��������� �� ���� ��������.\n"+
                          "��� ������ �������� ���� ������-���������, � �� ��������� ������, ������ ����, ����� ������ ������������� ���. � ���� ������� �� ������� �� �������!";
			link.l1 = "������ ����� ��������?";
			link.l1.go = "Step_E6_21";
        break;
        case "Step_E6_21":
			dialog.text = "��������, � �� �������� ����� ������� ���������� ����� �� ������ �������. ���������, ����, ��� �� ����� ������ �� ��������, ������� ����������� ��� ���.";
			link.l1 = "��, � ������� ������ ��������� � �������� ������� �� ������������ ����������, ������� �������, ��� ���� ��������� �������. ���������� ����������� �����, ��� ���� ������ ������, �� ��������� ����. ������� ���������, ��� �������, �������� ���������� ����� ������� �� �������. �� �������� �� �� �������, ��� ���� ������� ���������.";
			link.l1.go = "Step_E6_22";
        break;
        case "Step_E6_22":
			dialog.text = "��������� ������������ ������ ����� ������ ������� ���� �������. ��� � ��� �����, ���� � ���������� ������ ������ �� ����.\n"+
                          "�����, ������, ����� ����"+ GetSexPhrase("��","��") +"?";
			link.l1 = "����� �������� ���� ���� ���������� �������� � ���� ����� � ����������� �������� ����� � ��������� �������.";
			link.l1.go = "Step_E6_23";
        break;
        case "Step_E6_23":
			dialog.text = "��, � ���� ����������� ��������� ������, � ���� ���� �� �������, ��� � ���� ���������� �����.";
			link.l1 = "������������� ����������� ������ �� ��������������, ��� �����. ������� �������.";
			link.l1.go = "Step_E6_24";
        break;
        case "Step_E6_24":
			dialog.text = "��� �, ��� ������ �������: �� ����� �������� �� ������� � ������� �������.\n"+
                          "���� � ������� � ����� � ����, ��� �� � ��������, ����� � ���� ����������.";
			link.l1 = "����� ��������, ������. �� ���������� ���.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_AfterFirstTalkingWithMorris";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "2");
        break;

//**************************************** ������� ������ ����� **************************************
        case "Step_E12_1":
            dialog.text = "� ������ � ���. ���� ������� ����� ������� ������ ������.";
            link.l1 = "�������, ���.";
            link.l1.go = "Step_E12_2";
        break;

        case "Step_E12_2":
            dialog.text = "���� ����� ����� ����. � ��� ������������� ������ ������ �� 1664 ����, �.�. �� ������� ���������� ������������ ����� ���������� ���������.";
            link.l1 = "���, ����� �������� �������� ������������ ������ �...";
            link.l1.go = "Step_E12_3";
        break;

        case "Step_E12_3":
            dialog.text = "�� ������ �� �������� ������������ ������. �� ������ �����, ��� �������� ������������� �������.\n"+
                          "�� ���������� ������������ ������ �������� ���� ���������� ������ ������������ �� ��� ���������� ����� II �������� ��������� � ������������ ��������� ��������� � ��������.\n"+
                          "������ ����, ����� ��������� ���������� ���������, �������� ������������� ���������, � ��������� ��� '�����' - ������ � ������������ ��������� ����� - ������ ��������������� ������� � ������! �������� ������� ���� ����������� ���� ����� ��������� � ��������� ��������.";
            link.l1 = "���, ������� ���� �������� � ����. ��� ��� ������ ������ ��������, ����� �� ���� �����.";
            link.l1.go = "Step_E12_4";
        break;

        case "Step_E12_4":
            dialog.text = "� � ���� ������ �� ��������, ���� ���� ����� ������ �������� ���������� �������� � ���������� ���� ������.\n"+
                          "�� ������ ��������, ��� ���������� ��� � ������ ������ ���������� ����� ���� ����, ����� ������ ������� ����������� ��������!";
            link.l1 = "� ��� �� �������, ���?";
            link.l1.go = "Step_E12_5";
        break;

        case "Step_E12_5":
            dialog.text = "������� �������� ����������� ��������, � ������� � ������� ����������� ��������� � ��������� �����. ��, �������, ���� ��� ����� ����������, �������� ��� �������� � ������.\n"+
                          "������ �� ����� ��������� ���� ���������� �������� ������������ ������� � ������ �����, ������� �� � ����� ������ ������� � ��������.\n"+
                          "� ��� '���������' ��� ����� �������� ������ ����� ���� ����� ���!!!";
            link.l1 = "�������, ���.";
            link.l1.go = "Step_E12_6";
        break;

        case "Step_E12_6":
            dialog.text = "����� ����, �� ����� ���������� ������ ��������� ��������, ��� �������� ��������� ������������ � ���� ����� ��������� ����� ���� ����������� ��������� ���������.\n"+
                          "����� ������, �� ������� �������, ������� ������� ��������.";
            link.l1 = "���, �� ������������� ������ 10 ��������� �� ����� � ���������� �����.";
            link.l1.go = "Step_E12_7";
        break;

        case "Step_E12_7":
            dialog.text = "����� � ���! ���������� ������������� �� ����� ���� �����.\n"+
                          "��� ����� ��������, ��� �������� ����� ������ ��������� � ������������� �������� � �����������. � �� ���������� ��� ���������� '����' �������� ��������������� �������.";
            link.l1 = "���, ��� ����������� ����������� � ��������� ����� '�����', � � ���� �����������, ��� ��� ��� � ����.";
            link.l1.go = "Step_E12_8";
        break;

        case "Step_E12_8":
            dialog.text = "���� � �� ���������� � ����... ����������, � ���� � ��� ���� ������� �����������.";
            link.l1 = "����������� ������, ���.";
            link.l1.go = "Step_E12_9";

        break;
        
        case "Step_E12_9":
            dialog.text = "���� � ���, ��� �������� �������� ������. ������ ������� ��� ��� ������ �� �������.\n"+
                          "��� ������������ � ���� ����� ����������� ��������� �� �������� ������������ ������. �� ����, �� ����� �������������� ������������� ����� �����������, ���� ��������� � �� �������. � ���� �� �������� ���� ����� ����� �����.\n"+
                          "��������� ��� ��������, �� ������ ������ ������ � ���������?";
            link.l1 = "����� ���, ���?";
            link.l1.go = "Step_E12_10";
        break;

         case "Step_E12_10":
            dialog.text = "�� ��� ��, ����� ������. ��� ����� ����� ��, �� �������� �����, � ������������� ������-���� ������� �������� ��������� � ��� ����������. ������� ����.\n"+
                          "�, ���������� �� ���������, ����� ���� � ��� ������� ���� ���������� �����. ����� ������������ ������������ � ��� ������.\n"+
                          "�������, ��� ��� ����������� ������ - ��������� ����� � ��� �� �����.";
            link.l1 = "��� �����. � �������, ���?";
            link.l1.go = "Step_E12_11";
        break;

         case "Step_E12_11":
            dialog.text = "���� �� �� ������?";
            link.l1 = "� ��������� ����� � ���"+ GetSexPhrase("","�") +" �������� ����"+ GetSexPhrase("��","��") +" ���������, � � ���� ���������������� ��������� �� ��� ����� ���������� ������ �� �������.";
            link.l1.go = "Step_E12_12";
        break;
        
         case "Step_E12_12":
            dialog.text = "��� �� � ��� ��� ��������, �� ����������� �� ��������� ���������� �������������. � ������ ��������� ���������� ��������� � ���������� ��� �� ���������������, � �������� ��������� ���������� ������� � ����� �������.";
			link.l1 = "�����������! � ������: � ���� �������� �������� �� �������, ������� �������� ��������� �����.";
            link.l1.go = "Step_E12_13";
        break;
        
        case "Step_E12_13":
            dialog.text = "��... � �� ������ "+ GetSexPhrase("������� �������","������� �������") +", " + GetFullName(pchar) + ".";
            link.l1 = "��������, � �� ����� ��������� �� ��� ������ - ��� ����� � ��� ������� ������ � ������ �������...";
            link.l1.go = "Step_E12_14";
        break;

        case "Step_E12_14":
            dialog.text = "�-�-��, ���� ������... ������������! �������� �� ���������� - ����. ����, � �������� ��� ����� ���������� � ��� ��� ��������� ������������ ��������.\n"+
                          "��� �����, ����� �� ���������� ����������� � ���� ����� � ���������� ������� ����������� � ���������������� ����������� ������ ��������� ��� �������� ���� � �������.";
            link.l1 = "����� ���������, ���.";
            link.l1.go = "exit";
            pchar.questTemp.State = "ColonelLinch_ArrestModiford";
            AddQuestRecord("Eng_Line_12_ColonelLinch", "2");
			AddQuestUserData("Eng_Line_12_ColonelLinch", "sSex", GetSexPhrase("","�"));
            LAi_SetPlayerType(pchar);
            LAi_SetStayType(npchar);
            NextDiag.TempNode = "YouMustGo";
        break;

        case "YouMustGo":
            dialog.text = "��� ������� ��� ����� ������� ���������� ���������. ����� ��� ��������� ������������ ������.";
            link.l1 = "������, ���.";
            link.l1.go = "exit";
            NextDiag.TempNode = "YouMustGo";
        break;
    }
}
