
int CreateCaracasCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// �������� ���������
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//����������
	ch.id		= "Caracas_Mayor";
	ch.model	= "huber_spa";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "spa_gov_common";
	ch.nation = SPAIN;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
    LAi_LoginInCaptureTown(ch, true); //TO_DO eddy, ������
	n = n + 1;

    makeref(ch,Characters[n]);			//��������
	ch.id		= "Caracas_Priest";
	ch.model	= "priest_1";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "Gr_Church";
	ch.nation = SPAIN;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	makeref(ch,Characters[n]);		// ����������
	ch.id		= "Caracas_waitress";
	ch.model	= "girl_3";
	ch.sex = "woman";
	ch.City = "Caracas";
	ch.location	= "Caracas_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "Gr_officiant";
	ch.nation = SPAIN;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//����������
	ch.id		= "Caracas_tavernkeeper";
	ch.model	= "barmen_7";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = SPAIN;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������
	ch.id		= "Caracas_trader";
	ch.model	= "trader_7";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = SPAIN;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//�������
	ch.id		= "Caracas_shipyarder";
	ch.model	= "shipowner_7";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = SPAIN;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; //�������� � �������� �� �����
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//������
	ch.id		= "Caracas_usurer";
	ch.model	= "usurer_1";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = SPAIN;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 8000; // *1000 �����
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//��������� �����
	ch.id		= "Caracas_PortMan";
	ch.model	= "usurer_7";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = SPAIN;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= "�������������";
	ch.lastname = "";
	ch.id		= "Caracas_Smuggler";
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
	
	return n;
}