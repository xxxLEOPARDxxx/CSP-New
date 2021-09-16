void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "���� � �������, ��� ���� ������������ � ����� � �������?";
            link.l1 = "� �� ��� ������ ������?";
            link.l1.go = "HS_1";
			link.l2 = "��� �� ���� ����. �� ����� ���.";
            link.l2.go = "HS_2";
			link.l3 = "���� ��������� ������� �������������.";
            link.l3.go = "HS_2";
		break;

		case "HS_1":
			dialog.text = "�� ��� ����� ������������ �� �����. � ��, ��� �� ����� ��� �� �����-�� ��������.";
			link.l1 = "� ��� �� �� ������ �������?";
			link.l1.go = "HS_2";
		break;
		case "HS_2":
			dialog.text = "�� ������� ��������! ���������� �� ������� �������, ��� ���� ���� ������ �� �������� ������! ��� ���������� ��������� �����. ��������� ������� ������� ���� ��������� ������\n�� �������, ��� ����� ������� ��� ������� ������������ � �� ���������� �����? ������������? �� ������ �����! ���������� ���� ������, �� ������ ���������� �� ���� ������ ���� ����������� ���\n��� �� ������ ��������, ������ �� �������, ��� ���� ����� ������ ������ � ����.";
			link.l1 = "� �� ������� ����� ���������.";
			link.l1.go = "HS_fight";
		break;
		
		case "HS_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);
			
			string cnd;
			for (int i = 1; i<15; i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawn"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnFinish.function = "HellSpawnFinish";
		break;
		
		case "Ritual":
			dialog.text = "����� �� ������ ����? ������ �������� ��� ������ ������������?";
			link.l1 = "��������. � ���� � ��� ��������������.";
			link.l1.go = "Ritual_1";
			link.l2 = "��. ����� ��� �� �� ����������� ���� �����.";
			link.l2.go = "Ritual_fight";
		break;
		
		case "Ritual_1":
			dialog.text = "������ ���� ����� ������� ����� ���. �� ��� �� �������.";
			link.l1 = "������ ������, ��� ����� ���� �������.";
			link.l1.go = "Ritual_fight";
		break;
		
		case "Ritual_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			ref RitualLocLoad = &locations[reload_location_index];
			cnd;
			for (i = 1; i<sti(pchar.Hellspawn.num); i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawnR"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnRitualFinish.function = "HellSpawnRitualFinish";
			
		break;
	}
}
