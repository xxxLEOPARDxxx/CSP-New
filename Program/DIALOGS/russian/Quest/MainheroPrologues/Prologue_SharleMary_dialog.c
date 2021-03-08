void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.id == "SharleMary")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = GetSexPhrase("��� �������! �� ���� � �����!","������ ���! �� ��� � �����!");
				link.l1 = "�������. "+GetSexPhrase("����������","�����������")+" �� ����� �� ������. ���� �� ������? ��� ������� ��������� ��� ������.";
				link.l1.go = "2";
			}
			
			if (npchar.id == "SMPirate1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = "�������� �����, ����� ������� ������� ������� �� ��� ����! ���� ��������� ���� ������� � ����� �� ���� ����� �������, � ��� ����� �������! ��� ���� ��� �����, ��� ������� ��� ��������, ������ ������� ��� ������� ����!";
				link.l1 = "�� ��������� �������� �������� �� ���� ������� � ������ ���, ��� ��������, ������ ��� ��������� �� ����� ������������� ������, ��� �, ������� ������, ����������� ��� � ������ ����.";
				link.l1.go = "SMPirate1_2";
				if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
				{
					dialog.text = "�������� �����, ��� ������ �� ��� ����! ���� ��������� ���� ������� � ����� �� ���� ����� �������, � ��� ����� �������! ��� ���� ��� �����, ��� ������� ��� ��������, ������ ������� ��� ������� ����!";
					link.l1 = "� �������� �������� �������� �� ���� ������� � ����� ���, ��� ��������, ������ ��� ��������� �� ����� ������������� ������, ��� �, ������� ������, ����������� ��� � ������ ����.";
					link.l1.go = "SMPirate1_3";
				}
			}
			if (npchar.id == "SMCrew1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LocatorReloadEnterDisable("Shore_ship2", "boat", false);
				bDisableCharacterMenu = false;
				bDisableLandEncounters = false;
				dialog.text = "���������! ����� �� ��, ��� ��� ��� ���������, �� �� ��� �� ������ �� � �������\n������� ���� �����, � ������ ��� �� ������� �� �������� � ����� ����������, ��� ������� � ���������� ��������.";
				link.l1 = "� ���� ���������� � ����������� ����. � ���� ���� �����������, ������� ����� ������� ��� ����. �� ������ ���� �������� � �� ���������� ������.";
				link.l1.go = "SMCrew1_2";
			}
			NextDiag.TempNode = "First time";
		break;

		case "SMCrew1_2":
			dialog.text = "�� �� � ��� ���������, ����� ������������. ����� �� ����.";
			link.l1 = "�������!";
			sld = characterFromID("SharleMary");
			DeleteAttribute(sld, "cirassId");
			LAi_SetHP(sld, 100.0, 100.0);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "boat", "none", "", "", "", 10);
			link.l1.go = "Exit";
		break;
		case "SMPirate1_2":
			dialog.text = "...";
			link.l1 = GetSexPhrase("����: ","�����: ")+"��, ���� ������ �������� ��� �� ���������� � ��� ������� ����������� ����, ������ �����������.";
			link.l1.go = "SMPirate1_3";
		break;
		case "SMPirate1_3":
			dialog.text = "������, ��� ����, ���� ��� �� �����, ������������. �����, ���� �����������, ����� �� ��� � �����.";
			link.l1 = "...";
			if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
			{
				dialog.text = "������, ��� ����, ���� ��� �� �����, ������������. "+GetSexPhrase("�����, ���� �����������!","�����, ������ �����, ����� ��������� �� ��� � �����.");
				link.l1 = "...";
				link.l1.go = "SMPirate1_3";
			}
			link.l1.go = "Exit_fight_pirates";
		break;
		
		case "2":
			dialog.text = "���, � � �������.";
			link.l1 = "������ �� "+GetSexPhrase("����� ����?","����� ����?");
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "� "+GetSexPhrase("������","�����")+" ��������� ����� ������ �������, � ��� ������� ���������. ����� ������ ���������� ������. ����� �� ����, ��������, ��� ����-�� ������� � ������. � ����� ���-�� ������� � ����� ����� �� ������. �������� �������.";
			link.l1 = "�����.";
			link.l1.go = "Exit_follow";
		break;

		

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit_fight_pirates":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");
			
			SharleMary_FightPirates();
			
			//LAi_group_Attack(NPChar, Pchar);
			//LAi_SetWarriorType(NPChar);
			//LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit_follow":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.rank = 3;
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //�� �������� ����
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			if (NPChar.model.animation == "man") Npchar.CanTakeMushket = true;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // ��������
			LAi_SetImmortal(NPChar, false);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
		break;
	}
}