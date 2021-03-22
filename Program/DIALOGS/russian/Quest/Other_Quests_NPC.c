void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(NPChar.id == "Andre_Abel_Quest_Officer_1") // ������ � ���������� �������. ������������� ������ "�����"
			{
				dialog.text = LinkRandPhrase("������ ������� � ���������� �������-������������.", "�� ���� ��������� ����!", "����, � �������-����������� ����� ���� �������!");
				link.l1 = "�� ���� �, ����...";
				link.l1.go = "exit";
			}
			
			if(NPChar.id == "Martin_Bleker")	// ������ ������
			{
				dialog.text = GetSexPhrase("��� ������, ����� �� ���� '�������� �������'...","�-�... ��� ��� �� ��������...") + "�� ��� �, ����� ���������� � ���� ������.";
				//	link.l1 = "�� ��� �� � �����!";
				//	link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_1";
				link.l2 = "������ �� � ��� ���������� ����������������... �� �������������� �������, �� � ����� ���������.";
				link.l2.go = "Andre_Abel_Quest_In_Prison_1";
			}
			break;
			
		// ������ ������. ����� "������������� ������ '�����'" -->
		case "Andre_Abel_Quest_In_Prison_Wrong_Way_1":
			dialog.text = "�������� �� ���... ��, ��� ���� �����... ��� ������ ���� ���� ������������ ���� ����� ���������� �������...";
			link.l1 = "���� ����� ��������... ��� �������...";
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_2";
			link.l2 = "��... ���� ����� ���, ��� �� ��������, �� ����� ������ ���������� ������...";
			link.l2.go = "Andre_Abel_Quest_In_Prison_2";
			break;
			
		case "Andre_Abel_Quest_In_Prison_Wrong_Way_2":
			dialog.text = "������� �� ���...";
			link.l1 = "� ����.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_3";
			break;
			
		case "Andre_Abel_Quest_In_Prison_Wrong_Way_3":
			DialogExit();
			SetLaunchFrameFormParam("������ ��� ���...", "", 5, 3);
			LaunchFrameForm();
			break;
		
		case "Andre_Abel_Quest_In_Prison_1":
			dialog.text = "�����, ���������... � ������ �������� ����������, �� ����, ������, � ��� '���������' �����... ��� ��� ��� ��������, ��� ���� ������ �������.";
			link.l1 = "��� ������!.. ������� ���� �� ���� ��� ���������. ������ �� ������� ������� �� �����������...";
			link.l1.go = "Andre_Abel_Quest_In_Prison_2";
			break;
			
		case "Andre_Abel_Quest_In_Prison_2":
			dialog.text = "� ���� ����� ����������? ��� ������ ���������� ������ - ������ ������ ����� �������.";
			link.l1 = "��! � �� ���, ��������, �� �����������? ��� �� ���� � �������� �������.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_3";
			break;
			
		case "Andre_Abel_Quest_In_Prison_3":
			dialog.text = "�� ����� ��� '����'?! ������� ��� ����� ���������, ��� � �������, � ������ ����������. ������ � �������� ����� ������ �� ��������� - ��� � ��� ���������. � �� "+ GetSexPhrase("������ �������","����� ������") +", � ������ ��������, ���� �� ������ ���������... �� � ������ ���� ��� ��� �����. ��� ��� ������� ��������� � �� �������. ��-��...";
			link.l1 = "�� ��, � ������������ ��� ���������� �������. � ������� �� ��������?"; 
			link.l1.go = "Andre_Abel_Quest_In_Prison_4";
			break;
			
		case "Andre_Abel_Quest_In_Prison_4":
			dialog.text = "������? � ����� � ������ ����� ������ ���� �������, ����� ������ ����. ������ ����� ���� �� ��������� ������������, �� ��� ������ �������... ��� ��� ����� � ���� �� � �������.";
			link.l1 = "��, ��� ���, �� �����? ��� ���� �� ���������!.. ������, ����� ���� ���?";
			link.l1.go = "Andre_Abel_Quest_In_Prison_5";
			break;
			
		case "Andre_Abel_Quest_In_Prison_5":
			dialog.text = "����? ��� �����?.. ����� ���� ������ ������... ������ �� ������ �������, ���� ����� �� ��������, � �� �� � ���� ���-�� ��� ���������...\n��, ����� ������... ������� ����� �������, ������ - ������ ��� �������?";
			link.l1 = "��-��, �� �������� �������, �� �� ���� ����, � ��� �� ����� � �������... �� ������ ������, ���� ����� " + GetFullName(pchar) + "... ��, � �����.";
			link.l1.go = "Andre_Abel_Quest_In_Prison_6";
			break;
			
		case "Andre_Abel_Quest_In_Prison_6":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_Quest_In_Prison_7";
			LAi_SetCitizenType(NPChar);
			PChar.items.blade7 = 1;
			PChar.equip.blade = "blade7";
			NPChar.items.blade7 = 1;
			NPChar.equip.blade = "blade7";
			SetFunctionLocationCondition("Andre_Abel_Quest_Liberty", "Villemstad_ExitTown", false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Martin_Bleker_Is_Dead", "Martin_Bleker", false);
			ChangeCharacterAddressGroup(NPChar, "Villemstad_prison", "goto", "goto12");
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto23", "Andre_Abel_Quest_Runaway_From_Prison");
			break;
			
		case "Andre_Abel_Quest_In_Prison_7":
			dialog.text = RandPhraseSimple("��� �� ��������������� �����.", "������, ���� ������ ������� �� �������.");
			link.l1 = "�� �������. ��� �� �� ����� �������� ����������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_Quest_In_Prison_7";
			break;
			
		case "Andre_Abel_Quest_In_Liberty_1":
			dialog.text = "������ ���� � ���� ����� �������! ������� ����, �������. ��� ���� ��� ���� ��� �������� ����������.";
			link.l1 = "��� ���� �������. �� ����, ��� �� � �������"+ GetSexPhrase("��","���") +", ���� �� �� ���� ������� �� ������.";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_2";
			chrDisableReloadToLocation = false;
			break;
			
		case "Andre_Abel_Quest_In_Liberty_2":
			dialog.text = "�� ���? �����������?.. ������, ����� ����.";
			link.l1 = "������...";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			link.l2 = "������. � �� - ����� �� ������, �� ������ ��������� �� ��� � ������� ������������?";
			link.l2.go = "Andre_Abel_Quest_In_Liberty_4";
			break;
			
		case "Andre_Abel_Quest_In_Liberty_3":
			DialogExit();
			NPChar.LifeDay = 0;
			LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			break;
			
		case "Andre_Abel_Quest_In_Liberty_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 24 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 29)
			{
				dialog.text = "��������? ��, ������ �� � ���, ���� � ���� ��������.";
				link.l1 = "�� ���� ���� �� ��������. � ������� �� �����.";
				link.l1.go = "Andre_Abel_Quest_In_Liberty_5";
			}
			else
			{
				dialog.text = "���, �������... �� ��������, �� � ������� ��������� ������ ���������. ������ - ��� �� ��� ����.";
				link.l1 = "�����, ��� ��� ���. ����� ����.";
				link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			}
			break;
			
		case "Andre_Abel_Quest_In_Liberty_5":
			dialog.text = "����� � ��������!";
			link.l1 = "��� � �������. ����� ���������� � �������!";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_6";
			break;
			
		case "Andre_Abel_Quest_In_Liberty_6":
			dialog.text = "������� ����, �������. ���� ���������.";
			link.l1 = "� ���� � �� ����������.";
			link.l1.go = "Andre_Abel_Quest_In_Liberty_7";
			break;
			
		case "Andre_Abel_Quest_In_Liberty_7":
			DialogExit();
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
			LAi_SetStayType(NPChar);
			NPChar.Greeting = "Gr_Officer";
			NPChar.Money   = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;
			AddPassenger(PChar, NPChar, false);
			NPChar.OfficerWantToGo.DontGo = true;
			NPChar.HalfImmortal = true;  // ��������
			NPChar.loyality = MAX_LOYALITY;
			AddQuestRecord("Andre_Abel_Quest", "19");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Martin", PChar.location, false);
			break;
        	// <-- ������ ������. ����� "������������� ������ '�����'"
        
		//--> ������������, �����
		case "TakeShoreCap":
    		dialog.text = "�� �� �������! �� ������"+ GetSexPhrase("","�") +"?";
    		link.l1 = "�� ������"+ GetSexPhrase("","�") +" ����?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "��-��! ����� ����� ���! �� ���� �� ���� ����"+ GetSexPhrase("��","���") +"?";
			link.l1 = "�� ��... � � � �����, ������ �� �������� ������ �������, �� ��� ��� �����... �������!!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "��, ������"+ GetSexPhrase("��","��") +", ��� �������. � � �� ��������, � ������ ������! � ���� ��� �� �������"+ GetSexPhrase("","�") +", ���� ��� ����� �� ���� �� ����������.";
			link.l1 = "��� ������ ��? ������ ������� � �����, ���� ���� ������ �� ��� - � ����� ������ �� ������.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "����������. ���� ������ ������� � ������� ����������� ��������. ����� �� ���� ������ �������-����������, � ��� �� ����������� �� ��������. �� � � �� ����������, ����� �� �� ��� �� �����"+ GetSexPhrase("","�") +".";
			link.l1 = "��������, ������ ��������������!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //��� ��������� ������ ��� �������� � ������������
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = "" + GetFullName(pchar) + ", ������ ������ �� ����������! ���������� ������ ������ � �������� �� ����!";
			link.l1 = "��� ��� ������, ������? �� ����� ���������?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "�� �������������� �������, �������! ���� ������� ������� ��������. � �� �����, ��� �� �������, � �� ����������� ������� " + NationNameGenitive(sti(npchar.nation)) + ", �� ������ ��������� �� ���-���!";
			link.l1 = "�� ��� ���... �� ��� ������ ��� ������, �� ��� ��? ���������, ���!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<--������������ �����
		
		//--> ������������, ����� � ����
		case "Rat_bandos":
			dialog.text = "��! ��� �� ��� �����"+ GetSexPhrase("","�") +"? �����, ���� ������!";
    		link.l1 = "���-�� �� �� ����� �������, ��������. �� ����� �� �������� ��� ����� �������, �?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "��� ����� �������� ��������! ���� ��� ���, ��� �� �����"+ GetSexPhrase("","�") +" ������ - ��������!";
			link.l1 = "������� ���, ��� �� �����. ������ �� ������ ��� � ���������...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "�-���! �������! ����! ������, �� ���, �� ������!";
			link.l1 = "�� �� ���!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "��! �� �������� ����!";
    		link.l1 = "��� ������� �������? �������, ��������� �����, ��� ���������� �� ������ ��������!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "���, ���, � ��� �����! �� ��������� � ���� � ������, ������, �� ���� �������.";
    		link.l1 = "����� �������? � ����� ��� ��� �������, � ��� ����. �� ��� ���, �������, ���� �����...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "� �� ���, �������! �� �������, ��� �������������� � ���������� ��������, �� ������� ����, � �� ������ �������� �� ������... �� ���! �� �������� ����!";
    		link.l1 = "�����, ������ �� �� �����. ���� ���� � �� ��������. � ������, �������� ���� � ���� ��������. ����, ����� � ���� �� - �� ������ ����, ����-�����.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//���������� � �������
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//�������� �������
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		//<--������������ ����� � ����
		
		//--> ������������, ������ ����
		case "Slave_woman":
			dialog.text = "��������! ��������! �� �������!";
    		link.l1 = "��� ���? � ��, ��� ���� ���� �� ������� � �����! ��� ������� �������� �������� - ��������� �� �����!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
		//<--������������ ������ ����
			
		//���, ������ ������
		case "Carlos":
            dialog.text = "��������, ��� �� �� �� ���"+ GetSexPhrase("","�") +" � ������, � �����.";
            link.l1 = "�������� ��� � ������ ������� ����� �������... ����� ������ ������� ������. ����� �� ����"+ GetSexPhrase("","�") +", ��� � ����� ��������� ������� ������.";
            link.l1.go = "Carlos_7";
        break;
        
       	case "Carlos_3":
			Dialog.Text = "���, �� ������ �������! ������, �� ������� �� ����, �����������, ����� �� ������� ������� ������� ������ ������������! ���������� �� ���������� �������� ����� ���, � ��������� ���� ������, ����� �� ������� ���� ���� ��������� ������ �������\n�������, ���� ��������� ���� �� �������, � ���� ����� � ������� ���� �...";
			link.l1 = "��������, ���������. ��������� ��� ��� ������������� ����� ����. � ���� �� ����� ����� ���, � ���� �� ����� ��� ����, �� ���� ������ - ����� � �������� ���������� ������� ������ ���� �����, � ����� �� ���� �� �� �������.";
			link.l1.go = "Carlos_4";
			pchar.questTemp.Headhunter = "hunt_carlos_fight";
        break;
		
		case "Carlos_4":
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", true);//�������� �� �������
			locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = true; //��������� �������
			AddQuestRecord("Headhunt", "2_1");
			pchar.quest.HeadhunterTimer.win_condition.l1 = "Timer";
			pchar.quest.HeadhunterTimer.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.HeadhunterTimer.function = "CarlosDuel";
			SetFunctionTimerCondition("CarlosDuelOver", 0, 0, 2, false);
			NextDiag.CurrentNode = "Carlos_5";
			DialogExit();
		break;

		case "Carlos_5":
			Dialog.Text = "��, ���� ���� ���?";
			link.l1 = "������ �����"+ GetSexPhrase("","�") +" ��������� ���� � ����� �������.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "Carlos_5";
        break;

		case "talk_off_town_Carlos":
			Dialog.Text = "�� ��� � ���������, "+ GetSexPhrase("��������� �����","��������� �����") +"! ������ �� ���������, ��� �����"+ GetSexPhrase("��","���") +" �� ����!";
			link.l1 = "� �����, �� ������ � ����� ��������, ���? ��� ����� � ��� �� ����� ������� � ���. � ����!";
			link.l1.go = "Carlos_6";
			chrDisableReloadToLocation = true;
		break;

		case "Carlos_6":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "CarlosDie");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "Carlos_7":
			dialog.text = "�������-�� "+ GetSexPhrase("������","������") +"... ��� �� �������� ���� ���. �� ���� �������������, � ��� ��������������, ����"+ GetSexPhrase("�","���") +"?";
			link.l1 = "� ������ � ������ �������, ������� ������ ���������, ��� � �������"+ GetSexPhrase("��","���") +" �������� �����. � ������ ����� ��� ���������� ���������, ������ � ����� � ����� ������, ������?";
			link.l1.go = "Carlos_8";
		break;
    
		case "Carlos_8":
			dialog.text = "�� "+ GetSexPhrase("������ �����","������ �����") +", ��� � �������... � ������ ������ � ��� ��� ����� ������ � ���� ������ � �� ������ ������ � � ��� ����� ����� ��� �������� �������� ��������. ��� ���� ����� � ��������� ������, ���� � �� �������� ���� ����. �� ���� ������� ������� �����. ";
			link.l1 = "��� ������ �� ����������� ������. ����, ��� ��������� � ��� ��������... ����� ���� ����.";
			link.l1.go = "Carlos_3";
			int n = FindLocation(pchar.questTemp.Headhunter.City + "_Brothel");
			locations[n].reload.l2.disable = true;
		break;
		//���, ������ ������
		
		//���, �������� ����
		case "Houm":
            dialog.text = "����, ������� � ����. �� ������ �� ���� ������� ����.";
        	link.l1 = "���������� ���� �����, �� �� �������� � ����, ���� ��� �� �������.";
            link.l1.go = "Houm_1";
        break;
		
		case "Houm_1":
            dialog.text = "����������� ���� �������� ��������� ����? �����, �� ����� � ��� �� �������� ���, ��� ��� ��� ������ ��������� � �����.";
        	link.l1 = "����� ���� �� �������� ��� �����, ������ '���'? ";
            link.l1.go = "Houm_2";
        break;
		
		case "Houm_2":
            dialog.text = "������� ��������� ����... ���� ���� ��������� ����������� ������ ���? ��� ����� ������ ������ ������ ����, ��������� �� ����\n� ����� ������ ����, ��� �� �������. � ���� - ������ ������ ���������� ���, ����� �����, �������� �����. ������� ���, ���� ��� �� ����������� �������.";
        	link.l1 = "�������� �����������, ������ ��������. ����� ������� ��� ���������� � ��������� �������.";
            link.l1.go = "Houm_3";
        break;
		
		case "Houm_3":
            dialog.text = "������ ��� ���������, �� ���� "+ GetSexPhrase("������, ����������� �������","������, ����������� ��������") +".";
        	link.l1 = "� �� ������� �� ������, ������ ���. �� ����������� �������, ������� �� ������, ��� ��� ����. � � ����, ����� �� ������� �� ��� ������.";
            link.l1.go = "Houm_4";
        break;
		
		case "Houm_4":
            dialog.text = "��, ��� �������. ����� ��� �� ����, �� ����������� ������ ����������� ���� ���������, �� "+ GetSexPhrase("����","�������") +", ������"+ GetSexPhrase("��","��") +" ��������� �� �������? ��������\n��� ��������� ���� �����. �� ����� ��������� ����� ����� ������ � ��� ����� ����� ���"+ GetSexPhrase("��","����") +" � ����. ��������, ��� ��������, � ���� ��� ����, � ��� ����� ���� ������, � ��������� ���"+ GetSexPhrase("��","����") +" ��������� ���� ����� �"+ GetSexPhrase("��","�") +" ������.";
        	link.l1 = "����������� �� ���� �������, �����, � �������� ������� ������ � ���!";
            link.l1.go = "Houm_5";
			AddQuestRecord("Headhunt", "6");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","�"));
			pchar.quest.Headhunter_HoumAttack.win_condition.l1 = "location";
            pchar.quest.Headhunter_HoumAttack.win_condition.l1.location = pchar.questTemp.Headhunter.Island;//���������� � �������
            pchar.quest.Headhunter_HoumAttack.function = "Headhunter_CreateHoumShips";//�������� ��������
        break;
		
		case "Houm_5":
			if (findsubstr(PChar.location, "_tavern" , 0) != -1)
			{
				DialogExit();
				NextDiag.CurrentNode = "Houm_6";
			}
			else
			{
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			}
			DialogExit();
        break;
		
		case "Houm_6":
			Dialog.Text = "��, ���� ���� ���?";
			link.l1 = "������ �����"+ GetSexPhrase("","�") +" ��������� ���� � ����� �������.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "Houm_6";
        break;
		
		case "RatOfficer":
			int iGoods1 = 400 - GetSquadronGoods(Pchar, GOOD_EBONY);
			int iGoods2 = 500 - GetSquadronGoods(Pchar, GOOD_MAHOGANY);
			int iGoods3 = 670 - GetSquadronGoods(Pchar, GOOD_SANDAL);
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if(pchar.questTemp.Headhunter == "Rat_officer" && GetCompanionQuantity(pchar) == 1 && 3-sti(RealShips[sti(pchar.ship.type)].Class) <= 0)
				{
				
					if(iGoods1 < 1 || iGoods2 < 1 || iGoods3 < 1)
					{
						dialog.text = "��, ���� ����? ����������, � �� � ���������� �������.";
						link.l1 = "� ������ �� �����... ���� ������, � �� � ���. ��������� ��������? � ������!";
						link.l1.go = "RatOfficer_1";
					}
					else
					{
						dialog.text = "��, ���� ����? ����������, � �� � ���������� �������.";
						link.l1 = "�� � � �� �������"+ GetSexPhrase("��","���") +" � ����� ���������. ��������� ���������.";
						link.l1.go = "exit";
						NextDiag.TempNode = "RatOfficer";
					}
					break;
				}
			}
			dialog.text = "���� ���� ����? ����������, � �� � ���������� �������.";
			link.l1 = "�� � � �� �������"+ GetSexPhrase("��","���") +" � ����� ���������. ��������� ���������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer";
		break;
		
		case "RatOfficer_1":
			dialog.text = "�-�, �� ����� ������ ����. ������������.";
			link.l1 = "���! �� ��������� �����!";
			link.l1.go = "RatOfficer_1_sit";
		break;
		
		case "RatOfficer_1_sit":
			NextDiag.CurrentNode = "RatOfficer_2";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.5);
			DoQuestReloadToLocation("Tortuga_tavern", "sit", "sit1", "");
			LAi_SetSitType(Pchar);
			DialogExit();
		break;
		
		case "RatOfficer_2":
			dialog.text = "�������, "+ GetSexPhrase("������","������") +"! ������, �� �� ������, ��� �������! ������ ���� �������?";
			link.l1 = "����, ����� ���! ���? �, � ��������� ������� ��, � ���������. �������, ����������.";
			link.l1.go = "RatOfficer_3";
		break;
		
		case "RatOfficer_3":
			dialog.text = "��������? ��, ��� ���� �������. �� ��� ���� �������� - �����"+ GetSexPhrase("","�") +" ����� � �����?";
			link.l1 = "��, �������� - ���� �������, ������ ������, ���������, ������ ����� �� ����... ���� �� �������� ��������, �� ��, ��� �� ��������� �������. � ��� ������, ���� �� �������, ������� ������ ���� ������ ���������...��!";
			link.l1.go = "RatOfficer_4";
		break;
		
		case "RatOfficer_4":
			dialog.text = "�������, ��������, ���� ������?";
			link.l1 = "�� �� �� ������. ������ ������ ������. �������"+ GetSexPhrase("","�") +" � ��� - ������� ������, ����� ����� ���������, ��, ����� ���������, � ������� ������... ��� ��� �� - ����� ��� �����! �������� �� ������ ������ � �������� ����.";
			link.l1.go = "RatOfficer_5";
		break;
		
		case "RatOfficer_5":
			dialog.text = "��, � ���� ����� �����������. � ��� ��������� ���������...��! ��������! �� ����� ��� ��������! �� ��������� �������, ����� ��� �� � �����, ��� ��������...";
			link.l1 = "��, �� ����, ���� ������! ��� ��-�� ���, ���������������. ��, � ��� ��� ����"+ GetSexPhrase("��","�") +" �� ������� �� ������ ���������? � ���� ��� �� ���� � ����� ������ ����� ���� - ������ ����� � ��������� ��������� ������ �������� - �������� ����������� � ��� �� �������� ���������, �� � ������ ���� ������� ���������... ������, � �� ����� �� � ��� ����������� ���� �������? �����...";
			link.l1.go = "RatOfficer_6";
		break;
		
		case "RatOfficer_6":
			dialog.text = "���, �� ������...��! ������ � ������ ������� ����������.";
			link.l1 = "��, ����. ��, ����� ������� ����������, ����� �� ������� ��� � ����... �� ����� ������� ���� - � ����� ��� ����� ����� ��������, ��� ���� � ������ �����-�� ����� � �� ��������... ��� ���, �������� �������!";
			link.l1.go = "RatOfficer_7";
		break;
		
		case "RatOfficer_7":
			dialog.text = "��������... �������� - ���... ��, �����. ������� ������ ����, ��-�� ������� ������ ��������� ������. �� ����� ������ � ����� ������� �� ����� � ������ ���� �� ����. � ����, �������?";
			link.l1 = "�� ��� ��� ����, �������! ��� ������� ������ - � ��� ���� � ���������� �����. ������� � ������� �� ��� �����, � ������� ���������� ��� ������ � ��� ������... ��, ���� ����, ����...";
			link.l1.go = "RatOfficer_8";
		break;
		
		case "RatOfficer_8":
			dialog.text = "�� �� ��������� �� ���! ��� � ������ ���, ��� ��? ����� ����� ������, � �� ��� ��� ���� �� ���� �������� ������������.";
			link.l1 = "��, ����� ��� �� �����, � � ���� ���������... ��� �����-�-��� ���� �� ��������� ��-�-���, ��� ������-�-�� � ������ �������... ������, �������...";
			link.l1.go = "RatOfficer_9";
			pchar.quest.Headhunter_Ratgulf.win_condition.l1 = "location";
            pchar.quest.Headhunter_Ratgulf.win_condition.l1.location = "Shore_ship2";//���������� � �������
            pchar.quest.Headhunter_Ratgulf.function = "Headhunter_Ratgulf";
			SetFunctionTimerCondition("Headhunter_RatgulfOver", 0, 0, 15, false);//������
		break;
		
		case "RatOfficer_9":
			pchar.quest.Headhunter_RatOfficerOver.over = "yes";
			LAI_SetPlayerType(pchar); 
			LAI_SetSitType(npchar);
            DoQuestReloadToLocation("Tortuga_tavern", "goto", "goto2", "");
			AddQuestRecord("Headhunt", "18"); 
			pchar.questTemp.Headhunter = "Rat_gulf";
			NextDiag.CurrentNode = "RatOfficer_10";
			npchar.lifeDay = 0;
			DialogExit();
		break;
		
		case "RatOfficer_10":
			dialog.text = "��-����-����-��� �������, �� ������ ��������... ��!";
			link.l1 = "�������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer_10";
		break;
		
		//���, ���-�����
		case "Rat_talk":
			dialog.text = "����! ��� �� - �� ��������?";
			link.l1 = "���, �����. �� ���� ��� �� �������. ������ ������� ������ ���� ���� �������� ����� � ������� ������. ���� ���������� ���������� �����, � ���� �����.";
			link.l1.go = "Rat_talk_1";
		break;
		
		case "Rat_talk_1":
			dialog.text = "��� ������ � �� ������, ���� ������� ��� ��������. �� ��� �������, ��� ������ ��������� � ������! ��� ������� �������� �� ����!";
			link.l1 = "������ �� ������ ������������ ���� ����� ������ � ���. � ���, ��������!";
			link.l1.go = "Rat_talk_exit";
		break;
		
		case "Rat_talk_exit":
 		    pchar.questTemp.Headhunter = "hunt_rat_yes1"; 
            AddQuestRecord("Headhunt", "23");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","�"));
            pchar.quest.Headhunter_DieHard.over = "yes";
			pchar.quest.Headhunter_AfterBattle.over = "yes";
            Island_SetReloadEnableGlobal("Beliz", true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "RatHunters":
			//dialog.text = "...";
			link.l1 = "�?! ���? ��� �� ����� �������, ���� ������? ��� ��� ���� �������?";
			link.l1.go = "RatHunters_1";
		break;
		
		case "RatHunters_1":
			dialog.text = "��� ������� �������� ���� ������...";
			link.l1 = "���? �-���, ������!!";
			link.l1.go = "RatHunters_2";
		break;
		
		case "RatHunters_2":
			LAi_SetFightMode(pchar, true);
			LAi_LockFightMode(pchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "RatHunters_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Halen":
			dialog.text = "�� ���� ��������, "+ GetSexPhrase("��������","��������") +"! � ���� ���� ����� �����, ��� ��� �������������?";
			link.l1 = "�� - ������ ��� �����?";
			link.l1.go = "Halen_1";
		break;
		
		case "Halen_1":
			dialog.text = "��, ��� ��� ���, �� �� ��� � �� ������� ��� ����? ����������� ���������, ��� ��� ������, ��� ������������ �����. �� ����� ���������� ��� �������� - � ���� ��� �� ��������� ������� ������� ���� ����� �� �������� � ������.";
			link.l1 = "�� ��... � ������ - ���������, ����������� �������� ����. �� ������� ���������� �� �� ������. � ��� �� ������� ����� - ������ ��������. ��� �� ��������, ��� ������������ ������ �� ������������� �� ���� �����, ���� ���� �� ��������� ������������������ �����?";
			link.l1.go = "Halen_2";
			link.l2 = "��... ������ �����"+ GetSexPhrase("","�") +" ������������� �� ���������� ����������� ��������.";
			link.l2.go = "Halen_3";
		break;
		
		case "Halen_2":
			dialog.text = "����! �������� �������� � ��� �� �� ���� �� ������! �� ������� �������� � ����, ���� ������ ���� � ������. ��������� ����, �������, ��� �� ������� � ��� ������� ����� ���� ������ � ���� �����! ������ ���� �����, "+ GetSexPhrase("������","�����") +", ���� ������, � ������ ����� �� �������! � ���� �������� �������������� ����������. ����� � ������ ������ ����, ��� ������!";
			link.l1 = "�������, ��������!";
			link.l1.go = "Halen_fight";
		break;
		
		case "Halen_fight":
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "HOLLAND_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			
		break;
		
		case "Halen_3":
			dialog.text = "������������"+ GetSexPhrase("","�") +" �����������? � ������ � �������� � ������� � �������� �������� �����, �����������!";
			link.l1 = "���...";
			link.l1.go = "exit_halen";
		break;
		
		case "Halen_4":
			dialog.text = "����� ��? ����� ���������� � ����������� ��� "+ GetSexPhrase("� �������, ��� ���� � �������� � ������ ��������","� �������, ���������� ������ ��������") +". ��� ���� ����� �����.";
			link.l1 = "���...";
			link.l1.go = "exit_halen";
			link.l2 = "�������, � ����� ���� ����������, �������� ����������� ������!";
			link.l2.go = "Halen_2";
			NextDiag.CurrentNode = "Halen_4";
		break;
		
		case "exit_halen":
			LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Headhunter_HalenOut", -1);
            LAi_Actor2WaitDialog(npchar, pchar);
			NextDiag.CurrentNode = "Halen_4";
            DialogExit();
		break;
		
		case "Miko":
			dialog.text = "��� ���� �� ���� �����?";
			link.l1 = "���-���... �� � ���� ���� ����������?";
			link.l1.go = "Miko_1";
		break;
		
		case "Miko_1":
			dialog.text = "��, ��� �. ��� ������?";
			link.l1 = "��� ����� ���������� � ����� � ��� ��������. ��� ����� ������� � ��� ����������.";
			link.l1.go = "Miko_2";
		break;
		
		case "Miko_2":
			dialog.text = "���... ����. ��� � ���������. ��� �� � ���� "+ GetSexPhrase("��� ������","�� �����") +", �����"+ GetSexPhrase("���","��") +" �� �����������... "+ GetSexPhrase("��� ������","���� ������") +"... �� ��� ��, ��� ����������� ��������� ��� ������. �� �����, ��� �� ��� ������ ������ ������.";
			link.l1 = "��, ��� �. ������, ��� �������, � ������ ����.";
			link.l1.go = "Miko_3";
		break;
		
		case "Miko_3":
			dialog.text = "�� ��������� ���, "+ GetSexPhrase("��������","������") +"? ��������. �� ����� ���"+ GetSexPhrase("��","��") +", � �� ���� �������� �������� ���� � ������\n��� �������� ����� �������, �� �� ������ ������ ��������. ������� �����, ��� �� �������. �� ���� ������� �� ����� ��� - ������ ��� �� ���"+ GetSexPhrase("��","��") +" ����, ��-��-��!!";
			link.l1 = "��, ��������, �� ��� ������ ���� ������...";
			link.l1.go = "Miko_fight";
			pchar.questTemp.Headhunter = "miko_mustdie";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1 = "NPC_Death";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1.character = "Miko";
			pchar.quest.Headhunter_Miko_mustdie.function = "Miko_die";
		break;
		
		case "Miko_fight":
			chrDisableReloadToLocation = true;
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "Pearlgroup_2");
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Headhunt", "34");
		break;
		
		case "JaHunters":
			dialog.text = "� ��� � "+ GetSexPhrase("��� ����","���� �������") +"!";
			link.l1 = "�������... �����!";
			link.l1.go = "JaHunters_1";
		break;
		
		case "JaHunters_1":
			dialog.text = "��� ������� ������ �������� ���� ������...";
			link.l1 = "�-�-��!!";
			link.l1.go = "JaHunters_2";
		break;
		
		case "JaHunters_2":
			LAi_SetImmortal(npchar, false);
			pchar.quest.Headhunter_Find_Ja.win_condition.l1 = "location";
			pchar.quest.Headhunter_Find_Ja.win_condition.l1.location = "SantaCatalina";
			pchar.quest.Headhunter_Find_Ja.function = "Create_Ja";
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FindJa");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Ja_talk":
			dialog.text = "�� ��� � �����������, �������... �� ���, ����� ������� ���� �����, ���, �����, ���������?";
			link.l1 = "���"+ GetSexPhrase("","�") +" ���� ������. � �� ��� ������� �� �������... �������� ���� ������, �������, � ���� ��������� � ����� ��� � ��������.";
			link.l1.go = "Ja_talk_1";
			link.l2 = "����� ����������, ��� �����������. ������ �� ��� �� �������... ��� ������ � ��� ��������, ���������?";
			link.l2.go = "Ja_talk_3";
		break;
		
		case "Ja_talk_1":
			dialog.text = "�� ��� ��... ����� ���������!";
			link.l1 = "����! �������!";
			link.l1.go = "Ja_talk_exit";
		break;
		
		case "Ja_talk_exit":
 		    pchar.questTemp.Headhunter = "hunt_ja_yes"; 
            bQuestDisableMapEnter = false;
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Ja_talk_3":
			dialog.text = "������ ����� �� ��������� �� ����? ����� ����"+ GetSexPhrase("","�") +" ���� ���� �����?";
			link.l1 = "����! ��-�����, ��� �� ��������� �� ����! ��� �������� ������ ������� - �� ����� ������ ���� ����� ��������� ����� ����� � �� �������. ��� � �������� �� ��� ����������...";
			link.l1.go = "Ja_talk_4";
		break;
		
		case "Ja_talk_4":
			dialog.text = "��� ������! ������� ��-���� ��������, ��� �� ��������... ���� ���� ���� ����������.";
			link.l1 = "������ ��� ������, ���. ���� ����������� ��� �������� - �����, �� ����� ��, ��� �����. ������ ��� ������� ���� ������.";
			link.l1.go = "Ja_talk_5";
		break;
		
		case "Ja_talk_5":
			dialog.text = "�������... ��������, � �������� ���� ������. �� "+ GetSexPhrase("��������� � �������� ������","��������� � �������� �������") +", � �... � �������� ���� ����. � ���� ��� ������ �����, � ��� ��� ������� - �� �������"+ GetSexPhrase("","�") +" �������. ���� ���� ��� �������� ���� ������ �����, ����� ��� ����� ����\n�����, ����� ��������� ����? � ��������� ������� ������ �� ��� � ����� �������� � �����, ��� ����� �������.";
			link.l1 = "���, ���. � ���� �� ����. ������� - �� ��� ������, � ������ - �������� ������ � �����? ���� ��������� ���� ��������������!";
			link.l1.go = "Ja_talk_1";
			link.l2 = "��! ��� ��� ���������! � �� ������, ��� - � ������"+ GetSexPhrase("��","��") +". ������ �������, ��� ��, ��� �������� ����. �� ������ - �������� ����� ������ - ����� �� ���� ��������!";
			link.l2.go = "Ja_talk_6";
		break;
		
		case "Ja_talk_6":
			dialog.text = "�������������� �������, �������. ��� ���� ������ ����� ���������� ����� �� ���������� - ���� ��������. ������ �� ��� �� �����������. � ���, ��� �� ������������.";
			link.l1 = "����� ���������� � �������, ������!";
			link.l1.go = "Ja_hired";
			pchar.quest.Headhunter_AfterBattleJa.over = "yes";
		break;
		
		case "Ja_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Jafar")].lifeDay = 0;
			pchar.questTemp.Headhunter = "end_quest_full";
			AddQuestRecord("Headhunt", "38");
			CloseQuestHeader("Headhunt");
			sld = GetCharacter(NPC_GenerateCharacter("Jafarry", "QuestCaptain", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade14", "pistol6", 100);
			sld.name = "���";
			sld.lastname = "�������";
			sld.greeting = "Gr_Officer";
			sld.rank = 30;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			sld.HoldEquip = true;
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 70, 75, 75, 75, 80, 70, 70, 70, 70);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "Medic");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.HalfImmortal = true;  // ��������
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			AddDialogExitQuestFunction("Pascal_Escape");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
