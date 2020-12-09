// boal 27.03.2004 ��� ������� ������

void ProcessDialogEvent()
{
	ref NPChar, d, sld;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Good_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "RP_talkWithHusbandIsOver", 0);
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			if (CheckAttribute(pchar, "quest.wasInBeedroom"))
			{
	            if (CheckAttribute(NPChar, "quest.NiceMeet"))
				{
					dialog.text = "��, ������, �� ���������� ���� ������� ����� - �������� � ������� ��� ������ ������� ����...";
					link.l1 = "������, ��������, �������� ������...";
					link.l1.go = "Good_exit";
				}
				else
				{
					dialog.text = "������ ����� �� �������� � ���� ����? ���������, ��������!";
					link.l1 = "�� ������...";
					link.l1.go = "Romantic_Battle_in_Bedroom_2";
				}
				DeleteAttribute(pchar, "quest.wasInBeedroom");
			}
			else
			{				
				dialog.text = "����������� ���, ����������! ���� � ������, ��� �� � ���� ������ ����� ������ ��� � ���� ����?";
				link.l1 = "��� ��� - " + PChar.Name + " " + PChar.LastName +
						", � �������.";
				link.l1.go = "Next_1";
				link.l2 = "����� ���� ��������. � ������ �������.";
				link.l2.go = "Good_exit";
			}
		break;
		
        case "Next_1":
            NextDiag.TempNode = "Usual_1";
			dialog.text = "������� ��� ���-���� ������? ���� �� ������ ����, ������, ������ - ������. �� ��� �, � ���� ����� �� ���� �������������� ��� �������� ����� ������� ��������� ���������. � � - �� ����������.";
			link.l1 = "�� ���� ��������?!";
			link.l1.go = "Next_2";
			link.l2 = "����� ���� ��������... ����!";
			link.l2.go = "Good_exit";
		break;
		
		case "Next_2":
		    NextDiag.TempNode = "Usual_1";
			dialog.text = "� ��� � ���� �������������? ��� ����� ������� � �������� ������ �����������. �� ����� ������� �������� � ����� ������������, ���� � ��� �����.";
			link.l1 = "�������. ������� �� �����. ���������� �������� ��� ��� ������...";
			link.l1.go = "Good_exit";
			NPChar.quest.NiceMeet = true;
		break;
		
		case "Usual_1":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		    NextDiag.TempNode = "Usual_1";
			dialog.text = "������� ��������� � ���� �����. ��� ������� ��� �� ��� �� ��� ���?";
			link.l1 = "������ ����������. ������ ����� ���������.";
			link.l1.go = "Good_exit";
			if (CheckAttribute(pchar, "quest.VisitStep"))
			{
				if (sti(pchar.quest.VisitStep)>2 && !CheckAttribute(pchar, "quest.wasInBeedroom"))
				{
					dialog.text = "�, "+ GetFullName(pchar)+" ����� � ���� ����. �� ��� ��, ������� ������ ���� �����. ����� ���������?";
					link.l1 = "���������, � ���� ���������� � ����� �����. �����?";
					link.l1.go = "Step_2";
				}				
				if (sti(pchar.quest.VisitStep)>2 && CheckAttribute(pchar, "quest.wasInBeedroom"))
				{					
					if (!CheckAttribute(pchar, "quest.already"))
					{
						dialog.text = "�� ������� �� �� �������� � ���� ����, ��������?";
						link.l1 = "�� ��� ���������, ���� ���������. � ������ � �� ��������������, ��� ��� �� ��������.";
						link.l1.go = "Step_1";
					}
					else
					{
						dialog.text = "������� ���, ��� �����?";
						link.l1 = "��, ���������, ��� ���������.";
						link.l1.go = "Good_exit";
						LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
					}
					DeleteAttribute(pchar, "quest.wasInBeedroom");
				}		
			}
		break;
		case "Step_1":
			dialog.text = "��� ��� ������, �� ������ ������ ������� ���������� ��������� ��, ��� ��� �������� � ��������� �����.";
			link.l1 = "������, ���������, ��� �������.";
			link.l1.go = "Good_exit";
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
			pchar.quest.already = true;
		break;
		case "Step_2":
			dialog.text = "� ����� ���� ���?";
			link.l1 = "���� �������� �� �������� �� ������.";
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = "�� �����, ��������.";
			link.l1 = "�������, ���������. � �����.";
			link.l1.go = "Good_exit";
			if (pchar.RomanticQuest == "DelivMigel")
			{
				dialog.text = "�� ������� �� ������ ������ �� ������, ������� ��, ����� ���, ���� ����� ������. ��� ��� �������, ��� �������.";
				link.l1 = "��, � �����, ���������. ������� ����.";			
			}
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
		break;

		case "Romantic_Battle_in_Bedroom":
		    if (CheckAttribute(NPChar, "quest.NiceMeet"))
		    {
			    dialog.text = PChar.Name + " " + PChar.LastName +", �� ��� ������ ������������� � ���� ��������? " + Characters[GetCharacterIndex("Isabella")].Name + ", ���� ��� ����������, � ������� � ����� �����. ��� ��� �����...";
			    link.l1 = "�, ��. ������ � ��-������� ������ �� ��� �����.";
			    link.l1.go = "Romantic_Battle_in_Bedroom_3";
			}
			else
			{
			    dialog.text = "���! ��! �������! � ������� ���� ����?!";
			    link.l1 = "�... � ����� ���� �� ������... � ���� � � ������ �� ����...";
			    link.l1.go = "Romantic_Battle_in_Bedroom_1";
			}
		break;
		
		case "Romantic_Battle_in_Bedroom_1":
			dialog.text = "���������, ������, ������ �� ������!";
			link.l1 = "���??? ��, ��� �� ��� ��������!";
			link.l1.go = "Romantic_Battle_in_Bedroom_2";
		break;
		
		case "Romantic_Battle_in_Bedroom_2":
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_3");
		break;
		
		case "Romantic_Battle_in_Bedroom_3":
		    NextDiag.CurrentNode = "Usual_1";
            Pchar.RomanticQuest.TalkInShop = true;// �������� ��� ����� - �� ������� � ��������
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_4");
		break;

		case "WeWaitYouTonight":
			NextDiag.CurrentNode = "WeWaitYouTonight";
			dialog.text = "�� � �������� ����� ���� ������� ��� ������� �������, �������.";
			link.l1 = "���� �����������, ���������.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;

		case "SeenMainHero":
			dialog.text = "���, �� ��� ������ �������, " + GetFullName(pchar) + "... ������ ��� ������� ������. ����� ��� ��������, ��� ��� ���� ����� ��������.";
			link.l1 = "...";
			link.l1.go = "SeenMainHero_1";
		break;
		case "SeenMainHero_1":
			AddQuestRecord("Romantic_Line", "9");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "SanJuan_houseSp6", "goto", "goto1", "Romantic_DeadBrother_3", 2.0);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			NextDiag.CurrentNode = "ArrestInHome_1";
			DialogExit();
		break;

		case "ArrestInHome_1":
			dialog.text = "���, ��� � ��.\n"+
				          "������, ���� ������� ���� ����������� ���� ������ �� ��������! � ������, ��������, ��������� ����� ���� � ��� ����! ��������! � ���� ���� � �����!";
			link.l1 = "������ ��������! ��� �� ���� ���� ������ �� ��������!";
			link.l1.go = "ArrestInHome_2";
		break;
		case "ArrestInHome_2":
			AddDialogExitQuest("Romantic_ArrestInHouse");
			NextDiag.CurrentNode = "Romantic_Battle_in_Bedroom_1";
			DialogExit();
		break;
		//����� � ������
		case "TalkInCave":
			dialog.text = "�-�-�, ����� ��� ������� �������! � ��� �� �����?";
			link.l1 = "��������, ���������, �� ��� ��� �������! ���� �� �� ����, ��� � ��� ���� ������!";
			link.l1.go = "TalkInCave_1";
		break;
		case "TalkInCave_1":
			dialog.text = "�������?";
			link.l1 = "��-��, �� ���������� ����. �� ���� ������� ���� ���... �������-�� ������?";
			link.l1.go = "TalkInCave_2";
		break;
		case "TalkInCave_2":
			dialog.text = "��� ����, �����...";
			link.l1 = "�����, ������� ����� ��� ������� � ���� �� �����, ��������. ������� �������� ���� ����� ������.";
			link.l1.go = "TalkInCave_3";
		break;
		case "TalkInCave_3":
			dialog.text = "� �� �� �� �� ��� �����?";
			link.l1 = "�, ���������, �...";
			link.l1.go = "TalkInCave_4";
		break;
		case "TalkInCave_4":
			dialog.text = "����� ���������! ����� ���������� � ��, " + GetFullName(pchar) + "!";
			link.l1 = "�������, ������� ���� ������... ��, � ��� - ��� ����� �������� ���� ����, ���������. �����, ����� ����� ������ ��� �� ����� ������ � ������? �� ��������� �����������...";
			link.l1.go = "TalkInCave_5";
		break;
		case "TalkInCave_5":
			dialog.text = "����, ��� �������� � �������� ������ �� �����!";
			link.l1 = "�������� ��� �������� � ����������� ����...";
			link.l1.go = "TalkInCave_6";
		break;
		case "TalkInCave_6":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto5", "", -1);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Romantic_SalvatorIsDead");
			DialogExit();
		break;
	}
}
