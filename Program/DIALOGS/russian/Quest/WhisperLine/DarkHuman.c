void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "������";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";
		
			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "� ��, ����!";
				link.l1.go = "CS";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "DH_Villemstad_merc":
			dialog.Text = "� �����, ����� ������ �� �����.";
			Link.l1 = "� ������������ ������.";
			Link.l1.go = "DH_Villemstad_merc_exit_to_bank";
		break;
		
		case "DH_Villemstad_merc_exit_to_bank":
			DialogExit();
			sld = CharacterFromID("Villemstad_usurer");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_usurer";
			
			sld = CharacterFromID("Villemstad_shipyarder");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_shipyarder"
			
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "DH_Villemstad_shipyarder":
			dialog.Text = "������������, ���� ���.";
			Link.l1 = "������������. �� ���� ����� - ���� ���������� �������, � �� ����������� ���������.";
			Link.l1.go = "DH_Villemstad_shipyarder_1";
		break;
		case "DH_Villemstad_shipyarder_1":
			dialog.Text = "������� ������ �������� ����� � � ��������� ������, �� �������� ���� �� �����. � ���� ���� ��� ��� �������� �����������.";
			Link.l1 = "� ����� ��?";
			Link.l1.go = "DH_Villemstad_shipyarder_2";
		break;
		case "DH_Villemstad_shipyarder_2":
			dialog.Text = "������, �����������. ����� ������ ����������� � ����� �����. �����������, �� ������ ��� ���������������� ���������� ��������� ����� ������ ����� �������� � ��������� ���� � �������� �������.";
			Link.l1 = "������ � ����� ������, �� � ��� ������?";
			Link.l1.go = "DH_Villemstad_shipyarder_3";
		break;
		case "DH_Villemstad_shipyarder_3":
			dialog.Text = "������ ��, ��� ���������, ������� ��������� ������� ��... ��� �� �������, ��������� ��������. � �� � �������� �����, ��� ������ �� ����������� ����� �� ����� - ��� ������� ����. �������� ���� �������������� ��� ������ ���������. ����� ���������� ����������������� ����� ��� ����� ���������� ������������� ����� ��������� �������, ������� ���� ����������. �� �� ����.";
			Link.l1 = "��, �������� � ����.";
			Link.l1.go = "DH_Villemstad_shipyarder_4";
		break;
		case "DH_Villemstad_shipyarder_4":
			dialog.Text = "��� ���, �������������� ��� ��������� �������, ��� �������� ������������ ����� � �� ��� ������. � ���� �� ���� � ����������� �������������� ������� � ������ ������ ������ ��������� �� ��������. � ����� ��� �� ��� ������ ��� ������� ����. ";
			Link.l1 = "���������?";
			Link.l1.go = "DH_Villemstad_shipyarder_5";
		break;
		case "DH_Villemstad_shipyarder_5":
			dialog.Text = "����� ����� - �� ������, �� ���� ���������� � ��� ���� �������. ��� ��� �� ������ - �� �������. ";
			Link.l1 = "���� �������?";
			Link.l1.go = "DH_Villemstad_shipyarder_6";
		break;
		case "DH_Villemstad_shipyarder_6":
			dialog.Text = "15 ����� � ��� ����. ������ �����, �������� �������� ��, � ���� ���, ��� ��� ��������� ������, � ����� � ���������.";
			NextDiag.TempNode = "DH_Villemstad_shipyarder_wait_money";
			Link.l1 = "��� �, ������, ��� ������ �������� ������.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 15000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "����.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_wait_money":
			dialog.Text = "�������� ������?.";
			Link.l1 = "���� ���, ����� ��� ������� ���-����� ����.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 15000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "��.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_getship":
			AddMoneyToCharacter(pchar, -15000);
			DeleteAttribute(pchar, "DH_mercLeft");
			pchar.location.from_sea = "Villemstad_town"
			setWDMPointXZ(pchar.location.from_sea);  // ����� �� �����
			pchar.Ship.Type = GenerateShipExt(SHIP_EMPRESS, 0, pchar);
			SetBaseShipData(pchar);
			pchar.Ship.Name = RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple("������� �����", "������ ����"), "�����������"), "��������"), "������"), "������"), "�������"), "����������"), "�������");
			SetCrewQuantityFull(pchar);
			ChangeCrewExp(pchar, "Sailors", rand(30)+20);
			ChangeCrewExp(pchar, "Cannoners", rand(30)+20);
			ChangeCrewExp(pchar, "Soldiers", rand(30)+20);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_PLANKS, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
			// ������ �������
			pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)*0.05) * (MOD_SKILL_ENEMY_RATE);
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			
			InterfaceStates.DisFastTravel = false;
			bDisableLandEncounters = false;
			
			dialog.Text = "�������, ���������. �� ������� ���� �������� �����-�� ������� � �����, ��� �� �����-�� �������� ���� �����.";
			Link.l1 = "�������. �� ��������.";
			Link.l1.go = "exit";
			npchar.Dialog.Filename = "Common_Shipyard.c";
			NextDiag.TempNode = "first time";
		break;
		
		case "DH_Villemstad_usurer":
			dialog.Text = "�������-�� �� �������, � � ��� ������� �����������, ���� �� �� ��������������. ������� ������ ���� ������ �����������, ������� ��������� �����?";
			Link.l1 = "����� ��� ������, �� ������ ���� � ����� �������� ���������� ������� �������.";
			Link.l1.go = "DH_Villemstad_usurer_0_1";
		break;
		case "DH_Villemstad_usurer_0_1":
			dialog.Text = "��. ������� �������. �� ������� ������� �������� � �������������?";
			Link.l1 = "�����. ";
			Link.l1.go = "DH_Villemstad_usurer_0_2";
		break;
		case "DH_Villemstad_usurer_0_2":
			dialog.Text = "��� �� ���� ����. "+GetFullName(characterFromId("DH_mercenary"))+", ����������, ��� ���� ����� ������ �������. ";
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_3";
		break;
		case "DH_Villemstad_usurer_0_3":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_4";
		break;
		case "DH_Villemstad_usurer_0_4":
			dialog.Text = "�� ����� ������, �� ���� ��� ��, � � ����� ������� ��������.";
			Link.l1 = "���� �� ����.";
			Link.l1.go = "DH_Villemstad_usurer_0_5";
		break;
		case "DH_Villemstad_usurer_0_5":
			dialog.Text = "��� ������.";
			npchar.lifeday = 0;
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_6";
		break;
		case "DH_Villemstad_usurer_0_6":
			DialogExit();
			pchar.DH_mercLeft = true;
			LocatorReloadEnterDisable("SantaCatalina_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload2_back", false);
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			sld = CharacterFromID("Villemstad_usurer");
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_7";
		break;
		
		case "DH_Villemstad_usurer_0_7":
			dialog.Text = "���-�� ���?";
			Link.l1 = "� �� ����� ������� ���� �����.";
			Link.l1.go = "DH_Villemstad_usurer_1";
		break;
		case "DH_Villemstad_usurer_1":
			dialog.Text = "��� �����... ������, ��� ���� ��������� ���������...";
			Link.l1 = "����� ����� ���� ��������� � ����������� ��� ���� �����?";
			Link.l1.go = "DH_Villemstad_usurer_2";
		break;
		case "DH_Villemstad_usurer_2":
			dialog.Text = "������ ��... ���������, ������ ������ ������, ������ ���. ������ ������ ����� ������, ������ ���.";
			Link.l1 = "�� ����� ��������� ���� �������� ����� � ����� ������?";
			Link.l1.go = "DH_Villemstad_usurer_3";
		break;
		case "DH_Villemstad_usurer_3":
			dialog.Text = "�� ����������� ����, ��� ������ � ��� ����� ������� �� ����� ��� ����� ����� - �������. �� ��� ����� ����� �������� ��� ������ ������?";
			Link.l1 = "��� ������ ������ - ������. ������, � ���� ������� ������ ��� �� �����, ��� � � ����� ��������, � �������� ���� ����� ��� �� ��� �� �����!";
			Link.l1.go = "DH_Villemstad_usurer_4";
		break;
		case "DH_Villemstad_usurer_4":
			dialog.Text = "������, ���� � ���� ���� ������ �� ���������, �����, ��� ������� ����� ��������� ������ ������.";
			Link.l1 = "� ����� ��? ";
			Link.l1.go = "DH_Villemstad_usurer_6";
		break;
		case "DH_Villemstad_usurer_6":
			dialog.Text = "����������� �����. ���, ��������.";
			Link.l1 = "�� �� ����...  ";
			Link.l1.go = "DH_Villemstad_usurer_7";
		break;
		case "DH_Villemstad_usurer_7":
			dialog.Text = "���� � ��� ������������, �� ��� �� �������� ��� �����...";
			Link.l1 = "�����, ��������, ������ ��� � ���� 30 ��������� � ������ �������� �� ���������.";
			Link.l1.go = "DH_Villemstad_usurer_8";
		break;
		case "DH_Villemstad_usurer_8":
			LAi_SetOwnerTypeNoGroup(npchar);
			Log_Info("�� �������� ����������� �����.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "sculMa"+(drand(2)+1), 1);
			dialog.Text = "������������, � ���� ������� ����� ����.";
			Link.l1 = "� ��� �������.";
			Link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp.DH_Villemstad_money");
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			AddQuestRecord("DarkHumanQuestline", "6");
		break;
		case "DH_Villemstad_usurer_get_money":
			dialog.Text = "��������, �� � ���� ���� ��� ������ �����.";
			Link.l1 = "� ��� �������.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			if (GetQuestPastDayParam("questTemp.DH_Villemstad_money") >= 28)
			{
				AddMoneyToCharacter(pchar, 35000);
				dialog.Text = "� ��� ����. ������ � ����� ������� ��� �����. ���, �������. �������, �� ��� �������� ��������������� ����� ��������.";
				Link.l1 = "�� �������-��. ������ ����������, �� � �� �� ��������.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				npchar.Dialog.Filename = "Usurer_dialog.c";
			}
			
		break;
		
		case "DH_mercenary_SK_vavern":
			dialog.Text = "����� ���� ���� ������ ���� ���������.";
			Link.l1 = "�� �� ��������� ���� ������������� � ������ ������ �������� ����� � ���� ������ ��������. ������ ����� ������ �������� �� ������� �������� �� �������.";
			Link.l1.go = "DH_mercenary_SK_vavern_1";
		break;
		case "DH_mercenary_SK_vavern_1":
			dialog.Text = "��-��-��. ����, �� � ������ ������������� � �� ��������� ������������ ��� �� ����� �������. ";
			Link.l1 = "� ��� �� ���������?";
			Link.l1.go = "DH_mercenary_SK_vavern_2";
		break;
		case "DH_mercenary_SK_vavern_2":
			dialog.Text = "��������� ���������� ��������, ������� ������� ������ ��������� ������ ��������. ";
			Link.l1 = "������.";
			Link.l1.go = "DH_mercenary_SK_vavern_exit";
		break;
		case "DH_mercenary_SK_vavern_exit":
			chrDisableReloadToLocation = false;
		
			DialogExit();
			sld = CharacterFromID("SantaCatalina_Smuggler");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_SK_smuggler";
			
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "DH_SK_smuggler":
			dialog.Text = "����� ��? ��� ���� ���� �������? ";
			Link.l1 = "��� � ����� ����������� ���������� ��������� �� �������.";
			Link.l1.go = "DH_SK_smuggler_1";
		break;
		case "DH_SK_smuggler_1":
			dialog.Text = "������� ������, ��� �����. ��� ��������, ���� �� ��������. ������ �� �����.";
			Link.l1 = "������.";
			Link.l1.go = "DH_SK_smuggler_2";
		break;
		case "DH_SK_smuggler_2":
			AddMoneyToCharacter(pchar, -sti(pchar.money));
			pchar.money = 10;
			//Log_Info("�� ������ ��� ������, ��� ���� ��� ���.");
			PlaySound("interface\important_item.wav");
			dialog.Text = "���-�, ����� ����������, ���������.";
			Link.l1 = "...";
			Link.l1.go = "DH_SK_smuggler_exit";
		break;
		case "DH_SK_smuggler_exit":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.dialog.filename = "Smuggler Agent_dialog.c";
			DoQuestFunctionDelay("DarkHuman_Villemstad", 1.0);
			WaitDate("",0,0,7,2,25);
		break;
		
		case "DH_mercenary_SK_gate":
			dialog.Text = "���������.";
			Link.l1 = "����, ����� �������� ����! �� �����, ��� ��� ������ ������� �������!";
			Link.l1.go = "DH_mercenary_SK_gate_1";
		break;
		case "DH_mercenary_SK_gate_1":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		
			chrDisableReloadToLocation = false;
			dialog.Text = "� ����� ������ �� ���������, ������ �� ��������� ����� ����.";
			Link.l1 = "��, �������.";
			Link.l1.go = "exit";
		break;
		
		case "DH_mercenary_Amatike_return":
			dialog.Text = "�� ������ ����� ��� ��������?! ";
			Link.l1 = "������� �����? ������� �� ��������?";
			Link.l1.go = "DH_mercenary_Amatike_return_1";
		break;
		case "DH_mercenary_Amatike_return_1":
			dialog.Text = "��, ������! ������� ��� ��� ����������...";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_2_sailor";
		break;
		case "DH_mercenary_Amatike_return_2_sailor":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_3_sailor";
		break;
		case "DH_mercenary_Amatike_return_3_sailor":
			dialog.Text = "��... �� ���������, ����� ����!";
			Link.l1 = "��� ������ � ������ ��� ����� ��������! ���� ����� �������? ���� ���� ��� �� �����!";
			Link.l1.go = "DH_mercenary_Amatike_return_4_sailor";
		break;
		case "DH_mercenary_Amatike_return_4_sailor":
			dialog.Text = "������� �� �������.\n��� ������ �� �������� ���� � ������, ��-�� ���� ������ ��������� ������. ������� ����� ������� ��������, �� ���� ������ ���� ��� ������� � ������ �� �����. ";
			Link.l1 = "������...";
			Link.l1.go = "DH_mercenary_Amatike_return_5_sailor";
		break;
		case "DH_mercenary_Amatike_return_5_sailor":
			dialog.Text = "������� ������, �� ����� ��� � ����� �����. ";
			Link.l1 = "�� ����, ������.";
			Link.l1.go = "DH_mercenary_Amatike_return_6_sailor";
		break;
		case "DH_mercenary_Amatike_return_6_sailor":
			dialog.Text = "������ ��� ���� �� �������, ���� �������� � ����� � � ����� ���� ����� ����. ";
			Link.l1 = "� �������?";
			Link.l1.go = "DH_mercenary_Amatike_return_7_sailor";
		break;
		case "DH_mercenary_Amatike_return_7_sailor":
			dialog.Text = "����� ��� ������� � �� ����� �������, ���� �������, � ���� �� � ������� ��� ��������� ������, ������� ���� ���� � ����. ";
			Link.l1 = "���, � ��?";
			Link.l1.go = "DH_mercenary_Amatike_return_8_sailor";
		break;
		case "DH_mercenary_Amatike_return_8_sailor":
			dialog.Text = "� ��� �? ���� �� ��������, ��� ����� ��� � ��������� � �����. � ��� ����� ������ �������. ����� ������ ������ ���������� � �������� �� ������ � ���� ����� ���, � ����, ��� �� ������ ���������.";
			Link.l1 = "��������.";
			Link.l1.go = "DH_mercenary_Amatike_return_9";
		break;
		case "DH_mercenary_Amatike_return_9":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_10";
		break;
		case "DH_mercenary_Amatike_return_10":
			dialog.Text = "� ��� ��� � ��� ������?";
			Link.l1 = "� ������.";
			Link.l1.go = "DH_mercenary_Amatike_return_kill";
			Link.l2 = "� �� ����� ��� �� ��� ��������, � ������ ���� � ���� �� ��������.";
			Link.l2.go = "DH_mercenary_Amatike_return_10_1";
		break;
		case "DH_mercenary_Amatike_return_10_1":
			ChangeCharacterReputation(PChar, 30);
			dialog.Text = "�����.";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_kill":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_kill_1";
			sld = CharacterFromID("DH_mercenary");
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_11":
			dialog.Text = "��� ����� ������ ������?";
			Link.l1 = "���������� �� ������ ����� �����.";
			Link.l1.go = "DH_mercenary_Amatike_return_12";
			
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
		break;
		case "DH_mercenary_Amatike_return_kill_1":
			ChangeCharacterReputation(PChar, -30);
			dialog.Text = "����������, �� �������� ����!";
			Link.l1 = "�� �������� �� ���, ����� ������ �� ������������.";
			Link.l1.go = "exit_fight_sailor";
		break;
		case "DH_mercenary_Amatike_return_12":
			dialog.Text = "�� ����� �������� ���� �� �������.";
			Link.l1 = "�� � ��������� ������ ����� ��������� � ����� ������, ���� �������������� �������.";
			Link.l1.go = "DH_mercenary_Amatike_return_13";
		break;
		case "DH_mercenary_Amatike_return_13":
			dialog.Text = "�����.";
			Link.l1 = "� ������� �� ������������� ����� ������� �������� �������.";
			Link.l1.go = "DH_mercenary_Amatike_return_14";
		break;
		case "DH_mercenary_Amatike_return_14":
			dialog.Text = "���� ������. � ����?";
			Link.l1 = "� ����.";
			Link.l1.go = "DH_mercenary_Amatike_return_15_exit";
		break;
		case "DH_mercenary_Amatike_return_15_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			
			LAi_Fade("", "");
			WaitDate("",0,1,3,17,25);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("DarkHuman_SK", 1.5);
		break;
		
		case "DH_mercenary_temple_afterstash":
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetImmortal(sld, true);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetImmortal(sld, true);
			}
			dialog.Text = "��������? ";
			Link.l1 = "������ ������ � ��� ������ ���� �� ����������... � �����.";
			Link.l1.go = "DH_mercenary_temple_afterstash_1";
		break;
		case "DH_mercenary_temple_afterstash_1":
			dialog.Text = "���? ";
			Link.l1 = "��� ������ �����������, ������ ������ �������. ������� ��� ��� ���� ���, � �������������� ���� ... ������ ������� ����� �������. ";
			Link.l1.go = "DH_mercenary_temple_afterstash_2";
		break;
		case "DH_mercenary_temple_afterstash_2":
			dialog.Text = "��, �� � ���� ����� ������?";
			Link.l1 = "����� �� ����, �� � ��������� ������ �������� ����� ��������� � ����� ������.";
			Link.l1.go = "DH_mercenary_temple_afterstash_3";
		break;
		case "DH_mercenary_temple_afterstash_3":
			dialog.Text = "�������������... ������� �����, ������ � �����������!";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_temple_afterstash_exit";
		break;
		case "DH_mercenary_temple_afterstash_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			
			LocatorReloadEnterDisable("Temple", "reload1_back", false);
			LocatorReloadEnterDisable("Temple", "reload2", true);
			DeleteAttribute(pchar, "CantTakeItems");
		break;
		
		case "Dark_Incquisitor":
			dialog.Text = "����� ���� �� ���... ��� ��, ������ ���!";
			Link.l1 = "...";
			Link.l1.go = "Dark_Incquisitor_fight";
		break;
		case "Dark_Incquisitor_fight":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = CharacterFromID("Dark_Incquisitor1");
			LAi_SetWarriorTypeNoGroup(sld);
			sld = CharacterFromID("Dark_Incquisitor2");
			LAi_SetWarriorTypeNoGroup(sld);
			AddQuestRecord("DarkHumanQuestline", "2");
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1 = "locator";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.location = "Temple_Inside";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator_group = "item";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator = "item1";
			PChar.quest.DarkHuman_Temple_Stash.function = "DarkHuman_Temple_Stash";
		break;
		
		case "DH_mercenary_temple_afterfight":
			dialog.Text = "������� ���� ��������. ����������� �����, ��� ��� ����� ������ ������� ���������� ����� ... �� �� ��.";
			Link.l1 = "������ ���� ��������.";
			Link.l1.go = "DH_mercenary_temple_afterfight_1";
		break;
		case "DH_mercenary_temple_afterfight_1":
			dialog.Text = "��, �� ��������� �����. ���� �� ��� �������� �� ���� ����. � �� ����� ����� ������... ";
			Link.l1 = "� ��������, ���� �� ����� ��� �� ����.";
			Link.l1.go = "DH_mercenary_temple_afterfight_2";
		break;
		case "DH_mercenary_temple_afterfight_2":
			dialog.Text = "� ��� ����� ��� ���� ��� ...";
			Link.l1 = "... ��� ...";
			Link.l1.go = "DH_mercenary_temple_afterfight_3";
		break;
		case "DH_mercenary_temple_afterfight_3":
			chrDisableReloadToLocation = false;
			dialog.Text = "... ��� ���������� �� ��������. �� ���� ��� ������. ������ � �� ����� �����.";
			Link.l1 = "...";
			Link.l1.go = "exit";
		break;	
		
		case "DH_mercenary_temple":
			dialog.Text = "��� �������, ���� �� ����� �����������.";
			Link.l1 = "������� �� ���?";
			Link.l1.go = "DH_mercenary_temple_2";
		break;
		case "DH_mercenary_temple_2":
			dialog.Text = "������ ���� ������� ������. ��� ������ �� ����� �� ����������, ���� ����� ����������� ����������.";
			Link.l1 = "����������� ����?";
			Link.l1.go = "DH_mercenary_temple_3";
		break;
		case "DH_mercenary_temple_3":
			dialog.Text = "������.";
			Link.l1 = "������, � �����!";
			Link.l1.go = "DH_mercenary_temple_exit";
		break;
		case "DH_mercenary_temple_exit":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(npchar, PChar);
			LAi_warrior_DialogEnable(npchar, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
			}
			
			for (i = 0; i < sti(pchar.maxIndians) * 2; i++)
			{
				sld = CharacterFromID("DHindian" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
		break;
		
		case "DH_mercenary_shore":
			dialog.Text = "������ ���� ���������, �� �� �����.";
			Link.l1 = "������. ��������� ���� ��������?";
			Link.l1.go = "DH_mercenary_shore_1";
		break;
		case "DH_mercenary_shore_1":
			dialog.Text = "��������...";
			Link.l1 = "�� ��������. ��� ��� ��������� �������� ����� ��� ���. ��� �� �����������?";
			Link.l1.go = "DH_mercenary_shore_2";
		break;
		case "DH_mercenary_shore_2":
			dialog.Text = "�� ������ �� ������ �����, �� ������ ������� ����� ���������, � ������ � ����������.";
			Link.l1 = "�������?";
			Link.l1.go = "DH_mercenary_shore_3";
		break;
		case "DH_mercenary_shore_3":
			dialog.Text = "��, ������� ������. ������� ������� ���� � ��� ������. (������ �� ������ ����������)";
			Link.l1 = "����� ������������� �� ����� ������ �������.";
			Link.l1.go = "DH_mercenary_shore_exit";
		break;
		case "DH_mercenary_shore_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			PChar.quest.DarkHuman_Temple.win_condition.l1 = "location";
			PChar.quest.DarkHuman_Temple.win_condition.l1.location = "Temple";
			PChar.quest.DarkHuman_Temple.function = "DarkHuman_Temple";
			
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "PGG_transporter":
			//LAi_ActorSetSitMode(pchar);
			dialog.Text = "�� �������, ���� ���� ������ � �������.";
			Link.l1 = "�������, ���� ������������� �� ��������� ����������� ���������.";
			Link.l1.go = "PGG_transporter_1";
		break;
		case "PGG_transporter_1":
			dialog.Text = "������ �������.";
			Link.l1 = "������������, ����� ��������?";
			Link.l1.go = "PGG_transporter_2";
		break;
		case "PGG_transporter_2":
			dialog.Text = "������ � ������� ����.";
			Link.l1 = "��� �����, �� � ����.";
			Link.l1.go = "PGG_transporter_exit";
		break;
		case "PGG_transporter_exit":
			DialogExit();
			NextDiag.CurrentNode = "Second Time";
			if (npchar.sex != "woman")	npchar.Dialog.FileName = "PGG_dialog.c";
			else	npchar.Dialog.FileName = "pgg_dialog_town.c";
			//PGG_ChangeRelation2MainCharacter(npchar, 25);
			DoQuestFunctionDelay("DarkHuman_Amatike", 1.0);
			//LAi_SetWarriorType(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_fight_sailor":
			pchar.quest.DH_mercenary.win_condition.l1 = "NPC_Death";
			pchar.quest.DH_mercenary.win_condition.l1.character ="DH_sailor";
			PChar.quest.DH_mercenary.function = "SpeakAfterKill";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
			
			
			sld = CharacterFromID("DH_mercenary");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(sld, PChar);
			LAi_warrior_DialogEnable(sld, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}
				
				sld = CharacterFromID("DH_merc_blade" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}
				
			}
		break;
		
		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

