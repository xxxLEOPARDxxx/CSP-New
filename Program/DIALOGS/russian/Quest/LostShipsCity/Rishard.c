// ������ ������ - �������������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "� �� ����� � ����� ��������. �� ��������� ��� ������� �� ������ �������, ������������ �� �� �����. ����� �����!";
				link.l1 = "��...";
				link.l1.go = "exit";
				break;
			}
			// --> ������
			if (GetNpcQuestPastDayParam(npchar, "quest_date") >= 1 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "�! ��� � ��, "+ GetSexPhrase("������","�������") +". � � ��� ���� ����� ��� ���� ���������. �� ��� "+ GetSexPhrase("����� �������","����� �������") +"";
				link.l1 = "���-�� �� ������� ������������� ����������, ������. ��, ������ ����.";
				link.l1.go = "ring";
				break;
			}
			// <-- ������
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "��, ���� ����? ������� ������ - � �� � ����������. �� � ������ � �����, ����� ��������� ��� ��� � ���� ����.";
				link.l1 = "���, �� ��� �����, ��������?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "�, "+GetFullName(pchar)+"! "+TimeGreeting()+"! �� ���-�� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = LinkRandPhrase("���-������ ���������� ��� ����������?", "��� ������ ��������� �� ������� � ��������� �����?", "�� ���������� �� ��������� �������?");
				link.l1.go = "rumours_LSC";
				link.l2 = "� ���� ������ ���� ���� �������� �� �������.";
				link.l2.go = "int_quests"; //�������������� ����
				link.l5 = "�� ������ �����"+ GetSexPhrase("","�") +" ������ ��� � ���� ����. ��� ��������!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // ������ �������
			dialog.text = "�����? ���, �� �����. ������ � �� � ���� �������. ��� ���� �� �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "�� ������ �������������. � ��� �������, ���, ���� �� �������, ������� � ������.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "��? �� �����. � - ������ ������. �����-�� � ��������� ��������� ������� ������� ��������, � ��� ����� � ������������, �� ��������� ������ ��� � ������ � �����, ��� ��������� �� ������������� ����������� �������, ���������� ������ ���� � ��������� ��� �� ��� � ������.";
			link.l1 = "� � - "+GetFullName(pchar)+", ������� ������������ �������...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "�� �������� �����"+ GetSexPhrase("","�") +" ������� - ������ �������, ��-��?";
			link.l1 = "�� ��... ������";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "�-�... � �-�� ��� �������... �����, "+ GetSexPhrase("��������","�������") +", ����� � ����� ����...";
			link.l1 = "�����. ������� ���� ���������. ��� ��������!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("���-������ ���������� ��� ����������?", "��� ������ ��������� �� ������� � ��������� �����?", "�� ���������� �� ��������� �������?");
			link.l2.go = "rumours_LSC";
			link.l3 = "� ���� ������ ���� ���� �������� �� �������.";
			link.l3.go = "int_quests"; //�������������� ����
			NextDiag.TempNode = "First time";
		break;
		
		// ������
		case "ring":
			dialog.text = "� ���, ����� � ������ ��� �����-�� ������? �� ����� ����, ������ � ���� ��� ��� ���������� - � ���� �� �� ���! ����� ��� �����: ����� ��� �� ������� �����, ��� �� ���������� ����. ��� ���?";
			link.l1 = "�� ����, ��� ��� � ��� ������������ ��� ��, ����� � ����. ������ � ����, � ������ ����� ������� �����, ���� �� �� ���� �����������.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "����. ����, ����� �� ����... ��������, "+pchar.name+", �������, � ���-�� ���� ����������� ��� ������� ������? ��� ��, ��� ��� ����� ���������� � ��������� ������ �������?";
			link.l1 = "�� �� ��� ��� �� ���� ������� ������ ��������... ������ ���� � �� ��.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "� ��� �� ������ � �� ��������-��, ��-��! �����. �������� �����������, �������� � ����. (������� �����) ��� ������� �������� � �������� ������ ���� ������ ������������� �������. �� ����� �������� �� ������ ����� �����, ������ ���������-���������, ��� �������� �������\n������� ������� - �����. ������� ��� � ��� �������, ������ ��� ���� ��� ������� ������. ���� ����� �� ������ ������� ��� �� ���������, ��� ��� ���� ���� ������� ����������, ����������� � ��� ����� � ������.";
			link.l1 = "���������, � ���"+ GetSexPhrase("","�") +" �� ����. �� � �-�� ��� ������? ��� �� ������ ������� ���� � ����� �� ��������?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "������! ������ ������. � ����� ������ ����������� ������� �����. ����� ������ � ������� � ���� ��������� ��� ������� ����� � �������� ��� ��������� ������. ���� ��� ������ - ���������� �� ������� �� ���������, ��� ��� ��������� �� ������ �� ���� �� �������� ����� - � �� �����������\n��� � � ������� �� ��������� - ���������, � ������� �� ��������� ��������� � ����������, � �� ��������� ���� � ����� �� ������������� � ������ - ����� �� ����. ������� � � ������ � ����.";
			link.l1 = "�� ���� �� ����������� ��� �������� ������ ������ ����� �������, ���?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "�� ��. �� ��������� � ����� ����������: � ��������� ������ �� �������, � �� - ������������ ������. �� ��������� �� ������� ���������� ��� �����. ��� ����� ����������� - � ����� �����, �� ������"+ GetSexPhrase("","�") +" ������.";
			link.l1 = "���, ��������, �� �������������� ���� ���� �����������. ������� � ����� ���������������� ������� �� ����� ������ ���� ������������ ������� - ��� �� �� ���. ����� "+ GetSexPhrase("������� ��������� �����","����-������ �������") +", "+ GetSexPhrase("�������","���") +" ����� ������� ��� ���� ������� �� ����.";
			link.l1.go = "ring_exit";
			link.l2 = "���������... � ����� �����"+ GetSexPhrase("","�") +" �������� �� ������� ������. �� �����! � ������� � ���������.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "�������� �� ���... �� �������� �������� ������ ����� ������ �������... ��� �����, �� ���� ����� ��� ����� �� ���. �����, ���� ���. �����...";
			link.l1 = "����, ��������...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "� ���, ��� �� ������ � ����, "+ GetSexPhrase("�������","�������") +". � ���� ������������, ��� �� ����� ��� ����� ���� �����������...";
			link.l1 = "���������. ������� � ����� ������, �� �� ������?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "��� ����������, ������, ��� ����... ��, ���-�� ���.";
			link.l1 = "���������. ����� ����������?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "����� ������ - ������� ������� �������������, � ����, � ���. �������� ��������� ���������� � ����� ������ - � �������� ������ ���������� ��. ������������ �� ��������. ����������� � ������ ���� �� '����� ������'. ������, ��� ���?";
			link.l1 = "���. �������.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "�� '���-����������' �� ���� ������ ������� ������� �������. ��� ��� ���� ��� ����, � ����� ������� ����� - ������� � ���������� '����� �������'. ��������� ���� ����� ������ ������. ������� ����� ����� � ���� � '���-���������' ��� ������� ��������, � �������� ������� � ����� �������. ������ � ������� �� ������� ������.";
			link.l1 = "������. �� ������� ������!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "� ������ ����� �� '����� ������'...";
			link.l1 = "��-��, � �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // ������
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // ���������
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "���, ��� � ��, "+ GetSexPhrase("�������","�������") +". �����"+ GetSexPhrase("","�") +" ��������� �������� �����?";
			link.l1 = "�������!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "����� ������. ������ ������� ������ � ������� �������� ������ � ������: ������ ��� ��� ����������� �������, �������� �� ����?";
			link.l1 = "��... ��, ����.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "������ ����� ����� ���� �� ������� ������. ������ ������ � ������ � ��������� ������� ������? ������� ����� �� ���. ���������� ������������.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "���, �������, ����... ��, "+ GetSexPhrase("�����","�����") +"!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "��� ����. ������ �����, ������ �� ����������, � ����������� ����� �������. ��� ��������� ������ - ������ � ������ ������, ����� ����� ���������� �� �������� �������. ���� � ���� ����� ������� - ����� ������ � ������� �����. ����� �����: � ���� �� ������, ���� �� �� ��������� ���� ������.";
			link.l1 = "�� � ����� ��� �� ���� ������������ �����, � �����. �� - ����������� �������, � - ��������� ������. �������?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "�������! �� �����, � �� �����!";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "���, �� �������! ����� �������"+ GetSexPhrase("���","����") +" �� ���� ���� ��������!";
			link.l1 = "���-�� ������� ��� � '������-����' ������... �� ���������, ��� ��� ���?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = ""+ GetSexPhrase("�������","�������") +", � �� �� ����� � ���� �� �������������. � ������� �������, � ������, � �������� ������ �������. ��� ��� � ���� � � ������ �� ���� ���� �����.";
			link.l1 = "�����. ����� ����������� ����, ��� ��...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "� ��� ��! ���� ������ �� ���� �� ���� �������, �� ������ ��?";
			link.l1 = "�����! �� ����� ������ �������...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 ������ �� ����������
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "������, "+ GetSexPhrase("�������","�������") +", � ��� �� �� ��������, ��� �����. ������� �������, �����, ��� ��� ������.";
			link.l1 = "������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "���� ������ ����������. ����, ����� ������ ������� ���: � ������ - ��������, � ������ - �����. ���� ������� ���� � ��������� �������� ����. � � ���� ���?";
			link.l1 = "���� ������ ����������. ��������� ������ ������������ �������, ��������� - ��� �� � ������, �������� �� �����.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "�������� �����... ����������� ������, ������ ������ � �����.";
			link.l1 = "�����.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
/* 			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			} */
		break;
		
		case "ring_22":
			dialog.text = "׸�� ������! �� ������ �������� �� ���! ��������� �������� ������ �������� � �� ������! ��� ��� ����������?!";
			link.l1 = "�� �����! ���� ����� � �� ��������, �� ��������� �� ��������. ������ � � ����� ������� ���������...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "��! ������� ��� ���� ������������, ��� �� ����������� �������� �������. ��� �� � ���� - ��� ����� ������� �� �� ����...";
			link.l1 = "������, � ��� �� ������ ��������������� ��������� � �������, �? ��� �� ������ � �� ���� �����?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = ""+ GetSexPhrase("�������","�������") +", ��-������, ����� � ��� ������, ������� � ���������. ��-������, � �� �� ������, ����� ����������� � ������ - � �������������, � �� ������ ��������� ���������� �� ������ � ���������. � �������, � ��� ������ �� ����� ������� � �������, ������ ����� � ���������. �� � �-��������, �� ������ ��� ����� ����� �� ������� � ������ ������\n��� ��� �� ���� ���� ������. ����� ����� �������� ������. ������, ����� ��� ��� ������� ����, ���� ������� ������� � ��������� ��� - ������ - ������� �� ���� � ������ � ������, ����� � ������� � �����...";
			link.l1 = "�� ����. ������� ��� ��� ���������, ��� ��������. �����, ����� ������ ���-������ ����������.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "���. � ���� �������� ����� �� ���������� ���������.";
			link.l1 = "��, �� ������ �������. ��������� ����� - ���� �� ������.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 ������ �� ����������
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "� ����� ������ �������������... ����� ���� ���������� �������, � ��. �� ��� ��������� - �� ������� ��������� ������ �� ������. ��� ���� ������ ����� � ������. ��� ��� - ���� � ����� ��������. �����, �������� ���...";
			link.l1 = "������ ���������� - ���� ��� �����, ��� ��� ����� ����������. �����, ����� � ����� "+ GetSexPhrase("������","������") +"?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "�����, "+pchar.name+". �� �� �� ����� ��� � ���� �� ������ ���������. � � ����� ���� - ������...";
			link.l1 = "��, �����...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // ������ ������ '�����-�����'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "�������, ��� ������� - �� ��������� �� ������, �� �����-���� ������ ������. � ������ ��������� ��� ��� ����� ����� ���� - ������� ������, � ��� ������� �������: ����� ���� �������� �������� � ������ ��������� ��������� � ���� ������ �� �����!";
			link.l1 = "�� ��������. �� ��������� ������ - ��� �������� �������� � ����������� �����. ����!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 ��� �� ����������
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "��-��! ��� � � �����! ���� � ������� ���� �������� - ���������� ������� � ������� ��� ����������� �����! ������� ����� ������ ��� ������ ��������, �� ���� �� ��������! ������, ��� ��� ������� ������! ���"+ GetSexPhrase("","�") +" �� �� � ����� �� "+ GetSexPhrase("�����","�����") +" ����� ������!";
			link.l1 = "��-��, ������!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "����� ����� ��������, ��� ������� � ���������, ������� ��������� � ���� ��������������! ����������� ��� ��������... �����, ��� ���� �� ������ ���� � ����� �����, ���� � ����������� �� �������. ����� ��-�������, ���������, ��� ��������������.";
			link.l1 = "�������, ������. ���� ���-�� �� � ����� ����������!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("�� �������� ������");
			Log_Info("�� �������� 25 ���������");
			Log_Info("�� �������� ��������� ��������������");
			PlaySound("interface\important_item.wav");
			dialog.text = "��, � ��, ��� ������ �� ��� ����� � ����� � �� ������ - ������� ����. ����? � �������� � ������ ���-������ �������� ����?";
			link.l1 = "��������� ��������� ����������, ��������, ������, ������ ������.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "������ ��� ����. � �����-������, �� ��������"+ GetSexPhrase("","�") +" ����� ������� ������.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // ������ ������
			{
				link.l1 = "������. �� � "+ GetSexPhrase("�����","�����") +" ���-��� ���, �� ����� �����, �������� ��������. ���, �� ����� ����� ������� ������. �������, ������������ � ��, ����� ���������... �� ���-��� ��� ������ �������� � ���: ���-�� � ����� ������� ����� ���� ������! ������ ���!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // ���� ������
				{
					link.l1 = "������. �� � "+ GetSexPhrase("�����","�����") +" ���-��� ��� - ������� ������ �������� ����� �������.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "������, � �� �������� ������ ������ ��������, ��-��. �� ���, ���� ������������?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "��. ��� ������� ������ �� ����������� - ����� ����� ����� ������. �����, �������, ������ ��� �� �����, � ��� �������� ���������� ��� �����. �� ���� ����� �������� � ��������.";
			link.l1 = "������, ��� � �������. �������, ������ ������ ���� ������� �� �����. ������!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "�� ��� "+ GetSexPhrase("������","������") +"?";
			link.l1 = "���� ���...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "����� ����� ������! ��� ����� ����������� ������ ��������. �� � ������ ��������� ������, ������ ���� ������� �������� ���. �����!";
			link.l1 = "��. ������, ������ ��������...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = ""+ GetSexPhrase("������","������") +"? ��� ��� ��������?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // ������ ������
			{
				link.l1 = "��� �������� �����... ������� ����� ���������... �� ���-��� ��� ������ �������� � ���. � �����, ��� �� ����� �����, �������� ��������: ���-�� � ����� ������� ����� ���� ������! ������ ���!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "������. ������ ������ � ��������...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "�� �� ���?! "+pchar.name+", � ���... ����� �����. ����� �������� ��� � ������������, ��� ��� ��������, �?";
			link.l1 = "�������: ���� ����� ��������� ��������� ���� �� ������ ����� � ������� ����� �������. ������� ���� ���� � ��� ���������-�������� �� ����� ������� �������, � ��� �������� ���, ��� �� ���� ������ ���������������� �����...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "���������������� ���� � ���� ������� ����������. ��� �������� �������, ����������, ��������� ���� ������� �����, � ������ �� ��������� � ��������������� ������ ������ �� ������� � ���� �������, ������ � ���� �� ������ � �������� ������...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "��, �����, ����� ���������� ���������� ����� �� ������ ���������: ������� ����� � ������ �����, ������ ������������� ������� ����, �� ������� ��������� �������� ���������, ������ ������. ������� �������� �� ���� ��������, ���� ��������, � ����������� ��������� � �� ����. ���, �������, ���������, � ������� ������� ����...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "������� �������� ���� ���. ��������� ������ - �� ������� ������ � ��������� � �����, �������������, � ���������� ������� ������ �����. �� ��������� ���������� �����... ������, ��-�� � ����� ����� ����. ��� ����������� �������� - ����: ������� ����������, � �������, ����������, ��� ���� ������������.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "��. ������������� ��������. �� �� �� ������? � ����� ������� ����� ���� ������? � �� ���� ����� ����! �� ������� �� ���? ����� ������ � ����! � ������� ������ ���, ������ �����!";
			link.l1 = "�����. ��� ���� �� �������� ���������� � �������.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // ��������� �����
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // ��������� ���� // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // ������� ������
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ������ ���������� �� �������
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// ��������� ������ �����
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "��-��! �� ����� ���! ��� ������������� ����! �� ������ ��������, ����� �������� ����! ����� ����! �� ��� �� ������ ���� ����� �������! ������� �� ����� ����� ����� ������!";
			link.l1 = "����������, ���������. ���� �����������, ������, ����������� ������������� �������... ��� ������ � ������� �����?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "��� ���? ������� ���������!";
			link.l1 = "��� �������. ��� �� ��� ������� �����������? ����� ��������, ��� ������������� ���� ������?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "��! �������, �� ������ �� ����� ��������, ������� ����� � ������� �� �����. �-�� ���� �������! ����� ������ �������� ������ ��������� � ����� - ��� ����� ��� ����. � ��� �� ������� ������ � � ����� � ����� �������\n� �� - ����� �� ����� �����, ��� ������ ������. �� ����� ���� ���������, � �� ����� ������� - �������� ���� � ����. �� ����� �����: � - ������� ��-������ �������, � �� ���� ���� ���� �� ������ ����������. � ��� ������, ��� ���� �����... ����� � ����� ��������.";
			link.l1 = "������. � ����, ��� ��� ������� �� ����� �������. ����� ������������� ���� ���� � �����...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("������ ��� ����..."+ NewStr() +"������ ��������!", "", 0, 5);//��������
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "��� � ��... �������, "+pchar.name+", ��� "+ GetSexPhrase("����������","�����������") +" ����� �� ���� �� ����. ��� ���� �� ������ �� �����. ������ ����� ����������� ���������� �������, ����� ������ �� ���������... �, �����. �� ���� ������ �� ���� �������\n� ���� ��� ����� ����� ������ - ����������� ��� ������ �� ���������� ������. ����, "+ GetSexPhrase("�������","�������") +", ����� ������ ������������� ����� �����!";
			link.l1 = "����, ������. ������� ������� ���� �������. ��������!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // ��������� �����
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // ��������� ����
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- ���� �������� � ������� ---------------------------------------------
		case "int_quests":
			dialog.text = "�������? ��, �� �����, ��� ���� ��� ��� ����������...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "��� �� ����� ����?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "�� �� ����� ��������� ������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "� �� ������� �� ����� ��������� � ������ �� ������? ��������, � ��������?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "��� ���, �� �������� �������� ������ ����� ����� ����� ���� �����������?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "��� ��������. ��������...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "������ ��� ����� � � ���������� ��������� �������� �������� ����� �������� � ����� �� ������ ���������� �������. �� ������� � ����� ��������������� ������� - ���� �� ��������� ���� ����� � ���������� ������ ���� �� ������ �� ������ �������� �������� � ������\n��� ��� ���� ��������! � ���������� ����� ������ ���� �� �� - � �������� ������ �� ��������, ������� �� ������ ���� ������� ����������, �������� � ������ ����� ���������! �� ���� ���� � ����������� �������, ��� ��� ������� ���� ���� ������� � ������ �����������\n�� ����� �������� �����, ������ ����� � ����� ����� �����. � ���� ����� ���������� ������ - ������ ����� ���� � �������, � �� ������� ���� ���������� �� �������. ��������� ��� ��������� ����� �� ����, �� � � ������� ��������� ���������� �����������\n�� ��� ���, ���� ��� � ����� ������ �� ������� � ���� � ���� ����� �� �������. ��� � ���� �������� ������ �� ������� ���� - � � ��� ������ �� ���� �� ��� ���. ����� ������� � � ���� ����� �� ���, � ��� ������ ��������.";
			link.l1 = "���������� �������...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "��! � �������� ������, ���� ������! �� �� ������. ��� ��� ������ �� ����? ������ � ���� �� ��������, ����� ���� �� �����. ��� ��� ������ ����� �� ������� ������ ������� � ������� ������, ��� ���� ������� �������� - ����� �� ����� ������� �����.";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "� �����? ����� ����� ��� ������ ����� ����� ���� ������ � ������� ���������, ����� ����, ��� �������� �������� �� '���-��������'? �� � �� ����� ��� �������� ����������� � ���� �����. ��� �� - ������������� �����������, ��� ��... � ��������� ����� �� ����� ��. ���, �� ����� � ���� ��� �� ����.";
			link.l1 = "����...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "� ��� ��! ����������� ������ � ����� � �����. ������, ����� �� ������� ��������? ����� � ��� ��������� ����� �������. �� � ����� ������, �� ������� ������ ��� ����� ����� ��������������� � ��������������� �������, � ������ ������� ����� ����� ������ ������ � ������\n�� ��������� � ���, ��� �� �������� ������ ����������� ���������� ������ - ��� ����� ������ � �����, � ���� ����������� ��� �������������� � �������� ������ - ������ ��������� � ����� �����, ������ �������������� �� ���������. � ����� ���� �����. ��� ����� ����� ��� �������.";
			link.l1 = "��... �������.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- ���� �������� � �������
		
//----------------------------------------- ����������� ������� -----------------------------------------------
		//����������� �� � ��������
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("��� �� ��� ���������, �? �� �� ���!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������!", "�� �������� ������ �������"+ GetSexPhrase("","�") +"?! ���� ��� ����� �� ������!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "��, ���, ������, ���?! �� �������� ������ �������"+ GetSexPhrase("","�") +"?! ���� ��� ����� �� ������!";
			link.l1 = "��� ����!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//��������� �� ����������� ������
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("������, �� �� �����"+ GetSexPhrase("","�") +" ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� "+ GetSexPhrase("�'��������","������������") +", ������� ���, ������ ������? ����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������� �������") +"...");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ��������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ��������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","��������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","�������") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- ����������� �������
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}