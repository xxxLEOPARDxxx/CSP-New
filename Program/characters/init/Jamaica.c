
int CreateJamaicaCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// �������� ���������
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//����������
	ch.id		= "PortRoyal_Mayor";
	ch.model	= "huber_spa";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "eng_gov_common";
	ch.nation = ENGLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������
	ch.id		= "PortRoyal_Priest";
	ch.model	= "priest_1";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "Gr_Church";
	ch.nation = ENGLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ����������
	ch.id		= "PortRoyal_waitress";
	ch.model	= "girl_1";
	ch.sex = "woman";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Gr_officiant";
	ch.nation = ENGLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//����������
	ch.id		= "PortRoyal_tavernkeeper";
	ch.model	= "barmen_13";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = ENGLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������
	ch.id		= "PortRoyal_trader";
	ch.model	= "trader_13";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = ENGLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//�������
	ch.id		= "PortRoyal_shipyarder";
	ch.model	= "shipowner_13";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = ENGLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//������
	ch.id		= "PortRoyal_usurer";
	ch.model	= "usurer_3";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = ENGLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 9000; // *1000 �����
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������� �����
	ch.id		= "PortRoyal_PortMan";
	ch.model	= "usurer_7";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = ENGLAND;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//������� �������
	ch.id		= "PortRoyal_Hostess";
	ch.name		= "�������";
	ch.lastname = "";
	ch.model	= "lady03";
	ch.sex = "woman";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.greeting = "hostess";
	ch.nation = ENGLAND;
	ch.questChurch = ""; //���� ��� �������������
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= "�������������";
	ch.lastname = "";
	ch.id		= "PortRoyal_Smuggler";
	ch.model    = "pirate_1";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	ch.equip.blade = BLADE_SABER;
	// ������� � ����������
	ch.Dialog.Filename = "Smuggler Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "Gr_Smuggler Agent";
	n = n + 1;
	
   //=============== ���� ����� ===============

	makeref(ch,Characters[n]);			//����������
	ch.id		= "FortOrange_Mayor";
	ch.model	= "huber_spa";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.nation = HOLLAND;
	ch.quest.type = "hovernor";
	ch.greeting = "eng_gov_common";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������
	ch.id		= "FortOrange_Priest";
	ch.model	= "priest_4";
	ch.model.animation = "man"; 
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "Gr_Church";
	ch.nation = HOLLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ����������
	ch.id		= "FortOrange_waitress";
	ch.model	= "girl_1";
	ch.sex = "woman";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Gr_officiant";
	ch.nation = HOLLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//����������
	ch.id		= "FortOrange_tavernkeeper";
	ch.model	= "barmen_13";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = HOLLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������
	ch.id		= "FortOrange_trader";
	ch.model	= "trader_13";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = HOLLAND;
	LAi_SetBarmanType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//�������
	ch.id		= "FortOrange_shipyarder";
	ch.model	= "shipowner_2";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = HOLLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetHuberType(ch);
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	makeref(ch,Characters[n]);			//��������� �����
	ch.id		= "FortOrange_PortMan";
	ch.model	= "usurer_5";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = HOLLAND;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//������
	ch.id		= "FortOrange_usurer";
	ch.model	= "usurer_3";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = HOLLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 7000; // *1000 �����
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= "�������������";
	ch.lastname = "";
	ch.id		= "FortOrange_Smuggler";
	ch.model    = "pirate_1";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	ch.equip.blade = BLADE_SABER;
	// ������� � ����������
	ch.Dialog.Filename = "Smuggler Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "Gr_Smuggler Agent";
	n = n + 1;
	
		makeref(ch,Characters[n]);			// ����������
	ch.id		= "Builder";
	ch.name	= "��������";
	ch.lastname	= "��������";
	ch.model	= "Mechanic";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "BuilderHouse";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Builder.c";
	ch.Dialog.CurrentNode = "Hi1";
	ch.greeting = "Gr_Master";
	ch.nation = ENGLAND;
	ch.quest.type = "";
	ch.watchBoxes = true;
	ch.NotRemoved = true;
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor4");
	ch.equip.blade = "topor4";
	ch.equip.gun = GUN_COMMON;
	SetRandSPECIAL(ch);
    	SetSelfSkill(ch, 30, 30, 70, 50, 30);
    	SetShipSkill(ch, 30, 50, 30, 30, 40, 70, 30, 25, 70)
	ch.standUp = true; //�������� � �������� �� �����
	ch.NotCitizenBlade = true;
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	return n;
}
